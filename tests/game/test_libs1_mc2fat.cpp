// Pair tests of slice libs1, libmc2's FAT layer (game/src/lib/libs1_mc2fat.cpp), through tests/game/libs1_util.h: the
// memory card is the battle route's card image (extracted/_ours/cards/tartarus.ps2) served at the core layer, and the
// library state is the battle route's snapshot b_5800 (superblock copy, FAT / indirect caches, write-cluster cache,
// core sockets: the card the route just loaded its save from). Each world gets its own copy of the card; a pair's two
// cards must be equal, and a sequence of pairs carries the card forward. Documented-rule checks against a host reader
// of the card (public card format: superblock, indirect FAT, 1,024-byte clusters, 512-byte entries): every root and save
// directory entry looked up by path, the files read whole and at random offsets (both read paths), the directory
// listings, the FAT entries and chains, the free-cluster count and search, the card information; then a write sequence
// on the card -- make a directory, create a file, write / extend it (both write paths), set attributes, rename, read
// back, delete -- each step checked by re-reading the resulting card image on the host.
#include "libs1_util.h"

#include "p3fes/game/libs1_mc2fat.h"

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
void fn__sceMcFatInit_005153a0(EEContext&);  // generated body
void fn__sceMcFatInit_005153a0__recomp(EEContext&);  // recompiled
void fn__sceMcFatInit2_00515400(EEContext&);  // generated body
void fn__sceMcFatInit2_00515400__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetFatClustNum_00515468(EEContext&);  // generated body
void fn__sceMcFatGetFatClustNum_00515468__recomp(EEContext&);  // recompiled
void fn__sceMcFatFlushFatCache_00515588(EEContext&);  // generated body
void fn__sceMcFatFlushFatCache_00515588__recomp(EEContext&);  // recompiled
void fn__sceMcFatReadFatData_00515618(EEContext&);  // generated body
void fn__sceMcFatReadFatData_00515618__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetNextClust_00515730(EEContext&);  // generated body
void fn__sceMcFatGetNextClust_00515730__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetNextClustSelf_00515778(EEContext&);  // generated body
void fn__sceMcFatGetNextClustSelf_00515778__recomp(EEContext&);  // recompiled
void fn__sceMcFatWriteFatData_005157e0(EEContext&);  // generated body
void fn__sceMcFatWriteFatData_005157e0__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetFreeClust_00515910(EEContext&);  // generated body
void fn__sceMcFatGetFreeClust_00515910__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetFreeClustSize_00515a40(EEContext&);  // generated body
void fn__sceMcFatGetFreeClustSize_00515a40__recomp(EEContext&);  // recompiled
void fn__GetEntryByPos_00515b18(EEContext&);  // generated body
void fn__GetEntryByPos_00515b18__recomp(EEContext&);  // recompiled
void fn__fat_chain_trace_00515c98(EEContext&);  // generated body
void fn__fat_chain_trace_00515c98__recomp(EEContext&);  // recompiled
void fn__reset_problem_patch_00515d28(EEContext&);  // generated body
void fn__reset_problem_patch_00515d28__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetInfo_00515d80(EEContext&);  // generated body
void fn__sceMcFatGetInfo_00515d80__recomp(EEContext&);  // recompiled
void fn__sceMcFatUnFormat_00516a48(EEContext&);  // generated body
void fn__sceMcFatUnFormat_00516a48__recomp(EEContext&);  // recompiled
void fn__ConfInsert_00516b48(EEContext&);  // generated body
void fn__ConfInsert_00516b48__recomp(EEContext&);  // recompiled
void fn__CheckFileDescript_00516be8(EEContext&);  // generated body
void fn__CheckFileDescript_00516be8__recomp(EEContext&);  // recompiled
void fn__SearchEntry_00516c48(EEContext&);  // generated body
void fn__SearchEntry_00516c48__recomp(EEContext&);  // recompiled
void fn__SearchFile_00516ec0(EEContext&);  // generated body
void fn__SearchFile_00516ec0__recomp(EEContext&);  // recompiled
void fn__SetEntryByPos_00517310(EEContext&);  // generated body
void fn__SetEntryByPos_00517310__recomp(EEContext&);  // recompiled
void fn__GetFreeEntrySize_005174b8(EEContext&);  // generated body
void fn__GetFreeEntrySize_005174b8__recomp(EEContext&);  // recompiled
void fn__CreateEntry_005175e8(EEContext&);  // generated body
void fn__CreateEntry_005175e8__recomp(EEContext&);  // recompiled
void fn__ParentDirUpdate_00517ab8(EEContext&);  // generated body
void fn__ParentDirUpdate_00517ab8__recomp(EEContext&);  // recompiled
void fn__sceMcFatSearchFile_00517be8(EEContext&);  // generated body
void fn__sceMcFatSearchFile_00517be8__recomp(EEContext&);  // recompiled
void fn__sceMcFatCreateFile_00517cd8(EEContext&);  // generated body
void fn__sceMcFatCreateFile_00517cd8__recomp(EEContext&);  // recompiled
void fn__sceMcFatReadFile_00518268(EEContext&);  // generated body
void fn__sceMcFatReadFile_00518268__recomp(EEContext&);  // recompiled
void fn__sceMcFatReadFastFile_00518470(EEContext&);  // generated body
void fn__sceMcFatReadFastFile_00518470__recomp(EEContext&);  // recompiled
void fn__sceMcFatWriteFile_005187c0(EEContext&);  // generated body
void fn__sceMcFatWriteFile_005187c0__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetNextClustAlloc_00518da0(EEContext&);  // generated body
void fn__sceMcFatGetNextClustAlloc_00518da0__recomp(EEContext&);  // recompiled
void fn__sceMcFatWriteFastFile_00518e70(EEContext&);  // generated body
void fn__sceMcFatWriteFastFile_00518e70__recomp(EEContext&);  // recompiled
void fn__sceMcFatDeleteFile_005194f8(EEContext&);  // generated body
void fn__sceMcFatDeleteFile_005194f8__recomp(EEContext&);  // recompiled
void fn__sceMcFatChDir_00519728(EEContext&);  // generated body
void fn__sceMcFatChDir_00519728__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetDir_00519850(EEContext&);  // generated body
void fn__sceMcFatGetDir_00519850__recomp(EEContext&);  // recompiled
void fn__sceMcFatSetAttr_00519d70(EEContext&);  // generated body
void fn__sceMcFatSetAttr_00519d70__recomp(EEContext&);  // recompiled
void fn__sceMcFatRename_00519ef8(EEContext&);  // generated body
void fn__sceMcFatRename_00519ef8__recomp(EEContext&);  // recompiled
void fn__sceMcFatGetEntSpace_0051a078(EEContext&);  // generated body
void fn__sceMcFatGetEntSpace_0051a078__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using p3fes::game_test::libs1::Case;

