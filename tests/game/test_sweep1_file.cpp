// Pair tests of slice sweep1, group file (game/src/sweep/sweep1_file.cpp): every body against its recompiled body
// (handgen_pairs.h / pair_harness.h / stand_ins.h) on
//   * random worlds: the p3fes_handgen sweep;
//   * the dorm snapshot's sCdvdCache: the "pak:" RtFS device opens real cached files by name, reads their bytes,
//     seeks by the three whence rules, reports the end and the existence (each checked on the host);
//   * the stand-in heap: the two device installers' file-system record and file objects, h_chkmem's malloc / free
//     header and running total.
#include "sweep1_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_100210_00100210(EEContext&);  // generated body
void fn_sub_100210_00100210__recomp(EEContext&);  // recompiled
void fn_sub_100218_00100218(EEContext&);  // generated body
void fn_sub_100218_00100218__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_RtFsPak_FOpen_001016d0(EEContext&);  // generated body
void fn_H_Cdvd_RtFsPak_FOpen_001016d0__recomp(EEContext&);  // recompiled
void fn_sub_101800_00101800(EEContext&);  // generated body
void fn_sub_101800_00101800__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_RtFsPak_FRead_00101810(EEContext&);  // generated body
void fn_H_Cdvd_RtFsPak_FRead_00101810__recomp(EEContext&);  // recompiled
void fn_sub_1018A0_001018a0(EEContext&);  // generated body
void fn_sub_1018A0_001018a0__recomp(EEContext&);  // recompiled
void fn_sub_1018C0_001018c0(EEContext&);  // generated body
void fn_sub_1018C0_001018c0__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_RtFsPak_Get_001019a0(EEContext&);  // generated body
void fn_H_Cdvd_RtFsPak_Get_001019a0__recomp(EEContext&);  // recompiled
void fn_sub_1019E0_001019e0(EEContext&);  // generated body
void fn_sub_1019E0_001019e0__recomp(EEContext&);  // recompiled
void fn_sub_101A10_00101a10(EEContext&);  // generated body
void fn_sub_101A10_00101a10__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_InitRtFsPak_00101ad0(EEContext&);  // generated body
void fn_H_Cdvd_InitRtFsPak_00101ad0__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_InitRtFS_00101c70(EEContext&);  // generated body
void fn_H_Cdvd_InitRtFS_00101c70__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_StartSfd_001023f0(EEContext&);  // generated body
void fn_H_Cdvd_StartSfd_001023f0__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_StartADXTFileRange_00102530(EEContext&);  // generated body
void fn_H_Cdvd_StartADXTFileRange_00102530__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_StartADXTFile_001025c0(EEContext&);  // generated body
void fn_H_Cdvd_StartADXTFile_001025c0__recomp(EEContext&);  // recompiled
void fn_sub_1028D0_001028d0(EEContext&);  // generated body
void fn_sub_1028D0_001028d0__recomp(EEContext&);  // recompiled
void fn_sub_102D90_00102d90(EEContext&);  // generated body
void fn_sub_102D90_00102d90__recomp(EEContext&);  // recompiled
void fn_sub_102E00_00102e00(EEContext&);  // generated body
void fn_sub_102E00_00102e00__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_InitRtFsHdd_00102e50(EEContext&);  // generated body
void fn_H_Cdvd_InitRtFsHdd_00102e50__recomp(EEContext&);  // recompiled
void fn_sub_103D00_00103d00(EEContext&);  // generated body
void fn_sub_103D00_00103d00__recomp(EEContext&);  // recompiled
void fn_sub_103DA0_00103da0(EEContext&);  // generated body
void fn_sub_103DA0_00103da0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_100210", 0x100210, &recomp_gen::fn_sub_100210_00100210, &recomp_gen::fn_sub_100210_00100210__recomp},
    {"sub_100218", 0x100218, &recomp_gen::fn_sub_100218_00100218, &recomp_gen::fn_sub_100218_00100218__recomp},
    {"H_Cdvd_RtFsPak_FOpen", 0x1016D0, &recomp_gen::fn_H_Cdvd_RtFsPak_FOpen_001016d0, &recomp_gen::fn_H_Cdvd_RtFsPak_FOpen_001016d0__recomp},
    {"sub_101800", 0x101800, &recomp_gen::fn_sub_101800_00101800, &recomp_gen::fn_sub_101800_00101800__recomp},
    {"H_Cdvd_RtFsPak_FRead", 0x101810, &recomp_gen::fn_H_Cdvd_RtFsPak_FRead_00101810, &recomp_gen::fn_H_Cdvd_RtFsPak_FRead_00101810__recomp},
    {"sub_1018A0", 0x1018A0, &recomp_gen::fn_sub_1018A0_001018a0, &recomp_gen::fn_sub_1018A0_001018a0__recomp},
    {"sub_1018C0", 0x1018C0, &recomp_gen::fn_sub_1018C0_001018c0, &recomp_gen::fn_sub_1018C0_001018c0__recomp},
    {"H_Cdvd_RtFsPak_Get", 0x1019A0, &recomp_gen::fn_H_Cdvd_RtFsPak_Get_001019a0, &recomp_gen::fn_H_Cdvd_RtFsPak_Get_001019a0__recomp},
    {"sub_1019E0", 0x1019E0, &recomp_gen::fn_sub_1019E0_001019e0, &recomp_gen::fn_sub_1019E0_001019e0__recomp},
    {"sub_101A10", 0x101A10, &recomp_gen::fn_sub_101A10_00101a10, &recomp_gen::fn_sub_101A10_00101a10__recomp},
    {"H_Cdvd_InitRtFsPak", 0x101AD0, &recomp_gen::fn_H_Cdvd_InitRtFsPak_00101ad0, &recomp_gen::fn_H_Cdvd_InitRtFsPak_00101ad0__recomp},
    {"H_Cdvd_InitRtFS", 0x101C70, &recomp_gen::fn_H_Cdvd_InitRtFS_00101c70, &recomp_gen::fn_H_Cdvd_InitRtFS_00101c70__recomp},
    {"H_Cdvd_StartSfd", 0x1023F0, &recomp_gen::fn_H_Cdvd_StartSfd_001023f0, &recomp_gen::fn_H_Cdvd_StartSfd_001023f0__recomp},
    {"H_Cdvd_StartADXTFileRange", 0x102530, &recomp_gen::fn_H_Cdvd_StartADXTFileRange_00102530, &recomp_gen::fn_H_Cdvd_StartADXTFileRange_00102530__recomp},
    {"H_Cdvd_StartADXTFile", 0x1025C0, &recomp_gen::fn_H_Cdvd_StartADXTFile_001025c0, &recomp_gen::fn_H_Cdvd_StartADXTFile_001025c0__recomp},
    {"sub_1028D0", 0x1028D0, &recomp_gen::fn_sub_1028D0_001028d0, &recomp_gen::fn_sub_1028D0_001028d0__recomp},
    {"sub_102D90", 0x102D90, &recomp_gen::fn_sub_102D90_00102d90, &recomp_gen::fn_sub_102D90_00102d90__recomp},
    {"sub_102E00", 0x102E00, &recomp_gen::fn_sub_102E00_00102e00, &recomp_gen::fn_sub_102E00_00102e00__recomp},
    {"H_Cdvd_InitRtFsHdd", 0x102E50, &recomp_gen::fn_H_Cdvd_InitRtFsHdd_00102e50, &recomp_gen::fn_H_Cdvd_InitRtFsHdd_00102e50__recomp},
    {"sub_103D00", 0x103D00, &recomp_gen::fn_sub_103D00_00103d00, &recomp_gen::fn_sub_103D00_00103d00__recomp},
    {"sub_103DA0", 0x103DA0, &recomp_gen::fn_sub_103DA0_00103da0, &recomp_gen::fn_sub_103DA0_00103da0__recomp},
};

}  // namespace

