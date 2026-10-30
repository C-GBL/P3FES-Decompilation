// Slice libs3: CRI Sofdec's MWSFD module (the mwPly movie player): creation parameters, work sizes, the frame getters,
// the handle checks and the player's init.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_r_lock_def_free_2_0057fd58(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_2_0057fd78(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strncat_005244c0(p3fes::EEContext&);
void fn_sub_53EA90_0053ea90(p3fes::EEContext&);
void fn_sub_55D2A0_0055d2a0(p3fes::EEContext&);
void fn_sub_55D3A8_0055d3a8(p3fes::EEContext&);
void fn_sub_55D3F8_0055d3f8(p3fes::EEContext&);
void fn_sub_55DBC0_0055dbc0(p3fes::EEContext&);
void fn_sub_55DC88_0055dc88(p3fes::EEContext&);
void fn_sub_561870_00561870(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_562288_00562288(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_562E90_00562e90(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_57BF98_0057bf98(p3fes::EEContext&);
void fn_sub_57BFB8_0057bfb8(p3fes::EEContext&);
void fn_sub_57BFC0_0057bfc0(p3fes::EEContext&);
void fn_sub_57C210_0057c210(p3fes::EEContext&);
void fn_sub_57C2B0_0057c2b0(p3fes::EEContext&);
void fn_sub_57C398_0057c398(p3fes::EEContext&);
void fn_sub_57C3E8_0057c3e8(p3fes::EEContext&);
void fn_sub_57C4E8_0057c4e8(p3fes::EEContext&);
void fn_sub_57C538_0057c538(p3fes::EEContext&);
void fn_sub_57C568_0057c568(p3fes::EEContext&);
void fn_sub_57C570_0057c570(p3fes::EEContext&);
void fn_sub_57C628_0057c628(p3fes::EEContext&);
void fn_sub_57C680_0057c680(p3fes::EEContext&);
void fn_sub_57C6E0_0057c6e0(p3fes::EEContext&);
void fn_sub_57C800_0057c800(p3fes::EEContext&);
void fn_sub_57C910_0057c910(p3fes::EEContext&);
void fn_sub_57CA78_0057ca78(p3fes::EEContext&);
void fn_sub_57D1D0_0057d1d0(p3fes::EEContext&);
void fn_sub_57D208_0057d208(p3fes::EEContext&);
void fn_sub_57D220_0057d220(p3fes::EEContext&);
void fn_sub_57D308_0057d308(p3fes::EEContext&);
void fn_sub_57D380_0057d380(p3fes::EEContext&);
void fn_sub_57D3C8_0057d3c8(p3fes::EEContext&);
void fn_sub_57D5B0_0057d5b0(p3fes::EEContext&);
void fn_sub_57D5D8_0057d5d8(p3fes::EEContext&);
void fn_sub_57D960_0057d960(p3fes::EEContext&);
void fn_sub_57D9B0_0057d9b0(p3fes::EEContext&);
void fn_sub_57DA08_0057da08(p3fes::EEContext&);
void fn_sub_57DA90_0057da90(p3fes::EEContext&);
void fn_sub_57DB58_0057db58(p3fes::EEContext&);
void fn_sub_57DC80_0057dc80(p3fes::EEContext&);
void fn_sub_57DC90_0057dc90(p3fes::EEContext&);
void fn_sub_57DF60_0057df60(p3fes::EEContext&);
void fn_sub_57DFB0_0057dfb0(p3fes::EEContext&);
void fn_sub_57E028_0057e028(p3fes::EEContext&);
void fn_sub_57E070_0057e070(p3fes::EEContext&);
void fn_sub_57E110_0057e110(p3fes::EEContext&);
void fn_sub_57E148_0057e148(p3fes::EEContext&);
void fn_sub_57E180_0057e180(p3fes::EEContext&);
void fn_sub_57E1D0_0057e1d0(p3fes::EEContext&);
void fn_sub_57E1D8_0057e1d8(p3fes::EEContext&);
void fn_sub_57E210_0057e210(p3fes::EEContext&);
void fn_sub_57E270_0057e270(p3fes::EEContext&);
void fn_sub_57E290_0057e290(p3fes::EEContext&);
void fn_sub_57E298_0057e298(p3fes::EEContext&);
void fn_sub_57E320_0057e320(p3fes::EEContext&);
void fn_sub_57E360_0057e360(p3fes::EEContext&);
void fn_sub_57E378_0057e378(p3fes::EEContext&);
void fn_sub_57E3D0_0057e3d0(p3fes::EEContext&);
void fn_sub_57E428_0057e428(p3fes::EEContext&);
void fn_sub_57E530_0057e530(p3fes::EEContext&);
void fn_sub_57E698_0057e698(p3fes::EEContext&);
void fn_sub_57E6E0_0057e6e0(p3fes::EEContext&);
void fn_sub_57E730_0057e730(p3fes::EEContext&);
void fn_sub_57E910_0057e910(p3fes::EEContext&);
void fn_sub_57E9A8_0057e9a8(p3fes::EEContext&);
void fn_sub_57E9D8_0057e9d8(p3fes::EEContext&);
void fn_sub_57EA18_0057ea18(p3fes::EEContext&);
void fn_sub_57EA80_0057ea80(p3fes::EEContext&);
void fn_sub_57EB38_0057eb38(p3fes::EEContext&);
void fn_sub_57EB80_0057eb80(p3fes::EEContext&);
void fn_sub_57EC00_0057ec00(p3fes::EEContext&);
void fn_sub_57EC38_0057ec38(p3fes::EEContext&);
void fn_sub_57ED00_0057ed00(p3fes::EEContext&);
void fn_sub_57ED40_0057ed40(p3fes::EEContext&);
void fn_sub_57EDA8_0057eda8(p3fes::EEContext&);
void fn_sub_57EDD8_0057edd8(p3fes::EEContext&);
void fn_sub_57EE50_0057ee50(p3fes::EEContext&);
void fn_sub_57EF08_0057ef08(p3fes::EEContext&);
void fn_sub_57EF78_0057ef78(p3fes::EEContext&);
void fn_sub_57F050_0057f050(p3fes::EEContext&);
void fn_sub_57F058_0057f058(p3fes::EEContext&);
void fn_sub_57F0A8_0057f0a8(p3fes::EEContext&);
void fn_sub_57F0F0_0057f0f0(p3fes::EEContext&);
void fn_sub_57F328_0057f328(p3fes::EEContext&);
void fn_sub_57F390_0057f390(p3fes::EEContext&);
void fn_sub_57F600_0057f600(p3fes::EEContext&);
void fn_sub_57F670_0057f670(p3fes::EEContext&);
void fn_sub_57F6F8_0057f6f8(p3fes::EEContext&);
void fn_sub_57F750_0057f750(p3fes::EEContext&);
void fn_sub_57F768_0057f768(p3fes::EEContext&);
void fn_sub_57F920_0057f920(p3fes::EEContext&);
void fn_sub_57F980_0057f980(p3fes::EEContext&);
void fn_sub_57FA28_0057fa28(p3fes::EEContext&);
void fn_sub_57FA50_0057fa50(p3fes::EEContext&);
void fn_sub_57FA70_0057fa70(p3fes::EEContext&);
void fn_sub_57FAB8_0057fab8(p3fes::EEContext&);
void fn_sub_57FAF0_0057faf0(p3fes::EEContext&);
void fn_sub_57FC60_0057fc60(p3fes::EEContext&);
void fn_sub_57FC90_0057fc90(p3fes::EEContext&);
void fn_sub_57FCB0_0057fcb0(p3fes::EEContext&);
void fn_sub_580628_00580628(p3fes::EEContext&);
void fn_sub_580900_00580900(p3fes::EEContext&);
void fn_sub_580C80_00580c80(p3fes::EEContext&);
void fn_sub_580E10_00580e10(p3fes::EEContext&);
void fn_sub_5811D0_005811d0(p3fes::EEContext&);
void fn_sub_581690_00581690(p3fes::EEContext&);
void fn_sub_581798_00581798(p3fes::EEContext&);
void fn_sub_582798_00582798(p3fes::EEContext&);
void fn_sub_5827F0_005827f0(p3fes::EEContext&);
void fn_sub_5827F8_005827f8(p3fes::EEContext&);
void fn_sub_582810_00582810(p3fes::EEContext&);
void fn_sub_583028_00583028(p3fes::EEContext&);
void fn_sub_5833E8_005833e8(p3fes::EEContext&);
void fn_sub_583410_00583410(p3fes::EEContext&);
void fn_sub_583470_00583470(p3fes::EEContext&);
void fn_sub_5834A0_005834a0(p3fes::EEContext&);
void fn_sub_583500_00583500(p3fes::EEContext&);
void fn_sub_5835A8_005835a8(p3fes::EEContext&);
void fn_sub_585100_00585100(p3fes::EEContext&);
void fn_sub_585210_00585210(p3fes::EEContext&);
void fn_sub_5852F8_005852f8(p3fes::EEContext&);
void fn_sub_585360_00585360(p3fes::EEContext&);
void fn_sub_5853B8_005853b8(p3fes::EEContext&);
void fn_sub_585410_00585410(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_5860E8_005860e8(p3fes::EEContext&);
void fn_sub_586130_00586130(p3fes::EEContext&);
void fn_sub_586140_00586140(p3fes::EEContext&);
void fn_sub_5862F0_005862f0(p3fes::EEContext&);
void fn_sub_5864A8_005864a8(p3fes::EEContext&);
void fn_sub_5864C0_005864c0(p3fes::EEContext&);
void fn_sub_586800_00586800(p3fes::EEContext&);
void fn_sub_58A3E8_0058a3e8(p3fes::EEContext&);
void fn_sub_58BC20_0058bc20(p3fes::EEContext&);
void fn_sub_58BC30_0058bc30(p3fes::EEContext&);
void fn_sub_58BD68_0058bd68(p3fes::EEContext&);
void fn_sub_58BEF0_0058bef0(p3fes::EEContext&);
void fn_sub_58E310_0058e310(p3fes::EEContext&);
void fn_sub_58E4A0_0058e4a0(p3fes::EEContext&);
void fn_sub_58E530_0058e530(p3fes::EEContext&);
void fn_sub_58E800_0058e800(p3fes::EEContext&);
void fn_sub_593BF8_00593bf8(p3fes::EEContext&);
void fn_sub_593C58_00593c58(p3fes::EEContext&);
void fn_sub_593DB0_00593db0(p3fes::EEContext&);
void fn_sub_594B68_00594b68(p3fes::EEContext&);
void fn_sub_594E50_00594e50(p3fes::EEContext&);
void fn_sub_596C28_00596c28(p3fes::EEContext&);
void fn_sub_5971E8_005971e8(p3fes::EEContext&);
void fn_sub_597368_00597368(p3fes::EEContext&);
void fn_sub_597B88_00597b88(p3fes::EEContext&);
void fn_sub_597C28_00597c28(p3fes::EEContext&);
void fn_sub_597D20_00597d20(p3fes::EEContext&);
void fn_sub_597E20_00597e20(p3fes::EEContext&);
void fn_sub_599100_00599100(p3fes::EEContext&);
void fn_sub_5996B0_005996b0(p3fes::EEContext&);
void fn_sub_59AD80_0059ad80(p3fes::EEContext&);
void fn_sub_5A1340_005a1340(p3fes::EEContext&);
void fn_sub_5A1790_005a1790(p3fes::EEContext&);
void fn_thread_leave_1_00597aa0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0057C4E8 sub_57C4E8 -- 80 bytes; frame 0x10: ra sp+0x0
// [mwsfdBufferFormat] MWSFD buffer-format code of a creation parameter (cprm +36): 1 -> 1, 0 / 2 -> 2, 3 -> 3, anything
// else prints "E206011: MwsfdCrePrm: illigal buffmt." through MWSFD's error printer sub_585590 and gives 3.
void sub_57C4E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057c4e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    v1 = 1;
    if (a0 != v0) {
        // 0x0057c4fc
        charge(ctx, 2);
        v1 = 2;
        if (a0 != 0) {
            // 0x0057c504
            charge(ctx, 3);
            v0 = 2;
            cc = a0 == v0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (!cc) {
                // 0x0057c510
                charge(ctx, 2);
                v1 = 3;
                if (a0 != v0) {
                    // 0x0057c518
                    charge(ctx, 4);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, 31568);  // "E206011: MwsfdCrePrm: illigal buffmt."
                    jal(ctx, 0x57C51Cu, gen::fn_sub_585590_00585590);
                    v1 = 3;
                }
            }
        }
    }
    // 0x0057c528 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x0057C538 sub_57C538 -- 44 bytes; leaf frame (no stack)
// [mwsfdCalcFixedSizes] MWSFD fixed work sizes: *a = 16,384, *b = 256, *c = 1,536; returns their sum (18,176).
void sub_57C538(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0057c538
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 16384;
    v1 = 256;
    sw(v0, a1, 0);
    a0 = 1536;
    sw(v1, a2, 0);
    sw(a0, a3, 0);
    lw(v0, a1, 0);
    lw(v1, a2, 0);
    v0 = addu(v0, v1);
    v0 = addu(v0, a0);
}

// 0x0057C568 sub_57C568 -- 8 bytes; leaf frame (no stack)
// [mwsfdCalcHeaderSize] Returns 256 (an MWSFD fixed work size).
void sub_57C568(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057c568
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 256;
}

// 0x0057C570 sub_57C570 -- 184 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// [mwsfdCalcWorkSize] MWSFD work size of a creation parameter without the SFD part: the buffer sizes (sub_57C2B0), the
// frame sizes (sub_57C3E8), the fixed sizes (sub_57C538 / sub_57C568) and 2,112 + 64 bytes of records, summed.
void sub_57C570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c570
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = sp;
    a2 = addiu(sp, 0x4);
    a3 = addiu(sp, 0x8);
    t0 = addiu(sp, 0xC);
    t1 = addiu(sp, 0x10);
    t2 = addiu(sp, 0x14);
    sd(s0, sp, 0x30);
    sd(ra, sp, 0x38);
    s0 = a0;
    jal(ctx, 0x57C594u, gen::fn_sub_57C2B0_0057c2b0);
    a1 = addiu(sp, 0x18);
    a2 = addiu(sp, 0x1C);
    a0 = s0;
    jal(ctx, 0x57C5A4u, gen::fn_sub_57C3E8_0057c3e8);
    a0 = s0;
    a1 = addiu(sp, 0x20);
    a2 = addiu(sp, 0x24);
    a3 = addiu(sp, 0x28);
    jal(ctx, 0x57C5B8u, gen::fn_sub_57C538_0057c538);
    s0 = v0;
    jal(ctx, 0x57C5C0u, gen::fn_sub_57C568_0057c568);
    lw(a0, sp, 0x8);
    lw(v1, sp, 0x4);
    lw(a1, sp, 0xC);
    v1 = addu(v1, a0);
    lw(a0, sp, 0x18);
    lw(a2, sp, 0x0);
    v1 = addu(v1, a1);
    lw(t0, sp, 0x10);
    v1 = addiu(v1, 64);
    lw(a1, sp, 0x1C);
    v1 = addu(v1, s0);
    lw(a3, sp, 0x14);
    a2 = addu(a2, t0);
    a0 = addiu(a0, 64);
    v1 = addu(v1, a2);
    a1 = addu(a1, a3);
    ld(s0, sp, 0x30);
    a0 = addu(a0, a1);
    ld(ra, sp, 0x38);
    v1 = addu(v1, a0);
    v1 = addu(v1, v0);
    v0 = addiu(v1, 2048);
    sp = addiu(sp, 0x40);
}

// 0x0057C628 sub_57C628 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdCalcSfdWorkSize] The SFD part of an MWSFD work size: SFD's own work size for the picture size (sub_5827F0 with
// +8 / +12), plus 0x20000 when the creation parameter asks for the additional-information stream (sub_5833E8 == 1).
void sub_57C628(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c628
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(a1, s0, 12);
    link(ctx, 0x57C640u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);
    call(ctx, gen::fn_sub_5827F0_005827f0);
    a0 = s0;
    s1 = v0;
    jal(ctx, 0x57C64Cu, gen::fn_sub_5833E8_005833e8);
    v1 = 1;
    a0 = 0x20000;
    a0 = addu(a0, s1);
    v0 = v0 ^ v1;
    ld(s0, sp, 0x0);
    if (v0 == 0) s1 = a0;
    ld(ra, sp, 0x10);
    v0 = s1;
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0057C680 sub_57C680 -- 92 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [mwsfdCalcPlayerWorkSize] The whole work size of a player (sub_57C570 + sub_57C628); a null cprm prints "E1122613
// ...: cprm is NULL." and gives 0. The game's movie task (sub_10A860) calls it.
void sub_57C680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c680
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (s1 != 0) {
        // 0x0057c6b0
        charge(ctx, 6);
        jal(ctx, 0x57C6B0u, gen::fn_sub_57C570_0057c570);
        a0 = s1;
        s0 = v0;
        jal(ctx, 0x57C6BCu, gen::fn_sub_57C628_0057c628);
        v0 = addu(s0, v0);
    } else {
        // 0x0057c698
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 31720);  // "E1122613 mwPlyCalcWorkCprmSfd: cprm is NULL."
        jal(ctx, 0x57C69Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x0057c6c8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057C6E0 sub_57C6E0 -- 80 bytes; leaf frame (no stack)
// [mwsfdSetFramePool] Registers an external frame pool (count, size, frames[]): 0x7B2F40 = count, 0x7B2F44 = size, the
// frame addresses copied to 0x99EB88... No caller.
void sub_57C6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0057c6e0
    enter(ctx, 7);  // entry check point + this block's cycles
    t0 = a0;
    v0 = 0x7B0000;
    v1 = 0x7B0000;
    sw(t0, v0, 12096);  // 0x7B2F40
    sw(a1, v1, 12100);  // 0x7B2F44
    a3 = 0;
    if (i64(t0) > 0) {
        // 0x0057c6fc
        charge(ctx, 3);
        v0 = 0x9A0000;
        t1 = addiu(v0, -5240);  // &0x99EB88
        for (;;) {
            // 0x0057c708
            charge(ctx, 8);
            v0 = sll(a3, 2);
            a3 = addiu(a3, 1);
            v1 = addu(v0, a2);
            v0 = addu(v0, t1);
            lw(a0, v1, 0);
            a1 = slt(a3, t0);
            sw(a0, v0, 0);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0057c728 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057C800 sub_57C800 -- 268 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// [mwsfdAllocFrames] MWSFD frame buffers of a player (h, cprm, out[2]): with no external pool both frames are allocated
// from the work (sub_57E070); with an external pool its first two frames are used when it has at least two and each
// holds 9 * w * h / 2 + 10,304 bytes, else out = 0 and -1.
void sub_57C800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057c800
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(ra, sp, 0x28);
    t0 = 0x80000;
    lw(t1, v0, 12096);  // 0x7B2F40
    t0 = t0 | 0x40D0;
    lw(v1, a1, 12);
    lw(a3, a1, 8);
    sw(t0, sp, 0x4);
    mult(a3, a3, v1);
    v0 = sll(a3, 3);
    v0 = addu(v0, a3);
    v1 = srl(v0, 31);
    v0 = addu(v0, v1);
    v0 = sra(v0, 1);
    a1 = addiu(v0, 10304);
    sw(a1, sp, 0x0);
    if (t1 == 0) {
        // 0x0057c8b8
        charge(ctx, 7);
        jal(ctx, 0x57C8B8u, gen::fn_sub_57E070_0057e070);
        a0 = s1;
        sw(v0, s0, 0);
        link(ctx, 0x57C8C8u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x4);
        call(ctx, gen::fn_sub_57E070_0057e070);
        sw(v0, s0, 4);
    } else {
        // 0x0057c860
        charge(ctx, 3);
        v0 = slti(t1, 2);
        if (v0 != 0) {
            sw(zero, s0, 0);
        } else {
            // 0x0057c86c
            charge(ctx, 5);
            v0 = 0x7B0000;
            lw(v0, v0, 12100);  // 0x7B2F44
            v1 = slt(v0, a1);
            if (v1 != 0) {
                sw(zero, s0, 0);
                goto L_0057c8a8;
            }
            // 0x0057c880
            charge(ctx, 3);
            v0 = slt(v0, t0);
            if (v0 != 0) {
                sw(zero, s0, 0);
                goto L_0057c8a8;
            }
            // 0x0057c88c
            charge(ctx, 7);
            v0 = 0x9A0000;
            v0 = addiu(v0, -5240);  // &0x99EB88
            lw(v1, v0, 4);  // 0x99EB8C
            lw(a0, v0, 0);  // 0x99EB88
            sw(v1, s0, 4);
            sw(a0, s0, 0);
            goto L_0057c8d4;
        }
    L_0057c8a8:
        charge(ctx, 3);
        s2 = si(-1);
        sw(zero, s0, 4);
    }
L_0057c8d4:
    charge(ctx, 3);
    lw(v0, s0, 0);
    if (v0 == 0) {
        s2 = si(-1);
    } else {
        // 0x0057c8e0
        charge(ctx, 3);
        lw(v0, s0, 4);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = s2;
        if (!cc) {
            // 0x0057c8ec
            charge(ctx, 1);
            s2 = si(-1);
            goto L_0057c8f0;
        }
        // 0x0057c8f4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_0057c8f0:
    charge(ctx, 1);
    v0 = s2;
    // 0x0057c8f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0057C910 sub_57C910 -- 356 bytes; frame 0x40: s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x38
// [mwsfdAllocPictures] MWSFD picture buffers of a player (h, cprm, out): the size per frame from the macroblock count
// (1,024 bytes per macroblock in format 2, 384 otherwise, + 64), allocated from the work (sub_57E070) or taken from the
// external pool (0x99EB90..) for the cprm's frame count.
void sub_57C910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c910
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s4, sp, 0x20);
    s4 = 0;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(s6, sp, 0x30);
    s6 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x38);
    lw(s1, a1, 8);
    lw(s0, a1, 12);
    lw(a0, a1, 36);
    link(ctx, 0x57C94Cu);  // $ra first: the delay slot below depends on it
    lw(s3, a1, 16);
    call(ctx, gen::fn_sub_57C4E8_0057c4e8);
    a2 = addiu(s1, 15);
    a0 = slti(s1, 0);
    v1 = slti(s0, 0);
    a1 = addiu(s0, 15);
    if (a0 != 0) s1 = a2;
    if (v1 != 0) s0 = a1;
    a0 = 2;
    s1 = sra(s1, 4);
    v1 = sra(s0, 4);
    if (v0 != a0) {
        // 0x0057c988
        charge(ctx, 4);
        mult(v1, s1, v1);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 7);
    } else {
        // 0x0057c97c
        charge(ctx, 3);
        mult(v0, s1, v1);
        v0 = sll(v0, 10);
    }
    // 0x0057c998
    charge(ctx, 5);
    s2 = addiu(v0, 64);
    v0 = 0x7B0000;
    lw(v1, v0, 12096);  // 0x7B2F40
    v0 = addiu(s3, 2);
    if (v1 == 0) {
        // 0x0057ca10
        charge(ctx, 2);
        v0 = s4;
        if (i64(s3) > 0) {
            // 0x0057ca18
            charge(ctx, 4);
            s0 = s3;
            s3 = si(-1);
            s1 = s5;
            for (;;) {
                // 0x0057ca28
                charge(ctx, 8);
                a0 = s6;
                a1 = s2;
                jal(ctx, 0x57CA2Cu, gen::fn_sub_57E070_0057e070);
                s0 = addiu(s0, -1);
                sw(v0, s1, 0);
                s1 = addiu(s1, 4);
                if (v0 == 0) s4 = s3;
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        L_0057ca48:
            charge(ctx, 1);
            v0 = s4;
        }
    } else {
        // 0x0057c9ac
        charge(ctx, 3);
        v0 = slt(v1, v0);
        if (v0 != 0) {
            s4 = si(-1);
            goto L_0057ca48;
        }
        // 0x0057c9b8
        charge(ctx, 5);
        v1 = 0x7B0000;
        lw(v0, v1, 12100);  // 0x7B2F44
        v0 = slt(v0, s2);
        s0 = 0;
        if (v0 != 0) {
            // 0x0057c9cc
            charge(ctx, 2);
            s4 = si(-1);
            goto L_0057ca48;
        }
        for (;;) {
            // 0x0057c9f8
            charge(ctx, 3);
            v0 = slt(s0, s3);
            if (v0 == 0) {
                break;
            }
            v0 = sll(s0, 2);
            backedge(ctx);
            // 0x0057c9d8
            charge(ctx, 8);
            s0 = addiu(s0, 1);
            a0 = 0x9A0000;
            a0 = addu(a0, v0);
            lw(a0, a0, -5232);
            v0 = addu(v0, s5);
            v1 = si(-1);
            sw(a0, v0, 0);
            if (a0 == 0) s4 = v1;
        }
        // 0x0057ca04
        charge(ctx, 2);
        v0 = s4;
    }
    // 0x0057ca4c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0057CA78 sub_57CA78 -- 1876 bytes; frame 0x130: s0 sp+0xE0, s1 sp+0xE8, s2 sp+0xF0, s3 sp+0xF8, s4 sp+0x100, s5 sp+0x108, s7 sp+0x118, fp sp+0x120, s6 sp+0x110, ra sp+0x128
// [mwsfdSetupPlayerWork] MWSFD player work layout (h, cprm): allocates and attaches every buffer the creation parameter
// needs -- the stream buffers (sub_57C2B0), the SFD handle's creation parameters, the frame / picture buffers
// (sub_57C800 / sub_57C910), the fixed buffers, the header buffer -- through the work allocator (sub_57E070); a
// shortage prints "E2053002: not enough work" / "E4041301: not enough work", a failed SFD create "E20010703C ..." and
// sets the error code (sub_57FC60).
void sub_57CA78(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057ca78
    enter(ctx, 83);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    v0 = 0x9A0000;
    sd(s0, sp, 0xE0);
    v1 = 0x9A0000;
    sd(s1, sp, 0xE8);
    s0 = addiu(v1, -5272);  // &0x99EB68
    sd(s2, sp, 0xF0);
    a2 = 0x9A0000;
    sd(s3, sp, 0xF8);
    s3 = addiu(v0, -5276);  // &0x99EB64
    sd(s4, sp, 0x100);
    s4 = a0;
    sd(s5, sp, 0x108);
    s5 = a1;
    sd(s7, sp, 0x118);
    a1 = 0x9A0000;
    sd(fp, sp, 0x120);
    s1 = addiu(a1, -5268);  // &0x99EB6C
    sd(s6, sp, 0x110);
    s2 = addiu(a2, -5264);  // &0x99EB70
    sd(ra, sp, 0x128);
    t0 = s2;
    t1 = 0x9A0000;
    t1 = addiu(t1, -5248);  // &0x99EB80
    t2 = 0x9A0000;
    t2 = addiu(t2, -5252);  // &0x99EB7C
    lw(v0, s5, 16);
    a3 = s1;
    lw(s6, s5, 0);
    a1 = s3;
    sw(v0, sp, 0xC4);
    a0 = s5;
    a2 = s0;
    lw(v1, s5, 8);
    sw(v1, sp, 0xC8);
    lw(v0, s5, 12);
    link(ctx, 0x57CB08u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xCC);
    call(ctx, gen::fn_sub_57C2B0_0057c2b0);
    a1 = 0x9A0000;
    a2 = 0x9A0000;
    a1 = addiu(a1, -5260);  // &0x99EB74
    a2 = addiu(a2, -5256);  // &0x99EB78
    a0 = s5;
    jal(ctx, 0x57CB20u, gen::fn_sub_57C3E8_0057c3e8);
    a0 = s5;
    a1 = addiu(sp, 0xA0);
    a2 = addiu(sp, 0xA4);
    a3 = addiu(sp, 0xA8);
    jal(ctx, 0x57CB34u, gen::fn_sub_57C538_0057c538);
    jal(ctx, 0x57CB3Cu, gen::fn_sub_57C568_0057c568);
    sw(v0, sp, 0xD8);
    a0 = s4;
    lw(a1, s0, 0);  // 0x99EB68
    lw(v0, s1, 0);  // 0x99EB6C
    lw(v1, s2, 0);  // 0x99EB70
    a1 = addu(a1, v0);
    a1 = addu(a1, v1);
    a1 = addiu(a1, 64);
    jal(ctx, 0x57CB60u, gen::fn_sub_57E070_0057e070);
    a0 = s4;
    sw(v0, sp, 0xBC);
    lw(a1, s3, 0);  // 0x99EB64
    a1 = addiu(a1, 64);
    jal(ctx, 0x57CB74u, gen::fn_sub_57E070_0057e070);
    a0 = s4;
    v1 = addiu(sp, 0x50);
    a1 = s5;
    a2 = v1;
    s7 = v0;
    jal(ctx, 0x57CB8Cu, gen::fn_sub_57C800_0057c800);
    a0 = s4;
    a3 = addiu(sp, 0x60);
    a1 = s5;
    a2 = a3;
    fp = v0;
    jal(ctx, 0x57CBA4u, gen::fn_sub_57C910_0057c910);
    a0 = s6;
    s3 = v0;
    jal(ctx, 0x57CBB0u, gen::fn_sub_57D1D0_0057d1d0);
    v1 = 1;
    if (v0 != v1) {
        s2 = 0;
        // 0x0057cbf8
        charge(ctx, 1);
        s1 = 0;
    } else {
        // 0x0057cbc4
        charge(ctx, 13);
        t0 = 0x9A0000;
        a0 = s4;
        t0 = addiu(t0, -5248);  // &0x99EB80
        link(ctx, 0x57CBD0u);  // $ra first: the delay slot below depends on it
        lw(a1, t0, 0);
        call(ctx, gen::fn_sub_57E070_0057e070);
        a0 = s4;
        t1 = 0x9A0000;
        s2 = v0;
        t1 = addiu(t1, -5252);  // &0x99EB7C
        link(ctx, 0x57CBE8u);  // $ra first: the delay slot below depends on it
        lw(a1, t1, 0);
        call(ctx, gen::fn_sub_57E070_0057e070);
        s1 = v0;
    }
    // 0x0057cbfc
    charge(ctx, 22);
    a1 = 2048;
    a0 = s4;
    jal(ctx, 0x57CC00u, gen::fn_sub_57E070_0057e070);
    a0 = s4;
    lw(a1, sp, 0xA0);
    link(ctx, 0x57CC10u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xC0);
    call(ctx, gen::fn_sub_57E070_0057e070);
    a0 = s4;
    lw(a1, sp, 0xA4);
    link(ctx, 0x57CC20u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xD0);
    call(ctx, gen::fn_sub_57E070_0057e070);
    a0 = s4;
    lw(a1, sp, 0xA8);
    link(ctx, 0x57CC30u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xD4);
    call(ctx, gen::fn_sub_57E070_0057e070);
    a0 = s4;
    lw(a1, sp, 0xD8);
    s0 = v0;
    jal(ctx, 0x57CC40u, gen::fn_sub_57E070_0057e070);
    lw(t2, sp, 0xBC);
    sw(v0, sp, 0xDC);
    if (t2 != 0) {
        // 0x0057cc54
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s7 == 0) {
        L_0057cca0:
            charge(ctx, 2);
            a0 = addiu(a0, 31808);
        L_0057ccd4:
            charge(ctx, 6);
            jal(ctx, 0x57CCD4u, gen::fn_sub_585590_00585590);
            a0 = s4;
            jal(ctx, 0x57CCDCu, gen::fn_sub_57E210_0057e210);
            v0 = 0;
        } else {
            // 0x0057cc5c
            charge(ctx, 2);
            a0 = addiu(a0, 31808);
            if (fp != 0) {
                goto L_0057ccd4;
            }
            // 0x0057cc64
            charge(ctx, 2);
            if (s3 != 0) {
                a0 = 0x7C0000;
                goto L_0057cca0;
            }
            // 0x0057cc6c
            charge(ctx, 3);
            lw(v0, sp, 0xC0);
            lw(v1, sp, 0xD0);
            if (v0 == 0) {
                goto L_0057cc9c;
            }
            // 0x0057cc78
            charge(ctx, 2);
            a0 = 0x7C0000;
            if (v1 == 0) {
                goto L_0057cca0;
            }
            // 0x0057cc80
            charge(ctx, 3);
            lw(a0, sp, 0xD4);
            lw(a1, sp, 0xDC);
            if (a0 == 0) {
                goto L_0057cc9c;
            }
            // 0x0057cc8c
            charge(ctx, 2);
            if (a1 == 0) {
                a0 = 0x7C0000;
                goto L_0057cca0;
            }
            // 0x0057cc94
            charge(ctx, 2);
            if (s0 == 0) {
                goto L_0057cc9c;
            }
            // 0x0057cca8
            charge(ctx, 5);
            a0 = s6;
            jal(ctx, 0x57CCA8u, gen::fn_sub_57D1D0_0057d1d0);
            v1 = 1;
            if (v0 != v1) {
                v0 = si(-64);
            } else {
                // 0x0057ccbc
                charge(ctx, 2);
                a0 = 0x7C0000;
                if (s2 != 0) {
                    // 0x0057ccc4
                    charge(ctx, 2);
                    v0 = si(-64);
                    if (s1 != 0) {
                        goto L_0057ccf0;
                    }
                    // 0x0057cccc
                    charge(ctx, 1);
                    a0 = 0x7C0000;
                    goto L_0057ccd0;
                }
            L_0057ccd0:
                charge(ctx, 1);
                a0 = addiu(a0, 31840);
                goto L_0057ccd4;
            }
        L_0057ccf0:
            charge(ctx, 32);
            v1 = addiu(s7, 63);
            v1 = v1 & v0;
            a0 = s5;
            a1 = addiu(sp, 0xAC);
            a2 = addiu(sp, 0xB0);
            a3 = addiu(sp, 0xB4);
            t0 = addiu(sp, 0xB8);
            s0 = 0x9A0000;
            s3 = 0x7B0000;
            link(ctx, 0x57CD14u);  // $ra first: the delay slot below depends on it
            sw(v1, s0, -5280);  // 0x99EB60
            call(ctx, gen::fn_sub_57C398_0057c398);
            lw(a3, sp, 0xAC);
            s7 = 0x7B0000;
            lw(a2, sp, 0xB0);
            v0 = addiu(s3, 12024);  // &0x7B2EF8
            lw(a1, sp, 0xB4);
            a0 = addiu(s7, 12064);  // &0x7B2F20
            lw(v1, sp, 0xB8);
            t0 = 2;
            sw(s1, a0, 24);  // 0x7B2F38
            sw(a1, v0, 0);  // 0x7B2EF8
            sw(zero, v0, 32);  // 0x7B2F18
            sw(v1, v0, 4);  // 0x7B2EFC
            sw(s2, a0, 8);  // 0x7B2F28
            sw(a3, v0, 20);  // 0x7B2F0C
            sw(a2, v0, 24);  // 0x7B2F10
            sw(a3, v0, 8);  // 0x7B2F00
            sw(a2, v0, 12);  // 0x7B2F04
            sw(zero, v0, 16);  // 0x7B2F08
            lw(a2, sp, 0xC4);
            sw(a2, v0, 28);  // 0x7B2F14
            if (s6 == t0) {
                // 0x0057ce70
                charge(ctx, 5);
                v1 = 0x7B0000;
                v1 = addiu(v1, 11880);  // &0x7B2E68
                v0 = v1 & 0x7;
                a1 = sp;
                if (v0 == 0) {
                    // 0x0057cee8
                    charge(ctx, 1);
                    v0 = addiu(v1, 64);
                    for (;;) {
                        // 0x0057ceec
                        charge(ctx, 13);
                        ld(a3, v1, 0);
                        ld(t0, v1, 8);
                        ld(t1, v1, 16);
                        ld(t2, v1, 24);
                        sd(a3, a1, 0);
                        sd(t0, a1, 8);
                        sd(t1, a1, 16);
                        sd(t2, a1, 24);
                        v1 = addiu(v1, 32);
                        a1 = addiu(a1, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0057cf20
                    charge(ctx, 1);
                    lw(v0, s0, -5280);
                } else {
                    // 0x0057ce84
                    charge(ctx, 1);
                    v0 = addiu(v1, 64);
                    for (;;) {
                        // 0x0057ce88
                        charge(ctx, 21);
                        ldl(t1, v1, 7);
                        ldr(t1, v1, 0);
                        ldl(t2, v1, 15);
                        ldr(t2, v1, 8);
                        ldl(a0, v1, 23);
                        ldr(a0, v1, 16);
                        ldl(a2, v1, 31);
                        ldr(a2, v1, 24);
                        sdl(t1, a1, 7);
                        sdr(t1, a1, 0);
                        sdl(t2, a1, 15);
                        sdr(t2, a1, 8);
                        sdl(a0, a1, 23);
                        sdr(a0, a1, 16);
                        sdl(a2, a1, 31);
                        sdr(a2, a1, 24);
                        v1 = addiu(v1, 32);
                        a1 = addiu(a1, 32);
                        if (v1 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0057cedc
                    charge(ctx, 2);
                    lw(v0, s0, -5280);
                }
                // 0x0057cf24
                charge(ctx, 10);
                t2 = 0x9A0000;
                lw(a2, v1, 0);
                a0 = 2048;
                sw(a2, a1, 0);
                a1 = 0x7B0000;
                sw(v0, s4, 452);
                lw(v1, t2, -5276);  // 0x99EB64
                sw(a0, s4, 460);
                v1 = addiu(v1, -2048);
            L_0057d028:
                charge(ctx, 2);
                sw(v1, s4, 456);
                v1 = 0x9A0000;
            } else {
                // 0x0057cd70
                charge(ctx, 3);
                v0 = slti(s6, 3);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 3;
                if (cc) {
                    // 0x0057cd90
                    charge(ctx, 2);
                    a1 = 0x7B0000;
                    if (s6 == v0) {
                        // 0x0057cf50
                        charge(ctx, 5);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 11952);  // "({|"
                        v0 = v1 & 0x7;
                        a0 = sp;
                        if (v0 == 0) {
                            // 0x0057cfc8
                            charge(ctx, 1);
                            v0 = addiu(v1, 64);
                            for (;;) {
                                // 0x0057cfcc
                                charge(ctx, 13);
                                ld(t1, v1, 0);
                                ld(t2, v1, 8);
                                ld(a1, v1, 16);
                                ld(a2, v1, 24);
                                sd(t1, a0, 0);
                                sd(t2, a0, 8);
                                sd(a1, a0, 16);
                                sd(a2, a0, 24);
                                v1 = addiu(v1, 32);
                                a0 = addiu(a0, 32);
                                if (v1 == v0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0057d000
                            charge(ctx, 1);
                            lw(v0, s0, -5280);
                        } else {
                            // 0x0057cf64
                            charge(ctx, 1);
                            v0 = addiu(v1, 64);
                            for (;;) {
                                // 0x0057cf68
                                charge(ctx, 21);
                                ldl(a1, v1, 7);
                                ldr(a1, v1, 0);
                                ldl(a2, v1, 15);
                                ldr(a2, v1, 8);
                                ldl(a3, v1, 23);
                                ldr(a3, v1, 16);
                                ldl(t0, v1, 31);
                                ldr(t0, v1, 24);
                                sdl(a1, a0, 7);
                                sdr(a1, a0, 0);
                                sdl(a2, a0, 15);
                                sdr(a2, a0, 8);
                                sdl(a3, a0, 23);
                                sdr(a3, a0, 16);
                                sdl(t0, a0, 31);
                                sdr(t0, a0, 24);
                                v1 = addiu(v1, 32);
                                a0 = addiu(a0, 32);
                                if (v1 == v0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0057cfbc
                            charge(ctx, 2);
                            lw(v0, s0, -5280);
                        }
                        // 0x0057d004
                        charge(ctx, 6);
                        a1 = 0x7B0000;
                        lw(a3, v1, 0);
                        sw(a3, a0, 0);
                        sw(v0, s4, 452);
                        v0 = 0x9A0000;
                        lw(v1, v0, -5276);  // 0x99EB64
                    L_0057d01c:
                        charge(ctx, 3);
                        lw(v0, a1, 12092);
                        v1 = subu(v1, v0);
                        sw(v0, s4, 460);
                        goto L_0057d028;
                    }
                    // 0x0057cd98
                    charge(ctx, 2);
                    v1 = 0x9A0000;
                } else {
                    // 0x0057cd7c
                    charge(ctx, 3);
                    v0 = 1;
                    a1 = 0x7B0000;
                    if (s6 == v0) {
                        // 0x0057cda0
                        charge(ctx, 5);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 11808);  // &0x7B2E20
                        v0 = v1 & 0x7;
                        a0 = sp;
                        if (v0 == 0) {
                            // 0x0057ce18
                            charge(ctx, 1);
                            v0 = addiu(v1, 64);
                            for (;;) {
                                // 0x0057ce1c
                                charge(ctx, 13);
                                ld(a1, v1, 0);
                                ld(a2, v1, 8);
                                ld(a3, v1, 16);
                                ld(t0, v1, 24);
                                sd(a1, a0, 0);
                                sd(a2, a0, 8);
                                sd(a3, a0, 16);
                                sd(t0, a0, 24);
                                v1 = addiu(v1, 32);
                                a0 = addiu(a0, 32);
                                if (v1 == v0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0057ce50
                            charge(ctx, 1);
                            lw(v0, s0, -5280);
                        } else {
                            // 0x0057cdb4
                            charge(ctx, 1);
                            v0 = addiu(v1, 64);
                            for (;;) {
                                // 0x0057cdb8
                                charge(ctx, 21);
                                ldl(a3, v1, 7);
                                ldr(a3, v1, 0);
                                ldl(t0, v1, 15);
                                ldr(t0, v1, 8);
                                ldl(t1, v1, 23);
                                ldr(t1, v1, 16);
                                ldl(t2, v1, 31);
                                ldr(t2, v1, 24);
                                sdl(a3, a0, 7);
                                sdr(a3, a0, 0);
                                sdl(t0, a0, 15);
                                sdr(t0, a0, 8);
                                sdl(t1, a0, 23);
                                sdr(t1, a0, 16);
                                sdl(t2, a0, 31);
                                sdr(t2, a0, 24);
                                v1 = addiu(v1, 32);
                                a0 = addiu(a0, 32);
                                if (v1 == v0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0057ce0c
                            charge(ctx, 2);
                            lw(v0, s0, -5280);
                        }
                        // 0x0057ce54
                        charge(ctx, 7);
                        a1 = 0x7B0000;
                        lw(t1, v1, 0);
                        t0 = 0x9A0000;
                        sw(t1, a0, 0);
                        sw(v0, s4, 452);
                        lw(v1, t0, -5276);  // 0x99EB64
                        goto L_0057d01c;
                    }
                    // 0x0057cd88
                    charge(ctx, 2);
                    v1 = 0x9A0000;
                }
            }
            // 0x0057d030
            charge(ctx, 5);
            s0 = addiu(v1, -5272);
            lw(v1, a1, 12092);
            lw(a0, s0, 0);
            sw(v1, sp, 0x28);
            if (a0 != 0) {
                // 0x0057d044
                charge(ctx, 3);
                div(a0, v1);
                if (v1 == 0) {
                    brk(ctx, 0x57D04Cu, 0x7u);
                }
                // 0x0057d050
                charge(ctx, 3);
                mfhi(v0);
                v0 = subu(a0, v0);
                sw(v0, s0, 0);
            }
            // 0x0057d05c
            charge(ctx, 32);
            link(ctx, 0x57D05Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s5, 36);
            call(ctx, gen::fn_sub_57C4E8_0057c4e8);
            lw(a3, s0, 0);
            a2 = addiu(sp, 0x50);
            t2 = addiu(sp, 0x60);
            v1 = 0x9A0000;
            a1 = 0x9A0000;
            lw(t0, v1, -5268);  // 0x99EB6C
            a0 = addiu(s3, 12024);
            lw(v1, a1, -5264);  // 0x99EB70
            a1 = a2;
            a2 = t2;
            lw(t2, sp, 0xBC);
            lw(t1, sp, 0xA0);
            sw(t2, sp, 0x4);
            sw(a3, sp, 0x8);
            sw(t0, sp, 0xC);
            sw(v1, sp, 0x10);
            lw(a3, sp, 0xC8);
            lw(v1, sp, 0xC4);
            lw(t0, sp, 0xCC);
            lw(t2, sp, 0xD0);
            sw(v0, sp, 0x38);
            sw(v1, sp, 0x2C);
            sw(a3, sp, 0x30);
            sw(t0, sp, 0x34);
            sw(t2, sp, 0x3C);
            link(ctx, 0x57D0C8u);  // $ra first: the delay slot below depends on it
            sw(t1, sp, 0x40);
            call(ctx, gen::fn_sub_58E310_0058e310);
            v0 = 1;
            if (s6 == v0) {
                // 0x0057d0dc
                charge(ctx, 2);
                a0 = addiu(s7, 12064);
                jal(ctx, 0x57D0DCu, gen::fn_sub_586800_00586800);
            }
            // 0x0057d0e4
            charge(ctx, 8);
            a0 = 1;
            jal(ctx, 0x57D0E4u, gen::fn_sub_594B68_00594b68);
            a1 = 0;
            a0 = sp;
            jal(ctx, 0x57D0F0u, gen::fn_sub_596C28_00596c28);
            s0 = v0;
            a1 = 0x580000;
            if (s0 == 0) {
                // 0x0057d104
                charge(ctx, 5);
                a0 = si(-305);
                jal(ctx, 0x57D104u, gen::fn_sub_57FC60_0057fc60);
                a0 = 0x7C0000;
                a0 = addiu(a0, 31872);  // "E20010703C mwPlyCreateSofdec: create error"
                goto L_0057d160;
            }
            // 0x0057d118
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(a1, -648);
            a2 = s4;
            jal(ctx, 0x57D120u, gen::fn_sub_58BEF0_0058bef0);
            lw(a1, sp, 0xA4);
            if (v0 != 0) {
                // 0x0057d130
                charge(ctx, 5);
                a0 = si(-303);
                jal(ctx, 0x57D130u, gen::fn_sub_57FC60_0057fc60);
                a0 = 0x7C0000;
                a0 = addiu(a0, 31920);  // "E20010703D mwPlyCreateSofdec: set errcb"
                goto L_0057d160;
            }
            // 0x0057d148
            charge(ctx, 4);
            link(ctx, 0x57D148u);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0xD4);
            call(ctx, gen::fn_sub_57BF98_0057bf98);
            sw(v0, s4, 676);
            if (v0 != 0) {
                // 0x0057d170
                charge(ctx, 11);
                lw(v0, sp, 0xDC);
                a0 = s4;
                a2 = 2048;
                a3 = 64;
                sw(v0, s4, 420);
                lw(v1, sp, 0xD8);
                lw(a1, sp, 0xC0);
                link(ctx, 0x57D18Cu);  // $ra first: the delay slot below depends on it
                sw(v1, s4, 424);
                call(ctx, gen::fn_sub_57D208_0057d208);
                sw(zero, s4, 680);
                v0 = s0;
            } else {
                // 0x0057d158
                charge(ctx, 2);
                a0 = 0x7C0000;
                a0 = addiu(a0, 31960);  // "E410142 mwPlyCreateSofdec: can't skghn."
            L_0057d160:
                charge(ctx, 4);
                jal(ctx, 0x57D160u, gen::fn_sub_585590_00585590);
                v0 = 0;
            }
        }
        // 0x0057d19c (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0xE0);
        ld(s1, sp, 0xE8);
        ld(s2, sp, 0xF0);
        ld(s3, sp, 0xF8);
        ld(s4, sp, 0x100);
        ld(s5, sp, 0x108);
        ld(s6, sp, 0x110);
        ld(s7, sp, 0x118);
        ld(fp, sp, 0x120);
        ld(ra, sp, 0x128);
        sp = addiu(sp, 0x130);
        return;
    }
L_0057cc9c:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_0057cca0;
}

// 0x0057D1D0 sub_57D1D0 -- 56 bytes; leaf frame (no stack)
// [mwsfdIsMono] Returns 0 for the values 2 and 3, 1 otherwise (a four-entry jump table).
void sub_57D1D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057d1d0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a0, 6);
    if (v0 == 0) {
        // 0x0057d200 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x0057d1dc
    charge(ctx, 6);
    v0 = sll(a0, 2);
    v1 = 0x7C0000;
    v1 = addu(v1, v0);
    lw(v1, v1, 32000);
    switch (v1.u()) {
    case 0x57D1F8u:  // table[2, 3]
        // 0x0057d1f8
        charge(ctx, 2);
        v0 = 0;
        return;
    case 0x57D200u:  // table[0, 1, 4, 5]
        // 0x0057d200 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    default:  // not one of the table's targets: the dispatch table, as the recompiled body
        tail(ctx, v1.u());
        return;
    }
}

// 0x0057D208 sub_57D208 -- 24 bytes; leaf frame (no stack)
// [mwsfdSetUsrDatBufInternal] Sets a player's user-data buffer to the internal one: +352 / +356 / +360 = (a, b, c),
// +376 = h + 352.
void sub_57D208(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0057d208
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = addiu(a0, 352);
    sw(v0, a0, 376);
    sw(a1, v0, 0);
    sw(a2, v0, 4);
    sw(a3, v0, 8);
}

// 0x0057D220 sub_57D220 -- 232 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [mwsfdSetUsrDatBuf] Hands a player's user-data buffer (the record +376 points at: {buffer, size, count}) to SFD:
// "E02120501: Internal Error" without one, "E02120502: ...usrdatbuf is short." when size < count * (cprm +24 + 4);
// otherwise, when user data is enabled (sub_57FA50 == 1), sub_58E800(SFD handle, buffer, unit, count).
void sub_57D220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057d220
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(a1, s0, 376);
    if (a1 == 0) {
        // 0x0057d248
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 32024);  // "E02120501: Internal Error: mwsfcre_AttachPicUsrBuf()."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    lw(v1, s0, 24);
    // 0x0057d270
    charge(ctx, 7);
    lw(s3, a1, 8);
    s2 = addiu(v1, 4);
    lw(v0, a1, 4);
    mult(v1, s2, s3);
    v0 = slt(v0, v1);
    lw(s1, a1, 0);
    if (v0 != 0) {
        // 0x0057d28c
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 32080);  // "E02120502: mwsfcre_AttachPicUsrBuf(): usrdatbuf is short."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x0057d2b0
    charge(ctx, 5);
    jal(ctx, 0x57D2B0u, gen::fn_sub_57FA50_0057fa50);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x0057d2f0
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x0057d2c4
    charge(ctx, 11);
    lw(a0, s0, 60);
    a1 = s1;
    a2 = s2;
    ld(s2, sp, 0x10);
    a3 = s3;
    ld(s3, sp, 0x18);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_58E800_0058e800(ctx);  // tail call
}

// 0x0057D308 sub_57D308 -- 120 bytes; frame 0x10: ra sp+0x0
// [mwsfdSetUserDataBuffer] Sets the user-data buffer (h, buffer, size, count): a buffer too small prints "E02120503
// ...bufsize is short."; buffer == 0 switches back to the internal record (+352); then sub_57D220. No caller.
void sub_57D308(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057d308
    enter(ctx, 6);  // entry check point + this block's cycles
    t0 = a0;
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = addiu(t0, 364);
    v0 = addiu(t0, 352);
    if (a1 == 0) {
        // 0x0057d320
        charge(ctx, 5);
        sw(zero, v1, 8);
        sw(v0, t0, 376);
        sw(zero, v1, 0);
        sw(zero, v1, 4);
        goto L_0057d374;
    }
    // 0x0057d338
    charge(ctx, 6);
    lw(v0, t0, 24);
    v0 = addiu(v0, 4);
    mult(v0, v0, a3);
    v0 = slt(a2, v0);
    if (v0 != 0) {
        // 0x0057d350
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 32144);  // "E02120503: mwPlyAttachPicUsrBuf(): bufsize is short."
        sp = addiu(sp, 0x10);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    sw(a1, v1, 0);
    // 0x0057d368
    charge(ctx, 3);
    sw(a2, v1, 4);
    sw(a3, v1, 8);
    sw(v1, t0, 376);
L_0057d374:
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_57D220_0057d220(ctx);  // tail call
}

// 0x0057D380 sub_57D380 -- 68 bytes; frame 0x10: ra sp+0x0
// [mwsfdDestroySfd] Destroys the player's SFD side (sub_5971E8); a failure sets error code -306 (sub_57FC60) and prints
// "E20010703E ...".
void sub_57D380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057d380
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57D388u, gen::fn_sub_5971E8_005971e8);
    a0 = si(-306);
    if (v0 == 0) {
        // 0x0057d3b8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057d398
    charge(ctx, 7);
    jal(ctx, 0x57D398u, gen::fn_sub_57FC60_0057fc60);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 32200);  // "E20010703E MWSFCRE_DestroySfd: "
    sp = addiu(sp, 0x10);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x0057D3C8 sub_57D3C8 -- 332 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s2 sp+0x10, ra sp+0x20
// [mwsfdSetSfdParams] Sets a fresh SFD handle's parameters for a player (h, -, a, b): SFD parameters 8 / 1 / 0 / 23 /
// 15 / 51 / 14 / 28 (sub_599100) and the three time parameters 42 / 44 / 45 = round(1000 * a * b) through the FPU (cvt
// / add 0.5), then stream record 5 (sub_58E530).
void sub_57D3C8(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0057d3c8
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 8;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s3, sp, 0x18);
    s3 = 1;
    sd(s2, sp, 0x10);
    mult(s0, s0, s1);
    sd(ra, sp, 0x20);
    a2 = 0;
    lw(s2, a0, 60);
    a0 = s2;
    jal(ctx, 0x57D3FCu, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 1;
    a2 = 1;
    jal(ctx, 0x57D40Cu, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x57D41Cu, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 23;
    a2 = 4;
    jal(ctx, 0x57D42Cu, gen::fn_sub_599100_00599100);
    a0 = s2;
    v0 = sll(s0, 5);
    at = 0x3F000000;
    mtc1(at, f1);
    v0 = subu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    v0 = sll(v0, 3);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f1, f0);
    mfc1(v0, f1);
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    c_lt_s(f0, f1);
    a1 = 45;
    if (!cond(ctx)) {
        // 0x0057d47c
        charge(ctx, 1);
        s3 = 0;
    }
    // 0x0057d480
    charge(ctx, 37);
    s3 = subu(v0, s3);
    a2 = s3;
    jal(ctx, 0x57D484u, gen::fn_sub_599100_00599100);
    a0 = s2;
    a2 = s3;
    a1 = 44;
    jal(ctx, 0x57D494u, gen::fn_sub_599100_00599100);
    a0 = s2;
    a2 = s3;
    a1 = 42;
    jal(ctx, 0x57D4A4u, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 15;
    a2 = 2;
    jal(ctx, 0x57D4B4u, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 51;
    a2 = 0;
    jal(ctx, 0x57D4C4u, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 14;
    a2 = 0;
    jal(ctx, 0x57D4D4u, gen::fn_sub_599100_00599100);
    a0 = s2;
    a1 = 28;
    a2 = 0;
    jal(ctx, 0x57D4E4u, gen::fn_sub_599100_00599100);
    a0 = s2;
    ld(s0, sp, 0x0);
    a1 = 5;
    ld(s1, sp, 0x8);
    a2 = 0;
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_58E530_0058e530(ctx);  // tail call
}

// 0x0057D5B0 sub_57D5B0 -- 36 bytes; frame 0x10: ra sp+0x0
// [mwsfdSetupAudio] sub_562388(h +452, h +456, h +460) in the CRI band (the player's audio buffer setup).
void sub_57D5B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057d5b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    lw(a2, v0, 460);
    lw(a0, v0, 452);
    lw(a1, v0, 456);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_562388_00562388(ctx);  // tail call
}

// 0x0057D5D8 sub_57D5D8 -- 900 bytes; frame 0x60: s1 sp+0x28, s0 sp+0x20, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, ra sp+0x50
// [mwPlyCreate] mwPlyCreate (its own error texts name it) (cprm): validates the creation parameter (sub_57DA08), takes
// a free player record of the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) (+108, eight 684-byte records;
// "E4061801 ... exceeds its maximum number." and error -11 when none), needs the malloc / free functions (sub_57D960;
// "E2053006 ..."), clears the record, lays out its work (sub_57D9B0, sub_57CA78), creates the SFD handle, the stream
// joints and the SFX handle in the CRI band and the SFD band ("E2012 / E2013 / E2020 / E201185 / E201212 mwPlyCreate:
// ..."), sets the SFD parameters (sub_57D3C8) and the header callback (sub_57F328 / sub_57F390). Returns the player or
// 0 (after sub_57DB58 on a failure).
void sub_57D5D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057d5d8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s1, sp, 0x28);
    s1 = a0;
    sd(s0, sp, 0x20);
    sd(s2, sp, 0x30);
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(ra, sp, 0x50);
    if (s1 == 0) {
        // 0x0057d600
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 32344);  // "E1122612 mwPlyCreateSofdec : cprm is NULL."
        goto L_0057d6b8;
    }
    // 0x0057d610
    charge(ctx, 6);
    jal(ctx, 0x57D610u, gen::fn_sub_57DA08_0057da08);
    v1 = 1;
    s2 = v0;
    v0 = 0;
    if (s2 == v1) {
        // 0x0057d628
        charge(ctx, 8);
        jal(ctx, 0x57D628u, gen::fn___gthread_get_ee_key_use_0057f740);
        a0 = 0;
        s0 = addiu(v0, 108);
        s3 = addiu(v0, 4);
        lw(v0, s0, 0);
        cc = v0 != s2;  // the condition, before the delay slot changes it
        v0 = 8;
        if (!cc) {
            // 0x0057d648
            charge(ctx, 4);
            a1 = 1;
            v1 = s0;
            a0 = addiu(a0, 1);
            for (;;) {
                // 0x0057d658
                charge(ctx, 3);
                v0 = slti(a0, 8);
                v1 = addiu(v1, 684);
                if (v0 != 0) {
                    // 0x0057d664
                    charge(ctx, 6);
                    s0 = v1;
                    lw(v0, s0, 0);
                    if (v0 == a1) {
                        a0 = addiu(a0, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            // 0x0057d67c
            charge(ctx, 1);
            v0 = 8;
        }
        // 0x0057d680
        charge(ctx, 2);
        if (a0 == v0) {
            // 0x0057d688
            charge(ctx, 5);
            a0 = si(-11);
            jal(ctx, 0x57D688u, gen::fn_sub_57FC60_0057fc60);
            a0 = 0x7C0000;
            a0 = addiu(a0, 32392);  // "E4061801 mwPlyCreateSofdec: Number of MWPLY handles exceeds its maximum number."
            goto L_0057d6b8;
        }
        a0 = s1;
        // 0x0057d6a0
        charge(ctx, 4);
        s5 = si(-1);
        jal(ctx, 0x57D6A0u, gen::fn_sub_57D960_0057d960);
        a2 = 684;
        if (v0 != s5) {
            // 0x0057d6c8
            charge(ctx, 36);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x57D6CCu, gen::fn_memset_00521408);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x57D6D8u, gen::fn_sub_57D9B0_0057d9b0);
            ldl(v0, s1, 7);
            ldr(v0, s1, 0);
            ldl(v1, s1, 15);
            ldr(v1, s1, 8);
            ldl(a0, s1, 23);
            ldr(a0, s1, 16);
            ldl(a1, s1, 31);
            ldr(a1, s1, 24);
            sdl(v0, s0, 15);
            sdr(v0, s0, 8);
            sdl(v1, s0, 23);
            sdr(v1, s0, 16);
            sdl(a0, s0, 31);
            sdr(a0, s0, 24);
            sdl(a1, s0, 39);
            sdr(a1, s0, 32);
            ldl(v0, s1, 39);
            ldr(v0, s1, 32);
            ldl(v1, s1, 47);
            ldr(v1, s1, 40);
            sdl(v0, s0, 47);
            sdr(v0, s0, 40);
            sdl(v1, s0, 55);
            sdr(v1, s0, 48);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x57D744u, gen::fn_sub_57CA78_0057ca78);
            s2 = v0;
            sw(s2, s0, 60);
            if (s2 == 0) {
                // 0x0057d758
                charge(ctx, 3);
                a0 = 0x7C0000;
                a0 = addiu(a0, 32536);  // "E2012 mwPlyCreate:can't create SFD"
                goto L_0057d900;
            }
            // 0x0057d768
            charge(ctx, 21);
            a0 = s0;
            jal(ctx, 0x57D768u, gen::fn_sub_580E10_00580e10);
            a0 = s0;
            jal(ctx, 0x57D770u, gen::fn_sub_57D220_0057d220);
            a0 = s1;
            a1 = sp;
            a2 = addiu(sp, 0x4);
            a3 = addiu(sp, 0x8);
            t0 = addiu(sp, 0xC);
            t1 = addiu(sp, 0x10);
            t2 = addiu(sp, 0x14);
            jal(ctx, 0x57D790u, gen::fn_sub_57C2B0_0057c2b0);
            a0 = s0;
            lw(a2, s3, 4);
            a1 = s1;
            link(ctx, 0x57D7A4u);  // $ra first: the delay slot below depends on it
            lw(a3, s3, 8);
            call(ctx, gen::fn_sub_57D3C8_0057d3c8);
            a0 = s0;
            jal(ctx, 0x57D7ACu, gen::fn_sub_57D5B0_0057d5b0);
            sw(v0, s0, 448);
            if (v0 == 0) {
                // 0x0057d7bc
                charge(ctx, 3);
                a0 = 0x7C0000;
                a0 = addiu(a0, 32576);  // "E2013 mwPlyCreate:can't create SJ"
                goto L_0057d900;
            }
            // 0x0057d7c8
            charge(ctx, 5);
            a0 = 0;
            a1 = 0;
            jal(ctx, 0x57D7CCu, gen::fn_sub_561970_00561970);
            sw(v0, s0, 480);
            if (v0 == 0) {
                // 0x0057d7dc
                charge(ctx, 3);
                a0 = 0x7C0000;
                a0 = addiu(a0, 32616);  // "E2020 mwPlyCreate:can't create SJ"
                goto L_0057d900;
            }
            // 0x0057d7e8
            charge(ctx, 17);
            lw(v0, sp, 0x0);
            s4 = 1;
            sw(s4, s0, 56);
            s3 = addiu(s0, 68);
            sw(v0, s0, 88);
            a0 = s2;
            sw(zero, s0, 104);
            a1 = 3;
            sw(zero, s0, 4);
            a2 = s3;
            lw(v0, s1, 32);
            sw(v0, s0, 76);
            lw(v1, s1, 32);
            link(ctx, 0x57D81Cu);  // $ra first: the delay slot below depends on it
            sw(v1, s0, 80);
            call(ctx, gen::fn_sub_5996B0_005996b0);
            if (v0 != 0) {
                sw(zero, s3, 0);
            }
            // 0x0057d82c
            charge(ctx, 18);
            sw(s4, s0, 108);
            a1 = 0;
            sb(zero, s0, 112);
            a0 = s0;
            sb(zero, s0, 113);
            sb(zero, s0, 114);
            sb(zero, s0, 115);
            link(ctx, 0x57D848u);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 92);
            call(ctx, gen::fn_sub_586130_00586130);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x57D854u, gen::fn_sub_586140_00586140);
            sw(s4, s0, 84);
            sw(zero, s0, 132);
            link(ctx, 0x57D864u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 448);
            call(ctx, gen::fn_sub_5864A8_005864a8);
            sw(v0, s0, 64);
            if (v0 == 0) {
            L_0057d908:
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x57D908u, gen::fn_sub_57DB58_0057db58);
                v0 = 0;
            } else {
                // 0x0057d874
                charge(ctx, 13);
                a0 = s0;
                jal(ctx, 0x57D874u, gen::fn_sub_580900_00580900);
                link(ctx, 0x57D87Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 448);
                call(ctx, gen::fn_sub_55D2A0_0055d2a0);
                sw(zero, s0, 116);
                sw(v0, s0, 72);
                a0 = v0;
                link(ctx, 0x57D890u);  // $ra first: the delay slot below depends on it
                lw(a1, s0, 64);
                call(ctx, gen::fn_sub_55D3F8_0055d3f8);
                a0 = s0;
                jal(ctx, 0x57D898u, gen::fn_sub_57DA90_0057da90);
                if (v0 == s5) {
                    goto L_0057d908;
                }
                // 0x0057d8a8
                charge(ctx, 7);
                lw(a3, s1, 12);
                lw(a0, s0, 172);
                lw(a1, s0, 176);
                link(ctx, 0x57D8B4u);  // $ra first: the delay slot below depends on it
                lw(a2, s1, 8);
                call(ctx, gen::fn_sub_5827F8_005827f8);
                if (v0 == 0) {
                    // 0x0057d8c4
                    charge(ctx, 3);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, 32656);  // "E201185: can't create SfxHn"
                    goto L_0057d900;
                }
                sw(v0, s0, 168);
                // 0x0057d8d0
                charge(ctx, 10);
                a0 = s0;
                link(ctx, 0x57D8D4u);  // $ra first: the delay slot below depends on it
                lw(a1, s0, 40);
                call(ctx, gen::fn_sub_583028_00583028);
                a0 = s0;
                jal(ctx, 0x57D8DCu, gen::fn_sub_583410_00583410);
                a0 = s0;
                link(ctx, 0x57D8E8u);  // $ra first: the delay slot below depends on it
                sw(v0, s0, 380);
                call(ctx, gen::fn_sub_5834A0_005834a0);
                if (v0 != 0) {
                    // 0x0057d8f8
                    charge(ctx, 2);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, 32688);  // "E201212 mwPlyCreate: can't set AddInfSJ"
                L_0057d900:
                    charge(ctx, 2);
                    jal(ctx, 0x57D900u, gen::fn_sub_585590_00585590);
                    goto L_0057d908;
                }
                // 0x0057d918
                charge(ctx, 8);
                a0 = s0;
                jal(ctx, 0x57D918u, gen::fn_sub_583500_00583500);
                a0 = s0;
                jal(ctx, 0x57D920u, gen::fn_sub_57F328_0057f328);
                a0 = s0;
                jal(ctx, 0x57D928u, gen::fn_sub_57F390_0057f390);
                sw(s4, s0, 0);
                v0 = s0;
            }
        } else {
            // 0x0057d6b0
            charge(ctx, 2);
            a0 = 0x7C0000;
            a0 = addiu(a0, 32472);  // "E2053006 mwPlyCreateSofdec: Didn't set malloc/free func."
        L_0057d6b8:
            charge(ctx, 4);
            jal(ctx, 0x57D6B8u, gen::fn_sub_585590_00585590);
            v0 = 0;
        }
    }
    // 0x0057d938 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x0057D960 sub_57D960 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdCheckAllocator] Allocation check of a creation parameter: 0 when it brings its own work (+24 != 0); otherwise 0
// only when the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) has both a malloc (+40) and a free (+44)
// function, else -1.
void sub_57D960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057d960
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57D96Cu, gen::fn___gthread_get_ee_key_use_0057f740);
    a1 = v0;
    lw(v0, s0, 24);
    a2 = si(-1);
    a0 = 0;
    if (v0 == 0) {
        // 0x0057d988
        charge(ctx, 5);
        lw(v1, a1, 40);
        a0 = a2;
        lw(v0, a1, 44);
        if (v1 != 0) a0 = 0;
        if (v0 == 0) a0 = a2;
    }
    // 0x0057d99c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = a0;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057D9B0 sub_57D9B0 -- 84 bytes; leaf frame (no stack)
// [mwsfdInitAllocator] Starts a player's work allocator (h, cprm): the user work {+24 address, +28 size} into +492 /
// +496 / +500 (64-bit: the current pointer) / +508 = 0 allocations, and the 32-entry allocation table (+512..+636)
// cleared.
void sub_57D9B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0057d9b0
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(v1, a1, 24);
    v0 = addiu(a0, 492);
    lw(a2, a1, 28);
    a3 = addiu(a0, 636);
    sw(v1, v0, 0);
    t0 = 31;
    sw(a2, v0, 4);
    lw(v1, a1, 24);
    sw(zero, v0, 12);
    sw(v1, v0, 8);
    sw(zero, a0, 508);
    for (;;) {
        // 0x0057d9e0
        charge(ctx, 7);
        t0 = addiu(t0, -1);
        sw(zero, a3, 0);
        a3 = addiu(a3, -4);
        if (i64(t0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057d9fc
    charge(ctx, 2);
}

// 0x0057DA08 sub_57DA08 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdCheckCprm] Creation-parameter checks: format 2 (MPEG-1, +0) prints "E3012100: M1V Decode is not support yet.",
// a buffer format (+36) above 2 "E3012101: Buffer format is invalid.", a frame count (+16) of 15 or more "E4110901:
// Number of frame pool exceeds 14."; returns 1 when all pass, else 0.
void sub_57DA08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057da08
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 2;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 0);
    a0 = 1;
    if (v0 == v1) {
        // 0x0057da28
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 32728);  // "E3012100: M1V Decode is not support yet."
        jal(ctx, 0x57DA2Cu, gen::fn_sub_585590_00585590);
        a0 = 0;
    }
    // 0x0057da38
    charge(ctx, 4);
    lw(v0, s0, 36);
    v0 = sltiu(v0, 3);
    if (v0 != 0) {
        lw(v0, s0, 16);
    } else {
        // 0x0057da48
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32760);  // "E3012101: Buffer format is invalid."
        jal(ctx, 0x57DA4Cu, gen::fn_sub_585590_00585590);
        a0 = 0;
        lw(v0, s0, 16);
    }
    // 0x0057da5c
    charge(ctx, 3);
    v0 = slti(v0, 15);
    ld(s0, sp, 0x0);
    if (v0 == 0) {
        // 0x0057da68
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32720);  // "E4110901: Number of frame pool exceeds 14."
        jal(ctx, 0x57DA6Cu, gen::fn_sub_585590_00585590);
        a0 = 0;
        ld(s0, sp, 0x0);
    }
    // 0x0057da7c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v0 = a0;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057DA90 sub_57DA90 -- 196 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mwsfdAllocSfxWork] Allocates a player's SFX work (SFD band sub_5827F0 size; "E2053003: not enough work: sfx_wk")
// and, with the additional-information stream, its 128 KiB buffer ("E2053004 ...: ainfsj_buf"); a failure frees all
// allocations (sub_57E210).
void sub_57DA90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057da90
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(a0, s1, 8);
    link(ctx, 0x57DAB0u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 12);
    call(ctx, gen::fn_sub_5827F0_005827f0);
    a0 = s0;
    s2 = v0;
    a1 = s2;
    jal(ctx, 0x57DAC0u, gen::fn_sub_57E070_0057e070);
    a0 = 0x7D0000;
    a0 = addiu(a0, -32672);  // "E2053003: not enough work: sfx_wk"
    if (v0 != 0) {
        // 0x0057dad4
        charge(ctx, 7);
        sw(v0, s0, 172);
        a0 = s1;
        link(ctx, 0x57DADCu);  // $ra first: the delay slot below depends on it
        sw(s2, s0, 176);
        call(ctx, gen::fn_sub_5833E8_005833e8);
        v1 = 1;
        a0 = s0;
        if (v0 == v1) {
            // 0x0057daf0
            charge(ctx, 6);
            a1 = 0x20000;
            jal(ctx, 0x57DAF0u, gen::fn_sub_57E070_0057e070);
            a0 = 0x7D0000;
            v1 = v0;
            a0 = addiu(a0, -32632);  // "E2053004: not enough work: ainfsj_buf"
            if (v1 == 0) {
                goto L_0057db08;
            }
            // 0x0057db20
            charge(ctx, 4);
            v0 = 0x20000;
            sw(v1, s0, 384);
            sw(v0, s0, 388);
            goto L_0057db38;
        }
        // 0x0057db30
        charge(ctx, 2);
        sw(zero, s0, 388);
        sw(zero, s0, 384);
    L_0057db38:
        charge(ctx, 1);
        v0 = 0;
        // 0x0057db3c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0057db08:
    charge(ctx, 6);
    jal(ctx, 0x57DB08u, gen::fn_sub_585590_00585590);
    a0 = s0;
    jal(ctx, 0x57DB10u, gen::fn_sub_57E210_0057e210);
    v0 = si(-1);
    // 0x0057db3c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057DC80 sub_57DC80 -- 12 bytes; leaf frame (no stack)
// [mwsfdSetOption] Sets the word 0x7B2F3C; leaves 0x7B0000 in $v0 (the lui of the store address). No caller.
void sub_57DC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057dc80
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 12092);  // 0x7B2F3C
}

// 0x0057DC90 sub_57DC90 -- 716 bytes; frame 0x40: s5 sp+0x28, s0 sp+0x0, s3 sp+0x18, s4 sp+0x20, s1 sp+0x8, s2 sp+0x10, ra sp+0x30
// [mwPlyGetHdrInf] mwPlyGetHdrInf (its error texts name it) (buf, size, &info): checks the arguments ("E204161 ...:
// NULL pointer", "E204162 ...: bufsize error"), descrambles the header when keyed (the key table at the work record,
// sub_57C210), parses the Sofdec header with an SFD header view (sub_58A3E8) and fills the info record (picture size,
// frame rate, audio kind through sub_57DF60 / sub_57DFB0, the creation-parameter guess). No caller.
void sub_57DC90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057dc90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s5, sp, 0x28);
    s5 = a3;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a0;
    a1 = 0;
    a2 = 44;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x30);
    a0 = s5;
    jal(ctx, 0x57DCC8u, gen::fn_memset_00521408);
    a0 = 0x7D0000;
    if (s4 != 0) {
        // 0x0057dcd8
        charge(ctx, 2);
        if (i64(s3) <= 0) {
            goto L_0057dcec;
        }
        // 0x0057dce0
        charge(ctx, 3);
        v0 = s3 & 0x7FF;
        if (v0 != 0) {
            goto L_0057dcec;
        }
        // 0x0057dd18
        charge(ctx, 2);
        a0 = 0x9A0000;
        if (s0 != 0) {
            // 0x0057dd20
            charge(ctx, 10);
            a1 = 140;
            a0 = addiu(a0, -5176);
            jal(ctx, 0x57DD24u, gen::fn_sub_57BF98_0057bf98);
            a1 = s0;
            s2 = v0;
            a0 = s2;
            jal(ctx, 0x57DD34u, gen::fn_sub_57BFC0_0057bfc0);
            v0 = sra(s3, 11);
            s1 = v0;
            if (i64(v0) > 0) {
                // 0x0057dd48
                charge(ctx, 2);
                s0 = s4;
                a1 = s0;
                for (;;) {
                    // 0x0057dd50
                    charge(ctx, 6);
                    s0 = addiu(s0, 2048);
                    s1 = addiu(s1, -1);
                    a0 = s2;
                    jal(ctx, 0x57DD58u, gen::fn_sub_57C210_0057c210);
                    a1 = s0;
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0057dd68
            charge(ctx, 2);
            a0 = s2;
            jal(ctx, 0x57DD68u, gen::fn_sub_57BFB8_0057bfb8);
        }
        // 0x0057dd70
        charge(ctx, 12);
        a0 = s4;
        ld(s4, sp, 0x20);
        a1 = s3;
        ld(s3, sp, 0x18);
        a2 = s5;
        ld(s5, sp, 0x28);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        // 0x0057dda0
        charge(ctx, 20);
        sp = addiu(sp, -0xA0);
        sd(s1, sp, 0x78);
        s1 = a1;
        sd(s2, sp, 0x80);
        s2 = a0;
        sd(s3, sp, 0x88);
        s3 = a2;
        a0 = sp;
        a1 = 0;
        sd(s0, sp, 0x70);
        sd(ra, sp, 0x90);
        a2 = 44;
        jal(ctx, 0x57DDCCu, gen::fn_memset_00521408);
        a0 = s3;
        a1 = 0;
        a2 = 44;
        jal(ctx, 0x57DDDCu, gen::fn_memset_00521408);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32512);  // "E204161: mwPlyGetHdrInf(): NULL pointer"
        if (s2 != 0) {
            // 0x0057ddf0
            charge(ctx, 2);
            if (s3 == 0) {
                goto L_0057de08;
            }
            // 0x0057ddf8
            charge(ctx, 2);
            s0 = addiu(sp, 0x30);
            if (i64(s1) <= 0) {
                // 0x0057de00
                charge(ctx, 2);
                a0 = 0x7D0000;
                a0 = addiu(a0, -32472);  // "E204162: mwPlyGetHdrInf(): bufsize error"
                goto L_0057de08;
            }
            // 0x0057de18
            charge(ctx, 8);
            a0 = s2;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x57DE20u, gen::fn_sub_58A3E8_0058a3e8);
            lhu(v1, sp, 0x30);
            v0 = 257;
            a0 = s0;
            if (v1 == v0) {
                // 0x0057de98
                charge(ctx, 42);
                jal(ctx, 0x57DE98u, gen::fn_sub_57DF60_0057df60);
                a1 = s1;
                lw(v1, sp, 0x48);
                a0 = s2;
                lw(t2, sp, 0x44);
                a2 = sp;
                lw(a3, sp, 0x50);
                lw(t0, sp, 0x5C);
                lb(t1, sp, 0x58);
                sw(v1, sp, 0xC);
                sw(v0, sp, 0x4);
                sw(t2, sp, 0x8);
                sw(a3, sp, 0x10);
                sw(t0, sp, 0x24);
                link(ctx, 0x57DED4u);  // $ra first: the delay slot below depends on it
                sw(t1, sp, 0x28);
                call(ctx, gen::fn_sub_57F0F0_0057f0f0);
                a0 = sp;
                jal(ctx, 0x57DEDCu, gen::fn_sub_57DFB0_0057dfb0);
                sw(v0, sp, 0x0);
                ldl(v0, sp, 0x7);
                ldr(v0, sp, 0x0);
                ldl(v1, sp, 0xF);
                ldr(v1, sp, 0x8);
                ldl(a0, sp, 0x17);
                ldr(a0, sp, 0x10);
                ldl(a1, sp, 0x1F);
                ldr(a1, sp, 0x18);
                sdl(v0, s3, 7);
                sdr(v0, s3, 0);
                sdl(v1, s3, 15);
                sdr(v1, s3, 8);
                sdl(a0, s3, 23);
                sdr(a0, s3, 16);
                sdl(a1, s3, 31);
                sdr(a1, s3, 24);
                ldl(v0, sp, 0x27);
                ldr(v0, sp, 0x20);
                lw(v1, sp, 0x28);
                sdl(v0, s3, 39);
                sdr(v0, s3, 32);
                sw(v1, s3, 40);
            } else {
                // 0x0057de38
                charge(ctx, 24);
                ldl(v0, sp, 0x7);
                ldr(v0, sp, 0x0);
                ldl(v1, sp, 0xF);
                ldr(v1, sp, 0x8);
                ldl(a0, sp, 0x17);
                ldr(a0, sp, 0x10);
                ldl(a1, sp, 0x1F);
                ldr(a1, sp, 0x18);
                sdl(v0, s3, 7);
                sdr(v0, s3, 0);
                sdl(v1, s3, 15);
                sdr(v1, s3, 8);
                sdl(a0, s3, 23);
                sdr(a0, s3, 16);
                sdl(a1, s3, 31);
                sdr(a1, s3, 24);
                ldl(v0, sp, 0x27);
                ldr(v0, sp, 0x20);
                lw(v1, sp, 0x28);
                sdl(v0, s3, 39);
                sdr(v0, s3, 32);
                sw(v1, s3, 40);
                sw(zero, s3, 0);
            }
            // 0x0057df40
            charge(ctx, 1);
            ld(s0, sp, 0x70);
            // 0x0057df44 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x78);
            ld(s2, sp, 0x80);
            ld(s3, sp, 0x88);
            ld(ra, sp, 0x90);
            sp = addiu(sp, 0xA0);
            return;
        }
    L_0057de08:
        charge(ctx, 4);
        jal(ctx, 0x57DE08u, gen::fn_sub_585590_00585590);
        ld(s0, sp, 0x70);
        // 0x0057df44 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x78);
        ld(s2, sp, 0x80);
        ld(s3, sp, 0x88);
        ld(ra, sp, 0x90);
        sp = addiu(sp, 0xA0);
        return;
    }
