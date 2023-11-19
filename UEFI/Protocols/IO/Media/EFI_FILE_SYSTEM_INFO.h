#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"

namespace EFI
{
	constinit const EFI::EFI_GUID EFI_FILE_SYSTEM_INFO_ID{ 0x09576e93,0x6d3f,0x11d2,0x8e39,0x00,0xa0,0xc9,0x69,0x72,0x3b };

	struct EFI_FILE_SYSTEM_INFO
	{
	public:
		UINT64 Size;
		BOOLEAN ReadOnly;
		UINT64 VolumeSize;
		UINT64 FreeSpace;
		UINT32 BlockSize;
		CHAR16* VolumeLabel;
	};
}