// Phase 5 pair tests for the BMD message manager helpers and the manager slot list (game/src/msg/
// bmd_msg.cpp): each hand-written function and the recompiled body it replaces run on identical guest
// machines (pair_harness.h: result, callee-saved registers, memory outside the dead stack -- here the
// arena holding the BMD image and the handle --, virtual cycles, check-point count) on synthetic BMD
// images built by the rules of runtime/formats/bmd.h (random message counts, speakers, both magics,
// both relocation flag states, token streams of every encoding) and on the real .BMD files of the disc
// when the extracted tree is beside the ELF; the documented rules (docs/ANALYSIS/18_script_vm.md
// section 5, docs/FORMATS.md section 3) are checked on the host with the formats parser, independently
// of both bodies.
#include "pair_harness.h"

#include "p3fes/formats/bmd.h"
#include "p3fes/game/bmd_msg.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_itfMesMngCheckBmdMagic_003a5090(EEContext&);
void fn_itfMesMngCheckBmdMagic_003a5090__recomp(EEContext&);
void fn_itfMesMngGetMessageEntry_003a50e0(EEContext&);
void fn_itfMesMngGetMessageEntry_003a50e0__recomp(EEContext&);
void fn_itfMesMngGetSpeakerBlock_003a5100(EEContext&);
void fn_itfMesMngGetSpeakerBlock_003a5100__recomp(EEContext&);
void fn_itfMesMngRelocateBmdOnce_003a5030(EEContext&);
void fn_itfMesMngRelocateBmdOnce_003a5030__recomp(EEContext&);
void fn_itfMesMngBindBmd_003a42c0(EEContext&);
void fn_itfMesMngBindBmd_003a42c0__recomp(EEContext&);
void fn_sub_3B4920_003b4920(EEContext&);
void fn_sub_3B4920_003b4920__recomp(EEContext&);
void fn_sub_3B49A0_003b49a0(EEContext&);
void fn_sub_3B49A0_003b49a0__recomp(EEContext&);
void fn_sub_3B4A20_003b4a20(EEContext&);
void fn_sub_3B4A20_003b4a20__recomp(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

// Arena layout: a synthetic BMD image at kArena + (0 .. 0x400), the handle at +0x1A00; slot lists at +0.
constexpr u32 kImageRoom = 0x1800;
constexpr u32 kHandle = kArena + 0x1A00;
constexpr u32 kRealBmd = 0x01900000u;  // a real BMD of the disc, outside the arena (compared as a region)

u32 rd32(const std::vector<u8>& v, std::size_t off) {
    u32 x;
    std::memcpy(&x, v.data() + off, 4);
    return x;
}
void wr32(std::vector<u8>& v, std::size_t off, u32 x) { std::memcpy(v.data() + off, &x, 4); }
void wr16(std::vector<u8>& v, std::size_t off, u16 x) { std::memcpy(v.data() + off, &x, 2); }
u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
formats::Bytes span_of(const std::vector<u8>& v) { return formats::as_bytes(v.data(), v.size()); }

// Runs the pair with `region` and the arena restored between the runs; the region is compared afterwards
// (for images outside the arena, which the harness does not cover).
Pair run_pair_region(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, u32 region_va, u32 region_len) {
    const std::vector<u8> before = m.bytes(region_va, region_len);
    const std::vector<u8> arena_before = m.bytes(kArena, kArenaSize);
    Pair p;
    p.hand = run(m, hand, args, seed);
    const std::vector<u8> hand_region = m.bytes(region_va, region_len);
    std::memcpy(m.at(region_va), before.data(), region_len);
    std::memcpy(m.at(kArena), arena_before.data(), kArenaSize);
    p.recomp = run(m, recomp, args, seed);
    expect_same(p.hand, p.recomp, what);
    INFO(what);
    CHECK(hand_region == m.bytes(region_va, region_len));
    return p;
}

// --- synthetic BMD images by the rules of runtime/include/p3fes/formats/bmd.h -----------------------

struct SynthBmd {
    std::vector<u8> image;       // as on disc: pointers relative to +0x20, flag byte +0x1C = 0
    std::vector<u32> pointers;   // absolute offsets of every pointer field, ascending
    std::vector<u8> reloc;       // the encoded table (also at the end of `image`)
    u32 count = 0;
    u32 speakers = 0;
    u32 speaker_block = 0;       // offset of the BmdSpeakerBlock
    u32 word2 = 0;               // its third word
};

// One encoded line: ASCII, 0x0A, two-byte glyphs 0x80-0xEF xx, control codes 0xF1-0xFF of length
// 2 * low nibble (function byte 2..0x4C as sub_3B2430 asserts), the usual F2 08 FF FF F1 3F opener and
// F1 04 closer, NUL-terminated.
std::vector<u8> random_line(std::mt19937& rng) {
    std::vector<u8> t;
    if (rng() % 4 != 0) t.insert(t.end(), {0xF2, 0x08, 0xFF, 0xFF, 0xF1, 0x3F});
    const int n = 1 + static_cast<int>(rng() % 6);
    for (int i = 0; i < n; ++i) {
        switch (rng() % 4) {
            case 0: t.push_back(static_cast<u8>(0x20 + rng() % 95)); break;
            case 1: t.push_back(0x0A); break;
            case 2:  // parameter bytes stay non-zero: the host parser strips trailing NULs from a line
                t.push_back(static_cast<u8>(0x80 + rng() % 0x70));
                t.push_back(static_cast<u8>(1 + rng() % 255));
                break;
            default: {
                const u8 b = static_cast<u8>(0xF1 + rng() % 15);
                t.push_back(b);
                t.push_back(static_cast<u8>(2 + rng() % 0x4B));
                for (int k = 2; k < 2 * (b & 0x0F); ++k) t.push_back(static_cast<u8>(1 + rng() % 255));
                break;
            }
        }
    }
    if (rng() % 2) t.insert(t.end(), {0xF1, 0x04});
    t.push_back(0);
    return t;
}

// Encodes the pointer fields (word indices from +0x20, ascending) with every form of the relocation
// table (FORMATS.md section 3): one-byte advance (<= 127 words), two-byte, three-byte, and runs of
// 2..33 consecutive words.
std::vector<u8> encode_reloc(const std::vector<u32>& words, std::mt19937& rng) {
    std::vector<u8> out;
    u32 cursor = 0;
    std::size_t i = 0;
    while (i < words.size()) {
        const u32 delta = words[i] - cursor;
        std::size_t run = 1;
        while (i + run < words.size() && words[i + run] == words[i] + run) ++run;
        if (delta == 1 && run >= 2 && rng() % 2 == 0) {
            const u32 r = 2 + static_cast<u32>(rng() % (std::min<std::size_t>(run, 33) - 1));
            out.push_back(static_cast<u8>(((r - 2) << 3) | 7));
            cursor += r;
            i += r;
            continue;
        }
        std::vector<int> forms;
        if (delta <= 127) forms.push_back(1);
        if (delta < (1u << 14)) forms.push_back(2);
        if (delta < (1u << 21)) forms.push_back(3);
        const int f = forms[rng() % forms.size()];
        if (f == 1) {
            out.push_back(static_cast<u8>(delta << 1));
        } else if (f == 2) {
            const u32 v = (delta << 2) | 1;
            out.push_back(static_cast<u8>(v));
            out.push_back(static_cast<u8>(v >> 8));
        } else {
            const u32 v = (delta << 3) | 3;
            out.push_back(static_cast<u8>(v));
            out.push_back(static_cast<u8>(v >> 8));
            out.push_back(static_cast<u8>(v >> 16));
        }
        cursor = words[i];
        ++i;
    }
    return out;
}

void pad4(std::vector<u8>& v) {
    while (v.size() % 4) v.push_back(0);
}

SynthBmd make_bmd(std::mt19937& rng, bool msg1, u32 count, u32 speakers) {
    SynthBmd b;
    b.count = count;
    b.speakers = speakers;
    b.word2 = rng();
    std::vector<u8>& img = b.image;
    img.assign(0x20, 0);
    wr32(img, 0x00, 7);
    wr32(img, 0x08, msg1 ? game::bmd::kMagicMsg1 : game::bmd::kMagicMsg0);
    wr32(img, 0x18, count);
    wr32(img, 0x1C, 0x00020000u);
    img.resize(0x20 + count * 8, 0);
    for (u32 i = 0; i < count; ++i) b.pointers.push_back(0x24 + 8 * i);
    b.speaker_block = static_cast<u32>(img.size());
    img.resize(img.size() + 16, 0);
    wr32(img, b.speaker_block + 4, speakers);
    wr32(img, b.speaker_block + 8, b.word2);
    b.pointers.push_back(b.speaker_block);
    const u32 spk_table = static_cast<u32>(img.size());
    wr32(img, b.speaker_block, spk_table - 0x20);
    img.resize(img.size() + speakers * 4, 0);
    for (u32 j = 0; j < speakers; ++j) {
        b.pointers.push_back(spk_table + 4 * j);
        wr32(img, spk_table + 4 * j, static_cast<u32>(img.size()) - 0x20);
        const std::string name = "SPK" + std::to_string(j);
        img.insert(img.end(), name.begin(), name.end());
        img.push_back(0);
    }
    pad4(img);
    for (u32 i = 0; i < count; ++i) {
        const u32 rec = static_cast<u32>(img.size());
        const bool selection = rng() % 3 == 0;
        wr32(img, 0x20 + 8 * i, selection ? 1u : 0u);
        wr32(img, 0x24 + 8 * i, rec - 0x20);
        img.resize(rec + 24, 0);
        const std::string name = (selection ? "sel_" : "msg_") + std::to_string(i);
        std::memcpy(img.data() + rec, name.data(), name.size());
        const u32 lines = 1 + rng() % 4;
        if (selection) {
            img.resize(img.size() + 8, 0);
            wr16(img, rec + 26, static_cast<u16>(lines));
            wr32(img, rec + 28, rng());
        } else {
            img.resize(img.size() + 4, 0);
            wr16(img, rec + 24, static_cast<u16>(lines));
            wr16(img, rec + 26, (speakers && rng() % 2) ? static_cast<u16>(rng() % speakers) : 0xFFFFu);
        }
        const u32 ptrs = static_cast<u32>(img.size());
        img.resize(ptrs + 4 * lines + 4, 0);
        std::vector<u8> text;
        for (u32 k = 0; k < lines; ++k) {
            wr32(img, ptrs + 4 * k, static_cast<u32>(img.size() + text.size()) - 0x20);
            b.pointers.push_back(ptrs + 4 * k);
            const std::vector<u8> line = random_line(rng);
            text.insert(text.end(), line.begin(), line.end());
        }
        pad4(text);
        wr32(img, ptrs + 4 * lines, static_cast<u32>(text.size()));
        img.insert(img.end(), text.begin(), text.end());
    }
    pad4(img);
    std::vector<u32> words;
    for (u32 p : b.pointers) words.push_back((p - 0x20) / 4);
    b.reloc = encode_reloc(words, rng);
    wr32(img, 0x10, static_cast<u32>(img.size()));
    wr32(img, 0x14, static_cast<u32>(b.reloc.size()));
    img.insert(img.end(), b.reloc.begin(), b.reloc.end());
    wr32(img, 0x04, static_cast<u32>(img.size()));
    return b;
}

// What the image must look like after itfMesMngRelocateBmdOnce at guest address `va`.
std::vector<u8> relocated_image(const SynthBmd& b, u32 va) {
    std::vector<u8> want = b.image;
    for (u32 p : b.pointers) wr32(want, p, rd32(want, p) + va + 0x20);
    want[0x1C] = 1;
    return want;
}

std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

// --- slot lists ---------------------------------------------------------------------------------------

struct SlotList {
    u32 list;                 // guest address of the ItfMesSlotList
    std::vector<u32> slots;   // guest addresses of the slots
    std::vector<u32> used;    // in list order
    std::vector<u32> free;    // in list order
};

// Writes a consistent pair of lists over random slots (random stride, random bytes elsewhere).
SlotList make_lists(Machine& m, std::mt19937& rng, u32 n, u32 used_count) {
    SlotList l;
    l.list = kArena;
    const u32 stride = 12 + 4 * (rng() % 14);
    fill_random(m, kArena, kArenaSize, rng);
    for (u32 i = 0; i < n; ++i) l.slots.push_back(kArena + 0x40 + i * stride);
    std::vector<u32> order = l.slots;
    std::shuffle(order.begin(), order.end(), rng);
    l.used.assign(order.begin(), order.begin() + used_count);
    l.free.assign(order.begin() + used_count, order.end());
    auto link = [&](const std::vector<u32>& chain) {
        for (std::size_t i = 0; i < chain.size(); ++i) {
            store32(m, chain[i] + offsetof(game::ItfMesSlotLinks, prev), i ? chain[i - 1] : 0);
            store32(m, chain[i] + offsetof(game::ItfMesSlotLinks, next), i + 1 < chain.size() ? chain[i + 1] : 0);
        }
    };
    link(l.used);
    link(l.free);
    store32(m, l.list + offsetof(game::ItfMesSlotList, head), l.used.empty() ? 0 : l.used.front());
    store32(m, l.list + offsetof(game::ItfMesSlotList, tail), l.used.empty() ? 0 : l.used.back());
    store32(m, l.list + offsetof(game::ItfMesSlotList, free_head), l.free.empty() ? 0 : l.free.front());
    store32(m, l.list + offsetof(game::ItfMesSlotList, free_tail), l.free.empty() ? 0 : l.free.back());
    return l;
}

// Walks a chain head -> next and checks the prev links; returns the slots in order.
std::vector<u32> walk(const Machine& m, u32 head, u32 tail) {
    std::vector<u32> out;
    u32 prev = 0;
    for (u32 s = head; s != 0 && out.size() < 64; s = load32(m, s + offsetof(game::ItfMesSlotLinks, next))) {
        CHECK(load32(m, s + offsetof(game::ItfMesSlotLinks, prev)) == prev);
        out.push_back(s);
        prev = s;
    }
    CHECK(prev == tail);
    return out;
}

}  // namespace

