#include <UEFIDef.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Peripheral/EFI_INPUT_KEY.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>

#include "Helpers.h"
#include "StringHelpers.h"

namespace Bootloader
{
    using namespace EFI;

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

    EFI_GRAPHICS_OUTPUT_PROTOCOL gop;
    EFI_STATUS EfiMain(EFI_HANDLE handle, EFI_SYSTEM_TABLE* systemTable)
    {
        systemTable->ConOut->Reset(systemTable->ConOut, false);


        EFI_STATUS gopStatus = systemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);

        if (gopStatus != EFI_STATUS::SUCCESS)
        {
            SetConsoleColor(systemTable, EFI_CONSOLE_COLOR::FATAL_COLOR);
            ClearConOut(systemTable);
            Print(systemTable, boot_GOP_LOCATE_ERROR);
            PrintLine(systemTable, ToString(gopStatus));

            WaitForKey(systemTable);
            return gopStatus;
        }

        WaitForKey(systemTable);

        return EFI_STATUS::SUCCESS;
    }
}