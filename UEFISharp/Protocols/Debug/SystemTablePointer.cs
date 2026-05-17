using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct EFI_SYSTEM_TABLE_POINTER
{
    public ulong Signature;
    public nint EfiSystemTableBase; // PhysicalAddress
    public uint Crc32;
}
