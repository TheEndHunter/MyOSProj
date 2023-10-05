#include "Console.h"
#include "Graphics/Color.h"
#include "Graphics/GraphicsContext.h"
#include <UEFIDef.h>

namespace Bootloader::System
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

	void Console::Write(const CHAR16* str, Graphics::Color c)
	{
	}

	void Console::Write(const CHAR16* fmt, Graphics::Color c, ...)
	{
	}

	void Console::Write(const CHAR16* str, Graphics::Color bg, Graphics::Color fg)
	{
	}

	void Console::Write(const CHAR16* fmt, Graphics::Color bg, Graphics::Color fg, ...)
	{
	}

	void Console::WriteLine(const CHAR16* str)
	{
	}

	void Console::WriteLine(const CHAR16* fmt, ...)
	{
	}

	void Console::WriteLine(const CHAR16* str, Graphics::Color c)
	{
	}

	void Console::WriteLine(const CHAR16* fmt, Graphics::Color c, ...)
	{
	}

	void Console::WriteLine(const CHAR16* str, Graphics::Color bg, Graphics::Color fg)
	{
	}

	void Console::WriteLine(const CHAR16* fmt, Graphics::Color bg, Graphics::Color fg ...)
	{
	}

	void Console::ClearScreen()
	{
	}

	void Console::ClearScreen(Graphics::Color bg)
	{
	}

	void Console::ClearScreen(Graphics::Color bg, Graphics::Color fg)
	{
	}

	Console::~Console()
	{
	}
}