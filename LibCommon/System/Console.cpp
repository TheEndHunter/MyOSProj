#include "Console.h"
#include "Graphics/Colour.h"
#include "Graphics/RenderContext.h"
#include "TypeDefs.h"

namespace Common::System
{
	Console::Console(Graphics::RenderContext* c)
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

	void Console::SetCursorPosition(UINT32 x, UINT32 y)
	{
	}

	void Console::SetCursorPosition(Common::Numerics::Vect2D<UINT32> pos)
	{
	}

	void Console::SetCursorVisibility(BOOLEAN visible)
	{
	}

	Common::Numerics::Vect2D<UINT32> Console::GetCursorPosition()
	{
		return Common::Numerics::Vect2D<UINT32>();
	}

	BOOLEAN Console::GetCursorVisibility()
	{
		return BOOLEAN();
	}

	UINT64 Console::GetScreenCharWidth()
	{
		return UINT64();
	}

	UINT64 Console::GetScreenCharHeight()
	{
		return UINT64();
	}

	Console::~Console()
	{
	}
}