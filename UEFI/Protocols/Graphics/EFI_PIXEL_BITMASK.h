#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_PIXEL_BITMASK
	{
	public:
		UINT32 RedMask;
		UINT32 GreenMask;
		UINT32 BlueMask;
		UINT32 ReservedMask;
	};
}