using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

public static partial class EFIConsts
{
    public static readonly Guid GraphicsOutputProtocol_GUID =
        new(0x9042a9de, 0x23dc, 0x4a38, 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a);
}

public unsafe delegate Status GraphicsOutputProtocolQueryMode(
    GraphicsOutputProtocol* self,
    uint modeNumber,
    nuint* sizeOfInfo,
    GraphicsOutputModeInformation** info);

public unsafe delegate Status GraphicsOutputProtocolSetMode(
    GraphicsOutputProtocol* self,
    uint modeNumber);

public unsafe delegate Status GraphicsOutputProtocolBlt(
    GraphicsOutputProtocol* self,
    GraphicsOutputBLTPixel* bltBuffer,
    GraphicsOutputBLTOperation bltOperation,
    nuint sourceX,
    nuint sourceY,
    nuint destinationX,
    nuint destinationY,
    nuint width,
    nuint height,
    nuint delta);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct GraphicsOutputProtocol
{
    public GraphicsOutputProtocolQueryMode QueryMode;
    public GraphicsOutputProtocolSetMode SetMode;
    public GraphicsOutputProtocolBlt Blt;
    public GraphicsOutputProtocolMode* Mode;
}
