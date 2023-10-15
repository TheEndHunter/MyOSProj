#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_PROTOCOL.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>

namespace Common::FileSystem
{
	struct FileInfo
	{
	protected:
		EFI::EFI_FILE_PROTOCOL* _FileHandle;

		FileInfo(EFI::EFI_FILE_PROTOCOL* _file, EFI::EFI_FILE_INFO& info)
		{
			_FileHandle = _file;
			Size = info.Size;
			FileSize = info.FileSize;
			PhysicalSize = info.PhysicalSize;
			CreateTime = info.CreateTime;
			LastAccessTime = info.LastAccessTime;
			ModificationTime = info.ModificationTime;
			Attribute = info.Attribute;
			FileName = info.FileName;
		}

	public:
		UINT64 Size;
		UINT64 FileSize;
		UINT64 PhysicalSize;
		EFI::EFI_TIME CreateTime;
		EFI::EFI_TIME LastAccessTime;
		EFI::EFI_TIME ModificationTime;
		UINT64 Attribute;
		CHAR16* FileName;
	};
}
