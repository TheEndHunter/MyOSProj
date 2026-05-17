using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

public static partial class EFIConsts
{
    public static readonly Guid DebugImageInfoTableGuid =
        new(0x49152E77, 0x1ADA, 0x4764, 0xB7, 0xA2, 0x7A, 0xFE, 0xFE, 0xD9, 0x5E, 0x8B);

    public const byte DebugImageInfoUpdateInProgress = 0x01;
    public const byte DebugImageInfoTableModified = 0x02;
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DebugImageInfoTableHeader
{
    public volatile uint UpdateStatus;
    public uint TableSize;
    public DebugImageInfo* DebugImageInfoTable;
}
