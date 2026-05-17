namespace System.Runtime.CompilerServices
{
    public static unsafe class Unsafe
    {
        #nullable disable
        public static ref T As<T>(object o) => throw null;
        public static ref T AsRef<T>(void* source) => throw null;
        public static void CopyBlock(void* dest, void* src, uint byteCount) { }
    }
}
