#pragma once
#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes
{
	static const UINT8 MaxPE32DirectoryEntries = 16;
	static const UINT8 MaxPE32SectionHeaderNameLength = 8;

	enum COFFMachineTypes : UINT16
	{
		//The content of this field is assumed to be applicable to any machine type
		Unknown = 0x0,
		//Alpha AXP, 32 - bit address space
		Alpha = 0x184,
		//Alpha 64, 64 - bit address space
		Alpha64 = 0x284,
		//Matsushita AM33
		Am33 = 0x1d3,
		//x64
		Amd64 = 0x8664,
		//ARM little endian
		Arm = 0x1c0,
		//ARM64 little endian
		Arm64 = 0xaa64,
		//ARM Thumb - 2 little endian
		Armnt = 0x1c4,
		//AXP 64 (Same as Alpha 64)
		Axp64 = 0x284,
		//EFI byte code
		Ebc = 0xebc,
		//Intel 386 or later processors and compatible processors
		I386 = 0x14c,
		//Intel Itanium processor family
		Ia64 = 0x200,
		//LoongArch 32 - bit processor family
		Loongarch32 = 0x6232,
		//LoongArch 64 - bit processor family
		Loongarch64 = 0x6264,
		//Mitsubishi M32R little endian
		M32r = 0x9041,
		//MIPS16
		Mips16 = 0x266,
		//MIPS with FPU
		Mipsfpu = 0x366,
		//MIPS16 with FPU
		Mipsfpu16 = 0x466,
		//Power PC little endian
		Powerpc = 0x1f0,
		//Power PC with floating point support
		Powerpcfp = 0x1f1,
		//MIPS little endian
		R4000 = 0x166,
		//RISC - V 32 - bit address space
		Riscv32 = 0x5032,
		//RISC - V 64 - bit address space
		Riscv64 = 0x5064,
		//RISC - V 128 - bit address space
		Riscv128 = 0x5128,
		//Hitachi SH3
		Sh3 = 0x1a2,
		//Hitachi SH3 DSP
		Sh3dsp = 0x1a3,
		//Hitachi SH4
		Sh4 = 0x1a6,
		//Hitachi SH5
		Sh5 = 0x1a8,
		//Thumb
		Thumb = 0x1c2,
		//MIPS little - endian WCE v2
		Wcemipsv2 = 0x169,
	};

	enum COFFCharacteristics : UINT16
	{
		RelocsStripped = 0x0001,
		ExecutableImage = 0x0002,
		LineNumsStripped = 0x0004,
		LocalSymsStripped = 0x0008,
		AggressiveWsTrim = 0x0010,
		LargeAddressAware = 0x0020,
		BytesReversedLo = 0x0080,
		_32bitmachine = 0x0100,
		DebugStripped = 0x0200,
		RemovableRunFromSwap = 0x0400,
		NetRunFromSwap = 0x0800,
		System = 0x1000,
		Dll = 0x2000,
		UpSystemOnly = 0x4000,
		BytesReversedHi = 0x8000
	};

	enum PE32DLLCharacteristics : UINT16
	{
		HighEntropyVA = 0x0020,
		DynamicBase = 0x0040,
		ForceIntegrity = 0x0080,
		NxCompat = 0x0100,
		NoIsolation = 0x0200,
		NoSEH = 0x0400,
		NoBind = 0x0800,
		AppContainer = 0x1000,
		WDMDriver = 0x2000,
		GuardCF = 0x4000,
		TerminalServerAware = 0x8000
	};

	enum PE32SectionCharacteristics : UINT32
	{
		NO_PAD = 0x00000008,
		Reserved5 = 0x00000010,
		ContainsCode = 0x00000020,
		ContainsInitializedData = 0x00000040,
		ContainsUninitializedData = 0x00000080,
		LinkOther = 0x00000100,
		LinkInfo = 0x00000200,
		LinkRemove = 0x00000800,
		LinkComData = 0x00001000,
		GPREL = 0x00008000,
		MemPurgeable = 0x00020000,
		Memory16Bit = 0x00020000,
		MemoryLocked = 0x00040000,
		MemoryPreload = 0x00080000,
		Align1Bytes = 0x00100000,
		Align2Bytes = 0x00200000,
		Align4Bytes = 0x00300000,
		Align8Bytes = 0x00400000,
		Align16Bytes = 0x00500000,
		Align32Bytes = 0x00600000,
		Align64Bytes = 0x00700000,
		Align128Bytes = 0x00800000,
		Align256Bytes = 0x00900000,
		Align512Bytes = 0x00A00000,
		Align1024Bytes = 0x00B00000,
		Align2048Bytes = 0x00C00000,
		Align4096Bytes = 0x00D00000,
		Align8192Bytes = 0x00E00000,
		LinkExtendedRelocationOverflow = 0x01000000,
		MemoryDiscardable = 0x02000000,
		MemoryNotCached = 0x04000000,
		MemoryNotPaged = 0x08000000,
		MemoryShared = 0x10000000,
		MemoryExecute = 0x20000000,
		MemoryRead = 0x40000000,
		MemoryWrite = 0x80000000
	};

#pragma pack(push, 1)
	struct PE32DataDirectory
	{
		UINT32 VirtualAddress;
		UINT32 Size;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct DOSHeader
	{
	public:
		union
		{
			CHAR8 Char[2];
			UINT16 Value;
		} Magic;
		UINT16 BytesOnLastPage;
		UINT16 PagesInFile;
		UINT16 Relocations;
		UINT16 SizeOfHeaderParagraphs;
		UINT16 MinimumExtraParagraphs;
		UINT16 MaximumExtraParagraphs;
		UINT16 InitialSS;
		UINT16 InitialSP;
		UINT16 Checksum;
		UINT16 InitialIP;
		UINT16 InitialCS;
		UINT16 RelocationTableOffset;
		UINT16 OverlayNumber;
		UINT16 Reserved[4];
		UINT16 OEMID;
		UINT16 OEMInfo;
		UINT16 Reserved2[10];
		UINT32 PEHeaderOffset;

	public:
		static const BOOLEAN VerifySignature(const DOSHeader* header);

	};
#pragma pack(pop)
#pragma pack(push, 1)
	struct COFFHeader
	{
	public:
		COFFMachineTypes Machine;
		UINT16 NumberOfSections;
		UINT32 TimeDateStamp;
		UINT32 PointerToSymbolTable;
		UINT32 NumberOfSymbols;
		UINT16 SizeOfOptionalHeader;
		COFFCharacteristics Characteristics;
	};

#pragma pack(pop)

#pragma pack(push, 1)
	struct PE32OptionHeader
	{
	public:
		union
		{
			CHAR8 Char[2];
			UINT16 Value;
		} Magic;
		UINT8 MajorLinkerVersion;
		UINT8 MinorLinkerVersion;
		UINT32 SizeOfCode;
		UINT32 SizeOfInitializedData;
		UINT32 SizeOfUninitializedData;
		UINT32 AddressOfEntryPoint;
		union
		{
			UINT32 BaseOfCode;
			UINT32 BaseOfData;
			UINT64 ImageBase;
		}PEAddr;
		UINT32 SectionAlignment;
		UINT32 FileAlignment;
		UINT16 MajorOperatingSystemVersion;
		UINT16 MinorOperatingSystemVersion;
		UINT16 MajorImageVersion;
		UINT16 MinorImageVersion;
		UINT16 MajorSubsystemVersion;
		UINT16 MinorSubsystemVersion;
		UINT32 Win32VersionValue;
		UINT32 SizeOfImage;
		UINT32 SizeOfHeaders;
		UINT32 CheckSum;
		UINT16 Subsystem;
		PE32DLLCharacteristics DllCharacteristics;
	};
#pragma pack(pop)

#pragma pack(push, 1)

	struct PE32OptionFooter
	{
		UINT32 SizeOfStackReserve;
		UINT32 SizeOfStackCommit;
		UINT32 SizeOfHeapReserve;
		UINT32 SizeOfHeapCommit;
		UINT32 LoaderFlags;
		UINT32 NumberOfRvaAndSizes;
		PE32DataDirectory DataDirectory[MaxPE32DirectoryEntries];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PE32POptionFooter
	{
		UINT64 SizeOfStackReserve;
		UINT64 SizeOfStackCommit;
		UINT64 SizeOfHeapReserve;
		UINT64 SizeOfHeapCommit;
		UINT32 LoaderFlags;
		UINT32 NumberOfRvaAndSizes;
		PE32DataDirectory DataDirectory[MaxPE32DirectoryEntries];
	};

#pragma pack(pop)

#pragma pack(push, 1)
	struct PE32Header
	{
	public:
		union
		{
			CHAR8 Char[4];
			UINT32 Value;
		}Signature;

		COFFHeader FileHeader;
		PE32OptionHeader OptionHeader;
	public:
		static const BOOLEAN VerifySignature(const PE32Header* header);
	};
#pragma pack(pop)


#pragma pack(push,1)
	struct PE32SectionHeader
	{
		UINT8 Name[MaxPE32SectionHeaderNameLength];
		union
		{
			UINT32 PhysicalAddress;
			UINT32 VirtualSize;
		} Misc;
		UINT32 VirtualAddress;
		UINT32 SizeOfRawData;
		UINT32 PointerToRawData;
		UINT32 PointerToRelocations;
		UINT32 PointerToLinenumbers;
		UINT16 NumberOfRelocations;
		UINT16 NumberOfLinenumbers;
		PE32SectionCharacteristics Characteristics;
	};
#pragma pack(pop)

	struct PE32File
	{
		UINTN lastHeaderPosition;
		DOSHeader* DosHeader;
		PE32Header* PEHeader;
		PE32OptionHeader* PEOptionHeader;
		union
		{
			void* _Ptr;
			PE32OptionFooter* PE32;
			PE32POptionFooter* PE32P;
		}Footer;
		PE32SectionHeader* SectionHeaders;

	private:
		PE32File(Common::FileSystem::FileHandle* handle);
	public:
		static PE32File* Read(Common::FileSystem::FileHandle* handle);
		static DOSHeader* ReadDOSHeader(Common::FileSystem::FileHandle* handle, UINTN offset = 0U);
		static PE32Header* ReadPE32Header(Common::FileSystem::FileHandle* handle, UINTN offset = 0U);
		static PE32OptionHeader* ReadPE32OptionHeader(Common::FileSystem::FileHandle* handle, UINTN offset = 0U);
		static PE32OptionFooter* ReadPE32OptionFooter(Common::FileSystem::FileHandle* handle, UINTN offset = 0U);
		static PE32POptionFooter* ReadPE32POptionFooter(Common::FileSystem::FileHandle* handle, UINTN offset = 0U);
		static PE32SectionHeader* ReadPE32SectionHeader(Common::FileSystem::FileHandle* handle, UINTN offset = 0U);
	};
};

