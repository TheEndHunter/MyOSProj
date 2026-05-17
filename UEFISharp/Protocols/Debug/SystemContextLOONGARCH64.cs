using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct SystemContextLOONGARCH64
{
    public ulong R0;
    public ulong R1;
    public ulong R2;
    public ulong R3;
    public ulong R4;
    public ulong R5;
    public ulong R6;
    public ulong R7;
    public ulong R8;
    public ulong R9;
    public ulong R10;
    public ulong R11;
    public ulong R12;
    public ulong R13;
    public ulong R14;
    public ulong R15;
    public ulong R16;
    public ulong R17;
    public ulong R18;
    public ulong R19;
    public ulong R20;
    public ulong R21;
    public ulong R22;
    public ulong R23;
    public ulong R24;
    public ulong R25;
    public ulong R26;
    public ulong R27;
    public ulong R28;
    public ulong R29;
    public ulong R30;
    public ulong R31;
    public ulong CRMD;
    public ulong PRMD;
    public ulong EUEN;
    public ulong MISC;
    public ulong ECFG;
    public ulong ESTAT;
    public ulong ERA;
    public ulong BADV;
    public ulong BADI;
}
