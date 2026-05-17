using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SystemContextX64
{
    public ulong ExceptionData;
    public FxSaveStateX64 FxSaveState;
    public ulong Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
    public ulong Cr0, Cr1, Cr2, Cr3, Cr4, Cr8;
    public ulong Rflags;
    public ulong Ldtr, Tr;
    public fixed ulong Gdtr[2];
    public fixed ulong Idtr[2];
    public ulong Rip;
    public ulong Gs, Fs, Es, Ds, Cs, Ss;
    public ulong Rdi, Rsi, Rbp, Rsp, Rbx, Rdx, Rcx, Rax;
    public ulong R8, R9, R10, R11, R12, R13, R14, R15;
}
