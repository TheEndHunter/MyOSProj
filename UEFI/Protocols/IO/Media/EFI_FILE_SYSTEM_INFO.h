#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"
#include <Helper Funcs/StringHelpers.h>

namespace EFI
{
	constinit const ALIGN(8) EFI::EFI_GUID EFI_FILE_SYSTEM_INFO_ID         {0x09576e93U,0x6d3fU,0x11d2U,{0x8eU,0x39U,0x00U,0xa0U,0xc9U,0x69U,0x72U,0x3bU }};
	
	struct EFI_FILE_SYSTEM_INFO
	{
	public:
		UINT64 Size;
		BOOLEAN ReadOnly;
		UINT64 VolumeSize;
		UINT64 FreeSpace;
		UINT32 BlockSize;
		CONST CHAR16* VolumeLabel;

		BOOLEAN operator ==(const EFI_FILE_SYSTEM_INFO& other) const
		{
			return Size == other.Size &&
				ReadOnly == other.ReadOnly &&
				VolumeSize == other.VolumeSize &&
				FreeSpace == other.FreeSpace &&
				BlockSize == other.BlockSize &&
				CompareStrings(VolumeLabel, other.VolumeLabel);
		}
	};
	constexpr UINT64 EFI_FILE_SYSTEM_INFO_STRUCT_LEN = sizeof(EFI_FILE_SYSTEM_INFO);
}