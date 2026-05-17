using System;

namespace System.Runtime.InteropServices
{
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Parameter | AttributeTargets.ReturnValue | AttributeTargets.Method)]
    public sealed class NativeTypeNameAttribute : Attribute
    {
        public string Name { get; }
        public NativeTypeNameAttribute(string name) => Name = name;
    }
}
