using System.Runtime.InteropServices;

namespace EFI;

[StructLayout(LayoutKind.Explicit)]
public struct IPV4Address
{
    [FieldOffset(0)]
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public byte[] Addr;

    [FieldOffset(0)] public byte A;
    [FieldOffset(1)] public byte B;
    [FieldOffset(2)] public byte C;
    [FieldOffset(3)] public byte D;
}

[StructLayout(LayoutKind.Explicit)]
public struct IPV6Address
{
    [FieldOffset(0)]
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] Addr;

    [FieldOffset(0)] public uint A;
    [FieldOffset(4)] public uint B;
    [FieldOffset(8)] public uint C;
    [FieldOffset(12)] public uint D;
}

[StructLayout(LayoutKind.Explicit)]
public struct IPAddress
{
    [FieldOffset(0)]
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public uint[] Addr;

    [FieldOffset(0)] public IPV4Address v4;
    [FieldOffset(0)] public IPV6Address v6;
}
