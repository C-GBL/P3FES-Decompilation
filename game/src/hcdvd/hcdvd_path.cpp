// H_Cdvd path helpers (game/include/p3fes/game/hcdvd.h), hand-decompiled from SLUS_216.21. The
// guest::enter/charge/backedge lines mirror the recompiled bodies' virtual time (ADR-0013); strcpy and
// strlen stay recompiled and charge their own cycles through guest::call.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 3 functions here are p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 2, scratch GPRs 1); what this header says about
// guest::call describes those earlier versions. Made readable on 2026-10-22 (slice read_misc): role comments, named
// registers, the characters and the "VOL:" strings by name, block roles, and no goto left (H_Cdvd_NormalizePath's
// test chain with host `parent` / `skip` flags). Every guest statement, frame, link, cycle charge and check point is
// the generated body's, in its order on every path.
#include "p3fes/game/hcdvd.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

namespace p3fes::recomp_gen {
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
inline constexpr s32 kBackslash = 92, kSlash = 47, kDot = 46;
inline constexpr s32 kLowerA = 97, kAfterZ = 123, kCaseDelta = 32;
inline constexpr s32 kNormalizeMax = 253;  // H_Cdvd_NormalizePath visits at most 253 input characters
inline constexpr s32 kGpVolPrefix = -31560;     // $gp offset of the literal "VOL:\" (0x7CB1A8)
inline constexpr s32 kGpVolPrefixPtr = -31544;  // $gp offset of the pointer to "VOL:" (0x7CB1B8)
static_assert(kGpVolPrefix == mview::gp_off(kHCdvdVolPrefix) && kGpVolPrefixPtr == mview::gp_off(kHCdvdVolPrefixPtr));
static_assert(kNormalizeMax + 2 == static_cast<s32>(kHCdvdPathMax) && 255 == static_cast<s32>(kHCdvdPathMax));
inline constexpr s32 kReversed = 0x50;  // H_Cdvd_SplitPath: the reversed file name in its frame
}  // namespace

// 0x00101010 H_Cdvd_BuildPathUppercase -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_BuildPathUppercase(path, out): out = "VOL:\\" + path with '/' -> '\\' and a-z uppercased, at most 255
// characters of path.
// 0x101010, frame 64 (saved registers only). Cycles: prologue 21 (strcpy of "VOL:\", strlen of it);
// loop test 3, checked as a back-edge before every character including the first; per character 4,
// then 5 for the NUL (written, loop over), 4 for '/', 3 + 3 + 5 for a lowercase letter, 3 (+3 when
// >= 'a') + 2 for any other, 1 to advance; epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_BuildPathUppercase(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::sb,
          hg::sd, hg::slti, hg::sltiu, hg::sq;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00101010
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // path
    s0 = a1;  // out
    s2 = addiu(gp, kGpVolPrefix);  // "VOL:\\"
    a0 = s0;
    a1 = s2;
    jal(ctx, 0x101038u, gen::fn_strcpy_00524270);  // strcpy(out, "VOL:\\")
    a0 = s2;
    jal(ctx, 0x101044u, gen::fn_strlen_00524388);
    t0 = 0;               // i
    a3 = addu(s0, v0);    // the copy goes after the prefix
    a2 = kSlash;
    a1 = kBackslash;
    for (;;) {
        // 0x001010d8: for (i = 0; i < 255; i++)
        charge(ctx, 3);
        v1 = sltiu(t0, kHCdvdPathMax);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00101064: c = path[i]; the end -> the NUL after the copy
        charge(ctx, 4);
        v1 = addu(s1, t0);
        lb(a0, v1, 0);
        if (a0 == 0) {
            // 0x00101074
            charge(ctx, 5);
            v1 = addu(s0, t0);
            v1 = addu(v1, v0);
            sb(zero, v1, 0);
            // 0x001010e4 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
        // 0x00101088
        charge(ctx, 2);
        if (a0 != a2) {
            // 0x001010a0: 'a' <= c <= 'z' -> c - 32
            charge(ctx, 3);
            v1 = slti(a0, kLowerA);
            bool stored = false;
            if (v1 == 0) {
                // 0x001010ac
                charge(ctx, 3);
                at = slti(a0, kAfterZ);
                if (at != 0) {
                    // 0x001010b8
                    charge(ctx, 5);
                    a0 = addiu(a0, -kCaseDelta);
                    v1 = addu(a3, t0);
                    sb(a0, v1, 0);
                    stored = true;
                }
            }
            if (!stored) {
                // 0x001010cc: any other character as it is
                charge(ctx, 2);
                v1 = addu(a3, t0);
                sb(a0, v1, 0);
            }
        } else {
            // 0x00101090: '/' -> '\\'
            charge(ctx, 4);
            v1 = addu(a3, t0);
            sb(a1, v1, 0);
        }
        // 0x001010d4
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x001010e4
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void H_Cdvd_BuildPathUppercase(EEContext& ctx, u32 path_va, u32 out_va) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(path_va)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(out_va)));
    H_Cdvd_BuildPathUppercase(ctx);
}

