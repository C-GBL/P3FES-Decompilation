// H_Cdvd volume routing (game/include/p3fes/game/fs3.h), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/11_file_io.md
// §1 step 1, §4): H_Cdvd_BuildVolumePaths, the BTL/VOL split of every request path. Its caller H_Cdvd_Request and
// the matching H_Cdvd_Destroy stay recompiled (heap hooks at 0x960184 / 0x96017C, the REQ CDVD printf ring, ADXF's
// close): see the fs3 section of docs/INTEGRATION_LOG.md.
//
// The guest::enter/charge/backedge lines are the virtual-time model of the recompiled body (ADR-0013). Still
// recompiled and called through guest::call: strlen, strcmp, strcpy. H_Cdvd_NormalizePath is the hand version
// (hcdvd.h), called directly.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): the function here is p3fes_handgen's register-faithful body (the
// hand version differed from the original: frame/spills 1); what this header says about guest::call describes that
// earlier version (every callee goes through hg::jal now). Made readable on 2026-10-22 (slice read_misc): the role,
// named registers, the "VOL:" / "BTL:" pointers, the BTL directory table and the frame buffers by name (asserted
// against fs3.h / hcdvd.h), block roles, and no goto left. Every guest statement, frame, link, cycle charge and check
// point is the generated body's, in its order on every path.
#include "p3fes/game/fs3.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/hcdvd.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_H_Cdvd_NormalizePath_001013f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
inline constexpr s32 kBackslash = 92;
inline constexpr s32 kGpVolPtr2 = -31540;  // $gp offset of the second pointer to "VOL:" (0x7CB1BC)
inline constexpr s32 kGpBtlPtr = -31528;   // $gp offset of the pointer to "BTL:" (0x7CB1C8)
static_assert(kGpVolPtr2 == mview::gp_off(kHCdvdVolPtr2) && kGpBtlPtr == mview::gp_off(kHCdvdBtlPtr));
inline constexpr s32 kBtlDirScan = 200;    // BTL directory names looked at, at most
static_assert(kBtlDirScan == static_cast<s32>(kHCdvdBtlDirScan));
inline constexpr s32 kNormDir = 0x50;      // the normalized directory in the frame (256 bytes)
inline constexpr s32 kNormDirName = 0x54;  // it after "VOL:" -- what the BTL names are compared with
inline constexpr s32 kReversed = 0x150;    // the reversed file name in the frame (256 bytes)
}  // namespace

