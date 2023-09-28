#pragma once
#include <UEFIDef.h>

namespace EFI
{
    // System context for Itanium processor family
    struct EFI_SYSTEM_CONTEXT_IPF
    {
    public:
        UINT64 Reserved;

        UINT64 R1, R2, R3, R4, R5, R6, R7, R8, R9, R10,
            R11, R12, R13, R14, R15, R16, R17, R18, R19, R20,
            R21, R22, R23, R24, R25, R26, R27, R28, R29, R30,
            R31;

        UINT64 F2[2], F3[2], F4[2], F5[2], F6[2],
            F7[2], F8[2], F9[2], F10[2], F11[2],
            F12[2], F13[2], F14[2], F15[2], F16[2],
            F17[2], F18[2], F19[2], F20[2], F21[2],
            F22[2], F23[2], F24[2], F25[2], F26[2],
            F27[2], F28[2], F29[2], F30[2], F31[2];

        UINT64 Pr;

        UINT64 B0, B1, B2, B3, B4, B5, B6, B7;

        // application registers
        UINT64      ArRsc, ArBsp, ArBspstore, ArRnat;
        UINT64      ArFcr;
        UINT64      ArEflag, ArCsd, ArSsd, ArCflg;
        UINT64      ArFsr, ArFir, ArFdr;
        UINT64      ArCcv;
        UINT64      ArUnat;
        UINT64      ArFpsr;
        UINT64      ArPfs, ArLc, ArEc;

        // control registers
        UINT64      CrDcr, CrItm, CrIva, CrPta, CrIpsr, CrIsr;
        UINT64      CrIip, CrIfa, CrItir, CrIipa, CrIfs, CrIim;
        UINT64      CrIha;

        // debug registers
        UINT64      Dbr0, Dbr1, Dbr2, Dbr3, Dbr4, Dbr5, Dbr6, Dbr7;
        UINT64      Ibr0, Ibr1, Ibr2, Ibr3, Ibr4, Ibr5, Ibr6, Ibr7;

        // virtual registers
        UINT64      IntNat; // nat bits for R1-R31

    };
}
