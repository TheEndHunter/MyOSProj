#pragma once
#include <UEFIDef.h>

namespace EFI
{
    //
    ///
    /// AARCH64 processor context definition.
    ///
    struct EFI_SYSTEM_CONTEXT_AARCH64
    {
    public:
        // General Purpose Registers
        UINT64 X0;
        UINT64 X1;
        UINT64 X2;
        UINT64 X3;
        UINT64 X4;
        UINT64 X5;
        UINT64 X6;
        UINT64 X7;
        UINT64 X8;
        UINT64 X9;
        UINT64 X10;
        UINT64 X11;
        UINT64 X12;
        UINT64 X13;
        UINT64 X14;
        UINT64 X15;
        UINT64 X16;
        UINT64 X17;
        UINT64 X18;
        UINT64 X19;
        UINT64 X20;
        UINT64 X21;
        UINT64 X22;
        UINT64 X23;
        UINT64 X24;
        UINT64 X25;
        UINT64 X26;
        UINT64 X27;
        UINT64 X28;
        UINT64 FP; // x29 - Frame Pointer
        UINT64 LR; // x30 - Link Register
        UINT64 SP; // x31 - Stack Pointer
        // FP/SIMD Registers
        UINT64 V0[2];
        UINT64 V1[2];
        UINT64 V2[2];
        UINT64 V3[2];
        UINT64 V4[2];
        UINT64 V5[2];
        UINT64 V6[2];
        UINT64 V7[2];
        UINT64 V8[2];
        UINT64 V9[2];
        UINT64 V10[2];
        UINT64 V11[2];
        UINT64 V12[2];
        UINT64 V13[2];
        UINT64 V14[2];
        UINT64 V15[2];
        UINT64 V16[2];
        UINT64 V17[2];
        UINT64 V18[2];
        UINT64 V19[2];
        UINT64 V20[2];
        UINT64 V21[2];
        UINT64 V22[2];
        UINT64 V23[2];
        UINT64 V24[2];
        UINT64 V25[2];
        UINT64 V26[2];
        UINT64 V27[2];
        UINT64 V28[2];
        UINT64 V29[2];
        UINT64 V30[2];
        UINT64 V31[2];
        UINT64 ELR;       // Exception Link Register
        UINT64 SPSR;      // Saved Processor Status Register
        UINT64 FPSR;      // Floating Point Status Register
        UINT64 ESR;       // Exception syndrome register
        UINT64 FAR;       // Fault Address Register
    };
}
