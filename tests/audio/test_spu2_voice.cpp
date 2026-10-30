// SPU2 voice model (runtime/audio/spu2_voice.cpp, ADR-0014 milestone 2): hand-computed ADPCM vectors for the
// five filters, shifts, clamping and the loop flags; the envelope's phase transitions and rate formula; pitch
// 0x1000 reproducing a block one sample per frame and 0x800 interpolating; the end flag stopping a one-shot
// and setting ENDX; loop repeat; the mixer's pass grid, latency, stream sum, clipping and gaps; and, with
// extracted/ present, the COMSE bank's first Vagi entry played through the model against a direct decode of
// the same bytes.
#include <doctest.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

#include "p3fes/audio/spu2_voice.h"

using namespace p3fes;
using namespace p3fes::audio;

namespace {

std::filesystem::path extracted_dir() {
    if (const char* env = std::getenv("P3FES_EXTRACTED"); env && *env) return env;
    return P3FES_EXTRACTED_DIR;
}
std::optional<std::vector<u8>> read_file(const std::filesystem::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return std::nullopt;
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

// A 16-byte block from 28 nibbles (low nibble first, as the hardware reads them).
std::vector<u8> block(u8 shift, u8 filter, u8 flags, const std::vector<u8>& nibbles) {
    std::vector<u8> b(16, 0);
    b[0] = static_cast<u8>((shift & 0xF) | (filter << 4));
    b[1] = flags;
    for (std::size_t i = 0; i < 28; ++i) {
        const u8 n = i < nibbles.size() ? nibbles[i] & 0xF : 0;
        b[2 + i / 2] |= static_cast<u8>(n << ((i & 1) * 4));
    }
    return b;
}
void put(Spu2Voices& v, u32 addr, const std::vector<u8>& bytes) { std::memcpy(v.ram().data() + addr, bytes.data(), bytes.size()); }

s32 q15(s32 a, s32 b) { return (a * b) >> 15; }
// The chain gain of a core-0 voice at voice volume 0x3FFF with both cores' MVOL at 0x3FFF and libsd's init
// image (AVOL1 0x7FFF, MMIX open): voice x MVOL0 x AVOL1 x MVOL1, each a Q15 stage as the model applies them.
const s32 kCore0Gain = q15(spu2_fixed_gain(0x3FFF), q15(q15(spu2_fixed_gain(0x3FFF), spu2_input_gain(0x7FFF)), spu2_fixed_gain(0x3FFF)));
// The model's output arithmetic for a sample at envelope level `env` on such a voice.
s32 expect_out(s32 sample, s32 env) {
    const s32 out = sample * env >> 15;
    return (out * kCore0Gain) >> 15;
}

struct CaptureSink final : AudioSink {
    struct Push {
        u64 first = 0;
        std::vector<s16> data;
    };
    std::vector<Push> pushes;
    void push(u64 first_frame, std::span<const s16> interleaved) override { pushes.push_back({first_frame, std::vector<s16>(interleaved.begin(), interleaved.end())}); }
};

// Keys voice 0 of core 0 at `ssa` with full volume, attack rate 0, sustain level 0xF (the envelope reaches
// 0x7FFF after three frames and stays), release rate 0; both cores' MVOL at 0x3FFF (core 0 is heard through
// core 1); linear interpolation so the sample values can be checked exactly (the gaussian path has its own case).
void key(Spu2Voices& v, u32 ssa, u16 pitch, u16 adsr1 = 0x000F, u16 adsr2 = 0) {
    v.set_interpolation(Interpolation::Linear);
    v.set_core_param(0, sd_code::kMvoll, 0x3FFF);
    v.set_core_param(0, sd_code::kMvolr, 0x3FFF);
    v.set_core_param(1, sd_code::kMvoll, 0x3FFF);
    v.set_core_param(1, sd_code::kMvolr, 0x3FFF);
    v.set_voice_param(0, 0, sd_code::kVoll, 0x3FFF);
    v.set_voice_param(0, 0, sd_code::kVolr, 0x3FFF);
    v.set_voice_param(0, 0, sd_code::kPitch, pitch);
    v.set_voice_param(0, 0, sd_code::kAdsr1, adsr1);
    v.set_voice_param(0, 0, sd_code::kAdsr2, adsr2);
    v.set_voice_addr(0, 0, sd_code::kSsa, ssa);
    v.key_on(0, 1);
}
std::vector<s32> render(Spu2Voices& v, u32 frames) {
    std::vector<s32> acc(2u * frames, 0);
    v.render(frames, acc.data());
    return acc;
}
// One frame at a time, recording the envelope level each frame was scaled by (ENVX after the step).
struct Frame {
    s32 l = 0, r = 0, env = 0;
};
std::vector<Frame> render_each(Spu2Voices& v, u32 frames) {
    std::vector<Frame> out;
    for (u32 f = 0; f < frames; ++f) {
        s32 acc[2] = {0, 0};
        v.render(1, acc);
        out.push_back({acc[0], acc[1], static_cast<s16>(v.voice_param(0, 0, sd_code::kEnvx))});
    }
    return out;
}

}  // namespace

TEST_CASE("ADPCM: filter 0 nibbles are their signed values; filters 1-4 predict; shift and clamp; flags") {
    s32 s1 = 0, s2 = 0;
    s16 out[28];
    // Filter 0, shift 12: nibble n -> n (0..7) or n - 16 (8..15); the pattern repeats past 16.
    std::vector<u8> nib;
    for (u8 i = 0; i < 28; ++i) nib.push_back(i & 0xF);
    CHECK(adpcm_decode_block(block(12, 0, 0, nib).data(), s1, s2, out) == 0);
    for (int i = 0; i < 28; ++i) CHECK(out[i] == ((i & 0xF) < 8 ? (i & 0xF) : (i & 0xF) - 16));
    CHECK(s1 == out[27]);
    CHECK(s2 == out[26]);
    // Shift 0: nibble 7 -> 0x7000, nibble 9 -> (s16)0x9000 = -28672; shift 11: nibble 1 -> 2.
    s1 = s2 = 0;
    adpcm_decode_block(block(0, 0, 0, {7, 9}).data(), s1, s2, out);
    CHECK(out[0] == 28672);
    CHECK(out[1] == -28672);
    s1 = s2 = 0;
    adpcm_decode_block(block(11, 0, 0, {1}).data(), s1, s2, out);
    CHECK(out[0] == 2);
    // Filter 1 (60, 0) on {7, 7, 0, 0}: 7; 7 + (60*7+32)>>6 = 14; (60*14+32)>>6 = 13; (60*13+32)>>6 = 12.
    s1 = s2 = 0;
    adpcm_decode_block(block(12, 1, 0, {7, 7, 0, 0}).data(), s1, s2, out);
    CHECK(out[0] == 7);
    CHECK(out[1] == 14);
    CHECK(out[2] == 13);
    CHECK(out[3] == 12);
    // Filter 2 (115, -52) on {7, 0, 0}: 7; (805+32)>>6 = 13; (115*13 - 52*7 + 32)>>6 = 18.
    s1 = s2 = 0;
    adpcm_decode_block(block(12, 2, 0, {7, 0, 0}).data(), s1, s2, out);
    CHECK(out[1] == 13);
    CHECK(out[2] == 18);
    // Filter 3 (98, -55): (686+32)>>6 = 11; (98*11 - 55*7 + 32)>>6 = 11.
    s1 = s2 = 0;
    adpcm_decode_block(block(12, 3, 0, {7, 0, 0}).data(), s1, s2, out);
    CHECK(out[1] == 11);
    CHECK(out[2] == 11);
    // Filter 4 (122, -60): (854+32)>>6 = 13; (122*13 - 60*7 + 32)>>6 = 18.
    s1 = s2 = 0;
    adpcm_decode_block(block(12, 4, 0, {7, 0, 0}).data(), s1, s2, out);
    CHECK(out[1] == 13);
    CHECK(out[2] == 18);
    // History carries across blocks: a second filter-1 block of zeros continues the decay from 12.
    s1 = 12;
    s2 = 13;
    adpcm_decode_block(block(12, 1, 0, {0}).data(), s1, s2, out);
    CHECK(out[0] == (60 * 12 + 32) >> 6);  // 11
    // Clamp: shift 0 nibble 7 twice with filter 1: 28672 + (60*28672+32)>>6 = 55552 -> 32767.
    s1 = s2 = 0;
    adpcm_decode_block(block(0, 1, 0, {7, 7}).data(), s1, s2, out);
    CHECK(out[1] == 32767);
    // Flags are returned verbatim; a filter nibble above 4 is treated as 4.
    CHECK(adpcm_decode_block(block(12, 0, 0x07, {}).data(), s1, s2, out) == 7);
    s1 = s2 = 0;
    adpcm_decode_block(block(12, 9, 0, {7, 0, 0}).data(), s1, s2, out);
    CHECK(out[1] == 13);
    // adpcm_decode over consecutive blocks equals the per-block decode with carried history.
    std::vector<u8> two = block(12, 1, 0, {7, 7});
    const auto b2 = block(12, 1, 0, {0});
    two.insert(two.end(), b2.begin(), b2.end());
    const auto all = adpcm_decode(two, 2);
    REQUIRE(all.size() == 56);
    CHECK(all[0] == 7);
    CHECK(all[1] == 14);
    CHECK(all[2] == 13);
}

TEST_CASE("Envelope: attack, decay, sustain and release follow the rate formula and the phase rules") {
    Spu2Envelope e;
    // Rate 0 linear increase: +0x3800 per frame.
    e.step(0, false, false);
    CHECK(e.level == 0x3800);
    e.step(0, false, false);
    CHECK(e.level == 0x7000);
    e.step(0, false, false);
    CHECK(e.level == 0x7FFF);  // clamped
    // Rate 48 (shift 12): one step of 7 every 2 frames; rate 50: 5 every 2 frames; rate 4: 7 << 10 per frame.
    Spu2Envelope f;
    for (int i = 0; i < 4; ++i) f.step(48, false, false);
    CHECK(f.level == 14);
    Spu2Envelope g;
    for (int i = 0; i < 4; ++i) g.step(50, false, false);
    CHECK(g.level == 10);
    Spu2Envelope h;
    h.step(4, false, false);
    CHECK(h.level == 7 << 10);
    // Exponential decrease scales the step by level / 0x8000: from 0x7FFF, rate 0 -> -16383.
    Spu2Envelope d;
    d.level = 0x7FFF;
    d.step(0, true, true);
    CHECK(d.level == 0x7FFF - 16383);
    // ... and never sticks: at a level where the scaled step would be 0 it still moves by one.
    Spu2Envelope tiny;
    tiny.level = 3;
    for (int i = 0; i < (1 << 20); ++i) tiny.step(124, true, true);  // shift 31: one step per 2^20 frames
    CHECK(tiny.level == 2);
    // Exponential increase slows four times above 0x6000.
    Spu2Envelope x;
    x.level = 0x6001;
    x.step(0, false, true);
    CHECK(x.level == 0x6001);  // 1 of 4 cycles
    x.step(0, false, true);
    x.step(0, false, true);
    x.step(0, false, true);
    CHECK(x.level == 0x7FFF);

    // Through a voice: silent looping sample, adsr1 = AR 0 / DR 0 / SL 7, adsr2 = SR 0 linear decrease / RR 0.
    Spu2Voices v;
    put(v, 0x1000, block(12, 0, adpcm_flag::kLoopStart | adpcm_flag::kLoopRepeat, {}));
    put(v, 0x1010, block(12, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat, {}));
    key(v, 0x1000, 0x1000, 0x0007, 0x4000);
    CHECK(v.active());
    CHECK(v.voice(0, 0).key_on_pending);
    render(v, 1);
    CHECK(v.voice(0, 0).phase == VoicePhase::Attack);
    CHECK(v.voice_param(0, 0, sd_code::kEnvx) == 0x3800);
    render(v, 2);
    CHECK(v.voice_param(0, 0, sd_code::kEnvx) == 0x7FFF);
    CHECK(v.voice(0, 0).phase == VoicePhase::Decay);
    render(v, 1);  // decay: 0x7FFF - 16383 = 0x4000 <= (7 + 1) * 0x800 -> Sustain
    CHECK(v.voice_param(0, 0, sd_code::kEnvx) == 0x4000);
    CHECK(v.voice(0, 0).phase == VoicePhase::Sustain);
    render(v, 1);  // sustain: linear decrease rate 0 -> 0, still Sustain
    CHECK(v.voice_param(0, 0, sd_code::kEnvx) == 0);
    CHECK(v.voice(0, 0).phase == VoicePhase::Sustain);
    CHECK(v.active());
    v.key_off(0, 1);
    CHECK(v.voice(0, 0).phase == VoicePhase::Release);
    render(v, 1);
    CHECK(v.voice(0, 0).phase == VoicePhase::Off);
    CHECK_FALSE(v.active());
    CHECK(v.key_ons() == 1);
    CHECK(v.key_offs() == 1);
    // A key-off before the first rendered frame cancels the pending key-on.
    key(v, 0x1000, 0x1000);
    v.key_off(0, 1);
    CHECK_FALSE(v.active());
}

TEST_CASE("Pitch 0x1000 plays one decoded sample per frame; 0x800 interpolates; the end flag stops and sets ENDX") {
    // Two blocks of distinct values at shift 0 (nibble n -> n << 12), the second ends the sample.
    std::vector<u8> n0, n1;
    for (u8 i = 0; i < 28; ++i) {
        n0.push_back(static_cast<u8>((i * 5 + 1) & 0xF));
        n1.push_back(static_cast<u8>((i * 3 + 2) & 0xF));
    }
    const auto b0 = block(0, 0, 0, n0), b1 = block(0, 0, adpcm_flag::kLoopEnd, n1);
    std::vector<u8> both = b0;
    both.insert(both.end(), b1.begin(), b1.end());
    const std::vector<s16> direct = adpcm_decode(both, 2);
    REQUIRE(direct.size() == 56);

    Spu2Voices v;
    put(v, 0x2000, b0);
    put(v, 0x2010, b1);
    key(v, 0x2000, 0x1000);
    const auto fr = render_each(v, 60);
    // The envelope (AR 0, DR 0, SL 0xF, SR 0 linear up): 0x3800, 0x7000, 0x7FFF, the one decay step to 0x4000,
    // then back up 0x7800, 0x7FFF ... -- the sample index is the frame index throughout.
    CHECK(fr[0].env == 0x3800);
    CHECK(fr[2].env == 0x7FFF);
    CHECK(fr[3].env == 0x4000);
    CHECK(fr[5].env == 0x7FFF);
    for (u32 f = 0; f < 56; ++f) {
        INFO("frame " << f);
        CHECK(fr[f].l == expect_out(direct[f], fr[f].env));
        CHECK(fr[f].r == expect_out(direct[f], fr[f].env));
    }
    // Frame 56 shifts the end block out: ENDX set, the voice released at level 0 -> Off, output silent.
    CHECK(fr[56].l == 0);
    CHECK(fr[57].l == 0);
    CHECK(v.endx(0) == 1u);
    CHECK_FALSE(v.active());
    CHECK(v.voice(0, 0).phase == VoicePhase::Off);
    // NAX of a stopped voice reads its SSA; a write to ENDX clears the flags.
    CHECK(v.voice_addr(0, 0, sd_code::kNax) == 0x2000u);
    v.set_switch(0, sd_code::kEndx, 0);
    CHECK(v.endx(0) == 0u);

    // Pitch 0x800: frame f sits at position f * 0x800 -> even frames are samples, odd frames the midpoint.
    Spu2Voices w;
    put(w, 0x2000, b0);
    put(w, 0x2010, b1);
    key(w, 0x2000, 0x800);
    const auto half = render_each(w, 20);
    for (u32 f = 0; f < 20; ++f) {
        INFO("frame " << f);
        const s32 s = (f & 1) == 0 ? direct[f / 2] : (direct[f / 2] * 0x800 + direct[f / 2 + 1] * 0x800) >> 12;
        CHECK(half[f].l == expect_out(s, half[f].env));
    }
    // NAX while playing is the block being played; pitch is capped at 0x3FFF (4 samples per frame).
    CHECK(w.voice_addr(0, 0, sd_code::kNax) == 0x2000u);
    Spu2Voices fast;
    put(fast, 0x2000, b0);
    put(fast, 0x2010, b1);
    key(fast, 0x2000, 0xFFFF);
    render(fast, 14);  // 14 frames * 0x3FFF / 0x1000 = 55.99 samples: the end block is still playing
    CHECK(fast.endx(0) == 0u);
    CHECK(fast.active());
    render(fast, 1);   // 59.99: both blocks consumed
    CHECK(fast.endx(0) == 1u);
    CHECK_FALSE(fast.active());

    // Loop: block 0 carries the start flag, block 1 end + repeat -> the sample repeats from block 0 and ENDX is
    // set at every pass; an explicit LSAX overrides the start flag.
    Spu2Voices lp;
    put(lp, 0x3000, block(0, 0, adpcm_flag::kLoopStart, n0));
    put(lp, 0x3010, block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat, n1));
    key(lp, 0x3000, 0x1000);
    const auto rep = render_each(lp, 120);
    for (u32 f = 6; f < 56; ++f) {  // the envelope is flat at 0x7FFF from frame 5
        INFO("frame " << f);
        CHECK(rep[f + 56].l == rep[f].l);
    }
    CHECK(lp.endx(0) == 1u);
    CHECK(lp.active());
    CHECK(lp.voice(0, 0).lsax == 0x3000u);
    // An LSAX written after the key-on sticks (the start flag no longer updates it); one written before is
    // replaced by the start flag, as key-on clears the "written" state.
    Spu2Voices lx;
    put(lx, 0x3000, block(0, 0, adpcm_flag::kLoopStart, n0));
    put(lx, 0x3010, block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat, n1));
    put(lx, 0x3020, block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat, n0));
    lx.set_voice_addr(0, 0, sd_code::kLsax, 0x3020);
    key(lx, 0x3000, 0x1000);
    render(lx, 1);
    CHECK(lx.voice(0, 0).lsax == 0x3000u);
    lx.set_voice_addr(0, 0, sd_code::kLsax, 0x3020);
    render(lx, 60);
    CHECK(lx.voice(0, 0).lsax == 0x3020u);
    CHECK(lx.voice_addr(0, 0, sd_code::kNax) == 0x3020u);  // looped to the explicit address
}

