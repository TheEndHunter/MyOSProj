#pragma once
#include "UEFIDef.h"
namespace EFI
{
#if defined(BITS_64)
	constexpr static UINTN ERROR_MASK = 0x8000000000000000;
	constexpr static UINTN WARNING_MASK = 0x0000000000000000;
#elif defined(BITS_32)
	constexpr static UINTN ERROR_MASK = 0x80000000;
	constexpr static UINTN WARNING_MASK = 0x00000000;
#endif

	enum class EFI_STATUS : UINTN
	{
		SUCCESS = 0,
		LOAD_ERROR = 1 | ERROR_MASK,
		INVALID_PARAMETER = 2 | ERROR_MASK,
		UNSUPPORTED = 3 | ERROR_MASK,
		BAD_BUFFER_SIZE = 4 | ERROR_MASK,
		BUFFER_TOO_SMALL = 5 | ERROR_MASK,
		NOT_READY = 6 | ERROR_MASK,
		DEVICE_ERROR = 7 | ERROR_MASK,
		WRITE_PROTECTED = 8 | ERROR_MASK,
		OUT_OF_RESOURCES = 9 | ERROR_MASK,
		VOLUME_CORRUPTED = 10 | ERROR_MASK,
		VOLUME_FULL = 11 | ERROR_MASK,
		NO_MEDIA = 12 | ERROR_MASK,
		MEDIA_CHANGED = 13 | ERROR_MASK,
		NOT_FOUND = 14 | ERROR_MASK,
		ACCESS_DENIED = 15 | ERROR_MASK,
		NO_RESPONSE = 16 | ERROR_MASK,
		NO_MAPPING = 17 | ERROR_MASK,
		TIMEOUT = 18 | ERROR_MASK,
		NOT_STARTED = 19 | ERROR_MASK,
		ALREADY_STARTED = 20 | ERROR_MASK,
		ABORTED = 21 | ERROR_MASK,
		ICMP_ERROR = 22 | ERROR_MASK,
		TFTP_ERROR = 23 | ERROR_MASK,
		PROTOCOL_ERROR = 24 | ERROR_MASK,
		INCOMPATIBLE_VERSION = 25 | ERROR_MASK,
		SECURITY_VIOLATION = 26 | ERROR_MASK,
		CRC_ERROR = 27 | ERROR_MASK,
		END_OF_MEDIA = 28 | ERROR_MASK,
		END_OF_FILE = 31 | ERROR_MASK,
		INVALID_LANGUAGE = 32 | ERROR_MASK,
		COMPROMISED_DATA = 33 | ERROR_MASK,
		IP_ADDRESS_CONFLICT = 34 | ERROR_MASK,
		HTTP_ERROR = 35 | ERROR_MASK,

		WARN_UNKNOWN_GLYPH = 1 | WARNING_MASK,
		WARN_DELETE_FAILURE = 2 | WARNING_MASK,
		WARN_WRITE_FAILURE = 3 | WARNING_MASK,
		WARN_BUFFER_TOO_SMALL = 4 | WARNING_MASK,
		WARN_STALE_DATA = 5 | WARNING_MASK,
		WARN_FILE_SYSTEM = 6 | WARNING_MASK,
		WARN_RESET_REQUIRED = 7 | WARNING_MASK
	};
};