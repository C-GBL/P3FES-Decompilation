// Phase 5 pair tests for the file-system layer (game/src/cri/rofs_dir.cpp, rofs_search.cpp,
// game/src/hcdvd/): each hand-written function and the recompiled body it replaces run on identical
// guest machines (pair_harness.h: result, callee-saved registers, memory outside the dead stack, virtual
// cycles, check-point count), on randomised inputs with the edge cases, plus the documented rules of
// docs/ANALYSIS/11_file_io.md checked independently of the recompiled body. The ROFS searches also run
// against every real `#DirLst#` table of the ELF image (149 tables, 12,463 entries).
#include "pair_harness.h"

#include "p3fes/game/cri_rofs.h"
#include "p3fes/game/hcdvd.h"

#include <algorithm>
#include <cstddef>
#include <set>
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
void fn_rfdir_isContainPeriod_0056c2e0(EEContext&);
void fn_rfdir_isContainPeriod_0056c2e0__recomp(EEContext&);
void fn_rfdirStrcmpFileName_0056bac8(EEContext&);
void fn_rfdirStrcmpFileName_0056bac8__recomp(EEContext&);
void fn_rfdir_nameBinarySearch_0056c320(EEContext&);
void fn_rfdir_nameBinarySearch_0056c320__recomp(EEContext&);
void fn_rfdir_nameSequentialSearch_0056c4b0(EEContext&);
void fn_rfdir_nameSequentialSearch_0056c4b0__recomp(EEContext&);
void fn_RFDIR_SearchName_0056c5b0(EEContext&);
void fn_RFDIR_SearchName_0056c5b0__recomp(EEContext&);
void fn_H_Cdvd_BuildPathUppercase_00101010(EEContext&);
void fn_H_Cdvd_BuildPathUppercase_00101010__recomp(EEContext&);
void fn_H_Cdvd_SplitPath_00101100(EEContext&);
void fn_H_Cdvd_SplitPath_00101100__recomp(EEContext&);
void fn_H_Cdvd_NormalizePath_001013f0(EEContext&);
void fn_H_Cdvd_NormalizePath_001013f0__recomp(EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0__recomp(EEContext&);
void fn_H_Cdvd_CacheFindFile_001021c0(EEContext&);
void fn_H_Cdvd_CacheFindFile_001021c0__recomp(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

// Arena layout shared by the tests: arguments never overlap the dead stack or the ELF image.
constexpr u32 kQuery = kArena + 0x100;   // query / path strings (up to 0x300 bytes)
constexpr u32 kOut1 = kArena + 0x800;    // first output buffer (0x400)
constexpr u32 kOut2 = kArena + 0xC00;    // second output buffer (0x400)
constexpr u32 kTable = kArena + 0x1000;  // synthetic #DirLst# table (up to 0x1000: 24 + 48 * 85)
constexpr u32 kStruct = kArena + 0x40;   // small structs (RofsVolume, H_Cdvd node, size out)

// Pointer tables to the 149 `#DirLst#` tables (docs/ANALYSIS/11 §1): 25 for BTL, 123 for VOL, BGM's root.
constexpr u32 kDirLstPtrsBtl = 0x5CDDF0u, kDirLstPtrsBtlCount = 25;
constexpr u32 kDirLstPtrsVol = 0x5CE780u, kDirLstPtrsVolCount = 123;
constexpr u32 kDirLstBgmRoot = 0x6418E0u;
constexpr u32 kDirLstVolRoot = 0x5E5150u;

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

struct DirTable {
    u32 va;
    u32 count;
};
std::vector<DirTable> dir_tables(const Machine& m) {
    std::vector<DirTable> t;
    const auto add = [&](u32 va) {
        if (std::memcmp(m.mem.main_ram() + va + offsetof(game::RofsDirLstHdr, marker), "#DirLst#", 8) == 0)
            t.push_back({va, load32(m, va)});
    };
    for (u32 i = 0; i < kDirLstPtrsBtlCount; ++i) add(load32(m, kDirLstPtrsBtl + 4 * i));
    for (u32 i = 0; i < kDirLstPtrsVolCount; ++i) add(load32(m, kDirLstPtrsVol + 4 * i));
    add(kDirLstBgmRoot);
    return t;
}
std::string entry_name(const Machine& m, u32 table, u32 i) {
    return m.str(game::rofs_dir_entry(table, i) + offsetof(game::RofsDirLstEnt, name), 34);
}
u8 entry_flags(const Machine& m, u32 table, u32 i) { return *(m.mem.main_ram() + game::rofs_dir_entry(table, i) + offsetof(game::RofsDirLstEnt, flags)); }
u8 entry_search_id(const Machine& m, u32 table, u32 i) {
    return *(m.mem.main_ram() + game::rofs_dir_entry(table, i) + offsetof(game::RofsDirLstEnt, search_id));
}

// --- host-side statements of the documented rules -------------------------------------------------
std::string upper_az(std::string s) {
    for (char& c : s)
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 32);
    return s;
}
std::string dotted(std::string s) {
    if (s.find('.') == std::string::npos) s += '.';
    return s;
}
std::string strip_dot(std::string s) {
    if (!s.empty() && s.back() == '.') s.pop_back();
    return s;
}
u8 host_search_id(const std::string& s) {
    u32 sum = 218;
    for (char ch : s) {
        u8 c = static_cast<u8>(ch);
        if (c >= 'a' && c <= 'z') c = static_cast<u8>(c - 32);
        else if (c == '.') c = 0;
        sum += c;
    }
    return static_cast<u8>(sum >> 2);
}
// rfdirStrcmpFileName: `a` ends at its NUL or at a single '.' before it; up to there `b` must match
// case-insensitively, and then `b` must end the same way. (Asymmetric: ".." equals ".", "." does not
// equal "..", because b's '.' is compared as a character while a still has one.)
bool host_file_name_equal(const std::string& a, const std::string& b) {
    const std::string head = strip_dot(a);
    if (b.size() < head.size() || upper_az(b.substr(0, head.size())) != upper_az(head)) return false;
    const std::string rest = b.substr(head.size());
    return rest.empty() || rest == ".";
}
// rfdirStrcmpDirName: case-insensitive, exact length.
bool host_dir_name_equal(const std::string& a, const std::string& b) { return upper_az(a) == upper_az(b); }
// What the binary search's deciding strcmp compares entry `i` with for `query`.
bool host_bsearch_match(const Machine& m, u32 table, u32 i, const std::string& query) {
    const std::string up = upper_az(query);
    return entry_name(m, table, i) == ((entry_flags(m, table, i) & game::kRofsDirEntFlagDir) ? up : dotted(up));
}
// First index the sequential search accepts (0-based), or -1.
int host_seq_first(const Machine& m, u32 table, const std::string& query) {
    if (query == ".") return 0;
    if (query == "..") return 1;
    const u8 id = host_search_id(query);
    const u32 count = load32(m, table);
    for (u32 i = 0; i < count; ++i) {
        if (entry_search_id(m, table, i) != id) continue;
        const std::string name = entry_name(m, table, i);
        const bool dir = entry_flags(m, table, i) & game::kRofsDirEntFlagDir;
        if (dir ? host_dir_name_equal(query, name) : host_file_name_equal(query, name)) return static_cast<int>(i);
    }
    return -1;
}

std::string mixed_case(std::mt19937& rng, std::string s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z' && (rng() & 1)) c = static_cast<char>(c + 32);
    return s;
}
std::string random_name(std::mt19937& rng, std::size_t len, const std::string& alphabet) {
    std::string s;
    for (std::size_t i = 0; i < len; ++i) s += alphabet[rng() % alphabet.size()];
    return s;
}
const std::string kNameAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

// A synthetic #DirLst# table at `va`: ".", "..", then `names` (already sorted, unique) with their flags.
void build_table(Machine& m, u32 va, const std::vector<std::pair<std::string, bool>>& entries, std::mt19937& rng) {
    const u32 n = static_cast<u32>(entries.size());
    std::memset(m.at(va), 0, 24 + 48 * (n + 2));
    store32(m, va + offsetof(game::RofsDirLstHdr, count), n);
    store32(m, va + offsetof(game::RofsDirLstHdr, count2), n);
    store32(m, va + offsetof(game::RofsDirLstHdr, dir_lba), 0x14);
    std::memcpy(m.at(va + offsetof(game::RofsDirLstHdr, marker)), "#DirLst#", 8);
    for (u32 i = 0; i < n; ++i) {
        const u32 e = game::rofs_dir_entry(va, i);
        store32(m, e + offsetof(game::RofsDirLstEnt, size_lo), rng());
        store32(m, e + offsetof(game::RofsDirLstEnt, lba), 0x20 + i);
        *m.at(e + offsetof(game::RofsDirLstEnt, flags)) = entries[i].second ? game::kRofsDirEntFlagDir : 0;
        *m.at(e + offsetof(game::RofsDirLstEnt, search_id)) = host_search_id(entries[i].first);
        std::memcpy(m.at(e + offsetof(game::RofsDirLstEnt, name)), entries[i].first.data(), entries[i].first.size());
    }
}
std::vector<std::pair<std::string, bool>> random_table_entries(std::mt19937& rng, std::size_t n) {
    std::set<std::string> stripped;
    std::vector<std::pair<std::string, bool>> body;
    while (body.size() < n) {
        std::string name = random_name(rng, 1 + rng() % 8, kNameAlphabet);
        const unsigned kind = rng() % 3;  // directory, file with an extension, extension-less file ("NAME.")
        if (kind == 1) name += "." + random_name(rng, 1 + rng() % 3, kNameAlphabet);
        else if (kind == 2) name += ".";
        if (!stripped.insert(strip_dot(name)).second) continue;
        body.emplace_back(name, kind == 0);
    }
    std::sort(body.begin(), body.end());
    std::vector<std::pair<std::string, bool>> all{{".", true}, {"..", true}};
    all.insert(all.end(), body.begin(), body.end());
    return all;
}

}  // namespace

