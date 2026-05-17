namespace System.Runtime.InteropServices
{
    [System.AttributeUsage(System.AttributeTargets.Field)]
    public sealed class FieldOffsetAttribute : System.Attribute
    {
        public FieldOffsetAttribute(int offset) { }
    }
}
