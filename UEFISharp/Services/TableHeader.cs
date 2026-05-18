namespace EFI.Services;

public static partial class EFIConsts
{
    public const ulong EFI_SYSTEM_TABLE_SIGNATURE = 0x5453595320494249UL;
    public const uint EFI_2_100_SYSTEM_TABLE_REVISION = ((2u << 16) | 100u);
    public const uint EFI_2_110_SYSTEM_TABLE_REVISION = ((2u << 16) | 110u);
    public const uint EFI_2_90_SYSTEM_TABLE_REVISION = ((2u << 16) | 90u);
    public const uint EFI_2_80_SYSTEM_TABLE_REVISION = ((2u << 16) | 80u);
    public const uint EFI_2_70_SYSTEM_TABLE_REVISION = ((2u << 16) | 70u);
    public const uint EFI_2_60_SYSTEM_TABLE_REVISION = ((2u << 16) | 60u);
    public const uint EFI_2_50_SYSTEM_TABLE_REVISION = ((2u << 16) | 50u);
    public const uint EFI_2_40_SYSTEM_TABLE_REVISION = ((2u << 16) | 40u);
    public const uint EFI_2_31_SYSTEM_TABLE_REVISION = ((2u << 16) | 31u);
    public const uint EFI_2_30_SYSTEM_TABLE_REVISION = ((2u << 16) | 30u);
    public const uint EFI_2_20_SYSTEM_TABLE_REVISION = ((2u << 16) | 20u);
    public const uint EFI_2_10_SYSTEM_TABLE_REVISION = ((2u << 16) | 10u);
    public const uint EFI_2_00_SYSTEM_TABLE_REVISION = ((2u << 16) | 0u);
    public const uint EFI_1_10_SYSTEM_TABLE_REVISION = ((1u << 16) | 10u);
    public const uint EFI_1_02_SYSTEM_TABLE_REVISION = ((1u << 16) | 2u);
    public const uint EFI_SYSTEM_TABLE_REVISION = EFI_2_110_SYSTEM_TABLE_REVISION;
    public const uint SpecificationVersion = EFI_SYSTEM_TABLE_REVISION;

}

[System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential, Pack = 1)]
public struct TableHeader
{
    public ulong Signature;
    public uint Revision;
    public uint HeaderSize;
    public uint CRC32;
    public uint Reserved;
}
