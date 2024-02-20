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
	public:
		constexpr VolumeInfo()
		{
			Size = 0;
			ReadOnly = 0;
			VolumeSize = 0;
			FreeSpace = 0;
			BlockSize = 0;
			VolumeLabel = u"\0\0\0\0\0\0\0\0\0\0";
		}

		static VolumeInfo Create(EFI::EFI_FILE_SYSTEM_INFO* info);

	public:
		UINT64 Size;
		BOOLEAN ReadOnly;
		UINT64 VolumeSize;
		UINT64 FreeSpace;
		UINT32 BlockSize;
		const CHAR16* VolumeLabel;

		bool operator ==(const VolumeInfo& right)
		{
			/*Compare all members for equality, if one fails return false, otherwise return true*/

			if (Size != right.Size)
				return false;

			if (ReadOnly != right.ReadOnly)
				return false;

			if (VolumeSize != right.VolumeSize)
				return false;

			if (FreeSpace != right.FreeSpace)
				return false;

			if (BlockSize != right.BlockSize)
				return false;

			if (VolumeLabel != right.VolumeLabel)
				return false;

			return true;
		}

		bool operator !=(const VolumeInfo& right)
		{
			return !(*this == right);
		}
	};
	constinit const VolumeInfo Empty_VolInfo = VolumeInfo();
}
