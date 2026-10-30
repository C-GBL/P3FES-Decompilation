// Slice render_rw5: RenderWare, fifth pass -- the device-independent scene logic (the group overview and the record
// layouts are in game/include/p3fes/game/render_rw5.h). Every body started as p3fes_handgen's output and keeps the
// recompiled body's registers, frame, spills, $ra links, cycle charges and check points statement for statement
// (game/include/p3fes/game/hg_cpu.h); what was added is the role of each function, the role of its main blocks, the
// names of the record offsets (rw4:: / rw5::) and the labels of the RW globals. sub_* keep their symbols/functions.json
// names; proposed names are in brackets (symbols/deltas/render_rw5.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw5.h"

namespace p3fes::recomp_gen {
void fn_CameraBeginUpdate_004c9ba0(p3fes::EEContext&);
void fn_CameraEndUpdate_004c9b40(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_sub_45EC40_0045ec40(p3fes::EEContext&);
void fn_sub_45EDC0_0045edc0(p3fes::EEContext&);
void fn_sub_45EDD0_0045edd0(p3fes::EEContext&);
void fn_sub_45EE00_0045ee00(p3fes::EEContext&);
void fn_sub_45EFE0_0045efe0(p3fes::EEContext&);
void fn_sub_45F140_0045f140(p3fes::EEContext&);
void fn_sub_45F490_0045f490(p3fes::EEContext&);
void fn_sub_45F4C0_0045f4c0(p3fes::EEContext&);
void fn_sub_45F4E0_0045f4e0(p3fes::EEContext&);
void fn_sub_45F530_0045f530(p3fes::EEContext&);
void fn_sub_45F540_0045f540(p3fes::EEContext&);
void fn_sub_45F600_0045f600(p3fes::EEContext&);
void fn_sub_45F7B0_0045f7b0(p3fes::EEContext&);
void fn_sub_464280_00464280(p3fes::EEContext&);
void fn_sub_490690_00490690(p3fes::EEContext&);
void fn_sub_4906B0_004906b0(p3fes::EEContext&);
void fn_sub_4906F0_004906f0(p3fes::EEContext&);
void fn_sub_490770_00490770(p3fes::EEContext&);
void fn_sub_4907E0_004907e0(p3fes::EEContext&);
void fn_sub_490CA0_00490ca0(p3fes::EEContext&);
void fn_sub_490CC0_00490cc0(p3fes::EEContext&);
void fn_sub_490CD0_00490cd0(p3fes::EEContext&);
void fn_sub_490CF0_00490cf0(p3fes::EEContext&);
void fn_sub_490D00_00490d00(p3fes::EEContext&);
void fn_sub_491410_00491410(p3fes::EEContext&);
void fn_sub_4914D0_004914d0(p3fes::EEContext&);
void fn_sub_4915C0_004915c0(p3fes::EEContext&);
void fn_sub_491760_00491760(p3fes::EEContext&);
void fn_sub_4917F0_004917f0(p3fes::EEContext&);
void fn_sub_491DE0_00491de0(p3fes::EEContext&);
void fn_sub_491FF0_00491ff0(p3fes::EEContext&);
void fn_sub_492020_00492020(p3fes::EEContext&);
void fn_sub_492060_00492060(p3fes::EEContext&);
void fn_sub_492C30_00492c30(p3fes::EEContext&);
void fn_sub_492C60_00492c60(p3fes::EEContext&);
void fn_sub_492C90_00492c90(p3fes::EEContext&);
void fn_sub_492CC0_00492cc0(p3fes::EEContext&);
void fn_sub_492CE0_00492ce0(p3fes::EEContext&);
void fn_sub_492D00_00492d00(p3fes::EEContext&);
void fn_sub_492DE0_00492de0(p3fes::EEContext&);
void fn_sub_492E00_00492e00(p3fes::EEContext&);
void fn_sub_492E20_00492e20(p3fes::EEContext&);
void fn_sub_492F80_00492f80(p3fes::EEContext&);
void fn_sub_493210_00493210(p3fes::EEContext&);
void fn_sub_493230_00493230(p3fes::EEContext&);
void fn_sub_493B40_00493b40(p3fes::EEContext&);
void fn_sub_493C50_00493c50(p3fes::EEContext&);
void fn_sub_493C80_00493c80(p3fes::EEContext&);
void fn_sub_494490_00494490(p3fes::EEContext&);
void fn_sub_4944A0_004944a0(p3fes::EEContext&);
void fn_sub_4944B0_004944b0(p3fes::EEContext&);
void fn_sub_494520_00494520(p3fes::EEContext&);
void fn_sub_494550_00494550(p3fes::EEContext&);
void fn_sub_494760_00494760(p3fes::EEContext&);
void fn_sub_4947C0_004947c0(p3fes::EEContext&);
void fn_sub_4948B0_004948b0(p3fes::EEContext&);
void fn_sub_494930_00494930(p3fes::EEContext&);
void fn_sub_4949C0_004949c0(p3fes::EEContext&);
void fn_sub_494A40_00494a40(p3fes::EEContext&);
void fn_sub_494AB0_00494ab0(p3fes::EEContext&);
void fn_sub_494AE0_00494ae0(p3fes::EEContext&);
void fn_sub_494B70_00494b70(p3fes::EEContext&);
void fn_sub_494BE0_00494be0(p3fes::EEContext&);
void fn_sub_494DB0_00494db0(p3fes::EEContext&);
void fn_sub_494DE0_00494de0(p3fes::EEContext&);
void fn_sub_494E10_00494e10(p3fes::EEContext&);
void fn_sub_495300_00495300(p3fes::EEContext&);
void fn_sub_495340_00495340(p3fes::EEContext&);
void fn_sub_495480_00495480(p3fes::EEContext&);
void fn_sub_4959C0_004959c0(p3fes::EEContext&);
void fn_sub_4959E0_004959e0(p3fes::EEContext&);
void fn_sub_495A30_00495a30(p3fes::EEContext&);
void fn_sub_495B10_00495b10(p3fes::EEContext&);
void fn_sub_495C20_00495c20(p3fes::EEContext&);
void fn_sub_495C80_00495c80(p3fes::EEContext&);
void fn_sub_495CF0_00495cf0(p3fes::EEContext&);
void fn_sub_499140_00499140(p3fes::EEContext&);
void fn_sub_4991F0_004991f0(p3fes::EEContext&);
void fn_sub_499210_00499210(p3fes::EEContext&);
void fn_sub_499250_00499250(p3fes::EEContext&);
void fn_sub_499280_00499280(p3fes::EEContext&);
void fn_sub_4992B0_004992b0(p3fes::EEContext&);
void fn_sub_4992D0_004992d0(p3fes::EEContext&);
void fn_sub_499400_00499400(p3fes::EEContext&);
void fn_sub_499D30_00499d30(p3fes::EEContext&);
void fn_sub_499E90_00499e90(p3fes::EEContext&);
void fn_sub_499F40_00499f40(p3fes::EEContext&);
void fn_sub_499FD0_00499fd0(p3fes::EEContext&);
void fn_sub_49A080_0049a080(p3fes::EEContext&);
void fn_sub_49A7C0_0049a7c0(p3fes::EEContext&);
void fn_sub_49A920_0049a920(p3fes::EEContext&);
void fn_sub_49A950_0049a950(p3fes::EEContext&);
void fn_sub_49AAF0_0049aaf0(p3fes::EEContext&);
void fn_sub_49ABF0_0049abf0(p3fes::EEContext&);
void fn_sub_49AC90_0049ac90(p3fes::EEContext&);
void fn_sub_49ACD0_0049acd0(p3fes::EEContext&);
void fn_sub_49ACF0_0049acf0(p3fes::EEContext&);
void fn_sub_49AD80_0049ad80(p3fes::EEContext&);
void fn_sub_49ADE0_0049ade0(p3fes::EEContext&);
void fn_sub_49AE30_0049ae30(p3fes::EEContext&);
void fn_sub_49AEB0_0049aeb0(p3fes::EEContext&);
void fn_sub_49AF20_0049af20(p3fes::EEContext&);
void fn_sub_49AFA0_0049afa0(p3fes::EEContext&);
void fn_sub_49B180_0049b180(p3fes::EEContext&);
void fn_sub_49B290_0049b290(p3fes::EEContext&);
void fn_sub_49B2D0_0049b2d0(p3fes::EEContext&);
void fn_sub_49B2E0_0049b2e0(p3fes::EEContext&);
void fn_sub_49B3C0_0049b3c0(p3fes::EEContext&);
void fn_sub_49B430_0049b430(p3fes::EEContext&);
void fn_sub_49B440_0049b440(p3fes::EEContext&);
void fn_sub_49B730_0049b730(p3fes::EEContext&);
void fn_sub_49B760_0049b760(p3fes::EEContext&);
void fn_sub_49B7A0_0049b7a0(p3fes::EEContext&);
void fn_sub_49B850_0049b850(p3fes::EEContext&);
void fn_sub_49BBC0_0049bbc0(p3fes::EEContext&);
void fn_sub_49BBF0_0049bbf0(p3fes::EEContext&);
void fn_sub_49BC20_0049bc20(p3fes::EEContext&);
void fn_sub_49C160_0049c160(p3fes::EEContext&);
void fn_sub_49C1B0_0049c1b0(p3fes::EEContext&);
void fn_sub_49C1E0_0049c1e0(p3fes::EEContext&);
void fn_sub_49C230_0049c230(p3fes::EEContext&);
void fn_sub_49C3D0_0049c3d0(p3fes::EEContext&);
void fn_sub_49C480_0049c480(p3fes::EEContext&);
void fn_sub_49C560_0049c560(p3fes::EEContext&);
void fn_sub_49C5C0_0049c5c0(p3fes::EEContext&);
void fn_sub_49C620_0049c620(p3fes::EEContext&);
void fn_sub_49C790_0049c790(p3fes::EEContext&);
void fn_sub_4C15A0_004c15a0(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C17F0_004c17f0(p3fes::EEContext&);
void fn_sub_4C1820_004c1820(p3fes::EEContext&);
void fn_sub_4C1850_004c1850(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C3B50_004c3b50(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C4200_004c4200(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C53F0_004c53f0(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C61B0_004c61b0(p3fes::EEContext&);
void fn_sub_4C64B0_004c64b0(p3fes::EEContext&);
void fn_sub_4C6560_004c6560(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6AF0_004c6af0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6C20_004c6c20(p3fes::EEContext&);
void fn_sub_4C6CA0_004c6ca0(p3fes::EEContext&);
void fn_sub_4C6CE0_004c6ce0(p3fes::EEContext&);
void fn_sub_4C7A50_004c7a50(p3fes::EEContext&);
void fn_sub_4C89A0_004c89a0(p3fes::EEContext&);
void fn_sub_4C8A60_004c8a60(p3fes::EEContext&);
void fn_sub_4C9270_004c9270(p3fes::EEContext&);
void fn_sub_4C9400_004c9400(p3fes::EEContext&);
void fn_sub_4C9940_004c9940(p3fes::EEContext&);
void fn_sub_4C9AD0_004c9ad0(p3fes::EEContext&);
void fn_sub_4C9C00_004c9c00(p3fes::EEContext&);
void fn_sub_4C9C70_004c9c70(p3fes::EEContext&);
void fn_sub_4C9D20_004c9d20(p3fes::EEContext&);
void fn_sub_4C9DB0_004c9db0(p3fes::EEContext&);
void fn_sub_4C9F00_004c9f00(p3fes::EEContext&);
void fn_sub_4C9F90_004c9f90(p3fes::EEContext&);
void fn_sub_4CA000_004ca000(p3fes::EEContext&);
void fn_sub_4CA090_004ca090(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CBC70_004cbc70(p3fes::EEContext&);
void fn_sub_4CBE00_004cbe00(p3fes::EEContext&);
void fn_sub_4CBEB0_004cbeb0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CC050_004cc050(p3fes::EEContext&);
void fn_sub_4CC6B0_004cc6b0(p3fes::EEContext&);
void fn_sub_4CD750_004cd750(p3fes::EEContext&);
void fn_sub_4CF340_004cf340(p3fes::EEContext&);
void fn_sub_4D18C0_004d18c0(p3fes::EEContext&);
void fn_sub_4F23C0_004f23c0(p3fes::EEContext&);
void fn_sub_4F2430_004f2430(p3fes::EEContext&);
void fn_sub_4F28E0_004f28e0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rw4;
using namespace rw5;

namespace gen = ::p3fes::recomp_gen;

// sub_45EC40 [collTreeCreate] -- allocates a collision block for a sector / geometry
// ($a0 = triangles, $a1 = splits, $a2 = the box, $a3 = flags) 40 bytes + 16 per split (16-aligned) + 2 per triangle
// with a triangle map (flags bit 0); the header gets the flags, the counts and the box, then the split and map
// pointers into the same block. error 0x80000013 (out of memory) and 0 when the allocation fails (under plugin id 0x11D).
// 0x0045EC40 sub_45EC40 -- 372 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45EC40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0045ec40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    s0 = s4 & 0xFFFF;
    s1 = 40;
    if (i64(s0) > 0) {
        // 0x0045ec80: 16 bytes per split (+15 for the 16-byte alignment)
        charge(ctx, 4);
        v0 = sll(s0, 4);
        v0 = addiu(v0, 15);
        s1 = addu(s1, v0);
    }
    // 0x0045ed44
    charge(ctx, 3);
    s6 = s2 & 0x1;
    if (s6 == 0) {
        backedge(ctx);
    } else {
        // 0x0045ed50: a triangle map: 2 bytes per triangle (+1 for the 2-byte alignment)
        charge(ctx, 2);
        v0 = s5 & 0xFFFF;
        backedge(ctx);
        // 0x0045ec90
        charge(ctx, 3);
        v0 = sll(v0, 1);
        v0 = addiu(v0, 1);
        s1 = addu(s1, v0);
    }
    // 0x0045ec9c: RwMalloc(size, 0x3002C)
    charge(ctx, 8);
    v0 = 0x30000;
    a1 = v0 | 0x2C;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = s1;
    jalr(ctx, 0x45ECACu, v0.u());
    if (v0 == 0) {
        // 0x0045ed58: out of memory: error 0x80000013 for plugin 0x11D, return 0
        charge(ctx, 11);
        v0 = 285;
        a1 = s1;
        sw(v0, sp, 0x88);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x45ED68u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x8C);
        a0 = addiu(sp, 0x88);
        jal(ctx, 0x45ED74u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x0045ecbc: fill the header: flags, counts, the box (the argument's maximum, then its minimum)
        charge(ctx, 18);
        sw(s2, v0, coll::kFlags);
        a1 = v0;
        sh(s5, v0, coll::kNumTriangles);
        sh(s4, v0, coll::kNumSplits);
        lwc1(f3, s3, 0);
        lwc1(f2, s3, 4);
        lwc1(f1, s3, 8);
        lwc1(f0, s3, 12);
        swc1(f3, v0, coll::kBoxSup);
        swc1(f2, v0, 8);
        swc1(f1, v0, 12);
        swc1(f0, v0, coll::kBoxInf);
        lwc1(f1, s3, 16);
        lwc1(f0, s3, 20);
        swc1(f1, v0, 20);
        swc1(f0, v0, 24);
        v0 = addiu(v0, 40);
        if (i64(s0) <= 0) {
            // 0x0045ed84
            charge(ctx, 2);
            sw(zero, a1, coll::kSplits);
            backedge(ctx);
        } else {
            // 0x0045ed04: the split array, 16-aligned after the 40-byte header
            charge(ctx, 6);
            a0 = addiu(v0, 15);
            v1 = sll(s0, 4);
            v0 = si(-16);
            a0 = a0 & v0;
            v0 = addu(a0, v1);
            sw(a0, a1, coll::kSplits);
        }
        // 0x0045ed1c
        charge(ctx, 2);
        if (s6 == 0) {
            // 0x0045ed38
            charge(ctx, 1);
            sw(zero, a1, coll::kTriMap);
        } else {
            // 0x0045ed24: the triangle map after the splits, 2-aligned
            charge(ctx, 5);
            v1 = addiu(v0, 1);
            v0 = si(-2);
            v0 = v1 & v0;
            sw(v0, a1, coll::kTriMap);
        }
        // 0x0045ed3c
        charge(ctx, 2);
        v0 = a1;
    }
    // 0x0045ed8c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_45EDC0 [collTreeDestroy] -- frees a collision block (RwFree, a tail call through 0x96017C)
// 0x0045EDC0 sub_45EDC0 -- 16 bytes; leaf frame (no stack)
void sub_45EDC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0045edc0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_45EDD0 [collTreeStreamGetSize] -- the payload of a collision chunk: 48 + 16 per split (+ 2 per triangle with a map)
// 0x0045EDD0 sub_45EDD0 -- 48 bytes; leaf frame (no stack)
void sub_45EDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0045edd0
    enter(ctx, 7);  // entry check point + this block's cycles
    lhu(v0, a0, coll::kNumSplits);
    a1 = 48;
    lw(v1, a0, coll::kFlags);
    v0 = sll(v0, 4);
    v1 = v1 & 0x1;
    v0 = addu(a1, v0);
    if (v1 != 0) {
        // 0x0045edec
        charge(ctx, 3);
        lhu(v1, a0, coll::kNumTriangles);
        v1 = sll(v1, 1);
        v0 = addu(v0, v1);
    }
    // 0x0045edf8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_45EE00 [collTreeStreamWrite] -- writes a collision block as a chunk
// The collision chunk header (type 0x2C) and its struct chunk header (version 0x37002, build 55), the 36-byte header
// record (flags, the minimum, the maximum, triangles, splits), the splits and the triangle map. Returns the block or 0.
// 0x0045EE00 sub_45EE00 -- 468 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45EE00(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x0045ee00
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    lhu(v1, a0, coll::kNumSplits);
    lw(v0, a0, coll::kFlags);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    a1 = 48;
    v1 = sll(v1, 4);
    v0 = v0 & 0x1;
    s0 = addu(a1, v1);
    if (v0 != 0) {
        // 0x0045ee3c
        charge(ctx, 3);
        lhu(v0, s3, coll::kNumTriangles);
        v0 = sll(v0, 1);
        s0 = addu(s0, v0);
    }
    // 0x0045ee48: the collision chunk header (type 0x2C)
    charge(ctx, 9);
    v0 = 0x30000;
    a0 = s2;
    a1 = 44;
    a2 = s0;
    a3 = v0 | 0x7002;
    t0 = 55;
    jal(ctx, 0x45EE5Cu, gen::fn_sub_4C15A0_004c15a0);
    if (v0 != 0) {
        // 0x0045ee74: the struct chunk header (type 1, the size less 12)
        charge(ctx, 9);
        v0 = 0x30000;
        a2 = addiu(s0, -12);
        a0 = s2;
        a1 = 1;
        a3 = v0 | 0x7002;
        t0 = 55;
        jal(ctx, 0x45EE88u, gen::fn_sub_4C15A0_004c15a0);
        if (v0 != 0) {
            // 0x0045eea0: the 36-byte header record on the stack: flags, minimum, maximum, triangles, splits
            charge(ctx, 24);
            lwc1(f5, s3, coll::kBoxInf);
            lw(a3, s3, coll::kFlags);
            lwc1(f4, s3, 20);
            lhu(v1, s3, coll::kNumTriangles);
            lwc1(f3, s3, 24);
            lhu(v0, s3, coll::kNumSplits);
            lwc1(f2, s3, coll::kBoxSup);
            a0 = s2;
            lwc1(f1, s3, 8);
            a1 = addiu(sp, 0x60);
            lwc1(f0, s3, 12);
            a2 = 36;
            swc1(f5, sp, 0x64);
            sw(a3, sp, 0x60);
            swc1(f4, sp, 0x68);
            sw(v1, sp, 0x7C);
            swc1(f3, sp, 0x6C);
            sw(v0, sp, 0x80);
            swc1(f2, sp, 0x70);
            swc1(f1, sp, 0x74);
            link(ctx, 0x45EEF0u);  // $ra first: the delay slot below depends on it
            swc1(f0, sp, 0x78);
            call(ctx, gen::fn_sub_4C53F0_004c53f0);
            if (v0 == 0) {
                // 0x0045ef90
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0045ef00
                charge(ctx, 3);
                lhu(v0, s3, coll::kNumSplits);
                if (i64(v0) > 0) {
                    // 0x0045ef0c
                    charge(ctx, 3);
                    at = sltu(0, v0);
                    s1 = 0;
                    if (at == 0) {
                        goto L_0045ef78;
                    }
                    // 0x0045ef18: each split (16 bytes) through a stack copy
                    charge(ctx, 1);
                    s0 = 0;
                    for (;;) {
                        // 0x0045ef1c
                        charge(ctx, 16);
                        lw(v0, s3, coll::kSplits);
                        a1 = addiu(sp, 0x50);
                        a0 = s2;
                        a2 = 16;
                        v0 = addu(v0, s0);
                        lwc1(f3, v0, 0);
                        lwc1(f2, v0, 4);
                        lwc1(f1, v0, 8);
                        lwc1(f0, v0, 12);
                        swc1(f3, sp, 0x50);
                        swc1(f2, sp, 0x54);
                        swc1(f1, sp, 0x58);
                        link(ctx, 0x45EF4Cu);  // $ra first: the delay slot below depends on it
                        swc1(f0, sp, 0x5C);
                        call(ctx, gen::fn_sub_4C53F0_004c53f0);
                        if (v0 == 0) {
                            goto L_0045ef5c_11;
                        }
                        // 0x0045ef64
                        charge(ctx, 5);
                        lhu(v0, s3, coll::kNumSplits);
                        s1 = addiu(s1, 1);
                        v0 = sltu(s1, v0);
                        s0 = addiu(s0, 16);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    goto L_0045ef78;
                }
            L_0045ef78:
                charge(ctx, 4);
                lw(v0, s3, coll::kFlags);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x0045ef98: the triangle map (2 bytes a triangle, sub_4C1820)
                    charge(ctx, 7);
                    lhu(v0, s3, coll::kNumTriangles);
                    a0 = s2;
                    lw(a1, s3, coll::kTriMap);
                    a2 = sll(v0, 1);
                    jal(ctx, 0x45EFA4u, gen::fn_sub_4C1820_004c1820);
                    if (v0 != 0) {
                        backedge(ctx);
                        goto L_0045ef88;
                    }
                    // 0x0045efb4
                    charge(ctx, 1);
                    v0 = 0;
                    // 0x0045efb8 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    ld(ra, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x90);
                    return;
                }
            L_0045ef88:
                charge(ctx, 2);
                v0 = s3;
            }
        } else {
            // 0x0045ee98
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0045ee6c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0045efb8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
    return;
L_0045ef5c_11:
    charge(ctx, 2);
    v0 = 0;
    // 0x0045efb8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_45EFE0 [collTreeStreamRead] -- reads a collision chunk's struct: the header record, the block, the splits, the map
// Finds the struct chunk, reads the 36-byte header, creates the block (sub_45EC40: its counts, its box -- stored
// minimum first in the stream -- and its flags), then the splits and the triangle map; a short read frees the block
// (RwFree) and returns 0.
// 0x0045EFE0 sub_45EFE0 -- 340 bytes; frame 0x90: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45EFE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x0045efe0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    a1 = 1;
    sd(ra, sp, 0x30);
    a2 = 0;
    sq(s2, sp, 0x20);
    a3 = addiu(sp, 0x8C);
    sq(s1, sp, 0x10);
    s1 = a0;
    link(ctx, 0x45F000u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 != 0) {
        // 0x0045f018: read the 36-byte header record
        charge(ctx, 7);
        a0 = s1;
        a1 = addiu(sp, 0x60);
        a2 = 36;
        jal(ctx, 0x45F020u, gen::fn_sub_4C5250_004c5250);
        v1 = 36;
        if (v0 == v1) {
            // 0x0045f03c: the box from the record (the stream holds the minimum first) and sub_45EC40
            charge(ctx, 20);
            lwc1(f5, sp, 0x64);
            lhu(a0, sp, 0x7C);
            lwc1(f4, sp, 0x68);
            lhu(a1, sp, 0x80);
            lwc1(f3, sp, 0x6C);
            lw(a3, sp, 0x60);
            lwc1(f2, sp, 0x70);
            a2 = addiu(sp, 0x40);
            lwc1(f1, sp, 0x74);
            lwc1(f0, sp, 0x78);
            swc1(f5, sp, 0x4C);
            swc1(f4, sp, 0x50);
            swc1(f3, sp, 0x54);
            swc1(f2, sp, 0x40);
            swc1(f1, sp, 0x44);
            link(ctx, 0x45F078u);  // $ra first: the delay slot below depends on it
            swc1(f0, sp, 0x48);
            call(ctx, gen::fn_sub_45EC40_0045ec40);
            s0 = v0;
            if (s0 == 0) {
                // 0x0045f0b0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0045f08c
                charge(ctx, 3);
                lhu(v0, s0, coll::kNumSplits);
                if (i64(v0) > 0) {
                    // 0x0045f0b8: the splits
                    charge(ctx, 7);
                    lw(a1, s0, coll::kSplits);
                    s2 = sll(v0, 4);
                    a0 = s1;
                    a2 = s2;
                    jal(ctx, 0x45F0C4u, gen::fn_sub_4C5250_004c5250);
                    if (s2 == v0) {
                        backedge(ctx);
                        goto L_0045f098;
                    }
                    // 0x0045f0d4: a short read: free the block, 0
                    charge(ctx, 6);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                    a0 = s0;
                    jalr(ctx, 0x45F0DCu, v0.u());
                    v0 = 0;
                    // 0x0045f11c (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x90);
                    return;
                }
            L_0045f098:
                charge(ctx, 4);
                lw(v0, s0, coll::kFlags);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x0045f0ec: the triangle map
                    charge(ctx, 7);
                    lhu(v0, s0, coll::kNumTriangles);
                    a0 = s1;
                    lw(a1, s0, coll::kTriMap);
                    a2 = sll(v0, 1);
                    jal(ctx, 0x45F0F8u, gen::fn_sub_4C1850_004c1850);
                    if (v0 != 0) {
                        backedge(ctx);
                        goto L_0045f0a8;
                    }
                    // 0x0045f108: a short read: free the block, 0
                    charge(ctx, 5);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                    a0 = s0;
                    jalr(ctx, 0x45F110u, v0.u());
                    v0 = 0;
                    // 0x0045f11c (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x90);
                    return;
                }
            L_0045f0a8:
                charge(ctx, 2);
                v0 = s0;
            }
        } else {
            // 0x0045f034
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0045f010
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0045f11c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_45F140 [collTreeStreamReadOld] -- reads the collision data of the older layout (library ids before 0x36001)
// ($a0 = the stream, $a1 / $a2 = the counts, $a3 = the box, $t0 = the error flag) A block with a triangle map; each
// split from two words and two floats (its type bytes and child links decoded), then the child links rebuilt with an
// explicit stack; an index >= 240 is corrupt data (the flag set, error 1 for plugin 0x11D, the block freed); then the
// triangle map, one word per entry. Returns the block or 0.
// 0x0045F140 sub_45F140 -- 836 bytes; frame 0x110: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45F140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045f140
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s2 = a0;
    sq(s1, sp, 0x10);
    a0 = a1 & 0xFFFF;
    sq(s0, sp, 0x0);
    a1 = a2 & 0xFFFF;
    sw(zero, t0, 0);
    a2 = a3;
    s1 = t0;
    a3 = 1;
    jal(ctx, 0x45F174u, gen::fn_sub_45EC40_0045ec40);
    s0 = v0;
    if (s0 == 0) {
        // 0x0045f278
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0045f188
        charge(ctx, 3);
        lhu(v0, s0, coll::kNumSplits);
        if (i64(v0) <= 0) {
            // 0x0045f43c
            charge(ctx, 5);
            a0 = s2;
            a1 = 4;
            jal(ctx, 0x45F440u, gen::fn_sub_4C5620_004c5620);
            if (v0 != 0) {
                backedge(ctx);
            L_0045f1f8:
                charge(ctx, 4);
                lw(v0, s0, coll::kFlags);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x0045f208
                    charge(ctx, 4);
                    lhu(v0, s0, coll::kNumTriangles);
                    at = sltu(0, v0);
                    s3 = 0;
                    if (at == 0) {
                        goto L_0045f270;
                    }
                    // 0x0045f218: the triangle map: one 32-bit word per entry
                    charge(ctx, 1);
                    s1 = 0;
                    for (;;) {
                        // 0x0045f21c
                        charge(ctx, 6);
                        a0 = s2;
                        a1 = addiu(sp, 0x100);
                        a2 = 4;
                        jal(ctx, 0x45F224u, gen::fn_sub_4C1910_004c1910);
                        if (v0 == 0) {
                            goto L_0045f234_12;
                        }
                        // 0x0045f24c
                        charge(ctx, 9);
                        lw(v0, s0, coll::kTriMap);
                        s3 = addiu(s3, 1);
                        lw(v1, sp, 0x100);
                        v0 = addu(v0, s1);
                        sh(v1, v0, 0);
                        lhu(v0, s0, coll::kNumTriangles);
                        v0 = sltu(s3, v0);
                        s1 = addiu(s1, 2);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    goto L_0045f270;
                }
            L_0045f270:
                charge(ctx, 2);
                v0 = s0;
            } else {
                // 0x0045f450: a short read: free the block, 0
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                a0 = s0;
                jalr(ctx, 0x45F458u, v0.u());
                v0 = 0;
            }
        } else {
            // 0x0045f194
            charge(ctx, 4);
            lw(s4, s0, coll::kSplits);
            v0 = sltu(0, v0);
            s3 = 0;
            if (v0 == 0) {
                // 0x0045f1a4
                charge(ctx, 1);
                v0 = 255;
                goto L_0045f1a8;
            }
            for (;;) {
                // 0x0045f280: each split: two words and two floats
                charge(ctx, 6);
                a0 = s2;
                a1 = addiu(sp, 0x10C);
                a2 = 4;
                jal(ctx, 0x45F288u, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    goto L_0045f37c;
                }
                // 0x0045f298
                charge(ctx, 6);
                a0 = s2;
                a1 = addiu(sp, 0x108);
                a2 = 4;
                jal(ctx, 0x45F2A0u, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    goto L_0045f37c;
                }
                // 0x0045f2b0
                charge(ctx, 6);
                a0 = s2;
                a1 = addiu(s4, 4);
                a2 = 4;
                jal(ctx, 0x45F2B8u, gen::fn_sub_4C18B0_004c18b0);
                if (v0 == 0) {
                    goto L_0045f37c;
                }
                // 0x0045f2c8
                charge(ctx, 6);
                a0 = s2;
                a1 = addiu(s4, 12);
                a2 = 4;
                jal(ctx, 0x45F2D0u, gen::fn_sub_4C18B0_004c18b0);
                if (v0 == 0) {
                    goto L_0045f37c;
                }
                // 0x0045f2e0: decode the split's type byte and its two child kinds (2 = a split, else a leaf)
                charge(ctx, 17);
                lw(v1, sp, 0x10C);
                v0 = 2;
                v1 = srl(v1, 16);
                sb(v1, s4, 8);
                lbu(v1, s4, 8);
                v1 = v1 | 0x1;
                sb(v1, s4, 0);
                lw(v1, sp, 0x108);
                sh(v1, s4, 10);
                lw(v1, sp, 0x108);
                v1 = srl(v1, 16);
                sh(v1, s4, 2);
                lw(v1, sp, 0x10C);
                v1 = srl(v1, 8);
                v1 = v1 & 0xFF;
                if (v1 != v0) {
                    // 0x0045f330
                    charge(ctx, 2);
                    sb(zero, s4, 1);
                } else {
                    // 0x0045f324
                    charge(ctx, 3);
                    v0 = 255;
                    sb(v0, s4, 1);
                }
                // 0x0045f338
                charge(ctx, 4);
                lbu(v1, sp, 0x10C);
                v0 = 2;
                if (v1 != v0) {
                    // 0x0045f358
                    charge(ctx, 2);
                    sb(zero, s4, 9);
                } else {
                    // 0x0045f348
                    charge(ctx, 3);
                    v0 = 255;
                    sb(v0, s4, 9);
                }
                // 0x0045f360
                charge(ctx, 5);
                lhu(v0, s0, coll::kNumSplits);
                s3 = addiu(s3, 1);
                v0 = sltu(s3, v0);
                s4 = addiu(s4, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0045f374
            charge(ctx, 2);
            v0 = 255;
            backedge(ctx);
        L_0045f1a8:
            charge(ctx, 4);
            sh(zero, sp, 0xFA);
            sb(v0, sp, 0xF9);
            s4 = addiu(sp, 0xF8);
            s3 = 1;
            for (;;) {
                // 0x0045f1b8: rebuild the child links (an explicit stack of the pending children)
                charge(ctx, 4);
                lbu(v1, s4, 1);
                v0 = 255;
                if (v1 == v0) {
                    // 0x0045f1c8
                    charge(ctx, 10);
                    lhu(a0, s4, 2);
                    v0 = sll(s3, 2);
                    lw(v1, s0, coll::kSplits);
                    v0 = addu(v0, sp);
                    s3 = addiu(s3, 1);
                    a0 = sll(a0, 4);
                    s4 = addu(v1, a0);
                    v1 = addiu(s4, 8);
                    sw(v1, v0, 96);
                    goto L_0045f1f0;
                }
                // 0x0045f394
                charge(ctx, 6);
                a0 = s2;
                a1 = addiu(sp, 0x104);
                a2 = 4;
                jal(ctx, 0x45F39Cu, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    break;
                }
                // 0x0045f3ac: an index >= 240: corrupt data
                charge(ctx, 6);
                lw(v0, sp, 0x104);
                v0 = srl(v0, 16);
                v0 = v0 & 0xFFFF;
                at = slti(v0, 240);
                if (at == 0) {
                    goto L_0045f400;
                }
                // 0x0045f3c4
                charge(ctx, 8);
                sb(v0, s4, 1);
                s3 = addiu(s3, -1);
                lw(v1, sp, 0x104);
                v0 = sll(s3, 2);
                v0 = addu(v0, sp);
                sh(v1, s4, 2);
                lw(s4, v0, 96);
                backedge(ctx);
            L_0045f1f0:
                charge(ctx, 2);
                if (s3 == 0) {
                    goto L_0045f1f8;
                }
                backedge(ctx);
            }
            // 0x0045f3e8: a short read: free the block, 0
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s0;
            jalr(ctx, 0x45F3F0u, v0.u());
            v0 = 0;
        }
    }
    // 0x0045f464 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x110);
    return;
L_0045f234_12:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x45F23Cu, v0.u());
    v0 = 0;
    // 0x0045f464 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x110);
    return;
L_0045f37c:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x45F384u, v0.u());
    v0 = 0;
    // 0x0045f464 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x110);
    return;
L_0045f400:
    charge(ctx, 15);
    v0 = 1;
    sw(v0, s1, 0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x45F410u, v0.u());
    v0 = 285;
    a0 = 1;
    link(ctx, 0x45F420u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xF0);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xF4);
    a0 = addiu(sp, 0xF0);
    jal(ctx, 0x45F42Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x0045f464 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x110);
}


// sub_45F490 [collModuleOpen] -- the collision plugin's engine-module open: clears its module word and counts the open
// 0x0045F490 sub_45F490 -- 40 bytes; leaf frame (no stack)
void sub_45F490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0045f490
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = a0;
    lw(a1, gp, -17876);  // 0x7CE71C (the collision module's open count)
    lw(a0, gp, -17872);  // 0x7CE720 (the collision module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = addiu(a1, 1);
    v1 = addu(v1, a0);
    sw(a1, gp, -17876);  // 0x7CE71C (the collision module's open count)
    sw(zero, v1, 0);
}


// sub_45F4C0 [collModuleClose] -- the collision plugin's engine-module close: counts down
// 0x0045F4C0 sub_45F4C0 -- 20 bytes; leaf frame (no stack)
void sub_45F4C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0045f4c0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17876);  // 0x7CE71C (the collision module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17876);  // 0x7CE71C (the collision module's open count)
}


// sub_45F4E0 [collDataDestructor] -- the sector / geometry extension destructor: frees the collision block and clears the word
// 0x0045F4E0 sub_45F4E0 -- 72 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45F4E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045f4e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = addu(s1, a1);
    lw(a0, s0, 0);
    if (a0 != 0) {
        // 0x0045f504
        charge(ctx, 3);
        jal(ctx, 0x45F504u, gen::fn_sub_45EDC0_0045edc0);
        sw(zero, s0, 0);
    }
    // 0x0045f510 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_45F530 [collDataConstructor] -- the sector / geometry extension constructor: no collision block
// 0x0045F530 sub_45F530 -- 16 bytes; leaf frame (no stack)
void sub_45F530(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0045f530
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = addu(a0, a1);
    sw(zero, v0, 0);
    v0 = a0;
}


// sub_45F540 [collDataStreamGetSize] -- the extension chunk size: 0 without a block, else its chunk size + 16
// 0x0045F540 sub_45F540 -- 52 bytes; frame 0x10: ra sp+0x0
void sub_45F540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045f540
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addu(a0, a1);
    lw(a0, v0, 0);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0045f564
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0045f554
        charge(ctx, 4);
        jal(ctx, 0x45F554u, gen::fn_sub_45EDD0_0045edd0);
        v0 = addiu(v0, 16);
    }
    // 0x0045f568 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_45F600 [collDataStreamRead] -- reads the collision extension of a sector / geometry
// ($a0 = the stream, $a2 = the object, $a3 = the extension offset) A version word; from 0x36001 on the collision
// chunk follows (sub_45EFE0); before, a second word and the older reader with the object's box: a geometry (type 8)
// from its first morph target's sphere (centre +- radius), a sector from its vertex box. Returns the stream, or 0 when
// nothing could be read (the older reader's error flag keeps the stream).
// 0x0045F600 sub_45F600 -- 432 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45F600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0045f600
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    a1 = addiu(sp, 0x6C);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = addu(s2, a3);
    a2 = 4;
    jal(ctx, 0x45F624u, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x0045f778
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0045f634: the version word decides the layout
        charge(ctx, 6);
        lw(v0, sp, 0x6C);
        at = 0x30000;
        at = at | 0x6001;
        at = sltu(v0, at);
        if (at == 0) {
            // 0x0045f744: 0x36001 and later: find the collision chunk (0x2C) and read it
            charge(ctx, 7);
            a0 = s1;
            a1 = 44;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x45F750u, gen::fn_sub_4C1600_004c1600);
            if (v0 != 0) {
                // 0x0045f788
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x45F788u, gen::fn_sub_45EFE0_0045efe0);
                sw(v0, s0, 0);
                backedge(ctx);
            L_0045f768:
                charge(ctx, 4);
                lw(v0, s0, 0);
                if (v0 == 0) s1 = 0;
                v0 = s1;
            } else {
                // 0x0045f760
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0045f64c
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(sp, 0x68);
            a2 = 4;
            jal(ctx, 0x45F654u, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                // 0x0045f780
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0045f664: older: the box from the object
                charge(ctx, 4);
                lbu(v1, s2, 0);
                v0 = 8;
                if (v1 != v0) {
                    // 0x0045f6dc: a sector: its vertex box
                    charge(ctx, 12);
                    lwc1(f3, s2, sector::kTightBoxSup);
                    lwc1(f2, s2, 100);
                    lwc1(f1, s2, 104);
                    lwc1(f0, s2, sector::kTightBoxInf);
                    swc1(f3, sp, 0x40);
                    swc1(f2, sp, 0x44);
                    swc1(f1, sp, 0x48);
                    swc1(f0, sp, 0x4C);
                    lwc1(f1, s2, 112);
                    lwc1(f0, s2, 116);
                    swc1(f1, sp, 0x50);
                    swc1(f0, sp, 0x54);
                } else {
                    // 0x0045f674: a geometry: its first morph target's bounding sphere, centre +- radius
                    charge(ctx, 26);
                    lw(v0, s2, geometry::kMorphTargets);
                    lwc1(f1, v0, 4);
                    lwc1(f0, v0, 16);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x4C);
                    lwc1(f1, v0, 8);
                    lwc1(f0, v0, 16);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x50);
                    lwc1(f1, v0, 12);
                    lwc1(f0, v0, 16);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x54);
                    lwc1(f1, v0, 4);
                    lwc1(f0, v0, 16);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x40);
                    lwc1(f1, v0, 8);
                    lwc1(f0, v0, 16);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x44);
                    lwc1(f1, v0, 12);
                    lwc1(f0, v0, 16);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x48);
                }
                // 0x0045f70c: the older reader
                charge(ctx, 12);
                lw(v0, sp, 0x6C);
                a0 = s1;
                lw(a1, sp, 0x68);
                a3 = addiu(sp, 0x40);
                t0 = addiu(sp, 0x64);
                sw(zero, sp, 0x64);
                a2 = addiu(v0, -1);
                jal(ctx, 0x45F724u, gen::fn_sub_45F140_0045f140);
                sw(v0, s0, 0);
                lw(v0, sp, 0x64);
                if (v0 == 0) {
                    goto L_0045f768;
                }
                // 0x0045f73c
                charge(ctx, 2);
                v0 = s1;
            }
        }
    }
    // 0x0045f798 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_45F7B0 [collAtomicConstructor] -- the atomic extension constructor: clears the word at atomic + gp 0x7CE724
