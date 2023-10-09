#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"

namespace EFI
{
	constinit const EFI::EFI_GUID EFI_FILE_SYSTEM_VOLUME_LABEL_ID{ 0xdb47d7d3,0xfe81,0x11d3,0x9a35,0x00,0x90,0x27,0x3f,0xC1,0x4d };

	struct EFI_FILE_SYSTEM_VOLUME_LABEL
	{
	public:
		CHAR16 VolumeLabel[];
	};
}
