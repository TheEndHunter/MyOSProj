namespace ImageBuilder.Serialization
{
    using Microsoft.Extensions.Configuration;

    public record struct ImageBuilderConfigs
    {
        public List<string> Configurations;
        public List<string> Architectures;

        public string ImageBaseName;

        public string BaseOutputDir;

        public string BaseImageSourceDir;

        public List<ImageConfig> ImageConfigs;

        public List<DiscFormat> DiscFormats;

        public ImageBuilderConfigs(IConfigurationRoot root) : this()
        {
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
            }).Select(x => x.Value!).ToList();


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
            }).Select(x => x.Value!).ToList();


            var section = root.GetRequiredSection("ImageBuilderConfigs");

            ImageBaseName = section["ImageBaseName"] ?? throw new ArgumentNullException(nameof(ImageBaseName));
            BaseOutputDir = section["BaseOutputDir"] ?? throw new ArgumentNullException(nameof(BaseOutputDir));
            BaseImageSourceDir = section["BaseImageSourceDir"] ?? throw new ArgumentNullException(nameof(BaseImageSourceDir));
            BaseOutputDir = Path.GetFullPath(BaseOutputDir);
            BaseImageSourceDir = Path.GetFullPath(BaseImageSourceDir);


            DiscFormats = [];

            foreach (var format in section.GetRequiredSection("DiscFormats").GetChildren())
            {
                DiscFormats.Add(new DiscFormat(format));
            }


            ImageConfigs = [];

            foreach (var config in section.GetRequiredSection("ImageConfigs").GetChildren())
            {
                ImageConfigs.Add(new ImageConfig(config, BaseImageSourceDir));
            }

        }
    }
}
