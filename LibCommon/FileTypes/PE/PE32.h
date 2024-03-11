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
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes::PE
{

	struct PE32
	{
	public:
		PE32(FileSystem::FileHandle* handle);

		BOOLEAN IsValid() const;
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
	private:
		BOOLEAN _isValid;
	};
}
