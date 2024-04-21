#include "MonitorContext.h"
#include <System\Allocator.h>

namespace Common::Graphics
{
	MonitorContext::MonitorContext()
	{
		protocol = nullptr;
		modes = nullptr;
		maxMode = 0;
		currentModeNumber = 0;
		currentMode = nullptr;
	};

	MonitorContext::MonitorContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr)
	{
		protocol = ptr;
		maxMode = ptr->Mode->MaxMode;

		if (maxMode == 0)
		{
			return;
		};

		currentModeNumber = ptr->Mode->Mode;
		currentMode = &modes[currentModeNumber];

		modes = System::Allocator::AllocateZeroedArray<MonitorMode>(maxMode);

		if (modes == nullptr)
		{
			maxMode = 0;
			return;
		};

		for (UINT32 i = 0; i < maxMode; i++)
		{			
			ptr->SetMode(ptr, i);

			new(&modes[i]) MonitorMode(ptr->Mode);
		}
		ptr->SetMode(ptr, currentModeNumber);
	}

	MonitorMode* MonitorContext::GetCurrentMode()
	{
		return currentMode;
	}

	MonitorMode* MonitorContext::GetMode(UINT32 modeNumber)
	{
		return &modes[modeNumber];
	}

	BOOLEAN MonitorContext::SetMode(UINT32 modeNumber)
	{
		EFI::EFI_STATUS s = protocol->SetMode(protocol, modeNumber);
		
		if(s != EFI::EFI_STATUS::SUCCESS)
		{
			return FALSE;
		}
		currentModeNumber = modeNumber;
		currentMode = &modes[modeNumber];

		return TRUE;
	}

	UINT32 MonitorContext::GetMaxMode()
	{
		return maxMode;
	}

	UINTN MonitorContext::GetFrameBufferSize() 
	{
		return currentMode->FrameBufferSize;
	}

	UINT32 MonitorContext::GetHorizontalResolution()
	{
		return currentMode->HorizontalResolution;
	}

	UINT32 MonitorContext::GetVerticalResolution()
	{
		return currentMode->VerticalResolution;
	}

	UINT32 MonitorContext::GetPixelsPerScanLine()
	{
		return currentMode->PixelsPerScanLine;
	}

	VOID_PTR MonitorContext::GetFrameBuffer()
	{
		return currentMode->FrameBufferBase;
	}

	PixelFormat MonitorContext::GetPixelFormat()
	{
		return currentMode->Format;
	}

	PixelBitMask MonitorContext::GetPixelBitMask()
	{
		return currentMode->BitMask;
	}


	void MonitorContext::Terminate()
	{
		delete[maxMode] modes;
	}
}
