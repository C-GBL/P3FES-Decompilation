// Modernize layer 3 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native ADX output `--native sound` installs
// (runtime/native/sound/native_sound.h): the PSM volume law, the command layer (the IOPRNA switch), the output's
// cadence (one block in flight, the pass once per vblank after the vblank-end, the answer the server accepts next),
// GetNumData's accounting, the mixer (rate conversion, gains, sum and clip, silence passes, pause-all gaps,
// underruns, discard), the stream tap and the sound-log events, destroy, machine state.
#include <doctest.h>

#include <map>
#include <utility>
#include <vector>

#include "native_sound.h"
#include "p3fes/audio/audio_sink.h"
#include "p3fes/state_io.h"

using namespace p3fes;
using namespace p3fes::native::sound;

namespace {

struct CaptureSink final : audio::AudioSink {
    std::vector<std::pair<u64, std::vector<s16>>> passes;
    void push(u64 first, std::span<const s16> s) override { passes.emplace_back(first, std::vector<s16>(s.begin(), s.end())); }
};
struct CaptureTap final : audio::StreamTap {
    std::vector<audio::StreamInfo> begun;
    std::map<u32, std::vector<s16>> data[2];
    std::vector<u32> ended;
    void stream_begin(const audio::StreamInfo& i) override { begun.push_back(i); }
    void stream_data(u32 id, u32 ch, std::span<const s16> s) override {
        data[ch][id].insert(data[ch][id].end(), s.begin(), s.end());
    }
    void stream_end(u32 id) override { ended.push_back(id); }
};

constexpr u32 kRec0 = kRnaTable;               // the first PS2RNA record
constexpr u32 kRec1 = kRnaTable + kRnaSize;    // the second
constexpr u64 kVblank = 4'900'000;             // a vblank's cycles, roughly (only the order matters here)
constexpr u64 kPass = audio::kCyclesPerOutputFrame * NativeSound::kPassFrames;  // 512 frames

// One server call that hands `pcm` (already DMA'd) to the output with `cmds`, as the game's native branch does.
bool serve(NativeSound& ns, u64 t, u32 rec, u32 ch, const std::vector<s16>& pcm, std::vector<RnaCommand> cmds = {}) {
    if (!pcm.empty()) {
        ns.rna_dma_start(t, rec, ch, 0x100000, static_cast<u32>(pcm.size() * 2));
        ns.rna_dma_done(t, rec, ch, pcm);
    }
    if (!ns.rna_exchange(t)) return false;
    for (const RnaCommand& c : cmds) ns.rna_command(t, c);
    ns.rna_send(t);
    return true;
}

// The output's pass at the next vblank after `t`: returns the time it ran.
u64 output_pass(NativeSound& ns, u64& vb, u64 t) {
    ns.vblank(++vb, t);
    const u64 due = ns.next_deadline();
    REQUIRE(due != ~0ull);
    ns.advance(due);
    return due;
}

RnaCommand cmd(s16 c, u32 rec, u32 v8, u32 v12 = 0) { return RnaCommand{c, rec, v8, v12}; }

}  // namespace

TEST_CASE("native sound: the PSM volume law is round(vol x pan law x output-pan law / 65025), half up") {
    // the IRX's (10x * 0x81018203) >> 47 is an exact division by 65025 over the whole range
    constexpr u32 law[31] = {255, 254, 253, 251, 249, 246, 242, 238, 232, 227, 220, 213, 206, 198, 189, 180,
                             170, 160, 149, 138, 127, 115, 103, 91,  78,  65,  53,  39,  26,  13,  0};
    constexpr u32 out[31] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
                             238, 221, 204, 187, 170, 153, 136, 119, 102, 85,  68,  51,  34,  17,  0};
    u32 bad = 0;
    for (s32 vol = 0; vol <= 255; ++vol)
        for (s32 pan = -15; pan <= 15; ++pan)
            for (s32 mpan = -15; mpan <= 15; ++mpan)
                for (bool right : {false, true}) {
                    const u64 x = static_cast<u64>(vol) * law[right ? 15 - pan : 15 + pan] * out[right ? 15 - mpan : 15 + mpan];
                    const u64 q = (10 * x) / 65025;
                    const u32 want = static_cast<u32>(q / 10 + (q % 10 >= 5 ? 1 : 0));
                    bad += psm_side_gain(vol, pan, mpan, right) != want;
                }
    CHECK(bad == 0);
    CHECK(psm_side_gain(255, 0, 0, false) == 180);   // the -3 dB centre
    CHECK(psm_side_gain(181, -15, 0, false) == 181);  // ADXT's automatic stereo pan, left channel
    CHECK(psm_side_gain(181, -15, 0, true) == 0);
    CHECK(psm_side_gain(300, -40, 99, false) == psm_side_gain(255, -15, 15, false));  // clamped
}

