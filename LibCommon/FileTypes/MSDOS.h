#pragma once
#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes
{
    struct DOS_HDR
    {
    public:
        UINT16   Magic;// Magic number
        UINT16   Cblp; // Bytes on last page of file
        UINT16   PageCount; // Pages in file
        UINT16   Relocations; // Relocations
        UINT16   CountParHDR; // Size of header in paragraphs
        UINT16   MinAlloc; // Minimum extra paragraphs needed
        UINT16   MaxAlloc; // Maximum extra paragraphs needed
        UINT16   ssInital; // Initial (relative) SS value
        UINT16   spInital; // Initial SP value
        UINT16   ChkSum; // Checksum
        UINT16   IpInitial; // Initial IP value
        UINT16   CsInitial; // Initial (relative) CS value
        UINT16   RelocFileAddr; // File address of relocation table
        UINT16   OverlayNum; // Overlay number
        UINT16   Reserved[4]; // Reserved words
        UINT16   OEM_ID; // OEM identifier (for e_oeminfo)
        UINT16   OEM_INFO; // OEM information; e_oemid specific
        UINT16   Reserved2[10]; // Reserved words
        UINT32   ExeHdrAddr; // File address of new exe header

        static DOS_HDR ReadHdr(Common::FileSystem::FileHandle* file);
    };

    constinit const DOS_HDR DOS_HDR_EMPTY = { 0 };
}

