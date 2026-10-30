// Pair tests of slice field6, part fldrc (game/src/field/field6_fldrc.cpp): every body against its recompiled body
// (tests/game/handgen_pairs.h / pair_harness.h / stand_ins.h: the whole register file and cycles at every check point,
// all RAM including the dead stack, the call logs of the stand-ins), on
//   * random worlds: the p3fes_handgen sweep of all 16;
//   * the exit ("hit") tables of the disc: every hMMM_NNN.bin of DATA/FIELD/PACK parsed on the host with the layout of
//     field6.h (documented-rule checks), real tables installed through sub_1C7F20 on the climb snapshot (count = size
//     / 44, the copy byte for byte, the request destroyed), the request paths of K_Fldrc_RequestFieldHitTableFile;
//   * the replay snapshots: the dungeon script request / install / free on climb_ref_17000's dungeon task, the block
//     script path, the btl_eff.pac request and the battle-effect EPL teardown, the live "trans wall CTL" tasks of
//     climb_ref_17000 / b_6700 (update, stop state, destroy) and a fresh one, the party finish step.
// Callees this build does not emit are stood in by recorders (field4_util.h run_pair_si_absent); the heap, printf /
// sprintf and the H_Cdvd layer are the stand-ins of stand_ins.h.
#include "field6_util.h"

#include "p3fes/game/field6_fldrc.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::f6t;