TEST_CASE("game(msg): itfMesMngCheckBmdMagic equals its recompiled body and accepts MSG0 and MSG1 only") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xB3D5A61Cu};
    int cases = 0, accepted = 0;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kArena, kArenaSize, rng);
        const u32 bmd = kArena + 4 * (rng() % 0x700);
        u32 magic;
        switch (i % 6) {
            case 0: magic = game::bmd::kMagicMsg0; break;
            case 1: magic = game::bmd::kMagicMsg1; break;
            case 2: magic = 0x3247534Du; break;  // "MSG2"
            case 3: magic = 0x3047534Cu; break;  // one bit off
            default: magic = rng(); break;
        }
        store32(m, bmd + 8, magic);
        const Pair p = run_pair(m, &recomp_gen::fn_itfMesMngCheckBmdMagic_003a5090, &recomp_gen::fn_itfMesMngCheckBmdMagic_003a5090__recomp,
                                {sx(bmd), rng(), rng(), rng()}, rng(), "itfMesMngCheckBmdMagic", {{kArena, kArenaSize}});
        const bool want = magic == game::bmd::kMagicMsg0 || magic == game::bmd::kMagicMsg1;
        CHECK(p.hand.v0 == (want ? 1u : 0u));
        accepted += want;
        ++cases;
    }
    MESSAGE("itfMesMngCheckBmdMagic: " << cases << " cases, " << accepted << " accepted");
}

