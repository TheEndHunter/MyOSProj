#pragma once
#include <UEFIDef.h>

namespace Efi
{
	CONST UINT32 AbspSupportsAltActive = 0x00000001;
	CONST UINT32 AbspSupportsPressureAsZ = 0x00000002;

	struct AbsolutePointerMode
	{
	public:
		UINT64 AbsoluteMinX;
		UINT64 AbsoluteMinY;
		UINT64 AbsoluteMinZ;
		UINT64 AbsoluteMaxX;
		UINT64 AbsoluteMaxY;
		UINT64 AbsoluteMaxZ;
		UINT32 Attributes;
	};
}
