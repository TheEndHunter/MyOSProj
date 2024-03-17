#pragma once

#include <TypeDefs.h>

namespace Common::Graphics
{
	enum PixelFormat : UINT32
	{
		RedGreenBlueReserved8BitPerColor,
		BlueGreenRedReserved8BitPerColor,
		BitMask,
		BltOnly,
		FormatMax
	};
}
