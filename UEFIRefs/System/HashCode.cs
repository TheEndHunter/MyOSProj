namespace System
{
    // Minimal HashCode helper used by generated types for GetHashCode implementations.
    public static class HashCode
    {
        // Accept variable number of integer-compatible values and produce a stable int hash.
        public static int Combine(params long[] values)
        {
            unchecked
            {
                long hash = 1469598103934665603L; // FNV offset basis (64-bit)
                for (int i = 0; i < values.Length; i++)
                {
                    long v = values[i];
                    long x = v ^ (v >> 32);
                    hash = (hash ^ x) * 1099511628211L; // FNV prime
                }
                return (int)(hash & 0x7FFFFFFF);
            }
        }
    }
}
