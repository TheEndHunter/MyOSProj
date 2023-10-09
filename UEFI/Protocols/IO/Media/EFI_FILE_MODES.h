#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum EFI_FILE_MODES : UINT64
	{
		READ = 1,
		WRITE = 2,
		CREATE = 0,
	};
};
