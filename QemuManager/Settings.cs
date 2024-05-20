using Microsoft.Extensions.Configuration;

namespace QemuManager
{
    public record struct Settings
    {
        public List<string>? Configurations;
        public List<string>? Architectures;
        public GitConfiguration? OVMFConfiguration;

        public Settings(IConfigurationRoot root) : this()
        {
            OVMFConfiguration = null;
            root.GetRequiredSection("Configurations").Bind(Configurations);
            root.GetRequiredSection("Architectures").Bind(Architectures);

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