L_0057dcec:
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, -32568);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x0057DF60 sub_57DF60 -- 76 bytes; leaf frame (no stack)
// [mwsfdAudioCode] Audio-channel code of a header record (+4 / +8 / +12): (0, x, 0) -> 2, (0, x, y) -> 0, (x, -, 0) ->
// 3, (x, -, y) -> 1, (0, 0, -) -> 0.
void sub_57DF60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057df60
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 4);
    a1 = 0;
    if (v0 != 0) {
        // 0x0057df90
        charge(ctx, 4);
        lw(v1, a0, 12);
        v0 = 1;
        a1 = 3;
        if (v1 != 0) a1 = v0;
    L_0057dfa0:
        charge(ctx, 1);
        v0 = a1;
        // 0x0057dfa4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057df6c
    charge(ctx, 3);
    lw(v0, a0, 8);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = a1;
    if (cc) {
        // 0x0057dfa4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057df78
    charge(ctx, 3);
    lw(v0, a0, 12);
    if (v0 == 0) {
        a1 = 2;
        goto L_0057dfa0;
    }
    // 0x0057df84
    charge(ctx, 2);
    v0 = a1;
}

// 0x0057DFB0 sub_57DFB0 -- 120 bytes; leaf frame (no stack)
// [mwsfdRateOk] Rate check of a header record: kind +4 == 0 or 2 gives 0; kind 1 accepts the values (+36) 0, 6,000,
// 12,000, 24,000 and 48,000 (1) and refuses others (0); any other kind gives 1.
void sub_57DFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057dfb0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a1, a0, 4);
    v0 = 0;
    if (a1 == 0) {
        // 0x0057e020 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057dfbc
    charge(ctx, 3);
    v1 = 2;
    if (a1 == v1) {
        // 0x0057e020 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057dfc8
    charge(ctx, 3);
    v0 = 1;
    if (a1 != v0) {
        // 0x0057e020 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057dfd4
    charge(ctx, 4);
    lw(a0, a0, 36);
    v0 = 12000;
    cc = a0 == v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (cc) {
        // 0x0057e020 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057dfe4
    charge(ctx, 3);
    v0 = slti(a0, 12001);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 24000;
    if (!cc) {
        // 0x0057dff0
        charge(ctx, 2);
        if (a0 == 0) {
            v0 = 1;
            // 0x0057e020 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0057dff8
        charge(ctx, 2);
        v0 = 6000;
        goto L_0057e00c;
    }
    // 0x0057e000
    charge(ctx, 2);
    cc = a0 == v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (cc) {
        // 0x0057e020 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057e008
    charge(ctx, 1);
    v0 = 0xBB80;
L_0057e00c:
    charge(ctx, 2);
    if (a0 == v0) {
        v0 = 1;
        // 0x0057e020 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0057e014
    charge(ctx, 2);
    v0 = 0;
}

// 0x0057E028 sub_57E028 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mwsfdSetAllocator] Sets the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) allocator: +40 = malloc function,
// +44 = free function, +48 = their object. No caller in the ELF (the game provides its work).
void sub_57E028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e028
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x57E044u, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, 48);
    sw(s1, v0, 40);
    sw(s2, v0, 44);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057E070 sub_57E070 -- 160 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [mwsfdAlloc] Work allocation for a player (h, size): at most 32 live allocations ("E2053001 ...: cnt over." beyond);
// from the user work (sub_57E110) when one was given (+492), else through the malloc callback (sub_57E148); the address
// is recorded in the table (+512 + 4 * count) and the count raised (sub_57E270). Returns it or 0.
void sub_57E070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e070
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    lw(v0, s1, 508);
    v0 = slti(v0, 32);
    v1 = a1;
    if (v0 != 0) {
        // 0x0057e0a8
        charge(ctx, 2);
        v0 = 0;
        if (i64(v1) >= 0) {
            // 0x0057e0b0
            charge(ctx, 3);
            lw(v0, s1, 492);
            if (v0 == 0) {
                // 0x0057e0d0
                charge(ctx, 3);
                a0 = v1;
                jal(ctx, 0x57E0D0u, gen::fn_sub_57E148_0057e148);
                s0 = v0;
            } else {
                // 0x0057e0bc
                charge(ctx, 4);
                jal(ctx, 0x57E0BCu, gen::fn_sub_57E110_0057e110);
                s0 = v0;
            }
            // 0x0057e0dc
            charge(ctx, 2);
            a0 = s1;
            if (s0 != 0) {
                // 0x0057e0e4
                charge(ctx, 5);
                lw(v0, s1, 508);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                link(ctx, 0x57E0F0u);  // $ra first: the delay slot below depends on it
                sw(s0, v0, 512);
                call(ctx, gen::fn_sub_57E270_0057e270);
            }
            // 0x0057e0f8
            charge(ctx, 1);
            v0 = s0;
        }
    } else {
        // 0x0057e094
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32424);  // "E2053001 MWSFD_Malloc: cnt over."
        jal(ctx, 0x57E098u, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x0057e0fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057E110 sub_57E110 -- 52 bytes; leaf frame (no stack)
// [mwsfdAllocFromWork] Bump allocation from a player's user work: when used (+504) + size fits the size (+496), returns
// the current pointer (+500) and advances it; else 0.
void sub_57E110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0057e110
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = addiu(a0, libs3::mwsfd::kWorkUse);  // {use, size, cur, used}
    lw(v1, a0, 12);
    lw(v0, a0, 4);
    v1 = addu(v1, a1);
    v0 = sltu(v0, v1);
    a2 = 0;
    if (v0 == 0) {
        // 0x0057e12c
        charge(ctx, 4);
        lw(a2, a0, 8);
        sw(v1, a0, 12);
        v0 = addu(a2, a1);
        sw(v0, a0, 8);
    }
    // 0x0057e13c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a2;
}

// 0x0057E148 sub_57E148 -- 52 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdAllocFromMalloc] Allocation through the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) malloc callback
// (+40) with its object (+48), a tail call through jalr.
void sub_57E148(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e148
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57E154u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(a0, v0, 48);
    lw(v0, v0, 40);
    a1 = s0;
    jalr(ctx, 0x57E164u, v0.u());
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057E180 sub_57E180 -- 92 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdFree] Frees one allocation of a player (h, p): nothing to do for user work (sub_57E1D0), the free callback
// otherwise (sub_57E1D8); the count (+508) drops by one. Two chunks.
void sub_57E180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e180
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, 492);
    v1 = a1;
    if (v0 == 0) {
        // 0x0057e1b0
        charge(ctx, 3);
        a0 = v1;
        jal(ctx, 0x57E1B0u, gen::fn_sub_57E1D8_0057e1d8);
        a0 = s0;
    } else {
        // 0x0057e19c
        charge(ctx, 4);
        jal(ctx, 0x57E19Cu, gen::fn_sub_57E1D0_0057e1d0);
        a0 = s0;
    }
    // 0x0057e1bc
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    // 0x0057e280
    charge(ctx, 4);
    lw(v0, a0, 508);
    v0 = addiu(v0, -1);
    sw(v0, a0, 508);
}

// 0x0057E1D0 sub_57E1D0 -- 8 bytes; leaf frame (no stack)
// An empty function (jr $ra / nop): freeing user-work memory does nothing.
void sub_57E1D0(EEContext& ctx) {
    using namespace hg;
    // 0x0057e1d0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0057E1D8 sub_57E1D8 -- 52 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdFreeToMalloc] Free through the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) free callback (+44) with
// its object (+48), a tail call through jalr.
void sub_57E1D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e1d8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57E1E4u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(a0, v0, 48);
    lw(v1, v0, 44);
    a1 = s0;
    jalr(ctx, 0x57E1F4u, v1.u());
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057E210 sub_57E210 -- 92 bytes; frame 0x20: s1 sp+0x8, ra sp+0x18, s0 sp+0x0, s2 sp+0x10
// [mwsfdFreeAll] Frees every recorded allocation of a player: the 32-entry table from the top (+636 down to +512), each
// non-zero entry freed (sub_57E180) and cleared.
void sub_57E210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e210
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(s1, 636);
    sd(s2, sp, 0x10);
    s2 = 31;
    for (;;) {
        // 0x0057e230
        charge(ctx, 3);
        lw(a1, s0, 0);
        if (a1 == 0) {
            s2 = addiu(s2, -1);
        } else {
            // 0x0057e23c
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x57E23Cu, gen::fn_sub_57E180_0057e180);
            sw(zero, s0, 0);
            s2 = addiu(s2, -1);
        }
        // 0x0057e24c
        charge(ctx, 2);
        s0 = addiu(s0, -4);
        if (i64(s2) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057e254
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057E270 sub_57E270 -- 16 bytes; leaf frame (no stack)
// [mwsfdCountAlloc] Raises a player's allocation count (+508) by one.
void sub_57E270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057e270
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, libs3::mwsfd::kAllocCount);
    v0 = addiu(v0, 1);
    sw(v0, a0, libs3::mwsfd::kAllocCount);
}

// 0x0057E290 sub_57E290 -- 8 bytes; leaf frame (no stack)
// [mwsfdAllocCount] Returns a player's allocation count (+508).
void sub_57E290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057e290
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, libs3::mwsfd::kAllocCount);
}

// 0x0057E298 sub_57E298 -- 156 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mwsfdSetKey] Installs a player's header key (h, key): when key is non-null fills the key table (+676, sub_57BFC0)
// and sets the SFD handle's descramble hook to sub_57E360 with h (SFD handle +14240 / +14244); null removes the hook.
// Two chunks (the store tail at 0x58C698 is shared). No caller.
void sub_57E298(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e298
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x57E2B0u, gen::fn_sub_5811D0_005811d0);
    s1 = v0;
    lw(v0, s2, 676);
    a1 = 0;
    a0 = s1;
    a2 = 0;
    if (s0 != 0) {
        // 0x0057e2e8
        charge(ctx, 13);
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x57E2ECu, gen::fn_sub_57BFC0_0057bfc0);
        a1 = 0x580000;
        a0 = s1;
        ld(s1, sp, 0x8);
        a2 = s2;
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        a1 = addiu(a1, -7328);  // &sub_57E360
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
    } else {
        // 0x0057e2d0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
    }
    // 0x0058c698
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x0058c6a0
        charge(ctx, 2);
        sw(a2, a0, 14244);
        sw(a1, a0, 14240);
    }
    // 0x0058c6a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057E320 sub_57E320 -- 84 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdSetDescrambleHook] Sets a player's SFD descramble hook (h, fn, arg) directly (SFD handle +14240 / +14244). No