namespace p3fes::recomp_gen {
void fn_sub_1C0190_001c0190(EEContext&);  // generated body
void fn_sub_1C0190_001c0190__recomp(EEContext&);  // recompiled
void fn_sub_1C0210_001c0210(EEContext&);  // generated body
void fn_sub_1C0210_001c0210__recomp(EEContext&);  // recompiled
void fn_sub_1C02E0_001c02e0(EEContext&);  // generated body
void fn_sub_1C02E0_001c02e0__recomp(EEContext&);  // recompiled
void fn_sub_1C0330_001c0330(EEContext&);  // generated body
void fn_sub_1C0330_001c0330__recomp(EEContext&);  // recompiled
void fn_sub_1C03F0_001c03f0(EEContext&);  // generated body
void fn_sub_1C03F0_001c03f0__recomp(EEContext&);  // recompiled
void fn_sub_1C0440_001c0440(EEContext&);  // generated body
void fn_sub_1C0440_001c0440__recomp(EEContext&);  // recompiled
void fn_sub_1C0740_001c0740(EEContext&);  // generated body
void fn_sub_1C0740_001c0740__recomp(EEContext&);  // recompiled
void fn_sub_1C07F0_001c07f0(EEContext&);  // generated body
void fn_sub_1C07F0_001c07f0__recomp(EEContext&);  // recompiled
void fn_sub_1C0920_001c0920(EEContext&);  // generated body
void fn_sub_1C0920_001c0920__recomp(EEContext&);  // recompiled
void fn_sub_1C0D30_001c0d30(EEContext&);  // generated body
void fn_sub_1C0D30_001c0d30__recomp(EEContext&);  // recompiled
void fn_sub_1C0D70_001c0d70(EEContext&);  // generated body
void fn_sub_1C0D70_001c0d70__recomp(EEContext&);  // recompiled
void fn_sub_1C1E20_001c1e20(EEContext&);  // generated body
void fn_sub_1C1E20_001c1e20__recomp(EEContext&);  // recompiled
void fn_sub_1C1F30_001c1f30(EEContext&);  // generated body
void fn_sub_1C1F30_001c1f30__recomp(EEContext&);  // recompiled
void fn_K_Fldrc_RequestFieldHitTableFile_001c7e70(EEContext&);  // generated body
void fn_K_Fldrc_RequestFieldHitTableFile_001c7e70__recomp(EEContext&);  // recompiled
void fn_sub_1C7F20_001c7f20(EEContext&);  // generated body
void fn_sub_1C7F20_001c7f20__recomp(EEContext&);  // recompiled
void fn_sub_1CE960_001ce960(EEContext&);  // generated body
void fn_sub_1CE960_001ce960__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_1C0190", 0x1C0190, &recomp_gen::fn_sub_1C0190_001c0190, &recomp_gen::fn_sub_1C0190_001c0190__recomp},
    {"sub_1C0210", 0x1C0210, &recomp_gen::fn_sub_1C0210_001c0210, &recomp_gen::fn_sub_1C0210_001c0210__recomp},
    {"sub_1C02E0", 0x1C02E0, &recomp_gen::fn_sub_1C02E0_001c02e0, &recomp_gen::fn_sub_1C02E0_001c02e0__recomp},
    {"sub_1C0330", 0x1C0330, &recomp_gen::fn_sub_1C0330_001c0330, &recomp_gen::fn_sub_1C0330_001c0330__recomp},
    {"sub_1C03F0", 0x1C03F0, &recomp_gen::fn_sub_1C03F0_001c03f0, &recomp_gen::fn_sub_1C03F0_001c03f0__recomp},
    {"sub_1C0440", 0x1C0440, &recomp_gen::fn_sub_1C0440_001c0440, &recomp_gen::fn_sub_1C0440_001c0440__recomp},
    {"sub_1C0740", 0x1C0740, &recomp_gen::fn_sub_1C0740_001c0740, &recomp_gen::fn_sub_1C0740_001c0740__recomp},
    {"sub_1C07F0", 0x1C07F0, &recomp_gen::fn_sub_1C07F0_001c07f0, &recomp_gen::fn_sub_1C07F0_001c07f0__recomp},
    {"sub_1C0920", 0x1C0920, &recomp_gen::fn_sub_1C0920_001c0920, &recomp_gen::fn_sub_1C0920_001c0920__recomp},
    {"sub_1C0D30", 0x1C0D30, &recomp_gen::fn_sub_1C0D30_001c0d30, &recomp_gen::fn_sub_1C0D30_001c0d30__recomp},
    {"sub_1C0D70", 0x1C0D70, &recomp_gen::fn_sub_1C0D70_001c0d70, &recomp_gen::fn_sub_1C0D70_001c0d70__recomp},
    {"sub_1C1E20", 0x1C1E20, &recomp_gen::fn_sub_1C1E20_001c1e20, &recomp_gen::fn_sub_1C1E20_001c1e20__recomp},
    {"sub_1C1F30", 0x1C1F30, &recomp_gen::fn_sub_1C1F30_001c1f30, &recomp_gen::fn_sub_1C1F30_001c1f30__recomp},
    {"K_Fldrc_RequestFieldHitTableFile", 0x1C7E70, &recomp_gen::fn_K_Fldrc_RequestFieldHitTableFile_001c7e70, &recomp_gen::fn_K_Fldrc_RequestFieldHitTableFile_001c7e70__recomp},
    {"sub_1C7F20", 0x1C7F20, &recomp_gen::fn_sub_1C7F20_001c7f20, &recomp_gen::fn_sub_1C7F20_001c7f20__recomp},
    {"sub_1CE960", 0x1CE960, &recomp_gen::fn_sub_1CE960_001ce960, &recomp_gen::fn_sub_1CE960_001ce960__recomp},
};

const Case& fc(const char* name) { return find_case(kCases, name); }
namespace fld = game::f4::fld;
namespace dng = game::f4::dng;
namespace hitrec = game::f6::hitrec;
constexpr u32 kBtlEffPack = 0x7CE258u;
constexpr u32 kDungeonTask = 0x7CE268u;

bool contains_text(const SiPair& sp, const std::string& text) {
    for (const StandInCall& c : sp.recomp->si.log)
        if (c.text == text || c.text == FakeCd::build_path(text)) return true;
    return false;
}

}  // namespace

TEST_CASE("game(field6 fldrc): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 64);
}

