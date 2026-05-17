namespace EFI.Protocols.IO.Console;

public enum ForegroundColor : byte
{
    Black = 0x00,
    Blue = 0x01,
    Green = 0x02,
    Cyan = 0x03,
    Red = 0x04,
    Magenta = 0x05,
    Brown = 0x06,
    LightGray = 0x07,
    Bright = 0x08,
    DarkGray = 0x08,
    LightBlue = 0x09,
    LightGreen = 0x0A,
    LightCyan = 0x0B,
    LightRed = 0x0C,
    LightMagenta = 0x0D,
    Yellow = 0x0E,
    White = 0x0F
}

public enum BackgroundColor : byte
{
    Black = 0x00,
    Blue = 0x10,
    Green = 0x20,
    Cyan = 0x30,
    Red = 0x40,
    Magenta = 0x50,
    Brown = 0x60,
    LightGray = 0x70
}

public static class ConsoleColorHelpers
{
    public static byte MakeAttribute(ForegroundColor fore, BackgroundColor back) => (byte)(((byte)fore) | (byte)back);

    public const byte Debug = (byte)(ForegroundColor.Cyan | (ForegroundColor)BackgroundColor.Black);
    public const byte Default = (byte)(ForegroundColor.White | (ForegroundColor)BackgroundColor.Black);
    public const byte Error = (byte)(ForegroundColor.LightRed | (ForegroundColor)BackgroundColor.Black);
    public const byte Fatal = (byte)(ForegroundColor.Red | (ForegroundColor)BackgroundColor.Black);
    public const byte Info = (byte)(ForegroundColor.LightGreen | (ForegroundColor)BackgroundColor.Black);
    public const byte Success = (byte)(ForegroundColor.Green | (ForegroundColor)BackgroundColor.Black);
    public const byte Trace = (byte)(ForegroundColor.LightCyan | (ForegroundColor)BackgroundColor.Black);
    public const byte Warning = (byte)(ForegroundColor.Yellow | (ForegroundColor)BackgroundColor.Black);
}