TEST_CASE("Volumes: voice L/R and the core master scale the output; MUTE_ENABLE silences a core") {
    const auto b = block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat | adpcm_flag::kLoopStart, std::vector<u8>(28, 7));  // constant 0x7000
    Spu2Voices v;
    put(v, 0x4000, b);
    key(v, 0x4000, 0x1000);
    v.set_voice_param(0, 0, sd_code::kVoll, 0x2000);  // half left
    v.set_voice_param(0, 0, sd_code::kVolr, 0x0000);  // right silent
    v.set_core_param(0, sd_code::kMvoll, 0x1000);     // quarter
    const auto fr = render_each(v, 4);
    const s32 out = 0x7000 * fr[3].env >> 15;
    // voice 0x4000 x MVOL0 0x2000 x AVOL1 0x7FFF x MVOL1 0x7FFE, Q15 stages.
    const s32 chain = q15(q15(0x2000, 0x7FFF), 0x7FFE);
    CHECK(fr[3].l == (out * q15(0x4000, chain)) >> 15);
    CHECK(fr[3].r == 0);
    v.set_core_attr(0, 6, 1);  // SD_CORE_MUTE_ENABLE
    const auto muted = render(v, 2);
    CHECK(muted[0] == 0);
    CHECK(v.core_attr(0, 6) == 1);
    v.set_core_attr(0, 6, 0);
    CHECK(render(v, 2)[0] != 0);
    // Muting core 1 silences core 0's voices too (they reach the output through core 1).
    v.set_core_attr(1, 6, 1);
    CHECK(render(v, 2)[0] == 0);
    v.set_core_attr(1, 6, 0);
    // The second core's voices are independent registers.
    v.set_voice_param(1, 5, sd_code::kPitch, 0x1234);
    CHECK(v.voice_param(1, 5, sd_code::kPitch) == 0x1234);
    CHECK(v.voice_param(0, 5, sd_code::kPitch) == 0);
    CHECK(v.core_param(0, sd_code::kMvolxl) == 0x1000);
}