// The exit tables on the host (field6.h "The field exit ("hit") table"): 208 tables, 867 records in this ISO; every
// record's kind is 0 / 1, its side 0..4, its flags -1 or a flag id, its sound -1 or an id; a door (procedure 0xFFFF)
// names its destination, and nearly every destination field has a pack of its own; +36 / +40 are unused.
TEST_CASE("game(field6 fldrc): the exit table format holds for every table on the disc") {
    const std::vector<HitTable> tables = all_hit_tables();
    if (tables.empty()) {
        MESSAGE("SKIP: no extracted DATA/FIELD/PACK");
        return;
    }
    u32 records = 0, doors = 0, script_ids = 0, door_targets = 0, door_targets_packed = 0, padded = 0, with_flags = 0, prompts = 0;
    for (const HitTable& t : tables) {
        INFO("h" << t.major << "_" << t.minor);
        padded += (t.data.size() % hitrec::kSize) != 0;
        for (std::size_t i = 0; i + hitrec::kSize <= t.data.size(); i += hitrec::kSize) {
            const HitRecord r = hit_record(t.data.data() + i);
            ++records;
            CHECK(r.kind <= 1);
            CHECK(r.side >= 0);
            CHECK(r.side <= 4);
            CHECK(r.sound >= -1);
            for (s32 f : r.flags) CHECK(f >= -1);
            with_flags += r.flags[0] != -1 || r.flags[1] != -1 || r.flags[2] != -1;
            prompts += r.prompt != 0;
            CHECK(r.w40 == 0u);
            if (r.procedure == hitrec::kDoor) {
                ++doors;
                if (r.next_major != 0 || r.next_minor != 0) {
                    ++door_targets;
                    char rel[64];
                    std::snprintf(rel, sizeof rel, "DATA/FIELD/PACK/F%03u_%03u.PAC", unsigned(r.next_major), unsigned(r.next_minor));
                    door_targets_packed += !read_extracted(rel).empty();
                }
            } else {
                script_ids += r.next_major != 0 || r.next_minor != 0;  // ids a script record carries (not read)
            }
        }
    }
    CHECK(tables.size() == 208);
    CHECK(records == 867);
    CHECK(doors == 157);
    CHECK(door_targets == 91);
    CHECK(script_ids == 24);
    CHECK(door_targets_packed * 10 >= door_targets * 9);
    MESSAGE("exit tables: " << tables.size() << " tables (" << padded << " padded), " << records << " records, " << doors
                            << " doors (" << door_targets << " with a destination, " << door_targets_packed
                            << " of them packed), " << with_flags << " with flags, " << prompts << " with a prompt");
}

// sub_1C7F20 installs real tables: a finished H_Cdvd node holding the table, the .pac not resident; both bodies free the
// old table (sub_1C80C0), allocate the copy (RwCalloc stand-in), copy it and destroy the node.
TEST_CASE("game(field6 fldrc): real exit tables installed through sub_1C7F20 (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    const std::vector<HitTable> tables = all_hit_tables();
    if (!mp || tables.empty()) {
        MESSAGE("SKIP: no ELF, no climb_ref_17000 snapshot or no extracted packs");
        return;
    }
    Machine& m = *mp;
    const HwCheck hw = whole_ram_check();
    const u32 node = kScratch, data = kScratch + 0x400;
    int seed = 1, installed = 0;
    for (std::size_t k = 0; k < tables.size(); k += 13) {
        const HitTable& t = tables[k];
        INFO("h" << t.major << "_" << t.minor);
        reset(m, base);
        write_rw_slots(m);
        w32(m, gpv(game::f4::gpv::kPacRequest), 0);
        make_loaded_node(m, node, data, t.data);
        SiPair sp = run_pair_si(m, fc("sub_1C7F20").hand, fc("sub_1C7F20").recomp, {node, 0, 0, 0}, static_cast<u32>(seed++),
                                "sub_1C7F20", hw, [](StandInWorld& w) {
                                    w.heap.install_all(w.si);
                                    w.si.install_recorder(kHCdvdDestroyFn, "H_Cdvd_Destroy", 1);
                                });
        CHECK(v0_of(sp.hw) == 1);
        CHECK(r32(m, kSField + fld::kExitCount) == t.data.size() / hitrec::kSize);
        CHECK(guest_equals(m, r32(m, kSField + fld::kExits), t.data));
        CHECK(sp.recomp->si.calls_to(kHCdvdDestroyFn) == 1);
        ++installed;
    }
    // Still loading: 0 and nothing touched; no request: 1.
    reset(m, base);
    write_rw_slots(m);
    make_loaded_node(m, node, data, tables[0].data);
    w32(m, node + game::f6::node::kState, 1);
    const u32 before = r32(m, kSField + fld::kExitCount);
    hgp::Run r = hgp::pair(m, fc("sub_1C7F20").hand, fc("sub_1C7F20").recomp, {node, 0, 0, 0}, 99, "sub_1C7F20 loading");
    CHECK(v0_of(r) == 0);
    CHECK(r32(m, kSField + fld::kExitCount) == before);
    r = hgp::pair(m, fc("sub_1C7F20").hand, fc("sub_1C7F20").recomp, {0, 0, 0, 0}, 100, "sub_1C7F20 none");
    CHECK(v0_of(r) == 1);
    MESSAGE(installed << " real exit tables installed");
}

