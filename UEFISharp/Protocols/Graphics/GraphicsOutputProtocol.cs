using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

public static partial class EFIConsts
{
    public static readonly Guid GraphicsOutputProtocol_GUID =
        new(0x9042A9DE, 0x23DC, 0x4A38, 0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A);
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
    public nint QueryMode; // TODO: precise delegate signatures
    public nint SetMode; // TODO: precise delegate signatures
    public nint Blt; // TODO: precise delegate signatures
    public GraphicsOutputProtocolMode* Mode;
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct FrameBuffer
{
    public nuint FrameBufferBase;
    public nuint FrameBufferSize;
}
