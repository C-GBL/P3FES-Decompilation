// Pair tests of the fx_layers functions taken with the stand-ins (game/src/fx/fx_layers.cpp, the section "The
// functions wave 10 left out"): the after-effect pack unpacker, ring allocator, creator and destroyer, the effect
// manager's tagged-material records, image-sequence chunks and lists, sprite sets / players, image sequences, effect
// mesh objects, and the two set-up functions that load files (effMng_CreateEffectProgramTasks,
// effAfter_CreateAfterEffectRenderTask). Each body runs against its recompiled body on a fresh stand-in world
// (stand_ins.h: the guest heap behind the RW memory slots 0x960178.. and H_Malloc, printf / sprintf, the H_Cdvd file
// layer over extracted/). Every pair compares the whole of main RAM (write-tracked), the scratchpad, every GPR in 128
// bits, HI/LO, the register file and cycles at every check point, the dead stack, the stand-ins' call logs, the
// heaps' live blocks and the file layers' nodes; the host checks below restate the layouts fx_layers.h documents.
//
// Two machines: the ELF's own memory (with the retail RW slot pointers) for the functions that only use the heap and
// libc, and a replay snapshot (battle_ref_6150, dorm_replay_4900; skipped when absent) for the ones that create or
// destroy RenderWare objects (frames, atomics, materials, geometries, textures, matrices: their free lists are live
// there, and the free-list entry points are stood in) or create kwln tasks. A chain of pairs carries the recompiled
// run's heap into the next world (the blocks reserved), so a created object can be destroyed by the next pair.
// Callees the build does not emit get stand-ins here: the image loader uttmxCreateRaster (returns no raster), the
// texture-by-name loader sub_4D1260 (a zeroed 96-byte texture with one reference), and the effect-manager set-up
// steps sub_3580F0 / sub_351C20 (recorders; sub_34BD10 / sub_347D00 are hand-written in fx_types and run), and the
// PS2 driver's texture-cache destructor sub_4DD2E0 (returns its object: it would wait on DMA for a resident texture).
#include <doctest.h>

#include "stand_ins.h"

#include "p3fes/game/hcdvd.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

#define FXS_FNS(X)                                                                                                 \
    X(sub_1E9920_001e9920) X(sub_1E9A90_001e9a90) X(sub_1EE2E0_001ee2e0) X(sub_1EEB90_001eeb90)                     \
    X(sub_1EF340_001ef340) X(sub_320230_00320230) X(sub_320290_00320290) X(sub_320880_00320880)                     \
    X(sub_320FB0_00320fb0) X(sub_321010_00321010) X(effMng_CreateEffectProgramTasks_00322010) X(sub_322530_00322530) \
    X(sub_3225D0_003225d0) X(sub_322660_00322660) X(sub_322880_00322880) X(sub_322A20_00322a20)                     \
    X(sub_322DC0_00322dc0) X(sub_322F20_00322f20) X(sub_3230F0_003230f0) X(sub_3234F0_003234f0)                     \
    X(sub_3237C0_003237c0) X(sub_323C20_00323c20) X(effAfter_CreateAfterEffectRenderTask_001eef20)

namespace p3fes::recomp_gen {
#define FXS_DECL(n) void fn_##n(p3fes::EEContext&); void fn_##n##__recomp(p3fes::EEContext&);
FXS_FNS(FXS_DECL)
#undef FXS_DECL
}  // namespace p3fes::recomp_gen

namespace p3fes::game_test {
namespace {

namespace rg = p3fes::recomp_gen;
#define FXS(n) rg::fn_##n, rg::fn_##n##__recomp

// --- machines, checks, guest helpers ---------------------------------------------------------------------------------
HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void putf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
u32 get32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 get16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void fill(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
void zero(Machine& m, u32 va, u32 len) { std::memset(m.at(va), 0, len); }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 round16(u32 n) { return n == 0 ? 16u : (n + 15u) & ~15u; }
u32 v0_of(const SiPair& p) { return static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]); }
std::string guest_str(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va)), strnlen(reinterpret_cast<const char*>(m.at(va)), 256)); }

constexpr u32 kRwMalloc = 0x104140u, kRwFree = 0x104280u, kFreeListAlloc = 0x4C3D10u, kFreeListFree = 0x4C3EE0u;
constexpr u32 kHint = 0x40000u;                       // the RW memory hint every allocation here passes
constexpr u32 kData = 0x01BC0000u;                    // test data: free in the ELF's memory and in every snapshot
constexpr u32 kRasterLoader = 0x10E880u;              // uttmxCreateRaster (not emitted in this build)
constexpr u32 kTextureByName = 0x4D1260u;             // sub_4D1260(name, mask) -> texture (not emitted)
constexpr u32 kZ0Texture = 0x7CE2D4u;                 // the after effects' texture (effAfter_CreateAfterEffectRenderTask)
constexpr u32 kAeHead = 0x7CE2CCu, kAeTail = 0x7CE2C8u, kAeTask = 0x7CE2D0u;  // the live list, the render task
constexpr u32 kTexTable = 0x957A20u;                  // effMng's 22 effpack textures
constexpr u32 kTexCacheDtor = 0x4DD2E0u;              // the driver's texture-cache destructor (not emitted)

Machine* plain_machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        write_rw_slots(*mm);
        return mm;
    }();
    return m;
}

#define NEED_PLAIN()                                    \
    Machine* mp = plain_machine();                      \
    if (!mp) {                                          \
        MESSAGE("SKIP: no ELF at " << elf_path());      \
        return;                                         \
    }                                                   \
    Machine& m = *mp

// A machine holding a replay snapshot (its RW engine, free lists, kwln task system and textures live).
std::unique_ptr<Machine> snapshot_machine(const char* dir) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    const std::vector<u8> snap = read_snapshot(dir);
    if (snap.empty()) return nullptr;
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    return m;
}

const char* const kSnapshots[] = {"battle_ref_6150", "dorm_replay_4900"};

// The heap of a world: blocks reserved before the body runs (the same in both worlds), then the standard stand-ins
// and the extra ones of the test.
using Blocks = std::vector<std::pair<u32, u32>>;
using Extra = std::function<void(StandInWorld&)>;
WorldSetup world(Blocks blocks, Extra extra = {}) {
    return [blocks = std::move(blocks), extra = std::move(extra)](StandInWorld& w) {
        install_standard(w);
        for (const auto& [p, s] : blocks) w.heap.reserve(p, s);
        if (extra) extra(w);
    };
}
Blocks live_of(const SiPair& p) { return Blocks(p.recomp->heap.live().begin(), p.recomp->heap.live().end()); }
// Allocation addresses a world will hand out after `blocks` (first fit, as GuestHeap does).
struct Planner {
    GuestHeap heap;
    Blocks blocks;
    u32 take(u32 size) {
        const u32 p = heap.alloc(size);
        blocks.emplace_back(p, round16(size));
        return p;
    }
};

