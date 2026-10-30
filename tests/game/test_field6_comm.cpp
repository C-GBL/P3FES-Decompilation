// Pair tests of slice field6, part comm (game/src/field/field6_comm.cpp): the 41 field COMM handlers of k_command.c,
// each against its recompiled body (handgen_pairs.h / pair_harness.h / stand_ins.h: the whole register file and cycles
// at every check point, all RAM including the dead stack, the stand-ins' call logs), on
//   * random worlds: the p3fes_handgen sweep;
//   * the replay snapshots dorm_replay_4900 (the dorm 7/2: 3 NPCs, 27 field objects, 13 placements) and climb_ref_17000
//     (Tartarus 51/4: 2 characters, 5 NPCs, the dungeon task), with a script task whose argument stack holds each
//     command's arguments (script_vm.h ScrTask; g_scrCurrentTask -> it) -- the commands read their arguments with the
//     hand-written scrGetIntPara / scrGetFloatPara and answer in the COMM return register;
//   * documented rules computed on the host: the NPC count and rank of COMM 0x178 / 0x179 against the scene's type-3
//     list, the animation-finished byte of COMM 0x0E9, the resource flag of COMM 0x167, the sequence packets COMM
//     0x021 / 0x1D3 / 0x078 hand to adminiChangeSeq (its RwMalloc copy), the model paths of COMM 0x165, the dark-hour
//     wait of COMM 0x1E8.
// Callees this build does not emit are stood in by recorders (field4_util.h run_pair_si_absent).
#include "field6_util.h"

#include "p3fes/game/field6_comm.h"

#include <algorithm>
#include <cctype>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::f6t;

