#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_TIME
	{
	public:
		UINT16 Year;
		UINT8 Month;
		UINT8 Day;
		UINT8 Hour;
		UINT8 Minute;
		UINT8 Second;
		UINT8 Pad1;
		UINT32 Nanosecond;
		INT16 TimeZone;
		UINT8 Daylight;
		UINT8 Pad2;
	};

	//***************************************************
	// Bit Definitions for EFI_TIME.Daylight. See below.
	//***************************************************
	inline const UINT8 EFI_TIME_ADJUST_DAYLIGHT = 0x01;
	inline const UINT8 EFI_TIME_IN_DAYLIGHT = 0x02;

	//***************************************************
	// Value Definition for EFI_TIME.TimeZone. See below.
	//***************************************************
	inline const INT16 EFI_UNSPECIFIED_TIMEZONE = 0x07FF;

	
}
