#pragma once
#include "UEFIDef.h"

namespace EFI
{
	struct EFI_INPUT_KEY
	{
	public:
		EFI_INPUT_KEY(const UINT16 scanCode = 0,const CHAR16 unicodeChar = 0)
		{
			ScanCode = scanCode;
			UnicodeChar = unicodeChar;
		}

		EFI_INPUT_KEY(const EFI_INPUT_KEY& other)
		{
			ScanCode = other.ScanCode;
			UnicodeChar = other.UnicodeChar;
		}

		UINT16 ScanCode;
		CHAR16 UnicodeChar;

		BOOLEAN operator==(const EFI_INPUT_KEY& other)
		{
			return ScanCode == other.ScanCode && UnicodeChar == other.UnicodeChar;
		}

		BOOLEAN operator!=(const EFI_INPUT_KEY& other)
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
		const EFI_INPUT_KEY Backspace = EFI_INPUT_KEY(0x0E, 0x08);
		const EFI_INPUT_KEY Delete = EFI_INPUT_KEY(0x53, 0x00);
		const EFI_INPUT_KEY Down = EFI_INPUT_KEY(0x50, 0x00);
		const EFI_INPUT_KEY End = EFI_INPUT_KEY(0x4F, 0x00);
		const EFI_INPUT_KEY Enter = EFI_INPUT_KEY(0x1C, 0x0D);
		const EFI_INPUT_KEY Escape = EFI_INPUT_KEY(0x01, 0x1B);
		const EFI_INPUT_KEY F1 = EFI_INPUT_KEY(0x3B, 0x00);
		const EFI_INPUT_KEY F10 = EFI_INPUT_KEY(0x44, 0x00);
		const EFI_INPUT_KEY F11 = EFI_INPUT_KEY(0x85, 0x00);
		const EFI_INPUT_KEY F12 = EFI_INPUT_KEY(0x86, 0x00);
		const EFI_INPUT_KEY F2 = EFI_INPUT_KEY(0x3C, 0x00);
		const EFI_INPUT_KEY F3 = EFI_INPUT_KEY(0x3D, 0x00);
		const EFI_INPUT_KEY F4 = EFI_INPUT_KEY(0x3E, 0x00);
		const EFI_INPUT_KEY F5 = EFI_INPUT_KEY(0x3F, 0x00);
		const EFI_INPUT_KEY F6 = EFI_INPUT_KEY(0x40, 0x00);
		const EFI_INPUT_KEY F7 = EFI_INPUT_KEY(0x41, 0x00);
		const EFI_INPUT_KEY F8 = EFI_INPUT_KEY(0x42, 0x00);
		const EFI_INPUT_KEY F9 = EFI_INPUT_KEY(0x43, 0x00);
		const EFI_INPUT_KEY Home = EFI_INPUT_KEY(0x47, 0x00);
		const EFI_INPUT_KEY Insert = EFI_INPUT_KEY(0x52, 0x00);
		const EFI_INPUT_KEY Left = EFI_INPUT_KEY(0x4B, 0x00);
		const EFI_INPUT_KEY Null = EFI_INPUT_KEY(0x00, 0x00);
		const EFI_INPUT_KEY PageDown = EFI_INPUT_KEY(0x51, 0x00);
		const EFI_INPUT_KEY PageUp = EFI_INPUT_KEY(0x49, 0x00);
		const EFI_INPUT_KEY Right = EFI_INPUT_KEY(0x4D, 0x00);
		const EFI_INPUT_KEY Space = EFI_INPUT_KEY(0x39, ' ');
		const EFI_INPUT_KEY Tab = EFI_INPUT_KEY(0x0F, 0x09);
		const EFI_INPUT_KEY Up = EFI_INPUT_KEY(0x48, 0x00);
	}
}
