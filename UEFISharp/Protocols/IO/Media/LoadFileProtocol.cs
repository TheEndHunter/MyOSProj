using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

public static partial class EFIConsts
{
    public static readonly Guid LoadFileProtocolGuid =
        new(0x56EC3091, 0x954C, 0x11d2, 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b);
}

public unsafe delegate Status EFI_LOAD_FILE(void* self, void* filePath, bool bootPolicy, nuint* bufferSize, void* buffer);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct EFI_LOAD_FILE_PROTOCOL
{
    public EFI_LOAD_FILE LoadFile;
}

// Align with UEFI spec typedef naming used elsewhere in the project
public unsafe delegate Status LoadFileFunc(EFI_LOAD_FILE_PROTOCOL* self, DevicePathProtocol* filePath, bool bootPolicy, nuint* bufferSize, void* buffer);
