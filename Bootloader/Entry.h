#pragma once
#include <TypeDefs.h>
#include <Handle.h>
#include <Status.h>
#include <SystemTable.h>

#include <Protocols/IO/Peripheral/InputKey.h>

namespace Bootloader
{
	using namespace Efi;
	extern "C" Status EFIAPI EfiMain(Handle imgHndl, SystemTable * sysTbl);
}