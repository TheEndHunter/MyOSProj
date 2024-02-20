#include "FileSystemContext.h"
#include <Protocols/EFI_LOADED_IMAGE_PROTOCOL.h>
#include "FileAttribute.h"


namespace Common::FileSystem
{
    const FileSystemContext FileSystemContext::EmptyFS = FileSystemContext();
    const CHAR16* RootPath = u"\\";

    FileSystemContext::FileSystemContext(EFI::EFI_HANDLE hnd, EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp)
        : _deviceHandle(hnd), _fs(fsp), _root(nullptr), _cwd(nullptr), _isVolumeOpen(false), LastStatus(EFI::EFI_STATUS::SUCCESS)
    {
    };
    
    const UINTN FileSystemContext::QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
    {
        EFI::EFI_HANDLE* handles;
        UINTN fsCount;
        sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);
        sysTable->BootServices->FreePool(handles);
        return fsCount;
    };

    FileSystemContext FileSystemContext::GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
    {
        EFI::EFI_LOADED_IMAGE_PROTOCOL* lImg = nullptr;
        EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;

        sysTable->BootServices->OpenProtocol(hnd, &EFI::EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&lImg, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        sysTable->BootServices->OpenProtocol(lImg->DeviceHandle, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        sysTable->BootServices->CloseProtocol(hnd, &EFI::EFI_LOADED_IMAGE_PROTOCOL_GUID, hnd, nullptr);

        return FileSystemContext(lImg->DeviceHandle, fsProtocol);
    };

    FileSystemContext FileSystemContext::GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index)
    {
        EFI::EFI_HANDLE* handles;
        UINTN fsCount;
        sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);
        if (index >= fsCount)
        {
            sysTable->BootServices->FreePool(handles);
            return EmptyFS;
        };
        EFI::EFI_HANDLE FsHndl = handles[index];
        sysTable->BootServices->FreePool(handles);

        EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;
        sysTable->BootServices->OpenProtocol(FsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        return FileSystemContext(FsHndl, fsProtocol);
    };

    BOOLEAN FileSystemContext::OpenVolume()
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
            return false;
        }
        if (_root == nullptr)
        {
            LastStatus = _fs->OpenVolume(_fs, &_root);
            _cwd = _root;
            _isVolumeOpen = true;
        }
        return true;
    };

    BOOLEAN FileSystemContext::OpenDirectory(const CHAR16* path)
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return false;
		}

		EFI::EFI_FILE_PROTOCOL* dir;
        LastStatus = _cwd->Open(_cwd, &dir, (CHAR16*)path, EFI::EFI_FILE_MODES::READWRITE, EFI::EFI_FILE_ATTRIBUTES::DIRECTORY);
		_cwd = dir;
		return true;
	};

    BOOLEAN FileSystemContext::OpenRoot()
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
            return false;
        }

        if (_isVolumeOpen)
        {
            if (_root == nullptr)
            {
                LastStatus = _fs->OpenVolume(_fs, &_root);
				_cwd = _root;
            }

            if (_cwd != _root)
            {
                LastStatus = _cwd->Close(_cwd);
			    _cwd = _root;
			}
			return true;
		}

        EFI::EFI_FILE_PROTOCOL* dir;
        LastStatus = _cwd->Open(_cwd, &dir, (CHAR16*)&RootPath, EFI::EFI_FILE_MODES::READWRITE, EFI::EFI_FILE_ATTRIBUTES::DIRECTORY);
        _cwd = _root = dir;
        return true;
    };

    void FileSystemContext::CloseVolume()
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
            return;
        }

        if (_cwd != nullptr && _cwd != _root)
        {
            _cwd->Close(_cwd);
        }

        if (_root != nullptr)
        {
            LastStatus = _root->Close(_root);
            _root = nullptr;
            _isVolumeOpen = false;
        }
    };

    Common::FileSystem::VolumeInfo FileSystemContext::GetVolumeInfo(EFI::EFI_SYSTEM_TABLE* sysTable)
    {
        UINTN size = 0;
        LastStatus = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_INFO_ID, &size, nullptr);
        EFI::EFI_FILE_SYSTEM_INFO* info = nullptr;
        LastStatus = sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**)&info);
        LastStatus = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_INFO_ID, &size, info);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            LastStatus = sysTable->BootServices->FreePool(info);
            return VolumeInfo::Create(nullptr);
        }
        VolumeInfo volumeInfo = VolumeInfo::Create(info);
        LastStatus = sysTable->BootServices->FreePool(info);
        return volumeInfo;
    };

    Common::FileSystem::FileInfo FileSystemContext::GetDirectoryInfo(EFI::EFI_SYSTEM_TABLE* sysTable)
    {
        UINTN size = 0;
        LastStatus = _cwd->GetInfo(_cwd, &EFI::EFI_FILE_INFO_ID, &size, nullptr);
        EFI::EFI_FILE_INFO* info = nullptr;
        LastStatus = sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**)&info);
        LastStatus = _cwd->GetInfo(_cwd, &EFI::EFI_FILE_INFO_ID, &size, info);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            LastStatus = sysTable->BootServices->FreePool(info);
            return FileInfo::Create(nullptr);
        }
        FileInfo finfo = FileInfo::Create(info);
        LastStatus = sysTable->BootServices->FreePool(info);
        return finfo;
    }

    void FileSystemContext::CloseDirectory()
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return;
		}

        if (_cwd != nullptr && _cwd != _root)
        {
			_cwd->Close(_cwd);
			_cwd = _root;
		}
	};

    Common::FileSystem::FileInfo FileSystemContext::GetFileInfo(EFI::EFI_SYSTEM_TABLE* sysTable, const CHAR16* path)
    {
        if (path == nullptr)
        {
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return Empty_FileInfo;
		}

        UINTN size = 0;
        EFI::EFI_FILE_PROTOCOL* file;
        LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)path, EFI::EFI_FILE_MODES::READ, EFI::EFI_FILE_ATTRIBUTES::READ_ONLY);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
			return Empty_FileInfo;
		}
        LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &size, nullptr);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            return Empty_FileInfo;
        }

        EFI::EFI_FILE_INFO* info = nullptr;
        
        LastStatus = sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**)&info);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            return Empty_FileInfo;
        }
        LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &size, info);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            LastStatus = sysTable->BootServices->FreePool(info);
            return Empty_FileInfo;
        }
        file->Close(file);
        if (LastStatus != EFI::EFI_STATUS::SUCCESS)
        {
            LastStatus = sysTable->BootServices->FreePool(info);
            return Empty_FileInfo;
        }
        FileInfo finfo = FileInfo::Create(info);
        LastStatus = sysTable->BootServices->FreePool(info);
        return finfo;
    }

    FileHandle FileSystemContext::OpenFile(EFI::EFI_SYSTEM_TABLE* sysTable, FileInfo& fileInfo,FileMode mode, FileAttribute attribs)
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return Empty_FileHandle;
		}
        /* Check to make sure we aren't trying to use OpenFile in FileMode::Create as this is not correct usage */
        if ((mode & FileMode::Create) == FileMode::Create)
		{
			LastStatus = EFI::EFI_STATUS::ACCESS_DENIED;
			return Empty_FileHandle;
		}

        EFI::EFI_FILE_PROTOCOL* file;

        LastStatus = _cwd->Open(_cwd, &file, fileInfo.FileName, (EFI::EFI_FILE_MODES)mode, (EFI::EFI_FILE_ATTRIBUTES)attribs);

        return FileHandle::Create(file,fileInfo,mode,attribs);
	};

    FileHandle FileSystemContext::CreateFile(EFI::EFI_SYSTEM_TABLE* sysTable, const CHAR16* name, FileAttribute attribs)
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
            return Empty_FileHandle;
        }
        
        EFI::EFI_FILE_PROTOCOL* file;
        
        LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)name, EFI::EFI_FILE_MODES::CREATE, (EFI::EFI_FILE_ATTRIBUTES)attribs);

        /* Get EFI_FILE_INFO for FileHandle */
        UINTN size = 0;
        EFI::EFI_FILE_INFO* info = nullptr;
        LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &size, (void**)&info);
        LastStatus = sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**)&info);
        LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &size, info);
        return FileHandle::Create(file,FileInfo::Create(info), FileMode::Create, attribs);
    }

    void FileSystemContext::CloseFile(EFI::EFI_SYSTEM_TABLE* sysTable, FileHandle& handle)
    {
        if (_fs == nullptr)
		{ 
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
            return;
        }

        if (handle == Empty_FileHandle)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return;
		}

        LastStatus = sysTable->BootServices->FreePool(handle._File);
    }

    void FileSystemContext::CloseContext(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
    {
        if (_fs == nullptr)
        {
            LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
            return;
        }

        if (_isVolumeOpen)
        {
            CloseVolume();
        }
        LastStatus = sysTable->BootServices->CloseProtocol(_deviceHandle, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, hnd, nullptr);
    };


}