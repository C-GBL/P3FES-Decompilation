// Phase 5 pair tests for the second BMD message manager slice (game/src/msg/msg2.cpp): each hand-written
// function and the recompiled body it replaces run on identical guest machines (pair_harness.h: result,
// callee-saved registers, the arena holding handles / node lists / panel buffers, the caller's live stack,
// virtual cycles, check-point count), plus the low 1 KiB of RAM (where a null handle's fields land after
// the K_Assert that does not stop) and, where a function writes a fixed global, that region; the frame
// buffer of itfMesMngSwitchCurrentHandle (the 488-byte copy of the old handle on the guest stack) is compared too. Inputs
// are random with the edge cases forced (null handles, out-of-range indices, empty lists, division by
// zero, narrow panels, negative frame counters); the documented rules (msg2.h, docs/ANALYSIS/
// 18_script_vm.md section 5, 20_menu_ui.md section 4.3) are checked on the host, independently of both
// bodies, and on the real .BMD files of the disc when the extracted tree is beside the ELF.
#include "pair_harness.h"

#include "p3fes/formats/bmd.h"
#include "p3fes/game/bmd_msg.h"
#include "p3fes/game/msg2.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_itfMesMngGetBusy_003a2580)
P3FES_DECL_PAIR(fn_itfMesMngSetBusy_003a25f0)
P3FES_DECL_PAIR(fn_itfMesMngGetSelectWord84_003a2750)
P3FES_DECL_PAIR(fn_itfMesMngSetSelectWord84_003a27c0)
P3FES_DECL_PAIR(fn_itfMesMngGetSelection_003a2830)
P3FES_DECL_PAIR(fn_itfMesMngSwitchCurrentHandle_003a2c90)
P3FES_DECL_PAIR(fn_itfMesMngGetBmdMessageCount_003a3010)
P3FES_DECL_PAIR(fn_itfMesMngResetSelectionBySlot_003a3ab0)
P3FES_DECL_PAIR(fn_itfMesMngResetSelection_003a3b00)
P3FES_DECL_PAIR(fn_itfMesMngSetChoiceMask_003a3ba0)
P3FES_DECL_PAIR(fn_itfMesMngSetSelection_003a3c10)
P3FES_DECL_PAIR(fn_itfMesMngSetTextPosition_003a3ce0)
P3FES_DECL_PAIR(fn_itfMesMngGetState_003a3da0)
P3FES_DECL_PAIR(fn_itfMesMngSetStateFlags_003a3e10)
P3FES_DECL_PAIR(fn_itfMesMngClearStateFlags_003a3e90)
P3FES_DECL_PAIR(fn_itfMesMngGetSelection2_003a3f20)
P3FES_DECL_PAIR(fn_itfMesMngGetMessageArg_003a3f90)
P3FES_DECL_PAIR(fn_itfMesMngGetMessageType_003a5120)
P3FES_DECL_PAIR(fn_itfMesMngGetMessageCount_003a51a0)
P3FES_DECL_PAIR(fn_itfMesMngGetDialogueLine_003a5940)
P3FES_DECL_PAIR(fn_itfMesMngPushMessageArgs_003a5fd0)
P3FES_DECL_PAIR(fn_itfMesMngGetSpeakerName_003a6030)
P3FES_DECL_PAIR(fn_itfMesMngCountClearBits_003a6100)
P3FES_DECL_PAIR(fn_itfMesMngTextGetLastNode_003a6280)
P3FES_DECL_PAIR(fn_itfMesMngTextCopyNodeStyle_003a62b0)
P3FES_DECL_PAIR(fn_itfMesMngTextGetLineIndex_003a62e0)
P3FES_DECL_PAIR(fn_itfMesMngTextOffsetNodes_003a6310)
P3FES_DECL_PAIR(fn_itfMesMngTextSetNodesWord20_003a6350)
P3FES_DECL_PAIR(fn_itfMesMngTextSetLineAlpha_003a6380)
P3FES_DECL_PAIR(fn_itfMesMngTextSetGlyphColour_003a6410)
P3FES_DECL_PAIR(fn_itfMesMngTextGetMaxLineWidth_003a6460)
P3FES_DECL_PAIR(fn_itfMesMngTextResetNodes_003a64c0)
P3FES_DECL_PAIR(fn_itfMesMngInitSpeakerRecord_003a6900)
P3FES_DECL_PAIR(fn_itfMesMngInitTextRecord_003a6930)
P3FES_DECL_PAIR(fn_itfMesMngInitSelectRecord_003a6980)
P3FES_DECL_PAIR(fn_itfMesMngInitPanelRecord_003a69d0)
P3FES_DECL_PAIR(fn_itfMesMngClearMessageArgs_003a6a10)
P3FES_DECL_PAIR(fn_itfMesMngInitWindowRecord_003a6a40)
P3FES_DECL_PAIR(fn_itfMesMngSetWindowOffset_003a6a80)
P3FES_DECL_PAIR(fn_itfMesMngFormatNumber_003a6c10)
P3FES_DECL_PAIR(fn_itfPnlAnimClear10_003a9140)
P3FES_DECL_PAIR(fn_itfPnlAnimOpenType10_003a9170)
P3FES_DECL_PAIR(fn_itfPnlAnimCloseFade10_003a9230)
P3FES_DECL_PAIR(fn_itfPnlAnimClear11_003a92a0)
P3FES_DECL_PAIR(fn_itfPnlAnimOpenType11_003a92d0)
P3FES_DECL_PAIR(fn_itfPnlAnimCloseType11_003a93a0)
P3FES_DECL_PAIR(fn_itfPnlAnimOpenFade15_003a9400)
P3FES_DECL_PAIR(fn_itfPnlAnimCloseFade5_003a9470)
P3FES_DECL_PAIR(fn_itfPnlAnimClear13_003a94e0)
P3FES_DECL_PAIR(fn_itfPnlAnimOpenFade6_003a9510)
P3FES_DECL_PAIR(fn_itfPnlAnimCloseFade13_003a9580)
P3FES_DECL_PAIR(fn_itfPnlRunPhase0_003a95f0)
P3FES_DECL_PAIR(fn_itfPnlRunPhase1_003a9630)
P3FES_DECL_PAIR(fn_itfPnlRunPhase2_003a9670)
P3FES_DECL_PAIR(fn_itfPnlRunPhase3_003a96b0)
P3FES_DECL_PAIR(fn_itfPnlSetVertexType0_003a96f0)
P3FES_DECL_PAIR(fn_itfPnlSetVertexType1_003a9780)
P3FES_DECL_PAIR(fn_itfPnlSetVertexType2_003a9930)
P3FES_DECL_PAIR(fn_itfPnlSetVertexType3_003a9ac0)
P3FES_DECL_PAIR(fn_itfPnlSetVertexType5_003a9af0)
P3FES_DECL_PAIR(fn_itfPnlSetVertexType8_003a9b80)
P3FES_DECL_PAIR(fn_itfPnlSetColorType0_003a9c00)
P3FES_DECL_PAIR(fn_itfPnlSetColorType1_003a9c30)
P3FES_DECL_PAIR(fn_itfPnlSetColorType2_003a9c90)
P3FES_DECL_PAIR(fn_itfPnlSetColorType3_003a9cf0)
P3FES_DECL_PAIR(fn_itfPnlSetColorType4_003a9d90)
P3FES_DECL_PAIR(fn_itfPnlSetColorType5_003a9db0)
P3FES_DECL_PAIR(fn_itfPnlSetColorType8_003a9de0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// Arena layout (kArena .. kArena + 0x2000).
constexpr u32 kHandle = kArena + 0x0000;   // a 488-byte message handle (reads reach +482)
constexpr u32 kHandle2 = kArena + 0x0200;  // a second handle (itfMesMngSwitchCurrentHandle)
constexpr u32 kNodes = kArena + 0x0400;    // text line nodes, 0x48 apart (frFontLineResetAlpha writes +64)
constexpr u32 kNodeStride = 0x48;
constexpr u32 kMaxNodes = 12;
constexpr u32 kGlyphs = kArena + 0x0800;   // glyph records, 0x30 apart
constexpr u32 kGlyphStride = 0x30;
constexpr u32 kMaxGlyphs = 20;
constexpr u32 kBmd = kArena + 0x0C00;      // a synthetic BMD header + entries + speaker block
constexpr u32 kMisc = kArena + 0x1000;     // style records, dialogue records, speaker tables
constexpr u32 kBuf = kArena + 0x1400;      // panel buffers (up to +448), digit strings
constexpr u32 kSlot = kArena + 0x1C00;     // a 52-byte manager slot (itfMesMngSwitchCurrentHandle)
constexpr u32 kPanel = kArena + 0x1D00;    // an 80-byte itfPnl
constexpr u32 kWork = kArena + 0x1D80;     // its 16-byte animation work record
constexpr u32 kLow = 0x400;                // RAM [0, kLow): where a null handle's fields land
constexpr u32 kRealBmd = 0x01900000u;      // a real BMD of the disc, outside the arena (read-only here)

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 load16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) {  // inclusive
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}
u64 sxs(s32 v) { return sx(static_cast<u32>(v)); }

