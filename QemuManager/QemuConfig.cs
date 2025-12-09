namespace QemuRunner
{
    public record struct QEMUConfig(string Architecture, string Configuration, string Name, string? AdditionalArgs, LLDBConfig? LLDBConfig)
    {
    }
}

