using System.Runtime.InteropServices;

namespace System
{
    [StructLayout(LayoutKind.Sequential, Pack = 8)]
    public unsafe struct Guid
    {
        public Guid(uint v1, ushort v2, ushort v3, byte v4, byte v5, byte v6, byte v7, byte v8, byte v9, byte v10, byte v11)
        {
            Data1 = v1;
            Data2 = v2;
            Data3 = v3;
            fixed (byte* p = Data4)
            {
                p[0] = v4;
                p[1] = v5;
                p[2] = v6;
                p[3] = v7;
                p[4] = v8;
                p[5] = v9;
                p[6] = v10;
                p[7] = v11;
            }
        }

        public uint Data1;
        public ushort Data2;
        public ushort Data3;
        public fixed byte Data4[8];
    }
}
