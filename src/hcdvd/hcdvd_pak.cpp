// H_Cdvd name-first PAK indexing (game/include/p3fes/game/hcdvd.h), hand-decompiled from SLUS_216.21:
// the registration of every entry of a loaded archive in sCdvdCache and the two entry walkers. The
// guest::enter/charge/backedge lines mirror the recompiled bodies' virtual time (ADR-0013); memcpy and
// strcat stay recompiled and charge their own cycles through guest::call. Every original kept its
// entry header copy and name buffers on its stack frame and handed them to those callees, so they stay
// on the guest stack here (guest::StackFrame) at the original offsets.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 4 functions here are p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 4); what this header says about guest::call
// and guest::StackFrame describes those earlier versions (the frames are the bodies' own now). Made readable on
// 2026-10-22 (slice read_misc): role comments, named registers, the file record / PAK entry fields and the frame
// buffers by name (asserted against hcdvd.h), block roles, and no goto left. Every guest statement, frame, link, cycle
// charge and check point is the generated body's, in its order on every path.
#include "p3fes/game/hcdvd.h"

#include "p3fes/game/guest.h"

#include <cstddef>
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_H_Cdvd_AddFileCacheEntry_00102030(p3fes::EEContext&);
void fn_H_Cdvd_BuildPathUppercase_00101010(p3fes::EEContext&);
void fn_H_Cdvd_CacheAdd_00102650(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
// The file record H_Cdvd_Update hands to H_Cdvd_AddFile (hcdvd.h HCdvdFile, node + 8) and the request node.
namespace file {
inline constexpr s32 kPath = 8, kData = 264, kSize = 284, kIsArchive = 328, kEntryCount = 848;
static_assert(kPath == static_cast<s32>(offsetof(HCdvdFile, path)) && kData == static_cast<s32>(offsetof(HCdvdFile, data)));
static_assert(kSize == static_cast<s32>(offsetof(HCdvdFile, size)) && kIsArchive == static_cast<s32>(offsetof(HCdvdFile, is_archive)));
static_assert(kEntryCount == static_cast<s32>(offsetof(HCdvdFile, entry_count)));
}  // namespace file
inline constexpr s32 kNodeData = 272;  // the request node's file data (node + 8 + 264)
static_assert(kNodeData == static_cast<s32>(offsetof(HCdvdRequest, file) + offsetof(HCdvdFile, data)));
// A name-first PAK entry: the 252-byte name, the size word, the data at +256 (64-byte aligned steps).
inline constexpr s32 kPakNameSize = 252, kPakSizeWord = 252, kPakHeader = 256, kPakAlignMask = 63;
static_assert(kPakHeader == static_cast<s32>(sizeof(HCdvdPakEntry)) && kPakSizeWord == static_cast<s32>(offsetof(HCdvdPakEntry, size)));
// The frame buffers of H_Cdvd_AddFile / H_Cdvd_CacheAddArchive (832-byte frames).
inline constexpr s32 kFullName = 0x30;   // dir + entry name, then uppercased with '/' -> '\'
inline constexpr s32 kEntryName = 0x130; // the entry's 252-byte name
inline constexpr s32 kDirPath = 0x230;   // the directory part of the path
inline constexpr s32 kEntrySize = 0x33C; // the entry's size word
inline constexpr s32 kNameMax = 255;     // the uppercase pass visits at most 255 characters
inline constexpr s32 kPathBytes = 256;   // the directory pass looks at 256 bytes of the path
inline constexpr s32 kGetHeader = 0x50;  // H_Cdvd_ArchiveGetFile's header copy
inline constexpr s32 kBufHeader = 0x40;  // H_Cdvd_GetArchiveFileBuffer's header copy
inline constexpr s32 kBackslash = 92, kSlash = 47, kLowerA = 97, kAfterZ = 123, kCaseDelta = 32;
}  // namespace

