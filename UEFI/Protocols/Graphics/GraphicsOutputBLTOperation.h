#pragma once

namespace Efi
{
	 enum class GraphicsOutputBLTOperation 
	 {
		EfiBltVideoFill,
		EfiBltVideoToBltBuffer,
		EfiBltBufferToVideo,
		EfiBltVideoToVideo,
		EfiGraphicsOutputBltOperationMax
	};
}
