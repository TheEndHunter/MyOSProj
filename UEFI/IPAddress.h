#pragma once

#include "UEFIDef.h"

namespace Efi
{
	struct IPV4Address
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

	struct IPV6Address
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

	struct IPAddress
	{
	public:
		union
		{
		public:
			UINT32 Addr[16];
			Efi::IPV4Address v4;
			Efi::IPV6Address v6;
		};
	};
}