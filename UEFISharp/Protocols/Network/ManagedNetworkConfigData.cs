using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

// Managed Network (MNP) protocol delegates and structures (simplified)
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct ManagedNetworkConfigData
{
    public uint ReceivedQueueTimeoutValue;
    public uint TransmitQueueTimeoutValue;
    public uint MnpModeFlags;
    // ...more fields omitted for brevity; extend per spec as needed
}

