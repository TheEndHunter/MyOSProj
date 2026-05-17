#pragma once
#include "UEFIDef.h"
#include "Event.h"

namespace Efi
{
	typedef VOID (EFIAPI* EventNotify) (IN Event e,IN VOID* Context);
}
