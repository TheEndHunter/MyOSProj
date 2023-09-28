#pragma once

#include "UEFIDef.h"

namespace EFI
{
	struct EFI_MAC_ADDRESS
	{
	public:
		union
		{
		public:
			UINT8 Addr[32];

			UINT32 A;
			UINT32 B;
			UINT32 C;
			UINT32 D;

			UINT32 E;
			UINT32 F;
			UINT32 G;
			UINT32 H;
		};
	};
}
