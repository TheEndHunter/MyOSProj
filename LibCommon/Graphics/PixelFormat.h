#pragma once

#include <TypeDefs.h>

namespace Common::Graphics
{
	enum PixelFormat : UINT32
	{
		RedGreenBlueReserved8BitPerColor = 0,
		BlueGreenRedReserved8BitPerColor = 1,
		BitMask = 2,
		BltOnly = 3,
		FormatMax = 4
	};
}
