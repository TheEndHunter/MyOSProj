#pragma once

#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "Protocols/IO/Console/EFI_CONSOLE_COLOR.h"
#include "EFI_SYSTEM_TABLE.h"
#include <Enviroment/Unicode.h>

// Bootloader.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
namespace Bootloader
{
    using namespace EFI;
    using namespace Common::Enviroment;

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

    static void SetConsoleColor(EFI_SYSTEM_TABLE* systemTable, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
    {
        if (UTF16::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }

        systemTable->ConOut->OutputString(systemTable->ConOut, str);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        if (UTF16::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status)
    {
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::ToString(status));
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::ToString(status));
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
    {
        if (UTF16::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        if (UTF16::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status)
    {
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::ToString(status));
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::ToString(status));
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, UINT8 color)
    {
        if (UTF16::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }

        systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::ToString(status));
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, UINT8 color)
    {
        if (UTF16::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }

        systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::ToString(status));
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
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

    static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        if (c != u'\0')
        {
            return;
        }

        CHAR16 _u16_print[2] = { c, u'\0' };
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c)
    {
        if (c != u'\0')
        {
            return;
        }

        CHAR16 _u16_print[2] = { c, u'\0' };
        systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
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
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16 c, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        if (c != u'\0')
        {
            return;
        }

        CHAR16 _u16_print[2] = { c, u'\0' };
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, &_u16_print[0]);
        systemTable->ConOut->OutputString(systemTable->ConOut, UTF16::NewLine);
    }
}