// The pair with the arena, RAM [0, kLow) and the extra regions restored between the runs and compared
// afterwards (the harness itself compares only the arena).
struct Region {
    u32 va;
    u32 len;
};
Pair pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::initializer_list<Region> extra = {}) {
    std::vector<Region> regions{{kArena, kArenaSize}, {0, kLow}};
    regions.insert(regions.end(), extra.begin(), extra.end());
    std::vector<std::vector<u8>> before, after_hand;
    for (const Region& r : regions) before.push_back(m.bytes(r.va, r.len));
    Pair p;
    p.hand = run(m, hand, args, seed);
    for (const Region& r : regions) after_hand.push_back(m.bytes(r.va, r.len));
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    p.recomp = run(m, recomp, args, seed);
    expect_same(p.hand, p.recomp, what);
    INFO(what);
    for (std::size_t i = 0; i < regions.size(); ++i) CHECK(after_hand[i] == m.bytes(regions[i].va, regions[i].len));
    return p;
}

// $t0, the fifth argument of the itfPnl table functions (the harness sets $a0..$a3 only).
u32 g_t0 = 0;
template <void (*F)(EEContext&)>
void with_t0(EEContext& c) {
    c.gpr[8].u64[0] = sx(g_t0);
    F(c);
}
#define PAIR_T0(name) &with_t0<&recomp_gen::name>, &with_t0<&recomp_gen::name##__recomp>

u32 slot_word(u32 slot) { return game::kItfMesSlotCurrentHandle + slot * game::kItfMesSlotStride; }

// --- text line-node lists ---------------------------------------------------------------------------

struct NodeList {
    u32 head = 0;
    std::vector<u32> nodes;
    std::vector<std::vector<u32>> glyphs;  // per node
};

// n nodes (n >= 1 unless empty_ok), grouped into lines (consecutive nodes share y; a new line every 1-in-3
// nodes), each with 0..3 glyph records (kMaxGlyphs in all); random bytes everywhere else.
NodeList make_nodes(Machine& m, std::mt19937& rng, u32 n) {
    NodeList l;
    u32 glyph = 0;
    s32 y = rand_range(rng, -4000, 4000);
    for (u32 i = 0; i < n; ++i) {
        const u32 node = kNodes + i * kNodeStride;
        l.nodes.push_back(node);
        if (i > 0 && rng() % 3 == 0) y += rand_range(rng, 1, 600) * (rng() % 4 == 0 ? -1 : 1);
        store32(m, node + 8, static_cast<u32>(y));
        store32(m, node + 4, static_cast<u32>(rand_range(rng, -4000, 4000)));
        store32(m, node + 12, rng() % 5 == 0 ? rng() : static_cast<u32>(rand_range(rng, 0, 400)));
        store32(m, node + 32, kMisc + 32 * (rng() % 8));
        std::vector<u32> gl;
        const u32 count = std::min<u32>(rng() % 4, kMaxGlyphs - glyph);
        for (u32 k = 0; k < count; ++k) gl.push_back(kGlyphs + (glyph++) * kGlyphStride);
        for (std::size_t k = 0; k < gl.size(); ++k) store32(m, gl[k] + 40, k + 1 < gl.size() ? gl[k + 1] : 0);
        store32(m, node + 28, gl.empty() ? 0 : gl.front());
        l.glyphs.push_back(gl);
    }
    for (std::size_t i = 0; i < l.nodes.size(); ++i) store32(m, l.nodes[i] + 36, i + 1 < l.nodes.size() ? l.nodes[i + 1] : 0);
    l.head = l.nodes.empty() ? 0 : l.nodes.front();
    return l;
}

std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

}  // namespace

TEST_CASE("game(msg2): the fixed addresses and record sizes are what the doc says") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    CHECK(game::kItfMesSlotCurrentHandle == game::kItfMesSlotArray + 12);
    CHECK(m.str(0x6A1A70u) == "itfMesManager.c");  // the K_Assert file argument of every accessor
    // The vertex step table of itfPnl type 1 and the colour factor tables are .rodata of the ELF.
    CHECK(load32(m, game::kItfPnlVertexStepTable + 0) == 0);
    CHECK(load32(m, game::kItfPnlVertexStepTable + 4) == 8);
    CHECK(load32(m, game::kItfPnlVertexStepTable + 8) == 48);
    CHECK(sizeof(game::ItfMesHandle) == game::kItfMesHandleSize);
}

