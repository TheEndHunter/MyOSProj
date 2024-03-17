#include "MonitorContext.h"
#include <System\Allocator.h>

namespace Common::Graphics
{
	MonitorContext::MonitorContext()
	{
		protocol = nullptr;
		modes = nullptr;
		maxMode = 0;
		currentMode = 0;
	};

	MonitorContext::MonitorContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr)
	{
		protocol = ptr;
		maxMode = ptr->Mode->MaxMode;
		
		modes = (MonitorMode*)System::Allocator::Allocate(sizeof(MonitorMode)*maxMode);
		for (UINT32 i = 0; i < maxMode; i++)
		{
			EFI::EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info = ptr->Mode->Info;

			modes[i] = MonitorMode(info->Version, info->HorizontalResolution, info->VerticalResolution,(PixelFormat)info->PixelFormat, (PixelBitMask)info->PixelInformation,info->PixelsPerScanLine,ptr->Mode->FrameBufferSize,(Pixel*)ptr->Mode->FrameBufferBase);
		}
		currentMode = ptr->Mode->Mode;
	}

	const MonitorMode* MonitorContext::GetCurrentMode() const
	{
		return &modes[currentMode];
	}

	const MonitorMode* MonitorContext::GetMode(UINT32 modeNumber) const
	{
		return &modes[modeNumber];
	}
	void MonitorContext::SetMode(UINT32 modeNumber)
	{
		auto s = protocol->SetMode(protocol, modeNumber);
		if(s != EFI::EFI_STATUS::SUCCESS)
		{
			return;
		}
		currentMode = modeNumber;
	}

	UINTN MonitorContext::GetFrameBufferSize() const
	{
		return modes[currentMode].FrameBufferSize;
	}

	UINT32 MonitorContext::GetHorizontalResolution() const
	{
		return modes[currentMode].HorizontalResolution;
	}

	UINT32 MonitorContext::GetVerticalResolution() const
	{
		return modes[currentMode].VerticalResolution;
	}

	UINT32 MonitorContext::GetPixelsPerScanLine() const
	{
		return modes[currentMode].PixelsPerScanLine;
	}

	Pixel* MonitorContext::GetFrameBuffer() const
	{
		return modes[currentMode].FrameBufferBase;
	}
}
