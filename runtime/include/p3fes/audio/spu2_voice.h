// SPU2 voice model for the Standard Kit sound path (ADR-0014 "B-lite" milestones 2-3; docs/ANALYSIS/19 §3):
// 48 voices over libsd's 2 MiB of voice RAM -- the ADPCM block decoder (5 filter pairs, loop start /
// repeat / end flags), a 4-phase ADSR on the SPU2 rate formula, the pitch step (0x1000 = one input sample
// per 48 kHz output frame, capped at 0x3FFF) with the hardware's 4-tap gaussian interpolation (linear
// selectable for A/B), per-voice L/R volume, key on / key off, ENDX, and the two-core output topology:
// core 0's dry sum x MVOL0 feeds core 1 as its external input (x AVOL1, MMIX bit MSNDL/R), core 1's dry
// sum plus that input plus the AutoDMA stream (the CRI PSM mix, x BVOL1 assumed full scale, MMIX MINL/R)
// is scaled by MVOL1 (runtime/audio/README.md "SPU2 voice model"). Spu2Mixer renders the voices in the
// same 512-frame passes the CRI PSM model uses, applies the stream's core gain per pass, sums both into one
// stream (clipped to 16 bits) and pushes it to the host AudioSink on the virtual-time timeline. Not
// modelled: reverb (effect registers are stored; decision in the README), noise, pitch modulation, voice
// IRQ, volume sweeps (bit 15: counted), AutoDMA itself (the stream enters through the mixer). Everything is
// a pure function of the register writes and the frame positions they arrive at, so headless runs stay
// reproducible (ADR-0013 §4).
//
// Addresses are SPU RAM byte addresses as libsd takes them (sceSdSetAddr; the hardware registers hold
// halfword units -- libsd shifts). Parameter / switch / address codes are libsd's (ps2sdk @ 329e2bb
// common/include/libsd-common.h, AFL-2.0, names and values only).
//
// Provenance: the voice, envelope and decoder shape is ported from the MIT reference ps2-web-recomp
// runtime/src/iop/spu2.cpp @ c0f476e (Copyright (c) 2026 Samir Nuri): `Envelope::step`, `decode_block`,
// `key_on`, `update_envelope`, `render_voice`, `key` -- rewritten over byte-addressed RAM with libsd's entry
// model (no register file, no IRQ / AutoDMA / RAM rings) and a pass-based renderer. THIRD_PARTY_NOTICES.md
// row "ps2-web-recomp (SPU2 voices)"; ADR-0010 §2. The 512-entry gaussian table and its indexing come from
// the public SPU description (nocash psx-spx, "4-Point Gaussian Interpolation"; the SPU2 keeps the SPU's
// table), the libsd-init register image from ps2sdk libsd freesd.c @ 329e2bb (AFL-2.0; values only).
#pragma once

#include <array>
#include <cstddef>
#include <span>
#include <vector>

#include "p3fes/audio/audio_sink.h"
#include "p3fes/ee_types.h"

