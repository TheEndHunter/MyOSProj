#pragma once

#include <TypeDefs.h>
#include <Graphics/MonitorMode.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>

namespace Common::Graphics
{
	struct MonitorContext
	{
		friend struct RenderContext;

	public:
		const MonitorMode* GetCurrentMode() const;
		const MonitorMode* GetMode(UINT32 modeNumber) const;
		void SetMode(UINT32 modeNumber);

		UINTN GetFrameBufferSize() const;
		UINT32 GetHorizontalResolution() const;
		UINT32 GetVerticalResolution() const;
		UINT32 GetPixelsPerScanLine() const;
		Pixel* GetFrameBuffer() const;


	private:
		EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* protocol;
		MonitorMode* modes;
		UINTN maxMode;
		UINTN currentMode;
		MonitorContext();
		MonitorContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr);
	};


}
