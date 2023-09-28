#pragma once
#include <UEFIDef.h>
#include "EFI_FX_SAVE_STATE_IA32.h"

namespace EFI
{
    // System context for IA-32 processors
    struct EFI_SYSTEM_CONTEXT_IA32
    {
    public:
        UINT32 ExceptionData;   // ExceptionData is additional data pushed
        // on the stack by some types of IA-32
        // exceptions
        EFI_FX_SAVE_STATE_IA32     FxSaveState;
        UINT32                     Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
        UINT32                     Cr0, Cr1 /* Reserved */, Cr2, Cr3, Cr4;
        UINT32                     Eflags;
        UINT32                     Ldtr, Tr;
        UINT32                     Gdtr[2], Idtr[2];
        UINT32                     Eip;
        UINT32                     Gs, Fs, Es, Ds, Cs, Ss;
        UINT32                     Edi, Esi, Ebp, Esp, Ebx, Edx, Ecx, Eax;
    };
}
