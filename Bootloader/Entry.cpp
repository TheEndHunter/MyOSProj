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
#include <FileTypes/PE/PE32.h>

namespace Bootloader
{
    using namespace Common::Enviroment;
    using namespace Common::FileSystem;
    using namespace Common::Graphics;
    using namespace Common::FileTypes::PE;

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

        /*
        * Select highest resolution
        */

        UINTN modes = gop.GetModeCount();

        Print(sysTbl, u"Number of Modes: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
        PrintDebug(sysTbl, UTF16::ToString(modes));

        UINTN modeInfoSize = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);

        UINTN maxH = 0;
        UINTN maxV = 0;
        UINTN HighestResMode = 0;

        for (UINTN i = 0; i < modes; i++)
        {
            EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info = new EFI_GRAPHICS_OUTPUT_MODE_INFORMATION();
            EFI::EFI_STATUS s = gop.QueryMode(i,&modeInfoSize,&info);

            if (s != EFI::EFI_STATUS::SUCCESS)
            {
				ThrowException(sysTbl, imgHndl,u"Unable to Query GOP modes", s);
			}

            if (info->VerticalResolution > maxV || info->HorizontalResolution > maxH)
            {
                Print(sysTbl, u"Mode: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                Print(sysTbl, UTF16::ToString(i), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                Print(sysTbl, u" Width: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                Print(sysTbl, UTF16::ToString(info->HorizontalResolution), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                Print(sysTbl, u" Height: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                PrintDebug(sysTbl, UTF16::ToString(info->VerticalResolution));

				maxH = info->HorizontalResolution;
				maxV = info->VerticalResolution;
                HighestResMode = i;
			}
            delete info;
		}
        EFI::EFI_STATUS s = gop.SetMode(HighestResMode);
        gop.ClearScreen(Colors::Black);
        sysTbl->ConOut->SetCursorPosition(sysTbl->ConOut, 0, 0);
        
        if (s != EFI::EFI_STATUS::SUCCESS)
        {
            ThrowException(sysTbl,imgHndl, u"Unable to Set GOP mode" ,s);
        }

        UINTN w = gop.GetWidth();
        UINTN h = gop.GetHeight();

        Print(sysTbl, u"Selected Mode: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
        Print(sysTbl, UTF16::ToString(gop.GetCurrentMode()), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
        Print(sysTbl, u" Width: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
        Print(sysTbl, UTF16::ToString(w), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
        Print(sysTbl, u" Height: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
        PrintDebug(sysTbl, UTF16::ToString(h));

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

        PE32 krnlPE = PE32(&kernelHandle);

        if (!krnlPE.IsValid())
        {
			ThrowException(sysTbl, imgHndl, u"Invalid Kernel PE", EFI::EFI_STATUS::INVALID_PARAMETER);
		}

        PrintDebug(sysTbl, UTF16::ToHex(krnlPE.OptHdrCommon.AddressOfEntryPoint));
        
        UINTN imgBase;
        if (krnlPE.PE32hdr.Machine == MachineTypes::I386)
        {
            PrintDebug(sysTbl, u"Machine Type: I386");
            if (krnlPE.OptHdrCommon.Magic.Value = 0x10b)
            {
                PrintDebug(sysTbl, u"Magic: PE32");
                for (UINTN i = 0; i < krnlPE.OptHdr.PE32->NumberOfRvaAndSizes; i++)
                {
                    Print(sysTbl, u"Data Directory: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, UTF16::ToString(i), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl,u"VA: ",EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, UTF16::ToHex(krnlPE.OptHdr.PE32->DataDirectories[i].VirtualAddress), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, u" Size:", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
				    PrintDebug(sysTbl, UTF16::ToString(krnlPE.OptHdr.PE32->DataDirectories[i].Size));
			    }
                imgBase = krnlPE.OptHdr.PE32->ImageBase;
			}
            else if (krnlPE.OptHdrCommon.Magic.Value = 0x20b)
            {
				PrintDebug(sysTbl, u"Magic: PE32+");
                for (UINTN i = 0; i < krnlPE.OptHdr.PE32PLUS->NumberOfRvaAndSizes; i++)
                {
					Print(sysTbl, u"Data Directory: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
					Print(sysTbl, UTF16::ToString(i), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
					Print(sysTbl, u"VA: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
					Print(sysTbl, UTF16::ToHex(krnlPE.OptHdr.PE32PLUS->DataDirectories[i].VirtualAddress), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
					Print(sysTbl, u" Size:", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
					PrintDebug(sysTbl, UTF16::ToString(krnlPE.OptHdr.PE32PLUS->DataDirectories[i].Size));
				}
                imgBase = krnlPE.OptHdr.PE32PLUS->ImageBase;
			}
            else
            {
				ThrowException(sysTbl, imgHndl, u"Invalid Magic Value", EFI::EFI_STATUS::INVALID_PARAMETER);
			}
        }
        else if (krnlPE.PE32hdr.Machine == MachineTypes::Amd64)
        {
            PrintDebug(sysTbl, u"Machine Type: AMD64");
            if (krnlPE.OptHdrCommon.Magic.Value = 0x010B)
            {
                PrintDebug(sysTbl, u"Magic: PE32");
                for (UINTN i = 0; i < krnlPE.OptHdr.PE32->NumberOfRvaAndSizes; i++)
                {
                    Print(sysTbl, u"Data Directory: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, UTF16::ToString(i), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, u"VA: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, UTF16::ToHex(krnlPE.OptHdr.PE32->DataDirectories[i].VirtualAddress), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, u" Size:", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    PrintDebug(sysTbl, UTF16::ToString(krnlPE.OptHdr.PE32->DataDirectories[i].Size));
                }
                imgBase = krnlPE.OptHdr.PE32->ImageBase;
            }
            else if (krnlPE.OptHdrCommon.Magic.Value = 0x020B)
            {
                PrintDebug(sysTbl, u"Magic: PE32+");
                for (UINTN i = 0; i < krnlPE.OptHdr.PE32PLUS->NumberOfRvaAndSizes; i++)
                {
                    Print(sysTbl, u"Data Directory: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, UTF16::ToString(i), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, u"VA: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, UTF16::ToHex(krnlPE.OptHdr.PE32PLUS->DataDirectories[i].VirtualAddress), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    Print(sysTbl, u" Size:", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
                    PrintDebug(sysTbl, UTF16::ToString(krnlPE.OptHdr.PE32PLUS->DataDirectories[i].Size));
                }
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

        PrintDebug(sysTbl, u"Image Base: ");
        PrintDebug(sysTbl, UTF16::ToHex(imgBase));

        CHAR16 name[9] = { '\0','\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' };
        for (UINTN i = 0; i < krnlPE.PE32hdr.NumberOfSections; i++)
        {
            PE32SectionHeader* section = &krnlPE.SectionHeaders[i];
            Print(sysTbl, u"Section: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            Print(sysTbl, UTF16::ToString(i), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            Print(sysTbl, u" Name: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            name[0] = section->Name[0];
            name[1] = section->Name[1];
            name[2] = section->Name[2];
            name[3] = section->Name[3];
            name[4] = section->Name[4];
            name[5] = section->Name[5];
            name[6] = section->Name[6];
            name[7] = section->Name[7];
            name[8] = u'\0';
            Print(sysTbl, &name[0], EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
			Print(sysTbl, u" VA: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
			Print(sysTbl, UTF16::ToHex(section->VirtualAddress), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
			Print(sysTbl, u" Size: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
			Print(sysTbl, UTF16::ToString(section->SizeOfRawData));
            Print(sysTbl, u" RawDataOffset: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            Print(sysTbl, UTF16::ToHex(section->PointerToRawData), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            Print(sysTbl, u" NO Relocations: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            Print(sysTbl, UTF16::ToString(section->NumberOfRelocations), EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            Print(sysTbl, u" NO Line Numbers: ", EFI::EFI_CONSOLE_COLOR::DEBUG_COLOR);
            PrintDebug(sysTbl, UTF16::ToString(section->NumberOfLinenumbers));
        }

        gop.Terminate(imgHndl, sysTbl);

        WaitForKey(sysTbl);
        sysTbl->RuntimeServices->ResetSystem(EFI_RESET_TYPE::SHUTDOWN, EFI_STATUS::SUCCESS, 0, nullptr);

        return EFI::EFI_STATUS::END_OF_MEDIA;
    }
}