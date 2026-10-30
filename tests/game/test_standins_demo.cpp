// Pair tests of the standins_demo slice (game/src/misc/standins_demo.cpp): heap users, printf users and file loaders
// against their recompiled bodies, both runs on a fresh stand-in world (stand_ins.h: the guest heap behind H_Malloc
// and the RW memory slots, printf / sprintf, the H_Cdvd layer over extracted/). Every pair compares the whole RAM
// (write-tracked), the scratchpad, every GPR in 128 bits, HI/LO, the register file and cycles at every check point,
// the dead stack (frames and spills), the stand-ins' call logs, the heaps' live blocks and the file layers' nodes.
// The first pairs of each loader read the real files (when extracted/ is there); the rest record the requests.
#include <doctest.h>

#include "stand_ins.h"

#include "p3fes/game/hcdvd.h"

#include <cstring>
#include <string>

#define SD_FNS(X)                                                   \
    X(sub_266A20_00266a20) X(sub_266CB0_00266cb0) X(sub_21C7F0_0021c7f0) \
    X(sub_233B20_00233b20) X(sub_2339D0_002339d0) X(sub_24BE40_0024be40) \
    X(sub_107020_00107020) X(sub_2699A0_002699a0) X(sub_266600_00266600) \
    X(sub_3C4430_003c4430) X(sub_3C45F0_003c45f0) X(sub_3C4F30_003c4f30) \
    X(sub_430150_00430150) X(sub_4310E0_004310e0) X(Y_SMap_CreateStaireDispTask_00430180) \
    X(sub_234710_00234710) X(sub_2449D0_002449d0) X(sub_1FA450_001fa450) \
    X(sub_1FBCA0_001fbca0) X(sub_21B8B0_0021b8b0) X(kwlnAdxErrorCallback_00197fb0) \
    X(bpIfontDrawNumber_00238980)

namespace p3fes::recomp_gen {
#define SD_DECL(n) void fn_##n(p3fes::EEContext&); void fn_##n##__recomp(p3fes::EEContext&);
SD_FNS(SD_DECL)
#undef SD_DECL
}  // namespace p3fes::recomp_gen

