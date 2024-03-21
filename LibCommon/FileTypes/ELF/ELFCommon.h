#pragma once
#include <TypeDefs.h>

namespace Common::FileTypes::ELF
{
	const UINTN MAX_IDENT_LEN = 16ull;

	const UINT16 ELFSectionHdr_UNDEF = 0;
	const UINT16 ELFSectionHdr_LORESERVE = 0xff00;
	const UINT16 ELFSectionHdr_LOPROC = 0xff00;
	const UINT16 ELFSectionHdr_HIPROC = 0xff1f;
	const UINT16 ELFSectionHdr_LOOS = 0xff20;
	const UINT16 ELFSectionHdr_HIOS = 0xff3f;
	const UINT16 ELFSectionHdr_ABS = 0xfff1;
	const UINT16 ELFSectionHdr_COMMON = 0xfff2;
	const UINT16 ELFSectionHdr_XINDEX = 0xffff;
	const UINT16 ELFSectionHdr_HIRESERVE = 0xffff;

	enum ELFClass : UINT8
	{
		None = 0,
		ELF32 = 1,
		ELF64 = 2
	};

	enum ELFDataType : UINT8
	{
		None = 0,
		LSB = 1,
		MSB = 2
	};

	enum ElfType : UINT16
	{
		//No file type
		NONE = 0,
		//Relocatable file
		REL = 1,
		//Executable file
		EXEC = 2,
		//Shared object file
		DYN = 3,
		//Core file
		CORE = 4,
		//Operating system - specific        
		LOOS = 0xfe00,
		//Operating system - specific        
		HIOS = 0xfeff,
		//Processor - specific        
		LOPROC = 0xff00,
		//Processor - specific        
		HIPROC = 0xffff,
	};

	enum ElfMachine : UINT16
	{
		//No machine		
		NONE = 0,
		//AT & T WE 32100		
		M32 = 1,
		//SPARC		
		SPARC = 2,
		//Intel 80386		
		I386 = 3,
		//Motorola 68000		
		M68K = 4,
		//Motorola 88000		
		M88K = 5,
		//Reserved for future use(was EM_486)		
		reserved1 = 6,
		//Intel 80860		
		I860 = 7,
		//MIPS I Architecture		
		MIPS = 8,
		//IBM System / 370 Processor		
		S370 = 9,
		//MIPS RS3000 Little - endian		
		MIPS_RS3_LE = 10,
		// reserved for future use		
		reserved2 = 11,
		// reserved for future use		
		reserved3 = 12,
		// reserved for future use		
		reserved4 = 13,
		// reserved for future use		
		reserved5 = 14,
		//Hewlett - Packard PA - RISC		
		PARISC = 15,
		//Reserved for future use		
		reserved6 = 16,
		//Fujitsu VPP500		
		VPP500 = 17,
		//Enhanced instruction set SPARC		
		SPARC32PLUS = 18,
		// Intel 80960		
		I960 = 19,
		//PowerPC		
		PPC = 20,
		//64 - bit PowerPC		
		PPC64 = 21,
		//IBM System / 390 Processor		
		S390 = 22,
		// Reserved for future use		
		reserved7 = 23,
		// Reserved for future use		
		reserved8 = 24,
		// Reserved for future use		
		reserved9 = 25,
		// Reserved for future use		
		reserved10 = 26,
		// Reserved for future use		
		reserved11 = 27,
		// Reserved for future use		
		reserved12 = 28,
		// Reserved for future use		
		reserved13 = 29,
		// Reserved for future use		
		reserved14 = 30,
		// Reserved for future use		
		reserved15 = 31,
		// Reserved for future use		
		reserved16 = 32,
		// Reserved for future use		
		reserved17 = 33,
		// Reserved for future use		
		reserved18 = 34,
		// Reserved for future use		
		reserved19 = 35,
		//NEC V800		
		V800 = 36,
		//Fujitsu FR20		
		FR20 = 37,
		//TRW RH - 32		
		RH32 = 38,
		//Motorola RCE		
		RCE = 39,
		//Advanced RISC Machines ARM		
		ARM = 40,
		//Digital Alpha		
		ALPHA = 41,
		//Hitachi SH		
		SH = 42,
		//SPARC Version 9		
		SPARCV9 = 43,
		//Siemens TriCore embedded processor		
		TRICORE = 44,
		//Argonaut RISC Core, Argonaut Technologies Inc.		
		ARC = 45,
		//Hitachi H8 / 300		
		H8_300 = 46,
		//Hitachi H8 / 300H		
		H8_300H = 47,
		//Hitachi H8S		
		H8S = 48,
		//Hitachi H8 / 500		
		H8_500 = 49,
		//Intel IA - 64 processor architecture		
		IA_64 = 50,
		//Stanford MIPS - X		
		MIPS_X = 51,
		//Motorola ColdFire		
		COLDFIRE = 52,
		//Motorola M68HC12		
		M68_HC12 = 53,
		//Fujitsu MMA Multimedia Accelerator		
		MMA = 54,
		//Siemens PCP		
		PCP = 55,
		//Sony nCPU embedded RISC processor		
		NCPU = 56,
		//Denso NDR1 microprocessor		
		NDR1 = 57,
		//Motorola Star * Core processor		
		STARCORE = 58,
		//Toyota ME16 processor		
		ME16 = 59,
		//STMicroelectronics ST100 processor		
		ST100 = 60,
		//Advanced Logic Corp.TinyJ embedded processor family		
		TINYJ = 61,
		//AMD x86 - 64 architecture		
		X86_64 = 62,
		//Sony DSP Processor		
		PDSP = 63,
		//Digital Equipment Corp.PDP - 10		
		PDP10 = 64,
		//Digital Equipment Corp.PDP - 11		
		PDP11 = 65,
		//Siemens FX66 microcontroller		
		FX66 = 66,
		//STMicroelectronics ST9 + 8 / 16 bit microcontroller		
		ST9PLUS = 67,
		//STMicroelectronics ST7 8 - bit microcontroller		
		ST7 = 68,
		// Motorola MC68HC16 Microcontroller		
		M68_HC16 = 69,
		// Motorola MC68HC11 Microcontroller		
		M68_HC11 = 70,
		// Motorola MC68HC08 Microcontroller		
		M68_HC08 = 71,
		// Motorola MC68HC05 Microcontroller		
		M68_HC05 = 72,
		//Silicon Graphics SVx		
		SVX = 73,
		//STMicroelectronics ST19 8 - bit microcontroller		
		ST19 = 74,
		//Digital VAX		
		VAX = 75,
		//Axis Communications 32 - bit embedded processor		
		CRIS = 76,
		//Infineon Technologies 32 - bit embedded processor		
		JAVELIN = 77,
		//Element 14 64 - bit DSP Processor		
		FIREPATH = 78,
		//LSI Logic 16 - bit DSP Processor		
		ZSP = 79,
		//Donald Knuth's educational 64-bit processor		
		MMIX = 80,
		//Harvard University machine - independent object files		
		HUANY = 81,
		//SiTera Prism		
		PRISM = 82,
		//Atmel AVR 8 - bit microcontroller		
		AVR = 83,
		//Fujitsu FR30		
		FR30 = 84,
		//Mitsubishi D10V		
		D10V = 85,
		//Mitsubishi D30V		
		D30V = 86,
		//NEC v850		
		V850 = 87,
		//Mitsubishi M32R		
		M32R = 88,
		//Matsushita MN10300		
		MN10300 = 89,
		//Matsushita MN10200		
		MN10200 = 90,
		//picoJava		
		PJ = 91,
		//OpenRISC 32 - bit embedded processor		
		OPENRISC = 92,
		//ARC Cores Tangent - A5		
		ARC_A5 = 93,
		//Tensilica Xtensa Architecture		
		XTENSA = 94,
		//Alphamosaic VideoCore processor		
		VIDEOCORE = 95,
		//Thompson Multimedia General Purpose Processor		
		TMM_GPP = 96,
		//National Semiconductor 32000 series		
		NS32K = 97,
		//Tenor Network TPC processor		
		TPC = 98,
		//Trebia SNP 1000 processor		
		SNP1K = 99,
		//STMicroelectronics(www.st.com) ST200 microcontroller		
		ST200 = 100,
	};

