#pragma once
#include "UEFIDef.h"
#include "Enviroment.h"
#include "EFI_STATUS.h"
#include "Protocols/IO/Console/EFI_CONSOLE_COLOR.h"
#include "EFI_SYSTEM_TABLE.h"

// Bootloader.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
namespace Bootloader
{
    using namespace EFI;

    static void ClearConOut(EFI_SYSTEM_TABLE* systemTable)
    {
        systemTable->ConOut->ClearScreen(systemTable->ConOut);
    }

    static void ClearConIn(EFI_SYSTEM_TABLE* systemTable)
    {
        systemTable->ConIn->Reset(systemTable->ConIn, false);
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
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
	}

    static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
		systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg );
		systemTable->ConOut->OutputString(systemTable->ConOut, str);
	}

    static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status)
    {
        systemTable->ConOut->OutputString(systemTable->ConOut, EFI::ToString(status));
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
        systemTable->ConOut->OutputString(systemTable->ConOut, EFI::ToString(status));
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
    {
        Print(systemTable, str);
        Print(systemTable, Environment::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        Print(systemTable, str,fg,bg);
        Print(systemTable, Environment::NewLine,fg,bg);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status)
    {
        Print(systemTable, EFI::ToString(status));
        Print(systemTable, Environment::NewLine);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, EFI_FOREGROUND_COLOR fg, EFI_BACKGROUND_COLOR bg)
    {
        Print(systemTable, EFI::ToString(status),fg,bg);
		Print(systemTable, Environment::NewLine,fg,bg);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, UINT8 color)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut,color);
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
    }

    static void Print(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, color);
        systemTable->ConOut->OutputString(systemTable->ConOut, EFI::ToString(status));
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const CHAR16* str, UINT8 color)
    {
        Print(systemTable, str, color);
        Print(systemTable, Environment::NewLine, color);
    }

    static void PrintLine(EFI_SYSTEM_TABLE* systemTable, const EFI_STATUS status, UINT8 color)
    {
        Print(systemTable, EFI::ToString(status), color);
        Print(systemTable, Environment::NewLine, color);
    }
}
