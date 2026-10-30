// Slice fcl, part 1 of 3 (game/include/p3fes/game/fcl.h): fclMisc.c (0x3C77A0-0x3CF158) -- the facility message
// window helpers, the boot-time "MsgAssist" service, the persona-status ("psStatus") accessors and the persona model
// ("psModel") -- the bank manager's slot helpers (fclBankManager.c), and the helpers they need that no slice had taken:
// the nmlist object create / remove / clear (nmlist.c, left by nm_message when the RW heap was a skip reason), the two
// g_data colour lookups and sub_20D650.
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass adds the role of each function above it (names in [brackets] are proposals, ADR-0009) and
// named record offsets (fcl.h, namespace fcl: constexpr values equal to the instructions' offsets); `// 0x00xxxxxx`
// names the original basic block a C++ block comes from. It changes no statement.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/fcl.h"

namespace p3fes::recomp_gen {
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_fclMisc_CreateMsgAssistTask_003c88d0(p3fes::EEContext&);
void fn_fclMisc_UpdatePsStatusDrawHighTask_003ca660(p3fes::EEContext&);
void fn_fclMisc_UpdatePsStatusDrawLowTask_003ca610(p3fes::EEContext&);
void fn_frFontTagGetParam0_003af360(p3fes::EEContext&);
void fn_frFontTagGetParam1_003af370(p3fes::EEContext&);
void fn_frFontTagGetParam2_003af380(p3fes::EEContext&);
void fn_frFontTagGetParam3_003af390(p3fes::EEContext&);
void fn_itfMesMngGetSelectWord84_003a2750(p3fes::EEContext&);
void fn_itfMesMngGetSelection_003a2830(p3fes::EEContext&);
void fn_itfMesMngSetTextPosition_003a3ce0(p3fes::EEContext&);
void fn_itfMesMngSetWindowOffset_003a6a80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);
void fn_nmListUnlink_003c4820(p3fes::EEContext&);
void fn_nullsub_122_003ccc30(p3fes::EEContext&);
void fn_nullsub_123_003cd0a0(p3fes::EEContext&);
void fn_nullsub_124_003cd590(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_16BC80_0016bc80(p3fes::EEContext&);
void fn_sub_16BDB0_0016bdb0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_20D650_0020d650(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3A8650_003a8650(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C4A90_003c4a90(p3fes::EEContext&);
void fn_sub_3C78D0_003c78d0(p3fes::EEContext&);
void fn_sub_3C7D50_003c7d50(p3fes::EEContext&);
void fn_sub_3C7D60_003c7d60(p3fes::EEContext&);
void fn_sub_3C8400_003c8400(p3fes::EEContext&);
void fn_sub_3C8770_003c8770(p3fes::EEContext&);
void fn_sub_3C8810_003c8810(p3fes::EEContext&);
void fn_sub_3C8D80_003c8d80(p3fes::EEContext&);
void fn_sub_3C8DA0_003c8da0(p3fes::EEContext&);
void fn_sub_3C8DC0_003c8dc0(p3fes::EEContext&);
void fn_sub_3C8DD0_003c8dd0(p3fes::EEContext&);
void fn_sub_3C8DE0_003c8de0(p3fes::EEContext&);
void fn_sub_3C8EA0_003c8ea0(p3fes::EEContext&);
void fn_sub_3C8EC0_003c8ec0(p3fes::EEContext&);
void fn_sub_3C8F20_003c8f20(p3fes::EEContext&);
void fn_sub_3C8F40_003c8f40(p3fes::EEContext&);
void fn_sub_3C9340_003c9340(p3fes::EEContext&);
void fn_sub_3C9570_003c9570(p3fes::EEContext&);
void fn_sub_3C9840_003c9840(p3fes::EEContext&);
void fn_sub_3C9B00_003c9b00(p3fes::EEContext&);
void fn_sub_3C9BA0_003c9ba0(p3fes::EEContext&);
void fn_sub_3C9C10_003c9c10(p3fes::EEContext&);
void fn_sub_3C9CD0_003c9cd0(p3fes::EEContext&);
void fn_sub_3C9D80_003c9d80(p3fes::EEContext&);
void fn_sub_3C9E00_003c9e00(p3fes::EEContext&);
void fn_sub_3C9E30_003c9e30(p3fes::EEContext&);
void fn_sub_3C9E70_003c9e70(p3fes::EEContext&);
void fn_sub_3C9EE0_003c9ee0(p3fes::EEContext&);
void fn_sub_3C9F10_003c9f10(p3fes::EEContext&);
void fn_sub_3C9F60_003c9f60(p3fes::EEContext&);
void fn_sub_3C9FB0_003c9fb0(p3fes::EEContext&);
void fn_sub_3CDA60_003cda60(p3fes::EEContext&);
void fn_sub_3CDBA0_003cdba0(p3fes::EEContext&);
void fn_sub_3CDC80_003cdc80(p3fes::EEContext&);
void fn_sub_3CDCD0_003cdcd0(p3fes::EEContext&);
void fn_sub_3CDD80_003cdd80(p3fes::EEContext&);
void fn_sub_3CDE00_003cde00(p3fes::EEContext&);
void fn_sub_3CDE70_003cde70(p3fes::EEContext&);
void fn_sub_3CDEE0_003cdee0(p3fes::EEContext&);
void fn_sub_3CDF40_003cdf40(p3fes::EEContext&);
void fn_sub_3CE060_003ce060(p3fes::EEContext&);
void fn_sub_3CE180_003ce180(p3fes::EEContext&);
void fn_sub_3CF520_003cf520(p3fes::EEContext&);
void fn_sub_3CF8F0_003cf8f0(p3fes::EEContext&);
void fn_sub_3CF960_003cf960(p3fes::EEContext&);
void fn_sub_3CFAC0_003cfac0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fcl;  // the named record offsets (fcl.h)

// 0x0016BC80 sub_16BC80 -- 304 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gDataGetColourA] ($a0 table, $a1 entry, $a2 float[4] out) The first RGBA word (+20) of entry $a1 of table $a0 in
// the g_data colour set (gp slot 0x7CDFB0: 16-byte tables, +8 their 32-byte entries) as four floats 0..1 (byte / 255).
// K_Assert g_data.c:165 when the set is not loaded (retail continues and reads through null). Callers: the psModel
// creator sub_3CDA60 and its update sub_3CE2A0.
void sub_16BC80(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0016bc80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    lw(v1, gp, -19776);  // 0x7CDFB0
    if (v1 == 0) {
        // 0x0016bcac
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 165;
        jal(ctx, 0x16BCB8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0016bcc0
    charge(ctx, 60);
    v1 = s2 & 0xFFFF;
    a0 = sll(v1, 5);
    v1 = s1 & 0xFFFF;
    v1 = sll(v1, 4);
    lw(a1, gp, -19776);  // 0x7CDFB0
    a1 = addu(v1, a1);
    lw(a1, a1, 8);
    a1 = addu(a0, a1);
    lw(a1, a1, 20);
    a1 = sra(a1, 24);
    a1 = a1 & 0xFF;
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    a1 = 0x437F0000;
    mtc1(a1, f1);
    div_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lw(a1, gp, -19776);  // 0x7CDFB0
    a1 = addu(v1, a1);
    lw(a1, a1, 8);
    a1 = addu(a0, a1);
    lw(a1, a1, 20);
    a1 = sra(a1, 16);
    a1 = a1 & 0xFF;
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lw(a1, gp, -19776);  // 0x7CDFB0
    a1 = addu(v1, a1);
    lw(a1, a1, 8);
    a1 = addu(a0, a1);
    lw(a1, a1, 20);
    a1 = sra(a1, 8);
    a1 = a1 & 0xFF;
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f0, f1);
    swc1(f0, s0, 8);
    lw(a1, gp, -19776);  // 0x7CDFB0
    v1 = addu(v1, a1);
    lw(v1, v1, 8);
    v1 = addu(a0, v1);
    lbu(v1, v1, 20);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f0, f1);
    swc1(f0, s0, 12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0016BDB0 sub_16BDB0 -- 304 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gDataGetColourB] As sub_16BC80 for the second RGBA word (+24) of the entry; K_Assert g_data.c:175.
void sub_16BDB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0016bdb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    lw(v1, gp, -19776);  // 0x7CDFB0
    if (v1 == 0) {
        // 0x0016bddc
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 175;
        jal(ctx, 0x16BDE8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0016bdf0
    charge(ctx, 60);
    v1 = s2 & 0xFFFF;
    a0 = sll(v1, 5);
    v1 = s1 & 0xFFFF;
    v1 = sll(v1, 4);
    lw(a1, gp, -19776);  // 0x7CDFB0
    a1 = addu(v1, a1);
    lw(a1, a1, 8);
    a1 = addu(a0, a1);
    lw(a1, a1, 24);
    a1 = sra(a1, 24);
    a1 = a1 & 0xFF;
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    a1 = 0x437F0000;
    mtc1(a1, f1);
    div_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lw(a1, gp, -19776);  // 0x7CDFB0
    a1 = addu(v1, a1);
    lw(a1, a1, 8);
    a1 = addu(a0, a1);
    lw(a1, a1, 24);
    a1 = sra(a1, 16);
    a1 = a1 & 0xFF;
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lw(a1, gp, -19776);  // 0x7CDFB0
    a1 = addu(v1, a1);
    lw(a1, a1, 8);
    a1 = addu(a0, a1);
    lw(a1, a1, 24);
    a1 = sra(a1, 8);
    a1 = a1 & 0xFF;
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f0, f1);
    swc1(f0, s0, 8);
    lw(a1, gp, -19776);  // 0x7CDFB0
    v1 = addu(v1, a1);
    lw(v1, v1, 8);
    v1 = addu(a0, v1);
    lbu(v1, v1, 24);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f0, f1);
    swc1(f0, s0, 12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0020D650 sub_20D650 -- 32 bytes; leaf frame (no stack)
// [FrameSetTranslation] Copies the vector $a1 (3 floats) to $a0 +32 / +36 / +40 (the position row of a 16-byte-aligned
// frame matrix). Callers: the battle result / shuffle cameras and the fusion cut-in's placement commands.
void sub_20D650(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0020d650
    enter(ctx, 8);  // entry check point + this block's cycles
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, a0, 32);
    swc1(f1, a0, 36);
    swc1(f0, a0, 40);
}

// 0x003C44D0 sub_3C44D0 -- 288 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [nmListObjCreate] ($a0 payload size, $a1 on-insert, $a2 on-remove, $a3 remove filter) RwMalloc(40 + size) through
// the RW slot 0x960178 (K_Assert nmlist.c:55 on failure, retail continues), zeroed; +36 = the payload (obj + 40) when
// size != 0, +32 = size, and the three callbacks (+20 / +24 / +28, the defaults sub_3C4400 / sub_3C4410 / sub_3C4420
// when 0). Returns the object (nm_message.h documents the layout).
void sub_3C44D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c44d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = addiu(s5, kNmObjHeaderSize);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3C4514u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x003c4528
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15848);  // "nmlist.c"
        a1 = 55;
        jal(ctx, 0x3C4534u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c453c
    charge(ctx, 7);
    a0 = s0;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x3C4548u, gen::fn_memset_00521408);
    if (s5 != 0) {
        // 0x003c4558
        charge(ctx, 2);
        v0 = addiu(s0, kNmObjHeaderSize);
        sw(v0, s0, kNmObjPayload);
    }
    // 0x003c4560
    charge(ctx, 3);
    sw(s5, s0, kNmObjSize);
    if (s4 == 0) {
        // 0x003c4578
        charge(ctx, 3);
        v0 = 0x3C0000;
        v0 = addiu(v0, 17408);  // &sub_3C4400
        sw(v0, s0, kNmObjOnInsert);
    } else {
        // 0x003c456c
        charge(ctx, 3);
        sw(s4, s0, kNmObjOnInsert);
    }
    // 0x003c4584
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x003c4598
        charge(ctx, 3);
        v0 = 0x3C0000;
        v0 = addiu(v0, 17424);  // &sub_3C4410
        sw(v0, s0, kNmObjOnRemove);
    } else {
        // 0x003c458c
        charge(ctx, 3);
        sw(s3, s0, kNmObjOnRemove);
    }
    // 0x003c45a4
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x003c45b8
        charge(ctx, 3);
        v0 = 0x3C0000;
        v0 = addiu(v0, 17440);  // &sub_3C4420
        sw(v0, s0, kNmObjFilter);
    } else {
        // 0x003c45ac
        charge(ctx, 3);
        sw(s2, s0, kNmObjFilter);
    }
    // 0x003c45c4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003C49E0 sub_3C49E0 -- 176 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [nmListRemove] ($a0 object, $a1 its list header (object + 4), $a2 node) Unlinks the node (nmListUnlink), moves the
// cursor to the returned neighbour when it pointed at the node, calls the object's on-remove callback (+24, jalr) and,
// for a non-null node, clears it (memset of its +8 size) and frees it through the RW slot 0x96017C. Returns the
// neighbour nmListUnlink gave.
void sub_3C49E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c49e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x3C4A0Cu, gen::fn_nmListUnlink_003c4820);
    s0 = v0;
    lw(v0, s2, kNmListCursor);
    if (s1 == v0) {
        // 0x003c4a24
        charge(ctx, 1);
        sw(s0, s2, kNmListCursor);
    }
    // 0x003c4a28
    charge(ctx, 7);
    a0 = s3;
    a1 = s1;
    lw(v0, s3, kNmObjOnRemove);
    jalr(ctx, 0x3C4A34u, v0.u());
    if (s1 != 0) {
        // 0x003c4a44
        charge(ctx, 10);
        a0 = s1;
        a1 = 0;
        lw(a2, s1, kNmNodeSize);
        jal(ctx, 0x3C4A50u, gen::fn_memset_00521408);
        a0 = s1;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x3C4A64u, v0.u());
    }
    // 0x003c4a6c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003C4A90 sub_3C4A90 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [nmListClear] ($a0 object, $a1 its list header) For every node from the head: on-remove callback (+24), memset of
