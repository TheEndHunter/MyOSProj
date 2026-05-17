using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct InputKey
{
    public ushort ScanCode;
    public char UnicodeChar; // CHAR16, UTF-16 code unit
}
