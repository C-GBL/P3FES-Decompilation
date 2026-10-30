// CRI ROFS name lookup (game/include/p3fes/game/cri_rofs.h): RFDIR_SearchName and the two searches it
// dispatches to, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/11_file_io.md §1 step 4). The binary
// search runs on every CVM file open, so the dorm replay exercises it on every load.
//
// The guest::enter/charge/backedge lines are the virtual-time model of the recompiled body (ADR-0013;
// block costs from recomp/generated, where `ctx.cycles += N` marks each basic block). strcmp, strcpy,
// strcat and rfdirStrcmpDirName stay recompiled and are called through guest::call, so they charge
// their own cycles and reach their own check points exactly as before.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 3 functions here are p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 3); what this header says about guest::call
// describes those earlier versions. Made readable on 2026-10-22 (slice read_misc): role comments (cri_rofs.h has the
// contracts), named registers, the #DirLst# header / entry fields and the "." / ".." strings by name, block roles,
// and no goto left. Every guest statement, frame, link, cycle charge and check point is the generated body's, in its
// order on every path.
#include "p3fes/game/cri_rofs.h"

#include "p3fes/game/guest.h"

#include <cstddef>
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_RFMAI_ToUpperStr_00569848(p3fes::EEContext&);
void fn_rfdirStrcmpFileName_0056bac8(p3fes::EEContext&);
void fn_rfdir_getSearchID_0056bc10(p3fes::EEContext&);
void fn_rfdir_isContainPeriod_0056c2e0(p3fes::EEContext&);
void fn_rfdir_nameBinarySearch_0056c320(p3fes::EEContext&);
void fn_rfdir_nameSequentialSearch_0056c4b0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_rfdirStrcmpDirName_0056ba48(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
inline constexpr u32 kStrDot = 0x7C7740u;     // "."
inline constexpr u32 kStrDotDot = 0x7C7748u;  // ".."
inline constexpr s32 kDirEntries = 24;        // the #DirLst# header (cri_rofs.h RofsDirLstHdr): the entries follow
inline constexpr s32 kDirCount = 0;           // its entry count, "." and ".." included
namespace dir_ent {                           // a 48-byte RofsDirLstEnt
inline constexpr s32 kFlags = 12, kSearchId = 13, kName = 14, kSize = 48;
}  // namespace dir_ent
static_assert(kDirEntries == static_cast<s32>(sizeof(RofsDirLstHdr)) && dir_ent::kSize == static_cast<s32>(sizeof(RofsDirLstEnt)));
static_assert(dir_ent::kFlags == static_cast<s32>(offsetof(RofsDirLstEnt, flags)) &&
              dir_ent::kSearchId == static_cast<s32>(offsetof(RofsDirLstEnt, search_id)) &&
              dir_ent::kName == static_cast<s32>(offsetof(RofsDirLstEnt, name)));
inline constexpr s32 kPartMax = 512;  // the binary search's two frame buffers
inline constexpr s32 kVolumeLbaOffset = 4;  // RofsVolume: lba_offset (cri_rofs.h)
static_assert(kVolumeLbaOffset == static_cast<s32>(offsetof(RofsVolume, lba_offset)));
}  // namespace