// its size, RW free; then head / tail / cursor = 0 and the u16 count = 0. Nothing when either argument is null.
void sub_3C4A90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4a90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 != 0) {
        // 0x003c4ab8
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003c4ac0
            charge(ctx, 3);
            lw(s3, s0, kNmListHead);
            for (;;) {
                // 0x003c4b18
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003c4acc
                charge(ctx, 8);
                lw(s2, s3, kNmNodeNext);
                a0 = s1;
                a1 = s3;
                lw(v0, s1, kNmObjOnRemove);
                jalr(ctx, 0x3C4ADCu, v0.u());
                if (s3 != 0) {
                    // 0x003c4aec
                    charge(ctx, 10);
                    a0 = s3;
                    a1 = 0;
                    lw(a2, s3, kNmNodeSize);
                    jal(ctx, 0x3C4AF8u, gen::fn_memset_00521408);
                    a0 = s3;
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    jalr(ctx, 0x3C4B0Cu, v0.u());
                }
                // 0x003c4b14
                charge(ctx, 1);
                s3 = s2;
            }
            // 0x003c4b20
            charge(ctx, 4);
            sh(zero, s0, kNmListCount);
            sw(zero, s0, kNmListCursor);
            sw(zero, s0, kNmListTail);
            sw(zero, s0, kNmListHead);
        }
    }
    // 0x003c4b30 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003C78D0 sub_3C78D0 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [msgWinPollSelection] The facility message window 0x95BE90 (sub_3C7D50): when it has a handle (+0 >= 0) and
