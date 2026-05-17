#pragma once
#include <UEFIDef.h>
#include <EFI_MEMORY_ADDRESS.h>

namespace Efi
{
	struct _EFI_SYSTEM_TABLE_POINTER
	{
	public:
		UINT64 Signature;
		PhysicalAddress EfiSystemTableBase;
		UINT32 Crc32;
	};
}
