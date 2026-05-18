using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Udp4ConfigData
{
    public bool AcceptBroadcast;
    public bool AcceptPromiscuous;
    public bool AcceptAnyPort;
    public bool AllowDuplicatePort;
    public byte TypeOfService;
    public byte TimeToLive;
    public bool DoNotFragment;
    public uint ReceiveTimeout;
    public uint TransmitTimeout;
    public bool UseDefaultAddress;
    public IPV4Address StationAddress;
    public IPV4Address SubnetMask;
    public ushort StationPort;
    public IPV4Address RemoteAddress;
    public ushort RemotePort;
}
