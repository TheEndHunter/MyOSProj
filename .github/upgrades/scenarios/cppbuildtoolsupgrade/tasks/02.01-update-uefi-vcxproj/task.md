# 02.01-update-uefi-vcxproj: Update UEFI.vcxproj PlatformToolset to v180

## Objective
Set explicit PlatformToolset/VCToolsVersion for UEFI project to resolve MSB8003 and restore build.

## Scope
- Edit A:\Dev\Projects\MyOSProj\UEFI\UEFI.vcxproj.
- Update only the empty PlatformToolset and VCToolsVersion elements to 'v180' where present.
- Unload project before editing and reload after validation.
- Validate edited .vcxproj with cppupgrade_validate_vcxproj_file before reloading.

## Steps
1. Unload project in IDE (tool-managed step).
2. Edit UEFI.vcxproj: set <PlatformToolset>v180</PlatformToolset> or <VCToolsVersion>v180</VCToolsVersion> where empty.
3. Call cppupgrade_validate_vcxproj_file for the updated file.
4. Reload project in IDE.
5. Run cppupgrade_build_and_get_issues to verify build.
6. If successful, run cppupgrade_rebuild_and_get_issues for final verification.