TEST_CASE("game(sweep1 file): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep1 cases (real data and documented rules) ---

namespace {

constexpr u32 kCache = 0x7D6F80u;  // sCdvdCache: 256 x 148 bytes (hcdvd.h)
constexpr u32 kFile = kScratch + 0x1000;   // a 272-byte "pak:" file object
constexpr u32 kFs = kScratch + 0x2000;     // a 92-byte file-system record
constexpr u32 kName = kScratch + 0x3000;   // a path
constexpr u32 kDst = kScratch + 0x10000;   // a read buffer
constexpr u32 kResult = kScratch + 0x4000; // the seek's 128-bit result

namespace rtfs = game::sw1::rtfs;

struct CacheEntry {
    u32 slot;
    std::string name;
    u32 data, size;
};
std::vector<CacheEntry> cache_entries(Machine& m) {
    std::vector<CacheEntry> out;
    for (u32 i = 0; i < 256; ++i) {
        const u32 e = kCache + 148 * i;
        if (r32(m, e) == 0) continue;
        std::string rel = gstr(m, e + 8, 128);  // "VOL:\DIR\NAME" as H_Cdvd_BuildPathUppercase builds it
        if (rel.rfind("VOL:\\", 0) != 0) continue;
        rel = rel.substr(5);  // the name a caller passes: "dir/name"
        for (char& ch : rel)
            if (ch == '\\') ch = '/';
        out.push_back({i, rel, r32(m, e + 136), r32(m, e + 140)});
    }
    return out;
}

}  // namespace

// The "pak:" RtFS device over sCdvdCache on the dorm snapshot's cache: open finds a cached file by its name (and only
// for reading), read copies min(n, size - position) of its bytes, seek follows the three whence rules, eof and exists.
TEST_CASE("game(sweep1 file): the pak: device on the dorm snapshot's sCdvdCache") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    const std::vector<CacheEntry> entries = cache_entries(m);
    REQUIRE(!entries.empty());
    int opened = 0;
    for (std::size_t k = 0; k < entries.size() && k < 6; ++k) {
        const CacheEntry& e = entries[k];
        INFO(e.name);
        // open: the slot's 148 bytes copied to +112, position 0, length = size, state words
        SiPair sp = run_case(m, base, kCases, "H_Cdvd_RtFsPak_FOpen", {kFs, kFile, kName, 0}, 1 + static_cast<u32>(k), [&](Machine& mm) {
            std::memset(mm.at(kFile), 0xCD, 272);
            wstr(mm, kName, e.name);
        });
        CHECK(v0_of(sp.hw) == 1);
        CHECK(std::memcmp(m.at(kFile + rtfs::kPakEntry), m.at(kCache + 148 * e.slot), 144) == 0);
        CHECK(r32(m, kFile + rtfs::kPakPos) == 0u);
        CHECK(r32(m, kFile + 0) == e.size);
        CHECK(r32(m, kFile + 56) == 2u);
        CHECK(r32(m, kFile + 60) == 1u);
        ++opened;
        // read 100 bytes from position 0 (or the whole file when shorter)
        const u32 n = 100;
        std::vector<u8> opened_ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        sp = run_case(m, opened_ram, kCases, "H_Cdvd_RtFsPak_FRead", {kFile, kDst, n, 0}, 7);
        const u32 want = std::min(n, e.size);
        CHECK(static_cast<u32>(v0_of(sp.hw)) == want);
        CHECK(std::memcmp(m.at(kDst), m.at(e.data), want) == 0);
        CHECK(r32(m, kFile + rtfs::kPakPos) == want);
        // at the end: read returns 0 and eof is -1
        sp = run_case(m, opened_ram, kCases, "H_Cdvd_RtFsPak_FRead", {kFile, kDst, n, 0}, 8,
                      [&](Machine& mm) { w32(mm, kFile + rtfs::kPakPos, e.size); });
        CHECK(v0_of(sp.hw) == 0);
        sp = run_case(m, opened_ram, kCases, "sub_1018A0", {kFile, 0, 0, 0}, 9,
                      [&](Machine& mm) { w32(mm, kFile + rtfs::kPakPos, e.size); });
        CHECK(v0_of(sp.hw) == -1);
        sp = run_case(m, opened_ram, kCases, "sub_1018A0", {kFile, 0, 0, 0}, 10);
        CHECK(v0_of(sp.hw) == 0);
        // seek: whence 1 clamps at the size, whence 2 adds min(offset, size), whence 3 wraps to size - 1
        for (const u32 whence : {1u, 2u, 3u, 0u}) {
            for (const u32 off : {0u, 5u, e.size / 2, e.size + 9, 0xFFFFFFF0u}) {
                const u32 pos0 = e.size / 3;
                sp = run_case(m, opened_ram, kCases, "sub_1018C0", {kResult, kFile, off, whence}, 11 + whence,
                              [&](Machine& mm) { w32(mm, kFile + rtfs::kPakPos, pos0); });
                u32 want_pos = pos0;
                u64 want_res = 1;
                if (whence == 1) want_pos = std::min<u32>(pos0 + off, e.size);
                if (whence == 2) want_pos = pos0 + std::min<u32>(off, e.size);
                if (whence == 3) want_pos = (e.size < e.size + off) ? e.size - 1 : e.size + off;
                if (whence != 0) want_res = static_cast<u64>(static_cast<s64>(static_cast<s32>(want_pos)));
                CHECK(r32(m, kFile + rtfs::kPakPos) == want_pos);
                u64 res;
                std::memcpy(&res, m.at(kResult), 8);
                CHECK(res == want_res);
            }
        }
        // exists
        sp = run_case(m, base, kCases, "sub_101A10", {kFs, kName, 0, 0}, 20, [&](Machine& mm) { wstr(mm, kName, e.name); });
        CHECK(v0_of(sp.hw) == 1);
    }
    CHECK(opened > 0);
    // the name pointer 1 (a sentinel the open refuses) and an unknown name fail; exists says no
    SiPair sp = run_case(m, base, kCases, "H_Cdvd_RtFsPak_FOpen", {kFs, kFile, 1, 0}, 30,
                         [&](Machine& mm) { wstr(mm, kName, entries[0].name); });
    CHECK(v0_of(sp.hw) == 2);
    sp = run_case(m, base, kCases, "H_Cdvd_RtFsPak_FOpen", {kFs, kFile, kName, 0}, 31,
                  [&](Machine& mm) { wstr(mm, kName, "NO\\SUCH\\FILE.BIN"); });
    CHECK(v0_of(sp.hw) == 2);
    sp = run_case(m, base, kCases, "sub_101A10", {kFs, kName, 0, 0}, 32, [&](Machine& mm) { wstr(mm, kName, "NO\\SUCH\\FILE.BIN"); });
    CHECK(v0_of(sp.hw) == 0);
}

