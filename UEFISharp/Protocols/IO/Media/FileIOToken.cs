using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

[StructLayout(LayoutKind.Sequential)]
public struct FileIOToken
{
    public Event Event;
    public Status Status;
    public nuint BufferSize;
    public nint Buffer;
}
