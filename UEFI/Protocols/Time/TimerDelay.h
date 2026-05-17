#pragma once

#include "UEFIDef.h"

namespace Efi
{
	enum class TimerDelay
	{		
		/// <summary>
		///The event’s timer setting is to be cancelled and no timer trigger is to be set.
		/// TriggerTime is ignored when canceling a timer.
		/// </summary>
        Cancel,
		/// <summary>
		/// The event is to be signaled periodically at TriggerTime intervals from the current time.
		///  This is the only timer trigger Type for which the event timer does
		///  not need to be reset for each notification.
		///  All other timer trigger types are “one shot.”
		/// </summary>
        Periodic,
		/// <summary>
		/// The event is to be signaled in TriggerTime 100ns units.
		/// </summary>
        Relative
	};
}