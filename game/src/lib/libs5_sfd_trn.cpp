// Phase 5 slice libs5: CRI Sofdec SFD, the small transfer modules: the method tables 0x7C9DD0, 0x7C9FB0, 0x7CA4D8
// and 0x7CA510 (0x5883B8-0x58C300, 0x59C9F0-0x59CFA0).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_sub_5883B8_005883b8(p3fes::EEContext&);
void fn_sub_5883C8_005883c8(p3fes::EEContext&);
void fn_sub_588438_00588438(p3fes::EEContext&);
void fn_sub_5884A8_005884a8(p3fes::EEContext&);
void fn_sub_588518_00588518(p3fes::EEContext&);
void fn_sub_588558_00588558(p3fes::EEContext&);
void fn_sub_588560_00588560(p3fes::EEContext&);
void fn_sub_5885B0_005885b0(p3fes::EEContext&);
void fn_sub_5885F8_005885f8(p3fes::EEContext&);
void fn_sub_588F48_00588f48(p3fes::EEContext&);
void fn_sub_589BE0_00589be0(p3fes::EEContext&);
void fn_sub_589CB0_00589cb0(p3fes::EEContext&);
void fn_sub_589CD0_00589cd0(p3fes::EEContext&);
void fn_sub_589D10_00589d10(p3fes::EEContext&);
void fn_sub_58C130_0058c130(p3fes::EEContext&);
void fn_sub_58C140_0058c140(p3fes::EEContext&);
void fn_sub_58C168_0058c168(p3fes::EEContext&);
void fn_sub_58C170_0058c170(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59BC88_0059bc88(p3fes::EEContext&);
void fn_sub_59BCB8_0059bcb8(p3fes::EEContext&);
void fn_sub_59C9F0_0059c9f0(p3fes::EEContext&);
void fn_sub_59CA00_0059ca00(p3fes::EEContext&);
void fn_sub_59CA48_0059ca48(p3fes::EEContext&);
void fn_sub_59CAC8_0059cac8(p3fes::EEContext&);
void fn_sub_59CAD0_0059cad0(p3fes::EEContext&);
void fn_sub_59CB50_0059cb50(p3fes::EEContext&);
void fn_sub_59CB58_0059cb58(p3fes::EEContext&);
void fn_sub_59CB60_0059cb60(p3fes::EEContext&);
void fn_sub_59CB90_0059cb90(p3fes::EEContext&);
void fn_sub_59CC08_0059cc08(p3fes::EEContext&);
void fn_sub_59CC30_0059cc30(p3fes::EEContext&);
void fn_sub_59CC48_0059cc48(p3fes::EEContext&);
void fn_sub_59CCF8_0059ccf8(p3fes::EEContext&);
void fn_sub_59CD08_0059cd08(p3fes::EEContext&);
void fn_sub_59CD60_0059cd60(p3fes::EEContext&);
void fn_sub_59CDE0_0059cde0(p3fes::EEContext&);
void fn_sub_59CE28_0059ce28(p3fes::EEContext&);
void fn_sub_59CEA8_0059cea8(p3fes::EEContext&);
void fn_sub_59CEB0_0059ceb0(p3fes::EEContext&);
void fn_sub_59CEB8_0059ceb8(p3fes::EEContext&);
void fn_sub_59CEC0_0059cec0(p3fes::EEContext&);
void fn_sub_59CF28_0059cf28(p3fes::EEContext&);
void fn_sub_59CF70_0059cf70(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x005883B8 sub_5883B8 -- 8 bytes; leaf frame (no stack)
// [sfdTrn7Init] SFD transfer 0x7C9DD0: init, returns 0.
void sub_5883B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005883b8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005883C8 sub_5883C8 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdTrn7ExecServer] SFD transfer 0x7C9DD0 (slot 7): the server: with parameter 6, the input and output end checks.
void sub_5883C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005883c8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5883D8u, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 == 0) {
        // 0x005883f8
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005883e8
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    // 0x00588408
    charge(ctx, 12);
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x588414u, gen::fn_sub_588438_00588438);
    a0 = s0;
    jal(ctx, 0x58841Cu, gen::fn_sub_5884A8_005884a8);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00588438 sub_588438 -- 132 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdTrn7CheckInputEnd] SFD transfer slot 7: input end -- unless already ended, when its stream (+8476) ended sets
