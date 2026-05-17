using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

public static partial class EFIConsts
{
    public static readonly Guid MemoryRangeCapsuleGuid =
        new(0x00DE9F0EC, 0x88B6, 0x428F, 0x97, 0x7A, 0x25, 0x8F, 0x1D, 0x0E, 0x5E, 0x72);
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryRange
{
    public nint Address;
    public ulong Length;
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryRangeCapsule
{
    public CapsuleHeader Header;
    public uint OsRequestedMemoryType;
    public ulong NumberOfMemoryRanges;
    // Followed by MemoryRange[] MemoryRanges
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryRangeCapsuleResult
{
    public ulong FirmwareMemoryRequirement;
    public ulong NumberOfMemoryRanges;
}
