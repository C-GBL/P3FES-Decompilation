// Pair tests of slice libs1, libmc2's write-cluster cache, superblock I/O, bad-block checks, core socket helpers and
// blocking API (game/src/lib/libs1_mc2.cpp), through tests/game/libs1_util.h. The card is the battle route's image
// served at the core layer (each world its own copy, the two compared after every pair), the library state the battle
// snapshot b_5800's. The async requests and sceMc2Sync2 (kernel semaphores), _sceMcCoreCreateSocket /
// _sceMcCoreDeleteSocket (DBC RPC) are recorders (Sync2 stores a result word). Rules checked: the write cache against a
// host model of its runs (start / append within one erase block up to 16 clusters / flush and restart) and the card
// image after the flushes; cached reads served from the cache, others from the card; the superblock round trip through
// page 0; the bad-block list; the format-time bad-block scan against a host scan of the card; the socket table helpers;
// each blocking call's request arguments, its result word, and an async error returned without waiting.
//@INCLUDES
#include "p3fes/game/libs1_mc2fat.h"
//@END
#include "libs1_util.h"

#include "p3fes/game/libs1_mc2.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <map>
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
void fn_sceMc2DeleteSocket_005133f8(EEContext&);  // generated body
void fn_sceMc2DeleteSocket_005133f8__recomp(EEContext&);  // recompiled
void fn_sceMc2Sync_00514928(EEContext&);  // generated body
void fn_sceMc2Sync_00514928__recomp(EEContext&);  // recompiled
void fn_sceMc2GetInfo_00514950(EEContext&);  // generated body
void fn_sceMc2GetInfo_00514950__recomp(EEContext&);  // recompiled
void fn_sceMc2Format_00514990(EEContext&);  // generated body
void fn_sceMc2Format_00514990__recomp(EEContext&);  // recompiled
void fn_sceMc2Unformat_005149d0(EEContext&);  // generated body
void fn_sceMc2Unformat_005149d0__recomp(EEContext&);  // recompiled
void fn_sceMc2ReadFile_00514a10(EEContext&);  // generated body
void fn_sceMc2ReadFile_00514a10__recomp(EEContext&);  // recompiled
void fn_sceMc2WriteFile_00514a50(EEContext&);  // generated body
void fn_sceMc2WriteFile_00514a50__recomp(EEContext&);  // recompiled
void fn_sceMc2ReadFastFile_00514a90(EEContext&);  // generated body
void fn_sceMc2ReadFastFile_00514a90__recomp(EEContext&);  // recompiled
void fn_sceMc2WriteFastFile_00514ad0(EEContext&);  // generated body
void fn_sceMc2WriteFastFile_00514ad0__recomp(EEContext&);  // recompiled
void fn_sceMc2CreateFile_00514b10(EEContext&);  // generated body
void fn_sceMc2CreateFile_00514b10__recomp(EEContext&);  // recompiled
void fn_sceMc2Delete_00514b50(EEContext&);  // generated body
void fn_sceMc2Delete_00514b50__recomp(EEContext&);  // recompiled
void fn_sceMc2Rename_00514b90(EEContext&);  // generated body
void fn_sceMc2Rename_00514b90__recomp(EEContext&);  // recompiled
void fn_sceMc2Mkdir_00514bd0(EEContext&);  // generated body
void fn_sceMc2Mkdir_00514bd0__recomp(EEContext&);  // recompiled
void fn_sceMc2Chdir_00514c10(EEContext&);  // generated body
void fn_sceMc2Chdir_00514c10__recomp(EEContext&);  // recompiled
void fn_sceMc2GetDir_00514c50(EEContext&);  // generated body
void fn_sceMc2GetDir_00514c50__recomp(EEContext&);  // recompiled
void fn_sceMc2Chmod_00514c90(EEContext&);  // generated body
void fn_sceMc2Chmod_00514c90__recomp(EEContext&);  // recompiled
void fn_sceMc2SearchFile_00514cd0(EEContext&);  // generated body
void fn_sceMc2SearchFile_00514cd0__recomp(EEContext&);  // recompiled
void fn_sceMc2GetEntSpace_00514d10(EEContext&);  // generated body
void fn_sceMc2GetEntSpace_00514d10__recomp(EEContext&);  // recompiled
void fn__sceMcpInit_0051a140(EEContext&);  // generated body
void fn__sceMcpInit_0051a140__recomp(EEContext&);  // recompiled
void fn__sceMcpGetCardSpec_0051a180(EEContext&);  // generated body
void fn__sceMcpGetCardSpec_0051a180__recomp(EEContext&);  // recompiled
void fn__sceMcpCheckNewCard_0051a1a0(EEContext&);  // generated body
void fn__sceMcpCheckNewCard_0051a1a0__recomp(EEContext&);  // recompiled
void fn__sceMcpAuthentication_0051a1c0(EEContext&);  // generated body
void fn__sceMcpAuthentication_0051a1c0__recomp(EEContext&);  // recompiled
void fn__sceMcpReadSysInfo_0051a1e0(EEContext&);  // generated body
void fn__sceMcpReadSysInfo_0051a1e0__recomp(EEContext&);  // recompiled
void fn__sceMcpWriteSysInfo_0051a2f8(EEContext&);  // generated body
void fn__sceMcpWriteSysInfo_0051a2f8__recomp(EEContext&);  // recompiled
void fn__sceMcpReadClust_0051a418(EEContext&);  // generated body
void fn__sceMcpReadClust_0051a418__recomp(EEContext&);  // recompiled
void fn__sceMcpWriteClust_0051a458(EEContext&);  // generated body
void fn__sceMcpWriteClust_0051a458__recomp(EEContext&);  // recompiled
void fn__sceMcpFlushCache_0051a498(EEContext&);  // generated body
void fn__sceMcpFlushCache_0051a498__recomp(EEContext&);  // recompiled
void fn__sceMcpWriteUserClustOnCache_0051a508(EEContext&);  // generated body
void fn__sceMcpWriteUserClustOnCache_0051a508__recomp(EEContext&);  // recompiled
void fn__sceMcpReadUserClustOnCache_0051a8a0(EEContext&);  // generated body
void fn__sceMcpReadUserClustOnCache_0051a8a0__recomp(EEContext&);  // recompiled
void fn__sceMcpReadUserClust_0051a9e0(EEContext&);  // generated body
void fn__sceMcpReadUserClust_0051a9e0__recomp(EEContext&);  // recompiled
void fn__sceMcpReadUserClustFast_0051aa00(EEContext&);  // generated body
void fn__sceMcpReadUserClustFast_0051aa00__recomp(EEContext&);  // recompiled
void fn__sceMcpWriteUserClustFast_0051aa48(EEContext&);  // generated body
void fn__sceMcpWriteUserClustFast_0051aa48__recomp(EEContext&);  // recompiled
void fn__sceMcpWriteUserClust_0051aa90(EEContext&);  // generated body
void fn__sceMcpWriteUserClust_0051aa90__recomp(EEContext&);  // recompiled
void fn__sceMcpIsSpeckOutBlock_0051ab08(EEContext&);  // generated body
void fn__sceMcpIsSpeckOutBlock_0051ab08__recomp(EEContext&);  // recompiled
void fn__sceMcpIsSpeckOutClust_0051ab50(EEContext&);  // generated body
void fn__sceMcpIsSpeckOutClust_0051ab50__recomp(EEContext&);  // recompiled
void fn__sceMcpMakeSpecoutBlock_0051ab98(EEContext&);  // generated body
void fn__sceMcpMakeSpecoutBlock_0051ab98__recomp(EEContext&);  // recompiled
void fn__sceMcCoreSetWriteBackHole_0051af70(EEContext&);  // generated body
void fn__sceMcCoreSetWriteBackHole_0051af70__recomp(EEContext&);  // recompiled
void fn__sceMcCoreSetCardSpec_0051af98(EEContext&);  // generated body
void fn__sceMcCoreSetCardSpec_0051af98__recomp(EEContext&);  // recompiled
void fn__sceMcCoreReadPage_0051b8d0(EEContext&);  // generated body
void fn__sceMcCoreReadPage_0051b8d0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreCheckSocket_0051c250(EEContext&);  // generated body
void fn__sceMcCoreCheckSocket_0051c250__recomp(EEContext&);  // recompiled
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8(EEContext&);  // generated body
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8__recomp(EEContext&);  // recompiled
void fn__sceMcCoreChangeSocketTypeMc2Dbc_0051c330(EEContext&);  // generated body
void fn__sceMcCoreChangeSocketTypeMc2Dbc_0051c330__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using p3fes::game_test::libs1::Case;

