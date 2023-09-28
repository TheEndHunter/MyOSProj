#pragma once
#include <UEFIDef.h>
namespace EFI
{
    // System context for LoongArch64 processors
    struct EFI_SYSTEM_CONTEXT_LOONGARCH64
    {
    public:
        UINT64    R0;
        UINT64    R1;
        UINT64    R2;
        UINT64    R3;
        UINT64    R4;
        UINT64    R5;
        UINT64    R6;
        UINT64    R7;
        UINT64    R8;
        UINT64    R9;
        UINT64    R10;
        UINT64    R11;
        UINT64    R12;
        UINT64    R13;
        UINT64    R14;
        UINT64    R15;
        UINT64    R16;
        UINT64    R17;
        UINT64    R18;
        UINT64    R19;
        UINT64    R20;
        UINT64    R21;
        UINT64    R22;
        UINT64    R23;
        UINT64    R24;
        UINT64    R25;
        UINT64    R26;
        UINT64    R27;
        UINT64    R28;
        UINT64    R29;
        UINT64    R30;
        UINT64    R31;

        UINT64    CRMD;  // CuRrent MoDe information
        UINT64    PRMD;  // PRe-exception MoDe information
        UINT64    EUEN;  // Extended component Unit ENable
        UINT64    MISC;  // MISCellaneous controller
        UINT64    ECFG;  // Execption ConFiGuration
        UINT64    ESTAT; // Exeption STATus
        UINT64    ERA;   // Exception Return Address
        UINT64    BADV;  // BAD Virtual address
        UINT64    BADI;  // BAD Instruction
    };
}