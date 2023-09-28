#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_SIMPLE_POINTER_MODE 
	{
	public:
		UINT64 ResolutionX;
		UINT64 ResolutionY;
		UINT64 ResolutionZ;
		BOOLEAN LeftButton;
		BOOLEAN RightButton;
	};
}