TEST_CASE("game(msg2): the per-slot handle accessors equal their recompiled bodies (null handles included)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A258000u};
    int nulls = 0, moved = 0;
    for (int it = 0; it < 800; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const u32 slot = rng() % 8;
        const bool null = it % 8 == 7;
        nulls += null ? 1 : 0;
        const u32 h = null ? 0 : kHandle;
        store32(m, slot_word(slot), h);
        const u32 count = rng() % 16;
        store32(m, kBmd + 24, count);
        store32(m, kHandle + 4, kBmd);
        const u64 s = slot;
        const u32 seed = rng();

        Pair p = pair(m, PAIR(fn_itfMesMngGetBusy_003a2580), {s}, seed, "itfMesMngGetBusy (busy byte)");
        CHECK(p.hand.v0 == sxs(static_cast<s8>(m.at(h + 52)[0])));
        const u32 byte = rng();
        pair(m, PAIR(fn_itfMesMngSetBusy_003a25f0), {s, sx(byte)}, seed, "itfMesMngSetBusy");
        CHECK(m.at(h + 52)[0] == static_cast<u8>(byte));
        p = pair(m, PAIR(fn_itfMesMngGetSelectWord84_003a2750), {s}, seed, "itfMesMngGetSelectWord84");
        CHECK(p.hand.v0 == sxs(static_cast<s16>(load16(m, h + 84))));
        const u32 half = rng();
        pair(m, PAIR(fn_itfMesMngSetSelectWord84_003a27c0), {s, sx(half)}, seed, "itfMesMngSetSelectWord84");
        CHECK(load16(m, h + 84) == static_cast<u16>(half));
        p = pair(m, PAIR(fn_itfMesMngGetSelection_003a2830), {s}, seed, "itfMesMngGetSelection");
        CHECK(p.hand.v0 == sxs(static_cast<s16>(load16(m, h + 86))));
        p = pair(m, PAIR(fn_itfMesMngGetSelection2_003a3f20), {s}, seed, "itfMesMngGetSelection2");
        CHECK(p.hand.v0 == sxs(static_cast<s16>(load16(m, h + 86))));
        p = pair(m, PAIR(fn_itfMesMngGetState_003a3da0), {s}, seed, "itfMesMngGetState");
        CHECK(p.hand.v0 == sx(load32(m, h)));
        const u32 state = load32(m, h), set = rng(), clr = rng();
        pair(m, PAIR(fn_itfMesMngSetStateFlags_003a3e10), {s, sx(set)}, seed, "itfMesMngSetStateFlags");
        CHECK(load32(m, h) == (state | (set & 0xFFFF0000u)));
        pair(m, PAIR(fn_itfMesMngClearStateFlags_003a3e90), {s, sx(clr)}, seed, "itfMesMngClearStateFlags");
        CHECK(load32(m, h) == ((state | (set & 0xFFFF0000u)) & ~(clr & 0xFFFF0000u)));
        const s32 arg = rand_range(rng, -4, 40);
        p = pair(m, PAIR(fn_itfMesMngGetMessageArg_003a3f90), {s, sxs(arg)}, seed, "itfMesMngGetMessageArg");
        CHECK(p.hand.v0 == sx(load32(m, h + 212 + 4 * static_cast<u32>(arg))));
        const s32 index = rand_range(rng, 0, 15);
        p = pair(m, PAIR(fn_itfMesMngGetMessageType_003a5120), {s, sxs(index)}, seed, "itfMesMngGetMessageType");
        if (!null) CHECK(p.hand.v0 == sx(load32(m, kBmd + 32 + 8 * static_cast<u32>(index))));
        p = pair(m, PAIR(fn_itfMesMngGetMessageCount_003a51a0), {s}, seed, "itfMesMngGetMessageCount");
        if (!null) CHECK(p.hand.v0 == count);
        const u32 a = rng(), b = rng();
        pair(m, PAIR(fn_itfMesMngSetWindowOffset_003a6a80), {s, sx(a), sx(b)}, seed, "itfMesMngSetWindowOffset");
        CHECK(load16(m, h + 480) == static_cast<u16>(a));
        CHECK(load16(m, h + 482) == static_cast<u16>(b));
        const u32 mask = rng();
        pair(m, PAIR(fn_itfMesMngSetChoiceMask_003a3ba0), {s, sx(mask)}, seed, "itfMesMngSetChoiceMask");
        CHECK(load32(m, h + 80) == mask);

        // itfMesMngSetTextPosition: the text list at +48 moves by the delta; both coordinates kept when nothing moves.
        const NodeList l = make_nodes(m, rng, rng() % 6);
        if (!null) store32(m, kHandle + 48, l.head);
        const s32 cx = static_cast<s32>(load32(m, h + 36)), cy = static_cast<s32>(load32(m, h + 40));
        s32 x = rand_range(rng, -5000, 5000), y = rand_range(rng, -5000, 5000);
        switch (it % 4) {
            case 0: x = cx; y = cy; break;
            case 1: x = cx; break;
            case 2: y = cy; break;
            default: break;
        }
        std::vector<u32> xs;
        for (u32 n : l.nodes) xs.push_back(load32(m, n + 4));
        pair(m, PAIR(fn_itfMesMngSetTextPosition_003a3ce0), {s, sxs(x), sxs(y)}, seed, "itfMesMngSetTextPosition");
        CHECK(static_cast<s32>(load32(m, h + 36)) == x);
        CHECK(static_cast<s32>(load32(m, h + 40)) == y);
        if (!null) {
            for (std::size_t i = 0; i < l.nodes.size(); ++i)
                CHECK(load32(m, l.nodes[i] + 4) == xs[i] + (static_cast<u32>(x) - static_cast<u32>(cx)));
            moved += (x != cx || y != cy) && !l.nodes.empty() ? 1 : 0;
        }
    }
    CHECK(nulls == 100);
    CHECK(moved > 100);
}

TEST_CASE("game(msg2): itfMesMngSetSelection (option -> enabled index) equals its recompiled body and the bit rule") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A3C1000u};
    const u32 special[] = {0u, 0xFFFFFFFFu, 0x10000u, 0xFFFEFFFFu, 0x1FFFFu, 1u, 0x8000u, 0xFFFF0000u};
    for (int it = 0; it < 600; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const u32 slot = rng() % 8;
        const bool null = it % 10 == 9;
        const u32 h = null ? 0 : kHandle;
        store32(m, slot_word(slot), h);
        const u32 mask = it < 8 ? special[it] : (it % 3 == 0 ? rng() & 0x1FFFFu : rng());
        store32(m, h + 80, mask);
        // The option (the loop bound, $a1 compared as 64 bits): small counts, negatives, a wide negative.
        const s64 option = it % 50 == 0 ? -static_cast<s64>(rng()) * 4096 : rand_range(rng, -3, 33);
        pair(m, PAIR(fn_itfMesMngSetSelection_003a3c10), {slot, static_cast<u64>(option)}, rng(), "itfMesMngSetSelection");
        // Host rule: count the clear bits among bits 0..max(option, 0); 0 when that last bit is set, else
        // count - 1 (bits past 31 read as 0: the mask is shifted right logically).
        const s64 last = std::max<s64>(option, 0);
        int clear = 0;
        for (s64 b = 0; b <= last; ++b) clear += (b < 32 && ((mask >> b) & 1u)) ? 0 : 1;
        const bool last_set = last < 32 && ((mask >> last) & 1u);
        const u16 want = last_set ? 0 : static_cast<u16>(clear - 1);
        CHECK(load16(m, h + 86) == want);
        CHECK(load16(m, h + 88) == want);
    }
}

