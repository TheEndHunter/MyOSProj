#pragma once
#include <UEFIDef.h>
#include <EFI_MEMORY_ADDRESS.h>

namespace EFI
{
	struct _EFI_SYSTEM_TABLE_POINTER
	{
	public:
		UINT64 Signature;
		EFI_PHYSICAL_ADDRESS EfiSystemTableBase;
		UINT32 Crc32;
	};
}
