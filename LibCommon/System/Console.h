#pragma once
#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/GraphicsContext.h>

namespace Common::System
{
	class Console
	{
	public:
		Console(Graphics::GraphicsContext* c);

		void Write(const CHAR16* str);
		void Write(const CHAR16* fmt, ...);
		void Write(const CHAR16* str, Graphics::Colour bg);
		void Write(const CHAR16* fmt, Graphics::Colour bg, ...);
		void Write(const CHAR16* str, Graphics::Colour bg, Graphics::Colour fg);
		void Write(const CHAR16* fmt, Graphics::Colour bg,Graphics::Colour fg, ...);

		void WriteLine(const CHAR16* str);
		void WriteLine(const CHAR16* fmt,...);
		void WriteLine(const CHAR16* str, Graphics::Colour bg);
		void WriteLine(const CHAR16* fmt, Graphics::Colour bg, ...);
		void WriteLine(const CHAR16* str, Graphics::Colour bg, Graphics::Colour fg);
		void WriteLine(const CHAR16* fmt, Graphics::Colour bg,Graphics::Colour fg ...);

		void Write(const CHAR8* str);
		void Write(const CHAR8* fmt, ...);
		void Write(const CHAR8* str, Graphics::Colour bg);
		void Write(const CHAR8* fmt, Graphics::Colour bg, ...);
		void Write(const CHAR8* str, Graphics::Colour bg, Graphics::Colour fg);
		void Write(const CHAR8* fmt, Graphics::Colour bg, Graphics::Colour fg, ...);

		void WriteLine(const CHAR8* str);
		void WriteLine(const CHAR8* fmt, ...);
		void WriteLine(const CHAR8* str, Graphics::Colour bg);
		void WriteLine(const CHAR8* fmt, Graphics::Colour bg, ...);
		void WriteLine(const CHAR8* str, Graphics::Colour bg, Graphics::Colour fg);
		void WriteLine(const CHAR8* fmt, Graphics::Colour bg, Graphics::Colour fg ...);

		void Write(const CCHAR str);
		void Write(const CCHAR fmt, ...);
		void Write(const CCHAR str, Graphics::Colour bg);
		void Write(const CCHAR fmt, Graphics::Colour bg, ...);
		void Write(const CCHAR str, Graphics::Colour bg, Graphics::Colour fg);
		void Write(const CCHAR fmt, Graphics::Colour bg, Graphics::Colour fg, ...);

		void WriteLine(const CCHAR str);
		void WriteLine(const CCHAR fmt, ...);
		void WriteLine(const CCHAR str, Graphics::Colour bg);
		void WriteLine(const CCHAR fmt, Graphics::Colour bg, ...);
		void WriteLine(const CCHAR str, Graphics::Colour bg, Graphics::Colour fg);
		void WriteLine(const CCHAR fmt, Graphics::Colour bg, Graphics::Colour fg ...);

		CHAR16 ReadKey();
		CHAR16* ReadLine();

		void ClearScreen();
		void ClearScreen(Graphics::Colour bg);
		void ClearScreen(Graphics::Colour bg, Graphics::Colour fg);

		~Console();
	private:
		Graphics::GraphicsContext* context;
	};
}