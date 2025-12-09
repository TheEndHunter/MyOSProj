namespace QemuRunner
{
    public record struct LLDBConfig(string Remote, uint Port, string WorkingSourceDirectory, string BinaryDir, string RelativeExecutableLocation, string RelativeSymbolLocation, string? AdditionalArgs)
    {
    }
}

