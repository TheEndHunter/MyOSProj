#pragma once
#include "UEFIDef.h"

namespace Efi
{
	struct SimplePointerState
	{
	public:
		INT32 RelativeMovementX;
		INT32 RelativeMovementY;
		INT32 RelativeMovementZ;
		BOOLEAN LeftButton;
		BOOLEAN RightButton;
	} ;
}