// 0x0045F7B0 sub_45F7B0 -- 20 bytes; leaf frame (no stack)
void sub_45F7B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0045f7b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17868);  // 0x7CE724 (the collision atomic extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_464280 [pairArrayCreate] -- allocates a counted array of n zeroed 8-byte pairs: {count, -> the pairs}
// (error 0x80000013 under plugin id 0x122 when the allocation fails; called by the resource loader's chunk reader)
// 0x00464280 sub_464280 -- 292 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_464280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00464280
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x30000;
    sd(ra, sp, 0x20);
    a1 = v0 | 0x1E;
    sq(s1, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    s0 = a0;
    v1 = sll(s0, 3);
    s1 = addiu(v1, 8);
    a0 = s1;
    jalr(ctx, 0x4642ACu, v0.u());
    if (v0 == 0) {
        // 0x00464368
        charge(ctx, 11);
        v0 = 290;
        a1 = s1;
        sw(v0, sp, 0x38);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x464378u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x464384u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        ld(ra, sp, 0x20);
    } else {
        // 0x004642bc
        charge(ctx, 7);
        sw(s0, v0, 0);
        v1 = addiu(v0, 8);
        sw(v1, v0, 4);
        at = sltu(0, s0);
        lw(a1, v0, 4);
        a2 = 0;
        if (at != 0) {
            // 0x004642d8
            charge(ctx, 3);
            at = sltiu(s0, 9);
            a0 = addiu(s0, -8);
            if (at == 0) {
                for (;;) {
                    // 0x004642e4
                    charge(ctx, 20);
                    sw(zero, a1, 0);
                    a2 = addiu(a2, 8);
                    sw(zero, a1, 4);
                    v1 = sltu(a2, a0);
                    sw(zero, a1, 8);
                    sw(zero, a1, 12);
                    sw(zero, a1, 16);
                    sw(zero, a1, 20);
                    sw(zero, a1, 24);
                    sw(zero, a1, 28);
                    sw(zero, a1, 32);
                    sw(zero, a1, 36);
                    sw(zero, a1, 40);
                    sw(zero, a1, 44);
                    sw(zero, a1, 48);
                    sw(zero, a1, 52);
                    sw(zero, a1, 56);
                    sw(zero, a1, 60);
                    a1 = addiu(a1, 64);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00464334
                charge(ctx, 1);
            }
            // 0x00464338
            charge(ctx, 3);
            at = sltu(a2, s0);
            if (at != 0) {
                for (;;) {
                    // 0x00464344
                    charge(ctx, 7);
                    sw(zero, a1, 0);
                    a2 = addiu(a2, 1);
                    sw(zero, a1, 4);
                    v1 = sltu(a2, s0);
                    a1 = addiu(a1, 8);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x00464360
        charge(ctx, 2);
        ld(ra, sp, 0x20);
    }
    // 0x00464394 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_490690 [pipeStreamModuleClose] -- the atomic-pipeline stream module's close: counts down (gp 0x7CE80C)
// 0x00490690 sub_490690 -- 20 bytes; leaf frame (no stack)
void sub_490690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00490690
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17636);  // 0x7CE80C (the pipeline-stream module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17636);  // 0x7CE80C (the pipeline-stream module's open count)
}


// sub_4906B0 [pipeStreamModuleOpen] -- the atomic-pipeline stream module's open: counts the open
// 0x004906B0 sub_4906B0 -- 20 bytes; leaf frame (no stack)
void sub_4906B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004906b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17636);  // 0x7CE80C (the pipeline-stream module's open count)
    v0 = a0;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17636);  // 0x7CE80C (the pipeline-stream module's open count)
}


// sub_4906F0 [atomicPipelineStreamRead] -- reads an atomic's pipeline extension: the plugin id (and data for 8 bytes) into globals
// The ids wait in gp 0x7CE81C / 0x7CE818 for the atomic's always callback. Returns the stream or 0.
// 0x004906F0 sub_4906F0 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4906F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004906f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = addiu(gp, -17620);  // &0x7CE81C (the atomic pipeline's plugin id read from the stream)
    jal(ctx, 0x49070Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x00490730
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049071c
        charge(ctx, 3);
        v0 = 8;
        if (s0 == v0) {
            // 0x00490738
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(gp, -17624);  // &0x7CE818 (the atomic pipeline's plugin data read from the stream)
            a2 = 4;
            jal(ctx, 0x490740u, gen::fn_sub_4C1910_004c1910);
            if (v0 != 0) {
                backedge(ctx);
                goto L_00490728;
            }
            // 0x00490750
            charge(ctx, 1);
            v0 = 0;
            // 0x00490754 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_00490728:
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x00490754 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_490770 [atomicPipelineStreamWrite] -- writes an atomic's pipeline extension: its pipeline's plugin id and data
// 0x00490770 sub_490770 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_490770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490770
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lw(v0, a2, atomic::kPipeline);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a1 = addiu(v0, 44);
    a2 = 4;
    jal(ctx, 0x490790u, gen::fn_sub_4C17F0_004c17f0);
    if (v0 != 0) {
        // 0x004907a8
        charge(ctx, 7);
        lw(v0, s0, atomic::kPipeline);
        a0 = s1;
        a2 = 4;
        a1 = addiu(v0, 48);
        jal(ctx, 0x4907B4u, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x004907a0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004907c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4907E0 [atomicPipelineStreamGetSize] -- 8 when the atomic has a pipeline with a plugin id, else 0
// 0x004907E0 sub_4907E0 -- 44 bytes; leaf frame (no stack)
void sub_4907E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004907e0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, atomic::kPipeline);
    if (v0 != 0) {
        // 0x004907ec
        charge(ctx, 3);
        lw(v0, v0, pipeline::kPluginId);
        if (v0 == 0) {
            goto L_00490800;
        }
        // 0x004907f8
        charge(ctx, 2);
        v0 = 8;
        // 0x00490804 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00490800:
    charge(ctx, 1);
    v0 = 0;
    // 0x00490804 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_490CA0 [cameraClumpTieConstructor] -- the camera's clump-tie extension constructor: clears its 12 bytes
// 0x00490CA0 sub_490CA0 -- 28 bytes; leaf frame (no stack)
void sub_490CA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00490ca0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17632);  // 0x7CE810 (the camera clump-tie extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 8);
    sw(zero, v1, 4);
    sw(zero, v1, 0);
}


// sub_490CC0 [cameraClumpTieCopy] -- the camera's clump-tie copy: nothing to copy, returns the camera
// 0x00490CC0 sub_490CC0 -- 8 bytes; leaf frame (no stack)
void sub_490CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00490cc0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}


// sub_490CD0 [lightClumpTieConstructor] -- the light's clump-tie extension constructor: clears its 12 bytes
// 0x00490CD0 sub_490CD0 -- 28 bytes; leaf frame (no stack)
void sub_490CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00490cd0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17628);  // 0x7CE814 (the light clump-tie extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 8);
    sw(zero, v1, 4);
    sw(zero, v1, 0);
}


// sub_490CF0 [lightClumpTieCopy] -- the light's clump-tie copy: nothing to copy, returns the light
// 0x00490CF0 sub_490CF0 -- 8 bytes; leaf frame (no stack)
void sub_490CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00490cf0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}


// sub_490D00 [clumpDestroyLightCB] -- the clump destroy's light callback: out of the clump (sub_492020), then destroyed
// 0x00490D00 sub_490D00 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_490D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490d00
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17628);  // 0x7CE814 (the light clump-tie extension offset)
    s0 = a0;
    v0 = addu(s0, v0);
    lw(a0, v0, 0);
    a1 = s0;
    jal(ctx, 0x490D1Cu, gen::fn_sub_492020_00492020);
    a0 = s0;
    jal(ctx, 0x490D24u, gen::fn_sub_494760_00494760);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_491410 [clumpModuleClose] -- the clump / atomic module's close: every clump, then every atomic destroyed; both free lists
// 0x00491410 sub_491410 -- 192 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_491410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00491410
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    a1 = 0x490000;
    sq(s0, sp, 0x0);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    s0 = a0;
    a1 = addiu(a1, 1744);  // &j_RpClumpDestroy
    v0 = addu(v0, v1);
    lw(a0, v0, 4);
    a2 = 0;
    jal(ctx, 0x49143Cu, gen::fn_sub_4C4200_004c4200);
    lw(v1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = 0x490000;
    a1 = addiu(a1, 1760);  // &j_RpAtomicDestroy
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    a2 = 0;
    jal(ctx, 0x491460u, gen::fn_sub_4C4200_004c4200);
    lw(v1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    link(ctx, 0x491478u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    lw(v1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    link(ctx, 0x491490u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 4);
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    lw(a1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    a0 = 0x960000;
    lw(v1, gp, -17612);  // 0x7CE824 (the clump / atomic module's open count)
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = s0;
    a0 = addu(a0, a1);
    v1 = addiu(v1, -1);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(v1, gp, -17612);  // 0x7CE824 (the clump / atomic module's open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4914D0 [clumpModuleOpen] -- the clump / atomic module's open: the atomic and clump free lists (16-aligned, static records)
// 0x004914D0 sub_4914D0 -- 240 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4914D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004914d0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x780000;
    sq(s0, sp, 0x0);
    a2 = 16;
    s0 = a0;
    sw(a1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    lw(a0, v0, -8992);  // 0x77DCE0 (the atomic plugin registry)
    t0 = addiu(t0, -8544);  // &0x95DEA0 (the atomic free list's static record)
    lw(a1, gp, -20768);  // 0x7CDBD0 (the atomic free list's entries per block)
    lw(a3, gp, -20764);  // 0x7CDBD4 (the atomic free list's preallocated blocks)
    v0 = 0x40000;
    t1 = v0 | 0x10;
    jal(ctx, 0x491504u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x00491534: the clump free list
        charge(ctx, 18);
        v0 = 0x780000;
        t0 = 0x960000;
        lw(a0, v0, -8960);  // 0x77DD00 (the clump plugin registry)
        a2 = 16;
        lw(a1, gp, -20760);  // 0x7CDBD8 (the clump free list's entries per block)
        t0 = addiu(t0, -8592);  // &0x95DE70 (the clump free list's static record)
        lw(a3, gp, -20756);  // 0x7CDBDC (the clump free list's preallocated blocks)
        v0 = 0x40000;
        t1 = v0 | 0x14;
        jal(ctx, 0x491554u, gen::fn_sub_4C3B60_004c3b60);
        lw(a0, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v1 = addu(v1, a0);
        sw(v0, v1, 4);
        lw(v0, v1, 4);
        if (v0 == 0) {
            // 0x00491590: no clump free list: destroy the atomic one, 0
            charge(ctx, 8);
            link(ctx, 0x491590u);  // $ra first: the delay slot below depends on it
            lw(a0, v1, 0);
            call(ctx, gen::fn_sub_4C3C30_004c3c30);
            lw(v1, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = addu(v0, v1);
            sw(zero, v0, 0);
            backedge(ctx);
            goto L_0049152c;
        }
        // 0x0049157c: count the open, return the instance
        charge(ctx, 5);
        lw(v1, gp, -17612);  // 0x7CE824 (the clump / atomic module's open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17612);  // 0x7CE824 (the clump / atomic module's open count)
        // 0x004915b0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0049152c:
    charge(ctx, 2);
    v0 = 0;
    // 0x004915b0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4915C0 [clumpTiesAttach] -- registers the 12-byte clump-tie extensions of cameras and lights; 1 when both offsets are valid
// 0x004915C0 sub_4915C0 -- 112 bytes; frame 0x10: ra sp+0x0
void sub_4915C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004915c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x490000;
    a3 = 0x490000;
    sd(ra, sp, 0x0);
    a0 = 12;
    a1 = 16;
    a2 = addiu(a2, 3232);  // &sub_490CA0
    a3 = addiu(a3, 3264);  // &sub_490CC0
    t0 = 0;
    jal(ctx, 0x4915E0u, gen::fn_sub_4CA000_004ca000);
    sw(v0, gp, -17632);  // 0x7CE810 (the camera clump-tie extension offset)
    if (i64(v0) >= 0) {
        // 0x004915f8
        charge(ctx, 11);
        a2 = 0x490000;
        a3 = 0x490000;
        a0 = 12;
        a1 = 16;
        a2 = addiu(a2, 3280);  // &sub_490CD0
        a3 = addiu(a3, 3312);  // &sub_490CF0
        t0 = 0;
        jal(ctx, 0x491610u, gen::fn_sub_494520_00494520);
        sw(v0, gp, -17628);  // 0x7CE814 (the light clump-tie extension offset)
        v0 = slt(v0, 0);
        v0 = v0 ^ 0x1;
    } else {
        // 0x004915f0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00491624 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_491760 [clumpForAllCameras] -- calls a callback on each camera of a clump until it returns 0; returns the clump
// (a camera's link is camera + the tie offset + 4)
// 0x00491760 sub_491760 -- 140 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_491760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00491760
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s4, 24);
    lw(v0, a0, clump::kCameras);
    s2 = a2;
    if (v0 != s1) {
        for (;;) {
            // 0x00491794
            charge(ctx, 8);
            lw(s0, v0, 0);
            v1 = addiu(v0, -4);
            a1 = s2;
            lw(v0, gp, -17632);  // 0x7CE810 (the camera clump-tie extension offset)
            a0 = subu(v1, v0);
            jalr(ctx, 0x4917A4u, s3.u());
            if (v0 == 0) {
                goto L_004917b4_2;
            }
            // 0x004917bc
            charge(ctx, 2);
            v0 = s0;
            if (s0 == s1) {
                break;
            }
            backedge(ctx);
        }
        // 0x004917c4
        charge(ctx, 1);
    }
    // 0x004917c8
    charge(ctx, 1);
    v0 = s4;
    // 0x004917cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004917b4_2:
    charge(ctx, 2);
    v0 = s4;
    // 0x004917cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4917F0 [clumpForAllLights] -- calls a callback on each light of a clump until it returns 0; returns the clump
// (a light's link is light + the tie offset + 4)
// 0x004917F0 sub_4917F0 -- 140 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4917F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004917f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s4, 16);
    lw(v0, a0, clump::kLights);
    s2 = a2;
    if (v0 != s1) {
        for (;;) {
            // 0x00491824
            charge(ctx, 8);
            lw(s0, v0, 0);
            v1 = addiu(v0, -4);
            a1 = s2;
            lw(v0, gp, -17628);  // 0x7CE814 (the light clump-tie extension offset)
            a0 = subu(v1, v0);
            jalr(ctx, 0x491834u, s3.u());
            if (v0 == 0) {
                goto L_00491844_2;
            }
            // 0x0049184c
            charge(ctx, 2);
            v0 = s0;
            if (s0 == s1) {
                break;
            }
            backedge(ctx);
        }
        // 0x00491854
        charge(ctx, 1);
    }
    // 0x00491858
    charge(ctx, 1);
    v0 = s4;
    // 0x0049185c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_00491844_2:
    charge(ctx, 2);
    v0 = s4;
    // 0x0049185c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_491DE0 [clumpCreate] -- a clump from the clump free list: type 2, empty atomic / light / camera lists, the default callback
// (sub_490D80), then the clump plugins' constructors (registry 0x77DD00).
// 0x00491DE0 sub_491DE0 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_491DE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00491de0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0x10;
    lw(a0, gp, -17616);  // 0x7CE820 (the clump / atomic module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x491E0Cu);  // $ra = the return address
    lw(a0, v1, 4);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 != 0) {
        // 0x00491e20: fill the record and run the plugin constructors
        charge(ctx, 25);
        v0 = 2;
        a0 = 0x780000;
        sb(v0, s0, rwobj::kType);
        a3 = addiu(s0, 8);
        sb(zero, s0, rwobj::kSubType);
        v0 = 0x490000;
        sb(zero, s0, rwobj::kFlags);
        a2 = addiu(s0, 16);
        sb(zero, s0, rwobj::kPrivateFlags);
        v1 = addiu(s0, 24);
        sw(zero, s0, rwobj::kParent);
        v0 = addiu(v0, 3456);  // &sub_490D80
        sw(a3, s0, clump::kAtomics);
        a0 = addiu(a0, -8960);  // &0x77DD00 (the clump plugin registry)
        sw(a3, s0, clump::kAtomicsPrev);
        a1 = s0;
        sw(a2, s0, clump::kLights);
        sw(a2, s0, clump::kLightsPrev);
        sw(v1, s0, clump::kCameras);
        sw(v1, s0, clump::kCamerasPrev);
        sw(zero, s0, clump::kStreamPad36);
        sw(zero, s0, clump::kStreamPad32);
        link(ctx, 0x491E78u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, clump::kCallback);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s0;
    }
    // 0x00491e84 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_491FF0 [clumpAddAtomic] -- links an atomic at the head of the clump's atomic list and sets its clump; returns the clump
// 0x00491FF0 sub_491FF0 -- 44 bytes; leaf frame (no stack)
void sub_491FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00491ff0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a3, a0, clump::kAtomics);
    v1 = addiu(a0, 8);
    a2 = addiu(a1, 64);
    v0 = a0;
    sw(a3, a1, atomic::kClumpLink);
    sw(v1, a1, atomic::kClumpLinkPrev);
    lw(v1, a0, clump::kAtomics);
    sw(a2, v1, 4);
    sw(a2, a0, clump::kAtomics);
    sw(a0, a1, atomic::kClump);
}


// sub_492020 [clumpRemoveLight] -- unlinks a light's clump tie and clears it; returns the clump
// 0x00492020 sub_492020 -- 52 bytes; leaf frame (no stack)
void sub_492020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00492020
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v1, gp, -17628);  // 0x7CE814 (the light clump-tie extension offset)
    v0 = a0;
    a1 = addu(a1, v1);
    lw(a0, a1, 4);
    lw(v1, a1, 8);
    sw(a0, v1, 0);
    lw(a0, a1, 8);
    lw(v1, a1, 4);
    sw(a0, v1, 4);
    sw(zero, a1, 8);
    sw(zero, a1, 4);
    sw(zero, a1, 0);
}


// sub_492060 [clumpRemoveCamera] -- unlinks a camera's clump tie and clears it; returns the clump
// 0x00492060 sub_492060 -- 52 bytes; leaf frame (no stack)
void sub_492060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00492060
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v1, gp, -17632);  // 0x7CE810 (the camera clump-tie extension offset)
    v0 = a0;
    a1 = addu(a1, v1);
    lw(a0, a1, 4);
    lw(v1, a1, 8);
    sw(a0, v1, 0);
    lw(a0, a1, 8);
    lw(v1, a1, 4);
    sw(a0, v1, 4);
    sw(zero, a1, 8);
    sw(zero, a1, 4);
    sw(zero, a1, 0);
}


// sub_492C30 [atomicRegisterPlugin] -- registers an atomic plugin (sub_4C61B0 on the atomic registry 0x77DCE0)
// 0x00492C30 sub_492C30 -- 44 bytes; leaf frame (no stack)
void sub_492C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00492c30
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8992);  // &0x77DCE0 (the atomic plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_492C60 [clumpRegisterPlugin] -- registers a clump plugin (sub_4C61B0 on the clump registry 0x77DD00)
// 0x00492C60 sub_492C60 -- 44 bytes; leaf frame (no stack)
void sub_492C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00492c60
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8960);  // &0x77DD00 (the clump plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_492C90 [atomicRegisterPluginStream] -- sets an atomic plugin's stream read / write / size callbacks; its offset or -1
// (the registries' shared lookup tail at 0x4C5960)
// 0x00492C90 sub_492C90 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_492C90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00492c90
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -8992);  // &0x77DCE0 (the atomic plugin registry)
    a3 = v0;
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}


// sub_492CC0 [atomicSetStreamAlwaysCallBack] -- sets an atomic plugin's 'always' stream callback; its offset or -1
// 0x00492CC0 sub_492CC0 -- 96 bytes, 2 chunks; leaf frame (no stack)
void sub_492CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00492cc0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = a0;
    a2 = a1;
    a0 = 0x780000;
    a1 = v0;
    a0 = addiu(a0, -8992);  // &0x77DCE0 (the atomic plugin registry)
    // 0x004c59b0
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c59bc
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c59c8
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c59d4_4;
            }
            backedge(ctx);
        }
    }
L_004c59d8:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59ec
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c59e0
        charge(ctx, 3);
        sw(a2, v1, plugentry::kAlwaysCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c59d4_4:
    charge(ctx, 1);
    goto L_004c59d8;
}


// sub_492CE0 [atomicSetStreamRightsCallBack] -- sets an atomic plugin's rights callback; its offset or -1
// 0x00492CE0 sub_492CE0 -- 96 bytes, 2 chunks; leaf frame (no stack)
void sub_492CE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00492ce0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = a0;
    a2 = a1;
    a0 = 0x780000;
    a1 = v0;
    a0 = addiu(a0, -8992);  // &0x77DCE0 (the atomic plugin registry)
    // 0x004c5a00
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c5a0c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5a18
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5a24_4;
            }
            backedge(ctx);
        }
    }
L_004c5a28:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c5a3c
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5a30
        charge(ctx, 3);
        sw(a2, v1, plugentry::kRightsCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c5a40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5a24_4:
    charge(ctx, 1);
    goto L_004c5a28;
}


// sub_492D00 [atomicGetPluginOffset] -- the offset of an atomic plugin's data, -1 when it is not registered
// 0x00492D00 sub_492D00 -- 76 bytes, 2 chunks; leaf frame (no stack)
void sub_492D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00492d00
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = a0;
    a0 = 0x780000;
    a0 = addiu(a0, -8992);  // &0x77DCE0 (the atomic plugin registry)
    // 0x004c6170
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c617c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                goto L_004c6188_3;
            }
            // 0x004c6190
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c619c
        charge(ctx, 1);
    }
    // 0x004c61a0
    charge(ctx, 1);
    v0 = si(-1);
    // 0x004c61a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c6188_3:
    charge(ctx, 2);
    lw(v0, v1, plugentry::kOffset);
    // 0x004c61a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_492DE0 [geometryModuleOpen] -- the geometry module's open: keeps its offset (gp 0x7CE828), counts the open
// 0x00492DE0 sub_492DE0 -- 24 bytes; leaf frame (no stack)
void sub_492DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00492de0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17604);  // 0x7CE82C (the geometry module's open count)
    v0 = a0;
    sw(a1, gp, -17608);  // 0x7CE828 (the geometry module offset)
    v1 = addiu(v1, 1);
    sw(v1, gp, -17604);  // 0x7CE82C (the geometry module's open count)
}


// sub_492E00 [geometryModuleClose] -- the geometry module's close: counts down
// 0x00492E00 sub_492E00 -- 20 bytes; leaf frame (no stack)
void sub_492E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00492e00
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17604);  // 0x7CE82C (the geometry module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17604);  // 0x7CE82C (the geometry module's open count)
}


