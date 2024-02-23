#pragma once
#include "UEFIDef.h"
#include "EFI_GUID.h"
#include "EFI_MEMORY_ADDRESS.h"
#include <Protocols/Configuration/EFI_CAPSULE_HEADER.h>

namespace EFI
{
	constinit  const ALIGN(8) EFI::EFI_GUID EFI_MEMORY_RANGE_CAPSULE_GUID = { 0xde9f0ec, 0x88b6, 0x428f,{ 0x97, 0x7a, 0x25, 0x8f, 0x1d, 0xe, 0x5e, 0x72} };

	struct EFI_MEMORY_RANGE
	{
	public:
		EFI_PHYSICAL_ADDRESS Address;
		UINT64 Length;
	};

	struct EFI_MEMORY_RANGE_CAPSULE
	{
	public:
		EFI_CAPSULE_HEADER Header;
		UINT32 OsRequestedMemoryType;
		UINT64 NumberOfMemoryRanges;
		EFI_MEMORY_RANGE MemoryRanges[];
	} ;

	struct EFI_MEMORY_RANGE_CAPSULE_RESULT
	{
	public:
		UINT64 FirmwareMemoryRequirement;
		UINT64 NumberOfMemoryRanges;
	};
}
