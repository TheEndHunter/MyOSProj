using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dhcp4Packet
{
    public uint Size;
    public uint Length;
    public Dhcp4Header Dhcp4; // Header with fixed-size fields
    // Option[] follows in memory after the header; handled as pointer when needed
}

