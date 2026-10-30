// Pair tests of slice sweep1, group data (game/src/sweep/sweep1_data.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * facility/ps_model.bin from the extracted tree loaded through the stand-in file layer: the table the loader builds
//     against the host's parse of the file, and the seven getters on every record;
//   * the dorm snapshot: the item-table byte lookup against the documented sections of event/itemtbl.bin, the
//     social-link tag pick against gGlobalWork's ranks, comuFunction.c's accept (money clamp) / complete / expiry,
//     the flag words and range helpers.
#include "sweep1_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_16BA00_0016ba00(EEContext&);  // generated body
void fn_sub_16BA00_0016ba00__recomp(EEContext&);  // recompiled
void fn_sub_16BA80_0016ba80(EEContext&);  // generated body
void fn_sub_16BA80_0016ba80__recomp(EEContext&);  // recompiled
void fn_sub_16BB00_0016bb00(EEContext&);  // generated body
void fn_sub_16BB00_0016bb00__recomp(EEContext&);  // recompiled
void fn_sub_16BB80_0016bb80(EEContext&);  // generated body
void fn_sub_16BB80_0016bb80__recomp(EEContext&);  // recompiled
void fn_sub_16BC00_0016bc00(EEContext&);  // generated body
void fn_sub_16BC00_0016bc00__recomp(EEContext&);  // recompiled
void fn_sub_16BEE0_0016bee0(EEContext&);  // generated body
void fn_sub_16BEE0_0016bee0__recomp(EEContext&);  // recompiled
void fn_sub_16BF80_0016bf80(EEContext&);  // generated body
void fn_sub_16BF80_0016bf80__recomp(EEContext&);  // recompiled
void fn_sub_16C010_0016c010(EEContext&);  // generated body
void fn_sub_16C010_0016c010__recomp(EEContext&);  // recompiled
void fn_sub_16C1D0_0016c1d0(EEContext&);  // generated body
void fn_sub_16C1D0_0016c1d0__recomp(EEContext&);  // recompiled
void fn_sub_16E190_0016e190(EEContext&);  // generated body
void fn_sub_16E190_0016e190__recomp(EEContext&);  // recompiled
void fn_sub_16F320_0016f320(EEContext&);  // generated body
void fn_sub_16F320_0016f320__recomp(EEContext&);  // recompiled
void fn_sub_1715F0_001715f0(EEContext&);  // generated body
void fn_sub_1715F0_001715f0__recomp(EEContext&);  // recompiled
void fn_sub_172750_00172750(EEContext&);  // generated body
void fn_sub_172750_00172750__recomp(EEContext&);  // recompiled
void fn_sub_1727E0_001727e0(EEContext&);  // generated body
void fn_sub_1727E0_001727e0__recomp(EEContext&);  // recompiled
void fn_sub_172860_00172860(EEContext&);  // generated body
void fn_sub_172860_00172860__recomp(EEContext&);  // recompiled
void fn_sub_172B80_00172b80(EEContext&);  // generated body
void fn_sub_172B80_00172b80__recomp(EEContext&);  // recompiled
void fn_sub_172E50_00172e50(EEContext&);  // generated body
void fn_sub_172E50_00172e50__recomp(EEContext&);  // recompiled
void fn_sub_172F70_00172f70(EEContext&);  // generated body
void fn_sub_172F70_00172f70__recomp(EEContext&);  // recompiled
void fn_sub_173040_00173040(EEContext&);  // generated body
void fn_sub_173040_00173040__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_16BA00", 0x16BA00, &recomp_gen::fn_sub_16BA00_0016ba00, &recomp_gen::fn_sub_16BA00_0016ba00__recomp},
    {"sub_16BA80", 0x16BA80, &recomp_gen::fn_sub_16BA80_0016ba80, &recomp_gen::fn_sub_16BA80_0016ba80__recomp},
    {"sub_16BB00", 0x16BB00, &recomp_gen::fn_sub_16BB00_0016bb00, &recomp_gen::fn_sub_16BB00_0016bb00__recomp},
    {"sub_16BB80", 0x16BB80, &recomp_gen::fn_sub_16BB80_0016bb80, &recomp_gen::fn_sub_16BB80_0016bb80__recomp},
    {"sub_16BC00", 0x16BC00, &recomp_gen::fn_sub_16BC00_0016bc00, &recomp_gen::fn_sub_16BC00_0016bc00__recomp},
    {"sub_16BEE0", 0x16BEE0, &recomp_gen::fn_sub_16BEE0_0016bee0, &recomp_gen::fn_sub_16BEE0_0016bee0__recomp},
    {"sub_16BF80", 0x16BF80, &recomp_gen::fn_sub_16BF80_0016bf80, &recomp_gen::fn_sub_16BF80_0016bf80__recomp},
    {"sub_16C010", 0x16C010, &recomp_gen::fn_sub_16C010_0016c010, &recomp_gen::fn_sub_16C010_0016c010__recomp},
    {"sub_16C1D0", 0x16C1D0, &recomp_gen::fn_sub_16C1D0_0016c1d0, &recomp_gen::fn_sub_16C1D0_0016c1d0__recomp},
    {"sub_16E190", 0x16E190, &recomp_gen::fn_sub_16E190_0016e190, &recomp_gen::fn_sub_16E190_0016e190__recomp},
    {"sub_16F320", 0x16F320, &recomp_gen::fn_sub_16F320_0016f320, &recomp_gen::fn_sub_16F320_0016f320__recomp},
    {"sub_1715F0", 0x1715F0, &recomp_gen::fn_sub_1715F0_001715f0, &recomp_gen::fn_sub_1715F0_001715f0__recomp},
    {"sub_172750", 0x172750, &recomp_gen::fn_sub_172750_00172750, &recomp_gen::fn_sub_172750_00172750__recomp},
    {"sub_1727E0", 0x1727E0, &recomp_gen::fn_sub_1727E0_001727e0, &recomp_gen::fn_sub_1727E0_001727e0__recomp},
    {"sub_172860", 0x172860, &recomp_gen::fn_sub_172860_00172860, &recomp_gen::fn_sub_172860_00172860__recomp},
    {"sub_172B80", 0x172B80, &recomp_gen::fn_sub_172B80_00172b80, &recomp_gen::fn_sub_172B80_00172b80__recomp},
    {"sub_172E50", 0x172E50, &recomp_gen::fn_sub_172E50_00172e50, &recomp_gen::fn_sub_172E50_00172e50__recomp},
    {"sub_172F70", 0x172F70, &recomp_gen::fn_sub_172F70_00172f70, &recomp_gen::fn_sub_172F70_00172f70__recomp},
    {"sub_173040", 0x173040, &recomp_gen::fn_sub_173040_00173040, &recomp_gen::fn_sub_173040_00173040__recomp},
};

}  // namespace