TEST_CASE("Mixer: passes on the 512-frame grid two passes behind the clock, stream + voices summed, clipped, gaps kept") {
    Spu2Voices v;
    Spu2Mixer m;
    CaptureSink sink;
    m.set_sink(&sink);
    m.set_voices(&v);
    // The stream enters core 1 (CRI_ADXI spucore=1) and is scaled by its MVOL: 0x3FFF -> 0x7FFE/0x8000, so
    // a constant 1000 / -1000 stream pass at [700, 1212) comes out as 999 / -1000 (floor).
    v.set_interpolation(Interpolation::Linear);
    v.set_core_param(1, sd_code::kMvoll, 0x3FFF);
    v.set_core_param(1, sd_code::kMvolr, 0x3FFF);
    std::vector<s16> s(2 * 512);
    for (u32 i = 0; i < 512; ++i) {
        s[2 * i] = 1000;
        s[2 * i + 1] = -1000;
    }
    m.stream_sink().push(700, s);
    m.flush(3036);  // pass 0 ([0, 512)) is due (0 + 2560 <= 3036) and silent -> a gap; pass 512 not due yet
    CHECK(sink.pushes.empty());
    CHECK(m.passes_skipped() == 1);
    CHECK(m.next_pass() == 512);
    m.flush(3836);  // passes 512 and 1024 due (1024 + 2560 <= 3836); 1536 is not
    REQUIRE(sink.pushes.size() == 2);
    CHECK(sink.pushes[0].first == 512);
    CHECK(sink.pushes[0].data.size() == 1024);
    CHECK(sink.pushes[0].data[2 * (699 - 512)] == 0);
    CHECK(sink.pushes[0].data[2 * (700 - 512)] == 999);
    CHECK(sink.pushes[0].data[2 * (700 - 512) + 1] == -1000);
    CHECK(sink.pushes[1].first == 1024);
    CHECK(sink.pushes[1].data[2 * (1211 - 1024)] == 999);
    CHECK(sink.pushes[1].data[2 * (1212 - 1024)] == 0);
    CHECK(m.stream_frames() == 512);
    CHECK(m.stream_frames_late() == 0);
    // Two full-scale voices keyed at frame 2300 (where the voices stand after the last flush) clip the sum.
    const auto loud = block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat | adpcm_flag::kLoopStart, std::vector<u8>(28, 7));
    put(v, 0x5000, loud);
    CHECK(m.voice_frame() == 3836);
    v.set_core_param(0, sd_code::kMvoll, 0x3FFF);
    v.set_core_param(0, sd_code::kMvolr, 0x3FFF);
    for (u32 vo = 0; vo < 2; ++vo) {
        v.set_voice_param(0, vo, sd_code::kVoll, 0x3FFF);
        v.set_voice_param(0, vo, sd_code::kVolr, 0x3FFF);
        v.set_voice_param(0, vo, sd_code::kPitch, 0x1000);
        v.set_voice_param(0, vo, sd_code::kAdsr1, 0x000F);
        v.set_voice_addr(0, vo, sd_code::kSsa, 0x5000);
    }
    v.key_on(0, 3);
    m.flush(3836 + 2560 + 512);  // passes 1536, 2048, 2560, 3072 (silent) and 3584, 4096 (voices from 3836) due
    REQUIRE(sink.pushes.size() == 4);
    CHECK(sink.pushes[2].first == 3584);
    CHECK(sink.pushes[2].data[2 * (3835 - 3584)] == 0);
    CHECK(sink.pushes[2].data[2 * (3836 - 3584)] == 2 * expect_out(0x7000, 0x3800));  // frame 3836: both voices in attack
    CHECK(sink.pushes[2].data[2 * (3842 - 3584)] == 32767);                           // envelope flat: clipped from ~57,000
    CHECK(sink.pushes[2].data[2 * (3842 - 3584) + 1] == 32767);
    CHECK(sink.pushes[3].first == 4096);
    CHECK(m.first_voice_frame() == 3836);
    CHECK(m.voice_frames() > 0);
    CHECK(m.passes_skipped() == 5);
    // Key-off at 6908 (where the voices now stand): release rate 0 -> 0x3FFF on that frame, 0 on the next.
    CHECK(m.voice_frame() == 6908);
    v.key_off(0, 3);
    m.flush(6908 + 2560 + 512);  // passes 4608 ... 6656 (five with data) and 7168 (silent) due
    REQUIRE(sink.pushes.size() == 9);
    CHECK(sink.pushes[8].first == 6656);
    CHECK(sink.pushes[8].data[2 * (6907 - 6656)] == 32767);  // still sounding
    CHECK(sink.pushes[8].data[2 * (6908 - 6656)] == 2 * expect_out(0x7000, 0x3FFF));  // release rate 0: 0x7FFF -> 0x3FFF
    CHECK(sink.pushes[8].data[2 * (6909 - 6656)] == 0);                                // -> 0, Off
    CHECK_FALSE(v.active());
    CHECK(m.passes_skipped() == 6);
    CHECK(m.next_pass() == 7680);
    // finish() emits what remains (silent passes stay gaps).
    m.finish();
    CHECK(m.next_pass() >= m.voice_frame());
    CHECK(sink.pushes.size() == 9);
}

