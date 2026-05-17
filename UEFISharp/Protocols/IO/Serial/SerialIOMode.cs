using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Serial;

[StructLayout(LayoutKind.Sequential)]
public struct SerialIOMode
{
    public uint ControlMask;
    public uint Timeout;
    public ulong BaudRate;
    public uint ReceiveFifoDepth;
    public uint DataBits;
    public uint Parity;
    public uint StopBits;
}
