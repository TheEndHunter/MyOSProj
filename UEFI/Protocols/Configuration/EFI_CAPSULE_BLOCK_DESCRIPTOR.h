#pragma once
#include "UEFIDef.h"
#include "EFI_MEMORY_ADDRESS.h"


namespace EFI
{
	struct EFI_CAPSULE_BLOCK_DESCRIPTOR
	{
	public:
		UINT64 Length;
		union {
			EFI_PHYSICAL_ADDRESS DataBlock;
			EFI_PHYSICAL_ADDRESS ContinuationPointer;
		};
	};
}
