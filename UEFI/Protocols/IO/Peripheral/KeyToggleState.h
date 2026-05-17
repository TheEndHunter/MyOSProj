#pragma once
#include "UEFIDef.h"

namespace Efi
{
	enum class KeyToggleState : UINT8
	{
		ScrollLockActive = 0x01,
		NumLockActive = 0x02,
		CapsLockActive = 0x04,
		KeyStateExposed = 0x40,
		ToggleStateValid = 0x80,
	};
}
