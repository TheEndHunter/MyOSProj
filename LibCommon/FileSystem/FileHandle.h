#pragma once
#include <TypeDefs.h>
#include <SystemTable.h>
#include <Protocols/IO/Media/SimpleFileSystemProtocol.h>
#include <Status.h>
#include <FileSystem/FileInfo.h>
#include <FileSystem/FileMode.h>
#include <FileSystem/FileAttribute.h>
#include <Debugging/Debugger.h>

namespace Common::FileSystem
{
	namespace ESP
	{
		class ESP_FS_Context;
	}

	void SetFileSystemDebugger(Debugging::Debugger* debugger);

	ALIGN(8) struct FileHandle
	{
		friend class ESP::ESP_FS_Context;
	protected:
		FileHandle(Efi::FileProtocol* file, FileInfo* i, FileMode mode, UINT64 attribs);
	public:
		constexpr FileHandle() : Mode(FileMode::Create), Attributes(0),Info(), Size(0),_File(nullptr){} // Default constructor

		explicit FileHandle(FileHandle* handle) : Mode(handle->Mode), Attributes(handle->Attributes), Info(handle->Info), Size(handle->Info.Size), _File(handle->_File) {};
		FileHandle(const FileHandle& handle) : Mode(handle.Mode), Attributes(handle.Attributes), Info(handle.Info), Size(handle.Info.Size), _File(handle._File) {};

		static FileHandle Create(Efi::FileProtocol* file, FileInfo* i, FileMode mode, UINT64 attribs);
		FileMode Mode;
		UINT64 Attributes;
		FileInfo Info;
		UINT64 Size;
		BOOLEAN IsValid() { return _File != nullptr; };
		Efi::FileProtocol* GetFileEFIHandle() {
			return _File;
		};
		/*
		*  Below are all the functions needed to read, write, seek, close and delete, etc.
		*/
		/// <summary>
		/// Reads from the file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to read to</param>
		/// <returns>Status</returns>
		Efi::Status Read(UINTN* bufferSize, void* buffer);
		/// <summary>
		/// Reads from file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to read to</param>
		/// <returns>Status</returns>
		Efi::Status Read(const UINTN bufferSize, void* buffer);
		/// <summary>
		/// writes to file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write from</param>
		/// <returns>Status</returns>
		Efi::Status Write(UINTN* bufferSize, void* buffer);
		/// <summary>
		/// writes to file
		/// </summary>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write from</param>
		/// <returns>Status</returns>
		Efi::Status Write(const UINTN bufferSize, void* buffer);
		/// <summary>
		/// Gets the position of the file
		/// </summary>
		/// <param name="position">The position of the file</param>
		/// <returns>Status</returns>
		Efi::Status GetPosition(UINT64* position);
		/// <summary>
		/// Sets the position of the file
		/// </summary>
		/// <param name="position">The position of the file</param>
		/// <returns>Status</returns>
		Efi::Status GetPosition(UINT64 position);
		/// <summary>
		/// Sets the position of the file
		/// </summary>
		/// <param name="position">The position of the file</param>
		/// <returns>Status</returns>
		Efi::Status SetPosition(const UINT64 position);
		/// <summary>
		/// Gets the File Info
		/// </summary>
		/// <param name="infoType">The type of info</param>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write to</param>
		/// <returns>Status</returns>
		Efi::Status GetInfo(Efi::Guid* infoType, UINTN* bufferSize, void* buffer);
		/// <summary>
		/// Sets the File Info
		/// </summary>
		/// <param name="infoType">The type of info</param>
		/// <param name="bufferSize">The size of the buffer</param>
		/// <param name="buffer">The buffer to write to</param>
		/// <returns>Status</returns>
		Efi::Status SetInfo(Efi::Guid* infoType,const UINTN bufferSize, void* buffer);
		/// <summary>
		/// Flushes the file to media
		/// </summary>
		/// <returns>Status</returns>
		Efi::Status Flush();
		/// <summary>
		/// Closes the file
		/// </summary>
		/// <returns>Status</returns>
		Efi::Status Close();
		/// <summary>
		/// Deletes the file
		/// </summary>
		/// <returns>Status</returns>
		Efi::Status Delete();
		/// <summary>
		/// Reads the file asynchronously
		/// </summary>
		/// <param name="token">The token to use</param>
		/// <returns>Status</returns>
        Efi::Status ReadAsync(Efi::FileIOToken* token);
		/// <summary>
		/// Writes the file asynchronously
		/// </summary>
		/// <param name="token">The token to use</param>
		/// <returns>Status</returns>
        Efi::Status WriteAsync(Efi::FileIOToken* token);
		/// <summary>
		/// Flushes the file asynchronously
		/// </summary>
		/// <param name="token">The token to use</param>
		/// <returns>Status</returns>
        Efi::Status FlushAsync(Efi::FileIOToken* token);

		/// <summary>
		/// Reads from the file
		/// </summary>
		/// <param name="buffer">The buffer to read to</param>
		/// <returns>Status</returns>
		template<typename Type>
		Efi::Status Read(Type* buffer)
		{
			return Read(sizeof(Type), buffer);
		};
		/// <summary>
		/// Writes to the file
		/// </summary>
		/// <param name="buffer">The buffer to write from</param>
		/// <returns>Status</returns>
		template<typename Type>
		Efi::Status Write(Type* buffer)
		{
			return Write(sizeof(Type), buffer);
		};

		/// <summary>
		/// Reads from the file
		/// </summary>
		/// <param name="buffer">The buffer to read to</param>
		/// <param name="count">The number of elements to read</param>
		/// <returns>Status</returns>
		template<typename Type>
		Efi::Status Read(Type* buffer, UINTN count)
		{
			return Read(sizeof(Type) * count, buffer);
		};

		/// <summary>
		/// Writes to the file
		/// </summary>
		/// <param name="buffer">The buffer to write from</param>
		/// <param name="count">The number of elements to write</param>
		/// <returns>Status</returns>
		template<typename Type>
		Efi::Status Write(Type* buffer, UINTN count)
		{
			return Write(sizeof(Type) * count, buffer);
		};



		BOOLEAN operator ==(const FileHandle& right);
		BOOLEAN operator !=(const FileHandle& right);
		
	protected:
		Efi::FileProtocol* _File;
	};

	constinit const FileHandle Empty_FileHandle = FileHandle();
}