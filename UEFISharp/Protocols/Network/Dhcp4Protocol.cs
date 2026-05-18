using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // DHCPv4 protocol GUID from UEFI spec
    public static readonly Guid Dhcp4ProtocolGuid = new(0x8A219718, 0x4EF5, 0x4761, 0x91, 0xC8, 0xC0, 0xF0, 0x4B, 0xDA, 0x9E, 0x56);
}


public unsafe delegate Status Dhcp4GetModeDataFunc(Dhcp4Protocol* self, void* context, void* modeData);
public unsafe delegate Status Dhcp4ConfigureFunc(Dhcp4Protocol* self, Dhcp4ConfigData* configData);
public unsafe delegate Status Dhcp4StartFunc(Dhcp4Protocol* self, void* completionEvent);
public unsafe delegate Status Dhcp4RenewRebindFunc(Dhcp4Protocol* self, void* completionEvent);
public unsafe delegate Status Dhcp4ReleaseFunc(Dhcp4Protocol* self);
public unsafe delegate Status Dhcp4StopFunc(Dhcp4Protocol* self);
public unsafe delegate Status Dhcp4BuildFunc(Dhcp4Protocol* self, void* packet);
public unsafe delegate Status Dhcp4TransmitReceiveFunc(Dhcp4Protocol* self, void* transmitPacket, void** receivePacket);
public unsafe delegate Status Dhcp4ParseFunc(Dhcp4Protocol* self, void* packet);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dhcp4Protocol
{
    public nuint Revision;
    public Dhcp4GetModeDataFunc GetModeData;
    public Dhcp4ConfigureFunc Configure;
    public Dhcp4StartFunc Start;
    public Dhcp4RenewRebindFunc RenewRebind;
    public Dhcp4ReleaseFunc Release;
    public Dhcp4StopFunc Stop;
    public Dhcp4BuildFunc Build;
    public Dhcp4TransmitReceiveFunc TransmitReceive;
    public Dhcp4ParseFunc Parse;
}

