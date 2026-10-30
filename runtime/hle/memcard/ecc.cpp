// PS2 memory-card ECC (ecc.h). Written from Ross Ridge's description; see the header.
#include "p3fes/hle/memcard/ecc.h"

#include <bit>

namespace p3fes::hle::memcard {
namespace {

// Bit groups of the column parity, one per code bit (bit 3 has no group and is always 0 -- hence the
// 0x77 mask of the stored byte).
constexpr u8 kColumnGroups[7] = {0x55, 0x33, 0x0F, 0x00, 0xAA, 0xCC, 0xF0};

constexpr u8 odd(u32 v) { return static_cast<u8>(std::popcount(v) & 1); }

struct Tables {
    std::array<u8, 256> column{};  // column-parity contribution of a byte value
    std::array<u8, 256> parity{};  // 1 when the byte has an odd number of set bits
};

constexpr Tables make_tables() {
    Tables t;
    for (u32 b = 0; b < 256; ++b) {
        u8 m = 0;
        for (u32 i = 0; i < 7; ++i) m = static_cast<u8>(m | (odd(b & kColumnGroups[i]) << i));
        t.column[b] = m;
        t.parity[b] = odd(b);
    }
    return t;
}

constexpr Tables kTables = make_tables();

}  // namespace

std::array<u8, 3> ecc_chunk(std::span<const u8, kEccChunk> chunk) {
    u8 cp = 0, lp0 = 0, lp1 = 0;
    for (u32 i = 0; i < kEccChunk; ++i) {
        const u8 b = chunk[i];
        cp = static_cast<u8>(cp ^ kTables.column[b]);
        if (kTables.parity[b]) {
            lp0 = static_cast<u8>(lp0 ^ ~i);
            lp1 = static_cast<u8>(lp1 ^ i);
        }
    }
    return {static_cast<u8>(~cp & 0x77), static_cast<u8>(~lp0 & 0x7F), static_cast<u8>(~lp1 & 0x7F)};
}

std::size_t ecc_compute(std::span<const u8> data, std::span<u8> out) {
    if (data.size() % kEccChunk != 0) return 0;
    const std::size_t chunks = data.size() / kEccChunk;
    if (out.size() < chunks * kEccBytesPerChunk) return 0;
    for (std::size_t c = 0; c < chunks; ++c) {
        const auto e = ecc_chunk(data.subspan(c * kEccChunk).first<kEccChunk>());
        out[c * 3 + 0] = e[0];
        out[c * 3 + 1] = e[1];
        out[c * 3 + 2] = e[2];
    }
    return chunks * kEccBytesPerChunk;
}

EccCheck ecc_check_chunk(std::span<u8, kEccChunk> chunk, std::span<const u8, 3> stored) {
    const auto calc = ecc_chunk(chunk);
    const u8 cp = static_cast<u8>((calc[0] ^ stored[0]) & 0x77);
    const u8 l0 = static_cast<u8>((calc[1] ^ stored[1]) & 0x7F);
    const u8 l1 = static_cast<u8>((calc[2] ^ stored[2]) & 0x7F);
    if (cp == 0 && l0 == 0 && l1 == 0) return EccCheck::Ok;
    // One flipped data bit at byte i, bit j changes the line parities by ~i and i (so they are
    // complementary) and three column bits: the low group bits select ~j, the high ones j.
    if ((l0 ^ l1) == 0x7F && (((cp >> 4) ^ cp) & 0x07) == 0x07) {
        const u32 byte = l1;
        const u32 bit = (cp >> 4) & 0x07;
        chunk[byte] = static_cast<u8>(chunk[byte] ^ (1u << bit));
        return EccCheck::CorrectedData;
    }
    if (std::popcount(static_cast<u32>(cp)) + std::popcount(static_cast<u32>(l0)) + std::popcount(static_cast<u32>(l1)) == 1)
        return EccCheck::CorrectedCode;
    return EccCheck::Uncorrectable;
}

EccCheck ecc_check(std::span<u8> data, std::span<const u8> stored) {
    if (data.size() % kEccChunk != 0 || stored.size() < data.size() / kEccChunk * kEccBytesPerChunk)
        return EccCheck::Uncorrectable;
    EccCheck worst = EccCheck::Ok;
    for (std::size_t c = 0; c < data.size() / kEccChunk; ++c) {
        const EccCheck r = ecc_check_chunk(data.subspan(c * kEccChunk).first<kEccChunk>(), stored.subspan(c * 3).first<3>());
        if (static_cast<u8>(r) > static_cast<u8>(worst)) worst = r;
    }
    return worst;
}

}  // namespace p3fes::hle::memcard
