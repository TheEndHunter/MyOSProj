#pragma once
#include <UEFIDef.h>

namespace Efi
{
	enum class ForegroundColor : UINT8
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

	enum class BackgroundColor : UINT8
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

	constexpr UINT8 operator | (const ForegroundColor fore, const BackgroundColor back)
	{
		return static_cast<UINT8>(fore) | static_cast<UINT8>(back);
	}
	

	class ConsoleColor
	{
	public:
		static const UINT8 _Debug = ForegroundColor::CYAN | BackgroundColor::BLACK;
		static const UINT8 _Default = ForegroundColor::WHITE | BackgroundColor::BLACK;
		static const UINT8 _Error = ForegroundColor::LIGHTRED | BackgroundColor::BLACK;
		static const UINT8 _Fatal = ForegroundColor::RED | BackgroundColor::BLACK;
		static const UINT8 _Info = ForegroundColor::LIGHTGREEN | BackgroundColor::BLACK;
		static const UINT8 _Success = ForegroundColor::GREEN | BackgroundColor::BLACK;
		static const UINT8 _Trace = ForegroundColor::LIGHTCYAN | BackgroundColor::BLACK;
		static const UINT8 _Warning = ForegroundColor::YELLOW | BackgroundColor::BLACK;
	};
}
