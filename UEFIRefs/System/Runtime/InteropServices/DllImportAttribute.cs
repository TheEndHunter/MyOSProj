namespace System.Runtime.InteropServices
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Class | AttributeTargets.Struct)]
    public sealed class DllImportAttribute : Attribute
    {
        public string Value { get; }
        public CallingConvention CallingConvention { get; set; } = CallingConvention.Winapi;
        public CharSet CharSet { get; set; } = CharSet.None;
        public bool SetLastError { get; set; }
        public DllImportAttribute(string dllName) => Value = dllName;
    }
}
