#include "elf_image.h"

#include <cstdio>
#include <cstring>

namespace p3fes::recomp {

// ----------------------------------------------------------------------------------------------
// SHA-256 (FIPS 180-4), straightforward single-shot implementation.

namespace {

constexpr std::uint32_t kK[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

inline std::uint32_t rotr(std::uint32_t x, unsigned n) noexcept { return (x >> n) | (x << (32u - n)); }

void sha256_block(std::uint32_t h[8], const std::uint8_t* p) noexcept {
    std::uint32_t w[64];
    for (int i = 0; i < 16; ++i)
        w[i] = (std::uint32_t(p[4 * i]) << 24) | (std::uint32_t(p[4 * i + 1]) << 16) |
               (std::uint32_t(p[4 * i + 2]) << 8) | std::uint32_t(p[4 * i + 3]);
    for (int i = 16; i < 64; ++i) {
        const std::uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
        const std::uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
    std::uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
    for (int i = 0; i < 64; ++i) {
        const std::uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
        const std::uint32_t ch = (e & f) ^ (~e & g);
        const std::uint32_t t1 = hh + S1 + ch + kK[i] + w[i];
        const std::uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
        const std::uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        const std::uint32_t t2 = S0 + maj;
        hh = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
    }
    h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
}

std::uint32_t rd32(const std::uint8_t* p) noexcept {
    return std::uint32_t(p[0]) | (std::uint32_t(p[1]) << 8) | (std::uint32_t(p[2]) << 16) | (std::uint32_t(p[3]) << 24);
}
std::uint16_t rd16(const std::uint8_t* p) noexcept { return std::uint16_t(p[0] | (p[1] << 8)); }

}  // namespace

void sha256_hex(const std::uint8_t* data, std::size_t len, char out_hex[65]) noexcept {
    std::uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                          0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    std::size_t off = 0;
    for (; off + 64 <= len; off += 64) sha256_block(h, data + off);
    std::uint8_t tail[128] = {};
    const std::size_t rem = len - off;
    std::memcpy(tail, data + off, rem);
    tail[rem] = 0x80;
    const std::size_t total = rem + 1 <= 56 ? 64 : 128;
    const std::uint64_t bits = std::uint64_t(len) * 8u;
    for (int i = 0; i < 8; ++i) tail[total - 1 - i] = std::uint8_t(bits >> (8 * i));
    sha256_block(h, tail);
    if (total == 128) sha256_block(h, tail + 64);
    static constexpr char kHex[] = "0123456789abcdef";
    for (int i = 0; i < 8; ++i)
        for (int b = 0; b < 4; ++b) {
            const std::uint8_t v = std::uint8_t(h[i] >> (24 - 8 * b));
            out_hex[8 * i + 2 * b] = kHex[v >> 4];
            out_hex[8 * i + 2 * b + 1] = kHex[v & 15];
        }
    out_hex[64] = '\0';
}

// ----------------------------------------------------------------------------------------------

ElfImage::LoadResult ElfImage::load(const char* path, const char* expected_sha256_hex) {
    LoadResult r;
    bytes_.clear();
    segments_.clear();
    entry_ = 0;

    std::FILE* f = std::fopen(path, "rb");
    if (!f) { r.error = "cannot open ELF"; return r; }
    std::vector<std::uint8_t> data;
    {
        std::uint8_t chunk[1 << 16];
        std::size_t n;
        while ((n = std::fread(chunk, 1, sizeof chunk, f)) > 0) data.insert(data.end(), chunk, chunk + n);
        const bool read_error = std::ferror(f) != 0;
        std::fclose(f);
        if (read_error) { r.error = "read error"; return r; }
    }

    sha256_hex(data.data(), data.size(), r.sha256_hex);
    if (expected_sha256_hex && std::strcmp(r.sha256_hex, expected_sha256_hex) != 0) {
        r.error = "SHA-256 mismatch: not the expected SLUS_216.21 (docs/INVENTORY.md)";
        return r;
    }

    if (data.size() < 52 || std::memcmp(data.data(), "\x7f" "ELF", 4) != 0) { r.error = "not an ELF"; return r; }
    if (data[4] != 1 || data[5] != 1) { r.error = "not ELF32 little-endian"; return r; }
    if (rd16(&data[18]) != 8) { r.error = "e_machine is not MIPS"; return r; }
    const std::uint32_t phoff = rd32(&data[28]);
    const std::uint16_t phentsize = rd16(&data[42]), phnum = rd16(&data[44]);
    if (phentsize < 32 || std::size_t(phoff) + std::size_t(phentsize) * phnum > data.size()) {
        r.error = "program header table out of range";
        return r;
    }
    for (std::uint16_t i = 0; i < phnum; ++i) {
        const std::uint8_t* ph = &data[phoff + std::size_t(phentsize) * i];
        if (rd32(ph) != 1) continue;  // PT_LOAD
        ElfSegment s;
        s.offset = rd32(ph + 4);
        s.vaddr = rd32(ph + 8);
        s.filesz = rd32(ph + 16);
        s.memsz = rd32(ph + 20);
        s.flags = rd32(ph + 24);
        if (std::uint64_t(s.offset) + s.filesz > data.size()) { r.error = "PT_LOAD exceeds file"; return r; }
        segments_.push_back(s);
    }
    if (segments_.empty()) { r.error = "no PT_LOAD"; return r; }
    entry_ = rd32(&data[24]);
    bytes_ = std::move(data);
    return r;
}

std::optional<std::size_t> ElfImage::file_offset(std::uint32_t va) const noexcept {
    for (const ElfSegment& s : segments_)
        if (s.filesz && va >= s.vaddr && va - s.vaddr < s.filesz) return std::size_t(s.offset) + (va - s.vaddr);
    return std::nullopt;
}

const std::uint8_t* ElfImage::bytes_at(std::uint32_t va, std::size_t len) const noexcept {
    for (const ElfSegment& s : segments_)
        if (s.filesz && va >= s.vaddr && va - s.vaddr < s.filesz && std::size_t(s.filesz) - (va - s.vaddr) >= len)
            return bytes_.data() + s.offset + (va - s.vaddr);
    return nullptr;
}

std::optional<std::uint32_t> ElfImage::word_at(std::uint32_t va) const noexcept {
    if (va & 3u) return std::nullopt;
    const std::uint8_t* p = bytes_at(va, 4);
    if (!p) return std::nullopt;
    return rd32(p);
}

}  // namespace p3fes::recomp