// The device installers on the stand-in heap: the 92-byte record gets the eight / nine callbacks, `count` file
// objects (272 / 144 bytes) with their buffers, and the device is registered (a recorder stands in for RtFS).
TEST_CASE("game(sweep1 file): the RtFS installers fill the file-system record") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);  // RenderWare and its file-system manager are up
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 buffers = 0x01A00000u;
    for (const bool hdd : {false, true}) {
        const char* fn = hdd ? "H_Cdvd_InitRtFsHdd" : "H_Cdvd_InitRtFsPak";
        // sub_4BFD50 (name taken?) -> 0, sub_4BF6E0 (register) -> 1: both stood in with v0 = 0 first
        SiPair sp = run_case(m, base, kCases, fn, {5, buffers, 2048, kName + 16}, 40, [&](Machine& mm) {
            wstr(mm, kName, hdd ? "tsu" : "tst");  // device names no one registered
            wstr(mm, kName + 16, hdd ? "tsu:" : "tst:");
        }, 0, {{8u, kName}});  // $t0: the file-system name
        const u32 fs = static_cast<u32>(v0_of(sp.hw));
        REQUIRE(fs != 0u);
        const u32 objsize = hdd ? 144u : 272u;
        const u32 files = r32(m, fs + rtfs::kFsFiles);
        CHECK(files != 0u);
        CHECK(r32(m, fs + rtfs::kFsOpen) == (hdd ? 0x102900u : 0x1016D0u));
        CHECK(r32(m, fs + rtfs::kFsRead) == (hdd ? 0x102AD0u : 0x101810u));
        CHECK(r32(m, fs + rtfs::kFsGetFile) == (hdd ? 0x102D90u : 0x1019A0u));
        CHECK(r32(m, fs + rtfs::kFsWrite) == (hdd ? 0x102B60u : 0u));
        for (u32 i = 0; i < 5; ++i) {
            CHECK(r32(m, files + objsize * i + rtfs::kFileFs) == fs);
            CHECK(r32(m, files + objsize * i + rtfs::kFileBuffer) == buffers + 2048 * i);
            CHECK(r32(m, files + objsize * i + rtfs::kFileBufferSize) == 2048u);
        }
        // get-file-object: index < count -> the object, else 0 (the record's +4 count set by the registration)
        std::vector<u8> after(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (const u32 idx : {0u, 3u, 5u, 9u}) {
            sp = run_case(m, after, kCases, hdd ? "sub_102D90" : "H_Cdvd_RtFsPak_Get", {fs, idx, 0, 0}, 41,
                          [&](Machine& mm) { w32(mm, fs + rtfs::kFsFileCount, 5); });
            CHECK(static_cast<u32>(v0_of(sp.hw)) == (idx < 5 ? files + objsize * idx : 0u));
        }
    }
}

