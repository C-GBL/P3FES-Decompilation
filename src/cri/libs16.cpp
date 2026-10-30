// Phase 5 slice libs16: CRI Sofdec, 0x5886B8-0x598D20 (100 functions) -- the SFD method-table stubs and error
// raisers, the stream-kind probe (system / audio headers through temporary MPS handles), the SFD finish, the audio
// clock ring and the system-stream server's clock step, the picture time and time-code checks, the late / skip
// decisions, start-code skipping on the SJ, the frame-ready queries, the sceMpeg end-of-stream callback, step-play
// frame take / release, the 16-byte entry ring and the timing record (source selection, muldiv getters).
// Written from p3fes_handgen bodies: each keeps the recompiled body's registers, frame, spills, $ra links, cycle
// charges and check points (hg_cpu.h); the readability layer is the role comments and the named offsets of the SFD
// handle and video-decoder work (libs13.h). Pair tests: tests/game/test_libs16.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs16.h"
#include "p3fes/game/libs13.h"  // the SFD handle and video-decoder offsets (sfd::, vdec::, frm::)

namespace p3fes::recomp_gen {
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___env_unlock_11_0058c0f8(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn_cosl_12_0058c0a0(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_my_malloc_1_00597448(p3fes::EEContext&);
void fn_r_lock_def_free_6_0058c380(p3fes::EEContext&);
void fn_sceMpegGetPictureAbort_00500ba8(p3fes::EEContext&);
void fn_sub_562308_00562308(p3fes::EEContext&);
void fn_sub_56F4B8_0056f4b8(p3fes::EEContext&);
void fn_sub_575410_00575410(p3fes::EEContext&);
void fn_sub_575880_00575880(p3fes::EEContext&);
void fn_sub_575AA0_00575aa0(p3fes::EEContext&);
void fn_sub_5777F8_005777f8(p3fes::EEContext&);
void fn_sub_577B40_00577b40(p3fes::EEContext&);
void fn_sub_577DD8_00577dd8(p3fes::EEContext&);
void fn_sub_577F78_00577f78(p3fes::EEContext&);
void fn_sub_578378_00578378(p3fes::EEContext&);
void fn_sub_578820_00578820(p3fes::EEContext&);
void fn_sub_579368_00579368(p3fes::EEContext&);
void fn_sub_5796D0_005796d0(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_5886B8_005886b8(p3fes::EEContext&);
void fn_sub_5886D8_005886d8(p3fes::EEContext&);
void fn_sub_5886F8_005886f8(p3fes::EEContext&);
void fn_sub_588718_00588718(p3fes::EEContext&);
void fn_sub_588738_00588738(p3fes::EEContext&);
void fn_sub_589000_00589000(p3fes::EEContext&);
void fn_sub_589018_00589018(p3fes::EEContext&);
void fn_sub_5890D8_005890d8(p3fes::EEContext&);
void fn_sub_5890F0_005890f0(p3fes::EEContext&);
void fn_sub_589258_00589258(p3fes::EEContext&);
void fn_sub_5892E8_005892e8(p3fes::EEContext&);
void fn_sub_589F00_00589f00(p3fes::EEContext&);
void fn_sub_58A080_0058a080(p3fes::EEContext&);
void fn_sub_58A1C0_0058a1c0(p3fes::EEContext&);
void fn_sub_58A3E8_0058a3e8(p3fes::EEContext&);
void fn_sub_58A488_0058a488(p3fes::EEContext&);
void fn_sub_58A538_0058a538(p3fes::EEContext&);
void fn_sub_58A598_0058a598(p3fes::EEContext&);
void fn_sub_58A5A0_0058a5a0(p3fes::EEContext&);
void fn_sub_58A658_0058a658(p3fes::EEContext&);
void fn_sub_58A740_0058a740(p3fes::EEContext&);
void fn_sub_58A7D8_0058a7d8(p3fes::EEContext&);
void fn_sub_58A8C8_0058a8c8(p3fes::EEContext&);
void fn_sub_58A918_0058a918(p3fes::EEContext&);
void fn_sub_58AA20_0058aa20(p3fes::EEContext&);
void fn_sub_58AA88_0058aa88(p3fes::EEContext&);
void fn_sub_58AB08_0058ab08(p3fes::EEContext&);
void fn_sub_58ADA8_0058ada8(p3fes::EEContext&);
void fn_sub_58AFA0_0058afa0(p3fes::EEContext&);
void fn_sub_58B128_0058b128(p3fes::EEContext&);
void fn_sub_58B140_0058b140(p3fes::EEContext&);
void fn_sub_58B278_0058b278(p3fes::EEContext&);
void fn_sub_58B398_0058b398_at_0058b3d8(p3fes::EEContext&);
void fn_sub_58B4A8_0058b4a8(p3fes::EEContext&);
void fn_sub_58B510_0058b510(p3fes::EEContext&);
void fn_sub_58B560_0058b560(p3fes::EEContext&);
void fn_sub_58BB80_0058bb80(p3fes::EEContext&);
void fn_sub_58BBB0_0058bbb0(p3fes::EEContext&);
void fn_sub_58BD68_0058bd68(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C0D8_0058c0d8(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_58C198_0058c198(p3fes::EEContext&);
void fn_sub_58C1B8_0058c1b8(p3fes::EEContext&);
void fn_sub_58C1E0_0058c1e0(p3fes::EEContext&);
void fn_sub_58C200_0058c200(p3fes::EEContext&);
void fn_sub_58C220_0058c220(p3fes::EEContext&);
void fn_sub_58DF90_0058df90(p3fes::EEContext&);
void fn_sub_58E010_0058e010(p3fes::EEContext&);
void fn_sub_58E018_0058e018(p3fes::EEContext&);
void fn_sub_58E020_0058e020(p3fes::EEContext&);
void fn_sub_58E028_0058e028(p3fes::EEContext&);
void fn_sub_58E030_0058e030(p3fes::EEContext&);
void fn_sub_58E050_0058e050(p3fes::EEContext&);
void fn_sub_58E070_0058e070(p3fes::EEContext&);
void fn_sub_58E090_0058e090(p3fes::EEContext&);
void fn_sub_58E0B0_0058e0b0(p3fes::EEContext&);
void fn_sub_58E158_0058e158(p3fes::EEContext&);
void fn_sub_58E160_0058e160(p3fes::EEContext&);
void fn_sub_58E200_0058e200(p3fes::EEContext&);
void fn_sub_58E4A0_0058e4a0(p3fes::EEContext&);
void fn_sub_58E6E8_0058e6e8(p3fes::EEContext&);
void fn_sub_58F548_0058f548(p3fes::EEContext&);
void fn_sub_58FC30_0058fc30(p3fes::EEContext&);
void fn_sub_58FD00_0058fd00(p3fes::EEContext&);
void fn_sub_58FD60_0058fd60(p3fes::EEContext&);
void fn_sub_590430_00590430(p3fes::EEContext&);
void fn_sub_5905B0_005905b0(p3fes::EEContext&);
void fn_sub_590878_00590878(p3fes::EEContext&);
void fn_sub_590A28_00590a28(p3fes::EEContext&);
void fn_sub_590DF8_00590df8(p3fes::EEContext&);
void fn_sub_591700_00591700(p3fes::EEContext&);
void fn_sub_591808_00591808(p3fes::EEContext&);
void fn_sub_5918A8_005918a8(p3fes::EEContext&);
void fn_sub_591988_00591988(p3fes::EEContext&);
void fn_sub_591B00_00591b00(p3fes::EEContext&);
void fn_sub_591C08_00591c08(p3fes::EEContext&);
void fn_sub_5927D8_005927d8(p3fes::EEContext&);
void fn_sub_592938_00592938(p3fes::EEContext&);
void fn_sub_592EF8_00592ef8(p3fes::EEContext&);
void fn_sub_593608_00593608(p3fes::EEContext&);
void fn_sub_593700_00593700(p3fes::EEContext&);
void fn_sub_5938C0_005938c0(p3fes::EEContext&);
void fn_sub_593948_00593948(p3fes::EEContext&);
void fn_sub_593978_00593978(p3fes::EEContext&);
void fn_sub_593AA0_00593aa0(p3fes::EEContext&);
void fn_sub_593AC8_00593ac8(p3fes::EEContext&);
void fn_sub_593B10_00593b10(p3fes::EEContext&);
void fn_sub_593BF8_00593bf8(p3fes::EEContext&);
void fn_sub_593C58_00593c58(p3fes::EEContext&);
void fn_sub_593CE8_00593ce8(p3fes::EEContext&);
void fn_sub_593E08_00593e08(p3fes::EEContext&);
void fn_sub_593EA0_00593ea0(p3fes::EEContext&);
void fn_sub_593FD0_00593fd0(p3fes::EEContext&);
void fn_sub_5944A8_005944a8(p3fes::EEContext&);
void fn_sub_594B18_00594b18(p3fes::EEContext&);
void fn_sub_594B78_00594b78(p3fes::EEContext&);
void fn_sub_594E50_00594e50(p3fes::EEContext&);
void fn_sub_594E60_00594e60(p3fes::EEContext&);
void fn_sub_594EC8_00594ec8(p3fes::EEContext&);
void fn_sub_594F68_00594f68(p3fes::EEContext&);
void fn_sub_5954D8_005954d8(p3fes::EEContext&);
void fn_sub_595788_00595788(p3fes::EEContext&);
void fn_sub_5958F8_005958f8(p3fes::EEContext&);
void fn_sub_595A50_00595a50(p3fes::EEContext&);
void fn_sub_595AC0_00595ac0(p3fes::EEContext&);
void fn_sub_596340_00596340(p3fes::EEContext&);
void fn_sub_5965E0_005965e0(p3fes::EEContext&);
void fn_sub_5966C0_005966c0(p3fes::EEContext&);
void fn_sub_596760_00596760(p3fes::EEContext&);
void fn_sub_596818_00596818(p3fes::EEContext&);
void fn_sub_596B28_00596b28(p3fes::EEContext&);
void fn_sub_597168_00597168(p3fes::EEContext&);
void fn_sub_5971E8_005971e8(p3fes::EEContext&);
void fn_sub_597A18_00597a18(p3fes::EEContext&);
void fn_sub_597B88_00597b88(p3fes::EEContext&);
void fn_sub_597DC8_00597dc8(p3fes::EEContext&);
void fn_sub_597E98_00597e98(p3fes::EEContext&);
void fn_sub_597F20_00597f20(p3fes::EEContext&);
void fn_sub_598030_00598030(p3fes::EEContext&);
void fn_sub_598140_00598140(p3fes::EEContext&);
void fn_sub_5981D8_005981d8(p3fes::EEContext&);
void fn_sub_598348_00598348(p3fes::EEContext&);
void fn_sub_5983B8_005983b8(p3fes::EEContext&);
void fn_sub_598470_00598470(p3fes::EEContext&);
void fn_sub_598688_00598688(p3fes::EEContext&);
void fn_sub_5987F0_005987f0(p3fes::EEContext&);
void fn_sub_598870_00598870(p3fes::EEContext&);
void fn_sub_5988F0_005988f0(p3fes::EEContext&);
void fn_sub_598A90_00598a90(p3fes::EEContext&);
void fn_sub_598B90_00598b90(p3fes::EEContext&);
void fn_sub_598D20_00598d20(p3fes::EEContext&);
void fn_sub_599020_00599020(p3fes::EEContext&);
void fn_sub_599100_00599100(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599808_00599808(p3fes::EEContext&);
void fn_sub_599A30_00599a30(p3fes::EEContext&);
void fn_sub_599AA0_00599aa0(p3fes::EEContext&);
void fn_sub_599B40_00599b40(p3fes::EEContext&);
void fn_sub_59A168_0059a168(p3fes::EEContext&);
void fn_sub_59A560_0059a560(p3fes::EEContext&);
void fn_sub_59A870_0059a870(p3fes::EEContext&);
void fn_sub_59AC28_0059ac28(p3fes::EEContext&);
void fn_sub_59AEC0_0059aec0(p3fes::EEContext&);
void fn_sub_59B3A0_0059b3a0(p3fes::EEContext&);
void fn_sub_59B3A8_0059b3a8(p3fes::EEContext&);
void fn_sub_59B4F0_0059b4f0_at_0059b588(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59BCD0_0059bcd0(p3fes::EEContext&);
void fn_thread_leave_1_00597aa0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace sfd = ::p3fes::game::libs13::sfd;
namespace vdec = ::p3fes::game::libs13::vdec;

// 0x005886B8 sub_5886B8 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000A01 on the handle (sub_58BE40, tail call): an unsupported-call slot of a method table.
void sub_5886B8(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005886b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xA01;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x005886D8 sub_5886D8 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000A01 on the handle (sub_58BE40, tail call): a second slot of the same table.
void sub_5886D8(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005886d8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xA01;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x005886F8 sub_5886F8 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000A01 on the handle (sub_58BE40, tail call): a third slot of the same table.
void sub_5886F8(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005886f8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xA01;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00588718 sub_588718 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_588718(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00588718
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00588738 sub_588738 -- 8 bytes; leaf frame (no stack)
// Does nothing (called by the SFD finish, sub_58BD68, with the global 0x7B472C).
void sub_588738(EEContext& ctx) {
    using namespace hg;
    // 0x00588738
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00589258 sub_589258 -- 140 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// Drops a remembered chunk ({ptr, len} at +24) when it lies in neither part of the SJ's current two-part
//   chunk (sub_5892E8 on the SJ at +4, lane 1): both words cleared.
void sub_589258(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589258
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a0;
    sd(s0, sp, 0x20);
    s0 = addiu(v0, 24);
    sd(ra, sp, 0x28);
    a1 = 1;
    a2 = sp;
    a3 = addiu(sp, 0x10);
    link(ctx, 0x589278u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 4);
    call(ctx, gen::fn_sub_5892E8_005892e8);
    lw(v1, s0, 0);
    lw(a0, sp, 0x0);
    v0 = sltu(v1, a0);
    if (v0 != 0) {
        lw(a0, sp, 0x10);
    } else {
        // 0x00589294
        charge(ctx, 5);
        lw(v0, sp, 0x4);
        v0 = addu(a0, v0);
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x005892a8
            charge(ctx, 1);
            lw(a0, sp, 0x10);
            goto L_005892ac;
        }
        ld(s0, sp, 0x20);
        // 0x005892d8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_005892ac:
    charge(ctx, 3);
    v0 = sltu(v1, a0);
    if (v0 != 0) {
        sw(zero, s0, 4);
    } else {
        // 0x005892b8
        charge(ctx, 5);
        lw(v0, sp, 0x14);
        v0 = addu(a0, v0);
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x005892cc
            charge(ctx, 1);
            sw(zero, s0, 4);
            goto L_005892d0;
        }
        ld(s0, sp, 0x20);
        // 0x005892d8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_005892d0:
    charge(ctx, 2);
    sw(zero, s0, 0);
    ld(s0, sp, 0x20);
    // 0x005892d8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00589F00 sub_589F00 -- 52 bytes; frame 0x10: ra sp+0x0
// Whether an object's method +16 (through its vtable, jalr) returns the global 0x9A6EF4.
void sub_589F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589f00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 0);
    lw(v0, v1, 16);
    jalr(ctx, 0x589F10u, v0.u());
    v1 = 0x9A0000;
    lw(a0, v1, 28404);  // 0x9A6EF4
    ld(ra, sp, 0x0);
    v0 = v0 ^ a0;
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x0058A080 sub_58A080 -- 136 bytes; frame 0x30: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, ra sp+0x28
// Under the lock (sub_58C100 / sub_58C118): adds n to the running total (+3376+356), stores the total in the
//   32-slot ring at +3740 at the next index (+3376+360, modulo 32) and advances the index.
void sub_58A080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a080
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s0, sp, 0x10);
    s0 = addiu(s2, sfd::kTimeRec);
    a0 = sp;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x28);
    s1 = a1;
    jal(ctx, 0x58A0A0u, gen::fn_sub_58C100_0058c100);
    lw(a2, s0, 356);
    lw(v1, s0, 360);
    a0 = sp;
    a2 = addu(a2, s1);
    v1 = addiu(v1, 1);
    sw(a2, s0, 356);
    a3 = addiu(v1, 31);
    a1 = slti(v1, 0);
    v0 = v1;
    if (a1 != 0) v0 = a3;
    v0 = sra(v0, 5);
    v0 = sll(v0, 5);
    v0 = subu(v1, v0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s2);
    sw(a2, v0, 3740);
    link(ctx, 0x58A0E8u);  // $ra first: the delay slot below depends on it
    sw(v1, s0, 360);
    call(ctx, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058A1C0 sub_58A1C0 -- 204 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// Under the lock: when the ring at +3884 has entries (written +3376+500 > read +3376+504), *out1 = the entry at
//   the read index (modulo 32), *out2 = +3376+492, the read index advances and the result is 1; else *out1 = -1, 0.
void sub_58A1C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a1c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s0, sp, 0x10);
    s0 = addiu(s2, sfd::kTimeRec);
    a0 = sp;
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    s1 = a2;
    jal(ctx, 0x58A1ECu, gen::fn_sub_58C100_0058c100);
    lw(v1, s0, 504);
    lw(v0, s0, 500);
    v0 = subu(v0, v1);
    a0 = sp;
    if (i64(v0) > 0) {
        // 0x0058a218
        charge(ctx, 18);
        lw(v0, s0, 492);
        s4 = 1;
        sw(v0, s1, 0);
        lw(v1, s0, 504);
        a1 = slti(v1, 0);
        a2 = addiu(v1, 31);
        v0 = v1;
        if (a1 != 0) v0 = a2;
        v0 = sra(v0, 5);
        v0 = sll(v0, 5);
        v1 = subu(v1, v0);
        v1 = sll(v1, 2);
        v1 = addu(v1, s2);
        lw(a1, v1, 3884);
        sw(a1, s3, 0);
        lw(v0, s0, 504);
        v0 = addiu(v0, 1);
        sw(v0, s0, 504);
    } else {
        // 0x0058a208
        charge(ctx, 4);
        v0 = si(-1);
        s4 = 0;
        sw(v0, s3, 0);
    }
    // 0x0058a260
    charge(ctx, 11);
    jal(ctx, 0x58A260u, gen::fn_sub_58C118_0058c118);
    v0 = s4;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058A3E8 sub_58A3E8 -- 160 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Under the lock: probes a buffer for its stream kind (sub_58A488) into the 64-byte result, then sets byte 0
//   when word +8 or +12 is set or +16 is -1, and byte 1 when +8 or +12 is set.
void sub_58A3E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058a3e8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(ra, sp, 0x28);
    a0 = sp;
    jal(ctx, 0x58A408u, gen::fn_sub_58C100_0058c100);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x58A418u, gen::fn_sub_58A488_0058a488);
    lw(a1, s2, 8);
    a0 = sp;
    if (a1 == 0) {
        // 0x0058a42c
        charge(ctx, 3);
        lw(v0, s2, 12);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
        L_0058a44c:
            charge(ctx, 1);
            sb(v0, s2, 0);
        } else {
            // 0x0058a438
            charge(ctx, 4);
            lw(v1, s2, 16);
            v0 = si(-1);
            if (v1 == v0) {
                goto L_0058a448;
            }
        }
        goto L_0058a450;
    }
L_0058a448:
    charge(ctx, 1);
    v0 = 1;
    goto L_0058a44c;
L_0058a450:
    charge(ctx, 2);
    v0 = 1;
    if (a1 == 0) {
        // 0x0058a458
        charge(ctx, 3);
        lw(v0, s2, 12);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            goto L_0058a464;
        }
        goto L_0058a468;
    }
L_0058a464:
    charge(ctx, 1);
    sb(v0, s2, 1);
L_0058a468:
    charge(ctx, 8);
    jal(ctx, 0x58A468u, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058A488 sub_58A488 -- 176 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Stream-kind probe chain: clears the result (sub_58A538), then tries each prober in turn (sub_58A598,
//   sub_58A5A0, sub_58AFA0, sub_58AB08, sub_58ADA8) until one returns non-zero.
void sub_58A488(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a488
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x18);
    a0 = s0;
    jal(ctx, 0x58A4A8u, gen::fn_sub_58A538_0058a538);
    a0 = s1;
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x58A4B8u, gen::fn_sub_58A598_0058a598);
    a0 = s1;
    a1 = s2;
    a2 = s0;
    if (v0 == 0) {
        // 0x0058a4d0
        charge(ctx, 4);
        jal(ctx, 0x58A4D0u, gen::fn_sub_58A5A0_0058a5a0);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0058a4e0
            charge(ctx, 8);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x58A4E8u, gen::fn_sub_58AFA0_0058afa0);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            if (v0 != 0) {
                goto L_0058a520;
            }
            // 0x0058a500
            charge(ctx, 4);
            jal(ctx, 0x58A500u, gen::fn_sub_58AB08_0058ab08);
            if (v0 == 0) {
                // 0x0058a510
                charge(ctx, 4);
                a0 = s1;
                a1 = s2;
                a2 = s0;
                jal(ctx, 0x58A518u, gen::fn_sub_58ADA8_0058ada8);
                goto L_0058a520;
            }
            ld(s0, sp, 0x0);
        }
        // 0x0058a524 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0058a520:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058a524 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058A538 sub_58A538 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Clears a 64-byte probe result (memset) and then its bytes 0, 1, 40 and words 4..36, 44 one by one.
void sub_58A538(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a538
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    a2 = 64;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58A54Cu, gen::fn_memset_00521408);
    sb(zero, s0, 0);
    sw(zero, s0, 44);
    sb(zero, s0, 1);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(zero, s0, 16);
    sw(zero, s0, 20);
    sw(zero, s0, 24);
    sw(zero, s0, 28);
    sw(zero, s0, 32);
    sw(zero, s0, 36);
    sb(zero, s0, 40);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0058A598 sub_58A598 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a prober that never matches).
void sub_58A598(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058a598
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058A5A0 sub_58A5A0 -- 184 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// The system-stream prober: three pack headers (0x1BA) at a regular spacing (sub_58A658) give the pack size
//   (+16); -1 means no match. On a match: +28 = 50 x the pack's mux rate when positive, +4 = 0x7C9FE8, then the
//   Sofdec header (sub_58A7D8), the video (sub_58A918) and the marker (sub_58AFA0) probes; returns 1.
void sub_58A5A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a5a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a2;
    a2 = sp;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(ra, sp, 0x28);
    s1 = a0;
    jal(ctx, 0x58A5C0u, gen::fn_sub_58A658_0058a658);
    v1 = v0;
    a0 = si(-1);
    if (v1 != 0) {
        // 0x0058a5d4
        charge(ctx, 3);
        sw(v1, s0, 16);
        v0 = 1;
        if (v1 != a0) {
            // 0x0058a5e0
            charge(ctx, 3);
            lw(v1, sp, 0x0);
            v0 = sll(v1, 1);
            if (i64(v1) > 0) {
                // 0x0058a5ec
                charge(ctx, 5);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                sw(v0, s0, 28);
            }
            // 0x0058a600
            charge(ctx, 16);
            v0 = 0x7D0000;
            a0 = s1;
            v0 = addiu(v0, -24600);  // &0x7C9FE8
            a1 = s2;
            sw(v0, s0, 4);
            a2 = s0;
            jal(ctx, 0x58A614u, gen::fn_sub_58A7D8_0058a7d8);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x58A624u, gen::fn_sub_58A918_0058a918);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x58A634u, gen::fn_sub_58AFA0_0058afa0);
            v0 = 1;
        }
    }
    // 0x0058a640 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058A658 sub_58A658 -- 232 bytes; frame 0x40: s6 sp+0x30, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s0 sp+0x0, ra sp+0x38
// Finds three consecutive pack headers (sub_58AA20, class 0x10000); when the two gaps are equal and divide
//   the first offset, reads the pack's mux rate (sub_58A740) and returns the gap; -1 for unequal gaps, 0 when one
//   is missing.
void sub_58A658(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a658
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s6, sp, 0x30);
    s6 = a2;
    sd(s1, sp, 0x8);
    a2 = 0x10000;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = a1;
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x38);
    link(ctx, 0x58A68Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s6, 0);
    call(ctx, gen::fn_sub_58AA20_0058aa20);
    a2 = 0x10000;
    s1 = v0;
    s2 = subu(s1, s3);
    a0 = addiu(s1, 1);
    s5 = subu(s4, s2);
    if (s1 != 0) {
        // 0x0058a6ac
        charge(ctx, 8);
        a1 = addiu(s5, -1);
        jal(ctx, 0x58A6ACu, gen::fn_sub_58AA20_0058aa20);
        a2 = 0x10000;
        s0 = v0;
        v1 = subu(s0, s3);
        a0 = addiu(s0, 1);
        a1 = subu(s4, v1);
        if (s0 == 0) {
            goto L_0058a718;
        }
        // 0x0058a6cc
        charge(ctx, 5);
        a1 = addiu(a1, -1);
        jal(ctx, 0x58A6CCu, gen::fn_sub_58AA20_0058aa20);
        v1 = v0;
        a0 = subu(v1, s0);
        if (v1 == 0) {
            goto L_0058a718;
        }
        // 0x0058a6e0
        charge(ctx, 3);
        s0 = subu(s0, s1);
        v0 = si(-1);
        if (s0 != a0) {
            goto L_0058a718;
        }
        // 0x0058a6ec
        charge(ctx, 3);
        div(s2, s0);
        if (s0 == 0) {
            brk(ctx, 0x58A6F4u, 0x7u);
        }
        // 0x0058a6f8
        charge(ctx, 3);
        mfhi(v1);
        if (v1 == 0) {
            // 0x0058a704
            charge(ctx, 5);
            a0 = s1;
            a1 = s5;
            a2 = s6;
            jal(ctx, 0x58A70Cu, gen::fn_sub_58A740_0058a740);
            v0 = s0;
            goto L_0058a718;
        }
        ld(s0, sp, 0x0);
        // 0x0058a71c (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058a718:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058a71c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058A740 sub_58A740 -- 152 bytes; frame 0x50: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, ra sp+0x40
// Demuxes one pack through a temporary MPS handle (sub_577DD8 / sub_575AA0); when the pack-header class bit
//   0x10000 is set, copies the pack record out (sub_5777F8) and *out = its word 3; destroys the handle (sub_577F78).
void sub_58A740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a740
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(s2, sp, 0x30);
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x40);
    s3 = a2;
    jal(ctx, 0x58A760u, gen::fn_sub_577DD8_00577dd8);
    s2 = v0;
    a3 = addiu(sp, 0x10);
    a1 = s0;
    a2 = s1;
    a0 = s2;
    t0 = addiu(sp, 0x14);
    if (s2 != 0) {
        // 0x0058a784
        charge(ctx, 8);
        jal(ctx, 0x58A784u, gen::fn_sub_575AA0_00575aa0);
        v1 = 0x10000;
        lw(v0, sp, 0x14);
        a1 = sp;
        v0 = v0 & v1;
        a0 = s2;
        if (v0 != 0) {
            // 0x0058a7a4
            charge(ctx, 6);
            jal(ctx, 0x58A7A4u, gen::fn_sub_5777F8_005777f8);
            a0 = s2;
            jal(ctx, 0x58A7ACu, gen::fn_sub_577F78_00577f78);
            lw(v1, sp, 0xC);
            sw(v1, s3, 0);
        }
    }
    // 0x0058a7bc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0058A7D8 sub_58A7D8 -- 236 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s2 sp+0x10, ra sp+0x28
// Looks for a Sofdec header in up to four pack-size steps (sub_58B278); when found, parses it into the global
//   info 0x9A76F8 (sub_58A8C8) and copies its positive fields into the result (+28, +20, +24, +32; +8 = 0x7CA030).
void sub_58A7D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a7d8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    lw(s2, s4, 16);
    for (;;) {
        // 0x0058a828
        charge(ctx, 5);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x58A82Cu, gen::fn_sub_58B278_0058b278);
        v1 = slti(s3, 3);
        if (v0 != 0) {
            goto L_0058a83c_5;
        }
        backedge(ctx);
        // 0x0058a810
        charge(ctx, 3);
        s0 = subu(s0, s2);
        s1 = addu(s1, s2);
        if (v1 == 0) {
            goto L_0058a8a4;
        }
        // 0x0058a81c
        charge(ctx, 2);
        if (i64(s0) > 0) {
            // 0x0058a824
            charge(ctx, 1);
            s3 = addiu(s3, 1);
            continue;
        }
        ld(s0, sp, 0x0);
        break;
    }
    // 0x0058a8a8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0058a83c_5:
    charge(ctx, 10);
    v0 = 0x9A0000;
    a0 = s1;
    s1 = addiu(v0, 30456);  // &0x9A76F8
    a1 = s0;
    sw(zero, s1, 0);  // 0x9A76F8
    a2 = s1;
    jal(ctx, 0x58A850u, gen::fn_sub_58A8C8_0058a8c8);
    lw(v0, s1, 0);  // 0x9A76F8
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0058a864
        charge(ctx, 3);
        lw(v0, s1, 12);
        if (i64(v0) > 0) {
            sw(v0, s4, 28);
        }
        // 0x0058a870
        charge(ctx, 3);
        lw(v0, s1, 100);
        if (i64(v0) > 0) {
            sw(v0, s4, 20);
        }
        // 0x0058a87c
        charge(ctx, 3);
        lw(v0, s1, 104);
        if (i64(v0) > 0) {
            sw(v0, s4, 24);
        }
        // 0x0058a888
        charge(ctx, 3);
        lw(a2, s1, 108);
        ld(s0, sp, 0x0);
        if (i64(a2) > 0) {
            // 0x0058a894
            charge(ctx, 4);
            v0 = 0x7D0000;
            sw(a2, s4, 32);
            v0 = addiu(v0, -24528);  // &0x7CA030
            sw(v0, s4, 8);
        L_0058a8a4:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0058a8a8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058A8C8 sub_58A8C8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copies up to 2048 bytes of the header into an info record (+148, sub_575410), stores the length (+144) and
//   parses it (sub_58B560, tail call).
void sub_58A8C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a8c8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = slti(a1, 2049);
    sd(s0, sp, 0x0);
    s0 = 2048;
    if (v0 != 0) s0 = a1;
    a1 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    a0 = addiu(s1, 148);
    sd(ra, sp, 0x10);
    a2 = s0;
    jal(ctx, 0x58A8F0u, gen::fn_sub_575410_00575410);
    ld(ra, sp, 0x10);
    a0 = s1;
    sw(s0, s1, 144);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58B560_0058b560(ctx);  // tail call
}

// 0x0058A918 sub_58A918 -- 260 bytes; frame 0x50: s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s7 sp+0x38, ra sp+0x40
// Walks the buffer's MPEG audio start codes 0x1C0-0x1DF (sub_58AA20, class 0x40000); for each, skips its PES
//   header (sub_58AA88) and tries the audio-header probers (sub_58AB08, sub_58ADA8) on up to the pack size (+16);
//   stops at the first match.
void sub_58A918(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a918
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a0;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(s6, sp, 0x30);
    s6 = addu(s4, s3);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    lw(s7, s5, 16);
    for (;;) {
        // 0x0058a978
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (i64(s3) <= 0) {
            break;
        }
        // 0x0058a980
        charge(ctx, 8);
        a0 = s4;
        a1 = s3;
        a2 = 0x40000;
        jal(ctx, 0x58A988u, gen::fn_sub_58AA20_0058aa20);
        s2 = v0;
        a0 = s2;
        a1 = subu(s6, s2);
        if (s2 == 0) {
            goto L_0058a9f0;
        }
        // 0x0058a9a0
        charge(ctx, 6);
        lbu(v0, s2, 3);
        v0 = addiu(v0, 64);
        v0 = v0 & 0xFF;
        v0 = sltiu(v0, 32);
        if (v0 == 0) {
            v0 = subu(s2, s4);
            backedge(ctx);
        } else {
            // 0x0058a9b8
            charge(ctx, 14);
            s0 = s7;
            jal(ctx, 0x58A9B8u, gen::fn_sub_58AA88_0058aa88);
            a2 = s5;
            s1 = v0;
            v0 = subu(s6, s1);
            a0 = s1;
            v1 = slt(v0, s0);
            if (v1 != 0) s0 = v0;
            a1 = s0;
            jal(ctx, 0x58A9D8u, gen::fn_sub_58AB08_0058ab08);
            a0 = s1;
            a1 = s0;
            a2 = s5;
            if (v0 != 0) {
                goto L_0058a9f0;
            }
            backedge(ctx);
            // 0x0058a958
            charge(ctx, 4);
            jal(ctx, 0x58A958u, gen::fn_sub_58ADA8_0058ada8);
            ld(s0, sp, 0x0);
            if (v0 == 0) {
                // 0x0058a968
                charge(ctx, 1);
                v0 = subu(s2, s4);
                goto L_0058a96c;
            }
            break;
        }
    L_0058a96c:
        charge(ctx, 3);
        v0 = addiu(v0, 1);
        s3 = subu(s3, v0);
        s4 = addu(s4, v0);
    }
    // 0x0058a9f4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_0058a9f0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058a9f4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
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

// 0x0058AA88 sub_58AA88 -- 124 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// The payload start of a PES packet: through a temporary MPS handle (sub_577DD8 / sub_575AA0 / sub_577F78), the
//   buffer plus the header length the demuxer reports; without a handle, the buffer plus min(len, 6).
void sub_58AA88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058aa88
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a0;
    jal(ctx, 0x58AAA0u, gen::fn_sub_577DD8_00577dd8);
    s1 = v0;
    v0 = slti(s0, 7);
    v1 = 6;
    a1 = s2;
    if (v0 != 0) v1 = s0;
    a2 = s0;
    a3 = sp;
    t0 = addiu(sp, 0x4);
    a0 = s1;
    v0 = addu(s2, v1);
    if (s1 != 0) {
        // 0x0058aad4
        charge(ctx, 6);
        jal(ctx, 0x58AAD4u, gen::fn_sub_575AA0_00575aa0);
        a0 = s1;
        jal(ctx, 0x58AADCu, gen::fn_sub_577F78_00577f78);
        lw(v0, sp, 0x0);
        v0 = addu(s2, v0);
    }
    // 0x0058aaec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058B4A8 sub_58B4A8 -- 100 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Re-reads a handle's header: when the header buffer (sub_58B510) exists, copies it into the info record at
//   +120 (loc_58B3D8), parses it (sub_58B560) and copies its system words (sub_58BB80, tail call).
void sub_58B4A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b4a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = addiu(s1, 120);
    jal(ctx, 0x58B4BCu, gen::fn_sub_58B510_0058b510);
    a1 = v0;
    a0 = s0;
    if (v0 == 0) {
        // 0x0058b4f8
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058b4d0
    charge(ctx, 10);
    link(ctx, 0x58B4D0u);
    gen::fn_sub_58B398_0058b398_at_0058b3d8(ctx);
    a0 = s0;
    jal(ctx, 0x58B4D8u, gen::fn_sub_58B560_0058b560);
    a0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BB80_0058bb80(ctx);  // tail call
}

// 0x0058BD68 sub_58BD68 -- 164 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// SFD finish: destroys the eight handles of the table 0x7B4774 (sub_5971E8), then finishes the global parts
//   (sub_599808 0x7B4720, sub_588738 0x7B472C, the jalr through 0x59B588 with 0x7B4730, __env_unlock_11,
//   sub_58C0D8, cosl_12). Returns the jalr's result when non-zero, else the last destroy's. [proposed: SFD_Finish]
void sub_58BD68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bd68
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7B0000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = 7;
    sd(s1, sp, 0x8);
    s1 = addiu(v0, 18292);  // &0x7B4774
    sd(s2, sp, 0x10);
    s2 = 0;
    lw(v0, s1, 0);  // 0x7B4774
    for (;;) {
        // 0x0058bd90
        charge(ctx, 3);
        s1 = addiu(s1, 4);
        a0 = v0;
        if (v0 != 0) {
            // 0x0058bd9c
            charge(ctx, 3);
            jal(ctx, 0x58BD9Cu, gen::fn_sub_5971E8_005971e8);
            s2 = v0;
        }
        // 0x0058bda8
        charge(ctx, 3);
        s0 = addiu(s0, -1);
        if (i64(s0) < 0) {
            break;
        }
        lw(v0, s1, 0);
        backedge(ctx);
    }
    // 0x0058bdb4
    charge(ctx, 22);
    s0 = 0x7B0000;
    s0 = addiu(s0, 18208);  // &0x7B4720
    a0 = s0;
    jal(ctx, 0x58BDBCu, gen::fn_sub_599808_00599808);
    a0 = addiu(s0, 12);  // &0x7B472C
    jal(ctx, 0x58BDC4u, gen::fn_sub_588738_00588738);
    a0 = addiu(s0, 16);  // &0x7B4730
    link(ctx, 0x58BDCCu);
    gen::fn_sub_59B4F0_0059b4f0_at_0059b588(ctx);
    s0 = v0;
    jal(ctx, 0x58BDD4u, gen::fn___env_unlock_11_0058c0f8);
    jal(ctx, 0x58BDDCu, gen::fn_sub_58C0D8_0058c0d8);
    jal(ctx, 0x58BDE4u, gen::fn_cosl_12_0058c0a0);
    v0 = s0;
    ld(s1, sp, 0x8);
    if (s0 == 0) v0 = s2;
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058C0A0 cosl_12 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_562308 (SJRBF finish).
void cosl_12(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c0a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_562308_00562308(ctx);  // tail call
}

// 0x0058C0D8 sub_58C0D8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_58B128 (finishes SFH).
void sub_58C0D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c0d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58B128_0058b128(ctx);  // tail call
}

// 0x0058C0F8 __env_unlock_11 -- 8 bytes; leaf frame (no stack)
// Does nothing.
void __env_unlock_11(EEContext& ctx) {
    using namespace hg;
    // 0x0058c0f8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0058C198 sub_58C198 -- 28 bytes; frame 0x10: ra sp+0x0
// Chunk read on the handle's SJ (+8004): sub_589000(handle, sj, a1) as a tail call.
void sub_58C198(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c198
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a1;
    sd(ra, sp, 0x0);
    lw(a1, a0, 8004);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589000_00589000(ctx);  // tail call
}

// 0x0058C1B8 sub_58C1B8 -- 36 bytes; frame 0x10: ra sp+0x0
// Chunk release on the handle's SJ (+8004): sub_5890D8(handle, sj, a1, a2) as a tail call.
void sub_58C1B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c1b8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    a3 = a2;
    a2 = v0;
    lw(a1, a0, 8004);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5890D8_005890d8(ctx);  // tail call
}

// 0x0058C1E0 sub_58C1E0 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000501 on the handle (sub_58BE40, tail call).
void sub_58C1E0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c1e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x501;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058C200 sub_58C200 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000501 on the handle (sub_58BE40, tail call).
void sub_58C200(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c200
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x501;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058C220 sub_58C220 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_58C220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c220
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C380 r_lock_def_free_6 -- 32 bytes; frame 0x10: ra sp+0x0
// Finishes MPS (sub_577B40) and returns 0.
void r_lock_def_free_6(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c380
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x58C388u, gen::fn_sub_577B40_00577b40);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0058DF90 sub_58DF90 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call to sub_58BE40 with the caller's arguments (raises the given code on the handle).
void sub_58DF90(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058df90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058E010 sub_58E010 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_58E010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058e010
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058E018 sub_58E018 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_58E018(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058e018
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058E020 sub_58E020 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_58E020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058e020
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058E028 sub_58E028 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_58E028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058e028
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058E030 sub_58E030 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000D0B on the handle (sub_58BE40, tail call).
void sub_58E030(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e030
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xD0B;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058E050 sub_58E050 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000D0B on the handle (sub_58BE40, tail call).
void sub_58E050(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e050
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xD0B;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058E070 sub_58E070 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000D0B on the handle (sub_58BE40, tail call).
void sub_58E070(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e070
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xD0B;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058E090 sub_58E090 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000D0B on the handle (sub_58BE40, tail call).
void sub_58E090(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e090
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xD0B;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058E0B0 sub_58E0B0 -- 164 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Header-object step: with a header record (sub_58E200) whose word 0 is set, re-reads the header
//   (sub_58B4A8), calls sub_58E158, demuxes the record's two buffers (sub_58E160) and, when that succeeds,
//   copies the record's time words (+24, +32, +40, +44) into the handle (+3712) and the video record (+8060).
void sub_58E0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e0b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s1 = a0;
    jal(ctx, 0x58E0C8u, gen::fn_sub_58E200_0058e200);
    s0 = v0;
    if (s0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0058e0dc
        charge(ctx, 3);
        lw(v1, s0, 0);
        v0 = 0;
        if (v1 != 0) {
            // 0x0058e0e8
            charge(ctx, 12);
            lw(s2, s1, 8060);
            a0 = s1;
            jal(ctx, 0x58E0ECu, gen::fn_sub_58B4A8_0058b4a8);
            a0 = s1;
            jal(ctx, 0x58E0F4u, gen::fn_sub_58E158_0058e158);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            s3 = addiu(s1, sfd::kTimeRec);
            jal(ctx, 0x58E108u, gen::fn_sub_58E160_0058e160);
            if (v0 == 0) {
                // 0x0058e118
                charge(ctx, 8);
                lw(a0, s0, 40);
                ld(v1, s0, 24);
                sw(a0, s2, 44);
                sd(v1, s3, 336);
                lw(a0, s0, 44);
                ld(v1, s0, 32);
                sw(a0, s2, 48);
                sd(v1, s2, 16);
                goto L_0058e138;
            }
            ld(s0, sp, 0x0);
            // 0x0058e13c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0058e138:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0058e13c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058E160 sub_58E160 -- 160 bytes; frame 0x40: s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s1 sp+0x18, ra sp+0x38
// Demuxes the record's two buffers (+48 / +400 and +224 / +404) through the MPS handle *a1 (sub_575AA0); either
//   failing raises SFD error 0xFF000D0D (sub_58BE40, tail call).
void sub_58E160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e160
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    a3 = sp;
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s3, sp, 0x28);
    s0 = addiu(s2, 48);
    sd(s4, sp, 0x30);
    s4 = a0;
    sd(s1, sp, 0x18);
    t0 = addiu(sp, 0x4);
    sd(ra, sp, 0x38);
    lw(s1, a1, 0);
    a1 = s0;
    lw(a2, s0, 352);
    a0 = s1;
    jal(ctx, 0x58E19Cu, gen::fn_sub_575AA0_00575aa0);
    a0 = s1;
    lw(a2, s0, 356);
    a1 = addiu(s2, 224);
    a3 = sp;
    t0 = addiu(sp, 0x4);
    s3 = v0;
    jal(ctx, 0x58E1B8u, gen::fn_sub_575AA0_00575aa0);
    v1 = v0;
    a1 = lui(0xFF00);
    a0 = s4;
    if (s3 == 0) {
        // 0x0058e1d0
        charge(ctx, 2);
        ld(s0, sp, 0x10);
        if (v1 != 0) {
            goto L_0058e1d8;
        }
        // 0x0058e1e4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058e1d8:
    charge(ctx, 3);
    a1 = a1 | 0xD0D;
    jal(ctx, 0x58E1D8u, gen::fn_sub_58BE40_0058be40);
    ld(s0, sp, 0x10);
    // 0x0058e1e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058E4A0 sub_58E4A0 -- 144 bytes; leaf frame (no stack)
// Lays out a picture buffer's planes from the width and height (16-pixel macroblocks and 64-pixel blocks,
//   MMI mult1): +8 = the base, +0 and +4 the plane addresses after it, +12 / +14 the 64-aligned widths.
void sub_58E4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0058e4a0
    enter(ctx, 36);  // entry check point + this block's cycles
    v0 = addiu(a1, 15);
    a1 = addiu(a1, 30);
    v1 = slti(v0, 0);
    t2 = addiu(a2, 15);
    if (v1 != 0) v0 = a1;
    t3 = slti(t2, 0);
    v0 = sra(v0, 4);
    a2 = addiu(a2, 30);
    a1 = sll(v0, 4);
    v0 = sll(v0, 3);
    t0 = addiu(a1, 63);
    a1 = addiu(a1, 126);
    t1 = addiu(v0, 63);
    v0 = addiu(v0, 126);
    v1 = slti(t0, 0);
    if (t3 != 0) t2 = a2;
    if (v1 != 0) t0 = a1;
    v1 = slti(t1, 0);
    if (v1 != 0) t1 = v0;
    t0 = sra(t0, 6);
    t2 = sra(t2, 4);
    t1 = sra(t1, 6);
    mult(v0, t0, t2);
    mult1(t2, t1, t2);
    t0 = sll(t0, 6);
    t1 = sll(t1, 6);
    sh(t0, a3, 14);
    sh(t1, a3, 12);
    v0 = sll(v0, 10);
    t2 = sll(t2, 9);
    v0 = addu(a0, v0);
    sw(a0, a3, 8);
    t2 = addu(v0, t2);
    sw(v0, a3, 0);
    sw(t2, a3, 4);
}

// 0x0058E6E8 sub_58E6E8 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// *out = 0; with a valid handle (sub_58C060), *out = the number of frames waiting (sub_593978); a bad handle
//   raises 0xFF000182.
void sub_58E6E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e6e8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    link(ctx, 0x58E700u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0058e714
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x182;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058e730
    charge(ctx, 9);
    a0 = s1;
    jal(ctx, 0x58E730u, gen::fn_sub_593978_00593978);
    sw(v0, s0, 0);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058FC30 sub_58FC30 -- 208 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Audio-clock step of the system-stream server: the elapsed time from the audio when param 6 is set
//   (sub_58FD60, -1 when its ring is empty) or from the video time code (sub_58FD00); a positive count is pushed
//   to the ring (sub_58A080) and counted (+136); with sceMpeg, +3376+352 = sub_5954D8 + 1. Then resets two picture
//   records (sub_599A30, 0x7FFFFFFF and -1) and sets +120 = 192.
void sub_58FC30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fc30
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 6;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, sfd::kTimeRec);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    link(ctx, 0x58FC50u);  // $ra first: the delay slot below depends on it
    lw(s2, s0, sfd::kVdecWork);
    call(ctx, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 == 0) {
        // 0x0058fc60
        charge(ctx, 4);
        jal(ctx, 0x58FC60u, gen::fn_sub_58FD00_0058fd00);
        a1 = v0;
        goto L_0058fc84;
    }
    // 0x0058fc70
    charge(ctx, 5);
    jal(ctx, 0x58FC70u, gen::fn_sub_58FD60_0058fd60);
    a1 = v0;
    v0 = si(-1);
    if (i64(a1) >= 0) {
    L_0058fc84:
        charge(ctx, 2);
        if (i64(a1) <= 0) {
            a1 = 0x7FFF0000;
        } else {
            // 0x0058fc8c
            charge(ctx, 9);
            a0 = s0;
            jal(ctx, 0x58FC8Cu, gen::fn_sub_58A080_0058a080);
            a0 = s0;
            lw(v0, s2, 136);
            v0 = addiu(v0, 1);
            link(ctx, 0x58FCA0u);  // $ra first: the delay slot below depends on it
            sw(v0, s2, 136);
            call(ctx, gen::fn_sub_594B78_00594b78);
            a0 = s0;
            if (v0 != 0) {
                // 0x0058fcb0
                charge(ctx, 4);
                jal(ctx, 0x58FCB0u, gen::fn_sub_5954D8_005954d8);
                v0 = addiu(v0, 1);
                sw(v0, s1, 352);
            }
            // 0x0058fcc0
            charge(ctx, 1);
            a1 = 0x7FFF0000;
        }
        // 0x0058fcc4
        charge(ctx, 9);
        a0 = addiu(s1, 60);
        a1 = a1 | 0xFFFF;
        jal(ctx, 0x58FCC8u, gen::fn_sub_599A30_00599a30);
        a0 = addiu(s1, 104);
        a1 = si(-1);
        jal(ctx, 0x58FCD4u, gen::fn_sub_599A30_00599a30);
        v0 = 192;
        sw(v0, s2, 120);
        v0 = 0;
    }
    // 0x0058fce8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058FD00 sub_58FD00 -- 92 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// Elapsed time from the video time code: when +3480 is set, advances a copy of +3484 (sub_590DF8), converts
//   it (sub_59A870) and returns it minus +3472; else 0.
void sub_58FD00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fd00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = a0;
    sd(s0, sp, 0x30);
    s0 = addiu(v1, 3436);
    sd(ra, sp, 0x38);
    v0 = 0;
    lw(a1, v1, 3480);
    a0 = addiu(v1, 3484);
    if (a1 != 0) {
        // 0x0058fd24
        charge(ctx, 10);
        a1 = sp;
        jal(ctx, 0x58FD24u, gen::fn_sub_590DF8_00590df8);
        a0 = sp;
        a1 = addiu(sp, 0x20);
        a2 = addiu(sp, 0x24);
        link(ctx, 0x58FD38u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn_sub_59A870_0059a870);
        lw(v1, s0, 36);
        lw(v0, sp, 0x20);
        v0 = subu(v0, v1);
    }
    // 0x0058fd4c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058FD60 sub_58FD60 -- 164 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Elapsed audio time: when the audio is the CRI type (vtable +12 = 0x7C9D78), adds the next ring entry
//   (sub_58A1C0; -1 when empty) to the sample total +3872 with its rate, else adds 0 at 44100; returns
//   muldiv(total, +3476, rate) (sub_57BAF0) minus +3732, at least 0.
void sub_58FD60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fd60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7D0000;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    v0 = addiu(v0, -25224);  // "XhX"
    lw(a1, s0, 0);
    lw(v1, a1, 12);
    s1 = addiu(s0, sfd::kTimeRec);
    if (v1 != v0) {
        // 0x0058fd8c
        charge(ctx, 4);
        v0 = 0xAC44;
        sw(zero, sp, 0x0);
        sw(v0, sp, 0x4);
        // 0x0058fdc0
        charge(ctx, 1);
        lw(v0, s1, 496);
        goto L_0058fdc4;
    }
    // 0x0058fda0
    charge(ctx, 5);
    a1 = sp;
    a2 = addiu(sp, 0x4);
    jal(ctx, 0x58FDA4u, gen::fn_sub_58A1C0_0058a1c0);
    if (v0 != 0) {
        lw(v0, s1, 496);
    L_0058fdc4:
        charge(ctx, 11);
        lw(v1, sp, 0x0);
        lw(a1, s0, 3476);
        v0 = addu(v0, v1);
        lw(a2, sp, 0x4);
        sw(v0, s1, 496);
        a0 = v0;
        jal(ctx, 0x58FDD8u, gen::fn_sub_57BAF0_0057baf0);
        lw(v1, s1, 356);
        v0 = subu(v0, v1);
        a0 = slti(v0, 0);
        if (a0 != 0) v0 = 0;
    } else {
        // 0x0058fdb4
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0058fdf0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00590430 sub_590430 -- 380 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s6 sp+0x30, s7 sp+0x38, fp sp+0x40, s4 sp+0x20, s5 sp+0x28, ra sp+0x48
// The picture's presentation time: the stream's base time (+336, set once from the time code less the field
//   time, sub_5905B0, rate table 0x7CA2C0); a new GOP time code (memcmp) is copied with its field count (*$t1 =
//   the code), the same GOP adds its field offset (sub_5905B0). Returns the time since the base, at least 0.
void sub_590430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00590430
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    s7 = t0;
    sd(fp, sp, 0x40);
    fp = t1;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x48);
    lw(v0, s3, 16);
    ld(v1, s1, 336);
    v0 = sll(v0, 2);
    s6 = 0x7D0000;
    s6 = addu(s6, v0);
    lw(s6, s6, -23872);
    lw(s5, s3, 20);
    if (i64(v1) < 0) {
        // 0x00590494
        charge(ctx, 8);
        a0 = s5;
        a1 = s6;
        jal(ctx, 0x590498u, gen::fn_sub_5905B0_005905b0);
        ld(v1, s2, 0);
        v1 = v1 - v0;
        v0 = slti(v1, 0);
        if (v0 != 0) v1 = 0;
        sd(v1, s1, 336);
    }
    // 0x005904b4
    charge(ctx, 11);
    ld(v0, s2, 0);
    s4 = addiu(s0, 16);
    a0 = s4;
    a1 = s2;
    s1 = v0 - v1;
    a2 = 4;
    v0 = slti(s1, 0);
    if (v0 != 0) s1 = 0;
    jal(ctx, 0x5904D0u, gen::fn_memcmp_005211b8);
    a1 = 3;
    if (v0 == 0) {
        // 0x00590520
        charge(ctx, 2);
        if (s7 == 0) {
            lw(a0, s0, 0);
        } else {
            // 0x00590528
            charge(ctx, 8);
            lw(v0, s0, 4);
            lw(v1, s0, 8);
            sw(zero, s0, 0);
            v0 = addu(v0, v1);
            sw(zero, s0, 8);
            v0 = addiu(v0, 1);
            sw(v0, s0, 4);
            lw(a0, s0, 0);
        }
        // 0x00590548
        charge(ctx, 12);
        a1 = s6;
        lw(v1, s0, 8);
        a0 = subu(s5, a0);
        lw(a2, s0, 4);
        v0 = slt(a0, v1);
        if (v0 == 0) v1 = a0;
        a0 = addu(a2, a0);
        link(ctx, 0x590564u);  // $ra first: the delay slot below depends on it
        sw(v1, s0, 8);
        call(ctx, gen::fn_sub_5905B0_005905b0);
        s1 = s1 + v0;
        v0 = slti(s1, 0);
        if (v0 != 0) s1 = 0;
    } else {
        // 0x005904e0
        charge(ctx, 8);
        ld(v1, s2, 0);
        lw(a0, s3, 24);
        sd(v1, s4, 0);
        ld(v0, s2, 8);
        sw(s5, s0, 0);
        sd(v0, s0, 24);
        sw(zero, s0, 4);
        if (a0 != a1) {
            // 0x00590510
            charge(ctx, 1);
            sw(zero, s0, 8);
        } else {
            // 0x00590500
            charge(ctx, 3);
            v0 = 1;
            sw(v0, s0, 8);
        }
        // 0x00590514
        charge(ctx, 3);
        ld(v0, s2, 0);
        sd(v0, fp, 0x0);
    }
    // 0x00590578 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x005905B0 sub_5905B0 -- 60 bytes; frame 0x10: ra sp+0x0
// 90,000,000 x n / rate (a 64-bit product divided by __divdi3): a field count in 90 kHz x 1000 units.
void sub_5905B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005905b0
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x55D0000;
    sp = addiu(sp, -0x10);
    v0 = v0 | 0x4A80;
    mult(zero, a0, v0);
    sd(ra, sp, 0x0);
    mflo(v1);
    mfhi(a0);
    v1 = dsll32(v1, 0);
    a0 = dsll32(a0, 0);
    v1 = dsrl32(v1, 0);
    a0 = a0 | v1;
    jal(ctx, 0x5905D8u, gen::fn___divdi3_0052eeb0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00590878 sub_590878 -- 204 bytes; frame 0x30: s1 sp+0x18, s2 sp+0x20, s0 sp+0x10, ra sp+0x28
// Stores a picture's converted time (sub_59A870) relative to +3472 into its record (+48, +52, flag +12 = 1); when
//   it is at or past the handle's threshold (+3516), copies the 44-byte record to +3480.
void sub_590878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00590878
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = a0;
    a1 = sp;
    a2 = addiu(sp, 0x4);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x28);
    a0 = addiu(s1, 16);
    jal(ctx, 0x59089Cu, gen::fn_sub_59A870_0059a870);
    s0 = addiu(s2, sfd::kTimeRec);
    lw(v1, sp, 0x0);
    lw(a1, s0, 96);
    v0 = 1;
    lw(a0, sp, 0x4);
    v1 = subu(v1, a1);
    sw(v0, s1, 12);
    sw(v1, s1, 48);
    sw(a0, s1, 52);
    lw(v0, s0, 140);
    v1 = slt(v1, v0);
    ld(s0, sp, 0x10);
    if (v1 == 0) {
        // 0x005908d8
        charge(ctx, 22);
        ldl(v0, s1, 19);
        ldr(v0, s1, 12);
        ldl(v1, s1, 27);
        ldr(v1, s1, 20);
        ldl(a0, s1, 35);
        ldr(a0, s1, 28);
        ldl(a1, s1, 43);
        ldr(a1, s1, 36);
        sdl(v0, s2, 3487);
        sdr(v0, s2, 3480);
        sdl(v1, s2, 3495);
        sdr(v1, s2, 3488);
        sdl(a0, s2, 3503);
        sdr(a0, s2, 3496);
        sdl(a1, s2, 3511);
        sdr(a1, s2, 3504);
        ldl(v0, s1, 51);
        ldr(v0, s1, 44);
        lw(v1, s1, 52);
        sdl(v0, s2, 3519);
        sdr(v0, s2, 3512);
        sw(v1, s2, 3520);
    }
    // 0x00590930 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00590A28 sub_590A28 -- 192 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// Whether the stored time code (+3480) is due: converts the current (+3404) and stored (+3484) codes
//   (sub_59A870); 1 when the current one is within param 53 frames of the stored one or the code is unset.
void sub_590A28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00590a28
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(ra, sp, 0x38);
    lw(v1, s0, 3480);
    a0 = sp;
    if (v1 != 0) {
        // 0x00590a48
        charge(ctx, 33);
        a1 = addiu(sp, 0x20);
        ldl(v0, s0, 3411);
        ldr(v0, s0, 3404);
        ldl(v1, s0, 3419);
        ldr(v1, s0, 3412);
        ldl(a3, s0, 3427);
        ldr(a3, s0, 3420);
        ldl(t0, s0, 3435);
        ldr(t0, s0, 3428);
        sdl(v0, sp, 0x7);
        sdr(v0, sp, 0x0);
        sdl(v1, sp, 0xF);
        sdr(v1, sp, 0x8);
        sdl(a3, sp, 0x17);
        sdr(a3, sp, 0x10);
        sdl(t0, sp, 0x1F);
        sdr(t0, sp, 0x18);
        a2 = addiu(sp, 0x24);
        jal(ctx, 0x590A8Cu, gen::fn_sub_59A870_0059a870);
        a1 = addiu(sp, 0x28);
        a2 = addiu(sp, 0x24);
        a0 = addiu(s0, 3484);
        jal(ctx, 0x590A9Cu, gen::fn_sub_59A870_0059a870);
        a0 = s0;
        a1 = 53;
        jal(ctx, 0x590AA8u, gen::fn_sub_599408_00599408);
        lw(a2, sp, 0x20);
        lw(a1, sp, 0x28);
        lw(v1, sp, 0x24);
        a0 = slt(a1, a2);
        mult(v1, v0, v1);
        v0 = 1;
        if (a0 != 0) {
            // 0x00590acc
            charge(ctx, 3);
            v0 = addu(a1, v1);
            v0 = slt(a2, v0);
            v0 = sltiu(v0, 1);
        }
    }
    // 0x00590ad8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00591700 sub_591700 -- 264 bytes; frame 0x50: s1 sp+0x18, s4 sp+0x30, s5 sp+0x38, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, ra sp+0x40
// Picks the decoder's skip mode (vdec::kSkipMode, 3 skips B, 2 P and B): 5 when the decoder's first word (sub_579368) is 1, 2 when
//   its second word (or param 73 without a pending seek +3656) is 1; then 2 for a picture of type 1 or 2 when
//   $a2 == 1, else 2 -> 3 and 3 -> 5.
void sub_591700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00591700
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s4, sp, 0x30);
    s4 = a2;
    sd(s5, sp, 0x38);
    s5 = a1;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x40);
    lw(s3, s1, sfd::kVdecWork);
    lw(v0, s3, 272);
    lw(a0, s3, 0);
    lw(s0, s3, 116);
    if (v0 != 0) {
        // 0x00591740
        charge(ctx, 7);
        a1 = sp;
        a2 = addiu(sp, 0x4);
        jal(ctx, 0x591744u, gen::fn_sub_579368_00579368);
        s2 = 1;
        lw(v1, sp, 0x0);
        if (v1 != s2) {
            lw(v0, s1, 3656);
            // 0x00591768
            charge(ctx, 2);
            if (v0 != 0) {
                lw(v0, sp, 0x4);
            } else {
                // 0x00591770
                charge(ctx, 8);
                a0 = s1;
                a1 = 73;
                jal(ctx, 0x591774u, gen::fn_sub_599408_00599408);
                lw(v1, sp, 0x4);
                a0 = v0 ^ s2;
                if (a0 == 0) v1 = v0;
                sw(v1, sp, 0x4);
                lw(v0, sp, 0x4);
            }
            // 0x00591790
            charge(ctx, 3);
            v1 = 2;
            v0 = v0 ^ s2;
            if (v0 == 0) s0 = v1;
        } else {
            // 0x0059175c
            charge(ctx, 2);
            s0 = 5;
        }
    }
    // 0x0059179c
    charge(ctx, 3);
    v0 = 1;
    cc = s4 != v0;  // the condition, before the delay slot changes it
    v0 = 2;
    if (cc) {
        // 0x005917c8
        charge(ctx, 2);
        v1 = 5;
        if (s0 != v0) {
            // 0x005917d8
            charge(ctx, 2);
            v0 = s0 ^ 0x3;
            if (v0 == 0) s0 = v1;
        } else {
            // 0x005917d0
            charge(ctx, 2);
            s0 = 3;
        }
    L_005917e0:
        charge(ctx, 1);
        sw(s0, s3, 116);
    } else {
        // 0x005917a8
        charge(ctx, 5);
        lw(v0, s5, 24);
        v0 = addiu(v0, -1);
        v0 = sltiu(v0, 2);
        if (v0 != 0) {
            s0 = 2;
            goto L_005917e0;
        }
        // 0x005917bc
        charge(ctx, 2);
        sw(s0, s3, 116);
    }
    // 0x005917e4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00591808 sub_591808 -- 80 bytes; frame 0x10: ra sp+0x0
// The ratio compare (sub_56F4B8) of the picture time +14008 / +14012 against the display time +3604 / +3608,
//   negated, while +14008 >= 0 and no seek is pending (+3656); else 0.
void sub_591808(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00591808
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = addiu(a0, 14004);
    sd(ra, sp, 0x0);
    v0 = 0;
    v1 = addiu(a0, 3656);
    lw(a2, a1, 4);
    t0 = addiu(a0, 3568);
    if (i64(a2) >= 0) {
        // 0x00591828
        charge(ctx, 3);
        lw(v1, v1, 0);
        if (v1 == 0) {
            // 0x00591834
            charge(ctx, 6);
            a0 = a2;
            lw(a2, t0, 36);
            lw(a1, a1, 8);
            link(ctx, 0x591840u);  // $ra first: the delay slot below depends on it
            lw(a3, t0, 40);
            call(ctx, gen::fn_sub_56F4B8_0056f4b8);
            v0 = sltiu(v0, 1);
            goto L_0059184c;
        }
        ld(ra, sp, 0x0);
        // 0x00591850 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0059184c:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x00591850 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005918A8 sub_5918A8 -- 224 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// Unless param 7 is set, skips a picture of type 3 (sub_578378) or type 2 (sub_578820) with the frame size
//   +2324 x +2328 and counts it (+2400 / +2404).
void sub_5918A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005918a8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = a1;
    a1 = 7;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x5918CCu, gen::fn_sub_599408_00599408);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x005918dc
        charge(ctx, 4);
        v0 = 3;
        s2 = addiu(s0, 2384);
        a0 = addiu(s0, 2316);
        if (s3 != v0) {
            // 0x00591928
            charge(ctx, 3);
            v0 = 2;
            v1 = 0;
            if (s3 != v0) {
            L_00591968:
                charge(ctx, 1);
                v0 = v1;
            } else {
                // 0x00591934
                charge(ctx, 10);
                lw(a2, a0, 8);
                lw(v0, a0, 12);
                lw(a1, s1, 4);
                mult(zero, a2, v0);
                mflo(a2);
                link(ctx, 0x591948u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, 0);
                call(ctx, gen::fn_sub_578820_00578820);
                v1 = v0;
                v0 = v1;
                if (v1 != 0) {
                    // 0x0059195c
                    charge(ctx, 3);
                    lw(v0, s2, 20);
                    v0 = addiu(v0, 1);
                    sw(v0, s2, 20);
                    goto L_00591968;
                }
            }
        } else {
            // 0x005918ec
            charge(ctx, 10);
            lw(a2, a0, 8);
            lw(v0, a0, 12);
            lw(a1, s1, 4);
            mult(zero, a2, v0);
            mflo(a2);
            link(ctx, 0x591900u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 0);
            call(ctx, gen::fn_sub_578378_00578378);
            v1 = v0;
            v0 = v1;
            if (v1 != 0) {
                // 0x00591914
                charge(ctx, 4);
                lw(v0, s2, 16);
                v0 = addiu(v0, 1);
                sw(v0, s2, 16);
                goto L_00591968;
            }
        }
    }
    // 0x0059196c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00591988 sub_591988 -- 376 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s4 sp+0x30, s3 sp+0x28, s5 sp+0x38, ra sp+0x40
// Whether a picture is late: the user callback +3400 (jalr) decides when set; else the time (+3604 adjusted
//   by the seek offsets) goes through sub_599AA0 / sub_599B40 for picture types 1 / 2, and with the play speed
//   (sub_59B3A0) or the late-count limit, compares the clock (sub_59A168) to it (sub_56F4B8); a late picture counts
//   (+132) and returns 1.
void sub_591988(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00591988
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = addiu(s0, sfd::kTimeRec);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s4, sp, 0x30);
    s4 = 0;
    sd(s3, sp, 0x28);
    v1 = addiu(s0, 3656);
    sd(s5, sp, 0x38);
    a2 = addiu(s0, 3568);
    sd(ra, sp, 0x40);
    lw(v0, v1, 0);
    lw(s5, s0, sfd::kVdecWork);
    if (v0 != 0) {
        // 0x005919cc
        charge(ctx, 5);
        lw(v0, v1, 36);
        lw(v1, a2, 36);
        lw(a0, s1, 356);
        v1 = subu(v1, v0);
        s4 = addu(v1, a0);
    }
    // 0x005919e0
    charge(ctx, 3);
    lw(v0, s1, 24);
    lw(s3, a2, 40);
    if (v0 == 0) {
        // 0x00591a08
        charge(ctx, 3);
        v0 = 1;
        if (s2 != v0) {
            v0 = addiu(s2, -1);
        } else {
            // 0x00591a14
            charge(ctx, 4);
            a0 = s1;
            a1 = s4;
            jal(ctx, 0x591A18u, gen::fn_sub_599AA0_00599aa0);
            v0 = addiu(s2, -1);
        }
        // 0x00591a24
        charge(ctx, 3);
        v0 = sltiu(v0, 2);
        a1 = s4;
        if (v0 != 0) {
            // 0x00591a30
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x591A30u, gen::fn_sub_599B40_00599b40);
            s4 = v0;
        }
        // 0x00591a3c
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x591A3Cu, gen::fn_sub_59B3A0_0059b3a0);
        v0 = slti(v0, 1001);
        a0 = s0;
        if (v0 != 0) {
            // 0x00591a50
            charge(ctx, 5);
            lw(v1, s5, 132);
            lw(a0, s0, 2724);
            v1 = slt(v1, a0);
            v0 = 0;
            if (v1 != 0) {
                // 0x00591a64
                charge(ctx, 1);
                a0 = s0;
                goto L_00591a68;
            }
            goto L_00591adc;
        }
    L_00591a68:
        charge(ctx, 6);
        a1 = sp;
        a2 = addiu(sp, 0x4);
        jal(ctx, 0x591A6Cu, gen::fn_sub_59A168_0059a168);
        lw(v1, sp, 0x0);
        v0 = 0;
        if (i64(v1) >= 0) {
            // 0x00591a80
            charge(ctx, 11);
            a0 = s0;
            a1 = s2;
            a2 = addiu(sp, 0x8);
            a3 = addiu(sp, 0xC);
            jal(ctx, 0x591A8Cu, gen::fn_sub_591B00_00591b00);
            a3 = s3;
            lw(a2, sp, 0x8);
            lw(v0, sp, 0xC);
            mult(a2, s3, a2);
            if (v0 == 0) {
                brk(ctx, 0x591AA8u, 0x7u);
            }
            // 0x00591aac
            charge(ctx, 8);
            lw(a0, sp, 0x0);
            lw(a1, sp, 0x4);
            div(a2, v0);
            mflo(a2);
            a2 = subu(s4, a2);
            jal(ctx, 0x591ABCu, gen::fn_sub_56F4B8_0056f4b8);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x00591acc
                charge(ctx, 4);
                lw(v1, s5, 132);
                v0 = 1;
                v1 = addiu(v1, 1);
                sw(v1, s5, 132);
            }
        }
    L_00591adc:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x005919ec
        charge(ctx, 7);
        a0 = s0;
        a1 = s2;
        a2 = s4;
        a3 = s3;
        jalr(ctx, 0x5919F8u, v0.u());
        ld(s0, sp, 0x10);
    }
    // 0x00591ae0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00591B00 sub_591B00 -- 24 bytes; leaf frame (no stack)
// *$a2 = the frame-rate words +2740 and *$a3 = +2744; returns +2744.
void sub_591B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00591b00
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = addiu(a0, sfd::kParams);
    lw(v0, a0, 172);
    sw(v0, a3, 0);
    lw(v1, a0, 168);
    sw(v1, a2, 0);
}

// 0x00591C08 sub_591C08 -- 120 bytes; leaf frame (no stack)
// When the display time (+3604) is before the pending one (+3692), copies the 44-byte time record +3568 to
//   +3612.
void sub_591C08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00591c08
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = addiu(a0, 3568);
    lw(v1, a0, 3692);
    lw(v0, a1, 36);
    v0 = slt(v0, v1);
    a0 = addiu(a0, 3612);
    if (v0 != 0) {
        // 0x00591c20
        charge(ctx, 22);
        ldl(v0, a1, 7);
        ldr(v0, a1, 0);
        ldl(v1, a1, 15);
        ldr(v1, a1, 8);
        ldl(a2, a1, 23);
        ldr(a2, a1, 16);
        ldl(a3, a1, 31);
        ldr(a3, a1, 24);
        sdl(v0, a0, 7);
        sdr(v0, a0, 0);
        sdl(v1, a0, 15);
        sdr(v1, a0, 8);
        sdl(a2, a0, 23);
        sdr(a2, a0, 16);
        sdl(a3, a0, 31);
        sdr(a3, a0, 24);
        ldl(v0, a1, 39);
        ldr(v0, a1, 32);
        lw(v1, a1, 40);
        sdl(v0, a0, 39);
        sdr(v0, a0, 32);
        sw(v1, a0, 40);
    }
    // 0x00591c78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005927D8 sub_5927D8 -- 348 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// Skips to the next start code in the handle's SJ (+8136): reads the two-part chunk (sub_589018), finds the code
//   (sub_58F548), releases what comes before it less 3 bytes (sub_592938) and counts the bytes (+2472, and +2480
//   when a non-zero byte was dropped). Returns the count, 0 without data.
void sub_5927D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005927d8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    s0 = a2;
    sd(s1, sp, 0x38);
    s1 = a0;
    sd(ra, sp, 0x40);
    a2 = sp;
    link(ctx, 0x5927F4u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 8136);
    call(ctx, gen::fn_sub_589018_00589018);
    lw(v1, sp, 0x4);
    if (v0 == 0) {
        // 0x00592810
        charge(ctx, 2);
        a0 = sp;
        if (v1 != 0) {
            // 0x00592818
            charge(ctx, 6);
            a1 = s0;
            a2 = addiu(sp, 0x20);
            jal(ctx, 0x59281Cu, gen::fn_sub_58F548_0058f548);
            a0 = v0;
            lw(v1, sp, 0x0);
            if (a0 != 0) {
                // 0x00592850
                charge(ctx, 3);
                v0 = sltu(a0, v1);
                lw(a2, sp, 0x8);
                if (v0 == 0) {
                    // 0x0059285c
                    charge(ctx, 5);
                    lw(v0, sp, 0x4);
                    v0 = addu(v1, v0);
                    v0 = sltu(a0, v0);
                    s0 = subu(a0, v1);
                    if (v0 == 0) {
                        // 0x00592870
                        charge(ctx, 1);
                        lw(a2, sp, 0x8);
                        goto L_00592874;
                    }
                L_005928a0:
                    charge(ctx, 1);
                    a0 = s1;
                    goto L_005928a4;
                }
            L_00592874:
                charge(ctx, 3);
                v0 = sltu(a0, a2);
                s0 = 0;
                if (v0 != 0) {
                    goto L_005928a0;
                }
                // 0x00592880
                charge(ctx, 5);
                lw(v0, sp, 0xC);
                v0 = addu(a2, v0);
                v0 = sltu(a0, v0);
                if (v0 != 0) {
                    // 0x00592894
                    charge(ctx, 3);
                    lw(v1, sp, 0x4);
                    v0 = subu(a0, a2);
                    s0 = addu(v0, v1);
                    goto L_005928a0;
                }
                a0 = s1;
            } else {
                // 0x00592830
                charge(ctx, 6);
                lw(v0, sp, 0x4);
                lw(v1, sp, 0xC);
                v0 = addu(v0, v1);
                s0 = addiu(v0, -3);
                a0 = s1;
                if (i64(s0) < 0) {
                    // 0x00592848
                    charge(ctx, 2);
                    s0 = 0;
                }
            }
        L_005928a4:
            charge(ctx, 5);
            a1 = s0;
            jal(ctx, 0x5928A4u, gen::fn_sub_592938_00592938);
            a2 = 0;
            a0 = 0;
            a1 = slti(s0, 4);
            for (;;) {
                // 0x005928b8
                charge(ctx, 5);
                v0 = 3;
                if (a1 != 0) v0 = s0;
                v0 = slt(a0, v0);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                lw(v0, sp, 0x4);
                if (cc) {
                    break;
                }
                // 0x005928cc
                charge(ctx, 4);
                v1 = subu(a0, v0);
                v0 = slt(a0, v0);
                if (v0 == 0) {
                    lw(v0, sp, 0x8);
                    // 0x005928e8
                    charge(ctx, 1);
                    v0 = addu(v0, v1);
                } else {
                    // 0x005928dc
                    charge(ctx, 3);
                    lw(v0, sp, 0x0);
                    v0 = addu(v0, a0);
                }
                // 0x005928ec
                charge(ctx, 3);
                lb(v0, v0, 0);
                a0 = addiu(a0, 1);
                if (v0 != 0) {
                    goto L_005928f8_19;
                }
                backedge(ctx);
            }
        L_005928fc:
            charge(ctx, 2);
            a0 = s0;
            if (a2 != 0) {
                // 0x00592904
                charge(ctx, 3);
                ld(v0, s1, 2480);
                v0 = v0 + a0;
                sd(v0, s1, 2480);
            }
            // 0x00592910
            charge(ctx, 4);
            ld(v1, s1, 2472);
            v0 = s0;
            v1 = v1 + a0;
            sd(v1, s1, 2472);
        }
    } else {
        // 0x00592804
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00592920 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_005928f8_19:
    charge(ctx, 1);
    a2 = 1;
    goto L_005928fc;
}

// 0x00592938 sub_592938 -- 32 bytes; frame 0x10: ra sp+0x0
// Chunk release on the handle's SJ (+8136): sub_5890F0(handle, sj, n) as a tail call.
void sub_592938(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592938
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a1;
    sd(ra, sp, 0x0);
    link(ctx, 0x592944u);  // $ra first: the delay slot below depends on it
    lw(a1, a0, 8136);
    call(ctx, gen::fn_sub_5890F0_005890f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00592EF8 sub_592EF8 -- 64 bytes; frame 0x10: ra sp+0x0
// Raises a status code on the handle (sub_58BE40, tail call) unless it is 0, -2 or -3.
void sub_592EF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00592ef8
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = a1;
    sp = addiu(sp, -0x10);
    v0 = slti(v1, -3);
    sd(ra, sp, 0x0);
    a2 = slti(v1, -1);
    if (v0 == 0) {
        // 0x00592f10
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (a2 != 0) {
            // 0x00592f30 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x00592f18
        charge(ctx, 2);
        if (v1 != 0) {
            goto L_00592f20;
        }
        // 0x00592f30 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00592f20:
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00593608 sub_593608 -- 248 bytes; frame 0x40: s2 sp+0x30, s0 sp+0x20, s1 sp+0x28, ra sp+0x38
// Takes the header object's video record (sub_593700): copies its 44-byte time record to +3436 and decodes its
//   sequence header (sub_5796D0, {+56, +568}); a failure raises 0xFF000F1B, success sets *a3 = 1.
void sub_593608(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593608
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x30);
    s2 = a2;
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(s1, sp, 0x28);
    s1 = a0;
    sd(ra, sp, 0x38);
    link(ctx, 0x593628u);  // $ra first: the delay slot below depends on it
    sw(zero, s2, 0);
    call(ctx, gen::fn_sub_593700_00593700);
    a0 = v0;
    if (a0 == 0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x0059363c
        charge(ctx, 3);
        lw(v1, a0, 0);
        v0 = 0;
        if (v1 != 0) {
            // 0x00593648
            charge(ctx, 34);
            ldl(v0, a0, 19);
            ldr(v0, a0, 12);
            ldl(v1, a0, 27);
            ldr(v1, a0, 20);
            ldl(a1, a0, 35);
            ldr(a1, a0, 28);
            ldl(a2, a0, 43);
            ldr(a2, a0, 36);
            sdl(v0, s1, 3443);
            sdr(v0, s1, 3436);
            sdl(v1, s1, 3451);
            sdr(v1, s1, 3444);
            sdl(a1, s1, 3459);
            sdr(a1, s1, 3452);
            sdl(a2, s1, 3467);
            sdr(a2, s1, 3460);
            ldl(v0, a0, 51);
            ldr(v0, a0, 44);
            lw(v1, a0, 52);
            sdl(v0, s1, 3475);
            sdr(v0, s1, 3468);
            sw(v1, s1, 3476);
            v1 = addiu(a0, 56);
            lw(a0, s0, 0);
            a1 = sp;
            lw(v0, v1, 512);
            a2 = addiu(sp, 0x10);
            sw(v1, sp, 0x0);
            link(ctx, 0x5936B8u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x4);
            call(ctx, gen::fn_sub_5796D0_005796d0);
            a1 = lui(0xFF00);
            a0 = s1;
            a1 = a1 | 0xF1B;
            if (v0 == 0) {
                // 0x005936e0
                charge(ctx, 2);
                v1 = 1;
                sw(v1, s2, 0);
                goto L_005936e8;
            }
            // 0x005936d0
            charge(ctx, 4);
            jal(ctx, 0x5936D0u, gen::fn_sub_58BE40_0058be40);
            ld(s0, sp, 0x20);
            // 0x005936ec (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s1, sp, 0x28);
            ld(s2, sp, 0x30);
            ld(ra, sp, 0x38);
            sp = addiu(sp, 0x40);
            return;
        }
    L_005936e8:
        charge(ctx, 1);
        ld(s0, sp, 0x20);
    }
    // 0x005936ec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005938C0 sub_5938C0 -- 64 bytes; leaf frame (no stack)
// The frame record (vdec::kFrames, 16 x 240 bytes) whose shown mark (frm::kShown) equals $a1, or 0.
void sub_5938C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005938c0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, sfd::kVdecWork);
    a2 = 0;
    a0 = addiu(v0, 384);
    lw(v1, a0, 88);
    for (;;) {
        // 0x005938d0
        charge(ctx, 3);
        v0 = a0;
        a0 = addiu(a0, 240);
        if (v1 == a1) {
            break;
        }
        // 0x005938dc
        charge(ctx, 6);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 16);
        if (v0 == 0) {
            goto L_005938f4_3;
        }
        lw(v1, a0, 88);
        backedge(ctx);
    }
    // 0x005938f8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_005938f4_3:
    charge(ctx, 1);
    v0 = 0;
    // 0x005938f8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593948 sub_593948 -- 16 bytes; leaf frame (no stack)
// Sets the video-decoder work's end mark (vdec::kEndMark) and returns 1.
void sub_593948(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00593948
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kVdecWork);
    v0 = 1;
    sw(v0, v1, 124);
}

// 0x00593AA0 sub_593AA0 -- 16 bytes; leaf frame (no stack)
// Clears *p when p is not null.
void sub_593AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00593aa0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        sw(zero, a0, 0);
    }
    // 0x00593aa8
    charge(ctx, 2);
}

// 0x00593AC8 sub_593AC8 -- 20 bytes; leaf frame (no stack)
// Sets *p = 4 when p is not null; returns 4.
void sub_593AC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00593ac8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 4;
    if (a0 != 0) {
        // 0x00593ad0
        charge(ctx, 1);
        sw(v0, a0, 0);
    }
    // 0x00593ad4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00593B10 sub_593B10 -- 40 bytes; leaf frame (no stack)
// A frame state step: 4 -> 2, anything else -> 0 (p not null); returns 2 or 4.
void sub_593B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00593b10
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 4;
    if (a0 == 0) {
        // 0x00593b30 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00593b18
    charge(ctx, 3);
    lw(v1, a0, 0);
    if (v1 != v0) {
        sw(zero, a0, 0);
        // 0x00593b30 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00593b24
    charge(ctx, 3);
    v0 = 2;
    sw(v0, a0, 0);
}

// 0x00593BF8 sub_593BF8 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The displayed frame's {buffer, size} (frame +84 of sub_593E08) to *a1 / *a2, or 0 / 0.
void sub_593BF8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593bf8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a2;
    jal(ctx, 0x593C0Cu, gen::fn_sub_593E08_00593e08);
    if (v0 == 0) {
        sw(zero, s0, 0);
    } else {
        // 0x00593c1c
        charge(ctx, 3);
        lw(v1, v0, 84);
        if (v1 == 0) {
            // 0x00593c28
            charge(ctx, 1);
            sw(zero, s0, 0);
            goto L_00593c2c;
        }
        lw(v0, v1, 4);
        // 0x00593c38
        charge(ctx, 3);
        lw(v1, v1, 0);
        sw(v0, s1, 0);
        sw(v1, s0, 0);
        // 0x00593c44 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00593c2c:
    charge(ctx, 2);
    sw(zero, s1, 0);
    // 0x00593c44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00593C58 sub_593C58 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The frame-ready query: with a valid handle, sub_593CE8; during step play (+88 == 1) with fewer frames shown
//   (+2412) than asked (+2408), one less when positive. A bad handle raises 0xFF000187 and gives 0.
void sub_593C58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00593c58
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x593C68u, gen::fn_sub_58C060_0058c060);
    s1 = v0;
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x187;
    if (s1 == 0) {
        // 0x00593c98
        charge(ctx, 7);
        jal(ctx, 0x593C98u, gen::fn_sub_593CE8_00593ce8);
        v1 = 1;
        a0 = v0;
        lw(v0, s0, 88);
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = a0;
        if (!cc) {
            // 0x00593cb4
            charge(ctx, 5);
            lw(v0, s0, 2412);
            lw(v1, s0, 2408);
            v0 = slt(v0, v1);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = a0;
            if (!cc) {
                // 0x00593cc8
                charge(ctx, 3);
                v0 = slt(s1, a0);
                a0 = subu(a0, v0);
                v0 = a0;
            }
        }
    } else {
        // 0x00593c84
        charge(ctx, 4);
        a0 = 0;
        jal(ctx, 0x593C84u, gen::fn_sub_58BE40_0058be40);
        v0 = 0;
    }
    // 0x00593cd4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00593CE8 sub_593CE8 -- 200 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Under the lock: how many of the two oldest frames (sub_593EA0) are due (param 15, sub_59AEC0): 0, 1 or 2;
//   the second counts only while playing (status 4).
void sub_593CE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593ce8
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    a0 = sp;
    jal(ctx, 0x593CFCu, gen::fn_sub_58C100_0058c100);
    a1 = addiu(sp, 0x4);
    a2 = addiu(sp, 0x8);
    a0 = s0;
    jal(ctx, 0x593D0Cu, gen::fn_sub_593EA0_00593ea0);
    lw(v0, s0, 72);
    lw(v1, sp, 0x8);
    a0 = s0;
    v0 = v0 ^ 0x4;
    a1 = 15;
    if (v0 != 0) v1 = 0;
    link(ctx, 0x593D2Cu);  // $ra first: the delay slot below depends on it
    sw(v1, sp, 0x8);
    call(ctx, gen::fn_sub_599408_00599408);
    s1 = v0;
    lw(v0, sp, 0x4);
    if (v0 == 0) {
        s0 = 0;
    } else {
        // 0x00593d44
        charge(ctx, 2);
        a0 = s0;
        if (s1 != 0) {
            // 0x00593d4c
            charge(ctx, 5);
            lw(a2, v0, 60);
            link(ctx, 0x593D50u);  // $ra first: the delay slot below depends on it
            lw(a1, v0, 56);
            call(ctx, gen::fn_sub_59AEC0_0059aec0);
            if (v0 != 0) {
                goto L_00593d60;
            }
            s0 = 0;
            goto L_00593d90;
        }
    L_00593d60:
        charge(ctx, 3);
        lw(v0, sp, 0x8);
        if (v0 == 0) {
            s0 = 1;
        } else {
            // 0x00593d6c
            charge(ctx, 2);
            if (s1 == 0) {
                s0 = 2;
            } else {
                // 0x00593d74
                charge(ctx, 6);
                lw(a2, v0, 60);
                a0 = s0;
                link(ctx, 0x593D7Cu);  // $ra first: the delay slot below depends on it
                lw(a1, v0, 56);
                call(ctx, gen::fn_sub_59AEC0_0059aec0);
                if (v0 == 0) {
                    s0 = 1;
                } else {
                    // 0x00593d8c
                    charge(ctx, 1);
                    s0 = 2;
                }
            }
        }
    }
L_00593d90:
    charge(ctx, 8);
    a0 = sp;
    jal(ctx, 0x593D90u, gen::fn_sub_58C118_0058c118);
    v0 = s0;
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00593FD0 sub_593FD0 -- 24 bytes; leaf frame (no stack)
// Increments the counter +92 (saturating at 0 on overflow) and returns the old value.
void sub_593FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00593fd0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 92);
    v1 = addiu(v0, 1);
    a1 = slti(v1, 0);
    if (a1 != 0) v1 = 0;
    sw(v1, a0, 92);
}

// 0x00594B18 sub_594B18 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the semaphore (+64, _sceWaitSema / _sceSignalSema): +20 = (+20 + 2051) rounded down to 2048.
void sub_594B18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594b18
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x594B28u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 64);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    lw(v1, s0, 20);
    lw(a0, s0, 64);
    v0 = addiu(v1, 2051);
    v1 = addiu(v1, 4098);
    a1 = slti(v0, 0);
    ld(ra, sp, 0x8);
    if (a1 != 0) v0 = v1;
    v0 = sra(v0, 11);
    v0 = sll(v0, 11);
    sw(v0, s0, 20);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__sceSignalSema_00503180(ctx);  // tail call
}

// 0x00594E50 sub_594E50 -- 12 bytes; leaf frame (no stack)
// The work record's word +4604.
void sub_594E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00594e50
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, sfd::kVdecWork);
    lw(v0, v1, 4604);
}