TEST_CASE("native sound: one block in flight; the output takes it at its pass and answers what it played") {
    NativeSound ns;
    ns.set_pass_delay(1000);
    u64 vb = 0, t = kVblank;
    ns.rna_open(0);
    ns.rna_create(t, kRec0, 1);
    CHECK(ns.rna_inflight_bytes(kRec0, 0) == 0);
    CHECK_FALSE(ns.rna_transfer_running(kRec0));
    CHECK_FALSE(ns.rna_try_restart(t, kRec0));  // the transfer is not asked on
    ns.rna_transfer(t, kRec0, true);
    CHECK(ns.rna_try_restart(t, kRec0));        // everything free: the DTR restarts once
    CHECK_FALSE(ns.rna_try_restart(t, kRec0));
    CHECK(ns.rna_transfer_running(kRec0));

    // a started transfer counts as handed over (GetNumData) before it completes
    ns.rna_dma_start(t, kRec0, 0, 0x100000, 2048);
    u32 data = 0, len = 0;
    CHECK(ns.rna_dma_pending(kRec0, 0, data, len));
    CHECK((data == 0x100000 && len == 2048));
    CHECK(ns.rna_inflight_bytes(kRec0, 0) == 2048);
    ns.rna_dma_done(t, kRec0, 0, std::vector<s16>(1024, 100));
    CHECK_FALSE(ns.rna_dma_pending(kRec0, 0, data, len));
    REQUIRE(ns.rna_exchange(t));
    ns.rna_command(t, cmd(4, kRec0, 48000));
    ns.rna_command(t, cmd(2, kRec0, 1));
    ns.rna_send(t);
    CHECK_FALSE(ns.rna_exchange(t));  // the block is in flight: nothing more goes out
    CHECK(ns.stats().starts == 0);    // and nothing happened yet

    t = output_pass(ns, vb, t + kPass);  // the output takes the block: sfreq, then play
    CHECK(ns.stats().starts == 1);
    CHECK(ns.stats().blocks == 1);
    // the answer counts only what was played before the block arrived (nothing): the server sees no change yet
    REQUIRE(ns.rna_exchange(t));
    CHECK(ns.rna_inflight_bytes(kRec0, 0) == 2048);
    ns.rna_send(t);
    // three passes later the output has played its 1024 samples at 48 kHz (two 512-frame passes)
    t = output_pass(ns, vb, t + 3 * kPass);
    REQUIRE(ns.rna_exchange(t));
    CHECK(ns.rna_inflight_bytes(kRec0, 0) == 0);
    CHECK(ns.stats().pcm_bytes_played == 2048);
    // a pass with no block in flight renders but does not answer
    ns.vblank(++vb, t);
    ns.advance(ns.next_deadline() + 3 * kPass);
    CHECK(ns.rna_exchange(t));
    CHECK(ns.stats().underrun_samples > 0);  // playing with nothing queued
}

