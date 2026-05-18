using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

// ARP protocol delegates and related structures
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct ArpConfigData
{
    public ushort SwAddressType;
    public byte SwAddressLength;
    public void* StationAddress;
    public uint EntryTimeOut;
    public uint RetryCount;
    public uint RetryTimeOut;
}
