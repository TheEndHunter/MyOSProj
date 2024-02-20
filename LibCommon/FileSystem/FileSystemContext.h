#pragma once
#include <TypeDefs.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>
#include "VolumeInfo.h"
#include "FileInfo.h"
#include "FileHandle.h"
#include "FileMode.h"
#include "FileAttribute.h"

namespace Common::FileSystem
{
	
	class FileSystemContext
	{
	protected:
		FileSystemContext(EFI::EFI_HANDLE hnd, EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp);
		const FileSystemContext()
		{
			_deviceHandle = nullptr;
			_fs = nullptr;
			_root = nullptr;
			_cwd = nullptr;
			_isVolumeOpen = false;
		}
		
	public:
		static const UINTN QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static FileSystemContext GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static FileSystemContext GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index);
		static const FileSystemContext EmptyFS;

		BOOLEAN OpenVolume();
		void CloseVolume();

		BOOLEAN OpenDirectory(const CHAR16* path);
		BOOLEAN OpenRoot();
		void CloseDirectory();

		FileHandle OpenFile(EFI::EFI_SYSTEM_TABLE* sysTable, FileInfo& fileInfo, FileMode mode, FileAttribute attribs);
		FileHandle CreateFile(EFI::EFI_SYSTEM_TABLE* sysTable, const CHAR16* name, FileAttribute attribs);
		void CloseFile(EFI::EFI_SYSTEM_TABLE* sysTable, FileHandle& handle);

		VolumeInfo GetVolumeInfo(EFI::EFI_SYSTEM_TABLE* sysTable);

		FileInfo GetDirectoryInfo(EFI::EFI_SYSTEM_TABLE* sysTable);
		FileInfo GetFileInfo(EFI::EFI_SYSTEM_TABLE* sysTable, const CHAR16* path);

		void CloseContext(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);

		bool operator ==(const FileSystemContext& right)
		{
			/*Compare all members for equality, if one fails return false, otherwise return true*/

			if (_deviceHandle != right._deviceHandle)
				return false;

			if (_fs != right._fs)
				return false;

            if (_root != right._root)
				return false;

			if (_cwd != right._cwd)
				return false;

			if (_isVolumeOpen != right._isVolumeOpen)
				return false;

			return true;
		}

		bool operator !=(const FileSystemContext& right)
		{
			return !(*this == right);
		}

		EFI::EFI_STATUS LastStatus;

	private:
		bool _isVolumeOpen;
		EFI::EFI_HANDLE _deviceHandle;
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* _fs;
		EFI::EFI_FILE_PROTOCOL* _root;
		EFI::EFI_FILE_PROTOCOL* _cwd;
	};
}