TEST_CASE("game(msg2): itfMesMngSwitchCurrentHandle (switch the current handle) equals its recompiled body, guest frame included") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A2C9000u};
    int switched = 0, saved = 0;
    for (int it = 0; it < 600; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const s32 i = it % 10 == 0 ? rand_range(rng, -2, 5) : rand_range(rng, 0, 3);
        const bool empty = rng() % 5 == 0;
        const bool no_current = rng() % 4 == 0;
        // Every word of the slot (and the words an out-of-range index reaches, slot - 0 .. slot + 64) is
        // null or kHandle2; then the chosen entry and the current handle (+12) are set.
        for (u32 k = 0; k < 17; ++k) store32(m, kSlot + 4 * k, rng() % 3 == 0 ? 0 : kHandle2);
        if (i >= 0 && i < 4) store32(m, kSlot + 20 + 8 * static_cast<u32>(i), empty ? 0 : kHandle2);
        store32(m, kSlot + 12, no_current ? 0 : kHandle);
        const std::vector<u8> old = m.bytes(kHandle, game::kItfMesHandleSize);
        const u32 entry = load32(m, kSlot + 20 + 8 * static_cast<u32>(i));
        const u64 ireg = it % 25 == 0 ? (u64{1 + rng() % 3} << 32) | static_cast<u32>(i) : sxs(i);
        const Pair p = pair(m, PAIR(fn_itfMesMngSwitchCurrentHandle_003a2c90), {kSlot, ireg}, rng(), "itfMesMngSwitchCurrentHandle");
        if (entry == 0) {
            CHECK(p.hand.v0 == 0);
            continue;
        }
        ++switched;
        CHECK(p.hand.v0 == sx(kSlot + 20 + 8 * static_cast<u32>(i)));
        CHECK(load32(m, kSlot + 12) == entry);
        CHECK(load32(m, kSlot + 16) == entry);
        if (!no_current) {
            ++saved;
            CHECK(same_frame_bytes(p, 560, 64, game::kItfMesHandleSize));  // the copy of the old handle
            u32 old_state;
            std::memcpy(&old_state, old.data(), 4);
            CHECK(load32(m, entry) == old_state);
            CHECK(std::memcmp(m.at(entry + 168), old.data() + 168, 44) == 0);
        }
    }
    CHECK(switched > 300);
    CHECK(saved > 200);
}

TEST_CASE("game(msg2): itfMesMngResetSelection / itfMesMngResetSelectionBySlot (selection reset) equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A3B0000u};
    int released = 0;
    for (int it = 0; it < 500; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const bool null = it % 10 == 9;
        const u32 h = null ? 0 : kHandle;
        // A selection node list whose release stays inside frFontLineFadeStep (a glyph mid-fade: kind 2 with a
        // non-zero colour low byte), so sub_3B0170 returns without freeing; or no node at all.
        u32 node = 0;
        if (!null && rng() % 3 != 0) {
            const NodeList l = make_nodes(m, rng, 1 + rng() % 4);
            const u32 g = kGlyphs + (kMaxGlyphs - 1) * kGlyphStride;
            store32(m, g + 40, l.glyphs[0].empty() ? 0 : l.glyphs[0].front());
            store32(m, l.nodes[0] + 28, g);
            m.at(g + 22)[0] = 2;
            store32(m, g + 16, (rng() & ~0xFFu) | (1 + rng() % 255));
            node = l.head;
            ++released;
        }
        if (!null) store32(m, h + 76, node);
        const u32 state = load32(m, h);
        const u32 seed = rng();
        if (it & 1) {
            pair(m, PAIR(fn_itfMesMngResetSelection_003a3b00), {sx(h)}, seed, "itfMesMngResetSelection");
        } else {
            const u32 slot = rng() % 8;
            store32(m, slot_word(slot), h);
            pair(m, PAIR(fn_itfMesMngResetSelectionBySlot_003a3ab0), {slot}, seed, "itfMesMngResetSelectionBySlot");
        }
        CHECK(load32(m, h + 76) == 0);
        CHECK(load16(m, h + 84) == 0);
        CHECK(load16(m, h + 90) == 0);
        CHECK(load16(m, h + 86) == 0xFFFF);
        CHECK(load32(m, h + 80) == 0);
        CHECK(load32(m, h) == (state & ~0x40038u));
    }
    CHECK(released > 200);
}