// caller.
void sub_57E320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e320
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a2;
    jal(ctx, 0x57E334u, gen::fn_sub_5811D0_005811d0);
    ld(ra, sp, 0x10);
    a1 = s0;
    a2 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x20);
    // 0x0058c698
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x0058c6a0
        charge(ctx, 2);
        sw(a2, a0, 14244);
        sw(a1, a0, 14240);
    }
    // 0x0058c6a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057E360 sub_57E360 -- 24 bytes; frame 0x10: ra sp+0x0
// [mwsfdDescrambleHook] The descramble hook: sub_57C210 with the player's key table (+676) on the block.
void sub_57E360(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e360
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 676);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_57C210_0057c210(ctx);  // tail call
}

// 0x0057E378 sub_57E378 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdSetFrameSync] Sets the frame-sync switch (h, on): the player-handle check sub_581798 (it must return 1); an
// invalid handle prints "E1122629 ...: handle is invalid." through sub_585590; else +84 = on.
void sub_57E378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e378
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x57E38Cu, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -32384);  // "E1122629: mwPlySetFrmSync: handle is invalid."
    if (v0 == v1) {
        // 0x0057e3b8
        charge(ctx, 6);
        sw(s1, s0, libs3::mwsfd::kFrmSync);
        ld(ra, sp, 0x10);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0057e3a4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x0057E3D0 sub_57E3D0 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyGetFrmSync] mwPlyGetFrmSync (its error text names it) (h): the player-handle check sub_581798 (it must return
// 1); an invalid handle prints "E2010801: mwPlyGetFrmSync: handle is invalid." through sub_585590 and gives 0; else
// +84.
void sub_57E3D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e3d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57E3DCu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 == v1) {
        // 0x0057e410
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        // 0x0057e420
        charge(ctx, 2);
        lw(v0, a0, 84);
        return;
    }
    // 0x0057e3f0
    charge(ctx, 8);
    a0 = 0x7D0000;
    a0 = addiu(a0, -32336);  // "E2010801: mwPlyGetFrmSync: handle is invalid."
    jal(ctx, 0x57E3F4u, gen::fn_sub_585590_00585590);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057E428 sub_57E428 -- 264 bytes; frame 0x40: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// [mwPlyGetFrm] mwPlyGetFrm (its error text names it) (h, &frm): the player-handle check sub_581798 (it must return 1);
