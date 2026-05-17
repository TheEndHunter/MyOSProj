using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

[StructLayout(LayoutKind.Sequential)]
public struct OpenProtocolInformationEntry
{
    public Handle AgentHandle;
    public Handle ControllerHandle;
    public uint Attributes;
    public uint OpenCount;
}
