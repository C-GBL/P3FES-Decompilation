// Phase 5 pair tests for the H_Cdvd cache table and the name-first PAK indexing (game/src/hcdvd/
// hcdvd_cache.cpp, hcdvd_pak.cpp): each hand-written function and the recompiled body it replaces run
// on identical guest machines (pair_harness.h: result, callee-saved registers, memory outside the dead
// stack, virtual cycles, check-point count) -- here also the 37,888 bytes of sCdvdCache, which lives in
// .bss outside the arena -- on randomised cache tables and synthetic PAK images built by the rule of
// runtime/formats/pak.h, plus one real PAK of the disc when the extracted tree is beside the ELF; the
// documented rules of docs/ANALYSIS/11_file_io.md §2 are checked on the host independently of both.
#include "pair_harness.h"

#include "p3fes/game/hcdvd.h"

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
void fn_H_Cdvd_CacheAdd_00102650(EEContext&);
void fn_H_Cdvd_CacheAdd_00102650__recomp(EEContext&);
void fn_H_Cdvd_AddFileCacheEntry_00102030(EEContext&);
void fn_H_Cdvd_AddFileCacheEntry_00102030__recomp(EEContext&);
void fn_H_Cdvd_CacheRemove_00102870(EEContext&);
void fn_H_Cdvd_CacheRemove_00102870__recomp(EEContext&);
void fn_H_Cdvd_AddFile_00101e30(EEContext&);
void fn_H_Cdvd_AddFile_00101e30__recomp(EEContext&);
void fn_H_Cdvd_CacheAddArchive_00102720(EEContext&);
void fn_H_Cdvd_CacheAddArchive_00102720__recomp(EEContext&);
void fn_H_Cdvd_ArchiveGetFile_00102100(EEContext&);
void fn_H_Cdvd_ArchiveGetFile_00102100__recomp(EEContext&);
void fn_H_Cdvd_GetArchiveFileBuffer_001022e0(EEContext&);
void fn_H_Cdvd_GetArchiveFileBuffer_001022e0__recomp(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

// Arena layout: everything a function writes besides the cache sits in the arena, which the harness compares.
constexpr u32 kNode = kArena + 0x40;      // a request node (868 bytes)
constexpr u32 kName = kArena + 0x400;     // a 128/256-byte name buffer
constexpr u32 kDirPath = kArena + 0x500;  // a directory path (256)
constexpr u32 kSizeOut = kArena + 0x600;  // the size out-parameter
constexpr u32 kPak = kArena + 0x800;      // a synthetic PAK image (up to 0x1800 with its padding)
constexpr u32 kPakRoom = kArenaSize - 0x800;
constexpr u32 kRealPak = 0x01900000u;     // a real PAK of the disc, outside the arena (compared as a region)
constexpr u32 kFile = kNode + offsetof(game::HCdvdRequest, file);
constexpr u32 kCacheBytes = game::kHCdvdCacheSlots * static_cast<u32>(sizeof(game::HCdvdCacheEntry));
constexpr u32 kEntrySize = static_cast<u32>(sizeof(game::HCdvdCacheEntry));

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
s16 load16(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
u32 slot_va(u32 i) { return game::kHCdvdCache + i * kEntrySize; }

// The pair run of this file: besides the harness's comparison, the given guest regions (the cache
// table, a PAK outside the arena) must end identical in both runs; they are restored between the runs.
Pair run_pair_regions(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                      std::initializer_list<Reset> regions) {
    std::vector<std::vector<u8>> before, after_hand;
    for (const Reset& r : regions) before.push_back(m.bytes(r.va, r.len));
    Pair p;
    p.hand = run(m, hand, args, seed);
    for (const Reset& r : regions) after_hand.push_back(m.bytes(r.va, r.len));
    std::size_t i = 0;
    for (const Reset& r : regions) std::memcpy(m.at(r.va), before[i++].data(), r.len);
    p.recomp = run(m, recomp, args, seed);
    expect_same(p.hand, p.recomp, what);
    i = 0;
    for (const Reset& r : regions) {
        INFO(std::string(what) << ": region 0x" << std::hex << r.va);
        CHECK(after_hand[i++] == m.bytes(r.va, r.len));
    }
    return p;
}
Pair run_pair_cache(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    return run_pair_regions(m, hand, recomp, args, seed, what, {{game::kHCdvdCache, kCacheBytes}});
}

// --- cache tables ---------------------------------------------------------------------------------
struct HostSlot {
    u32 used = 0, owner = 0, data = 0, size = 0, zero = 0;
    std::vector<u8> name = std::vector<u8>(128, 0);
};
HostSlot read_slot(const Machine& m, u32 i) {
    HostSlot s;
    const u32 va = slot_va(i);
    s.used = load32(m, va + offsetof(game::HCdvdCacheEntry, used));
    s.owner = load32(m, va + offsetof(game::HCdvdCacheEntry, owner));
    s.data = load32(m, va + offsetof(game::HCdvdCacheEntry, data));
    s.size = load32(m, va + offsetof(game::HCdvdCacheEntry, size));
    s.zero = load32(m, va + offsetof(game::HCdvdCacheEntry, zero));
    s.name = m.bytes(va + offsetof(game::HCdvdCacheEntry, name), 128);
    return s;
}
bool operator==(const HostSlot& a, const HostSlot& b) {
    return a.used == b.used && a.owner == b.owner && a.data == b.data && a.size == b.size && a.zero == b.zero && a.name == b.name;
}
void write_slot(Machine& m, u32 i, const HostSlot& s) {
    const u32 va = slot_va(i);
    store32(m, va + offsetof(game::HCdvdCacheEntry, used), s.used);
    store32(m, va + offsetof(game::HCdvdCacheEntry, owner), s.owner);
    store32(m, va + offsetof(game::HCdvdCacheEntry, data), s.data);
    store32(m, va + offsetof(game::HCdvdCacheEntry, size), s.size);
    store32(m, va + offsetof(game::HCdvdCacheEntry, zero), s.zero);
    std::memcpy(m.at(va + offsetof(game::HCdvdCacheEntry, name)), s.name.data(), 128);
}
std::vector<HostSlot> read_table(const Machine& m) {
    std::vector<HostSlot> t;
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i) t.push_back(read_slot(m, i));
    return t;
}
// A random table: each slot used with probability `density` (in 1/8), owners from a small set so
// that CacheRemove hits several slots, random names (some without a NUL in their 128 bytes).
std::vector<HostSlot> random_table(std::mt19937& rng, unsigned density8, const std::vector<u32>& owners) {
    std::vector<HostSlot> t(game::kHCdvdCacheSlots);
    for (HostSlot& s : t) {
        if (rng() % 8 >= density8) continue;
        s.used = 1;
        s.owner = owners[rng() % owners.size()];
        s.data = rng();
        s.size = rng();
        s.zero = rng() % 4 == 0 ? rng() : 0;
        const std::size_t len = rng() % 130;  // 128 or 129: no terminator
        for (std::size_t k = 0; k < 128; ++k) s.name[k] = k < len ? static_cast<u8>('A' + rng() % 26) : 0;
    }
    return t;
}
void write_table(Machine& m, const std::vector<HostSlot>& t) {
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i) write_slot(m, i, t[i]);
}
int first_free(const std::vector<HostSlot>& t) {
    for (std::size_t i = 0; i < t.size(); ++i)
        if (t[i].used == 0) return static_cast<int>(i);
    return -1;
}