	enum ElfOSABI : UINT8
	{
		//UNIX System V
		UnixSVR4 = 0,
		//HP-UX
		HP_UX = 1,
		//NetBSD
		NetBSD = 2,
		//Linux
		Linux = 3,
		//GNU Hurd
		GNU = 4,
		//Solaris
		Solaris = 6,
		//AIX
		AIX = 7,
		//IRIX
		IRIX = 8,
		//FreeBSD
		FreeBSD = 9,
		//Compaq TRU64 UNIX
		TRU64 = 10,
		//Novell Modesto
		Modesto = 11,
		//OpenBSD
		OpenBSD = 12,
		//OpenVMS
		OpenVMS = 13,
		//NonStop Kernel
		NonStop = 14,
		//AROS
		AROS = 15,
		//Fenix OS
		FenixOS = 16,
		//CloudABI
		CloudABI = 17,
		//Stratus Technologies OpenVOS
		OpenVOS = 18,
		//Nuxi CloudABI
		NuxiCloudABI = 19,
		//Sortix
		Sortix = 83,
	};

	enum ElfSectionType : UINT32
	{
		NULL = 0,
		PROGBITS = 1,
		SYMTAB = 2,
		STRTAB = 3,
		RELA = 4,
		HASH = 5,
		DYNAMIC = 6,
		NOTE = 7,
		NOBITS = 8,
		REL = 9,
		SHLIB = 10,
		DYNSYM = 11,
		INIT_ARRAY = 14,
		FINI_ARRAY = 15,
		PREINIT_ARRAY = 16,
		GROUP = 17,
		SYMTAB_SHNDX = 18,
		LOOS = 0x60000000,
		HIOS = 0x6fffffff,
		LOPROC = 0x70000000,
		HIPROC = 0x7fffffff,
		LOUSER = 0x80000000,
		HIUSER = 0xffffffff,

	};

#pragma pack(push, 1)
	struct ElfIdentHdr
	{
	public:
		union
		{
			CCHAR Char[4];
			UINT32 Value;
		}Magic;
		ELFClass Class;
		ELFDataType DataType;
		UINT8 Version;
		ElfOSABI OSABI;
		UINT8 ABIVersion;
		UINT8 Padding[7];
	};
#pragma pack(pop)

	struct ElfHeaderCommon
	{
	public:
		ElfIdentHdr Identity;
		ElfType Type;
		ElfMachine Machine;
	};

}