TEST_CASE("game(msg): itfMesMngGetMessageEntry and itfMesMngGetSpeakerBlock equal their recompiled bodies and address what the host parser finds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x6E7B1E5Du};
    int images = 0, entries = 0, parsed = 0;
    for (int i = 0; i < 60; ++i) {
        const SynthBmd b = make_bmd(rng, /*msg1=*/i % 5 != 4, rng() % 13, rng() % 4);
        REQUIRE(b.image.size() <= kImageRoom);
        fill_random(m, kArena, kArenaSize, rng);
        const u32 bmd = kArena + 4 * (rng() % 0x100);
        std::memcpy(m.at(bmd), b.image.data(), b.image.size());
        store32(m, kHandle + offsetof(game::ItfMesHandle, bmd), bmd);
        formats::Result<formats::BmdView> view = formats::BmdView::parse(span_of(b.image));
        if (rd32(b.image, 8) == game::bmd::kMagicMsg1) {
            REQUIRE(view.ok());
            REQUIRE(view->messages().size() == b.count);
            CHECK(view->speaker_names().size() == b.speakers);
            ++parsed;
        }
        // Every entry, then indices outside the table (no bounds check: plain arithmetic).
        std::vector<s32> indices;
        for (u32 k = 0; k < b.count; ++k) indices.push_back(static_cast<s32>(k));
        indices.push_back(-1);
        indices.push_back(static_cast<s32>(b.count));
        indices.push_back(static_cast<s32>(rng()));
        for (s32 index : indices) {
            const Pair p = run_pair(m, &recomp_gen::fn_itfMesMngGetMessageEntry_003a50e0, &recomp_gen::fn_itfMesMngGetMessageEntry_003a50e0__recomp,
                                    {sx(kHandle), sx(static_cast<u32>(index)), rng(), rng()}, rng(), "itfMesMngGetMessageEntry", {{kArena, kArenaSize}});
            const u32 want = bmd + 0x20 + (static_cast<u32>(index) << 3);
            CHECK(static_cast<u32>(p.hand.v0) == want);
            CHECK(p.hand.v0 == sx(want));
            if (index >= 0 && static_cast<u32>(index) < b.count && view.ok()) {
                const formats::BmdMessage& msg = view->messages()[static_cast<std::size_t>(index)];
                CHECK(load32(m, want + offsetof(game::BmdMessageEntry, type)) == static_cast<u32>(msg.type));
                CHECK(load32(m, want + offsetof(game::BmdMessageEntry, ptr)) + 0x20 == msg.offset);
            }
            ++entries;
        }
        const Pair s = run_pair(m, &recomp_gen::fn_itfMesMngGetSpeakerBlock_003a5100, &recomp_gen::fn_itfMesMngGetSpeakerBlock_003a5100__recomp,
                                {sx(bmd), rng(), rng(), rng()}, rng(), "itfMesMngGetSpeakerBlock", {{kArena, kArenaSize}});
        CHECK(s.hand.v0 == sx(bmd + b.speaker_block));
        CHECK(load32(m, static_cast<u32>(s.hand.v0) + offsetof(game::BmdSpeakerBlock, count)) == b.speakers);
        CHECK(load32(m, static_cast<u32>(s.hand.v0) + offsetof(game::BmdSpeakerBlock, word2)) == b.word2);
        ++images;
    }
    // A huge message count wraps the address arithmetic like the original's 32-bit add.
    {
        fill_random(m, kArena, kArenaSize, rng);
        store32(m, kArena + 0x18, 0xFFFFFFF0u);
        const Pair s = run_pair(m, &recomp_gen::fn_itfMesMngGetSpeakerBlock_003a5100, &recomp_gen::fn_itfMesMngGetSpeakerBlock_003a5100__recomp,
                                {sx(kArena), 0, 0, 0}, rng(), "itfMesMngGetSpeakerBlock (wrap)", {{kArena, kArenaSize}});
        CHECK(s.hand.v0 == sx(kArena + 0x20 + (0xFFFFFFF0u << 3)));
    }
    MESSAGE("itfMesMngGetMessageEntry: " << entries << " lookups on " << images << " images (" << parsed << " parsed by the host); itfMesMngGetSpeakerBlock: " << images + 1);
}

