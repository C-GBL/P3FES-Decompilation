// Modernize layer 3 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the host side of `--native sound`
// (p3fes/native/sound_service.h). Pure C++20 over p3fes_audio's sink interfaces; no OS calls.
//
// Step 1, the ADX output: CRI's PS2RNA records become native outputs. The mixer renders 512-frame passes (48 kHz,
// the PSM's half-buffer), each playing output consuming sfreq / 48000 input samples per frame per channel through
// the same linear rate converter and volume law as the faithful IOP model (runtime/hle/sif/iop/srv_adxi.cpp; IRX
// 0x27E4 and the pan tables 0xD310 / 0xD38C), summed and clipped. The commands are the IOPRNA switch's (start /
// stop / play / channels / sfreq / volume / discard / pan / route / pause all / core / output pan).
//
// Cadence (so the game's timing stays the faithful one): the output runs one pass per vblank, `delay` cycles after
// the VBLANK_START (vblank()), as CRI_ADXI's thread after WaitVblankEnd: it renders every 512-frame pass that ended
// by then, drops the data of outputs whose discard switch is on, takes the block the server sent (PCM first, then
// the commands) and answers with what it played or dropped since its last answer. The server accepts an answer at
// its next call and sends the next block only once the previous one was taken: one block in flight, as DTX's
// ping-pong. GetNumData counts the bytes handed over and not yet given back, as the PSJ's free line does.
//
// The passes go to the output sink (the SPU2 mixer's stream input while sound effects run on the faithful SK
// stack, else the host mix), every play session's consumed PCM to the stream tap (`--dump-wav` stream files), and
// every start / stop to the event sink (`--sound-log`'s `RNA start` / `RNA stop` lines, the faithful arguments).
#pragma once

#include <array>
#include <cstdint>
#include <deque>
#include <functional>
#include <span>
#include <vector>

#include "p3fes/audio/audio_sink.h"
#include "p3fes/native/sound_service.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::native::sound {

namespace sk {
class NativeSk;
}

// The PSM volume law (IRX 0x27E4): side gain 0..255 for a channel volume 0..255, pan -15..15 and output pan
// -15..15; `right` selects the mirrored table entries. The same arithmetic as the faithful model.
u32 psm_side_gain(s32 vol, s32 pan, s32 mpan, bool right);

// An event for the sound log: fno 0x8000 start / 0x8001 stop, args as the faithful `RNA start` / `RNA stop`
// ({slot, sfreq, channels, core, vol L, vol R, stream, 0}; stop: slot and volumes 0), `frame` the timeline frame.
struct NativeSoundEvent {
    u64 cycles = 0;
    u32 fno = 0;
    std::array<u32, 8> args{};
    u64 frame = 0;
};

struct NativeSoundStats {
    u64 creates = 0, destroys = 0, starts = 0, stops = 0, commands = 0, restarts = 0, blocks = 0, passes_run = 0;
    u64 pcm_bytes_in = 0, pcm_bytes_played = 0, discarded_bytes = 0, underrun_samples = 0, passes = 0;
    u32 playing = 0;  // at the time of reading
};

class NativeSound final : public SoundService {
public:
    static constexpr u32 kPassFrames = 512;
    static constexpr u64 kDefaultPassDelay = 412'352;  // IopConfig::adxi_tick_delay_cycles (22 NTSC H-lines)

    NativeSound();

    void set_output(audio::AudioSink* out, audio::StreamTap* tap) {
        out_ = out;
        tap_ = tap;
    }
    void set_event_sink(std::function<void(const NativeSoundEvent&)> f) { events_ = std::move(f); }
    void set_pass_delay(u64 cycles) { delay_ = cycles; }

    // SoundService
    void rna_open(u64 cycles) override;
    void rna_close(u64 cycles) override;
    void rna_create(u64 cycles, u32 rna, u32 nch) override;
    void rna_destroy(u64 cycles, u32 rna) override;
    void rna_transfer(u64 cycles, u32 rna, bool on) override;
    bool rna_try_restart(u64 cycles, u32 rna) override;
    bool rna_transfer_running(u32 rna) const override;
    u32 rna_inflight_bytes(u32 rna, u32 ch) const override;
    u32 rna_dma_room(u32 rna, u32 ch) const override;
    void rna_dma_start(u64 cycles, u32 rna, u32 ch, u32 data, u32 len) override;
    bool rna_dma_pending(u32 rna, u32 ch, u32& data, u32& len) const override;
    void rna_dma_done(u64 cycles, u32 rna, u32 ch, std::span<const s16> pcm) override;
    bool rna_exchange(u64 cycles) override;
    void rna_command(u64 cycles, const RnaCommand& c) override;
    void rna_send(u64 cycles) override;

