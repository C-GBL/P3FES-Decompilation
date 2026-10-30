// Pair tests of the field7 slice, part lbox: the debug window / list box / colour box and the camera debug shapes
// (game/src/field/field7_lbox.cpp).
// First every body against its recompiled body on random worlds (the p3fes_handgen skeleton, tests/game/
// handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all 32 MiB of
// RAM, the scratchpad, the BIOS window, the bus log), then built worlds with real data and the documented rules.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field7_lbox.h"
#include "p3fes/game/task.h"

#include <algorithm>
#include <cstring>
#include <map>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_1A2200_001a2200(EEContext&);  // generated body
void fn_sub_1A2200_001a2200__recomp(EEContext&);  // recompiled
void fn_sub_1A2390_001a2390(EEContext&);  // generated body
void fn_sub_1A2390_001a2390__recomp(EEContext&);  // recompiled
void fn_sub_1A23D0_001a23d0(EEContext&);  // generated body
void fn_sub_1A23D0_001a23d0__recomp(EEContext&);  // recompiled
void fn_sub_1A23E0_001a23e0(EEContext&);  // generated body
void fn_sub_1A23E0_001a23e0__recomp(EEContext&);  // recompiled
void fn_sub_1A3B10_001a3b10(EEContext&);  // generated body
void fn_sub_1A3B10_001a3b10__recomp(EEContext&);  // recompiled
void fn_sub_1A3BE0_001a3be0(EEContext&);  // generated body
void fn_sub_1A3BE0_001a3be0__recomp(EEContext&);  // recompiled
void fn_sub_1A3C30_001a3c30(EEContext&);  // generated body
void fn_sub_1A3C30_001a3c30__recomp(EEContext&);  // recompiled
void fn_sub_1A3F20_001a3f20(EEContext&);  // generated body
void fn_sub_1A3F20_001a3f20__recomp(EEContext&);  // recompiled
void fn_sub_1A4010_001a4010(EEContext&);  // generated body
void fn_sub_1A4010_001a4010__recomp(EEContext&);  // recompiled
void fn_sub_1A4050_001a4050(EEContext&);  // generated body
void fn_sub_1A4050_001a4050__recomp(EEContext&);  // recompiled
void fn_sub_1A4090_001a4090(EEContext&);  // generated body
void fn_sub_1A4090_001a4090__recomp(EEContext&);  // recompiled
void fn_sub_1A4110_001a4110(EEContext&);  // generated body
void fn_sub_1A4110_001a4110__recomp(EEContext&);  // recompiled
void fn_sub_1A41F0_001a41f0(EEContext&);  // generated body
void fn_sub_1A41F0_001a41f0__recomp(EEContext&);  // recompiled
void fn_sub_1A4260_001a4260(EEContext&);  // generated body
void fn_sub_1A4260_001a4260__recomp(EEContext&);  // recompiled
void fn_sub_1A4380_001a4380(EEContext&);  // generated body
void fn_sub_1A4380_001a4380__recomp(EEContext&);  // recompiled
void fn_sub_1A44A0_001a44a0(EEContext&);  // generated body
void fn_sub_1A44A0_001a44a0__recomp(EEContext&);  // recompiled
void fn_sub_1A4660_001a4660(EEContext&);  // generated body
void fn_sub_1A4660_001a4660__recomp(EEContext&);  // recompiled
void fn_sub_1A46C0_001a46c0(EEContext&);  // generated body
void fn_sub_1A46C0_001a46c0__recomp(EEContext&);  // recompiled
void fn_sub_1A47E0_001a47e0(EEContext&);  // generated body
void fn_sub_1A47E0_001a47e0__recomp(EEContext&);  // recompiled
void fn_sub_1A4830_001a4830(EEContext&);  // generated body
void fn_sub_1A4830_001a4830__recomp(EEContext&);  // recompiled
void fn_sub_1A4B40_001a4b40(EEContext&);  // generated body
void fn_sub_1A4B40_001a4b40__recomp(EEContext&);  // recompiled
void fn_sub_1A4B70_001a4b70(EEContext&);  // generated body
void fn_sub_1A4B70_001a4b70__recomp(EEContext&);  // recompiled
void fn_sub_1A4CA0_001a4ca0(EEContext&);  // generated body
void fn_sub_1A4CA0_001a4ca0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1A2200", 0x1A2200, &recomp_gen::fn_sub_1A2200_001a2200, &recomp_gen::fn_sub_1A2200_001a2200__recomp},
    {"sub_1A2390", 0x1A2390, &recomp_gen::fn_sub_1A2390_001a2390, &recomp_gen::fn_sub_1A2390_001a2390__recomp},
    {"sub_1A23D0", 0x1A23D0, &recomp_gen::fn_sub_1A23D0_001a23d0, &recomp_gen::fn_sub_1A23D0_001a23d0__recomp},
    {"sub_1A23E0", 0x1A23E0, &recomp_gen::fn_sub_1A23E0_001a23e0, &recomp_gen::fn_sub_1A23E0_001a23e0__recomp},
    {"sub_1A3B10", 0x1A3B10, &recomp_gen::fn_sub_1A3B10_001a3b10, &recomp_gen::fn_sub_1A3B10_001a3b10__recomp},
    {"sub_1A3BE0", 0x1A3BE0, &recomp_gen::fn_sub_1A3BE0_001a3be0, &recomp_gen::fn_sub_1A3BE0_001a3be0__recomp},
    {"sub_1A3C30", 0x1A3C30, &recomp_gen::fn_sub_1A3C30_001a3c30, &recomp_gen::fn_sub_1A3C30_001a3c30__recomp},
    {"sub_1A3F20", 0x1A3F20, &recomp_gen::fn_sub_1A3F20_001a3f20, &recomp_gen::fn_sub_1A3F20_001a3f20__recomp},
    {"sub_1A4010", 0x1A4010, &recomp_gen::fn_sub_1A4010_001a4010, &recomp_gen::fn_sub_1A4010_001a4010__recomp},
    {"sub_1A4050", 0x1A4050, &recomp_gen::fn_sub_1A4050_001a4050, &recomp_gen::fn_sub_1A4050_001a4050__recomp},
    {"sub_1A4090", 0x1A4090, &recomp_gen::fn_sub_1A4090_001a4090, &recomp_gen::fn_sub_1A4090_001a4090__recomp},
    {"sub_1A4110", 0x1A4110, &recomp_gen::fn_sub_1A4110_001a4110, &recomp_gen::fn_sub_1A4110_001a4110__recomp},
    {"sub_1A41F0", 0x1A41F0, &recomp_gen::fn_sub_1A41F0_001a41f0, &recomp_gen::fn_sub_1A41F0_001a41f0__recomp},
    {"sub_1A4260", 0x1A4260, &recomp_gen::fn_sub_1A4260_001a4260, &recomp_gen::fn_sub_1A4260_001a4260__recomp},
    {"sub_1A4380", 0x1A4380, &recomp_gen::fn_sub_1A4380_001a4380, &recomp_gen::fn_sub_1A4380_001a4380__recomp},
    {"sub_1A44A0", 0x1A44A0, &recomp_gen::fn_sub_1A44A0_001a44a0, &recomp_gen::fn_sub_1A44A0_001a44a0__recomp},
    {"sub_1A4660", 0x1A4660, &recomp_gen::fn_sub_1A4660_001a4660, &recomp_gen::fn_sub_1A4660_001a4660__recomp},
    {"sub_1A46C0", 0x1A46C0, &recomp_gen::fn_sub_1A46C0_001a46c0, &recomp_gen::fn_sub_1A46C0_001a46c0__recomp},
    {"sub_1A47E0", 0x1A47E0, &recomp_gen::fn_sub_1A47E0_001a47e0, &recomp_gen::fn_sub_1A47E0_001a47e0__recomp},
    {"sub_1A4830", 0x1A4830, &recomp_gen::fn_sub_1A4830_001a4830, &recomp_gen::fn_sub_1A4830_001a4830__recomp},
    {"sub_1A4B40", 0x1A4B40, &recomp_gen::fn_sub_1A4B40_001a4b40, &recomp_gen::fn_sub_1A4B40_001a4b40__recomp},
    {"sub_1A4B70", 0x1A4B70, &recomp_gen::fn_sub_1A4B70_001a4b70, &recomp_gen::fn_sub_1A4B70_001a4b70__recomp},
    {"sub_1A4CA0", 0x1A4CA0, &recomp_gen::fn_sub_1A4CA0_001a4ca0, &recomp_gen::fn_sub_1A4CA0_001a4ca0__recomp},
};