namespace p3fes::audio {

inline constexpr u32 kSpuRamBytes = 2u * 1024u * 1024u;
inline constexpr u32 kSpuCores = 2;
inline constexpr u32 kSpuVoicesPerCore = 24;
inline constexpr u32 kAdpcmBlockBytes = 16;
inline constexpr u32 kAdpcmBlockSamples = 28;

// ADPCM block flags (header byte 1; libsd-common.h ADPCM_LOOP_*).
namespace adpcm_flag {
inline constexpr u8 kLoopEnd = 1;     // last block: jump to LSAX; without kLoopRepeat the voice ends
inline constexpr u8 kLoopRepeat = 2;  // the loop is live (set on blocks inside the loop)
inline constexpr u8 kLoopStart = 4;   // first block of the loop: LSAX = this block unless written explicitly
}  // namespace adpcm_flag

// libsd codes (entry >> 8) this model understands.
namespace sd_code {
inline constexpr u32 kVoll = 0x00, kVolr = 0x01, kPitch = 0x02, kAdsr1 = 0x03, kAdsr2 = 0x04, kEnvx = 0x05, kVolxl = 0x06, kVolxr = 0x07;
inline constexpr u32 kMmix = 0x08, kMvoll = 0x09, kMvolr = 0x0A, kEvoll = 0x0B, kEvolr = 0x0C, kAvoll = 0x0D, kAvolr = 0x0E, kBvoll = 0x0F, kBvolr = 0x10;
inline constexpr u32 kMvolxl = 0x11, kMvolxr = 0x12;
inline constexpr u32 kPmon = 0x13, kNon = 0x14, kKon = 0x15, kKoff = 0x16, kEndx = 0x17, kVmixl = 0x18, kVmixel = 0x19, kVmixr = 0x1A, kVmixer = 0x1B;
inline constexpr u32 kEsa = 0x1C, kEea = 0x1D, kTsa = 0x1E, kIrqa = 0x1F, kSsa = 0x20, kLsax = 0x21, kNax = 0x22;
}  // namespace sd_code

// MMIX (core mixer enable) bits, by the public SPU2 register description (libsd-common.h names the register
// only): voices dry L/R, voices wet (reverb input) L/R, memory input (AutoDMA / "sound data") dry and wet,
// core-0 output into core 1 ("external input") dry and wet. The game writes 0xFC0 to core 0 and 0xFCC to
// core 1 (H_Sndcom_Init); libsd's init image is 0xFF0 / 0xFFC.
namespace mmix_bit {
inline constexpr u16 kVoiceDryL = 1u << 11, kVoiceDryR = 1u << 10, kVoiceWetL = 1u << 9, kVoiceWetR = 1u << 8;
inline constexpr u16 kMemDryL = 1u << 7, kMemDryR = 1u << 6, kMemWetL = 1u << 5, kMemWetR = 1u << 4;
inline constexpr u16 kExtDryL = 1u << 3, kExtDryR = 1u << 2, kExtWetL = 1u << 1, kExtWetR = 1u << 0;
}  // namespace mmix_bit

// Sample interpolation between the decoded ADPCM samples at fractional positions: the hardware's 4-tap
// gaussian (default) or the linear two-point form of milestone 2 (kept selectable for A/B listening and for
// tests that assert exact sample reproduction).
enum class Interpolation : u8 { Linear, Gaussian };

// The SPU's 512-entry gaussian table (public description, nocash psx-spx "4-Point Gaussian Interpolation";
// values -1..0x59B3). With i = bits 4..11 of the 16.12 position: out = (g[0xFF - i] * oldest >> 15) +
// (g[0x1FF - i] * older >> 15) + (g[0x100 + i] * old >> 15) + (g[i] * new >> 15), each term shifted on its
// own; the four weights of any i sum to 0x7F7F..0x7F81.
extern const std::array<s16, 512> kSpu2GaussTable;

// A 16-bit volume register as a Q15 gain. MVOL and the voice volumes are the sweep-capable kind: bit 15
// selects sweep mode (not modelled: full scale, counted), else bits 0..14 are a signed level that the
// hardware doubles (0x3FFF -> 0x7FFE ~ 1.0). AVOL / BVOL / EVOL (the input and effect volumes) are plain
// signed 16-bit gains (0x7FFF ~ 1.0), as on the SPU's CD / external input volumes.
inline s32 spu2_fixed_gain(u16 reg) { return (reg & 0x8000u) ? 0x7FFF : static_cast<s16>(static_cast<u16>(reg << 1)); }
inline s32 spu2_input_gain(u16 reg) { return static_cast<s16>(reg); }

// Decodes one 16-byte block: header byte 0 = shift | filter << 4, byte 1 = flags, 14 bytes of nibbles (low
// nibble first). `s1`/`s2` are the previous two samples (filter history), updated. Returns the flags.
u8 adpcm_decode_block(const u8* block, s32& s1, s32& s2, s16* out28);
// Decodes `blocks` consecutive blocks from `bytes` (a bank body) into samples, from a zero history,
// following no loop (a host-side oracle for the tests and the Vagi check).
std::vector<s16> adpcm_decode(std::span<const u8> bytes, std::size_t blocks);

enum class VoicePhase : u8 { Off, Attack, Decay, Sustain, Release };

// The SPU2 envelope step: rate 0..127, linear or exponential, up or down (hardware rate table formula:
// shift = rate >> 2; a step of (7 - (rate & 3)) << max(0, 11 - shift) every 1 << max(0, shift - 11) frames;
// exponential increase slows 4x above 0x6000; exponential decrease scales the step by level / 0x8000).
struct Spu2Envelope {
    int counter = 0;
    s32 level = 0;  // 0..0x7FFF
    void step(int rate, bool decrease, bool exponential);
};

struct Spu2Voice {
    u16 voll = 0, volr = 0, pitch = 0, adsr1 = 0, adsr2 = 0;
    u32 ssa = 0, lsax = 0, next = 0;   // byte addresses; `next` = the block decoded next
    bool lsax_written = false;         // an explicit LSAX overrides the loop-start flag
    bool key_on_pending = false;       // set by KON, consumed at the next rendered frame
    bool endx = false;                 // a block with kLoopEnd was played out
    bool jump_pending = false;         // the last decoded block had kLoopEnd: the next fetch starts at LSAX
    VoicePhase phase = VoicePhase::Off;
    Spu2Envelope env;
    // [0..2] the three samples before the current block (the gaussian taps), [3..30] the current block,
    // [31..58] the next one.
    static constexpr u32 kHistory = 3;
    std::array<s16, kHistory + 2 * kAdpcmBlockSamples> buffer{};
    std::array<u32, 2> block{};        // byte address of the current / next block
    std::array<bool, 2> block_end{};   // that block carries kLoopEnd
    std::array<bool, 2> stop_after{};  // that block ends the sample (kLoopEnd without kLoopRepeat)
    s32 s1 = 0, s2 = 0;                // decoder history
    u32 position = 0;                  // 16.12 fixed-point sample position inside the current block
    u64 key_ons = 0;
    u64 started_at = 0;                // Spu2Voices::frames_rendered() when the voice started (stuck-voice accounting)
};

struct Spu2CoreState {
    std::array<Spu2Voice, kSpuVoicesPerCore> voices{};
    std::array<u16, 0x20> params{};     // core parameters by code (MMIX, MVOLL/R, EVOL, AVOL, BVOL ...)
    std::array<u32, 0x24> switches{};   // PMON/NON/VMIX* by code (stored; ENDX is computed)
    std::array<u32, 0x24> addrs{};      // ESA/EEA/TSA/IRQA by code (stored)
    std::array<u16, 0x10> attrs{};      // core attributes by libsd code (stored; MUTE_ENABLE honoured)
};

class Spu2Voices {
public:
    Spu2Voices();

