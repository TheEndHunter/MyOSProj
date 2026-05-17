using System.Runtime.InteropServices;

namespace EFI.Protocols.Graphics;

public static partial class EFIConsts
{
    public static readonly Guid EdidDiscoveredProtocolGuid =
        new(0x1c0c34f6, 0xd380, 0x41fa, 0xa0, 0x49, 0x8a, 0xd0, 0x6c, 0x1a, 0x66, 0xaa);

    public static readonly Guid EdidActiveProtocolGuid =
        new(0xbd8c1056, 0x9f36, 0x44ec, 0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86);

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
