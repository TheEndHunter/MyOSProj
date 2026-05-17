#pragma once

#include "UEFIDef.h"
#include "GraphicsPixelFormat.h"
#include "PixelBitmask.h"

namespace Efi
{
	struct GraphicsOutputModeInformation
	{
	public:
		UINT32 Version;
		UINT32 HorizontalResolution;
		UINT32 VerticalResolution;
		GraphicsPixelFormat PixelFormat;
		PixelBitmask PixelInformation;
		UINT32 PixelsPerScanLine;
	};
}