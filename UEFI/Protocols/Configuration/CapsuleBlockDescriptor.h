#pragma once
#include "UEFIDef.h"
#include "MemoryAddress.h"


namespace Efi
{
    struct CapsuleBlockDescriptor
	{
	public:
		UINT64 Length;
		union {
			PhysicalAddress DataBlock;
			PhysicalAddress ContinuationPointer;
		};
	};
}
