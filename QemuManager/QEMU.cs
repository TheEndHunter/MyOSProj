namespace QemuRunner
{
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using System.Text;

    public static class QEMU
    {
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
                else if (config.SerialTarget == QEMUConfig.SerialTargetType.Stdio)
                {
                    if (!structuredArgs.Contains("-serial")) structuredArgs += " -serial stdio";
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
                    case QEMUConfig.SerialTargetType.Disabled:
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

                return new Process()
                {
                    StartInfo = psi,
                    EnableRaisingEvents = true,
                };
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

            if (config.SerialTarget == QEMUConfig.SerialTargetType.Stdio)
            {
                if (!structuredArgs.Contains("-serial")) structuredArgs += " -serial stdio";
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