// --- synthetic PAKs (runtime/formats/pak.h: 252-byte name, u32 size, data, next at align64) -------------
struct PakEntry {
    std::string name;
    u32 size;               // the header word (may be "negative" in one deliberate case)
    std::vector<u8> bytes;  // the data actually laid out (size when sane, else 0)
};
struct PakImage {
    std::vector<PakEntry> entries;
    std::vector<u32> header_off;  // offset of each entry's header
    std::vector<u8> bytes;        // the image, terminator included, then zero padding
};
u32 host_align64(u32 size) {  // the compiler's signed (size + 63) / 64 * 64
    const s32 t = static_cast<s32>(size + 63u);
    const s32 q = t >= 0 ? (t >> 6) : ((t + 63) >> 6);
    return static_cast<u32>(q) << 6;
}
PakImage build_pak(const std::vector<PakEntry>& entries, u32 padding = 0x400) {
    PakImage img;
    img.entries = entries;
    for (const PakEntry& e : entries) {
        img.header_off.push_back(static_cast<u32>(img.bytes.size()));
        std::vector<u8> hdr(256, 0);
        std::memcpy(hdr.data(), e.name.data(), std::min<std::size_t>(e.name.size(), 252));
        std::memcpy(hdr.data() + 252, &e.size, 4);
        img.bytes.insert(img.bytes.end(), hdr.begin(), hdr.end());
        img.bytes.insert(img.bytes.end(), e.bytes.begin(), e.bytes.end());
        img.bytes.resize(img.header_off.back() + 256 + host_align64(e.size), 0);
    }
    img.header_off.push_back(static_cast<u32>(img.bytes.size()));  // the terminator
    img.bytes.resize(img.bytes.size() + 256 + padding, 0);
    return img;
}
const std::string kPakNameAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-/";
std::string random_pak_name(std::mt19937& rng, std::size_t len) {
    std::string s;
    for (std::size_t i = 0; i < len; ++i) s += kPakNameAlphabet[rng() % kPakNameAlphabet.size()];
    return s;
}
PakImage random_pak(std::mt19937& rng, std::size_t n, bool allow_negative = false) {
    std::vector<PakEntry> es;
    for (std::size_t i = 0; i < n; ++i) {
        PakEntry e;
        e.name = random_pak_name(rng, 1 + rng() % 20) + "." + random_pak_name(rng, 1 + rng() % 3);
        if (rng() % 8 == 0) e.name = random_pak_name(rng, 30 + rng() % 200);  // long names: the cache keeps 128 bytes
        e.size = rng() % 5 == 0 ? 0 : rng() % 321;
        if (allow_negative && i + 1 == n && rng() % 2) e.size = static_cast<u32>(-static_cast<s32>(1 + rng() % 100));  // steps 0
        if (static_cast<s32>(e.size) > 0) {
            e.bytes.resize(e.size);
            for (u8& b : e.bytes) b = static_cast<u8>(rng());
        }
        es.push_back(e);
    }
    return build_pak(es);
}
std::string upper_slashes(std::string s) {
    for (char& c : s) {
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 32);
        else if (c == '/') c = '\\';
    }
    return s;
}
// What H_Cdvd_BuildPathUppercase makes of a game path.
std::string host_built(const std::string& path) { return upper_slashes("VOL:\\" + path); }
// The name the cache gets, byte for byte: the function's 256-byte directory buffer (252 bytes of it
// copied into the name buffer, whose last 4 bytes are the frame's, zero here), the entry name appended
// at the first NUL (strcat), the uppercase pass up to the NUL it leaves (255 characters at most), and
// the slot keeps the first 128 bytes -- including whatever the directory buffer held after that NUL
// (H_Cdvd_AddFile: the rest of the file name of the path it was cut from).
std::vector<u8> host_cache_name(const std::vector<u8>& dir_buf, const std::string& entry) {
    std::vector<u8> buf(256, 0);
    std::memcpy(buf.data(), dir_buf.data(), 252);
    const std::size_t at = strnlen(reinterpret_cast<const char*>(buf.data()), 256);
    for (std::size_t i = 0; i < entry.size() && at + i < 256; ++i) buf[at + i] = static_cast<u8>(entry[i]);
    if (at + entry.size() < 256) buf[at + entry.size()] = 0;
    for (std::size_t j = 0; j < 255 && buf[j] != 0; ++j) {
        if (buf[j] >= 'a' && buf[j] <= 'z') buf[j] = static_cast<u8>(buf[j] - 32);
        if (buf[j] == '/') buf[j] = '\\';
    }
    return std::vector<u8>(buf.begin(), buf.begin() + 128);
}
// A directory buffer holding `s` (NUL-padded to 256).
std::vector<u8> dir_buffer(const std::string& s) {
    std::vector<u8> buf(256, 0);
    std::memcpy(buf.data(), s.data(), std::min<std::size_t>(s.size(), 256));
    return buf;
}
// The directory prefix H_Cdvd_AddFile cuts from file.path: up to and including the last '\' at or
// before the second-to-last character (the scan starts at path[n - 2]).
std::string host_dir_prefix(const std::string& path) {
    if (path.size() < 2) return path;
    const std::size_t b = path.rfind('\\', path.size() - 2);
    return b == std::string::npos ? path : path.substr(0, b + 1);
}

