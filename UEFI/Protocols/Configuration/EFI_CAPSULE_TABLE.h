#pragma once

#include "UEFIDef.h"

namespace EFI
{
	struct EFI_CAPSULE_TABLE
	{
	public:
		UINT32 CapsuleArrayNumber;
		VOID* CapsulePtr[1];
	};
}
