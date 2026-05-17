#pragma once

#include <UEFIDef.h>
#include <Guid.h>
#include <Event.h>
#include <Status.h>
#include "AbsolutePointerMode.h"
#include "AbsolutePointerState.h"

namespace Efi
{
    struct AbsolutePointerProtocol;
    constinit  const ALIGN(8) Efi::Guid AbsolutePointerProtocolGuid = {0x8D59D32B, 0xC655, 0x4AE9, {0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43}};

    typedef Status(EFIAPI* AbsolutePointerReset) (IN AbsolutePointerProtocol* This,IN BOOLEAN ExtendedVerification);
    typedef Status(EFIAPI* AbsolutePointerGetState) (IN AbsolutePointerProtocol* This,OUT AbsolutePointerState* State);

    struct AbsolutePointerProtocol
	{
	public:
        AbsolutePointerReset Reset;
        AbsolutePointerGetState GetState;
		Event WaitForInput;
        AbsolutePointerMode* Mode;
	};
}