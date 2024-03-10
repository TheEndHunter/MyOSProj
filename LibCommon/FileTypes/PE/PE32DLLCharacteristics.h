#pragma once
#include <typedefs.h>

namespace Common::FileTypes::PE
{
	enum PE32DLLCharacteristics : UINT16
	{
		HighEntropyVA = 0x0020,
		DynamicBase = 0x0040,
		ForceIntegrity = 0x0080,
		NxCompat = 0x0100,
		NoIsolation = 0x0200,
		NoSEH = 0x0400,
		NoBind = 0x0800,
		AppContainer = 0x1000,
		WDMDriver = 0x2000,
		GuardCF = 0x4000,
		TerminalServerAware = 0x8000
	};
}
