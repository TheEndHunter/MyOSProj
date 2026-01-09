namespace QemuRunner.JsonConverters
{
    internal static class TypeDiscriminatorRegistry
    {
        private static readonly Dictionary<Type, Dictionary<string, Type>> _map = new();

        public static void Register(Type baseType, string discriminator, Type concreteType)
        {
            if (!_map.TryGetValue(baseType, out var inner))
            {
                inner = new Dictionary<string, Type>(StringComparer.OrdinalIgnoreCase);
                _map[baseType] = inner;
            }
            inner[discriminator] = concreteType;
        }

        public static bool TryGet(Type baseType, string discriminator, out Type? concrete)
        {
            concrete = null;
            if (!_map.TryGetValue(baseType, out var inner)) return false;
            return inner.TryGetValue(discriminator, out concrete);
        }

        public static void AutoRegisterFromAssembly(System.Reflection.Assembly asm)
        {
            foreach (var t in asm.GetTypes())
            {
                if (t.IsAbstract) continue;
                var attrs = t.GetCustomAttributes(typeof(TypeDiscriminatorAttribute), inherit: false);
                foreach (TypeDiscriminatorAttribute? a in attrs)
                {
                    // register multiple discriminator forms for convenience
                    // 1) explicit attribute value
                    // 2) short type name
                    // 3) full type name (namespace + nested name format)
                    // 4) assembly-qualified name (FullName, AssemblyName)
                    var candidates = new List<string>();
                    if (!string.IsNullOrWhiteSpace(a.Discriminator)) candidates.Add(a.Discriminator);
                    candidates.Add(t.Name);
                    if (!string.IsNullOrWhiteSpace(t.FullName)) candidates.Add(t.FullName);
                    try
                    {
                        var asmName = asm.GetName().Name;
                        if (!string.IsNullOrWhiteSpace(t.FullName) && !string.IsNullOrWhiteSpace(asmName))
                        {
                            candidates.Add(t.FullName + ", " + asmName);
                        }
                    }
                    catch { }

                    foreach (var key in candidates.Distinct(StringComparer.OrdinalIgnoreCase))
                    {
                        if (typeof(QEMUConfig.NetdevConfigBase).IsAssignableFrom(t))
                        {
                            Register(typeof(QEMUConfig.NetdevConfigBase), key, t);
                        }
                        if (typeof(QEMUConfig.ChardevConfigBase).IsAssignableFrom(t))
                        {
                            Register(typeof(QEMUConfig.ChardevConfigBase), key, t);
                        }
                    }
                }
            }
        }
    }
}
