#include <FileTypes/PE/PE32OptionHeader32.h>
#include <System/Allocator.h>

namespace Common::FileTypes::PE
{
	PE32OptionHeader32::PE32OptionHeader32(FileSystem::FileHandle* handle)
	{
		handle->Read(sizeof(BaseOfData), &BaseOfData);
		handle->Read(sizeof(ImageBase), &ImageBase);
		handle->Read(sizeof(SectionAlignment), &SectionAlignment);
		handle->Read(sizeof(FileAlignment), &FileAlignment);
		handle->Read(sizeof(MajorOperatingSystemVersion), &MajorOperatingSystemVersion);
		handle->Read(sizeof(MinorOperatingSystemVersion), &MinorOperatingSystemVersion);
		handle->Read(sizeof(MajorImageVersion), &MajorImageVersion);
		handle->Read(sizeof(MinorImageVersion), &MinorImageVersion);
		handle->Read(sizeof(MajorSubsystemVersion), &MajorSubsystemVersion);
		handle->Read(sizeof(MinorSubsystemVersion), &MinorSubsystemVersion);
		handle->Read(sizeof(Win32VersionValue), &Win32VersionValue);
		handle->Read(sizeof(SizeOfImage), &SizeOfImage);
		handle->Read(sizeof(SizeOfHeaders), &SizeOfHeaders);
		handle->Read(sizeof(CheckSum), &CheckSum);
		handle->Read(sizeof(Subsystem), &Subsystem);
		handle->Read(sizeof(DllCharacteristics), &DllCharacteristics);
		handle->Read(sizeof(SizeOfStackReserve), &SizeOfStackReserve);
		handle->Read(sizeof(SizeOfStackCommit), &SizeOfStackCommit);
		handle->Read(sizeof(SizeOfHeapReserve), &SizeOfHeapReserve);
		handle->Read(sizeof(SizeOfHeapCommit), &SizeOfHeapCommit);
		handle->Read(sizeof(LoaderFlags), &LoaderFlags);
		handle->Read(sizeof(NumberOfRvaAndSizes), &NumberOfRvaAndSizes);
		UINTN dataDirSize = sizeof(PE32DataDirectory) * NumberOfRvaAndSizes;
		
		DataDirectories = (PE32DataDirectory*)System::Allocator::Allocate(dataDirSize);
		handle->Read(dataDirSize, &DataDirectories);
	};
}