// an invalid handle prints "E410131: mwPlyGetFrm: handle is invalid." through sub_585590 and clears the record; locks
// the get / release API type 2 (sub_57E698), asks SFD for the next frame (SFD band), fills the frame record
// (sub_57EB38, sub_57E730) and the frame-time bookkeeping (sub_57E6E0). No caller.
void sub_57E428(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e428
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s2, sp, 0x20);
    s2 = a1;
    a2 = 144;
    a0 = s1;
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    a1 = 0;
    jal(ctx, 0x57E454u, gen::fn_memset_00521408);
    v0 = si(-1);
    sw(zero, s1, 0);
    sw(v0, s1, 4);
    a0 = s0;
    link(ctx, 0x57E46Cu);  // $ra first: the delay slot below depends on it
    sw(v0, s2, 0);
    call(ctx, gen::fn_sub_581798_00581798);
    a0 = s0;
    s3 = v0;
    v0 = 1;
    a1 = 2;
    if (s3 != v0) {
        // 0x0057e488
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32288);  // "E410131: mwPlyGetFrm: handle is invalid."
        jal(ctx, 0x57E48Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
        goto L_0057e514;
    }
    // 0x0057e4a0
    charge(ctx, 9);
    jal(ctx, 0x57E4A0u, gen::fn_sub_57E698_0057e698);
    a0 = s0;
    jal(ctx, 0x57E4A8u, gen::fn_sub_5811D0_005811d0);
    a1 = s2;
    v1 = v0;
    a2 = sp;
    a0 = v1;
    if (v1 == 0) {
    L_0057e514:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x0057e4c4
        charge(ctx, 4);
        jal(ctx, 0x57E4C4u, gen::fn_thread_leave_1_00597aa0);
        if (v0 == s3) {
            // 0x0057e4d4
            charge(ctx, 16);
            lw(a1, sp, 0x0);
            a0 = s0;
            link(ctx, 0x57E4DCu);  // $ra first: the delay slot below depends on it
            sw(a1, s0, 120);
            call(ctx, gen::fn_sub_57EB38_0057eb38);
            a0 = s0;
            lw(a1, sp, 0x0);
            a2 = s1;
            jal(ctx, 0x57E4ECu, gen::fn_sub_57E730_0057e730);
            lw(v0, s2, 0);
            lw(v1, s1, 48);
            a0 = s0;
            sw(v0, s1, 4);
            a1 = s1;
            link(ctx, 0x57E508u);  // $ra first: the delay slot below depends on it
            sw(v1, s0, 184);
            call(ctx, gen::fn_sub_57E6E0_0057e6e0);
            v0 = 1;
            goto L_0057e514;
        }
        ld(s0, sp, 0x10);
    }
    // 0x0057e518 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0057E530 sub_57E530 -- 360 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x20, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// [mwsfdGetCurrentFrame] The current-frame getter (h, &frm), the game's frame getter: the player-handle check
