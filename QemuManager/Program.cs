namespace QemuManager
{
    using System.Diagnostics;

    internal class Program
    {
        static int Main(string[] args)
        {
            Console.Title = "Qemu Virtual Machine Starter Tool";

            string Dir = Path.GetFullPath(Directory.GetCurrentDirectory());

            string? architecture = null;
            string? configuration = null;
            string? imagePath = null;
            string? machine;

            if (!Directory.Exists(Path.Combine(Dir, "OVMF")))
            {
                Console.WriteLine("Could not find OVMF folder");
                Console.ReadKey();
                return -1;
            }

            int l = args.Length;
            if (l != 3)
            {
                args = new string[3];
                Console.WriteLine("Invalid amount of arguments specified (min/max of 3 arguments). switching to manual entry");

                while (string.IsNullOrEmpty(architecture) && string.IsNullOrWhiteSpace(architecture))
                {
                    Console.Clear();
                    Console.WriteLine("Please enter the architecture being used (Select from: x86,x64,ARM,ARM64)");
                    architecture = Console.ReadLine().ToLower();

                    switch (architecture)
                    {
                        case "x86":
                        case "x64":
                        case "arm":
                        case "arm64":
                            break;
                        default:
                            architecture = null;
                            break;
                    }
                }

                while (string.IsNullOrEmpty(configuration) && string.IsNullOrWhiteSpace(configuration))
                {
                    Console.Clear();
                    Console.WriteLine("Please enter the configuration being used(e.g. Debug, Release)");
                    configuration = Console.ReadLine();
                }

                while (string.IsNullOrEmpty(imagePath) && string.IsNullOrWhiteSpace(imagePath))
                {
                    Console.Clear();
                    Console.WriteLine($"Current Dir: {Directory.GetCurrentDirectory()}");
                    Console.WriteLine("Please enter path of the virtual disk being used(e.g. VirtualOS.vhdx)");
                    var test = Console.ReadLine();

                    test = Path.GetFullPath(test);

                    if (File.Exists(test))
                    {
                        imagePath = test;
                    }
                    else
                    {
                        Console.WriteLine("Invalid path specified");
                        Console.ReadKey();
                    }
                }

                Console.Clear();
            }
            else
            {
                architecture = args[0];
                configuration = args[1];
                imagePath = Path.Combine(Dir, args[2]);
            }

            string firmwareCodePath = Path.Combine(Dir, "OVMF", architecture, configuration, "OVMF_CODE.fd");
            string firmwareVarPath = Path.Combine(Dir, "OVMF", architecture, configuration, "OVMF_VARS.fd");

            string filename;

            switch (architecture)
            {
                case "x86":
                    filename = "qemu-system-i386";
                    machine = " -machine q35 -cpu qemu32";
                    break;
                case "x64":
                    filename = "qemu-system-x86_64";
                    machine = " -machine q35 -cpu qemu64";
                    break;
                case "arm":
                    filename = "qemu-system-arm";
                    machine = " -machine virt -cpu cortex-a15";
                    break;
                case "arm64":
                    filename = "qemu-system-aarch64";
                    machine = " -machine virt -cpu cortex-a710";
                    break;
                default:
                    Console.WriteLine("Unknown Architecture");
                    Console.ReadKey();
                    return -1;
            }

            string exePath = string.Empty;
            string qemuPath = string.Empty;

            if (Environment.OSVersion.Platform == PlatformID.Win32NT)
            {
                filename += ".exe";
                var path = Environment.GetEnvironmentVariable("Path");

                string[] paths = path.Split(";");

                foreach (string s in paths)
                {
                    if (File.Exists(Path.Combine(s, filename)))
                    {
                        qemuPath = s;
                        exePath = Path.Combine(s, filename);
                        break;
                    }
                }
                if (exePath == string.Empty)
                {
                    Console.WriteLine("Could not find Qemu in Path");
                    Console.ReadKey();
                    return -1;
                }
            }
            else
            {
                exePath = filename;
            }

            Process qemu = new();
            qemu.StartInfo.FileName = exePath;
            qemu.StartInfo.WorkingDirectory = qemuPath;
            qemu.StartInfo.Arguments = $"""{machine} -m 2048M -drive if=pflash,format=raw,unit=0,file={firmwareCodePath},readonly=on -drive if=pflash,format=raw,unit=1,file={firmwareVarPath} -drive file={imagePath} -net none""";
            qemu.StartInfo.UseShellExecute = false;
            qemu.StartInfo.CreateNoWindow = false;
            qemu.StartInfo.WindowStyle = ProcessWindowStyle.Normal;

            Console.WriteLine(qemu.StartInfo.Arguments);

            if (qemu.Start())
            {
                qemu.WaitForExit();
                if (qemu.ExitCode != 0)
                {
                    Console.WriteLine("Qemu exited with error code: " + qemu.ExitCode);
                    Console.ReadKey(true);
                }

                return qemu.ExitCode;
            }
            else
            {
                Console.WriteLine("Failed to start Process");
                Console.ReadKey();
                return -1;
            }
        }
    }
}
