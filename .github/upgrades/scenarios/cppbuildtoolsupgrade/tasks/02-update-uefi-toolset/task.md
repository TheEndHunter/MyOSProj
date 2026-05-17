# 02-update-uefi-toolset: Update UEFI project PlatformToolset

Edit the UEFI.vcxproj to set an explicit PlatformToolset/VCToolsVersion where empty to resolve MSB8003.

**Done when**: UEFI project builds successfully and a full rebuild reports zero errors related to missing PlatformToolset.
