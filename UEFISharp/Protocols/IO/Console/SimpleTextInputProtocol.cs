using System.Runtime.InteropServices;

using EFI.Protocols.IO.Peripheral;

namespace EFI.Protocols.IO.Console;

public static partial class EFIConsts
{
    public static readonly Guid SimpleTextInputProtocolGuid =
        new(0x387477C1, 0x69C7, 0x11D2, 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B);
}

public unsafe delegate Status InputResetFunc(SimpleTextInputProtocol* self, bool extendedVerification);
public unsafe delegate Status InputReadKeyFunc(SimpleTextInputProtocol* self, InputKey* key);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SimpleTextInputProtocol
{
    public InputResetFunc Reset;
    public InputReadKeyFunc ReadKeyStroke;
    public Event WaitForKey;
}
