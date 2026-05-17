namespace EFI;

public readonly struct TPL
{
    public readonly nuint Value;
    public TPL(nuint value) => Value = value;
}

public static partial class EFIConsts
{
    public const nuint EFI_TPL_APPLICATION = 4;
    public const nuint EFI_TPL_CALLBACK = 8;
    public const nuint EFI_TPL_NOTIFY = 16;
    public const nuint EFI_TPL_HIGH_LEVEL = 31;
}