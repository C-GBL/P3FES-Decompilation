// Phase 5 pair tests for slice fs3 (game/src/cri/rofs_name.cpp, game/src/hcdvd/hcdvd_volpaths.cpp): each
// hand-written function and the recompiled body it replaces run on identical guest machines (pair_harness.h: result,
// callee-saved registers, the arena and the caller's stack, virtual cycles, check-point count -- here also
// RFMAI_CopyStructCdDr's static record outside the arena), on randomised inputs with the edge cases, plus the
// documented rules of docs/ANALYSIS/11_file_io.md checked on the host independently of both. Real data: every
// ISO9660 directory record of the three CVMs (when they are beside the ELF) is converted by rfdir_getOneDirEnt and
// must equal the entry of the ELF's own #DirLst# table for that directory; the CVM PVDs pass rfmai_checkMedia; the
// 25 BTL / 123 VOL directory strings of the ELF drive H_Cdvd_BuildVolumePaths.
#include "pair_harness.h"

#include "p3fes/game/cri_rofs.h"
#include "p3fes/game/fs3.h"

#include <algorithm>
#include <climits>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include <utility>
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
P3FES_DECL_PAIR(fn_rfdir_toUpper_0056b980)
P3FES_DECL_PAIR(fn_rfdirStrncmpi_0056b9a8)
P3FES_DECL_PAIR(fn_rfdirStrcmpDirName_0056ba48)
P3FES_DECL_PAIR(fn_rfdir_getTokenSize_0056bba0)
P3FES_DECL_PAIR(fn_rfdir_getOneDirEnt_0056bcb0)
P3FES_DECL_PAIR(fn_rfmai_checkMedia_00566f30)
P3FES_DECL_PAIR(fn_rfmai_divideFname_00566f78)
P3FES_DECL_PAIR(fn_rfmai_getDirBufAdr_00567188)
P3FES_DECL_PAIR(fn_rfmai_getVolume_005671f0)
P3FES_DECL_PAIR(fn_sub_568368_00568368)
P3FES_DECL_PAIR(fn_sub_569BD0_00569bd0)
P3FES_DECL_PAIR(fn_sub_569BE8_00569be8)
P3FES_DECL_PAIR(fn_H_Cdvd_BuildVolumePaths_00101240)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

// Arena layout (kArena .. kArena + 0x2000).
constexpr u32 kA = kArena + 0x100;      // first string / path / ISO record (up to 0x700)
constexpr u32 kB = kArena + 0x800;      // second string / volume out / #DirLst# entry out (up to 0x400)
constexpr u32 kC = kArena + 0xC00;      // third buffer: name out, directory out (up to 0x400)
constexpr u32 kD = kArena + 0x1000;     // fourth buffer: vol_file out (0x400)
constexpr u32 kWork = kArena + 0x1800;  // a ROFS work area (0x100)
constexpr u32 kVols = kArena + 0x1900;  // its RofsVolume array (up to 8 x 52)
constexpr u32 kOut64 = kArena + 0x1C00; // two u32 outputs
// Outside the arena, compared as regions.
constexpr u32 kDrStatic = 0x99A1F0u;    // RFMAI_CopyStructCdDr's static record

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

// run_pair with whole-state reset: the arena and every listed region are restored before the second run, and the
// listed regions must end equal (the arena is compared by expect_same).
struct Region {
    u32 va;
    u32 len;
};
Pair pair_mem(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::vector<Region> regions = {}) {
    regions.push_back({kArena, kArenaSize});
    std::vector<std::vector<u8>> before;
    for (const Region& r : regions) before.push_back(m.bytes(r.va, r.len));
    Pair p;
    p.hand = run(m, hand, args, seed);
    std::vector<std::vector<u8>> hand_after;
    for (const Region& r : regions) hand_after.push_back(m.bytes(r.va, r.len));
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    p.recomp = run(m, recomp, args, seed);
    expect_same(p.hand, p.recomp, what);
    for (std::size_t i = 0; i < regions.size(); ++i) {
        INFO(what << ": region 0x" << std::hex << regions[i].va);
        CHECK(hand_after[i] == m.bytes(regions[i].va, regions[i].len));
    }
    return p;
}

std::string random_str(std::mt19937& rng, std::size_t len, const std::string& alphabet) {
    std::string s;
    for (std::size_t i = 0; i < len; ++i) s += alphabet[rng() % alphabet.size()];
    return s;
}
std::string upper_az(std::string s) {
    for (char& c : s)
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 32);
    return s;
}
std::string mixed_case(std::mt19937& rng, std::string s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z' && (rng() & 1)) c = static_cast<char>(c + 32);
    return s;
}
std::vector<std::string> string_table(const Machine& m, u32 va, u32 count) {
    std::vector<std::string> v;
    for (u32 i = 0; i < count; ++i) v.push_back(m.str(load32(m, va + 4 * i), 256));
    return v;
}

