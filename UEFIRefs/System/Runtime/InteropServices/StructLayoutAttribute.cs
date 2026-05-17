namespace System.Runtime.InteropServices
{
    [AttributeUsage(AttributeTargets.Struct | AttributeTargets.Class | AttributeTargets.Enum)]
    public sealed class StructLayoutAttribute : Attribute
    {
        private LayoutKind _value;
        public LayoutKind Value => _value;
        public int Pack { get; set; }

        // Accept either positional parameter or named argument 'layoutKind'
        public StructLayoutAttribute(LayoutKind layoutKind) => _value = layoutKind;

        // Named argument used in some sources: layoutKind
        public LayoutKind layoutKind { get => _value; set => _value = value; }
    }
}
