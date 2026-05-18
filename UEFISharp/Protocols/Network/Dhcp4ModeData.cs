using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

// DHCP mode data (related definitions)
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dhcp4ModeData
{
    public Dhcp4State State;
    public Dhcp4ConfigData ConfigData;
    public IPV4Address ClientAddress;
    public MACAddress ClientMacAddress;
    public IPV4Address ServerAddress;
    public IPV4Address RouterAddress;
    public IPV4Address SubnetMask;
    public uint LeaseTime;
    public Dhcp4Packet* ReplyPacket;
}

