namespace QemuRunner
{
    public record struct QemuConfig(string Architecture, string Configuration, string Name, string? AdditionalArgs)
    {
    }
}

