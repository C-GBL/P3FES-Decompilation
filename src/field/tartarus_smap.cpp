// The Tartarus mini-map ("y_smap draw proc", 0x4281F0-0x4312AC) and the time-limit display (0x45A020), hand-decompiled
// from SLUS_216.21 (game/include/p3fes/game/tartarus.h; docs/ANALYSIS/27_unmapped_bands.md section 8). Phase 5 slice
// `tartarus`: these replace the recompiled bodies listed in game/replaced.txt; tests/game/test_tartarus.cpp runs each
// against its __recomp body. The register view, the cycle model and the call convention: game/src/field/tartarus_cpu.h.
//
// The map is drawn from the Tartarus grid (sField +72, 16 x 16 cells of 800 units, 26_field.md 6.2): a cell is
// `(x + 400) / 800` (sub_44F120 / sub_44F170), and a unit's place inside its cell maps to a pixel offset of
// `size / 2 - (pos - (800 cell - 400)) * size / 800` with the map cell `size` in pixels passed in $f12.
#include "p3fes/game/tartarus.h"

#include "tartarus_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_1AD940_001ad940(p3fes::EEContext&);              // (out, controller task): its position (field_big.cpp)
void fn_K_FldFrame_CtlGetXGrid_001ad910(p3fes::EEContext&);  // (controller task) -> its grid cell x (field_lo.cpp)
void fn_K_FldFrame_CtlGetZGrid_001ad920(p3fes::EEContext&);  // (controller task) -> its grid cell z (field_lo.cpp)
void fn_sub_44F120_0044f120(p3fes::EEContext&);              // (pos) -> its grid cell x (tartarus_ene.cpp)
void fn_sub_44F170_0044f170(p3fes::EEContext&);              // (pos) -> its grid cell z (tartarus_ene.cpp)
void fn_K_Field_Get_001b9120(p3fes::EEContext&);             // &sField (field.cpp)
void fn_sub_1BF220_001bf220(p3fes::EEContext&);              // (out, x, z): a door position next to cell (x, z) (k_dungeon)
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);              // RwMatrixCreate
void fn_sub_4C3880_004c3880(p3fes::EEContext&);              // RwMatrixDestroy
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);              // RwMatrixRotate(m, axis, $f12 angle, combine)
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);              // RwV3dTransformPoint(out, in, m)
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);         // (0, sprite file, index) -> a sprite handle
void fn_sprGetSpriteWidth_001126b0(p3fes::EEContext&);       // (handle) -> $f0
void fn_sprGetSpriteHeight_00112740(p3fes::EEContext&);      // (handle) -> $f0
void fn_sub_1127D0_001127d0(p3fes::EEContext&);              // sprDrawSprite(handle, 1) (20_menu_ui.md)
void fn_sub_115980_00115980(p3fes::EEContext&);              // (handle): releases a sprite handle
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);              // RpRandom
void fn_sub_433810_00433810(p3fes::EEContext&);              // (x, z) -> the u8 room index of the cell, 0 = none
void fn_sub_435260_00435260(p3fes::EEContext&);              // (pc) -> s8 (inf: the party member is busy)
void fn_sub_4352E0_004352e0(p3fes::EEContext&);              // () -> (inf: any party member busy)
void fn_sub_4353F0_004353f0(p3fes::EEContext&);              // (unit) -> s8 state of its think work (+364 -> +60)
void fn_sub_43C730_0043c730(p3fes::EEContext&);              // (pc) -> 1 when its think state +4692 is not 1
void fn_sub_456450_00456450(p3fes::EEContext&);              // (pc) (tartarus_sym.cpp)
void fn_sub_456490_00456490(p3fes::EEContext&);              // (pc) (tartarus_sym.cpp)
void fn_sub_423FE0_00423fe0(p3fes::EEContext&);              // (out, ..) a box centred in another (the area-map band)
void fn_Y_LMap_CreateTmxDispTask_00427670(p3fes::EEContext&);              // creates a "y_tmx_disp_proc" task (bands.sym Y_LMap_CreateTmxDispTask)
void fn_sub_427BF0_00427bf0(p3fes::EEContext&);              // creates a "y_tmx_disp(_ex)_proc" task with a size record
void fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0(p3fes::EEContext&);              // creates "smap_symbol_dirp" (heap)
void fn_sub_4563B0_004563b0(p3fes::EEContext&);              // (task, $f12): its angle (tartarus_sym.cpp)
void fn_sub_4563C0_004563c0(p3fes::EEContext&);              // (task, floor) (tartarus_sym.cpp)
void fn_sub_4563D0_004563d0(p3fes::EEContext&);              // (task, xy) (tartarus_sym.cpp)
void fn_sub_42ADB0_0042adb0(p3fes::EEContext&);              // (this file)
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_430780_00430780(p3fes::EEContext&);
void fn_sub_43A230_0043a230(p3fes::EEContext&);
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sub_1C7160_001c7160(p3fes::EEContext&);
void fn_sub_4221A0_004221a0(p3fes::EEContext&);
void fn_Y_LMap_CreateBoxfillTasks_004229d0(p3fes::EEContext&);
void fn_sub_422C10_00422c10(p3fes::EEContext&);
void fn_sub_422C30_00422c30(p3fes::EEContext&);
void fn_sub_422C90_00422c90(p3fes::EEContext&);
void fn_sub_45A490_0045a490(p3fes::EEContext&);
void fn_sub_45ACE0_0045ace0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
// @@CALLEES@@
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace gen = ::p3fes::recomp_gen;
using namespace tartarus;
using namespace tart;

// =====================================================================================================================
// Leaves: the map's flags, the stair icon's setters, the cell offsets
// =====================================================================================================================

struct SMapLeaves : Cpu {
    using Cpu::Cpu;

    // 0x429E80: smap work +2148 = shown (the field root / the event task switch the map on and off).
    void sub_429E80() {
        enter(4);
        v1 = lw(a0, kTaskWork);
        sb(v1, kSmapShown, a1);
    }

    // 0x429E90: +2149 = frozen; the frozen centre +2152.. = the position of the player's controller (gFldUnitsPc[0]
    // +84 -> +480), copied through the frame at sp+32. The draw functions centre the map there while +2149 == 1.
    void sub_429E90() {
        enter(22);
        sp = addiu(sp, -48);
        sd(sp, 16, ra);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        sb(s0, kSmapFrozen, a1);
        v0 = lui(0x87u);
        v0 = lw(v0, 6132);  // 0x8717F4: gFldUnitsPc[0] +84, the scene resource
        a0 = addiu(sp, 32);
        a1 = lw(v0, kResController);
        jal(0x429EB4u, &gen::fn_sub_1AD940_001ad940);
        lwc1(2, sp, 32);
        lwc1(1, sp, 36);
        lwc1(0, sp, 40);
        swc1(2, s0, kSmapFrozenPos + 0);
        swc1(1, s0, kSmapFrozenPos + 4);
        swc1(0, s0, kSmapFrozenPos + 8);
        ra = ld(sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 48);
    }

    // The offset tail shared by the eight cell-offset functions: $f20 = size (from $f12), $v0 = the cell, the
    // coordinate at sp+coord. f0 = size / 2 - (coord - (800 cell - 400)) * (size / 800) through ACC (adda / msub),
    // truncated to an integer (cvt.w / cvt.s) when `trunc`.
    void offset_tail(s32 coord, bool trunc) {
        mtc1(v0, 0);
        cvt_s_w(0, 0);
        v0 = lui(0x4448u);
        mtc1(v0, 2);  // 800.0
        mul_s(1, 2, 0);
        v0 = lui(0x43C8u);
        mtc1(v0, 0);  // 400.0
        sub_s(1, 1, 0);  // f1 = 800 cell - 400: the cell's low edge
        lwc1(0, sp, coord);
        sub_s(3, 0, 1);  // f3 = the coordinate inside the cell
        div_s(2, 20, 2);  // f2 = size / 800
        v0 = lui(0x4000u);
        mtc1(v0, 0);  // 2.0
        div_s(1, 20, 0);  // f1 = size / 2
        mtc1(zero, 0);
        adda_s(0, 1);
        msub_s(0, 3, 2);
        if (trunc) {
            cvt_w_s(0, 0);
            cvt_s_w(0, 0);
        }
    }

    // 0x429EF0 / 0x429FE0 / 0x42A230 / 0x42A310: the offset of field unit (s8) $a0 of `table` (gFldUnitsPc or
    // gFldUnitsEc, +84 = the scene resource) inside its cell, on x (sp+64, `grid` = K_FldFrame_CtlGetXGrid) or z (sp+72,
    // CtlGetZGrid); the controller's position is copied sp+48 -> sp+64. The PC versions truncate (58 cycles), the EC
    // versions do not (56).
    void unit_offset(u32 start, s32 table_lo, rt::Fn grid, s32 coord, bool trunc) {
        enter(trunc ? 58 : 56);
        sp = addiu(sp, -80);
        sd(sp, 32, ra);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        mov_s(20, 12);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);  // 448 i
        v0 = lui(0x87u);
        v0 = addiu(v0, table_lo);  // the units' +84
        s0 = addu(v0, v1);
        v0 = lw(s0, 0);
        a0 = addiu(sp, 48);
        a1 = lw(v0, kResController);
        jal(start + 0x40u, &gen::fn_sub_1AD940_001ad940);
        lwc1(2, sp, 48);
        lwc1(1, sp, 52);
        lwc1(0, sp, 56);
        swc1(2, sp, 64);
        swc1(1, sp, 68);
        swc1(0, sp, 72);
        v0 = lw(s0, 0);
        a0 = lw(v0, kResController);
        jal(start + 0x68u, grid);
        offset_tail(coord, trunc);
        ra = ld(sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 80);
    }
    void sub_429EF0() { unit_offset(0x429EF0u, 6132, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910, 64, true); }    // 0x8717F4
    void sub_429FE0() { unit_offset(0x429FE0u, 6132, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920, 72, true); }
    void sub_42A230() { unit_offset(0x42A230u, -4620, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910, 64, false); }  // 0x86EDF4
    void sub_42A310() { unit_offset(0x42A310u, -4620, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920, 72, false); }

    // 0x42A0D0 / 0x42A180 / 0x42A3F0 / 0x42A4A0: the same for the position at $a0 (copied to sp+32; its cell from
    // sub_44F120 / sub_44F170 on the copy), x (sp+32) or z (sp+40); 0x42A0D0 / 0x42A180 truncate (43 cycles), the other
    // two do not (41).
    void pos_offset(u32 start, rt::Fn cell, s32 coord, bool trunc) {
        enter(trunc ? 43 : 41);
        sp = addiu(sp, -48);
        sd(sp, 16, ra);
        swc1(20, sp, 0);
        mov_s(20, 12);
        v0 = addiu(sp, 32);
        lwc1(2, a0, 0);
        lwc1(1, a0, 4);
        lwc1(0, a0, 8);
        swc1(2, sp, 32);
        swc1(1, sp, 36);
        swc1(0, sp, 40);
        a0 = v0;
        jal(start + 0x30u, cell);
        offset_tail(coord, trunc);
        ra = ld(sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 48);
    }
    void sub_42A0D0() { pos_offset(0x42A0D0u, &gen::fn_sub_44F120_0044f120, 32, true); }
    void sub_42A180() { pos_offset(0x42A180u, &gen::fn_sub_44F170_0044f170, 40, true); }
    void sub_42A3F0() { pos_offset(0x42A3F0u, &gen::fn_sub_44F120_0044f120, 32, false); }
    void sub_42A4A0() { pos_offset(0x42A4A0u, &gen::fn_sub_44F170_0044f170, 40, false); }

    // 0x42BA30: 1 when the s8 at gp-0x4614 is 1 (`(v ^ 1) < 1`).
    void sub_42BA30() {
        enter(5);
        v0 = lb(gp, kGpSmapLock);
        v0 = v0 ^ 0x1u;
        v0 = sltiu(v0, 1);
    }

    // 0x430220: the stair icon at (x, y): $a1 holds two f32 (passed by value), spilled to sp+8 and converted to s16
    // work +0 / +2 through $f0 / $v1; shown = 1.
    void sub_430220() {
        enter(18);
        sp = addiu(sp, -16);
        sd(sp, 8, a1);
        a0 = lw(a0, kTaskWork);
        lwc1(0, sp, 8);
        cvt_w_s(0, 0);
        mfc1(v1, 0);
        sh(a0, kStairX, v1);
        lwc1(0, sp, 12);
        cvt_w_s(0, 0);
        mfc1(v1, 0);
        sh(a0, kStairY, v1);
        v1 = si(1);
        sb(a0, kStairShown, v1);
        sp = addiu(sp, 16);
    }

    // 0x430270: out[0..3] = the four words at work +8..+20 (through $f3..$f0).
    void sub_430270() {
        enter(11);
        v1 = lw(a1, kTaskWork);
        lwc1(3, v1, kStairRect + 0);
        lwc1(2, v1, kStairRect + 4);
        lwc1(1, v1, kStairRect + 8);
        lwc1(0, v1, kStairRect + 12);
        swc1(3, a0, 0);
        swc1(2, a0, 4);
        swc1(1, a0, 8);
        swc1(0, a0, 12);
    }

    // 0x4302A0: shown = 0.
    void sub_4302A0() {
        enter(4);
        v1 = lw(a0, kTaskWork);
        sb(v1, kStairShown, zero);
    }

    // `(float)(unsigned) r` into $f0 as the compiled code converts (halve with the low bit kept, convert, double),
    // `tmp` the register the halves go through.
    void u32_to_float(const Gpr& r, Gpr& tmp) {
        if (gez(r)) {
            charge(5);
            mtc1(r, 0);
            cvt_s_w(0, 0);
        } else {
            charge(7);
            tmp = srl(r, 1);
            v1 = r & 0x1u;
            tmp = tmp | v1;
            mtc1(tmp, 0);
            cvt_s_w(0, 0);
            add_s(0, 0, 0);
        }
    }

    // 0x4311F0: out = {800 x, 0, 800 z} for the cell (x, z) (unsigned), built in the frame at sp+0 and copied out.
    void sub_4311F0() {
        enter(6);
        sp = addiu(sp, -16);
        sw(sp, 4, zero);
        v1 = lui(0x4448u);
        mtc1(v1, 1);  // 800.0
        u32_to_float(a1, a3);
        charge(6);
        mul_s(0, 1, 0);
        swc1(0, sp, 0);
        v1 = lui(0x4448u);
        mtc1(v1, 1);
        u32_to_float(a2, a1);
        charge(11);
        mul_s(0, 1, 0);
        swc1(0, sp, 8);
        lwc1(2, sp, 0);
        lwc1(1, sp, 4);
        lwc1(0, sp, 8);
        swc1(2, a0, 0);
        swc1(1, a0, 4);
        swc1(0, a0, 8);
        sp = addiu(sp, 16);
    }
};

// =====================================================================================================================
// The map's drawing helpers (called from the "y_smap draw proc" update Y_SMap_UpdateSmapDrawTask)
// =====================================================================================================================

struct SMapDraw : SMapLeaves {
    using SMapLeaves::SMapLeaves;

