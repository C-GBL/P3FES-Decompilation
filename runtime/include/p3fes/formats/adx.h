// CRI ADX header (BGM/*.ADX, DATA/SOUND*/**.ADX, AFS members). Big-endian.
// Header parsing and framing only; no ADPCM decoding (docs/FORMATS.md §6).
#pragma once

#include <optional>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

struct AdxLoop {
    u32 alignment_samples = 0;
    u32 enabled = 0;
    u32 begin_sample = 0;
    u32 begin_byte = 0;
    u32 end_sample = 0;
    u32 end_byte = 0;
};

struct AdxHeader {
    u16 copyright_offset = 0;  // "(c)CRI" sits at copyright_offset-2; data at +4
    u8 encoding = 0;           // 3 = standard ADX ADPCM (only value on this disc)
    u8 block_size = 0;         // 18
    u8 sample_bit_depth = 0;   // 4
    u8 channels = 0;           // 1 or 2
    u32 sample_rate = 0;       // 24000 / 48000 observed
    u32 sample_count = 0;
    u16 highpass_cutoff = 0;   // 500
    u8 version = 0;            // 3 or 4
    u8 flags = 0;              // 0x08 would mean encrypted; 0 on this disc
    std::optional<AdxLoop> loop;  // present only when the header is long enough

    [[nodiscard]] u32 data_offset() const { return static_cast<u32>(copyright_offset) + 4; }
    [[nodiscard]] u32 frame_count() const { return (sample_count + 31) / 32; }  // 32 samples per block
    [[nodiscard]] u64 expected_body_bytes() const {
        return static_cast<u64>(frame_count()) * block_size * channels;
    }
};

struct AdxInfo {
    AdxHeader header;
    std::size_t file_size = 0;
    bool copyright_ok = false;     // "(c)CRI" found where expected
    bool body_fits = false;        // data_offset + expected_body_bytes <= file_size
    bool end_marker = false;       // 0x8001 end block directly after the body
};

bool is_adx(Bytes buf);
Result<AdxInfo> parse_adx(Bytes buf);

}  // namespace p3fes::formats
