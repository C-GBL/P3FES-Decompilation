#include "p3fes/formats/formats.h"

namespace p3fes::formats {

std::string_view format_kind_name(FormatKind k) {
    switch (k) {
    case FormatKind::Unknown: return "unknown";
    case FormatKind::Pak: return "pak";
    case FormatKind::Bf: return "bf";
    case FormatKind::Bmd: return "bmd";
    case FormatKind::Tmx: return "tmx";
    case FormatKind::Rmd: return "rmd";
    case FormatKind::Adx: return "adx";
    case FormatKind::Afs: return "afs";
    }
    return "unknown";
}

FormatKind sniff(Bytes buf) {
    if (is_bf(buf)) return FormatKind::Bf;
    if (is_bmd(buf)) return FormatKind::Bmd;
    if (is_tmx(buf)) return FormatKind::Tmx;
    if (is_afs(buf)) return FormatKind::Afs;
    if (is_adx(buf)) return FormatKind::Adx;
    if (looks_like_rmd(buf)) return FormatKind::Rmd;
    if (looks_like_pak(buf)) return FormatKind::Pak;
    return FormatKind::Unknown;
}

}  // namespace p3fes::formats
