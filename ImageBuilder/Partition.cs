namespace ImageBuilder
{
    public struct Partition
    {
        public string Label { get; set; }
        public PartitionType Type { get; set; }
        public string SrcPath { get; set; }

        public string? DestPath { get; set; }
        public long Size { get; set; }
    }
}
