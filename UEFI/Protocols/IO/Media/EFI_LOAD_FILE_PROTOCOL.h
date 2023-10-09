#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/IO/EFI_DEVICE_PATH_PROTOCOL.h>

namespace EFI
{
	struct EFI_LOAD_FILE_PROTOCOL;

	constinit const EFI::EFI_GUID EFI_LOAD_FILE_PROTOCOL_GUID{ 0x56EC3091,0x954C,0x11d2,{0x8e,0x3f,0x00,0xa0, 0xc9,0x69,0x72,0x3b} };

	typedef EFI::EFI_STATUS (EFIAPI* EFI_LOAD_FILE) (EFI_LOAD_FILE_PROTOCOL* self, EFI::EFI_DEVICE_PATH_PROTOCOL* filePath, BOOLEAN bootPolicy, UINTN* bufferSize, VOID* buffer);

	struct EFI_LOAD_FILE_PROTOCOL
	{
	public:
		EFI_LOAD_FILE LoadFile;
	};
}