TEST_CASE("game(msg): itfMesMngRelocateBmdOnce equals its recompiled body, relocates every pointer field once and honours the flag") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5E10CA7Eu};
    int images = 0, fixups = 0, runs_forms[4] = {0, 0, 0, 0};
    for (int i = 0; i < 80; ++i) {
        const SynthBmd b = make_bmd(rng, /*msg1=*/i % 4 != 3, rng() % 13, rng() % 4);
        REQUIRE(b.image.size() <= kImageRoom);
        for (std::size_t k = 0; k < b.reloc.size();) {  // the forms the stream carries
            const u8 v = b.reloc[k];
            if ((v & 1) == 0) { ++runs_forms[0]; k += 1; }
            else if ((v & 7) == 7) { ++runs_forms[3]; k += 1; }
            else if ((v & 3) == 1) { ++runs_forms[1]; k += 2; }
            else { ++runs_forms[2]; k += 3; }
        }
        if (rd32(b.image, 8) == game::bmd::kMagicMsg1) {
            // The table decodes to exactly the pointer fields (host rule, FORMATS.md section 3).
            formats::Result<formats::BmdView> view = formats::BmdView::parse(span_of(b.image));
            REQUIRE(view.ok());
            CHECK(view->relocations() == b.pointers);
            for (const formats::BmdMessage& msg : view->messages())
                for (formats::Bytes line : msg.lines)
                    for (const formats::BmdToken& t : formats::bmd_tokenize(line)) CHECK(t.kind != formats::BmdTokenKind::Invalid);
        }
        fill_random(m, kArena, kArenaSize, rng);
        const u32 bmd = kArena + 4 * (rng() % 0x100);
        std::memcpy(m.at(bmd), b.image.data(), b.image.size());
        const std::vector<u8> outside_before = m.bytes(kArena, kArenaSize);
        // Unrelocated: every pointer field gains bmd + 0x20, the flag becomes 1, nothing else moves.
        run_pair(m, &recomp_gen::fn_itfMesMngRelocateBmdOnce_003a5030, &recomp_gen::fn_itfMesMngRelocateBmdOnce_003a5030__recomp,
                 {sx(bmd), rng(), rng(), rng()}, rng(), "itfMesMngRelocateBmdOnce (flag 0)", {{kArena, kArenaSize}});
        std::vector<u8> want = outside_before;
        const std::vector<u8> rel = relocated_image(b, bmd);
        std::memcpy(want.data() + (bmd - kArena), rel.data(), rel.size());
        CHECK(m.bytes(kArena, kArenaSize) == want);
        // Relocated (flag 1, or any other non-zero byte): untouched.
        if (i % 3 == 0) m.at(bmd)[0x1C] = static_cast<u8>(2 + rng() % 254);
        const std::vector<u8> again = m.bytes(kArena, kArenaSize);
        run_pair(m, &recomp_gen::fn_itfMesMngRelocateBmdOnce_003a5030, &recomp_gen::fn_itfMesMngRelocateBmdOnce_003a5030__recomp,
                 {sx(bmd), rng(), rng(), rng()}, rng(), "itfMesMngRelocateBmdOnce (flag set)", {{kArena, kArenaSize}});
        CHECK(m.bytes(kArena, kArenaSize) == again);
        fixups += static_cast<int>(b.pointers.size());
        ++images;
    }
    MESSAGE("itfMesMngRelocateBmdOnce: " << images << " images, " << fixups << " pointer fields; table forms 1/2/3-byte/run: "
                                        << runs_forms[0] << "/" << runs_forms[1] << "/" << runs_forms[2] << "/" << runs_forms[3]);
}