// 0x00101100 H_Cdvd_SplitPath -- 308 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_SplitPath(path, vol_file, dir): dir = the path up to and including its last '\\', vol_file = "VOL:" + the
// file name after it.
// 0x101100, frame 336: saved registers at +0..+72, the reversed file name at +80 (256 bytes).
// Cycles: prologue 24 (strcpy "VOL:" -> vol_file, strcpy path -> dir, strlen dir); backward scan:
// test 3 (a back-edge check before every character), 5 per character, 8 when it is the '\' (both
// strings get their NUL there), else 3; then 7 (strlen of the reversed name); forward copy: test 3
// (likewise), 10 per character (with a strlen of "VOL:" each time); tail 14 (one more strlen, the NUL).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_SplitPath(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::sb, hg::sd, hg::sltu, hg::sq, hg::subu;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00101100
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // path
    s3 = a1;  // vol_file
    s0 = a2;  // dir
    a0 = s3;
    lw(a1, gp, kGpVolPrefixPtr);  // "VOL:"
    jal(ctx, 0x10112Cu, gen::fn_strcpy_00524270);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x10113Cu, gen::fn_strcpy_00524270);
    a0 = s0;
    jal(ctx, 0x101148u, gen::fn_strlen_00524388);
    a2 = 1;
    a0 = kBackslash;
    for (;;) {
        // 0x001011a0: the backward scan of dir: for (k = 1; k < len; k++)
        charge(ctx, 3);
        v1 = sltu(a2, v0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00101160
        charge(ctx, 5);
        v1 = subu(v0, a2);
        v1 = addu(s0, v1);
        lb(a1, v1, 0);
        if (a1 == a0) {
            // 0x00101174: the last '\\': dir ends after it, the reversed name ends here
            charge(ctx, 8);
            v1 = addiu(a2, -1);
            v0 = subu(v0, v1);
            v0 = addu(s0, v0);
            sb(zero, v0, 0);
            v0 = addu(a2, sp);
            sb(zero, v0, kReversed - 1);
            break;
        }
        // 0x00101194: reversed[k - 1] = dir[len - k]
        charge(ctx, 3);
        v1 = addu(a2, sp);
        sb(a1, v1, kReversed - 1);
        a2 = addiu(a2, 1);
    }
    // 0x001011ac: vol_file[strlen("VOL:") + n - 1 - j] = reversed[j]
    charge(ctx, 7);
    a0 = addiu(sp, kReversed);
    jal(ctx, 0x1011B0u, gen::fn_strlen_00524388);
    s1 = v0;
    s2 = 0;
    for (;;) {
        // 0x001011f0
        charge(ctx, 3);
        v0 = sltu(s2, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001011c8
        charge(ctx, 10);
        v0 = addu(s2, sp);
        lb(s0, v0, kReversed);
        lw(a0, gp, kGpVolPrefixPtr);  // "VOL:"
        jal(ctx, 0x1011D4u, gen::fn_strlen_00524388);
        v0 = addu(s1, v0);
        v0 = subu(v0, s2);
        v0 = addu(s3, v0);
        sb(s0, v0, -1);
        s2 = addiu(s2, 1);
    }
    // 0x001011fc: the NUL after the name
    charge(ctx, 14);
    lw(a0, gp, kGpVolPrefixPtr);  // "VOL:"
    jal(ctx, 0x101200u, gen::fn_strlen_00524388);
    v1 = addu(s3, s1);
    v1 = addu(v1, v0);
    sb(zero, v1, 0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x001013F0 H_Cdvd_NormalizePath -- 296 bytes; leaf frame (no stack)
// H_Cdvd_NormalizePath(src, dst): dst = src with "..\\" / "../" stepping back to the previous separator and ".\\" / "./"
// dropped, at most 253 input characters.
// 0x1013F0, no frame. Cycles: entry 7; loop test 3, checked as a back-edge before every input
// character including the first; per character 4, then 4 for the NUL (written, loop over);
// the "..\" test 2 (+3 +3 as it gets further), the "../" test likewise; a parent step 4, +3 to
// start the backward scan when dst holds 3+ characters, scan test 2 (back-edge check per step),
// 4 per step, +2 when not '\', +1 to step back, 3 when a separator is found, 2 when none is; the
// ".\" test 2 (+3), the "./" test likewise, 3 to skip it; 3 to copy a character; 1 to advance; exit 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_NormalizePath(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lb, hg::sb, hg::slti;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, src{ctx, 4}, dst{ctx, 5}, slash{ctx, 6}, backslash{ctx, 7}, dot{ctx, 8},
        c{ctx, 9}, p{ctx, 10}, out{ctx, 11}, in{ctx, 12};
    // $t1 is also the backward scan's index; $t2 = &src[in]
    // 0x001013f0
    enter(ctx, 7);  // entry check point + this block's cycles
    out = 0;
    in = 0;
    backslash = kBackslash;
    slash = kSlash;
    dot = kDot;
    for (;;) {
        // 0x00101504: while (in < 253)
        charge(ctx, 3);
        v1 = slti(in, kNormalizeMax);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010140c: c = src[in]; the end -> dst[out] = 0
        charge(ctx, 4);
        p = addu(src, in);
        lb(c, p, 0);
        if (c == 0) {
            // 0x0010141c
            charge(ctx, 4);
            v1 = addu(dst, out);
            sb(zero, v1, 0);
            // 0x00101510 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0010142c: "..\" ?
        charge(ctx, 2);
        bool parent = false;  // "..\" or "../": back to the previous separator in dst
        if (c == dot) {
            // 0x00101434
            charge(ctx, 3);
            lb(v1, p, 1);
            if (v1 == dot) {
                // 0x00101440
                charge(ctx, 3);
                lb(v1, p, 2);
                parent = v1 == backslash;
            }
        }
        if (!parent) {
            // 0x0010144c: "../" ?
            charge(ctx, 2);
            if (c == dot) {
                // 0x00101454
                charge(ctx, 3);
                lb(v1, p, 1);
                if (v1 == dot) {
                    // 0x00101460
                    charge(ctx, 3);
                    lb(v1, p, 2);
                    parent = v1 == slash;
                }
            }
        }
        bool skip = false;  // ".\" or "./": dropped
        if (!parent) {
            // 0x001014c0: ".\" ?
            charge(ctx, 2);
            if (c == dot) {
                // 0x001014c8
                charge(ctx, 3);
                lb(v1, p, 1);
                skip = v1 == backslash;
            }
            if (!skip) {
                // 0x001014d4: "./" ?
                charge(ctx, 2);
                if (c == dot) {
                    // 0x001014dc
                    charge(ctx, 3);
                    lb(v1, p, 1);
                    skip = v1 == slash;
                }
            }
        }
        if (parent) {
            // 0x0010146c: in += 2; with 3+ characters in dst, out = after the separator before its last one
            charge(ctx, 4);
            in = addiu(in, 2);
            at = slti(out, 3);
            if (at == 0) {
                // 0x0010147c
                charge(ctx, 3);
                c = addiu(out, -2);
                bool sep = false;
                for (;;) {
                    // 0x001014b0
                    charge(ctx, 2);
                    if (i64(c) < 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00101488: dst[i] a separator?
                    charge(ctx, 4);
                    v1 = addu(dst, c);
                    lb(v1, v1, 0);
                    if (v1 == backslash) {
                        sep = true;
                        break;
                    }
                    // 0x00101498
                    charge(ctx, 2);
                    if (v1 == slash) {
                        sep = true;
                        break;
                    }
                    // 0x001014ac
                    charge(ctx, 1);
                    c = addiu(c, -1);
                }
                if (sep) {
                    // 0x001014a0: out = i + 1
                    charge(ctx, 3);
                    out = addiu(c, 1);
                } else {
                    // 0x001014b8: none: out stays
                    charge(ctx, 2);
                }
            }
        } else if (skip) {
            // 0x001014e8: in += 1 (and the advance below)
            charge(ctx, 3);
            in = addiu(in, 1);
        } else {
            // 0x001014f4: dst[out++] = c
            charge(ctx, 3);
            v1 = addu(dst, out);
            sb(c, v1, 0);
            out = addiu(out, 1);
        }
        // 0x00101500
        charge(ctx, 1);
        in = addiu(in, 1);
    }
    // 0x00101510
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