TEST_CASE("COMSE.BD: the first Vagi entry through the voice model equals a direct decode of the same bytes") {
    const auto hd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.HD");
    const auto bd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.BD");
    if (!hd || !bd) {
        MESSAGE("skipped: extracted/DATA/SOUND/SPU/COMSE.{HD,BD} not present");
        return;
    }
    // Head chunk offsets (docs/ANALYSIS/19 §2.2): Vagi at 0x50; the Vagi chunk holds {IECS, igaV, size, max index,
    // offsets[]} and 8-byte entries {u32 bd offset, u16 rate, u8 loop, u8} (ps2sdk sdhd.h).
    auto u32_at = [&](std::size_t o) { u32 v; std::memcpy(&v, hd->data() + o, 4); return v; };
    auto u16_at = [&](std::size_t o) { u16 v; std::memcpy(&v, hd->data() + o, 2); return v; };
    const u32 vagi = u32_at(0x10 + 0x20);
    REQUIRE(vagi == 0x50u);
    REQUIRE(std::memcmp(hd->data() + vagi + 4, "igaV", 4) == 0);
    const u32 count = u32_at(vagi + 12) + 1;
    CHECK(count == 53);
    const u32 entry = vagi + u32_at(vagi + 16);
    const u32 bd_off = u32_at(entry);
    const u16 rate = u16_at(entry + 4);
    CHECK(bd_off == 0);
    CHECK(rate == 44100);
    // Blocks of the entry: up to and including the first end flag.
    std::size_t blocks = 0;
    while ((bd_off + 16 * blocks + 1) < bd->size() && ((*bd)[bd_off + 16 * blocks + 1] & adpcm_flag::kLoopEnd) == 0) ++blocks;
    ++blocks;
    CHECK(blocks == 489);
    const std::vector<s16> direct = adpcm_decode(std::span<const u8>(bd->data() + bd_off, bd->size() - bd_off), blocks);
    REQUIRE(direct.size() == blocks * 28);

    Spu2Voices v;
    std::memcpy(v.ram().data() + 0x5010, bd->data(), bd->size());  // SOUND_Send's placement (19 §1.3)
    key(v, 0x5010 + bd_off, 0x1000);
    const u32 frames = static_cast<u32>(blocks * 28 + 8);
    const auto fr = render_each(v, frames);
    u32 mismatches = 0, nonzero = 0;
    for (u32 f = 0; f < blocks * 28; ++f) {
        if (fr[f].l != expect_out(direct[f], fr[f].env) || fr[f].r != fr[f].l) ++mismatches;
        if (fr[f].l != 0) ++nonzero;
    }
    CHECK(mismatches == 0);
    CHECK(nonzero > blocks * 28 / 2);  // a real sound, not silence
    CHECK(v.endx(0) == 1u);
    CHECK_FALSE(v.active());
    MESSAGE("COMSE Vagi 0: " << blocks << " blocks, " << blocks * 28 << " samples at 44.1 kHz, " << nonzero << " non-zero output frames");
}