// h_chkmem.c's malloc / free: the 16-byte header (size, serial, tag), the running total 0x7CDEAC, the zero fill.
TEST_CASE("game(sweep1 file): h_chkmem malloc / free keep the header and the running total") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kTotal = 0x7CDEACu, kSerial = 0x7CDEB8u, kTag = 0x7CDEBCu;
    for (const u32 size : {16u, 100u, 172u, 4096u}) {
        // newlib malloc (0x520728) is served by the stand-in heap; DIntr / EIntr are recorders
        SiPair sp = run_case(m, base, kCases, "sub_103DA0", {size, 0, 0, 0}, 50 + size, [&](Machine& mm) {
            w32(mm, kTotal, 1000);
            w32(mm, kSerial, 41);
            w32(mm, kTag, 0x1234);
        }, 1);
        const u32 blk = static_cast<u32>(v0_of(sp.hw));
        CHECK(r32(m, kTotal) == 1000u + size);
        if (blk != 0u) {
            CHECK(r32(m, blk - 16) == size);
            CHECK(r32(m, blk - 8) == 42u);
            CHECK(r32(m, blk - 4) == 0x1234u);
            CHECK(r32(m, kSerial) == 42u);
        }
    }
    // free: the total drops by the header's size, a flagged block (tag != 0) is zero-filled before cfree
    const u32 blk = kScratch + 0x8000;
    for (const u32 flag : {0u, 1u}) {
        SiPair sp = run_case(m, base, kCases, "sub_103D00", {blk + 16, 0, 0, 0}, 60 + flag, [&](Machine& mm) {
            w32(mm, kTotal, 5000);
            w32(mm, blk, 64);
            w32(mm, blk + 12, flag);
            std::memset(mm.at(blk + 16), 0xAB, 48);
        }, 1);
        CHECK(r32(m, kTotal) == 5000u - 64u);
        CHECK(r8(m, blk + 20) == (flag ? 0u : 0xABu));
    }
    // a null block does nothing
    SiPair sp = run_case(m, base, kCases, "sub_103D00", {0, 0, 0, 0}, 70, [&](Machine& mm) { w32(mm, kTotal, 5000); });
    CHECK(r32(m, kTotal) == 5000u);
}

// --- end of the sweep1 cases ---

#else

TEST_CASE("game(sweep1 file): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