// +8460; $v0 476 (the slot's offset).
void sub_588438(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588438
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 7;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x588450u, gen::fn_sub_59BC88_0059bc88);
    a0 = s0;
    if (v0 == s1) {
        // 0x00588490 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00588460
    charge(ctx, 6);
    link(ctx, 0x588460u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdh::kTrn7Stream);
    call(ctx, gen::fn_sub_589CD0_00589cd0);
    a0 = s0;
    a1 = 7;
    a2 = 1;
    if (v0 != s1) {
        // 0x00588490 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00588478
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x0059bc70
    charge(ctx, 6);
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, 7984);
}

// 0x005884A8 sub_5884A8 -- 132 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdTrn7CheckOutputEnd] SFD transfer slot 7: output end -- sets +8464 when the stream's output ended.
void sub_5884A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005884a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 7;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x5884C0u, gen::fn_sub_59BCB8_0059bcb8);
    a0 = s0;
    if (v0 == s1) {
        // 0x00588500 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005884d0
    charge(ctx, 6);
    link(ctx, 0x5884D0u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdh::kTrn7Stream);
    call(ctx, gen::fn_sub_589D10_00589d10);
    a0 = s0;
    a1 = 7;
    a2 = 1;
    if (v0 != s1) {
        // 0x00588500 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005884e8
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x0059bca0
    charge(ctx, 6);
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, 7988);
}

// 0x00588518 sub_588518 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdTrn7Create] SFD transfer slot 7: create -- with parameter 6, its work is the handle's +13916.
void sub_588518(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588518
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x588528u, gen::fn_sub_599408_00599408);
    v1 = addiu(s0, 13916);
    a0 = v1;
    if (v0 != 0) {
        // 0x0058853c
        charge(ctx, 3);
        link(ctx, 0x58853Cu);  // $ra first: the delay slot below depends on it
        sw(v1, s0, sfdh::kTrn7Work);
        call(ctx, gen::fn_sub_588558_00588558);
        v0 = 0;
    }
    // 0x00588548 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00588558 sub_588558 -- 8 bytes; leaf frame (no stack)
// [sfdTrn7InitWork] SFD transfer slot 7: an empty work init.
void sub_588558(EEContext& ctx) {
    using namespace hg;
    // 0x00588558
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00588560 sub_588560 -- 8 bytes; leaf frame (no stack)
// [sfdTrn7Destroy] SFD transfer 0x7C9DD0: destroy, returns 0.
void sub_588560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00588560
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005885B0 sub_5885B0 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdTrn7Start] SFD transfer 0x7C9DD0: start -- with parameter 6, method 6 of slot 3 (the audio transfer).
void sub_5885B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005885b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5885C0u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 3;
    a2 = 6;
    a3 = 0;
    t0 = 0;
    if (v0 != 0) {
        // 0x005885e0
        charge(ctx, 2);
        jal(ctx, 0x5885E0u, gen::fn_sub_59BC20_0059bc20);
    }
    // 0x005885e8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005885F8 sub_5885F8 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdTrn7Stop] SFD transfer 0x7C9DD0: stop -- method 7 of slot 3.
void sub_5885F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005885f8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 6;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x588608u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 3;
    a2 = 7;
    a3 = 0;
    t0 = 0;
    if (v0 != 0) {
        // 0x00588628
        charge(ctx, 2);
        jal(ctx, 0x588628u, gen::fn_sub_59BC20_0059bc20);
    }
    // 0x00588630 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058C130 sub_58C130 -- 8 bytes; leaf frame (no stack)
