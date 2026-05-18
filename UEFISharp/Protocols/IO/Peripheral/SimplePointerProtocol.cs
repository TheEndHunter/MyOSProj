using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

public static partial class EFIConsts
{
    public static readonly Guid SimplePointerProtocolGuid =
        new(0x387477C3, 0x69C7, 0x11D2, 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B);
}

public unsafe delegate Status SimplePointerResetFunc(SimplePointerProtocol* self, bool extendedVerification);
public unsafe delegate Status SimplePointerGetStateFunc(SimplePointerProtocol* self, SimplePointerState* state);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SimplePointerProtocol
{
    public SimplePointerResetFunc Reset;
    public SimplePointerGetStateFunc GetState;
    public Event WaitForInput;
    public SimplePointerMode* Mode;
}