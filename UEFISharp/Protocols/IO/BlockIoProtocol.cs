using System.Runtime.InteropServices;

namespace EFI.Protocols.IO;

public static partial class EFIConsts
{
    public static readonly Guid BlockIoProtocolGuid = new(0x964E5B21, 0x6459, 0x11D2, 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B);
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct BlockIoMedia
{
    public uint MediaId;
    public bool RemovableMedia;
    public bool MediaPresent;
    public bool LogicalPartition;
    public bool ReadOnly;
    public bool WriteCaching;
    public uint BlockSize; // UINT32
    public uint IoAlign; // UINT32
    public ulong LastBlock; // EFI_LBA (UINT64)
}

public unsafe delegate Status BlockIoResetFunc(BlockIoProtocol* self, bool extendedVerification);
public unsafe delegate Status BlockIoReadBlocksFunc(BlockIoProtocol* self, uint mediaId, ulong lba, nuint bufferSize, void* buffer);
public unsafe delegate Status BlockIoWriteBlocksFunc(BlockIoProtocol* self, uint mediaId, ulong lba, nuint bufferSize, void* buffer);
public unsafe delegate Status BlockIoFlushFunc(BlockIoProtocol* self);

// Per-spec aliases for clearer signatures
public unsafe delegate Status BlockIoReset(BlockIoProtocol* self, bool extendedVerification);
public unsafe delegate Status BlockIoReadBlocks(BlockIoProtocol* self, uint mediaId, ulong lba, nuint bufferSize, void* buffer);
public unsafe delegate Status BlockIoWriteBlocks(BlockIoProtocol* self, uint mediaId, ulong lba, nuint bufferSize, void* buffer);
public unsafe delegate Status BlockIoFlush(BlockIoProtocol* self);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct BlockIoProtocol
{
    public ulong Revision;
    public BlockIoMedia* Media;
    public BlockIoResetFunc Reset;
    public BlockIoReadBlocksFunc ReadBlocks;
    public BlockIoWriteBlocksFunc WriteBlocks;
    public BlockIoFlushFunc FlushBlocks;
}
