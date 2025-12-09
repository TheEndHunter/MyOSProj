#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_PROTOCOL.h>
#include <Protocols/IO/Media/EFI_FILE_SYSTEM_INFO.h>
#include <System/Environment/Unicode.h>
#include <Protocols/IO/Media/EFI_FILE_SYSTEM_VOLUME_LABEL.h>
#include <System/MemoryManagement/MemFuncs.h>

namespace Common::FileSystem::ESP
{
	class ESP_FS_Context;
}

namespace Common::FileSystem
{
	struct VolumeLabel
	{
	public:
		constexpr VolumeLabel() : Size(0), Label(nullptr)
		{
		}

		VolumeLabel(const CHAR16* label)
		{
			if (label == nullptr)
			{
				Size = 0;
				Label = nullptr;
				return;
			}

			Size = Common::System::Environment::UTF<CHAR16>::Length(label);
			Label = new CHAR16[Size];

			Common::System::MemCpy<CHAR16>(&Label[0], (CHAR16*)label, Size);

		}

		VolumeLabel(const EFI::EFI_FILE_SYSTEM_VOLUME_LABEL label)
		{
			Size = Common::System::Environment::UTF<CHAR16>::Length(label.VolumeLabel);
			Label = new CHAR16[Size];
			Common::System::MemCpy<CHAR16>(&Label[0], (CHAR16*)&label.VolumeLabel[0], Size);
		}

		UINT64 Size;
		CHAR16* Label;

		BOOLEAN operator ==(const VolumeLabel& right)
		{
			if (Size != right.Size)
				return FALSE;

			return Common::System::Environment::UTF<CHAR16>::Compare(Label, right.Label);
		}
	};
	struct VolumeInfo
	{
		friend ESP::ESP_FS_Context;
	protected:
		VolumeInfo(EFI::EFI_FILE_SYSTEM_INFO* info)
		{
			if (info == nullptr)
			{
				Size = 0;
				ReadOnly = FALSE;
				VolumeSize = 0;
				FreeSpace = 0;
				BlockSize = 0;
				Label = VolumeLabel();
				return;
			}

			Size = info->Size;
			ReadOnly = info->ReadOnly;
			VolumeSize = info->VolumeSize;
			FreeSpace = info->FreeSpace;
			BlockSize = info->BlockSize;
			Label = info->VolumeLabel;

		}

	public:
		constexpr VolumeInfo() : Size(0), ReadOnly(FALSE), VolumeSize(0), FreeSpace(0), BlockSize(0), Label(VolumeLabel())
		{
		}

		BOOLEAN operator==(const VolumeInfo& right)
		{
			return  Label == right.Label && Size == right.Size && ReadOnly == right.ReadOnly && VolumeSize == right.VolumeSize && FreeSpace == right.FreeSpace && BlockSize == right.BlockSize;
		}

		static VolumeInfo Create(EFI::EFI_FILE_SYSTEM_INFO* info);

	public:
		UINT64 Size;
		BOOLEAN ReadOnly;
		UINT64 VolumeSize;
		UINT64 FreeSpace;
		UINT32 BlockSize;
		VolumeLabel Label;
	};

	constinit const VolumeInfo Empty_VolInfo = VolumeInfo();
	constinit const VolumeLabel Empty_VolLabel = VolumeLabel();
}
