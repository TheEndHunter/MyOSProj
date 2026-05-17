#pragma once

#include <UefiDef.h>
#include <Status.h>
#include <Guid.h>
#include <Event.h>
#include "SimplePointerMode.h"
#include "SimplePointerState.h"

namespace Efi
{
    struct SimplePointerProtocol;
    
    constinit  const ALIGN(8) Efi::Guid SimplePointerProtocolGuid = { 0x31878c87, 0xb75, 0x11d5,{ 0x9a, 0x4f, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d }};

    typedef Status (EFIAPI* SimplePointerResetFunc) (IN SimplePointerProtocol* This, IN BOOLEAN ExtendedVerification);
    typedef Status (EFIAPI* SimplePointerGetStateFunc)(IN SimplePointerProtocol* This, OUT Efi::SimplePointerState* State);

    struct SimplePointerProtocol
	{
	public:
        SimplePointerResetFunc Reset;
        SimplePointerGetStateFunc GetState;
		Efi::Event WaitForInput;
        Efi::SimplePointerState* Mode;
	};
}
