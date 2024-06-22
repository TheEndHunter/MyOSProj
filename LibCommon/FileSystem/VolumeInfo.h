#pragma once
#include <TypeDefs.h>
#include <Protocols/Time/EFI_TIME.h>
#include <Protocols/IO/Media/EFI_FILE_PROTOCOL.h>
#include <Protocols/IO/Media/EFI_FILE_SYSTEM_INFO.h>
#include <Environment/Unicode.h>
#include <Protocols/IO/Media/EFI_FILE_SYSTEM_VOLUME_LABEL.h>

namespace Common::FileSystem
{
	struct VolumeInfo
	{
	protected:
		VolumeInfo(EFI::EFI_FILE_SYSTEM_INFO info)
			:Size(info.Size), ReadOnly(info.ReadOnly), VolumeSize(info.VolumeSize), FreeSpace(info.FreeSpace), BlockSize(info.BlockSize), VolumeLabel(info.VolumeLabel)
		{
		}

	public:
		constexpr VolumeInfo() : Size(0), ReadOnly(FALSE), VolumeSize(0), FreeSpace(0), BlockSize(0), VolumeLabel(nullptr)
		{
		}

		static VolumeInfo Create(EFI::EFI_FILE_SYSTEM_INFO* info);

	public:
		UINT64 Size;
		BOOLEAN ReadOnly;
		UINT64 VolumeSize;
		UINT64 FreeSpace;
		UINT32 BlockSize;
		CHAR16* VolumeLabel;

		bool operator ==(const VolumeInfo& right)
		{
			/*Compare all members for equality, if one fails return false, otherwise return true*/

			if (Size != right.Size)
				return false;

			if (ReadOnly != right.ReadOnly)
				return false;

			if (VolumeSize != right.VolumeSize)
				return false;

			if (FreeSpace != right.FreeSpace)
				return false;

			if (BlockSize != right.BlockSize)
				return false;

			BOOLEAN lb = Environment::UTF16::IsNullOrEmpty(VolumeLabel);
			BOOLEAN rb = Environment::UTF16::IsNullOrEmpty(right.VolumeLabel);

			if (lb && rb)
				return TRUE;

			if (lb || rb)
				return FALSE;

			return Environment::UTF16::Compare(VolumeLabel, right.VolumeLabel) == TRUE;
		}

		bool operator !=(const VolumeInfo& right)
		{
			return !(*this == right);
		}
	};

	struct VolumeLabel
	{
		constexpr VolumeLabel() : Label(nullptr)
		{
		}

		VolumeLabel(const EFI::EFI_FILE_SYSTEM_VOLUME_LABEL label)
			:Label((CHAR16*)& label.VolumeLabel[0])
		{
		}

		CHAR16* Label;

		bool operator ==(const VolumeLabel* right)
		{
			if(right == nullptr && this == nullptr)
				return true;

			if(right == nullptr || this == nullptr)
				return false;

			BOOLEAN lb = Environment::UTF16::IsNullOrEmpty(Label);
			BOOLEAN rb = Environment::UTF16::IsNullOrEmpty(right->Label);

			if (lb == TRUE && rb == TRUE)
				return TRUE;

			if (lb || rb)
				return FALSE;

			return Environment::UTF16::Compare(Label, right->Label) == TRUE;
		};

		bool operator !=(const VolumeLabel* right)
		{
			return !this->operator==(right);
		}

		bool operator ==(const VolumeLabel right)
		{
			BOOLEAN lb = Environment::UTF16::IsNullOrEmpty(Label);
			BOOLEAN rb = Environment::UTF16::IsNullOrEmpty(right.Label);

			if(lb == TRUE && rb == TRUE)
				return TRUE;

			if(lb || rb)
				return FALSE;

			return Environment::UTF16::Compare(Label, right.Label) == TRUE;
		}

		bool operator !=(const VolumeLabel right)
		{
			return !this->operator==(right);
		}

	private:
		bool IsNullOrEmpty(VolumeLabel* right)
		{
			if(right == nullptr)
				return TRUE;

			if(right->Label == nullptr)
				return TRUE;

			if(right->Label[0] == 0)
				return TRUE;

			return FALSE;
		}
	};

	constinit const VolumeInfo Empty_VolInfo = VolumeInfo();
	constinit const VolumeLabel Empty_VolLabel = VolumeLabel();
}
