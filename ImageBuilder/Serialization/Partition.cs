namespace ImageBuilder.Serialization
{
    using Microsoft.Extensions.Configuration;

    public record struct Partition
    {
        public string Label;
        public long MinSizeBytes;
        public Guid PartitionTypeGUID;
        public string FileFormat;
        public string SourceDir;
        public long AttributeFlags;

        public Partition(IConfigurationSection partition, string architecture, string configuration, string baseImageSrcDir)
        {
            Label = partition.GetValue<string>("Label")!;
            MinSizeBytes = partition.GetValue<long>("MinSizeBytes")!;
            PartitionTypeGUID = partition.GetValue<Guid>("PartitionTypeGUID")!;
            FileFormat = partition.GetValue<string>("FileFormat")!;
            SourceDir = partition.GetValue<string>("SourceDir")!;
            AttributeFlags = partition.GetValue<long>("AttributeFlags")!;
            SourceDir = Path.GetFullPath(Path.Combine(baseImageSrcDir, architecture, configuration, SourceDir));
        }
    }
}
