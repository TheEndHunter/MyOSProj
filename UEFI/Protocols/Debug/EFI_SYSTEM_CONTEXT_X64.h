#pragma once
#include <UEFIDef.h>
#include "EFI_FX_SAVE_STATE_X64.h"

namespace EFI
{
    // System context for x64 processors
    struct EFI_SYSTEM_CONTEXT_X64
    {
    public:
        UINT64 ExceptionData;   // ExceptionData is
        // additional data pushed
        // on the stack by some
        // types of x64 64-bit
        // mode exceptions
        EFI_FX_SAVE_STATE_X64 FxSaveState;
        UINT64 Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
        UINT64 Cr0, Cr1 /* Reserved */, Cr2, Cr3, Cr4, Cr8;
        UINT64 Rflags;
        UINT64 Ldtr, Tr;
        UINT64 Gdtr[2], Idtr[2];
        UINT64 Rip;
        UINT64 Gs, Fs, Es, Ds, Cs, Ss;
        UINT64 Rdi, Rsi, Rbp, Rsp, Rbx, Rdx, Rcx, Rax;
        UINT64 R8, R9, R10, R11, R12, R13, R14, R15;
    };
}
