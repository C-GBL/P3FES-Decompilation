// Slice libs3: CRI Sofdec's M2V module (the MPEG video decoder above the IPU): its entry table, the handle pool, the
// MPEG-2 probe and the copy hooks (the handle check 0x5753E8 and the memcpy hook 0x575410 stay recompiled: tests
// stand them in; the bit-level header parsers 0x570030-0x574CA8 stay recompiled:
// unreached).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn_atan2l_10_00575470(p3fes::EEContext&);
void fn_coshl_10_005754a0(p3fes::EEContext&);
void fn_cosl_10_00575488(p3fes::EEContext&);
void fn_expl_10_005754b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_16_00574e50(p3fes::EEContext&);
void fn_sub_56F850_0056f850(p3fes::EEContext&);
void fn_sub_56F8F8_0056f8f8_at_0056f978(p3fes::EEContext&);
void fn_sub_56FD28_0056fd28(p3fes::EEContext&);
void fn_sub_56FD58_0056fd58(p3fes::EEContext&);
void fn_sub_574CA8_00574ca8(p3fes::EEContext&);
void fn_sub_574E60_00574e60(p3fes::EEContext&);
void fn_sub_574F10_00574f10(p3fes::EEContext&);
void fn_sub_574FE8_00574fe8(p3fes::EEContext&);
void fn_sub_575088_00575088(p3fes::EEContext&);
void fn_sub_575138_00575138(p3fes::EEContext&);
void fn_sub_575140_00575140(p3fes::EEContext&);
void fn_sub_575178_00575178(p3fes::EEContext&);
void fn_sub_5751C8_005751c8(p3fes::EEContext&);
void fn_sub_575288_00575288(p3fes::EEContext&);
void fn_sub_5752D8_005752d8(p3fes::EEContext&);
void fn_sub_5752E0_005752e0(p3fes::EEContext&);
void fn_sub_575390_00575390(p3fes::EEContext&);
void fn_sub_5753E8_005753e8(p3fes::EEContext&);
void fn_sub_575410_00575410(p3fes::EEContext&);
void fn_sub_575428_00575428(p3fes::EEContext&);
void fn_sub_575440_00575440(p3fes::EEContext&);
void fn_sub_575458_00575458(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00574CA8 sub_574CA8 -- 424 bytes; frame 0x50: s7 sp+0x38, fp sp+0x40, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30
// [m2vSetupEntryTable] M2V's entry table: sets the "table filled" word 0x7B2928 = 1 and stores the module's 20 entry
// points at 0x7B292C..0x7B2978 (the version getter, the MPEG-2 probe sub_574E60, init sub_574F10, the empty finish
// sub_575138, create sub_575140, destroy sub_575288, set-callback sub_5752E0, the empty sub_5752D8, and the decoder
// entries sub_56F888..sub_56FCB0 in the CRI band). Leaves the last address in $v0.
void sub_574CA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // 0x00574ca8
    enter(ctx, 106);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x570000;
    sd(s7, sp, 0x38);
    s7 = 0x7B0000;
    v0 = addiu(v0, 20048);  // &sceLibgcc32GetErxEntries_16
    t8 = 0x7B0000;
    sw(v0, s7, 10540);  // 0x7B292C
    v0 = 0x570000;
    v0 = addiu(v0, 20064);  // &sub_574E60
    t9 = 0x7B0000;
    sw(v0, t8, 10544);  // 0x7B2930
    v0 = 0x570000;
    v0 = addiu(v0, 20240);  // &sub_574F10
    sd(fp, sp, 0x40);
    sw(v0, t9, 10548);  // 0x7B2934
    v0 = 0x570000;
    fp = 0x7B0000;
    v0 = addiu(v0, 20792);  // &sub_575138
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    sd(s2, sp, 0x10);
    s2 = 0x7B0000;
    sd(s3, sp, 0x18);
    s3 = 0x7B0000;
    sd(s4, sp, 0x20);
    s4 = 0x7B0000;
    sd(s5, sp, 0x28);
    s5 = 0x7B0000;
    sd(s6, sp, 0x30);
    s6 = 1;
    sw(v0, fp, 0x2938);
    v0 = 0x570000;
    v0 = addiu(v0, 20800);  // &sub_575140
    a0 = 0x570000;
    sw(v0, s5, 10556);  // 0x7B293C
    v0 = 0x570000;
    v0 = addiu(v0, 21128);  // &sub_575288
    v1 = 0x570000;
    sw(v0, s4, 10560);  // 0x7B2940
    v0 = 0x570000;
    v0 = addiu(v0, 21216);  // &sub_5752E0
    t7 = 0x7B0000;
    sw(v0, s3, 10564);  // 0x7B2944
    v0 = 0x570000;
    v0 = addiu(v0, 21208);  // &sub_5752D8
    t6 = 0x7B0000;
    sw(v0, s2, 10568);  // 0x7B2948
    v0 = a0;
    v0 = addiu(v0, -1912);  // &sub_56F888
    t5 = 0x7B0000;
    sw(v0, s1, 10572);  // 0x7B294C
    v0 = v1;
    v0 = addiu(v0, -1800);  // &sub_56F8F8
    t4 = 0x7B0000;
    sw(v0, s0, 10576);  // 0x7B2950
    v0 = 0x570000;
    v0 = addiu(v0, -1352);  // &sub_56FAB8
    t3 = 0x7B0000;
    sw(v0, t7, 10580);  // 0x7B2954
    v0 = 0x570000;
    v0 = addiu(v0, -1536);  // &sub_56FA00
    t2 = 0x7B0000;
    sw(v0, t6, 10584);  // 0x7B2958
    v0 = 0x570000;
    v0 = addiu(v0, -544);  // &sub_56FDE0
    t1 = 0x7B0000;
    sw(v0, t5, 10588);  // 0x7B295C
    v0 = 0x570000;
    v0 = addiu(v0, -504);  // &sub_56FE08
    t0 = 0x7B0000;
    sw(v0, t4, 10592);  // 0x7B2960
    v0 = 0x570000;
    v0 = addiu(v0, -488);  // &sub_56FE18
    a3 = 0x7B0000;
    sw(v0, t3, 10596);  // 0x7B2964
    v0 = 0x570000;
    v0 = addiu(v0, -448);  // &sub_56FE40
    a1 = 0x7B0000;
    sw(v0, t2, 10600);  // 0x7B2968
    v0 = 0x570000;
    v0 = addiu(v0, -1344);  // &sub_56FAC0
    sw(s6, a1, 10536);  // 0x7B2928
    sw(v0, t1, 10604);  // 0x7B296C
    v0 = 0x570000;
    v0 = addiu(v0, -1088);  // &sub_56FBC0
    ld(s0, sp, 0x0);
    sw(v0, t0, 10608);  // 0x7B2970
    v0 = 0x570000;
    v0 = addiu(v0, -992);  // &sub_56FC20
    ld(s1, sp, 0x8);
    sw(v0, a3, 10612);  // 0x7B2974
    v0 = 0x570000;
    ld(s2, sp, 0x10);
    a2 = 0x7B0000;
    ld(s3, sp, 0x18);
    v0 = addiu(v0, -848);  // &sub_56FCB0
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    sw(v0, a2, 10616);  // 0x7B2978
    sp = addiu(sp, 0x50);
}

