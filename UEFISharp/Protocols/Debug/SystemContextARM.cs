using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct SystemContextARM
{
    public uint R0;
    public uint R1;
    public uint R2;
    public uint R3;
    public uint R4;
    public uint R5;
    public uint R6;
    public uint R7;
    public uint R8;
    public uint R9;
    public uint R10;
    public uint R11;
    public uint R12;
    public uint SP;
    public uint LR;
    public uint PC;
    public uint CPSR;
    public uint DFSR;
    public uint DFAR;
    public uint IFSR;
}
