#pragma once
#include <Guid.h>
#include <Protocols/Debug/DebugImageInfo.h>

namespace Efi
{
    constinit  const ALIGN(8) Efi::Guid DebugImageInfoTableGuid = { 0x49152E77,0x1ADA,0x4764, {0xB7,0xA2,0x7A,0xFE,0xFE,0xD9,0x5E,0x8B } };

    CONST UINT8 DebugImageInfoUpdateInProgress = 0x01;
    CONST UINT8 DebugImageInfoTableModified = 0x02;

    typedef struct  DebugImageInfoTableHeader 
	{
	public:
		volatile UINT32 UpdateStatus;
		UINT32 TableSize;
        DebugImageInfo* DebugImageInfoTable;
	};
}