namespace p3fes::recomp_gen {
void fn_sub_1C2010_001c2010(EEContext&);  // generated body
void fn_sub_1C2010_001c2010__recomp(EEContext&);  // recompiled
void fn_sub_1C20B0_001c20b0(EEContext&);  // generated body
void fn_sub_1C20B0_001c20b0__recomp(EEContext&);  // recompiled
void fn_sub_1C2160_001c2160(EEContext&);  // generated body
void fn_sub_1C2160_001c2160__recomp(EEContext&);  // recompiled
void fn_sub_1C2240_001c2240(EEContext&);  // generated body
void fn_sub_1C2240_001c2240__recomp(EEContext&);  // recompiled
void fn_sub_1C2340_001c2340(EEContext&);  // generated body
void fn_sub_1C2340_001c2340__recomp(EEContext&);  // recompiled
void fn_sub_1C23B0_001c23b0(EEContext&);  // generated body
void fn_sub_1C23B0_001c23b0__recomp(EEContext&);  // recompiled
void fn_sub_1C2480_001c2480(EEContext&);  // generated body
void fn_sub_1C2480_001c2480__recomp(EEContext&);  // recompiled
void fn_sub_1C2550_001c2550(EEContext&);  // generated body
void fn_sub_1C2550_001c2550__recomp(EEContext&);  // recompiled
void fn_sub_1C2580_001c2580(EEContext&);  // generated body
void fn_sub_1C2580_001c2580__recomp(EEContext&);  // recompiled
void fn_sub_1C25B0_001c25b0(EEContext&);  // generated body
void fn_sub_1C25B0_001c25b0__recomp(EEContext&);  // recompiled
void fn_sub_1C2900_001c2900(EEContext&);  // generated body
void fn_sub_1C2900_001c2900__recomp(EEContext&);  // recompiled
void fn_sub_1C2B80_001c2b80(EEContext&);  // generated body
void fn_sub_1C2B80_001c2b80__recomp(EEContext&);  // recompiled
void fn_sub_1C2C80_001c2c80(EEContext&);  // generated body
void fn_sub_1C2C80_001c2c80__recomp(EEContext&);  // recompiled
void fn_sub_1C2DD0_001c2dd0(EEContext&);  // generated body
void fn_sub_1C2DD0_001c2dd0__recomp(EEContext&);  // recompiled
void fn_sub_1C37C0_001c37c0(EEContext&);  // generated body
void fn_sub_1C37C0_001c37c0__recomp(EEContext&);  // recompiled
void fn_sub_1C3820_001c3820(EEContext&);  // generated body
void fn_sub_1C3820_001c3820__recomp(EEContext&);  // recompiled
void fn_sub_1C3AD0_001c3ad0(EEContext&);  // generated body
void fn_sub_1C3AD0_001c3ad0__recomp(EEContext&);  // recompiled
void fn_sub_1C3CD0_001c3cd0(EEContext&);  // generated body
void fn_sub_1C3CD0_001c3cd0__recomp(EEContext&);  // recompiled
void fn_sub_1C3DC0_001c3dc0(EEContext&);  // generated body
void fn_sub_1C3DC0_001c3dc0__recomp(EEContext&);  // recompiled
void fn_sub_1C4120_001c4120(EEContext&);  // generated body
void fn_sub_1C4120_001c4120__recomp(EEContext&);  // recompiled
void fn_sub_1C45E0_001c45e0(EEContext&);  // generated body
void fn_sub_1C45E0_001c45e0__recomp(EEContext&);  // recompiled
void fn_sub_1C4700_001c4700(EEContext&);  // generated body
void fn_sub_1C4700_001c4700__recomp(EEContext&);  // recompiled
void fn_sub_1C48F0_001c48f0(EEContext&);  // generated body
void fn_sub_1C48F0_001c48f0__recomp(EEContext&);  // recompiled
void fn_sub_1C4990_001c4990(EEContext&);  // generated body
void fn_sub_1C4990_001c4990__recomp(EEContext&);  // recompiled
void fn_sub_1C4A00_001c4a00(EEContext&);  // generated body
void fn_sub_1C4A00_001c4a00__recomp(EEContext&);  // recompiled
void fn_sub_1C4A60_001c4a60(EEContext&);  // generated body
void fn_sub_1C4A60_001c4a60__recomp(EEContext&);  // recompiled
void fn_sub_1C4B30_001c4b30(EEContext&);  // generated body
void fn_sub_1C4B30_001c4b30__recomp(EEContext&);  // recompiled
void fn_sub_1C4C50_001c4c50(EEContext&);  // generated body
void fn_sub_1C4C50_001c4c50__recomp(EEContext&);  // recompiled
void fn_sub_1C5340_001c5340(EEContext&);  // generated body
void fn_sub_1C5340_001c5340__recomp(EEContext&);  // recompiled
void fn_sub_1C5400_001c5400(EEContext&);  // generated body
void fn_sub_1C5400_001c5400__recomp(EEContext&);  // recompiled
void fn_sub_1C54A0_001c54a0(EEContext&);  // generated body
void fn_sub_1C54A0_001c54a0__recomp(EEContext&);  // recompiled
void fn_sub_1C5510_001c5510(EEContext&);  // generated body
void fn_sub_1C5510_001c5510__recomp(EEContext&);  // recompiled
void fn_sub_1C5550_001c5550(EEContext&);  // generated body
void fn_sub_1C5550_001c5550__recomp(EEContext&);  // recompiled
void fn_sub_1C55B0_001c55b0(EEContext&);  // generated body
void fn_sub_1C55B0_001c55b0__recomp(EEContext&);  // recompiled
void fn_sub_1C56A0_001c56a0(EEContext&);  // generated body
void fn_sub_1C56A0_001c56a0__recomp(EEContext&);  // recompiled
void fn_sub_1C5700_001c5700(EEContext&);  // generated body
void fn_sub_1C5700_001c5700__recomp(EEContext&);  // recompiled
void fn_sub_1C5870_001c5870(EEContext&);  // generated body
void fn_sub_1C5870_001c5870__recomp(EEContext&);  // recompiled
void fn_sub_1C5900_001c5900(EEContext&);  // generated body
void fn_sub_1C5900_001c5900__recomp(EEContext&);  // recompiled
void fn_sub_1C5980_001c5980(EEContext&);  // generated body
void fn_sub_1C5980_001c5980__recomp(EEContext&);  // recompiled
void fn_sub_1C5D30_001c5d30(EEContext&);  // generated body
void fn_sub_1C5D30_001c5d30__recomp(EEContext&);  // recompiled
void fn_sub_1C5D80_001c5d80(EEContext&);  // generated body
void fn_sub_1C5D80_001c5d80__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_1C2010", 0x1C2010, &recomp_gen::fn_sub_1C2010_001c2010, &recomp_gen::fn_sub_1C2010_001c2010__recomp},
    {"sub_1C20B0", 0x1C20B0, &recomp_gen::fn_sub_1C20B0_001c20b0, &recomp_gen::fn_sub_1C20B0_001c20b0__recomp},
    {"sub_1C2160", 0x1C2160, &recomp_gen::fn_sub_1C2160_001c2160, &recomp_gen::fn_sub_1C2160_001c2160__recomp},
    {"sub_1C2240", 0x1C2240, &recomp_gen::fn_sub_1C2240_001c2240, &recomp_gen::fn_sub_1C2240_001c2240__recomp},
    {"sub_1C2340", 0x1C2340, &recomp_gen::fn_sub_1C2340_001c2340, &recomp_gen::fn_sub_1C2340_001c2340__recomp},
    {"sub_1C23B0", 0x1C23B0, &recomp_gen::fn_sub_1C23B0_001c23b0, &recomp_gen::fn_sub_1C23B0_001c23b0__recomp},
    {"sub_1C2480", 0x1C2480, &recomp_gen::fn_sub_1C2480_001c2480, &recomp_gen::fn_sub_1C2480_001c2480__recomp},
    {"sub_1C2550", 0x1C2550, &recomp_gen::fn_sub_1C2550_001c2550, &recomp_gen::fn_sub_1C2550_001c2550__recomp},
    {"sub_1C2580", 0x1C2580, &recomp_gen::fn_sub_1C2580_001c2580, &recomp_gen::fn_sub_1C2580_001c2580__recomp},
    {"sub_1C25B0", 0x1C25B0, &recomp_gen::fn_sub_1C25B0_001c25b0, &recomp_gen::fn_sub_1C25B0_001c25b0__recomp},
    {"sub_1C2900", 0x1C2900, &recomp_gen::fn_sub_1C2900_001c2900, &recomp_gen::fn_sub_1C2900_001c2900__recomp},
    {"sub_1C2B80", 0x1C2B80, &recomp_gen::fn_sub_1C2B80_001c2b80, &recomp_gen::fn_sub_1C2B80_001c2b80__recomp},
    {"sub_1C2C80", 0x1C2C80, &recomp_gen::fn_sub_1C2C80_001c2c80, &recomp_gen::fn_sub_1C2C80_001c2c80__recomp},
    {"sub_1C2DD0", 0x1C2DD0, &recomp_gen::fn_sub_1C2DD0_001c2dd0, &recomp_gen::fn_sub_1C2DD0_001c2dd0__recomp},
    {"sub_1C37C0", 0x1C37C0, &recomp_gen::fn_sub_1C37C0_001c37c0, &recomp_gen::fn_sub_1C37C0_001c37c0__recomp},
    {"sub_1C3820", 0x1C3820, &recomp_gen::fn_sub_1C3820_001c3820, &recomp_gen::fn_sub_1C3820_001c3820__recomp},
    {"sub_1C3AD0", 0x1C3AD0, &recomp_gen::fn_sub_1C3AD0_001c3ad0, &recomp_gen::fn_sub_1C3AD0_001c3ad0__recomp},
    {"sub_1C3CD0", 0x1C3CD0, &recomp_gen::fn_sub_1C3CD0_001c3cd0, &recomp_gen::fn_sub_1C3CD0_001c3cd0__recomp},
    {"sub_1C3DC0", 0x1C3DC0, &recomp_gen::fn_sub_1C3DC0_001c3dc0, &recomp_gen::fn_sub_1C3DC0_001c3dc0__recomp},
    {"sub_1C4120", 0x1C4120, &recomp_gen::fn_sub_1C4120_001c4120, &recomp_gen::fn_sub_1C4120_001c4120__recomp},
    {"sub_1C45E0", 0x1C45E0, &recomp_gen::fn_sub_1C45E0_001c45e0, &recomp_gen::fn_sub_1C45E0_001c45e0__recomp},
    {"sub_1C4700", 0x1C4700, &recomp_gen::fn_sub_1C4700_001c4700, &recomp_gen::fn_sub_1C4700_001c4700__recomp},
    {"sub_1C48F0", 0x1C48F0, &recomp_gen::fn_sub_1C48F0_001c48f0, &recomp_gen::fn_sub_1C48F0_001c48f0__recomp},
    {"sub_1C4990", 0x1C4990, &recomp_gen::fn_sub_1C4990_001c4990, &recomp_gen::fn_sub_1C4990_001c4990__recomp},
    {"sub_1C4A00", 0x1C4A00, &recomp_gen::fn_sub_1C4A00_001c4a00, &recomp_gen::fn_sub_1C4A00_001c4a00__recomp},
    {"sub_1C4A60", 0x1C4A60, &recomp_gen::fn_sub_1C4A60_001c4a60, &recomp_gen::fn_sub_1C4A60_001c4a60__recomp},
    {"sub_1C4B30", 0x1C4B30, &recomp_gen::fn_sub_1C4B30_001c4b30, &recomp_gen::fn_sub_1C4B30_001c4b30__recomp},
    {"sub_1C4C50", 0x1C4C50, &recomp_gen::fn_sub_1C4C50_001c4c50, &recomp_gen::fn_sub_1C4C50_001c4c50__recomp},
    {"sub_1C5340", 0x1C5340, &recomp_gen::fn_sub_1C5340_001c5340, &recomp_gen::fn_sub_1C5340_001c5340__recomp},
    {"sub_1C5400", 0x1C5400, &recomp_gen::fn_sub_1C5400_001c5400, &recomp_gen::fn_sub_1C5400_001c5400__recomp},
    {"sub_1C54A0", 0x1C54A0, &recomp_gen::fn_sub_1C54A0_001c54a0, &recomp_gen::fn_sub_1C54A0_001c54a0__recomp},
    {"sub_1C5510", 0x1C5510, &recomp_gen::fn_sub_1C5510_001c5510, &recomp_gen::fn_sub_1C5510_001c5510__recomp},
    {"sub_1C5550", 0x1C5550, &recomp_gen::fn_sub_1C5550_001c5550, &recomp_gen::fn_sub_1C5550_001c5550__recomp},
    {"sub_1C55B0", 0x1C55B0, &recomp_gen::fn_sub_1C55B0_001c55b0, &recomp_gen::fn_sub_1C55B0_001c55b0__recomp},
    {"sub_1C56A0", 0x1C56A0, &recomp_gen::fn_sub_1C56A0_001c56a0, &recomp_gen::fn_sub_1C56A0_001c56a0__recomp},
    {"sub_1C5700", 0x1C5700, &recomp_gen::fn_sub_1C5700_001c5700, &recomp_gen::fn_sub_1C5700_001c5700__recomp},
    {"sub_1C5870", 0x1C5870, &recomp_gen::fn_sub_1C5870_001c5870, &recomp_gen::fn_sub_1C5870_001c5870__recomp},
    {"sub_1C5900", 0x1C5900, &recomp_gen::fn_sub_1C5900_001c5900, &recomp_gen::fn_sub_1C5900_001c5900__recomp},
    {"sub_1C5980", 0x1C5980, &recomp_gen::fn_sub_1C5980_001c5980, &recomp_gen::fn_sub_1C5980_001c5980__recomp},
    {"sub_1C5D30", 0x1C5D30, &recomp_gen::fn_sub_1C5D30_001c5d30, &recomp_gen::fn_sub_1C5D30_001c5d30__recomp},
    {"sub_1C5D80", 0x1C5D80, &recomp_gen::fn_sub_1C5D80_001c5d80, &recomp_gen::fn_sub_1C5D80_001c5d80__recomp},
};

