#pragma once

#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_TABLE_HEADER.h"
#include "EFI_TPL.h"
#include "EFI_ALLOCATE_TYPE.h"
#include "EFI_EVENT.h"
#include "EFI_HANDLE.h"
#include "EFI_EVENT_NOTIFY.h"
#include "EFI_LOCATE_SEARCH_TYPE.h"
#include "EFI_INTERFACE_TYPE.h"
#include <Protocols/Time/EFI_TIMER_DELAY.h>
#include <Protocols/IO/EFI_DEVICE_PATH_PROTOCOL.h>
#include <Protocols/Configuration/EFI_OPEN_PROTOCOL_INFORMATION_ENTRY.h>
#include <EFI_MEMORY_TYPE.h>
#include <EFI_GUID.h>
#include <EFI_MEMORY_DESCRIPTOR.h>

namespace EFI
{
	struct EFI_BOOT_SERVICES;

	inline const UINT64 EFI_BOOT_SERVICES_SIGNATURE = 0x56524553544f4f42;
	inline const UINT64 EFI_BOOT_SERVICES_REVISION = EFI_SPECIFICATION_VERSION;

	inline const UINT32 EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL = 0x00000001;
	inline const UINT32 EFI_OPEN_PROTOCOL_GET_PROTOCOL = 0x00000002;
	inline const UINT32 EFI_OPEN_PROTOCOL_TEST_PROTOCOL = 0x00000004;
	inline const UINT32 EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER = 0x00000008;
	inline const UINT32 EFI_OPEN_PROTOCOL_BY_DRIVER = 0x00000010;
	inline const UINT32 EFI_OPEN_PROTOCOL_EXCLUSIVE = 0x00000020;

