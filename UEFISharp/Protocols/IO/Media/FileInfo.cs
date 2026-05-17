using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

[StructLayout(LayoutKind.Sequential)]
public struct FileInfo
{
    public ulong Size;
    public ulong FileSize;
    public ulong PhysicalSize;
    public Time CreateTime;
    public Time LastAccessTime;
    public Time ModificationTime;
    public FileAttributes Attribute;
    public nint FileName; // CHAR16*
}
