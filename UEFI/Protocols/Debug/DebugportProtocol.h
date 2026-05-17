﻿#pragma once
#include "UEFIDef.h"
#include <Guid.h>
#include <Status.h>

namespace Efi
{
    struct DebugportProtocol;

    constinit  const ALIGN(8) Efi::Guid DebugportProtocolGuid = { 0xEBA4E8D2,0x3858,0x41EC, {0xA2,0x81,0x26,0x47,0xBA,0x96,0x60,0xD0} };
    const Guid DevicePathMessagingDebugportGuid = DebugportProtocolGuid;
    const Guid DebugportVariableGuid = DebugportProtocolGuid;
    const CHAR16* DebugportVariableName = u"DEBUGPORT";

    typedef Status (EFIAPI* DebugportResetFunc) (IN DebugportProtocol* This);

    typedef Status(EFIAPI* DebugportWriteFunc) (IN DebugportProtocol* This,
		IN UINT32 Timeout, IN OUT UINTN* BufferSize,IN VOID* Buffer);
	
    typedef Status (EFIAPI* DebugportReadFunc) (IN DebugportProtocol* This,
		IN UINT32 Timeout, IN OUT UINTN* BufferSize, OUT VOID* Buffer);

    typedef Status(EFIAPI* DebugportPollFunc) (IN DebugportProtocol* This);

    struct DebugportProtocol
	{
	public:
        DebugportResetFunc Reset;
        DebugportWriteFunc Write;
        DebugportReadFunc Read;
        DebugportPollFunc Poll;
	} ;
}