const Case kCases[] = {
    {"_sceMcFatInit", 0x5153A0, &recomp_gen::fn__sceMcFatInit_005153a0, &recomp_gen::fn__sceMcFatInit_005153a0__recomp},
    {"_sceMcFatInit2", 0x515400, &recomp_gen::fn__sceMcFatInit2_00515400, &recomp_gen::fn__sceMcFatInit2_00515400__recomp},
    {"_sceMcFatGetFatClustNum", 0x515468, &recomp_gen::fn__sceMcFatGetFatClustNum_00515468, &recomp_gen::fn__sceMcFatGetFatClustNum_00515468__recomp},
    {"_sceMcFatFlushFatCache", 0x515588, &recomp_gen::fn__sceMcFatFlushFatCache_00515588, &recomp_gen::fn__sceMcFatFlushFatCache_00515588__recomp},
    {"_sceMcFatReadFatData", 0x515618, &recomp_gen::fn__sceMcFatReadFatData_00515618, &recomp_gen::fn__sceMcFatReadFatData_00515618__recomp},
    {"_sceMcFatGetNextClust", 0x515730, &recomp_gen::fn__sceMcFatGetNextClust_00515730, &recomp_gen::fn__sceMcFatGetNextClust_00515730__recomp},
    {"_sceMcFatGetNextClustSelf", 0x515778, &recomp_gen::fn__sceMcFatGetNextClustSelf_00515778, &recomp_gen::fn__sceMcFatGetNextClustSelf_00515778__recomp},
    {"_sceMcFatWriteFatData", 0x5157E0, &recomp_gen::fn__sceMcFatWriteFatData_005157e0, &recomp_gen::fn__sceMcFatWriteFatData_005157e0__recomp},
    {"_sceMcFatGetFreeClust", 0x515910, &recomp_gen::fn__sceMcFatGetFreeClust_00515910, &recomp_gen::fn__sceMcFatGetFreeClust_00515910__recomp},
    {"_sceMcFatGetFreeClustSize", 0x515A40, &recomp_gen::fn__sceMcFatGetFreeClustSize_00515a40, &recomp_gen::fn__sceMcFatGetFreeClustSize_00515a40__recomp},
    {"_GetEntryByPos", 0x515B18, &recomp_gen::fn__GetEntryByPos_00515b18, &recomp_gen::fn__GetEntryByPos_00515b18__recomp},
    {"_fat_chain_trace", 0x515C98, &recomp_gen::fn__fat_chain_trace_00515c98, &recomp_gen::fn__fat_chain_trace_00515c98__recomp},
    {"_reset_problem_patch", 0x515D28, &recomp_gen::fn__reset_problem_patch_00515d28, &recomp_gen::fn__reset_problem_patch_00515d28__recomp},
    {"_sceMcFatGetInfo", 0x515D80, &recomp_gen::fn__sceMcFatGetInfo_00515d80, &recomp_gen::fn__sceMcFatGetInfo_00515d80__recomp},
    {"_sceMcFatUnFormat", 0x516A48, &recomp_gen::fn__sceMcFatUnFormat_00516a48, &recomp_gen::fn__sceMcFatUnFormat_00516a48__recomp},
    {"_ConfInsert", 0x516B48, &recomp_gen::fn__ConfInsert_00516b48, &recomp_gen::fn__ConfInsert_00516b48__recomp},
    {"_CheckFileDescript", 0x516BE8, &recomp_gen::fn__CheckFileDescript_00516be8, &recomp_gen::fn__CheckFileDescript_00516be8__recomp},
    {"_SearchEntry", 0x516C48, &recomp_gen::fn__SearchEntry_00516c48, &recomp_gen::fn__SearchEntry_00516c48__recomp},
    {"_SearchFile", 0x516EC0, &recomp_gen::fn__SearchFile_00516ec0, &recomp_gen::fn__SearchFile_00516ec0__recomp},
    {"_SetEntryByPos", 0x517310, &recomp_gen::fn__SetEntryByPos_00517310, &recomp_gen::fn__SetEntryByPos_00517310__recomp},
    {"_GetFreeEntrySize", 0x5174B8, &recomp_gen::fn__GetFreeEntrySize_005174b8, &recomp_gen::fn__GetFreeEntrySize_005174b8__recomp},
    {"_CreateEntry", 0x5175E8, &recomp_gen::fn__CreateEntry_005175e8, &recomp_gen::fn__CreateEntry_005175e8__recomp},
    {"_ParentDirUpdate", 0x517AB8, &recomp_gen::fn__ParentDirUpdate_00517ab8, &recomp_gen::fn__ParentDirUpdate_00517ab8__recomp},
    {"_sceMcFatSearchFile", 0x517BE8, &recomp_gen::fn__sceMcFatSearchFile_00517be8, &recomp_gen::fn__sceMcFatSearchFile_00517be8__recomp},
    {"_sceMcFatCreateFile", 0x517CD8, &recomp_gen::fn__sceMcFatCreateFile_00517cd8, &recomp_gen::fn__sceMcFatCreateFile_00517cd8__recomp},
    {"_sceMcFatReadFile", 0x518268, &recomp_gen::fn__sceMcFatReadFile_00518268, &recomp_gen::fn__sceMcFatReadFile_00518268__recomp},
    {"_sceMcFatReadFastFile", 0x518470, &recomp_gen::fn__sceMcFatReadFastFile_00518470, &recomp_gen::fn__sceMcFatReadFastFile_00518470__recomp},
    {"_sceMcFatWriteFile", 0x5187C0, &recomp_gen::fn__sceMcFatWriteFile_005187c0, &recomp_gen::fn__sceMcFatWriteFile_005187c0__recomp},
    {"_sceMcFatGetNextClustAlloc", 0x518DA0, &recomp_gen::fn__sceMcFatGetNextClustAlloc_00518da0, &recomp_gen::fn__sceMcFatGetNextClustAlloc_00518da0__recomp},
    {"_sceMcFatWriteFastFile", 0x518E70, &recomp_gen::fn__sceMcFatWriteFastFile_00518e70, &recomp_gen::fn__sceMcFatWriteFastFile_00518e70__recomp},
    {"_sceMcFatDeleteFile", 0x5194F8, &recomp_gen::fn__sceMcFatDeleteFile_005194f8, &recomp_gen::fn__sceMcFatDeleteFile_005194f8__recomp},
    {"_sceMcFatChDir", 0x519728, &recomp_gen::fn__sceMcFatChDir_00519728, &recomp_gen::fn__sceMcFatChDir_00519728__recomp},
    {"_sceMcFatGetDir", 0x519850, &recomp_gen::fn__sceMcFatGetDir_00519850, &recomp_gen::fn__sceMcFatGetDir_00519850__recomp},
    {"_sceMcFatSetAttr", 0x519D70, &recomp_gen::fn__sceMcFatSetAttr_00519d70, &recomp_gen::fn__sceMcFatSetAttr_00519d70__recomp},
    {"_sceMcFatRename", 0x519EF8, &recomp_gen::fn__sceMcFatRename_00519ef8, &recomp_gen::fn__sceMcFatRename_00519ef8__recomp},
    {"_sceMcFatGetEntSpace", 0x51A078, &recomp_gen::fn__sceMcFatGetEntSpace_0051a078, &recomp_gen::fn__sceMcFatGetEntSpace_0051a078__recomp},
};

}  // namespace
namespace p3fes::recomp_gen {
void fn__sceMcpFlushCache_0051a498(EEContext&);
void fn__sceMcpFlushCache_0051a498__recomp(EEContext&);
}  // namespace p3fes::recomp_gen
namespace {
using namespace p3fes::game_test::libs1;
namespace mc = p3fes::game::libs1::mc2;

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kBuf = 0x01830000u;     // file data (64 KiB)
constexpr u32 kRec = 0x01840000u;     // records, paths, tables
constexpr u32 kPath = 0x01841000u;
constexpr u32 kPath2 = 0x01841100u;
constexpr u32 kErr = 0x01841200u;
constexpr u32 kTable = 0x01842000u;

const Case& C(const char* n) {
    // libs1_mc2.cpp's cluster-cache flush, paired here too: the write sequence flushes before each host re-read
    static const Case kFlush{"_sceMcpFlushCache", 0x51A498, &recomp_gen::fn__sceMcpFlushCache_0051a498, &recomp_gen::fn__sceMcpFlushCache_0051a498__recomp};
    if (std::string(n) == kFlush.name) return kFlush;
    return by_name(kCases, std::size(kCases), n);
}

// --- a host reader of the card image (public format) ----------------------------------------------------------------
struct HostCard {
    const std::vector<u8>& img;
    explicit HostCard(const std::vector<u8>& i) : img(i) {}
    u32 page_word(u32 page, u32 off) const {
        u32 v;
        std::memcpy(&v, img.data() + static_cast<std::size_t>(page) * kRawPage + off, 4);
        return v;
    }
    u32 sb(u32 off) const { return page_word(0, off); }
    u16 sb16(u32 off) const { return static_cast<u16>(page_word(0, off & ~3u) >> ((off & 2) * 8)); }
    std::vector<u8> cluster(u32 abs) const {  // 2 pages
        std::vector<u8> v(1024);
        for (u32 p = 0; p < 2; ++p) {
            const std::size_t off = (static_cast<std::size_t>(abs) * 2 + p) * kRawPage;
            if (off + 512 <= img.size()) std::memcpy(v.data() + 512 * p, img.data() + off, 512);
            else std::memset(v.data() + 512 * p, 0xFF, 512);  // (a cluster number past the card)
        }
        return v;
    }
    static u32 word(const std::vector<u8>& c, u32 i) {
        u32 v;
        std::memcpy(&v, c.data() + 4 * i, 4);
        return v;
    }
    u32 fat(u32 n) const {
        const u32 ifc = sb(mc::kIfcList + 4 * ((n / 256) / 256));
        const u32 ind = word(cluster(ifc), (n / 256) % 256);
        return word(cluster(ind), n % 256);
    }
    u32 alloc_offset() const { return sb(mc::kAllocOffset); }
    struct Ent {
        u16 mode = 0;
        u32 len = 0, cl = 0;
        std::string name;
        std::vector<u8> raw;
    };
    Ent entry(u32 first, u32 i) const {  // entry i of the chain starting at user cluster `first`
        u32 c = first;
        for (u32 k = 0; k < i / 2; ++k) c = fat(c) & 0x7FFFFFFFu;
        const auto cl = cluster(c + alloc_offset());
        Ent e;
        e.raw.assign(cl.begin() + 512 * (i % 2), cl.begin() + 512 * (i % 2) + 512);
        std::memcpy(&e.mode, e.raw.data(), 2);
        std::memcpy(&e.len, e.raw.data() + 4, 4);
        std::memcpy(&e.cl, e.raw.data() + 16, 4);
        e.name = std::string(reinterpret_cast<const char*>(e.raw.data() + 64), strnlen(reinterpret_cast<const char*>(e.raw.data() + 64), 32));
        return e;
    }
    // A directory's entries: its entry's length (in the parent; the root's own "." entry) counts them.
    std::vector<Ent> dir(u32 first, u32 count) const {
        std::vector<Ent> v;
        for (u32 i = 0; i < count && i < 256; ++i) v.push_back(entry(first, i));
        return v;
    }
    std::vector<Ent> dir(const Ent& d) const { return dir(d.cl, d.len); }
    Ent root_entry() const {
        Ent r = entry(sb(mc::kRootCluster), 0);
        r.cl = sb(mc::kRootCluster);
        return r;
    }
    std::vector<Ent> root() const { return dir(root_entry()); }
    bool find(const std::string& path, Ent& out) const {  // "/A/B"
        Ent e = root_entry();
        std::size_t pos = 1;
        while (pos < path.size()) {
            const std::size_t nx = path.find('/', pos);
            const std::string comp = path.substr(pos, nx == std::string::npos ? std::string::npos : nx - pos);
            bool found = false;
            for (const Ent& x : dir(e))
                if ((x.mode & 0x8000) && x.name == comp) {
                    e = x;
                    found = true;
                    break;
                }
            if (!found) return false;
            if (nx == std::string::npos) break;
            pos = nx + 1;
        }
        out = e;
        return true;
    }
    std::vector<u8> read(const Ent& e) const {
        std::vector<u8> v;
        u32 c = e.cl;
        while (v.size() < e.len) {
            const auto cl = cluster(c + alloc_offset());
            const std::size_t n = std::min<std::size_t>(1024, e.len - v.size());
            v.insert(v.end(), cl.begin(), cl.begin() + static_cast<std::ptrdiff_t>(n));
            c = fat(c) & 0x7FFFFFFFu;
        }
        return v;
    }
};

// --- the world: the b_5800 library state and the card --------------------------------------------------------------
struct CardRun {
    std::vector<u8> master;                 // the card the next pair starts from
    std::vector<std::shared_ptr<Card>> made;  // the two worlds' cards of the last pair
    u64 new_card = 1;
};
Setup card_setup(std::shared_ptr<CardRun> run) {
    return [run](StandInWorld& w) {
        auto card = std::make_shared<Card>();
        card->img = run->master;
        run->made.push_back(card);
        install_card(w, card, 1, run->new_card);
        // the card geometry record GetInfo / UnFormat read: page length, pages per block, pages, ECC
        w.si.install(kGetCardSpec, "_sceMcCoreGetCardSpec", [](EEContext& ctx, StandIns&, StandInCall& c) {
            const u32 spec[4] = {512, 16, 16384, 1};
            std::memcpy(gptr(ctx, static_cast<u32>(c.args[1])), spec, 16);
            c.v0 = 1;
        });
    };
}
// One pair on the card; the two cards must be equal; the card carries forward.
hgp::Run card_pair(Machine& m, std::shared_ptr<CardRun> run, const char* fn, const Args& a, u32& seed, const std::string& what,
                   const HwCheck& hw = {}) {
    run->made.clear();
    const hgp::Run r = pair(m, C(fn), a, seed++, what, card_setup(run), hw);
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
    copy_from_snapshot(m, snap, 0x7827D8u, 0x400);    // the init flag, both superblock copies
    copy_from_snapshot(m, snap, 0x96F100u, 0x100);    // the request-busy word
    copy_from_snapshot(m, snap, 0x97B700u, 0xA900u);  // FAT state, entry buffers, write-cluster cache, core sockets
    // the snapshot's superblock copy must be this card's page 0
    return std::memcmp(card.data(), m.mem.main_ram() + mc::kSuperblock, 340) == 0;
}

void wpath(Machine& m, u32 va, const std::string& s) { wstr(m, va, s); }

}  // namespace