// 0x00594E60 sub_594E60 -- 100 bytes; frame 0x10: ra sp+0x0
// Sets the global flag 0x9ACBB8, stores *a1 in 0x9ACBC0 and in the work record (+4600), raises 0xFF000F40
//   (sub_58BE40) and returns 1.
void sub_594E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00594e60
    enter(ctx, 25);  // entry check point + this block's cycles
    v1 = 0x9B0000;
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    sw(v0, v1, -13384);  // 0x9ACBB8
    v0 = 0x9B0000;
    a3 = a1;
    t0 = addiu(v0, -13376);  // &0x9ACBC0
    ldl(v1, a3, 7);
    ldr(v1, a3, 0);
    sdl(v1, t0, 7);  // 0x9ACBC7
    sdr(v1, t0, 0);  // 0x9ACBC0
    a1 = lui(0xFF00);
    a0 = a2;
    lw(v0, a2, sfd::kVdecWork);
    ldl(t1, a3, 7);
    ldr(t1, a3, 0);
    sdl(t1, v0, 4607);
    sdr(t1, v0, 4600);
    a1 = a1 | 0xF40;
    jal(ctx, 0x594EACu, gen::fn_sub_58BE40_0058be40);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00594F68 sub_594F68 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sceMpeg callback: in abort mode (+4416 == 1) aborts the picture (sceMpegGetPictureAbort); else flushes the
