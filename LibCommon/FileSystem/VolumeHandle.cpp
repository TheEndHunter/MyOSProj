#include "FileHandle.h"
#include "VolumeHandle.h"

namespace Common::FileSystem
{
	VolumeHandle VolumeHandle::Create(EFI::EFI_FILE_PROTOCOL* file, VolumeInfo i, FileMode mode, FileAttribute attribs)
	{
		return VolumeHandle(file, i, mode, attribs);
	}

	bool VolumeHandle::operator==(const VolumeHandle& right)
	{
		/*Compare all members for equality, if one fails return false, otherwise return true*/
		if (Info != right.Info)
			return false;
		if (Size != right.Size)
			return false;
		if( Mode != right.Mode)
			return false;	
		if (Attributes != right.Attributes)
			return false;

		return true;
	}

	bool VolumeHandle::operator!=(const VolumeHandle& right)
	{
		return !(*this == right);
	}

	EFI::EFI_STATUS VolumeHandle::Read(UINTN* bufferSize, void* buffer)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Read) != FileMode::Read)
				return EFI::EFI_STATUS::ACCESS_DENIED;
		}

		return _File->Read(_File, bufferSize, buffer);
	}

	EFI::EFI_STATUS VolumeHandle::Write(UINTN* bufferSize, void* buffer)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return EFI::EFI_STATUS::ACCESS_DENIED;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return EFI::EFI_STATUS::ACCESS_DENIED;
		}

		return _File->Write(_File, bufferSize, buffer);
	}

	EFI::EFI_STATUS VolumeHandle::GetPosition(UINT64* position)
	{
		return _File->GetPosition(_File, position);
	}

	EFI::EFI_STATUS VolumeHandle::SetPosition(UINT64 position)
	{
		return _File->SetPosition(_File, position);
	}

	EFI::EFI_STATUS VolumeHandle::GetInfo(EFI::EFI_GUID* infoType, UINTN* bufferSize, void* buffer)
	{
		return _File->GetInfo(_File, infoType, bufferSize, buffer);
	}

	EFI::EFI_STATUS VolumeHandle::SetInfo(EFI::EFI_GUID* infoType, UINTN bufferSize, void* buffer)
	{
		return _File->SetInfo(_File, infoType, bufferSize, buffer);
	}

	EFI::EFI_STATUS VolumeHandle::Flush()
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return EFI::EFI_STATUS::ACCESS_DENIED;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return EFI::EFI_STATUS::ACCESS_DENIED;

		}
		return _File->Flush(_File);
	}

	EFI::EFI_STATUS VolumeHandle::Close()
	{
		return _File->Close(_File);
	}

	EFI::EFI_STATUS VolumeHandle::Delete()
	{
		return _File->Delete(_File);
	}

	EFI::EFI_STATUS VolumeHandle::ReadAsync(EFI::EFI_FILE_IO_TOKEN* token)
	{
		/*Check enum flag to see if we have the right FileMode bit set*/
		if ((Mode & FileMode::Read) != FileMode::Read)
			return EFI::EFI_STATUS::ACCESS_DENIED;

		return _File->ReadEx(_File, token);
	}

	EFI::EFI_STATUS VolumeHandle::WriteAsync(EFI::EFI_FILE_IO_TOKEN* token)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return EFI::EFI_STATUS::ACCESS_DENIED;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return EFI::EFI_STATUS::ACCESS_DENIED;
		}
		return _File->WriteEx(_File, token);
	}

	EFI::EFI_STATUS VolumeHandle::FlushAsync(EFI::EFI_FILE_IO_TOKEN* token)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return EFI::EFI_STATUS::ACCESS_DENIED;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return EFI::EFI_STATUS::ACCESS_DENIED;
		}
		return _File->FlushEx(_File, token);
	}
}
