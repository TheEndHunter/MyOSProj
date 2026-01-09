using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace QemuRunner.JsonConverters
{
    public class PolymorphicNetdevConverter : JsonConverter<QEMUConfig.NetdevConfigBase>
    {
        public override QEMUConfig.NetdevConfigBase? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            using var doc = JsonDocument.ParseValue(ref reader);
            if (!doc.RootElement.TryGetProperty("$type", out var typeProp))
            {
                // fallback to generic
                var tmp = doc.RootElement.ToString();
                return JsonSerializer.Deserialize<QEMUConfig.NetdevConfig>(tmp, options) as QEMUConfig.NetdevConfigBase;
            }

            var t = typeProp.GetString() ?? string.Empty;
            var json = doc.RootElement.ToString();
            if (t.Contains("NetdevUserConfig", StringComparison.OrdinalIgnoreCase))
                return JsonSerializer.Deserialize<QEMUConfig.NetdevUserConfig>(json, options);
            if (t.Contains("NetdevTapConfig", StringComparison.OrdinalIgnoreCase))
                return JsonSerializer.Deserialize<QEMUConfig.NetdevTapConfig>(json, options);

            return JsonSerializer.Deserialize<QEMUConfig.NetdevConfig>(json, options) as QEMUConfig.NetdevConfigBase;
        }

        public override void Write(Utf8JsonWriter writer, QEMUConfig.NetdevConfigBase value, JsonSerializerOptions options)
        {
            JsonSerializer.Serialize(writer, (object)value, options);
        }
    }
}