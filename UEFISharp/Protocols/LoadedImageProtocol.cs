using System.Runtime.InteropServices;
using EFI;
using EFI.Services;

namespace EFI.Protocols
{
    using EfiGuid = Guid;

    public enum LoadOptionAttribute : uint
    {
        LOAD_OPTION_ACTIVE = 0x00000001,
        LOAD_OPTION_FORCE_RECONNECT = 0x00000002,
        LOAD_OPTION_HIDDEN = 0x00000008,
        LOAD_OPTION_CATEGORY = 0x00001F00,
        LOAD_OPTION_CATEGORY_BOOT = 0x00000000,
        LOAD_OPTION_CATEGORY_APP = 0x00000100
    }

    [StructLayout(LayoutKind.Sequential, Pack = 8)]
    public unsafe struct LoadOption
    {
        public LoadOptionAttribute Attributes;
        public ushort FilePathListLength;
        public char* Description; // CHAR16*
        public nint* FilePathList; // DevicePathProtocol**
        public byte** OptionalData; // UINT8**
    }

    public unsafe delegate Status ImageUnload(nint ImageHandle);

    [StructLayout(LayoutKind.Sequential, Pack = 8)]
    public unsafe struct LoadedImageProtocol
    {
        public uint Revision;
        public nint ParentHandle;
        public SystemTable* SystemTable;

        public nint DeviceHandle; // Handle
        public nint FilePath; // DevicePathProtocol*
        public nint Reserved;

        public uint LoadOptionsSize;
        public nint LoadOptions;

        public nint ImageBase; // VOID*
        public ulong ImageSize;
        public MemoryType ImageCodeType;
        public MemoryType ImageDataType;
        public delegate* unmanaged[Cdecl]<nint, Status> Unload; // ImageUnload
    }
}
