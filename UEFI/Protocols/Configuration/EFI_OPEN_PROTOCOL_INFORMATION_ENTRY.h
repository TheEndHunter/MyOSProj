#pragma once
#include "UEFIDef.h"
#include "EFI_HANDLE.h"


namespace EFI
{
	struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
	{
	public:
		EFI_HANDLE AgentHandle;
		EFI_HANDLE ControllerHandle;
		UINT32 Attributes;
		UINT32 OpenCount;
	} ;
}