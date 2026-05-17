namespace System.Runtime.InteropServices
{
    public static class Marshal
    {
        public static IntPtr AllocHGlobal(int cb) => throw null;
        public static void FreeHGlobal(IntPtr hglobal) => throw null;
        public static int SizeOf<T>() => throw null;
    }
}
