#include "FileHandle.h"
#include "VolumeHandle.h"

namespace Common::FileSystem
{
	VolumeHandle VolumeHandle::Create(Efi::FileProtocol* file, VolumeInfo i, FileMode mode, FileAttribute attribs)
	{
		return VolumeHandle(file, i, mode, attribs);
	}

	BOOLEAN VolumeHandle::operator==(const VolumeHandle& right)
	{
		return Info == right.Info && Size == right.Size && Mode == right.Mode && Attributes == right.Attributes;
	}

	BOOLEAN VolumeHandle::operator!=(const VolumeHandle& right)
	{
		return !(*this == right);
	}

	Efi::Status VolumeHandle::Read(UINTN* bufferSize, void* buffer)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Read) != FileMode::Read)
				return Efi::Status::AccessDenied;
		}

		return File->Read(File, bufferSize, buffer);
	}

	Efi::Status VolumeHandle::Write(UINTN* bufferSize, void* buffer)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return Efi::Status::AccessDenied;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return Efi::Status::AccessDenied;
		}

		return File->Write(File, bufferSize, buffer);
	}

	Efi::Status VolumeHandle::GetPosition(UINT64* position)
	{
		return File->GetPosition(File, position);
	}

	Efi::Status VolumeHandle::SetPosition(UINT64 position)
	{
		return File->SetPosition(File, position);
	}

	Efi::Status VolumeHandle::GetInfo(Efi::Guid* infoType, UINTN* bufferSize, void* buffer)
	{
		return File->GetInfo(File, infoType, bufferSize, buffer);
	}

	Efi::Status VolumeHandle::SetInfo(Efi::Guid* infoType, UINTN bufferSize, void* buffer)
	{
		return File->SetInfo(File, infoType, bufferSize, buffer);
	}

	Efi::Status VolumeHandle::Flush()
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return Efi::Status::AccessDenied;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return Efi::Status::AccessDenied;

		}
		return File->Flush(File);
	}

	Efi::Status VolumeHandle::Close()
	{
		return File->Close(File);
	}

	Efi::Status VolumeHandle::Delete()
	{
		return File->Delete(File);
	}

    Efi::Status VolumeHandle::ReadAsync(Efi::FileIOToken* token)
	{
		/*Check enum flag to see if we have the right FileMode bit set*/
		if ((Mode & FileMode::Read) != FileMode::Read)
			return Efi::Status::AccessDenied;

		return File->ReadEx(File, token);
	}

    Efi::Status VolumeHandle::WriteAsync(Efi::FileIOToken* token)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return Efi::Status::AccessDenied;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return Efi::Status::AccessDenied;
		}
		return File->WriteEx(File, token);
	}

    Efi::Status VolumeHandle::FlushAsync(Efi::FileIOToken* token)
	{
		if ((Mode & FileMode::Create) != FileMode::Create)
		{
			if (Attributes & FileAttribute::ReadOnly)
				return Efi::Status::AccessDenied;

			/*Check enum flag to see if we have the right FileMode bit set*/
			if ((Mode & FileMode::Write) != FileMode::Write)
				return Efi::Status::AccessDenied;
		}
		return File->FlushEx(File, token);
	}
}
