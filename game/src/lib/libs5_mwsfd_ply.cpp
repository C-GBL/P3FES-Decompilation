// Phase 5 slice libs5: CRI Sofdec MWSFD, part 1: the movie player's entry points -- start / stop / pause, the handle
// check, the status, the play-time and SFD bridges, the SFX and header-ring hooks of a player (0x580000-0x584000).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_R_LOCK_DEF_lock_free_4_005865c0(p3fes::EEContext&);
void fn_WTLS_get_table_0_00580df0(p3fes::EEContext&);
void fn___env_lock_11_00581138(p3fes::EEContext&);
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_my_malloc_0_00581070(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_541008_00541008(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_57D518_0057d518(p3fes::EEContext&);
void fn_sub_57DB58_0057db58(p3fes::EEContext&);
void fn_sub_57F328_0057f328(p3fes::EEContext&);
void fn_sub_57FA98_0057fa98(p3fes::EEContext&);
void fn_sub_57FC60_0057fc60(p3fes::EEContext&);
void fn_sub_5800F0_005800f0(p3fes::EEContext&);
void fn_sub_580130_00580130(p3fes::EEContext&);
void fn_sub_580270_00580270(p3fes::EEContext&);
void fn_sub_580368_00580368(p3fes::EEContext&);
void fn_sub_580378_00580378(p3fes::EEContext&);
void fn_sub_580628_00580628(p3fes::EEContext&);
void fn_sub_580750_00580750(p3fes::EEContext&);
void fn_sub_580900_00580900(p3fes::EEContext&);
void fn_sub_580958_00580958(p3fes::EEContext&);
void fn_sub_5809B0_005809b0(p3fes::EEContext&);
void fn_sub_580A28_00580a28(p3fes::EEContext&);
void fn_sub_580C80_00580c80(p3fes::EEContext&);
void fn_sub_580CB0_00580cb0(p3fes::EEContext&);
void fn_sub_580D40_00580d40(p3fes::EEContext&);
void fn_sub_580E10_00580e10(p3fes::EEContext&);
void fn_sub_580E78_00580e78(p3fes::EEContext&);
void fn_sub_580E98_00580e98(p3fes::EEContext&);
void fn_sub_580ED8_00580ed8(p3fes::EEContext&);
void fn_sub_580F10_00580f10(p3fes::EEContext&);
void fn_sub_580F78_00580f78(p3fes::EEContext&);
void fn_sub_580FB8_00580fb8(p3fes::EEContext&);
void fn_sub_580FE8_00580fe8(p3fes::EEContext&);
void fn_sub_5810F0_005810f0(p3fes::EEContext&);
void fn_sub_581108_00581108(p3fes::EEContext&);
void fn_sub_581120_00581120(p3fes::EEContext&);
void fn_sub_581148_00581148(p3fes::EEContext&);
void fn_sub_5811D0_005811d0(p3fes::EEContext&);
void fn_sub_581690_00581690(p3fes::EEContext&);
void fn_sub_5816F0_005816f0(p3fes::EEContext&);
void fn_sub_581798_00581798(p3fes::EEContext&);
void fn_sub_581840_00581840(p3fes::EEContext&);
void fn_sub_582798_00582798(p3fes::EEContext&);
void fn_sub_5827F0_005827f0(p3fes::EEContext&);
void fn_sub_5827F8_005827f8(p3fes::EEContext&);
void fn_sub_582810_00582810(p3fes::EEContext&);
void fn_sub_582828_00582828(p3fes::EEContext&);
void fn_sub_583028_00583028(p3fes::EEContext&);
void fn_sub_5833D8_005833d8(p3fes::EEContext&);
void fn_sub_5833E8_005833e8(p3fes::EEContext&);
void fn_sub_583410_00583410(p3fes::EEContext&);
void fn_sub_583470_00583470(p3fes::EEContext&);
void fn_sub_5834A0_005834a0(p3fes::EEContext&);
void fn_sub_583500_00583500(p3fes::EEContext&);
void fn_sub_583520_00583520(p3fes::EEContext&);
void fn_sub_5835A8_005835a8(p3fes::EEContext&);
void fn_sub_5835F0_005835f0(p3fes::EEContext&);
void fn_sub_5837A0_005837a0(p3fes::EEContext&);
void fn_sub_5847D0_005847d0(p3fes::EEContext&);
void fn_sub_584C80_00584c80(p3fes::EEContext&);
void fn_sub_584CD8_00584cd8(p3fes::EEContext&);
void fn_sub_584E08_00584e08(p3fes::EEContext&);
void fn_sub_585050_00585050(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_586248_00586248(p3fes::EEContext&);
void fn_sub_586428_00586428(p3fes::EEContext&);
void fn_sub_586610_00586610(p3fes::EEContext&);
void fn_sub_5957D8_005957d8(p3fes::EEContext&);
void fn_sub_595988_00595988(p3fes::EEContext&);
void fn_sub_5972B0_005972b0(p3fes::EEContext&);
void fn_sub_597368_00597368(p3fes::EEContext&);
void fn_sub_597968_00597968(p3fes::EEContext&);
void fn_sub_5990C0_005990c0(p3fes::EEContext&);
void fn_sub_599100_00599100(p3fes::EEContext&);
void fn_sub_599368_00599368(p3fes::EEContext&);
void fn_sub_59C8E0_0059c8e0(p3fes::EEContext&);
void fn_sub_59F970_0059f970(p3fes::EEContext&);
void fn_sub_59FAA8_0059faa8(p3fes::EEContext&);
void fn_sub_59FCC0_0059fcc0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x005800F0 sub_5800F0 -- 60 bytes; frame 0x10: ra sp+0x0
// [mwPlySfdStandby] MWSFD: puts the player's SFD handle (+60) into standby (sub_595988); on failure records -311 as
// the last error (sub_57FC60) and reports 'mwPlySfdStandby'. Returns SFD's result, or -311.
void sub_5800F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005800f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x5800F8u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 60);
    call(ctx, gen::fn_sub_595988_00595988);
    a0 = si(-311);
    if (v0 != 0) {
        // 0x00580108
        charge(ctx, 6);
        jal(ctx, 0x580108u, gen::fn_sub_57FC60_0057fc60);
        a0 = 0x7D0000;
        a0 = addiu(a0, -30568);  // "E20010703F mwPlySfdStandby: "
        jal(ctx, 0x580114u, gen::fn_sub_585590_00585590);
        v0 = si(-311);
    }
    // 0x00580120 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00580130 sub_580130 -- 60 bytes; frame 0x10: ra sp+0x0
// [mwPlySfdStart] MWSFD: starts the player's SFD handle (sub_5972B0); on failure records -307 and reports
// 'mwPlySfdStart'. Returns SFD's result, or -307.
void sub_580130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580130
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x580138u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 60);
    call(ctx, gen::fn_sub_5972B0_005972b0);
    a0 = si(-307);
    if (v0 != 0) {
        // 0x00580148
        charge(ctx, 6);
        jal(ctx, 0x580148u, gen::fn_sub_57FC60_0057fc60);
        a0 = 0x7D0000;
        a0 = addiu(a0, -30536);  // "E20010703G mwPlySfdStart: "
        jal(ctx, 0x580154u, gen::fn_sub_585590_00585590);
        v0 = si(-307);
    }
    // 0x00580160 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00580270 sub_580270 -- 248 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mw_sfd_start_ex] MWSFD: (re)starts a player's decode. With an SFD handle: resets it (sub_57D518, 'RESET failed'),
// resets the audio slave (sub_585050), runs the AddInf SJ's reset method, re-attaches it to SFD ('can't set
// AddInfSJ'), clears the AddInf record and the header ring; then clears the frame counters, stands SFD by, re-applies
// the pause byte, pauses and starts the audio slave, clears +132 / +680, sets the status to 1 (preparing) and the
// 'term requested' byte +113 to 0. Returns 1.
void sub_580270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580270
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = addiu(s0, 640);
    jal(ctx, 0x580284u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, s0, ply::kSfd);
    a0 = s0;
    if (v0 != 0) {
        // 0x00580298
        charge(ctx, 4);
        jal(ctx, 0x580298u, gen::fn_sub_57D518_0057d518);
        ld(ra, sp, 0x10);
        if (v0 != 0) {
            // 0x005802a8
            charge(ctx, 6);
            a0 = 0x7D0000;
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = addiu(a0, -30456);  // "E0203263: mw_sfd_start_ex: RESET failed."
            sp = addiu(sp, 0x20);
            gen::fn_sub_585590_00585590(ctx);  // tail call
            return;
        }
        // 0x005802c0
        charge(ctx, 8);
        a0 = s0;
        jal(ctx, 0x5802C0u, gen::fn_sub_585050_00585050);
        a0 = s0;
        jal(ctx, 0x5802C8u, gen::fn_sub_583520_00583520);
        a0 = s0;
        jal(ctx, 0x5802D0u, gen::fn_sub_5834A0_005834a0);
        a0 = s0;
        if (v0 == 0) {
            // 0x00580300
            charge(ctx, 4);
            jal(ctx, 0x580300u, gen::fn_sub_583500_00583500);
            a0 = s0;
            jal(ctx, 0x580308u, gen::fn_sub_57F328_0057f328);
            goto L_00580310;
        }
        // 0x005802e0
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -30408);  // "E201213 mw_sfd_start_ex: can't set AddInfSJ"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
L_00580310:
    charge(ctx, 22);
    a0 = s0;
    jal(ctx, 0x580310u, gen::fn_sub_580368_00580368);
    a0 = s0;
    jal(ctx, 0x580318u, gen::fn_sub_5800F0_005800f0);
    a0 = s0;
    link(ctx, 0x580324u);  // $ra first: the delay slot below depends on it
    lb(a1, s0, ply::kPause);
    call(ctx, gen::fn_sub_580750_00580750);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x580330u, gen::fn_sub_584E08_00584e08);
    a0 = s1;
    jal(ctx, 0x580338u, gen::fn_sub_584C80_00584c80);
    sw(zero, s0, ply::kUnk132);
    v0 = 1;
    sw(zero, s0, ply::kUnk680);
    sw(v0, s0, ply::kStat);
    sb(zero, s0, ply::kTermReq);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00580368 sub_580368 -- 12 bytes; leaf frame (no stack)