// --------------------------------------------------------------------------------------------------
TEST_CASE("game(fs): rfdir_isContainPeriod equals its recompiled body; 1 iff the name holds a '.'") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x9E210Du};
    const std::string alphabet = "abcXYZ019_.";
    std::vector<std::string> cases = {"", ".", "a.", ".a", "abc", "a.b.c", std::string(300, 'x') + ".", std::string(40, '.')};
    for (int i = 0; i < 300; ++i) {
        std::string s = random_name(rng, rng() % 24, alphabet);
        if (rng() % 3 == 0) std::replace(s.begin(), s.end(), '.', '_');
        cases.push_back(s);
    }
    for (const std::string& s : cases) {
        m.put(kQuery, s);
        const Pair p = run_pair(m, &recomp_gen::fn_rfdir_isContainPeriod_0056c2e0, &recomp_gen::fn_rfdir_isContainPeriod_0056c2e0__recomp,
                                {sx(kQuery), 0, 0, 0}, rng(), "rfdir_isContainPeriod");
        CHECK(p.hand.v0 == (s.find('.') != std::string::npos ? 1u : 0u));
    }
    MESSAGE("rfdir_isContainPeriod: " << cases.size() << " names compared");
}

TEST_CASE("game(fs): rfdirStrcmpFileName equals its recompiled body; case-insensitive with one optional trailing '.'") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5F11E5u};
    std::vector<std::pair<std::string, std::string>> cases = {
        {"", ""},        {".", ""},       {"", "."},        {"..", "."},     {".", ".."},      {"ABC", "abc."},
        {"ABC.", "abc"}, {"ABC", "ABCD"}, {"ABCD", "ABC"},  {"A.B", "a.b"},  {"A.", "A.."},    {"A..", "A."},
        {"A.B.", "A.B"}, {"NAME", "NAME."}, {"NAME.", "NAME"}, {"X", "x"},    {"x", "Y"},       {"_", "_."},
        {"\xE9", "\xC9"}, {"a{", "A["},   {"LMAP_DAT", "lmap_dat."},          {"a.b.", "a.b.."}};
    const std::string alphabet = "abcdefxyzABCDEFXYZ0189_.";
    for (int i = 0; i < 700; ++i) {
        std::string a = random_name(rng, rng() % 12, alphabet);
        std::string b = a;
        switch (rng() % 7) {
            case 0: b = mixed_case(rng, upper_az(a)); break;             // same name, other case
            case 1: b = strip_dot(a) + "."; break;                        // trailing dot added/kept
            case 2: a = strip_dot(a); break;                              // trailing dot removed
            case 3: if (!b.empty()) b[rng() % b.size()] = '#'; break;     // one character differs
            case 4: if (!b.empty()) b.pop_back(); break;                  // b shorter
            case 5: b += random_name(rng, 1 + rng() % 3, alphabet); break; // b longer
            default: b = random_name(rng, rng() % 12, alphabet); break;   // unrelated
        }
        cases.emplace_back(a, b);
    }
    for (const auto& [a, b] : cases) {
        m.put(kQuery, a);
        m.put(kQuery + 0x100, b);
        const Pair p = run_pair(m, &recomp_gen::fn_rfdirStrcmpFileName_0056bac8, &recomp_gen::fn_rfdirStrcmpFileName_0056bac8__recomp,
                                {sx(kQuery), sx(kQuery + 0x100), 0, 0}, rng(), "rfdirStrcmpFileName");
        INFO("a=\"" << a << "\" b=\"" << b << "\"");
        CHECK(p.hand.v0 == (host_file_name_equal(a, b) ? 1u : 0u));
    }
    MESSAGE("rfdirStrcmpFileName: " << cases.size() << " pairs compared");
}

