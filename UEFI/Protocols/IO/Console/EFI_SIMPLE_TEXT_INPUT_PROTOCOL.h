#pragma once

#include "UEFIDef.h"
#include "EFI_EVENT.h"
#include "EFI_GUID.h"
#include "EFI_STATUS.h"
#include "Protocols/IO/Peripheral/EFI_INPUT_KEY.h"

namespace EFI
{
	struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

	constinit  const ALIGN(8) EFI::EFI_GUID EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID = { 0x387477c1, 0x69c7, 0x11d2,{ 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b} };

	/*
	* EFI_SIMPLE_TEXT_INPUT_PROTOCOL function Delegates
	*/
	typedef EFI::EFI_STATUS (EFIAPI* EFI_INPUT_RESET)(EFI::EFI_SIMPLE_TEXT_INPUT_PROTOCOL* self, BOOLEAN ExtendedVerification);
	typedef EFI::EFI_STATUS (EFIAPI* EFI_INPUT_READ_KEY)(EFI::EFI_SIMPLE_TEXT_INPUT_PROTOCOL* self, EFI::EFI_INPUT_KEY* Key);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_INPUT_WAIT_FOR_KEY)(EFI::EFI_SIMPLE_TEXT_INPUT_PROTOCOL* self, UINTN* NumberOfKeys, EFI::EFI_INPUT_KEY** Keys);

	struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
	{
	public:
		EFI::EFI_INPUT_RESET Reset;
		EFI::EFI_INPUT_READ_KEY ReadKeyStroke;
		EFI::EFI_EVENT WaitForKey;
	};
}
