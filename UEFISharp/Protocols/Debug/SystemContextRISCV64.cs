using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct SystemContextRISCV64
{
    public ulong Zero, Ra, Sp, Gp, Tp, T0, T1, T2;
    public ulong S0FP, S1, A0, A1, A2, A3, A4, A5, A6, A7;
    public ulong S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;
    public ulong T3, T4, T5, T6;
    // Floating registers (each UINT128 in native; here represented as two ulongs)
}
