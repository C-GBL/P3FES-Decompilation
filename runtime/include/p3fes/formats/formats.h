// Umbrella header for runtime/formats/ plus a magic-based sniffer used by the
// manifest probe and by container consumers that must decide what an entry is.
#pragma once

#include <string_view>

#include "p3fes/formats/adx.h"
#include "p3fes/formats/afs.h"
#include "p3fes/formats/bf.h"
#include "p3fes/formats/bmd.h"
#include "p3fes/formats/bytes.h"
#include "p3fes/formats/pak.h"
#include "p3fes/formats/result.h"
#include "p3fes/formats/rmd.h"
#include "p3fes/formats/tmx.h"

namespace p3fes::formats {

enum class FormatKind : u8 {
    Unknown = 0,
    Pak,   // Atlus name-first container
    Bf,    // FLW0
    Bmd,   // MSG1
    Tmx,   // TMX0
    Rmd,   // RenderWare stream (Atlus tag or RW chunk first)
    Adx,   // CRI ADX
    Afs,   // CRI AFS
};

std::string_view format_kind_name(FormatKind k);

// Header-only identification; checks magic/tag bytes (and for PAK the first
// entry header). Order: Bf, Bmd, Tmx, Afs, Adx, Rmd, Pak.
FormatKind sniff(Bytes buf);

}  // namespace p3fes::formats
