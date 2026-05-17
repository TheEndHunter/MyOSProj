#pragma once

#include "UEFIDef.h"

namespace Efi
{
	struct DevicePathProtocol
	{
	public:
		UINT8 Type;
		UINT8 SubType;
		UINT8 Length[2];
	};
}
