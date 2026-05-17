#include <Debugging/Debugger.h>
#include <Protocols/IO/Console/ConsoleColor.h>
#include <System/Environment/Unicode.h>

namespace Common::Debugging
{
    inline static void SetConsoleColor(Efi::SystemTable* systemTable, UINT8 v)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, v);
    }
    inline static void SetConsoleColor(Efi::SystemTable* systemTable, Efi::ForegroundColor fg, Efi::BackgroundColor bg)
    {
        systemTable->ConOut->SetAttribute(systemTable->ConOut, fg | bg);
    }
    inline static void PrintLine(Efi::SystemTable* systemTable, const CHAR16* str)
    {
        if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
        systemTable->ConOut->OutputString(systemTable->ConOut, Common::System::Environment::UTF<CHAR16>::NewLine);
    }
    inline static void Print(Efi::SystemTable* systemTable, const CHAR16* str)
    {
        if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(str) == TRUE)
        {
            return;
        }
        systemTable->ConOut->OutputString(systemTable->ConOut, str);
    }
    void Debugger::PrintDebugLine(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Debug);
        PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }

    void Debugger::PrintInfoLine(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Info);
        PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }

    void Debugger::PrintWarningLine(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Warning);
		PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }

    void Debugger::PrintErrorLine(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Error);
		PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }

    void Debugger::PrintCriticalLine(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Fatal);
		PrintLine(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }
    void Debugger::PrintDebug(const CHAR16* msg) const
	{
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Debug);
		Print(_sysTbl, msg);
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }
    void Debugger::PrintInfo(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Info);
		Print(_sysTbl, msg);
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }
    void Debugger::PrintWarning(const CHAR16* msg) const
    {
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Warning);
		Print(_sysTbl, msg);
		SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }
    void Debugger::PrintError(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Error);
        Print(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }
    void Debugger::PrintCritical(const CHAR16* msg) const
    {
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Fatal);
        Print(_sysTbl, msg);
        SetConsoleColor(_sysTbl, Efi::ConsoleColor::_Default);
    }
    void Debugger::WaitForKey(const CHAR16 key) const
    {
        Efi::Status status = Efi::Status::Success;
        Efi::InputKey inputKey = Efi::KEYS::Null;
        _sysTbl->ConIn->Reset(_sysTbl->ConIn, false);
        /*Await for a specific key to be entered, otherwise clear ConsoleIn*/
        do
        {
            status = _sysTbl->BootServices->WaitForEvent(1, &_sysTbl->ConIn->WaitForKey, nullptr);
            if (status != Efi::Status::Success)
            {
                PrintErrorLine(u"Error in WaitForEvent");
                return;
            }

            status = _sysTbl->ConIn->ReadKeyStroke(_sysTbl->ConIn, &inputKey);
			_sysTbl->ConIn->Reset(_sysTbl->ConIn, false);

            if (status != Efi::Status::Success)
            {
                PrintErrorLine(u"Error in ReadKeyStroke");
                return;
            }
        } while (inputKey != key);

        _sysTbl->ConIn->Reset(_sysTbl->ConIn, false);
    }
    void Debugger::WaitForKey() const
    {

        Efi::Status status = Efi::Status::Success;
        Efi::InputKey inputKey = Efi::KEYS::Null;
        
        _sysTbl->ConIn->Reset(_sysTbl->ConIn, false);

        /*Await for a specific key to be entered, otherwise clear ConsoleIn*/
        do
        {
            status = _sysTbl->BootServices->WaitForEvent(1, &_sysTbl->ConIn->WaitForKey, nullptr);
            if (status != Efi::Status::Success)
            {
                PrintErrorLine(u"Error in WaitForEvent");
                return;
            }

            status = _sysTbl->ConIn->ReadKeyStroke(_sysTbl->ConIn, &inputKey);
            _sysTbl->ConIn->Reset(_sysTbl->ConIn, false);

            if (status != Efi::Status::Success)
            {
                PrintErrorLine(u"Error in ReadKeyStroke");
                return;
            }
        } while (inputKey == Efi::KEYS::Null);

        _sysTbl->ConIn->Reset(_sysTbl->ConIn,false);
    }
}