// A ROFS work area with `names` as volumes (RofsVolume name at +22) and `def` (index, -1 = none) as default;
// `max_vols` is the slot count written to the work area (kAllNames: one per name; negative counts are test inputs).
constexpr s32 kAllNames = INT32_MIN;
void setup_rofs(Machine& m, const std::vector<std::string>& names, int def, s32 max_vols = kAllNames, u32 max_ents = 836) {
    std::memset(m.at(kWork), 0, 0x100);
    std::memset(m.at(kVols), 0, 8 * game::kRofsVolumeSize);
    store32(m, game::kRofsWorkPtr, kWork);
    store32(m, kWork + game::kRofsWorkMaxVolumes, static_cast<u32>(max_vols == kAllNames ? static_cast<s32>(names.size()) : max_vols));
    store32(m, kWork + game::kRofsWorkMaxDirEnts, max_ents);
    store32(m, kWork + game::kRofsWorkVolumes, kVols);
    for (std::size_t i = 0; i < names.size(); ++i)
        std::memcpy(m.at(kVols + static_cast<u32>(i) * game::kRofsVolumeSize + game::kRofsVolumeName), names[i].c_str(),
                    std::min<std::size_t>(names[i].size() + 1, 9));
    store32(m, kWork + game::kRofsWorkDefVolume, def < 0 ? 0 : kVols + static_cast<u32>(def) * game::kRofsVolumeSize);
}

// Reads `n` bytes at byte offset `off` of a file (empty on failure).
std::vector<u8> read_at(const std::filesystem::path& p, u64 off, std::size_t n) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    f.seekg(static_cast<std::streamoff>(off));
    std::vector<u8> v(n);
    f.read(reinterpret_cast<char*>(v.data()), static_cast<std::streamsize>(n));
    if (static_cast<std::size_t>(f.gcount()) != n) return {};
    return v;
}
u32 le32(const u8* p) { return static_cast<u32>(p[0]) | (static_cast<u32>(p[1]) << 8) | (static_cast<u32>(p[2]) << 16) | (static_cast<u32>(p[3]) << 24); }

}  // namespace

// --- rofs_dir.c comparers ---------------------------------------------------------------------------------------
TEST_CASE("game(fs3): rfdir_toUpper equals its recompiled body for every byte; ASCII a-z only, sign-extended") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5301u};
    int n = 0;
    for (int b = 0; b < 256; ++b) {
        for (u64 high : {u64{0}, u64{0xFFFFFF00u}, u64{0x123456789ABC0000ull}}) {  // only the low byte may matter
            const Pair p = pair_mem(m, &recomp_gen::fn_rfdir_toUpper_0056b980, &recomp_gen::fn_rfdir_toUpper_0056b980__recomp,
                                    {high | static_cast<u64>(b), 0, 0, 0}, rng(), "rfdir_toUpper");
            const s8 c = static_cast<s8>(b);
            const s8 want = (c >= 'a' && c <= 'z') ? static_cast<s8>(c - 32) : c;
            CHECK(p.hand.v0 == sx(static_cast<u32>(static_cast<s32>(want))));
            ++n;
        }
    }
    MESSAGE("rfdir_toUpper: " << n << " pairs");
}

TEST_CASE("game(fs3): rfdirStrncmpi and rfdirStrcmpDirName equal their recompiled bodies; case-insensitive rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5302u};
    const std::string alphabet = "abcxyzABCXYZ09_.\\@[`{\xE1\xC1";
    std::vector<std::pair<std::string, std::string>> cases = {
        {"", ""}, {"", "A"}, {"A", ""}, {"abc", "ABC"}, {"abc", "ABD"}, {"ABC", "ABCD"}, {"ABCD", "ABC"},
        {"@", "`"}, {"[", "{"}, {"\xE1", "\xC1"}, {"MODEL", "model"}, {"BATTLE", "BATTLE."}};
    // Real directory names of the ELF's tables, in their stored and in mixed case.
    for (u32 i = 0; i < 123; ++i) {
        std::string s = m.str(load32(m, 0x5CE590u + 4 * i), 256);
        cases.emplace_back(s, mixed_case(rng, s));
    }
    for (int i = 0; i < 600; ++i) {
        std::string a = random_str(rng, rng() % 20, alphabet);
        std::string b = (rng() % 3 == 0) ? random_str(rng, rng() % 20, alphabet) : mixed_case(rng, upper_az(a));
        if (rng() % 4 == 0 && !b.empty()) b.resize(rng() % b.size());
        cases.emplace_back(a, b);
    }
    int pairs = 0;
    for (const auto& [a, b] : cases) {
        m.put(kA, a);
        m.put(kB, b);
        const Pair d = pair_mem(m, &recomp_gen::fn_rfdirStrcmpDirName_0056ba48, &recomp_gen::fn_rfdirStrcmpDirName_0056ba48__recomp,
                                {sx(kA), sx(kB), 0, 0}, rng(), "rfdirStrcmpDirName");
        CHECK(d.hand.v0 == (upper_az(a) == upper_az(b) ? 1u : 0u));
        ++pairs;
        for (s32 n : {-1, 0, 1, 2, 5, static_cast<s32>(a.size()), static_cast<s32>(a.size()) + 1, 40}) {
            const Pair p = pair_mem(m, &recomp_gen::fn_rfdirStrncmpi_0056b9a8, &recomp_gen::fn_rfdirStrncmpi_0056b9a8__recomp,
                                    {sx(kA), sx(kB), sx(static_cast<u32>(n)), 0}, rng(), "rfdirStrncmpi");
            // Host rule: compare up to n characters, stopping when a ends (then b must end there too).
            u32 want = 1;
            for (s32 k = 0; k < n; ++k) {
                const char ca = k < static_cast<s32>(a.size()) ? a[k] : 0;
                const char cb = k < static_cast<s32>(b.size()) ? b[k] : 0;
                if (ca == 0) {
                    want = cb == 0 ? 1 : 0;
                    break;
                }
                if (upper_az(std::string(1, ca)) != upper_az(std::string(1, cb))) {
                    want = 0;
                    break;
                }
            }
            CHECK(p.hand.v0 == want);
            ++pairs;
        }
    }
    MESSAGE("rfdirStrcmpDirName / rfdirStrncmpi: " << pairs << " pairs");
}

