#pragma once

#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/Pixel.h>
#include <Graphics/PixelBitMask.h>
#include <Graphics/PixelFormat.h>

#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>


namespace Common::Graphics
{
	struct MonitorMode
	{
		friend struct MonitorContext;
	private:
		MonitorMode();
		MonitorMode(UINT32 version, UINT32 horizonalRes, UINT32 verticalRes, PixelFormat format, PixelBitMask bitMask, UINT32 pixelsPerScanLine, UINTN fbSize, VOID_PTR* fbPtr);
		MonitorMode(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* mode);
		
	public:
		UINT32 Version;
		UINT32 HorizontalResolution;
		UINT32 VerticalResolution;
		PixelFormat Format;
		PixelBitMask BitMask;
		UINT32 PixelsPerScanLine;
		UINTN FrameBufferSize;
		VOID_PTR FrameBufferBase;

	};	
}
