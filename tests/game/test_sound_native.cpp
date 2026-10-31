// Modernize layer 3 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of CRI's PS2RNA
// (game/include/p3fes/game/sound_native.h) with the host's output (runtime/native/sound/native_sound.h) installed,
// on the ELF's own code: PS2RNA_Init opens the output without SJX / DTX; PS2RNA_Create lays the record out
// as the faithful code does; a player's PCM leaves its output joint through the native ExecServer (started in one
// call, completed in the next: the chunk back on the joint's free line), GetNumData / GetNumRoom count it; the
// faithful setters' fields reach the output as the command builder's commands at its next pass; the transfer
// switch and Destroy. Without the service the same bodies run their faithful path (the pair tests of test_libs14 /
// test_libs25 / test_libs26 cover those byte for byte).
#include "pair_harness.h"
#include "stand_ins.h"

#include "native_sound.h"
#include "p3fes/game/sound_native.h"

#include <cstring>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using namespace p3fes::game_test;
namespace ns = p3fes::native::sound;

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
void fn_PS2RNA_Init_0055ff70(EEContext&);
void fn_PS2RNA_Create_00560758(EEContext&);
void fn_sub_560AF8_00560af8(EEContext&);  // destroy
void fn_sub_560C88_00560c88(EEContext&);  // transfer switch
void fn_sub_560D20_00560d20(EEContext&);  // play switch (+80)
void fn_sub_560EB0_00560eb0(EEContext&);  // GetNumData
void fn_sub_560F18_00560f18(EEContext&);  // GetNumRoom
void fn_PS2RNA_ExecServer_00561138(EEContext&);
void fn_sub_541B70_00541b70(EEContext&);  // ADXRNA_SetSfreq
void fn_sub_541B88_00541b88(EEContext&);  // ADXRNA_SetOutVol
void fn_sub_562288_00562288(EEContext&);  // SJRBF_Init
void fn_sub_562388_00562388(EEContext&);  // SJRBF_Create
void fn_sub_562630_00562630(EEContext&);  // SJRBF_GetNumData
void fn_sub_562680_00562680(EEContext&);  // SJRBF_GetChunk
void fn_sub_562880_00562880(EEContext&);  // SJRBF_PutChunk
void fn_sceSdRemote_005129c0(EEContext&);
}  // namespace p3fes::recomp_gen

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

namespace {

namespace gen = ::p3fes::recomp_gen;

struct ServiceScope {
    explicit ServiceScope(ns::SoundService* s) { ns::g_service = s; }
    ~ServiceScope() { ns::g_service = nullptr; }
};

u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void st32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

constexpr u32 kBuf = kArena + 0x100;  // the joint's ring (8 KiB + 64 bytes of mirror)
constexpr u32 kRing = 0x2000;
constexpr u32 kCk = kArena;           // a chunk {data, len}
constexpr u32 kSjArray = kArena + 0x10;
constexpr u32 kDtxObjects = 0x7A1160u;  // the EE's DTX objects (16 x 68): never made in native mode
constexpr u32 kIopHeapWords[] = {0x7B1AC4u, 0x7A93FCu, 0x7A9444u, 0x7A940Cu};  // SJX / PSJ / RNA DTX / PSM blocks

}  // namespace

