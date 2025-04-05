#include <System/Console.h>
#include <System/Environment/Unicode.h>
#include <Numerics/Math.h>

namespace Common::System
{
	Common::Numerics::Vect2D<UINT32> Empty_V2DU32 = Common::Numerics::Vect2D<UINT32>();

	Console::Console(Graphics::RenderContext* c, ConsoleColour backgroundDefault, ConsoleColour foregroundDefault, Graphics::Font::PCSF::PCSF1* pcsf1)
	{
		_context = c;
		_context->SetPCSF1Font(pcsf1);
		_pcsf1 = pcsf1;
		_pcsf2 = nullptr;

		_bgColour = backgroundDefault;
		_bgColourDefault = backgroundDefault;
		_fgColour = foregroundDefault;
		_fgColourDefault = foregroundDefault;

		_cursorPos = Empty_V2DU32;

		_usePCSF1 = TRUE;
		_usePCSF2 = FALSE;
		_cursorVisible = FALSE;
	}

	Console::Console(Graphics::RenderContext* c, ConsoleColour backgroundDefault, ConsoleColour foregroundDefault, Graphics::Font::PCSF::PCSF2* pcsf2)
	{
		_context = c;
		_context->SetPCSF2Font(pcsf2);
		_pcsf1 = nullptr;
		_pcsf2 = pcsf2;
		_bgColour = backgroundDefault;
		_bgColourDefault = backgroundDefault;
		_fgColour = foregroundDefault;
		_fgColourDefault = foregroundDefault;
		_cursorPos = Empty_V2DU32;
		
		_usePCSF1 = FALSE;
		_usePCSF2 = TRUE;
		_cursorVisible = FALSE;
	}

	Console::Console(Graphics::RenderContext* c, ConsoleColour backgroundDefault, ConsoleColour foregroundDefault, Graphics::Font::PCSF::PCSF1* pcsf1, Graphics::Font::PCSF::PCSF2* pcsf2)
	{
		_context = c;
		_context->SetPCSF1Font(pcsf1);
		_context->SetPCSF2Font(pcsf2);
		_pcsf1 = pcsf1;
		_pcsf2 = pcsf2;
		_bgColour = backgroundDefault;
		_bgColourDefault = backgroundDefault;
		_fgColour = foregroundDefault;
		_fgColourDefault = foregroundDefault;
		_cursorPos = Empty_V2DU32;
		_usePCSF1 = TRUE;
		_usePCSF2 = TRUE;
		_cursorVisible = FALSE;
	}

