namespace System.Runtime.InteropServices
{
    [AttributeUsage(AttributeTargets.Method)]
    public sealed class NativeCallableAttribute : Attribute
    {
        public string EntryPoint { get; init; }
        public CallingConvention CallingConvention { get; init; }
        public NativeCallableAttribute() { }
    }
}