// The random world: 64 KiB of free RAM above the harness's arena (the built worlds follow below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field7_lbox): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}


// =====================================================================================================================
// Meaningful pairs on the stand-in world (tests/game/stand_ins.h: the heap behind the RW calloc / free slots and
// H_Malloc, which the hand-written kwln kernel creates tasks with): a debug list box built item by item the way the
// event editor does (labels, then a kind and value per item), re-laid out after every change, items removed and the
// box cleared; the window's creation and state predicate; the colour box; the camera debug shapes' draws. Each call
// is one pair (hand vs recompiled, whole RAM, every register at every check point, the dead stack, the stand-ins'
// logs); the machine keeps the recompiled run's state and the heap's live blocks go on to the next call. The host
// restates the documented rules of field7_lbox.h and checks the guest state against them.
// =====================================================================================================================

namespace {

namespace rg = p3fes::recomp_gen;
using namespace p3fes::game::f7::lbox;

Machine* lbox_machine() {
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

u32 g32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
float gf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

HwCheck lbox_check(u64 t0 = 0, u64 t1 = 0) {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in[GPR_T0] = t0;  // arguments 5 and 6
    hw.gpr_in[GPR_T1] = t1;
    return hw;
}

constexpr u32 kParent = 0x01B80000u;
constexpr u32 kStrings = 0x01B84000u;  // guest strings (labels, texts), 256 bytes each

void clean_world(Machine& m) {
    std::memset(m.at(0x7CE064u), 0, 0x7CE088u - 0x7CE064u);  // the kwln starting / ending / running lists
    std::memset(m.at(kParent), 0, 0x8000);
    p32(m, kParent + game::kwln::kOffWork, kParent + 0x100u);
    p32(m, kParent + game::kwln::kOffState, 2);
}

using Live = std::map<u32, u32>;
struct World {
    Machine& m;
    Live live;
    int pairs = 0;
    u32 seed = 1;
    u32 call(Fn hand, Fn recomp, const Args& args, const char* what, u64 t0 = 0, u64 t1 = 0) {
        const Live carried = live;
        SiPair p = run_pair_si(m, hand, recomp, args, seed++, what, lbox_check(t0, t1), [carried](StandInWorld& w) {
            install_standard(w);
            for (const auto& [b, n] : carried) w.heap.reserve(b, n);
        });
        ++pairs;
        live = p.recomp->heap.live();
        return static_cast<u32>(p.hw.recomp.base.v0);
    }
};

u32 put_string(Machine& m, u32 slot, const std::string& s) {
    const u32 va = kStrings + 256u * slot;
    std::memset(m.at(va), 0, 256);
    std::memcpy(m.at(va), s.data(), s.size());
    return va;
}

// The host's model of one item and of sub_1A3C30's line length for it.
struct Item {
    u32 id;
    std::string label;
    u32 kind = 0;
    std::string text;
    u32 hex = 0;
    u32 value = 0, lo = 0, hi = 0;
};
u32 line_chars(const Item& it) {
    const u32 n = static_cast<u32>(it.label.size());
    switch (it.kind) {
    case 1: return n + 1u + static_cast<u32>(it.text.size());
    case 2: return n + 1u + 5u;  // strlen("FALSE")
    case 3: return n + (it.hex ? 11u : 9u);
    case 4: return n + 8u;
    default: return n;
    }
}

void check_box(Machine& m, u32 work, const std::vector<Item>& items) {
    // the list in order, linked both ways
    u32 node = g32(m, work + kBoxItems), prev = 0;
    u32 widest = 0;
    for (const Item& it : items) {
        REQUIRE(node != 0);
        CHECK(g32(m, node + kItemId) == it.id);
        CHECK(m.str(node + kItemLabel, 256) == it.label);
        CHECK(g32(m, node + kItemKind) == it.kind);
        CHECK(g32(m, node + kItemPrev) == prev);
        widest = std::max(widest, line_chars(it));
        prev = node;
        node = g32(m, node + kItemNext);
    }
    CHECK(node == 0);
    CHECK(g32(m, work + kBoxCount) == items.size());
    // the layout rule: 12 px per character + 4; 12 px per visible row + 4
    CHECK(g32(m, work + kBoxW) == 12u * widest + 4u);
    const u32 rows = std::min<u32>(static_cast<u32>(items.size()), g32(m, work + kBoxRows));
    CHECK(g32(m, work + kBoxH) == 12u * rows + 4u);
}

}  // namespace

TEST_CASE("game(field7_lbox): a list box grows item by item, takes one kind per item and lays itself out") {
    Machine* mp = lbox_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x1B0Bu};
    int boxes = 0;
    World w{m, {}};
    for (int round = 0; round < 6; ++round) {
        clean_world(m);
        w.live.clear();
        const u32 x = 16u + rng() % 200u;
        const u32 y = 16u + rng() % 200u;
        const u32 style = 1u + rng() % 3u;
        const u32 task = w.call(&rg::fn_sub_1A3B10_001a3b10, &rg::fn_sub_1A3B10_001a3b10__recomp,
                                {sx(kParent), sx(x), sx(y), sx(style)}, "sub_1A3B10 create");
        REQUIRE(task != 0);
        ++boxes;
        CHECK(m.str(task + game::kwln::kOffName, 24) == "ksk list box");
        CHECK(g32(m, task + game::kwln::kOffUpdate) == 0x1A2A80u);
        CHECK(g32(m, task + game::kwln::kOffDestroy) == 0x1A3A60u);
        const u32 work = g32(m, task + kTaskWork);
        CHECK(g32(m, work + kBoxX) == x);
        CHECK(g32(m, work + kBoxY) == y);
        CHECK(g32(m, work + kBoxW) == 128);
        CHECK(g32(m, work + kBoxH) == 128);
        CHECK(g32(m, work + kBoxRows) == 10);
        CHECK(g32(m, work + kBoxStyle) == style);
        // labels
        std::vector<Item> items;
        const u32 n = 1u + rng() % 14u;
        for (u32 i = 0; i < n; ++i) {
            std::string label;
            const u32 len = rng() % 24u;
            for (u32 k = 0; k < len; ++k) label += static_cast<char>('A' + rng() % 26u);
            const u32 va = put_string(m, i % 8u, label);
            const u32 id = w.call(&rg::fn_sub_1A3F20_001a3f20, &rg::fn_sub_1A3F20_001a3f20__recomp,
                                  {sx(task), sx(va), 0, 0}, "sub_1A3F20 add");
            CHECK(id == i);  // ids count from 0
            Item item;
            item.id = id;
            item.label = label;
            items.push_back(item);
            check_box(m, work, items);
        }
        CHECK(g32(m, work + kBoxNextId) == n);
        // kinds and values (a second setter on the same item changes nothing)
        for (Item& it : items) {
            const u32 kind = rng() % 5u;
            const u32 value = rng() % 1000u;
            const u32 lo = rng() % 10u;
            const u32 hi = 10u + rng() % 100u;
            const u32 hex = rng() & 1u;
            for (int again = 0; again < 2; ++again) {
                const u32 k = again == 0 ? kind : 1u + (kind % 4u);
                switch (k) {
                case 1: {
                    std::string text;
                    const u32 len = rng() % 12u;
                    for (u32 c = 0; c < len; ++c) text += static_cast<char>('a' + rng() % 26u);
                    const bool none = rng() % 4u == 0;
                    const u32 va = none ? 0u : put_string(m, 9, text);
                    w.call(&rg::fn_sub_1A4090_001a4090, &rg::fn_sub_1A4090_001a4090__recomp,
                           {sx(task), sx(it.id), sx(va), 0}, "sub_1A4090 string");
                    if (it.kind == 0) {
                        it.kind = 1;
                        if (!none) it.text = text;
                    }
                    break;
                }
                case 2:
                    w.call(&rg::fn_sub_1A41F0_001a41f0, &rg::fn_sub_1A41F0_001a41f0__recomp,
                           {sx(task), sx(it.id), sx(value & 1u), 0}, "sub_1A41F0 flag");
                    if (it.kind == 0) {
                        it.kind = 2;
                        it.value = value & 1u;
                    }
                    break;
                case 3:
                    w.call(&rg::fn_sub_1A4110_001a4110, &rg::fn_sub_1A4110_001a4110__recomp,
                           {sx(task), sx(it.id), sx(value), sx(lo)}, "sub_1A4110 int", sx(hi), sx(hex));
                    if (it.kind == 0) {
                        it.kind = 3;
                        it.hex = hex;
                        it.value = value;
                        it.lo = lo;
                        it.hi = hi;
                    }
                    break;
                case 4:
                    w.call(&rg::fn_sub_1A4260_001a4260, &rg::fn_sub_1A4260_001a4260__recomp,
                           {sx(task), sx(it.id), sx(value), sx(lo)}, "sub_1A4260 float", sx(hi));
                    if (it.kind == 0) {
                        it.kind = 4;
                        it.value = value;
                        it.lo = lo;
                        it.hi = hi;
                    }
                    break;
                default:
                    break;
                }
            }
            check_box(m, work, items);
        }
        // the values the setters stored, item by item
        u32 node = g32(m, work + kBoxItems);
        for (const Item& it : items) {
            if (it.kind == 1 && !it.text.empty()) CHECK(m.str(node + kItemText, 256) == it.text);
            if (it.kind == 2) {
                CHECK(g32(m, node + kItemValue) == it.value);
                CHECK(g32(m, node + kItemMin) == 0);
                CHECK(g32(m, node + kItemMax) == 1);
            }
            if (it.kind == 3) {
                CHECK(g32(m, node + kItemValue) == it.value);
                CHECK(g32(m, node + kItemMin) == it.lo);
                CHECK(g32(m, node + kItemMax) == it.hi);
                CHECK(g32(m, node + kItemHex) == it.hex);
            }
            if (it.kind == 4) {
                CHECK(gf(m, node + kItemFloat) == static_cast<float>(static_cast<s32>(it.value)));
                CHECK(g32(m, node + kItemMin) == it.lo);
                CHECK(g32(m, node + kItemMax) == it.hi);
            }
            node = g32(m, node + kItemNext);
        }
        // label lookup and the word +540
        for (const Item& it : items) {
            const u32 label = w.call(&rg::fn_sub_1A4010_001a4010, &rg::fn_sub_1A4010_001a4010__recomp,
                                     {sx(task), sx(it.id), 0, 0}, "sub_1A4010 label");
            CHECK(m.str(label, 256) == it.label);
        }
        CHECK(w.call(&rg::fn_sub_1A4010_001a4010, &rg::fn_sub_1A4010_001a4010__recomp, {sx(task), sx(0xFFFFFFFFu), 0, 0},
                     "sub_1A4010 none") == 0);
        w.call(&rg::fn_sub_1A4050_001a4050, &rg::fn_sub_1A4050_001a4050__recomp, {sx(task), sx(items[0].id), 0x77, 0},
               "sub_1A4050");
        CHECK(g32(m, g32(m, work + kBoxItems) + kItemWord540) == 0x77);
        // removals: an id -1 does nothing; each removal unlinks, frees and re-lays out; top / cursor follow the rule
        w.call(&rg::fn_sub_1A4380_001a4380, &rg::fn_sub_1A4380_001a4380__recomp, {sx(task), sx(0xFFFFFFFFu), 0, 0},
               "sub_1A4380 none");
        check_box(m, work, items);
        const u32 removals = rng() % (static_cast<u32>(items.size()) + 1u);
        for (u32 r = 0; r < removals; ++r) {
            const std::size_t at = rng() % items.size();
            const u32 top = rng() % 4u;
            const u32 cursor = rng() % 10u;
            p32(m, work + kBoxTop, top);
            p32(m, work + kBoxCursor, cursor);
            const Item gone = items[at];
            w.call(&rg::fn_sub_1A4380_001a4380, &rg::fn_sub_1A4380_001a4380__recomp, {sx(task), sx(gone.id), 0, 0},
                   "sub_1A4380 remove");
            items.erase(items.begin() + static_cast<std::ptrdiff_t>(at));
            const u32 count = static_cast<u32>(items.size());
            if (count == 0) {
                CHECK(g32(m, work + kBoxItems) == 0);
                CHECK(g32(m, work + kBoxTop) == 0);
                CHECK(g32(m, work + kBoxCursor) == 0);
                CHECK(g32(m, work + kBoxW) == 4);
                CHECK(g32(m, work + kBoxH) == 4);
                break;
            }
            const bool pull = count < 10u && top + cursor >= count;
            CHECK(g32(m, work + kBoxTop) == (pull ? count - 1u : top));
            CHECK(g32(m, work + kBoxCursor) == (pull ? 0u : cursor));
            check_box(m, work, items);
        }
        // clear: every item freed, count / top / cursor 0 (the head word is left)
        const u32 head = g32(m, work + kBoxItems);
        std::vector<u32> nodes;
        for (u32 nd = head; nd != 0; nd = g32(m, nd + kItemNext)) nodes.push_back(nd);
        w.call(&rg::fn_sub_1A44A0_001a44a0, &rg::fn_sub_1A44A0_001a44a0__recomp, {sx(task), 0, 0, 0}, "sub_1A44A0 clear");
        CHECK(g32(m, work + kBoxCount) == 0);
        CHECK(g32(m, work + kBoxTop) == 0);
        CHECK(g32(m, work + kBoxCursor) == 0);
        CHECK(g32(m, work + kBoxItems) == head);
        for (u32 nd : nodes) CHECK(w.live.count(nd) == 0);  // freed
    }
    MESSAGE("list boxes: " << boxes << " built, " << w.pairs << " pairs");
}

