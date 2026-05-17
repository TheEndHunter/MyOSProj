#pragma once
#include <TypeDefs.h>
#include <SystemTable.h>
#include <Status.h>
#include "VolumeInfo.h"

namespace Common::FileSystem
{
	struct VolumeHandle
	{
		friend class ESP_FS_Context;
	protected:
		VolumeHandle(Efi::FileProtocol* file, VolumeInfo& i, FileMode mode, FileAttribute attribs) : Mode(mode), Attributes(attribs), Info(i), Size(i.Size), File(file) {};

	public:
		constexpr VolumeHandle() : File(nullptr), Size(0), Mode(FileMode::Create), Attributes(FileAttribute::ValidAttrib) {};

		static VolumeHandle Create(Efi::FileProtocol* file, VolumeInfo i, FileMode mode, FileAttribute attribs);

		FileMode Mode;
		FileAttribute Attributes;
		VolumeInfo Info;
		UINT64 Size;

		/*
		*  Below are all the functions needed to read, write, seek, close and delete, etc.
		*/

		Efi::Status Read(UINTN* bufferSize, void* buffer);
		Efi::Status Write(UINTN* bufferSize, void* buffer);
		Efi::Status GetPosition(UINT64* position);
		Efi::Status SetPosition(UINT64 position);
		Efi::Status GetInfo(Efi::Guid* infoType, UINTN* bufferSize, void* buffer);
		Efi::Status SetInfo(Efi::Guid* infoType, UINTN bufferSize, void* buffer);
		Efi::Status Flush();
		Efi::Status Close();
		Efi::Status Delete();
        Efi::Status ReadAsync(Efi::FileIOToken* token);
        Efi::Status WriteAsync(Efi::FileIOToken* token);
        Efi::Status FlushAsync(Efi::FileIOToken* token);


		BOOLEAN operator ==(const VolumeHandle& right);
		BOOLEAN operator !=(const VolumeHandle& right);

	protected:
		Efi::FileProtocol* File;
	};

	constinit const VolumeHandle Empty_VolumeHandle = VolumeHandle();
}