// K_Fldrc_RequestFieldHitTableFile: the .pac resident -> 1 without a request; else the loose file is looked for (none on
// this disc: the tables live in the packs) -> 0. Major 0xFFFF is NOT special (the u16 is compared with -1: dead code):
// both bodies ask for h65535_NNN.bin.
TEST_CASE("game(field6 fldrc): the exit table request rules (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    const HwCheck hw = whole_ram_check();
    const Case& c = fc("K_Fldrc_RequestFieldHitTableFile");
    {
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {0xFFFF, 2, 0, 0}, 1, c.name, hw, install_field_world);
        CHECK(v0_of(sp.hw) == 0);
        CHECK(contains_text(sp, "field/table/h65535_002.bin"));
    }
    reset(m, base);
    write_rw_slots(m);
    w32(m, gpv(game::f4::gpv::kPacRequest), kScratch);  // a resident pack
    {
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {7, 2, 0, 0}, 2, c.name, hw, install_field_world);
        CHECK(v0_of(sp.hw) == 1);
        CHECK(sp.recomp->si.calls_to(kHCdvdRequestFn) == 0);
    }
    reset(m, base);
    write_rw_slots(m);
    w32(m, gpv(game::f4::gpv::kPacRequest), 0);
    {
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {7, 2, 0, 0}, 3, c.name, hw, install_field_world);
        CHECK(contains_text(sp, "field/table/h007_002.bin"));
        CHECK(sp.recomp->si.calls_to(kHCdvdRequestFn) == 0);
        CHECK(v0_of(sp.hw) == 0);
    }
}

