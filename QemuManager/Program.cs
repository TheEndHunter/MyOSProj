using System.Diagnostics;
using System.Text;

using System.Linq;
using Microsoft.Extensions.Configuration;

namespace QemuRunner
{
    public static class Program
    {
        private static Process? qemu = null;
        private static Process? lldb = null;
        private static readonly System.Text.RegularExpressions.Regex AnsiRegex = new("\\x1B\\[[0-9;?]*[ -/]*[@-~]|\\x1B\\][^\\x07]*\\x07|\\x1B[@-_]", System.Text.RegularExpressions.RegexOptions.Compiled);
        static async Task<int> Main(string[] args)
        {
            // Early bridge-only mode: if --bridge flag is present, skip updates/config and start the requested server.
            var bridgeArg = args.FirstOrDefault(a => a.StartsWith("--bridge=", StringComparison.OrdinalIgnoreCase));
            if (bridgeArg != null)
            {
                var mode = bridgeArg.Split('=', 2, StringSplitOptions.RemoveEmptyEntries).ElementAtOrDefault(1)?.ToLowerInvariant() ?? string.Empty;
                if (mode == "stdio")
                {
                    int port = 17000;
                    var portArg = args.FirstOrDefault(a => a.StartsWith("--port=", StringComparison.OrdinalIgnoreCase));
                    if (portArg != null && int.TryParse(portArg.Split('=', 2)[1], out var p) && p > 0 && p <= 65535) port = p;
                    var term = QEMU.StartUdpTerminal(port);
                    if (term == null)
                    {
                        Console.WriteLine("Failed to start UDP terminal (Windows-only).");
                        return -1;
                    }
                    Console.Title = $"QemuManager UDP Terminal ({port})";
                    Console.WriteLine($"QemuManager terminal bridge running (UDP 127.0.0.1:{port}). Press Ctrl+C to exit.");
                    Console.CancelKeyPress += (_, __) => term.Dispose();
                    AppDomain.CurrentDomain.ProcessExit += (_, __) => term.Dispose();
                    await Task.Delay(Timeout.InfiniteTimeSpan);
                    return 0;
                }
                else if (mode == "pipes")
                {
                    string pipe = "QemuManagerServer";
                    var pipeArg = args.FirstOrDefault(a => a.StartsWith("--pipe=", StringComparison.OrdinalIgnoreCase));
                    if (pipeArg != null) pipe = pipeArg.Split('=', 2, StringSplitOptions.RemoveEmptyEntries).ElementAtOrDefault(1) ?? pipe;
                    var term = QEMU.StartPipeTerminal(pipe);
                    if (term == null)
                    {
                        Console.WriteLine("Failed to start pipe terminal (Windows-only).");
                        return -1;
                    }
                    Console.Title = $"QemuManager Pipe Terminal ({pipe})";
                    Console.WriteLine($"QemuManager pipe bridge running (\\\\.\\pipe\\{pipe}). Press Ctrl+C to exit.");
                    Console.CancelKeyPress += (_, __) => term.Dispose();
                    AppDomain.CurrentDomain.ProcessExit += (_, __) => term.Dispose();
                    await Task.Delay(Timeout.InfiniteTimeSpan);
                    return 0;
                }
            }
            Settings config;
            string Dir = Path.GetFullPath(Directory.GetCurrentDirectory());
            string SettingsPath = Path.Combine(Dir, "Settings.json");

            if (File.Exists(SettingsPath))
            {
                ConfigurationBuilder builder = new();
                builder.SetBasePath(Dir);
                builder.AddJsonFile(SettingsPath, false);

                IConfigurationRoot root = builder.Build();

                config = new Settings(root);
            }
            else
            {
                config = new Settings()
                {
                    Architectures = ["x86", "x64", "arm", "arm64"],
                    Configurations = ["debug", "release"],
                    OVMFConfiguration = null,
                };
            }

            Console.Title = "Qemu Virtual Machine Starter Tool";

            if (!Directory.Exists(Path.Combine(Dir, "OVMF")) && config.OVMFConfiguration.HasValue)
            {
                await OVMF.UpdateAsync(config);
            }

            var verPath = Path.Combine(Dir, "OVMF", "Version.txt");
            if (File.Exists(verPath))
            {
                var sha1 = File.ReadLines(verPath).FirstOrDefault();
                if (!string.IsNullOrEmpty(sha1))
                {
                    await OVMF.UpdateAsync(config, sha1);
                }
                else
                {
                    await OVMF.UpdateAsync(config);
                }
            }

            string? architecture = args.Length > 0 ? args[0].ToLower() : null;
            string? configuration = args.Length > 1 ? args[1].ToLower() : null;
            string? imagePath = args.Length > 2 ? Path.GetFullPath(args[2]) : null;

            if (string.IsNullOrEmpty(architecture) || string.IsNullOrEmpty(configuration) || string.IsNullOrEmpty(imagePath))
            {
                Console.WriteLine("Invalid or insufficient arguments. Please provide architecture, configuration, and image path.");
                return -1;
            }

            if (config.Architectures == null || config.Configurations == null || config.Architectures.Count < 1 || config.Configurations.Count < 1)
            {
                Console.WriteLine("Invalid configuration. Please provide valid configurations and architectures in the settings file.");
                return -1;
            }

            if (!config.Architectures.Contains(architecture) || !config.Configurations.Contains(configuration))
            {
                Console.WriteLine("Invalid architecture or configuration.");
                return -1;
            }

            if (!Directory.Exists(imagePath))
            {
                Console.WriteLine("Image path does not exist.");
                return -1;
            }

            QEMUConfig? qemuConf = config.QemuConfigs!.Find(x => { return x.Architecture == architecture && x.Configuration == configuration; });

            if (qemuConf == null)
            {
                Console.WriteLine("No QEMU configuration found for the specified architecture and configuration.");
                return -1;
            }

            // If DryRun mode is enabled, print the fully resolved command and exit without starting QEMU.
            if (qemuConf.DryRun)
            {
                try
                {
                    var ovmfPath = Path.Combine(Dir, "OVMF", architecture, configuration);
                    var cmd = QEMU.BuildFullCommand(qemuConf, ovmfPath, imagePath);
                    Console.WriteLine("DRY RUN: Resolved QEMU command:");
                    Console.WriteLine(cmd);
                    // Also write to temp file for convenience
                    QEMU.WriteCommandToTempFile(cmd);
                    return 0;
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Failed to build QEMU command for DryRun:");
                    Console.WriteLine(ex.ToString());
                    return -1;
                }
            }


            AppDomain.CurrentDomain.ProcessExit += (s, e) =>
            {
                qemu?.Kill(true);
                lldb?.Kill(true);
            };

            qemu = QEMU.StartProcess(qemuConf, Path.Combine(Dir, "OVMF", architecture, configuration), imagePath);
            // Optionally start LLDB based on configuration flag
            if (qemuConf.EnableLLDB)
            {
                lldb = LLDB.StartProcess(qemuConf);
            }

            if (qemu == null)
            {
                Console.WriteLine("Failed to start QEMU process.");
                return -1;
            }

            qemu.Exited += OnQemuTerminate;
            if (lldb != null)
            {
                lldb.Exited += OnLLDBTerminate;
            }

            try
            {
                if (!qemu.Start())
                {
                    Console.WriteLine("Failed to start QEMU process (Start returned false).");
                    return -1;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception while starting QEMU process:");
                Console.WriteLine(ex.ToString());
                return -1;
            }

            // Ensure console uses UTF8 so Unicode output displays correctly
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Console.InputEncoding = System.Text.Encoding.UTF8;

            // On Windows enable Virtual Terminal Processing so ANSI/VT sequences are interpreted by the terminal
            if (OperatingSystem.IsWindows())
            {
                try
                {
                    var handle = NativeMethods.GetStdHandle(NativeMethods.STD_OUTPUT_HANDLE);
                    if (NativeMethods.GetConsoleMode(handle, out uint mode))
                    {
                        NativeMethods.SetConsoleMode(handle, mode | NativeMethods.ENABLE_VIRTUAL_TERMINAL_PROCESSING | NativeMethods.DISABLE_NEWLINE_AUTO_RETURN);
                    }
                }
                catch { }
            }

            var cts = new CancellationTokenSource();
            qemu.Exited += (s, e) => cts.Cancel();

            // Create a UTF8 log file for captured output if enabled
            FileStream? logFs = null;
            StreamWriter? logWriter = null;
            if (qemuConf.EnableLogging)
            {
                string logPath = Path.Combine(Directory.GetCurrentDirectory(), $"qemu_{DateTime.Now:yyyyMMdd-HHmmss}.log");
                try
                {
                    logFs = new FileStream(logPath, FileMode.Create, FileAccess.Write, FileShare.Read);
                    logWriter = new StreamWriter(logFs, System.Text.Encoding.UTF8) { AutoFlush = true };
                }
                catch
                {
                    logWriter = null;
                    logFs?.Dispose();
                    logFs = null;
                }

                // Perform simple rotation: delete oldest files if more than LogMaxFiles
                try
                {
                    if (qemuConf.LogMaxFiles > 0)
                    {
                        var dir = Directory.GetCurrentDirectory();
                        var files = Directory.GetFiles(dir, "qemu_*.log").OrderByDescending(f => f).ToArray();
                        if (files.Length > qemuConf.LogMaxFiles)
                        {
                            foreach (var f in files.Skip(qemuConf.LogMaxFiles))
                            {
                                try { File.Delete(f); } catch { }
                            }
                        }
                    }
                }
                catch { }
            }

            Task stdoutTask;
            Task stderrTask;
            if (qemuConf.RawStdioMode)
            {
                // stateful ANSI buffer to handle CSI sequences split across reads
                StringBuilder ansiBuffer = new(4096);
                // Raw byte mode: decode with a UTF8 decoder to handle multi-byte sequences across reads
                stdoutTask = Task.Run(async () =>
                {
                    var buffer = new byte[4096];
                    var decoder = System.Text.Encoding.UTF8.GetDecoder();
                    var charBuf = new char[4096];
                    var stream = qemu.StandardOutput.BaseStream;
                    try
                    {
                        while (!cts.IsCancellationRequested)
                        {
                            int read = await stream.ReadAsync(buffer, 0, buffer.Length, cts.Token).ConfigureAwait(false);
                            if (read == 0) break;
                            // If logging raw, write a hex dump header for this read so we can inspect boundaries
                            if (logWriter != null && qemuConf.EnableRawLogging)
                            {
                                try
                                {
                                    var hex = BitConverter.ToString(buffer, 0, read).Replace('-', ' ');
                                    await logWriter.WriteLineAsync($"--RAW-READ-START len={read} hex={hex}").ConfigureAwait(false);
                                }
                                catch { }
                            }
                            int chars = decoder.GetChars(buffer, 0, read, charBuf, 0, false);
                            var s = new string(charBuf, 0, chars);

                            // Prepend any buffered ANSI prefix from previous partial read
                            if (ansiBuffer.Length > 0)
                            {
                                s = ansiBuffer.ToString() + s;
                                ansiBuffer.Clear();
                            }

                            // If the string ends with an ESC followed by '[' and digits but no final byte, buffer it
                            // Simple heuristic: if the string contains an ESC and the last char is not in the range '@'..'~', buffer tail
                            int escIdx = s.LastIndexOf('\u001B');
                            if (escIdx >= 0)
                            {
                                int tailLen = s.Length - escIdx;
                                if (tailLen > 0)
                                {
                                    // check if this tail likely is an incomplete CSI (starts with ESC[)
                                    if (tailLen >= 2 && s[escIdx + 1] == '[')
                                    {
                                        // find if final byte present
                                        bool hasFinal = false;
                                        for (int j = escIdx + 2; j < s.Length; j++)
                                        {
                                            char ch = s[j];
                                            if (ch >= '@' && ch <= '~') { hasFinal = true; break; }
                                        }
                                        if (!hasFinal)
                                        {
                                            // buffer the tail
                                            ansiBuffer.Append(s, escIdx, s.Length - escIdx);
                                            s = s.Substring(0, escIdx);
                                        }
                                    }
                                }
                            }

                            Console.Out.Write(s);
                            if (logWriter != null)
                            {
                                var write = qemuConf.StripAnsiSequences ? StripAnsiSequences(s) : s;
                                await logWriter.WriteAsync(write).ConfigureAwait(false);
                                try { await logWriter.WriteLineAsync("--RAW-READ-END").ConfigureAwait(false); } catch { }
                            }
                        }
                        int remaining = decoder.GetChars(Array.Empty<byte>(), 0, 0, charBuf, 0, true);
                        if (remaining > 0)
                        {
                            var s = new string(charBuf, 0, remaining);
                            Console.Out.Write(s);
                            if (logWriter != null)
                            {
                                var write = qemuConf.StripAnsiSequences ? StripAnsiSequences(s) : s;
                                await logWriter.WriteAsync(write).ConfigureAwait(false);
                            }
                        }
                    }
                    catch (OperationCanceledException) { }
                    catch (Exception ex)
                    {
                        Console.Error.WriteLine($"Error reading QEMU stdout: {ex.Message}");
                    }
                }, cts.Token);

                stderrTask = Task.Run(async () =>
            {
                var buffer = new byte[4096];
                var decoder = System.Text.Encoding.UTF8.GetDecoder();
                var charBuf = new char[4096];
                var stream = qemu.StandardError.BaseStream;
                try
                {
                    while (!cts.IsCancellationRequested)
                    {
                        int read = await stream.ReadAsync(buffer, 0, buffer.Length, cts.Token).ConfigureAwait(false);
                        if (read == 0) break;
                        if (logWriter != null && qemuConf.EnableRawLogging)
                        {
                            try
                            {
                                var hex = BitConverter.ToString(buffer, 0, read).Replace('-', ' ');
                                await logWriter.WriteLineAsync($"--RAW-ERR-READ-START len={read} hex={hex}").ConfigureAwait(false);
                            }
                            catch { }
                        }
                        int chars = decoder.GetChars(buffer, 0, read, charBuf, 0, false);
                        var s = new string(charBuf, 0, chars);

                        if (ansiBuffer.Length > 0)
                        {
                            s = ansiBuffer.ToString() + s;
                            ansiBuffer.Clear();
                        }

                        int escIdxErr = s.LastIndexOf('\u001B');
                        if (escIdxErr >= 0)
                        {
                            int tailLen = s.Length - escIdxErr;
                            if (tailLen > 0 && escIdxErr + 1 < s.Length && s[escIdxErr + 1] == '[')
                            {
                                bool hasFinal = false;
                                for (int j = escIdxErr + 2; j < s.Length; j++)
                                {
                                    char ch = s[j];
                                    if (ch >= '@' && ch <= '~') { hasFinal = true; break; }
                                }
                                if (!hasFinal)
                                {
                                    ansiBuffer.Append(s, escIdxErr, s.Length - escIdxErr);
                                    s = s.Substring(0, escIdxErr);
                                }
                            }
                        }

                        Console.Error.Write(s);
                        if (logWriter != null)
                        {
                            var write = qemuConf.StripAnsiSequences ? StripAnsiSequences(s) : s;
                            await logWriter.WriteAsync(write).ConfigureAwait(false);
                            try { await logWriter.WriteLineAsync("--RAW-ERR-READ-END").ConfigureAwait(false); } catch { }
                        }
                    }
                    int remaining = decoder.GetChars(Array.Empty<byte>(), 0, 0, charBuf, 0, true);
                    if (remaining > 0)
                    {
                        var s = new string(charBuf, 0, remaining);
                        Console.Error.Write(s);
                        if (logWriter != null)
                        {
                            var write = qemuConf.StripAnsiSequences ? StripAnsiSequences(s) : s;
                            await logWriter.WriteAsync(write).ConfigureAwait(false);
                        }
                    }
                }
                catch (OperationCanceledException) { }
                catch (Exception ex)
                {
                    Console.Error.WriteLine($"Error reading QEMU stderr: {ex.Message}");
                }
            }, cts.Token);

                // Forward raw bytes from host console input to QEMU stdin
                Task stdinTask = Task.Run(async () =>
                {
                    var inStream = Console.OpenStandardInput();
                    var outStream = qemu.StandardInput.BaseStream;
                    var buffer = new byte[1024];
                    try
                    {
                        while (!cts.IsCancellationRequested && !qemu.HasExited)
                        {
                            int read = await inStream.ReadAsync(buffer, 0, buffer.Length, cts.Token).ConfigureAwait(false);
                            if (read == 0) break;
                            await outStream.WriteAsync(buffer, 0, read, cts.Token).ConfigureAwait(false);
                            await outStream.FlushAsync(cts.Token).ConfigureAwait(false);
                        }
                    }
                    catch (OperationCanceledException) { }
                    catch (Exception) { }
                }, cts.Token);

                // Start LLDB after QEMU is running
                lldb?.Start();

                // Wait for QEMU exit, then cancel and wait for tasks to finish
                try
                {
                    while (!qemu.HasExited && !QemuExitCalled && !cts.IsCancellationRequested)
                    {
                        await Task.Delay(200, cts.Token).ConfigureAwait(false);
                    }
                }
                catch (OperationCanceledException) { }
                finally
                {
                    try { cts.Cancel(); } catch { }
                    try { await Task.WhenAll(new[] { stdoutTask, stderrTask, stdinTask }).WaitAsync(TimeSpan.FromSeconds(2)); } catch { }
                    if (logWriter != null) { try { logWriter.Flush(); logWriter.Dispose(); } catch { } }
                    if (logFs != null) { try { logFs.Dispose(); } catch { } }
                }
                while (!QemuExitCalled && !LLDBExitCalled)
                {
                    Thread.Yield();
                }
            }
            return 0;
        }

        private static bool QemuExitCalled = false;
        private static bool LLDBExitCalled = false;
        private static void OnQemuTerminate(object? sender, EventArgs e)
        {
            if (QemuExitCalled) return;

            QemuExitCalled = true;
            if (qemu is null) return;
            if (lldb is null)
            {
                LLDBExitCalled = true;
                return;
            }

            if (!lldb.HasExited)
            {
                lldb.Kill(true);
            }
        }

        private static void OnLLDBTerminate(object? sender, EventArgs e)
        {
            if (LLDBExitCalled) return;
            LLDBExitCalled = true;

            if (lldb is null) return;
            if (qemu is null) return;

            if (!qemu.HasExited)
            {
                qemu.Kill(true);
            }
        }

        private static string StripAnsiSequences(string input)
        {
            if (string.IsNullOrEmpty(input)) return input;
            return AnsiRegex.Replace(input, string.Empty);
        }

        internal static class NativeMethods
        {
            public const int STD_OUTPUT_HANDLE = -11;
            public const uint ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004;
            public const uint DISABLE_NEWLINE_AUTO_RETURN = 0x0008;

            [System.Runtime.InteropServices.DllImport("kernel32.dll", SetLastError = true)]
            public static extern IntPtr GetStdHandle(int nStdHandle);

            [System.Runtime.InteropServices.DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool GetConsoleMode(IntPtr hConsoleHandle, out uint lpMode);

            [System.Runtime.InteropServices.DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool SetConsoleMode(IntPtr hConsoleHandle, uint dwMode);
        }
    }
}

