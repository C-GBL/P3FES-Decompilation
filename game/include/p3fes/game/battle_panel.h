// The battle status panels (slice battle_panel): pb_main.c (0x684D60), bp_root.c (0x684E38), bp_misc.c (0x684E48) in
// 0x1FC720-0x1FF888 and the unnamed 2D sprite helpers 0x21C9F0-0x21EC38 that every battle-UI drawer calls,
// hand-decompiled from SLUS_216.21 (docs/ANALYSIS/27_unmapped_bands.md section 3; queue_bands.txt slice battle_panel).
//
// The objects these functions read (offsets decimal where the instructions give them so, hex in brackets):
//   the "battle panel" kwlnTask   *(u32*)0x7CE2E4 ($gp - 18956), created by bpRoot_CreateBattlePanelTasks (called by btlStart) with the
//             update bpRoot_UpdateBattlePanelTask [bpRoot_UpdateBattlePanelTask]; "battle panel draw" runs bpRoot_UpdateBattlePanelDrawTask
//             [bpRoot_UpdateBattlePanelDrawTask] (symbols/deltas/bands.sym). Both are live at battle vblank 5800.
//   the panel work  task +60: +0 the panel mode word -- the bits these functions set, clear and test (the meaning in
//             brackets where the callee makes it plain): 0x4 (set by sub_1FDD60 after sub_1FF890, cleared by sub_1FDDA0
//             after sub_1FFC60: the command menu), 0x8 (set by bpRoot_UpdateBattlePanelTask after sub_201B50, cleared by sub_1FDEC0 /
//             sub_1FDDA0), 0x10 (sub_1FE120 / sub_1FE1A0), 0x20 (blocks sub_2016B0 in the draw task), 0x100 (the target
//             list of sub_1FE270 / sub_1FE2E0 / sub_1FE350), 0x200 with +12 (sub_1FE510, dropped by sub_1FE3B0 /
//             sub_1FE430), 0x2000 with +16 (sub_1FE580, dropped by sub_1FE4A0), 0x400 (sub_1FE5F0: until sub_21BAB0 says
//             done), 0x1000 (sub_1FEAB0: until sub_249600), 0x4000 with the id at +0x33310 (sub_1FEBF0) and 0x8000
//             (sub_1FEC50: until sub_24D0C0), 0x10000 (sub_1FE810, cleared by sub_1FE8D0 / sub_1FE920), 0x20000
//             (sub_1FE9B0 / sub_1FEA10), 0x40000 (sub_1FE120 / sub_1FE1A0, blocks sub_243150); +0x119B0 the record the
//             command panel drawers take (sub_210D90 / sub_213E80 / sub_20FE30 / sub_210D60 / sub_215A30 / sub_215A40).
//   gBtl      *(u32*)0x7CE3EC ($gp - 18692): +12 [0xC] flags (0x80 without 0x800 stops both panel tasks), +336 [0x150]
//             four btlUnit lists of 8 bytes (head +0; bp_misc.c's searches use the first or all four), a btlUnit links
//             on through +2612 [0xA34], +156 [0x9C] flags (bit 3 = 0x8 set: counted / found), +164 [0xA4] u16 the unit
//             id, +168 [0xA8] the slot, +2604 [0xA2C] its DatUnit (u16 +2 the id sub_1FF7F0 compares).
//   the 2D sprite helpers take a sprite record { +0 the set (+8 its page table: page records with the sizes at +12 /
//             +16), +4 flags (bits 0 / 1 swap the u / v pair), +8 the page, +12 / +16 w / h, +20 / +24 u / v, +28..+43
//             RGBA bytes } (a set's +4 is its array of 44-byte records, sub_21CCA0) and fill a 4-vertex strip of 64-byte
//             vertices: +0 / +4 x / y (sub_21D890 / sub_21D8E0 / sub_21E170), +8 a float (the word *(float*)0x960088, or
//             sub_21EAC0's $f12), +16 / +20 the uv, +24 1 / (the main camera's +128; kwlnGetMainCamera sub_198590), +32..
//             +44 the RGBA as floats.
//
// Every function is `void name(EEContext&)`: the arguments are read from $a0..$a3 ($f12 for floats) and the result
// is left in $v0 / $f0 by the very instructions of the original. All keep their functions.json names (`sub_*`); a role
// is given in brackets in the .cpp.
//
// Fidelity (wave 7): the register transfers are written with the rt:: operations of the instructions they stand for,
// in the original order, so every GPR (in 128 bits), HI/LO, FPR and $at holds the original value at every check point,
// call and return; the functions with a frame perform the original prologue / epilogue (the spill slots hold what the
// original stored) and call their callees through the generated symbols with $ra = the original link; the jump tables
// (0x7B7230, 0x7B7250, 0x7B7280, 0x7B75F0, 0x7B7610) are read from guest memory and dispatched on the loaded target.
// tests/game/test_battle_panel.cpp compares the whole register file at every check point, at the return or the stop.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace bpanel {
inline constexpr u32 kPanelTaskPtr = 0x7CE2E4u;  // the "battle panel" kwlnTask ($gp - 18956)
inline constexpr u32 kGBtlPtr = 0x7CE3ECu;       // gBtl ($gp - 18692)
inline constexpr s32 kGpPanelTask = -18956;
inline constexpr s32 kGpGBtl = -18692;
inline constexpr u32 kPanelCmdRecord = 0x119B0u;  // panel work + this: the command panel record of the 2D drawers
inline constexpr u32 kPanelTutorialId = 0x33310u; // panel work + this: the pending tutorial id
inline constexpr u32 kDepthWord = 0x960088u;      // the sprite depth float the 2D helpers copy into every vertex
inline constexpr u32 kTblCmdKind = 0x7B7230u;     // sub_1FDF10: 7 targets by the command menu's state
inline constexpr u32 kTblNavLines1 = 0x7B7250u;   // sub_1FEF90: 11 targets (message triples 227..254)
inline constexpr u32 kTblNavLines2 = 0x7B7280u;   // sub_1FF160: 11 targets (message triples 255..281)
inline constexpr u32 kTblUvMode = 0x7B75F0u;      // sub_21CEC0: 8 targets (the u / v anchor by mode)
inline constexpr u32 kTblUvColour = 0x7B7610u;    // sub_21E380: 8 targets (which colour bytes feed which vertex)
}  // namespace bpanel