TEST_CASE("native sound: the mixer -- rate conversion, gains, sum and clip, silence, pause gaps, discard, tap, log") {
    NativeSound ns;
    CaptureSink sink;
    CaptureTap tap;
    std::vector<NativeSoundEvent> ev;
    ns.set_output(&sink, &tap);
    ns.set_event_sink([&](const NativeSoundEvent& e) { ev.push_back(e); });
    ns.set_pass_delay(10);
    u64 vb = 0, t = 0;
    ns.rna_open(0);
    ns.rna_create(t, kRec0, 1);
    ns.rna_create(t, kRec1, 2);
    for (u32 r : {kRec0, kRec1}) {
        ns.rna_transfer(t, r, true);
        REQUIRE(ns.rna_try_restart(t, r));
    }
    // RNA 0: mono 48 kHz, 1000 constant, volume 255, pan 0 -> 1000 x 180 / 255 = 705 on both sides
    // RNA 1: stereo 24 kHz, ramp on channel 0 (0, 100, 200, ...), silent channel 1, volume 255, pans -15 / +15
    std::vector<s16> ramp(512);
    for (u32 i = 0; i < ramp.size(); ++i) ramp[i] = static_cast<s16>(100 * i);
    ns.rna_dma_start(t, kRec0, 0, 0x100000, 1024 * 2);
    ns.rna_dma_done(t, kRec0, 0, std::vector<s16>(1024, 1000));
    ns.rna_dma_start(t, kRec1, 0, 0x110000, 512 * 2);
    ns.rna_dma_done(t, kRec1, 0, ramp);
    ns.rna_dma_start(t, kRec1, 1, 0x120000, 512 * 2);
    ns.rna_dma_done(t, kRec1, 1, std::vector<s16>(512, 0));
    REQUIRE(ns.rna_exchange(t));
    for (const RnaCommand& c : {cmd(4, kRec0, 48000), cmd(5, kRec0, 0, 255), cmd(2, kRec0, 1), cmd(4, kRec1, 24000),
                                cmd(5, kRec1, 0, 255), cmd(9, kRec1, 0, static_cast<u32>(-15)), cmd(9, kRec1, 1, 15),
                                cmd(2, kRec1, 1)})
        ns.rna_command(t, c);
    ns.rna_send(t);
    const u64 p0 = output_pass(ns, vb, t);  // block taken: both start
    REQUIRE(ev.size() == 2);
    CHECK(ev[0].fno == 0x8000u);
    CHECK(ev[0].args == std::array<u32, 8>{0, 48000, 1, 0, 255, 255, 1, 0});
    CHECK(ev[1].args == std::array<u32, 8>{1, 24000, 2, 0, 255, 255, 2, 0});
    REQUIRE(tap.begun.size() == 2);
    CHECK((tap.begun[1].slot == 1 && tap.begun[1].channels == 2 && tap.begun[1].sample_rate == 24000));
    const std::size_t before = sink.passes.size();
    ns.advance(p0 + kPass);  // no pass due: nothing renders between the output's passes
    CHECK(sink.passes.size() == before);
    const u64 p1 = output_pass(ns, vb, p0 + 2 * kPass);
    REQUIRE(sink.passes.size() >= before + 1);
    const auto& pass = sink.passes[before].second;
    // frame f: RNA 0 gives 1000 x 180 / 255 = 705 L / R from frame 1 on (the converter ramps from 0 to the first
    // sample); RNA 1 channel 0 (left only, gain 255 at pan -15) at 24 kHz takes input k at frame 2k + 1 and sits
    // halfway between at the even frames
    CHECK(pass[0] == 0);
    CHECK(pass[2 * 1] == 705);
    CHECK(pass[2 * 9] == 705 + 300);   // f = 9: input 4 taken, the converter at input 3 (300)
    CHECK(pass[2 * 10] == 705 + 350);  // f = 10: halfway between 300 and 400
    CHECK(pass[2 * 10 + 1] == 705);    // right: RNA 1's channel 0 is panned hard left, its channel 1 is silent
    CHECK(pass[2 * 11] == 705 + 400);
    CHECK(tap.data[0][2].size() >= 256);    // RNA 1 consumed 256 input samples per 512-frame pass
    CHECK(tap.data[0][1].size() >= 512);

    // clip: two outputs at full scale sum past 16 bits
    ns.rna_destroy(p1, kRec1);
    CHECK(ev.back().fno == 0x8001u);  // destroy stops it
    ns.rna_create(p1, kRec1, 1);
    ns.rna_transfer(p1, kRec1, true);
    REQUIRE(ns.rna_try_restart(p1, kRec1));
    for (u32 r : {kRec0, kRec1}) {
        ns.rna_dma_start(p1, r, 0, 0x100000, 2048);
        ns.rna_dma_done(p1, r, 0, std::vector<s16>(1024, 30000));
    }
    REQUIRE(ns.rna_exchange(p1));
    for (const RnaCommand& c : {cmd(4, kRec1, 48000), cmd(5, kRec1, 0, 255), cmd(2, kRec1, 1)}) ns.rna_command(p1, c);
    ns.rna_send(p1);
    output_pass(ns, vb, p1 + kPass);
    const u64 p3 = output_pass(ns, vb, p1 + 4 * kPass);
    bool clipped = false;
    for (const auto& [f, s] : sink.passes)
        for (s16 v : s) clipped |= v == 32767;
    CHECK(clipped);

    // pause all: no passes (a timeline gap); resume continues from the current time
    REQUIRE(ns.rna_exchange(p3));
    ns.rna_command(p3, cmd(11, 0, 1));
    ns.rna_send(p3);
    const u64 p4 = output_pass(ns, vb, p3 + kPass);
    const std::size_t paused_at = sink.passes.size();
    output_pass(ns, vb, p4 + 10 * kPass);
    CHECK(sink.passes.size() == paused_at);

    // discard: the queued data is dropped at the pass and answered as free
    REQUIRE(ns.rna_exchange(p4));
    ns.rna_command(p4, cmd(11, 0, 0));
    ns.rna_command(p4, cmd(8, kRec0, 1));
    ns.rna_dma_start(p4, kRec0, 0, 0x100000, 4096);
    ns.rna_dma_done(p4, kRec0, 0, std::vector<s16>(2048, 7));
    ns.rna_send(p4);
    const u64 p5 = output_pass(ns, vb, p4 + 20 * kPass);  // block in: resume, discard on (the data arrives after the drop)
    const u64 p6 = output_pass(ns, vb, p5 + kPass);        // the drop
    CHECK(ns.stats().discarded_bytes > 0);
    REQUIRE(ns.rna_exchange(p6));
    ns.rna_send(p6);
    output_pass(ns, vb, p6 + kPass);
    REQUIRE(ns.rna_exchange(p6 + 2 * kPass));
    CHECK(ns.rna_inflight_bytes(kRec0, 0) == 0);
    CHECK(sink.passes.size() > paused_at);  // resumed

    // a sample-rate change while playing opens a new tap session (as the faithful model)
    const std::size_t sessions = tap.begun.size();
    ns.rna_command(p6, cmd(4, kRec1, 24000));
    ns.rna_send(p6);
    output_pass(ns, vb, p6 + 3 * kPass);
    CHECK(tap.begun.size() == sessions + 1);
    CHECK(tap.begun.back().sample_rate == 24000);
}

