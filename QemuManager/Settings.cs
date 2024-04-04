using Microsoft.Extensions.Configuration;

namespace QemuManager
{
    public struct Settings
    {
        public List<string> Configurations;
        public List<string> Architectures;
        public GitConfiguration? OVMFConfiguration;

        public Settings(IConfigurationRoot root) : this()
        {
            root.GetRequiredSection("Configurations").Bind(Configurations);
            root.GetRequiredSection("Architectures").Bind(Architectures);

            var ovmf = root.GetRequiredSection("OVMFConfig");

            OVMFConfiguration = new GitConfiguration()
            {
                Author = ovmf["Author"],
                Repo = ovmf["Repo"],
                OVMFBinPath = ovmf["OVMFBinPath"]
            };

        }
    }
}

