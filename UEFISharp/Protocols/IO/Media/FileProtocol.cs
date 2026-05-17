using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Media;

public static partial class EFIConsts
{
    public const uint FileProtocol_REVISION = 0x00010000;
    public const uint FileProtocol_REVISION2 = 0x00020000;
    public const uint FileProtocol_LATEST_REVISION = FileProtocol_REVISION2;
}

public unsafe delegate Status FileOpenFunc(FileProtocol* self, FileProtocol** newHandle, char* fileName, FileModes openMode, ulong attributes);
public unsafe delegate Status FileCloseFunc(FileProtocol* self);
public unsafe delegate Status FileDeleteFunc(FileProtocol* self);
public unsafe delegate Status FileReadFunc(FileProtocol* self, nuint* bufferSize, void* buffer);
public unsafe delegate Status FileWriteFunc(FileProtocol* self, nuint* bufferSize, void* buffer);

public unsafe delegate Status FileOpenExFunc(FileProtocol* self, FileProtocol** newHandle, char* fileName, FileModes openMode, ulong attributes, FileIOToken* token);
public unsafe delegate Status FileReadExFunc(FileProtocol* self, FileIOToken* token);
public unsafe delegate Status FileWriteExFunc(FileProtocol* self, FileIOToken* token);
public unsafe delegate Status FileFlushExFunc(FileProtocol* self, FileIOToken* token);

public unsafe delegate Status FileSetPositionFunc(FileProtocol* self, ulong position);
public unsafe delegate Status FileGetPositionFunc(FileProtocol* self, ulong* position);
public unsafe delegate Status FileGetInfoFunc(FileProtocol* self, Guid* informationType, nuint* bufferSize, void* buffer);
public unsafe delegate Status FileSetInfoFunc(FileProtocol* self, Guid* informationType, nuint bufferSize, void* buffer);
public unsafe delegate Status FileFlushFunc(FileProtocol* self);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct FileProtocol
{
    public ulong Revision;
    public FileOpenFunc Open;
    public FileCloseFunc Close;
    public FileDeleteFunc Delete;
    public FileReadFunc Read;
    public FileWriteFunc Write;
    public FileGetPositionFunc GetPosition;
    public FileSetPositionFunc SetPosition;
    public FileGetInfoFunc GetInfo;
    public FileSetInfoFunc SetInfo;
    public FileFlushFunc Flush;
    public FileOpenExFunc OpenEx;
    public FileReadExFunc ReadEx;
    public FileWriteExFunc WriteEx;
    public FileFlushExFunc FlushEx;
}