TEST_CASE("game(fs): rfdir_nameBinarySearch equals its recompiled body on every entry of the 149 real #DirLst# tables") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xB15EA2C4u};
    const std::vector<DirTable> tables = dir_tables(m);
    REQUIRE(tables.size() == 149);
    int entries = 0, at_own_index = 0, misses = 0;
    for (const DirTable& t : tables) {
        for (u32 i = 0; i < t.count; ++i) {
            const std::string stored = entry_name(m, t.va, i);
            std::string query = mixed_case(rng, stored);
            if (i >= 2 && !stored.empty() && stored.back() == '.' && (rng() & 1)) query = strip_dot(query);  // extension-less files are opened without the '.'
            m.put(kQuery, query);
            const Pair p = run_pair(m, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320__recomp,
                                    {sx(kQuery), sx(t.va), 0, 0}, rng(), "rfdir_nameBinarySearch (real table)");
            CHECK(same_frame_bytes(p, 1104, 0, 1024));  // the two query buffers land where the original put them
            const u32 r = static_cast<u32>(p.hand.v0);
            INFO("table 0x" << std::hex << t.va << " entry " << std::dec << i << " \"" << query << "\" -> " << r);
            if (i < 2) {
                CHECK(r == i + 1);
            } else {
                CHECK(r != 0);
                if (r != 0 && r <= t.count) CHECK(host_bsearch_match(m, t.va, r - 1, query));
                if (r == i + 1) ++at_own_index;
            }
            ++entries;
        }
        // Misses: names that no entry matches must give 0, a few per table.
        for (int k = 0; k < 3; ++k) {
            std::string query = random_name(rng, 1 + rng() % 10, kNameAlphabet);
            if (rng() & 1) query += ".BIN";
            bool exists = false;
            for (u32 i = 2; i < t.count; ++i) exists = exists || host_bsearch_match(m, t.va, i, query);
            if (exists) continue;
            m.put(kQuery, query);
            const Pair p = run_pair(m, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320__recomp,
                                    {sx(kQuery), sx(t.va), 0, 0}, rng(), "rfdir_nameBinarySearch (miss)");
            CHECK(p.hand.v0 == 0);
            ++misses;
        }
    }
    // A null name is refused before anything is read.
    const Pair p0 = run_pair(m, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320__recomp,
                             {0, sx(kDirLstVolRoot), 0, 0}, rng(), "rfdir_nameBinarySearch (null name)");
    CHECK(p0.hand.v0 == 0);
    // Documented examples on the VOL root (docs/ANALYSIS/11 §1): 1-based, case-insensitive, "." and "..".
    {
        rt_test::HooksScope scope{&m.hooks};
        rt::bind_context(&m.ctx);
        Args a{};
        std::mt19937 r2{1};
        m.fresh_context(a, r2);
        m.put(kQuery, "bustup");
        CHECK(game::rfdir_nameBinarySearch(m.ctx, kQuery, kDirLstVolRoot) == 3);  // entry 2 is "BUSTUP"
        m.put(kQuery, "CAMP");
        CHECK(game::rfdir_nameBinarySearch(m.ctx, kQuery, kDirLstVolRoot) == 4);
        m.put(kQuery, ".");
        CHECK(game::rfdir_nameBinarySearch(m.ctx, kQuery, kDirLstVolRoot) == 1);
        m.put(kQuery, "..");
        CHECK(game::rfdir_nameBinarySearch(m.ctx, kQuery, kDirLstVolRoot) == 2);
        m.put(kQuery, "nothing_like_this");
        CHECK(game::rfdir_nameBinarySearch(m.ctx, kQuery, kDirLstVolRoot) == 0);
        std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    }
    MESSAGE("rfdir_nameBinarySearch: " << entries << " real entries (" << at_own_index << " found at their own index), " << misses << " misses");
}