TEST_CASE("game(msg2): itfMesMngGetBmdMessageCount, itfMesMngGetDialogueLine, itfMesMngGetSpeakerName, itfMesMngCountClearBits equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A301000u};
    for (int it = 0; it < 1500; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const u32 seed = rng();
        // itfMesMngGetBmdMessageCount: K_Assert(magic) then the count, whatever the magic.
        const u32 magic = it % 3 == 0 ? game::bmd::kMagicMsg0 : it % 3 == 1 ? game::bmd::kMagicMsg1 : rng();
        store32(m, kBmd + 8, magic);
        Pair p = pair(m, PAIR(fn_itfMesMngGetBmdMessageCount_003a3010), {kBmd}, seed, "itfMesMngGetBmdMessageCount");
        CHECK(p.hand.v0 == sx(load32(m, kBmd + 24)));

        // itfMesMngGetDialogueLine: line i of a dialogue record (s16 count at +24).
        const u32 rec = kMisc + 4 * (rng() % 32);
        const s16 count = it % 7 == 0 ? static_cast<s16>(rng()) : static_cast<s16>(rng() % 12);
        store16(m, rec + 24, static_cast<u16>(count));
        const s32 line = it % 5 == 0 ? static_cast<s32>(rng()) : rand_range(rng, -3, 14);
        // an occasional index with high bits set: the range test compares the whole register
        const u64 lreg = it % 13 == 0 ? (u64{1 + rng() % 3} << 32) | static_cast<u32>(line) : sxs(line);
        p = pair(m, PAIR(fn_itfMesMngGetDialogueLine_003a5940), {rec, lreg}, seed, "itfMesMngGetDialogueLine");
        const bool in = lreg == sxs(line) && line >= 0 && line < count;
        CHECK(p.hand.v0 == (in ? sx(load32(m, rec + 28 + 4 * static_cast<u32>(line))) : 0));

        // itfMesMngGetSpeakerName: speaker name pointer through the bound BMD's speaker table.
        const u32 msgs = rng() % 24;
        store32(m, kBmd + 24, msgs);
        const u32 table = kMisc + 0x200 + 4 * (rng() % 16);
        store32(m, kBmd + 32 + 8 * msgs, table);
        store32(m, kHandle + 4, kBmd);
        const u16 who = static_cast<u16>(rng() % 32);
        store16(m, kHandle + 32, who);
        p = pair(m, PAIR(fn_itfMesMngGetSpeakerName_003a6030), {kHandle}, seed, "itfMesMngGetSpeakerName");
        CHECK(p.hand.v0 == sx(load32(m, table + 4u * who)));

        // itfMesMngCountClearBits: clear bits among the low n bits.
        // (a large positive n would run 2^31 guest iterations: real callers pass an option count)
        const s32 n = it % 9 == 0 ? -static_cast<s32>(rng() >> 1) : rand_range(rng, -3, 40);
        const u32 mask = rng();
        // an occasional count with high bits set: the first test sees the whole register, then `addiu`
        // leaves the sign-extended low word minus one
        const bool wide = it % 11 == 0 && n > 0;
        const u64 nreg = wide ? (u64{1 + rng() % 3} << 32) | static_cast<u32>(n) : sxs(n);
        p = pair(m, PAIR(fn_itfMesMngCountClearBits_003a6100), {nreg, sx(mask)}, seed, "itfMesMngCountClearBits");
        s32 clear = 0;
        u32 mm = mask;
        for (s32 k = n; k > 0; --k, mm >>= 1) clear += (mm & 1u) ? 0 : 1;
        CHECK(p.hand.v0 == sxs(clear));
    }
}

TEST_CASE("game(msg2): itfMesMngPushMessageArgs hands the 32 argument words to the font table") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A5FD000u};
    for (int it = 0; it < 100; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        fill_random(m, game::kFrMessageArgTable, 128, rng);
        const u32 table = kBuf + 4 * (rng() % 64);
        const Pair p = pair(m, PAIR(fn_itfMesMngPushMessageArgs_003a5fd0), {table}, rng(), "itfMesMngPushMessageArgs", {{game::kFrMessageArgTable, 128}});
        CHECK(p.hand.v0 == sx(table + 124));
        CHECK(m.bytes(game::kFrMessageArgTable, 128) == m.bytes(table, 128));
    }
}

TEST_CASE("game(msg2): the handle sub-record initialisers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A690000u};
    for (int it = 0; it < 400; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        const u32 rec = kBuf + 4 * (rng() % 64);
        // 0, 1, random, and a value whose low word is zero (the bodies test the whole register)
        const u64 flag = it % 4 == 0 ? 0 : it % 4 == 1 ? 1 : it % 4 == 2 ? sx(rng()) : u64{1 + rng() % 7} << 32;
        const u32 seed = rng();
        const s32 x0 = static_cast<s32>(load32(m, rec)), y0 = static_cast<s32>(load32(m, rec + 4));
        pair(m, PAIR(fn_itfMesMngInitSpeakerRecord_003a6900), {rec, flag}, seed, "itfMesMngInitSpeakerRecord");
        CHECK(static_cast<s32>(load32(m, rec)) == (flag ? 656 : x0));
        CHECK(static_cast<s32>(load32(m, rec + 4)) == (flag ? 2632 : y0));
        CHECK(load32(m, rec + 8) == 0);
        CHECK(load16(m, rec + 12) == 0xFFFF);
        pair(m, PAIR(fn_itfMesMngInitTextRecord_003a6930), {rec, flag}, seed, "itfMesMngInitTextRecord");
        if (flag) CHECK(load32(m, rec) == 864);
        CHECK(m.at(rec + 21)[0] == 255);
        CHECK(m.at(rec + 16)[0] == 0);
        pair(m, PAIR(fn_itfMesMngInitSelectRecord_003a6980), {rec}, seed, "itfMesMngInitSelectRecord");
        CHECK(load32(m, rec) == 3824);
        CHECK(load32(m, rec + 4) == 3904);
        CHECK(load16(m, rec + 22) == 0xFFFF);
        CHECK(load16(m, rec + 24) == 0xFFFF);
        pair(m, PAIR(fn_itfMesMngInitPanelRecord_003a69d0), {rec}, seed, "itfMesMngInitPanelRecord");
        CHECK(load32(m, rec) == 0);
        CHECK(load32(m, rec + 4) == 0);
        CHECK(load32(m, rec + 8) == 0);
        pair(m, PAIR(fn_itfMesMngClearMessageArgs_003a6a10), {rec}, seed, "itfMesMngClearMessageArgs");
        CHECK(m.bytes(rec, 128) == std::vector<u8>(128, 0));
        fill_random(m, rec, 16, rng);
        const u8 b0 = m.at(rec)[0];
        pair(m, PAIR(fn_itfMesMngInitWindowRecord_003a6a40), {rec, flag}, seed, "itfMesMngInitWindowRecord");
        CHECK(m.at(rec)[0] == (flag ? b0 : 0));
        CHECK(load16(m, rec + 12) == 568);
        CHECK(load16(m, rec + 14) == 395);
    }
}

TEST_CASE("game(msg2): itfMesMngFormatNumber (decimal glyph string) equals its recompiled body and the digit rule") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A6C1000u};
    const s32 special[] = {0, 1, 9, 10, 99, 100, 2147483647, -1, -10, static_cast<s32>(0x80000000u), 1000000000, 999999999};
    for (int it = 0; it < 800; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        s32 n;
        if (it < 12) n = special[it];
        else if (it % 3 == 0) n = static_cast<s32>(rng());
        else n = static_cast<s32>(rng() % (1u + (1u << (rng() % 31))));
        const u32 out = kBuf + 2 * (rng() % 64);
        const Pair p = pair(m, PAIR(fn_itfMesMngFormatNumber_003a6c10), {sxs(n), out}, rng(), "itfMesMngFormatNumber");
        if (n >= 0) {
            const std::string digits = std::to_string(n);
            CHECK(p.hand.v0 == sx(out + 2 * static_cast<u32>(digits.size())));
            for (std::size_t k = 0; k < digits.size(); ++k)
                CHECK(load16(m, out + 2 * static_cast<u32>(k)) == static_cast<u16>(((digits[k] - '0' + 16) << 8) + 0x8080));
            CHECK(load16(m, out + 2 * static_cast<u32>(digits.size())) == 0);
        }
    }
}

