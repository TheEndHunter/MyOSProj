#pragma once
#include <EFI_STATUS.h>
#include <EFI_GUID.h>
#include <Protocols\Debug\EFI_SYSTEM_CONTEXT.h>
#include <Protocols\Debug\EFI_INSTRUCTION_SET_ARCHITECTURE.h>
#include <Protocols\Debug\EFI_EXCEPTION_TYPE.h>

namespace EFI
{
	struct EFI_DEBUG_SUPPORT_PROTOCOL;

	constinit  const ALIGN(8) EFI::EFI_GUID EFI_DEBUG_SUPPORT_PROTOCOL_GUID = { 0x2755590C, 0x6F3C, 0x42FA,{ 0x9E, 0xA4, 0xA3, 0xBA, 0x54, 0x3C, 0xDA, 0x25} };

	typedef VOID(*EFI_EXCEPTION_CALLBACK) (IN EFI_EXCEPTION_TYPE ExceptionType, IN OUT EFI_SYSTEM_CONTEXT SystemContext);
	typedef EFI_STATUS (EFIAPI* REGISTER_EXCEPTION_CALLBACK) (IN EFI_DEBUG_SUPPORT_PROTOCOL* This, IN UINTN ProcessorIndex, IN EFI_EXCEPTION_CALLBACK ExceptionCallback, IN EFI_EXCEPTION_TYPE ExceptionType);
	typedef EFI_STATUS(EFIAPI* EFI_INVALIDATE_INSTRUCTION_CACHE) (IN EFI_DEBUG_SUPPORT_PROTOCOL* This,IN UINTN ProcessorIndex,IN VOID* Start,IN UINT64 Length);

	typedef VOID(*EFI_PERIODIC_CALLBACK) (IN OUT EFI_SYSTEM_CONTEXT SystemContext);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_GET_MAXIMUM_PROCESSOR_INDEX) (IN EFI_DEBUG_SUPPORT_PROTOCOL* This,OUT UINTN* MaxProcessorIndex);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_REGISTER_PERIODIC_CALLBACK) (IN EFI_DEBUG_SUPPORT_PROTOCOL* This,IN UINTN ProcessorIndex,IN EFI_PERIODIC_CALLBACK PeriodicCallback );
	typedef EFI::EFI_STATUS(EFIAPI* EFI_REGISTER_EXCEPTION_CALLBACK) (IN EFI_DEBUG_SUPPORT_PROTOCOL* This,IN UINTN ProcessorIndex,IN EFI_EXCEPTION_CALLBACK ExceptionCallback,IN EFI_EXCEPTION_TYPE ExceptionType);

	struct EFI_DEBUG_SUPPORT_PROTOCOL
	{
	public:
		EFI_INSTRUCTION_SET_ARCHITECTURE Isa;
		EFI_GET_MAXIMUM_PROCESSOR_INDEX GetMaximumProcessorIndex;
		EFI_REGISTER_PERIODIC_CALLBACK RegisterPeriodicCallback;
		EFI_REGISTER_EXCEPTION_CALLBACK RegisterExceptionCallback;
		EFI_INVALIDATE_INSTRUCTION_CACHE InvalidateInstructionCache;
	};
}