TEST_CASE("game(fs3): rfdir_getTokenSize equals its recompiled body; characters before the first delimiter") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5303u};
    std::vector<std::pair<std::string, std::string>> cases = {
        {"", ""}, {"", "\\"}, {"ABC", ""}, {"ABC", "\\"}, {"\\ABC", "\\"}, {"AB\\C", "\\/"}, {"AB/C", "\\/"},
        {"VOL:\\X", ":"}, {"\xE9X", "\xE9"}, {"abc", "cba"}};
    const std::string alphabet = "ABab/\\:._\xE9";
    for (int i = 0; i < 800; ++i) cases.emplace_back(random_str(rng, rng() % 30, alphabet), random_str(rng, rng() % 4, alphabet));
    for (const auto& [s, d] : cases) {
        m.put(kA, s);
        m.put(kB, d);
        const Pair p = pair_mem(m, &recomp_gen::fn_rfdir_getTokenSize_0056bba0, &recomp_gen::fn_rfdir_getTokenSize_0056bba0__recomp,
                                {sx(kA), sx(kB), 0, 0}, rng(), "rfdir_getTokenSize");
        const std::size_t want = s.find_first_of(d);
        CHECK(p.hand.v0 == (want == std::string::npos ? s.size() : want));
    }
    MESSAGE("rfdir_getTokenSize: " << cases.size() << " pairs");
}

// --- rfdir_getOneDirEnt: synthetic ISO records and every record of the three CVMs -----------------------------
namespace {
std::vector<u8> iso_record(const std::string& ident, u32 lba, u32 size, u8 flags, std::size_t pad = 0) {
    std::vector<u8> r(33 + ident.size() + ((ident.size() & 1) ? 0 : 1) + pad, 0);
    r[0] = static_cast<u8>(r.size());
    for (int i = 0; i < 4; ++i) {
        r[2 + i] = static_cast<u8>(lba >> (8 * i));
        r[9 - i] = static_cast<u8>(lba >> (8 * i));
        r[10 + i] = static_cast<u8>(size >> (8 * i));
        r[17 - i] = static_cast<u8>(size >> (8 * i));
    }
    r[25] = flags;
    r[28] = 1;
    r[31] = 1;
    r[32] = static_cast<u8>(ident.size());
    std::memcpy(r.data() + 33, ident.data(), ident.size());
    return r;
}
}  // namespace