const Case kCases[] = {
    {"sceMc2DeleteSocket", 0x5133F8, &recomp_gen::fn_sceMc2DeleteSocket_005133f8, &recomp_gen::fn_sceMc2DeleteSocket_005133f8__recomp},
    {"sceMc2Sync", 0x514928, &recomp_gen::fn_sceMc2Sync_00514928, &recomp_gen::fn_sceMc2Sync_00514928__recomp},
    {"sceMc2GetInfo", 0x514950, &recomp_gen::fn_sceMc2GetInfo_00514950, &recomp_gen::fn_sceMc2GetInfo_00514950__recomp},
    {"sceMc2Format", 0x514990, &recomp_gen::fn_sceMc2Format_00514990, &recomp_gen::fn_sceMc2Format_00514990__recomp},
    {"sceMc2Unformat", 0x5149D0, &recomp_gen::fn_sceMc2Unformat_005149d0, &recomp_gen::fn_sceMc2Unformat_005149d0__recomp},
    {"sceMc2ReadFile", 0x514A10, &recomp_gen::fn_sceMc2ReadFile_00514a10, &recomp_gen::fn_sceMc2ReadFile_00514a10__recomp},
    {"sceMc2WriteFile", 0x514A50, &recomp_gen::fn_sceMc2WriteFile_00514a50, &recomp_gen::fn_sceMc2WriteFile_00514a50__recomp},
    {"sceMc2ReadFastFile", 0x514A90, &recomp_gen::fn_sceMc2ReadFastFile_00514a90, &recomp_gen::fn_sceMc2ReadFastFile_00514a90__recomp},
    {"sceMc2WriteFastFile", 0x514AD0, &recomp_gen::fn_sceMc2WriteFastFile_00514ad0, &recomp_gen::fn_sceMc2WriteFastFile_00514ad0__recomp},
    {"sceMc2CreateFile", 0x514B10, &recomp_gen::fn_sceMc2CreateFile_00514b10, &recomp_gen::fn_sceMc2CreateFile_00514b10__recomp},
    {"sceMc2Delete", 0x514B50, &recomp_gen::fn_sceMc2Delete_00514b50, &recomp_gen::fn_sceMc2Delete_00514b50__recomp},
    {"sceMc2Rename", 0x514B90, &recomp_gen::fn_sceMc2Rename_00514b90, &recomp_gen::fn_sceMc2Rename_00514b90__recomp},
    {"sceMc2Mkdir", 0x514BD0, &recomp_gen::fn_sceMc2Mkdir_00514bd0, &recomp_gen::fn_sceMc2Mkdir_00514bd0__recomp},
    {"sceMc2Chdir", 0x514C10, &recomp_gen::fn_sceMc2Chdir_00514c10, &recomp_gen::fn_sceMc2Chdir_00514c10__recomp},
    {"sceMc2GetDir", 0x514C50, &recomp_gen::fn_sceMc2GetDir_00514c50, &recomp_gen::fn_sceMc2GetDir_00514c50__recomp},
    {"sceMc2Chmod", 0x514C90, &recomp_gen::fn_sceMc2Chmod_00514c90, &recomp_gen::fn_sceMc2Chmod_00514c90__recomp},
    {"sceMc2SearchFile", 0x514CD0, &recomp_gen::fn_sceMc2SearchFile_00514cd0, &recomp_gen::fn_sceMc2SearchFile_00514cd0__recomp},
    {"sceMc2GetEntSpace", 0x514D10, &recomp_gen::fn_sceMc2GetEntSpace_00514d10, &recomp_gen::fn_sceMc2GetEntSpace_00514d10__recomp},
    {"_sceMcpInit", 0x51A140, &recomp_gen::fn__sceMcpInit_0051a140, &recomp_gen::fn__sceMcpInit_0051a140__recomp},
    {"_sceMcpGetCardSpec", 0x51A180, &recomp_gen::fn__sceMcpGetCardSpec_0051a180, &recomp_gen::fn__sceMcpGetCardSpec_0051a180__recomp},
    {"_sceMcpCheckNewCard", 0x51A1A0, &recomp_gen::fn__sceMcpCheckNewCard_0051a1a0, &recomp_gen::fn__sceMcpCheckNewCard_0051a1a0__recomp},
    {"_sceMcpAuthentication", 0x51A1C0, &recomp_gen::fn__sceMcpAuthentication_0051a1c0, &recomp_gen::fn__sceMcpAuthentication_0051a1c0__recomp},
    {"_sceMcpReadSysInfo", 0x51A1E0, &recomp_gen::fn__sceMcpReadSysInfo_0051a1e0, &recomp_gen::fn__sceMcpReadSysInfo_0051a1e0__recomp},
    {"_sceMcpWriteSysInfo", 0x51A2F8, &recomp_gen::fn__sceMcpWriteSysInfo_0051a2f8, &recomp_gen::fn__sceMcpWriteSysInfo_0051a2f8__recomp},
    {"_sceMcpReadClust", 0x51A418, &recomp_gen::fn__sceMcpReadClust_0051a418, &recomp_gen::fn__sceMcpReadClust_0051a418__recomp},
    {"_sceMcpWriteClust", 0x51A458, &recomp_gen::fn__sceMcpWriteClust_0051a458, &recomp_gen::fn__sceMcpWriteClust_0051a458__recomp},
    {"_sceMcpFlushCache", 0x51A498, &recomp_gen::fn__sceMcpFlushCache_0051a498, &recomp_gen::fn__sceMcpFlushCache_0051a498__recomp},
    {"_sceMcpWriteUserClustOnCache", 0x51A508, &recomp_gen::fn__sceMcpWriteUserClustOnCache_0051a508, &recomp_gen::fn__sceMcpWriteUserClustOnCache_0051a508__recomp},
    {"_sceMcpReadUserClustOnCache", 0x51A8A0, &recomp_gen::fn__sceMcpReadUserClustOnCache_0051a8a0, &recomp_gen::fn__sceMcpReadUserClustOnCache_0051a8a0__recomp},
    {"_sceMcpReadUserClust", 0x51A9E0, &recomp_gen::fn__sceMcpReadUserClust_0051a9e0, &recomp_gen::fn__sceMcpReadUserClust_0051a9e0__recomp},
    {"_sceMcpReadUserClustFast", 0x51AA00, &recomp_gen::fn__sceMcpReadUserClustFast_0051aa00, &recomp_gen::fn__sceMcpReadUserClustFast_0051aa00__recomp},
    {"_sceMcpWriteUserClustFast", 0x51AA48, &recomp_gen::fn__sceMcpWriteUserClustFast_0051aa48, &recomp_gen::fn__sceMcpWriteUserClustFast_0051aa48__recomp},
    {"_sceMcpWriteUserClust", 0x51AA90, &recomp_gen::fn__sceMcpWriteUserClust_0051aa90, &recomp_gen::fn__sceMcpWriteUserClust_0051aa90__recomp},
    {"_sceMcpIsSpeckOutBlock", 0x51AB08, &recomp_gen::fn__sceMcpIsSpeckOutBlock_0051ab08, &recomp_gen::fn__sceMcpIsSpeckOutBlock_0051ab08__recomp},
    {"_sceMcpIsSpeckOutClust", 0x51AB50, &recomp_gen::fn__sceMcpIsSpeckOutClust_0051ab50, &recomp_gen::fn__sceMcpIsSpeckOutClust_0051ab50__recomp},
    {"_sceMcpMakeSpecoutBlock", 0x51AB98, &recomp_gen::fn__sceMcpMakeSpecoutBlock_0051ab98, &recomp_gen::fn__sceMcpMakeSpecoutBlock_0051ab98__recomp},
    {"_sceMcCoreSetWriteBackHole", 0x51AF70, &recomp_gen::fn__sceMcCoreSetWriteBackHole_0051af70, &recomp_gen::fn__sceMcCoreSetWriteBackHole_0051af70__recomp},
    {"_sceMcCoreSetCardSpec", 0x51AF98, &recomp_gen::fn__sceMcCoreSetCardSpec_0051af98, &recomp_gen::fn__sceMcCoreSetCardSpec_0051af98__recomp},
    {"_sceMcCoreReadPage", 0x51B8D0, &recomp_gen::fn__sceMcCoreReadPage_0051b8d0, &recomp_gen::fn__sceMcCoreReadPage_0051b8d0__recomp},
    {"_sceMcCoreCheckSocket", 0x51C250, &recomp_gen::fn__sceMcCoreCheckSocket_0051c250, &recomp_gen::fn__sceMcCoreCheckSocket_0051c250__recomp},
    {"_sceMcCoreChangeSocketTypeDbc2Mc", 0x51C2E8, &recomp_gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8, &recomp_gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8__recomp},
    {"_sceMcCoreChangeSocketTypeMc2Dbc", 0x51C330, &recomp_gen::fn__sceMcCoreChangeSocketTypeMc2Dbc_0051c330, &recomp_gen::fn__sceMcCoreChangeSocketTypeMc2Dbc_0051c330__recomp},
};

