namespace System
{
    // Minimal ArgumentNullException facade for reference assembly
    public class ArgumentNullException : Exception
    {
        public string ParamName { get; }

        public ArgumentNullException() : base()
        {
        }

        public ArgumentNullException(string paramName) : base()
        {
            ParamName = paramName;
        }

        public ArgumentNullException(string paramName, string message) : base()
        {
            ParamName = paramName;
        }
    }
}
