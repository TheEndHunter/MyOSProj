#pragma once
#include <TypeDefs.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>
#include <FileSystem/FileInfo.h>
#include <FileSystem/FileMode.h>
#include <FileSystem/FileAttribute.h>
#include <FileSystem/VolumeInfo.h>
#include <FileSystem/VolumeHandle.h>
#include <FileSystem/FileHandle.h>

#include <Environment/StringComparisonMode.h>

namespace Common::FileSystem::ESP
{
	class ESP_FS_Context
	{
	protected:
		ESP_FS_Context(EFI::EFI_SYSTEM_TABLE* sysTbl, EFI::EFI_HANDLE imgHndl, EFI::EFI_HANDLE devHNDL, EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp);
		ESP_FS_Context() : _sysTable(nullptr),_imgHndl(nullptr), _deviceHandle(nullptr), _fs(nullptr), _root(nullptr), _cwd(nullptr), _isVolumeOpen(false), LastStatus(EFI::EFI_STATUS::SUCCESS)
		{
		}
		
	public:
		static const UINTN QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static ESP_FS_Context GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static ESP_FS_Context GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index, OUT EFI::EFI_STATUS* status);
		static ESP_FS_Context GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, const CHAR16* label, OUT EFI::EFI_STATUS* status, Environment::StringComparisonMode mode = Environment::StringComparisonMode::Compare, Environment::StringCulture culture = Environment::StringCulture::InvariantCulture);
		static const ESP_FS_Context EmptyFS;

		BOOLEAN OpenVolume();
		void CloseVolume();

		BOOLEAN OpenDirectory(const CHAR16* path);
		void CloseDirectory();

		FileHandle OpenFile(FileInfo* fileInfo, FileMode mode, UINT64 attribs);
		FileHandle CreateFile(const CHAR16* name, UINT64 attribs);
		void CloseFile(FileHandle& handle);

		VolumeInfo GetVolumeInfo();
		VolumeLabel GetVolumeLabel();
		
		FileInfo GetDirectoryInfo();
		FileInfo GetFileInfo(const CHAR16* path);

		bool operator ==(const ESP_FS_Context& right)
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

			if (_sysTable != right._sysTable)
				return false;

			return true;
		}

		bool operator !=(const ESP_FS_Context& right)
		{
			return !(*this == right);
		}

		EFI::EFI_STATUS LastStatus;

	private:
		bool _isVolumeOpen;
		EFI::EFI_HANDLE _deviceHandle;
		EFI::EFI_SYSTEM_TABLE* _sysTable;
		EFI::EFI_HANDLE _imgHndl;
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* _fs;
		EFI::EFI_FILE_PROTOCOL* _root;
		EFI::EFI_FILE_PROTOCOL* _cwd;
	};
}

