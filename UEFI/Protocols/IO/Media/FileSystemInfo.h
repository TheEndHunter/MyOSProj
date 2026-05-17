#pragma once
#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include <Protocols/Time/Time.h>
#include "FileAttributes.h"
#include <HelperFuncs/StringHelpers.h>

namespace Efi
{
	constinit const ALIGN(8) Efi::Guid EFI_FILE_SYSTEM_INFO_ID         {0x09576e93U,0x6d3fU,0x11d2U,{0x8eU,0x39U,0x00U,0xa0U,0xc9U,0x69U,0x72U,0x3bU }};
	
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