#pragma once
#include <UEFIDef.h>

namespace Efi
{
    CONST UINT32 AbspTouchActive = 0x00000001;
    CONST UINT32 AbsAltActive = 0x00000002;

    struct AbsolutePointerState
    {
        public:
        UINT64                 CurrentX;
        UINT64                 CurrentY;
        UINT64                 CurrentZ;
        UINT32                 ActiveButtons;
    };
}