// [mwPlyClearFrmCnt] MWSFD: clears a player's two frame counters (+124, +128).
void sub_580368(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00580368
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, ply::kFrmCnt1);
    sw(zero, a0, ply::kFrmCnt0);
}

// 0x00580378 sub_580378 -- 296 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [mwPlyStartFname] MWSFD: start playing a file: handle check, file name check ('fname is NULL'), the input SJ +444 =
// the file SJ +448, stop, start_ex, store the name (sub_580A28), then the empty start hook with (ply, 0, -1).
void sub_580378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580378
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00580390
    charge(ctx, 11);
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5803A4u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -30360);  // "E1122601: mwPlyStartFname: handle is invalid."
    if (v0 != v1) {
        // 0x005803bc
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005803d0
    charge(ctx, 2);
    a0 = s1;
    if (s0 == 0) {
        // 0x005803d8
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -30312);  // "E10915C: mwPlyStartFname: fname is NULL."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005803f8
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    a1 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    a2 = 0;
    a3 = si(-1);
    sp = addiu(sp, 0x20);
    // 0x00580418
    charge(ctx, 32);
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(ra, sp, 0x20);
    lw(v0, s0, 448);
    link(ctx, 0x580444u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 444);
    call(ctx, gen::fn_sub_580628_00580628);
    a0 = s0;
    jal(ctx, 0x58044Cu, gen::fn_sub_580270_00580270);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x580458u, gen::fn_sub_580A28_00580a28);
    a0 = s0;
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x580468u, gen::fn___env_lock_11_00581138);
    a0 = s0;
    a1 = s3;
    ld(s3, sp, 0x18);
    a2 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    // 0x00581140
    charge(ctx, 2);
}

