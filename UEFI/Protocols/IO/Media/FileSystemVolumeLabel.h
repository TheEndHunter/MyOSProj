#pragma once
#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include <Protocols/Time/Time.h>
#include "FileAttributes.h"
#include <HelperFuncs/StringHelpers.h>

namespace Efi
{
	constinit const ALIGN(8) Efi::Guid FileSystemVolumeLabel_ID { 0xdb47d7d3U,0xfe81U,0x11d3U,{0x9aU,0x35U,0x00U,0x90U,0x27U,0x3fU,0xC1U,0x4dU } };

	struct FileSystemVolumeLabel
	{
	public:
		const CHAR16* VolumeLabel;


		BOOLEAN operator==(const FileSystemVolumeLabel& other) const
		{
			return CompareStrings(VolumeLabel, other.VolumeLabel);
		}
	};
}
