#include "EFIDebugger.h"

namespace Common::Debugging
{
	EfiDebugger::EfiDebugger(EFI::EFI_HANDLE imgHndl, EFI::EFI_SYSTEM_TABLE* systbl)
	{
		_imgHandle = imgHndl;
		_sysTable = systbl;		
	}

	void EfiDebugger::Log(const CHAR* message)
	{

	}

	void EfiDebugger::Log(const CHAR8* message)
	{

	}

	void EfiDebugger::Log(const CHAR16* message)
	{

	}

	void EfiDebugger::Log(const CHAR* message, const CHAR* file, const CHAR* function, int line)
	{

	}

	void EfiDebugger::Log(const CHAR8* message, const CHAR8* file, const CHAR8* function, int line)
	{

	}

	void EfiDebugger::Log(const CHAR16* message, const CHAR16* file, const CHAR16* function, int line)
	{

	}

	void EfiDebugger::Assert(bool condition, const CHAR* message)
	{

	}

	void EfiDebugger::Assert(bool condition, const CHAR8* message)
	{

	}

	void EfiDebugger::Assert(bool condition, const CHAR16* message)
	{

	}

	void EfiDebugger::Assert(bool condition, const CHAR* message, const CHAR* file, const CHAR* function, int line)
	{

	}

	void EfiDebugger::Assert(bool condition, const CHAR8* message, const CHAR8* file, const CHAR8* function, int line)
	{

	}

	void EfiDebugger::Assert(bool condition, const CHAR16* message, const CHAR16* file, const CHAR16* function, int line)
	{

	}
}