//   input ring (sub_5944A8) and, when +4412 is set and the ring's +16 is 0, sets +4416, feeds the 16-byte end code
//   0x7CA0E8 (sub_594EC8), copies +24 to +20 and flushes again. Returns 1.
void sub_594F68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00594f68
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = 1;
    sd(ra, sp, 0x18);
    lw(v0, a2, sfd::kVdecWork);
    s1 = addiu(v0, 4392);
    a0 = addiu(v0, vdec::kMpeg);
    lw(v1, s1, 24);
    s0 = addiu(v0, vdec::kViBuf);
    if (v1 != s2) {
        // 0x00594fa8
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x594FA8u, gen::fn_sub_5944A8_005944a8);
        lw(v1, s1, 20);
        v0 = 1;
        if (v1 != 0) {
            // 0x00594fbc
            charge(ctx, 3);
            lw(v0, s0, 16);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x00594fc8
                charge(ctx, 11);
                sw(s2, s1, 24);
                a1 = 0x7D0000;
                a0 = s0;
                a1 = addiu(a1, -24344);  // &0x7CA0E8
                a2 = 16;
                jal(ctx, 0x594FD8u, gen::fn_sub_594EC8_00594ec8);
                lw(v1, s0, 24);
                a0 = s0;
                link(ctx, 0x594FE8u);  // $ra first: the delay slot below depends on it
                sw(v1, s0, 20);
                call(ctx, gen::fn_sub_5944A8_005944a8);
                v0 = 1;
            }
        }
    } else {
        // 0x00594f98
        charge(ctx, 4);
        jal(ctx, 0x594F98u, gen::fn_sceMpegGetPictureAbort_00500ba8);
        v0 = 1;
    }
    // 0x00594ff4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00595788 sub_595788 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The handle's word +80 for a valid handle; else raises 0xFF000141 and returns 0.
