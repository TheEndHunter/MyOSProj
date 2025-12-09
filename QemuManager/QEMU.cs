namespace QemuRunner
{
    using System.Diagnostics;
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


        public static string FindPath(string qemuExecutableName)
        {
            string qemuExe = qemuExecutableName;
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

                string logName = Path.Combine(Directory.GetCurrentDirectory(), $"qemu_{DateTime.Now:dd_mm_yyyy-HH_mm_ss_ff}.log");
                using FileStream s = File.Create(logName);
                s.Flush(true);
                s.Close();
                s.Dispose();

                string qemuArguments = $"{config.AdditionalArgs} -serial file:{logName} -drive if=pflash,format=raw,readonly=on,file=\"{ovmfCodePath}\" -drive if=pflash,format=raw,file=\"{ovmfVarPath}\" {BuildDrives(imagePath)}";
                Console.WriteLine($"Starting Qemu With the Following Configurations:{Environment.NewLine}\tArch: {config.Architecture}");
                Console.WriteLine($"\tConfig: {config.Configuration}{Environment.NewLine}\tAdditonal Args: {config.AdditionalArgs}");
                Console.WriteLine($"\tOVMF_CODE path: {ovmfCodePath}{Environment.NewLine}\tOVMF_VARS path: {ovmfVarPath}{Environment.NewLine}");

                return new()
                {
                    StartInfo = new ProcessStartInfo(qemuPath, qemuArguments)
                    {
                        UseShellExecute = false,
                    },
                    EnableRaisingEvents = true,
                };
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to start QEMU process: {ex.Message}");
                return null;
            }
        }
    }
}
