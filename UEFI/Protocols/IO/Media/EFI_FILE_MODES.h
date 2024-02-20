#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum EFI_FILE_MODES : UINT64
	{
		CREATE = 0,
		READ = 1,
		WRITE = 2,
		READWRITE = READ | WRITE,
	};
};
