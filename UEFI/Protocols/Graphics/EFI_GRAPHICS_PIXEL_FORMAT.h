#pragma once


#include "UEFIDef.h"

namespace EFI
{
	enum class EFI_GRAPHICS_PIXEL_FORMAT
	{
		PixelRedGreenBlueReserved8BitPerColor,
		PixelBlueGreenRedReserved8BitPerColor,
		PixelBitMask,
		PixelBltOnly,
		PixelFormatMax
	};
}