namespace QemuRunner.JsonConverters;

using System;
using System.Text.Json;
using System.Text.Json.Serialization;

/// <summary>
/// A tolerant enum converter that attempts to parse string values case-insensitively and
/// accepts hyphenated or underscore variants for enum names.
/// </summary>
public class TolerantJsonStringEnumConverter : JsonConverterFactory
{
    public override bool CanConvert(Type typeToConvert)
    {
        return typeToConvert.IsEnum;
    }


    public override JsonConverter? CreateConverter(Type typeToConvert, JsonSerializerOptions options)
    {
        var converterType = typeof(TolerantEnumConverterInner<>).MakeGenericType(typeToConvert);
        return (JsonConverter?)Activator.CreateInstance(converterType)!;
    }

    private class TolerantEnumConverterInner<T> : JsonConverter<T> where T : struct, Enum
    {
        public override T Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            if (reader.TokenType == JsonTokenType.String)
            {
                var s = reader.GetString() ?? string.Empty;
                var norm = s.Trim().Replace('-', '_').Replace('.', '_');
                if (Enum.TryParse<T>(norm, true, out var val)) return val;
                // try without normalization
                if (Enum.TryParse<T>(s, true, out val)) return val;
            }

            // Fallback to default handling for numbers
            if (reader.TokenType == JsonTokenType.Number && reader.TryGetInt32(out var intVal))
            {
                return (T)Enum.ToObject(typeof(T), intVal);
            }

            throw new JsonException($"Unable to convert value to enum {typeof(T)}.");
        }

        public override void Write(Utf8JsonWriter writer, T value, JsonSerializerOptions options)
        {
            writer.WriteStringValue(value.ToString());
        }
    }
}
