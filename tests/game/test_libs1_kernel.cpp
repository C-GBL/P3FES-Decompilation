// Pair tests of slice libs1, the timer-alarm counter operations and sceSpu2Mem (game/src/lib/libs1_kernel.cpp),
// through tests/game/libs1_util.h. The timer itself is served by stand-ins: sub_50E508 (reads the hardware counter:
// a deterministic clock that advances 1,000 ticks per read) and sub_50E000 (programs the compare register: a recorder);
// sce1's hand-written pool functions (insert / unlink / allocate / free) run. Inputs: alarm pools built as sce1's tests
// build them (game/include/p3fes/game/sce.h `sce::alarm`), every counter operation over running / stopped / armed
// records and the error ids; sceSpu2MemInit / Quit and sceSpu2MemFree over built tables of allocated blocks freed in random order (after
// every free the list covers 0x5010 .. the end without gaps and no two neighbours are both free; after the last one the
// table is one free block again) and over the allocated blocks of the dorm snapshot's table. sceSpu2MemAllocate stays
// recompiled (test_field8_sys stands it in).
//@INCLUDES
#include "p3fes/game/sce.h"
//@END
#include "libs1_util.h"

#include "p3fes/game/libs1_kernel.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_50E850_0050e850(EEContext&);  // generated body
void fn_sub_50E850_0050e850__recomp(EEContext&);  // recompiled
void fn_sub_50E950_0050e950(EEContext&);  // generated body
void fn_sub_50E950_0050e950__recomp(EEContext&);  // recompiled
void fn_sub_50EBE8_0050ebe8(EEContext&);  // generated body
void fn_sub_50EBE8_0050ebe8__recomp(EEContext&);  // recompiled
void fn_sub_50ECA8_0050eca8(EEContext&);  // generated body
void fn_sub_50ECA8_0050eca8__recomp(EEContext&);  // recompiled
void fn_iSetTimerAlarm_0050f1c0(EEContext&);  // generated body
void fn_iSetTimerAlarm_0050f1c0__recomp(EEContext&);  // recompiled
void fn_iReleaseTimerAlarm_0050f358(EEContext&);  // generated body
void fn_iReleaseTimerAlarm_0050f358__recomp(EEContext&);  // recompiled
void fn_sceSpu2MemInit_0051d5b0(EEContext&);  // generated body
void fn_sceSpu2MemInit_0051d5b0__recomp(EEContext&);  // recompiled
void fn_sceSpu2MemQuit_0051d6b0(EEContext&);  // generated body
void fn_sceSpu2MemQuit_0051d6b0__recomp(EEContext&);  // recompiled
void fn_sceSpu2MemFree_0051d908(EEContext&);  // generated body
void fn_sceSpu2MemFree_0051d908__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using p3fes::game_test::libs1::Case;

const Case kCases[] = {
    {"sub_50E850", 0x50E850, &recomp_gen::fn_sub_50E850_0050e850, &recomp_gen::fn_sub_50E850_0050e850__recomp},
    {"sub_50E950", 0x50E950, &recomp_gen::fn_sub_50E950_0050e950, &recomp_gen::fn_sub_50E950_0050e950__recomp},
    {"sub_50EBE8", 0x50EBE8, &recomp_gen::fn_sub_50EBE8_0050ebe8, &recomp_gen::fn_sub_50EBE8_0050ebe8__recomp},
    {"sub_50ECA8", 0x50ECA8, &recomp_gen::fn_sub_50ECA8_0050eca8, &recomp_gen::fn_sub_50ECA8_0050eca8__recomp},
    {"iSetTimerAlarm", 0x50F1C0, &recomp_gen::fn_iSetTimerAlarm_0050f1c0, &recomp_gen::fn_iSetTimerAlarm_0050f1c0__recomp},
    {"iReleaseTimerAlarm", 0x50F358, &recomp_gen::fn_iReleaseTimerAlarm_0050f358, &recomp_gen::fn_iReleaseTimerAlarm_0050f358__recomp},
    {"sceSpu2MemInit", 0x51D5B0, &recomp_gen::fn_sceSpu2MemInit_0051d5b0, &recomp_gen::fn_sceSpu2MemInit_0051d5b0__recomp},
    {"sceSpu2MemQuit", 0x51D6B0, &recomp_gen::fn_sceSpu2MemQuit_0051d6b0, &recomp_gen::fn_sceSpu2MemQuit_0051d6b0__recomp},
    {"sceSpu2MemFree", 0x51D908, &recomp_gen::fn_sceSpu2MemFree_0051d908, &recomp_gen::fn_sceSpu2MemFree_0051d908__recomp},
};