// sub_492E20 [morphTargetCalcBoundingSphere] -- a morph target's bounding sphere: the centre of its vertices' box, the radius
// the largest distance from it, x 1.001 (stored in $a1: centre, radius). Returns the morph target.
// 0x00492E20 sub_492E20 -- 344 bytes; frame 0x80: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_492E20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f20{ctx, 20};
    // 0x00492e20
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    lw(v0, a0, morph::kParent);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    swc1(f20, sp, 0x0);
    s0 = a1;
    lw(s2, v0, 20);
    mtc1(zero, f20);
    lw(a1, s1, 20);
    a0 = addiu(sp, 0x50);
    a2 = s2;
    jal(ctx, 0x492E54u, gen::fn_sub_4C7A50_004c7a50);
    lwc1(f6, sp, 0x5C);
    v0 = 0x3F000000;
    lwc1(f5, sp, 0x50);
    lw(a2, s1, 20);
    lwc1(f4, sp, 0x60);
    a0 = addiu(sp, 0x74);
    lwc1(f3, sp, 0x54);
    v1 = addiu(sp, 0x78);
    mtc1(v0, f0);
    a1 = addiu(s2, -1);
    lwc1(f2, sp, 0x64);
    lwc1(f1, sp, 0x58);
    add_s(f5, f6, f5);
    add_s(f4, f4, f3);
    mul_s(f3, f5, f0);
    mul_s(f5, f4, f0);
    add_s(f1, f2, f1);
    mul_s(f4, f1, f0);
    swc1(f3, sp, 0x70);
    swc1(f5, a0, morph::kParent);
    swc1(f4, v1, 0);
    if (s2 != 0) {
        for (;;) {
            // 0x00492eb4: the squared distance of each vertex to the centre; keep the largest
            charge(ctx, 12);
            lwc1(f1, a2, 4);
            lwc1(f2, a2, 0);
            lwc1(f0, a2, 8);
            sub_s(f1, f1, f5);
            sub_s(f2, f2, f3);
            mula_s(f1, f1);
            sub_s(f0, f0, f4);
            madda_s(f2, f2);
            madd_s(f0, f0, f0);
            c_le_s(f0, f20);
            if (!cond(ctx)) {
                // 0x00492ee4
                charge(ctx, 1);
                mov_s(f20, f0);
            }
            // 0x00492ee8
            charge(ctx, 4);
            v0 = a1;
            a2 = addiu(a2, 12);
            a1 = addiu(a1, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00492ef8
        charge(ctx, 2);
    }
    // 0x00492f40
    charge(ctx, 5);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        backedge(ctx);
    } else {
        // 0x00492f54
        charge(ctx, 2);
        backedge(ctx);
        // 0x00492f00: the radius = sqrt(largest) x 1.001
        charge(ctx, 2);
        sqrt_s(f20, f20);
    }
    // 0x00492f08
    charge(ctx, 14);
    v1 = 0x3F800000;
    v0 = s1;
    lwc1(f2, sp, 0x70);
    v1 = v1 | 0x20C5;
    mtc1(v1, f3);
    lwc1(f1, sp, 0x74);
    mul_s(f3, f3, f20);
    swc1(f2, s0, 0);
    lwc1(f0, sp, 0x78);
    swc1(f1, s0, 4);
    swc1(f3, sp, 0x7C);
    swc1(f0, s0, 8);
    swc1(f3, s0, 12);
    // 0x00492f5c
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lwc1(f20, sp, 0x0);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x80);
}


// sub_492F80 [geometryAddMorphTargets] -- grows a geometry's morph-target array by n; the first new index or -1
// A record is 28 bytes + 12 per vertex for the points (+ 12 per vertex again with normals, flag 0x10); a native
// geometry (flag 0x1000000) keeps 28. The array is reallocated (RwRealloc) or allocated (RwMalloc), the existing
// records' vertex data moved up to the new layout, every target's point / normal pointers re-set and the new targets
// initialised (the geometry, a zero sphere). error 0x80000013 (out of memory) and -1 when the allocation fails.
// 0x00492F80 sub_492F80 -- 644 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_492F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00492f80
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x1000000;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 8);
    v0 = v1 & v0;
    s2 = a1;
    if (v0 != 0) {
        // 0x00493164
        charge(ctx, 2);
        s1 = 28;
        backedge(ctx);
    } else {
        // 0x00492fb0: the record size: 28 + 12 per vertex (points), + 12 per vertex with normals
        charge(ctx, 7);
        lw(a0, s3, geometry::kNumVertices);
        v0 = v1 & 0x10;
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        s1 = addiu(v1, 28);
        if (v0 != 0) {
            // 0x00492fcc
            charge(ctx, 1);
            s1 = addu(s1, v1);
        }
    }
    // 0x00492fd0
    charge(ctx, 6);
    lw(v0, s3, geometry::kNumMorphTargets);
    v0 = addu(v0, s2);
    mult(s0, s1, v0);
    lw(a0, s3, geometry::kMorphTargets);
    if (a0 == 0) {
        // 0x00493198: no array yet: RwMalloc
        charge(ctx, 8);
        v0 = 0x30000;
        a1 = v0 | 0xF;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = s0;
        jalr(ctx, 0x4931A8u, v0.u());
        if (v0 != 0) {
            backedge(ctx);
        L_00493058:
            charge(ctx, 12);
            lw(a0, s3, geometry::kNumMorphTargets);
            v1 = 0;
            a0 = addu(a0, s2);
            sw(a0, s3, geometry::kNumMorphTargets);
            sw(v0, s3, geometry::kMorphTargets);
            lw(a1, s3, geometry::kNumMorphTargets);
            a0 = sll(a1, 3);
            at = slt(0, a1);
            a0 = subu(a0, a1);
            a0 = sll(a0, 2);
            t1 = addu(v0, a0);
            if (at != 0) {
                // 0x00493088: re-point every target's point and normal arrays into the block
                charge(ctx, 2);
                t0 = 0;
                a2 = 0x1000000;
                for (;;) {
                    // 0x00493090
                    charge(ctx, 8);
                    lw(v0, s3, geometry::kMorphTargets);
                    a3 = addu(v0, t0);
                    sw(zero, a3, morph::kVerts);
                    sw(zero, a3, morph::kNormals);
                    lw(v0, s3, geometry::kFlags);
                    v0 = v0 & a2;
                    if (v0 == 0) {
                        // 0x004930b0
                        charge(ctx, 3);
                        lw(v0, s3, geometry::kNumVertices);
                        if (v0 != 0) {
                            // 0x004930bc
                            charge(ctx, 9);
                            sw(t1, a3, morph::kVerts);
                            lw(a1, s3, geometry::kNumVertices);
                            lw(v0, s3, geometry::kFlags);
                            a0 = sll(a1, 1);
                            a0 = addu(a0, a1);
                            v0 = v0 & 0x10;
                            a0 = sll(a0, 2);
                            t1 = addu(t1, a0);
                            if (v0 != 0) {
                                // 0x004930e0
                                charge(ctx, 6);
                                sw(t1, a3, morph::kNormals);
                                lw(a0, s3, geometry::kNumVertices);
                                v0 = sll(a0, 1);
                                v0 = addu(v0, a0);
                                v0 = sll(v0, 2);
                                t1 = addu(t1, v0);
                            }
                        }
                    }
                    // 0x004930f8
                    charge(ctx, 5);
                    lw(a1, s3, geometry::kNumMorphTargets);
                    v1 = addiu(v1, 1);
                    v0 = slt(v1, a1);
                    t0 = addiu(t0, 28);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049310c
                charge(ctx, 1);
            }
            // 0x00493110
            charge(ctx, 4);
            v1 = subu(a1, s2);
            at = slt(v1, a1);
            if (at == 0) {
                // 0x004931e4
                charge(ctx, 1);
                v0 = subu(a1, s2);
            } else {
                // 0x00493120: the new targets: the geometry, a zero sphere
                charge(ctx, 3);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                a0 = sll(v0, 2);
                for (;;) {
                    // 0x0049312c
                    charge(ctx, 12);
                    lw(v0, s3, geometry::kMorphTargets);
                    v1 = addiu(v1, 1);
                    v0 = addu(v0, a0);
                    sw(zero, v0, 4);
                    sw(zero, v0, 8);
                    sw(zero, v0, 12);
                    sw(zero, v0, 16);
                    sw(s3, v0, 0);
                    lw(a1, s3, geometry::kNumMorphTargets);
                    v0 = slt(v1, a1);
                    a0 = addiu(a0, 28);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049315c
                charge(ctx, 2);
                v0 = subu(a1, s2);
            }
        } else {
            // 0x004931b8: out of memory: error 0x80000013, -1
            charge(ctx, 11);
            v0 = 2;
            a1 = s0;
            sw(v0, sp, 0x50);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x4931C8u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x4931D4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = si(-1);
        }
    } else {
        // 0x00492fe8: an array already: RwRealloc
        charge(ctx, 8);
        v0 = 0x30000;
        a2 = v0 | 0xF;
        v0 = 0x960000;
        lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
        a1 = s0;
        jalr(ctx, 0x492FF8u, v0.u());
        if (v0 != 0) {
            // 0x00493008: move the old records' vertex data up to the new record size (byte copy from the end)
            charge(ctx, 12);
            lw(a2, s3, geometry::kNumMorphTargets);
            mult(a1, s1, a2);
            a0 = sll(s2, 3);
            a0 = subu(a0, s2);
            v1 = addiu(s1, -28);
            a0 = sll(a0, 2);
            a1 = addu(v0, a1);
            t0 = addiu(a1, -1);
            a3 = addu(t0, a0);
            mult1(v1, a2, v1);
            a1 = addiu(v1, -1);
            if (v1 != 0) {
                for (;;) {
                    // 0x00493038
                    charge(ctx, 7);
                    lbu(a0, t0, 0);
                    v1 = a1;
                    a1 = addiu(a1, -1);
                    sb(a0, a3, morph::kParent);
                    t0 = addiu(t0, -1);
                    a3 = addiu(a3, -1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00493054
                charge(ctx, 1);
            }
            goto L_00493058;
        }
        // 0x0049316c: out of memory: error 0x80000013, -1
        charge(ctx, 11);
        v0 = 2;
        a1 = s0;
        sw(v0, sp, 0x58);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x49317Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x493188u, gen::fn_sub_4C1C50_004c1c50);
        v0 = si(-1);
    }
    // 0x004931e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_493210 [triangleSetVertexIndices] -- ($a1 = the triangle) its three u16 vertex indices; returns the geometry
// 0x00493210 sub_493210 -- 20 bytes; leaf frame (no stack)
void sub_493210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00493210
    enter(ctx, 5);  // entry check point + this block's cycles
    sh(a2, a1, 0);
    v0 = a0;
    sh(a3, a1, 2);
    sh(t0, a1, 4);
}


// sub_493230 [triangleSetMaterial] -- ($a1 = the triangle, $a2 = the material) its index in the geometry's material list
// (appended when missing) into the triangle's +6; 0xFFFF for no material; returns the geometry, 0 when the append fails.
// 0x00493230 sub_493230 -- 132 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_493230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00493230
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s0 = a2;
    s1 = a1;
    if (s0 != 0) {
        // 0x00493254
        charge(ctx, 5);
        a0 = addiu(s2, 32);
        a1 = s0;
        jal(ctx, 0x493258u, gen::fn_sub_495480_00495480);
        if (i64(v0) < 0) {
            // 0x00493274
            charge(ctx, 5);
            a1 = s0;
            a0 = addiu(s2, 32);
            jal(ctx, 0x493278u, gen::fn_sub_495340_00495340);
            if (i64(v0) >= 0) {
                backedge(ctx);
                goto L_00493268;
            }
            // 0x00493288
            charge(ctx, 2);
            v0 = 0;
            // 0x0049329c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_00493268:
        charge(ctx, 1);
        sh(v0, s1, 6);
        goto L_0049326c;
    }
    // 0x00493290
    charge(ctx, 3);
    v0 = 0xFFFF;
    sh(v0, s1, 6);
    backedge(ctx);
L_0049326c:
    charge(ctx, 2);
    v0 = s2;
    // 0x0049329c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_493B40 [geometryAddRef] -- adds a reference to a geometry (+14); returns it
// 0x00493B40 sub_493B40 -- 20 bytes; leaf frame (no stack)
void sub_493B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00493b40
    enter(ctx, 5);  // entry check point + this block's cycles
    lh(v1, a0, geometry::kRefCount);
    v0 = a0;
    v1 = addiu(v1, 1);
    sh(v1, a0, geometry::kRefCount);
}


// sub_493C50 [geometryRegisterPlugin] -- registers a geometry plugin (sub_4C61B0 on the geometry registry 0x77DD20)
// 0x00493C50 sub_493C50 -- 44 bytes; leaf frame (no stack)
void sub_493C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00493c50
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8928);  // &0x77DD20 (the geometry plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_493C80 [geometryRegisterPluginStream] -- sets a geometry plugin's stream callbacks; its offset or -1
// 0x00493C80 sub_493C80 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_493C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00493c80
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -8928);  // &0x77DD20 (the geometry plugin registry)
    a3 = v0;
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}


// sub_494490 [lightDestroyCB] -- the light module close's walk callback: destroys the light (sub_494760, a tail call)
// 0x00494490 sub_494490 -- 8 bytes; leaf frame (no stack)
void sub_494490(EEContext& ctx) {
    using namespace hg;
    // 0x00494490
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_494760_00494760(ctx);  // tail call
}


// sub_4944A0 [lightSyncNone] -- the light's default object sync: nothing to do, returns the light
// 0x004944A0 sub_4944A0 -- 8 bytes; leaf frame (no stack)
void sub_4944A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004944a0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}


// sub_4944B0 [lightSetColor] -- copies a light's colour (r, g, b, a) and sets its private flag byte to (r == g == b)
// 0x004944B0 sub_4944B0 -- 100 bytes; leaf frame (no stack)
void sub_4944B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004944b0
    enter(ctx, 13);  // entry check point + this block's cycles
    lwc1(f3, a1, 0);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a1, 12);
    swc1(f3, a0, light::kColor);
    swc1(f2, a0, light::kColorG);
    swc1(f1, a0, light::kColorB);
    swc1(f0, a0, light::kColorA);
    lwc1(f1, a0, light::kColor);
    lwc1(f0, a0, light::kColorG);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x004944f0: r == g: compare with b
        charge(ctx, 4);
        lwc1(f0, a0, light::kColorB);
        c_eq_s(f1, f0);
        if (!cond(ctx)) {
            backedge(ctx);
            goto L_004944e4;
        }
        // 0x00494500: grey: the private flag 1
        charge(ctx, 3);
        v0 = 1;
        sb(v0, a0, light::kPrivateFlags);
        backedge(ctx);
        goto L_004944e8;
    }
L_004944e4:
    charge(ctx, 1);
    sb(zero, a0, light::kPrivateFlags);
L_004944e8:
    charge(ctx, 2);
    v0 = a0;
    // 0x0049450c
    charge(ctx, 2);
}


// sub_494520 [lightRegisterPlugin] -- registers a light plugin (sub_4C61B0 on the light registry 0x77DD40)
// 0x00494520 sub_494520 -- 44 bytes; leaf frame (no stack)
void sub_494520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00494520
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8896);  // &0x77DD40 (the light plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_494550 [lightRegisterPluginStream] -- sets a light plugin's stream callbacks; its offset or -1
// 0x00494550 sub_494550 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_494550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00494550
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -8896);  // &0x77DD40 (the light plugin registry)
    a3 = v0;
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}


// sub_494760 [lightDestroy] -- destroys a light: the plugin destructors, off its frame (sub_4D18C0), back to its free list; 1
// 0x00494760 sub_494760 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_494760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494760
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -8896);  // &0x77DD40 (the light plugin registry)
    jal(ctx, 0x494778u, gen::fn_sub_4C6560_004c6560);
    a0 = s0;
    jal(ctx, 0x494780u, gen::fn_sub_4D18C0_004d18c0);
    lw(a0, gp, -17600);  // 0x7CE830 (the light module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    a1 = s0;
    jalr(ctx, 0x4947A4u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4947C0 [lightCreate] -- ($a0 = the light type) a light from the light free list, then the light plugins' constructors
// RwObject type 3, subtype = the light type, the sync sub_4944A0, radius 0, colour white (grey flag 1), cone 0, an
// empty sector-tie list, no world link, frame stamp = the engine's light frame - 1, flags 3.
// 0x004947C0 sub_4947C0 -- 232 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4947C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004947c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x30000;
    sd(ra, sp, 0x20);
    a1 = v1 | 0x12;
    sq(s1, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a2, gp, -17600);  // 0x7CE830 (the light module offset)
    a0 = 0x960000;
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(a0, a2);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4947F4u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x00494890
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00494808: fill the record and run the plugin constructors
        charge(ctx, 34);
        t0 = 3;
        a1 = 0x490000;
        sb(t0, s0, rwobj::kType);
        a0 = 0x780000;
        sb(s1, s0, light::kType);
        a1 = addiu(a1, 17568);  // &sub_4944A0
        sb(zero, s0, light::kFlags);
        a3 = 0x3F800000;
        sb(zero, s0, light::kPrivateFlags);
        a2 = 1;
        sw(zero, s0, light::kFrame);
        v1 = addiu(s0, 44);
        sw(a1, s0, light::kSync);
        v0 = 0x960000;
        sw(zero, s0, light::kRadius);
        a0 = addiu(a0, -8896);  // &0x77DD40 (the light plugin registry)
        sw(zero, s0, light::kMinusCosAngle);
        a1 = s0;
        sw(a3, s0, light::kColor);
        sw(a3, s0, light::kColorG);
        sw(a3, s0, light::kColorB);
        sw(a3, s0, light::kColorA);
        sb(a2, s0, light::kPrivateFlags);
        sw(v1, s0, light::kSectorTies);
        sw(v1, s0, light::kSectorTiesPrev);
        sw(zero, s0, light::kWorldLinkPrev);
        sw(zero, s0, light::kWorldLink);
        lhu(v0, v0, 122);  // 0x96007A (the engine's light frame stamp)
        v0 = addiu(v0, -1);
        sh(v0, s0, light::kLightFrame);
        link(ctx, 0x494880u);  // $ra first: the delay slot below depends on it
        sb(t0, s0, light::kFlags);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s0;
    }
    // 0x00494894 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4948B0 [lightModuleClose] -- the light module's close: every live light destroyed, the free list destroyed, count down
// 0x004948B0 sub_4948B0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4948B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004948b0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    a1 = 0x490000;
    sq(s0, sp, 0x0);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v1, gp, -17600);  // 0x7CE830 (the light module offset)
    s0 = a0;
    a1 = addiu(a1, 17552);  // &sub_494490
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    a2 = 0;
    jal(ctx, 0x4948DCu, gen::fn_sub_4C4200_004c4200);
    lw(v1, gp, -17600);  // 0x7CE830 (the light module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    link(ctx, 0x4948F4u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    lw(v1, gp, -17596);  // 0x7CE834 (the light module's open count)
    a0 = 0x960000;
    lw(a1, gp, -17600);  // 0x7CE830 (the light module offset)
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = s0;
    v1 = addiu(v1, -1);
    a0 = addu(a0, a1);
    sw(v1, gp, -17596);  // 0x7CE834 (the light module's open count)
    sw(zero, a0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_494930 [lightModuleOpen] -- the light module's open: the light free list (16-aligned, the static record 0x95DED0)
// 0x00494930 sub_494930 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_494930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494930
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x780000;
    sq(s0, sp, 0x0);
    a2 = 16;
    s0 = a0;
    sw(a1, gp, -17600);  // 0x7CE830 (the light module offset)
    lw(a0, v0, -8896);  // 0x77DD40 (the light plugin registry)
    t0 = addiu(t0, -8496);  // &0x95DED0 (the light free list's static record)
    lw(a1, gp, -20752);  // 0x7CDBE0 (the light free list's entries per block)
    lw(a3, gp, -20748);  // 0x7CDBE4 (the light free list's preallocated blocks)
    v0 = 0x40000;
    t1 = v0 | 0x12;
    jal(ctx, 0x494964u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17600);  // 0x7CE830 (the light module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x00494994: count the open, return the instance
        charge(ctx, 4);
        lw(v1, gp, -17596);  // 0x7CE834 (the light module's open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17596);  // 0x7CE834 (the light module's open count)
    } else {
        // 0x0049498c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004949a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4949C0 [materialPipelineStreamRead] -- reads a material's pipeline extension: the plugin id (and data) into globals
// The ids wait in gp 0x7CE83C / 0x7CE838 for the material's always callback. Returns the stream or 0.
// 0x004949C0 sub_4949C0 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4949C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004949c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = addiu(gp, -17588);  // &0x7CE83C (the material pipeline's plugin id read from the stream)
    jal(ctx, 0x4949DCu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x00494a00
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004949ec
        charge(ctx, 3);
        v0 = 8;
        if (s0 == v0) {
            // 0x00494a08
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(gp, -17592);  // &0x7CE838 (the material pipeline's plugin data read from the stream)
            a2 = 4;
            jal(ctx, 0x494A10u, gen::fn_sub_4C1910_004c1910);
            if (v0 != 0) {
                backedge(ctx);
                goto L_004949f8;
            }
            // 0x00494a20
            charge(ctx, 1);
            v0 = 0;
            // 0x00494a24 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004949f8:
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x00494a24 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_494A40 [materialPipelineStreamWrite] -- writes a material's pipeline extension: its pipeline's plugin id and data
// 0x00494A40 sub_494A40 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_494A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494a40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lw(v0, a2, material::kPipeline);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a1 = addiu(v0, 44);
    a2 = 4;
    jal(ctx, 0x494A60u, gen::fn_sub_4C17F0_004c17f0);
    if (v0 != 0) {
        // 0x00494a78
        charge(ctx, 7);
        lw(v0, s0, material::kPipeline);
        a0 = s1;
        a2 = 4;
        a1 = addiu(v0, 48);
        jal(ctx, 0x494A84u, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x00494a70
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00494a94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_494AB0 [materialPipelineStreamGetSize] -- 8 when the material has a pipeline with a plugin id, else 0
// 0x00494AB0 sub_494AB0 -- 44 bytes; leaf frame (no stack)
void sub_494AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00494ab0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, material::kPipeline);
    if (v0 != 0) {
        // 0x00494abc
        charge(ctx, 3);
        lw(v0, v0, pipeline::kPluginId);
        if (v0 == 0) {
            goto L_00494ad0;
        }
        // 0x00494ac8
        charge(ctx, 2);
        v0 = 8;
        // 0x00494ad4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00494ad0:
    charge(ctx, 1);
    v0 = 0;
    // 0x00494ad4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_494AE0 [materialModuleOpen] -- the material module's open: the material free list (4-aligned, static record 0x95DF00)
// 0x00494AE0 sub_494AE0 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_494AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494ae0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x780000;
    sq(s0, sp, 0x0);
    a2 = 4;
    s0 = a0;
    sw(a1, gp, -17584);  // 0x7CE840 (the material module offset)
    lw(a0, v0, -8864);  // 0x77DD60 (the material plugin registry)
    t0 = addiu(t0, -8448);  // &0x95DF00 (the material free list's static record)
    lw(a1, gp, -20744);  // 0x7CDBE8 (the material free list's entries per block)
    lw(a3, gp, -20740);  // 0x7CDBEC (the material free list's preallocated blocks)
    v0 = 0x40000;
    t1 = v0 | 0x7;
    jal(ctx, 0x494B14u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17584);  // 0x7CE840 (the material module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x00494b44: count the open, return the instance
        charge(ctx, 4);
        lw(v1, gp, -17580);  // 0x7CE844 (the material module's open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17580);  // 0x7CE844 (the material module's open count)
    } else {
        // 0x00494b3c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00494b54 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_494B70 [materialModuleClose] -- the material module's close: destroys the material free list; count down
// 0x00494B70 sub_494B70 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_494B70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00494b70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17584);  // 0x7CE840 (the material module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x00494b9c
        charge(ctx, 7);
        jal(ctx, 0x494B9Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17584);  // 0x7CE840 (the material module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x00494bb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17580);  // 0x7CE844 (the material module's open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17580);  // 0x7CE844 (the material module's open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_494BE0 [materialCreate] -- a material from its free list: one reference, white, no texture or pipeline, the default
// surface properties (0x77DD78); then the material plugins' constructors.
// 0x00494BE0 sub_494BE0 -- 212 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_494BE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00494be0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0x7;
    lw(a0, gp, -17584);  // 0x7CE840 (the material module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x494C0Cu);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x00494ca0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00494c20: fill the record and run the plugin constructors
        charge(ctx, 32);
        a1 = 255;
        v0 = 1;
        sb(a1, sp, 0x2C);
        a0 = 0x780000;
        sb(a1, sp, 0x2D);
        a2 = 0x780000;
        sb(a1, sp, 0x2E);
        v1 = 0x780000;
        sb(a1, sp, 0x2F);
        a0 = addiu(a0, -8864);  // &0x77DD60 (the material plugin registry)
        lbu(t2, sp, 0x2C);
        a1 = s0;
        lbu(t1, sp, 0x2D);
        sh(v0, s0, material::kRefCount);
        lbu(t0, sp, 0x2E);
        v0 = 0x780000;
        lbu(a3, sp, 0x2F);
        sb(t2, s0, material::kColor);
        sb(t1, s0, material::kColorG);
        sb(t0, s0, material::kColorB);
        sb(a3, s0, material::kColorA);
        sw(zero, s0, material::kTexture);
        sw(zero, s0, material::kPipeline);
        lwc1(f2, a2, -8840);  // 0x77DD78 (the default surface properties)
        lwc1(f1, v1, -8836);  // 0x77DD7C
        lwc1(f0, v0, -8832);  // 0x77DD80
        swc1(f2, s0, material::kAmbient);
        swc1(f1, s0, material::kSpecular);
        link(ctx, 0x494C90u);  // $ra first: the delay slot below depends on it
        swc1(f0, s0, material::kDiffuse);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s0;
    }
    // 0x00494ca4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_494DB0 [materialRegisterPlugin] -- registers a material plugin (sub_4C61B0 on the material registry 0x77DD60)
// 0x00494DB0 sub_494DB0 -- 44 bytes; leaf frame (no stack)
void sub_494DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00494db0
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8864);  // &0x77DD60 (the material plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_494DE0 [materialRegisterPluginStream] -- sets a material plugin's stream callbacks; its offset or -1
// 0x00494DE0 sub_494DE0 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_494DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00494de0
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -8864);  // &0x77DD60 (the material plugin registry)
    a3 = v0;
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}


// sub_494E10 [materialSetStreamRightsCallBack] -- sets a material plugin's rights callback; its offset or -1
// 0x00494E10 sub_494E10 -- 96 bytes, 2 chunks; leaf frame (no stack)
void sub_494E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00494e10
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = a0;
    a2 = a1;
    a0 = 0x780000;
    a1 = v0;
    a0 = addiu(a0, -8864);  // &0x77DD60 (the material plugin registry)
    // 0x004c5a00
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c5a0c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5a18
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5a24_4;
            }
            backedge(ctx);
        }
    }
L_004c5a28:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c5a3c
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5a30
        charge(ctx, 3);
        sw(a2, v1, plugentry::kRightsCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c5a40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5a24_4:
    charge(ctx, 1);
    goto L_004c5a28;
}


// sub_495300 [matListInit] -- empties a material list (array, count, capacity 0); returns it
// 0x00495300 sub_495300 -- 20 bytes; leaf frame (no stack)
void sub_495300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    // 0x00495300
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, matlist::kCapacity);
    v0 = a0;
    sw(zero, a0, matlist::kArray);
    sw(zero, a0, matlist::kCount);
}


// sub_495340 [matListAppendMaterial] -- appends a material to a list (grown by 20); its index or -1
// The array grows through RwRealloc / RwMalloc (hint 0x1030008); the material gets a reference (+24).
// 0x00495340 sub_495340 -- 308 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_495340(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00495340
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, a0, matlist::kCount);
    lw(v0, a0, matlist::kCapacity);
    at = slt(v1, v0);
    s1 = a1;
    if (at != 0) {
        // 0x004953e0: room left: store it, add a reference
        charge(ctx, 13);
        lw(v0, s2, matlist::kArray);
        v1 = sll(v1, 2);
        v0 = addu(v0, v1);
        sw(s1, v0, 0);
        lh(v0, s1, material::kRefCount);
        v0 = addiu(v0, 1);
        sh(v0, s1, material::kRefCount);
        lw(v0, s2, matlist::kCount);
        v0 = addiu(v0, 1);
        sw(v0, s2, matlist::kCount);
        lw(v0, s2, matlist::kCount);
        v0 = addiu(v0, -1);
    } else {
        // 0x0049536c: full: grow the array by 20 entries
        charge(ctx, 4);
        lw(a0, s2, matlist::kArray);
        v0 = addiu(v0, 20);
        s0 = sll(v0, 2);
        if (a0 == 0) {
            // 0x00495414
            charge(ctx, 8);
            v0 = 0x1030000;
            a1 = v0 | 0x8;  // &0x1030008 (a memory hint)
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = s0;
            jalr(ctx, 0x495424u, v0.u());
            backedge(ctx);
        } else {
            // 0x0049537c
            charge(ctx, 6);
            v0 = 0x1030000;
            a2 = v0 | 0x8;  // &0x1030008 (a memory hint)
            v0 = 0x960000;
            lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
            a1 = s0;
            jalr(ctx, 0x49538Cu, v0.u());
        }
        // 0x00495394
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x00495434: out of memory: error 0x80000013, -1
            charge(ctx, 10);
            v0 = 2;
            a1 = s0;
            sw(v0, sp, 0x48);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x495444u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x48);
            jal(ctx, 0x495450u, gen::fn_sub_4C1C50_004c1c50);
            v0 = si(-1);
        } else {
            // 0x0049539c: store it in the grown array, add a reference
            charge(ctx, 17);
            sw(v0, s2, matlist::kArray);
            lw(v1, s2, matlist::kCapacity);
            v1 = addiu(v1, 20);
            sw(v1, s2, matlist::kCapacity);
            lw(v1, s2, matlist::kCount);
            v1 = sll(v1, 2);
            v0 = addu(v0, v1);
            sw(s1, v0, 0);
            lh(v0, s1, material::kRefCount);
            v0 = addiu(v0, 1);
            sh(v0, s1, material::kRefCount);
            lw(v0, s2, matlist::kCount);
            v0 = addiu(v0, 1);
            sw(v0, s2, matlist::kCount);
            lw(v0, s2, matlist::kCount);
            v0 = addiu(v0, -1);
        }
    }
    // 0x0049545c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_495480 [matListFindMaterial] -- the index of a material in a list, searched from the end; -1 when it is missing
// 0x00495480 sub_495480 -- 64 bytes; leaf frame (no stack)
void sub_495480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00495480
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, matlist::kCount);
    v0 = addiu(v1, -1);
    if (i64(v1) > 0) {
        // 0x0049548c
        charge(ctx, 3);
        lw(v1, a0, 0);
        a0 = sll(v0, 2);
        a0 = addu(v1, a0);
        for (;;) {
            // 0x00495498
            charge(ctx, 3);
            lw(v1, a0, 0);
            if (v1 == a1) {
                break;
            }
            // 0x004954a4
            charge(ctx, 4);
            v1 = v0;
            a0 = addiu(a0, -4);
            v0 = addiu(v0, -1);
            if (i64(v1) <= 0) {
                goto L_004954b4_4;
            }
            backedge(ctx);
        }
    }
    // 0x004954b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004954b4_4:
    charge(ctx, 1);
    // 0x004954b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4959C0 [meshMalloc] -- RwMalloc(size, 0x30502) for mesh data (a tail call)
// 0x004959C0 sub_4959C0 -- 24 bytes; leaf frame (no stack)
void sub_4959C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x004959c0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x30000;
    a1 = v0 | 0x502;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4959E0 [meshModuleClose] -- the mesh module's close: counts down; the last close destroys the build-mesh free list
