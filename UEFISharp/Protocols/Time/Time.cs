using System;
using System.Runtime.InteropServices;

namespace EFI;

[StructLayout(LayoutKind.Sequential)]
public struct Time
{
    public ushort Year;
    public byte Month;
    public byte Day;
    public byte Hour;
    public byte Minute;
    public byte Second;
    public byte Pad1;
    public uint Nanosecond;
    public short TimeZone;
    public byte Daylight;
    public byte Pad2;

    public bool Equals(Time other)
    {
        return Year == other.Year &&
               Month == other.Month &&
               Day == other.Day &&
               Hour == other.Hour &&
               Minute == other.Minute &&
               Second == other.Second &&
               Pad1 == other.Pad1 &&
               Nanosecond == other.Nanosecond &&
               TimeZone == other.TimeZone &&
               Daylight == other.Daylight &&
               Pad2 == other.Pad2;
    }

    public override bool Equals(object? obj) => obj is Time t && Equals(t);

    public override int GetHashCode()
    {
        return HashCode.Combine(Year, Month, Day, Hour, Minute, Second, Pad1, HashCode.Combine((long)Nanosecond, TimeZone, Daylight, Pad2));
    }

    public static bool operator ==(Time left, Time right) => left.Equals(right);
    public static bool operator !=(Time left, Time right) => !left.Equals(right);
}

public static class TimeConsts
{
    public const byte TimeAdjustDaylight = 0x01;
    public const byte TimeInDaylight = 0x02;
    public const short UnspecifiedTimezone = 0x07FF;
}