TEST_CASE("game(sound_native): PS2RNA with --native sound plays a player's joint on the host's output") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    ns::NativeSound out;
    out.set_pass_delay(100);
    ServiceScope svc(&out);

    // a player's output joint with 4 KiB of PCM on its data line (SJRBF on the ELF's code)
    run(m, &gen::fn_sub_562288_00562288, {}, 1);
    const u32 sj = static_cast<u32>(run(m, &gen::fn_sub_562388_00562388, {kBuf, kRing, 64, 0}, 2).v0);
    REQUIRE(sj != 0);
    run(m, &gen::fn_sub_562680_00562680, {sj, 0, 4096, kCk}, 3);  // free space
    REQUIRE(ld32(m, kCk + 4) == 4096);
    const u32 data = ld32(m, kCk);
    for (u32 i = 0; i < 2048; ++i) {
        const s16 v = static_cast<s16>(i * 3 - 3000);
        std::memcpy(m.at(data + 2 * i), &v, 2);
    }
    run(m, &gen::fn_sub_562880_00562880, {sj, 1, kCk, 0}, 4);  // onto the data line
    REQUIRE(run(m, &gen::fn_sub_562630_00562630, {sj, 1, 0, 0}, 5).v0 == 4096);

    // Init: the output opens; the IOP's answers are written as the faithful EE side keeps them; no SJX / DTX, no IOP
    // heap block
    run(m, &gen::fn_PS2RNA_Init_0055ff70, {}, 6);
    CHECK(ld32(m, 0x7A943Cu) == 1);  // the reference count
    CHECK(ld32(m, 0x7A9438u) == 0);  // core 0 (urpc 12's reply)
    CHECK(ld32(m, 0x7A9430u) == 1);  // PCM transfer on core 0
    for (u32 o = 0; o < 16 * 68; ++o) REQUIRE(m.at(kDtxObjects)[o] == 0);
    for (u32 w : kIopHeapWords) CHECK(ld32(m, w) == 0);

    // Create: the record as PS2RNA_Create lays it out (no PSJ, no DTR, +32 = the record itself)
    st32(m, kSjArray, sj);
    const u32 rec = static_cast<u32>(run(m, &gen::fn_PS2RNA_Create_00560758, {kSjArray, 1, 0, 0}, 7).v0);
    REQUIRE(rec == ns::kRnaTable);
    CHECK(m.at(rec)[0] == 1);
    CHECK(ld32(m, rec + 4) == 1);
    CHECK(ld32(m, rec + 8) == 0);   // no PSJ
    CHECK(ld32(m, rec + 16) == 0);  // no DTR
    CHECK(ld32(m, rec + 24) == sj);
    CHECK(ld32(m, rec + 32) == rec);
    CHECK(ld32(m, rec + 40) == kRing);  // the joint's data + free bytes
    CHECK(ld32(m, rec + 44) == ns::kRnaBufBytes);
    CHECK((m.at(rec)[82] == 1 && m.at(rec)[83] == 1 && m.at(rec)[88] == 0 && m.at(rec)[89] == 1));
    CHECK(run(m, &gen::fn_sub_560EB0_00560eb0, {rec, 0, 0, 0}, 8).v0 == 0);
    CHECK(run(m, &gen::fn_sub_560F18_00560f18, {rec, 0, 0, 0}, 9).v0 == ns::kRnaBufBytes / 2);

    // ADXT's start: sample rate and volume (faithful setters: record fields), play, transfer on (native)
    run(m, &gen::fn_sub_541B70_00541b70, {rec, 48000, 0, 0}, 10);
    CHECK(ld32(m, rec + 48) == 48000);
    run(m, &gen::fn_sub_541B88_00541b88, {rec, 0, 0, 0}, 11);
    run(m, &gen::fn_sub_560D20_00560d20, {rec, 1, 0, 0}, 12);
    run(m, &gen::fn_sub_560C88_00560c88, {rec, 1, 0, 0}, 13);
    CHECK(m.at(rec)[88] == 1);
    m.at(rec + 91)[0] = 1;  // a discard left over from a stop: the restart clears it

    // ExecServer 1: the restart, the transfer starts (the chunk leaves the data line), the first block goes out
    run(m, &gen::fn_PS2RNA_ExecServer_00561138, {}, 14);
    CHECK(m.at(rec)[91] == 0);
    CHECK(run(m, &gen::fn_sub_562630_00562630, {sj, 1, 0, 0}, 15).v0 == 0);         // taken off the data line
    CHECK(run(m, &gen::fn_sub_562630_00562630, {sj, 0, 0, 0}, 16).v0 == kRing - 4096);  // not yet freed
    CHECK(run(m, &gen::fn_sub_560EB0_00560eb0, {rec, 0, 0, 0}, 17).v0 == 2048);     // GetNumData: handed over
    CHECK(run(m, &gen::fn_sub_560F18_00560f18, {rec, 0, 0, 0}, 18).v0 == ns::kRnaBufBytes / 2 - 2048);
    CHECK(m.at(rec)[81] == 1);  // the builder updated its old / new pair (play switch sent)
    CHECK(ld32(m, rec + 52) == 48000);
    CHECK(out.stats().blocks == 1);
    // ExecServer 2: the transfer completes (the chunk back on the free line); the block is still in flight
    run(m, &gen::fn_PS2RNA_ExecServer_00561138, {}, 19);
    CHECK(run(m, &gen::fn_sub_562630_00562630, {sj, 0, 0, 0}, 20).v0 == kRing);
    CHECK(out.stats().blocks == 1);
    CHECK(out.stats().pcm_bytes_in == 4096);

    // the output's pass takes the first block: its commands (the sample rate, play; the volume is unchanged) start
    // the stream; the PCM completed in ExecServer 2 waits for the next block, as DTX's ping-pong has it
    out.vblank(1, 2'000'000);
    out.advance(out.next_deadline());
    CHECK(out.stats().starts == 1);
    CHECK(out.stats().commands == 2);
    run(m, &gen::fn_PS2RNA_ExecServer_00561138, {}, 21);  // accepts the answer, sends the PCM
    CHECK(out.stats().blocks == 2);
    out.vblank(2, 2'500'000);
    out.advance(out.next_deadline());                     // the PCM enters the output
    out.vblank(3, 20'000'000);  // ~3,255 frames: the 2,048 samples (four 512-frame passes) have played
    out.advance(out.next_deadline());
    CHECK(out.stats().pcm_bytes_played == 4096);
    // what was played is given back with the answer to the next block, which the server accepts after that
    run(m, &gen::fn_PS2RNA_ExecServer_00561138, {}, 22);
    CHECK(run(m, &gen::fn_sub_560EB0_00560eb0, {rec, 0, 0, 0}, 23).v0 == 2048);
    out.vblank(4, 22'000'000);
    out.advance(out.next_deadline());
    run(m, &gen::fn_PS2RNA_ExecServer_00561138, {}, 24);
    CHECK(run(m, &gen::fn_sub_560EB0_00560eb0, {rec, 0, 0, 0}, 25).v0 == 0);

    // transfer off, destroy
    run(m, &gen::fn_sub_560C88_00560c88, {rec, 0, 0, 0}, 24);
    CHECK((m.at(rec)[88] == 0 && m.at(rec)[89] == 1));
    run(m, &gen::fn_sub_560AF8_00560af8, {rec, 0, 0, 0}, 25);
    CHECK(m.at(rec)[0] == 0);
    CHECK(out.stats().destroys == 1);
    for (u32 o = 0; o < 16 * 68; ++o) REQUIRE(m.at(kDtxObjects)[o] == 0);
}

