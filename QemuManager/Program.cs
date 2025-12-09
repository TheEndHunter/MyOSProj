using System.Diagnostics;

using Microsoft.Extensions.Configuration;

namespace QemuRunner
{
    public static class Program
    {
        private static Process? qemu = null;
        private static Process? lldb = null;
        static async Task<int> Main(string[] args)
        {
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

            QEMUConfig qemuConf = config.QemuConfigs!.Find(x => { return x.Architecture == architecture && x.Configuration == configuration; });

            if (qemuConf == null)
            {
                Console.WriteLine("No QEMU configuration found for the specified architecture and configuration.");
                return -1;
            }


            AppDomain.CurrentDomain.ProcessExit += (s, e) =>
            {
                qemu?.Kill(true);
                lldb?.Kill(true);
            };

            qemu = QEMU.StartProcess(qemuConf, Path.Combine(Dir, "OVMF", architecture, configuration), imagePath);
            lldb = LLDB.StartProcess(qemuConf);

            if (qemu == null)
            {
                Console.WriteLine("Failed to start QEMU process.");
                return -1;
            }

            qemu.Exited += OnQemuTerminate;
            lldb?.Exited += OnLLDBTerminate;

            if (!qemu.Start())
            {
                Console.WriteLine("Failed to start QEMU process.");
                return -1;
            }

            bool windowLoaded = false;
            while (!windowLoaded)
            {
                try
                {
                    if (qemu.MainWindowTitle.Length > 0)
                    {
                        windowLoaded = true;
                        break;
                    }
                }
                catch (Exception ex)
                {
                    continue;
                }
                finally
                {
                    qemu.Refresh();
                }
            }


            lldb?.Start();
            while (!QemuExitCalled && !LLDBExitCalled)
            {
                Thread.Yield();
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
    }
}

