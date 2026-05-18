namespace EFI.Protocols.Network;

public enum SimpleNetworkState : uint
{
    // Matches EFI_SIMPLE_NETWORK_STATE from UEFI spec
    Stopped = 0,
    Started = 1,
    Initialized = 2,
    MaxState = 3,
}

