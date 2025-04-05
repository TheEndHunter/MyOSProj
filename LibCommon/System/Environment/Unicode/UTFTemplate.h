#pragma once
#include <TypeDefs.h>
#include <EFI_GUID.h>
#include <EFI_STATUS.h>
#include <System/Environment/IsChar.h>
#include <System/Environment/StringCulture.h>
#include <System/MemoryManagement/AllocatorStatus.h>

namespace Common::System::Environment
{
	template<IsChar StrType>
	class UTF
	{
	public:
		const static StrType  NULL;
		const static StrType* NewLine;
		const static StrType  Space;
		const static StrType  Tab;
		const static StrType  Backspace;

		static StrType* ToHex(const INT16 value);
		static StrType* ToHex(const INT32 value);
		static StrType* ToHex(const INT64 value);
		static StrType* ToHex(const INT8 value);

		static StrType* ToHex(const UINT16 value);
		static StrType* ToHex(const UINT32 value);
		static StrType* ToHex(const UINT64 value);
		static StrType* ToHex(const UINT8 value);
		static StrType* ToHex(const VOID_PTR ptr);

		static StrType* ToString(const EFI::EFI_GUID guid);
		static StrType* ToString(const EFI::EFI_STATUS status);
		static StrType* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static StrType* ToString(const INT16 value);
		static StrType* ToString(const INT32 value);
		static StrType* ToString(const INT64 value);
		static StrType* ToString(const INT8 value);

		static StrType* ToString(const UINT16 value);
		static StrType* ToString(const UINT32 value);
		static StrType* ToString(const UINT64 value);
		static StrType* ToString(const UINT8 value);
		static StrType* ToString(const VOID_PTR ptr);
		static StrType* ToString(const BOOLEAN boolean);

		static UINT64 Length(const StrType* str);
		static BOOLEAN Compare(const StrType* l, const StrType* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const StrType* str, const StrType* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const StrType* str, const StrType* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const StrType* str, const StrType* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const StrType* str);
		static BOOLEAN IsNullOrWhiteSpace(const StrType* str);
		static BOOLEAN IsNullEmptyOrWhiteSpace(const StrType* str);

		static StrType* FromCharArray(StrType arr[], UINT64 Length);

		static INT64 IndexOf(const StrType* str, const StrType* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static INT64 IndexOf(const StrType* str, const StrType value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static INT64 LastIndexOf(const StrType* str, const StrType* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static INT64 LastIndexOf(const StrType* str, const StrType value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);

		static StrType** Split(const StrType* str, const StrType* separator, OUT UINT64* count);
		static StrType** Split(const StrType* str, const StrType separator, OUT UINT64* count);
		static StrType* Join(const StrType** str, const StrType* separator, UINT64 count);
		static StrType* Join(const StrType** str, const StrType separator, UINT64 count);
	};
}
