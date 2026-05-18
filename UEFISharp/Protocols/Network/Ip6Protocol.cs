using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // IPv6 protocol GUID from UEFI spec
    public static readonly Guid Ip6ProtocolGuid = new(0x2C8759D5, 0x5C2D, 0x66EF, 0x92, 0x5F, 0xB6, 0x6C, 0x10, 0x19, 0x57, 0xE2);
}

// IPv6 types from spec (converted to C#)
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip6RouteTable
{
    public IPV6Address Gateway;
    public IPV6Address Destination;
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip6ConfigData
{
    public IPV6Address DestinationAddress;
    public IPV6Address StationAddress;
    public IPV6Address GatewayAddress;
    public uint ReceiveTimeout;
    public uint TransmitTimeout;
    // Additional fields in the spec omitted for brevity; add as needed
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip6ModeData
{
    public bool IsStarted;
    public uint MaxPacketSize;
    public Ip6ConfigData ConfigData;
    public IPV6Address* GroupTable;
    public Ip6RouteTable* RouteTable;
    public uint RouteCount;
}

// IPv6 delegates
public unsafe delegate Status Ip6GetModeDataFunc(Ip6Protocol* self, Ip6ModeData* ip6ModeData);
public unsafe delegate Status Ip6ConfigureFunc(Ip6Protocol* self, Ip6ConfigData* ip6ConfigData);
public unsafe delegate Status Ip6GroupsFunc(Ip6Protocol* self, IPV6Address* groupAddr, bool join);
public unsafe delegate Status Ip6RoutesFunc(Ip6Protocol* self, Ip6RouteTable* route, bool add);
public unsafe delegate Status Ip6NeighborsFunc(Ip6Protocol* self, IPV6Address* neighbor);
public unsafe delegate Status Ip6TransmitFunc(Ip6Protocol* self, void* token);
public unsafe delegate Status Ip6ReceiveFunc(Ip6Protocol* self, void* token);
public unsafe delegate Status Ip6CancelFunc(Ip6Protocol* self, void* token);
public unsafe delegate Status Ip6PollFunc(Ip6Protocol* self);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip6Protocol
{
    public nuint Revision;
    public Ip6GetModeDataFunc GetModeData;
    public Ip6ConfigureFunc Configure;
    public Ip6GroupsFunc Groups;
    public Ip6RoutesFunc Routes;
    public Ip6NeighborsFunc Neighbors;
    public Ip6TransmitFunc Transmit;
    public Ip6ReceiveFunc Receive;
    public Ip6CancelFunc Cancel;
    public Ip6PollFunc Poll;
}