// 0x00580628 sub_580628 -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwSfdStop] MWSFD: stops a player's decode. With an SFD handle: waits the decode server out (sub_586248), clears
// the status and the SFD handle while SFD stops (sub_597368; -308, 'can't stop SFD'), puts the handle back, stops the
// audio slave, clears +672, stops the ADXT file input (+64) and the loop-play list (+72).
void sub_580628(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580628
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(s1, s0, ply::kSfd);
    if (s1 == 0) {
        ld(s0, sp, 0x0);
        // 0x005806c0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00580648
    charge(ctx, 8);
    jal(ctx, 0x580648u, gen::fn_sub_586248_00586248);
    sw(zero, s0, ply::kStat);
    sw(zero, s0, ply::kSfd);
    a0 = s1;
    jal(ctx, 0x580658u, gen::fn_sub_597368_00597368);
    a0 = si(-308);
    if (v0 != 0) {
        // 0x00580668
        charge(ctx, 5);
        jal(ctx, 0x580668u, gen::fn_sub_57FC60_0057fc60);
        a0 = 0x7D0000;
        a0 = addiu(a0, -30088);  // "E2003 mwSfdStop:can't stop SFD"
        jal(ctx, 0x580674u, gen::fn_sub_585590_00585590);
    }
    // 0x0058067c
    charge(ctx, 7);
    sw(s1, s0, ply::kSfd);
    a0 = addiu(s0, 640);
    jal(ctx, 0x580680u, gen::fn_sub_584CD8_00584cd8);
    sw(zero, s0, ply::kSlaveIdx);
    lw(v0, s0, ply::kAdxt);
    a0 = v0;
    if (v0 != 0) {
        // 0x00580698
        charge(ctx, 2);
        jal(ctx, 0x580698u, gen::fn_R_LOCK_DEF_lock_free_4_005865c0);
    }
    // 0x005806a0
    charge(ctx, 3);
    lw(a0, s0, ply::kLsc);
    ld(s0, sp, 0x0);
    if (a0 == 0) {
        // 0x005806c0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005806ac
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55D668_0055d668(ctx);  // tail call
}

// 0x00580750 sub_580750 -- 292 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// [mwPlyPause] MWSFD: pause on / off. Handle check; when the pause byte +114 or the request is set: if the server is
// locked (sub_57FA98) and +8 is 1, waits the server out when SFD's condition 6 is set (or cannot be read); pauses SFD
// (sub_5957D8; -310, 'can't pause (ON / OFF)'), pauses the audio slave, stores the request in +114.
void sub_580750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00580750
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    s2 = a1;
    jal(ctx, 0x58076Cu, gen::fn_sub_581798_00581798);
    s1 = v0;
    v0 = 1;
    a0 = 0x7D0000;
    if (s1 == v0) {
        // 0x00580798
        charge(ctx, 3);
        lb(v0, s0, ply::kPause);
        lw(s3, s0, ply::kSfd);
        if (v0 == 0) {
            // 0x005807a4
            charge(ctx, 2);
            if (s2 != 0) {
                goto L_005807ac;
            }
            ld(s0, sp, 0x10);
            // 0x0058085c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x18);
            ld(s2, sp, 0x20);
            ld(s3, sp, 0x28);
            ld(ra, sp, 0x30);
            sp = addiu(sp, 0x40);
            return;
        }
    L_005807ac:
        charge(ctx, 4);
        jal(ctx, 0x5807ACu, gen::fn_sub_57FA98_0057fa98);
        a0 = s3;
        if (v0 == s1) {
            // 0x005807bc
            charge(ctx, 3);
            lw(s1, s0, ply::kCprm);
            if (s1 == v0) {
                // 0x005807c8
                charge(ctx, 5);
                a1 = 6;
                a2 = sp;
                jal(ctx, 0x5807CCu, gen::fn_sub_599368_00599368);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                lw(v0, sp, 0x0);
                if (cc) {
                    // 0x005807f8
                    charge(ctx, 3);
                    a0 = s0;
                    jal(ctx, 0x5807F8u, gen::fn_sub_586248_00586248);
                    a0 = s3;
                } else {
                    // 0x005807dc
                    charge(ctx, 2);
                    if (v0 != s1) {
                        a0 = s3;
                    } else {
                        // 0x005807e4
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x5807E4u, gen::fn_sub_586248_00586248);
                        a0 = s3;
                    }
                }
            }
        }
        // 0x00580804
        charge(ctx, 4);
        a1 = s2;
        jal(ctx, 0x580804u, gen::fn_sub_5957D8_005957d8);
        if (v0 == 0) {
            a0 = addiu(s0, 640);
        } else {
            // 0x00580814
            charge(ctx, 6);
            a0 = si(-310);
            jal(ctx, 0x580814u, gen::fn_sub_57FC60_0057fc60);
            v1 = 0x7D0000;
            v0 = 1;
            a0 = addiu(v1, -29976);  // "E2007 mwPlyPause; can't pause (%s)"
            if (s2 != v0) {
                // 0x00580838
                charge(ctx, 2);
                v0 = 0x7D0000;
                a1 = addiu(v0, -29928);  // "OFF"
            } else {
                // 0x0058082c
                charge(ctx, 3);
                v0 = 0x7D0000;
                a1 = addiu(v0, -29936);  // "ON"
            }
            // 0x00580840
            charge(ctx, 3);
            jal(ctx, 0x580840u, gen::fn_sub_585590_00585590);
            a0 = addiu(s0, 640);
        }
        // 0x0058084c
        charge(ctx, 4);
        a1 = s2;
        jal(ctx, 0x58084Cu, gen::fn_sub_584E08_00584e08);
        sb(s2, s0, ply::kPause);
        ld(s0, sp, 0x10);
    } else {
        // 0x00580784
        charge(ctx, 4);
        a0 = addiu(a0, -30016);
        jal(ctx, 0x580784u, gen::fn_sub_585590_00585590);
        ld(s0, sp, 0x10);
    }
    // 0x0058085c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00580900 sub_580900 -- 88 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10, s1 sp+0x8
// [mwPlySetReadSize] MWSFD: the ADXT input's read size from the player's +456 scaled by the double at 0x7C8B50
// (litodp / dpmul / dptoli), handed to sub_5816F0 with +456.
void sub_580900(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580900
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    sd(s1, sp, 0x8);
    lw(s1, s0, ply::kReadSize);
    a0 = s1;
    jal(ctx, 0x580918u, gen::fn_litodp_00531720);
    at = 0x7D0000;
    ld(a1, at, -29872);  // 0x7C8B50
    a0 = v0;
    jal(ctx, 0x580928u, gen::fn_dpmul_00531230);
    a0 = v0;
    jal(ctx, 0x580930u, gen::fn_dptoli_005317d0);
    a0 = s0;
    a2 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a1 = v0;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5816F0_005816f0(ctx);  // tail call
}

// 0x00580958 sub_580958 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyTermSupplyAtEof] MWSFD: when the ADXT file input (+64) reports status 3 (end of file), terminates SFD's input
// (sub_597968).
void sub_580958(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580958
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    lw(v0, a0, 64);
    lw(s0, a0, 60);
    a0 = v0;
    if (v0 == 0) {
        // 0x005809a0
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x005809a4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00580974
    charge(ctx, 5);
    jal(ctx, 0x580974u, gen::fn_sub_586610_00586610);
    v1 = 3;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x005809a4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00580988
    charge(ctx, 5);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_597968_00597968(ctx);  // tail call
}

// 0x005809B0 sub_5809B0 -- 120 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [mwPlySetFname] MWSFD: copies the file name into the buffer +420 (capacity +424): strcpy when it fits, else reports
// 'filename is longer.' and copies the capacity with strncpy (no terminator then).
void sub_5809B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005809b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x5809C8u, gen::fn_strlen_00524388);
    a0 = 0x7D0000;
    lw(v1, s0, ply::kFnameCap);
    a0 = addiu(a0, -29864);  // "E211121: filename is longer."
    v1 = slt(v1, v0);
    a1 = s1;
    if (v1 == 0) {
        // 0x00580a10
        charge(ctx, 6);
        lw(a0, s0, ply::kFname);
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_strcpy_00524270(ctx);  // tail call
        return;
    }
    // 0x005809e8
    charge(ctx, 10);
    jal(ctx, 0x5809E8u, gen::fn_sub_585590_00585590);
    lw(a2, s0, ply::kFnameCap);
    a1 = s1;
    ld(s1, sp, 0x8);
    lw(a0, s0, ply::kFname);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_strncpy_00524828(ctx);  // tail call
}

