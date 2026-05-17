using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DebugImageInfoNormal
{
    public uint ImageInfoType;
    public nint LoadedImageProtocolInstance; // LoadedImageProtocol*
    public Handle ImageHandle;
}