using namespace p3fes::game_test::libs1;
namespace mc = p3fes::game::libs1::mc2;

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kBuf = 0x01830000u;
constexpr u32 kRec = 0x01840000u;
constexpr u32 kSync2 = 0x514858u, kCoreCreateSocket = 0x51C130u, kCoreDeleteSocket = 0x51C280u;

const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }

struct Api {
    const char* sync;
    u32 async;
};
const Api kApi[] = {
    {"sceMc2GetInfo", 0x5136F8u},      {"sceMc2Format", 0x513598u},    {"sceMc2Unformat", 0x513648u},
    {"sceMc2ReadFile", 0x513968u},     {"sceMc2WriteFile", 0x513CC8u}, {"sceMc2ReadFastFile", 0x513A88u},
    {"sceMc2WriteFastFile", 0x513BA8u}, {"sceMc2CreateFile", 0x513DE8u}, {"sceMc2Delete", 0x513EE0u},
    {"sceMc2Rename", 0x5143F0u},       {"sceMc2Mkdir", 0x5140F8u},     {"sceMc2Chdir", 0x5141F0u},
    {"sceMc2GetDir", 0x513FC8u},       {"sceMc2Chmod", 0x5142F0u},     {"sceMc2SearchFile", 0x5137B8u},
    {"sceMc2GetEntSpace", 0x514510u},
};

