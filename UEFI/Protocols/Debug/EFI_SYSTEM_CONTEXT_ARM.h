#pragma once
#include <UEFIDef.h>

namespace EFI
{
    //
    // ARM processor context definition
    //
    struct EFI_SYSTEM_CONTEXT_ARM
    {
    public:
        UINT32 R0;
        UINT32 R1;
        UINT32 R2;
        UINT32 R3;
        UINT32 R4;
        UINT32 R5;
        UINT32 R6;
        UINT32 R7;
        UINT32 R8;
        UINT32 R9;
        UINT32 R10;
        UINT32 R11;
        UINT32 R12;
        UINT32 SP;
        UINT32 LR;
        UINT32 PC;
        UINT32 CPSR;
        UINT32 DFSR;
        UINT32 DFAR;
        UINT32 IFSR;
    };
}
