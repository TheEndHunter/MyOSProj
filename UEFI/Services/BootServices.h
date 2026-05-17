#pragma once

#include "UEFIDef.h"
#include <Status.h>
#include <TableHeader.h>
#include <TPL.h>
#include <AllocateType.h>
#include "Event.h"
#include <Handle.h>
#include <EventNotify.h>
#include <LocateSearchType.h>
#include <InterfaceType.h>
#include <Protocols/Time/TimerDelay.h>

#include <Protocols/IO/DevicePathProtocol.h>
#include <Protocols/Configuration/OpenProtocolInformationEntry.h>
#include <MemoryType.h>
#include <Guid.h>
#include <MemoryDescriptor.h>

namespace Efi::Services
{
	struct BootServices;

	CONST UINT64 BootServicesSignature = 0x56524553544f4f42;
	CONST UINT64 BootServicesRevision = SpecificationVersion;

	CONST UINT32 OpenProtocolByHandleProtocol = 0x00000001;
	CONST UINT32 OpenProtocolGetProtocol = 0x00000002;
	CONST UINT32 OpenProtocolTestProtocol = 0x00000004;
	CONST UINT32 OpenProtocolByChildController = 0x00000008;
	CONST UINT32 OpenProtocolByDriver = 0x00000010;
	CONST UINT32 OpenProtocolExclusive = 0x00000020;

	typedef Status(EFIAPI* RaiseTplFunc) (IN TPL NewTpl);
	typedef Status(EFIAPI* RestoreTplFunc) (IN TPL OldTpl);

	typedef Status(EFIAPI* AllocatePagesFunc) (IN AllocateType Type, IN MemoryType MemoryType, IN UINTN Pages, OUT PhysicalAddress* Memory);
	typedef Status(EFIAPI* FreePagesFunc) (IN PhysicalAddress Memory, IN UINTN Pages);
	typedef Status(EFIAPI* GetMemoryMapFunc) (IN OUT UINTN* MemoryMapSize, INOUT MemoryDescriptor* MemoryMap, OUT UINTN* MapKey, OUT UINTN* DescriptorSize, OUT UINT32* DescriptorVersion);
	typedef Status(EFIAPI* AllocatePoolFunc) (IN MemoryType PoolType, IN UINTN Size, OUT VOID_PTR* Buffer);
	typedef Status(EFIAPI* FreePoolFunc) (IN VOID_PTR Buffer);

	typedef Status(EFIAPI* CreateEventFunc) (IN UINT32 Type, IN TPL NotifyTpl, IN EventNotify NotifyFunction OPTIONAL, IN VOID_PTR NotifyContext OPTIONAL, OUT Event* Event);
	typedef Status(EFIAPI* SetTimerFunc) (IN Event Event, IN TimerDelay Type, IN UINT64 TriggerTime);
	typedef Status(EFIAPI* WaitForEventFunc) (IN UINTN NumberOfEvents, IN Event* Event, OUT UINTN* Index);
	typedef Status(EFIAPI* SingalEventFunc) (IN Event Event);
	typedef Status(EFIAPI* CloseEventFunc) (IN Event Event);
	typedef Status(EFIAPI* CheckEventFunc) (IN Event Event);

	typedef Status(EFIAPI* InstallProtocolInterfaceFunc) (IN OUT Handle* Handle,IN const Guid* Protocol, IN InterfaceType InterfaceType, IN VOID_PTR Interface);
	typedef Status(EFIAPI* ReinstallProtocolInterfaceFunc) (IN Handle Handle,IN const Guid* Protocol, IN VOID_PTR OldInterface, IN VOID_PTR NewInterface);
	typedef Status(EFIAPI* UninstallProtocolInterfaceFunc) (IN Handle Handle,IN const Guid* Protocol, IN VOID_PTR Interface);
	typedef Status(EFIAPI* HandleProtocolFunc) (IN Handle Handle, IN const Guid* Protocol, OUT VOID_PTR* Interface);
	typedef Status(EFIAPI* RegisterProtocolNotifyFunc) (IN const Guid* Protocol, IN Event Event, OUT VOID_PTR* Registration);
	typedef Status(EFIAPI* LocateHandleFunc) (IN LocateSearchType SearchType,IN const Guid* Protocol OPTIONAL, IN VOID_PTR SearchKey OPTIONAL, IN OUT UINTN* BufferSize, OUT Handle* Buffer);
	typedef Status(EFIAPI* LocateDevicePathFunc) (IN const Guid* Protocol, IN OUT DevicePathProtocol** DevicePath, OUT Handle* Device);
	typedef Status(EFIAPI* InstallConfigurationTableFunc) (IN const Guid* Guid, IN VOID_PTR Table);

