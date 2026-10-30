// CRI ADX (encoding 3, 4-bit ADPCM) decoder over the runtime/formats ADX header parser.
//
// Hand-derived from the public format description (big-endian header, 18-byte frames = a 16-bit
// scale word and 32 signed nibbles, high nibble first; a two-tap predictor whose coefficients come
// from the header's high-pass cutoff), with every arithmetic detail checked against the game's own
// EE decoder (docs/ANALYSIS/16_iop_audio_modules.md §8, obs):
//   * coefficients (ADX_GetCoefficient 0x539858): a = sqrt2 - cos(2*pi*cutoff/rate), b = sqrt2 - 1,
//     c = (a - sqrt((a+b)(a-b))) / b; k0 = trunc(2c * 4096), k1 = trunc(-c^2 * 4096) (float math,
//     cvt.w.s truncates toward zero);
//   * a frame whose scale word has bit 15 set ends decoding (ADX_DecodeMono4 0x53A410: the 0x8001
//     end marker / a header);
//   * effective scale = (scale & 0x1FFF) + 1 (unencrypted: the key state is 0);
//   * sample = clamp16(((k0*h1 + k1*h2) >> 12) + nibble * scale), arithmetic shift, 32-bit sum.
// Stereo files interleave one frame per channel. Loops use the v4 loop block (begin/end samples):
// the loop region repeats bit-exactly from the predictor state the first pass had at its start
// (inf: CRI's ADXT loop restart is not traced; the encoder makes the seam continuous).
// The live game path does NOT use this decoder: the EE decodes ADX itself and the IOP HLE plays
// that PCM. This is for --dump-wav of disc files, tools and tests.
#pragma once

#include <array>
#include <filesystem>
#include <span>
#include <vector>

#include "p3fes/ee_types.h"
#include "p3fes/formats/adx.h"

namespace p3fes::audio {

struct AdxCoefficients {
    s32 k0 = 0;
    s32 k1 = 0;
};
AdxCoefficients adx_coefficients(u32 cutoff_hz, u32 sample_rate);

inline constexpr std::size_t kAdxFrameBytes = 18;
inline constexpr std::size_t kAdxFrameSamples = 32;

// Decodes one 18-byte mono frame. Returns false -- and touches nothing -- when the scale word has
// bit 15 set (end marker).
bool adx_decode_frame(std::span<const std::byte> frame, const AdxCoefficients& k, s16& hist1, s16& hist2,
                      std::span<s16, kAdxFrameSamples> out);

class AdxDecoder {
public:
    // The decoder keeps a view of `file`; the bytes must outlive it. Only encoding 3, 4-bit,
    // 18-byte frames, 1 or 2 channels, unencrypted (flags bit 3 clear) are accepted.
    static formats::Result<AdxDecoder> open(formats::Bytes file);

    const formats::AdxHeader& header() const { return hdr_; }
    u32 channels() const { return hdr_.channels; }
    u32 sample_rate() const { return hdr_.sample_rate; }
    AdxCoefficients coefficients() const { return k_; }
    bool has_loop() const;
    // 0 = ignore the loop (play the file once), N > 0 = play the loop region N more times,
    // -1 = loop forever. Default 0.
    void set_loops(int loops) { loops_ = loops; }

    // Decodes up to out.size() / channels() frames (interleaved). Returns the frames written; 0 =
    // end of stream (sample count reached, end marker, or truncated data).
    std::size_t decode(std::span<s16> out);
    // Frames emitted so far (counting loop repetitions).
    u64 frames_out() const { return out_frames_; }

private:
    formats::Bytes file_;
    formats::AdxHeader hdr_{};
    AdxCoefficients k_{};
    int loops_ = 0;
    u64 out_frames_ = 0;
    u64 pos_ = 0;       // current sample index within the file's sample space
    u64 end_ = 0;       // sample index where the current pass stops
    std::array<s16, 2> h1_{}, h2_{};
    // Decoded current frame (per channel) and the frame index it holds.
    std::array<std::array<s16, kAdxFrameSamples>, 2> cur_{};
    u64 cur_frame_ = ~0ull;
    // Predictor state at the start of the loop's first frame, captured on the first pass.
    bool loop_saved_ = false;
    std::array<s16, 2> loop_h1_{}, loop_h2_{};
    bool ended_ = false;
    bool load_frame(u64 frame);
};

// Whole-file helpers (interleaved output).
formats::Result<std::vector<s16>> decode_adx(formats::Bytes file, int loops = 0);
// Decodes `file` into a WAV at `out` (parent directories created). false on a format or I/O error.
bool decode_adx_to_wav(formats::Bytes file, const std::filesystem::path& out, int loops = 0);

}  // namespace p3fes::audio