TEST_CASE("Gaussian: the table is the SPU's (four weights of every index sum to 0x7F7F..0x7F81) and pitch 0x1000 applies it") {
    CHECK(kSpu2GaussTable[0] == -1);
    CHECK(kSpu2GaussTable[0xFF] == 0x12C7);
    CHECK(kSpu2GaussTable[0x100] == 0x1307);
    CHECK(kSpu2GaussTable[0x1FF] == 0x59B3);
    for (u32 i = 0; i < 256; ++i) {
        const s32 sum = kSpu2GaussTable[0xFF - i] + kSpu2GaussTable[0x1FF - i] + kSpu2GaussTable[0x100 + i] + kSpu2GaussTable[i];
        CHECK(sum >= 0x7F7F);
        CHECK(sum <= 0x7F81);
    }
    // A voice at pitch 0x1000 (index i = 0 every frame): out[f] = g[0xFF] s[f-3] + g[0x1FF] s[f-2] + g[0x100] s[f-1]
    // + g[0] s[f], each product shifted by 15 on its own; the three taps before the first sample are 0.
    std::vector<u8> n0, n1;
    for (u8 i = 0; i < 28; ++i) {
        n0.push_back(static_cast<u8>((i * 5 + 1) & 0xF));
        n1.push_back(static_cast<u8>((i * 3 + 2) & 0xF));
    }
    const auto b0 = block(0, 0, 0, n0), b1 = block(0, 0, adpcm_flag::kLoopEnd, n1);
    std::vector<u8> both = b0;
    both.insert(both.end(), b1.begin(), b1.end());
    const std::vector<s16> direct = adpcm_decode(both, 2);
    auto sample_at = [&](int k) -> s32 { return k < 0 ? 0 : direct[static_cast<std::size_t>(k)]; };
    Spu2Voices v;
    put(v, 0x2000, b0);
    put(v, 0x2010, b1);
    key(v, 0x2000, 0x1000);
    v.set_interpolation(Interpolation::Gaussian);
    CHECK(v.interpolation() == Interpolation::Gaussian);
    const auto fr = render_each(v, 55);
    const s16* g = kSpu2GaussTable.data();
    for (int f = 0; f < 55; ++f) {
        INFO("frame " << f);
        const s32 s = ((g[0xFF] * sample_at(f - 3)) >> 15) + ((g[0x1FF] * sample_at(f - 2)) >> 15) + ((g[0x100] * sample_at(f - 1)) >> 15) +
                      ((g[0] * sample_at(f)) >> 15);
        CHECK(fr[static_cast<std::size_t>(f)].l == expect_out(s, fr[static_cast<std::size_t>(f)].env));
    }
    // Pitch 0x800: odd frames sit at fraction 0x800 -> i = 0x80, the four taps around position f/2.
    Spu2Voices w;
    put(w, 0x2000, b0);
    put(w, 0x2010, b1);
    key(w, 0x2000, 0x800);
    w.set_interpolation(Interpolation::Gaussian);
    const auto half = render_each(w, 20);
    for (int f = 0; f < 20; ++f) {
        INFO("frame " << f);
        const int k = f / 2;
        const u32 i = (f & 1) ? 0x80u : 0u;
        const s32 s = ((g[0xFF - i] * sample_at(k - 3)) >> 15) + ((g[0x1FF - i] * sample_at(k - 2)) >> 15) + ((g[0x100 + i] * sample_at(k - 1)) >> 15) +
                      ((g[i] * sample_at(k)) >> 15);
        CHECK(half[static_cast<std::size_t>(f)].l == expect_out(s, half[static_cast<std::size_t>(f)].env));
    }
    // The block shift keeps the taps: the second block's first frames (28..30) above used samples 25..27.
    // Frame 55 (the end block's last sample) shifts the end block out: ENDX, and the voice stops.
    CHECK(v.endx(0) == 0u);
    CHECK(v.active());
    render(v, 1);
    CHECK(v.endx(0) == 1u);
    CHECK_FALSE(v.active());
    CHECK(v.longest_voice_frames() == 56);
}

