#pragma once
#include <TypeDefs.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>

namespace Common::FileSystem
{
	struct  VolumeInfo
	{
		CHAR16* LABEL;
	};
	class FileSystemContext
	{
	protected:
		FileSystemContext(EFI::EFI_HANDLE hnd,EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp);
		~FileSystemContext();
		
	public:
		static const UINTN QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static FileSystemContext GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);

		void OpenVolume();
		void CloseVolume();

		void CloseContext(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);

	private:
		bool _isVolumeOpen;
		EFI::EFI_HANDLE _devhnd;
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* _fs;
		EFI::EFI_FILE_PROTOCOL* _root;
	};
}

