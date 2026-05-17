using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

[StructLayout(LayoutKind.Sequential)]
public struct GraphicsOutputModeInformation
{
    public uint Version;
    public uint HorizontalResolution;
    public uint VerticalResolution;
    public GraphicsPixelFormat PixelFormat;
    public PixelBitmask PixelInformation;
    public uint PixelsPerScanLine;
}