TEST_CASE("game(msg): itfMesMngBindBmd equals its recompiled body, binds and relocates once, keeps the MSG1 speaker word") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xB1ADB3D0u};
    int cases = 0, relocated = 0, msg1 = 0;
    for (int i = 0; i < 80; ++i) {
        const bool is_msg1 = i % 2 == 0;
        const SynthBmd b = make_bmd(rng, is_msg1, rng() % 13, rng() % 4);
        REQUIRE(b.image.size() <= kImageRoom);
        fill_random(m, kArena, kArenaSize, rng);
        const u32 bmd = kArena + 4 * (rng() % 0x100);
        std::memcpy(m.at(bmd), b.image.data(), b.image.size());
        const bool pre_relocated = i % 4 >= 2;
        if (pre_relocated) {
            const std::vector<u8> rel = relocated_image(b, bmd);
            std::memcpy(m.at(bmd), rel.data(), rel.size());
        }
        const u32 old_bmd = load32(m, kHandle + offsetof(game::ItfMesHandle, bmd));
        const std::vector<u8> handle_before = m.bytes(kHandle, game::kItfMesHandleSize);
        const Pair p = run_pair(m, &recomp_gen::fn_itfMesMngBindBmd_003a42c0, &recomp_gen::fn_itfMesMngBindBmd_003a42c0__recomp,
                                {sx(kHandle), sx(bmd), rng(), rng()}, rng(), "itfMesMngBindBmd", {{kArena, kArenaSize}});
        CHECK(p.hand.v0 == sx(old_bmd));
        CHECK(load32(m, kHandle + offsetof(game::ItfMesHandle, bmd)) == bmd);
        CHECK(load32(m, kHandle + offsetof(game::ItfMesHandle, speaker_word2)) == (is_msg1 ? b.word2 : 0u));
        std::vector<u8> handle_want = handle_before;
        wr32(handle_want, offsetof(game::ItfMesHandle, bmd), bmd);
        wr32(handle_want, offsetof(game::ItfMesHandle, speaker_word2), is_msg1 ? b.word2 : 0u);
        CHECK(m.bytes(kHandle, game::kItfMesHandleSize) == handle_want);
        const std::vector<u8> rel = relocated_image(b, bmd);
        CHECK(m.bytes(bmd, static_cast<u32>(rel.size())) == rel);  // relocated exactly once either way
        relocated += !pre_relocated;
        msg1 += is_msg1;
        ++cases;
    }
    // A null handle: K_Assert("itfMesManager.c", 3085) is a stub in this build, and the body goes on
    // to use address 0 as the handle (the words at 4 and 8); both bodies do the same.
    {
        const SynthBmd b = make_bmd(rng, true, 2, 1);
        fill_random(m, kArena, kArenaSize, rng);
        std::memcpy(m.at(kArena), b.image.data(), b.image.size());
        const std::vector<u8> low_before = m.bytes(0, 16);
        const Pair p = run_pair(m, &recomp_gen::fn_itfMesMngBindBmd_003a42c0, &recomp_gen::fn_itfMesMngBindBmd_003a42c0__recomp,
                                {0, sx(kArena), rng(), rng()}, rng(), "itfMesMngBindBmd (null handle)", {{kArena, kArenaSize}, {0, 16}});
        CHECK(p.hand.v0 == sx(rd32(low_before, 4)));
        CHECK(load32(m, 4) == kArena);
        CHECK(load32(m, 8) == b.word2);
        std::memcpy(m.at(0), low_before.data(), 16);
        ++cases;
    }
    MESSAGE("itfMesMngBindBmd: " << cases << " cases (" << relocated << " relocated by the bind, " << msg1 << " MSG1)");
}

