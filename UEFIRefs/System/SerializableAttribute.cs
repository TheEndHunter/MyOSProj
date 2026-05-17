namespace System
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Enum | AttributeTargets.Delegate)]
    public sealed class SerializableAttribute : Attribute { }
}