void put_pak(Machine& m, u32 va, const PakImage& img) {
    std::memcpy(m.at(va), img.bytes.data(), img.bytes.size());
}
void put_node(Machine& m, u32 node, const std::string& path, u32 data, u32 size, u32 is_archive) {
    std::memset(m.at(node), 0, sizeof(game::HCdvdRequest));
    const u32 f = node + offsetof(game::HCdvdRequest, file);
    std::memcpy(m.at(f + offsetof(game::HCdvdFile, path)), path.data(), path.size());
    store32(m, f + offsetof(game::HCdvdFile, data), data);
    store32(m, f + offsetof(game::HCdvdFile, size), size);
    store32(m, f + offsetof(game::HCdvdFile, is_archive), is_archive);
}

// The slots the archive registration must have appended, in order, starting at `from` in the table
// `before` (first free slots), with `owner` and `data` the entry data addresses at `pak`.
void check_archive_slots(const Machine& m, const std::vector<HostSlot>& before, const PakImage& img, u32 pak, u32 owner,
                         const std::vector<u8>& dir_buf, const char* what) {
    std::vector<HostSlot> expect = before;
    std::size_t next = 0;
    for (std::size_t e = 0; e < img.entries.size(); ++e) {
        while (next < expect.size() && expect[next].used) ++next;
        if (next == expect.size()) break;  // table full: the rest is dropped
        HostSlot s;
        s.used = 1;
        s.owner = owner;
        s.data = pak + img.header_off[e] + 256;
        s.size = img.entries[e].size;
        s.zero = 0;
        s.name = host_cache_name(dir_buf, img.entries[e].name);
        expect[next++] = s;
    }
    const std::vector<HostSlot> after = read_table(m);
    int bad = 0;
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i)
        if (!(after[i] == expect[i])) ++bad;
    INFO(std::string(what) << " dir \"" << std::string(reinterpret_cast<const char*>(dir_buf.data())) << "\": " << img.entries.size() << " entries");
    CHECK(bad == 0);
}

}  // namespace

