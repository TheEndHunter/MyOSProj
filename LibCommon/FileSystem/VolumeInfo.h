#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/Time.h>
#include <Protocols/IO/Media/FileProtocol.h>
#include <Protocols/IO/Media/FileSystemInfo.h>
#include <System/Environment/Unicode.h>
#include <Protocols/IO/Media/FileSystemVolumeLabel.h>
#include <System/MemoryManagement/MemFuncs.h>
#include <System/Environment/String.h>

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

		//Size always includes null terminaltor
        Size = Common::System::Environment::UTF<CHAR16>::Length(label);
        Label = (CHAR16*)Common::System::MemoryManagement::EfiAllocator::Allocate(sizeof(CHAR16) * (Size + 1));
        if (Label == nullptr)
        {
            Size = 0;
            return;
        }

		System::MemCpy<CHAR16>(&Label[0], (CHAR16*)label, Size);
		Label[Size] = 0;

		}

    VolumeLabel(const Efi::FileSystemVolumeLabel label)
		{
        Size = Common::System::Environment::UTF<CHAR16>::Length(label.VolumeLabel);
        Label = (CHAR16*)Common::System::MemoryManagement::EfiAllocator::Allocate(sizeof(CHAR16) * (Size + 1));
        if (Label == nullptr)
        {
            Size = 0;
            return;
        }

		System::MemCpy<CHAR16>(&Label[0], (CHAR16*)&label.VolumeLabel[0], Size);
		Label[Size] = 0;
		}

    ~VolumeLabel()
    {
        if (Label != nullptr)
        {
            Common::System::MemoryManagement::EfiAllocator::Free(Label);
            Label = nullptr;
            Size = 0;
        }
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
		VolumeInfo(Efi::EFI_FILE_SYSTEM_INFO* info)
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
			// Initialize VolumeLabel from EFI struct
			Label = VolumeLabel(info->VolumeLabel);

		}

	public:
		constexpr VolumeInfo() : Size(0), ReadOnly(FALSE), VolumeSize(0), FreeSpace(0), BlockSize(0), Label(VolumeLabel())
		{
		}

		BOOLEAN operator==(const VolumeInfo& right)
		{
			return  Label == right.Label && Size == right.Size && ReadOnly == right.ReadOnly && VolumeSize == right.VolumeSize && FreeSpace == right.FreeSpace && BlockSize == right.BlockSize;
		}

		static VolumeInfo Create(Efi::EFI_FILE_SYSTEM_INFO* info);

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