TEST_CASE("game(fs): rfdir_nameBinarySearch equals its recompiled body on synthetic tables (counts 0..12, dotted and plain names, misses, empty query)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7AB1E5u};
    int cases = 0;
    for (int round = 0; round < 120; ++round) {
        const std::size_t n = (round < 4) ? static_cast<std::size_t>(round) : rng() % 11;
        std::vector<std::pair<std::string, bool>> entries = random_table_entries(rng, n);
        if (round < 3) entries.resize(static_cast<std::size_t>(round));  // counts 0, 1, 2: no searchable entry at all
        build_table(m, kTable, entries, rng);
        std::vector<std::string> queries;
        for (const auto& [name, dir] : entries) {
            queries.push_back(mixed_case(rng, name));
            if (!dir && name.back() == '.') queries.push_back(mixed_case(rng, strip_dot(name)));
        }
        queries.push_back("");
        queries.push_back(".");
        queries.push_back("..");
        for (int k = 0; k < 4; ++k) queries.push_back(random_name(rng, 1 + rng() % 9, kNameAlphabet));
        for (const std::string& q : queries) {
            m.put(kQuery, q);
            const Pair p = run_pair(m, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320, &recomp_gen::fn_rfdir_nameBinarySearch_0056c320__recomp,
                                    {sx(kQuery), sx(kTable), 0, 0}, rng(), "rfdir_nameBinarySearch (synthetic)", {{kTable, 0x1000}});
            CHECK(same_frame_bytes(p, 1104, 0, 1024));
            const u32 r = static_cast<u32>(p.hand.v0);
            INFO("count " << entries.size() << " query \"" << q << "\" -> " << r);
            if (q == ".") CHECK(r == 1);
            else if (q == "..") CHECK(r == 2);
            else {
                bool exists = false;
                for (u32 i = 2; i < entries.size(); ++i) exists = exists || host_bsearch_match(m, kTable, i, q);
                CHECK((r != 0) == exists);
                if (r >= 3 && r <= entries.size()) CHECK(host_bsearch_match(m, kTable, r - 1, q));
            }
            ++cases;
        }
    }
    MESSAGE("rfdir_nameBinarySearch: " << cases << " synthetic cases");
}

