#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/Time.h>
#include <Protocols/IO/Media/FileProtocol.h>
#include <Protocols/IO/Media/FileInfo.h>
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
        FileInfo(Efi::FileInfo* info);
	public:
		constexpr FileInfo()
		{
			Size = 0;
			FileSize = 0;
			PhysicalSize = 0;
			CreateTime = Efi::Time();
			LastAccessTime = Efi::Time();
			ModificationTime = Efi::Time();
			Attribute = 0;
			FileName = nullptr;
		}

        static FileInfo Create(Efi::FileInfo* info);

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
		Efi::Time CreateTime;
		Efi::Time LastAccessTime;
		Efi::Time ModificationTime;
		UINT64 Attribute;
		CONST CHAR16* FileName;
	};

	constinit const FileInfo Empty_FileInfo = FileInfo();
}
