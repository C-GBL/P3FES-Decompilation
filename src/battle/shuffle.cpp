// Slice shuffle: Shuffle Time (game/include/p3fes/game/shuffle.h has the records and every function's role),
// hand-decompiled from SLUS_216.21 starting from p3fes_handgen's faithful bodies: one statement per instruction on the
// register view of game/include/p3fes/game/hg_cpu.h, the recompiled body's cycle charges (`charge`, one per block,
// charged where the block starts) and back-edge checks (`backedge`), $ra = the original link at every jal / jalr,
// the original frames and spills. The readability pass names the record offsets below and documents each function;
// it changes no operand, so every register holds at every check point, call and return what the original holds there
// (tests/game/test_shuffle.cpp checks it pair by pair; tools/ours/audit/audit_faithful.py proves it per function).
// K_Assert(file, line) is sub_19D3F0 (`jr $ra` in retail): the bad-input paths continue as the original does.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/shuffle.h"

namespace p3fes::recomp_gen {
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16F380_0016f380(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_174B40_00174b40(p3fes::EEContext&);
void fn_sub_1756F0_001756f0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1F30B0_001f30b0(p3fes::EEContext&);
void fn_sub_1F30D0_001f30d0(p3fes::EEContext&);
void fn_sub_1F4650_001f4650(p3fes::EEContext&);
void fn_sub_1F48D0_001f48d0(p3fes::EEContext&);
void fn_sub_1F4910_001f4910(p3fes::EEContext&);
void fn_sub_1F4930_001f4930(p3fes::EEContext&);
void fn_sub_1F4970_001f4970(p3fes::EEContext&);
void fn_sub_1F4990_001f4990(p3fes::EEContext&);
void fn_sub_1F5510_001f5510(p3fes::EEContext&);
void fn_sub_1F5650_001f5650(p3fes::EEContext&);
void fn_sub_1F56B0_001f56b0(p3fes::EEContext&);
void fn_sub_1F5760_001f5760(p3fes::EEContext&);
void fn_sub_1F58F0_001f58f0(p3fes::EEContext&);
void fn_sub_1F65E0_001f65e0(p3fes::EEContext&);
void fn_sub_1F6D20_001f6d20(p3fes::EEContext&);
void fn_sub_1F9630_001f9630(p3fes::EEContext&);
void fn_sub_1F9680_001f9680(p3fes::EEContext&);
void fn_sub_1F9770_001f9770(p3fes::EEContext&);
void fn_sub_1F9800_001f9800(p3fes::EEContext&);
void fn_sub_1F9890_001f9890(p3fes::EEContext&);
void fn_sub_20B250_0020b250(p3fes::EEContext&);
void fn_sub_20C400_0020c400(p3fes::EEContext&);
void fn_sub_20C500_0020c500(p3fes::EEContext&);
void fn_sub_20C660_0020c660(p3fes::EEContext&);
void fn_sub_20CC80_0020cc80(p3fes::EEContext&);
void fn_sub_20E2C0_0020e2c0(p3fes::EEContext&);
void fn_sub_20E610_0020e610(p3fes::EEContext&);
void fn_sub_21A670_0021a670(p3fes::EEContext&);
void fn_sub_21A760_0021a760(p3fes::EEContext&);
void fn_sub_21A920_0021a920(p3fes::EEContext&);
void fn_sub_21AB80_0021ab80(p3fes::EEContext&);
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);
void fn_sub_23C280_0023c280(p3fes::EEContext&);
void fn_sub_24DA60_0024da60(p3fes::EEContext&);
void fn_sub_24DAF0_0024daf0(p3fes::EEContext&);
void fn_sub_24F090_0024f090(p3fes::EEContext&);
void fn_sub_24F960_0024f960(p3fes::EEContext&);
void fn_sub_24F9F0_0024f9f0(p3fes::EEContext&);
void fn_sub_24FAF0_0024faf0(p3fes::EEContext&);
void fn_sub_24FDA0_0024fda0(p3fes::EEContext&);
void fn_sub_24FE00_0024fe00(p3fes::EEContext&);
void fn_sub_250CF0_00250cf0(p3fes::EEContext&);
void fn_sub_2534D0_002534d0(p3fes::EEContext&);
void fn_sub_253560_00253560(p3fes::EEContext&);
void fn_sub_253600_00253600(p3fes::EEContext&);
void fn_sub_2536B0_002536b0(p3fes::EEContext&);
void fn_sub_2537F0_002537f0(p3fes::EEContext&);
void fn_sub_253920_00253920(p3fes::EEContext&);
void fn_sub_254B90_00254b90(p3fes::EEContext&);
void fn_sub_254E10_00254e10(p3fes::EEContext&);
void fn_sub_254F20_00254f20(p3fes::EEContext&);
void fn_sub_254F70_00254f70(p3fes::EEContext&);
void fn_sub_2550B0_002550b0(p3fes::EEContext&);
void fn_sub_255130_00255130(p3fes::EEContext&);
void fn_sub_255170_00255170(p3fes::EEContext&);
void fn_sub_255190_00255190(p3fes::EEContext&);
void fn_sub_2551B0_002551b0(p3fes::EEContext&);
void fn_sub_2551D0_002551d0(p3fes::EEContext&);
void fn_sub_255390_00255390(p3fes::EEContext&);
void fn_sub_255440_00255440(p3fes::EEContext&);
void fn_sub_2554F0_002554f0(p3fes::EEContext&);
void fn_sub_255570_00255570(p3fes::EEContext&);
void fn_sub_255810_00255810(p3fes::EEContext&);
void fn_sub_255B20_00255b20(p3fes::EEContext&);
void fn_sub_255F30_00255f30(p3fes::EEContext&);
void fn_sub_255F80_00255f80(p3fes::EEContext&);
void fn_sub_255FE0_00255fe0(p3fes::EEContext&);
void fn_sub_256030_00256030(p3fes::EEContext&);
void fn_sub_256110_00256110(p3fes::EEContext&);
void fn_sub_2561C0_002561c0(p3fes::EEContext&);
void fn_sub_2561D0_002561d0(p3fes::EEContext&);
void fn_sub_2561E0_002561e0(p3fes::EEContext&);
void fn_sub_256430_00256430(p3fes::EEContext&);
void fn_sub_256F20_00256f20(p3fes::EEContext&);
void fn_sub_256FA0_00256fa0(p3fes::EEContext&);
void fn_sub_257130_00257130(p3fes::EEContext&);
void fn_sub_257D00_00257d00(p3fes::EEContext&);
void fn_sub_257D90_00257d90(p3fes::EEContext&);
void fn_sub_257E20_00257e20(p3fes::EEContext&);
void fn_sub_257F10_00257f10(p3fes::EEContext&);
void fn_sub_258090_00258090(p3fes::EEContext&);
void fn_sub_2580E0_002580e0(p3fes::EEContext&);
void fn_sub_258140_00258140(p3fes::EEContext&);
void fn_sub_2582B0_002582b0(p3fes::EEContext&);
void fn_sub_258300_00258300(p3fes::EEContext&);
void fn_sub_258490_00258490(p3fes::EEContext&);
void fn_sub_2584E0_002584e0(p3fes::EEContext&);
void fn_sub_258540_00258540(p3fes::EEContext&);
void fn_sub_258630_00258630(p3fes::EEContext&);
void fn_sub_258A50_00258a50(p3fes::EEContext&);
void fn_sub_258AF0_00258af0(p3fes::EEContext&);
void fn_sub_258F80_00258f80(p3fes::EEContext&);
void fn_sub_259190_00259190(p3fes::EEContext&);
void fn_sub_259250_00259250(p3fes::EEContext&);
void fn_sub_2592C0_002592c0(p3fes::EEContext&);
void fn_sub_259310_00259310(p3fes::EEContext&);
void fn_sub_259380_00259380(p3fes::EEContext&);
void fn_sub_2593D0_002593d0(p3fes::EEContext&);
void fn_sub_2594C0_002594c0(p3fes::EEContext&);
void fn_sub_2595C0_002595c0(p3fes::EEContext&);
void fn_sub_259610_00259610(p3fes::EEContext&);
void fn_sub_259630_00259630(p3fes::EEContext&);
void fn_sub_259640_00259640(p3fes::EEContext&);
void fn_sub_259690_00259690(p3fes::EEContext&);
void fn_sub_2596F0_002596f0(p3fes::EEContext&);
void fn_sub_259740_00259740(p3fes::EEContext&);
void fn_sub_259850_00259850(p3fes::EEContext&);
void fn_sub_259970_00259970(p3fes::EEContext&);
void fn_sub_2599C0_002599c0(p3fes::EEContext&);
void fn_sub_259A60_00259a60(p3fes::EEContext&);
void fn_sub_259B00_00259b00(p3fes::EEContext&);
void fn_sub_259B60_00259b60(p3fes::EEContext&);
void fn_sub_259BC0_00259bc0(p3fes::EEContext&);
void fn_sub_259C10_00259c10(p3fes::EEContext&);
void fn_sub_259C60_00259c60(p3fes::EEContext&);
void fn_sub_259CC0_00259cc0(p3fes::EEContext&);
void fn_sub_259D10_00259d10(p3fes::EEContext&);
void fn_sub_259D80_00259d80(p3fes::EEContext&);
void fn_sub_259E00_00259e00(p3fes::EEContext&);
void fn_sub_259E60_00259e60(p3fes::EEContext&);
void fn_sub_259EA0_00259ea0(p3fes::EEContext&);
void fn_sub_259ED0_00259ed0(p3fes::EEContext&);
void fn_sub_259F40_00259f40(p3fes::EEContext&);
void fn_sub_259FC0_00259fc0(p3fes::EEContext&);
void fn_sub_25A030_0025a030(p3fes::EEContext&);
void fn_sub_25AA70_0025aa70(p3fes::EEContext&);
void fn_sub_25AAD0_0025aad0(p3fes::EEContext&);
void fn_sub_25B300_0025b300(p3fes::EEContext&);
void fn_sub_25B3B0_0025b3b0(p3fes::EEContext&);
void fn_sub_25B440_0025b440(p3fes::EEContext&);
void fn_sub_25B4A0_0025b4a0(p3fes::EEContext&);
void fn_sub_25B4B0_0025b4b0(p3fes::EEContext&);
void fn_sub_25B4F0_0025b4f0(p3fes::EEContext&);
void fn_sub_25B5F0_0025b5f0(p3fes::EEContext&);
void fn_sub_25B640_0025b640(p3fes::EEContext&);
void fn_sub_260A10_00260a10(p3fes::EEContext&);
void fn_sub_260BD0_00260bd0(p3fes::EEContext&);
void fn_sub_260C20_00260c20(p3fes::EEContext&);
void fn_sub_260C70_00260c70(p3fes::EEContext&);
void fn_sub_260CD0_00260cd0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// --- gp slots (`lw rX, off(gp)`) -----------------------------------------------------------------------------------
constexpr s32 kGpRoot = -18964;        // 0x7CE2DC sfl_root.c work
constexpr s32 kGpResult = -18960;      // 0x7CE2E0 sfl_result.c work
constexpr s32 kGpPoseMgr = -18864;     // 0x7CE340 gc_pose.c manager {head, tail}
constexpr s32 kGpCard = -18844;        // 0x7CE354 sfl_card.c work
constexpr s32 kGpScript = -18840;      // 0x7CE358 sfl_script.c work
constexpr s32 kGpActStarted = -18836;  // 0x7CE35C sub_259ED0's started flag
constexpr s32 kGpCursor = -18832;      // 0x7CE360 sfl_cursor.c work
constexpr s32 kGpCount = -18828;       // 0x7CE364 sfl_count.c work
constexpr s32 kGpPsel2 = -18808;       // 0x7CE378 sfl_psel2.c work

// --- a card record (card work +4 + 4708 i) ---------------------------------------------------------------------------
constexpr s32 kCardStride = 4708;
constexpr s32 kCardPrev = 4032;       // the deal list
constexpr s32 kCardNext = 4036;
constexpr s32 kCardParent = 4040;     // the stack it is in (flag 0x2)
constexpr s32 kCardPose0 = 4044;      // six gc_pose objects
constexpr s32 kCardPose1 = 4144;
constexpr s32 kCardPose2 = 4244;
constexpr s32 kCardPose3 = 4344;
constexpr s32 kCardPose4 = 4456;
constexpr s32 kCardPose5 = 4568;
constexpr s32 kCardEffect = 4680;     // its effect (flag 0x80)
constexpr s32 kCardAnimKind = 4684;
constexpr s32 kCardAnimFrame = 4688;
constexpr s32 kCardAnimLength = 4692;

// --- card work fields above 0x10000 (`lui 1; addu; lw rX, lo(rY)`: the low halves) ---------------------------------
constexpr s32 kLoListHead = 9820;     // +0x1265C the deal list
constexpr s32 kLoListTail = 9824;     // +0x12660
constexpr s32 kLoStacks = 9828;       // +0x12664 the stack list (4 bytes each)
constexpr s32 kLoCardCount = 9852;    // +0x1267C the card count (the next order)
constexpr s32 kLoStackCount = 9860;   // +0x12684
constexpr s32 kLoCmdRing = 9864;      // +0x12688 the command ring (36-byte entries)
constexpr s32 kLoCmdCount = 10152;    // +0x127A8
constexpr s32 kLoSelected = 10156;    // +0x127AC the selected order
constexpr s32 kLoSpeed = 10160;       // +0x127B0 the command speed
constexpr s32 kLoAnimState = 10352;   // +0x12870

// --- sfl_result.c work ---------------------------------------------------------------------------------------------
constexpr s32 kResEntries = 92;       // 1,648-byte entries
constexpr s32 kResCount = 13276;
constexpr s32 kResList1Count = 13336; // kind 1 entries (+28[])
constexpr s32 kResList0Count = 13340; // kind 0 entries (+60[])

// 0x001F30B0 sub_1F30B0 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_root.c: the "shuffle root" task's steps (root work = task +60 = gp-18964)
// ====================================================================================================================

// sub_1F30B0 (task) -> work+4 & 1: the root work's flag 0x1 (task +60 = the "shuffle root" work)
void sub_1F30B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001f30b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 4);
    v0 = v0 & 0x1;
}

// 0x001F30D0 sub_1F30D0 -- 32 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F30D0 (task): destroys the "shuffle root" task and its children (kwlnTaskDestroyWithHierarchy); called by the
// result screen when it takes the shuffle hand-off back [sflRootDestroy]
void sub_1F30D0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x001f30d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1F30D8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001F4650 sub_1F4650 -- 252 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F4650 (task, request): takes the shuffle request: request +12 / +16 -> work +88 / +84, request +4 (the trigger
// kind) -> work +0xC0FC; kind 468 -> mode 0, kind 469 -> mode 1 when none of the hero's personas (sub_1756F0 /
// sub_174A90) is persona 46, else 2; any other kind -> mode 2 (work +0)
void sub_1F4650(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f4650
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v1, a1, 12);
    sw(v1, s0, 88);
    lw(v1, a1, 16);
    sw(v1, s0, 84);
    lw(a0, a1, 4);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(a0, v1, -16132);
    lw(a0, a1, 4);
    v1 = 469;
    if (a0 == v1) {
        // 0x001f46b8
        charge(ctx, 6);
        jal(ctx, 0x1F46B8u, gen::fn_sub_1756F0_001756f0);
        s1 = v0 & 0xFFFF;
        s2 = 0;
        for (;;) {
            // 0x001f46f4
            charge(ctx, 3);
            v1 = slt(s2, s1);
            if (v1 != 0) {
                backedge(ctx);
                // 0x001f46d0
                charge(ctx, 8);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1F46D8u, gen::fn_sub_174A90_00174a90);
                lhu(a0, v0, 2);
                v1 = 46;
                if (a0 != v1) {
                    // 0x001f46f0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                    continue;
                }
            }
            break;
        }
        // 0x001f4700
        charge(ctx, 2);
        if (s2 != s1) {
            // 0x001f4718
            charge(ctx, 4);
            v1 = 2;
            sw(v1, s0, 0);
        } else {
            // 0x001f4708
            charge(ctx, 4);
            v1 = 1;
            sw(v1, s0, 0);
        }
    } else {
        // 0x001f4698
        charge(ctx, 3);
        v1 = 468;
        if (a0 == v1) {
            // 0x001f46ac
            charge(ctx, 3);
            sw(zero, s0, 0);
        } else {
            // 0x001f46a4
            charge(ctx, 2);
            // 0x001f4728
            charge(ctx, 2);
            v1 = 2;
            sw(v1, s0, 0);
        }
    }
    // 0x001f4730 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001F4910 sub_1F4910 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F4910 (task) -> work+4 & 0x80: the ground resources requested (set by sub_1F48D0)