// The stand-ins for the callees the build leaves out (see the file comment).
Extra loaders(Machine& m) {
    return [&m](StandInWorld& w) {
        w.si.install_recorder(kRasterLoader, "uttmxCreateRaster", 0);
        w.si.install(kTextureByName, "sub_4D1260 (texture by name)", [&m, &w](EEContext&, StandIns&, StandInCall& c) {
            c.text = guest_str(m, static_cast<u32>(c.args[0]));
            const u32 t = w.heap.alloc(96);
            zero(m, t, 96);
            put32(m, t + 84, 1);  // one reference
            c.v0 = t;
            c.extra = 96;
        });
        w.si.install_recorder(0x3580F0u, "sub_3580F0");
        w.si.install_recorder(0x351C20u, "sub_351C20");
        // the PS2 driver's texture-cache destructor (a texture plugin, reached from sub_4D0F00): it waits on the DMA
        // buffers while the texture is resident, so it stays out of the build; a destructor returns its object
        w.si.install(kTexCacheDtor, "sub_4DD2E0 (texture cache destructor)",
                     [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
    };
}

std::size_t calls(const SiPair& p, u32 va) { return p.recomp->si.calls_to(va); }

// run_pair_si, and when a body raises a fatal event (a fault, a callee not emitted): where, before it propagates.
SiPair pair_si(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw,
               const WorldSetup& setup) {
    try {
        return run_pair_si(m, hand, recomp, args, seed, what, hw, setup);
    } catch (const rt_test::FatalEvent& e) {
        MESSAGE(std::string(what) << ": fatal event at pc " << hex64(e.pc) << ", $ra " << hex64(e.ctx->gpr[31].u64[0]));
        throw;
    }
}

// =====================================================================================================================
// Effect manager: tagged-material records and reference counts (the ELF's memory)
// =====================================================================================================================
TEST_CASE("game(fx_layers): sub_320FB0 / sub_320230 / sub_321010 -- records and reference counts on the guest heap") {
    NEED_PLAIN();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF1A0001};
    int pairs = 0;
    // sub_320FB0(n): a record {+0 -> the n entries at +12, +4 u16 0, +6 u16 n, +8 u16 references = 1}; n is a u16.
    const u32 sizes[] = {0, 1, 2, 5, 31, 127, 300, 0xFFFF};
    for (int i = 0; i < 80; ++i) {
        const u32 n = i < 8 ? sizes[i] : chance(rng, 80) ? rng() % 40 : rng() & 0xFFFFu;
        const u32 a0 = chance(rng, 30) ? (rng() & 0xFFFF0000u) | n : n;  // the high half is masked off
        Planner pl;
        for (u32 k = rng() % 3; k > 0; --k) pl.take(16 + rng() % 64);
        const u32 want = pl.heap.alloc(4 * n + 12);
        const SiPair p = pair_si(m, FXS(sub_320FB0_00320fb0), {sx(a0), rng(), rng(), rng()}, rng(), "sub_320FB0", hw,
                                     world(pl.blocks));
        ++pairs;
        const StandIns& si = p.recomp->si;
        REQUIRE(si.log.size() == 1);
        CHECK(si.log[0].va == kRwMalloc);
        CHECK(static_cast<u32>(si.log[0].args[0]) == 4 * n + 12);
        CHECK(static_cast<u32>(si.log[0].args[1]) == kHint);
        const u32 rec = v0_of(p);
        CHECK(rec == want);
        CHECK(get32(m, rec) == rec + 12);
        CHECK(get16(m, rec + 4) == 0);
        CHECK(get16(m, rec + 6) == n);
        CHECK(get16(m, rec + 8) == 1);
    }
    // sub_320230(): a zeroed 4-byte list head.
    for (int i = 0; i < 30; ++i) {
        Planner pl;
        for (u32 k = rng() % 3; k > 0; --k) pl.take(16 + rng() % 64);
        const u32 want = pl.heap.alloc(4);
        put32(m, want, rng());
        const SiPair p = pair_si(m, FXS(sub_320230_00320230), {rng(), rng(), rng(), rng()}, rng(), "sub_320230", hw,
                                     world(pl.blocks));
        ++pairs;
        REQUIRE(p.recomp->si.log.size() == 1);
        CHECK(p.recomp->si.log[0].extra == 4);
        CHECK(v0_of(p) == want);
        CHECK(get32(m, want) == 0);
    }
    // sub_321010(record): one reference less (+8, u16); the last one frees the record.
    for (int i = 0; i < 60; ++i) {
        Planner pl;
        const u32 n = rng() % 6;
        const u32 rec = pl.take(4 * n + 12);
        const u16 refs = static_cast<u16>(i % 4 == 3 ? 0 : 1 + rng() % 3);  // 0: wraps to 0xFFFF, nothing freed
        put32(m, rec, rec + 12);
        put16(m, rec + 4, 0);
        put16(m, rec + 6, static_cast<u16>(n));
        put16(m, rec + 8, refs);
        const SiPair p = pair_si(m, FXS(sub_321010_00321010), {sx(rec), rng(), rng(), rng()}, rng(), "sub_321010", hw,
                                     world(pl.blocks));
        ++pairs;
        if (refs == 1) {
            REQUIRE(p.recomp->si.log.size() == 1);
            CHECK(p.recomp->si.log[0].va == kRwFree);
            CHECK(static_cast<u32>(p.recomp->si.log[0].args[0]) == rec);
            CHECK(p.recomp->heap.live().empty());
        } else {
            CHECK(p.recomp->si.log.empty());
            CHECK(get16(m, rec + 8) == static_cast<u16>(refs - 1));
        }
    }
    MESSAGE("records: " << pairs << " pairs");
}

// =====================================================================================================================
// Effect manager: image-sequence lists (sub_320290) and chunks (sub_320880)
// =====================================================================================================================
TEST_CASE("game(fx_layers): sub_320290 -- freeing an image-sequence list") {
    NEED_PLAIN();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF1A0002};
    int pairs = 0, records_kept = 0;
    for (int i = 0; i < 120; ++i) {
        Planner pl;
        const u32 head = pl.take(4);
        const u32 nrec = 1 + rng() % 2;
        std::vector<u32> recs, refs(nrec, 0), keep(nrec, 0);
        for (u32 r = 0; r < nrec; ++r) recs.push_back(pl.take(12 + 4 * (rng() % 3)));
        const u32 nodes = rng() % 5;
        std::vector<u32> node(nodes), data;
        for (u32 k = 0; k < nodes; ++k) {
            node[k] = pl.take(88);
            fill(m, node[k], 88, rng);
            for (u32 j = 0; j < 4; ++j) {
                u32 d = 0;
                if (chance(rng, 50)) {
                    d = pl.take(16 + rng() % 64);
                    data.push_back(d);
                }
                put32(m, node[k] + 16 * j + 12, d);
            }
            const u32 r = rng() % nrec;
            put32(m, node[k] + 80, recs[r]);
            ++refs[r];
        }
        for (u32 k = 0; k < nodes; ++k) put32(m, node[k] + 84, k + 1 < nodes ? node[k + 1] : 0u);
        put32(m, head, nodes ? node[0] : 0u);
        for (u32 r = 0; r < nrec; ++r) {
            keep[r] = rng() % 2;  // a reference held elsewhere
            put32(m, recs[r], recs[r] + 12);
            put16(m, recs[r] + 8, static_cast<u16>(refs[r] + keep[r]));
        }
        const SiPair p = pair_si(m, FXS(sub_320290_00320290), {sx(head), rng(), rng(), rng()}, rng(), "sub_320290", hw,
                                     world(pl.blocks));
        ++pairs;
        // every node, its image data and the head are freed; a record goes with its last reference
        std::set<u32> want;
        for (u32 r = 0; r < nrec; ++r) {
            if (keep[r] != 0 || refs[r] == 0) want.insert(recs[r]);
            CHECK(get16(m, recs[r] + 8) == keep[r]);
        }
        std::set<u32> live;
        for (const auto& [b, s] : p.recomp->heap.live()) live.insert(b);
        CHECK(live == want);
        CHECK(p.recomp->heap.bad_frees == 0);
        CHECK(calls(p, kRwFree) == nodes + data.size() + 1 + (nrec - want.size()));
        records_kept += static_cast<int>(want.size());
    }
    MESSAGE("sub_320290: " << pairs << " pairs, " << records_kept << " records kept alive");
}

