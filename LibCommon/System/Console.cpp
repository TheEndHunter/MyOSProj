#include "Console.h"
#include "Graphics/Colour.h"
#include "Graphics/GraphicsContext.h"
#include "TypeDefs.h"

namespace Common::System
{
	Console::Console(Graphics::GraphicsContext* c)
	{
		context = c;
	}

	void Console::Write(const CHAR16* str)
	{
	}

	void Console::Write(const CHAR16* fmt, ...)
	{
	}

	void Console::Write(const CHAR16* str, Graphics::Colour c)
	{
	}

	void Console::Write(const CHAR16* fmt, Graphics::Colour c, ...)
	{
	}

	void Console::Write(const CHAR16* str, Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	void Console::Write(const CHAR16* fmt, Graphics::Colour bg, Graphics::Colour fg, ...)
	{
	}

	void Console::WriteLine(const CHAR16* str)
	{
	}

	void Console::WriteLine(const CHAR16* fmt, ...)
	{
	}

	void Console::WriteLine(const CHAR16* str, Graphics::Colour c)
	{
	}

	void Console::WriteLine(const CHAR16* fmt, Graphics::Colour c, ...)
	{
	}

	void Console::WriteLine(const CHAR16* str, Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	void Console::WriteLine(const CHAR16* fmt, Graphics::Colour bg, Graphics::Colour fg ...)
	{
	}

	void Console::Write(const CHAR8* str)
	{
	}

	void Console::Write(const CHAR8* fmt, ...)
	{
	}

	void Console::Write(const CHAR8* str, Graphics::Colour c)
	{
	}

	void Console::Write(const CHAR8* fmt, Graphics::Colour c, ...)
	{
	}

	void Console::Write(const CHAR8* str, Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	void Console::Write(const CHAR8* fmt, Graphics::Colour bg, Graphics::Colour fg, ...)
	{
	}

	void Console::WriteLine(const CHAR8* str)
	{
	}

	void Console::WriteLine(const CHAR8* fmt, ...)
	{
	}

	void Console::WriteLine(const CHAR8* str, Graphics::Colour c)
	{
	}

	void Console::WriteLine(const CHAR8* fmt, Graphics::Colour c, ...)
	{
	}

	void Console::WriteLine(const CHAR8* str, Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	void Console::WriteLine(const CHAR8* fmt, Graphics::Colour bg, Graphics::Colour fg ...)
	{
	}

	void Console::Write(const CCHAR str)
	{
	}

	void Console::Write(const CCHAR fmt, ...)
	{
	}

	void Console::Write(const CCHAR str, Graphics::Colour bg)
	{
	}

	void Console::Write(const CCHAR fmt, Graphics::Colour bg, ...)
	{
	}

	void Console::Write(const CCHAR str, Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	void Console::Write(const CCHAR fmt, Graphics::Colour bg, Graphics::Colour fg, ...)
	{
	}

	void Console::WriteLine(const CCHAR str)
	{
	}

	void Console::WriteLine(const CCHAR fmt, ...)
	{
	}

	void Console::WriteLine(const CCHAR str, Graphics::Colour bg)
	{
	}

	void Console::WriteLine(const CCHAR fmt, Graphics::Colour bg, ...)
	{
	}

	void Console::WriteLine(const CCHAR str, Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	void Console::WriteLine(const CCHAR fmt, Graphics::Colour bg, Graphics::Colour fg ...)
	{
	}

	CHAR16 Console::ReadKey()
	{
		return '\0';
	}

	CHAR16* Console::ReadLine()
	{
		return nullptr;
	}

	void Console::ClearScreen()
	{
	}

	void Console::ClearScreen(Graphics::Colour bg)
	{
	}

	void Console::ClearScreen(Graphics::Colour bg, Graphics::Colour fg)
	{
	}

	Console::~Console()
	{
	}
}