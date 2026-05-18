using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;

public static partial class EFIConsts
{
    // PXE Base Code GUID from UEFI spec
    public static readonly Guid PxeBaseCodeProtocolGuid = new(0x03C4E603, 0xAC28, 0x11D3, 0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D);
}

// Placeholder PXE Base Code protocol struct if needed later
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct PxeBaseCodeProtocol
{
    public nuint Revision;
}
