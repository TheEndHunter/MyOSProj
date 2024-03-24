#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>
#include <EFI_STATUS.h>
#include <FileSystem/ESP/FileInfo.h>
#include <FileSystem/ESP/FileMode.h>
#include <FileSystem/ESP/FileAttribute.h>

namespace Common::FileSystem::ESP
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
		/// <summary>
		/// Reads from the file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to read to</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Read(UINTN* bufferSize, void* buffer);
		/// <summary>
		/// Reads from file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to read to</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Read(const UINTN bufferSize, void* buffer);
		/// <summary>
		/// writes to file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write from</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Write(UINTN* bufferSize, void* buffer);
		/// <summary>
		/// writes to file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write from</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Write(const UINTN bufferSize, void* buffer);
		/// <summary>
		/// Gets the position of the file
		/// </summary>
		/// <param name="position">The position of the file</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS GetPosition(UINT64* position);
		/// <summary>
		/// Sets the position of the file
		/// </summary>
		/// <param name="position">The position of the file</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS GetPosition(UINT64 position);
		/// <summary>
		/// Sets the position of the file
		/// </summary>
		/// <param name="position">The position of the file</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS SetPosition(const UINT64 position);
		/// <summary>
		/// Gets the File Info
		/// </summary>
		/// <param name="infoType">The type of info</param>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write to</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS GetInfo(EFI::EFI_GUID* infoType, UINTN* bufferSize, void* buffer);
		/// <summary>
		/// Sets the File Info
		/// </summary>
		/// <param name="infoType">The type of info</param>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write to</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS SetInfo(EFI::EFI_GUID* infoType,const UINTN bufferSize, void* buffer);
		/// <summary>
		/// Flushes the file to media
		/// </summary>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Flush();
		/// <summary>
		/// Closes the file
		/// </summary>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Close();
		/// <summary>
		/// Deletes the file
		/// </summary>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS Delete();
		/// <summary>
		/// Reads the file asynchronously
		/// </summary>
		/// <param name="token">The token to use</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS ReadAsync(EFI::EFI_FILE_IO_TOKEN* token);
		/// <summary>
		/// Writes the file asynchronously
		/// </summary>
		/// <param name="token">The token to use</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS WriteAsync(EFI::EFI_FILE_IO_TOKEN* token);
		/// <summary>
		/// Flushes the file asynchronously
		/// </summary>
		/// <param name="token">The token to use</param>
		/// <returns>EFI_STATUS</returns>
		EFI::EFI_STATUS FlushAsync(EFI::EFI_FILE_IO_TOKEN* token);

		/// <summary>
		/// Reads from the file
		/// </summary>
		/// <param name="buffer">The buffer to read to</param>
		/// <returns>EFI_STATUS</returns>
		template<typename Type>
		EFI::EFI_STATUS Read(Type* buffer)
		{
			return Read(sizeof(Type), buffer);
		};
		/// <summary>
		/// Writes to the file
		/// </summary>
		/// <param name="buffer">The buffer to write from</param>
		/// <returns>EFI_STATUS</returns>
		template<typename Type>
		EFI::EFI_STATUS Write(Type* buffer)
		{
			return Write(sizeof(Type), buffer);
		};

		/// <summary>
		/// Reads from the file
		/// </summary>
		/// <param name="buffer">The buffer to read to</param>
		/// <param name="count">The number of elements to read</param>
		/// <returns>EFI_STATUS</returns>
		template<typename Type>
		EFI::EFI_STATUS Read(Type* buffer, UINTN count)
		{
			return Read(sizeof(Type) * count, buffer);
		};

		/// <summary>
		/// Writes to the file
		/// </summary>
		/// <param name="buffer">The buffer to write from</param>
		/// <param name="count">The number of elements to write</param>
		/// <returns>EFI_STATUS</returns>
		template<typename Type>
		EFI::EFI_STATUS Write(Type* buffer, UINTN count)
		{
			return Write(sizeof(Type) * count, buffer);
		};



		bool operator ==(const FileHandle& right);
		bool operator !=(const FileHandle& right);
		
	protected:
		EFI::EFI_FILE_PROTOCOL* _File;
	};

	constinit const FileHandle Empty_FileHandle = FileHandle();
}