using System;

namespace QemuRunner.JsonConverters
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property, AllowMultiple = true, Inherited = false)]
    public sealed class TypeDiscriminatorAttribute : Attribute
    {
        public string Discriminator { get; }

        public TypeDiscriminatorAttribute(string discriminator)
        {
            Discriminator = discriminator;
        }
    }
}