	typedef Status(EFIAPI* ImageLoadFunc) (IN BOOLEAN BootPolicy, IN Handle ParentImageHandle, IN DevicePathProtocol* DevicePath, IN VOID_PTR SourceBuffer OPTIONAL, IN UINTN SourceSize, OUT Handle* ImageHandle);
	typedef Status(EFIAPI* ImageStartFunc) (IN Handle ImageHandle, OUT UINTN* ExitDataSize, OUT CONST CHAR16** ExitData OPTIONAL);
	typedef Status(EFIAPI* ExitFunc) (IN Handle ImageHandle, IN Status ExitStatus, IN UINTN ExitDataSize, IN CONST CHAR16* ExitData OPTIONAL);
	typedef Status(EFIAPI* ImageUnloadFunc) (IN Handle ImageHandle);
	typedef Status(EFIAPI* ExitBootServicesFunc) (IN Handle ImageHandle, IN UINTN MapKey);

	typedef Status(EFIAPI* GetNextMonotonicCountFunc) (OUT UINT64* Count);
	typedef Status(EFIAPI* StallFunc) (IN UINTN Microseconds);
	typedef Status(EFIAPI* SetWatchdogTimerFunc) (IN UINTN Timeout, IN UINT64 WatchdogCode, IN UINTN DataSize, IN CHAR16* WatchdogData OPTIONAL);

	typedef Status(EFIAPI* ConnectControllerFunc) (IN Handle ControllerHandle, IN Handle* DriverImageHandle OPTIONAL, IN DevicePathProtocol* RemainingDevicePath OPTIONAL, IN BOOLEAN Recursive);
	typedef Status(EFIAPI* DisconnectControllerFunc) (IN Handle ControllerHandle, IN Handle DriverImageHandle OPTIONAL, IN Handle ChildHandle OPTIONAL);

	typedef Status(EFIAPI* OpenProtocolFunc) (IN Handle Handle,IN const Guid* Protocol, OUT VOID_PTR* Interface OPTIONAL, IN Efi::Handle AgentHandle, IN Efi::Handle ControllerHandle, IN UINT32 Attributes);
	typedef Status(EFIAPI* CloseProtocolFunc) (IN Handle Handle, IN const Guid* Protocol, IN Efi::Handle AgentHandle, IN Efi::Handle ControllerHandle);
	typedef Status(EFIAPI* OpenProtocolInformationFunc) (IN Handle Handle,IN const Guid* Protocol, OUT OpenProtocolInformationEntry** EntryBuffer, OUT UINTN* EntryCount);

	typedef Status(EFIAPI* ProtocolsPerHandleFunc) (IN Handle Handle, OUT Guid*** ProtocolBuffer, OUT UINTN* ProtocolBufferCount);
	typedef Status(EFIAPI* LocateHandleBufferFunc) (IN LocateSearchType SearchType,IN const Guid* Protocol OPTIONAL, IN VOID_PTR SearchKey OPTIONAL, IN OUT UINTN* NoHandles, OUT Handle** Buffer);
	typedef Status(EFIAPI* LocateProtocolFunc) (IN const Guid* Protocol, IN VOID_PTR Registration OPTIONAL, OUT VOID_PTR* Interface);
	typedef Status(EFIAPI* InstallMultipleProtocolInterfacesFunc) (IN OUT Handle* Handle, ...);
	typedef Status(EFIAPI* UninstallMultipleProtocolInterfacesFunc) (IN Handle Handle, ...);