    std::span<u8> ram() { return ram_; }
    std::span<const u8> ram() const { return ram_; }

    // libsd's sceSdInit(flag) register image (ps2sdk freesd.c, values only): every voice keyed off, every
    // VMIX switch on, MMIX 0xFF0 / 0xFFC, AVOL core 0 = 0, AVOL core 1 = 0x7FFF (core 0's output into core 1),
    // BVOL 0; with (flag & 1) == 0 also MVOL 0 and EVOL 0. The constructor applies the image of reset(0) without counting its key-offs. The voice RAM
    // is kept, as the hardware keeps it.
    void reset(u32 flag = 0);
    void set_interpolation(Interpolation i) { interp_ = i; }
    Interpolation interpolation() const { return interp_; }
    // The core the CRI PSM stream enters by AutoDMA (CRI_ADXI "spucore=1": core 1, inf from the argument;
    // 16 §6.3). Its BVOL is written by CRI_ADXI itself, which the port models as a whole (never through this
    // libsd), so the stream's input gain is taken as full scale and only the core's MVOL (and the core-0 to
    // core-1 chain when the stream enters core 0) applies: stream_gain_l/r().
    void set_stream_core(u32 core) { stream_core_ = core & 1u; }
    u32 stream_core() const { return stream_core_; }

