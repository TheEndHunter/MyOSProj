#pragma once
#include <UEFIDef.h>
#include <Guid.h>
#include <Status.h>
#include "FileProtocol.h"

namespace Efi
{
	struct SimpleFileSystemProtocol;

	constinit const ALIGN(8) Efi::Guid SimpleFileSystemProtocol_GUID{0x0964e5b22,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
	CONST UINT32 SimpleFileSystemProtocol_REVISION = 0x00010000;

	typedef Status(EFIAPI* SimpleFileSystemProtocolOpenVolume) (IN SimpleFileSystemProtocol* self,OUT Efi::FileProtocol** root);

	struct SimpleFileSystemProtocol
	{
	public:
		UINT64 Revision;
		SimpleFileSystemProtocolOpenVolume OpenVolume;
	};
}
