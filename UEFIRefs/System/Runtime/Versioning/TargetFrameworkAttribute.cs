namespace System.Runtime.Versioning
{
    [System.AttributeUsage(System.AttributeTargets.Assembly | System.AttributeTargets.Module, AllowMultiple = false)]
    public sealed class TargetFrameworkAttribute : System.Attribute
    {
        public TargetFrameworkAttribute(string frameworkName) { }
        public string FrameworkDisplayName { get; set; }
    }
}
