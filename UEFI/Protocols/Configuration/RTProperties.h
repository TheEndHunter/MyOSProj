
#pragma once
#include "UEFIDef.h"
#include <Guid.h>

namespace Efi
{
	//
	// RT Properties table GUID
	//
	constinit  const ALIGN(8) Efi::Guid RtPropertiesTableGuid = { 0xeb66918a, 0x7eef, 0x402a,{ 0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9 } };

	struct RtPropertiesTable
	{
	public:
		UINT16 Version;
		UINT16 Length;
		UINT32 RuntimeServicesSupported;
	};

	enum class RtSupportedMask : UINT32
	{
		GetTime = 0x0001,
		SetTime = 0x0002,
		GetWakeupTime = 0x0004,
		SetWakeupTime = 0x0008,
		GetVariable = 0x0010,
		GetNextVariableName = 0x0020,
		SetVariable = 0x0040,
		SetVirtualAddressMap = 0x0080,
		ConvertPointer = 0x0100,
		GetNextHighMonotonicCount = 0x0200,
		ResetSystem = 0x0400,
		UpdateCapsule = 0x0800,
		QueryCapsuleCapabilities = 0x1000,
		QueryVariableInfo = 0x2000,
	};
}