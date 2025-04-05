#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_PROTOCOL.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>

namespace Common::FileSystem
{
	struct DirectoryInfo
	{
		
	protected:
		DirectoryInfo(EFI::EFI_FILE_INFO* info);
	public:
		constexpr DirectoryInfo()
		{
			Size = 0;
			FileSize = 0;
			PhysicalSize = 0;
			CreateTime = EFI::EFI_TIME();
			LastAccessTime = EFI::EFI_TIME();
			ModificationTime = EFI::EFI_TIME();
			Attribute = 0;
			DirectoryName = nullptr;
		}

		static DirectoryInfo Create(EFI::EFI_FILE_INFO* info);

	public:
		UINT64 Size;
		UINT64 FileSize;
		UINT64 PhysicalSize;
		EFI::EFI_TIME CreateTime;
		EFI::EFI_TIME LastAccessTime;
		EFI::EFI_TIME ModificationTime;
		UINT64 Attribute;
		CHAR16* DirectoryName;

		BOOLEAN operator ==(const DirectoryInfo& right);

		BOOLEAN operator !=(const DirectoryInfo& right);
	};

	constinit const DirectoryInfo Empty_DirectoryInfo = DirectoryInfo();
}