TEST_CASE("Release: a key-off while sounding runs the release rate down to Off; counters account for the voice") {
    // Looping sample; ADSR1 0x000F (AR 0, SL 0xF), ADSR2 0x000B: SR 0 up, RR 0x0B linear -> rate 44, shift 11,
    // step -8 every frame: from 0x7FFF the release takes 4096 frames (85 ms).
    const auto b = block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat | adpcm_flag::kLoopStart, std::vector<u8>(28, 7));
    Spu2Voices v;
    put(v, 0x4000, b);
    key(v, 0x4000, 0x1000, 0x000F, 0x000B);
    render(v, 100);
    CHECK(v.voice(0, 0).phase == VoicePhase::Sustain);
    CHECK(v.voice_param(0, 0, sd_code::kEnvx) == 0x7FFF);
    CHECK(v.active_voices() == 1);
    CHECK(v.active_voices_max() == 1);
    CHECK(v.key_offs_sounding() == 0);
    v.key_off(0, 1);
    CHECK(v.voice(0, 0).phase == VoicePhase::Release);
    CHECK(v.key_offs_sounding() == 1);
    v.key_off(0, 1);  // a second key-off of a releasing voice changes nothing
    CHECK(v.key_offs_sounding() == 1);
    CHECK(v.key_offs() == 2);
    const auto rel = render_each(v, 4100);
    CHECK(rel[0].env == 0x7FFF - 8);
    CHECK(rel[1].env == 0x7FFF - 16);
    CHECK(rel[4094].env == 0x7FFF - 8 * 4095);  // 7
    CHECK(rel[4095].env == 0);
    CHECK(rel[4095].l == 0);
    CHECK(v.voice(0, 0).phase == VoicePhase::Off);
    CHECK_FALSE(v.active());
    CHECK(v.active_voices() == 0);
    CHECK(v.endx(0) == 1u);  // the loop end flag was passed while sounding
    // Active from its start (render 1) through the release: 100 + 4096 frames, counted at the granularity of
    // the render calls (one frame each here).
    CHECK(v.longest_voice_frames() == 100 + 4096);
    // Exponential release (bit 5): rate 0x0B -> shift 11, step scaled by level / 0x8000, never sticking.
    Spu2Voices e;
    put(e, 0x4000, b);
    key(e, 0x4000, 0x1000, 0x000F, 0x002B);
    render(e, 10);
    e.key_off(0, 1);
    const auto ex = render_each(e, 1);
    CHECK(ex[0].env == 0x7FFF - 8 * 0x7FFF / 0x8000);  // -7
    u32 n = 1;
    while (e.active() && n < 200000) {
        render(e, 1);
        ++n;
    }
    CHECK_FALSE(e.active());
    MESSAGE("exponential release from full scale: " << n << " frames");
    CHECK(n > 4096);
}

