namespace ImageBuilder.Serialization
{
    using Microsoft.Extensions.Configuration;

    public readonly record struct DiscFormat
    {
        public DiscFormat(string format)
        {
            Format = format;
            Variant = null;
        }

        public DiscFormat(string format, string variant)
        {
            Format = format;
            Variant = variant;
        }

        public DiscFormat(IConfigurationSection conf)
        {
            Format = conf.GetValue<string>("Format")!;
            Variant = conf.GetValue<string>("Variant");
        }

        public string Format { get; init; }
        public string? Variant { get; init; }
    }
}
