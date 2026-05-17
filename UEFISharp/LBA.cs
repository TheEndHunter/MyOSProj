namespace EFI;

public readonly struct LBA
{
    public readonly ulong Value;

    public LBA(ulong value)
    {
        Value = value;
    }
}
