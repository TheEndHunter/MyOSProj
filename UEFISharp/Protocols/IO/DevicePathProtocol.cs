using System.Runtime.InteropServices;

namespace EFI.Protocols.IO;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct DevicePathProtocol
{
    public byte Type;
    public byte SubType;
    public fixed byte Length[2];
}