// A clump with one atomic whose geometry has `mats` materials carrying user-data arrays (fx_layers.h: the tagged
// materials; the plugin offset gp-17680, the array name gp-25296). `want` is the string the stream asks for.
struct Clump {
    u32 clump, atomic, geometry, mats, strs, arrays;
};
Clump make_clump(Machine& m, std::mt19937& rng, u32 at, int mats, const std::string& want) {
    Clump c{at, at + 0x100, at + 0x200, at + 0x400, at + 0x800, at + 0x1000};
    zero(m, at, 0x3000);
    const std::string tag(reinterpret_cast<const char*>(m.at(kGp - 25296u)), strnlen(reinterpret_cast<const char*>(m.at(kGp - 25296u)), 32));
    put32(m, kGp - 17680u, 0x40u);
    std::memcpy(m.at(c.strs), want.c_str(), want.size() + 1);
    std::memcpy(m.at(c.strs + 0x200), "other", 6);
    std::memcpy(m.at(c.strs + 0x240), tag.c_str(), tag.size() + 1);
    put32(m, c.atomic + 24, c.geometry);
    put32(m, c.clump + 8, c.atomic + 64);  // the atomic list: links at atomic +64, back to the clump's +8
    put32(m, c.atomic + 64, c.clump + 8);
    put32(m, c.geometry + 32, c.geometry + 0x100);
    put32(m, c.geometry + 36, static_cast<u32>(mats));
    put32(m, c.geometry + 8, rng() & 0xBFu);
    for (int i = 0; i < mats; ++i) {
        const u32 mat = c.mats + 0x80u * static_cast<u32>(i);
        fill(m, mat, 0x40, rng);  // colour (+4..+7), surface properties (+12 / +16 / +20)
        put32(m, c.geometry + 0x100 + 4u * i, mat);
        const u32 arrays = c.arrays + 0x200u * static_cast<u32>(i);
        const u32 na = rng() % 3;
        put32(m, mat + 0x40, na);
        put32(m, mat + 0x44, arrays);
        for (u32 a = 0; a < na; ++a) {
            const u32 arr = arrays + 16u * a;
            put32(m, arr + 0, chance(rng, 75) ? c.strs + 0x240 : c.strs + 0x200);
            put32(m, arr + 4, chance(rng, 85) ? 3u : rng() % 4);
            const u32 ne = rng() % 3;
            put32(m, arr + 8, ne);
            put32(m, arr + 12, arrays + 0x100 + 16u * a);
            for (u32 e = 0; e < ne; ++e) put32(m, arrays + 0x100 + 16u * a + 4 * e, chance(rng, 60) ? c.strs : c.strs + 0x200);
        }
    }
    return c;
}