// The dungeon scripts on climb_ref_17000 (Tartarus floor 5 = 51/4, the dungeon task alive with its script copied):
// no request while the copy exists; with the copy cleared, "field/script/dungeonat.bf"; the install copies a loaded
// node to work +52 / +56; the free clears +52; the block script path carries the block set.
TEST_CASE("game(field6 fldrc): the dungeon script request, install and free on the climb snapshot (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    const auto bf = read_extracted("DATA/FIELD/SCRIPT/DUNGEONAT.BF");
    if (!mp || bf.empty()) {
        MESSAGE("SKIP: no ELF, no climb_ref_17000 snapshot or no extracted DATA/FIELD");
        return;
    }
    Machine& m = *mp;
    const HwCheck hw = whole_ram_check();
    const u32 task = r32(m, kDungeonTask);
    REQUIRE(task != 0);
    const u32 work = r32(m, task + game::f6::task::kWork);
    {
        write_rw_slots(m);
        SiPair sp = run_pair_si(m, fc("sub_1C0190").hand, fc("sub_1C0190").recomp, {0, 0, 0, 0}, 1, "sub_1C0190", hw, install_field_world);
        CHECK(v0_of(sp.hw) == 0);
        CHECK(sp.recomp->si.calls_to(kHCdvdRequestFn) == 0);
    }
    reset(m, base);
    write_rw_slots(m);
    w32(m, work + dng::kScrMemory, 0);
    {
        SiPair sp = run_pair_si(m, fc("sub_1C0190").hand, fc("sub_1C0190").recomp, {0, 0, 0, 0}, 2, "sub_1C0190", hw, install_field_world);
        CHECK(sp.recomp->si.calls_to(kHCdvdRequestFn) == 1);
        CHECK(contains_text(sp, "field/script/dungeonat.bf"));
        CHECK(v0_of(sp.hw) != 0);
    }
    reset(m, base);
    write_rw_slots(m);
    w32(m, work + dng::kScrMemory, 0);
    make_loaded_node(m, kScratch, kScratch + 0x400, bf);
    {
        SiPair sp = run_pair_si(m, fc("sub_1C0210").hand, fc("sub_1C0210").recomp, {kScratch, 0, 0, 0}, 3, "sub_1C0210", hw,
                                [](StandInWorld& w) {
                                    w.heap.install_all(w.si);
                                    w.si.install_recorder(kHCdvdDestroyFn, "H_Cdvd_Destroy", 1);
                                });
        CHECK(v0_of(sp.hw) == 1);
        CHECK(r32(m, work + dng::kScrSize) == bf.size());
        CHECK(guest_equals(m, r32(m, work + dng::kScrMemory), bf));
        CHECK(sp.recomp->si.calls_to(kHCdvdDestroyFn) == 1);
    }
    {
        SiPair sp = run_pair_si(m, fc("sub_1C02E0").hand, fc("sub_1C02E0").recomp, {0, 0, 0, 0}, 4, "sub_1C02E0", hw,
                                [](StandInWorld& w) { w.heap.install_all(w.si); });
        CHECK(r32(m, work + dng::kScrMemory) == 0u);
    }
    reset(m, base);
    write_rw_slots(m);
    {
        SiPair sp = run_pair_si(m, fc("sub_1C0330").hand, fc("sub_1C0330").recomp, {5, 0, 0, 0}, 5, "sub_1C0330", hw, install_field_world);
        CHECK(contains_text(sp, "field/script/dungeonat05.bf"));
    }
}

// The battle-effect pack: dorm has no EPLs and no request -> btl_eff.pac is requested (as an archive); climb has the
// EPLs -> no request. The teardown destroys climb's seven EPL tasks and clears all ten slots; the release waits for
// every EPL (the EPL readiness test stood in as "ready") and then destroys the request.
TEST_CASE("game(field6 fldrc): the btl_eff.pac request and the battle-effect EPL teardown (stand-ins)") {
    const HwCheck hw = whole_ram_check();
    {
        std::vector<u8> base;
        auto mp = real_machine("dorm_replay_4900", base);
        if (!mp) {
            MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
            return;
        }
        Machine& m = *mp;
        write_rw_slots(m);
        SiPair sp = run_pair_si(m, fc("sub_1C03F0").hand, fc("sub_1C03F0").recomp, {0, 0, 0, 0}, 1, "sub_1C03F0", hw, install_field_world);
        CHECK(sp.recomp->si.calls_to(kHCdvdRequestFn) == 1);
        CHECK(contains_text(sp, "field/btl_effect/btl_eff.pac"));
        CHECK(r32(m, kBtlEffPack) != 0u);
    }
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) return;
    Machine& m = *mp;
    write_rw_slots(m);
    {
        SiPair sp = run_pair_si(m, fc("sub_1C03F0").hand, fc("sub_1C03F0").recomp, {0, 0, 0, 0}, 2, "sub_1C03F0", hw, install_field_world);
        CHECK(sp.recomp->si.calls_to(kHCdvdRequestFn) == 0);
    }
    std::vector<u32> absent;
    {
        reset(m, base);
        SiPair sp = run_pair_si_absent(m, base, fc("sub_1C07F0").hand, fc("sub_1C07F0").recomp, {0, 0, 0, 0}, 3, "sub_1C07F0", hw,
                                       [](Machine& mm) { write_rw_slots(mm); }, absent);
        for (int i = 0; i < 10; ++i) CHECK(r32(m, kSField + fld::kBtlEpl + 4 * i) == 0u);
    }
    {
        absent.clear();
        SiPair sp = run_pair_si_absent(m, base, fc("sub_1C0740").hand, fc("sub_1C0740").recomp, {0, 0, 0, 0}, 4, "sub_1C0740", hw,
                                       [](Machine& mm) {
                                           write_rw_slots(mm);
                                           w32(mm, kBtlEffPack, kScratch);
                                       },
                                       absent, 1);
        MESSAGE("sub_1C0740: " << absent.size() << " callees stood in, $v0 " << v0_of(sp.hw));
    }
}

