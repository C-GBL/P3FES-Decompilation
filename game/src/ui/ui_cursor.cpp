// H_Cursor setters (Atlus h_cursor.c, "H CURSOR Draw" task), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/20_menu_ui.md section 4.2). Each takes the kwln task of the cursor, reaches its work
// record through task+0x3C and stores the new parameter; H_Cursor_UpdateDrawTask rebuilds the four
// vertices from them on the next frame. Phase 5: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_menu_ui.cpp runs each against its __recomp body. Virtual time per
// ADR-0013 (one block each; costs from recomp/generated).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 4 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 2, scratch GPRs 2). Each keeps the notes of its
// earlier hand version above it; what this header says about how the bodies were written describes those earlier
// versions.
#include "p3fes/game/ui.h"

#include "p3fes/game/guest.h"

#include <cstddef>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::game {

// 0x00100710 H_Cursor_SetPos -- 40 bytes; frame 0x10
// 0x100710 H_Cursor_SetPos(task, {x, y}): the pair of floats arrives packed in $a1 (x in the low word).
// The original spills $a1 to its frame and reloads the halves with lwc1; the hand version keeps them in
// host variables (dead-stack difference only).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Cursor_SetPos(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::lw, hg::lwc1, hg::sd, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00100710
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(a1, sp, 0x8);
    lw(v1, a0, 60);
    lwc1(f1, sp, 0x8);
    lwc1(f0, sp, 0xC);
    swc1(f1, v1, 276);
    swc1(f0, v1, 280);
    sp = addiu(sp, 0x10);
}

// 0x00100740 H_Cursor_SetRect -- 44 bytes; leaf frame (no stack)
// 0x100740 H_Cursor_SetRect(task, rect[4]): four words copied as bits (lwc1/swc1).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Cursor_SetRect(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::lwc1, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00100740
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    lwc1(f3, a1, 0);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a1, 12);
    swc1(f3, v1, 284);
    swc1(f2, v1, 288);
    swc1(f1, v1, 292);
    swc1(f0, v1, 296);
}

// 0x00100770 H_Cursor_SetZOffset -- 16 bytes; leaf frame (no stack)
// 0x100770 H_Cursor_SetZOffset(task, float z in $f12).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Cursor_SetZOffset(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x00100770
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    swc1(f12, v1, 300);
}

// 0x00100780 H_Cursor_SetColor -- 104 bytes; frame 0x10
// 0x100780 H_Cursor_SetColor(task, rgba): the four bytes of $a1 (little-endian: r = bits 0..7) go to all
// four vertex colours.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Cursor_SetColor(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::lbu, hg::lw, hg::sb, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29};
    // 0x00100780
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sw(a1, sp, 0xC);
    lw(a3, a0, 60);
    lbu(a2, sp, 0xC);
    lbu(a1, sp, 0xD);
    lbu(a0, sp, 0xE);
    lbu(v1, sp, 0xF);
    sb(a2, a3, 304);
    sb(a1, a3, 305);
    sb(a0, a3, 306);
    sb(v1, a3, 307);
    sb(a2, a3, 308);
    sb(a1, a3, 309);
    sb(a0, a3, 310);
    sb(v1, a3, 311);
    sb(a2, a3, 312);
    sb(a1, a3, 313);
    sb(a0, a3, 314);
    sb(v1, a3, 315);
    sb(a2, a3, 316);
    sb(a1, a3, 317);
    sb(a0, a3, 318);
    sb(v1, a3, 319);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (void: $v0 is left as the caller had it) ------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
}  // namespace p3fes::recomp_gen
