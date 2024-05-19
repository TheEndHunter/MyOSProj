#pragma once
#include <TypeDefs.h>
#include <Debugging/IDebugger.h>
#include <EFI_SYSTEM_TABLE.h>


namespace Common::Debugging
{
	class EfiDebugger : IDebugger
	{
	public:
		EfiDebugger(EFI::EFI_HANDLE imgHndl,EFI::EFI_SYSTEM_TABLE* systbl);

		// Inherited via IDebugger
		void Log(const CCHAR* message) override;

		void Log(const CHAR8* message) override;

		void Log(const CHAR16* message) override;

		void Log(const CCHAR* message, const CCHAR* file, const CCHAR* function, int line) override;

		void Log(const CHAR8* message, const CHAR8* file, const CHAR8* function, int line) override;

		void Log(const CHAR16* message, const CHAR16* file, const CHAR16* function, int line) override;


		void Assert(bool condition, const CCHAR* message) override;

		void Assert(bool condition, const CHAR8* message) override;

		void Assert(bool condition, const CHAR16* message) override;

		void Assert(bool condition, const CCHAR* message, const CCHAR* file, const CCHAR* function, int line) override;

		void Assert(bool condition, const CHAR8* message, const CHAR8* file, const CHAR8* function, int line) override;

		void Assert(bool condition, const CHAR16* message, const CHAR16* file, const CHAR16* function, int line) override;

	private:
		EFI::EFI_HANDLE _imgHandle;
		EFI::EFI_SYSTEM_TABLE* _sysTable;
	};
}