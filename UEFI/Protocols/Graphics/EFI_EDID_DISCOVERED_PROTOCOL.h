#pragma once
#include "UEFIDef.h"
#include "EFI_GUID.h"
#include "EFI_HANDLE.h"
#include "EFI_STATUS.h"

namespace EFI
{
	constinit const EFI_GUID EFI_EDID_DISCOVERED_PROTOCOL_GUID = { 0x1c0c34f6,0xd380,0x41fa,{0xa0,0x49,0x8a,0xd0,0x6c,0x1a,0x66,0xaa }};
	constinit const EFI_GUID EFI_EDID_ACTIVE_PROTOCOL_GUID = {0xbd8c1056,0x9f36,0x44ec,{0x92,0xa8,0xa6,0x33,0x7f,0x81,0x79,0x86}};
	constinit const EFI_GUID EFI_EDID_OVERRIDE_PROTOCOL_GUID = { 0x48ecb431,0xfb72,0x45c0,{ 0xa9,0x22,0xf4,0x58,0xfe,0x04,0x0b,0xd5 }};

	inline const UINT8 EFI_EDID_OVERRIDE_DONT_OVERRIDE = 0x01;
	inline const UINT8 EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG = 0x02;

	typedef EFI::EFI_STATUS (EFIAPI* EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID) (IN   EFI_EDID_OVERRIDE_PROTOCOL* This,IN   EFI_HANDLE* ChildHandle,OUT  UINT32* Attributes,OUT UINTN* EdidSize,OUT UINT8** Edid);

	struct EFI_EDID_DISCOVERED_PROTOCOL 
	{
	public:
		UINT32 SizeOfEdid;
		UINT8* Edid;
	};

	struct EFI_EDID_ACTIVE_PROTOCOL
	{
	public:
		UINT32 SizeOfEdid;
		UINT8* Edid;
	};

	struct EFI_EDID_OVERRIDE_PROTOCOL
	{
	public:
		EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID GetEdid;
	};
}