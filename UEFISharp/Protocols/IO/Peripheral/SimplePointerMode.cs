using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct SimplePointerMode
{
    public uint ResolutionX;
    public uint ResolutionY;
    public uint ResolutionZ;
    public bool LeftButton;
    public bool RightButton;
}
