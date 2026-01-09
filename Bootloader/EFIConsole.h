#pragma once

#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "Protocols/IO/Console/EFI_CONSOLE_COLOR.h"
#include "EFI_SYSTEM_TABLE.h"
#include <System/Environment/Unicode.h>
#include <CRT/CRT_Stubs.h>

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

		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(str);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			UTF<CHAR16>::Free(sanitized);
		}
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(str);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			UTF<CHAR16>::Free(sanitized);
		}
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

		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(str);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			UTF<CHAR16>::Free(sanitized);
		}
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c)
	{
		if (c == u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(&_u16_print[0]);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			UTF<CHAR16>::Free(sanitized);
		}
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, UINT8 color)
	{
		if (c == u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
	}
	static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (c == u'\0')
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
		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(str);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
			UTF<CHAR16>::Free(sanitized);
		}
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EfiForegroundColor fg, EfiBackgroundColor bg)
	{
		if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
		{
			return;
		}
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(str);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
			UTF<CHAR16>::Free(sanitized);
		}
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

		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(str);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
			UTF<CHAR16>::Free(sanitized);
		}
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
	{
		systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::ToString(status));
		systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
	}
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c)
	{
		if (c == u'\0')
		{
			return;
		}

		CHAR16 _u16_print[2] = { c, u'\0' };
		CHAR16* sanitized = UTF<CHAR16>::SanitizeToUcs2(&_u16_print[0]);
		if (sanitized != nullptr)
		{
			systemTable->ConOut->OutputString(systemTable->ConOut, sanitized);
			systemTable->ConOut->OutputString(systemTable->ConOut, UTF<CHAR16>::NewLine);
			UTF<CHAR16>::Free(sanitized);
		}
	}

    // Basic ANSI/VT100 sequence interpreter for UEFI ConOut.
    // Supports: SGR (m) for colors, Cursor position (H/f), Clear screen (2J), and plain text output.
    static void PrintAnsi(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
    {
        if (UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }

        // Current attribute: lower 4 = foreground, upper 4 = background
        UINT8 attr = 0x07; // default light gray on black

        auto applyAttribute = [&](UINT8 a)
        {
            systemTable->ConOut->SetAttribute(systemTable->ConOut, a);
            attr = a;
        };

        // Temporary output buffer
        const size_t BUF_SZ = 256;
        CHAR16 outBuf[BUF_SZ];
        size_t outIdx = 0;

        auto flushOut = [&]() {
            if (outIdx == 0) return;
            outBuf[outIdx] = u'\0';
            systemTable->ConOut->OutputString(systemTable->ConOut, outBuf);
            outIdx = 0;
        };

        for (UINTN i = 0; str[i] != u'\0'; ++i)
        {
            CHAR16 c = str[i];
            if (c == 0x1B) // ESC
            {
                // Potential ANSI sequence
                if (str[i + 1] == u'[')
                {
                    // Flush text seen so far
                    flushOut();

                    // parse parameters
                    i += 2; // point to first char after ESC[
                    // collect params until a letter
                    int params[8];
                    int pCount = 0;
                    int cur = -1;
                    while (str[i] != u'\0' && !( (str[i] >= u'@' && str[i] <= u'~') ))
                    {
                        CHAR16 ch = str[i];
                        if (ch >= u'0' && ch <= u'9')
                        {
                            if (cur == -1) cur = 0;
                            cur = cur * 10 + (ch - u'0');
                        }
                        else if (ch == u';')
                        {
                            if (pCount < 8) params[pCount++] = (cur == -1) ? 0 : cur;
                            cur = -1;
                        }
                        else
                        {
                            // ignore
                        }
                        ++i;
                    }

                    if (cur != -1)
                    {
                        if (pCount < 8) params[pCount++] = cur;
                    }

                    CHAR16 final = str[i];
                    // Handle some final bytes
                    if (final == u'm')
                    {
                        // SGR - set graphics rendition
                        if (pCount == 0)
                        {
                            // reset
                            applyAttribute(0x07);
                        }
                        for (int pi = 0; pi < pCount; ++pi)
                        {
                            int v = params[pi];
                            if (v == 0)
                            {
                                applyAttribute(0x07);
                            }
                            else if (v == 1)
                            {
                                // bold - set bright bit on foreground
                                UINT8 fg = attr & 0x0F;
                                fg = fg | 0x08;
                                UINT8 bg = (attr & 0xF0);
                                applyAttribute((UINT8)(fg | bg));
                            }
                            else if (v >= 30 && v <= 37)
                            {
                                UINT8 fg = (UINT8)(v - 30);
                                UINT8 bg = (attr & 0xF0);
                                applyAttribute((UINT8)(fg | bg));
                            }
                            else if (v >= 40 && v <= 47)
                            {
                                UINT8 bg = (UINT8)((v - 40) << 4);
                                UINT8 fg = (attr & 0x0F);
                                applyAttribute((UINT8)(fg | bg));
                            }
                            else if (v >= 90 && v <= 97)
                            {
                                // bright foreground
                                UINT8 fg = (UINT8)((v - 90) | 0x08);
                                UINT8 bg = (attr & 0xF0);
                                applyAttribute((UINT8)(fg | bg));
                            }
                            else if (v == 39)
                            {
                                // reset fg
                                UINT8 bg = (attr & 0xF0);
                                applyAttribute((UINT8)(0x07 | bg));
                            }
                            else if (v == 49)
                            {
                                // reset bg
                                UINT8 fg = (attr & 0x0F);
                                applyAttribute((UINT8)(fg | (0x00 << 4)));
                            }
                        }
                    }
                    else if (final == u'H' || final == u'f')
                    {
                        // Cursor position: params are [row;col]
                        int row = (pCount >= 1) ? params[0] : 1;
                        int col = (pCount >= 2) ? params[1] : 1;
                        if (row < 1) row = 1;
                        if (col < 1) col = 1;
                        // UEFI SetCursorPosition uses zero-based coordinates
                        systemTable->ConOut->SetCursorPosition(systemTable->ConOut, (UINTN)(col - 1), (UINTN)(row - 1));
                    }
                    else if (final == u'J')
                    {
                        // Clear screen (if param 2)
                        int mode = (pCount >= 1) ? params[0] : 0;
                        if (mode == 2)
                        {
                            systemTable->ConOut->ClearScreen(systemTable->ConOut);
                        }
                    }
                    else if (final == u'K')
                    {
                        // Erase line - implement as overwrite with spaces from current pos to eol
                        int mode = (pCount >= 1) ? params[0] : 0;
                        // approximate: write 160 spaces
                        CHAR16 spaces[161];
                        for (int si = 0; si < 160; ++si) spaces[si] = u' ';
                        spaces[160] = u'\0';
                        if (mode == 0 || mode == 1 || mode == 2)
                        {
                            systemTable->ConOut->OutputString(systemTable->ConOut, spaces);
                        }
                    }
                    // else: unsupported sequence - ignore
                }
                // skip the ESC if not a CSI
                continue;
            }

            // Normal character - buffer it
            outBuf[outIdx++] = c;
            if (outIdx + 1 >= BUF_SZ)
            {
                flushOut();
            }
        }

        flushOut();
    }
	static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, UINT8 color)
	{
		if (c == u'\0')
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
		if (c == u'\0')
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

    // simple wrappers for printing with colors are available above (with optional status overloads)

	static EFI_INPUT_KEY WaitForAnyKey(EFI_SYSTEM_TABLE* sysTable)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY key;
		UINTN index = 0;

		status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &index);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintErrorLine(sysTable, u"Error in WaitForEvent", status);
			PrintDebugLine(sysTable, UTF<CHAR16>::ToHex((UINT64)status));
		}
		status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &key);
		if (status != EFI_STATUS::SUCCESS)
		{
			PrintErrorLine(sysTable, u"Error in ReadKeyStroke", status);
			PrintDebugLine(sysTable, UTF<CHAR16>::ToHex((UINT64)status));
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
			UINTN idx = 0;
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &idx);
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
		} while (!(inputKey.UnicodeChar == key.UnicodeChar && inputKey.ScanCode == key.ScanCode));

		ClearConIn(sysTable);
	}
	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const CHAR16 key)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		sysTable->ConIn->Reset(sysTable->ConIn, false);
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			UINTN idx = 0;
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &idx);
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
		} while (inputKey.UnicodeChar != key);

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
			UINTN idx = 0;
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &idx);
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
		} while (inputKey.UnicodeChar != k);

		ClearConIn(sysTable);
	}
	static void WaitForKey(EFI_SYSTEM_TABLE* sysTable, const UINT16 scancode)
	{
		EFI_STATUS status = EFI_STATUS::SUCCESS;
		EFI_INPUT_KEY inputKey = KEYS::Null;
		/*Await for a specific key to be entered, otherwise clear ConsoleIn*/
		do
		{
			UINTN idx = 0;
			status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &idx);
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
		} while (inputKey.ScanCode != scancode);

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
		}

		WaitForAnyKey(sysTbl);
		Exit(sysTbl, imgHndl, status);
	}

}