TEST_CASE("game(hcdvd): H_Cdvd_CacheAdd and H_Cdvd_AddFileCacheEntry equal their recompiled bodies; the first free slot takes owner, 128 name bytes, data, size") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xADDu};
    struct Variant {
        const char* what;
        Fn hand, recomp;
    };
    const Variant variants[] = {
        {"H_Cdvd_CacheAdd", &recomp_gen::fn_H_Cdvd_CacheAdd_00102650, &recomp_gen::fn_H_Cdvd_CacheAdd_00102650__recomp},
        {"H_Cdvd_AddFileCacheEntry", &recomp_gen::fn_H_Cdvd_AddFileCacheEntry_00102030, &recomp_gen::fn_H_Cdvd_AddFileCacheEntry_00102030__recomp},
    };
    int runs = 0, full = 0;
    for (const Variant& v : variants) {
        for (int t = 0; t < 40; ++t) {
            const unsigned density = t < 36 ? static_cast<unsigned>(t % 9) : 8;  // 0/8 .. 8/8; the last four tables are full
            std::vector<HostSlot> table = random_table(rng, density, {0x9ACC80u, 0x9B0000u, kFile});
            if (t >= 36)
                for (HostSlot& s : table) s.used = 1;
            if (t == 35) table[255].used = 0;  // only the last slot free
            write_table(m, table);
            std::vector<u8> name(256);
            for (u8& b : name) b = static_cast<u8>('a' + rng() % 26);
            const std::size_t len = rng() % 140;  // >= 128: no NUL in the copied bytes
            if (len < 256) name[len] = 0;
            std::memcpy(m.at(kName), name.data(), name.size());
            const u32 owner = rng(), data = rng(), size = rng();
            const Pair p = run_pair_cache(m, v.hand, v.recomp, {sx(owner), sx(data), sx(size), sx(kName)}, rng(), v.what);
            // The rule.
            const int slot = first_free(table);
            std::vector<HostSlot> expect = table;
            if (slot >= 0) {
                HostSlot s;
                s.used = 1;
                s.owner = owner;
                s.data = data;
                s.size = size;
                s.zero = 0;
                s.name.assign(name.begin(), name.begin() + 128);
                expect[slot] = s;
                CHECK(p.hand.v0 == sx(slot_va(static_cast<u32>(slot)) + offsetof(game::HCdvdCacheEntry, name)));  // memcpy's result
            } else {
                ++full;
            }
            const std::vector<HostSlot> after = read_table(m);
            int bad = 0;
            for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i)
                if (!(after[i] == expect[i])) ++bad;
            INFO(std::string(v.what) << " table " << t << " first free " << slot);
            CHECK(bad == 0);
            ++runs;
        }
    }
    MESSAGE("H_Cdvd_CacheAdd / H_Cdvd_AddFileCacheEntry: " << runs << " tables, " << full << " full");
}

