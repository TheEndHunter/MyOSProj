#pragma once

#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/Pixel.h>
#include <Graphics/PixelBitMask.h>
#include <Graphics/PixelFormat.h>

namespace Common::Graphics
{
	struct MonitorMode
	{
		friend struct MonitorContext;
	private:
		const MonitorMode(UINT32 version, UINT32 horizonalRes, UINT32 verticalRes, PixelFormat format, PixelBitMask bitMask, UINT32 pixelsPerScanLine, UINTN fbSize, Pixel* fbPtr);
		
	public:
		UINT32 Version;
		UINT32 HorizontalResolution;
		UINT32 VerticalResolution;
		PixelFormat Format;
		PixelBitMask BitMask;
		UINT32 PixelsPerScanLine;
		UINTN FrameBufferSize;
		Pixel* FrameBufferBase;
	};	
}
