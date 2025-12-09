#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_PROTOCOL.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>
#include <System/Environment/Unicode.h>

namespace Common::FileSystem::ESP
{
	class ESP_FS_Context;
}

namespace Common::FileSystem
{
	struct FileInfo
	{
		friend Common::FileSystem::ESP::ESP_FS_Context;
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

		BOOLEAN operator==(const FileInfo& file)
		{
			BOOLEAN result = Common::System::Environment::UTF<CHAR16>::Compare(FileName, file.FileName);

			return result && Size == file.Size && FileSize == file.FileSize && PhysicalSize == file.PhysicalSize && CreateTime == file.CreateTime && LastAccessTime == file.LastAccessTime && ModificationTime == file.ModificationTime && Attribute == file.Attribute;
		}

		BOOLEAN operator!=(const FileInfo& file)
		{
			return !(*this == file);
		}

	public:
		UINT64 Size;
		UINT64 FileSize;
		UINT64 PhysicalSize;
		EFI::EFI_TIME CreateTime;
		EFI::EFI_TIME LastAccessTime;
		EFI::EFI_TIME ModificationTime;
		UINT64 Attribute;
		CONST CHAR16* FileName;
	};

	constinit const FileInfo Empty_FileInfo = FileInfo();
}
