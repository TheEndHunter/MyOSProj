#pragma once
#include <UEFIDef.h>
#include <Protocols/Debug/EFI_DEBUG_IMAGE_INFO_NORMAL.h>

namespace EFI
{
	union EFI_DEBUG_IMAGE_INFO
	{
		UINT32* ImageInfoType;
		EFI_DEBUG_IMAGE_INFO_NORMAL* NormalImage;
	};
}
