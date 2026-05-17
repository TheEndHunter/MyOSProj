#pragma once

#include <UEFIDef.h>
#include <Status.h>
#include <ResetType.h>
#include <TableHeader.h>
#include <Protocols/Configuration/CapsuleHeader.h>
#include <Protocols/Time/Time.h>
#include <Protocols/Time/TimeCapabilities.h>
#include <MemoryDescriptor.h>

namespace Efi::Services
{

    CONST UINT64 RuntimeServicesSignature = 0x56524553544e5552;
    CONST UINT64 RuntimeServicesRevision = SpecificationVersion;

    typedef Status (EFIAPI* GetTimeFunc)(OUT Time* t,OUT TimeCapabilities* Capabilities OPTIONAL);
    typedef Status (EFIAPI* SetTimeFunc)(IN Time* t);
    typedef Status (EFIAPI* GetWakeupTimeFunc)(OUT BOOLEAN* Enabled,OUT BOOLEAN* Pending,OUT Time* t);
    typedef Status (EFIAPI* SetWakeupTimeFunc)(IN BOOLEAN Enable,IN Time* t OPTIONAL);

	typedef Status (EFIAPI* SetVirtualAddressMapFunc)(IN UINTN MemoryMapSize,IN UINTN DescriptorSize,IN UINT32 DescriptorVersion,IN MemoryDescriptor* VirtualMap);
    typedef Status (EFIAPI* ConvertPointerFunc)(IN UINTN DebugDisposition,IN VOID** Address);

    typedef Status (EFIAPI* GetVariableFunc)(IN CHAR16* VariableName,IN const Guid* VendorGuid,OUT UINT32* Attributes OPTIONAL,IN OUT UINTN* DataSize,OUT VOID* Data OPTIONAL);

    typedef Status (EFIAPI* GetNextVariableNameFunc)(IN OUT UINTN* VariableNameSize,IN OUT CONST CHAR16* VariableName,IN OUT Guid* VendorGuid);
	typedef Status (EFIAPI* SetVariableFunc)(IN CONST CHAR16* VariableName,IN const Guid* VendorGuid,IN UINT32 Attributes,IN UINTN DataSize,IN VOID* Data);

	typedef Status (EFIAPI* GetNextHighMonoCountFunc)(OUT UINT32* HighCount);
	typedef VOID (EFIAPI* ResetSystemFunc)(IN Efi::ResetType ResetType,IN Status ResetStatus,IN UINTN DataSize,IN VOID* ResetData OPTIONAL);

    typedef Status (EFIAPI* UpdateCapsuleFunc)(IN CapsuleHeader** CapsuleHeaderArray,IN UINTN CapsuleCount,IN PhysicalAddress ScatterGatherList OPTIONAL);
    typedef Status (EFIAPI* QueryCapsuleCapabilitiesFunc)(IN CapsuleHeader** CapsuleHeaderArray,IN UINTN CapsuleCount,OUT UINT64* MaximumCapsuleSize,OUT ResetType* ResetType);

	typedef Status (EFIAPI* QueryVariableInfoFunc)(IN UINT32 Attributes,OUT UINT64* MaximumVariableStorageSize,OUT UINT64* RemainingVariableStorageSize,OUT UINT64* MaximumVariableSize);

    //******************************************************
    // EFI_OPTIONAL_PTR
    //******************************************************
    CONST UINTN EFI_OPTIONAL_PTR = 1;

	struct RuntimeServices
	{
	public:        
        /// <summary>
        /// The table header for the EFI Runtime Services Table. 
        /// This header contains the RuntimeServicesSignature 
        /// and RuntimeServicesRevision values along with the size of
        ///  the RuntimeServices structure and a 32-bit CRC to
        ///  verify that the contents of the EFI Runtime Services Table are valid.
        /// </summary>
        Efi::TableHeader Hdr;

        //
        // Time Services
        //        
        /// <summary>
        /// Returns the current time and date, and the time-keeping capabilities of the platform.
        /// </summary>
        GetTimeFunc GetTime;        
        /// <summary>
        /// Sets the current local time and date information.
        /// </summary>
        SetTimeFunc SetTime;        
        /// <summary>
        /// Returns the current wakeup alarm clock setting.
        /// </summary>
        GetWakeupTimeFunc GetWakeupTime;        
        /// <summary>
        /// Sets the system wakeup alarm clock time.
        /// </summary>
        SetWakeupTimeFunc SetWakeupTime;

        //
        // Virtual Memory Services
        //        
        /// <summary>
        /// Used by a UEFI OS loader to convert from physical addressing to virtual addressing.
        /// </summary>
        SetVirtualAddressMapFunc SetVirtualAddressMap;        
        /// <summary>
        /// Used by EFI components to convert internal pointers when switching to virtual addressing.
        /// </summary>
        ConvertPointerFunc ConvertPointer;

        //
        // Variable Services
        //        
        /// <summary>
        /// Returns the value of a variable.
        /// </summary>
        GetVariableFunc GetVariable;
        /// <summary>
        /// Gets the current variable names.
        /// </summary>
        GetNextVariableNameFunc GetNextVariableName;        
        /// <summary>
        /// The set variable
        /// </summary>
        SetVariableFunc SetVariable;


        //
        // Miscellaneous Services
        //        
        /// <summary>
        /// Returns the next high 32 bits of the platform’s monotonic counter.
        /// </summary>
        GetNextHighMonoCountFunc GetNextHighMonotonicCount;        
        /// <summary>
        /// Resets the entire platform.
        /// </summary>
        ResetSystemFunc ResetSystem;

        //
        // UEFI 2.0 Capsule Services
        //        
        /// <summary>
        /// Passes capsules to the firmware with both virtual and physical mapping. EFI 2.0+
        /// </summary>
        UpdateCapsuleFunc UpdateCapsule;        
        /// <summary>
        /// Returns if the capsule can be supported via UpdateCapsule() . EFI 2.0+
        /// </summary>
        QueryCapsuleCapabilitiesFunc QueryCapsuleCapabilities;


        //
        // Miscellaneous UEFI 2.0 Service
        //        
        /// <summary>
        /// Returns information about the EFI variable store. EFI 2.0+
        /// </summary>
        QueryVariableInfoFunc QueryVariableInfo;
	};
}
