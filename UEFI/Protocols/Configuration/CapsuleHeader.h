#pragma once
#include "UEFIDef.h"
#include <Guid.h>

namespace Efi
{
    struct CapsuleHeader
	{
	public:
		Guid CapsuleGuid;
		UINT32 HeaderSize;
		UINT32 Flags;
		UINT32 CapsuleImageSize;
	};

	CONST UINT32 CAPSULE_FLAGS_PERSIST_ACROSS_RESET = 0x00010000;
	CONST UINT32 CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE = 0x00020000;
	CONST UINT32 CAPSULE_FLAGS_INITIATE_RESET = 0x00040000;
}
