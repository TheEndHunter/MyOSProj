#pragma once

namespace EFI
{
	 enum class EFI_GRAPHICS_OUTPUT_BLT_OPERATION 
	 {
		EfiBltVideoFill,
		EfiBltVideoToBltBuffer,
		EfiBltBufferToVideo,
		EfiBltVideoToVideo,
		EfiGraphicsOutputBltOperationMax
	};
}
