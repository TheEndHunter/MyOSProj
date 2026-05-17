#pragma once
#include "UEFIDef.h"
#include <TableHeader.h>
#include "Protocols/IO/Console/SimpleTextInputProtocol.h"
#include "Protocols/IO/Console/SimpleTextOutputProtocol.h"
#include <Services/RuntimeServices.h>
#include <Services/BootServices.h>
#include <Handle.h>
#include <Protocols/Configuration/ConfigurationTable.h>

namespace Efi
{
	/*
	*  UEFI System Table Definition
	*/
	struct SystemTable
	{
	public:		
		/// <summary>
		/// The table header for the EFI System Table.
		/// This header contains the EFI_SYSTEM_TABLE_SIGNATURE and
		/// EFI_SYSTEM_TABLE_REVISION values along with the size of the SystemTable
		/// structure and a 32-bit CRC to verify that the contents of the EFI System Table are valid.
		/// </summary>
		Efi::TableHeader Hdr;		
		/// <summary>
		/// A pointer to a null terminated string that identifies
		///  the vendor that produces the system firmware for the platform.
		/// </summary>
		CONST CHAR16* FirmwareVendor;
		/// <summary>
		/// A firmware vendor specific value that identifies the revision of the system firmware for the platform.
		/// </summary>
		UINT32 FirmwareRevision;		
		/// <summary>
		/// The handle for the active console input device.
		/// This handle must support SimpleTextInputProtocol and SimpleTextInputExProtocol.
		///  If there is no active console, these protocols must still be present.
		/// </summary>
		Efi::Handle ConsoleInHandle;		
		/// <summary>
		/// A pointer to the SimpleTextInputProtocol interface that is associated with ConsoleInHandle.
		/// </summary>
		Efi::SimpleTextInputProtocol* ConIn;		
		/// <summary>
		/// The handle for the active console output device.
		/// This handle must support the SimpleTextOutputProtocol.
		/// If there is no active console, this protocol must still be present.
		/// </summary>
		Efi::Handle ConsoleOutHandle;		
		/// <summary>
		/// A pointer to the SimpleTextOutputProtocol
		/// interface that is associated with ConsoleOutHandle.
		/// </summary>
		Efi::SimpleTextOutputProtocol* ConOut;		
		/// <summary>
		/// The handle for the active standard error console device.
		/// This handle must support the SimpleTextOutputProtocol.
		///  If there is no active console, this protocol must still be present.
		/// </summary>
		Efi::Handle StandardErrorHandle;		
		/// <summary>
		/// A pointer to the SimpleTextOutputProtocol
		///  interface that is associated with StandardErrorHandle.
		/// </summary>
		Efi::SimpleTextOutputProtocol* StdErr;		
		/// <summary>
		/// A pointer to the EFI Runtime Services Table.
		/// </summary>
		Efi::Services::RuntimeServices* RuntimeServices;		
		/// <summary>
		/// A pointer to the EFI Boot Services Table. See ref:efi-boot-services-table_efi_system_table.
		/// </summary>
		Efi::Services::BootServices* BootServices;		
		/// <summary>
		/// The number of system configuration tables in the buffer ConfigurationTable.
		/// </summary>
		UINTN NumberOfTableEntries;		
		/// <summary>
		/// A pointer to the system configuration tables. The number of entries in the table is NumberOfTableEntries.
		/// </summary>
		Efi::ConfigurationTable* ConfigurationTable;
	};
};