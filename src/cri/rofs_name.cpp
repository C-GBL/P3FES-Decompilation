// CRI ROFS name handling (game/include/p3fes/game/fs3.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/11_file_io.md §1): the comparers and the record converter of rofs_dir.c, the volume-name split
// and the volume table of rofs_mai.c. rfmai_divideFname and rfmai_getVolume run on every file open
// (RFMAI_OpenG 0x568388), so the dorm replay exercises them on every load.
//
// The guest::enter/charge/backedge lines are the virtual-time model of the recompiled bodies (ADR-0013; block
// costs from recomp/generated, where `ctx.cycles += N` marks each basic block). strlen, strcmp, strcpy, memcpy,
// memset, strncpy and RFMAI_CopyStructCdDr stay recompiled and are called through guest::call, so they charge
// their own cycles and reach their own check points exactly as before.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 12 functions here are p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: scratch GPRs 5, frame/spills 4, $v0 1, logic 1, faults only
// 1); what this header says about guest::call describes those earlier versions (the bodies call through
// hg::jal). Made readable on 2026-10-22 (slice read_misc): role comments (fs3.h has the contracts), named registers,
// the ROFS work area / volume / ISO directory record / #DirLst# entry fields and the characters by name (the
// anonymous namespace below, asserted against fs3.h / cri_rofs.h), block roles; the loop exits became `break`s and
// in-place returns. rfmai_divideFname and rfmai_getVolume keep their gotos: their loops have two entries. Every guest
// statement, frame, link, cycle charge and check point is the generated body's, in its order on every path.
#include "p3fes/game/fs3.h"

#include "p3fes/ee/hilo.h"
#include "p3fes/game/cri_rofs.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

#include <cstddef>

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_RFMAI_ToUpperStr_00569848(p3fes::EEContext&);
void fn_rfdir_getSearchID_0056bc10(p3fes::EEContext&);
void fn_rfdir_toUpper_0056b980(p3fes::EEContext&);
void fn_sub_568368_00568368(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_RFMAI_CopyStructCdDr_0056a348(p3fes::EEContext&);  // ISO directory record -> its static aligned struct
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
// The characters the name helpers test, as the instructions' immediates.
inline constexpr s32 kDot = 46;        // '.'
inline constexpr s32 kColon = 58;      // ':' between the volume and the file name
inline constexpr s32 kLowerA = 97;     // 'a': `addiu v0, a0, -97; sltiu v0, v0, 26` = 'a' <= c <= 'z'
inline constexpr s32 kLetters = 26;
inline constexpr s32 kCaseDelta = 32;  // 'a' - 'A'
inline constexpr s32 kPartMax = 512;   // rfmai_divideFname: the frame buffer of one path part
// The ROFS work area (*g_rofs_work, fs3.h) and its 52-byte volume slots.
inline constexpr s32 kWorkMaxVolumes = 8, kWorkMaxDirEnts = 12, kWorkVolumes = 40, kWorkDefVolume = 44;
inline constexpr s32 kVolumeName = 22, kVolumeSize = 52;
static_assert(kWorkMaxVolumes == static_cast<s32>(kRofsWorkMaxVolumes) && kWorkMaxDirEnts == static_cast<s32>(kRofsWorkMaxDirEnts));
static_assert(kWorkVolumes == static_cast<s32>(kRofsWorkVolumes) && kWorkDefVolume == static_cast<s32>(kRofsWorkDefVolume));
static_assert(kVolumeName == static_cast<s32>(kRofsVolumeName) && kVolumeSize == static_cast<s32>(kRofsVolumeSize));
inline constexpr s32 kDirBufHeader = 24;  // a directory buffer: the 24-byte #DirLst# header, then 48-byte entries
// The ISO9660 directory record as RFMAI_CopyStructCdDr leaves it (its static aligned struct).
namespace iso_rec {
inline constexpr s32 kLength = 0;       // u8: the record length (< 34: none)
inline constexpr s32 kExtent = 4;       // u32: the extent LBA (little-endian half)
inline constexpr s32 kDataLength = 12;  // u32: the data length
inline constexpr s32 kFlags = 27;       // u8: the file flags (2 = directory)
inline constexpr s32 kNameLength = 34;  // u8: the identifier length (the minimum record length too)
inline constexpr s32 kName = 35;        // the identifier ("\0" / "\1" for . / ..; files end in ";1")
}  // namespace iso_rec
// A 48-byte #DirLst# entry (cri_rofs.h RofsDirLstEnt).
namespace dir_ent {
inline constexpr s32 kSizeLo = 0, kSizeHi = 4, kLba = 8, kFlags = 12, kSearchId = 13, kName = 14, kSize = 48;
static_assert(kFlags == static_cast<s32>(offsetof(RofsDirLstEnt, flags)) && kName == static_cast<s32>(offsetof(RofsDirLstEnt, name)));
static_assert(kSearchId == static_cast<s32>(offsetof(RofsDirLstEnt, search_id)) && kLba == static_cast<s32>(offsetof(RofsDirLstEnt, lba)));
}  // namespace dir_ent
}  // namespace

