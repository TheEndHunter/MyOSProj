using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

public static partial class EFIConsts
{
    public static readonly Guid AbsolutePointerProtocolGuid =
        new(0x8D59D32B, 0xC655, 0x4AE9, 0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43);
}

public unsafe delegate Status AbsolutePointerResetFunc(AbsolutePointerProtocol* self, bool extendedVerification);
public unsafe delegate Status AbsolutePointerGetStateFunc(AbsolutePointerProtocol* self, AbsolutePointerState* state);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct AbsolutePointerProtocol
{
    public AbsolutePointerResetFunc Reset;
    public AbsolutePointerGetStateFunc GetState;
    public Event WaitForInput;
    public AbsolutePointerMode* Mode;
}