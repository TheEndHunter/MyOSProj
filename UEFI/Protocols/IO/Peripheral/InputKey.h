#pragma once
#include "UEFIDef.h"

namespace Efi
{
	struct InputKey
	{
	public:
		InputKey(const UINT16 scanCode = 0,const CHAR16 unicodeChar = 0)
		{
			ScanCode = scanCode;
			UnicodeChar = unicodeChar;
		}

		InputKey(const InputKey& other)
		{
			ScanCode = other.ScanCode;
			UnicodeChar = other.UnicodeChar;
		}

		UINT16 ScanCode;
		CHAR16 UnicodeChar;

		BOOLEAN operator==(const InputKey& other)
		{
			return ScanCode == other.ScanCode && UnicodeChar == other.UnicodeChar;
		}

		BOOLEAN operator!=(const InputKey& other)
		{
			return ScanCode != other.ScanCode || UnicodeChar != other.UnicodeChar;
		}

		BOOLEAN operator==(const CHAR8& other)
		{
			return UnicodeChar == (CHAR16)other;
		}

		BOOLEAN operator!=(const CHAR8& other)
		{
			return !(*this == other);
		}

		BOOLEAN operator==(const CHAR16& other)
		{
			return UnicodeChar == other;
		}

		BOOLEAN operator!=(const CHAR16& other)
		{
			return !(*this == other);
		}

		BOOLEAN operator==(const UINT16& other)
		{
			return ScanCode == other;
		}

		BOOLEAN operator!=(const UINT16& other)
		{
			return !(*this == other);
		}
	};

	namespace KEYS
	{
		// UEFI Defined Keys and Scan Codes
		const InputKey Backspace = InputKey(0x0E, 0x08);
		const InputKey Delete = InputKey(0x53, 0x00);
		const InputKey Down = InputKey(0x50, 0x00);
		const InputKey End = InputKey(0x4F, 0x00);
		const InputKey Enter = InputKey(0x1C, 0x0D);
		const InputKey Escape = InputKey(0x01, 0x1B);
		const InputKey F1 = InputKey(0x3B, 0x00);
		const InputKey F10 = InputKey(0x44, 0x00);
		const InputKey F11 = InputKey(0x85, 0x00);
		const InputKey F12 = InputKey(0x86, 0x00);
		const InputKey F2 = InputKey(0x3C, 0x00);
		const InputKey F3 = InputKey(0x3D, 0x00);
		const InputKey F4 = InputKey(0x3E, 0x00);
		const InputKey F5 = InputKey(0x3F, 0x00);
		const InputKey F6 = InputKey(0x40, 0x00);
		const InputKey F7 = InputKey(0x41, 0x00);
		const InputKey F8 = InputKey(0x42, 0x00);
		const InputKey F9 = InputKey(0x43, 0x00);
		const InputKey Home = InputKey(0x47, 0x00);
		const InputKey Insert = InputKey(0x52, 0x00);
		const InputKey Left = InputKey(0x4B, 0x00);
		const InputKey Null = InputKey(0x00, 0x00);
		const InputKey PageDown = InputKey(0x51, 0x00);
		const InputKey PageUp = InputKey(0x49, 0x00);
		const InputKey Right = InputKey(0x4D, 0x00);
		const InputKey Space = InputKey(0x39, ' ');
		const InputKey Tab = InputKey(0x0F, 0x09);
		const InputKey Up = InputKey(0x48, 0x00);
	}
}
