#pragma once
#include "EFI_GUID.h"
#include "EFI_LOAD_FILE_PROTOCOL.h"

namespace EFI
{
	struct EFI_LOAD_FILE2_PROTOCOL;

	constinit const EFI::EFI_GUID EFI_LOAD_FILE2_PROTOCOL_GUID{ 0x4006c0c1, 0xfcb3, 0x403e,{ 0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d } };

	typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE2_PROTOCOL;

	struct EFI_LOAD_FILE2_PROTOCOL
	{
	public:
		EFI_LOAD_FILE LoadFile;
	};
}