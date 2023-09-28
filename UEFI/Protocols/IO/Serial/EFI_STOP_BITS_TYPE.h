#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum class EFI_STOP_BITS_TYPE : UINT8
	{
		DefaultStopBits,
		OneStopBit,         // 1 stop bit
		OneFiveStopBits,    // 1.5 stop bits
		TwoStopBits         // 2 stop bits
	};
}