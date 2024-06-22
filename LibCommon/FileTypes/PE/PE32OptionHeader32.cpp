#include <FileTypes/PE/PE32OptionHeader32.h>
#include <System/Allocator.h>

namespace Common::FileTypes::PE
{
	PE32OptionHeader32::PE32OptionHeader32(FileSystem::FileHandle* handle)
	{
		handle->Read<UINT32>(&BaseOfData);
		handle->Read<UINT32>(&ImageBase);
		handle->Read<UINT32>(&SectionAlignment);
		handle->Read<UINT32>(&FileAlignment);
		handle->Read<UINT16>(&MajorOperatingSystemVersion);
		handle->Read<UINT16>(&MinorOperatingSystemVersion);
		handle->Read<UINT16>(&MajorImageVersion);
		handle->Read<UINT16>(&MinorImageVersion);
		handle->Read<UINT16>(&MajorSubsystemVersion);
		handle->Read<UINT16>(&MinorSubsystemVersion);
		handle->Read<UINT32>(&Win32VersionValue);
		handle->Read<UINT32>(&SizeOfImage);
		handle->Read<UINT32>(&SizeOfHeaders);
		handle->Read<UINT32>(&CheckSum);
		handle->Read<UINT16>(&Subsystem);
		handle->Read<PE32DLLCharacteristics>(&DllCharacteristics);
		handle->Read<UINT32>(&SizeOfStackReserve);
		handle->Read<UINT32>(&SizeOfStackCommit);
		handle->Read<UINT32>(&SizeOfHeapReserve);
		handle->Read<UINT32>(&SizeOfHeapCommit);
		handle->Read<UINT32>(&LoaderFlags);
		handle->Read<UINT32>(&NumberOfRvaAndSizes);
		DataDirectories = new PE32DataDirectory[NumberOfRvaAndSizes];
		handle->Read<PE32DataDirectory>(DataDirectories,NumberOfRvaAndSizes);
	};
}