#pragma once
#include <UEFIDef.h>

namespace EFI
{
    // FXSAVE_STATE - FP / MMX / XMM registers
    struct EFI_FX_SAVE_STATE_IA32
    {
    public:
        UINT16         Fcw;
        UINT16         Fsw;
        UINT16         Ftw;
        UINT16         Opcode;
        UINT32         Eip;
        UINT16         Cs;
        UINT16         Reserved1;
        UINT32         DataOffset;
        UINT16         Ds;
        UINT8          Reserved2[10];
        UINT8          St0Mm0[10], Reserved3[6];
        UINT8          St1Mm1[10], Reserved4[6];
        UINT8          St2Mm2[10], Reserved5[6];
        UINT8          St3Mm3[10], Reserved6[6];
        UINT8          St4Mm4[10], Reserved7[6];
        UINT8          St5Mm5[10], Reserved8[6];
        UINT8          St6Mm6[10], Reserved9[6];
        UINT8          St7Mm7[10], Reserved10[6];
        UINT8          Xmm0[16];
        UINT8          Xmm1[16];
        UINT8          Xmm2[16];
        UINT8          Xmm3[16];
        UINT8          Xmm4[16];
        UINT8          Xmm5[16];
        UINT8          Xmm6[16];
        UINT8          Xmm7[16];
        UINT8          Reserved11[14 * 16];
    };
}
