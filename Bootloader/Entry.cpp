#include <TypeDefs.h>
#include <EFI_HANDLE.h>
#include <EFI_STATUS.h>
#include <EFI_RESET_TYPE.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Peripheral/EFI_INPUT_KEY.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <Graphics/GraphicsContext.h>
#include <EFIConsole.h>
#include <Graphics/Color.h>
#include <Enviroment/Unicode.h>
#include <FileSystem/FileSystemContext.h>

namespace Bootloader
{
    using namespace EFI;
    using namespace Common::Enviroment;
    using namespace Common::FileSystem;
    using namespace Common::Graphics;

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
    
    EFI_STATUS EfiMain(EFI_HANDLE imgHndl, EFI_SYSTEM_TABLE* sysTbl)
    {
        sysTbl->ConOut->Reset(sysTbl->ConOut, false);
        sysTbl->ConIn->Reset(sysTbl->ConIn, false);

        GraphicsContext gop = GraphicsContext::Initialize(imgHndl, sysTbl);
        if (GraphicsContext::LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL_COLOR);
            ClearConOut(sysTbl);
            Print(sysTbl, boot_GOP_LOCATE_ERROR);
            PrintLine(sysTbl, UTF16::ToString(GraphicsContext::LastStatus));
            WaitForKey(sysTbl);
            return GraphicsContext::LastStatus;
        }
        gop.ClearScreen();
        PrintLine(sysTbl, u"Graphics Initialized");

        UINTN w = gop.GetWidth();
        UINTN h = gop.GetHeight();

        UINTN cX = w / 2;
        UINTN cY = h / 2;

        UINTN x1 = w / 3;
        UINTN y1 = h / 3;

        UINTN x2 = w / 4;
        UINTN y2 = h / 4;

        UINTN posX = cX - (x2 / 2);
        UINTN posY = cY - (y2 / 2);

        gop.DrawFilledRectangle(x1, y1, x1, y1, Colors::MediumVioletRed);
        gop.DrawFilledRectangle(posX, posY, x2, y2, Colors::HotPink);

        WaitForKey(sysTbl);

        UINTN fsCount = FileSystemContext::QueryFSCount(sysTbl, imgHndl);

        if (fsCount == 0)
        {
			SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL_COLOR);
			ClearConOut(sysTbl);
			PrintLine(sysTbl, u"No File Systems Found");
			WaitForKey(sysTbl);
			return EFI_STATUS::NOT_FOUND;
		}
        UINTN fsIndex = 0;
        FileSystemContext sysFs = FileSystemContext::EmptyFS;
        for (; fsIndex < fsCount; fsIndex++)
        {
            sysFs = FileSystemContext::GetFileSystem(sysTbl, imgHndl, fsIndex);

            sysFs.OpenVolume();
            VolumeInfo v = sysFs.GetVolumeInfo(sysTbl);

            if (v.VolumeLabel == u"Sys")
            {
                break;
            }
        }

        if(sysFs == FileSystemContext::EmptyFS)
		{
            SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL_COLOR);
            ClearConOut(sysTbl);
            PrintLine(sysTbl, u"Could Not Find System Volume");
            WaitForKey(sysTbl);
            return EFI_STATUS::NOT_FOUND;
        }
        PrintLine(sysTbl, u"Found System Volume");

        sysFs.OpenVolume();

        FileInfo krnl = sysFs.GetFileInfo(sysTbl, u"Kernel.bin");

        if (krnl == Empty_FileInfo)
        {
            SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL_COLOR);
			ClearConOut(sysTbl);
			PrintLine(sysTbl, u"Could Not Find Kernel");
			WaitForKey(sysTbl);
			return EFI_STATUS::NOT_FOUND;
        }

        UINT8* krnlData;
        sysTbl->BootServices->AllocatePool(EFI_MEMORY_TYPE::LoaderData, krnl.PhysicalSize,(void**)&krnlData);

        PrintLine(sysTbl, u"Found Kernel.bin");
        WaitForKey(sysTbl);

        sysTbl->RuntimeServices->ResetSystem(EFI_RESET_TYPE::SHUTDOWN, EFI_STATUS::SUCCESS, 0, nullptr);

        return EFI_STATUS::SUCCESS;
    }

   
}