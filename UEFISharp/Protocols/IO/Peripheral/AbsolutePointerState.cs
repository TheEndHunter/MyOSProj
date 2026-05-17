using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct AbsolutePointerState
{
    public uint CurrentX;
    public uint CurrentY;
    public uint CurrentZ;
    public uint ActiveButtons;
}
