#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_STATUS.h>
#include "VolumeInfo.h"

namespace Common::FileSystem
{
	struct VolumeHandle
	{
		friend class ESP_FS_Context;
	protected:
		VolumeHandle(EFI::EFI_FILE_PROTOCOL* file, VolumeInfo& i, FileMode mode, FileAttribute attribs) : Mode(mode), Attributes(attribs), Info(i), Size(i.Size), _File(file) {};

	public:
		constexpr VolumeHandle() : _File(nullptr), Size(0), Mode(FileMode::Create), Attributes(FileAttribute::ValidAttrib) {};

		static VolumeHandle Create(EFI::EFI_FILE_PROTOCOL* file, VolumeInfo i, FileMode mode, FileAttribute attribs);

		FileMode Mode;
		FileAttribute Attributes;
		VolumeInfo Info;
		UINT64 Size;

		/*
		*  Below are all the functions needed to read, write, seek, close and delete, etc.
		*/

		EFI::EFI_STATUS Read(UINTN* bufferSize, void* buffer);
		EFI::EFI_STATUS Write(UINTN* bufferSize, void* buffer);
		EFI::EFI_STATUS GetPosition(UINT64* position);
		EFI::EFI_STATUS SetPosition(UINT64 position);
		EFI::EFI_STATUS GetInfo(EFI::EFI_GUID* infoType, UINTN* bufferSize, void* buffer);
		EFI::EFI_STATUS SetInfo(EFI::EFI_GUID* infoType, UINTN bufferSize, void* buffer);
		EFI::EFI_STATUS Flush();
		EFI::EFI_STATUS Close();
		EFI::EFI_STATUS Delete();
		EFI::EFI_STATUS ReadAsync(EFI::EFI_FILE_IO_TOKEN* token);
		EFI::EFI_STATUS WriteAsync(EFI::EFI_FILE_IO_TOKEN* token);
		EFI::EFI_STATUS FlushAsync(EFI::EFI_FILE_IO_TOKEN* token);


		BOOLEAN operator ==(const VolumeHandle& right);
		BOOLEAN operator !=(const VolumeHandle& right);

	protected:
		EFI::EFI_FILE_PROTOCOL* _File;
	};

	constinit const VolumeHandle Empty_VolumeHandle = VolumeHandle();
}
