// Slice scene (game/include/p3fes/game/scene.h has the formats and the records): comuFunction.c / comuTimerSequence.c: comuTable.bin and its accessors, the link state rules, the event requests, the comu timer sequence steps.
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; tools check it).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_adminiChangeSeq_0027c080(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrCreateTaskFromHeader_0035bb40(p3fes::EEContext&);
void fn_sub_16C7E0_0016c7e0(p3fes::EEContext&);
void fn_sub_16D280_0016d280(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DCE0_0016dce0(p3fes::EEContext&);
void fn_sub_16DD20_0016dd20(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16E410_0016e410(p3fes::EEContext&);
void fn_sub_16E920_0016e920(p3fes::EEContext&);
void fn_sub_1717B0_001717b0(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_171960_00171960(p3fes::EEContext&);
void fn_sub_171AC0_00171ac0(p3fes::EEContext&);
void fn_sub_171C40_00171c40(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_172660_00172660(p3fes::EEContext&);
void fn_sub_172A50_00172a50(p3fes::EEContext&);
void fn_sub_172B20_00172b20(p3fes::EEContext&);
void fn_sub_172C50_00172c50(p3fes::EEContext&);
void fn_sub_17E050_0017e050(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_27C2B0_0027c2b0(p3fes::EEContext&);
void fn_sub_27C330_0027c330(p3fes::EEContext&);
void fn_sub_38D6F0_0038d6f0(p3fes::EEContext&);
void fn_sub_395200_00395200(p3fes::EEContext&);
void fn_sub_395230_00395230(p3fes::EEContext&);
void fn_sub_3BD280_003bd280(p3fes::EEContext&);
void fn_sub_3BD870_003bd870(p3fes::EEContext&);
void fn_sub_3BD890_003bd890(p3fes::EEContext&);
void fn_sub_3BD8A0_003bd8a0(p3fes::EEContext&);
void fn_sub_3BDA60_003bda60(p3fes::EEContext&);
void fn_sub_3BDB80_003bdb80(p3fes::EEContext&);
void fn_sub_3BDBA0_003bdba0(p3fes::EEContext&);
void fn_sub_3BDBB0_003bdbb0(p3fes::EEContext&);
void fn_sub_3BDBD0_003bdbd0(p3fes::EEContext&);
void fn_sub_3BDD40_003bdd40(p3fes::EEContext&);
void fn_sub_3BDD50_003bdd50(p3fes::EEContext&);
void fn_sub_3BDD60_003bdd60(p3fes::EEContext&);
void fn_sub_3BDD90_003bdd90(p3fes::EEContext&);
void fn_sub_3BDDD0_003bddd0(p3fes::EEContext&);
void fn_sub_3BDDE0_003bdde0(p3fes::EEContext&);
void fn_sub_3BDED0_003bded0(p3fes::EEContext&);
void fn_sub_3BDFC0_003bdfc0(p3fes::EEContext&);
void fn_sub_3BE020_003be020(p3fes::EEContext&);
void fn_sub_3BE1A0_003be1a0(p3fes::EEContext&);
void fn_sub_3BE1C0_003be1c0(p3fes::EEContext&);
void fn_sub_3BE2A0_003be2a0(p3fes::EEContext&);
void fn_sub_3BEA20_003bea20(p3fes::EEContext&);
void fn_sub_3BEAB0_003beab0(p3fes::EEContext&);
void fn_sub_3BEB10_003beb10(p3fes::EEContext&);
void fn_sub_3BEB70_003beb70(p3fes::EEContext&);
void fn_sub_3BEBD0_003bebd0(p3fes::EEContext&);
void fn_sub_3BEC50_003bec50(p3fes::EEContext&);
void fn_sub_3BECA0_003beca0(p3fes::EEContext&);
void fn_sub_3BEE80_003bee80(p3fes::EEContext&);
void fn_sub_3BF130_003bf130(p3fes::EEContext&);
void fn_sub_3BF180_003bf180(p3fes::EEContext&);
void fn_sub_3BF200_003bf200(p3fes::EEContext&);
void fn_sub_3BF270_003bf270(p3fes::EEContext&);
void fn_sub_3BF370_003bf370(p3fes::EEContext&);
void fn_sub_3BF510_003bf510(p3fes::EEContext&);
void fn_sub_3BF610_003bf610(p3fes::EEContext&);
void fn_sub_3BF720_003bf720(p3fes::EEContext&);
void fn_sub_3BF8E0_003bf8e0(p3fes::EEContext&);
void fn_sub_3BF950_003bf950(p3fes::EEContext&);
void fn_sub_3BFAE0_003bfae0(p3fes::EEContext&);
void fn_sub_3BFC50_003bfc50(p3fes::EEContext&);
void fn_sub_3BFDB0_003bfdb0(p3fes::EEContext&);
void fn_sub_3BFF40_003bff40(p3fes::EEContext&);
void fn_sub_3BFFA0_003bffa0(p3fes::EEContext&);
void fn_sub_3C2570_003c2570(p3fes::EEContext&);
void fn_sub_3C2B40_003c2b40(p3fes::EEContext&);
void fn_sub_3C2C50_003c2c50(p3fes::EEContext&);
void fn_sub_3C3050_003c3050(p3fes::EEContext&);
void fn_sub_3C30B0_003c30b0(p3fes::EEContext&);
void fn_sub_3C3120_003c3120(p3fes::EEContext&);
void fn_sub_3C3190_003c3190(p3fes::EEContext&);
void fn_sub_3C3E80_003c3e80(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scn;

// 0x00172A50 sub_172A50 -- 88 bytes; leaf frame (no stack)
// (link) 1 for the social links 6..11 (the ones with partner events, sub_3BE020), else 0.
void sub_172A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00172a50
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    a0 = dsll32(a0, 16);
    a0 = dsra32(a0, 16);
    for (;;) {
        // 0x00172a88
        charge(ctx, 5);
        v1 = dsll32(a1, 16);
        v1 = dsra32(v1, 16);
        v0 = slti(v1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00172a64
        charge(ctx, 3);
        v0 = addiu(v1, 6);
        if (a0 == v0) {
            goto L_00172a70_2;
        }
        // 0x00172a7c
        charge(ctx, 3);
        v0 = addiu(a1, 1);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
    }
    // 0x00172a9c
    charge(ctx, 1);
    v0 = 0;
    // 0x00172aa0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00172a70_2:
    charge(ctx, 3);
    v0 = 1;
    // 0x00172aa0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BD280 sub_3BD280 -- 1512 bytes; frame 0x20: ra sp+0x0
// [comuLoadTableBin] Loads "event/comuPack.pak" (request kept at 0x7CE668, read synchronously), finds
// "event/comuTable.bin" and "event/SiteibiEvent.bf" in it; version 1 (u16 +0): the 144 sections (+4: {u32 offset, u32
// size}) become pointers (0 when the offset is 0) and sizes, sections 0..29 / 32..61 / 64..93 are copied to the
// per-link tables (0x95B4F0 / 0x95B568 / 0x95B5E0), and the named tables {pointer, count} are derived with their
// record sizes (comu namespace). Another version: "error!! comuTableBinFile Version Invalid" and the table pointer
// cleared.
void sub_3BD280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bd280
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(a0, gp, comu::kGpPakPath);  // 0x7CD568 "event/comuPack.pak"
    a1 = 1;
    jal(ctx, 0x3BD290u, gen::fn_H_Cdvd_Request_00100d80);
    sw(v0, gp, comu::kGpPakRequest);  // 0x7CE668 the H_Cdvd request of comuPack.pak
    a0 = v0;
    jal(ctx, 0x3BD2A0u, gen::fn_H_Cdvd_ReadSync_001023a0);
    lw(a0, gp, comu::kGpTablePath);  // 0x7CD56C "event/comuTable.bin"
    a1 = addiu(sp, 0x1C);
    jal(ctx, 0x3BD2B0u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
    v1 = 0x960000;
    sw(v0, v1, comu::kLoTable);  // 0x95B070 comuTable.bin in the pak
    lw(a0, gp, comu::kGpScriptPath);  // 0x7CD570 "event/SiteibiEvent.bf"
    a1 = addiu(sp, 0x1C);
    jal(ctx, 0x3BD2C8u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
    v1 = 0x960000;
    sw(v0, v1, comu::kLoScript);  // 0x95B074 SiteibiEvent.bf in the pak
    v0 = 0x960000;
    lw(v0, v0, comu::kLoTable);  // 0x95B070 comuTable.bin in the pak
    lhu(a2, v0, 0);
    a1 = 1;
    if (a2 == a1) {
        // 0x003bd310
        charge(ctx, 7);
        a3 = addiu(v0, 4);
        t0 = 0;
        a0 = 0x960000;
        a0 = addiu(a0, -20368);  // &0x95B070
        v0 = 0x960000;
        for (;;) {
            // 0x003bd370
            charge(ctx, 3);
            at = slti(t0, 144);
            if (at == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bd32c
            charge(ctx, 3);
            lw(a1, a3, 0);
            if (a1 == 0) {
                // 0x003bd354
                charge(ctx, 3);
                v1 = sll(t0, 2);
                a2 = addu(a0, v1);
                sw(zero, a2, 8);
            } else {
                // 0x003bd338
                charge(ctx, 7);
                v1 = sll(t0, 2);
                a2 = addu(a0, v1);
                lw(v1, v0, -20368);
                v1 = addu(v1, a1);
                sw(v1, a2, 8);
            }
            // 0x003bd360
            charge(ctx, 4);
            lw(v1, a3, 4);
            sw(v1, a2, 580);
            a3 = addiu(a3, 8);
            t0 = addiu(t0, 1);
        }
        // 0x003bd37c
        charge(ctx, 13);
        v0 = 0x960000;
        lw(v0, v0, comu::kLoTable);  // 0x95B070 comuTable.bin in the pak
        lhu(a1, v0, 0);
        lbu(a2, v0, 2);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12880);  // "comuTableBinFile Load version=%d tableno=%d\n"
        jal(ctx, 0x3BD394u, gen::fn_printf_005225a8);
        a2 = 0;
        a1 = 0x960000;
        a1 = addiu(a1, -20368);  // &0x95B070
        for (;;) {
            // 0x003bd3c4
            charge(ctx, 3);
            v1 = slti(a2, 30);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bd3b0
            charge(ctx, 5);
            v1 = sll(a2, 2);
            a0 = addu(a1, v1);
            lw(v1, a0, 8);
            sw(v1, a0, 1152);
            a2 = addiu(a2, 1);
        }
        // 0x003bd3d0
        charge(ctx, 5);
        a2 = 0;
        a1 = 0x960000;
        a1 = addiu(a1, -20368);  // &0x95B070
        for (;;) {
            // 0x003bd3f8
            charge(ctx, 3);
            v1 = slti(a2, 30);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bd3e4
            charge(ctx, 5);
            v1 = sll(a2, 2);
            a0 = addu(a1, v1);
            lw(v1, a0, 136);
            sw(v1, a0, 1272);
            a2 = addiu(a2, 1);
        }
        // 0x003bd404
        charge(ctx, 5);
        a2 = 0;
        a1 = 0x960000;
        a1 = addiu(a1, -20368);  // &0x95B070
        for (;;) {
            // 0x003bd42c
            charge(ctx, 3);
            v1 = slti(a2, 30);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bd418
            charge(ctx, 5);
            v1 = sll(a2, 2);
            a0 = addu(a1, v1);
            lw(v1, a0, 264);
            sw(v1, a0, 1392);
            a2 = addiu(a2, 1);
        }
        // 0x003bd438
        charge(ctx, 4);
        v1 = 0x960000;
        lw(a0, v1, -19976);  // 0x95B1F8
        if (a0 != 0) {
            // 0x003bd448
            charge(ctx, 9);
            v1 = 0x960000;
            sw(a0, v1, comu::kLoSec96);  // 0x95B658 {section 96, size / 24}
            v1 = 0x960000;
            lw(a0, v1, -19404);  // 0x95B434
            v1 = 24;
            divu(a0, v1);
            mflo(a0);
            v1 = 0x960000;
            sw(a0, v1, -18852);  // 0x95B65C
        }
        // 0x003bd46c
        charge(ctx, 4);
        v1 = 0x960000;
        lw(a0, v1, -19936);  // 0x95B220
        if (a0 != 0) {
            // 0x003bd47c
            charge(ctx, 7);
            v1 = 0x960000;
            sw(a0, v1, comu::kLoDatedConds);  // 0x95B660 {section 106, size / 4}: dated conditions
            v1 = 0x960000;
            lw(v1, v1, -19364);  // 0x95B45C
            a0 = srl(v1, 2);
            v1 = 0x960000;
            sw(a0, v1, -18844);  // 0x95B664
        }
        // 0x003bd498
        charge(ctx, 4);
        v1 = 0x960000;
        lw(a0, v1, -19932);  // 0x95B224
        if (a0 != 0) {
            // 0x003bd4a8
            charge(ctx, 9);
            v1 = 0x960000;
            sw(a0, v1, comu::kLoDatedFlags);  // 0x95B668 {section 107, size / 6}: dated flags
            v1 = 0x960000;
            lw(a0, v1, -19360);  // 0x95B460
            v1 = 6;
            divu(a0, v1);
            mflo(a0);
            v1 = 0x960000;
            sw(a0, v1, -18836);  // 0x95B66C
        }
        // 0x003bd4cc
        charge(ctx, 227);
        v1 = 0x960000;
        lw(a0, v1, -19912);  // 0x95B238
        v1 = 0x960000;
        sw(a0, v1, comu::kLoMapEvents);  // 0x95B670 {section 112, size / 10}: 10-byte event rows
        v1 = 0x960000;
        lw(a0, v1, -19340);  // 0x95B474
        v1 = 10;
        divu(a0, v1);
        mflo(a0);
        v1 = 0x960000;
        sw(a0, v1, comu::kLoMapEventCount);  // 0x95B674 the row count of section 112
        v1 = 0x960000;
        lw(a0, v1, -19964);  // 0x95B204
        v1 = 0x960000;
        sw(a0, v1, comu::kLoCallDays);  // 0x95B678 {section 99, /3}, {100, /3}, {101, /5}, {102, /5}: the dated / ranged call tables
        v1 = 0x960000;
        lw(v1, v1, -19392);  // 0x95B440
        a0 = 3;
        divu(v1, a0);
        mflo(a1);
        v1 = 0x960000;
        sw(a1, v1, -18820);  // 0x95B67C
        v1 = 0x960000;
        lw(a1, v1, -19960);  // 0x95B208
        v1 = 0x960000;
        sw(a1, v1, -18816);  // 0x95B680
        v1 = 0x960000;
        lw(v1, v1, -19388);  // 0x95B444
        divu(v1, a0);
        mflo(a1);
        v1 = 0x960000;
        sw(a1, v1, -18812);  // 0x95B684
        v1 = 0x960000;
        lw(a1, v1, -19956);  // 0x95B20C
        v1 = 0x960000;
        sw(a1, v1, -18808);  // 0x95B688
        v1 = 0x960000;
        lw(a1, v1, -19384);  // 0x95B448
        v1 = 5;
        divu(a1, v1);
        mflo(a2);
        a1 = 0x960000;
        sw(a2, a1, -18804);  // 0x95B68C
        a1 = 0x960000;
        lw(a2, a1, -19952);  // 0x95B210
        a1 = 0x960000;
        sw(a2, a1, -18800);  // 0x95B690
        a1 = 0x960000;
        lw(a1, a1, -19380);  // 0x95B44C
        divu(a1, v1);
        mflo(a2);
        a1 = 0x960000;
        sw(a2, a1, -18796);  // 0x95B694
        a1 = 0x960000;
        lw(a2, a1, -19944);  // 0x95B218
        a1 = 0x960000;
        sw(a2, a1, -18792);  // 0x95B698
        a1 = 0x960000;
        lw(a1, a1, -19372);  // 0x95B454
        divu(a1, v1);
        mflo(a2);
        a1 = 0x960000;
        sw(a2, a1, -18788);  // 0x95B69C
        a1 = 0x960000;
        lw(a2, a1, -19940);  // 0x95B21C
        a1 = 0x960000;
        sw(a2, a1, -18784);  // 0x95B6A0
        a1 = 0x960000;
        lw(a1, a1, -19368);  // 0x95B458
        divu(a1, a0);
        mflo(a2);
        a1 = 0x960000;
        sw(a2, a1, -18780);  // 0x95B6A4
        a1 = 0x960000;
        lw(a2, a1, -19904);  // 0x95B240
        a1 = 0x960000;
        sw(a2, a1, comu::kLoRankEvents);  // 0x95B6A8 {section 114, size / 24}: per link, the rank events
        a1 = 0x960000;
        lw(a2, a1, -19332);  // 0x95B47C
        a1 = 24;
        divu(a2, a1);
        mflo(a2);
        a1 = 0x960000;
        sw(a2, a1, comu::kLoRankEventCount);  // 0x95B6AC the row count of section 114
        a1 = 0x960000;
        lw(a2, a1, -19900);  // 0x95B244
        a1 = 0x960000;
        sw(a2, a1, -18768);  // 0x95B6B0
        a1 = 0x960000;
        lw(a1, a1, -19328);  // 0x95B480
        a2 = srl(a1, 1);
        a1 = 0x960000;
        sw(a2, a1, -18764);  // 0x95B6B4
        a1 = 0x960000;
        lw(a2, a1, -19896);  // 0x95B248
        a1 = 0x960000;
        sw(a2, a1, -18760);  // 0x95B6B8
        a1 = 0x960000;
        lw(a1, a1, -19324);  // 0x95B484
        a2 = srl(a1, 4);
        a1 = 0x960000;
        sw(a2, a1, -18756);  // 0x95B6BC
        a1 = 0x960000;
        lw(a2, a1, -19804);  // 0x95B2A4
        a1 = 0x960000;
        sw(a2, a1, -18752);  // 0x95B6C0
        a1 = 0x960000;
        lw(a1, a1, -19232);  // 0x95B4E0
        divu(a1, a0);
        mflo(a1);
        a0 = 0x960000;
        sw(a1, a0, -18748);  // 0x95B6C4
        a0 = 0x960000;
        lw(a1, a0, -19892);  // 0x95B24C
        a0 = 0x960000;
        sw(a1, a0, comu::kLoPartners);  // 0x95B6C8 {section 117, size / 2}: {link 6..11, rank} pairs
        a0 = 0x960000;
        lw(a0, a0, -19320);  // 0x95B488
        a1 = srl(a0, 1);
        a0 = 0x960000;
        sw(a1, a0, comu::kLoPartnerCount);  // 0x95B6CC the pair count of section 117
        a0 = 0x960000;
        lw(a1, a0, -19884);  // 0x95B254
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec119);  // 0x95B6F8 section 119: 6-byte event triples per link
        a0 = 0x960000;
        lw(a1, a0, -19852);  // 0x95B274
        a0 = 0x960000;
        sw(a1, a0, -18692);  // 0x95B6FC
        a0 = 0x960000;
        lw(a1, a0, -19856);  // 0x95B270
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec126);  // 0x95B700 section 126: u8 per link
        a0 = 0x960000;
        lw(a1, a0, -19880);  // 0x95B258
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec120);  // 0x95B704 section 120: 6-byte event triples per link
        a0 = 0x960000;
        lw(a1, a0, -19876);  // 0x95B25C
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec121);  // 0x95B708 section 121: 6-byte event triples, 4 per link 6..11
        a0 = 0x960000;
        lw(a1, a0, -19872);  // 0x95B260
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec122);  // 0x95B70C section 122: 6-byte event triples per link 6..11
        a0 = 0x960000;
        lw(a1, a0, -19868);  // 0x95B264
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec123);  // 0x95B710 {section 123, size / 26}: {u8 link, ..., u16 flag ids +4 + 2k}
        a0 = 0x960000;
        lw(a1, a0, -19296);  // 0x95B4A0
        a0 = 26;
        divu(a1, a0);
        mflo(a1);
        a0 = 0x960000;
        sw(a1, a0, comu::kLoSec123Count);  // 0x95B714 the row count of section 123
        a0 = 0x960000;
        lw(a1, a0, -19848);  // 0x95B278
        a0 = 0x960000;
        sw(a1, a0, comu::kLoDateLinks);  // 0x95B6D8 {section 128, size / 5}: {month, day, link, min rank, max rank}
        a0 = 0x960000;
        lw(a0, a0, -19276);  // 0x95B4B4
        divu(a0, v1);
        mflo(a0);
        v1 = 0x960000;
        sw(a0, v1, comu::kLoDateLinkCount);  // 0x95B6DC the row count of section 128
        v1 = 0x960000;
        lw(a0, v1, -19860);  // 0x95B26C
        v1 = 0x960000;
        sw(a0, v1, -18736);  // 0x95B6D0
        v1 = 0x960000;
        lw(v1, v1, -19288);  // 0x95B4A8
        a1 = 12;
        divu(v1, a1);
        mflo(a0);
        v1 = 0x960000;
        sw(a0, v1, -18732);  // 0x95B6D4
        v1 = 0x960000;
        lw(a0, v1, -19864);  // 0x95B268
        v1 = 0x960000;
        sw(a0, v1, comu::kLoLinks);  // 0x95B718 section 124: 64 x 32-byte social link records
        v1 = 0x960000;
        lw(a0, v1, -19844);  // 0x95B27C
        v1 = 0x960000;
        sw(a0, v1, -18720);  // 0x95B6E0
        v1 = 0x960000;
        lw(a0, v1, -19836);  // 0x95B284
        v1 = 0x960000;
        sw(a0, v1, -18716);  // 0x95B6E4
        v1 = 0x960000;
        lw(v1, v1, -19264);  // 0x95B4C0
        divu(v1, a1);
        mflo(a0);
        v1 = 0x960000;
        sw(a0, v1, -18712);  // 0x95B6E8
        v1 = 0x960000;
        lw(a0, v1, -19832);  // 0x95B288
        v1 = 0x960000;
        sw(a0, v1, -18708);  // 0x95B6EC
        v1 = 0x960000;
        lw(a0, v1, -19828);  // 0x95B28C
        v1 = 0x960000;
        sw(a0, v1, comu::kLoSec133);  // 0x95B6F4 section 133
        v1 = 0x960000;
        lw(a0, v1, -19824);  // 0x95B290
        v1 = 0x960000;
        sw(a0, v1, comu::kLoSec134);  // 0x95B6F0 section 134
        v1 = 0x960000;
        lw(a0, v1, -19820);  // 0x95B294
        v1 = 0x960000;
        sw(a0, v1, -18660);  // 0x95B71C
        v1 = 0x960000;
        lw(a0, v1, -19248);  // 0x95B4D0
        v1 = 6;
        divu(a0, v1);
        mflo(a0);
        v1 = 0x960000;
        sw(a0, v1, -18656);  // 0x95B720
        v1 = 0x960000;
        lw(a0, v1, -19816);  // 0x95B298
        v1 = 0x960000;
        sw(a0, v1, -18652);  // 0x95B724
        v1 = 0x960000;
        lw(v1, v1, -19244);  // 0x95B4D4
        a0 = srl(v1, 3);
        v1 = 0x960000;
        sw(a0, v1, -18648);  // 0x95B728
    } else {
        // 0x003bd2f0
        charge(ctx, 8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12800);  // "error!! comuTableBinFile Version Invalid  SupportVersion=%d (%d)"
        jal(ctx, 0x3BD2F8u, gen::fn_printf_005225a8);
        v1 = 0x960000;
        sw(zero, v1, comu::kLoTable);  // 0x95B070 comuTable.bin in the pak
    }
    // 0x003bd858 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BD870 sub_3BD870 -- 16 bytes; leaf frame (no stack)
// [comuGetTables] The loaded table block (0x95B070).
void sub_3BD870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bd870
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -20368);  // &0x95B070
}

// 0x003BD890 sub_3BD890 -- 16 bytes; leaf frame (no stack)
// The {pointer, count} pair of the dated conditions (0x95B660).
void sub_3BD890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bd890
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18848);  // &0x95B660
}

