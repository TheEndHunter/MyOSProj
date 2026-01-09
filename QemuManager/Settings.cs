using Microsoft.Extensions.Configuration;

namespace QemuRunner
{

    public record struct Settings
    {
        public List<string> Configurations;
        public List<string> Architectures;
        public List<QEMUConfig> QemuConfigs;
        public GitConfig? OVMFConfiguration;

        public Settings(IConfigurationRoot root) : this()
        {
            OVMFConfiguration = null;
            var c = root.GetRequiredSection("Configurations");

            Configurations = c.AsEnumerable()
                .Where(x => !string.IsNullOrWhiteSpace(x.Value))
                .Select(x => x.Value!.ToLowerInvariant())
                .ToList();


            var a = root.GetRequiredSection("Architectures");

            Architectures = a.AsEnumerable()
                .Where(x => !string.IsNullOrWhiteSpace(x.Value))
                .Select(x => x.Value!.ToLowerInvariant())
                .ToList();

            var qc = root.GetRequiredSection("QEMUConfig");

            // Use System.Text.Json options globally: case-insensitive property names and string enum converter (allow common casing)
            var jsonOptions = new System.Text.Json.JsonSerializerOptions
            {
                PropertyNameCaseInsensitive = true,
            };
            // Add a tolerant enum converter that accepts hyphenated and case-insensitive values
            jsonOptions.Converters.Add(new QemuRunner.JsonConverters.TolerantJsonStringEnumConverter());

            // Bind using the configuration binder then re-serialize/deserialise to apply options for enums robustly
            // Use configuration binder; fall back to empty list if missing
            QemuConfigs = qc.Get<List<QEMUConfig>>() ?? new List<QEMUConfig>();

            // Prepare JsonSerializerOptions for per-item polymorphic deserialization
            var serOptions = new System.Text.Json.JsonSerializerOptions
            {
                PropertyNameCaseInsensitive = true,
            };
            serOptions.Converters.Add(new QemuRunner.JsonConverters.TolerantJsonStringEnumConverter());
            // polymorphic converters for typed lists
            serOptions.Converters.Add(new QemuRunner.JsonConverters.PolymorphicNetdevConverter());
            serOptions.Converters.Add(new QemuRunner.JsonConverters.PolymorphicChardevConverter());
            // Auto-register types annotated with TypeDiscriminatorAttribute in this assembly
            QemuRunner.JsonConverters.TypeDiscriminatorRegistry.AutoRegisterFromAssembly(typeof(QEMUConfig).Assembly);

            int count = QemuConfigs.Count;

            if (count < 1)
            {
                throw new InvalidOperationException("No QemuConfigs found in configuration file.");
            }

            // Also handle legacy AdditionalArgs in settings.json: parse and populate typed properties
            var qcSection = root.GetRequiredSection("QEMUConfig");
            var qcChildren = qcSection.GetChildren().ToList();

            for (int i = 0; i < count; i++)
            {
                var qemuConfig = QemuConfigs[i];
                qemuConfig.Architecture = qemuConfig.Architecture.ToLower();
                qemuConfig.Configuration = qemuConfig.Configuration.ToLower();

                // If settings.json still contains AdditionalArgs for this config, parse them.
                if (i < qcChildren.Count)
                {
                    var section = qcChildren[i];

                    // Parse enum-like and driver fields case-insensitively from the IConfigurationSection
                    var accelVal = section["Accel"];
                    if (!string.IsNullOrWhiteSpace(accelVal))
                    {
                        if (Enum.TryParse<QEMUConfig.AccelType>(accelVal, true, out var at)) qemuConfig.Accel = at;
                        else qemuConfig.Accel = QEMUConfig.AccelType.Unknown;
                    }

                    var dispVal = section["Display"];
                    if (!string.IsNullOrWhiteSpace(dispVal))
                    {
                        if (Enum.TryParse<QEMUConfig.DisplayType>(dispVal, true, out var dt)) qemuConfig.Display = dt;
                        else qemuConfig.Display = QEMUConfig.DisplayType.Unknown;
                    }

                    var serialVal = section["SerialTarget"];
                    if (!string.IsNullOrWhiteSpace(serialVal))
                    {
                        if (Enum.TryParse<QEMUConfig.SerialTargetType>(serialVal, true, out var st)) qemuConfig.SerialTarget = st;
                        else qemuConfig.SerialTarget = QEMUConfig.SerialTargetType.Unknown;
                    }

                    // If DeviceConfigs exist, map their Driver strings to DriverType enum case-insensitively
                    if (qemuConfig.DeviceConfigs != null)
                    {
                        foreach (var dc in qemuConfig.DeviceConfigs)
                        {
                            if (dc == null) continue;
                            if (!string.IsNullOrWhiteSpace(dc.Driver))
                            {
                                dc.DriverType = QEMUConfig.DeviceDriverFromString(dc.Driver);
                            }
                            else
                            {
                                dc.DriverType = QEMUConfig.DeviceDriver.Unknown;
                            }
                        }
                    }

                // Handle polymorphic TypedNetdevs and TypedChardevs if present in configuration section
                var typedNetdevSection = section.GetSection("TypedNetdevs");
                if (typedNetdevSection.Exists())
                {
                    qemuConfig.TypedNetdevs = new List<QEMUConfig.NetdevConfigBase>();
                    foreach (var item in typedNetdevSection.GetChildren())
                    {
                        try
                        {
                            var dict = ToDictionary(item);
                            dict.TryGetValue("$type", out var tval);
                            var typeStr = tval as string ?? string.Empty;
                            QEMUConfig.NetdevConfigBase? obj = null;
                            if (typeStr.Contains("NetdevUserConfig", StringComparison.OrdinalIgnoreCase))
                            {
                                var json = System.Text.Json.JsonSerializer.Serialize(dict, serOptions);
                                obj = System.Text.Json.JsonSerializer.Deserialize<QEMUConfig.NetdevUserConfig>(json, serOptions);
                            }
                            else if (typeStr.Contains("NetdevTapConfig", StringComparison.OrdinalIgnoreCase))
                            {
                                var json = System.Text.Json.JsonSerializer.Serialize(dict, serOptions);
                                obj = System.Text.Json.JsonSerializer.Deserialize<QEMUConfig.NetdevTapConfig>(json, serOptions);
                            }
                            else
                            {
                                // fallback: try to bind to generic NetdevConfig
                                var json = System.Text.Json.JsonSerializer.Serialize(dict, serOptions);
                                var tmp = System.Text.Json.JsonSerializer.Deserialize<QEMUConfig.NetdevConfig>(json, serOptions);
                                if (tmp != null) obj = new QEMUConfig.NetdevConfig { Id = tmp.Id, Options = tmp.Options, Type = tmp.Type } as QEMUConfig.NetdevConfigBase;
                            }

                            if (obj != null) qemuConfig.TypedNetdevs.Add(obj);
                        }
                        catch { /* ignore failures per-item */ }
                    }
                }

                var typedChardevSection = section.GetSection("TypedChardevs");
                if (typedChardevSection.Exists())
                {
                    qemuConfig.TypedChardevs = new List<QEMUConfig.ChardevConfigBase>();
                    foreach (var item in typedChardevSection.GetChildren())
                    {
                        try
                        {
                            var dict = ToDictionary(item);
                            dict.TryGetValue("$type", out var tval);
                            var typeStr = tval as string ?? string.Empty;
                            QEMUConfig.ChardevConfigBase? obj = null;
                            if (typeStr.Contains("ChardevPtyConfig", StringComparison.OrdinalIgnoreCase))
                            {
                                var json = System.Text.Json.JsonSerializer.Serialize(dict, serOptions);
                                obj = System.Text.Json.JsonSerializer.Deserialize<QEMUConfig.ChardevPtyConfig>(json, serOptions);
                            }
                            else if (typeStr.Contains("ChardevSocketConfig", StringComparison.OrdinalIgnoreCase))
                            {
                                var json = System.Text.Json.JsonSerializer.Serialize(dict, serOptions);
                                obj = System.Text.Json.JsonSerializer.Deserialize<QEMUConfig.ChardevSocketConfig>(json, serOptions);
                            }
                            else
                            {
                                var json = System.Text.Json.JsonSerializer.Serialize(dict, serOptions);
                                var tmp = System.Text.Json.JsonSerializer.Deserialize<QEMUConfig.ChardevConfig>(json, serOptions);
                                if (tmp != null) obj = new QEMUConfig.ChardevConfig { Id = tmp.Id, Backend = tmp.Backend, Options = tmp.Options } as QEMUConfig.ChardevConfigBase;
                            }

                            if (obj != null) qemuConfig.TypedChardevs.Add(obj);
                        }
                        catch { }
                    }
                }
                }

                // Validate required fields
                if (string.IsNullOrWhiteSpace(qemuConfig.Name))
                {
                    throw new InvalidOperationException($"QEMUConfig at index {i} is missing required 'Name' field.");
                }

                if (string.IsNullOrWhiteSpace(qemuConfig.Architecture))
                {
                    throw new InvalidOperationException($"QEMUConfig at index {i} is missing required 'Architecture' field.");
                }

                if (string.IsNullOrWhiteSpace(qemuConfig.Configuration))
                {
                    throw new InvalidOperationException($"QEMUConfig at index {i} is missing required 'Configuration' field.");
                }

                QemuConfigs[i] = qemuConfig;
            }

            // Validate each config via its typed validation method
            foreach (var qcItem in QemuConfigs)
            {
                qcItem.Validate();
            }

            var ovmf = root.GetRequiredSection("OVMFConfig");

            if (ovmf != null)
            {
                OVMFConfiguration = new GitConfig()
                {
                    Author = ovmf["Author"] ?? string.Empty,
                    Repo = ovmf["Repo"] ?? string.Empty,
                    OVMFBinPath = ovmf["OVMFBinPath"] ?? string.Empty,
                    Branch = ovmf["Branch"] ?? "main",
                };
            }
        }
        private static Dictionary<string, object?> ToDictionary(Microsoft.Extensions.Configuration.IConfigurationSection section)
        {
            var dict = new Dictionary<string, object?>();
            foreach (var child in section.GetChildren())
            {
                if (child.Value == null)
                {
                    // treat as nested object or array
                    var children = child.GetChildren().ToList();
                    if (children.Count == 0) dict[child.Key] = null;
                    else
                    {
                        // if child keys are numeric -> array
                        if (children.All(c => int.TryParse(c.Key, out _)))
                        {
                            var list = new List<object?>();
                            foreach (var el in children) list.Add(ToDictionary(el));
                            dict[child.Key] = list;
                        }
                        else
                        {
                            dict[child.Key] = ToDictionary(child);
                        }
                    }
                }
                else
                {
                    dict[child.Key] = child.Value;
                }
            }
            return dict;
        }
    }
}


