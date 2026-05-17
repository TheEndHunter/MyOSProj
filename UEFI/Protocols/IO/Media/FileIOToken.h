#pragma once
#include "UEFIDef.h"
#include <Status.h>
#include <Event.h>

namespace Efi
{
    struct FileIOToken
	{
	public:
		Event Event;
		Status Status;
		UINTN BufferSize;
		VOID* Buffer;
	};
}