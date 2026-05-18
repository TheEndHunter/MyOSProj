using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

// Minimal Dhcp4Packet structure: size/length and pointer to packet buffer.
// Full DHCPv4 packet and related structs from the UEFI spec
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dhcp4Header
{
    public byte OpCode;
    public byte HwType;
    public byte HwAddrLen;
    public byte Hops;
    public uint Xid;
    public ushort Seconds;
    public ushort Reserved;
    public IPV4Address ClientAddr;
    public IPV4Address YourAddr;
    public IPV4Address ServerAddr;
    public IPV4Address GatewayAddr;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] ClientHwAddr;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
    public byte[] ServerName; // CHAR8[64]
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
    public byte[] BootFileName; // CHAR8[128]
}