struct Run {
    std::vector<u8> master;
    std::vector<std::shared_ptr<Card>> made;
    u64 async_result = 0;
};
Setup setup_of(std::shared_ptr<Run> run) {
    return [run](StandInWorld& w) {
        auto card = std::make_shared<Card>();
        card->img = run->master;
        run->made.push_back(card);
        install_card(w, card, 1, 1);
        for (const Api& a : kApi) w.si.install_recorder(a.async, std::string(a.sync) + "Async", run->async_result);
        w.si.install(kSync2, "sceMc2Sync2", [](EEContext& ctx, StandIns&, StandInCall& c) {
            const u32 out = static_cast<u32>(c.args[2]);
            if (out) {
                const u32 v = 0x5A5A0000u | static_cast<u32>(c.args[0]);
                std::memcpy(gptr(ctx, out), &v, 4);
            }
            c.v0 = 1;
        });
        w.si.install_recorder(kCoreCreateSocket, "_sceMcCoreCreateSocket", 1);
        w.si.install_recorder(kCoreDeleteSocket, "_sceMcCoreDeleteSocket", 1);
    };
}
hgp::Run mpair(Machine& m, std::shared_ptr<Run> run, const char* fn, const Args& a, u32& seed, const std::string& what, const HwCheck& hw = {}) {
    run->made.clear();
    const hgp::Run r = pair(m, C(fn), a, seed++, what, setup_of(run), hw);
    REQUIRE(run->made.size() == 2);
    CHECK(run->made[0]->img == run->made[1]->img);
    CHECK(run->made[0]->ops == run->made[1]->ops);
    run->master = run->made[1]->img;
    return r;
}
bool load_battle_state(Machine& m, std::vector<u8>& card) {
    const std::vector<u8> snap = read_snapshot("b_5800");
    card = route_card("tartarus.ps2");
    if (snap.empty() || card.empty()) return false;
    copy_from_snapshot(m, snap, 0x7827D8u, 0x400);
    copy_from_snapshot(m, snap, 0x96F100u, 0x100);
    copy_from_snapshot(m, snap, 0x97B700u, 0xA900u);
    return std::memcmp(card.data(), m.mem.main_ram() + mc::kSuperblock, 340) == 0;
}
std::vector<u8> card_cluster(const std::vector<u8>& img, u32 abs) {
    std::vector<u8> v(1024);
    for (u32 p = 0; p < 2; ++p) std::memcpy(v.data() + 512 * p, img.data() + static_cast<std::size_t>(abs * 2 + p) * kRawPage, 512);
    return v;
}

}  // namespace

