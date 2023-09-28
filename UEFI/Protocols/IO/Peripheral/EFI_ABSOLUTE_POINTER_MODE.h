#pragma once
#include <UEFIDef.h>

namespace EFI
{
	const UINT32 EFI_ABSP_SupportsAltActive = 0x00000001;
	const UINT32 EFI_ABSP_SupportsPressureAsZ = 0x00000002;

	struct EFI_ABSOLUTE_POINTER_MODE
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