void sub_595788(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595788
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x595794u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x141;
    if (v0 == 0) {
        // 0x005957c0
        charge(ctx, 1);
        lw(v0, s0, 80);
    } else {
        // 0x005957ac
        charge(ctx, 4);
        jal(ctx, 0x5957ACu, gen::fn_sub_58BE40_0058be40);
        v0 = 0;
    }
    // 0x005957c4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005958F8 sub_5958F8 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// In states 3 and 4 (+76), sub_59AC28 and then transfer call (slot 7, method 8) with a1 (sub_59BC20); else 0.
void sub_5958F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005958f8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v1, s0, 76);
    v1 = addiu(v1, -3);
    v1 = sltiu(v1, 2);
    s1 = a1;
    if (v1 == 0) {
        // 0x00595948
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00595924
    charge(ctx, 9);
    jal(ctx, 0x595924u, gen::fn_sub_59AC28_0059ac28);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x00595960
    charge(ctx, 10);
    sp = addiu(sp, -0x10);
    a3 = a1;
    a2 = 8;
    t0 = 0;
    sd(ra, sp, 0x0);
    a1 = 7;
    jal(ctx, 0x595974u, gen::fn_sub_59BC20_0059bc20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00595A50 sub_595A50 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets parameter 30 to a1 (sub_599100) for a valid handle; else raises 0xFF000145.
void sub_595A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595a50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x595A64u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a2 = s0;
    a1 = a1 | 0x145;
    if (v0 != 0) {
        // 0x00595a80
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00595a98
    charge(ctx, 9);
    a0 = s1;
    a1 = 30;
    jal(ctx, 0x595A9Cu, gen::fn_sub_599100_00599100);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00595AC0 sub_595AC0 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets parameter 29 to a1 (sub_599100) for a valid handle; else raises 0xFF000146.
void sub_595AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595ac0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x595AD4u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a2 = s0;
    a1 = a1 | 0x146;
    if (v0 != 0) {
        // 0x00595af0
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00595b08
    charge(ctx, 9);
    a0 = s1;
    a1 = 29;
    jal(ctx, 0x595B0Cu, gen::fn_sub_599100_00599100);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00596340 sub_596340 -- 8 bytes; leaf frame (no stack)
// The handle's word +72.
void sub_596340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00596340
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 72);
}

// 0x005965E0 sub_5965E0 -- 224 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Whether the input is short: a dry input (sub_5966C0), a stalled param-5 / param-6 stream (sub_596760 /
//   sub_596818), or the clock (sub_59A168) past the buffered time (+4020 less param 69 in microseconds,
//   sub_57BAF0 / sub_59A560).
void sub_5965E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005965e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    jal(ctx, 0x5965F0u, gen::fn_sub_5966C0_005966c0);
    a0 = s1;
    a1 = 5;
    if (v0 == 0) {
        // 0x00596604
        charge(ctx, 5);
        jal(ctx, 0x596604u, gen::fn_sub_599408_00599408);
        v1 = 1;
        a0 = s1;
        if (v0 == v1) {
            // 0x00596618
            charge(ctx, 4);
            jal(ctx, 0x596618u, gen::fn_sub_596760_00596760);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                goto L_00596628;
            }
            // 0x005966ac (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x10);
            ld(s1, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_00596628:
        charge(ctx, 6);
        a0 = s1;
        a1 = 6;
        jal(ctx, 0x59662Cu, gen::fn_sub_599408_00599408);
        v1 = 1;
        a0 = s1;
        if (v0 == v1) {
            // 0x00596640
            charge(ctx, 4);
            jal(ctx, 0x596640u, gen::fn_sub_596818_00596818);
            if (v0 != 0) {
                goto L_00596650;
            }
            a1 = sp;
            goto L_0059665c;
        }
        // 0x00596658
        charge(ctx, 1);
        a1 = sp;
    L_0059665c:
        charge(ctx, 20);
        a2 = addiu(sp, 0x4);
        a0 = s1;
        jal(ctx, 0x596660u, gen::fn_sub_59A168_0059a168);
        v1 = addiu(s1, sfd::kTimeRec);
        lw(s0, v1, 648);
        a0 = s1;
        a1 = 69;
        link(ctx, 0x596678u);  // $ra first: the delay slot below depends on it
        lw(s1, v1, 644);
        call(ctx, gen::fn_sub_599408_00599408);
        a1 = s0;
        a2 = 0xF0000;
        a0 = v0;
        a2 = a2 | 0x4240;
        jal(ctx, 0x59668Cu, gen::fn_sub_57BAF0_0057baf0);
        a3 = s0;
        lw(a0, sp, 0x0);
        a2 = subu(s1, v0);
        link(ctx, 0x5966A0u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x4);
        call(ctx, gen::fn_sub_59A560_0059a560);
        v0 = sltu(0, v0);
        // 0x005966ac (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00596650:
    charge(ctx, 2);
    v0 = 1;
    // 0x005966ac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00596818 sub_596818 -- 128 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Whether the current stream's buffer (slot +8204, 116-byte records from +4896) is at least 80% full: its SJ's
//   method +36 (jalr) against 80% of the capacity (+12).
void sub_596818(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596818
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v1, s0, 8204);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    s0 = addu(s0, v0);
    s0 = addiu(s0, 4896);
    lw(a0, s0, 4);
    lw(v1, a0, 0);
    lw(v0, v1, 36);
    a1 = 1;
    jalr(ctx, 0x596854u, v0.u());
    lw(a1, s0, 12);
    a0 = 100;
    v1 = sll(a1, 2);
    if (a0 == 0) {
        brk(ctx, 0x59686Cu, 0x7u);
    }
    // 0x00596870
    charge(ctx, 10);
    v1 = addu(v1, a1);
    ld(s0, sp, 0x0);
    v1 = sll(v1, 4);
    ld(ra, sp, 0x8);
    div(v1, a0);
    mflo(v1);
    v0 = slt(v0, v1);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00596B28 sub_596B28 -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Allocates through my_malloc_1; on failure sets the state +76 = 6, calls sub_597A18 and returns 0.
void sub_596B28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596b28
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x596B34u, gen::fn_my_malloc_1_00597448);
    a0 = s0;
    if (v0 == 0) {
        // 0x00596b44
        charge(ctx, 4);
        v0 = 6;
        link(ctx, 0x596B48u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 76);
        call(ctx, gen::fn_sub_597A18_00597a18);
        v0 = 0;
    }
    // 0x00596b54 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00597168 sub_597168 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Adds $a1 to +2388 and calls the callback in param 37 (sub_599408; jalr) with (handle, $a2, handle+2384) when
//   one is set.
void sub_597168(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597168
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    s0 = addiu(s1, 2384);
    lw(v0, s0, 4);
    v0 = addu(v0, a1);
    a1 = 37;
    link(ctx, 0x597194u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 4);
    call(ctx, gen::fn_sub_599408_00599408);
    a0 = s1;
    a1 = s2;
    a2 = s0;
    if (v0 != 0) {
        // 0x005971ac
        charge(ctx, 2);
        jalr(ctx, 0x5971ACu, v0.u());
    }
    // 0x005971b4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00597AA0 thread_leave_1 -- 228 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Takes a frame for step play: *a3 = 0, *a2 = -1; with a valid handle and API mode 2 (sub_597DC8), transfer
//   call (slot 6, method 11) and the user hook 0x7B47BC; a frame taken counts (+2408, the first remembers the
//   clock in +14208, sub_59B3A8) and returns 1. A bad handle raises 0xFF00013A.
void thread_leave_1(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00597aa0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x18);
    sw(zero, s1, 0);
    link(ctx, 0x597AC8u);  // $ra first: the delay slot below depends on it
    sw(v0, s2, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    if (v0 == 0) {
        // 0x00597af0
        charge(ctx, 5);
        a0 = s0;
        a1 = 2;
        jal(ctx, 0x597AF4u, gen::fn_sub_597DC8_00597dc8);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00597b04
            charge(ctx, 10);
            t0 = s2;
            a0 = s0;
            a1 = 6;
            a2 = 11;
            a3 = s1;
            jal(ctx, 0x597B14u, gen::fn_sub_59BC20_0059bc20);
            v1 = 0x7B0000;
            lw(v0, v1, 18364);  // 0x7B47BC
            if (v0 == 0) {
                lw(v1, s1, 0);
            } else {
                // 0x00597b2c
                charge(ctx, 4);
                lw(a1, s1, 0);
                a0 = s0;
                jalr(ctx, 0x597B30u, v0.u());
                lw(v1, s1, 0);
            }
            // 0x00597b3c
            charge(ctx, 2);
            v0 = 0;
            if (v1 != 0) {
                // 0x00597b44
                charge(ctx, 3);
                lw(v1, s0, 2408);
                if (v1 != 0) {
                    v1 = addiu(v1, 1);
                } else {
                    // 0x00597b50
                    charge(ctx, 5);
                    jal(ctx, 0x597B50u, gen::fn_sub_59B3A8_0059b3a8);
                    lw(v1, s0, 2408);
                    sd(v0, s0, 14208);
                    v1 = addiu(v1, 1);
                }
                // 0x00597b64
                charge(ctx, 2);
                v0 = 1;
                sw(v1, s0, 2408);
            }
        }
    } else {
        // 0x00597ad8
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x13A;
        jal(ctx, 0x597ADCu, gen::fn_sub_58BE40_0058be40);
        v0 = 0;
    }
    // 0x00597b6c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00597B88 sub_597B88 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Releases a step-play frame: with a valid handle and API mode 2, counts it (+2412) and makes transfer call
//   (slot 6, method 12). A bad handle raises 0xFF00013B.
void sub_597B88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597b88
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x597B9Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00597bb0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x13B;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00597bc8
    charge(ctx, 9);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x597BCCu, gen::fn_sub_597DC8_00597dc8);
    a0 = s0;
    t0 = s1;
    a1 = 6;
    a2 = 12;
    a3 = 0;
    if (v0 != 0) {
        // 0x00597c10
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00597bec
    charge(ctx, 8);
    lw(v0, s0, 2412);
    ld(s1, sp, 0x8);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x10);
    sw(v0, s0, 2412);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BC20_0059bc20(ctx);  // tail call
}

// 0x00597E98 sub_597E98 -- 136 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Sets up the handle's work ring (+5052, sub_597F20) over (buf, size) for a valid handle; a bad handle raises
//   0xFF000165. Nothing for a null buffer or a size <= 0.
void sub_597E98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597e98
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x18);
    if (s1 != 0) {
        // 0x00597ebc
        charge(ctx, 2);
        v0 = 0;
        if (i64(s0) <= 0) {
            // 0x00597f08 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            return;
        }
        // 0x00597ec4
        charge(ctx, 7);
        jal(ctx, 0x597EC4u, gen::fn_sub_58C060_0058c060);
        a1 = lui(0xFF00);
        a0 = 0;
        a1 = a1 | 0x165;
        a2 = s0;
        if (v0 == 0) {
            // 0x00597ef8
            charge(ctx, 3);
            a0 = addiu(s2, 5052);
            a1 = s1;
            jal(ctx, 0x597EFCu, gen::fn_sub_597F20_00597f20);
            goto L_00597f04;
        }
        // 0x00597ee0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
L_00597f04:
    charge(ctx, 1);
    v0 = 0;
    // 0x00597f08 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00597F20 sub_597F20 -- 124 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Sets up a ring of 16-byte entries: +0 = the buffer rounded up to 8 bytes (cleared with memset), +4 = its
//   entry count, count +8, write index +12 and read index +16 = 0.
void sub_597F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597f20
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a1;
    sd(s1, sp, 0x8);
    s1 = addiu(v1, 7);
    v0 = si(-8);
    sd(s0, sp, 0x0);
    s1 = s1 & v0;
    sd(s2, sp, 0x10);
    v1 = subu(s1, v1);
    a1 = 0;
    s0 = subu(a2, v1);
    s2 = a0;
    a2 = s0;
    sd(ra, sp, 0x18);
    a0 = s1;
    jal(ctx, 0x597F58u, gen::fn_memset_00521408);
    v1 = addiu(s0, 15);
    v0 = slti(s0, 0);
    if (v0 != 0) s0 = v1;
    sw(s1, s2, 0);
    s0 = sra(s0, 4);
    sw(zero, s2, 16);
    sw(s0, s2, 4);
    sw(zero, s2, 8);
    sw(zero, s2, 12);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00598030 sub_598030 -- 148 bytes; leaf frame (no stack)
// Pushes a 16-byte entry into the ring (full: *$a2 = 1, -1); the write index +12 wraps; *$a2 = 1 when it is
//   now full; 0.
void sub_598030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00598030
    enter(ctx, 6);  // entry check point + this block's cycles
    a3 = a0;
    t1 = a2;
    lw(v1, a3, 8);
    lw(v0, a3, 4);
    t0 = a1;
    if (v1 == v0) {
        // 0x00598048
        charge(ctx, 4);
        v1 = 1;
        v0 = si(-1);
        sw(v1, t1, 0);
        return;
    }
    // 0x00598058
    charge(ctx, 14);
    lw(a1, a3, 12);
    lw(v0, a3, 0);
    ld(a2, t0, 0);
    v1 = sll(a1, 4);
    v1 = addu(v1, v0);
    a0 = addiu(a1, 1);
    sd(a2, v1, 0);
    a2 = a0;
    ld(v0, t0, 8);
    sd(v0, v1, 8);
    lw(v1, a3, 4);
    a0 = slt(a0, v1);
    a1 = subu(a1, v1);
    if (a0 == 0) {
        // 0x00598090
        charge(ctx, 1);
        a2 = addiu(a1, 1);
    }
    // 0x00598094
    charge(ctx, 6);
    lw(v0, a3, 8);
    sw(a2, a3, 12);
    v0 = addiu(v0, 1);
    v1 = slt(v0, v1);
    sw(v0, a3, 8);
    if (v1 != 0) {
        // 0x005980b8
        charge(ctx, 1);
        sw(zero, t1, 0);
    } else {
        // 0x005980ac
        charge(ctx, 3);
        v0 = 1;
        sw(v0, t1, 0);
    }
    // 0x005980bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x00598140 sub_598140 -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Pops the entries before a matching one (sub_5981D8; read index +16, count +8) and copies the match to *$a2; -1
//   when none matches, 0 for an empty ring.
void sub_598140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598140
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x10);
    a2 = a3;
    lw(v0, s0, 8);
    a3 = t0;
    if (v0 != 0) {
        // 0x00598168
        charge(ctx, 6);
        jal(ctx, 0x598168u, gen::fn_sub_5981D8_005981d8);
        a2 = v0;
        v0 = si(-1);
        if (a2 != v0) {
            // 0x00598180
            charge(ctx, 17);
            lw(v0, s0, 16);
            lw(v1, s0, 4);
            lw(a1, s0, 8);
            v0 = addu(v0, a2);
            a0 = subu(v0, v1);
            v1 = slt(v0, v1);
            if (v1 == 0) v0 = a0;
            lw(v1, s0, 0);
            a1 = subu(a1, a2);
            sw(v0, s0, 16);
            sw(a1, s0, 8);
            a0 = sll(v0, 4);
            a0 = addu(a0, v1);
            ld(v0, a0, 0);
            sd(v0, s1, 0);
            ld(v1, a0, 8);
            sd(v1, s1, 8);
            goto L_005981c4;
        }
        ld(s0, sp, 0x0);
        // 0x005981c8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_005981c4:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005981c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005981D8 sub_5981D8 -- 200 bytes; leaf frame (no stack)
// Searches the ring from the read index for the first entry whose range (+8 start, +12 length) fits the window
//   ($a1, $a2, $a3) by the three unsigned compares; its distance from the read index, or -1.
void sub_5981D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x005981d8
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 8);
    t4 = addu(a2, a3);
    lw(t3, a0, 4);
    t2 = 0;
    lw(t1, a0, 16);
    if (i64(v0) <= 0) {
        // 0x00598298 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    // 0x005981f0
    charge(ctx, 6);
    lw(t7, a0, 0);
    a2 = sltu(a1, a2);
    t6 = v0;
    t5 = sltu(a1, t4);
    v0 = sll(t1, 4);
    for (;;) {
        // 0x00598208
        charge(ctx, 8);
        v0 = addu(t7, v0);
        lw(v1, v0, 8);
        lw(a0, v0, 12);
        t0 = sltu(a1, v1);
        a0 = addu(v1, a0);
        v0 = sltu(t4, a0);
        v1 = t0;
        if (v0 == 0) {
            // 0x00598228
            charge(ctx, 2);
            v0 = addiu(t1, 1);
            if (t0 != 0) {
                goto L_00598274;
            }
            // 0x00598230
            charge(ctx, 3);
            v0 = sltu(a1, a0);
            if (v0 == 0) {
                v0 = addiu(t1, 1);
                goto L_00598274;
            }
            // 0x0059823c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = t2;
            return;
        }
        // 0x00598248
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00598250
            charge(ctx, 2);
            if (t5 == 0) {
                goto L_00598258;
            }
            backedge(ctx);
            // 0x0059823c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = t2;
            return;
        }
    L_00598258:
        charge(ctx, 2);
        v0 = addiu(t1, 1);
        if (a2 == 0) {
            // 0x00598260
            charge(ctx, 4);
            v0 = subu(a0, a3);
            v0 = sltu(a1, v0);
            if (v0 == 0) {
                // 0x00598270
                charge(ctx, 1);
                v0 = addiu(t1, 1);
                goto L_00598274;
            }
            backedge(ctx);
            // 0x0059823c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = t2;
            return;
        }
    L_00598274:
        charge(ctx, 3);
        v1 = slt(v0, t3);
        t2 = addiu(t2, 1);
        if (v1 == 0) {
            // 0x00598280
            charge(ctx, 2);
            v0 = subu(t1, t3);
            v0 = addiu(v0, 1);
        }
        // 0x00598288
        charge(ctx, 4);
        t1 = v0;
        v0 = slt(t2, t6);
        if (v0 == 0) {
            break;
        }
        v0 = sll(t1, 4);
        backedge(ctx);
    }
    // 0x00598298 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = si(-1);
}