// --- rofs_dir.c --------------------------------------------------------------------------------------------------

// 0x0056B980 rfdir_toUpper -- 40 bytes; leaf frame (no stack)
// rfdir_toUpper(c): ASCII toupper of one character ('a'..'z' -> 'A'..'Z', the rest unchanged).
// 0x56B980: 7 (sign-extends the byte, tests a-z), +1 for the subtraction, 2 for the return.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_toUpper(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::sll, hg::sltiu, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    Gpr& c = a0;
    // 0x0056b980
    enter(ctx, 7);  // entry check point + this block's cycles
    c = sll(c, 24);
    c = sra(c, 24);
    v0 = addiu(c, -kLowerA);
    v1 = addiu(c, -kCaseDelta);
    v0 = sltiu(v0, kLetters);
    v1 = sll(v1, 24);
    if (v0 != 0) {
        // 0x0056b99c: lowercase: c - 32
        charge(ctx, 1);
        c = sra(v1, 24);
    }
    // 0x0056b9a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x0056B9A8 rfdirStrncmpi -- 160 bytes; frame 0x30: s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// rfdirStrncmpi(a, b, n): 1 when the first n characters are equal ignoring case (or n <= 0); when a ends first,
// whether b ends there too; 0 on a mismatch.
// 0x56B9A8: prologue 10 (tests n); 2 to load *a; per character 3 (a NUL in a ends it: 3 to test b), 8 for
// the two rfdir_toUpper calls, 2 on a mismatch, 2 for the count test; 1 for "equal"; epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdirStrncmpi(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lb, hg::ld, hg::sd,
          hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, upper_a{ctx, 16}, b{ctx, 17}, n{ctx, 18}, a{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // a, b, n: the two names and the count left ($a0, $a1, $a2); upper_a: toupper of a's character
    // 0x0056b9a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(n, sp, 0x10);
    n = a2;
    sd(b, sp, 0x8);
    b = a1;
    sd(a, sp, 0x18);
    a = a0;
    sd(upper_a, sp, 0x0);
    sd(ra, sp, 0x20);
    if (i64(n) > 0) {
        // 0x0056b9d0
        charge(ctx, 2);
        lb(v0, a, 0);
        for (;;) {
            // 0x0056b9d8
            charge(ctx, 3);
            a = addiu(a, 1);
            a0 = v0;
            if (v0 == 0) {
                // 0x0056ba10: a ended: 1 when b ends too
                charge(ctx, 3);
                lb(v0, b, 0);
                v0 = sltiu(v0, 1);
                // 0x0056ba2c (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(upper_a, sp, 0x0);
                ld(b, sp, 0x8);
                ld(n, sp, 0x10);
                ld(a, sp, 0x18);
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                return;
            }
            // 0x0056b9e4: toupper(*a++) == toupper(*b++)?
            charge(ctx, 8);
            jal(ctx, 0x56B9E4u, gen::fn_rfdir_toUpper_0056b980);
            lb(a0, b, 0);
            upper_a = v0;
            b = addiu(b, 1);
            jal(ctx, 0x56B9F4u, gen::fn_rfdir_toUpper_0056b980);
            n = addiu(n, -1);
            if (upper_a != v0) {
                // 0x0056ba04: they differ: 0
                charge(ctx, 2);
                v0 = 0;
                // 0x0056ba2c (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(upper_a, sp, 0x0);
                ld(b, sp, 0x8);
                ld(n, sp, 0x10);
                ld(a, sp, 0x18);
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                return;
            }
            // 0x0056ba20: --n > 0: the next character of a
            charge(ctx, 2);
            if (i64(n) <= 0) {
                break;
            }
            lb(v0, a, 0);
            backedge(ctx);
        }
    }
    // 0x0056ba28: n characters equal: 1
    charge(ctx, 1);
    v0 = 1;
    // 0x0056ba2c
    charge(ctx, 7);
    ld(upper_a, sp, 0x0);
    ld(b, sp, 0x8);
    ld(n, sp, 0x10);
    ld(a, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0056BA48 rfdirStrcmpDirName -- 124 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// rfdirStrcmpDirName(a, b): 1 when the directory names are equal ignoring case (exact length), else 0.
// 0x56BA48: prologue 8, 1 to load *a; loop test 2 (a back-edge check before every character, the first
// included); per character 10 (two rfdir_toUpper calls), 2 on a mismatch; 2 for the final test of *b;
// epilogue 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdirStrcmpDirName(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::lbu, hg::ld, hg::sd, hg::sll,
          hg::sltiu, hg::sra;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, a{ctx, 17}, b{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // a, b: the names ($a0, $a1)
    // 0x0056ba48
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(a, sp, 0x8);
    a = a0;
    sd(b, sp, 0x10);
    b = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    // 0x0056ba98
    charge(ctx, 1);
    lb(v0, a, 0);
    for (;;) {
        // 0x0056ba9c
        charge(ctx, 2);
        lbu(a0, a, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0056ba68: toupper(*a++) == toupper(*b++)?
        charge(ctx, 10);
        a0 = sll(a0, 24);
        a = addiu(a, 1);
        a0 = sra(a0, 24);
        jal(ctx, 0x56BA70u, gen::fn_rfdir_toUpper_0056b980);
        lb(a0, b, 0);
        s0 = v0;
        b = addiu(b, 1);
        jal(ctx, 0x56BA80u, gen::fn_rfdir_toUpper_0056b980);
        if (s0 != v0) {
            // 0x0056ba90: they differ: 0
            charge(ctx, 2);
            v0 = 0;
            // 0x0056baac (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s0, sp, 0x0);
            ld(a, sp, 0x8);
            ld(b, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            return;
        }
        lb(v0, a, 0);
    }
    // 0x0056baa4: a ended: 1 when b ends too
    charge(ctx, 2);
    lb(v0, b, 0);
    v0 = sltiu(v0, 1);
    // 0x0056baac
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(a, sp, 0x8);
    ld(b, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0056BBA0 rfdir_getTokenSize -- 108 bytes; leaf frame (no stack)
// rfdir_getTokenSize(str, delims): the characters of str before the first one that occurs in delims.
// 0x56BBA0, leaf: entry 4; per character 4 (first delimiter), +2 when there is one, per delimiter 4 (compare)
// and 5 (next), a hit 2; 5 to step to the next character; 1 + 2 at the end.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_getTokenSize(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lb, hg::lbu, hg::sll, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Gpr &str = a0, &delims = a1, &d = a2, &c = a3, &count = t0;
    // 0x0056bba0
    enter(ctx, 4);  // entry check point + this block's cycles
    lb(v0, str, 0);
    count = 0;
    lbu(c, str, 0);
    if (v0 != 0) {
        for (;;) {
            // 0x0056bbb0: c among the delimiters?
            charge(ctx, 4);
            d = delims;
            lb(v0, d, 0);
            lbu(v1, d, 0);
            bool hit = false;
            if (v0 != 0) {
                // 0x0056bbc0
                charge(ctx, 2);
                v0 = sll(c, 24);
                c = sra(v0, 24);
                for (;;) {
                    // 0x0056bbc8: a hit returns the count
                    charge(ctx, 4);
                    v1 = sll(v1, 24);
                    v1 = sra(v1, 24);
                    v0 = count;
                    if (c == v1) {
                        hit = true;
                        break;
                    }
                    // 0x0056bbd8: the next delimiter
                    charge(ctx, 5);
                    d = addiu(d, 1);
                    lb(v0, d, 0);
                    lbu(v1, d, 0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                if (hit) {
                    break;
                }
            }
            // 0x0056bbec: the next character, count++
            charge(ctx, 5);
            str = addiu(str, 1);
            count = addiu(count, 1);
            lbu(v0, str, 0);
            c = v0;
            if (v0 == 0) {
                // 0x0056bc00: the end of str: the count
                charge(ctx, 1);
                v0 = count;
                break;
            }
            backedge(ctx);
        }
    } else {
        // 0x0056bc00: an empty str: 0
        charge(ctx, 1);
        v0 = count;
    }
    // 0x0056bc04
    charge(ctx, 2);
}

// 0x0056BCB0 rfdir_getOneDirEnt -- 272 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// rfdir_getOneDirEnt(rec, out): one ISO9660 directory record -> one 48-byte #DirLst# entry (fs3.h): the record
// length, -1 when it is shorter than 34, 0 for a null argument.
// 0x56BCB0: prologue 8 (tests rec), 2 (tests out), 2 for the null return; 7 for RFMAI_CopyStructCdDr and the
// length test; 26 for the copy (memset, strncpy charge their own); directory names 3, then 4 for "\0" or
// 2 (+3 for "\1"); 4 for rfdir_getSearchID; epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_getOneDirEnt(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lb, hg::lbu, hg::ld, hg::lw, hg::sb,
          hg::sd, hg::si, hg::sltiu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056bcb0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    if (a0 != 0) {
        // 0x0056bcd0
        charge(ctx, 2);
        if (s1 != 0) {
        // 0x0056bce0: rec = RFMAI_CopyStructCdDr(rec); its length < 34 -> -1
        charge(ctx, 7);
        jal(ctx, 0x56BCE0u, gen::fn_RFMAI_CopyStructCdDr_0056a348);
        s2 = v0;
        lbu(v1, s2, iso_rec::kLength);
        v1 = sltiu(v1, iso_rec::kNameLength);
        v0 = si(-1);
        if (v1 == 0) {
            // 0x0056bcfc: memset(out, 0, 48); size_lo / size_hi / lba / flags; the name (a file's minus ";1")
            charge(ctx, 26);
            a0 = s1;
            a1 = 0;
            a2 = dir_ent::kSize;
            s3 = addiu(s1, dir_ent::kName);
            jal(ctx, 0x56BD08u, gen::fn_memset_00521408);
            lw(a2, s2, iso_rec::kExtent);
            a0 = s3;
            a1 = addiu(s2, iso_rec::kName);
            sw(a2, s1, dir_ent::kLba);
            lw(v1, s2, iso_rec::kDataLength);
            sw(zero, s1, dir_ent::kSizeHi);
            sw(v1, s1, dir_ent::kSizeLo);
            lbu(v0, s2, iso_rec::kFlags);
            sb(v0, s1, dir_ent::kFlags);
            v0 = v0 & kRofsDirEntFlagDir;
            lbu(s0, s2, iso_rec::kNameLength);
            v1 = addiu(s0, -2);
            if (v0 == 0) s0 = v1;  // a file: drop the ";1"
            a2 = s0;
            s0 = addu(s3, s0);
            jal(ctx, 0x56BD48u, gen::fn_strncpy_00524828);
            sb(zero, s0, 0);
            lbu(v0, s1, dir_ent::kFlags);
            v0 = v0 & kRofsDirEntFlagDir;
            if (v0 != 0) {
                // 0x0056bd64: a directory: the identifiers "\0" / "\1" become "." / ".."
                charge(ctx, 3);
                lb(v1, s3, 0);
                v0 = 1;
                if (v1 != 0) {
                    // 0x0056bd80
                    charge(ctx, 2);
                    cc = v1 != v0;  // the condition, before the delay slot changes it
                    v0 = kDot;
                    if (!cc) {
                        // 0x0056bd88: "\1" -> ".."
                        charge(ctx, 3);
                        sb(v0, s3, 0);
                        sb(v0, s1, dir_ent::kName + 1);
                        sb(zero, s1, dir_ent::kName + 2);
                    }
                } else {
                    // 0x0056bd70: "\0" -> "."
                    charge(ctx, 4);
                    v0 = kDot;
                    sb(v0, s3, 0);
                    sb(zero, s1, dir_ent::kName + 1);
                }
            }
            // 0x0056bd94: search_id = rfdir_getSearchID(name); return the record length
            charge(ctx, 4);
            a0 = s3;
            jal(ctx, 0x56BD94u, gen::fn_rfdir_getSearchID_0056bc10);
            sb(v0, s1, dir_ent::kSearchId);
            lbu(v0, s2, iso_rec::kLength);
        }
        // 0x0056bda4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
        }
    }
    // 0x0056bcd8: a null argument: 0
    charge(ctx, 2);
    v0 = 0;
    // 0x0056bda4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// --- rofs_mai.c --------------------------------------------------------------------------------------------------

// 0x00566F30 rfmai_checkMedia -- 72 bytes; leaf frame (no stack)
// rfmai_checkMedia(pvd): 1 when the five bytes at pvd + 1 are "CD001" (an ISO9660 volume descriptor), else 0.
// 0x566F30, leaf: entry 6; per byte 5 (compare), 4 (count); 1 for "yes"; 2 for the return.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfmai_checkMedia(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::slti;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00566f30
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = mview::hi(kRofsCd001);
    a1 = addiu(a0, 1);
    a3 = addiu(v0, mview::lo(kRofsCd001));  // "CD001"
    a2 = 0;
    lbu(a0, a1, 0);
    for (;;) {
        // 0x00566f48: pvd[1 + i] == "CD001"[i]? (a mismatch: 0)
        charge(ctx, 5);
        a1 = addiu(a1, 1);
        lbu(v1, a3, 0);
        a3 = addiu(a3, 1);
        v0 = 0;
        if (v1 != a0) {
            break;
        }
        // 0x00566f5c
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 5);
        if (v0 == 0) {
            // 0x00566f6c: all five matched: 1
            charge(ctx, 1);
            v0 = 1;
            break;
        }
        lbu(a0, a1, 0);
        backedge(ctx);
    }
    // 0x00566f70
    charge(ctx, 2);
}

// 0x00566F78 rfmai_divideFname -- 528 bytes; frame 0x240: s3 sp+0x218, s2 sp+0x210, s4 sp+0x220, s5 sp+0x228, s6 sp+0x230, s0 sp+0x200, s1 sp+0x208, ra sp+0x238
// rfmai_divideFname(vol, name, name_cap, vol_cap, path): "VOL:NAME" -> the volume (uppercased) and the file name
// (fs3.h); 1 on success, 0 otherwise.
// 0x566F78, frame 576: the 512-byte part buffer at +0, the saved registers at +512. Cycles: prologue 15, 2
// per argument test; 5 for strlen(path), 9 for the memset; the first part: 2 + 2 for its first byte, per
// character 6 (stored), 3 (':' test), 2 (NUL test); 5 for strlen of the part. No ':': 3, 8 (memcpy,
// sub_568368), 4 for the strcpy. ':': 3, 7 (memcpy of the volume); the second part 5 + 2 + 3 for its first
// byte, per character 6 / 3 / 2; 1 + 1 to end it; 7 for strlen, 6 for the memcpy and RFMAI_ToUpperStr. Exits
// 1 (the shared $s0 reload) + 9 (epilogue).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfmai_divideFname(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::i64, hg::jal, hg::lb,
          hg::lbu, hg::ld, hg::link, hg::sb, hg::sd, hg::slt, hg::slti, hg::sltiu, hg::subu;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00566f78
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x240);
    sd(s3, sp, 0x218);
    s3 = a0;
    sd(s2, sp, 0x210);
    s2 = t0;
    sd(s4, sp, 0x220);
    s4 = a3;
    sd(s5, sp, 0x228);
    s5 = a1;
    sd(s6, sp, 0x230);
    s6 = a2;
    sd(s0, sp, 0x200);
    sd(s1, sp, 0x208);
    sd(ra, sp, 0x238);
    if (s3 != 0) {
        // 0x00566fb4
        charge(ctx, 2);
        v0 = 0;
        if (s5 == 0) {
        L_00567160:
            charge(ctx, 1);
            ld(s0, sp, 0x200);
        } else {
            // 0x00566fbc
            charge(ctx, 2);
            ld(s0, sp, 0x200);
            if (s2 != 0) {
                // 0x00566fc4
                charge(ctx, 2);
                if (i64(s6) > 0) {
                    // 0x00566fcc
                    charge(ctx, 2);
                    if (i64(s4) <= 0) {
                        goto L_00566fd4;
                    }
                    // 0x00566fe0
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x566FE0u, gen::fn_strlen_00524388);
                    v1 = sltiu(v0, kPartMax + 1);  // a path of 513+ characters is refused
                    v0 = 0;
                    if (v1 == 0) {
                        goto L_00567160;
                    }
                    // 0x00566ff4
                    charge(ctx, 9);
                    a0 = sp;
                    a1 = 0;
                    a2 = kPartMax;
                    s1 = 0;
                    jal(ctx, 0x567000u, gen::fn_memset_00521408);
                    lb(v1, s2, 0);
                    v0 = kColon;
                    s0 = s2;
                    if (v1 != v0) {
                        // 0x00567018
                        charge(ctx, 2);
                        a1 = kColon;
                        if (v1 != 0) {
                            // 0x00567020
                            charge(ctx, 2);
                            lbu(a0, s0, 0);
                            for (;;) {
                                // 0x00567028
                                charge(ctx, 6);
                                v1 = addu(sp, s1);
                                s1 = addiu(s1, 1);
                                v0 = slti(s1, kPartMax);
                                s0 = addu(s2, s1);
                                sb(a0, v1, 0);
                                if (v0 != 0) {
                                    // 0x00567040
                                    charge(ctx, 3);
                                    lb(v0, s0, 0);
                                    if (v0 != a1) {
                                        // 0x0056704c
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            lbu(a0, s0, 0);
                                            backedge(ctx);
                                            continue;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                    // 0x00567054
                    charge(ctx, 5);
                    a0 = sp;
                    jal(ctx, 0x567054u, gen::fn_strlen_00524388);
                    lb(v1, s0, 0);
                    a2 = addiu(v0, 1);
                    if (v1 != 0) {
                        // 0x005670a8
                        charge(ctx, 3);
                        v1 = slt(s6, a2);
                        v0 = 0;
                        if (v1 == 0) {
                            // 0x005670b4
                            charge(ctx, 7);
                            s1 = addiu(s1, 1);
                            a1 = sp;
                            a0 = s3;
                            jal(ctx, 0x5670BCu, gen::fn_memcpy_00521250);
                            v0 = slti(s1, kPartMax);
                            a1 = s1;
                            if (v0 != 0) {
                                // 0x005670d0
                                charge(ctx, 5);
                                v1 = addu(s2, s1);
                                v0 = kColon;
                                lb(a0, v1, 0);
                                cc = a0 == v0;  // the condition, before the delay slot changes it
                                v0 = subu(a1, s1);
                                if (cc) {
                                L_00567128:
                                    charge(ctx, 1);
                                    a0 = sp;
                                } else {
                                    // 0x005670e4
                                    charge(ctx, 2);
                                    cc = a0 == 0;  // the condition, before the delay slot changes it
                                    a0 = sp;
                                    if (!cc) {
                                        // 0x005670ec
                                        charge(ctx, 3);
                                        a3 = kColon;
                                        a2 = sp;
                                        lbu(v0, v1, 0);
                                        for (;;) {
                                            // 0x005670f8
                                            charge(ctx, 6);
                                            a1 = addiu(a1, 1);
                                            a0 = slti(a1, kPartMax);
                                            v1 = addu(s2, a1);
                                            sb(v0, a2, 0);
                                            a2 = addiu(a2, 1);
                                            if (a0 == 0) {
                                                goto L_00567124;
                                            }
                                            // 0x00567110
                                            charge(ctx, 3);
                                            lb(v0, v1, 0);
                                            if (v0 != a3) {
                                                // 0x0056711c
                                                charge(ctx, 2);
                                                if (v0 == 0) {
                                                    goto L_00567124;
                                                }
                                                lbu(v0, v1, 0);
                                                backedge(ctx);
                                                continue;
                                            }
                                            v0 = subu(a1, s1);
                                            break;
                                        }
                                        goto L_00567128;
                                    }
                                }
                                goto L_0056712c;
                            }
                        L_00567124:
                            charge(ctx, 1);
                            v0 = subu(a1, s1);
                            goto L_00567128;
                        }
                        goto L_00567160;
                    }
                    // 0x00567068
                    charge(ctx, 3);
                    v1 = slt(s4, a2);
                    v0 = 0;
                    if (v1 != 0) {
                        goto L_00567160;
                    }
                    // 0x00567074
                    charge(ctx, 8);
                    a1 = sp;
                    a0 = s5;
                    jal(ctx, 0x567078u, gen::fn_memcpy_00521250);
                    link(ctx, 0x567080u);  // $ra first: the delay slot below depends on it
                    sb(zero, s3, 0);
                    call(ctx, gen::fn_sub_568368_00568368);
                    a1 = v0;
                    if (a1 != 0) {
                        // 0x00567094
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x567094u, gen::fn_strcpy_00524270);
                        v0 = 1;
                        goto L_00567160;
                    }
                    ld(s0, sp, 0x200);
                }
            }
        }
        // 0x00567164 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s1, sp, 0x208);
        ld(s2, sp, 0x210);
        ld(s3, sp, 0x218);
        ld(s4, sp, 0x220);
        ld(s5, sp, 0x228);
        ld(s6, sp, 0x230);
        ld(ra, sp, 0x238);
        sp = addiu(sp, 0x240);
        return;
    }
L_00566fd4:
    charge(ctx, 2);
    v0 = 0;
    goto L_00567160;
L_0056712c:
    charge(ctx, 7);
    v1 = addu(sp, v0);
    link(ctx, 0x567130u);  // $ra first: the delay slot below depends on it
    sb(zero, v1, 0);
    call(ctx, gen::fn_strlen_00524388);
    a2 = addiu(v0, 1);
    v1 = slt(s4, a2);
    v0 = 0;
    if (v1 == 0) {
        // 0x00567148
        charge(ctx, 6);
        a0 = s5;
        a1 = sp;
        jal(ctx, 0x56714Cu, gen::fn_memcpy_00521250);
        a0 = s3;
        jal(ctx, 0x567154u, gen::fn_RFMAI_ToUpperStr_00569848);
        v0 = 1;
    }
    goto L_00567160;
}

// 0x00567188 rfmai_getDirBufAdr -- 100 bytes; leaf frame (no stack)
// rfmai_getDirBufAdr(idx): the directory buffer of volume slot idx (fs3.h), 0 when idx < 0 or > max_volumes.
// 0x567188, leaf: entry 6 (loads the work area's counts, tests idx < 0), 3 (idx > max_volumes), 2 for the
// null return, 13 for the address.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfmai_getDirBufAdr(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::lw, hg::mult, hg::sll, hg::slt;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00567188
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = mview::hi(kRofsWorkPtr);
    a2 = a0;  // idx
    lw(a0, v0, mview::lo(kRofsWorkPtr));  // g_rofs_work
    lw(a1, a0, kWorkMaxVolumes);
    lw(a3, a0, kWorkMaxDirEnts);
    if (i64(a2) < 0) {
        // 0x005671ac (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x005671a0
    charge(ctx, 3);
    v0 = slt(a1, a2);
    if (v0 != 0) {
        // 0x005671ac (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    v0 = sll(a3, 1);
    // 0x005671b8: volumes + 52 * max_volumes + idx * (24 + 48 * max_dir_ents)
    charge(ctx, 13);
    v1 = sll(a1, 1);
    v0 = addu(v0, a3);
    v1 = addu(v1, a1);
    v0 = sll(v0, 4);
    v1 = sll(v1, 2);
    v0 = addiu(v0, kDirBufHeader);
    lw(a0, a0, kWorkVolumes);
    mult(v0, a2, v0);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    a0 = addu(a0, v1);
    v0 = addu(a0, v0);
}

// 0x00568368 sub_568368 -- 28 bytes; leaf frame (no stack)
// sub_568368 [rfmai_getDefVolName]: the default volume's name (its RofsVolume + 22), 0 when none is set.
// 0x568368, leaf, one block of 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_568368_regs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00568368
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = mview::hi(kRofsWorkPtr);
    lw(v1, v0, mview::lo(kRofsWorkPtr));  // g_rofs_work
    lw(v0, v1, kWorkDefVolume);
    a0 = v0 ^ 0x0;
    v0 = addiu(v0, kVolumeName);
    if (a0 == 0) v0 = 0;
}

// 0x005671F0 rfmai_getVolume -- 216 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// rfmai_getVolume(name, use_default): the RofsVolume named `name` (fs3.h); a null name with use_default 1, or
// "ROFS", is the default volume's name; 0 when not found.
// 0x5671F0: prologue 9; a null name 3 (+2 to take the default); 5 for the "ROFS" strcmp; 5 for sub_568368
// (2 when it has none); 5 to load the table, 3 to enter the loop, per slot 6 (strcmp) and 3 (count); a hit
// takes a back-edge check on its way to the 2-cycle result block; exits 1 + 1 / 1, epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfmai_getVolume(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lw, hg::sd, hg::slt;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005671f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (s2 == 0) {
        // 0x00567214
        charge(ctx, 3);
        v0 = 1;
        cc = a1 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            goto L_005672a8;
        }
        // 0x00567220
        charge(ctx, 2);
        goto L_0056723c;
    }
    // 0x00567228
    charge(ctx, 5);
    mview::la(a1, kRofsDevName);  // "ROFS"
    jal(ctx, 0x56722Cu, gen::fn_strcmp_00524128);
    v1 = mview::hi(kRofsWorkPtr);
    if (v0 != 0) {
    L_00567260:  // the volume table walk (entered again from 0x56723c with the default name)
        charge(ctx, 5);
        s4 = 0;
        lw(v0, v1, mview::lo(kRofsWorkPtr));
        lw(s3, v0, kWorkMaxVolumes);
        lw(a1, v0, kWorkVolumes);
        if (i64(s3) > 0) {
            // 0x00567274
            charge(ctx, 3);
            s1 = a1;                      // the slot
            s0 = addiu(a1, kVolumeName);  // its name
            for (;;) {
                // 0x00567280
                charge(ctx, 6);
                a1 = s0;
                s0 = addiu(s0, kVolumeSize);
                a0 = s2;
                jal(ctx, 0x567288u, gen::fn_strcmp_00524128);
                s4 = addiu(s4, 1);
                if (v0 == 0) {
                    backedge(ctx);
                    goto L_00567258;
                }
                // 0x00567298
                charge(ctx, 3);
                v0 = slt(s4, s3);
                s1 = addiu(s1, kVolumeSize);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x005672a4
        charge(ctx, 1);
        v0 = 0;
    L_005672a8:  // the shared $s0 reload
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
    L_0056723c:  // the default volume's name (sub_568368)
        charge(ctx, 5);
        jal(ctx, 0x56723Cu, gen::fn_sub_568368_00568368);
        s2 = v0;
        v1 = mview::hi(kRofsWorkPtr);
        if (s2 != 0) {
            goto L_00567260;
        }
        // 0x00567250
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x005672ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_00567258:  // found: the slot
    charge(ctx, 2);
    v0 = s1;
    goto L_005672a8;
}

// 0x00569BD0 sub_569BD0 -- 20 bytes; leaf frame (no stack)
// sub_569BD0 [RFMAI_CnvU32plusU32toS64]: (hi << 32) | lo as one 64-bit value ($a0 = hi, $a1 = lo).
// 0x569BD0, leaf, one block of 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_569BD0(EEContext& ctx) {
    using hg::Gpr, hg::dsll32, hg::dsrl32, hg::enter;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00569bd0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = dsll32(a1, 0);
    a0 = dsll32(a0, 0);
    v0 = dsrl32(v0, 0);
    v0 = a0 + v0;
}

// 0x00569BE8 sub_569BE8 -- 24 bytes; leaf frame (no stack)
// sub_569BE8 [RFMAI_CnvS64toU32plusU32]: stores the high word of $a0 at $a1 and the low word at $a2; returns the
// high word. 0x569BE8, leaf, one block of 6: the low word is stored first.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_569BE8(EEContext& ctx) {
    using hg::Gpr, hg::dsll32, hg::dsra32, hg::enter, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00569be8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = dsra32(a0, 0);
    a0 = dsll32(a0, 0);
    a0 = dsra32(a0, 0);
    sw(a0, a2, 0);
    sw(v0, a1, 0);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) -------------------------
