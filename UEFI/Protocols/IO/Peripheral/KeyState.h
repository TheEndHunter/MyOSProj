#pragma once
#include "KeyShiftState.h"
#include "KeyToggleState.h"

namespace Efi
{
	struct KeyState
	{
	public:
		KeyShiftState ShiftState;
		KeyToggleState ToggleState;
	};
}