TEST_CASE("game(fs3): rfdir_getOneDirEnt equals its recompiled body on synthetic ISO9660 records") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5304u};
    std::vector<std::vector<u8>> recs = {
        iso_record(std::string(1, '\0'), 0x14, 0x800, 2), iso_record(std::string(1, '\1'), 0x14, 0x800, 2),
        iso_record("BATTLE", 0x20, 0x1000, 2), iso_record("LMAP_DAT.;1", 0x30, 1234, 0), iso_record("A.BIN;1", 0x31, 7, 0),
        iso_record("AB;1", 0x32, 0, 0), iso_record("X", 0x33, 9, 3), iso_record("ODD", 1, 2, 3)};  // files always end in ";1"
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
    for (int i = 0; i < 400; ++i) {
        const bool dir = rng() & 1;
        std::string id = random_str(rng, 1 + rng() % 24, alphabet);
        if (!dir) id += (rng() & 1 ? "." + random_str(rng, rng() % 4, alphabet) : std::string(".")) + ";1";
        recs.push_back(iso_record(id, rng(), rng(), dir ? 2 : (rng() % 4 == 0 ? 0x80 : 0), rng() % 8));
    }
    int n = 0;
    for (std::vector<u8> r : recs) {
        for (int variant = 0; variant < 2; ++variant) {
            if (variant == 1) r[0] = static_cast<u8>(rng() % 34);  // too short for a directory record: -1
            std::memset(m.at(kA), 0xCD, 0x300);
            std::memcpy(m.at(kA), r.data(), r.size());
            std::memset(m.at(kB), 0xEE, 0x100);
            const Pair p = pair_mem(m, &recomp_gen::fn_rfdir_getOneDirEnt_0056bcb0, &recomp_gen::fn_rfdir_getOneDirEnt_0056bcb0__recomp,
                                    {sx(kA), sx(kB), 0, 0}, rng(), "rfdir_getOneDirEnt", {{kDrStatic, 0x40}});
            ++n;
            if (r[0] < 34) {
                CHECK(p.hand.v0 == sx(0xFFFFFFFFu));
                continue;
            }
            CHECK(p.hand.v0 == r[0]);
            // Host rule: lba / size / flags from the record, the identifier without ";1" for files.
            const u32 e = kB;
            CHECK(load32(m, e + offsetof(game::RofsDirLstEnt, lba)) == le32(r.data() + 2));
            CHECK(load32(m, e + offsetof(game::RofsDirLstEnt, size_lo)) == le32(r.data() + 10));
            CHECK(load32(m, e + offsetof(game::RofsDirLstEnt, size_hi)) == 0);
            CHECK(*m.at(e + offsetof(game::RofsDirLstEnt, flags)) == r[25]);
            std::string id(reinterpret_cast<const char*>(r.data() + 33), r[32]);
            std::string want = (r[25] & 2) ? id : id.substr(0, id.size() - 2);
            if (r[25] & 2) {
                if (want[0] == '\0') want = ".";
                else if (want[0] == '\1') want = "..";
            }
            want = want.substr(0, want.find('\0'));
            CHECK(m.str(e + offsetof(game::RofsDirLstEnt, name), 64) == want);
        }
    }
    // Null arguments.
    for (const auto& [a, b] : std::vector<std::pair<u32, u32>>{{0, kB}, {kA, 0}, {0, 0}}) {
        const Pair p = pair_mem(m, &recomp_gen::fn_rfdir_getOneDirEnt_0056bcb0, &recomp_gen::fn_rfdir_getOneDirEnt_0056bcb0__recomp,
                                {sx(a), sx(b), 0, 0}, rng(), "rfdir_getOneDirEnt null");
        CHECK(p.hand.v0 == 0);
        ++n;
    }
    MESSAGE("rfdir_getOneDirEnt: " << n << " synthetic pairs");
}

