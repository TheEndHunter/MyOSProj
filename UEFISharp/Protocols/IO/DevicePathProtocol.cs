using System;
using System.Runtime.InteropServices;

namespace EFI.Protocols.IO;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct DevicePathProtocol
{
    public byte Type;
    public byte SubType;
    public fixed byte Length[2];
}

public static partial class EFIConsts
{
    public static readonly Guid DevicePathProtocolGuid = new(0x09576E91, 0x6D3F, 0x11D2, 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B);
    public static readonly Guid FilePathDevicePathGuid = new(0x0424F782, 0x8A51, 0x4179, 0xBF, 0x1D, 0xF3, 0x3E, 0xA6, 0x0D, 0x83, 0x5C);
    public static readonly Guid MediaDevicePathGuid = new(0x0379473F, 0x9E9E, 0x485F, 0xA3, 0x9C, 0xD8, 0x7D, 0xE1, 0x67, 0x79, 0xAB);
}
