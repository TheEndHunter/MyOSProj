#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"
#include <Helper Funcs/StringHelpers.h>

namespace EFI
{
	constinit const ALIGN(8) EFI::EFI_GUID EFI_FILE_SYSTEM_VOLUME_LABEL_ID { 0xdb47d7d3U,0xfe81U,0x11d3U,{0x9aU,0x35U,0x00U,0x90U,0x27U,0x3fU,0xC1U,0x4dU } };

	struct EFI_FILE_SYSTEM_VOLUME_LABEL
	{
	public:
		const CHAR16* VolumeLabel;


		BOOLEAN operator==(const EFI_FILE_SYSTEM_VOLUME_LABEL& other) const
		{
			return CompareStrings(VolumeLabel, other.VolumeLabel);
		}
	};
}
