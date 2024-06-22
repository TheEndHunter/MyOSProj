#include "VolumeInfo.h"

namespace Common::FileSystem
{
	VolumeInfo VolumeInfo::Create(EFI::EFI_FILE_SYSTEM_INFO* info)
	{
		if (info == nullptr)
			return Empty_VolInfo;

		return VolumeInfo(*info);
	}
}
