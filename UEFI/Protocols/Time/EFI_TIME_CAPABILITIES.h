#pragma once
#include "UEFIDef.h"

namespace EFI
{
	//******************************************************
	// EFI_TIME_CAPABILITIES
	//******************************************************
	// This provides the capabilities of the
	// real time clock device as exposed through the EFI interfaces.
	struct EFI_TIME_CAPABILITIES
	{
	public:
		UINT32 Resolution;
		UINT32 Accuracy;
		BOOLEAN SetsToZero;
	};
}