namespace p3fes::game_test {
namespace {

namespace rg = p3fes::recomp_gen;

Machine* machine() {
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

#define NEED_MACHINE()                                                  \
    Machine* mp = machine();                                            \
    if (!mp) {                                                          \
        MESSAGE("SKIP: no ELF at " << elf_path());                      \
        return;                                                         \
    }                                                                   \
    Machine& m = *mp

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
u32 get32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void put_gp(Machine& m, s32 off, u32 v) { put32(m, kGp + static_cast<u32>(off), v); }

// A clean file layer before a loader pair: no requests, an empty sCdvdCache.
void clear_cdvd(Machine& m) {
    std::memset(m.at(game::kHCdvdListHead), 0, 16 + 256);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * game::kHCdvdCacheSlots);
}

constexpr u32 kWork = kArena + 0x100;  // the module work record the loaders find through their gp word

// The Answer (sub_17D800 returns the scenario word gp-19788) and datGetFlag(752) (bit 16 of the flag word 0x83A278).
void random_scenario(Machine& m, std::mt19937& rng) {
    put_gp(m, -19788, (rng() & 1) ? 1u : 0u);
    put32(m, 0x83A278u, rng());
}

}  // namespace

using LoaderFn = void (*)(EEContext&);

struct LoaderCase {
    const char* name;
    LoaderFn hand, recomp;
    s32 gp_off;
    u32 clear_mask0, clear_mask4;  // bits the asserts want clear in +0 / +4
    s32 store;
    u32 bit;
    const char* path;  // the request's path (the plain one for sub_2339D0)
};

TEST_CASE("game(standins_demo): the file loaders request through the fake H_Cdvd layer") {
    NEED_MACHINE();
    const LoaderCase cases[] = {
        {"sub_266A20", rg::fn_sub_266A20_00266a20, rg::fn_sub_266A20_00266a20__recomp, -18780, 1, 1, 8, 1, "oped/op_title.bin"},
        {"sub_266CB0", rg::fn_sub_266CB0_00266cb0, rg::fn_sub_266CB0_00266cb0__recomp, -18780, 2, 2, 72, 2, "oped/op_logo.bin"},
        {"sub_21C7F0", rg::fn_sub_21C7F0_0021c7f0, rg::fn_sub_21C7F0_0021c7f0__recomp, -18924, 0, 0, 132, 4, "battle/panel/bp_tutorial.bin"},
        {"sub_233B20", rg::fn_sub_233B20_00233b20, rg::fn_sub_233B20_00233b20__recomp, -18916, 2, 0, 16, 2, "battle/result/br_level.bin"},
        {"sub_2339D0", rg::fn_sub_2339D0_002339d0, rg::fn_sub_2339D0_002339d0__recomp, -18916, 1, 0, 12, 1, "battle/result/br_base.bin"},
        {"sub_24BE40", rg::fn_sub_24BE40_0024be40, rg::fn_sub_24BE40_0024be40__recomp, -18876, 0, 1, 8, 1, "battle/result/brp_birth.bin"},
    };
    const HwCheck hw = full_check();
    std::mt19937 rng{0x5D0001};
    int pairs = 0, asserted = 0, loaded = 0;
    for (const LoaderCase& c : cases) {
        for (int i = 0; i < 160; ++i) {
            clear_cdvd(m);
            const bool no_work = (rng() & 15) == 0;
            put_gp(m, c.gp_off, no_work ? 0u : kWork);
            for (u32 k = 0; k < 160; k += 4) put32(m, kWork + k, rng());
            u32 f0 = rng(), f4 = rng();
            if ((rng() & 7) != 0) f0 &= ~c.clear_mask0;
            if ((rng() & 7) != 0) f4 &= ~c.clear_mask4;
            put32(m, kWork, f0);
            put32(m, kWork + 4, f4);
            random_scenario(m, rng);  // sub_2339D0: The Answer and flag 752 pick the variant
            const bool load = i < 3;
            const WorldSetup setup = [load](StandInWorld& w) {
                install_standard(w);
                w.cd.load = load;
            };
            const SiPair p = run_pair_si(m, c.hand, c.recomp, {rng(), rng(), rng(), rng()}, rng(), c.name, hw, setup);
            ++pairs;
            asserted += (no_work || (f0 & c.clear_mask0) || (f4 & c.clear_mask4)) ? 1 : 0;
            const StandIns& si = p.recomp->si;
            REQUIRE(si.calls_to(kHCdvdRequestFn) == 1);
            const StandInCall& rq = si.log[0];
            if (std::string(c.name) != "sub_2339D0") {
                CHECK(rq.text == FakeCd::build_path(c.path));
            } else {
                const bool answer = get32(m, kGp - 19788u) != 0, flag = (get32(m, 0x83A278u) >> 16) & 1u;
                CHECK(rq.text == FakeCd::build_path(!answer ? "battle/result/br_base.bin"
                                                    : flag  ? "battle/result/AGS_br_base.bin"
                                                            : "battle/result/AGS2_br_base.bin"));
            }
            CHECK(rq.args[1] == (std::string(c.name) == "sub_21C7F0" ? 0u : 1u));
            // the node lands in work[store] and the bit is set (work = address 0 on the K_Assert path)
            const u32 work = no_work ? 0u : kWork;
            CHECK(get32(m, work + static_cast<u32>(c.store)) == static_cast<u32>(rq.v0));
            CHECK((get32(m, work) & c.bit) == c.bit);
            if (load && !p.recomp->cd.missing.empty()) MESSAGE(c.name << ": not under extracted/: " << p.recomp->cd.missing[0]);
            if (load && p.recomp->cd.missing.empty()) ++loaded;
        }
    }
    MESSAGE("loaders: " << pairs << " pairs (" << asserted << " through a K_Assert), " << loaded << " real loads");
}

TEST_CASE("game(standins_demo): sub_107020 requests and read-syncs the fade PAK") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0x5D0002};
    int pairs = 0, loaded = 0;
    for (int i = 0; i < 40; ++i) {
        clear_cdvd(m);
        const bool load = i < 4;
        const SiPair p = run_pair_si(m, rg::fn_sub_107020_00107020, rg::fn_sub_107020_00107020__recomp,
                                     {rng(), rng(), rng(), rng()}, rng(), "sub_107020", hw, [load](StandInWorld& w) {
                                         install_standard(w);
                                         w.cd.load = load;
                                     });
        ++pairs;
        const StandIns& si = p.recomp->si;
        REQUIRE(si.log.size() == 2);
        CHECK(si.log[0].text == FakeCd::build_path("camp/fade_pak.pak"));
        CHECK(si.log[1].va == kHCdvdReadSyncFn);
        CHECK(si.log[1].args[0] == si.log[0].v0);
        CHECK(get32(m, 0x7E39D0u) == static_cast<u32>(si.log[0].v0));
        if (load && si.log[1].extra != 0) ++loaded;
    }
    MESSAGE("sub_107020: " << pairs << " pairs, " << loaded << " with the PAK read");
}

