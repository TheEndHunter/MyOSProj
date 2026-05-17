#include "ESP_FS_Context.h"
#include <Protocols/LoadedImageProtocol.h>
#include <FileSystem/FileAttribute.h>
#include <Protocols/IO/Media/FileInfo.h>
#include <Protocols/IO/Media/FileSystemVolumeLabel.h>
#include <System/Environment/Unicode.h>
#include <System/MemoryManagement/Allocator.h>


Common::Debugging::Debugger* _espDebugger = nullptr;

namespace Common::FileSystem::ESP
{
	void SetESPDebugger(Debugging::Debugger* _debug)
	{
		_espDebugger = _debug;
	}

	const ESP_FS_Context ESP_FS_Context::EmptyFS = ESP_FS_Context();
	const CHAR16* RootPath = u"\\";

	const UINTN ESP_FS_Context::QueryFSCount(Efi::SystemTable* sysTable, Efi::Handle hnd)
	{
		Efi::Handle* handles;
		UINTN fsCount;
		sysTable->BootServices->LocateHandleBuffer(Efi::LocateSearchType::ByProtocol, &Efi::SimpleFileSystemProtocol_GUID, nullptr, &fsCount, &handles);
		sysTable->BootServices->FreePool(handles);
		return fsCount;
	};
	ESP_FS_Context ESP_FS_Context::GetBootFS(Efi::SystemTable* sysTable, Efi::Handle hnd)
	{
		Efi::LoadedImageProtocol* lImg = nullptr;
		Efi::SimpleFileSystemProtocol* fsProtocol = nullptr;

		sysTable->BootServices->OpenProtocol(hnd, &Efi::EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&lImg, hnd, nullptr, Efi::Services::OpenProtocolGetProtocol);

		sysTable->BootServices->OpenProtocol(lImg->DeviceHandle, &Efi::SimpleFileSystemProtocol_GUID, (void**)&fsProtocol, hnd, nullptr, Efi::Services::OpenProtocolGetProtocol);

		sysTable->BootServices->CloseProtocol(hnd, &Efi::EFI_LOADED_IMAGE_PROTOCOL_GUID, hnd, nullptr);

		return ESP_FS_Context(sysTable, hnd,lImg->DeviceHandle, fsProtocol);
	};
	ESP_FS_Context ESP_FS_Context::GetFileSystem(Efi::SystemTable* sysTable, Efi::Handle hnd, UINTN index, OUT Efi::Status* status)
	{
		Efi::Handle* handles;
		UINTN fsCount;
		*status = sysTable->BootServices->LocateHandleBuffer(Efi::LocateSearchType::ByProtocol, &Efi::SimpleFileSystemProtocol_GUID, nullptr, &fsCount, &handles);
		if (*status != Efi::Status::Success)
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
		Efi::Handle FsHndl = handles[index];
		Efi::SimpleFileSystemProtocol* fsProtocol = nullptr;
		*status = sysTable->BootServices->OpenProtocol(FsHndl, &Efi::SimpleFileSystemProtocol_GUID, (void**)&fsProtocol, hnd, nullptr, Efi::Services::OpenProtocolGetProtocol);

		if (*status != Efi::Status::Success)
		{
			delete[fsCount] handles;
			return EmptyFS;
		}


		delete[fsCount] handles;
		return ESP_FS_Context(sysTable, hnd, FsHndl, fsProtocol);
	}
	ESP_FS_Context ESP_FS_Context::GetFileSystem(Efi::SystemTable* sysTable, Efi::Handle hnd, const CHAR16* label, OUT Efi::Status* status, Common::System::Environment::StringComparisonMode mode, Common::System::Environment::StringCulture culture)
	{
		if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(label))
		{
			*status = Efi::Status::InvalidParameter;
			return EmptyFS;
		}

		Efi::Handle* handles;
		UINTN fsCount;

		*status = sysTable->BootServices->LocateHandleBuffer(Efi::LocateSearchType::ByProtocol, &Efi::SimpleFileSystemProtocol_GUID, nullptr, &fsCount, &handles);

