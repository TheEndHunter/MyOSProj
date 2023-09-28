#pragma once
#include "UEFIDef.h"

namespace EFI
{
	typedef UINTN EFI_TPL;
	

	inline const UINTN EFI_TPL_APPLICATION = 4;
	inline const UINTN EFI_TPL_CALLBACK = 8;
	inline const UINTN EFI_TPL_NOTIFY = 16;
	inline const UINTN EFI_TPL_HIGH_LEVEL = 31;
};
