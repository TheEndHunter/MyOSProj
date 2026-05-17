#pragma once
#include "UEFIDef.h"
#include <Guid.h>
#include <Handle.h>
#include <Status.h>

namespace Efi
{
    constinit  const ALIGN(8) Efi::Guid EdidDiscoveredProtocolGuid = { 0x1c0c34f6,0xd380,0x41fa,{ 0xa0,0x49,0x8a,0xd0,0x6c,0x1a,0x66,0xaa }};
    constinit  const ALIGN(8) Efi::Guid EdidActiveProtocolGuid =		{ 0xbd8c1056,0x9f36,0x44ec,{ 0x92,0xa8,0xa6,0x33,0x7f,0x81,0x79,0x86 }};
    constinit  const ALIGN(8) Efi::Guid EdidOverrideProtocolGuid =	{ 0x48ecb431,0xfb72,0x45c0,{ 0xa9,0x22,0xf4,0x58,0xfe,0x04,0x0b,0xd5 }};

    CONST UINT8 EdidOverrideDontOverride = 0x01;
    CONST UINT8 EdidOverrideEnableHotPlug = 0x02;

    struct EdidOverrideProtocol;
    typedef Status (EFIAPI* EdidOverrideProtocolGetEdidFunc) (IN   EdidOverrideProtocol* This,IN   Efi::Handle* ChildHandle,OUT  UINT32* Attributes,OUT UINTN* EdidSize,OUT UINT8** Edid);

    struct EdidDiscoveredProtocol 
	{
	public:
		UINT32 SizeOfEdid;
		UINT8* Edid;
	};

    struct EdidActiveProtocol
	{
	public:
		UINT32 SizeOfEdid;
		UINT8* Edid;
	};

    struct EdidOverrideProtocol
	{
	public:
        EdidOverrideProtocolGetEdidFunc GetEdid;
	};
}