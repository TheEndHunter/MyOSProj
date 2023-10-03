#pragma once

#include "UEFIDef.h"

namespace EFI
{
	typedef struct EFI_GUID
	{
	public:
		UINT32 Data1;
		UINT16 Data2;
		UINT16 Data3;
		UINT8 Data4[8];
	} EFI_GUID;
}
