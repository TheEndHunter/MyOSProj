#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_SIMPLE_POINTER_STATE
	{
	public:
		INT32 RelativeMovementX;
		INT32 RelativeMovementY;
		INT32 RelativeMovementZ;
		BOOLEAN LeftButton;
		BOOLEAN RightButton;
	} ;
}