// sub_581798 (it must return 1); an invalid handle prints "E1122614 ...: handle is invalid." through sub_585590 and
// clears the 144-byte record; locks API type 1 (sub_57E698), asks SFD for the frame (sub_597C28), drops frames that are
// late when frame sync is off (+84 == 0: sub_57EF08 / sub_597D20, counting +132), records the frame (+120, +124) and
// fills the record (sub_57EB38, sub_57E730, sub_57E6E0).
void sub_57E530(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e530
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x40);
    s2 = a1;
    jal(ctx, 0x57E554u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a1 = 1;
    if (v0 != v1) {
        // 0x0057e568
        charge(ctx, 3);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32240);  // "E1122614: mwPlyGetCurFrm: handle is invalid."
        jal(ctx, 0x57E56Cu, gen::fn_sub_585590_00585590);
        goto L_0057e574;
    }
    // 0x0057e590
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x57E590u, gen::fn_sub_57E698_0057e698);
    a0 = s0;
    jal(ctx, 0x57E598u, gen::fn_sub_5811D0_005811d0);
    s1 = v0;
    a0 = s1;
    if (s1 == 0) {
        backedge(ctx);
    L_0057e574:
        charge(ctx, 6);
        a0 = s2;
        a1 = 0;
        a2 = 144;
        jal(ctx, 0x57E57Cu, gen::fn_memset_00521408);
        sw(zero, s2, 0);
    L_0057e674:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x0057e5ac
        charge(ctx, 5);
        a1 = sp;
        jal(ctx, 0x57E5ACu, gen::fn_sub_597C28_00597c28);
        lw(v1, sp, 0x0);
        if (v1 == 0) {
            sw(zero, s2, 0);
            goto L_0057e674;
        }
        // 0x0057e5c0
        charge(ctx, 3);
        lw(v0, s0, 84);
        s3 = 0;
        if (v0 == 0) {
            // 0x0057e5cc
            charge(ctx, 3);
            lw(s4, s0, 24);
            s5 = 1;
            v0 = slt(s3, s4);
            for (;;) {
                // 0x0057e5d8
                charge(ctx, 2);
                s3 = addiu(s3, 1);
                if (v0 != 0) {
                    // 0x0057e5e0
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x57E5E0u, gen::fn_sub_57EF08_0057ef08);
                    a0 = s1;
                    if (v0 == s5) {
                        // 0x0057e5f0
                        charge(ctx, 10);
                        link(ctx, 0x57E5F0u);  // $ra first: the delay slot below depends on it
                        lw(a1, sp, 0x0);
                        call(ctx, gen::fn_sub_597D20_00597d20);
                        lw(v1, s0, 132);
                        a0 = s1;
                        a1 = sp;
                        v1 = addiu(v1, 1);
                        link(ctx, 0x57E608u);  // $ra first: the delay slot below depends on it
                        sw(v1, s0, 132);
                        call(ctx, gen::fn_sub_597C28_00597c28);
                        v0 = slt(s3, s4);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            // 0x0057e618
            charge(ctx, 1);
            lw(v1, sp, 0x0);
        }
        // 0x0057e61c
        charge(ctx, 2);
        a0 = s0;
        if (v1 == 0) {
            // 0x0057e670
            charge(ctx, 1);
            sw(zero, s2, 0);
            goto L_0057e674;
        }
        // 0x0057e624
        charge(ctx, 19);
        lw(v0, s0, 124);
        sw(v1, s0, 120);
        v0 = addiu(v0, 1);
        lw(a1, sp, 0x0);
        link(ctx, 0x57E634u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 124);
        call(ctx, gen::fn_sub_57EB38_0057eb38);
        a0 = s0;
        lw(a1, sp, 0x0);
        a2 = s2;
        jal(ctx, 0x57E644u, gen::fn_sub_57E730_0057e730);
        lw(v0, s2, 36);
        lw(v1, s2, 48);
        a0 = s0;
        sw(v0, s2, 4);
        a1 = s2;
        link(ctx, 0x57E660u);  // $ra first: the delay slot below depends on it
        sw(v1, s0, 184);
        call(ctx, gen::fn_sub_57E6E0_0057e6e0);
        ld(s0, sp, 0x10);
    }
    // 0x0057e678 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0057E698 sub_57E698 -- 68 bytes; frame 0x10: ra sp+0x0
// [mwsfdCheckFrameApi] The get / release frame API guard (h, type): the first call records the type (+680); a later
// call with another type prints "E4110902: Don't use another type get/rel frame API together."
void sub_57E698(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e698
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, libs3::mwsfd::kFrameApi);
    if (v0 == 0) {
        // 0x0057e6ac
        charge(ctx, 2);
        sw(a1, a0, libs3::mwsfd::kFrameApi);
        // 0x0057e6d0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057e6b8
    charge(ctx, 2);
    a0 = 0x7D0000;
    if (v0 == a1) {
        // 0x0057e6d0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057e6c0
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a0 = addiu(a0, -32192);
    sp = addiu(sp, 0x10);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x0057E6E0 sub_57E6E0 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdNoteFrameTime] Frame-time bookkeeping (h, frm): when the frame's time (+48) is past the last one seen (+400)
// the player's time hook runs (sub_5835A8); +400 = the frame's time either way.
void sub_57E6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e6e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    lw(v1, s1, 48);
    lw(v0, s0, 400);
    v0 = slt(v0, v1);
    if (v0 == 0) {
        sw(v1, s0, 400);
    } else {
        // 0x0057e70c
        charge(ctx, 4);
        jal(ctx, 0x57E70Cu, gen::fn_sub_5835A8_005835a8);
        lw(v1, s1, 48);
        sw(v1, s0, 400);
    }
    // 0x0057e71c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057E730 sub_57E730 -- 480 bytes; frame 0x80: s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, s4 sp+0x50, s5 sp+0x58, s6 sp+0x60, fp sp+0x70, s0 sp+0x30, s7 sp+0x68, ra sp+0x78
// [mwsfdFillFrameInfo] Fills a frame record from SFD's frame (h, sfd frame, out): picture type and structure codes
// (sub_57E9D8, sub_57EA18), the size and pitch words, the frame rate from SFD (sub_59AD80; "E201301: MWSFD: GetFps
// failed."), the frame times converted to the rate (sub_57E9A8), the user data (sub_57E910), the tag values
// (sub_57EB80), the concatenation flag (sub_57EA80) and five 8-byte words copied.
void sub_57E730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0057e730
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s1, sp, 0x38);
    s1 = a2;
    sd(s2, sp, 0x40);
    s2 = a1;
    sd(s3, sp, 0x48);
    sd(s4, sp, 0x50);
    s4 = a0;
    sd(s5, sp, 0x58);
    sd(s6, sp, 0x60);
    sd(fp, sp, 0x70);
    sd(s0, sp, 0x30);
    sd(s7, sp, 0x68);
    sd(ra, sp, 0x78);
    lw(a0, s2, 28);
    lw(s0, s4, 60);
    link(ctx, 0x57E770u);  // $ra first: the delay slot below depends on it
    lw(s7, s2, 32);
    call(ctx, gen::fn_sub_57E9D8_0057e9d8);
    sw(v0, sp, 0x4);
    lw(v0, s2, 0);
    lw(a0, s2, 16);
    sw(v0, sp, 0x8);
    lw(v0, s2, 4);
    sw(v0, sp, 0xC);
    lw(v0, s2, 8);
    sw(v0, sp, 0x10);
    lw(v0, s2, 12);
    link(ctx, 0x57E79Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x14);
    call(ctx, gen::fn_sub_57EA18_0057ea18);
    sw(v0, sp, 0x18);
    a1 = sp;
    a0 = s0;
    lw(v0, s2, 36);
    lw(s3, s2, 24);
    lw(s5, s2, 52);
    lw(s6, s2, 48);
    lw(fp, s2, 44);
    sw(v0, sp, 0x1C);
    lw(v0, s2, 40);
    link(ctx, 0x57E7CCu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x20);
    call(ctx, gen::fn_sub_59AD80_0059ad80);
    lw(a1, sp, 0x0);
    if (v0 != 0) {
        // 0x0057e7dc
        charge(ctx, 4);
        a0 = 0x7D0000;
        a0 = addiu(a0, -32128);  // "E201301: MWSFD: GetFps failed."
        jal(ctx, 0x57E7E0u, gen::fn_sub_585590_00585590);
        lw(a1, sp, 0x0);
    }
    // 0x0057e7ec
    charge(ctx, 73);
    a2 = s3;
    a0 = s5;
    jal(ctx, 0x57E7F0u, gen::fn_sub_57E9A8_0057e9a8);
    a0 = s6;
    lw(a1, sp, 0x0);
    a2 = s3;
    s0 = v0;
    jal(ctx, 0x57E804u, gen::fn_sub_57E9A8_0057e9a8);
    sw(s7, s1, 0);
    a0 = s4;
    a1 = s2;
    lw(v1, sp, 0x0);
    a2 = s1;
    sw(v0, s1, 52);
    lw(v0, sp, 0x4);
    sw(v0, s1, 8);
    lw(v0, sp, 0x8);
    sw(v0, s1, 12);
    lw(v0, sp, 0xC);
    sw(v0, s1, 16);
    lw(v0, sp, 0x10);
    sw(v0, s1, 20);
    lw(v0, sp, 0x14);
    sw(v0, s1, 24);
    lw(v0, sp, 0x18);
    sw(v1, s1, 32);
    sw(s0, s1, 36);
    sw(s5, s1, 40);
    sw(s3, s1, 44);
    sw(fp, s1, 48);
    sw(s6, s1, 56);
    sw(v0, s1, 28);
    lw(v0, sp, 0x1C);
    sw(v0, s1, 60);
    lw(v0, sp, 0x20);
    link(ctx, 0x57E878u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 64);
    call(ctx, gen::fn_sub_57E910_0057e910);
    a0 = s4;
    a1 = s2;
    a2 = s1;
    jal(ctx, 0x57E888u, gen::fn_sub_57EB80_0057eb80);
    a0 = s4;
    lw(a2, s1, 136);
    a1 = s2;
    link(ctx, 0x57E89Cu);  // $ra first: the delay slot below depends on it
    lw(a3, s1, 140);
    call(ctx, gen::fn_sub_57EA80_0057ea80);
    sw(v0, s1, 76);
    ld(s0, sp, 0x30);
    ld(v0, s2, 72);
    ld(s3, sp, 0x48);
    sd(v0, s1, 80);
    ld(s4, sp, 0x50);
    ld(v1, s2, 80);
    ld(s5, sp, 0x58);
    sd(v1, s1, 88);
    ld(s6, sp, 0x60);
    ld(v0, s2, 88);
    ld(s7, sp, 0x68);
    sd(v0, s1, 96);
    ld(fp, sp, 0x70);
    ld(v1, s2, 96);
    ld(ra, sp, 0x78);
    sd(v1, s1, 104);
    ld(v0, s2, 104);
    sd(v0, s1, 112);
    ld(v1, s2, 112);
    sd(v1, s1, 120);
    ld(v0, s2, 120);
    ld(s2, sp, 0x40);
    sd(v0, s1, 128);
    ld(s1, sp, 0x38);
    sp = addiu(sp, 0x80);
}

// 0x0057E910 sub_57E910 -- 152 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s4 sp+0x20, ra sp+0x28
// [mwsfdFrameUserData] User data of a frame (h, sfd frame, out): when user data is enabled (sub_57FA50 == 1) and the
// player has its own user-data buffer (+376 != h + 352), out +68 / +72 = the frame's user data (address, size) when it
// holds 5 or more bytes, else 0.
void sub_57E910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e910
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = addiu(a0, 352);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    lw(v0, a1, 56);
    lw(s4, a0, 376);
    lw(s1, v0, 4);
    link(ctx, 0x57E940u);  // $ra first: the delay slot below depends on it
    lw(s0, v0, 0);
    call(ctx, gen::fn_sub_57FA50_0057fa50);
    v1 = 1;
    if (v0 != v1) {
        sw(zero, s2, 72);
    } else {
        // 0x0057e954
        charge(ctx, 2);
        if (s4 == s3) {
            // 0x0057e95c
            charge(ctx, 1);
            sw(zero, s2, 72);
            goto L_0057e960;
        }
        // 0x0057e968
        charge(ctx, 2);
        v0 = slti(s1, 5);
        if (s0 != 0) {
            // 0x0057e970
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0057e978
                charge(ctx, 2);
                s0 = addiu(s0, 4);
                s1 = addiu(s1, -4);
                goto L_0057e980;
            }
            sw(s1, s2, 72);
            goto L_0057e984;
        }
    L_0057e980:
        charge(ctx, 1);
        sw(s1, s2, 72);
    L_0057e984:
        charge(ctx, 1);
        sw(s0, s2, 68);
        // 0x0057e988 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_0057e960:
    charge(ctx, 2);
    sw(zero, s2, 68);
    // 0x0057e988 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0057E9A8 sub_57E9A8 -- 44 bytes; frame 0x10: ra sp+0x0
// [mwsfdTimeToMs] Frame time to milliseconds: muldiv(a, b, 1000 * c) (sub_57BAF0).
void sub_57E9A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057e9a8
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a2;
    sp = addiu(sp, -0x10);
    a2 = sll(v0, 5);
    sd(ra, sp, 0x0);
    a2 = subu(a2, v0);
    a2 = sll(a2, 2);
    ld(ra, sp, 0x0);
    a2 = addu(a2, v0);
    a2 = sll(a2, 3);
    sp = addiu(sp, 0x10);
    gen::fn_sub_57BAF0_0057baf0(ctx);  // tail call
}

