#pragma once
#include "UEFIDef.h"
#include "GraphicsOutputModeInformation.h"
#include "MemoryAddress.h"

namespace Efi
{
	struct GraphicsOutputProtocolMode
	{
		public:
		UINT32 MaxMode;
		UINT32 Mode;
		GraphicsOutputModeInformation* Info;
		UINTN SizeOfInfo;
		VOID_PTR FrameBufferBase;
		UINTN FrameBufferSize;
	};
}