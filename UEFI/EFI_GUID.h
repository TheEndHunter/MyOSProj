#pragma once

#include "UEFIDef.h"

namespace EFI
{
	struct EFI_GUID
	{
	public:
		UINT32 Data1;
		UINT16 Data2;
		UINT16 Data3;
		UINT8 Data4[8];
	};
}
