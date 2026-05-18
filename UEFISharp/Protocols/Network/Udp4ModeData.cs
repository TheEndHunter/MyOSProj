using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Udp4ModeData
{
    public bool IsStarted;
    public uint MaxPacketSize;
    public Udp4ConfigData ConfigData;
    public bool IsConfigured;
    public uint GroupCount;
    public IPV4Address* GroupTable;
    public uint RouteCount;
    public Ip4RouteTable* RouteTable;
}
