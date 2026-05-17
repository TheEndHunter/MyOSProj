using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct KeyData
{
    public InputKey Key;
    public KeyState KeyState;
}