TEST_CASE("Volume law: libsd's init image, MVOL1 on core 1, the core-0 chain through AVOL1 and MMIX, the stream gain") {
    Spu2Voices v;
    // reset(0) = sceSdInit(0): MMIX 0xFF0 / 0xFFC, MVOL 0, EVOL 0, AVOL 0 / 0x7FFF, BVOL 0, VMIX all on.
    CHECK(v.core_param(0, sd_code::kMmix) == 0xFF0);
    CHECK(v.core_param(1, sd_code::kMmix) == 0xFFC);
    CHECK(v.core_param(0, sd_code::kMvoll) == 0);
    CHECK(v.core_param(1, sd_code::kMvolr) == 0);
    CHECK(v.core_param(0, sd_code::kAvoll) == 0);
    CHECK(v.core_param(1, sd_code::kAvoll) == 0x7FFF);
    CHECK(v.core_param(1, sd_code::kAvolr) == 0x7FFF);
    CHECK(v.core_param(1, sd_code::kBvoll) == 0);
    CHECK(v.get_switch(0, sd_code::kVmixl) == 0xFFFFFFu);
    CHECK(v.get_switch(1, sd_code::kVmixer) == 0xFFFFFFu);
    // reset(1) keeps MVOL / EVOL.
    v.set_core_param(1, sd_code::kMvoll, 0x1234);
    v.set_core_param(0, sd_code::kEvoll, 0x0777);
    v.reset(1);
    CHECK(v.core_param(1, sd_code::kMvoll) == 0x1234);
    CHECK(v.core_param(0, sd_code::kEvoll) == 0x0777);
    v.reset(0);
    CHECK(v.core_param(1, sd_code::kMvoll) == 0);
    // Gains: the sweep-capable registers double a 15-bit level, the input volumes are plain s16.
    CHECK(spu2_fixed_gain(0x3FFF) == 0x7FFE);
    CHECK(spu2_fixed_gain(0x2000) == 0x4000);
    CHECK(spu2_fixed_gain(0x7FFF) == -2);      // bit 14 is the sign of a 15-bit level
    CHECK(spu2_fixed_gain(0x8000) == 0x7FFF);  // sweep mode: full scale (counted, not modelled)
    CHECK(spu2_input_gain(0x7FFF) == 0x7FFF);
    CHECK(spu2_input_gain(0x4000) == 0x4000);

    // A constant 0x7000 sample on core 1, voice 0, MVOL1 = 0x2000 (half): out x voice 0x7FFE x 0x4000.
    const auto b = block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat | adpcm_flag::kLoopStart, std::vector<u8>(28, 7));
    put(v, 0x4000, b);
    v.set_interpolation(Interpolation::Linear);
    v.set_core_param(1, sd_code::kMvoll, 0x2000);
    v.set_core_param(1, sd_code::kMvolr, 0x2000);
    v.set_voice_param(1, 0, sd_code::kVoll, 0x3FFF);
    v.set_voice_param(1, 0, sd_code::kVolr, 0x3FFF);
    v.set_voice_param(1, 0, sd_code::kPitch, 0x1000);
    v.set_voice_param(1, 0, sd_code::kAdsr1, 0x000F);
    v.set_voice_addr(1, 0, sd_code::kSsa, 0x4000);
    v.key_on(1, 1);
    auto one = [&]() {
        s32 acc[2] = {0, 0};
        v.render(1, acc);
        return acc[0];
    };
    for (int i = 0; i < 6; ++i) one();  // envelope flat at 0x7FFF
    const s32 out = 0x7000 * 0x7FFF >> 15;
    CHECK(one() == (out * q15(0x7FFE, 0x4000)) >> 15);
    // The game's per-frame SOUND_Control 0x80 (127, 127) -> MVOL1 = 127 * 129 = 0x3FFF: gain 0x7FFE.
    v.set_core_param(1, sd_code::kMvoll, 127 * 129);
    CHECK(v.core_param(1, sd_code::kMvoll) == 0x3FFF);
    CHECK(one() == (out * q15(0x7FFE, 0x7FFE)) >> 15);
    // MMIX1 without the voice-dry bits silences core 1's voices; MVOL1 = 0 likewise.
    v.set_core_param(1, sd_code::kMmix, 0xFFC & ~(mmix_bit::kVoiceDryL | mmix_bit::kVoiceDryR));
    CHECK(one() == 0);
    v.set_core_param(1, sd_code::kMmix, 0xFFC);
    CHECK(one() != 0);
    v.set_core_param(1, sd_code::kMvoll, 0);
    CHECK(one() == 0);
    v.set_core_param(1, sd_code::kMvoll, 0x3FFF);

    // A core-0 voice: x MVOL0 x AVOL1 x MVOL1; AVOL1 = 0x4000 halves it; MMIX1 without the external-input bits
    // or MMIX0 without the voice-dry bits silences it.
    v.key_off(1, 1);
    for (int i = 0; i < 2; ++i) one();  // release rate 0: two frames to Off
    CHECK_FALSE(v.active());
    v.set_core_param(0, sd_code::kMvoll, 0x3FFF);
    v.set_core_param(0, sd_code::kMvolr, 0x3FFF);
    v.set_voice_param(0, 3, sd_code::kVoll, 0x3FFF);
    v.set_voice_param(0, 3, sd_code::kVolr, 0x3FFF);
    v.set_voice_param(0, 3, sd_code::kPitch, 0x1000);
    v.set_voice_param(0, 3, sd_code::kAdsr1, 0x000F);
    v.set_voice_addr(0, 3, sd_code::kSsa, 0x4000);
    v.key_on(0, 1u << 3);
    for (int i = 0; i < 6; ++i) one();
    CHECK(one() == (out * kCore0Gain) >> 15);
    v.set_core_param(1, sd_code::kAvoll, 0x4000);
    CHECK(one() == (out * q15(0x7FFE, q15(q15(0x7FFE, 0x4000), 0x7FFE))) >> 15);
    v.set_core_param(1, sd_code::kAvoll, 0x7FFF);
    v.set_core_param(1, sd_code::kMmix, 0xFF0);  // no MSNDL/R: core 0 is not mixed into core 1
    CHECK(one() == 0);
    v.set_core_param(1, sd_code::kMmix, 0xFFC);
    v.set_core_param(0, sd_code::kMmix, 0x3F0);  // core 0's own voice-dry bits off
    CHECK(one() == 0);
    v.set_core_param(0, sd_code::kMmix, 0xFF0);
    CHECK(one() != 0);
    CHECK(v.active_voices_max() == 1);

    // The stream (core 1 by default) gets MVOL1 through MMIX1's memory-input bits; on core 0 it takes the
    // same chain as a core-0 voice.
    CHECK(v.stream_core() == 1);
    CHECK(v.stream_gain_l() == 0x7FFE);
    v.set_core_param(1, sd_code::kMvolr, 0x1000);
    CHECK(v.stream_gain_r() == 0x2000);
    v.set_core_param(1, sd_code::kMmix, 0xFFC & ~mmix_bit::kMemDryL);
    CHECK(v.stream_gain_l() == 0);
    CHECK(v.stream_gain_r() == 0x2000);
    v.set_core_param(1, sd_code::kMmix, 0xFFC);
    v.set_core_attr(1, 6, 1);  // MUTE core 1
    CHECK(v.stream_gain_l() == 0);
    v.set_core_attr(1, 6, 0);
    v.set_stream_core(0);
    CHECK(v.stream_gain_l() == q15(q15(0x7FFE, 0x7FFF), 0x7FFE));
    // Sweep-mode volume writes are counted.
    CHECK(v.volume_sweeps() == 0);
    v.set_voice_param(0, 5, sd_code::kVoll, 0x8000 | 0x40);
    CHECK(v.volume_sweeps() == 1);
}