// 0x004959E0 sub_4959E0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4959E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004959e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17564);  // 0x7CE854 (the mesh module's open count)
    s0 = a0;
    v0 = addiu(v0, -1);
    sw(v0, gp, -17564);  // 0x7CE854 (the mesh module's open count)
    if (v0 == 0) {
        // 0x00495a00
        charge(ctx, 3);
        lw(a0, gp, -17576);  // 0x7CE848 (the build-mesh free list)
        if (a0 != 0) {
            // 0x00495a0c
            charge(ctx, 3);
            jal(ctx, 0x495A0Cu, gen::fn_sub_4C3C30_004c3c30);
            sw(zero, gp, -17576);  // 0x7CE848 (the build-mesh free list)
        }
    }
    // 0x00495a18 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_495A30 [meshModuleOpen] -- the mesh module's open: the build-mesh free list (once), the module's primitive code tables
// ($a1 = the module offset) The free list holds 12-byte records, 50 a block; the table bytes at engine + offset.
// 0x00495A30 sub_495A30 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_495A30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00495a30
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17564);  // 0x7CE854 (the mesh module's open count)
    s0 = a0;
    sw(a1, gp, -17568);  // 0x7CE850 (the mesh module offset)
    if (v0 == 0) {
        // 0x00495ac4: the first open: the build-mesh free list
        charge(ctx, 8);
        v0 = 0x40000;
        a0 = 12;
        a1 = 50;
        a2 = 4;
        a3 = v0 | 0x502;
        jal(ctx, 0x495AD4u, gen::fn_sub_4C3B50_004c3b50);
        sw(v0, gp, -17576);  // 0x7CE848 (the build-mesh free list)
        if (v0 != 0) {
            backedge(ctx);
            goto L_00495a4c;
        }
        // 0x00495ae4
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x00495aec
            charge(ctx, 3);
            a0 = v0;
            jal(ctx, 0x495AECu, gen::fn_sub_4C3C30_004c3c30);
            sw(zero, gp, -17576);  // 0x7CE848 (the build-mesh free list)
        }
        // 0x00495af8
        charge(ctx, 1);
        v0 = 0;
        // 0x00495afc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_00495a4c:
    charge(ctx, 30);
    lw(t4, gp, -17568);  // 0x7CE850 (the mesh module offset)
    t3 = 0x960000;
    t3 = addiu(t3, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(t2, gp, -17564);  // 0x7CE854 (the mesh module's open count)
    t5 = 1;
    t1 = 3;
    t0 = 4;
    a3 = 5;
    a2 = 2;
    a1 = 6;
    a0 = 8;
    v1 = 16;
    t3 = addu(t3, t4);
    v0 = s0;
    sh(t5, t3, 0);
    t2 = addiu(t2, 1);
    sb(t1, t3, 8);
    sb(t0, t3, 9);
    sb(a3, t3, 10);
    sb(t5, t3, 12);
    sb(a2, t3, 16);
    sb(a1, t3, 24);
    sb(t0, t3, 40);
    sb(a0, t3, 41);
    sb(zero, t3, 42);
    sb(t5, t3, 43);
    sb(a2, t3, 44);
    sw(t2, gp, -17564);  // 0x7CE854 (the mesh module's open count)
    sb(v1, t3, 45);
    // 0x00495afc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_495B10 [buildMeshCreate] -- ($a0 = triangles) a build mesh from its free list with room for n 20-byte triangles
// (RwMalloc, hint 0x1030502); 0 and error 0x80000013 when either allocation fails (the record goes back).
// 0x00495B10 sub_495B10 -- 272 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_495B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00495b10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x30000;
    sd(ra, sp, 0x30);
    a1 = v0 | 0x502;
    sq(s2, sp, 0x20);
    v0 = 0x960000;
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x495B38u);  // $ra = the return address
    lw(a0, gp, -17576);  // 0x7CE848 (the build-mesh free list)
    call_ptr(ctx, jt);
    s1 = v0;
    if (s1 == 0) {
        // 0x00495be0: no record: error 0x80000013, 0
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x40);
        a0 = v0 | 0x13;
        a1 = 12;
        jal(ctx, 0x495BF0u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x44);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x495BFCu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x00495b4c
        charge(ctx, 2);
        sw(zero, s1, buildmesh::kCount);
        if (s2 == 0) {
            // 0x00495b54: no triangles: no array
            charge(ctx, 2);
            sw(zero, s1, buildmesh::kTriangles);
            sw(zero, s1, buildmesh::kCapacity);
            goto L_00495b5c;
        }
        // 0x00495b64: the triangle records
        charge(ctx, 13);
        v0 = 0x1030000;
        v1 = sll(s2, 2);
        a1 = v0 | 0x502;  // &0x1030502 (a memory hint)
        v1 = addu(v1, s2);
        v0 = 0x960000;
        s0 = sll(v1, 2);
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = s0;
        jalr(ctx, 0x495B80u, v0.u());
        sw(v0, s1, buildmesh::kTriangles);
        lw(v0, s1, buildmesh::kTriangles);
        if (v0 == 0) {
            // 0x00495ba0: out of memory: the record back to the free list, error 0x80000013, 0
            charge(ctx, 16);
            v0 = 0x960000;
            lw(a0, gp, -17576);  // 0x7CE848 (the build-mesh free list)
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            a1 = s1;
            jalr(ctx, 0x495BACu, v0.u());
            v0 = 2;
            a1 = s0;
            sw(v0, sp, 0x48);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x495BC4u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x48);
            jal(ctx, 0x495BD0u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x00495b98
            charge(ctx, 2);
            sw(s2, s1, buildmesh::kCapacity);
            backedge(ctx);
        L_00495b5c:
            charge(ctx, 2);
            v0 = s1;
        }
    }
    // 0x00495c08 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_495C20 [buildMeshDestroy] -- frees a build mesh's triangle records and returns it to its free list; 1
// 0x00495C20 sub_495C20 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_495C20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00495c20
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, buildmesh::kTriangles);
    if (a0 != 0) {
        // 0x00495c3c
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x495C44u, v0.u());
        sw(zero, s0, buildmesh::kTriangles);
    }
    // 0x00495c50
    charge(ctx, 10);
    v0 = 0x960000;
    lw(a0, gp, -17576);  // 0x7CE848 (the build-mesh free list)
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    a1 = s0;
    jalr(ctx, 0x495C5Cu, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_495C80 [meshHeaderDestroy] -- frees a mesh header (RwFree) when any of its first fields is set; 1
// 0x00495C80 sub_495C80 -- 112 bytes; frame 0x10: ra sp+0x0
void sub_495C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00495c80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 0);
    if (v0 == 0) {
        // 0x00495c94
        charge(ctx, 3);
        lhu(v0, a0, 4);
        if (v0 != 0) {
            goto L_00495ccc;
        }
        // 0x00495ca0
        charge(ctx, 3);
        lhu(v0, a0, 6);
        if (v0 != 0) {
            goto L_00495ccc;
        }
        // 0x00495cac
        charge(ctx, 3);
        lw(v0, a0, 8);
        if (v0 != 0) {
            goto L_00495ccc;
        }
        // 0x00495cb8
        charge(ctx, 3);
        lw(v0, a0, 12);
        if (v0 != 0) {
            goto L_00495ccc;
        }
        goto L_00495cc4;
    }
L_00495ccc:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jalr(ctx, 0x495CD4u, v0.u());
    backedge(ctx);
L_00495cc4:
    charge(ctx, 2);
    v0 = 1;
    // 0x00495ce4
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4991F0 [sectorModuleOpen] -- the world-sector module's open: counts the open
// 0x004991F0 sub_4991F0 -- 20 bytes; leaf frame (no stack)
void sub_4991F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004991f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17556);  // 0x7CE85C (the world-sector module's open count)
    v0 = a0;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17556);  // 0x7CE85C (the world-sector module's open count)
}


// sub_499210 [sectorModuleClose] -- the world-sector module's close: counts down
// 0x00499210 sub_499210 -- 20 bytes; leaf frame (no stack)
void sub_499210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00499210
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17556);  // 0x7CE85C (the world-sector module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17556);  // 0x7CE85C (the world-sector module's open count)
}


// sub_499250 [sectorRegisterPlugin] -- registers a world-sector plugin (sub_4C61B0 on the sector registry 0x77DDB0)
// 0x00499250 sub_499250 -- 44 bytes; leaf frame (no stack)
void sub_499250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00499250
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_499280 [sectorRegisterPluginStream] -- sets a world-sector plugin's stream callbacks; its offset or -1
// 0x00499280 sub_499280 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_499280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00499280
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry)
    a3 = v0;
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}


// sub_4992B0 [sectorSetStreamAlwaysCallBack] -- sets a world-sector plugin's 'always' stream callback; its offset or -1
// 0x004992B0 sub_4992B0 -- 96 bytes, 2 chunks; leaf frame (no stack)
void sub_4992B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004992b0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = a0;
    a2 = a1;
    a0 = 0x780000;
    a1 = v0;
    a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry)
    // 0x004c59b0
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c59bc
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c59c8
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c59d4_4;
            }
            backedge(ctx);
        }
    }
L_004c59d8:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59ec
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c59e0
        charge(ctx, 3);
        sw(a2, v1, plugentry::kAlwaysCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c59d4_4:
    charge(ctx, 1);
    goto L_004c59d8;
}


// sub_4992D0 [sectorSetStreamRightsCallBack] -- sets a world-sector plugin's rights callback; its offset or -1
// 0x004992D0 sub_4992D0 -- 96 bytes, 2 chunks; leaf frame (no stack)
void sub_4992D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004992d0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = a0;
    a2 = a1;
    a0 = 0x780000;
    a1 = v0;
    a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry)
    // 0x004c5a00
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c5a0c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5a18
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5a24_4;
            }
            backedge(ctx);
        }
    }
L_004c5a28:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c5a3c
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5a30
        charge(ctx, 3);
        sw(a2, v1, plugentry::kRightsCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c5a40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5a24_4:
    charge(ctx, 1);
    goto L_004c5a28;
}


// sub_499400 [sectorBuildMesh] -- builds a sector's mesh from its triangles
// ($a0 = the world, $a1 = a build mesh, $a2 = the sector, $a3 = its materials) Collects the distinct textures, rasters
// and pipelines of the triangles' materials (three scratch arrays, freed afterwards), adds every triangle to the build
// mesh (sub_495CF0), then generates the mesh (sub_499140: tri-strips when the world's flag bit 0) into the sector's
// +120; on failure the build mesh is destroyed and 0 returned. Returns the world.
// 0x00499400 sub_499400 -- 796 bytes; frame 0xC0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
void sub_499400(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00499400
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    s7 = a2;
    sq(s5, sp, 0x60);
    s6 = a1;
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = 0;
    sq(s1, sp, 0x20);
    s2 = 0;
    sq(s0, sp, 0x10);
    s1 = 0;
    lw(v0, a0, 20);
    sw(a3, sp, 0xB8);
    sw(a0, sp, 0xBC);
    if (v0 != 0) {
        // 0x00499450: three scratch arrays, 4 bytes per material
        charge(ctx, 25);
        s0 = sll(v0, 2);
        s5 = 0x960000;
        v0 = 0x10000;
        s5 = addiu(s5, 376);  // &0x960178 (RwMalloc slot)
        a1 = v0 | 0x6;
        lw(v0, s5, 0);  // 0x960178 (RwMalloc slot)
        a0 = s0;
        jalr(ctx, 0x499468u, v0.u());
        s4 = v0;
        v1 = 0x10000;
        lw(v0, s5, 0);  // 0x960178 (RwMalloc slot)
        a0 = s0;
        a1 = v1 | 0x507;
        jalr(ctx, 0x499480u, v0.u());
        lw(v1, s5, 0);  // 0x960178 (RwMalloc slot)
        fp = v0;
        v0 = 0x10000;
        a0 = s0;
        a1 = v0 | 0x507;
        jalr(ctx, 0x499498u, v1.u());
        sw(v0, sp, 0xB4);
        lhu(v0, s7, sector::kNumTriangles);
        at = slt(0, v0);
        s5 = 0;
        if (at != 0) {
            // 0x004994b4: each triangle: its material's texture, raster and pipeline into the distinct lists
            charge(ctx, 1);
            s0 = 0;
            for (;;) {
                // 0x004994b8
                charge(ctx, 13);
                lw(v0, s7, sector::kTriangles);
                a2 = s3 & 0xFFFF;
                at = slt(0, a2);
                v1 = 0;
                t1 = addu(v0, s0);
                lhu(v0, t1, 6);
                a0 = sll(v0, 2);
                lw(v0, sp, 0xB8);
                v0 = addu(v0, a0);
                lw(a1, v0, 0);
                lw(v0, a1, 0);
                t2 = 0;
                if (at != 0) {
                    // 0x004994ec
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004994f0
                        charge(ctx, 6);
                        a0 = t2 & 0xFFFF;
                        a0 = sll(a0, 2);
                        a0 = addu(s4, a0);
                        lw(a0, a0, 0);
                        if (a0 == v0) {
                            break;
                        }
                        // 0x00499508
                        charge(ctx, 5);
                        a0 = addiu(t2, 1);
                        t2 = a0 & 0xFFFF;
                        a0 = slt(t2, a2);
                        if (a0 == 0) {
                            goto L_0049951c_7;
                        }
                        backedge(ctx);
                    }
                }
            L_00499520:
                charge(ctx, 3);
                a0 = t2 & 0xFFFF;
                if (a0 == a2) {
                    // 0x0049968c
                    charge(ctx, 6);
                    a2 = sll(a0, 2);
                    a0 = addiu(s3, 1);
                    a2 = addu(s4, a2);
                    s3 = a0 & 0xFFFF;
                    sw(v0, a2, 0);
                    backedge(ctx);
                } else {
                    // 0x0049952c
                    charge(ctx, 1);
                }
                // 0x00499530
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x00499538
                    charge(ctx, 2);
                    lw(v1, v0, 0);
                }
                // 0x00499540
                charge(ctx, 4);
                a0 = s2 & 0xFFFF;
                at = slt(0, a0);
                t3 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x00499550
                        charge(ctx, 6);
                        v0 = t3 & 0xFFFF;
                        v0 = sll(v0, 2);
                        v0 = addu(fp, v0);
                        lw(v0, v0, 0);
                        if (v0 == v1) {
                            break;
                        }
                        // 0x00499568
                        charge(ctx, 5);
                        v0 = addiu(t3, 1);
                        t3 = v0 & 0xFFFF;
                        v0 = slt(t3, a0);
                        if (v0 == 0) {
                            goto L_0049957c_15;
                        }
                        backedge(ctx);
                    }
                }
            L_00499580:
                charge(ctx, 3);
                v0 = t3 & 0xFFFF;
                if (v0 == a0) {
                    // 0x004996a8
                    charge(ctx, 6);
                    v0 = sll(v0, 2);
                    a0 = addu(fp, v0);
                    v0 = addiu(s2, 1);
                    sw(v1, a0, 0);
                    s2 = v0 & 0xFFFF;
                    backedge(ctx);
                } else {
                    // 0x0049958c
                    charge(ctx, 1);
                }
                // 0x00499590
                charge(ctx, 5);
                lw(v1, a1, 8);
                v0 = s1 & 0xFFFF;
                at = slt(0, v0);
                a0 = 0;
                if (at != 0) {
                    // 0x004995a4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004995a8
                        charge(ctx, 7);
                        a2 = a0 & 0xFFFF;
                        a3 = sll(a2, 2);
                        lw(a2, sp, 0xB4);
                        a2 = addu(a2, a3);
                        lw(a2, a2, 0);
                        if (a2 != v1) {
                            // 0x004995c4
                            charge(ctx, 5);
                            a0 = addiu(a0, 1);
                            a0 = a0 & 0xFFFF;
                            a2 = slt(a0, v0);
                            if (a2 != 0) {
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                }
                // 0x004995d8
                charge(ctx, 3);
                a2 = a0 & 0xFFFF;
                if (a2 == v0) {
                    // 0x004996c0
                    charge(ctx, 7);
                    lw(v0, sp, 0xB4);
                    a2 = sll(a2, 2);
                    a2 = addu(v0, a2);
                    v0 = addiu(s1, 1);
                    sw(v1, a2, 0);
                    s1 = v0 & 0xFFFF;
                    backedge(ctx);
                } else {
                    // 0x004995e4: add the triangle to the build mesh
                    charge(ctx, 1);
                }
                // 0x004995e8
                charge(ctx, 12);
                sd(a0, sp, 0x0);
                lhu(a2, t1, 0);
                lhu(a3, t1, 2);
                lhu(t0, t1, 4);
                lhu(t1, t1, 6);
                a0 = s6;
                jal(ctx, 0x4995FCu, gen::fn_sub_495CF0_00495cf0);
                lhu(v0, s7, sector::kNumTriangles);
                s5 = addiu(s5, 1);
                v0 = slt(s5, v0);
                s0 = addiu(s0, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00499618: free the scratch arrays
        charge(ctx, 11);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        a0 = s4;
        jalr(ctx, 0x499624u, v0.u());
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        a0 = fp;
        jalr(ctx, 0x499630u, v0.u());
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x49963Cu);  // $ra = the return address
        lw(a0, sp, 0xB4);
        call_ptr(ctx, jt);
    }
    // 0x00499644: generate the mesh: tri-strips when the world's flag bit 0
    charge(ctx, 5);
    lw(v0, sp, 0xBC);
    lw(v0, v0, 8);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0049966c
        charge(ctx, 3);
        a0 = s6;
        a1 = 0;
        jal(ctx, 0x499670u, gen::fn_sub_499140_00499140);
    } else {
        // 0x00499658
        charge(ctx, 5);
        a0 = s6;
        a1 = 1;
        jal(ctx, 0x49965Cu, gen::fn_sub_499140_00499140);
    }
    // 0x00499678: keep it in the sector (0: destroy the build mesh, 0)
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x004996e0
        charge(ctx, 3);
        a0 = s6;
        jal(ctx, 0x4996E0u, gen::fn_sub_495C20_00495c20);
        v0 = 0;
    } else {
        // 0x00499680
        charge(ctx, 3);
        sw(v0, s7, sector::kMesh);
        lw(v0, sp, 0xBC);
    }
    // 0x004996ec (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xC0);
    return;
L_0049951c_7:
    charge(ctx, 1);
    goto L_00499520;
L_0049957c_15:
    charge(ctx, 1);
    goto L_00499580;
}