// 0x0057E9D8 sub_57E9D8 -- 60 bytes; leaf frame (no stack)
// [mwsfdPicStruct] Picture-structure code: 1 -> 1, 2 -> 2, 3 -> 3, anything else 3.
void sub_57E9D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0057e9d8
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 2;
    a1 = sltiu(a0, 3);
    v1 = 2;
    if (a0 != v0) {
        // 0x0057e9e8
        charge(ctx, 2);
        if (a1 == 0) {
            v0 = 3;
            // 0x0057ea00
            charge(ctx, 1);
            v1 = 3;
        } else {
            // 0x0057e9f0
            charge(ctx, 3);
            v0 = 1;
            v1 = 1;
        }
        // 0x0057ea04
        charge(ctx, 2);
        if (a0 != v0) {
            v1 = 3;
        }
    }
    // 0x0057ea0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = v1;
}

// 0x0057EA18 sub_57EA18 -- 104 bytes; frame 0x10: ra sp+0x0
// [mwsfdPicType] Picture-type code: 1..4 kept, anything else prints "...: Invalid Ptype" through MWSFD's error printer
// sub_585590.
void sub_57EA18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ea18
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    a1 = sltiu(a0, 3);
    v1 = 2;
    if (a0 != v0) {
        // 0x0057ea30
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x0057ea38
            charge(ctx, 3);
            v0 = 1;
            v1 = 1;
            goto L_0057ea58;
        }
        v0 = 3;
        // 0x0057ea48
        charge(ctx, 2);
        v1 = 3;
        if (a0 == v0) {
            goto L_0057ea70;
        }
        // 0x0057ea50
        charge(ctx, 2);
        v0 = 4;
        v1 = 4;
    L_0057ea58:
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (a0 != v0) {
            // 0x0057ea60
            charge(ctx, 4);
            a0 = 0x7D0000;
            a0 = addiu(a0, -32096);  // "mwl_convPtypeFromSFD : Invalid Ptype"
            jal(ctx, 0x57EA64u, gen::fn_sub_585590_00585590);
            v1 = 1;
            goto L_0057ea70;
        }
        // 0x0057ea74 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = v1;
        sp = addiu(sp, 0x10);
        return;
    }
L_0057ea70:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0057ea74 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x0057EA80 sub_57EA80 -- 184 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// [mwsfdFrameConcat] Concatenation flag of a frame (h, sfd frame, ud, udlen): the picture structure (+88) 1 / 2 gives
// 2, 0 gives 0, 3 checks the frame's user data for the tag (sub_5A1340, tail1's strncmp caller) when enabled; other
// values print "E301271: ...: Invalid Pstruct".
void sub_57EA80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ea80
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    lw(v1, a1, 88);
    v0 = sltiu(v1, 3);
    s3 = a2;
    if (v0 == 0) {
        // 0x0057eac0
        charge(ctx, 3);
        v0 = 3;
        a0 = 0x7D0000;
        if (v1 != v0) {
        L_0057eae0:
            charge(ctx, 2);
            a0 = addiu(a0, -32056);
            jal(ctx, 0x57EAE0u, gen::fn_sub_585590_00585590);
        } else {
            // 0x0057eacc
            charge(ctx, 3);
            lb(v0, a1, 108);
            if (v0 == 0) {
                // 0x0057ead8
                charge(ctx, 2);
                s1 = 2;
            }
        }
    } else {
        // 0x0057eab0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0057eab8
            charge(ctx, 2);
            a0 = 0x7D0000;
            goto L_0057eae0;
        }
        s1 = 2;
    }
    // 0x0057eae8
    charge(ctx, 6);
    jal(ctx, 0x57EAE8u, gen::fn_sub_57FA50_0057fa50);
    s0 = v0;
    v0 = 1;
    if (s0 != v0) {
        v0 = s1;
    } else {
        // 0x0057eb00
        charge(ctx, 7);
        a0 = s3;
        a1 = s2;
        jal(ctx, 0x57EB04u, gen::fn_sub_5A1340_005a1340);
        v1 = 2;
        v0 = v0 ^ s0;
        if (v0 == 0) s1 = v1;
        v0 = s1;
    }
    // 0x0057eb1c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057EB38 sub_57EB38 -- 68 bytes; leaf frame (no stack)
// [mwsfdNoteFrame] Copies a frame's picture words into the player (+136..+160: structure, type, the three flag bytes as
// signed words, the frame number, the 64-bit time).
void sub_57EB38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0057eb38
    enter(ctx, 17);  // entry check point + this block's cycles
    lw(v1, a1, 88);
    a0 = addiu(a0, 136);
    lw(a2, a1, 60);
    sw(v1, a0, 0);
    lw(v0, a1, 92);
    sw(v0, a0, 4);
    lb(v1, a1, 108);
    sw(v1, a0, 8);
    lb(v0, a1, 109);
    sw(v0, a0, 12);
    lb(v1, a1, 110);
    sw(a2, a0, 20);
    sw(v1, a0, 16);
    lw(v0, a1, 64);
    sw(zero, a0, 28);
    sw(v0, a0, 24);
}