TEST_CASE("game(standins_demo): the heap users on the guest heap") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0x5D0003};
    int pairs = 0;
    // A world whose heap already holds `n` blocks (the same in both runs): kStandInHeap, +0x40, ...
    auto with_blocks = [](int n, u32 size) {
        return [n, size](StandInWorld& w) {
            install_standard(w);
            for (int k = 0; k < n; ++k) w.heap.alloc(size);
        };
    };
    // sub_2699A0(ptr): a live block, a random pointer (a bad free) or 0.
    for (int i = 0; i < 200; ++i) {
        const u32 r = rng() % 3;
        const u32 ptr = r == 0 ? kStandInHeap + 0x40u * (rng() % 4) : r == 1 ? rng() : 0u;
        const SiPair p = run_pair_si(m, rg::fn_sub_2699A0_002699a0, rg::fn_sub_2699A0_002699a0__recomp,
                                     {ptr, rng(), rng(), rng()}, rng(), "sub_2699A0", hw, with_blocks(4, 0x40));
        ++pairs;
        REQUIRE(p.recomp->si.log.size() == 1);
        CHECK(p.recomp->si.log[0].va == 0x104280u);
        CHECK(p.recomp->heap.live().size() == (r == 0 ? 3u : 4u));
    }
    // sub_266600(task) / sub_430150(task) / sub_4310E0(task): free(task->+60).
    for (int i = 0; i < 300; ++i) {
        const int which = i % 3;
        const u32 task = kArena + 0x400;
        for (u32 k = 0; k < 0x68; k += 4) put32(m, task + k, rng());
        put32(m, task + 60, (rng() & 3) ? kStandInHeap + 0x40u * (rng() % 4) : rng());
        put_gp(m, -18788, (rng() & 7) ? rng() | 1u : 0u);
        const LoaderFn hand = which == 0 ? rg::fn_sub_266600_00266600 : which == 1 ? rg::fn_sub_430150_00430150 : rg::fn_sub_4310E0_004310e0;
        const LoaderFn recomp = which == 0   ? rg::fn_sub_266600_00266600__recomp
                                : which == 1 ? rg::fn_sub_430150_00430150__recomp
                                             : rg::fn_sub_4310E0_004310e0__recomp;
        const char* name = which == 0 ? "sub_266600" : which == 1 ? "sub_430150" : "sub_4310E0";
        const SiPair p = run_pair_si(m, hand, recomp, {task, rng(), rng(), rng()}, rng(), name, hw, with_blocks(4, 0x40));
        ++pairs;
        REQUIRE(p.recomp->si.log.size() == 1);
        CHECK(static_cast<u32>(p.recomp->si.log[0].args[0]) == get32(m, task + 60));
        if (which == 0) CHECK(get32(m, kGp - 18788u) == 0u);
    }
    // sub_3C4430(payload): a zeroed block of payload + 24 bytes, its header filled.
    for (int i = 0; i < 300; ++i) {
        const u32 payload = (rng() & 3) == 0 ? 0u : rng() % 0x400;
        const SiPair p = run_pair_si(m, rg::fn_sub_3C4430_003c4430, rg::fn_sub_3C4430_003c4430__recomp,
                                     {payload, rng(), rng(), rng()}, rng(), "sub_3C4430", hw, with_blocks(static_cast<int>(rng() % 3), 0x30));
        ++pairs;
        const u32 block = static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]);
        REQUIRE(p.recomp->si.log.size() == 1);
        CHECK(p.recomp->si.log[0].extra == payload + 24);
        CHECK(p.recomp->heap.size_of(block) >= payload + 24);
        CHECK(get32(m, block + 8) == payload + 24);
        CHECK(get32(m, block + 20) == (payload != 0 ? block + 24 : 0u));
    }
    // sub_3C45F0(list): sub_3C4A90 releases the chained items (callback nmlist default 0x3C4400, memset, free), then the
    // list itself; and sub_3C4F30(buf).
    for (int i = 0; i < 300; ++i) {
        const bool list_case = (i & 1) == 0;
        const int items = static_cast<int>(rng() % 4);
        const bool null_arg = (rng() & 15) == 0;
        const WorldSetup setup = [items](StandInWorld& w) {
            install_standard(w);
            w.heap.alloc(0x40);                                   // the list / buffer
            for (int k = 0; k < items; ++k) w.heap.alloc(0x30);  // its items
        };
        // Guest bytes of the blocks (the same addresses in both worlds: the setup allocates in this order).
        const u32 list = kStandInHeap;
        for (u32 k = 0; k < 0x40; k += 4) put32(m, list + k, rng());
        put32(m, list + 24, 0x3C4400u);
        put32(m, list + 32, 0x40);
        put32(m, list + 8, 0x40);
        u32 head = 0;
        for (int k = items - 1; k >= 0; --k) {
            const u32 item = kStandInHeap + 0x40 + 0x30u * static_cast<u32>(k);
            for (u32 b = 0; b < 0x30; b += 4) put32(m, item + b, rng());
            put32(m, item + 8, 0x30);
            put32(m, item + 16, head);
            head = item;
        }
        put32(m, list + 4, head);
        const u32 arg = null_arg ? 0u : list;
        const SiPair p = list_case ? run_pair_si(m, rg::fn_sub_3C45F0_003c45f0, rg::fn_sub_3C45F0_003c45f0__recomp,
                                                 {arg, rng(), rng(), rng()}, rng(), "sub_3C45F0", hw, setup)
                                   : run_pair_si(m, rg::fn_sub_3C4F30_003c4f30, rg::fn_sub_3C4F30_003c4f30__recomp,
                                                 {arg, rng(), rng(), rng()}, rng(), "sub_3C4F30", hw, setup);
        ++pairs;
        const std::size_t live = static_cast<std::size_t>(1 + items);
        if (null_arg) CHECK(p.recomp->heap.live().size() == live);
        else CHECK(p.recomp->heap.live().size() == (list_case ? 0u : live - 1));
    }
    // Y_SMap_CreateStaireDispTask(parent): RwCalloc work, kwlnTaskCreate (H_Malloc'd record), the work's fields.
    for (int i = 0; i < 200; ++i) {
        const u32 parent = 0;
        const SiPair p = run_pair_si(m, rg::fn_Y_SMap_CreateStaireDispTask_00430180,
                                     rg::fn_Y_SMap_CreateStaireDispTask_00430180__recomp, {parent, rng(), rng(), rng()}, rng(),
                                     "Y_SMap_CreateStaireDispTask", hw, with_blocks(static_cast<int>(rng() % 3), 0x20));
        ++pairs;
        const StandIns& si = p.recomp->si;
        REQUIRE(si.calls_to(0x104040u) == 1);
        CHECK(si.calls_to(kHMalloc) == 1);
        const u32 work = static_cast<u32>(si.log[0].v0);
        CHECK(get32(m, work + 4) == 0x3F800000u);
        CHECK(get32(m, work) == 0u);
        CHECK(static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]) != 0u);  // the task
    }
    // sub_234710(src, size): a copy in a fresh block at work+44.
    for (int i = 0; i < 200; ++i) {
        const u32 src = kArena + 0x800, size = rng() % 0x200;
        for (u32 k = 0; k < 0x200; k += 4) put32(m, src + k, rng());
        const bool no_work = (rng() & 15) == 0;
        put_gp(m, -18916, no_work ? 0u : kWork);
        for (u32 k = 0; k < 64; k += 4) put32(m, kWork + k, rng());
        if (rng() & 7) put32(m, kWork + 4, get32(m, kWork + 4) & ~0x20u);
        const SiPair p = run_pair_si(m, rg::fn_sub_234710_00234710, rg::fn_sub_234710_00234710__recomp, {src, size, rng(), rng()},
                                     rng(), "sub_234710", hw, with_blocks(static_cast<int>(rng() % 3), 0x20));
        ++pairs;
        const u32 work = no_work ? 0u : kWork;
        const u32 copy = get32(m, work + 44);
        CHECK(copy == static_cast<u32>(p.recomp->si.log[0].v0));
        CHECK(std::memcmp(m.at(copy), m.at(src), size) == 0);
    }
    MESSAGE("heap users: " << pairs << " pairs");
}

