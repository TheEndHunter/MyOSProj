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
#include <FileSystem/DirectoryInfo.h>
#include <System/Environment/StringComparisonMode.h>

namespace Common::FileSystem::ESP
{
	void SetESPDebugger(Debugging::Debugger* _debug);

	class ESP_FS_Context
	{
	protected:
		ESP_FS_Context(EFI::EFI_SYSTEM_TABLE* sysTbl, EFI::EFI_HANDLE imgHndl, EFI::EFI_HANDLE devHNDL, EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp) : LastStatus(EFI::EFI_STATUS::NOT_READY), _isVolumeOpen(FALSE), _deviceHandle(devHNDL), _sysTable(sysTbl), _imgHndl(imgHndl), _fs(fsp), _root(nullptr), _cwd(nullptr), _rootInfo(nullptr), _dirInfo(nullptr)
		{
		}

		ESP_FS_Context() : LastStatus(EFI::EFI_STATUS::NOT_READY), _isVolumeOpen(FALSE), _deviceHandle(nullptr), _sysTable(nullptr), _imgHndl(nullptr), _fs(nullptr), _root(nullptr), _cwd(nullptr), _rootInfo(nullptr), _dirInfo(nullptr)
        {  
        }
		
	public:
		static const CHAR16 DirectorySeparatorChar = '\\';

		static const UINTN QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static ESP_FS_Context GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static ESP_FS_Context GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index, OUT EFI::EFI_STATUS* status);
		static ESP_FS_Context GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, const CHAR16* label, OUT EFI::EFI_STATUS* status, Common::System::Environment::StringComparisonMode mode = Common::System::Environment::StringComparisonMode::Compare, Common::System::Environment::StringCulture culture = Common::System::Environment::StringCulture::InvariantCulture);
		static const ESP_FS_Context EmptyFS;

		static CHAR16* GetParentDirectory(CHAR16* path);
		static CHAR16* GetFileName(CHAR16* path);
		BOOLEAN OpenVolume();
		void CloseVolume();
		BOOLEAN OpenDirectory(const CHAR16* path);
		void CloseDirectory();
		FileHandle OpenFile(FileInfo* fileInfo, FileMode mode, UINT64 attribs);
		FileHandle CreateFile(const CHAR16* name, UINT64 attribs);
		BOOLEAN DeleteFile(FileHandle* handle);
		void CloseFile(FileHandle& handle);
		BOOLEAN IsRootDirectory();
		BOOLEAN ReturnToRootDirectory();
		BOOLEAN CheckAttribute(const CHAR16* path, UINT64 attrib);
		BOOLEAN IsDirectory(const CHAR16* path);
		BOOLEAN IsFile(const CHAR16* path);
		CHAR16* GetFullPath(const CHAR16* path);
		CHAR16* GetRelativePath(const CHAR16* path);
		BOOLEAN DirectoryExists(const CHAR16* path);
		BOOLEAN FileExists(const CHAR16* path);
		VolumeInfo GetVolumeInfo();
		VolumeLabel GetVolumeLabel();
		DirectoryInfo GetDirectoryInfo();
		DirectoryInfo GetDirectoryInfo(const CHAR16* path);

		FileInfo* EnumerateFiles(OUT UINT64* length);
		FileInfo GetFileInfo(const CHAR16* path);
		BOOLEAN operator ==(const ESP_FS_Context& right)
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
		BOOLEAN operator !=(const ESP_FS_Context& right)
		{
			return !(*this == right);
		}

		EFI::EFI_STATUS LastStatus;
	private:
		BOOLEAN _isVolumeOpen;
		EFI::EFI_HANDLE _deviceHandle;
		EFI::EFI_SYSTEM_TABLE* _sysTable;
		EFI::EFI_HANDLE _imgHndl;
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* _fs;
		EFI::EFI_FILE_PROTOCOL* _root;
		EFI::EFI_FILE_PROTOCOL* _cwd;
		VolumeInfo* _rootInfo;
		DirectoryInfo* _dirInfo;
	};
}