    // ---- libsd-level register model -------------------------------------------------------------------
    void set_voice_param(u32 core, u32 voice, u32 code, u16 value);
    u16 voice_param(u32 core, u32 voice, u32 code) const;  // ENVX reads the live envelope
    void set_core_param(u32 core, u32 code, u16 value);
    u16 core_param(u32 core, u32 code) const;
    void set_voice_addr(u32 core, u32 voice, u32 code, u32 byte_addr);  // SSA / LSAX / NAX
    u32 voice_addr(u32 core, u32 voice, u32 code) const;              // NAX = the block being played
    void set_core_addr(u32 core, u32 code, u32 byte_addr);
    u32 core_addr(u32 core, u32 code) const;
    void set_switch(u32 core, u32 code, u32 mask);  // KON / KOFF act; a write to ENDX clears it; others stored
    u32 get_switch(u32 core, u32 code) const;       // ENDX is the voices' end flags
    void set_core_attr(u32 core, u32 code, u16 value);
    u16 core_attr(u32 core, u32 code) const;

    void key_on(u32 core, u32 mask);
    void key_off(u32 core, u32 mask);
    u32 endx(u32 core) const;

    // ---- rendering --------------------------------------------------------------------------------------
    // Adds `frames` output frames of the two-core chain to `acc` (interleaved L, R; s32, full scale
    // +-0x7FFF): core 1's output = MVOL1 x (core-1 voices + AVOL1 x core-0 output), core 0's output =
    // MVOL0 x core-0 voices, each sum gated by its core's MMIX bits; returns whether any voice contributed.
    bool render(u32 frames, s32* acc);
    bool active() const;        // a voice is keyed or not Off
    u32 active_voices() const;
    // Q15 gains the AutoDMA stream of stream_core() gets on its way to the output at this instant.
    s32 stream_gain_l() const;
    s32 stream_gain_r() const;

    const Spu2Voice& voice(u32 core, u32 v) const { return cores_[core & 1u].voices[v % kSpuVoicesPerCore]; }
    u64 key_ons() const { return key_ons_; }
    u64 key_offs() const { return key_offs_; }
    u64 key_offs_sounding() const { return key_offs_sounding_; }  // key-offs that released a sounding voice
    u64 frames_rendered() const { return frames_; }
    u32 active_voices_max() const { return active_max_; }        // most voices active at one rendered instant
    u64 longest_voice_frames() const { return longest_; }        // longest key-on .. Off span (finished voices)
    u64 volume_sweeps() const { return sweeps_; }                // volume writes with bit 15 (sweep mode) seen
    void state(StateIo& io);  // machine state (spu2_voice.cpp): RAM, cores, counters (interpolation is config)

private:
    std::vector<u8> ram_;
    std::array<Spu2CoreState, kSpuCores> cores_{};
    Interpolation interp_ = Interpolation::Gaussian;
    u32 stream_core_ = 1;
    u64 key_ons_ = 0, key_offs_ = 0, key_offs_sounding_ = 0, frames_ = 0, longest_ = 0, sweeps_ = 0;
    u32 active_max_ = 0;

