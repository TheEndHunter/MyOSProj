using Microsoft.Extensions.Configuration;

namespace QemuRunner
{
    public static class Program
    {
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
            QemuConfig qemuConf = config.QemuConfigs!.Find(x => { return x.Architecture == architecture && x.Configuration == configuration; });

            return QEMU.StartProcess(qemuConf, Path.Combine(Dir, "OVMF", architecture, configuration), imagePath);
        }
    }
}

