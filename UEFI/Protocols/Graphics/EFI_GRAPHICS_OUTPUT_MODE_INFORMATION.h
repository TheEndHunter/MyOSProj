#pragma once

#include "UEFIDef.h"
#include "EFI_GRAPHICS_PIXEL_FORMAT.h"
#include "EFI_PIXEL_BITMASK.h"

namespace EFI
{
	struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
	{
	public:
		UINT32 Version;
		UINT32 HorizontalResolution;
		UINT32 VerticalResolution;
		EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
		EFI_PIXEL_BITMASK PixelInformation;
		UINT32 PixelsPerScanLine;
	};
}