#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum EFI_FILE_ATTRIBUTES : UINT64
	{
		ReadOnly = 0x0000000000000001,
		Hidden = 0x0000000000000002,
		System = 0x0000000000000004,
		Reserved = 0x0000000000000008,
		Directory = 0x0000000000000010,
		Archive = 0x0000000000000020,
		ValidAttrib = 0x0000000000000037,
	};
};