// itfMesMngGetSelectWord84 reports a choice (>= 0), stores the selection (itfMesMngGetSelection, or -1 when the handle
// went away) in +13 and returns 1; else 0. Callers: the shuffle root, sub_215FC0, sub_45DF00.
void sub_3C78D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c78d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C78DCu, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 != 0) {
        // 0x003c78fc
        charge(ctx, 3);
        lw(a0, s0, kMsgWinHandle);
        if (i64(a0) >= 0) {
            // 0x003c7914
            charge(ctx, 4);
            jal(ctx, 0x3C7914u, gen::fn_itfMesMngGetSelectWord84_003a2750);
            if (i64(v0) >= 0) {
                // 0x003c7930
                charge(ctx, 4);
                jal(ctx, 0x3C7930u, gen::fn_sub_3C7D50_003c7d50);
                if (v0 != 0) {
                    // 0x003c794c
                    charge(ctx, 3);
                    lw(a0, v0, kMsgWinHandle);
                    if (i64(a0) >= 0) {
                        // 0x003c7964
                        charge(ctx, 2);
                        jal(ctx, 0x3C7964u, gen::fn_itfMesMngGetSelection_003a2830);
                    } else {
                        // 0x003c7958
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x003c7940
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                // 0x003c796c
                charge(ctx, 2);
                sb(v0, s0, kMsgWinSelection);
                v0 = 1;
            } else {
                // 0x003c7924
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003c7908
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c78f0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c7974 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C7D50 sub_3C7D50 -- 16 bytes; leaf frame (no stack)
// [msgWinGet] The facility message-window record 0x95BE90 (+0 the itfMesMng handle, +4 s8 state, +5 s8 hidden, +13 s8
// the last selection).
void sub_3C7D50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c7d50
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -16752);  // &0x95BE90
}

// 0x003C7D60 sub_3C7D60 -- 28 bytes; leaf frame (no stack)
// [fclMiscTableWord] The word $a0 of table 0x6A3E50. Callers: sub_202A10, sub_203410, sub_402800.
void sub_3C7D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003c7d60
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 15952);  // &0x6A3E50
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x003C8400 sub_3C8400 -- 332 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [msgAssistSlotStart] ($a0 MsgAssist work, $a1 slot 0..11; K_Assert fclMisc.c:918 / 919 otherwise) Unless the slot
// (+28 + 12 i) is already running (flag 2) or queued (a node of the slot list +24 whose payload +4 is $a1), records
// the index in the slot (+4) and appends a node to the slot list whose payload is the slot (K_Assert nmlist.h:80 on
// failure); returns 1. Otherwise clears the slot's flag 4 (a pending stop) and returns 0.
void sub_3C8400(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8400
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    if (s2 == 0) {
        // 0x003c8424
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 918;
        jal(ctx, 0x3C8430u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c8438
    charge(ctx, 2);
    if (i64(s1) >= 0) {
        // 0x003c8440
        charge(ctx, 3);
        at = slti(s1, 12);
        if (at == 0) {
            goto L_003c844c;
        }
        goto L_003c8460;
    }
L_003c844c:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15896);  // "fclMisc.c"
    a1 = 919;
    jal(ctx, 0x3C8458u, gen::fn_sub_19D3F0_0019d3f0);
L_003c8460:
    charge(ctx, 9);
    v0 = sll(s1, 1);
    v0 = addu(v0, s1);
    v0 = sll(v0, 2);
    v0 = addu(s2, v0);
    s0 = addiu(v0, kMaSlots);
    lw(v1, v0, kMaSlots);
    v0 = v1 & 0x2;
    if (v0 == 0) {
        // 0x003c8484: is the slot already queued? (search the slot list)
        charge(ctx, 4);
        lw(v0, s2, kMaSlotList);
        lw(a0, v0, kNmObjHead);
        for (;;) {
            // 0x003c84b0
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c8494
            charge(ctx, 4);
            lw(a1, a0, kNmNodePayload);
            lw(v0, a1, kMaSlotIndex);
            if (v0 == s1) {
                goto L_003c84a4_8;
            }
            // 0x003c84ac
            charge(ctx, 1);
            lw(a0, a0, kNmNodeNext);
        }
        // 0x003c84b8
        charge(ctx, 1);
        a1 = 0;
    L_003c84bc:
        charge(ctx, 2);
        if (a1 != 0) {
            goto L_003c8510;
        }
        // 0x003c84c4: queue it: index + a slot-list node
        charge(ctx, 10);
        sw(s1, s0, kMaSlotIndex);
        lw(a0, s2, kMaSlotList);
        lhu(v0, a0, kNmObjCount);
        a1 = addiu(v0, 1);
        a2 = 0;
        jal(ctx, 0x3C84D8u, gen::fn_nmListAppendNew_003c4910);
        s1 = v0;
        if (s1 == 0) {
            // 0x003c84ec
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, -19240);  // "nmlist.h"
            a1 = 80;
            jal(ctx, 0x3C84F8u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003c8500
        charge(ctx, 4);
        sw(s0, s1, kNmNodePayload);
        v0 = 1;
        // 0x003c8530 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003c8510:
    charge(ctx, 3);
    v0 = v1 & 0x4;
    if (v0 != 0) {
        // 0x003c851c: running or queued: drop a pending stop (flag 4)
        charge(ctx, 4);
        lw(v1, s0, kMaSlotFlags);
        v0 = si(-5);
        v0 = v1 & v0;
        sw(v0, s0, kMaSlotFlags);
    }
    // 0x003c852c
    charge(ctx, 1);
    v0 = 0;
    // 0x003c8530 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003c84a4_8:
    charge(ctx, 2);
    goto L_003c84bc;
}

// 0x003C8770 sub_3C8770 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [msgAssistSlotStop] ($a0 work, $a1 slot 0..11; K_Assert fclMisc.c:1003 / 1004) Sets flag 4 (stop) on the slot.
// Returns 0.
void sub_3C8770(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8770
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x003c8790
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 1003;
        jal(ctx, 0x3C879Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c87a4
    charge(ctx, 2);
    if (i64(s0) >= 0) {
        // 0x003c87ac
        charge(ctx, 3);
        at = slti(s0, 12);
        if (at == 0) {
            goto L_003c87b8;
        }
        // 0x003c87cc (the shared epilogue, written out on this path)
        charge(ctx, 14);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v1 = addu(s1, v0);
        lw(v0, v1, kMaSlots);
        v0 = v0 | 0x4;
        sw(v0, v1, kMaSlots);
        v0 = 0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003c87b8:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15896);  // "fclMisc.c"
    a1 = 1004;
    jal(ctx, 0x3C87C4u, gen::fn_sub_19D3F0_0019d3f0);
    // 0x003c87cc (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v1 = addu(s1, v0);
    lw(v0, v1, kMaSlots);
    v0 = v0 | 0x4;
    sw(v0, v1, kMaSlots);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C8810 sub_3C8810 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [msgAssistPurge] ($a0 work) Removes (sub_3C49E0) every node of the slot list (+24) whose slot has no index word (+8
// == 0), then every node of the request list (the work's own object, +0) whose request is not flagged 2 (+4). Returns
// 0. Callers: the MsgAssist update and sub_3C8F40.
void sub_3C8810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8810
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, kMaSlotList);
    lw(a2, v0, kNmObjHead);
    for (;;) {
        // 0x003c8860
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c8830
        charge(ctx, 4);
        lw(v0, a2, kNmNodePayload);
        lw(v0, v0, kMaSlotWord8);
        if (v0 != 0) {
            // 0x003c885c
            charge(ctx, 1);
            lw(a2, a2, kNmNodeNext);
        } else {
            // 0x003c8840
            charge(ctx, 7);
            lw(a0, s0, kMaSlotList);
            a1 = addiu(a0, kNmObjList);
            jal(ctx, 0x3C8848u, gen::fn_sub_3C49E0_003c49e0);
            a2 = v0;
        }
    }
    // 0x003c8868
    charge(ctx, 4);
    lw(v0, s0, kMaRequests);
    lw(a2, v0, kNmObjHead);
    for (;;) {
        // 0x003c88ac
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c8878
        charge(ctx, 5);
        lw(v0, a2, kNmNodePayload);
        lw(v0, v0, kMaReqFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x003c88a8
            charge(ctx, 1);
            lw(a2, a2, kNmNodeNext);
        } else {
            // 0x003c888c
            charge(ctx, 7);
            lw(a0, s0, kMaRequests);
            a1 = addiu(a0, kNmObjList);
            jal(ctx, 0x3C8894u, gen::fn_sub_3C49E0_003c49e0);
            a2 = v0;
        }
    }
    // 0x003c88b4
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C88D0 fclMisc_CreateMsgAssistTask -- 208 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclMisc_CreateMsgAssistTask] Creates the "MsgAssist" task (priority 6335, update fclMisc_UpdateMsgAssistTask, no
// work), the boot-time message-assist service (called once from frFontSystemStart): its work is the payload of a
// 160-byte nm list object whose nodes are 48-byte assist requests (work +0 = that object), with a 12-byte-payload slot
// list at +24 and flag 1; the work goes to the gp slot 0x7CE67C. Also resets the facility message record 0x95BE80 (+0
// / +8 = -1, +4 / +5 = 0, +12 / +13 = 1).
void fclMisc_CreateMsgAssistTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c88d0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, -16768);  // &0x95BE80
    a0 = 160;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3C88F8u, gen::fn_sub_3C44D0_003c44d0);
    lw(s1, v0, kNmObjPayload);
    sw(v0, s1, kMaRequests);
    a0 = 12;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3C8918u, gen::fn_sub_3C44D0_003c44d0);
    sw(v0, s1, kMaSlotList);
    lw(v0, s1, kMaFlags);
    v0 = v0 | 0x1;
    sw(v0, s1, kMaFlags);
    sw(s1, gp, kGpMsgAssist);  // 0x7CE67C
    v0 = s0;
    if (v0 != 0) {
        // 0x003c8940: the facility message record's defaults
        charge(ctx, 8);
        v0 = si(-1);
        sw(v0, s0, 0);
        sb(zero, s0, 4);
        sb(zero, s0, 5);
        sw(v0, s0, 8);
        v0 = 1;
        sb(v0, s0, 12);
        sb(v0, s0, 13);
    }
    // 0x003c8960: the "MsgAssist" task
    charge(ctx, 16);
    a0 = 0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 16224);  // "MsgAssist"
    a2 = 6335;
    a3 = 0x3D0000;
    a3 = addiu(a3, -30304);  // &fclMisc_UpdateMsgAssistTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3C8980u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C8D80 sub_3C8D80 -- 28 bytes; leaf frame (no stack)
// [msgAssistSlotsIdle] 1 when the MsgAssist slot list (0x7CE67C -> +24) has no node, else 0.
void sub_3C8D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003c8d80
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, gp, kGpMsgAssist);  // 0x7CE67C
    lw(v0, v0, kMaSlotList);
    lw(v0, v0, kNmObjHead);
    // xor v0: a 64-bit move to itself (no effect)
    v0 = sltiu(v0, 1);
}

// 0x003C8DA0 sub_3C8DA0 -- 24 bytes; leaf frame (no stack)
// [msgAssistOrMask] MsgAssist work +20 |= $a0. Callers: sub_1C3CD0, sub_2DBEB0 (field / event code).
void sub_3C8DA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003c8da0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a1, gp, kGpMsgAssist);  // 0x7CE67C
    lw(v1, a1, kMaMask);
    v1 = v1 | a0;
    sw(v1, a1, kMaMask);
}

