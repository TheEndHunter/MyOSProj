using System.Runtime.InteropServices;

namespace EFI.Protocols.Configuration;

public static partial class EFIConsts
{
    public static readonly Guid ConformanceProfilesTableGuid =
        new(0x36122546, 0xF7E7, 0x4C8F, 0xBD, 0x9B, 0xEB, 0x85, 0x25, 0xB5, 0x0C, 0x0B);

    public static readonly Guid ConformanceProfilesUefiSpecGuid =
        new(0x523C91AF, 0xA195, 0x4382, 0x81, 0x8D, 0x29, 0x5F, 0xE4, 0x00, 0x64, 0x65);

    public const ushort ConformanceProfilesTableVersion = 0x0001;
}

[StructLayout(LayoutKind.Sequential)]
public struct ConformanceProfilesTable
{
    public ushort Version;
    public ushort NumberOfProfiles;
    // Followed by Guid[] ConformanceProfiles
}
