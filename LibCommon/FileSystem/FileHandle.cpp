#include "FileHandle.h"

namespace Common::FileSystem
{
	Debugging::Debugger* _FSDebugger = nullptr;

	FileHandle::FileHandle(Efi::FileProtocol* file, FileInfo* i, FileMode mode, UINT64 attribs)
	{
		// Initialize members to safe defaults so early returns don't leave members uninitialized
		Mode = FileMode::Create;
		Attributes = 0;
		Info = FileInfo();
		Size = 0;
		_File = nullptr;

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

	FileHandle FileHandle::Create(Efi::FileProtocol* file, FileInfo* i, FileMode mode, UINT64 attribs)
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

	Efi::Status FileHandle::Read(UINTN* bufferSize, void* buffer)
	{
		return _File->Read(_File, bufferSize, buffer);
	}

	Efi::Status FileHandle::Read(const UINTN bufferSize, void* buffer)
	{
		return _File->Read(_File, (UINTN*)&bufferSize, buffer);
	}

	Efi::Status FileHandle::Write(UINTN* bufferSize, void* buffer)
	{
		return _File->Write(_File, bufferSize, buffer);
	}

	Efi::Status FileHandle::Write(const UINTN bufferSize, void* buffer)
	{
		return _File->Write(_File, (UINTN*)&bufferSize, buffer);
	}

	Efi::Status FileHandle::GetPosition(UINT64* position)
	{
		return _File->GetPosition(_File, position);
	}

	Efi::Status FileHandle::SetPosition(const UINT64 position)
	{
		return _File->SetPosition(_File, position);
	}

	Efi::Status FileHandle::GetPosition(UINT64 position)
	{
		return _File->GetPosition(_File, &position);
	}

	Efi::Status FileHandle::GetInfo(Efi::Guid* infoType, UINTN* bufferSize, void* buffer)
	{
		return _File->GetInfo(_File, infoType, bufferSize, buffer);
	}

	Efi::Status FileHandle::SetInfo(Efi::Guid* infoType, UINTN bufferSize, void* buffer)
	{
		return _File->SetInfo(_File, infoType, bufferSize, buffer);
	}

	Efi::Status FileHandle::Flush()
	{
		return _File->Flush(_File);	
	}

	Efi::Status FileHandle::Close()
	{
		return _File->Close(_File);
	}

	Efi::Status FileHandle::Delete()
	{
		return _File->Delete(_File);
	}

    Efi::Status FileHandle::ReadAsync(Efi::FileIOToken* token)
	{
		return _File->ReadEx(_File, token);
	}

    Efi::Status FileHandle::WriteAsync(Efi::FileIOToken* token)
	{
		return _File->WriteEx(_File, token);
	}

    Efi::Status FileHandle::FlushAsync(Efi::FileIOToken* token)
	{
		return _File->FlushEx(_File, token);
	}

	void SetFileSystemDebugger(Debugging::Debugger* debugger)
	{
		_FSDebugger = debugger;
	}
}
