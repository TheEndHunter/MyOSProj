#pragma once
#include "EFI_KEY_SHIFT_STATE.h"
#include "EFI_KEY_TOGGLE_STATE.h"

namespace EFI
{
	struct EFI_KEY_STATE
	{
	public:
		EFI_KEY_SHIFT_STATE KeyShiftState;
		EFI_KEY_TOGGLE_STATE KeyToggleState;
	};
}
