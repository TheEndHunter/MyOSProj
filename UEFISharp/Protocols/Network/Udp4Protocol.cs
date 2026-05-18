using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // UDP4 protocol GUID from UEFI spec
    public static readonly Guid Udp4ProtocolGuid = new(0x3ad9df29, 0x4501, 0x478d, 0xb1, 0xf8, 0x7f, 0x7f, 0xe7, 0x0e, 0x50, 0xf3);
}

public unsafe delegate Status Udp4GetModeDataFunc(Udp4Protocol* self, Udp4ConfigData* udp4ConfigData, Ip4ModeData* ip4ModeData, ManagedNetworkConfigData* mnpConfigData, SimpleNetworkMode* snpModeData);
public unsafe delegate Status Udp4ConfigureFunc(Udp4Protocol* self, Udp4ConfigData* udpConfigData);
public unsafe delegate Status Udp4GroupsFunc(Udp4Protocol* self, IPV4Address* groupIp, bool join);
public unsafe delegate Status Udp4RoutesFunc(Udp4Protocol* self, Ip4RouteTable* route, bool add);
public unsafe delegate Status Udp4TransmitFunc(Udp4Protocol* self, void* token);
public unsafe delegate Status Udp4ReceiveFunc(Udp4Protocol* self, void* token);
public unsafe delegate Status Udp4CancelFunc(Udp4Protocol* self, void* token);
public unsafe delegate Status Udp4PollFunc(Udp4Protocol* self);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Udp4Protocol
{
    public nuint Revision;
    public Udp4GetModeDataFunc GetModeData;
    public Udp4ConfigureFunc Configure;
    public Udp4GroupsFunc Groups;
    public Udp4RoutesFunc Routes;
    public Udp4TransmitFunc Transmit;
    public Udp4ReceiveFunc Receive;
    public Udp4CancelFunc Cancel;
    public Udp4PollFunc Poll;
}