// 0x00580C80 sub_580C80 -- 60 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [mwsfdInitSprSwap] MWSFD: the scratchpad-swap settings: enabled (0x7B4528 = 1), no callback (0x7B452C), not swapped
// (0x7B4530), DMA rather than memcpy (0x7B4534 = 0). Returns 1.
void sub_580C80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580c80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00580e50
    charge(ctx, 10);
    a2 = 0x7B0000;
    v0 = 1;
    v1 = 0x7B0000;
    a0 = 0x7B0000;
    a1 = 0x7B0000;
    sw(v0, a2, 17704);  // 0x7B4528
    sw(zero, v1, 17708);  // 0x7B452C
    sw(zero, a0, 17712);  // 0x7B4530
    sw(zero, a1, 17716);  // 0x7B4534
}

// 0x00580CB0 sub_580CB0 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdSprSwapIn] MWSFD: swaps the scratchpad in, once (0x7B4530 = 1), when enabled: waits DMA channels 8 / 9, saves
// the scratchpad's 16 KiB to 0x99EDC0, loads 0x9A2DC0 into it, waiting each channel. Returns 0x7B0000 when disabled.
void sub_580CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580cb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    jal(ctx, 0x580CC0u, gen::fn_WTLS_get_table_0_00580df0);
    s0 = v0;
    v0 = 0x7B0000;
    v1 = 1;
    s1 = addiu(v0, 17712);  // &0x7B4530
    if (s0 == v1) {
        // 0x00580cdc
        charge(ctx, 3);
        lw(v0, s1, 0);
        if (v0 != s0) {
            // 0x00580ce8
            charge(ctx, 17);
            jal(ctx, 0x580CE8u, gen::fn_sub_580E78_00580e78);
            a2 = 0x9A0000;
            a2 = addiu(a2, -4672);  // &0x99EDC0
            a1 = 16384;
            a0 = 0;
            jal(ctx, 0x580CFCu, gen::fn_sub_580E98_00580e98);
            a0 = 8;
            jal(ctx, 0x580D04u, gen::fn_my_malloc_0_00581070);
            a0 = 0x9A0000;
            a0 = addiu(a0, 11712);  // &0x9A2DC0
            a1 = 16384;
            a2 = 0;
            jal(ctx, 0x580D18u, gen::fn_sub_580F78_00580f78);
            a0 = 9;
            jal(ctx, 0x580D20u, gen::fn_my_malloc_0_00581070);
            sw(s0, s1, 0);
            goto L_00580d2c;
        }
        ld(s0, sp, 0x0);
        // 0x00580d30 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00580d2c:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00580d30 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00580D40 sub_580D40 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSprSwapOut] MWSFD: swaps the scratchpad back (0x7B4530 = 0): saves it to 0x9A2DC0 and reloads 0x99EDC0.
void sub_580D40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580d40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x580D4Cu, gen::fn_WTLS_get_table_0_00580df0);
    v1 = 0x7B0000;
    a0 = 1;
    s0 = addiu(v1, 17712);  // &0x7B4530
    if (v0 == a0) {
        // 0x00580d64
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 != 0) {
            // 0x00580d70
            charge(ctx, 17);
            jal(ctx, 0x580D70u, gen::fn_sub_580E78_00580e78);
            a2 = 0x9A0000;
            a2 = addiu(a2, 11712);  // &0x9A2DC0
            a1 = 16384;
            a0 = 0;
            jal(ctx, 0x580D84u, gen::fn_sub_580E98_00580e98);
            a0 = 8;
            jal(ctx, 0x580D8Cu, gen::fn_my_malloc_0_00581070);
            a0 = 0x9A0000;
            a0 = addiu(a0, -4672);  // &0x99EDC0
            a1 = 16384;
            a2 = 0;
            jal(ctx, 0x580DA0u, gen::fn_sub_580F78_00580f78);
            a0 = 9;
            jal(ctx, 0x580DA8u, gen::fn_my_malloc_0_00581070);
            sw(zero, s0, 0);
            goto L_00580db4;
        }
        ld(s0, sp, 0x0);
        // 0x00580db8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00580db4:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00580db8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00580DF0 WTLS_get_table_0 -- 12 bytes; leaf frame (no stack)