TEST_CASE("game(fs3): rfdir_getOneDirEnt rebuilds the ELF's #DirLst# tables from the CVMs' ISO directories; checkMedia on their PVDs") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const std::filesystem::path disc = std::filesystem::path(elf_path()).parent_path();
    // The ELF's tables by directory LBA, per volume (docs/ANALYSIS/11 §1 step 1).
    std::map<u32, u32> vol_tables, btl_tables, bgm_tables;
    for (u32 i = 0; i < 123; ++i) {
        const u32 t = load32(m, 0x5CE780u + 4 * i);
        vol_tables[load32(m, t + offsetof(game::RofsDirLstHdr, dir_lba))] = t;
    }
    for (u32 i = 0; i < 25; ++i) {
        const u32 t = load32(m, 0x5CDDF0u + 4 * i);
        btl_tables[load32(m, t + offsetof(game::RofsDirLstHdr, dir_lba))] = t;
    }
    bgm_tables[load32(m, 0x6418E0u + offsetof(game::RofsDirLstHdr, dir_lba))] = 0x6418E0u;
    std::mt19937 rng{0xF5305u};
    u32 records = 0, tables_seen = 0, pvds = 0;
    bool any = false;
    for (const auto& [file, tables] : std::vector<std::pair<const char*, std::map<u32, u32>*>>{
             {"DATA.CVM", &vol_tables}, {"BTL.CVM", &btl_tables}, {"BGM.CVM", &bgm_tables}}) {
        const std::filesystem::path cvm = disc / file;
        const u64 iso = 0x1800;  // the ISO image starts after the CVM header (docs/ANALYSIS/11 §0)
        const std::vector<u8> pvd = read_at(cvm, iso + 16 * 2048, 2048);
        if (pvd.empty()) {
            MESSAGE("SKIP: " << cvm.string() << " not readable");
            continue;
        }
        any = true;
        // rfmai_checkMedia on the real PVD (and on a corrupted copy).
        for (int k = 0; k < 2; ++k) {
            std::memcpy(m.at(kA), pvd.data(), 8);
            if (k == 1) m.at(kA)[3] ^= 1;
            const Pair p = pair_mem(m, &recomp_gen::fn_rfmai_checkMedia_00566f30, &recomp_gen::fn_rfmai_checkMedia_00566f30__recomp,
                                    {sx(kA), 0, 0, 0}, rng(), "rfmai_checkMedia (real PVD)");
            CHECK(p.hand.v0 == (k == 0 ? 1u : 0u));
            ++pvds;
        }
        for (const auto& [lba, table] : *tables) {
            const u32 count = load32(m, table + offsetof(game::RofsDirLstHdr, count));
            // The directory's size is in its own "." record, the first one of its extent.
            const std::vector<u8> first = read_at(cvm, iso + static_cast<u64>(lba) * 2048, 2048);
            REQUIRE(!first.empty());
            const u32 dir_size = le32(first.data() + 10);
            const std::vector<u8> dir = read_at(cvm, iso + static_cast<u64>(lba) * 2048, dir_size);
            REQUIRE(!dir.empty());
            u32 idx = 0;
            for (u32 off = 0; off < dir_size && idx < count;) {
                const u8 len = dir[off];
                if (len == 0) {  // records never cross a sector: the rest of this one is padding
                    off = (off / 2048 + 1) * 2048;
                    continue;
                }
                std::memset(m.at(kA), 0, 0x100);
                std::memcpy(m.at(kA), dir.data() + off, len);
                std::memset(m.at(kB), 0xEE, 0x40);
                const Pair p = pair_mem(m, &recomp_gen::fn_rfdir_getOneDirEnt_0056bcb0, &recomp_gen::fn_rfdir_getOneDirEnt_0056bcb0__recomp,
                                        {sx(kA), sx(kB), 0, 0}, rng(), "rfdir_getOneDirEnt (CVM record)", {{kDrStatic, 0x40}});
                CHECK(p.hand.v0 == len);
                // The ELF's entry for this record, field by field (the name compared up to its NUL).
                const u32 want = game::rofs_dir_entry(table, idx);
                INFO(file << " dir lba " << lba << " entry " << idx << " " << m.str(want + offsetof(game::RofsDirLstEnt, name), 34));
                CHECK(std::memcmp(m.at(kB), m.at(want), offsetof(game::RofsDirLstEnt, name)) == 0);
                CHECK(m.str(kB + offsetof(game::RofsDirLstEnt, name), 34) == m.str(want + offsetof(game::RofsDirLstEnt, name), 34));
                off += len;
                ++idx;
                ++records;
            }
            CHECK(idx == count);
            ++tables_seen;
        }
    }
    if (any) {
        CHECK(tables_seen == 149);
        MESSAGE("rfdir_getOneDirEnt: " << records << " CVM directory records of " << tables_seen << " directories equal the ELF's #DirLst# entries; "
                                       << pvds << " checkMedia pairs");
    }
}

TEST_CASE("game(fs3): rfmai_checkMedia equals its recompiled body; 1 iff bytes 1..5 are CD001") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5306u};
    int n = 0;
    for (int i = 0; i < 400; ++i) {
        u8 b[8] = {1, 'C', 'D', '0', '0', '1', 1, 0};
        if (i % 4 != 0) b[1 + rng() % 5] = static_cast<u8>(rng());
        std::memcpy(m.at(kA), b, 8);
        const Pair p = pair_mem(m, &recomp_gen::fn_rfmai_checkMedia_00566f30, &recomp_gen::fn_rfmai_checkMedia_00566f30__recomp,
                                {sx(kA), 0, 0, 0}, rng(), "rfmai_checkMedia");
        CHECK(p.hand.v0 == (std::memcmp(b + 1, "CD001", 5) == 0 ? 1u : 0u));
        ++n;
    }
    MESSAGE("rfmai_checkMedia: " << n << " pairs");
}

// --- rofs_mai.c: the volume name split and the volume table -----------------------------------------------------
namespace {
// rfmai_divideFname has five arguments, the fifth ($t0) beyond run()'s $a0..$a3: the pair is run here with the same
// checks as pair_harness.h's run_pair, the arena restored before each run, plus the dead stack (its part buffer).
struct DivideOut {
    Outcome o;
    std::string vol, name;
};
DivideOut run_divide(Machine& m, Fn fn, u32 vol, u32 name, s32 vc, s32 nc, u32 path, u32 seed) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context({sx(vol), sx(name), sx(static_cast<u32>(vc)), sx(static_cast<u32>(nc))}, rng);
    m.ctx.gpr[8].u64[0] = sx(path);  // $t0
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    DivideOut d;
    d.o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) d.o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    d.o.cycles = m.ctx.cycles - c0;
    d.o.checks = m.hooks.checks - k0;
    d.o.arena = m.bytes(kArena, kArenaSize);
    d.o.live_stack = m.bytes(kSp, 0x100);
    d.o.dead_stack = m.bytes(kSp - kDeadStack, kDeadStack);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    if (vol) d.vol = m.str(vol, 0x300);
    if (name) d.name = m.str(name, 0x300);
    return d;
}
}  // namespace

