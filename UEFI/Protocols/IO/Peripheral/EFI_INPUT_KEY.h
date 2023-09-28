#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_INPUT_KEY
	{
	public:
		UINT16 ScanCode;
		CHAR16 UnicodeChar;
	};
}
