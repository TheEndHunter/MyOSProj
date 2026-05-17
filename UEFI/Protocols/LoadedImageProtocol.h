#pragma once
#include <Guid.h>
#include <Handle.h>
#include <SystemTable.h>
#include <Services/BootServices.h>
#include <MemoryType.h>
#include <Status.h>
#include <Protocols/IO/DevicePathProtocol.h>
#include <UEFIDef.h>

namespace Efi
{
	constinit  const ALIGN(8) Efi::Guid EFI_LOADED_IMAGE_PROTOCOL_GUID = { 0x5B1B31A1, 0x9562, 0x11d2,{ 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} };
	constinit  const ALIGN(8) Efi::Guid EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID = { 0xbc62157e,0x3e33,0x4fec,{0x99,0x20,0x2d,0x3b,0x36,0xd7,0x50,0xdf} };

	CONST UINT16 EFI_LOADED_IMAGE_PROTOCOL_REVISION = 0x1000;

	enum class LoadOptionAttribute
	{
		LOAD_OPTION_ACTIVE = 0x00000001,
		LOAD_OPTION_FORCE_RECONNECT = 0x00000002,
		LOAD_OPTION_HIDDEN = 0x00000008,
		LOAD_OPTION_CATEGORY = 0x00001F00,
		LOAD_OPTION_CATEGORY_BOOT = 0x00000000,
		LOAD_OPTION_CATEGORY_APP = 0x00000100,
		// All values 0x00000200-0x00001F00 are reserved
	};

	struct LoadOption
	{
	public:
		LoadOptionAttribute Attributes;
		UINT16 FilePathListLength;
		CHAR16* Description;
		DevicePathProtocol** FilePathList;
		UINT8** OptionalData;
	};

	typedef Status(EFIAPI* ImageUnload) (IN Handle ImageHandle);

	struct LoadedImageProtocol 
	{
	public:
		UINT32 Revision;
		Handle ParentHandle;
		SystemTable* SystemTable;

		// Source location of the image
		Handle DeviceHandle;
		DevicePathProtocol* FilePath;
		VOID* Reserved;

		// Image’s load options
		UINT32 LoadOptionsSize;
		VOID* LoadOptions;

		// Location where image was loaded
		VOID* ImageBase;
		UINT64 ImageSize;
		MemoryType ImageCodeType;
		MemoryType ImageDataType;
		ImageUnload Unload;
	};
}
