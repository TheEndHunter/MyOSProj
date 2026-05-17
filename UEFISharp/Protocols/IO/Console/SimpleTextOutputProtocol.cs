using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Console;

public static partial class EFIConsts
{
    public static readonly Guid SimpleTextOutputProtocolGuid =
        new(0x387477C2, 0x69C7, 0x11D2, 0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B);
}

[StructLayout(LayoutKind.Sequential)]
public struct SimpleTextOutputMode
{
    public int MaxMode;
    public int Mode;
    public int Attribute;
    public int CursorColumn;
    public int CursorRow;
    public bool CursorVisible;
}

public unsafe delegate Status TextResetFunc(SimpleTextOutputProtocol* self, bool extendedVerification);
public unsafe delegate Status TextStringFunc(SimpleTextOutputProtocol* self, char* str);
public unsafe delegate Status TextTestStringFunc(SimpleTextOutputProtocol* self, char* str);
public unsafe delegate Status TextQueryModeFunc(SimpleTextOutputProtocol* self, nuint modeNumber, nuint* columns, nuint* rows);
public unsafe delegate Status TextSetModeFunc(SimpleTextOutputProtocol* self, nuint modeNumber);
public unsafe delegate Status TextSetAttributeFunc(SimpleTextOutputProtocol* self, nuint attribute);
public unsafe delegate Status TextClearScreenFunc(SimpleTextOutputProtocol* self);
public unsafe delegate Status TextSetCursorPositionFunc(SimpleTextOutputProtocol* self, nuint column, nuint row);
public unsafe delegate Status TextEnableCursorFunc(SimpleTextOutputProtocol* self, bool visible);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SimpleTextOutputProtocol
{
    public TextResetFunc Reset;
    public TextStringFunc OutputString;
    public TextTestStringFunc TestString;
    public TextQueryModeFunc QueryMode;
    public TextSetModeFunc SetMode;
    public TextSetAttributeFunc SetAttribute;
    public TextClearScreenFunc ClearScreen;
    public TextSetCursorPositionFunc SetCursorPosition;
    public TextEnableCursorFunc EnableCursor;
    public SimpleTextOutputMode* Mode;
}
