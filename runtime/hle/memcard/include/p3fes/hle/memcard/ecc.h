// PS2 memory-card ECC: a Hamming-style code of 3 bytes per 128-byte chunk, 12 bytes per 512-byte page,
// stored at the start of the page's 16-byte spare area.
//
// Source: Ross Ridge, "PlayStation 2 Memory Card File System" (the ECC section: column parity over bit
// groups 0x55/0x33/0x0F/0xAA/0xCC/0xF0 of every byte, two 7-bit line parities over the indices of the
// bytes with odd parity, all stored inverted). Cross-checked against the game's own IOP driver: the
// generator MC2_S1.IRX runs before every page program (.text 0x2BDC, disc LIB31/MC2_S1.IRX) produces the
// same three bytes -- column byte masked 0x77, line bytes 0x7F; the module's checker (.text 0x2C78) is a
// stub that always returns 1, so the game never corrects on read (obs). Written from the description,
// no code copied.
#pragma once

#include <array>
#include <cstddef>
#include <span>

#include "p3fes/ee_types.h"

namespace p3fes::hle::memcard {

inline constexpr std::size_t kEccChunk = 128;
inline constexpr std::size_t kEccBytesPerChunk = 3;

// ECC of one 128-byte chunk: {column parity, line parity 0, line parity 1}.
std::array<u8, 3> ecc_chunk(std::span<const u8, kEccChunk> chunk);

// ECC of `data` (a multiple of 128 bytes) into `out` (3 bytes per chunk). Returns the bytes written,
// 0 if the sizes do not fit.
std::size_t ecc_compute(std::span<const u8> data, std::span<u8> out);

enum class EccCheck : u8 {
    Ok,             // data and code agree
    CorrectedData,  // one data bit was wrong and has been flipped back
    CorrectedCode,  // one bit of the stored code was wrong; the data is fine
    Uncorrectable,  // more than one bit differs
};

// Verifies one chunk against its stored code and corrects a single-bit data error in place.
EccCheck ecc_check_chunk(std::span<u8, kEccChunk> chunk, std::span<const u8, 3> stored);

// Whole page (`data` a multiple of 128 bytes, `stored` 3 bytes per chunk): the worst chunk result.
EccCheck ecc_check(std::span<u8> data, std::span<const u8> stored);

}  // namespace p3fes::hle::memcard
