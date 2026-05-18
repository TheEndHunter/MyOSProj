namespace EFI.Protocols.Network;

public enum Dhcp4Event : uint
{
    Dhcp4SendDiscover = 0x01,
    Dhcp4RcvdOffer = 0x02,
    Dhcp4SelectOffer = 0x03,
    Dhcp4SendRequest = 0x04,
    Dhcp4RcvdAck = 0x05,
    Dhcp4RcvdNak = 0x06,
    Dhcp4SendDecline = 0x07,
    Dhcp4BoundCompleted = 0x08,
    Dhcp4EnterRenewing = 0x09,
    Dhcp4EnterRebinding = 0x0A,
    Dhcp4AddressLost = 0x0B,
    Dhcp4Fail = 0x0C
}

