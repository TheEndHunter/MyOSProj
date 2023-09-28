#include <EFI_STATUS.h>
#include <EFI_HANDLE.h>
#include <EFI_SYSTEM_TABLE.h>
// Kernel.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
namespace kernel
{
    using namespace EFI;

    EFI_STATUS KrnlMain(EFI::EFI_HANDLE handle, EFI::EFI_SYSTEM_TABLE* systemTable)
    {
        return EFI_STATUS::SUCCESS;
    }
}
