using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct SystemContextRISCV128
{
    // Integer registers modeled as pairs of ulongs for UINT128
    public ulong Zero_L, Zero_H, Ra_L, Ra_H, Sp_L, Sp_H, Gp_L, Gp_H, Tp_L, Tp_H, T0_L, T0_H, T1_L, T1_H, T2_L, T2_H;
    // Remaining registers omitted for brevity; follow header if needed
}