void sub_1F4910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001f4910
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 4);
    v0 = v0 & 0x80;
}

// 0x001F4970 sub_1F4970 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F4970 (task) -> work+4 & 0x100: the ground started (set by sub_1F4930)
void sub_1F4970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001f4970
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 4);
    v0 = v0 & 0x100;
}

// 0x001F4990 sub_1F4990 -- 108 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F4990 () -> bool: kind 468 (work +0xC0FC) and work +228 == 0
void sub_1F4990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f4990
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpRoot);
    if (v0 == 0) {
        // 0x001f49a4
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 17952);  // "sfl_root.c"
        a1 = 254;
        jal(ctx, 0x1F49B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f49b8
    charge(ctx, 7);
    lw(a0, gp, kGpRoot);
    v0 = 0x10000;
    v0 = addu(a0, v0);
    lw(v1, v0, -16132);
    v0 = 468;
    if (v1 == v0) {
        // 0x001f49e0
        charge(ctx, 3);
        lw(v0, a0, 228);
        // xor v0: a 64-bit move to itself (no effect)
        v0 = sltiu(v0, 1);
    } else {
        // 0x001f49d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001f49ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001F48D0 sub_1F48D0 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F48D0 (task): requests battle/shuffle/sfl_ground.bin (sub_20E2C0) and sets work flag 0x80
void sub_1F48D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f48d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    jal(ctx, 0x1F48E0u, gen::fn_sub_20E2C0_0020e2c0);
    lw(v1, s0, 4);
    v1 = v1 | 0x80;
    sw(v1, s0, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F4930 sub_1F4930 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F4930 (task): starts the ground (sub_23C280) and sets work flag 0x100
void sub_1F4930(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f4930
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    jal(ctx, 0x1F4940u, gen::fn_sub_23C280_0023c280);
    lw(v1, s0, 4);
    v1 = v1 | 0x100;
    sw(v1, s0, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F5510 sub_1F5510 -- 196 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F5510: ends a persona-card result: raises flag 5137 when work flag 0x1000 is set, passes every id of the
// result's first u16 list (sub_1F9770) to sub_174B40, state 0, clears work flag 0x1
void sub_1F5510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f5510
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpRoot);
    if (v0 == 0) {
        // 0x001f552c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 17952);  // "sfl_root.c"
        a1 = 254;
        jal(ctx, 0x1F5538u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f5540
    charge(ctx, 5);
    lw(s0, gp, kGpRoot);
    lw(v0, s0, 4);
    v0 = v0 & 0x1000;
    if (v0 != 0) {
        // 0x001f5554
        charge(ctx, 4);
        a0 = 5137;
        a1 = 1;
        jal(ctx, 0x1F555Cu, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x001f5564
    charge(ctx, 7);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x4C);
    jal(ctx, 0x1F556Cu, gen::fn_sub_1F9770_001f9770);
    s1 = 0;
    for (;;) {
        // 0x001f5598
        charge(ctx, 4);
        lw(v1, sp, 0x4C);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001f5580
        charge(ctx, 6);
        v0 = sll(s1, 1);
        v0 = addu(v0, sp);
        lhu(a0, v0, 48);
        jal(ctx, 0x1F558Cu, gen::fn_sub_174B40_00174b40);
        s1 = addiu(s1, 1);
    }
    // 0x001f55a8
    charge(ctx, 11);
    sw(zero, s0, 8);
    lw(a0, s0, 4);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001F5650 sub_1F5650 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F5650: card state 4 (sub_259310) and root state 25
void sub_1F5650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f5650
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpRoot);
    if (v0 == 0) {
        // 0x001f5668
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 17952);  // "sfl_root.c"
        a1 = 254;
        jal(ctx, 0x1F5674u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f567c
    charge(ctx, 10);
    lw(s0, gp, kGpRoot);
    jal(ctx, 0x1F5680u, gen::fn_sub_259310_00259310);
    v1 = 25;
    sw(v1, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F56B0 sub_1F56B0 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F56B0: counts a battle towards Shuffle Time: game counter 57 + 1, or, when it has reached counter 56, 57 = 0
// and 56 = 24 + RpRandom() % 5 (the same re-arm as sub_25B440) [sflCountBattle]
void sub_1F56B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f56b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 57;
    jal(ctx, 0x1F56C0u, gen::fn_sub_16F380_0016f380);
    s0 = v0;
    a0 = 56;
    jal(ctx, 0x1F56D0u, gen::fn_sub_16F380_0016f380);
    if (s0 != v0) {
        // counter 57 (battles counted) has not reached counter 56 (the limit): 57 + 1
        // 0x001f5724
        charge(ctx, 7);
        a0 = 57;
        jal(ctx, 0x1F5728u, gen::fn_sub_16F380_0016f380);
        a1 = addiu(v0, 1);
        a0 = 57;
        jal(ctx, 0x1F5738u, gen::fn_sub_16F3E0_0016f3e0);
    } else {
        // reached: Shuffle Time is due; re-arm 57 = 0, 56 = 24 + RpRandom() % 5
        // 0x001f56e0
        charge(ctx, 17);
        s0 = 24;
        jal(ctx, 0x1F56E4u, gen::fn_sub_488F30_00488f30);
        v1 = 5;
        divu(v0, v1);
        mfhi(v0);
        s0 = addu(s0, v0);
        a0 = 57;
        a1 = 0;
        jal(ctx, 0x1F5704u, gen::fn_sub_16F3E0_0016f3e0);
        a0 = 56;
        a1 = s0;
        jal(ctx, 0x1F5714u, gen::fn_sub_16F3E0_0016f3e0);
    }
    // 0x001f5740 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F5760 sub_1F5760 -- 168 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F5760 (persona id) -> bool: is the persona among the hero's personas (sub_1756F0 count, sub_174A90 entry +2)
void sub_1F5760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f5760
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1F577Cu, gen::fn_sub_1756F0_001756f0);
    s2 = v0 & 0xFFFF;
    s3 = 0;
    s1 = s0 & 0xFFFF;
    for (;;) {
        // 0x001f57d8
        charge(ctx, 3);
        v0 = slt(s3, s2);
        if (v0 != 0) {
            backedge(ctx);
            // 0x001f5798
            charge(ctx, 7);
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1F57A0u, gen::fn_sub_174A90_00174a90);
            s0 = v0;
            if (s0 == 0) {
                // 0x001f57b4
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 17952);  // "sfl_root.c"
                a1 = 2460;
                jal(ctx, 0x1F57C0u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001f57c8
            charge(ctx, 3);
            lhu(v0, s0, 2);
            if (s1 != v0) {
                // 0x001f57d4
                charge(ctx, 1);
                s3 = addiu(s3, 1);
                continue;
            }
        }
        break;
    }
    // 0x001f57e4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = slt(s3, s2);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001F58F0 sub_1F58F0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_result.c: the card result: the entries won, their id lists (gp-18960)
// ====================================================================================================================

// sub_1F58F0 (work): sfl_result init: K_Assert when gp-18960 is already set, zeroes +0 / +13336 / +13340 / +13276,
// gp-18960 = work
void sub_1F58F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f58f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpResult);
    if (v1 != 0) {
        // 0x001f590c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 146;
        jal(ctx, 0x1F5918u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f5920 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    sw(zero, s0, 0);
    sw(zero, s0, kResList1Count);
    sw(zero, s0, kResList0Count);
    sw(zero, s0, kResCount);
    sw(s0, gp, kGpResult);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F65E0 sub_1F65E0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F65E0 () -> flags & 1: the result work's flag 0x1
void sub_1F65E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f65e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpResult);
    if (v0 == 0) {
        // 0x001f65f4
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F6600u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f6608 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpResult);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001F6D20 sub_1F6D20 -- 352 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F6D20 (card info {kind, a, b}): appends a result entry (1,648-byte records from +92; count +13276, < 8): the
// three words, then its index in the kind's list (kind 1 -> +28[] / +13336, kind 0 -> +60[] / +13340, each < 8)
void sub_1F6D20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001f6d20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, kGpResult);
    if (v1 == 0) {
        // 0x001f6d40
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F6D4Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f6d54
    charge(ctx, 4);
    lw(s0, gp, kGpResult);
    lw(v1, s0, kResCount);
    if (i64(v1) >= 0) {
        // 0x001f6d64
        charge(ctx, 3);
        v1 = slti(v1, 8);
        if (v1 == 0) {
            goto L_001f6d70;
        }
        goto L_001f6d84;
    }
L_001f6d70:
    charge(ctx, 5);
    a0 = 0x680000;
    a0 = addiu(a0, 18984);  // "sfl_result.c"
    a1 = 845;
    jal(ctx, 0x1F6D7Cu, gen::fn_sub_19D3F0_0019d3f0);
L_001f6d84:
    charge(ctx, 14);
    lw(a0, s0, kResCount);
    v1 = 1648;
    mult(v1, a0, v1);
    v1 = addu(s0, v1);
    lwc1(f2, s1, 0);
    lwc1(f1, s1, 4);
    lwc1(f0, s1, 8);
    swc1(f2, v1, 92);
    swc1(f1, v1, 96);
    swc1(f0, v1, 100);
    lw(a0, s1, 0);
    v1 = 1;
    if (a0 == v1) {
        // 0x001f6e18
        charge(ctx, 4);
        lw(v1, s0, kResList1Count);
        v1 = slti(v1, 8);
        if (v1 == 0) {
            // 0x001f6e28
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 18984);  // "sfl_result.c"
            a1 = 858;
            jal(ctx, 0x1F6E34u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001f6e3c
        charge(ctx, 8);
        lw(a0, s0, kResCount);
        lw(v1, s0, kResList1Count);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        sw(a0, v1, 28);
        lw(v1, s0, kResList1Count);
        v1 = addiu(v1, 1);
        sw(v1, s0, kResList1Count);
    } else {
        // 0x001f6dbc
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x001f6dcc
            charge(ctx, 4);
            lw(v1, s0, kResList0Count);
            v1 = slti(v1, 8);
            if (v1 == 0) {
                // 0x001f6ddc
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 18984);  // "sfl_result.c"
                a1 = 853;
                jal(ctx, 0x1F6DE8u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001f6df0
            charge(ctx, 10);
            lw(a0, s0, kResCount);
            lw(v1, s0, kResList0Count);
            v1 = sll(v1, 2);
            v1 = addu(v1, s0);
            sw(a0, v1, 60);
            lw(v1, s0, kResList0Count);
            v1 = addiu(v1, 1);
            sw(v1, s0, kResList0Count);
        } else {
            // 0x001f6dc4
            charge(ctx, 2);
        }
    }
    // 0x001f6e5c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, s0, kResCount);
    v1 = addiu(v1, 1);
    sw(v1, s0, kResCount);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001F9630 sub_1F9630 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F9630: empties the two entry lists (+13336, +13340)
void sub_1F9630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f9630
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpResult);
    if (v1 == 0) {
        // 0x001f9644
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F9650u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f9658 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, gp, kGpResult);
    sw(zero, v1, kResList0Count);
    sw(zero, v1, kResList1Count);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001F9680 sub_1F9680 -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F9680 (card info) -> bool: is there an entry of the same kind with the same id: kind 0 the u16 at +4, kind 1
// the word at +4 or the word at +8
void sub_1F9680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f9680
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpResult);
    if (v0 == 0) {
        // 0x001f969c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F96A8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f96b0
    charge(ctx, 7);
    lw(t0, gp, kGpResult);
    t1 = 0;
    lw(a3, t0, kResCount);
    v0 = 1;
    a2 = 1648;
    for (;;) {
        // 0x001f9748
        charge(ctx, 3);
        v1 = slt(t1, a3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001f96cc
        charge(ctx, 7);
        mult(v1, t1, a2);
        v1 = addu(t0, v1);
        a1 = addiu(v1, 92);
        lw(a0, s0, 0);
        lw(v1, v1, 92);
        if (v1 == a0) {
            // 0x001f96e8
            charge(ctx, 2);
            if (a0 == v0) {
                // 0x001f9718
                charge(ctx, 4);
                lw(a0, a1, 4);
                lw(v1, s0, 4);
                if (a0 == v1) {
                    goto L_001f9738;
                }
                // 0x001f9728
                charge(ctx, 4);
                lw(a0, a1, 8);
                lw(v1, s0, 8);
                if (a0 != v1) {
                    goto L_001f9744;
                }
                goto L_001f9738;
            }
            // 0x001f96f0
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x001f96f8
                charge(ctx, 2);
                goto L_001f9744;
            }
            // 0x001f9700
            charge(ctx, 4);
            lhu(a0, a1, 4);
            lhu(v1, s0, 4);
            if (a0 != v1) {
                goto L_001f9744;
            }
            goto L_001f9710_8;
        }
    L_001f9744:
        charge(ctx, 1);
        t1 = addiu(t1, 1);
    }
    // 0x001f9754
    charge(ctx, 1);
    v0 = 0;
    // 0x001f9758 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_001f9710_8:
    charge(ctx, 2);
    // 0x001f9758 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_001f9738:
    charge(ctx, 3);
    v0 = 1;
    // 0x001f9758 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F9770 sub_1F9770 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F9770 (out u16[], out count): copies the u16 list +13280 (count +13312)
void sub_1F9770(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f9770
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpResult);
    if (v1 == 0) {
        // 0x001f9794
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F97A0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f97a8
    charge(ctx, 4);
    lw(a2, gp, kGpResult);
    a3 = 0;
    for (;;) {
        // 0x001f97d0
        charge(ctx, 4);
        lw(a0, a2, 13312);
        v1 = slt(a3, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001f97b8
        charge(ctx, 6);
        a1 = sll(a3, 1);
        v1 = addu(a2, a1);
        lhu(a0, v1, 13280);
        v1 = addu(s1, a1);
        sh(a0, v1, 0);
        a3 = addiu(a3, 1);
    }
    // 0x001f97e0
    charge(ctx, 7);
    sw(a0, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001F9800 sub_1F9800 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F9800 (out u16[], out count): copies the u16 list +13296 (count +13316)
void sub_1F9800(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f9800
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpResult);
    if (v1 == 0) {
        // 0x001f9824
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F9830u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f9838
    charge(ctx, 4);
    lw(a2, gp, kGpResult);
    a3 = 0;
    for (;;) {
        // 0x001f9860
        charge(ctx, 4);
        lw(a0, a2, 13316);
        v1 = slt(a3, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001f9848
        charge(ctx, 6);
        a1 = sll(a3, 1);
        v1 = addu(a2, a1);
        lhu(a0, v1, 13296);
        v1 = addu(s1, a1);
        sh(a0, v1, 0);
        a3 = addiu(a3, 1);
    }
    // 0x001f9870
    charge(ctx, 7);
    sw(a0, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001F9890 sub_1F9890 -- 64 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_1F9890 () -> word: the result work +24
void sub_1F9890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f9890
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpResult);
    if (v0 == 0) {
        // 0x001f98a4
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 18984);  // "sfl_result.c"
        a1 = 140;
        jal(ctx, 0x1F98B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f98b8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, gp, kGpResult);
    lw(v0, v0, 24);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0024DA60 sub_24DA60 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// gc_pose.c: the pose list leaves the cards use (pose manager gp-18864)
// ====================================================================================================================

// sub_24DA60 (pose): links a pose object at the tail of the pose list (+0 prev, +4 next; +8 / +16 cleared)
// [gcPoseRegister]
void sub_24DA60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024da60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpPoseMgr);
    if (v1 == 0) {
        // 0x0024da7c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 93;
        jal(ctx, 0x24DA88u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024da90
    charge(ctx, 6);
    lw(a0, gp, kGpPoseMgr);
    sw(zero, s0, 8);
    sw(zero, s0, 16);
    lw(v1, a0, 0);
    if (v1 == 0) {
        // 0x0024dac8
        charge(ctx, 4);
        sw(zero, s0, 4);
        sw(zero, s0, 0);
        sw(s0, a0, 0);
        sw(s0, a0, 4);
    } else {
        // 0x0024daa8
        charge(ctx, 8);
        lw(v1, a0, 4);
        sw(v1, s0, 0);
        sw(zero, s0, 4);
        lw(v1, a0, 4);
        sw(s0, v1, 4);
        sw(s0, a0, 4);
    }
    // 0x0024dad8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024DAF0 sub_24DAF0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_24DAF0 (pose): unlinks a pose object from the pose list, fixing head / tail [gcPoseUnregister]
void sub_24DAF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024daf0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpPoseMgr);
    if (v1 == 0) {
        // 0x0024db0c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 93;
        jal(ctx, 0x24DB18u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024db20
    charge(ctx, 4);
    lw(a1, gp, kGpPoseMgr);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x0024db30
        charge(ctx, 2);
        lw(v1, s0, 0);
        sw(v1, a0, 0);
    }
    // 0x0024db38
    charge(ctx, 3);
    lw(a0, s0, 0);
    if (a0 != 0) {
        // 0x0024db44
        charge(ctx, 2);
        lw(v1, s0, 4);
        sw(v1, a0, 4);
    }
    // 0x0024db4c
    charge(ctx, 3);
    lw(v1, a1, 0);
    if (s0 == v1) {
        // 0x0024db58
        charge(ctx, 2);
        lw(v1, s0, 4);
        sw(v1, a1, 0);
    }
    // 0x0024db60
    charge(ctx, 3);
    lw(v1, a1, 4);
    if (s0 == v1) {
        // 0x0024db6c
        charge(ctx, 2);
        lw(v1, s0, 0);
        sw(v1, a1, 4);
    }
    // 0x0024db74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024F960 sub_24F960 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_24F960 (pose, out vec3): the pose's position +20..+28 (K_Assert unless type +12 is 0 and state +32 < 4)
// [gcPoseGetPos]
void sub_24F960(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0024f960
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 12);
    if (v1 != 0) {
        // 0x0024f984
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 885;
        jal(ctx, 0x24F990u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f998
    charge(ctx, 4);
    lw(v1, s1, 32);
    v1 = slti(v1, 4);
    if (v1 == 0) {
        // 0x0024f9a8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 886;
        jal(ctx, 0x24F9B4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024f9bc (the shared epilogue, written out on this path)
    charge(ctx, 12);
    lwc1(f2, s1, 20);
    lwc1(f1, s1, 24);
    lwc1(f0, s1, 28);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024F9F0 sub_24F9F0 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_24F9F0 (pose, vec3): sets the position of a type-0 pose in state 0 or 3 (else K_Assert) [gcPoseSetPos]
void sub_24F9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0024f9f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 32);
    v1 = slti(v1, 4);
    if (v1 == 0) {
        // 0x0024fa18
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 893;
        jal(ctx, 0x24FA24u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fa2c
    charge(ctx, 4);
    lw(a0, s1, 32);
    v1 = 3;
    if (a0 != v1) {
        // 0x0024fa3c
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_0024fa4c;
        }
        // 0x0024fa44
        charge(ctx, 2);
        // 0x0024fa6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 902;
        jal(ctx, 0x24FA78u, gen::fn_sub_19D3F0_0019d3f0);
        // 0x0024fa80 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0024fa4c:
    charge(ctx, 8);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, s1, 20);
    swc1(f1, s1, 24);
    swc1(f0, s1, 28);
    // 0x0024fa80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024FAF0 sub_24FAF0 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_24FAF0 (pose, vec3): sets the position of a pose in state 0 or 1 (K_Assert from state 2) [gcPoseSetPos1]
void sub_24FAF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0024faf0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 32);
    v1 = slti(v1, 2);
    if (v1 == 0) {
        // 0x0024fb18
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 917;
        jal(ctx, 0x24FB24u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024fb2c
    charge(ctx, 4);
    lw(a0, s1, 32);
    v1 = 1;
    if (a0 != v1) {
        // 0x0024fb3c
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_0024fb4c;
        }
        // 0x0024fb44
        charge(ctx, 2);
        // 0x0024fb6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 926;
        jal(ctx, 0x24FB78u, gen::fn_sub_19D3F0_0019d3f0);
        // 0x0024fb80 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0024fb4c:
    charge(ctx, 8);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, s1, 20);
    swc1(f1, s1, 24);
    swc1(f0, s1, 28);
    // 0x0024fb80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024FDA0 sub_24FDA0 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_24FDA0 (pose): type 1, state 0
void sub_24FDA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0024fda0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 1;
    sw(v1, a0, 12);
    sw(zero, a0, 32);
}

// 0x0024FE00 sub_24FE00 -- 24 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_24FE00 (pose): type 2, +36 = 3
void sub_24FE00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0024fe00
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 2;
    sw(v1, a0, 12);
    v1 = 3;
    sw(v1, a0, 36);
}

// 0x002534D0 sub_2534D0 -- 140 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_card.c: the cards: records, the deal list, stacks, the command ring, animations (gp-18844)
// ====================================================================================================================

// sub_2534D0 (work): sfl_card init: clears the flags, the list, the counters and the 16 card records (slot id +20 =
// i), speed +0x12880 = 256, gp-18844 = work [sflCardInit]
void sub_2534D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x002534d0
    enter(ctx, 20);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(zero, v1, kLoCardCount);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(zero, v1, kLoStackCount);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(zero, v1, kLoListHead);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(zero, v1, kLoListTail);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(zero, v1, kLoCmdCount);
    a2 = 0;
    a1 = kCardStride;
    for (;;) {
        // 0x00253534
        charge(ctx, 3);
        v1 = slti(a2, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00253520
        charge(ctx, 5);
        mult(v1, a2, a1);
        v1 = addu(a0, v1);
        sw(zero, v1, 4);
        sw(a2, v1, 24);
        a2 = addiu(a2, 1);
    }
    // 0x00253540
    charge(ctx, 7);
    a1 = 256;
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(a1, v1, 10368);
    sw(a0, gp, kGpCard);
}

// 0x00253560 sub_253560 -- 152 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_253560: sfl_card shutdown: releases every card in use (sub_253600), gp-18844 = 0
void sub_253560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00253560
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x0025357c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253588u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253590
    charge(ctx, 4);
    lw(s0, gp, kGpCard);
    s1 = 0;
    for (;;) {
        // 0x002535d0
        charge(ctx, 3);
        v1 = slti(s1, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002535a0
        charge(ctx, 9);
        v1 = kCardStride;
        mult(v1, s1, v1);
        v1 = addu(s0, v1);
        a0 = addiu(v1, 4);
        lw(v1, v1, 4);
        v1 = nor(v1, 0);
        v1 = v1 & 0x4;
        if (v1 == 0) {
            // 0x002535c4
            charge(ctx, 2);
            jal(ctx, 0x2535C4u, gen::fn_sub_253600_00253600);
        }
        // 0x002535cc
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x002535dc
    charge(ctx, 7);
    sw(zero, gp, kGpCard);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00253600 sub_253600 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_253600 (card): releases a card's objects: its effect (+4680, sub_34FCF0) when flag 0x80, its six pose objects
// (sub_24DAF0) when flag 0x100; clears 0x100
void sub_253600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00253600
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 0);
    v1 = a0 & 0x100;
    if (v1 != 0) {
        // 0x00253620
        charge(ctx, 3);
        v0 = a0 & 0x80;
        if (v0 != 0) {
            // 0x0025362c
            charge(ctx, 3);
            lw(a0, s0, kCardEffect);
            jal(ctx, 0x253630u, gen::fn_sub_34FCF0_0034fcf0);
        }
        // 0x00253638
        charge(ctx, 18);
        a0 = addiu(s0, kCardPose0);
        jal(ctx, 0x25363Cu, gen::fn_sub_24DAF0_0024daf0);
        a0 = addiu(s0, kCardPose2);
        jal(ctx, 0x253648u, gen::fn_sub_24DAF0_0024daf0);
        a0 = addiu(s0, kCardPose1);
        jal(ctx, 0x253654u, gen::fn_sub_24DAF0_0024daf0);
        a0 = addiu(s0, kCardPose3);
        jal(ctx, 0x253660u, gen::fn_sub_24DAF0_0024daf0);
        a0 = addiu(s0, kCardPose4);
        jal(ctx, 0x25366Cu, gen::fn_sub_24DAF0_0024daf0);
        a0 = addiu(s0, kCardPose5);
        jal(ctx, 0x253678u, gen::fn_sub_24DAF0_0024daf0);
    }
    // 0x00253680 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, 0);
    v1 = si(-257);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002536B0 sub_2536B0 -- 320 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2536B0 (arcana, number): deals an arcana card: a free record (sub_255390) linked at the deal list's tail, flag
// 0x4, kind 1, the order = the card count, which grows
void sub_2536B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002536b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002536dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2536E8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002536f0
    charge(ctx, 3);
    lw(s1, gp, kGpCard);
    if (s1 == 0) {
        // 0x002536fc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253708u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253710
    charge(ctx, 8);
    lw(s0, gp, kGpCard);
    jal(ctx, 0x253714u, gen::fn_sub_255390_00255390);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoListHead);
    if (v1 != 0) {
        // 0x00253758
        charge(ctx, 12);
        sw(zero, v0, kCardNext);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoListTail);
        sw(v1, v0, kCardPrev);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoListTail);
        sw(v0, v1, kCardNext);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListTail);
    } else {
        // 0x00253730
        charge(ctx, 10);
        sw(zero, v0, kCardNext);
        sw(zero, v0, kCardPrev);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListHead);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListTail);
    }
    // 0x00253788
    charge(ctx, 26);
    lw(v1, v0, 0);
    v1 = v1 | 0x4;
    sw(v1, v0, 0);
    v1 = 1;
    sw(v1, v0, 4);
    sw(s3, v0, 8);
    sw(s2, v0, 12);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    sw(v1, v0, 16);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    a0 = addiu(v1, 1);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(a0, v1, kLoCardCount);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002537F0 sub_2537F0 -- 300 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2537F0 (persona id): deals a persona card (kind 0, u16 id at +8), as sub_2536B0
void sub_2537F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002537f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00253814
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253820u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253828
    charge(ctx, 3);
    lw(s1, gp, kGpCard);
    if (s1 == 0) {
        // 0x00253834
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253840u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253848
    charge(ctx, 8);
    lw(s0, gp, kGpCard);
    jal(ctx, 0x25384Cu, gen::fn_sub_255390_00255390);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoListHead);
    if (v1 != 0) {
        // 0x00253890
        charge(ctx, 12);
        sw(zero, v0, kCardNext);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoListTail);
        sw(v1, v0, kCardPrev);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoListTail);
        sw(v0, v1, kCardNext);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListTail);
    } else {
        // 0x00253868
        charge(ctx, 10);
        sw(zero, v0, kCardNext);
        sw(zero, v0, kCardPrev);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListHead);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListTail);
    }
    // 0x002538c0 (the shared epilogue, written out on this path)
    charge(ctx, 23);
    lw(v1, v0, 0);
    v1 = v1 | 0x4;
    sw(v1, v0, 0);
    sw(zero, v0, 4);
    sh(s2, v0, 8);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    sw(v1, v0, 16);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    a0 = addiu(v1, 1);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(a0, v1, kLoCardCount);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00253920 sub_253920 -- 288 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_253920: deals a blank card (kind 2), as sub_2536B0
void sub_253920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00253920
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x0025393c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253948u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253950
    charge(ctx, 3);
    lw(s1, gp, kGpCard);
    if (s1 == 0) {
        // 0x0025395c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x253968u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253970
    charge(ctx, 8);
    lw(s0, gp, kGpCard);
    jal(ctx, 0x253974u, gen::fn_sub_255390_00255390);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoListHead);
    if (v1 != 0) {
        // 0x002539b8
        charge(ctx, 12);
        sw(zero, v0, kCardNext);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoListTail);
        sw(v1, v0, kCardPrev);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoListTail);
        sw(v0, v1, kCardNext);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListTail);
    } else {
        // 0x00253990
        charge(ctx, 10);
        sw(zero, v0, kCardNext);
        sw(zero, v0, kCardPrev);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListHead);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        sw(v0, v1, kLoListTail);
    }
    // 0x002539e8 (the shared epilogue, written out on this path)
    charge(ctx, 22);
    lw(v1, v0, 0);
    v1 = v1 | 0x4;
    sw(v1, v0, 0);
    v1 = 2;
    sw(v1, v0, 4);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    sw(v1, v0, 16);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    a0 = addiu(v1, 1);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(a0, v1, kLoCardCount);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00254B90 sub_254B90 -- 636 bytes; frame 0xE0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_254B90: draws the cards: the leaf models of every top-level card (sub_256FA0), sorted far to near by their
// distance from the camera (kwlnGetMainCamera, RwFrameGetLTM, RwV3dLength; a bubble sort on the guest frame), each
// model drawn (sub_20B250)
void sub_254B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00254b90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00254bb4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x254BC0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00254bc8
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    lw(v1, v1, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00254be0
        charge(ctx, 13);
        jal(ctx, 0x254BE0u, gen::fn_sub_198590_00198590);
        lw(a0, v0, 4);
        jal(ctx, 0x254BECu, gen::fn_sub_4CB2F0_004cb2f0);
        s2 = addiu(v0, 48);
        jal(ctx, 0x254BF8u, gen::fn_sub_2554F0_002554f0);
        s1 = v0;
        s0 = 0;
        s3 = 0;
        for (;;) {
            // 0x00254c44
            charge(ctx, 3);
            v1 = slt(s3, s1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00254c14
            charge(ctx, 12);
            a0 = s3;
            jal(ctx, 0x254C18u, gen::fn_sub_255440_00255440);
            v1 = sll(s0, 2);
            v1 = addu(v1, sp);
            a0 = v0;
            a1 = addiu(v1, 112);
            a2 = addiu(sp, 0xD8);
            jal(ctx, 0x254C34u, gen::fn_sub_256FA0_00256fa0);
            s0 = addiu(s0, 1);
            s3 = addiu(s3, 1);
        }
        // 0x00254c50
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x00254c78
            charge(ctx, 3);
            v1 = slt(s3, s1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00254c5c
            charge(ctx, 7);
            a0 = s3;
            jal(ctx, 0x254C60u, gen::fn_sub_255440_00255440);
            v1 = sll(s3, 2);
            v1 = addu(v1, sp);
            sw(v0, v1, 80);
            s3 = addiu(s3, 1);
        }
        // 0x00254c84
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00254ce4
            charge(ctx, 3);
            v1 = slt(s1, s0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00254c90
            charge(ctx, 21);
            s3 = sll(s1, 2);
            v0 = addu(s3, sp);
            lw(v0, v0, 112);
            lwc1(f1, v0, 56);
            lwc1(f0, s2, 0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f1, v0, 60);
            lwc1(f0, s2, 4);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xCC);
            lwc1(f1, v0, 64);
            lwc1(f0, s2, 8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xD0);
            a0 = addiu(sp, 0xC8);
            jal(ctx, 0x254CD0u, gen::fn_sub_4C6AC0_004c6ac0);
            v1 = addu(s3, sp);
            swc1(f0, v1, 176);
            s1 = addiu(s1, 1);
        }
        // 0x00254cf0
        charge(ctx, 4);
        t0 = 0;
        a0 = addiu(s0, -1);
        for (;;) {
            // 0x00254d74
            charge(ctx, 3);
            v1 = slt(t0, a0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00254d00
            charge(ctx, 3);
            t1 = 0;
            for (;;) {
                // 0x00254d64
                charge(ctx, 3);
                v1 = slt(t1, a0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00254d0c
                charge(ctx, 9);
                v1 = sll(t1, 2);
                a3 = addu(v1, sp);
                a1 = addiu(a3, 176);
                v1 = addiu(a1, 4);
                lwc1(f1, a1, 4);
                lwc1(f0, a1, 0);
                c_lt_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00254d30
                    charge(ctx, 12);
                    swc1(f1, a1, 0);
                    swc1(f0, v1, 0);
                    a2 = addiu(a3, 112);
                    lw(a1, a2, 0);
                    lw(v1, a2, 4);
                    sw(v1, a2, 0);
                    sw(a1, a2, 4);
                    a2 = addiu(a3, 80);
                    lw(a1, a2, 0);
                    lw(v1, a2, 4);
                    sw(v1, a2, 0);
                    sw(a1, a2, 4);
                }
                // 0x00254d60
                charge(ctx, 1);
                t1 = addiu(t1, 1);
            }
            // 0x00254d70
            charge(ctx, 1);
            t0 = addiu(t0, 1);
        }
        // 0x00254d80
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x00254de0
            charge(ctx, 3);
            v1 = slt(s2, s0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00254d8c
            charge(ctx, 10);
            v0 = sll(s2, 2);
            v0 = addu(v0, sp);
            lw(a0, v0, 80);
            a1 = addiu(sp, 0x90);
            a2 = addiu(sp, 0xDC);
            jal(ctx, 0x254DA0u, gen::fn_sub_256F20_00256f20);
            s1 = 0;
            for (;;) {
                // 0x00254dcc
                charge(ctx, 4);
                lw(v1, sp, 0xDC);
                v1 = slt(s1, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00254db4
                charge(ctx, 6);
                v0 = sll(s1, 2);
                v0 = addu(v0, sp);
                lw(a0, v0, 144);
                jal(ctx, 0x254DC0u, gen::fn_sub_20B250_0020b250);
                s1 = addiu(s1, 1);
            }
            // 0x00254ddc
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
    }
    // 0x00254dec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x00254E10 sub_254E10 -- 268 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_254E10: requests the textures of every card in use that is no stack (kind 1: sub_21A920 arcana / number; kind 0:
// sub_21AB80 persona id); work flags 0x400 | 0x200
void sub_254E10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00254e10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00254e30
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x254E3Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00254e44
    charge(ctx, 4);
    lw(s1, gp, kGpCard);
    s2 = 0;
    for (;;) {
        // 0x00254ee0
        charge(ctx, 3);
        v1 = slti(s2, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00254e54
        charge(ctx, 9);
        v1 = kCardStride;
        mult(v1, s2, v1);
        v1 = addu(s1, v1);
        s0 = addiu(v1, 4);
        lw(v1, v1, 4);
        a0 = nor(v1, 0);
        v1 = a0 & 0x4;
        if (v1 == 0) {
            // 0x00254e78
            charge(ctx, 3);
            v1 = a0 & 0x8;
            if (v1 == 0) {
                // 0x00254e84
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -5632);  // "sfl_card.c"
                a1 = 909;
                jal(ctx, 0x254E90u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x00254e98
            charge(ctx, 4);
            lw(a0, s0, 4);
            v1 = 1;
            if (a0 == v1) {
                // 0x00254ecc
                charge(ctx, 4);
                lw(a0, s0, 8);
                lw(a1, s0, 12);
                jal(ctx, 0x254ED4u, gen::fn_sub_21A920_0021a920);
            } else {
                // 0x00254ea8
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x00254eb8
                    charge(ctx, 5);
                    lhu(a0, s0, 8);
                    jal(ctx, 0x254EBCu, gen::fn_sub_21AB80_0021ab80);
                } else {
                    // 0x00254eb0
                    charge(ctx, 2);
                }
            }
        }
        // 0x00254edc
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00254eec
    charge(ctx, 12);
    lw(v1, s1, 0);
    v1 = v1 | 0x400;
    sw(v1, s1, 0);
    v1 = v1 | 0x200;
    sw(v1, s1, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00254F20 sub_254F20 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_254F20 () -> flags & 0x200: the textures requested
void sub_254F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00254f20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00254f34
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x254F40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00254f48 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x200;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00254F70 sub_254F70 -- 320 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_254F70: sets the cards up: every card of the deal list (sub_258630), +0x12680 = 0, the two work poses (+0x127D4,
// +0x12800) reset, placed at the table 0x68EA30 position and registered; work flag 0x1
void sub_254F70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00254f70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00254f8c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x254F98u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00254fa0
    charge(ctx, 12);
    lw(s0, gp, kGpCard);
    v0 = 0x690000;
    ld(v1, v0, -5584);  // 0x68EA30
    v0 = 0x690000;
    lwc1(f0, v0, -5576);  // 0x68EA38
    sd(v1, sp, 0x30);
    swc1(f0, sp, 0x38);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lw(s1, v0, kLoListHead);
    for (;;) {
        // 0x00254fe0
        charge(ctx, 4);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00254fd0
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x254FD4u, gen::fn_sub_258630_00258630);
        lw(s1, s1, kCardNext);
    }
    // 0x00254ff0
    charge(ctx, 48);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    sw(zero, v0, 9856);
    at = 0x10000;
    at = at | 0x27D4;
    a0 = addu(s0, at);
    jal(ctx, 0x255008u, gen::fn_sub_24FDA0_0024fda0);
    at = 0x10000;
    at = at | 0x27D4;
    a0 = addu(s0, at);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x255020u, gen::fn_sub_24FAF0_0024faf0);
    at = 0x10000;
    at = at | 0x27D4;
    a0 = addu(s0, at);
    jal(ctx, 0x255034u, gen::fn_sub_24DA60_0024da60);
    at = 0x10000;
    at = at | 0x27D4;
    a0 = addu(s0, at);
    jal(ctx, 0x255048u, gen::fn_sub_24F090_0024f090);
    at = 0x10000;
    at = at | 0x2800;
    a0 = addu(s0, at);
    jal(ctx, 0x25505Cu, gen::fn_sub_24FE00_0024fe00);
    at = 0x10000;
    at = at | 0x2800;
    a0 = addu(s0, at);
    jal(ctx, 0x255070u, gen::fn_sub_24DA60_0024da60);
    at = 0x10000;
    at = at | 0x2800;
    a0 = addu(s0, at);
    jal(ctx, 0x255084u, gen::fn_sub_24F090_0024f090);
    lw(v1, s0, 0);
    v1 = v1 | 0x1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002550B0 sub_2550B0 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2550B0: unregisters the two work poses, clears work flag 0x1
void sub_2550B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002550b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002550c8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2550D4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002550dc
    charge(ctx, 20);
    lw(s0, gp, kGpCard);
    at = 0x10000;
    at = at | 0x27D4;
    a0 = addu(s0, at);
    jal(ctx, 0x2550ECu, gen::fn_sub_24DAF0_0024daf0);
    at = 0x10000;
    at = at | 0x2800;
    a0 = addu(s0, at);
    jal(ctx, 0x255100u, gen::fn_sub_24DAF0_0024daf0);
    lw(a0, s0, 0);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00255130 sub_255130 -- 64 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255130 () -> count: the number of top-level cards (sub_2554F0)
void sub_255130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255130
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00255144
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255150u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255158
    charge(ctx, 6);
    jal(ctx, 0x255158u, gen::fn_sub_2554F0_002554f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00255170 sub_255170 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255170 (card): card flag 0x1
void sub_255170(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00255170
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, 0);
    v1 = v1 | 0x1;
    sw(v1, a0, 0);
}

// 0x00255190 sub_255190 -- 24 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255190 (card): +4696 = 0, card flag 0x80
void sub_255190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00255190
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(zero, a0, 4696);
    lw(v1, a0, 0);
    v1 = v1 | 0x80;
    sw(v1, a0, 0);
}

// 0x002551B0 sub_2551B0 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2551B0 (card): card flag 0x400
void sub_2551B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002551b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, 0);
    v1 = v1 | 0x400;
    sw(v1, a0, 0);
}

// 0x002551D0 sub_2551D0 -- 436 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2551D0 (order a, order b): queues a SWAP: dumps the deal list (sub_257E20), marks both cards (flag 0x20,
// K_Assert when marked already) and appends {kind 0, speed, card a, card b} to the command ring (+0x12688, 36-byte
// entries, count +0x127A8)
void sub_2551D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002551d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002551f8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255204u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025520c
    charge(ctx, 16);
    lw(s2, gp, kGpCard);
    jal(ctx, 0x255210u, gen::fn_sub_257E20_00257e20);
    a0 = s1;
    jal(ctx, 0x25521Cu, gen::fn_sub_255440_00255440);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x25522Cu, gen::fn_sub_255440_00255440);
    s0 = v0;
    lw(v1, s1, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x20;
    if (v1 == 0) {
        // 0x0025524c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1057;
        jal(ctx, 0x255258u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255260
    charge(ctx, 5);
    lw(v1, s0, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x20;
    if (v1 == 0) {
        // 0x00255274
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1058;
        jal(ctx, 0x255280u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255288
    charge(ctx, 63);
    lw(v1, s1, 0);
    v1 = v1 | 0x20;
    sw(v1, s1, 0);
    lw(v1, s0, 0);
    v1 = v1 | 0x20;
    sw(v1, s0, 0);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    lw(a0, v1, kLoCmdCount);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a0 = addu(v1, s2);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(zero, v1, 9864);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    lw(a0, v1, kLoCmdCount);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a0 = addu(v1, s2);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(s1, v1, 9872);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    lw(a0, v1, kLoCmdCount);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a0 = addu(v1, s2);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(s0, v1, 9876);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    lw(a1, v1, kLoSpeed);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    lw(a0, v1, kLoCmdCount);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a0 = addu(v1, s2);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(a1, v1, 9868);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    lw(v1, v1, kLoCmdCount);
    a0 = addiu(v1, 1);
    v1 = 0x10000;
    v1 = addu(s2, v1);
    sw(a0, v1, kLoCmdCount);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00255390 sub_255390 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255390 () -> card: the first free card record (no flag 0x4; K_Assert when all 16 are used)
void sub_255390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255390
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002553a8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2553B4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002553bc
    charge(ctx, 5);
    lw(a0, gp, kGpCard);
    a1 = 0;
    v1 = kCardStride;
    for (;;) {
        // 0x002553f4
        charge(ctx, 3);
        v0 = slti(a1, 16);
        if (v0 != 0) {
            backedge(ctx);
            // 0x002553d0
            charge(ctx, 8);
            mult(v0, a1, v1);
            v0 = addu(a0, v0);
            s0 = addiu(v0, 4);
            lw(v0, v0, 4);
            v0 = nor(v0, 0);
            v0 = v0 & 0x4;
            if (v0 == 0) {
                // 0x002553f0
                charge(ctx, 1);
                a1 = addiu(a1, 1);
                continue;
            }
        }
        break;
    }
    // 0x00255400
    charge(ctx, 3);
    v0 = slti(a1, 16);
    if (v0 == 0) {
        // 0x0025540c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1119;
        jal(ctx, 0x255418u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255420 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00255440 sub_255440 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255440 (order) -> card: the top-level card (no flag 0x2) with that order (K_Assert when none)
void sub_255440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255440
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00255460
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x25546Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255474
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x002554b0
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025548c
        charge(ctx, 5);
        s0 = v1;
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x002554a0
            charge(ctx, 3);
            lw(v0, v1, 16);
            if (v0 == s1) {
                break;
            }
        }
        charge(ctx, 1);
        lw(v1, v1, kCardNext);
    }
    // 0x002554b8
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x002554c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1146;
        jal(ctx, 0x2554CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002554d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002554F0 sub_2554F0 -- 116 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2554F0 () -> count: counts the top-level cards of the deal list
void sub_2554F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002554f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00255504
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255510u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255518
    charge(ctx, 7);
    v0 = 0;
    lw(a0, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    lw(a0, v1, kLoListHead);
    for (;;) {
        // 0x0025554c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255534
        charge(ctx, 4);
        lw(v1, a0, 0);  // card flags: 0x2 = inside a stack, not counted
        v1 = v1 & 0x2;
        if (v1 == 0) {
            // 0x00255544
            charge(ctx, 1);
            v0 = addiu(v0, 1);
        }
        // 0x00255548
        charge(ctx, 1);
        lw(a0, a0, kCardNext);
    }
    // 0x00255554
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00255570 sub_255570 -- 672 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255570 (first, n): queues a CLOSE (gathers n cards into a stack): collects the top-level cards by order (fewer
// than 7, K_Assert), marks the n from order `first`, appends {kind 1, speed, n, the n cards}
void sub_255570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255570
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x002555a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2555B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002555b8
    charge(ctx, 3);
    lw(s0, gp, kGpCard);
    if (s0 == 0) {
        // 0x002555c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2555D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002555d8
    charge(ctx, 7);
    s1 = 0;
    lw(a0, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    lw(a0, v1, kLoListHead);
    for (;;) {
        // 0x0025560c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002555f4
        charge(ctx, 4);
        lw(v1, a0, 0);
        v1 = v1 & 0x2;
        if (v1 == 0) {
            // 0x00255604
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x00255608
        charge(ctx, 1);
        lw(a0, a0, kCardNext);
    }
    // 0x00255614
    charge(ctx, 3);
    at = slti(s1, 7);
    if (at == 0) {
        // 0x00255620
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1183;
        jal(ctx, 0x25562Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255634
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x002556d0
        charge(ctx, 3);
        v1 = slt(s2, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255640
        charge(ctx, 3);
        lw(v1, gp, kGpCard);
        if (v1 == 0) {
            // 0x0025564c
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 188;
            jal(ctx, 0x255658u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00255660
        charge(ctx, 6);
        lw(a0, gp, kGpCard);
        v1 = 0x10000;
        v1 = addu(a0, v1);
        lw(a0, v1, kLoListHead);
        for (;;) {
            // 0x0025569c
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00255678
            charge(ctx, 5);
            s5 = a0;
            lw(v1, a0, 0);
            v1 = v1 & 0x2;
            if (v1 == 0) {
                // 0x0025568c
                charge(ctx, 3);
                lw(v1, a0, 16);
                if (v1 == s2) {
                    break;
                }
            }
            charge(ctx, 1);
            lw(a0, a0, kCardNext);
        }
        // 0x002556a4
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x002556ac
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 1146;
            jal(ctx, 0x2556B8u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x002556c0
        charge(ctx, 4);
        v1 = sll(s2, 2);
        v1 = addu(v1, sp);
        sw(s5, v1, 112);
        s2 = addiu(s2, 1);
    }
    // 0x002556dc
    charge(ctx, 4);
    v1 = addu(s4, s3);
    at = slt(s1, v1);
    if (at != 0) {
        // 0x002556ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1188;
        jal(ctx, 0x2556F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255700
    charge(ctx, 6);
    a2 = 0;
    v1 = sll(s4, 2);
    v1 = addu(v1, sp);
    v1 = addiu(v1, 112);
    for (;;) {
        // 0x00255734
        charge(ctx, 3);
        a0 = slt(a2, s3);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255718
        charge(ctx, 7);
        a0 = sll(a2, 2);
        a0 = addu(v1, a0);
        lw(a1, a0, 0);
        lw(a0, a1, 0);
        a0 = a0 | 0x20;
        sw(a0, a1, 0);
        a2 = addiu(a2, 1);
    }
    // 0x00255740
    charge(ctx, 21);
    a0 = 0x10000;
    a0 = addu(s0, a0);
    lw(a1, a0, kLoCmdCount);
    a0 = sll(a1, 3);
    a0 = addu(a0, a1);
    a0 = sll(a0, 2);
    a0 = addu(s0, a0);
    at = 0x10000;
    at = at | 0x2688;
    a1 = addu(a0, at);
    a0 = 1;
    sw(a0, a1, 0);
    a0 = 0x10000;
    a0 = addu(s0, a0);
    lw(a0, a0, kLoSpeed);
    sw(a0, a1, 4);
    a2 = addiu(a1, 8);
    sw(zero, a1, 32);
    a3 = 0;
    for (;;) {
        // 0x002557c0
        charge(ctx, 3);
        a0 = slt(a3, s3);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255794
        charge(ctx, 11);
        a0 = sll(a3, 2);
        a0 = addu(v1, a0);
        lw(a1, a0, 0);
        lw(a0, a2, 24);
        a0 = sll(a0, 2);
        a0 = addu(a2, a0);
        sw(a1, a0, 0);
        lw(a0, a2, 24);
        a0 = addiu(a0, 1);
        sw(a0, a2, 24);
        a3 = addiu(a3, 1);
    }
    // 0x002557cc
    charge(ctx, 17);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoCmdCount);
    a0 = addiu(v1, 1);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(a0, v1, kLoCmdCount);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00255810 sub_255810 -- 776 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255810 (stack index): queues an OPEN (spreads a stack): takes stack (count - 1 - index) out of the stack list
// (+0x12664[], count +0x12684), marks its children (sub_259190), appends {kind 2, speed, stack}
void sub_255810(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255810
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x0025583c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255848u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255850
    charge(ctx, 7);
    lw(s0, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lw(v0, v0, kLoStackCount);
    v0 = slt(s1, v0);
    if (v0 == 0) {
        // 0x0025586c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1225;
        jal(ctx, 0x255878u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255880
    charge(ctx, 15);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lw(v0, v0, kLoStackCount);
    v0 = addiu(v0, -1);
    s2 = subu(v0, s1);
    v0 = sll(s2, 2);
    v1 = addu(v0, s0);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(s4, v0, kLoStacks);
    lw(v0, s4, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x002558bc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1231;
        jal(ctx, 0x2558C8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002558d0
    charge(ctx, 3);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002558dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2558E8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002558f0
    charge(ctx, 7);
    s1 = 0;
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x00255924
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025590c
        charge(ctx, 4);
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x0025591c
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x00255920
        charge(ctx, 1);
        lw(v1, v1, kCardNext);
    }
    // 0x0025592c
    charge(ctx, 3);
    at = slti(s1, 7);
    if (at == 0) {
        // 0x00255938
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1234;
        jal(ctx, 0x255944u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025594c
    charge(ctx, 3);
    s3 = 0;
    for (;;) {
        // 0x002559d8
        charge(ctx, 3);
        v0 = slt(s3, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255958
        charge(ctx, 3);
        lw(v0, gp, kGpCard);
        if (v0 == 0) {
            // 0x00255964
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 188;
            jal(ctx, 0x255970u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00255978
        charge(ctx, 6);
        lw(v1, gp, kGpCard);
        v0 = 0x10000;
        v0 = addu(v1, v0);
        lw(v1, v0, kLoListHead);
        for (;;) {
            // 0x002559b0
            charge(ctx, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00255990
            charge(ctx, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x002559a0
                charge(ctx, 3);
                lw(v0, v1, 16);
                if (v0 == s3) {
                    break;
                }
            }
            charge(ctx, 1);
            lw(v1, v1, kCardNext);
        }
        // 0x002559b8
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x002559c0
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 1146;
            jal(ctx, 0x2559CCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x002559d4
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x002559e4
    charge(ctx, 8);
    a0 = s4;
    a1 = addiu(sp, 0x60);
    a2 = addiu(sp, 0x7C);
    jal(ctx, 0x2559F0u, gen::fn_sub_259190_00259190);
    a1 = 0;
    for (;;) {
        // 0x00255a20
        charge(ctx, 4);
        lw(v1, sp, 0x7C);
        v1 = slt(a1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255a04
        charge(ctx, 7);
        v1 = sll(a1, 2);
        v1 = addu(v1, sp);
        lw(a0, v1, 96);
        lw(v1, a0, 0);
        v1 = v1 | 0x20;
        sw(v1, a0, 0);
        a1 = addiu(a1, 1);
    }
    // 0x00255a30
    charge(ctx, 2);
    for (;;) {
        // 0x00255a5c
        charge(ctx, 7);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoStackCount);
        v1 = addiu(v1, -1);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00255a38
        charge(ctx, 9);
        v1 = sll(s2, 2);
        a1 = addu(s0, v1);
        v1 = 0x10000;
        v1 = addu(a1, v1);
        lw(a0, v1, 9832);
        v1 = 0x10000;
        v1 = addu(a1, v1);
        sw(a0, v1, kLoStacks);
        s2 = addiu(s2, 1);
    }
    // 0x00255a78
    charge(ctx, 40);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoStackCount);
    a0 = addiu(v1, -1);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(a0, v1, kLoStackCount);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(a0, v1, kLoCmdCount);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(s0, v1);
    at = 0x10000;
    at = at | 0x2688;
    a0 = addu(v1, at);
    v1 = 2;
    sw(v1, a0, 0);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoSpeed);
    sw(v1, a0, 4);
    sw(s4, a0, 8);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoCmdCount);
    a0 = addiu(v1, 1);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(a0, v1, kLoCmdCount);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00255F30 sub_255F30 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255F30 () -> flags & 0x10: a command running
void sub_255F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255f30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00255f44
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255F50u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255f58 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x10;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00255F80 sub_255F80 -- 96 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255F80: starts the selection: selected order 0, work flag 0x4 on, 0x8 off
void sub_255F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255f80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00255f94
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x255FA0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00255fa8 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a1, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a1, v1);
    sw(zero, v1, kLoSelected);
    lw(v1, a1, 0);
    a0 = v1 | 0x4;
    sw(a0, a1, 0);
    v1 = si(-9);
    v1 = a0 & v1;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00255FE0 sub_255FE0 -- 76 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_255FE0: ends the selection (work flag 0x4 off)
void sub_255FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00255fe0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00255ff4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x256000u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00256008 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpCard);
    lw(a0, a1, 0);
    v1 = si(-5);
    v1 = a0 & v1;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00256030 sub_256030 -- 216 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_256030 () -> card: the selected card (order +0x127AC)
void sub_256030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00256030
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x0025604c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x256058u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00256060
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(s0, v0, kLoSelected);
    if (v1 == 0) {
        // 0x00256078
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x256084u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025608c
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x002560c8
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002560a4
        charge(ctx, 5);
        s1 = v1;
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x002560b8
            charge(ctx, 3);
            lw(v0, v1, 16);
            if (v0 == s0) {
                break;
            }
        }
        charge(ctx, 1);
        lw(v1, v1, kCardNext);
    }
    // 0x002560d0
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x002560d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1146;
        jal(ctx, 0x2560E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002560ec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00256110 sub_256110 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_256110 (order) -> card: the top-level card with that order (a second copy of sub_255440)
void sub_256110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00256110
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00256130
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x25613Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00256144
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x00256180
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025615c
        charge(ctx, 5);
        s0 = v1;
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x00256170
            charge(ctx, 3);
            lw(v0, v1, 16);
            if (v0 == s1) {
                break;
            }
        }
        charge(ctx, 1);
        lw(v1, v1, kCardNext);
    }
    // 0x00256188
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00256190
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1146;
        jal(ctx, 0x25619Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002561a4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002561C0 sub_2561C0 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2561C0 (card) -> flags & 1: card flag 0x1
void sub_2561C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002561c0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    v0 = v0 & 0x1;
}

// 0x002561D0 sub_2561D0 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2561D0 (card) -> flags & 0x80: card flag 0x80
void sub_2561D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002561d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    v0 = v0 & 0x80;
}

// 0x002561E0 sub_2561E0 -- 592 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2561E0 ($f12 fade, card): fades a card's colour: each byte c of the colour at gp-26752 becomes (u8)((c - 255) *
// fade + 255) on the guest frame, set on every leaf model of the card (sub_256F20, sub_20CC80)
void sub_2561E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x002561e0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lwc1(f0, gp, -26752);  // 0x7CC470
    swc1(f0, sp, 0x48);
    lbu(v0, sp, 0x48);
    v0 = addiu(v0, -255);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    v0 = 0x437F0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f12);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00256250
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00256238
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00256268
    charge(ctx, 18);
    sb(v1, sp, 0x4C);
    lbu(v0, sp, 0x49);
    v0 = addiu(v0, -255);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    v0 = 0x437F0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f12);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002562c8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002562b0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002562e0
    charge(ctx, 18);
    sb(v1, sp, 0x4D);
    lbu(v0, sp, 0x4A);
    v0 = addiu(v0, -255);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    v0 = 0x437F0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f12);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00256340
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00256328
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00256358
    charge(ctx, 18);
    sb(v1, sp, 0x4E);
    lbu(v0, sp, 0x4B);
    v0 = addiu(v0, -255);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    v0 = 0x437F0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f12);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002563b8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002563a0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002563d0
    charge(ctx, 8);
    sb(v1, sp, 0x4F);
    a1 = addiu(sp, 0x20);
    a2 = addiu(sp, 0x44);
    jal(ctx, 0x2563DCu, gen::fn_sub_256F20_00256f20);
    s0 = 0;
    for (;;) {
        // 0x0025640c
        charge(ctx, 4);
        lw(v1, sp, 0x44);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002563f0
        charge(ctx, 7);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        lw(a0, v0, 32);
        a1 = addiu(sp, 0x4C);
        jal(ctx, 0x256400u, gen::fn_sub_20CC80_0020cc80);
        s0 = addiu(s0, 1);
    }
    // 0x0025641c
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00256430 sub_256430 -- 136 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_256430 () -> bool: any card of the deal list marked (flag 0x20)
void sub_256430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00256430
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00256444
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x256450u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00256458
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x00256484
        charge(ctx, 3);
        if (v1 != 0) {
            backedge(ctx);
            // 0x00256470
            charge(ctx, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x20;
            if (v0 == 0) {
                // 0x00256480
                charge(ctx, 1);
                lw(v1, v1, kCardNext);
                continue;
            }
        }
        break;
    }
    // 0x00256490
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x002564a4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00256498
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002564a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00256F20 sub_256F20 -- 124 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_256F20 (card, out models[], out count): the leaf cards of a card (sub_256FA0) as model pointers (card +24)
void sub_256F20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00256f20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a1 = addiu(sp, 0x30);
    a2 = addiu(sp, 0x4C);
    jal(ctx, 0x256F40u, gen::fn_sub_256FA0_00256fa0);
    a2 = 0;
    for (;;) {
        // 0x00256f70
        charge(ctx, 4);
        lw(a0, sp, 0x4C);
        v1 = slt(a2, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00256f54
        charge(ctx, 7);
        a1 = sll(a2, 2);
        v1 = addu(a1, sp);
        lw(v1, v1, 48);
        a0 = addiu(v1, 24);
        v1 = addu(s1, a1);
        sw(a0, v1, 0);
        a2 = addiu(a2, 1);
    }
    // 0x00256f80
    charge(ctx, 7);
    sw(a0, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00256FA0 sub_256FA0 -- 396 bytes; frame 0xC0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_256FA0 (card, out cards[], out count): flattens a stack: a card that is no stack (flag 0x8 clear) is its own
// leaf; a stack's children (sub_259190) are walked depth-first on a guest-frame stack, the leaves stored in reverse;
// count = the leaves when the stack has flag 0x10 (spread), else 1
void sub_256FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00256fa0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    lw(v1, a0, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x8;
    if (v1 == 0) {
        // 0x00256ff0
        charge(ctx, 8);
        a1 = addiu(sp, 0x60);
        a2 = addiu(sp, 0xB8);
        jal(ctx, 0x256FF8u, gen::fn_sub_259190_00259190);
        lw(s0, sp, 0xB8);
        s1 = 0;
        for (;;) {
            // 0x00257080
            charge(ctx, 3);
            lw(v1, sp, 0xB8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00257010
            charge(ctx, 11);
            lw(v1, sp, 0xB8);
            v1 = addiu(v1, -1);
            sw(v1, sp, 0xB8);
            v1 = sll(v1, 2);
            v1 = addu(v1, sp);
            lw(a0, v1, 96);
            lw(v1, a0, 0);
            v1 = nor(v1, 0);
            v1 = v1 & 0x8;
            if (v1 == 0) {
                // 0x00257054
                charge(ctx, 11);
                a1 = addiu(sp, 0x80);
                a2 = addiu(sp, 0xBC);
                jal(ctx, 0x25705Cu, gen::fn_sub_259190_00259190);
                lw(a1, sp, 0x80);
                lw(a0, sp, 0xB8);
                v1 = sll(a0, 2);
                v1 = addu(v1, sp);
                sw(a1, v1, 96);
                v1 = addiu(a0, 1);
                sw(v1, sp, 0xB8);
            } else {
                // 0x0025703c
                charge(ctx, 6);
                v1 = sll(s1, 2);
                v1 = addu(v1, sp);
                sw(a0, v1, 160);
                s1 = addiu(s1, 1);
            }
        }
        // 0x0025708c
        charge(ctx, 2);
        if (s0 != s1) {
            // 0x00257094
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 1794;
            jal(ctx, 0x2570A0u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x002570a8
        charge(ctx, 4);
        a2 = 0;
        a1 = addiu(s1, -1);
        for (;;) {
            // 0x002570d8
            charge(ctx, 3);
            v1 = slt(a2, s1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002570b8
            charge(ctx, 8);
            v1 = subu(a1, a2);
            v1 = sll(v1, 2);
            v1 = addu(v1, sp);
            lw(a0, v1, 160);
            v1 = sll(a2, 2);
            v1 = addu(s3, v1);
            sw(a0, v1, 0);
            a2 = addiu(a2, 1);
        }
        // 0x002570e4
        charge(ctx, 4);
        lw(v1, s4, 0);
        v1 = v1 & 0x10;
        if (v1 == 0) {
            // 0x00257100
            charge(ctx, 2);
            v1 = 1;
            sw(v1, s2, 0);
        } else {
            // 0x002570f4
            charge(ctx, 3);
            sw(s1, s2, 0);
        }
    } else {
        // 0x00256fdc
        charge(ctx, 5);
        sw(s4, s3, 0);
        v1 = 1;
        sw(v1, s2, 0);
    }
    // 0x00257108 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x00257D00 sub_257D00 -- 144 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_257D00 (out pos, column, row?, columns): a card slot's position: the screen x of the column (sub_20C660), y 184,
// depth 90 unprojected (sub_20C500, sub_20C400), then y += 100
void sub_257D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00257d00
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a0 = a1;
    a1 = a3;
    jal(ctx, 0x257D20u, gen::fn_sub_20C660_0020c660);
    swc1(f0, sp, 0x38);
    v0 = 0x43380000;
    sw(v0, sp, 0x3C);
    v0 = 0x42B40000;
    mtc1(v0, f12);
    a0 = s0;
    jal(ctx, 0x257D40u, gen::fn_sub_20C500_0020c500);
    a0 = s0;
    a1 = addiu(sp, 0x38);
    mov_s(f12, f0);
    a2 = s1;
    jal(ctx, 0x257D58u, gen::fn_sub_20C400_0020c400);
    lwc1(f1, s1, 4);
    v1 = 0x42C80000;
    mtc1(v1, f0);
    add_s(f0, f1, f0);
    swc1(f0, s1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00257D90 sub_257D90 -- 132 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_257D90 (out pos, a1): the centre slot's position: screen (320, 184), depth 200, then y += 100
void sub_257D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00257d90
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = 0x43A00000;
    sw(v0, sp, 0x38);
    v0 = 0x43380000;
    sw(v0, sp, 0x3C);
    v0 = 0x43480000;
    mtc1(v0, f12);
    a0 = s0;
    jal(ctx, 0x257DC4u, gen::fn_sub_20C500_0020c500);
    a0 = s0;
    a1 = addiu(sp, 0x38);
    mov_s(f12, f0);
    a2 = s1;
    jal(ctx, 0x257DDCu, gen::fn_sub_20C400_0020c400);
    lwc1(f1, s1, 4);
    v1 = 0x42C80000;
    mtc1(v1, f0);
    add_s(f0, f1, f0);
    swc1(f0, s1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00257E20 sub_257E20 -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_257E20: debug dump of the deal list ("dump", each card's slot id and markers) through printf
void sub_257E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00257e20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00257e38
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x257E44u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00257e4c
    charge(ctx, 9);
    lw(s0, gp, kGpCard);
    a0 = addiu(gp, -26744);  // "dump\n"
    jal(ctx, 0x257E54u, gen::fn_printf_005225a8);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    lw(s0, v0, kLoListHead);
    for (;;) {
        // 0x00257ee4
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00257e70
        charge(ctx, 8);
        a0 = addiu(gp, -26736);  // "%d"
        lw(a1, s0, 20);
        jal(ctx, 0x257E78u, gen::fn_printf_005225a8);
        lw(v0, s0, 0);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x00257e90
            charge(ctx, 3);
            a0 = addiu(gp, -26732);  // &0x7CC484
            jal(ctx, 0x257E94u, gen::fn_printf_005225a8);
        }
        // 0x00257e9c
        charge(ctx, 4);
        lw(v0, s0, 0);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x00257eac
            charge(ctx, 3);
            a0 = addiu(gp, -26728);  // &0x7CC488
            jal(ctx, 0x257EB0u, gen::fn_printf_005225a8);
        }
        // 0x00257eb8
        charge(ctx, 4);
        lw(v0, s0, 0);
        v0 = v0 & 0x20;
        if (v0 != 0) {
            // 0x00257ec8
            charge(ctx, 3);
            a0 = addiu(gp, -26724);  // &0x7CC48C
            jal(ctx, 0x257ECCu, gen::fn_printf_005225a8);
        }
        // 0x00257ed4
        charge(ctx, 4);
        a0 = addiu(gp, -26720);  // &0x7CC490
        jal(ctx, 0x257ED8u, gen::fn_printf_005225a8);
        lw(s0, s0, kCardNext);
    }
    // 0x00257eec
    charge(ctx, 8);
    a0 = addiu(gp, -26716);  // "\n\n"
    jal(ctx, 0x257EF0u, gen::fn_printf_005225a8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00257F10 sub_257F10 -- 372 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_257F10: starts the deal animation: every top-level card flips in over 12 frames (sub_250CF0 with the table
// 0x68EA90 axis, the angle gp-32184; anim kind 2), work flags 0x2 | 0x40, state +0x12870 = 0
void sub_257F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00257f10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00257f30
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x257F3Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00257f44
    charge(ctx, 10);
    lw(s0, gp, kGpCard);
    v1 = 0x690000;
    ld(a0, v1, -5488);  // 0x68EA90
    v1 = 0x690000;
    lwc1(f0, v1, -5480);  // 0x68EA98
    sd(a0, sp, 0x40);
    swc1(f0, sp, 0x48);
    s2 = 0;
    for (;;) {
        // 0x0025802c
        charge(ctx, 6);
        v1 = 0x10000;
        v1 = addu(s0, v1);
        lw(v1, v1, kLoCardCount);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00257f6c
        charge(ctx, 3);
        lw(v0, gp, kGpCard);
        if (v0 == 0) {
            // 0x00257f78
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 188;
            jal(ctx, 0x257F84u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00257f8c
        charge(ctx, 6);
        lw(v1, gp, kGpCard);
        v0 = 0x10000;
        v0 = addu(v1, v0);
        lw(v1, v0, kLoListHead);
        for (;;) {
            // 0x00257fc8
            charge(ctx, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00257fa4
            charge(ctx, 5);
            s1 = v1;
            lw(v0, v1, 0);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x00257fb8
                charge(ctx, 3);
                lw(v0, v1, 16);
                if (v0 == s2) {
                    break;
                }
            }
            charge(ctx, 1);
            lw(v1, v1, kCardNext);
        }
        // 0x00257fd0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00257fd8
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -5632);  // "sfl_card.c"
            a1 = 1146;
            jal(ctx, 0x257FE4u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00257fec
        charge(ctx, 16);
        mtc1(zero, f13);
        a0 = addiu(s1, kCardPose4);
        a1 = addiu(sp, 0x40);
        lwc1(f12, gp, -32184);  // 0x7CAF38
        a2 = 12;
        jal(ctx, 0x258000u, gen::fn_sub_250CF0_00250cf0);
        sw(zero, s1, kCardAnimFrame);
        v1 = 12;
        sw(v1, s1, kCardAnimLength);
        v1 = 2;
        sw(v1, s1, kCardAnimKind);
        lw(v1, s1, 0);
        v1 = v1 | 0x200;
        sw(v1, s1, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00258044
    charge(ctx, 16);
    lw(v1, s0, 0);
    v1 = v1 | 0x2;
    sw(v1, s0, 0);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(zero, v1, kLoAnimState);
    lw(v1, s0, 0);
    v1 = v1 | 0x40;
    sw(v1, s0, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00258090 sub_258090 -- 80 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258090: work flag 0x2000 on, then turns the selected card (sub_258140)
void sub_258090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258090
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002580a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2580B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002580b8
    charge(ctx, 10);
    lw(v1, gp, kGpCard);
    lw(v0, v1, 0);
    v0 = v0 | 0x2000;
    sw(v0, v1, 0);
    jal(ctx, 0x2580C8u, gen::fn_sub_258140_00258140);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002580E0 sub_2580E0 -- 84 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2580E0: work flag 0x2000 off, then turns the selected card (sub_258140)
void sub_2580E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002580e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002580f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258100u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258108
    charge(ctx, 11);
    lw(a0, gp, kGpCard);
    lw(v1, a0, 0);
    v0 = si(-8193);
    v0 = v1 & v0;
    sw(v0, a0, 0);
    jal(ctx, 0x25811Cu, gen::fn_sub_258140_00258140);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00258140 sub_258140 -- 360 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258140: turns the selected card over (12 frames, the table 0x68EAA0 axis, anim kind 3), work flag 0x40 on, state
// 1, +0x12874 = 0, flag 0x2 off
void sub_258140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00258140
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258160
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x25816Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258174
    charge(ctx, 12);
    lw(s1, gp, kGpCard);
    v0 = 0x690000;
    ld(v1, v0, -5472);  // 0x68EAA0
    v0 = 0x690000;
    lwc1(f0, v0, -5464);  // 0x68EAA8
    sd(v1, sp, 0x40);
    swc1(f0, sp, 0x48);
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(s0, v0, kLoSelected);
    if (s1 == 0) {
        // 0x002581a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2581B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002581b8
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x002581f4
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002581d0
        charge(ctx, 5);
        s2 = v1;
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x002581e4
            charge(ctx, 3);
            lw(v0, v1, 16);
            if (v0 == s0) {
                break;
            }
        }
        charge(ctx, 1);
        lw(v1, v1, kCardNext);
    }
    // 0x002581fc
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00258204
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1146;
        jal(ctx, 0x258210u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258218
    charge(ctx, 36);
    mtc1(zero, f12);
    a0 = addiu(s2, kCardPose4);
    a1 = addiu(sp, 0x40);
    lwc1(f13, gp, -32184);  // 0x7CAF38
    a2 = 12;
    jal(ctx, 0x25822Cu, gen::fn_sub_250CF0_00250cf0);
    sw(zero, s2, kCardAnimFrame);
    v1 = 12;
    sw(v1, s2, kCardAnimLength);
    v1 = 3;
    sw(v1, s2, kCardAnimKind);
    lw(v1, s2, 0);
    v1 = v1 | 0x200;
    sw(v1, s2, 0);
    lw(v1, s1, 0);
    v1 = v1 | 0x40;
    sw(v1, s1, 0);
    a0 = 1;
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(a0, v1, kLoAnimState);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, 10356);
    lw(a0, s1, 0);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s1, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002582B0 sub_2582B0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2582B0 () -> flags & 0x40: a card animation running
void sub_2582B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002582b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002582c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2582D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002582d8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x40;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00258300 sub_258300 -- 388 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258300: resets the cards: releases every card in use, the textures (sub_2593D0), the counters and the list; card
// records free (slot id +20 = i)
void sub_258300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258300
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258320
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x25832Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258334
    charge(ctx, 4);
    lw(s1, gp, kGpCard);
    s2 = 0;
    for (;;) {
        // 0x002583e8
        charge(ctx, 3);
        v0 = slti(s2, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258344
        charge(ctx, 9);
        v0 = kCardStride;
        mult(v0, s2, v0);
        v0 = addu(s1, v0);
        s0 = addiu(v0, 4);
        lw(v1, v0, 4);
        v0 = nor(v1, 0);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x00258368
            charge(ctx, 3);
            v0 = v1 & 0x100;
            if (v0 != 0) {
                // 0x00258374
                charge(ctx, 3);
                v0 = v1 & 0x80;
                if (v0 != 0) {
                    // 0x00258380
                    charge(ctx, 3);
                    lw(a0, s0, kCardEffect);
                    jal(ctx, 0x258384u, gen::fn_sub_34FCF0_0034fcf0);
                }
                // 0x0025838c
                charge(ctx, 18);
                a0 = addiu(s0, kCardPose0);
                jal(ctx, 0x258390u, gen::fn_sub_24DAF0_0024daf0);
                a0 = addiu(s0, kCardPose2);
                jal(ctx, 0x25839Cu, gen::fn_sub_24DAF0_0024daf0);
                a0 = addiu(s0, kCardPose1);
                jal(ctx, 0x2583A8u, gen::fn_sub_24DAF0_0024daf0);
                a0 = addiu(s0, kCardPose3);
                jal(ctx, 0x2583B4u, gen::fn_sub_24DAF0_0024daf0);
                a0 = addiu(s0, kCardPose4);
                jal(ctx, 0x2583C0u, gen::fn_sub_24DAF0_0024daf0);
                a0 = addiu(s0, kCardPose5);
                jal(ctx, 0x2583CCu, gen::fn_sub_24DAF0_0024daf0);
            }
            // 0x002583d4
            charge(ctx, 4);
            lw(v1, s0, 0);
            v0 = si(-257);
            v0 = v1 & v0;
            sw(v0, s0, 0);
        }
        // 0x002583e4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x002583f4
    charge(ctx, 21);
    jal(ctx, 0x2583F4u, gen::fn_sub_2593D0_002593d0);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, kLoCardCount);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, kLoStackCount);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, kLoListHead);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, kLoListTail);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(zero, v1, kLoCmdCount);
    a1 = 0;
    a0 = kCardStride;
    for (;;) {
        // 0x0025845c
        charge(ctx, 3);
        v1 = slti(a1, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258448
        charge(ctx, 5);
        mult(v1, a1, a0);
        v1 = addu(s1, v1);
        sw(zero, v1, 4);
        sw(a1, v1, 24);
        a1 = addiu(a1, 1);
    }
    // 0x00258468
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00258490 sub_258490 -- 72 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258490: work flag 0x8
void sub_258490(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258490
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x002584a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2584B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002584b8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpCard);
    lw(v1, a0, 0);
    v1 = v1 | 0x8;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002584E0 sub_2584E0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2584E0 (speed): the command speed (+0x127B0)
void sub_2584E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002584e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x002584fc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258508u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258510 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    sw(s0, v1, kLoSpeed);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00258540 sub_258540 -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258540 (order, out vec3): the position of the card with that order (its first pose, sub_24F960)
void sub_258540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258540
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258568
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258574u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025857c
    charge(ctx, 3);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258588
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258594u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025859c
    charge(ctx, 6);
    lw(v1, gp, kGpCard);
    v0 = 0x10000;
    v0 = addu(v1, v0);
    lw(v1, v0, kLoListHead);
    for (;;) {
        // 0x002585d8
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002585b4
        charge(ctx, 5);
        s0 = v1;
        lw(v0, v1, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x002585c8
            charge(ctx, 3);
            lw(v0, v1, 16);
            if (v0 == s2) {
                break;
            }
        }
        charge(ctx, 1);
        lw(v1, v1, kCardNext);
    }
    // 0x002585e0
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x002585e8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 1146;
        jal(ctx, 0x2585F4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002585fc
    charge(ctx, 11);
    a0 = addiu(s0, kCardPose0);
    a1 = s1;
    jal(ctx, 0x258604u, gen::fn_sub_24F960_0024f960);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00258A50 sub_258A50 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258A50: plays the cursor sound (sub_10A4E0), state 2, work flags 0x40 | 0x80
void sub_258A50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258a50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258a68
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258A74u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258a7c
    charge(ctx, 27);
    lw(s0, gp, kGpCard);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x258A90u, gen::fn_sub_10A4E0_0010a4e0);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(zero, v1, 10364);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(zero, v1, 10360);
    a0 = 2;
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(a0, v1, kLoAnimState);
    lw(v1, s0, 0);
    v1 = v1 | 0x40;
    sw(v1, s0, 0);
    v1 = v1 | 0x80;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00258AF0 sub_258AF0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258AF0 () -> flags & 0x80: work flag 0x80
void sub_258AF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258af0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258b04
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258B10u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258b18 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x80;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00258F80 sub_258F80 -- 520 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_258F80 (stack card): breaks a stack up: its children (sub_259190) become top-level cards numbered after the
// stack's order (later orders move up), placed at the stack's position; the stack card leaves the list and is released
// (sub_253600); the card count grows by children - 1
void sub_258F80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00258f80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00258fa8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x258FB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00258fbc
    charge(ctx, 11);
    lw(s1, gp, kGpCard);
    a0 = s3;
    a1 = addiu(sp, 0x50);
    a2 = addiu(sp, 0x7C);
    jal(ctx, 0x258FCCu, gen::fn_sub_259190_00259190);
    v0 = 0x10000;
    v0 = addu(s1, v0);
    lw(a0, v0, kLoListHead);
    for (;;) {
        // 0x00259020
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00258fe8
        charge(ctx, 4);
        lw(v0, a0, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x00258ff8
            charge(ctx, 5);
            lw(v1, a0, 16);
            lw(v0, s3, 16);
            at = slt(v0, v1);
            if (at != 0) {
                // 0x0025900c
                charge(ctx, 4);
                lw(v0, sp, 0x7C);
                v0 = addiu(v0, -1);
                v0 = addu(v1, v0);
                sw(v0, a0, 16);
            }
        }
        // 0x0025901c
        charge(ctx, 1);
        lw(a0, a0, kCardNext);
    }
    // 0x00259028
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x00259084
        charge(ctx, 4);
        lw(v0, sp, 0x7C);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00259034
        charge(ctx, 20);
        v0 = sll(s2, 2);
        v0 = addu(v0, sp);
        lw(s0, v0, 80);
        lw(v1, s0, 0);
        v0 = si(-3);
        v0 = v1 & v0;
        sw(v0, s0, 0);
        lw(v1, s0, 16);
        lw(v0, s3, 16);
        v0 = addu(v1, v0);
        sw(v0, s0, 16);
        a0 = addiu(s3, kCardPose2);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x259068u, gen::fn_sub_24F960_0024f960);
        a0 = addiu(s0, kCardPose2);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x259078u, gen::fn_sub_24F9F0_0024f9f0);
        s2 = addiu(s2, 1);
    }
    // 0x00259094
    charge(ctx, 3);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002590a0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2590ACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002590b4
    charge(ctx, 4);
    lw(a0, gp, kGpCard);
    lw(v1, s3, kCardNext);
    if (v1 != 0) {
        // 0x002590c4
        charge(ctx, 2);
        lw(v0, s3, kCardPrev);
        sw(v0, v1, kCardPrev);
    }
    // 0x002590cc
    charge(ctx, 3);
    lw(v1, s3, kCardPrev);
    if (v1 != 0) {
        // 0x002590d8
        charge(ctx, 2);
        lw(v0, s3, kCardNext);
        sw(v0, v1, kCardNext);
    }
    // 0x002590e0
    charge(ctx, 5);
    v0 = 0x10000;
    v0 = addu(a0, v0);
    lw(v0, v0, kLoListHead);
    if (v0 == s3) {
        // 0x002590f4
        charge(ctx, 4);
        lw(v1, s3, kCardNext);
        v0 = 0x10000;
        v0 = addu(a0, v0);
        sw(v1, v0, kLoListHead);
    }
    // 0x00259104
    charge(ctx, 5);
    v0 = 0x10000;
    v0 = addu(a0, v0);
    lw(v0, v0, kLoListTail);
    if (v0 == s3) {
        // 0x00259118
        charge(ctx, 4);
        lw(v1, s3, kCardPrev);
        v0 = 0x10000;
        v0 = addu(a0, v0);
        sw(v1, v0, kLoListTail);
    }
    // 0x00259128
    charge(ctx, 24);
    a0 = s3;
    jal(ctx, 0x25912Cu, gen::fn_sub_253600_00253600);
    lw(a0, s3, 0);
    v1 = si(-5);
    v1 = a0 & v1;
    sw(v1, s3, 0);
    lw(v1, sp, 0x7C);
    a0 = addiu(v1, -1);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    lw(v1, v1, kLoCardCount);
    a0 = addu(v1, a0);
    v1 = 0x10000;
    v1 = addu(s1, v1);
    sw(a0, v1, kLoCardCount);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00259190 sub_259190 -- 188 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259190 (parent, out cards[], out count): the children of a stack (flag 0x2, parent +4040): out[child order] =
// child
void sub_259190(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259190
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x002591bc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2591C8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002591d0
    charge(ctx, 7);
    a1 = 0;
    lw(a0, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a0, v1);
    lw(a0, v1, kLoListHead);
    for (;;) {
        // 0x00259224
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002591ec
        charge(ctx, 5);
        lw(v1, a0, 0);
        v1 = nor(v1, 0);
        v1 = v1 & 0x2;
        if (v1 == 0) {
            // 0x00259200
            charge(ctx, 3);
            lw(v1, a0, kCardParent);
            if (v1 == s2) {
                // 0x0025920c
                charge(ctx, 5);
                lw(v1, a0, 16);
                v1 = sll(v1, 2);
                v1 = addu(s1, v1);
                sw(a0, v1, 0);
                a1 = addiu(a1, 1);
            }
        }
        // 0x00259220
        charge(ctx, 1);
        lw(a0, a0, kCardNext);
    }
    // 0x0025922c
    charge(ctx, 8);
    sw(a1, s0, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00259250 sub_259250 -- 112 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259250: state 3, work flags 0x40 | 0x100
void sub_259250(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259250
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00259264
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x259270u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259278 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    lw(a1, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a1, v1);
    sw(zero, v1, 10364);
    lw(v1, a1, 0);
    v1 = v1 | 0x40;
    sw(v1, a1, 0);
    a0 = 3;
    v1 = 0x10000;
    v1 = addu(a1, v1);
    sw(a0, v1, kLoAnimState);
    lw(v1, a1, 0);
    v1 = v1 | 0x100;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002592C0 sub_2592C0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2592C0 () -> flags & 0x100: work flag 0x100
void sub_2592C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002592c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002592d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2592E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002592e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x100;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259310 sub_259310 -- 112 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259310: state 4, work flags 0x40 | 0x800
void sub_259310(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259310
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x00259324
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x259330u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259338 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    lw(a1, gp, kGpCard);
    v1 = 0x10000;
    v1 = addu(a1, v1);
    sw(zero, v1, 10364);
    lw(v1, a1, 0);
    v1 = v1 | 0x40;
    sw(v1, a1, 0);
    a0 = 4;
    v1 = 0x10000;
    v1 = addu(a1, v1);
    sw(a0, v1, kLoAnimState);
    lw(v1, a1, 0);
    v1 = v1 | 0x800;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259380 sub_259380 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259380 () -> flags & 0x800: work flag 0x800
void sub_259380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259380
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x00259394
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2593A0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002593a8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x800;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002593D0 sub_2593D0 -- 236 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2593D0: releases the textures of every card in use that is no stack (kind 1: sub_21A670; kind 0: sub_21A760),
// work flag 0x400 off
void sub_2593D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002593d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpCard);
    if (v1 == 0) {
        // 0x002593ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2593F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259400
    charge(ctx, 4);
    lw(s0, gp, kGpCard);
    s1 = 0;
    for (;;) {
        // 0x00259488
        charge(ctx, 3);
        v1 = slti(s1, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00259410
        charge(ctx, 9);
        v1 = kCardStride;
        mult(v1, s1, v1);
        v1 = addu(s0, v1);
        a1 = addiu(v1, 4);
        lw(a0, v1, 4);
        v1 = nor(a0, 0);
        v1 = v1 & 0x4;
        if (v1 == 0) {
            // 0x00259434
            charge(ctx, 3);
            v1 = a0 & 0x8;
            if (v1 == 0) {
                // 0x00259440
                charge(ctx, 4);
                lw(a0, a1, 4);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00259474
                    charge(ctx, 4);
                    lw(a0, a1, 8);
                    lw(a1, a1, 12);
                    jal(ctx, 0x25947Cu, gen::fn_sub_21A670_0021a670);
                } else {
                    // 0x00259450
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00259460
                        charge(ctx, 5);
                        lhu(a0, a1, 8);
                        jal(ctx, 0x259464u, gen::fn_sub_21A760_0021a760);
                    } else {
                        // 0x00259458
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x00259484
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00259494
    charge(ctx, 10);
    lw(a0, s0, 0);
    v1 = si(-1025);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002594C0 sub_2594C0 -- 244 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2594C0: picks a random card (+0x12884 = RpRandom() % card count), starts the second work pose's 90-frame turn
// (sub_250CF0), the sound (sub_10A4E0), state 5, work flags 0x40 | 0x1000
void sub_2594C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x002594c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002594d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2594E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002594ec
    charge(ctx, 50);
    lw(s0, gp, kGpCard);
    v0 = 0x690000;
    ld(v1, v0, -5440);  // 0x68EAC0
    v0 = 0x690000;
    lwc1(f0, v0, -5432);  // 0x68EAC8
    sd(v1, sp, 0x20);
    swc1(f0, sp, 0x28);
    jal(ctx, 0x259508u, gen::fn_sub_488F30_00488f30);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    lw(v1, v1, kLoCardCount);
    divu(v0, v1);
    mfhi(v1);
    v0 = 0x10000;
    v0 = addu(s0, v0);
    sw(v1, v0, 10372);
    at = 0x10000;
    at = at | 0x2800;
    a0 = addu(s0, at);
    a1 = addiu(sp, 0x20);
    lwc1(f12, gp, -32184);  // 0x7CAF38
    lwc1(f13, gp, -31808);  // 0x7CB0B0
    a2 = 90;
    jal(ctx, 0x25954Cu, gen::fn_sub_250CF0_00250cf0);
    a0 = 1;
    a1 = 2;
    a2 = 6;
    a3 = a1;
    jal(ctx, 0x259564u, gen::fn_sub_10A4E0_0010a4e0);
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(zero, v1, 10364);
    lw(v1, s0, 0);
    v1 = v1 | 0x40;
    sw(v1, s0, 0);
    a0 = 5;
    v1 = 0x10000;
    v1 = addu(s0, v1);
    sw(a0, v1, kLoAnimState);
    lw(v1, s0, 0);
    v1 = v1 | 0x1000;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002595C0 sub_2595C0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2595C0 () -> flags & 0x1000: work flag 0x1000
void sub_2595C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002595c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCard);
    if (v0 == 0) {
        // 0x002595d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5632);  // "sfl_card.c"
        a1 = 188;
        jal(ctx, 0x2595E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002595e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCard);
    lw(v0, v0, 0);
    v0 = v0 & 0x1000;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259610 sub_259610 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_script.c: the shuffle script: command writer, runner and the nine command handlers (gp-18840)
// ====================================================================================================================

// sub_259610 (work): sfl_script init: flags and the wait counter 0, gp-18840 = work
void sub_259610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00259610
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 20);
    sw(a0, gp, kGpScript);
}

// 0x00259630 sub_259630 -- 12 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259630: sfl_script shutdown: gp-18840 = 0
void sub_259630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x00259630
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpScript);
}

// 0x00259640 sub_259640 -- 80 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259640: rewinds the script (pc = buffer) and starts it (flag 0x1)
void sub_259640(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259640
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpScript);
    if (v1 == 0) {
        // 0x00259654
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259660u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259668 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(a0, gp, kGpScript);
    lw(v1, a0, 4);
    sw(v1, a0, 8);
    lw(v1, a0, 0);
    v1 = v1 | 0x1;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259690 sub_259690 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259690 (buffer, size): the script buffer: buffer, write pointer = buffer, size
void sub_259690(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259690
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpScript);
    if (v1 == 0) {
        // 0x002596b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x2596C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002596c8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(v1, gp, kGpScript);
    sw(s1, v1, 4);
    sw(s1, v1, 12);
    sw(s0, v1, 16);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002596F0 sub_2596F0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2596F0 () -> flags & 1: the script running
void sub_2596F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002596f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259704
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259710u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259718 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpScript);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259740 sub_259740 -- 264 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259740: runs the script: while running, the command at pc (u16 op; table 0x68EAD0 {handler, u16 argument size})
// is called with its arguments (aligned to 4) through jalr until a handler returns 0 (pc stays: the command runs again
// next frame); else pc moves past it (aligned to 2)
void sub_259740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259740
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpScript);
    if (v1 == 0) {
        // 0x0025975c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259768u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259770
    charge(ctx, 6);
    lw(s1, gp, kGpScript);
    lw(v1, s1, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        for (;;) {
            // 0x00259788
            charge(ctx, 11);
            lw(a0, s1, 8);
            lhu(v0, a0, 0);
            v1 = sll(v0, 3);
            v0 = 0x690000;
            v0 = addiu(v0, -5424);  // &0x68EAD0
            s0 = addu(v0, v1);
            lhu(v0, s0, 4);
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                // 0x002597d0
                charge(ctx, 1);
                a0 = 0;
            } else {
                // 0x002597b4
                charge(ctx, 4);
                a0 = addiu(a0, 2);
                v0 = a0 & 0x3;
                if (v0 != 0) {
                    // 0x002597c4
                    charge(ctx, 3);
                    a0 = addiu(a0, 2);
                }
            }
            // 0x002597d4
            charge(ctx, 5);
            lw(v0, s0, 0);
            jalr(ctx, 0x2597D8u, v0.u());  // handler(arguments or 0): 0 = stay on this command
            if (v0 == 0) {
                break;
            }
            // 0x002597e8
            charge(ctx, 5);
            lw(v0, s1, 8);
            a0 = addiu(v0, 2);
            lhu(v1, s0, 4);
            if (v1 != 0) {
                // 0x002597fc
                charge(ctx, 3);
                v0 = a0 & 0x3;
                if (v0 != 0) {
                    // 0x00259808
                    charge(ctx, 1);
                    a0 = addiu(a0, 2);
                }
                // 0x0025980c
                charge(ctx, 5);
                v0 = v1 & 0xFFFF;
                a0 = addu(a0, v0);
                v0 = a0 & 0x1;
                if (v0 != 0) {
                    // 0x00259820
                    charge(ctx, 1);
                    a0 = addiu(a0, 1);
                }
            }
            // 0x00259824
            charge(ctx, 3);
            sw(a0, s1, 8);
            backedge(ctx);
        }
    }
    // 0x00259830 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00259850 sub_259850 -- 284 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259850 (op, arguments): appends a command: u16 op, then (aligned to 4) the argument bytes the table gives
// (memcpy), the write pointer aligned to 2; K_Assert when the buffer size is exceeded
void sub_259850(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259850
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(v1, gp, kGpScript);
    if (v1 == 0) {
        // 0x0025987c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259888u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259890
    charge(ctx, 11);
    lw(s0, gp, kGpScript);
    lw(v1, s0, 12);
    sh(s3, v1, 0);  // the op at the write pointer (+12)
    s1 = addiu(v1, 2);
    a0 = sll(s3, 3);
    v1 = 0x690000;
    v1 = addiu(v1, -5420);  // &0x68EAD4
    v1 = addu(v1, a0);
    lhu(a0, v1, 0);
    if (a0 != 0) {
        // 0x002598bc
        charge(ctx, 3);
        v0 = s1 & 0x3;
        if (v0 != 0) {
            // 0x002598c8
            charge(ctx, 1);
            s1 = addiu(s1, 2);
        }
        // 0x002598cc
        charge(ctx, 11);
        v1 = sll(s3, 3);
        v0 = 0x690000;
        v0 = addiu(v0, -5420);  // &0x68EAD4
        s3 = addu(v0, v1);
        a2 = a0 & 0xFFFF;
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x2598E8u, gen::fn_memcpy_00521250);
        lhu(v1, s3, 0);
        s1 = addu(s1, v1);
    }
    // 0x002598f8
    charge(ctx, 10);
    lw(a0, s0, 12);
    v1 = subu(s1, a0);
    a0 = addu(a0, v1);
    sw(a0, s0, 12);
    lw(v1, s0, 4);
    a0 = subu(a0, v1);
    lw(v1, s0, 16);
    at = slt(v1, a0);
    if (at != 0) {
        // 0x00259920
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 178;
        jal(ctx, 0x25992Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259934
    charge(ctx, 4);
    lw(a0, s0, 12);
    v1 = a0 & 0x1;
    if (v1 != 0) {
        // 0x00259944
        charge(ctx, 2);
        v1 = addiu(a0, 1);
        sw(v1, s0, 12);
    }
    // 0x0025994c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00259970 sub_259970 -- 72 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259970: writes END (op 0)
void sub_259970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259970
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259984
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259990u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259998
    charge(ctx, 8);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x2599A0u, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002599C0 sub_2599C0 -- 148 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_2599C0 (a, b): writes SWAP a, b (op 1)
void sub_2599C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002599c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x002599e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x2599F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002599f8
    charge(ctx, 4);
    v1 = addiu(sp, 0x3C);
    v0 = 4;
    if (v1 != 0) {
        for (;;) {
            // 0x00259a08
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00259a24
    charge(ctx, 12);
    sh(s1, sp, 0x3C);
    sh(s0, sp, 0x3E);
    a0 = 1;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x259A34u, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00259A60 sub_259A60 -- 148 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259A60 (a, b): writes CLOSE a, b (op 3)
void sub_259A60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259a60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259a84
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259A90u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259a98
    charge(ctx, 4);
    v1 = addiu(sp, 0x3C);
    v0 = 4;
    if (v1 != 0) {
        for (;;) {
            // 0x00259aa8
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00259ac4
    charge(ctx, 12);
    sh(s1, sp, 0x3C);
    sh(s0, sp, 0x3E);
    a0 = 3;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x259AD4u, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00259B00 sub_259B00 -- 88 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259B00 (n): writes WAIT n (op 2)
void sub_259B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259b00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259b1c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259B28u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259b30
    charge(ctx, 10);
    sh(s0, sp, 0x2E);
    a0 = 2;
    a1 = addiu(sp, 0x2E);
    jal(ctx, 0x259B3Cu, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00259B60 sub_259B60 -- 88 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259B60 (n): writes OPEN n (op 4)
void sub_259B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259b60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259b7c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259B88u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259b90
    charge(ctx, 10);
    sh(s0, sp, 0x2E);
    a0 = 4;
    a1 = addiu(sp, 0x2E);
    jal(ctx, 0x259B9Cu, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00259BC0 sub_259BC0 -- 72 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259BC0: writes op 5 (wait until no card is marked)
void sub_259BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259bc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259bd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259BE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259be8
    charge(ctx, 8);
    a0 = 5;
    a1 = 0;
    jal(ctx, 0x259BF0u, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259C10 sub_259C10 -- 72 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259C10: writes START_ACT (op 6)
void sub_259C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259c10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259c24
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259C30u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259c38
    charge(ctx, 8);
    a0 = 6;
    a1 = 0;
    jal(ctx, 0x259C40u, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259C60 sub_259C60 -- 88 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259C60 (speed): writes SPEED (op 7)
void sub_259C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259c60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259c7c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259C88u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259c90
    charge(ctx, 10);
    sh(s0, sp, 0x2E);
    a0 = 7;
    a1 = addiu(sp, 0x2E);
    jal(ctx, 0x259C9Cu, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00259CC0 sub_259CC0 -- 72 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259CC0: writes op 8 (start the act and wait for it)
void sub_259CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259cc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259cd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259CE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259ce8
    charge(ctx, 8);
    a0 = 8;
    a1 = 0;
    jal(ctx, 0x259CF0u, gen::fn_sub_259850_00259850);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259D10 sub_259D10 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259D10 (args) -> 0: END: "sfli: END", stops the script (flag 0x1 off)
void sub_259D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259d10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259d28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259D34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259d3c
    charge(ctx, 15);
    lw(s0, gp, kGpScript);
    a0 = 0x690000;
    a0 = addiu(a0, -5336);  // "sfli: END\n"
    jal(ctx, 0x259D48u, gen::fn_printf_005225a8);
    lw(v1, s0, 0);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, s0, 0);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00259D80 sub_259D80 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259D80 (args) -> 1: SWAP: "sfli: SWAP %d, %d", queues the swap (sub_2551D0)
void sub_259D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259d80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259da0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259DACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259db4
    charge(ctx, 18);
    s0 = addiu(s1, 2);
    lh(a1, s1, 0);
    lh(a2, s1, 2);
    a0 = 0x690000;
    a0 = addiu(a0, -5312);  // "sfli: SWAP %d, %d\n"
    jal(ctx, 0x259DC8u, gen::fn_printf_005225a8);
    lh(a0, s1, 0);
    lh(a1, s0, 0);
    jal(ctx, 0x259DD8u, gen::fn_sub_2551D0_002551d0);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00259E00 sub_259E00 -- 88 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259E00 (args) -> bool: waits until no card is marked (sub_256430)
void sub_259E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259e00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259e14
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259E20u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259e28
    charge(ctx, 4);
    jal(ctx, 0x259E28u, gen::fn_sub_256430_00256430);
    if (v0 == 0) {
        // 0x00259e44
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x00259e38
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00259e48 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259E60 sub_259E60 -- 52 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259E60 (args) -> 1: START_ACT: "sfli: START_ACT", starts the act (sub_257130)
void sub_259E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259e60
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x690000;
    a0 = addiu(a0, -5280);  // "sfli: START_ACT\n"
    jal(ctx, 0x259E70u, gen::fn_printf_005225a8);
    jal(ctx, 0x259E78u, gen::fn_sub_257130_00257130);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259EA0 sub_259EA0 -- 40 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259EA0 (args) -> 1: SPEED: the command speed (sub_2584E0)
void sub_259EA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259ea0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(a0, a0, 0);
    jal(ctx, 0x259EACu, gen::fn_sub_2584E0_002584e0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259ED0 sub_259ED0 -- 108 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259ED0 (args) -> bool: starts the shuffle act once (sub_255B20, gp-18836 = 1) and returns 1 when it has finished
// (sub_255F30 clear; gp-18836 = 0)
void sub_259ED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259ed0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpActStarted);
    if (v0 != 0) {
        // 0x00259efc
        charge(ctx, 4);
        jal(ctx, 0x259EFCu, gen::fn_sub_255F30_00255f30);
        if (v0 == 0) {
            // 0x00259f18
            charge(ctx, 4);
            sw(zero, gp, kGpActStarted);
            v0 = 1;
        } else {
            // 0x00259f0c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00259ee4
        charge(ctx, 6);
        jal(ctx, 0x259EE4u, gen::fn_sub_255B20_00255b20);
        v0 = 1;
        sw(v0, gp, kGpActStarted);
        // 0x00259f28
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00259f2c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00259F40 sub_259F40 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259F40 (args) -> 1: CLOSE: "sfli: CLOSE %d, %d", gathers b cards from order a into a stack (sub_255570)
void sub_259F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259f40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259f60
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259F6Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259f74
    charge(ctx, 18);
    s0 = addiu(s1, 2);
    lh(a1, s1, 0);
    lh(a2, s1, 2);
    a0 = 0x690000;
    a0 = addiu(a0, -5248);  // "sfli: CLOSE %d, %d\n"
    jal(ctx, 0x259F88u, gen::fn_printf_005225a8);
    lh(a0, s1, 0);
    lh(a1, s0, 0);
    jal(ctx, 0x259F98u, gen::fn_sub_255570_00255570);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00259FC0 sub_259FC0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_259FC0 (args) -> 1: OPEN: "sfli: OPEN %d", spreads stack n (sub_255810)
void sub_259FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00259fc0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x00259fdc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x259FE8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00259ff0
    charge(ctx, 14);
    lh(a1, s0, 0);
    a0 = 0x690000;
    a0 = addiu(a0, -5224);  // "sfli: OPEN %d\n"
    jal(ctx, 0x259FFCu, gen::fn_printf_005225a8);
    lh(a0, s0, 0);
    jal(ctx, 0x25A008u, gen::fn_sub_255810_00255810);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0025A030 sub_25A030 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25A030 (args) -> bool: WAIT n: on the first frame "sfli: WAIT %d" and the counter 0 (n == 0 ends at once), then
// counts frames until n (flag 0x2 while waiting)
void sub_25A030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025a030
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpScript);
    if (v0 == 0) {
        // 0x0025a054
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5352);  // "sfl_script.c"
        a1 = 67;
        jal(ctx, 0x25A060u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025a068
    charge(ctx, 7);
    lw(s1, gp, kGpScript);
    lhu(s0, s2, 0);
    lw(v0, s1, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0025a0b0
        charge(ctx, 5);
        lw(v0, s1, 20);
        v0 = addiu(v0, 1);
        sw(v0, s1, 20);
        if (v0 != s0) {
        L_0025a0e0:
            charge(ctx, 4);
            lw(v0, s1, 0);
            v0 = v0 | 0x2;
            sw(v0, s1, 0);
            v0 = 0;
        } else {
            // 0x0025a0c4
            charge(ctx, 7);
            lw(v1, s1, 0);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s1, 0);
            v0 = 1;
        }
    } else {
        // 0x0025a084
        charge(ctx, 8);
        lh(a1, s2, 0);
        a0 = 0x690000;
        a0 = addiu(a0, -5208);  // "sfli: WAIT %d\n"
        jal(ctx, 0x25A090u, gen::fn_printf_005225a8);
        sw(zero, s1, 20);
        if (s0 != 0) {
            goto L_0025a0e0;
        }
        // 0x0025a0a4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0025a0f0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0025AA70 sub_25AA70 -- 84 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_cursor.c: the selection cursor (gp-18832) and the Shuffle Time counters
// ====================================================================================================================

// sub_25AA70: cursor mode 3, +40 = 0, flag 0x2 (moving)
void sub_25AA70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025aa70
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCursor);
    if (v1 == 0) {
        // 0x0025aa84
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5192);  // "sfl_cursor.c"
        a1 = 71;
        jal(ctx, 0x25AA90u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025aa98 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(a0, gp, kGpCursor);
    sw(zero, a0, 40);
    v1 = 3;
    sw(v1, a0, 3232);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025B300 sub_25B300 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B300 (order): moves the cursor from its card (+48) to the card `order` (positions sub_258540 -> +4 / +16,
// start +28 = +4), mode 0, then updates it (sub_25AAD0)
void sub_25B300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0025b300
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpCursor);
    if (v0 == 0) {
        // 0x0025b320
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5192);  // "sfl_cursor.c"
        a1 = 71;
        jal(ctx, 0x25B32Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025b334
    charge(ctx, 31);
    lw(s0, gp, kGpCursor);
    lw(a0, s0, 48);
    a1 = addiu(s0, 4);
    jal(ctx, 0x25B340u, gen::fn_sub_258540_00258540);
    a0 = s1;
    a1 = addiu(s0, 16);
    jal(ctx, 0x25B350u, gen::fn_sub_258540_00258540);
    lwc1(f2, s0, 4);
    lwc1(f1, s0, 8);
    lwc1(f0, s0, 12);
    swc1(f2, s0, 28);
    swc1(f1, s0, 32);
    swc1(f0, s0, 36);
    lw(v0, s0, 48);
    sw(v0, s0, 44);
    sw(s1, s0, 48);
    sw(zero, s0, 40);
    sw(zero, s0, 3232);
    lw(v0, s0, 0);
    v0 = v0 | 0x2;
    sw(v0, s0, 0);
    jal(ctx, 0x25B390u, gen::fn_sub_25AAD0_0025aad0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0025B3B0 sub_25B3B0 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B3B0 (order): moves the cursor to the card `order` in mode 1 (the target position -> +28), then updates it
void sub_25B3B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025b3b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpCursor);
    if (v0 == 0) {
        // 0x0025b3d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5192);  // "sfl_cursor.c"
        a1 = 71;
        jal(ctx, 0x25B3DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025b3e4
    charge(ctx, 22);
    lw(s0, gp, kGpCursor);
    a0 = s1;
    a1 = addiu(s0, 28);
    jal(ctx, 0x25B3F0u, gen::fn_sub_258540_00258540);
    lw(v0, s0, 48);
    sw(v0, s0, 44);
    sw(s1, s0, 48);
    sw(zero, s0, 40);
    v0 = 1;
    sw(v0, s0, 3232);
    lw(v0, s0, 0);
    v0 = v0 | 0x2;
    sw(v0, s0, 0);
    jal(ctx, 0x25B41Cu, gen::fn_sub_25AAD0_0025aad0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0025B440 sub_25B440 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B440: arms the Shuffle Time counters: game counter 57 = 0, 56 = 24 + RpRandom() % 5 (called by
// kwlnInitGameData / kwlnInitGameData2) [sflCountReset]
void sub_25B440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025b440
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 24;  // the limit: 24 + RpRandom() % 5 battles
    jal(ctx, 0x25B450u, gen::fn_sub_488F30_00488f30);
    v1 = 5;
    divu(v0, v1);
    mfhi(v0);
    s0 = addu(s0, v0);
    a0 = 57;
    a1 = 0;
    jal(ctx, 0x25B470u, gen::fn_sub_16F3E0_0016f3e0);
    a0 = 56;
    a1 = s0;
    jal(ctx, 0x25B480u, gen::fn_sub_16F3E0_0016f3e0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0025B4A0 sub_25B4A0 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_count.c: the countdown digits (gp-18828)
// ====================================================================================================================

// sub_25B4A0 (work): sfl_count init: flags 0, gp-18828 = work
void sub_25B4A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0025b4a0
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpCount);
}

// 0x0025B4B0 sub_25B4B0 -- 60 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B4B0: sfl_count shutdown: gp-18828 = 0
void sub_25B4B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025b4b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCount);
    if (v1 == 0) {
        // 0x0025b4c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5176);  // "sfl_count.c"
        a1 = 43;
        jal(ctx, 0x25B4D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025b4d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpCount);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025B4F0 sub_25B4F0 -- 252 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B4F0: sets up the three digit sprites: each sprite's uv rect from the shuffle sprite's size (sub_20E610 i:
// 0/w, 0/h, w/w, h/h on the guest frame) into the two quads +16 + 256 i and +784 + 256 i (sub_21EB80); +4 = +8 = 0,
// flag 0x1 on, 0x2 off
void sub_25B4F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0025b4f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpCount);
    if (v1 == 0) {
        // 0x0025b510
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5176);  // "sfl_count.c"
        a1 = 43;
        jal(ctx, 0x25B51Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025b524
    charge(ctx, 4);
    lw(s0, gp, kGpCount);
    s2 = 0;
    for (;;) {
        // 0x0025b5a4
        charge(ctx, 3);
        v1 = slti(s2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025b534
        charge(ctx, 28);
        a0 = s2;
        jal(ctx, 0x25B538u, gen::fn_sub_20E610_0020e610);
        lwc1(f0, v0, 12);
        cvt_s_w(f3, f0);
        lwc1(f0, v0, 16);
        cvt_s_w(f2, f0);
        mtc1(zero, f1);
        div_s(f0, f1, f3);
        swc1(f0, sp, 0x40);
        div_s(f0, f1, f2);
        swc1(f0, sp, 0x44);
        div_s(f0, f3, f3);
        swc1(f0, sp, 0x48);
        div_s(f0, f2, f2);
        swc1(f0, sp, 0x4C);
        v0 = sll(s2, 8);
        s1 = addu(s0, v0);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x25B588u, gen::fn_sub_21EB80_0021eb80);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x25B598u, gen::fn_sub_21EB80_0021eb80);
        s2 = addiu(s2, 1);
    }
    // 0x0025b5b0
    charge(ctx, 15);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    lw(a0, s0, 0);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    v1 = v1 | 0x1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0025B5F0 sub_25B5F0 -- 76 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B5F0: starts the count: +8 = 0, flag 0x2
void sub_25B5F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025b5f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpCount);
    if (v1 == 0) {
        // 0x0025b604
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5176);  // "sfl_count.c"
        a1 = 43;
        jal(ctx, 0x25B610u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025b618 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, gp, kGpCount);
    sw(zero, a0, 8);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025B640 sub_25B640 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_25B640 () -> flags & 1: the count set up
void sub_25B640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025b640
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpCount);
    if (v0 == 0) {
        // 0x0025b654
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5176);  // "sfl_count.c"
        a1 = 43;
        jal(ctx, 0x25B660u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025b668 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpCount);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00260A10 sub_260A10 -- 60 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// ====================================================================================================================
// sfl_psel2.c: the persona-select page (gp-18808)
// ====================================================================================================================

// sub_260A10: sfl_psel2 shutdown: gp-18808 = 0
void sub_260A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00260a10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpPsel2);
    if (v1 == 0) {
        // 0x00260a24
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x260A30u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00260a38 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpPsel2);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00260BD0 sub_260BD0 -- 76 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_260BD0: flag 0x1 off
void sub_260BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00260bd0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpPsel2);
    if (v1 == 0) {
        // 0x00260be4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x260BF0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00260bf8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpPsel2);
    lw(a0, a1, 0);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00260C20 sub_260C20 -- 80 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_260C20: opens page 0 (+4 = 0, +8 = 0, flag 0x2)
void sub_260C20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00260c20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpPsel2);
    if (v1 == 0) {
        // 0x00260c34
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x260C40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00260c48 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(a0, gp, kGpPsel2);
    sw(zero, a0, 8);
    sw(zero, a0, 4);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00260C70 sub_260C70 -- 84 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_260C70: opens page 1 (+4 = 1, +8 = 0, flag 0x2)
void sub_260C70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00260c70
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpPsel2);
    if (v1 == 0) {
        // 0x00260c84
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x260C90u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00260c98 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(a0, gp, kGpPsel2);
    sw(zero, a0, 8);
    v1 = 1;
    sw(v1, a0, 4);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00260CD0 sub_260CD0 -- 68 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// sub_260CD0 () -> flags & 2: a page open
void sub_260CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00260cd0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpPsel2);
    if (v0 == 0) {
        // 0x00260ce4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5096);  // "sfl_psel2.c"
        a1 = 87;
        jal(ctx, 0x260CF0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00260cf8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpPsel2);
    lw(v0, v0, 0);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