// 0x003C8DC0 sub_3C8DC0 -- 16 bytes; leaf frame (no stack)
// [msgAssistSetMask] MsgAssist work +20 = $a0.
void sub_3C8DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x003c8dc0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, gp, kGpMsgAssist);  // 0x7CE67C
    sw(a0, v1, kMaMask);
}

// 0x003C8DD0 sub_3C8DD0 -- 16 bytes; leaf frame (no stack)
// [msgAssistSetOwner] MsgAssist work +12 = $a0 (the owner new requests record, sub_3C8DE0).
void sub_3C8DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x003c8dd0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, gp, kGpMsgAssist);  // 0x7CE67C
    sw(a0, v1, kMaOwner);
}

// 0x003C8DE0 sub_3C8DE0 -- 184 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [msgAssistRequest] ($a0 key, $a1 a, $a2 b, $a3 s16 c) Appends a 48-byte request to the MsgAssist request list (key =
// count + 1): payload +0 the node, +44 key, +32 a, +36 b, +40 the current owner (+12; K_Assert fclMisc.c:1198 when
// none), +14 c. Returns 0. Callers: sub_1C3CD0, sub_2DAD00.
void sub_3C8DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8de0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    lw(s5, gp, kGpMsgAssist);  // 0x7CE67C
    lw(v0, s5, kMaOwner);
    if (v0 == 0) {
        // 0x003c8e20
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 1198;
        jal(ctx, 0x3C8E2Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c8e34
    charge(ctx, 25);
    lw(s4, s5, kMaOwner);
    lw(a0, s5, kMaRequests);
    lhu(v0, a0, kNmObjCount);
    a1 = addiu(v0, 1);
    a2 = 48;
    jal(ctx, 0x3C8E48u, gen::fn_nmListAppendNew_003c4910);
    lw(v1, v0, kNmNodePayload);
    sw(v0, v1, kMaReqNode);
    sw(s3, v1, kMaReqKey);
    sw(s2, v1, kMaReqA);
    sw(s1, v1, kMaReqB);
    sw(s4, v1, kMaReqOwner);
    sh(s0, v1, kMaReqC);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003C8EA0 sub_3C8EA0 -- 20 bytes; leaf frame (no stack)
// [msgAssistRequestCount] The u16 node count of the MsgAssist request list.
void sub_3C8EA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003c8ea0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, kGpMsgAssist);  // 0x7CE67C
    lw(v0, v0, kMaRequests);
    lhu(v0, v0, kNmObjCount);
}

// 0x003C8EC0 sub_3C8EC0 -- 84 bytes; leaf frame (no stack)
// [msgAssistHasRequest] 1 when a request with key $a0 (+44) and a == $a1 (+32) is queued, else 0. Caller: sub_1C3D60.
void sub_3C8EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x003c8ec0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, kGpMsgAssist);  // 0x7CE67C
    lw(v0, v0, kMaRequests);
    lw(a2, v0, kNmObjHead);
    for (;;) {
        // 0x003c8f00
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c8ed4
        charge(ctx, 4);
        lw(v1, a2, kNmNodePayload);
        lw(v0, v1, kMaReqKey);
        if (v0 == a0) {
            // 0x003c8ee4
            charge(ctx, 3);
            lw(v0, v1, kMaReqA);
            if (v0 != a1) {
                goto L_003c8efc;
            }
            goto L_003c8ef0_3;
        }
    L_003c8efc:
        charge(ctx, 1);
        lw(a2, a2, kNmNodeNext);
    }
    // 0x003c8f08
    charge(ctx, 1);
    v0 = 0;
    // 0x003c8f0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003c8ef0_3:
    charge(ctx, 3);
    v0 = 1;
    // 0x003c8f0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003C8F20 sub_3C8F20 -- 24 bytes; leaf frame (no stack)
// [msgAssistFlag2] MsgAssist work +4 |= 2. Callers: sub_1C3DC0, K_FldEvent_UpdateFldEventTask, sub_2DB980.
void sub_3C8F20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x003c8f20
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, gp, kGpMsgAssist);  // 0x7CE67C
    lw(v1, a0, kMaFlags);
    v1 = v1 | 0x2;
    sw(v1, a0, kMaFlags);
}

// 0x003C8F40 sub_3C8F40 -- 36 bytes; frame 0x10: ra sp+0x0
// [msgAssistPurgeAll] sub_3C8810 on the MsgAssist work (0x7CE67C). Callers: K_Field_DestroyFieldRootTask, sub_2DBA80,
// sub_2DBAC0.
void sub_3C8F40(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8f40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, kGpMsgAssist);  // 0x7CE67C
    jal(ctx, 0x3C8F4Cu, gen::fn_sub_3C8810_003c8810);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C9340 sub_3C9340 -- 76 bytes; leaf frame (no stack)
// [msgWinState] ($a0 a msgWin-shaped record) 0 when it has no handle (+0 < 0) or when it is hidden (+5) in state 2;
// else its s8 state +4.
void sub_3C9340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003c9340
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, kMsgWinHandle);
    if (i64(v0) >= 0) {
        // 0x003c9358
        charge(ctx, 3);
        lb(v0, a0, kMsgWinHidden);
        if (v0 != 0) {
            // 0x003c9364
            charge(ctx, 4);
            lb(v1, a0, kMsgWinState);
            v0 = 2;
            if (v1 != v0) {
                goto L_003c9380;
            }
            // 0x003c9374
            charge(ctx, 3);
            v0 = 0;
            // 0x003c9384 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_003c9380:
        charge(ctx, 1);
        lb(v0, a0, kMsgWinState);
    } else {
        // 0x003c934c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c9384 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003C9570 sub_3C9570 -- 532 bytes; frame 0xA0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [msgAssistPlaceWindow] ($a0 itfMesMng handle) Places a message window from the current font tag's parameters
// (frFontTagGetParam0..3): param 2 = -1 picks a preset (table 0x6A3F70 {width, height} by param 3, the y offsets
// 0x6A3F88) and puts the window at the fixed text position (1232, 1248) with a 0x2800-wide frame (sub_3A8650) and
// itfMesMngSetWindowOffset(596, y + 113); otherwise width = param 2, height = 25 * param 3, x / y = params 0 / 1 (-1
// centres on 640 x 448) in 1/16 and 1/8 units. Callers: sub_3A2260, sub_3A2440, sub_3C9790.
void sub_3C9570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003c9570
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s1 = 0;
    s0 = 0;
    a2 = 0x6A0000;
    a2 = addiu(a2, 16240);  // &0x6A3F70
    a1 = addiu(sp, 0x70);
    a0 = 3;
    for (;;) {
        // 0x003c95ac
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003c95d0
    charge(ctx, 17);
    v0 = 0x6A0000;
    lwc1(f2, v0, 16264);  // 0x6A3F88
    v0 = 0x6A0000;
    lwc1(f1, v0, 16268);  // 0x6A3F8C
    v0 = 0x6A0000;
    lwc1(f0, v0, 16272);  // 0x6A3F90
    swc1(f2, sp, 0x90);
    swc1(f1, sp, 0x94);
    swc1(f0, sp, 0x98);
    jal(ctx, 0x3C95F4u, gen::fn_frFontTagGetParam2_003af380);
    s3 = v0;
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x003c964c: explicit width, height = 25 * param 3
        charge(ctx, 6);
        jal(ctx, 0x3C964Cu, gen::fn_frFontTagGetParam3_003af390);
        v1 = sll(v0, 2);
        v1 = addu(v1, v0);
        v0 = sll(v1, 2);
        s2 = addu(v1, v0);
    } else {
        // 0x003c9614: param 2 == -1: a preset {width, height} by param 3
        charge(ctx, 14);
        s1 = 1;
        jal(ctx, 0x3C9618u, gen::fn_frFontTagGetParam3_003af390);
        s0 = v0;
        v0 = sll(s0, 3);
        v0 = addu(v0, sp);
        lw(s3, v0, 112);
        lw(v1, v0, 116);
        v0 = sll(v1, 2);
        v1 = addu(v0, v1);
        v0 = sll(v1, 2);
        s2 = addu(v1, v0);
    }
    // 0x003c9664
    charge(ctx, 8);
    jal(ctx, 0x3C9664u, gen::fn_frFontTagGetParam0_003af360);
    s4 = v0;
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 == v0) {
        // 0x003c9684: x: centred
        charge(ctx, 3);
        v1 = 320;
        v0 = sra(s3, 1);
        s4 = subu(v1, v0);
    }
    // 0x003c9690
    charge(ctx, 7);
    jal(ctx, 0x3C9690u, gen::fn_frFontTagGetParam1_003af370);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 == v1) {
        // 0x003c96ac: y: centred
        charge(ctx, 3);
        v1 = 224;
        v0 = sra(s2, 1);
        v0 = subu(v1, v0);
    }
    // 0x003c96b8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x003c9720: explicit placement (1/16, 1/8 units)
        charge(ctx, 15);
        s1 = sll(v0, 3);
        s0 = sll(s4, 4);
        a0 = s5;
        a1 = s0;
        a2 = s1;
        jal(ctx, 0x3C9734u, gen::fn_itfMesMngSetTextPosition_003a3ce0);
        t0 = sll(s3, 4);
        t1 = sll(s2, 3);
        a0 = s5;
        a1 = s0;
        a2 = s1;
        a3 = 0;
        jal(ctx, 0x3C9754u, gen::fn_sub_3A8650_003a8650);
    } else {
        // 0x003c96c0: preset placement
        charge(ctx, 24);
        a0 = s5;
        a1 = 1232;
        a2 = 1248;
        jal(ctx, 0x3C96CCu, gen::fn_itfMesMngSetTextPosition_003a3ce0);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 144);
        lw(s0, v0, 0);
        t1 = sll(s0, 3);
        a0 = s5;
        a1 = 0;
        a2 = 1032;
        a3 = 0;
        t0 = 10240;
        jal(ctx, 0x3C96FCu, gen::fn_sub_3A8650_003a8650);
        a2 = addiu(s0, 113);
        a0 = s5;
        a1 = 596;
        jal(ctx, 0x3C9710u, gen::fn_itfMesMngSetWindowOffset_003a6a80);
    }
    // 0x003c975c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003C9840 sub_3C9840 -- 12 bytes; leaf frame (no stack)
