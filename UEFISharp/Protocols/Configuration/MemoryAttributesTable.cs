using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

public static partial class EFIConsts
{
    public static readonly Guid MemoryAttributesTableGuid =
        new(0xDCFA911D, 0x26EB, 0x469F, 0xA2, 0x20, 0x38, 0xB7, 0xDC, 0x46, 0x12, 0x20);

    public const byte MemoryAttributesFlagsRtForwardControlFlowGuard = 0x1;
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryAttributesTable
{
    public uint Version;
    public uint NumberOfEntries;
    public uint DescriptorSize;
    public uint Flags;
    // Followed by MemoryDescriptor entries
}
