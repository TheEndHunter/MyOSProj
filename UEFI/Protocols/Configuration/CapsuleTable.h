#pragma once

#include "UEFIDef.h"

namespace Efi
{
    struct CapsuleTable
	{
	public:
		UINT32 CapsuleArrayNumber;
		VOID** CapsulePtr;
	};
}
