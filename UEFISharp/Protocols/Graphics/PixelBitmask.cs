using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

[StructLayout(LayoutKind.Sequential)]
public struct PixelBitmask
{
    public uint RedMask;
    public uint GreenMask;
    public uint BlueMask;
    public uint ReservedMask;
}