TEST_CASE("game(standins_demo): the printf / sprintf users") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0x5D0004};
    int pairs = 0;
    // kwlnAdxErrorCallback(obj, message): printf(message) with what the caller left in $a2, $a3, $t0..
    for (int i = 0; i < 200; ++i) {
        const u32 msg = kArena + 0x200;
        const char* texts[] = {"E0120401: adxf read error", "ADX: %d / %d", "%s", "", "err %x (%c)"};
        m.put(msg, texts[rng() % 5]);
        m.put(kArena + 0x300, "file");
        const SiPair p = run_pair_si(m, rg::fn_kwlnAdxErrorCallback_00197fb0, rg::fn_kwlnAdxErrorCallback_00197fb0__recomp,
                                     {rng(), msg, kArena + 0x300, rng()}, rng(), "kwlnAdxErrorCallback", hw);
        ++pairs;
        REQUIRE(p.recomp->si.log.size() == 1);
        CHECK(p.recomp->si.log[0].args[0] == msg);
    }
    // sub_21B8B0(value): printf, work+8 = value, flags &= ~1.
    for (int i = 0; i < 200; ++i) {
        const bool no_work = (rng() & 15) == 0;
        put_gp(m, -18928, no_work ? 0u : kWork);
        for (u32 k = 0; k < 16; k += 4) put32(m, kWork + k, rng());
        const u32 value = rng();
        const SiPair p = run_pair_si(m, rg::fn_sub_21B8B0_0021b8b0, rg::fn_sub_21B8B0_0021b8b0__recomp, {value, rng(), rng(), rng()},
                                     rng(), "sub_21B8B0", hw);
        ++pairs;
        CHECK(get32(m, (no_work ? 0u : kWork) + 8) == value);
        CHECK(p.recomp->si.calls_to(kPrintf) == 1);
    }
    // sub_1FBCA0(level): the rows at gp-18600 (random [lo, hi) bytes, a zero row at the end).
    for (int i = 0; i < 300; ++i) {
        const u32 table = kArena + 0x400;
        const int rows = static_cast<int>(rng() % 12);
        for (int k = 0; k < rows; ++k) {
            u8 lo = static_cast<u8>(rng() % 100), hi = static_cast<u8>(rng() % 100);
            u16 x = static_cast<u16>(rng());
            if ((rng() & 3) == 0) lo = 0;
            if (lo == 0 && hi == 0 && x == 0) x = 1;
            m.at(table + 4u * static_cast<u32>(k))[0] = lo;
            m.at(table + 4u * static_cast<u32>(k))[1] = hi;
            std::memcpy(m.at(table + 4u * static_cast<u32>(k) + 2), &x, 2);
        }
        std::memset(m.at(table + 4u * static_cast<u32>(rows)), 0, 4);
        put_gp(m, -18600, table);
        const u32 level = (rng() & 1) ? rng() % 100 : rng();
        const SiPair p = run_pair_si(m, rg::fn_sub_1FBCA0_001fbca0, rg::fn_sub_1FBCA0_001fbca0__recomp, {level, rng(), rng(), rng()},
                                     rng(), "sub_1FBCA0", hw);
        ++pairs;
        int expect = 0;
        std::vector<std::string> texts;
        for (int k = 0; k < rows; ++k) {
            const int lo = m.at(table + 4u * static_cast<u32>(k))[0], hi = m.at(table + 4u * static_cast<u32>(k))[1];
            const int lv = static_cast<int>(level & 0xFFFFu);
            if (lo <= lv && lv < hi) {
                ++expect;
                texts.push_back(std::to_string(lo) + " <= " + std::to_string(lv) + " < " + std::to_string(hi) + "\n");
            }
        }
        CHECK(static_cast<int>(p.hw.recomp.gpr[GPR_V0].u64[0]) == expect);
        REQUIRE(p.recomp->si.log.size() == texts.size());
        for (std::size_t k = 0; k < texts.size(); ++k) CHECK(p.recomp->si.log[k].text == texts[k]);
    }
    // bpIfontDrawNumber(quads, max_digits, number, colour): half the pairs with the sprintf stand-in, half with the
    // recompiled sprintf (newlib's string path is emitted for test_stand_ins.cpp).
    for (int i = 0; i < 300; ++i) {
        const u32 quads = kArena + 0x100;
        const u32 number = (rng() & 1) ? rng() % 100000 : rng();
        const u32 max_digits = rng() % 12;
        const bool real_sprintf = (i & 1) != 0;
        // The font (bpIfontSetDigitQuad's a2 is a font index): sprFontGetFile's table 0x833A40[font] -> F; F+388 -> the
        // glyph rows (128 bytes per character, '0' - 11 first), each row's +20 selects F+260[+4 k] -> a texture header
        // (+12 width, +16 height).
        const u32 font = rng() % 4, F = kArena + 0x1C00, G = kArena + 0x1000, T = kArena + 0x1B00;
        put32(m, 0x833A40u + 4 * font, F);
        put32(m, F + 388, G);
        put32(m, F + 260, T);
        put32(m, T + 12, 16 + rng() % 64);
        put32(m, T + 16, 16 + rng() % 64);
        for (u32 row = 8; row <= 20; ++row) {
            for (u32 k = 0; k < 128; k += 4) put32(m, G + 128 * row + k, rng() % 256);
            put32(m, G + 128 * row + 20, 0);
        }
        const SiPair p = run_pair_si(m, rg::fn_bpIfontDrawNumber_00238980, rg::fn_bpIfontDrawNumber_00238980__recomp,
                                     {quads, max_digits, number, font}, rng(), "bpIfontDrawNumber", hw,
                                     [real_sprintf](StandInWorld& w) {
                                         w.heap.install_all(w.si);
                                         install_printf(w.si);
                                         if (!real_sprintf) install_sprintf(w.si);
                                     });
        ++pairs;
        if (!real_sprintf) {
            REQUIRE(p.recomp->si.log.size() == 1);
            CHECK(p.recomp->si.log[0].text == std::to_string(static_cast<s32>(number)));
        }
    }
    // sub_2449D0: printf, then sub_244770 on a battle-panel work whose lists are empty (gp-18896).
    for (int i = 0; i < 200; ++i) {
        put_gp(m, -18896, kWork);
        for (u32 k = 0; k < 64; k += 4) put32(m, kWork + k, rng());
        put32(m, kWork, get32(m, kWork) & ~2u);
        put32(m, kWork + 4, rng() % 5);
        put32(m, kWork + 8, 0);
        put32(m, kWork + 12, 0);
        const SiPair p = run_pair_si(m, rg::fn_sub_2449D0_002449d0, rg::fn_sub_2449D0_002449d0__recomp, {rng(), rng(), rng(), rng()},
                                     rng(), "sub_2449D0", hw);
        ++pairs;
        CHECK(p.recomp->si.calls_to(kPrintf) == 1);
        CHECK((get32(m, kWork) & 0x20u) == 0x20u);
    }
    // sub_1FA450: The Answer (the scenario word sub_17D800 reads) skips everything; else printf and sub_1FA4F0 x 8.
    for (int i = 0; i < 60; ++i) {
        random_scenario(m, rng);
        const SiPair p = run_pair_si(m, rg::fn_sub_1FA450_001fa450, rg::fn_sub_1FA450_001fa450__recomp, {rng(), rng(), rng(), rng()},
                                     rng(), "sub_1FA450", hw);
        ++pairs;
        CHECK(p.recomp->si.log.size() == (get32(m, kGp - 19788u) != 0 ? 0u : 1u));
        if (p.recomp->si.log.size() == 1) CHECK(p.recomp->si.log[0].text == "brfUpdateFriendEquip\n");
    }
    MESSAGE("printf / sprintf users: " << pairs << " pairs");
}

}  // namespace p3fes::game_test
