using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct CapsuleTable
{
    public uint CapsuleArrayNumber;
    public void** CapsulePtr;
}