TEST_CASE("game(hcdvd): H_Cdvd_CacheRemove equals its recompiled body; clears `used` of every slot of the owner") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5E30u};
    const std::vector<u32> owners = {0x9ACC80u, 0x9B0000u, kFile, 0, 0xFFFFFFFFu};
    int runs = 0, cleared = 0;
    for (int t = 0; t < 60; ++t) {
        std::vector<HostSlot> table = random_table(rng, static_cast<unsigned>(t % 9), owners);
        write_table(m, table);
        const u32 owner = t % 7 == 6 ? rng() : owners[rng() % owners.size()];  // sometimes an owner nothing has
        run_pair_cache(m, &recomp_gen::fn_H_Cdvd_CacheRemove_00102870, &recomp_gen::fn_H_Cdvd_CacheRemove_00102870__recomp,
                       {sx(owner), 0, 0, 0}, rng(), "H_Cdvd_CacheRemove");
        std::vector<HostSlot> expect = table;
        for (HostSlot& s : expect)
            if (s.used && s.owner == owner) {
                s.used = 0;  // only `used` changes: owner/name/data stay
                ++cleared;
            }
        const std::vector<HostSlot> after = read_table(m);
        int bad = 0;
        for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i)
            if (!(after[i] == expect[i])) ++bad;
        INFO("table " << t << " owner 0x" << std::hex << owner);
        CHECK(bad == 0);
        ++runs;
    }
    MESSAGE("H_Cdvd_CacheRemove: " << runs << " tables, " << cleared << " slots cleared");
}

TEST_CASE("game(hcdvd): H_Cdvd_CacheAddArchive equals its recompiled body; every entry under UPPER(\"VOL:\\\" + dir + name), owner = the PAK") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xA2C41u};
    const std::vector<std::string> dirs = {"", "data/", "DATA\\FIELD\\", "camp/Menu/", "x", "a/b/c/d/e/"};
    int runs = 0, entries = 0;
    for (int t = 0; t < 70; ++t) {
        const std::vector<HostSlot> table = random_table(rng, t < 60 ? static_cast<unsigned>(t % 7) : 8, {0x9ACC80u});
        std::vector<HostSlot> start = table;
        if (t >= 60)
            for (u32 i = 250 + static_cast<u32>(t - 60); i < 256; ++i) start[i].used = 0;  // room for 1..6 of the entries
        write_table(m, start);
        const PakImage img = random_pak(rng, rng() % 7, t % 5 == 4);
        REQUIRE(img.bytes.size() <= kPakRoom);
        std::memset(m.at(kPak), 0, kPakRoom);
        put_pak(m, kPak, img);
        const std::string dir = dirs[rng() % dirs.size()];
        m.put(kDirPath, dir);
        const Pair p = run_pair_cache(m, &recomp_gen::fn_H_Cdvd_CacheAddArchive_00102720, &recomp_gen::fn_H_Cdvd_CacheAddArchive_00102720__recomp,
                                      {sx(kDirPath), sx(kPak), 0, 0}, rng(), "H_Cdvd_CacheAddArchive");
        CHECK(same_frame_bytes(p, 832, 48, 784));  // the name, entry, directory and size buffers of the frame
        check_archive_slots(m, start, img, kPak, kPak, dir_buffer(host_built(dir)), "H_Cdvd_CacheAddArchive");
        ++runs;
        entries += static_cast<int>(img.entries.size());
    }
    MESSAGE("H_Cdvd_CacheAddArchive: " << runs << " PAKs, " << entries << " entries");
}

