#pragma once

#include <UEFIDef.h>
#include <EFI_RESET_TYPE.h>
#include <Protocols/Configuration/EFI_CAPSULE_HEADER.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/Time/EFI_TIME_CAPABILITIES.h>
#include <EFI_MEMORY_DESCRIPTOR.h>

namespace EFI
{

    const UINT64 EFI_RUNTIME_SERVICES_SIGNATURE = 0x56524553544e5552;
    const UINT64 EFI_RUNTIME_SERVICES_REVISION = EFI_SPECIFICATION_VERSION;

    typedef EFI_STATUS (EFIAPI* EFI_GET_TIME)(OUT EFI_TIME* Time,OUT EFI_TIME_CAPABILITIES* Capabilities OPTIONAL);
    typedef EFI_STATUS (EFIAPI* EFI_SET_TIME)(IN EFI_TIME* Time);
    typedef EFI_STATUS (EFIAPI* EFI_GET_WAKEUP_TIME)(OUT BOOLEAN* Enabled,OUT BOOLEAN* Pending,OUT EFI_TIME* Time);
    typedef EFI_STATUS (EFIAPI* EFI_SET_WAKEUP_TIME)(IN BOOLEAN Enable,IN EFI_TIME* Time OPTIONAL);

	typedef EFI_STATUS (EFIAPI* EFI_SET_VIRTUAL_ADDRESS_MAP)(IN UINTN MemoryMapSize,IN UINTN DescriptorSize,IN UINT32 DescriptorVersion,IN EFI_MEMORY_DESCRIPTOR* VirtualMap);
    typedef EFI_STATUS (EFIAPI* EFI_CONVERT_POINTER)(IN UINTN DebugDisposition,IN VOID** Address);

    typedef EFI_STATUS (EFIAPI* EFI_GET_VARIABLE)(IN CHAR16* VariableName,IN const EFI_GUID* VendorGuid,OUT UINT32* Attributes OPTIONAL,IN OUT UINTN* DataSize,OUT VOID* Data OPTIONAL);

    typedef EFI_STATUS (EFIAPI* EFI_GET_NEXT_VARIABLE_NAME)(IN OUT UINTN* VariableNameSize,IN OUT CHAR16* VariableName,IN OUT EFI_GUID* VendorGuid);
	typedef EFI_STATUS (EFIAPI* EFI_SET_VARIABLE)(IN CHAR16* VariableName,IN const EFI_GUID* VendorGuid,IN UINT32 Attributes,IN UINTN DataSize,IN VOID* Data);

	typedef EFI_STATUS (EFIAPI* EFI_GET_NEXT_HIGH_MONO_COUNT)(OUT UINT32* HighCount);
	typedef VOID (EFIAPI* EFI_RESET_SYSTEM)(IN EFI_RESET_TYPE ResetType,IN EFI_STATUS ResetStatus,IN UINTN DataSize,IN VOID* ResetData OPTIONAL);

	typedef EFI_STATUS (EFIAPI* EFI_UPDATE_CAPSULE)(IN EFI_CAPSULE_HEADER** CapsuleHeaderArray,IN UINTN CapsuleCount,IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL);
	typedef EFI_STATUS (EFIAPI* EFI_QUERY_CAPSULE_CAPABILITIES)(IN EFI_CAPSULE_HEADER** CapsuleHeaderArray,IN UINTN CapsuleCount,OUT UINT64* MaximumCapsuleSize,OUT EFI_RESET_TYPE* ResetType);

	typedef EFI_STATUS (EFIAPI* EFI_QUERY_VARIABLE_INFO)(IN UINT32 Attributes,OUT UINT64* MaximumVariableStorageSize,OUT UINT64* RemainingVariableStorageSize,OUT UINT64* MaximumVariableSize);

    //******************************************************
    // EFI_OPTIONAL_PTR
    //******************************************************
    const UINTN EFI_OPTIONAL_PTR = 1;

	struct EFI_RUNTIME_SERVICES
	{
	public:        
        /// <summary>
        /// The table header for the EFI Runtime Services Table. 
        /// This header contains the EFI_RUNTIME_SERVICES_SIGNATURE 
        /// and EFI_RUNTIME_SERVICES_REVISION values along with the size of
        ///  the EFI_RUNTIME_SERVICES structure and a 32-bit CRC to
        ///  verify that the contents of the EFI Runtime Services Table are valid.
        /// </summary>
        EFI_TABLE_HEADER Hdr;

        //
        // Time Services
        //        
        /// <summary>
        /// Returns the current time and date, and the time-keeping capabilities of the platform.
        /// </summary>
        EFI_GET_TIME GetTime;        
        /// <summary>
        /// Sets the current local time and date information.
        /// </summary>
        EFI_SET_TIME SetTime;        
        /// <summary>
        /// Returns the current wakeup alarm clock setting.
        /// </summary>
        EFI_GET_WAKEUP_TIME GetWakeupTime;        
        /// <summary>
        /// Sets the system wakeup alarm clock time.
        /// </summary>
        EFI_SET_WAKEUP_TIME SetWakeupTime;

        //
        // Virtual Memory Services
        //        
        /// <summary>
        /// Used by a UEFI OS loader to convert from physical addressing to virtual addressing.
        /// </summary>
        EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;        
        /// <summary>
        /// Used by EFI components to convert internal pointers when switching to virtual addressing.
        /// </summary>
        EFI_CONVERT_POINTER ConvertPointer;

        //
        // Variable Services
        //        
        /// <summary>
        /// Returns the value of a variable.
        /// </summary>
        EFI_GET_VARIABLE GetVariable;
        /// <summary>
        /// enum classerates the current variable names.
        /// </summary>
        EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;        
        /// <summary>
        /// The set variable
        /// </summary>
        EFI_SET_VARIABLE SetVariable;


        //
        // Miscellaneous Services
        //        
        /// <summary>
        /// Returns the next high 32 bits of the platform’s monotonic counter.
        /// </summary>
        EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;        
        /// <summary>
        /// Resets the entire platform.
        /// </summary>
        EFI_RESET_SYSTEM ResetSystem;

        //
        // UEFI 2.0 Capsule Services
        //        
        /// <summary>
        /// Passes capsules to the firmware with both virtual and physical mapping. EFI 2.0+
        /// </summary>
        EFI_UPDATE_CAPSULE UpdateCapsule;        
        /// <summary>
        /// Returns if the capsule can be supported via UpdateCapsule() . EFI 2.0+
        /// </summary>
        EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;


        //
        // Miscellaneous UEFI 2.0 Service
        //        
        /// <summary>
        /// Returns information about the EFI variable store. EFI 2.0+
        /// </summary>
        EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
	};
}