TEST_CASE("game(fx_layers): sub_320880 -- an image-sequence chunk from a memory stream") {
    NEED_PLAIN();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF1A0003};
    int pairs = 0, found = 0, skipped = 0, long_names = 0, short_streams = 0;
    for (int i = 0; i < 160; ++i) {
        // the stream data: {+0 width, +4 height, +8 depth, +12 name length, +16 -}, the name, width * depth bytes
        const bool long_name = chance(rng, 25);  // >= 0x80 characters: the name goes to a heap block
        std::string name;
        const u32 len = long_name ? 0x80 + rng() % 0x30 : 1 + rng() % 24;
        for (u32 k = 0; k < len; ++k) name.push_back(static_cast<char>('a' + rng() % 26));
        const u32 w = 1 + rng() % 16, h = 1 + rng() % 16, depth = 1 + rng() % 4;
        const Clump c = make_clump(m, rng, kData, static_cast<int>(rng() % 4), name);
        const u32 stream = kData + 0x3000, block = kData + 0x3100;
        const bool short_stream = chance(rng, 8);
        const u32 size = 20 + len + w * depth - (short_stream ? 1 + rng() % (w * depth) : 0u);
        fill(m, block, 0x400, rng);
        put32(m, block + 0, w);
        put32(m, block + 4, h);
        put32(m, block + 8, depth);
        put32(m, block + 12, len);
        std::memcpy(m.at(block + 20), name.data(), len);
        zero(m, stream, 0x20);
        put32(m, stream + 0, 3);  // a memory stream {type, access, -, position, size, memory}
        put32(m, stream + 4, 1);
        put32(m, stream + 16, size);
        put32(m, stream + 20, block);
        // the list: a node already there whose record (+80) may be the one this chunk builds (the first block after
        // the name's), so the chunk lands in it; its slot taken or free
        Planner pl;
        if (long_name) pl.heap.alloc(len + 1);
        const u32 rec = pl.heap.alloc(16);
        const u32 list = kData + 0x3800, n0 = kData + 0x3900, n1 = kData + 0x3A00;
        fill(m, n0, 88, rng);
        fill(m, n1, 88, rng);
        const bool hit = chance(rng, 40);
        put32(m, n0 + 80, rng());
        put32(m, n1 + 80, hit ? rec : rng());
        put32(m, n0 + 84, n1);
        put32(m, n1 + 84, 0);
        const u32 slot_index = rng() % 4;
        const bool taken = hit && chance(rng, 50);
        put32(m, n1 + 16 * slot_index + 12, taken ? 0x01BF0000u : 0u);
        put32(m, list, chance(rng, 85) ? n0 : 0u);
        if (get32(m, list) == 0 && hit) put32(m, list, n1);
        const u32 chunk = 0xF0F00080u + slot_index;  // the image chunks 0xF0F00080..83 -> slots +0 / +16 / +32 / +48
        // a record of no entries still reads entry 0 (the word after its header, in the next heap bytes): those bytes
        // start zero, as a fresh heap holds them (the earlier pairs' output would otherwise be read as a material)
        zero(m, kStandInHeap, 0x10000);
        INFO("round " << i << ": name length " << len << ", " << w << "x" << h << "x" << depth << ", hit " << hit << ", taken "
                      << taken << ", short " << short_stream << ", stream size " << size);
        const SiPair p = pair_si(m, FXS(sub_320880_00320880), {sx(stream), sx(list), sx(chunk), sx(c.clump)}, rng(),
                                 "sub_320880", hw, world({}));
        ++pairs;
        found += hit ? 1 : 0;
        skipped += taken ? 1 : 0;
        long_names += long_name ? 1 : 0;
        short_streams += short_stream ? 1 : 0;
        CHECK(v0_of(p) == 1);
        if (short_stream) continue;
        const u32 node = hit ? n1 : get32(m, list);
        if (!hit) CHECK(get32(m, node + 80) == rec);
        const u32 slot = node + 16 * slot_index;
        if (taken) {
            CHECK(get32(m, slot + 12) == 0x01BF0000u);  // left alone; the data skipped
            CHECK(get32(m, stream + 12) == 20 + len + w * depth);
        } else {
            CHECK(get32(m, slot + 0) == w);
            CHECK(get32(m, slot + 4) == h);
            CHECK(get32(m, slot + 8) == depth);
            const u32 data = get32(m, slot + 12);
            REQUIRE(data != 0);
            CHECK(std::memcmp(m.at(data), m.at(block + 20 + len), w * depth) == 0);
            CHECK(get32(m, stream + 12) == 20 + len + w * depth);
        }
    }
    MESSAGE("sub_320880: " << pairs << " pairs (" << found << " into an existing node, " << skipped << " skipping a taken slot, "
                           << long_names << " long names, " << short_streams << " short streams)");
}

// =====================================================================================================================
// After effects: unpacking a pack (sub_1EE2E0)
// =====================================================================================================================
struct Trail {
    u16 a, b, cap, n, shape;
    u32 size, data;
};
struct Pack {
    u32 va = 0, type = 0, word = 0, alloc = 0;
    u32 T = 0, A = 0, B = 0;
    std::vector<u16> aid, bid;
    std::vector<Trail> trails;
    bool valid = true;
};

// A raw pack (eff_afpack.c; layout in fx_layers.cpp above sub_1EE2E0): {+0 type 100 / 101, +4 word, +8 u16 trails,
// +10 u16 curves, +12 u16 colour sets}, then the 56-byte curves, the colour sets (8 bytes, 4 more, 16 colour bytes;
// the asserts at +4 / +6), the trails (24 bytes for type 100, 32 for 101) each followed by its data.
Pack make_pack(Machine& m, std::mt19937& rng, u32 va, bool valid, bool resolvable, u32 max_trails) {
    Pack pk;
    pk.va = va;
    pk.valid = valid;
    pk.type = chance(rng, 50) ? 101u : 100u;
    if (!valid && chance(rng, 50)) pk.type = chance(rng, 50) ? 102u : 0u;
    pk.word = rng();
    pk.T = rng() % (max_trails + 1);
    pk.A = (resolvable ? 1 : 0) + rng() % 4;
    pk.B = (resolvable ? 1 : 0) + rng() % 3;
    put32(m, va, pk.type);
    put32(m, va + 4, pk.word);
    put16(m, va + 8, static_cast<u16>(pk.T));
    put16(m, va + 10, static_cast<u16>(pk.A));
    put16(m, va + 12, static_cast<u16>(pk.B));
    put16(m, va + 14, static_cast<u16>(rng()));
    u32 p = va + 16;
    for (u32 k = 0; k < pk.A; ++k, p += 56) {
        fill(m, p, 56, rng);
        pk.aid.push_back(static_cast<u16>(10 + k));
        put16(m, p, pk.aid.back());
    }
    for (u32 k = 0; k < pk.B; ++k) {
        fill(m, p, 28, rng);
        pk.bid.push_back(static_cast<u16>(20 + k));
        put16(m, p, pk.bid.back());
        const bool bad4 = !valid && chance(rng, 20), bad6 = !valid && chance(rng, 20);
        put16(m, p + 4, bad4 ? static_cast<u16>(1 + rng() % 9) : 0);
        put16(m, p + 6, bad6 ? static_cast<u16>(1 + rng() % 9) : 0);
        p += 8;
        if (!bad4) p += 4;
        if (!bad6) p += 16;
    }
    pk.alloc = 36;
    for (u32 k = 0; k < pk.T; ++k) {
        Trail t{};
        const u32 rec = 101 == pk.type ? 32u : 24u;
        fill(m, p, rec, rng);
        // an id that names no curve / colour set resolves to the slot past the last one
        t.a = pk.A != 0 && (resolvable || chance(rng, 85)) ? pk.aid[rng() % pk.A] : 999;
        t.b = pk.B != 0 && (resolvable || chance(rng, 85)) ? pk.bid[rng() % pk.B] : 998;
        t.cap = static_cast<u16>(2 + rng() % 7);
        t.n = static_cast<u16>(1 + rng() % 5);
        t.shape = static_cast<u16>(rng() % (resolvable ? 3 : 4));
        t.size = 4 * (rng() % 13);  // word-sized: the next trail record stays aligned, as in the game's packs
        put16(m, p + 2, t.a);
        put16(m, p + 4, t.b);
        put16(m, p + 16, t.cap);
        put16(m, p + 18, t.n);
        if (pk.type == 101) {
            put16(m, p + 20, t.shape);
            putf(m, p + 24, static_cast<float>(rng() % 100) / 7.0f);
            put32(m, p + 28, t.size);
        } else if (pk.type == 100) {
            put32(m, p + 20, t.size);
        }
        if (pk.type == 100 || pk.type == 101) {
            p += rec;
            t.data = p;
            fill(m, p, t.size, rng);
            p += t.size;
        }
        pk.trails.push_back(t);
    }
    if (pk.type == 100 || pk.type == 101) {
        u32 sum = 0;
        for (const Trail& t : pk.trails) sum += t.size;
        pk.alloc = 24 * pk.T + 36 + 52 * pk.A + 24 * pk.B + 4 * pk.T + sum + 8 * pk.T;
    }
    return pk;
}