// 0x00101240 H_Cdvd_BuildVolumePaths -- 424 bytes; frame 0x250: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_BuildVolumePaths(path, vol_file, dir): dir = the path up to and including its last '\\'; vol_file = "VOL:"
// + the file name, or "BTL:" + the name when the normalized directory is one of g_tbl_rofsDirNames_BTL. Returns 0.
// 0x101240, frame 592: saved registers at +0..+80, the normalized directory at +80 (256), the reversed file
// name at +336 (256). Cycles: prologue 20 (strcpy, strlen); backward scan: test 3 (a back-edge check before
// every character), 5 per character, 8 at the '\', else 3; 11 (H_Cdvd_NormalizePath, strcpy "VOL:"); BTL
// table: test 3 (back-edge check per entry), 8 per entry, 5 for its strcmp, 4 for the "BTL:" strcpy, 1 to
// advance; 7 (strlen of the reversed name); forward copy: test 3 (likewise), 10 per character; tail 15.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_BuildVolumePaths(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw,
          hg::sb, hg::sd, hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::subu;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00101240
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x250);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a0;  // path
    s0 = a1;  // vol_file
    s1 = a2;  // dir
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x10126Cu, gen::fn_strcpy_00524270);  // strcpy(dir, path)
    a0 = s1;
    jal(ctx, 0x101278u, gen::fn_strlen_00524388);
    a2 = 1;
    a0 = kBackslash;
    for (;;) {
        // 0x001012d0: the backward scan of dir: for (k = 1; k < len; k++)
        charge(ctx, 3);
        v1 = sltu(a2, v0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00101290
        charge(ctx, 5);
        v1 = subu(v0, a2);
        v1 = addu(s1, v1);
        lb(a1, v1, 0);
        if (a1 == a0) {
            // 0x001012a4: the last '\\': dir ends after it, the reversed name ends here
            charge(ctx, 8);
            v1 = addiu(a2, -1);
            v0 = subu(v0, v1);
            v0 = addu(s1, v0);
            sb(zero, v0, 0);
            v0 = addu(a2, sp);
            sb(zero, v0, kReversed - 1);
            break;
        }
        // 0x001012c4: reversed[k - 1] = dir[len - k]
        charge(ctx, 3);
        v1 = addu(a2, sp);
        sb(a1, v1, kReversed - 1);
        a2 = addiu(a2, 1);
    }
    // 0x001012dc: norm = H_Cdvd_NormalizePath(dir); vol_file = "VOL:"
    charge(ctx, 11);
    a0 = s1;
    a1 = addiu(sp, kNormDir);
    jal(ctx, 0x1012E4u, gen::fn_H_Cdvd_NormalizePath_001013f0);
    a0 = s0;
    lw(a1, gp, kGpVolPtr2);  // "VOL:"
    jal(ctx, 0x1012F4u, gen::fn_strcpy_00524270);
    s1 = 0;
    for (;;) {
        // 0x00101350: the BTL directory names, until 200 or the empty one
        charge(ctx, 3);
        v0 = sltiu(s1, kBtlDirScan);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00101308
            charge(ctx, 8);
            v1 = sll(s1, 2);
            mview::la(v0, kHCdvdBtlDirNames);  // &g_tbl_rofsDirNames_BTL
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            lb(v0, a0, 0);
            if (v0 != 0) {
                // 0x00101328: a match routes the file to "BTL:"
                charge(ctx, 5);
                a1 = addiu(sp, kNormDirName);
                jal(ctx, 0x10132Cu, gen::fn_strcmp_00524128);
                if (v0 == 0) {
                    // 0x0010133c
                    charge(ctx, 4);
                    a0 = s0;
                    lw(a1, gp, kGpBtlPtr);  // "BTL:"
                    jal(ctx, 0x101344u, gen::fn_strcpy_00524270);
                }
                // 0x0010134c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x0010135c: vol_file[strlen(prefix) + n - 1 - j] = reversed[j]
    charge(ctx, 7);
    a0 = addiu(sp, kReversed);
    jal(ctx, 0x101360u, gen::fn_strlen_00524388);
    s2 = v0;
    s3 = 0;
    for (;;) {
        // 0x001013a0
        charge(ctx, 3);
        v0 = sltu(s3, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00101378
        charge(ctx, 10);
        v0 = addu(s3, sp);
        lb(s1, v0, kReversed);
        lw(a0, gp, kGpVolPtr2);  // "VOL:"
        jal(ctx, 0x101384u, gen::fn_strlen_00524388);
        v0 = addu(s2, v0);
        v0 = subu(v0, s3);
        v0 = addu(s0, v0);
        sb(s1, v0, -1);
        s3 = addiu(s3, 1);
    }
    // 0x001013ac: the NUL after the name; 0
    charge(ctx, 15);
    lw(a0, gp, kGpVolPtr2);  // "VOL:"
    jal(ctx, 0x1013B0u, gen::fn_strlen_00524388);
    v1 = addu(s0, s2);
    v0 = addu(v1, v0);
    sb(zero, v0, 0);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x250);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 H_Cdvd_BuildVolumePaths(EEContext& ctx, u32 path_va, u32 vol_file_va, u32 dir_va) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(path_va)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(vol_file_va)));
    ee::core::set_gpr64(ctx, GPR_A2, ee::core::sext32(static_cast<u32>(dir_va)));
    H_Cdvd_BuildVolumePaths(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

}  // namespace p3fes::game

// --- the recompiled program's entry point (signature from recomp/generated/functions.h) ---------------------------
