using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // ARP protocol GUID from UEFI spec
    public static readonly Guid ArpProtocolGuid = new(0xF4B427BB, 0xBA21, 0x4F16, 0xBC, 0x4E, 0x43, 0xE4, 0x16, 0xAB, 0x61, 0x9C);
}

public unsafe delegate Status ArpConfigureFunc(ArpProtocol* self, ArpConfigData* configData);
public unsafe delegate Status ArpAddFunc(ArpProtocol* self, bool denyFlag, void* targetSwAddress, void* targetHwAddress, uint timeoutValue, bool overwrite);
public unsafe delegate Status ArpFindFunc(ArpProtocol* self, void* targetSwAddress, void** targetHwAddresses, uint* count);
public unsafe delegate Status ArpDeleteFunc(ArpProtocol* self, void* targetSwAddress, void* targetHwAddress);
public unsafe delegate Status ArpFlushFunc(ArpProtocol* self);
public unsafe delegate Status ArpRequestFunc(ArpProtocol* self, void* targetSwAddress, uint timeout, void* serviceTag);
public unsafe delegate Status ArpCancelFunc(ArpProtocol* self, void* serviceTag);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct ArpProtocol
{
    public nuint Revision;
    public ArpConfigureFunc Configure;
    public ArpAddFunc Add;
    public ArpFindFunc Find;
    public ArpDeleteFunc Delete;
    public ArpFlushFunc Flush;
    public ArpRequestFunc Request;
    public ArpCancelFunc Cancel;
}