// [mwsfdSprSwapEnabled] MWSFD: the scratchpad-swap enable word 0x7B4528 (FLIRT misname).
void WTLS_get_table_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00580df0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 17704);  // 0x7B4528
}

// 0x00580E10 sub_580E10 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdCallSprCb] MWSFD: calls the user callback 0x7B452C, when set, with (a0, the swap enable word).
void sub_580E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580e10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x580E1Cu, gen::fn_WTLS_get_table_0_00580df0);
    v1 = 0x7B0000;
    a1 = v0;
    lw(v0, v1, 17708);  // 0x7B452C
    a0 = s0;
    if (v0 != 0) {
        // 0x00580e38
        charge(ctx, 2);
        jalr(ctx, 0x580E38u, v0.u());
    }
    // 0x00580e40 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00580E78 sub_580E78 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdSprWait] MWSFD: waits for DMA channels 8 (fromSPR) and 9 (toSPR) (my_malloc_0 is the channel wait).
void sub_580E78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580e78
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 8;
    jal(ctx, 0x580E80u, gen::fn_my_malloc_0_00581070);
    ld(ra, sp, 0x0);
    a0 = 9;
    sp = addiu(sp, 0x10);
    gen::fn_my_malloc_0_00581070(ctx);  // tail call
}

// 0x00580E98 sub_580E98 -- 60 bytes; frame 0x10: ra sp+0x0
// [mwsfdSprToMem] MWSFD: scratchpad to memory: the memcpy path (sub_580ED8) when 0x7B4534 is set, else DMA
// (sub_580F10).
void sub_580E98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580e98
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 17716);  // 0x7B4534
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x00580ec0
        charge(ctx, 3);
        jal(ctx, 0x580EC0u, gen::fn_sub_580ED8_00580ed8);
        ld(ra, sp, 0x0);
    } else {
        // 0x00580eac
        charge(ctx, 4);
        jal(ctx, 0x580EACu, gen::fn_sub_580F10_00580f10);
        ld(ra, sp, 0x0);
    }
    // 0x00580ecc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00580F78 sub_580F78 -- 60 bytes; frame 0x10: ra sp+0x0
