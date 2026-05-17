#pragma once
#include <Status.h>
#include <Guid.h>
#include <Protocols\Debug\EFI_SYSTEM_CONTEXT.h>
#include <Protocols\Debug\EFI_INSTRUCTION_SET_ARCHITECTURE.h>
#include <Protocols\Debug\EFI_EXCEPTION_TYPE.h>

namespace Efi
{
    struct DebugSupportProtocol;

    constinit  const ALIGN(8) Efi::Guid DebugSupportProtocolGuid = { 0x2755590C, 0x6F3C, 0x42FA,{ 0x9E, 0xA4, 0xA3, 0xBA, 0x54, 0x3C, 0xDA, 0x25} };

    typedef VOID(*ExceptionCallback) (IN ExceptionType ExceptionType, IN OUT SystemContext SystemContext);
    typedef Status (EFIAPI* RegisterExceptionCallbackFunc) (IN DebugSupportProtocol* This, IN UINTN ProcessorIndex, IN ExceptionCallback ExceptionCallback, IN ExceptionType ExceptionType);
    typedef Status(EFIAPI* InvalidateInstructionCacheFunc) (IN DebugSupportProtocol* This,IN UINTN ProcessorIndex,IN VOID* Start,IN UINT64 Length);

    typedef VOID(*PeriodicCallback) (IN OUT SystemContext SystemContext);

    typedef Status(EFIAPI* GetMaximumProcessorIndexFunc) (IN DebugSupportProtocol* This,OUT UINTN* MaxProcessorIndex);
    typedef Status(EFIAPI* RegisterPeriodicCallbackFunc) (IN DebugSupportProtocol* This,IN UINTN ProcessorIndex,IN PeriodicCallback PeriodicCallback );
    typedef Status(EFIAPI* RegisterExceptionCallbackFunc2) (IN DebugSupportProtocol* This,IN UINTN ProcessorIndex,IN ExceptionCallback ExceptionCallback,IN ExceptionType ExceptionType);

    struct DebugSupportProtocol
	{
	public:
        InstructionSetArchitecture Isa;
        GetMaximumProcessorIndexFunc GetMaximumProcessorIndex;
        RegisterPeriodicCallbackFunc RegisterPeriodicCallback;
        RegisterExceptionCallbackFunc2 RegisterExceptionCallback;
        InvalidateInstructionCacheFunc InvalidateInstructionCache;
	};
}
