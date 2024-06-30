using Microsoft.Extensions.Configuration;

namespace QemuRunner
{

    public record struct Settings
    {
        public List<string> Configurations;
        public List<string> Architectures;
        public List<QemuConfig> QemuConfigs;
        public GitConfiguration? OVMFConfiguration;

        public Settings(IConfigurationRoot root) : this()
        {
            OVMFConfiguration = null;
            var c = root.GetRequiredSection("Configurations");

            Configurations = c.AsEnumerable().Where(x =>
            {
                if (string.IsNullOrEmpty(x.Value))
                {
                    return false;
                }

                if (string.IsNullOrWhiteSpace(x.Value))
                {
                    return false;
                }
                return true;
            }).Select(x => x.Value!.ToLower()).ToList();


            var a = root.GetRequiredSection("Architectures");

            Architectures = a.AsEnumerable().Where(x =>
            {
                if (string.IsNullOrEmpty(x.Value))
                {
                    return false;
                }

                if (string.IsNullOrWhiteSpace(x.Value))
                {
                    return false;
                }
                return true;
            }).Select(x => x.Value!.ToLower()).ToList();

            var qc = root.GetRequiredSection("QemuConfig");

            QemuConfigs = qc.Get<List<QemuConfig>>() ?? [];

            int count = QemuConfigs.Count;

            if (count < 1)
            {
                throw new InvalidOperationException("No QemuConfigs found in configuration file.");
            }

            for (int i = 0; i < count; i++)
            {
                var qemuConfig = QemuConfigs[i];
                qemuConfig.Architecture = qemuConfig.Architecture.ToLower();
                qemuConfig.Configuration = qemuConfig.Configuration.ToLower();
                QemuConfigs[i] = qemuConfig;
            }

            var ovmf = root.GetRequiredSection("OVMFConfig");

            if (ovmf != null)
            {
                OVMFConfiguration = new GitConfiguration()
                {
                    Author = ovmf["Author"] ?? string.Empty,
                    Repo = ovmf["Repo"] ?? string.Empty,
                    OVMFBinPath = ovmf["OVMFBinPath"] ?? string.Empty,
                    Branch = ovmf["Branch"] ?? "main",
                };
            }
        }
    }
}

