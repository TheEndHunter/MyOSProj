using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SystemContextIA32
{
    public uint ExceptionData;
    public FxSaveStateIA32 FxSaveState;
    public uint Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
    public uint Cr0, Cr1, Cr2, Cr3, Cr4;
    public uint Eflags;
    public uint Ldtr, Tr;
    public fixed uint Gdtr[2];
    public fixed uint Idtr[2];
    public uint Eip;
    public uint Gs, Fs, Es, Ds, Cs, Ss;
    public uint Edi, Esi, Ebp, Esp, Ebx, Edx, Ecx, Eax;
}
