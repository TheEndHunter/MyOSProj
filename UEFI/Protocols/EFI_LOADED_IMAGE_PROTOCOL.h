#pragma once
#include <EFI_GUID.h>
#include <EFI_HANDLE.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_BOOT_SERVICES.h>
#include <EFI_MEMORY_TYPE.h>
#include <EFI_STATUS.h>
#include <Protocols/IO/EFI_DEVICE_PATH_PROTOCOL.h>
#include <UEFIDef.h>

namespace EFI
{
	constinit  const ALIGN(8) EFI::EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID = { 0x5B1B31A1, 0x9562, 0x11d2,{ 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} };
	constinit  const ALIGN(8) EFI::EFI_GUID EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID = { 0xbc62157e,0x3e33,0x4fec,{0x99,0x20,0x2d,0x3b,0x36,0xd7,0x50,0xdf} };

	inline const UINT16 EFI_LOADED_IMAGE_PROTOCOL_REVISION = 0x1000;

	enum class EFI_LOAD_OPTION_ATTRIBUTE
	{
		LOAD_OPTION_ACTIVE = 0x00000001,
		LOAD_OPTION_FORCE_RECONNECT = 0x00000002,
		LOAD_OPTION_HIDDEN = 0x00000008,
		LOAD_OPTION_CATEGORY = 0x00001F00,
		LOAD_OPTION_CATEGORY_BOOT = 0x00000000,
		LOAD_OPTION_CATEGORY_APP = 0x00000100,
		// All values 0x00000200-0x00001F00 are reserved
	};

	struct EFI_LOAD_OPTION
	{
	public:
		EFI_LOAD_OPTION_ATTRIBUTE Attributes;
		UINT16 FilePathListLength;
		CHAR16* Description;
		EFI_DEVICE_PATH_PROTOCOL** FilePathList;
		UINT8** OptionalData;
	};

	typedef EFI_STATUS(EFIAPI* EFI_IMAGE_UNLOAD) (IN EFI_HANDLE ImageHandle);

	struct EFI_LOADED_IMAGE_PROTOCOL 
	{
	public:
		UINT32 Revision;
		EFI_HANDLE ParentHandle;
		EFI_SYSTEM_TABLE* SystemTable;

		// Source location of the image
		EFI_HANDLE DeviceHandle;
		EFI_DEVICE_PATH_PROTOCOL* FilePath;
		VOID* Reserved;

		// Image’s load options
		UINT32 LoadOptionsSize;
		VOID* LoadOptions;

		// Location where image was loaded
		VOID* ImageBase;
		UINT64 ImageSize;
		EFI_MEMORY_TYPE ImageCodeType;
		EFI_MEMORY_TYPE ImageDataType;
		EFI_IMAGE_UNLOAD Unload;
	};
}
