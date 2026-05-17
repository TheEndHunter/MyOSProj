using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

// Mirrors FxSaveStateX64
[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct FxSaveStateX64
{
    public ushort Fcw;
    public ushort Fsw;
    public ushort Ftw;
    public ushort Opcode;
    public ulong Rip;
    public ulong DataOffset;
    public fixed byte Reserved1[8];

    public fixed byte St0Mm0[10];
    public fixed byte Reserved2[6];
    public fixed byte St1Mm1[10];
    public fixed byte Reserved3[6];
    public fixed byte St2Mm2[10];
    public fixed byte Reserved4[6];
    public fixed byte St3Mm3[10];
    public fixed byte Reserved5[6];
    public fixed byte St4Mm4[10];
    public fixed byte Reserved6[6];
    public fixed byte St5Mm5[10];
    public fixed byte Reserved7[6];
    public fixed byte St6Mm6[10];
    public fixed byte Reserved8[6];
    public fixed byte St7Mm7[10];
    public fixed byte Reserved9[6];

    public fixed byte Xmm0[16];
    public fixed byte Xmm1[16];
    public fixed byte Xmm2[16];
    public fixed byte Xmm3[16];
    public fixed byte Xmm4[16];
    public fixed byte Xmm5[16];
    public fixed byte Xmm6[16];
    public fixed byte Xmm7[16];

    public fixed byte Reserved11[14 * 16];
}