const Case& fc(const char* name) { return find_case(kCases, name); }
namespace sres = game::f6::sres;

// One handler on a snapshot: the arguments set after every reset, the absent callees stood in (v0 = `absent_v0`).
SiPair comm(Machine& m, const std::vector<u8>& base, const char* fn, const std::vector<s32>& args, u32 seed,
            const std::function<void(Machine&)>& extra = {}, const std::vector<int>& float_slots = {}, u64 absent_v0 = 0) {
    std::vector<u32> absent;
    const HwCheck hw = whole_ram_check();
    return run_pair_si_absent(m, base, fc(fn).hand, fc(fn).recomp, {0, 0, 0, 0}, seed, fn, hw,
                              [&](Machine& mm) {
                                  write_rw_slots(mm);
                                  set_comm_args(mm, args, float_slots);
                                  if (extra) extra(mm);
                              },
                              absent, absent_v0);
}
std::string upper(std::string s) {
    for (char& c : s) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}
bool logged_path_with(const SiPair& sp, const std::string& part) {
    for (const StandInCall& c : sp.recomp->si.log)
        if (upper(c.text).find(upper(part)) != std::string::npos) return true;
    return false;
}
// The block RwMalloc returned for a `size`-byte request in the recompiled run (adminiChangeSeq's packet copy).
u32 rw_block_of_size(const SiPair& sp, u64 size) {
    for (const StandInCall& c : sp.recomp->si.log)
        if (c.va == kRwSlotFns[0] && c.args[0] == size) return static_cast<u32>(c.v0);
    return 0;
}

}  // namespace