TEST_CASE("game(msg2): the text line-node helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A628000u};
    int div0 = 0;
    for (int it = 0; it < 1200; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const u32 n = 1 + rng() % kMaxNodes;
        const NodeList l = make_nodes(m, rng, n);
        const u32 seed = rng();
        Pair p = pair(m, PAIR(fn_itfMesMngTextGetLastNode_003a6280), {l.head}, seed, "itfMesMngTextGetLastNode");
        CHECK(p.hand.v0 == sx(l.nodes.back()));

        const u32 dst = kBuf + 4 * (rng() % 32);
        pair(m, PAIR(fn_itfMesMngTextCopyNodeStyle_003a62b0), {l.nodes[0], dst}, seed, "itfMesMngTextCopyNodeStyle");
        const u32 style = load32(m, l.nodes[0] + 32);
        CHECK(m.at(dst + 21)[0] == (m.at(l.nodes[0] + 2)[0] >> 1));
        CHECK(m.at(dst + 18)[0] == m.at(style + 21)[0]);

        const u32 b = l.nodes[rng() % n];
        if (it % 6 == 0) {
            store16(m, b + 18, 0);
            ++div0;
        } else if (it % 6 == 1) {
            store16(m, b + 18, 0xFFFF);
        }
        p = pair(m, PAIR(fn_itfMesMngTextGetLineIndex_003a62e0), {l.nodes[0], b}, seed, "itfMesMngTextGetLineIndex");
        const s16 height = static_cast<s16>(load16(m, b + 18));
        if (height != 0) {
            const s32 rows = static_cast<s32>(load32(m, b + 8) - load32(m, l.nodes[0] + 8)) >> 3;
            CHECK(p.hand.v0 == sxs(rows / height + 1));
        }

        std::vector<u32> xs, ys;
        for (u32 node : l.nodes) xs.push_back(load32(m, node + 4)), ys.push_back(load32(m, node + 8));
        const u32 dx = rng() % 4 == 0 ? 0 : rng(), dy = rng();
        pair(m, PAIR(fn_itfMesMngTextOffsetNodes_003a6310), {l.head, sx(dx), sx(dy)}, seed, "itfMesMngTextOffsetNodes");
        for (std::size_t i = 0; i < n; ++i) {
            CHECK(load32(m, l.nodes[i] + 4) == xs[i] + dx);
            CHECK(load32(m, l.nodes[i] + 8) == ys[i] + dy);
        }
        const u32 word = rng();
        pair(m, PAIR(fn_itfMesMngTextSetNodesWord20_003a6350), {l.head, sx(word)}, seed, "itfMesMngTextSetNodesWord20");
        for (u32 node : l.nodes) CHECK(load32(m, node + 20) == word);

        const s32 first = rand_range(rng, -2, 6), last = rand_range(rng, -2, 8);
        pair(m, PAIR(fn_itfMesMngTextSetLineAlpha_003a6380), {l.head, sxs(first), sxs(last), sx(rng())}, seed, "itfMesMngTextSetLineAlpha");
        const u32 colour = rng();
        pair(m, PAIR(fn_itfMesMngTextSetGlyphColour_003a6410), {l.head, sx(colour)}, seed, "itfMesMngTextSetGlyphColour");
        for (const std::vector<u32>& gl : l.glyphs)
            for (u32 g : gl) CHECK((load32(m, g + 16) & 0xFFu) == (colour & 0xFFu));
        p = pair(m, PAIR(fn_itfMesMngTextGetMaxLineWidth_003a6460), {l.head}, seed, "itfMesMngTextGetMaxLineWidth");
        s32 widest = 0;
        for (std::size_t i = 0; i < n;) {
            u32 sum = 0;
            std::size_t j = i;
            do sum += load32(m, l.nodes[j++] + 12);
            while (j < n && load32(m, l.nodes[j] + 8) == load32(m, l.nodes[i] + 8));
            widest = std::max(widest, static_cast<s32>(sum));
            i = j;
        }
        CHECK(p.hand.v0 == sx(static_cast<u32>(widest) << 4));

        // itfMesMngTextResetNodes: nodes whose first glyph has a zero +22 byte are reset by frFontLineResetAlpha (glyph-less
        // nodes read the low RAM, zero, and are reset too).
        for (const std::vector<u32>& gl : l.glyphs)
            if (!gl.empty() && rng() % 2) m.at(gl.front() + 22)[0] = 0;
        pair(m, PAIR(fn_itfMesMngTextResetNodes_003a64c0), {l.head}, seed, "itfMesMngTextResetNodes");
    }
    CHECK(div0 == 200);
}

TEST_CASE("game(msg2): the itfPnl vertex tables equal their recompiled bodies and the layout rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A96F000u};
    int narrow = 0;
    for (int it = 0; it < 800; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        const u32 buf = kBuf + 4 * (rng() % 32);
        s32 x0 = rand_range(rng, -2000, 6000), y0 = rand_range(rng, -2000, 6000);
        s32 x1 = x0 + rand_range(rng, it % 4 == 0 ? -200 : 0, it % 4 == 0 ? 1100 : 7000);
        s32 y1 = y0 + rand_range(rng, -200, 4000);
        if (it % 13 == 0) x0 = static_cast<s32>(rng()), y0 = static_cast<s32>(rng()), x1 = static_cast<s32>(rng()), y1 = static_cast<s32>(rng());
        g_t0 = static_cast<u32>(y1);
        const Args a{buf, sxs(x0), sxs(y0), sxs(x1)};
        const u32 seed = rng();
        pair(m, PAIR_T0(fn_itfPnlSetVertexType0_003a96f0), a, seed, "itfPnlSetVertexType0");
        if (it % 13 != 0) {
            const bool is_narrow = x1 - 512 < x0 + 512;
            narrow += is_narrow ? 1 : 0;
            const s32 mid = x0 + ((x1 - x0) >> 1);
            const s32 cols[4] = {x0, is_narrow ? mid : x0 + 512, is_narrow ? mid : x1 - 512, x1};
            for (u32 c = 0; c < 4; ++c) {
                CHECK(static_cast<s32>(load32(m, buf + 16 * c)) == cols[c]);
                CHECK(static_cast<s32>(load32(m, buf + 16 * c + 4)) == y0);
                CHECK(static_cast<s32>(load32(m, buf + 16 * c + 12)) == y1);
            }
        }
        pair(m, PAIR_T0(fn_itfPnlSetVertexType1_003a9780), a, seed, "itfPnlSetVertexType1");
        if (it % 13 != 0) {
            CHECK(static_cast<s32>(load32(m, buf + 128 + 4)) == y0);            // row 0 of the edge rows
            CHECK(static_cast<s32>(load32(m, buf + 128 + 32 + 4)) == y0 + 8);   // row 1
            CHECK(static_cast<s32>(load32(m, buf + 128 + 64 + 4)) == y0 + 48);  // row 2
            CHECK(static_cast<s32>(load32(m, buf + 224 + 64 + 4)) == y1 - 48);
            CHECK(static_cast<s32>(load32(m, buf + 128 + 8)) == x0 + 1024);
        }
        pair(m, PAIR_T0(fn_itfPnlSetVertexType2_003a9930), a, seed, "itfPnlSetVertexType2");
        pair(m, PAIR_T0(fn_itfPnlSetVertexType3_003a9ac0), a, seed, "itfPnlSetVertexType3");
        {
            const s32 want[8] = {x0, y0, x1, y0, x1, y1, x0, y1};
            for (u32 k = 0; k < 8; ++k) CHECK(static_cast<s32>(load32(m, buf + 4 * k)) == want[k]);
        }
        pair(m, PAIR_T0(fn_itfPnlSetVertexType5_003a9af0), a, seed, "itfPnlSetVertexType5");
        pair(m, PAIR_T0(fn_itfPnlSetVertexType8_003a9b80), a, seed, "itfPnlSetVertexType8");
        if (it % 13 != 0) {
            CHECK(load32(m, buf + 4) == 416);
            CHECK(static_cast<s32>(load32(m, buf + 8)) == y0 + 352);
            CHECK(static_cast<s32>(load32(m, buf + 16)) == y1 - 320);
            CHECK(load32(m, buf + 4 + 48) == 7760);
        }
    }
    CHECK(narrow > 50);
}

