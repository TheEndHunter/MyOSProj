using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct KeyState
{
    public KeyShiftState KeyShiftState;
    public KeyToggleState KeyToggleState;
}
