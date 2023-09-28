#pragma once
#include "UEFIDef.h"
#include "EFI_EVENT.h"

namespace EFI
{
	typedef VOID (EFIAPI* EFI_EVENT_NOTIFY) (IN EFI_EVENT Event,IN VOID* Context);
}
