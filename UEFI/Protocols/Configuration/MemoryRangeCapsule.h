#pragma once
#include "UEFIDef.h"
#include <Guid.h>
#include "MemoryAddress.h"
#include <Protocols/Configuration/CapsuleHeader.h>

namespace Efi
{
    constinit  const ALIGN(8) Efi::Guid MemoryRangeCapsuleGuid = { 0xde9f0ec, 0x88b6, 0x428f,{ 0x97, 0x7a, 0x25, 0x8f, 0x1d, 0xe, 0x5e, 0x72} };

    struct MemoryRange
	{
	public:
		PhysicalAddress Address;
		UINT64 Length;
	};

    struct MemoryRangeCapsule
	{
	public:
        CapsuleHeader Header;
		UINT32 OsRequestedMemoryType;
		UINT64 NumberOfMemoryRanges;
        MemoryRange MemoryRanges[];
	} ;

    struct MemoryRangeCapsuleResult
	{
	public:
		UINT64 FirmwareMemoryRequirement;
		UINT64 NumberOfMemoryRanges;
	};
}
