#pragma once
#include "UEFIDef.h"
#include "EFI_GUID.h"

namespace EFI
{
	struct EFI_CAPSULE_HEADER
	{
	public:
		EFI_GUID CapsuleGuid;
		UINT32 HeaderSize;
		UINT32 Flags;
		UINT32 CapsuleImageSize;
	};

	inline const UINT32 CAPSULE_FLAGS_PERSIST_ACROSS_RESET = 0x00010000;
	inline const UINT32 CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE = 0x00020000;
	inline const UINT32 CAPSULE_FLAGS_INITIATE_RESET = 0x00040000;
}
