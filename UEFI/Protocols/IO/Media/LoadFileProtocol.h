#pragma once
#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include <Protocols/IO/EFI_DEVICE_PATH_PROTOCOL.h>

namespace Efi
{
	struct EFI_LOAD_FILE_PROTOCOL;

	constinit const ALIGN(8) Efi::Guid EFI_LOAD_FILE_PROTOCOL_GUID{ 0x56EC3091,0x954C,0x11d2,{0x8e,0x3f,0x00,0xa0, 0xc9,0x69,0x72,0x3b} };

	typedef Status (EFIAPI* EFI_LOAD_FILE) (EFI_LOAD_FILE_PROTOCOL* self, Efi::DevicePathProtocol* filePath, BOOLEAN bootPolicy, UINTN* bufferSize, VOID* buffer);

	struct EFI_LOAD_FILE_PROTOCOL
	{
	public:
		EFI_LOAD_FILE LoadFile;
	};
}