// [mwsfdMemToSpr] MWSFD: memory to scratchpad: memcpy (sub_580FB8) or DMA (sub_580FE8).
void sub_580F78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580f78
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 17716);  // 0x7B4534
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x00580fa0
        charge(ctx, 3);
        jal(ctx, 0x580FA0u, gen::fn_sub_580FB8_00580fb8);
        ld(ra, sp, 0x0);
    } else {
        // 0x00580f8c
        charge(ctx, 4);
        jal(ctx, 0x580F8Cu, gen::fn_sub_580FE8_00580fe8);
        ld(ra, sp, 0x0);
    }
    // 0x00580fac (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005810F0 sub_5810F0 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwPlyExecAdxSvr] MWSFD: thunk to sub_541008, the ADX server step (SVM lock, the ADX servers, unlock); the game's
// raster task calls it.
void sub_5810F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005810f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541008_00541008(ctx);  // tail call
}

// 0x00581108 sub_581108 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdSprIn] MWSFD: thunk to the scratchpad swap-in sub_580CB0.
void sub_581108(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00581108
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_580CB0_00580cb0(ctx);  // tail call
}

// 0x00581120 sub_581120 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdSprOut] MWSFD: thunk to the scratchpad swap-out sub_580D40.
void sub_581120(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00581120
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_580D40_00580d40(ctx);  // tail call
}

// 0x00581138 __env_lock_11 -- 8 bytes; leaf frame (no stack)
// [mwsfdStartHook] MWSFD: an empty hook mwPlyStartFname calls with (ply, 0, -1) (FLIRT misname).
void __env_lock_11(EEContext& ctx) {
    using namespace hg;
    // 0x00581138
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00581148 sub_581148 -- 8 bytes; leaf frame (no stack)
// [mwsfdSvrHook] MWSFD: an empty hook the per-player server step calls last.
void sub_581148(EEContext& ctx) {
    using namespace hg;
    // 0x00581148
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005811D0 sub_5811D0 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyGetSfdHn] MWSFD: the player's SFD handle (+60); 0 and 'handle is invalid' for a bad handle.
void sub_5811D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005811d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5811DCu, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -29624);  // "E1122640: mwPlyGetSfdHn: handle is invalid."
    if (v0 == v1) {
        // 0x00581208
        charge(ctx, 1);
        lw(v0, s0, ply::kSfd);
    } else {
        // 0x005811f4
        charge(ctx, 4);
        jal(ctx, 0x5811F4u, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x0058120c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00581690 sub_581690 -- 36 bytes; frame 0x10: ra sp+0x0
// [mwPlySetSfdPara] MWSFD: SFD set-parameter (sub_599100) on the player's SFD handle (0 for a null player: every
// handle).
void sub_581690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00581690
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005816a0
        charge(ctx, 1);
        lw(v0, a0, 60);
    }
    // 0x005816a4
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_sub_599100_00599100(ctx);  // tail call
}

