#include "Entry.h"
#include <ResetType.h>
#include <Protocols/IO/Console/ConsoleColor.h>
#include <Graphics/Colour.h>
#include <System/Environment/Unicode.h>
#include <FileSystem/ESP/ESP_FS_Context.h>
#include <System/MemoryManagement/Allocator.h>
#include <System/MemoryManagement/AllocatorStatus.h>
#include <FileTypes/PE/PE32.h>
#include <Graphics/RenderContext.h>
#include <EFIConsole.h>
#include <Debugging/Debugger.h>
#include <CRT/CRT_Stubs.h>
#include <System/Environment/KernelErrors.h>
#include <Protocols/IO/Serial/SerialIOProtocol.h>

namespace Bootloader
{
    using namespace Common::FileSystem;
    using namespace Common::System::Environment;
    using namespace Common::Graphics;
    using namespace Common::FileTypes::PE;
    using namespace Efi;

    typedef Common::System::Environment::KernelError(CDECL*KrnlMain)(Common::System::MemoryManagement::Allocator* efiAlloc, Common::Debugging::Debugger* debugger,RenderContext* rendererCtx, MonitorContext* monitorCtx, Common::FileSystem::ESP::ESP_FS_Context* efiSysPart, Common::FileSystem::ESP::ESP_FS_Context* sysPart, Common::FileSystem::ESP::ESP_FS_Context* libPart);
    

    extern "C" Status EFIAPI EfiMain(Handle imgHndl, SystemTable* sysTbl)
    {
        // Attempt to write an early diagnostic to any Serial IO protocol (COM) so -serial stdio can capture it
        Efi::SerialIOProtocol* serial = nullptr;
        Status serStat = sysTbl->BootServices->LocateProtocol((Efi::Guid*)&Efi::SerialIOProtocolGuid, nullptr, (void**)&serial);
        if (serStat == Efi::Status::Success && serial != nullptr)
        {
        const CHAR8 testMsg[] = u8"*** EfiMain reached (serial test) ***\r\n";
        // Use sizeof to get the byte length (exclude terminating NUL)
        UINTN writeSize = sizeof(testMsg) - 1;
        // Serial Write expects a buffer size in bytes and returns a status
        Status writeStat = serial->Write(serial, &writeSize, (VOID*)testMsg);
        if (writeStat != Efi::Status::Success)
        {
            PrintWarningLine(sysTbl, u"Serial Write returned error: ", writeStat);
        }
        }
        PrintLine(sysTbl, u"*** EfiMain reached Print***");
        CRT_Initialize();
        PrintLine(sysTbl, u"***CRT Initialized***");
        UTF<CHAR>();
        UTF<CHAR8>();
        UTF<CHAR16>();

        Common::System::MemoryManagement::Allocator::SetEfiAllocator(sysTbl);
        auto* alloc = Common::System::MemoryManagement::Allocator::GetInstance();

        if (!alloc->IsInitalized())
		{
            ThrowException(sysTbl, imgHndl, u"Could Not Set EFI Allocator", Common::System::MemoryManagement::ToEfiStatus(alloc->LastStatus()));
		}
        PrintLine(sysTbl, u"***Allocator Initialized***");

        UINT32 mm = sysTbl->ConOut->Mode->MaxMode;
        UINTN Columns = 0;
        UINTN Rows = 0;
        UINTN bestMode = 0;
        UINT64 bestArea = 0;

        for (UINTN m = 0; m < mm; m++)
        {
            UINTN CurrentC = 0;
            UINTN CurrentR = 0;

            Status queryStat = sysTbl->ConOut->QueryMode(sysTbl->ConOut, m, &CurrentC, &CurrentR);

            if (queryStat == Status::Success)
            {
                // Protect against weird zero values
                if (CurrentC == 0 || CurrentR == 0)
                {
                    continue;
                }

                UINT64 area = (UINT64)CurrentC * (UINT64)CurrentR;
                if (area > bestArea)
                {
                    bestArea = area;
                    Columns = CurrentC;
                    Rows = CurrentR;
                    bestMode = m;
                }
                continue;
            }

            PrintWarningLine(sysTbl, u"Query Mode returned an error: ", queryStat);
        }

        Status conStat = sysTbl->ConOut->SetMode(sysTbl->ConOut, bestMode);

        if (conStat != Status::Success)
		{
            if (conStat != Status::Unsupported)
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

        PrintInfoLine(sysTbl, u"Renderer Initalized");

        if (render == nullptr)
        {
			ThrowException(sysTbl, imgHndl, u"Unable to initialize render context", Efi::Status::DeviceError);
        }

        /*
        * Select highest resolution
        */

        UINT32 modes = monitor->GetMaxMode();

        UINTN modeInfoSize = sizeof(GraphicsOutputModeInformation);

        UINTN maxH = 1280;
        UINTN maxV = 720;
        UINT32 HighestResMode = 0;

        MonitorMode* info = nullptr;

        for (UINT32 i = 0; i < modes; i++)
        {
            info = monitor->GetMode(i);
            if (info == nullptr) continue;
            if (info->VerticalResolution == 0) continue;

            // choose the mode with the largest area (width * height)
            UINT64 area = (UINT64)info->HorizontalResolution * (UINT64)info->VerticalResolution;
            if (area > (UINT64)maxH * (UINT64)maxV)
            {
                maxH = info->HorizontalResolution;
                maxV = info->VerticalResolution;
                HighestResMode = i;
            }
        }
        
        if (!monitor->SetMode(HighestResMode))
        {
			ThrowException(sysTbl, imgHndl, u"Could Not Set Highest Resolution Mode", Efi::Status::DeviceError);
        }

		PrintInfoLine(sysTbl, u"Highest Resolution Mode Set");
        WaitForAnyKey(sysTbl);
		ClearConOut(sysTbl);

        sysTbl->ConOut->SetCursorPosition(sysTbl->ConOut, 0, 0);

        Common::Debugging::Debugger debug = Common::Debugging::Debugger(sysTbl);
        Common::FileSystem::SetFileSystemDebugger(&debug);
        Common::FileSystem::ESP::SetESPDebugger(&debug);

        UINTN fsCount = ESP::ESP_FS_Context::QueryFSCount(sysTbl, imgHndl);

        if (fsCount == 0)
        {
			ThrowException(sysTbl, imgHndl, u"No File Systems Found", Status::NotFound);
        }

        // Use EFIConsole helpers to print info
        Bootloader::Print(sysTbl, u"Found File Systems: ");
        Bootloader::PrintLine(sysTbl, UTF<CHAR16>::ToString(fsCount));

        Status fsStatus = Status::Success;
        ESP::ESP_FS_Context sysFs = ESP::ESP_FS_Context::GetFileSystem(sysTbl, imgHndl, u"SYS", &fsStatus);

        if (sysFs == ESP::ESP_FS_Context::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"SYS\"", fsStatus);
        }

		PrintInfoLine(sysTbl, u"Got SYS File System");

        sysFs.OpenVolume();

        PrintInfoLine(sysTbl,u"Finding Kernel...");

        Common::FileSystem::FileInfo kernel = sysFs.GetFileInfo(u"Kernel.bin");

        if (sysFs.LastStatus != Efi::Status::Success)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate Kernel ", sysFs.LastStatus);
        }

