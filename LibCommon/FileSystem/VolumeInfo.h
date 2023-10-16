#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_PROTOCOL.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>
#include <Protocols/IO/Media/EFI_FILE_SYSTEM_INFO.h>

namespace Common::FileSystem
{
	struct  VolumeInfo
	{
	protected:

		VolumeInfo(EFI::EFI_FILE_SYSTEM_INFO& info)
			:Size(info.Size), ReadOnly(info.ReadOnly), VolumeSize(info.VolumeSize), FreeSpace(info.FreeSpace), BlockSize(info.BlockSize), VolumeLabel(info.VolumeLabel)
		{
		}

		VolumeInfo()
		{
			Size = 0;
			ReadOnly = 0;
			VolumeSize = 0;
			FreeSpace = 0;
			BlockSize = 0;
			VolumeLabel = nullptr;
		}

	public:
		static VolumeInfo Create(EFI::EFI_FILE_SYSTEM_INFO* info)
		{
			if (info == nullptr)
				return VolumeInfo();

			return VolumeInfo(*info);
		}

	public:
		UINT64 Size;
		BOOLEAN ReadOnly;
		UINT64 VolumeSize;
		UINT64 FreeSpace;
		UINT32 BlockSize;
		CHAR16* VolumeLabel;
	};
}