// 0x005816F0 sub_5816F0 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwPlySetInputReadSize] MWSFD: hands a read size to the ADXT input (+64, sub_586428) and to the loop-play list
// (sub_5847D0).
void sub_5816F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005816f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    link(ctx, 0x581708u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, ply::kAdxt);
    call(ctx, gen::fn_sub_586428_00586428);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5847D0_005847d0(ctx);  // tail call
}

// 0x00581798 sub_581798 -- 20 bytes; leaf frame (no stack)
// [mwPlyIsValidHn] MWSFD: the handle check: the player's used word (+0; 1 = in use), 0 for a null pointer.
void sub_581798(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00581798
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
    if (a0 != 0) {
        // 0x005817a0
        charge(ctx, 1);
        lw(v0, a0, 0);
    }
    // 0x005817a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00581840 sub_581840 -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwPlyGetStat] MWSFD: player status. Bad handle: last error -12, 'mwPlyGetStat: handle is invalid', 0. Else the
// status (+4); while playing (2) it follows SFD's status: 1 (preparing) for 0..3 and 5, 2 (playing) for 4 and 6, 4
// (error) for a negative one.
void sub_581840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00581840
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x581850u, gen::fn_sub_581798_00581798);
    s1 = v0;
    v0 = 1;
    a0 = si(-12);
    a1 = 2;
    if (s1 != v0) {
        // 0x0058186c
        charge(ctx, 7);
        jal(ctx, 0x58186Cu, gen::fn_sub_57FC60_0057fc60);
        a0 = 0x7D0000;
        a0 = addiu(a0, -29032);  // "W2004 mwPlyGetStat: handle is invalid"
        jal(ctx, 0x581878u, gen::fn_sub_585590_00585590);
        v0 = 0;
        goto L_005818c4;
    }
    // 0x00581888
    charge(ctx, 3);
    lw(v1, s0, ply::kStat);
    v0 = v1;
    if (v1 == a1) {
        // 0x00581894
        charge(ctx, 9);
        link(ctx, 0x581894u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, ply::kSfd);
        call(ctx, gen::fn_sub_5990C0_005990c0);
        a2 = 6;
        a1 = v0;
        a0 = 4;
        v1 = slti(a1, 0);
        v0 = a0;
        if (v1 == 0) v0 = s1;
        if (a1 != a0) {
            // 0x005818b8
            charge(ctx, 2);
            ld(s0, sp, 0x0);
            if (a1 == a2) {
                goto L_005818c0;
            }
            // 0x005818c8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_005818c0:
        charge(ctx, 1);
        v0 = 2;
        goto L_005818c4;
    }
L_005818c4:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005818c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00582798 sub_582798 -- 60 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [mwsfdInitSfx] MWSFD: SFX init (sub_59F970) and the SFX hook record 0x7B4928 = {sub_5827C0, 0}; returns its
// address.
void sub_582798(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582798
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5827A0u, gen::fn_sub_59F970_0059f970);
    ld(ra, sp, 0x0);
    a0 = 0x580000;
    a0 = addiu(a0, 10176);  // &sub_5827C0
    a1 = 0;
    sp = addiu(sp, 0x10);
    // 0x0059fa90
    charge(ctx, 5);
    v0 = 0x7B0000;
    v0 = addiu(v0, 18728);  // &0x7B4928
    sw(a1, v0, 4);  // 0x7B492C
    sw(a0, v0, 0);  // 0x7B4928
}

// 0x005827F0 sub_5827F0 -- 8 bytes; leaf frame (no stack)
// [mwsfdGetSfxWorkSize] MWSFD: the SFX handle's work size, 6175 bytes.
void sub_5827F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005827f0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 6175;
}

// 0x005827F8 sub_5827F8 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdCreateSfx] MWSFD: thunk to SFX create (sub_59FAA8).
void sub_5827F8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005827f8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59FAA8_0059faa8(ctx);  // tail call
}

// 0x00582810 sub_582810 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdDestroySfx] MWSFD: thunk to SFX destroy (sub_59FCC0).
void sub_582810(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00582810
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59FCC0_0059fcc0(ctx);  // tail call
}

// 0x00582828 sub_582828 -- 8 bytes; leaf frame (no stack)
// [mwPlyGetSfxHn] MWSFD: the player's SFX handle (+168).
void sub_582828(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00582828
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, ply::kSfx);
}

// 0x00583028 sub_583028 -- 52 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlySetSfxCompo] MWSFD: stores a2 in the player's SFX handle +4 (the composition mode).
void sub_583028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583028
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x583034u, gen::fn_sub_582828_00582828);
    ld(ra, sp, 0x8);
    a1 = s0;
    ld(s0, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    // 0x0059fdb0
    charge(ctx, 2);
    sw(a1, a0, 4);
}

// 0x005833D8 sub_5833D8 -- 16 bytes; leaf frame (no stack)
// [mwPlyIsCprmMode2] MWSFD: true when the creation parameter's first word (player +8) is 2.
void sub_5833D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005833d8
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, ply::kCprm);
    v0 = v0 ^ 0x2;
    v0 = sltiu(v0, 1);
}

