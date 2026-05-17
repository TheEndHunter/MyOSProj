namespace QemuRunner
{
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using System.Text;

    public static class QEMU
    {
        // Track active bridges/terminals to ensure disposal on exit
        private static readonly object s_bridgeLock = new();
        private static readonly List<IDisposable> s_activeBridges = new();

        // PInvoke to manage a secondary console window (Windows only)
        private static class NativeConsole
        {
            [System.Runtime.InteropServices.DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool AllocConsole();
            [System.Runtime.InteropServices.DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool FreeConsole();
        }
        public static string BuildDrives(string directory)
        {
            if (!Directory.Exists(directory)) return string.Empty;

            Console.WriteLine($"Building Qemu Drive Layout from Directory: {Path.GetFullPath(directory)}");

            StringBuilder sb = new();
            foreach (string folder in Directory.GetDirectories(directory))
            {
                DirectoryInfo i = new(folder);
                sb.Append($"-drive file=fat:fat-type=fat32:rw:\"{i.FullName}\",label=\"{i.Name.ToUpperInvariant()}\",format=vvfat ");
            }
            return sb.ToString();
        }

        // Launches a simple terminal that connects to a Windows named pipe created by QEMU with '-serial pipe:<name>'.
        // The terminal bridges Console stdin/stdout to the pipe. Windows only.
        // Returns IDisposable to close the terminal bridge.
        public static IDisposable? StartPipeTerminal(string pipeName, CancellationToken? externalToken = null)
        {
            var isWindows = Environment.OSVersion.Platform is PlatformID.Win32S or PlatformID.Win32Windows or PlatformID.Win32NT or PlatformID.WinCE;
            if (!isWindows) return null;
            if (string.IsNullOrWhiteSpace(pipeName)) throw new ArgumentException("Pipe name is required", nameof(pipeName));

            var cts = externalToken.HasValue ? CancellationTokenSource.CreateLinkedTokenSource(externalToken.Value) : new CancellationTokenSource();
            var ct = cts.Token;

            // QEMU expects a duplex pipe at \\./pipe/<name>
            var client = new System.IO.Pipes.NamedPipeClientStream($"{pipeName}_server", pipeName, System.IO.Pipes.PipeDirection.InOut, System.IO.Pipes.PipeOptions.Asynchronous);
            client.Connect(5000);
            var enc = Encoding.UTF8;

            // Pipe -> Console
            var reader = new Thread(() =>
            {
                try
                {
                    var buf = new byte[4096];
                    while (!ct.IsCancellationRequested && client.IsConnected)
                    {
                        int n = 0;
                        try { n = client.Read(buf, 0, buf.Length); }
                        catch { n = 0; Thread.Sleep(10); }
                        if (n > 0)
                        {
                            var text = enc.GetString(buf, 0, n);
                            Console.Write(text);
                        }
                    }
                }
                catch { }
            })
            { IsBackground = true, Name = "QEMU-Pipe-Terminal-Reader" };

            // Console -> Pipe
            var writer = new Thread(() =>
            {
                try
                {
                    while (!ct.IsCancellationRequested && client.IsConnected)
                    {
                        string? line = null;
                        try { line = Console.ReadLine(); }
                        catch { line = null; }
                        if (line != null)
                        {
                            var data = enc.GetBytes(line + "\n");
                            try { client.Write(data, 0, data.Length); client.Flush(); }
                            catch { /* pipe may close */ }
                        }
                        else
                        {
                            Thread.Sleep(10);
                        }
                    }
                }
                catch { }
            })
            { IsBackground = true, Name = "QEMU-Pipe-Terminal-Writer" };

            reader.Start();
            writer.Start();

            return new BridgeDisposable(() =>
            {
                try { cts.Cancel(); } catch { }
                try { client.Dispose(); } catch { }
            });
        }

        // Starts a UDP bridge that proxies data to/from the QEMU process stdio when SerialTarget=Stdio (Windows only).
        // Returns IDisposable to stop the bridge. Caller must start the process before calling this.
        public static IDisposable? StartUdpStdioBridge(Process process, int port = 17000, CancellationToken? externalToken = null)
        {
            // Only supported on Windows and when stdio is redirected
            var isWindows = Environment.OSVersion.Platform is PlatformID.Win32S or PlatformID.Win32Windows or PlatformID.Win32NT or PlatformID.WinCE;
            if (!isWindows) return null;
            if (process is null) throw new ArgumentNullException(nameof(process));
            var si = process.StartInfo;
            if (!(si.RedirectStandardInput && si.RedirectStandardOutput)) return null;

            var cts = externalToken.HasValue ? CancellationTokenSource.CreateLinkedTokenSource(externalToken.Value) : new CancellationTokenSource();
            var ct = cts.Token;

            var udp = new System.Net.Sockets.UdpClient(new System.Net.IPEndPoint(System.Net.IPAddress.Loopback, port));
            udp.Client.ReceiveTimeout = 1000;
            udp.Client.SendTimeout = 1000;

            var stdout = process.StandardOutput;
            var stdin = process.StandardInput;

            // Track the remote endpoint to echo back
            System.Net.IPEndPoint? remote = null;

            // Reader: QEMU stdout -> UDP
            var readerThread = new Thread(() =>
            {
                try
                {
                    char[] buffer = new char[4096];
                    var enc = Encoding.UTF8;
                    while (!ct.IsCancellationRequested && !process.HasExited)
                    {
                        int read = 0;
                        try { read = stdout.Read(buffer, 0, buffer.Length); }
                        catch { read = 0; }
                        if (read > 0 && remote != null)
                        {
                            var bytes = enc.GetBytes(buffer.AsSpan(0, read).ToArray());
                            try { udp.Send(bytes, bytes.Length, remote); } catch { /* ignore transient UDP errors */ }
                        }
                        else
                        {
                            Thread.Sleep(10);
                        }
                    }
                }
                catch { }
            })
            { IsBackground = true, Name = "QEMU-UDP-STDIO-Reader" };

            // Writer: UDP -> QEMU stdin
            var writerThread = new Thread(() =>
            {
                try
                {
                    var enc = Encoding.UTF8;
                    while (!ct.IsCancellationRequested && !process.HasExited)
                    {
                        try
                        {
                            var ep = new System.Net.IPEndPoint(System.Net.IPAddress.Any, 0);
                            udp.Client.ReceiveTimeout = 500;
                            byte[]? data = null;
                            try { data = udp.Receive(ref ep); }
                            catch (System.Net.Sockets.SocketException) { data = null; }
                            if (data != null && data.Length > 0)
                            {
                                remote = ep;
                                var text = enc.GetString(data);
                                try { stdin.Write(text); stdin.Flush(); }
                                catch { /* ignore write errors if process exits */ }
                            }
                        }
                        catch { }
                    }
                }
                catch { }
            })
            { IsBackground = true, Name = "QEMU-UDP-STDIO-Writer" };

            readerThread.Start();
            writerThread.Start();

            // Dispose bridge when QEMU process exits or terminal/app exits
            var disposable = new BridgeDisposable(() =>
            {
                try { cts.Cancel(); } catch { }
                try { udp.Dispose(); } catch { }
            });

            void OnProcessExited(object? s, EventArgs e)
            {
                try { disposable.Dispose(); } catch { }
                try { process.Exited -= OnProcessExited; } catch { }
            }

            void OnProcessExit(object? s, EventArgs e)
            {
                try { disposable.Dispose(); } catch { }
                try { AppDomain.CurrentDomain.ProcessExit -= OnProcessExit; } catch { }
            }

            void OnCancel(object? s, ConsoleCancelEventArgs e)
            {
                try { disposable.Dispose(); } catch { }
                try { Console.CancelKeyPress -= OnCancel; } catch { }
            }

            try
            {
                process.EnableRaisingEvents = true;
                process.Exited += OnProcessExited;
                AppDomain.CurrentDomain.ProcessExit += OnProcessExit;
                Console.CancelKeyPress += OnCancel;
            }
            catch { }

            return disposable;
        }

        // Opens a secondary console window and bridges it to the UDP stdio bridge (Windows only).
        // Use together with StartUdpStdioBridge. Returns IDisposable to close the window/bridge.
        public static IDisposable? StartUdpTerminal(int port = 17000, CancellationToken? externalToken = null)
        {
            var isWindows = Environment.OSVersion.Platform is PlatformID.Win32S or PlatformID.Win32Windows or PlatformID.Win32NT or PlatformID.WinCE;
            if (!isWindows) return null;

            var cts = externalToken.HasValue ? CancellationTokenSource.CreateLinkedTokenSource(externalToken.Value) : new CancellationTokenSource();
            var ct = cts.Token;

            // Create a dedicated console window for the terminal
            try { NativeConsole.AllocConsole(); } catch { }

            var udp = new System.Net.Sockets.UdpClient();
            udp.Client.ReceiveTimeout = 500;
            udp.Client.SendTimeout = 500;

            var enc = Encoding.UTF8;
            var remoteEp = new System.Net.IPEndPoint(System.Net.IPAddress.Loopback, port);

            // Reader: UDP -> Console
            var reader = new Thread(() =>
            {
                try
                {
                    using var recv = new System.Net.Sockets.UdpClient(new System.Net.IPEndPoint(System.Net.IPAddress.Loopback, port));
                    recv.Client.ReceiveTimeout = 500;
                    while (!ct.IsCancellationRequested)
                    {
                        try
                        {
                            var ep = new System.Net.IPEndPoint(System.Net.IPAddress.Any, 0);
                            byte[] data = recv.Receive(ref ep);
                            if (data != null && data.Length > 0)
                            {
                                var text = enc.GetString(data);
                                Console.Write(text);
                            }
                        }
                        catch (System.Net.Sockets.SocketException) { }
                        catch { }
                    }
                }
                catch { }
            }) { IsBackground = true, Name = "QEMU-UDP-Terminal-Reader" };

            // Writer: Console -> UDP
            var writer = new Thread(() =>
            {
                try
                {
                    while (!ct.IsCancellationRequested)
                    {
                        string? line = null;
                        try { line = Console.ReadLine(); }
                        catch { line = null; }
                        if (line != null)
                        {
                            var data = enc.GetBytes(line + "\n");
                            try { udp.Send(data, data.Length, remoteEp); } catch { }
                        }
                        else
                        {
                            Thread.Sleep(10);
                        }
                    }
                }
                catch { }
            }) { IsBackground = true, Name = "QEMU-UDP-Terminal-Writer" };

            reader.Start();
            writer.Start();

            return new BridgeDisposable(() =>
            {
                try { cts.Cancel(); } catch { }
                try { udp.Dispose(); } catch { }
                try { NativeConsole.FreeConsole(); } catch { }
            });
        }

        private sealed class BridgeDisposable : IDisposable
        {
            private readonly Action _dispose;
            private bool _done;
            public BridgeDisposable(Action dispose) => _dispose = dispose;
            public void Dispose()
            {
                if (_done) return; _done = true; _dispose();
            }
        }

        // Validate that required volume labels (folder names) exist under the image directory.
        // Returns true when all required labels are present; missingLabels will contain a comma-separated list otherwise.
        public static bool ValidateRequiredLabels(string directory, IEnumerable<string> requiredLabels, out string missingLabels)
        {
            missingLabels = string.Empty;
            if (!Directory.Exists(directory))
            {
                missingLabels = string.Join(",", requiredLabels);
                return false;
            }

            var present = Directory.GetDirectories(directory)
                                   .Select(d => new DirectoryInfo(d).Name.ToUpperInvariant())
                                   .ToHashSet(StringComparer.OrdinalIgnoreCase);

            var missing = requiredLabels.Where(r => !present.Contains(r.ToUpperInvariant())).ToArray();
            if (missing.Length > 0)
            {
                missingLabels = string.Join(",", missing);
                return false;
            }

            return true;
        }

        // Writes the generated QEMU command line to a timestamped file in the temp directory for debugging.
        public static void WriteCommandToTempFile(string command)
        {
            try
            {
                var fileName = $"qemu_command_{DateTime.Now:yyyyMMdd_HHmmss}.txt";
                // Try to write to current directory (where logs are created). Fall back to temp if not writable.
                string dir = Directory.GetCurrentDirectory();
                string path = Path.Combine(dir, fileName);
                try
                {
                    File.WriteAllText(path, command);
                    Console.WriteLine($"Wrote QEMU command to: {path}");
                    return;
                }
                catch
                {
                    // fallback to temp  
                }

                path = Path.Combine(Path.GetTempPath(), fileName);
                File.WriteAllText(path, command);
                Console.WriteLine($"Wrote QEMU command to: {path}");
            }
            catch
            {
                // best-effort, do not fail the run for diagnostics write failures
            }
        }


        public static string FindPath(string qemuExecutableName)
        {
            var tried = new List<string>();

            // If caller supplied a path (absolute or relative), check it directly first
            bool containsDir = Path.IsPathRooted(qemuExecutableName) || qemuExecutableName.Contains(Path.DirectorySeparatorChar) || qemuExecutableName.Contains(Path.AltDirectorySeparatorChar);
            string exeName = qemuExecutableName;
            // Determine platform-specific extension to try when one isn't provided
            string? platformExt = null;
            platformExt = Environment.OSVersion.Platform switch
            {
                PlatformID.Win32S or PlatformID.Win32Windows or PlatformID.Win32NT or PlatformID.WinCE => ".exe",
                PlatformID.Xbox => ".xex",
                _ => null,
            };

            // note: candidates are checked inline below and recorded in 'tried'

            if (containsDir)
            {
                // Try exact name first
                if (File.Exists(exeName)) return Path.GetFullPath(exeName);
                // Try with platform extension if missing
                if (platformExt != null && Path.GetExtension(exeName) == string.Empty)
                {
                    var withExt = exeName + platformExt;
                    if (File.Exists(withExt)) return Path.GetFullPath(withExt);
                    tried.Add(withExt);
                }
                tried.Add(exeName);
                // Not found
                Console.WriteLine($"QEMU executable '{qemuExecutableName}' was provided as a path but was not found. Tried: {string.Join(';', tried)}");
                return string.Empty;
            }

            // Try current directory first
            var cwdCandidate = Path.Combine(Directory.GetCurrentDirectory(), exeName);
            if (File.Exists(cwdCandidate)) return Path.GetFullPath(cwdCandidate);
            if (platformExt != null && Path.GetExtension(exeName) == string.Empty)
            {
                var cwdWithExt = cwdCandidate + platformExt;
                if (File.Exists(cwdWithExt)) return Path.GetFullPath(cwdWithExt);
                tried.Add(cwdWithExt);
            }
            tried.Add(cwdCandidate);

            string? paths = Environment.GetEnvironmentVariable("PATH");
            if (!string.IsNullOrEmpty(paths))
            {
                foreach (var path in paths.Split(Path.PathSeparator))
                {
                    if (string.IsNullOrWhiteSpace(path)) continue;
                    var fullPath = Path.Combine(path, exeName);
                    if (File.Exists(fullPath)) return Path.GetFullPath(fullPath);
                    tried.Add(fullPath);
                    if (platformExt != null && Path.GetExtension(exeName) == string.Empty)
                    {
                        var fullWithExt = fullPath + platformExt;
                        if (File.Exists(fullWithExt)) return Path.GetFullPath(fullWithExt);
                        tried.Add(fullWithExt);
                    }
                }
            }

            Console.WriteLine($"QEMU executable '{qemuExecutableName}' not found. Tried locations: {string.Join(';', tried)}");
            return string.Empty;
        }

        public static Process? StartProcess(QEMUConfig config, string ovmfPath, string imagePath)
        {
            try
            {
                string qemuPath = QEMU.FindPath(config.Name);

                if (string.IsNullOrEmpty(qemuPath))
                {
                    Console.WriteLine("QEMU executable not found in PATH.");
                    return null;
                }

                var ovmfCodePath = Path.Combine(ovmfPath, "OVMF_CODE.fd");
                var ovmfVarPath = Path.Combine(ovmfPath, "OVMF_VARS.fd");

                if (!File.Exists(ovmfCodePath))
                {
                    throw new FileNotFoundException($"OVMF Code file not found in location: {ovmfCodePath}");
                }

                if (!File.Exists(ovmfVarPath))
                {
                    throw new FileNotFoundException($"OVMF Var file not found in location: {ovmfVarPath}");
                }

                string drives = BuildDrives(imagePath);

                // Build structured arguments (new)
                string structuredArgs = config.BuildArgumentsString();

                // Ensure serial option is present in the structured args if needed
                if (config.SerialTarget == QEMUConfig.SerialTargetType.Disabled)
                {
                    // do not add -serial (default behaviour)
                }
                else if (config.SerialTarget == QEMUConfig.SerialTargetType.Off)
                {
                    if (!structuredArgs.Contains("-serial")) structuredArgs += " -serial disabled";
                }
                else if (config.SerialTarget == QEMUConfig.SerialTargetType.Stdio)
                {
                    // forward QEMU serial to UDP so secondary console can bridge
                    var port = config.SerialUdpPort;
                    if (!structuredArgs.Contains("-serial")) structuredArgs += $" -serial udp:127.0.0.1:{port}";
                }
                else if (config.SerialTarget == QEMUConfig.SerialTargetType.File)
                {
                    // generate filename from template and append
                    var fname = config.SerialFileTemplate;
                    fname = fname.Replace("{arch}", string.IsNullOrWhiteSpace(config.Architecture) ? "unknown" : config.Architecture);
                    fname = fname.Replace("{config}", string.IsNullOrWhiteSpace(config.Configuration) ? "unknown" : config.Configuration);
                    fname = fname.Replace("{timestamp}", System.DateTime.UtcNow.ToString("yyyyMMddHHmmss"));
                    if (!Path.IsPathRooted(fname)) fname = Path.Combine(Directory.GetCurrentDirectory(), fname);
                    if (!structuredArgs.Contains("-serial")) structuredArgs += " -serial file:" + QuoteIfNeeded(fname);
                }

                string qemuArguments = ($"{structuredArgs} -drive if=pflash,format=raw,readonly=on,file=\"{ovmfCodePath}\" -drive if=pflash,format=raw,file=\"{ovmfVarPath}\" {drives}").Trim();

                // Sanitize arguments for quoting and control characters
                qemuArguments = SanitizeArguments(qemuArguments);

                // Validate expected labels exist under the image path. Fail early with an informative message.
                string missing;
                var required = new[] { "SYS", "EFI", "LIBS" };
                if (!ValidateRequiredLabels(imagePath, required, out missing))
                {
                    Console.WriteLine($"Missing expected volume folders (labels): {missing}. Aborting QEMU start.");
                    return null;
                }

                // Build and write full command to a temp file to aid debugging if needed.
                var fullCmd = qemuPath + " " + qemuArguments;
                WriteCommandToTempFile(fullCmd);

                Console.WriteLine($"Starting Qemu With the Following Configurations:{Environment.NewLine}\tArch: {config.Architecture}");
                Console.WriteLine($"\tConfig: {config.Configuration}");
                Console.WriteLine($"\tOVMF_CODE path: {ovmfCodePath}{Environment.NewLine}\tOVMF_VARS path: {ovmfVarPath}{Environment.NewLine}");

                var psi = new ProcessStartInfo(qemuPath, qemuArguments)
                {
                    UseShellExecute = false,
                    CreateNoWindow = false,
                };

                Console.WriteLine($"ProcessStartInfo: FileName={psi.FileName} Args={psi.Arguments} UseShellExecute={psi.UseShellExecute} RedirectStdout={psi.RedirectStandardOutput} RedirectStderr={psi.RedirectStandardError} RedirectStdin={psi.RedirectStandardInput}");

                // Configure redirection based on serial target. If stdio is used, redirect stdio so the runner can interact.
                switch (config.SerialTarget)
                {
                    case QEMUConfig.SerialTargetType.File:
                        // When serial output is redirected to a file by QEMU, the runner does not need to capture stdin.
                        psi.RedirectStandardOutput = true;
                        psi.RedirectStandardError = true;
                        psi.RedirectStandardInput = false;
                        break;
                    case QEMUConfig.SerialTargetType.Pipes:
                        // With named pipes, QEMU handles I/O at the pipe device; keep stdio redirected for logs.
                        psi.RedirectStandardOutput = true;
                        psi.RedirectStandardError = true;
                        psi.RedirectStandardInput = true;
                        break;
                    case QEMUConfig.SerialTargetType.Disabled:
                    case QEMUConfig.SerialTargetType.Off:
                        // keep reading output but do not expect interactive input
                        psi.RedirectStandardOutput = true;
                        psi.RedirectStandardError = true;
                        psi.RedirectStandardInput = true;
                        break;
                    case QEMUConfig.SerialTargetType.Stdio:
                    default:
                        psi.RedirectStandardOutput = true;
                        psi.RedirectStandardError = true;
                        psi.RedirectStandardInput = true;
                        break;
                }

                var proc = new Process()
                {
                    StartInfo = psi,
                    EnableRaisingEvents = true,
                };

                // If using pipes, start a secondary terminal bridge to the named pipe
                if (config.SerialTarget == QEMUConfig.SerialTargetType.Pipes && !string.IsNullOrWhiteSpace(config.SerialPipeName))
                {
                    try
                    {
                        var term = StartPipeTerminal(config.SerialPipeName);
                        if (term != null)
                        {
                            lock (s_bridgeLock) s_activeBridges.Add(term);
                            void DisposeTerm()
                            {
                                try
                                {
                                    lock (s_bridgeLock)
                                    {
                                        if (s_activeBridges.Remove(term)) term.Dispose();
                                    }
                                }
                                catch { }
                            }

                            proc.Exited += (_, __) => DisposeTerm();
                            AppDomain.CurrentDomain.ProcessExit += (_, __) => DisposeTerm();
                            Console.CancelKeyPress += (_, __) => DisposeTerm();
                        }
                    }
                    catch { /* optional terminal setup */ }
                }

                // If using stdio, start a UDP stdio bridge and launch a secondary terminal window attached to it
                if (config.SerialTarget == QEMUConfig.SerialTargetType.Stdio)
                {
                    try
                    {
                        var bridge = StartUdpStdioBridge(proc);
                        var term = StartUdpTerminal();
                        lock (s_bridgeLock)
                        {
                            if (bridge != null) s_activeBridges.Add(bridge);
                            if (term != null) s_activeBridges.Add(term);
                        }
                        void DisposeAll()
                        {
                            try
                            {
                                lock (s_bridgeLock)
                                {
                                    foreach (var d in s_activeBridges.ToList())
                                    {
                                        try { d.Dispose(); } catch { }
                                        s_activeBridges.Remove(d);
                                    }
                                }
                            }
                            catch { }
                        }
                        proc.Exited += (_, __) => DisposeAll();
                        AppDomain.CurrentDomain.ProcessExit += (_, __) => DisposeAll();
                        Console.CancelKeyPress += (_, __) => DisposeAll();
                    }
                    catch { /* optional terminal setup */ }
                }

                return proc;
            }
            catch (Exception ex)
            {
                // Provide full exception details for diagnostics
                Console.WriteLine("Failed to start QEMU process:");
                Console.WriteLine(ex.ToString());
                return null;
            }
        }

        // BuildFullCommand builds the fully resolved command string including executable path and sanitized arguments.
        public static string BuildFullCommand(QEMUConfig config, string ovmfPath, string imagePath)
        {
            string qemuPath = QEMU.FindPath(config.Name);
            var ovmfCodePath = Path.Combine(ovmfPath, "OVMF_CODE.fd");
            var ovmfVarPath = Path.Combine(ovmfPath, "OVMF_VARS.fd");
            string structuredArgs = config.BuildArgumentsString();

            if (config.SerialTarget == QEMUConfig.SerialTargetType.Off)
            {
                if (!structuredArgs.Contains("-serial")) structuredArgs += " -serial disabled";
            }
            else if (config.SerialTarget == QEMUConfig.SerialTargetType.Stdio)
            {
                var port = config.SerialUdpPort;
                if (!structuredArgs.Contains("-serial")) structuredArgs += $" -serial udp:127.0.0.1:{port}";
            }
            else if (config.SerialTarget == QEMUConfig.SerialTargetType.File)
            {
                var fname = config.SerialFileTemplate;
                fname = fname.Replace("{arch}", string.IsNullOrWhiteSpace(config.Architecture) ? "unknown" : config.Architecture);
                fname = fname.Replace("{config}", string.IsNullOrWhiteSpace(config.Configuration) ? "unknown" : config.Configuration);
                fname = fname.Replace("{timestamp}", System.DateTime.UtcNow.ToString("yyyyMMddHHmmss"));
                if (!Path.IsPathRooted(fname)) fname = Path.Combine(Directory.GetCurrentDirectory(), fname);
                if (!structuredArgs.Contains("-serial")) structuredArgs += " -serial file:" + QuoteIfNeeded(fname);
            }

            string qemuArguments = ($"{structuredArgs} -drive if=pflash,format=raw,readonly=on,file=\"{ovmfCodePath}\" -drive if=pflash,format=raw,file=\"{ovmfVarPath}\" {BuildDrives(imagePath)}").Trim();
            qemuArguments = SanitizeArguments(qemuArguments);
            return qemuPath + " " + qemuArguments;
        }

        // Basic sanitization: remove control characters, ensure balanced quotes; if unbalanced, escape quotes.
        private static string SanitizeArguments(string args)
        {
            if (args is null) return string.Empty;
            // Remove newlines and control characters that would break the argument parsing
            var filtered = new string(args.Where(c => c == '"' || (c >= ' ' && c != '\u007f')).ToArray());

            int quoteCount = filtered.Count(c => c == '"');
            if ((quoteCount & 1) == 1)
            {
                // Unbalanced quotes: escape all quotes to avoid breaking the argument parsing
                Console.WriteLine("Warning: Unbalanced quotes detected in QEMU arguments. Escaping quotes for safety.");
                filtered = filtered.Replace("\"", "\\\"");
            }

            return filtered;
        }

        // (Serial argument is handled by QEMUConfig.BuildArgumentsString)

        private static string QuoteIfNeeded(string path)
        {
            if (path.Contains(' '))
            {
                return '"' + path + '"';
            }
            return path;
        }
    }
}
