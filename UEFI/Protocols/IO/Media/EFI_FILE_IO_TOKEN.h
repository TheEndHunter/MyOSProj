#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include <EFI_EVENT.h>

namespace EFI
{
	struct EFI_FILE_IO_TOKEN
	{
	public:
		EFI_EVENT Event;
		EFI_STATUS Status;
		UINTN BufferSize;
		VOID* Buffer;
	};
}