// 0x00598348 sub_598348 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Clears a timing record (sub_575880(rec, 0, 886)), its sub-records (sub_5983B8) and sets its defaults
//   (+3496..+3540: -1, -8, 1). Returns -1.
void sub_598348(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598348
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a2 = 886;
    jal(ctx, 0x59835Cu, gen::fn_sub_575880_00575880);
    a0 = s0;
    jal(ctx, 0x598364u, gen::fn_sub_5983B8_005983b8);
    sw(zero, s0, 3496);
    v0 = si(-1);
    v1 = si(-8);
    a0 = 1;
    sw(v0, s0, 3540);
    sw(v1, s0, 3528);
    sw(a0, s0, 3532);
    sw(zero, s0, 3500);
    sw(v1, s0, 3504);
    sw(a0, s0, 3508);
    sw(v0, s0, 3512);
    sw(v0, s0, 3516);
    sw(zero, s0, 3520);
    sw(zero, s0, 3524);
    sw(zero, s0, 3536);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005983B8 sub_5983B8 -- 180 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Clears the timing record's sub-records: words 0..2, the header info (+12, sub_58B140), +2208, +2768 (with a
//   picture record at +2780, sub_599A30) and +3340 (+3348 = 1). Returns 1.
void sub_5983B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005983b8
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, 2208);
    sd(s2, sp, 0x10);
    s2 = addiu(s0, 3340);
    sd(s3, sp, 0x18);
    s3 = addiu(s0, 2768);
    sd(ra, sp, 0x20);
    a0 = addiu(s0, 12);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    link(ctx, 0x5983ECu);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 8);
    call(ctx, gen::fn_sub_58B140_0058b140);
    sw(zero, s1, 0);
    sw(zero, s1, 44);
    a1 = 0x7FFF0000;
    sw(zero, s1, 4);
    a0 = addiu(s0, 2780);
    sw(zero, s1, 8);
    a1 = a1 | 0xFFFF;
    sw(zero, s1, 12);
    sw(zero, s1, 16);
    sw(zero, s1, 40);
    sd(zero, s1, 24);
    sw(zero, s3, 8);
    sd(zero, s1, 32);
    sw(zero, s3, 0);
    link(ctx, 0x59842Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s3, 4);
    call(ctx, gen::fn_sub_599A30_00599a30);
    sw(zero, s2, 0);
    v0 = 1;
    sw(zero, s2, 4);
    sw(v0, s2, 8);
    sw(zero, s2, 12);
    sw(zero, s2, 16);
    sw(zero, s2, 20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00598470 sub_598470 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets the handle's timing record pointer (+14000) for a valid handle; else raises 0xFF000151.
void sub_598470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598470
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x598484u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 == 0) {
        // 0x005984b0
        charge(ctx, 6);
        sw(s1, s0, sfd::kHdrObj);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00598498
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = a1 | 0x151;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00598688 sub_598688 -- 356 bytes; frame 0x50: s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s0 sp+0x10, ra sp+0x40
// Picks the timing source once (record word 0): the audio (+3340, sub_5987F0) or the video (+2768,
//   sub_598870) when present and ready, else the header (+2208) with its rate from the stream (+24, +3524 in
//   ms, sub_57BAF0) or the header version (sub_58BBB0 < 108 scales by 2048 / 2018); then sub_599020.
void sub_598688(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00598688
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    s5 = a0;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x40);
    lw(s0, s5, sfd::kHdrObj);
    lw(v0, s0, 0);
    s3 = addiu(s0, 12);
    s4 = addiu(s0, 2208);
    s1 = addiu(s0, 2768);
    s2 = addiu(s0, 3340);
    if (v0 == 0) {
        // 0x005986c8
        charge(ctx, 5);
        a1 = s2;
        a2 = sp;
        jal(ctx, 0x5986CCu, gen::fn_sub_5987F0_005987f0);
        if (v0 != 0) {
            ld(s0, sp, 0x10);
        } else {
            // 0x005986dc
            charge(ctx, 6);
            a0 = s5;
            a1 = s1;
            a2 = addiu(sp, 0x4);
            jal(ctx, 0x5986E4u, gen::fn_sub_598870_00598870);
            if (v0 != 0) {
                ld(s0, sp, 0x10);
            } else {
                // 0x005986f4
                charge(ctx, 4);
                a0 = s5;
                jal(ctx, 0x5986F4u, gen::fn_sub_5988F0_005988f0);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 1;
                if (!cc) {
                    // 0x00598704
                    charge(ctx, 4);
                    sw(v0, s4, 0);
                    lw(v1, s3, 0);
                    if (v1 == 0) {
                        lw(a1, s4, 4);
                    } else {
                        // 0x00598714
                        charge(ctx, 3);
                        lw(v0, s3, 12);
                        if (i64(v0) <= 0) {
                            // 0x00598748
                            charge(ctx, 5);
                            a0 = s5;
                            jal(ctx, 0x598748u, gen::fn_sub_58BBB0_0058bbb0);
                            v0 = slti(v0, 108);
                            if (v0 == 0) {
                                lw(a1, s4, 4);
                            } else {
                                // 0x0059875c
                                charge(ctx, 4);
                                lw(v0, s4, 4);
                                v1 = 2018;
                                if (v1 == 0) {
                                    brk(ctx, 0x598768u, 0x7u);
                                }
                                // 0x0059876c
                                charge(ctx, 4);
                                v0 = sll(v0, 11);
                                div(v0, v1);
                                mflo(v0);
                                a1 = v0;
                            }
                        } else {
                            // 0x00598720
                            charge(ctx, 3);
                            lw(a0, s0, 3524);
                            lw(a2, s3, 52);
                            if (i64(a0) > 0) {
                                // 0x0059872c
                                charge(ctx, 2);
                                if (i64(a2) > 0) {
                                    // 0x00598734
                                    charge(ctx, 2);
                                    a1 = 1000;
                                    jal(ctx, 0x598734u, gen::fn_sub_57BAF0_0057baf0);
                                    goto L_0059873c;
                                }
                                a1 = v0;
                                goto L_0059877c;
                            }
                        L_0059873c:
                            charge(ctx, 2);
                            a1 = v0;
                        }
                    }
                L_0059877c:
                    charge(ctx, 2);
                    lw(v1, s4, 8);
                    goto L_005987b0;
                }
                // 0x00598788
                charge(ctx, 3);
                lw(v0, sp, 0x4);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                lw(v0, sp, 0x0);
                if (!cc) {
                    // 0x00598794
                    charge(ctx, 3);
                    lw(v1, s1, 8);
                    lw(a1, s1, 4);
                    goto L_005987b0;
                }
                // 0x005987a0
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x005987a8
                    charge(ctx, 2);
                    lw(v1, s2, 8);
                    lw(a1, s2, 4);
                L_005987b0:
                    charge(ctx, 6);
                    v0 = 1;
                    sw(a1, s0, 4);
                    sw(v0, s0, 0);
                    a0 = s5;
                    link(ctx, 0x5987C0u);  // $ra first: the delay slot below depends on it
                    sw(v1, s0, 8);
                    call(ctx, gen::fn_sub_599020_00599020);
                    goto L_005987c8;
                }
                ld(s0, sp, 0x10);
            }
        }
        // 0x005987cc (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(ra, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_005987c8:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x005987cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x005987F0 sub_5987F0 -- 128 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// Audio timing check: when stream 3 is active (sub_59BCD0) and param 6 is 1, *$a2 = 1 and returns whether
//   *$a1 is 0; else *$a2 = 0, 0.
void sub_5987F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005987f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a1;
    a1 = 3;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x18);
    s0 = a0;
    jal(ctx, 0x598810u, gen::fn_sub_59BCD0_0059bcd0);
    a0 = s0;
    a1 = 6;
    if (v0 == 0) {
        // 0x00598850
        charge(ctx, 1);
        sw(zero, s1, 0);
    L_00598854:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00598824
        charge(ctx, 6);
        jal(ctx, 0x598824u, gen::fn_sub_599408_00599408);
        v1 = v0;
        v0 = 1;
        if (v1 != v0) {
            sw(zero, s1, 0);
            goto L_00598854;
        }
        // 0x0059883c
        charge(ctx, 4);
        sw(v1, s1, 0);
        lw(v0, s2, 0);
        v0 = sltiu(v0, 1);
    }
    // 0x00598858 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00598870 sub_598870 -- 128 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// Video timing check: when stream 2 is active and param 5 is 1, *$a2 = 1 and returns whether *$a1 is 0; else
