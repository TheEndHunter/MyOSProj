#pragma once
#include "UEFIDef.h"
#include "EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.h"
#include "EFI_MEMORY_ADDRESS.h"

namespace EFI
{
	struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
	{
		public:
		UINT32 MaxMode;
		UINT32 Mode;
		EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* Info;
		UINTN SizeOfInfo;
		VOID_PTR FrameBufferBase;
		UINTN FrameBufferSize;
	};
}