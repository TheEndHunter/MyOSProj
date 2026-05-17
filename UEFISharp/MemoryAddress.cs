namespace EFI;

public readonly struct PhysicalAddress
{
    public readonly nint Value;
    public PhysicalAddress(nint value) => Value = value;
}

public readonly struct VirtualAddress
{
    public readonly nint Value;
    public VirtualAddress(nint value) => Value = value;
}
