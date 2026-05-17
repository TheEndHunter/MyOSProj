using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Explicit)]
public unsafe struct SystemContext
{
    [FieldOffset(0)] public void* Raw;

    [FieldOffset(0)] public SystemContextEBC* Ebc;
    [FieldOffset(0)] public SystemContextIA32* Ia32;
    [FieldOffset(0)] public SystemContextX64* X64;
    [FieldOffset(0)] public SystemContextIPF* Ipf;
    [FieldOffset(0)] public SystemContextARM* Arm;
    [FieldOffset(0)] public SystemContextAARCH64* AArch64;
    [FieldOffset(0)] public SystemContextRISCV32* RiscV32;
    [FieldOffset(0)] public SystemContextRISCV64* RiscV64;
    [FieldOffset(0)] public SystemContextRISCV128* Riscv128;
    [FieldOffset(0)] public SystemContextLOONGARCH64* LongArch64;
}
