#include <Graphics/MonitorMode.h>

namespace Common::Graphics
{
	MonitorMode::MonitorMode() : Version(0), HorizontalResolution(0), VerticalResolution(0), Format(PixelFormat::RedGreenBlueReserved8BitPerColor), BitMask(PixelBitMask()), PixelsPerScanLine(0), FrameBufferSize(0), FrameBufferBase(nullptr)
	{
	}

	MonitorMode::MonitorMode(UINT32 version, UINT32 horizonalRes, UINT32 verticalRes, PixelFormat format, PixelBitMask bitMask, UINT32 pixelsPerScanLine, UINTN fbSize, VOID_PTR* fbPtr): Version(version),
		HorizontalResolution(horizonalRes), VerticalResolution(verticalRes), Format(format), BitMask(bitMask), PixelsPerScanLine(pixelsPerScanLine), FrameBufferSize(fbSize), FrameBufferBase(fbPtr)
	{
	}

	MonitorMode::MonitorMode(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* mode) : Version(mode->Info->Version), HorizontalResolution(mode->Info->HorizontalResolution), VerticalResolution(mode->Info->VerticalResolution), PixelsPerScanLine(mode->Info->PixelsPerScanLine), FrameBufferSize(mode->FrameBufferSize),
		Format((PixelFormat)mode->Info->PixelFormat), BitMask(PixelBitMask(mode->Info->PixelInformation)), FrameBufferBase(mode->FrameBufferBase)
	{
	}
}