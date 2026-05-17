using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct AbsolutePointerMode
{
    public uint AbsoluteMinX;
    public uint AbsoluteMinY;
    public uint AbsoluteMinZ;
    public uint AbsoluteMaxX;
    public uint AbsoluteMaxY;
    public uint AbsoluteMaxZ;
    public uint Attributes;
}
