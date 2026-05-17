#pragma once

#include "UEFIDef.h"
#include "Event.h"
#include <Guid.h>
#include <Status.h>
#include "Protocols/IO/Peripheral/InputKey.h"

namespace Efi
{
	struct SimpleTextInputProtocol;

    constinit  const ALIGN(8) Guid SimpleTextInputProtocolGuid = { 0x387477c1, 0x69c7, 0x11d2,{ 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b} };

	/*
	* SimpleTextInputProtocol function Delegates
	*/
	typedef Status (EFIAPI* InputResetFunc)(SimpleTextInputProtocol* self, BOOLEAN ExtendedVerification);
	typedef Status (EFIAPI* InputReadKeyFunc)(SimpleTextInputProtocol* self, InputKey* Key);
	typedef Status(EFIAPI* InputWaitForKeyFunc)(SimpleTextInputProtocol* self, UINTN* NumberOfKeys, InputKey** Keys);

	struct SimpleTextInputProtocol
	{
	public:
		InputResetFunc Reset;
		InputReadKeyFunc ReadKeyStroke;
		Event WaitForKey;
	};
}
