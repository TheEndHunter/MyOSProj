using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct CapsuleBlockDescriptor
{
    public ulong Length;
    public nint DataBlock; // or ContinuationPointer, unioned in native
}
