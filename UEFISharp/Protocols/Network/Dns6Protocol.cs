using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // DNS6 protocol GUID from UEFI spec
    public static readonly Guid Dns6ProtocolGuid = new(0xCA37BC1F, 0xA327, 0x4AE9, 0x82, 0x8A, 0x8C, 0x40, 0xD8, 0x50, 0x6A, 0x17);
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dns6ConfigData
{
    public nuint DnsServerListCount;
    public IPV6Address* DnsServerList;
    public bool UseDefaultSetting;
    public bool EnableDnsCache;
    public byte Protocol;
    public IPV6Address StationIp;
    public IPV6Address SubnetMask; // may be prefix length in real spec; simplified
    public ushort LocalPort;
    public uint RetryCount;
    public uint RetryInterval;
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dns6ModeData
{
    public Dns6ConfigData DnsConfigData;
    public uint DnsServerCount;
    public IPV6Address* DnsServerList;
    public uint DnsCacheCount;
    public void* DnsCacheList; // simplified
}

public unsafe delegate Status Dns6GetModeDataFunc(Dns6Protocol* self, Dns6ModeData* dnsModeData);
public unsafe delegate Status Dns6ConfigureFunc(Dns6Protocol* self, Dns6ConfigData* dnsConfigData);
public unsafe delegate Status Dns6HostNameToIpFunc(Dns6Protocol* self, char* hostName, IPV6Address** addrList);
public unsafe delegate Status Dns6IpToHostNameFunc(Dns6Protocol* self, IPV6Address* ip, char* hostNameBuf);
public unsafe delegate Status Dns6GeneralLookUpFunc(Dns6Protocol* self, void* query, void* result);
public unsafe delegate Status Dns6UpdateDnsCacheFunc(Dns6Protocol* self, void* entry);
public unsafe delegate Status Dns6PollFunc(Dns6Protocol* self);
public unsafe delegate Status Dns6CancelFunc(Dns6Protocol* self, void* token);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dns6Protocol
{
    public nuint Revision;
    public Dns6GetModeDataFunc GetModeData;
    public Dns6ConfigureFunc Configure;
    public Dns6HostNameToIpFunc HostNameToIp;
    public Dns6IpToHostNameFunc IpToHostName;
    public Dns6GeneralLookUpFunc GeneralLookUp;
    public Dns6UpdateDnsCacheFunc UpdateDnsCache;
    public Dns6PollFunc Poll;
    public Dns6CancelFunc Cancel;
}
