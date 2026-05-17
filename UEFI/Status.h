#pragma once
#include "UEFIDef.h"
namespace Efi
{

#if defined(BITS_64)
	constexpr static UINTN ErrorMask = 0x8000000000000000;
	constexpr static UINTN WarningMask = 0x0000000000000000;
#elif defined(BITS_32)
	constexpr static UINTN ErrorMask = 0x80000000;
	constexpr static UINTN WarningMask = 0x00000000;
#endif

	enum class Status : UINTN
	{
		Success = 0,
		LoadError = 1 | ErrorMask,
		InvalidParameter = 2 | ErrorMask,
		Unsupported = 3 | ErrorMask,
		BadBufferSize = 4 | ErrorMask,
		BufferTooSmall = 5 | ErrorMask,
		NotReady = 6 | ErrorMask,
		DeviceError = 7 | ErrorMask,
		WriteProtected = 8 | ErrorMask,
		OutOfResources = 9 | ErrorMask,
		VolumeCorrupted = 10 | ErrorMask,
		VolumeFull = 11 | ErrorMask,
		NoMedia = 12 | ErrorMask,
		MediaChanged = 13 | ErrorMask,
		NotFound = 14 | ErrorMask,
		AccessDenied = 15 | ErrorMask,
		NoResponse = 16 | ErrorMask,
		NoMapping = 17 | ErrorMask,
		Timeout = 18 | ErrorMask,
		NotStarted = 19 | ErrorMask,
		AlreadyStarted = 20 | ErrorMask,
		Aborted = 21 | ErrorMask,
		IcmpError = 22 | ErrorMask,
		TftpError = 23 | ErrorMask,
		ProtocolError = 24 | ErrorMask,
		IncompatibleVersion = 25 | ErrorMask,
		SecurityViolation = 26 | ErrorMask,
		CrcError = 27 | ErrorMask,
		EndOfMedia = 28 | ErrorMask,
		EndOfFile = 31 | ErrorMask,
		InvalidLanguage = 32 | ErrorMask,
		CompromisedData = 33 | ErrorMask,
		IpAddressConflict = 34 | ErrorMask,
		HttpError = 35 | ErrorMask,

		WarnUnknownGlyph = 1 | WarningMask,
		WarnDeleteFailure = 2 | WarningMask,
		WarnWriteFailure = 3 | WarningMask,
		WarnBufferTooSmall = 4 | WarningMask,
		WarnStaleData = 5 | WarningMask,
		WarnFileSystem = 6 | WarningMask,
		WarnResetRequired = 7 | WarningMask
	};
};