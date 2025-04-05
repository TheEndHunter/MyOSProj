#pragma once

#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "Protocols/IO/Console/EFI_CONSOLE_COLOR.h"
#include "EFI_SYSTEM_TABLE.h"
#include <System/Environment/Unicode.h>
#include <CRT_ENTRIES.h>

// Bootloader.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
namespace Bootloader
{
	using namespace EFI;
	using namespace Common::System::Environment;

	static void ClearConIn(EFI_SYSTEM_TABLE* systemTable)
	{
		systemTable->ConIn->Reset(systemTable->ConIn, false);
	}
	static void ClearConOut(EFI_SYSTEM_TABLE* systemTable)
	{
		systemTable->ConOut->ClearScreen(systemTable->ConOut);
	}

	static void SetConsoleColor(EFI_SYSTEM_TABLE* systemTable, UINT8 v)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, v);
	}
	static void SetConsoleColor(EFI_SYSTEM_TABLE* systemTable, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
	}

	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}

		systemTable->ConOut->OutputString(systemTable->ConOut, str);
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status)
	{
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, UINT8 color)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}

		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c)
	{

		if (c != u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, UINT8 color)
	{
		if (c != u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (c != u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
	}

	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status)
	{
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, UINT8 color)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}

		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c)
	{
		if (c != u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, UINT8 color)
	{
		if (c != u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (c != u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}

	static void PrintInfoLine(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
	{
		SetConsoleColor(sysTbl, EfiConsoleColor::_Default);
		PrintLine(sysTbl, errorMessage);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintLine(sysTbl, UTF<CHAR16>::ToString(status));
		};
	}
	static void PrintDebugLine(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
	{
		SetConsoleColor(sysTbl, EfiConsoleColor::_Debug);
		PrintLine(sysTbl, errorMessage);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintLine(sysTbl, UTF<CHAR16>::ToString(status));
		};
	}
	static void PrintErrorLine(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
	{
		SetConsoleColor(sysTbl, EfiConsoleColor::_Error);
		PrintLine(sysTbl, errorMessage);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintLine(sysTbl, UTF<CHAR16>::ToString(status));
		};
	}
	static void PrintWarningLine(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
	{
		SetConsoleColor(sysTbl, EfiConsoleColor::_Warning);
		PrintLine(sysTbl, errorMessage);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintLine(sysTbl, UTF<CHAR16>::ToString(status));
		};
	}
	static void PrintCriticalLine(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
	{
		SetConsoleColor(sysTbl, EfiConsoleColor::_Fatal);
		PrintLine(sysTbl, errorMessage);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintLine(sysTbl, UTF<CHAR16>::ToString(status));
		};
	}

	static EFI_INPUT_KEY WaitForAnyKey(EFI_SYSTEM_TABLE* sysTable)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY key;
		UINTN index = 0;

		status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &index);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
		}
		status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &key);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
		}
		ClearConIn(sysTable);
		return key;
	}

	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const EFI_INPUT_KEY key)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, nullptr);
			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
				return;
			}

			status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &inputKey);
			ClearConIn(sysTable);

			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
				return;
			}
		} while (inputKey != key);

		ClearConIn(sysTable);
	}
	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const CHAR16 key)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, nullptr);
			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
				return;
			}

			status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &inputKey);
			ClearConIn(sysTable);

			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
				return;
			}
		} while (inputKey != key);

		ClearConIn(sysTable);
	}
	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const CHAR8 key)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		CHAR16 k = (CHAR16)key;
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, nullptr);
			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
				return;
			}

			status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &inputKey);
			ClearConIn(sysTable);

			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
				return;
			}
		} while (inputKey != k);

		ClearConIn(sysTable);
	}
	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const UINT16 scancode)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, nullptr);
			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
				return;
			}

			status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &inputKey);
			ClearConIn(sysTable);

			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
				return;
			}
		} while (inputKey != scancode);

		ClearConIn(sysTable);
	}
	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const UINT8 scancode)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		UINT16 sc = (UINT16)scancode;
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, nullptr);
			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
				return;
			}

			status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &inputKey);
			ClearConIn(sysTable);

			if (status != EFI_STATUS::SUCCESS)
			{
				PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
				return;
			}
		} while (inputKey != sc);

		ClearConIn(sysTable);
	}

	static void Exit(EFI_SYSTEM_TABLE* sysTable, EFI_HANDLE imgHndl, EFI_STATUS Status = EFI::EFI_STATUS::SUCCESS, UINTN exitDataSize = 0, CHAR16* exitData = nullptr)
	{
		_CRT_TERM();
		sysTable->BootServices->Exit(imgHndl, Status, exitDataSize, exitData);
	}
	static void ThrowException(EFI_SYSTEM_TABLE* sysTbl, EFI_HANDLE imgHndl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
	{
		SetConsoleColor(sysTbl, EfiConsoleColor::_Fatal);
		ClearConOut(sysTbl);
		PrintLine(sysTbl, errorMessage);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintLine(sysTbl, UTF<CHAR16>::ToString(status));
		};
		WaitForAnyKey(sysTbl);
		Exit(sysTbl, imgHndl, status);
	}

}
