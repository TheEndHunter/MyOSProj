using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

public static partial class EFIConsts
{
    public static readonly Guid EdidDiscoveredProtocolGuid =
        new(0x1C0C34F6, 0xD380, 0x41FA, 0xA0, 0x49, 0x8A, 0xD0, 0x6C, 0x1A, 0x66, 0xAA);

    public static readonly Guid EdidActiveProtocolGuid =
        new(0xBD8C1056, 0x9F36, 0x44EC, 0x92, 0xA8, 0xA6, 0x33, 0x7F, 0x81, 0x79, 0x86);

    public static readonly Guid EdidOverrideProtocolGuid =
        new(0x48ecb431, 0xfb72, 0x45c0, 0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x04, 0x0b, 0xd5);

    public const byte EdidOverrideDontOverride = 0x01;
    public const byte EdidOverrideEnableHotPlug = 0x02;
}

public unsafe delegate Status EdidOverrideProtocolGetEdidFunc(
    EdidOverrideProtocol* self,
    nint childHandle,
    uint* attributes,
    nuint* edidSize,
    byte** edid);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct EdidDiscoveredProtocol
{
    public uint SizeOfEdid;
    public byte* Edid;
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct EdidActiveProtocol
{
    public uint SizeOfEdid;
    public byte* Edid;
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct EdidOverrideProtocol
{
    public EdidOverrideProtocolGetEdidFunc GetEdid;
}
