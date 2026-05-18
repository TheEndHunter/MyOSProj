using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct Dhcp4PacketOption
{
    public byte OptionType;
    public byte Length;
    public void* Data;
}

