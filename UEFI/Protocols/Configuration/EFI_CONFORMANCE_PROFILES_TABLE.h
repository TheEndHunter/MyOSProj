#pragma once
#include "UEFIDef.h"
#include "EFI_GUID.h"

namespace EFI
{
	constinit  const ALIGN(8) EFI::EFI_GUID EFI_CONFORMANCE_PROFILES_TABLE_GUID = { 0x36122546, 0xf7e7, 0x4c8f,{ 0xbd, 0x9b, 0xeb, 0x85, 0x25, 0xb5, 0x0c, 0x0b} };
	constinit  const ALIGN(8) EFI::EFI_GUID EFI_CONFORMANCE_PROFILES_UEFI_SPEC_GUID = {0x523c91af, 0xa195, 0x4382,{ 0x81, 0x8d, 0x29, 0x5f, 0xe4, 0x00, 0x64, 0x65}};
	inline const UINT16 EFI_CONFORMANCE_PROFILES_TABLE_VERSION = 0x0001;

	typedef struct EFI_CONFORMANCE_PROFILES_TABLE
	{
	public:
		UINT16   Version;
		UINT16   NumberOfProfiles;
		//EFI_GUID ConformanceProfiles [];
	} ;
}