	typedef Status(EFIAPI* CalculateCrc32Func) (IN VOID_PTR Data, IN UINTN DataSize, OUT UINT32* Crc32);
	typedef Status(EFIAPI* CopyMemFunc) (IN VOID_PTR Destination, IN VOID_PTR Source, IN UINTN Length);
	typedef Status(EFIAPI* SetMemFunc) (IN VOID_PTR Buffer, IN UINTN Size, IN UINT8 Value);
	typedef Status(EFIAPI* CreateEventExFunc) (IN UINT32 Type, IN TPL NotifyTpl, IN EventNotify NotifyFunction OPTIONAL, IN CONST VOID_PTR NotifyContext OPTIONAL, IN const Guid* EventGroup OPTIONAL, OUT Event* Event);

	
	/// <summary>
	/// EFI Boot Services Table
	/// </summary>
	struct BootServices
	{
	public:
		/// <summary>
		/// The table header for the EFI Runtime Services Table. 
		/// This header contains the RuntimeServicesSignature 
		/// and RuntimeServicesRevision values along with the size of
		///  the RuntimeServices structure and a 32-bit CRC to
		///  verify that the contents of the EFI Runtime Services Table are valid.
		/// </summary>
		TableHeader Hdr;
		//
		// Task Priority Services
		//		
		/// <summary>
		/// Raises the task priority level. EFI 1.0+
		/// </summary>
		RaiseTplFunc RaiseTPL;
		/// <summary>
		/// Restores/lowers the task priority level. EFI 1.0+
		/// </summary>
		RestoreTplFunc RestoreTPL;

		//
		// Memory Services
		//

		/// <summary>
		/// Allocates pages of a particular type.. EFI 1.0+
		/// </summary>
		AllocatePagesFunc AllocatePages;
		/// <summary>
		/// Frees allocated pages.. EFI 1.0+
		/// </summary>
		FreePagesFunc FreePages;
		/// <summary>
		/// Returns the current boot services memory map and memory map key. EFI 1.0+
		/// </summary>
		GetMemoryMapFunc GetMemoryMap;
		/// <summary>
		/// Allocates a pool of a particular type. EFI 1.0+
		/// </summary>
		AllocatePoolFunc AllocatePool;
		/// <summary>
		/// Frees allocated pool. EF I1.0+
		/// </summary>
		FreePoolFunc FreePool;

		//
		// Event & Timer Services
		//		
		/// <summary>
		/// Creates a general - purpose event structure. EFI 1.0+
		/// </summary>
		CreateEventFunc CreateEvent;		
		/// <summary>
		///  Sets an event to be signaled at a particular time. EFI 1.0+
		/// </summary>
		SetTimerFunc SetTimer;
		/// <summary>
		/// Stops execution until an event is signaled. EFI 1.0+
		/// </summary>
		WaitForEventFunc WaitForEvent;
		/// <summary>
		/// Signal an event. EFI 1.0+
		/// </summary>
		SingalEventFunc SignalEvent;
		/// <summary>
		/// Closes and frees an event structure. EFI 1.0+
		/// </summary>
		CloseEventFunc CloseEvent; 
		/// <summary>
		/// Checks whether an event is in the signaled state. EFI 1.0+
		/// </summary>
		CheckEventFunc CheckEvent;

		//
		// Protocol Handler Services
		//		
		/// <summary>
		/// Installs a protocol interface on a device handle. EFI1.0+
		/// </summary>
		InstallProtocolInterfaceFunc InstallProtocolInterface;		
		/// <summary>
		/// Reinstalls a protocol interface on a device handle. EFI 1.0+
		/// </summary>
		ReinstallProtocolInterfaceFunc ReinstallProtocolInterface;		
		/// <summary>
		/// Removes a protocol interface from a device handle. EFI 1.0+
		/// </summary>
		UninstallProtocolInterfaceFunc UninstallProtocolInterface;		
		/// <summary>
		/// Queries a handle to determine if it supports a specified protocol. EFI 1.0+
		/// </summary>
		HandleProtocolFunc HandleProtocol;		
		/// <summary>
		/// Reserved
		/// </summary>
		VOID_PTR Reserved;		
		/// <summary>
		/// Registers an event that is to be signaled whenever an interface is installed for a specified protocol. EFI 1.0+
		/// </summary>
		RegisterProtocolNotifyFunc RegisterProtocolNotify;		
		/// <summary>
		/// Returns an array of handles that support a specified protocol. EFI 1.0+
		/// </summary>
		LocateHandleFunc LocateHandle;		
		/// <summary>
		/// Locates all devices on a device path that support a specified protocol and returns the handle to the device that is closest to the path. EFI 1.0+
		/// </summary>
		LocateDevicePathFunc LocateDevicePath;		
		/// <summary>
		/// Adds, updates, or removes a configuration table from the EFI System Table. EFI 1.0+
		/// </summary>
		InstallConfigurationTableFunc InstallConfigurationTable;

