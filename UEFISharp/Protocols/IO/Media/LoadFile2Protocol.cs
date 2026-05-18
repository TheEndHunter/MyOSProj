using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

public static partial class EFIConsts
{
    public static readonly Guid EFI_LOAD_FILE2_PROTOCOL_GUID = new(0x4006c0c1, 0xfcb3, 0x403e, 0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d);
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct EFI_LOAD_FILE2_PROTOCOL
{
    public EFI_LOAD_FILE LoadFile;
}