using namespace p3fes::game_test::libs1;
namespace al = p3fes::game::sce::alarm;
namespace ls = p3fes::game::libs1::spu2;

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kReadTimer = 0x50E508u, kSetCompare = 0x50E000u;
constexpr u32 kRecs = 0x01830000u;       // 8 alarm records, 64-byte aligned
constexpr u32 kSpuTable = 0x01834000u;   // a caller's SPU2 block table

const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }

void stand_ins(StandInWorld& w) {
    auto clock = std::make_shared<u64>(0x100000);
    w.si.install(kReadTimer, "sub_50E508 (read the timer)", [clock](EEContext&, StandIns&, StandInCall& c) {
        *clock += 1000;
        c.v0 = *clock;
    });
    w.si.install_recorder(kSetCompare, "sub_50E000 (program the compare)", 0);
}

void fresh_pool(Machine& m) {
    w32(m, al::kSetUp, 0);
    w32(m, al::kInUse, 0);
    w32(m, al::kTagSeq, 0);
    w32(m, al::kPending, 0);
    w32(m, al::kHandling, 0);
    w32(m, al::kCursor, 0);
    for (u32 i = 0; i < 8; ++i) {
        wzero(m, kRecs + 64 * i, 64);
        w32(m, kRecs + 64 * i + al::kNext, i < 7 ? kRecs + 64 * (i + 1) : 0);
    }
    w32(m, al::kFreeList, kRecs);
}
// A record in use with tag `tag`, as sub_50E5D8 leaves it; returns its id.
u32 use_record(Machine& m, u32 i, u32 tag, u32 flags = 0) {
    const u32 rec = kRecs + 64 * i;
    w32(m, rec + al::kTag, tag);
    w32(m, rec + al::kFlags, flags);
    return (rec >> 6 << 10) | tag;
}

}  // namespace

TEST_CASE("game(libs1_kernel): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, 32, stand_ins);
}

