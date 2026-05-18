using System.Runtime.InteropServices;

using EFI.Protocols.IO.Media;

namespace EFI;

public static partial class EFIConsts
{
    public static readonly Guid SimpleFileSystemProtocol_GUID = new(0x0964e5b2, 0x6459, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b);
    public const uint SimpleFileSystemProtocol_REVISION = 0x00010000;
}

public unsafe delegate Status SimpleFileSystemProtocolOpenVolume(SimpleFileSystemProtocol* self, FileProtocol** root);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct SimpleFileSystemProtocol
{
    public ulong Revision;
    public SimpleFileSystemProtocolOpenVolume OpenVolume;
}
