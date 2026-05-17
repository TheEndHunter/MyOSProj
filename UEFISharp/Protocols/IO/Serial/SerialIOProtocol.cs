using System.Runtime.InteropServices;


namespace EFI.Protocols.IO.Serial;

public static partial class EFIConsts
{
    public static readonly Guid SerialIOProtocolGuid =
        new(0xBB25CF6F, 0xF1D4, 0x11D2, 0x9A, 0x0C, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0xFD);

    public static readonly Guid SerialTerminalDeviceTypeGuid =
        new(0x6AD9A60F, 0x5815, 0x4C7C, 0x8A, 0x10, 0x50, 0x53, 0xD2, 0xBF, 0x7A, 0x1B);

    public const uint SerialIOProtocolRevision = 0x00010000;
    public const uint SerialIOProtocolRevision1p1 = 0x00010001;
}

public unsafe delegate Status SerialResetFunc(SerialIOProtocol* self);

public unsafe delegate Status SerialSetAttributesFunc(
    SerialIOProtocol* self,
    ulong baudRate,
    uint receiveFifoDepth,
    uint timeout,
    ParityType parity,
    byte dataBits,
    StopBitsType stopBits);

public unsafe delegate Status SerialSetControlBitsFunc(SerialIOProtocol* self, SerialControlBits control);
public unsafe delegate Status SerialGetControlBitsFunc(SerialIOProtocol* self, SerialControlBits* control);

public unsafe delegate Status SerialWriteFunc(SerialIOProtocol* self, nuint* bufferSize, void* buffer);
public unsafe delegate Status SerialReadFunc(SerialIOProtocol* self, nuint* bufferSize, void* buffer);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct SerialIOProtocol
{
    public uint Revision;
    public SerialResetFunc Reset;
    public SerialSetAttributesFunc SetAttributes;
    public SerialSetControlBitsFunc SetControl;
    public SerialGetControlBitsFunc GetControl;
    public SerialWriteFunc Write;
    public SerialReadFunc Read;
    public SerialIOMode* Mode;
    public Guid* DeviceTypeGuid; // Revision 1.1
}