	void Console::Write(const CHAR16* str)
	{
		if (_context == nullptr)
		{
			return;
		}

		if (_usePCSF1)
		{
			/*Draw each Character, if the max width of the screen is reached, jump to new line*/
			UINT64 width = GetScreenCharWidth();
			UINT64 height = GetScreenCharHeight();
			UINT64 x = _cursorPos.X;
			UINT64 y = _cursorPos.Y;

			for (UINT64 i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == '\n')
				{
					x = 0;
					y+= _pcsf1->Header.CharSize;
				}
				else
				{
					/*Draw the character*/
					_context->DrawPCSF1Char(x, y, str[i]);
					x += _pcsf1->Header.CharSize;
				}

				if (x >= width)
				{
					x = 0;
					y += _pcsf1->Header.CharSize;
				}

				if (y >= height)
				{
					break;
				}
			}
		}
		else
		{
			/*Draw each Character, if the max width of the screen is reached, jump to new line*/
			UINT64 width = GetScreenCharWidth();
			UINT64 height = GetScreenCharHeight();
			UINT64 x = _cursorPos.X;
			UINT64 y = _cursorPos.Y;

			for (UINT64 i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == '\n')
				{
					x = 0;
					y += _pcsf2->Header.Height;
				}
				else
				{
					/*Draw the character*/
					_context->DrawPCSF2Char(x, y, str[i]);
					x += _pcsf2->Header.Width;
				}

				if (x >= width)
				{
					x = 0;
					y += _pcsf2->Header.Height;
				}

				if (y >= height)
				{
					break;
				}
			}
		}
	}

	void Console::WriteLine(const CHAR16* str)
	{
		if (_context == nullptr)
		{
			return;
		}

		Write(str);
		Write(Common::System::Environment::UTF<CHAR16>::NewLine);
	}

	void Console::Write(const CHAR8* str)
	{
		if (_context == nullptr)
		{
			return;
		}
	}

	void Console::WriteLine(const CHAR8* str)
	{
		if (_context == nullptr)
		{
			return;
		}

		Write(str);
		Write(Common::System::Environment::UTF<CHAR8>::NewLine);
	}

	void Console::Write(const CHAR16 c)
	{
		if (_context == nullptr)
		{
			return;
		}

		if (_usePCSF1)
		{
			/*Draw the character*/
			_context->DrawPCSF1Char(_cursorPos.X, _cursorPos.Y, c);
		}
	}

	void Console::WriteLine(const CHAR16 c)
	{
		if (_context == nullptr)
		{
			return;
		}

		Write(c);
		Write(Common::System::Environment::UTF<CHAR16>::NewLine);
	}

	void Console::Write(const CHAR8 c)
	{
		if (_context == nullptr)
		{
			return;
		}

		if (_usePCSF1)
		{
			/*Draw the character*/
			_context->DrawPCSF1Char(_cursorPos.X, _cursorPos.Y, (CHAR16)c);
		}
	}

	void Console::WriteLine(const CHAR8 c)
	{
		if (_context == nullptr)
		{
			return;
		}

		Write(c);
		Write(Common::System::Environment::UTF<CHAR8>::NewLine);
	}

	void Console::SetConsoleColours(ConsoleColour bg, ConsoleColour fg)
	{
		if (_context == nullptr)
		{
			return;
		}

		_bgColour = bg;
		_fgColour = fg;

		_context->SetBackgroundColour(GetColour(_bgColour));
		_context->SetForeground1Colour(GetColour(fg));

	}

	void Console::SetConsoleBackground(ConsoleColour bg)
	{
		if (_context == nullptr)
		{
			return;
		}

		_bgColour = bg;

		_context->SetBackgroundColour(GetColour(_bgColour));
	}

	void Console::SetConsoleForeground(ConsoleColour fg)
	{
		if (_context == nullptr)
		{
			return;
		}

		_fgColour = fg;

		_context->SetForeground1Colour(GetColour(_fgColour));
	}

	void Console::ResetConsoleColour()
	{
		if (_context == nullptr)
		{
			return;
		}

		_bgColour = _bgColourDefault;
		_fgColour = _fgColourDefault;

		_context->SetBackgroundColour(GetColour(_bgColour));
		_context->SetForeground1Colour(GetColour(_fgColour));

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
		if (_context == nullptr)
		{
			return;
		}
	}

	void Console::ClearScreen(ConsoleColour bg)
	{
		if (_context == nullptr)
		{
			return;
		}

		_bgColour = bg;

		_context->SetBackgroundColour(GetColour(bg));
	}

	void Console::ClearScreen(ConsoleColour bg, ConsoleColour fg)
	{
		if (_context == nullptr)
		{
			return;
		}

		_bgColour = bg;
		_fgColour = fg;

		_context->SetBackgroundColour(GetColour(bg));
		_context->SetForeground1Colour(GetColour(fg));

		_context->ClearScreen();


	}

	void Console::SetCursorPosition(UINT32 x, UINT32 y)
	{
		if (_context == nullptr)
		{
			return;
		}

		_cursorPos = Common::Numerics::Vect2D<UINT32>(x, y);
	}

	void Console::SetCursorPosition(Common::Numerics::Vect2D<UINT32> pos)
	{
		if (_context == nullptr)
		{
			return;
		}

		_cursorPos = pos;
	}

	void Console::SetCursorVisibility(BOOLEAN visible)
	{
		if (_context == nullptr)
		{
			return;
		}

		_cursorVisible = visible;
	}

	Common::Numerics::Vect2D<UINT32> Console::GetCursorPosition()
	{
		if (_context == nullptr)
		{
			return Empty_V2DU32;
		}

		return _cursorPos;
	}

	BOOLEAN Console::GetCursorVisibility()
	{
		return _cursorVisible;
	}

	UINT64 Console::GetScreenCharWidth()
	{
		if (_context == nullptr)
		{
			return 0;
		}

		// Get the width of the screen (in pixels)
		UINT64 width = _context->GetWidth();

		if (_pcsf1 == nullptr && _pcsf2 == nullptr)
		{
			return 0;
		}
		else if (_pcsf1 != nullptr && _pcsf2 != nullptr)
		{
			/*get the bigger width of the 2 fonts*/
			return width / Common::Numerics::Math::Max((UINT64)_pcsf1->Header.CharSize, (UINT64)_pcsf2->Header.Width);
		}
		else if(_pcsf1 != nullptr && _pcsf2 == nullptr)
		{
			return width / _pcsf1->Header.CharSize;
		}
		else
		{
			return width / _pcsf2->Header.Width;
		}
	}

	UINT64 Console::GetScreenCharHeight()
	{
		if (_context == nullptr)
		{
			return 0;
		}

		// Get the height of the screen (in pixels)
		UINT64 height = _context->GetHeight();

		if (_pcsf1 == nullptr && _pcsf2 == nullptr)
		{
			return 0;
		}
		else if (_pcsf1 != nullptr && _pcsf2 != nullptr)
		{
			return height / Common::Numerics::Math::Max((UINT64)_pcsf1->Header.CharSize, (UINT64)_pcsf2->Header.Height);
		}
		else if (_pcsf1 != nullptr && _pcsf2 == nullptr)
		{
			return height / _pcsf1->Header.CharSize;
		}
		else
		{
			return height / _pcsf2->Header.Height;
		}
	}

	void Console::UsePCSF1()
	{
		_usePCSF1 = TRUE;
		_usePCSF2 = FALSE;
	}

	void Console::UsePCSF2()
	{
		_usePCSF1 = FALSE;
		_usePCSF2 = TRUE;
	}

	Console::~Console()
	{
	}

	Graphics::Colour GetColour(const ConsoleColour colour)
	{
		switch (colour)
		{
		case ConsoleColour::Black:
			return Graphics::Colours::Black;
		case ConsoleColour::Blue:
			return Graphics::Colours::Blue;
		case ConsoleColour::Green:
			return Graphics::Colours::Green;
		case ConsoleColour::Cyan:
			return Graphics::Colours::Cyan;
		case ConsoleColour::Red:
			return Graphics::Colours::Red;
		case ConsoleColour::Magenta:
			return Graphics::Colours::Magenta;
		case ConsoleColour::Brown:
			return Graphics::Colours::Brown;
		case ConsoleColour::LightGray:
			return Graphics::Colours::LightGray;
		case ConsoleColour::DarkGray:
			return Graphics::Colours::DarkGray;
		case ConsoleColour::LightBlue:
			return Graphics::Colours::LightBlue;
		case ConsoleColour::LightGreen:
			return Graphics::Colours::LightGreen;
		case ConsoleColour::LightCyan:
			return Graphics::Colours::LightCyan;
		case ConsoleColour::LightRed:
			return Graphics::Colours::LightRed;
		case ConsoleColour::LightMagenta:
			return Graphics::Colours::LightMagenta;
		case ConsoleColour::LightBrown:
			return Graphics::Colours::LightBrown;
		case ConsoleColour::White:
			return Graphics::Colours::White;
		default:
			return Graphics::Colours::Black;
		}
	}
}