using System.Runtime.InteropServices;

namespace EFI.Protocols.Debug;

public static partial class EFIConsts
{
    public static readonly System.Guid DebugSupportProtocolGuid =
        new(0x2755590C, 0x6F3C, 0x42FA, 0x9E, 0xA4, 0xA3, 0xBA, 0x54, 0x3C, 0xDA, 0x25);
}

public unsafe delegate void ExceptionCallback(ExceptionType exceptionType, SystemContext systemContext);

public unsafe delegate Status RegisterExceptionCallbackFunc(
    DebugSupportProtocol* self,
    nuint processorIndex,
    ExceptionCallback exceptionCallback,
    ExceptionType exceptionType);

public unsafe delegate Status InvalidateInstructionCacheFunc(
    DebugSupportProtocol* self,
    nuint processorIndex,
    void* start,
    ulong length);

public unsafe delegate void PeriodicCallback(SystemContext systemContext);

public unsafe delegate Status GetMaximumProcessorIndexFunc(
    DebugSupportProtocol* self,
    nuint* maxProcessorIndex);

public unsafe delegate Status RegisterPeriodicCallbackFunc(
    DebugSupportProtocol* self,
    nuint processorIndex,
    PeriodicCallback periodicCallback);

public unsafe delegate Status RegisterExceptionCallbackFunc2(
    DebugSupportProtocol* self,
    nuint processorIndex,
    ExceptionCallback exceptionCallback,
    ExceptionType exceptionType);

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DebugSupportProtocol
{
    public InstructionSetArchitecture Isa;
    public GetMaximumProcessorIndexFunc GetMaximumProcessorIndex;
    public RegisterPeriodicCallbackFunc RegisterPeriodicCallback;
    public RegisterExceptionCallbackFunc2 RegisterExceptionCallback;
    public InvalidateInstructionCacheFunc InvalidateInstructionCache;
}