// All 106 functions: X(name, addr8), addr8 the start address in eight hex digits (fn_<name>_<addr8>).
#define P3FES_BATTLE_PANEL_FUNCS(X) \
    X(sub_1FC720, 001fc720)         \
    X(sub_1FC870, 001fc870)         \
    X(sub_1FCCC0, 001fccc0)         \
    X(sub_1FCE20, 001fce20)         \
    X(sub_1FD350, 001fd350)         \
    X(bpRoot_UpdateBattlePanelTask, 001fd890)         \
    X(bpRoot_UpdateBattlePanelDrawTask, 001fdac0)         \
    X(sub_1FDBE0, 001fdbe0)         \
    X(sub_1FDD20, 001fdd20)         \
    X(sub_1FDD40, 001fdd40)         \
    X(sub_1FDD60, 001fdd60)         \
    X(sub_1FDDA0, 001fdda0)         \
    X(sub_1FDDF0, 001fddf0)         \
    X(sub_1FDEC0, 001fdec0)         \
    X(sub_1FDF10, 001fdf10)         \
    X(sub_1FE120, 001fe120)         \
    X(sub_1FE1A0, 001fe1a0)         \
    X(sub_1FE220, 001fe220)         \
    X(sub_1FE270, 001fe270)         \
    X(sub_1FE2E0, 001fe2e0)         \
    X(sub_1FE350, 001fe350)         \
    X(sub_1FE3B0, 001fe3b0)         \
    X(sub_1FE430, 001fe430)         \
    X(sub_1FE4A0, 001fe4a0)         \
    X(sub_1FE510, 001fe510)         \
    X(sub_1FE580, 001fe580)         \
    X(sub_1FE5F0, 001fe5f0)         \
    X(sub_1FE630, 001fe630)         \
    X(sub_1FE650, 001fe650)         \
    X(sub_1FE7F0, 001fe7f0)         \
    X(sub_1FE810, 001fe810)         \
    X(sub_1FE8D0, 001fe8d0)         \
    X(sub_1FE920, 001fe920)         \
    X(sub_1FE970, 001fe970)         \
    X(sub_1FE990, 001fe990)         \
    X(sub_1FE9B0, 001fe9b0)         \
    X(sub_1FEA10, 001fea10)         \
    X(sub_1FEA70, 001fea70)         \
    X(sub_1FEA90, 001fea90)         \
    X(sub_1FEAB0, 001feab0)         \
    X(sub_1FEB30, 001feb30)         \
    X(sub_1FEB50, 001feb50)         \
    X(sub_1FEB70, 001feb70)         \
    X(sub_1FEBB0, 001febb0)         \
    X(sub_1FEBF0, 001febf0)         \
    X(sub_1FEC30, 001fec30)         \
    X(sub_1FEC50, 001fec50)         \
    X(sub_1FECC0, 001fecc0)         \
    X(sub_1FECE0, 001fece0)         \
    X(sub_1FED00, 001fed00)         \
    X(sub_1FED20, 001fed20)         \
    X(sub_1FED40, 001fed40)         \
    X(sub_1FED60, 001fed60)         \
    X(sub_1FED80, 001fed80)         \
    X(sub_1FEDA0, 001feda0)         \
    X(sub_1FEDC0, 001fedc0)         \
    X(sub_1FEDE0, 001fede0)         \
    X(sub_1FEE00, 001fee00)         \
    X(sub_1FEE20, 001fee20)         \
    X(sub_1FEE40, 001fee40)         \
    X(sub_1FEE60, 001fee60)         \
    X(sub_1FEE80, 001fee80)         \
    X(sub_1FEEA0, 001feea0)         \
    X(sub_1FEEC0, 001feec0)         \
    X(sub_1FEF10, 001fef10)         \
    X(sub_1FEF30, 001fef30)         \
    X(sub_1FEF50, 001fef50)         \
    X(sub_1FEF70, 001fef70)         \
    X(sub_1FEF90, 001fef90)         \
    X(sub_1FF100, 001ff100)         \
    X(sub_1FF120, 001ff120)         \
    X(sub_1FF140, 001ff140)         \
    X(sub_1FF160, 001ff160)         \
    X(sub_1FF2B0, 001ff2b0)         \
    X(sub_1FF2D0, 001ff2d0)         \
    X(sub_1FF2F0, 001ff2f0)         \
    X(sub_1FF310, 001ff310)         \
    X(sub_1FF330, 001ff330)         \
    X(sub_1FF350, 001ff350)         \
    X(sub_1FF370, 001ff370)         \
    X(sub_1FF390, 001ff390)         \
    X(sub_1FF3B0, 001ff3b0)         \
    X(sub_1FF3D0, 001ff3d0)         \
    X(sub_1FF3F0, 001ff3f0)         \
    X(sub_1FF410, 001ff410)         \
    X(sub_1FF430, 001ff430)         \
    X(sub_1FF500, 001ff500)         \
    X(sub_1FF5B0, 001ff5b0)         \
    X(sub_1FF630, 001ff630)         \
    X(sub_1FF740, 001ff740)         \
    X(sub_1FF7F0, 001ff7f0)         \
    X(sub_21CCA0, 0021cca0)         \
    X(sub_21CCE0, 0021cce0)         \
    X(sub_21CD00, 0021cd00)         \
    X(sub_21CEC0, 0021cec0)         \
    X(sub_21D3B0, 0021d3b0)         \
    X(sub_21D890, 0021d890)         \
    X(sub_21D8E0, 0021d8e0)         \
    X(sub_21D950, 0021d950)         \
    X(sub_21DD60, 0021dd60)         \
    X(sub_21E170, 0021e170)         \
    X(sub_21E380, 0021e380)         \
    X(sub_21EA00, 0021ea00)         \
    X(sub_21EAC0, 0021eac0)         \
    X(sub_21EAE0, 0021eae0)         \
    X(sub_21EB80, 0021eb80)

#define P3FES_BATTLE_PANEL_DECL(name, addr8) void name(EEContext& ctx);
P3FES_BATTLE_PANEL_FUNCS(P3FES_BATTLE_PANEL_DECL)
#undef P3FES_BATTLE_PANEL_DECL

}  // namespace p3fes::game