	typedef EFI::EFI_STATUS(EFIAPI* EFI_RAISE_TPL) (IN EFI::EFI_TPL NewTpl);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_RESTORE_TPL) (IN EFI::EFI_TPL OldTpl);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_ALLOCATE_PAGES) (IN EFI::EFI_ALLOCATE_TYPE Type, IN EFI::EFI_MEMORY_TYPE MemoryType, IN UINTN Pages, OUT EFI::EFI_PHYSICAL_ADDRESS* Memory);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_FREE_PAGES) (IN EFI::EFI_PHYSICAL_ADDRESS Memory, IN UINTN Pages);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_GET_MEMORY_MAP) (IN OUT UINTN* MemoryMapSize, INOUT EFI::EFI_MEMORY_DESCRIPTOR* MemoryMap, OUT UINTN* MapKey, OUT UINTN* DescriptorSize, OUT UINT32* DescriptorVersion);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_ALLOCATE_POOL) (IN EFI::EFI_MEMORY_TYPE PoolType, IN UINTN Size, OUT VOID_PTR* Buffer);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_FREE_POOL) (IN VOID_PTR Buffer);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_CREATE_EVENT) (IN UINT32 Type, IN EFI::EFI_TPL NotifyTpl, IN EFI::EFI_EVENT_NOTIFY NotifyFunction OPTIONAL, IN VOID_PTR NotifyContext OPTIONAL, OUT EFI::EFI_EVENT* Event);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_SET_TIMER) (IN EFI::EFI_EVENT Event, IN EFI::EFI_TIMER_DELAY Type, IN UINT64 TriggerTime);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_WAIT_FOR_EVENT) (IN UINTN NumberOfEvents, IN EFI::EFI_EVENT* Event, OUT UINTN* Index);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_SIGNAL_EVENT) (IN EFI::EFI_EVENT Event);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_CLOSE_EVENT) (IN EFI::EFI_EVENT Event);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_CHECK_EVENT) (IN EFI::EFI_EVENT Event);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_INSTALL_PROTOCOL_INTERFACE) (IN OUT EFI::EFI_HANDLE* Handle,IN const EFI_GUID* Protocol, IN EFI::EFI_INTERFACE_TYPE InterfaceType, IN VOID_PTR Interface);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_REINSTALL_PROTOCOL_INTERFACE) (IN EFI::EFI_HANDLE Handle,IN const EFI_GUID* Protocol, IN VOID_PTR OldInterface, IN VOID_PTR NewInterface);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_UNINSTALL_PROTOCOL_INTERFACE) (IN EFI::EFI_HANDLE Handle,IN const EFI_GUID* Protocol, IN VOID_PTR Interface);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_HANDLE_PROTOCOL) (IN EFI::EFI_HANDLE Handle, IN const EFI_GUID* Protocol, OUT VOID_PTR* Interface);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_REGISTER_PROTOCOL_NOTIFY) (IN const EFI_GUID* Protocol, IN EFI::EFI_EVENT Event, OUT VOID_PTR* Registration);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_LOCATE_HANDLE) (IN EFI::EFI_LOCATE_SEARCH_TYPE SearchType,IN const EFI_GUID* Protocol OPTIONAL, IN VOID_PTR SearchKey OPTIONAL, IN OUT UINTN* BufferSize, OUT EFI::EFI_HANDLE* Buffer);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_LOCATE_DEVICE_PATH) (IN const EFI_GUID* Protocol, IN OUT EFI::EFI_DEVICE_PATH_PROTOCOL** DevicePath, OUT EFI::EFI_HANDLE* Device);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_INSTALL_CONFIGURATION_TABLE) (IN const EFI_GUID* Guid, IN VOID_PTR Table);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_IMAGE_LOAD) (IN BOOLEAN BootPolicy, IN EFI::EFI_HANDLE ParentImageHandle, IN EFI::EFI_DEVICE_PATH_PROTOCOL* DevicePath, IN VOID_PTR SourceBuffer OPTIONAL, IN UINTN SourceSize, OUT EFI::EFI_HANDLE* ImageHandle);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_IMAGE_START) (IN EFI::EFI_HANDLE ImageHandle, OUT UINTN* ExitDataSize, OUT CHAR16** ExitData OPTIONAL);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_EXIT) (IN EFI::EFI_HANDLE ImageHandle, IN EFI::EFI_STATUS ExitStatus, IN UINTN ExitDataSize, IN CHAR16* ExitData OPTIONAL);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_IMAGE_UNLOAD) (IN EFI::EFI_HANDLE ImageHandle);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_EXIT_BOOT_SERVICES) (IN EFI::EFI_HANDLE ImageHandle, IN UINTN MapKey);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_GET_NEXT_MONOTONIC_COUNT) (OUT UINT64* Count);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_STALL) (IN UINTN Microseconds);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_SET_WATCHDOG_TIMER) (IN UINTN Timeout, IN UINT64 WatchdogCode, IN UINTN DataSize, IN CHAR16* WatchdogData OPTIONAL);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_CONNECT_CONTROLLER) (IN EFI::EFI_HANDLE ControllerHandle, IN EFI::EFI_HANDLE* DriverImageHandle OPTIONAL, IN EFI::EFI_DEVICE_PATH_PROTOCOL* RemainingDevicePath OPTIONAL, IN BOOLEAN Recursive);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_DISCONNECT_CONTROLLER) (IN EFI::EFI_HANDLE ControllerHandle, IN EFI::EFI_HANDLE DriverImageHandle OPTIONAL, IN EFI::EFI_HANDLE ChildHandle OPTIONAL);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_OPEN_PROTOCOL) (IN EFI::EFI_HANDLE Handle,IN const EFI_GUID* Protocol, OUT VOID_PTR* Interface OPTIONAL, IN EFI::EFI_HANDLE AgentHandle, IN EFI::EFI_HANDLE ControllerHandle, IN UINT32 Attributes);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_CLOSE_PROTOCOL) (IN EFI::EFI_HANDLE Handle,IN const EFI_GUID* Protocol, IN EFI::EFI_HANDLE AgentHandle, IN EFI::EFI_HANDLE ControllerHandle);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_OPEN_PROTOCOL_INFORMATION) (IN EFI::EFI_HANDLE Handle,IN const EFI_GUID* Protocol, OUT EFI::EFI_OPEN_PROTOCOL_INFORMATION_ENTRY** EntryBuffer, OUT UINTN* EntryCount);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_PROTOCOLS_PER_HANDLE) (IN EFI::EFI_HANDLE Handle, OUT EFI_GUID*** ProtocolBuffer, OUT UINTN* ProtocolBufferCount);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_LOCATE_HANDLE_BUFFER) (IN EFI::EFI_LOCATE_SEARCH_TYPE SearchType,IN const EFI_GUID* Protocol OPTIONAL, IN VOID_PTR SearchKey OPTIONAL, IN OUT UINTN* NoHandles, OUT EFI::EFI_HANDLE** Buffer);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_LOCATE_PROTOCOL) (IN const EFI_GUID* Protocol, IN VOID_PTR Registration OPTIONAL, OUT VOID_PTR* Interface);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (IN OUT EFI::EFI_HANDLE* Handle, ...);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (IN EFI::EFI_HANDLE Handle, ...);

	typedef EFI::EFI_STATUS(EFIAPI* EFI_CALCULATE_CRC32) (IN VOID_PTR Data, IN UINTN DataSize, OUT UINT32* Crc32);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_COPY_MEM) (IN VOID_PTR Destination, IN VOID_PTR Source, IN UINTN Length);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_SET_MEM) (IN VOID_PTR Buffer, IN UINTN Size, IN UINT8 Value);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_CREATE_EVENT_EX) (IN UINT32 Type, IN EFI::EFI_TPL NotifyTpl, IN EFI::EFI_EVENT_NOTIFY NotifyFunction OPTIONAL, IN CONST VOID_PTR NotifyContext OPTIONAL, IN const EFI_GUID* EventGroup OPTIONAL, OUT EFI::EFI_EVENT* Event);

	
	/// <summary>
	/// EFI Boot Services Table
	/// </summary>
	struct EFI_BOOT_SERVICES
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
		// Task Priority Services
		//		
		/// <summary>
		/// Raises the task priority level. EFI 1.0+
		/// </summary>
		EFI::EFI_RAISE_TPL RaiseTPL;
		/// <summary>
		/// Restores/lowers the task priority level. EFI 1.0+
		/// </summary>
		EFI::EFI_RESTORE_TPL RestoreTPL;

		//
		// Memory Services
		//

		/// <summary>
		/// Allocates pages of a particular type.. EFI 1.0+
		/// </summary>
		EFI::EFI_ALLOCATE_PAGES AllocatePages;
		/// <summary>
		/// Frees allocated pages.. EFI 1.0+
		/// </summary>
		EFI::EFI_FREE_PAGES FreePages;
		/// <summary>
		/// Returns the current boot services memory map and memory map key. EFI 1.0+
		/// </summary>
		EFI::EFI_GET_MEMORY_MAP GetMemoryMap;
		/// <summary>
		/// Allocates a pool of a particular type. EFI 1.0+
		/// </summary>
		EFI::EFI_ALLOCATE_POOL AllocatePool;
		/// <summary>
		/// Frees allocated pool. EF I1.0+
		/// </summary>
		EFI::EFI_FREE_POOL FreePool;

		//
		// Event & Timer Services
		//		
		/// <summary>
		/// Creates a general - purpose event structure. EFI 1.0+
		/// </summary>
		EFI::EFI_CREATE_EVENT CreateEvent;		
		/// <summary>
		///  Sets an event to be signaled at a particular time. EFI 1.0+
		/// </summary>
		EFI::EFI_SET_TIMER SetTimer;
		/// <summary>
		/// Stops execution until an event is signaled. EFI 1.0+
		/// </summary>
		EFI::EFI_WAIT_FOR_EVENT WaitForEvent;
		/// <summary>
		/// Signal an event. EFI 1.0+
		/// </summary>
		EFI::EFI_SIGNAL_EVENT SignalEvent;
		/// <summary>
		/// Closes and frees an event structure. EFI 1.0+
		/// </summary>
		EFI::EFI_CLOSE_EVENT CloseEvent; 
		/// <summary>
		/// Checks whether an event is in the signaled state. EFI 1.0+
		/// </summary>
		EFI::EFI_CHECK_EVENT CheckEvent;

		//
		// Protocol Handler Services
		//		
		/// <summary>
		/// Installs a protocol interface on a device handle. EFI1.0+
		/// </summary>
		EFI::EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;		
		/// <summary>
		/// Reinstalls a protocol interface on a device handle. EFI 1.0+
		/// </summary>
		EFI::EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;		
		/// <summary>
		/// Removes a protocol interface from a device handle. EFI 1.0+
		/// </summary>
		EFI::EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;		
		/// <summary>
		/// Queries a handle to determine if it supports a specified protocol. EFI 1.0+
		/// </summary>
		EFI::EFI_HANDLE_PROTOCOL HandleProtocol;		
		/// <summary>
		/// Reserved
		/// </summary>
		VOID_PTR Reserved;		
		/// <summary>
		/// Registers an event that is to be signaled whenever an interface is installed for a specified protocol. EFI 1.0+
		/// </summary>
		EFI::EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;		
		/// <summary>
		/// Returns an array of handles that support a specified protocol. EFI 1.0+
		/// </summary>
		EFI::EFI_LOCATE_HANDLE LocateHandle;		
		/// <summary>
		/// Locates all devices on a device path that support a specified protocol and returns the handle to the device that is closest to the path. EFI 1.0+
		/// </summary>
		EFI::EFI_LOCATE_DEVICE_PATH LocateDevicePath;		
		/// <summary>
		/// Adds, updates, or removes a configuration table from the EFI System Table. EFI 1.0+
		/// </summary>
		EFI::EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

		//
		// Image Services
		//		
		/// <summary>
		/// Loads an EFI image into memory. EFI 1.0+
		/// </summary>
		EFI::EFI_IMAGE_UNLOAD LoadImage;		
		/// <summary>
		/// Transfers control to a loaded image’s entry point. EFI 1.0+
		/// </summary>
		EFI::EFI_IMAGE_START StartImage;		
		/// <summary>
		/// Exits the image’s entry point. EFI 1.0+
		/// </summary>
		EFI::EFI_EXIT Exit;		
		/// <summary>
		/// Unloads an image. EFI 1.0+
		/// </summary>
		EFI::EFI_IMAGE_UNLOAD UnloadImage;		
		/// <summary>
		/// Terminates boot services. EFI 1.0+
		/// </summary>
		EFI::EFI_EXIT_BOOT_SERVICES ExitBootServices;

		//
		// Miscellaneous Services
		//		
		/// <summary>
		/// Returns a monotonically increasing count for the platform. EFI 1.0+
		/// </summary>
		EFI::EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;		
		/// <summary>
		/// Stalls the processor. EFI 1.0+
		/// </summary>
		EFI::EFI_STALL Stall;		
		/// <summary>
		/// Resets and sets a watchdog timer used during boot services time. EFI 1.0+
		/// </summary>
		EFI::EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

		//
		// DriverSupport Services		
		/// <summary>
		/// Uses a set of precedence rules to find the best set of drivers to manage a controller. EFI 1.1+
		/// </summary>
		EFI::EFI_CONNECT_CONTROLLER ConnectController;		
		/// <summary>
		/// Informs a set of drivers to stop managing a controller. EFI 1.1+
		/// </summary>
		EFI::EFI_DISCONNECT_CONTROLLER DisconnectController;

		//
		// Open and Close Protocol Services
		//
		//		
		/// <summary>
		/// Queries a handle to determine if it supports a specified protocol.
		///  If the protocol is supported by the handle, it opens the protocol on behalf of the calling agent. 
		/// This is an extended version of the EFI boot service EFI_BOOT_SERVICES.HandleProtocol() . EFI 1.1+
		/// </summary>
		EFI::EFI_OPEN_PROTOCOL OpenProtocol;		
		/// <summary>
		/// Removes elements from the list of agents consuming a protocol interface. EFI 1.1+
		/// </summary>
		EFI::EFI_CLOSE_PROTOCOL CloseProtocol;		
		/// <summary>
		/// Retrieve the list of agents that are currently consuming a protocol interface. EFI 1.1+
		/// </summary>
		EFI::EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

		//
		// Library Services
		//		
		/// <summary>
		/// Retrieves the list of protocols installed on a handle.
		/// The return buffer is automatically allocated. EFI 1.1+
		/// </summary>
		EFI::EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;	
		/// <summary> 	
		/// Retrieves the list of handles from the handle database that meet the search criteria.
		/// The return buffer is automatically allocated. EFI 1.1+
		/// </summary>
		EFI::EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
		/// <summary>
		/// Finds the first handle in the handle database the supports the requested protocol. EFI 1.1+
		/// </summary>
		EFI::EFI_LOCATE_PROTOCOL LocateProtocol;
		/// <summary>
		/// Installs one or more protocol interfaces onto a handle. EFI 1.1+
		/// </summary>
		EFI::EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;		
		/// <summary>
		/// Uninstalls one or more protocol interfaces from a handle. EFI 1.1+
		/// </summary>
		EFI::EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

		//
		// 32-bit CRC Services
		//		
		/// <summary>
		/// Computes and returns a 32-bit CRC for a data buffer. EFI 1.1+
		/// </summary>
		EFI::EFI_CALCULATE_CRC32 CalculateCrc32;

		//
		// Miscellaneous Services
		//		
		/// <summary>
		/// Copies the contents of one buffer to another buffer. EFI 1.1+
		/// </summary>
		EFI::EFI_COPY_MEM CopyMem;	
		/// <summary>
		/// Fills a buffer with a specified value. EFI 1.1+
		/// </summary>
		EFI::EFI_SET_MEM SetMem;		
		/// <summary>
		/// Creates an event structure as part of an event group. EFI 2.0+
		/// </summary>
		EFI::EFI_CREATE_EVENT_EX CreateEventEx;
	};
}