// The unpacked descriptor (fx_layers.h): {+0 word, +4 / +6 / +8 u16 counts, +12 the 24-byte trails, +16 the 52-byte
// curves, +20 the 24-byte colour sets, +24 the {word, word} pairs, +28 the data pointers}.
void check_unpacked(Machine& m, const Pack& pk, u32 r) {
    CHECK(get32(m, r) == pk.word);
    CHECK(get16(m, r + 4) == pk.T);
    CHECK(get16(m, r + 6) == pk.A);
    CHECK(get16(m, r + 8) == pk.B);
    CHECK(get32(m, r + 12) == r + 36);
    CHECK(get32(m, r + 16) == r + 36 + 24 * pk.T);
    CHECK(get32(m, r + 20) == r + 36 + 24 * pk.T + 52 * pk.A);
    CHECK(get32(m, r + 28) == r + 36 + 24 * pk.T + 52 * pk.A + 24 * pk.B);
    for (u32 k = 0; k < pk.T; ++k) {
        const Trail& t = pk.trails[k];
        const u32 e = r + 36 + 24 * k;
        const u32 ia = static_cast<u32>(std::find(pk.aid.begin(), pk.aid.end(), t.a) - pk.aid.begin());
        const u32 ib = static_cast<u32>(std::find(pk.bid.begin(), pk.bid.end(), t.b) - pk.bid.begin());
        CHECK(get32(m, e + 0) == get32(m, r + 16) + 52 * ia);
        CHECK(get32(m, e + 4) == get32(m, r + 20) + 24 * ib);
        CHECK(get32(m, e + 8) == t.cap);
        CHECK(get32(m, e + 12) == t.n);
        CHECK(get32(m, e + 16) == (pk.type == 101 ? t.shape : 0u));
        if (pk.type == 100) CHECK(get32(m, e + 20) == 0x41200000u);  // 10.0f
        const u32 d = get32(m, get32(m, r + 28) + 4 * k);
        CHECK(std::memcmp(m.at(d), m.at(t.data), t.size) == 0);
    }
}

TEST_CASE("game(fx_layers): sub_1EE2E0 -- unpacking after-effect packs") {
    NEED_PLAIN();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF1A0004};
    int pairs = 0, invalid = 0;
    for (int i = 0; i < 150; ++i) {
        const bool valid = !chance(rng, 12);
        put32(m, kZ0Texture, chance(rng, 50) ? 0x01BE0000u : 0u);
        const Pack pk = make_pack(m, rng, kData, valid, false, 6);
        const SiPair p = pair_si(m, FXS(sub_1EE2E0_001ee2e0), {sx(kData), rng(), rng(), rng()}, rng(), "sub_1EE2E0", hw,
                                     world({}));
        ++pairs;
        invalid += valid ? 0 : 1;
        REQUIRE(calls(p, kRwMalloc) == 1);
        if (!valid) continue;
        CHECK(p.recomp->si.log[0].extra == pk.alloc);
        check_unpacked(m, pk, v0_of(p));
    }
    MESSAGE("sub_1EE2E0: " << pairs << " pairs (" << invalid << " with a bad type or colour set: the asserts)");
}

// =====================================================================================================================
// Effect manager: sprite sets / players and image sequences without images (the ELF's memory)
// =====================================================================================================================
// A sprite file (effpack): {+0 header size S, +4 animation count F, +8 the 20-byte animations {+0 key offset, +4, +8
// flags, +12 count, +16 flags}, the 24-byte keys}, then at +S {image count, image offsets}.
// sub_322880 allocates S + 28 + 4 * images bytes but puts the texture pointers at +36 + S: the last 8 bytes past the
// block. The header is padded so that they land in the 16-byte rounding of the block (as the game's allocator rounds
// too) instead of in the next block, the first texture, which the pair's own destroy step would then trip over.
u32 make_sprite_file(Machine& m, std::mt19937& rng, u32 va, u32 images, u32 image_area) {
    const u32 F = 1 + rng() % 6, K = 24;
    u32 S = 8 + 20 * F + 24 * K;
    while ((S + 28 + 4 * images) % 16 == 0 || (S + 28 + 4 * images) % 16 > 8) S += 4;
    fill(m, va, S, rng);
    put32(m, va + 0, S);
    put32(m, va + 4, F);
    for (u32 a = 0; a < F; ++a) {
        const u32 rec = va + 8 + 20 * a;
        const u32 k0 = rng() % 12;
        put32(m, rec + 0, 8 + 20 * F + 24 * k0);
        put32(m, rec + 4, 4u * (rng() % 8));
        put32(m, rec + 8, chance(rng, 30) && F > 1 ? 0xC0u : rng() & 0x3Fu);
        put32(m, rec + 12, 1 + rng() % 4);
        u32 fl = rng() & 0x17u;
        if (chance(rng, 25)) fl |= 0x10000000u;
        put32(m, rec + 16, fl);
    }
    for (u32 k = 0; k < K; ++k) {
        const u32 key = va + 8 + 20 * F + 24 * k;
        put16(m, key + 0, static_cast<u16>(rng() % F));
        put16(m, key + 2, static_cast<u16>(rng() % 5));
        put16(m, key + 16, static_cast<u16>(rng() % (images ? images : 1)));
        put16(m, key + 18, static_cast<u16>(rng() % 6));
    }
    put32(m, va + S, images);
    for (u32 k = 0; k < images; ++k) put32(m, va + S + 4 + 4 * k, image_area - va + 0x40 * k);
    return S;
}

// The mode a set gets (sub_322880): the last animation with flag 0x10000000 gives its count, else flags 0xC0 give 2.
u32 sprite_mode(Machine& m, u32 file) {
    u32 mode = 1;
    const u32 F = get32(m, file + 4);
    for (u32 a = 0; a < F; ++a) {
        const u32 rec = file + 8 + 20 * a;
        if (get32(m, rec + 16) & 0x10000000u) mode = get32(m, rec + 12);
        else if (get32(m, rec + 8) & 0xC0u) mode = 2;
    }
    return mode;
}