TEST_CASE("native sound: the transfer switch, the restart rule and the channel command") {
    NativeSound ns;
    u64 vb = 0;
    ns.set_pass_delay(10);
    ns.rna_open(0);
    ns.rna_create(0, kRec0, 2);
    ns.rna_transfer(0, kRec0, true);
    REQUIRE(ns.rna_try_restart(0, kRec0));
    ns.rna_dma_start(0, kRec0, 1, 0x100000, 64);
    ns.rna_transfer(0, kRec0, false);  // DTR_Stop
    CHECK_FALSE(ns.rna_transfer_running(kRec0));
    ns.rna_transfer(0, kRec0, true);
    CHECK_FALSE(ns.rna_try_restart(0, kRec0));  // channel 1 still has 64 bytes out
    ns.rna_dma_done(0, kRec0, 1, std::vector<s16>(32, 1));
    REQUIRE(ns.rna_exchange(0));
    ns.rna_command(0, cmd(8, kRec0, 1));  // discard
    ns.rna_send(0);
    const u64 a = output_pass(ns, vb, 0);
    const u64 b = output_pass(ns, vb, a + kPass);
    REQUIRE(ns.rna_exchange(b));
    ns.rna_send(b);
    output_pass(ns, vb, b + kPass);
    REQUIRE(ns.rna_exchange(b + kPass));
    CHECK(ns.rna_try_restart(b, kRec0));  // all given back: the DTR restarts
    // channels: the PSM's count changes only while stopped and up to the created count
    ns.rna_command(b, cmd(3, kRec0, 1));
    ns.rna_command(b, cmd(3, kRec0, 3));  // refused
    ns.rna_command(b, cmd(2, kRec0, 1));
    ns.rna_send(b);
    std::vector<NativeSoundEvent> ev;
    ns.set_event_sink([&](const NativeSoundEvent& e) { ev.push_back(e); });
    output_pass(ns, vb, b + 3 * kPass);
    REQUIRE(ev.size() == 1);
    CHECK(ev[0].args[2] == 1);
    // an unknown record is ignored
    ns.rna_dma_start(0, kRnaTable + 3, 0, 0, 64);
    CHECK(ns.rna_inflight_bytes(kRnaTable + 3, 0) == 0);
    CHECK(ns.rna_inflight_bytes(kRec1, 0) == 0);
}

TEST_CASE("native sound: machine state round trip continues identically") {
    auto setup = [](NativeSound& ns, u64& vb) {
        ns.set_pass_delay(10);
        ns.rna_open(0);
        ns.rna_create(0, kRec0, 1);
        ns.rna_transfer(0, kRec0, true);
        REQUIRE(ns.rna_try_restart(0, kRec0));
        std::vector<s16> pcm(4096);
        for (u32 i = 0; i < pcm.size(); ++i) pcm[i] = static_cast<s16>(i * 7);
        REQUIRE(serve(ns, 0, kRec0, 0, pcm, {cmd(4, kRec0, 22050), cmd(5, kRec0, 0, 200), cmd(2, kRec0, 1)}));
        output_pass(ns, vb, 0);
        output_pass(ns, vb, 3 * kPass);
    };
    NativeSound a;
    u64 vb = 0;
    setup(a, vb);
    StateIo save;
    a.state(save);
    NativeSound b;
    StateIo load(save.buffer().data(), save.buffer().size());
    b.state(load);
    REQUIRE(load.ok());
    CaptureSink sa, sb;
    a.set_output(&sa, nullptr);
    b.set_output(&sb, nullptr);
    u64 va = vb, vbb = vb;
    u64 ta = 3 * kPass, tb = ta;
    for (int i = 0; i < 6; ++i) {
        ta = output_pass(a, va, ta + 2 * kPass);
        tb = output_pass(b, vbb, tb + 2 * kPass);
    }
    CHECK(sa.passes == sb.passes);
    CHECK(!sa.passes.empty());
    CHECK(a.stats().pcm_bytes_played == b.stats().pcm_bytes_played);
}