TEST_CASE("Mixer: the stream is scaled by its core's master volume per pass; a change applies from the next pass") {
    Spu2Voices v;
    Spu2Mixer m;
    CaptureSink sink;
    m.set_sink(&sink);
    m.set_voices(&v);
    v.set_core_param(1, sd_code::kMvoll, 0x2000);  // half
    v.set_core_param(1, sd_code::kMvolr, 0x1000);  // quarter
    std::vector<s16> s(2 * 1024);
    for (u32 i = 0; i < 1024; ++i) {
        s[2 * i] = 1000;
        s[2 * i + 1] = -1000;
    }
    m.stream_sink().push(512, s);  // passes 512 and 1024
    m.flush(1000);                 // the voices enter pass 512 here: its gain is sampled (0x4000 / 0x2000)
    v.set_core_param(1, sd_code::kMvoll, 0x3FFF);
    v.set_core_param(1, sd_code::kMvolr, 0x3FFF);
    m.flush(1024 + 512 + 2560);  // passes 512 and 1024 due
    REQUIRE(sink.pushes.size() == 2);
    CHECK(sink.pushes[0].first == 512);
    CHECK(sink.pushes[0].data[0] == 500);
    CHECK(sink.pushes[0].data[1] == -250);
    CHECK(sink.pushes[1].first == 1024);
    CHECK(sink.pushes[1].data[0] == 999);    // the new MVOL from the next pass on (0x7FFE / 0x8000, floor)
    CHECK(sink.pushes[1].data[1] == -1000);
    // Without a voice model the stream passes unscaled.
    Spu2Mixer plain;
    CaptureSink psink;
    plain.set_sink(&psink);
    plain.stream_sink().push(0, s);
    plain.finish();
    REQUIRE(psink.pushes.size() == 2);
    CHECK(psink.pushes[0].data[0] == 1000);
    CHECK(psink.pushes[1].data[1] == -1000);
}

TEST_CASE("Reverb decision: the effect registers are stored, the wet path is not rendered, the dry output is unchanged") {
    // runtime/audio/README.md "Reverb": EVOL, ESA/EEA, the wet MMIX bits and VMIXE* are held as the register
    // image libsd leaves; the output is the dry chain only, bit for bit the same whatever they hold.
    const auto b = block(0, 0, adpcm_flag::kLoopEnd | adpcm_flag::kLoopRepeat | adpcm_flag::kLoopStart, std::vector<u8>(28, 5));
    auto run = [&](bool effect_on) {
        Spu2Voices v;
        put(v, 0x4000, b);
        key(v, 0x4000, 0x0C00, 0x000F, 0x000B);
        if (effect_on) {
            for (u32 c = 0; c < kSpuCores; ++c) {
                v.set_core_param(c, sd_code::kEvoll, 0x3000);
                v.set_core_param(c, sd_code::kEvolr, 0x3000);
                v.set_core_addr(c, sd_code::kEsa, 0x1F0000);
                v.set_core_addr(c, sd_code::kEea, 0x1FFFFF);
                v.set_switch(c, sd_code::kVmixel, 0xFFFFFFu);
                v.set_switch(c, sd_code::kVmixer, 0xFFFFFFu);
            }
            v.set_core_param(0, sd_code::kMmix, 0xFFF);
            v.set_core_param(1, sd_code::kMmix, 0xFFF);
        } else {
            v.set_switch(0, sd_code::kVmixel, 0);
            v.set_switch(0, sd_code::kVmixer, 0);
            v.set_core_param(0, sd_code::kMmix, 0xC00);  // voice dry only
            v.set_core_param(1, sd_code::kMmix, 0x00C);  // external input dry only
        }
        CHECK(v.core_param(0, sd_code::kEvoll) == (effect_on ? 0x3000 : 0));
        std::vector<s32> out = render(v, 300);
        v.key_off(0, 1);
        const std::vector<s32> rel = render(v, 300);
        out.insert(out.end(), rel.begin(), rel.end());
        return out;
    };
    const auto dry = run(false), wet = run(true);
    REQUIRE(dry.size() == wet.size());
    CHECK(dry == wet);
    s32 peak = 0;
    for (s32 x : dry) peak = std::max(peak, std::abs(x));
    CHECK(peak > 0);
}
