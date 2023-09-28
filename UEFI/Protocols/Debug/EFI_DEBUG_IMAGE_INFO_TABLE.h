#pragma once
#include <EFI_GUID.h>
#include <Protocols/Debug/EFI_DEBUG_IMAGE_INFO.h>

namespace EFI
{
	constinit const EFI_GUID EFI_DEBUG_IMAGE_INFO_TABLE_GUID = { 0x49152E77,0x1ADA,0x4764, {0xB7,0xA2,0x7A,0xFE,0xFE,0xD9,0x5E,0x8B } };

	inline const UINT8 EFI_DEBUG_IMAGE_INFO_UPDATE_IN_PROGRESS = 0x01;
	inline const UINT8 EFI_DEBUG_IMAGE_INFO_TABLE_MODIFIED = 0x02;

	typedef struct  EFI_DEBUG_IMAGE_INFO_TABLE_HEADER 
	{
	public:
		volatile UINT32 UpdateStatus;
		UINT32 TableSize;
		EFI_DEBUG_IMAGE_INFO* EfiDebugImageInfoTable;
	};
}
