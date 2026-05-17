#pragma once
#include "UEFIDef.h"

namespace Efi
{
	//******************************************************
	// TimeCapabilities
	//******************************************************
	// This provides the capabilities of the
	// real time clock device as exposed through the EFI interfaces.
	struct TimeCapabilities
	{
	public:
		UINT32 Resolution;
		UINT32 Accuracy;
		BOOLEAN SetsToZero;
	};
}
