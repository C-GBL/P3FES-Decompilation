// Shared helpers of the field6 pair tests (test_field6_fldrc / _comm / _misc / _result / _shuffle.cpp): the random-world
// sweep of every body (each random draw its own statement: the order of draws inside one argument list differs between
// MSVC and clang-cl), the field / exit-table data of the extracted packs, and a script task for the COMM handlers.
#pragma once

#include "field4_util.h"
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field6.h"
#include "p3fes/game/script_vm.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <memory>
#include <random>
#include <string>
#include <vector>

namespace p3fes::game_test::f6t {

using namespace f4t;

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

template <std::size_t N>
const Case& find_case(const Case (&cases)[N], const char* name) {
    for (const Case& c : cases)
        if (std::string(c.name) == name) return c;
    std::fprintf(stderr, "no case %s\n", name);
    std::abort();
}

// The p3fes_handgen sweep: every body against its recompiled body on `seeds` random worlds at [world, world + size).
template <std::size_t N>
void random_sweep(const Case (&cases)[N], u32 world, u32 size, u32 default_seeds) {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : default_seeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : cases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, world, size, rng);
            const u64 a0 = hgp::random_arg(rng, world, size);
            const u64 a1 = hgp::random_arg(rng, world, size);
            const u64 a2 = hgp::random_arg(rng, world, size);
            const u64 a3 = hgp::random_arg(rng, world, size);
            stops += hgp::pair(*m, c.hand, c.recomp, Args{a0, a1, a2, a3}, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// run_pair_si_absent with heap blocks already live in the stand-in arena (a world an earlier pair built through the
// stand-in heap, kept as the base of later pairs): [kStandInHeap, kStandInHeap + reserved) is marked used first.
inline SiPair run_absent_reserved(Machine& m, const std::vector<u8>& base, Fn hand, Fn recomp, const Args& args, u32 seed,
                                  const char* what, const std::function<void(Machine&)>& prepare, std::vector<u32>& absent,
                                  u32 reserved, u64 v0 = 0) {
    const HwCheck hw = whole_ram_check();
    for (int tries = 0;; ++tries) {
        reset(m, base);
        prepare(m);
        try {
            const std::vector<u32> list = absent;
            return run_pair_si(m, hand, recomp, args, seed, what, hw, [list, v0, reserved](StandInWorld& w) {
                install_field_world(w);
                if (reserved) w.heap.reserve(kStandInHeap, reserved);
                for (u32 va : list) w.si.install_recorder(va, "absent", v0);
            });
        } catch (const rt_test::FatalEvent& e) {
            const std::size_t k = e.what.find("function at 0x");
            if (k == std::string::npos || tries >= 32) throw;
            absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
        }
    }
}
// The end of the highest live block of a run's stand-in heap, relative to the arena base.
inline u32 heap_used(const StandInWorld& w) {
    u32 end = 0;
    for (const auto& [p, size] : w.heap.live()) end = std::max(end, p + size - kStandInHeap);
    return (end + 0xFFFu) & ~0xFFFu;
}

// --- the field packs (DATA/FIELD/PACK/FMMM_NNN.PAC: {char name[252], u32 size} headers, data 64-byte aligned) ---------
struct PacMember {
    std::string name;
    std::vector<u8> data;
};
inline std::vector<PacMember> read_pac(const std::string& rel) {
    std::vector<PacMember> out;
    const std::vector<u8> b = read_extracted(rel);
    std::size_t o = 0;
    while (o + 256 <= b.size()) {
        const char* nm = reinterpret_cast<const char*>(b.data() + o);
        const std::string name(nm, strnlen(nm, 252));
        u32 size;
        std::memcpy(&size, b.data() + o + 252, 4);
        if (name.empty() || o + 256 + size > b.size()) break;
        out.push_back({name, std::vector<u8>(b.begin() + static_cast<std::ptrdiff_t>(o + 256),
                                             b.begin() + static_cast<std::ptrdiff_t>(o + 256 + size))});
        o += 256 + ((size + 63u) & ~63u);
    }
    return out;
}
// Every exit table of the packs: {major, minor, bytes}.
struct HitTable {
    u32 major, minor;
    std::vector<u8> data;
};
inline std::vector<HitTable> all_hit_tables() {
    std::vector<HitTable> out;
    const std::string dir = extracted_root() + "/DATA/FIELD/PACK";
    for (u32 major = 0; major < 300; ++major)
        for (u32 minor = 0; minor < 100; ++minor) {
            char rel[64];
            std::snprintf(rel, sizeof rel, "DATA/FIELD/PACK/F%03u_%03u.PAC", major, minor);
            std::ifstream probe(extracted_root() + "/" + rel, std::ios::binary);
            if (!probe) continue;
            char want[32];
            std::snprintf(want, sizeof want, "h%03u_%03u.bin", major, minor);
            for (PacMember& mem : read_pac(rel))
                if (mem.name == want) out.push_back({major, minor, std::move(mem.data)});
        }
    (void)dir;
    return out;
}
// One 44-byte record read on the host (field6.h namespace hitrec).
struct HitRecord {
    s32 flags[3];
    u8 kind, prompt;
    u16 area, procedure, next_major, next_minor, next_entry, door_obj;
    s16 door_anim;
    s32 sound, side;
    u32 w36, w40;
};
inline HitRecord hit_record(const u8* p) {
    namespace h = game::f6::hitrec;
    HitRecord r{};
    std::memcpy(r.flags, p + h::kFlags, 12);
    r.kind = p[h::kKind];
    r.prompt = p[h::kPrompt];
    std::memcpy(&r.area, p + h::kAreaName, 2);
    std::memcpy(&r.procedure, p + h::kProcedure, 2);
    std::memcpy(&r.next_major, p + h::kNextMajor, 2);
    std::memcpy(&r.next_minor, p + h::kNextMinor, 2);
    std::memcpy(&r.next_entry, p + h::kNextEntry, 2);
    std::memcpy(&r.door_obj, p + h::kDoorObj, 2);
    std::memcpy(&r.door_anim, p + h::kDoorAnim, 2);
    std::memcpy(&r.sound, p + h::kSound, 4);
    std::memcpy(&r.side, p + h::kSide, 4);
    std::memcpy(&r.w36, p + 36, 4);
    std::memcpy(&r.w40, p + 40, 4);
    return r;
}

// --- a script task for the COMM handlers (script_vm.h ScrTask; g_scrCurrentTask points at it) ----------------------
constexpr u32 kScrTask = kScratch + 0x10000u;  // free in the field snapshots (field4_util.h kScratch)
inline void set_comm_args(Machine& m, const std::vector<s32>& ints, const std::vector<int>& float_slots = {}) {
    namespace scr = game::scr;
    const u32 sp = static_cast<u32>(ints.size());
    std::memset(m.at(kScrTask), 0, 0x100);
    w32(m, kScrTask + scr::kSp, sp);
    for (u32 i = 0; i < sp; ++i) {
        const u32 slot = sp - 1 - i;
        bool as_float = false;
        for (int f : float_slots) as_float |= static_cast<u32>(f) == i;
        m.at(kScrTask + scr::kTags + slot)[0] = static_cast<u8>(as_float ? scr::kTagFloat : scr::kTagInt);
        if (as_float) {
            const f32 v = static_cast<f32>(ints[i]);
            std::memcpy(m.at(kScrTask + scr::kValues + slot * 4), &v, 4);
        } else {
            w32(m, kScrTask + scr::kValues + slot * 4, static_cast<u32>(ints[i]));
        }
    }
    w32(m, kScrTask + scr::kValues + scr::kReturnSlot * 4, 0xDEADBEEFu);
    w32(m, scr::kCurrentTask, kScrTask);
}
inline u32 comm_return(Machine& m) { return r32(m, kScrTask + game::scr::kValues + game::scr::kReturnSlot * 4); }

// The scene resources of one type, read on the host as sub_3B5D50 / sub_3B5430 read them: the resource manager
// (MT_Scene +8) holds 22 list heads (+4 type), each resource the next of its type at +248.
inline std::vector<u32> scene_resources(Machine& m, u32 type) {
    std::vector<u32> out;
    const u32 mgr = r32(m, kSceneRecord + game::f4::scene::kResMgr);
    if (mgr < 0x100000u || mgr >= 0x2000000u || type >= 22) return out;
    for (u32 r = r32(m, mgr + 4 * type); r != 0 && out.size() < 512; r = r32(m, r + game::f6::sres::kNext)) {
        if (r < 0x100000u || r >= 0x2000000u) break;
        out.push_back(r);
    }
    return out;
}

}  // namespace p3fes::game_test::f6t
