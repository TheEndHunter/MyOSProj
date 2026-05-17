#pragma once
#include "UEFIDef.h"

namespace Efi
{
    enum class ParityType
	{
		DefaultParity,
		NoParity,
		EvenParity,
		OddParity,
		MarkParity,
		SpaceParity
	};
}