TEST_CASE("game(libs1_mc2): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    auto run = std::make_shared<Run>();
    run->master.assign(64 * kRawPage, 0xFF);
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, 24, setup_of(run), true);
}

TEST_CASE("game(libs1_mc2): the write-cluster cache, cached reads, the superblock and bad blocks on the battle card") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    auto run = std::make_shared<Run>();
    if (!load_battle_state(*m, run->master)) {
        MESSAGE("SKIP: b_5800 / tartarus.ps2 not found or not the same card");
        return;
    }
    u32 seed = 1;
    const u32 cache = mc::kClustCache;  // port 0
    const u32 alloc = r32(*m, mc::kSuperblock + mc::kAllocOffset);
    // a host model of the cache's run
    struct Model { s32 first = -1, last = 0, block = 0, count = 0; } model;
    std::map<u32, std::vector<u8>> written;  // user cluster -> data (what the card must hold after the flushes)
    CHECK(static_cast<s32>(r32(*m, cache)) == -1);
    std::mt19937 rng{11};
    u32 next = 7000;  // user clusters far up the card
    for (int step = 0; step < 60; ++step) {
        const u32 k = rng() % 6;
        u32 cl = k == 0 ? 7000 + rng() % 400 : next;
        next = cl + 1;
        const u32 n = 1 + rng() % 3;
        for (u32 i = 0; i < 1024 * n; i += 4) w32(*m, kBuf + i, (cl << 12) ^ i ^ static_cast<u32>(step));
        const auto r = mpair(*m, run, "_sceMcpWriteUserClust", {0, kBuf, cl, n}, seed, "WriteUserClust " + std::to_string(cl) + " x" + std::to_string(n));
        CHECK(v0_of(r) == 1);
        for (u32 i = 0; i < n; ++i) {
            const s32 abs = static_cast<s32>(cl + i + alloc);
            const s32 block = abs * 2 / 16;
            if (model.first == -1) model = {abs, abs, block, 0};
            else if (abs == model.last + 1 && model.count < 16 && block == model.block) model.last = abs;
            else model = {abs, abs, block, 0};
            ++model.count;
            std::vector<u8> d(1024);  // every cluster of the call gets the buffer's FIRST 1,024 bytes (finding: the
            std::memcpy(d.data(), m->mem.main_ram() + kBuf, 1024);  // loop advances the cluster, never the buffer)
            written[cl + i] = d;
        }
        CHECK(static_cast<s32>(r32(*m, cache)) == model.first);
        CHECK(static_cast<s32>(r32(*m, cache + 4)) == model.last);
        CHECK(static_cast<s32>(r32(*m, cache + 8)) == model.block);
        CHECK(static_cast<s32>(r32(*m, cache + 12)) == model.count);
        // a cached cluster reads from the cache, an older one from the card (after its flush)
        const u32 probe = rng() % 2 ? static_cast<u32>(model.last) - alloc : 7000 + rng() % 400;
        wzero(*m, kBuf + 0x8000, 1024);
        mpair(*m, run, "_sceMcpReadUserClust", {0, kBuf + 0x8000, probe, 1}, seed, "ReadUserClust " + std::to_string(probe));
        std::vector<u8> got(1024);
        std::memcpy(got.data(), m->mem.main_ram() + kBuf + 0x8000, 1024);
        const s32 pabs = static_cast<s32>(probe + alloc);
        const bool in_cache = model.first != -1 && pabs >= model.first && pabs < model.first + model.count;
        if (in_cache && got != written[probe]) {
            u32 g0, w0, c0;
            std::memcpy(&g0, got.data(), 4);
            std::memcpy(&w0, written[probe].data(), 4);
            const auto cardc = card_cluster(run->master, probe + alloc);
            std::memcpy(&c0, cardc.data(), 4);
            MESSAGE("probe " << probe << " step " << step << ": got " << std::hex << g0 << " written " << w0 << " card " << c0 << " first "
                             << model.first << " count " << model.count << std::dec);
        }
        if (in_cache) CHECK(got == written[probe]);
        else CHECK(got == card_cluster(run->master, probe + alloc));
    }
    auto r = mpair(*m, run, "_sceMcpFlushCache", {0}, seed, "FlushCache");
    CHECK(v0_of(r) != 0);  // what the cluster write returned: the pages written
    CHECK(static_cast<s32>(r32(*m, cache)) == -1);
    CHECK(r32(*m, cache + 12) == 0);
    int checked = 0;
    for (const auto& [cl, d] : written) {
        CHECK(card_cluster(run->master, cl + alloc) == d);
        ++checked;
    }
    // the fast paths: whole clusters straight to / from the card
    for (u32 i = 0; i < 2048; i += 4) w32(*m, kBuf + i, 0xC0DE0000u + i);
    mpair(*m, run, "_sceMcpWriteUserClustFast", {0, kBuf, 7600, 2}, seed, "WriteUserClustFast");
    wzero(*m, kBuf + 0x8000, 2048);
    mpair(*m, run, "_sceMcpReadUserClustFast", {0, kBuf + 0x8000, 7600, 2}, seed, "ReadUserClustFast");
    CHECK(std::memcmp(m->mem.main_ram() + kBuf, m->mem.main_ram() + kBuf + 0x8000, 2048) == 0);
    // the superblock: page 0 -> the copy, the copy -> page 0 (388 bytes, then 0xFF)
    w32(*m, mc::kSuperblock + 300, 0x11223344u);  // a stray word the read must restore
    mpair(*m, run, "_sceMcpReadSysInfo", {0}, seed, "ReadSysInfo");
    CHECK(std::memcmp(m->mem.main_ram() + mc::kSuperblock, run->master.data(), 388) == 0);
    w32(*m, mc::kSuperblock + 0x150, 0x0302u);  // change the card type / flags bytes in the copy
    mpair(*m, run, "_sceMcpWriteSysInfo", {0}, seed, "WriteSysInfo");
    CHECK(std::memcmp(m->mem.main_ram() + mc::kSuperblock, run->master.data(), 388) == 0);
    for (u32 i = 388; i < 512; ++i) CHECK(run->master[i] == 0xFF);
    // the bad-block list
    for (u32 i = 0; i < 32; ++i) w32(*m, mc::kSuperblock + mc::kBadBlocks + 4 * i, i < 3 ? 100 + 7 * i : 0xFFFFFFFFu);
    for (u32 b : {99u, 100u, 107u, 114u, 121u, 0u}) {
        r = mpair(*m, run, "_sceMcpIsSpeckOutBlock", {0, b}, seed, "IsSpeckOutBlock " + std::to_string(b));
        CHECK(v0_of(r) == ((b == 100 || b == 107 || b == 114) ? 1u : 0u));
    }
    for (u32 c : {800u, 799u, 807u, 856u, 863u, 864u}) {  // block = cluster * 2 / 16
        r = mpair(*m, run, "_sceMcpIsSpeckOutClust", {0, c}, seed, "IsSpeckOutClust " + std::to_string(c));
        const u32 b = c * 2 / 16;
        CHECK(v0_of(r) == ((b == 100 || b == 107 || b == 114) ? 1u : 0u));
    }
    // the format-time scan: blocks (from 1) whose first 2,048 bytes are not all 0xFF, at most 16
    const u32 spec = kRec;
    w32(*m, spec, 512);
    w32(*m, spec + 4, 16);
    w32(*m, spec + 8, 16 * 24);  // 24 blocks: an empty block costs 512 loop turns, within the harness's check-point budget
    for (u32 i = 0; i < 16; ++i) w32(*m, kRec + 0x100 + 4 * i, 0xEEEEEEEEu);
    r = mpair(*m, run, "_sceMcpMakeSpecoutBlock", {0, spec, kRec + 0x100}, seed, "MakeSpecoutBlock");
    CHECK(!r.stopped);
    std::vector<u32> host;
    for (u32 b = 1; b < 24 && host.size() < 16; ++b) {
        bool used = false;
        for (u32 p = 0; p < 4 && !used; ++p)
            for (u32 i = 0; i < 512 && !used; ++i) used = run->master[static_cast<std::size_t>(b * 16 + p) * kRawPage + i] != 0xFF;
        if (used) host.push_back(b);
    }
    for (u32 i = 0; i < host.size(); ++i) CHECK(r32(*m, kRec + 0x100 + 4 * i) == host[i]);
    MESSAGE(checked << " clusters checked after the flushes; scan found " << host.size() << " blocks; pairs " << counts().pairs << ", stopped "
                    << counts().stops);
}

