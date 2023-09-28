#pragma once

#include "UEFIDef.h"

namespace EFI
{
#pragma pack(push, 1)
	struct alignas(8) EFI_GUID
	{
	public:
		UINT32 Data1;
		UINT16 Data2;
		UINT16 Data3;
		UINT8 Data4[8];
	};
#pragma pack(pop)
}
