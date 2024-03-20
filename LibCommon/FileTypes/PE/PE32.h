#pragma once
#include <TypeDefs.h>
#include <FileTypes/PE/MSDos.h>
#include <FileTypes/PE/PE32Header.h>
#include <FileTypes/PE/PE32OptionHeader.h>
#include <FileTypes/PE/PE32OptionHeader32.h>
#include <FileTypes/PE/PE32OptionHeader64.h>
#include <FileTypes/PE/PE32DataDirectory.h>
#include <FileTypes/PE/PE32SectionHeader.h>
#include <FileTypes/PE/PE32DLLCharacteristics.h>
#include <System/Allocator.h>
#include <FileSystem/ESP/FileHandle.h>

namespace Common::FileTypes::PE
{

	struct PE32
	{
	public:
		PE32(FileSystem::ESP::FileHandle* handle);

		BOOLEAN IsDosHdrValid() const;
		BOOLEAN IsPEHdrValid() const;
		BOOLEAN IsOptHdrValid() const;
		BOOLEAN IsSectionHdrValid() const;
		BOOLEAN IsDataBufferValid() const;

		DOSHeader DOSHdr;
		PE32Header PE32hdr;
		PE32OptionHeader OptHdrCommon;
		union
		{
			friend struct PE32;
		private:
			void* _optionHeaders;
		public:
			PE32OptionHeader32* PE32;
			PE32OptionHeader64* PE32PLUS;
		}OptHdr;

		PE32SectionHeader* SectionHeaders;

		const UINTN GetEntryPointOffset() const;
		const VOID_PTR GetEntryPoint() const;

		UINTN SizeOfDataBuffer;
		UINT8* DataBuffer;

	private:

		UINTN _EntryPointOffset;
		VOID_PTR _EntryPoint;
		BOOLEAN _dosHdrValid;
		BOOLEAN _peHdrValid;
		BOOLEAN _optHdrValid;
		BOOLEAN _sectionHdrValid;
		BOOLEAN _dataBufferValid;
	};
}