TEST_CASE("game(fs3): rfmai_divideFname equals its recompiled body; VOL:NAME split, default volume, length limits") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5307u};
    std::vector<std::string> paths = {"", ":", "::", "VOL:", ":NAME", "vol:name.bin", "BTL:\\BATTLE\\X.BIN", "NAME.BIN",
                                      "a:b:c", "lmap_dat.", std::string(511, 'x'), std::string(512, 'x'), std::string(513, 'x'),
                                      std::string(511, 'v') + ":n", std::string(510, 'v') + ":n", "v:" + std::string(510, 'n'),
                                      "v:" + std::string(511, 'n'), "v:" + std::string(509, 'n') + ":z"};
    const std::string alphabet = "abcVOLBTGM\\._:09";
    for (int i = 0; i < 500; ++i) {
        std::string p = random_str(rng, rng() % 14, alphabet);
        if (rng() % 10 == 0) p += std::string(490 + rng() % 30, 'q');
        paths.push_back(p);
    }
    const std::vector<std::string> names = {"VOL", "BGM", "BTL"};
    int n = 0, ok = 0, unterminated_runs = 0;
    const auto pair = [&](u32 vol, u32 name, s32 vc, s32 nc, u32 path) {
        const u32 seed = rng();
        const std::vector<u8> before = m.bytes(kArena, kArenaSize);
        DivideOut h = run_divide(m, &recomp_gen::fn_rfmai_divideFname_00566f78, vol, name, vc, nc, path, seed);
        std::memcpy(m.at(kArena), before.data(), kArenaSize);
        DivideOut r = run_divide(m, &recomp_gen::fn_rfmai_divideFname_00566f78__recomp, vol, name, vc, nc, path, seed);
        expect_same(h.o, r.o, "rfmai_divideFname");
        // The 512-byte part buffer at the bottom of the 576-byte frame, where the original put it.
        CHECK(std::equal(h.o.dead_stack.begin() + (kDeadStack - 576), h.o.dead_stack.begin() + (kDeadStack - 576) + 512,
                         r.o.dead_stack.begin() + (kDeadStack - 576)));
        ++n;
        return h;
    };
    for (const std::string& path : paths) {
        const int def = static_cast<int>(rng() % 4) - 1;  // -1: no default volume
        setup_rofs(m, names, def);
        std::memset(m.at(kA), 0, 0x700);
        m.put(kA, path);
        const std::vector<std::pair<s32, s32>> caps = {
            {9, 32}, {9, 600}, {600, 600}, {static_cast<s32>(rng() % 12) - 1, static_cast<s32>(rng() % 40) - 1}};
        for (const auto& [vc, nc] : caps) {
            std::memset(m.at(kB), 0xAA, 0x300);
            std::memset(m.at(kC), 0xBB, 0x300);
            const DivideOut h = pair(kB, kC, vc, nc, kA);
            // Host rule (docs/ANALYSIS/11 §1 step 3): the first part runs to the first ':' (at most 512 characters);
            // no ':' -> it is the name and the volume is the default one; else the volume, uppercased, and the name
            // runs to the next ':' or the end. Each part must fit its buffer with its NUL.
            const std::size_t len = path.size();
            u32 want = 0;
            std::string want_vol, want_name;
            if (vc > 0 && nc > 0 && len <= 512) {
                std::size_t i = 0;
                while (i < len && i < 512 && path[i] != ':') ++i;
                if (i == len) {
                    if (nc >= static_cast<s32>(i) + 1 && def >= 0) {
                        want = 1;
                        want_vol = names[static_cast<std::size_t>(def)];
                        want_name = path;
                    }
                } else if (vc >= static_cast<s32>(i) + 1) {
                    std::size_t j = i + 1;
                    while (j < len && j < 512 && path[j] != ':') ++j;
                    want_name = path.substr(i + 1, j - i - 1);
                    if (nc >= static_cast<s32>(want_name.size()) + 1) {
                        want = 1;
                        want_vol = upper_az(path.substr(0, i));
                    }
                }
            }
            // A path of exactly 512 characters without ':' fills the 512-byte part buffer and leaves it unterminated:
            // the strlen and memcpy that follow run on into the register save area above it ($s0 first, as the
            // prologue stored it), so the name gets those bytes appended and the copy length depends on them. Only
            // the 512-character prefix is a rule there (the pair comparison above covers the rest).
            const bool unterminated = len == 512 && path.find(':') == std::string::npos;
            if (!unterminated) CHECK(h.o.v0 == want);
            if (want && h.o.v0 == 1) {
                CHECK(h.vol == want_vol);
                if (unterminated) {
                    CHECK(h.name.size() > 512);
                    CHECK(h.name.substr(0, 512) == want_name);
                    ++unterminated_runs;
                } else {
                    CHECK(h.name == want_name);
                }
                ++ok;
            }
        }
    }
    // Null pointers.
    setup_rofs(m, names, 0);
    m.put(kA, "VOL:X");
    for (const auto& [v, nm, p] : std::vector<std::tuple<u32, u32, u32>>{{0, kC, kA}, {kB, 0, kA}, {kB, kC, 0}}) {
        const DivideOut h = pair(v, nm, 9, 32, p);
        CHECK(h.o.v0 == 0);
    }
    CHECK(unterminated_runs > 0);
    MESSAGE("rfmai_divideFname: " << n << " pairs, " << ok << " successful splits checked against the host rule ("
                                  << unterminated_runs << " with the unterminated 512-character part)");
}