// 0x00574E50 sceLibgcc32GetErxEntries_16 -- 12 bytes; leaf frame (no stack)
// [m2vGetVersionStr] Returns M2V's version banner ("CRI M2V/PS2EE Ver.1.958") in $v0. The FLIRT name is a false match
// of a short code shape; the role is read from the instructions.
void sceLibgcc32GetErxEntries_16(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00574e50
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 31000);  // "\nCRI M2V/PS2EE Ver.1.958 Build:Mar  1 2005 10:54:05\n"
}

// 0x00574E60 sub_574E60 -- 176 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [m2vIsMpeg2] M2V's MPEG-2 probe (buf, len): finds a sequence_header_code (sub_578160 with class 64), then the next
// start code; returns 1 when it is an extension (class 16) whose extension_start_code_identifier (the top four bits of
// the next byte) is 1 -- a sequence_extension, so ISO/IEC 13818-2 video -- and 0 otherwise (MPEG-1, or the data ends
// first).
void sub_574E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00574e60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 64;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x574E7Cu, gen::fn_sub_578160_00578160);
    s0 = v0;
    cc = s0 == 0;  // the condition, before the delay slot changes it
    s0 = addiu(s0, 4);
    if (!cc) {
        // 0x00574e90
        charge(ctx, 7);
        v0 = 0;
        v1 = subu(s0, s2);
        s2 = s0;
        s1 = subu(s1, v1);
        a0 = s2;
        a1 = s1;
        if (i64(s1) <= 0) {
            goto L_00574ef8;
        }
        // 0x00574eac
        charge(ctx, 5);
        a2 = si(-1);
        jal(ctx, 0x574EACu, gen::fn_sub_578160_00578160);
        s0 = v0;
        a0 = s0;
        if (s0 == 0) {
            goto L_00574ef8;
        }
        // 0x00574ec0
        charge(ctx, 5);
        jal(ctx, 0x574EC0u, gen::fn_sub_577FC8_00577fc8);
        v1 = v0 & 0x10;
        v0 = 0;
        if (v1 == 0) {
            goto L_00574ef8;
        }
        // 0x00574ed4
        charge(ctx, 5);
        s0 = addiu(s0, 4);
        v1 = subu(s0, s2);
        s1 = subu(s1, v1);
        if (i64(s1) > 0) {
            // 0x00574ee8
            charge(ctx, 4);
            lbu(v0, s0, 0);
            v0 = srl(v0, 4);
            v0 = v0 ^ 0x1;
            v0 = sltiu(v0, 1);
            goto L_00574ef8;
        }
        ld(s0, sp, 0x0);
        // 0x00574efc (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00574ef8:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00574efc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00574F10 sub_574F10 -- 212 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [m2vInit] M2V init (n, work, size): checks a build-time word (== 4) and otherwise jumps to address 0xFFFFFFFF (a
// deliberate trap the recompiled body reproduces); stores the banner at 0x99B258, runs the decoder setup in the CRI
// band (sub_56F850, sub_56FD28), lays out the handle pool (sub_574FE8) and marks every handle free (state 1, 1,696-byte
// handles).
void sub_574F10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00574f10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    v0 = 0x7C0000;
    lbu(v1, v0, 31156);  // 0x7C79B4
    a0 = 4;
    s2 = a2;
    if (v1 != a0) {
        for (;;) {
            // 0x00574f40
            charge(ctx, 5);
            at = si(-1);
            jalr(ctx, 0x574F44u, at.u());
            backedge(ctx);
        }
    }
    // 0x00574f58
    charge(ctx, 18);
    v1 = 0x9A0000;
    v0 = 0x7C0000;
    v1 = addiu(v1, -19880);  // &0x99B258
    v0 = addiu(v0, 31000);  // "\nCRI M2V/PS2EE Ver.1.958 Build:Mar  1 2005 10:54:05\n"
    link(ctx, 0x574F68u);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 0);
    call(ctx, gen::fn_sub_56F850_0056f850);
    jal(ctx, 0x574F70u, gen::fn_sub_56FD28_0056fd28);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x574F80u, gen::fn_sub_574FE8_00574fe8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    // 0x00574fa0
    charge(ctx, 5);
    v0 = 0x9A0000;
    v0 = addiu(v0, -19872);  // &0x99B260
    lw(a0, v0, 64);  // 0x99B2A0
    lw(v1, v0, 68);  // 0x99B2A4
    if (i64(a0) > 0) {
        // 0x00574fb4
        charge(ctx, 3);
        v0 = a0;
        a0 = 1;
        for (;;) {
            // 0x00574fc0
            charge(ctx, 7);
            v0 = addiu(v0, -1);
            sw(a0, v1, 0);
            v1 = addiu(v1, 1696);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00574fdc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00574FE8 sub_574FE8 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [m2vSetupPool] M2V pool layout (n, work, size): lowers n until 1,792 * n + 64 bytes fit in size, aligns work up to 64
// bytes, clears 1,792 * n bytes there (memset) and records the pool base 0x99B2A4 and count 0x99B2A0.
void sub_574FE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00574fe8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = a2;
    sd(s0, sp, 0x0);
    s0 = a0;
    a2 = sll(s0, 3);
    sd(s1, sp, 0x8);
    v0 = subu(a2, s0);
    sd(ra, sp, 0x10);
    v0 = sll(v0, 8);
    v0 = addiu(v0, 64);
    v1 = sltu(a3, v0);
    s1 = a1;
    if (v1 != 0) {
        // 0x0057501c
        charge(ctx, 3);
        a0 = v0;
        v1 = a2;
        for (;;) {
            // 0x00575028
            charge(ctx, 7);
            a0 = addiu(a0, -1792);
            v1 = addiu(v1, -8);
            v0 = sltu(a3, a0);
            s0 = addiu(s0, -1);
            a2 = v1;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00575044
    charge(ctx, 17);
    v1 = addiu(s1, 63);
    v0 = si(-64);
    s1 = v1 & v0;
    a2 = subu(a2, s0);
    a0 = s1;
    a2 = sll(a2, 8);
    a1 = 0;
    jal(ctx, 0x57505Cu, gen::fn_memset_00521408);
    v1 = 0x9A0000;
    v1 = addiu(v1, -19872);  // &0x99B260
    ld(ra, sp, 0x10);
    sw(s1, v1, 68);  // 0x99B2A4
    sw(s0, v1, 64);  // 0x99B2A0
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00575088 sub_575088 -- 176 bytes; leaf frame (no stack)
// [m2vResetParams] Resets an M2V decode-parameter block (handle + 88): every word cleared, then the defaults (byte +89
// = 1, +56 = 3, +60 = 1, +68 = 1, the halfwords +80 / +82 = -1, byte +85 = 1, ...).
void sub_575088(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00575088
    enter(ctx, 44);  // entry check point + this block's cycles
    v1 = si(-1);
    a1 = 1;
    v0 = 3;
    sb(a1, a0, 89);
    sw(v0, a0, 56);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    sw(zero, a0, 16);
    sw(zero, a0, 20);
    sw(zero, a0, 24);
    sw(zero, a0, 28);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    sw(zero, a0, 44);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
    sw(a1, a0, 60);
    sw(zero, a0, 64);
    sw(a1, a0, 68);
    sw(zero, a0, 72);
    sw(zero, a0, 76);
    sh(v1, a0, 80);
    sh(v1, a0, 82);
    sb(zero, a0, 84);
    sb(a1, a0, 85);
    sb(zero, a0, 86);
    sb(zero, a0, 87);
    sb(zero, a0, 88);
    sb(zero, a0, 90);
    sb(zero, a0, 91);
    sb(zero, a0, 92);
    sb(v1, a0, 93);
    sb(zero, a0, 94);
    sb(v1, a0, 95);
    sb(v1, a0, 100);
    sw(zero, a0, 104);
    sb(v1, a0, 96);
    sb(zero, a0, 97);
    sb(v1, a0, 98);
    sb(v1, a0, 99);
}

// 0x00575138 sub_575138 -- 8 bytes; leaf frame (no stack)
// [m2vFinish] An empty function (jr $ra / nop): M2V's finish entry (table slot 0x7B2938).
void sub_575138(EEContext& ctx) {
    using namespace hg;
    // 0x00575138
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00575140 sub_575140 -- 52 bytes; frame 0x10: ra sp+0x0
// [m2vCreate] M2V create: takes the first free handle (sub_575178) and initialises it (sub_5751C8); returns it or 0.
void sub_575140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575140
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x575148u, gen::fn_sub_575178_00575178);
    v1 = v0;
    a0 = v1;
    if (v1 == 0) {
        // 0x00575168
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057515c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5751C8_005751c8(ctx);  // tail call
}

// 0x00575178 sub_575178 -- 80 bytes; leaf frame (no stack)
// [m2vFindFreeHandle] The first free M2V handle (state 1) of the pool (base 0x99B2A4, count 0x99B2A0, 1,696-byte
// stride), or 0.
void sub_575178(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00575178
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    a2 = 0;
    v0 = addiu(v0, -19872);  // &0x99B260
    lw(a1, v0, 64);  // 0x99B2A0
    lw(a0, v0, 68);  // 0x99B2A4
    if (i64(a1) > 0) {
        // 0x00575190
        charge(ctx, 2);
        a3 = libs3::m2v::kStateFree;
        lw(v1, a0, 0);
        for (;;) {
            // 0x00575198
            charge(ctx, 3);
            v0 = a0;
            a0 = addiu(a0, libs3::m2v::kHandleStride);
            if (v1 == a3) {
                break;
            }
            // 0x005751a4
            charge(ctx, 6);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_005751bc;
            }
            lw(v1, a0, 0);
            backedge(ctx);
        }
        // 0x005751c0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005751bc:
    charge(ctx, 1);
    v0 = 0;
    // 0x005751c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005751C8 sub_5751C8 -- 192 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [m2vInitHandle] Initialises an M2V handle: copies the eight default callback words 0x99B260..0x99B29F to handle +24,
// resets the decoder (sub_56FD58 in the CRI band) and the parameter block (sub_575088 at +88), and marks it valid
// (state 2). Returns the handle.
void sub_5751C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005751c8
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a3 = addiu(v0, -19872);  // &0x99B260
    ldl(v1, a3, 7);  // 0x99B267
    ldr(v1, a3, 0);  // 0x99B260
    ldl(a1, a3, 15);  // 0x99B26F
    ldr(a1, a3, 8);  // 0x99B268
    ldl(a2, a3, 23);  // 0x99B277
    ldr(a2, a3, 16);  // 0x99B270
    sdl(v1, s0, 31);
    sdr(v1, s0, 24);
    sdl(a1, s0, 39);
    sdr(a1, s0, 32);
    sdl(a2, s0, 47);
    sdr(a2, s0, 40);
    ldl(v1, a3, 31);  // 0x99B27F
    ldr(v1, a3, 24);  // 0x99B278
    ldl(a1, a3, 39);  // 0x99B287
    ldr(a1, a3, 32);  // 0x99B280
    ldl(a2, a3, 47);  // 0x99B28F
    ldr(a2, a3, 40);  // 0x99B288
    sdl(v1, s0, 55);
    sdr(v1, s0, 48);
    sdl(a1, s0, 63);
    sdr(a1, s0, 56);
    sdl(a2, s0, 71);
    sdr(a2, s0, 64);
    ldl(v1, a3, 55);  // 0x99B297
    ldr(v1, a3, 48);  // 0x99B290
    ldl(a1, a3, 63);  // 0x99B29F
    ldr(a1, a3, 56);  // 0x99B298
    sdl(v1, s0, 79);
    sdr(v1, s0, 72);
    sdl(a1, s0, 87);
    link(ctx, 0x57525Cu);  // $ra first: the delay slot below depends on it
    sdr(a1, s0, 80);
    call(ctx, gen::fn_sub_56FD58_0056fd58);
    a0 = addiu(s0, 88);
    jal(ctx, 0x575264u, gen::fn_sub_575088_00575088);
    v0 = 2;
    sw(v0, s0, 0);
    v0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00575288 sub_575288 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [m2vDestroy] M2V destroy (h): an invalid handle (sub_5753E8) leaves through the module's error path (a tail jump to
// loc_56F978); otherwise state = 1 (free) and the result is 1.
void sub_575288(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575288
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x575294u, gen::fn_sub_5753E8_005753e8);
    a1 = lui(0xFF03);
    a0 = 0;
    a1 = a1 | 0x201;
    if (v0 != 0) {
        // 0x005752ac
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x005752c0
    charge(ctx, 6);
    v0 = 1;
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005752D8 sub_5752D8 -- 8 bytes; leaf frame (no stack)
// An empty function (jr $ra / nop) of M2V's entry table (slot 0x7B2948).
void sub_5752D8(EEContext& ctx) {
    using namespace hg;
    // 0x005752d8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005752E0 sub_5752E0 -- 176 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [m2vSetCallback] M2V set-callback (h, id, fn): callback 8 defaults to sub_56F618 when fn is null; h == 0 sets the
// default table entry (0x99B260 + 4 * id) and the same entry of every valid handle (sub_575390); a valid handle sets
// its own (+24 + 4 * id); an invalid one leaves through the error path (loc_56F978).
void sub_5752E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005752e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 8;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x18);
    a0 = s2;
    if (s2 == v0) {
        // 0x0057530c
        charge(ctx, 2);
        v0 = 0x570000;
        if (s1 == 0) {
            // 0x00575314
            charge(ctx, 1);
            s1 = addiu(v0, -2536);
        }
    }
    // 0x00575318
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00575320
        charge(ctx, 5);
        a1 = s1;
        jal(ctx, 0x575320u, gen::fn_sub_575390_00575390);
        v0 = 0x9A0000;
        a0 = addiu(v0, -19872);  // &0x99B260
        // 0x0057536c (the shared epilogue, written out on this path)
        charge(ctx, 9);
        v0 = sll(s2, 2);
        ld(s2, sp, 0x10);
        v0 = addu(v0, a0);
        ld(s0, sp, 0x0);
        sw(s1, v0, 0);
        ld(ra, sp, 0x18);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00575338
    charge(ctx, 5);
    a0 = s0;
    jal(ctx, 0x575338u, gen::fn_sub_5753E8_005753e8);
    a1 = lui(0xFF03);
    a0 = 0;
    if (v0 != 0) {
        // 0x0057534c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x202;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x00575368
    charge(ctx, 1);
    a0 = addiu(s0, 24);
    // 0x0057536c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s2, 2);
    ld(s2, sp, 0x10);
    v0 = addu(v0, a0);
    ld(s0, sp, 0x0);
    sw(s1, v0, 0);
    ld(ra, sp, 0x18);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00575390 sub_575390 -- 84 bytes; leaf frame (no stack)
// [m2vSetCallbackAll] Sets callback id to fn in every valid M2V handle (state 2) of the pool.
void sub_575390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00575390
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    v0 = addiu(v0, -19872);  // &0x99B260
    lw(a2, v0, 64);  // 0x99B2A0
    lw(v1, v0, 68);  // 0x99B2A4
    if (i64(a2) > 0) {
        // 0x005753a4
        charge(ctx, 5);
        v0 = sll(a0, 2);
        a3 = 2;
        v0 = addu(v1, v0);
        a0 = addiu(v0, 24);
        for (;;) {
            // 0x005753b8
            charge(ctx, 3);
            lw(v0, v1, 0);
            v1 = addiu(v1, libs3::m2v::kHandleStride);
            if (v0 == a3) {
                // 0x005753c4
                charge(ctx, 1);
                sw(a1, a0, 0);
            }
            // 0x005753c8
            charge(ctx, 5);
            a2 = addiu(a2, -1);
            a0 = addiu(a0, libs3::m2v::kHandleStride);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005753dc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00575428 sub_575428 -- 20 bytes; frame 0x10: ra sp+0x0
// A 20-byte wrapper: memcpy(a0, a1, a2) through jal with its own frame and $ra (the module's copy hook). Reached only
// through cosl_10.
void sub_575428(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00575428
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memcpy_00521250(ctx);  // tail call
}

// 0x00575440 sub_575440 -- 20 bytes; frame 0x10: ra sp+0x0
// A 20-byte wrapper: memcpy(a0, a1, a2) through jal with its own frame and $ra (the module's copy hook). Reached only
// through coshl_10.
void sub_575440(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00575440
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memcpy_00521250(ctx);  // tail call
}

// 0x00575458 sub_575458 -- 20 bytes; frame 0x10: ra sp+0x0
// A 20-byte wrapper: memcpy(a0, a1, a2) through jal with its own frame and $ra (the module's copy hook). Reached only
// through expl_10.
void sub_575458(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00575458
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memcpy_00521250(ctx);  // tail call
}

// 0x00575470 atan2l_10 -- 20 bytes; frame 0x10: ra sp+0x0
// The FLIRT name is a false match of a short code shape; the role is read from the instructions. A 20-byte wrapper
// calling sub_575410 (the memcpy hook); no caller.
void atan2l_10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00575470
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_575410_00575410(ctx);  // tail call
}

// 0x00575488 cosl_10 -- 20 bytes; frame 0x10: ra sp+0x0
// The FLIRT name is a false match of a short code shape; the role is read from the instructions. A 20-byte wrapper
// calling sub_575428; no caller.
void cosl_10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00575488
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_575428_00575428(ctx);  // tail call
}

// 0x005754A0 coshl_10 -- 20 bytes; frame 0x10: ra sp+0x0
// The FLIRT name is a false match of a short code shape; the role is read from the instructions. A 20-byte wrapper
// calling sub_575440; no caller.
void coshl_10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005754a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_575440_00575440(ctx);  // tail call
}

// 0x005754B8 expl_10 -- 20 bytes; frame 0x10: ra sp+0x0
// The FLIRT name is a false match of a short code shape; the role is read from the instructions. A 20-byte wrapper
// calling sub_575458; no caller.
void expl_10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005754b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_575458_00575458(ctx);  // tail call
}

}  // namespace p3fes::game