        if (kernel == Empty_FileInfo)
        {
			ThrowException(sysTbl, imgHndl, u"Kernel Not Found", Efi::Status::NotFound);
        }

        Common::FileSystem::FileHandle kernelHandle = sysFs.OpenFile(&kernel, Common::FileSystem::FileMode::Read, kernel.Attribute);

        if (sysFs.LastStatus != Efi::Status::Success)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Open Kernel", sysFs.LastStatus);
        }

        PE32 krnlPE = PE32(&kernelHandle);

        kernelHandle.Close();

        if (!krnlPE.IsDosHdrValid())
        {
            ThrowException(sysTbl, imgHndl, u"Invalid DOS Header", Efi::Status::InvalidParameter);
        }

        if (!krnlPE.IsPEHdrValid())
        {
            ThrowException(sysTbl, imgHndl, u"Invalid PE Header", Efi::Status::InvalidParameter);
        }

        if (!krnlPE.IsOptHdrValid())
        {
            ThrowException(sysTbl, imgHndl, u"Invalid PE32 Optional Header", Efi::Status::InvalidParameter);
        }

        if (!krnlPE.IsSectionHdrValid())
        {
            PrintErrorLine(sysTbl, u"Invalid PE32 Section Header", Efi::Status::InvalidParameter);
            Print(sysTbl, UTF<CHAR16>::ToString(alloc->LastStatus()), Efi::ConsoleColor::_Error);
            WaitForAnyKey(sysTbl);
            Exit(sysTbl, imgHndl, Common::System::MemoryManagement::ToEfiStatus(alloc->LastStatus()),0,nullptr);
            //ThrowException(sysTbl, imgHndl, u"Invalid PE32 Section Header", Efi::Status::InvalidParameter);
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
                ThrowException(sysTbl, imgHndl, u"Invalid Magic Value", Efi::Status::InvalidParameter);
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
                ThrowException(sysTbl, imgHndl, u"Invalid Magic Value", Efi::Status::InvalidParameter);
            }
        }
        else
        {
            ThrowException(sysTbl, imgHndl, u"Invalid Machine Type", Efi::Status::InvalidParameter);
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
        PrintLine(sysTbl, u"Got efiFS");
        if (efiFs == ESP::ESP_FS_Context::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"EFI\"", fsStatus);
        }

		ESP::ESP_FS_Context libFs = ESP::ESP_FS_Context::GetFileSystem(sysTbl, imgHndl, u"LIBS", &fsStatus);
        PrintLine(sysTbl, u"Got libFS");
        if (libFs == ESP::ESP_FS_Context::EmptyFS)
        {
            ThrowException(sysTbl, imgHndl, u"Could Not Locate File System with Label: \"LIBS\"", fsStatus);
        }


		render->ClearScreen(TRUE);
        ClearConOut(sysTbl);
        sysTbl->ConOut->SetCursorPosition(sysTbl->ConOut, 0, 0);

        
        
		PrintLine(sysTbl, u"Press Enter to start Kernel...");
        WaitForKey(sysTbl, u'\r');

        // Diagnostic: dump first bytes at the computed entry point to help detect loader/mapping issues
        {
            const void* entryPtrConst = krnlPE.GetEntryPoint();
            void* entryPtr = const_cast<void*>(entryPtrConst);
            UINT8* bytes = (UINT8*)entryPtr;
            Bootloader::Print(sysTbl, u"Kernel Entry Point: ");
            Bootloader::PrintLine(sysTbl, UTF<CHAR16>::ToHex((UINT64)(UINTN)entryPtr));

            const UINTN DUMP_BYTES = 64;
            UINTN zeroCount = 0;
            for (UINTN off = 0; off < DUMP_BYTES; off += 8)
            {
                // print address
                Print(sysTbl, UTF<CHAR16>::ToHex((UINT64)(UINTN)(bytes + off)));
                Print(sysTbl, u": ");

                UINT64 chunk = 0;
                for (UINTN b = 0; b < 8; ++b)
                {
                    UINTN idx = off + b;
                    UINT8 v = 0;
                    // avoid reading past a bogus pointer - try/catch not available; assume readable
                    v = bytes[idx];
                    chunk |= ((UINT64)v) << (b * 8);
                    if (v == 0) zeroCount++;
                }

                PrintLine(sysTbl, UTF<CHAR16>::ToHex(chunk));
            }

            if (zeroCount >= DUMP_BYTES)
            {
                // All zeros in the first region - likely mapped incorrectly
                PrintErrorLine(sysTbl, u"Kernel entry region appears to be all zeros; loader may have mapped data incorrectly.", Efi::Status::LoadError);
                PrintErrorLine(sysTbl, u"Aborting jump to kernel for safety.", Efi::Status::LoadError);
                WaitForAnyKey(sysTbl);
                Exit(sysTbl, imgHndl, Efi::Status::LoadError);
            }
        }

        auto main = (KrnlMain)(krnlPE.GetEntryPoint());
        Common::System::Environment::KernelError status = main(alloc,&debug,render, monitor,&efiFs,&sysFs,&libFs);

        switch (status)
        {
        case Common::System::Environment::KernelError::Success:
            break;
        default:
			Print(sysTbl, u"Kernel Error: ",ConsoleColor::_Error);
			Print(sysTbl, UTF<CHAR16>::ToHex((UINT64)status), ConsoleColor::_Error);
            Print(sysTbl, UTF<CHAR16>::NewLine, ConsoleColor::_Error);
			PrintLine(sysTbl, u"Press Enter to continue...",ConsoleColor::_Error);
            break;
        }

        render->Terminate(imgHndl, sysTbl);

        WaitForAnyKey(sysTbl);
        sysTbl->RuntimeServices->ResetSystem(ResetType::Shutdown, Status::Success, 0, nullptr);

        _CRT_TERM();

		return Efi::Status::NotStarted;
    }
}

