using System.Runtime.InteropServices;

namespace EFI;

[StructLayout(LayoutKind.Sequential)]
public struct TimeCapabilities
{
    public uint Resolution;
    public uint Accuracy;
    public bool SetsToZero;
}
