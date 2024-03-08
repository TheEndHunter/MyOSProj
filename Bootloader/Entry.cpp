#include "Entry.h"
#include <EFI_RESET_TYPE.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <Graphics/GraphicsContext.h>
#include <EFIConsole.h>
#include <Graphics/Color.h>
#include <Enviroment/Unicode.h>
#include <FileSystem/FileSystemContext.h>
#include <System/EfiAllocator.h>
#include <System/Allocator.h>
#include <System//AllocatorStatus.h>
#include <FileTypes/PE32.h>

namespace Bootloader
{
    using namespace Common::Enviroment;
    using namespace Common::FileSystem;
    using namespace Common::Graphics;
    using namespace Common::FileTypes;

    void PrintInfo(EFI_SYSTEM_TABLE* sysTbl, UINT8 color, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, color);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    }

    void PrintDebug(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::DEBUG_COLOR);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
	}

    void PrintError(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::ERROR_COLOR);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    };

    void ThrowException(EFI_SYSTEM_TABLE* sysTbl, EFI_HANDLE imgHndl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL_COLOR);
        ClearConOut(sysTbl);
        PrintLine(sysTbl, errorMessage);
        PrintLine(sysTbl, UTF16::ToString(status));
        WaitForKey(sysTbl);
        Exit(sysTbl, imgHndl, status);
    }

    void Exit(EFI_SYSTEM_TABLE* sysTable, EFI_HANDLE imgHndl, EFI_STATUS Status, UINTN exitDataSize, CHAR16* exitData)
    {
        sysTable->BootServices->Exit(imgHndl, Status, exitDataSize, exitData);
    }

    EFI_INPUT_KEY WaitForKey(EFI_SYSTEM_TABLE* sysTable)
    {
        EFI_STATUS status = EFI_STATUS::SUCCESS;
        EFI_INPUT_KEY key;
        UINTN index = 0;

        status = sysTable->BootServices->WaitForEvent(1, &sysTable->ConIn->WaitForKey, &index);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintError(sysTable,u"Error in WaitForEvent", status);
        }
        status = sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &key);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintError(sysTable,u"Error in ReadKeyStroke", status);
        }
        ClearConIn(sysTable);
        return key;
    }

    EFI_STATUS EfiMain(EFI_HANDLE imgHndl, EFI_SYSTEM_TABLE* sysTbl)
    {
        Common::System::EFIAllocator::SetEFIAllocator(sysTbl);


        if (!Common::System::Allocator::IsInitalized())
        {
            Common::System::AllocatorStatus s = Common::System::Allocator::LastStatus();

            EFI::EFI_STATUS t = Common::System::ToEfiStatus(s);

			ThrowException(sysTbl, imgHndl, u"Could Not Initialize EFI Allocator", t);
		}

        sysTbl->ConOut->Reset(sysTbl->ConOut, false);
        sysTbl->ConIn->Reset(sysTbl->ConIn, false);

        GraphicsContext gop = GraphicsContext::Initialize(imgHndl, sysTbl);

        if (GraphicsContext::LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl,imgHndl, boot_GOP_LOCATE_ERROR,GraphicsContext::LastStatus);
        }

        gop.ClearScreen();

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

        UINTN fsCount = FileSystemContext::QueryFSCount(sysTbl, imgHndl);

        if (fsCount == 0)
        {
            ThrowException(sysTbl, imgHndl, u"No File Systems Found", EFI_STATUS::NOT_FOUND);
		}

        EFI_STATUS fsStatus = EFI_STATUS::SUCCESS;
        FileSystemContext sysFs = FileSystemContext::GetFileSystem(sysTbl, imgHndl,u"SYS" , &fsStatus);
        
        if (sysFs == FileSystemContext::EmptyFS)
        {
			ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"Sys\"", fsStatus);
		}

        sysFs.OpenVolume();

        FileInfo kernel = sysFs.GetFileInfo(sysTbl,u"Kernel.bin");

        if (sysFs.LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
			ThrowException(sysTbl, imgHndl, u"Could Not Locate Kernel", sysFs.LastStatus);
		}
        
        if (kernel == Empty_FileInfo)
        {
			ThrowException(sysTbl, imgHndl, u"Kernel Not Found", EFI::EFI_STATUS::NOT_FOUND);
		}

        FileHandle kernelHandle = sysFs.OpenFile(sysTbl, &kernel, FileMode::Read,kernel.Attribute);

        if (sysFs.LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Open Kernel", sysFs.LastStatus);
        }

        PE32File* kernelFile = PE32File::Read(&kernelHandle);

        if (kernelFile->DosHeader == nullptr)
        {
			ThrowException(sysTbl, imgHndl, u"Invalid DOS Header", EFI::EFI_STATUS::INVALID_PARAMETER);
            PrintDebug(sysTbl, u"Invalid PE Header", EFI::EFI_STATUS::INVALID_PARAMETER);
            PrintDebug(sysTbl, UTF16::ToString(kernelFile->lastHeaderPosition));
            WaitForKey(sysTbl);
		}

        if (kernelFile->PEHeader == nullptr)
        {
            PrintDebug(sysTbl, u"Invalid PE Header", EFI::EFI_STATUS::INVALID_PARAMETER);
            PrintDebug(sysTbl, UTF16::ToString(kernelFile->lastHeaderPosition));
            WaitForKey(sysTbl);
		}

        WaitForKey(sysTbl);
        sysTbl->RuntimeServices->ResetSystem(EFI_RESET_TYPE::SHUTDOWN, EFI_STATUS::SUCCESS, 0, nullptr);

        return EFI::EFI_STATUS::END_OF_MEDIA;
    }
}