TEST_CASE("game(msg): the real BMD files of the disc through RelocateBmdOnce, BindBmd, GetSpeakerBlock and GetMessageEntry") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    // extracted/DATA/... beside the ELF (extracted/disc/SLUS_216.21) when the build points at the main tree.
    const std::filesystem::path root = std::filesystem::path(elf_path()).parent_path().parent_path();
    const char* const files[] = {"DATA/HELP/DATTUTORIAL.BMD", "DATA/HELP/DATQUESTHELP.BMD", "DATA/HELP/DATGLOSSARYHELP.BMD",
                                 "DATA/HELP/DATMYTH.BMD", "DATA/CAMP/COMU/DATCOMUHELP.BMD", "DATA/CAMP/DATMIXRAIDHELP.BMD"};
    std::mt19937 rng{0x4EA1B3D0u};
    int found = 0, messages = 0;
    for (const char* rel : files) {
        const std::vector<u8> disc = read_file(root / rel);
        if (disc.empty()) {
            MESSAGE("SKIP: no real BMD at " << (root / rel).string());
            continue;
        }
        INFO(rel);
        formats::Result<formats::BmdView> view = formats::BmdView::parse(span_of(disc));
        REQUIRE(view.ok());
        const std::vector<u32> pointers = view->relocations();
        const u32 len = static_cast<u32>(disc.size());
        fill_random(m, kRealBmd, len + 64, rng);
        std::memcpy(m.at(kRealBmd), disc.data(), disc.size());
        fill_random(m, kArena, kArenaSize, rng);
        // Relocation in place: the decoded pointer fields gain kRealBmd + 0x20, the flag becomes 1.
        run_pair_region(m, &recomp_gen::fn_itfMesMngRelocateBmdOnce_003a5030, &recomp_gen::fn_itfMesMngRelocateBmdOnce_003a5030__recomp,
                        {sx(kRealBmd), rng(), rng(), rng()}, rng(), "itfMesMngRelocateBmdOnce (disc)", kRealBmd, len + 64);
        std::vector<u8> want = disc;
        for (u32 p : pointers) wr32(want, p, rd32(want, p) + kRealBmd + 0x20);
        want[0x1C] = 1;
        CHECK(m.bytes(kRealBmd, len) == want);
        // Binding the relocated image does not relocate it again; the handle takes the BMD and the MSG1 word.
        const u32 old_bmd = load32(m, kHandle + offsetof(game::ItfMesHandle, bmd));
        Pair p = run_pair_region(m, &recomp_gen::fn_itfMesMngBindBmd_003a42c0, &recomp_gen::fn_itfMesMngBindBmd_003a42c0__recomp,
                                 {sx(kHandle), sx(kRealBmd), rng(), rng()}, rng(), "itfMesMngBindBmd (disc)", kRealBmd, len + 64);
        CHECK(p.hand.v0 == sx(old_bmd));
        CHECK(m.bytes(kRealBmd, len) == want);
        CHECK(load32(m, kHandle + offsetof(game::ItfMesHandle, bmd)) == kRealBmd);
        const u32 spk = 0x20 + 8 * static_cast<u32>(view->messages().size());
        CHECK(load32(m, kHandle + offsetof(game::ItfMesHandle, speaker_word2)) == rd32(disc, spk + 8));
        p = run_pair_region(m, &recomp_gen::fn_itfMesMngGetSpeakerBlock_003a5100, &recomp_gen::fn_itfMesMngGetSpeakerBlock_003a5100__recomp,
                            {sx(kRealBmd), rng(), rng(), rng()}, rng(), "itfMesMngGetSpeakerBlock (disc)", kRealBmd, len + 64);
        CHECK(p.hand.v0 == sx(kRealBmd + spk));
        CHECK(load32(m, kRealBmd + spk + 4) == view->speaker_names().size());
        // Every entry now points at its record's guest address; the speaker table at the names.
        for (std::size_t i = 0; i < view->messages().size(); ++i) {
            p = run_pair_region(m, &recomp_gen::fn_itfMesMngGetMessageEntry_003a50e0, &recomp_gen::fn_itfMesMngGetMessageEntry_003a50e0__recomp,
                                {sx(kHandle), sx(static_cast<u32>(i)), rng(), rng()}, rng(), "itfMesMngGetMessageEntry (disc)", kRealBmd, len + 64);
            const u32 entry = static_cast<u32>(p.hand.v0);
            const formats::BmdMessage& msg = view->messages()[i];
            CHECK(load32(m, entry) == static_cast<u32>(msg.type));
            CHECK(load32(m, entry + 4) == kRealBmd + msg.offset);
            CHECK(std::string(reinterpret_cast<const char*>(m.at(kRealBmd + static_cast<u32>(msg.offset)))) == std::string(msg.name));
            ++messages;
        }
        for (std::size_t j = 0; j < view->speaker_names().size(); ++j) {
            const u32 table = load32(m, kRealBmd + spk);
            const u32 name = load32(m, table + 4 * static_cast<u32>(j));
            CHECK(std::string(reinterpret_cast<const char*>(m.at(name))) == std::string(view->speaker_names()[j]));
        }
        ++found;
    }
    if (found == 0) {
        MESSAGE("SKIP: no real BMD found under " << root.string());
        return;
    }
    MESSAGE("real BMDs: " << found << " files, " << messages << " message entries resolved");
}

