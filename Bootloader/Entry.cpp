#include "Entry.h"
#include <EFI_RESET_TYPE.h>
#include <Protocols/IO/Console/EFI_CONSOLE_COLOR.h>
#include <Graphics/Colour.h>
#include <System/Environment/Unicode.h>
#include <FileSystem/ESP/ESP_FS_Context.h>
#include <System/MemoryManagement/Allocator.h>
#include <System/MemoryManagement/AllocatorStatus.h>
#include <FileTypes/PE/PE32.h>
#include <Graphics/RenderContext.h>
#include <EFIConsole.h>
#include <Debugging/Debugger.h>
#include <CRT_ENTRIES.h>
#include <System/Environment/KernelErrors.h>

namespace Bootloader
{
    using namespace Common::FileSystem;
    using namespace Common::System::Environment;
    using namespace Common::Graphics;
    using namespace Common::FileTypes::PE;
    using namespace EFI;

    typedef Common::System::Environment::KernelError(CDECL*KrnlMain)(Common::System::MemoryManagement::Allocator* efiAlloc, Common::Debugging::Debugger* debugger,RenderContext* rendererCtx, MonitorContext* monitorCtx, Common::FileSystem::ESP::ESP_FS_Context* efiSysPart, Common::FileSystem::ESP::ESP_FS_Context* sysPart, Common::FileSystem::ESP::ESP_FS_Context* libPart);
    

    EFI_STATUS EfiMain(EFI_HANDLE imgHndl, EFI_SYSTEM_TABLE* sysTbl)
    {
        _CRT_INIT();

        UTF<CHAR>();
        UTF<CHAR8>();
        UTF<CHAR16>();

        Common::System::MemoryManagement::Allocator::SetEfiAllocator(sysTbl);
        auto* alloc = Common::System::MemoryManagement::Allocator::GetInstance();


        if (!alloc->IsInitalized())
		{
            ThrowException(sysTbl, imgHndl, u"Could Not Set EFI Allocator", Common::System::MemoryManagement::ToEfiStatus(alloc->LastStatus()));
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

            PrintWarningLine(sysTbl, u"Query Mode returned an error: ", queryStat);
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
                PrintWarningLine(sysTbl, u"Does not support setting console mode", conStat);
            }
		}

        ClearConIn(sysTbl);
		ClearConOut(sysTbl);


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

		ClearConOut(sysTbl);
        sysTbl->ConOut->SetCursorPosition(sysTbl->ConOut, 0, 0);

        UINTN fsCount = ESP::ESP_FS_Context::QueryFSCount(sysTbl, imgHndl);
        if (fsCount == 0)
        {
            ThrowException(sysTbl, imgHndl, u"No File Systems Found", EFI_STATUS::NOT_FOUND);
        }

        EFI_STATUS fsStatus = EFI_STATUS::SUCCESS;
        ESP::ESP_FS_Context sysFs = ESP::ESP_FS_Context::GetFileSystem(sysTbl, imgHndl, u"SYS", &fsStatus);

