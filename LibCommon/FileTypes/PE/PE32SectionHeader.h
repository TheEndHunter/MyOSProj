#pragma once

#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes::PE
{
	enum PE32SectionFlags : UINT32
	{	
		// reserved for future use.
		SectionFlagReserved1 = 0x00000000,
		// reserved for future use.
		SectionFlagReserved2 = 0x00000001,
		// reserved for future use.
		SectionFlagReserved3 = 0x00000002,
		// reserved for future use.
		SectionFlagReserved4 = 0x00000004,
		// the section should not be padded to the next boundary.this flag is obsolete and is replaced by image_scn_align_1bytes.this is valid only for object files.
		TypeNoPad = 0x00000008,
		// reserved for future use.
		SectionFlagReserved5 = 0x00000010,
		// the section contains executable code.
		ContainsCode = 0x00000020,
		// the section contains initialized data.
		ContainsInitializedData = 0x00000040,
		// the section contains uninitialized data.
		ContainsUninitializedData = 0x00000080,
		// reserved for future use.
		LinkOther = 0x00000100,
		// the section contains comments or other information.the.drectve section has this type.this is valid for object files only.
		LinkInfo = 0x00000200,
		// reserved for future use.
		SectionFlagReserved6 = 0x00000400,
		// the section will not become part of the image.this is valid only for object files.
		LnkRemove = 0x00000800,
		// the section contains comdat data.for more information, see comdat sections(object only).this is valid only for object files.
		LnkComDat = 0x00001000,
		// the section contains data referenced through the global pointer(gp).
		GPRel = 0x00008000,
		// reserved for future use.
		MemPurgeable = 0x00020000,
		// reserved for future use.
		Mem16bit = 0x00020000,
		// reserved for future use.
		MemLocked = 0x00040000,
		// reserved for future use.
		MemPreload = 0x00080000,
		// align data on a 1 - byte boundary.valid only for object files.
		Align_1bytes = 0x00100000,
		// align data on a 2 - byte boundary.valid only for object files.
		Align_2bytes = 0x00200000,
		// align data on a 4 - byte boundary.valid only for object files.
		Align_4bytes = 0x00300000,
		// align data on an 8 - byte boundary.valid only for object files.
		Align_8bytes = 0x00400000,
		// align data on a 16 - byte boundary.valid only for object files.
		Align_16bytes = 0x00500000,
		// align data on a 32 - byte boundary.valid only for object files.
		Align_32bytes = 0x00600000,
		// align data on a 64 - byte boundary.valid only for object files.
		Align_64bytes = 0x00700000,
		// align data on a 128 - byte boundary.valid only for object files.
		Align_128bytes = 0x00800000,
		// align data on a 256 - byte boundary.valid only for object files.
		Align_256bytes = 0x00900000,
		// align data on a 512 - byte boundary.valid only for object files.
		Align_512bytes = 0x00a00000,
		// align data on a 1024 - byte boundary.valid only for object files.
		Align_1024bytes = 0x00b00000,
		// align data on a 2048 - byte boundary.valid only for object files.
		Align_2048bytes = 0x00c00000,
		// align data on a 4096 - byte boundary.valid only for object files.
		Align_4096bytes = 0x00d00000,
		// align data on an 8192 - byte boundary.valid only for object files.
		Align_8192bytes = 0x00e00000,
		// the section contains extended relocations.
		LinkNRelocOvfl = 0x01000000,
		// the section can be discarded as needed.
		MemDiscardable = 0x02000000,
		// the section cannot be cached.
		MemNotCached = 0x04000000,
		// the section is not pageable.
		MemNotPaged = 0x08000000,
		// the section can be shared in memory.
		MemShared = 0x10000000,
		// the section can be executed as code.
		MemExecute = 0x20000000,
		// the section can be read.
		MemRead = 0x40000000,
		// the section can be written to.
		MemWrite = 0x80000000,
	};
#pragma pack(push, 1)
	struct PE32SectionHeader
	{
	public:
		PE32SectionHeader();
		PE32SectionHeader(FileSystem::FileHandle* handle);

		CHAR Name[8];

		union
		{
			friend struct PE32SectionHeader;
		private:
			UINT32 Value;
		public:
			UINT32 PhysicalAddress;
			UINT32 VirtualSize;
		}Misc;
		UINT32 VirtualAddress;
		UINT32 SizeOfRawData;
		UINT32 PointerToRawData;
		UINT32 PointerToRelocations;
		UINT32 PointerToLinenumbers;
		UINT16 NumberOfRelocations;
		UINT16 NumberOfLinenumbers;
		PE32SectionFlags Characteristics;
	};
#pragma pack(pop)
}
