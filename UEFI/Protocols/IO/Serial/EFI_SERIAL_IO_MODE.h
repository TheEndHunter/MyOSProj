#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_SERIAL_IO_MODE
	{
	public:
		UINT32 ControlMask;

		// current Attributes
		UINT32 Timeout;
		UINT64 BaudRate;
		UINT32 ReceiveFifoDepth;
		UINT32 DataBits;
		UINT32 Parity;
		UINT32 StopBits;
	};
}