// 0x005833E8 sub_5833E8 -- 36 bytes; leaf frame (no stack)
// [mwsfdNeedAddInfSj] MWSFD: true when a creation parameter block's +32 word is 0 or 257 (an AddInf SJ is wanted).
void sub_5833E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005833e8
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, 32);
    a0 = 1;
    if (v1 != 0) {
        // 0x005833f4
        charge(ctx, 3);
        v0 = 257;
        a0 = 0;
        if (v1 == v0) {
            // 0x00583400
            charge(ctx, 1);
            a0 = 1;
        }
    }
    // 0x00583404 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x00583410 sub_583410 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyCreateAddInfSj] MWSFD: creates the AddInf SJ when wanted (sub_562388 on the buffer +384 / +388); on failure
// reports 'mwPlyCreate: can't create AddInfSJ' and destroys the player. Returns the SJ or 0.
void sub_583410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583410
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a0 = addiu(s0, 8);
    jal(ctx, 0x583420u, gen::fn_sub_5833E8_005833e8);
    v1 = 1;
    a2 = 0;
    if (v0 == v1) {
        // 0x00583434
        charge(ctx, 6);
        lw(a0, s0, ply::kAddInfBuf);
        link(ctx, 0x583438u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, ply::kAddInfBufSize);
        call(ctx, gen::fn_sub_562388_00562388);
        a0 = 0x7D0000;
        a0 = addiu(a0, -27072);  // "E201211 mwPlyCreate: can't create AddInfSJ"
        if (v0 == 0) {
            // 0x0058344c
            charge(ctx, 4);
            jal(ctx, 0x58344Cu, gen::fn_sub_585590_00585590);
            a0 = s0;
            jal(ctx, 0x583454u, gen::fn_sub_57DB58_0057db58);
            goto L_0058345c;
        }
        // 0x00583460 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058345c:
    charge(ctx, 1);
    v0 = 0;
    // 0x00583460 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00583470 sub_583470 -- 48 bytes; frame 0x10: ra sp+0x0
// [mwPlyDestroyAddInfSj] MWSFD: destroys the AddInf SJ (+380) through its method table (+12).
void sub_583470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583470
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 380);
    a0 = v0;
    if (v0 != 0) {
        // 0x00583484
        charge(ctx, 4);
        lw(v0, v0, 0);
        lw(v1, v0, 12);
        jalr(ctx, 0x58348Cu, v1.u());
    }
    // 0x00583494 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005834A0 sub_5834A0 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyAttachAddInfSj] MWSFD: attaches the AddInf SJ (+380) to SFD as stream 2 (sub_59C8E0) unless the creation mode
// is 2; -1 on failure, else 0.
void sub_5834A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005834a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5834ACu, gen::fn_sub_5833D8_005833d8);
    v1 = 1;
    if (v0 != v1) {
        lw(v1, s0, ply::kAddInfSj);
        // 0x005834c8
        charge(ctx, 3);
        v0 = 0;
        a2 = v1;
        if (v1 != 0) {
            // 0x005834d4
            charge(ctx, 7);
            lw(a0, s0, ply::kSfd);
            a1 = 2;
            a3 = 0;
            jal(ctx, 0x5834DCu, gen::fn_sub_59C8E0_0059c8e0);
            v1 = si(-1);
            if (v0 == 0) v1 = 0;
            v0 = v1;
        }
    } else {
        // 0x005834c0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x005834f0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00583500 sub_583500 -- 28 bytes; leaf frame (no stack)
// [mwPlyResetAddInf] MWSFD: resets the AddInf record (+400 = -1, +404 / +408 / +412 = 0).
void sub_583500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00583500
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = addiu(a0, 404);
    v1 = si(-1);
    sw(zero, v0, 8);
    sw(zero, v0, 0);
    sw(zero, v0, 4);
    sw(v1, a0, ply::kAddInfIdx);
}

// 0x00583520 sub_583520 -- 48 bytes; frame 0x10: ra sp+0x0
// [mwPlyResetAddInfSj] MWSFD: resets the AddInf SJ (+380) through its method table (+20).
void sub_583520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583520
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 380);
    a0 = v0;
    if (v0 != 0) {
        // 0x00583534
        charge(ctx, 4);
        lw(v0, v0, 0);
        lw(v1, v0, 20);
        jalr(ctx, 0x58353Cu, v1.u());
    }
    // 0x00583544 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005835A8 sub_5835A8 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyScanAddInf] MWSFD: with an AddInf SJ, scans it for the CRITAGS block (sub_5835F0) and the SFXINF block
// (sub_5837A0).
void sub_5835A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005835a8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, ply::kAddInfSj);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x005835e0
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005835c4
    charge(ctx, 7);
    jal(ctx, 0x5835C4u, gen::fn_sub_5835F0_005835f0);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5837A0_005837a0(ctx);  // tail call
}

}  // namespace p3fes::game
