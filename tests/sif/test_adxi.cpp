// CRI_ADXI (runtime/hle/sif/iop/srv_adxi.cpp) driven the way the game's EE library drives it: DTX
// ports re-enacted from DTX_ExecHndl 0x559938 (block out -> wait for the IOP's counter -> block in),
// SJX/RNA blocks in the layouts of sjx_sndcbf 0x564400 / ps2rna_sndcbf 0x55FC00, urpc calls as
// DTX_CallUrpc 0x559C10 marshals them, and SDRDRV/SK blocks as sceSdRemote 0x5129C0 sends them.
// Timing: one VBLANK_START per field (4,920,120 EE cycles), the IOP's pass ~22 H-lines later.
#include <doctest.h>

#include <cstring>
#include <vector>

#include "p3fes/audio/audio_sink.h"
#include "p3fes/hle/sif/iop.h"
#include "sif_harness.h"
#include "srv_adxi.h"

using namespace p3fes;
using namespace p3fes::test;

namespace {

constexpr u64 kField = 4'920'120;  // 294,912,000 / 59.94
constexpr u32 kDtxRpc = 0x90000200u;

// IOP and EE addresses for the buffers (the game's come from AllocIopHeap / its .bss; any IOP RAM
// address works for the model).
constexpr u32 kIopSjxBuf = 0x00100040u, kIopRnaBuf = 0x00101040u;
constexpr u32 kEeSjxBuf = 0x00980000u, kEeRnaBuf = 0x00981000u;
constexpr u32 kWk = 2176;  // DTX_Create(.., 2176) in SJX_Init 0x564588 / PS2RNA_Init 0x560018
constexpr u32 kIopPool = 0x00110000u;  // SJUNI chain pools (256 B each, ps2rna_init_psj 0x55F8C0)
constexpr u32 kIopPcm = 0x00120000u;   // 16 KiB PCM buffers
constexpr u32 kEeSjxObj0 = 0x007B1AD0u, kEeSjxObj1 = 0x007B1AE4u;  // the EE's SJX objects (echoed)

// The EE half of one DTX port (DTX_Create 0x559718 + DTX_ExecHndl 0x559938).
struct EeDtx {
    EeSide& e;
    u32 cd;
    u32 id, eebuf, iopbuf, size;
    u8 stat = 0;
    u32 cnt = 0;
    u32 rmt = 0;
    u32 sends = 0, receives = 0;