TEST_CASE("game(libs1_mc2): core socket helpers, sockets and the blocking API") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    auto run = std::make_shared<Run>();
    run->master.assign(64 * kRawPage, 0xFF);
    u32 seed = 500;
    const u32 t = mc::kCoreSockets;
    for (u32 used0 : {0u, 1u})
        for (u32 used1 : {0u, 1u}) {
            wzero(*m, t, 72);
            w32(*m, t, used0);
            w32(*m, t + 4, 0x30);
            w32(*m, t + 36, used1);
            w32(*m, t + 40, 0x31);
            for (u64 s : {0ull, 1ull, 2ull, ~0ull}) {
                auto r = mpair(*m, run, "_sceMcCoreCheckSocket", {s}, seed, "CheckSocket");
                CHECK(v0_of(r) == ((s == 0 && used0) || (s == 1 && used1) ? 1u : 0u));
            }
            for (u64 d : {0x30ull, 0x31ull, 0x32ull}) {
                auto r = mpair(*m, run, "_sceMcCoreChangeSocketTypeDbc2Mc", {d}, seed, "Dbc2Mc");
                const s64 want = d == 0x30 && used0 ? 0 : d == 0x31 && used1 ? 1 : -1;
                CHECK(static_cast<s64>(v0_of(r)) == want);
            }
            for (u32 s : {0u, 1u}) {
                auto r = mpair(*m, run, "_sceMcCoreChangeSocketTypeMc2Dbc", {s}, seed, "Mc2Dbc");
                CHECK(v0s(r) == ((s == 0 ? used0 : used1) ? static_cast<s32>(0x30 + s) : -1));
            }
        }
    mpair(*m, run, "_sceMcCoreSetWriteBackHole", {1, 1022, 1023}, seed, "SetWriteBackHole");
    CHECK(r32(*m, t + 36 + 28) == 1022);
    CHECK(r32(*m, t + 36 + 32) == 1023);
    for (u32 i = 0; i < 4; ++i) w32(*m, kRec + 4 * i, 0x100u * (i + 1));
    mpair(*m, run, "_sceMcCoreSetCardSpec", {1, kRec}, seed, "SetCardSpec");
    for (u32 i = 0; i < 4; ++i) CHECK(r32(*m, t + 36 + 8 + 4 * i) == 0x100u * (i + 1));
    w32(*m, t + 8, 512);
    w32(*m, t + 20, 1);  // ECC on
    mpair(*m, run, "_sceMcCoreReadPage", {0, kBuf, 5, 2}, seed, "ReadPage");
    REQUIRE(last_log().calls_to(kReadPage2) == 1);
    CHECK(last_log().log.back().args[4] == 1);  // the socket's ECC flag in $t0
    // sockets (sceMc2CreateSocket stays recompiled: test_field8_sys's H_Memcard_Init pair needs it absent)
    w32(*m, 0x7827D8u, 1);
    w32(*m, t + 36, 1);
    w32(*m, t + 40, 0x44);
    w32(*m, 0x96F144u, 0);
    auto r = mpair(*m, run, "sceMc2DeleteSocket", {0x44}, seed, "DeleteSocket");
    CHECK(v0_of(r) == 0);
    CHECK(last_log().calls_to(kCoreDeleteSocket) == 1);
    w32(*m, 0x96F144u, 1);
    CHECK(v0_of(mpair(*m, run, "sceMc2DeleteSocket", {0x44}, seed, "DeleteSocket busy")) == sx(0x81010010u));
    w32(*m, 0x96F144u, 0);
    CHECK(v0_of(mpair(*m, run, "sceMc2DeleteSocket", {0x99}, seed, "DeleteSocket unknown")) == sx(0x81018002u));
    // Sync: sceMc2Sync2 with mode 0 (CheckAsync, mode 1, stays recompiled: test_field8_sys stands it in)
    mpair(*m, run, "sceMc2Sync", {kRec, kRec + 4}, seed, "Sync");
    CHECK(last_log().log.back().args[0] == 0);
    // the blocking calls: the async request with the caller's arguments, then a wait whose result word is returned
    for (const Api& a : kApi) {
        const Args args{0x40, kRec + 0x10, kRec + 0x20, 0x123};
        run->async_result = 0;
        r = mpair(*m, run, a.sync, args, seed, a.sync, hw_in({{GPR_T0, 0x777}, {GPR_T1, 0x888}}));
        const auto& log = last_log().log;
        REQUIRE(log.size() == 2);
        CHECK(log[0].va == a.async);
        CHECK(log[0].args[0] == 0x40);
        CHECK(log[0].args[1] == kRec + 0x10);
        CHECK(log[1].va == kSync2);
        CHECK(log[1].args[0] == 0);
        CHECK(static_cast<u32>(v0_of(r)) == 0x5A5A0000u);
        run->async_result = 0x81010010u;  // busy: returned at once, no wait
        r = mpair(*m, run, a.sync, args, seed, std::string(a.sync) + " busy");
        CHECK(last_log().log.size() == 1);
        CHECK(static_cast<u32>(v0_of(r)) == 0x81010010u);
    }
    run->async_result = 0;
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

#else

TEST_CASE("game(libs1_mc2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
