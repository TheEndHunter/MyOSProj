#pragma once
#include <UEFIDef.h>

namespace EFI
{
	enum class EfiForegroundColor : UINT8
	{
		BLACK = 0x00,
		BLUE = 0x01,
		GREEN = 0x02,
		CYAN = 0x03,
		RED = 0x04,
		MAGENTA = 0x05,
		BROWN = 0x06,
		LIGHTGRAY = 0x07,
		BRIGHT = 0x08,
		DARKGRAY = 0x08,
		LIGHTBLUE = 0x09,
		LIGHTGREEN = 0x0A,
		LIGHTCYAN = 0x0B,
		LIGHTRED = 0x0C,
		LIGHTMAGENTA = 0x0D,
		YELLOW = 0x0E,
		WHITE = 0x0F

	};

	enum class EfiBackgroundColor : UINT8
	{
		BLACK = 0x00,
		BLUE = 0x10,
		GREEN = 0x20,
		CYAN = 0x30,
		RED = 0x40,
		MAGENTA = 0x50,
		BROWN = 0x60,
		LIGHTGRAY = 0x70,
	};

	constexpr UINT8 operator | (const EfiForegroundColor fore, const EfiBackgroundColor back)
	{
			return static_cast<UINT8>(fore) | static_cast<UINT8>(back);
	}
	

	class EfiConsoleColor
	{
	public:
		static const UINT8 _Success = EfiForegroundColor::GREEN | EfiBackgroundColor::BLACK;
		static const UINT8 _Default = EfiForegroundColor::WHITE | EfiBackgroundColor::BLACK;
		static const UINT8 _Warning = EfiForegroundColor::YELLOW | EfiBackgroundColor::BLACK;
		static const UINT8 _Error = EfiForegroundColor::RED | EfiBackgroundColor::BLACK;
		static const UINT8 _Trace = EfiForegroundColor::LIGHTCYAN | EfiBackgroundColor::BLACK;
		static const UINT8 _Debug = EfiForegroundColor::CYAN | EfiBackgroundColor::BLACK;
		static const UINT8 _Fatal = EfiForegroundColor::WHITE | EfiBackgroundColor::BLUE;
	};
}
