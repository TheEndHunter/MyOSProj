#pragma once
#include <TypeDefs.h>

#if defined(__has_include)
// Prefer the generator output from the .tt template name if present
#if __has_include("GenerateCaseFolding.generated.h")
#include "GenerateCaseFolding.generated.h"
#elif __has_include("UnicodeCaseFolding.generated.h")
#include "UnicodeCaseFolding.generated.h"
#else
#endif
#else
#endif

// Placeholder for a full, data-driven Unicode CaseFolding table.
// This header will include a generated mapping file when present. The generated
// filename may be either `GenerateCaseFolding.generated.h` (produced by the
// template `GenerateCaseFolding.tt`) or `UnicodeCaseFolding.generated.h`.
// If no generated file is available a small fallback mapping is provided.
namespace Common::System::Environment::Unicode
{
#if defined(__has_include)
  // Prefer the generator output from the .tt template name if present
  #if __has_include("GenerateCaseFolding.generated.h")
  #elif __has_include("UnicodeCaseFolding.generated.h")
  #else
    struct Mapping { UINT32 from; UINT32 to; };
    // Fallback small sample mapping. Generated file not found.
    static constexpr Mapping _caseFoldTable[] = {
        { 0x0178u, 0x00FFu },
    const UINTN CaseFoldTableSize = sizeof(_caseFoldTable) / sizeof(Mapping);
    };
  #endif
#else
  struct Mapping { UINT32 from; UINT32 to; };
  // No __has_include support; fallback mapping.
  static constexpr Mapping _caseFoldTable[] = {
      { 0x0178u, 0x00FFu },
  };
  const UINTN CaseFoldTableSize = sizeof(_caseFoldTable) / sizeof(Mapping);
#endif

  

  inline UINT32 FoldCodePoint(UINT32 cp)
  {
      for (UINTN i = 0; i < CaseFoldTableSize; i++)
      {
          if (_caseFoldTable[i].from == cp)
          {
              return _caseFoldTable[i].to;
		  }
      }

      return cp;
  }
}
