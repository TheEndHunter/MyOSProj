#pragma once


#include "UEFIDef.h"

namespace Efi
{
	enum GraphicsPixelFormat : UINT32
	{
		PixelRedGreenBlueReserved8BitPerColor,
		PixelBlueGreenRedReserved8BitPerColor,
		PixelBitMask,
		PixelBltOnly,
		PixelFormatMax
	};
}