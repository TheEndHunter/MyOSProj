namespace ImageBuilder
{
    public record struct Partition(string Label, PartitionType Type, string SrcPath, string? DestPath, long Size);
}
