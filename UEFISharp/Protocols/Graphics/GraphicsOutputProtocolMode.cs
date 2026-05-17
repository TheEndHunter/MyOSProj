using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct GraphicsOutputProtocolMode
{
    public uint MaxMode;
    public uint Mode;
    public GraphicsOutputModeInformation* Info;
    public nuint SizeOfInfo;
    public nint FrameBufferBase; // VOID_PTR
    public nuint FrameBufferSize;
}
