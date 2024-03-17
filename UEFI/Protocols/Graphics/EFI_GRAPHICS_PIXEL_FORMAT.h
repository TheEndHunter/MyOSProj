#pragma once


#include "UEFIDef.h"

namespace EFI
{
	enum EFI_GRAPHICS_PIXEL_FORMAT : UINT32
	{
		PixelRedGreenBlueReserved8BitPerColor,
		PixelBlueGreenRedReserved8BitPerColor,
		PixelBitMask,
		PixelBltOnly,
		PixelFormatMax
	};
}