// [sfdTrn0Init] SFD transfer 0x7C9FB0: init, returns 0.
void sub_58C130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c130
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C140 sub_58C140 -- 36 bytes; frame 0x10: ra sp+0x0
// [sfdTrn0ExecServer] SFD transfer 0x7C9FB0 (slot 0): the server marks its stream (+8004) ended. Returns 0.
void sub_58C140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c140
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 1;
    sd(ra, sp, 0x0);
    link(ctx, 0x58C14Cu);  // $ra first: the delay slot below depends on it
    lw(a1, a0, 8004);
    call(ctx, gen::fn_sub_589CB0_00589cb0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0058C168 sub_58C168 -- 8 bytes; leaf frame (no stack)
// [sfdTrn0Create] SFD transfer 0x7C9FB0: create, returns 0.
void sub_58C168(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c168
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C170 sub_58C170 -- 8 bytes; leaf frame (no stack)
// [sfdTrn0Destroy] SFD transfer 0x7C9FB0: destroy, returns 0.
void sub_58C170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c170
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059C9F0 sub_59C9F0 -- 8 bytes; leaf frame (no stack)
// [sfdTrn8Init] SFD transfer 0x7CA4D8: init, returns 0.
void sub_59C9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059c9f0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CA00 sub_59CA00 -- 68 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [sfdTrn8ExecServer] SFD transfer 0x7CA4D8 (slot 8): the server: output end, the (empty) step, input end; returns
// the step's 0.
void sub_59CA00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ca00
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x59CA10u, gen::fn_sub_59CA48_0059ca48);
    a0 = s1;
    jal(ctx, 0x59CA18u, gen::fn_sub_59CB58_0059cb58);
    a0 = s1;
    s0 = v0;
    jal(ctx, 0x59CA24u, gen::fn_sub_59CAD0_0059cad0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0059CA48 sub_59CA48 -- 148 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdTrn8CheckOutputEnd] SFD transfer slot 8: output end -- sets +8532 when its stream (+8544) ended and the check
// allows; $v0 544.
void sub_59CA48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ca48
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 8;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x59CA60u, gen::fn_sub_59BCB8_0059bcb8);
    a0 = s0;
    if (v0 == s1) {
        // 0x0059cab0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ca70
    charge(ctx, 4);
    link(ctx, 0x59CA70u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdh::kTrn8Stream);
    call(ctx, gen::fn_sub_589D10_00589d10);
    a0 = s0;
    if (v0 != s1) {
        // 0x0059cab0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ca80
    charge(ctx, 4);
    jal(ctx, 0x59CA80u, gen::fn_sub_59CAC8_0059cac8);
    a0 = s0;
    if (v0 == 0) {
        // 0x0059cab0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ca90
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = 8;
    ld(ra, sp, 0x10);
    a2 = 1;
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x0059bca0
    charge(ctx, 6);
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, 7988);
}

// 0x0059CAD0 sub_59CAD0 -- 148 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdTrn8CheckInputEnd] SFD transfer slot 8: input end -- sets +8528.
void sub_59CAD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cad0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 8;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x59CAE8u, gen::fn_sub_59BC88_0059bc88);
    a0 = s0;
    if (v0 == s1) {
        // 0x0059cb38 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059caf8
    charge(ctx, 4);
    link(ctx, 0x59CAF8u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdh::kTrn8Stream);
    call(ctx, gen::fn_sub_589CD0_00589cd0);
    a0 = s0;
    if (v0 != s1) {
        // 0x0059cb38 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059cb08
    charge(ctx, 4);
    jal(ctx, 0x59CB08u, gen::fn_sub_59CB50_0059cb50);
    a0 = s0;
    if (v0 == 0) {
        // 0x0059cb38 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059cb18
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = 8;
    ld(ra, sp, 0x10);
    a2 = 1;
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x0059bc70
    charge(ctx, 6);
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, 7984);
}

// 0x0059CB50 sub_59CB50 -- 8 bytes; leaf frame (no stack)
// [sfdTrn8CanEndInput] SFD transfer slot 8: the input-end check, always 1.
void sub_59CB50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cb50
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0059CB58 sub_59CB58 -- 8 bytes; leaf frame (no stack)
// [sfdTrn8Step] SFD transfer slot 8: the empty server step, 0.
void sub_59CB58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cb58
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CB60 sub_59CB60 -- 48 bytes; frame 0x10: ra sp+0x0
// [sfdTrn8Create] SFD transfer slot 8: create -- the work at +13944, its three entries registered (sub_59CB90).
void sub_59CB60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cb60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    a1 = addiu(v0, 13944);
    v0 = addiu(v0, 8528);
    sw(a1, v0, 8);
    link(ctx, 0x59CB78u);  // $ra first: the delay slot below depends on it
    lw(a2, v0, 16);
    call(ctx, gen::fn_sub_59CB90_0059cb90);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059CB90 sub_59CB90 -- 120 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [sfdTrn8InitWork] SFD transfer slot 8: clears the work's count and registers three cleared 16-byte entries
// (sub_588F48).
void sub_59CB90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cb90
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = addiu(a1, 4);
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(ra, sp, 0x20);
    sw(zero, a1, 0);
    for (;;) {
        // 0x0059cbc0
        charge(ctx, 12);
        a0 = s0;
        jal(ctx, 0x59CBC0u, gen::fn_sub_59CC08_0059cc08);
        a0 = s3;
        a2 = s1;
        s1 = addiu(s1, 1);
        a3 = s0;
        s0 = addiu(s0, 16);
        a1 = s2;
        jal(ctx, 0x59CBDCu, gen::fn_sub_588F48_00588f48);
        v0 = slti(s1, 3);
        ld(ra, sp, 0x20);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0059cbf0
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    sp = addiu(sp, 0x30);
}

// 0x0059CC08 sub_59CC08 -- 36 bytes; frame 0x10: ra sp+0x0
// [sfdTrn8ClearEntry] SFD transfer slot 8: clears a 16-byte entry.
void sub_59CC08(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cc08
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59CC30_0059cc30(ctx);  // tail call
}

// 0x0059CC30 sub_59CC30 -- 20 bytes; leaf frame (no stack)
// [sfdSetEntry] SFD: stores four words in a 16-byte entry (a1, a2, a3, the stack word).
void sub_59CC30(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0059cc30
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(t0, a0, 12);
    sw(a1, a0, 0);
    sw(a2, a0, 4);
    sw(a3, a0, 8);
}

// 0x0059CC48 sub_59CC48 -- 8 bytes; leaf frame (no stack)
// [sfdTrn8Destroy] SFD transfer 0x7CA4D8: destroy, returns 0.
void sub_59CC48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cc48
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CCF8 sub_59CCF8 -- 8 bytes; leaf frame (no stack)
// [sfdTrn6Init] SFD transfer 0x7CA510: init, returns 0.
void sub_59CCF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059ccf8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CD08 sub_59CD08 -- 88 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [sfdTrn6ExecServer] SFD transfer 0x7CA510 (slot 6): the server: with parameter 5, output end, the (empty) step,
// input end.
void sub_59CD08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cd08
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 5;
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x59CD1Cu, gen::fn_sub_599408_00599408);
    a0 = s1;
    if (v0 != 0) {
        // 0x0059cd2c
        charge(ctx, 8);
        jal(ctx, 0x59CD2Cu, gen::fn_sub_59CD60_0059cd60);
        a0 = s1;
        jal(ctx, 0x59CD34u, gen::fn_sub_59CEB0_0059ceb0);
        a0 = s1;
        s0 = v0;
        jal(ctx, 0x59CD40u, gen::fn_sub_59CE28_0059ce28);
        v0 = s0;
    }
    // 0x0059cd4c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059CD60 sub_59CD60 -- 148 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdTrn6CheckOutputEnd] SFD transfer slot 6: output end -- sets +8396 when its stream (+8408) ended; $v0 408.