TEST_CASE("game(msg): sub_3B4920 (slot list init) equals its recompiled body and chains the slots") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B492000u};
    int cases = 0, slots_written = 0;
    for (int i = 0; i < 70; ++i) {
        // 0 and 1 overshoot into a second slot (the body runs once before the count is tested); counts
        // above 128 wrap the signed-byte id.
        const s32 count = i < 3 ? i : (i % 7 == 6 ? 100 + static_cast<s32>(rng() % 60) : 2 + static_cast<s32>(rng() % 14));
        const u32 stride = 12 + 4 * (rng() % 6);
        const u32 n = static_cast<u32>(std::max(count, 2));
        REQUIRE(0x40 + n * stride <= kArenaSize);
        fill_random(m, kArena, kArenaSize, rng);
        const u32 list = kArena + 4 * (rng() % 8);
        const u32 slots = kArena + 0x40;
        run_pair(m, &recomp_gen::fn_sub_3B4920_003b4920, &recomp_gen::fn_sub_3B4920_003b4920__recomp,
                 {sx(list), sx(slots), sx(static_cast<u32>(count)), sx(stride)}, rng(), "sub_3B4920", {{kArena, kArenaSize}});
        for (u32 k = 0; k < n; ++k) {
            const u32 s = slots + k * stride;
            CHECK(load32(m, s + offsetof(game::ItfMesSlotLinks, prev)) == (k ? s - stride : 0));
            CHECK(load32(m, s + offsetof(game::ItfMesSlotLinks, next)) == (k + 1 < n ? s + stride : 0));
            CHECK(static_cast<s32>(load32(m, s + offsetof(game::ItfMesSlotLinks, id))) == static_cast<s8>(k));
        }
        CHECK(load32(m, list + offsetof(game::ItfMesSlotList, head)) == 0);
        CHECK(load32(m, list + offsetof(game::ItfMesSlotList, tail)) == 0);
        CHECK(load32(m, list + offsetof(game::ItfMesSlotList, free_head)) == slots);
        CHECK(load32(m, list + offsetof(game::ItfMesSlotList, free_tail)) == slots + (n - 1) * stride);
        slots_written += static_cast<int>(n);
        ++cases;
    }
    MESSAGE("sub_3B4920: " << cases << " lists, " << slots_written << " slots chained");
}

