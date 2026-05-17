using System.Runtime.InteropServices;

using EFI;
using EFI.Protocols.IO.Peripheral;

namespace EF.Protocols.IO.PeripheralI;

public static partial class EFIConsts
{
    public static readonly Guid SimplePointerProtocolGuid =
        new(0x31878C87, 0x0B75, 0x11D5, 0x9A, 0x4F, 0x0, 0x90, 0x27, 0x3F, 0xC1, 0x4D);
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
