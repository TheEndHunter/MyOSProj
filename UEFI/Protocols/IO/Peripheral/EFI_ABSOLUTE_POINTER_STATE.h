#pragma once
#include <UEFIDef.h>

namespace EFI
{
    inline const UINT32 EFI_ABSP_TouchActive = 0x00000001;
    inline const UINT32 EFI_ABS_AltActive = 0x00000002;

    struct EFI_ABSOLUTE_POINTER_STATE
    {
        public:
        UINT64                 CurrentX;
        UINT64                 CurrentY;
        UINT64                 CurrentZ;
        UINT32                 ActiveButtons;
    };
}