TEST_CASE("game(sweep1 data): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep1 cases (real data and documented rules) ---

namespace {

constexpr u32 kOut = kScratch + 0x100;

// facility/ps_model.bin parsed on the host (sweep1.h psmodel): {n0, n1, .., .., n2, n3, .., ..} then the four arrays.
struct PsModelFile {
    u32 n[4] = {};
    std::vector<u8> recs[2], subs[2];
    bool ok = false;
};
PsModelFile parse_ps_model(const std::vector<u8>& f) {
    PsModelFile p;
    if (f.size() < 32) return p;
    std::memcpy(&p.n[0], f.data() + 0, 4);
    std::memcpy(&p.n[1], f.data() + 4, 4);
    std::memcpy(&p.n[2], f.data() + 16, 4);
    std::memcpy(&p.n[3], f.data() + 20, 4);
    std::size_t o = 32;
    for (int set = 0; set < 2; ++set) {
        const std::size_t rn = 32u * p.n[2 * set], sn = 16u * p.n[2 * set + 1];
        if (o + rn + sn > f.size()) return p;
        p.recs[set].assign(f.begin() + static_cast<std::ptrdiff_t>(o), f.begin() + static_cast<std::ptrdiff_t>(o + rn));
        o += rn;
        p.subs[set].assign(f.begin() + static_cast<std::ptrdiff_t>(o), f.begin() + static_cast<std::ptrdiff_t>(o + sn));
        o += sn;
    }
    p.ok = true;
    return p;
}

}  // namespace

// The ps_model.bin loader on the stand-in file layer (the real file from the extracted tree), the table it builds checked
// against the host's parse, then the seven getters on that table: every record's fields and copies.
TEST_CASE("game(sweep1 data): facility/ps_model.bin -- the loader's table and the getters") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const PsModelFile pf = parse_ps_model(read_extracted("DATA/FACILITY/PS_MODEL.BIN"));
    if (!pf.ok) {
        MESSAGE("SKIP: no DATA/FACILITY/PS_MODEL.BIN");
        return;
    }
    namespace psm = game::sw1::psmodel;
    SiPair sp = run_case(m, base, kCases, "sub_16C010", {0, 0, 0, 0}, 1);
    const u32 t = r32(m, gpv(psm::kGpTable));
    REQUIRE(t != 0u);
    for (int set = 0; set < 2; ++set) {
        INFO("set " << set);
        const u32 h = t + psm::kSetSize * static_cast<u32>(set);
        CHECK(r32(m, h + 0) == pf.n[2 * set]);
        CHECK(r32(m, h + 4) == pf.n[2 * set + 1]);
        CHECK(guest_equals(m, r32(m, h + psm::kRecords), pf.recs[set]));
        CHECK(guest_equals(m, r32(m, h + psm::kSubRecords), pf.subs[set]));
    }
    CHECK(calls(sp, kHCdvdDestroyFn).size() == 1u);
    // the getters on the loaded table (the loader's RAM is the base of these pairs)
    std::vector<u8> loaded(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    int checked = 0;
    for (u32 set = 0; set < 2; ++set) {
        const u32 n = std::min<u32>(pf.n[2 * set], 12);
        for (u32 i = 0; i < n; ++i) {
            const u8* rec = pf.recs[set].data() + 32 * i;
            s16 h[4];
            std::memcpy(h, rec, 8);
            f32 f;
            std::memcpy(&f, rec + psm::kRecF32, 4);
            const char* getters[4] = {"sub_16BA80", "sub_16BB00", "sub_16BB80", "sub_16BC00"};
            for (int k = 0; k < 4; ++k) {
                SiPair g = run_case(m, loaded, kCases, getters[k], {set, i, 0, 0}, 10 + i);
                CHECK(v0_of(g.hw) == h[k]);
            }
            SiPair g = run_case(m, loaded, kCases, "sub_16BA00", {set, i, 0, 0}, 20 + i);
            const u32 got = m.ctx.fpr[0];  // the recompiled run's $f0 (its context stays in m)
            u32 fbits;
            std::memcpy(&fbits, &f, 4);
            CHECK(got == fbits);
            g = run_case(m, loaded, kCases, "sub_16BF80", {set, i, kOut, 0}, 30 + i);
            CHECK(std::memcmp(m.at(kOut), rec, 32) == 0);
            s16 sub;
            std::memcpy(&sub, rec + psm::kRecSubIndex, 2);
            if (sub >= 0 && static_cast<u32>(sub) < pf.n[2 * set + 1]) {
                g = run_case(m, loaded, kCases, "sub_16BEE0", {set, i, kOut, 0}, 40 + i);
                CHECK(std::memcmp(m.at(kOut), pf.subs[set].data() + 16 * sub, 16) == 0);
            }
            ++checked;
        }
    }
    CHECK(checked > 0);
}

// The item-table byte lookup on the dorm snapshot's event/itemtbl.bin against the documented sections, and the
// social-link tag pick against gGlobalWork's ranks.
TEST_CASE("game(sweep1 data): the item-table byte lookup and the social-link tag pick (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    namespace itb = game::sw1::itemtbl;
    const u32 s0 = r32(m, gpv(itb::kGpSection0)), s2 = r32(m, gpv(itb::kGpSection2)), s3 = r32(m, gpv(itb::kGpSection3));
    const u32 s10 = r32(m, gpv(itb::kGpSection10));
    REQUIRE(s0 != 0u);
    int checked = 0;
    for (const u32 item : {0u, 1u, 7u, 50u, 999u, 1000u, 1003u, 1500u, 2000u, 2010u, 2999u, 3000u, 3999u, 4000u, 5000u}) {
        SiPair sp = run_case(m, base, kCases, "sub_1715F0", {item, 0, 0, 0}, 1 + item);
        u32 want = 0;
        if (item < 3000) {
            u32 idx = 0;
            if (item < 1000) idx = r16(m, s0 + 40 * item + 20);
            else if (item < 2000) idx = r16(m, s2 + 32 * (item - 1000) + 12);
            else idx = r16(m, s3 + 32 * (item - 2000) + 12);
            want = r8(m, s10 + 32 * idx) == 100 ? r8(m, s10 + 32 * idx + 1) : 255;
        }
        INFO("item " << item);
        CHECK(static_cast<u32>(v0_of(sp.hw)) == want);
        ++checked;
    }
    CHECK(checked == 15);
    // the tag pick: the first of row k's three {link, value} pairs whose link has a rank > 0
    constexpr u32 kTable = 0x5E3240u, kRanks = 0x836276u;
    auto pick = [&](u32 kind, const std::vector<u8>& ranks) {
        for (u32 i = 0; i < 3; ++i) {
            const s16 link = static_cast<s16>(r16(m, kTable + 12 * kind + 4 * i));
            if (link >= 0 && link < 30 && static_cast<s8>(ranks[static_cast<u32>(link)]) > 0)
                return static_cast<s16>(r16(m, kTable + 12 * kind + 4 * i + 2));
        }
        return s16{0};
    };
    for (u32 kind = 0; kind < 2; ++kind) {
        for (int variant = 0; variant < 3; ++variant) {
            std::vector<u8> ranks(30);
            for (u32 l = 0; l < 30; ++l) ranks[l] = variant == 0 ? r8(m, kRanks + l) : variant == 1 ? 0 : 3;
            SiPair sp = run_case(m, base, kCases, "sub_16E190", {kind, 0, 0, 0}, 50 + kind, [&](Machine& mm) {
                for (u32 l = 0; l < 30; ++l) w8(mm, kRanks + l, ranks[l]);
            });
            CHECK(v0_of(sp.hw) == pick(kind, ranks));
        }
    }
}

// comuFunction.c's entries: accepting takes the money (clamped to 9,999,999) and marks the entry; completion hands the
// rewards out; the expired-entry search; the small flag and range helpers.
TEST_CASE("game(sweep1 data): comuFunction.c entries, flag words and range helpers") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    namespace req = game::sw1::request;
    constexpr u32 kMoney = 0x83A6DCu;
    for (const u32 already : {0u, 1u}) {
        for (const s32 money : {5000, 12000000}) {
            SiPair sp = run_case(m, base, kCases, "sub_172E50", {7, 3, 1000, 0}, 1 + already, [&](Machine& mm) {
                w32(mm, req::kAccepted + 4 * 7, already);
                w32(mm, req::kDone + 4 * 7, 9);
                w32(mm, kMoney, static_cast<u32>(money));
            });
            if (already) {
                CHECK(rs32(m, kMoney) == money);
                CHECK(r32(m, req::kDone + 4 * 7) == 9u);
            } else {
                CHECK(r32(m, req::kAccepted + 4 * 7) == 1u);
                CHECK(r32(m, req::kDone + 4 * 7) == 0u);
                CHECK(r8(m, req::kExtra + 7) == 3u);
                CHECK(rs32(m, kMoney) == std::min(money - 1000, 9999999));
            }
        }
    }
    // the expired search over the snapshot's entries (whatever it finds, the pair decides), then one forced entry
    SiPair sp = run_case(m, base, kCases, "sub_172F70", {kOut, 0, 0, 0}, 10);
    sp = run_case(m, base, kCases, "sub_172F70", {kOut, 0, 0, 0}, 11, [&](Machine& mm) {
        for (u32 i = 0; i < 64; ++i) w32(mm, req::kAccepted + 4 * i, 0);
    });
    CHECK(v0_of(sp.hw) == 0);
    sp = run_case(m, base, kCases, "sub_173040", {5, 0, 0, 0}, 12, [&](Machine& mm) {
        w32(mm, req::kAccepted + 4 * 5, 1);
        w32(mm, req::kDone + 4 * 5, 0);
        w8(mm, req::kExtra + 5, 0);
    });
    CHECK(r32(m, req::kDone + 4 * 5) == 1u);
    // flag words
    constexpr u32 kW1 = 0x83A24Cu, kW2 = 0x83A34Cu;
    sp = run_case(m, base, kCases, "sub_16F320", {0, 0, 0, 0}, 20, [&](Machine& mm) { w32(mm, kW1, 0xFFFFFFFFu); });
    CHECK(r32(m, kW1) == ((0xFFFFFFFFu & ~0x3F8u) | 0x58u));
    sp = run_case(m, base, kCases, "sub_1727E0", {0, 0, 0, 0}, 21, [&](Machine& mm) { w32(mm, kW2, 0xFFFFFFFFu); });
    CHECK(r32(m, kW2) == 0xFFFFF07Fu);
    for (const u32 v : {0u, 0x400u, 0xFFFFFBFFu}) {
        sp = run_case(m, base, kCases, "sub_172860", {0, 0, 0, 0}, 22, [&](Machine& mm) { w32(mm, kW2, v); });
        CHECK(v0_of(sp.hw) == ((v & 0x400u) ? 1 : 0));
    }
    // the 6-byte "set" record: the empty pattern {255, 0, 0, 0} is 0, any other non-zero field 1, all zero 0
    struct R6 { u8 b0; u16 h2; u8 b4, b5; int want; };
    for (const R6 r : {R6{255, 0, 0, 0, 0}, R6{0, 0, 0, 0, 0}, R6{1, 0, 0, 0, 1}, R6{255, 1, 0, 0, 1}, R6{0, 0, 0, 2, 1}}) {
        sp = run_case(m, base, kCases, "sub_172750", {kOut, 0, 0, 0}, 40, [&](Machine& mm) {
            std::memset(mm.at(kOut), 0, 8);
            w8(mm, kOut, r.b0);
            w16(mm, kOut + 2, r.h2);
            w8(mm, kOut + 4, r.b4);
            w8(mm, kOut + 5, r.b5);
        });
        CHECK(v0_of(sp.hw) == r.want);
    }
    // the event block: 56 bytes copied to 0x8364BC
    sp = run_case(m, base, kCases, "sub_172B80", {1, 2, kOut, 0}, 50, [&](Machine& mm) {
        for (u32 i = 0; i < 56; ++i) w8(mm, kOut + i, static_cast<u8>(i * 3 + 1));
    });
    CHECK(std::memcmp(m.at(0x8364BCu), m.at(kOut), 56) == 0);
}

// --- end of the sweep1 cases ---

#else

TEST_CASE("game(sweep1 data): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
