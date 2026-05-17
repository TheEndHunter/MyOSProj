#include "VolumeInfo.h"

namespace Common::FileSystem
{
	VolumeInfo VolumeInfo::Create(Efi::EFI_FILE_SYSTEM_INFO* info)
	{
		if (info == nullptr)
			return Empty_VolInfo;

		return VolumeInfo(info);
	}
}
