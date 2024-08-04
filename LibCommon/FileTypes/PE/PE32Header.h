#pragma once
#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>
#include <FileTypes/PE/PE32OptionHeader32.h>
#include <FileTypes/PE/PE32OptionHeader64.h>

namespace Common::FileTypes::PE
{
	enum MachineTypes : UINT16
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

	enum PECharacteristics : UINT16
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

#pragma pack(push, 1)
	struct PE32Header
	{
	public:
		PE32Header();

		PE32Header(FileSystem::FileHandle* handle);

		union
		{
			CHAR Char[4];
			UINT32 Value;
		}Signature;

		MachineTypes Machine;
		UINT16 NumberOfSections;
		UINT32 TimeDateStamp;
		UINT32 PointerToSymbolTable;
		UINT32 NumberOfSymbols;
		UINT16 SizeOfOptionalHeader;
		PECharacteristics Characteristics;
	};
#pragma pack(pop)
}
