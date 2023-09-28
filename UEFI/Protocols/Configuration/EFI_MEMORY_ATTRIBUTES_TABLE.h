#pragma once
#include "UEFIDef.h"
#include "EFI_GUID.h"

namespace EFI
{
	constinit const EFI_GUID EFI_MEMORY_ATTRIBUTES_TABLE_GUID = { 0xdcfa911d, 0x26eb, 0x469f,{0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20}};
	/// <summary>
	/// BIT0 implies that Runtime code includes the forward control flow guard
	/// instruction, such as X86 CET-IBT or ARM BTI. 
	/// </summary>
	const UINT8 EFI_MEMORY_ATTRIBUTES_FLAGS_RT_FORWARD_CONTROL_FLOW_GUARD = (UINT8)0x1;

	struct EFI_MEMORY_ATTRIBUTES_TABLE
	{
	public:
		UINT32                       Version;
		UINT32                       NumberOfEntries;
		UINT32                       DescriptorSize;
		UINT32                       Flags;
		// EFI_MEMORY_DESCRIPTOR     Entry [1] ;
	};
}
