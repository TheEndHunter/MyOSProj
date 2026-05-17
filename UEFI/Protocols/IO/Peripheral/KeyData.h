#pragma once
#include "InputKey.h"
#include <Protocols/IO/Peripheral/KeyState.h>

namespace Efi
{
	struct KeyData
	{
	public:
		InputKey Key;
		KeyState KeyState;
	};
}
