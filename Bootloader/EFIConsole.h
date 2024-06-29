#pragma once

#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "Protocols/IO/Console/EFI_CONSOLE_COLOR.h"
#include "EFI_SYSTEM_TABLE.h"
#include <Environment/Unicode.h>

// Bootloader.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
namespace Bootloader
{
    using namespace EFI;
    using namespace Common::Environment;

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

    static void PrintInfo(EFI_SYSTEM_TABLE* sysTbl, UINT8 color, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
    {
        SetConsoleColor(sysTbl, color);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    }

    static  void PrintDebug(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::DEBUG);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    }

    static void PrintError(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::ERROR);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    
    }

    static EFI_INPUT_KEY WaitForKey(EFI_SYSTEM_TABLE* sysTable)
    {
        EFI_STATUS status = EFI_STATUS::SUCCESS;
        EFI_INPUT_KEY key;
        UINTN index = 0;

        status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &index);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintError(sysTable, u"Error in WaitForEvent", status);
        }
        status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &key);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintError(sysTable, u"Error in ReadKeyStroke", status);
        }
        ClearConIn(sysTable);
        return key;
    }

    static void PrintWarning(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::WARNING);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    };

    static void Exit(EFI_SYSTEM_TABLE* sysTable, EFI_HANDLE imgHndl, EFI_STATUS Status = EFI::EFI_STATUS::SUCCESS, UINTN exitDataSize = 0, CHAR16* exitData = nullptr)
    {
        sysTable->BootServices->Exit(imgHndl, Status, exitDataSize, exitData);
    }

    static void ThrowException(EFI_SYSTEM_TABLE* sysTbl, EFI_HANDLE imgHndl, const CHAR16* errorMessage, EFI_STATUS status = EFI::EFI_STATUS::SUCCESS)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL);
        ClearConOut(sysTbl);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
        WaitForKey(sysTbl);
        Exit(sysTbl, imgHndl, status);
    }
}