TEST_CASE("game(msg2): the itfPnl colour tables equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A9C0000u};
    for (int it = 0; it < 600; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        const u32 buf = kBuf + 4 * (rng() % 32);
        const bool wide = it % 7 == 0;
        const u32 r = wide ? rng() : rng() % 256, g = wide ? rng() : rng() % 256, b = wide ? rng() : rng() % 256;
        g_t0 = wide ? rng() : rng() % 256;
        const Args a{buf, sx(r), sx(g), sx(b)};
        const u32 seed = rng();
        pair(m, PAIR_T0(fn_itfPnlSetColorType0_003a9c00), a, seed, "itfPnlSetColorType0");
        CHECK(load32(m, buf + 64) == r);
        CHECK(load32(m, buf + 76) == 0);
        CHECK(load32(m, buf + 92) == g_t0);
        Pair p = pair(m, PAIR_T0(fn_itfPnlSetColorType1_003a9c30), a, seed, "itfPnlSetColorType1");
        CHECK(p.hand.v0 == 1);
        CHECK(load32(m, buf + 332) == 1);
        p = pair(m, PAIR_T0(fn_itfPnlSetColorType2_003a9c90), a, seed, "itfPnlSetColorType2");
        CHECK(p.hand.v0 == 1);
        CHECK(load32(m, buf + 268) == 1);
        pair(m, PAIR_T0(fn_itfPnlSetColorType3_003a9cf0), a, seed, "itfPnlSetColorType3");
        CHECK(load32(m, buf + 44) == g_t0);
        CHECK(load32(m, buf + 64 + 12) == 128);  // the two lower shades carry alpha 128
        CHECK(load32(m, buf + 80 + 12) == 128);
        pair(m, PAIR_T0(fn_itfPnlSetColorType4_003a9d90), a, seed, "itfPnlSetColorType4");
        pair(m, PAIR_T0(fn_itfPnlSetColorType5_003a9db0), a, seed, "itfPnlSetColorType5");
        CHECK(load32(m, buf + 60) == 0);
        pair(m, PAIR_T0(fn_itfPnlSetColorType8_003a9de0), a, seed, "itfPnlSetColorType8");
        const u32 want[8] = {115, 135, 255, 0, 115, 135, 255, 0};
        for (u32 k = 0; k < 8; ++k) CHECK(load32(m, buf + 68 + 4 * k) == want[k]);
    }
}

namespace {
struct AnimFn {
    Fn hand;
    Fn recomp;
    const char* name;
};
#define ANIM(n) AnimFn{PAIR(n), #n}
const AnimFn kAnims[] = {
    ANIM(fn_itfPnlAnimClear10_003a9140), ANIM(fn_itfPnlAnimClear11_003a92a0), ANIM(fn_itfPnlAnimClear13_003a94e0), ANIM(fn_itfPnlAnimOpenType10_003a9170),
    ANIM(fn_itfPnlAnimCloseFade10_003a9230), ANIM(fn_itfPnlAnimCloseFade13_003a9580), ANIM(fn_itfPnlAnimOpenType11_003a92d0), ANIM(fn_itfPnlAnimCloseType11_003a93a0),
    ANIM(fn_itfPnlAnimOpenFade15_003a9400), ANIM(fn_itfPnlAnimCloseFade5_003a9470), ANIM(fn_itfPnlAnimOpenFade6_003a9510),
};
#undef ANIM

// Runs one phase function from a cleared work record until it reports done; returns the number of calls.
int frames_to_done(Machine& m, std::mt19937& rng, const AnimFn& f, u32 want_phase, u32 want_alpha) {
    std::memset(m.at(kWork), 0, 16);
    for (int k = 1; k <= 40; ++k) {
        const Pair p = pair(m, f.hand, f.recomp, {kPanel}, rng(), f.name);
        if (p.hand.v0 == 1) {
            CHECK(load32(m, kWork) == want_phase);
            CHECK(load32(m, kWork + 8) == 0);
            CHECK(load32(m, kWork + 12) == want_alpha);
            return k;
        }
        CHECK(p.hand.v0 == 0);
    }
    return -1;
}
}  // namespace

TEST_CASE("game(msg2): the itfPnl animation phases equal their recompiled bodies and their frame counts") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A914000u};
    for (int it = 0; it < 500; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        store32(m, kPanel + 8, kWork);
        const s32 counter = it % 9 == 0 ? static_cast<s32>(rng()) : rand_range(rng, -120, 20);
        for (const AnimFn& f : kAnims) {
            store32(m, kWork + 8, static_cast<u32>(counter));
            pair(m, f.hand, f.recomp, {kPanel}, rng(), f.name);
        }
    }
    // Documented frame counts from a cleared record (msg2.h): open 6 / 10 / 15 / 6, close 10 / 1 / 5 / 10.
    fill_random(m, kArena, kArenaSize, rng);
    store32(m, kPanel + 8, kWork);
    CHECK(frames_to_done(m, rng, kAnims[3], 2, 255) == 6);    // itfPnlAnimOpenType10
    CHECK(frames_to_done(m, rng, kAnims[6], 2, 255) == 10);   // itfPnlAnimOpenType11
    CHECK(frames_to_done(m, rng, kAnims[8], 2, 255) == 15);   // itfPnlAnimOpenFade15
    CHECK(frames_to_done(m, rng, kAnims[10], 2, 255) == 6);   // itfPnlAnimOpenFade6
    CHECK(frames_to_done(m, rng, kAnims[4], 0, 0) == 10);     // itfPnlAnimCloseFade10
    CHECK(frames_to_done(m, rng, kAnims[7], 0, 0) == 1);      // itfPnlAnimCloseType11
    CHECK(frames_to_done(m, rng, kAnims[9], 0, 0) == 5);      // itfPnlAnimCloseFade5
    CHECK(frames_to_done(m, rng, kAnims[5], 0, 0) == 10);     // itfPnlAnimCloseFade13
    // The clear functions zero the record and return 0.
    fill_random(m, kWork, 16, rng);
    const Pair p = pair(m, PAIR(fn_itfPnlAnimClear10_003a9140), {kPanel}, rng(), "itfPnlAnimClear10");
    CHECK(p.hand.v0 == 0);
    CHECK(m.bytes(kWork, 16) == std::vector<u8>(16, 0));
}