//   *$a2 = 0, 0.
void sub_598870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598870
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a1;
    a1 = 2;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x18);
    s0 = a0;
    jal(ctx, 0x598890u, gen::fn_sub_59BCD0_0059bcd0);
    a0 = s0;
    a1 = 5;
    if (v0 == 0) {
        // 0x005988d0
        charge(ctx, 1);
        sw(zero, s1, 0);
    L_005988d4:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x005988a4
        charge(ctx, 6);
        jal(ctx, 0x5988A4u, gen::fn_sub_599408_00599408);
        v1 = v0;
        v0 = 1;
        if (v1 != v0) {
            sw(zero, s1, 0);
            goto L_005988d4;
        }
        // 0x005988bc
        charge(ctx, 4);
        sw(v1, s1, 0);
        lw(v0, s2, 0);
        v0 = sltiu(v0, 1);
    }
    // 0x005988d8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005988F0 sub_5988F0 -- 32 bytes; frame 0x10: ra sp+0x0
// Whether stream 1 is active (sub_59BCD0).
void sub_5988F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005988f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 1;
    jal(ctx, 0x5988F8u, gen::fn_sub_59BCD0_0059bcd0);
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x00598A90 sub_598A90 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// *$a3 = 0 at the end (+3520), else the muldiv (sub_57BAF0) of the time +3496 with the caller's $a1 / $a2.
void sub_598A90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598a90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(ra, sp, 0x8);
    lw(v0, v1, 3520);
    a0 = v0;
    if (v0 != 0) {
        // 0x00598ab0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        // 0x00598ae0
        charge(ctx, 2);
        sw(zero, a3, 0);
        return;
    }
    // 0x00598ac0
    charge(ctx, 7);
    link(ctx, 0x598AC0u);  // $ra first: the delay slot below depends on it
    lw(a0, v1, 3496);
    call(ctx, gen::fn_sub_57BAF0_0057baf0);
    sw(v0, s0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00598B90 sub_598B90 -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// *$a2 = 0 at the end (+3520) or for a time +3496 <= 0, else muldiv($a1, 1000, +3496); *$a3 = 1000. Returns
//   1000.
void sub_598B90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598b90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(ra, sp, 0x10);
    t0 = a1;
    lw(v0, v1, 3520);
    a0 = v0;
    if (v0 != 0) {
        // 0x00598bbc
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        // 0x00598c18
        charge(ctx, 4);
        v0 = 1000;
        sw(zero, a2, 0);
        sw(v0, a3, 0);
        return;
    }
    // 0x00598bd0
    charge(ctx, 3);
    lw(v0, v1, 3496);
    a2 = v0;
    if (i64(v0) > 0) {
        // 0x00598be8
        charge(ctx, 4);
        a0 = t0;
        a1 = 1000;
        jal(ctx, 0x598BECu, gen::fn_sub_57BAF0_0057baf0);
        sw(v0, s0, 0);
    } else {
        // 0x00598bdc
        charge(ctx, 2);
        sw(zero, s0, 0);
    }
    // 0x00598bf8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1000;
    ld(s0, sp, 0x0);
    sw(v0, s1, 0);
    ld(ra, sp, 0x10);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00598D20 sub_598D20 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets the timing record's word +3524 for a valid handle with a timing record (+14000) and calls sub_599020;
//   a bad handle raises 0xFF000159.
void sub_598D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598d20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x598D34u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00598d48
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x159;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598d60
    charge(ctx, 3);
    lw(v1, s0, sfd::kHdrObj);
    if (v1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00598d6c
        charge(ctx, 5);
        sw(s1, v1, 3524);
        a0 = s0;
        jal(ctx, 0x598D70u, gen::fn_sub_599020_00599020);
        v0 = 0;
        ld(s0, sp, 0x0);
    }
    // 0x00598d80 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
