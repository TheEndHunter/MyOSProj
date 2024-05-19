#pragma once
#include <TypeDefs.h>

namespace Common::Debugging
{
	class IDebugger
	{
	public:
		virtual void Log(const CCHAR* message) = 0;
		virtual void Log(const CHAR8* message) = 0;
		virtual void Log(const CHAR16* message) = 0;
		virtual void Log(const CCHAR* message, const CCHAR* file, const CCHAR* function, int line) = 0;
		virtual void Log(const CHAR8* message, const CHAR8* file, const CHAR8* function, int line) = 0;
		virtual void Log(const CHAR16* message, const CHAR16* file, const CHAR16* function, int line) = 0;


		virtual void Assert(bool condition, const CCHAR* message) = 0;
		virtual void Assert(bool condition, const CHAR8* message) = 0;
		virtual void Assert(bool condition, const CHAR16* message) = 0;

		virtual void Assert(bool condition, const CCHAR* message, const CCHAR* file, const CCHAR* function, int line) = 0;
		virtual void Assert(bool condition, const CHAR8* message, const CHAR8* file, const CHAR8* function, int line) = 0;
		virtual void Assert(bool condition, const CHAR16* message, const CHAR16* file, const CHAR16* function, int line) = 0;
	};
}