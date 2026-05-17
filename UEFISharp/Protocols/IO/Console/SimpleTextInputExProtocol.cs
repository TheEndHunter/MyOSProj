using System.Runtime.InteropServices;

using EFI.Protocols.IO.Peripheral;

namespace EFI.Protocols.IO.Console;

public static partial class EFIConsts
{
    public static readonly Guid SimpleTextInputExProtocolGuid =
        new(0xDD9E7534, 0x7762, 0x4698, 0x8C, 0x14, 0xF5, 0x85, 0x17, 0xA6, 0x25, 0xAA);
}

public unsafe delegate Status InputResetExFunc(SimpleTextInputExProtocol* self, bool extendedVerification);
public unsafe delegate Status InputReadKeyExFunc(SimpleTextInputExProtocol* self, KeyData* keyData);
public unsafe delegate Status SetStateFunc(SimpleTextInputExProtocol* self, KeyToggleState* keyToggleState);
public unsafe delegate Status KeyNotifyFunc(KeyData* keyData);
public unsafe delegate Status RegisterKeyStrokeNotifyFunc(SimpleTextInputExProtocol* self, KeyData* keyData, KeyNotifyFunc keyNotificationFunction, void** notifyHandle);
public unsafe delegate Status UnregisterKeyStrokeNotifyFunc(SimpleTextInputExProtocol* self, void* notificationHandle);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SimpleTextInputExProtocol
{
    public InputResetExFunc Reset;
    public InputReadKeyExFunc ReadKeyStrokeEx;
    public Event WaitForKeyEx;
    public SetStateFunc SetStateFunc;
    public RegisterKeyStrokeNotifyFunc RegisterKeyNotify;
    public UnregisterKeyStrokeNotifyFunc UnregisterKeyNotify;
}