TEST_CASE("game(libs1_mc2fat): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    auto blank = std::make_shared<std::vector<u8>>(64 * kRawPage, 0xFF);
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, 16, [blank](StandInWorld& w) {
        auto card = std::make_shared<Card>();
        card->img = *blank;
        install_card(w, card, 1, 1);
    }, true);
}

TEST_CASE("game(libs1_mc2fat): reading the battle route's card -- look-ups, files, listings, the FAT") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    auto run = std::make_shared<CardRun>();
    if (!load_battle_state(*m, run->master)) {
        MESSAGE("SKIP: b_5800 / tartarus.ps2 not found or not the same card");
        return;
    }
    const std::vector<u8> pristine = run->master;
    HostCard host(pristine);
    u32 seed = 1;
    const auto root = host.root();
    REQUIRE(root.size() >= 2);
    CHECK(root[0].name == ".");
    CHECK(root[1].name == "..");
    int looked = 0, files = 0, bytes = 0;
    // every root entry and every entry of each directory, by absolute path
    for (std::size_t i = 2; i < root.size(); ++i) {
        if (!(root[i].mode & 0x8000)) continue;
        std::vector<std::pair<std::string, HostCard::Ent>> ents = {{"/" + root[i].name, root[i]}};
        if (root[i].mode & 0x20)
            for (const auto& e : host.dir(root[i]))
                if ((e.mode & 0x8000) && e.name != "." && e.name != "..") ents.push_back({"/" + root[i].name + "/" + e.name, e});
        for (const auto& [path, e] : ents) {
            wpath(*m, kPath, path);
            wzero(*m, kRec, 64);
            auto r = card_pair(*m, run, "_sceMcFatSearchFile", {0, kPath, kRec}, seed, "SearchFile " + path);
            CHECK(v0_of(r) == 0);
            CHECK(r32(*m, kRec + 16) == e.len);
            CHECK(r16(*m, kRec + 20) == e.mode);
            CHECK(gstr(*m, kRec + 24) == e.name);
            ++looked;
            if ((e.mode & 0x10) && e.len > 0 && files < 12) {
                ++files;
                const std::vector<u8> want = host.read(e);
                const u32 len = std::min<u32>(e.len, 0x10000);
                for (const char* fn : {"_sceMcFatReadFile", "_sceMcFatReadFastFile"}) {
                    wzero(*m, kBuf, len);
                    r = card_pair(*m, run, fn, {0, kPath, kBuf, 0}, seed, std::string(fn) + " " + path, hw_in({{GPR_T0, len}}));
                    CHECK(v0_of(r) == len);
                    bool same = true;
                    for (u32 k = 0; k < len && same; ++k) same = r8(*m, kBuf + k) == want[k];
                    CHECK(same);
                    bytes += static_cast<int>(len);
                }
                // random offsets and lengths (a length 0 reads to the end; past the end is clipped)
                std::mt19937 rng{seed};
                for (int k = 0; k < 4; ++k) {
                    const u32 off = rng() % e.len, n = rng() % 3000;
                    wzero(*m, kBuf, 0x2000);
                    r = card_pair(*m, run, k % 2 ? "_sceMcFatReadFastFile" : "_sceMcFatReadFile", {0, kPath, kBuf, off}, seed,
                                  "read part " + path, hw_in({{GPR_T0, n}}));
                    const u32 exp = n == 0 || off + n > e.len ? e.len - off : n;
                    CHECK(v0_of(r) == std::min<u32>(exp, 0xFFFFFFFFu));
                    for (u32 b = 0; b < std::min<u32>(exp, 0x2000); ++b)
                        if (r8(*m, kBuf + b) != want[off + b]) { CHECK(false); break; }
                }
            }
        }
        // the directory listing
        if (root[i].mode & 0x20) {
            wpath(*m, kPath, "/" + root[i].name + "/*");
            wzero(*m, kTable, 56 * 64);
            w32(*m, kErr, 0xDEAD);
            auto r = card_pair(*m, run, "_sceMcFatGetDir", {0, kPath, 0, 64}, seed, "GetDir " + root[i].name,
                               hw_in({{GPR_T0, kTable}, {GPR_T1, kErr}}));
            const auto want = host.dir(root[i]);
            std::vector<std::string> got;
            CHECK(v0_of(r) == 0);
            const u32 cnt = r32(*m, kErr);  // the entry count through the sixth argument
            for (u32 k = 0; k < cnt && k < 64; ++k) got.push_back(gstr(*m, kTable + 56 * k + 24));
            std::vector<std::string> exp;
            for (const auto& e : want)
                if (e.mode & 0x8000) exp.push_back(e.name);
            if (got != exp) {
                std::string g, x;
                for (const auto& s : got) g += s + " ";
                for (const auto& s : exp) x += s + " ";
                MESSAGE("GetDir " << root[i].name << ": v0 " << v0s(r) << " count word " << r32(*m, kErr) << "; got [" << g << "] host [" << x << "]");
            }
            CHECK(got == exp);
        }
    }
    // a path that is not there
    wpath(*m, kPath, "/NO-SUCH-SAVE");
    CHECK(v0_of(card_pair(*m, run, "_sceMcFatSearchFile", {0, kPath, kRec}, seed, "SearchFile missing")) == sx(mc::kNoEntry));
    // FAT entries, chains and the free clusters
    const u32 usable = r32(*m, mc::kSuperblock + mc::kUsableClusters);
    std::mt19937 rng{5};
    for (int k = 0; k < 48; ++k) {
        const u32 n = rng() % usable;
        w32(*m, kErr, 0xDEAD);
        auto r = card_pair(*m, run, "_sceMcFatReadFatData", {0, n, kErr}, seed, "ReadFatData " + std::to_string(n));
        CHECK(static_cast<u32>(v0_of(r)) == host.fat(n));
        CHECK(r32(*m, kErr) == 0);
        r = card_pair(*m, run, "_sceMcFatGetNextClustSelf", {0, n, kErr}, seed, "GetNextClustSelf");
        const u32 f = host.fat(n);
        if (f == 0xFFFFFFFFu) CHECK(v0s(r) == -1);
        else if (f != 0x7FFFFFFFu) CHECK(static_cast<u32>(v0_of(r)) == (f & 0x7FFFFFFFu));
    }
    for (std::size_t i = 2; i < root.size(); ++i) {
        const auto r = card_pair(*m, run, "_fat_chain_trace", {0, root[i].cl}, seed, "fat_chain_trace " + root[i].name);
        u32 len = 0;
        for (u32 c = root[i].cl; len < 10000; ++len) {
            const u32 f = host.fat(c);
            if (f == 0xFFFFFFFFu) { ++len; break; }
            c = f & 0x7FFFFFFFu;
        }
        CHECK(static_cast<u32>(v0_of(r)) == len);
    }
    // (the pair harness cuts a run at 20,000 check points: the free-cluster walks start 1,200 clusters before the end)
    w32(*m, mc::kFatState + mc::kFreeSearch, usable - 1200);
    u32 free_count = 0, first_free = 0xFFFFFFFFu;
    const u32 start = r32(*m, mc::kFatState + mc::kFreeSearch);
    for (u32 n = start; n < usable; ++n)
        if (!(host.fat(n) & 0x80000000u)) {
            ++free_count;
            if (first_free == 0xFFFFFFFFu) first_free = n;
        }
    CHECK(static_cast<u32>(v0_of(card_pair(*m, run, "_sceMcFatGetFreeClustSize", {0, kErr}, seed, "GetFreeClustSize"))) == free_count);
    CHECK(static_cast<u32>(v0_of(card_pair(*m, run, "_sceMcFatGetFreeClust", {0, kErr}, seed, "GetFreeClust"))) == first_free);
    // the card information: cached (the free clusters from the search start) ...
    wzero(*m, kRec, 16);
    auto ri = card_pair(*m, run, "_sceMcFatGetInfo", {0, kRec}, seed, "GetInfo");
    CHECK(v0_of(ri) == 0);
    CHECK(r32(*m, kRec) == 2);
    CHECK(r32(*m, kRec + 4) == 1);
    CHECK(r32(*m, kRec + 8) == free_count);
    // ... and on a changed card: the superblock re-read from page 0, the geometry and write-back hole set, the root's
    // "." / ".." checked, the free search from 0. To stay inside the harness's check-point budget the card's page 0
    // says alloc_end 400 (the bad-block walk) and 1,000 usable clusters (the free walk).
    run->new_card = 2;
    auto patch = [&](u32 off, u32 v) { std::memcpy(run->master.data() + off, &v, 4); };
    patch(mc::kAllocEnd, 400);
    patch(mc::kUsableClusters, 1000);
    u32 free1000 = 0;
    for (u32 n = 0; n < 1000; ++n) free1000 += (host.fat(n) & 0x80000000u) ? 0 : 1;
    wzero(*m, kRec, 16);
    ri = card_pair(*m, run, "_sceMcFatGetInfo", {0, kRec}, seed, "GetInfo new card");
    CHECK(v0_of(ri) == sx(mc::kCardChanged));  // reported once after a change, with the information filled in
    CHECK(r32(*m, kRec) == 2);
    CHECK(r32(*m, kRec + 4) == 1);
    CHECK(r32(*m, kRec + 8) == free1000);
    CHECK(r32(*m, mc::kSuperblock + mc::kAllocEnd) == 400);  // the copy is page 0's
    CHECK(r32(*m, mc::kFatState + mc::kNewCard) == 0);
    CHECK(r32(*m, mc::kFatState + mc::kFormatted) == 1);
    patch(mc::kAllocEnd, HostCard(pristine).sb(mc::kAllocEnd));  // page 0 as it was
    patch(mc::kUsableClusters, HostCard(pristine).sb(mc::kUsableClusters));
    run->new_card = 1;
    CHECK(run->master == pristine);  // reading wrote nothing
    MESSAGE(looked << " paths looked up, " << files << " files read (" << bytes << " bytes); " << free_count << " free clusters; pairs "
                   << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_mc2fat): a write sequence on the card -- mkdir, create, write, rename, delete") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    auto run = std::make_shared<CardRun>();
    if (!load_battle_state(*m, run->master)) {
        MESSAGE("SKIP: b_5800 / tartarus.ps2 not found or not the same card");
        return;
    }
    u32 seed = 100;
    w32(*m, mc::kFatState + mc::kFreeSearch, r32(*m, mc::kSuperblock + mc::kUsableClusters) - 1200);  // (the walk budget)
    // the host re-reads the card after both caches are written back (the library defers its cluster writes)
    auto host_find = [&](const std::string& p, HostCard::Ent& e) {
        card_pair(*m, run, "_sceMcFatFlushFatCache", {0}, seed, "FlushFatCache");
        card_pair(*m, run, "_sceMcpFlushCache", {0}, seed, "FlushCache");
        HostCard h(run->master);
        return h.find(p, e);
    };
    HostCard::Ent e;
    // mkdir
    wpath(*m, kPath, "/LIBS1TEST");
    auto r = card_pair(*m, run, "_sceMcFatCreateFile", {0, kPath, 0x8427}, seed, "CreateFile dir", hw_in({{GPR_S3, 0}}));
    CHECK(v0_of(r) == 0);
    REQUIRE(host_find("/LIBS1TEST", e));
    CHECK((e.mode & 0x20) != 0);
    CHECK(e.len == 2);  // "." and ".."
    // the same again: exists
    CHECK(v0_of(card_pair(*m, run, "_sceMcFatCreateFile", {0, kPath, 0x8427}, seed, "CreateFile dir again", hw_in({{GPR_S3, 0}}))) != 0);
    // create a file with the default mode
    wpath(*m, kPath, "/LIBS1TEST/DATA.BIN");
    r = card_pair(*m, run, "_sceMcFatCreateFile", {0, kPath, 0}, seed, "CreateFile file", hw_in({{GPR_S3, 0}}));
    CHECK(v0_of(r) == 0);
    REQUIRE(host_find("/LIBS1TEST/DATA.BIN", e));
    CHECK(e.mode == 0x8417);
    CHECK(e.len == 0);
    // write 3,000 bytes, then 2,000 more from offset 2,500 (extending the chain); both write paths
    std::vector<u8> data(4500);
    std::mt19937 rng{3};
    for (auto& b : data) b = static_cast<u8>(rng());
    for (u32 i = 0; i < 3000; ++i) w8(*m, kBuf + i, data[i]);
    r = card_pair(*m, run, "_sceMcFatWriteFile", {0, kPath, kBuf, 0}, seed, "WriteFile 3000", hw_in({{GPR_T0, 3000}}));
    CHECK(v0_of(r) == 3000);
    REQUIRE(host_find("/LIBS1TEST/DATA.BIN", e));
    CHECK(e.len == 3000);
    CHECK(HostCard(run->master).read(e) == std::vector<u8>(data.begin(), data.begin() + 3000));
    for (u32 i = 0; i < 2000; ++i) w8(*m, kBuf + i, data[2500 + i]);
    r = card_pair(*m, run, "_sceMcFatWriteFastFile", {0, kPath, kBuf, 2500}, seed, "WriteFastFile +2000", hw_in({{GPR_T0, 2000}}));
    CHECK(v0_of(r) == 2000);
    REQUIRE(host_find("/LIBS1TEST/DATA.BIN", e));
    CHECK(e.len == 4500);
    CHECK(HostCard(run->master).read(e) == data);
    // read it back through the library
    wzero(*m, kBuf, 0x2000);
    r = card_pair(*m, run, "_sceMcFatReadFile", {0, kPath, kBuf, 0}, seed, "ReadFile back", hw_in({{GPR_T0, 4500}}));
    CHECK(v0_of(r) == 4500);
    bool same = true;
    for (u32 i = 0; i < 4500 && same; ++i) same = r8(*m, kBuf + i) == data[i];
    CHECK(same);
    // free entries of the directory, attributes, change directory
    wpath(*m, kPath2, "/LIBS1TEST");
    r = card_pair(*m, run, "_sceMcFatGetEntSpace", {0, kPath2}, seed, "GetEntSpace");
    CHECK(v0s(r) >= 0);
    r = card_pair(*m, run, "_sceMcFatSetAttr", {0, kPath, 0x8413}, seed, "SetAttr");
    REQUIRE(host_find("/LIBS1TEST/DATA.BIN", e));
    MESSAGE("SetAttr: v0 " << std::hex << v0_of(r) << ", mode now " << e.mode << std::dec);
    r = card_pair(*m, run, "_sceMcFatChDir", {0, kPath2, kRec}, seed, "ChDir");
    CHECK(v0_of(r) == 0);
    CHECK(gstr(*m, mc::kFatState + mc::kCurDir) == "/LIBS1TEST/");
    wpath(*m, kPath2, "/");
    card_pair(*m, run, "_sceMcFatChDir", {0, kPath2, kRec}, seed, "ChDir root");
    CHECK(gstr(*m, mc::kFatState + mc::kCurDir) == "/");
    // rename within the directory
    wpath(*m, kPath2, "DATA2.BIN");
    r = card_pair(*m, run, "_sceMcFatRename", {0, kPath, kPath2}, seed, "Rename");
    CHECK(v0_of(r) == 0);
    CHECK(!host_find("/LIBS1TEST/DATA.BIN", e));
    REQUIRE(host_find("/LIBS1TEST/DATA2.BIN", e));
    CHECK(e.len == 4500);
    // delete the file, then the (now empty) directory; deleting a non-empty directory first is refused
    wpath(*m, kPath2, "/LIBS1TEST");
    CHECK(v0_of(card_pair(*m, run, "_sceMcFatDeleteFile", {0, kPath2}, seed, "DeleteFile dir not empty")) != 0);
    wpath(*m, kPath, "/LIBS1TEST/DATA2.BIN");
    r = card_pair(*m, run, "_sceMcFatDeleteFile", {0, kPath}, seed, "DeleteFile file");
    CHECK(v0_of(r) == 0);
    CHECK(!host_find("/LIBS1TEST/DATA2.BIN", e));
    r = card_pair(*m, run, "_sceMcFatDeleteFile", {0, kPath2}, seed, "DeleteFile dir");
    CHECK(v0_of(r) == 0);
    CHECK(!host_find("/LIBS1TEST", e));
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

#else

TEST_CASE("game(libs1_mc2fat): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