TEST_CASE("game(fs): rfdir_nameSequentialSearch equals its recompiled body on the real tables and synthetic ones; first search_id + name match") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5E0A1u};
    const std::vector<DirTable> tables = dir_tables(m);
    REQUIRE(tables.size() == 149);
    int entries = 0, misses = 0;
    for (const DirTable& t : tables) {
        for (u32 i = 0; i < t.count; ++i) {
            const std::string stored = entry_name(m, t.va, i);
            std::string query = mixed_case(rng, stored);
            if (i >= 2 && !stored.empty() && stored.back() == '.' && (rng() & 1)) query = strip_dot(query);
            m.put(kQuery, query);
            const Pair p = run_pair(m, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0__recomp,
                                    {sx(kQuery), sx(t.va), 0, 0}, rng(), "rfdir_nameSequentialSearch (real table)");
            INFO("table 0x" << std::hex << t.va << " entry " << std::dec << i << " \"" << query << "\" -> " << p.hand.v0);
            CHECK(p.hand.v0 == static_cast<u64>(host_seq_first(m, t.va, query) + 1));
            ++entries;
        }
        for (int k = 0; k < 2; ++k) {
            const std::string query = random_name(rng, 1 + rng() % 10, kNameAlphabet) + ((rng() & 1) ? ".BIN" : "");
            m.put(kQuery, query);
            const Pair p = run_pair(m, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0__recomp,
                                    {sx(kQuery), sx(t.va), 0, 0}, rng(), "rfdir_nameSequentialSearch (miss)");
            CHECK(p.hand.v0 == static_cast<u64>(host_seq_first(m, t.va, query) + 1));
            ++misses;
        }
    }
    // Null name; empty table (count 0); a table whose count is negative is treated as empty.
    const Pair p0 = run_pair(m, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0__recomp,
                             {0, sx(kDirLstVolRoot), 0, 0}, rng(), "rfdir_nameSequentialSearch (null name)");
    CHECK(p0.hand.v0 == 0);
    int synthetic = 0;
    for (int round = 0; round < 60; ++round) {
        std::vector<std::pair<std::string, bool>> entries_s = random_table_entries(rng, rng() % 10);
        if (round == 0) entries_s.clear();
        build_table(m, kTable, entries_s, rng);
        if (round == 1) store32(m, kTable, 0xFFFFFFFFu);
        std::vector<std::string> queries{".", "..", "", "ZZZ"};
        for (const auto& [name, dir] : entries_s) {
            queries.push_back(mixed_case(rng, name));
            if (!dir) queries.push_back(mixed_case(rng, strip_dot(name)) + ((rng() & 1) ? "." : ""));
        }
        for (const std::string& q : queries) {
            m.put(kQuery, q);
            const Pair p = run_pair(m, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0, &recomp_gen::fn_rfdir_nameSequentialSearch_0056c4b0__recomp,
                                    {sx(kQuery), sx(kTable), 0, 0}, rng(), "rfdir_nameSequentialSearch (synthetic)");
            INFO("round " << round << " query \"" << q << "\" -> " << p.hand.v0);
            if (round == 1) CHECK(p.hand.v0 == (q == "." ? 1u : q == ".." ? 2u : 0u));
            else CHECK(p.hand.v0 == static_cast<u64>(host_seq_first(m, kTable, q) + 1));
            ++synthetic;
        }
    }
    MESSAGE("rfdir_nameSequentialSearch: " << entries << " real entries, " << misses << " misses, " << synthetic << " synthetic cases");
}

TEST_CASE("game(fs): RFDIR_SearchName equals its recompiled body; binary search iff the volume has an LBA offset, 0 for no volume") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5EA2C4u};
    const u32 vol = kStruct;
    int cases = 0;
    for (int i = 0; i < 160; ++i) {
        const u32 offsets[] = {3, 0, 0xFFFFFFFFu, 1};
        const u32 lba_offset = offsets[i % 4];
        std::memset(m.at(vol), 0, sizeof(game::RofsVolume));
        store32(m, vol + offsetof(game::RofsVolume, lba_offset), lba_offset);
        store32(m, vol + offsetof(game::RofsVolume, dir), kDirLstVolRoot);
        const u32 count = load32(m, kDirLstVolRoot);
        const std::string stored = entry_name(m, kDirLstVolRoot, rng() % count);
        const std::string query = (i % 5 == 4) ? random_name(rng, 1 + rng() % 8, kNameAlphabet) : mixed_case(rng, stored);
        m.put(kQuery, query);
        const Pair p = run_pair(m, &recomp_gen::fn_RFDIR_SearchName_0056c5b0, &recomp_gen::fn_RFDIR_SearchName_0056c5b0__recomp,
                                {sx(kQuery), sx(kDirLstVolRoot), sx(vol), 0}, rng(), "RFDIR_SearchName");
        // The same answer as the search it dispatches to, run directly.
        rt_test::HooksScope scope{&m.hooks};
        rt::bind_context(&m.ctx);
        Args a{};
        std::mt19937 r2{7};
        m.fresh_context(a, r2);
        const s32 direct = lba_offset != 0 ? game::rfdir_nameBinarySearch(m.ctx, kQuery, kDirLstVolRoot)
                                           : game::rfdir_nameSequentialSearch(m.ctx, kQuery, kDirLstVolRoot);
        std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
        CHECK(static_cast<s32>(p.hand.v0) == direct);
        ++cases;
    }
    m.put(kQuery, "BUSTUP");
    const Pair p0 = run_pair(m, &recomp_gen::fn_RFDIR_SearchName_0056c5b0, &recomp_gen::fn_RFDIR_SearchName_0056c5b0__recomp,
                             {sx(kQuery), sx(kDirLstVolRoot), 0, 0}, rng(), "RFDIR_SearchName (null volume)");
    CHECK(p0.hand.v0 == 0);
    MESSAGE("RFDIR_SearchName: " << cases << " cases");
}