TEST_CASE("game(hcdvd): H_Cdvd_AddFile equals its recompiled body; a plain file takes one slot, an archive one per entry under its directory") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xF11Eu};
    const std::vector<std::string> paths = {"VOL:\\A", "VOL:\\DIR\\FILE.PAK", "VOL:\\DATA\\FIELD\\PACK\\F001_001.PAC", "VOL:\\DIR\\",
                                            "VOL:\\CAMP\\MENU\\ITEM\\ICON.BIN", "VOL:\\X\\Y", "VOL:\\\\DOUBLE.BIN"};
    int runs = 0, archives = 0, entries = 0;
    for (int t = 0; t < 80; ++t) {
        const std::vector<HostSlot> table = random_table(rng, static_cast<unsigned>(t % 7), {0x9ACC80u, kFile});
        write_table(m, table);
        std::string path = paths[rng() % paths.size()];
        if (rng() % 3 == 0) path = host_built(random_pak_name(rng, 1 + rng() % 12) + "/" + random_pak_name(rng, 1 + rng() % 12));
        const u32 is_archive = t % 4 == 0 ? 0 : 1;
        const PakImage img = random_pak(rng, rng() % 6, t % 9 == 8);
        REQUIRE(img.bytes.size() <= kPakRoom);
        std::memset(m.at(kPak), 0, kPakRoom);
        put_pak(m, kPak, img);
        const u32 size = static_cast<u32>(img.bytes.size()) - 0x400;
        put_node(m, kNode, path, kPak, size, is_archive);
        const bool garbage = is_archive && t % 10 == 9;  // bytes after the path's NUL: copied, and every zero among them rescans
        if (garbage)
            for (u32 k = static_cast<u32>(path.size()) + 1; k < 256; ++k) m.at(kFile + offsetof(game::HCdvdFile, path) + k)[0] = static_cast<u8>(rng() % 3 ? rng() : 0);
        const Pair p = run_pair_cache(m, &recomp_gen::fn_H_Cdvd_AddFile_00101e30, &recomp_gen::fn_H_Cdvd_AddFile_00101e30__recomp,
                                      {sx(kFile), 0, 0, 0}, rng(), "H_Cdvd_AddFile");
        if (is_archive) CHECK(same_frame_bytes(p, 832, 48, 784));
        // The rule.
        if (!is_archive) {
            std::vector<HostSlot> expect = table;
            const int slot = first_free(table);
            REQUIRE(slot >= 0);
            HostSlot s;
            s.used = 1;
            s.owner = kFile;
            s.data = kPak;
            s.size = size;
            s.zero = 0;
            std::vector<u8> name(256, 0);
            std::memcpy(name.data(), path.data(), path.size());
            s.name.assign(name.begin(), name.begin() + 128);
            expect[slot] = s;
            const std::vector<HostSlot> after = read_table(m);
            int bad = 0;
            for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i)
                if (!(after[i] == expect[i])) ++bad;
            INFO("plain file \"" << path << "\"");
            CHECK(bad == 0);
            CHECK(load16(m, kFile + offsetof(game::HCdvdFile, entry_count)) == 1);
        } else if (!garbage) {
            // The directory buffer: the whole path with a NUL after its last '\' (the file name's tail stays).
            std::vector<u8> dir_buf = dir_buffer(path);
            dir_buf[host_dir_prefix(path).size()] = 0;
            check_archive_slots(m, table, img, kPak, kFile, dir_buf, "H_Cdvd_AddFile");
            CHECK(load16(m, kFile + offsetof(game::HCdvdFile, entry_count)) == static_cast<s16>(img.entries.size()));
            ++archives;
            entries += static_cast<int>(img.entries.size());
        }
        ++runs;
    }
    MESSAGE("H_Cdvd_AddFile: " << runs << " files, " << archives << " archives checked against the rule (" << entries << " entries)");
}

TEST_CASE("game(hcdvd): H_Cdvd_ArchiveGetFile and H_Cdvd_GetArchiveFileBuffer equal their recompiled bodies; entry walk by index") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x6E7Fu};
    int walks = 0, misses = 0;
    for (int t = 0; t < 60; ++t) {
        const PakImage img = random_pak(rng, rng() % 7, t % 6 == 5);
        REQUIRE(img.bytes.size() <= kPakRoom);
        std::memset(m.at(kPak), 0, kPakRoom);
        put_pak(m, kPak, img);
        put_node(m, kNode, "VOL:\\PAK.BIN", kPak, static_cast<u32>(img.bytes.size()) - 0x400, 1);
        const int n = static_cast<int>(img.entries.size());
        for (int index = -1; index <= n + 2; ++index) {
            store32(m, kSizeOut, 0xDEADBEEFu);
            const Pair pg = run_pair(m, &recomp_gen::fn_H_Cdvd_ArchiveGetFile_00102100, &recomp_gen::fn_H_Cdvd_ArchiveGetFile_00102100__recomp,
                                     {sx(kNode), sx(static_cast<u32>(index)), sx(kSizeOut), 0}, rng(), "H_Cdvd_ArchiveGetFile", {{kSizeOut, 4}});
            CHECK(same_frame_bytes(pg, 336, 80, 256));
            const Pair pb = run_pair(m, &recomp_gen::fn_H_Cdvd_GetArchiveFileBuffer_001022e0, &recomp_gen::fn_H_Cdvd_GetArchiveFileBuffer_001022e0__recomp,
                                     {sx(kNode), sx(static_cast<u32>(index)), 0, 0}, rng(), "H_Cdvd_GetArchiveFileBuffer");
            CHECK(same_frame_bytes(pb, 320, 64, 256));
            INFO("PAK " << t << " index " << index);
            if (index >= 0 && index < n) {
                // The documented walk: header `index`, its data at +256 and its size word.
                CHECK(pg.hand.v0 == sx(kPak + img.header_off[static_cast<std::size_t>(index)] + 256));
                CHECK(load32(m, kSizeOut) == img.entries[static_cast<std::size_t>(index)].size);
                CHECK(pb.hand.v0 == sx(kPak + img.header_off[static_cast<std::size_t>(index)]));
            } else if (index >= n) {
                // At or past the terminator: the walker returns 0; the blind one lands in the zero bytes.
                CHECK(pb.hand.v0 == 0);
                if (index == n) {
                    CHECK(pg.hand.v0 == sx(kPak + img.header_off[static_cast<std::size_t>(n)] + 256));
                    CHECK(load32(m, kSizeOut) == 0);
                }
                ++misses;
            } else {
                CHECK(pg.hand.v0 == sx(kPak + 256));  // a negative index: no step at all
                CHECK(pb.hand.v0 == sx(img.entries.empty() ? 0 : kPak));
            }
            ++walks;
        }
    }
    MESSAGE("H_Cdvd_ArchiveGetFile / H_Cdvd_GetArchiveFileBuffer: " << walks << " walks each, " << misses << " past the end");
}