    // Steps 2-3: the SK stack on native code (sk/sk_host.h), installed by the host when it could read the six modules.
    void set_sk(sk::NativeSk* s) { sk_ = s; }
    sk::NativeSk* sk() const { return sk_; }
    bool sk_native() const override;
    s32 sk_load_module(u64 cycles, std::string_view path, std::span<const u8> args) override;
    void sd_remote(u64 cycles, u32 fno, std::span<const u8> send, std::span<u8> recv) override;

    // The host's clock: a VBLANK_START seen (schedules the output's pass `delay` cycles later) and the time passing
    // (runs a due pass). next_deadline() is the next time advance() has work, ~0 for none.
    void vblank(u64 vblank_count, u64 cycles);  // called at every service; acts once per new count
    void advance(u64 cycles);
    u64 next_deadline() const { return pass_due_; }
    NativeSoundStats stats() const;
    // Machine state (runtime/STATE.md): everything but the sinks.
    void state(StateIo& io);

private:
    struct Resampler {
        u32 phase = 0;  // in 1/48000 input-sample units
        s16 prev = 0, cur = 0;
    };
    // A piece of the 16 KiB buffer of one channel, by offset (the faithful buffer's IOP addresses minus its base).
    struct Chunk {
        u32 off = 0, len = 0;
    };
    // A piece with its PCM (the data line); `pos` bytes of it are played.
    struct Data {
        u32 off = 0, len = 0, pos = 0;
        std::vector<s16> pcm;
    };
    // One channel's buffer as the faithful EE and IOP keep it (CRI SJUNI lines, mode 1: a put that continues the
    // line's tail merges, a get larger than asked splits): the EE's free line (what a transfer may fill), the
    // completed transfers not yet sent, the block in flight, the output's data line, the output's free line (what
    // it played or dropped, given back with its next answer) and the answer the server has not accepted yet.
    struct Chan {
        std::deque<Chunk> efree;
        std::deque<Data> edata, sent, idata;
        std::deque<Chunk> ifree, answered;
        Chunk dma{};      // a transfer started in the last server call (len 0: none) ...
        u32 dma_src = 0;  // ... from this guest address
        Resampler rs{};
    };
    struct Rna {
        bool used = false;
        u32 nch = 0;                  // created channels
        u32 psm_nch = 0;              // the PSM's channel count (command 3 while stopped)
        bool transfer = false;        // +88 asked on
        bool running = false;         // PCM may move in (restarted)
        bool playing = false;
        s8 discard = 0;
        u32 sfreq = 48000;
        std::array<s32, 2> vol{255, 255};
        std::array<s32, 2> pan{0, 0};
        s32 mpan = 0;
        u32 core = 0;
        u32 stream = 0;
        std::array<Chan, 2> ch;
    };
    static void put_merge(std::deque<Chunk>& line, Chunk c);
    static u32 line_bytes(const std::deque<Chunk>& line);
    void reset_buffers(Rna& r);
    int index_of(u32 rna) const;
    void pass(u64 cycles);
    void apply(const RnaCommand& c, u64 cycles);
    void start(Rna& r, u32 index, u64 cycles);
    void stop(Rna& r, u64 cycles);
    void render_until(u64 cycles);
    void render_pass();
    void emit(u64 cycles, u32 fno, const Rna& r, u32 index, bool with_vol);

    audio::AudioSink* out_ = nullptr;
    audio::StreamTap* tap_ = nullptr;
    std::function<void(const NativeSoundEvent&)> events_;
    std::array<Rna, kRnaCount> rna_{};
    std::vector<RnaCommand> building_, in_flight_;  // the commands of the block being built / in flight
    bool block_in_flight_ = false, answer_waiting_ = false;
    bool open_ = false;
    bool paused_ = false;
    u64 delay_ = kDefaultPassDelay;
    u64 pass_due_ = ~0ull;
    u64 seen_vblank_ = ~0ull;
    u64 next_frame_ = 0;
    u32 stream_seq_ = 0;
    NativeSoundStats st_{};
    sk::NativeSk* sk_ = nullptr;  // steps 2-3 (borrowed)
    std::vector<s16> mixbuf_;
};

}  // namespace p3fes::native::sound
