using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // Managed Network (MNP) GUID from spec
    public static readonly Guid ManagedNetworkProtocolGuid = new(0x7AB33A91, 0xACE5, 0x4326, 0xB5, 0x72, 0xE7, 0xEE, 0x33, 0xD3, 0x9F, 0x16);
}

public unsafe delegate Status MnpGetModeDataFunc(ManagedNetworkProtocol* self, ManagedNetworkConfigData* mnpConfig, SimpleNetworkMode* snpMode);
public unsafe delegate Status MnpConfigureFunc(ManagedNetworkProtocol* self, ManagedNetworkConfigData* configData);
public unsafe delegate Status MnpMcastIpToMacFunc(ManagedNetworkProtocol* self, byte* ipAddress, byte* macAddress);
public unsafe delegate Status MnpGroupsFunc(ManagedNetworkProtocol* self, byte* group, bool enable);
public unsafe delegate Status MnpTransmitFunc(ManagedNetworkProtocol* self, void* token);
public unsafe delegate Status MnpReceiveFunc(ManagedNetworkProtocol* self, void* token);
public unsafe delegate Status MnpCancelFunc(ManagedNetworkProtocol* self, void* token);
public unsafe delegate Status MnpPollFunc(ManagedNetworkProtocol* self);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct ManagedNetworkProtocol
{
    public nuint Revision;
    public MnpGetModeDataFunc GetModeData;
    public MnpConfigureFunc Configure;
    public MnpMcastIpToMacFunc McastIpToMac;
    public MnpGroupsFunc Groups;
    public MnpTransmitFunc Transmit;
    public MnpReceiveFunc Receive;
    public MnpCancelFunc Cancel;
    public MnpPollFunc Poll;
}

