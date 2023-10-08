#include <UEFIDef.h>
#include <EFI_HANDLE.h>
#include <EFI_STATUS.h>
#include <EFI_RESET_TYPE.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Peripheral/EFI_INPUT_KEY.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <Graphics/GraphicsContext.h>
#include <EFIConsole.h>
#include "Graphics/Color.h"
#include "Enviroment/Unicode.h"

namespace Bootloader
{
    using namespace EFI;
    using namespace Graphics;

    constinit const CHAR16* boot_GOP_LOCATE_ERROR = u"Error in Locate Protocol: ";

    static EFI_INPUT_KEY WaitForKey(EFI_SYSTEM_TABLE* sysTable)
    {
        EFI_INPUT_KEY key;
        while (sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &key) == EFI_STATUS::NOT_READY)
        {
            sysTable->BootServices->Stall(1000);
        }
        ClearConIn(sysTable);
        return key;
    }
    
    EFI_STATUS EfiMain(EFI_HANDLE handle, EFI_SYSTEM_TABLE* systemTable)
    {
        systemTable->ConOut->Reset(systemTable->ConOut, false);

        GraphicsContext gop;
        EFI_STATUS gopStatus = gop.Initialize(handle, systemTable);
        
        if (gopStatus != EFI_STATUS::SUCCESS)
        {
            WaitForKey(systemTable);
            SetConsoleColor(systemTable, EFI_CONSOLE_COLOR::FATAL_COLOR);
            ClearConOut(systemTable);
            Print(systemTable, boot_GOP_LOCATE_ERROR);
            PrintLine(systemTable, UTF16::ToString(gopStatus));
            WaitForKey(systemTable);
            return gopStatus;
        }

        gop.ClearScreen();

        PrintLine(systemTable, u"GOP INITIALIZED");
        
        UINTN w = gop.GetWidth();
        UINTN h = gop.GetHeight();

        UINTN x1 = w / 3;
        UINTN y1 = h / 3;

        UINTN x2 = w / 4;
        UINTN y2 = h / 4;

        gop.DrawRectangle(x1, y1, x1, y1, Colors::MediumVioletRed);
        gop.DrawRectangle(x2, y2, x2, y2, Colors::HotPink);

        WaitForKey(systemTable);

        systemTable->RuntimeServices->ResetSystem(EFI::EFI_RESET_TYPE::Cold, EFI_STATUS::SUCCESS, 0, nullptr);

        return EFI_STATUS::SUCCESS;
    }

   
}