// 0x0057EB80 sub_57EB80 -- 124 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// [mwsfdFrameTagValues] Tag values of a frame (h, sfd frame, out): out +136 / +140 = the two values the SUD tag reader
// (sub_5A1790, tail1) finds in the frame's user data past its 4-byte header (needs 5 or more bytes), else 0.
void sub_57EB80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057eb80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(ra, sp, 0x18);
    sw(zero, sp, 0x0);
    lw(v0, a1, 56);
    lw(a1, v0, 4);
    lw(a0, v0, 0);
    sw(zero, sp, 0x4);
    v0 = slti(a1, 5);
    sw(zero, s0, 136);
    sw(zero, s0, 140);
    if (a0 != 0) {
        // 0x0057ebb4
        charge(ctx, 2);
        lw(v1, sp, 0x0);
        if (v0 == 0) {
            // 0x0057ebbc
            charge(ctx, 5);
            a0 = addiu(a0, 4);
            a1 = addiu(a1, -4);
            a2 = sp;
            a3 = addiu(sp, 0x4);
            jal(ctx, 0x57EBC8u, gen::fn_sub_5A1790_005a1790);
            goto L_0057ebd0;
        }
        goto L_0057ebd4;
    }
L_0057ebd0:
    charge(ctx, 1);
    lw(v1, sp, 0x0);
L_0057ebd4:
    charge(ctx, 2);
    lw(v0, sp, 0x4);
    if (v1 != 0) {
        // 0x0057ebdc
        charge(ctx, 2);
        if (i64(v0) > 0) {
            // 0x0057ebe4
            charge(ctx, 2);
            sw(v0, s0, 140);
            sw(v1, s0, 136);
            goto L_0057ebec;
        }
        ld(s0, sp, 0x10);
        // 0x0057ebf0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0057ebec:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0057ebf0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057EC00 sub_57EC00 -- 52 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// [mwsfdGetPictureInfo] sub_58E4A0 (SFD band) into a 16-byte stack record, then copied out by sub_57EDA8.
void sub_57EC00(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ec00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a3;
    sd(ra, sp, 0x18);
    a3 = sp;
    jal(ctx, 0x57EC10u, gen::fn_sub_58E4A0_0058e4a0);
    a1 = s0;
    a0 = sp;
    jal(ctx, 0x57EC1Cu, gen::fn_sub_57EDA8_0057eda8);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057EC38 sub_57EC38 -- 200 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, ra sp+0x40, s7 sp+0x38
// [mwsfdConvertPicture] Converts an SFD picture record (in) to the player's form (out): words reordered, the structure
// and type codes through sub_57ED00 / sub_57ED40. No caller.
void sub_57EC38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ec38
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x40);
    sd(s7, sp, 0x38);
    lw(a0, s0, 8);
    link(ctx, 0x57EC6Cu);  // $ra first: the delay slot below depends on it
    lw(s7, s0, 0);
    call(ctx, gen::fn_sub_57ED00_0057ed00);
    lw(s6, s0, 12);
    lw(a0, s0, 28);
    s5 = v0;
    lw(s2, s0, 16);
    lw(s3, s0, 20);
    link(ctx, 0x57EC88u);  // $ra first: the delay slot below depends on it
    lw(s4, s0, 24);
    call(ctx, gen::fn_sub_57ED40_0057ed40);
    lw(v1, s0, 48);
    lw(a0, s0, 40);
    lw(a1, s0, 44);
    lw(a2, s0, 60);
    lw(a3, s0, 64);
    sw(s7, s1, 32);
    sw(s5, s1, 28);
    sw(s6, s1, 0);
    sw(s2, s1, 4);
    sw(s3, s1, 8);
    sw(s4, s1, 12);
    sw(v1, s1, 44);
    sw(v0, s1, 16);
    sw(a0, s1, 20);
    sw(a1, s1, 24);
    sw(a2, s1, 36);
    sw(a3, s1, 40);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0057ED00 sub_57ED00 -- 60 bytes; leaf frame (no stack)
// Picture-structure code (a copy of sub_57E9D8).
void sub_57ED00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0057ed00
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 2;
    a1 = sltiu(a0, 3);
    v1 = 2;
    if (a0 != v0) {
        // 0x0057ed10
        charge(ctx, 2);
        if (a1 == 0) {
            v0 = 3;
            // 0x0057ed28
            charge(ctx, 1);
            v1 = 3;
        } else {
            // 0x0057ed18
            charge(ctx, 3);
            v0 = 1;
            v1 = 1;
        }
        // 0x0057ed2c
        charge(ctx, 2);
        if (a0 != v0) {
            v1 = 3;
        }
    }
    // 0x0057ed34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = v1;
}

// 0x0057ED40 sub_57ED40 -- 104 bytes; frame 0x10: ra sp+0x0
// Picture-type code (a copy of sub_57EA18: "...: Invalid Ptype" for values outside 1..4).
void sub_57ED40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ed40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    a1 = sltiu(a0, 3);
    v1 = 2;
    if (a0 != v0) {
        // 0x0057ed58
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x0057ed60
            charge(ctx, 3);
            v0 = 1;
            v1 = 1;
            goto L_0057ed80;
        }
        v0 = 3;
        // 0x0057ed70
        charge(ctx, 2);
        v1 = 3;
        if (a0 == v0) {
            goto L_0057ed98;
        }
        // 0x0057ed78
        charge(ctx, 2);
        v0 = 4;
        v1 = 4;
    L_0057ed80:
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (a0 != v0) {
            // 0x0057ed88
            charge(ctx, 4);
            a0 = 0x7D0000;
            a0 = addiu(a0, -32000);  // "mwl_convPtypeToSFD : Invalid Ptype"
            jal(ctx, 0x57ED8Cu, gen::fn_sub_585590_00585590);
            v1 = 1;
            goto L_0057ed98;
        }
        // 0x0057ed9c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = v1;
        sp = addiu(sp, 0x10);
        return;
    }
L_0057ed98:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0057ed9c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x0057EDA8 sub_57EDA8 -- 48 bytes; leaf frame (no stack)
// [mwsfdCopyPictureInfo] Copies a 16-byte picture record out: +0 = in +8, +4 = in +0, +8 = in +4, +12 = halfword +14,
// +16 / +20 = halfword +12.
void sub_57EDA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0057eda8
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(v0, a0, 8);
    lh(a2, a0, 12);
    sw(v0, a1, 0);
    lh(v1, a0, 14);
    lw(v0, a0, 0);
    sw(a2, a1, 20);
    sw(v0, a1, 4);
    sw(v1, a1, 12);
    lw(v0, a0, 4);
    sw(a2, a1, 16);
    sw(v0, a1, 8);
}

// 0x0057EDD8 sub_57EDD8 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdReleaseFrame] Releases a frame (h, frm): the player-handle check sub_581798 (it must return 1); an invalid
// handle prints "E410132 ...: handle is invalid." through sub_585590; locks API type 2 and releases the frame in SFD
// (sub_597B88). No caller.
void sub_57EDD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057edd8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x57EDECu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a1 = 2;
    a0 = s0;
    if (v0 != v1) {
        // 0x0057ee04
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -31960);  // "E410132: mwPlyRelFrm: handle is invalid."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x0057ee20
    charge(ctx, 11);
    jal(ctx, 0x57EE20u, gen::fn_sub_57E698_0057e698);
    a0 = s0;
    jal(ctx, 0x57EE28u, gen::fn_sub_5811D0_005811d0);
    a1 = s1;
    ld(s0, sp, 0x0);
    a0 = v0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_597B88_00597b88(ctx);  // tail call
}

// 0x0057EE50 sub_57EE50 -- 180 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// [mwsfdReleaseCurrentFrame] Releases the current frame (h): the player-handle check sub_581798 (it must return 1); an
// invalid handle prints "E1122615 ...: handle is invalid." through sub_585590; locks API type 1 and, when a frame is
// held (+128 < +124), releases it (sub_597D20) and counts it.
void sub_57EE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ee50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x57EE68u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a1 = 1;
    a0 = s3;
    if (v0 != v1) {
        // 0x0057ee80
        charge(ctx, 9);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -31912);  // "E1122615: mwPlyRelCurFrm: handle is invalid."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x0057eea8
    charge(ctx, 10);
    lw(s1, s3, 124);
    lw(s0, s3, 128);
    link(ctx, 0x57EEB0u);  // $ra first: the delay slot below depends on it
    lw(s2, s3, 120);
    call(ctx, gen::fn_sub_57E698_0057e698);
    a0 = s3;
    s0 = slt(s0, s1);
    jal(ctx, 0x57EEBCu, gen::fn_sub_5811D0_005811d0);
    a1 = s2;
    a0 = v0;
    if (s0 != 0) {
        // 0x0057eed0
        charge(ctx, 6);
        jal(ctx, 0x57EED0u, gen::fn_sub_597D20_00597d20);
        lw(v1, s3, 128);
        v1 = addiu(v1, 1);
        sw(v1, s3, 124);
        sw(v1, s3, 128);
    }
    // 0x0057eee8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057EF08 sub_57EF08 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdIsFrameLate] Is the next frame late? (h): the player-handle check sub_581798 (it must return 1); an invalid
// handle prints "E1122618 ...: handle is invalid." through sub_585590 and gives 0; else sub_593DB0 on the SFD handle.
void sub_57EF08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ef08
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57EF14u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x0057ef28
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -31864);  // "E1122618: mwPlyIsNextFrmReady: handle is invalid."
        jal(ctx, 0x57EF2Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
        // 0x0057ef68 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057ef40
    charge(ctx, 5);
    jal(ctx, 0x57EF40u, gen::fn_sub_5811D0_005811d0);
    v1 = v0;
    a0 = v1;
    if (v1 == 0) {
        // 0x0057ef68 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057ef54
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_593DB0_00593db0(ctx);  // tail call
}

// 0x0057EF78 sub_57EF78 -- 180 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// [mwsfdGetUserData] Frame user data (h, &addr, &size): the player-handle check sub_581798 (it must return 1); an
// invalid handle prints "E3122201 ...: handle is invalid." through sub_585590; else SFD's user data (sub_593BF8),
// skipping its 4-byte header when it holds 4 or more bytes. No caller.
void sub_57EF78(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057ef78
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x18);
    sw(zero, s2, 0);
    link(ctx, 0x57EF9Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 0);
    call(ctx, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x0057efb0
        charge(ctx, 8);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -31808);  // "E3122201: mwPlyGetNextPicUsr: handle is invalid."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x0057efd0
    charge(ctx, 6);
    jal(ctx, 0x57EFD0u, gen::fn_sub_5811D0_005811d0);
    a1 = s2;
    a2 = s1;
    a0 = v0;
    if (v0 != 0) {
        // 0x0057efe8
        charge(ctx, 7);
        jal(ctx, 0x57EFE8u, gen::fn_sub_593BF8_00593bf8);
        lw(v0, s1, 0);
        v1 = addiu(v0, -4);
        v0 = slti(v0, 4);
        ld(s0, sp, 0x0);
        if (v0 == 0) {
            // 0x0057f004
            charge(ctx, 4);
            lw(v0, s2, 0);
            sw(v1, s1, 0);
            v0 = addiu(v0, 4);
            sw(v0, s2, 0);
            goto L_0057f014;
        }
        // 0x0057f018 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0057f014:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0057f018 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057F050 sub_57F050 -- 8 bytes; leaf frame (no stack)
// Returns its argument (an 8-byte stub; no caller).
void sub_57F050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057f050
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0057F058 sub_57F058 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSkippedFrames] Dropped-frame count (h): the player-handle check sub_581798 (it must return 1); an invalid
// handle prints "E202231 ...: handle is invalid." through sub_585590 and gives 0; else +132.
void sub_57F058(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f058
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57F064u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -31752);  // "E202231: mwPlyGetNumSkipDisp: handle is invalid."
    if (v0 == v1) {
        // 0x0057f090
        charge(ctx, 1);
        lw(v0, s0, libs3::mwsfd::kSkipped);
    } else {
        // 0x0057f07c
        charge(ctx, 4);
        jal(ctx, 0x57F07Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x0057f094 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057F0A8 sub_57F0A8 -- 104 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [mwsfdRingSysWord] The system word of the current header-ring entry (h): entry (+184 mod 8) of the ring (+192,
// 20-byte entries) when valid, its +12, else 0. Two chunks (the ring-index tail at 0x57F5A0 is shared with tail1's
// sub_57F5F8 shape). No caller.
void sub_57F0A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f0a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0057f5a0
    charge(ctx, 18);
    lw(a2, a0, 184);
    t0 = 1;
    v0 = 0;
    a1 = slti(a2, 0);
    a3 = addiu(a2, 7);
    v1 = a2;
    if (a1 != 0) v1 = a3;
    a1 = sra(v1, 3);
    a1 = sll(a1, 3);
    a1 = subu(a2, a1);
    v1 = sll(a1, 2);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addiu(v1, 192);
    a1 = addu(a0, v1);
    lw(a0, a1, 0);
    v1 = a1;
    if (a0 == t0) {
        // 0x0057f5e8
        charge(ctx, 1);
        lw(v0, v1, 12);
    }
    // 0x0057f5ec (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057F600 sub_57F600 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSkippedDecodes] Skipped-decode count (h): the player-handle check sub_581798 (it must return 1); an invalid
// handle prints "E409171 ...: handle is invalid." through sub_585590 and gives 0; else sub_593C58 on the SFD handle. No
// caller.
void sub_57F600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f600
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57F60Cu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x0057f620
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -31656);  // "E409171: mwPlyGetNumRemainFrm: handle is invalid."
        jal(ctx, 0x57F624u, gen::fn_sub_585590_00585590);
        v0 = 0;
        // 0x0057f660 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057f638
    charge(ctx, 5);
    jal(ctx, 0x57F638u, gen::fn_sub_5811D0_005811d0);
    v1 = v0;
    a0 = v1;
    if (v1 == 0) {
        // 0x0057f660 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057f64c
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_593C58_00593c58(ctx);  // tail call
}

// 0x0057F670 sub_57F670 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdFindStream] Finds a stream by id in the player's SFD handle (h, id, &index): the stream table at SFD +9504
// (count) / +9512 (240-byte records, id at +8); *index = its number or -1. No caller.
void sub_57F670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f670
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x57F684u, gen::fn_sub_5811D0_005811d0);
    lw(a1, v0, 9504);
    v0 = addiu(v0, 9512);
    v1 = si(-1);
    a0 = 0;
    sw(v1, s0, 0);
    a2 = 0;
    if (i64(a1) > 0) {
        // 0x0057f6a8
        charge(ctx, 2);
        v1 = v0;
        for (;;) {
            // 0x0057f6b0
            charge(ctx, 3);
            lw(v0, v1, 8);
            if (s1 != v0) {
                a0 = addiu(a0, 1);
            } else {
                // 0x0057f6bc
                charge(ctx, 3);
                sw(a0, s0, 0);
                lw(a2, v1, 0);
                a0 = addiu(a0, 1);
            }
            // 0x0057f6c8
            charge(ctx, 3);
            v0 = slt(a0, a1);
            v1 = addiu(v1, 240);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0057f6d4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, s0, 0);
    v0 = si(-1);
    ld(s0, sp, 0x0);
    v1 = v1 ^ v0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    if (v1 != 0) v0 = a2;
    sp = addiu(sp, 0x20);
}

// 0x0057F6F8 sub_57F6F8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdStreamWord] The first word of stream record i of the player's SFD handle (SFD +9512 + 240 * i). No caller.
void sub_57F6F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f6f8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x57F704u, gen::fn_sub_5811D0_005811d0);
    v1 = sll(s0, 4);
    ld(ra, sp, 0x8);
    v1 = subu(v1, s0);
    ld(s0, sp, 0x0);
    v1 = sll(v1, 4);
    v0 = addu(v0, v1);
    lw(v0, v0, 9512);
    sp = addiu(sp, 0x10);
}

