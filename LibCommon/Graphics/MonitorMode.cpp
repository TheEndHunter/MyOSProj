#include <Graphics/MonitorMode.h>

namespace Common::Graphics
{
	MonitorMode::MonitorMode(UINT32 version, UINT32 horizonalRes, UINT32 verticalRes, PixelFormat format, PixelBitMask bitMask, UINT32 pixelsPerScanLine, UINTN fbSize, Pixel* fbPtr)
	{
		Version = version;
		HorizontalResolution = horizonalRes;
		VerticalResolution = verticalRes;
		Format = format;
		BitMask = bitMask;
		PixelsPerScanLine = pixelsPerScanLine;
		FrameBufferSize = fbSize;
		FrameBufferBase = fbPtr;
	}

	PixelBitMask::PixelBitMask()
	{
		RedMask = 0;
		GreenMask = 0;
		BlueMask = 0;
		AlphaMask = 0;
	};

	PixelBitMask::PixelBitMask(UINT32 red, UINT32 green, UINT32 blue, UINT32 alpha)
	{
		RedMask = red;
		GreenMask = green;
		BlueMask = blue;
		AlphaMask = alpha;
	};
	PixelBitMask::PixelBitMask(EFI::EFI_PIXEL_BITMASK& mask)
	{
		RedMask = mask.RedMask;
		GreenMask = mask.GreenMask;
		BlueMask = mask.BlueMask;
		AlphaMask = mask.ReservedMask;
	};
}