// sub_499D30 [worldCalcSectorBoxes] -- gives every sector of a world the box of its BSP cell
// Walks the BSP with an explicit stack of boxes, starting from the world's box: below a plane the box's maximum on
// the plane's axis becomes the left value, above it its minimum the right value; each sector stores its box.
// 0x00499D30 sub_499D30 -- 352 bytes; frame 0x720
void sub_499D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x00499d30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x720);
    lw(a3, a0, world::kRootNode);
    lwc1(f5, a0, world::kBoxSup);
    t0 = 0;
    lwc1(f4, a0, 84);
    lwc1(f3, a0, 88);
    lwc1(f2, a0, world::kBoxInf);
    lwc1(f1, a0, 96);
    lwc1(f0, a0, 100);
    swc1(f5, sp, 0x600);
    swc1(f4, sp, 0x604);
    swc1(f3, sp, 0x608);
    swc1(f2, sp, 0x60C);
    swc1(f1, sp, 0x610);
    swc1(f0, sp, 0x614);
    for (;;) {
        // 0x00499d6c: a sector: store the box, pop the next node and its box
        charge(ctx, 3);
        lw(v0, a3, bsp::kType);
        if (i64(v0) < 0) {
            // 0x00499e00
            charge(ctx, 34);
            lwc1(f5, sp, 0x600);
            v0 = sll(t0, 2);
            lwc1(f4, sp, 0x604);
            v1 = addu(v0, sp);
            lwc1(f3, sp, 0x608);
            v0 = sll(t0, 1);
            lwc1(f2, sp, 0x60C);
            v0 = addu(v0, t0);
            lwc1(f1, sp, 0x610);
            v0 = sll(v0, 3);
            lwc1(f0, sp, 0x614);
            v0 = addu(v0, sp);
            swc1(f5, a3, sector::kBoxSup);
            v0 = addiu(v0, 0);
            swc1(f4, a3, 76);
            t0 = addiu(t0, -1);
            swc1(f3, a3, 80);
            swc1(f2, a3, sector::kBoxInf);
            swc1(f1, a3, 88);
            swc1(f0, a3, 92);
            lwc1(f5, v0, 0);
            lw(a3, v1, 1568);
            lwc1(f4, v0, 4);
            lwc1(f3, v0, 8);
            lwc1(f2, v0, 12);
            lwc1(f1, v0, 16);
            lwc1(f0, v0, 20);
            swc1(f5, sp, 0x600);
            swc1(f4, sp, 0x604);
            swc1(f3, sp, 0x608);
            swc1(f2, sp, 0x60C);
            swc1(f1, sp, 0x610);
            swc1(f0, sp, 0x614);
            backedge(ctx);
        } else {
            // 0x00499d78: a plane: push the right child with its box, go left with the left box
            charge(ctx, 30);
            t0 = addiu(t0, 1);
            lw(a2, a3, bsp::kRight);
            v0 = sll(t0, 1);
            v1 = sll(t0, 2);
            v0 = addu(v0, t0);
            a1 = addu(v1, sp);
            v0 = sll(v0, 3);
            v0 = addu(v0, sp);
            v1 = addiu(v0, 0);
            lwc1(f2, sp, 0x600);
            lw(v0, a3, bsp::kType);
            lwc1(f1, a3, bsp::kRightValue);
            sw(a2, a1, 1568);
            lwc1(f0, a3, bsp::kLeftValue);
            lwc1(f6, sp, 0x604);
            lwc1(f5, sp, 0x608);
            lwc1(f4, sp, 0x60C);
            swc1(f2, v1, 0);
            lwc1(f3, sp, 0x610);
            lwc1(f2, sp, 0x614);
            lw(a3, a3, bsp::kLeft);
            swc1(f6, v1, 4);
            swc1(f5, v1, 8);
            swc1(f4, v1, 12);
            swc1(f3, v1, 16);
            swc1(f2, v1, 20);
            v1 = addu(v0, v1);
            v0 = addu(v0, sp);
            swc1(f1, v1, 12);
            swc1(f0, v0, 1536);
        }
        // 0x00499df0
        charge(ctx, 2);
        if (i64(t0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00499df8
    charge(ctx, 2);
    v0 = a0;
    // 0x00499e88
    charge(ctx, 2);
    sp = addiu(sp, 0x720);
}


// sub_499E90 [pendingPairAdd] -- links a new {first, second} record at the head of the world module's pending list
// (a record from the module's free list, tag 0x40507; read back by sub_499F40). Returns the record or 0.
// 0x00499E90 sub_499E90 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_499E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00499e90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x960000;
    sd(ra, sp, 0x20);
    v0 = 0x40000;
    sq(s1, sp, 0x10);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
    s0 = a1;
    a1 = v0 | 0x507;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x499EC8u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    if (v0 != 0) {
        // 0x00499ed8
        charge(ctx, 20);
        sw(s1, v0, 0);
        a1 = 0x960000;
        sw(s0, v0, 4);
        a1 = addiu(a1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        lw(v1, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
        a0 = addiu(v0, 8);
        v1 = addu(a1, v1);
        lw(v1, v1, 4);
        sw(v1, v0, 8);
        lw(v1, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
        v1 = addu(a1, v1);
        v1 = addiu(v1, 4);
        sw(v1, v0, 12);
        lw(v1, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
        v1 = addu(a1, v1);
        lw(v1, v1, 4);
        sw(a0, v1, 4);
        lw(v1, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
        v1 = addu(a1, v1);
        sw(a0, v1, 4);
    }
    // 0x00499f28 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_499F40 [pendingPairRemove] -- unlinks and frees the pending record whose first word is $a0 (if any)
// 0x00499F40 sub_499F40 -- 140 bytes; frame 0x10: ra sp+0x0
void sub_499F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00499f40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x960000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(a1, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
    v1 = addu(v1, a1);
    lw(a3, v1, 4);
    a2 = addiu(v1, 4);
    if (a3 != a2) {
        for (;;) {
            // 0x00499f68
            charge(ctx, 3);
            lw(v1, a3, -8);
            a1 = addiu(a3, -8);
            if (v1 == a0) {
                goto L_00499f74_2;
            }
            // 0x00499fb4
            charge(ctx, 3);
            lw(a3, a3, 0);
            if (a3 == a2) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00499fc0
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x00499fc4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    return;
L_00499f74_2:
    charge(ctx, 16);
    lw(a2, a1, 8);
    v1 = 0x960000;
    lw(a0, a1, 12);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    sw(a2, a0, 0);
    lw(a2, a1, 12);
    lw(a0, a1, 8);
    sw(a2, a0, 4);
    lw(a0, gp, -17552);  // 0x7CE860 (the pending-pair list module offset)
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x499FA4u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    ld(ra, sp, 0x0);
    // 0x00499fc4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}


// sub_499FD0 [worldDestroySectorMeshes] -- frees every sector's mesh header (sub_495C80) and clears it; the world (0: no tree)
// 0x00499FD0 sub_499FD0 -- 168 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_499FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499fd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(s1, a0, world::kRootNode);
    s0 = 0;
    if (s1 == 0) {
        // 0x0049a028
        charge(ctx, 2);
        v0 = 0;
    } else {
        for (;;) {
            // 0x00499ff4: a sector: free its mesh, pop the next node
            charge(ctx, 3);
            lw(v0, s1, bsp::kType);
            if (i64(v0) < 0) {
                // 0x0049a030
                charge(ctx, 3);
                lw(a0, s1, sector::kMesh);
                if (a0 != 0) {
                    // 0x0049a03c
                    charge(ctx, 3);
                    jal(ctx, 0x49A03Cu, gen::fn_sub_495C80_00495c80);
                    sw(zero, s1, sector::kMesh);
                }
                // 0x0049a048
                charge(ctx, 5);
                v0 = sll(s0, 2);
                v0 = addu(v0, sp);
                lw(s1, v0, 64);
                s0 = addiu(s0, -1);
                backedge(ctx);
            } else {
                // 0x0049a000: a plane: push the right child, go left
                charge(ctx, 6);
                lw(v1, s1, bsp::kRight);
                s0 = addiu(s0, 1);
                v0 = sll(s0, 2);
                v0 = addu(v0, sp);
                lw(s1, s1, bsp::kLeft);
                sw(v1, v0, 64);
            }
            // 0x0049a018
            charge(ctx, 2);
            if (i64(s0) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049a020
        charge(ctx, 2);
        v0 = s2;
    }
    // 0x0049a060 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}


// sub_49A080 [worldBuildSectorMeshes] -- builds the mesh of every sector that has none; the world, or 0 on a failure
// Per sector: a build mesh for its triangles (sub_495B10), then sub_499400 with the world's materials from the
// sector's base index.
// 0x0049A080 sub_49A080 -- 240 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49A080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049a080
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(s1, a0, world::kRootNode);
    s0 = 0;
    if (s1 == 0) {
        // 0x0049a0e0
        charge(ctx, 2);
        v0 = 0;
    } else {
        for (;;) {
            // 0x0049a0a8: a plane: push the right child, go left
            charge(ctx, 3);
            lw(v0, s1, bsp::kType);
            if (i64(v0) >= 0) {
                // 0x0049a0b4
                charge(ctx, 7);
                lw(v1, s1, bsp::kRight);
                s0 = addiu(s0, 1);
                v0 = sll(s0, 2);
                v0 = addu(v0, sp);
                lw(s1, s1, bsp::kLeft);
                sw(v1, v0, 80);
                goto L_0049a0d0;
            }
            // 0x0049a0e8: a sector without a mesh: build it
            charge(ctx, 6);
            lhu(a0, s1, sector::kMatListBase);
            lw(v1, s2, world::kMaterials);
            lw(v0, s1, sector::kMesh);
            a0 = sll(a0, 2);
            s3 = addu(v1, a0);
            if (v0 == 0) {
                // 0x0049a118
                charge(ctx, 4);
                link(ctx, 0x49A118u);  // $ra first: the delay slot below depends on it
                lhu(a0, s1, sector::kNumTriangles);
                call(ctx, gen::fn_sub_495B10_00495b10);
                if (v0 == 0) {
                    goto L_0049a150;
                }
                // 0x0049a128: sub_499400 with the sector's materials
                charge(ctx, 8);
                a0 = s2;
                a2 = s1;
                a3 = s3;
                a1 = v0;
                jal(ctx, 0x49A134u, gen::fn_sub_499400_00499400);
                s2 = v0;
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
                goto L_0049a100;
            }
        L_0049a100:
            charge(ctx, 5);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            lw(s1, v0, 80);
            s0 = addiu(s0, -1);
            backedge(ctx);
        L_0049a0d0:
            charge(ctx, 2);
            if (i64(s0) < 0) {
                goto L_0049a0d8_4;
            }
            backedge(ctx);
        }
        // 0x0049a148
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0049a154 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
    return;
L_0049a0d8_4:
    charge(ctx, 2);
    v0 = s2;
    // 0x0049a154 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
    return;
L_0049a150:
    charge(ctx, 1);
    v0 = 0;
    // 0x0049a154 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}


// sub_49A7C0 [worldForAllMaterials] -- calls a callback on each material of a world until it returns 0; returns the world
// 0x0049A7C0 sub_49A7C0 -- 168 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49A7C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049a7c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, world::kNumMaterials);
    v0 = slt(0, s0);
    s2 = 0;
    if (v0 != 0) {
        // 0x0049a804
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x0049a808
            charge(ctx, 7);
            lw(v0, s5, world::kMaterials);
            v0 = addu(v0, s1);
            lw(a0, v0, 0);
            a1 = s3;
            jalr(ctx, 0x49A814u, s4.u());
            if (v0 == 0) {
                goto L_0049a824_4;
            }
            // 0x0049a82c
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, s0);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049a83c
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x0049a7fc
    charge(ctx, 2);
    v0 = s5;
    // 0x0049a844 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_0049a824_4:
    charge(ctx, 2);
    v0 = s5;
    // 0x0049a844 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_49A920 [worldRegisterPlugin] -- registers a world plugin (sub_4C61B0 on the world registry 0x77DDD0)
// 0x0049A920 sub_49A920 -- 44 bytes; leaf frame (no stack)
void sub_49A920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0049a920
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -8752);  // &0x77DDD0 (the world plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_49A950 [worldRegisterPluginStream] -- sets a world plugin's stream callbacks; its offset or -1
// 0x0049A950 sub_49A950 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_49A950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0049a950
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -8752);  // &0x77DDD0 (the world plugin registry)
    a3 = v0;
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}


// sub_49AAF0 [worldTiesModuleOpen] -- the world-ties module's open: the atomic-tie and light-tie free lists (24-byte records)
// The render frame stamp starts at 1; +8 of the module is cleared. 0 when a free list cannot be made.
// 0x0049AAF0 sub_49AAF0 -- 256 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49AAF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049aaf0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a2 = 4;
    sw(a1, gp, -17528);  // 0x7CE878 (the world-ties module offset)
    s0 = a0;
    lw(a1, gp, -20736);  // 0x7CDBF0 (the atomic-tie free list's entries per block)
    a0 = 24;
    lw(a3, gp, -20732);  // 0x7CDBF4 (the atomic-tie free list's preallocated blocks)
    t0 = addiu(t0, -8304);  // &0x95DF90 (the atomic-tie free list's static record)
    t1 = v0 | 0x507;
    jal(ctx, 0x49AB20u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x0049ab50: the light-tie free list
        charge(ctx, 17);
        lw(a1, gp, -20728);  // 0x7CDBF8 (the light-tie free list's entries per block)
        t0 = 0x960000;
        lw(a3, gp, -20724);  // 0x7CDBFC (the light-tie free list's preallocated blocks)
        v0 = 0x40000;
        a0 = 24;
        a2 = 4;
        t0 = addiu(t0, -8352);  // &0x95DF60 (the light-tie free list's static record)
        t1 = v0 | 0x507;
        jal(ctx, 0x49AB6Cu, gen::fn_sub_4C3B60_004c3b60);
        lw(v1, gp, -17528);  // 0x7CE878 (the world-ties module offset)
        a2 = 0x960000;
        a2 = addiu(a2, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v1 = addu(a2, v1);
        sw(v0, v1, 4);
        lw(v0, v1, 4);
        if (v0 == 0) {
            // 0x0049abc0: no light-tie list: destroy the atomic-tie list, 0
            charge(ctx, 8);
            link(ctx, 0x49ABC0u);  // $ra first: the delay slot below depends on it
            lw(a0, v1, 0);
            call(ctx, gen::fn_sub_4C3C30_004c3c30);
            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = 0;
            v1 = addu(v1, a0);
            sw(zero, v1, 0);
        } else {
            // 0x0049ab94: frame stamp 1, count the open
            charge(ctx, 11);
            a1 = 1;
            v1 = 0x960000;
            sh(a1, v1, 120);  // 0x960078 (the render frame stamp, engine +8)
            v0 = s0;
            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
            lw(v1, gp, -17524);  // 0x7CE87C (the world-ties module's open count)
            a0 = addu(a2, a0);
            v1 = addiu(v1, 1);
            sw(zero, a0, 8);
            sw(v1, gp, -17524);  // 0x7CE87C (the world-ties module's open count)
        }
    } else {
        // 0x0049ab48
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0049abe0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49ABF0 [worldTiesModuleClose] -- the world-ties module's close: destroys both tie free lists; count down
// 0x0049ABF0 sub_49ABF0 -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49ABF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049abf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17528);  // 0x7CE878 (the world-ties module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 4);
    if (a0 != 0) {
        // 0x0049ac1c
        charge(ctx, 7);
        jal(ctx, 0x49AC1Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17528);  // 0x7CE878 (the world-ties module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 4);
    }
    // 0x0049ac38
    charge(ctx, 7);
    lw(v1, gp, -17528);  // 0x7CE878 (the world-ties module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x0049ac54
        charge(ctx, 7);
        jal(ctx, 0x49AC54u, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17528);  // 0x7CE878 (the world-ties module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x0049ac70 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17524);  // 0x7CE87C (the world-ties module's open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17524);  // 0x7CE87C (the world-ties module's open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49AC90 [cameraWorldBeginUpdate] -- the camera's begin-update in a world: its world current, a new frame stamp, its own begin-update
// (a tail call through the saved callback).
// 0x0049AC90 sub_49AC90 -- 52 bytes; leaf frame (no stack)
void sub_49AC90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0049ac90
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(a2, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    v0 = 0x960000;
    lhu(a1, v0, 120);  // 0x960078 (the render frame stamp, engine +8)
    v1 = 0x960000;
    a3 = addu(a0, a2);
    lw(a2, a3, camworld::kWorld);
    v0 = 0x960000;
    a1 = addiu(a1, 1);
    sw(a2, v1, 116);  // 0x960074 (the current world, engine +4)
    sh(a1, v0, 120);  // 0x960078 (the render frame stamp, engine +8)
    lw(v0, a3, camworld::kSavedBegin);
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_49ACD0 [cameraWorldEndUpdate] -- the camera's end in a world: no current world, then its own end-update (tail call)
// 0x0049ACD0 sub_49ACD0 -- 28 bytes; leaf frame (no stack)
void sub_49ACD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0049acd0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    v0 = 0x960000;
    sw(zero, v0, 116);  // 0x960074 (the current world, engine +4)
    v0 = addu(a0, v1);
    lw(v0, v0, camworld::kSavedEnd);
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_49ACF0 [cameraWorldSync] -- the camera's sync in a world: its own sync, then its visible-sector list (sub_49B850)
// and the device standard function at 0x960110 called with (0, 0, world +12 == 1). Returns the camera or 0.
// 0x0049ACF0 sub_49ACF0 -- 144 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49ACF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049acf0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    s0 = a0;
    s1 = addu(s0, v0);
    lw(v0, s1, camworld::kSavedSync);
    jalr(ctx, 0x49AD14u, v0.u());
    if (v0 == 0) {
        // 0x0049ad64
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0049ad24
        charge(ctx, 3);
        lw(s2, s1, camworld::kWorld);
        if (s2 != 0) {
            // 0x0049ad30: a world: build the visible-sector list
            charge(ctx, 11);
            v0 = 0x960000;
            a0 = s2;
            lw(s1, v0, 272);  // 0x960110 (a device standard function)
            a1 = s0;
            jal(ctx, 0x49AD3Cu, gen::fn_sub_49B850_0049b850);
            lw(v0, s2, 12);
            a0 = 0;
            a1 = 0;
            v0 = v0 ^ 0x1;
            a2 = sltiu(v0, 1);
            jalr(ctx, 0x49AD54u, s1.u());
        }
        // 0x0049ad5c
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x0049ad68 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_49AD80 [cameraWorldExtConstructor] -- the camera's world extension constructor: no list, no world; saves the camera's
// begin / end / sync callbacks and installs the world wrappers sub_49AC90 / sub_49ACD0 / sub_49ACF0.
// 0x0049AD80 sub_49AD80 -- 92 bytes; leaf frame (no stack)
void sub_49AD80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x0049ad80
    enter(ctx, 23);  // entry check point + this block's cycles
    lw(a3, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    a2 = 0x4A0000;
    a1 = 0x4A0000;
    v1 = 0x4A0000;
    a2 = addiu(a2, -21264);  // &sub_49ACF0
    a1 = addiu(a1, -21360);  // &sub_49AC90
    v1 = addiu(v1, -21296);  // &sub_49ACD0
    v0 = a0;
    t0 = addu(a0, a3);
    sw(zero, t0, camworld::kSectors);
    sw(zero, t0, camworld::kCapacity);
    sw(zero, t0, camworld::kCount);
    lw(a3, a0, camera::kBeginUpdate);
    sw(a3, t0, camworld::kSavedBegin);
    lw(a3, a0, camera::kEndUpdate);
    sw(a3, t0, camworld::kSavedEnd);
    lw(a3, a0, camera::kSync);
    sw(a3, t0, camworld::kSavedSync);
    sw(a2, a0, camera::kSync);
    sw(a1, a0, camera::kBeginUpdate);
    sw(v1, a0, camera::kEndUpdate);
    sw(zero, t0, camworld::kWorld);
}


// sub_49ADE0 [cameraWorldExtCopy] -- the camera's world extension copy: an empty list; the copy joins the source's world
// 0x0049ADE0 sub_49ADE0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49ADE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049ade0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    s0 = a0;
    v0 = addu(a1, v1);
    lw(a0, v0, 12);
    v1 = addu(s0, v1);
    sw(zero, v1, 0);
    sw(zero, v1, 4);
    sw(zero, v1, 8);
    if (a0 != 0) {
        // 0x0049ae10
        charge(ctx, 2);
        a1 = s0;
        jal(ctx, 0x49AE10u, gen::fn_sub_49C160_0049c160);
    }
    // 0x0049ae18 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49AE30 [cameraWorldExtDestructor] -- the camera's world extension destructor: frees the sector list, restores the camera's callbacks
// 0x0049AE30 sub_49AE30 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49AE30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049ae30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    s0 = a0;
    s1 = addu(s0, v0);
    lw(a0, s1, camworld::kSectors);
    if (a0 != 0) {
        // 0x0049ae58
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x49AE60u, v0.u());
    }
    // 0x0049ae68 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    sw(zero, s1, camworld::kSectors);
    v0 = s0;
    sw(zero, s1, camworld::kCapacity);
    sw(zero, s1, camworld::kCount);
    lw(v1, s1, camworld::kSavedBegin);
    sw(v1, s0, camera::kBeginUpdate);
    lw(v1, s1, camworld::kSavedEnd);
    sw(v1, s0, camera::kEndUpdate);
    lw(v1, s1, camworld::kSavedSync);
    sw(v1, s0, camera::kSync);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49AEB0 [lightTieFree] -- unlinks a light-sector tie from both lists and returns it to the light-tie free list; 1
// 0x0049AEB0 sub_49AEB0 -- 108 bytes; frame 0x10: ra sp+0x0
void sub_49AEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049aeb0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x960000;
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(a3, a0, tie::kObjectNext);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(a2, a0, tie::kObjectPrev);
    v0 = 0x960000;
    sw(a3, a2, 0);
    lw(a3, a0, tie::kObjectPrev);
    lw(a2, a0, tie::kObjectNext);
    sw(a3, a2, 4);
    lw(a3, a0, tie::kSectorNext);
    lw(a2, a0, tie::kSectorPrev);
    sw(a3, a2, 0);
    lw(a2, a0, tie::kSectorPrev);
    lw(a0, a0, tie::kSectorNext);
    sw(a2, a0, tie::kSectorPrev);
    lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x49AF04u);  // $ra = the return address
    lw(a0, v1, 4);
    call_ptr(ctx, jt);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// sub_49AF20 [atomicTieFree] -- unlinks an atomic-sector tie (when it is in use) and returns it to the atomic-tie free list; 1
// 0x0049AF20 sub_49AF20 -- 128 bytes; frame 0x10: ra sp+0x0
void sub_49AF20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049af20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, tie::kObject);
    a1 = a0;
    if (v0 != 0) {
        // 0x0049af34
        charge(ctx, 3);
        lw(v0, a1, tie::kSector);
        if (v0 != 0) {
            // 0x0049af40
            charge(ctx, 20);
            lw(a2, a1, tie::kObjectNext);
            v1 = 0x960000;
            lw(a0, a1, tie::kObjectPrev);
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = 0x960000;
            sw(a2, a0, tie::kSectorNext);
            lw(a2, a1, tie::kObjectPrev);
            lw(a0, a1, tie::kObjectNext);
            sw(a2, a0, tie::kSectorPrev);
            lw(a2, a1, tie::kSectorNext);
            lw(a0, a1, tie::kSectorPrev);
            sw(a2, a0, tie::kSectorNext);
            lw(a2, a1, tie::kSectorPrev);
            lw(a0, a1, tie::kSectorNext);
            sw(a2, a0, tie::kSectorPrev);
            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            v1 = addu(v1, a0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x49AF88u);  // $ra = the return address
            lw(a0, v1, 0);
            call_ptr(ctx, jt);
        }
    }
    // 0x0049af90 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// sub_49AFA0 [atomicTieToSectors] -- ties an atomic to every sector its world bounding sphere's box reaches
// ($a0 = the world, $a1 = the atomic) A BSP walk with an explicit stack: a sector gets a tie (atomic-tie free list)
// linked into the sector's atomic list and the atomic's sector list.
// 0x0049AFA0 sub_49AFA0 -- 468 bytes; frame 0x170: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49AFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049afa0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = a0;
    a0 = s3;
    jal(ctx, 0x49AFC4u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    lwc1(f0, v0, 8);
    lw(s2, s0, 28);
    lwc1(f4, v0, 0);
    a2 = addiu(sp, 0x164);
    lwc1(f1, v0, 12);
    a0 = addiu(sp, 0x168);
    lwc1(f2, v0, 4);
    a1 = addiu(sp, 0x154);
    v1 = addiu(sp, 0x158);
    swc1(f0, sp, 0x168);
    s0 = 0x960000;
    s0 = addiu(s0, 392);  // &0x960188 (free-list alloc slot)
    sub_s(f0, f4, f1);
    swc1(f2, sp, 0x164);
    swc1(f0, sp, 0x160);
    add_s(f0, f4, f1);
    lwc1(f3, a2, 0);
    swc1(f0, sp, 0x150);
    lwc1(f2, a0, 0);
    sub_s(f0, f3, f1);
    swc1(f0, a2, 0);
    add_s(f0, f3, f1);
    swc1(f0, a1, 0);
    sub_s(f0, f2, f1);
    swc1(f0, a0, 0);
    add_s(f0, f2, f1);
    swc1(f0, v1, 0);
    for (;;) {
        // 0x0049b038
        charge(ctx, 3);
        lw(v1, s2, bsp::kType);
        if (i64(v1) < 0) {
            // 0x0049b0c0: a sector: a tie into both lists
            charge(ctx, 31);
            lw(a2, gp, -17528);  // 0x7CE878 (the world-ties module offset)
            a0 = 0x960000;
            v1 = 0x30000;
            a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            a1 = v1 | 0x507;
            lw(v0, s0, 0);
            v1 = addu(a0, a2);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x49B0DCu);  // $ra = the return address
            lw(a0, v1, 0);
            call_ptr(ctx, jt);
            sw(s2, v0, 20);
            v1 = sll(s1, 2);
            sw(s3, v0, 8);
            a3 = addiu(s2, 56);
            lw(a2, s2, sector::kAtomicTies);
            v1 = addu(v1, sp);
            a1 = addiu(s3, 100);
            a0 = addiu(v0, 12);
            s1 = addiu(s1, -1);
            sw(a2, v0, 0);
            sw(a3, v0, 4);
            lw(a2, s2, sector::kAtomicTies);
            sw(v0, a2, 4);
            sw(v0, s2, sector::kAtomicTies);
            lw(s2, v1, 80);
            lw(v1, s3, atomic::kSectorTies);
            sw(v1, v0, 12);
            sw(a1, v0, 16);
            lw(v1, s3, atomic::kSectorTies);
            sw(a0, v1, 4);
            sw(a0, s3, atomic::kSectorTies);
            backedge(ctx);
        } else {
            // 0x0049b044: a plane: which sides the box reaches
            charge(ctx, 6);
            v1 = addu(v1, sp);
            lwc1(f1, v1, 352);
            lwc1(f0, s2, bsp::kLeftValue);
            c_lt_s(f1, f0);
            a0 = s2;
            if (!cond(ctx)) {
                // 0x0049b090
                charge(ctx, 7);
                lw(v1, s2, bsp::kType);
                lwc1(f0, s2, bsp::kRightValue);
                v1 = addu(v1, sp);
                lwc1(f1, v1, 336);
                c_lt_s(f0, f1);
                if (!cond(ctx)) {
                    // 0x0049b140: pop the next node
                    charge(ctx, 5);
                    v1 = sll(s1, 2);
                    v1 = addu(v1, sp);
                    lw(s2, v1, 80);
                    s1 = addiu(s1, -1);
                    backedge(ctx);
                } else {
                    // 0x0049b0ac
                    charge(ctx, 1);
                    lw(s2, s2, bsp::kRight);
                }
            } else {
                // 0x0049b05c
                charge(ctx, 7);
                lw(v1, a0, 0);
                lwc1(f0, a0, 20);
                v1 = addu(v1, sp);
                lwc1(f1, v1, 336);
                c_lt_s(f0, f1);
                lw(s2, s2, bsp::kLeft);
                if (cond(ctx)) {
                    // 0x0049b078
                    charge(ctx, 6);
                    lw(a0, a0, 12);
                    s1 = addiu(s1, 1);
                    v1 = sll(s1, 2);
                    v1 = addu(v1, sp);
                    sw(a0, v1, 80);
                }
            }
        }
        // 0x0049b0b0
        charge(ctx, 2);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0049b0b8
    charge(ctx, 2);
    // 0x0049b158
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}


// sub_49B180 [atomicWorldSync] -- the atomic's sync in a world: its own sync, then its old ties freed and new ones made
// 0x0049B180 sub_49B180 -- 264 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49B180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049b180
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17540);  // 0x7CE86C (the atomic world extension offset)
    s0 = addu(s4, v0);
    lw(v0, s0, objworld::kSavedSync);
    jalr(ctx, 0x49B1ACu, v0.u());
    if (v0 == 0) {
        // 0x0049b264
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0049b1bc
        charge(ctx, 3);
        lw(s3, s0, objworld::kWorld);
        if (s3 != 0) {
            // 0x0049b1c8
            charge(ctx, 4);
            lw(s2, s4, atomic::kSectorTies);
            s1 = addiu(s4, 100);
            if (s2 != s1) {
                // 0x0049b1d8: free every tie of the atomic
                charge(ctx, 2);
                s0 = 0x960000;
                s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
                for (;;) {
                    // 0x0049b1e0
                    charge(ctx, 4);
                    a1 = addiu(s2, -12);
                    lw(v0, a1, tie::kObject);
                    lw(s2, s2, 0);
                    if (v0 != 0) {
                        // 0x0049b1f0
                        charge(ctx, 3);
                        lw(v0, a1, tie::kSector);
                        if (v0 != 0) {
                            // 0x0049b1fc
                            charge(ctx, 19);
                            lw(a0, a1, tie::kObjectNext);
                            v1 = 0x960000;
                            lw(v0, a1, tie::kObjectPrev);
                            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                            sw(a0, v0, 0);
                            lw(a0, a1, tie::kObjectPrev);
                            lw(v0, a1, tie::kObjectNext);
                            sw(a0, v0, 4);
                            lw(a0, a1, tie::kSectorNext);
                            lw(v0, a1, tie::kSectorPrev);
                            sw(a0, v0, 0);
                            lw(a0, a1, tie::kSectorPrev);
                            lw(v0, a1, tie::kSectorNext);
                            sw(a0, v0, 4);
                            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
                            lw(v0, s0, objworld::kWorld);
                            v1 = addu(v1, a0);
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x49B240u);  // $ra = the return address
                            lw(a0, v1, 0);
                            call_ptr(ctx, jt);
                        }
                    }
                    // 0x0049b248
                    charge(ctx, 2);
                    if (s2 == s1) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0049b250: tie it again (sub_49AFA0)
            charge(ctx, 3);
            a0 = s3;
            a1 = s4;
            jal(ctx, 0x49B254u, gen::fn_sub_49AFA0_0049afa0);
        }
        // 0x0049b25c
        charge(ctx, 2);
        v0 = s4;
    }
    // 0x0049b268 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_49B290 [atomicWorldExtConstructor] -- the atomic's world extension constructor: no world, an old render stamp, the world sync installed
// (render stamp = the engine's - 1; the atomic's own sync saved, sub_49B180 installed).
// 0x0049B290 sub_49B290 -- 56 bytes; leaf frame (no stack)
void sub_49B290(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x0049b290
    enter(ctx, 14);  // entry check point + this block's cycles
    lw(a2, gp, -17540);  // 0x7CE86C (the atomic world extension offset)
    a1 = 0x4A0000;
    v1 = 0x960000;
    a1 = addiu(a1, -20096);  // &sub_49B180
    v0 = a0;
    a2 = addu(a0, a2);
    sw(zero, a2, objworld::kWorld);
    lhu(v1, v1, 120);  // 0x960078 (the render frame stamp, engine +8)
    v1 = addiu(v1, -1);
    sh(v1, a0, atomic::kRenderFrame);
    lw(v1, a0, atomic::kSync);
    sw(v1, a2, objworld::kSavedSync);
    sw(a1, a0, atomic::kSync);
}


// sub_49B2D0 [atomicWorldExtCopy] -- the atomic's world extension copy: returns the atomic
// 0x0049B2D0 sub_49B2D0 -- 8 bytes; leaf frame (no stack)
void sub_49B2D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0049b2d0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}


// sub_49B2E0 [atomicWorldExtDestructor] -- the atomic's world extension destructor: its ties freed, its own sync restored
// 0x0049B2E0 sub_49B2E0 -- 220 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49B2E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049b2e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s4, 100);
    lw(v0, gp, -17540);  // 0x7CE86C (the atomic world extension offset)
    lw(s3, a0, atomic::kSectorTies);
    s2 = addu(s4, v0);
    if (s3 != s1) {
        // 0x0049b314
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x0049b31c
            charge(ctx, 4);
            a1 = addiu(s3, -12);
            lw(v0, a1, tie::kObject);
            lw(s3, s3, 0);
            if (v0 != 0) {
                // 0x0049b32c
                charge(ctx, 3);
                lw(v0, a1, tie::kSector);
                if (v0 != 0) {
                    // 0x0049b338
                    charge(ctx, 20);
                    lw(a0, a1, tie::kObjectNext);
                    v1 = 0x960000;
                    lw(v0, a1, tie::kObjectPrev);
                    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    sw(a0, v0, 0);
                    lw(a0, a1, tie::kObjectPrev);
                    lw(v0, a1, tie::kObjectNext);
                    sw(a0, v0, 4);
                    lw(a0, a1, tie::kSectorNext);
                    lw(v0, a1, tie::kSectorPrev);
                    sw(a0, v0, 0);
                    lw(a0, a1, tie::kSectorPrev);
                    lw(v0, a1, tie::kSectorNext);
                    sw(a0, v0, 4);
                    lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
                    lw(v0, s0, 0);
                    v1 = addu(v1, a0);
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x49B37Cu);  // $ra = the return address
                    lw(a0, v1, 0);
                    call_ptr(ctx, jt);
                }
            }
            // 0x0049b388
            charge(ctx, 2);
            if (s3 == s1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0049b390 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v1, s2, objworld::kSavedSync);
    v0 = s4;
    sw(v1, s4, atomic::kSync);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_49B3C0 [clumpWorldExtConstructor] -- the clump's world extension constructor: no world; +4 from the world module's +8
// 0x0049B3C0 sub_49B3C0 -- 44 bytes; leaf frame (no stack)
void sub_49B3C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0049b3c0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a1, gp, -17536);  // 0x7CE870 (the clump world extension offset)
    v1 = 0x960000;
    v0 = a0;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = addu(a0, a1);
    sw(zero, a1, objworld::kWorld);
    lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
    v1 = addu(v1, a0);
    lw(v1, v1, 8);
    sw(v1, a1, objworld::kSavedSync);
}


// sub_49B430 [clumpWorldExtDestructor] -- the clump's world extension destructor: nothing to do, returns the clump
// 0x0049B430 sub_49B430 -- 8 bytes; leaf frame (no stack)
void sub_49B430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0049b430
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}


// sub_49B440 [lightWorldSync] -- the light's sync in a world: its own sync, then a local light is tied to the sectors it reaches
// A local light (type bit 7) with a world and a frame has its ties freed and is tied to every sector its
// sphere's box (frame position +- radius) reaches. Error 0x80000016 when the light's own sync fails.
// 0x0049B440 sub_49B440 -- 740 bytes; frame 0x1C0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_49B440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049b440
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a0;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(v0, gp, -17532);  // 0x7CE874 (the light world extension offset)
    s0 = addu(s4, v0);
    lw(v0, s0, objworld::kSavedSync);
    jalr(ctx, 0x49B478u, v0.u());
    if (v0 == 0) {
        // 0x0049b6d0: its own sync failed: error 0x80000016
        charge(ctx, 10);
        v0 = 2;
        sw(v0, sp, 0x198);
        v0 = lui(0x8000);
        a0 = v0 | 0x16;
        jal(ctx, 0x49B6DCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x19C);
        a0 = addiu(sp, 0x198);
        jal(ctx, 0x49B6E8u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    L_0049b52c:
        charge(ctx, 2);
        v0 = s4;
    } else {
        // 0x0049b488: a local light (type >= 0x80) with a world and a frame
        charge(ctx, 4);
        lbu(v0, s4, light::kType);
        v0 = slti(v0, 128);
        if (v0 == 0) {
            // 0x0049b498
            charge(ctx, 3);
            lw(s6, s0, objworld::kWorld);
            lw(s5, s4, light::kFrame);
            if (s6 != 0) {
                // 0x0049b4a4
                charge(ctx, 2);
                if (s5 != 0) {
                    // 0x0049b4ac
                    charge(ctx, 5);
                    lw(s2, s4, light::kSectorTies);
                    lwc1(f20, s4, light::kRadius);
                    s1 = addiu(s4, 44);
                    s3 = 0;
                    if (s2 == s1) {
                        // 0x0049b53c
                        charge(ctx, 1);
                        a0 = s5;
                    } else {
                        // 0x0049b4c0: free its old ties
                        charge(ctx, 2);
                        s0 = 0x960000;
                        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
                        for (;;) {
                            // 0x0049b4c8
                            charge(ctx, 23);
                            a1 = addiu(s2, -12);
                            v1 = 0x960000;
                            lw(s2, s2, 0);
                            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                            lw(a0, a1, tie::kObjectNext);
                            lw(v0, a1, tie::kObjectPrev);
                            sw(a0, v0, 0);
                            lw(a0, a1, tie::kObjectPrev);
                            lw(v0, a1, tie::kObjectNext);
                            sw(a0, v0, 4);
                            lw(a0, a1, tie::kSectorNext);
                            lw(v0, a1, tie::kSectorPrev);
                            sw(a0, v0, 0);
                            lw(a0, a1, tie::kSectorPrev);
                            lw(v0, a1, tie::kSectorNext);
                            sw(a0, v0, 4);
                            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
                            lw(v0, s0, objworld::kWorld);
                            v1 = addu(v1, a0);
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x49B514u);  // $ra = the return address
                            lw(a0, v1, 4);
                            call_ptr(ctx, jt);
                            if (s2 == s1) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0049b524
                        charge(ctx, 2);
                        a0 = s5;
                    }
                    // 0x0049b540: the box of its sphere around the frame's position
                    charge(ctx, 28);
                    jal(ctx, 0x49B540u, gen::fn_sub_4CB2F0_004cb2f0);
                    lwc1(f3, v0, 48);
                    s0 = 0x960000;
                    lwc1(f2, v0, 52);
                    a1 = addiu(sp, 0x1B4);
                    lwc1(f1, v0, 56);
                    a0 = addiu(sp, 0x1A4);
                    v1 = addiu(sp, 0x1B8);
                    lw(s1, s6, 28);
                    s0 = addiu(s0, 392);  // &0x960188 (free-list alloc slot)
                    add_s(f0, f3, f20);
                    v0 = addiu(sp, 0x1A8);
                    swc1(f2, sp, 0x1B4);
                    swc1(f0, sp, 0x1A0);
                    sub_s(f0, f3, f20);
                    lwc1(f2, a1, tie::kSectorNext);
                    swc1(f0, sp, 0x1B0);
                    swc1(f1, sp, 0x1B8);
                    lwc1(f1, v1, 0);
                    add_s(f0, f2, f20);
                    swc1(f0, a0, 0);
                    sub_s(f0, f2, f20);
                    swc1(f0, a1, tie::kSectorNext);
                    add_s(f0, f1, f20);
                    swc1(f0, v0, 0);
                    sub_s(f0, f1, f20);
                    swc1(f0, v1, 0);
                    for (;;) {
                        // 0x0049b5b0
                        charge(ctx, 3);
                        lw(v0, s1, bsp::kType);
                        if (i64(v0) < 0) {
                            // 0x0049b638: a sector: a tie into both lists
                            charge(ctx, 31);
                            lw(a2, gp, -17528);  // 0x7CE878 (the world-ties module offset)
                            a0 = 0x960000;
                            v1 = 0x30000;
                            a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                            a1 = v1 | 0x507;
                            lw(v0, s0, objworld::kWorld);
                            v1 = addu(a0, a2);
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x49B654u);  // $ra = the return address
                            lw(a0, v1, 4);
                            call_ptr(ctx, jt);
                            sw(s1, v0, 20);
                            v1 = sll(s3, 2);
                            sw(s4, v0, 8);
                            a3 = addiu(s1, 64);
                            lw(a2, s1, sector::kLightTies);
                            v1 = addu(v1, sp);
                            a1 = addiu(s4, 44);
                            a0 = addiu(v0, 12);
                            s3 = addiu(s3, -1);
                            sw(a2, v0, 0);
                            sw(a3, v0, 4);
                            lw(a2, s1, sector::kLightTies);
                            sw(v0, a2, 4);
                            sw(v0, s1, sector::kLightTies);
                            lw(s1, v1, 144);
                            lw(v1, s4, light::kSectorTies);
                            sw(v1, v0, 12);
                            sw(a1, v0, 16);
                            lw(v0, s4, light::kSectorTies);
                            sw(a0, v0, 4);
                            sw(a0, s4, light::kSectorTies);
                            backedge(ctx);
                        } else {
                            // 0x0049b5bc: a plane: which sides the box reaches
                            charge(ctx, 6);
                            v0 = addu(v0, sp);
                            lwc1(f1, v0, 432);
                            lwc1(f0, s1, bsp::kLeftValue);
                            c_lt_s(f1, f0);
                            v1 = s1;
                            if (!cond(ctx)) {
                                // 0x0049b608
                                charge(ctx, 7);
                                lw(v0, s1, bsp::kType);
                                lwc1(f0, s1, bsp::kRightValue);
                                v0 = addu(v0, sp);
                                lwc1(f1, v0, 416);
                                c_lt_s(f0, f1);
                                if (!cond(ctx)) {
                                    // 0x0049b6b8
                                    charge(ctx, 5);
                                    v0 = sll(s3, 2);
                                    v0 = addu(v0, sp);
                                    lw(s1, v0, 144);
                                    s3 = addiu(s3, -1);
                                    backedge(ctx);
                                } else {
                                    // 0x0049b624
                                    charge(ctx, 1);
                                    lw(s1, s1, bsp::kRight);
                                }
                            } else {
                                // 0x0049b5d4
                                charge(ctx, 7);
                                lw(v0, v1, 0);
                                lwc1(f0, v1, 20);
                                v0 = addu(v0, sp);
                                lwc1(f1, v0, 416);
                                c_lt_s(f0, f1);
                                lw(s1, s1, bsp::kLeft);
                                if (cond(ctx)) {
                                    // 0x0049b5f0
                                    charge(ctx, 6);
                                    lw(v1, v1, 12);
                                    s3 = addiu(s3, 1);
                                    v0 = sll(s3, 2);
                                    v0 = addu(v0, sp);
                                    sw(v1, v0, 144);
                                }
                            }
                        }
                        // 0x0049b628
                        charge(ctx, 2);
                        if (i64(s3) < 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0049b630
                    charge(ctx, 2);
                    backedge(ctx);
                }
            }
            goto L_0049b52c;
        }
        // 0x0049b534
        charge(ctx, 2);
        v0 = s4;
    }
    // 0x0049b6f8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x1C0);
}


// sub_49B730 [lightWorldExtConstructor] -- the light's world extension constructor: no world, saves its sync, installs sub_49B440
// 0x0049B730 sub_49B730 -- 40 bytes; leaf frame (no stack)
void sub_49B730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x0049b730
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a1, gp, -17532);  // 0x7CE874 (the light world extension offset)
    v1 = 0x4A0000;
    v1 = addiu(v1, -19392);  // &sub_49B440
    v0 = a0;
    a2 = addu(a0, a1);
    sw(zero, a2, objworld::kWorld);
    lw(a1, a0, light::kSync);
    sw(a1, a2, objworld::kSavedSync);
    sw(v1, a0, light::kSync);
}


// sub_49B760 [lightWorldExtCopy] -- the light's world extension copy: the copy joins the source's world (sub_49C3D0)
// 0x0049B760 sub_49B760 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49B760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049b760
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17532);  // 0x7CE874 (the light world extension offset)
    s0 = a0;
    v0 = addu(a1, v0);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x0049b784
        charge(ctx, 2);
        a1 = s0;
        jal(ctx, 0x49B784u, gen::fn_sub_49C3D0_0049c3d0);
    }
    // 0x0049b78c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49B7A0 [lightWorldExtDestructor] -- the light's world extension destructor: frees its sector ties
// 0x0049B7A0 sub_49B7A0 -- 176 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49B7A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049b7a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s3, 44);
    lw(s2, a0, light::kSectorTies);
    if (s2 != s1) {
        // 0x0049b7cc
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x0049b7d4
            charge(ctx, 23);
            a1 = addiu(s2, -12);
            v1 = 0x960000;
            lw(s2, s2, 0);
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            lw(a0, a1, tie::kObjectNext);
            lw(v0, a1, tie::kObjectPrev);
            sw(a0, v0, 0);
            lw(a0, a1, tie::kObjectPrev);
            lw(v0, a1, tie::kObjectNext);
            sw(a0, v0, 4);
            lw(a0, a1, tie::kSectorNext);
            lw(v0, a1, tie::kSectorPrev);
            sw(a0, v0, 0);
            lw(a0, a1, tie::kSectorPrev);
            lw(v0, a1, tie::kSectorNext);
            sw(a0, v0, 4);
            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
            lw(v0, s0, 0);
            v1 = addu(v1, a0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x49B820u);  // $ra = the return address
            lw(a0, v1, 4);
            call_ptr(ctx, jt);
            if (s2 == s1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0049b830 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_49B850 [cameraBuildSectorList] -- builds a camera's visible-sector list: the BSP walked against the frustum
// ($a0 = the world, $a1 = the camera) Each plane node: the frustum box decides the side(s); when both are reached
// the side holding the camera position comes first (parallel projection: the other order); a sector is kept
// unless one of the six frustum planes has its box entirely outside; the array grows by 50 (RwRealloc /
// RwMalloc, hint 0x1030507). The count goes to the camera's extension; returns the world.
// 0x0049B850 sub_49B850 -- 868 bytes; frame 0x200: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49B850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x0049b850
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x200);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = 0;
    sq(s2, sp, 0x20);
    s3 = 0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    lw(a0, a1, 4);
    s1 = addu(s2, v0);
    jal(ctx, 0x49B894u, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 48);
    lw(v1, s1, camworld::kWorld);
    lwc1(f5, v0, 52);
    lw(a0, s0, 12);
    lwc1(f4, v0, 56);
    fp = addiu(s2, 0x94);
    lwc1(f1, s2, camera::kFrustumBoxInf);
    s6 = 0;
    lwc1(f0, s2, 284);
    lwc1(f3, s2, 288);
    swc1(f2, sp, 0x1E8);
    lw(s5, v1, 28);
    lwc1(f2, s2, camera::kFrustumBoxSup);
    v0 = 0x960000;
    swc1(f1, sp, 0x1D8);
    v0 = addiu(v0, 384);  // &0x960180 (RwRealloc slot)
    swc1(f0, sp, 0x1DC);
    sq(v0, sp, 0xB0);
    lwc1(f1, s2, 272);
    v0 = 0x960000;
    lwc1(f0, s2, 276);
    v0 = addiu(v0, 376);  // &0x960178 (RwMalloc slot)
    sq(v0, sp, 0xA0);
    swc1(f5, sp, 0x1EC);
    v0 = a0 ^ 0x2;
    swc1(f4, sp, 0x1F0);
    s7 = sltiu(v0, 1);
    swc1(f3, sp, 0x1E0);
    swc1(f2, sp, 0x1C8);
    swc1(f1, sp, 0x1CC);
    swc1(f0, sp, 0x1D0);
    for (;;) {
        // 0x0049b918: a plane node: compare the frustum box with the plane
        charge(ctx, 3);
        lw(v0, s5, bsp::kType);
        if (i64(v0) >= 0) {
            // 0x0049b924
            charge(ctx, 12);
            v1 = addu(v0, sp);
            a0 = s5;
            lwc1(f3, v1, 472);
            lwc1(f2, s5, bsp::kLeftValue);
            lwc1(f1, s5, bsp::kRightValue);
            lwc1(f0, v1, 456);
            sub_s(f2, f3, f2);
            swc1(f2, sp, 0x1F8);
            lw(v0, sp, 0x1F8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x1F4);
            if (i64(v0) < 0) {
                // 0x0049bb00
                charge(ctx, 3);
                lw(v0, sp, 0x1F4);
                if (i64(v0) >= 0) {
                    backedge(ctx);
                    goto L_0049b954;
                }
                // 0x0049bb0c: both sides: the camera position's side first
                charge(ctx, 5);
                lwc1(f1, v1, 488);
                lwc1(f0, s5, bsp::kPlane);
                c_le_s(f1, f0);
                v0 = 1;
                if (cond(ctx)) {
                    // 0x0049bb20
                    charge(ctx, 1);
                    v0 = 0;
                }
                // 0x0049bb24
                charge(ctx, 2);
                if (s7 != 0) {
                    // 0x0049bb58
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x0049bb60
                        charge(ctx, 2);
                        backedge(ctx);
                        goto L_0049bb2c;
                    }
                    backedge(ctx);
                L_0049bb3c:
                    charge(ctx, 7);
                    lw(v1, a0, 12);
                    s4 = addiu(s4, 1);
                    lw(s5, a0, 8);
                    v0 = sll(s4, 2);
                    v0 = addu(v0, sp);
                    sw(v1, v0, 192);
                    backedge(ctx);
                    goto L_0049b96c;
                }
            L_0049bb2c:
                charge(ctx, 2);
                if (s7 == 0) {
                    // 0x0049bb34
                    charge(ctx, 2);
                    if (v0 != 0) {
                        goto L_0049bb68;
                    }
                    goto L_0049bb3c;
                }
            L_0049bb68:
                charge(ctx, 7);
                lw(v1, a0, 8);
                s4 = addiu(s4, 1);
                lw(s5, a0, 12);
                v0 = sll(s4, 2);
                v0 = addu(v0, sp);
                sw(v1, v0, 192);
                backedge(ctx);
                goto L_0049b96c;
            }
        L_0049b954:
            charge(ctx, 3);
            lw(v0, sp, 0x1F8);
            if (i64(v0) >= 0) {
                // 0x0049b968
                charge(ctx, 1);
                lw(s5, a0, 12);
            } else {
                // 0x0049b960
                charge(ctx, 2);
                lw(s5, a0, 8);
            }
            goto L_0049b96c;
        }
        // 0x0049b980: a sector: test its box against the six frustum planes (the plane's closest box corner)
        charge(ctx, 3);
        v0 = addiu(s5, 72);
        a0 = 0;
        v1 = fp;
        for (;;) {
            // 0x0049b98c
            charge(ctx, 31);
            lbu(t0, v1, 18);
            lwc1(f1, v1, 4);
            lbu(a3, v1, 16);
            lwc1(f3, v1, 0);
            lbu(a2, v1, 17);
            lwc1(f5, v1, 8);
            lwc1(f0, v1, 12);
            a1 = sll(t0, 1);
            t0 = addu(a1, t0);
            a1 = sll(a3, 1);
            a1 = addu(a1, a3);
            a1 = sll(a1, 2);
            a3 = sll(t0, 2);
            a1 = addu(v0, a1);
            a3 = addu(v0, a3);
            lwc1(f4, a1, 0);
            lwc1(f6, a3, 8);
            a1 = sll(a2, 1);
            a1 = addu(a1, a2);
            a1 = sll(a1, 2);
            a1 = addu(v0, a1);
            lwc1(f2, a1, 4);
            mula_s(f2, f1);
            madda_s(f4, f3);
            madd_s(f1, f6, f5);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x1FC);
            lw(a1, sp, 0x1FC);
            a2 = slt(0, a1);
            if (a2 == 0) {
                // 0x0049ba08
                charge(ctx, 4);
                a0 = addiu(a0, 1);
                a1 = slti(a0, 6);
                v1 = addiu(v1, 20);
                if (a1 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
        // 0x0049ba18: inside: append it (grow the array by 50 when full)
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x0049ba20
            charge(ctx, 4);
            lw(v1, s1, camworld::kCapacity);
            v0 = slt(s3, v1);
            if (v0 == 0) {
                // 0x0049ba30
                charge(ctx, 4);
                lw(a0, s1, camworld::kSectors);
                v0 = addiu(v1, 50);
                s2 = sll(v0, 2);
                if (a0 == 0) {
                    // 0x0049ba60
                    charge(ctx, 6);
                    v0 = 0x1030000;
                    a1 = v0 | 0x507;  // &0x1030507 (a memory hint)
                    lq(v0, sp, 0xA0);
                    lw(v0, v0, 0);
                    a0 = s2;
                    jalr(ctx, 0x49BA70u, v0.u());
                } else {
                    // 0x0049ba40
                    charge(ctx, 8);
                    v0 = 0x1030000;
                    a2 = v0 | 0x507;  // &0x1030507 (a memory hint)
                    lq(v0, sp, 0xB0);
                    lw(v0, v0, 0);
                    a1 = s2;
                    jalr(ctx, 0x49BA50u, v0.u());
                }
                // 0x0049ba78
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x0049bad0: out of memory: error 0x80000013
                    charge(ctx, 12);
                    v0 = 2;
                    a1 = s2;
                    sw(v0, sp, 0x1C0);
                    v0 = lui(0x8000);
                    a0 = v0 | 0x13;
                    jal(ctx, 0x49BAE0u, gen::fn_sub_4C1D10_004c1d10);
                    v1 = addiu(sp, 0x1C4);
                    a0 = addiu(sp, 0x1C0);
                    link(ctx, 0x49BAF0u);  // $ra first: the delay slot below depends on it
                    sw(v0, v1, 0);
                    call(ctx, gen::fn_sub_4C1C50_004c1c50);
                    v1 = 0;
                    backedge(ctx);
                } else {
                    // 0x0049ba80
                    charge(ctx, 5);
                    sw(v0, s1, camworld::kSectors);
                    v1 = 1;
                    lw(v0, s1, camworld::kCapacity);
                    v0 = addiu(v0, 50);
                    sw(v0, s1, camworld::kCapacity);
                }
                // 0x0049ba94
                charge(ctx, 2);
                if (v1 != 0) {
                    goto L_0049baa8;
                }
                goto L_0049ba9c_19;
            }
        L_0049baa8:
            charge(ctx, 5);
            lw(v0, s1, camworld::kSectors);
            s3 = addiu(s3, 1);
            v0 = addu(v0, s6);
            sw(s5, v0, 0);
            s6 = addiu(s6, 4);
        }
        // 0x0049babc: pop the next node
        charge(ctx, 5);
        v0 = sll(s4, 2);
        v0 = addu(v0, sp);
        lw(s5, v0, 192);
        s4 = addiu(s4, -1);
        backedge(ctx);
    L_0049b96c:
        charge(ctx, 2);
        if (i64(s4) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0049b974: store the count
    charge(ctx, 3);
    sw(s3, s1, camworld::kCount);
    v0 = s0;
    // 0x0049bb84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x200);
    return;
L_0049ba9c_19:
    charge(ctx, 3);
    sw(s3, s1, camworld::kCount);
    v0 = s0;
    // 0x0049bb84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x200);
}


// sub_49BBC0 [worldAddAtomicCB] -- a for-all callback: adds the atomic to the world (sub_49C1E0); returns the atomic
// 0x0049BBC0 sub_49BBC0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BBC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bbc0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1;
    a1 = s0;
    jal(ctx, 0x49BBD4u, gen::fn_sub_49C1E0_0049c1e0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49BBF0 [worldAddLightCB] -- a for-all callback: adds the light to the world (sub_49C3D0); returns the light
// 0x0049BBF0 sub_49BBF0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BBF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bbf0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1;
    a1 = s0;
    jal(ctx, 0x49BC04u, gen::fn_sub_49C3D0_0049c3d0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49BC20 [worldAddCameraCB] -- a for-all callback: adds the camera to the world (sub_49C160); returns the camera
// 0x0049BC20 sub_49BC20 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bc20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1;
    a1 = s0;
    jal(ctx, 0x49BC34u, gen::fn_sub_49C160_0049c160);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49C160 [worldAddCamera] -- ($a0 = the world, $a1 = the camera) the camera's world; its frame marked dirty; the world
// 0x0049C160 sub_49C160 -- 72 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49C160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c160
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    lw(a0, a1, camera::kFrame);
    s0 = addu(a1, v0);
    if (a0 != 0) {
        // 0x0049c184
        charge(ctx, 2);
        jal(ctx, 0x49C184u, gen::fn_sub_4CB270_004cb270);
    }
    // 0x0049c18c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(s1, s0, camworld::kWorld);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49C1B0 [worldRemoveCamera] -- the camera leaves its world (no world, no sectors); 0 when it had none
// 0x0049C1B0 sub_49C1B0 -- 48 bytes; leaf frame (no stack)
void sub_49C1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0049c1b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17544);  // 0x7CE868 (the camera world extension offset)
    v1 = addu(a1, v0);
    lw(v0, v1, camworld::kWorld);
    if (v0 != 0) {
        // 0x0049c1cc
        charge(ctx, 3);
        sw(zero, v1, camworld::kWorld);
        v0 = a0;
        sw(zero, v1, camworld::kCount);
    } else {
        // 0x0049c1c4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0049c1d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_49C1E0 [worldAddAtomic] -- ($a0 = the world, $a1 = the atomic) the atomic's world; its frame marked dirty (re-tie)
// 0x0049C1E0 sub_49C1E0 -- 72 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49C1E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c1e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17540);  // 0x7CE86C (the atomic world extension offset)
    lw(a0, a1, atomic::kFrame);
    s0 = addu(a1, v0);
    if (a0 != 0) {
        // 0x0049c204
        charge(ctx, 2);
        jal(ctx, 0x49C204u, gen::fn_sub_4CB270_004cb270);
    }
    // 0x0049c20c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(s1, s0, objworld::kWorld);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49C230 [atomicGetWorld] -- the world an atomic is in
// 0x0049C230 sub_49C230 -- 16 bytes; leaf frame (no stack)
void sub_49C230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0049c230
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, -17540);  // 0x7CE86C (the atomic world extension offset)
    v0 = addu(a0, v0);
    lw(v0, v0, objworld::kWorld);
}


// sub_49C3D0 [worldAddLight] -- ($a0 = the world, $a1 = the light) the light joins the world's global list (type < 0x80)
// or its local list (its frame marked dirty, to tie it to sectors). Returns the world.
// 0x0049C3D0 sub_49C3D0 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49C3D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c3d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17532);  // 0x7CE874 (the light world extension offset)
    s0 = a1;
    v0 = addu(s0, v0);
    sw(s1, v0, 0);
    lbu(v0, a1, light::kType);
    v0 = slti(v0, 128);
    if (v0 != 0) {
        // 0x0049c440: a global light: the world's global list
        charge(ctx, 9);
        lw(a0, s1, world::kGlobalLights);
        v0 = addiu(s1, 60);
        v1 = addiu(s0, 52);
        sw(a0, s0, light::kWorldLink);
        sw(v0, s0, light::kWorldLinkPrev);
        lw(v0, s1, world::kGlobalLights);
        sw(v1, v0, 4);
        sw(v1, s1, world::kGlobalLights);
        backedge(ctx);
    } else {
        // 0x0049c404: a local light: mark its frame dirty
        charge(ctx, 3);
        lw(a0, s0, light::kFrame);
        if (a0 != 0) {
            // 0x0049c410
            charge(ctx, 2);
            jal(ctx, 0x49C410u, gen::fn_sub_4CB270_004cb270);
        }
        // 0x0049c418: the world's local list
        charge(ctx, 8);
        lw(a0, s1, world::kLocalLights);
        v0 = addiu(s1, 52);
        v1 = addiu(s0, 52);
        sw(a0, s0, light::kWorldLink);
        sw(v0, s0, light::kWorldLinkPrev);
        lw(v0, s1, world::kLocalLights);
        sw(v1, v0, 4);
        sw(v1, s1, world::kLocalLights);
    }
    // 0x0049c438
    charge(ctx, 2);
    v0 = s1;
    // 0x0049c464
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49C480 [worldRemoveLight] -- the light leaves its world: its sector ties freed, out of the world's light list
// 0x0049C480 sub_49C480 -- 220 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49C480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049c480
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s3, 44);
    lw(v0, gp, -17532);  // 0x7CE874 (the light world extension offset)
    v0 = addu(s3, v0);
    sw(zero, v0, 0);
    lw(s2, a1, light::kSectorTies);
    s4 = a0;
    if (s2 != s1) {
        // 0x0049c4bc: free every tie of the light
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x0049c4c4
            charge(ctx, 23);
            a1 = addiu(s2, -12);
            v1 = 0x960000;
            lw(s2, s2, 0);
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            lw(a0, a1, tie::kObjectNext);
            lw(v0, a1, tie::kObjectPrev);
            sw(a0, v0, 0);
            lw(a0, a1, tie::kObjectPrev);
            lw(v0, a1, tie::kObjectNext);
            sw(a0, v0, 4);
            lw(a0, a1, tie::kSectorNext);
            lw(v0, a1, tie::kSectorPrev);
            sw(a0, v0, 0);
            lw(a0, a1, tie::kSectorPrev);
            lw(v0, a1, tie::kSectorNext);
            sw(a0, v0, 4);
            lw(a0, gp, -17528);  // 0x7CE878 (the world-ties module offset)
            lw(v0, s0, 0);
            v1 = addu(v1, a0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x49C510u);  // $ra = the return address
            lw(a0, v1, 4);
            call_ptr(ctx, jt);
            if (s2 == s1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0049c520 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lw(a0, s3, light::kWorldLink);
    lw(v1, s3, light::kWorldLinkPrev);
    v0 = s4;
    sw(a0, v1, 0);
    lw(a0, s3, light::kWorldLinkPrev);
    lw(v1, s3, light::kWorldLink);
    sw(a0, v1, 4);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_49C560 [setDefaultSectorPipeline] -- sets the world sectors' default pipeline (0: the original default); returns it
// 0x0049C560 sub_49C560 -- 88 bytes; leaf frame (no stack)
void sub_49C560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0049c560
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x0049c584
        charge(ctx, 7);
        lw(v1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        lw(a0, v0, pipemod::kDefSector);
        if (a0 == 0) {
            // 0x0049c5a8
            charge(ctx, 2);
            a0 = 0;
            backedge(ctx);
            goto L_0049c568;
        }
        // 0x0049c5a0
        charge(ctx, 2);
        lw(a1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
        backedge(ctx);
        goto L_0049c56c;
    }
L_0049c568:
    charge(ctx, 1);
    lw(a1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
L_0049c56c:
    charge(ctx, 6);
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = a0;
    v1 = addu(v1, a1);
    sw(a0, v1, pipemod::kSector);
    // 0x0049c5b0
    charge(ctx, 2);
}


// sub_49C5C0 [setDefaultAtomicPipeline] -- sets the atomics' default pipeline (0: the original default); returns it
// 0x0049C5C0 sub_49C5C0 -- 88 bytes; leaf frame (no stack)
void sub_49C5C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0049c5c0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x0049c5e4
        charge(ctx, 7);
        lw(v1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        lw(a0, v0, pipemod::kDefAtomic);
        if (a0 == 0) {
            // 0x0049c608
            charge(ctx, 2);
            a0 = 0;
            backedge(ctx);
            goto L_0049c5c8;
        }
        // 0x0049c600
        charge(ctx, 2);
        lw(a1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
        backedge(ctx);
        goto L_0049c5cc;
    }
L_0049c5c8:
    charge(ctx, 1);
    lw(a1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
L_0049c5cc:
    charge(ctx, 6);
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = a0;
    v1 = addu(v1, a1);
    sw(a0, v1, pipemod::kAtomic);
    // 0x0049c610
    charge(ctx, 2);
}


// sub_49C620 [setDefaultMaterialPipeline] -- sets the materials' default pipeline (0: the original default); returns it
// 0x0049C620 sub_49C620 -- 88 bytes; leaf frame (no stack)
void sub_49C620(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0049c620
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x0049c644
        charge(ctx, 7);
        lw(v1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        lw(a0, v0, pipemod::kDefMaterial);
        if (a0 == 0) {
            // 0x0049c668
            charge(ctx, 2);
            a0 = 0;
            backedge(ctx);
            goto L_0049c628;
        }
        // 0x0049c660
        charge(ctx, 2);
        lw(a1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
        backedge(ctx);
        goto L_0049c62c;
    }
L_0049c628:
    charge(ctx, 1);
    lw(a1, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
L_0049c62c:
    charge(ctx, 6);
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = a0;
    v1 = addu(v1, a1);
    sw(a0, v1, pipemod::kMaterial);
    // 0x0049c670
    charge(ctx, 2);
}


// sub_49C790 [worldPluginsDone] -- returns 1 (the end of the world plugins' attach sequence)
// 0x0049C790 sub_49C790 -- 8 bytes; leaf frame (no stack)
void sub_49C790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0049c790
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}


// sub_4C69F0 [v3dNormalize] -- dst = src / |src|; $f0 = the length; error 25 for a zero vector (dst = src x 0)
// 0x004C69F0 sub_4C69F0 -- 204 bytes; frame 0x30: ra sp+0x10, f20 sp+0x0
void sub_4C69F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20};
    // 0x004c69f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lwc1(f2, a1, 4);
    sd(ra, sp, 0x10);
    lwc1(f4, a1, 0);
    lwc1(f0, a1, 8);
    swc1(f20, sp, 0x0);
    mtc1(zero, f1);
    mula_s(f2, f2);
    madda_s(f4, f4);
    madd_s(f0, f0, f0);
    sqrt_s(f20, f0);
    c_le_s(f20, f1);
    if (cond(ctx)) {
        // 0x004c6a50
        charge(ctx, 1);
        mov_s(f3, f20);
    } else {
        // 0x004c6a30: 1 / length
        charge(ctx, 8);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f3, f0, f20);
    }
    // 0x004c6a54
    charge(ctx, 11);
    mul_s(f0, f4, f3);
    lwc1(f2, a1, 4);
    swc1(f0, a0, 0);
    mtc1(zero, f0);
    lwc1(f1, a1, 8);
    c_le_s(f20, f0);
    mul_s(f2, f2, f3);
    mul_s(f0, f1, f3);
    swc1(f2, a0, 4);
    swc1(f0, a0, 8);
    if (cond(ctx)) {
        // 0x004c6a88: a zero vector: error 25
        charge(ctx, 9);
        v0 = 1;
        a0 = 25;
        link(ctx, 0x4C6A90u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x28);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C6A9Cu, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    }
    // 0x004c6a80
    charge(ctx, 2);
    mov_s(f0, f20);
    // 0x004c6aac
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4C6AC0 [v3dLength] -- $f0 = |v| (3-D)
// 0x004C6AC0 sub_4C6AC0 -- 44 bytes; leaf frame (no stack)
void sub_4C6AC0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004c6ac0
    enter(ctx, 11);  // entry check point + this block's cycles
    lwc1(f2, a0, 4);
    lwc1(f1, a0, 0);
    lwc1(f0, a0, 8);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f0, f0);
}


// sub_4C6AF0 [v2dLength] -- $f0 = |v| (2-D)
// 0x004C6AF0 sub_4C6AF0 -- 36 bytes; leaf frame (no stack)
void sub_4C6AF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004c6af0
    enter(ctx, 9);  // entry check point + this block's cycles
    lwc1(f1, a0, 4);
    lwc1(f0, a0, 0);
    mula_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f0, f0);
}


// sub_4C6B20 [v2dNormalize] -- dst = src / |src| (2-D); $f0 = the length; error 25 for a zero vector
// 0x004C6B20 sub_4C6B20 -- 188 bytes; frame 0x30: ra sp+0x10, f20 sp+0x0
void sub_4C6B20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x004c6b20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lwc1(f1, a1, 4);
    sd(ra, sp, 0x10);
    lwc1(f3, a1, 0);
    swc1(f20, sp, 0x0);
    mtc1(zero, f0);
    mula_s(f1, f1);
    madd_s(f1, f3, f3);
    sqrt_s(f20, f1);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x004c6b7c
        charge(ctx, 1);
        mov_s(f2, f20);
    } else {
        // 0x004c6b5c: 1 / length
        charge(ctx, 8);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f2, f0, f20);
    }
    // 0x004c6b80
    charge(ctx, 8);
    mul_s(f0, f3, f2);
    swc1(f0, a0, 0);
    mtc1(zero, f0);
    lwc1(f1, a1, 4);
    c_le_s(f20, f0);
    mul_s(f0, f1, f2);
    swc1(f0, a0, 4);
    if (cond(ctx)) {
        // 0x004c6ba8: a zero vector: error 25
        charge(ctx, 9);
        v0 = 1;
        a0 = 25;
        link(ctx, 0x4C6BB0u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x28);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C6BBCu, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    }
    // 0x004c6ba0
    charge(ctx, 2);
    mov_s(f0, f20);
    // 0x004c6bcc
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4C6C20 [v3dTransformPoints] -- transforms points by a matrix through the vector module's function (+12); the dst
// 0x004C6C20 sub_4C6C20 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C6C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c6c20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17376);  // 0x7CE910 (the vector module offset)
    v0 = addu(v0, v1);
    lw(v0, v0, 12);
    s0 = a0;
    jalr(ctx, 0x4C6C40u, v0.u());
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C6CA0 [v3dTransformVectors] -- transforms vectors by a matrix through the vector module's function (+20); the dst
// 0x004C6CA0 sub_4C6CA0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C6CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c6ca0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17376);  // 0x7CE910 (the vector module offset)
    v0 = addu(v0, v1);
    lw(v0, v0, 20);
    s0 = a0;
    jalr(ctx, 0x4C6CC0u, v0.u());
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C6CE0 [v3dModuleClose] -- the vector module's close: counts down
// 0x004C6CE0 sub_4C6CE0 -- 20 bytes; leaf frame (no stack)
void sub_4C6CE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004c6ce0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17372);  // 0x7CE914 (the vector module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17372);  // 0x7CE914 (the vector module's open count)
}


