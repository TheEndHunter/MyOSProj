#pragma once

#include "UEFIDef.h"

namespace EFI
{
	struct EFI_IPV4_ADDRESS
	{
	public:
		union
		{
		public:
			UINT8 Addr[4];

			UINT8 A;
			UINT8 B;
			UINT8 C;
			UINT8 D;
		};
	};

	struct EFI_IPV6_ADDRESS
	{
	public:
		union
		{
		public:
			UINT8 Addr[16];

			UINT32 A;
			UINT32 B;
			UINT32 C;
			UINT32 D;
		};
	};

	struct EFI_IP_ADDRESS
	{
	public:
		union
		{
		public:
			UINT32 Addr[4];
			EFI::EFI_IPV4_ADDRESS v4;
			EFI::EFI_IPV6_ADDRESS v6;
		};
	};
}