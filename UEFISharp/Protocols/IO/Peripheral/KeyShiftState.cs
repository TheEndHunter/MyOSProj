namespace EFI.Protocols.IO.Peripheral;

public enum KeyShiftState : uint
{
    None = 0,
    RightShiftPressed = 0x00000001,
    LeftShiftPressed = 0x00000002,
    RightControlPressed = 0x00000004,
    LeftControlPressed = 0x00000008,
    RightAltPressed = 0x00000010,
    LeftAltPressed = 0x00000020,
    RightLogoPressed = 0x00000040,
    LeftLogoPressed = 0x00000080,
    MenuKeyPressed = 0x00000100,
    SysReqPressed = 0x00000200,
}
