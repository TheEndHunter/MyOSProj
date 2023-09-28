#pragma once
#include <UEFIDef.h>

namespace EFI
{
    // System context for virtual EBC processors
    struct EFI_SYSTEM_CONTEXT_EBC
    {
    public:
        UINT64 R0, R1, R2, R3, R4, R5, R6, R7;
        UINT64 Flags;
        UINT64 ControlFlags;
        UINT64 Ip;
    };
}
