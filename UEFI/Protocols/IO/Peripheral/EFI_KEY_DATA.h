#pragma once
#include "EFI_INPUT_KEY.h"
#include "EFI_KEY_STATE.h"

namespace EFI
{
	struct EFI_KEY_DATA
	{
	public:
		EFI_INPUT_KEY Key;
		EFI_KEY_STATE KeyState;
	};
}
