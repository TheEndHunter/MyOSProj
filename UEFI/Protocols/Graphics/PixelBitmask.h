#pragma once
#include "UEFIDef.h"

namespace Efi
{
	struct PixelBitmask
	{
	public:
		UINT32 RedMask;
		UINT32 GreenMask;
		UINT32 BlueMask;
		UINT32 ReservedMask;
	};
}