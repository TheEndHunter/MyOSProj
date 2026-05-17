using System.Runtime.InteropServices;

namespace EFI;

[StructLayout(LayoutKind.Sequential, Pack = 8)]
public struct Guid
{
    public Guid(uint v1, ushort v2, ushort v3, byte v4, byte v5, byte v6, byte v7, byte v8, byte v9, byte v10, byte v11)
    {
        Data1 = v1;
        Data2 = v2;
        Data3 = v3;
        unsafe
        {
            Data4[0] = v4;
            Data4[1] = v5;
            Data4[2] = v6;
            Data4[3] = v7;
            Data4[4] = v8;
            Data4[5] = v9;
            Data4[6] = v10;
            Data4[7] = v11;
        }
    }
    public uint Data1;
    public ushort Data2;
    public ushort Data3;
    public unsafe fixed byte Data4[8];
}