namespace EFI.Protocols.IO.Media;

[System.Flags]
public enum FileModes : ulong
{
    Read = 0x0000000000000001,
    Write = 0x0000000000000002,
    Create = 0x8000000000000000,
    ReadWrite = Read | Write,
}