TEST_CASE("game(fs3): rfmai_getVolume and sub_568368 equal their recompiled bodies; name lookup, ROFS and null -> default") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5308u};
    const std::vector<std::string> names = {"VOL", "BGM", "BTL"};
    int n = 0;
    for (int round = 0; round < 60; ++round) {
        const int def = static_cast<int>(rng() % 4) - 1;
        s32 count = round % 5 == 0 ? static_cast<s32>(rng() % 3) - 1 : 3;  // also 0 / -1 / fewer slots
        setup_rofs(m, names, def, count);
        {
            const Pair p = pair_mem(m, &recomp_gen::fn_sub_568368_00568368, &recomp_gen::fn_sub_568368_00568368__recomp, {0, 0, 0, 0}, rng(),
                                    "sub_568368");
            CHECK(p.hand.v0 == (def < 0 ? 0 : sx(kVols + static_cast<u32>(def) * 52 + 22)));
            ++n;
        }
        for (const std::string& q : {std::string("VOL"), std::string("BGM"), std::string("BTL"), std::string("ROFS"), std::string("vol"),
                                      std::string(""), std::string("VOLX"), std::string("NULL")}) {
            for (s32 use_default : {0, 1, 2}) {
                const bool null = q == "NULL";
                m.put(kA, q);
                const Pair p = pair_mem(m, &recomp_gen::fn_rfmai_getVolume_005671f0, &recomp_gen::fn_rfmai_getVolume_005671f0__recomp,
                                        {null ? 0 : sx(kA), sx(static_cast<u32>(use_default)), 0, 0}, rng(), "rfmai_getVolume",
                                        {{game::kRofsWorkPtr, 4}});
                ++n;
                // Host rule.
                std::string key = q;
                bool lookup = true;
                if (null || q == "ROFS") {
                    if (null && use_default != 1) lookup = false;
                    else if (def < 0) lookup = false;
                    else key = names[static_cast<std::size_t>(def)];
                }
                u32 want = 0;
                if (lookup)
                    for (s32 i = 0; i < count; ++i)
                        if (names[static_cast<std::size_t>(i)] == key) {
                            want = kVols + static_cast<u32>(i) * 52;
                            break;
                        }
                CHECK(p.hand.v0 == sx(want));
            }
        }
    }
    MESSAGE("rfmai_getVolume / sub_568368: " << n << " pairs");
}

TEST_CASE("game(fs3): rfmai_getDirBufAdr equals its recompiled body (HI/LO included); buffers follow the volume array") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF5309u};
    int n = 0;
    for (int round = 0; round < 50; ++round) {
        const s32 vols = round == 0 ? 3 : static_cast<s32>(rng() % 9) - 1;
        const u32 ents = round == 0 ? 836 : rng() % 2000;
        setup_rofs(m, {}, -1, vols, ents);
        for (s32 idx : {-5, -1, 0, 1, 2, vols - 1, vols, vols + 1, static_cast<s32>(rng())}) {
            Outcome o[2];
            u64 lo[2], hi[2];
            Fn fns[2] = {&recomp_gen::fn_rfmai_getDirBufAdr_00567188, &recomp_gen::fn_rfmai_getDirBufAdr_00567188__recomp};
            const u32 seed = rng();
            for (int k = 0; k < 2; ++k) {
                o[k] = run(m, fns[k], {sx(static_cast<u32>(idx)), 0, 0, 0}, seed);
                lo[k] = m.ctx.lo.u64[0];
                hi[k] = m.ctx.hi.u64[0];
            }
            expect_same(o[0], o[1], "rfmai_getDirBufAdr");
            CHECK(lo[0] == lo[1]);
            CHECK(hi[0] == hi[1]);
            const u32 want = (idx < 0 || vols < idx) ? 0 : kVols + 52 * static_cast<u32>(vols) + static_cast<u32>(idx) * (24 + 48 * ents);
            CHECK(o[0].v0 == sx(want));
            ++n;
        }
    }
    MESSAGE("rfmai_getDirBufAdr: " << n << " pairs");
}

