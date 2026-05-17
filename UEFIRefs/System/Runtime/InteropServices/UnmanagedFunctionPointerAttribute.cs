namespace System.Runtime.InteropServices
{
    [AttributeUsage(AttributeTargets.Delegate)]
    public sealed class UnmanagedFunctionPointerAttribute : Attribute
    {
        public CallingConvention CallingConvention { get; }
        public UnmanagedFunctionPointerAttribute(CallingConvention callingConvention) => CallingConvention = callingConvention;
    }
}
