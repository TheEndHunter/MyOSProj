#pragma once

#include "UEFIDef.h"

namespace EFI
{
	struct EFI_DEVICE_PATH_PROTOCOL
	{
	public:
		UINT8 Type;
		UINT8 SubType;
		UINT8 Length[2];
	};
}
