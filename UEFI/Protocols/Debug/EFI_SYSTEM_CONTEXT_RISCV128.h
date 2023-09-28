#pragma once
#include <UEFIDef.h>

namespace EFI
{
    // System context for RISC-V 128
    struct EFI_SYSTEM_CONTEXT_RISCV128
    {
    public:
        // Integer registers
        UINT128 Zero, Ra, Sp, Gp, Tp, T0, T1, T2;
        UINT128 S0FP, S1, A0, A1, A2, A3, A4, A5, A6, A7;
        UINT128 S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;
        UINT128 T3, T4, T5, T6;

        // Floating registers for F, D and Q Standard Extensions
        UINT128 Ft0, Ft1, Ft2, Ft3, Ft4, Ft5, Ft6, Ft7;
        UINT128 Fs0, Fs1, Fa0, Fa1, Fa2, Fa3, Fa4, Fa5, Fa6, Fa7;
        UINT128 Fs2, Fs3, Fs4, Fs5, Fs6, Fs7, Fs8, Fs9, Fs10, Fs11;
        UINT128 Ft8, Ft9, Ft10, Ft11;
    };
}