TEST_CASE("game(msg2): the itfPnl phase dispatchers equal their recompiled bodies (callbacks and null slots)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3A95F000u};
    const u32 callbacks[] = {0, 0x3A9230u, 0x3A9400u, 0x3A9140u, 0x3A93A0u, 0x3A9170u};
    const AnimFn runners[] = {{PAIR(fn_itfPnlRunPhase0_003a95f0), "itfPnlRunPhase0"},
                              {PAIR(fn_itfPnlRunPhase1_003a9630), "itfPnlRunPhase1"},
                              {PAIR(fn_itfPnlRunPhase2_003a9670), "itfPnlRunPhase2"},
                              {PAIR(fn_itfPnlRunPhase3_003a96b0), "itfPnlRunPhase3"}};
    int nulls = 0;
    for (int it = 0; it < 400; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        store32(m, kPanel + 8, kWork);
        store32(m, kWork + 8, static_cast<u32>(rand_range(rng, -3, 16)));
        for (u32 k = 0; k < 4; ++k) store32(m, kPanel + 64 + 4 * k, callbacks[rng() % 6]);
        for (u32 k = 0; k < 4; ++k) {
            const bool null = load32(m, kPanel + 64 + 4 * k) == 0;
            const Pair p = pair(m, runners[k].hand, runners[k].recomp, {kPanel}, rng(), runners[k].name);
            if (null) {
                CHECK(p.hand.v0 == 1);
                ++nulls;
            }
        }
    }
    CHECK(nulls > 150);
}

TEST_CASE("game(msg2): the real BMD files of the disc through itfMesMngGetBmdMessageCount, itfMesMngGetMessageType, itfMesMngGetMessageCount, itfMesMngGetDialogueLine, itfMesMngGetSpeakerName") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const std::filesystem::path root = std::filesystem::path(elf_path()).parent_path().parent_path();
    // (MSG_QUEST and BP_TUTORIAL are two of the four standalone BMDs with a speaker table)
    const char* const files[] = {"DATA/HELP/DATTUTORIAL.BMD", "DATA/CAMP/COMU/DATCOMUHELP.BMD", "DATA/FACILITY/MSG_QUEST.BMD",
                                 "BTL/BATTLE/PANEL/BP_TUTORIAL.BMD"};
    std::mt19937 rng{0x3A5120D0u};
    int found = 0, lines = 0, speakers = 0;
    for (const char* rel : files) {
        const std::vector<u8> disc = read_file(root / rel);
        if (disc.empty()) {
            MESSAGE("SKIP: no real BMD at " << (root / rel).string());
            continue;
        }
        INFO(rel);
        formats::Result<formats::BmdView> view = formats::BmdView::parse(formats::as_bytes(disc.data(), disc.size()));
        REQUIRE(view.ok());
        // The image relocated as itfMesMngRelocateBmdOnce leaves it (test_bmd_msg.cpp proves that part).
        std::vector<u8> img = disc;
        for (u32 off : view->relocations()) {
            u32 v;
            std::memcpy(&v, img.data() + off, 4);
            v += kRealBmd + 0x20;
            std::memcpy(img.data() + off, &v, 4);
        }
        img[0x1C] = 1;
        std::memcpy(m.at(kRealBmd), img.data(), img.size());
        fill_random(m, kArena, kArenaSize, rng);
        std::memset(m.at(0), 0, kLow);
        const u32 count = static_cast<u32>(view->messages().size());
        Pair p = pair(m, PAIR(fn_itfMesMngGetBmdMessageCount_003a3010), {kRealBmd}, rng(), "itfMesMngGetBmdMessageCount (disc)");
        CHECK(p.hand.v0 == count);
        store32(m, kHandle + 4, kRealBmd);
        store32(m, slot_word(3), kHandle);
        p = pair(m, PAIR(fn_itfMesMngGetMessageCount_003a51a0), {3}, rng(), "itfMesMngGetMessageCount (disc)");
        CHECK(p.hand.v0 == count);
        for (u32 i = 0; i < count; ++i) {
            const formats::BmdMessage& msg = view->messages()[i];
            p = pair(m, PAIR(fn_itfMesMngGetMessageType_003a5120), {3, i}, rng(), "itfMesMngGetMessageType (disc)");
            CHECK(p.hand.v0 == static_cast<u32>(msg.type));
            if (msg.type != formats::BmdMessageType::Dialogue) continue;
            const u32 rec = kRealBmd + static_cast<u32>(msg.offset);
            for (s32 k = -1; k <= static_cast<s32>(msg.lines.size()); ++k) {
                p = pair(m, PAIR(fn_itfMesMngGetDialogueLine_003a5940), {rec, sxs(k)}, rng(), "itfMesMngGetDialogueLine (disc)");
                const bool in = k >= 0 && k < static_cast<s32>(msg.lines.size());
                const u32 want =
                    in ? kRealBmd + static_cast<u32>(reinterpret_cast<const u8*>(msg.lines[static_cast<std::size_t>(k)].data()) - disc.data()) : 0;
                CHECK(p.hand.v0 == want);
                lines += in ? 1 : 0;
            }
        }
        for (std::size_t j = 0; j < view->speaker_names().size(); ++j) {
            store16(m, kHandle + 32, static_cast<u16>(j));
            p = pair(m, PAIR(fn_itfMesMngGetSpeakerName_003a6030), {kHandle}, rng(), "itfMesMngGetSpeakerName (disc)");
            CHECK(m.str(static_cast<u32>(p.hand.v0)) == std::string(view->speaker_names()[j]));
            ++speakers;
        }
        ++found;
    }
    if (found == 0) {
        MESSAGE("SKIP: no real BMD found under " << root.string());
        return;
    }
    MESSAGE("real BMDs: " << found << " files, " << lines << " dialogue lines, " << speakers << " speaker names resolved");
}

#else
TEST_CASE("game(msg2): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