    // The map centre into sp+ctr: the player's controller position (gFldUnitsPc[0] +84 -> +480, copied through
    // sp+tmp); the callers then replace it with the frozen centre while +2149 == 1.
    void centre(s32 tmp, s32 ctr, u32 pc) {
        v0 = lui(0x87u);
        v0 = lw(v0, 6132);  // 0x8717F4: gFldUnitsPc[0] +84
        a0 = addiu(sp, tmp);
        a1 = lw(v0, kResController);
        jal(pc, &gen::fn_sub_1AD940_001ad940);
        lwc1(2, sp, tmp);
        lwc1(1, sp, tmp + 4);
        lwc1(0, sp, tmp + 8);
        swc1(2, sp, ctr);
        swc1(1, sp, ctr + 4);
        swc1(0, sp, ctr + 8);
    }
    // A fresh RW matrix ($v0 from sub_4C38C0, RwMatrixCreate) set to the identity with the flags | 0x20003 (through
    // $v1 / $a0).
    void identity(const Gpr& m) {
        v1 = lui(0x3F80u);  // 1.0
        sw(m, 40, v1);
        sw(m, 20, v1);
        sw(m, 0, v1);
        sw(m, 16, zero);
        sw(m, 8, zero);
        sw(m, 4, zero);
        sw(m, 36, zero);
        sw(m, 32, zero);
        sw(m, 24, zero);
        sw(m, 56, zero);
        sw(m, 52, zero);
        sw(m, 48, zero);
        a0 = lw(m, 12);
        v1 = lui(0x2u);
        v1 = v1 | 0x3u;
        v1 = a0 | v1;
        sw(m, 12, v1);
    }
    // $dst = the floor layout record of the current floor: *(gp-0x4A40) + 964 * major (*(gp-0x57B0) +0) + 40 * the s16
    // at work +2960, read below at -29864 .. -29844 (records of majors 31..: map offsets x / z at -29864 / -29860, the
    // map's rotation angle at -29856, the floor origin at -29852 / -29844; inf). Computed in the two orders the
    // compiled code uses.
    void layout_major_first(const Gpr& work) {
        a0 = lw(gp, -19008);
        v0 = lw(gp, -22448);
        v1 = lw(v0, 0);
        v0 = sll(v1, 4);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);  // 964 major
        a0 = addu(v0, a0);
        v1 = lh(work, 2960);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);  // 40 i
        v0 = addu(v0, a0);
    }

    // 0x42ADB0: places the map's tmx layers (the +2858 s8 count of y_tmx_disp_proc tasks at work +92 + 8 i, each with
    // an f32 pair at +2860 + 8 i): the floor origin (+2980..) minus the centre, turned by the map's angle (RW matrix
    // rotate about the axis 0x6B44C0, then transform), gives the map offset 63 - (2.25 (origin - turned - layout
    // origin)) / 100 - layout offset on x and z; each layer's work +308 / +312 = its pair + that offset (through
    // sp+136).
    void sub_42ADB0() {
        enter(27);
        sp = addiu(sp, -144);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        centre(56, 120, 0x42ADD4u);
        v0 = lui(0x6Bu);
        v1 = ld(v0, 17600);  // 0x6B44C0: the axis
        v0 = lui(0x6Bu);
        lwc1(0, v0, 17608);
        sd(sp, 104, v1);
        swc1(0, sp, 112);
        v1 = lb(s0, kSmapFrozen);
        v0 = si(1);
        if (v1 == v0) {
            charge(6);
            lwc1(2, s0, kSmapFrozenPos + 0);
            lwc1(1, s0, kSmapFrozenPos + 4);
            lwc1(0, s0, kSmapFrozenPos + 8);
            swc1(2, sp, 120);
            swc1(1, sp, 124);
            swc1(0, sp, 128);
        }
        charge(104);
        jal(0x42AE34u, &gen::fn_sub_4C38C0_004c38c0);
        s1 = v0;
        identity(v0);
        layout_major_first(s0);
        a0 = s1;
        a1 = addiu(sp, 104);
        lwc1(12, v0, -29856);  // the angle
        a2 = si(2);
        jal(0x42AED0u, &gen::fn_sub_4C31B0_004c31b0);
        // sp+88 = origin - centre, turned into sp+72
        lwc1(1, s0, 2980);
        lwc1(0, sp, 120);
        sub_s(0, 1, 0);
        swc1(0, sp, 88);
        lwc1(1, s0, 2984);
        lwc1(0, sp, 124);
        sub_s(0, 1, 0);
        swc1(0, sp, 92);
        lwc1(1, s0, 2988);
        lwc1(0, sp, 128);
        sub_s(0, 1, 0);
        swc1(0, sp, 96);
        a0 = addiu(sp, 72);
        a1 = addiu(sp, 88);
        a2 = s1;
        jal(0x42AF14u, &gen::fn_sub_4C6BE0_004c6be0);
        // the layout record again, the other order
        v1 = lh(s0, 2960);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        a0 = sll(v0, 3);
        v0 = lw(gp, -22448);
        v1 = lw(v0, 0);
        v0 = sll(v1, 4);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = lw(gp, -19008);
        lwc1(1, s0, 2980);
        lwc1(0, sp, 72);
        sub_s(1, 1, 0);
        v0 = addu(v1, v0);
        v1 = addu(a0, v0);
        // f5 = 63 - 2.25 (x - turned x - layout x) / 100 - offset x; f2 the same on z
        lwc1(0, v1, -29852);
        sub_s(0, 1, 0);
        v0 = lui(0x4010u);
        mtc1(v0, 4);  // 2.25
        mul_s(0, 4, 0);
        v0 = lui(0x42C8u);
        mtc1(v0, 3);  // 100.0
        div_s(0, 0, 3);
        v0 = lui(0x427Cu);
        mtc1(v0, 2);  // 63.0
        sub_s(1, 2, 0);
        lwc1(0, v1, -29864);
        sub_s(5, 1, 0);
        lwc1(1, s0, 2988);
        lwc1(0, sp, 80);
        sub_s(1, 1, 0);
        lwc1(0, v1, -29844);
        sub_s(0, 1, 0);
        mul_s(0, 4, 0);
        div_s(0, 0, 3);
        sub_s(1, 2, 0);
        lwc1(0, v1, -29860);
        sub_s(2, 1, 0);
        v1 = 0;
        for (;;) {
            charge(4);
            v0 = lb(s0, 2858);
            v0 = slt(v1, v0);
            if (v0 == 0) break;
            backedge();
            charge(15);
            v0 = sll(v1, 3);
            v0 = addu(s0, v0);
            lwc1(0, v0, 2860);
            add_s(0, 0, 5);
            swc1(0, sp, 136);
            lwc1(0, v0, 2864);
            add_s(0, 0, 2);
            swc1(0, sp, 140);
            v0 = lw(v0, 92);
            v0 = lw(v0, kTaskWork);
            lwc1(1, sp, 136);
            lwc1(0, sp, 140);
            swc1(1, v0, 308);
            swc1(0, v0, 312);
            v1 = addiu(v1, 1);
        }
        charge(9);
        a0 = s1;
        jal(0x42B024u, &gen::fn_sub_4C3880_004c3880);  // RwMatrixDestroy
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 144);
    }

    // 0x42B050 (the party members gFldUnitsPc[1..3], sprite 7, axis 0x6B44D0) and 0x42B540 (the shadows
    // gFldUnitsEc[0..23], sprite 11, axis 0x6B44E0): one mark per used unit (+72 and +84 set): its position relative to
    // the centre, scaled by 2.25 / 100 and turned by the map's angle, is drawn as sprite `sprite` of the mini-map's
    // sprite file at work +2140 / +2144 (the map's screen corner) + the map offset - half the sprite size; the mark is
    // shown (+24 alpha 0, else 255) only when it lies inside [corner + 8, corner + 126 - 12) on both axes. One RW matrix
    // per mark (created, set to the identity, destroyed). The bodies are the same code: jal links at fixed offsets from
    // `start`.
    void unit_marks(u32 start, s32 axis_lo, s32 first, s32 end, s32 table_lo, s32 sprite) {
        enter(33);
        sp = addiu(sp, -176);
        sd(sp, 80, ra);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(23, sp, 12);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s1 = lw(a0, kTaskWork);
        centre(96, 160, start + 0x3Cu);
        v1 = lui(0x6Bu);
        a0 = ld(v1, axis_lo);  // the axis
        v1 = lui(0x6Bu);
        lwc1(0, v1, axis_lo + 8);
        sd(sp, 128, a0);
        swc1(0, sp, 136);
        a0 = lb(s1, kSmapFrozen);
        v1 = si(1);
        if (a0 == v1) {
            charge(6);
            lwc1(2, s1, kSmapFrozenPos + 0);
            lwc1(1, s1, kSmapFrozenPos + 4);
            lwc1(0, s1, kSmapFrozenPos + 8);
            swc1(2, sp, 160);
            swc1(1, sp, 164);
            swc1(0, sp, 168);
        }
        charge(4);
        s3 = si(first);
        lwc1(21, sp, 168);  // the centre's z
        for (;;) {
            charge(3);
            v1 = slti(s3, end);
            if (v1 == 0) break;
            backedge();
            charge(10);
            a1 = 0;
            v1 = sll(s3, 3);
            v1 = subu(v1, s3);
            a0 = sll(v1, 6);  // 448 i
            v1 = lui(0x87u);
            v1 = addiu(v1, table_lo);  // the units
            s0 = addu(v1, a0);
            v1 = lw(s0, kUnitUsed);
            if (v1 != 0) {
                charge(3);
                v1 = lw(s0, kUnitSceneRes);
                if (v1 != 0) {
                    charge(1);
                    a1 = si(1);
                }
            }
            charge(4);
            a0 = sltu(zero, a1);
            v1 = si(1);
            if (a0 == v1) {
                charge(161);
                jal(start + 0xF4u, &gen::fn_sub_4C38C0_004c38c0);
                s2 = v0;
                identity(v0);
                v0 = lw(s0, kUnitSceneRes);
                a0 = addiu(sp, 144);
                a1 = lw(v0, kResController);
                jal(start + 0x154u, &gen::fn_sub_1AD940_001ad940);  // the unit's position -> sp+144
                v0 = lw(gp, -22448);
                v1 = lw(v0, 0);
                v0 = sll(v1, 4);
                v0 = subu(v0, v1);
                v0 = sll(v0, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = lw(gp, -19008);
                a0 = addu(v0, v1);
                v1 = lh(s1, 2960);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v0 = addu(a0, v0);
                a0 = s2;
                a1 = addiu(sp, 128);
                lwc1(12, v0, -29856);  // the angle
                a2 = si(2);
                jal(start + 0x1A4u, &gen::fn_sub_4C31B0_004c31b0);
                layout_major_first(s1);
                // f23 / f22 = 63 - 2.25 (2.25 (layout origin - unit) / 100 ...) / 100 on x / z, as compiled
                lwc1(6, sp, 144);
                lwc1(1, s1, 2980);
                lwc1(0, v0, -29852);
                sub_s(0, 0, 6);
                sub_s(3, 1, 0);
                lwc1(5, sp, 152);
                lwc1(1, s1, 2988);
                lwc1(0, v0, -29844);
                sub_s(0, 0, 5);
                sub_s(2, 1, 0);
                v0 = lui(0x4010u);
                mtc1(v0, 4);  // 2.25
                mul_s(0, 4, 3);
                v0 = lui(0x42C8u);
                mtc1(v0, 3);  // 100.0
                div_s(1, 0, 3);
                mul_s(0, 4, 2);
                div_s(2, 0, 3);
                mul_s(0, 4, 1);
                div_s(0, 0, 3);
                v0 = lui(0x427Cu);
                mtc1(v0, 1);  // 63.0
                sub_s(23, 1, 0);
                mul_s(0, 4, 2);
                div_s(0, 0, 3);
                sub_s(22, 1, 0);
                // sp+112 = {2.25 (x - centre x) / 100, 0, 2.25 (z - centre z) / 100}, turned in place
                lwc1(0, sp, 160);
                sub_s(0, 6, 0);
                swc1(0, sp, 112);
                sub_s(1, 5, 21);
                swc1(1, sp, 120);
                mul_s(0, 4, 0);
                div_s(0, 0, 3);
                swc1(0, sp, 112);
                mul_s(0, 4, 1);
                div_s(0, 0, 3);
                swc1(0, sp, 120);
                sw(sp, 116, zero);
                a0 = addiu(sp, 112);
                a1 = a0;
                a2 = s2;
                jal(start + 0x294u, &gen::fn_sub_4C6BE0_004c6be0);
                a0 = 0;
                a1 = lw(gp, kGpSmapSprite);
                a2 = si(sprite);
                jal(start + 0x2A8u, &gen::fn_sprCreateHandle_001158b0);
                s0 = v0;
                v1 = lui(0x4000u);  // scale 2.0
                sw(v0, 44, v1);
                a0 = s0;
                jal(start + 0x2C0u, &gen::fn_sprGetSpriteWidth_001126b0);
                v0 = lui(0x4000u);
                mtc1(v0, 1);  // 2.0
                div_s(2, 0, 1);
                lwc1(0, s1, 2140);
                add_s(1, 0, 23);
                lwc1(0, sp, 112);
                add_s(0, 0, 1);
                sub_s(0, 0, 2);
                swc1(0, s0, 16);  // x
                a0 = s0;
                jal(start + 0x2F4u, &gen::fn_sprGetSpriteHeight_00112740);
                v0 = lui(0x4000u);
                mtc1(v0, 1);
                div_s(2, 0, 1);
                lwc1(0, s1, 2144);
                add_s(1, 0, 22);
                lwc1(0, sp, 120);
                add_s(0, 0, 1);
                sub_s(0, 0, 2);
                swc1(0, s0, 20);  // y
                v0 = si(255);
                sb(s0, 24, v0);  // hidden unless inside
                lwc1(20, s1, 2140);
                a0 = s0;
                jal(start + 0x334u, &gen::fn_sprGetSpriteWidth_001126b0);
                v0 = lui(0x4000u);
                mtc1(v0, 1);
                div_s(2, 0, 1);
                lwc1(1, sp, 112);
                add_s(0, 20, 23);
                add_s(0, 1, 0);
                sub_s(1, 0, 2);
                v0 = lui(0x4100u);
                mtc1(v0, 0);  // 8.0
                add_s(0, 0, 1);
                c_lt_s(20, 0);
                if (cond()) {  // corner x < x + 8
                    charge(19);
                    lwc1(20, s1, 2144);
                    a0 = s0;
                    jal(start + 0x380u, &gen::fn_sprGetSpriteHeight_00112740);
                    v0 = lui(0x4000u);
                    mtc1(v0, 1);
                    div_s(2, 0, 1);
                    lwc1(1, sp, 120);
                    add_s(0, 20, 22);
                    add_s(0, 1, 0);
                    sub_s(1, 0, 2);
                    v0 = lui(0x4100u);
                    mtc1(v0, 0);
                    add_s(0, 0, 1);
                    c_lt_s(20, 0);
                    if (cond()) {  // corner y < y + 8
                        charge(23);
                        lwc1(20, s1, 2140);
                        a0 = s0;
                        jal(start + 0x3CCu, &gen::fn_sprGetSpriteWidth_001126b0);
                        v0 = lui(0x4000u);
                        mtc1(v0, 1);
                        div_s(2, 0, 1);
                        lwc1(1, sp, 112);
                        add_s(0, 20, 23);
                        add_s(0, 1, 0);
                        sub_s(1, 0, 2);
                        v0 = lui(0x4140u);
                        mtc1(v0, 0);  // 12.0
                        add_s(1, 0, 1);
                        v0 = lui(0x42FCu);
                        mtc1(v0, 0);  // 126.0
                        add_s(0, 0, 20);
                        c_le_s(0, 1);
                        if (!cond()) {  // x + 12 < corner x + 126
                            charge(23);
                            lwc1(20, s1, 2144);
                            a0 = s0;
                            jal(start + 0x428u, &gen::fn_sprGetSpriteHeight_00112740);
                            v0 = lui(0x4000u);
                            mtc1(v0, 1);
                            div_s(2, 0, 1);
                            lwc1(1, sp, 120);
                            add_s(0, 20, 22);
                            add_s(0, 1, 0);
                            sub_s(1, 0, 2);
                            v0 = lui(0x4140u);
                            mtc1(v0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x42FCu);
                            mtc1(v0, 0);
                            add_s(0, 0, 20);
                            c_le_s(0, 1);
                            if (!cond()) {  // y + 12 < corner y + 126
                                charge(1);
                                sb(s0, 24, zero);
                            }
                        }
                    }
                }
                charge(10);
                a0 = s0;
                a1 = si(1);
                jal(start + 0x488u, &gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
                a0 = s0;
                jal(start + 0x494u, &gen::fn_sub_115980_00115980);  // release the handle
                a0 = s2;
                jal(start + 0x4A0u, &gen::fn_sub_4C3880_004c3880);  // RwMatrixDestroy
            }
            charge(1);
            s3 = addiu(s3, 1);
        }
        charge(12);
        ra = ld(sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(23, sp, 12);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 176);
    }
    void sub_42B050() { unit_marks(0x42B050u, 17616, 1, 4, 6048, 7); }     // 0x6B44D0, gFldUnitsPc 0x8717A0
    void sub_42B540() { unit_marks(0x42B540u, 17632, 0, 24, -4704, 11); }  // 0x6B44E0, gFldUnitsEc 0x86EDA0

    // 0x42FD80: finds the floor's stair cell -- the last grid cell (x, z) whose kind byte (+2) is 8 and +1 byte is 1 --
    // and stores x / z at work +2992 / +2993 and 800 x / 800 z at +2832 / +2836 (the s4 / s5 holding them keep their
    // values when no cell matches). Then, over the 2 x 2 cells from it, every open side (cell byte +11 bits 1 / 2 / 4 /
    // 8 = towards z - 1, x - 1, z + 1, x + 1) whose neighbour is not a stair cell asks sub_1BF220(sp+144, x, z) for the
    // neighbour's door position; the last one answered is copied to out ($a0).
    void sub_42FD80() {
        enter(15);
        sp = addiu(sp, -160);
        sd(sp, 128, ra);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s6 = a0;
        s0 = lw(a1, kTaskWork);
        s1 = 0;
        for (;;) {  // z
            charge(3);
            v1 = slti(s1, 16);
            if (v1 == 0) break;
            backedge();
            charge(4);
            s2 = 0;
            s3 = sll(s1, 8);
            for (;;) {  // x
                charge(3);
                v1 = slti(s2, 16);
                if (v1 == 0) break;
                backedge();
                charge(9);
                s7 = sll(s2, 4);
                jal(0x42FDD0u, &gen::fn_K_Field_Get_001b9120);
                v1 = addu(s3, v0);
                v1 = addu(v1, s7);
                a0 = lbu(v1, 74);
                v1 = si(8);
                if (a0 == v1) {
                    charge(8);
                    jal(0x42FDF0u, &gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s3, v0);
                    v1 = addu(v1, s7);
                    a0 = lbu(v1, 73);
                    v1 = si(1);
                    if (a0 == v1) {
                        charge(2);
                        s5 = s2;
                        s4 = s1;
                    }
                }
                charge(1);
                s2 = addiu(s2, 1);
            }
            charge(1);
            s1 = addiu(s1, 1);
        }
        charge(17);
        sb(s0, 2992, s5);
        sb(s0, 2993, s4);
        v1 = lui(0x4448u);
        mtc1(v1, 1);  // 800.0
        mtc1(s5, 0);
        cvt_s_w(0, 0);
        mul_s(0, 1, 0);
        swc1(0, s0, 2832);
        mtc1(s4, 0);
        cvt_s_w(0, 0);
        mul_s(0, 1, 0);
        swc1(0, s0, 2836);
        s3 = s5;
        for (;;) {  // x = s5 .. s5 + 1
            charge(4);
            v1 = addiu(s5, 2);
            v1 = slt(s3, v1);
            if (v1 == 0) break;
            backedge();
            charge(4);
            s2 = s4;
            s1 = sll(s3, 4);
            for (;;) {  // z = s4 .. s4 + 1
                charge(4);
                v1 = addiu(s4, 2);
                v1 = slt(s2, v1);
                if (v1 == 0) break;
                backedge();
                charge(9);
                s0 = sll(s2, 8);
                jal(0x42FE90u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x1u;
                if (v0 != 0) {  // open towards z - 1
                    charge(8);
                    jal(0x42FEB0u, &gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s1, v0);
                    v0 = addu(v0, s0);
                    v1 = lbu(v0, -182);
                    v0 = si(8);
                    if (v1 != v0) {
                        charge(6);
                        a1 = s3 & 0xFFFFu;
                        v0 = addiu(s2, -1);
                        a2 = v0 & 0xFFFFu;
                        a0 = addiu(sp, 144);
                        jal(0x42FEE0u, &gen::fn_sub_1BF220_001bf220);
                    }
                }
                charge(8);
                jal(0x42FEE8u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x2u;
                if (v0 != 0) {  // open towards x - 1
                    charge(8);
                    jal(0x42FF08u, &gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s1, v0);
                    v0 = addu(v0, s0);
                    v1 = lbu(v0, 58);
                    v0 = si(8);
                    if (v1 != v0) {
                        charge(6);
                        v0 = addiu(s3, -1);
                        a1 = v0 & 0xFFFFu;
                        a2 = s2 & 0xFFFFu;
                        a0 = addiu(sp, 144);
                        jal(0x42FF38u, &gen::fn_sub_1BF220_001bf220);
                    }
                }
                charge(8);
                jal(0x42FF40u, &gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                v0 = lbu(v0, 83);
                v0 = v0 & 0x4u;
                if (v0 != 0) {  // open towards z + 1
                    charge(8);
                    jal(0x42FF60u, &gen::fn_K_Field_Get_001b9120);
                    v0 = addu(s1, v0);
                    v0 = addu(v0, s0);
                    v1 = lbu(v0, 330);
                    v0 = si(8);
                    if (v1 != v0) {
                        charge(6);
                        a1 = s3 & 0xFFFFu;
                        v0 = addiu(s2, 1);
                        a2 = v0 & 0xFFFFu;
                        a0 = addiu(sp, 144);
                        jal(0x42FF90u, &gen::fn_sub_1BF220_001bf220);
                    }
                }
                charge(8);
                jal(0x42FF98u, &gen::fn_K_Field_Get_001b9120);
                v1 = addu(s1, v0);
                v1 = addu(v1, s0);
                v1 = lbu(v1, 83);
                v1 = v1 & 0x8u;
                if (v1 != 0) {  // open towards x + 1
                    charge(8);
                    jal(0x42FFB8u, &gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s1, v0);
                    v1 = addu(v1, s0);
                    a0 = lbu(v1, 90);
                    v1 = si(8);
                    if (a0 != v1) {
                        charge(6);
                        v0 = addiu(s3, 1);
                        a1 = v0 & 0xFFFFu;
                        a2 = s2 & 0xFFFFu;
                        a0 = addiu(sp, 144);
                        jal(0x42FFE8u, &gen::fn_sub_1BF220_001bf220);
                    }
                }
                charge(1);
                s2 = addiu(s2, 1);
            }
            charge(1);
            s3 = addiu(s3, 1);
        }
        charge(18);
        lwc1(2, sp, 144);
        lwc1(1, sp, 148);
        lwc1(0, sp, 152);
        swc1(2, s6, 0);
        swc1(1, s6, 4);
        swc1(0, s6, 8);
        ra = ld(sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 160);
    }

    // 0x430060 ("y_staire_disp_proc" update, [Y_SMap_UpdateStaireDispTask] bands.sym): while shown, draws sprite 4 of
    // the mini-map's sprite file at the icon's (x, y) with scale 4.0 and alpha 0, after storing the sprite's width /
    // height (int) at work +16 / +20. Returns 0 (keep running).
    void Y_SMap_UpdateStaireDispTask() {
        enter(8);
        sp = addiu(sp, -48);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        v0 = lb(s0, kStairShown);
        if (v0 == 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(41);
            a0 = 0;
            a1 = lw(gp, kGpSmapSprite);
            a2 = si(4);
            jal(0x430098u, &gen::fn_sprCreateHandle_001158b0);
            s1 = v0;
            a0 = s1;
            jal(0x4300A8u, &gen::fn_sprGetSpriteWidth_001126b0);
            cvt_w_s(0, 0);
            mfc1(v0, 0);
            sw(s0, 16, v0);
            a0 = s1;
            jal(0x4300C4u, &gen::fn_sprGetSpriteHeight_00112740);
            cvt_w_s(0, 0);
            mfc1(v0, 0);
            sw(s0, 20, v0);
            v0 = lui(0x4080u);  // 4.0
            sw(s1, 44, v0);
            v0 = lh(s0, kStairX);
            mtc1(v0, 0);
            cvt_s_w(0, 0);
            swc1(0, s1, 16);
            v0 = lh(s0, kStairY);
            mtc1(v0, 0);
            cvt_s_w(0, 0);
            swc1(0, s1, 20);
            sb(s1, 24, zero);
            a0 = s1;
            a1 = si(1);
            jal(0x430118u, &gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
            a0 = s1;
            jal(0x430124u, &gen::fn_sub_115980_00115980);
            v0 = 0;
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 48);
    }

    // One of the map frame's four corner handles: sprite `index` of the mini-map's sprite file into work +slot, alpha
    // 255, x / y / scale 50.0 (each store re-reads the handle from the work, as compiled). `y_int`: y comes from the
    // integer 313 (through $f0) instead of the word 0x43630000 (227.0).
    void frame_handle(s32 slot, s32 index, u32 pc, u32 x_hi, bool y_int, bool last) {
        a0 = 0;
        a1 = lw(gp, kGpSmapSprite);
        a2 = si(index);
        jal(pc, &gen::fn_sprCreateHandle_001158b0);
        sw(s0, slot, v0);
        v1 = si(255);
        sb(v0, 24, v1);
        Gpr& k = last ? a0 : v1;  // the last handle's constants go through $a0 and the handle through $v1
        Gpr& h = last ? v1 : v0;
        k = lui(x_hi);
        h = lw(s0, slot);
        sw(h, 16, k);
        if (y_int) {
            h = si(313);
            mtc1(h, 0);
            cvt_s_w(0, 0);
            h = lw(s0, slot);
            swc1(0, h, 20);
        } else {
            k = lui(0x4363u);  // 227.0
            h = lw(s0, slot);
            sw(h, 20, k);
        }
        k = lui(0x4248u);  // 50.0
        h = lw(s0, slot);
        sw(h, 44, k);
    }

    // 0x430630: creates the map frame's four corner sprites (sprites 0..3 into work +76 / +80 / +84 / +88 at x 7 /
    // 95 and y 227 / 313, scale 50.0, alpha 255).
    void sub_430630() {
        enter(83);
        sp = addiu(sp, -32);
        sd(sp, 16, ra);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        frame_handle(76, 0, 0x43064Cu, 0x40E0u, false, false);  // x 7.0
        frame_handle(80, 1, 0x430690u, 0x42BEu, false, false);  // x 95.0
        frame_handle(84, 2, 0x4306D4u, 0x40E0u, true, false);
        frame_handle(88, 3, 0x430724u, 0x42BEu, true, true);
        ra = ld(sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 32);
    }

    // `(u8 / u16)(unsigned) $f<src>` with the 2^31 split (0x4F000000 through $f0), into $v1 masked with `mask`.
    void float_to_unsigned(unsigned src, u32 mask) {
        v0 = lui(0x4F00u);
        mtc1(v0, 0);
        c_le_s(0, src);
        charge(6);
        if (!cond()) {
            cvt_w_s(0, src);
            mfc1(v1, 0);
            v1 = v1 & mask;
        } else {
            sub_s(0, src, 0);
            cvt_w_s(0, 0);
            mfc1(v1, 0);
            v0 = lui(0x8000u);
            v1 = v1 | v0;
            v1 = v1 & mask;
        }
    }

    // 0x430780: the pulsing marker (sprite 13): $a0 holds two f32 (an offset, spilled to sp+88), ($a1, $a2) the
    // position, $a3 the frame. s = 0.5 + 0.5 sin(frame * gp[-31676]) (in $f21), alpha = 255 - 255 sin(frame *
    // gp[-31672]) (in $f20); x = a1 + (offset.x - s * width / 2) + width / 4 and y likewise, scale 1.0, alpha (u8),
    // the u16 pair +40 / +42 = 4096 s (both from $f1).
    void sub_430780() {
        enter(104);
        sp = addiu(sp, -96);
        sd(sp, 64, ra);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        sd(sp, 88, a0);
        s2 = a1;
        s1 = a2;
        s0 = a3;
        mtc1(s0, 0);
        cvt_s_w(1, 0);
        lwc1(0, gp, -31676);
        mul_s(12, 0, 1);
        jal(0x4307C4u, &gen::fn_sinf_0052e878);
        v0 = lui(0x3F00u);
        mtc1(v0, 2);  // 0.5
        mtc1(zero, 1);
        adda_s(1, 2);
        madd_s(21, 2, 0);  // f21 = 0.5 + 0.5 sin
        mtc1(s0, 0);
        cvt_s_w(1, 0);
        lwc1(0, gp, -31672);
        mul_s(12, 0, 1);
        jal(0x4307F8u, &gen::fn_sinf_0052e878);
        v0 = lui(0xC37Fu);
        mtc1(v0, 3);  // -255.0
        v0 = lui(0x437Fu);
        mtc1(v0, 2);  // 255.0
        mtc1(zero, 1);
        adda_s(1, 2);
        madd_s(20, 3, 0);  // f20 = 255 - 255 sin
        a0 = 0;
        a1 = lw(gp, kGpSmapSprite);
        a2 = si(13);
        jal(0x43082Cu, &gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        v1 = lui(0x3F80u);  // scale 1.0
        sw(v0, 44, v1);
        a0 = s0;
        jal(0x430844u, &gen::fn_sprGetSpriteWidth_001126b0);
        v0 = lui(0x4000u);
        mtc1(v0, 1);  // 2.0
        div_s(2, 0, 1);
        lwc1(1, sp, 88);
        mtc1(zero, 0);
        adda_s(0, 1);
        msub_s(22, 21, 2);  // f22 = offset.x - s * width / 2
        a0 = s0;
        jal(0x430874u, &gen::fn_sprGetSpriteWidth_001126b0);
        v0 = lui(0x4080u);
        mtc1(v0, 1);  // 4.0
        div_s(0, 0, 1);
        add_s(1, 22, 0);
        mtc1(s2, 0);
        cvt_s_w(0, 0);
        add_s(0, 0, 1);
        swc1(0, s0, 16);
        a0 = s0;
        jal(0x4308A8u, &gen::fn_sprGetSpriteHeight_00112740);
        v0 = lui(0x4000u);
        mtc1(v0, 1);
        div_s(2, 0, 1);
        lwc1(1, sp, 92);
        mtc1(zero, 0);
        adda_s(0, 1);
        msub_s(22, 21, 2);
        a0 = s0;
        jal(0x4308D8u, &gen::fn_sprGetSpriteHeight_00112740);
        v0 = lui(0x4080u);
        mtc1(v0, 1);
        div_s(0, 0, 1);
        add_s(1, 22, 0);
        mtc1(s1, 0);
        cvt_s_w(0, 0);
        add_s(0, 0, 1);
        swc1(0, s0, 20);
        float_to_unsigned(20, 0xFFu);
        charge(11);
        sb(s0, 24, v1);
        v0 = lui(0x4580u);
        mtc1(v0, 0);  // 4096.0
        mul_s(1, 0, 21);
        float_to_unsigned(1, 0xFFFFu);
        charge(7);
        sh(s0, 40, v1);
        float_to_unsigned(1, 0xFFFFu);
        charge(18);
        sh(s0, 42, v1);
        a0 = s0;
        a1 = si(1);
        jal(0x430A04u, &gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
        a0 = s0;
        jal(0x430A10u, &gen::fn_sub_115980_00115980);
        ra = ld(sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 96);
    }

    // `8 - (float)(u32)(RpRandom() & 15)` (sub_488F30) truncated into the s16 at s0 + off; `t` carries the value and
    // `h` the halves of the unsigned-convert path, as compiled.
    void jitter(Gpr& t, Gpr& h, s32 off, u32 pc, u64 tail) {
        jal(pc, &gen::fn_sub_488F30_00488f30);
        t = v0 & 0xFu;
        if (gez(t)) {
            charge(5);
            mtc1(t, 0);
            cvt_s_w(1, 0);
        } else {
            charge(7);
            h = srl(t, 1);
            t = t & 0x1u;
            h = h | t;
            mtc1(h, 0);
            cvt_s_w(1, 0);
            add_s(1, 1, 1);
        }
        charge(tail);
        t = lui(0x4100u);
        mtc1(t, 0);  // 8.0
        sub_s(0, 0, 1);
        cvt_w_s(0, 0);
        mfc1(t, 0);
        sh(s0, off, t);
    }

    // 0x430A40: re-seeds the five sparkles of row (s8) $a0 in the field root's work (K_Field_Get() +24 -> +60):
    // byte +2274 + 5 row + i = 4 i, byte +2259 + 5 row + i = 0, and the s16 jitters +2294 / +2324 at 10 (row - 1) + 2 i
    // = 8 - (random & 15).
    void sub_430A40() {
        enter(24);
        sp = addiu(sp, -80);
        sd(sp, 64, ra);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s0 = a0;
        jal(0x430A5Cu, &gen::fn_K_Field_Get_001b9120);
        v1 = lw(v0, 24);
        a1 = lw(v1, kTaskWork);
        s3 = 0;
        a0 = dsll32(s0, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        s2 = addu(a1, v1);  // work + 5 row
        a0 = addiu(a0, -1);
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        v1 = sll(v1, 1);
        s1 = addu(a1, v1);  // work + 10 (row - 1)
        for (;;) {
            charge(3);
            v1 = slti(s3, 5);
            if (v1 == 0) break;
            backedge();
            charge(11);
            v1 = addu(s2, s3);
            v0 = sll(s3, 2);
            sb(v1, 2274, v0);
            sb(v1, 2259, zero);
            v0 = sll(s3, 1);
            s0 = addu(s1, v0);
            jitter(v0, v1, 2294, 0x430AB8u, 13);
            jitter(v1, a0, 2324, 0x430B1Cu, 9);
            s3 = addiu(s3, 1);
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 80);
    }
};

// =====================================================================================================================
// The map's set-up and the seen-cells grid
// =====================================================================================================================

struct SMapSetup : SMapDraw {
    using SMapDraw::SMapDraw;

    // Marks one cell seen in the u8 grid at 0x95C110 (16 x 16): the room sub_433810(x, z) returns (a u8 cell index,
    // 0 = none) or else the cell itself, written through `base_lo` (0x95C110 + the neighbour's offset) + x + 16 z.
    void mark_room(s32 base_lo, u64 cyc_room) {
        a0 = v0 & 0xFFu;
        if (a0 == 0) {
            charge(9);
            a0 = si(1);
            v0 = lui(0x96u);
            v0 = addiu(v0, base_lo);
            v1 = addu(v0, s0);
            v0 = sll(s1, 4);
            v0 = addu(v0, v1);
            sb(v0, 0, a0);
        } else {
            charge(cyc_room);
            v1 = si(1);
            v0 = lui(0x96u);
            v0 = addiu(v0, -16112);  // 0x95C110
            v0 = addu(v0, a0);
            sb(v0, 0, v1);
        }
    }
    // The open side `bit` of cell (s0, s1) (byte +11 of the grid cell): mark the room of the neighbour (nx, nz).
    void mark_side(u32 pc_field, u32 pc_room, u32 bit, bool x_axis, s32 delta, s32 base_lo) {
        charge(8);
        jal(pc_field, &gen::fn_K_Field_Get_001b9120);
        v0 = addu(v0, s6);
        v0 = addu(v0, s7);
        v0 = lbu(v0, 83);
        v0 = v0 & bit;
        if (v0 != 0) {
            charge(9);
            if (x_axis) {
                v0 = addiu(s0, delta);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                a1 = s5;
            } else {
                v0 = addiu(s1, delta);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                a0 = s3;
            }
            jal(pc_room, &gen::fn_sub_433810_00433810);
            mark_room(base_lo, 5);
        }
    }
    // The +2824 / +2825 cell of the map work in the seen grid == 1 (through $a0 / $v1 into `out`), `cyc` the block.
    void seen_target(Gpr& out) {
        a0 = lb(s2, 2824);
        v1 = lui(0x96u);
        v1 = addiu(v1, -16112);  // 0x95C110
        a0 = addu(v1, a0);
        v1 = lb(s2, 2825);
        v1 = sll(v1, 4);
        v1 = addu(v1, a0);
        out = lb(v1, 0);
    }
    void epilogue144() {
        ra = ld(sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 144);
    }

    // 0x42A550 (task, pc, x, z): marks the cell (x, z) and the rooms behind its open sides (+11 bits 8 / 2 / 1 / 4 =
    // x + 1, x - 1, z - 1, z + 1) seen. Then, for a party member pc != 0 (the s8 of $a1) that sub_435260 says is not
    // busy: when its sub_4353F0 is not 1, the flag gp-0x4628 is clear and the map work's target cell (+2824 / +2825)
    // has been seen, sub_456490(pc) and the flag = 1; when the flag gp-0x462C is clear: standing on the work's cell
    // (+2827 / +2828) with sub_43C730(pc) == 1 calls sub_456450(pc) (unless its sub_4353F0 is 1) and sets that flag,
    // standing on a stair cell (kind 8) only sets it. For pc 0: when sub_4352E0() == 0 the first flag follows the
    // target cell's seen byte.
    void sub_42A550() {
        enter(21);
        sp = addiu(sp, -144);
        sd(sp, 128, ra);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s4 = a1;
        s3 = a2;
        s5 = a3;
        s2 = lw(a0, kTaskWork);
        a0 = s3;
        a1 = s5;
        jal(0x42A590u, &gen::fn_sub_433810_00433810);
        a0 = v0 & 0xFFu;
        if (a0 == 0) {  // no room: the cell itself
            charge(13);
            a0 = si(1);
            v1 = dsll32(s3, 24);
            v1 = dsra32(v1, 24);
            v0 = lui(0x96u);
            v0 = addiu(v0, -16112);  // 0x95C110
            v1 = addu(v0, v1);
            v0 = dsll32(s5, 24);
            v0 = dsra32(v0, 24);
            v0 = sll(v0, 4);
            v0 = addu(v0, v1);
            sb(v0, 0, a0);
        } else {
            charge(5);
            v1 = si(1);
            v0 = lui(0x96u);
            v0 = addiu(v0, -16112);
            v0 = addu(v0, a0);
            sb(v0, 0, v1);
        }
        charge(14);
        s1 = dsll32(s5, 24);
        s1 = dsra32(s1, 24);  // z
        s6 = sll(s1, 8);
        s0 = dsll32(s3, 24);
        s0 = dsra32(s0, 24);  // x
        s7 = sll(s0, 4);
        jal(0x42A604u, &gen::fn_K_Field_Get_001b9120);
        v0 = addu(v0, s6);
        v0 = addu(v0, s7);
        v0 = lbu(v0, 83);
        v0 = v0 & 0x8u;
        if (v0 != 0) {  // x + 1
            charge(9);
            v0 = addiu(s0, 1);
            a0 = dsll32(v0, 24);
            a0 = dsra32(a0, 24);
            a1 = s5;
            jal(0x42A634u, &gen::fn_sub_433810_00433810);
            mark_room(-16111, 5);  // 0x95C111
        }
        mark_side(0x42A680u, 0x42A6B0u, 0x2u, true, -1, -16113);   // x - 1: 0x95C10F
        mark_side(0x42A6FCu, 0x42A72Cu, 0x1u, false, -1, -16128);  // z - 1: 0x95C100
        mark_side(0x42A778u, 0x42A7A8u, 0x4u, false, 1, -16096);   // z + 1: 0x95C120
        charge(4);
        s0 = dsll32(s4, 24);
        s0 = dsra32(s0, 24);
        if (s0 != 0) {
            charge(7);
            a0 = s4;
            jal(0x42A808u, &gen::fn_sub_435260_00435260);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            if (v1 == 0) {
                charge(14);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                s1 = sll(v0, 6);  // 448 pc
                v0 = lui(0x87u);
                v0 = addiu(v0, 6048);  // 0x8717A0 gFldUnitsPc
                s0 = addu(v0, s1);
                a0 = s0;
                jal(0x42A83Cu, &gen::fn_sub_4353F0_004353f0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                a1 = si(1);
                if (v1 != a1) {
                    charge(3);
                    v1 = lb(gp, -17960);
                    if (v1 == 0) {
                        charge(10);
                        seen_target(v1);
                        if (v1 == a1) {
                            charge(5);
                            a0 = s4;
                            jal(0x42A890u, &gen::fn_sub_456490_00456490);
                            v1 = si(1);
                            sb(gp, -17960, v1);
                        }
                    }
                }
                charge(3);
                v1 = lb(gp, -17964);
                if (v1 == 0) {
                    charge(10);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6132);  // 0x8717F4: the units' +84
                    s3 = addu(v0, s1);
                    s1 = lb(s2, 2827);
                    v0 = lw(s3, 0);
                    a0 = lw(v0, kResController);
                    jal(0x42A8C4u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    if (s1 == v0) {
                        charge(7);
                        s1 = lb(s2, 2828);
                        v0 = lw(s3, 0);
                        a0 = lw(v0, kResController);
                        jal(0x42A8E0u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        if (s1 == v0) {
                            charge(6);
                            a0 = s4;
                            jal(0x42A8F4u, &gen::fn_sub_43C730_0043c730);
                            v1 = si(1);
                            if (v0 != v1) {
                                charge(12);
                                epilogue144();
                                return;
                            }
                            charge(8);
                            a0 = s0;
                            jal(0x42A90Cu, &gen::fn_sub_4353F0_004353f0);
                            a0 = dsll32(v0, 24);
                            a0 = dsra32(a0, 24);
                            v1 = si(1);
                            if (a0 != v1) {
                                charge(3);
                                a0 = s4;
                                jal(0x42A92Cu, &gen::fn_sub_456450_00456450);
                            }
                            charge(4);
                            v1 = si(1);
                            sb(gp, -17964, v1);
                            charge(12);
                            epilogue144();
                            return;
                        }
                    }
                    // not on the work's cell: on a stair cell (kind 8) only the flag
                    charge(26);
                    v1 = dsll32(s4, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = lui(0x87u);
                    v0 = addiu(v0, 6132);  // 0x8717F4
                    s1 = addu(v0, v1);
                    v0 = lw(s1, 0);
                    a0 = lw(v0, kResController);
                    jal(0x42A96Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    s0 = sll(v0, 8);
                    jal(0x42A978u, &gen::fn_K_Field_Get_001b9120);
                    s0 = addu(v0, s0);
                    v0 = lw(s1, 0);
                    a0 = lw(v0, kResController);
                    jal(0x42A98Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    v1 = sll(v0, 4);
                    v1 = addu(s0, v1);
                    a0 = lbu(v1, 74);
                    v1 = si(8);
                    if (a0 == v1) {
                        charge(4);
                        v1 = si(1);
                        sb(gp, -17964, v1);
                    }
                }
            }
        } else {
            charge(4);
            jal(0x42A9BCu, &gen::fn_sub_4352E0_004352e0);
            if (v0 == 0) {
                charge(3);
                v1 = lb(gp, -17960);
                if (v1 == 0) {
                    charge(11);
                    seen_target(a0);
                    v1 = si(1);
                    if (a0 == v1) {
                        charge(1);
                        sb(gp, -17960, v1);
                    }
                }
            }
        }
        charge(12);
        epilogue144();
    }

    // The layout record's f32 at `off` for the s16 at a0 +2940 (layer i's layout entry), into $v0 (the record pointer)
    // through $a1: `*(gp-0x4A40) + 964 major + 40 entry`.
    void layer_layout() {
        v0 = lw(gp, -22448);
        v1 = lw(v0, 0);
        v0 = sll(v1, 4);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = lw(gp, -19008);
        a1 = addu(v0, v1);
        v1 = lh(a0, 2940);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(a1, v0);
    }

    // 0x42BA50: creates the map's tmx layer tasks: for each of the +2858 layers, its pair +2860 + 8 i = the map corner
    // (+2140 / +2144) + the layout entry's offsets (-29864 / -29860), and work +92 + 8 i = sub_427BF0(task, layer tmx
    // (work +40 + 4 i), the pair (two f32 in $a2, read unaligned with ldl / ldr), colour 0xFFFFFFFF, sp+80 {+8 size
    // from the tmx's +12 / +16}, $f12 5.0, $f13 / $f14 the layout's scale (-29872 / -29868), $f15 / $f16 their ratio to
    // the tmx size).
    void sub_42BA50() {
        enter(11);
        sp = addiu(sp, -112);
        sd(sp, 64, ra);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s3 = a0;
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        for (;;) {
            charge(4);
            v1 = lb(s1, 2858);
            v1 = slt(s2, v1);
            if (v1 == 0) break;
            backedge();
            charge(89);
            v0 = sll(s2, 1);
            a0 = addu(s1, v0);  // work + 2 i (the layer's s16 entry at +2940)
            v0 = sll(s2, 3);
            s0 = addu(s1, v0);
            a3 = addiu(s0, 2860);
            layer_layout();
            lwc1(1, v0, -29864);
            lwc1(0, s1, 2140);
            add_s(0, 0, 1);
            swc1(0, s0, 2860);
            layer_layout();
            lwc1(1, v0, -29860);
            lwc1(0, s1, 2144);
            add_s(0, 0, 1);
            swc1(0, s0, 2864);
            v0 = sll(s2, 2);
            v0 = addu(s1, v0);
            a1 = lw(v0, 40);  // the layer's tmx
            v0 = lw(a1, 0);
            v1 = lw(v0, 16);
            sw(sp, 92, v1);
            v0 = lw(v0, 12);
            sw(sp, 88, v0);
            a2 = si(255);
            sb(sp, 111, a2);
            sb(sp, 109, a2);
            sb(sp, 110, a2);
            sb(sp, 108, a2);
            a5 = lw(gp, -19008);
            a2 = lw(gp, -22448);
            a4 = lw(a2, 0);
            a2 = sll(a4, 4);
            a2 = subu(a2, a4);
            a2 = sll(a2, 4);
            a2 = addu(a2, a4);
            a2 = sll(a2, 2);
            a4 = addu(a5, a2);
            a2 = lh(a0, 2940);
            a0 = sll(a2, 2);
            a0 = addu(a0, a2);
            a0 = sll(a0, 3);
            a0 = addu(a4, a0);
            lwc1(14, a0, -29868);
            lwc1(13, a0, -29872);
            mtc1(v0, 0);
            cvt_s_w(0, 0);
            div_s(15, 13, 0);
            mtc1(v1, 0);
            cvt_s_w(0, 0);
            div_s(16, 14, 0);
            v0 = lui(0x40A0u);
            mtc1(v0, 12);  // 5.0
            a0 = s3;
            ldr(a2, a3, 0);
            ldl(a2, a3, 7);
            a3 = lw(sp, 108);
            a4 = addiu(sp, 80);
            jal(0x42BBD0u, &gen::fn_sub_427BF0_00427bf0);
            sw(s0, 92, v0);
            s2 = addiu(s2, 1);
        }
        charge(8);
        ra = ld(sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 112);
    }

    // The symbol-direction task's box: work +2200 cleared if set (`cyc` = the next block), sub_423FE0(sp+56, 0, 126,
    // 126, 32, 32) centres a 32 x 32 box in the 126 x 126 map, +2204 / +2208 = the map corner + that offset, and
    // +2200 = Y_Stratum_CreateSmapSymbolDirpTask(task, 32, 32, $f12 / $f13 = the box, $f14 1.0) ("smap_symbol_dirp", bands.sym
    // [Y_Stratum_CreateSmapSymbolDirpTask]).
    void symbol_task(u64 cyc, u32 pc_box, u32 pc_create) {
        charge(3);
        v0 = lw(s0, 2200);
        if (v0 != 0) {
            charge(1);
            sw(s0, 2200, zero);
        }
        charge(cyc);
        a0 = addiu(sp, 56);
        a1 = 0;
        a2 = si(126);
        a3 = a2;
        a4 = si(32);
        a5 = a4;
        jal(pc_box, &gen::fn_sub_423FE0_00423fe0);
        lwc1(1, s0, 2140);
        lwc1(0, sp, 56);
        add_s(0, 1, 0);
        swc1(0, s0, 2204);
        lwc1(1, s0, 2144);
        lwc1(0, sp, 60);
        add_s(0, 1, 0);
        swc1(0, s0, 2208);
        v0 = lui(0x3F80u);
        mtc1(v0, 14);  // 1.0
        a0 = s1;
        lwc1(12, s0, 2204);
        lwc1(13, s0, 2208);
        a1 = si(32);
        a2 = a1;
        jal(pc_create, &gen::fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0);
        sw(s0, 2200, v0);
    }

    // 0x42BC10: while gFldUnitsPc[0] is used (0x8717E8 = its +72): the symbol-direction task (above), its floor
    // (sub_4563C0, the s8 at +2960), position (sub_4563D0, the corner pair +2140 read unaligned) and angle (sub_4563B0,
    // the layout's -29856); the floor origin's x / z (+2980 / +2988) = 0, the layers placed (sub_42ADB0) and every
    // layer task's work +336 = 1.
    void sub_42BC10() {
        enter(10);
        sp = addiu(sp, -64);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a0;
        s0 = lw(a0, kTaskWork);
        v1 = lui(0x87u);
        v1 = lw(v1, 6120);  // 0x8717E8: gFldUnitsPc[0] +72
        if (v1 != 0) {
            symbol_task(62, 0x42BC60u, 0x42BCA4u);
            a1 = lb(s0, 2960);
            a0 = v0;
            jal(0x42BCB8u, &gen::fn_sub_4563C0_004563c0);
            a0 = lw(s0, 2200);
            ldr(a1, s0, 2140);
            ldl(a1, s0, 2147);
            jal(0x42BCCCu, &gen::fn_sub_4563D0_004563d0);
            layout_major_first(s0);
            a0 = lw(s0, 2200);
            lwc1(12, v0, -29856);
            jal(0x42BD14u, &gen::fn_sub_4563B0_004563b0);
            sw(s0, 2980, zero);
            sw(s0, 2988, zero);
            a0 = s1;
            jal(0x42BD28u, &gen::fn_sub_42ADB0_0042adb0);
            a1 = 0;
            a0 = si(1);
            for (;;) {
                charge(4);
                v1 = lb(s0, 2858);
                v1 = slt(a1, v1);
                if (v1 == 0) break;
                backedge();
                charge(6);
                v1 = sll(a1, 3);
                v1 = addu(s0, v1);
                v1 = lw(v1, 92);
                v1 = lw(v1, kTaskWork);
                sb(v1, 336, a0);
                a1 = addiu(a1, 1);
            }
        }
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 64);
    }

    // One cell's tmx task: Y_LMap_CreateTmxDispTask(task, the room tmx 0x95C0E0[kind] (smap/smap0..8.tmx), kind, cell +6, $f12 = $f13
    // = scale) into the cell's slot; `cyc` / the scale differ for kinds < 5 (0.625) and the others (0.59375).
    void cell_tmx(u64 cyc, u32 pc0, u32 scale_hi) {
        charge(cyc);
        jal(pc0, &gen::fn_K_Field_Get_001b9120);
        v0 = addu(s1, v0);
        v0 = addu(v0, s5);
        v0 = lbu(v0, 74);
        v1 = sll(v0, 2);
        v0 = lui(0x96u);
        v0 = addiu(v0, -16160);  // 0x95C0E0: the room tmx files
        s7 = addu(v0, v1);
        jal(pc0 + 0x24u, &gen::fn_K_Field_Get_001b9120);
        v0 = addu(s1, v0);
        v0 = addu(v0, s5);
        fp = lb(v0, 74);
        jal(pc0 + 0x38u, &gen::fn_K_Field_Get_001b9120);
        v0 = addu(s1, v0);
        v0 = addu(v0, s5);
        a3 = lb(v0, 78);
        v0 = lui(scale_hi);
        mtc1(v0, 12);
        a0 = s4;
        a1 = lw(s7, 0);
        a2 = fp;
        mov_s(13, 12);
        jal(pc0 + 0x64u, &gen::fn_Y_LMap_CreateTmxDispTask_00427670);
        sw(s0, 0, v0);
    }

    // 0x42BD80: creates the tmx task of every grid cell whose bytes +0 / +1 are 1 / 1 (a room on the map) into work
    // +92 + 128 z + 8 x (cleared first when set), sets its work +336 = 1 and the cell's byte +96 = 0. The work pointer
    // is kept in a quadword at sp+160 (sq / lq of $v1).
    void sub_42BD80() {
        enter(17);
        sp = addiu(sp, -176);
        sd(sp, 144, ra);
        sq(fp, sp, 128);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s4 = a0;
        v1 = lw(a0, kTaskWork);
        sq(v1, sp, 160);
        s2 = 0;
        for (;;) {  // z
            charge(3);
            v1 = slti(s2, 16);
            if (v1 == 0) break;
            backedge();
            charge(7);
            s3 = 0;
            s1 = sll(s2, 8);
            a0 = sll(s2, 7);
            lq(v1, sp, 160);
            s6 = addu(v1, a0);
            for (;;) {  // x
                charge(3);
                v1 = slti(s3, 16);
                if (v1 == 0) break;
                backedge();
                charge(9);
                s0 = sll(s3, 4);
                jal(0x42BDE4u, &gen::fn_K_Field_Get_001b9120);
                v1 = addu(s1, v0);
                v1 = addu(v1, s0);
                a0 = lbu(v1, 72);
                v1 = si(1);
                if (a0 == v1) {
                    charge(8);
                    jal(0x42BE04u, &gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s1, v0);
                    v1 = addu(v1, s0);
                    a0 = lbu(v1, 73);
                    v1 = si(1);
                    if (a0 == v1) {
                        charge(6);
                        v0 = sll(s3, 3);
                        v0 = addu(s6, v0);
                        s0 = addiu(v0, 92);
                        v0 = lw(v0, 92);
                        if (v0 != 0) {
                            charge(1);
                            sw(s0, 0, zero);
                        }
                        charge(11);
                        s5 = sll(s3, 4);
                        jal(0x42BE44u, &gen::fn_K_Field_Get_001b9120);
                        jal(0x42BE4Cu, &gen::fn_K_Field_Get_001b9120);
                        v0 = addu(s1, v0);
                        v0 = addu(v0, s5);
                        v0 = lbu(v0, 74);
                        at = slti(v0, 5);
                        if (at != 0) {
                            cell_tmx(30, 0x42BE6Cu, 0x3F20u);  // 0.625
                        } else {
                            cell_tmx(28, 0x42BEE4u, 0x3F18u);  // 0.59375
                        }
                        charge(7);
                        v1 = sll(s3, 3);
                        a1 = addu(s6, v1);
                        a0 = si(1);
                        v1 = lw(s0, 0);
                        v1 = lw(v1, kTaskWork);
                        sb(v1, 336, a0);
                        sb(a1, 96, zero);
                    }
                }
                charge(1);
                s3 = addiu(s3, 1);
            }
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(13);
        ra = ld(sp, 144);
        lq(fp, sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 176);
    }

    // 0x42BFD0: the symbol-direction task alone, while gFldUnitsPc[0] is used and has a scene resource.
    void sub_42BFD0() {
        enter(11);
        sp = addiu(sp, -64);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a0;
        s0 = lw(a0, kTaskWork);
        v1 = lui(0x87u);
        v1 = lw(v1, 6120);  // 0x8717E8: gFldUnitsPc[0] +72
        v1 = sltu(zero, v1);
        if (v1 != 0) {
            charge(3);
            v1 = lui(0x87u);
            v1 = lw(v1, 6132);  // 0x8717F4: +84
            v1 = sltu(zero, v1);
        }
        charge(2);
        if (v1 != 0) symbol_task(26, 0x42C038u, 0x42C07Cu);
        charge(6);
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 64);
    }
};

struct SMapMarks : SMapSetup {
    using SMapSetup::SMapSetup;

    // 0x42C0A0 (task, pc, x, z, ox, oz; ox / oz in $a4 / $a5): the mark of party member (s8) pc when its unit is used, has a
    // scene resource and stands on cell (x, z). Its map position (f32 pair at work +2232 + 8 pc) is, per axis, the map corner
    // (+2140 / +2144) + size * o - its cell offset + the player's cell offset - 2 size + size / 2 - 8 with the cell size in
    // pixels the s8 at +2857 and the offsets int-truncated (sub_429EF0's formula, inlined; the player's offset from the
    // frozen centre while +2149 is set). Inside the map ([corner + 8, corner + 126 - 12) on both axes) it sets +2359 + pc = 1
    // and draws: with bad status bit 0x80 (datGetBadStatusNoDown of the unit's s16 at 0x871948 + 448 pc) or 0x80000 a blink
    // -- the s16 phase +2352 + 2 pc counts 0..40, sprite 10 at the mark + 3 with scale 3.0 and alpha 128 - 128 sin(phase *
    // gp[-31676]) -- then sprite 8 (0x80) or 9 (0x80000) at the mark with scale 2.0 ($f21) and alpha 0; without either, sprite 7.
    // sprCreateHandle / sprDrawSprite (sub_1127D0) / the handle release (sub_115980) per sprite.
    void sub_42C0A0() {
        enter(31);
        sp = addiu(sp, -384);
        sd(sp, 144, ra);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(23, sp, 12);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s4 = a1;
        s3 = a3;
        s6 = a4;
        s7 = a5;
        s2 = lw(a0, kTaskWork);
        a1 = 0;
        a0 = dsll32(s4, 24);
        a0 = dsra32(a0, 24);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        s1 = sll(v1, 6);
        v1 = lui(0x87u);
        v1 = addiu(v1, 6120);  // 0x8717E8
        v1 = addu(v1, s1);
        v1 = lw(v1, 0);
        if (v1 != 0) {
            charge(6);
            v1 = lui(0x87u);
            v1 = addiu(v1, 6132);  // 0x8717F4
            v1 = addu(v1, s1);
            v1 = lw(v1, 0);
            if (v1 != 0) {
                charge(1);
                a1 = si(1);
            }
        }
        charge(4);
        a0 = sltu(zero, a1);
        v1 = si(1);
        if (a0 == v1) {
            charge(11);
            v0 = lui(0x87u);
            v0 = addiu(v0, 6132);  // 0x8717F4
            s0 = addu(v0, s1);
            s5 = dsll32(a2, 16);
            s5 = dsra32(s5, 16);
            v0 = lw(s0, 0);
            a0 = lw(v0, kResController);
            jal(0x42C164u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            if (s5 == v0) {
                charge(8);
                s3 = dsll32(s3, 16);
                s3 = dsra32(s3, 16);
                v0 = lw(s0, 0);
                a0 = lw(v0, kResController);
                jal(0x42C184u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                if (s3 == v0) {
                    charge(3);
                    v0 = lb(s2, 2149);
                    if (v0 == 0) {
                        charge(118);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = addiu(sp, 320);
                        a1 = lw(v0, kResController);
                        jal(0x42C1C0u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 320);
                        lwc1(1, sp, 324);
                        lwc1(0, sp, 328);
                        swc1(2, sp, 336);
                        swc1(1, sp, 340);
                        swc1(0, sp, 344);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = lw(v0, kResController);
                        jal(0x42C1ECu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 336);
                        sub_s(3, 0, 1);
                        v0 = lui(0x4000u);
                        mtc1(v0, 21);  // 2.0
                        div_s(2, 20, 2);
                        div_s(1, 20, 21);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(22, 0);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        s3 = dsll32(s4, 24);
                        s3 = dsra32(s3, 24);
                        v0 = sll(s3, 3);
                        v0 = subu(v0, s3);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        s0 = addu(v0, v1);
                        v0 = lw(s0, 0);
                        a0 = addiu(sp, 352);
                        a1 = lw(v0, kResController);
                        jal(0x42C290u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 352);
                        lwc1(1, sp, 356);
                        lwc1(0, sp, 360);
                        swc1(2, sp, 368);
                        swc1(1, sp, 372);
                        swc1(0, sp, 376);
                        v0 = lw(s0, 0);
                        a0 = lw(v0, kResController);
                        jal(0x42C2B8u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 368);
                        sub_s(3, 0, 1);
                        div_s(2, 20, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 20, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        v1 = lb(s2, 2857);
                        v0 = lui(0x4100u);
                        mtc1(v0, 20);  // 8.0
                        s5 = sll(s3, 3);
                        v0 = addu(s5, s2);
                        s3 = addiu(v0, 2232);
                        lwc1(1, s2, 2140);
                        mult(v0, v1, s6);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        sub_s(0, 0, 2);
                        add_s(1, 0, 22);
                        v0 = sll(v1, 1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(116);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(1, 0, 1);
                        v0 = lui(0x4100u);
                        mtc1(v0, 0);  // 8.0
                        sub_s(0, 1, 0);
                        swc1(0, s3, 0);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(22, 0);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = addiu(sp, 256);
                        a1 = lw(v0, kResController);
                        jal(0x42C3C4u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 256);
                        lwc1(1, sp, 260);
                        lwc1(0, sp, 264);
                        swc1(2, sp, 272);
                        swc1(1, sp, 276);
                        swc1(0, sp, 280);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = lw(v0, kResController);
                        jal(0x42C3F0u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 280);
                        sub_s(3, 0, 1);
                        div_s(2, 22, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 22, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(22, 0);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(23, 0);
                        v0 = lw(s0, 0);
                        a0 = addiu(sp, 288);
                        a1 = lw(v0, kResController);
                        jal(0x42C474u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 288);
                        lwc1(1, sp, 292);
                        lwc1(0, sp, 296);
                        swc1(2, sp, 304);
                        swc1(1, sp, 308);
                        swc1(0, sp, 312);
                        v0 = lw(s0, 0);
                        a0 = lw(v0, kResController);
                        jal(0x42C49Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v1 = lui(0x4448u);
                        mtc1(v1, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v1 = lui(0x43C8u);
                        mtc1(v1, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 312);
                        sub_s(3, 0, 1);
                        div_s(2, 23, 2);
                        v1 = lui(0x4000u);
                        mtc1(v1, 0);  // 2.0
                        div_s(1, 23, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        a0 = lb(s2, 2857);
                        v1 = addu(s5, s2);
                        s0 = addiu(v1, 2236);
                        lwc1(1, s2, 2144);
                        mult(v1, a0, s7);
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        sub_s(0, 0, 2);
                        add_s(1, 0, 22);
                        v1 = sll(a0, 1);
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v1 = sra(a0, 1);
                        if (ltz(a0)) {
                            charge(2);
                            v1 = addiu(a0, 1);
                            v1 = sra(v1, 1);
                        }
                        charge(11);
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(1, 0, 1);
                        v1 = lui(0x4100u);
                        mtc1(v1, 0);  // 8.0
                        sub_s(0, 1, 0);
                        swc1(0, s0, 0);
                    } else {
                        charge(110);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        a0 = addiu(sp, 208);
                        lwc1(2, s2, 2152);
                        lwc1(1, s2, 2156);
                        lwc1(0, s2, 2160);
                        swc1(2, sp, 208);
                        swc1(1, sp, 212);
                        swc1(0, sp, 216);
                        jal(0x42C5B0u, &gen::fn_sub_44F120_0044f120);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 208);
                        sub_s(3, 0, 1);
                        v0 = lui(0x4000u);
                        mtc1(v0, 21);  // 2.0
                        div_s(2, 20, 2);
                        div_s(1, 20, 21);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(22, 0);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        s3 = dsll32(s4, 24);
                        s3 = dsra32(s3, 24);
                        v0 = sll(s3, 3);
                        v0 = subu(v0, s3);
                        v1 = sll(v0, 6);
                        v0 = lui(0x87u);
                        v0 = addiu(v0, 6132);  // 0x8717F4
                        s0 = addu(v0, v1);
                        v0 = lw(s0, 0);
                        a0 = addiu(sp, 224);
                        a1 = lw(v0, kResController);
                        jal(0x42C654u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 224);
                        lwc1(1, sp, 228);
                        lwc1(0, sp, 232);
                        swc1(2, sp, 240);
                        swc1(1, sp, 244);
                        swc1(0, sp, 248);
                        v0 = lw(s0, 0);
                        a0 = lw(v0, kResController);
                        jal(0x42C67Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 240);
                        sub_s(3, 0, 1);
                        div_s(2, 20, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 20, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        v1 = lb(s2, 2857);
                        v0 = lui(0x4100u);
                        mtc1(v0, 20);  // 8.0
                        s5 = sll(s3, 3);
                        v0 = addu(s5, s2);
                        s3 = addiu(v0, 2232);
                        lwc1(1, s2, 2140);
                        mult(v0, v1, s6);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        sub_s(0, 0, 2);
                        add_s(1, 0, 22);
                        v0 = sll(v1, 1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(108);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(1, 0, 1);
                        v0 = lui(0x4100u);
                        mtc1(v0, 0);  // 8.0
                        sub_s(0, 1, 0);
                        swc1(0, s3, 0);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(22, 0);
                        a0 = addiu(sp, 160);
                        lwc1(2, s2, 2152);
                        lwc1(1, s2, 2156);
                        lwc1(0, s2, 2160);
                        swc1(2, sp, 160);
                        swc1(1, sp, 164);
                        swc1(0, sp, 168);
                        jal(0x42C794u, &gen::fn_sub_44F170_0044f170);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 168);
                        sub_s(3, 0, 1);
                        div_s(2, 22, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 22, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(22, 0);
                        v0 = lb(s2, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(23, 0);
                        v0 = lw(s0, 0);
                        a0 = addiu(sp, 176);
                        a1 = lw(v0, kResController);
                        jal(0x42C818u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 176);
                        lwc1(1, sp, 180);
                        lwc1(0, sp, 184);
                        swc1(2, sp, 192);
                        swc1(1, sp, 196);
                        swc1(0, sp, 200);
                        v0 = lw(s0, 0);
                        a0 = lw(v0, kResController);
                        jal(0x42C840u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v1 = lui(0x4448u);
                        mtc1(v1, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v1 = lui(0x43C8u);
                        mtc1(v1, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 200);
                        sub_s(3, 0, 1);
                        div_s(2, 23, 2);
                        v1 = lui(0x4000u);
                        mtc1(v1, 0);  // 2.0
                        div_s(1, 23, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        a0 = lb(s2, 2857);
                        v1 = addu(s5, s2);
                        s0 = addiu(v1, 2236);
                        lwc1(1, s2, 2144);
                        mult(v1, a0, s7);
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        sub_s(0, 0, 2);
                        add_s(1, 0, 22);
                        v1 = sll(a0, 1);
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v1 = sra(a0, 1);
                        if (ltz(a0)) {
                            charge(2);
                            v1 = addiu(a0, 1);
                            v1 = sra(v1, 1);
                        }
                        charge(9);
                        mtc1(v1, 0);
                        cvt_s_w(0, 0);
                        add_s(1, 0, 1);
                        v1 = lui(0x4100u);
                        mtc1(v1, 0);  // 8.0
                        sub_s(0, 1, 0);
                        swc1(0, s0, 0);
                    }
                    charge(6);
                    lwc1(6, s3, 0);
                    lwc1(1, s2, 2140);
                    add_s(0, 20, 6);
                    c_lt_s(1, 0);
                    if (cond()) {
                        charge(6);
                        lwc1(5, s0, 0);
                        lwc1(4, s2, 2144);
                        add_s(0, 20, 5);
                        c_lt_s(4, 0);
                        if (cond()) {
                            charge(11);
                            v1 = lui(0x42FCu);
                            mtc1(v1, 3);  // 126.0
                            add_s(1, 3, 1);
                            v1 = lui(0x4140u);
                            mtc1(v1, 2);  // 12.0
                            add_s(0, 2, 6);
                            c_le_s(1, 0);
                            if (!cond()) {
                                charge(5);
                                add_s(1, 3, 4);
                                add_s(0, 2, 5);
                                c_le_s(1, 0);
                                if (!cond()) {
                                    charge(14);
                                    v0 = dsll32(s4, 24);
                                    v0 = dsra32(v0, 24);
                                    v1 = si(1);
                                    v0 = addu(v0, s2);
                                    sb(v0, 2359, v1);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, 6472);  // 0x871948
                                    s1 = addu(v0, s1);
                                    a0 = lh(s1, 0);
                                    jal(0x42C9B4u, &gen::fn_sub_16C970_0016c970);
                                    v0 = v0 & 0x80u;
                                    if (v0 != 0) {
                                        charge(29);
                                        v0 = dsll32(s4, 24);
                                        v0 = dsra32(v0, 24);
                                        v0 = sll(v0, 1);
                                        v0 = addu(v0, s2);
                                        s0 = addiu(v0, 2352);
                                        v0 = lh(v0, 2352);
                                        mtc1(v0, 0);
                                        cvt_s_w(1, 0);
                                        lwc1(0, gp, -31676);
                                        mul_s(12, 0, 1);
                                        jal(0x42C9F4u, &gen::fn_sinf_0052e878);
                                        v0 = lui(0xC300u);
                                        mtc1(v0, 3);  // -128.0
                                        v0 = lui(0x4300u);
                                        mtc1(v0, 2);  // 128.0
                                        mtc1(zero, 1);
                                        adda_s(1, 2);
                                        madd_s(20, 3, 0);
                                        v0 = lh(s0, 0);
                                        v0 = addiu(v0, 1);
                                        sh(s0, 0, v0);
                                        v0 = dsll32(v0, 16);
                                        v0 = dsra32(v0, 16);
                                        at = slti(v0, 41);
                                        if (at == 0) {
                                            charge(1);
                                            sh(s0, 0, zero);
                                        }
                                        charge(27);
                                        a0 = 0;
                                        a1 = lw(gp, kGpSmapSprite);
                                        a2 = si(10);
                                        jal(0x42CA4Cu, &gen::fn_sprCreateHandle_001158b0);
                                        s3 = v0;
                                        v1 = lui(0x4040u);
                                        mtc1(v1, 1);  // 3.0
                                        sw(v0, 44, v1);
                                        v1 = dsll32(s4, 24);
                                        v1 = dsra32(v1, 24);
                                        v1 = sll(v1, 3);
                                        v1 = addu(v1, s2);
                                        s1 = addiu(v1, 2232);
                                        lwc1(0, v1, 2232);
                                        add_s(0, 1, 0);
                                        swc1(0, v0, 16);
                                        s0 = addiu(v1, 2236);
                                        lwc1(0, v1, 2236);
                                        add_s(0, 1, 0);
                                        swc1(0, v0, 20);
                                        v0 = lui(0x4F00u);
                                        mtc1(v0, 0);  // 2^31
                                        c_le_s(0, 20);
                                        if (!cond()) {
                                            charge(6);
                                            cvt_w_s(0, 20);
                                            mfc1(v1, 0);
                                            v1 = v1 & 0xFFu;
                                        } else {
                                            charge(6);
                                            sub_s(0, 20, 0);
                                            cvt_w_s(0, 0);
                                            mfc1(v1, 0);
                                            v0 = lui(0x8000u);
                                            v1 = v1 | v0;
                                            v1 = v1 & 0xFFu;
                                        }
                                        charge(29);
                                        sb(s3, 24, v1);
                                        a0 = s3;
                                        a1 = si(1);
                                        jal(0x42CAE8u, &gen::fn_sub_1127D0_001127d0);
                                        a0 = s3;
                                        jal(0x42CAF4u, &gen::fn_sub_115980_00115980);
                                        a0 = 0;
                                        a1 = lw(gp, kGpSmapSprite);
                                        a2 = si(8);
                                        jal(0x42CB08u, &gen::fn_sprCreateHandle_001158b0);
                                        s2 = v0;
                                        swc1(21, v0, 44);
                                        lwc1(0, s1, 0);
                                        swc1(0, v0, 16);
                                        lwc1(0, s0, 0);
                                        swc1(0, v0, 20);
                                        sb(v0, 24, zero);
                                        a0 = s2;
                                        a1 = si(1);
                                        jal(0x42CB34u, &gen::fn_sub_1127D0_001127d0);
                                        a0 = s2;
                                        jal(0x42CB40u, &gen::fn_sub_115980_00115980);
                                    } else {
                                        charge(7);
                                        a0 = lh(s1, 0);
                                        jal(0x42CB54u, &gen::fn_sub_16C970_0016c970);
                                        v1 = lui(0x8u);
                                        v0 = v0 & v1;
                                        if (v0 != 0) {
                                            charge(29);
                                            v0 = dsll32(s4, 24);
                                            v0 = dsra32(v0, 24);
                                            v0 = sll(v0, 1);
                                            v0 = addu(v0, s2);
                                            s0 = addiu(v0, 2352);
                                            v0 = lh(v0, 2352);
                                            mtc1(v0, 0);
                                            cvt_s_w(1, 0);
                                            lwc1(0, gp, -31676);
                                            mul_s(12, 0, 1);
                                            jal(0x42CB98u, &gen::fn_sinf_0052e878);
                                            v0 = lui(0xC300u);
                                            mtc1(v0, 3);  // -128.0
                                            v0 = lui(0x4300u);
                                            mtc1(v0, 2);  // 128.0
                                            mtc1(zero, 1);
                                            adda_s(1, 2);
                                            madd_s(20, 3, 0);
                                            v0 = lh(s0, 0);
                                            v0 = addiu(v0, 1);
                                            sh(s0, 0, v0);
                                            v0 = dsll32(v0, 16);
                                            v0 = dsra32(v0, 16);
                                            at = slti(v0, 41);
                                            if (at == 0) {
                                                charge(1);
                                                sh(s0, 0, zero);
                                            }
                                            charge(27);
                                            a0 = 0;
                                            a1 = lw(gp, kGpSmapSprite);
                                            a2 = si(10);
                                            jal(0x42CBF0u, &gen::fn_sprCreateHandle_001158b0);
                                            s3 = v0;
                                            v1 = lui(0x4040u);
                                            mtc1(v1, 1);  // 3.0
                                            sw(v0, 44, v1);
                                            v1 = dsll32(s4, 24);
                                            v1 = dsra32(v1, 24);
                                            v1 = sll(v1, 3);
                                            v1 = addu(v1, s2);
                                            s1 = addiu(v1, 2232);
                                            lwc1(0, v1, 2232);
                                            add_s(0, 1, 0);
                                            swc1(0, v0, 16);
                                            s0 = addiu(v1, 2236);
                                            lwc1(0, v1, 2236);
                                            add_s(0, 1, 0);
                                            swc1(0, v0, 20);
                                            v0 = lui(0x4F00u);
                                            mtc1(v0, 0);  // 2^31
                                            c_le_s(0, 20);
                                            if (!cond()) {
                                                charge(6);
                                                cvt_w_s(0, 20);
                                                mfc1(v1, 0);
                                                v1 = v1 & 0xFFu;
                                            } else {
                                                charge(6);
                                                sub_s(0, 20, 0);
                                                cvt_w_s(0, 0);
                                                mfc1(v1, 0);
                                                v0 = lui(0x8000u);
                                                v1 = v1 | v0;
                                                v1 = v1 & 0xFFu;
                                            }
                                            charge(29);
                                            sb(s3, 24, v1);
                                            a0 = s3;
                                            a1 = si(1);
                                            jal(0x42CC8Cu, &gen::fn_sub_1127D0_001127d0);
                                            a0 = s3;
                                            jal(0x42CC98u, &gen::fn_sub_115980_00115980);
                                            a0 = 0;
                                            a1 = lw(gp, kGpSmapSprite);
                                            a2 = si(9);
                                            jal(0x42CCACu, &gen::fn_sprCreateHandle_001158b0);
                                            s2 = v0;
                                            swc1(21, v0, 44);
                                            lwc1(0, s1, 0);
                                            swc1(0, v0, 16);
                                            lwc1(0, s0, 0);
                                            swc1(0, v0, 20);
                                            sb(v0, 24, zero);
                                            a0 = s2;
                                            a1 = si(1);
                                            jal(0x42CCD8u, &gen::fn_sub_1127D0_001127d0);
                                            a0 = s2;
                                            jal(0x42CCE4u, &gen::fn_sub_115980_00115980);
                                        } else {
                                            charge(19);
                                            a0 = 0;
                                            a1 = lw(gp, kGpSmapSprite);
                                            a2 = si(7);
                                            jal(0x42CD00u, &gen::fn_sprCreateHandle_001158b0);
                                            s1 = v0;
                                            swc1(21, v0, 44);
                                            lwc1(0, s3, 0);
                                            swc1(0, v0, 16);
                                            lwc1(0, s0, 0);
                                            swc1(0, v0, 20);
                                            sb(v0, 24, zero);
                                            a0 = s1;
                                            a1 = si(1);
                                            jal(0x42CD2Cu, &gen::fn_sub_1127D0_001127d0);
                                            a0 = s1;
                                            jal(0x42CD38u, &gen::fn_sub_115980_00115980);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        charge(16);
        ra = ld(sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(23, sp, 12);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 384);
    }

    // 0x42CD80: for party members i = 0..2 with +2360 + i == 1 and sub_43A230(i + 1) == 1, their five sparkles j = 5 i ..
    // 5 i + 4: sub_430780(the f32 pair +2240 + 8 i read unaligned, x = s8 +2294 + 2 j, y = s8 +2324 + 2 j, frame = s8 +2264
    // + j, $f12 = 8.0), then the sparkle's delay +2279 + j: above 0 it counts down; else the frame counts up and at 21 the
    // jitters +2294 / +2324 are re-rolled (8 - (RpRandom() & 15)), the frame = 0 and the delay = 4. The jitter pointer is kept
    // in a quadword at sp+160 (sq / lq of $v0) across the calls.
    void sub_42CD80() {
        enter(15);
        sp = addiu(sp, -176);
        sd(sp, 144, ra);
        sq(fp, sp, 128);
        sq(s7, sp, 112);
        sq(s6, sp, 96);
        sq(s5, sp, 80);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s3 = lw(a0, kTaskWork);
        s5 = 0;
        for (;;) {
            charge(3);
            v1 = slti(s5, 3);
            if (v1 == 0) break;
            backedge();
            charge(5);
            v1 = addu(s3, s5);
            a0 = lb(v1, 2360);
            v1 = si(1);
            if (a0 == v1) {
                charge(8);
                v0 = addiu(s5, 1);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                jal(0x42CDDCu, &gen::fn_sub_43A230_0043a230);
                v1 = si(1);
                if (v0 == v1) {
                    charge(9);
                    v1 = sll(s5, 2);
                    s4 = addu(v1, s5);
                    v1 = sll(s5, 3);
                    s2 = addu(s3, v1);
                    a0 = addiu(s5, 1);
                    v1 = sll(a0, 2);
                    s6 = addu(v1, a0);
                    for (;;) {
                        charge(3);
                        v1 = slt(s4, s6);
                        if (v1 == 0) break;
                        backedge();
                        charge(20);
                        s1 = addu(s3, s4);
                        s7 = addiu(s1, 2264);
                        v0 = sll(s4, 1);
                        v1 = addu(s3, v0);
                        fp = addiu(v1, 2324);
                        v0 = addiu(v1, 2294);
                        sq(v0, sp, 160);
                        v0 = lui(0x4100u);
                        mtc1(v0, 12);  // 8.0
                        a1 = lb(v1, 2294);
                        a2 = lb(v1, 2324);
                        a3 = lb(s1, 2264);
                        ldr(a0, s2, 2240);
                        ldl(a0, s2, 2247);
                        jal(0x42CE4Cu, &gen::fn_sub_430780_00430780);
                        s0 = addiu(s1, 2279);
                        v1 = lb(s1, 2279);
                        if (lez(v1)) {
                            charge(9);
                            a0 = s1;
                            v1 = lb(a0, 2264);
                            v1 = addiu(v1, 1);
                            sb(a0, 2264, v1);
                            v1 = dsll32(v1, 24);
                            v1 = dsra32(v1, 24);
                            at = slti(v1, 21);
                            if (at == 0) {
                                charge(5);
                                jal(0x42CE88u, &gen::fn_sub_488F30_00488f30);
                                v0 = v0 & 0xFu;
                                if (gez(v0)) {
                                    charge(5);
                                    mtc1(v0, 0);
                                    cvt_s_w(1, 0);
                                } else {
                                    charge(7);
                                    v1 = srl(v0, 1);
                                    v0 = v0 & 0x1u;
                                    v1 = v1 | v0;
                                    mtc1(v1, 0);
                                    cvt_s_w(1, 0);
                                    add_s(1, 1, 1);
                                }
                                charge(13);
                                v0 = lui(0x4100u);
                                mtc1(v0, 0);  // 8.0
                                sub_s(0, 0, 1);
                                cvt_w_s(0, 0);
                                mfc1(v1, 0);
                                lq(v0, sp, 160);
                                sh(v0, 0, v1);
                                jal(0x42CEECu, &gen::fn_sub_488F30_00488f30);
                                v1 = v0 & 0xFu;
                                if (gez(v1)) {
                                    charge(5);
                                    mtc1(v1, 0);
                                    cvt_s_w(1, 0);
                                } else {
                                    charge(7);
                                    a0 = srl(v1, 1);
                                    v1 = v1 & 0x1u;
                                    a0 = a0 | v1;
                                    mtc1(a0, 0);
                                    cvt_s_w(1, 0);
                                    add_s(1, 1, 1);
                                }
                                charge(13);
                                v1 = lui(0x4100u);
                                mtc1(v1, 0);  // 8.0
                                sub_s(0, 0, 1);
                                cvt_w_s(0, 0);
                                mfc1(v1, 0);
                                sh(fp, 0, v1);
                                sb(s7, 0, zero);
                                v1 = si(4);
                                sb(s0, 0, v1);
                            }
                        } else {
                            charge(2);
                            v1 = addiu(v1, -1);
                            sb(s0, 0, v1);
                        }
                        charge(1);
                        s4 = addiu(s4, 1);
                    }
                }
            }
            charge(1);
            s5 = addiu(s5, 1);
        }
        charge(13);
        ra = ld(sp, 144);
        lq(fp, sp, 128);
        lq(s7, sp, 112);
        lq(s6, sp, 96);
        lq(s5, sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 176);
    }
};

struct SMapObjects : SMapMarks {
    using SMapMarks::SMapMarks;

    // 0x42CFC0 (task, x, z, ox, oz): every used shadow gFldUnitsEc[i] (+72 and +84 set) standing on cell (x, z) (the s16 x / z
    // are kept in quadwords at sp+192 / sp+176 across the calls) gets its mark position at work +2364 + 8 i / +2368 + 8 i,
    // per axis corner + size * o - its cell offset + the player's (or the frozen centre's) cell offset - 2 size + size / 2
    // - 8 (size = the s8 at +2857). When sub_1C7160 (the units within reach) says it touches the player (gFldUnitsPc[0]):
    // sprite 11 at the mark with scale 2.0, alpha 0 -- or, when the unit's +396 is 4, alpha 100 - 100 sin(phase *
    // gp[-31676]) with the s16 phase +2556 counting 0..20. Otherwise, while it still has a scene resource, the mark is
    // recomputed as corner + the player's offset - its offset + size / 4 + 2 - 2 size (both axes) and the byte 0x95C210 + i
    // is cleared.
    void sub_42CFC0() {
        enter(25);
        sp = addiu(sp, -560);
        sd(sp, 160, ra);
        sq(fp, sp, 144);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s7 = a3;
        fp = a4;
        s1 = lw(a0, kTaskWork);
        s4 = 0;
        v1 = dsll32(a1, 16);
        v1 = dsra32(v1, 16);
        sq(v1, sp, 192);
        v1 = dsll32(a2, 16);
        v1 = dsra32(v1, 16);
        sq(v1, sp, 176);
        for (;;) {
            charge(3);
            v1 = slti(s4, 24);
            if (v1 == 0) break;
            backedge();
            charge(10);
            a1 = 0;
            v1 = sll(s4, 3);
            v1 = subu(v1, s4);
            a0 = sll(v1, 6);
            v1 = lui(0x87u);
            v1 = addiu(v1, -4704);  // 0x86EDA0 gFldUnitsEc
            s3 = addu(v1, a0);
            v1 = lw(s3, 72);
            if (v1 != 0) {
                charge(3);
                v1 = lw(s3, 84);
                if (v1 != 0) {
                    charge(1);
                    a1 = si(1);
                }
            }
            charge(4);
            a0 = sltu(zero, a1);
            v1 = si(1);
            if (a0 == v1) {
                charge(8);
                s6 = addiu(s3, 84);
                v0 = lw(s3, 84);
                a0 = lw(v0, kResController);
                jal(0x42D078u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                lq(v1, sp, 192);
                if (v1 == v0) {
                    charge(7);
                    v0 = lw(s6, 0);
                    a0 = lw(v0, kResController);
                    jal(0x42D094u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    lq(v1, sp, 176);
                    if (v1 == v0) {
                        charge(3);
                        v0 = lb(s1, 2149);
                        if (v0 == 0) {
                            charge(115);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 496);
                            a1 = lw(v0, kResController);
                            jal(0x42D0D4u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 496);
                            lwc1(1, sp, 500);
                            lwc1(0, sp, 504);
                            swc1(2, sp, 512);
                            swc1(1, sp, 516);
                            swc1(0, sp, 520);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = lw(v0, kResController);
                            jal(0x42D100u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 512);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v1 = dsll32(s4, 24);
                            v1 = dsra32(v1, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                            v0 = addu(v0, v1);
                            s0 = addiu(v0, 84);
                            v0 = lw(v0, 84);
                            a0 = addiu(sp, 528);
                            a1 = lw(v0, kResController);
                            jal(0x42D1A8u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 528);
                            lwc1(1, sp, 532);
                            lwc1(0, sp, 536);
                            swc1(2, sp, 544);
                            swc1(1, sp, 548);
                            swc1(0, sp, 552);
                            v0 = lw(s0, 0);
                            a0 = lw(v0, kResController);
                            jal(0x42D1D0u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 544);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            v1 = lb(s1, 2857);
                            v0 = sll(s4, 3);
                            s5 = addu(s1, v0);
                            s2 = addiu(s5, 2364);
                            lwc1(1, s1, 2140);
                            mult(v0, v1, s7);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(113);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x4100u);
                            mtc1(v0, 0);  // 8.0
                            sub_s(0, 1, 0);
                            swc1(0, s2, 0);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 432);
                            a1 = lw(v0, kResController);
                            jal(0x42D2CCu, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 432);
                            lwc1(1, sp, 436);
                            lwc1(0, sp, 440);
                            swc1(2, sp, 448);
                            swc1(1, sp, 452);
                            swc1(0, sp, 456);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = lw(v0, kResController);
                            jal(0x42D2F8u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 456);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v0 = lw(s0, 0);
                            a0 = addiu(sp, 464);
                            a1 = lw(v0, kResController);
                            jal(0x42D37Cu, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 464);
                            lwc1(1, sp, 468);
                            lwc1(0, sp, 472);
                            swc1(2, sp, 480);
                            swc1(1, sp, 484);
                            swc1(0, sp, 488);
                            v0 = lw(s0, 0);
                            a0 = lw(v0, kResController);
                            jal(0x42D3A4u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 488);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            v1 = lb(s1, 2857);
                            s0 = addiu(s5, 2368);
                            lwc1(1, s1, 2144);
                            mult(v0, v1, fp);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(11);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x4100u);
                            mtc1(v0, 0);  // 8.0
                            sub_s(0, 1, 0);
                            swc1(0, s0, 0);
                        } else {
                            charge(107);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            a0 = addiu(sp, 384);
                            lwc1(2, s1, 2152);
                            lwc1(1, s1, 2156);
                            lwc1(0, s1, 2160);
                            swc1(2, sp, 384);
                            swc1(1, sp, 388);
                            swc1(0, sp, 392);
                            jal(0x42D4ACu, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 384);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v1 = dsll32(s4, 24);
                            v1 = dsra32(v1, 24);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                            v0 = addu(v0, v1);
                            s0 = addiu(v0, 84);
                            v0 = lw(v0, 84);
                            a0 = addiu(sp, 400);
                            a1 = lw(v0, kResController);
                            jal(0x42D554u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 400);
                            lwc1(1, sp, 404);
                            lwc1(0, sp, 408);
                            swc1(2, sp, 416);
                            swc1(1, sp, 420);
                            swc1(0, sp, 424);
                            v0 = lw(s0, 0);
                            a0 = lw(v0, kResController);
                            jal(0x42D57Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 416);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            v1 = lb(s1, 2857);
                            v0 = sll(s4, 3);
                            s5 = addu(s1, v0);
                            s2 = addiu(s5, 2364);
                            lwc1(1, s1, 2140);
                            mult(v0, v1, s7);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(105);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x4100u);
                            mtc1(v0, 0);  // 8.0
                            sub_s(0, 1, 0);
                            swc1(0, s2, 0);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            a0 = addiu(sp, 336);
                            lwc1(2, s1, 2152);
                            lwc1(1, s1, 2156);
                            lwc1(0, s1, 2160);
                            swc1(2, sp, 336);
                            swc1(1, sp, 340);
                            swc1(0, sp, 344);
                            jal(0x42D684u, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 344);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s1, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v0 = lw(s0, 0);
                            a0 = addiu(sp, 352);
                            a1 = lw(v0, kResController);
                            jal(0x42D708u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 352);
                            lwc1(1, sp, 356);
                            lwc1(0, sp, 360);
                            swc1(2, sp, 368);
                            swc1(1, sp, 372);
                            swc1(0, sp, 376);
                            v0 = lw(s0, 0);
                            a0 = lw(v0, kResController);
                            jal(0x42D730u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 376);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            v1 = lb(s1, 2857);
                            s0 = addiu(s5, 2368);
                            lwc1(1, s1, 2144);
                            mult(v0, v1, fp);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(9);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x4100u);
                            mtc1(v0, 0);  // 8.0
                            sub_s(0, 1, 0);
                            swc1(0, s0, 0);
                        }
                        charge(10);
                        v0 = lui(0x44FAu);
                        mtc1(v0, 12);  // 2000f
                        a0 = s3;
                        a1 = lui(0x87u);
                        a1 = addiu(a1, 6048);  // 0x8717A0 gFldUnitsPc
                        jal(0x42D818u, &gen::fn_sub_1C7160_001c7160);
                        v1 = si(1);
                        if (v0 == v1) {
                            charge(4);
                            v1 = lw(s3, 396);
                            v0 = si(4);
                            if (v1 == v0) {
                                charge(24);
                                v0 = lh(s1, 2556);
                                mtc1(v0, 0);
                                cvt_s_w(1, 0);
                                lwc1(0, gp, -31672);
                                mul_s(12, 0, 1);
                                jal(0x42D854u, &gen::fn_sinf_0052e878);
                                v0 = lui(0xC2C8u);
                                mtc1(v0, 3);  // -100f
                                v0 = lui(0x42C8u);
                                mtc1(v0, 2);  // 100.0
                                mtc1(zero, 1);
                                adda_s(1, 2);
                                madd_s(20, 3, 0);
                                v0 = lh(s1, 2556);
                                v0 = addiu(v0, 1);
                                sh(s1, 2556, v0);
                                v0 = dsll32(v0, 16);
                                v0 = dsra32(v0, 16);
                                at = slti(v0, 21);
                                if (at == 0) {
                                    charge(1);
                                    sh(s1, 2556, zero);
                                }
                                charge(18);
                                a0 = 0;
                                a1 = lw(gp, kGpSmapSprite);
                                a2 = si(11);
                                jal(0x42D8ACu, &gen::fn_sprCreateHandle_001158b0);
                                s3 = v0;
                                v1 = lui(0x4000u);
                                sw(v0, 44, v1);
                                lwc1(0, s2, 0);
                                swc1(0, v0, 16);
                                lwc1(0, s0, 0);
                                swc1(0, v0, 20);
                                v0 = lui(0x4F00u);
                                mtc1(v0, 0);  // 2^31
                                c_le_s(0, 20);
                                if (!cond()) {
                                    charge(6);
                                    cvt_w_s(0, 20);
                                    mfc1(v1, 0);
                                    v1 = v1 & 0xFFu;
                                } else {
                                    charge(6);
                                    sub_s(0, 20, 0);
                                    cvt_w_s(0, 0);
                                    mfc1(v1, 0);
                                    v0 = lui(0x8000u);
                                    v1 = v1 | v0;
                                    v1 = v1 & 0xFFu;
                                }
                                charge(10);
                                sb(s3, 24, v1);
                                a0 = s3;
                                a1 = si(1);
                                jal(0x42D924u, &gen::fn_sub_1127D0_001127d0);
                                a0 = s3;
                                jal(0x42D930u, &gen::fn_sub_115980_00115980);
                            } else {
                                charge(22);
                                a0 = 0;
                                a1 = lw(gp, kGpSmapSprite);
                                a2 = si(11);
                                jal(0x42D94Cu, &gen::fn_sprCreateHandle_001158b0);
                                s3 = v0;
                                v1 = lui(0x4000u);
                                sw(v0, 44, v1);
                                lwc1(0, s2, 0);
                                swc1(0, v0, 16);
                                lwc1(0, s0, 0);
                                swc1(0, v0, 20);
                                sb(v0, 24, zero);
                                a0 = s3;
                                a1 = si(1);
                                jal(0x42D97Cu, &gen::fn_sub_1127D0_001127d0);
                                a0 = s3;
                                jal(0x42D988u, &gen::fn_sub_115980_00115980);
                            }
                        } else {
                            charge(3);
                            v1 = lw(s6, 0);
                            if (v1 != 0) {
                                charge(102);
                                v0 = lb(s1, 2857);
                                mtc1(v0, 0);
                                cvt_s_w(20, 0);
                                v1 = dsll32(s4, 24);
                                v1 = dsra32(v1, 24);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = lui(0x87u);
                                v0 = addiu(v0, -4704);  // 0x86EDA0 gFldUnitsEc
                                v0 = addu(v0, v1);
                                s3 = addiu(v0, 84);
                                v0 = lw(v0, 84);
                                a0 = addiu(sp, 272);
                                a1 = lw(v0, kResController);
                                jal(0x42D9E4u, &gen::fn_sub_1AD940_001ad940);
                                lwc1(2, sp, 272);
                                lwc1(1, sp, 276);
                                lwc1(0, sp, 280);
                                swc1(2, sp, 288);
                                swc1(1, sp, 292);
                                swc1(0, sp, 296);
                                v0 = lw(s3, 0);
                                a0 = lw(v0, kResController);
                                jal(0x42DA0Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                mtc1(v0, 0);
                                cvt_s_w(0, 0);
                                v0 = lui(0x4448u);
                                mtc1(v0, 2);  // 800.0
                                mul_s(1, 2, 0);
                                v0 = lui(0x43C8u);
                                mtc1(v0, 0);  // 400.0
                                sub_s(1, 1, 0);
                                lwc1(0, sp, 288);
                                sub_s(3, 0, 1);
                                div_s(2, 20, 2);
                                v0 = lui(0x4000u);
                                mtc1(v0, 0);  // 2.0
                                div_s(1, 20, 0);
                                mtc1(zero, 0);
                                adda_s(0, 1);
                                msub_s(20, 3, 2);
                                v0 = lb(s1, 2857);
                                mtc1(v0, 0);
                                cvt_s_w(21, 0);
                                v0 = lui(0x87u);
                                v0 = lw(v0, 6132);  // 0x8717F4
                                a0 = addiu(sp, 304);
                                a1 = lw(v0, kResController);
                                jal(0x42DA8Cu, &gen::fn_sub_1AD940_001ad940);
                                lwc1(2, sp, 304);
                                lwc1(1, sp, 308);
                                lwc1(0, sp, 312);
                                swc1(2, sp, 320);
                                swc1(1, sp, 324);
                                swc1(0, sp, 328);
                                v0 = lui(0x87u);
                                v0 = lw(v0, 6132);  // 0x8717F4
                                a0 = lw(v0, kResController);
                                jal(0x42DAB8u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                mtc1(v0, 0);
                                cvt_s_w(0, 0);
                                v0 = lui(0x4448u);
                                mtc1(v0, 2);  // 800.0
                                mul_s(1, 2, 0);
                                v0 = lui(0x43C8u);
                                mtc1(v0, 0);  // 400.0
                                sub_s(1, 1, 0);
                                lwc1(0, sp, 320);
                                sub_s(3, 0, 1);
                                div_s(2, 21, 2);
                                v0 = lui(0x4000u);
                                mtc1(v0, 0);  // 2.0
                                div_s(1, 21, 0);
                                mtc1(zero, 0);
                                adda_s(0, 1);
                                msub_s(0, 3, 2);
                                cvt_w_s(0, 0);
                                cvt_s_w(1, 0);
                                v1 = lb(s1, 2857);
                                lwc1(0, s1, 2140);
                                add_s(0, 0, 1);
                                sub_s(1, 0, 20);
                                v0 = sra(v1, 2);
                                if (ltz(v1)) {
                                    charge(2);
                                    v0 = addiu(v1, 3);
                                    v0 = sra(v0, 2);
                                }
                                charge(107);
                                mtc1(v0, 0);
                                cvt_s_w(0, 0);
                                add_s(1, 0, 1);
                                v0 = lui(0x4000u);
                                mtc1(v0, 0);  // 2.0
                                add_s(1, 0, 1);
                                v0 = sll(v1, 1);
                                mtc1(v0, 0);
                                cvt_s_w(0, 0);
                                sub_s(0, 1, 0);
                                swc1(0, s2, 0);
                                v0 = lb(s1, 2857);
                                mtc1(v0, 0);
                                cvt_s_w(20, 0);
                                v0 = lw(s3, 0);
                                a0 = addiu(sp, 208);
                                a1 = lw(v0, kResController);
                                jal(0x42DB98u, &gen::fn_sub_1AD940_001ad940);
                                lwc1(2, sp, 208);
                                lwc1(1, sp, 212);
                                lwc1(0, sp, 216);
                                swc1(2, sp, 224);
                                swc1(1, sp, 228);
                                swc1(0, sp, 232);
                                v0 = lw(s3, 0);
                                a0 = lw(v0, kResController);
                                jal(0x42DBC0u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                mtc1(v0, 0);
                                cvt_s_w(0, 0);
                                v0 = lui(0x4448u);
                                mtc1(v0, 2);  // 800.0
                                mul_s(1, 2, 0);
                                v0 = lui(0x43C8u);
                                mtc1(v0, 0);  // 400.0
                                sub_s(1, 1, 0);
                                lwc1(0, sp, 232);
                                sub_s(3, 0, 1);
                                div_s(2, 20, 2);
                                v0 = lui(0x4000u);
                                mtc1(v0, 0);  // 2.0
                                div_s(1, 20, 0);
                                mtc1(zero, 0);
                                adda_s(0, 1);
                                msub_s(20, 3, 2);
                                v0 = lb(s1, 2857);
                                mtc1(v0, 0);
                                cvt_s_w(21, 0);
                                v0 = lui(0x87u);
                                v0 = lw(v0, 6132);  // 0x8717F4
                                a0 = addiu(sp, 240);
                                a1 = lw(v0, kResController);
                                jal(0x42DC40u, &gen::fn_sub_1AD940_001ad940);
                                lwc1(2, sp, 240);
                                lwc1(1, sp, 244);
                                lwc1(0, sp, 248);
                                swc1(2, sp, 256);
                                swc1(1, sp, 260);
                                swc1(0, sp, 264);
                                v0 = lui(0x87u);
                                v0 = lw(v0, 6132);  // 0x8717F4
                                a0 = lw(v0, kResController);
                                jal(0x42DC6Cu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                mtc1(v0, 0);
                                cvt_s_w(0, 0);
                                v1 = lui(0x4448u);
                                mtc1(v1, 2);  // 800.0
                                mul_s(1, 2, 0);
                                v1 = lui(0x43C8u);
                                mtc1(v1, 0);  // 400.0
                                sub_s(1, 1, 0);
                                lwc1(0, sp, 264);
                                sub_s(3, 0, 1);
                                div_s(2, 21, 2);
                                v1 = lui(0x4000u);
                                mtc1(v1, 0);  // 2.0
                                div_s(1, 21, 0);
                                mtc1(zero, 0);
                                adda_s(0, 1);
                                msub_s(0, 3, 2);
                                cvt_w_s(0, 0);
                                cvt_s_w(1, 0);
                                a0 = lb(s1, 2857);
                                lwc1(0, s1, 2144);
                                add_s(0, 0, 1);
                                sub_s(1, 0, 20);
                                v1 = sra(a0, 2);
                                if (ltz(a0)) {
                                    charge(2);
                                    v1 = addiu(a0, 3);
                                    v1 = sra(v1, 2);
                                }
                                charge(18);
                                mtc1(v1, 0);
                                cvt_s_w(0, 0);
                                add_s(1, 0, 1);
                                v1 = lui(0x4000u);
                                mtc1(v1, 0);  // 2.0
                                add_s(1, 0, 1);
                                v1 = sll(a0, 1);
                                mtc1(v1, 0);
                                cvt_s_w(0, 0);
                                sub_s(0, 1, 0);
                                swc1(0, s0, 0);
                                v1 = lui(0x96u);
                                v1 = addiu(v1, -15856);  // 0x95C210
                                v1 = addu(v1, s4);
                                sb(v1, 0, zero);
                            }
                        }
                    }
                }
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
        charge(15);
        ra = ld(sp, 160);
        lq(fp, sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 560);
    }

    // 0x42DD90 (task, x, z, ox, oz): the eight 16-byte object records at 0x86BE00 ({s32 kind, f32 pos[3]}, comm_b.h
    // kVec4Table) whose position is on cell (x, z) (sub_44F120 / sub_44F170): the mark position per axis (as sub_42C0A0,
    // with the object's own cell offset), then by kind (compared in the order 4, 3, 2, 1): 1 sprite 7 scale 2.0; 2
    // sprite 11 scale 2.0 only within 2000 units of the player (RwV3dLength, sub_4C6AC0); 3 sprite 12 and 4 sprite 5 with
    // scale 3.0, shown only when the cell's room (sub_433810, or the cell itself) is seen (0x95C110); 1 / 2 are shown inside
    // the map ([corner + 8, corner + 126 - 12)) regardless. Alpha 255 = hidden, 0 = shown.
    void sub_42DD90() {
        enter(34);
        sp = addiu(sp, -432);
        sd(sp, 160, ra);
        sq(fp, sp, 144);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s4 = a1;
        s3 = a2;
        s6 = a3;
        s7 = a4;
        s0 = lw(a0, kTaskWork);
        s2 = 0;
        fp = dsll32(s4, 16);
        fp = dsra32(fp, 16);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        sq(v1, sp, 192);
        v1 = lui(0x96u);
        v1 = addiu(v1, -16112);  // 0x95C110
        a0 = addu(v1, fp);
        lq(v1, sp, 192);
        v1 = sll(v1, 4);
        v1 = addu(v1, a0);
        sq(v1, sp, 176);
        for (;;) {
            charge(3);
            v1 = slti(s2, 8);
            if (v1 == 0) break;
            backedge();
            charge(7);
            a0 = sll(s2, 4);
            v1 = lui(0x87u);
            v1 = addiu(v1, -16896);  // 0x86BE00
            s5 = addu(v1, a0);
            v1 = lw(s5, 0);
            if (v1 != 0) {
                charge(6);
                s1 = addiu(s5, 4);
                a0 = s1;
                jal(0x42DE3Cu, &gen::fn_sub_44F120_0044f120);
                if (fp == v0) {
                    charge(6);
                    a0 = s1;
                    jal(0x42DE50u, &gen::fn_sub_44F170_0044f170);
                    lq(v1, sp, 192);
                    if (v1 == v0) {
                        charge(3);
                        v0 = lb(s0, 2149);
                        if (v0 == 0) {
                            charge(102);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 320);
                            a1 = lw(v0, kResController);
                            jal(0x42DE90u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 320);
                            lwc1(1, sp, 324);
                            lwc1(0, sp, 328);
                            swc1(2, sp, 336);
                            swc1(1, sp, 340);
                            swc1(0, sp, 344);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = lw(v0, kResController);
                            jal(0x42DEBCu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 336);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v1 = sll(s2, 4);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -16896);  // 0x86BE00
                            v0 = addu(v0, v1);
                            s1 = addiu(v0, 4);
                            a0 = addiu(sp, 352);
                            lwc1(2, v0, 4);
                            lwc1(1, v0, 8);
                            lwc1(0, v0, 12);
                            swc1(2, sp, 352);
                            swc1(1, sp, 356);
                            swc1(0, sp, 360);
                            jal(0x42DF64u, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 352);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            v1 = lb(s0, 2857);
                            lwc1(1, s0, 2140);
                            mult(v0, v1, s6);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(104);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x4100u);
                            mtc1(v0, 0);  // 8.0
                            sub_s(21, 1, 0);
                            mtc1(v1, 0);
                            cvt_s_w(20, 0);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 272);
                            a1 = lw(v0, kResController);
                            jal(0x42E04Cu, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 272);
                            lwc1(1, sp, 276);
                            lwc1(0, sp, 280);
                            swc1(2, sp, 288);
                            swc1(1, sp, 292);
                            swc1(0, sp, 296);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = lw(v0, kResController);
                            jal(0x42E078u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 296);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(22, 0);
                            a0 = addiu(sp, 304);
                            lwc1(2, s1, 0);
                            lwc1(1, s1, 4);
                            lwc1(0, s1, 8);
                            swc1(2, sp, 304);
                            swc1(1, sp, 308);
                            swc1(0, sp, 312);
                            jal(0x42E10Cu, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v1 = lui(0x4448u);
                            mtc1(v1, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v1 = lui(0x43C8u);
                            mtc1(v1, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 312);
                            sub_s(3, 0, 1);
                            div_s(2, 22, 2);
                            v1 = lui(0x4000u);
                            mtc1(v1, 0);  // 2.0
                            div_s(1, 22, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            a0 = lb(s0, 2857);
                            lwc1(1, s0, 2144);
                            mult(v1, a0, s7);
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v1 = sll(a0, 1);
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v1 = sra(a0, 1);
                            if (ltz(a0)) {
                                charge(2);
                                v1 = addiu(a0, 1);
                                v1 = sra(v1, 1);
                            }
                            charge(10);
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v1 = lui(0x4100u);
                            mtc1(v1, 0);  // 8.0
                            sub_s(20, 1, 0);
                        } else {
                            charge(94);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            a0 = addiu(sp, 240);
                            lwc1(2, s0, 2152);
                            lwc1(1, s0, 2156);
                            lwc1(0, s0, 2160);
                            swc1(2, sp, 240);
                            swc1(1, sp, 244);
                            swc1(0, sp, 248);
                            jal(0x42E20Cu, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 240);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v1 = sll(s2, 4);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -16896);  // 0x86BE00
                            v0 = addu(v0, v1);
                            s1 = addiu(v0, 4);
                            a0 = addiu(sp, 256);
                            lwc1(2, v0, 4);
                            lwc1(1, v0, 8);
                            lwc1(0, v0, 12);
                            swc1(2, sp, 256);
                            swc1(1, sp, 260);
                            swc1(0, sp, 264);
                            jal(0x42E2B4u, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 256);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            v1 = lb(s0, 2857);
                            lwc1(1, s0, 2140);
                            mult(v0, v1, s6);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(96);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v0 = lui(0x4100u);
                            mtc1(v0, 0);  // 8.0
                            sub_s(21, 1, 0);
                            mtc1(v1, 0);
                            cvt_s_w(20, 0);
                            a0 = addiu(sp, 208);
                            lwc1(2, s0, 2152);
                            lwc1(1, s0, 2156);
                            lwc1(0, s0, 2160);
                            swc1(2, sp, 208);
                            swc1(1, sp, 212);
                            swc1(0, sp, 216);
                            jal(0x42E3A8u, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 216);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(20, 0);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(22, 0);
                            a0 = addiu(sp, 224);
                            lwc1(2, s1, 0);
                            lwc1(1, s1, 4);
                            lwc1(0, s1, 8);
                            swc1(2, sp, 224);
                            swc1(1, sp, 228);
                            swc1(0, sp, 232);
                            jal(0x42E43Cu, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v1 = lui(0x4448u);
                            mtc1(v1, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v1 = lui(0x43C8u);
                            mtc1(v1, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 232);
                            sub_s(3, 0, 1);
                            div_s(2, 22, 2);
                            v1 = lui(0x4000u);
                            mtc1(v1, 0);  // 2.0
                            div_s(1, 22, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(2, 3, 2);
                            a0 = lb(s0, 2857);
                            lwc1(1, s0, 2144);
                            mult(v1, a0, s7);
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            sub_s(0, 0, 2);
                            add_s(1, 0, 20);
                            v1 = sll(a0, 1);
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v1 = sra(a0, 1);
                            if (ltz(a0)) {
                                charge(2);
                                v1 = addiu(a0, 1);
                                v1 = sra(v1, 1);
                            }
                            charge(8);
                            mtc1(v1, 0);
                            cvt_s_w(0, 0);
                            add_s(1, 0, 1);
                            v1 = lui(0x4100u);
                            mtc1(v1, 0);  // 8.0
                            sub_s(20, 1, 0);
                        }
                        charge(4);
                        a0 = lw(s5, 0);
                        v1 = si(4);
                        if (a0 != v1) {
                            charge(3);
                            v1 = si(3);
                            if (a0 != v1) {
                                charge(3);
                                v1 = si(2);
                                if (a0 != v1) {
                                    charge(3);
                                    v1 = si(1);
                                    if (a0 != v1) {
                                        charge(2);
                                    } else {
                                        charge(20);
                                        a0 = 0;
                                        a1 = lw(gp, kGpSmapSprite);
                                        a2 = si(7);
                                        jal(0x42E550u, &gen::fn_sprCreateHandle_001158b0);
                                        s1 = v0;
                                        v1 = lui(0x4000u);
                                        sw(v0, 44, v1);
                                        swc1(21, v0, 16);
                                        swc1(20, v0, 20);
                                        v1 = si(255);
                                        sb(v0, 24, v1);
                                        lwc1(2, s0, 2140);
                                        v0 = lui(0x4100u);
                                        mtc1(v0, 1);  // 8.0
                                        add_s(0, 1, 21);
                                        c_lt_s(2, 0);
                                        if (cond()) {
                                            charge(5);
                                            lwc1(4, s0, 2144);
                                            add_s(0, 1, 20);
                                            c_lt_s(4, 0);
                                            if (cond()) {
                                                charge(11);
                                                v0 = lui(0x42FCu);
                                                mtc1(v0, 3);  // 126.0
                                                add_s(1, 3, 2);
                                                v0 = lui(0x4140u);
                                                mtc1(v0, 2);  // 12.0
                                                add_s(0, 2, 21);
                                                c_le_s(1, 0);
                                                if (!cond()) {
                                                    charge(5);
                                                    add_s(1, 3, 4);
                                                    add_s(0, 2, 20);
                                                    c_le_s(1, 0);
                                                    if (!cond()) {
                                                        charge(1);
                                                        sb(s1, 24, zero);
                                                    }
                                                }
                                            }
                                        }
                                        charge(9);
                                        a0 = s1;
                                        a1 = si(1);
                                        jal(0x42E5F4u, &gen::fn_sub_1127D0_001127d0);
                                        a0 = s1;
                                        jal(0x42E600u, &gen::fn_sub_115980_00115980);
                                    }
                                } else {
                                    charge(43);
                                    v1 = sll(s2, 4);
                                    v0 = lui(0x87u);
                                    v0 = addiu(v0, -16896);  // 0x86BE00
                                    s5 = addu(v0, v1);
                                    v0 = lui(0x87u);
                                    v0 = lw(v0, 6132);  // 0x8717F4
                                    a0 = addiu(sp, 400);
                                    a1 = lw(v0, kResController);
                                    jal(0x42E630u, &gen::fn_sub_1AD940_001ad940);
                                    lwc1(1, sp, 400);
                                    lwc1(0, s1, 0);
                                    sub_s(0, 0, 1);
                                    swc1(0, sp, 416);
                                    v0 = lui(0x87u);
                                    v0 = lw(v0, 6132);  // 0x8717F4
                                    a0 = addiu(sp, 384);
                                    a1 = lw(v0, kResController);
                                    jal(0x42E658u, &gen::fn_sub_1AD940_001ad940);
                                    lwc1(1, sp, 388);
                                    lwc1(0, s5, 8);
                                    sub_s(0, 0, 1);
                                    swc1(0, sp, 420);
                                    v0 = lui(0x87u);
                                    v0 = lw(v0, 6132);  // 0x8717F4
                                    a0 = addiu(sp, 368);
                                    a1 = lw(v0, kResController);
                                    jal(0x42E680u, &gen::fn_sub_1AD940_001ad940);
                                    lwc1(1, sp, 376);
                                    lwc1(0, s5, 12);
                                    sub_s(0, 0, 1);
                                    swc1(0, sp, 424);
                                    a0 = addiu(sp, 416);
                                    jal(0x42E69Cu, &gen::fn_sub_4C6AC0_004c6ac0);
                                    v1 = lui(0x44FAu);
                                    mtc1(v1, 1);  // 2000f
                                    c_lt_s(0, 1);
                                    if (cond()) {
                                        charge(20);
                                        a0 = 0;
                                        a1 = lw(gp, kGpSmapSprite);
                                        a2 = si(11);
                                        jal(0x42E6C8u, &gen::fn_sprCreateHandle_001158b0);
                                        s1 = v0;
                                        v1 = lui(0x4000u);
                                        sw(v0, 44, v1);
                                        swc1(21, v0, 16);
                                        swc1(20, v0, 20);
                                        v1 = si(255);
                                        sb(v0, 24, v1);
                                        lwc1(2, s0, 2140);
                                        v0 = lui(0x4100u);
                                        mtc1(v0, 1);  // 8.0
                                        add_s(0, 1, 21);
                                        c_lt_s(2, 0);
                                        if (cond()) {
                                            charge(5);
                                            lwc1(4, s0, 2144);
                                            add_s(0, 1, 20);
                                            c_lt_s(4, 0);
                                            if (cond()) {
                                                charge(11);
                                                v0 = lui(0x42FCu);
                                                mtc1(v0, 3);  // 126.0
                                                add_s(1, 3, 2);
                                                v0 = lui(0x4140u);
                                                mtc1(v0, 2);  // 12.0
                                                add_s(0, 2, 21);
                                                c_le_s(1, 0);
                                                if (!cond()) {
                                                    charge(5);
                                                    add_s(1, 3, 4);
                                                    add_s(0, 2, 20);
                                                    c_le_s(1, 0);
                                                    if (!cond()) {
                                                        charge(1);
                                                        sb(s1, 24, zero);
                                                    }
                                                }
                                            }
                                        }
                                        charge(9);
                                        a0 = s1;
                                        a1 = si(1);
                                        jal(0x42E76Cu, &gen::fn_sub_1127D0_001127d0);
                                        a0 = s1;
                                        jal(0x42E778u, &gen::fn_sub_115980_00115980);
                                    }
                                }
                            } else {
                                charge(20);
                                a0 = 0;
                                a1 = lw(gp, kGpSmapSprite);
                                a2 = si(12);
                                jal(0x42E794u, &gen::fn_sprCreateHandle_001158b0);
                                s1 = v0;
                                v1 = lui(0x4040u);
                                sw(v0, 44, v1);
                                swc1(21, v0, 16);
                                swc1(20, v0, 20);
                                v1 = si(255);
                                sb(v0, 24, v1);
                                lwc1(2, s0, 2140);
                                v0 = lui(0x4100u);
                                mtc1(v0, 1);  // 8.0
                                add_s(0, 1, 21);
                                c_lt_s(2, 0);
                                if (cond()) {
                                    charge(5);
                                    lwc1(4, s0, 2144);
                                    add_s(0, 1, 20);
                                    c_lt_s(4, 0);
                                    if (cond()) {
                                        charge(11);
                                        v0 = lui(0x42FCu);
                                        mtc1(v0, 3);  // 126.0
                                        add_s(1, 3, 2);
                                        v0 = lui(0x4140u);
                                        mtc1(v0, 2);  // 12.0
                                        add_s(0, 2, 21);
                                        c_le_s(1, 0);
                                        if (!cond()) {
                                            charge(5);
                                            add_s(1, 3, 4);
                                            add_s(0, 2, 20);
                                            c_le_s(1, 0);
                                            if (!cond()) {
                                                charge(9);
                                                a0 = dsll32(s4, 24);
                                                a0 = dsra32(a0, 24);
                                                a1 = dsll32(s3, 24);
                                                a1 = dsra32(a1, 24);
                                                jal(0x42E83Cu, &gen::fn_sub_433810_00433810);
                                                v0 = v0 & 0xFFu;
                                                if (v0 == 0) {
                                                    charge(5);
                                                    lq(v0, sp, 176);
                                                    v1 = lb(v0, 0);
                                                    v0 = si(1);
                                                    if (v1 == v0) {
                                                        charge(3);
                                                        sb(s1, 24, zero);
                                                    }
                                                } else {
                                                    charge(14);
                                                    a0 = dsll32(s4, 24);
                                                    a0 = dsra32(a0, 24);
                                                    a1 = dsll32(s3, 24);
                                                    a1 = dsra32(a1, 24);
                                                    jal(0x42E880u, &gen::fn_sub_433810_00433810);
                                                    v1 = v0 & 0xFFu;
                                                    v0 = lui(0x96u);
                                                    v0 = addiu(v0, -16112);  // 0x95C110
                                                    v0 = addu(v0, v1);
                                                    v1 = lb(v0, 0);
                                                    v0 = si(1);
                                                    if (v1 == v0) {
                                                        charge(1);
                                                        sb(s1, 24, zero);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                charge(9);
                                a0 = s1;
                                a1 = si(1);
                                jal(0x42E8B4u, &gen::fn_sub_1127D0_001127d0);
                                a0 = s1;
                                jal(0x42E8C0u, &gen::fn_sub_115980_00115980);
                            }
                        } else {
                            charge(20);
                            a0 = 0;
                            a1 = lw(gp, kGpSmapSprite);
                            a2 = si(5);
                            jal(0x42E8DCu, &gen::fn_sprCreateHandle_001158b0);
                            s1 = v0;
                            v1 = lui(0x4040u);
                            sw(v0, 44, v1);
                            swc1(21, v0, 16);
                            swc1(20, v0, 20);
                            v1 = si(255);
                            sb(v0, 24, v1);
                            lwc1(2, s0, 2140);
                            v0 = lui(0x4100u);
                            mtc1(v0, 1);  // 8.0
                            add_s(0, 1, 21);
                            c_lt_s(2, 0);
                            if (cond()) {
                                charge(5);
                                lwc1(4, s0, 2144);
                                add_s(0, 1, 20);
                                c_lt_s(4, 0);
                                if (cond()) {
                                    charge(11);
                                    v0 = lui(0x42FCu);
                                    mtc1(v0, 3);  // 126.0
                                    add_s(1, 3, 2);
                                    v0 = lui(0x4140u);
                                    mtc1(v0, 2);  // 12.0
                                    add_s(0, 2, 21);
                                    c_le_s(1, 0);
                                    if (!cond()) {
                                        charge(5);
                                        add_s(1, 3, 4);
                                        add_s(0, 2, 20);
                                        c_le_s(1, 0);
                                        if (!cond()) {
                                            charge(9);
                                            a0 = dsll32(s4, 24);
                                            a0 = dsra32(a0, 24);
                                            a1 = dsll32(s3, 24);
                                            a1 = dsra32(a1, 24);
                                            jal(0x42E984u, &gen::fn_sub_433810_00433810);
                                            v0 = v0 & 0xFFu;
                                            if (v0 == 0) {
                                                charge(5);
                                                lq(v0, sp, 176);
                                                v1 = lb(v0, 0);
                                                v0 = si(1);
                                                if (v1 == v0) {
                                                    charge(3);
                                                    sb(s1, 24, zero);
                                                }
                                            } else {
                                                charge(14);
                                                a0 = dsll32(s4, 24);
                                                a0 = dsra32(a0, 24);
                                                a1 = dsll32(s3, 24);
                                                a1 = dsra32(a1, 24);
                                                jal(0x42E9C8u, &gen::fn_sub_433810_00433810);
                                                v1 = v0 & 0xFFu;
                                                v0 = lui(0x96u);
                                                v0 = addiu(v0, -16112);  // 0x95C110
                                                v0 = addu(v0, v1);
                                                v1 = lb(v0, 0);
                                                v0 = si(1);
                                                if (v1 == v0) {
                                                    charge(1);
                                                    sb(s1, 24, zero);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            charge(7);
                            a0 = s1;
                            a1 = si(1);
                            jal(0x42E9FCu, &gen::fn_sub_1127D0_001127d0);
                            a0 = s1;
                            jal(0x42EA08u, &gen::fn_sub_115980_00115980);
                        }
                    }
                }
            }
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(16);
        ra = ld(sp, 160);
        lq(fp, sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 432);
    }

    // 0x42EA60 (task, x, z, ox, oz): the 32 records of 312 bytes at 0x86BE80 with a non-zero +0 whose position (+268) is on
    // cell (x, z): sprite 12 is created first, the mark position (work +2560 + 8 i / +2564 + 8 i) is the corner + size * o +
    // the record's cell offset - the player's (or the frozen centre's) - 2 size + size / 2 minus half the sprite's width /
    // height; scale 3.0, shown when inside the map and its room is seen.
    void sub_42EA60() {
        enter(35);
        sp = addiu(sp, -416);
        sd(sp, 160, ra);
        sq(fp, sp, 144);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s3 = a1;
        s5 = a2;
        s7 = a3;
        fp = a4;
        s0 = lw(a0, kTaskWork);
        s2 = 0;
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        sq(v1, sp, 240);
        v1 = dsll32(s5, 16);
        v1 = dsra32(v1, 16);
        sq(v1, sp, 224);
        a0 = lui(0x96u);
        a0 = addiu(a0, -16112);  // 0x95C110
        lq(v1, sp, 240);
        a0 = addu(a0, v1);
        lq(v1, sp, 224);
        v1 = sll(v1, 4);
        v1 = addu(v1, a0);
        sq(v1, sp, 208);
        for (;;) {
            charge(3);
            v1 = slti(s2, 32);
            if (v1 == 0) break;
            backedge();
            charge(11);
            v1 = sll(s2, 2);
            v1 = addu(v1, s2);
            v1 = sll(v1, 3);
            v1 = subu(v1, s2);
            a0 = sll(v1, 3);
            v1 = lui(0x87u);
            v1 = addiu(v1, -16768);  // 0x86BE80
            a0 = addu(v1, a0);
            v1 = lw(a0, 0);
            if (v1 != 0) {
                charge(7);
                s1 = addiu(a0, 268);
                a0 = s1;
                jal(0x42EB20u, &gen::fn_sub_44F120_0044f120);
                lq(v1, sp, 240);
                if (v1 == v0) {
                    charge(6);
                    a0 = s1;
                    jal(0x42EB38u, &gen::fn_sub_44F170_0044f170);
                    lq(v1, sp, 224);
                    if (v1 == v0) {
                        charge(9);
                        a0 = 0;
                        a1 = lw(gp, kGpSmapSprite);
                        a2 = si(12);
                        jal(0x42EB58u, &gen::fn_sprCreateHandle_001158b0);
                        s1 = v0;
                        v0 = lb(s0, 2149);
                        if (v0 == 0) {
                            charge(110);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            v0 = sll(s2, 2);
                            v0 = addu(v0, s2);
                            v0 = sll(v0, 3);
                            v0 = subu(v0, s2);
                            v1 = sll(v0, 3);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -16768);  // 0x86BE80
                            v0 = addu(v0, v1);
                            s4 = addiu(v0, 268);
                            a0 = addiu(sp, 368);
                            lwc1(2, v0, 268);
                            lwc1(1, v0, 272);
                            lwc1(0, v0, 276);
                            swc1(2, sp, 368);
                            swc1(1, sp, 372);
                            swc1(0, sp, 376);
                            jal(0x42EBC0u, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 368);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(20, 3, 2);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 384);
                            a1 = lw(v0, kResController);
                            jal(0x42EC40u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 384);
                            lwc1(1, sp, 388);
                            lwc1(0, sp, 392);
                            swc1(2, sp, 400);
                            swc1(1, sp, 404);
                            swc1(0, sp, 408);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = lw(v0, kResController);
                            jal(0x42EC6Cu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 400);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(2, 0);
                            v1 = lb(s0, 2857);
                            v0 = sll(s2, 3);
                            s6 = addu(s0, v0);
                            v0 = addiu(s6, 2560);
                            sq(v0, sp, 192);
                            lwc1(1, s0, 2140);
                            mult(v0, v1, s7);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            add_s(0, 0, 2);
                            sub_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(112);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(20, 0, 1);
                            a0 = s1;
                            jal(0x42ED44u, &gen::fn_sprGetSpriteWidth_001126b0);
                            v0 = lui(0x4000u);
                            mtc1(v0, 1);  // 2.0
                            div_s(0, 0, 1);
                            sub_s(0, 20, 0);
                            lq(v0, sp, 192);
                            swc1(0, v0, 0);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            a0 = addiu(sp, 320);
                            lwc1(2, s4, 0);
                            lwc1(1, s4, 4);
                            lwc1(0, s4, 8);
                            swc1(2, sp, 320);
                            swc1(1, sp, 324);
                            swc1(0, sp, 328);
                            jal(0x42ED94u, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 328);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(20, 3, 2);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = addiu(sp, 336);
                            a1 = lw(v0, kResController);
                            jal(0x42EE14u, &gen::fn_sub_1AD940_001ad940);
                            lwc1(2, sp, 336);
                            lwc1(1, sp, 340);
                            lwc1(0, sp, 344);
                            swc1(2, sp, 352);
                            swc1(1, sp, 356);
                            swc1(0, sp, 360);
                            v0 = lui(0x87u);
                            v0 = lw(v0, 6132);  // 0x8717F4
                            a0 = lw(v0, kResController);
                            jal(0x42EE40u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 360);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(2, 0);
                            v1 = lb(s0, 2857);
                            s4 = addiu(s6, 2564);
                            lwc1(1, s0, 2144);
                            mult(v0, v1, fp);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            add_s(0, 0, 2);
                            sub_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(16);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(20, 0, 1);
                            a0 = s1;
                            jal(0x42EF0Cu, &gen::fn_sprGetSpriteHeight_00112740);
                            v0 = lui(0x4000u);
                            mtc1(v0, 1);  // 2.0
                            div_s(0, 0, 1);
                            sub_s(0, 20, 0);
                            swc1(0, s4, 0);
                        } else {
                            charge(102);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            v0 = sll(s2, 2);
                            v0 = addu(v0, s2);
                            v0 = sll(v0, 3);
                            v0 = subu(v0, s2);
                            v1 = sll(v0, 3);
                            v0 = lui(0x87u);
                            v0 = addiu(v0, -16768);  // 0x86BE80
                            v0 = addu(v0, v1);
                            s4 = addiu(v0, 268);
                            a0 = addiu(sp, 288);
                            lwc1(2, v0, 268);
                            lwc1(1, v0, 272);
                            lwc1(0, v0, 276);
                            swc1(2, sp, 288);
                            swc1(1, sp, 292);
                            swc1(0, sp, 296);
                            jal(0x42EF88u, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 288);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(20, 3, 2);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            a0 = addiu(sp, 304);
                            lwc1(2, s0, 2152);
                            lwc1(1, s0, 2156);
                            lwc1(0, s0, 2160);
                            swc1(2, sp, 304);
                            swc1(1, sp, 308);
                            swc1(0, sp, 312);
                            jal(0x42F014u, &gen::fn_sub_44F120_0044f120);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 304);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(2, 0);
                            v1 = lb(s0, 2857);
                            v0 = sll(s2, 3);
                            s6 = addu(s0, v0);
                            v0 = addiu(s6, 2560);
                            sq(v0, sp, 176);
                            lwc1(1, s0, 2140);
                            mult(v0, v1, s7);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            add_s(0, 0, 2);
                            sub_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(104);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(20, 0, 1);
                            a0 = s1;
                            jal(0x42F0ECu, &gen::fn_sprGetSpriteWidth_001126b0);
                            v0 = lui(0x4000u);
                            mtc1(v0, 1);  // 2.0
                            div_s(0, 0, 1);
                            sub_s(0, 20, 0);
                            lq(v0, sp, 176);
                            swc1(0, v0, 0);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(20, 0);
                            a0 = addiu(sp, 256);
                            lwc1(2, s4, 0);
                            lwc1(1, s4, 4);
                            lwc1(0, s4, 8);
                            swc1(2, sp, 256);
                            swc1(1, sp, 260);
                            swc1(0, sp, 264);
                            jal(0x42F13Cu, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 264);
                            sub_s(3, 0, 1);
                            div_s(2, 20, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 20, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(20, 3, 2);
                            v0 = lb(s0, 2857);
                            mtc1(v0, 0);
                            cvt_s_w(21, 0);
                            a0 = addiu(sp, 272);
                            lwc1(2, s0, 2152);
                            lwc1(1, s0, 2156);
                            lwc1(0, s0, 2160);
                            swc1(2, sp, 272);
                            swc1(1, sp, 276);
                            swc1(0, sp, 280);
                            jal(0x42F1C8u, &gen::fn_sub_44F170_0044f170);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            v0 = lui(0x4448u);
                            mtc1(v0, 2);  // 800.0
                            mul_s(1, 2, 0);
                            v0 = lui(0x43C8u);
                            mtc1(v0, 0);  // 400.0
                            sub_s(1, 1, 0);
                            lwc1(0, sp, 280);
                            sub_s(3, 0, 1);
                            div_s(2, 21, 2);
                            v0 = lui(0x4000u);
                            mtc1(v0, 0);  // 2.0
                            div_s(1, 21, 0);
                            mtc1(zero, 0);
                            adda_s(0, 1);
                            msub_s(0, 3, 2);
                            cvt_w_s(0, 0);
                            cvt_s_w(2, 0);
                            v1 = lb(s0, 2857);
                            s4 = addiu(s6, 2564);
                            lwc1(1, s0, 2144);
                            mult(v0, v1, fp);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(0, 1, 0);
                            add_s(0, 0, 2);
                            sub_s(1, 0, 20);
                            v0 = sll(v1, 1);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            sub_s(1, 1, 0);
                            v0 = sra(v1, 1);
                            if (ltz(v1)) {
                                charge(2);
                                v0 = addiu(v1, 1);
                                v0 = sra(v0, 1);
                            }
                            charge(13);
                            mtc1(v0, 0);
                            cvt_s_w(0, 0);
                            add_s(20, 0, 1);
                            a0 = s1;
                            jal(0x42F294u, &gen::fn_sprGetSpriteHeight_00112740);
                            v0 = lui(0x4000u);
                            mtc1(v0, 1);  // 2.0
                            div_s(0, 0, 1);
                            sub_s(0, 20, 0);
                            swc1(0, s4, 0);
                        }
                        charge(19);
                        v0 = lui(0x4040u);
                        sw(s1, 44, v0);
                        v0 = sll(s2, 3);
                        v1 = addu(s0, v0);
                        lwc1(0, v1, 2560);
                        swc1(0, s1, 16);
                        lwc1(0, s4, 0);
                        swc1(0, s1, 20);
                        v0 = si(255);
                        sb(s1, 24, v0);
                        lwc1(6, v1, 2560);
                        lwc1(2, s0, 2140);
                        v0 = lui(0x4100u);
                        mtc1(v0, 1);  // 8.0
                        add_s(0, 1, 6);
                        c_lt_s(2, 0);
                        if (cond()) {
                            charge(6);
                            lwc1(5, s4, 0);
                            lwc1(4, s0, 2144);
                            add_s(0, 1, 5);
                            c_lt_s(4, 0);
                            if (cond()) {
                                charge(11);
                                v0 = lui(0x42FCu);
                                mtc1(v0, 3);  // 126.0
                                add_s(1, 3, 2);
                                v0 = lui(0x4140u);
                                mtc1(v0, 2);  // 12.0
                                add_s(0, 2, 6);
                                c_le_s(1, 0);
                                if (!cond()) {
                                    charge(5);
                                    add_s(1, 3, 4);
                                    add_s(0, 2, 5);
                                    c_le_s(1, 0);
                                    if (!cond()) {
                                        charge(9);
                                        a0 = dsll32(s3, 24);
                                        a0 = dsra32(a0, 24);
                                        a1 = dsll32(s5, 24);
                                        a1 = dsra32(a1, 24);
                                        jal(0x42F368u, &gen::fn_sub_433810_00433810);
                                        v0 = v0 & 0xFFu;
                                        if (v0 == 0) {
                                            charge(5);
                                            lq(v0, sp, 208);
                                            v1 = lb(v0, 0);
                                            v0 = si(1);
                                            if (v1 == v0) {
                                                charge(3);
                                                sb(s1, 24, zero);
                                            }
                                        } else {
                                            charge(14);
                                            a0 = dsll32(s3, 24);
                                            a0 = dsra32(a0, 24);
                                            a1 = dsll32(s5, 24);
                                            a1 = dsra32(a1, 24);
                                            jal(0x42F3ACu, &gen::fn_sub_433810_00433810);
                                            v1 = v0 & 0xFFu;
                                            v0 = lui(0x96u);
                                            v0 = addiu(v0, -16112);  // 0x95C110
                                            v0 = addu(v0, v1);
                                            v1 = lb(v0, 0);
                                            v0 = si(1);
                                            if (v1 == v0) {
                                                charge(1);
                                                sb(s1, 24, zero);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        charge(7);
                        a0 = s1;
                        a1 = si(1);
                        jal(0x42F3E0u, &gen::fn_sub_1127D0_001127d0);
                        a0 = s1;
                        jal(0x42F3ECu, &gen::fn_sub_115980_00115980);
                    }
                }
            }
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(15);
        ra = ld(sp, 160);
        lq(fp, sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 416);
    }

    // 0x42F440 (task, x, z, ox, oz): while the s32 at 0x86E580 is 1 and the position at 0x86E684 is on cell (x, z): sprite 5
    // at work +2816 / +2820 (the same placement as sub_42EA60, minus half the sprite's size), scale 3.0, shown when inside
    // the map and its room (or the cell itself) is seen.
    void sub_42F440() {
        enter(22);
        sp = addiu(sp, -320);
        sd(sp, 144, ra);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s3 = a1;
        s2 = a2;
        s1 = a3;
        s0 = a4;
        s4 = lw(a0, kTaskWork);
        v1 = lui(0x87u);
        a0 = lw(v1, -6784);  // 0x86E580
        v1 = si(1);
        if (a0 == v1) {
            charge(8);
            s6 = dsll32(s3, 16);
            s6 = dsra32(s6, 16);
            a0 = lui(0x87u);
            a0 = addiu(a0, -6524);  // 0x86E684
            jal(0x42F4A8u, &gen::fn_sub_44F120_0044f120);
            if (s6 == v0) {
                charge(8);
                s7 = dsll32(s2, 16);
                s7 = dsra32(s7, 16);
                a0 = lui(0x87u);
                a0 = addiu(a0, -6524);  // 0x86E684
                jal(0x42F4C8u, &gen::fn_sub_44F170_0044f170);
                if (s7 == v0) {
                    charge(9);
                    a0 = 0;
                    a1 = lw(gp, kGpSmapSprite);
                    a2 = si(5);
                    jal(0x42F4E4u, &gen::fn_sprCreateHandle_001158b0);
                    s5 = v0;
                    v0 = lb(s4, 2149);
                    if (v0 == 0) {
                        charge(100);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        a0 = addiu(sp, 272);
                        v0 = lui(0x87u);
                        lwc1(2, v0, -6524);  // 0x86E684
                        v0 = lui(0x87u);
                        lwc1(1, v0, -6520);  // 0x86E688
                        v0 = lui(0x87u);
                        lwc1(0, v0, -6516);  // 0x86E68C
                        swc1(2, sp, 272);
                        swc1(1, sp, 276);
                        swc1(0, sp, 280);
                        jal(0x42F534u, &gen::fn_sub_44F120_0044f120);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 272);
                        sub_s(3, 0, 1);
                        div_s(2, 20, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 20, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(20, 3, 2);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(21, 0);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = addiu(sp, 288);
                        a1 = lw(v0, kResController);
                        jal(0x42F5B4u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 288);
                        lwc1(1, sp, 292);
                        lwc1(0, sp, 296);
                        swc1(2, sp, 304);
                        swc1(1, sp, 308);
                        swc1(0, sp, 312);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = lw(v0, kResController);
                        jal(0x42F5E0u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 304);
                        sub_s(3, 0, 1);
                        div_s(2, 21, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 21, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        v1 = lb(s4, 2857);
                        lwc1(1, s4, 2140);
                        mult(v0, v1, s1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        add_s(0, 0, 2);
                        sub_s(1, 0, 20);
                        v0 = sll(v1, 1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(113);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(20, 0, 1);
                        a0 = s5;
                        jal(0x42F6A8u, &gen::fn_sprGetSpriteWidth_001126b0);
                        v0 = lui(0x4000u);
                        mtc1(v0, 1);  // 2.0
                        div_s(0, 0, 1);
                        sub_s(0, 20, 0);
                        swc1(0, s4, 2816);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        a0 = addiu(sp, 224);
                        v0 = lui(0x87u);
                        lwc1(2, v0, -6524);  // 0x86E684
                        v0 = lui(0x87u);
                        lwc1(1, v0, -6520);  // 0x86E688
                        v0 = lui(0x87u);
                        lwc1(0, v0, -6516);  // 0x86E68C
                        swc1(2, sp, 224);
                        swc1(1, sp, 228);
                        swc1(0, sp, 232);
                        jal(0x42F700u, &gen::fn_sub_44F170_0044f170);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 232);
                        sub_s(3, 0, 1);
                        div_s(2, 20, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 20, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(20, 3, 2);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(21, 0);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = addiu(sp, 240);
                        a1 = lw(v0, kResController);
                        jal(0x42F780u, &gen::fn_sub_1AD940_001ad940);
                        lwc1(2, sp, 240);
                        lwc1(1, sp, 244);
                        lwc1(0, sp, 248);
                        swc1(2, sp, 256);
                        swc1(1, sp, 260);
                        swc1(0, sp, 264);
                        v0 = lui(0x87u);
                        v0 = lw(v0, 6132);  // 0x8717F4
                        a0 = lw(v0, kResController);
                        jal(0x42F7ACu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 264);
                        sub_s(3, 0, 1);
                        div_s(2, 21, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 21, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        v1 = lb(s4, 2857);
                        lwc1(1, s4, 2144);
                        mult(v0, v1, s0);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        add_s(0, 0, 2);
                        sub_s(1, 0, 20);
                        v0 = sll(v1, 1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(16);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(20, 0, 1);
                        a0 = s5;
                        jal(0x42F874u, &gen::fn_sprGetSpriteHeight_00112740);
                        v0 = lui(0x4000u);
                        mtc1(v0, 1);  // 2.0
                        div_s(0, 0, 1);
                        sub_s(0, 20, 0);
                        swc1(0, s4, 2820);
                    } else {
                        charge(92);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        a0 = addiu(sp, 192);
                        v0 = lui(0x87u);
                        lwc1(2, v0, -6524);  // 0x86E684
                        v0 = lui(0x87u);
                        lwc1(1, v0, -6520);  // 0x86E688
                        v0 = lui(0x87u);
                        lwc1(0, v0, -6516);  // 0x86E68C
                        swc1(2, sp, 192);
                        swc1(1, sp, 196);
                        swc1(0, sp, 200);
                        jal(0x42F8D8u, &gen::fn_sub_44F120_0044f120);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 192);
                        sub_s(3, 0, 1);
                        div_s(2, 20, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 20, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(20, 3, 2);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(21, 0);
                        a0 = addiu(sp, 208);
                        lwc1(2, s4, 2152);
                        lwc1(1, s4, 2156);
                        lwc1(0, s4, 2160);
                        swc1(2, sp, 208);
                        swc1(1, sp, 212);
                        swc1(0, sp, 216);
                        jal(0x42F964u, &gen::fn_sub_44F120_0044f120);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 208);
                        sub_s(3, 0, 1);
                        div_s(2, 21, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 21, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        v1 = lb(s4, 2857);
                        lwc1(1, s4, 2140);
                        mult(v0, v1, s1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        add_s(0, 0, 2);
                        sub_s(1, 0, 20);
                        v0 = sll(v1, 1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(105);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(20, 0, 1);
                        a0 = s5;
                        jal(0x42FA2Cu, &gen::fn_sprGetSpriteWidth_001126b0);
                        v0 = lui(0x4000u);
                        mtc1(v0, 1);  // 2.0
                        div_s(0, 0, 1);
                        sub_s(0, 20, 0);
                        swc1(0, s4, 2816);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(20, 0);
                        a0 = addiu(sp, 160);
                        v0 = lui(0x87u);
                        lwc1(2, v0, -6524);  // 0x86E684
                        v0 = lui(0x87u);
                        lwc1(1, v0, -6520);  // 0x86E688
                        v0 = lui(0x87u);
                        lwc1(0, v0, -6516);  // 0x86E68C
                        swc1(2, sp, 160);
                        swc1(1, sp, 164);
                        swc1(0, sp, 168);
                        jal(0x42FA84u, &gen::fn_sub_44F170_0044f170);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 168);
                        sub_s(3, 0, 1);
                        div_s(2, 20, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 20, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(20, 3, 2);
                        v0 = lb(s4, 2857);
                        mtc1(v0, 0);
                        cvt_s_w(21, 0);
                        a0 = addiu(sp, 176);
                        lwc1(2, s4, 2152);
                        lwc1(1, s4, 2156);
                        lwc1(0, s4, 2160);
                        swc1(2, sp, 176);
                        swc1(1, sp, 180);
                        swc1(0, sp, 184);
                        jal(0x42FB10u, &gen::fn_sub_44F170_0044f170);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        v0 = lui(0x4448u);
                        mtc1(v0, 2);  // 800.0
                        mul_s(1, 2, 0);
                        v0 = lui(0x43C8u);
                        mtc1(v0, 0);  // 400.0
                        sub_s(1, 1, 0);
                        lwc1(0, sp, 184);
                        sub_s(3, 0, 1);
                        div_s(2, 21, 2);
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        div_s(1, 21, 0);
                        mtc1(zero, 0);
                        adda_s(0, 1);
                        msub_s(0, 3, 2);
                        cvt_w_s(0, 0);
                        cvt_s_w(2, 0);
                        v1 = lb(s4, 2857);
                        lwc1(1, s4, 2144);
                        mult(v0, v1, s0);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(0, 1, 0);
                        add_s(0, 0, 2);
                        sub_s(1, 0, 20);
                        v0 = sll(v1, 1);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        sub_s(1, 1, 0);
                        v0 = sra(v1, 1);
                        if (ltz(v1)) {
                            charge(2);
                            v0 = addiu(v1, 1);
                            v0 = sra(v0, 1);
                        }
                        charge(13);
                        mtc1(v0, 0);
                        cvt_s_w(0, 0);
                        add_s(20, 0, 1);
                        a0 = s5;
                        jal(0x42FBD8u, &gen::fn_sprGetSpriteHeight_00112740);
                        v0 = lui(0x4000u);
                        mtc1(v0, 1);  // 2.0
                        div_s(0, 0, 1);
                        sub_s(0, 20, 0);
                        swc1(0, s4, 2820);
                    }
                    charge(17);
                    v0 = lui(0x4040u);
                    sw(s5, 44, v0);
                    lwc1(0, s4, 2816);
                    swc1(0, s5, 16);
                    lwc1(0, s4, 2820);
                    swc1(0, s5, 20);
                    v0 = si(255);
                    sb(s5, 24, v0);
                    lwc1(6, s4, 2816);
                    lwc1(2, s4, 2140);
                    v0 = lui(0x4100u);
                    mtc1(v0, 1);  // 8.0
                    add_s(0, 1, 6);
                    c_lt_s(2, 0);
                    if (cond()) {
                        charge(6);
                        lwc1(5, s4, 2820);
                        lwc1(4, s4, 2144);
                        add_s(0, 1, 5);
                        c_lt_s(4, 0);
                        if (cond()) {
                            charge(11);
                            v0 = lui(0x42FCu);
                            mtc1(v0, 3);  // 126.0
                            add_s(1, 3, 2);
                            v0 = lui(0x4140u);
                            mtc1(v0, 2);  // 12.0
                            add_s(0, 2, 6);
                            c_le_s(1, 0);
                            if (!cond()) {
                                charge(5);
                                add_s(1, 3, 4);
                                add_s(0, 2, 5);
                                c_le_s(1, 0);
                                if (!cond()) {
                                    charge(9);
                                    a0 = dsll32(s3, 24);
                                    a0 = dsra32(a0, 24);
                                    a1 = dsll32(s2, 24);
                                    a1 = dsra32(a1, 24);
                                    jal(0x42FCA4u, &gen::fn_sub_433810_00433810);
                                    v0 = v0 & 0xFFu;
                                    if (v0 == 0) {
                                        charge(9);
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -16112);  // 0x95C110
                                        v1 = addu(v0, s6);
                                        v0 = sll(s7, 4);
                                        v0 = addu(v0, v1);
                                        v1 = lb(v0, 0);
                                        v0 = si(1);
                                        if (v1 == v0) {
                                            charge(3);
                                            sb(s5, 24, zero);
                                        }
                                    } else {
                                        charge(14);
                                        a0 = dsll32(s3, 24);
                                        a0 = dsra32(a0, 24);
                                        a1 = dsll32(s2, 24);
                                        a1 = dsra32(a1, 24);
                                        jal(0x42FCF8u, &gen::fn_sub_433810_00433810);
                                        v1 = v0 & 0xFFu;
                                        v0 = lui(0x96u);
                                        v0 = addiu(v0, -16112);  // 0x95C110
                                        v0 = addu(v0, v1);
                                        v1 = lb(v0, 0);
                                        v0 = si(1);
                                        if (v1 == v0) {
                                            charge(1);
                                            sb(s5, 24, zero);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    charge(7);
                    a0 = s5;
                    a1 = si(1);
                    jal(0x42FD2Cu, &gen::fn_sub_1127D0_001127d0);
                    a0 = s5;
                    jal(0x42FD38u, &gen::fn_sub_115980_00115980);
                }
            }
        }
        charge(14);
        ra = ld(sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 320);
    }

    // 0x430BB0 ("y_smap mask draw " update, [Y_SMap_UpdateSmapMaskDrawTask] bands.sym): in state 0 (work +0) creates the
    // four "y_boxfill proc" tasks (Y_LMap_CreateBoxfillTasks) that mask the screen around the map (work +4 .. +16; their rectangles at +92
    // .. +120 and sizes +36 .. +84 from the map corner +20 / +24 and its 126 x 126 size, the two layouts by the s8 at +125),
    // each set up through sub_422C30 (position / size), sub_422C90 (colour 0) and sub_422C10 (1). Returns 0.
    void Y_SMap_UpdateSmapMaskDrawTask() {
        enter(10);
        sp = addiu(sp, -48);
        sd(sp, 32, ra);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s1 = a0;
        s0 = lw(a0, kTaskWork);
        v1 = lb(s0, 0);
        v0 = si(2);
        if (v1 != v0) {
            charge(3);
            v0 = si(1);
            if (v1 != v0) {
                charge(2);
                if (v1 != 0) {
                    charge(2);
                } else {
                    charge(3);
                    v0 = lb(s0, 125);
                    if (v0 == 0) {
                        charge(150);
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430C0Cu, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 4, v0);
                        lwc1(0, s0, 20);
                        swc1(0, s0, 92);
                        lwc1(1, s0, 24);
                        v0 = lui(0x4298u);
                        mtc1(v0, 0);  // 76f
                        sub_s(0, 1, 0);
                        swc1(0, s0, 96);
                        v0 = si(211);
                        sw(s0, 36, v0);
                        v0 = si(76);
                        sw(s0, 40, v0);
                        a0 = lw(s0, 4);
                        ldr(a1, s0, 92);
                        ldl(a1, s0, 99);
                        a2 = addiu(s0, 28);
                        jal(0x430C58u, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 4);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x430C74u, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 4);
                        a1 = si(1);
                        jal(0x430C84u, &gen::fn_sub_422C10_00422c10);
                        a0 = s1;
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430C9Cu, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 8, v0);
                        lwc1(0, s0, 20);
                        v0 = lui(0x4298u);
                        mtc1(v0, 1);  // 76f
                        sub_s(0, 0, 1);
                        swc1(0, s0, 100);
                        lwc1(0, s0, 24);
                        sub_s(0, 0, 1);
                        swc1(0, s0, 104);
                        v0 = si(76);
                        sw(s0, 52, v0);
                        v0 = si(202);
                        sw(s0, 56, v0);
                        a0 = lw(s0, 8);
                        ldr(a1, s0, 100);
                        ldl(a1, s0, 107);
                        a2 = addiu(s0, 44);
                        jal(0x430CECu, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 8);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x430D08u, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 8);
                        a1 = si(1);
                        jal(0x430D18u, &gen::fn_sub_422C10_00422c10);
                        a0 = s1;
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430D30u, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 12, v0);
                        lwc1(1, s0, 20);
                        v0 = lui(0x4298u);
                        mtc1(v0, 0);  // 76f
                        sub_s(0, 1, 0);
                        swc1(0, s0, 108);
                        lwc1(1, s0, 24);
                        v0 = lui(0x42FCu);
                        mtc1(v0, 0);  // 126.0
                        add_s(0, 0, 1);
                        swc1(0, s0, 112);
                        v0 = si(202);
                        sw(s0, 68, v0);
                        v0 = si(76);
                        sw(s0, 72, v0);
                        a0 = lw(s0, 12);
                        ldr(a1, s0, 108);
                        ldl(a1, s0, 115);
                        a2 = addiu(s0, 60);
                        jal(0x430D8Cu, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 12);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x430DA8u, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 12);
                        a1 = si(1);
                        jal(0x430DB8u, &gen::fn_sub_422C10_00422c10);
                        a0 = s1;
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430DD0u, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 16, v0);
                        lwc1(1, s0, 20);
                        v0 = lui(0x42FCu);
                        mtc1(v0, 0);  // 126.0
                        add_s(0, 0, 1);
                        swc1(0, s0, 116);
                        lwc1(0, s0, 24);
                        swc1(0, s0, 120);
                        v0 = si(85);
                        sw(s0, 84, v0);
                        v0 = si(202);
                        sw(s0, 88, v0);
                        a0 = lw(s0, 16);
                        ldr(a1, s0, 116);
                        ldl(a1, s0, 123);
                        a2 = addiu(s0, 76);
                        jal(0x430E1Cu, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 16);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x430E38u, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 16);
                        a1 = si(1);
                        jal(0x430E48u, &gen::fn_sub_422C10_00422c10);
                    } else {
                        charge(151);
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430E64u, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 4, v0);
                        lwc1(0, s0, 20);
                        swc1(0, s0, 92);
                        sw(s0, 96, zero);
                        v0 = si(320);
                        sw(s0, 36, v0);
                        lwc1(0, s0, 24);
                        cvt_w_s(0, 0);
                        mfc1(v0, 0);
                        sw(s0, 40, v0);
                        a0 = lw(s0, 4);
                        ldr(a1, s0, 92);
                        ldl(a1, s0, 99);
                        a2 = addiu(s0, 28);
                        jal(0x430EA8u, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 4);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x430EC4u, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 4);
                        a1 = si(1);
                        jal(0x430ED4u, &gen::fn_sub_422C10_00422c10);
                        a0 = s1;
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430EECu, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 8, v0);
                        lwc1(1, s0, 20);
                        v0 = lui(0x4298u);
                        mtc1(v0, 0);  // 76f
                        sub_s(0, 1, 0);
                        swc1(0, s0, 100);
                        sw(s0, 104, zero);
                        v0 = si(76);
                        sw(s0, 52, v0);
                        lwc1(1, s0, 24);
                        v0 = lui(0x42FCu);
                        mtc1(v0, 0);  // 126.0
                        add_s(0, 0, 1);
                        cvt_w_s(0, 0);
                        mfc1(v0, 0);
                        sw(s0, 56, v0);
                        a0 = lw(s0, 8);
                        ldr(a1, s0, 100);
                        ldl(a1, s0, 107);
                        a2 = addiu(s0, 44);
                        jal(0x430F50u, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 8);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x430F6Cu, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 8);
                        a1 = si(1);
                        jal(0x430F7Cu, &gen::fn_sub_422C10_00422c10);
                        a0 = s1;
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x430F94u, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 12, v0);
                        lwc1(1, s0, 20);
                        v0 = lui(0x4298u);
                        mtc1(v0, 0);  // 76f
                        sub_s(0, 1, 0);
                        swc1(0, s0, 108);
                        lwc1(1, s0, 24);
                        v0 = lui(0x42FCu);
                        mtc1(v0, 0);  // 126.0
                        add_s(0, 0, 1);
                        swc1(0, s0, 112);
                        v0 = si(202);
                        sw(s0, 68, v0);
                        v0 = si(76);
                        sw(s0, 72, v0);
                        a0 = lw(s0, 12);
                        ldr(a1, s0, 108);
                        ldl(a1, s0, 115);
                        a2 = addiu(s0, 60);
                        jal(0x430FF0u, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 12);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x43100Cu, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 12);
                        a1 = si(1);
                        jal(0x43101Cu, &gen::fn_sub_422C10_00422c10);
                        a0 = s1;
                        ldr(a1, s0, 20);
                        ldl(a1, s0, 27);
                        a2 = si(3);
                        jal(0x431034u, &gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                        sw(s0, 16, v0);
                        lwc1(1, s0, 20);
                        v0 = lui(0x42FCu);
                        mtc1(v0, 0);  // 126.0
                        add_s(0, 0, 1);
                        swc1(0, s0, 116);
                        lwc1(0, s0, 24);
                        swc1(0, s0, 120);
                        v0 = si(320);
                        sw(s0, 84, v0);
                        v0 = si(202);
                        sw(s0, 88, v0);
                        a0 = lw(s0, 16);
                        ldr(a1, s0, 116);
                        ldl(a1, s0, 123);
                        a2 = addiu(s0, 76);
                        jal(0x431080u, &gen::fn_sub_422C30_00422c30);
                        a0 = lw(s0, 16);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        a4 = 0;
                        jal(0x43109Cu, &gen::fn_sub_422C90_00422c90);
                        a0 = lw(s0, 16);
                        a1 = si(1);
                        jal(0x4310ACu, &gen::fn_sub_422C10_00422c10);
                    }
                    charge(2);
                    v0 = si(1);
                    sb(s0, 0, v0);
                }
            }
        }
        charge(7);
        v0 = 0;
        ra = ld(sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 48);
    }

    // 0x45A020 ("y_TimeLimit draw" update, [Y_TimeLimit_UpdateTimeLimitDrawTask] bands.sym): with +93 == 1 it returns 0 at
    // once. Else by the state +4 (a jump table at 0x7BC710): 0 requests smap/i_timelimit01.spr (sprAddFile, work +0) -> 1;
    // 1 waits for the file -> 2; 2 waits for +5 == 1 -> 3 (counters +6 / +10 = 0); 3 fades in: +72 = sub_4221A0(1, $f12 =
    // gp[-32044], ..), +6 counts to 10, the s16 +68 to 10 then +72 = 1.0 and state 4, and draws (sub_45A490); 4 draws
    // (sub_45A490, sub_45ACE0); 5 fades out to gp[-32044] -> 6 and draws; 6 returns -1 (done). Other states return 0.
    void Y_TimeLimit_UpdateTimeLimitDrawTask() {
        enter(8);
        sp = addiu(sp, -32);
        sd(sp, 16, ra);
        sq(s0, sp, 0);
        s0 = lw(a0, kTaskWork);
        v0 = lb(s0, 93);
        a0 = si(1);
        if (v0 == a0) {
            charge(3);
            v0 = 0;
        } else {
            charge(4);
            v0 = lb(s0, 4);
            at = sltiu(v0, 8);
            if (at != 0) {
                charge(7);
                v1 = lui(0x7Cu);
                v1 = addiu(v1, -14576);  // 0x7BC710
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v0 = lw(v0, 0);
                switch (w(v0)) {  // jump table 0x7BC710
                default:
                    dispatch(v0);
                    return;
                case 0x45A078u:  // [0]
                    charge(7);
                    a0 = lui(0x6Bu);
                    a0 = addiu(a0, 19392);  // 0x6B4BC0
                    jal(0x45A080u, &gen::fn_sprAddFile_00112370);
                    sw(s0, 0, v0);
                    v0 = si(1);
                    sb(s0, 4, v0);
                case 0x45A094u:  // [1]
                    charge(6);
                    a0 = lw(s0, 0);
                    jal(0x45A098u, &gen::fn_sprFileIsReady_00111f30);
                    v1 = si(1);
                    if (v0 != v1) break;
                    charge(4);
                    v0 = si(2);
                    sb(s0, 4, v0);
                    break;
                case 0x45A0BCu:  // [2]
                    charge(3);
                    v0 = lb(s0, 5);
                    if (v0 != a0) break;
                    charge(6);
                    v0 = si(3);
                    sb(s0, 4, v0);
                    sh(s0, 6, zero);
                    sh(s0, 10, zero);
                    break;
                case 0x45A0E0u:  // [3]
                    charge(17);
                    v0 = lh(s0, 68);
                    mtc1(v0, 0);
                    cvt_s_w(14, 0);
                    v0 = lui(0x3F80u);
                    mtc1(v0, 13);  // 1.0
                    v0 = lui(0x4120u);
                    mtc1(v0, 15);  // 10.0
                    lwc1(12, gp, -32044);
                    jal(0x45A104u, &gen::fn_sub_4221A0_004221a0);
                    swc1(0, s0, 72);
                    sh(s0, 10, zero);
                    v0 = lh(s0, 6);
                    at = slti(v0, 10);
                    if (at != 0) {
                        charge(2);
                        v0 = addiu(v0, 1);
                        sh(s0, 6, v0);
                    }
                    charge(4);
                    v0 = lh(s0, 68);
                    at = slti(v0, 10);
                    if (at != 0) {
                        charge(4);
                        v0 = addiu(v0, 1);
                        sh(s0, 68, v0);
                    } else {
                        charge(4);
                        v0 = lui(0x3F80u);
                        sw(s0, 72, v0);
                        v0 = si(4);
                        sb(s0, 4, v0);
                    }
                    charge(4);
                    jal(0x45A15Cu, &gen::fn_sub_45A490_0045a490);
                    break;
                case 0x45A16Cu:  // [4]
                    charge(6);
                    jal(0x45A16Cu, &gen::fn_sub_45A490_0045a490);
                    jal(0x45A174u, &gen::fn_sub_45ACE0_0045ace0);
                    break;
                case 0x45A184u:  // [5]
                    charge(16);
                    v0 = lh(s0, 68);
                    mtc1(v0, 0);
                    cvt_s_w(14, 0);
                    v0 = lui(0x3F80u);
                    mtc1(v0, 12);  // 1.0
                    v0 = lui(0x4120u);
                    mtc1(v0, 15);  // 10.0
                    lwc1(13, gp, -32044);
                    jal(0x45A1A8u, &gen::fn_sub_4221A0_004221a0);
                    swc1(0, s0, 72);
                    v0 = lh(s0, 68);
                    at = slti(v0, 10);
                    if (at != 0) {
                        charge(4);
                        v0 = addiu(v0, 1);
                        sh(s0, 68, v0);
                    } else {
                        charge(4);
                        lwc1(0, gp, -32044);
                        swc1(0, s0, 72);
                        v0 = si(6);
                        sb(s0, 4, v0);
                    }
                    charge(4);
                    jal(0x45A1E4u, &gen::fn_sub_45A490_0045a490);
                    break;
                case 0x45A1F4u:  // [6]
                    charge(3);
                    v0 = si(-1);
                    charge(5);
                    ra = ld(sp, 16);
                    lq(s0, sp, 0);
                    sp = addiu(sp, 32);
                    return;
                case 0x45A200u:  // [7]
                    break;
                }
            }
            charge(1);
            v0 = 0;
        }
        charge(5);
        ra = ld(sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 32);
    }
};

// @@STRUCTS@@

}  // namespace

// --- typed entry points -------------------------------------------------------------------------------------------------
void sub_429E80(EEContext& ctx, u64 task, u64 shown) { set_args(ctx, {task, shown}); SMapLeaves{ctx}.sub_429E80(); }
void sub_429E90(EEContext& ctx, u64 task, u64 frozen) { set_args(ctx, {task, frozen}); SMapLeaves{ctx}.sub_429E90(); }
u32 sub_429EF0(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SMapLeaves{ctx}.sub_429EF0(); return ctx.fpr[0]; }
u32 sub_429FE0(EEContext& ctx, u64 pc) { set_args(ctx, {pc}); SMapLeaves{ctx}.sub_429FE0(); return ctx.fpr[0]; }
u32 sub_42A230(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); SMapLeaves{ctx}.sub_42A230(); return ctx.fpr[0]; }
u32 sub_42A310(EEContext& ctx, u64 ec) { set_args(ctx, {ec}); SMapLeaves{ctx}.sub_42A310(); return ctx.fpr[0]; }
u32 sub_42A0D0(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); SMapLeaves{ctx}.sub_42A0D0(); return ctx.fpr[0]; }
u32 sub_42A180(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); SMapLeaves{ctx}.sub_42A180(); return ctx.fpr[0]; }
u32 sub_42A3F0(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); SMapLeaves{ctx}.sub_42A3F0(); return ctx.fpr[0]; }
u32 sub_42A4A0(EEContext& ctx, u64 pos) { set_args(ctx, {pos}); SMapLeaves{ctx}.sub_42A4A0(); return ctx.fpr[0]; }
u32 sub_42BA30(EEContext& ctx) { SMapLeaves{ctx}.sub_42BA30(); return static_cast<u32>(v0_of(ctx)); }
void sub_430220(EEContext& ctx, u64 task, u64 xy) { set_args(ctx, {task, xy}); SMapLeaves{ctx}.sub_430220(); }
void sub_430270(EEContext& ctx, u64 out, u64 task) { set_args(ctx, {out, task}); SMapLeaves{ctx}.sub_430270(); }
void sub_4302A0(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapLeaves{ctx}.sub_4302A0(); }
void sub_4311F0(EEContext& ctx, u64 out, u64 x, u64 z) { set_args(ctx, {out, x, z}); SMapLeaves{ctx}.sub_4311F0(); }
void sub_42ADB0(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapDraw{ctx}.sub_42ADB0(); }
void sub_42B050(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapDraw{ctx}.sub_42B050(); }
void sub_42B540(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapDraw{ctx}.sub_42B540(); }
void sub_42FD80(EEContext& ctx, u64 out, u64 task) { set_args(ctx, {out, task}); SMapDraw{ctx}.sub_42FD80(); }
s32 Y_SMap_UpdateStaireDispTask(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapDraw{ctx}.Y_SMap_UpdateStaireDispTask(); return static_cast<s32>(v0_of(ctx)); }
void sub_430630(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapDraw{ctx}.sub_430630(); }
void sub_430780(EEContext& ctx, u64 offset, u64 x, u64 y, u64 frame) {
    set_args(ctx, {offset, x, y, frame});
    SMapDraw{ctx}.sub_430780();
}
void sub_430A40(EEContext& ctx, u64 row) { set_args(ctx, {row}); SMapDraw{ctx}.sub_430A40(); }
void sub_42A550(EEContext& ctx, u64 task, u64 pc, u64 x, u64 z) { set_args(ctx, {task, pc, x, z}); SMapSetup{ctx}.sub_42A550(); }
void sub_42BA50(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapSetup{ctx}.sub_42BA50(); }
void sub_42BC10(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapSetup{ctx}.sub_42BC10(); }
void sub_42BD80(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapSetup{ctx}.sub_42BD80(); }
void sub_42BFD0(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapSetup{ctx}.sub_42BFD0(); }

void sub_42C0A0(EEContext& ctx, u64 task, u64 pc, u64 x, u64 z, u64 ox, u64 oz) { set_args(ctx, {task, pc, x, z, ox, oz}); SMapMarks{ctx}.sub_42C0A0(); }
void sub_42CD80(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapMarks{ctx}.sub_42CD80(); }
void sub_42CFC0(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz) { set_args(ctx, {task, x, z, ox, oz}); SMapObjects{ctx}.sub_42CFC0(); }
void sub_42DD90(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz) { set_args(ctx, {task, x, z, ox, oz}); SMapObjects{ctx}.sub_42DD90(); }
void sub_42EA60(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz) { set_args(ctx, {task, x, z, ox, oz}); SMapObjects{ctx}.sub_42EA60(); }
void sub_42F440(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz) { set_args(ctx, {task, x, z, ox, oz}); SMapObjects{ctx}.sub_42F440(); }
s32 Y_SMap_UpdateSmapMaskDrawTask(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapObjects{ctx}.Y_SMap_UpdateSmapMaskDrawTask(); return static_cast<s32>(v0_of(ctx)); }
s32 Y_TimeLimit_UpdateTimeLimitDrawTask(EEContext& ctx, u64 task) { set_args(ctx, {task}); SMapObjects{ctx}.Y_TimeLimit_UpdateTimeLimitDrawTask(); return static_cast<s32>(v0_of(ctx)); }
// @@API@@
}  // namespace p3fes::game

// =====================================================================================================================
// The recompiled program's entry points (recomp/generated/functions.h signatures)
// =====================================================================================================================
namespace p3fes::recomp_gen {
namespace g = p3fes::game;
void fn_sub_429E80_00429e80(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_429E80(); }
void fn_sub_429E90_00429e90(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_429E90(); }
void fn_sub_429EF0_00429ef0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_429EF0(); }
void fn_sub_429FE0_00429fe0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_429FE0(); }
void fn_sub_42A230_0042a230(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42A230(); }
void fn_sub_42A310_0042a310(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42A310(); }
void fn_sub_42A0D0_0042a0d0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42A0D0(); }
void fn_sub_42A180_0042a180(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42A180(); }
void fn_sub_42A3F0_0042a3f0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42A3F0(); }
void fn_sub_42A4A0_0042a4a0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42A4A0(); }
void fn_sub_42BA30_0042ba30(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_42BA30(); }
void fn_sub_430220_00430220(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_430220(); }
void fn_sub_430270_00430270(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_430270(); }
void fn_sub_4302A0_004302a0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_4302A0(); }
void fn_sub_4311F0_004311f0(p3fes::EEContext& ctx) { g::SMapLeaves{ctx}.sub_4311F0(); }
void fn_sub_42ADB0_0042adb0(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_42ADB0(); }
void fn_sub_42B050_0042b050(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_42B050(); }
void fn_sub_42B540_0042b540(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_42B540(); }
void fn_sub_42FD80_0042fd80(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_42FD80(); }
void fn_Y_SMap_UpdateStaireDispTask_00430060(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.Y_SMap_UpdateStaireDispTask(); }
void fn_sub_430630_00430630(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_430630(); }
void fn_sub_430780_00430780(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_430780(); }
void fn_sub_430A40_00430a40(p3fes::EEContext& ctx) { g::SMapDraw{ctx}.sub_430A40(); }
void fn_sub_42A550_0042a550(p3fes::EEContext& ctx) { g::SMapSetup{ctx}.sub_42A550(); }
void fn_sub_42BA50_0042ba50(p3fes::EEContext& ctx) { g::SMapSetup{ctx}.sub_42BA50(); }
void fn_sub_42BC10_0042bc10(p3fes::EEContext& ctx) { g::SMapSetup{ctx}.sub_42BC10(); }
void fn_sub_42BD80_0042bd80(p3fes::EEContext& ctx) { g::SMapSetup{ctx}.sub_42BD80(); }
void fn_sub_42BFD0_0042bfd0(p3fes::EEContext& ctx) { g::SMapSetup{ctx}.sub_42BFD0(); }
void fn_sub_42C0A0_0042c0a0(p3fes::EEContext& ctx) { g::SMapMarks{ctx}.sub_42C0A0(); }
void fn_sub_42CD80_0042cd80(p3fes::EEContext& ctx) { g::SMapMarks{ctx}.sub_42CD80(); }
void fn_sub_42CFC0_0042cfc0(p3fes::EEContext& ctx) { g::SMapObjects{ctx}.sub_42CFC0(); }
void fn_sub_42DD90_0042dd90(p3fes::EEContext& ctx) { g::SMapObjects{ctx}.sub_42DD90(); }
void fn_sub_42EA60_0042ea60(p3fes::EEContext& ctx) { g::SMapObjects{ctx}.sub_42EA60(); }
void fn_sub_42F440_0042f440(p3fes::EEContext& ctx) { g::SMapObjects{ctx}.sub_42F440(); }
void fn_Y_SMap_UpdateSmapMaskDrawTask_00430bb0(p3fes::EEContext& ctx) { g::SMapObjects{ctx}.Y_SMap_UpdateSmapMaskDrawTask(); }
void fn_Y_TimeLimit_UpdateTimeLimitDrawTask_0045a020(p3fes::EEContext& ctx) { g::SMapObjects{ctx}.Y_TimeLimit_UpdateTimeLimitDrawTask(); }
// @@SHIMS@@
}  // namespace p3fes::recomp_gen
