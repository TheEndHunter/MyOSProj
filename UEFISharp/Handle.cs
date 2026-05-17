namespace EFI;

public readonly struct Handle
{
    public readonly nint Value;

    public Handle(nint value)
    {
        Value = value;
    }
}
