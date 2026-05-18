using System.Runtime.InteropServices;
using EFI;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // IPv4 protocol GUID from UEFI spec
    public static readonly Guid Ip4ProtocolGuid = new(0x41D94CD2, 0x35B6, 0x455A, 0x82, 0x58, 0xD4, 0xE5, 0x13, 0x34, 0xAA, 0xDD);
}

// IPv4 protocol types from the UEFI spec (converted to C#)
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip4RouteTable
{
    public IPV4Address SubnetAddress;
    public IPV4Address SubnetMask;
    public IPV4Address GatewayAddress;
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip4ConfigData
{
    public byte DefaultProtocol;
    public bool AcceptAnyProtocol;
    public bool AcceptIcmpErrors;
    public bool AcceptBroadcast;
    public bool AcceptPromiscuous;
    public bool UseDefaultAddress;
    public IPV4Address StationAddress;
    public IPV4Address SubnetMask;
    public byte TypeOfService;
    public byte TimeToLive;
    public bool DoNotFragment;
    public bool RawData;
    public uint ReceiveTimeout;
    public uint TransmitTimeout;
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip4ModeData
{
    public bool IsStarted;
    public uint MaxPacketSize;
    public Ip4ConfigData ConfigData;
    public bool IsConfigured;
    public uint GroupCount;
    public IPV4Address* GroupTable; // pointer to group addresses
    public uint RouteCount;
    public Ip4RouteTable RouteTable; // single or pointer; use struct for now
    public uint IcmpTypeCount;
    public byte* IcmpTypeList; // simplified
}

// IPv4 protocol delegates using typed parameters
public unsafe delegate Status Ip4GetModeDataFunc(Ip4Protocol* self, Ip4ModeData* ip4ModeData);
public unsafe delegate Status Ip4ConfigureFunc(Ip4Protocol* self, Ip4ConfigData* ip4ConfigData);
public unsafe delegate Status Ip4GroupsFunc(Ip4Protocol* self, IPV4Address* groupIp, bool join);
public unsafe delegate Status Ip4RoutesFunc(Ip4Protocol* self, Ip4RouteTable* route, bool add);
public unsafe delegate Status Ip4TransmitFunc(Ip4Protocol* self, void* token);
public unsafe delegate Status Ip4ReceiveFunc(Ip4Protocol* self, void* token);
public unsafe delegate Status Ip4CancelFunc(Ip4Protocol* self, void* token);
public unsafe delegate Status Ip4PollFunc(Ip4Protocol* self);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Ip4Protocol
{
    public nuint Revision;
    public Ip4GetModeDataFunc GetModeData;
    public Ip4ConfigureFunc Configure;
    public Ip4GroupsFunc Groups;
    public Ip4RoutesFunc Routes;
    public Ip4TransmitFunc Transmit;
    public Ip4ReceiveFunc Receive;
    public Ip4CancelFunc Cancel;
    public Ip4PollFunc Poll;
}