		//
		// Image Services
		//		
		/// <summary>
		/// Loads an EFI image into memory. EFI 1.0+
		/// </summary>
		ImageUnloadFunc LoadImage;		
		/// <summary>
		/// Transfers control to a loaded image’s entry point. EFI 1.0+
		/// </summary>
		ImageStartFunc StartImage;		
		/// <summary>
		/// Exits the image’s entry point. EFI 1.0+
		/// </summary>
		ExitFunc Exit;		
		/// <summary>
		/// Unloads an image. EFI 1.0+
		/// </summary>
		ImageUnloadFunc UnloadImage;		
		/// <summary>
		/// Terminates boot services. EFI 1.0+
		/// </summary>
		ExitBootServicesFunc ExitBootServices;

		//
		// Miscellaneous Services
		//		
		/// <summary>
		/// Returns a monotonically increasing count for the platform. EFI 1.0+
		/// </summary>
		GetNextMonotonicCountFunc GetNextMonotonicCount;		
		/// <summary>
		/// Stalls the processor. EFI 1.0+
		/// </summary>
		StallFunc Stall;		
		/// <summary>
		/// Resets and sets a watchdog timer used during boot services time. EFI 1.0+
		/// </summary>
		SetWatchdogTimerFunc SetWatchdogTimer;

		//
		// DriverSupport Services		
		/// <summary>
		/// Uses a set of precedence rules to find the best set of drivers to manage a controller. EFI 1.1+
		/// </summary>
		ConnectControllerFunc ConnectController;		
		/// <summary>
		/// Informs a set of drivers to stop managing a controller. EFI 1.1+
		/// </summary>
		DisconnectControllerFunc DisconnectController;

		//
		// Open and Close Protocol Services
		//
		//		
		/// <summary>
		/// Queries a handle to determine if it supports a specified protocol.
		///  If the protocol is supported by the handle, it opens the protocol on behalf of the calling agent. 
		/// This is an extended version of the EFI boot service BootServices.HandleProtocol() . EFI 1.1+
		/// </summary>
		OpenProtocolFunc OpenProtocol;		
		/// <summary>
		/// Removes elements from the list of agents consuming a protocol interface. EFI 1.1+
		/// </summary>
		CloseProtocolFunc CloseProtocol;		
		/// <summary>
		/// Retrieve the list of agents that are currently consuming a protocol interface. EFI 1.1+
		/// </summary>
		OpenProtocolInformationFunc OpenProtocolInformation;
		//
		// Library Services
		//		
		/// <summary>
		/// Retrieves the list of protocols installed on a handle.
		/// The return buffer is automatically allocated. EFI 1.1+
		/// </summary>
		ProtocolsPerHandleFunc ProtocolsPerHandle;	
		/// <summary> 	
		/// Retrieves the list of handles from the handle database that meet the search criteria.
		/// The return buffer is automatically allocated. EFI 1.1+
		/// </summary>
		LocateHandleBufferFunc LocateHandleBuffer;
		/// <summary>
		/// Finds the first handle in the handle database the supports the requested protocol. EFI 1.1+
		/// </summary>
		LocateProtocolFunc LocateProtocol;
		/// <summary>
		/// Installs one or more protocol interfaces onto a handle. EFI 1.1+
		/// </summary>
		InstallMultipleProtocolInterfacesFunc InstallMultipleProtocolInterfaces;		
		/// <summary>
		/// Uninstalls one or more protocol interfaces from a handle. EFI 1.1+
		/// </summary>
		UninstallMultipleProtocolInterfacesFunc UninstallMultipleProtocolInterfaces;
		//
		// 32-bit CRC Services
		//		
		/// <summary>
		/// Computes and returns a 32-bit CRC for a data buffer. EFI 1.1+
		/// </summary>
		CalculateCrc32Func CalculateCrc32;

		//
		// Miscellaneous Services
		//		
		/// <summary>
		/// Copies the contents of one buffer to another buffer. EFI 1.1+
		/// </summary>
		CopyMemFunc CopyMem;	
		/// <summary>
		/// Fills a buffer with a specified value. EFI 1.1+
		/// </summary>
		SetMemFunc SetMem;		
		/// <summary>
		/// Creates an event structure as part of an event group. EFI 2.0+
		/// </summary>
		CreateEventExFunc CreateEventEx;
	};
}
