#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>
#include <EFI_STATUS.h>
#include <FileSystem/FileInfo.h>
#include <FileSystem/FileMode.h>
#include <FileSystem/FileAttribute.h>

namespace Common::FileSystem
{
	struct FileHandle
	{
		friend class FileSystemContext;
	protected:
		FileHandle(EFI::EFI_FILE_PROTOCOL* file, FileInfo* i, FileMode mode, UINT64 attribs) : Mode(mode),Attributes(attribs), Info(*i), Size(i->Size), _File(file) {};

	public:
		constexpr FileHandle(): _File(nullptr), Size(0), Mode(FileMode::Create), Attributes(0) {};

		static FileHandle Create(EFI::EFI_FILE_PROTOCOL* file, FileInfo* i, FileMode mode, UINT64 attribs);
		FileMode Mode;
		UINT64 Attributes;
		FileInfo Info;
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


		bool operator ==(const FileHandle& right);
		bool operator !=(const FileHandle& right);
		
	protected:
		EFI::EFI_FILE_PROTOCOL* _File;
	};

	constinit const FileHandle Empty_FileHandle = FileHandle();
}