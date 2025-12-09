#include "FileHandle.h"

namespace Common::FileSystem
{
	Debugging::Debugger* _FSDebugger = nullptr;

	FileHandle::FileHandle(EFI::EFI_FILE_PROTOCOL* file, FileInfo* i, FileMode mode, UINT64 attribs)
	{
		/*Check if the file is null, if it is, return an error*/
		if (file == nullptr)
		{
			if (_FSDebugger != nullptr)
			{
				_FSDebugger->PrintErrorLine(u"FileHandle::FileHandle: file == nullptr");
			}
			return;
		}
		if (i == nullptr)
		{
			if (_FSDebugger != nullptr)
			{
				_FSDebugger->PrintErrorLine(u"FileHandle::FileHandle: i == nullptr");
			}
			return;
		}

		if (i->Size == 0)
		{
			if (_FSDebugger != nullptr)
			{
				_FSDebugger->PrintErrorLine(u"FileHandle::FileHandle: i->Size == 0");
			}
			return;
		}

		Mode = mode;
		Size = i->Size;
		Info = *i;
		_File = file;
		Attributes = attribs;
	}

	FileHandle FileHandle::Create(EFI::EFI_FILE_PROTOCOL* file, FileInfo* i, FileMode mode, UINT64 attribs)
	{
		return FileHandle(file, i,mode,attribs);
	}

	BOOLEAN FileHandle::operator==(const FileHandle& right)
	{
		/*Compare all members for equality, if one fails return false, otherwise return true*/

		return (_File == right._File) &&
			(Mode == right.Mode) &&
			(Size == right.Size) &&
			(Info == right.Info) &&
			(Attributes == right.Attributes);
	}

	BOOLEAN FileHandle::operator!=(const FileHandle& right)
	{
		return !(*this == right);
	};

	EFI::EFI_STATUS FileHandle::Read(UINTN* bufferSize, void* buffer)
	{
		return _File->Read(_File, bufferSize, buffer);
	}

	EFI::EFI_STATUS FileHandle::Read(const UINTN bufferSize, void* buffer)
	{
		return _File->Read(_File, (UINTN*)&bufferSize, buffer);
	}

	EFI::EFI_STATUS FileHandle::Write(UINTN* bufferSize, void* buffer)
	{
		return _File->Write(_File, bufferSize, buffer);
	}

	EFI::EFI_STATUS FileHandle::Write(const UINTN bufferSize, void* buffer)
	{
		return _File->Write(_File, (UINTN*)&bufferSize, buffer);
	}

	EFI::EFI_STATUS FileHandle::GetPosition(UINT64* position)
	{
		return _File->GetPosition(_File, position);
	}

	EFI::EFI_STATUS FileHandle::SetPosition(const UINT64 position)
	{
		return _File->SetPosition(_File, position);
	}

	EFI::EFI_STATUS FileHandle::GetPosition(UINT64 position)
	{
		return _File->GetPosition(_File, &position);
	}

	EFI::EFI_STATUS FileHandle::GetInfo(EFI::EFI_GUID* infoType, UINTN* bufferSize, void* buffer)
	{
		return _File->GetInfo(_File, infoType, bufferSize, buffer);
	}

	EFI::EFI_STATUS FileHandle::SetInfo(EFI::EFI_GUID* infoType, UINTN bufferSize, void* buffer)
	{
		return _File->SetInfo(_File, infoType, bufferSize, buffer);
	}

	EFI::EFI_STATUS FileHandle::Flush()
	{
		return _File->Flush(_File);	
	}

	EFI::EFI_STATUS FileHandle::Close()
	{
		return _File->Close(_File);
	}

	EFI::EFI_STATUS FileHandle::Delete()
	{
		return _File->Delete(_File);
	}

	EFI::EFI_STATUS FileHandle::ReadAsync(EFI::EFI_FILE_IO_TOKEN* token)
	{
		return _File->ReadEx(_File, token);
	}

	EFI::EFI_STATUS FileHandle::WriteAsync(EFI::EFI_FILE_IO_TOKEN* token)
	{
		return _File->WriteEx(_File, token);
	}

	EFI::EFI_STATUS FileHandle::FlushAsync(EFI::EFI_FILE_IO_TOKEN* token)
	{
		return _File->FlushEx(_File, token);
	}

	void SetFileSystemDebugger(Debugging::Debugger* debugger)
	{
		_FSDebugger = debugger;
	}
}
