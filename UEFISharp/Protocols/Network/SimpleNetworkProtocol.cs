using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // Simple Network Protocol GUID from UEFI spec
    public static readonly Guid SimpleNetworkProtocolGuid = new(0xA19832B9, 0xAC25, 0x11D3, 0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D);

    // HTTP Boot callback GUID is declared in HttpBootCallbackProtocolGuid.cs
    // DHCPv4 protocol GUID is declared in Dhcp4Protocol.cs
    // HTTP Service Binding GUID is declared in HttpProtocol.cs
    // ARP protocol GUID is declared in ArpProtocol.cs
    // Managed Network (MNP) GUID is declared in ManagedNetworkProtocol.cs
    // DHCPv4 protocol GUID (already added above as Dhcp4ProtocolGuid)

    // PXE Base Code GUID is declared in PxeBaseCodeProtocol.cs (not present yet)
}

public unsafe delegate Status SnpResetFunc(SimpleNetworkProtocol* self, bool extendedVerification);
public unsafe delegate Status SnpStartFunc(SimpleNetworkProtocol* self);
public unsafe delegate Status SnpStopFunc(SimpleNetworkProtocol* self);
public unsafe delegate Status SnpReceiveFunc(SimpleNetworkProtocol* self, nuint* bufferSize, void* buffer);
public unsafe delegate Status SnpTransmitFunc(SimpleNetworkProtocol* self, nuint* bufferSize, void* buffer);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct SimpleNetworkProtocol
{
    public nuint Revision;
    public SimpleNetworkMode* Mode;
    public SnpResetFunc Reset;
    public SnpStartFunc Start;
    public SnpStopFunc Stop;
    public SnpReceiveFunc Receive;
    public SnpTransmitFunc Transmit;
    public Event WaitForPacket;
}

