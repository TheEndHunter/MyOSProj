using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

[StructLayout(LayoutKind.Sequential)]
public struct FileSystemInfo
{
    public ulong Size;
    public bool ReadOnly;
    public ulong VolumeSize;
    public ulong FreeSpace;
    public uint BlockSize;
    public nint VolumeLabel; // CHAR16*
}
