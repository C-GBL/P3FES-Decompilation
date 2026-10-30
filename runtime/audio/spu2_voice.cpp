// SPU2 voice model + mixer (p3fes/audio/spu2_voice.h). Voice/envelope/decoder shape after the MIT reference
// ps2-web-recomp runtime/src/iop/spu2.cpp @ c0f476e (THIRD_PARTY_NOTICES.md "ps2-web-recomp (SPU2 voices)");
// the libsd entry model, the byte-addressed RAM, the end-of-sample timing and the pass mixer are p3fes-port's.
#include "p3fes/audio/spu2_voice.h"
#include "p3fes/prof.h"
#include "p3fes/state_io.h"

#include <algorithm>
#include <cstring>

namespace p3fes::audio {

namespace {

constexpr u32 kRamMask = kSpuRamBytes - 1u;
constexpr u32 kMaxPitch = 0x3FFFu;
constexpr s32 kFilter[5][2] = {{0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60}};

inline s16 clamp16(s32 v) { return static_cast<s16>(std::clamp(v, -32768, 32767)); }
inline s32 fixed_gain(u16 reg) { return spu2_fixed_gain(reg); }
inline s32 q15(s32 a, s32 b) { return (a * b) >> 15; }

}  // namespace

// nocash psx-spx, "4-Point Gaussian Interpolation" (the SPU's ROM table, kept by the SPU2); 512 entries.
const std::array<s16, 512> kSpu2GaussTable = {{
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,
         0,      0,      0,      0,      0,      0,      0,      1,
         1,      1,      1,      2,      2,      2,      3,      3,
         3,      4,      4,      5,      5,      6,      7,      7,
         8,      9,      9,     10,     11,     12,     13,     14,
        15,     16,     17,     18,     19,     21,     22,     24,
        25,     27,     28,     30,     32,     33,     35,     37,
        39,     41,     44,     46,     48,     51,     53,     56,
        58,     61,     64,     67,     70,     73,     77,     80,
        84,     87,     91,     95,     99,    103,    107,    111,
       116,    120,    125,    130,    135,    140,    145,    150,
       156,    161,    167,    173,    179,    186,    192,    199,
       205,    212,    219,    227,    234,    242,    250,    257,
       266,    274,    283,    291,    300,    309,    319,    328,
       338,    348,    358,    369,    379,    390,    401,    412,
       424,    436,    448,    460,    473,    485,    498,    512,
       525,    539,    553,    567,    582,    597,    612,    627,
       643,    659,    675,    692,    708,    726,    743,    761,
       779,    797,    816,    835,    854,    874,    894,    914,
       935,    956,    977,    999,   1020,   1043,   1066,   1089,
      1112,   1136,   1160,   1184,   1209,   1234,   1260,   1286,
      1312,   1339,   1366,   1394,   1422,   1450,   1479,   1508,
      1537,   1567,   1598,   1628,   1660,   1691,   1723,   1756,
      1789,   1822,   1856,   1890,   1924,   1959,   1995,   2031,
      2067,   2104,   2141,   2179,   2217,   2256,   2295,   2334,
      2374,   2415,   2456,   2497,   2539,   2582,   2624,   2668,
      2712,   2756,   2801,   2846,   2892,   2938,   2985,   3032,
      3079,   3128,   3176,   3225,   3275,   3325,   3376,   3427,
      3479,   3531,   3584,   3637,   3691,   3745,   3799,   3855,
      3910,   3967,   4023,   4081,   4138,   4197,   4255,   4315,
      4374,   4435,   4495,   4557,   4619,   4681,   4744,   4807,
      4871,   4935,   5000,   5065,   5131,   5197,   5264,   5332,
      5399,   5468,   5536,   5606,   5676,   5746,   5817,   5888,
      5959,   6032,   6104,   6177,   6251,   6325,   6400,   6475,
      6550,   6626,   6702,   6779,   6856,   6934,   7012,   7091,
      7170,   7249,   7329,   7409,   7490,   7571,   7653,   7735,
      7817,   7900,   7983,   8066,   8150,   8234,   8319,   8404,
      8489,   8575,   8661,   8748,   8834,   8922,   9009,   9097,
      9185,   9273,   9362,   9451,   9541,   9630,   9720,   9811,
      9901,   9992,  10083,  10174,  10266,  10358,  10450,  10542,
     10635,  10727,  10820,  10913,  11007,  11100,  11194,  11288,
     11382,  11476,  11571,  11665,  11760,  11855,  11950,  12045,
     12140,  12236,  12331,  12427,  12522,  12618,  12714,  12809,
     12905,  13001,  13097,  13193,  13289,  13385,  13481,  13577,
     13673,  13769,  13865,  13961,  14056,  14152,  14248,  14343,
     14439,  14534,  14630,  14725,  14820,  14915,  15010,  15104,
     15199,  15293,  15387,  15481,  15575,  15669,  15762,  15855,
     15948,  16041,  16133,  16226,  16317,  16409,  16500,  16592,
     16682,  16773,  16863,  16953,  17042,  17131,  17220,  17308,
     17396,  17484,  17571,  17658,  17744,  17830,  17916,  18001,
     18086,  18170,  18254,  18337,  18420,  18502,  18584,  18665,
     18746,  18826,  18905,  18985,  19063,  19141,  19219,  19295,
     19372,  19447,  19522,  19597,  19671,  19744,  19816,  19888,
     19959,  20030,  20100,  20169,  20238,  20306,  20373,  20439,
     20505,  20570,  20634,  20698,  20760,  20822,  20884,  20944,
     21004,  21063,  21121,  21178,  21235,  21290,  21345,  21399,
     21452,  21505,  21556,  21607,  21657,  21706,  21754,  21801,
     21848,  21893,  21938,  21982,  22025,  22066,  22107,  22148,
     22187,  22225,  22262,  22299,  22334,  22369,  22402,  22435,
     22467,  22498,  22527,  22556,  22584,  22611,  22637,  22662,
     22686,  22709,  22731,  22752,  22772,  22791,  22809,  22826,
     22842,  22857,  22872,  22885,  22897,  22908,  22918,  22927,
     22935,  22942,  22948,  22953,  22957,  22960,  22962,  22963,
}};

u8 adpcm_decode_block(const u8* block, s32& s1, s32& s2, s16* out) {
    const int shift = block[0] & 0xF;
    const int filter = std::min<int>((block[0] >> 4) & 0xF, 4);
    const u8 flags = block[1];
    for (u32 i = 0; i < kAdpcmBlockSamples; ++i) {
        const u32 nibble = (block[2 + i / 2] >> ((i & 1u) * 4u)) & 0xFu;
        s32 sample = static_cast<s16>(static_cast<u16>(nibble << 12)) >> shift;
        sample += (s1 * kFilter[filter][0] + s2 * kFilter[filter][1] + 32) >> 6;
        sample = std::clamp(sample, -32768, 32767);
        s2 = s1;
        s1 = sample;
        out[i] = static_cast<s16>(sample);
    }
    return flags;
}

std::vector<s16> adpcm_decode(std::span<const u8> bytes, std::size_t blocks) {
    std::vector<s16> out;
    s32 s1 = 0, s2 = 0;
    for (std::size_t b = 0; b < blocks && (b + 1) * kAdpcmBlockBytes <= bytes.size(); ++b) {
        s16 tmp[kAdpcmBlockSamples];
        adpcm_decode_block(bytes.data() + b * kAdpcmBlockBytes, s1, s2, tmp);
        out.insert(out.end(), tmp, tmp + kAdpcmBlockSamples);
    }
    return out;
}

void Spu2Envelope::step(int rate, bool decrease, bool exponential) {
    const int shift = rate >> 2;
    int cycles = 1 << std::max(0, shift - 11);
    if (exponential && !decrease && level > 0x6000) cycles *= 4;
    if (++counter < cycles) return;
    counter = 0;
    int delta = (decrease ? -8 + (rate & 3) : 7 - (rate & 3)) << std::max(0, 11 - shift);
    if (exponential && decrease) {
        delta = delta * level / 0x8000;
        if (delta == 0) delta = -1;  // the hardware's exponential decrease reaches 0 (inf: the table's last step)
    }
    level = std::clamp(level + delta, 0, 0x7FFF);
}

// The power-on state is libsd's init image without the counted key-off (no voice has sounded yet).
Spu2Voices::Spu2Voices() : ram_(kSpuRamBytes, 0) { init_image(0); }

void Spu2Voices::state(StateIo& io) {
    io.section("spu2-voices");
    io.expect(static_cast<u64>(sizeof(Spu2CoreState)), "Spu2CoreState layout");
    io(ram_, cores_, stream_core_, key_ons_, key_offs_, key_offs_sounding_, frames_, longest_, sweeps_, active_max_);
}

void Spu2Mixer::state(StateIo& io) {
    io.section("spu2-mixer");
    io(vring_, sring_, svalid_, vact_, sgain_, out_, vfront_, gpush_, stream_front_);
    io(pushed_, skipped_, stream_frames_, stream_late_, voice_frames_, first_voice_);
}

void Spu2Voices::reset(u32 flag) {
    // sceSdInit writes KOFF to every voice (counted like any key-off; a sounding voice enters release).
    for (u32 c = 0; c < kSpuCores; ++c) key_off(c, 0xFFFFFFu);
    init_image(flag);
}

void Spu2Voices::init_image(u32 flag) {
    // ps2sdk libsd freesd.c InitSpu2 / sceSdInit (AFL-2.0, values only): key-off, VMIX* all on, MMIX
    // 0xFF0 / 0xFFC, (flag & 1) == 0: MVOL 0 and EVOL 0, AVOL core 0 = 0, core 1 = 0x7FFF, BVOL 0.
    for (u32 c = 0; c < kSpuCores; ++c) {
        Spu2CoreState& core = cores_[c];
        for (u32 s = sd_code::kVmixl; s <= sd_code::kVmixer; ++s) core.switches[s] = 0xFFFFFFu;
        core.params[sd_code::kMmix] = c == 0 ? 0xFF0u : 0xFFCu;
        if ((flag & 1u) == 0) {
            core.params[sd_code::kMvoll] = core.params[sd_code::kMvolr] = 0;
            core.params[sd_code::kEvoll] = core.params[sd_code::kEvolr] = 0;
        }
        core.params[sd_code::kAvoll] = core.params[sd_code::kAvolr] = c == 0 ? 0u : 0x7FFFu;
        core.params[sd_code::kBvoll] = core.params[sd_code::kBvolr] = 0;
    }
}

// ---- registers -----------------------------------------------------------------------------------------

void Spu2Voices::set_voice_param(u32 core, u32 voice, u32 code, u16 value) {
    Spu2Voice& v = cores_[core & 1u].voices[voice % kSpuVoicesPerCore];
    if ((code == sd_code::kVoll || code == sd_code::kVolr) && (value & 0x8000u)) ++sweeps_;
    switch (code) {
    case sd_code::kVoll: v.voll = value; break;
    case sd_code::kVolr: v.volr = value; break;
    case sd_code::kPitch: v.pitch = value; break;
    case sd_code::kAdsr1: v.adsr1 = value; break;
    case sd_code::kAdsr2: v.adsr2 = value; break;
    case sd_code::kEnvx: v.env.level = static_cast<s16>(value); break;
    default: break;  // VOLXL/VOLXR are read-only on the hardware
    }
}

u16 Spu2Voices::voice_param(u32 core, u32 voice, u32 code) const {
    const Spu2Voice& v = cores_[core & 1u].voices[voice % kSpuVoicesPerCore];
    switch (code) {
    case sd_code::kVoll: return v.voll;
    case sd_code::kVolr: return v.volr;
    case sd_code::kPitch: return v.pitch;
    case sd_code::kAdsr1: return v.adsr1;
    case sd_code::kAdsr2: return v.adsr2;
    case sd_code::kEnvx: return static_cast<u16>(v.env.level);
    case sd_code::kVolxl: return static_cast<u16>(fixed_gain(v.voll) >> 1);
    case sd_code::kVolxr: return static_cast<u16>(fixed_gain(v.volr) >> 1);
    default: return 0;
    }
}

void Spu2Voices::set_core_param(u32 core, u32 code, u16 value) {
    auto& p = cores_[core & 1u].params;
    if (code < p.size()) p[code] = value;
}
u16 Spu2Voices::core_param(u32 core, u32 code) const {
    const auto& p = cores_[core & 1u].params;
    if (code == sd_code::kMvolxl) return static_cast<u16>(fixed_gain(p[sd_code::kMvoll]) >> 1);
    if (code == sd_code::kMvolxr) return static_cast<u16>(fixed_gain(p[sd_code::kMvolr]) >> 1);
    return code < p.size() ? p[code] : 0;
}

void Spu2Voices::set_voice_addr(u32 core, u32 voice, u32 code, u32 byte_addr) {
    Spu2Voice& v = cores_[core & 1u].voices[voice % kSpuVoicesPerCore];
    const u32 a = byte_addr & kRamMask & ~0xFu;
    switch (code) {
    case sd_code::kSsa: v.ssa = a; break;
    case sd_code::kLsax: v.lsax = a; v.lsax_written = true; break;
    case sd_code::kNax: v.next = a; break;
    default: break;
    }
}
u32 Spu2Voices::voice_addr(u32 core, u32 voice, u32 code) const {
    const Spu2Voice& v = cores_[core & 1u].voices[voice % kSpuVoicesPerCore];
    switch (code) {
    case sd_code::kSsa: return v.ssa;
    case sd_code::kLsax: return v.lsax;
    case sd_code::kNax: return v.phase == VoicePhase::Off && !v.key_on_pending ? v.ssa : v.block[0];
    default: return 0;
    }
}
void Spu2Voices::set_core_addr(u32 core, u32 code, u32 byte_addr) {
    auto& a = cores_[core & 1u].addrs;
    if (code < a.size()) a[code] = byte_addr & kRamMask;
}
u32 Spu2Voices::core_addr(u32 core, u32 code) const {
    const auto& a = cores_[core & 1u].addrs;
    return code < a.size() ? a[code] : 0;
}

void Spu2Voices::set_switch(u32 core, u32 code, u32 mask) {
    switch (code) {
    case sd_code::kKon: key_on(core, mask); break;
    case sd_code::kKoff: key_off(core, mask); break;
    case sd_code::kEndx:  // a write clears the end flags (the register is write-to-clear)
        for (Spu2Voice& v : cores_[core & 1u].voices) v.endx = false;
        break;
    default: {
        auto& s = cores_[core & 1u].switches;
        if (code < s.size()) s[code] = mask & 0xFFFFFFu;
        break;
    }
    }
}
u32 Spu2Voices::get_switch(u32 core, u32 code) const {
    if (code == sd_code::kEndx) return endx(core);
    const auto& s = cores_[core & 1u].switches;
    return code < s.size() ? s[code] : 0;
}

void Spu2Voices::set_core_attr(u32 core, u32 code, u16 value) {
    auto& a = cores_[core & 1u].attrs;
    if (code < a.size()) a[code] = value;
}
u16 Spu2Voices::core_attr(u32 core, u32 code) const {
    const auto& a = cores_[core & 1u].attrs;
    return code < a.size() ? a[code] : 0;
}

void Spu2Voices::key_on(u32 core, u32 mask) {
    for (u32 i = 0; i < kSpuVoicesPerCore; ++i) {
        if (!(mask & (1u << i))) continue;
        Spu2Voice& v = cores_[core & 1u].voices[i];
        v.key_on_pending = true;
        ++v.key_ons;
        ++key_ons_;
    }
}

void Spu2Voices::key_off(u32 core, u32 mask) {
    for (u32 i = 0; i < kSpuVoicesPerCore; ++i) {
        if (!(mask & (1u << i))) continue;
        Spu2Voice& v = cores_[core & 1u].voices[i];
        ++key_offs_;
        if (v.key_on_pending) {
            v.key_on_pending = false;
        } else if (v.phase != VoicePhase::Off && v.phase != VoicePhase::Release) {
            v.phase = VoicePhase::Release;
            v.env.counter = 0;
            ++key_offs_sounding_;
        }
    }
}

u32 Spu2Voices::endx(u32 core) const {
    u32 m = 0;
    for (u32 i = 0; i < kSpuVoicesPerCore; ++i)
        if (cores_[core & 1u].voices[i].endx) m |= 1u << i;
    return m;
}

bool Spu2Voices::active() const {
    for (const Spu2CoreState& c : cores_)
        for (const Spu2Voice& v : c.voices)
            if (v.key_on_pending || v.phase != VoicePhase::Off) return true;
    return false;
}

u32 Spu2Voices::active_voices() const {
    u32 n = 0;
    for (const Spu2CoreState& c : cores_)
        for (const Spu2Voice& v : c.voices) n += (v.key_on_pending || v.phase != VoicePhase::Off) ? 1u : 0u;
    return n;
}

// ---- rendering -----------------------------------------------------------------------------------------

void Spu2Voices::decode_into(Spu2Voice& v, int half) {
    // A loop-end block jumps to LSAX; the target is read when the block after it is fetched (one block
    // before the end block finishes), so an LSAX written while the sample plays is honoured.
    const u32 at = (v.jump_pending ? v.lsax : v.next) & kRamMask & ~0xFu;
    v.jump_pending = false;
    const u8 flags = adpcm_decode_block(ram_.data() + at, v.s1, v.s2, v.buffer.data() + Spu2Voice::kHistory + half * kAdpcmBlockSamples);
    v.block[half] = at;
    v.block_end[half] = (flags & adpcm_flag::kLoopEnd) != 0;
    if ((flags & adpcm_flag::kLoopStart) && !v.lsax_written) v.lsax = at;
    v.next = (at + kAdpcmBlockBytes) & kRamMask;
    // A loop-end block jumps to LSAX; without the repeat flag the sample ends there: the envelope is forced
    // to release at level 0 once that block has played out (render_voice, where it is shifted out).
    v.stop_after[half] = (flags & adpcm_flag::kLoopEnd) && !(flags & adpcm_flag::kLoopRepeat);
    v.jump_pending = (flags & adpcm_flag::kLoopEnd) != 0;
}

void Spu2Voices::start(Spu2Voice& v) {
    v.key_on_pending = false;
    v.lsax_written = false;
    v.endx = false;
    v.next = v.ssa;
    v.s1 = v.s2 = 0;
    v.position = 0;
    v.phase = VoicePhase::Attack;
    v.env = Spu2Envelope{};
    v.stop_after = {false, false};
    v.jump_pending = false;
    v.started_at = frames_;
    v.buffer[0] = v.buffer[1] = v.buffer[2] = 0;  // the gaussian taps before the first sample
    decode_into(v, 0);
    decode_into(v, 1);
}

void Spu2Voices::finish_voice(Spu2Voice& v, u64 end_frame) {
    v.phase = VoicePhase::Off;
    longest_ = std::max(longest_, end_frame - v.started_at);
}

void Spu2Voices::step_envelope(Spu2Voice& v, u64 end_frame) {
    Spu2Envelope& e = v.env;
    switch (v.phase) {
    case VoicePhase::Attack:
        e.step((v.adsr1 >> 8) & 0x7F, false, (v.adsr1 & 0x8000u) != 0);
        if (e.level >= 0x7FFF) v.phase = VoicePhase::Decay;
        break;
    case VoicePhase::Decay:
        e.step(((v.adsr1 >> 4) & 0xF) << 2, true, true);
        if (e.level <= ((v.adsr1 & 0xF) + 1) * 0x800) v.phase = VoicePhase::Sustain;
        break;
    case VoicePhase::Sustain:
        e.step((v.adsr2 >> 6) & 0x7F, (v.adsr2 & 0x4000u) != 0, (v.adsr2 & 0x8000u) != 0);
        break;
    case VoicePhase::Release:
        e.step((v.adsr2 & 0x1F) << 2, true, (v.adsr2 & 0x20u) != 0);
        if (e.level <= 0) finish_voice(v, end_frame);
        break;
    case VoicePhase::Off:
        break;
    }
}

bool Spu2Voices::render_voice(Spu2Voice& v, u32 frames, s32* acc, s32 gate_l, s32 gate_r) {
    if (v.key_on_pending) start(v);
    if (v.phase == VoicePhase::Off) return false;
    const u32 step = std::min<u32>(v.pitch, kMaxPitch);
    const s32 gl = q15(fixed_gain(v.voll), gate_l), gr = q15(fixed_gain(v.volr), gate_r);
    const bool gaussian = interp_ == Interpolation::Gaussian;
    const s16* g = kSpu2GaussTable.data();
    u32 position = v.position;
    bool any = false;
    for (u32 n = 0; n < frames; ++n) {
        if (v.phase == VoicePhase::Off) break;
        const u32 index = position >> 12, frac = position & 0xFFFu;
        // s[3] is the sample at the integer position ("new"), s[2..0] the three before it, s[4] the one after.
        const s16* s = v.buffer.data() + index;
        s32 sample;
        if (gaussian) {
            const u32 i = (frac >> 4) & 0xFFu;
            sample = ((g[0xFF - i] * s[0]) >> 15) + ((g[0x1FF - i] * s[1]) >> 15) + ((g[0x100 + i] * s[2]) >> 15) + ((g[i] * s[3]) >> 15);
        } else {
            sample = (s[3] * static_cast<s32>(0x1000u - frac) + s[4] * static_cast<s32>(frac)) >> 12;
        }
        position += step;
        while ((position >> 12) >= kAdpcmBlockSamples) {
            position -= kAdpcmBlockSamples << 12;
            // Shift the next block (and the current block's last three samples, the taps) down.
            std::memmove(v.buffer.data(), v.buffer.data() + kAdpcmBlockSamples, (Spu2Voice::kHistory + kAdpcmBlockSamples) * sizeof(s16));
            v.endx |= v.block_end[0];
            const bool stop = v.stop_after[0];
            v.block[0] = v.block[1];
            v.block_end[0] = v.block_end[1];
            v.stop_after[0] = v.stop_after[1];
            decode_into(v, 1);
            if (stop) {
                v.phase = VoicePhase::Release;
                v.env.level = 0;
            }
        }
        step_envelope(v, frames_ + n + 1);  // the span ends after this frame
        const s32 out = sample * v.env.level >> 15;
        if (out != 0) any = true;
        acc[2 * n] += (out * gl) >> 15;
        acc[2 * n + 1] += (out * gr) >> 15;
    }
    v.position = position;
    return any;
}

void Spu2Voices::chain_gains(u32 core, s32& gl, s32& gr) const {
    const Spu2CoreState& c = cores_[core & 1u];
    const bool muted = c.attrs[6] != 0;  // SD_CORE_MUTE_ENABLE
    const u16 mmix = c.params[sd_code::kMmix];
    gl = muted || !(mmix & mmix_bit::kVoiceDryL) ? 0 : fixed_gain(c.params[sd_code::kMvoll]);
    gr = muted || !(mmix & mmix_bit::kVoiceDryR) ? 0 : fixed_gain(c.params[sd_code::kMvolr]);
    if ((core & 1u) == 0) {
        // Core 0's output is core 1's external input: AVOL1 x MVOL1, through MMIX1's MSNDL/R bits.
        const Spu2CoreState& c1 = cores_[1];
        const bool muted1 = c1.attrs[6] != 0;
        const u16 mmix1 = c1.params[sd_code::kMmix];
        gl = muted1 || !(mmix1 & mmix_bit::kExtDryL) ? 0 : q15(q15(gl, spu2_input_gain(c1.params[sd_code::kAvoll])), fixed_gain(c1.params[sd_code::kMvoll]));
        gr = muted1 || !(mmix1 & mmix_bit::kExtDryR) ? 0 : q15(q15(gr, spu2_input_gain(c1.params[sd_code::kAvolr])), fixed_gain(c1.params[sd_code::kMvolr]));
    }
}

s32 Spu2Voices::stream_gain_l() const {
    const Spu2CoreState& c = cores_[stream_core_];
    if (c.attrs[6] != 0 || !(c.params[sd_code::kMmix] & mmix_bit::kMemDryL)) return 0;
    s32 gl = fixed_gain(c.params[sd_code::kMvoll]);
    if (stream_core_ == 0) {
        const Spu2CoreState& c1 = cores_[1];
        if (c1.attrs[6] != 0 || !(c1.params[sd_code::kMmix] & mmix_bit::kExtDryL)) return 0;
        gl = q15(q15(gl, spu2_input_gain(c1.params[sd_code::kAvoll])), fixed_gain(c1.params[sd_code::kMvoll]));
    }
    return gl;
}

s32 Spu2Voices::stream_gain_r() const {
    const Spu2CoreState& c = cores_[stream_core_];
    if (c.attrs[6] != 0 || !(c.params[sd_code::kMmix] & mmix_bit::kMemDryR)) return 0;
    s32 gr = fixed_gain(c.params[sd_code::kMvolr]);
    if (stream_core_ == 0) {
        const Spu2CoreState& c1 = cores_[1];
        if (c1.attrs[6] != 0 || !(c1.params[sd_code::kMmix] & mmix_bit::kExtDryR)) return 0;
        gr = q15(q15(gr, spu2_input_gain(c1.params[sd_code::kAvolr])), fixed_gain(c1.params[sd_code::kMvolr]));
    }
    return gr;
}

bool Spu2Voices::render(u32 frames, s32* acc) {
    const prof::Scope prof_zone(prof::Zone::Audio);
    bool any = false;
    u32 active = 0;
    for (u32 c = 0; c < kSpuCores; ++c) {
        Spu2CoreState& core = cores_[c];
        s32 gl = 0, gr = 0;
        chain_gains(c, gl, gr);
        for (Spu2Voice& v : core.voices) {
            if (!v.key_on_pending && v.phase == VoicePhase::Off) continue;
            ++active;
            any |= render_voice(v, frames, acc, gl, gr);
        }
    }
    active_max_ = std::max(active_max_, active);
    frames_ += frames;
    return any;
}

// ---- mixer ----------------------------------------------------------------------------------------------

Spu2Mixer::Spu2Mixer()
    : stream_(*this),
      vring_(2u * kRingFrames, 0),
      sring_(2u * kRingFrames, 0),
      svalid_(kRingFrames, 0),
      vact_(kRingFrames / kPassFrames, 0),
      sgain_(2u * (kRingFrames / kPassFrames), 0x8000),  // unity until a voice model exists
      out_(2u * kPassFrames, 0) {}

void Spu2Mixer::advance_voices(u64 frame) {
    if (frame <= vfront_) return;
    while (vfront_ < frame) {
        const u64 pass_end = (vfront_ / kPassFrames + 1) * kPassFrames;
        const u32 n = static_cast<u32>(std::min<u64>(frame, pass_end) - vfront_);
        while (vfront_ + n > gpush_ + kRingFrames) emit_pass();  // ring full: emit early (degraded, counted as pushed)
        const std::size_t pass_slot = static_cast<std::size_t>((vfront_ / kPassFrames) % (kRingFrames / kPassFrames));
        if (vfront_ % kPassFrames == 0) {  // entering a pass: sample the stream's core gain for it
            sgain_[2 * pass_slot] = voices_ ? voices_->stream_gain_l() : 0x8000;
            sgain_[2 * pass_slot + 1] = voices_ ? voices_->stream_gain_r() : 0x8000;
        }
        if (voices_ && voices_->active()) {  // nothing keyed: the span is silent, the ring stays clear
            s32* acc = &vring_[2u * static_cast<std::size_t>(vfront_ % kRingFrames)];
            if (voices_->render(n, acc)) {
                vact_[pass_slot] = 1;
                voice_frames_ += n;
                if (first_voice_ == ~0ull) first_voice_ = vfront_;
            }
        }
        vfront_ += n;
    }
    while (vfront_ > gpush_ + kRingFrames) emit_pass();
}

void Spu2Mixer::stage(u64 first_frame, std::span<const s16> interleaved) {
    const u64 n = interleaved.size() / kOutputChannels;
    for (u64 i = 0; i < n; ++i) {
        const u64 f = first_frame + i;
        if (f < gpush_) {
            ++stream_late_;
            continue;
        }
        while (f >= gpush_ + kRingFrames) emit_pass();
        const std::size_t slot = static_cast<std::size_t>(f % kRingFrames);
        sring_[2 * slot] = interleaved[2 * i];
        sring_[2 * slot + 1] = interleaved[2 * i + 1];
        svalid_[slot] = 1;
    }
    stream_frames_ += n;
    stream_front_ = std::max(stream_front_, first_frame + n);
}

void Spu2Mixer::flush(u64 clock_frame) {
    advance_voices(clock_frame);
    while (gpush_ + kLatencyFrames <= clock_frame && gpush_ + kPassFrames <= vfront_) emit_pass();
}

void Spu2Mixer::finish() {
    const u64 end = std::max(vfront_, stream_front_);
    while (gpush_ < end) emit_pass();
}

void Spu2Mixer::emit_pass() {
    const prof::Scope prof_zone(prof::Zone::Audio);
    const u64 g = gpush_;
    const std::size_t pass_slot = static_cast<std::size_t>((g / kPassFrames) % (kRingFrames / kPassFrames));
    bool active = vact_[pass_slot] != 0;
    for (u32 i = 0; i < kPassFrames && !active; ++i) active = svalid_[static_cast<std::size_t>((g + i) % kRingFrames)] != 0;
    if (active) {
        // The stream's core gain for this pass (sampled when the voices entered it; a pass the voices have not
        // reached -- finish() at the end of a run -- takes the current one).
        s32 sgl = sgain_[2 * pass_slot], sgr = sgain_[2 * pass_slot + 1];
        if (g >= vfront_ && voices_) {
            sgl = voices_->stream_gain_l();
            sgr = voices_->stream_gain_r();
        }
        for (u32 i = 0; i < kPassFrames; ++i) {
            const std::size_t slot = static_cast<std::size_t>((g + i) % kRingFrames);
            s32 l = vring_[2 * slot], r = vring_[2 * slot + 1];
            if (svalid_[slot]) {
                l += (sring_[2 * slot] * sgl) >> 15;
                r += (sring_[2 * slot + 1] * sgr) >> 15;
            }
            out_[2 * i] = clamp16(l);
            out_[2 * i + 1] = clamp16(r);
        }
        if (sink_) sink_->push(g, out_);
        ++pushed_;
    } else {
        ++skipped_;
    }
    for (u32 i = 0; i < kPassFrames; ++i) {
        const std::size_t slot = static_cast<std::size_t>((g + i) % kRingFrames);
        vring_[2 * slot] = vring_[2 * slot + 1] = 0;
        svalid_[slot] = 0;
    }
    vact_[pass_slot] = 0;
    gpush_ += kPassFrames;
}

}  // namespace p3fes::audio
