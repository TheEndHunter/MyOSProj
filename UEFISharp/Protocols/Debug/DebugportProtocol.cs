using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

public static partial class EFIConsts
{
    public static readonly Guid DebugportProtocolGuid =
        new(0xEBA4E8D2, 0x3858, 0x41EC, 0xA2, 0x81, 0x26, 0x47, 0xBA, 0x96, 0x60, 0xD0);

    public static readonly Guid DevicePathMessagingDebugportGuid = DebugportProtocolGuid;
    public static readonly Guid DebugportVariableGuid = DebugportProtocolGuid;

    public const string DebugportVariableName = "DEBUGPORT";
}

public unsafe delegate Status DebugportResetFunc(DebugportProtocol* self);

public unsafe delegate Status DebugportWriteFunc(
    DebugportProtocol* self,
    uint timeout,
    nuint* bufferSize,
    void* buffer);

public unsafe delegate Status DebugportReadFunc(
    DebugportProtocol* self,
    uint timeout,
    nuint* bufferSize,
    void* buffer);

public unsafe delegate Status DebugportPollFunc(DebugportProtocol* self);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DebugportProtocol
{
    public DebugportResetFunc Reset;
    public DebugportWriteFunc Write;
    public DebugportReadFunc Read;
    public DebugportPollFunc Poll;
}
