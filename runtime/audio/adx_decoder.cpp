#include "p3fes/audio/adx_decoder.h"

#include <algorithm>
#include <cmath>

#include "p3fes/audio/wav.h"

namespace p3fes::audio {

AdxCoefficients adx_coefficients(u32 cutoff_hz, u32 sample_rate) {
    AdxCoefficients k;
    if (sample_rate == 0) return k;
    // ADX_GetCoefficient 0x539858 (obs): the same expression in single precision, results
    // converted with cvt.w.s (round toward zero). Evaluated here in double; for the cutoff/rate pairs
    // on this disc (500 Hz at 24/48 kHz, also 22.05/32/44.1 kHz) the pre-truncation values sit
    // >= 0.07 away from an integer, far outside float/double differences (der).
    const double sqrt2 = std::sqrt(2.0);
    const double a = sqrt2 - std::cos(2.0 * 3.14159265358979323846 * static_cast<double>(cutoff_hz) / sample_rate);
    const double b = sqrt2 - 1.0;
    const double c = (a - std::sqrt((a + b) * (a - b))) / b;
    k.k0 = static_cast<s32>(std::trunc(c * 2.0 * 4096.0));
    k.k1 = static_cast<s32>(std::trunc(-(c * c) * 4096.0));
    return k;
}

bool adx_decode_frame(std::span<const std::byte> frame, const AdxCoefficients& k, s16& hist1, s16& hist2,
                      std::span<s16, kAdxFrameSamples> out) {
    if (frame.size() < kAdxFrameBytes) return false;
    const u32 raw = (static_cast<u32>(frame[0]) << 8) | static_cast<u32>(frame[1]);  // big-endian scale
    if (raw & 0x8000u) return false;  // end marker / header (0x53A49C)
    const s32 scale = static_cast<s32>(raw & 0x1FFFu) + 1;  // (scale ^ key) & 0x1FFF, + 1 (0x53A4BC)
    s32 h1 = hist1, h2 = hist2;
    std::size_t o = 0;
    for (std::size_t i = 2; i < kAdxFrameBytes; ++i) {
        const u32 byte = static_cast<u32>(frame[i]);
        for (const u32 nib : {byte >> 4, byte & 0xFu}) {  // high nibble first (0x53A4F8)
            const s32 d = static_cast<s32>(nib ^ 8u) - 8;  // signed 4-bit
            // 32-bit products and sum, arithmetic shift (0x53A4E8..0x53A510).
            const s32 pred = (k.k0 * h1 + k.k1 * h2) >> 12;
            const s32 s = std::clamp<s32>(pred + d * scale, -32768, 32767);
            h2 = h1;
            h1 = s;
            out[o++] = static_cast<s16>(s);
        }
    }
    hist1 = static_cast<s16>(h1);
    hist2 = static_cast<s16>(h2);
    return true;
}

formats::Result<AdxDecoder> AdxDecoder::open(formats::Bytes file) {
    auto info = formats::parse_adx(file);
    if (!info) return info.error();
    const formats::AdxHeader& h = info->header;
    if (h.encoding != 3) return {formats::FormatError::Unsupported, "ADX encoding (only 3)"};
    if (h.block_size != kAdxFrameBytes || h.sample_bit_depth != 4) return {formats::FormatError::Unsupported, "ADX frame shape"};
    if (h.channels < 1 || h.channels > 2) return {formats::FormatError::Unsupported, "ADX channel count"};
    if (h.flags & 0x08u) return {formats::FormatError::Unsupported, "encrypted ADX"};
    if (h.sample_rate == 0) return {formats::FormatError::BadHeader, "sample rate"};
    AdxDecoder d;
    d.file_ = file;
    d.hdr_ = h;
    d.k_ = adx_coefficients(h.highpass_cutoff, h.sample_rate);
    d.end_ = h.sample_count;
    return d;
}

bool AdxDecoder::has_loop() const {
    return hdr_.loop && hdr_.loop->enabled != 0 && hdr_.loop->begin_sample < hdr_.loop->end_sample &&
           hdr_.loop->end_sample <= hdr_.sample_count;
}

bool AdxDecoder::load_frame(u64 frame) {
    const u32 ch = hdr_.channels;
    if (has_loop() && !loop_saved_ && frame == hdr_.loop->begin_sample / kAdxFrameSamples) {
        loop_saved_ = true;
        loop_h1_ = h1_;
        loop_h2_ = h2_;
    }
    for (u32 c = 0; c < ch; ++c) {
        const u64 off = hdr_.data_offset() + (frame * ch + c) * kAdxFrameBytes;
        if (off + kAdxFrameBytes > file_.size()) return false;  // truncated body
        if (!adx_decode_frame(file_.subspan(static_cast<std::size_t>(off), kAdxFrameBytes), k_, h1_[c], h2_[c],
                              std::span<s16, kAdxFrameSamples>(cur_[c])))
            return false;
    }
    cur_frame_ = frame;
    return true;
}

std::size_t AdxDecoder::decode(std::span<s16> out) {
    const u32 ch = hdr_.channels;
    const std::size_t cap = out.size() / ch;
    std::size_t n = 0;
    if (pos_ == 0 && out_frames_ == 0 && loops_ != 0 && has_loop()) end_ = hdr_.loop->end_sample;
    while (n < cap && !ended_) {
        if (pos_ >= end_) {
            if (loops_ != 0 && has_loop() && loop_saved_) {
                if (loops_ > 0) --loops_;
                pos_ = hdr_.loop->begin_sample;
                h1_ = loop_h1_;
                h2_ = loop_h2_;
                cur_frame_ = ~0ull;
                end_ = loops_ == 0 ? hdr_.sample_count : hdr_.loop->end_sample;
                continue;
            }
            ended_ = true;
            break;
        }
        const u64 frame = pos_ / kAdxFrameSamples;
        if (cur_frame_ != frame && !load_frame(frame)) {
            ended_ = true;
            break;
        }
        const std::size_t in_frame = static_cast<std::size_t>(pos_ % kAdxFrameSamples);
        const std::size_t take = static_cast<std::size_t>(
            std::min<u64>({kAdxFrameSamples - in_frame, end_ - pos_, static_cast<u64>(cap - n)}));
        for (std::size_t i = 0; i < take; ++i)
            for (u32 c = 0; c < ch; ++c) out[(n + i) * ch + c] = cur_[c][in_frame + i];
        n += take;
        pos_ += take;
    }
    out_frames_ += n;
    return n;
}

formats::Result<std::vector<s16>> decode_adx(formats::Bytes file, int loops) {
    if (loops < 0) return {formats::FormatError::Unsupported, "infinite loop count"};
    auto d = AdxDecoder::open(file);
    if (!d) return d.error();
    d->set_loops(loops);
    std::vector<s16> pcm;
    std::vector<s16> chunk(4096 * d->channels());
    for (;;) {
        const std::size_t got = d->decode(chunk);
        if (got == 0) break;
        pcm.insert(pcm.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(got * d->channels()));
    }
    return pcm;
}

bool decode_adx_to_wav(formats::Bytes file, const std::filesystem::path& out, int loops) {
    auto d = AdxDecoder::open(file);
    if (!d || loops < 0) return false;
    d->set_loops(loops);
    WavWriter w;
    if (!w.open(out, d->sample_rate(), static_cast<u16>(d->channels()))) return false;
    std::vector<s16> chunk(4096 * d->channels());
    for (;;) {
        const std::size_t got = d->decode(chunk);
        if (got == 0) break;
        w.write(std::span<const s16>(chunk.data(), got * d->channels()));
    }
    return w.close();
}

}  // namespace p3fes::audio
