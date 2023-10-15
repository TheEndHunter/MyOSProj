#pragma once
#include <TypeDefs.h>

namespace Common::Math
{
	INTN Absolute(INTN num)
	{
		return num >= 0 ? num : -num;
	}

	INTN Min(INTN a, INTN b)
	{
		return a < b ? a : b;
	}

	INTN Max(INTN a, INTN b)
	{
		return a > b ? a : b;
	}

	INTN Clamp(INTN value, INTN min, INTN max)
	{
		return value < min ? min : value > max ? max : value;
	}

	INTN Sign(INTN value)
	{
		return value > 0 ? 1 : value < 0 ? -1 : 0;
	}

	UINTN Min(UINTN a, UINTN b)
	{
		return a < b ? a : b;
	}

	UINTN Max(UINTN a, UINTN b)
	{
		return a > b ? a : b;
	}

	UINTN Clamp(UINTN value, UINTN min, UINTN max)
	{
		return value < min ? min : value > max ? max : value;
	}
}