    void decode_into(Spu2Voice& v, int half);
    void start(Spu2Voice& v);
    void init_image(u32 flag);  // reset()'s register image without the key-off
    void step_envelope(Spu2Voice& v, u64 end_frame);
    void finish_voice(Spu2Voice& v, u64 end_frame);
    bool render_voice(Spu2Voice& v, u32 frames, s32* acc, s32 gate_l, s32 gate_r);
    // The chain gains of a core's dry sum to the output (Q15 L/R): core 1 -> MVOL1; core 0 -> MVOL0 x AVOL1
    // x MVOL1 when core 1's MMIX lets its external input through, else 0.
    void chain_gains(u32 core, s32& gl, s32& gr) const;
};

// One voice key-on as the model saw it (for the sound log).
struct Spu2KeyOn {
    u32 core = 0, voice = 0;
    u32 ssa = 0, lsax = 0;
    u16 pitch = 0, adsr1 = 0, adsr2 = 0, voll = 0, volr = 0;
};

// Sums the SPU2 voices and the CRI PSM stream into one 48 kHz stream on the virtual-time timeline.
//
// The PSM model keeps its own 512-frame pass grid (anchored where its output started) and its own
// consumption clock -- nothing EE-visible changes -- and pushes each pass into `stream_sink()` instead of
// the host. The voices are advanced to every instant the IOP model acts (RPC calls, SK tick deadlines) with
// `advance_voices(frame)`, so a key-on takes effect at its own frame. `flush(clock_frame)` emits the mixer's
// passes [g, g + 512) on a grid anchored at frame 0 once the clock passed g + kLatencyFrames: by then the
// PSM model -- which renders its due passes at its once-per-vblank server pass (about 800 + 67 frames apart,
// IopConfig::adxi_tick_delay_cycles) and at its RPC calls -- has delivered every stream frame below g + 512
// (worst case the stream frontier trails the clock by ~1,380 frames; the lag of 2,560 leaves ~1,180 spare;
// `stream_frames_late()` counts any frame that still arrived for an emitted pass -- 0 in every run).
// A pass with neither stream data nor voice output is skipped, so silence stays a timeline gap
// (as before) and the sinks' gap handling is unchanged. `finish()` emits what remains at the end of a run.
// The stream is scaled by the gains its SPU2 core applies (Spu2Voices::stream_gain_l/r: MVOL of the core
// it enters, full scale without a voice model), sampled once per pass when the voices first advance into
// that pass -- a master-volume change takes effect on the stream from the next 512-frame pass.
class Spu2Mixer {
public:
    static constexpr u32 kPassFrames = 512;
    static constexpr u32 kLatencyFrames = 5 * kPassFrames;
    static constexpr u32 kRingFrames = 16384;  // > kLatencyFrames + the longest EE check-point interval

    Spu2Mixer();
    void set_sink(AudioSink* sink) { sink_ = sink; }
    void set_voices(Spu2Voices* voices) { voices_ = voices; }
    AudioSink& stream_sink() { return stream_; }

    void advance_voices(u64 frame);
    void flush(u64 clock_frame);
    void finish();

    // ---- inspection ---------------------------------------------------------------------------------------
    u64 voice_frame() const { return vfront_; }        // voices rendered up to here
    u64 next_pass() const { return gpush_; }           // first frame of the next pass to emit
    u64 passes_pushed() const { return pushed_; }
    u64 passes_skipped() const { return skipped_; }
    u64 stream_frames() const { return stream_frames_; }
    u64 stream_frames_late() const { return stream_late_; }
    u64 voice_frames() const { return voice_frames_; }  // frames in which a voice produced output
    u64 first_voice_frame() const { return first_voice_; }
    void state(StateIo& io);  // machine state (spu2_voice.cpp): the rings and positions

private:
    class StreamSink final : public AudioSink {
    public:
        explicit StreamSink(Spu2Mixer& m) : m_(m) {}
        void push(u64 first_frame, std::span<const s16> interleaved) override { m_.stage(first_frame, interleaved); }
    private:
        Spu2Mixer& m_;
    };
    friend class StreamSink;

    AudioSink* sink_ = nullptr;
    Spu2Voices* voices_ = nullptr;
    StreamSink stream_;
    std::vector<s32> vring_;          // voice accumulators, 2 per frame
    std::vector<s16> sring_;          // staged stream frames, 2 per frame
    std::vector<u8> svalid_;          // stream frame staged
    std::vector<u8> vact_;            // per pass: a voice produced output
    std::vector<s32> sgain_;          // per pass: the stream's Q15 gain L, R (sampled when the voices enter the pass)
    std::vector<s16> out_;
    u64 vfront_ = 0, gpush_ = 0, stream_front_ = 0;
    u64 pushed_ = 0, skipped_ = 0, stream_frames_ = 0, stream_late_ = 0, voice_frames_ = 0, first_voice_ = ~0ull;

    void stage(u64 first_frame, std::span<const s16> interleaved);
    void emit_pass();
};

}  // namespace p3fes::audio
