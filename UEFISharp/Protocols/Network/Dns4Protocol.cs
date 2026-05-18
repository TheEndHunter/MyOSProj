using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // DNS4 protocol GUID from UEFI spec
    public static readonly Guid Dns4ProtocolGuid = new(0xAE3D28CC, 0xE05B, 0x4FA1, 0xA0, 0x11, 0x7E, 0xB5, 0x5A, 0x3F, 0x14, 0x01);
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dns4ConfigData
{
    public nuint DnsServerListCount;
    public IPV4Address* DnsServerList;
    public bool UseDefaultSetting;
    public bool EnableDnsCache;
    public byte Protocol;
    public IPV4Address StationIp;
    public IPV4Address SubnetMask;
    public ushort LocalPort;
    public uint RetryCount;
    public uint RetryInterval;
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dns4ModeData
{
    public Dns4ConfigData DnsConfigData;
    public uint DnsServerCount;
    public IPV4Address* DnsServerList;
    public uint DnsCacheCount;
    public void* DnsCacheList; // simplified
}

public unsafe delegate Status Dns4GetModeDataFunc(Dns4Protocol* self, Dns4ModeData* dnsModeData);
public unsafe delegate Status Dns4ConfigureFunc(Dns4Protocol* self, Dns4ConfigData* dnsConfigData);
public unsafe delegate Status Dns4HostNameToIpFunc(Dns4Protocol* self, char* hostName, IPV4Address** addrList);
public unsafe delegate Status Dns4IpToHostNameFunc(Dns4Protocol* self, IPV4Address* ip, char* hostNameBuf);
public unsafe delegate Status Dns4GeneralLookUpFunc(Dns4Protocol* self, void* query, void* result);
public unsafe delegate Status Dns4UpdateDnsCacheFunc(Dns4Protocol* self, void* entry);
public unsafe delegate Status Dns4PollFunc(Dns4Protocol* self);
public unsafe delegate Status Dns4CancelFunc(Dns4Protocol* self, void* token);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dns4Protocol
{
    public nuint Revision;
    public Dns4GetModeDataFunc GetModeData;
    public Dns4ConfigureFunc Configure;
    public Dns4HostNameToIpFunc HostNameToIp;
    public Dns4IpToHostNameFunc IpToHostName;
    public Dns4GeneralLookUpFunc GeneralLookUp;
    public Dns4UpdateDnsCacheFunc UpdateDnsCache;
    public Dns4PollFunc Poll;
    public Dns4CancelFunc Cancel;
}