// 0x00101E30 H_Cdvd_AddFile -- 508 bytes; frame 0x340: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_AddFile(file): registers a loaded file in sCdvdCache: a plain file once (entry_count 1); an archive entry by
// entry, each as dir + name uppercased with '/' -> '\\', until the empty name (entry_count = the entries).
// 0x101E30, frame 832: saved registers at +0..+40, buffers as above. Cycles: prologue 8; a plain
// file 9 (H_Cdvd_AddFileCacheEntry charges its own) + epilogue 6. An archive: 4 to start the
// directory pass; its test 3, checked as a back-edge before every character including the first,
// 4 per character, +4 to copy a non-NUL one; a NUL costs 1 and starts the backward scan, 5 per
// step, +3 and done at a '\' (the NUL goes after it), else 3 and a back-edge check before the
// next step; 1 to advance. Then 2; per entry 14 (two memcpy), 20 more for a non-empty name
// (memcpy, strcat), the uppercase pass, 12 (H_Cdvd_AddFileCacheEntry), the alignment (+2 when
// size + 63 is negative), 5 and a back-edge check; epilogue 6 after the empty name.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_AddFile(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lb, hg::ld,
          hg::lh, hg::lq, hg::lw, hg::sb, hg::sd, hg::sh, hg::sll, hg::slti, hg::sq, hg::sra, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00101e30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x340);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, file::kIsArchive);
    if (v0 != 0) {
        // 0x00101e74: an archive: dir = the path up to and including its last '\\' (into the frame)
        charge(ctx, 4);
        a2 = 0;
        v1 = kBackslash;
        for (;;) {
            // 0x00101ed8
            charge(ctx, 3);
            v0 = slti(a2, kPathBytes);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00101e84
            charge(ctx, 4);
            v0 = addu(s1, a2);
            lb(a0, v0, file::kPath);
            if (a0 == 0) {
                // 0x00101ea4: the end: scan back to the last '\\' and end dir after it
                charge(ctx, 1);
                a1 = addiu(a2, -1);
                for (;;) {
                    // 0x00101ea8
                    charge(ctx, 5);
                    v0 = addu(a1, sp);
                    a0 = addiu(v0, kDirPath);
                    lb(v0, a0, -1);
                    if (v0 == v1) {
                        break;
                    }
                    // 0x00101ec8
                    charge(ctx, 3);
                    a1 = addiu(a1, -1);
                    backedge(ctx);
                }
                // 0x00101ebc
                charge(ctx, 3);
                sb(zero, a0, 0);
            } else {
                // 0x00101e94: copy the character
                charge(ctx, 4);
                v0 = addu(a2, sp);
                sb(a0, v0, kDirPath);
            }
            // 0x00101ed4
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x00101ee4: entry_count = 0; offset = 0
        charge(ctx, 2);
        sh(zero, s1, file::kEntryCount);
        s0 = 0;
        for (;;) {
            // 0x00101eec: full = dir; name = the entry's name; an empty name ends the archive
            charge(ctx, 14);
            a0 = addiu(sp, kFullName);
            a1 = addiu(sp, kDirPath);
            a2 = kPakNameSize;
            jal(ctx, 0x101EF8u, gen::fn_memcpy_00521250);
            lw(v0, s1, file::kData);
            a1 = addu(v0, s0);
            a0 = addiu(sp, kEntryName);
            a2 = kPakNameSize;
            jal(ctx, 0x101F10u, gen::fn_memcpy_00521250);
            lb(v1, sp, kEntryName);
            if (v1 == 0) {
                break;
            }
            // 0x00101f24: entry_count++; size = the entry's size word; offset += 256; full += name
            charge(ctx, 20);
            lh(v0, s1, file::kEntryCount);
            v0 = addiu(v0, 1);
            sh(v0, s1, file::kEntryCount);
            v1 = addiu(s0, kPakSizeWord);
            lw(v0, s1, file::kData);
            a1 = addu(v0, v1);
            a0 = addiu(sp, kEntrySize);
            a2 = 4;
            jal(ctx, 0x101F44u, gen::fn_memcpy_00521250);
            s0 = addiu(s0, kPakHeader);
            a0 = addiu(sp, kFullName);
            a1 = addiu(sp, kEntryName);
            jal(ctx, 0x101F58u, gen::fn_strcat_00523e68);
            a3 = 0;
            v1 = kBackslash;
            a0 = kSlash;
            for (;;) {
                // 0x00101fbc
                charge(ctx, 3);
                v0 = slti(a3, kNameMax);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x00101f74
                    charge(ctx, 6);
                    v0 = addu(a3, sp);
                    a2 = addiu(v0, kFullName);
                    lb(a1, a2, 0);
                    v0 = slti(a1, kLowerA);
                    if (v0 == 0) {
                        // 0x00101f8c
                        charge(ctx, 3);
                        at = slti(a1, kAfterZ);
                        if (at != 0) {
                            // 0x00101f98
                            charge(ctx, 2);
                            v0 = addiu(a1, -kCaseDelta);
                            sb(v0, a2, 0);
                        }
                    }
                    // 0x00101fa0
                    charge(ctx, 3);
                    lb(v0, a2, 0);
                    if (v0 != 0) {
                        // 0x00101fac
                        charge(ctx, 2);
                        if (v0 == a0) {
                            // 0x00101fb4
                            charge(ctx, 1);
                            sb(v1, a2, 0);
                        }
                        // 0x00101fb8
                        charge(ctx, 1);
                        a3 = addiu(a3, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x00101fc8: H_Cdvd_AddFileCacheEntry(file, data + offset, size, full); offset += align64(size)
            charge(ctx, 12);
            lw(v0, s1, file::kData);
            a1 = addu(v0, s0);
            a0 = s1;
            lw(a2, sp, kEntrySize);
            a3 = addiu(sp, kFullName);
            jal(ctx, 0x101FDCu, gen::fn_H_Cdvd_AddFileCacheEntry_00102030);
            lw(v0, sp, kEntrySize);
            v1 = addiu(v0, kPakAlignMask);
            v0 = sra(v1, 6);
            if (i64(v1) < 0) {
                // 0x00101ff8
                charge(ctx, 2);
                v0 = addiu(v1, kPakAlignMask);
                v0 = sra(v0, 6);
            }
            // 0x00102000
            charge(ctx, 5);
            v0 = sll(v0, 6);
            sw(v0, sp, kEntrySize);
            s0 = addu(s0, v0);
            backedge(ctx);
        }
    } else {
        // 0x00101e50: a plain file: H_Cdvd_AddFileCacheEntry(file, data, size, path); entry_count = 1
        charge(ctx, 9);
        lw(a2, s1, file::kSize);
        lw(a1, s1, file::kData);
        a3 = addiu(s1, file::kPath);
        jal(ctx, 0x101E5Cu, gen::fn_H_Cdvd_AddFileCacheEntry_00102030);
        v1 = 1;
        sh(v1, s1, file::kEntryCount);
    }
    // 0x00102014 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x340);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void H_Cdvd_AddFile(EEContext& ctx, u32 file_va) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(file_va)));
    H_Cdvd_AddFile(ctx);
}

// 0x00102720 H_Cdvd_CacheAddArchive -- 332 bytes; frame 0x340: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_CacheAddArchive(path, data): registers every entry of an archive in memory under dir(path) + name (the
// uppercase pass as H_Cdvd_AddFile's), through H_Cdvd_CacheAdd with the archive as the owner.
// 0x102720, frame 832 as H_Cdvd_AddFile's (saved registers at +0..+40). Cycles: prologue 9
// (H_Cdvd_BuildPathUppercase charges its own); per entry 13 (two memcpy), 16 more for a non-empty
// name (memcpy, strcat), the uppercase pass, 11 (H_Cdvd_CacheAdd), the alignment (+2 when size +
// 63 is negative), 5 and a back-edge check; epilogue 6 after the empty name.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_CacheAddArchive(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lb, hg::ld,
          hg::lq, hg::lw, hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sra, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00102720
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x340);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    a1 = addiu(sp, kDirPath);
    jal(ctx, 0x102738u, gen::fn_H_Cdvd_BuildPathUppercase_00101010);
    s0 = 0;
    for (;;) {
        // 0x00102744: full = dir; name = the entry's name; an empty name ends the archive
        charge(ctx, 13);
        a0 = addiu(sp, kFullName);
        a1 = addiu(sp, kDirPath);
        a2 = kPakNameSize;
        jal(ctx, 0x102750u, gen::fn_memcpy_00521250);
        a1 = addu(s1, s0);
        a0 = addiu(sp, kEntryName);
        a2 = kPakNameSize;
        jal(ctx, 0x102764u, gen::fn_memcpy_00521250);
        lb(v1, sp, kEntryName);
        if (v1 == 0) {
            break;
        }
        // 0x00102778: size = the entry's size word; offset += 256; full += name
        charge(ctx, 16);
        v0 = addiu(s0, kPakSizeWord);
        a1 = addu(s1, v0);
        a0 = addiu(sp, kEntrySize);
        a2 = 4;
        jal(ctx, 0x102788u, gen::fn_memcpy_00521250);
        s0 = addiu(s0, kPakHeader);
        a0 = addiu(sp, kFullName);
        a1 = addiu(sp, kEntryName);
        jal(ctx, 0x10279Cu, gen::fn_strcat_00523e68);
        a3 = 0;
        v1 = kBackslash;
        a0 = kSlash;
        for (;;) {
            // 0x00102800
            charge(ctx, 3);
            v0 = slti(a3, kNameMax);
            if (v0 != 0) {
                backedge(ctx);
                // 0x001027b8
                charge(ctx, 6);
                v0 = addu(a3, sp);
                a2 = addiu(v0, kFullName);
                lb(a1, a2, 0);
                v0 = slti(a1, kLowerA);
                if (v0 == 0) {
                    // 0x001027d0
                    charge(ctx, 3);
                    at = slti(a1, kAfterZ);
                    if (at != 0) {
                        // 0x001027dc
                        charge(ctx, 2);
                        v0 = addiu(a1, -kCaseDelta);
                        sb(v0, a2, 0);
                    }
                }
                // 0x001027e4
                charge(ctx, 3);
                lb(v0, a2, 0);
                if (v0 != 0) {
                    // 0x001027f0
                    charge(ctx, 2);
                    if (v0 == a0) {
                        // 0x001027f8
                        charge(ctx, 1);
                        sb(v1, a2, 0);
                    }
                    // 0x001027fc
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                    continue;
                }
            }
            break;
        }
        // 0x0010280c: H_Cdvd_CacheAdd(data, data + offset, size, full); offset += align64(size)
        charge(ctx, 11);
        a1 = addu(s1, s0);
        a0 = s1;
        lw(a2, sp, kEntrySize);
        a3 = addiu(sp, kFullName);
        jal(ctx, 0x10281Cu, gen::fn_H_Cdvd_CacheAdd_00102650);
        lw(v0, sp, kEntrySize);
        v1 = addiu(v0, kPakAlignMask);
        v0 = sra(v1, 6);
        if (i64(v1) < 0) {
            // 0x00102838
            charge(ctx, 2);
            v0 = addiu(v1, kPakAlignMask);
            v0 = sra(v0, 6);
        }
        // 0x00102840
        charge(ctx, 5);
        v0 = sll(v0, 6);
        sw(v0, sp, kEntrySize);
        s0 = addu(s0, v0);
        backedge(ctx);
    }
    // 0x00102854
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x340);
}