TEST_CASE("game(fx_layers): sprite sets and players sub_322880 / 322530 / 3225D0 / 322660 / 322A20, image sequences "
          "sub_322DC0 / 322F20 (no images)") {
    NEED_PLAIN();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF1A0005};
    int pairs = 0;
    for (int i = 0; i < 40; ++i) {
        const u32 file = kData;
        const u32 S = make_sprite_file(m, rng, file, 0, kData + 0x2000);
        const u32 mode = sprite_mode(m, file);
        // a set alone, released again
        SiPair p = pair_si(m, FXS(sub_322880_00322880), {sx(file), rng(), rng(), rng()}, rng(), "sub_322880", hw, world({}));
        ++pairs;
        u32 set = v0_of(p);
        CHECK(p.recomp->si.log[0].extra == S + 28);
        CHECK(get32(m, set + 0) == set + 28);
        CHECK(get32(m, set + 4) == set + 36);
        CHECK(get32(m, set + 8) == mode);
        CHECK(get32(m, set + 12) == 0);
        CHECK(get32(m, set + 16) == 1);
        CHECK(get32(m, set + 24) == set);
        CHECK(std::memcmp(m.at(set + 28), m.at(file), S) == 0);
        p = pair_si(m, FXS(sub_322A20_00322a20), {sx(set), rng(), rng(), rng()}, rng(), "sub_322A20", hw, world(live_of(p)));
        ++pairs;
        CHECK(p.recomp->heap.live().empty());
        // a player on a new set, a clone sharing it, both released (the set with the last one)
        p = pair_si(m, FXS(sub_322530_00322530), {sx(file), rng(), rng(), rng()}, rng(), "sub_322530", hw, world({}));
        ++pairs;
        const u32 player = v0_of(p);
        set = get32(m, player);
        CHECK(get32(m, player + 16) == player + 24);
        CHECK(get16(m, player + 20) == 1);
        CHECK(p.recomp->heap.size_of(player) == round16(20 * mode + 24));
        p = pair_si(m, FXS(sub_3225D0_003225d0), {sx(player), rng(), rng(), rng()}, rng(), "sub_3225D0", hw, world(live_of(p)));
        ++pairs;
        const u32 clone = v0_of(p);
        CHECK(get32(m, clone) == set);
        CHECK(get32(m, set + 16) == 2);
        p = pair_si(m, FXS(sub_322660_00322660), {sx(clone), rng(), rng(), rng()}, rng(), "sub_322660", hw, world(live_of(p)));
        ++pairs;
        CHECK(get32(m, set + 16) == 1);
        CHECK(p.recomp->heap.live().size() == 2);
        p = pair_si(m, FXS(sub_322660_00322660), {sx(player), rng(), rng(), rng()}, rng(), "sub_322660 (last)", hw, world(live_of(p)));
        ++pairs;
        CHECK(p.recomp->heap.live().empty());
        // an image sequence without images: {+0..+16 the header copy, +16 the image records, +20 the textures, +24
        // the frame total, +28 references, +32 -1, +36 itself}
        const u32 seq = kData + 0x3000;
        fill(m, seq, 16, rng);
        put32(m, seq + 4, 0);
        p = pair_si(m, FXS(sub_322DC0_00322dc0), {sx(seq), rng(), rng(), rng()}, rng(), "sub_322DC0", hw, world({}));
        ++pairs;
        const u32 s = v0_of(p);
        CHECK(std::memcmp(m.at(s), m.at(seq), 16) == 0);
        CHECK(get32(m, s + 16) == s + 40);
        CHECK(get32(m, s + 24) == 0);
        CHECK(get32(m, s + 28) == 1);
        CHECK(get32(m, s + 32) == 0xFFFFFFFFu);
        CHECK(get32(m, s + 36) == s);
        const u32 refs = 1 + rng() % 2;
        put32(m, s + 28, refs);
        p = pair_si(m, FXS(sub_322F20_00322f20), {sx(s), rng(), rng(), rng()}, rng(), "sub_322F20", hw, world(live_of(p)));
        ++pairs;
        CHECK(p.recomp->heap.live().size() == (refs == 1 ? 0u : 1u));
    }
    MESSAGE("sprite sets / players / sequences: " << pairs << " pairs");
}

// =====================================================================================================================
// On a replay snapshot: textures, rings, effect meshes, the after effects, the set-up functions
// =====================================================================================================================
TEST_CASE("game(fx_layers): sprite sets and image sequences with images (textures through the stood-in image loader)") {
    const HwCheck hw = full_check();
    int pairs = 0;
    for (const char* dir : kSnapshots) {
        auto mp = snapshot_machine(dir);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << dir);
            continue;
        }
        Machine& m = *mp;
        std::mt19937 rng{0xF1A0006};
        for (int i = 0; i < 6; ++i) {
            const u32 file = kData, images = 1 + rng() % 3;
            const u32 S = make_sprite_file(m, rng, file, images, kData + 0x2000);
            SiPair p = pair_si(m, FXS(sub_322880_00322880), {sx(file), rng(), rng(), rng()}, rng(), "sub_322880 (images)", hw,
                                   world({}, loaders(m)));
            ++pairs;
            const u32 set = v0_of(p);
            REQUIRE(calls(p, kRasterLoader) == images);
            u32 k = 0;
            for (const StandInCall& c : p.recomp->si.log)
                if (c.va == kRasterLoader) CHECK(static_cast<u32>(c.args[0]) == kData + 0x2000 + 0x40 * k++);
            CHECK(get32(m, set + 12) == images);
            const u32 tex = get32(m, set + 20);
            CHECK(tex == set + 36 + S);
            for (u32 t = 0; t < images; ++t) {
                const u32 texture = get32(m, tex + 4 * t);
                REQUIRE(texture != 0);
                CHECK((get32(m, texture + 80) & 0xFFFFu) == 0x1102u);  // sub_3210C0's filter / addressing
            }
            p = pair_si(m, FXS(sub_322A20_00322a20), {sx(set), rng(), rng(), rng()}, rng(), "sub_322A20 (images)", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(p.recomp->heap.live().empty());
            // an image sequence of `images` records {+0 frames, +4 the image's size, ...} and the images after them
            const u32 seq = kData + 0x3000;
            fill(m, seq, 0x400, rng);
            put32(m, seq + 4, images);
            u32 frames = 0;
            for (u32 j = 0; j < images; ++j) {
                put32(m, seq + 16 + 16 * j + 0, rng() % 8);
                put32(m, seq + 16 + 16 * j + 4, 0x20 + 0x10 * (rng() % 4));
                frames += 1 + get32(m, seq + 16 + 16 * j);
            }
            p = pair_si(m, FXS(sub_322DC0_00322dc0), {sx(seq), rng(), rng(), rng()}, rng(), "sub_322DC0 (images)", hw,
                            world({}, loaders(m)));
            ++pairs;
            const u32 s = v0_of(p);
            CHECK(get32(m, s + 24) == frames);
            u32 at = seq + 16 + 16 * images;
            k = 0;
            for (const StandInCall& c : p.recomp->si.log) {
                if (c.va != kRasterLoader) continue;
                CHECK(static_cast<u32>(c.args[0]) == at);
                at += get32(m, seq + 16 + 16 * k++ + 4);
            }
            CHECK(k == images);
            p = pair_si(m, FXS(sub_322F20_00322f20), {sx(s), rng(), rng(), rng()}, rng(), "sub_322F20 (images)", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(p.recomp->heap.live().empty());
        }
    }
    MESSAGE("textured sets / sequences: " << pairs << " pairs");
}

