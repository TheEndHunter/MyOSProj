#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum class EFI_PARITY_TYPE
	{
		DefaultParity,
		NoParity,
		EvenParity,
		OddParity,
		MarkParity,
		SpaceParity
	};
}