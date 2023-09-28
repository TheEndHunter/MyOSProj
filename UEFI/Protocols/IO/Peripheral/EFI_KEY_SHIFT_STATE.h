#pragma once
#include "UEFIDef.h"

namespace EFI
{
	enum class EFI_KEY_SHIFT_STATE : UINT32
	{
		EFI_RIGHT_SHIFT_PRESSED = 0x00000001,
		EFI_LEFT_SHIFT_PRESSED = 0x00000002,
		EFI_RIGHT_CONTROL_PRESSED = 0x00000004,
		EFI_LEFT_CONTROL_PRESSED = 0x00000008,
		EFI_RIGHT_ALT_PRESSED = 0x00000010,
		EFI_LEFT_ALT_PRESSED = 0x00000020,
		EFI_RIGHT_LOGO_PRESSED = 0x00000040,
		EFI_LEFT_LOGO_PRESSED = 0x00000080,
		EFI_MENU_KEY_PRESSED = 0x00000100,
		EFI_SYS_REQ_PRESSED = 0x00000200,
		EFI_SHIFT_STATE_VALID = 0x80000000,
	};
}