TEST_CASE("game(libs1_kernel): timer counters -- start, stop, time, arm") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 1;
    fresh_pool(*m);
    const u32 id = use_record(*m, 2, 0x35);
    const u32 rec = kRecs + 128;
    // bad ids: negative, wrong tag, the handler's own id
    CHECK(v0_of(pair(*m, C("sub_50E850"), {sx(0x80000000u | id)}, seed++, "start negative", stand_ins)) == sx(0x80008002u));
    CHECK(v0_of(pair(*m, C("sub_50E850"), {id ^ 2}, seed++, "start wrong tag", stand_ins)) == sx(0x80008002u));
    w32(*m, al::kHandling, id);
    CHECK(v0_of(pair(*m, C("sub_50E850"), {id}, seed++, "start own handler", stand_ins)) == sx(0x80000010u));
    CHECK(v0_of(pair(*m, C("sub_50E950"), {id}, seed++, "stop own handler", stand_ins)) == sx(0x80000010u));
    CHECK(v0_of(pair(*m, C("sub_50ECA8"), {id, 0, 0, 0}, seed++, "arm own handler", stand_ins)) == sx(0x80000010u));
    w32(*m, al::kHandling, 0);
    CHECK(v0_of(pair(*m, C("sub_50EBE8"), {id ^ 4}, seed++, "time wrong tag", stand_ins)) == ~0ull);
    // start: the start time from the timer, the running bit
    w64(*m, rec + al::kU64B, 5000);  // the total so far
    auto r = pair(*m, C("sub_50E850"), {id}, seed++, "start", stand_ins);
    CHECK(v0_of(r) == 0);
    CHECK((r32(*m, rec + al::kFlags) & 1u) == 1u);
    CHECK(r64(*m, rec + al::kU64A) == 0x100000 + 1000);
    CHECK(last_log().calls_to(kSetCompare) == 0);  // not armed: nothing to reprogram
    CHECK(v0_of(pair(*m, C("sub_50E850"), {id}, seed++, "start again", stand_ins)) == 1);
    // time while running: the total plus the running stretch (each pair's stand-in clock starts again: 700 ticks)
    w64(*m, rec + al::kU64A, 0x100000 + 1000 - 700);
    CHECK(v0_of(pair(*m, C("sub_50EBE8"), {id}, seed++, "time running", stand_ins)) == 5000 + 700);
    // stop: the stretch added to the total, the running bit cleared
    r = pair(*m, C("sub_50E950"), {id}, seed++, "stop", stand_ins);
    CHECK(v0_of(r) == 1);
    CHECK((r32(*m, rec + al::kFlags) & 1u) == 0u);
    CHECK(r64(*m, rec + al::kU64B) == 5000 + 700);
    CHECK(v0_of(pair(*m, C("sub_50E950"), {id}, seed++, "stop again", stand_ins)) == 0);
    CHECK(v0_of(pair(*m, C("sub_50EBE8"), {id}, seed++, "time stopped", stand_ins)) == 5000 + 700);
    // arm: target, handler, argument; running + armed goes onto the pending list, the compare is reprogrammed
    pair(*m, C("sub_50E850"), {id}, seed++, "start for arm", stand_ins);
    r = pair(*m, C("sub_50ECA8"), {id, 90000, 0x50F030u, 0x1234}, seed++, "arm", stand_ins);
    CHECK(v0_of(r) == 0);
    CHECK((r32(*m, rec + al::kFlags) & 3u) == 3u);
    CHECK(r64(*m, rec + al::kU64C) == 90000);
    CHECK(r32(*m, rec + 40) == 0x50F030u);
    CHECK(r32(*m, rec + 48) == 0x1234u);
    CHECK(r32(*m, al::kPending) == rec);
    CHECK(last_log().calls_to(kSetCompare) == 1);
    // a second armed counter goes into the list by key; stop takes the first off, disarm clears the bit
    const u32 id2 = use_record(*m, 5, 0x77, 1);
    w64(*m, kRecs + 320 + al::kU64A, 0);
    w64(*m, kRecs + 320 + al::kU64B, 0);
    pair(*m, C("sub_50ECA8"), {id2, 10, 0x50F030u, 0}, seed++, "arm second", stand_ins);
    CHECK(r32(*m, al::kPending) == kRecs + 320);  // the smaller key first
    CHECK(r32(*m, kRecs + 320 + al::kNext) == rec);
    pair(*m, C("sub_50E950"), {id}, seed++, "stop armed", stand_ins);
    CHECK(r32(*m, kRecs + 320 + al::kNext) == 0);
    r = pair(*m, C("sub_50ECA8"), {id2, 0, 0, 0}, seed++, "disarm", stand_ins);
    CHECK((r32(*m, kRecs + 320 + al::kFlags) & 2u) == 0u);
    CHECK(r32(*m, al::kPending) == 0);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_kernel): iSetTimerAlarm / iReleaseTimerAlarm on the user-alarm list") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 100;
    fresh_pool(*m);
    // the user-alarm free list: three 16-byte records
    const u32 u = 0x01836000u;
    for (u32 i = 0; i < 3; ++i) {
        wzero(*m, u + 16 * i, 16);
        w32(*m, u + 16 * i, i < 2 ? u + 16 * (i + 1) : 0);
    }
    w32(*m, al::kUserFree, u);
    CHECK(v0_of(pair(*m, C("iSetTimerAlarm"), {1000, 0, 0}, seed++, "iSetTimerAlarm no handler", stand_ins)) == sx(0x80000016u));
    std::vector<u32> ids;
    for (u32 i = 0; i < 3; ++i) {
        const auto r = pair(*m, C("iSetTimerAlarm"), {sx(1000 * (i + 1)), 0x123450u, 0x40 + i}, seed++, "iSetTimerAlarm " + std::to_string(i), stand_ins);
        const u32 id = static_cast<u32>(v0_of(r));
        CHECK((id & 1u) == 1u);
        CHECK((id >> 8 << 4) == u + 16 * i);           // the user record
        CHECK(r32(*m, u + 16 * i + 8) == 0x123450u);   // handler, argument
        CHECK(r32(*m, u + 16 * i + 12) == 0x40 + i);
        const u32 cid = r32(*m, u + 16 * i + 4);       // its counter: armed with AlarmHandler and running
        const u32 crec = cid >> 10 << 6;
        CHECK(r32(*m, crec + 40) == 0x50F030u);
        CHECK((r32(*m, crec + al::kFlags) & 3u) == 3u);
        CHECK((id & 0xFFu) == (((cid & 0xFFu) & 0xFEu) | 1u));
        ids.push_back(id);
    }
    // no free user record left
    CHECK(v0_of(pair(*m, C("iSetTimerAlarm"), {1, 0x123450u, 0}, seed++, "iSetTimerAlarm empty", stand_ins)) == sx(0x80008005u));
    // release: the counter freed (sce1's sub_50E690), the record back at the head of the free list
    for (u32 id : ids) {
        const auto r = pair(*m, C("iReleaseTimerAlarm"), {id}, seed++, "iReleaseTimerAlarm", stand_ins);
        CHECK(v0_of(r) == 0);
        CHECK(r32(*m, al::kUserFree) == (id >> 8 << 4));
    }
    CHECK(v0_of(pair(*m, C("iReleaseTimerAlarm"), {sx(0x80000001u)}, seed++, "iReleaseTimerAlarm bad", stand_ins)) == sx(0x80008002u));
    CHECK(v0_of(pair(*m, C("iReleaseTimerAlarm"), {ids[0] ^ 0x10}, seed++, "iReleaseTimerAlarm wrong tag", stand_ins)) == sx(0x80008002u));
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_kernel): sceSpu2Mem -- init, free sequences, quit") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 1000;
    for (u32 flag : {0u, 1u}) {
        const u32 entries = 24;
        auto r = pair(*m, C("sceSpu2MemInit"), {kSpuTable, entries, flag}, seed++, "Init", stand_ins);
        CHECK(v0_of(r) == 0);
        CHECK(r32(*m, ls::kTable) == kSpuTable);
        CHECK(r32(*m, kSpuTable) == (0x80000000u | ls::kReserved));  // one free block from the reserved end
        const u32 end = flag ? 0x200000u : 0x1C0000u;
        CHECK(r32(*m, kSpuTable + 4) == end - 0x5010u);  // its size: to the end of SPU2 RAM
        CHECK(v0s(pair(*m, C("sceSpu2MemInit"), {0, entries, flag}, seed++, "Init null", stand_ins)) == -1);
        pair(*m, C("sceSpu2MemInit"), {kSpuTable, entries, flag}, seed++, "Init again", stand_ins);
        // sceSpu2MemAllocate stays recompiled (test_field8_sys stands it in), so the tables are built here: a run of
        // allocated blocks from 0x5010 (entries 0..k-1, linked through +8), then the free tail to the end of SPU2
        // RAM, with the top (0x782B38) at the tail and its remaining size (0x782B3C) as Init leaves them.
        std::mt19937 rng{flag + 9};
        for (int round = 0; round < 6; ++round) {
            pair(*m, C("sceSpu2MemInit"), {kSpuTable, entries, flag}, seed++, "Init (round)", stand_ins);
            const u32 k = 1 + rng() % (entries - 1);
            std::vector<u32> live;
            u32 at = ls::kReserved;
            for (u32 i = 0; i < k; ++i) {
                const u32 sz = 16 * (1 + rng() % 0x400);
                w32(*m, kSpuTable + 12 * i, at);
                w32(*m, kSpuTable + 12 * i + 4, sz);
                w32(*m, kSpuTable + 12 * i + 8, kSpuTable + 12 * (i + 1));
                live.push_back(at);
                at += sz;
            }
            w32(*m, kSpuTable + 12 * k, 0x80000000u | at);
            w32(*m, kSpuTable + 12 * k + 4, end - at);
            w32(*m, kSpuTable + 12 * k + 8, 0);
            w32(*m, ls::kTop, at);
            w32(*m, ls::kTop + 4, end - at);
            std::shuffle(live.begin(), live.end(), rng);
            for (u32 a : live) {
                pair(*m, C("sceSpu2MemFree"), {a}, seed++, "Free", stand_ins);
                // the list still covers 0x5010 .. end without gaps, and no two neighbours are both free
                u32 e = kSpuTable, next_at = ls::kReserved, steps = 0;
                bool prev_free = false;
                for (; e != 0 && steps <= entries; e = r32(*m, e + 8), ++steps) {
                    const u32 w0 = r32(*m, e);
                    const bool is_free = (w0 & 0x80000000u) != 0;
                    CHECK((w0 & 0x7FFFFFFFu) == next_at);
                    CHECK(!(is_free && prev_free));
                    next_at = (w0 & 0x7FFFFFFFu) + r32(*m, e + 4);
                    prev_free = is_free;
                }
                CHECK(e == 0);
                CHECK(next_at == end);
            }
            // everything freed: one free block at the reserved end again
            CHECK(r32(*m, kSpuTable) == (0x80000000u | ls::kReserved));
            CHECK(r32(*m, kSpuTable + 8) == 0);
            CHECK(r32(*m, ls::kTop) == static_cast<u32>(ls::kReserved));
        }
        pair(*m, C("sceSpu2MemFree"), {0}, seed++, "Free 0", stand_ins);
        pair(*m, C("sceSpu2MemQuit"), {}, seed++, "Quit", stand_ins);
        for (u32 i = 0; i < 12 * (entries + 1); i += 4) CHECK(r32(*m, kSpuTable + i) == 0);
    }
    // the dorm snapshot's live table (H_Sndcom_Init's): free its allocated blocks one by one
    const std::vector<u8> snap = read_snapshot("dorm_replay_4900");
    if (!snap.empty()) {
        copy_from_snapshot(*m, snap, 0x782B18u, 0x40);
        const u32 table = r32(*m, ls::kTable);
        const u32 n = r32(*m, 0x782B24u);
        if (table && n && n < 4096) {
            copy_from_snapshot(*m, snap, table, 12 * n);
            std::vector<u32> used;
            for (u32 e = table, steps = 0; e != 0 && steps < n; e = r32(*m, e + 8), ++steps)
                if (!(r32(*m, e) & 0x80000000u)) used.push_back(r32(*m, e));
            for (u32 a : used) pair(*m, C("sceSpu2MemFree"), {a}, seed++, "Free (dorm)", stand_ins);
            MESSAGE("dorm SPU2 table at " << std::hex << table << std::dec << ", " << n << " entries; " << used.size()
                                          << " blocks freed");
        }
    }
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

#else

TEST_CASE("game(libs1_kernel): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
