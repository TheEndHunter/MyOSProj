namespace System
{
    public readonly ref struct ReadOnlySpan<T>
    {
        #nullable disable
        public ReadOnlySpan(T[] array) { }
        public int Length => throw null;
        public ref readonly T this[int index] => throw null;
    }
}