// The transparent-wall control on its live tasks: climb_ref_17000 (a fixed floor: field objects) and b_6700 (a random
// floor: 38 block resources). The update returns 0 in state 0 and -1 in state 1 (the kernel then destroys the task);
// the destroy frees the work; a new task gets its target at +516.
TEST_CASE("game(field6 fldrc): the trans wall CTL task on the climb and b_6700 snapshots (stand-ins)") {
    const HwCheck hw = whole_ram_check();
    int runs = 0;
    for (const char* snap : {"climb_ref_17000", "b_6700"}) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        const u32 task = r32(m, kSField + fld::kWalls);
        if (task == 0) continue;
        const u32 work = r32(m, task + game::f6::task::kWork);
        INFO(snap);
        std::vector<u32> absent;
        SiPair sp = run_pair_si_absent(m, base, fc("sub_1C0D70").hand, fc("sub_1C0D70").recomp, {task, 0, 0, 0}, 1, "sub_1C0D70", hw,
                                       [](Machine& mm) { write_rw_slots(mm); }, absent);
        CHECK(v0_of(sp.hw) == 0);
        CHECK(r32(m, work + game::f6::wall::kState) == 0u);
        absent.clear();
        sp = run_pair_si_absent(m, base, fc("sub_1C0D70").hand, fc("sub_1C0D70").recomp, {task, 0, 0, 0}, 2, "sub_1C0D70 stop", hw,
                                [work](Machine& mm) {
                                    write_rw_slots(mm);
                                    w32(mm, work + game::f6::wall::kState, 1);
                                },
                                absent);
        CHECK(v0_of(sp.hw) == -1);
        absent.clear();
        sp = run_pair_si_absent(m, base, fc("sub_1C1E20").hand, fc("sub_1C1E20").recomp, {task, 0, 0, 0}, 3, "sub_1C1E20", hw,
                                [](Machine& mm) { write_rw_slots(mm); }, absent);
        CHECK(sp.recomp->si.calls_to(kRwSlotFns[1]) >= 1);  // the work freed (RwFree)
        absent.clear();
        const u32 unit = r32(m, work + game::f6::wall::kTarget);
        sp = run_pair_si_absent(m, base, fc("sub_1C1F30").hand, fc("sub_1C1F30").recomp, {0, unit, 0, 0}, 4, "sub_1C1F30", hw,
                                [](Machine& mm) { write_rw_slots(mm); }, absent);
        const u32 made = static_cast<u32>(v0_of(sp.hw));
        CHECK(made != 0u);
        if (made) CHECK(r32(m, r32(m, made + game::f6::task::kWork) + game::f6::wall::kTarget) == unit);
        ++runs;
    }
    if (runs == 0) MESSAGE("SKIP: no snapshot with a trans wall CTL task");
}

// The party finish step: with every party unit placed (climb, b_6700) nothing is left to do -> 1.
TEST_CASE("game(field6 fldrc): the party finish step on placed parties (stand-ins)") {
    const HwCheck hw = whole_ram_check();
    for (const char* snap : {"climb_ref_17000", "b_6700"}) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        INFO(snap);
        std::vector<u32> absent;
        SiPair sp = run_pair_si_absent(m, base, fc("sub_1CE960").hand, fc("sub_1CE960").recomp, {0, 0, 0, 0}, 1, "sub_1CE960", hw,
                                       [](Machine& mm) { write_rw_slots(mm); }, absent);
        CHECK(v0_of(sp.hw) == 1);
    }
}

#else

TEST_CASE("game(field6 fldrc): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
