#pragma once
#include "UEFIDef.h"

namespace Efi
{
    enum class StopBitsType : UINT8
	{
		DefaultStopBits,
		OneStopBit,         // 1 stop bit
		OneFiveStopBits,    // 1.5 stop bits
		TwoStopBits         // 2 stop bits
	};
}