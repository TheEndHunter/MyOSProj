namespace ImageBuilder.Serialization
{
    using Microsoft.Extensions.Configuration;

    public record struct ImageConfig
    {
        public string Name;
        public string Configuration;
        public string Architecture;
        public long ImageMinSizeBytes;
        public bool GenerateStartupScript;
        public List<Partition> Partitions;

        public ImageConfig(IConfigurationSection config, string baseImageSrcDir) : this()
        {
            Name = config.GetValue<string>("Name")!;
            Configuration = config.GetValue<string>("Configuration")!;
            Architecture = config.GetValue<string>("Architecture")!;
            ImageMinSizeBytes = config.GetValue<long>("ImageMinSizeBytes");
            GenerateStartupScript = config.GetValue<bool>("GenerateStartupScript");

            Partitions = [];
            foreach (var partition in config.GetRequiredSection("Partitions").GetChildren())
            {
                Partitions.Add(new Partition(partition, Architecture, Configuration, baseImageSrcDir));
            }
        }
    }
}
