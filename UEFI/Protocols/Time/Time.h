#pragma once
#include "UEFIDef.h"

namespace Efi
{
	struct Time
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

		BOOLEAN operator ==(const Time& right)
		{
			/*Compare all members for equality, if one fails return FALSE, otherwise return TRUE*/

			if (Year != right.Year)
				return FALSE;

			if (Month != right.Month)
				return FALSE;

			if (Day != right.Day)
				return FALSE;

			if (Hour != right.Hour)
				return FALSE;

			if (Minute != right.Minute)
				return FALSE;

			if (Second != right.Second)
				return FALSE;

			if (Pad1 != right.Pad1)
				return FALSE;

			if (Nanosecond != right.Nanosecond)
				return FALSE;

			if (TimeZone != right.TimeZone)
				return FALSE;

			if (Daylight != right.Daylight)
				return FALSE;

			if (Pad2 != right.Pad2)
				return FALSE;

			return TRUE;
		}

		BOOLEAN operator !=(const Time& right)
		{
			return !(*this == right);
		}
	};

	//***************************************************
	// Bit Definitions for Time.Daylight. See below.
	//***************************************************
    CONST UINT8 TimeAdjustDaylight = 0x01;
    CONST UINT8 TimeInDaylight = 0x02;

	//***************************************************
	// Value Definition for Time.TimeZone. See below.
	//***************************************************
    CONST INT16 UnspecifiedTimezone = 0x07FF;

}
