namespace EFI.Protocols.Debug;

public enum InstructionSetArchitecture : byte
{
    IsaIa32 = 0x4C,       // IMAGE_FILE_MACHINE_I386 low byte
    IsaX64 = 0x64,        // IMAGE_FILE_MACHINE_X64 low byte
    IsaIpf = 0x00,        // low byte of 0x0200
    IsaEbc = 0xBC,        // low byte of 0x0EBC
    IsaArm = 0xC2,        // low byte of 0x01C2
    IsaAArch64 = 0x64,    // low byte of 0xAA64
    IsaRISCV32 = 0x32,    // low byte of 0x5032
    IsaRISCV64 = 0x64,    // low byte of 0x5064
    IsaRISCV128 = 0x28,   // low byte of 0x5128
    IsaLoongArch32 = 0x32,// low byte of 0x6232
    IsaLoongArch64 = 0x64 // low byte of 0x6264
}
