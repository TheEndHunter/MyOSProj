#pragma once
#include "UEFIDef.h"
#include <Guid.h>

namespace Efi
{
    constinit  const ALIGN(8) Efi::Guid MemoryAttributesTableGuid = { 0xdcfa911d, 0x26eb, 0x469f,{0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20}};
	/// <summary>
	/// BIT0 implies that Runtime code includes the forward control flow guard
	/// instruction, such as X86 CET-IBT or ARM BTI. 
	/// </summary>
    CONST UINT8 MemoryAttributesFlagsRtForwardControlFlowGuard = (UINT8)0x1;

    struct MemoryAttributesTable
	{
	public:
		UINT32                       Version;
		UINT32                       NumberOfEntries;
		UINT32                       DescriptorSize;
		UINT32                       Flags;
		// MemoryDescriptor     Entry [1] ;
	};
}
