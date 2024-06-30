namespace QemuRunner
{
    using System.Diagnostics;
    using System.Text;

    internal static class QEMU
    {
        internal static string BuildDrives(string directory)
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


        internal static string FindPath(string qemuExecutableName)
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

        private static Process? qemuProcess = null;
        internal static int StartProcess(QemuConfig config, string ovmfPath, string imagePath)
        {
            try
            {
                AppDomain.CurrentDomain.ProcessExit += TerminateQemuProcess;

                string qemuPath = QEMU.FindPath(config.Name);

                if (string.IsNullOrEmpty(qemuPath))
                {
                    Console.WriteLine("QEMU executable not found in PATH.");
                    return -1;
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

                string qemuArguments = $"{config.AdditionalArgs} -drive if=pflash,format=raw,readonly=on,file=\"{ovmfCodePath}\" -drive if=pflash,format=raw,file=\"{ovmfVarPath}\" {BuildDrives(imagePath)}";

                using (qemuProcess = new())
                {
                    qemuProcess.StartInfo.FileName = qemuPath;
                    qemuProcess.StartInfo.Arguments = qemuArguments;
                    qemuProcess.StartInfo.UseShellExecute = false;
                    qemuProcess.StartInfo.RedirectStandardOutput = false;
                    qemuProcess.StartInfo.RedirectStandardError = false;

                    Console.WriteLine($"Starting Qemu With the Following Configurations:{Environment.NewLine}\tArch: {config.Architecture}");
                    Console.WriteLine($"\tConfig: {config.Configuration}{Environment.NewLine}\tAdditonal Args: {config.AdditionalArgs}");
                    Console.WriteLine($"\tOVMF_CODE path: {ovmfCodePath}{Environment.NewLine}\tOVMF_VARS path: {ovmfVarPath}{Environment.NewLine}");

                    qemuProcess.Start();

                    qemuProcess.WaitForExit();

                    int exitCode = qemuProcess.ExitCode;

                    // Clear the reference after the process exits
                    qemuProcess = null;

                    return exitCode;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to start QEMU process: {ex.Message}");
                return -1;
            }
        }
        private static void TerminateQemuProcess(object? sender, EventArgs e)
        {
            if (qemuProcess != null && !qemuProcess.HasExited)
            {
                qemuProcess.Kill();
            }
        }
    }
}
