#pragma once

#include <TypeDefs.h>

namespace Common::Graphics
{
	struct Pixel
	{
	public:
		const Pixel()
		{
			B1 = 0;
			B2 = 0;
			B3 = 0;
			B4 = 0;
		}

		const Pixel(UINT8 b1, UINT8 b2, UINT8 b3, UINT8 b4)
		{
			B1 = b1;
			B2 = b2;
			B3 = b3;
			B4 = b4;
		}

		UINT8 B1;
		UINT8 B2;
		UINT8 B3;
		UINT8 B4;
	};
}
