using System.Runtime.InteropServices;

namespace EFI;

// Adjust SizeConst after inspecting UEFI/MACAddress.h.
[StructLayout(LayoutKind.Explicit)]
public struct MACAddress
{
    [FieldOffset(0)]
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
    public byte[] Addr;

    [FieldOffset(0)] public uint A;
    [FieldOffset(4)] public uint B;
    [FieldOffset(8)] public uint C;
    [FieldOffset(12)] public uint D;
    [FieldOffset(16)] public uint E;
    [FieldOffset(20)] public uint F;
    [FieldOffset(24)] public uint G;
    [FieldOffset(28)] public uint H;
}