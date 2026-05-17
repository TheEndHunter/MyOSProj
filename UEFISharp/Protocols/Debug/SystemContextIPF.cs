using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SystemContextIPF
{
    public ulong Reserved;
    public fixed ulong R[31];
    // Floating, branch, application, control, debug, and virtual registers can be added if needed
}
