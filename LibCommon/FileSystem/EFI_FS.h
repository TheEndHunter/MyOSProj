#pragma once
#include <TypeDefs.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Media/EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_INFO.h>

namespace Common::FileSystem
{
	class FileSystemContext
	{
	protected:
		FileSystemContext(EFI::EFI_HANDLE hnd, EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp);
		
	public:
		static const UINTN QueryFSCount(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static FileSystemContext GetBootFS(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);
		static FileSystemContext GetFileSystem(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd, UINTN index);
		void OpenVolume();
		void CloseVolume();

		void CloseContext(EFI::EFI_SYSTEM_TABLE* sysTable, EFI::EFI_HANDLE hnd);

	private:
		bool _isVolumeOpen;
		EFI::EFI_HANDLE _devhnd;
		EFI::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* _fs;
		EFI::EFI_FILE_PROTOCOL* _root;
		EFI::EFI_FILE_PROTOCOL* _cwd;
	};
}