// 0x003BD8A0 sub_3BD8A0 -- 16 bytes; leaf frame (no stack)
// The {pointer, count} pair of the dated flags (0x95B668).
void sub_3BD8A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bd8a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18840);  // &0x95B668
}

// 0x003BDA60 sub_3BDA60 -- 276 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (a, b, c, d) Looks up section 112 for the row {u8 a, u8 b, u16 c, u8 d}: its u16 +6 when the row has no flag (+8 ==
// 0) or the flag is clear (MT_Misc_BitChk != 1), else the next match; -1 when none.
void sub_3BDA60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bda60
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
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
    v0 = 0x960000;
    lw(s6, v0, comu::kLoMapEventCount);  // 0x95B674 the row count of section 112
    s1 = 0;
    for (;;) {
        // 0x003bdb38
        charge(ctx, 3);
        v0 = slt(s1, s6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bdaa8
        charge(ctx, 9);
        v0 = 0x960000;
        lw(v1, v0, comu::kLoMapEvents);  // 0x95B670 {section 112, size / 10}: 10-byte event rows
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        s0 = sll(v0, 1);
        v1 = addu(v1, s0);
        lbu(v0, v1, 0);
        if (s5 == v0) {
            // 0x003bdacc
            charge(ctx, 3);
            lbu(v0, v1, 1);
            if (s4 != v0) {
                goto L_003bdb34;
            }
            // 0x003bdad8
            charge(ctx, 3);
            lhu(v0, v1, 2);
            if (s3 != v0) {
                goto L_003bdb34;
            }
            // 0x003bdae4
            charge(ctx, 3);
            lbu(v0, v1, 4);
            if (s2 != v0) {
                goto L_003bdb34;
            }
            // 0x003bdaf0
            charge(ctx, 3);
            lhu(a0, v1, 8);
            if (a0 == 0) {
                goto L_003bdb28;
            }
            // 0x003bdafc
            charge(ctx, 5);
            jal(ctx, 0x3BDAFCu, gen::fn_MT_Misc_BitChk_003951d0);
            v1 = 1;
            if (v0 == v1) {
                goto L_003bdb34;
            }
            goto L_003bdb10_7;
        }
    L_003bdb34:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003bdb44
    charge(ctx, 1);
    v0 = si(-1);
    // 0x003bdb48 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_003bdb10_7:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, comu::kLoMapEvents);  // 0x95B670 {section 112, size / 10}: 10-byte event rows
    v0 = addu(s0, v0);
    lhu(v0, v0, 6);
    // 0x003bdb48 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_003bdb28:
    charge(ctx, 3);
    lhu(v0, v1, 6);
    // 0x003bdb48 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003BDB80 sub_3BDB80 -- 20 bytes; leaf frame (no stack)
// The f32 at the start of section 133 (in $f0).
void sub_3BDB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    Fpr f0{ctx, 0};
    // 0x003bdb80
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, comu::kLoSec133);  // 0x95B6F4 section 133
    lwc1(f0, v0, 0);
}

// 0x003BDBA0 sub_3BDBA0 -- 16 bytes; leaf frame (no stack)
// Section 134's pointer.
void sub_3BDBA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bdba0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, comu::kLoSec134);  // 0x95B6F0 section 134
}

