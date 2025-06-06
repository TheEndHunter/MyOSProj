#include "ESP_FS_Context.h"
#include <Protocols/EFI_LOADED_IMAGE_PROTOCOL.h>
#include <FileSystem/FileAttribute.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>
#include <Protocols/IO/Media/EFI_FILE_SYSTEM_VOLUME_LABEL.h>
#include <System/Environment/Unicode.h>

namespace Common::FileSystem::ESP
{
	const ESP_FS_Context ESP_FS_Context::EmptyFS = ESP_FS_Context();

	const CHAR16* RootPath = u"\\";

	ESP_FS_Context::ESP_FS_Context(EFI::EFI_SYSTEM_TABLE* sysTbl, EFI::EFI_HANDLE imgHndl, EFI::EFI_HANDLE devHNDL, EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp)
		: _sysTable(sysTbl), _deviceHandle(devHNDL),_imgHndl(imgHndl), _fs(fsp), _root(nullptr), _cwd(nullptr), _isVolumeOpen(false), LastStatus(EFI::EFI_STATUS::SUCCESS)
	{
	};

	const UINTN ESP_FS_Context::QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
	{
		EFI::EFI_HANDLE* handles;
		UINTN fsCount;
		sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);
		sysTable->BootServices->FreePool(handles);
		return fsCount;
	};

	ESP_FS_Context ESP_FS_Context::GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd)
	{
		EFI::EFI_LOADED_IMAGE_PROTOCOL* lImg = nullptr;
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;

		sysTable->BootServices->OpenProtocol(hnd, &EFI::EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&lImg, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

		sysTable->BootServices->OpenProtocol(lImg->DeviceHandle, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

		sysTable->BootServices->CloseProtocol(hnd, &EFI::EFI_LOADED_IMAGE_PROTOCOL_GUID, hnd, nullptr);

		return ESP_FS_Context(sysTable, hnd,lImg->DeviceHandle, fsProtocol);
	};

	ESP_FS_Context ESP_FS_Context::GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index, OUT EFI::EFI_STATUS* status)
	{
		EFI::EFI_HANDLE* handles;
		UINTN fsCount;
		*status = sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);
		if (*status != EFI::EFI_STATUS::SUCCESS)
		{
			return EmptyFS;
		}

		if (index >= fsCount)
		{
			if (fsCount > 0)
			{
				sysTable->BootServices->FreePool(handles);
			}
			return EmptyFS;
		};
		EFI::EFI_HANDLE FsHndl = handles[index];
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;
		*status = sysTable->BootServices->OpenProtocol(FsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

		if (*status != EFI::EFI_STATUS::SUCCESS)
		{
			sysTable->BootServices->FreePool(handles);
			return EmptyFS;
		}

		sysTable->BootServices->FreePool(handles);
		return ESP_FS_Context(sysTable, hnd, FsHndl, fsProtocol);
	}

	ESP_FS_Context ESP_FS_Context::GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, const CHAR16* label, OUT EFI::EFI_STATUS* status, System::Environment::StringComparisonMode mode, System::Environment::StringCulture culture)
	{
		if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(label))
		{
			*status = EFI::EFI_STATUS::INVALID_PARAMETER;
			return EmptyFS;
		}

		EFI::EFI_HANDLE* handles;
		UINTN fsCount;
		*status = sysTable->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, &fsCount, &handles);

		if (*status != EFI::EFI_STATUS::SUCCESS)
		{
			return EmptyFS;
		}

		if (fsCount == 0)
		{
			return EmptyFS;
		};

		ESP_FS_Context fsContext = EmptyFS;
		for (UINTN fsIndex = 0; fsIndex < fsCount; fsIndex++)
		{
			EFI::EFI_HANDLE fsHndl = handles[fsIndex];
			EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsProtocol = nullptr;
			*status = sysTable->BootServices->OpenProtocol(fsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&fsProtocol, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

			if (*status != EFI::EFI_STATUS::SUCCESS)
			{
				continue;
			}

			EFI::EFI_FILE_PROTOCOL* root = nullptr;
			*status = fsProtocol->OpenVolume(fsProtocol, &root);

			if (*status != EFI::EFI_STATUS::SUCCESS)
			{
				sysTable->BootServices->CloseProtocol(fsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, hnd, nullptr);
				continue;
			}

			UINTN volLblSize = 0;
			EFI::EFI_FILE_SYSTEM_VOLUME_LABEL* volLbl = nullptr;
			*status = root->GetInfo(root, &EFI::EFI_FILE_SYSTEM_VOLUME_LABEL_ID, &volLblSize, (void**)&volLbl);
			if (volLblSize < 1)
			{
				*status = EFI::EFI_STATUS::END_OF_FILE;
				return EmptyFS;
			}
			*status = sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, volLblSize, (void**)&volLbl);

			if (*status != EFI::EFI_STATUS::SUCCESS)
			{
				root->Close(root);
				sysTable->BootServices->CloseProtocol(fsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, hnd, nullptr);
				continue;
			}

			*status = root->GetInfo(root, &EFI::EFI_FILE_SYSTEM_VOLUME_LABEL_ID, &volLblSize, (void*)&volLbl->VolumeLabel);

			if (*status != EFI::EFI_STATUS::SUCCESS)
			{
				sysTable->BootServices->FreePool(volLbl);
				root->Close(root);
				sysTable->BootServices->CloseProtocol(fsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, hnd, nullptr);
				continue;
			}

			if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty((CHAR16*)&volLbl->VolumeLabel))
			{
				sysTable->BootServices->FreePool(volLbl);
				root->Close(root);
				sysTable->BootServices->CloseProtocol(fsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, hnd, nullptr);
				continue;
			}

			BOOLEAN comparison = FALSE;

			switch (mode)
			{
			case Common::System::Environment::Compare:
				comparison = Common::System::Environment::UTF<CHAR16>::Compare((const CHAR16*)&volLbl->VolumeLabel, label, culture);
				break;
			case Common::System::Environment::Contains:
				comparison = Common::System::Environment::UTF<CHAR16>::Contains((const CHAR16*)&volLbl->VolumeLabel, label, culture);
				break;
			case Common::System::Environment::StartsWith:
				comparison = Common::System::Environment::UTF<CHAR16>::StartsWith((const CHAR16*)&volLbl->VolumeLabel, label, culture);
				break;
			case Common::System::Environment::EndsWith:
				comparison = Common::System::Environment::UTF<CHAR16>::EndsWith((const CHAR16*)&volLbl->VolumeLabel, label, culture);
				break;
			}

			if (comparison)
			{
				sysTable->BootServices->FreePool(volLbl);
				root->Close(root);
				fsContext = ESP_FS_Context(sysTable,hnd,fsHndl, fsProtocol);
				break;
			}

			sysTable->BootServices->FreePool(volLbl);
			root->Close(root);
			sysTable->BootServices->CloseProtocol(fsHndl, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, hnd, nullptr);
			continue;
		}

		sysTable->BootServices->FreePool(handles);

		if (fsContext == EmptyFS)
		{
			*status = EFI::EFI_STATUS::NOT_FOUND;
		}

		return fsContext;
	}
	CHAR16* ESP_FS_Context::GetParentDirectory(CHAR16* path)
	{
		return nullptr;
	}

	CHAR16* ESP_FS_Context::GetFileName(CHAR16* path)
	{
		return nullptr;
	}
	;

	BOOLEAN ESP_FS_Context::OpenVolume()
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return false;
		}

		if (_root == nullptr)
		{
			LastStatus = _fs->OpenVolume(_fs, &_root);
			if (LastStatus != EFI::EFI_STATUS::SUCCESS)
			{
				return false;
			}
		}

		_cwd = _root;
		_isVolumeOpen = true;

		return true;
	};

	BOOLEAN ESP_FS_Context::OpenDirectory(const CHAR16* path)
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return false;
		}

		if (!_isVolumeOpen)
		{
			if (!OpenVolume())
			{
				return FALSE;
			}
		}

		if (_cwd == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::DEVICE_ERROR;
			return FALSE;
		}
		
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return FALSE;
		}

		if (Common::System::Environment::UTF<CHAR16>::StartsWith(path,u"\\"))
		{
			_cwd = _root;
			return true;
		}

		LastStatus = _cwd->Open(_cwd, &_cwd, (CHAR16*)path, EFI::EFI_FILE_MODES::ReadWrite, EFI::EFI_FILE_ATTRIBUTES::Directory);
		return true;
	};

	void ESP_FS_Context::CloseVolume()
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return;
		}

		if (_cwd != nullptr)
		{
			LastStatus = _cwd->Close(_cwd);
			_cwd = nullptr;
		}

		if (_root != nullptr)
		{
			LastStatus = _root->Close(_root);
			_root = nullptr;
			_isVolumeOpen = false;
		}

		_sysTable->BootServices->CloseProtocol(_deviceHandle, &EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, nullptr, _imgHndl);
	};

	Common::FileSystem::VolumeInfo ESP_FS_Context::GetVolumeInfo()
	{
		UINTN length = 0;
		LastStatus = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_INFO_ID, &length, nullptr);

		if (length < 1)
		{
			return Empty_VolInfo;
		};

		EFI::EFI_FILE_SYSTEM_INFO* info = nullptr;
		LastStatus = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, (void**)&info);
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_VolInfo;
		}

		LastStatus = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_INFO_ID, &length, info);

		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_VolInfo;
		}

		VolumeInfo volumeInfo = VolumeInfo::Create(info);
		return volumeInfo;
	};

	Common::FileSystem::VolumeLabel ESP_FS_Context::GetVolumeLabel()
	{
		UINTN length = 0;
		EFI::EFI_FILE_SYSTEM_VOLUME_LABEL* info = nullptr;
		LastStatus = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_VOLUME_LABEL_ID, &length, (void**)&info);

		if (LastStatus != EFI::EFI_STATUS::BUFFER_TOO_SMALL)
		{
			return Empty_VolLabel;
		}

		if (length == 0)
		{
			LastStatus = EFI::EFI_STATUS::BAD_BUFFER_SIZE;
			return Empty_VolLabel;
		};

		LastStatus = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, (void**)&info);
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_VolLabel;
		}

		LastStatus = _root->GetInfo(_root, &EFI::EFI_FILE_SYSTEM_VOLUME_LABEL_ID, &length, info);

		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_VolLabel;
		}

		VolumeLabel volLabel = VolumeLabel(*info);
		LastStatus = _sysTable->BootServices->FreePool(info);

		return volLabel;
	}

	DirectoryInfo ESP_FS_Context::GetDirectoryInfo()
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return Empty_DirectoryInfo;
		}

		if (_cwd == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::DEVICE_ERROR;
			return Empty_DirectoryInfo;
		};

		/*Get the size of the FileInfo struct for the file*/
		UINTN length = 0;
		LastStatus = _cwd->GetInfo(_cwd, &EFI::EFI_FILE_INFO_ID, &length, nullptr);

		/*if the LastStatus is not a Buffer to small error, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::BUFFER_TOO_SMALL)
		{
			return Empty_DirectoryInfo;
		}

		/*if the size is less than 1, return an Empty FileInfo*/
		if (length < 1)
		{
			LastStatus = EFI::EFI_STATUS::BAD_BUFFER_SIZE;
			return Empty_DirectoryInfo;
		}

		length += sizeof(EFI::EFI_FILE_INFO);
		/*Allocate a buffer for the FileInfo struct*/
		EFI::EFI_FILE_INFO* info = nullptr;
		LastStatus = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, (void**)&info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_DirectoryInfo;
		}

		/*Get the FileInfo struct for the file*/
		LastStatus = _cwd->GetInfo(_cwd, &EFI::EFI_FILE_INFO_ID, &length, info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_DirectoryInfo;
		}

		/*Create a FileInfo struct from the EFI_FILE_INFO struct*/
		DirectoryInfo dirInfo = DirectoryInfo::Create(info);
		return dirInfo;
	}

	DirectoryInfo ESP_FS_Context::GetDirectoryInfo(const CHAR16* path)
	{
		/*Check path to see if it's null or empty, if it is return an empty FileSystem, putting INVALID_PARAMETER status into LastStatus Member*/
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return Empty_DirectoryInfo;
		}

		/*Check to see if the FileSystem is null, if it is return an empty FileSystem, putting WARN_FILE_SYSTEM status into LastStatus Member*/
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return Empty_DirectoryInfo;
		}

		if (_cwd == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::DEVICE_ERROR;
			return Empty_DirectoryInfo;
		};

		/*open _cwd to the file denoted by the path as readOnly, placing the found files pointer into a _file pointer variable on the stack*/
		EFI::EFI_FILE_PROTOCOL* file = nullptr;
		LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)path, EFI::EFI_FILE_MODES::Read, EFI::EFI_FILE_ATTRIBUTES::ReadOnly);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_DirectoryInfo;
		}
		/*Get the size of the FileInfo struct for the file*/
		UINTN length = 0;
		LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &length, nullptr);
		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::BUFFER_TOO_SMALL)
		{
			return Empty_DirectoryInfo;
		}

		/*if the size is less than 1, return an Empty FileInfo*/
		if (length < 1)
		{
			LastStatus = EFI::EFI_STATUS::BAD_BUFFER_SIZE;
			return Empty_DirectoryInfo;
		}

		length += sizeof(EFI::EFI_FILE_INFO);
		/*Allocate a buffer for the FileInfo struct*/
		EFI::EFI_FILE_INFO* info = nullptr;
		LastStatus = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, (void**)&info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_DirectoryInfo;
		}

		/*Get the FileInfo struct for the file*/
		LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &length, info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_DirectoryInfo;
		}

		/*Create a FileInfo struct from the EFI_FILE_INFO struct*/
		DirectoryInfo dirInfo = DirectoryInfo::Create(info);
		return dirInfo;
	}

	void ESP_FS_Context::CloseDirectory()
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

	Common::FileSystem::FileInfo ESP_FS_Context::GetFileInfo(const CHAR16* path)
	{
		/*Check path to see if it's null or empty, if it is return an empty FileSystem, putting INVALID_PARAMETER status into LastStatus Member*/
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return Empty_FileInfo;
		}

		/*Check to see if the FileSystem is null, if it is return an empty FileSystem, putting WARN_FILE_SYSTEM status into LastStatus Member*/
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return Empty_FileInfo;
		}

		if (_cwd == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::DEVICE_ERROR;
			return Empty_FileInfo;
		};

		/*open _cwd to the file denoted by the path as readOnly, placing the found files pointer into a _file pointer variable on the stack*/
		EFI::EFI_FILE_PROTOCOL* file = nullptr;
		LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)path, EFI::EFI_FILE_MODES::Read, EFI::EFI_FILE_ATTRIBUTES::ReadOnly);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_FileInfo;
		}
		/*Get the size of the FileInfo struct for the file*/
		UINTN length = 0;
		LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &length, nullptr);
		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::BUFFER_TOO_SMALL)
		{
			return Empty_FileInfo;
		}

		/*if the size is less than 1, return an Empty FileInfo*/
		if (length < 1)
		{
			LastStatus = EFI::EFI_STATUS::BAD_BUFFER_SIZE;
			return Empty_FileInfo;
		}

		length += sizeof(EFI::EFI_FILE_INFO);
		/*Allocate a buffer for the FileInfo struct*/
		EFI::EFI_FILE_INFO* info = nullptr;
		LastStatus = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, (void**)&info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_FileInfo;
		}

		/*Get the FileInfo struct for the file*/
		LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &length, info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_FileInfo;
		}

		/*Create a FileInfo struct from the EFI_FILE_INFO struct*/
		FileInfo fileInfo = FileInfo::Create(info);
		return fileInfo;
	}

	FileHandle ESP_FS_Context::OpenFile(FileInfo* fileInfo, FileMode mode, UINT64 attribs)
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return Empty_FileHandle;
		}

		if (fileInfo == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return Empty_FileHandle;
		}

		if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(fileInfo->FileName))
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return Empty_FileHandle;
		}

		/* Check to see if FileMode::Create Flag is set, if it is, set an INVALID_PARAMETER and return an Empty File Handle*/

		if ((mode & FileMode::Create) == FileMode::Create)
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return Empty_FileHandle;
		}

		EFI::EFI_FILE_PROTOCOL* file = nullptr;
		LastStatus = _cwd->Open(_cwd, &file, fileInfo->FileName, (EFI::EFI_FILE_MODES)mode,attribs);


		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return Empty_FileHandle;
		}

		return FileHandle::Create(file, fileInfo, mode, attribs);
	};

	FileHandle ESP_FS_Context::CreateFile(const CHAR16* name, UINT64 attribs)
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return Empty_FileHandle;
		}

		EFI::EFI_FILE_PROTOCOL* file;

		LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)name, EFI::EFI_FILE_MODES::Create, attribs);

		/* Get EFI_FILE_INFO for FileHandle */
		UINTN length = 0;
		EFI::EFI_FILE_INFO* info = nullptr;
		LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &length, (void**)&info);
		LastStatus = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, (void**)&info);
		LastStatus = file->GetInfo(file, &EFI::EFI_FILE_INFO_ID, &length, info);
		FileInfo i = FileInfo::Create(info);
		return FileHandle::Create(file,&i, FileMode::Create, attribs);
	}

	BOOLEAN ESP_FS_Context::DeleteFile(FileHandle* handle)
	{
		if (_fs == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::WARN_FILE_SYSTEM;
			return FALSE;
		}

		if (handle == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return FALSE;
		}

		if (handle->_File == nullptr)
		{
			LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return FALSE;
		}

		LastStatus = handle->_File->Delete(handle->_File);
		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return FALSE;
		}

		return TRUE;
	}

	void ESP_FS_Context::CloseFile(FileHandle& handle)
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

		LastStatus = handle.Close();

		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return;
		}
		LastStatus = _sysTable->BootServices->FreePool(handle._File);
	}
	BOOLEAN ESP_FS_Context::IsRootDirectory()
	{
		if (_cwd == _root)
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOLEAN ESP_FS_Context::ReturnToRootDirectory()
	{
		if (_cwd == _root)
		{
			return TRUE;
		}

		EFI::EFI_FILE_PROTOCOL* parent = nullptr;
		LastStatus = _cwd->Close(_cwd);

		while (_cwd != _root)
		{
			LastStatus = _cwd->Close(_cwd);

			if (LastStatus != EFI::EFI_STATUS::SUCCESS)
			{
				return FALSE;
			}
		}
		
		_cwd = _root;
		return TRUE;
	}

	BOOLEAN ESP_FS_Context::IsDirectory(const CHAR16* path)
	{
		return false;
	}

	BOOLEAN ESP_FS_Context::IsFile(const CHAR16* path)
	{
		return false;
	}

	CHAR16* ESP_FS_Context::GetFullPath(const CHAR16* path)
	{
		return nullptr;
	}

	CHAR16* ESP_FS_Context::GetRelativePath(const CHAR16* path)
	{
		return nullptr;
	}

	BOOLEAN ESP_FS_Context::DirectoryExists(const CHAR16* path)
	{
		return BOOLEAN();
	}

	BOOLEAN ESP_FS_Context::FileExists(const CHAR16* path)
	{
		return BOOLEAN();
	}
}