// --------------------------------------------------------------------------------------------------
TEST_CASE("game(fs): H_Cdvd_BuildPathUppercase equals its recompiled body; \"VOL:\\\" + path, '/' -> '\\', a-z uppercased, cut at 255") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xB01D9A7Bu};
    REQUIRE(m.str(game::kHCdvdVolPrefix) == "VOL:\\");
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_./\\`{@[";
    std::vector<std::string> paths = {"", "a", "/", "data/file.bin", "DATA\\FILE.BIN", "camp/cmp_t.pac", std::string(254, 'q'),
                                      std::string(255, 'r'), std::string(256, 's'), std::string(300, 't') + "/x", "\x80\xE9\xFF"};
    for (int i = 0; i < 400; ++i) {
        std::string p = random_name(rng, rng() % 70, alphabet);
        if (rng() % 10 == 0) p += std::string(200 + rng() % 70, 'z');
        if (rng() % 8 == 0) for (char& c : p) if (rng() % 5 == 0) c = static_cast<char>(0x80 + rng() % 128);
        paths.push_back(p);
    }
    for (const std::string& path : paths) {
        m.put(kQuery, path);
        std::memset(m.at(kOut1), 0xAA, 0x400);  // the bytes the function does not write stay (both runs see them)
        const Pair p = run_pair(m, &recomp_gen::fn_H_Cdvd_BuildPathUppercase_00101010, &recomp_gen::fn_H_Cdvd_BuildPathUppercase_00101010__recomp,
                                {sx(kQuery), sx(kOut1), 0, 0}, rng(), "H_Cdvd_BuildPathUppercase", {{kOut1, 0x400}});
        std::string expect = "VOL:\\";
        for (std::size_t k = 0; k < path.size() && k < 255; ++k) {
            char c = path[k];
            if (c == '/') c = '\\';
            else if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 32);
            expect += c;
        }
        const std::vector<u8> out = m.bytes(kOut1, static_cast<u32>(expect.size()) + 1);
        INFO("path length " << path.size());
        CHECK(std::string(out.begin(), out.end() - 1) == expect);
        CHECK(out.back() == (path.size() < 255 ? 0 : 0xAA));  // no terminator after 255 characters
    }
    MESSAGE("H_Cdvd_BuildPathUppercase: " << paths.size() << " paths");
}

TEST_CASE("game(fs): H_Cdvd_SplitPath equals its recompiled body; \"VOL:\" + name after the last '\\', directory up to it") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5B117u};
    REQUIRE(m.str(load32(m, game::kHCdvdVolPrefixPtr)) == "VOL:");
    std::vector<std::string> paths = {"VOL:\\A\\B\\C.EXT", "VOL:\\X", "VOL:\\", "VOL:\\\\A", "NOSEP", "", "A", "\\", "AB\\", "\\X.Y", "VOL:\\LONG\\" + std::string(200, 'n')};
    const std::string alphabet = "ABCXYZ019_.\\\\\\";
    for (int i = 0; i < 300; ++i) paths.push_back(((rng() & 1) ? "VOL:\\" : "") + random_name(rng, rng() % 40, alphabet));
    for (const std::string& path : paths) {
        m.put(kQuery, path);
        std::memset(m.at(kOut1), 0x55, 0x400);
        std::memset(m.at(kOut2), 0x66, 0x400);
        const Pair p = run_pair(m, &recomp_gen::fn_H_Cdvd_SplitPath_00101100, &recomp_gen::fn_H_Cdvd_SplitPath_00101100__recomp,
                                {sx(kQuery), sx(kOut1), sx(kOut2), 0}, rng(), "H_Cdvd_SplitPath", {{kOut1, 0x400}, {kOut2, 0x400}});
        CHECK(same_frame_bytes(p, 336, 80, 256));  // the reversed name sits in the frame where the original kept it
        const std::size_t cut = path.find_last_of('\\');
        INFO("path \"" << path << "\"");
        if (cut != std::string::npos && cut > 0) {
            CHECK(m.str(kOut1) == "VOL:" + path.substr(cut + 1));
            CHECK(m.str(kOut2) == path.substr(0, cut + 1));
        } else if (cut == 0) {  // path[0] is never examined: a leading '\' alone does not split
            CHECK(m.str(kOut2) == path);
        }
    }
    MESSAGE("H_Cdvd_SplitPath: " << paths.size() << " paths");
}

namespace {
// The documented rule of H_Cdvd_NormalizePath, written independently of the cycle-mirroring version.
std::string host_normalize(const std::string& src) {
    std::string out;
    const auto at = [&](std::size_t i) -> char { return i < src.size() ? src[i] : 0; };
    std::size_t in = 0;
    while (static_cast<int>(in) < 253) {
        const char c = at(in);
        if (c == 0) return out;
        if (c == '.' && at(in + 1) == '.' && (at(in + 2) == '\\' || at(in + 2) == '/')) {
            in += 2;
            if (out.size() >= 3) {
                int q = static_cast<int>(out.size()) - 2;
                for (; q >= 0; --q)
                    if (out[static_cast<std::size_t>(q)] == '\\' || out[static_cast<std::size_t>(q)] == '/') break;
                if (q >= 0) out.resize(static_cast<std::size_t>(q) + 1);
            }
        } else if (c == '.' && (at(in + 1) == '\\' || at(in + 1) == '/')) {
            in += 1;
        } else {
            out += c;
        }
        ++in;
    }
    return out + '\x01';  // marker: no terminator written
}
}  // namespace

TEST_CASE("game(fs): H_Cdvd_NormalizePath equals its recompiled body; \".\\\" dropped, \"..\\\" pops a component, 253-character limit") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x0A11CEu};
    std::vector<std::string> paths = {"", "VOL:\\A\\..\\B", "VOL:\\.\\A", "AB\\..\\C", "X\\AB\\..\\C", "..\\A", ".\\", "..\\", "A\\B\\..\\..\\C",
                                      "A/B/../C", "A\\./B", "...", ".", "..", "A\\...\\B", "VOL:\\DATA\\..\\..\\..\\X.BIN", std::string(252, 'a') + "\\b",
                                      std::string(253, 'a'), std::string(300, 'a'), std::string(251, 'a') + "..\\", std::string(250, 'a') + "\\..\\Z"};
    const std::vector<std::string> tokens = {"A", "BC", "D1", "\\", "/", ".", "..", "..\\", "../", ".\\", "./", "VOL:\\", "..."};
    for (int i = 0; i < 500; ++i) {
        std::string p;
        const std::size_t n = rng() % 14;
        for (std::size_t k = 0; k < n; ++k) p += tokens[rng() % tokens.size()];
        if (rng() % 12 == 0) p += std::string(240 + rng() % 30, 'x');
        paths.push_back(p);
    }
    for (const std::string& path : paths) {
        m.put(kQuery, path);
        std::memset(m.at(kOut1), 0x77, 0x400);
        const Pair p = run_pair(m, &recomp_gen::fn_H_Cdvd_NormalizePath_001013f0, &recomp_gen::fn_H_Cdvd_NormalizePath_001013f0__recomp,
                                {sx(kQuery), sx(kOut1), 0, 0}, rng(), "H_Cdvd_NormalizePath", {{kOut1, 0x400}});
        std::string expect = host_normalize(path);
        const bool terminated = expect.empty() || expect.back() != '\x01';
        if (!terminated) expect.pop_back();
        const std::vector<u8> out = m.bytes(kOut1, static_cast<u32>(expect.size()) + 1);
        INFO("path \"" << path << "\"");
        CHECK(std::string(out.begin(), out.end() - 1) == expect);
        CHECK(out.back() == (terminated ? 0 : 0x77));
    }
    MESSAGE("H_Cdvd_NormalizePath: " << paths.size() << " paths");
}

TEST_CASE("game(fs): H_Cdvd_IsFileLoaded equals its recompiled body; state 4 only") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x10ADEDu};
    const u32 node = kStruct;
    for (int i = 0; i < 64; ++i) {
        const u32 state = (i < 10) ? static_cast<u32>(i) : (i < 14 ? 0x80000004u + static_cast<u32>(i) : rng());
        std::memset(m.at(node), 0x5A, 64);
        store32(m, node + game::kHCdvdNodeState, state);
        const Pair p = run_pair(m, &recomp_gen::fn_H_Cdvd_IsFileLoaded_001016b0, &recomp_gen::fn_H_Cdvd_IsFileLoaded_001016b0__recomp,
                                {sx(node), 0, 0, 0}, rng(), "H_Cdvd_IsFileLoaded");
        CHECK(p.hand.v0 == (state == 4 ? 1u : 0u));
    }
}

TEST_CASE("game(fs): H_Cdvd_CacheFindFile equals its recompiled body; built + normalized path against each used slot's normalized name") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xCAC4Eu};
    // Fill sCdvdCache (in .bss, zero in the image): used slots with names as H_Cdvd_AddFile registers
    // them, some with ".\" / "..\" inside, some unused slots in between, one used slot with an empty name.
    const auto slot = [](u32 i) { return game::kHCdvdCache + i * static_cast<u32>(sizeof(game::HCdvdCacheEntry)); };
    std::vector<std::pair<u32, std::string>> used;  // slot index, registered name
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i) {
        std::memset(m.at(slot(i)), 0, sizeof(game::HCdvdCacheEntry));
        if (i % 3 == 1 || i > 200) continue;
        std::string name = "VOL:\\DIR" + std::to_string(i % 7) + "\\FILE" + std::to_string(i) + ".BIN";
        if (i % 5 == 0) name = "VOL:\\DIR" + std::to_string(i % 7) + "\\.\\FILE" + std::to_string(i) + ".BIN";
        if (i % 11 == 0) name = "VOL:\\X\\..\\DIR" + std::to_string(i % 7) + "\\FILE" + std::to_string(i) + ".BIN";
        if (i == 60) name = "";
        if (i == 63) name = "vol:\\dir0\\lower.bin";  // registered lowercase: never equals a built (uppercased) path
        store32(m, slot(i) + offsetof(game::HCdvdCacheEntry, used), 1);
        store32(m, slot(i) + offsetof(game::HCdvdCacheEntry, owner), i);
        std::memcpy(m.at(slot(i) + offsetof(game::HCdvdCacheEntry, name)), name.data(), name.size());
        store32(m, slot(i) + offsetof(game::HCdvdCacheEntry, data), 0x00A00000u + i * 0x1000u);
        store32(m, slot(i) + offsetof(game::HCdvdCacheEntry, size), 100 + i);
        used.emplace_back(i, name);
    }
    const u32 size_out = kStruct;
    std::vector<std::string> paths = {"dir0/file0.bin", "DIR1\\FILE12.BIN", "dir5/./file5.bin", "x/../dir6/file6.bin", "dir0/lower.bin",
                                      "nothing.bin", "", "dir3\\file201.bin", "dir4\\file11.bin", "DIR2\\FILE93.BIN"};
    for (int i = 0; i < 150; ++i) {
        const u32 k = used[rng() % used.size()].first;
        std::string p = "dir" + std::to_string(k % 7) + "/file" + std::to_string(k) + ".bin";
        if (rng() % 4 == 0) p = "dir" + std::to_string(k % 7) + "/../dir" + std::to_string(k % 7) + "/file" + std::to_string(k) + ".bin";
        if (rng() % 6 == 0) p[rng() % p.size()] = '#';
        paths.push_back(mixed_case(rng, p));
    }
    int hits = 0;
    for (const std::string& path : paths) {
        m.put(kQuery, path);
        store32(m, size_out, 0xDEADBEEFu);
        const Pair p = run_pair(m, &recomp_gen::fn_H_Cdvd_CacheFindFile_001021c0, &recomp_gen::fn_H_Cdvd_CacheFindFile_001021c0__recomp,
                                {sx(kQuery), sx(size_out), 0, 0}, rng(), "H_Cdvd_CacheFindFile", {{size_out, 4}});
        CHECK(same_frame_bytes(p, 816, 48, 768));  // the three path buffers sit in the frame where the original kept them
        // The rule: the first used slot whose normalized name equals the normalized built path.
        std::string built = "VOL:\\";
        for (char c : path) built += (c == '/') ? '\\' : (c >= 'a' && c <= 'z') ? static_cast<char>(c - 32) : c;
        const std::string query = host_normalize(built);
        u32 expect_data = 0, expect_size = 0xDEADBEEFu;
        for (const auto& [idx, name] : used) {
            if (host_normalize(name) != query) continue;
            expect_data = 0x00A00000u + idx * 0x1000u;
            expect_size = 100 + idx;
            break;
        }
        INFO("path \"" << path << "\"");
        CHECK(p.hand.v0 == sx(expect_data));
        CHECK(load32(m, size_out) == expect_size);
        if (expect_data) ++hits;
    }
    // The sentinel path value 1 returns 0 without touching anything.
    store32(m, size_out, 0xDEADBEEFu);
    const Pair p1 = run_pair(m, &recomp_gen::fn_H_Cdvd_CacheFindFile_001021c0, &recomp_gen::fn_H_Cdvd_CacheFindFile_001021c0__recomp,
                             {1, sx(size_out), 0, 0}, rng(), "H_Cdvd_CacheFindFile (sentinel)");
    CHECK(p1.hand.v0 == 0);
    CHECK(load32(m, size_out) == 0xDEADBEEFu);
    MESSAGE("H_Cdvd_CacheFindFile: " << paths.size() << " paths, " << hits << " hits");
}

#else

TEST_CASE("game(fs): file-system layer (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game needs the ELF at configure time (P3FES_RT_EXEC_ELF)");
}

#endif
