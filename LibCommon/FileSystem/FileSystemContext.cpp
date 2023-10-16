#include "FileSystemContext.h"
#include <Protocols/EFI_LOADED_IMAGE_PROTOCOL.h>

namespace Common::FileSystem
{
    const FileSystemContext FileSystemContext::EmptyFS = FileSystemContext();

    FileSystemContext::FileSystemContext(EFI::EFI_HANDLE hnd,EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp)
        : _devhnd(hnd), _fs(fsp), _root(nullptr), _cwd(nullptr), _isVolumeOpen(false)
    {
    }
    
    const UINTN FileSystemContext::QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
    {
        EFI::EFI_HANDLE* handles;
        UINTN fsCount;
        sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);
        sysTable->BootServices->FreePool(handles);
        return fsCount;
    }

    FileSystemContext FileSystemContext::GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
    {
        EFI::EFI_LOADED_IMAGE_PROTOCOL* lImg;
        EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol;

        sysTable->BootServices->OpenProtocol(hnd, &EFI::EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&lImg,hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        sysTable->BootServices->OpenProtocol(lImg->DeviceHandle, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        sysTable->BootServices->CloseProtocol(hnd, &EFI::EFI_LOADED_IMAGE_PROTOCOL_GUID, hnd, nullptr);

        return FileSystemContext(lImg->DeviceHandle,fsProtocol);
    }

    FileSystemContext FileSystemContext::GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index)
    {
		EFI::EFI_HANDLE* handles;
		UINTN fsCount;
		sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);
        if (index >= fsCount)
        {
            sysTable->BootServices->FreePool(handles);
            return FileSystemContext(nullptr, nullptr);
        };
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol;

		sysTable->BootServices->OpenProtocol(handles[index], &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);
		sysTable->BootServices->FreePool(handles);
		return FileSystemContext(handles[index],fsProtocol);
    }

    void FileSystemContext::OpenVolume()
    {
        if(_fs == nullptr )
		{
			return;
		}
        if (_root == nullptr)
        {
            _fs->OpenVolume(_fs, &_root);
            _cwd = _root;
            _isVolumeOpen = true;
        }
    }

    void FileSystemContext::CloseVolume()
    {
        if (_fs == nullptr)
        {
            return;
        }

        if (_cwd != nullptr && _cwd != _root)
        {
            _cwd->Close(_cwd);
        }

        if (_root != nullptr)
		{
			_root->Close(_root);
			_root = nullptr;
            _isVolumeOpen = false;
		}
    }

    Common::FileSystem::VolumeInfo FileSystemContext::GetVolumeInfo(EFI::EFI_SYSTEM_TABLE* sysTable)
    {
        UINTN size = 0;
        _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_INFO_ID, &size, nullptr);
        EFI::EFI_FILE_SYSTEM_INFO* info;
        sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**) &info);
        EFI::EFI_STATUS s = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_INFO_ID, &size, info);
        if (s != EFI::EFI_STATUS::SUCCESS)
        {
			sysTable->BootServices->FreePool(info);
            return VolumeInfo::Create(nullptr);
		}
        VolumeInfo vinfo = VolumeInfo::Create(info);
        sysTable->BootServices->FreePool(info);
        return vinfo;
    }

    Common::FileSystem::FileInfo FileSystemContext::GetDirectoryInfo(EFI::EFI_SYSTEM_TABLE* sysTable)
    {
        UINTN size = 0;
        _cwd->GetInfo(_cwd, &EFI::EFI_FILE_INFO_ID, &size, nullptr);
        EFI::EFI_FILE_INFO* info;
        sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**)&info);
        EFI::EFI_STATUS s = _cwd->GetInfo(_cwd, &EFI::EFI_FILE_INFO_ID, &size, info);
        if (s != EFI::EFI_STATUS::SUCCESS)
        {
            sysTable->BootServices->FreePool(info);
            return FileInfo::Create(nullptr);
        }
        FileInfo finfo = FileInfo::Create(info);
        sysTable->BootServices->FreePool(info);
        return finfo;
    }

    Common::FileSystem::FileInfo FileSystemContext::GetFileInfo(EFI::EFI_SYSTEM_TABLE* sysTable, const CHAR16* path)
    {
        UINTN size = 0;
        EFI::EFI_FILE_PROTOCOL *file;
        _cwd->Open(_cwd, &file, (CHAR16*)path, EFI::EFI_FILE_MODES::READ, EFI::EFI_FILE_ATTRIBUTES::READ_ONLY);
        file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &size, nullptr);
        EFI::EFI_FILE_INFO* info;
        sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, (void**)&info);
        EFI::EFI_STATUS s = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &size, info);
        file->Close(file);
        if (s != EFI::EFI_STATUS::SUCCESS)
        {
            sysTable->BootServices->FreePool(info);
            return FileInfo::Create(nullptr);
        }
        FileInfo finfo = FileInfo::Create(info);
        sysTable->BootServices->FreePool(info);
        return finfo;
    }


    void FileSystemContext::CloseContext(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
    {
        if (_fs == nullptr)
        {
            return;
        }

        if (_isVolumeOpen)
        {
            CloseVolume();
        }
        sysTable->BootServices->CloseProtocol(_devhnd, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,hnd, nullptr);
    }
}