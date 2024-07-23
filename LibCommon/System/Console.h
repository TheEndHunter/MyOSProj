#pragma once
#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/RenderContext.h>
#include <Numerics/Vectors.h>
#include <Graphics/Font/PCSF/PCSF1.h>
#include <Graphics/Font/PCSF/PCSF2.h>


namespace Common::System
{
	enum class ConsoleColour : UINT8
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		LightBrown = 14,
		White = 15
	};

	Graphics::Colour GetColour(const ConsoleColour colour);

	class Console
	{
	public:
		Console(Graphics::RenderContext* c,ConsoleColour backgroundDefault,ConsoleColour foregroundDefault, Graphics::Font::PCSF::PCSF1* pcsf1);
		Console(Graphics::RenderContext* c,ConsoleColour backgroundDefault,ConsoleColour foregroundDefault, Graphics::Font::PCSF::PCSF2* pcsf2);
		Console(Graphics::RenderContext* c,ConsoleColour backgroundDefault,ConsoleColour foregroundDefault, Graphics::Font::PCSF::PCSF1* pcsf1, Graphics::Font::PCSF::PCSF2* pcsf2);

		void Write(const CHAR16* str);
		void WriteLine(const CHAR16* str);
		void Write(const CHAR8* str);
		void WriteLine(const CHAR8* str);
		void Write(const CHAR16 c);
		void WriteLine(const CHAR16 c);
		void Write(const CHAR8 c);
		void WriteLine(const CHAR8 c);


		void SetConsoleColours(ConsoleColour bg, ConsoleColour fg);
		void SetConsoleBackground(ConsoleColour bg);
		void SetConsoleForeground(ConsoleColour fg);
		void ResetConsoleColour();

		CHAR16 ReadKey();
		CHAR16* ReadLine();

		void ClearScreen();
		void ClearScreen(ConsoleColour bg);
		void ClearScreen(ConsoleColour bg, ConsoleColour fg);

		void SetCursorPosition(UINT32 x, UINT32 y);
		void SetCursorPosition(Numerics::Vect2D<UINT32> pos);
		void SetCursorVisibility(BOOLEAN visible);
		Common::Numerics::Vect2D<UINT32> GetCursorPosition();
		BOOLEAN GetCursorVisibility();

		UINT64 GetScreenCharWidth();
		UINT64 GetScreenCharHeight();

		void UsePCSF1();
		void UsePCSF2();

		~Console();
	protected:
		Numerics::Vect2D<UINT32> _cursorPos;
		Graphics::RenderContext* _context;
		Graphics::Font::PCSF::PCSF1* _pcsf1;
		Graphics::Font::PCSF::PCSF2* _pcsf2;
		ConsoleColour _bgColour;
		ConsoleColour _fgColour;
		ConsoleColour _bgColourDefault;
		ConsoleColour _fgColourDefault;
		BOOLEAN _cursorVisible;
		BOOLEAN _usePCSF1;
		BOOLEAN _usePCSF2;
	};
}