TEST_CASE("game(msg): sub_3B49A0 (pop a free slot) and sub_3B4A20 (release a slot) equal their recompiled bodies and keep both lists consistent") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B49A020u};
    int pops = 0, empty_pops = 0, releases = 0;
    for (int i = 0; i < 120; ++i) {
        const u32 n = 1 + rng() % 12;
        const u32 used_count = i % 5 == 4 ? n : rng() % (n + 1);  // every fifth list has no free slot
        SlotList l = make_lists(m, rng, n, used_count);
        // Pop until the free list is empty, then once more.
        const u32 pops_here = static_cast<u32>(l.free.size()) + 1;
        for (u32 k = 0; k < pops_here; ++k) {
            const Pair p = run_pair(m, &recomp_gen::fn_sub_3B49A0_003b49a0, &recomp_gen::fn_sub_3B49A0_003b49a0__recomp,
                                    {sx(l.list), rng(), rng(), rng()}, rng(), "sub_3B49A0", {{kArena, kArenaSize}});
            if (l.free.empty()) {
                CHECK(p.hand.v0 == 0);
                CHECK(load32(m, l.list + offsetof(game::ItfMesSlotList, free_head)) == 0);
                ++empty_pops;
            } else {
                const u32 slot = l.free.front();
                l.free.erase(l.free.begin());
                l.used.push_back(slot);
                CHECK(p.hand.v0 == sx(slot));
                ++pops;
            }
            CHECK(walk(m, load32(m, l.list + offsetof(game::ItfMesSlotList, head)), load32(m, l.list + offsetof(game::ItfMesSlotList, tail))) == l.used);
            CHECK(walk(m, load32(m, l.list + offsetof(game::ItfMesSlotList, free_head)), load32(m, l.list + offsetof(game::ItfMesSlotList, free_tail))) == l.free);
        }
        // Release the slots in use in random order (head, tail and middle positions all occur).
        while (!l.used.empty()) {
            const std::size_t at = rng() % l.used.size();
            const u32 slot = l.used[at];
            run_pair(m, &recomp_gen::fn_sub_3B4A20_003b4a20, &recomp_gen::fn_sub_3B4A20_003b4a20__recomp,
                     {sx(slot), sx(l.list), rng(), rng()}, rng(), "sub_3B4A20", {{kArena, kArenaSize}});
            l.used.erase(l.used.begin() + static_cast<std::ptrdiff_t>(at));
            l.free.push_back(slot);
            CHECK(walk(m, load32(m, l.list + offsetof(game::ItfMesSlotList, head)), load32(m, l.list + offsetof(game::ItfMesSlotList, tail))) == l.used);
            CHECK(walk(m, load32(m, l.list + offsetof(game::ItfMesSlotList, free_head)), load32(m, l.list + offsetof(game::ItfMesSlotList, free_tail))) == l.free);
            ++releases;
        }
    }
    MESSAGE("sub_3B49A0: " << pops << " pops, " << empty_pops << " on an empty free list; sub_3B4A20: " << releases << " releases");
}

#else

TEST_CASE("game(msg): BMD message manager replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game needs the ELF at configure time (P3FES_RT_EXEC_ELF)");
}

#endif
