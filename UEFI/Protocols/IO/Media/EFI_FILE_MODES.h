#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum EFI_FILE_MODES : UINT64
	{
		Read = 0x0000000000000001,
		Write  = 0x0000000000000002,
		Create = 0x8000000000000000,
		ReadWrite = Read | Write,
	};
};
