#pragma once
#include "UEFIDef.h"

namespace EFI
{
	typedef UINTN EFI_TPL;
	

	const UINTN EFI_TPL_APPLICATION = 4;
	const UINTN EFI_TPL_CALLBACK = 8;
	const UINTN EFI_TPL_NOTIFY = 16;
	const UINTN EFI_TPL_HIGH_LEVEL = 31;
};
