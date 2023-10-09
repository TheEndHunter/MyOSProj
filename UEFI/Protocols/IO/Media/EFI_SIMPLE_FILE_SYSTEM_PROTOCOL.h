#pragma once
#include <UEFIDef.h>
#include <EFI_GUID.h>
#include <EFI_STATUS.h>
#include "EFI_FILE_PROTOCOL.h"

namespace EFI
{
	struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

	constinit const EFI::EFI_GUID EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID{0x0964e5b22,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
	inline const UINT32 EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION = 0x00010000;

	typedef EFI::EFI_STATUS(EFIAPI* EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME) (IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* self,OUT EFI::EFI_FILE_PROTOCOL** root);

	struct EFI_SIMPLE_FILE_PROTOCOL
	{
	public:
		UINT64 Revision;
		EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
	};
}