// sub_4C7A50 [bboxCalculate] -- the box of n points: the maximum at +0, the minimum at +12; returns the box
// 0x004C7A50 sub_4C7A50 -- 272 bytes; leaf frame (no stack)
void sub_4C7A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004c7a50
    enter(ctx, 13);  // entry check point + this block's cycles
    lwc1(f2, a1, 0);
    v0 = addiu(a2, -1);
    lwc1(f1, a1, 4);
    a2 = addiu(v0, -1);
    lwc1(f0, a1, 8);
    swc1(f2, a0, bbox::kInfX);
    swc1(f1, a0, bbox::kInfY);
    swc1(f0, a0, bbox::kInfZ);
    a1 = addiu(a1, 12);
    swc1(f2, a0, bbox::kSupX);
    swc1(f1, a0, bbox::kSupY);
    swc1(f0, a0, bbox::kSupZ);
    if (v0 != 0) {
        for (;;) {
            // 0x004c7a84: each point: the minimum, then the maximum
            charge(ctx, 5);
            lwc1(f1, a1, 0);
            lwc1(f0, a0, bbox::kInfX);
            c_le_s(f0, f1);
            if (!cond(ctx)) {
                // 0x004c7b28
                charge(ctx, 2);
                swc1(f1, a0, bbox::kInfX);
                backedge(ctx);
            }
            // 0x004c7a98
            charge(ctx, 5);
            lwc1(f1, a1, 4);
            lwc1(f0, a0, bbox::kInfY);
            c_le_s(f0, f1);
            if (!cond(ctx)) {
                // 0x004c7b30
                charge(ctx, 2);
                swc1(f1, a0, bbox::kInfY);
                backedge(ctx);
            } else {
                // 0x004c7aac
                charge(ctx, 1);
            }
            // 0x004c7ab0
            charge(ctx, 5);
            lwc1(f1, a1, 8);
            lwc1(f0, a0, bbox::kInfZ);
            c_le_s(f0, f1);
            if (!cond(ctx)) {
                // 0x004c7b38
                charge(ctx, 2);
                swc1(f1, a0, bbox::kInfZ);
                backedge(ctx);
            } else {
                // 0x004c7ac4
                charge(ctx, 1);
            }
            // 0x004c7ac8
            charge(ctx, 5);
            lwc1(f1, a1, 0);
            lwc1(f0, a0, bbox::kSupX);
            c_lt_s(f0, f1);
            if (cond(ctx)) {
                // 0x004c7b40
                charge(ctx, 2);
                swc1(f1, a0, bbox::kSupX);
                backedge(ctx);
            } else {
                // 0x004c7adc
                charge(ctx, 1);
            }
            // 0x004c7ae0
            charge(ctx, 5);
            lwc1(f1, a1, 4);
            lwc1(f0, a0, bbox::kSupY);
            c_lt_s(f0, f1);
            if (cond(ctx)) {
                // 0x004c7b48
                charge(ctx, 2);
                swc1(f1, a0, bbox::kSupY);
                backedge(ctx);
            } else {
                // 0x004c7af4
                charge(ctx, 1);
            }
            // 0x004c7af8
            charge(ctx, 5);
            lwc1(f1, a1, 8);
            lwc1(f0, a0, bbox::kSupZ);
            c_lt_s(f0, f1);
            if (cond(ctx)) {
                // 0x004c7b50
                charge(ctx, 2);
                swc1(f1, a0, bbox::kSupZ);
                backedge(ctx);
            } else {
                // 0x004c7b0c
                charge(ctx, 1);
            }
            // 0x004c7b10
            charge(ctx, 4);
            v0 = a2;
            a1 = addiu(a1, 12);
            a2 = addiu(a2, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c7b20
    charge(ctx, 2);
    v0 = a0;
    // 0x004c7b58
    charge(ctx, 2);
}


// sub_4C89A0 [cameraUpdateZShiftScale] -- the camera's device z scale and shift from its clip planes
// Perspective (and any type but 2) works on 1 / far and 1 / near, parallel on near and far; the device range
// (0x960088 .. 0x96008C) is narrowed by 1e-4 of itself at both ends. Returns the camera.
// 0x004C89A0 sub_4C89A0 -- 184 bytes; leaf frame (no stack)
void sub_4C89A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004c89a0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v1, a0, camera::kProjection);
    lwc1(f4, v0, 136);  // g_rwIm2DNearScreenZ
    v0 = 0x960000;
    lwc1(f3, v0, 140);  // 0x96008C (the device's far screen z)
    v0 = 1;
    if (v1 == v0) {
        // 0x004c89e0
        charge(ctx, 1);
        lwc1(f1, a0, camera::kFarPlane);
    L_004c89e4:
        charge(ctx, 6);
        v0 = 0x3F800000;
        lwc1(f0, a0, camera::kNearPlane);
        mtc1(v0, f2);
        div_s(f5, f2, f1);
        div_s(f6, f2, f0);
    } else {
        // 0x004c89c0
        charge(ctx, 3);
        v0 = 2;
        if (v1 != v0) {
            // 0x004c89cc
            charge(ctx, 2);
            lwc1(f1, a0, camera::kFarPlane);
            goto L_004c89e4;
        }
        // 0x004c89d4: parallel: near and far as they are
        charge(ctx, 3);
        lwc1(f6, a0, camera::kNearPlane);
        lwc1(f5, a0, camera::kFarPlane);
    }
    // 0x004c89fc (the shared epilogue, written out on this path): the scale and shift that map them onto the narrowed device range
    charge(ctx, 23);
    v0 = 0x38D10000;
    v1 = 0x3F000000;
    a1 = v0 | 0xB717;
    sub_s(f2, f3, f4);
    v0 = a0;
    mtc1(a1, f1);
    mtc1(v1, f0);
    mul_s(f1, f1, f2);
    sub_s(f2, f3, f1);
    add_s(f1, f4, f1);
    sub_s(f3, f2, f1);
    add_s(f2, f2, f1);
    sub_s(f1, f5, f6);
    div_s(f4, f3, f1);
    mtc1(zero, f1);
    add_s(f3, f5, f6);
    adda_s(f1, f2);
    msub_s(f1, f4, f3);
    mul_s(f0, f0, f1);
    swc1(f4, a0, camera::kZScale);
    swc1(f0, a0, camera::kZShift);
}


