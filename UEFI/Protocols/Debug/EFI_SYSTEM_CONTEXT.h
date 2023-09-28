#pragma once
#include <UEFIDef.h>
#include "EFI_SYSTEM_CONTEXT_LOONGARCH64.h"
#include "EFI_SYSTEM_CONTEXT_AARCH64.h"
#include "EFI_SYSTEM_CONTEXT_ARM.h"
#include "EFI_SYSTEM_CONTEXT_IFP.h"
#include "EFI_SYSTEM_CONTEXT_X64.h"
#include "EFI_SYSTEM_CONTEXT_IA32.h"
#include "EFI_SYSTEM_CONTEXT_RISCV128.h"
#include "EFI_SYSTEM_CONTEXT_RISCV64.h"
#include "EFI_SYSTEM_CONTEXT_RISCV32.h"
#include "EFI_SYSTEM_CONTEXT_EBC.h"

namespace EFI
{

    typedef union EFI_SYSTEM_CONTEXT
    {
        EFI_SYSTEM_CONTEXT_EBC* SystemContextEbc;
        EFI_SYSTEM_CONTEXT_IA32* SystemContextIa32;
        EFI_SYSTEM_CONTEXT_X64* SystemContextX64;
        EFI_SYSTEM_CONTEXT_IPF* SystemContextIpf;
        EFI_SYSTEM_CONTEXT_ARM* SystemContextArm;
        EFI_SYSTEM_CONTEXT_AARCH64* SystemContextAArch64;
        EFI_SYSTEM_CONTEXT_RISCV32* SystemContextRiscV32;
        EFI_SYSTEM_CONTEXT_RISCV64* SystemContextRiscV64;
        EFI_SYSTEM_CONTEXT_RISCV128* SystemContextRiscv128;
        EFI_SYSTEM_CONTEXT_LOONGARCH64* SystemContextLongArch64;
    };
}