TEST_CASE("game(fx_layers): effect mesh objects sub_3230F0 / sub_323C20 / sub_3234F0 and sub_3237C0 destroying them") {
    const HwCheck hw = full_check();
    int pairs = 0;
    for (const char* dir : kSnapshots) {
        auto mp = snapshot_machine(dir);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << dir);
            continue;
        }
        Machine& m = *mp;
        std::mt19937 rng{0xF1A0007};
        const u32 flag_set[] = {0u, 1u, 0x8u, 0x1Cu, 0x7Fu};
        for (int i = 0; i < 10; ++i) {
            const u32 verts = 3 + rng() % 30, tris = 1 + rng() % 20, flags = flag_set[rng() % 5];
            // a mesh {+0 u16 5, +4 flags, +8 / +10 u16 counts, +12 frame, +16 atomic, +20 material, +24 0}
            SiPair p = pair_si(m, FXS(sub_3230F0_003230f0), {sx(verts), sx(tris), sx(flags), rng()}, rng(), "sub_3230F0", hw,
                                   world({}, loaders(m)));
            ++pairs;
            u32 obj = v0_of(p);
            CHECK(get16(m, obj) == 5);
            CHECK(get32(m, obj + 4) == flags);
            CHECK(get16(m, obj + 8) == verts);
            CHECK(get16(m, obj + 10) == tris);
            CHECK(get32(m, obj + 12) != 0);
            CHECK(get32(m, obj + 16) != 0);
            CHECK(get32(m, obj + 20) != 0);
            CHECK(get32(m, obj + 24) == 0);
            p = pair_si(m, FXS(sub_3237C0_003237c0), {sx(obj), rng(), rng(), rng()}, rng(), "sub_3237C0", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(p.recomp->heap.size_of(obj) == 0);
            // one material per band: {..., +28 u16 bands, +30 / +32 u16 counts, +34..+37 0xFF, +40 the materials}
            const u32 bands = 1 + rng() % 4, bverts = 4 + rng() % 16, btris = 2 + rng() % 12;
            p = pair_si(m, FXS(sub_323C20_00323c20), {sx(bands), sx(bverts), sx(btris), sx(flags)}, rng(), "sub_323C20", hw,
                            world({}, loaders(m)));
            ++pairs;
            obj = v0_of(p);
            CHECK(get16(m, obj) == 5);
            CHECK(get16(m, obj + 28) == bands);
            CHECK(get32(m, obj + 40) == obj + 44);
            CHECK(get32(m, obj + 34) == 0xFFFFFFFFu);
            for (u32 b = 0; b < bands; ++b) CHECK(get32(m, obj + 44 + 4 * b) != 0);
            p = pair_si(m, FXS(sub_3237C0_003237c0), {sx(obj), rng(), rng(), rng()}, rng(), "sub_3237C0 (bands)", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(p.recomp->heap.size_of(obj) == 0);
            // the flag-2 kind {+0 u16 3, +4 flags, +10 u16 count, +12 frame, +16 the object of sub_474210}
            const u32 count = 1 + rng() % 16, f2 = chance(rng, 50) ? 0x80000u : 0u;
            p = pair_si(m, FXS(sub_3234F0_003234f0), {sx(count), sx(f2 | (rng() & 1u)), rng(), rng()}, rng(), "sub_3234F0", hw,
                            world({}, loaders(m)));
            ++pairs;
            obj = v0_of(p);
            CHECK(get16(m, obj) == 3);
            CHECK(get16(m, obj + 10) == count);
            CHECK(get32(m, obj + 12) != 0);
            CHECK(get32(m, obj + 16) != 0);
            p = pair_si(m, FXS(sub_3237C0_003237c0), {sx(obj), rng(), rng(), rng()}, rng(), "sub_3237C0 (flag 2)", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(p.recomp->heap.size_of(obj) == 0);
        }
    }
    MESSAGE("effect mesh objects: " << pairs << " pairs");
}

TEST_CASE("game(fx_layers): after effects -- sub_1E9920 / 1E9A90 rings, sub_1EE2E0 -> sub_1EEB90 -> sub_1EF340") {
    const HwCheck hw = full_check();
    int pairs = 0, emptied = 0;
    for (const char* dir : kSnapshots) {
        auto mp = snapshot_machine(dir);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << dir);
            continue;
        }
        Machine& m = *mp;
        std::mt19937 rng{0xF1A0008};
        for (int i = 0; i < 6; ++i) {
            // a ring alone: {+0 the curve descriptor, +16..+36 / +48 the rails (12 bytes x capacity each), +40 / +44
            // the arc tables (sub_1E7CE0), +52 a matrix, +72 u16 shape}
            const u32 desc = kData + 0x100, ring = kData;
            fill(m, desc, 24, rng);
            const u32 cap = 2 + rng() % 7, n = 1 + rng() % 5;
            put32(m, desc + 8, cap);
            put32(m, desc + 12, n);
            put32(m, desc + 16, rng() % 3);
            fill(m, ring, 76, rng);
            SiPair p = pair_si(m, FXS(sub_1E9920_001e9920), {sx(ring), sx(desc), rng(), rng()}, rng(), "sub_1E9920", hw,
                                   world({}, loaders(m)));
            ++pairs;
            CHECK(get32(m, ring + 0) == desc);
            const u32 rails = get32(m, ring + 16);
            CHECK(p.recomp->si.log[0].extra == 72 * (cap + n));
            for (u32 r = 1; r < 5; ++r) CHECK(get32(m, ring + 16 + 4 * r) == rails + 12 * cap * r);
            CHECK(get32(m, ring + 48) == rails + 12 * cap * 6);
            CHECK(get32(m, ring + 4) == 0);
            CHECK(get32(m, ring + 8) == 0);
            CHECK(get32(m, ring + 12) == 0);
            CHECK(get32(m, get32(m, ring + 40) + 24) == cap - 1);
            CHECK(get32(m, get32(m, ring + 44) + 20) == 64);
            CHECK(get32(m, ring + 52) != 0);
            CHECK(get16(m, ring + 72) == static_cast<u16>(get32(m, desc + 16)));
            p = pair_si(m, FXS(sub_1E9A90_001e9a90), {sx(ring), rng(), rng(), rng()}, rng(), "sub_1E9A90", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(p.recomp->heap.live().empty());

            // a pack unpacked, an after effect created from it, linked first in the live list, destroyed by its model
            const u32 pack = kData + 0x1000, model = 0x01BF8000u;
            const Pack pk = make_pack(m, rng, pack, true, true, 3);
            p = pair_si(m, FXS(sub_1EE2E0_001ee2e0), {sx(pack), rng(), rng(), rng()}, rng(), "sub_1EE2E0 (snapshot)", hw,
                            world({}, loaders(m)));
            ++pairs;
            const u32 d = v0_of(p);
            check_unpacked(m, pk, d);
            put32(m, d + 32, model);
            p = pair_si(m, FXS(sub_1EEB90_001eeb90), {sx(d), rng(), rng(), rng()}, rng(), "sub_1EEB90", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            const u32 eff = v0_of(p);
            CHECK(get32(m, eff + 4) == d);
            CHECK(get32(m, eff + 8) == eff + 36);
            CHECK(get32(m, eff + 32) == 0xFEFFFFFFu);
            for (u32 t = 0; t < pk.T; ++t) {
                const u32 r = get32(m, eff + 8) + 76 * t;
                CHECK(get32(m, r) == get32(m, d + 12) + 24 * t);
                CHECK(get32(m, get32(m, eff + 12) + 8 * t) != 0);      // the atomic
                CHECK(get32(m, get32(m, eff + 12) + 8 * t + 4) != 0);  // the material
            }
            const u32 old_head = get32(m, kAeHead), old_tail = get32(m, kAeTail);
            put32(m, eff + 24, 0);
            put32(m, eff + 28, old_head);
            if (old_head != 0) put32(m, old_head + 24, eff);
            put32(m, kAeHead, eff);
            if (old_tail == 0) put32(m, kAeTail, eff);
            p = pair_si(m, FXS(sub_1EF340_001ef340), {sx(model), rng(), rng(), rng()}, rng(), "sub_1EF340", hw,
                            world(live_of(p), loaders(m)));
            ++pairs;
            CHECK(get32(m, kAeHead) == old_head);
            CHECK(get32(m, kAeTail) == old_tail);
            CHECK(p.recomp->heap.size_of(eff) == 0);
            CHECK(p.recomp->heap.size_of(d) == 0);
            emptied += p.recomp->heap.live().empty() ? 1 : 0;
        }
    }
    MESSAGE("after effects: " << pairs << " pairs, " << emptied << " destroys leaving the heap empty");
}

void clear_cdvd(Machine& m) {
    std::memset(m.at(game::kHCdvdListHead), 0, 16 + 256);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * game::kHCdvdCacheSlots);
}