// sub_4C8A60 [cameraBuildPerspFrustum] -- the perspective camera's frustum: its 8 corners and 6 planes in world space
// The near and far corners from the frame's axes, the view window and offset (scaled by the clip distances); the
// far plane and the near plane along the view axis, the four side planes from the corner cross products (normalised);
// each plane's distance and its closest-corner bytes.
// 0x004C8A60 sub_4C8A60 -- 2064 bytes; frame 0x10
void sub_4C8A60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x004c8a60
    enter(ctx, 98);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(t1, a0, camera::kFrame);
    lwc1(f1, a0, camera::kViewOffsetX);
    a2 = 0x40000000;
    a1 = addiu(a0, 292);
    t0 = addiu(sp, 0x4);
    lwc1(f0, a0, camera::kViewOffsetY);
    a3 = addiu(sp, 0x8);
    mtc1(zero, f2);
    v1 = addiu(a0, 148);
    lwc1(f7, a0, camera::kViewWindowX);
    t4 = 0;
    lwc1(f12, t1, frameltm::kRightY);
    t5 = addiu(t1, 80);
    neg_s(f1, f1);
    t3 = a1;
    lwc1(f13, t1, frameltm::kRightX);
    t2 = 0;
    lwc1(f11, t1, frameltm::kRightZ);
    lwc1(f15, t1, frameltm::kUpX);
    lwc1(f8, t1, frameltm::kUpY);
    mul_s(f4, f12, f1);
    mula_s(f13, f1);
    mul_s(f1, f11, f1);
    madd_s(f3, f15, f0);
    adda_s(f2, f4);
    madd_s(f4, f8, f0);
    adda_s(f2, f1);
    lwc1(f14, t1, frameltm::kUpZ);
    lwc1(f1, t1, frameltm::kAtY);
    lwc1(f10, a0, camera::kViewWindowY);
    mul_s(f11, f11, f7);
    madd_s(f5, f14, f0);
    lwc1(f0, t1, frameltm::kAtZ);
    mul_s(f12, f12, f7);
    adda_s(f0, f11);
    add_s(f0, f1, f12);
    lwc1(f6, t1, frameltm::kAtX);
    mul_s(f13, f13, f7);
    mul_s(f1, f15, f10);
    add_s(f6, f6, f13);
    add_s(f7, f6, f1);
    mtc1(a2, f9);
    mul_s(f8, f8, f10);
    mul_s(f6, f13, f9);
    mul_s(f13, f12, f9);
    mul_s(f12, f11, f9);
    add_s(f0, f0, f8);
    mul_s(f11, f8, f9);
    swc1(f0, t0, 0);
    mul_s(f1, f1, f9);
    sub_s(f8, f7, f6);
    swc1(f7, a0, camera::kFrustumCorners);
    sub_s(f7, f8, f1);
    lwc1(f0, sp, 0x4);
    mul_s(f1, f14, f10);
    swc1(f0, a0, 296);
    madd_s(f0, f14, f10);
    mul_s(f10, f1, f9);
    swc1(f0, a3, 0);
    lwc1(f1, t0, 0);
    lwc1(f9, sp, 0x8);
    add_s(f6, f7, f6);
    sub_s(f1, f1, f13);
    swc1(f9, a0, 300);
    lwc1(f0, a3, 0);
    swc1(f1, t0, 0);
    swc1(f8, a0, 304);
    swc1(f6, sp, 0x0);
    sub_s(f1, f0, f12);
    swc1(f1, a3, 0);
    lwc1(f0, sp, 0x4);
    lwc1(f1, t0, 0);
    lwc1(f8, sp, 0x8);
    swc1(f0, a0, 308);
    lwc1(f0, a3, 0);
    sub_s(f1, f1, f11);
    swc1(f1, t0, 0);
    swc1(f8, a0, 312);
    sub_s(f0, f0, f10);
    swc1(f0, a3, 0);
    lwc1(f1, t0, 0);
    lwc1(f0, a3, 0);
    swc1(f7, a0, 316);
    lwc1(f8, sp, 0x4);
    lwc1(f7, sp, 0x8);
    add_s(f1, f1, f13);
    add_s(f0, f0, f12);
    swc1(f1, t0, 0);
    swc1(f0, a3, 0);
    swc1(f8, a0, 320);
    swc1(f7, a0, 324);
    lwc1(f1, sp, 0x4);
    swc1(f6, a0, 328);
    lwc1(f0, sp, 0x8);
    swc1(f1, a0, 332);
    swc1(f0, a0, 336);
    for (;;) {
        // 0x004c8be8: the four near corners and the four far corners
        charge(ctx, 61);
        lwc1(f6, t5, 48);
        a2 = addiu(t2, 48);
        lwc1(f7, t3, 0);
        a3 = addu(a1, a2);
        lwc1(f1, t3, 4);
        t4 = addiu(t4, 1);
        lwc1(f0, t3, 8);
        a2 = slti(t4, 4);
        t2 = addiu(t2, 12);
        add_s(f6, f3, f6);
        swc1(f6, t3, 0);
        lwc1(f6, t5, 52);
        sub_s(f8, f7, f3);
        sub_s(f1, f1, f4);
        add_s(f6, f4, f6);
        swc1(f6, t3, 4);
        lwc1(f6, t5, 56);
        sub_s(f0, f0, f5);
        add_s(f6, f5, f6);
        swc1(f6, t3, 8);
        lwc1(f6, t3, 0);
        lwc1(f7, a0, camera::kNearPlane);
        adda_s(f2, f6);
        madd_s(f6, f8, f7);
        swc1(f6, t3, 0);
        lwc1(f6, t3, 4);
        lwc1(f7, a0, camera::kNearPlane);
        adda_s(f2, f6);
        madd_s(f6, f1, f7);
        swc1(f6, t3, 4);
        lwc1(f6, t3, 8);
        lwc1(f7, a0, camera::kNearPlane);
        adda_s(f2, f6);
        madd_s(f6, f0, f7);
        swc1(f6, t3, 8);
        lwc1(f6, t5, 48);
        t3 = addiu(t3, 12);
        add_s(f6, f3, f6);
        swc1(f6, a3, 0);
        lwc1(f6, t5, 52);
        add_s(f6, f4, f6);
        swc1(f6, a3, 4);
        lwc1(f6, t5, 56);
        add_s(f6, f5, f6);
        swc1(f6, a3, 8);
        lwc1(f6, a3, 0);
        lwc1(f7, a0, camera::kFarPlane);
        adda_s(f2, f6);
        madd_s(f6, f8, f7);
        swc1(f6, a3, 0);
        lwc1(f6, a3, 4);
        lwc1(f7, a0, camera::kFarPlane);
        adda_s(f2, f6);
        madd_s(f1, f1, f7);
        swc1(f1, a3, 4);
        lwc1(f1, a3, 8);
        lwc1(f6, a0, camera::kFarPlane);
        adda_s(f2, f1);
        madd_s(f0, f0, f6);
        swc1(f0, a3, 8);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004c8cdc: the far plane (the view axis) and the near plane (its negation)
    charge(ctx, 104);
    lwc1(f3, t5, 32);
    lwc1(f1, t5, 36);
    lwc1(f0, t5, 40);
    swc1(f3, v1, 0);
    swc1(f1, v1, 4);
    swc1(f0, v1, 8);
    lwc1(f0, t5, 36);
    lwc1(f1, a1, 52);
    lwc1(f4, a1, 48);
    lwc1(f3, t5, 32);
    lwc1(f6, a1, 56);
    lwc1(f5, t5, 40);
    mul_s(f0, f1, f0);
    adda_s(f2, f0);
    madd_s(f0, f4, f3);
    adda_s(f2, f0);
    madd_s(f0, f6, f5);
    swc1(f0, v1, 12);
    lw(a0, v1, 0);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 16);
    lw(a0, v1, 4);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 17);
    lw(a0, v1, 8);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 18);
    lwc1(f0, v1, 0);
    neg_s(f0, f0);
    swc1(f0, v1, 20);
    lwc1(f0, v1, 4);
    neg_s(f0, f0);
    swc1(f0, v1, 24);
    lwc1(f0, v1, 8);
    neg_s(f0, f0);
    swc1(f0, v1, 28);
    lwc1(f1, a1, 4);
    lwc1(f0, v1, 24);
    lwc1(f4, a1, 0);
    lwc1(f3, v1, 20);
    lwc1(f6, a1, 8);
    lwc1(f5, v1, 28);
    mul_s(f0, f1, f0);
    adda_s(f2, f0);
    madd_s(f0, f4, f3);
    adda_s(f2, f0);
    madd_s(f0, f6, f5);
    swc1(f0, v1, 32);
    lw(a0, v1, 20);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 36);
    lw(a0, v1, 24);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 37);
    lw(a0, v1, 28);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 38);
    lwc1(f5, a1, 60);
    lwc1(f0, a1, 12);
    lwc1(f3, a1, 72);
    lwc1(f7, a1, 64);
    lwc1(f1, a1, 16);
    lwc1(f6, a1, 76);
    lwc1(f9, a1, 68);
    sub_s(f0, f0, f5);
    sub_s(f8, f3, f5);
    sub_s(f1, f1, f7);
    lwc1(f4, a1, 20);
    lwc1(f5, a1, 80);
    sub_s(f7, f6, f7);
    sub_s(f3, f4, f9);
    sub_s(f6, f5, f9);
    mul_s(f5, f1, f6);
    adda_s(f2, f5);
    msub_s(f5, f3, f7);
    mul_s(f4, f3, f8);
    adda_s(f2, f4);
    swc1(f5, v1, 40);
    msub_s(f4, f0, f6);
    swc1(f4, v1, 44);
    mul_s(f4, f0, f7);
    adda_s(f2, f4);
    msub_s(f4, f1, f8);
    swc1(f4, v1, 48);
    lwc1(f4, v1, 44);
    lwc1(f6, v1, 40);
    lwc1(f5, v1, 48);
    mul_s(f4, f4, f4);
    adda_s(f2, f4);
    madd_s(f4, f6, f6);
    adda_s(f2, f4);
    madd_s(f4, f5, f5);
    sqrt_s(f4, f4);
    c_le_s(f4, f2);
    if (!cond(ctx)) {
        // 0x004c8e7c
        charge(ctx, 7);
        a0 = 0x3F800000;
        mtc1(a0, f2);
        div_s(f4, f2, f4);
    }
    // 0x004c8e98: the left plane: normalise, distance, closest corner
    charge(ctx, 62);
    lwc1(f2, v1, 40);
    mtc1(zero, f9);
    mul_s(f2, f2, f4);
    swc1(f2, v1, 40);
    lwc1(f2, v1, 44);
    mul_s(f2, f2, f4);
    swc1(f2, v1, 44);
    lwc1(f2, v1, 48);
    mul_s(f2, f2, f4);
    swc1(f2, v1, 48);
    lwc1(f4, a1, 16);
    lwc1(f2, v1, 44);
    lwc1(f6, a1, 12);
    lwc1(f5, v1, 40);
    lwc1(f8, a1, 20);
    lwc1(f7, v1, 48);
    mula_s(f4, f2);
    madda_s(f6, f5);
    madd_s(f2, f8, f7);
    swc1(f2, v1, 52);
    lw(a0, v1, 40);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 56);
    lw(a0, v1, 44);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 57);
    lw(a0, v1, 48);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 58);
    lwc1(f6, a1, 52);
    lwc1(f5, a1, 64);
    lwc1(f4, a1, 56);
    lwc1(f2, a1, 68);
    lwc1(f8, a1, 48);
    lwc1(f7, a1, 60);
    sub_s(f5, f6, f5);
    sub_s(f4, f4, f2);
    mula_s(f5, f3);
    msub_s(f2, f4, f1);
    sub_s(f7, f8, f7);
    swc1(f2, v1, 60);
    mula_s(f4, f0);
    msub_s(f2, f7, f3);
    mula_s(f7, f1);
    msub_s(f0, f5, f0);
    swc1(f2, v1, 64);
    swc1(f0, v1, 68);
    lwc1(f2, v1, 64);
    lwc1(f1, v1, 60);
    lwc1(f0, v1, 68);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f1, f0);
    c_le_s(f1, f9);
    if (!cond(ctx)) {
        // 0x004c8f90
        charge(ctx, 7);
        a0 = 0x3F800000;
        mtc1(a0, f0);
        div_s(f1, f0, f1);
    }
    // 0x004c8fac: the top plane
    charge(ctx, 68);
    lwc1(f0, v1, 60);
    mtc1(zero, f8);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 60);
    lwc1(f0, v1, 64);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 64);
    lwc1(f0, v1, 68);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 68);
    lwc1(f1, a1, 16);
    lwc1(f0, v1, 64);
    lwc1(f3, a1, 12);
    lwc1(f2, v1, 60);
    lwc1(f5, a1, 20);
    lwc1(f4, v1, 68);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    swc1(f0, v1, 72);
    lw(a0, v1, 60);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 76);
    lw(a0, v1, 64);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 77);
    lw(a0, v1, 68);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 78);
    lwc1(f4, a1, 84);
    lwc1(f0, a1, 36);
    lwc1(f2, a1, 48);
    lwc1(f7, a1, 92);
    lwc1(f3, a1, 44);
    lwc1(f5, a1, 88);
    lwc1(f1, a1, 40);
    sub_s(f0, f0, f4);
    sub_s(f6, f2, f4);
    sub_s(f2, f3, f7);
    lwc1(f4, a1, 52);
    sub_s(f1, f1, f5);
    lwc1(f3, a1, 56);
    sub_s(f5, f4, f5);
    sub_s(f4, f3, f7);
    mula_s(f1, f4);
    msub_s(f3, f2, f5);
    swc1(f3, v1, 80);
    mula_s(f2, f6);
    msub_s(f3, f0, f4);
    swc1(f3, v1, 84);
    mula_s(f0, f5);
    msub_s(f3, f1, f6);
    swc1(f3, v1, 88);
    lwc1(f5, v1, 84);
    lwc1(f4, v1, 80);
    lwc1(f3, v1, 88);
    mula_s(f5, f5);
    madda_s(f4, f4);
    madd_s(f3, f3, f3);
    sqrt_s(f4, f3);
    c_le_s(f4, f8);
    if (!cond(ctx)) {
        // 0x004c90bc
        charge(ctx, 7);
        a0 = 0x3F800000;
        mtc1(a0, f3);
        div_s(f4, f3, f4);
    }
    // 0x004c90d8: the right plane
    charge(ctx, 62);
    lwc1(f3, v1, 80);
    mtc1(zero, f9);
    mul_s(f3, f3, f4);
    swc1(f3, v1, 80);
    lwc1(f3, v1, 84);
    mul_s(f3, f3, f4);
    swc1(f3, v1, 84);
    lwc1(f3, v1, 88);
    mul_s(f3, f3, f4);
    swc1(f3, v1, 88);
    lwc1(f4, a1, 40);
    lwc1(f3, v1, 84);
    lwc1(f6, a1, 36);
    lwc1(f5, v1, 80);
    lwc1(f8, a1, 44);
    lwc1(f7, v1, 88);
    mula_s(f4, f3);
    madda_s(f6, f5);
    madd_s(f3, f8, f7);
    swc1(f3, v1, 92);
    lw(a0, v1, 80);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 96);
    lw(a0, v1, 84);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 97);
    lw(a0, v1, 88);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 98);
    lwc1(f6, a1, 76);
    lwc1(f5, a1, 88);
    lwc1(f4, a1, 80);
    lwc1(f3, a1, 92);
    lwc1(f8, a1, 72);
    lwc1(f7, a1, 84);
    sub_s(f5, f6, f5);
    sub_s(f4, f4, f3);
    mula_s(f5, f2);
    msub_s(f3, f4, f1);
    sub_s(f7, f8, f7);
    mula_s(f4, f0);
    msub_s(f2, f7, f2);
    swc1(f3, v1, 100);
    mula_s(f7, f1);
    msub_s(f0, f5, f0);
    swc1(f2, v1, 104);
    swc1(f0, v1, 108);
    lwc1(f2, v1, 104);
    lwc1(f1, v1, 100);
    lwc1(f0, v1, 108);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f1, f0);
    c_le_s(f1, f9);
    if (!cond(ctx)) {
        // 0x004c91d0
        charge(ctx, 7);
        a0 = 0x3F800000;
        mtc1(a0, f0);
        div_s(f1, f0, f1);
    }
    // 0x004c91ec: the bottom plane
    charge(ctx, 33);
    lwc1(f0, v1, 100);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 100);
    lwc1(f0, v1, 104);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 104);
    lwc1(f0, v1, 108);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 108);
    lwc1(f1, a1, 40);
    lwc1(f0, v1, 104);
    lwc1(f3, a1, 36);
    lwc1(f2, v1, 100);
    lwc1(f5, a1, 44);
    lwc1(f4, v1, 108);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    swc1(f0, v1, 112);
    lw(a0, v1, 100);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 116);
    lw(a0, v1, 104);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 117);
    lw(a0, v1, 108);
    a0 = sra(a0, 31);
    a0 = addiu(a0, 1);
    sb(a0, v1, 118);
    sp = addiu(sp, 0x10);
}


// sub_4C9270 [cameraBuildPerspViewMatrix] -- the perspective camera's view matrix from its frame and view window / offset
// (the frame's inverse scaled by 1 / the view window, the offset folded in; then optimised, sub_4C2D20).
// 0x004C9270 sub_4C9270 -- 400 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004c9270
    enter(ctx, 100);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = lui(0xBF00);
    sd(ra, sp, 0x10);
    v0 = 0x3F000000;
    sq(s0, sp, 0x0);
    mtc1(v1, f9);
    lw(a3, a0, camera::kFrame);
    lwc1(f5, a0, camera::kRecipViewWindowX);
    s0 = a0;
    a1 = 0;
    lwc1(f1, a0, camera::kViewOffsetX);
    a2 = addiu(s0, 32);
    mtc1(v0, f0);
    mtc1(zero, f8);
    lwc1(f4, a3, frameltm::kRightX);
    mul_s(f7, f9, f5);
    lwc1(f3, a3, frameltm::kRightY);
    lwc1(f2, a3, frameltm::kRightZ);
    mul_s(f6, f4, f7);
    mul_s(f5, f3, f7);
    mul_s(f4, f2, f7);
    adda_s(f8, f0);
    msub_s(f7, f7, f1);
    lwc1(f3, a3, frameltm::kAtX);
    adda_s(f8, f6);
    lwc1(f2, a3, frameltm::kAtY);
    lwc1(f1, a3, frameltm::kAtZ);
    madd_s(f6, f3, f7);
    adda_s(f8, f5);
    madd_s(f5, f2, f7);
    adda_s(f8, f4);
    swc1(f6, a0, camera::kViewMatrix);
    madd_s(f4, f1, f7);
    swc1(f5, a0, camera::kView10);
    swc1(f4, a0, camera::kView20);
    lwc1(f1, a3, frameltm::kPosY);
    lwc1(f2, a3, frameltm::kPosX);
    lwc1(f3, a3, frameltm::kPosZ);
    mula_s(f1, f5);
    madda_s(f2, f6);
    madd_s(f1, f3, f4);
    add_s(f1, f7, f1);
    sub_s(f1, f0, f1);
    swc1(f1, a0, camera::kView30);
    lwc1(f6, a0, camera::kRecipViewWindowY);
    lwc1(f5, a3, frameltm::kUpX);
    lwc1(f4, a3, frameltm::kUpY);
    lwc1(f3, a3, frameltm::kUpZ);
    lwc1(f2, a0, camera::kViewOffsetY);
    lwc1(f1, a3, frameltm::kAtX);
    mul_s(f6, f9, f6);
    adda_s(f8, f0);
    madd_s(f7, f6, f2);
    mul_s(f5, f5, f6);
    mul_s(f4, f4, f6);
    mul_s(f3, f3, f6);
    adda_s(f8, f5);
    madd_s(f6, f1, f7);
    lwc1(f2, a3, frameltm::kAtY);
    lwc1(f1, a3, frameltm::kAtZ);
    adda_s(f8, f4);
    madd_s(f5, f2, f7);
    adda_s(f8, f3);
    swc1(f6, a0, camera::kView01);
    madd_s(f4, f1, f7);
    swc1(f5, a0, camera::kView11);
    swc1(f4, a0, camera::kView21);
    lwc1(f1, a3, frameltm::kPosY);
    lwc1(f2, a3, frameltm::kPosX);
    lwc1(f3, a3, frameltm::kPosZ);
    mula_s(f1, f5);
    madda_s(f2, f6);
    madd_s(f1, f3, f4);
    add_s(f1, f7, f1);
    sub_s(f0, f0, f1);
    swc1(f0, a0, camera::kView31);
    lwc1(f0, a3, frameltm::kAtX);
    swc1(f0, a0, camera::kView02);
    lwc1(f0, a3, frameltm::kAtY);
    swc1(f0, a0, camera::kView12);
    lwc1(f0, a3, frameltm::kAtZ);
    swc1(f0, a0, camera::kView22);
    lwc1(f1, a3, frameltm::kPosY);
    lwc1(f0, a3, frameltm::kAtY);
    lwc1(f3, a3, frameltm::kPosX);
    lwc1(f2, a3, frameltm::kAtX);
    lwc1(f5, a3, frameltm::kPosZ);
    lwc1(f4, a3, frameltm::kAtZ);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    neg_s(f0, f0);
    swc1(f0, a0, camera::kView32);
    a0 = a2;
    jal(ctx, 0x4C93E4u, gen::fn_sub_4C2D20_004c2d20);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9400 [cameraBuildParallelFrustum] -- the parallel camera's frustum: its 8 corners (transformed by the frame, sub_4C6C20) and 6 planes
// 0x004C9400 sub_4C9400 -- 1336 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C9400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004c9400
    enter(ctx, 159);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x3F800000;
    sd(ra, sp, 0x30);
    mtc1(v0, f0);
    sq(s2, sp, 0x20);
    a2 = 8;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(a0, 292);
    lw(v1, a0, camera::kFrame);
    lwc1(f8, a0, camera::kViewWindowX);
    lwc1(f6, a0, camera::kNearPlane);
    s0 = addiu(a0, 148);
    lwc1(f1, a0, camera::kViewOffsetX);
    a1 = s1;
    lwc1(f7, a0, camera::kViewWindowY);
    lwc1(f3, a0, camera::kFarPlane);
    lwc1(f4, a0, camera::kViewOffsetY);
    s2 = addiu(v1, 80);
    sub_s(f2, f0, f6);
    a3 = s2;
    swc1(f6, a0, 336);
    swc1(f6, a0, 324);
    swc1(f6, a0, 312);
    swc1(f6, a0, 300);
    swc1(f3, a0, 384);
    swc1(f3, a0, 372);
    swc1(f3, a0, 360);
    sub_s(f0, f0, f3);
    neg_s(f1, f1);
    swc1(f3, a0, 348);
    mul_s(f3, f2, f1);
    mul_s(f1, f0, f1);
    add_s(f6, f8, f3);
    swc1(f6, a0, 328);
    mul_s(f2, f2, f4);
    mul_s(f0, f0, f4);
    neg_s(f5, f8);
    add_s(f4, f5, f3);
    add_s(f3, f8, f1);
    swc1(f6, a0, camera::kFrustumCorners);
    swc1(f4, a0, 316);
    swc1(f4, a0, 304);
    swc1(f3, a0, 376);
    swc1(f3, a0, 340);
    add_s(f1, f5, f1);
    swc1(f1, a0, 364);
    swc1(f1, a0, 352);
    add_s(f1, f7, f2);
    swc1(f1, a0, 308);
    swc1(f1, a0, 296);
    neg_s(f3, f7);
    add_s(f2, f3, f2);
    add_s(f1, f7, f0);
    swc1(f2, a0, 332);
    swc1(f2, a0, 320);
    swc1(f1, a0, 356);
    add_s(f0, f3, f0);
    swc1(f1, a0, 344);
    swc1(f0, a0, 380);
    swc1(f0, a0, 368);
    a0 = s1;
    jal(ctx, 0x4C94F4u, gen::fn_sub_4C6C20_004c6c20);
    lwc1(f3, s2, rwmatrix::kAt);
    lwc1(f2, s2, 36);
    lwc1(f1, s2, 40);
    mtc1(zero, f0);
    swc1(f3, s0, 0);
    swc1(f2, s0, 4);
    swc1(f1, s0, 8);
    lwc1(f2, s1, 52);
    lwc1(f1, s0, 4);
    lwc1(f4, s1, 48);
    lwc1(f3, s0, 0);
    lwc1(f6, s1, 56);
    lwc1(f5, s0, 8);
    mula_s(f2, f1);
    madda_s(f4, f3);
    madd_s(f1, f6, f5);
    swc1(f1, s0, 12);
    lw(v1, s0, 0);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 16);
    lw(v1, s0, 4);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 17);
    lw(v1, s0, 8);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 18);
    lwc1(f1, s0, 0);
    neg_s(f1, f1);
    swc1(f1, s0, 20);
    lwc1(f1, s0, 4);
    neg_s(f1, f1);
    swc1(f1, s0, 24);
    lwc1(f1, s0, 8);
    neg_s(f1, f1);
    swc1(f1, s0, 28);
    lwc1(f2, s1, 4);
    lwc1(f1, s0, 24);
    lwc1(f4, s1, 0);
    lwc1(f3, s0, 20);
    lwc1(f6, s1, 8);
    lwc1(f5, s0, 28);
    mula_s(f2, f1);
    madda_s(f4, f3);
    madd_s(f1, f6, f5);
    swc1(f1, s0, 32);
    lw(v1, s0, 20);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 36);
    lw(v1, s0, 24);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 37);
    lw(v1, s0, 28);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 38);
    lwc1(f5, s1, 60);
    lwc1(f1, s1, 12);
    lwc1(f3, s1, 72);
    lwc1(f8, s1, 68);
    lwc1(f4, s1, 20);
    lwc1(f6, s1, 64);
    lwc1(f2, s1, 16);
    sub_s(f1, f1, f5);
    sub_s(f7, f3, f5);
    sub_s(f3, f4, f8);
    lwc1(f5, s1, 76);
    sub_s(f2, f2, f6);
    lwc1(f4, s1, 80);
    sub_s(f6, f5, f6);
    sub_s(f5, f4, f8);
    mula_s(f2, f5);
    msub_s(f4, f3, f6);
    swc1(f4, s0, 40);
    mula_s(f3, f7);
    msub_s(f4, f1, f5);
    swc1(f4, s0, 44);
    mula_s(f1, f6);
    msub_s(f4, f2, f7);
    swc1(f4, s0, 48);
    lwc1(f6, s0, 44);
    lwc1(f5, s0, 40);
    lwc1(f4, s0, 48);
    mula_s(f6, f6);
    madda_s(f5, f5);
    madd_s(f4, f4, f4);
    sqrt_s(f4, f4);
    c_le_s(f4, f0);
    if (!cond(ctx)) {
        // 0x004c967c
        charge(ctx, 7);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f4, f0, f4);
    }
    // 0x004c9698: the left plane: normalise, distance, closest corner
    charge(ctx, 62);
    lwc1(f0, s0, 40);
    mtc1(zero, f9);
    mul_s(f0, f0, f4);
    swc1(f0, s0, 40);
    lwc1(f0, s0, 44);
    mul_s(f0, f0, f4);
    swc1(f0, s0, 44);
    lwc1(f0, s0, 48);
    mul_s(f0, f0, f4);
    swc1(f0, s0, 48);
    lwc1(f4, s1, 16);
    lwc1(f0, s0, 44);
    lwc1(f6, s1, 12);
    lwc1(f5, s0, 40);
    lwc1(f8, s1, 20);
    lwc1(f7, s0, 48);
    mula_s(f4, f0);
    madda_s(f6, f5);
    madd_s(f0, f8, f7);
    swc1(f0, s0, 52);
    lw(v1, s0, 40);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 56);
    lw(v1, s0, 44);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 57);
    lw(v1, s0, 48);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 58);
    lwc1(f6, s1, 52);
    lwc1(f5, s1, 64);
    lwc1(f4, s1, 56);
    lwc1(f0, s1, 68);
    lwc1(f8, s1, 48);
    lwc1(f7, s1, 60);
    sub_s(f5, f6, f5);
    sub_s(f4, f4, f0);
    mula_s(f5, f3);
    msub_s(f0, f4, f2);
    sub_s(f7, f8, f7);
    mula_s(f4, f1);
    msub_s(f3, f7, f3);
    swc1(f0, s0, 60);
    mula_s(f7, f2);
    msub_s(f0, f5, f1);
    swc1(f3, s0, 64);
    swc1(f0, s0, 68);
    lwc1(f2, s0, 64);
    lwc1(f1, s0, 60);
    lwc1(f0, s0, 68);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f1, f0);
    c_le_s(f1, f9);
    if (!cond(ctx)) {
        // 0x004c9790
        charge(ctx, 7);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f1, f0, f1);
    }
    // 0x004c97ac: the top plane
    charge(ctx, 99);
    lwc1(f0, s0, 60);
    mul_s(f0, f0, f1);
    swc1(f0, s0, 60);
    lwc1(f0, s0, 64);
    mul_s(f0, f0, f1);
    swc1(f0, s0, 64);
    lwc1(f0, s0, 68);
    mul_s(f0, f0, f1);
    swc1(f0, s0, 68);
    lwc1(f1, s1, 16);
    lwc1(f0, s0, 64);
    lwc1(f3, s1, 12);
    lwc1(f2, s0, 60);
    lwc1(f5, s1, 20);
    lwc1(f4, s0, 68);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    swc1(f0, s0, 72);
    lw(v1, s0, 60);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 76);
    lw(v1, s0, 64);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 77);
    lw(v1, s0, 68);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 78);
    lwc1(f0, s0, 40);
    neg_s(f0, f0);
    swc1(f0, s0, 80);
    lwc1(f0, s0, 44);
    neg_s(f0, f0);
    swc1(f0, s0, 84);
    lwc1(f0, s0, 48);
    neg_s(f0, f0);
    swc1(f0, s0, 88);
    lwc1(f1, s1, 40);
    lwc1(f0, s0, 84);
    lwc1(f3, s1, 36);
    lwc1(f2, s0, 80);
    lwc1(f5, s1, 44);
    lwc1(f4, s0, 88);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    swc1(f0, s0, 92);
    lw(v1, s0, 80);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 96);
    lw(v1, s0, 84);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 97);
    lw(v1, s0, 88);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 98);
    lwc1(f0, s0, 60);
    neg_s(f0, f0);
    swc1(f0, s0, 100);
    lwc1(f0, s0, 64);
    neg_s(f0, f0);
    swc1(f0, s0, 104);
    lwc1(f0, s0, 68);
    neg_s(f0, f0);
    swc1(f0, s0, 108);
    lwc1(f1, s1, 40);
    lwc1(f0, s0, 104);
    lwc1(f3, s1, 36);
    lwc1(f2, s0, 100);
    lwc1(f5, s1, 44);
    lwc1(f4, s0, 108);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    swc1(f0, s0, 112);
    lw(v1, s0, 100);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 116);
    lw(v1, s0, 104);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 117);
    lw(v1, s0, 108);
    v1 = sra(v1, 31);
    v1 = addiu(v1, 1);
    sb(v1, s0, 118);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4C9940 [cameraBuildParallelViewMatrix] -- the parallel camera's view matrix from its frame and view window / offset
// 0x004C9940 sub_4C9940 -- 388 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004c9940
    enter(ctx, 97);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = lui(0xBF00);
    sd(ra, sp, 0x10);
    v0 = 0x3F000000;
    sq(s0, sp, 0x0);
    mtc1(v1, f9);
    lw(a3, a0, camera::kFrame);
    lwc1(f5, a0, camera::kRecipViewWindowX);
    s0 = a0;
    a1 = 0;
    lwc1(f1, a0, camera::kViewOffsetX);
    a2 = addiu(s0, 32);
    mtc1(zero, f8);
    mtc1(v0, f7);
    mul_s(f5, f9, f5);
    lwc1(f3, a3, frameltm::kRightY);
    lwc1(f2, a3, frameltm::kRightZ);
    lwc1(f4, a3, frameltm::kRightX);
    mul_s(f1, f5, f1);
    neg_s(f6, f1);
    lwc1(f0, a3, frameltm::kAtX);
    mul_s(f3, f3, f5);
    mul_s(f2, f2, f5);
    mula_s(f4, f5);
    madd_s(f5, f0, f6);
    lwc1(f1, a3, frameltm::kAtY);
    lwc1(f0, a3, frameltm::kAtZ);
    adda_s(f8, f3);
    madd_s(f4, f1, f6);
    adda_s(f8, f2);
    swc1(f5, a0, camera::kViewMatrix);
    madd_s(f3, f0, f6);
    swc1(f4, a0, camera::kView10);
    swc1(f3, a0, camera::kView20);
    lwc1(f0, a3, frameltm::kPosY);
    lwc1(f1, a3, frameltm::kPosX);
    lwc1(f2, a3, frameltm::kPosZ);
    mula_s(f0, f4);
    madda_s(f1, f5);
    madd_s(f0, f2, f3);
    add_s(f0, f6, f0);
    sub_s(f0, f7, f0);
    swc1(f0, a0, camera::kView30);
    lwc1(f5, a0, camera::kRecipViewWindowY);
    lwc1(f3, a3, frameltm::kUpY);
    lwc1(f2, a3, frameltm::kUpZ);
    lwc1(f1, a0, camera::kViewOffsetY);
    lwc1(f4, a3, frameltm::kUpX);
    lwc1(f0, a3, frameltm::kAtX);
    mul_s(f5, f9, f5);
    mul_s(f6, f5, f1);
    mul_s(f3, f3, f5);
    mul_s(f2, f2, f5);
    mula_s(f4, f5);
    madd_s(f5, f0, f6);
    lwc1(f1, a3, frameltm::kAtY);
    lwc1(f0, a3, frameltm::kAtZ);
    adda_s(f8, f3);
    madd_s(f4, f1, f6);
    adda_s(f8, f2);
    swc1(f5, a0, camera::kView01);
    madd_s(f3, f0, f6);
    swc1(f4, a0, camera::kView11);
    swc1(f3, a0, camera::kView21);
    lwc1(f0, a3, frameltm::kPosY);
    lwc1(f1, a3, frameltm::kPosX);
    lwc1(f2, a3, frameltm::kPosZ);
    mula_s(f0, f4);
    madda_s(f1, f5);
    madd_s(f0, f2, f3);
    add_s(f0, f6, f0);
    sub_s(f0, f7, f0);
    swc1(f0, a0, camera::kView31);
    lwc1(f0, a3, frameltm::kAtX);
    swc1(f0, a0, camera::kView02);
    lwc1(f0, a3, frameltm::kAtY);
    swc1(f0, a0, camera::kView12);
    lwc1(f0, a3, frameltm::kAtZ);
    swc1(f0, a0, camera::kView22);
    lwc1(f1, a3, frameltm::kPosY);
    lwc1(f0, a3, frameltm::kAtY);
    lwc1(f3, a3, frameltm::kPosX);
    lwc1(f2, a3, frameltm::kAtX);
    lwc1(f5, a3, frameltm::kPosZ);
    lwc1(f4, a3, frameltm::kAtZ);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    neg_s(f0, f0);
    swc1(f0, a0, camera::kView32);
    a0 = a2;
    jal(ctx, 0x4C9AA8u, gen::fn_sub_4C2D20_004c2d20);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9AD0 [cameraSync] -- the camera's object sync: the view matrix and frustum for its projection, then the frustum's box