TEST_CASE("game(hcdvd): a real PAK of the disc through CacheAddArchive, AddFile, the two walkers and CacheRemove") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    // extracted/DATA/FIELD/ICON/FICON.BIN: nine .tmx entries with lowercase names (8,320 bytes); the
    // tree is beside the ELF (extracted/disc/SLUS_216.21) when the build points at the main tree.
    const std::filesystem::path pak_path = std::filesystem::path(elf_path()).parent_path().parent_path() / "DATA" / "FIELD" / "ICON" / "FICON.BIN";
    std::ifstream in(pak_path, std::ios::binary);
    if (!in) {
        MESSAGE("SKIP: no real PAK at " << pak_path.string());
        return;
    }
    std::vector<u8> disc((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    // Parse it by the format rule into the same PakImage shape (H_Cdvd_Update appends 256 zero bytes).
    std::vector<PakEntry> es;
    for (std::size_t off = 0; off + 256 <= disc.size() && disc[off] != 0;) {
        PakEntry e;
        e.name = std::string(reinterpret_cast<const char*>(disc.data() + off), strnlen(reinterpret_cast<const char*>(disc.data() + off), 252));
        std::memcpy(&e.size, disc.data() + off + 252, 4);
        e.bytes.assign(disc.begin() + static_cast<std::ptrdiff_t>(off + 256), disc.begin() + static_cast<std::ptrdiff_t>(off + 256 + e.size));
        es.push_back(e);
        off += 256 + host_align64(e.size);
    }
    PakImage img = build_pak(es, 0x400);
    REQUIRE(img.entries.size() == 9);
    REQUIRE(disc.size() >= img.header_off.back());
    // The disc bytes themselves up to the terminator (their inter-entry padding as it is), then the
    // 256 zero bytes and room for the walkers past the end.
    img.bytes.assign(disc.begin(), disc.begin() + static_cast<std::ptrdiff_t>(img.header_off.back()));
    img.bytes.resize(img.header_off.back() + 256 + 0x400, 0);
    put_pak(m, kRealPak, img);
    const u32 pak_len = static_cast<u32>(img.bytes.size());
    std::mt19937 rng{0xF1C0Du};
    std::vector<HostSlot> table = random_table(rng, 3, {0x9ACC80u});
    write_table(m, table);

    // CacheAddArchive under "field/icon/".
    m.put(kDirPath, "field/icon/");
    Pair p = run_pair_regions(m, &recomp_gen::fn_H_Cdvd_CacheAddArchive_00102720, &recomp_gen::fn_H_Cdvd_CacheAddArchive_00102720__recomp,
                              {sx(kDirPath), sx(kRealPak), 0, 0}, rng(), "H_Cdvd_CacheAddArchive (FICON.BIN)",
                              {{game::kHCdvdCache, kCacheBytes}, {kRealPak, pak_len}});
    CHECK(same_frame_bytes(p, 832, 48, 784));
    check_archive_slots(m, table, img, kRealPak, kRealPak, dir_buffer("VOL:\\FIELD\\ICON\\"), "H_Cdvd_CacheAddArchive (FICON.BIN)");
    table = read_table(m);
    // AddFile of the same archive as H_Cdvd_Update would hand it over.
    put_node(m, kNode, "VOL:\\FIELD\\ICON\\FICON.BIN", kRealPak, static_cast<u32>(disc.size()), 1);
    p = run_pair_regions(m, &recomp_gen::fn_H_Cdvd_AddFile_00101e30, &recomp_gen::fn_H_Cdvd_AddFile_00101e30__recomp, {sx(kFile), 0, 0, 0},
                         rng(), "H_Cdvd_AddFile (FICON.BIN)", {{game::kHCdvdCache, kCacheBytes}, {kRealPak, pak_len}});
    CHECK(same_frame_bytes(p, 832, 48, 784));
    std::vector<u8> dir_buf = dir_buffer("VOL:\\FIELD\\ICON\\FICON.BIN");
    dir_buf[std::string("VOL:\\FIELD\\ICON\\").size()] = 0;
    check_archive_slots(m, table, img, kRealPak, kFile, dir_buf, "H_Cdvd_AddFile (FICON.BIN)");
    CHECK(load16(m, kFile + offsetof(game::HCdvdFile, entry_count)) == 9);
    // Each entry through both walkers.
    for (int index = 0; index <= 9; ++index) {
        store32(m, kSizeOut, 0xDEADBEEFu);
        const Pair pg = run_pair(m, &recomp_gen::fn_H_Cdvd_ArchiveGetFile_00102100, &recomp_gen::fn_H_Cdvd_ArchiveGetFile_00102100__recomp,
                                 {sx(kNode), sx(static_cast<u32>(index)), sx(kSizeOut), 0}, rng(), "H_Cdvd_ArchiveGetFile (FICON.BIN)", {{kSizeOut, 4}});
        const Pair pb = run_pair(m, &recomp_gen::fn_H_Cdvd_GetArchiveFileBuffer_001022e0, &recomp_gen::fn_H_Cdvd_GetArchiveFileBuffer_001022e0__recomp,
                                 {sx(kNode), sx(static_cast<u32>(index)), 0, 0}, rng(), "H_Cdvd_GetArchiveFileBuffer (FICON.BIN)");
        INFO("FICON.BIN index " << index);
        CHECK(pg.hand.v0 == sx(kRealPak + img.header_off[static_cast<std::size_t>(index)] + 256));
        CHECK(load32(m, kSizeOut) == (index < 9 ? img.entries[static_cast<std::size_t>(index)].size : 0));
        CHECK(pb.hand.v0 == (index < 9 ? sx(kRealPak + img.header_off[static_cast<std::size_t>(index)]) : 0));
        if (index < 9) CHECK(m.str(kRealPak + img.header_off[static_cast<std::size_t>(index)], 252) == img.entries[static_cast<std::size_t>(index)].name);
    }
    // CacheRemove of both owners leaves the table as it was before, apart from `used`.
    const std::vector<HostSlot> loaded = read_table(m);
    run_pair_cache(m, &recomp_gen::fn_H_Cdvd_CacheRemove_00102870, &recomp_gen::fn_H_Cdvd_CacheRemove_00102870__recomp, {sx(kRealPak), 0, 0, 0}, rng(),
                   "H_Cdvd_CacheRemove (FICON.BIN, CacheAddArchive's)");
    run_pair_cache(m, &recomp_gen::fn_H_Cdvd_CacheRemove_00102870, &recomp_gen::fn_H_Cdvd_CacheRemove_00102870__recomp, {sx(kFile), 0, 0, 0}, rng(),
                   "H_Cdvd_CacheRemove (FICON.BIN, AddFile's)");
    const std::vector<HostSlot> after = read_table(m);
    int removed = 0, bad = 0;
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i) {
        HostSlot e = loaded[i];
        if (e.used && (e.owner == kRealPak || e.owner == kFile)) {
            e.used = 0;
            ++removed;
        }
        if (!(after[i] == e)) ++bad;
    }
    CHECK(removed == 18);
    CHECK(bad == 0);
    MESSAGE("FICON.BIN: 9 entries registered twice and removed (" << removed << " slots)");
}

#else

TEST_CASE("game(hcdvd): cache table and PAK indexing (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game needs the ELF at configure time (P3FES_RT_EXEC_ELF)");
}

#endif
