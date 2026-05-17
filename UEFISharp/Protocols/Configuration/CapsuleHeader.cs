using System.Runtime.InteropServices;



namespace EFI.Protocols.Configuration;

[StructLayout(LayoutKind.Sequential)]
public struct CapsuleHeader
{
    public Guid CapsuleGuid;
    public uint HeaderSize;
    public uint Flags;
    public uint CapsuleImageSize;
}

public static class CapsuleFlags
{
    public const uint CAPSULE_FLAGS_PERSIST_ACROSS_RESET = 0x00010000;
    public const uint CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE = 0x00020000;
    public const uint CAPSULE_FLAGS_INITIATE_RESET = 0x00040000;
}
