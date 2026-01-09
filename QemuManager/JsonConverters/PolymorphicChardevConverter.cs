using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace QemuRunner.JsonConverters
{
    public class PolymorphicChardevConverter : JsonConverter<QEMUConfig.ChardevConfigBase>
    {
        public override QEMUConfig.ChardevConfigBase? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            using var doc = JsonDocument.ParseValue(ref reader);
            if (!doc.RootElement.TryGetProperty("$type", out var typeProp))
            {
                var tmp = doc.RootElement.ToString();
                return JsonSerializer.Deserialize<QEMUConfig.ChardevConfig>(tmp, options) as QEMUConfig.ChardevConfigBase;
            }

            var t = typeProp.GetString() ?? string.Empty;
            var json = doc.RootElement.ToString();
            if (t.Contains("ChardevPtyConfig", StringComparison.OrdinalIgnoreCase))
                return JsonSerializer.Deserialize<QEMUConfig.ChardevPtyConfig>(json, options);
            if (t.Contains("ChardevSocketConfig", StringComparison.OrdinalIgnoreCase))
                return JsonSerializer.Deserialize<QEMUConfig.ChardevSocketConfig>(json, options);

            return JsonSerializer.Deserialize<QEMUConfig.ChardevConfig>(json, options) as QEMUConfig.ChardevConfigBase;
        }

        public override void Write(Utf8JsonWriter writer, QEMUConfig.ChardevConfigBase value, JsonSerializerOptions options)
        {
            JsonSerializer.Serialize(writer, (object)value, options);
        }
    }
}