TEST_CASE("game(field7_lbox): the window, the colour box and the camera debug shapes") {
    Machine* mp = lbox_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x3170u};
    World w{m, {}};
    // the window: rect, colours, the scratch buffer of (x / 8) * (y / 8) + 32 bytes (C division)
    for (int i = 0; i < 12; ++i) {
        clean_world(m);
        w.live.clear();
        s32 rect[4];
        for (s32& v : rect) {
            const u32 r = rng();
            v = static_cast<s32>(r % 600u) - 100;
        }
        const u32 rect_va = kStrings;
        std::memcpy(m.at(rect_va), rect, 16);
        const u32 frame_rgba = rng();
        const u32 fill_rgba = rng();
        p32(m, kStrings + 0x20u, frame_rgba);
        p32(m, kStrings + 0x24u, fill_rgba);
        const u32 task = w.call(&rg::fn_sub_1A2200_001a2200, &rg::fn_sub_1A2200_001a2200__recomp,
                                {sx(kParent), sx(rect_va), sx(kStrings + 0x20u), sx(kStrings + 0x24u)}, "sub_1A2200 create");
        REQUIRE(task != 0);
        CHECK(m.str(task + game::kwln::kOffName, 24) == "ksk window");
        CHECK(g32(m, task + game::kwln::kOffUpdate) == 0x1A1550u);
        CHECK(g32(m, task + game::kwln::kOffDestroy) == 0x1A2170u);
        const u32 work = g32(m, task + kTaskWork);
        CHECK(g32(m, work + kWinVisible) == 1);
        CHECK(std::memcmp(m.at(work + kWinRect), rect, 16) == 0);
        CHECK(g32(m, work + kWinFrameRgba) == frame_rgba);
        CHECK(g32(m, work + kWinFillRgba) == fill_rgba);
        CHECK(g32(m, work + kWinBufSize) == static_cast<u32>((rect[0] / 8) * (rect[1] / 8) + 32));
        CHECK(g32(m, work + kWinBuf) == g32(m, work + kWinBufCur));
        // the state predicate over every state, and the visibility word
        for (u32 st = 0; st <= 9; ++st) {
            p32(m, work + kWinState, st);
            const u32 busy = w.call(&rg::fn_sub_1A2390_001a2390, &rg::fn_sub_1A2390_001a2390__recomp,
                                    {sx(task), 0, 0, 0}, "sub_1A2390");
            CHECK(busy == ((st == 6 || st == 8) ? 0u : 1u));
        }
        w.call(&rg::fn_sub_1A23D0_001a23d0, &rg::fn_sub_1A23D0_001a23d0__recomp, {sx(task), 0, 0, 0}, "sub_1A23D0");
        CHECK(g32(m, work + kWinVisible) == 0);
        // the rect setter outside state 6 changes nothing
        p32(m, work + kWinState, 5);
        w.call(&rg::fn_sub_1A23E0_001a23e0, &rg::fn_sub_1A23E0_001a23e0__recomp, {sx(task), sx(rect_va), 0, 0},
               "sub_1A23E0 not open");
    }
    // the colour box: its target word, then the destroy frees the work
    clean_world(m);
    w.live.clear();
    const u32 cb = w.call(&rg::fn_sub_1A4B70_001a4b70, &rg::fn_sub_1A4B70_001a4b70__recomp, {sx(kParent), 0x1234, 0, 0},
                          "sub_1A4B70 create");
    REQUIRE(cb != 0);
    CHECK(m.str(cb + game::kwln::kOffName, 24) == "color box");
    CHECK(g32(m, cb + game::kwln::kOffUpdate) == 0x1A4940u);
    const u32 cb_work = g32(m, cb + kTaskWork);
    CHECK(g32(m, cb_work + kColorBoxTarget) == 0x1234);
    CHECK(w.live.count(cb_work) == 1);
    w.call(&rg::fn_sub_1A4B40_001a4b40, &rg::fn_sub_1A4B40_001a4b40__recomp, {sx(cb), 0, 0, 0}, "sub_1A4B40 destroy");
    // the debug point / cylinder draws while off: nothing drawn, 0 returned (switched on they draw through the wire
    // sphere / cylinder of sub_359B40 / sub_359E50, whose RW immediate-mode callees this test build does not emit: the
    // random-world pass covers that path up to the first of them)
    constexpr u32 kShapeTask = kParent + 0x2000u;
    constexpr u32 kShapeWork = kParent + 0x2100u;
    int shapes = 0;
    for (int i = 0; i < 16; ++i) {
        std::memset(m.at(kShapeWork), 0, 64);
        p32(m, kShapeTask + kTaskWork, kShapeWork);
        p32(m, kShapeWork + kDbgOn, 0);
        float pos[3];
        for (float& f : pos) {
            const u32 r = rng();
            f = static_cast<float>(static_cast<s32>(r % 4001u) - 2000);
        }
        std::memcpy(m.at(kShapeWork + kDbgPos), pos, 12);
        const float radius = 20.0f + static_cast<float>(rng() % 100u);
        const float height = 50.0f + static_cast<float>(rng() % 200u);
        std::memcpy(m.at(kShapeWork + kDbgCylRadius), &radius, 4);
        std::memcpy(m.at(kShapeWork + kDbgCylHeight), &height, 4);
        CHECK(w.call(&rg::fn_sub_1A4660_001a4660, &rg::fn_sub_1A4660_001a4660__recomp, {sx(kShapeTask), 0, 0, 0},
                     "sub_1A4660 point") == 0);
        CHECK(w.call(&rg::fn_sub_1A47E0_001a47e0, &rg::fn_sub_1A47E0_001a47e0__recomp, {sx(kShapeTask), 0, 0, 0},
                     "sub_1A47E0 cylinder") == 0);
        ++shapes;
        CHECK(std::memcmp(m.at(kShapeWork + kDbgPos), pos, 12) == 0);
    }
    MESSAGE("window / colour box / debug shapes: " << w.pairs << " pairs, " << shapes << " switched-off shape tasks");
}

#else

TEST_CASE("game(field7_lbox): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
