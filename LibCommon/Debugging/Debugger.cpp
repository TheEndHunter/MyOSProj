#include <Debugging/Debugger.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <System/Environment/Unicode.h>

namespace Common::Debugging
{
    inline static void SetConsoleColor(EFI::EFI_SYSTEM_TABLE* systemTable, UINT8 v)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, v);
    }

    inline static void SetConsoleColor(EFI::EFI_SYSTEM_TABLE* systemTable, EFI::EfiForegroundColor fg, EFI::EfiBackgroundColor bg)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
    }

    inline static void PrintLine(EFI::EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
    {
        if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
        systemTable->ConOut->OutputString(systemTable->ConOut, Common::System::Environment::UTF<CHAR16>::NewLine);
    }

    inline static void Print(EFI::EFI_SYSTEM_TABLE* systemTable, const CHAR16* str)
    {
        if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
    }

    void Debugger::PrintDebugLine(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Debug);
        PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }

    void Debugger::PrintInfoLine(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Info);
        PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }

    void Debugger::PrintWarningLine(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Warning);
		PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }

    void Debugger::PrintErrorLine(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Error);
		PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }

    void Debugger::PrintCriticalLine(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Fatal);
		PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }
    void Debugger::PrintDebug(const CHAR16* msg) const
	{
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Debug);
		Print(_sysTbl, msg);
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }
    void Debugger::PrintInfo(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Info);
		Print(_sysTbl, msg);
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }
    void Debugger::PrintWarning(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Warning);
		Print(_sysTbl, msg);
		SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }
    void Debugger::PrintError(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Error);
        Print(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }
    void Debugger::PrintCritical(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Fatal);
        Print(_sysTbl, msg);
        SetConsoleColor(_sysTbl, EFI::EfiConsoleColor::_Default);
    }
}