// [fclReturn0] Returns 0 (a no-op callback in five handler tables).
void sub_3C9840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c9840
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003C9B00 sub_3C9B00 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusSetPersona] ($a0 psStatus task, $a1 52-byte persona record or 0, $a2 84-byte block or 0) Copies the block
// to the status work +28 (or clears it), then the persona record over +32. Callers: the battle result, the panel,
// fusion, the shops.
void sub_3C9B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9b00
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    jal(ctx, 0x3C9B1Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s1 == 0) {
        // 0x003c9b4c
        charge(ctx, 5);
        a0 = addiu(s0, kPsBlock84);
        a1 = 0;
        a2 = 84;
        jal(ctx, 0x3C9B58u, gen::fn_memset_00521408);
    } else {
        // 0x003c9b30
        charge(ctx, 7);
        a0 = addiu(s0, kPsBlock84);
        a1 = s1;
        a2 = 84;
        jal(ctx, 0x3C9B3Cu, gen::fn_memcpy_00521250);
    }
    // 0x003c9b60
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x003c9b68
        charge(ctx, 5);
        a0 = addiu(s0, kPsPersona);
        a1 = s2;
        a2 = 52;
        jal(ctx, 0x3C9B74u, gen::fn_memcpy_00521250);
    }
    // 0x003c9b7c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C9BA0 sub_3C9BA0 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusSetPersonaRecord] Copies the 52-byte persona record $a1 to work +32 (K_Assert fclMisc.c:1687 on null).
void sub_3C9BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9ba0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3C9BB4u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s1 == 0) {
        // 0x003c9bc8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 1687;
        jal(ctx, 0x3C9BD4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c9bdc
    charge(ctx, 11);
    a0 = addiu(s0, kPsPersona);
    a1 = s1;
    a2 = 52;
    jal(ctx, 0x3C9BE8u, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C9C10 sub_3C9C10 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusSetCompare] ($a1 current, $a2 next persona record; K_Assert fclMisc.c:1694 on null) Copies them to work +32
// and +116; the first time (flag 0x40 clear) +22 = page (+232) * the page height (+20); then sets flag 0x40. Returns
// 1. Caller: the shop's sub_3ED5E0.
void sub_3C9C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9c10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    jal(ctx, 0x3C9C2Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s2 != 0) {
        // 0x003c9c40
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_003c9c48;
        }
        goto L_003c9c5c;
    }
L_003c9c48:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15896);  // "fclMisc.c"
    a1 = 1694;
    jal(ctx, 0x3C9C54u, gen::fn_sub_19D3F0_0019d3f0);
L_003c9c5c:
    charge(ctx, 14);
    a0 = addiu(s0, kPsPersona);
    a1 = s2;
    a2 = 52;
    jal(ctx, 0x3C9C68u, gen::fn_memcpy_00521250);
    a0 = addiu(s0, kPsPersonaNext);
    a1 = s1;
    a2 = 52;
    jal(ctx, 0x3C9C7Cu, gen::fn_memcpy_00521250);
    lw(v0, s0, kPsState);
    v0 = v0 & 0x40;
    if (v0 == 0) {
        // 0x003c9c94
        charge(ctx, 4);
        lb(v1, s0, kPsPage);
        lh(v0, s0, kPsPageHeight);
        mult(v0, v1, v0);
        sh(v0, s0, kPsScroll);
    }
    // 0x003c9ca4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v0, s0, kPsState);
    v0 = v0 | 0x40;
    sw(v0, s0, kPsState);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C9CD0 sub_3C9CD0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusSetWord24] psStatus work +24 = $a1.
void sub_3C9CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9cd0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9CE0u, gen::fn_kwlnTaskGetWorkData_00195540);
    sw(s0, v0, kPsWord24);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9D80 sub_3C9D80 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusSetStateOff] Clears the state bits $a1 of work +8, then prints "[fclMisc.c:1721]" and "psStatusSetStateOFF
// %d\n" and logs it (sub_1052B0). Caller: sub_276C30.
void sub_3C9D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9d80
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9D90u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = nor(s0, 0);
    lw(v1, v0, kPsState);
    v1 = v1 & a0;
    sw(v1, v0, kPsState);
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 1721;
    jal(ctx, 0x3C9DB8u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16656);  // "psStatusSetStateOFF %d\n"
    a1 = s0;
    jal(ctx, 0x3C9DCCu, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16656);  // "psStatusSetStateOFF %d\n"
    a1 = s0;
    jal(ctx, 0x3C9DE0u, gen::fn_sub_1052B0_001052b0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9E00 sub_3C9E00 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusSetWord234] psStatus work s16 +234 = $a1.
void sub_3C9E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9e00
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9E10u, gen::fn_kwlnTaskGetWorkData_00195540);
    sh(s0, v0, kPsWord234);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9E30 sub_3C9E30 -- 64 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusSetPages] psStatus work +233 = $a1 (page count), +232 = $a2 (page).
void sub_3C9E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9e30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    jal(ctx, 0x3C9E48u, gen::fn_kwlnTaskGetWorkData_00195540);
    sb(s1, v0, kPsPageCount);
    sb(s0, v0, kPsPage);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C9E70 sub_3C9E70 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusSetPage] work +232 = $a1 clamped to 0 .. count (+kPsPageCount) - 1.
void sub_3C9E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9e70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9E80u, gen::fn_kwlnTaskGetWorkData_00195540);
    sb(s0, v0, kPsPage);
    v1 = dsll32(s0, 24);
    v1 = dsra32(v1, 24);
    if (i64(v1) >= 0) {
        // 0x003c9ea8
        charge(ctx, 4);
        lb(a0, v0, kPsPageCount);
        v1 = slt(v1, a0);
        if (v1 == 0) {
            // 0x003c9eb8
            charge(ctx, 2);
            v1 = addiu(a0, -1);
            sb(v1, v0, kPsPage);
        }
    } else {
        // 0x003c9e9c
        charge(ctx, 3);
        sb(zero, v0, kPsPage);
    }
    // 0x003c9ec0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9EE0 sub_3C9EE0 -- 36 bytes; frame 0x10: ra sp+0x0
// [psStatusGetPage] The s8 page +232.
void sub_3C9EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9ee0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3C9EE8u, gen::fn_kwlnTaskGetWorkData_00195540);
    lb(v0, v0, kPsPage);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C9F10 sub_3C9F10 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusSetSpeedA] work u16 +12 = $a1, 1 when 0.
void sub_3C9F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9f10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9F20u, gen::fn_kwlnTaskGetWorkData_00195540);
    sh(s0, v0, kPsSpeedA);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    if (v1 == 0) {
        // 0x003c9f3c
        charge(ctx, 2);
        v1 = 1;
        sh(v1, v0, kPsSpeedA);
    }
    // 0x003c9f44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9F60 sub_3C9F60 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusSetSpeedB] work u16 +14 = $a1, 1 when 0.
void sub_3C9F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9f60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3C9F70u, gen::fn_kwlnTaskGetWorkData_00195540);
    sh(s0, v0, kPsSpeedB);
    v1 = dsll32(s0, 16);
    v1 = dsra32(v1, 16);
    if (v1 == 0) {
        // 0x003c9f8c
        charge(ctx, 2);
        v1 = 1;
        sh(v1, v0, kPsSpeedB);
    }
    // 0x003c9f94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9FB0 sub_3C9FB0 -- 40 bytes; frame 0x10: ra sp+0x0
// [psStatusSetPageHeight] work s16 +20 = 15.
void sub_3C9FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9fb0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3C9FB8u, gen::fn_kwlnTaskGetWorkData_00195540);
    v1 = 15;
    sh(v1, v0, kPsPageHeight);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003CA610 fclMisc_UpdatePsStatusDrawLowTask -- 80 bytes; frame 0x10: ra sp+0x0