namespace {
// Steps 2-3, --native-sk direct: a service whose SK stack "runs natively" and records what sceSdRemote hands it.
struct SkRecorder final : ns::SoundService {
    struct Call {
        u32 fno = 0;
        std::vector<u8> send;
        std::size_t recv = 0;
    };
    std::vector<Call> calls;
    u32 answer = 0;
    void rna_open(u64) override {}
    void rna_close(u64) override {}
    void rna_create(u64, u32, u32) override {}
    void rna_destroy(u64, u32) override {}
    void rna_transfer(u64, u32, bool) override {}
    bool rna_try_restart(u64, u32) override { return false; }
    bool rna_transfer_running(u32) const override { return false; }
    u32 rna_inflight_bytes(u32, u32) const override { return 0; }
    u32 rna_dma_room(u32, u32) const override { return 0; }
    void rna_dma_start(u64, u32, u32, u32, u32) override {}
    bool rna_dma_pending(u32, u32, u32&, u32&) const override { return false; }
    void rna_dma_done(u64, u32, u32, std::span<const s16>) override {}
    bool rna_exchange(u64) override { return false; }
    void rna_command(u64, const ns::RnaCommand&) override {}
    void rna_send(u64) override {}
    bool sk_native() const override { return true; }
    void sd_remote(u64, u32 fno, std::span<const u8> send, std::span<u8> recv) override {
        calls.push_back({fno, std::vector<u8>(send.begin(), send.end()), recv.size()});
        std::memset(recv.data(), 0, recv.size());
        if (recv.size() >= 4) std::memcpy(recv.data(), &answer, 4);
    }
};
}  // namespace

TEST_CASE("game(sound_native): with the SK stack native (--native-sk direct), sceSdRemote's RPCs go to the service") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    SkRecorder sk;
    ServiceScope scope(&sk);
    // a libsd remote call: SetParam(0x980, 0x3FFF) -- the 64-byte argument block, 16 bytes back into it, word 0 the result
    sk.answer = 0x00001234u;
    CHECK(run(m, &gen::fn_sceSdRemote_005129c0, {1, 0x8010, 0x980, 0x3FFF}, 1).v0 == 0x1234u);
    REQUIRE(sk.calls.size() == 1);
    CHECK(sk.calls[0].fno == 0x8010u);
    REQUIRE(sk.calls[0].send.size() == 64);
    u32 w[3];
    std::memcpy(w, sk.calls[0].send.data(), sizeof w);
    CHECK(w[0] == 0x0096E000u);  // the block's own EE address (sdr_rpc_argblk)
    CHECK(w[1] == 0x980u);
    CHECK(w[2] == 0x3FFFu);
    CHECK(sk.calls[0].recv == 16);
    // a Standard Kit command: the caller's 64-byte block goes as it is (0x9000..0x90F0: send = arg 2, size = arg 3)
    const u32 blk = kArena + 0x400;
    const u32 words[6] = {0x04000000u, 2, 0, 0, 10, 1};  // SESQ_Control(port 0, play, type 10, group 1)
    std::memcpy(m.at(blk), words, sizeof words);
    sk.answer = 5;
    CHECK(run(m, &gen::fn_sceSdRemote_005129c0, {1, 0x90F0, blk, 64}, 2).v0 == 5u);
    REQUIRE(sk.calls.size() == 2);
    CHECK(sk.calls[1].fno == 0x90F0u);
    REQUIRE(sk.calls[1].send.size() == 64);
    CHECK(std::memcmp(sk.calls[1].send.data(), words, sizeof words) == 0);
}
#endif  // P3FES_GAME_HAVE_GENERATED
