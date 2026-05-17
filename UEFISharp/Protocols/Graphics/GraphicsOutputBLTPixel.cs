using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

[StructLayout(LayoutKind.Sequential)]
public struct GraphicsOutputBLTPixel
{
    public byte Blue;
    public byte Green;
    public byte Red;
    public byte Alpha;
}
