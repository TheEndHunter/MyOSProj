using System;

namespace EFI.Protocols.IO.Serial;

[Flags]
public enum SerialControlBits : ushort
{
    ClearToSend = 0x0010,
    DataSetReady = 0x0020,
    RingIndicate = 0x0040,
    CarrierDetect = 0x0080,
    RequestToSend = 0x0002,
    DataTerminalReady = 0x0001,
    InputBufferEmpty = 0x0100,
    OutputBufferEmpty = 0x0200,
    HardwareLoopbackEnable = 0x1000,
    SoftwareLoopbackEnable = 0x2000,
    HardwareFlowControlEnable = 0x4000,
}