// 0x003BDBB0 sub_3BDBB0 -- 20 bytes; leaf frame (no stack)
// The u16 at the start of section 137.
void sub_3BDBB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bdbb0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, comu::kLoSec137);  // 0x95B29C section 137
    lhu(v0, v0, 0);
}

// 0x003BDBD0 sub_3BDBD0 -- 364 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (link) For a link 6..11 that is active: every other active link 6..11 whose rank reaches its threshold (section
// 140) is set to the rank of section 138 (sub_171960).
void sub_3BDBD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bdbd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BDBECu, gen::fn_sub_16DCE0_0016dce0);
    if (v0 != 0) {
        // 0x003bdbfc
        charge(ctx, 6);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3BDC04u, gen::fn_sub_172A50_00172a50);
        if (v0 != 0) {
            // 0x003bdc14
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x003bdd18
                charge(ctx, 3);
                v1 = slti(s0, 6);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003bdc20
                charge(ctx, 3);
                v1 = addiu(s0, 6);
                if (s1 != v1) {
                    // 0x003bdc2c
                    charge(ctx, 6);
                    a0 = dsll32(v1, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3BDC34u, gen::fn_sub_16DCE0_0016dce0);
                    if (v0 == 0) {
                        // 0x003bdc44
                        charge(ctx, 5);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 12928);  // "comuFunction.c"
                        a1 = 438;
                        jal(ctx, 0x3BDC50u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x003bdc58
                    charge(ctx, 7);
                    v0 = addiu(s0, 6);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3BDC64u, gen::fn_sub_16E100_0016e100);
                    if (v0 != 0) {
                        // 0x003bdc80
                        charge(ctx, 7);
                        v0 = addiu(s0, 6);
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x3BDC8Cu, gen::fn_sub_172A50_00172a50);
                        if (v0 != 0) {
                            // 0x003bdca8
                            charge(ctx, 14);
                            v0 = addiu(s0, 6);
                            a0 = dsll32(v0, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x3BDCB4u, gen::fn_sub_16DBA0_0016dba0);
                            a0 = dsll32(v0, 24);
                            a0 = dsra32(a0, 24);
                            v1 = 0x960000;
                            lw(v1, v1, comu::kLoSec140);  // 0x95B2A8 section 140
                            v1 = addu(v1, s0);
                            lbu(v1, v1, 0);
                            v1 = slt(a0, v1);
                            if (v1 != 0) {
                                // 0x003bdcec
                                charge(ctx, 1);
                                v1 = 0;
                            } else {
                                // 0x003bdce0
                                charge(ctx, 3);
                                v1 = 1;
                            }
                        } else {
                            // 0x003bdc9c
                            charge(ctx, 3);
                            v1 = 0;
                        }
                    } else {
                        // 0x003bdc74
                        charge(ctx, 3);
                        v1 = 0;
                    }
                    // 0x003bdcf0
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x003bdcf8
                        charge(ctx, 7);
                        v0 = 0x960000;
                        lw(v0, v0, comu::kLoSec138);  // 0x95B2A0 section 138
                        lh(v0, v0, 0);
                        a0 = addiu(s0, 6);
                        a1 = v0;
                        jal(ctx, 0x3BDD0Cu, gen::fn_sub_171960_00171960);
                    }
                }
                // 0x003bdd14
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
        }
    }
    // 0x003bdd24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BDD40 sub_3BDD40 -- 16 bytes; leaf frame (no stack)
// The call tables (0x95B678: four {pointer, count} pairs).
void sub_3BDD40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bdd40
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18824);  // &0x95B678
}

// 0x003BDD50 sub_3BDD50 -- 16 bytes; leaf frame (no stack)
// The rank-event table pair (0x95B6A8).
void sub_3BDD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bdd50
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18776);  // &0x95B6A8
}

// 0x003BDD60 sub_3BDD60 -- 44 bytes; frame 0x10: ra sp+0x0
// (a0, a2) Starts a script procedure of SiteibiEvent.bf (scrCreateTaskFromHeader(a0, the .bf, a1)).
void sub_3BDD60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bdd60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    v0 = 0x960000;
    lw(a1, v0, comu::kLoScript);  // 0x95B074 SiteibiEvent.bf in the pak
    jal(ctx, 0x3BDD74u, gen::fn_scrCreateTaskFromHeader_0035bb40);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BDD90 sub_3BDD90 -- 52 bytes; leaf frame (no stack)
// (link) The per-link table of sections 64..93 (link < 31, else 0).
void sub_3BDD90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003bdd90
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x960000;
    v1 = addiu(v1, -20368);  // &0x95B070
    at = slti(a0, 31);
    if (at != 0) {
        // 0x003bddb0
        charge(ctx, 3);
        v0 = sll(a0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 1392);
    } else {
        // 0x003bdda4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bddbc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BDDD0 sub_3BDDD0 -- 16 bytes; leaf frame (no stack)
// Section 130's pointer.
void sub_3BDDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003bddd0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, comu::kLoSec130);  // 0x95B280 section 130
}

// 0x003BDDE0 sub_3BDDE0 -- 228 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuRefreshAvailability] For the 30 links: an active link (sub_16E100) that is not reversed / broken (sub_1717C0,
// sub_172160) and below rank 10 is marked available (sub_171960(i, 1)); one whose counter (sub_171AC0) is <= 0 is
// also flagged (sub_171C40(i, 1)).
void sub_3BDDE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bdde0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x003bdea4
        charge(ctx, 3);
        v1 = slti(s0, 30);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bddf8
        charge(ctx, 6);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3BDE00u, gen::fn_sub_16E100_0016e100);
        if (v0 != 0) {
            // 0x003bde10
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x3BDE14u, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 != v1) {
                // 0x003bde28
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x3BDE2Cu, gen::fn_sub_172160_00172160);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003bde40
                    charge(ctx, 9);
                    a0 = dsll32(s0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3BDE48u, gen::fn_sub_16DBA0_0016dba0);
                    a0 = dsll32(v0, 24);
                    a0 = dsra32(a0, 24);
                    v1 = 10;
                    if (a0 != v1) {
                        // 0x003bde64
                        charge(ctx, 11);
                        a0 = s0;
                        a1 = 1;
                        jal(ctx, 0x3BDE6Cu, gen::fn_sub_171960_00171960);
                        a0 = s0;
                        jal(ctx, 0x3BDE78u, gen::fn_sub_171AC0_00171ac0);
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        if (i64(v1) <= 0) {
                            // 0x003bde90
                            charge(ctx, 4);
                            a0 = s0;
                            a1 = 1;
                            jal(ctx, 0x3BDE98u, gen::fn_sub_171C40_00171c40);
                        }
                    }
                }
            }
        }
        // 0x003bdea0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003bdeb0
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BDED0 sub_3BDED0 -- 236 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuGetLinkState] (link) 5 at rank 10 (max), 4 broken (sub_172160), 3 reversed (sub_1717C0), else when available
// (sub_172660) 2 if a partner flag of the next rank is pending (sub_3BE1C0) or 1, else 0.
void sub_3BDED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bded0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BDEECu, gen::fn_sub_16DBA0_0016dba0);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    v0 = 10;
    if (s0 != v0) {
        // 0x003bdf14
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x3BDF18u, gen::fn_sub_172160_00172160);
        v1 = 1;
        if (v0 != v1) {
            // 0x003bdf38
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x3BDF3Cu, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 != v1) {
                // 0x003bdf5c
                charge(ctx, 6);
                a0 = s1;
                jal(ctx, 0x3BDF60u, gen::fn_sub_172660_00172660);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003bdfa0
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x003bdf74
                    charge(ctx, 7);
                    a1 = addiu(s0, 1);
                    a0 = s1;
                    jal(ctx, 0x3BDF7Cu, gen::fn_sub_3BE1C0_003be1c0);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x003bdf90
                        charge(ctx, 1);
                        v1 = 2;
                    }
                    // 0x003bdf94
                    charge(ctx, 3);
                    v0 = v1;
                }
            } else {
                // 0x003bdf50
                charge(ctx, 3);
                v0 = 3;
            }
        } else {
            // 0x003bdf2c
            charge(ctx, 3);
            v0 = 4;
        }
    } else {
        // 0x003bdf08
        charge(ctx, 3);
        v0 = 5;
    }
    // 0x003bdfa4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BDFC0 sub_3BDFC0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (link) The link's byte of section 126 (asserts comuFunction.c 657 on an invalid link).
void sub_3BDFC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bdfc0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BDFD8u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003bdfe8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 657;
        jal(ctx, 0x3BDFF4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bdffc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 0x960000;
    lw(v0, v0, comu::kLoSec126);  // 0x95B700 section 126: u8 per link
    v0 = addu(v0, s0);
    lbu(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BE020 sub_3BE020 -- 384 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (rank, req, link) For links 6..11: the first row {link, min rank} of section 117 for this link that the link's rank
// reaches (rank 0 when inactive), when the link is neither reversed nor broken (or rank 0): the partner event triple
// of section 122 into req +42 and req +1 = link; 1, else 0.
void sub_3BE020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003be020
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a1;
    s4 = a2;
    v0 = 0x960000;
    lw(s1, v0, comu::kLoPartners);  // 0x95B6C8 {section 117, size / 2}: {link 6..11, rank} pairs
    v0 = 0x960000;
    lw(s0, v0, comu::kLoPartnerCount);  // 0x95B6CC the pair count of section 117
    s3 = 0;
    for (;;) {
        // 0x003be164
        charge(ctx, 3);
        v0 = slt(s3, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003be068
        charge(ctx, 5);
        v0 = sll(s3, 1);
        v0 = addu(s1, v0);
        lbu(s2, v0, 0);
        if (s4 == s2) {
            // 0x003be07c
            charge(ctx, 7);
            lbu(s6, v0, 1);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3BE088u, gen::fn_sub_172A50_00172a50);
            if (v0 == 0) {
                goto L_003be160;
            }
            // 0x003be098
            charge(ctx, 7);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3BE0A0u, gen::fn_sub_16E100_0016e100);
            v1 = 1;
            if (v0 != v1) {
                // 0x003be0d4
                charge(ctx, 1);
                v1 = 0;
            } else {
                // 0x003be0b4
                charge(ctx, 8);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3BE0BCu, gen::fn_sub_16DBA0_0016dba0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
            }
            // 0x003be0d8
            charge(ctx, 3);
            v0 = slt(v1, s6);
            if (v0 != 0) {
                goto L_003be160;
            }
            // 0x003be0e4
            charge(ctx, 2);
            if (i64(v1) <= 0) {
                goto L_003be11c;
            }
            // 0x003be0ec
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3BE0F0u, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 == v1) {
                goto L_003be160;
            }
            // 0x003be104
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3BE108u, gen::fn_sub_172160_00172160);
            v1 = 1;
            if (v0 == v1) {
                goto L_003be160;
            }
            goto L_003be11c;
        }
    L_003be160:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x003be170
    charge(ctx, 1);
    v0 = 0;
    // 0x003be174 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_003be11c:
    charge(ctx, 17);
    v1 = addiu(s2, -6);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 1);
    v0 = 0x960000;
    lw(v0, v0, comu::kLoSec122);  // 0x95B70C section 122: 6-byte event triples per link 6..11
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    lh(v1, v0, 2);
    lh(v0, v0, 4);
    sh(a0, s5, 42);
    sh(v1, s5, 44);
    sh(v0, s5, 46);
    sb(s2, s5, 1);
    v0 = 1;
    // 0x003be174 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003BE1A0 sub_3BE1A0 -- 20 bytes; leaf frame (no stack)
// (req) req +4 == 3.
void sub_3BE1A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x003be1a0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, creq::kResult);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
}