// (sub_4C7A50 over the 8 corners). Returns the camera.
// 0x004C9AD0 sub_4C9AD0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9AD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9ad0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, camera::kProjection);
    s0 = a0;
    if (v1 != v0) {
        // 0x004c9b04: parallel
        charge(ctx, 5);
        jal(ctx, 0x4C9B04u, gen::fn_sub_4C9940_004c9940);
        a0 = s0;
        jal(ctx, 0x4C9B0Cu, gen::fn_sub_4C9400_004c9400);
        a0 = addiu(s0, 268);
    } else {
        // 0x004c9aec: perspective
        charge(ctx, 6);
        jal(ctx, 0x4C9AECu, gen::fn_sub_4C9270_004c9270);
        a0 = s0;
        jal(ctx, 0x4C9AF4u, gen::fn_sub_4C8A60_004c8a60);
        a0 = addiu(s0, 268);
    }
    // 0x004c9b18: the frustum's box
    charge(ctx, 8);
    a1 = addiu(s0, 292);
    a2 = 8;
    jal(ctx, 0x4C9B1Cu, gen::fn_sub_4C7A50_004c7a50);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// CameraEndUpdate -- the camera's end-update: the device's end-update; the current camera cleared; the camera or 0
// 0x004C9B40 CameraEndUpdate -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void CameraEndUpdate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9b40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    a2 = 0;
    sq(s0, sp, 0x0);
    lw(v0, v0, 224);  // 0x9600E0 (the device's camera end-update function)
    s0 = a0;
    a0 = 0;
    a1 = s0;
    jalr(ctx, 0x4C9B60u, v0.u());
    if (v0 != 0) {
        // 0x004c9b78
        charge(ctx, 3);
        v1 = 0x960000;
        v0 = s0;
        sw(zero, v1, 112);  // 0x960070 (the current camera, engine +0)
    } else {
        // 0x004c9b70
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c9b84 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// CameraBeginUpdate -- the camera's begin-update: current camera, dirty frames synced, the device's begin-update
// (the dirty frames by sub_4CF340), then sub_4F28E0; the camera or 0.
// 0x004C9BA0 CameraBeginUpdate -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void CameraBeginUpdate(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9ba0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4C9BB4u);  // $ra first: the delay slot below depends on it
    sw(s0, v0, 112);  // 0x960070 (the current camera, engine +0)
    call(ctx, gen::fn_sub_4CF340_004cf340);
    v0 = 0x960000;
    a0 = 0;
    lw(v0, v0, 188);  // 0x9600BC (the device's camera begin-update function)
    a1 = s0;
    a2 = 0;
    jalr(ctx, 0x4C9BCCu, v0.u());
    if (v0 != 0) {
        // 0x004c9be4
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x4C9BE4u, gen::fn_sub_4F28E0_004f28e0);
        v0 = s0;
    } else {
        // 0x004c9bdc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c9bf0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9C00 [cameraModuleClose] -- the camera module's close: destroys the camera free list; count down
// 0x004C9C00 sub_4C9C00 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9c00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17360);  // 0x7CE920 (the camera module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004c9c2c
        charge(ctx, 7);
        jal(ctx, 0x4C9C2Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17360);  // 0x7CE920 (the camera module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x004c9c48 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17356);  // 0x7CE924 (the camera module's open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17356);  // 0x7CE924 (the camera module's open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9C70 [cameraModuleOpen] -- the camera module's open: the camera free list (16-aligned, static record 0x960040)
// 0x004C9C70 sub_4C9C70 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9c70
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x780000;
    sq(s0, sp, 0x0);
    a2 = 16;
    s0 = a0;
    sw(a1, gp, -17360);  // 0x7CE920 (the camera module offset)
    lw(a0, v0, -6688);  // 0x77E5E0 (the camera plugin registry)
    t0 = addiu(t0, 64);  // &0x960040 (the camera free list's static record)
    lw(a1, gp, -20364);  // 0x7CDD64 (the camera free list's entries per block)
    lw(a3, gp, -20360);  // 0x7CDD68 (the camera free list's preallocated blocks)
    v0 = 0x40000;
    t1 = v0 | 0x5;
    jal(ctx, 0x4C9CA4u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17360);  // 0x7CE920 (the camera module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x004c9cd4: count the open, return the instance
        charge(ctx, 4);
        lw(v1, gp, -17356);  // 0x7CE924 (the camera module's open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17356);  // 0x7CE924 (the camera module's open count)
    } else {
        // 0x004c9ccc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c9ce4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9D20 [cameraSetViewOffset] -- sets the camera's view offset (x, y); its frame marked dirty; returns the camera
// 0x004C9D20 sub_4C9D20 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004c9d20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lwc1(f1, a1, 0);
    sd(ra, sp, 0x10);
    lwc1(f0, a1, 4);
    sq(s0, sp, 0x0);
    s0 = a0;
    swc1(f1, a0, camera::kViewOffsetX);
    swc1(f0, a0, camera::kViewOffsetY);
    lw(a0, a0, camera::kFrame);
    if (a0 != 0) {
        // 0x004c9d4c
        charge(ctx, 2);
        jal(ctx, 0x4C9D4Cu, gen::fn_sub_4CB270_004cb270);
    }
    // 0x004c9d54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9DB0 [cameraSetFarClipPlane] -- sets the far clip ($f12), refreshes the z scale / shift, marks the frame dirty
// 0x004C9DB0 sub_4C9DB0 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004c9db0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4C9DC0u);  // $ra first: the delay slot below depends on it
    swc1(f12, a0, camera::kFarPlane);
    call(ctx, gen::fn_sub_4C89A0_004c89a0);
    lw(a0, s0, camera::kFrame);
    if (a0 != 0) {
        // 0x004c9dd4
        charge(ctx, 2);
        jal(ctx, 0x4C9DD4u, gen::fn_sub_4CB270_004cb270);
    }
    // 0x004c9ddc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C9F00 [cameraSetProjection] -- sets the projection (1 perspective, 2 parallel; else 'Invalid projection type
// specified', 0x80000003, 0); marks the frame dirty and refreshes the z scale / shift; returns the camera.
// 0x004C9F00 sub_4C9F00 -- 136 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9f00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (a1 != v1) {
        // 0x004c9f18
        charge(ctx, 3);
        v0 = 2;
        if (a1 == v0) {
            goto L_004c9f2c;
        }
        // 0x004c9f24: an invalid type: error 0x80000003 with the string, 0
        charge(ctx, 2);
        v0 = lui(0x8000);
        // 0x004c9f54
        charge(ctx, 9);
        a1 = 0x780000;
        sw(v1, sp, 0x28);
        a0 = v0 | 0x3;
        a1 = addiu(a1, -6656);  // "Invalid projection type specified"
        jal(ctx, 0x4C9F60u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C9F6Cu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004c9f78 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004c9f2c:
    charge(ctx, 4);
    sw(a1, s0, camera::kProjection);
    lw(a0, s0, camera::kFrame);
    if (a0 != 0) {
        // 0x004c9f3c
        charge(ctx, 2);
        jal(ctx, 0x4C9F3Cu, gen::fn_sub_4CB270_004cb270);
    }
    // 0x004c9f44
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x4C9F44u, gen::fn_sub_4C89A0_004c89a0);
    v0 = s0;
    // 0x004c9f78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4C9F90 [cameraSetViewWindow] -- sets the view window (x, y) and its reciprocals; marks the frame dirty
// 0x004C9F90 sub_4C9F90 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C9F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004c9f90
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x3F800000;
    lwc1(f2, a1, 0);
    sd(ra, sp, 0x10);
    lwc1(f0, a1, 4);
    sq(s0, sp, 0x0);
    mtc1(v0, f1);
    s0 = a0;
    swc1(f2, a0, camera::kViewWindowX);
    swc1(f0, a0, camera::kViewWindowY);
    lwc1(f0, a0, camera::kViewWindowX);
    div_s(f0, f1, f0);
    swc1(f0, a0, camera::kRecipViewWindowX);
    lwc1(f0, a0, camera::kViewWindowY);
    div_s(f0, f1, f0);
    swc1(f0, a0, camera::kRecipViewWindowY);
    lw(a0, a0, camera::kFrame);
    if (a0 != 0) {
        // 0x004c9fe0
        charge(ctx, 2);
        jal(ctx, 0x4C9FE0u, gen::fn_sub_4CB270_004cb270);
    }
    // 0x004c9fe8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4CA000 [cameraRegisterPlugin] -- registers a camera plugin (sub_4C61B0 on the camera registry 0x77E5E0)
// 0x004CA000 sub_4CA000 -- 44 bytes; leaf frame (no stack)
void sub_4CA000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004ca000
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -6688);  // &0x77E5E0 (the camera plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_4CA090 [cameraCreate] -- a camera from the camera free list, then the camera plugins' constructors
// RwObject type 4, the sync sub_4C9AD0, CameraBeginUpdate / CameraEndUpdate, view window 1 x 1 (reciprocals 1), no
// offset, near 0.05, far 10, fog 5, no rasters, perspective, the z scale / shift (sub_4C89A0).
// 0x004CA090 sub_4CA090 -- 252 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CA090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004ca090
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0x5;
    lw(a0, gp, -17360);  // 0x7CE920 (the camera module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4CA0BCu);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x004ca178
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004ca0d0: fill the record, the z scale / shift, the plugin constructors
        charge(ctx, 42);
        v0 = 4;
        a1 = 0x4D0000;
        sb(v0, s0, rwobj::kType);
        v1 = 0x4D0000;
        sb(zero, s0, rwobj::kSubType);
        a0 = 0x4D0000;
        sb(zero, s0, rwobj::kFlags);
        v0 = 0x3D4C0000;
        sb(zero, s0, rwobj::kPrivateFlags);
        a2 = v0 | 0xCCCD;
        a1 = addiu(a1, -25904);  // &sub_4C9AD0
        sw(zero, s0, camera::kFrame);
        sw(a1, s0, camera::kSync);
        v1 = addiu(v1, -25696);  // &CameraBeginUpdate
        sw(v1, s0, camera::kBeginUpdate);
        a0 = addiu(a0, -25792);  // &CameraEndUpdate
        sw(a0, s0, camera::kEndUpdate);
        a3 = 0x3F800000;
        sw(a3, s0, camera::kViewWindowY);
        a1 = 0x41200000;
        sw(a3, s0, camera::kViewWindowX);
        v1 = 0x40A00000;
        sw(a3, s0, camera::kRecipViewWindowY);
        v0 = 1;
        sw(a3, s0, camera::kRecipViewWindowX);
        a0 = s0;
        sw(zero, s0, camera::kViewOffsetY);
        sw(zero, s0, camera::kViewOffsetX);
        sw(a2, s0, camera::kNearPlane);
        sw(a1, s0, camera::kFarPlane);
        sw(v1, s0, camera::kFogPlane);
        sw(zero, s0, camera::kFrameBuffer);
        sw(zero, s0, camera::kZBuffer);
        link(ctx, 0x4CA154u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, camera::kProjection);
        call(ctx, gen::fn_sub_4C89A0_004c89a0);
        a0 = 0x780000;
        a1 = s0;
        a0 = addiu(a0, -6688);  // &0x77E5E0 (the camera plugin registry)
        link(ctx, 0x4CA168u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, camera::kViewMatrixFlags);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s0;
    }
    // 0x004ca17c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4CBC70 [imageModuleClose] -- the image module's close: its scratch buffers and list records freed, its free lists destroyed
// (the buffers at +528 and +4; the records of the list at +540, linked at +48, back to the free list at +536;
// that free list and the image free list destroyed); count down.
// 0x004CBC70 sub_4CBC70 -- 388 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CBC70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cbc70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
    v0 = addu(v0, v1);
    lw(a0, v0, 528);
    if (a0 != 0) {
        // 0x004cbca0: free the scratch buffer at +528
        charge(ctx, 10);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4CBCA8u, v0.u());
        lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 528);
        sw(zero, v0, 532);
    }
    // 0x004cbcc8
    charge(ctx, 7);
    lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(a0, v0, 4);
    if (a0 != 0) {
        // 0x004cbce4: free the scratch buffer at +4
        charge(ctx, 10);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4CBCECu, v0.u());
        lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 4);
        sw(zero, v0, 8);
    }
    // 0x004cbd0c
    charge(ctx, 7);
    lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a2 = addu(v0, v1);
    lw(a1, a2, 540);
    if (a1 != 0) {
        // 0x004cbd28: return the list's records to their free list
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x004cbd30
            charge(ctx, 16);
            lw(a0, a1, 48);
            v0 = 0x960000;
            lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
            v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            sw(a0, a2, 540);
            v1 = addu(v0, v1);
            lw(v0, s0, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4CBD4Cu);  // $ra = the return address
            lw(a0, v1, 536);
            call_ptr(ctx, jt);
            lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            a2 = addu(v0, v1);
            lw(a1, a2, 540);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004cbd70: destroy that free list
    charge(ctx, 3);
    lw(a0, a2, 536);
    if (a0 != 0) {
        // 0x004cbd7c
        charge(ctx, 7);
        jal(ctx, 0x4CBD7Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 536);
    }
    // 0x004cbd98: destroy the image free list
    charge(ctx, 7);
    lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004cbdb4
        charge(ctx, 7);
        jal(ctx, 0x4CBDB4u, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x004cbdd0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, gp, -17332);  // 0x7CE93C (the image module's open count)
    v0 = s1;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17332);  // 0x7CE93C (the image module's open count)
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4CBE00 [imageCreate] -- ($a0 = width, $a1 = height, $a2 = depth) an image from its free list, without pixels or palette
// then the image plugins' constructors.
// 0x004CBE00 sub_4CBE00 -- 168 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CBE00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cbe00
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x30000;
    sd(ra, sp, 0x40);
    v0 = 0x960000;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a0 = 0x960000;
    lw(a2, gp, -17336);  // 0x7CE938 (the image module offset)
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = v1 | 0x18;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(a0, a2);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4CBE44u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s3 = v0;
    if (s3 == 0) {
        // 0x004cbe88
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004cbe58
        charge(ctx, 12);
        sw(s2, s3, image::kWidth);
        a0 = 0x780000;
        sw(s1, s3, image::kHeight);
        a0 = addiu(a0, -6512);  // &0x77E690 (the image plugin registry)
        sw(s0, s3, image::kDepth);
        a1 = s3;
        sw(zero, s3, image::kPixels);
        sw(zero, s3, image::kPalette);
        link(ctx, 0x4CBE78u);  // $ra first: the delay slot below depends on it
        sw(zero, s3, image::kFlags);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s3;
    }
    // 0x004cbe8c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4CBEB0 [imageDestroy] -- destroys an image: owned pixels freed (sub_4CC050), the plugin destructors, back to its free
// list; 1.
// 0x004CBEB0 sub_4CBEB0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CBEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cbeb0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, image::kFlags);
    v0 = v0 & 0x1;
    s0 = a0;
    if (v0 != 0) {
        // 0x004cbecc
        charge(ctx, 2);
        jal(ctx, 0x4CBECCu, gen::fn_sub_4CC050_004cc050);
    }
    // 0x004cbed4
    charge(ctx, 18);
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -6512);  // &0x77E690 (the image plugin registry)
    jal(ctx, 0x4CBEDCu, gen::fn_sub_4C6560_004c6560);
    lw(a0, gp, -17336);  // 0x7CE938 (the image module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    a1 = s0;
    jalr(ctx, 0x4CBF00u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4CC050 [imageFreePixels] -- frees an image's pixels (RwFree), clears pixels / palette and the owned flag; the image
// 0x004CC050 sub_4CC050 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CC050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cc050
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4CC068u);  // $ra = the return address
    lw(a0, a0, image::kPixels);
    call_ptr(ctx, jt);
    sw(zero, s0, image::kPixels);
    v1 = si(-2);
    sw(zero, s0, image::kPalette);
    v0 = s0;
    lw(a0, s0, image::kFlags);
    v1 = a0 & v1;
    sw(v1, s0, image::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4CC6B0 [imageGetScratch] -- the image module's scratch buffer (+4)
// 0x004CC6B0 sub_4CC6B0 -- 24 bytes; leaf frame (no stack)
void sub_4CC6B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28};
    // 0x004cc6b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17336);  // 0x7CE938 (the image module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(v0, v0, 4);
}


// sub_4CD750 [imageStreamRead] -- reads an image chunk: the 16-byte header, the image, its pixels and palette
// The header {width, height, depth, stride}; the pixels (sub_4CBF20) read row by row when the strides
// differ (the file's extra bytes skipped); the palette (4 << depth bytes below depth 9). 0 when there is
// no struct chunk.
// 0x004CD750 sub_4CD750 -- 484 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CD750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cd750
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    a1 = 1;
    sd(ra, sp, 0x70);
    a2 = addiu(sp, 0x9C);
    sq(s6, sp, 0x60);
    a3 = addiu(sp, 0x98);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4CD780u, gen::fn_sub_4C1600_004c1600);
    if (v0 != 0) {
        // 0x004cd798: the 16-byte header and the image record
        charge(ctx, 21);
        a0 = s0;
        a1 = addiu(sp, 0x80);
        a2 = 16;
        jal(ctx, 0x4CD7A0u, gen::fn_sub_4C5250_004c5250);
        lw(a0, gp, -17336);  // 0x7CE938 (the image module offset)
        v1 = 0x960000;
        v0 = 0x30000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        a1 = v0 | 0x18;
        s6 = addiu(sp, 0x84);
        v0 = 0x960000;
        lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
        lw(s1, s6, 0);
        v1 = addu(v1, a0);
        lw(s3, sp, 0x80);
        lw(a0, v1, 0);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4CD7D8u);  // $ra = the return address
        lw(s2, sp, 0x88);
        call_ptr(ctx, jt);
        s4 = v0;
        if (s4 == 0) {
            // 0x004cd8c8
            charge(ctx, 2);
            s4 = 0;
            backedge(ctx);
        } else {
            // 0x004cd7ec
            charge(ctx, 10);
            sw(s3, s4, image::kWidth);
            a0 = 0x780000;
            sw(s1, s4, image::kHeight);
            a0 = addiu(a0, -6512);  // &0x77E690 (the image plugin registry)
            sw(s2, s4, image::kDepth);
            a1 = s4;
            sw(zero, s4, image::kPixels);
            sw(zero, s4, image::kPalette);
            link(ctx, 0x4CD80Cu);  // $ra first: the delay slot below depends on it
            sw(zero, s4, image::kFlags);
            call(ctx, gen::fn_sub_4C64B0_004c64b0);
        }
        // 0x004cd814: the pixels: one read when the strides match
        charge(ctx, 7);
        a0 = s4;
        jal(ctx, 0x4CD814u, gen::fn_sub_4CBF20_004cbf20);
        s1 = addiu(sp, 0x8C);
        lw(s2, s4, image::kStride);
        lw(v0, s1, 0);
        if (s2 == v0) {
            // 0x004cd8d0
            charge(ctx, 7);
            lw(v0, s4, image::kHeight);
            mult(a2, v0, s2);
            lw(a1, s4, image::kPixels);
            a0 = s0;
            jal(ctx, 0x4CD8DCu, gen::fn_sub_4C5250_004c5250);
            backedge(ctx);
        } else {
            // 0x004cd830
            charge(ctx, 4);
            lw(v0, s6, 0);
            at = slt(0, v0);
            s5 = 0;
            if (at != 0) {
                // 0x004cd840: else row by row
                charge(ctx, 1);
                s3 = 0;
                for (;;) {
                    // 0x004cd844
                    charge(ctx, 4);
                    lw(a2, s1, 0);
                    at = slt(a2, s2);
                    if (at == 0) {
                        // 0x004cd870
                        charge(ctx, 10);
                        lw(v0, s4, image::kPixels);
                        a0 = s0;
                        a2 = s2;
                        a1 = addu(v0, s3);
                        jal(ctx, 0x4CD87Cu, gen::fn_sub_4C5250_004c5250);
                        lw(v0, s1, 0);
                        a0 = s0;
                        a1 = subu(v0, s2);
                        jal(ctx, 0x4CD88Cu, gen::fn_sub_4C5620_004c5620);
                    } else {
                        // 0x004cd854
                        charge(ctx, 6);
                        lw(v0, s4, image::kPixels);
                        a0 = s0;
                        a1 = addu(v0, s3);
                        jal(ctx, 0x4CD85Cu, gen::fn_sub_4C5250_004c5250);
                    }
                    // 0x004cd898
                    charge(ctx, 5);
                    lw(v0, s6, 0);
                    s5 = addiu(s5, 1);
                    v0 = slt(s5, v0);
                    s3 = addu(s3, s2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cd8ac
                charge(ctx, 1);
            }
        }
        // 0x004cd8b0: the palette (depth < 9)
        charge(ctx, 4);
        lw(v1, s4, image::kDepth);
        at = slti(v1, 9);
        if (at != 0) {
            // 0x004cd8ec
            charge(ctx, 8);
            lw(a1, s4, image::kPalette);
            v0 = 1;
            v0 = sllv(v0, v1);
            a0 = s0;
            a2 = sll(v0, 2);
            jal(ctx, 0x4CD8FCu, gen::fn_sub_4C5250_004c5250);
            backedge(ctx);
        }
        // 0x004cd8c0
        charge(ctx, 2);
        v0 = s4;
    } else {
        // 0x004cd790
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004cd90c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}


// sub_4D18C0 [objectHasFrameReleaseFrame] -- takes an object off its frame's object list (when it has a frame)
// 0x004D18C0 sub_4D18C0 -- 56 bytes; leaf frame (no stack)
void sub_4D18C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004d18c0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, objframe::kFrame);
    if (v1 != 0) {
        // 0x004d18d4
        charge(ctx, 7);
        lw(a1, a0, objframe::kLinkNext);
        lw(v1, a0, objframe::kLinkPrev);
        sw(a1, v1, 0);
        lw(a1, a0, objframe::kLinkPrev);
        lw(v1, a0, objframe::kLinkNext);
        sw(a1, v1, 4);
        backedge(ctx);
    }
    // 0x004d18cc
    charge(ctx, 2);
    // 0x004d18f0
    charge(ctx, 2);
}


// sub_4F23C0 [im3dSetTransformPipeline] -- sets the Im3D transform pipeline (0: the default); returns the one in use
// 0x004F23C0 sub_4F23C0 -- 104 bytes; leaf frame (no stack)
void sub_4F23C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004f23c0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004f23f4
        charge(ctx, 7);
        lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v1 = addu(v0, v1);
        lw(v0, v1, im3dmod::kDefTransform);
        if (v0 == 0) {
            // 0x004f2418
            charge(ctx, 2);
            sw(zero, v1, im3dmod::kTransform);
            backedge(ctx);
        } else {
            // 0x004f2410
            charge(ctx, 2);
            sw(v0, v1, im3dmod::kTransform);
            backedge(ctx);
        }
    } else {
        // 0x004f23c8
        charge(ctx, 5);
        lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(a0, v0, im3dmod::kTransform);
    }
    // 0x004f23dc
    charge(ctx, 6);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(v0, v0, im3dmod::kTransform);
    // 0x004f2420
    charge(ctx, 2);
}


// sub_4F2430 [im3dSetRenderPipeline] -- sets the Im3D render pipeline of a primitive type ($a1 = 1..6; $a0 = 0: the default); the one in use
// Another type: error 37, 0.
// 0x004F2430 sub_4F2430 -- 728 bytes; frame 0x20: ra sp+0x0
void sub_4F2430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2430
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x004f2530
        charge(ctx, 3);
        at = sltiu(a1, 7);
        if (at != 0) {
            // 0x004f253c: 0: the slot's default
            charge(ctx, 7);
            v1 = 0x7C0000;
            v0 = sll(a1, 2);
            v1 = addiu(v1, -12240);  // &0x7BD030 (the jump table of the getter path)
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x4F2558u:  // table[3]
                // 0x004f2558
                charge(ctx, 7);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v1 = addu(v0, v1);
                lw(v0, v1, im3dmod::kDefRender3);
                if (v0 == 0) {
                    // 0x004f26cc
                    charge(ctx, 2);
                    sw(zero, v1, im3dmod::kRender3);
                    backedge(ctx);
                } else {
                    // 0x004f2574
                    charge(ctx, 1);
                    sw(v0, v1, im3dmod::kRender3);
                }
                // 0x004f2578
                charge(ctx, 6);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                lw(v0, v0, im3dmod::kRender3);
                break;
            case 0x4F2590u:  // table[5]
                // 0x004f2590
                charge(ctx, 7);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v1 = addu(v0, v1);
                lw(v0, v1, im3dmod::kDefRender5);
                if (v0 == 0) {
                    // 0x004f26d4
                    charge(ctx, 2);
                    sw(zero, v1, im3dmod::kRender5);
                    backedge(ctx);
                } else {
                    // 0x004f25ac
                    charge(ctx, 1);
                    sw(v0, v1, im3dmod::kRender5);
                }
                // 0x004f25b0
                charge(ctx, 6);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                lw(v0, v0, im3dmod::kRender5);
                break;
            case 0x4F25C8u:  // table[4]
                // 0x004f25c8
                charge(ctx, 7);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v1 = addu(v0, v1);
                lw(v0, v1, im3dmod::kDefRender4);
                if (v0 == 0) {
                    // 0x004f26dc
                    charge(ctx, 2);
                    sw(zero, v1, im3dmod::kRender4);
                    backedge(ctx);
                } else {
                    // 0x004f25e4
                    charge(ctx, 1);
                    sw(v0, v1, im3dmod::kRender4);
                }
                // 0x004f25e8
                charge(ctx, 6);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                lw(v0, v0, im3dmod::kDefRender4);
                break;
            case 0x4F2600u:  // table[1]
                // 0x004f2600
                charge(ctx, 7);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v1 = addu(v0, v1);
                lw(v0, v1, im3dmod::kDefRender1);
                if (v0 == 0) {
                    // 0x004f26e4
                    charge(ctx, 2);
                    sw(zero, v1, im3dmod::kRender1);
                    backedge(ctx);
                } else {
                    // 0x004f261c
                    charge(ctx, 1);
                    sw(v0, v1, im3dmod::kRender1);
                }
                // 0x004f2620
                charge(ctx, 6);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                lw(v0, v0, im3dmod::kDefRender1);
                break;
            case 0x4F2638u:  // table[2]
                // 0x004f2638
                charge(ctx, 7);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v1 = addu(v0, v1);
                lw(v0, v1, im3dmod::kDefRender2);
                if (v0 == 0) {
                    // 0x004f26ec
                    charge(ctx, 2);
                    sw(zero, v1, im3dmod::kRender2);
                    backedge(ctx);
                } else {
                    // 0x004f2654
                    charge(ctx, 1);
                    sw(v0, v1, im3dmod::kRender2);
                }
                // 0x004f2658
                charge(ctx, 6);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                lw(v0, v0, im3dmod::kDefRender2);
                break;
            case 0x4F2670u:  // table[6]
                // 0x004f2670
                charge(ctx, 7);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v1 = addu(v0, v1);
                lw(v0, v1, im3dmod::kDefRender6);
                if (v0 == 0) {
                    // 0x004f26f4
                    charge(ctx, 2);
                    sw(zero, v1, im3dmod::kRender6);
                    backedge(ctx);
                } else {
                    // 0x004f268c
                    charge(ctx, 1);
                    sw(v0, v1, im3dmod::kRender6);
                }
                // 0x004f2690
                charge(ctx, 6);
                lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                lw(v0, v0, im3dmod::kDefRender6);
                break;
            case 0x4F26A8u:  // table[0]
            L_004f26a8:
                charge(ctx, 9);
                v0 = 1;
                a0 = 37;
                link(ctx, 0x4F26B0u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x10);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x14);
                a0 = addiu(sp, 0x10);
                jal(ctx, 0x4F26BCu, gen::fn_sub_4C1C50_004c1c50);
                backedge(ctx);
            L_004f2528:
                charge(ctx, 2);
                v0 = 0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x004f26fc (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
        goto L_004f26a8;
    }
    // 0x004f243c
    charge(ctx, 3);
    at = sltiu(a1, 7);
    if (at != 0) {
        // 0x004f2448: set: the slot of the primitive type
        charge(ctx, 7);
        v1 = 0x7C0000;
        v0 = sll(a1, 2);
        v1 = addiu(v1, -12208);  // &0x7BD050 (the jump table of the setter path)
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x4F2464u:  // table[3]
            // 0x004f2464
            charge(ctx, 7);
            lw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = a0;
            v1 = addu(v1, a1);
            sw(a0, v1, im3dmod::kRender3);
            break;
        case 0x4F2480u:  // table[5]
            // 0x004f2480
            charge(ctx, 7);
            lw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = a0;
            v1 = addu(v1, a1);
            sw(a0, v1, im3dmod::kRender5);
            break;
        case 0x4F249Cu:  // table[4]
            // 0x004f249c
            charge(ctx, 7);
            lw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = a0;
            v1 = addu(v1, a1);
            sw(a0, v1, im3dmod::kRender4);
            break;
        case 0x4F24B8u:  // table[1]
            // 0x004f24b8
            charge(ctx, 7);
            lw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = a0;
            v1 = addu(v1, a1);
            sw(a0, v1, im3dmod::kRender1);
            break;
        case 0x4F24D4u:  // table[2]
            // 0x004f24d4
            charge(ctx, 7);
            lw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = a0;
            v1 = addu(v1, a1);
            sw(a0, v1, im3dmod::kRender2);
            break;
        case 0x4F24F0u:  // table[6]
            // 0x004f24f0
            charge(ctx, 7);
            lw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = a0;
            v1 = addu(v1, a1);
            sw(a0, v1, im3dmod::kRender6);
            break;
        case 0x4F250Cu:  // table[0]
        L_004f250c:
            charge(ctx, 7);
            v0 = 1;
            a0 = 37;
            link(ctx, 0x4F2514u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x18);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x1C);
            a0 = addiu(sp, 0x18);
            jal(ctx, 0x4F2520u, gen::fn_sub_4C1C50_004c1c50);
            goto L_004f2528;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x004f26fc (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    goto L_004f250c;
}


// sub_4F28E0 [cameraBeginUpdateHook] -- an empty hook called at the end of CameraBeginUpdate
// 0x004F28E0 sub_4F28E0 -- 8 bytes; leaf frame (no stack)
void sub_4F28E0(EEContext& ctx) {
    using namespace hg;
    // 0x004f28e0
    enter(ctx, 2);  // entry check point + this block's cycles
}


}  // namespace p3fes::game
