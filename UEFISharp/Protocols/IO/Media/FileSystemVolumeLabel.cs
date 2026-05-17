using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

[StructLayout(LayoutKind.Sequential)]
public struct FileSystemVolumeLabel
{
    public nint VolumeLabel; // CHAR16*
}
