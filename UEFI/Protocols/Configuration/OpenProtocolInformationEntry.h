#pragma once
#include "UEFIDef.h"
#include <Handle.h>


namespace Efi
{
	struct OpenProtocolInformationEntry
	{
	public:
		Handle AgentHandle;
		Handle ControllerHandle;
		UINT32 Attributes;
		UINT32 OpenCount;
	} ;
}