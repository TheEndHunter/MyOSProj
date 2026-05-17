#nullable enable

namespace System
{
    // Minimal Exception facade for reference assembly
    public class Exception : Object
    {
        public Exception() { }
        public Exception(string message) { }
        public virtual string Message => throw null;
    }
}
