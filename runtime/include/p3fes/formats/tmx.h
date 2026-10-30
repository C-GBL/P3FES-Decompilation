// Atlus TMX texture ("TMX0" at +8; 645 top-level files + many inside PAKs).
//
// 0x40-byte header, then palette(s), then pixels (docs/FORMATS.md §4):
//   +00 u16 id (2)      +02 u16 0          +04 u32 file size   +08 "TMX0"
//   +0C u32 0           +10 u8 palette count  +11 u8 palette PSM (0 = CT32)
//   +12 u16 width       +14 u16 height     +16 u8 pixel PSM    +17 u8 mip count
//   +18 u8 mip K        +19 u8 mip L       +1A u16 wrap (0xFF00)  +1C u32 texture id
//   +20 u32 clut id     +24 char comment[28]
// The T8 palette is stored CSM1-swizzled (PS2 CLUT): 8-colour blocks 1 and 2 of
// every 32 colours are swapped. to_rgba8() unswizzles it. PS2 alpha 0x80 = opaque.
#pragma once

#include <span>
#include <string_view>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

// GS pixel storage modes as used by TMX (same numbering as the GS PSM field).
enum class TmxPsm : u8 {
    CT32 = 0x00,
    CT24 = 0x01,
    CT16 = 0x02,
    CT16S = 0x0A,
    T8 = 0x13,
    T4 = 0x14,
    T8H = 0x1B,
    T4HL = 0x24,
    T4HH = 0x2C,
};

constexpr u32 tmx_bits_per_pixel(TmxPsm p) {
    switch (p) {
    case TmxPsm::CT32: return 32;
    case TmxPsm::CT24: return 24;
    case TmxPsm::CT16: case TmxPsm::CT16S: return 16;
    case TmxPsm::T8: case TmxPsm::T8H: return 8;
    case TmxPsm::T4: case TmxPsm::T4HL: case TmxPsm::T4HH: return 4;
    }
    return 0;
}
constexpr u32 tmx_palette_colours(TmxPsm p) {
    switch (p) {
    case TmxPsm::T8: case TmxPsm::T8H: return 256;
    case TmxPsm::T4: case TmxPsm::T4HL: case TmxPsm::T4HH: return 16;
    default: return 0;
    }
}
std::string_view tmx_psm_name(TmxPsm p);

struct TmxHeader {
    u16 id = 0;
    u16 id2 = 0;
    u32 file_size = 0;
    u8 palette_count = 0;
    TmxPsm palette_psm = TmxPsm::CT32;
    u16 width = 0;
    u16 height = 0;
    TmxPsm pixel_psm = TmxPsm::CT32;
    u8 mip_count = 0;
    u8 mip_k = 0;
    u8 mip_l = 0;
    u16 wrap_mode = 0;
    u32 texture_id = 0;
    u32 clut_id = 0;
    std::string_view comment;  // up to 28 chars
};

inline constexpr std::size_t kTmxHeaderSize = 0x40;

class TmxView {
public:
    static Result<TmxView> parse(Bytes buf);

    [[nodiscard]] const TmxHeader& header() const { return hdr_; }
    [[nodiscard]] std::size_t palette_bytes_each() const { return palette_bytes_each_; }
    [[nodiscard]] Bytes palette(std::size_t index) const;  // raw, as stored (swizzled for T8)
    [[nodiscard]] Bytes pixels() const { return pixels_; }
    [[nodiscard]] std::size_t rgba8_size() const {
        return static_cast<std::size_t>(hdr_.width) * hdr_.height * 4;
    }
    // Converts to tightly packed RGBA8 (alpha rescaled 0x80 -> 0xFF). `out` must
    // hold rgba8_size() bytes. Returns Unsupported for PSMs without a converter.
    [[nodiscard]] FormatError to_rgba8(std::span<u8> out, std::size_t palette_index = 0) const;

private:
    TmxHeader hdr_;
    Bytes buf_;
    Bytes palettes_;
    Bytes pixels_;
    std::size_t palette_bytes_each_ = 0;
};

bool is_tmx(Bytes buf);

// Unswizzles a 256-entry 32-bit PS2 CLUT (CSM1) into linear order; `in` and
// `out` are 1024 bytes each. Exposed for tests.
void tmx_unswizzle_clut8(Bytes in, std::span<u8> out);

}  // namespace p3fes::formats
