#pragma once

#include "UEFIDef.h"

namespace EFI
{
	enum class EFI_TIMER_DELAY
	{		
		/// <summary>
		///The event’s timer setting is to be cancelled and no timer trigger is to be set.
		/// TriggerTime is ignored when canceling a timer.
		/// </summary>
		EFI_TIMER_CANCEL,		
		/// <summary>
		/// The event is to be signaled periodically at TriggerTime intervals from the current time.
		///  This is the only timer trigger Type for which the event timer does
		///  not need to be reset for each notification.
		///  All other timer trigger types are “one shot.”
		/// </summary>
		EFI_TIMER_PERIODIC,		
		/// <summary>
		/// The event is to be signaled in TriggerTime 100ns units.
		/// </summary>
		EFI_TIMER_RELATIVE
	};
}