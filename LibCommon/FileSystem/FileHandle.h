#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>
#include <EFI_STATUS.h>
#include "FileInfo.h"

namespace Common::FileSystem
{
	struct FileHandle
	{
		friend class FileSystemContext;
	protected:
		FileHandle(EFI::EFI_FILE_PROTOCOL* file, FileInfo& i) : Info(i), Size(i.Size), _File(file) {};

	public:
		constexpr FileHandle(): _File(nullptr), Size(0) {};

		static FileHandle Create(EFI::EFI_FILE_PROTOCOL* file, FileInfo& i);
		FileInfo Info;
		UINT64 Size;

		bool operator ==(const FileHandle& right);
		bool operator !=(const FileHandle& right);
		
	protected:
		EFI::EFI_FILE_PROTOCOL* _File;
	};

	constinit const FileHandle Empty_FileHandle = FileHandle();
}