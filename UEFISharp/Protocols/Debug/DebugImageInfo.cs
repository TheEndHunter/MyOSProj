using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DebugImageInfo
{
    public uint* ImageInfoType;
    public DebugImageInfoNormal* NormalImage;
}
