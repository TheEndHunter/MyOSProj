#pragma once
#include <TypeDefs.h>


namespace Common::FileSystem::ESP
{
	/* All Status enums for file status */
	enum FileStatus
	{
		Success = 0,
		EndOfFile = 1,
		NotFound = 2,
		NotOpen = 3,
		NotEnoughMemory = 4,
		ReadOnly = 5,
		WriteOnly = 6,
		NotEnoughSpace = 7,
		AccessDenied = 8,
		AlreadyExists = 9,
	};

}