// 0x00102100 H_Cdvd_ArchiveGetFile -- 188 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_ArchiveGetFile(node, index, out_size): the data of entry `index` of the node's archive (*out_size = its
// size), stepping over the earlier entries by their aligned sizes.
// 0x102100, frame 336: saved registers at +0..+72, the entry header copy at +80 (256 bytes, its
// size word at +332). Cycles: prologue 12; loop test 3, checked as a back-edge before every entry
// including the first; 11 per entry skipped (memcpy charges its own), +2 when size + 63 is
// negative, 3 to step; 16 for the entry itself (memcpy, the size store, the epilogue).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_ArchiveGetFile(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slt, hg::sq, hg::sra, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00102100
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    lw(s3, a0, kNodeData);  // the entry cursor
    s0 = 0;
    for (;;) {
        // 0x00102170: for (i = 0; i < index; i++)
        charge(ctx, 3);
        v0 = slt(s0, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00102130: copy the header; cursor += 256 + align64(size)
        charge(ctx, 11);
        a0 = addiu(sp, kGetHeader);
        a1 = s3;
        a2 = kPakHeader;
        jal(ctx, 0x10213Cu, gen::fn_memcpy_00521250);
        a0 = addiu(s3, kPakHeader);
        lw(v0, sp, kGetHeader + kPakSizeWord);
        v1 = addiu(v0, kPakAlignMask);
        v0 = sra(v1, 6);
        if (i64(v1) < 0) {
            // 0x0010215c
            charge(ctx, 2);
            v0 = addiu(v1, kPakAlignMask);
            v0 = sra(v0, 6);
        }
        // 0x00102164
        charge(ctx, 3);
        v0 = sll(v0, 6);
        s3 = addu(a0, v0);
        s0 = addiu(s0, 1);
    }
    // 0x0010217c: the entry: *out_size = its size, return its data
    charge(ctx, 16);
    a0 = addiu(sp, kGetHeader);
    a1 = s3;
    a2 = kPakHeader;
    jal(ctx, 0x102188u, gen::fn_memcpy_00521250);
    lw(v0, sp, kGetHeader + kPakSizeWord);
    sw(v0, s1, 0);
    v0 = addiu(s3, kPakHeader);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x001022E0 H_Cdvd_GetArchiveFileBuffer -- 188 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_GetArchiveFileBuffer(node, index): the entry header of entry `index` (0 when the archive ends before it or
// the entry is the terminator).
// 0x1022E0, frame 320: saved registers at +0..+56, the entry header copy at +64 (256 bytes, its
// size word at +316). Cycles: prologue 10; loop test 3, checked as a back-edge before every entry
// including the first; 8 per entry skipped (memcpy charges its own), then 3 and out with 0 at an
// empty name, else 6 (+2 when size + 63 is negative) and 3 to step; after the loop 3 to look at the
// entry's first byte, +1 when it is NUL (result 0), 1; epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_GetArchiveFileBuffer(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lb, hg::ld,
          hg::lq, hg::lw, hg::sd, hg::sll, hg::slt, hg::sq, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001022e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s2, a0, kNodeData);  // the entry cursor
    s0 = 0;
    for (;;) {
        // 0x00102360: for (i = 0; i < index; i++)
        charge(ctx, 3);
        v0 = slt(s0, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00102308: copy the header; the terminator (empty name) -> 0
        charge(ctx, 8);
        a0 = addiu(sp, kBufHeader);
        a1 = s2;
        a2 = kPakHeader;
        jal(ctx, 0x102314u, gen::fn_memcpy_00521250);
        lb(v0, sp, kBufHeader);
        if (v0 == 0) {
            // 0x00102328
            charge(ctx, 3);
            v0 = 0;
            // 0x00102380 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x140);
            return;
        }
        // 0x00102334: cursor += 256 + align64(size)
        charge(ctx, 6);
        a0 = addiu(s2, kPakHeader);
        lw(v0, sp, kBufHeader + kPakSizeWord);
        v1 = addiu(v0, kPakAlignMask);
        v0 = sra(v1, 6);
        if (i64(v1) < 0) {
            // 0x0010234c
            charge(ctx, 2);
            v0 = addiu(v1, kPakAlignMask);
            v0 = sra(v0, 6);
        }
        // 0x00102354
        charge(ctx, 3);
        v0 = sll(v0, 6);
        s2 = addu(a0, v0);
        s0 = addiu(s0, 1);
    }
    // 0x0010236c: the entry, or 0 when it is the terminator
    charge(ctx, 3);
    lb(v0, s2, 0);
    if (v0 == 0) {
        // 0x00102378
        charge(ctx, 1);
        s2 = 0;
    }
    // 0x0010237c
    charge(ctx, 1);
    v0 = s2;
    // 0x00102380 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
namespace p3fes::recomp_gen {

// H_Cdvd_AddFile and H_Cdvd_CacheAddArchive are void; the original leaves $v0 as its last callee did
// (memcpy of the terminating header, or the plain file's registration), which the guest::call chain
// reproduces: nothing to write here.

}  // namespace p3fes::recomp_gen
