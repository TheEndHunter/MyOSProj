#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>

namespace Common::Debugging
{
	typedef void (*LOGDEBUGMSG)(const CHAR16* message);
	typedef void (*LOGINFOMSG)(const CHAR16* message);
	typedef void (*LOGWARNINGMSG)(const CHAR16* message);
	typedef void (*LOGERRORMSG)(const CHAR16* message);
	typedef void (*LOGCRITICALMSG)(const CHAR16* message);


	struct Debugger
	{
	public:
		Debugger(EFI::EFI_SYSTEM_TABLE* sysTable)
		{
			_sysTbl = sysTable;
		}

		void PrintDebugLine(const CHAR16* msg) const;
		void PrintInfoLine(const CHAR16* msg) const;
		void PrintWarningLine(const CHAR16* msg) const;
		void PrintErrorLine(const CHAR16* msg) const;
		void PrintCriticalLine(const CHAR16* msg) const;

		void PrintDebug(const CHAR16* msg) const;
		void PrintInfo(const CHAR16* msg) const;
		void PrintWarning(const CHAR16* msg) const;
		void PrintError(const CHAR16* msg) const;
		void PrintCritical(const CHAR16* msg) const;

	private:
		EFI::EFI_SYSTEM_TABLE* _sysTbl;
	};
}