TEST_CASE("game(field6 comm): every handler equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}

// COMM 0x178 / 0x179 / 0x0E9 / 0x167 on the dorm's and Tartarus' scene resources against the documented rules.
TEST_CASE("game(field6 comm): the resource queries on the dorm and climb scenes (stand-ins)") {
    int scenes = 0;
    for (const char* snap : {"dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        INFO(snap);
        const std::vector<u32> npcs = scene_resources(m, 3);
        u32 seed = 1;
        {
            SiPair sp = comm(m, base, "sub_1C56A0", {}, seed++);
            CHECK(v0_of(sp.hw) == 1);
            CHECK(comm_return(m) == npcs.size());
        }
        for (u32 n = 0; n <= npcs.size(); ++n) {
            u32 expect = 0;
            if (n < npcs.size()) {
                const u16 rank = r16(m, r32(m, npcs[n] + sres::kCharModel) + 214);
                expect = rank > 500 ? 0u : rank / 50u + 1u;
            }
            SiPair sp = comm(m, base, "sub_1C5700", {static_cast<s32>(n)}, seed++);
            CHECK(comm_return(m) == expect);
        }
        // COMM 0x0E9: 1 when the model's animation byte +238 is 1; a missing resource -> 1
        std::vector<u32> res = npcs;
        for (u32 r : scene_resources(m, 10)) res.push_back(r);
        for (u32 r : scene_resources(m, 1)) res.push_back(r);
        for (u32 r : res) {
            const u16 id = r16(m, r + sres::kId);
            const u32 type = id >> 10;
            const u32 model = r32(m, r + (type == 10 ? sres::kModel : sres::kCharModel));
            const u32 expect = model && r8(m, model + 238) == 1 ? 1u : 0u;
            SiPair sp = comm(m, base, "sub_1C2B80", {id}, seed++);
            if (model) CHECK(v0_of(sp.hw) == static_cast<s64>(expect));
        }
        {
            SiPair sp = comm(m, base, "sub_1C2B80", {0x2BF0}, seed++);  // no such object
            CHECK(v0_of(sp.hw) == 1);
        }
        // COMM 0x167: resource +272 = the value
        if (!res.empty()) {
            const u16 id = r16(m, res[0] + sres::kId);
            comm(m, base, "sub_1C4990", {id, 0x1234}, seed++);
            CHECK(r32(m, res[0] + 272) == 0x1234u);
        }
        ++scenes;
    }
    if (scenes == 0) MESSAGE("SKIP: no replay snapshot");
}

// The sequence commands: the packet adminiChangeSeq copies (RwMalloc stand-in) and the sequence id in the admini work.
TEST_CASE("game(field6 comm): the field / event / dungeon calls hand their packets to adminiChangeSeq (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    {  // COMM 0x021: {u16 major, minor, entry, 0, sub-id}
        SiPair sp = comm(m, base, "sub_1C2010", {9, 4, 2, 1}, 1);
        CHECK(v0_of(sp.hw) == 1);
        const u32 pkt = rw_block_of_size(sp, 28);
        REQUIRE(pkt != 0u);
        CHECK(r16(m, pkt + 0) == 9);
        CHECK(r16(m, pkt + 2) == 4);
        CHECK(r16(m, pkt + 4) == 2);
        CHECK(r16(m, pkt + 6) == 0);
        CHECK(r16(m, pkt + 8) == 1);
    }
    {  // COMM 0x1D3: the same, the scene's NPC set -> -1 first
        SiPair sp = comm(m, base, "sub_1C20B0", {8, 3, 1, 0}, 2);
        CHECK(rs16(m, kSceneRecord + game::f4::scene::kNpcSet) == -1);
        const u32 pkt = rw_block_of_size(sp, 28);
        REQUIRE(pkt != 0u);
        CHECK(r16(m, pkt + 0) == 8);
        CHECK(r16(m, pkt + 2) == 3);
    }
    {  // COMM 0x078: {s32 floor, s32 0}; floor 1 sets gp 0x7CE26C
        SiPair sp = comm(m, base, "sub_1C2340", {1}, 3, [](Machine& mm) { w32(mm, gpv(game::f4::gpv::kDungeonReload), 0); });
        const u32 pkt = rw_block_of_size(sp, 8);
        REQUIRE(pkt != 0u);
        CHECK(rs32(m, pkt) == 1);
        CHECK(rs32(m, pkt + 4) == 0);
        CHECK(r32(m, gpv(game::f4::gpv::kDungeonReload)) == 1u);
    }
    {  // COMM 0x128: {floor, entry}; floor 7 leaves 0x7CE26C alone
        SiPair sp = comm(m, base, "sub_1C23B0", {7, 3}, 4, [](Machine& mm) { w32(mm, gpv(game::f4::gpv::kDungeonReload), 0); });
        const u32 pkt = rw_block_of_size(sp, 8);
        REQUIRE(pkt != 0u);
        CHECK(rs32(m, pkt) == 7);
        CHECK(rs32(m, pkt + 4) == 3);
        CHECK(r32(m, gpv(game::f4::gpv::kDungeonReload)) == 0u);
    }
    {  // COMM 0x076: the first call (timer 0) requests sequence 3 and waits
        SiPair sp = comm(m, base, "sub_1C2160", {101, 2, 3}, 5);
        CHECK(v0_of(sp.hw) == 0);
        CHECK(rw_block_of_size(sp, 28) != 0u);
    }
}

// COMM 0x165: the model file paths ("field/rmd/mMMM_NNN.RMD", or "field/grmd/fobjNNN.RMD" for a negative major), built in
// the handler's 64-byte stack buffer and handed to mdlModelCreateFromFile (sub_316B40), whose sub_3198C0 requests it
// (H_Cdvd_Request on the stand-in file layer: the logged path).
TEST_CASE("game(field6 comm): the model paths of COMM 0x165 (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    SiPair sp = comm(m, base, "sub_1C45E0", {7, 2}, 1);
    CHECK(logged_path_with(sp, FakeCd::build_path("field/rmd/m007_002.RMD")));
    CHECK(v0_of(sp.hw) == 1);
    sp = comm(m, base, "sub_1C45E0", {-1, 12}, 2);
    CHECK(logged_path_with(sp, FakeCd::build_path("field/grmd/fobj012.RMD")));
}

// The resource commands on real resources (pairs only: the model / frame code is the models slice's): animation,
// scale, shadow, placement, radius on the dorm's NPCs and objects; the camera turns; the party commands on climb.
TEST_CASE("game(field6 comm): the resource, camera and party commands on real scenes (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    const std::vector<u32> npcs = scene_resources(m, 3);
    const std::vector<u32> objs = scene_resources(m, 10);
    REQUIRE(!npcs.empty());
    REQUIRE(!objs.empty());
    const s32 npc = r16(m, npcs[0] + sres::kId), obj = r16(m, objs[0] + sres::kId);
    for (s32 id : {npc, obj, 0x0400, 0x5000}) {  // NPC, object, a missing character, an unsupported type
        INFO("resource " << id);
        CHECK(v0_of(comm(m, base, "sub_1C2900", {id, 3, 1, 8, 0}, seed++, {}, {3, 4}).hw) == 1);
        CHECK(v0_of(comm(m, base, "sub_1C2C80", {id, 2}, seed++, {}, {1}).hw) == 1);
        CHECK(v0_of(comm(m, base, "sub_1C2DD0", {id, 3}, seed++, {}, {1}).hw) == 1);
        CHECK(v0_of(comm(m, base, "sub_1C4120", {id, 0}, seed++).hw) == 1);
        CHECK(v0_of(comm(m, base, "sub_1C4B30", {id, 40}, seed++, {}, {1}).hw) == 1);
    }
    CHECK(v0_of(comm(m, base, "sub_1C37C0", {90, 30}, seed++).hw) == 1);
    CHECK(v0_of(comm(m, base, "sub_1C3820", {180, 20}, seed++).hw) == 1);
    CHECK(v0_of(comm(m, base, "sub_1C25B0", {0}, seed++).hw) == 1);
    CHECK(v0_of(comm(m, base, "sub_1C25B0", {21}, seed++).hw) == 1);
    CHECK(v0_of(comm(m, base, "sub_1C4A00", {2, 1}, seed++).hw) == 1);
    comm(m, base, "sub_1C5340", {3, 5}, seed++);
    comm(m, base, "sub_1C5400", {2, 5}, seed++);
    comm(m, base, "sub_1C55B0", {1}, seed++);
    comm(m, base, "sub_1C5870", {3, 1}, seed++);
    // the dark hour: COMM 0x1E8 counts 90 frames, then waits for the BGM and restarts the main field script
    {
        SiPair sp = comm(m, base, "sub_1C5D80", {}, seed++, [](Machine& mm) {
            w32(mm, gpv(game::f6::gp6::kDarkHourState), 1);
            w32(mm, gpv(game::f6::gp6::kDarkHourTimer), 10);
        });
        CHECK(v0_of(sp.hw) == 0);
        CHECK(comm_return(m) == 0u);
        CHECK(r32(m, gpv(game::f6::gp6::kDarkHourTimer)) == 11u);
    }
    {
        SiPair sp = comm(m, base, "sub_1C5D80", {}, seed++, [](Machine& mm) { w32(mm, gpv(game::f6::gp6::kDarkHourState), 0); });
        CHECK(v0_of(sp.hw) == 1);
    }
    comm(m, base, "sub_1C5D30", {}, seed++);
    // the party on climb: hide, the three re-create steps
    std::vector<u8> cbase;
    auto cp = real_machine("climb_ref_17000", cbase);
    if (!cp) return;
    Machine& c = *cp;
    comm(c, cbase, "sub_1C5900", {2}, seed++);
    for (u32 step = 0; step < 3; ++step) {
        INFO("re-create step " << step);
        comm(c, cbase, "sub_1C5980", {2}, seed++, [step](Machine& mm) { w32(mm, gpv(game::f6::gp6::kParty), step); });
    }
    comm(c, cbase, "sub_1C2580", {}, seed++);
    comm(c, cbase, "sub_1C2480", {}, seed++);
    comm(c, cbase, "sub_1C3AD0", {}, seed++);
}

#else

TEST_CASE("game(field6 comm): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