// 0x003BE1C0 sub_3BE1C0 -- 220 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (link, rank) 1 when a row of section 123 for this link has a non-zero flag id for `rank` (rank >= 2; +4 + 2 rank)
// whose flag is clear (datGetFlag), else 0.
void sub_3BE1C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003be1c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    v0 = 0x960000;
    lw(s1, v0, comu::kLoSec123Count);  // 0x95B714 the row count of section 123
    at = slti(a1, 2);
    if (at == 0) {
        // 0x003be1fc
        charge(ctx, 4);
        s2 = 0;
        s0 = sll(a1, 1);
        for (;;) {
            // 0x003be26c
            charge(ctx, 3);
            v0 = slt(s2, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003be20c
            charge(ctx, 11);
            v0 = 0x960000;
            lw(a0, v0, comu::kLoSec123);  // 0x95B710 {section 123, size / 26}: {u8 link, ..., u16 flag ids +4 + 2k}
            v0 = sll(s2, 1);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            v1 = sll(v0, 1);
            v0 = addu(a0, v1);
            lbu(v0, v0, 0);
            if (s3 == v0) {
                // 0x003be238
                charge(ctx, 5);
                v0 = addu(s0, a0);
                v0 = addu(v0, v1);
                lhu(a0, v0, 4);
                if (a0 == 0) {
                    goto L_003be268;
                }
                // 0x003be24c
                charge(ctx, 4);
                jal(ctx, 0x3BE24Cu, gen::fn_datGetFlag_0016f190);
                if (v0 != 0) {
                    goto L_003be268;
                }
                goto L_003be25c_6;
            }
        L_003be268:
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x003be278
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003be1f0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003be27c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_003be25c_6:
    charge(ctx, 3);
    v0 = 1;
    // 0x003be27c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003BE2A0 sub_3BE2A0 -- 1592 bytes; frame 0xD0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuMakeEventRequest] (mode, choice, link, kind, req) Fills the 56-byte event request for a link of rank > 0
// (asserts on invalid links): +0 link, +2 kind, by kind: 0 the rank event of sections 0..29 (14-byte rows, 10 per
// rank, the sub-step min 9) + the partner event (sub_3BE020; result 3) else result 2; 1 the 24-byte row of sections
// 32..61 for the rank (four triples, result 3; mode 1 also raises the rank, sub_16E410); 2 section 123's triple; 3 /
// 4 the per-link triples of sections 119 / 120; 5 the triple at +1268 of the link's rank table; 6 section 121's
// triple for links 6..11 (sub_3C2570); 7 one of the link's rank-event rows of section 114 (mode 1: `choice`, else the
// rank's; asserts 947 / 970); +4 = the result (number of triples). 1, or 0 for rank 0.
void sub_3BE2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003be2a0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s6 = a0;
    s7 = a1;
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s5 = 0x960000;
    s5 = addiu(s5, -20368);  // &0x95B070
    s1 = 0;
    a0 = dsll32(s4, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BE2F0u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003be300
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 810;
        jal(ctx, 0x3BE30Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003be314
    charge(ctx, 15);
    a0 = s2;
    a1 = 0;
    a2 = 56;
    jal(ctx, 0x3BE320u, gen::fn_memset_00521408);
    sb(s4, s2, creq::kLink);
    sb(s3, s2, creq::kKind);
    a0 = dsll32(s4, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BE338u, gen::fn_sub_16DBA0_0016dba0);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    if (i64(s0) > 0) {
        // 0x003be35c
        charge(ctx, 3);
        at = sltiu(s3, 8);
        if (at != 0) {
            // 0x003be368
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -19632);  // &0x7BB350
            v0 = sll(s3, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3BE384u:  // table[0]
                // 0x003be384
                charge(ctx, 6);
                v0 = sll(s4, 2);
                v0 = addu(v0, s5);
                s3 = addiu(v0, 1152);
                lw(v0, v0, 1152);
                if (v0 == 0) {
                    // 0x003be39c
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12928);  // "comuFunction.c"
                    a1 = 825;
                    jal(ctx, 0x3BE3A8u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003be3b0
                charge(ctx, 9);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3BE3B8u, gen::fn_sub_16DD20_0016dd20);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                at = slti(a0, 10);
                if (at == 0) {
                    // 0x003be3d4
                    charge(ctx, 1);
                    a0 = 9;
                }
                // 0x003be3d8
                charge(ctx, 26);
                v1 = addiu(s0, -1);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v1 = addu(a0, v0);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 1);
                lw(v0, s3, 0);
                a1 = addu(v0, v1);
                s1 = addiu(s1, 2);
                lh(a0, a1, 8);
                lh(v1, a1, 10);
                lh(v0, a1, 12);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                lh(a0, a1, 14);
                lh(v1, a1, 16);
                lh(v0, a1, 18);
                sh(a0, s2, creq::kEvent2);
                sh(v1, s2, creq::kEvent2Minor);
                sh(v0, s2, creq::kEvent2Sub);
                lbu(a2, a1, 20);
                if (a2 != 0) {
                    // 0x003be440
                    charge(ctx, 7);
                    a0 = s4;
                    a1 = s2;
                    jal(ctx, 0x3BE448u, gen::fn_sub_3BE020_003be020);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x003be45c
                        charge(ctx, 3);
                        s1 = addiu(s1, 1);
                    }
                }
            L_003be8a0:
                charge(ctx, 2);
                sw(s1, s2, creq::kResult);
                v0 = 1;
                break;
            case 0x3BE468u:  // table[1]
                // 0x003be468
                charge(ctx, 6);
                v0 = sll(s4, 2);
                v0 = addu(v0, s5);
                s1 = addiu(v0, 1272);
                lw(v0, v0, 1272);
                if (v0 == 0) {
                    // 0x003be480
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12928);  // "comuFunction.c"
                    a1 = 849;
                    jal(ctx, 0x3BE48Cu, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003be494
                charge(ctx, 34);
                v1 = addiu(s0, -1);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 3);
                lw(v0, s1, 0);
                a1 = addu(v0, v1);
                lh(a0, a1, 8);
                lh(v1, a1, 10);
                lh(v0, a1, 12);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                lh(a0, a1, 14);
                lh(v1, a1, 16);
                lh(v0, a1, 18);
                sh(a0, s2, creq::kEvent2);
                sh(v1, s2, creq::kEvent2Minor);
                sh(v0, s2, creq::kEvent2Sub);
                lh(a0, a1, 20);
                lh(v1, a1, 22);
                lh(v0, a1, 24);
                sh(a0, s2, creq::kEvent3);
                sh(v1, s2, creq::kEvent3Minor);
                sh(v0, s2, creq::kEvent3Sub);
                lh(a0, a1, 26);
                lh(v1, a1, 28);
                lh(v0, a1, 30);
                sh(a0, s2, creq::kEvent4);
                sh(v1, s2, creq::kEvent4Minor);
                sh(v0, s2, creq::kEvent4Sub);
                s1 = 3;
                v0 = 1;
                if (s6 == v0) {
                    // 0x003be51c
                    charge(ctx, 9);
                    a0 = dsll32(s4, 16);
                    a0 = dsra32(a0, 16);
                    v0 = addiu(s0, 1);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    jal(ctx, 0x3BE530u, gen::fn_sub_16E410_0016e410);
                }
                goto L_003be8a0;
            case 0x3BE540u:  // table[2]
                // 0x003be540
                charge(ctx, 7);
                v0 = 0x960000;
                lw(a1, v0, comu::kLoSec123Count);  // 0x95B714 the row count of section 123
                a2 = 0;
                v0 = 0x960000;
                lw(a0, v0, comu::kLoSec123);  // 0x95B710 {section 123, size / 26}: {u8 link, ..., u16 flag ids +4 + 2k}
                for (;;) {
                    // 0x003be590
                    charge(ctx, 3);
                    v0 = slt(a2, a1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003be55c
                    charge(ctx, 9);
                    v0 = sll(a2, 1);
                    v0 = addu(v0, a2);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, a2);
                    v0 = sll(v0, 1);
                    v1 = addu(a0, v0);
                    lbu(v0, v1, 0);
                    if (s4 == v0) {
                        goto L_003be580_19;
                    }
                    // 0x003be58c
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                }
                // 0x003be59c
                charge(ctx, 1);
                s0 = 0;
            L_003be5a0:
                charge(ctx, 2);
                if (s0 == 0) {
                    // 0x003be5a8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12928);  // "comuFunction.c"
                    a1 = 869;
                    jal(ctx, 0x3BE5B4u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003be5bc
                charge(ctx, 9);
                lh(a0, s0, 0);
                lh(v1, s0, 2);
                lh(v0, s0, 4);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                s1 = 1;
                goto L_003be8a0;
            case 0x3BE5E0u:  // table[3]
                // 0x003be5e0
                charge(ctx, 16);
                v0 = sll(s4, 1);
                v0 = addu(v0, s4);
                v1 = sll(v0, 1);
                v0 = 0x960000;
                lw(v0, v0, comu::kLoSec119);  // 0x95B6F8 section 119: 6-byte event triples per link
                v0 = addu(v0, v1);
                lh(a0, v0, 0);
                lh(v1, v0, 2);
                lh(v0, v0, 4);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                sb(zero, s2, creq::kEventSubHi);
                s1 = 1;
                goto L_003be8a0;
            case 0x3BE620u:  // table[4]
                // 0x003be620
                charge(ctx, 15);
                v0 = sll(s4, 1);
                v0 = addu(v0, s4);
                v1 = sll(v0, 1);
                v0 = 0x960000;
                lw(v0, v0, comu::kLoSec120);  // 0x95B704 section 120: 6-byte event triples per link
                v0 = addu(v0, v1);
                lh(a0, v0, 0);
                lh(v1, v0, 2);
                lh(v0, v0, 4);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                s1 = 1;
                goto L_003be8a0;
            case 0x3BE65Cu:  // table[5]
                // 0x003be65c
                charge(ctx, 6);
                v0 = sll(s4, 2);
                v0 = addu(v0, s5);
                s0 = addiu(v0, 1152);
                lw(v0, v0, 1152);
                if (v0 == 0) {
                    // 0x003be674
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12928);  // "comuFunction.c"
                    a1 = 893;
                    jal(ctx, 0x3BE680u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003be688
                charge(ctx, 10);
                lw(v0, s0, 0);
                lh(a0, v0, 1268);
                lh(v1, v0, 1270);
                lh(v0, v0, 1272);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                s1 = 1;
                goto L_003be8a0;
            case 0x3BE6B0u:  // table[6]
                // 0x003be6b0
                charge(ctx, 6);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3BE6B8u, gen::fn_sub_172A50_00172a50);
                if (v0 == 0) {
                    // 0x003be6c8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12928);  // "comuFunction.c"
                    a1 = 904;
                    jal(ctx, 0x3BE6D4u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003be6dc
                charge(ctx, 21);
                a0 = s4;
                jal(ctx, 0x3BE6E0u, gen::fn_sub_3C2570_003c2570);
                v1 = addiu(s4, -6);
                v1 = sll(v1, 2);
                v1 = addu(v0, v1);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 1);
                v0 = 0x960000;
                lw(v0, v0, comu::kLoSec121);  // 0x95B708 section 121: 6-byte event triples, 4 per link 6..11
                v0 = addu(v0, v1);
                lh(a0, v0, 0);
                lh(v1, v0, 2);
                lh(v0, v0, 4);
                sh(a0, s2, creq::kEvent);
                sh(v1, s2, creq::kEventMinor);
                sh(v0, s2, creq::kEventSub);
                s1 = 1;
                goto L_003be8a0;
            case 0x3BE730u:  // table[7]
                // 0x003be730
                charge(ctx, 8);
                v0 = 0x960000;
                v0 = addiu(v0, -18776);  // &0x95B6A8
                a0 = 0;
                lw(s1, v0, 0);  // 0x95B6A8
                lw(v1, v0, 4);  // 0x95B6AC
                a1 = 0;
                for (;;) {
                    // 0x003be78c
                    charge(ctx, 3);
                    v0 = slt(a1, v1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003be750
                    charge(ctx, 7);
                    v0 = sll(a1, 1);
                    v0 = addu(v0, a1);
                    v0 = sll(v0, 3);
                    v0 = addu(s1, v0);
                    lbu(v0, v0, 0);
                    if (s4 == v0) {
                        // 0x003be76c
                        charge(ctx, 3);
                        at = slti(a0, 32);
                        if (at == 0) {
                            break;
                        }
                        // 0x003be778
                        charge(ctx, 4);
                        v0 = sll(a0, 1);
                        v0 = addu(v0, sp);
                        sh(a1, v0, 144);
                        a0 = addiu(a0, 1);
                        goto L_003be788;
                    }
                L_003be788:
                    charge(ctx, 1);
                    a1 = addiu(a1, 1);
                }
                // 0x003be798
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x003be7c0
                    charge(ctx, 3);
                    v0 = 1;
                    if (s6 != v0) {
                        // 0x003be7f4
                        charge(ctx, 3);
                        v0 = slti(s0, 2);
                        if (v0 == 0) {
                            // 0x003be800
                            charge(ctx, 3);
                            v0 = slti(s0, 10);
                            if (v0 == 0) {
                                goto L_003be80c;
                            }
                            goto L_003be820;
                        }
                    L_003be80c:
                        charge(ctx, 5);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 12928);  // "comuFunction.c"
                        a1 = 970;
                        jal(ctx, 0x3BE818u, gen::fn_sub_19D3F0_0019d3f0);
                    L_003be820:
                        charge(ctx, 7);
                        v0 = sll(s0, 1);
                        v0 = addu(v0, sp);
                        lhu(v1, v0, 140);
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        a2 = addu(s1, v0);
                    } else {
                        // 0x003be7cc
                        charge(ctx, 10);
                        lw(v0, s7, 0);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, sp);
                        lhu(v1, v0, 144);
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 3);
                        a2 = addu(s1, v0);
                    }
                    // 0x003be83c
                    charge(ctx, 15);
                    lh(a0, a2, 2);
                    lh(v1, a2, 4);
                    lh(v0, a2, 6);
                    sh(a0, s2, creq::kEvent);
                    sh(v1, s2, creq::kEventMinor);
                    sh(v0, s2, creq::kEventSub);
                    lh(a0, a2, 8);
                    lh(v1, a2, 10);
                    lh(v0, a2, 12);
                    sh(a0, s2, creq::kEvent2);
                    sh(v1, s2, creq::kEvent2Minor);
                    sh(v0, s2, creq::kEvent2Sub);
                    a1 = 0;
                    for (;;) {
                        // 0x003be890
                        charge(ctx, 3);
                        v0 = slti(a1, 5);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003be878
                        charge(ctx, 6);
                        a0 = sll(a1, 1);
                        v0 = addu(a2, a0);
                        lhu(v1, v0, 14);
                        v0 = addu(s2, a0);
                        sh(v1, v0, 20);
                        a1 = addiu(a1, 1);
                    }
                    // 0x003be89c
                    charge(ctx, 1);
                    s1 = 2;
                    goto L_003be8a0;
                }
                // 0x003be7a0
                charge(ctx, 8);
                a0 = 0x6A0000;
                a0 = addiu(a0, 12928);  // "comuFunction.c"
                a1 = 947;
                jal(ctx, 0x3BE7ACu, gen::fn_sub_19D3F0_0019d3f0);
                v0 = 0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x003be8a8 (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(ra, sp, 0x80);
            lq(s7, sp, 0x70);
            lq(s6, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xD0);
            return;
        }
        goto L_003be8a0;
    }
    // 0x003be350
    charge(ctx, 3);
    v0 = 0;
    // 0x003be8a8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_003be580_19:
    charge(ctx, 3);
    s0 = addiu(v1, 2);
    goto L_003be5a0;
}

// 0x003BEA20 sub_3BEA20 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (row, col) The byte at 30 + 6 row + col (row < 4, the value < 42; asserts comuFunction.c 1017 / 1019).
void sub_3BEA20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bea20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = slti(s1, 4);
    if (v0 == 0) {
        // 0x003bea44
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 1017;
        jal(ctx, 0x3BEA50u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bea58
    charge(ctx, 9);
    v0 = sll(s1, 1);
    v0 = addu(v0, s1);
    v0 = sll(v0, 1);
    v0 = addu(v0, s0);
    s0 = addiu(v0, 30);
    lbu(v0, v0, 30);
    v0 = slti(v0, 42);
    if (v0 == 0) {
        // 0x003bea7c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 1019;
        jal(ctx, 0x3BEA88u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bea90 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lbu(v0, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BEAB0 sub_3BEAB0 -- 96 bytes; leaf frame (no stack)
// [comuFindLink] (a, b, out) The index of the first of the 64 link records with bytes {a, b} at +0 / +1 into *out: 1,
// else 0.
void sub_3BEAB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003beab0
    enter(ctx, 5);  // entry check point + this block's cycles
    t0 = 0;
    v0 = 0x960000;
    lw(a3, v0, comu::kLoLinks);  // 0x95B718 section 124: 64 x 32-byte social link records
    for (;;) {
        // 0x003beaf8
        charge(ctx, 3);
        v0 = slti(t0, 64);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003beac4
        charge(ctx, 5);
        v0 = sll(t0, 5);
        v1 = addu(a3, v0);
        lbu(v0, v1, 0);
        if (a0 == v0) {
            // 0x003bead8
            charge(ctx, 3);
            lbu(v0, v1, 1);
            if (a1 != v0) {
                goto L_003beaf4;
            }
            goto L_003beae4_3;
        }
    L_003beaf4:
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x003beb04
    charge(ctx, 1);
    v0 = 0;
    // 0x003beb08 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003beae4_3:
    charge(ctx, 4);
    sw(t0, a2, 0);
    v0 = 1;
    // 0x003beb08 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BEB10 sub_3BEB10 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuGetLinkRecord] (i) The 32-byte link record i (asserts comuFunction.c 1046 for i >= 64).
void sub_3BEB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003beb10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (i64(s0) >= 0) {
        // 0x003beb28
        charge(ctx, 3);
        v0 = slti(s0, 64);
        if (v0 == 0) {
            goto L_003beb34;
        }
        // 0x003beb48 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        v1 = sll(s0, 5);
        v0 = 0x960000;
        lw(v0, v0, comu::kLoLinks);  // 0x95B718 section 124: 64 x 32-byte social link records
        v0 = addu(v0, v1);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_003beb34:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 12928);  // "comuFunction.c"
    a1 = 1046;
    jal(ctx, 0x3BEB40u, gen::fn_sub_19D3F0_0019d3f0);
    // 0x003beb48 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v1 = sll(s0, 5);
    v0 = 0x960000;
    lw(v0, v0, comu::kLoLinks);  // 0x95B718 section 124: 64 x 32-byte social link records
    v0 = addu(v0, v1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BEB70 sub_3BEB70 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (link) Sets flag 2512 + link (the link's "met today" flag; asserts on an invalid link).
void sub_3BEB70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003beb70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BEB88u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003beb98
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 1058;
        jal(ctx, 0x3BEBA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bebac
    charge(ctx, 9);
    a0 = addiu(s0, 2512);
    a1 = 1;
    jal(ctx, 0x3BEBB4u, gen::fn_datSetFlag_0016f1f0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BEBD0 sub_3BEBD0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (link) Flag 2512 + link == 1.
void sub_3BEBD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bebd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BEBE8u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 == 0) {
        // 0x003bebf8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 1067;
        jal(ctx, 0x3BEC04u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bec0c
    charge(ctx, 6);
    a0 = addiu(s0, 2512);
    jal(ctx, 0x3BEC10u, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 != v1) {
        // 0x003bec30
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003bec24
        charge(ctx, 3);
        v0 = v1;
    }
    // 0x003bec34 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BEC50 sub_3BEC50 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Clears the flags 2512..2541 (all 30 links).
void sub_3BEC50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bec50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x003bec7c
        charge(ctx, 3);
        v1 = slti(s0, 30);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bec68
        charge(ctx, 5);
        a0 = addiu(s0, 2512);
        a1 = 0;
        jal(ctx, 0x3BEC70u, gen::fn_datSetFlag_0016f1f0);
        s0 = addiu(s0, 1);
    }
    // 0x003bec88
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BECA0 sub_3BECA0 -- 472 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuListDateLinks] (out) Lists today's links of section 128 ({month, day, link, min rank, max rank} == the
// calendar date, the rank in range, rank 9 only while available, flag 2512 + link clear and sub_3C2C50 agreeing) into
// out[]; the count, or 0 when sub_3C2B40 refuses.
void sub_3BECA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003beca0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s3 = 0;
    v0 = 0x960000;
    lw(s1, v0, comu::kLoDateLinkCount);  // 0x95B6DC the row count of section 128
    v0 = 0x960000;
    lw(s0, v0, comu::kLoDateLinks);  // 0x95B6D8 {section 128, size / 5}: {month, day, link, min rank, max rank}
    sw(zero, sp, 0xBC);
    sw(zero, sp, 0xB8);
    jal(ctx, 0x3BECECu, gen::fn_clndGetCurrentMonth_0017d920);
    s6 = v0;
    jal(ctx, 0x3BECF8u, gen::fn_clndGetCurrentDay_0017da40);
    s7 = v0;
    a0 = addiu(sp, 0xBC);
    a1 = addiu(sp, 0xB8);
    jal(ctx, 0x3BED0Cu, gen::fn_sub_3C2B40_003c2b40);
    if (v0 != 0) {
        // 0x003bed28
        charge(ctx, 3);
        s4 = 0;
        for (;;) {
            // 0x003bee34
            charge(ctx, 3);
            v0 = slt(s4, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bed34
            charge(ctx, 6);
            v0 = sll(s4, 2);
            v0 = addu(v0, s4);
            v1 = addu(s0, v0);
            lbu(v0, v1, 0);
            if (s6 == v0) {
                // 0x003bed4c
                charge(ctx, 3);
                lbu(v0, v1, 1);
                if (s7 == v0) {
                    // 0x003bed58
                    charge(ctx, 13);
                    lbu(s2, v1, 2);
                    lbu(fp, v1, 3);
                    lbu(v0, v1, 4);
                    sq(v0, sp, 0xA0);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3BED70u, gen::fn_sub_16DBA0_0016dba0);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    at = slt(v1, fp);
                    if (at == 0) {
                        // 0x003bed8c
                        charge(ctx, 4);
                        lq(v0, sp, 0xA0);
                        v0 = slt(v0, v1);
                        if (v0 == 0) {
                            // 0x003bed9c
                            charge(ctx, 3);
                            v0 = 9;
                            if (v1 == v0) {
                                // 0x003beda8
                                charge(ctx, 6);
                                a0 = s2;
                                jal(ctx, 0x3BEDACu, gen::fn_sub_172660_00172660);
                                v1 = 1;
                                if (v0 != v1) {
                                    goto L_003bedc0;
                                }
                                goto L_003bee30;
                            }
                        L_003bedc0:
                            charge(ctx, 6);
                            a0 = dsll32(s2, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x3BEDC8u, gen::fn_sub_16DCE0_0016dce0);
                            if (v0 == 0) {
                                // 0x003bedd8
                                charge(ctx, 5);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, 12928);  // "comuFunction.c"
                                a1 = 1067;
                                jal(ctx, 0x3BEDE4u, gen::fn_sub_19D3F0_0019d3f0);
                            }
                            // 0x003bedec
                            charge(ctx, 8);
                            a0 = addiu(s2, 2512);
                            jal(ctx, 0x3BEDF0u, gen::fn_datGetFlag_0016f190);
                            v0 = v0 ^ 0x1;
                            v1 = sltiu(v0, 1);
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x003bee0c
                                charge(ctx, 5);
                                a0 = s2;
                                jal(ctx, 0x3BEE10u, gen::fn_sub_3C2C50_003c2c50);
                                if (v0 != 0) {
                                    // 0x003bee20
                                    charge(ctx, 4);
                                    v0 = sll(s3, 2);
                                    v0 = addu(s5, v0);
                                    sw(s2, v0, 0);
                                    s3 = addiu(s3, 1);
                                }
                            }
                        }
                    }
                }
            }
        L_003bee30:
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x003bee40
        charge(ctx, 1);
        v0 = s3;
    } else {
        // 0x003bed1c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003bee44 (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
    sp = addiu(sp, 0xC0);
}

// 0x003BEE80 sub_3BEE80 -- 676 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (link, out_count) The personas of the link's arcana (PERSONA.TBL, not flagged 0x10 / 0x08, 0x40 only at rank 10) at
// or below the hero's level, then the lowest-level one above it, sorted by level, into 0x95B730 (max 15; asserts 1202
// / 1220 / 1245); returns 0x95B730.
void sub_3BEE80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003bee80
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s6 = a1;
    a0 = dsll32(s4, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3BEEBCu, gen::fn_sub_16DF30_0016df30);
    s7 = dsll32(v0, 24);
    s7 = dsra32(s7, 24);
    s2 = 0;
    a0 = 1;
    jal(ctx, 0x3BEED4u, gen::fn_sub_16C7E0_0016c7e0);
    a0 = v0;
    jal(ctx, 0x3BEEE0u, gen::fn_sub_16D280_0016d280);
    fp = v0 & 0xFF;
    s1 = si(-1);
    s0 = 9999;
    s3 = 1;
    for (;;) {
        // 0x003befdc
        charge(ctx, 3);
        v0 = slti(s3, 256);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bef00
        charge(ctx, 8);
        lw(v1, gp, comu::kGpPersonaTable);  // 0x7CE420 PERSONA.TBL section 0
        v0 = sll(s3, 3);
        v0 = subu(v0, s3);
        s5 = sll(v0, 1);
        v1 = addu(v1, s5);
        lbu(v0, v1, 2);
        if (s7 == v0) {
            // 0x003bef20
            charge(ctx, 4);
            lhu(v1, v1, 0);
            v0 = v1 & 0x10;
            if (v0 == 0) {
                // 0x003bef30
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 == 0) {
                    // 0x003bef3c
                    charge(ctx, 3);
                    v0 = v1 & 0x40;
                    if (v0 != 0) {
                        // 0x003bef48
                        charge(ctx, 9);
                        a0 = dsll32(s4, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x3BEF50u, gen::fn_sub_16DBA0_0016dba0);
                        v1 = dsll32(v0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = 10;
                        if (v1 == v0) {
                            goto L_003bef6c;
                        }
                        goto L_003befd8;
                    }
                L_003bef6c:
                    charge(ctx, 6);
                    lw(v0, gp, comu::kGpPersonaTable);  // 0x7CE420 PERSONA.TBL section 0
                    v0 = addu(v0, s5);
                    lbu(v0, v0, 3);
                    at = slt(fp, v0);
                    if (at != 0) {
                        // 0x003befc4
                        charge(ctx, 3);
                        at = slt(v0, s0);
                        if (at != 0) {
                            // 0x003befd0
                            charge(ctx, 2);
                            s0 = v0;
                            s1 = s3;
                        }
                    } else {
                        // 0x003bef84
                        charge(ctx, 3);
                        v0 = slti(s2, 15);
                        if (v0 == 0) {
                            // 0x003bef90
                            charge(ctx, 5);
                            a0 = 0x6A0000;
                            a0 = addiu(a0, 12928);  // "comuFunction.c"
                            a1 = 1202;
                            jal(ctx, 0x3BEF9Cu, gen::fn_sub_19D3F0_0019d3f0);
                        }
                        // 0x003befa4
                        charge(ctx, 8);
                        v1 = sll(s2, 1);
                        v0 = 0x960000;
                        v0 = addiu(v0, -18640);  // &0x95B730
                        v0 = addu(v0, v1);
                        sh(s3, v0, 0);
                        s2 = addiu(s2, 1);
                    }
                }
            }
        }
    L_003befd8:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x003befe8
    charge(ctx, 3);
    v0 = si(-1);
    if (s1 != v0) {
        // 0x003beff4
        charge(ctx, 3);
        v0 = slti(s2, 15);
        if (v0 == 0) {
            // 0x003bf000
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 12928);  // "comuFunction.c"
            a1 = 1220;
            jal(ctx, 0x3BF00Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003bf014
        charge(ctx, 6);
        v1 = sll(s2, 1);
        v0 = 0x960000;
        v0 = addiu(v0, -18640);  // &0x95B730
        v0 = addu(v0, v1);
        sh(s1, v0, 0);
        s2 = addiu(s2, 1);
    }
    // 0x003bf02c
    charge(ctx, 8);
    sw(s2, s6, 0);
    v0 = 0;
    lw(t3, gp, comu::kGpPersonaTable);  // 0x7CE420 PERSONA.TBL section 0
    t2 = 0x960000;
    t2 = addiu(t2, -18640);  // &0x95B730
    a0 = addiu(s2, -1);
    for (;;) {
        // 0x003bf0c0
        charge(ctx, 3);
        v1 = slt(v0, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003bf04c
        charge(ctx, 5);
        t4 = addiu(v0, 1);
        v1 = sll(v0, 1);
        t1 = addu(t2, v1);
        for (;;) {
            // 0x003bf0b0
            charge(ctx, 3);
            v1 = slt(t4, s2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003bf060
            charge(ctx, 17);
            lhu(t0, t1, 0);
            v1 = sll(t4, 1);
            a3 = addu(t2, v1);
            lhu(a2, a3, 0);
            v1 = sll(a2, 3);
            v1 = subu(v1, a2);
            v1 = sll(v1, 1);
            v1 = addu(t3, v1);
            lbu(a1, v1, 3);
            v1 = sll(t0, 3);
            v1 = subu(v1, t0);
            v1 = sll(v1, 1);
            v1 = addu(t3, v1);
            lbu(v1, v1, 3);
            at = slt(a1, v1);
            if (at != 0) {
                // 0x003bf0a4
                charge(ctx, 2);
                sh(a2, t1, 0);
                sh(t0, a3, 0);
            }
            // 0x003bf0ac
            charge(ctx, 1);
            t4 = addiu(t4, 1);
        }
        // 0x003bf0bc
        charge(ctx, 1);
        v0 = addiu(v0, 1);
    }
    // 0x003bf0cc
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x003bf0d4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 12928);  // "comuFunction.c"
        a1 = 1245;
        jal(ctx, 0x3BF0E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003bf0e8 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    v0 = 0x960000;
    v0 = addiu(v0, -18640);  // &0x95B730
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
    sp = addiu(sp, 0xA0);
}

// 0x003BF130 sub_3BF130 -- 76 bytes; frame 0x10: ra sp+0x0
// 1 when no sequence change is pending (sub_27C2B0 == 0) and sub_27C330 == -1.
void sub_3BF130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf130
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3BF138u, gen::fn_sub_27C2B0_0027c2b0);
    if (v0 == 0) {
        // 0x003bf148
        charge(ctx, 5);
        jal(ctx, 0x3BF148u, gen::fn_sub_27C330_0027c330);
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003bf168;
        }
        // 0x003bf15c
        charge(ctx, 3);
        v0 = 1;
        // 0x003bf16c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_003bf168:
    charge(ctx, 1);
    v0 = 0;
    // 0x003bf16c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BF180 sub_3BF180 -- 116 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s2 sp+0x4C, s1 sp+0x50, s0 sp+0x54
// (a, b, c) Requests sequence 3 (adminiChangeSeq) with the 28-byte packet {.., +12 a, +16 b, +20 c}.
void sub_3BF180(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf180
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = addiu(sp, 0x40);
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x3BF1ACu, gen::fn_memset_00521408);
    sw(s2, sp, 0x4C);
    sw(s1, sp, 0x50);
    sw(s0, sp, 0x54);
    a0 = 3;
    a1 = addiu(sp, 0x40);
    a2 = 28;
    a3 = 0;
    jal(ctx, 0x3BF1D0u, gen::fn_adminiChangeSeq_0027c080);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003BF200 sub_3BF200 -- 112 bytes; frame 0x10: ra sp+0x0
// (month, day, m2, d2) The date (m2, d2) matches: m2 == 255 means "weekday d2" (sub_17E050), else both equal.
void sub_3BF200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf200
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t0 = a0;
    v1 = a1;
    v0 = 255;
    if (a2 != v0) {
        // 0x003bf240
        charge(ctx, 2);
        if (t0 == a2) {
            // 0x003bf248
            charge(ctx, 2);
            if (v1 != a3) {
                goto L_003bf25c;
            }
            // 0x003bf250
            charge(ctx, 3);
            v0 = 1;
            // 0x003bf260 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
    L_003bf25c:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003bf21c
        charge(ctx, 9);
        a0 = a3;
        a1 = t0;
        a2 = v1;
        jal(ctx, 0x3BF228u, gen::fn_sub_17E050_0017e050);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    }
    // 0x003bf260 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003BF270 sub_3BF270 -- 256 bytes; leaf frame (no stack)
// [comuDateInRange] (month, day, m0, d0, m1, d1) 1 when (month, day) lies in the range (m0, d0) .. (m1, d1), the
// range wrapping over the year end when it ends before it starts; else 0. Quirks of the original: a range inside one
// month (m0 == m1, d0 <= d1) accepts every day from d0 to the month's end, and a wrapping range that starts and ends
// in the same month rejects that month's days before d0.
void sub_3BF270(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x003bf270
    enter(ctx, 3);  // entry check point + this block's cycles
    at = slt(t0, a2);
    if (at == 0) {
        // 0x003bf27c
        charge(ctx, 2);
        if (a2 == t0) {
            // 0x003bf284
            charge(ctx, 3);
            at = slt(t1, a3);
            if (at == 0) {
                goto L_003bf300;
            }
            goto L_003bf290;
        }
    L_003bf300:
        charge(ctx, 3);
        at = slt(a0, a2);
        if (at != 0) {
        L_003bf364:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003bf30c
            charge(ctx, 3);
            at = slt(t0, a0);
            if (at != 0) {
                goto L_003bf364;
            }
            // 0x003bf318
            charge(ctx, 2);
            if (a2 != a0) {
                // 0x003bf338
                charge(ctx, 2);
                if (t0 != a0) {
                    // 0x003bf358
                    charge(ctx, 3);
                    v0 = 1;
                } else {
                    // 0x003bf340
                    charge(ctx, 3);
                    v0 = slt(t1, a1);
                    if (v0 != 0) {
                        goto L_003bf364;
                    }
                    // 0x003bf34c
                    charge(ctx, 3);
                    v0 = 1;
                }
            } else {
                // 0x003bf320
                charge(ctx, 3);
                at = slt(a1, a3);
                if (at != 0) {
                    goto L_003bf364;
                }
                // 0x003bf32c
                charge(ctx, 3);
                v0 = 1;
            }
        }
        // 0x003bf368 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_003bf290:
    charge(ctx, 3);
    at = slt(a0, a2);
    if (at != 0) {
        // 0x003bf2c8
        charge(ctx, 3);
        v0 = slt(t0, a0);
        if (v0 != 0) {
            goto L_003bf364;
        }
        // 0x003bf2d4
        charge(ctx, 2);
        if (t0 != a0) {
            // 0x003bf2f4
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x003bf2dc
            charge(ctx, 3);
            v0 = slt(t1, a1);
            if (v0 != 0) {
                goto L_003bf364;
            }
            // 0x003bf2e8
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x003bf29c
        charge(ctx, 2);
        if (a2 != a0) {
            // 0x003bf2bc
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x003bf2a4
            charge(ctx, 3);
            at = slt(a1, a3);
            if (at != 0) {
                goto L_003bf364;
            }
            // 0x003bf2b0
            charge(ctx, 3);
            v0 = 1;
        }
    }
    // 0x003bf368 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003BF370 sub_3BF370 -- 412 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// A timer-sequence step: 0 starts (clears 0x7CE66C), 1 waits for sub_3C3E80 on the hero record +484, 2 arms a 2-frame
// wait, 3 waits it out and requests event 861 (sequence 3), 4 returns -1 when the change is done; 0 otherwise.
void sub_3BF370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf370
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BF37Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    jal(ctx, 0x3BF388u, gen::fn_sub_1717B0_001717b0);
    lw(a1, s0, seq::kState);
    v1 = 4;
    if (a1 != v1) {
        // 0x003bf3a0
        charge(ctx, 3);
        a0 = 3;
        if (a1 == a0) {
            // 0x003bf41c
            charge(ctx, 5);
            lw(v1, s0, seq::kTimer);
            lw(v0, s0, seq::kWait);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                // 0x003bf444
                charge(ctx, 3);
                v0 = addiu(v1, 1);
                sw(v0, s0, seq::kTimer);
                v0 = 0;
            } else {
                // 0x003bf430
                charge(ctx, 5);
                sw(zero, s0, seq::kTimer);
                sw(zero, s0, seq::kWait);
                v0 = 1;
            }
            // 0x003bf450
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003bf458
                charge(ctx, 20);
                a0 = addiu(sp, 0x20);
                a1 = 0;
                a2 = 28;
                jal(ctx, 0x3BF464u, gen::fn_memset_00521408);
                v0 = 861;
                sw(v0, sp, 0x2C);
                v0 = 1;
                sw(v0, sp, 0x30);
                sw(zero, sp, 0x34);
                a0 = 3;
                a1 = addiu(sp, 0x20);
                a2 = 28;
                a3 = 0;
                jal(ctx, 0x3BF490u, gen::fn_adminiChangeSeq_0027c080);
                v0 = 4;
                sw(v0, s0, seq::kState);
            }
        } else {
            // 0x003bf3ac
            charge(ctx, 3);
            v1 = 2;
            if (a1 == v1) {
                // 0x003bf408
                charge(ctx, 5);
                sw(zero, s0, seq::kTimer);
                sw(v1, s0, seq::kWait);
                sw(a0, s0, seq::kState);
            } else {
                // 0x003bf3b8
                charge(ctx, 3);
                v1 = 1;
                if (a1 == v1) {
                    // 0x003bf3e4
                    charge(ctx, 5);
                    a0 = addiu(v0, 484);
                    jal(ctx, 0x3BF3E8u, gen::fn_sub_3C3E80_003c3e80);
                    if (v0 == 0) {
                        // 0x003bf3f8
                        charge(ctx, 4);
                        v0 = 2;
                        sw(v0, s0, seq::kState);
                    }
                } else {
                    // 0x003bf3c4
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x003bf3d4
                        charge(ctx, 4);
                        sw(zero, gp, comu::kGpTimerArg);  // 0x7CE66C the comu timer word sub_3BF370 clears
                        sw(v1, s0, seq::kState);
                    } else {
                        // 0x003bf3cc
                        charge(ctx, 2);
                    }
                }
            }
        }
        goto L_003bf4f4;
    }
    // 0x003bf4a8
    charge(ctx, 4);
    jal(ctx, 0x3BF4A8u, gen::fn_sub_27C2B0_0027c2b0);
    if (v0 == 0) {
        // 0x003bf4b8
        charge(ctx, 5);
        jal(ctx, 0x3BF4B8u, gen::fn_sub_27C330_0027c330);
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003bf4d8;
        }
        // 0x003bf4cc
        charge(ctx, 3);
        v1 = 1;
        goto L_003bf4dc;
    }
L_003bf4d8:
    charge(ctx, 1);
    v1 = 0;
L_003bf4dc:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
    L_003bf4f4:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003bf4e8
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003bf4f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BF510 sub_3BF510 -- 248 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// A timer-sequence step: 1 waits for sub_3C3E80 on the hero record +584, 2 returns -1, 3 returns -1 once the sequence
// change is done; 0 otherwise.
void sub_3BF510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf510
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BF51Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    jal(ctx, 0x3BF528u, gen::fn_sub_1717B0_001717b0);
    lw(a0, s0, seq::kState);
    v1 = 3;
    if (a0 == v1) {
        // 0x003bf5a4
        charge(ctx, 4);
        jal(ctx, 0x3BF5A4u, gen::fn_sub_27C2B0_0027c2b0);
        if (v0 == 0) {
            // 0x003bf5b4
            charge(ctx, 5);
            jal(ctx, 0x3BF5B4u, gen::fn_sub_27C330_0027c330);
            v1 = si(-1);
            if (v0 != v1) {
                goto L_003bf5d4;
            }
            // 0x003bf5c8
            charge(ctx, 3);
            v1 = 1;
            goto L_003bf5d8;
        }
    L_003bf5d4:
        charge(ctx, 1);
        v1 = 0;
    L_003bf5d8:
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
        L_003bf5f0:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003bf5e4
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x003bf540
        charge(ctx, 3);
        v1 = 2;
        if (a0 != v1) {
            // 0x003bf54c
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x003bf574
                charge(ctx, 5);
                a0 = addiu(v0, 584);
                jal(ctx, 0x3BF578u, gen::fn_sub_3C3E80_003c3e80);
                if (v0 == 0) {
                    // 0x003bf588
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, s0, seq::kState);
                }
            } else {
                // 0x003bf558
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x003bf568
                    charge(ctx, 3);
                    sw(v1, s0, seq::kState);
                } else {
                    // 0x003bf560
                    charge(ctx, 2);
                }
            }
            goto L_003bf5f0;
        }
        // 0x003bf598
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003bf5f4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BF610 sub_3BF610 -- 272 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// Update of "comuTimerProcess": 0 arms, 1 requests sequence 2 with {7, 1, 0, .., 0}, 2 returns -1 once the change is
// done.
void sub_3BF610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf610
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BF61Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lw(a0, v0, 0);
    v1 = 2;
    if (a0 != v1) {
        // 0x003bf638
        charge(ctx, 3);
        v0 = 1;
        if (a0 == v0) {
            // 0x003bf668
            charge(ctx, 21);
            a0 = addiu(sp, 0x20);
            a1 = 0;
            a2 = 28;
            jal(ctx, 0x3BF674u, gen::fn_memset_00521408);
            v0 = 7;
            sh(v0, sp, 0x20);
            v0 = 1;
            sh(v0, sp, 0x22);
            sh(zero, sp, 0x24);
            sh(zero, sp, 0x28);
            a0 = 2;
            a1 = addiu(sp, 0x20);
            a2 = 28;
            a3 = 0;
            jal(ctx, 0x3BF6A4u, gen::fn_adminiChangeSeq_0027c080);
            v0 = 2;
            sw(v0, s0, seq::kState);
        } else {
            // 0x003bf644
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x003bf654
                charge(ctx, 5);
                sw(zero, s0, seq::kTimer);
                sw(v1, s0, seq::kWait);
                sw(v0, s0, seq::kState);
            } else {
                // 0x003bf64c
                charge(ctx, 2);
            }
        }
        goto L_003bf708;
    }
    // 0x003bf6bc
    charge(ctx, 4);
    jal(ctx, 0x3BF6BCu, gen::fn_sub_27C2B0_0027c2b0);
    if (v0 == 0) {
        // 0x003bf6cc
        charge(ctx, 5);
        jal(ctx, 0x3BF6CCu, gen::fn_sub_27C330_0027c330);
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003bf6ec;
        }
        // 0x003bf6e0
        charge(ctx, 3);
        v1 = 1;
        goto L_003bf6f0;
    }
L_003bf6ec:
    charge(ctx, 1);
    v1 = 0;
L_003bf6f0:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
    L_003bf708:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003bf6fc
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003bf70c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BF720 sub_3BF720 -- 448 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// A timer-sequence step: 1 waits 2 frames, then plays the event of 0x7CE678 (sub_16E920, sequence 3 with event 809);
// 2 waits for the change; 3 returns -1 (asserting sub_3C30B0 unless sub_38D6F0(0)).
void sub_3BF720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf720
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BF730u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 3;
    if (v1 == v0) {
        // 0x003bf874
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x3BF878u, gen::fn_sub_38D6F0_0038d6f0);
        if (v0 != 0) {
            // 0x003bf8b8
            charge(ctx, 3);
            v0 = si(-1);
        } else {
            // 0x003bf888
            charge(ctx, 4);
            jal(ctx, 0x3BF888u, gen::fn_sub_3C30B0_003c30b0);
            if (v0 == 0) {
                // 0x003bf898
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 12944);  // "comuTimerSequence.c"
                a1 = 425;
                jal(ctx, 0x3BF8A4u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003bf8ac
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x003bf74c
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x003bf824
            charge(ctx, 4);
            jal(ctx, 0x3BF824u, gen::fn_sub_27C2B0_0027c2b0);
            if (v0 == 0) {
                // 0x003bf834
                charge(ctx, 5);
                jal(ctx, 0x3BF834u, gen::fn_sub_27C330_0027c330);
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003bf854;
                }
                // 0x003bf848
                charge(ctx, 3);
                v1 = 1;
                goto L_003bf858;
            }
        L_003bf854:
            charge(ctx, 1);
            v1 = 0;
        L_003bf858:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003bf864
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, seq::kState);
            }
        } else {
            // 0x003bf758
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x003bf788
                charge(ctx, 5);
                lw(v1, s0, seq::kTimer);
                lw(v0, s0, seq::kWait);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003bf7ac
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, seq::kTimer);
                    a0 = 0;
                } else {
                    // 0x003bf79c
                    charge(ctx, 4);
                    sw(zero, s0, seq::kTimer);
                    sw(zero, s0, seq::kWait);
                }
                // 0x003bf7b8
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003bf7c4
                    charge(ctx, 24);
                    lh(a0, gp, comu::kGpTimerEvent);  // 0x7CE678 the event request of the timer sequence
                    jal(ctx, 0x3BF7C8u, gen::fn_sub_16E920_0016e920);
                    lw(s1, gp, comu::kGpTimerEvent);  // 0x7CE678 the event request of the timer sequence
                    a0 = addiu(sp, 0x30);
                    a1 = 0;
                    a2 = 28;
                    jal(ctx, 0x3BF7E0u, gen::fn_memset_00521408);
                    v0 = 809;
                    sw(v0, sp, 0x3C);
                    v0 = 1;
                    sw(v0, sp, 0x40);
                    sw(s1, sp, 0x44);
                    a0 = 3;
                    a1 = addiu(sp, 0x30);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x3BF80Cu, gen::fn_adminiChangeSeq_0027c080);
                    v0 = 2;
                    sw(v0, s0, seq::kState);
                }
            } else {
                // 0x003bf764
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003bf774
                    charge(ctx, 5);
                    sw(zero, s0, seq::kTimer);
                    sw(v0, s0, seq::kWait);
                    sw(a0, s0, seq::kState);
                } else {
                    // 0x003bf76c
                    charge(ctx, 2);
                }
            }
        }
        // 0x003bf8c4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003bf8c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003BF8E0 sub_3BF8E0 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// A timer-sequence step: when sub_3C3190 prepares the request at 0x7CE678, clears the work and returns the next step
// sub_3BF720, else -1.
void sub_3BF8E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf8e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BF8ECu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    a0 = addiu(gp, -18040);  // &0x7CE678
    jal(ctx, 0x3BF8FCu, gen::fn_sub_3C3190_003c3190);
    v1 = 1;
    if (v0 != v1) {
        // 0x003bf938
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x003bf910
        charge(ctx, 10);
        sw(zero, s0, seq::kState);
        sw(zero, s0, seq::kTimer);
        sw(zero, s0, seq::kWait);
        sw(zero, s0, seq::kW12);
        sw(zero, s0, seq::kW16);
        sw(zero, s0, seq::kW20);
        v0 = 0x3C0000;
        v0 = addiu(v0, -2272);  // &sub_3BF720
    }
    // 0x003bf93c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BF950 sub_3BF950 -- 392 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// A timer-sequence step: waits 2 frames, requests event 811 (sequence 3), waits for the change, then clears the work
// and returns the next step sub_3BF8E0.
void sub_3BF950(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bf950
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BF95Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    jal(ctx, 0x3BF968u, gen::fn_sub_1717B0_001717b0);
    lw(v1, s0, seq::kState);
    v0 = 3;
    if (v1 == v0) {
        // 0x003bfa98
        charge(ctx, 10);
        sw(zero, s0, seq::kState);
        sw(zero, s0, seq::kTimer);
        sw(zero, s0, seq::kWait);
        sw(zero, s0, seq::kW12);
        sw(zero, s0, seq::kW16);
        sw(zero, s0, seq::kW20);
        v0 = 0x3C0000;
        v0 = addiu(v0, -1824);  // &sub_3BF8E0
    } else {
        // 0x003bf980
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x003bfa48
            charge(ctx, 4);
            jal(ctx, 0x3BFA48u, gen::fn_sub_27C2B0_0027c2b0);
            if (v0 == 0) {
                // 0x003bfa58
                charge(ctx, 5);
                jal(ctx, 0x3BFA58u, gen::fn_sub_27C330_0027c330);
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003bfa78;
                }
                // 0x003bfa6c
                charge(ctx, 3);
                v1 = 1;
                goto L_003bfa7c;
            }
        L_003bfa78:
            charge(ctx, 1);
            v1 = 0;
        L_003bfa7c:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003bfa88
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, seq::kState);
            }
        } else {
            // 0x003bf98c
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x003bf9bc
                charge(ctx, 5);
                lw(v1, s0, seq::kTimer);
                lw(v0, s0, seq::kWait);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003bf9e0
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, seq::kTimer);
                    a0 = 0;
                } else {
                    // 0x003bf9d0
                    charge(ctx, 4);
                    sw(zero, s0, seq::kTimer);
                    sw(zero, s0, seq::kWait);
                }
                // 0x003bf9ec
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003bf9f8
                    charge(ctx, 20);
                    a0 = addiu(sp, 0x20);
                    a1 = 0;
                    a2 = 28;
                    jal(ctx, 0x3BFA04u, gen::fn_memset_00521408);
                    v0 = 811;
                    sw(v0, sp, 0x2C);
                    v0 = 1;
                    sw(v0, sp, 0x30);
                    sw(zero, sp, 0x34);
                    a0 = 3;
                    a1 = addiu(sp, 0x20);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x3BFA30u, gen::fn_adminiChangeSeq_0027c080);
                    v0 = 2;
                    sw(v0, s0, seq::kState);
                }
            } else {
                // 0x003bf998
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003bf9a8
                    charge(ctx, 5);
                    sw(zero, s0, seq::kTimer);
                    sw(v0, s0, seq::kWait);
                    sw(a0, s0, seq::kState);
                } else {
                    // 0x003bf9a0
                    charge(ctx, 2);
                }
            }
        }
        // 0x003bfac0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003bfac4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BFAE0 sub_3BFAE0 -- 360 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// A timer-sequence step: waits 2 frames, requests event 808, waits for the change; -1 at the end.
