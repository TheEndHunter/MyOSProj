using System;
using System.Runtime.InteropServices;

namespace EFI;

public static partial class EFIConsts
{
    public const nuint MemoryDescriptorVersion = 1;
}

[Flags]
public enum MemoryAttributes : ulong
{
    UC = 0x0000000000000001,
    WC = 0x0000000000000002,
    WT = 0x0000000000000004,
    WB = 0x0000000000000008,
    UCE = 0x0000000000000010,
    WP = 0x0000000000001000,
    RP = 0x0000000000002000,
    XP = 0x0000000000004000,
    NV = 0x0000000000008000,
    MoreReliable = 0x0000000000010000,
    RO = 0x0000000000020000,
    SP = 0x0000000000040000,
    CpuCrypto = 0x0000000000080000,
    Runtime = 0x8000000000000000,
    IsaValid = 0x4000000000000000,
    IsaMask = 0x0FFFF00000000000
}

[StructLayout(LayoutKind.Sequential)]
public struct MemoryDescriptor
{
    public uint Type;
    private uint Padding;
    public nint PhysicalStart;
    public nint VirtualStart;
    public ulong NumberOfPages;
    public MemoryAttributes Attribute;
}
