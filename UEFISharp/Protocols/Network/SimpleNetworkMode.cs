using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct SimpleNetworkMode
{
    public uint State;
    public uint HwAddressSize;
    public fixed byte HwAddress[32];
    public uint MaxPacketSize;
    public uint ReceiveFilterSetting;
}

