namespace EFI.Protocols.IO.Peripheral;

public enum KeyToggleState : byte
{
    None = 0,
    ScrollLockActive = 0x01,
    NumLockActive = 0x02,
    CapsLockActive = 0x04,
}
