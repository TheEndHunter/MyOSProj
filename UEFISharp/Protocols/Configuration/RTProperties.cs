using System;
using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

public static partial class EFIConsts
{
    public static readonly Guid RtPropertiesTableGuid =
        new(0xEB66918A, 0x7EEF, 0x402A, 0x84, 0x2E, 0x93, 0x1D, 0x21, 0xC3, 0x8A, 0xE9);
}

[StructLayout(LayoutKind.Sequential)]
public struct RtPropertiesTable
{
    public ushort Version;
    public ushort Length;
    public uint RuntimeServicesSupported;
}

[Flags]
public enum RtSupportedMask : uint
{
    GetTime = 0x0001,
    SetTime = 0x0002,
    GetWakeupTime = 0x0004,
    SetWakeupTime = 0x0008,
    GetVariable = 0x0010,
    GetNextVariableName = 0x0020,
    SetVariable = 0x0040,
    SetVirtualAddressMap = 0x0080,
    ConvertPointer = 0x0100,
    GetNextHighMonotonicCount = 0x0200,
    ResetSystem = 0x0400,
    UpdateCapsule = 0x0800,
    QueryCapsuleCapabilities = 0x1000,
    QueryVariableInfo = 0x2000,
}
