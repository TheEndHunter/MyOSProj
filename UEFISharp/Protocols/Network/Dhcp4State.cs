namespace EFI.Protocols.Network;

// DHCPv4 enums and packet type from UEFI spec (converted)
public enum Dhcp4State : uint
{
    Dhcp4Stopped = 0x0,
    Dhcp4Init = 0x1,
    Dhcp4Selecting = 0x2,
    Dhcp4Requesting = 0x3,
    Dhcp4Bound = 0x4,
    Dhcp4Renewing = 0x5,
    Dhcp4Rebinding = 0x6,
    Dhcp4InitReboot = 0x7,
    Dhcp4Rebooting = 0x8
}