    bool create() {
        rmt = load32(e.call_sync(cd, 2, words({id, eebuf, iopbuf, size}), 4), 0);
        for (u32 i = 0; i < size - 64; i += 4) e.w32(eebuf + i, 0);  // memset(buf, 0, size - 64)
        return rmt != 0;
    }
    u32 ctrl() const { return e.r32(eebuf + size - 4); }  // the uncached read at obj+20 -> +60
    // rcv(buf) runs on a newer counter; snd(buf) fills the data area before the block goes out.
    template <class Rcv, class Snd>
    void exec(Rcv rcv, Snd snd) {
        if (stat == 1 && static_cast<s32>(cnt) < static_cast<s32>(ctrl())) {
            rcv(eebuf);
            cnt = ctrl();
            stat = 0;
            ++receives;
        }
        if (stat == 0) {
            snd(eebuf);
            ++cnt;
            e.w32(eebuf + size - 4, cnt);
            e.set_dma({DmaTransfer{eebuf, iopbuf, size, 0}});
            stat = 1;
            ++sends;
        }
    }
};

// One field: VBLANK_START, the IOP's vblank-end pass, then the rest of the field.
void field(EeSide& e) {
    e.bus.vblank();
    e.sif.service();
    e.bus.advance(500'000);
    e.sif.service();
    e.pump();
    e.bus.advance(kField - 500'000);
    e.sif.service();
}

std::vector<u8> urpc(EeSide& e, u32 cd, u32 n, std::initializer_list<u32> args, u32 nrecv) {
    return e.call_sync(cd, 1024 + n, words(args), 4 * nrecv);
}

// SJX / RNA block writers (EE side).
void put_sjx_entries(EeSide& e, u32 buf, const std::vector<std::array<u32, 3>>& entries /* iop_sjx, ptr, len */) {
    e.w32(buf, static_cast<u32>(entries.size()));
    for (std::size_t i = 0; i < entries.size(); ++i) {
        const u32 a = buf + 16 + 16 * static_cast<u32>(i);
        e.w32(a + 0, 0x00000100u);  // flag 0, line 1, id 0
        e.w32(a + 4, entries[i][0]);
        e.w32(a + 8, entries[i][1]);
        e.w32(a + 12, entries[i][2]);
    }
}
void put_rna_cmds(EeSide& e, u32 buf, const std::vector<std::array<u32, 4>>& cmds /* cmd, rna, v8, v12 */) {
    e.w32(buf, static_cast<u32>(cmds.size()));
    for (std::size_t i = 0; i < cmds.size(); ++i) {
        const u32 a = buf + 16 + 16 * static_cast<u32>(i);
        e.w32(a + 0, cmds[i][0] & 0xFFFFu);
        e.w32(a + 4, cmds[i][1]);
        e.w32(a + 8, cmds[i][2]);
        e.w32(a + 12, cmds[i][3]);
    }
}

// Collects every SJX return entry the EE receives: {ee_sjx, ptr, len} with byte0 = 0, byte1 = line.
struct Returns {
    std::vector<std::array<u32, 4>> got;  // line, ee_sjx, ptr, len
    void operator()(EeSide& e, u32 buf) {
        const u32 n = e.r32(buf);
        for (u32 i = 0; i < n; ++i) {
            const u32 a = buf + 16 + 16 * i;
            const u32 w0 = e.r32(a);
            REQUIRE((w0 & 0xFF) == 0);
            got.push_back({(w0 >> 8) & 0xFF, e.r32(a + 4), e.r32(a + 8), e.r32(a + 12)});
        }
    }
    u32 total(u32 ee_sjx) const {
        u32 t = 0;
        for (const auto& g : got)
            if (g[1] == ee_sjx) t += g[3];
        return t;
    }
};

// The CRI/PSM cases observe the PSM model's own pushes: SkMode::Constants keeps the SPU2 mixer out of the
// path (and the legacy IOP map), as every number below was taken (the mixer is tested in tests/audio).
inline IopConfig constants_cfg() {
    IopConfig c;
    c.sk_mode = SkMode::Constants;
    c.iop_layout = IopLayout::Legacy;
    return c;
}

struct Rig {
    EeSide e{constants_cfg()};
    u32 cd = 0;
    EeDtx sjx{e, 0, 0, kEeSjxBuf, kIopSjxBuf, kWk};
    EeDtx rna{e, 0, 1, kEeRnaBuf, kIopRnaBuf, kWk};
    audio::NullSink sink;
    u32 sj0 = 0, sj1 = 0, iop_sjx0 = 0, iop_sjx1 = 0, rna_h = 0;

    Rig() {
        e.init_rpc();
        e.sif.iop().set_audio_output(&sink);
        cd = e.bind(kDtxRpc);
        sjx.cd = rna.cd = cd;
    }
    // SJX_Init 0x564528, PS2RNA_Init 0x55FF70, ps2rna_init_psj 0x55F748 (two channels), PS2RNA_Create.
    void boot_cri(u32 urpc12_rate = 48000) {
        REQUIRE(sjx.create());
        urpc(e, cd, 3, {0, 0, 0}, 0);
        REQUIRE(rna.create());
        REQUIRE(load32(urpc(e, cd, 12, {urpc12_rate}, 1), 0) == 0);  // PS2RNA_InitIopSnd -> SPU core 0
        urpc(e, cd, 10, {16, 0x00130000u, 0x4040}, 0);
        sj0 = load32(urpc(e, cd, 34, {1, kIopPool, 256}, 1), 0);
        sj1 = load32(urpc(e, cd, 34, {1, kIopPool + 256, 256}, 1), 0);
        REQUIRE(sj0 != 0);
        REQUIRE(sj1 != 0);
        iop_sjx0 = load32(urpc(e, cd, 0, {0x7B0CD8u, sj0, 1, kEeSjxObj0}, 1), 0);
        iop_sjx1 = load32(urpc(e, cd, 0, {0x7B0D08u, sj1, 1, kEeSjxObj1}, 1), 0);
        REQUIRE(iop_sjx0 != 0);
        REQUIRE(iop_sjx1 != 0);
        rna_h = load32(urpc(e, cd, 8, {2, 0, sj0, sj1}, 1), 0);
        REQUIRE(rna_h != 0);
    }
    // PCM into IOP RAM by EE -> IOP DMA (what DTR_ExecHndl 0x558DD0 does).
    void dma_pcm(u32 iop, const std::vector<s16>& pcm) {
        const u32 src = 0x00990000u;
        e.write(src, std::as_bytes(std::span(pcm)));
        e.set_dma({DmaTransfer{src, iop, static_cast<u32>(pcm.size() * 2), 0}});
    }
};

}  // namespace

TEST_CASE("ADXI DTX: block out -> IOP counter (EE + 1) written back at its vblank-end pass -> next block") {
    Rig r;
    REQUIRE(r.sjx.create());
    CHECK(r.e.sif.iop().adxi_stats().dtx_open == 1);
    auto noop = [](u32) {};
    auto empty = [&](u32 buf) { r.e.w32(buf, 0); };
    // No block yet: the IOP waits (counter 0 in its zeroed buffer).
    field(r.e);
    CHECK(r.e.sif.iop().adxi_stats().dtx_blocks_in == 0);
    r.sjx.exec(noop, empty);  // first block: count 1
    for (u32 round = 1; round <= 5; ++round) {
        CHECK(r.sjx.ctrl() == 2 * round - 1);  // the EE sends odd counts
        // VBLANK_START and less than 22 H-lines later: nothing has come back yet.
        r.e.bus.vblank();
        r.e.sif.service();
        r.e.bus.advance(100'000);
        r.e.sif.service();
        CHECK(r.sjx.ctrl() == 2 * round - 1);
        // The IOP's pass: the whole 2176-byte buffer comes back carrying EE count + 1.
        r.e.bus.advance(400'000);
        r.e.sif.service();
        CHECK(r.sjx.ctrl() == 2 * round);
        r.e.bus.advance(kField - 500'000);
        r.e.sif.service();
        // The EE's next exec takes it (counter now > its own) and sends the next block in the same call.
        r.sjx.exec(noop, empty);
        CHECK(r.sjx.receives == round);
        CHECK(r.sjx.ctrl() == 2 * round + 1);
    }
    const AdxiStats st = r.e.sif.iop().adxi_stats();
    CHECK(st.dtx_blocks_in == 5);
    CHECK(st.dtx_blocks_out == 5);
}

TEST_CASE("ADXI DTX: steady ping-pong, the IOP buffer verbatim in the EE buffer, RNA reply has 0 entries") {
    Rig r;
    r.boot_cri();
    u32 rna_replies = 0;
    for (int f = 0; f < 30; ++f) {
        r.sjx.exec([](u32) {}, [&](u32 buf) { r.e.w32(buf, 0); });
        r.rna.exec([&](u32 buf) { CHECK(r.e.r32(buf) == 0); ++rna_replies; },  // 0x10F8 writes count 0
                   [&](u32 buf) { put_rna_cmds(r.e, buf, {{4, r.rna_h, 24000, 0}}); });
        field(r.e);
    }
    CHECK(r.sjx.receives == 29);  // the first exec only sends
    CHECK(rna_replies == 29);
    CHECK(r.sjx.cnt == 59);       // EE 59, IOP 60 written back, consumed next exec
    CHECK(r.sjx.ctrl() == 60);
    // The reply is the IOP buffer: identical bytes on both sides.
    const auto iop = r.e.sif.iop().ram();
    for (u32 i = 0; i < kWk; i += 4) {
        u32 w = 0;
        std::memcpy(&w, iop.data() + kIopSjxBuf + i, 4);
        REQUIRE(w == r.e.r32(kEeSjxBuf + i));
    }
}

TEST_CASE("ADXI DTX: create checks (alignment, id, in use), destroy, urpc buffer echo, unknown fn") {
    Rig r;
    CHECK(load32(r.e.call_sync(r.cd, 2, words({0, kEeSjxBuf + 4, kIopSjxBuf, kWk}), 4), 0) == 0);  // eewk % 64
    CHECK(load32(r.e.call_sync(r.cd, 2, words({0, kEeSjxBuf, kIopSjxBuf + 4, kWk}), 4), 0) == 0);  // iopwk % 32
    CHECK(load32(r.e.call_sync(r.cd, 2, words({0, kEeSjxBuf, kIopSjxBuf, 2170}), 4), 0) == 0);     // wklen % 64
    CHECK(load32(r.e.call_sync(r.cd, 2, words({16, kEeSjxBuf, kIopSjxBuf, kWk}), 4), 0) == 0);     // id >= 16
    const u32 h = load32(r.e.call_sync(r.cd, 2, words({0, kEeSjxBuf, kIopSjxBuf, kWk}), 4), 0);
    CHECK(h != 0);
    CHECK(load32(r.e.call_sync(r.cd, 2, words({0, kEeSjxBuf, kIopSjxBuf, kWk}), 4), 0) == 0);      // in use
    r.e.call_sync(r.cd, 3, words({h}), 0);
    CHECK(r.e.sif.iop().adxi_stats().dtx_open == 0);
    // An unregistered urpc (IRX 0x7A4: table entry 0) and fn 0/1: the request comes back unchanged.
    CHECK(urpc(r.e, r.cd, 20, {11, 22, 33}, 3) == words({11, 22, 33}));
    CHECK(r.e.call_sync(r.cd, 1, words({7, 8}), 8) == words({7, 8}));
}

TEST_CASE("ADXI SJX + PSM: data chunks in, 512-byte passes consumed at 24 kHz, merged chunks back, mix out") {
    Rig r;
    r.boot_cri();
    // 16 KiB per channel, constant PCM: ch0 1000, ch1 -2000.
    r.dma_pcm(kIopPcm, std::vector<s16>(8192, 1000));
    r.dma_pcm(kIopPcm + 0x4000, std::vector<s16>(8192, -2000));
    Returns back;
    bool handed = false, started = false;
    u64 frames_before_play = 0;
    // 18 fields = 300 ms < the 341 ms the 8192 samples last at 24 kHz.
    auto run = [&](int fields) {
    for (int f = 0; f < fields; ++f) {
        r.sjx.exec([&](u32 buf) { back(r.e, buf); },
                   [&](u32 buf) {
                       if (!handed) {
                           put_sjx_entries(r.e, buf, {{r.iop_sjx0, kIopPcm, 0x4000}, {r.iop_sjx1, kIopPcm + 0x4000, 0x4000}});
                           handed = true;
                       } else {
                           r.e.w32(buf, 0);
                       }
                   });
        r.rna.exec([](u32) {}, [&](u32 buf) {
            if (!started && handed) {
                put_rna_cmds(r.e, buf, {{4, r.rna_h, 24000, 0}, {2, r.rna_h, 1, 0}});
                frames_before_play = r.sink.end_frame();
                started = true;
            } else {
                r.e.w32(buf, 0);
            }
        });
        field(r.e);
    }
    };
    run(18);
    const AdxiStats st = r.e.sif.iop().adxi_stats();
    CHECK(st.sjx_chunks_in == 2);
    CHECK(st.rna_playing == 1);
    REQUIRE(st.psm_passes > 0);
    // Every byte consumed was returned to the EE (merged contiguous ranges) or is still in flight in
    // the IOP's free line until the next exchange.
    const u32 back0 = back.total(kEeSjxObj0), back1 = back.total(kEeSjxObj1);
    CHECK(back0 == back1);
    CHECK(back0 % 512 == 0);  // 256 samples (512 bytes) per 512-frame pass at 24 kHz
    CHECK(back0 > 0);
    CHECK(st.pcm_bytes_consumed >= 2ull * back0);
    for (const auto& g : back.got) {
        CHECK(g[0] == 0);  // returned on line 0 (free)
        CHECK(((g[1] == kEeSjxObj0 && g[2] >= kIopPcm && g[2] < kIopPcm + 0x4000) ||
               (g[1] == kEeSjxObj1 && g[2] >= kIopPcm + 0x4000 && g[2] < kIopPcm + 0x8000)));
    }
    // The ranges come back in order and tile the buffer from its start.
    u32 next0 = kIopPcm;
    for (const auto& g : back.got)
        if (g[1] == kEeSjxObj0) {
            CHECK(g[2] == next0);
            next0 += g[3];
        }
    CHECK(r.sink.non_silent_frames() > 0);
    CHECK(r.sink.end_frame() > frames_before_play);
    CHECK(st.underrun_samples == 0);
    // Keep going past the end of the data: every byte comes back exactly once, then underruns.
    run(30);
    CHECK(back.total(kEeSjxObj0) == 0x4000);
    CHECK(back.total(kEeSjxObj1) == 0x4000);
    CHECK(r.e.sif.iop().adxi_stats().pcm_bytes_consumed == 2u * 0x4000);
    CHECK(r.e.sif.iop().adxi_stats().underrun_samples > 0);
}

TEST_CASE("ADXI PSM: stereo pans pass the channels through; volume/pan law values (IRX 0x27E4)") {
    using hle::sif::detail::psm_side_gain;
    CHECK(psm_side_gain(255, -15, 0, false) == 255);
    CHECK(psm_side_gain(255, -15, 0, true) == 0);
    CHECK(psm_side_gain(255, 0, 0, false) == 180);   // centre: table entry 15 = 180 (-3 dB)
    CHECK(psm_side_gain(181, -15, 0, false) == 181); // the title's BGM (PCSX2 state: vol 181, pans -15/15)
    CHECK(psm_side_gain(181, 15, 0, true) == 181);
    CHECK(psm_side_gain(181, 0, 0, false) == 128);
    CHECK(psm_side_gain(255, 0, 15, false) == 0);
    CHECK(psm_side_gain(255, 0, 15, true) == 180);
    CHECK(psm_side_gain(100, 7, -3, false) == 40);
    CHECK(psm_side_gain(100, 7, -3, true) == 73);
    CHECK(psm_side_gain(999, -99, 99, false) == psm_side_gain(255, -15, 15, false));  // clamped
}

namespace {
// Plays 16 KiB of constant PCM per channel with the given RNA commands; returns the sink.
struct PlayResult {
    u64 hash = 0;
    u64 frames = 0;
    std::vector<s16> last;  // the last pushed pass
};
class Capture final : public audio::AudioSink {
public:
    std::vector<s16> last;
    audio::NullSink null;
    void push(u64 first, std::span<const s16> s) override {
        last.assign(s.begin(), s.end());
        null.push(first, s);
    }
};
PlayResult play(std::vector<std::array<u32, 4>> extra_cmds, int fields) {
    Rig r;
    Capture cap;
    r.e.sif.iop().set_audio_output(&cap);
    r.boot_cri();
    r.dma_pcm(kIopPcm, std::vector<s16>(8192, 1000));
    r.dma_pcm(kIopPcm + 0x4000, std::vector<s16>(8192, -2000));
    bool handed = false, started = false;
    for (int f = 0; f < fields; ++f) {
        r.sjx.exec([](u32) {}, [&](u32 buf) {
            if (!handed) put_sjx_entries(r.e, buf, {{r.iop_sjx0, kIopPcm, 0x4000}, {r.iop_sjx1, kIopPcm + 0x4000, 0x4000}});
            else r.e.w32(buf, 0);
            handed = true;
        });
        r.rna.exec([](u32) {}, [&](u32 buf) {
            if (!started) {
                std::vector<std::array<u32, 4>> c = {{4, r.rna_h, 24000, 0}};
                for (auto x : extra_cmds) c.push_back({x[0], r.rna_h, x[2], x[3]});
                c.push_back({2, r.rna_h, 1, 0});
                put_rna_cmds(r.e, buf, c);
                started = true;
            } else {
                r.e.w32(buf, 0);
            }
        });
        field(r.e);
    }
    return PlayResult{cap.null.hash(), cap.null.frames(), cap.last};
}
}  // namespace

TEST_CASE("ADXI PSM: mixed output values for centre pans and for -15/+15 pans") {
    const PlayResult centre = play({}, 8);
    REQUIRE(centre.last.size() == 1024);
    for (std::size_t f = 0; f < 512; ++f) {
        CHECK(centre.last[2 * f] == 705 - 1411);
        CHECK(centre.last[2 * f + 1] == 705 - 1411);
    }
    const PlayResult stereo = play({{9, 0, 0, static_cast<u32>(-15)}, {9, 0, 1, 15}}, 8);
    for (std::size_t f = 0; f < 512; ++f) {
        CHECK(stereo.last[2 * f] == 1000);
        CHECK(stereo.last[2 * f + 1] == -2000);
    }
    const PlayResult quiet = play({{5, 0, 0, 0}}, 8);  // command 5: volume 0
    for (s16 s : quiet.last) CHECK(s == 0);
}

TEST_CASE("ADXI PSM: the output depends on virtual time only (two runs, same fingerprint)") {
    const PlayResult a = play({{9, 0, 0, static_cast<u32>(-15)}, {9, 0, 1, 15}}, 12);
    const PlayResult b = play({{9, 0, 0, static_cast<u32>(-15)}, {9, 0, 1, 15}}, 12);
    CHECK(a.frames > 0);
    CHECK(a.frames == b.frames);
    CHECK(a.hash == b.hash);
}

TEST_CASE("ADXI SJUNI urpcs (SJRMT): put merges, get splits, num data, unget") {
    Rig r;
    const u32 sj = load32(urpc(r.e, r.cd, 34, {1, kIopPool, 256}, 1), 0);
    REQUIRE(sj != 0);
    urpc(r.e, r.cd, 40, {sj, 0, 0x1000, 0x100}, 0);
    urpc(r.e, r.cd, 40, {sj, 0, 0x1100, 0x80}, 0);  // continues the tail: merged
    CHECK(load32(urpc(r.e, r.cd, 41, {sj, 0}, 1), 0) == 0x180);
    const auto c = urpc(r.e, r.cd, 38, {sj, 0, 0x40}, 2);  // split
    CHECK(load32(c, 0) == 0x1000);
    CHECK(load32(c, 4) == 0x40);
    CHECK(load32(urpc(r.e, r.cd, 41, {sj, 0}, 1), 0) == 0x140);
    urpc(r.e, r.cd, 39, {sj, 0, 0x1000, 0x40}, 0);  // unget back in front
    const auto all = urpc(r.e, r.cd, 38, {sj, 0, 0x7FFFFFFF}, 2);
    CHECK(load32(all, 0) == 0x1000);
    CHECK(load32(all, 4) == 0x180);
    CHECK(load32(urpc(r.e, r.cd, 41, {sj, 1}, 1), 0) == 0);
}

TEST_CASE("ADXI: pause-all (command 11) stops the output clock; the timeline resumes later") {
    Rig r;
    r.boot_cri();
    for (int f = 0; f < 4; ++f) {
        r.sjx.exec([](u32) {}, [&](u32 buf) { r.e.w32(buf, 0); });
        r.rna.exec([](u32) {}, [&](u32 buf) { r.e.w32(buf, 0); });
        field(r.e);
    }
    const u64 passes = r.e.sif.iop().adxi_stats().psm_passes;
    CHECK(passes > 0);
    r.rna.exec([](u32) {}, [&](u32 buf) { put_rna_cmds(r.e, buf, {{11, 0, 1, 0}}); });
    field(r.e);
    const u64 paused_at = r.e.sif.iop().adxi_stats().psm_passes;
    for (int f = 0; f < 4; ++f) field(r.e);
    CHECK(r.e.sif.iop().adxi_stats().psm_passes == paused_at);
    r.rna.exec([](u32) {}, [&](u32 buf) { put_rna_cmds(r.e, buf, {{11, 0, 0, 0}}); });
    field(r.e);
    field(r.e);
    CHECK(r.e.sif.iop().adxi_stats().psm_passes > paused_at);
    CHECK(r.sink.gap_frames() > 0);  // the paused span is a gap on the timeline
}

TEST_CASE("SDRDRV/SK: the values the constant model returns for the H_Sndcom bank and voice flow (SkMode::Constants)") {
    EeSide e(constants_cfg());  // the interpreted modules answer this flow in tests/sif/test_sk_modules.cpp
    e.init_rpc();
    const u32 sd = e.bind(0x80000701u);
    auto sk = [&](u32 module, u32 fn, std::initializer_list<u32> args) {
        std::vector<u8> blk(64, 0);
        store32(blk, 0, module);
        store32(blk, 4, fn);
        std::size_t i = 8;
        for (u32 a : args) {
            store32(blk, i, a);
            i += 4;
        }
        return static_cast<s32>(load32(e.call_sync(sd, 0x90F0, blk, 16), 0));
    };
    const u32 m1 = static_cast<u32>(-1);
    // H_Sndcom_Init 0x10CAC0: SOUND_Control(0,143,0), (3,131,261), (3,132,60), (3,130,1), (3,128,127) -> 0.
    CHECK(sk(0, 2, {0, 143, 0}) == 0);
    CHECK(sk(0, 2, {3, 131, 261, 60, 0}) == 0);
    CHECK(sk(0, 2, {3, 132, 60, 60}) == 0);
    CHECK(sk(0, 2, {3, 130, 1}) == 0);
    CHECK(sk(0, 2, {3, 128, 127, 127}) == 0);
    CHECK(sk(0, 2, {3, 0x77, 0}) == -310);  // unknown Control command
    // H_Sndcom_Update 0x10D2A8..0x10D3B4, slot 0 then slot 1: 0-based IRX slot indices.
    for (s32 slot = 0; slot < 2; ++slot) {
        const s32 bank = sk(0x1000000, 0, {3, m1, 0x100000, 100, 0x5000, 200});
        const s32 port = sk(0x1000000, 0, {5, m1, static_cast<u32>(bank), 0});
        const s32 seq = sk(0x4000000, 0, {0, m1, 0x110000, 300});
        const s32 ctl = sk(0x4000000, 0, {5, static_cast<u32>(port), static_cast<u32>(seq)});
        CHECK(bank == slot);
        CHECK(port == slot);
        CHECK(seq == slot);
        CHECK(ctl == port);  // SESQ_Bind(5, port, entry) returns the port (SKSESQ 0xA88)
    }
    CHECK(sk(0x4000000, 0, {5, 0, 0}) == -202);                 // port 0 already has a sequence
    CHECK(sk(0x1000000, 0, {5, m1, 7, 0}) == -201);             // entry 7 not bound
    // Play / status / stop (H_Sndcom_PlayVoice 0x10DB60, StopVoice 0x10DA70).
    const s32 t0 = sk(0x4000000, 2, {0, 0, 10, 4});
    const s32 t1 = sk(0x4000000, 2, {0, 0, 10, 5});
    CHECK(t0 == 0);
    CHECK(t1 == 1);
    CHECK(sk(0x4000000, 3, {0, 1, 10, static_cast<u32>(t0)}) == 0);
    CHECK(sk(0x4000000, 2, {0, 2, 10, static_cast<u32>(t0)}) == 0);
    CHECK(sk(0x4000000, 2, {0, 0, 10, 6}) == 0);  // the freed track is reused
    // Unbinds (H_Sndcom_UnbindSfx 0x10D950) free the slots for the next bank.
    CHECK(sk(0x4000000, 1, {5, 0}) == 0);
    CHECK(sk(0x4000000, 1, {0, 0}) == 0);
    CHECK(sk(0x1000000, 1, {5, 0}) == 0);
    CHECK(sk(0x1000000, 1, {3, 0}) == 0);
    CHECK(sk(0x1000000, 0, {3, m1, 0x100000, 100, 0x5000, 200}) == 0);
    // Unregistered SK module and SDRDRV codes.
    CHECK(sk(0x2000000, 0, {}) == -310);
    // SOUND_Send(1, iop, spu, n): the bytes land in the SPU2 shadow, result = size.
    const u32 src = 0x00990000u;
    std::vector<u8> bank(64);
    for (std::size_t i = 0; i < bank.size(); ++i) bank[i] = static_cast<u8>(i * 3 + 1);
    e.write(src, bank);
    e.set_dma({DmaTransfer{src, 0x00140000u, 64, 0}});
    CHECK(sk(0, 10, {1, 0x00140000u, 0x5000, 64}) == 64);
    // 0x8010 SetParam / 0x8020 GetParam / 0xE620 callback init (sceSdRemote's 64-byte block).
    auto sd_call = [&](u32 code, u32 a1, u32 a2) {
        return static_cast<s32>(load32(e.call_sync(sd, code, words({0x96E000, a1, a2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 16), 0));
    };
    CHECK(sd_call(0x8010, 0x980, 0x3FFF) == 0);
    CHECK(sd_call(0x8020, 0x980, 0) == 0x3FFF);
    CHECK(sd_call(0xE620, 0x780000, 0x780000) == 0);
    CHECK(sd_call(0x9000, 0, 0) == 0);  // unregistered user slot
}