// [fclMisc_UpdatePsStatusDrawLowTask] The "psStatusDrawLow" task: when the status is visible (+8 bit 0) and has a
// persona (u16 +34), calls the low draw function +224 through jalr. Returns 0.
void fclMisc_UpdatePsStatusDrawLowTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ca610
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3CA618u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    lw(v0, v0, kPsState);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003ca634
        charge(ctx, 3);
        lhu(v0, a0, kPsPersonaId);
        if (v0 != 0) {
            // 0x003ca640
            charge(ctx, 3);
            lw(v0, a0, kPsDrawLow);
            jalr(ctx, 0x3CA644u, v0.u());
        }
    }
    // 0x003ca64c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003CA660 fclMisc_UpdatePsStatusDrawHighTask -- 80 bytes; frame 0x10: ra sp+0x0
// [fclMisc_UpdatePsStatusDrawHighTask] As the low task with the high draw function +228.
void fclMisc_UpdatePsStatusDrawHighTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ca660
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3CA668u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    lw(v0, v0, kPsState);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003ca684
        charge(ctx, 3);
        lhu(v0, a0, kPsPersonaId);
        if (v0 != 0) {
            // 0x003ca690
            charge(ctx, 3);
            lw(v0, a0, kPsDrawHigh);
            jalr(ctx, 0x3CA694u, v0.u());
        }
    }
    // 0x003ca69c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003CCC30 nullsub_122 -- 8 bytes; leaf frame (no stack)
