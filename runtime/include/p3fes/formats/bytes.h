// Bounds-checked little/big-endian readers over std::span<const std::byte>.
//
// Reader uses a sticky fail flag instead of per-read results so header decoding
// reads like a struct definition; callers check `r.failed()` once afterwards.
#pragma once

#include <cstddef>
#include <cstring>
#include <span>
#include <string_view>

#include "p3fes/ee_types.h"

namespace p3fes::formats {

using Bytes = std::span<const std::byte>;

inline Bytes as_bytes(const void* p, std::size_t n) {
    return Bytes{static_cast<const std::byte*>(p), n};
}

inline bool in_bounds(Bytes b, std::size_t off, std::size_t n) {
    return off <= b.size() && n <= b.size() - off;
}

inline Bytes subspan_or_empty(Bytes b, std::size_t off, std::size_t n) {
    return in_bounds(b, off, n) ? b.subspan(off, n) : Bytes{};
}

// Unchecked fixed-width loads (callers must have verified bounds).
inline u8 ld_u8(Bytes b, std::size_t off) { return static_cast<u8>(b[off]); }
inline u16 ld_u16le(Bytes b, std::size_t off) {
    return static_cast<u16>(ld_u8(b, off) | (ld_u8(b, off + 1) << 8));
}
inline u32 ld_u32le(Bytes b, std::size_t off) {
    return static_cast<u32>(ld_u8(b, off)) | (static_cast<u32>(ld_u8(b, off + 1)) << 8) |
           (static_cast<u32>(ld_u8(b, off + 2)) << 16) | (static_cast<u32>(ld_u8(b, off + 3)) << 24);
}
inline u16 ld_u16be(Bytes b, std::size_t off) {
    return static_cast<u16>((ld_u8(b, off) << 8) | ld_u8(b, off + 1));
}
inline u32 ld_u32be(Bytes b, std::size_t off) {
    return (static_cast<u32>(ld_u8(b, off)) << 24) | (static_cast<u32>(ld_u8(b, off + 1)) << 16) |
           (static_cast<u32>(ld_u8(b, off + 2)) << 8) | static_cast<u32>(ld_u8(b, off + 3));
}

// Returns the bytes before the first NUL in `field` (or the whole field). Does
// not validate the character set; see is_printable_ascii().
inline std::string_view cstr_field(Bytes field) {
    const char* p = reinterpret_cast<const char*>(field.data());
    std::size_t n = 0;
    while (n < field.size() && p[n] != '\0') ++n;
    return std::string_view{p, n};
}

inline bool is_printable_ascii(std::string_view s) {
    for (unsigned char c : s)
        if (c < 0x20 || c > 0x7E) return false;
    return true;
}

constexpr std::size_t align_up(std::size_t v, std::size_t a) { return (v + a - 1) / a * a; }

class Reader {
public:
    explicit Reader(Bytes b, std::size_t pos = 0) : b_(b), pos_(pos) {}

    [[nodiscard]] bool failed() const { return fail_; }
    [[nodiscard]] std::size_t pos() const { return pos_; }
    [[nodiscard]] std::size_t remaining() const { return pos_ <= b_.size() ? b_.size() - pos_ : 0; }
    [[nodiscard]] Bytes buffer() const { return b_; }

    void seek(std::size_t pos) {
        if (pos > b_.size()) { fail_ = true; return; }
        pos_ = pos;
    }
    void skip(std::size_t n) { if (take(n)) {} }

    u8 u8_() { return take(1) ? ld_u8(b_, pos_ - 1) : 0; }
    u16 u16le() { return take(2) ? ld_u16le(b_, pos_ - 2) : 0; }
    u32 u32le() { return take(4) ? ld_u32le(b_, pos_ - 4) : 0; }
    u16 u16be() { return take(2) ? ld_u16be(b_, pos_ - 2) : 0; }
    u32 u32be() { return take(4) ? ld_u32be(b_, pos_ - 4) : 0; }

    // Returns an n-byte window or an empty span on failure.
    Bytes bytes(std::size_t n) { return take(n) ? b_.subspan(pos_ - n, n) : Bytes{}; }

    bool match(std::string_view magic) {
        Bytes got = bytes(magic.size());
        return !got.empty() && std::memcmp(got.data(), magic.data(), magic.size()) == 0;
    }

private:
    bool take(std::size_t n) {
        if (fail_ || !in_bounds(b_, pos_, n)) { fail_ = true; return false; }
        pos_ += n;
        return true;
    }

    Bytes b_;
    std::size_t pos_ = 0;
    bool fail_ = false;
};

}  // namespace p3fes::formats
