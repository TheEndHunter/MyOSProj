#pragma once

#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include "Event.h"
#include <Protocols/IO/Peripheral/KeyData.h>
#include <Protocols/IO/Peripheral/KeyToggleState.h>


namespace Efi
{
	struct SimpleTextInputExProtocol;

    constinit  const ALIGN(8) Efi::Guid SimpleTextInputExProtocolGuid = { 0xdd9e7534, 0x7762, 0x4698,{ 0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa} };

	typedef Status (EFIAPI* InputReadResetEXFunc)  (IN Efi::SimpleTextInputExProtocol* This, IN BOOLEAN ExtendedVerification);
	typedef Status (EFIAPI* InputReadKeyEXFunc ) (IN Efi::SimpleTextInputExProtocol* This, OUT Efi::KeyData* KeyData);
	typedef Status (EFIAPI* SetStateFunc) (IN Efi::SimpleTextInputExProtocol* This,IN Efi::KeyToggleState* KeyToggleState);

	typedef Status(EFIAPI* KeyNotifyFunc) (IN Efi::KeyData* KeyData);
	typedef Status (EFIAPI* RegisterKeyStrokeNotifyFunc) (IN Efi::SimpleTextInputExProtocol* This,IN Efi::KeyData* KeyData,IN Efi::KeyNotifyFunc KeyNotificationFunction,OUT VOID** NotifyHandle);
	typedef Status(EFIAPI* UnregisterKeyStrokeNotifyFunc) (IN Efi::SimpleTextInputExProtocol* This,IN VOID* NotificationHandle);

	struct SimpleTextInputExProtocol
	{
	public:
		Efi::InputReadResetEXFunc Reset;
		Efi::InputReadKeyEXFunc ReadKeyStrokeEx;
		Efi::Event WaitForKeyEx;
		Efi::SetStateFunc SetStateFunc;
		Efi::RegisterKeyStrokeNotifyFunc RegisterKeyNotify;
		Efi::UnregisterKeyStrokeNotifyFunc UnregisterKeyNotify;
	};
}