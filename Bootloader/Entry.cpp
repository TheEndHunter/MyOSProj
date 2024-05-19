#include "Entry.h"
#include <EFI_RESET_TYPE.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <Graphics/GraphicsContext.h>
#include <EFIConsole.h>
#include <Graphics/Colour.h>
#include <Environment/Unicode.h>
#include <FileSystem/ESP/FileSystemContext.h>
#include <System/Allocator.h>
#include <System//AllocatorStatus.h>

#include <FileTypes/PE/PE32.h>
#include <Graphics/RenderContext.h>


namespace Bootloader
{
    using namespace Common::Environment;
    using namespace Common::FileSystem::ESP;
    using namespace Common::Graphics;
    using namespace Common::FileTypes::PE;
    using namespace EFI;

    typedef UINTN(CDECL*KrnlMain)(RenderContext* rendererCtx, MonitorContext* monitorCtx);

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
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::DEBUG);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    }

    void PrintError(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::ERROR);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    }
    void PrintWarning(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::WARNING);
        PrintLine(sysTbl, errorMessage);
        if (status != EFI_STATUS::SUCCESS)
        {
            PrintLine(sysTbl, UTF16::ToString(status));
        };
    };

    void ThrowException(EFI_SYSTEM_TABLE* sysTbl, EFI_HANDLE imgHndl, const CHAR16* errorMessage, EFI_STATUS status)
    {
        SetConsoleColor(sysTbl, EFI_CONSOLE_COLOR::FATAL);
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

    EFI_STATUS EfiMain(EFI_HANDLE imgHndl, EFI_SYSTEM_TABLE* sysTbl)
    {
        Common::System::Allocator::SetEfiAllocator(sysTbl);

        if (!Common::System::Allocator::IsInitalized())
		{
            ThrowException(sysTbl, imgHndl, u"Could Not Set EFI Allocator", Common::System::ToEfiStatus(Common::System::Allocator::LastStatus()));
		}

        UINT32 mm = sysTbl->ConOut->Mode->MaxMode;
        UINTN Columns = 0;
        UINTN Rows = 0;
        UINTN mode = 0;

        for (; mode < mm; mode++)
        {
            UINTN CurrentC = 0;
            UINTN CurrentR = 0;

            EFI_STATUS queryStat = sysTbl->ConOut->QueryMode(sysTbl->ConOut, mode,&CurrentC,&CurrentR);
			
            if (queryStat == EFI_STATUS::SUCCESS)
			{
                if (CurrentC > Columns && CurrentR > Rows)
                {
                    Columns = CurrentC;
                    Rows = CurrentR;
                }
                continue;
			}

            PrintError(sysTbl, u"Error in Query Mode", queryStat);
        }

        EFI_STATUS conStat = sysTbl->ConOut->SetMode(sysTbl->ConOut,mode);

        if (conStat != EFI_STATUS::SUCCESS)
		{
            if (conStat != EFI_STATUS::UNSUPPORTED)
            {
                ThrowException(sysTbl, imgHndl, u"Could Not Set Console Mode", conStat);
            }
            else
            {
                PrintWarning(sysTbl, u"Does not support setting console mode", conStat);
            }
		}

        sysTbl->ConOut->Reset(sysTbl->ConOut, false);
        sysTbl->ConIn->Reset(sysTbl->ConIn, false);

        RenderContext* render = RenderContext::Initialize(sysTbl, imgHndl);
        MonitorContext* monitor = render->GetMonitorContext();

        if (render == nullptr)
        {
            ThrowException(sysTbl, imgHndl, u"Unable to initialize render context", EFI::EFI_STATUS::DEVICE_ERROR);
        }

        /*
        * Select highest resolution
        */

        UINT32 modes = monitor->GetMaxMode();

        Print(sysTbl, u"Number of Modes: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToString(modes));

        UINTN modeInfoSize = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);

        UINTN maxH = 1280;
        UINTN maxV = 720;
        UINT32 HighestResMode = 0;

        MonitorMode* info = nullptr;

        for (UINT32 i = 0; i < modes; i++)
        {
            info = monitor->GetMode(i);
            UINTN r = info->HorizontalResolution / info->VerticalResolution;

            if (info->VerticalResolution == maxV && info->HorizontalResolution == maxH)
            {
                maxH = info->HorizontalResolution;
                maxV = info->VerticalResolution;
                HighestResMode = i;
            }
        }
        
        if (!monitor->SetMode(HighestResMode))
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Set Highest Resolution Mode", EFI::EFI_STATUS::DEVICE_ERROR);
        }

        WaitForKey(sysTbl);

        render->ClearScreen(Colours::White);

        sysTbl->ConOut->SetCursorPosition(sysTbl->ConOut, 0, 0);

        UINTN w = monitor->GetHorizontalResolution();
        UINTN h = monitor->GetVerticalResolution();

        Print(sysTbl, u"Selected Mode: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(monitor->GetCurrentMode()), EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Width: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(w), EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Height: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToString(h));

        UINTN fsCount = FileSystemContext::QueryFSCount(sysTbl, imgHndl);
        Print(sysTbl, u"Number of File Systems: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToString(fsCount));

        if (fsCount == 0)
        {
            ThrowException(sysTbl, imgHndl, u"No File Systems Found", EFI_STATUS::NOT_FOUND);
        }

        EFI_STATUS fsStatus = EFI_STATUS::SUCCESS;
        FileSystemContext sysFs = FileSystemContext::GetFileSystem(sysTbl, imgHndl, u"SYS", &fsStatus);

        if (sysFs == FileSystemContext::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"Sys\"", fsStatus);
        }
        PrintDebug(sysTbl, u"FS Found Found");

        sysFs.OpenVolume();

        FileInfo kernel = sysFs.GetFileInfo(sysTbl, u"Kernel.bin");

        if (sysFs.LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate Kernel", sysFs.LastStatus);
        }

        if (kernel == Empty_FileInfo)
        {
            ThrowException(sysTbl, imgHndl, u"Kernel Not Found", EFI::EFI_STATUS::NOT_FOUND);
        }

        FileHandle kernelHandle = sysFs.OpenFile(sysTbl, &kernel, FileMode::Read, kernel.Attribute);

        if (sysFs.LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Open Kernel", sysFs.LastStatus);
        }

        PrintDebug(sysTbl, u"Kernel Found");
        
        PE32 krnlPE = PE32(&kernelHandle);

        PrintDebug(sysTbl, u"Kernel Loaded");

        if (!krnlPE.IsDosHdrValid())
        {
            ThrowException(sysTbl, imgHndl, u"Invalid DOS Header", EFI::EFI_STATUS::INVALID_PARAMETER);
        }

        if (!krnlPE.IsPEHdrValid())
        {
            ThrowException(sysTbl, imgHndl, u"Invalid PE Header", EFI::EFI_STATUS::INVALID_PARAMETER);
        }

        if (!krnlPE.IsOptHdrValid())
        {
            ThrowException(sysTbl, imgHndl, u"Invalid PE32 Optional Header", EFI::EFI_STATUS::INVALID_PARAMETER);
        }

        if (!krnlPE.IsSectionHdrValid())
        {
            PrintError(sysTbl, u"Invalid PE32 Section Header", EFI::EFI_STATUS::INVALID_PARAMETER);
            Print(sysTbl, UTF16::ToString(Common::System::Allocator::LastStatus()), EFI::EFI_CONSOLE_COLOR::ERROR);
            WaitForKey(sysTbl);
            Exit(sysTbl, imgHndl, Common::System::ToEfiStatus(Common::System::Allocator::LastStatus()));
            //ThrowException(sysTbl, imgHndl, u"Invalid PE32 Section Header", EFI::EFI_STATUS::INVALID_PARAMETER);
        }

        PrintDebug(sysTbl, UTF16::ToHex(krnlPE.OptHdrCommon.AddressOfEntryPoint));

        UINTN imgBase;
        if (krnlPE.PE32hdr.Machine == MachineTypes::I386)
        {
            Print(sysTbl, u"Machine Type: I386 ", EFI::EFI_CONSOLE_COLOR::DEBUG);
            if (krnlPE.OptHdrCommon.Magic.Value == 0x010b)
            {
                PrintDebug(sysTbl, u"File Type: PE32");
                imgBase = krnlPE.OptHdr.PE32->ImageBase;
            }
            else if (krnlPE.OptHdrCommon.Magic.Value == 0x020b)
            {
                PrintDebug(sysTbl, u"File Type: PE32+");
                imgBase = krnlPE.OptHdr.PE32PLUS->ImageBase;
            }
            else
            {
                ThrowException(sysTbl, imgHndl, u"Invalid Magic Value", EFI::EFI_STATUS::INVALID_PARAMETER);
            }
        }
        else if (krnlPE.PE32hdr.Machine == MachineTypes::Amd64)
        {
            Print(sysTbl, u"Machine Type: AMD64 ", EFI::EFI_CONSOLE_COLOR::DEBUG);
            if (krnlPE.OptHdrCommon.Magic.Value == 0x010b)
            {
                PrintDebug(sysTbl, u"File Type: PE32");
                imgBase = krnlPE.OptHdr.PE32->ImageBase;
            }
            else if (krnlPE.OptHdrCommon.Magic.Value == 0x020b)
            {
                PrintDebug(sysTbl, u"File Type: PE32+");
                imgBase = krnlPE.OptHdr.PE32PLUS->ImageBase;
            }
            else
            {
                ThrowException(sysTbl, imgHndl, u"Invalid Magic Value", EFI::EFI_STATUS::INVALID_PARAMETER);
            }
        }
        else
        {
            ThrowException(sysTbl, imgHndl, u"Invalid Machine Type", EFI::EFI_STATUS::INVALID_PARAMETER);
        }

        Print(sysTbl, u"Image Base: ",EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToHex(imgBase),EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Kernel Image Size: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToHex(krnlPE.OptHdr.PE32PLUS->SizeOfImage));

        Print(sysTbl, u"Kernel Buffer Size: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(krnlPE.SizeOfDataBuffer), EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Kernel Entry Point: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        KrnlMain main = (KrnlMain)(krnlPE.GetEntryPoint());
        PrintDebug(sysTbl, UTF16::ToHex(main));

        UINTN entryPVO = krnlPE.GetEntryPointOffset() + (UINTN)&krnlPE.DataBuffer[0];

        Print(sysTbl, u"Kernel Entry Point Virtual Offset: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToHex(entryPVO));

        /* print values of current monitor mode*/
        Print(sysTbl, u"Current Mode: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(monitor->GetCurrentMode()), EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Width: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(monitor->GetHorizontalResolution()), EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Height: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToString(monitor->GetVerticalResolution()));

        /* print Pixel Format and bpp*/
        Print(sysTbl, u"Pixel Format: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(monitor->GetPixelFormat()), EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, u" Pixels Per Scanline: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        Print(sysTbl, UTF16::ToString(monitor->GetPixelsPerScanLine()));
        
        WaitForKey(sysTbl);
        render->ClearScreen(Colours::Aqua);
        UINTN status = main(render, monitor);

        Print(sysTbl, u"Kernel Returned: ", EFI::EFI_CONSOLE_COLOR::DEBUG);
        PrintDebug(sysTbl, UTF16::ToString(status));

        render->Terminate(imgHndl, sysTbl);

        WaitForKey(sysTbl);
        sysTbl->RuntimeServices->ResetSystem(EFI_RESET_TYPE::SHUTDOWN, EFI_STATUS::SUCCESS, 0, nullptr);

        return EFI::EFI_STATUS::END_OF_MEDIA;
    }
}
