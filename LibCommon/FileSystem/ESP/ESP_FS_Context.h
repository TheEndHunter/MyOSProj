#pragma once
#include <TypeDefs.h>
#include <Status.h>
#include <SystemTable.h>
#include <Protocols/IO/Media/SimpleFileSystemProtocol.h>
#include <Protocols/Time/Time.h>
#include <Protocols/IO/Media/FileInfo.h>
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
		ESP_FS_Context(Efi::SystemTable* sysTbl, Efi::Handle imgHndl, Efi::Handle devHNDL, Efi::SimpleFileSystemProtocol* fsp) : LastStatus(Efi::Status::NotReady), _isVolumeOpen(FALSE), _deviceHandle(devHNDL), _sysTable(sysTbl), _imgHndl(imgHndl), _fs(fsp), _root(nullptr), _cwd(nullptr), _rootInfo(nullptr), _dirInfo(nullptr)
		{
		}

		ESP_FS_Context() : LastStatus(Efi::Status::NotReady), _isVolumeOpen(FALSE), _deviceHandle(nullptr), _sysTable(nullptr), _imgHndl(nullptr), _fs(nullptr), _root(nullptr), _cwd(nullptr), _rootInfo(nullptr), _dirInfo(nullptr)
        {  
        }
		
	public:
		static const CHAR16 DirectorySeparatorChar = '\\';

		static const UINTN QueryFSCount(Efi::SystemTable* sysTable, Efi::Handle hnd);
		static ESP_FS_Context GetBootFS(Efi::SystemTable* sysTable, Efi::Handle hnd);
		static ESP_FS_Context GetFileSystem(Efi::SystemTable* sysTable, Efi::Handle hnd, UINTN index, OUT Efi::Status* status);
		static ESP_FS_Context GetFileSystem(Efi::SystemTable* sysTable, Efi::Handle hnd, const CHAR16* label, OUT Efi::Status* status, Common::System::Environment::StringComparisonMode mode = Common::System::Environment::StringComparisonMode::Compare, Common::System::Environment::StringCulture culture = Common::System::Environment::StringCulture::InvariantCulture);
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

		Efi::Status LastStatus;
	private:
		BOOLEAN _isVolumeOpen;
		Efi::Handle _deviceHandle;
		Efi::SystemTable* _sysTable;
		Efi::Handle _imgHndl;
		Efi::SimpleFileSystemProtocol* _fs;
		Efi::FileProtocol* _root;
		Efi::FileProtocol* _cwd;
		VolumeInfo* _rootInfo;
		DirectoryInfo* _dirInfo;
	};
}

