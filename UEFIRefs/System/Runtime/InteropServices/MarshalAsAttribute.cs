namespace System.Runtime.InteropServices
{
    [System.AttributeUsage(System.AttributeTargets.Field | System.AttributeTargets.Parameter | System.AttributeTargets.Property)]
    public sealed class MarshalAsAttribute : System.Attribute
    {
        public MarshalAsAttribute(UnmanagedType unmanagedType) { }
        public int SizeConst { get; set; }
    }
}
