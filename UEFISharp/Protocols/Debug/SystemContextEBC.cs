using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct SystemContextEBC
{
    public ulong R0, R1, R2, R3, R4, R5, R6, R7;
    public ulong Flags;
    public ulong ControlFlags;
    public ulong Ip;
}
