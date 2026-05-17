#pragma once
#include "UEFIDef.h"
#include <Guid.h>
#include <Status.h>
#include "FileIOToken.h"
#include "FileModes.h"
#include "FileAttributes.h"


namespace Efi
{
	struct FileProtocol;

	CONST UINT32 FileProtocol_REVISION = 0x00010000;
	CONST UINT32 FileProtocol_REVISION2 = 0x00020000;
	CONST UINT32 FileProtocol_LATEST_REVISION = FileProtocol_REVISION2;

    typedef Status(EFIAPI* FileOpenFunc) (IN FileProtocol* self,OUT FileProtocol** newHandle,IN CONST CHAR16* fileName,IN FileModes openMode,IN UINT64 attributes);
    typedef Status(EFIAPI* FileCloseFunc) (IN FileProtocol* self);
    typedef Status(EFIAPI* FileDeleteFunc) (IN FileProtocol* self);
    typedef Status(EFIAPI* FileReadFunc) (IN FileProtocol* self,IN OUT UINTN* bufferSize,OUT VOID* buffer);
    typedef Status(EFIAPI* FileWriteFunc) (IN FileProtocol* self, IN OUT UINTN* bufferSize,IN VOID* buffer);

    typedef Status(EFIAPI* FileOpenExFunc) (IN FileProtocol* self, OUT FileProtocol** newHandle, IN CONST CHAR16* fileName, IN FileModes openMode, IN UINT64 attributes, IN OUT FileIOToken* token);
    typedef Status(EFIAPI* FileReadExFunc) (IN FileProtocol* self,IN OUT FileIOToken* token);
    typedef Status(EFIAPI* FileWriteExFunc) (IN FileProtocol* selft,IN OUT FileIOToken* token);
    typedef Status(EFIAPI* FileFlushExFunc) (IN FileProtocol* self,IN OUT FileIOToken* token);

    typedef Status(EFIAPI* FileSetPositionFunc) (IN FileProtocol* self,IN UINT64 position);
    typedef Status(EFIAPI* FileGetPositionFunc) (IN FileProtocol* self,OUT UINT64* position);
    typedef Status(EFIAPI* FileGetInfoFunc) (IN FileProtocol* self,IN const Guid* informationType,IN OUT UINTN* bufferSize,OUT VOID_PTR buffer);
    typedef Status(EFIAPI* FileSetInfoFunc) (IN FileProtocol* self,IN const Guid* informationType,IN UINTN bufferSize,IN VOID_PTR buffer);
    typedef Status(EFIAPI* FileFlushFunc) (IN FileProtocol* self);

	struct FileProtocol
	{
	public:
		UINT64 Revision;
        FileOpenFunc Open;
        FileCloseFunc Close;
        FileDeleteFunc Delete;
        FileReadFunc Read;
        FileWriteFunc Write;
        FileGetPositionFunc GetPosition;
        FileSetPositionFunc SetPosition;
        FileGetInfoFunc GetInfo;
        FileSetInfoFunc SetInfo;
        FileFlushFunc Flush;
        FileOpenExFunc OpenEx; // Added for revision 2
        FileReadExFunc ReadEx; // Added for revision 2
        FileWriteExFunc WriteEx; // Added for revision 2
        FileFlushExFunc FlushEx; // Added for revision 2
	};
}
