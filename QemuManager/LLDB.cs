namespace QemuRunner
{
    using System.Diagnostics;

    public static class LLDB
    {
        private static readonly string LLDBENV = "LLDB_USE_NATIVE_PDB_READER";
        private static bool GetEnvironmentVariable(string variable, out string? value)
        {
            value = null;

            string? envValue = Environment.GetEnvironmentVariable(variable, EnvironmentVariableTarget.Process);
            if (string.IsNullOrEmpty(envValue))
            {
                envValue = Environment.GetEnvironmentVariable(variable, EnvironmentVariableTarget.User);

                if (string.IsNullOrEmpty(envValue))
                {
                    envValue = Environment.GetEnvironmentVariable(variable, EnvironmentVariableTarget.Machine);

                    if (string.IsNullOrEmpty(envValue))
                    {
                        return false;
                    }
                }
            }
            value = envValue;
            return true;
        }
        public static string FindPath(string lldbExecutableName)
        {
            string qemuExe = lldbExecutableName;
            /*Append the correct extension based on the platform*/
            switch (Environment.OSVersion.Platform)
            {
                case PlatformID.Win32S:
                case PlatformID.Win32Windows:
                case PlatformID.Win32NT:
                case PlatformID.WinCE:
                    qemuExe += ".exe";
                    break;
                case PlatformID.Xbox:
                    qemuExe += ".xex";
                    break;
                case PlatformID.MacOSX:
                case PlatformID.Unix:
                case PlatformID.Other:
                    break;
            }

            var paths = Environment.GetEnvironmentVariable("PATH");
            foreach (var path in paths.Split(Path.PathSeparator))
            {
                var fullPath = Path.Combine(path, qemuExe);

                if (File.Exists(fullPath))
                {
                    return fullPath;
                }
            }
            return string.Empty;
        }

        public static Process? StartProcess(QEMUConfig qemuConf)
        {
            if (!qemuConf.LLDBConfig.HasValue)
            {
                Console.WriteLine("No LLDB configuration found.");
                return null;
            }

            try
            {
                LLDBConfig config = qemuConf.LLDBConfig.Value;
                string lldbPath = FindPath("lldb");

                if (string.IsNullOrEmpty(lldbPath))
                {
                    Console.WriteLine("QEMU executable not found in PATH.");
                    return null;
                }
                string fullWorkingPath = Path.GetFullPath(config.WorkingSourceDirectory);
                string fullBinDir = Path.GetFullPath(config.BinaryDir, fullWorkingPath);
                string fullBinaryPath = Path.GetFullPath(config.RelativeExecutableLocation, fullBinDir);
                string fullSymbolPath = Path.GetFullPath(config.RelativeSymbolLocation, fullBinDir);

                string? arch = qemuConf.Architecture.ToLower() switch
                {
                    "x64" => "x86_64",
                    "arm64" => "aarch64",
                    "arm" => "arm",
                    "x86" => "i386",
                    _ => null
                };

                string lldbArgs = $"-e {config.AdditionalArgs ?? ""} -o \"target create {fullBinaryPath} --no-dependents --symfile {fullSymbolPath} {(arch is null ? string.Empty : "--arch " + arch)}\" -o  \"gdb-remote {config.Remote}:{config.Port}\"";
                Console.WriteLine($"Starting LLDB With the Following Configurations:{Environment.NewLine}\tArch: {qemuConf.Architecture}");
                Console.WriteLine($"\tConfig: {lldbArgs}");

                if (!GetEnvironmentVariable(LLDBENV, out string? str) || int.Parse(str!) != 1)
                {
                    Environment.SetEnvironmentVariable(LLDBENV, "1", EnvironmentVariableTarget.Process);
                }

                Process _ldb = new()
                {
                    StartInfo = new ProcessStartInfo(lldbPath, lldbArgs)
                    {
                        WorkingDirectory = fullWorkingPath,
                        UseShellExecute = true,
                        CreateNoWindow = false,
                    },
                    EnableRaisingEvents = true,
                };

                return _ldb;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error starting LLDB: {ex.Message}");
                return null;
            }
        }
    }
}