TEST_CASE("game(fx_layers): effMng_CreateEffectProgramTasks and effAfter_CreateAfterEffectRenderTask -- files, "
          "textures, tasks") {
    const HwCheck hw = full_check();
    int pairs = 0, loaded = 0;
    for (const char* dir : kSnapshots) {
        auto mp = snapshot_machine(dir);
        if (!mp) {
            MESSAGE("SKIP: no snapshot " << dir);
            continue;
        }
        Machine& m = *mp;
        std::mt19937 rng{0xF1A0009};
        for (int i = 0; i < 2; ++i) {
            clear_cdvd(m);
            const bool load = i == 0;
            const Extra extra = [&m, load](StandInWorld& w) {
                loaders(m)(w);
                w.cd.load = load;
            };
            SiPair p = pair_si(m, FXS(effMng_CreateEffectProgramTasks_00322010), {rng(), rng(), rng(), rng()}, rng(),
                                   "effMng_CreateEffectProgramTasks", hw, world({}, extra));
            ++pairs;
            const StandIns& si = p.recomp->si;
            REQUIRE(calls(p, kHCdvdRequestFn) == 1);
            CHECK(si.log[0].text == FakeCd::build_path("effect/effpack.bin"));
            CHECK(si.log[0].args[1] == 1u);
            CHECK(calls(p, kHCdvdReadSyncFn) == 1);
            CHECK(calls(p, kHCdvdDestroyFn) == 1);
            if (load && p.recomp->cd.missing.empty()) ++loaded;
            // be_0001..be_0022: sprintf'd names, each loaded, filter 2 / addressing 0x11, kept at 0x957A20
            REQUIRE(calls(p, kSprintf) == 22);
            REQUIRE(calls(p, kTextureByName) == 22);
            u32 k = 0;
            for (const StandInCall& c : si.log) {
                if (c.va != kTextureByName) continue;
                char want[32];
                std::snprintf(want, sizeof want, "effect/be_%04u.tmx", k + 1);
                CHECK(c.text == want);
                CHECK(get32(m, kTexTable + 4 * k) == static_cast<u32>(c.v0));
                CHECK((get32(m, static_cast<u32>(c.v0) + 80) & 0xFFFFu) == 0x1102u);
                ++k;
            }
            CHECK(calls(p, 0x3580F0u) == 1);
            CHECK(calls(p, 0x351C20u) == 1);
            for (u32 t = 0; t < 7; ++t)  // the seven layer tables cleared (252 bytes each)
                for (u32 o = 0; o < 252; o += 4) CHECK(get32(m, 0x957320u + 0x100 * t + o) == 0);
            CHECK(get32(m, 0x9572D0u) == 1);
            clear_cdvd(m);
            p = pair_si(m, FXS(effAfter_CreateAfterEffectRenderTask_001eef20), {rng(), rng(), rng(), rng()}, rng(),
                            "effAfter_CreateAfterEffectRenderTask", hw, world(live_of(p), extra));
            ++pairs;
            REQUIRE(calls(p, kHCdvdRequestFn) == 1);
            CHECK(p.recomp->si.log[0].text == FakeCd::build_path("effect/z0.tmx"));
            REQUIRE(calls(p, kTextureByName) == 1);
            for (const StandInCall& c : p.recomp->si.log)
                if (c.va == kTextureByName) CHECK(get32(m, kZ0Texture) == static_cast<u32>(c.v0));
            CHECK(get32(m, kAeHead) == 0);
            CHECK(get32(m, kAeTail) == 0);
            CHECK(get32(m, kAeTask) == v0_of(p));
            CHECK(v0_of(p) != 0);
        }
    }
    MESSAGE("set-up functions: " << pairs << " pairs, " << loaded << " with effpack.bin read from extracted/");
}

}  // namespace
}  // namespace p3fes::game_test

#endif  // P3FES_GAME_HAVE_GENERATED