        if (sysFs == ESP::ESP_FS_Context::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"SYS\"", fsStatus);
        }

        sysFs.OpenVolume();

        FileInfo kernel = sysFs.GetFileInfo(u"Kernel.bin");

        if (sysFs.LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate Kernel", sysFs.LastStatus);
        }

        if (kernel == Empty_FileInfo)
        {
            ThrowException(sysTbl, imgHndl, u"Kernel Not Found", EFI::EFI_STATUS::NOT_FOUND);
        }

        FileHandle kernelHandle = sysFs.OpenFile(&kernel, FileMode::Read, kernel.Attribute);

        if (sysFs.LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Open Kernel", sysFs.LastStatus);
        }

        PE32 krnlPE = PE32(&kernelHandle);

        kernelHandle.Close();

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
            PrintErrorLine(sysTbl, u"Invalid PE32 Section Header", EFI::EFI_STATUS::INVALID_PARAMETER);
            Print(sysTbl, UTF<CHAR16>::ToString(alloc->LastStatus()), EFI::EfiConsoleColor::_Error);
            WaitForAnyKey(sysTbl);
            Exit(sysTbl, imgHndl, Common::System::MemoryManagement::ToEfiStatus(alloc->LastStatus()),0,nullptr);
            //ThrowException(sysTbl, imgHndl, u"Invalid PE32 Section Header", EFI::EFI_STATUS::INVALID_PARAMETER);
        }

        UINTN imgBase;
        if (krnlPE.PE32hdr.Machine == MachineTypes::I386)
        {
            if (krnlPE.OptHdrCommon.Magic.Value == 0x010b)
            {
                imgBase = krnlPE.OptHdr.PE32->ImageBase;
            }
            else if (krnlPE.OptHdrCommon.Magic.Value == 0x020b)
            {
                imgBase = krnlPE.OptHdr.PE32PLUS->ImageBase;
            }
            else
            {
                ThrowException(sysTbl, imgHndl, u"Invalid Magic Value", EFI::EFI_STATUS::INVALID_PARAMETER);
            }
        }
        else if (krnlPE.PE32hdr.Machine == MachineTypes::Amd64)
        {
            if (krnlPE.OptHdrCommon.Magic.Value == 0x010b)
            {
                imgBase = krnlPE.OptHdr.PE32->ImageBase;
            }
            else if (krnlPE.OptHdrCommon.Magic.Value == 0x020b)
            {
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

		if (!sysFs.IsRootDirectory())
		{
			PrintDebugLine(sysTbl, u"Returning to Root Directory");
			if(!sysFs.ReturnToRootDirectory())
            {
				ThrowException(sysTbl, imgHndl, u"Could Not Return to Root Directory", sysFs.LastStatus);
            }
		}

        ESP::ESP_FS_Context efiFs = ESP::ESP_FS_Context::GetFileSystem(sysTbl, imgHndl, u"EFI", &fsStatus);

        if (efiFs == ESP::ESP_FS_Context::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"EFI\"", fsStatus);
        }

		ESP::ESP_FS_Context libFs = ESP::ESP_FS_Context::GetFileSystem(sysTbl, imgHndl, u"LIBS", &fsStatus);

        if (libFs == ESP::ESP_FS_Context::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"LIBS\"", fsStatus);
        }

		render->ClearScreen(TRUE);
        ClearConOut(sysTbl);
        sysTbl->ConOut->SetCursorPosition(sysTbl->ConOut, 0, 0);


        Common::Debugging::Debugger debug = Common::Debugging::Debugger(sysTbl);

		PrintLine(sysTbl, u"Press Enter to start Kernel...");
        WaitForKey(sysTbl, u'\r');

        KrnlMain main = (KrnlMain)(krnlPE.GetEntryPoint());
        Common::System::Environment::KernelError status = main(alloc,&debug,render, monitor,&efiFs,&sysFs,&libFs);

        switch (status)
        {
        case Common::System::Environment::KernelError::Success:
            break;
        default:
			Print(sysTbl, u"Kernel Error: ",EfiConsoleColor::_Error);
			Print(sysTbl, UTF<CHAR16>::ToString((UINT64)status), EfiConsoleColor::_Error);
            Print(sysTbl, UTF<CHAR16>::NewLine, EfiConsoleColor::_Error);
			PrintLine(sysTbl, u"Press Enter to continue...",EfiConsoleColor::_Error);
            break;
        }

        render->Terminate(imgHndl, sysTbl);

        WaitForAnyKey(sysTbl);
        sysTbl->RuntimeServices->ResetSystem(EFI_RESET_TYPE::SHUTDOWN, EFI_STATUS::SUCCESS, 0, nullptr);

        _CRT_TERM();

        return EFI::EFI_STATUS::NOT_STARTED;
    }
}