TEST_CASE("game(fs3): sub_569BD0 / sub_569BE8 equal their recompiled bodies; 64-bit size halves") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937_64 rng{0xF530Au};
    int n = 0;
    for (int i = 0; i < 300; ++i) {
        const u64 a = i < 4 ? std::vector<u64>{0, ~0ull, 0x80000000ull, 0x7FFFFFFFFFFFFFFFull}[static_cast<std::size_t>(i)] : rng();
        const u64 b = rng();
        const Pair j = pair_mem(m, &recomp_gen::fn_sub_569BD0_00569bd0, &recomp_gen::fn_sub_569BD0_00569bd0__recomp, {a, b, 0, 0},
                                static_cast<u32>(rng()), "sub_569BD0");
        CHECK(j.hand.v0 == ((a << 32) + (b & 0xFFFFFFFFu)));
        std::memset(m.at(kOut64), 0, 8);
        const Pair s = pair_mem(m, &recomp_gen::fn_sub_569BE8_00569be8, &recomp_gen::fn_sub_569BE8_00569be8__recomp,
                                {a, sx(kOut64), sx(kOut64 + 4), 0}, static_cast<u32>(rng()), "sub_569BE8");
        CHECK(load32(m, kOut64) == static_cast<u32>(a >> 32));
        CHECK(load32(m, kOut64 + 4) == static_cast<u32>(a));
        CHECK(s.hand.v0 == sx(static_cast<u32>(a >> 32)));
        n += 2;
    }
    MESSAGE("sub_569BD0 / sub_569BE8: " << n << " pairs");
}

// --- H_Cdvd: volume routing, the request list ----------------------------------------------------------------------
namespace {
// The directory strings of the ELF (25 BTL, 123 VOL) and file names for random requests.
struct Dirs {
    std::vector<std::string> btl, vol;
};
Dirs elf_dirs(const Machine& m) { return {string_table(m, game::kHCdvdBtlDirNames, 25), string_table(m, 0x5CE590u, 123)}; }
std::string random_request(std::mt19937& rng, const Dirs& d) {
    const std::vector<std::string>& pool = (rng() & 1) ? d.btl : d.vol;
    std::string dir = pool[rng() % pool.size()];  // "\BATTLE\" etc.
    std::string name = random_str(rng, 1 + rng() % 10, "ABCDEFGHIJ0123_") + (rng() % 4 ? ".BIN" : "");
    std::string p = dir.substr(1) + name;  // the game passes paths without the leading separator
    if (rng() & 1) std::replace(p.begin(), p.end(), '\\', '/');
    return mixed_case(rng, p);
}
}  // namespace

TEST_CASE("game(fs3): H_Cdvd_BuildVolumePaths equals its recompiled body; BTL directories route to BTL:") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF530Bu};
    const Dirs d = elf_dirs(m);
    std::vector<std::string> paths = {"VOL:\\X.BIN", "VOL:\\BATTLE\\X.BIN", "VOL:\\BATTLE\\", "VOL:\\MODEL\\PACK\\A.PAK",
                                      "VOL:\\FIELD\\.\\A.BIN", "VOL:\\BATTLE\\..\\MODEL\\A", "VOL:\\BATTLE\\SUB\\..\\X",
                                      "VOL:\\" + std::string(200, 'L')};
    for (const std::string& s : d.btl) paths.push_back("VOL:" + s + "F.BIN");
    for (const std::string& s : d.vol) paths.push_back("VOL:" + s + "F.BIN");
    for (int i = 0; i < 300; ++i) paths.push_back("VOL:\\" + upper_az(random_request(rng, d)));
    std::size_t btl = 0;
    for (std::string path : paths) {
        std::replace(path.begin(), path.end(), '/', '\\');
        m.put(kA, path);
        std::memset(m.at(kC), 0x11, 0x300);
        std::memset(m.at(kD), 0x22, 0x300);
        const Pair p = pair_mem(m, &recomp_gen::fn_H_Cdvd_BuildVolumePaths_00101240, &recomp_gen::fn_H_Cdvd_BuildVolumePaths_00101240__recomp,
                                {sx(kA), sx(kD), sx(kC), 0}, rng(), "H_Cdvd_BuildVolumePaths");
        CHECK(p.hand.v0 == 0);
        CHECK(same_frame_bytes(p, 592, 80, 512));  // the normalized directory and the reversed name on the guest stack
        // Host rule for paths without "." components.
        if (path.find("\\.") == std::string::npos) {
            const std::size_t cut = path.rfind('\\');
            const std::string dir = path.substr(0, cut + 1), file = path.substr(cut + 1);
            const bool to_btl = std::find(d.btl.begin(), d.btl.end(), dir.substr(4)) != d.btl.end();
            CHECK(m.str(kC, 0x300) == dir);
            CHECK(m.str(kD, 0x300) == (to_btl ? "BTL:" : "VOL:") + file);
            btl += to_btl;
        }
    }
    MESSAGE("H_Cdvd_BuildVolumePaths: " << paths.size() << " pairs, " << btl << " routed to BTL:");
}

#endif  // P3FES_GAME_HAVE_GENERATED