// 0x0057F750 sub_57F750 -- 24 bytes; frame 0x10: ra sp+0x0
// [mwsfdSfdErrorCb] The SFD error callback MWSFD installs at init: prints the error text (a1) through MWSFD's error
// printer sub_585590.
void sub_57F750(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f750
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x0057F768 sub_57F768 -- 436 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// [mwsfdInit] MWSFD init (iprm): "E1122611 ...: iprm is NULL." for a null parameter; copies it to the stack, stores the
// MWSFD banner at 0x99EC58, sets up the CRI library layers (sub_585210, sub_580C80, and on the first init -- 0x7B2F48
// == 0 -- the CRI band's ADX / SJ / SVM inits and GSC, "E2005 ...: can't init GSC"), the work record (sub_57F980), SFD
// (sub_57FCB0), the frame rate (sub_57FAB8), the CRI server threads (sub_57F920) and its error callback (sub_57F750);
// counts the inits (0x7B2F48).
void sub_57F768(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0057f768
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    a0 = sp;
    sd(ra, sp, 0x30);
    if (s0 != 0) {
        // 0x0057f798
        charge(ctx, 35);
        a1 = 0;
        a2 = 32;
        jal(ctx, 0x57F79Cu, gen::fn_memset_00521408);
        lwc1(f0, s0, 0);
        v1 = 0x9A0000;
        v0 = 0x7D0000;
        v1 = addiu(v1, -5032);  // &0x99EC58
        v0 = addiu(v0, -31600);  // "\nMWSFD/PS2EE Ver.3.50 Build:Mar  1 2005 10:54:15\n"
        lw(a0, s0, 20);
        s1 = 0x7B0000;
        lw(t2, s0, 28);
        lw(t1, s0, 4);
        lw(t0, s0, 8);
        lw(a2, s0, 16);
        lw(a1, s0, 24);
        lw(a3, s0, 12);
        sw(v0, v1, 0);  // 0x99EC58
        sw(a0, sp, 0x14);
        swc1(f0, sp, 0x0);
        sw(t1, sp, 0x4);
        sw(t0, sp, 0x8);
        sw(a3, sp, 0xC);
        sw(a2, sp, 0x10);
        sw(a1, sp, 0x18);
        link(ctx, 0x57F7F8u);  // $ra first: the delay slot below depends on it
        sw(t2, sp, 0x1C);
        call(ctx, gen::fn_sub_585210_00585210);
        jal(ctx, 0x57F800u, gen::fn_sub_580C80_00580c80);
        lw(a0, s1, 12104);  // 0x7B2F48
        lw(v0, sp, 0x8);
        v0 = addiu(v0, -2);
        v1 = slti(v0, 0);
        if (v1 != 0) v0 = 0;
        sw(v0, sp, 0x8);
        if (a0 == 0) {
            // 0x0057f824
            charge(ctx, 12);
            jal(ctx, 0x57F824u, gen::fn_sub_53EA90_0053ea90);
            jal(ctx, 0x57F82Cu, gen::fn_sub_562288_00562288);
            jal(ctx, 0x57F834u, gen::fn_sub_561870_00561870);
            jal(ctx, 0x57F83Cu, gen::fn_sub_562E90_00562e90);
            jal(ctx, 0x57F844u, gen::fn_sub_5862F0_005862f0);
            if (v0 != 0) {
                // 0x0057f854
                charge(ctx, 5);
                a0 = si(-101);
                jal(ctx, 0x57F854u, gen::fn_sub_57FC60_0057fc60);
                a0 = 0x7D0000;
                a0 = addiu(a0, -31400);  // "E2005 mwPlyInitSfdFx: can't init GSC"
                jal(ctx, 0x57F860u, gen::fn_sub_585590_00585590);
            }
            // 0x0057f868
            charge(ctx, 19);
            a0 = sp;
            jal(ctx, 0x57F868u, gen::fn_sub_57F980_0057f980);
            v0 = 0x7B0000;
            v0 = addiu(v0, 17732);  // &0x7B4544
            at = 0x447A0000;
            mtc1(at, f2);
            sw(zero, v0, 0);  // 0x7B4544
            at = 0x3F000000;
            mtc1(at, f1);
            lwc1(f0, sp, 0x0);
            mul_s(f0, f0, f2);
            add_s(f0, f0, f1);
            cvt_w_s(f1, f0);
            mfc1(a0, f1);
            jal(ctx, 0x57F8A0u, gen::fn_sub_57FCB0_0057fcb0);
            a0 = 0x7D0000;
            a0 = addiu(a0, -31360);  // "ERR20010421A : mwPlyInitSfdFx"
            if (v0 != 0) {
                // 0x0057f8b4
                charge(ctx, 2);
                jal(ctx, 0x57F8B4u, gen::fn_sub_585590_00585590);
            }
            // 0x0057f8bc
            charge(ctx, 15);
            a0 = sp;
            v0 = 0x7B0000;
            v1 = 1;
            link(ctx, 0x57F8C8u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, 12108);
            call(ctx, gen::fn_sub_57FAB8_0057fab8);
            jal(ctx, 0x57F8D0u, gen::fn_sub_55DC88_0055dc88);
            a0 = 0x580000;
            a0 = addiu(a0, -2224);  // &sub_57F750
            a1 = 0;
            jal(ctx, 0x57F8E0u, gen::fn_sub_55DBC0_0055dbc0);
            jal(ctx, 0x57F8E8u, gen::fn_sub_582798_00582798);
            a0 = sp;
            jal(ctx, 0x57F8F0u, gen::fn_sub_57F920_0057f920);
        }
        // 0x0057f8f8
        charge(ctx, 5);
        v1 = addiu(s1, 12104);
        lw(v0, v1, 0);
        v0 = addiu(v0, 1);
        sw(v0, v1, 0);
        ld(s0, sp, 0x20);
    } else {
        // 0x0057f784
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -31440);  // "E1122611 mwPlyInitSfdFx: iprm is NULL."
        jal(ctx, 0x57F788u, gen::fn_sub_585590_00585590);
        ld(s0, sp, 0x20);
    }
    // 0x0057f90c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0057F920 sub_57F920 -- 96 bytes; frame 0x10: ra sp+0x0
// [mwsfdCreateServerThreads] Creates the three MWSFD server threads through the CRI band: the vsync thread (sub_5852F8
// with sub_585BA8, "MWSFSVR_VsyncThrdProc"), the main thread (sub_5853B8, sub_585BC0) and the idle thread (sub_585360,
// sub_585C08), then starts them (sub_585410).
void sub_57F920(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f920
    enter(ctx, 24);  // entry check point + this block's cycles
    a1 = 0x580000;
    a3 = 0x7D0000;
    sp = addiu(sp, -0x10);
    a3 = addiu(a3, -31328);  // "MWSFSVR_VsyncThrdProc"
    a1 = addiu(a1, 23464);  // &sub_585BA8
    a0 = 2;
    sd(ra, sp, 0x0);
    a2 = 0;
    jal(ctx, 0x57F93Cu, gen::fn_sub_5852F8_005852f8);
    a0 = 0x580000;
    a2 = 0x7D0000;
    a0 = addiu(a0, 23488);  // &sub_585BC0
    a2 = addiu(a2, -31304);  // "MWSFSVR_MainThrdProc"
    a1 = 0;
    jal(ctx, 0x57F954u, gen::fn_sub_5853B8_005853b8);
    a0 = 0x580000;
    a2 = 0x7D0000;
    a0 = addiu(a0, 23560);  // &sub_585C08
    a2 = addiu(a2, -31280);  // "MWSFSVR_IdleThrdProc"
    a1 = 0;
    jal(ctx, 0x57F96Cu, gen::fn_sub_585360_00585360);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_585410_00585410(ctx);  // tail call
}

// 0x0057F980 sub_57F980 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdInitWork] Resets the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) (5,580 bytes cleared,
// sub_5860E8(0)) and copies the init parameter's frame rate (float +0), +4, +8 and +12 into it.
void sub_57F980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0057f980
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x57F990u, gen::fn___gthread_get_ee_key_use_0057f740);
    s1 = v0;
    a1 = 0;
    a0 = s1;
    a2 = 5580;
    jal(ctx, 0x57F9A4u, gen::fn_memset_00521408);
    a0 = 0;
    jal(ctx, 0x57F9ACu, gen::fn_sub_5860E8_005860e8);
    v0 = 1;
    sw(zero, s1, 92);
    a1 = addiu(s1, 4);
    if (s0 == 0) {
        // 0x0057f9e8
        charge(ctx, 7);
        at = 0x426F0000;
        at = at | 0xC28F;
        mtc1(at, f0);
        sw(zero, a1, 12);
        swc1(f0, a1, 0);
        sw(v0, a1, 8);
        sw(v0, a1, 4);
    } else {
        // 0x0057f9c4
        charge(ctx, 9);
        lw(v0, s0, 4);
        lw(v1, s0, 12);
        sw(v0, a1, 4);
        lwc1(f0, s0, 0);
        lw(v0, s0, 8);
        sw(v1, a1, 12);
        swc1(f0, a1, 0);
        sw(v0, a1, 8);
    }
    // 0x0057fa04 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    sw(zero, s1, 60);
    sw(v0, s1, 56);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057FA28 sub_57FA28 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSetUserDataSwitch] Sets the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) user-data switch (+56). No
// caller.
void sub_57FA28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fa28
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57FA34u, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, libs3::mwsfd::kWorkUsrDatSw);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0057FA50 sub_57FA50 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdUsrDatSw] Returns the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) user-data switch (+56).
void sub_57FA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fa50
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57FA58u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, v0, libs3::mwsfd::kWorkUsrDatSw);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0057FA70 sub_57FA70 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSetWork60] Sets the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use) word +60. No caller.
void sub_57FA70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fa70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57FA7Cu, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, libs3::mwsfd::kWork60);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0057FAB8 sub_57FAB8 -- 56 bytes; frame 0x10: ra sp+0x0
// [mwsfdSetFps] Sets the SFD frame-rate parameters from the init parameter: sub_581690(0, 27, (int) fps) and
// sub_581690(0, 7, 1).
void sub_57FAB8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0057fab8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 27;
    sd(ra, sp, 0x0);
    lwc1(f0, a0, 0);
    cvt_w_s(f1, f0);
    mfc1(a2, f1);
    a0 = 0;
    jal(ctx, 0x57FAD0u, gen::fn_sub_581690_00581690);
    a0 = 0;
    ld(ra, sp, 0x0);
    a1 = 7;
    a2 = 1;
    sp = addiu(sp, 0x10);
    gen::fn_sub_581690_00581690(ctx);  // tail call
}

// 0x0057FAF0 sub_57FAF0 -- 48 bytes; frame 0x10: ra sp+0x0
// [mwsfdReinit] Re-initialises MWSFD when the init count (0x7B2F48) is non-zero: clears it and runs sub_57F768 (with
// the caller's $a0). No caller.
void sub_57FAF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057faf0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 12104);  // &0x7B2F48
    lw(v1, v0, 0);  // 0x7B2F48
    ld(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x0057fb18
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0057fb0c
    charge(ctx, 3);
    sw(zero, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_57F768_0057f768(ctx);  // tail call
}

// 0x0057FC90 sub_57FC90 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdLastErrorCode] Returns the last MWSFD error code (the MWSFD work record (0x7B2F50, __gthread_get_ee_key_use)
// +104). No caller.
void sub_57FC90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fc90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57FC98u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, v0, libs3::mwsfd::kWorkLastError);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0057FCB0 sub_57FCB0 -- 164 bytes; frame 0x20: ra sp+0x10
// [mwsfdInitSfd] SFD start-up for MWSFD (work): checks SFD's version ("1.958", handle size 14,256: sub_58BC20; "E011081
// ...: Not compatible SFD Version."), initialises SFD with {0x7C8520 word, work} (sub_58BC30; error -301) and installs
// the error callback r_lock_def_get_free_item_2 (sub_58BEF0; error -303).
void sub_57FCB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fcb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x7D0000;
    v0 = 0x7D0000;
    sd(ra, sp, 0x10);
    t0 = addiu(v0, -31456);  // &0x7C8520
    ldl(a1, t0, 7);  // 0x7C8527
    ldr(a1, t0, 0);  // 0x7C8520
    sdl(a1, sp, 0x7);
    sdr(a1, sp, 0x0);
    a1 = 14256;
    sw(a0, sp, 0x4);
    a0 = addiu(v1, -31256);  // "1.958"
    jal(ctx, 0x57FCDCu, gen::fn_sub_58BC20_0058bc20);
    v1 = 1;
    a0 = sp;
    if (v0 != v1) {
        // 0x0057fcf0
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -31248);  // "E011081 mwPlySfdInit: Not compatible SFD Version."
        jal(ctx, 0x57FCF4u, gen::fn_sub_585590_00585590);
        v0 = si(-1);
        goto L_0057fd48;
    }
    // 0x0057fd08
    charge(ctx, 4);
    jal(ctx, 0x57FD08u, gen::fn_sub_58BC30_0058bc30);
    a1 = 0x580000;
    if (v0 == 0) {
        // 0x0057fd28
        charge(ctx, 6);
        a0 = 0;
        a1 = addiu(a1, -648);
        a2 = 0;
        jal(ctx, 0x57FD30u, gen::fn_sub_58BEF0_0058bef0);
        a0 = si(-303);
        if (v0 != 0) {
            // 0x0057fd40
            charge(ctx, 2);
            jal(ctx, 0x57FD40u, gen::fn_sub_57FC60_0057fc60);
        }
    L_0057fd48:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x0057fd18
        charge(ctx, 4);
        a0 = si(-301);
        jal(ctx, 0x57FD18u, gen::fn_sub_57FC60_0057fc60);
        ld(ra, sp, 0x10);
    }
    // 0x0057fd4c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x0057FD58 r_lock_def_free_2 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdFinishSfd] SFD finish for MWSFD: sub_58BD68; returns 0. The FLIRT name is a false match of a short code shape;
// the role is read from the instructions.
void r_lock_def_free_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fd58
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57FD60u, gen::fn_sub_58BD68_0058bd68);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0057FD78 r_lock_def_get_free_item_2 -- 664 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s2 sp+0x10, s4 sp+0x20, ra sp+0x28
// [mwsfdSfdErrorHandler] MWSFD's SFD error callback (handle, code): records the handle and its player (sub_5811D0) in
// 0x7B451C / 0x7B4520, appends the code to the 16-entry history (0x99EC60, count 0x99ECA0), formats the message for the
// code into 0x99ECA8 with sprintf ("DATA ERROR(%08X)", "DEC ERROR(%08X): " + the decoder's text via sub_594E50 and
// strncat, the "SFD ERROR(%08X): ..." texts for the known codes) and prints it (sub_585590). The FLIRT name is a false
// match of a short code shape; the role is read from the instructions.
void r_lock_def_get_free_item_2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057fd78
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (s0 == 0) {
        // 0x0057fdc8
        charge(ctx, 5);
        v0 = 0x7B0000;
        v1 = 0x7B0000;
        sw(zero, v0, 17692);  // 0x7B451C
        s2 = 0;
        sw(zero, v1, 17696);  // 0x7B4520
    } else {
        // 0x0057fda4
        charge(ctx, 8);
        jal(ctx, 0x57FDA4u, gen::fn_sub_5811D0_005811d0);
        v1 = 0x7B0000;
        s2 = v0;
        v0 = 0x7B0000;
        sw(s0, v0, 17692);  // 0x7B451C
        sw(s2, v1, 17696);  // 0x7B4520
    }
    // 0x0057fddc
    charge(ctx, 2);
    v0 = 0x9A0000;
    if (s1 != 0) {
        // 0x0057fde4
        charge(ctx, 9);
        a1 = addiu(v0, -4960);
        lw(a0, a1, 0);
        v0 = sll(a0, 2);
        v1 = slti(a0, 15);
        at = 0x9A0000;
        at = addu(at, v0);
        sw(s1, at, -5024);
        v0 = addiu(a0, 1);
        if (v1 != 0) {
            // 0x0057fe08
            charge(ctx, 1);
            sw(v0, a1, 0);
        }
    }
    // 0x0057fe0c
    charge(ctx, 5);
    v0 = lui(0xFF00);
    v0 = v0 | 0xF18;
    v0 = slt(v0, s1);
    if (v0 != 0) {
        // 0x0057fe90
        charge(ctx, 4);
        v0 = lui(0xFF00);
        v0 = v0 | 0xF40;
        cc = s1 == v0;  // the condition, before the delay slot changes it
        v0 = slt(v0, s1);
        if (cc) {
            // 0x0057fef8
            charge(ctx, 10);
            s4 = 0x9A0000;
            a1 = 0x7D0000;
            s0 = addiu(s4, -4952);  // &0x99ECA8
            a2 = lui(0xFF00);
            a1 = addiu(a1, -31112);  // "DEC ERROR(%08X): "
            a0 = s0;
            a2 = a2 | 0xF40;
            jal(ctx, 0x57FF10u, gen::fn_sprintf_00523ac8);
            if (s2 != 0) {
                // 0x0057ff20
                charge(ctx, 3);
                a0 = s2;
                jal(ctx, 0x57FF20u, gen::fn_sub_594E50_00594e50);
                s3 = v0;
            }
            // 0x0057ff2c
            charge(ctx, 2);
            a0 = s0;
            if (s3 == 0) {
            L_0057ffec:
                charge(ctx, 1);
                a0 = addiu(s4, -4952);
            } else {
                // 0x0057ff34
                charge(ctx, 5);
                a1 = s3;
                a2 = 233;
                jal(ctx, 0x57FF38u, gen::fn_strncat_005244c0);
                a0 = addiu(s4, -4952);
            }
        } else {
            // 0x0057fea0
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = slti(s1, -1);
            if (cc) {
                // 0x0057fed0
                charge(ctx, 2);
                s4 = 0x9A0000;
                if (v0 == 0) {
                    // 0x0057ffd8
                    charge(ctx, 1);
                    a1 = 0x7D0000;
                L_0057ffdc:
                    charge(ctx, 4);
                    a1 = addiu(a1, -30584);
                    a2 = s1;
                    a0 = addiu(s4, -4952);
                    jal(ctx, 0x57FFE4u, gen::fn_sprintf_00523ac8);
                    goto L_0057ffec;
                }
                // 0x0057fed8
                charge(ctx, 3);
                v0 = slti(s1, -3);
                if (v0 != 0) {
                    a1 = 0x7D0000;
                    goto L_0057ffdc;
                }
                // 0x0057fee4
                charge(ctx, 4);
                s4 = 0x9A0000;
                a1 = 0x7D0000;
                a1 = addiu(a1, -31136);  // "DATA ERROR(%08X)"
            L_0057ff60:
                charge(ctx, 5);
                a2 = s1;
                a0 = addiu(s4, -4952);
                jal(ctx, 0x57FF64u, gen::fn_sprintf_00523ac8);
                a0 = addiu(s4, -4952);
            } else {
                // 0x0057fea8
                charge(ctx, 4);
                v0 = lui(0xFF00);
                v0 = v0 | 0xF1C;
                s4 = 0x9A0000;
                if (s1 == v0) {
                L_0057ff58:
                    charge(ctx, 1);
                    a1 = 0x7D0000;
                L_0057ff5c:
                    charge(ctx, 1);
                    a1 = addiu(a1, -30992);
                    goto L_0057ff60;
                }
                // 0x0057feb8
                charge(ctx, 4);
                v0 = lui(0xFF00);
                v0 = v0 | 0xF1F;
                a1 = 0x7D0000;
                if (s1 != v0) {
                    // 0x0057fec8
                    charge(ctx, 2);
                    a1 = 0x7D0000;
                    goto L_0057ffdc;
                }
                // 0x0057ffb8
                charge(ctx, 7);
                a2 = lui(0xFF00);
                a1 = addiu(a1, -30656);
                a0 = addiu(s4, -4952);
                a2 = a2 | 0xF1F;
                jal(ctx, 0x57FFC4u, gen::fn_sprintf_00523ac8);
                a0 = addiu(s4, -4952);
            }
        }
    } else {
        // 0x0057fe20
        charge(ctx, 5);
        v0 = lui(0xFF00);
        v0 = v0 | 0xF17;
        v0 = slt(s1, v0);
        s4 = 0x9A0000;
        if (v0 == 0) {
            // 0x0057ff48
            charge(ctx, 3);
            a1 = 0x7D0000;
            a1 = addiu(a1, -31088);  // "SFD ERROR(%08X): 'max_width, max_height' of creation parameter is small. Increase this value."
            goto L_0057ff60;
        }
        // 0x0057fe34
        charge(ctx, 4);
        v0 = lui(0xFF00);
        v0 = v0 | 0x40C;
        cc = s1 == v0;  // the condition, before the delay slot changes it
        v0 = slt(v0, s1);
        if (cc) {
            goto L_0057ff58;
        }
        // 0x0057fe44
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0057fe4c
            charge(ctx, 4);
            v0 = lui(0xFF00);
            v0 = v0 | 0x408;
            a1 = 0x7D0000;
            if (s1 == v0) {
                goto L_0057ff5c;
            }
            // 0x0057fe5c
            charge(ctx, 2);
            a1 = 0x7D0000;
            goto L_0057ffdc;
        }
        // 0x0057fe68
        charge(ctx, 4);
        v0 = lui(0xFF00);
        v0 = v0 | 0xC04;
        s4 = 0x9A0000;
        if (s1 == v0) {
            // 0x0057ff98
            charge(ctx, 8);
            a1 = 0x7D0000;
            a2 = lui(0xFF00);
            a1 = addiu(a1, -30792);  // &0x7C87B8
            a0 = addiu(s4, -4952);
            a2 = a2 | 0xC04;
            jal(ctx, 0x57FFA8u, gen::fn_sprintf_00523ac8);
            a0 = addiu(s4, -4952);
        } else {
            // 0x0057fe78
            charge(ctx, 4);
            v0 = lui(0xFF00);
            v0 = v0 | 0xF15;
            a1 = 0x7D0000;
            if (s1 != v0) {
                // 0x0057fe88
                charge(ctx, 2);
                a1 = 0x7D0000;
                goto L_0057ffdc;
            }
            // 0x0057ff78
            charge(ctx, 7);
            a2 = lui(0xFF00);
            a1 = addiu(a1, -30904);
            a0 = addiu(s4, -4952);
            a2 = a2 | 0xF15;
            jal(ctx, 0x57FF84u, gen::fn_sprintf_00523ac8);
            a0 = addiu(s4, -4952);
        }
    }
    // 0x0057fff0
    charge(ctx, 8);
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

}  // namespace p3fes::game
