#pragma once
#include <UEFIDef.h>
#include "Graphics\Color.h"
#include <Graphics/GraphicsContext.h>

namespace Bootloader::System
{
	class Console
	{
	public:
		Console(Graphics::GraphicsContext* c);

		void Write(const CHAR16* str);
		void Write(const CHAR16* fmt, ...);
		void Write(const CHAR16* str, Graphics::Color bg);
		void Write(const CHAR16* fmt, Graphics::Color bg, ...);
		void Write(const CHAR16* str, Graphics::Color bg, Graphics::Color fg);
		void Write(const CHAR16* fmt, Graphics::Color bg,Graphics::Color fg, ...);
		void WriteLine(const CHAR16* str);
		void WriteLine(const CHAR16* fmt,...);
		void WriteLine(const CHAR16* str, Graphics::Color bg);
		void WriteLine(const CHAR16* fmt, Graphics::Color bg, ...);
		void WriteLine(const CHAR16* str, Graphics::Color bg, Graphics::Color fg);
		void WriteLine(const CHAR16* fmt, Graphics::Color bg,Graphics::Color fg ...);

		void ClearScreen();
		void ClearScreen(Graphics::Color bg);
		void ClearScreen(Graphics::Color bg, Graphics::Color fg);

		~Console();
	private:
		Graphics::GraphicsContext* context;
	};
}

