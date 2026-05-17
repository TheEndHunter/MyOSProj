#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/Time.h>
#include <Protocols/IO/Media/FileProtocol.h>
#include <Protocols/IO/Media/FileInfo.h>

namespace Common::FileSystem::ESP
{
	class ESP_FS_Context;
}

namespace Common::FileSystem
{
	struct DirectoryInfo
	{
		friend ESP::ESP_FS_Context;
	protected:
        DirectoryInfo(Efi::FileInfo* info);
	public:
		constexpr DirectoryInfo()
		{
			Size = 0;
			FileSize = 0;
			PhysicalSize = 0;
			CreateTime = Efi::Time();
			LastAccessTime = Efi::Time();
			ModificationTime = Efi::Time();
			Attribute = 0;
			DirectoryName = nullptr;
		}

        static DirectoryInfo Create(Efi::FileInfo* info);

	public:
		UINT64 Size;
		UINT64 FileSize;
		UINT64 PhysicalSize;
		Efi::Time CreateTime;
		Efi::Time LastAccessTime;
		Efi::Time ModificationTime;
		UINT64 Attribute;
		CONST CHAR16* DirectoryName;

		BOOLEAN operator ==(const DirectoryInfo& right);

		BOOLEAN operator !=(const DirectoryInfo& right);
	};

	constinit const DirectoryInfo Empty_DirectoryInfo = DirectoryInfo();
}