void sub_59CD60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cd60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 6;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x59CD78u, gen::fn_sub_59BCB8_0059bcb8);
    a0 = s0;
    if (v0 == s1) {
        // 0x0059cdc8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059cd88
    charge(ctx, 4);
    link(ctx, 0x59CD88u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdh::kTrn6Stream);
    call(ctx, gen::fn_sub_589D10_00589d10);
    a0 = s0;
    if (v0 != s1) {
        // 0x0059cdc8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059cd98
    charge(ctx, 4);
    jal(ctx, 0x59CD98u, gen::fn_sub_59CDE0_0059cde0);
    a0 = s0;
    if (v0 == 0) {
        // 0x0059cdc8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059cda8
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = 6;
    ld(ra, sp, 0x10);
    a2 = 1;
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x0059bca0
    charge(ctx, 6);
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, 7988);
}

// 0x0059CE28 sub_59CE28 -- 148 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdTrn6CheckInputEnd] SFD transfer slot 6: input end -- sets +8392.
void sub_59CE28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ce28
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 6;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 1;
    jal(ctx, 0x59CE40u, gen::fn_sub_59BC88_0059bc88);
    a0 = s0;
    if (v0 == s1) {
        // 0x0059ce90 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ce50
    charge(ctx, 4);
    link(ctx, 0x59CE50u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, sfdh::kTrn6Stream);
    call(ctx, gen::fn_sub_589CD0_00589cd0);
    a0 = s0;
    if (v0 != s1) {
        // 0x0059ce90 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ce60
    charge(ctx, 4);
    jal(ctx, 0x59CE60u, gen::fn_sub_59CEA8_0059cea8);
    a0 = s0;
    if (v0 == 0) {
        // 0x0059ce90 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ce70
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = 6;
    ld(ra, sp, 0x10);
    a2 = 1;
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x0059bc70
    charge(ctx, 6);
    v0 = sll(a1, 4);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, 7984);
}

// 0x0059CEA8 sub_59CEA8 -- 8 bytes; leaf frame (no stack)
// [sfdTrn6CanEndInput] SFD transfer slot 6: the input-end check, always 1.
void sub_59CEA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cea8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0059CEB0 sub_59CEB0 -- 8 bytes; leaf frame (no stack)
// [sfdTrn6Step] SFD transfer slot 6: the empty server step, 0.
void sub_59CEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059ceb0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CEB8 sub_59CEB8 -- 8 bytes; leaf frame (no stack)
// [sfdTrn6Create] SFD transfer 0x7CA510: create, returns 0.
void sub_59CEB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059ceb8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CEC0 sub_59CEC0 -- 8 bytes; leaf frame (no stack)
// [sfdTrn6Destroy] SFD transfer 0x7CA510: destroy, returns 0.
void sub_59CEC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cec0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CF28 sub_59CF28 -- 68 bytes; frame 0x10: ra sp+0x0
// [sfdTrn6GetData] SFD transfer slot 6: get data -- while the handle's status is 3 or 4, from its stream
// (sub_589BE0); else 0 bytes.
void sub_59CF28(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cf28
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    a3 = a2;
    lw(v0, v1, 72);
    v0 = addiu(v0, -3);
    v0 = sltiu(v0, 2);
    a2 = a1;
    if (v0 != 0) {
        // 0x0059cf58
        charge(ctx, 2);
        link(ctx, 0x59CF58u);  // $ra first: the delay slot below depends on it
        lw(a1, v1, 8408);
        call(ctx, gen::fn_sub_589BE0_00589be0);
    } else {
        // 0x0059cf4c
        charge(ctx, 3);
        sw(zero, a1, 0);
        v0 = 0;
    }
    // 0x0059cf60 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059CF70 sub_59CF70 -- 148 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [sfdTrn6Forward] SFD transfer slot 6: unless its stream is flagged (+4884), forwards to method 12 of the stream's
// transfer; sets +68.
void sub_59CF70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cf70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    a3 = a2;
    a2 = v0;
    lw(a1, a0, 8408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00589c40
    charge(ctx, 18);
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x10);
    v0 = subu(v0, a1);
    sd(s0, sp, 0x0);
    v0 = sll(v0, 2);
    s0 = a0;
    v0 = addu(v0, a1);
    a1 = 0;
    v0 = sll(v0, 2);
    sd(ra, sp, 0x8);
    t1 = addiu(s0, 4880);
    v1 = a2;
    t1 = addu(t1, v0);
    t0 = a3;
    lw(v0, t1, 4);
    a2 = 12;
    a3 = v1;
    if (v0 == 0) {
        // 0x00589c88
        charge(ctx, 3);
        link(ctx, 0x589C88u);  // $ra first: the delay slot below depends on it
        lw(a1, t1, 76);
        call(ctx, gen::fn_sub_59BC20_0059bc20);
        a1 = v0;
    }
    // 0x00589c94 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v1 = 1;
    ld(ra, sp, 0x8);
    sw(v1, s0, sfdh::kTimeUpd);
    v0 = a1;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