// [fclNop122] An empty draw handler (jr $ra) in a handler table.
void nullsub_122(EEContext& ctx) {
    using namespace hg;
    // 0x003ccc30
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003CD0A0 nullsub_123 -- 8 bytes; leaf frame (no stack)
// [fclNop123] An empty draw handler (jr $ra) in a handler table.
void nullsub_123(EEContext& ctx) {
    using namespace hg;
    // 0x003cd0a0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003CD590 nullsub_124 -- 8 bytes; leaf frame (no stack)
// [fclNop124] An empty draw handler (jr $ra) in a handler table.
void nullsub_124(EEContext& ctx) {
    using namespace hg;
    // 0x003cd590
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003CDA60 sub_3CDA60 -- 320 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelCreate] ($a0 parent task, $a1 unused) RwMalloc(256), zeroed: state +8 = 1, persona +12 = 0, a frame matrix
// at +64 (sub_4C31B0 with the rotation axis 0x6A4228, then sub_4C35D0 translation 0x6A4218), the RGBA word 0x7CD718 at
// +128, the g_data colours of persona 0 at +132 / +148 (sub_16BC80 / sub_16BDB0); then creates the "psModel" task
// (priority 5244, update sub_3CE2A0, destroy fclMisc_CreatePsModelDummyTask) and returns it. Callers: the battle panel
// sub_24AB10, the shop sub_3ECEB0, the fusion cut-in.
void sub_3CDA60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x003cda60
    enter(ctx, 80);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v0 = 0x6A0000;
    ld(v1, v0, 16920);  // 0x6A4218
    v0 = 0x6A0000;
    lwc1(f0, v0, 16928);  // 0x6A4220
    sd(v1, sp, 0x40);
    swc1(f0, sp, 0x48);
    v0 = 0x6A0000;
    ld(v1, v0, 16936);  // 0x6A4228
    v0 = 0x6A0000;
    lwc1(f0, v0, 16944);  // 0x6A4230
    sd(v1, sp, 0x30);
    swc1(f0, sp, 0x38);
    lwc1(f0, gp, -21976);  // 0x7CD718
    swc1(f0, sp, 0x4C);
    a0 = 256;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3CDABCu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 256;
    jal(ctx, 0x3CDAD4u, gen::fn_memset_00521408);
    sh(zero, s0, kPmPersona);
    v0 = 1;
    sw(v0, s0, kPmState);
    v0 = 0x43340000;
    mtc1(v0, f12);
    a0 = addiu(s0, 64);
    a1 = addiu(sp, 0x30);
    a2 = 0;
    jal(ctx, 0x3CDAFCu, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(s0, 64);
    a1 = addiu(sp, 0x40);
    a2 = 2;
    jal(ctx, 0x3CDB10u, gen::fn_sub_4C35D0_004c35d0);
    lbu(a1, sp, 0x4C);
    lbu(a0, sp, 0x4D);
    lbu(v1, sp, 0x4E);
    lbu(v0, sp, 0x4F);
    sb(a1, s0, kPmColour);
    sb(a0, s0, kPmColour + 1);
    sb(v1, s0, kPmColour + 2);
    sb(v0, s0, kPmColour + 3);
    lhu(a1, s0, kPmPersona);
    a0 = 0;
    a2 = addiu(s0, 132);
    jal(ctx, 0x3CDB44u, gen::fn_sub_16BC80_0016bc80);
    lhu(a1, s0, kPmPersona);
    a0 = 0;
    a2 = addiu(s0, 148);
    jal(ctx, 0x3CDB58u, gen::fn_sub_16BDB0_0016bdb0);
    a0 = s1;
    a1 = addiu(gp, -21968);  // "psModel"
    a2 = 5244;
    a3 = 0x3D0000;
    a3 = addiu(a3, -7520);  // &sub_3CE2A0
    t0 = 0x3D0000;
    t0 = addiu(t0, -3968);  // &fclMisc_CreatePsModelDummyTask
    t1 = s0;
    jal(ctx, 0x3CDB80u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003CDBA0 sub_3CDBA0 -- 220 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelSetPersona] ($a0 psModel task, $a1 persona id; K_Assert fclMisc.c:2530 on no work) Same id: clears the
// pending id (+14), returns 0. Model ready (+4 bit 0): a new id drops the ready bit and sets state 2 (reload); id 0
// destroys the model (+24, sub_3174E0); +12 = id, +14 = 0, returns 1. Not ready: queues the id in +14, returns 0.
void sub_3CDBA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cdba0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3CDBB4u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cdbc8: no work: K_Assert (continues)
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2530;
        jal(ctx, 0x3CDBD4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cdbdc
    charge(ctx, 4);
    a0 = s1 & 0xFFFF;
    lh(v0, s0, kPmPersona);
    if (v0 != a0) {
        // 0x003cdbfc: model ready?
        charge(ctx, 4);
        lw(v1, s0, kPmFlags);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x003cdc1c
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x003cdc40: persona 0: destroy the model
                charge(ctx, 3);
                lw(a0, s0, kPmModel);
                if (a0 != 0) {
                    // 0x003cdc4c
                    charge(ctx, 3);
                    jal(ctx, 0x3CDC4Cu, gen::fn_sub_3174E0_003174e0);
                    sw(zero, s0, kPmModel);
                }
            } else {
                // 0x003cdc24: a new persona: drop the ready bit, state 2 (reload)
                charge(ctx, 7);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s0, kPmFlags);
                v0 = 2;
                sw(v0, s0, kPmState);
            }
            // 0x003cdc58: record the persona
            charge(ctx, 3);
            sh(s1, s0, kPmPersona);
            sh(zero, s0, kPmPending);
            v0 = 1;
        } else {
            // 0x003cdc0c: not ready: queue the id
            charge(ctx, 4);
            sh(s1, s0, kPmPending);
            v0 = 0;
        }
    } else {
        // 0x003cdbec: same persona: clear the pending id
        charge(ctx, 4);
        sh(zero, s0, kPmPending);
        v0 = 0;
    }
    // 0x003cdc64 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CDC80 sub_3CDC80 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psModelIsReady] +4 bit 0 of the psModel work (K_Assert fclMisc.c:2561).
void sub_3CDC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cdc80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3CDC8Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cdca0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2561;
        jal(ctx, 0x3CDCACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cdcb4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, kPmFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CDCD0 sub_3CDCD0 -- 164 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelPlayAnim] When the model is ready: sub_3182D0(model +24, 0, $a1, $a2, $a3) (start an animation), else 0
// (K_Assert fclMisc.c:2568).
void sub_3CDCD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cdcd0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    jal(ctx, 0x3CDCF4u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cdd08
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2568;
        jal(ctx, 0x3CDD14u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cdd1c
    charge(ctx, 4);
    lw(v0, s0, kPmFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003cdd38
        charge(ctx, 7);
        lw(a0, s0, kPmModel);
        a1 = 0;
        a2 = s3;
        a3 = s2;
        t0 = s1;
        jal(ctx, 0x3CDD4Cu, gen::fn_sub_3182D0_003182d0);
    } else {
        // 0x003cdd2c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003cdd54 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003CDD80 sub_3CDD80 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psModelAnimDone] 1 when the model is not ready or its animation state byte (+24 -> +238) is 1 (K_Assert
// fclMisc.c:2576).
void sub_3CDD80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cdd80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3CDD8Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cdda0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2576;
        jal(ctx, 0x3CDDACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cddb4
    charge(ctx, 4);
    lw(v0, s0, kPmFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x003cddd0
        charge(ctx, 4);
        lw(v0, s0, kPmModel);
        lbu(v0, v0, kModelAnimState);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x003cddc4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003cdde0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CDE00 sub_3CDE00 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelSetFlags] work +4 |= $a1 << 16 (K_Assert fclMisc.c:2584).
void sub_3CDE00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cde00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3CDE14u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cde28
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2584;
        jal(ctx, 0x3CDE34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cde3c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    a0 = sll(s1, 16);
    lw(v1, s0, kPmFlags);
    v1 = v1 | a0;
    sw(v1, s0, kPmFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CDE70 sub_3CDE70 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelClearFlags] work +4 &= ~($a1 << 16) (K_Assert fclMisc.c:2590).
void sub_3CDE70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cde70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3CDE84u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cde98
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2590;
        jal(ctx, 0x3CDEA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cdeac (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v1 = sll(s1, 16);
    a0 = nor(v1, 0);
    lw(v1, s0, kPmFlags);
    v1 = v1 & a0;
    sw(v1, s0, kPmFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CDEE0 sub_3CDEE0 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelSetWord0] work u16 +0 = $a1 (K_Assert fclMisc.c:2598).
void sub_3CDEE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cdee0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3CDEF4u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cdf08
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2598;
        jal(ctx, 0x3CDF14u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cdf1c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sh(s1, s0, kPmWord0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CDF40 sub_3CDF40 -- 280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelFadeColour] ($a1 RGBA bytes, $a2 frames; K_Assert fclMisc.c:2641) Starts a fade of the model colour +128:
// target +164 = $a1, start +168 = the current colour; with 0 frames the colour is set at once (+168 = +164 = +128 =
// $a1). Timer +172 = 0, duration +174 = $a2.
void sub_3CDF40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cdf40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    jal(ctx, 0x3CDF5Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003cdf70
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2641;
        jal(ctx, 0x3CDF7Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cdf84
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003cdff4
        charge(ctx, 16);
        lbu(a2, s2, 0);
        lbu(a1, s2, 1);
        lbu(a0, s2, 2);
        lbu(v1, s2, 3);
        sb(a2, s0, kPmFadeTarget);
        sb(a1, s0, kPmFadeTarget + 1);
        sb(a0, s0, kPmFadeTarget + 2);
        sb(v1, s0, kPmFadeTarget + 3);
        lbu(a2, s0, kPmColour);
        lbu(a1, s0, kPmColour + 1);
        lbu(a0, s0, kPmColour + 2);
        lbu(v1, s0, kPmColour + 3);
        sb(a2, s0, kPmFadeStart);
        sb(a1, s0, kPmFadeStart + 1);
        sb(a0, s0, kPmFadeStart + 2);
        sb(v1, s0, kPmFadeStart + 3);
    } else {
        // 0x003cdf8c
        charge(ctx, 26);
        lbu(a2, s2, 0);
        lbu(a1, s2, 1);
        lbu(a0, s2, 2);
        lbu(v1, s2, 3);
        sb(a2, s0, kPmFadeStart);
        sb(a1, s0, kPmFadeStart + 1);
        sb(a0, s0, kPmFadeStart + 2);
        sb(v1, s0, kPmFadeStart + 3);
        lbu(a2, s0, kPmFadeStart);
        lbu(a1, s0, kPmFadeStart + 1);
        lbu(a0, s0, kPmFadeStart + 2);
        lbu(v1, s0, kPmFadeStart + 3);
        sb(a2, s0, kPmFadeTarget);
        sb(a1, s0, kPmFadeTarget + 1);
        sb(a0, s0, kPmFadeTarget + 2);
        sb(v1, s0, kPmFadeTarget + 3);
        lbu(a2, s0, kPmFadeTarget);
        lbu(a1, s0, kPmFadeTarget + 1);
        lbu(a0, s0, kPmFadeTarget + 2);
        lbu(v1, s0, kPmFadeTarget + 3);
        sb(a2, s0, kPmColour);
        sb(a1, s0, kPmColour + 1);
        sb(a0, s0, kPmColour + 2);
        sb(v1, s0, kPmColour + 3);
    }
    // 0x003ce034 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sh(zero, s0, kPmFadeTimer);
    sh(s1, s0, kPmFadeFrames);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003CE060 sub_3CE060 -- 280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelFadeColourA] As sub_3CDF40 for the float colour A +132 (target +176, start +192, timer +208, duration +210;
// K_Assert fclMisc.c:2657).
void sub_3CE060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x003ce060
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    jal(ctx, 0x3CE07Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003ce090
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2657;
        jal(ctx, 0x3CE09Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003ce0a4
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003ce114
        charge(ctx, 16);
        lwc1(f3, s2, 0);
        lwc1(f2, s2, 4);
        lwc1(f1, s2, 8);
        lwc1(f0, s2, 12);
        swc1(f3, s0, kPmFadeATarget);
        swc1(f2, s0, kPmFadeATarget + 4);
        swc1(f1, s0, kPmFadeATarget + 8);
        swc1(f0, s0, kPmFadeATarget + 12);
        lwc1(f3, s0, kPmColourA);
        lwc1(f2, s0, kPmColourA + 4);
        lwc1(f1, s0, kPmColourA + 8);
        lwc1(f0, s0, kPmColourA + 12);
        swc1(f3, s0, kPmFadeAStart);
        swc1(f2, s0, kPmFadeAStart + 4);
        swc1(f1, s0, kPmFadeAStart + 8);
        swc1(f0, s0, kPmFadeAStart + 12);
    } else {
        // 0x003ce0ac
        charge(ctx, 26);
        lwc1(f3, s2, 0);
        lwc1(f2, s2, 4);
        lwc1(f1, s2, 8);
        lwc1(f0, s2, 12);
        swc1(f3, s0, kPmFadeAStart);
        swc1(f2, s0, kPmFadeAStart + 4);
        swc1(f1, s0, kPmFadeAStart + 8);
        swc1(f0, s0, kPmFadeAStart + 12);
        lwc1(f3, s0, kPmFadeAStart);
        lwc1(f2, s0, kPmFadeAStart + 4);
        lwc1(f1, s0, kPmFadeAStart + 8);
        lwc1(f0, s0, kPmFadeAStart + 12);
        swc1(f3, s0, kPmFadeATarget);
        swc1(f2, s0, kPmFadeATarget + 4);
        swc1(f1, s0, kPmFadeATarget + 8);
        swc1(f0, s0, kPmFadeATarget + 12);
        lwc1(f3, s0, kPmFadeATarget);
        lwc1(f2, s0, kPmFadeATarget + 4);
        lwc1(f1, s0, kPmFadeATarget + 8);
        lwc1(f0, s0, kPmFadeATarget + 12);
        swc1(f3, s0, kPmColourA);
        swc1(f2, s0, kPmColourA + 4);
        swc1(f1, s0, kPmColourA + 8);
        swc1(f0, s0, kPmColourA + 12);
    }
    // 0x003ce154 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sh(zero, s0, kPmFadeATimer);
    sh(s1, s0, kPmFadeAFrames);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003CE180 sub_3CE180 -- 280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelFadeColourB] As sub_3CDF40 for the float colour B +148 (target +212, start +228, timer +244, duration +246;
// K_Assert fclMisc.c:2679).
void sub_3CE180(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x003ce180
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    jal(ctx, 0x3CE19Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x003ce1b0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2679;
        jal(ctx, 0x3CE1BCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003ce1c4
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003ce234
        charge(ctx, 16);
        lwc1(f3, s2, 0);
        lwc1(f2, s2, 4);
        lwc1(f1, s2, 8);
        lwc1(f0, s2, 12);
        swc1(f3, s0, kPmFadeBTarget);
        swc1(f2, s0, kPmFadeBTarget + 4);
        swc1(f1, s0, kPmFadeBTarget + 8);
        swc1(f0, s0, kPmFadeBTarget + 12);
        lwc1(f3, s0, kPmColourB);
        lwc1(f2, s0, kPmColourB + 4);
        lwc1(f1, s0, kPmColourB + 8);
        lwc1(f0, s0, kPmColourB + 12);
        swc1(f3, s0, kPmFadeBStart);
        swc1(f2, s0, kPmFadeBStart + 4);
        swc1(f1, s0, kPmFadeBStart + 8);
        swc1(f0, s0, kPmFadeBStart + 12);
    } else {
        // 0x003ce1cc
        charge(ctx, 26);
        lwc1(f3, s2, 0);
        lwc1(f2, s2, 4);
        lwc1(f1, s2, 8);
        lwc1(f0, s2, 12);
        swc1(f3, s0, kPmFadeBStart);
        swc1(f2, s0, kPmFadeBStart + 4);
        swc1(f1, s0, kPmFadeBStart + 8);
        swc1(f0, s0, kPmFadeBStart + 12);
        lwc1(f3, s0, kPmFadeBStart);
        lwc1(f2, s0, kPmFadeBStart + 4);
        lwc1(f1, s0, kPmFadeBStart + 8);
        lwc1(f0, s0, kPmFadeBStart + 12);
        swc1(f3, s0, kPmFadeBTarget);
        swc1(f2, s0, kPmFadeBTarget + 4);
        swc1(f1, s0, kPmFadeBTarget + 8);
        swc1(f0, s0, kPmFadeBTarget + 12);
        lwc1(f3, s0, kPmFadeBTarget);
        lwc1(f2, s0, kPmFadeBTarget + 4);
        lwc1(f1, s0, kPmFadeBTarget + 8);
        lwc1(f0, s0, kPmFadeBTarget + 12);
        swc1(f3, s0, kPmColourB);
        swc1(f2, s0, kPmColourB + 4);
        swc1(f1, s0, kPmColourB + 8);
        swc1(f0, s0, kPmColourB + 12);
    }
    // 0x003ce274 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sh(zero, s0, kPmFadeBTimer);
    sh(s1, s0, kPmFadeBFrames);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003CF520 sub_3CF520 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBankMarkBlocked] For the three bank slots of the fclBank work (0x7CE680 -> +36, +4 + 20 i): an active slot (bit
// 0) that is playing (8) or loading (2) gets 0x400, and every active slot gets 0x800 while game flag 5145 is clear
// (datGetFlag). Caller: sub_3ADD00.
void sub_3CF520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf520
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBankManager);  // 0x7CE680
    lw(v1, v1, kBankSlots);
    s0 = addiu(v1, 4);
    s1 = 0;
    for (;;) {
        // 0x003cf5a4
        charge(ctx, 3);
        v1 = slti(s1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf548: an active slot
        charge(ctx, 4);
        lh(a0, s0, kBankSlotFlags);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            // 0x003cf558
            charge(ctx, 3);
            v0 = a0 & 0x8;
            if (v0 == 0) {
                // 0x003cf564
                charge(ctx, 3);
                v0 = a0 & 0x2;
                if (v0 != 0) {
                    goto L_003cf570;
                }
                goto L_003cf57c;
            }
        L_003cf570:
            charge(ctx, 3);
            lh(v0, s0, kBankSlotFlags);
            v0 = v0 | 0x400;
            sh(v0, s0, kBankSlotFlags);
        L_003cf57c:
            charge(ctx, 5);
            a0 = 5145;
            jal(ctx, 0x3CF580u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x003cf590: game flag 5145 clear: 0x800
                charge(ctx, 3);
                lh(v1, s0, kBankSlotFlags);
                v1 = v1 | 0x800;
                sh(v1, s0, kBankSlotFlags);
            }
        }
        // 0x003cf59c
        charge(ctx, 2);
        s0 = addiu(s0, 20);
        s1 = addiu(s1, 1);
    }
    // 0x003cf5b0
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CF8F0 sub_3CF8F0 -- 100 bytes; leaf frame (no stack)
// [fclBankFindSlot] The index 0..2 of the active bank slot whose bank number (+4) is $a0, else -1. Caller: sub_3CF240.
void sub_3CF8F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003cf8f0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, kGpBankManager);  // 0x7CE680
    lw(v0, v0, kBankSlots);
    v1 = addiu(v0, 4);
    a1 = 0;
    for (;;) {
        // 0x003cf93c
        charge(ctx, 3);
        v0 = slti(a1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf908
        charge(ctx, 4);
        lh(v0, v1, kBankSlotFlags);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x003cf918
            charge(ctx, 3);
            lw(v0, v1, kBankSlotBank);
            if (v0 != a0) {
                goto L_003cf934;
            }
            goto L_003cf924_3;
        }
    L_003cf934:
        charge(ctx, 2);
        v1 = addiu(v1, 20);
        a1 = addiu(a1, 1);
    }
    // 0x003cf948
    charge(ctx, 1);
    v0 = si(-1);
    // 0x003cf94c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003cf924_3:
    charge(ctx, 4);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    // 0x003cf94c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003CF960 sub_3CF960 -- 340 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBankRequest] ($a0 bank number, $a1 flags in the high byte) When a slot already holds the bank: replaces the
// slot's high flag byte with $a1's, prints "[fclBankManager.c:438]" / "fclBankManagerRequest:Bank Hit[%d]!!!" and logs
// it, returns 0; otherwise appends a request node (payload +4 bank, +0 = ($a1 & 0xFF00) | 3) to the bank's request
// list and returns the node. Caller: sub_3CF160.
void sub_3CF960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf960
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(a0, gp, kGpBankManager);  // 0x7CE680
    lw(v1, a0, kBankSlots);
    a1 = addiu(v1, 4);
    a2 = 0;
    for (;;) {
        // 0x003cf9c8
        charge(ctx, 3);
        v0 = slti(a2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf994: find the active slot of this bank
        charge(ctx, 4);
        lh(v0, a1, kBankSlotFlags);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x003cf9a4
            charge(ctx, 3);
            lw(v0, a1, kBankSlotBank);
            if (v0 != s2) {
                goto L_003cf9c0;
            }
            goto L_003cf9b0_3;
        }
    L_003cf9c0:
        charge(ctx, 2);
        a1 = addiu(a1, 20);
        a2 = addiu(a2, 1);
    }
    // 0x003cf9d4
    charge(ctx, 1);
    v0 = si(-1);
L_003cf9d8:
    charge(ctx, 5);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    v0 = si(-1);
    if (s0 == v0) {
        // 0x003cfa6c: no slot: a new request node
        charge(ctx, 11);
        a1 = 0;
        a2 = 20;
        jal(ctx, 0x3CFA74u, gen::fn_nmListAppendNew_003c4910);
        lw(a0, v0, kNmNodePayload);
        sw(s2, a0, kBankSlotBank);
        v1 = dsll32(s1, 16);
        v1 = dsra32(v1, 16);
        v1 = v1 & 0xFF00;
        v1 = v1 | 0x3;
        sh(v1, a0, kBankSlotFlags);
    } else {
        // 0x003cf9ec: a slot hit: replace its request flags, log it
        charge(ctx, 32);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        a1 = addu(v0, v1);
        lbu(a0, a1, 4);
        sh(a0, a1, 4);
        v0 = s1 & 0xFF00;
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = dsll32(a0, 16);
        v0 = dsra32(v0, 16);
        v0 = v0 | v1;
        sh(v0, a1, 4);
        a0 = addiu(gp, -21960);  // "[%s:%d]"
        a1 = 0x6A0000;
        a1 = addiu(a1, 17008);  // "fclBankManager.c"
        a2 = 438;
        jal(ctx, 0x3CFA30u, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 17136);  // "fclBankManagerRequest:Bank Hit[%d]!!!\n"
        a1 = s0;
        jal(ctx, 0x3CFA44u, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 17136);  // "fclBankManagerRequest:Bank Hit[%d]!!!\n"
        a1 = s0;
        jal(ctx, 0x3CFA58u, gen::fn_sub_1052B0_001052b0);
        v0 = 0;
    }
    // 0x003cfa98 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003cf9b0_3:
    charge(ctx, 4);
    v0 = dsll32(a2, 16);
    v0 = dsra32(v0, 16);
    goto L_003cf9d8;
}

// 0x003CFAC0 sub_3CFAC0 -- 144 bytes; leaf frame (no stack)
// [fclBankConflict] ($a0 a bank slot) For each other active slot that is playing (8) with the same 0x100 bit as $a0:
// marks it 0x400 and, when it is not stopped (4), the result becomes 0. Returns 1 when no such slot is still running.
// Caller: fclBank_UpdateTask.
void sub_3CFAC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x003cfac0
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 1;
    lw(v1, gp, kGpBankManager);  // 0x7CE680
    lw(v1, v1, kBankSlots);
    t0 = addiu(v1, 4);
    a3 = 0;
    for (;;) {
        // 0x003cfb3c
        charge(ctx, 3);
        v1 = slti(a3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cfadc
        charge(ctx, 2);
        if (t0 != a0) {
            // 0x003cfae4: another active slot
            charge(ctx, 4);
            lh(a2, t0, kBankSlotFlags);
            v1 = a2 & 0x1;
            if (v1 != 0) {
                // 0x003cfaf4
                charge(ctx, 3);
                v1 = a2 & 0x8;
                if (v1 != 0) {
                    // 0x003cfb00: playing, same group?
                    charge(ctx, 5);
                    a1 = a2 & 0x100;
                    lh(v1, a0, kBankSlotFlags);
                    v1 = v1 & 0x100;
                    if (a1 == v1) {
                        // 0x003cfb14: block it
                        charge(ctx, 7);
                        v1 = a2 | 0x400;
                        sh(v1, t0, kBankSlotFlags);
                        v1 = dsll32(v1, 16);
                        v1 = dsra32(v1, 16);
                        v1 = v1 & 0x4;
                        if (v1 == 0) {
                            // 0x003cfb30: still running: not clear
                            charge(ctx, 1);
                            v0 = 0;
                        }
                    }
                }
            }
        }
        // 0x003cfb34
        charge(ctx, 2);
        t0 = addiu(t0, 20);
        a3 = addiu(a3, 1);
    }
    // 0x003cfb48
    charge(ctx, 2);
}

}  // namespace p3fes::game
