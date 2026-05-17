#pragma once
#include "UEFIDef.h"
#include <Guid.h>

namespace Efi
{
    constinit  const ALIGN(8) Efi::Guid ConformanceProfilesTableGuid = { 0x36122546, 0xf7e7, 0x4c8f,{ 0xbd, 0x9b, 0xeb, 0x85, 0x25, 0xb5, 0x0c, 0x0b} };
    constinit  const ALIGN(8) Efi::Guid ConformanceProfilesUefiSpecGuid = {0x523c91af, 0xa195, 0x4382,{ 0x81, 0x8d, 0x29, 0x5f, 0xe4, 0x00, 0x64, 0x65}};
    CONST UINT16 ConformanceProfilesTableVersion = 0x0001;

    typedef struct ConformanceProfilesTable
	{
	public:
		UINT16   Version;
		UINT16   NumberOfProfiles;
		//Guid* ConformanceProfiles;
	} ;
}