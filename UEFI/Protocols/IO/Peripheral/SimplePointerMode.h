#pragma once
#include "UEFIDef.h"

namespace Efi
{
	struct SimplePointerMode 
	{
	public:
		UINT64 ResolutionX;
		UINT64 ResolutionY;
		UINT64 ResolutionZ;
		BOOLEAN LeftButton;
		BOOLEAN RightButton;
	};
}
