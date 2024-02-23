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
		FileInfo(EFI::EFI_FILE_INFO* info);
	public:
		constexpr FileInfo()
		{
			Size = 0;
			FileSize = 0;
			PhysicalSize = 0;
			CreateTime = EFI::EFI_TIME();
			LastAccessTime = EFI::EFI_TIME();
			ModificationTime = EFI::EFI_TIME();
			Attribute = 0;
			FileName = nullptr;
		}

		static FileInfo Create(EFI::EFI_FILE_INFO* info);

	public:
		UINT64 Size;
		UINT64 FileSize;
		UINT64 PhysicalSize;
		EFI::EFI_TIME CreateTime;
		EFI::EFI_TIME LastAccessTime;
		EFI::EFI_TIME ModificationTime;
		UINT64 Attribute;
		CHAR16* FileName;

		bool operator ==(const FileInfo& right);

		bool operator !=(const FileInfo& right);
	};

	constinit const FileInfo Empty_FileInfo = FileInfo();
}