		if (*status != Efi::Status::Success)
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
			Efi::Handle fsHndl = handles[fsIndex];
			Efi::SimpleFileSystemProtocol* fsProtocol = nullptr;
			*status = sysTable->BootServices->OpenProtocol(fsHndl, &Efi::SimpleFileSystemProtocol_GUID, (void**)&fsProtocol, hnd, nullptr, Efi::Services::OpenProtocolGetProtocol);

			_espDebugger->PrintInfo(u"Checking File System: ");
			_espDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToString(fsIndex));

			if (*status != Efi::Status::Success)
			{
				continue;
			}

			Efi::FileProtocol* root = nullptr;
			*status = fsProtocol->OpenVolume(fsProtocol, &root);

			if (*status != Efi::Status::Success)
			{
				sysTable->BootServices->CloseProtocol(fsHndl, &Efi::SimpleFileSystemProtocol_GUID, hnd, nullptr);
				continue;
			}

			UINTN volLblSize = 0;
			Efi::FileSystemVolumeLabel* volLbl = nullptr;
			*status = root->GetInfo(root, &Efi::FileSystemVolumeLabel_ID, &volLblSize, (void**)&volLbl);
			
			if (volLblSize < 1)
			{
				*status = Efi::Status::EndOfFile;
				return EmptyFS;
			}
			volLbl = (Efi::FileSystemVolumeLabel*)new UINT8[volLblSize];

			*status = Common::System::MemoryManagement::ToEfiStatus(Common::System::MemoryManagement::Allocator::GetInstance()->LastStatus());

			if (*status != Efi::Status::Success)
			{
				root->Close(root);
				sysTable->BootServices->CloseProtocol(fsHndl, &Efi::SimpleFileSystemProtocol_GUID, hnd, nullptr);
				continue;
			}

			*status = root->GetInfo(root, &Efi::FileSystemVolumeLabel_ID, &volLblSize, (void*)&volLbl->VolumeLabel);

			if (*status != Efi::Status::Success)
			{
				delete[volLblSize] volLbl;
				root->Close(root);
				sysTable->BootServices->CloseProtocol(fsHndl, &Efi::SimpleFileSystemProtocol_GUID, hnd, nullptr);
				continue;
			}

			if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty((CHAR16*)&volLbl->VolumeLabel))
			{
				delete[volLblSize] volLbl;
				root->Close(root);
				sysTable->BootServices->CloseProtocol(fsHndl, &Efi::SimpleFileSystemProtocol_GUID, hnd, nullptr);
				continue;
			}

			_espDebugger->PrintInfo(u"Volume Label: ");
			_espDebugger->PrintInfoLine(volLbl->VolumeLabel);

			BOOLEAN comparison = FALSE;

			switch (mode)
			{
			case Common::System::Environment::Compare:
				comparison = Common::System::Environment::UTF<CHAR16>::Compare(volLbl->VolumeLabel, label, culture);
				break;
			case Common::System::Environment::Contains:
				comparison = Common::System::Environment::UTF<CHAR16>::Contains(volLbl->VolumeLabel, label, culture);
				break;
			case Common::System::Environment::StartsWith:
				comparison = Common::System::Environment::UTF<CHAR16>::StartsWith(volLbl->VolumeLabel, label, culture);
				break;
			case Common::System::Environment::EndsWith:
				comparison = Common::System::Environment::UTF<CHAR16>::EndsWith(volLbl->VolumeLabel, label, culture);
				break;
			}

			delete[volLblSize] volLbl;
			root->Close(root);
			
			if (comparison)
			{
				fsContext = ESP_FS_Context(sysTable, hnd, fsHndl, fsProtocol);
				break;
			}

			sysTable->BootServices->CloseProtocol(fsHndl, &Efi::SimpleFileSystemProtocol_GUID, hnd, nullptr);
			continue;
		}

		delete[fsCount] handles;
		if (fsContext == EmptyFS)
		{
			*status = Efi::Status::NotFound;
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
	};
	BOOLEAN ESP_FS_Context::OpenVolume()
	{
		if (_fs == nullptr)
		{
			if (_espDebugger != nullptr)
			{
				_espDebugger->PrintWarningLine(u"filesystem null");
			}
			LastStatus = Efi::Status::WarnFileSystem;
			return false;
		}

		if (_root == nullptr)
		{
			LastStatus = _fs->OpenVolume(_fs, &_root);

			if (LastStatus != Efi::Status::Success)
			{
				return false;
			}
			_cwd = _root;
			_isVolumeOpen = true;
			if (GetVolumeInfo() == Empty_VolInfo)
			{
				return false;
			}

			if (GetDirectoryInfo() == Empty_DirectoryInfo)
			{
				return false;
			}
		}

		return true;
	};
	BOOLEAN ESP_FS_Context::OpenDirectory(const CHAR16* path)
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
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
			LastStatus = Efi::Status::DeviceError;
			return FALSE;
		}
		
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = Efi::Status::InvalidParameter;
			return FALSE;
		}

		if (Common::System::Environment::UTF<CHAR16>::StartsWith(path,u"\\"))
		{
			_cwd = _root;
			return true;
		}

        LastStatus = _cwd->Open(_cwd, &_cwd, (CHAR16*)path, Efi::FileModes::ReadWrite, (UINT64)Efi::FileAttributes::Directory);

		delete _dirInfo;
		_dirInfo = nullptr;
		GetDirectoryInfo();
		return true;
	};
	void ESP_FS_Context::CloseVolume()
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
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

		_sysTable->BootServices->CloseProtocol(_deviceHandle, &Efi::SimpleFileSystemProtocol_GUID, nullptr, _imgHndl);
	};
	Common::FileSystem::VolumeInfo ESP_FS_Context::GetVolumeInfo()
	{
		if (_root == nullptr) return Empty_VolInfo;

		if(_rootInfo && _rootInfo->operator==(Empty_VolInfo))
		{
			return *_rootInfo;
		}

		UINTN length = 0;

		LastStatus = _root->GetInfo(_root, &Efi::EFI_FILE_SYSTEM_INFO_ID, &length, nullptr);

		if (length < 1)
		{
			_espDebugger->PrintInfo(u"Length is less than 1, returning Empty VolumeInfo");
			return Empty_VolInfo;
		}
		
		Efi::EFI_FILE_SYSTEM_INFO* info = (Efi::EFI_FILE_SYSTEM_INFO*) new UINT8[length]();

		if (info == nullptr)
		{
			_espDebugger->PrintErrorLine(u"Unable To Allocate");
			return Empty_VolInfo;
		}
		
		LastStatus = _root->GetInfo(_root, &Efi::EFI_FILE_SYSTEM_INFO_ID, &length, info);

		if (LastStatus != Efi::Status::Success)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			_espDebugger->PrintErrorLine(u"Unable To Get Intfo");
			return Empty_VolInfo;
		}

		_rootInfo = new VolumeInfo(info);
		delete info;
		return *_rootInfo;
	};
	Common::FileSystem::VolumeLabel ESP_FS_Context::GetVolumeLabel()
	{
		UINTN length = 0;
		Efi::FileSystemVolumeLabel* info = nullptr;
		LastStatus = _root->GetInfo(_root, &Efi::FileSystemVolumeLabel_ID, &length, (void**)&info);

		if (LastStatus != Efi::Status::BufferTooSmall)
		{
			return Empty_VolLabel;
		}

		if (length == 0)
		{
			LastStatus = Efi::Status::BadBufferSize;
			return Empty_VolLabel;
		};

		LastStatus = _sysTable->BootServices->AllocatePool(Efi::MemoryType::LoaderData, length, (void**)&info);
		if (LastStatus != Efi::Status::Success)
		{
			return Empty_VolLabel;
		}

		LastStatus = _root->GetInfo(_root, &Efi::FileSystemVolumeLabel_ID, &length, info);

		if (LastStatus != Efi::Status::Success)
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
		if (_root == nullptr) return Empty_DirectoryInfo;
		if (_cwd == nullptr) return Empty_DirectoryInfo;

		if (_dirInfo != nullptr && *_dirInfo != Empty_DirectoryInfo)
		{
			return *_dirInfo;
		}

		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return Empty_DirectoryInfo;
		}

		if (_cwd == nullptr)
		{
			LastStatus = Efi::Status::DeviceError;
			return Empty_DirectoryInfo;
		}

        Efi::FileInfo* info = nullptr;
		/*Get the size of the FileInfo struct for the file*/
		UINTN length = 0;
        LastStatus = _cwd->GetInfo(_cwd, &Efi::FileInfoId, &length, nullptr);

		/*if the LastStatus is not a Buffer to small error, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::BufferTooSmall)
		{
			return Empty_DirectoryInfo;
		}

		/*if the size is less than 1, return an Empty FileInfo*/
		if (length < 1)
		{
			LastStatus = Efi::Status::BadBufferSize;
			return Empty_DirectoryInfo;
		}

        length += sizeof(Efi::FileInfo);
		/*Allocate a buffer for the FileInfo struct*/
		LastStatus = _sysTable->BootServices->AllocatePool(Efi::MemoryType::LoaderData, length, (void**)&info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			return Empty_DirectoryInfo;
		}

		/*Get the FileInfo struct for the file*/
        LastStatus = _cwd->GetInfo(_cwd, &Efi::FileInfoId, &length, info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_DirectoryInfo;
		}

		/*Create a FileInfo struct from the EFI_FILE_INFO struct*/
		_dirInfo = new DirectoryInfo(info);
		return *_dirInfo;
	}

	DirectoryInfo ESP_FS_Context::GetDirectoryInfo(const CHAR16* path)
	{
		/*Check path to see if it's null or empty, if it is return an empty FileSystem, putting InvalidParameter status into LastStatus Member*/
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = Efi::Status::InvalidParameter;
			return Empty_DirectoryInfo;
		}

		/*Check to see if the FileSystem is null, if it is return an empty FileSystem, putting WARN_FILE_SYSTEM status into LastStatus Member*/
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;	
			return Empty_DirectoryInfo;
		}

		if (_cwd == nullptr)
		{
			LastStatus = Efi::Status::DeviceError;
			return Empty_DirectoryInfo;
		};

		/*open _cwd to the file denoted by the path as readOnly, placing the found files pointer into a _file pointer variable on the stack*/
		Efi::FileProtocol* file = nullptr;
        LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)path, Efi::FileModes::Read, (UINT64)Efi::FileAttributes::ReadOnly);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			return Empty_DirectoryInfo;
		}
		/*Get the size of the FileInfo struct for the file*/
		UINTN length = 0;
        LastStatus = file->GetInfo(file, &Efi::FileInfoId, &length, nullptr);
		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::BufferTooSmall)
		{
			return Empty_DirectoryInfo;
		}

		/*if the size is less than 1, return an Empty FileInfo*/
		if (length < 1)
		{
			LastStatus = Efi::Status::BadBufferSize;
			return Empty_DirectoryInfo;
		}

        length += sizeof(Efi::FileInfo);
		/*Allocate a buffer for the FileInfo struct*/
        Efi::FileInfo* info = nullptr;
		LastStatus = _sysTable->BootServices->AllocatePool(Efi::MemoryType::LoaderData, length, (void**)&info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			return Empty_DirectoryInfo;
		}

		/*Get the FileInfo struct for the file*/
        LastStatus = file->GetInfo(file, &Efi::FileInfoId, &length, info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			LastStatus = _sysTable->BootServices->FreePool(info);
			return Empty_DirectoryInfo;
		}

		file->Close(file);

		/*Create a FileInfo struct from the EFI_FILE_INFO struct*/
		DirectoryInfo dirInfo = DirectoryInfo::Create(info);
		return dirInfo;
	}

	void ESP_FS_Context::CloseDirectory()
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return;
		}

		if (_cwd != nullptr && _cwd != _root)
		{
			_cwd->Close(_cwd);
			_cwd = _root;

			delete _dirInfo;
			_dirInfo = nullptr;
		}
	};

	FileInfo* ESP_FS_Context::EnumerateFiles(OUT UINT64* length)
	{
		if (length == nullptr)
		{
			LastStatus = Efi::Status::InvalidParameter;
			*length = 0;
			return nullptr;
		}

		/* Get All Files In Current Working Directory*/
		UINT64 bufferSize = _dirInfo->PhysicalSize;
		UINT8* buffer = new UINT8[bufferSize]();

		LastStatus = _cwd->Read(_cwd, &bufferSize, buffer);

		if (LastStatus != Efi::Status::Success)
		{
			delete[bufferSize] buffer;
			return nullptr;
		}

	}

	Common::FileSystem::FileInfo ESP_FS_Context::GetFileInfo(const CHAR16* path)
	{
		/*Check path to see if it's null or empty, if it is return an empty FileSystem, putting InvalidParameter status into LastStatus Member*/
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = Efi::Status::InvalidParameter;
			return Empty_FileInfo;
		}

		/*Check to see if the FileSystem is null, if it is return an empty FileSystem, putting WARN_FILE_SYSTEM status into LastStatus Member*/
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return Empty_FileInfo;
		}

		if (_cwd == nullptr)
		{
			LastStatus = Efi::Status::DeviceError;
			return Empty_FileInfo;
		}

		/*open _cwd to the file denoted by the path as readOnly, placing the found files pointer into a _file pointer variable on the stack*/
		Efi::FileProtocol* file = nullptr;
        LastStatus = _cwd->Open(_cwd, &file, path, Efi::FileModes::Read, (UINT64)Efi::FileAttributes::ReadOnly);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			if (_espDebugger != nullptr)
			{
				_espDebugger->PrintCritical(u"Failed to open file: ");
				_espDebugger->PrintCritical(path);
				_espDebugger->PrintCritical(u" : ");
				_espDebugger->PrintCriticalLine(Common::System::Environment::UTF<CHAR16>::ToString(LastStatus));
				_espDebugger->WaitForKey();
			}
			return Empty_FileInfo;
		}
		/*Get the size of the FileInfo struct for the file*/
		UINTN length = 0;
        LastStatus = file->GetInfo(file, &Efi::FileInfoId, &length, nullptr);
		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::BufferTooSmall)
		{
			if (_espDebugger != nullptr)
			{
				_espDebugger->PrintCritical(u"Failed to get file Info Alloc: ");
				_espDebugger->PrintCriticalLine(Common::System::Environment::UTF<CHAR16>::ToString(LastStatus));
			}
			return Empty_FileInfo;
		}

		/*if the size is less than 1, return an Empty FileInfo*/
		if (length < 1)
		{
			LastStatus = Efi::Status::BadBufferSize;
			return Empty_FileInfo;
		}

        length += sizeof(Efi::FileInfo);
		/*Allocate a buffer for the FileInfo struct*/
        Efi::FileInfo* info = (Efi::FileInfo*)new UINT8[length]();

		/*Get the FileInfo struct for the file*/
        LastStatus = file->GetInfo(file, &Efi::FileInfoId, &length, info);

		/*if the LastStatus is Not a success, return an Empty FileInfo*/
		if (LastStatus != Efi::Status::Success)
		{
			_espDebugger->PrintCritical(u"Failed to get file Info: ");
			_espDebugger->PrintCriticalLine(Common::System::Environment::UTF<CHAR16>::ToString(LastStatus));
			delete info;
			delete file;
			return Empty_FileInfo;
		}
		file->Close(file);
		delete file;

		/*Create a FileInfo struct from the EFI_FILE_INFO struct*/
        Common::FileSystem::FileInfo fileInfo = Common::FileSystem::FileInfo::Create(info);
		return fileInfo;
	}

	FileHandle ESP_FS_Context::OpenFile(FileInfo* fileInfo, FileMode mode, UINT64 attribs)
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return Empty_FileHandle;
		}

		if (fileInfo == nullptr)
		{
			LastStatus = Efi::Status::InvalidParameter;
			return Empty_FileHandle;
		}

		if (Common::System::Environment::UTF<CHAR16>::IsNullOrEmpty(fileInfo->FileName))
		{
			LastStatus = Efi::Status::InvalidParameter;
			return Empty_FileHandle;
		}

		/* Check to see if FileMode::Create Flag is set, if it is, set an InvalidParameter and return an Empty File Handle*/
		if ((mode & FileMode::Create) == FileMode::Create)
		{
			LastStatus = Efi::Status::InvalidParameter;
			return Empty_FileHandle;
		}

		Efi::FileProtocol* file = nullptr;
        LastStatus = _cwd->Open(_cwd, &file, fileInfo->FileName, (Efi::FileModes)mode, attribs);

		if (LastStatus != Efi::Status::Success)
		{
			if (_espDebugger != nullptr)
			{
				switch (LastStatus)
				{
				case Efi::Status::Success:
					_espDebugger->PrintCriticalLine(u"File opened successfully.");
					break;
					case Efi::Status::NotFound:
					_espDebugger->PrintCriticalLine(u"File Not Found");
					break;
					case Efi::Status::NoMedia:
					_espDebugger->PrintCriticalLine(u"Media Not Found");
					break;
					case Efi::Status::MediaChanged:
					_espDebugger->PrintCriticalLine(u"Media Changed");
					break;
					case Efi::Status::DeviceError:
					_espDebugger->PrintCriticalLine(u"Device Error");
					break;
					case Efi::Status::VolumeCorrupted:
					_espDebugger->PrintCriticalLine(u"Volume Corrupted");
					break;
					case Efi::Status::WriteProtected:
					_espDebugger->PrintCriticalLine(u"Write Protected");
					break;
				case Efi::Status::AccessDenied:
					_espDebugger->PrintCriticalLine(u"Access Denied");
					break;
				case Efi::Status::OutOfResources:
					_espDebugger->PrintCriticalLine(u"Out of Resources");
					break;
					case Efi::Status::VolumeFull:
					_espDebugger->PrintCriticalLine(u"Volume Full");
					break;
				}
			}
			return Empty_FileHandle;
		}

		if (file == nullptr)
		{
			return Empty_FileHandle;
		}
		/*print all file info and file pointer below using _debugger*/
        if (_espDebugger != nullptr)
        {
        _espDebugger->PrintInfoLine(u"File opened successfully.");
        _espDebugger->PrintInfo(u"File pointer: 0x");
        _espDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToHex(file));
        _espDebugger->PrintInfo(u"FileName: ");
        _espDebugger->PrintInfoLine(fileInfo->FileName);
        _espDebugger->PrintInfo(u"FileSize: ");
        _espDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToString(fileInfo->FileSize));
        _espDebugger->PrintInfo(u"PhysicalSize: ");
        _espDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToString(fileInfo->PhysicalSize));
        _espDebugger->PrintInfo(u"Attribute: ");
        _espDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToString(fileInfo->Attribute));
        }

		return FileHandle::Create(file, fileInfo, mode, attribs);
	};

	FileHandle ESP_FS_Context::CreateFile(const CHAR16* name, UINT64 attribs)
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return Empty_FileHandle;
		}

		Efi::FileProtocol* file;

        LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)name, Efi::FileModes::Create, attribs);

		/* Get EFI_FILE_INFO for FileHandle */
		UINTN length = 0;
        Efi::FileInfo* info = nullptr;
        LastStatus = file->GetInfo(file, &Efi::FileInfoId, &length, (void**)&info);
		LastStatus = _sysTable->BootServices->AllocatePool(Efi::MemoryType::LoaderData, length, (void**)&info);
        LastStatus = file->GetInfo(file, &Efi::FileInfoId, &length, info);
        Common::FileSystem::FileInfo i = Common::FileSystem::FileInfo::Create(info);
		return FileHandle::Create(file,&i, FileMode::Create, attribs);
	}

	BOOLEAN ESP_FS_Context::DeleteFile(FileHandle* handle)
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return FALSE;
		}

		if (handle == nullptr)
		{
			LastStatus = Efi::Status::InvalidParameter;
			return FALSE;
		}

		if (handle->_File == nullptr)
		{
			LastStatus = Efi::Status::InvalidParameter;
			return FALSE;
		}

		LastStatus = handle->_File->Delete(handle->_File);
		if (LastStatus != Efi::Status::Success)
		{
			return FALSE;
		}

		return TRUE;
	}

	void ESP_FS_Context::CloseFile(FileHandle& handle)
	{
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return;
		}

		if (handle == Empty_FileHandle)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return;
		}

		LastStatus = handle.Close();

		if (LastStatus != Efi::Status::Success)
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

		Efi::FileProtocol* parent = nullptr;
		LastStatus = _cwd->Close(_cwd);

		while (_cwd != _root)
		{
			LastStatus = _cwd->Close(_cwd);

			if (LastStatus != Efi::Status::Success)
			{
				return FALSE;
			}
		}
		
		_cwd = _root;
		return TRUE;
	}

	BOOLEAN ESP_FS_Context::CheckAttribute(const CHAR16* path, UINT64 attrib)
	{
		auto dir = GetDirectoryInfo(path);

		BOOLEAN result = (dir.Attribute & attrib) == attrib;

		return result;
	}

	BOOLEAN ESP_FS_Context::IsDirectory(const CHAR16* path)
	{
		return CheckAttribute(path,FileAttribute::Directory);
	}

	BOOLEAN ESP_FS_Context::IsFile(const CHAR16* path)
	{
		return !CheckAttribute(path, FileAttribute::Directory | FileAttribute::Archive);
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
		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
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
			LastStatus = Efi::Status::DeviceError;
			return FALSE;
		}

		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = Efi::Status::InvalidParameter;
			return FALSE;
		}
		Efi::FileProtocol* file = nullptr;
        LastStatus = _cwd->Open(_cwd, &file, (CHAR16*)path, Efi::FileModes::ReadWrite, (UINT64)Efi::FileAttributes::Directory);

		if (LastStatus == Efi::Status::NotFound || LastStatus == Efi::Status::VolumeCorrupted)
		{
			return false;
		}

		return true;
	}

	/// <summary>
	/// Checks if a file exists at the specified path.
	/// </summary>
	/// <param name="path">path to esp file</param>
	/// <returns>True if the the file system is able to open the file, otherwise false</returns>
	BOOLEAN ESP_FS_Context::FileExists(const CHAR16* path)
	{
		if(path == nullptr)
		{
			LastStatus = Efi::Status::InvalidParameter;
			if (_espDebugger != nullptr)
			{
				_espDebugger->PrintCriticalLine(u"Path is null, cannot check if file exists.");
			}
			return FALSE;
		}

		if (_fs == nullptr)
		{
			LastStatus = Efi::Status::WarnFileSystem;
			return false;
		}
		if (!_isVolumeOpen || !OpenVolume())
		{
			return FALSE;
		}
		if (_cwd == nullptr)
		{
			LastStatus = Efi::Status::DeviceError;
			return FALSE;
		}
		if (Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path))
		{
			LastStatus = Efi::Status::InvalidParameter;
			return FALSE;
		}
		Efi::FileProtocol* file = nullptr;
        LastStatus = _cwd->Open(_cwd, &file, const_cast<CHAR16*>(path), Efi::FileModes::Read, 0);
		BOOLEAN ls = LastStatus == Efi::Status::Success;

		_espDebugger->PrintDebugLine(Common::System::Environment::UTF<CHAR16>::ToString(ls));

		if (file != nullptr)
		{
			file->Close(file);
			delete file;
			file = nullptr;
		}
		return ls;
	}
}