// 0x0056C320 rfdir_nameBinarySearch -- 400 bytes; frame 0x450: s0 sp+0x400, s7 sp+0x438, s1 sp+0x408, s2 sp+0x410, s3 sp+0x418, s4 sp+0x420, s5 sp+0x428, s6 sp+0x430, fp sp+0x440, ra sp+0x448
// rfdir_nameBinarySearch(name, dir): the CVM lookup (cri_rofs.h): "." -> 1, ".." -> 2, else a binary search over
// entries [2, count] with the uppercased query (directories) or its dotted copy (files); the 1-based index or 0.
// 0x56C320, frame 1104: the uppercased query at +0 and its dotted copy at +512 (512 bytes each),
// the nine saved registers at +1024. Cycles: prologue 16; "." test 6 (+2 on a match); ".." test 5
// (+2); setup 17 (strcpy, RFMAI_ToUpperStr, strcpy, rfdir_isContainPeriod charge their own), +2 for
// the strcat; range test 3, +2 entering the loop; per probe 14 (the discarded strcmp), 4 or 2 for
// the deciding strcmp (directory / file), 2 for its equality test, 2 for its sign, +1 when `lo`
// moves, 3 for the loop test; 1 after the loop (L_56C470); 3 for the result; epilogue 12.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_nameBinarySearch(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld,
          hg::lw, hg::sd, hg::sll, hg::sltiu, hg::sltu, hg::srl;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, hi_idx{ctx, 18}, mid{ctx, 19}, dotted{ctx, 20}, lo_idx{ctx, 21}, s6{ctx, 22}, entries{ctx, 23}, sp{ctx, 29}, found{ctx, 30}, ra{ctx, 31};
    // $s0: the name, then the entry; $s1: the count, then the entry name; $s6: "."
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056c320
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x450);
    v0 = 0;
    sd(s0, sp, 0x400);
    s0 = a0;
    sd(entries, sp, 0x438);
    entries = addiu(a1, kDirEntries);
    sd(s1, sp, 0x408);
    sd(hi_idx, sp, 0x410);
    sd(mid, sp, 0x418);
    sd(dotted, sp, 0x420);
    sd(lo_idx, sp, 0x428);
    sd(s6, sp, 0x430);
    sd(found, sp, 0x440);
    sd(ra, sp, 0x448);
    lw(s1, a1, kDirCount);
    if (s0 != 0) {
        // 0x0056c360: strcmp(name, ".")
        charge(ctx, 6);
        v0 = mview::hi(kStrDot);
        s6 = addiu(v0, mview::lo(kStrDot));  // s6 = "." (also the strcat suffix)
        a1 = s6;
        jal(ctx, 0x56C368u, gen::fn_strcmp_00524128);
        if (v0 != 0) {
            a1 = mview::hi(kStrDotDot);
            // 0x0056c380: strcmp(name, "..")
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(a1, mview::lo(kStrDotDot));
            jal(ctx, 0x56C384u, gen::fn_strcmp_00524128);
            a0 = sp;
            if (v0 != 0) {
                // 0x0056c3a0: buf = upper(name); dotted = buf (+ "." when it has none); lo = 2, hi = count
                charge(ctx, 17);
                a1 = s0;
                jal(ctx, 0x56C3A0u, gen::fn_strcpy_00524270);
                hi_idx = s1;
                a0 = sp;
                lo_idx = 2;
                jal(ctx, 0x56C3B0u, gen::fn_RFMAI_ToUpperStr_00569848);
                mid = 0;
                dotted = addiu(sp, kPartMax);
                a1 = sp;
                a0 = dotted;
                found = 0;
                jal(ctx, 0x56C3C8u, gen::fn_strcpy_00524270);
                a0 = dotted;
                jal(ctx, 0x56C3D0u, gen::fn_rfdir_isContainPeriod_0056c2e0);
                v1 = 1;
                a1 = s6;
                if (v0 != v1) {
                    // 0x0056c3e4
                    charge(ctx, 2);
                    a0 = dotted;
                    jal(ctx, 0x56C3E4u, gen::fn_strcat_00523e68);
                }
                // 0x0056c3ec: count < 2: nothing to search
                charge(ctx, 3);
                v0 = sltiu(hi_idx, 2);
                v1 = 1;
                if (v0 == 0) {
                    // 0x0056c3f8
                    charge(ctx, 2);
                    v0 = addu(lo_idx, hi_idx);
                    for (;;) {
                        // 0x0056c400: mid = (lo + hi) / 2; strcmp(entry[mid].name, dotted) (its result unused)
                        charge(ctx, 14);
                        a1 = dotted;
                        mid = srl(v0, 1);
                        s0 = sll(mid, 1);
                        s0 = addu(s0, mid);
                        s0 = sll(s0, 4);
                        s0 = addu(entries, s0);
                        s1 = addiu(s0, dir_ent::kName);
                        a0 = s1;
                        jal(ctx, 0x56C41Cu, gen::fn_strcmp_00524128);
                        a0 = s1;
                        lbu(v0, s0, dir_ent::kFlags);
                        v0 = v0 & kRofsDirEntFlagDir;
                        a1 = sp;
                        if (v0 == 0) {
                            // 0x0056c448: a file: against the dotted query
                            charge(ctx, 2);
                            a1 = dotted;
                            jal(ctx, 0x56C448u, gen::fn_strcmp_00524128);
                        } else {
                            // 0x0056c438: a directory: against the raw uppercase query
                            charge(ctx, 4);
                            jal(ctx, 0x56C438u, gen::fn_strcmp_00524128);
                        }
                        // 0x0056c450: equal: found
                        charge(ctx, 2);
                        if (v0 == 0) {
                            found = 0x1;
                        } else {
                            // 0x0056c458: entry > query: hi = mid - 1
                            charge(ctx, 2);
                            if (i64(v0) >= 0) {
                                hi_idx = addiu(mid, -1);
                            } else {
                                // 0x0056c460: else lo = mid + 1
                                charge(ctx, 1);
                                lo_idx = addiu(mid, 1);
                            }
                            // 0x0056c464: while (lo <= hi)
                            charge(ctx, 3);
                            v0 = sltu(hi_idx, lo_idx);
                            cc = v0 == 0;  // the condition, before the delay slot changes it
                            v0 = addu(lo_idx, hi_idx);
                            if (cc) {
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                    // 0x0056c470
                    charge(ctx, 1);
                    v1 = 1;
                }
                // 0x0056c474: found ? mid + 1 : 0
                charge(ctx, 3);
                v0 = addiu(mid, 1);
                v1 = found ^ v1;
                if (v1 != 0) v0 = 0;
            } else {
                // 0x0056c394
                charge(ctx, 2);
                v0 = 2;
            }
        } else {
            // 0x0056c378
            charge(ctx, 2);
            v0 = 1;
        }
    }
    // 0x0056c480 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x400);
    ld(s1, sp, 0x408);
    ld(hi_idx, sp, 0x410);
    ld(mid, sp, 0x418);
    ld(dotted, sp, 0x420);
    ld(lo_idx, sp, 0x428);
    ld(s6, sp, 0x430);
    ld(entries, sp, 0x438);
    ld(found, sp, 0x440);
    ld(ra, sp, 0x448);
    sp = addiu(sp, 0x450);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 rfdir_nameBinarySearch(EEContext& ctx, u32 name_va, u32 dir_va) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(name_va)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(dir_va)));
    rfdir_nameBinarySearch(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0056C4B0 rfdir_nameSequentialSearch -- 256 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// rfdir_nameSequentialSearch(name, dir): "." -> 1, ".." -> 2; else the first entry whose search_id and name match
// (rfdirStrcmpDirName for directories, rfdirStrcmpFileName for files), 1-based; 0 when none.
// 0x56C4B0, frame 64 (saved registers only). Cycles: prologue 13; 9 for rfdir_getSearchID and the
// "." strcmp (+2 on a match); 5 for the ".." strcmp; 2 for the count test; 1 entering the loop; per
// entry 3 (search_id), +4 for the flags test, +4 for rfdirStrcmpDirName or rfdirStrcmpFileName
// (each charges its own), +2 on a directory hit, +1 after a file miss, 3 for the loop test; 1 after
// the last entry; epilogue 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_nameSequentialSearch(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lw, hg::sd,
          hg::slt;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, entry{ctx, 16}, name{ctx, 17}, index{ctx, 18}, s3{ctx, 19}, count{ctx, 20}, id{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056c4b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0;
    sd(entry, sp, 0x0);
    entry = addiu(a1, kDirEntries);
    sd(name, sp, 0x8);
    name = a0;
    sd(index, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(count, sp, 0x20);
    sd(id, sp, 0x28);
    sd(ra, sp, 0x30);
    lw(count, a1, kDirCount);
    if (name != 0) {
        // 0x0056c4e4: id = rfdir_getSearchID(name); strcmp(name, ".")
        charge(ctx, 9);
        jal(ctx, 0x56C4E4u, gen::fn_rfdir_getSearchID_0056bc10);
        mview::la(a1, kStrDot);
        a0 = name;
        id = v0 & 0xFF;
        jal(ctx, 0x56C4F8u, gen::fn_strcmp_00524128);
        a1 = mview::hi(kStrDotDot);
        if (v0 != 0) {
            // 0x0056c510: strcmp(name, "..")
            charge(ctx, 5);
            a0 = name;
            a1 = addiu(a1, mview::lo(kStrDotDot));
            jal(ctx, 0x56C514u, gen::fn_strcmp_00524128);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 2;
            if (!cc) {
                // 0x0056c524
                charge(ctx, 2);
                index = 0;
                if (i64(count) > 0) {
                    // 0x0056c52c
                    charge(ctx, 1);
                    s3 = 1;
                    bool found = false;  // a file entry matched: $v0 = index + 1
                    for (;;) {
                        // 0x0056c530: the search ids first
                        charge(ctx, 3);
                        lbu(v0, entry, dir_ent::kSearchId);
                        if (v0 != id) {
                            index = addiu(index, 1);
                        } else {
                            // 0x0056c53c: then the name, by kind
                            charge(ctx, 4);
                            lbu(v0, entry, dir_ent::kFlags);
                            v0 = v0 & kRofsDirEntFlagDir;
                            a1 = addiu(entry, dir_ent::kName);
                            if (v0 != 0) {
                                // 0x0056c54c: a directory
                                charge(ctx, 4);
                                a0 = name;
                                jal(ctx, 0x56C54Cu, gen::fn_rfdirStrcmpDirName_0056ba48);
                                if (v0 == s3) {
                                    // 0x0056c55c: found: index + 1
                                    charge(ctx, 2);
                                    v0 = addiu(index, 1);
                                    // 0x0056c58c (the shared epilogue, written out on this path)
                                    charge(ctx, 9);
                                    ld(entry, sp, 0x0);
                                    ld(name, sp, 0x8);
                                    ld(index, sp, 0x10);
                                    ld(s3, sp, 0x18);
                                    ld(count, sp, 0x20);
                                    ld(id, sp, 0x28);
                                    ld(ra, sp, 0x30);
                                    sp = addiu(sp, 0x40);
                                    return;
                                }
                                index = addiu(index, 1);
                            } else {
                                // 0x0056c568: a file
                                charge(ctx, 4);
                                a0 = name;
                                jal(ctx, 0x56C568u, gen::fn_rfdirStrcmpFileName_0056bac8);
                                cc = v0 == s3;  // the condition, before the delay slot changes it
                                v0 = addiu(index, 1);
                                if (cc) {
                                    found = true;
                                    break;
                                }
                                // 0x0056c578
                                charge(ctx, 1);
                                index = addiu(index, 1);
                            }
                        }
                        // 0x0056c57c: the next entry while index < count
                        charge(ctx, 3);
                        v0 = slt(index, count);
                        entry = addiu(entry, dir_ent::kSize);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    if (found) {
                        // 0x0056c58c (the shared epilogue, written out on this path)
                        charge(ctx, 9);
                        ld(entry, sp, 0x0);
                        ld(name, sp, 0x8);
                        ld(index, sp, 0x10);
                        ld(s3, sp, 0x18);
                        ld(count, sp, 0x20);
                        ld(id, sp, 0x28);
                        ld(ra, sp, 0x30);
                        sp = addiu(sp, 0x40);
                        return;
                    }
                }
                // 0x0056c588: not found: 0
                charge(ctx, 1);
                v0 = 0;
            }
        } else {
            // 0x0056c508
            charge(ctx, 2);
            v0 = 1;
        }
    }
    // 0x0056c58c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(entry, sp, 0x0);
    ld(name, sp, 0x8);
    ld(index, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(count, sp, 0x20);
    ld(id, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 rfdir_nameSequentialSearch(EEContext& ctx, u32 name_va, u32 dir_va) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(name_va)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(dir_va)));
    rfdir_nameSequentialSearch(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0056C5B0 RFDIR_SearchName -- 60 bytes; frame 0x10: ra sp+0x0
// RFDIR_SearchName(name, dir, volume): 0 for a null volume; else rfdir_nameBinarySearch for a volume with an LBA
// offset (the CVMs), rfdir_nameSequentialSearch otherwise (tail calls).
// 0x56C5B0: prologue 4 (tests the volume), 3 for the lba_offset test, 2 before either tail call
// (the callee charges its own entry); 3 for the null-volume return.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void RFDIR_SearchName(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c5b0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a2 == 0) {
        // 0x0056c5e0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056c5c0
    charge(ctx, 3);
    lw(v0, a2, kVolumeLbaOffset);
    ld(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056c5d8
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_rfdir_nameBinarySearch_0056c320(ctx);  // tail call
        return;
    }
    // 0x0056c5cc
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_rfdir_nameSequentialSearch_0056c4b0(ctx);  // tail call
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
