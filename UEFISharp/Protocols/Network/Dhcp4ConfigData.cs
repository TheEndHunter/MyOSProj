using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dhcp4ConfigData
{
    public uint DiscoverTryCount;
    public uint* DiscoverTimeout;
    public uint RequestTryCount;
    public uint* RequestTimeout;
    public IPV4Address ClientAddress;
    public delegate* unmanaged[Cdecl]<Dhcp4Protocol*, void*, Dhcp4State, Dhcp4Event, Dhcp4Packet*, Dhcp4Packet**, Status> Dhcp4CallbackPtr;
    public void* CallbackContext;
    public uint OptionCount;
    public Dhcp4PacketOption** OptionList;
}