void sub_3BFAE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bfae0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BFAECu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    jal(ctx, 0x3BFAF8u, gen::fn_sub_1717B0_001717b0);
    lw(v1, s0, seq::kState);
    v0 = 3;
    if (v1 == v0) {
        // 0x003bfc24
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x003bfb10
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x003bfbd4
            charge(ctx, 4);
            jal(ctx, 0x3BFBD4u, gen::fn_sub_27C2B0_0027c2b0);
            if (v0 == 0) {
                // 0x003bfbe4
                charge(ctx, 5);
                jal(ctx, 0x3BFBE4u, gen::fn_sub_27C330_0027c330);
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003bfc04;
                }
                // 0x003bfbf8
                charge(ctx, 3);
                v1 = 1;
                goto L_003bfc08;
            }
        L_003bfc04:
            charge(ctx, 1);
            v1 = 0;
        L_003bfc08:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003bfc14
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, seq::kState);
            }
        } else {
            // 0x003bfb1c
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x003bfb4c
                charge(ctx, 5);
                lw(v1, s0, seq::kTimer);
                lw(v0, s0, seq::kWait);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003bfb70
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, seq::kTimer);
                    a0 = 0;
                } else {
                    // 0x003bfb60
                    charge(ctx, 4);
                    sw(zero, s0, seq::kTimer);
                    sw(zero, s0, seq::kWait);
                }
                // 0x003bfb7c
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x003bfb84
                    charge(ctx, 20);
                    a0 = addiu(sp, 0x20);
                    a1 = 0;
                    a2 = 28;
                    jal(ctx, 0x3BFB90u, gen::fn_memset_00521408);
                    v0 = 808;
                    sw(v0, sp, 0x2C);
                    v0 = 1;
                    sw(v0, sp, 0x30);
                    sw(zero, sp, 0x34);
                    a0 = 3;
                    a1 = addiu(sp, 0x20);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x3BFBBCu, gen::fn_adminiChangeSeq_0027c080);
                    v0 = 2;
                    sw(v0, s0, seq::kState);
                }
            } else {
                // 0x003bfb28
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003bfb38
                    charge(ctx, 5);
                    sw(zero, s0, seq::kTimer);
                    sw(v0, s0, seq::kWait);
                    sw(a0, s0, seq::kState);
                } else {
                    // 0x003bfb30
                    charge(ctx, 2);
                }
            }
        }
        // 0x003bfc30
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003bfc34 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003BFC50 sub_3BFC50 -- 344 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// A timer-sequence step: requests event 810 with the link of 0x7CE674, waits for the change (sub_172B20 after it),
// then clears the work and returns the next step sub_3BF950.
void sub_3BFC50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bfc50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BFC60u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lw(a0, v0, 0);
    v0 = 3;
    if (a0 == v0) {
        // 0x003bfd64
        charge(ctx, 10);
        sw(zero, s0, seq::kState);
        sw(zero, s0, seq::kTimer);
        sw(zero, s0, seq::kWait);
        sw(zero, s0, seq::kW12);
        sw(zero, s0, seq::kW16);
        sw(zero, s0, seq::kW20);
        v0 = 0x3C0000;
        v0 = addiu(v0, -1712);  // &sub_3BF950
    } else {
        // 0x003bfc7c
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x003bfd0c
            charge(ctx, 4);
            jal(ctx, 0x3BFD0Cu, gen::fn_sub_27C2B0_0027c2b0);
            if (v0 == 0) {
                // 0x003bfd1c
                charge(ctx, 5);
                jal(ctx, 0x3BFD1Cu, gen::fn_sub_27C330_0027c330);
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003bfd3c;
                }
                // 0x003bfd30
                charge(ctx, 3);
                v1 = 1;
                goto L_003bfd40;
            }
        L_003bfd3c:
            charge(ctx, 1);
            v1 = 0;
        L_003bfd40:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003bfd4c
                charge(ctx, 6);
                jal(ctx, 0x3BFD4Cu, gen::fn_sub_172B20_00172b20);
                v0 = 3;
                sw(v0, s0, seq::kState);
            }
        } else {
            // 0x003bfc88
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                // 0x003bfcb8
                charge(ctx, 21);
                lw(s1, gp, comu::kGpTimerLink);  // 0x7CE674 s32: the link the timer sequence works on
                a0 = addiu(sp, 0x30);
                a1 = 0;
                a2 = 28;
                jal(ctx, 0x3BFCC8u, gen::fn_memset_00521408);
                v0 = 810;
                sw(v0, sp, 0x3C);
                v0 = 1;
                sw(v0, sp, 0x40);
                sw(s1, sp, 0x44);
                a0 = 3;
                a1 = addiu(sp, 0x30);
                a2 = 28;
                a3 = 0;
                jal(ctx, 0x3BFCF4u, gen::fn_adminiChangeSeq_0027c080);
                v0 = 2;
                sw(v0, s0, seq::kState);
            } else {
                // 0x003bfc94
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x003bfca4
                    charge(ctx, 5);
                    sw(zero, s0, seq::kTimer);
                    sw(v1, s0, seq::kWait);
                    sw(v0, s0, seq::kState);
                } else {
                    // 0x003bfc9c
                    charge(ctx, 2);
                }
            }
        }
        // 0x003bfd8c
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003bfd90 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003BFDB0 sub_3BFDB0 -- 392 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// A timer-sequence step: picks the link (sub_172C50): at rank 10 (0x7CE674 = link + 30) or reversed / broken
// (0x7CE674 = link) -> sub_3BFC50; otherwise prepares its events (sub_3C3050, sub_3C3120; asserts 585 / 587) ->
// sub_3BFAE0; no link -> sub_3BF950. Clears the work.
void sub_3BFDB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bfdb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BFDBCu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    a0 = addiu(sp, 0x2E);
    jal(ctx, 0x3BFDCCu, gen::fn_sub_172C50_00172c50);
    if (v0 == 0) {
        // 0x003bff04
        charge(ctx, 8);
        sw(zero, s0, seq::kState);
        sw(zero, s0, seq::kTimer);
        sw(zero, s0, seq::kWait);
        sw(zero, s0, seq::kW12);
        sw(zero, s0, seq::kW16);
        sw(zero, s0, seq::kW20);
        v0 = 0x3C0000;
        v0 = addiu(v0, -1712);  // &sub_3BF950
    } else {
        // 0x003bfddc
        charge(ctx, 8);
        lh(a0, sp, 0x2E);
        jal(ctx, 0x3BFDE0u, gen::fn_sub_16DBA0_0016dba0);
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = 10;
        if (v1 != v0) {
            // 0x003bfe30
            charge(ctx, 6);
            lh(a0, sp, 0x2E);
            jal(ctx, 0x3BFE34u, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 != v1) {
                // 0x003bfe48
                charge(ctx, 6);
                lh(a0, sp, 0x2E);
                jal(ctx, 0x3BFE4Cu, gen::fn_sub_172160_00172160);
                v1 = 1;
                if (v0 == v1) {
                    goto L_003bfe60;
                }
                // 0x003bfe90
                charge(ctx, 5);
                lh(a0, sp, 0x2E);
                jal(ctx, 0x3BFE94u, gen::fn_sub_3C3050_003c3050);
                if (v0 == 0) {
                    // 0x003bfea4
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12944);  // "comuTimerSequence.c"
                    a1 = 585;
                    jal(ctx, 0x3BFEB0u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003bfeb8
                charge(ctx, 4);
                jal(ctx, 0x3BFEB8u, gen::fn_sub_3C3120_003c3120);
                if (v0 == 0) {
                    // 0x003bfec8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 12944);  // "comuTimerSequence.c"
                    a1 = 587;
                    jal(ctx, 0x3BFED4u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003bfedc
                charge(ctx, 10);
                sw(zero, s0, seq::kState);
                sw(zero, s0, seq::kTimer);
                sw(zero, s0, seq::kWait);
                sw(zero, s0, seq::kW12);
                sw(zero, s0, seq::kW16);
                sw(zero, s0, seq::kW20);
                v0 = 0x3C0000;
                v0 = addiu(v0, -1312);  // &sub_3BFAE0
                // 0x003bff24 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_003bfe60:
            charge(ctx, 12);
            lh(v0, sp, 0x2E);
            sw(v0, gp, comu::kGpTimerLink);  // 0x7CE674 s32: the link the timer sequence works on
            sw(zero, s0, seq::kState);
            sw(zero, s0, seq::kTimer);
            sw(zero, s0, seq::kWait);
            sw(zero, s0, seq::kW12);
            sw(zero, s0, seq::kW16);
            sw(zero, s0, seq::kW20);
            v0 = 0x3C0000;
            v0 = addiu(v0, -944);  // &sub_3BFC50
        } else {
            // 0x003bfdfc
            charge(ctx, 13);
            lh(v0, sp, 0x2E);
            v0 = addiu(v0, 30);
            sw(v0, gp, comu::kGpTimerLink);  // 0x7CE674 s32: the link the timer sequence works on
            sw(zero, s0, seq::kState);
            sw(zero, s0, seq::kTimer);
            sw(zero, s0, seq::kWait);
            sw(zero, s0, seq::kW12);
            sw(zero, s0, seq::kW16);
            sw(zero, s0, seq::kW20);
            v0 = 0x3C0000;
            v0 = addiu(v0, -944);  // &sub_3BFC50
        }
    }
    // 0x003bff24 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003BFF40 sub_3BFF40 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// The first timer-sequence step: refreshes the links (sub_3BDDE0), clears the work, next step sub_3BFDB0.
void sub_3BFF40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003bff40
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3BFF4Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    jal(ctx, 0x3BFF58u, gen::fn_sub_3BDDE0_003bdde0);
    sw(zero, s0, seq::kState);
    sw(zero, s0, seq::kTimer);
    sw(zero, s0, seq::kWait);
    sw(zero, s0, seq::kW12);
    sw(zero, s0, seq::kW16);
    sw(zero, s0, seq::kW20);
    v0 = 0x3C0000;
    v0 = addiu(v0, -592);  // &sub_3BFDB0
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003BFFA0 sub_3BFFA0 -- 1096 bytes; frame 0x140: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuPickDatedCall] (out_event, out_flag, out_minor) Today's call: an exact-date row of the first / second dated
// table (3-byte {month, day, minor}; month 255 = weekday) gives event 802 / 803; else up to 10 range rows (5-byte
// {m0, d0, m1, d1, minor}) of the first / second ranged table, one picked at random (sub_395200) with a 20 % chance
// (sub_395230(20)) -> 802 / 803. 1 when one is chosen, else 0.
void sub_3BFFA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x003bffa0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s6 = a1;
    s7 = a2;
    jal(ctx, 0x3BFFD8u, gen::fn_sub_3BDD40_003bdd40);
    s3 = v0;
    s5 = 0;
    jal(ctx, 0x3BFFE8u, gen::fn_clndGetCurrentMonth_0017d920);
    s1 = v0;
    jal(ctx, 0x3BFFF4u, gen::fn_clndGetCurrentDay_0017da40);
    s0 = v0;
    lw(v0, s3, 0);
    sq(v0, sp, 0x100);
    lw(v0, s3, 4);
    sq(v0, sp, 0xF0);
    s4 = 0;
    for (;;) {
        // 0x003c00c0
        charge(ctx, 4);
        lq(v0, sp, 0xF0);
        v0 = slt(s4, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c001c
        charge(ctx, 10);
        v0 = sll(s4, 1);
        v0 = addu(v0, s4);
        sq(v0, sp, 0xE0);
        lq(v1, sp, 0x100);
        v0 = addu(v1, v0);
        lbu(a0, v0, 1);
        lbu(v1, v0, 0);
        v0 = 255;
        if (v1 != v0) {
            // 0x003c0074
            charge(ctx, 2);
            if (s1 == v1) {
                // 0x003c007c
                charge(ctx, 2);
                if (s0 != a0) {
                    goto L_003c0090;
                }
                // 0x003c0084
                charge(ctx, 3);
                v1 = 1;
                goto L_003c0094;
            }
        L_003c0090:
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x003c0044
            charge(ctx, 7);
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3C004Cu, gen::fn_sub_17E050_0017e050);
            v1 = 1;
            if (v0 != v1) {
                // 0x003c0068
                charge(ctx, 3);
                v1 = 0;
            } else {
                // 0x003c0060
                charge(ctx, 2);
            }
        }
    L_003c0094:
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_003c00a0_10;
        }
        // 0x003c00bc
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
L_003c00d0:
    charge(ctx, 3);
    v0 = 1;
    if (s5 != v0) {
        // 0x003c00f4
        charge(ctx, 7);
        lw(v0, s3, 8);
        sq(v0, sp, 0xD0);
        lw(v0, s3, 12);
        sq(v0, sp, 0xC0);
        s4 = 0;
        for (;;) {
            // 0x003c01b4
            charge(ctx, 4);
            lq(v0, sp, 0xC0);
            v0 = slt(s4, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c0110
            charge(ctx, 10);
            v0 = sll(s4, 1);
            v0 = addu(v0, s4);
            sq(v0, sp, 0xB0);
            lq(v1, sp, 0xD0);
            v0 = addu(v1, v0);
            lbu(a0, v0, 1);
            lbu(v1, v0, 0);
            v0 = 255;
            if (v1 != v0) {
                // 0x003c0168
                charge(ctx, 2);
                if (s1 == v1) {
                    // 0x003c0170
                    charge(ctx, 2);
                    if (s0 != a0) {
                        goto L_003c0184;
                    }
                    // 0x003c0178
                    charge(ctx, 3);
                    v1 = 1;
                    goto L_003c0188;
                }
            L_003c0184:
                charge(ctx, 1);
                v1 = 0;
            } else {
                // 0x003c0138
                charge(ctx, 7);
                a1 = s1;
                a2 = s0;
                jal(ctx, 0x3C0140u, gen::fn_sub_17E050_0017e050);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003c015c
                    charge(ctx, 3);
                    v1 = 0;
                } else {
                    // 0x003c0154
                    charge(ctx, 2);
                }
            }
        L_003c0188:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003c0194_25;
            }
            // 0x003c01b0
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
    L_003c01c4:
        charge(ctx, 3);
        v0 = 1;
        if (s5 != v0) {
            // 0x003c01e8
            charge(ctx, 7);
            lw(fp, s3, 16);
            lw(v0, s3, 20);
            sq(v0, sp, 0xA0);
            s5 = 0;
            s4 = 0;
            for (;;) {
                // 0x003c025c
                charge(ctx, 4);
                lq(v0, sp, 0xA0);
                v0 = slt(s4, v0);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x003c0204
                    charge(ctx, 14);
                    v0 = sll(s4, 2);
                    v0 = addu(v0, s4);
                    v0 = addu(fp, v0);
                    lbu(a2, v0, 0);
                    lbu(a3, v0, 1);
                    lbu(t0, v0, 2);
                    lbu(t1, v0, 3);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x3C0228u, gen::fn_sub_3BF270_003bf270);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x003c023c
                        charge(ctx, 4);
                        v0 = sll(s5, 2);
                        v0 = addu(v0, sp);
                        sw(s4, v0, 272);
                        s5 = addiu(s5, 1);
                    }
                    // 0x003c024c
                    charge(ctx, 3);
                    at = slti(s5, 10);
                    if (at != 0) {
                        // 0x003c0258
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x003c026c
            charge(ctx, 2);
            if (i64(s5) > 0) {
                // 0x003c0274
                charge(ctx, 16);
                a0 = s5;
                jal(ctx, 0x3C0278u, gen::fn_sub_395200_00395200);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(v1, v0, 272);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = addu(v0, fp);
                lbu(s4, v0, 4);
                a0 = 20;
                jal(ctx, 0x3C02A0u, gen::fn_sub_395230_00395230);
                v1 = 1;
                if (v0 != v1) {
                    goto L_003c02d0;
                }
                // 0x003c02b4
                charge(ctx, 7);
                v0 = 802;
                sw(v0, s2, 0);
                sw(v1, s6, 0);
                sw(s4, s7, 0);
                v0 = v1;
                // 0x003c03b4 (the shared epilogue, written out on this path)
                charge(ctx, 13);
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
                sp = addiu(sp, 0x140);
                return;
            }
        L_003c02d0:
            charge(ctx, 6);
            lw(s5, s3, 24);
            lw(fp, s3, 28);
            s4 = 0;
            s3 = 0;
            for (;;) {
                // 0x003c0340
                charge(ctx, 3);
                v0 = slt(s3, fp);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x003c02e8
                    charge(ctx, 14);
                    v0 = sll(s3, 2);
                    v0 = addu(v0, s3);
                    v0 = addu(s5, v0);
                    lbu(a2, v0, 0);
                    lbu(a3, v0, 1);
                    lbu(t0, v0, 2);
                    lbu(t1, v0, 3);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x3C030Cu, gen::fn_sub_3BF270_003bf270);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x003c0320
                        charge(ctx, 4);
                        v0 = sll(s4, 2);
                        v0 = addu(v0, sp);
                        sw(s3, v0, 272);
                        s4 = addiu(s4, 1);
                    }
                    // 0x003c0330
                    charge(ctx, 3);
                    at = slti(s4, 10);
                    if (at != 0) {
                        // 0x003c033c
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x003c034c
            charge(ctx, 2);
            if (i64(s4) > 0) {
                // 0x003c0354
                charge(ctx, 16);
                a0 = s4;
                jal(ctx, 0x3C0358u, gen::fn_sub_395200_00395200);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(v1, v0, 272);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = addu(v0, s5);
                lbu(s0, v0, 4);
                a0 = 20;
                jal(ctx, 0x3C0380u, gen::fn_sub_395230_00395230);
                v1 = 1;
                if (v0 != v1) {
                    goto L_003c03b0;
                }
                // 0x003c0394
                charge(ctx, 7);
                v0 = 803;
                sw(v0, s2, 0);
                sw(v1, s6, 0);
                sw(s0, s7, 0);
                v0 = v1;
                // 0x003c03b4 (the shared epilogue, written out on this path)
                charge(ctx, 13);
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
                sp = addiu(sp, 0x140);
                return;
            }
        L_003c03b0:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003c01d0
            charge(ctx, 6);
            v1 = 803;
            sw(v1, s2, 0);
            sw(v0, s6, 0);
            sw(fp, s7, 0);
        }
    } else {
        // 0x003c00dc
        charge(ctx, 6);
        v1 = 802;
        sw(v1, s2, 0);
        sw(v0, s6, 0);
        sw(fp, s7, 0);
    }
    // 0x003c03b4 (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
    sp = addiu(sp, 0x140);
    return;
L_003c00a0_10:
    charge(ctx, 7);
    s5 = v0;
    lq(v1, sp, 0xE0);
    lq(v0, sp, 0x100);
    v0 = addu(v1, v0);
    lbu(fp, v0, 2);
    goto L_003c00d0;
L_003c0194_25:
    charge(ctx, 7);
    s5 = v0;
    lq(v1, sp, 0xB0);
    lq(v0, sp, 0xD0);
    v0 = addu(v1, v0);
    lbu(fp, v0, 2);
    goto L_003c01c4;
}

}  // namespace p3fes::game
