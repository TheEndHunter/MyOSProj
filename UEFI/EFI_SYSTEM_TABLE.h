#pragma once
#include "UEFIDef.h"
#include "EFI_TABLE_HEADER.h"
#include "Protocols/IO/Console/EFI_SIMPLE_TEXT_INPUT_PROTOCOL.h"
#include "Protocols/IO/Console/EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.h"
#include "EFI_RUNTIME_SERVICES.h"
#include "EFI_BOOT_SERVICES.h"
#include "EFI_HANDLE.h"
#include <Protocols/Configuration/EFI_CONFIGURATION_TABLE.h>

namespace EFI
{
	/*
	*  UEFI System Table Definition
	*/
	struct EFI_SYSTEM_TABLE
	{
	public:		
		/// <summary>
		/// The table header for the EFI System Table.
		/// This header contains the EFI_SYSTEM_TABLE_SIGNATURE and
		/// EFI_SYSTEM_TABLE_REVISION values along with the size of the EFI_SYSTEM_TABLE
		/// structure and a 32-bit CRC to verify that the contents of the EFI System Table are valid.
		/// </summary>
		EFI::EFI_TABLE_HEADER Hdr;		
		/// <summary>
		/// A pointer to a null terminated string that identifies
		///  the vendor that produces the system firmware for the platform.
		/// </summary>
		CHAR16* FirmwareVendor;		
		/// <summary>
		/// A firmware vendor specific value that identifies the revision of the system firmware for the platform.
		/// </summary>
		UINT32 FirmwareRevision;		
		/// <summary>
		/// The handle for the active console input device.
		/// This handle must support EFI_SIMPLE_TEXT_INPUT_PROTOCOL and EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.
		///  If there is no active console, these protocols must still be present.
		/// </summary>
		EFI::EFI_HANDLE ConsoleInHandle;		
		/// <summary>
		/// A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL interface that is associated with ConsoleInHandle.
		/// </summary>
		EFI::EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;		
		/// <summary>
		/// The handle for the active console output device.
		/// This handle must support the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.
		/// If there is no active console, this protocol must still be present.
		/// </summary>
		EFI::EFI_HANDLE ConsoleOutHandle;		
		/// <summary>
		/// A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
		/// interface that is associated with ConsoleOutHandle.
		/// </summary>
		EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;		
		/// <summary>
		/// The handle for the active standard error console device.
		/// This handle must support the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.
		///  If there is no active console, this protocol must still be present.
		/// </summary>
		EFI::EFI_HANDLE StandardErrorHandle;		
		/// <summary>
		/// A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
		///  interface that is associated with StandardErrorHandle.
		/// </summary>
		EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr;		
		/// <summary>
		/// A pointer to the EFI Runtime Services Table.
		/// </summary>
		EFI::EFI_RUNTIME_SERVICES* RuntimeServices;		
		/// <summary>
		/// A pointer to the EFI Boot Services Table. See ref:efi-boot-services-table_efi_system_table.
		/// </summary>
		EFI::EFI_BOOT_SERVICES* BootServices;		
		/// <summary>
		/// The number of system configuration tables in the buffer ConfigurationTable.
		/// </summary>
		UINTN NumberOfTableEntries;		
		/// <summary>
		/// A pointer to the system configuration tables. The number of entries in the table is NumberOfTableEntries.
		/// </summary>
		EFI::EFI_CONFIGURATION_TABLE* ConfigurationTable;
	};
};