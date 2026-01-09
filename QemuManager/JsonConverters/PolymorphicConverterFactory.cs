using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace QemuRunner.JsonConverters
{
    public class PolymorphicConverterFactory<TBase> : JsonConverter<TBase> where TBase : class
    {
        public override TBase? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            using var doc = JsonDocument.ParseValue(ref reader);
            if (!doc.RootElement.TryGetProperty("$type", out var tprop))
            {
                // No discriminator; try direct deserialize
                var json = doc.RootElement.GetRawText();
                return JsonSerializer.Deserialize<TBase>(json, options);
            }

            var disc = tprop.GetString() ?? string.Empty;
            if (TypeDiscriminatorRegistry.TryGet(typeof(TBase), disc, out var concreteType))
            {
                var json = doc.RootElement.GetRawText();
                var obj = JsonSerializer.Deserialize(json, concreteType, options);
                return obj as TBase;
            }

            // fallback
            var fallback = doc.RootElement.GetRawText();
            return JsonSerializer.Deserialize<TBase>(fallback, options);
        }

        public override void Write(Utf8JsonWriter writer, TBase value, JsonSerializerOptions options)
        {
            JsonSerializer.Serialize(writer, (object?)value, value.GetType(), options);
        }
    }
}
