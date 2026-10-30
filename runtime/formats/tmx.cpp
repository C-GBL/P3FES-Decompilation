#include "p3fes/formats/tmx.h"

#include <cstring>

namespace p3fes::formats {

std::string_view tmx_psm_name(TmxPsm p) {
    switch (p) {
    case TmxPsm::CT32: return "PSMCT32";
    case TmxPsm::CT24: return "PSMCT24";
    case TmxPsm::CT16: return "PSMCT16";
    case TmxPsm::CT16S: return "PSMCT16S";
    case TmxPsm::T8: return "PSMT8";
    case TmxPsm::T4: return "PSMT4";
    case TmxPsm::T8H: return "PSMT8H";
    case TmxPsm::T4HL: return "PSMT4HL";
    case TmxPsm::T4HH: return "PSMT4HH";
    }
    return "?";
}

bool is_tmx(Bytes buf) {
    return buf.size() >= kTmxHeaderSize && ld_u16le(buf, 0) == 2 &&
           std::memcmp(buf.data() + 8, "TMX0", 4) == 0;
}

void tmx_unswizzle_clut8(Bytes in, std::span<u8> out) {
    // PS2 CSM1 layout for a 256-entry 32-bit CLUT: within each group of 32
    // colours, the second and third blocks of 8 are swapped.
    for (std::size_t i = 0; i < 256; ++i) {
        const std::size_t block = (i >> 3) & 3;  // 0..3 within the 32-colour group
        std::size_t src = i;
        if (block == 1) src = i + 8;
        else if (block == 2) src = i - 8;
        std::memcpy(out.data() + i * 4, in.data() + src * 4, 4);
    }
}

Result<TmxView> TmxView::parse(Bytes buf) {
    if (buf.size() < kTmxHeaderSize) return {FormatError::Truncated, "header (0x40 bytes)"};
    Reader r(buf);
    TmxView v;
    TmxHeader& h = v.hdr_;
    h.id = r.u16le();
    h.id2 = r.u16le();
    h.file_size = r.u32le();
    if (!r.match("TMX0")) return {FormatError::BadMagic, "TMX0"};
    const u32 pad = r.u32le();
    h.palette_count = r.u8_();
    h.palette_psm = static_cast<TmxPsm>(r.u8_());
    h.width = r.u16le();
    h.height = r.u16le();
    h.pixel_psm = static_cast<TmxPsm>(r.u8_());
    h.mip_count = r.u8_();
    h.mip_k = r.u8_();
    h.mip_l = r.u8_();
    h.wrap_mode = r.u16le();
    h.texture_id = r.u32le();
    h.clut_id = r.u32le();
    h.comment = cstr_field(r.bytes(28));
    if (r.failed()) return {FormatError::Truncated, "header"};
    if (h.id != 2 || pad != 0) return {FormatError::BadHeader, "id/pad"};
    if (h.width == 0 || h.height == 0) return {FormatError::BadHeader, "dimensions"};

    const u32 bpp = tmx_bits_per_pixel(h.pixel_psm);
    if (bpp == 0) return {FormatError::Unsupported, "pixel PSM"};
    const u32 colours = tmx_palette_colours(h.pixel_psm);
    if (colours != 0) {
        if (h.palette_count == 0) return {FormatError::BadHeader, "indexed with no palette"};
        const u32 pbpp = tmx_bits_per_pixel(h.palette_psm);
        if (pbpp == 0 || pbpp < 16) return {FormatError::Unsupported, "palette PSM"};
        v.palette_bytes_each_ = static_cast<std::size_t>(colours) * pbpp / 8;
    }
    if (h.mip_count != 0) return {FormatError::Unsupported, "mipmaps"};

    const std::size_t pal_total = v.palette_bytes_each_ * h.palette_count;
    const std::size_t pix_bytes = (static_cast<std::size_t>(h.width) * h.height * bpp + 7) / 8;
    if (!in_bounds(buf, kTmxHeaderSize, pal_total + pix_bytes)) return {FormatError::Overrun, "palette+pixels"};
    v.buf_ = buf;
    v.palettes_ = buf.subspan(kTmxHeaderSize, pal_total);
    v.pixels_ = buf.subspan(kTmxHeaderSize + pal_total, pix_bytes);
    return v;
}

Bytes TmxView::palette(std::size_t index) const {
    return subspan_or_empty(palettes_, index * palette_bytes_each_, palette_bytes_each_);
}

namespace {

inline u8 ps2_alpha_to_8(u8 a) {
    // GS alpha: 0x80 = 1.0. Values above 0x80 clamp.
    return a >= 0x80 ? 0xFF : static_cast<u8>(a * 2);
}

inline void put_ct32(const std::byte* src, u8* dst) {
    dst[0] = static_cast<u8>(src[0]);
    dst[1] = static_cast<u8>(src[1]);
    dst[2] = static_cast<u8>(src[2]);
    dst[3] = ps2_alpha_to_8(static_cast<u8>(src[3]));
}

inline void put_ct16(u16 v, u8* dst) {
    // PSMCT16: R 0-4, G 5-9, B 10-14, A 15 (1 = 0x80 alpha).
    dst[0] = static_cast<u8>(((v & 0x1F) * 255 + 15) / 31);
    dst[1] = static_cast<u8>((((v >> 5) & 0x1F) * 255 + 15) / 31);
    dst[2] = static_cast<u8>((((v >> 10) & 0x1F) * 255 + 15) / 31);
    dst[3] = (v & 0x8000) ? 0xFF : 0x00;
}

// Decodes a palette (any supported palette PSM) into linear RGBA8 entries.
bool palette_to_rgba(Bytes pal, TmxPsm psm, u32 colours, bool unswizzle, u8* out) {
    if (psm == TmxPsm::CT32) {
        u8 linear[1024];
        Bytes src = pal;
        if (unswizzle && colours == 256) {
            tmx_unswizzle_clut8(pal, std::span<u8>(linear, 1024));
            src = as_bytes(linear, 1024);
        }
        for (u32 i = 0; i < colours; ++i) put_ct32(src.data() + i * 4, out + i * 4);
        return true;
    }
    if (psm == TmxPsm::CT16 || psm == TmxPsm::CT16S) {
        for (u32 i = 0; i < colours; ++i) put_ct16(ld_u16le(pal, i * 2), out + i * 4);
        return true;
    }
    return false;
}

}  // namespace

FormatError TmxView::to_rgba8(std::span<u8> out, std::size_t palette_index) const {
    if (out.size() < rgba8_size()) return FormatError::Truncated;
    const std::size_t n = static_cast<std::size_t>(hdr_.width) * hdr_.height;
    const std::byte* px = pixels_.data();

    switch (hdr_.pixel_psm) {
    case TmxPsm::CT32:
        for (std::size_t i = 0; i < n; ++i) put_ct32(px + i * 4, out.data() + i * 4);
        return FormatError::None;
    case TmxPsm::CT24:
        for (std::size_t i = 0; i < n; ++i) {
            u8* d = out.data() + i * 4;
            d[0] = static_cast<u8>(px[i * 3]);
            d[1] = static_cast<u8>(px[i * 3 + 1]);
            d[2] = static_cast<u8>(px[i * 3 + 2]);
            d[3] = 0xFF;
        }
        return FormatError::None;
    case TmxPsm::CT16:
    case TmxPsm::CT16S:
        for (std::size_t i = 0; i < n; ++i) put_ct16(ld_u16le(pixels_, i * 2), out.data() + i * 4);
        return FormatError::None;
    case TmxPsm::T8:
    case TmxPsm::T4: {
        Bytes pal = palette(palette_index);
        if (pal.empty()) return FormatError::Overrun;
        const u32 colours = tmx_palette_colours(hdr_.pixel_psm);
        u8 rgba[256 * 4];
        if (!palette_to_rgba(pal, hdr_.palette_psm, colours, hdr_.pixel_psm == TmxPsm::T8, rgba))
            return FormatError::Unsupported;
        if (hdr_.pixel_psm == TmxPsm::T8) {
            for (std::size_t i = 0; i < n; ++i)
                std::memcpy(out.data() + i * 4, rgba + static_cast<u8>(px[i]) * 4, 4);
        } else {
            // T4: low nibble is the first (left) pixel.
            for (std::size_t i = 0; i < n; ++i) {
                const u8 b = static_cast<u8>(px[i >> 1]);
                const u8 idx = (i & 1) ? static_cast<u8>(b >> 4) : static_cast<u8>(b & 0xF);
                std::memcpy(out.data() + i * 4, rgba + idx * 4, 4);
            }
        }
        return FormatError::None;
    }
    default:
        return FormatError::Unsupported;  // T8H/T4HL/T4HH: not observed on this disc
    }
}

}  // namespace p3fes::formats
