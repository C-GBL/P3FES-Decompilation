// Animation and skinning (slice anim; anim.h documents the records and the animation state of a character):
// RenderWare's RtAnim (interpolators, animations, their streams, the scheme registry), RpHAnim (the hierarchy plugin,
// its standard keyframe scheme, the hierarchy matrix update), RpSkin (the skin plugin: geometry / atomic extensions,
// streams, skin types and pipelines, the per-vertex weight packing), RpUVAnim with its RtDict dictionaries, the
// compressed keyframe scheme every character animation uses (id 2), the game's own keyframe scheme (0x44A07195) and
// two model-manager leftovers (sub_311730 the look-at hierarchy update, sub_317730 the per-model frame update). The
// bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): register for register and block for block as the
// recompiled bodies -- frame, spills, $ra links, cycle charges and check points -- with each function's role and
// proposed name above it, the record offsets named (anim:: / mdl:: constants; the same values) and the callee roles
// on the calls. Proposed names in brackets follow the public RenderWare 3.x API where the body matches it.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/anim.h"
#include "p3fes/game/models.h"

namespace p3fes::recomp_gen {
void fn_RpPDSGetPipe_0046a890(p3fes::EEContext&);
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_name__C9type_info_0048a3d0(p3fes::EEContext&);
void fn_name__C9type_info_1_004c21d0(p3fes::EEContext&);
void fn_nullsub_125_004b8610(p3fes::EEContext&);
void fn_nullsub_126_004b8620(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_311480_00311480(p3fes::EEContext&);
void fn_sub_311730_00311730(p3fes::EEContext&);
void fn_sub_313490_00313490(p3fes::EEContext&);
void fn_sub_314D30_00314d30(p3fes::EEContext&);
void fn_sub_317730_00317730(p3fes::EEContext&);
void fn_sub_3185B0_003185b0(p3fes::EEContext&);
void fn_sub_3189F0_003189f0(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318D10_00318d10(p3fes::EEContext&);
void fn_sub_3191D0_003191d0(p3fes::EEContext&);
void fn_sub_319210_00319210(p3fes::EEContext&);
void fn_sub_319770_00319770(p3fes::EEContext&);
void fn_sub_3197C0_003197c0(p3fes::EEContext&);
void fn_sub_31D9C0_0031d9c0(p3fes::EEContext&);
void fn_sub_31DDA0_0031dda0(p3fes::EEContext&);
void fn_sub_31F5C0_0031f5c0(p3fes::EEContext&);
void fn_sub_35A290_0035a290(p3fes::EEContext&);
void fn_sub_35A3F0_0035a3f0(p3fes::EEContext&);
void fn_sub_35A620_0035a620(p3fes::EEContext&);
void fn_sub_35A6A0_0035a6a0(p3fes::EEContext&);
void fn_sub_35A770_0035a770(p3fes::EEContext&);
void fn_sub_35A850_0035a850(p3fes::EEContext&);
void fn_sub_35A870_0035a870(p3fes::EEContext&);
void fn_sub_35AA10_0035aa10(p3fes::EEContext&);
void fn_sub_35ABA0_0035aba0(p3fes::EEContext&);
void fn_sub_464760_00464760(p3fes::EEContext&);
void fn_sub_464850_00464850(p3fes::EEContext&);
void fn_sub_464E80_00464e80(p3fes::EEContext&);
void fn_sub_4654A0_004654a0(p3fes::EEContext&);
void fn_sub_465590_00465590(p3fes::EEContext&);
void fn_sub_465660_00465660(p3fes::EEContext&);
void fn_sub_465670_00465670(p3fes::EEContext&);
void fn_sub_4657D0_004657d0(p3fes::EEContext&);
void fn_sub_465930_00465930(p3fes::EEContext&);
void fn_sub_465A00_00465a00(p3fes::EEContext&);
void fn_sub_465AE0_00465ae0(p3fes::EEContext&);
void fn_sub_465B20_00465b20(p3fes::EEContext&);
void fn_sub_465B40_00465b40(p3fes::EEContext&);
void fn_sub_465BF0_00465bf0(p3fes::EEContext&);
void fn_sub_465CF0_00465cf0(p3fes::EEContext&);
void fn_sub_465EB0_00465eb0(p3fes::EEContext&);
void fn_sub_466130_00466130(p3fes::EEContext&);
void fn_sub_4661B0_004661b0(p3fes::EEContext&);
void fn_sub_466260_00466260(p3fes::EEContext&);
void fn_sub_4663D0_004663d0(p3fes::EEContext&);
void fn_sub_466480_00466480(p3fes::EEContext&);
void fn_sub_466640_00466640(p3fes::EEContext&);
void fn_sub_466710_00466710(p3fes::EEContext&);
void fn_sub_466720_00466720(p3fes::EEContext&);
void fn_sub_466730_00466730(p3fes::EEContext&);
void fn_sub_466EF0_00466ef0(p3fes::EEContext&);
void fn_sub_4699B0_004699b0(p3fes::EEContext&);
void fn_sub_489020_00489020(p3fes::EEContext&);
void fn_sub_489080_00489080(p3fes::EEContext&);
void fn_sub_489160_00489160(p3fes::EEContext&);
void fn_sub_489320_00489320(p3fes::EEContext&);
void fn_sub_489350_00489350(p3fes::EEContext&);
void fn_sub_4893E0_004893e0(p3fes::EEContext&);
void fn_sub_489460_00489460(p3fes::EEContext&);
void fn_sub_489550_00489550(p3fes::EEContext&);
void fn_sub_489730_00489730(p3fes::EEContext&);
void fn_sub_489840_00489840(p3fes::EEContext&);
void fn_sub_4898C0_004898c0(p3fes::EEContext&);
void fn_sub_4898E0_004898e0(p3fes::EEContext&);
void fn_sub_489950_00489950(p3fes::EEContext&);
void fn_sub_489960_00489960(p3fes::EEContext&);
void fn_sub_4899A0_004899a0(p3fes::EEContext&);
void fn_sub_4899BC_004899bc(p3fes::EEContext&);
void fn_sub_4899D0_004899d0(p3fes::EEContext&);
void fn_sub_4899F0_004899f0(p3fes::EEContext&);
void fn_sub_489A80_00489a80(p3fes::EEContext&);
void fn_sub_489AE0_00489ae0(p3fes::EEContext&);
void fn_sub_489B70_00489b70(p3fes::EEContext&);
void fn_sub_489CD0_00489cd0(p3fes::EEContext&);
void fn_sub_489F20_00489f20(p3fes::EEContext&);
void fn_sub_48A180_0048a180(p3fes::EEContext&);
void fn_sub_48A190_0048a190(p3fes::EEContext&);
void fn_sub_48A1A0_0048a1a0(p3fes::EEContext&);
void fn_sub_48A2A0_0048a2a0(p3fes::EEContext&);
void fn_sub_48A2C0_0048a2c0(p3fes::EEContext&);
void fn_sub_48A2E0_0048a2e0(p3fes::EEContext&);
void fn_sub_48A370_0048a370(p3fes::EEContext&);
void fn_sub_48A3F0_0048a3f0(p3fes::EEContext&);
void fn_sub_48A480_0048a480(p3fes::EEContext&);
void fn_sub_48A4B0_0048a4b0(p3fes::EEContext&);
void fn_sub_48A790_0048a790(p3fes::EEContext&);
void fn_sub_48A7A0_0048a7a0(p3fes::EEContext&);
void fn_sub_48A800_0048a800(p3fes::EEContext&);
void fn_sub_48A9A0_0048a9a0(p3fes::EEContext&);
void fn_sub_48ABF0_0048abf0(p3fes::EEContext&);
void fn_sub_48AC00_0048ac00(p3fes::EEContext&);
void fn_sub_48AC10_0048ac10(p3fes::EEContext&);
void fn_sub_492C30_00492c30(p3fes::EEContext&);
void fn_sub_492C90_00492c90(p3fes::EEContext&);
void fn_sub_492CC0_00492cc0(p3fes::EEContext&);
void fn_sub_492CE0_00492ce0(p3fes::EEContext&);
void fn_sub_492D00_00492d00(p3fes::EEContext&);
void fn_sub_493C50_00493c50(p3fes::EEContext&);
void fn_sub_493C80_00493c80(p3fes::EEContext&);
void fn_sub_494DB0_00494db0(p3fes::EEContext&);
void fn_sub_494DE0_00494de0(p3fes::EEContext&);
void fn_sub_4B65A0_004b65a0(p3fes::EEContext&);
void fn_sub_4B6600_004b6600(p3fes::EEContext&);
void fn_sub_4B6640_004b6640(p3fes::EEContext&);
void fn_sub_4B6680_004b6680(p3fes::EEContext&);
void fn_sub_4B67B0_004b67b0(p3fes::EEContext&);
void fn_sub_4B6840_004b6840(p3fes::EEContext&);
void fn_sub_4B6980_004b6980(p3fes::EEContext&);
void fn_sub_4B69B0_004b69b0(p3fes::EEContext&);
void fn_sub_4B6A40_004b6a40(p3fes::EEContext&);
void fn_sub_4B6C80_004b6c80(p3fes::EEContext&);
void fn_sub_4B6D90_004b6d90(p3fes::EEContext&);
void fn_sub_4B6DD0_004b6dd0(p3fes::EEContext&);
void fn_sub_4B6E10_004b6e10(p3fes::EEContext&);
void fn_sub_4B6EB0_004b6eb0(p3fes::EEContext&);
void fn_sub_4B6EC0_004b6ec0(p3fes::EEContext&);
void fn_sub_4B7010_004b7010(p3fes::EEContext&);
void fn_sub_4B7020_004b7020(p3fes::EEContext&);
void fn_sub_4B7050_004b7050(p3fes::EEContext&);
void fn_sub_4B7240_004b7240(p3fes::EEContext&);
void fn_sub_4B74C0_004b74c0(p3fes::EEContext&);
void fn_sub_4B7510_004b7510(p3fes::EEContext&);
void fn_sub_4B75D0_004b75d0(p3fes::EEContext&);
void fn_sub_4B7630_004b7630(p3fes::EEContext&);
void fn_sub_4B7690_004b7690(p3fes::EEContext&);
void fn_sub_4B76B0_004b76b0(p3fes::EEContext&);
void fn_sub_4B7750_004b7750(p3fes::EEContext&);
void fn_sub_4B7760_004b7760(p3fes::EEContext&);
void fn_sub_4B7770_004b7770(p3fes::EEContext&);
void fn_sub_4B77F0_004b77f0(p3fes::EEContext&);
void fn_sub_4B79D0_004b79d0(p3fes::EEContext&);
void fn_sub_4B7C60_004b7c60(p3fes::EEContext&);
void fn_sub_4B7D00_004b7d00(p3fes::EEContext&);
void fn_sub_4B7E10_004b7e10(p3fes::EEContext&);
void fn_sub_4B7F30_004b7f30(p3fes::EEContext&);
void fn_sub_4B7F80_004b7f80(p3fes::EEContext&);
void fn_sub_4B7FD0_004b7fd0(p3fes::EEContext&);
void fn_sub_4B8080_004b8080(p3fes::EEContext&);
void fn_sub_4B8120_004b8120(p3fes::EEContext&);
void fn_sub_4B81F0_004b81f0(p3fes::EEContext&);
void fn_sub_4B8290_004b8290(p3fes::EEContext&);
void fn_sub_4B82D0_004b82d0(p3fes::EEContext&);
void fn_sub_4B83D0_004b83d0(p3fes::EEContext&);
void fn_sub_4B8500_004b8500(p3fes::EEContext&);
void fn_sub_4B8630_004b8630(p3fes::EEContext&);
void fn_sub_4B8740_004b8740(p3fes::EEContext&);
void fn_sub_4B87D0_004b87d0(p3fes::EEContext&);
void fn_sub_4B8830_004b8830(p3fes::EEContext&);
void fn_sub_4B88E0_004b88e0(p3fes::EEContext&);
void fn_sub_4B8920_004b8920(p3fes::EEContext&);
void fn_sub_4B89D0_004b89d0(p3fes::EEContext&);
void fn_sub_4B8B10_004b8b10(p3fes::EEContext&);
void fn_sub_4B8C30_004b8c30(p3fes::EEContext&);
void fn_sub_4B8D50_004b8d50(p3fes::EEContext&);
void fn_sub_4B8E70_004b8e70(p3fes::EEContext&);
void fn_sub_4B9030_004b9030(p3fes::EEContext&);
void fn_sub_4B90A0_004b90a0(p3fes::EEContext&);
void fn_sub_4B9140_004b9140(p3fes::EEContext&);
void fn_sub_4B91B0_004b91b0(p3fes::EEContext&);
void fn_sub_4B91C0_004b91c0(p3fes::EEContext&);
void fn_sub_4B92D0_004b92d0(p3fes::EEContext&);
void fn_sub_4B9350_004b9350(p3fes::EEContext&);
void fn_sub_4B9370_004b9370(p3fes::EEContext&);
void fn_sub_4B96E0_004b96e0(p3fes::EEContext&);
void fn_sub_4B96F0_004b96f0(p3fes::EEContext&);
void fn_sub_4B97B0_004b97b0(p3fes::EEContext&);
void fn_sub_4B97D0_004b97d0(p3fes::EEContext&);
void fn_sub_4B97F0_004b97f0(p3fes::EEContext&);
void fn_sub_4BDCB0_004bdcb0(p3fes::EEContext&);
void fn_sub_4BE310_004be310(p3fes::EEContext&);
void fn_sub_4C15A0_004c15a0(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C1750_004c1750(p3fes::EEContext&);
void fn_sub_4C17F0_004c17f0(p3fes::EEContext&);
void fn_sub_4C1820_004c1820(p3fes::EEContext&);
void fn_sub_4C1850_004c1850(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C1D50_004c1d50(p3fes::EEContext&);
void fn_sub_4C1E70_004c1e70(p3fes::EEContext&);
void fn_sub_4C2080_004c2080(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_4C21B0_004c21b0(p3fes::EEContext&);
void fn_sub_4C21E0_004c21e0(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);
void fn_sub_4C33D0_004c33d0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C3760_004c3760(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C53F0_004c53f0(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
void fn_sub_4C7D00_004c7d00(p3fes::EEContext&);
void fn_sub_4CA520_004ca520(p3fes::EEContext&);
void fn_sub_4CA550_004ca550(p3fes::EEContext&);
void fn_sub_4CAE30_004cae30(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB6E0_004cb6e0(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4CB9F0_004cb9f0(p3fes::EEContext&);
void fn_sub_4CF4C0_004cf4c0(p3fes::EEContext&);
void fn_sub_4F7300_004f7300(p3fes::EEContext&);
void fn_sub_4F7470_004f7470(p3fes::EEContext&);
void fn_sub_4F7560_004f7560(p3fes::EEContext&);
void fn_sub_4F7F40_004f7f40(p3fes::EEContext&);
void fn_sub_4F8560_004f8560(p3fes::EEContext&);
void fn_sub_4F8690_004f8690(p3fes::EEContext&);
void fn_sub_4F8790_004f8790(p3fes::EEContext&);
void fn_sub_4F87B0_004f87b0(p3fes::EEContext&);
void fn_sub_4F8CB0_004f8cb0(p3fes::EEContext&);
void fn_sub_4F8E10_004f8e10(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x004B65A0 sub_4B65A0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B65A0 [rtAnimOpen]: RtAnim's engine-open callback: creates a free list of 24-byte records (the RW globals'
// free-list parameters 0x7CDCF4 / 0x7CDCF8, static block 0x95FEE0) and keeps it at 0x7CE8A4; returns the engine
// instance, or 0 when the free list could not be made.
void sub_4B65A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b65a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a2 = 4;
    lw(a1, gp, -20476);  // 0x7CDCF4
    s0 = a0;
    lw(a3, gp, -20472);  // 0x7CDCF8
    a0 = 24;
    t0 = addiu(t0, -288);  // &0x95FEE0
    t1 = v0 | 0x1B;
    jal(ctx, 0x4B65CCu, gen::fn_sub_4C3B60_004c3b60);  // [RwFreeListCreate]
    sw(v0, gp, -17484);  // 0x7CE8A4 RtAnim: the 24-byte free list
    if (v0 == 0) {
        // 0x004b65e4
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    }
    // 0x004b65dc
    charge(ctx, 2);
    v0 = s0;
    // 0x004b65ec
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B6600 sub_4B6600 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B6600 [rtAnimClose]: RtAnim's engine-close callback: forgets every registered interpolation scheme (count
// 0x7CE8A0 = 0) and destroys the 0x7CE8A4 free list.
void sub_4B6600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6600
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -17484);  // 0x7CE8A4 RtAnim: the 24-byte free list
    sw(zero, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
    if (a0 != 0) {
        // 0x004b661c
        charge(ctx, 3);
        jal(ctx, 0x4B661Cu, gen::fn_sub_4C3C30_004c3c30);  // [RwFreeListDestroy]
        sw(zero, gp, -17484);  // 0x7CE8A4 RtAnim: the 24-byte free list
    }
    // 0x004b6628 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B6640 sub_4B6640 -- 52 bytes; frame 0x10: ra sp+0x0
// sub_4B6640 [RtAnimInitialize]: Attaches the RtAnim toolkit: RwEngineRegisterPlugin(0, id 0x1B7, open, close).
// Returns 1 when the registration gave a positive offset.
void sub_4B6640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6640
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x4B0000;
    a3 = 0x4B0000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 439;
    a2 = addiu(a2, 26016);  // &sub_4B65A0
    a3 = addiu(a3, 26112);  // &sub_4B6600
    jal(ctx, 0x4B665Cu, gen::fn_sub_4CA520_004ca520);  // [RwEngineRegisterPlugin]
    ld(ra, sp, 0x0);
    v0 = slt(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x004B6680 sub_4B6680 -- 296 bytes; frame 0x20: ra sp+0x0
// sub_4B6680 [RtAnimRegisterInterpolationScheme]: Copies a 48-byte RtAnimInterpolatorInfo (type id, frame sizes, the
// eight callbacks, custom data size) into the scheme table 0x95FBE0 (at most 16; count 0x7CE8A0). A full table (error
// 1) or an id already registered (error 0) sets an RtAnim error (plugin 0x1B7) and returns 0; else 1.
void sub_4B6680(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004b6680
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(a1, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
    at = slti(a1, 16);
    if (at == 0) {
        // 0x004b677c
        charge(ctx, 8);
        v0 = 439;
        a0 = 1;
        link(ctx, 0x4B6784u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x10);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
        sw(v0, sp, 0x14);
        a0 = addiu(sp, 0x10);
        jal(ctx, 0x4B6790u, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
        v0 = 0;
    } else {
        // 0x004b6698
        charge(ctx, 3);
        at = slt(0, a1);
        a3 = 0;
        if (at != 0) {
            // 0x004b66a4
            charge(ctx, 3);
            lw(v1, a0, 0);
            a2 = 0x960000;
            a2 = addiu(a2, -1056);  // &0x95FBE0
            for (;;) {
                // 0x004b66b0
                charge(ctx, 3);
                lw(v0, a2, 0);
                if (v1 == v0) {
                    goto L_004b66bc_4;
                }
                // 0x004b66e0
                charge(ctx, 4);
                a3 = addiu(a3, 1);
                v0 = slt(a3, a1);
                a2 = addiu(a2, 48);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b66f0
        charge(ctx, 35);
        v0 = sll(a1, 1);
        lwc1(f3, a0, 0);
        v1 = addu(v0, a1);
        lwc1(f2, a0, 4);
        v0 = 0x960000;
        lwc1(f1, a0, 8);
        a1 = sll(v1, 4);
        v0 = addiu(v0, -1056);  // &0x95FBE0
        lw(v1, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
        a1 = addu(v0, a1);
        lwc1(f0, a0, 12);
        v0 = 1;
        v1 = addiu(v1, 1);
        swc1(f3, a1, 0);
        swc1(f2, a1, 4);
        swc1(f1, a1, 8);
        swc1(f0, a1, 12);
        lwc1(f3, a0, 16);
        lwc1(f2, a0, 20);
        lwc1(f1, a0, 24);
        lwc1(f0, a0, 28);
        swc1(f3, a1, 16);
        swc1(f2, a1, 20);
        swc1(f1, a1, 24);
        swc1(f0, a1, 28);
        lwc1(f3, a0, 32);
        lwc1(f2, a0, 36);
        lwc1(f1, a0, 40);
        lwc1(f0, a0, 44);
        swc1(f3, a1, 32);
        sw(v1, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
        swc1(f2, a1, 36);
        swc1(f1, a1, 40);
        swc1(f0, a1, 44);
    }
    // 0x004b679c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_004b66bc_4:
    charge(ctx, 9);
    v0 = 439;
    a0 = 0;
    link(ctx, 0x4B66C4u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x18);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
    sw(v0, sp, 0x1C);
    a0 = addiu(sp, 0x18);
    jal(ctx, 0x4B66D0u, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
    v0 = 0;
    // 0x004b679c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B67B0 sub_4B67B0 -- 132 bytes; frame 0x20: ra sp+0x0
// sub_4B67B0 [RtAnimGetInterpolatorInfo]: The scheme table entry of type id $a0, or 0 with RtAnim error 2 when no
// scheme has that id.
void sub_4B67B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b67b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(v1, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
    at = slt(0, v1);
    a2 = 0;
    if (at != 0) {
        // 0x004b67c8
        charge(ctx, 2);
        a1 = 0x960000;
        a1 = addiu(a1, -1056);  // &0x95FBE0
        for (;;) {
            // 0x004b67d0
            charge(ctx, 3);
            lw(v0, a1, 0);
            if (a0 == v0) {
                goto L_004b67dc_3;
            }
            // 0x004b67f8
            charge(ctx, 4);
            a2 = addiu(a2, 1);
            v0 = slt(a2, v1);
            a1 = addiu(a1, 48);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b6808
    charge(ctx, 8);
    v0 = 439;
    sw(v0, sp, 0x18);
    a0 = 2;
    jal(ctx, 0x4B6810u, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
    sw(v0, sp, 0x1C);
    a0 = addiu(sp, 0x18);
    jal(ctx, 0x4B681Cu, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
    v0 = 0;
    // 0x004b6828 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_004b67dc_3:
    charge(ctx, 7);
    v1 = sll(a2, 1);
    v0 = 0x960000;
    v1 = addu(v1, a2);
    v0 = addiu(v0, -1056);  // &0x95FBE0
    v1 = sll(v1, 4);
    v0 = addu(v0, v1);
    // 0x004b6828 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B6840 sub_4B6840 -- 308 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4B6840 [RtAnimAnimationCreate]: Creates an animation of scheme $a0 with $a1 keyframes, flags $a2 and duration
// $f12: one RwMalloc(24 + frames x the scheme's keyframe size + custom data size, 0x3001B); the keyframes follow the
// 24-byte head and the custom data follow the keyframes (0 when the scheme has none). An unknown scheme sets RtAnim
// error 2 and returns 0.
void sub_4B6840(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x004b6840
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    s2 = a1;
    sq(s0, sp, 0x10);
    s1 = a2;
    swc1(f20, sp, 0x0);
    a2 = 0;
    lw(v1, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
    at = slt(0, v1);
    mov_s(f20, f12);
    if (at != 0) {
        // 0x004b6874
        charge(ctx, 2);
        a1 = 0x960000;
        a1 = addiu(a1, -1056);  // &0x95FBE0
        for (;;) {
            // 0x004b687c
            charge(ctx, 3);
            lw(v0, a1, 0);
            if (a0 == v0) {
                goto L_004b6888_3;
            }
            // 0x004b68a4
            charge(ctx, 4);
            a2 = addiu(a2, 1);
            v0 = slt(a2, v1);
            a1 = addiu(a1, 48);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b68b4
        charge(ctx, 1);
    }
    // 0x004b68b8
    charge(ctx, 8);
    v0 = 439;
    sw(v0, sp, 0x58);
    a0 = 2;
    jal(ctx, 0x4B68C0u, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
    sw(v0, sp, 0x5C);
    a0 = addiu(sp, 0x58);
    jal(ctx, 0x4B68CCu, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
    s0 = 0;
L_004b68d8:
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x004b6948
        charge(ctx, 2);
        v0 = 0;
        // 0x004b6958
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    } else {
        // 0x004b68e0
        charge(ctx, 19);
        lw(v0, s0, 8);
        mult(a2, s2, v0);
        v1 = 0x30000;
        a1 = v1 | 0x1B;
        lw(a0, s0, 44);
        v0 = 0x960000;
        v1 = addiu(a2, 24);
        lw(v0, v0, 376);  // 0x960178 RwMalloc slot
        a0 = addu(a0, v1);
        jalr(ctx, 0x4B6900u, v0.u());
        sw(s2, v0, 4);
        v1 = addiu(v0, 24);
        swc1(f20, v0, 12);
        sw(s1, v0, 8);
        sw(s0, v0, 0);
        sw(v1, v0, 16);
        lw(v1, s0, 44);
        if (i64(v1) <= 0) {
            // 0x004b6950
            charge(ctx, 2);
            sw(zero, v0, 20);
            backedge(ctx);
        } else {
            // 0x004b692c
            charge(ctx, 5);
            lw(v1, s0, 8);
            mult(a0, s2, v1);
            lw(v1, v0, 16);
            v1 = addu(v1, a0);
            sw(v1, v0, 20);
        }
        // 0x004b6940
        charge(ctx, 2);
        ld(ra, sp, 0x40);
    }
    // 0x004b695c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lwc1(f20, sp, 0x0);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
    return;
L_004b6888_3:
    charge(ctx, 7);
    v1 = sll(a2, 1);
    v0 = 0x960000;
    v1 = addu(v1, a2);
    v0 = addiu(v0, -1056);  // &0x95FBE0
    v1 = sll(v1, 4);
    s0 = addu(v0, v1);
    goto L_004b68d8;
}

// 0x004B69B0 sub_4B69B0 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B69B0 [RtAnimAnimationRead]: Loads an animation from a file name: opens a file stream, finds the animation
// chunk (0x1B), reads it with RtAnimAnimationStreamRead and closes the stream. 0 on any failure.
void sub_4B69B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b69b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = a0;
    sd(ra, sp, 0x20);
    a0 = 2;
    sq(s1, sp, 0x10);
    a1 = 1;
    link(ctx, 0x4B69C8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C58A0_004c58a0);  // [RwStreamOpen]
    s0 = v0;
    if (s0 == 0) {
        // 0x004b6a00
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b69dc
        charge(ctx, 7);
        a0 = s0;
        a1 = 27;
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x4B69E8u, gen::fn_sub_4C1600_004c1600);  // [RwStreamFindChunk]
        if (v0 != 0) {
            // 0x004b6a08
            charge(ctx, 7);
            a0 = s0;
            jal(ctx, 0x4B6A08u, gen::fn_sub_4B6A40_004b6a40);  // [RtAnimAnimationStreamRead]
            s1 = v0;
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x4B6A18u, gen::fn_sub_4C5780_004c5780);  // [RwStreamClose]
            v0 = s1;
        } else {
            // 0x004b69f8
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004b6a24 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004B6A40 sub_4B6A40 -- 576 bytes; frame 0xA0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4B6A40 [RtAnimAnimationStreamRead]: Reads an animation chunk body: version 0x100, the scheme id, the keyframe
// count, the flags and the duration; creates the animation (as RtAnimAnimationCreate, inlined) and lets the scheme's
// stream-read callback (+32) fill the keyframes. Returns the animation, 0 on a bad version, an unknown scheme or a
// short read.
void sub_4B6A40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f20{ctx, 20};
    // 0x004b6a40
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    a2 = 4;
    sd(ra, sp, 0x70);
    a1 = addiu(sp, 0x9C);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s0 = a0;
    link(ctx, 0x4B6A6Cu);  // $ra first: the delay slot below depends on it
    swc1(f20, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
    if (v0 == 0) {
        // 0x004b6a94
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b6a7c
        charge(ctx, 4);
        lw(v1, sp, 0x9C);
        v0 = 256;
        if (v1 == v0) {
            // 0x004b6a9c
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(sp, 0x98);
            a2 = 4;
            jal(ctx, 0x4B6AA4u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 == 0) {
                // 0x004b6b50
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b6ab4
                charge(ctx, 5);
                lw(v1, gp, -17488);  // 0x7CE8A0 RtAnim: registered scheme count
                lw(a0, sp, 0x98);
                at = slt(0, v1);
                a2 = 0;
                if (at != 0) {
                    // 0x004b6ac8
                    charge(ctx, 2);
                    a1 = 0x960000;
                    a1 = addiu(a1, -1056);  // &0x95FBE0
                    for (;;) {
                        // 0x004b6ad0
                        charge(ctx, 3);
                        lw(v0, a1, 0);
                        if (a0 == v0) {
                            goto L_004b6adc_8;
                        }
                        // 0x004b6af8
                        charge(ctx, 4);
                        a2 = addiu(a2, 1);
                        v0 = slt(a2, v1);
                        a1 = addiu(a1, 48);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004b6b08
                charge(ctx, 8);
                v0 = 439;
                sw(v0, sp, 0x80);
                a0 = 2;
                jal(ctx, 0x4B6B10u, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
                sw(v0, sp, 0x84);
                a0 = addiu(sp, 0x80);
                jal(ctx, 0x4B6B1Cu, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
                s5 = 0;
            L_004b6b28:
                charge(ctx, 2);
                if (s5 == 0) {
                    // 0x004b6b58
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004b6b30
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = addiu(sp, 0x94);
                    a2 = 4;
                    jal(ctx, 0x4B6B38u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                    if (v0 != 0) {
                        // 0x004b6b60
                        charge(ctx, 6);
                        a0 = s0;
                        a1 = addiu(sp, 0x90);
                        a2 = 4;
                        jal(ctx, 0x4B6B68u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                        if (v0 != 0) {
                            // 0x004b6b80
                            charge(ctx, 6);
                            a0 = s0;
                            a1 = addiu(sp, 0x8C);
                            a2 = 4;
                            jal(ctx, 0x4B6B88u, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
                            if (v0 != 0) {
                                // 0x004b6ba0
                                charge(ctx, 8);
                                lwc1(f20, sp, 0x8C);
                                lw(s3, sp, 0x90);
                                lw(s2, sp, 0x94);
                                link(ctx, 0x4B6BACu);  // $ra first: the delay slot below depends on it
                                lw(a0, sp, 0x98);
                                call(ctx, gen::fn_sub_4B67B0_004b67b0);  // [RtAnimGetInterpolatorInfo]
                                s1 = v0;
                                if (s1 == 0) {
                                    // 0x004b6c44
                                    charge(ctx, 2);
                                    s4 = 0;
                                    backedge(ctx);
                                } else {
                                    // 0x004b6bc0
                                    charge(ctx, 20);
                                    lw(v0, s1, 8);
                                    mult(a2, s2, v0);
                                    v1 = 0x30000;
                                    a1 = v1 | 0x1B;
                                    lw(a0, s1, 44);
                                    v0 = 0x960000;
                                    v1 = addiu(a2, 24);
                                    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
                                    a0 = addu(a0, v1);
                                    jalr(ctx, 0x4B6BE0u, v0.u());
                                    sw(s2, v0, 4);
                                    s4 = v0;
                                    swc1(f20, v0, 12);
                                    v1 = addiu(s4, 24);
                                    sw(s3, v0, 8);
                                    sw(s1, v0, 0);
                                    sw(v1, v0, 16);
                                    lw(v0, s1, 44);
                                    if (i64(v0) <= 0) {
                                        // 0x004b6c4c
                                        charge(ctx, 2);
                                        sw(zero, s4, 20);
                                        backedge(ctx);
                                    } else {
                                        // 0x004b6c10
                                        charge(ctx, 5);
                                        lw(v0, s1, 8);
                                        mult(v1, s2, v0);
                                        lw(v0, s4, 16);
                                        v0 = addu(v0, v1);
                                        sw(v0, s4, 20);
                                    }
                                }
                                // 0x004b6c24
                                charge(ctx, 2);
                                if (s4 == 0) {
                                    // 0x004b6c54
                                    charge(ctx, 1);
                                    v0 = 0;
                                } else {
                                    // 0x004b6c2c
                                    charge(ctx, 6);
                                    lw(v0, s5, 32);
                                    a0 = s0;
                                    a1 = s4;
                                    jalr(ctx, 0x4B6C34u, v0.u());
                                    v0 = s4;
                                }
                            } else {
                                // 0x004b6b98
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        } else {
                            // 0x004b6b78
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x004b6b48
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
            }
        } else {
            // 0x004b6a8c
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004b6c58 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xA0);
    return;
L_004b6adc_8:
    charge(ctx, 7);
    v1 = sll(a2, 1);
    v0 = 0x960000;
    v1 = addu(v1, a2);
    v0 = addiu(v0, -1056);  // &0x95FBE0
    v1 = sll(v1, 4);
    s5 = addu(v0, v1);
    goto L_004b6b28;
}

// 0x004B6C80 sub_4B6C80 -- 268 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B6C80 [RtAnimAnimationStreamWrite]: Writes an animation chunk: the chunk header (0x1B, size from
// RtAnimAnimationStreamGetSize, version 0x37002 / build 0x37), version 0x100, the scheme id, the keyframe count, the
// flags and the duration (a real), then the scheme's stream-write callback (+36). Returns 1, 0 on a write failure.
void sub_4B6C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6c80
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 256;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    link(ctx, 0x4B6C9Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x3C);
    call(ctx, gen::fn_sub_4B6D90_004b6d90);  // [RtAnimAnimationStreamGetSize]
    a2 = v0;
    a0 = s0;
    v0 = 0x30000;
    a1 = 27;
    a3 = v0 | 0x7002;
    t0 = 55;
    jal(ctx, 0x4B6CB8u, gen::fn_sub_4C15A0_004c15a0);  // [RwStreamWriteVersionedChunkHeader]
    a0 = s0;
    a1 = addiu(sp, 0x3C);
    a2 = 4;
    jal(ctx, 0x4B6CC8u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
    if (v0 != 0) {
        // 0x004b6ce0
        charge(ctx, 6);
        lw(a1, s1, anim::kAnmInfo);
        a0 = s0;
        a2 = 4;
        jal(ctx, 0x4B6CE8u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 != 0) {
            // 0x004b6d00
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(s1, 4);
            a2 = 4;
            jal(ctx, 0x4B6D08u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 != 0) {
                // 0x004b6d20
                charge(ctx, 6);
                a0 = s0;
                a1 = addiu(s1, 8);
                a2 = 4;
                jal(ctx, 0x4B6D28u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                if (v0 != 0) {
                    // 0x004b6d40
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = addiu(s1, 12);
                    a2 = 4;
                    jal(ctx, 0x4B6D48u, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
                    if (v0 != 0) {
                        // 0x004b6d60
                        charge(ctx, 6);
                        lw(v0, s1, anim::kAnmInfo);
                        a1 = s0;
                        lw(v0, v0, anim::kInfoStreamWriteCB);
                        a0 = s1;
                        jalr(ctx, 0x4B6D6Cu, v0.u());
                        v0 = 1;
                    } else {
                        // 0x004b6d58
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x004b6d38
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x004b6d18
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x004b6cf8
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004b6cd8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b6d78 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B6D90 sub_4B6D90 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B6D90 [RtAnimAnimationStreamGetSize]: The chunk body size of an animation: 20 + the scheme's stream-size
// callback (+40).
void sub_4B6D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6d90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addiu(v0, 20);
    lw(v0, a0, anim::kAnmInfo);
    lw(v0, v0, anim::kInfoStreamSizeCB);
    jalr(ctx, 0x4B6DACu, v0.u());
    v0 = addu(s0, v0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B6DD0 sub_4B6DD0 -- 64 bytes; leaf frame (no stack)
// sub_4B6DD0 [RtAnimAnimationGetNumNodes]: The node count of an animation: the keyframes before the first one whose
// previous-frame link points back at keyframe 0 (the scheme's keyframe size is the stride). Every node starts with
// two keyframes that link to nothing, so this counts the first pass.
void sub_4B6DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004b6dd0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, anim::kAnmInfo);
    lw(a2, a0, anim::kAnmFrames);
    lw(a1, v1, anim::kInfoAnimFrameSize);
    lw(v1, a2, anim::kKfPrev);
    v0 = 0;
    if (v1 != a2) {
        // 0x004b6de8
        charge(ctx, 1);
        v1 = a2;
        for (;;) {
            // 0x004b6dec
            charge(ctx, 7);
            a2 = addu(a2, a1);
            v0 = addiu(v0, 1);
            lw(a0, a2, 0);
            if (a0 == v1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b6e08 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004B6E10 sub_4B6E10 -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B6E10 [RtAnimInterpolatorCreate]: Creates an interpolator for $a0 nodes with interpolated frames of up to $a1
// bytes: RwMalloc(76 + nodes x size, 0x3001B), every field zero except the callback time (-1.0), the frame sizes
// ($a1; the animation's keyframe size -1 until an animation is set) and the parent (itself).
void sub_4B6E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6e10
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mult(v1, s1, s0);
    v0 = 0x30000;
    a1 = v0 | 0x1B;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
    a0 = addiu(v1, 76);
    jalr(ctx, 0x4B6E3Cu, v0.u());
    sw(s1, v0, 44);
    a0 = lui(0xBF80);
    sw(zero, v0, 0);
    v1 = si(-1);
    sw(zero, v0, 8);
    sw(zero, v0, 4);
    sw(zero, v0, 12);
    sw(a0, v0, 20);
    sw(zero, v0, 16);
    sw(zero, v0, 24);
    sw(zero, v0, 28);
    sw(s0, v0, 36);
    sw(v1, v0, 40);
    sw(s0, v0, 32);
    sw(zero, v0, 48);
    sw(zero, v0, 52);
    sw(v0, v0, 56);
    sw(zero, v0, 60);
    sw(zero, v0, 68);
    sw(zero, v0, 64);
    sw(zero, v0, 72);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004B6EC0 sub_4B6EC0 -- 324 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B6EC0 [RtAnimInterpolatorSetCurrentAnim]: Starts animation $a1 on interpolator $a0 at time 0: copies the
// scheme's frame sizes and its apply / blend / interpolate / add callbacks into the interpolator, interpolates every
// node between its first two keyframes (keyframe i and keyframe i + nodes) and points each interpolated frame at
// them; the next keyframe to read is keyframe 2 x nodes. Returns 1.
void sub_4B6EC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004b6ec0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    sw(s1, a0, anim::kItpAnim);
    sw(zero, a0, anim::kItpTime);
    lw(v1, a1, anim::kAnmInfo);
    lw(v0, v1, anim::kInfoInterpFrameSize);
    sw(v0, a0, anim::kItpFrameSize);
    lw(v0, v1, anim::kInfoAnimFrameSize);
    sw(v0, a0, anim::kItpAnimFrameSize);
    lw(v0, v1, anim::kInfoApplyCB);
    sw(v0, a0, anim::kItpApplyCB);
    lw(v0, v1, anim::kInfoBlendCB);
    sw(v0, a0, anim::kItpBlendCB);
    lw(v0, v1, anim::kInfoInterpolateCB);
    sw(v0, a0, anim::kItpInterpolateCB);
    lw(v0, v1, anim::kInfoAddCB);
    sw(v0, a0, anim::kItpAddCB);
    lw(a3, a0, anim::kItpNumNodes);
    v0 = slt(0, a3);
    s0 = 0;
    if (v0 != 0) {
        for (;;) {
            // 0x004b6f7c
            charge(ctx, 20);
            lw(v0, s2, anim::kItpFrameSize);
            lw(v1, s2, anim::kItpAnimFrameSize);
            lw(a2, s1, anim::kAnmFrames);
            mult(v0, s0, v0);
            a0 = addu(v0, s2);
            mult1(v0, s0, v1);
            a1 = addu(a2, v0);
            v0 = addu(s0, a3);
            mult(v1, v1, v0);
            lw(a3, s1, anim::kAnmCustomData);
            mtc1(zero, f12);
            a0 = addiu(a0, 76);
            lw(v0, s2, anim::kItpInterpolateCB);
            a2 = addu(a2, v1);
            jalr(ctx, 0x4B6FB0u, v0.u());
            lw(a3, s2, anim::kItpNumNodes);
            s0 = addiu(s0, 1);
            v0 = slt(s0, a3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b6fcc
        charge(ctx, 2);
        lw(a0, s2, anim::kItpAnimFrameSize);
        backedge(ctx);
    } else {
        // 0x004b6f28
        charge(ctx, 1);
        lw(a0, s2, anim::kItpAnimFrameSize);
    }
    // 0x004b6f2c
    charge(ctx, 7);
    a1 = addiu(s2, 76);
    lw(t0, s1, anim::kAnmFrames);
    mult(v0, a3, a0);
    at = slt(0, a3);
    v1 = 0;
    a2 = addu(t0, v0);
    if (at == 0) {
        // 0x004b6fd4
        charge(ctx, 1);
        mult(a0, a3, a0);
    } else {
        for (;;) {
            // 0x004b6f48
            charge(ctx, 11);
            sw(t0, a1, 0);
            v1 = addiu(v1, 1);
            sw(a2, a1, 4);
            lw(v0, s2, anim::kItpFrameSize);
            lw(a3, s2, anim::kItpNumNodes);
            lw(a0, s2, anim::kItpAnimFrameSize);
            a1 = addu(a1, v0);
            v0 = slt(v1, a3);
            t0 = addu(t0, a0);
            a2 = addu(a2, a0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b6f74
        charge(ctx, 2);
        mult(a0, a3, a0);
    }
    // 0x004b6fd8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v1, s1, anim::kAnmFrames);
    v0 = 1;
    a0 = sll(a0, 1);
    v1 = addu(v1, a0);
    sw(v1, s2, anim::kItpNextFrame);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B7010 sub_4B7010 -- 12 bytes; leaf frame (no stack)
// sub_4B7010 [RtAnimInterpolatorSetAnimLoopCallBack]: Sets the loop callback ($a1) and its data ($a2): called when
// the time wraps past the duration.
void sub_4B7010(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004b7010
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, anim::kItpLoopCallBack);
    sw(a2, a0, anim::kItpLoopCallBackData);
}

// 0x004B7020 sub_4B7020 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_4B7020 [RtAnimInterpolatorCopy]: Copies the interpolated frames of $a1 into $a0 (memcpy of nodes x frame size
// bytes from +76). Returns 1.
void sub_4B7020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7020
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, anim::kItpFrameSize);
    lw(v0, a0, anim::kItpNumNodes);
    mult(a2, v1, v0);
    a0 = addiu(a0, 76);
    a1 = addiu(a1, 76);
    jal(ctx, 0x4B7038u, gen::fn_memcpy_00521250);  // [memcpy]
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x004B7050 sub_4B7050 -- 492 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4B7050 [RtAnimInterpolatorSubAnimTime]: Moves interpolator $a0 back by $f12 seconds. When the time goes below 0
// it wraps (adding the duration until positive), restarts the animation and runs the time forward again
// (RtAnimInterpolatorAddAnimTime) with the loop callback due; otherwise each node's keyframe pair is walked back
// along the previous-frame links until the earlier keyframe is at or before the time, the node is re-interpolated,
// and the next-frame pointer is cleared (so the next forward step restarts the keyframe search). The animation
// callback runs when its time was crossed (a callback returning 0 is cleared), then the loop callback. Returns 1.
void sub_4B7050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x004b7050
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0;
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a0;
    sq(s2, sp, 0x30);
    s3 = 0;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lwc1(f1, a0, anim::kItpCallBackTime);
    lwc1(f0, a0, anim::kItpTime);
    c_le_s(f0, f1);
    s2 = 0;
    if (!cond(ctx)) {
        // 0x004b7090
        charge(ctx, 4);
        sub_s(f0, f0, f12);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x004b70a0
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x004b70a4
    charge(ctx, 10);
    lwc1(f0, s4, anim::kItpTime);
    mtc1(zero, f1);
    sub_s(f0, f0, f12);
    swc1(f0, s4, anim::kItpTime);
    lwc1(f20, s4, anim::kItpTime);
    lw(a1, s4, anim::kItpAnim);
    c_lt_s(f20, f1);
    s3 = s3 | v0;
    if (cond(ctx)) {
        // 0x004b7190
        charge(ctx, 3);
        c_lt_s(f20, f1);
        lwc1(f2, a1, 12);
        if (cond(ctx)) {
            for (;;) {
                // 0x004b719c
                charge(ctx, 7);
                lwc1(f0, s4, anim::kItpTime);
                add_s(f20, f0, f2);
                c_lt_s(f20, f1);
                swc1(f20, s4, anim::kItpTime);
                if (!cond(ctx)) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b71b8
        charge(ctx, 10);
        a0 = s4;
        jal(ctx, 0x4B71B8u, gen::fn_sub_4B6EC0_004b6ec0);  // [RtAnimInterpolatorSetCurrentAnim]
        mov_s(f12, f20);
        a0 = s4;
        jal(ctx, 0x4B71C4u, gen::fn_sub_4B7240_004b7240);  // [RtAnimInterpolatorAddAnimTime]
        lwc1(f1, s4, anim::kItpTime);
        lwc1(f0, s4, anim::kItpCallBackTime);
        c_lt_s(f1, f0);
        v0 = 1;
        if (!cond(ctx)) {
            // 0x004b71e0
            charge(ctx, 1);
            v0 = 0;
        }
        // 0x004b71e4
        charge(ctx, 3);
        s3 = s3 | v0;
        s2 = 1;
        backedge(ctx);
    } else {
        // 0x004b70cc
        charge(ctx, 3);
        lw(s1, s4, anim::kItpNumNodes);
        s0 = addiu(s4, 76);
        for (;;) {
            // 0x004b7120
            charge(ctx, 3);
            v0 = s1;
            s1 = addiu(s1, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x004b70d8
            charge(ctx, 6);
            lw(a1, s0, 0);
            lwc1(f12, s4, anim::kItpTime);
            lwc1(f0, a1, 4);
            c_lt_s(f12, f0);
            if (!cond(ctx)) {
                // 0x004b71f0
                charge(ctx, 1);
                lw(v1, s4, anim::kItpAnim);
            } else {
                for (;;) {
                    // 0x004b70f0
                    charge(ctx, 10);
                    sw(a1, s0, 4);
                    lw(v0, s0, 0);
                    lw(v0, v0, 0);
                    sw(v0, s0, 0);
                    lw(a1, s0, 0);
                    lwc1(f12, s4, anim::kItpTime);
                    lwc1(f0, a1, 4);
                    c_lt_s(f12, f0);
                    if (!cond(ctx)) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b7118
                charge(ctx, 2);
                lw(v1, s4, anim::kItpAnim);
            }
            // 0x004b71f4
            charge(ctx, 8);
            lw(a2, s0, 4);
            lw(v0, s4, anim::kItpInterpolateCB);
            lw(a3, v1, 20);
            a0 = s0;
            jalr(ctx, 0x4B7200u, v0.u());
            lw(v0, s4, anim::kItpFrameSize);
            s0 = addu(s0, v0);
            backedge(ctx);
        }
        // 0x004b712c
        charge(ctx, 1);
        sw(zero, s4, anim::kItpNextFrame);
    }
    // 0x004b7130
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x004b7138
        charge(ctx, 3);
        lw(v0, s4, anim::kItpCallBack);
        if (v0 != 0) {
            // 0x004b7144
            charge(ctx, 5);
            lw(a1, s4, anim::kItpCallBackData);
            a0 = s4;
            jalr(ctx, 0x4B7148u, v0.u());
            if (v0 == 0) {
                // 0x004b7158
                charge(ctx, 1);
                sw(zero, s4, anim::kItpCallBack);
            }
        }
    }
    // 0x004b715c
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x004b7164
        charge(ctx, 3);
        lw(v0, s4, anim::kItpLoopCallBack);
        if (v0 != 0) {
            // 0x004b7170
            charge(ctx, 5);
            lw(a1, s4, anim::kItpLoopCallBackData);
            a0 = s4;
            jalr(ctx, 0x4B7174u, v0.u());
            if (v0 == 0) {
                // 0x004b7184
                charge(ctx, 1);
                sw(zero, s4, anim::kItpLoopCallBack);
            }
        }
    }
    // 0x004b7188
    charge(ctx, 2);
    v0 = 1;
    // 0x004b7218
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lwc1(f20, sp, 0x0);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x004B7240 sub_4B7240 -- 628 bytes; frame 0x80: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4B7240 [RtAnimInterpolatorAddAnimTime]: Advances interpolator $a0 by $f12 seconds (nothing for $f12 <= 0). Past
// the duration the time wraps (subtracting the duration) and the animation restarts (loop callback due); a cleared
// next-frame pointer also restarts it. Then every keyframe whose time is now reached is fed in order: the node whose
// later keyframe it follows takes it as its new later keyframe (the round-robin node search starts at node 0).
// Finally every node is re-interpolated with the scheme's interpolate callback, and the animation callback (when its
// time was crossed) and the loop callback run (a callback returning 0 is cleared). Returns 1.
void sub_4B7240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x004b7240
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    mtc1(zero, f0);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    c_le_s(f12, f0);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    if (!cond(ctx)) {
        // 0x004b7274
        charge(ctx, 10);
        lw(s2, s0, anim::kItpAnim);
        lwc1(f1, s0, anim::kItpCallBackTime);
        lwc1(f0, s0, anim::kItpTime);
        lw(s1, s0, anim::kItpNumNodes);
        s5 = 0;
        s4 = 0;
        lwc1(f2, s2, anim::kAnmDuration);
        c_lt_s(f0, f1);
        v0 = 0;
        if (cond(ctx)) {
            // 0x004b729c
            charge(ctx, 4);
            add_s(f0, f0, f12);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                // 0x004b72ac
                charge(ctx, 1);
                v0 = 1;
            }
        }
        // 0x004b72b0
        charge(ctx, 6);
        lwc1(f0, s0, anim::kItpTime);
        s5 = s5 | v0;
        add_s(f20, f0, f12);
        c_le_s(f20, f2);
        swc1(f20, s0, anim::kItpTime);
        if (!cond(ctx)) {
            // 0x004b72c8
            charge(ctx, 3);
            c_le_s(f20, f2);
            if (!cond(ctx)) {
                // 0x004b72d4
                charge(ctx, 3);
                c_le_s(f20, f2);
                s4 = 1;
                if (!cond(ctx)) {
                    for (;;) {
                        // 0x004b72e0
                        charge(ctx, 7);
                        lwc1(f0, s0, anim::kItpTime);
                        sub_s(f20, f0, f2);
                        swc1(f20, s0, anim::kItpTime);
                        lwc1(f0, s0, anim::kItpCallBackTime);
                        c_lt_s(f20, f0);
                        v0 = s4;
                        if (cond(ctx)) {
                            // 0x004b72fc
                            charge(ctx, 1);
                            v0 = 0;
                        }
                        // 0x004b7300
                        charge(ctx, 3);
                        c_le_s(f20, f2);
                        s5 = s5 | v0;
                        if (cond(ctx)) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b730c
                    charge(ctx, 1);
                }
            }
            // 0x004b7310
            charge(ctx, 4);
            a0 = s0;
            a1 = s2;
            jal(ctx, 0x4B7314u, gen::fn_sub_4B6EC0_004b6ec0);  // [RtAnimInterpolatorSetCurrentAnim]
            swc1(f20, s0, anim::kItpTime);
        }
        // 0x004b7320
        charge(ctx, 3);
        lw(v0, s0, anim::kItpNextFrame);
        if (v0 == 0) {
            // 0x004b7438
            charge(ctx, 6);
            lwc1(f20, s0, anim::kItpTime);
            a0 = s0;
            a1 = s2;
            jal(ctx, 0x4B7440u, gen::fn_sub_4B6EC0_004b6ec0);  // [RtAnimInterpolatorSetCurrentAnim]
            swc1(f20, s0, anim::kItpTime);
            backedge(ctx);
        }
        // 0x004b732c
        charge(ctx, 9);
        lw(v1, s2, 4);
        lw(v0, s0, anim::kItpAnimFrameSize);
        mult(v1, v1, v0);
        lw(a0, s0, anim::kItpNextFrame);
        lw(v0, s2, 16);
        a2 = addu(v0, v1);
        at = sltu(a0, a2);
        a3 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004b7350
                charge(ctx, 6);
                lw(a1, a0, 0);
                lwc1(f0, s0, anim::kItpTime);
                lwc1(f1, a1, 4);
                c_le_s(f1, f0);
                if (cond(ctx)) {
                    // 0x004b7368
                    charge(ctx, 2);
                    lw(a0, s0, anim::kItpFrameSize);
                    for (;;) {
                        // 0x004b7370
                        charge(ctx, 7);
                        mult(v0, a3, a0);
                        v0 = addu(v0, s0);
                        a3 = addiu(a3, 1);
                        v1 = addiu(v0, 76);
                        v0 = slt(a3, s1);
                        if (v0 == 0) {
                            // 0x004b738c
                            charge(ctx, 1);
                            a3 = 0;
                        }
                        // 0x004b7390
                        charge(ctx, 3);
                        lw(v0, v1, 4);
                        if (v0 == a1) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b739c
                    charge(ctx, 11);
                    sw(v0, v1, 0);
                    lw(v0, s0, anim::kItpNextFrame);
                    sw(v0, v1, 4);
                    lw(v1, s0, anim::kItpNextFrame);
                    lw(v0, s0, anim::kItpAnimFrameSize);
                    v0 = addu(v1, v0);
                    sw(v0, s0, anim::kItpNextFrame);
                    lw(a0, s0, anim::kItpNextFrame);
                    v0 = sltu(a0, a2);
                    if (v0 != 0) {
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x004b73c8
        charge(ctx, 4);
        v0 = slt(0, s1);
        s2 = addiu(s0, 76);
        s3 = 0;
        if (v0 != 0) {
            for (;;) {
                // 0x004b7450
                charge(ctx, 13);
                lw(v1, s0, anim::kItpAnim);
                lwc1(f12, s0, anim::kItpTime);
                lw(a1, s2, 0);
                lw(a2, s2, 4);
                lw(v0, s0, anim::kItpInterpolateCB);
                lw(a3, v1, anim::kAnmCustomData);
                a0 = s2;
                jalr(ctx, 0x4B7468u, v0.u());
                lw(v1, s0, anim::kItpFrameSize);
                s3 = addiu(s3, 1);
                v0 = slt(s3, s1);
                s2 = addu(s2, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b7484
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x004b73d8
        charge(ctx, 2);
        if (s5 != 0) {
            // 0x004b73e0
            charge(ctx, 3);
            lw(v0, s0, anim::kItpCallBack);
            if (v0 != 0) {
                // 0x004b73ec
                charge(ctx, 5);
                lw(a1, s0, anim::kItpCallBackData);
                a0 = s0;
                jalr(ctx, 0x4B73F0u, v0.u());
                if (v0 == 0) {
                    // 0x004b7400
                    charge(ctx, 1);
                    sw(zero, s0, anim::kItpCallBack);
                }
            }
        }
        // 0x004b7404
        charge(ctx, 2);
        if (s4 != 0) {
            // 0x004b740c
            charge(ctx, 3);
            lw(v0, s0, anim::kItpLoopCallBack);
            if (v0 != 0) {
                // 0x004b7418
                charge(ctx, 5);
                lw(a1, s0, anim::kItpLoopCallBackData);
                a0 = s0;
                jalr(ctx, 0x4B741Cu, v0.u());
                if (v0 == 0) {
                    // 0x004b742c
                    charge(ctx, 1);
                    sw(zero, s0, anim::kItpLoopCallBack);
                }
            }
        }
    }
    // 0x004b7430
    charge(ctx, 2);
    v0 = 1;
    // 0x004b748c
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x80);
}

// 0x004B74C0 sub_4B74C0 -- 72 bytes; frame 0x10: ra sp+0x0
// sub_4B74C0 [RtAnimInterpolatorSetCurrentTime]: Sets the time of interpolator $a0 to $f12: forward from the current
// time with RtAnimInterpolatorAddAnimTime, or back with RtAnimInterpolatorSubAnimTime. Returns 1.
void sub_4B74C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x004b74c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    mtc1(zero, f0);
    lwc1(f1, a0, anim::kItpTime);
    sub_s(f12, f12, f1);
    c_lt_s(f12, f0);
    if (!cond(ctx)) {
        // 0x004b74f0
        charge(ctx, 3);
        jal(ctx, 0x4B74F0u, gen::fn_sub_4B7240_004b7240);  // [RtAnimInterpolatorAddAnimTime]
        ld(ra, sp, 0x0);
    } else {
        // 0x004b74e0
        charge(ctx, 4);
        neg_s(f12, f12);
        jal(ctx, 0x4B74E0u, gen::fn_sub_4B7050_004b7050);  // [RtAnimInterpolatorSubAnimTime]
        ld(ra, sp, 0x0);
    }
    // 0x004b74fc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x004B7510 sub_4B7510 -- 188 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4B7510 [RtAnimInterpolatorBlend]: Blends two interpolators into $a0: for every node of $a0 the scheme's blend
// callback (+64) mixes the frames of $a1 and $a2 with the weight in $f12 (passed through). Returns 1.
void sub_4B7510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x004b7510
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = a0;
    sq(s1, sp, 0x20);
    s2 = a1;
    sq(s0, sp, 0x10);
    s1 = a2;
    swc1(f20, sp, 0x0);
    s0 = 0;
    lw(v0, a0, anim::kItpNumNodes);
    v0 = slt(0, v0);
    mov_s(f20, f12);
    if (v0 != 0) {
        for (;;) {
            // 0x004b7554
            charge(ctx, 20);
            lw(v0, s3, anim::kItpFrameSize);
            mult(v1, s0, v0);
            lw(v0, s2, anim::kItpFrameSize);
            a0 = addu(v1, s3);
            mult1(v1, s0, v0);
            lw(v0, s1, anim::kItpFrameSize);
            a1 = addu(v1, s2);
            mult(v1, s0, v0);
            a0 = addiu(a0, 76);
            a1 = addiu(a1, 76);
            mov_s(f12, f20);
            lw(v0, s3, anim::kItpBlendCB);
            v1 = addu(v1, s1);
            a2 = addiu(v1, 76);
            jalr(ctx, 0x4B7588u, v0.u());
            lw(v0, s3, anim::kItpNumNodes);
            s0 = addiu(s0, 1);
            v0 = slt(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b75a4
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004b754c
    charge(ctx, 2);
    v0 = 1;
    // 0x004b75ac
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lwc1(f20, sp, 0x0);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x004B75D0 sub_4B75D0 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B75D0 [RtAnimInterpolatorCreateSubInterpolator]: Creates a sub-interpolator of parent $a0 starting at node $a1
// with $a2 nodes and frame size $a3 (-1: the parent's): a new interpolator flagged as a sub-interpolator (+48 = 1)
// with its offset in the parent and the parent pointer.
void sub_4B75D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b75d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-1);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (a3 == v0) {
        // 0x004b75f0
        charge(ctx, 1);
        lw(a3, s1, anim::kItpMaxFrameSize);
    }
    // 0x004b75f4
    charge(ctx, 12);
    a0 = a2;
    a1 = a3;
    jal(ctx, 0x4B75F8u, gen::fn_sub_4B6E10_004b6e10);  // [RtAnimInterpolatorCreate]
    sw(s1, v0, 56);
    v1 = 1;
    sw(s0, v0, 52);
    sw(v1, v0, 48);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004B76B0 sub_4B76B0 -- 156 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B76B0 [rtDictRemoveEntry]: Removes entry $a1 from dictionary $a0's entry list (+16): the last entry takes its
// place and the list shrinks by one. Returns the dictionary, 0 when the entry is not in it.
void sub_4B76B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b76b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(a0, a0, 16);
    s1 = a1;
    jal(ctx, 0x4B76CCu, gen::fn_name__C9type_info_1_004c21d0);  // [rwSListGetArray]
    lw(a0, s2, 16);
    s0 = v0;
    jal(ctx, 0x4B76D8u, gen::fn_sub_4C21E0_004c21e0);  // [rwSListGetEnd]
    if (s0 != v0) {
        for (;;) {
            // 0x004b76e8
            charge(ctx, 3);
            lw(v1, s0, 0);
            if (s1 == v1) {
                goto L_004b76f4_2;
            }
            // 0x004b7724
            charge(ctx, 3);
            s0 = addiu(s0, 4);
            if (s0 == v0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b7730
    charge(ctx, 1);
    v0 = 0;
    // 0x004b7734 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004b76f4_2:
    charge(ctx, 12);
    link(ctx, 0x4B76F4u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 16);
    call(ctx, gen::fn_sub_4C2120_004c2120);  // [rwSListGetNumEntries]
    lw(a0, s2, 16);
    a1 = addiu(v0, -1);
    jal(ctx, 0x4B7700u, gen::fn_sub_4C21B0_004c21b0);  // [rwSListGetEntry]
    lw(v0, v0, 0);
    sw(v0, s0, 0);
    lw(a0, s2, 16);
    a1 = 1;
    jal(ctx, 0x4B7714u, gen::fn_sub_4C2080_004c2080);  // [rwSListDestroyEndEntries]
    v0 = s2;
    // 0x004b7734 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B7750 sub_4B7750 -- 8 bytes; leaf frame (no stack)
// sub_4B7750 [RtDictSchemaGetCurrentDict]: The schema's current dictionary (+20).
void sub_4B7750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004b7750
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, anim::kDscCurrent);
}

// 0x004B7760 sub_4B7760 -- 12 bytes; leaf frame (no stack)
// sub_4B7760 [RtDictSchemaSetCurrentDict]: Sets the schema's current dictionary (+20). Returns the schema.
void sub_4B7760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004b7760
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, anim::kDscCurrent);
    v0 = a0;
}

// 0x004B7770 sub_4B7770 -- 124 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B7770 [rtDictDestroyEntries]: Releases every entry of dictionary $a0 with the schema's entry-destroy callback
// (+28), then destroys the entry list. Returns 1.
void sub_4B7770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7770
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    link(ctx, 0x4B7788u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, anim::kDictEntries);
    call(ctx, gen::fn_sub_4C21E0_004c21e0);  // [rwSListGetEnd]
    lw(a0, s2, anim::kDictEntries);
    s0 = v0;
    jal(ctx, 0x4B7794u, gen::fn_name__C9type_info_1_004c21d0);  // [rwSListGetArray]
    s1 = v0;
    if (s1 != s0) {
        for (;;) {
            // 0x004b77a8
            charge(ctx, 7);
            lw(v0, s2, anim::kDictSchema);
            lw(a0, s1, 0);
            lw(v0, v0, anim::kDscDestroyCB);
            s1 = addiu(s1, 4);
            jalr(ctx, 0x4B77B4u, v0.u());
            if (s1 == s0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b77c4
        charge(ctx, 1);
    }
    // 0x004b77c8
    charge(ctx, 9);
    link(ctx, 0x4B77C8u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, anim::kDictEntries);
    call(ctx, gen::fn_sub_4C20B0_004c20b0);  // [rwSListDestroy]
    ld(ra, sp, 0x30);
    v0 = 1;
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004B77F0 sub_4B77F0 -- 192 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B77F0 [RtDictFindNamedEntry]: Finds the entry of dictionary $a0 whose name (schema callback +32) equals the
// string $a1 (the RW string-compare slot 0x960158). Returns the entry or 0.
void sub_4B77F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b77f0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, anim::kDictSchema);
    s0 = a0;
    lw(s3, v0, anim::kDscGetNameCB);
    lw(a0, a0, anim::kDictEntries);
    s5 = a1;
    jal(ctx, 0x4B7820u, gen::fn_sub_4C21E0_004c21e0);  // [rwSListGetEnd]
    lw(a0, s0, anim::kDictEntries);
    s2 = v0;
    jal(ctx, 0x4B782Cu, gen::fn_name__C9type_info_1_004c21d0);  // [rwSListGetArray]
    s4 = v0;
    if (s4 != s2) {
        // 0x004b7840
        charge(ctx, 2);
        s1 = 0x960000;
        s1 = addiu(s1, 344);  // &0x960158
        for (;;) {
            // 0x004b7848
            charge(ctx, 9);
            lw(s0, s4, 0);
            a0 = s0;
            jalr(ctx, 0x4B784Cu, s3.u());
            a0 = v0;
            lw(v0, s1, 0);
            a1 = s5;
            jalr(ctx, 0x4B785Cu, v0.u());
            if (v0 == 0) {
                goto L_004b786c_3;
            }
            // 0x004b7878
            charge(ctx, 3);
            s4 = addiu(s4, 4);
            if (s4 == s2) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b7884
        charge(ctx, 1);
    }
    // 0x004b7888
    charge(ctx, 1);
    v0 = 0;
    // 0x004b788c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004b786c_3:
    charge(ctx, 3);
    v0 = dsll32(s0, 0);
    v0 = dsra32(v0, 0);
    // 0x004b788c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x004B79D0 sub_4B79D0 -- 644 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B79D0 [RtDictSchemaStreamReadDict]: Reads a dictionary chunk for schema $a0 from stream $a1: an old-version
// chunk goes to the schema's compatibility reader (+44); otherwise the entry count, a new dictionary (RwMalloc(8) +
// an entry list; registered in the schema's list) and per entry the schema's stream-read (+40), its add-ref (+24) for
// the dictionary's reference and its destroy (+28) for the reader's. A failed entry destroys the dictionary. Returns
// the dictionary or 0.
void sub_4B79D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b79d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    a2 = addiu(sp, 0x6C);
    sq(s3, sp, 0x30);
    a3 = addiu(sp, 0x68);
    sq(s2, sp, 0x20);
    s3 = a0;
    s2 = a1;
    sq(s1, sp, 0x10);
    a0 = s2;
    a1 = 1;
    link(ctx, 0x4B79FCu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);  // [RwStreamFindChunk]
    if (v0 == 0) {
        // 0x004b7a40
        charge(ctx, 2);
        v0 = 0;
    L_004b7c38:
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    } else {
        // 0x004b7a0c
        charge(ctx, 5);
        lw(v1, sp, 0x68);
        lw(v0, s3, anim::kDscVersion);
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004b7a20
            charge(ctx, 6);
            lw(a2, sp, 0x6C);
            a0 = s2;
            a1 = addiu(sp, 0x64);
            jal(ctx, 0x4B7A28u, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
            if (v0 != 0) {
                // 0x004b7a5c
                charge(ctx, 10);
                v0 = 0x960000;
                lw(a1, s3, anim::kDscAllocHint);
                lw(v0, v0, 376);  // 0x960178 RwMalloc slot
                v1 = 0x30000;
                a0 = 8;
                a1 = a1 | v1;
                jalr(ctx, 0x4B7A70u, v0.u());
                s0 = v0;
                if (s0 == 0) {
                    // 0x004b7ad4
                    charge(ctx, 11);
                    v1 = 447;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x58);
                    a0 = v0 | 0x13;
                    a1 = 8;
                    jal(ctx, 0x4B7AE4u, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
                    sw(v0, sp, 0x5C);
                    a0 = addiu(sp, 0x58);
                    jal(ctx, 0x4B7AF0u, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
                    s0 = 0;
                    backedge(ctx);
                } else {
                    // 0x004b7a84
                    charge(ctx, 9);
                    lw(v1, s3, anim::kDscAllocHint);
                    v0 = 0x30000;
                    a0 = 4;
                    a1 = v1 | v0;
                    jal(ctx, 0x4B7A90u, gen::fn_sub_4C1D50_004c1d50);  // [rwSListCreate]
                    sw(v0, s0, 4);
                    lw(v0, s0, 4);
                    if (v0 != 0) {
                        // 0x004b7b00
                        charge(ctx, 8);
                        sw(s3, s0, 0);
                        v0 = 0x30000;
                        lw(v1, s3, anim::kDscAllocHint);
                        lw(a0, s3, anim::kDscDicts);
                        a1 = v1 | v0;
                        jal(ctx, 0x4B7B10u, gen::fn_sub_4C1E70_004c1e70);  // [rwSListGetNewEntry]
                        if (v0 == 0) {
                            // 0x004b7b38
                            charge(ctx, 2);
                            v0 = 0;
                            backedge(ctx);
                        } else {
                            // 0x004b7b20
                            charge(ctx, 2);
                            sw(s0, v0, 0);
                            v0 = s3;
                        }
                        // 0x004b7b28
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x004b7b40
                            charge(ctx, 4);
                            link(ctx, 0x4B7B40u);  // $ra first: the delay slot below depends on it
                            lw(a0, s0, 4);
                            call(ctx, gen::fn_sub_4C20B0_004c20b0);  // [rwSListDestroy]
                            v0 = 0;
                            backedge(ctx);
                        } else {
                            // 0x004b7b30
                            charge(ctx, 2);
                            v0 = s0;
                            backedge(ctx);
                        }
                    } else {
                        // 0x004b7aa8
                        charge(ctx, 1);
                        v0 = 0;
                    }
                    // 0x004b7aac
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x004b7b50
                        charge(ctx, 6);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C RwFree slot
                        a0 = s0;
                        jalr(ctx, 0x4B7B58u, v0.u());
                        s0 = 0;
                        backedge(ctx);
                    }
                }
                // 0x004b7ab4
                charge(ctx, 2);
                if (s0 == 0) {
                    // 0x004b7b68
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004b7abc
                    charge(ctx, 4);
                    lw(v1, sp, 0x64);
                    v0 = addiu(v1, -1);
                    sw(v0, sp, 0x64);
                    if (v1 != 0) {
                        for (;;) {
                            // 0x004b7b70
                            charge(ctx, 7);
                            lw(a1, s3, anim::kDscEntryChunkId);
                            a0 = s2;
                            a2 = addiu(sp, 0x6C);
                            a3 = addiu(sp, 0x68);
                            jal(ctx, 0x4B7B7Cu, gen::fn_sub_4C1600_004c1600);  // [RwStreamFindChunk]
                            if (v0 == 0) {
                                goto L_004b7bf0;
                            }
                            // 0x004b7b8c
                            charge(ctx, 5);
                            lw(v0, s3, anim::kDscStreamReadCB);
                            a0 = s2;
                            jalr(ctx, 0x4B7B90u, v0.u());
                            s1 = v0;
                            if (v0 == 0) {
                                goto L_004b7bf0;
                            }
                            // 0x004b7ba0
                            charge(ctx, 18);
                            lw(v1, s0, 0);
                            v0 = 0x30000;
                            lw(a0, s0, 4);
                            lw(v1, v1, 4);
                            a1 = v1 | v0;
                            jal(ctx, 0x4B7BB0u, gen::fn_sub_4C1E70_004c1e70);  // [rwSListGetNewEntry]
                            sw(s1, v0, 0);
                            lw(v0, s0, 0);
                            lw(v0, v0, 24);
                            a0 = s1;
                            jalr(ctx, 0x4B7BC4u, v0.u());
                            lw(v0, s3, anim::kDscDestroyCB);
                            a0 = s1;
                            jalr(ctx, 0x4B7BD0u, v0.u());
                            lw(v1, sp, 0x64);
                            v0 = addiu(v1, -1);
                            sw(v0, sp, 0x64);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004b7be8
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                    // 0x004b7acc
                    charge(ctx, 2);
                    v0 = s0;
                }
            } else {
                // 0x004b7a38
                charge(ctx, 2);
                v0 = 0;
            }
            goto L_004b7c38;
        }
        // 0x004b7a48
        charge(ctx, 5);
        lw(v0, s3, anim::kDscCompatReadCB);
        a0 = s2;
        jalr(ctx, 0x4B7A4Cu, v0.u());
        ld(ra, sp, 0x40);
    }
    // 0x004b7c3c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b7bf0:
    charge(ctx, 5);
    lw(v0, s0, 0);
    v1 = addiu(v0, 20);
    lw(v0, v0, 20);
    if (s0 == v0) {
        // 0x004b7c30
        charge(ctx, 2);
        sw(zero, v1, 0);
        backedge(ctx);
    }
    // 0x004b7c04
    charge(ctx, 11);
    lw(a0, s0, 0);
    a1 = s0;
    jal(ctx, 0x4B7C08u, gen::fn_sub_4B76B0_004b76b0);  // [rtDictRemoveEntry]
    a0 = s0;
    jal(ctx, 0x4B7C10u, gen::fn_sub_4B7770_004b7770);  // [rtDictDestroyEntries]
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    a0 = s0;
    jalr(ctx, 0x4B7C20u, v0.u());
    v0 = 0;
    goto L_004b7c38;
}

// 0x004B7C60 sub_4B7C60 -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B7C60 [uvAnimKeyFrameInit]: Initialises UV keyframe $a1: previous frame $a2, time $f12, and the UV values from
// matrix $a3 by the animation's scheme (0x77E520 the linear UV scheme, 0x77E550 the parametric one).
void sub_4B7C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004b7c60
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    lw(v1, a0, 0);
    sd(ra, sp, 0x30);
    v0 = 0x780000;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    sw(a2, a1, 0);
    swc1(f12, a1, 4);
    lw(v0, v0, -6880);  // 0x77E520 the linear UV scheme info
    lw(v1, v1, 0);
    s0 = a3;
    if (v1 == v0) {
        // 0x004b7cbc
        charge(ctx, 5);
        a0 = addiu(s1, 8);
        a1 = s0;
        jal(ctx, 0x4B7CC0u, gen::fn_sub_4B8290_004b8290);  // [uvAnimLinearFromMatrix]
        if (v0 == 0) {
            backedge(ctx);
            goto L_004b7c9c;
        }
        // 0x004b7cd0
        charge(ctx, 2);
        v0 = 0;
        // 0x004b7ce8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004b7c9c:
    charge(ctx, 6);
    lw(v1, s2, 0);
    v0 = 0x780000;
    lw(v0, v0, -6832);  // 0x77E550 the parametric UV scheme info
    lw(v1, v1, 0);
    if (v1 == v0) {
        // 0x004b7cd8
        charge(ctx, 4);
        a0 = addiu(s1, 8);
        a1 = s0;
        jal(ctx, 0x4B7CDCu, gen::fn_sub_4B8630_004b8630);  // [uvAnimParamFromMatrix]
        v0 = 0;
    } else {
        // 0x004b7cb4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b7ce8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B7D00 sub_4B7D00 -- 260 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B7D00 [uvAnimStreamRead]: Stream-read callback of the UV keyframe schemes: an int (unused), the custom data
// (uvAnimCustomDataStreamRead), then per keyframe 7 reals and the previous-frame index (stored as a pointer, stride
// 32). Returns the animation or 0.
void sub_4B7D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7d00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 4;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a1 = addiu(sp, 0x6C);
    link(ctx, 0x4B7D28u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
    if (v0 != 0) {
        // 0x004b7d40
        charge(ctx, 4);
        a0 = s4;
        jal(ctx, 0x4B7D40u, gen::fn_sub_4B90A0_004b90a0);  // [uvAnimCustomDataStreamRead]
        if (v0 == 0) {
            // 0x004b7d70
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b7d50
            charge(ctx, 6);
            sw(v0, s3, anim::kAnmCustomData);
            lw(v0, s3, anim::kAnmNumFrames);
            lw(s0, s3, anim::kAnmFrames);
            v0 = slt(0, v0);
            s2 = 0;
            if (v0 != 0) {
                // 0x004b7d78
                charge(ctx, 1);
                s1 = s0;
                for (;;) {
                    // 0x004b7d7c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = addiu(s1, 4);
                    a2 = 28;
                    jal(ctx, 0x4B7D84u, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
                    if (v0 == 0) {
                        // 0x004b7d94_8 (its only goto: the block written out here)
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004b7de4 (the shared epilogue, written out on this path)
                        charge(ctx, 8);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x70);
                        return;
                    }
                    // 0x004b7d9c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = addiu(sp, 0x68);
                    a2 = 4;
                    jal(ctx, 0x4B7DA4u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                    if (v0 == 0) {
                        goto L_004b7de0;
                    }
                    // 0x004b7db4
                    charge(ctx, 9);
                    lw(v0, sp, 0x68);
                    s2 = addiu(s2, 1);
                    v0 = sll(v0, 5);
                    v0 = addu(s0, v0);
                    sw(v0, s1, 0);
                    lw(v0, s3, anim::kAnmNumFrames);
                    v0 = slt(s2, v0);
                    s1 = addiu(s1, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b7dd8
                charge(ctx, 2);
                backedge(ctx);
            }
            // 0x004b7d68
            charge(ctx, 2);
            v0 = s3;
        }
    } else {
        // 0x004b7d38
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b7de4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b7de0:
    charge(ctx, 1);
    v0 = 0;
    // 0x004b7de4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004B7E10 sub_4B7E10 -- 280 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B7E10 [uvAnimStreamWrite]: Stream-write callback of the UV keyframe schemes: 0, the custom data, then per
// keyframe 7 reals and the previous-frame index. Returns 1 or 0.
void sub_4B7E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7e10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 4;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a0 = s3;
    sq(s0, sp, 0x0);
    a1 = addiu(sp, 0x6C);
    link(ctx, 0x4B7E40u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x6C);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
    if (v0 != 0) {
        // 0x004b7e58
        charge(ctx, 5);
        lw(a0, s4, anim::kAnmCustomData);
        a1 = s3;
        jal(ctx, 0x4B7E5Cu, gen::fn_sub_4B9140_004b9140);  // [uvAnimCustomDataStreamWrite]
        if (v0 == 0) {
            // 0x004b7e88
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b7e6c
            charge(ctx, 5);
            lw(v0, s4, anim::kAnmNumFrames);
            lw(s0, s4, anim::kAnmFrames);
            v0 = slt(0, v0);
            s2 = 0;
            if (v0 != 0) {
                // 0x004b7e90
                charge(ctx, 1);
                s1 = s0;
                for (;;) {
                    // 0x004b7e94
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = addiu(s1, 4);
                    a2 = 28;
                    jal(ctx, 0x4B7E9Cu, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
                    if (v0 == 0) {
                        // 0x004b7eac_8 (its only goto: the block written out here)
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004b7f08 (the shared epilogue, written out on this path)
                        charge(ctx, 8);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x70);
                        return;
                    }
                    // 0x004b7eb4
                    charge(ctx, 4);
                    lw(v0, s1, 0);
                    v1 = subu(v0, s0);
                    v0 = sra(v1, 5);
                    if (i64(v1) < 0) {
                        // 0x004b7ec4
                        charge(ctx, 2);
                        v0 = addiu(v1, 31);
                        v0 = sra(v0, 5);
                    }
                    // 0x004b7ecc
                    charge(ctx, 7);
                    sw(v0, sp, 0x68);
                    a0 = s3;
                    a1 = addiu(sp, 0x68);
                    a2 = 4;
                    jal(ctx, 0x4B7ED8u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                    if (v0 == 0) {
                        goto L_004b7f04;
                    }
                    // 0x004b7ee8
                    charge(ctx, 5);
                    lw(v0, s4, anim::kAnmNumFrames);
                    s2 = addiu(s2, 1);
                    v0 = slt(s2, v0);
                    s1 = addiu(s1, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b7efc
                charge(ctx, 2);
                backedge(ctx);
            }
            // 0x004b7e80
            charge(ctx, 2);
            v0 = 1;
        }
    } else {
        // 0x004b7e50
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b7f08 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b7f04:
    charge(ctx, 1);
    v0 = 0;
    // 0x004b7f08 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004B7F30 sub_4B7F30 -- 68 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B7F30 [uvAnimStreamGetSize]: Stream-size callback of the UV keyframe schemes: the custom data size + 4 + 32
// per keyframe.
void sub_4B7F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7f30
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    lw(a0, a0, anim::kAnmCustomData);
    s0 = 4;
    jal(ctx, 0x4B7F48u, gen::fn_sub_4B91B0_004b91b0);
    v1 = addu(s0, v0);
    ld(ra, sp, 0x20);
    lw(v0, s1, anim::kAnmNumFrames);
    lq(s0, sp, 0x0);
    lq(s1, sp, 0x10);
    v0 = sll(v0, 5);
    v0 = addu(v1, v0);
    sp = addiu(sp, 0x30);
}

// 0x004B7F80 sub_4B7F80 -- 76 bytes; leaf frame (no stack)
// sub_4B7F80 [uvAnimLinearApply]: Apply callback of the linear UV scheme: writes interpolated frame $a1's six UV
// values into matrix $a0 (right.xy, up.xy, pos.xy; the rest zero) and updates the matrix flags.
void sub_4B7F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0};
    // 0x004b7f80
    enter(ctx, 19);  // entry check point + this block's cycles
    lwc1(f0, a1, 8);
    swc1(f0, a0, 0);
    lwc1(f0, a1, 12);
    swc1(f0, a0, 4);
    sw(zero, a0, 8);
    lwc1(f0, a1, 16);
    swc1(f0, a0, 16);
    lwc1(f0, a1, 20);
    swc1(f0, a0, 20);
    sw(zero, a0, 24);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    lwc1(f0, a1, 24);
    swc1(f0, a0, 48);
    lwc1(f0, a1, 28);
    swc1(f0, a0, 52);
    sw(zero, a0, 56);
    gen::fn_sub_4C2F10_004c2f10(ctx);  // tail call
}

// 0x004B7FD0 sub_4B7FD0 -- 172 bytes; leaf frame (no stack)
// sub_4B7FD0 [uvAnimLinearInterpolate]: Interpolate callback of the linear UV scheme: out ($a0) = key1 + (key2 -
// key1) x (t - t1) / (t2 - t1) for the six values, t in $f12.
void sub_4B7FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12};
    // 0x004b7fd0
    enter(ctx, 43);  // entry check point + this block's cycles
    lwc1(f5, a1, 4);
    lwc1(f4, a2, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a2, 8);
    mtc1(zero, f2);
    sub_s(f3, f12, f5);
    sub_s(f4, f4, f5);
    div_s(f3, f3, f4);
    sub_s(f0, f0, f1);
    adda_s(f2, f1);
    madd_s(f0, f3, f0);
    swc1(f0, a0, 8);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 12);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, a0, 12);
    lwc1(f1, a1, 16);
    lwc1(f0, a2, 16);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, a0, 16);
    lwc1(f1, a1, 20);
    lwc1(f0, a2, 20);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, a0, 20);
    lwc1(f1, a1, 24);
    lwc1(f0, a2, 24);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, a0, 24);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, a0, 28);
}

// 0x004B8080 sub_4B8080 -- 156 bytes; leaf frame (no stack)
// sub_4B8080 [uvAnimLinearBlend]: Blend callback of the linear UV scheme: out = a + (b - a) x $f12 for the six
// values.
void sub_4B8080(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x004b8080
    enter(ctx, 39);  // entry check point + this block's cycles
    lwc1(f1, a1, 8);
    lwc1(f0, a2, 8);
    mtc1(zero, f2);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 8);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 12);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 12);
    lwc1(f1, a1, 16);
    lwc1(f0, a2, 16);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 16);
    lwc1(f1, a1, 20);
    lwc1(f0, a2, 20);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 20);
    lwc1(f1, a1, 24);
    lwc1(f0, a2, 24);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 24);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 28);
}

// 0x004B8120 sub_4B8120 -- 204 bytes; leaf frame (no stack)
// sub_4B8120 [uvAnimLinearMulRecip]: Mul-recip callback of the linear UV scheme: replaces frame $a0 by its product
// with the inverse of the 2x2 part of $a1 (when invertible) and subtracts $a1's translation.
void sub_4B8120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004b8120
    enter(ctx, 11);  // entry check point + this block's cycles
    lwc1(f4, a1, 20);
    a0 = addiu(a0, 8);
    lwc1(f0, a1, 8);
    lwc1(f5, a1, 16);
    lwc1(f1, a1, 12);
    mtc1(zero, f9);
    mula_s(f0, f4);
    msub_s(f3, f1, f5);
    c_eq_s(f3, f9);
    a2 = addiu(a1, 8);
    if (!cond(ctx)) {
        // 0x004b8170
        charge(ctx, 29);
        v1 = 0x3F800000;
        mtc1(v1, f2);
        neg_s(f0, f5);
        div_s(f2, f2, f3);
        mul_s(f5, f4, f2);
        neg_s(f1, f1);
        lwc1(f6, a0, 8);
        mul_s(f1, f1, f2);
        mul_s(f4, f0, f2);
        lwc1(f3, a0, 12);
        mul_s(f0, f1, f6);
        mul_s(f2, f1, f3);
        adda_s(f9, f0);
        lwc1(f8, a0, 0);
        mul_s(f0, f4, f3);
        madd_s(f3, f5, f8);
        lwc1(f7, a0, 4);
        adda_s(f9, f2);
        mul_s(f1, f4, f6);
        madd_s(f2, f5, f7);
        adda_s(f9, f1);
        swc1(f3, a0, 0);
        madd_s(f1, f4, f8);
        swc1(f2, a0, 4);
        adda_s(f9, f0);
        madd_s(f0, f4, f7);
        swc1(f1, a0, 8);
        swc1(f0, a0, 12);
        backedge(ctx);
    }
    // 0x004b814c
    charge(ctx, 9);
    lwc1(f1, a2, 16);
    lwc1(f0, a0, 16);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 16);
    lwc1(f1, a2, 20);
    lwc1(f0, a0, 20);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 20);
    // 0x004b81e4
    charge(ctx, 2);
}

// 0x004B81F0 sub_4B81F0 -- 148 bytes; leaf frame (no stack)
// sub_4B81F0 [uvAnimLinearAdd]: Add callback of the linear UV scheme: the 2x2 product of the two frames' matrices and
// the sum of their translations.
void sub_4B81F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004b81f0
    enter(ctx, 37);  // entry check point + this block's cycles
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 16);
    lwc1(f3, a1, 8);
    lwc1(f2, a2, 8);
    mula_s(f1, f0);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 8);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 20);
    lwc1(f3, a1, 8);
    lwc1(f2, a2, 12);
    mula_s(f1, f0);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 12);
    lwc1(f1, a1, 20);
    lwc1(f0, a2, 16);
    lwc1(f3, a1, 16);
    lwc1(f2, a2, 8);
    mula_s(f1, f0);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 16);
    lwc1(f1, a1, 20);
    lwc1(f0, a2, 20);
    lwc1(f3, a1, 16);
    lwc1(f2, a2, 12);
    mula_s(f1, f0);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 20);
    lwc1(f1, a1, 24);
    lwc1(f0, a2, 24);
    add_s(f0, f1, f0);
    swc1(f0, a0, 24);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    add_s(f0, f1, f0);
    swc1(f0, a0, 28);
}

// 0x004B8290 sub_4B8290 -- 56 bytes; leaf frame (no stack)
// sub_4B8290 [uvAnimLinearFromMatrix]: Copies a matrix's UV part (right.xy, up.xy, pos.xy) into the six values of a
// linear UV keyframe. Returns 0 (the caller then takes the matrix as it is).
void sub_4B8290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x004b8290
    enter(ctx, 14);  // entry check point + this block's cycles
    lwc1(f5, a1, 0);
    v0 = a0;
    lwc1(f4, a1, 4);
    lwc1(f3, a1, 16);
    lwc1(f2, a1, 20);
    lwc1(f1, a1, 48);
    lwc1(f0, a1, 52);
    swc1(f5, a0, 0);
    swc1(f4, a0, 4);
    swc1(f3, a0, 8);
    swc1(f2, a0, 12);
    swc1(f1, a0, 16);
    swc1(f0, a0, 20);
}

// 0x004B82D0 sub_4B82D0 -- 248 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B82D0 [uvAnimParamApply]: Apply callback of the parametric UV scheme: builds the matrix from the frame's
// (angle, scale u, scale v, skew, pos u, pos v) -- scale and translation set, then translate (-0.5), rotate about z
// by the angle, translate back (0x7BCBC8 / 0x7BCBD8).
void sub_4B82D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x004b82d0
    enter(ctx, 62);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(a1, 8);
    lwc1(f2, v0, -6976);  // 0x77E4C0
    s0 = a0;
    v0 = 0x780000;
    lwc1(f1, v0, -6972);  // 0x77E4C4
    swc1(f2, sp, 0x30);
    v0 = 0x780000;
    lwc1(f0, v0, -6968);  // 0x77E4C8
    swc1(f1, sp, 0x34);
    swc1(f0, sp, 0x38);
    lwc1(f0, a1, 12);
    swc1(f0, a0, 0);
    lwc1(f0, a1, 20);
    swc1(f0, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 16);
    lwc1(f0, a1, 16);
    swc1(f0, a0, 20);
    sw(zero, a0, 24);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    lwc1(f0, a1, 24);
    swc1(f0, a0, 48);
    lwc1(f0, a1, 28);
    swc1(f0, a0, 52);
    link(ctx, 0x4B834Cu);  // $ra first: the delay slot below depends on it
    sw(zero, a0, 56);
    call(ctx, gen::fn_sub_4C2F10_004c2f10);  // [RwMatrixUpdate]
    a1 = 0x7C0000;
    a0 = s0;
    a1 = addiu(a1, -13368);  // &0x7BCBC8
    a2 = 2;
    jal(ctx, 0x4B8360u, gen::fn_sub_4C35D0_004c35d0);  // [RwMatrixTranslate]
    lwc1(f1, s1, 0);
    v0 = 0x40490000;
    v1 = v0 | 0xFDB;
    a0 = s0;
    mtc1(v1, f2);
    v0 = 0x43340000;
    mtc1(v0, f0);
    a1 = addiu(sp, 0x30);
    a2 = 2;
    div_s(f1, f1, f2);
    mul_s(f12, f0, f1);
    jal(ctx, 0x4B8398u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
    a1 = 0x7C0000;
    a0 = s0;
    a1 = addiu(a1, -13352);  // &0x7BCBD8
    a2 = 2;
    jal(ctx, 0x4B83ACu, gen::fn_sub_4C35D0_004c35d0);  // [RwMatrixTranslate]
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004B83D0 sub_4B83D0 -- 292 bytes; leaf frame (no stack)
// sub_4B83D0 [uvAnimParamInterpolate]: Interpolate callback of the parametric UV scheme: linear in the six parameters
// between the two keyframes at t = $f12.
void sub_4B83D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12};
    // 0x004b83d0
    enter(ctx, 18);  // entry check point + this block's cycles
    lwc1(f4, a1, 4);
    v1 = lui(0xC049);
    lwc1(f3, a2, 4);
    t0 = addiu(a0, 8);
    v1 = v1 | 0xFDB;
    a3 = addiu(a1, 8);
    lwc1(f5, a1, 8);
    a0 = addiu(a2, 8);
    lwc1(f1, a2, 8);
    mtc1(v1, f0);
    sub_s(f2, f12, f4);
    sub_s(f3, f3, f4);
    div_s(f3, f2, f3);
    sub_s(f1, f1, f5);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x004b84d8
        charge(ctx, 5);
        v1 = 0x40C90000;
        v1 = v1 | 0xFDB;
        mtc1(v1, f0);
        add_s(f1, f1, f0);
        backedge(ctx);
    } else {
        // 0x004b8418
        charge(ctx, 7);
        v1 = 0x40490000;
        v1 = v1 | 0xFDB;
        mtc1(v1, f0);
        c_le_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004b8434
            charge(ctx, 5);
            v1 = 0x40C90000;
            v1 = v1 | 0xFDB;
            mtc1(v1, f0);
            sub_s(f1, f1, f0);
        }
    }
    // 0x004b8448
    charge(ctx, 36);
    mtc1(zero, f2);
    adda_s(f2, f5);
    madd_s(f0, f3, f1);
    swc1(f0, t0, 0);
    lwc1(f1, a3, 4);
    lwc1(f0, a0, 4);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, t0, 4);
    lwc1(f1, a3, 8);
    lwc1(f0, a0, 8);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, t0, 8);
    lwc1(f1, a3, 12);
    lwc1(f0, a0, 12);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, t0, 12);
    lwc1(f1, a3, 16);
    lwc1(f0, a0, 16);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, t0, 16);
    lwc1(f1, a3, 20);
    lwc1(f0, a0, 20);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f3, f0);
    swc1(f0, t0, 20);
    // 0x004b84ec
    charge(ctx, 2);
}

// 0x004B8500 sub_4B8500 -- 268 bytes; leaf frame (no stack)
// sub_4B8500 [uvAnimParamBlend]: Blend callback of the parametric UV scheme: linear in the six parameters with weight
// $f12.
void sub_4B8500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x004b8500
    enter(ctx, 12);  // entry check point + this block's cycles
    lwc1(f3, a1, 8);
    v1 = lui(0xC049);
    lwc1(f1, a2, 8);
    v1 = v1 | 0xFDB;
    a3 = addiu(a0, 8);
    t0 = addiu(a2, 8);
    mtc1(v1, f0);
    sub_s(f1, f1, f3);
    c_lt_s(f1, f0);
    a0 = addiu(a1, 8);
    if (cond(ctx)) {
        // 0x004b85f0
        charge(ctx, 5);
        v1 = 0x40C90000;
        v1 = v1 | 0xFDB;
        mtc1(v1, f0);
        add_s(f1, f1, f0);
        backedge(ctx);
    } else {
        // 0x004b8530
        charge(ctx, 7);
        v1 = 0x40490000;
        v1 = v1 | 0xFDB;
        mtc1(v1, f0);
        c_le_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004b854c
            charge(ctx, 5);
            v1 = 0x40C90000;
            v1 = v1 | 0xFDB;
            mtc1(v1, f0);
            sub_s(f1, f1, f0);
        }
    }
    // 0x004b8560
    charge(ctx, 36);
    mtc1(zero, f2);
    adda_s(f2, f3);
    madd_s(f0, f12, f1);
    swc1(f0, a3, 0);
    lwc1(f1, a0, 4);
    lwc1(f0, t0, 4);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a3, 4);
    lwc1(f1, a0, 8);
    lwc1(f0, t0, 8);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a3, 8);
    lwc1(f1, a0, 12);
    lwc1(f0, t0, 12);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a3, 12);
    lwc1(f1, a0, 16);
    lwc1(f0, t0, 16);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a3, 16);
    lwc1(f1, a0, 20);
    lwc1(f0, t0, 20);
    adda_s(f2, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f12, f0);
    swc1(f0, a3, 20);
    // 0x004b8604
    charge(ctx, 2);
}

// 0x004B8610 nullsub_125 -- 8 bytes; leaf frame (no stack)
// nullsub_125 [uvAnimParamMulRecip]: Mul-recip callback of the parametric UV scheme: nothing (jr $ra).
void nullsub_125(EEContext& ctx) {
    using namespace hg;
    // 0x004b8610
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x004B8620 nullsub_126 -- 8 bytes; leaf frame (no stack)
// nullsub_126 [uvAnimParamAdd]: Add callback of the parametric UV scheme: nothing (jr $ra).
void nullsub_126(EEContext& ctx) {
    using namespace hg;
    // 0x004b8620
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x004B8630 sub_4B8630 -- 272 bytes; frame 0x70: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B8630 [uvAnimParamFromMatrix]: Converts a matrix into the parametric UV values: angle = atan2 of the first
// row, then the matrix rotated back about the centre gives the scales, skew and position.
void sub_4B8630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13};
    // 0x004b8630
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x10);
    a2 = addiu(sp, 0x20);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 8;
    for (;;) {
        // 0x004b8648
        charge(ctx, 8);
        lw(v1, a1, 0);
        a0 = addiu(a0, -1);
        lw(v0, a1, 4);
        sw(v1, a2, 0);
        sw(v0, a2, 4);
        a1 = addiu(a1, 8);
        a2 = addiu(a2, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b8668
    charge(ctx, 54);
    v0 = 0x780000;
    v1 = 0x780000;
    lwc1(f3, v0, -6960);  // 0x77E4D0
    lwc1(f2, v1, -6956);  // 0x77E4D4
    lwc1(f0, sp, 0x30);
    lwc1(f13, sp, 0x20);
    v0 = 0x780000;
    lwc1(f1, v0, -6952);  // 0x77E4D8
    swc1(f3, sp, 0x60);
    swc1(f2, sp, 0x64);
    neg_s(f12, f0);
    link(ctx, 0x4B8694u);  // $ra first: the delay slot below depends on it
    swc1(f1, sp, 0x68);
    call(ctx, gen::fn_atan2f_0052ea18);  // [atan2f]
    a1 = 0x7C0000;
    a0 = addiu(sp, 0x20);
    swc1(f0, s0, 0);
    a1 = addiu(a1, -13368);  // &0x7BCBC8
    a2 = 2;
    jal(ctx, 0x4B86ACu, gen::fn_sub_4C35D0_004c35d0);  // [RwMatrixTranslate]
    lwc1(f2, s0, 0);
    v0 = 0x40490000;
    v1 = v0 | 0xFDB;
    a0 = addiu(sp, 0x20);
    v0 = 0x43340000;
    a1 = addiu(sp, 0x60);
    mtc1(v1, f1);
    a2 = 2;
    mtc1(v0, f0);
    neg_s(f2, f2);
    div_s(f1, f2, f1);
    mul_s(f12, f0, f1);
    jal(ctx, 0x4B86E8u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
    a1 = 0x7C0000;
    a0 = addiu(sp, 0x20);
    a1 = addiu(a1, -13352);  // &0x7BCBD8
    a2 = 2;
    jal(ctx, 0x4B86FCu, gen::fn_sub_4C35D0_004c35d0);  // [RwMatrixTranslate]
    lwc1(f0, sp, 0x20);
    v0 = s0;
    swc1(f0, s0, 4);
    lwc1(f0, sp, 0x24);
    swc1(f0, s0, 12);
    lwc1(f0, sp, 0x34);
    swc1(f0, s0, 8);
    lwc1(f0, sp, 0x50);
    swc1(f0, s0, 16);
    lwc1(f0, sp, 0x54);
    swc1(f0, s0, 20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004B8740 sub_4B8740 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B8740 [uvAnimOpen]: RpUVAnim's engine-open callback: creates the 68-byte custom-data free list (0x7CE8B0),
// initialises the UV-animation dictionary schema 0x77E4E0 and registers the two UV schemes (0x77E520 id 0x1C0,
// 0x77E550 id 0x1C1); counts the open (0x7CE8AC).
void sub_4B8740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b8740
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x40000;
    sd(ra, sp, 0x10);
    a2 = 4;
    sq(s0, sp, 0x0);
    t1 = v0 | 0x135;
    lw(a1, gp, -20468);  // 0x7CDCFC
    s0 = a0;
    lw(a3, gp, -20464);  // 0x7CDD00
    lw(t0, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
    a0 = 68;
    jal(ctx, 0x4B8768u, gen::fn_sub_4C3B60_004c3b60);  // [RwFreeListCreate]
    sw(v0, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
    if (v0 == 0) {
        // 0x004b87b0
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    }
    // 0x004b8778
    charge(ctx, 14);
    a0 = 0x780000;
    a0 = addiu(a0, -6944);  // &0x77E4E0
    jal(ctx, 0x4B877Cu, gen::fn_sub_4B7630_004b7630);
    a0 = 0x780000;
    a0 = addiu(a0, -6880);  // &0x77E520
    jal(ctx, 0x4B8788u, gen::fn_sub_4B6680_004b6680);  // [RtAnimRegisterInterpolationScheme]
    a0 = 0x780000;
    a0 = addiu(a0, -6832);  // &0x77E550
    jal(ctx, 0x4B8794u, gen::fn_sub_4B6680_004b6680);  // [RtAnimRegisterInterpolationScheme]
    lw(v1, gp, -17476);  // 0x7CE8AC RpUVAnim: open count
    v0 = s0;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17476);  // 0x7CE8AC RpUVAnim: open count
    // 0x004b87b8
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B87D0 sub_4B87D0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B87D0 [uvAnimClose]: RpUVAnim's engine-close callback: drops the open count, closes the dictionary schema and
// destroys the custom-data free list.
void sub_4B87D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b87d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17476);  // 0x7CE8AC RpUVAnim: open count
    s0 = a0;
    a0 = 0x780000;
    a0 = addiu(a0, -6944);  // &0x77E4E0
    v0 = addiu(v0, -1);
    link(ctx, 0x4B87F0u);  // $ra first: the delay slot below depends on it
    sw(v0, gp, -17476);  // 0x7CE8AC RpUVAnim: open count
    call(ctx, gen::fn_sub_4B7690_004b7690);
    lw(a0, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
    if (a0 != 0) {
        // 0x004b8804
        charge(ctx, 3);
        jal(ctx, 0x4B8804u, gen::fn_sub_4C3C30_004c3c30);  // [RwFreeListDestroy]
        sw(zero, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
    }
    // 0x004b8810 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B8830 sub_4B8830 -- 164 bytes; frame 0x10: ra sp+0x0
// sub_4B8830 [RpUVAnimPluginAttach]: Attaches RpUVAnim (id 0x135): the engine plugin, a 48-byte material extension
// (offset 0x7CE8B4: two UV matrices + eight interpolator slots) and its stream callbacks. Returns 1 on success.
void sub_4B8830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b8830
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 309;
    a2 = addiu(a2, -30912);  // &sub_4B8740
    a3 = addiu(a3, -30768);  // &sub_4B87D0
    jal(ctx, 0x4B884Cu, gen::fn_sub_4CA520_004ca520);  // [RwEngineRegisterPlugin]
    if (i64(v0) >= 0) {
        // 0x004b8864
        charge(ctx, 22);
        a2 = 0x4C0000;
        a3 = 0x4C0000;
        t0 = 0x4C0000;
        a0 = 48;
        a1 = 309;
        a2 = addiu(a2, -30496);  // &sub_4B88E0
        a3 = addiu(a3, -30432);  // &sub_4B8920
        t0 = addiu(t0, -30256);  // &sub_4B89D0
        jal(ctx, 0x4B8880u, gen::fn_sub_494DB0_00494db0);  // [RpMaterialRegisterPlugin]
        a1 = 0x4C0000;
        a2 = 0x4C0000;
        a3 = 0x4C0000;
        sw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
        a0 = 309;
        a1 = addiu(a1, -29072);  // &sub_4B8E70
        a2 = addiu(a2, -29648);  // &sub_4B8C30
        a3 = addiu(a3, -28624);  // &sub_4B9030
        jal(ctx, 0x4B88A4u, gen::fn_sub_494DE0_00494de0);  // [RpMaterialRegisterPluginStream]
        v0 = slt(v0, 0);
        v0 = v0 ^ 0x1;
        if (v0 != 0) {
            // 0x004b88bc
            charge(ctx, 3);
            lw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
            v0 = slt(v0, 0);
            v0 = v0 ^ 0x1;
        }
    } else {
        // 0x004b885c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b88c8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004B88E0 sub_4B88E0 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B88E0 [uvAnimMaterialCtor]: Material constructor of RpUVAnim: zeroes the 48-byte extension.
void sub_4B88E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b88e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(ra, sp, 0x10);
    a2 = 48;
    sq(s0, sp, 0x0);
    lw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    s0 = a0;
    a0 = addu(s0, v0);
    jal(ctx, 0x4B88FCu, gen::fn_memset_00521408);  // [memset]
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B8920 sub_4B8920 -- 168 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B8920 [uvAnimMaterialDtor]: Material destructor of RpUVAnim: destroys the two UV matrices and, per used slot,
// releases the animation (refcount) and destroys the interpolator.
void sub_4B8920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b8920
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = 0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    s0 = addu(s1, v0);
    s2 = s0;
    for (;;) {
        // 0x004b894c
        charge(ctx, 3);
        lw(a0, s2, 0);
        if (a0 != 0) {
            // 0x004b8958
            charge(ctx, 2);
            jal(ctx, 0x4B8958u, gen::fn_sub_4C3880_004c3880);  // [RwMatrixDestroy]
        }
        // 0x004b8960
        charge(ctx, 5);
        s3 = addiu(s3, 1);
        sw(zero, s2, 0);
        v0 = sltiu(s3, 2);
        s2 = addiu(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b8974
    charge(ctx, 1);
    s3 = 0;
    for (;;) {
        // 0x004b8978
        charge(ctx, 3);
        lw(s2, s0, 8);
        if (s2 != 0) {
            // 0x004b8984
            charge(ctx, 5);
            link(ctx, 0x4B8984u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 0);
            call(ctx, gen::fn_sub_4B92D0_004b92d0);  // [RpUVAnimDestroy]
            a0 = s2;
            jal(ctx, 0x4B898Cu, gen::fn_sub_4B6EB0_004b6eb0);  // [RtAnimInterpolatorDestroy]
        }
        // 0x004b8998
        charge(ctx, 4);
        s3 = addiu(s3, 1);
        v0 = sltiu(s3, 8);
        s0 = addiu(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b89a8
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004B89D0 sub_4B89D0 -- 308 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B89D0 [uvAnimMaterialCopy]: Material copy callback of RpUVAnim: per slot a new interpolator for the source
// slot's animation with its frames copied and the animation's refcount raised; on a failure every interpolator made
// so far is released and 0 is returned.
void sub_4B89D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004b89d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = 0x1;
    sq(s6, sp, 0x60);
    s7 = a0;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = 0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    s5 = addu(s7, v0);
    s3 = addu(a1, v0);
    s6 = s5;
    for (;;) {
        // 0x004b8a18
        charge(ctx, 3);
        lw(s2, s3, 8);
        s1 = addiu(s6, 8);
        if (s2 == 0) {
            // 0x004b8ac8
            charge(ctx, 2);
            sw(zero, s1, 0);
            backedge(ctx);
        L_004b8a60:
            charge(ctx, 5);
            s4 = addiu(s4, 1);
            v0 = sltiu(s4, 8);
            s3 = addiu(s3, 4);
            s6 = addiu(s6, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            continue;
        }
        // 0x004b8a24
        charge(ctx, 11);
        lw(s0, s2, 0);
        a0 = s0;
        jal(ctx, 0x4B8A28u, gen::fn_sub_4B6DD0_004b6dd0);  // [RtAnimAnimationGetNumNodes]
        lw(v1, s0, 0);
        lw(a1, v1, 4);
        a0 = v0;
        jal(ctx, 0x4B8A38u, gen::fn_sub_4B6E10_004b6e10);  // [RtAnimInterpolatorCreate]
        sw(v0, s1, 0);
        lw(a0, s1, 0);
        if (a0 == 0) {
            goto L_004b8ac0;
        }
        // 0x004b8a50
        charge(ctx, 4);
        a1 = s2;
        jal(ctx, 0x4B8A50u, gen::fn_sub_4B7020_004b7020);  // [RtAnimInterpolatorCopy]
        a0 = s0;
        jal(ctx, 0x4B8A58u, gen::fn_sub_4B9350_004b9350);  // [RpUVAnimAddRef]
        goto L_004b8a60;
    }
    // 0x004b8a74
    charge(ctx, 1);
L_004b8a78:
    charge(ctx, 2);
    if (fp != 0) {
        // 0x004b8ad0
        charge(ctx, 1);
        v0 = s7;
    } else {
        // 0x004b8a80
        charge(ctx, 3);
        at = sltu(0, s4);
        s1 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004b8a8c
                charge(ctx, 3);
                lw(v0, s5, 8);
                s0 = addiu(s5, 8);
                if (v0 != 0) {
                    // 0x004b8a98
                    charge(ctx, 4);
                    link(ctx, 0x4B8A98u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4B92D0_004b92d0);  // [RpUVAnimDestroy]
                    link(ctx, 0x4B8AA0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 0);
                    call(ctx, gen::fn_sub_4B6EB0_004b6eb0);  // [RtAnimInterpolatorDestroy]
                }
                // 0x004b8aa8
                charge(ctx, 4);
                s1 = addiu(s1, 1);
                v0 = sltu(s1, s4);
                s5 = addiu(s5, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b8ab8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b8ad4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
    return;
L_004b8ac0:
    charge(ctx, 2);
    fp = 0;
    backedge(ctx);
    goto L_004b8a78;
}

// 0x004B8B10 sub_4B8B10 -- 288 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B8B10 [uvAnimMaterialUpdateMatrices]: Creates or destroys the material's two UV matrices: matrix c exists only
// while some slot's animation maps a node to UV channel c (custom data +32). Returns the extension, 0 when a matrix
// could not be created.
void sub_4B8B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b8b10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = s2;
    for (;;) {
        // 0x004b8b30
        charge(ctx, 4);
        a3 = 0;
        a2 = 0;
        a1 = 0;
        for (;;) {
            // 0x004b8b40
            charge(ctx, 5);
            v0 = sll(a3, 2);
            v0 = addu(s2, v0);
            lw(a0, v0, 8);
            if (a0 == 0) {
                // 0x004b8be8
                charge(ctx, 2);
                a3 = addiu(a3, 1);
                backedge(ctx);
            L_004b8b90:
                charge(ctx, 3);
                v0 = sltiu(a3, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                continue;
            }
            // 0x004b8b54
            charge(ctx, 7);
            lw(v0, a0, 0);
            v1 = sll(a2, 2);
            lw(v0, v0, 20);
            v0 = addu(v0, v1);
            lw(v0, v0, 32);
            if (s1 == v0) {
                goto L_004b8be0;
            }
            // 0x004b8b70
            charge(ctx, 5);
            lw(v0, a0, 44);
            a2 = addiu(a2, 1);
            v0 = sltu(a2, v0);
            if (v0 == 0) {
                // 0x004b8b84
                charge(ctx, 3);
                a2 = 0;
                a3 = addiu(a3, 1);
            }
            goto L_004b8b90;
        }
        // 0x004b8b9c
        charge(ctx, 1);
    L_004b8ba0:
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x004b8bf0
            charge(ctx, 3);
            lw(v0, s0, 0);
            if (v0 != 0) {
                backedge(ctx);
                goto L_004b8ba8;
            }
            // 0x004b8bfc
            charge(ctx, 6);
            jal(ctx, 0x4B8BFCu, gen::fn_sub_4C38C0_004c38c0);  // [RwMatrixCreate]
            sw(v0, s0, 0);
            lw(v0, s0, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        L_004b8bc8:
            charge(ctx, 4);
            s1 = addiu(s1, 1);
            v0 = sltiu(s1, 2);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                // 0x004b8bd8_13 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = s2;
                // 0x004b8c18 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(ra, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x40);
                return;
            }
            backedge(ctx);
            continue;
        }
    L_004b8ba8:
        charge(ctx, 2);
        if (a1 == 0) {
            // 0x004b8bb0
            charge(ctx, 3);
            lw(a0, s0, 0);
            if (a0 != 0) {
                // 0x004b8bbc
                charge(ctx, 3);
                jal(ctx, 0x4B8BBCu, gen::fn_sub_4C3880_004c3880);  // [RwMatrixDestroy]
                sw(zero, s0, 0);
            }
        }
        goto L_004b8bc8;
    }
    // 0x004b8c14
    charge(ctx, 1);
    v0 = 0;
    // 0x004b8c18 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004b8be0:
    charge(ctx, 2);
    a1 = 1;
    backedge(ctx);
    goto L_004b8ba0;
}

// 0x004B8C30 sub_4B8C30 -- 276 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B8C30 [uvAnimMaterialStreamWrite]: Material stream-write of RpUVAnim: a chunk with the slot mask and the
// 32-byte name of each slot's animation.
void sub_4B8C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b8c30
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0;
    sd(ra, sp, 0x30);
    a3 = 0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    sw(zero, sp, 0x4C);
    s0 = addu(a2, v1);
    a2 = 4;
    a1 = s0;
    a0 = 1;
    for (;;) {
        // 0x004b8c68
        charge(ctx, 3);
        lw(v1, a1, 8);
        if (v1 != 0) {
            // 0x004b8cb4
            charge(ctx, 7);
            v0 = dsll32(v0, 0);
            v1 = sllv(a0, a3);
            v0 = dsra32(v0, 0);
            a2 = addiu(a2, 32);
            v0 = v0 | v1;
            sw(v0, sp, 0x4C);
            backedge(ctx);
        } else {
            // 0x004b8c74
            charge(ctx, 1);
        }
        // 0x004b8c78
        charge(ctx, 5);
        a3 = addiu(a3, 1);
        v1 = sltiu(a3, 8);
        a1 = addiu(a1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b8c8c
    charge(ctx, 8);
    v0 = 0x30000;
    a0 = s1;
    a1 = 1;
    t0 = 55;
    a3 = v0 | 0x7002;
    jal(ctx, 0x4B8C9Cu, gen::fn_sub_4C15A0_004c15a0);  // [RwStreamWriteVersionedChunkHeader]
    if (v0 != 0) {
        // 0x004b8cd0
        charge(ctx, 6);
        a0 = s1;
        a1 = addiu(sp, 0x4C);
        a2 = 4;
        jal(ctx, 0x4B8CD8u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 == 0) {
            // 0x004b8d28
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004b8ce8
            charge(ctx, 1);
            s2 = 0;
            for (;;) {
                // 0x004b8cec
                charge(ctx, 3);
                lw(v0, s0, 8);
                if (v0 != 0) {
                    // 0x004b8cf8
                    charge(ctx, 6);
                    link(ctx, 0x4B8CF8u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4B96E0_004b96e0);  // [uvAnimGetName]
                    a1 = v0;
                    a0 = s1;
                    a2 = 32;
                    jal(ctx, 0x4B8D08u, gen::fn_sub_4C53F0_004c53f0);  // [RwStreamWrite]
                }
                // 0x004b8d10
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = sltiu(s2, 8);
                s0 = addiu(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b8d20
            charge(ctx, 2);
            v0 = s1;
        }
    } else {
        // 0x004b8cac
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b8d2c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004B8D50 sub_4B8D50 -- 276 bytes; frame 0x90: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B8D50 [uvAnimCreateIdentity]: Makes a 2-keyframe UV animation that holds the identity (used when a named
// animation is missing from the dictionary): RtAnimAnimationCreate on the linear scheme, the name and channel map in
// a fresh custom-data record, both keyframes from the identity matrix.
void sub_4B8D50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004b8d50
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 4;
    sd(ra, sp, 0x30);
    v1 = addiu(sp, 0x8C);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (v1 != 0) {
        for (;;) {
            // 0x004b8d70
            charge(ctx, 7);
            sb(zero, v1, 0);
            v0 = addiu(v0, -1);
            v1 = addiu(v1, 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b8d8c
    charge(ctx, 10);
    v0 = 0x3F800000;
    a1 = 1;
    mtc1(v0, f12);
    a2 = 2;
    a3 = addiu(sp, 0x8C);
    t0 = 0;
    jal(ctx, 0x4B8DA0u, gen::fn_sub_4B91C0_004b91c0);  // [uvAnimCreate]
    s1 = v0;
    if (s1 == 0) {
        // 0x004b8e48
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b8db4
        charge(ctx, 37);
        lw(t1, s1, 0);
        v0 = 0x20000;
        lw(s0, s1, 16);
        v0 = v0 | 0x3;
        lw(v1, sp, 0x4C);
        t0 = 0x3F800000;
        mtc1(zero, f12);
        a0 = s1;
        a2 = 0;
        a3 = addiu(sp, 0x40);
        lw(t1, t1, 8);
        a1 = s0;
        v0 = v1 | v0;
        sw(v0, sp, 0x4C);
        s2 = addu(s0, t1);
        sw(t0, sp, 0x68);
        sw(t0, sp, 0x54);
        sw(t0, sp, 0x40);
        sw(zero, sp, 0x50);
        sw(zero, sp, 0x48);
        sw(zero, sp, 0x44);
        sw(zero, sp, 0x64);
        sw(zero, sp, 0x60);
        sw(zero, sp, 0x58);
        sw(zero, sp, 0x78);
        sw(zero, sp, 0x74);
        link(ctx, 0x4B8E1Cu);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x70);
        call(ctx, gen::fn_sub_4B7C60_004b7c60);  // [uvAnimKeyFrameInit]
        v0 = 0x3F800000;
        a1 = s2;
        mtc1(v0, f12);
        a2 = s0;
        a0 = s1;
        a3 = addiu(sp, 0x40);
        jal(ctx, 0x4B8E38u, gen::fn_sub_4B7C60_004b7c60);  // [uvAnimKeyFrameInit]
        v0 = s1;
    }
    // 0x004b8e4c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x004B8E70 sub_4B8E70 -- 440 bytes; frame 0xA0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B8E70 [uvAnimMaterialStreamRead]: Material stream-read of RpUVAnim: the slot mask, and per set bit an
// animation name looked up in the current UV dictionary (refcount raised) or an identity animation, a new
// interpolator started on it; then the UV matrices.
void sub_4B8E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b8e70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    a1 = 1;
    sd(ra, sp, 0x60);
    a3 = 0;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    s0 = a0;
    s5 = addu(a2, v0);
    a2 = 0;
    jal(ctx, 0x4B8EA4u, gen::fn_sub_4C1600_004c1600);  // [RwStreamFindChunk]
    if (v0 != 0) {
        // 0x004b8ebc
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(sp, 0x9C);
        a2 = 4;
        jal(ctx, 0x4B8EC4u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
        if (v0 == 0) {
            backedge(ctx);
            goto L_004b8eb4;
        }
        // 0x004b8ed4
        charge(ctx, 2);
        s4 = 0;
        s2 = s5;
        for (;;) {
            // 0x004b8edc
            charge(ctx, 6);
            lw(v0, sp, 0x9C);
            v1 = 1;
            v1 = sllv(v1, s4);
            v0 = v0 & v1;
            if (v0 == 0) {
                // 0x004b8ef4
                charge(ctx, 1);
                goto L_004b8ef8;
            }
            // 0x004b8f1c
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(sp, 0x70);
            a2 = 32;
            jal(ctx, 0x4B8F24u, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
            if (v0 != 0) {
                // 0x004b8f90
                charge(ctx, 5);
                a0 = 0x780000;
                a0 = addiu(a0, -6944);  // &0x77E4E0
                jal(ctx, 0x4B8F94u, gen::fn_sub_4B7750_004b7750);  // [RtDictSchemaGetCurrentDict]
                if (v0 == 0) {
                    // 0x004b8fe8
                    charge(ctx, 4);
                    a0 = addiu(sp, 0x70);
                    jal(ctx, 0x4B8FE8u, gen::fn_sub_4B8D50_004b8d50);  // [uvAnimCreateIdentity]
                    s3 = v0;
                    backedge(ctx);
                } else {
                    // 0x004b8fa4
                    charge(ctx, 6);
                    a0 = v0;
                    a1 = addiu(sp, 0x70);
                    jal(ctx, 0x4B8FA8u, gen::fn_sub_4B77F0_004b77f0);  // [RtDictFindNamedEntry]
                    s3 = v0;
                    if (s3 == 0) {
                        // 0x004b8fd8
                        charge(ctx, 4);
                        a0 = addiu(sp, 0x70);
                        jal(ctx, 0x4B8FD8u, gen::fn_sub_4B8D50_004b8d50);  // [uvAnimCreateIdentity]
                        s3 = v0;
                        backedge(ctx);
                    } else {
                        // 0x004b8fbc
                        charge(ctx, 3);
                        a0 = s3;
                        jal(ctx, 0x4B8FBCu, gen::fn_sub_4B9350_004b9350);  // [RpUVAnimAddRef]
                    }
                }
                // 0x004b8fc8
                charge(ctx, 2);
                if (s3 == 0) {
                    // 0x004b8ff8
                    charge(ctx, 2);
                    v0 = 0;
                    backedge(ctx);
                } else {
                    // 0x004b8fd0
                    charge(ctx, 2);
                    v0 = s0;
                    backedge(ctx);
                }
            } else {
                // 0x004b8f34
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x004b8f38
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            // 0x004b8f40
            charge(ctx, 2);
            if (s3 == 0) {
                backedge(ctx);
            L_004b8ef8:
                charge(ctx, 4);
                s4 = addiu(s4, 1);
                v0 = sltiu(s4, 8);
                s2 = addiu(s2, 4);
                if (v0 == 0) {
                    // 0x004b8f08_7 (its only goto: the block written out here)
                    charge(ctx, 5);
                    a0 = s5;
                    jal(ctx, 0x4B8F08u, gen::fn_sub_4B8B10_004b8b10);  // [uvAnimMaterialUpdateMatrices]
                    if (v0 == 0) s0 = 0;
                    v0 = s0;
                    // 0x004b9004 (the shared epilogue, written out on this path)
                    charge(ctx, 9);
                    ld(ra, sp, 0x60);
                    lq(s5, sp, 0x50);
                    lq(s4, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0xA0);
                    return;
                }
                backedge(ctx);
                continue;
            }
            // 0x004b8f48
            charge(ctx, 9);
            a0 = s3;
            s1 = addiu(s2, 8);
            jal(ctx, 0x4B8F4Cu, gen::fn_sub_4B6DD0_004b6dd0);  // [RtAnimAnimationGetNumNodes]
            lw(v1, s3, 0);
            lw(a1, v1, 4);
            a0 = v0;
            jal(ctx, 0x4B8F5Cu, gen::fn_sub_4B6E10_004b6e10);  // [RtAnimInterpolatorCreate]
            sw(v0, s1, 0);
            if (v0 == 0) {
                goto L_004b8f80;
            }
            // 0x004b8f6c
            charge(ctx, 5);
            lw(a0, s1, 0);
            a1 = s3;
            jal(ctx, 0x4B8F70u, gen::fn_sub_4B6EC0_004b6ec0);  // [RtAnimInterpolatorSetCurrentAnim]
            if (v0 == 0) {
                goto L_004b8f80;
            }
            backedge(ctx);
            goto L_004b8ef8;
        }
        // 0x004b9000
        charge(ctx, 1);
        v0 = 0;
        // 0x004b9004 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xA0);
        return;
    }
L_004b8eb4:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b9004 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004b8f80:
    charge(ctx, 4);
    a0 = s3;
    jal(ctx, 0x4B8F80u, gen::fn_sub_4B92D0_004b92d0);  // [RpUVAnimDestroy]
    v0 = 0;
    // 0x004b9004 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004B9030 sub_4B9030 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B9030 [uvAnimMaterialStreamGetSize]: Material stream-size of RpUVAnim: 0 without animations, else 16 + 32 per
// used slot.
void sub_4B9030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b9030
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4B903Cu, gen::fn_sub_4B97F0_004b97f0);  // [RpUVAnimMaterialHasAnims]
    if (v0 == 0) {
        // 0x004b9088
        charge(ctx, 2);
        v0 = 0;
        ld(ra, sp, 0x10);
    } else {
        // 0x004b904c
        charge(ctx, 5);
        lw(v1, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
        v0 = 12;
        v0 = addiu(v0, 4);
        a1 = 0;
        a0 = addu(s0, v1);
        for (;;) {
            // 0x004b9060
            charge(ctx, 3);
            lw(v1, a0, 8);
            if (v1 != 0) {
                // 0x004b906c
                charge(ctx, 1);
                v0 = addiu(v0, 32);
            }
            // 0x004b9070
            charge(ctx, 4);
            a1 = addiu(a1, 1);
            v1 = sltiu(a1, 8);
            a0 = addiu(a0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b9080
        charge(ctx, 2);
        ld(ra, sp, 0x10);
    }
    // 0x004b9090 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B90A0 sub_4B90A0 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B90A0 [uvAnimCustomDataStreamRead]: Reads a UV animation's custom data: a record from the 0x7CE8B0 free list,
// the 32-byte name and the 8 channel ints; refcount 1.
void sub_4B90A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004b90a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x30000;
    sd(ra, sp, 0x20);
    a1 = v0 | 0x135;
    sq(s1, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4B90C4u);  // $ra = the return address
    lw(a0, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x004b90f8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b90d8
        charge(ctx, 6);
        a0 = s1;
        a1 = s0;
        a2 = 32;
        jal(ctx, 0x4B90E0u, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
        if (v0 != 0) {
            // 0x004b9100
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(s0, 32);
            a2 = 32;
            jal(ctx, 0x4B9108u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 != 0) {
                // 0x004b9120
                charge(ctx, 3);
                v1 = 1;
                v0 = s0;
                sw(v1, s0, 64);
            } else {
                // 0x004b9118
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x004b90f0
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004b912c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004B9140 sub_4B9140 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B9140 [uvAnimCustomDataStreamWrite]: Writes the name and the 8 channel ints of a UV animation's custom data.
void sub_4B9140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b9140
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 32;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x4B9160u, gen::fn_sub_4C53F0_004c53f0);  // [RwStreamWrite]
    if (v0 != 0) {
        // 0x004b9178
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(s1, 32);
        a2 = 32;
        jal(ctx, 0x4B9180u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x004b9170
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b9190 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004B91C0 sub_4B91C0 -- 264 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B91C0 [uvAnimCreate]: RpUVAnimCreate-like: an animation of the linear ($t0 = 0) or parametric ($t0 = 1) UV
// scheme ($a0 name, $a1 channels, $a2 keyframes, $a3 the channel map) with a custom-data record holding the name (32
// chars) and the channel map; refcount 1.
void sub_4B91C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004b91c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 1;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a3;
    s0 = 0;
    if (t0 == v0) {
        // 0x004b9220
        charge(ctx, 6);
        v0 = 0x780000;
        a1 = a2;
        lw(a0, v0, -6832);  // 0x77E550 the parametric UV scheme info
        a2 = 0;
        jal(ctx, 0x4B922Cu, gen::fn_sub_4B6840_004b6840);  // [RtAnimAnimationCreate]
        s0 = v0;
    } else {
        // 0x004b91f4
        charge(ctx, 2);
        if (t0 == 0) {
            // 0x004b9204
            charge(ctx, 7);
            v0 = 0x780000;
            a1 = a2;
            lw(a0, v0, -6880);  // 0x77E520 the linear UV scheme info
            a2 = 0;
            jal(ctx, 0x4B9210u, gen::fn_sub_4B6840_004b6840);  // [RtAnimAnimationCreate]
            s0 = v0;
        } else {
            // 0x004b91fc
            charge(ctx, 2);
        }
    }
    // 0x004b9238
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x004b92a4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b9240
        charge(ctx, 9);
        v0 = 0x30000;
        a1 = v0 | 0x135;
        v0 = 0x960000;
        lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4B9250u);  // $ra = the return address
        lw(a0, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
        call_ptr(ctx, jt);
        s4 = v0;
        if (s4 == 0) {
            // 0x004b929c
            charge(ctx, 2);
            s0 = 0;
            backedge(ctx);
        } else {
            // 0x004b9264
            charge(ctx, 12);
            a1 = s3;
            a0 = s4;
            a2 = 32;
            jal(ctx, 0x4B926Cu, gen::fn_strncpy_00524828);  // [strncpy]
            a2 = sll(s2, 2);
            a1 = s1;
            a0 = addiu(s4, 32);
            link(ctx, 0x4B9280u);  // $ra first: the delay slot below depends on it
            sb(zero, s4, 31);
            call(ctx, gen::fn_memcpy_00521250);  // [memcpy]
            v0 = 1;
            sw(v0, s4, 64);
            sw(s4, s0, 20);
        }
        // 0x004b9294
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004b92a8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004B92D0 sub_4B92D0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B92D0 [RpUVAnimDestroy]: Releases a UV animation: drops its custom data's refcount and, at zero, frees the
// record and destroys the animation. Returns 1.
void sub_4B92D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004b92d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, anim::kAnmCustomData);
    lw(v0, v1, 64);
    v0 = addiu(v0, -1);
    sw(v0, v1, 64);
    lw(v0, v1, 64);
    s0 = a0;
    if (v0 == 0) {
        // 0x004b930c
        charge(ctx, 7);
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C RwFreeListFree slot
        lw(a1, s0, anim::kAnmCustomData);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4B9318u);  // $ra = the return address
        lw(a0, gp, -17472);  // 0x7CE8B0 RpUVAnim: custom-data free list
        call_ptr(ctx, jt);
        v0 = 1;
        backedge(ctx);
    } else {
        // 0x004b92f8
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x004b92fc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004b9328
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4B9328u, gen::fn_sub_4B6980_004b6980);  // [RtAnimAnimationDestroy]
        backedge(ctx);
    }
    // 0x004b9304
    charge(ctx, 2);
    v0 = 1;
    // 0x004b9338
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004B9350 sub_4B9350 -- 24 bytes; leaf frame (no stack)
// sub_4B9350 [RpUVAnimAddRef]: Raises a UV animation's refcount (custom data +64). Returns the animation.
void sub_4B9350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004b9350
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a1, a0, anim::kAnmCustomData);
    v0 = a0;
    lw(v1, a1, 64);
    v1 = addiu(v1, 1);
    sw(v1, a1, 64);
}

// 0x004B9370 sub_4B9370 -- 872 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B9370 [RpUVAnimMaterialApplyInterpolators]: Applies a material's UV interpolators: resets both UV matrices to
// identity, then for every node of every slot whose channel is 0 or 1 builds the node's matrix (the linear or
// parametric apply inlined, or the scheme's apply callback) and multiplies it into that channel's matrix; finally
// sets the two matrices as the material's MatFX UV transforms. Returns the material.
void sub_4B9370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x004b9370
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    v0 = a0;
    sd(ra, sp, 0x90);
    a3 = 0;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    sw(a0, sp, 0xCC);
    v0 = addu(v0, v1);
    sw(v0, sp, 0xB0);
    a2 = v0;
    v0 = 0x20000;
    a0 = 0x3F800000;
    v1 = v0 | 0x3;
    for (;;) {
        // 0x004b93c4
        charge(ctx, 3);
        lw(a1, a2, 0);
        if (a1 != 0) {
            // 0x004b93d0
            charge(ctx, 16);
            sw(a0, a1, 40);
            sw(a0, a1, 20);
            sw(a0, a1, 0);
            sw(zero, a1, 16);
            sw(zero, a1, 8);
            sw(zero, a1, 4);
            sw(zero, a1, 36);
            sw(zero, a1, 32);
            sw(zero, a1, 24);
            sw(zero, a1, 56);
            sw(zero, a1, 52);
            sw(zero, a1, 48);
            lw(v0, a1, 12);
            v0 = v0 | v1;
            sw(v0, a1, 12);
        }
        // 0x004b9410
        charge(ctx, 4);
        a3 = addiu(a3, 1);
        v0 = sltiu(a3, 2);
        a2 = addiu(a2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b9420
    charge(ctx, 2);
    lw(s7, sp, 0xB0);
    s5 = 0;
    for (;;) {
        // 0x004b9428
        charge(ctx, 3);
        lw(s1, s7, 8);
        if (s1 != 0) {
            // 0x004b9434
            charge(ctx, 11);
            lw(v0, s1, 36);
            s3 = addiu(s1, 76);
            lw(v1, s1, 0);
            s4 = 0;
            lw(s0, s1, 60);
            sq(v0, sp, 0xA0);
            lw(v0, s1, 44);
            lw(v1, v1, 20);
            at = slt(0, v0);
            s6 = addiu(v1, 32);
            if (at != 0) {
                for (;;) {
                    // 0x004b9460
                    charge(ctx, 4);
                    lw(v0, s6, 0);
                    at = sltiu(v0, 2);
                    if (at != 0) {
                        // 0x004b9470
                        charge(ctx, 6);
                        v1 = sll(v0, 2);
                        lw(v0, sp, 0xB0);
                        v0 = addu(v0, v1);
                        lw(s2, v0, 0);
                        if (s2 != 0) {
                            // 0x004b9488
                            charge(ctx, 4);
                            v0 = 0x4B0000;
                            v0 = addiu(v0, 32640);  // &sub_4B7F80
                            if (v0 == s0) {
                                // 0x004b9514
                                charge(ctx, 33);
                                lwc1(f0, s3, 8);
                                v0 = addiu(sp, 0xD4);
                                a0 = addiu(sp, 0xD0);
                                swc1(f0, sp, 0xD0);
                                lwc1(f0, s3, 12);
                                swc1(f0, v0, 0);
                                v0 = addiu(sp, 0xD8);
                                sw(zero, v0, 0);
                                lwc1(f0, s3, 16);
                                v0 = addiu(sp, 0xE0);
                                swc1(f0, v0, 0);
                                lwc1(f0, s3, 20);
                                v0 = addiu(sp, 0xE4);
                                swc1(f0, v0, 0);
                                v0 = addiu(sp, 0xE8);
                                sw(zero, v0, 0);
                                v0 = addiu(sp, 0xF0);
                                sw(zero, v0, 0);
                                v0 = addiu(sp, 0xF4);
                                sw(zero, v0, 0);
                                v0 = addiu(sp, 0xF8);
                                sw(zero, v0, 0);
                                lwc1(f0, s3, 24);
                                v0 = addiu(sp, 0x100);
                                swc1(f0, v0, 0);
                                lwc1(f0, s3, 28);
                                v0 = addiu(sp, 0x104);
                                swc1(f0, v0, 0);
                                v0 = addiu(sp, 0x108);
                                link(ctx, 0x4B9588u);  // $ra first: the delay slot below depends on it
                                sw(zero, v0, 0);
                                call(ctx, gen::fn_sub_4C2F10_004c2f10);  // [RwMatrixUpdate]
                                backedge(ctx);
                            } else {
                                // 0x004b9498
                                charge(ctx, 4);
                                v0 = 0x4C0000;
                                v0 = addiu(v0, -32048);  // &sub_4B82D0
                                if (v0 == s0) {
                                    // 0x004b9598
                                    charge(ctx, 68);
                                    v0 = 0x780000;
                                    lwc1(f2, v0, -6784);  // 0x77E580
                                    v1 = 0x780000;
                                    lwc1(f1, v1, -6780);  // 0x77E584
                                    a0 = addiu(sp, 0xD0);
                                    fp = addiu(s3, 0x8);
                                    v0 = 0x780000;
                                    lwc1(f0, v0, -6776);  // 0x77E588
                                    swc1(f2, sp, 0x110);
                                    v0 = addiu(sp, 0x114);
                                    swc1(f1, v0, 0);
                                    v0 = addiu(sp, 0x118);
                                    swc1(f0, v0, 0);
                                    lwc1(f0, s3, 12);
                                    v0 = addiu(sp, 0xD4);
                                    swc1(f0, sp, 0xD0);
                                    lwc1(f0, s3, 20);
                                    swc1(f0, v0, 0);
                                    v0 = addiu(sp, 0xD8);
                                    sw(zero, v0, 0);
                                    v0 = addiu(sp, 0xE0);
                                    sw(zero, v0, 0);
                                    lwc1(f0, s3, 16);
                                    v0 = addiu(sp, 0xE4);
                                    swc1(f0, v0, 0);
                                    v0 = addiu(sp, 0xE8);
                                    sw(zero, v0, 0);
                                    v0 = addiu(sp, 0xF0);
                                    sw(zero, v0, 0);
                                    v0 = addiu(sp, 0xF4);
                                    sw(zero, v0, 0);
                                    v0 = addiu(sp, 0xF8);
                                    sw(zero, v0, 0);
                                    lwc1(f0, s3, 24);
                                    v0 = addiu(sp, 0x100);
                                    swc1(f0, v0, 0);
                                    lwc1(f0, s3, 28);
                                    v0 = addiu(sp, 0x104);
                                    swc1(f0, v0, 0);
                                    v0 = addiu(sp, 0x108);
                                    link(ctx, 0x4B9638u);  // $ra first: the delay slot below depends on it
                                    sw(zero, v0, 0);
                                    call(ctx, gen::fn_sub_4C2F10_004c2f10);  // [RwMatrixUpdate]
                                    a1 = 0x7C0000;
                                    a0 = addiu(sp, 0xD0);
                                    a1 = addiu(a1, -13368);  // &0x7BCBC8
                                    a2 = 2;
                                    jal(ctx, 0x4B964Cu, gen::fn_sub_4C35D0_004c35d0);  // [RwMatrixTranslate]
                                    lwc1(f1, fp, 0x0);
                                    v0 = 0x40490000;
                                    v1 = v0 | 0xFDB;
                                    a0 = addiu(sp, 0xD0);
                                    mtc1(v1, f2);
                                    v0 = 0x43340000;
                                    mtc1(v0, f0);
                                    a1 = addiu(sp, 0x110);
                                    a2 = 2;
                                    div_s(f1, f1, f2);
                                    mul_s(f12, f0, f1);
                                    jal(ctx, 0x4B9684u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                                    a1 = 0x7C0000;
                                    a0 = addiu(sp, 0xD0);
                                    a1 = addiu(a1, -13352);  // &0x7BCBD8
                                    a2 = 2;
                                    jal(ctx, 0x4B9698u, gen::fn_sub_4C35D0_004c35d0);  // [RwMatrixTranslate]
                                    backedge(ctx);
                                } else {
                                    // 0x004b94a8
                                    charge(ctx, 4);
                                    a0 = addiu(sp, 0xD0);
                                    a1 = s3;
                                    jalr(ctx, 0x4B94ACu, s0.u());
                                }
                            }
                            // 0x004b94b8
                            charge(ctx, 6);
                            a0 = s2;
                            a1 = addiu(sp, 0xD0);
                            a2 = 1;
                            jal(ctx, 0x4B94C0u, gen::fn_sub_4C3760_004c3760);
                            lq(v0, sp, 0xA0);
                            s3 = addu(s3, v0);
                        }
                    }
                    // 0x004b94d0
                    charge(ctx, 5);
                    lw(v0, s1, 44);
                    s4 = addiu(s4, 1);
                    v0 = slt(s4, v0);
                    s6 = addiu(s6, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b94e4
                charge(ctx, 1);
            }
        }
        // 0x004b94e8
        charge(ctx, 4);
        s5 = addiu(s5, 1);
        v0 = slti(s5, 8);
        s7 = addiu(s7, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b94f8
    charge(ctx, 7);
    lw(v0, sp, 0xB0);
    lw(a1, v0, 0);
    lw(a2, v0, 4);
    link(ctx, 0x4B9504u);  // $ra first: the delay slot below depends on it
    lw(a0, sp, 0xCC);
    call(ctx, gen::fn_sub_4699B0_004699b0);  // [RpMatFXMaterialSetUVTransformMatrices]
    lw(v0, sp, 0xCC);
    // 0x004b96a8
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
    sp = addiu(sp, 0x120);
}

// 0x004B96E0 sub_4B96E0 -- 8 bytes; leaf frame (no stack)
// sub_4B96E0 [uvAnimGetName]: The custom data (the name comes first) of a UV animation.
void sub_4B96E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004b96e0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, anim::kAnmCustomData);
}

// 0x004B96F0 sub_4B96F0 -- 188 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4B96F0 [RpUVAnimMaterialSetAnim]: Puts animation $a1 in slot $a2 of material $a0: a new interpolator started on
// it, the UV matrices updated, the animation's refcount raised. Returns the material or 0.
void sub_4B96F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b96f0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = sll(a2, 2);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    a0 = s1;
    s0 = addu(s2, v1);
    v0 = addu(s0, v0);
    s3 = addiu(v0, 8);
    jal(ctx, 0x4B9724u, gen::fn_sub_4B6DD0_004b6dd0);  // [RtAnimAnimationGetNumNodes]
    lw(v1, s1, anim::kAnmInfo);
    lw(a1, v1, anim::kInfoInterpFrameSize);
    a0 = v0;
    jal(ctx, 0x4B9734u, gen::fn_sub_4B6E10_004b6e10);  // [RtAnimInterpolatorCreate]
    sw(v0, s3, 0);
    lw(a0, s3, 0);
    if (a0 == 0) {
        // 0x004b977c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b974c
        charge(ctx, 6);
        a1 = s1;
        jal(ctx, 0x4B974Cu, gen::fn_sub_4B6EC0_004b6ec0);  // [RtAnimInterpolatorSetCurrentAnim]
        a0 = s0;
        jal(ctx, 0x4B9754u, gen::fn_sub_4B8B10_004b8b10);  // [uvAnimMaterialUpdateMatrices]
        if (v0 == 0) {
            // 0x004b9784
            charge(ctx, 3);
            link(ctx, 0x4B9784u);  // $ra first: the delay slot below depends on it
            lw(a0, s3, 0);
            call(ctx, gen::fn_sub_4B6EB0_004b6eb0);  // [RtAnimInterpolatorDestroy]
            v0 = 0;
        } else {
            // 0x004b9764
            charge(ctx, 6);
            lw(a0, s1, anim::kAnmCustomData);
            v0 = s2;
            lw(v1, a0, 64);
            v1 = addiu(v1, 1);
            sw(v1, a0, 64);
        }
    }
    // 0x004b9790 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004B97B0 sub_4B97B0 -- 24 bytes; leaf frame (no stack)
// sub_4B97B0 [RpUVAnimMaterialGetInterpolator]: The interpolator in slot $a1 of material $a0's UV extension.
void sub_4B97B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004b97b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    v0 = sll(a1, 2);
    v1 = addu(a0, v1);
    v0 = addu(v0, v1);
    lw(v0, v0, 8);
}

// 0x004B97D0 sub_4B97D0 -- 28 bytes; leaf frame (no stack)
// sub_4B97D0 [uvAnimMaterialSetInterpolator]: Sets slot $a2 of material $a0's UV extension to $a1. Returns $a0.
void sub_4B97D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004b97d0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a2, 2);
    v0 = a0;
    lw(a2, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    a0 = addu(a0, a2);
    v1 = addu(v1, a0);
    sw(a1, v1, 8);
}

// 0x004B97F0 sub_4B97F0 -- 68 bytes; leaf frame (no stack)
// sub_4B97F0 [RpUVAnimMaterialHasAnims]: 1 when any of the material's eight UV slots holds an interpolator.
void sub_4B97F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004b97f0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -17468);  // 0x7CE8B4 RpUVAnim: material extension offset
    a1 = 0;
    v1 = addu(a0, v0);
    for (;;) {
        // 0x004b97fc
        charge(ctx, 5);
        lw(v0, v1, 8);
        v0 = sltu(0, v0);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            goto L_004b9810_2;
        }
        // 0x004b9818
        charge(ctx, 4);
        a1 = addiu(a1, 1);
        v0 = sltiu(a1, 8);
        v1 = addiu(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b9828
    charge(ctx, 1);
    v0 = 0;
    // 0x004b982c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004b9810_2:
    charge(ctx, 2);
    v0 = 1;
    // 0x004b982c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004F7300 sub_4F7300 -- 368 bytes; frame 0x10
// sub_4F7300 [cmpKeyFloatToHalf]: Packs a float into the scheme's 16-bit format (sign, 5-bit exponent biased by 112,
// 11-bit mantissa) with rounding: values above 1 are clamped to the largest, below 2^-15 to zero.
void sub_4F7300(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x004f7300
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    swc1(f12, sp, 0xC);
    lw(v0, sp, 0xC);
    v0 = v0 & 0xFFF;
    v0 = slti(v0, 2048);
    if (v0 == 0) {
        // 0x004f731c
        charge(ctx, 7);
        lw(v1, sp, 0xC);
        v0 = 0x7F800000;
        v0 = v1 & v0;
        a1 = sra(v0, 23);
        at = slti(a1, 13);
        if (at == 0) {
            // 0x004f7338
            charge(ctx, 3);
            v0 = slti(a1, 254);
            if (v0 == 0) {
                // 0x004f7344
                charge(ctx, 6);
                lw(a0, sp, 0xC);
                v0 = 0x7F0000;
                v1 = v0 | 0xF000;  // &0x7FF000
                v0 = a0 & v1;
                if (v0 != v1) {
                    goto L_004f735c;
                }
                goto L_004f7388;
            }
        L_004f735c:
            charge(ctx, 11);
            lw(a0, sp, 0xC);
            v0 = addiu(a1, -12);
            v1 = lui(0x8000);
            v0 = sll(v0, 23);
            lwc1(f1, sp, 0xC);
            v1 = a0 & v1;
            v0 = v1 | v0;
            sw(v0, sp, 0x8);
            lwc1(f0, sp, 0x8);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xC);
        }
    }
L_004f7388:
    charge(ctx, 12);
    lw(a0, sp, 0xC);
    v1 = si(-4096);
    at = 0x3F800000;
    v0 = 0x7F800000;
    at = at | 0x1;
    v1 = a0 & v1;
    sw(v1, sp, 0xC);
    lw(v1, sp, 0xC);
    v0 = v1 & v0;
    at = slt(v0, at);
    if (at == 0) {
        // 0x004f7430
        charge(ctx, 8);
        lw(a0, sp, 0xC);
        v1 = lui(0x8000);
        v0 = 0x7FFF0000;
        v0 = v0 | 0xF000;
        v1 = a0 & v1;
        v0 = v1 | v0;
        sw(v0, sp, 0xC);
        backedge(ctx);
    }
    // 0x004f73b8
    charge(ctx, 7);
    lw(a0, sp, 0xC);
    v1 = 0x7F800000;
    v0 = 0x38000000;
    v1 = a0 & v1;
    v0 = slt(v1, v0);
    if (v0 != 0) {
        // 0x004f7450
        charge(ctx, 5);
        lw(v1, sp, 0xC);
        v0 = lui(0x8000);
        v0 = v1 & v0;
        sw(v0, sp, 0xC);
        backedge(ctx);
    }
    // 0x004f73d4
    charge(ctx, 8);
    lw(v1, sp, 0xC);
    lw(v0, sp, 0xC);
    v1 = sra(v1, 16);
    a0 = v1 & 0x8000;
    v1 = dsll32(v0, 1);
    v1 = dsrl32(v1, 1);
    v0 = a0 & 0xFFFF;
    if (v1 == 0) {
        // 0x004f7464
        charge(ctx, 1);
        sp = addiu(sp, 0x10);
    } else {
        // 0x004f73f4
        charge(ctx, 15);
        lw(a0, sp, 0xC);
        lw(v1, sp, 0xC);
        a0 = sra(a0, 23);
        a0 = a0 & 0xFF;
        v1 = sra(v1, 12);
        a0 = addiu(a0, -112);
        v1 = v1 & 0x7FF;
        a0 = sll(a0, 11);
        a0 = a0 & 0xFFFF;
        v0 = v0 | a0;
        v0 = v0 & 0xFFFF;
        v0 = v0 | v1;
        v0 = v0 & 0xFFFF;
        sp = addiu(sp, 0x10);
    }
    // 0x004f7468 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004F7470 sub_4F7470 -- 240 bytes; leaf frame (no stack)
// sub_4F7470 [cmpKeyFrameApply]: Apply callback (scheme id 2): writes an interpolated frame's quaternion as a
// rotation matrix and its translation into matrix $a0 (flags 3 = orthonormal) -- the same body as the standard
// scheme's.
void sub_4F7470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x004f7470
    enter(ctx, 60);  // entry check point + this block's cycles
    lwc1(f8, a1, anim::kIfQuat);
    v1 = 0x40000000;
    lwc1(f7, a1, 12);
    lwc1(f6, a1, 16);
    mtc1(v1, f5);
    lwc1(f0, a1, 20);
    v1 = 0x3F800000;
    mul_s(f12, f8, f8);
    mul_s(f2, f7, f7);
    mul_s(f1, f6, f6);
    mtc1(v1, f4);
    mtc1(zero, f3);
    mul_s(f11, f7, f6);
    v1 = 3;
    mul_s(f10, f6, f8);
    mul_s(f9, f8, f7);
    mul_s(f6, f0, f6);
    mul_s(f8, f0, f8);
    mul_s(f7, f0, f7);
    add_s(f0, f2, f1);
    adda_s(f3, f4);
    msub_s(f0, f5, f0);
    swc1(f0, a0, 0);
    add_s(f1, f12, f1);
    add_s(f0, f12, f2);
    adda_s(f3, f4);
    msub_s(f2, f5, f1);
    adda_s(f3, f4);
    add_s(f3, f9, f6);
    mul_s(f3, f5, f3);
    sub_s(f4, f10, f7);
    sub_s(f1, f9, f6);
    swc1(f3, a0, 4);
    mul_s(f3, f5, f1);
    mul_s(f4, f5, f4);
    swc1(f4, a0, 8);
    swc1(f3, a0, 16);
    add_s(f3, f11, f8);
    add_s(f1, f10, f7);
    swc1(f2, a0, 20);
    mul_s(f2, f5, f1);
    sub_s(f1, f11, f8);
    mul_s(f3, f5, f3);
    swc1(f3, a0, 24);
    mul_s(f1, f5, f1);
    swc1(f2, a0, 32);
    msub_s(f0, f5, f0);
    swc1(f1, a0, 36);
    swc1(f0, a0, 40);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
    sw(zero, a0, 56);
    sw(v1, a0, 12);
    lwc1(f0, a1, anim::kIfTrans);
    swc1(f0, a0, 48);
    lwc1(f0, a1, 28);
    swc1(f0, a0, 52);
    lwc1(f0, a1, 32);
    swc1(f0, a0, 56);
}

// 0x004F7560 sub_4F7560 -- 2516 bytes; frame 0x60: f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_4F7560 [cmpKeyFrameInterpolate]: Interpolate callback: decompresses the two keyframes (16-bit quaternion and
// translation; the translation scaled and offset by the animation's custom data) and writes the slerp of the
// quaternions (nlerp below the angle threshold) and the lerp of the translations at t = $f12 into frame $a0.
void sub_4F7560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004f7560
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lhu(t1, a1, anim::kKfQuat);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x5C);
    if (v1 != 0) {
        // 0x004f7588
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x5C);
    }
    // 0x004f75ac
    charge(ctx, 6);
    lhu(t1, a1, 10);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x58);
    if (v1 != 0) {
        // 0x004f75c4
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x58);
    }
    // 0x004f75e8
    charge(ctx, 6);
    lhu(t1, a1, 12);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x54);
    if (v1 != 0) {
        // 0x004f7600
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x54);
    }
    // 0x004f7624
    charge(ctx, 6);
    lhu(t1, a1, 14);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x50);
    if (v1 != 0) {
        // 0x004f763c
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x50);
    }
    // 0x004f7660
    charge(ctx, 6);
    lhu(t1, a1, 16);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x4C);
    if (v1 != 0) {
        // 0x004f7678
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x4C);
    }
    // 0x004f769c
    charge(ctx, 6);
    lhu(t1, a1, 18);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x48);
    if (v1 != 0) {
        // 0x004f76b4
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x48);
    }
    // 0x004f76d8
    charge(ctx, 6);
    lhu(t1, a1, 20);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x44);
    if (v1 != 0) {
        // 0x004f76f0
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x44);
    }
    // 0x004f7714
    charge(ctx, 6);
    lhu(t1, a2, anim::kKfQuat);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x40);
    if (v1 != 0) {
        // 0x004f772c
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x40);
    }
    // 0x004f7750
    charge(ctx, 7);
    lhu(t1, a2, 10);
    lwc1(f4, sp, 0x40);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x3C);
    if (v1 != 0) {
        // 0x004f776c
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x3C);
    }
    // 0x004f7790
    charge(ctx, 7);
    lhu(t1, a2, 12);
    lwc1(f5, sp, 0x3C);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x38);
    if (v1 != 0) {
        // 0x004f77ac
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x38);
    }
    // 0x004f77d0
    charge(ctx, 7);
    lhu(t1, a2, 14);
    lwc1(f6, sp, 0x38);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x34);
    if (v1 != 0) {
        // 0x004f77ec
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x34);
    }
    // 0x004f7810
    charge(ctx, 7);
    lhu(t1, a2, 16);
    lwc1(f7, sp, 0x34);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x30);
    if (v1 != 0) {
        // 0x004f782c
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x30);
    }
    // 0x004f7850
    charge(ctx, 6);
    lhu(t1, a2, 18);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x2C);
    if (v1 != 0) {
        // 0x004f7868
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x2C);
    }
    // 0x004f788c
    charge(ctx, 6);
    lhu(t1, a2, 20);
    t0 = t1 & 0x8000;
    v1 = t1 & 0x7FFF;
    t2 = sll(t0, 16);
    sw(t2, sp, 0x28);
    if (v1 != 0) {
        // 0x004f78a4
        charge(ctx, 9);
        v1 = t1 & 0x7FF;
        t0 = t1 & 0x7800;
        t1 = sll(t0, 12);
        v1 = sll(v1, 12);
        t0 = 0x38000000;
        t0 = addu(t1, t0);
        t0 = t2 | t0;
        v1 = t0 | v1;
        sw(v1, sp, 0x28);
    }
    // 0x004f78c8
    charge(ctx, 62);
    lwc1(f10, a1, anim::kKfTime);
    lwc1(f8, a2, anim::kKfTime);
    lwc1(f17, sp, 0x58);
    lwc1(f0, sp, 0x3C);
    lwc1(f18, sp, 0x5C);
    lwc1(f1, sp, 0x40);
    sub_s(f9, f12, f10);
    sub_s(f10, f8, f10);
    div_s(f9, f9, f10);
    mula_s(f17, f0);
    lwc1(f14, sp, 0x30);
    lwc1(f15, sp, 0x4C);
    lwc1(f19, sp, 0x54);
    lwc1(f2, sp, 0x38);
    madda_s(f18, f1);
    lwc1(f20, sp, 0x50);
    lwc1(f3, sp, 0x34);
    lwc1(f12, sp, 0x2C);
    lwc1(f13, sp, 0x48);
    madda_s(f19, f2);
    lwc1(f8, sp, 0x28);
    lwc1(f11, sp, 0x44);
    sub_s(f14, f14, f15);
    mtc1(zero, f16);
    madd_s(f10, f20, f3);
    adda_s(f16, f15);
    madd_s(f14, f9, f14);
    sub_s(f12, f12, f13);
    adda_s(f16, f13);
    madd_s(f12, f9, f12);
    swc1(f14, a0, anim::kIfTrans);
    sub_s(f8, f8, f11);
    adda_s(f16, f11);
    swc1(f12, a0, 28);
    madd_s(f8, f9, f8);
    swc1(f8, a0, 32);
    lwc1(f11, a0, anim::kIfTrans);
    lwc1(f8, a3, 12);
    c_lt_s(f10, f16);
    mul_s(f8, f11, f8);
    swc1(f8, a0, anim::kIfTrans);
    lwc1(f11, a0, 28);
    lwc1(f8, a3, 16);
    mul_s(f8, f11, f8);
    swc1(f8, a0, 28);
    lwc1(f11, a0, 32);
    lwc1(f8, a3, 20);
    mul_s(f8, f11, f8);
    swc1(f8, a0, 32);
    lwc1(f11, a0, anim::kIfTrans);
    lwc1(f8, a3, 0);
    add_s(f8, f11, f8);
    swc1(f8, a0, anim::kIfTrans);
    lwc1(f11, a3, 4);
    lwc1(f8, a0, 28);
    add_s(f8, f8, f11);
    swc1(f8, a0, 28);
    lwc1(f11, a3, 8);
    lwc1(f8, a0, 32);
    add_s(f8, f8, f11);
    swc1(f8, a0, 32);
    if (cond(ctx)) {
        // 0x004f79c0
        charge(ctx, 5);
        neg_s(f4, f1);
        neg_s(f5, f0);
        neg_s(f6, f2);
        neg_s(f7, f3);
        neg_s(f10, f10);
    }
    // 0x004f79d4
    charge(ctx, 9);
    a1 = 0x3F800000;
    v1 = 0x3F7F0000;
    mtc1(a1, f2);
    v1 = v1 | 0xBE77;
    mtc1(v1, f0);
    c_lt_s(f10, f0);
    sub_s(f8, f2, f9);
    if (cond(ctx)) {
        // 0x004f79f8
        charge(ctx, 8);
        swc1(f10, sp, 0x24);
        at = 0x3F800000;
        lw(a1, sp, 0x24);
        v1 = dsll32(a1, 1);
        v1 = dsrl32(v1, 1);
        at = slt(v1, at);
        if (at == 0) {
            // 0x004f7ca4
            charge(ctx, 2);
            if (i64(a1) <= 0) {
                // 0x004f7cb8
                charge(ctx, 5);
                v1 = 0x40490000;
                v1 = v1 | 0xFDB;
                mtc1(v1, f17);
                backedge(ctx);
            } else {
                // 0x004f7cac
                charge(ctx, 3);
                mtc1(zero, f17);
                backedge(ctx);
            }
        L_004f7b4c:
            charge(ctx, 1);
            v1 = 0x2F2E0000;
        } else {
            // 0x004f7a18
            charge(ctx, 4);
            at = 0x3F000000;
            at = slt(v1, at);
            if (at == 0) {
                // 0x004f7ccc
                charge(ctx, 2);
                if (i64(a1) < 0) {
                    // 0x004f7e00
                    charge(ctx, 72);
                    add_s(f0, f2, f10);
                    a3 = 0x3F000000;
                    a1 = 0x38110000;
                    v1 = 0x3A4F0000;
                    a2 = a1 | 0xEF08;
                    t0 = v1 | 0x7F04;
                    a1 = lui(0xBD24);
                    v1 = 0x3E4E0000;
                    mtc1(a3, f1);
                    t3 = a1 | 0x1146;
                    mtc1(t0, f20);
                    mul_s(f22, f1, f0);
                    a3 = v1 | 0xAA8;
                    v1 = lui(0xBEA6);
                    t2 = v1 | 0xB090;
                    v1 = 0x3E2A0000;
                    mtc1(zero, f19);
                    mtc1(a2, f21);
                    adda_s(f19, f20);
                    a2 = v1 | 0xAAAB;
                    v1 = 0x3D9D0000;
                    a1 = v1 | 0xC62E;
                    v1 = lui(0xBF30);
                    t1 = v1 | 0x3361;
                    v1 = 0x40010000;
                    t0 = v1 | 0x572D;
                    mtc1(a1, f14);
                    v1 = lui(0xC019);
                    mtc1(a3, f17);
                    mtc1(t3, f18);
                    a1 = 0x40000000;
                    a3 = v1 | 0xD139;
                    madd_s(f20, f21, f22);
                    v1 = 0x33A20000;
                    adda_s(f19, f18);
                    madd_s(f18, f22, f20);
                    adda_s(f19, f17);
                    mtc1(a2, f15);
                    mtc1(t2, f16);
                    a2 = v1 | 0x2168;
                    madd_s(f17, f22, f18);
                    v1 = 0x40490000;
                    adda_s(f19, f16);
                    v1 = v1 | 0xFDA;
                    madd_s(f16, f22, f17);
                    adda_s(f19, f15);
                    madd_s(f15, f22, f16);
                    mtc1(t1, f13);
                    mtc1(t0, f12);
                    adda_s(f19, f13);
                    madd_s(f13, f14, f22);
                    adda_s(f19, f12);
                    mtc1(a3, f11);
                    madd_s(f12, f22, f13);
                    adda_s(f19, f11);
                    madd_s(f11, f22, f12);
                    adda_s(f19, f2);
                    mul_s(f15, f22, f15);
                    mtc1(v1, f1);
                    madd_s(f2, f22, f11);
                    adda_s(f19, f1);
                    sqrt_s(f0, f22);
                    div_s(f1, f15, f2);
                    mul_s(f1, f1, f0);
                    mtc1(a2, f10);
                    mtc1(a1, f3);
                    sub_s(f1, f1, f10);
                    add_s(f0, f0, f1);
                    msub_s(f17, f3, f0);
                    backedge(ctx);
                } else {
                    // 0x004f7cd4
                    charge(ctx, 75);
                    sub_s(f0, f2, f10);
                    a3 = 0x3F000000;
                    a1 = 0x38110000;
                    v1 = si(-4096);
                    a2 = a1 | 0xEF08;
                    a1 = 0x3A4F0000;
                    mtc1(a3, f1);
                    t5 = a1 | 0x7F04;
                    a1 = lui(0xBD24);
                    mul_s(f1, f1, f0);
                    a3 = a1 | 0x1146;
                    a1 = 0x3E4E0000;
                    t4 = a1 | 0xAA8;
                    a1 = 0x3E2A0000;
                    t2 = a1 | 0xAAAB;
                    mtc1(a2, f20);
                    a1 = lui(0xBF30);
                    sqrt_s(f3, f1);
                    t0 = a1 | 0x3361;
                    a2 = lui(0xBEA6);
                    a1 = 0x40010000;
                    t3 = a2 | 0xB090;
                    a2 = 0x3D9D0000;
                    t1 = a2 | 0xC62E;
                    mtc1(a3, f18);
                    mtc1(t5, f19);
                    a3 = a1 | 0x572D;
                    mtc1(zero, f0);
                    a1 = lui(0xC019);
                    a2 = a1 | 0xD139;
                    adda_s(f0, f19);
                    a1 = 0x40000000;
                    madd_s(f19, f20, f1);
                    adda_s(f0, f18);
                    mtc1(t4, f17);
                    madd_s(f18, f1, f19);
                    adda_s(f0, f17);
                    mtc1(t3, f11);
                    madd_s(f17, f1, f18);
                    adda_s(f0, f11);
                    mtc1(t2, f16);
                    madd_s(f17, f1, f17);
                    adda_s(f0, f16);
                    madd_s(f16, f1, f17);
                    mtc1(t0, f14);
                    mtc1(t1, f15);
                    adda_s(f0, f14);
                    mtc1(a3, f13);
                    madd_s(f14, f15, f1);
                    adda_s(f0, f13);
                    mtc1(a2, f12);
                    madd_s(f13, f1, f14);
                    adda_s(f0, f12);
                    madd_s(f12, f1, f13);
                    adda_s(f0, f2);
                    madd_s(f2, f1, f12);
                    mul_s(f16, f1, f16);
                    div_s(f12, f16, f2);
                    mtc1(a1, f10);
                    swc1(f3, sp, 0x20);
                    lw(a1, sp, 0x20);
                    adda_s(f0, f1);
                    v1 = a1 & v1;
                    sw(v1, sp, 0x1C);
                    lwc1(f11, sp, 0x1C);
                    add_s(f1, f3, f11);
                    msub_s(f2, f11, f11);
                    div_s(f1, f2, f1);
                    adda_s(f0, f1);
                    madd_s(f0, f12, f3);
                    add_s(f0, f11, f0);
                    mul_s(f17, f10, f0);
                    backedge(ctx);
                }
                goto L_004f7b4c;
            }
            // 0x004f7a28
            charge(ctx, 5);
            at = 0x23000000;
            at = at | 0x1;
            at = slt(v1, at);
            if (at == 0) {
                // 0x004f7a50
                charge(ctx, 63);
                v1 = 0x38110000;
                a1 = v1 | 0xEF08;
                v1 = 0x3A4F0000;
                t0 = v1 | 0x7F04;
                v1 = lui(0xBD24);
                a2 = v1 | 0x1146;
                v1 = 0x3E4E0000;
                a3 = v1 | 0xAA8;
                mul_s(f21, f10, f10);
                v1 = lui(0xBEA6);
                mtc1(a1, f20);
                mtc1(t0, f19);
                a1 = v1 | 0xB090;
                mtc1(zero, f18);
                v1 = 0x3E2A0000;
                mtc1(a2, f17);
                adda_s(f18, f19);
                a2 = v1 | 0xAAAB;
                madd_s(f19, f20, f21);
                v1 = 0x3D9D0000;
                mtc1(a1, f15);
                adda_s(f18, f17);
                a1 = v1 | 0xC62E;
                v1 = lui(0xBF30);
                v1 = v1 | 0x3361;
                mtc1(v1, f12);
                mtc1(a3, f16);
                madd_s(f17, f21, f19);
                v1 = 0x40010000;
                adda_s(f18, f16);
                madd_s(f16, f21, f17);
                adda_s(f18, f15);
                mtc1(a1, f13);
                mtc1(a2, f14);
                a1 = v1 | 0x572D;
                madd_s(f15, f21, f16);
                v1 = lui(0xC019);
                adda_s(f18, f14);
                v1 = v1 | 0xD139;
                madd_s(f14, f21, f15);
                adda_s(f18, f12);
                mtc1(v1, f3);
                mtc1(a1, f11);
                madd_s(f12, f13, f21);
                v1 = 0x33A20000;
                a1 = v1 | 0x2168;
                adda_s(f18, f11);
                v1 = 0x3FC90000;
                madd_s(f11, f21, f12);
                v1 = v1 | 0xFDA;
                adda_s(f18, f3);
                madd_s(f3, f21, f11);
                adda_s(f18, f2);
                mul_s(f14, f21, f14);
                mtc1(a1, f1);
                madd_s(f2, f21, f3);
                adda_s(f18, f1);
                div_s(f1, f14, f2);
                msub_s(f1, f10, f1);
                sub_s(f1, f10, f1);
                mtc1(v1, f0);
                sub_s(f17, f0, f1);
                goto L_004f7b4c;
            }
            // 0x004f7a3c
            charge(ctx, 5);
            v1 = 0x3FC90000;
            v1 = v1 | 0xFDB;
            mtc1(v1, f17);
            v1 = 0x2F2E0000;
        }
        // 0x004f7b50
        charge(ctx, 68);
        a2 = v1 | 0xC9D3;
        mul_s(f11, f17, f17);
        v1 = lui(0xB2D7);
        t0 = v1 | 0x2F34;
        v1 = 0x36380000;
        a1 = v1 | 0xEF1B;
        v1 = lui(0xB950);
        a3 = v1 | 0xD01;
        mtc1(t0, f16);
        v1 = 0x3C080000;
        mtc1(zero, f0);
        mtc1(a2, f1);
        adda_s(f0, f16);
        a2 = v1 | 0x8889;
        mtc1(a1, f15);
        v1 = lui(0xBE2A);
        madd_s(f10, f1, f11);
        a1 = v1 | 0xAAAB;
        adda_s(f0, f15);
        v1 = 0x3F800000;
        mtc1(a3, f14);
        madd_s(f10, f11, f10);
        adda_s(f0, f14);
        mtc1(a2, f13);
        madd_s(f10, f11, f10);
        adda_s(f0, f13);
        mtc1(a1, f12);
        madd_s(f10, f11, f10);
        adda_s(f0, f12);
        madd_s(f10, f11, f10);
        mul_s(f3, f11, f17);
        adda_s(f0, f17);
        madd_s(f3, f3, f10);
        mtc1(v1, f2);
        mul_s(f10, f8, f17);
        div_s(f11, f2, f3);
        mul_s(f3, f9, f17);
        mul_s(f9, f10, f10);
        adda_s(f0, f16);
        madd_s(f2, f1, f9);
        adda_s(f0, f15);
        madd_s(f2, f9, f2);
        adda_s(f0, f14);
        madd_s(f2, f9, f2);
        adda_s(f0, f13);
        madd_s(f2, f9, f2);
        adda_s(f0, f12);
        madd_s(f8, f9, f2);
        mul_s(f2, f9, f10);
        adda_s(f0, f10);
        madd_s(f2, f2, f8);
        mul_s(f8, f2, f11);
        mul_s(f2, f3, f3);
        adda_s(f0, f16);
        madd_s(f1, f1, f2);
        adda_s(f0, f15);
        madd_s(f1, f2, f1);
        adda_s(f0, f14);
        madd_s(f1, f2, f1);
        adda_s(f0, f13);
        madd_s(f1, f2, f1);
        adda_s(f0, f12);
        madd_s(f1, f2, f1);
        adda_s(f0, f3);
        mul_s(f0, f2, f3);
        madd_s(f0, f0, f1);
        mul_s(f9, f0, f11);
    }
    // 0x004f7c60
    charge(ctx, 17);
    lwc1(f3, sp, 0x5C);
    mula_s(f9, f4);
    lwc1(f2, sp, 0x58);
    lwc1(f1, sp, 0x54);
    lwc1(f0, sp, 0x50);
    madd_s(f3, f8, f3);
    mula_s(f9, f5);
    madd_s(f2, f8, f2);
    mula_s(f9, f6);
    swc1(f3, a0, 8);
    madd_s(f1, f8, f1);
    swc1(f2, a0, 12);
    mula_s(f9, f7);
    madd_s(f0, f8, f0);
    swc1(f1, a0, 16);
    swc1(f0, a0, 20);
    // 0x004f7f20
    charge(ctx, 5);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004F7F40 sub_4F7F40 -- 1564 bytes; frame 0x10
// sub_4F7F40 [cmpKeyFrameBlend]: Blend callback: slerps the quaternions and lerps the translations of two
// interpolated frames with weight $f12.
void sub_4F7F40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18};
    // 0x004f7f40
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f4, a1, 12);
    lwc1(f1, a2, 12);
    lwc1(f6, a1, anim::kIfQuat);
    lwc1(f5, a2, anim::kIfQuat);
    lwc1(f2, a1, anim::kIfTrans);
    lwc1(f0, a2, anim::kIfTrans);
    lwc1(f8, a1, 16);
    mula_s(f4, f1);
    lwc1(f7, a2, 16);
    madda_s(f6, f5);
    lwc1(f10, a1, 20);
    lwc1(f9, a2, 20);
    sub_s(f0, f0, f2);
    madda_s(f8, f7);
    mtc1(zero, f3);
    madd_s(f1, f10, f9);
    adda_s(f3, f2);
    madd_s(f0, f12, f0);
    swc1(f0, a0, anim::kIfTrans);
    lwc1(f2, a1, 28);
    lwc1(f0, a2, 28);
    c_lt_s(f1, f3);
    adda_s(f3, f2);
    sub_s(f0, f0, f2);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 28);
    lwc1(f2, a1, 32);
    lwc1(f0, a2, 32);
    adda_s(f3, f2);
    sub_s(f0, f0, f2);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 32);
    if (cond(ctx)) {
        // 0x004f82a0
        charge(ctx, 14);
        lwc1(f0, a2, anim::kIfQuat);
        neg_s(f1, f1);
        neg_s(f0, f0);
        swc1(f0, a2, anim::kIfQuat);
        lwc1(f0, a2, 12);
        neg_s(f0, f0);
        swc1(f0, a2, 12);
        lwc1(f0, a2, 16);
        neg_s(f0, f0);
        swc1(f0, a2, 16);
        lwc1(f0, a2, 20);
        neg_s(f0, f0);
        swc1(f0, a2, 20);
        backedge(ctx);
    }
    // 0x004f7fc8
    charge(ctx, 9);
    a3 = 0x3F800000;
    v1 = 0x3F7F0000;
    mtc1(a3, f0);
    v1 = v1 | 0xBE77;
    mtc1(v1, f3);
    c_lt_s(f1, f3);
    sub_s(f2, f0, f12);
    if (cond(ctx)) {
        // 0x004f7fec
        charge(ctx, 8);
        swc1(f1, sp, 0xC);
        at = 0x3F800000;
        lw(a3, sp, 0xC);
        v1 = dsll32(a3, 1);
        v1 = dsrl32(v1, 1);
        at = slt(v1, at);
        if (at == 0) {
            // 0x004f82d8
            charge(ctx, 2);
            if (i64(a3) <= 0) {
                // 0x004f82ec
                charge(ctx, 5);
                v1 = 0x40490000;
                v1 = v1 | 0xFDB;
                mtc1(v1, f14);
                backedge(ctx);
            } else {
                // 0x004f82e0
                charge(ctx, 3);
                mtc1(zero, f14);
                backedge(ctx);
            }
        L_004f813c:
            charge(ctx, 1);
            v1 = 0x2F2E0000;
        } else {
            // 0x004f800c
            charge(ctx, 4);
            at = 0x3F000000;
            at = slt(v1, at);
            if (at == 0) {
                // 0x004f8300
                charge(ctx, 2);
                if (i64(a3) < 0) {
                    // 0x004f8434
                    charge(ctx, 72);
                    add_s(f1, f0, f1);
                    t1 = 0x3F000000;
                    a3 = 0x38110000;
                    v1 = 0x3A4F0000;
                    t0 = a3 | 0xEF08;
                    t2 = v1 | 0x7F04;
                    a3 = lui(0xBD24);
                    v1 = 0x3E4E0000;
                    mtc1(t1, f3);
                    t5 = a3 | 0x1146;
                    mtc1(t2, f15);
                    mul_s(f17, f3, f1);
                    t1 = v1 | 0xAA8;
                    v1 = lui(0xBEA6);
                    t4 = v1 | 0xB090;
                    v1 = 0x3E2A0000;
                    mtc1(zero, f14);
                    mtc1(t0, f16);
                    adda_s(f14, f15);
                    t0 = v1 | 0xAAAB;
                    v1 = 0x3D9D0000;
                    a3 = v1 | 0xC62E;
                    v1 = lui(0xBF30);
                    t3 = v1 | 0x3361;
                    v1 = 0x40010000;
                    t2 = v1 | 0x572D;
                    mtc1(a3, f8);
                    v1 = lui(0xC019);
                    mtc1(t1, f11);
                    mtc1(t5, f13);
                    a3 = 0x40000000;
                    t1 = v1 | 0xD139;
                    madd_s(f15, f16, f17);
                    v1 = 0x33A20000;
                    adda_s(f14, f13);
                    madd_s(f13, f17, f15);
                    adda_s(f14, f11);
                    mtc1(t0, f9);
                    mtc1(t4, f10);
                    madd_s(f11, f17, f13);
                    t0 = v1 | 0x2168;
                    adda_s(f14, f10);
                    v1 = 0x40490000;
                    madd_s(f10, f17, f11);
                    v1 = v1 | 0xFDA;
                    adda_s(f14, f9);
                    madd_s(f9, f17, f10);
                    mtc1(t3, f7);
                    mtc1(t2, f6);
                    adda_s(f14, f7);
                    madd_s(f7, f8, f17);
                    adda_s(f14, f6);
                    mtc1(t1, f5);
                    madd_s(f6, f17, f7);
                    adda_s(f14, f5);
                    madd_s(f5, f17, f6);
                    adda_s(f14, f0);
                    mul_s(f9, f17, f9);
                    madd_s(f0, f17, f5);
                    sqrt_s(f18, f17);
                    div_s(f0, f9, f0);
                    mtc1(v1, f1);
                    mul_s(f0, f0, f18);
                    mtc1(t0, f4);
                    mtc1(a3, f3);
                    sub_s(f0, f0, f4);
                    add_s(f0, f18, f0);
                    adda_s(f14, f1);
                    msub_s(f14, f3, f0);
                    backedge(ctx);
                } else {
                    // 0x004f8308
                    charge(ctx, 75);
                    sub_s(f1, f0, f1);
                    t1 = 0x3F000000;
                    a3 = 0x38110000;
                    v1 = si(-4096);
                    t0 = a3 | 0xEF08;
                    a3 = 0x3A4F0000;
                    mtc1(t1, f3);
                    t7 = a3 | 0x7F04;
                    a3 = lui(0xBD24);
                    mul_s(f15, f3, f1);
                    t1 = a3 | 0x1146;
                    a3 = 0x3E4E0000;
                    t6 = a3 | 0xAA8;
                    a3 = 0x3E2A0000;
                    t4 = a3 | 0xAAAB;
                    mtc1(t0, f14);
                    a3 = lui(0xBF30);
                    sqrt_s(f16, f15);
                    t2 = a3 | 0x3361;
                    t0 = lui(0xBEA6);
                    a3 = 0x40010000;
                    t5 = t0 | 0xB090;
                    t0 = 0x3D9D0000;
                    t3 = t0 | 0xC62E;
                    mtc1(t1, f10);
                    mtc1(t7, f13);
                    t1 = a3 | 0x572D;
                    mtc1(zero, f11);
                    a3 = lui(0xC019);
                    t0 = a3 | 0xD139;
                    adda_s(f11, f13);
                    a3 = 0x40000000;
                    madd_s(f13, f14, f15);
                    adda_s(f11, f10);
                    mtc1(t6, f9);
                    madd_s(f10, f15, f13);
                    adda_s(f11, f9);
                    mtc1(t5, f4);
                    madd_s(f9, f15, f10);
                    adda_s(f11, f4);
                    mtc1(t4, f8);
                    madd_s(f9, f15, f9);
                    adda_s(f11, f8);
                    madd_s(f8, f15, f9);
                    mtc1(t2, f6);
                    mtc1(t3, f7);
                    adda_s(f11, f6);
                    mtc1(t1, f5);
                    madd_s(f6, f7, f15);
                    adda_s(f11, f5);
                    mtc1(t0, f3);
                    madd_s(f5, f15, f6);
                    adda_s(f11, f3);
                    madd_s(f3, f15, f5);
                    adda_s(f11, f0);
                    madd_s(f0, f15, f3);
                    mul_s(f8, f15, f8);
                    div_s(f5, f8, f0);
                    mtc1(a3, f1);
                    swc1(f16, sp, 0x8);
                    lw(a3, sp, 0x8);
                    adda_s(f11, f15);
                    v1 = a3 & v1;
                    sw(v1, sp, 0x4);
                    lwc1(f4, sp, 0x4);
                    add_s(f0, f16, f4);
                    msub_s(f3, f4, f4);
                    div_s(f0, f3, f0);
                    adda_s(f11, f0);
                    madd_s(f0, f5, f16);
                    add_s(f0, f4, f0);
                    mul_s(f14, f1, f0);
                    backedge(ctx);
                }
                goto L_004f813c;
            }
            // 0x004f801c
            charge(ctx, 5);
            at = 0x23000000;
            at = at | 0x1;
            at = slt(v1, at);
            if (at == 0) {
                // 0x004f8044
                charge(ctx, 62);
                v1 = 0x38110000;
                a3 = v1 | 0xEF08;
                v1 = 0x3A4F0000;
                t2 = v1 | 0x7F04;
                v1 = lui(0xBD24);
                t0 = v1 | 0x1146;
                v1 = 0x3E4E0000;
                t1 = v1 | 0xAA8;
                mul_s(f17, f1, f1);
                v1 = lui(0xBEA6);
                mtc1(a3, f16);
                mtc1(t2, f15);
                a3 = v1 | 0xB090;
                mtc1(zero, f14);
                v1 = 0x3E2A0000;
                mtc1(t0, f13);
                adda_s(f14, f15);
                t0 = v1 | 0xAAAB;
                madd_s(f15, f16, f17);
                v1 = 0x3D9D0000;
                mtc1(a3, f10);
                adda_s(f14, f13);
                a3 = v1 | 0xC62E;
                v1 = lui(0xBF30);
                v1 = v1 | 0x3361;
                mtc1(v1, f7);
                mtc1(t1, f11);
                madd_s(f13, f17, f15);
                v1 = 0x40010000;
                adda_s(f14, f11);
                madd_s(f11, f17, f13);
                adda_s(f14, f10);
                mtc1(a3, f8);
                mtc1(t0, f9);
                a3 = v1 | 0x572D;
                madd_s(f10, f17, f11);
                v1 = lui(0xC019);
                adda_s(f14, f9);
                v1 = v1 | 0xD139;
                madd_s(f9, f17, f10);
                adda_s(f14, f7);
                mtc1(v1, f5);
                mtc1(a3, f6);
                madd_s(f7, f8, f17);
                v1 = 0x33A20000;
                adda_s(f14, f6);
                a3 = v1 | 0x2168;
                madd_s(f6, f17, f7);
                v1 = 0x3FC90000;
                adda_s(f14, f5);
                v1 = v1 | 0xFDA;
                madd_s(f5, f17, f6);
                adda_s(f14, f0);
                mul_s(f9, f17, f9);
                madd_s(f0, f17, f5);
                div_s(f0, f9, f0);
                mtc1(a3, f4);
                mtc1(v1, f3);
                adda_s(f14, f4);
                msub_s(f0, f1, f0);
                sub_s(f0, f1, f0);
                sub_s(f14, f3, f0);
                goto L_004f813c;
            }
            // 0x004f8030
            charge(ctx, 5);
            v1 = 0x3FC90000;
            v1 = v1 | 0xFDB;
            mtc1(v1, f14);
            v1 = 0x2F2E0000;
        }
        // 0x004f8140
        charge(ctx, 67);
        t0 = v1 | 0xC9D3;
        mul_s(f4, f14, f14);
        v1 = lui(0xB2D7);
        t2 = v1 | 0x2F34;
        v1 = 0x36380000;
        a3 = v1 | 0xEF1B;
        v1 = lui(0xB950);
        t1 = v1 | 0xD01;
        mtc1(t2, f11);
        v1 = 0x3C080000;
        mtc1(zero, f10);
        mtc1(t0, f13);
        adda_s(f10, f11);
        t0 = v1 | 0x8889;
        mtc1(a3, f9);
        v1 = lui(0xBE2A);
        madd_s(f3, f13, f4);
        a3 = v1 | 0xAAAB;
        adda_s(f10, f9);
        v1 = 0x3F800000;
        mtc1(t1, f8);
        madd_s(f3, f4, f3);
        adda_s(f10, f8);
        mtc1(t0, f7);
        madd_s(f3, f4, f3);
        adda_s(f10, f7);
        mtc1(a3, f6);
        madd_s(f3, f4, f3);
        adda_s(f10, f6);
        madd_s(f3, f4, f3);
        mul_s(f1, f4, f14);
        adda_s(f10, f14);
        madd_s(f1, f1, f3);
        mtc1(v1, f0);
        mul_s(f3, f2, f14);
        div_s(f5, f0, f1);
        mul_s(f2, f3, f3);
        adda_s(f10, f11);
        madd_s(f0, f13, f2);
        adda_s(f10, f9);
        madd_s(f0, f2, f0);
        adda_s(f10, f8);
        madd_s(f0, f2, f0);
        adda_s(f10, f7);
        madd_s(f0, f2, f0);
        adda_s(f10, f6);
        madd_s(f1, f2, f0);
        mul_s(f0, f2, f3);
        adda_s(f10, f3);
        madd_s(f0, f0, f1);
        mul_s(f4, f12, f14);
        mul_s(f2, f0, f5);
        mul_s(f3, f4, f4);
        adda_s(f10, f11);
        madd_s(f0, f13, f3);
        adda_s(f10, f9);
        madd_s(f0, f3, f0);
        adda_s(f10, f8);
        madd_s(f0, f3, f0);
        adda_s(f10, f7);
        madd_s(f0, f3, f0);
        adda_s(f10, f6);
        madd_s(f1, f3, f0);
        mul_s(f0, f3, f4);
        adda_s(f10, f4);
        madd_s(f0, f0, f1);
        mul_s(f12, f0, f5);
    }
    // 0x004f824c
    charge(ctx, 21);
    lwc1(f0, a2, 8);
    lwc1(f1, a1, 8);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 8);
    lwc1(f0, a2, 12);
    lwc1(f1, a1, 12);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 12);
    lwc1(f0, a2, 16);
    lwc1(f1, a1, 16);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 16);
    lwc1(f0, a2, 20);
    lwc1(f1, a1, 20);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 20);
    // 0x004f8554
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x004F8560 sub_4F8560 -- 292 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F8560 [cmpKeyFrameStreamRead]: Stream-read callback: per keyframe the time (real), 7 int16 (quaternion +
// translation) and the previous-frame byte offset (turned into a pointer, stride 24); then the 24-byte custom data.
void sub_4F8560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f8560
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, anim::kAnmNumFrames);
    lw(s0, a1, anim::kAnmFrames);
    lw(s2, a1, anim::kAnmCustomData);
    at = slt(0, v0);
    s3 = 0;
    if (at != 0) {
        // 0x004f85a0
        charge(ctx, 1);
        s1 = s0;
        for (;;) {
            // 0x004f85a4
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(s1, 4);
            a2 = 4;
            jal(ctx, 0x4F85ACu, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
            if (v0 == 0) {
                // 0x004f85bc_3 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = 0;
                // 0x004f8660 (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
            // 0x004f85c4
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(s1, 8);
            a2 = 14;
            jal(ctx, 0x4F85CCu, gen::fn_sub_4C1850_004c1850);  // [RwStreamReadInt16]
            if (v0 == 0) {
                // 0x004f8654 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = 0;
                // 0x004f8660 (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
            // 0x004f85dc
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(sp, 0x7C);
            a2 = 4;
            jal(ctx, 0x4F85E4u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 == 0) {
                goto L_004f865c;
            }
            // 0x004f85f4
            charge(ctx, 16);
            lw(v1, sp, 0x7C);
            v0 = lui(0xAAAA);
            v0 = v0 | 0xAAAB;
            multu(zero, v0, v1);
            mfhi(v0);
            s3 = addiu(s3, 1);
            v1 = srl(v0, 4);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 3);
            v0 = addu(s0, v0);
            sw(v0, s1, 0);
            lw(v0, s4, anim::kAnmNumFrames);
            v0 = slt(s3, v0);
            s1 = addiu(s1, 24);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f8634
        charge(ctx, 1);
    }
    // 0x004f8638
    charge(ctx, 7);
    a0 = s5;
    a1 = s2;
    a2 = 24;
    jal(ctx, 0x4F8640u, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
    if (v0 == 0) s4 = 0;
    v0 = s4;
    // 0x004f8660 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004f865c:
    charge(ctx, 1);
    v0 = 0;
    // 0x004f8660 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x004F8690 sub_4F8690 -- 256 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F8690 [cmpKeyFrameStreamWrite]: Stream-write callback: per keyframe the time, the 7 int16 and the previous
// frame's byte offset; then the custom data.
void sub_4F8690(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f8690
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    lw(v0, a0, anim::kAnmNumFrames);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    at = slt(0, v0);
    sq(s0, sp, 0x0);
    lw(s0, a0, anim::kAnmFrames);
    lw(s2, a0, anim::kAnmCustomData);
    s3 = 0;
    if (at != 0) {
        // 0x004f86d0
        charge(ctx, 1);
        s1 = s0;
        for (;;) {
            // 0x004f86d4
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(s1, 4);
            a2 = 4;
            jal(ctx, 0x4F86DCu, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
            if (v0 == 0) {
                // 0x004f86ec_3 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = 0;
                // 0x004f876c (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
            // 0x004f86f4
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(s1, 8);
            a2 = 14;
            jal(ctx, 0x4F86FCu, gen::fn_sub_4C1820_004c1820);  // [RwStreamWriteInt16]
            if (v0 == 0) {
                // 0x004f8760 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = 0;
                // 0x004f876c (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
            // 0x004f870c
            charge(ctx, 9);
            lw(v0, s1, 0);
            a0 = s4;
            a1 = addiu(sp, 0x7C);
            a2 = 4;
            v0 = subu(v0, s0);
            link(ctx, 0x4F8720u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x7C);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 == 0) {
                goto L_004f8768;
            }
            // 0x004f8730
            charge(ctx, 5);
            lw(v0, s5, anim::kAnmNumFrames);
            s3 = addiu(s3, 1);
            v0 = slt(s3, v0);
            s1 = addiu(s1, 24);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f8744
        charge(ctx, 1);
    }
    // 0x004f8748
    charge(ctx, 6);
    a0 = s4;
    a1 = s2;
    a2 = 24;
    jal(ctx, 0x4F8750u, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
    v0 = sltu(0, v0);
    // 0x004f876c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004f8768:
    charge(ctx, 1);
    v0 = 0;
    // 0x004f876c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x004F8790 sub_4F8790 -- 20 bytes; leaf frame (no stack)
// sub_4F8790 [cmpKeyFrameStreamGetSize]: Stream-size callback: 22 bytes per keyframe + 24.
void sub_4F8790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004f8790
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, anim::kAnmNumFrames);
    v1 = 22;
    mult(v0, v1, v0);
    v0 = addiu(v0, 24);
}

// 0x004F87B0 sub_4F87B0 -- 1268 bytes; frame 0xA0: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_4F87B0 [cmpKeyFrameMulRecip]: Mul-recip callback: multiplies keyframe $a0 by the inverse of $a1 (conjugate
// quaternion product, translation difference) and re-packs the result with cmpKeyFloatToHalf.
void sub_4F87B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x004f87b0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s1 = a0;
    swc1(f25, sp, 0x14);
    s0 = a1;
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lhu(a0, a1, anim::kKfQuat);
    lwc1(f20, sp, 0x50);
    lwc1(f21, sp, 0x54);
    lwc1(f22, sp, 0x58);
    lwc1(f23, sp, 0x5C);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x9C);
    if (v0 != 0) {
        // 0x004f8808
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x9C);
    }
    // 0x004f882c
    charge(ctx, 6);
    lhu(a0, s0, 10);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x98);
    if (v0 != 0) {
        // 0x004f8844
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x98);
    }
    // 0x004f8868
    charge(ctx, 6);
    lhu(a0, s0, 12);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x94);
    if (v0 != 0) {
        // 0x004f8880
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x94);
    }
    // 0x004f88a4
    charge(ctx, 6);
    lhu(a0, s0, 14);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x90);
    if (v0 != 0) {
        // 0x004f88bc
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x90);
    }
    // 0x004f88e0
    charge(ctx, 12);
    lwc1(f2, sp, 0x98);
    lwc1(f3, sp, 0x9C);
    lwc1(f4, sp, 0x94);
    lwc1(f5, sp, 0x90);
    mtc1(zero, f0);
    mula_s(f2, f2);
    madda_s(f3, f3);
    madda_s(f4, f4);
    madd_s(f1, f5, f5);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x004f8910
        charge(ctx, 9);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f0, f0, f1);
        mul_s(f23, f5, f0);
        neg_s(f0, f0);
        mul_s(f20, f3, f0);
        mul_s(f21, f2, f0);
        mul_s(f22, f4, f0);
    }
    // 0x004f8934
    charge(ctx, 6);
    lhu(a0, s1, anim::kKfQuat);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x8C);
    if (v0 != 0) {
        // 0x004f894c
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x8C);
    }
    // 0x004f8970
    charge(ctx, 6);
    lhu(a0, s1, 10);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x88);
    if (v0 != 0) {
        // 0x004f8988
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x88);
    }
    // 0x004f89ac
    charge(ctx, 6);
    lhu(a0, s1, 12);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x84);
    if (v0 != 0) {
        // 0x004f89c4
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x84);
    }
    // 0x004f89e8
    charge(ctx, 6);
    lhu(a0, s1, 14);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x80);
    if (v0 != 0) {
        // 0x004f8a00
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x80);
    }
    // 0x004f8a24
    charge(ctx, 48);
    lwc1(f6, sp, 0x84);
    lwc1(f7, sp, 0x88);
    lwc1(f3, sp, 0x8C);
    mtc1(zero, f4);
    lwc1(f0, sp, 0x80);
    mula_s(f21, f6);
    msub_s(f5, f22, f7);
    mula_s(f22, f3);
    msub_s(f2, f20, f6);
    mula_s(f20, f7);
    msub_s(f1, f21, f3);
    adda_s(f4, f5);
    madd_s(f3, f3, f23);
    adda_s(f4, f2);
    madd_s(f2, f7, f23);
    adda_s(f4, f1);
    madd_s(f1, f6, f23);
    adda_s(f4, f3);
    madd_s(f12, f20, f0);
    adda_s(f4, f2);
    madd_s(f25, f21, f0);
    adda_s(f4, f1);
    madd_s(f24, f22, f0);
    jal(ctx, 0x4F8A7Cu, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    mov_s(f12, f25);
    link(ctx, 0x4F8A88u);  // $ra first: the delay slot below depends on it
    sh(v0, s1, anim::kKfQuat);
    call(ctx, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    mov_s(f12, f24);
    link(ctx, 0x4F8A94u);  // $ra first: the delay slot below depends on it
    sh(v0, s1, 10);
    call(ctx, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    lwc1(f0, sp, 0x80);
    sh(v0, s1, 12);
    lwc1(f1, sp, 0x88);
    lwc1(f2, sp, 0x8C);
    lwc1(f3, sp, 0x84);
    mul_s(f0, f23, f0);
    mula_s(f21, f1);
    madda_s(f20, f2);
    madd_s(f1, f22, f3);
    sub_s(f12, f0, f1);
    jal(ctx, 0x4F8AC0u, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    sh(v0, s1, 14);
    lhu(a0, s0, 16);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x7C);
    if (v0 != 0) {
        // 0x004f8ae4
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x7C);
    }
    // 0x004f8b08
    charge(ctx, 6);
    lhu(a0, s0, 18);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x78);
    if (v0 != 0) {
        // 0x004f8b20
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x78);
    }
    // 0x004f8b44
    charge(ctx, 6);
    lhu(a0, s0, 20);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x74);
    if (v0 != 0) {
        // 0x004f8b5c
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x74);
    }
    // 0x004f8b80
    charge(ctx, 6);
    lhu(a0, s1, 16);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x70);
    if (v0 != 0) {
        // 0x004f8b98
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x70);
    }
    // 0x004f8bbc
    charge(ctx, 7);
    lhu(a0, s1, 18);
    lwc1(f4, sp, 0x70);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x6C);
    if (v0 != 0) {
        // 0x004f8bd8
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x6C);
    }
    // 0x004f8bfc
    charge(ctx, 7);
    lhu(a0, s1, 20);
    lwc1(f20, sp, 0x6C);
    v1 = a0 & 0x8000;
    v0 = a0 & 0x7FFF;
    a1 = sll(v1, 16);
    sw(a1, sp, 0x68);
    if (v0 != 0) {
        // 0x004f8c18
        charge(ctx, 9);
        v0 = a0 & 0x7FF;
        v1 = a0 & 0x7800;
        a0 = sll(v1, 12);
        v0 = sll(v0, 12);
        v1 = 0x38000000;
        v1 = addu(a0, v1);
        v1 = a1 | v1;
        v0 = v1 | v0;
        sw(v0, sp, 0x68);
    }
    // 0x004f8c3c
    charge(ctx, 26);
    lwc1(f2, sp, 0x7C);
    lwc1(f1, sp, 0x78);
    lwc1(f3, sp, 0x68);
    lwc1(f0, sp, 0x74);
    sub_s(f12, f4, f2);
    sub_s(f21, f3, f0);
    sub_s(f20, f20, f1);
    jal(ctx, 0x4F8C54u, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    mov_s(f12, f20);
    link(ctx, 0x4F8C60u);  // $ra first: the delay slot below depends on it
    sh(v0, s1, 16);
    call(ctx, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    mov_s(f12, f21);
    link(ctx, 0x4F8C6Cu);  // $ra first: the delay slot below depends on it
    sh(v0, s1, 18);
    call(ctx, gen::fn_sub_4F7300_004f7300);  // [cmpKeyFloatToHalf]
    sh(v0, s1, 20);
    ld(ra, sp, 0x40);
    lwc1(f25, sp, 0x14);
    lq(s1, sp, 0x30);
    lwc1(f24, sp, 0x10);
    lq(s0, sp, 0x20);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004F8CB0 sub_4F8CB0 -- 344 bytes; leaf frame (no stack)
// sub_4F8CB0 [cmpKeyFrameAdd]: Add callback: out = quaternion product of the two frames and the sum of their
// translations.
void sub_4F8CB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004f8cb0
    enter(ctx, 86);  // entry check point + this block's cycles
    lwc1(f2, a1, 20);
    lwc1(f1, a2, 20);
    lwc1(f4, a1, 12);
    lwc1(f3, a2, 12);
    lwc1(f6, a1, anim::kIfQuat);
    lwc1(f5, a2, anim::kIfQuat);
    lwc1(f8, a1, 16);
    lwc1(f7, a2, 16);
    mul_s(f1, f2, f1);
    mula_s(f4, f3);
    madda_s(f6, f5);
    madd_s(f3, f8, f7);
    sub_s(f1, f1, f3);
    swc1(f1, a0, 20);
    lwc1(f2, a1, 12);
    lwc1(f1, a2, 16);
    lwc1(f4, a1, 16);
    lwc1(f3, a2, 12);
    mtc1(zero, f0);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, anim::kIfQuat);
    lwc1(f2, a1, 16);
    lwc1(f1, a2, anim::kIfQuat);
    lwc1(f4, a1, anim::kIfQuat);
    lwc1(f3, a2, 16);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, 12);
    lwc1(f2, a1, anim::kIfQuat);
    lwc1(f1, a2, 12);
    lwc1(f4, a1, 12);
    lwc1(f3, a2, anim::kIfQuat);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, 16);
    lwc1(f1, a0, anim::kIfQuat);
    lwc1(f3, a2, anim::kIfQuat);
    lwc1(f2, a1, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, anim::kIfQuat);
    lwc1(f1, a0, 12);
    lwc1(f3, a2, 12);
    lwc1(f2, a1, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 12);
    lwc1(f1, a0, 16);
    lwc1(f3, a2, 16);
    lwc1(f2, a1, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 16);
    lwc1(f1, a0, anim::kIfQuat);
    lwc1(f3, a1, anim::kIfQuat);
    lwc1(f2, a2, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, anim::kIfQuat);
    lwc1(f1, a0, 12);
    lwc1(f3, a1, 12);
    lwc1(f2, a2, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 12);
    lwc1(f1, a0, 16);
    lwc1(f3, a1, 16);
    lwc1(f2, a2, 20);
    adda_s(f0, f1);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 16);
    lwc1(f1, a1, anim::kIfTrans);
    lwc1(f0, a2, anim::kIfTrans);
    add_s(f0, f1, f0);
    swc1(f0, a0, anim::kIfTrans);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    add_s(f0, f1, f0);
    swc1(f0, a0, 28);
    lwc1(f1, a1, 32);
    lwc1(f0, a2, 32);
    add_s(f0, f1, f0);
    swc1(f0, a0, 32);
}

// 0x004F8E10 sub_4F8E10 -- 156 bytes; frame 0x40: ra sp+0x0
// sub_4F8E10 [cmpKeyRegisterScheme]: Registers the compressed keyframe scheme (id 2, 24-byte keyframes, 36-byte
// interpolated frames, 24 bytes of custom data). Returns 1.
void sub_4F8E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f8e10
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 2;
    sd(ra, sp, 0x0);
    v1 = 24;
    sw(v0, sp, 0x10);
    a0 = addiu(sp, 0x10);
    v0 = 36;
    sw(v1, sp, 0x18);
    sw(v0, sp, 0x14);
    v0 = 0x4F0000;
    sw(v1, sp, 0x3C);
    v0 = addiu(v0, 29808);  // &sub_4F7470
    sw(v0, sp, 0x1C);
    v0 = 0x4F0000;
    v0 = addiu(v0, 32576);  // &sub_4F7F40
    sw(v0, sp, 0x20);
    v0 = 0x4F0000;
    v0 = addiu(v0, 30048);  // &sub_4F7560
    sw(v0, sp, 0x24);
    v0 = 0x500000;
    v0 = addiu(v0, -29520);  // &sub_4F8CB0
    sw(v0, sp, 0x28);
    v0 = 0x500000;
    v0 = addiu(v0, -30800);  // &sub_4F87B0
    sw(v0, sp, 0x2C);
    v0 = 0x500000;
    v0 = addiu(v0, -31392);  // &sub_4F8560
    sw(v0, sp, 0x30);
    v0 = 0x500000;
    v0 = addiu(v0, -31088);  // &sub_4F8690
    sw(v0, sp, 0x34);
    v0 = 0x500000;
    v0 = addiu(v0, -30832);  // &sub_4F8790
    link(ctx, 0x4F8E94u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x38);
    call(ctx, gen::fn_sub_4B6680_004b6680);  // [RtAnimRegisterInterpolationScheme]
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x40);
}

// 0x0035A290 sub_35A290 -- 348 bytes; frame 0xB0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_35A290 [gameKeyFrameApply]: Apply callback of the game scheme: matrix $a0 = scale(frame +36) x rotation(frame
// quaternion), translation from frame +24; clears the matrix's identity flag.
void sub_35A290(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x0035a290
    enter(ctx, 87);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    lwc1(f3, a1, anim::kIfQuat);
    lwc1(f2, a1, 12);
    lwc1(f1, a1, 16);
    lwc1(f0, a1, 20);
    mul_s(f12, f3, f3);
    mul_s(f11, f2, f2);
    mul_s(f10, f1, f1);
    mul_s(f9, f2, f1);
    mul_s(f8, f1, f3);
    mul_s(f7, f3, f2);
    mul_s(f6, f0, f3);
    mul_s(f5, f0, f2);
    mul_s(f4, f0, f1);
    add_s(f0, f11, f10);
    v0 = 0x40000000;
    mtc1(v0, f3);
    v0 = 0x3F800000;
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f2);
    msub_s(f0, f3, f0);
    swc1(f0, sp, 0x30);
    add_s(f0, f7, f4);
    mul_s(f0, f3, f0);
    swc1(f0, sp, 0x34);
    sub_s(f0, f8, f5);
    mul_s(f0, f3, f0);
    swc1(f0, sp, 0x38);
    sub_s(f0, f7, f4);
    mul_s(f0, f3, f0);
    swc1(f0, sp, 0x40);
    add_s(f0, f12, f10);
    adda_s(f1, f2);
    msub_s(f0, f3, f0);
    swc1(f0, sp, 0x44);
    add_s(f0, f9, f6);
    mul_s(f0, f3, f0);
    swc1(f0, sp, 0x48);
    add_s(f0, f8, f5);
    mul_s(f0, f3, f0);
    swc1(f0, sp, 0x50);
    sub_s(f0, f9, f6);
    mul_s(f0, f3, f0);
    swc1(f0, sp, 0x54);
    add_s(f0, f12, f11);
    adda_s(f1, f2);
    msub_s(f0, f3, f0);
    swc1(f0, sp, 0x58);
    sw(zero, sp, 0x60);
    sw(zero, sp, 0x64);
    sw(zero, sp, 0x68);
    v0 = 3;
    sw(v0, sp, 0x3C);
    a0 = addiu(sp, 0x70);
    a1 = addiu(s1, 36);
    a2 = 0;
    jal(ctx, 0x35A38Cu, gen::fn_sub_4C33D0_004c33d0);  // [RwMatrixScale]
    a0 = s0;
    a1 = addiu(sp, 0x70);
    a2 = addiu(sp, 0x30);
    jal(ctx, 0x35A3A0u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
    lwc1(f2, s1, anim::kIfTrans);
    lwc1(f1, s1, 28);
    lwc1(f0, s1, 32);
    swc1(f2, s0, 48);
    swc1(f1, s0, 52);
    swc1(f0, s0, 56);
    lw(a0, s0, 12);
    v1 = lui(0xFFFD);
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    sw(v1, s0, 12);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x0035A3F0 sub_35A3F0 -- 552 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_35A3F0 [gameKeyFrameInterpolateQT]: Interpolates two frames ($a1, $a2) at weight $f12 into $a0: slerp of the
// quaternions (the second negated when the dot product is negative; nlerp below the 0x7CAD18 threshold), lerp of
// translation and scale.
void sub_35A3F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0035a3f0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    mov_s(f21, f12);
    lwc1(f7, a2, anim::kIfQuat);
    lwc1(f6, a1, 20);
    lwc1(f5, a2, 20);
    lwc1(f4, a1, 16);
    lwc1(f3, a2, 16);
    lwc1(f2, a1, anim::kIfQuat);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 12);
    mula_s(f1, f0);
    mtc1(zero, f0);
    madda_s(f2, f7);
    madda_s(f4, f3);
    madd_s(f12, f6, f5);
    c_lt_s(f12, f0);
    if (cond(ctx)) {
        // 0x0035a464
        charge(ctx, 12);
        neg_s(f12, f12);
        neg_s(f0, f7);
        swc1(f0, s0, anim::kIfQuat);
        lwc1(f0, s0, 12);
        neg_s(f0, f0);
        swc1(f0, s0, 12);
        lwc1(f0, s0, 16);
        neg_s(f0, f0);
        swc1(f0, s0, 16);
        lwc1(f0, s0, 20);
        neg_s(f0, f0);
        swc1(f0, s0, 20);
    }
    // 0x0035a494
    charge(ctx, 8);
    v1 = 0x3F800000;
    mtc1(v1, f0);
    sub_s(f20, f0, f21);
    lwc1(f0, gp, -32728);  // 0x7CAD18
    c_lt_s(f12, f0);
    if (cond(ctx)) {
        // 0x0035a4b4
        charge(ctx, 20);
        jal(ctx, 0x35A4B4u, gen::fn_acosf_0052e9e8);  // [acosf]
        mov_s(f22, f0);
        mov_s(f12, f22);
        jal(ctx, 0x35A4C4u, gen::fn_sinf_0052e878);  // [sinf]
        v0 = 0x3F800000;
        mtc1(v0, f1);
        div_s(f23, f1, f0);
        mul_s(f12, f20, f22);
        jal(ctx, 0x35A4E8u, gen::fn_sinf_0052e878);  // [sinf]
        mul_s(f20, f23, f0);
        mul_s(f12, f21, f22);
        jal(ctx, 0x35A4F8u, gen::fn_sinf_0052e878);  // [sinf]
        mul_s(f21, f23, f0);
    }
    // 0x0035a504
    charge(ctx, 69);
    lwc1(f1, s1, anim::kIfQuat);
    lwc1(f0, s0, anim::kIfQuat);
    mula_s(f21, f0);
    mtc1(zero, f0);
    madd_s(f1, f20, f1);
    swc1(f1, s2, anim::kIfQuat);
    lwc1(f2, s1, 12);
    lwc1(f1, s0, 12);
    mula_s(f21, f1);
    madd_s(f1, f20, f2);
    swc1(f1, s2, 12);
    lwc1(f2, s1, 16);
    lwc1(f1, s0, 16);
    mula_s(f21, f1);
    madd_s(f1, f20, f2);
    swc1(f1, s2, 16);
    lwc1(f2, s1, 20);
    lwc1(f1, s0, 20);
    mula_s(f21, f1);
    madd_s(f1, f20, f2);
    swc1(f1, s2, 20);
    lwc1(f2, s1, anim::kIfTrans);
    lwc1(f1, s0, anim::kIfTrans);
    sub_s(f1, f1, f2);
    adda_s(f0, f2);
    madd_s(f1, f21, f1);
    swc1(f1, s2, anim::kIfTrans);
    lwc1(f2, s1, 28);
    lwc1(f1, s0, 28);
    sub_s(f1, f1, f2);
    adda_s(f0, f2);
    madd_s(f1, f21, f1);
    swc1(f1, s2, 28);
    lwc1(f2, s1, 32);
    lwc1(f1, s0, 32);
    sub_s(f1, f1, f2);
    adda_s(f0, f2);
    madd_s(f1, f21, f1);
    swc1(f1, s2, 32);
    lwc1(f2, s1, anim::kIfScale);
    lwc1(f1, s0, anim::kIfScale);
    sub_s(f1, f1, f2);
    adda_s(f0, f2);
    madd_s(f1, f21, f1);
    swc1(f1, s2, anim::kIfScale);
    lwc1(f2, s1, 40);
    lwc1(f1, s0, 40);
    sub_s(f1, f1, f2);
    adda_s(f0, f2);
    madd_s(f1, f21, f1);
    swc1(f1, s2, 40);
    lwc1(f2, s1, 44);
    lwc1(f1, s0, 44);
    sub_s(f1, f1, f2);
    adda_s(f0, f2);
    madd_s(f0, f21, f1);
    swc1(f0, s2, 44);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0035A620 sub_35A620 -- 116 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_35A620 [gameKeyFrameBlend]: Blend callback of the game scheme: gameKeyFrameInterpolateQT, plus the product of
// the two +48 values.
void sub_35A620(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x0035a620
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lwc1(f2, a1, anim::kIfKey2);
    lwc1(f0, a2, anim::kIfKey2);
    sub_s(f1, f0, f2);
    sub_s(f0, f12, f2);
    div_s(f12, f0, f1);
    jal(ctx, 0x35A660u, gen::fn_sub_35A3F0_0035a3f0);  // [gameKeyFrameInterpolateQT]
    lwc1(f1, s1, 48);
    lwc1(f0, s0, 48);
    mul_s(f0, f1, f0);
    swc1(f0, s2, 48);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0035A6A0 sub_35A6A0 -- 208 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_35A6A0 [gameKeyFrameStreamWrite]: Stream-write callback: per 52-byte keyframe 12 reals and the previous frame's
// byte offset.
void sub_35A6A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035a6a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(s0, a0, anim::kAnmFrames);
    s1 = 0;
    for (;;) {
        // 0x0035a73c
        charge(ctx, 4);
        lw(v0, s3, anim::kAnmNumFrames);
        v0 = slt(s1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035a6d0
        charge(ctx, 16);
        v0 = sll(s1, 1);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v1 = addu(s0, v0);
        lw(v0, v1, 0);
        v0 = subu(v0, s0);
        sw(v0, sp, 0x5C);
        a0 = s2;
        a1 = addiu(v1, 4);
        a2 = 48;
        jal(ctx, 0x35A700u, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
        if (v0 == 0) {
            goto L_0035a72c;
        }
        // 0x0035a710
        charge(ctx, 7);
        a0 = s2;
        a1 = addiu(sp, 0x5C);
        a2 = 4;
        jal(ctx, 0x35A71Cu, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 == 0) {
            goto L_0035a72c;
        }
        // 0x0035a738
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0035a74c
    charge(ctx, 1);
    v0 = 1;
    // 0x0035a750 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_0035a72c:
    charge(ctx, 3);
    v0 = 0;
    // 0x0035a750 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0035A770 sub_35A770 -- 216 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_35A770 [gameKeyFrameStreamRead]: Stream-read callback: per keyframe 12 reals and the previous frame's offset
// (turned into a pointer).
void sub_35A770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035a770
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    lw(s1, a1, anim::kAnmFrames);
    s2 = 0;
    for (;;) {
        // 0x0035a810
        charge(ctx, 4);
        lw(v0, s3, anim::kAnmNumFrames);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035a7a4
        charge(ctx, 13);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s1, v0);
        a0 = s4;
        a1 = addiu(s0, 4);
        a2 = 48;
        jal(ctx, 0x35A7C8u, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
        if (v0 == 0) {
            goto L_0035a7f4;
        }
        // 0x0035a7d8
        charge(ctx, 7);
        a0 = s4;
        a1 = addiu(sp, 0x6C);
        a2 = 4;
        jal(ctx, 0x35A7E4u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
        if (v0 == 0) {
            goto L_0035a7f4;
        }
        // 0x0035a800
        charge(ctx, 4);
        lw(v0, sp, 0x6C);
        v0 = addu(s1, v0);
        sw(v0, s0, 0);
        s2 = addiu(s2, 1);
    }
    // 0x0035a820
    charge(ctx, 1);
    v0 = s3;
    // 0x0035a824 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_0035a7f4:
    charge(ctx, 3);
    v0 = 0;
    // 0x0035a824 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0035A850 sub_35A850 -- 32 bytes; leaf frame (no stack)
// sub_35A850 [gameKeyFrameStreamGetSize]: Stream-size callback: 52 bytes per keyframe.
void sub_35A850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0035a850
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, a0, anim::kAnmNumFrames);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
}

// 0x0035A870 sub_35A870 -- 408 bytes; frame 0x10
// sub_35A870 [gameKeyFrameMulRecip]: Mul-recip callback: frame $a0 times the inverse of $a1 (conjugate quaternion
// product, translation difference).
void sub_35A870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10};
    // 0x0035a870
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f5, a0, anim::kKfQuat);
    lwc1(f4, a0, 12);
    lwc1(f3, a0, 16);
    lwc1(f2, a0, 20);
    swc1(f5, sp, 0x0);
    swc1(f4, sp, 0x4);
    swc1(f3, sp, 0x8);
    swc1(f2, sp, 0xC);
    lwc1(f7, a1, 12);
    lwc1(f6, a1, anim::kKfQuat);
    lwc1(f5, a1, 16);
    lwc1(f4, a1, 20);
    mula_s(f7, f7);
    mtc1(zero, f3);
    madda_s(f6, f6);
    madda_s(f5, f5);
    madd_s(f2, f4, f4);
    c_le_s(f2, f3);
    if (!cond(ctx)) {
        // 0x0035a8c4
        charge(ctx, 9);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f2);
        mul_s(f10, f4, f0);
        neg_s(f0, f0);
        mul_s(f9, f6, f0);
        mul_s(f1, f7, f0);
        mul_s(f0, f5, f0);
    }
    // 0x0035a8e8
    charge(ctx, 72);
    lwc1(f8, sp, 0x4);
    lwc1(f7, sp, 0x8);
    lwc1(f6, sp, 0xC);
    lwc1(f5, sp, 0x0);
    mula_s(f1, f8);
    mtc1(zero, f4);
    madda_s(f9, f5);
    madd_s(f3, f0, f7);
    mul_s(f2, f10, f6);
    sub_s(f2, f2, f3);
    swc1(f2, a0, 20);
    mula_s(f1, f7);
    msub_s(f2, f0, f8);
    swc1(f2, a0, anim::kKfQuat);
    mula_s(f0, f5);
    msub_s(f2, f9, f7);
    swc1(f2, a0, 12);
    mula_s(f9, f8);
    msub_s(f2, f1, f5);
    swc1(f2, a0, 16);
    lwc1(f2, a0, anim::kKfQuat);
    adda_s(f4, f2);
    madd_s(f2, f5, f10);
    swc1(f2, a0, anim::kKfQuat);
    lwc1(f2, a0, 12);
    adda_s(f4, f2);
    madd_s(f2, f8, f10);
    swc1(f2, a0, 12);
    lwc1(f2, a0, 16);
    adda_s(f4, f2);
    madd_s(f2, f7, f10);
    swc1(f2, a0, 16);
    lwc1(f2, a0, anim::kKfQuat);
    adda_s(f4, f2);
    madd_s(f2, f9, f6);
    swc1(f2, a0, anim::kKfQuat);
    lwc1(f2, a0, 12);
    adda_s(f4, f2);
    madd_s(f1, f1, f6);
    swc1(f1, a0, 12);
    lwc1(f1, a0, 16);
    adda_s(f4, f1);
    madd_s(f0, f0, f6);
    swc1(f0, a0, 16);
    lwc1(f1, a1, anim::kKfTrans);
    lwc1(f0, a0, anim::kKfTrans);
    sub_s(f0, f0, f1);
    swc1(f0, a0, anim::kKfTrans);
    lwc1(f1, a1, 28);
    lwc1(f0, a0, 28);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 28);
    lwc1(f1, a1, 32);
    lwc1(f0, a0, 32);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 32);
    lwc1(f1, a1, anim::kKfScale);
    lwc1(f0, a0, anim::kKfScale);
    sub_s(f0, f0, f1);
    swc1(f0, a0, anim::kKfScale);
    lwc1(f1, a1, 40);
    lwc1(f0, a0, 40);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 40);
    lwc1(f1, a1, 44);
    lwc1(f0, a0, 44);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 44);
    sp = addiu(sp, 0x10);
}

// 0x0035AA10 sub_35AA10 -- 392 bytes; leaf frame (no stack)
// sub_35AA10 [gameKeyFrameAdd]: Add callback: quaternion product, translation sum.
void sub_35AA10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x0035aa10
    enter(ctx, 98);  // entry check point + this block's cycles
    lwc1(f5, a1, 16);
    lwc1(f4, a2, 16);
    lwc1(f3, a1, anim::kKfQuat);
    lwc1(f2, a2, anim::kKfQuat);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 12);
    mula_s(f1, f0);
    mtc1(zero, f0);
    madda_s(f3, f2);
    madd_s(f3, f5, f4);
    lwc1(f2, a1, 20);
    lwc1(f1, a2, 20);
    mul_s(f1, f2, f1);
    sub_s(f1, f1, f3);
    swc1(f1, a0, 20);
    lwc1(f4, a1, 16);
    lwc1(f3, a2, 12);
    lwc1(f2, a1, 12);
    lwc1(f1, a2, 16);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, anim::kKfQuat);
    lwc1(f4, a1, anim::kKfQuat);
    lwc1(f3, a2, 16);
    lwc1(f2, a1, 16);
    lwc1(f1, a2, anim::kKfQuat);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, 12);
    lwc1(f4, a1, 12);
    lwc1(f3, a2, anim::kKfQuat);
    lwc1(f2, a1, anim::kKfQuat);
    lwc1(f1, a2, 12);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, 16);
    lwc1(f3, a2, anim::kKfQuat);
    lwc1(f2, a1, 20);
    lwc1(f1, a0, anim::kKfQuat);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, anim::kKfQuat);
    lwc1(f3, a2, 12);
    lwc1(f2, a1, 20);
    lwc1(f1, a0, 12);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 12);
    lwc1(f3, a2, 16);
    lwc1(f2, a1, 20);
    lwc1(f1, a0, 16);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 16);
    lwc1(f3, a1, anim::kKfQuat);
    lwc1(f2, a2, 20);
    lwc1(f1, a0, anim::kKfQuat);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, anim::kKfQuat);
    lwc1(f3, a1, 12);
    lwc1(f2, a2, 20);
    lwc1(f1, a0, 12);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 12);
    lwc1(f3, a1, 16);
    lwc1(f2, a2, 20);
    lwc1(f1, a0, 16);
    adda_s(f0, f1);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 16);
    lwc1(f1, a1, anim::kKfTrans);
    lwc1(f0, a2, anim::kKfTrans);
    add_s(f0, f1, f0);
    swc1(f0, a0, anim::kKfTrans);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    add_s(f0, f1, f0);
    swc1(f0, a0, 28);
    lwc1(f1, a1, 32);
    lwc1(f0, a2, 32);
    add_s(f0, f1, f0);
    swc1(f0, a0, 32);
    lwc1(f1, a1, anim::kKfScale);
    lwc1(f0, a2, anim::kKfScale);
    add_s(f0, f1, f0);
    swc1(f0, a0, anim::kKfScale);
    lwc1(f1, a1, 40);
    lwc1(f0, a2, 40);
    add_s(f0, f1, f0);
    swc1(f0, a0, 40);
    lwc1(f1, a1, 44);
    lwc1(f0, a2, 44);
    add_s(f0, f1, f0);
    swc1(f0, a0, 44);
}

// 0x0035ABA0 sub_35ABA0 -- 164 bytes; frame 0x40: ra sp+0x0
// sub_35ABA0 [gameKeyRegisterScheme]: Registers the game's keyframe scheme (id 0x44A07195, 52-byte keyframes and
// frames, callbacks 0x35A290..0x35AA10). Returns 1.
void sub_35ABA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035aba0
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    v0 = 0x44A00000;
    v0 = v0 | 0x7195;
    sw(v0, sp, 0x10);
    v0 = 52;
    sw(v0, sp, 0x18);
    sw(v0, sp, 0x14);
    v0 = 0x360000;
    v0 = addiu(v0, -23920);  // &sub_35A290
    sw(v0, sp, 0x1C);
    v0 = 0x360000;
    v0 = addiu(v0, -23568);  // &sub_35A3F0
    sw(v0, sp, 0x20);
    v0 = 0x360000;
    v0 = addiu(v0, -23008);  // &sub_35A620
    sw(v0, sp, 0x24);
    v0 = 0x360000;
    v0 = addiu(v0, -22000);  // &sub_35AA10
    sw(v0, sp, 0x28);
    v0 = 0x360000;
    v0 = addiu(v0, -22416);  // &sub_35A870
    sw(v0, sp, 0x2C);
    v0 = 0x360000;
    v0 = addiu(v0, -22672);  // &sub_35A770
    sw(v0, sp, 0x30);
    v0 = 0x360000;
    v0 = addiu(v0, -22880);  // &sub_35A6A0
    sw(v0, sp, 0x34);
    v0 = 0x360000;
    v0 = addiu(v0, -22448);  // &sub_35A850
    sw(v0, sp, 0x38);
    sw(zero, sp, 0x3C);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x35AC28u, gen::fn_sub_4B6680_004b6680);  // [RtAnimRegisterInterpolationScheme]
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00464760 sub_464760 -- 240 bytes; leaf frame (no stack)
// sub_464760 [RpHAnimKeyFrameApply]: Apply callback of the standard scheme (id 1): writes the frame's quaternion (+8)
// as a rotation matrix and its translation (+24) into matrix $a0, flags 3.
void sub_464760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x00464760
    enter(ctx, 60);  // entry check point + this block's cycles
    lwc1(f8, a1, anim::kIfQuat);
    v1 = 0x40000000;
    lwc1(f7, a1, 12);
    lwc1(f6, a1, 16);
    mtc1(v1, f5);
    lwc1(f0, a1, 20);
    v1 = 0x3F800000;
    mul_s(f12, f8, f8);
    mul_s(f2, f7, f7);
    mul_s(f1, f6, f6);
    mtc1(v1, f4);
    mtc1(zero, f3);
    mul_s(f11, f7, f6);
    v1 = 3;
    mul_s(f10, f6, f8);
    mul_s(f9, f8, f7);
    mul_s(f6, f0, f6);
    mul_s(f8, f0, f8);
    mul_s(f7, f0, f7);
    add_s(f0, f2, f1);
    adda_s(f3, f4);
    msub_s(f0, f5, f0);
    swc1(f0, a0, 0);
    add_s(f1, f12, f1);
    add_s(f0, f12, f2);
    adda_s(f3, f4);
    msub_s(f2, f5, f1);
    adda_s(f3, f4);
    add_s(f3, f9, f6);
    mul_s(f3, f5, f3);
    sub_s(f4, f10, f7);
    sub_s(f1, f9, f6);
    swc1(f3, a0, 4);
    mul_s(f3, f5, f1);
    mul_s(f4, f5, f4);
    swc1(f4, a0, 8);
    swc1(f3, a0, 16);
    add_s(f3, f11, f8);
    add_s(f1, f10, f7);
    swc1(f2, a0, 20);
    mul_s(f2, f5, f1);
    sub_s(f1, f11, f8);
    mul_s(f3, f5, f3);
    swc1(f3, a0, 24);
    mul_s(f1, f5, f1);
    swc1(f2, a0, 32);
    msub_s(f0, f5, f0);
    swc1(f1, a0, 36);
    swc1(f0, a0, 40);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
    sw(zero, a0, 56);
    sw(v1, a0, 12);
    lwc1(f0, a1, anim::kIfTrans);
    swc1(f0, a0, 48);
    lwc1(f0, a1, 28);
    swc1(f0, a0, 52);
    lwc1(f0, a1, 32);
    swc1(f0, a0, 56);
}

// 0x00464850 sub_464850 -- 1576 bytes; frame 0x10
// sub_464850 [RpHAnimKeyFrameInterpolate]: Interpolate callback: slerp of the two keyframes' quaternions (nlerp when
// they are nearly equal; the second negated for the short way) and lerp of the translations at t = $f12, with t taken
// relative to the two keyframe times.
void sub_464850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18};
    // 0x00464850
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f4, a1, 12);
    lwc1(f3, a2, 12);
    lwc1(f5, a1, anim::kKfTime);
    lwc1(f2, a2, anim::kKfTime);
    lwc1(f8, a1, anim::kKfQuat);
    lwc1(f7, a2, anim::kKfQuat);
    lwc1(f1, a1, anim::kKfTrans);
    mula_s(f4, f3);
    lwc1(f0, a2, anim::kKfTrans);
    sub_s(f4, f2, f5);
    sub_s(f2, f12, f5);
    div_s(f2, f2, f4);
    lwc1(f10, a1, 16);
    lwc1(f9, a2, 16);
    madda_s(f8, f7);
    lwc1(f13, a1, 20);
    lwc1(f11, a2, 20);
    sub_s(f0, f0, f1);
    madda_s(f10, f9);
    mtc1(zero, f6);
    madd_s(f3, f13, f11);
    adda_s(f6, f1);
    madd_s(f0, f2, f0);
    swc1(f0, a0, anim::kIfTrans);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    c_lt_s(f3, f6);
    adda_s(f6, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f2, f0);
    swc1(f0, a0, 28);
    lwc1(f1, a1, 32);
    lwc1(f0, a2, 32);
    adda_s(f6, f1);
    sub_s(f0, f0, f1);
    madd_s(f0, f2, f0);
    swc1(f0, a0, 32);
    if (cond(ctx)) {
        // 0x00464bc8
        charge(ctx, 14);
        lwc1(f0, a2, anim::kKfQuat);
        neg_s(f3, f3);
        neg_s(f0, f0);
        swc1(f0, a2, anim::kKfQuat);
        lwc1(f0, a2, 12);
        neg_s(f0, f0);
        swc1(f0, a2, 12);
        lwc1(f0, a2, 16);
        neg_s(f0, f0);
        swc1(f0, a2, 16);
        lwc1(f0, a2, 20);
        neg_s(f0, f0);
        swc1(f0, a2, 20);
        backedge(ctx);
    }
    // 0x004648ec
    charge(ctx, 9);
    a3 = 0x3F800000;
    v1 = 0x3F7F0000;
    mtc1(a3, f0);
    v1 = v1 | 0xBE77;
    mtc1(v1, f4);
    c_lt_s(f3, f4);
    sub_s(f1, f0, f2);
    if (cond(ctx)) {
        // 0x00464910
        charge(ctx, 8);
        swc1(f3, sp, 0xC);
        at = 0x3F800000;
        lw(a3, sp, 0xC);
        v1 = dsll32(a3, 1);
        v1 = dsrl32(v1, 1);
        at = slt(v1, at);
        if (at == 0) {
            // 0x00464c00
            charge(ctx, 2);
            if (i64(a3) <= 0) {
                // 0x00464c14
                charge(ctx, 5);
                v1 = 0x40490000;
                v1 = v1 | 0xFDB;
                mtc1(v1, f13);
                backedge(ctx);
            } else {
                // 0x00464c08
                charge(ctx, 3);
                mtc1(zero, f13);
                backedge(ctx);
            }
        L_00464a64:
            charge(ctx, 1);
            v1 = 0x2F2E0000;
        } else {
            // 0x00464930
            charge(ctx, 4);
            at = 0x3F000000;
            at = slt(v1, at);
            if (at == 0) {
                // 0x00464c28
                charge(ctx, 2);
                if (i64(a3) < 0) {
                    // 0x00464d54
                    charge(ctx, 71);
                    add_s(f3, f0, f3);
                    t1 = 0x3F000000;
                    a3 = 0x38110000;
                    v1 = 0x3A4F0000;
                    t0 = a3 | 0xEF08;
                    t2 = v1 | 0x7F04;
                    a3 = lui(0xBD24);
                    v1 = 0x3E4E0000;
                    mtc1(t1, f4);
                    t5 = a3 | 0x1146;
                    mtc1(t2, f15);
                    mul_s(f17, f4, f3);
                    t1 = v1 | 0xAA8;
                    v1 = lui(0xBEA6);
                    t4 = v1 | 0xB090;
                    v1 = 0x3E2A0000;
                    mtc1(zero, f14);
                    mtc1(t0, f16);
                    adda_s(f14, f15);
                    t0 = v1 | 0xAAAB;
                    v1 = 0x3D9D0000;
                    a3 = v1 | 0xC62E;
                    v1 = lui(0xBF30);
                    t3 = v1 | 0x3361;
                    v1 = 0x40010000;
                    t2 = v1 | 0x572D;
                    mtc1(a3, f9);
                    v1 = lui(0xC019);
                    mtc1(t1, f12);
                    mtc1(t5, f13);
                    a3 = 0x40000000;
                    t1 = v1 | 0xD139;
                    madd_s(f15, f16, f17);
                    v1 = 0x33A20000;
                    adda_s(f14, f13);
                    madd_s(f13, f17, f15);
                    adda_s(f14, f12);
                    mtc1(t0, f10);
                    mtc1(t4, f11);
                    madd_s(f12, f17, f13);
                    t0 = v1 | 0x2168;
                    adda_s(f14, f11);
                    v1 = 0x40490000;
                    madd_s(f11, f17, f12);
                    v1 = v1 | 0xFDA;
                    adda_s(f14, f10);
                    madd_s(f10, f17, f11);
                    mtc1(t3, f8);
                    mtc1(t2, f7);
                    adda_s(f14, f8);
                    madd_s(f8, f9, f17);
                    adda_s(f14, f7);
                    mtc1(t1, f6);
                    madd_s(f7, f17, f8);
                    adda_s(f14, f6);
                    madd_s(f6, f17, f7);
                    adda_s(f14, f0);
                    mul_s(f10, f17, f10);
                    madd_s(f0, f17, f6);
                    sqrt_s(f18, f17);
                    div_s(f0, f10, f0);
                    mtc1(v1, f3);
                    mul_s(f0, f0, f18);
                    mtc1(t0, f5);
                    mtc1(a3, f4);
                    sub_s(f0, f0, f5);
                    add_s(f0, f18, f0);
                    adda_s(f14, f3);
                    msub_s(f13, f4, f0);
                    backedge(ctx);
                } else {
                    // 0x00464c30
                    charge(ctx, 73);
                    sub_s(f3, f0, f3);
                    t1 = 0x3F000000;
                    a3 = 0x38110000;
                    v1 = si(-4096);
                    t0 = a3 | 0xEF08;
                    a3 = 0x3A4F0000;
                    mtc1(t1, f4);
                    t7 = a3 | 0x7F04;
                    a3 = lui(0xBD24);
                    mul_s(f15, f4, f3);
                    t1 = a3 | 0x1146;
                    a3 = 0x3E4E0000;
                    t6 = a3 | 0xAA8;
                    a3 = 0x3E2A0000;
                    t4 = a3 | 0xAAAB;
                    mtc1(t0, f14);
                    a3 = lui(0xBF30);
                    sqrt_s(f16, f15);
                    t2 = a3 | 0x3361;
                    t0 = lui(0xBEA6);
                    a3 = 0x40010000;
                    t5 = t0 | 0xB090;
                    t0 = 0x3D9D0000;
                    t3 = t0 | 0xC62E;
                    mtc1(t1, f11);
                    mtc1(t7, f13);
                    t1 = a3 | 0x572D;
                    mtc1(zero, f12);
                    a3 = lui(0xC019);
                    t0 = a3 | 0xD139;
                    adda_s(f12, f13);
                    a3 = 0x40000000;
                    madd_s(f13, f14, f15);
                    adda_s(f12, f11);
                    mtc1(t6, f10);
                    madd_s(f11, f15, f13);
                    adda_s(f12, f10);
                    mtc1(t5, f5);
                    madd_s(f10, f15, f11);
                    adda_s(f12, f5);
                    mtc1(t4, f9);
                    madd_s(f10, f15, f10);
                    adda_s(f12, f9);
                    madd_s(f9, f15, f10);
                    mtc1(t2, f7);
                    mtc1(t3, f8);
                    adda_s(f12, f7);
                    mtc1(t1, f6);
                    madd_s(f7, f8, f15);
                    adda_s(f12, f6);
                    mtc1(t0, f4);
                    madd_s(f6, f15, f7);
                    adda_s(f12, f4);
                    madd_s(f4, f15, f6);
                    adda_s(f12, f0);
                    madd_s(f0, f15, f4);
                    mul_s(f9, f15, f9);
                    div_s(f6, f9, f0);
                    mtc1(a3, f3);
                    swc1(f16, sp, 0x8);
                    lw(a3, sp, 0x8);
                    adda_s(f12, f15);
                    v1 = a3 & v1;
                    sw(v1, sp, 0x4);
                    lwc1(f5, sp, 0x4);
                    add_s(f0, f16, f5);
                    msub_s(f4, f5, f5);
                    div_s(f0, f4, f0);
                    adda_s(f12, f0);
                    madd_s(f0, f6, f16);
                    add_s(f0, f5, f0);
                    mul_s(f13, f3, f0);
                    backedge(ctx);
                }
                goto L_00464a64;
            }
            // 0x00464940
            charge(ctx, 5);
            at = 0x23000000;
            at = at | 0x1;
            at = slt(v1, at);
            if (at == 0) {
                // 0x00464968
                charge(ctx, 63);
                v1 = 0x38110000;
                a3 = v1 | 0xEF08;
                v1 = 0x3A4F0000;
                t2 = v1 | 0x7F04;
                v1 = lui(0xBD24);
                t0 = v1 | 0x1146;
                v1 = 0x3E4E0000;
                t1 = v1 | 0xAA8;
                mul_s(f17, f3, f3);
                v1 = lui(0xBEA6);
                mtc1(a3, f16);
                mtc1(t2, f15);
                a3 = v1 | 0xB090;
                mtc1(zero, f14);
                v1 = 0x3E2A0000;
                mtc1(t0, f13);
                adda_s(f14, f15);
                t0 = v1 | 0xAAAB;
                madd_s(f15, f16, f17);
                v1 = 0x3D9D0000;
                mtc1(a3, f11);
                adda_s(f14, f13);
                a3 = v1 | 0xC62E;
                v1 = lui(0xBF30);
                v1 = v1 | 0x3361;
                mtc1(v1, f8);
                mtc1(t1, f12);
                madd_s(f13, f17, f15);
                v1 = 0x40010000;
                adda_s(f14, f12);
                madd_s(f12, f17, f13);
                adda_s(f14, f11);
                mtc1(a3, f9);
                mtc1(t0, f10);
                a3 = v1 | 0x572D;
                madd_s(f11, f17, f12);
                v1 = lui(0xC019);
                adda_s(f14, f10);
                v1 = v1 | 0xD139;
                madd_s(f10, f17, f11);
                adda_s(f14, f8);
                mtc1(v1, f6);
                mtc1(a3, f7);
                madd_s(f8, f9, f17);
                v1 = 0x33A20000;
                adda_s(f14, f7);
                a3 = v1 | 0x2168;
                madd_s(f7, f17, f8);
                v1 = 0x3FC90000;
                adda_s(f14, f6);
                v1 = v1 | 0xFDA;
                madd_s(f6, f17, f7);
                adda_s(f14, f0);
                mul_s(f10, f17, f10);
                madd_s(f0, f17, f6);
                div_s(f0, f10, f0);
                mtc1(a3, f5);
                mtc1(v1, f4);
                adda_s(f14, f5);
                msub_s(f0, f3, f0);
                sub_s(f0, f3, f0);
                sub_s(f13, f4, f0);
                goto L_00464a64;
            }
            // 0x00464954
            charge(ctx, 5);
            v1 = 0x3FC90000;
            v1 = v1 | 0xFDB;
            mtc1(v1, f13);
            v1 = 0x2F2E0000;
        }
        // 0x00464a68
        charge(ctx, 67);
        t0 = v1 | 0xC9D3;
        mul_s(f5, f13, f13);
        v1 = lui(0xB2D7);
        t2 = v1 | 0x2F34;
        v1 = 0x36380000;
        a3 = v1 | 0xEF1B;
        v1 = lui(0xB950);
        t1 = v1 | 0xD01;
        mtc1(t2, f11);
        v1 = 0x3C080000;
        mtc1(zero, f10);
        mtc1(t0, f12);
        adda_s(f10, f11);
        t0 = v1 | 0x8889;
        mtc1(a3, f9);
        v1 = lui(0xBE2A);
        madd_s(f4, f12, f5);
        a3 = v1 | 0xAAAB;
        adda_s(f10, f9);
        v1 = 0x3F800000;
        mtc1(t1, f8);
        madd_s(f4, f5, f4);
        adda_s(f10, f8);
        mtc1(t0, f7);
        madd_s(f4, f5, f4);
        adda_s(f10, f7);
        mtc1(a3, f6);
        madd_s(f4, f5, f4);
        adda_s(f10, f6);
        madd_s(f4, f5, f4);
        mul_s(f3, f5, f13);
        adda_s(f10, f13);
        madd_s(f3, f3, f4);
        mtc1(v1, f0);
        mul_s(f4, f2, f13);
        div_s(f5, f0, f3);
        mul_s(f3, f1, f13);
        mul_s(f2, f3, f3);
        adda_s(f10, f11);
        madd_s(f0, f12, f2);
        adda_s(f10, f9);
        madd_s(f0, f2, f0);
        adda_s(f10, f8);
        madd_s(f0, f2, f0);
        adda_s(f10, f7);
        madd_s(f0, f2, f0);
        adda_s(f10, f6);
        madd_s(f1, f2, f0);
        mul_s(f0, f2, f3);
        adda_s(f10, f3);
        madd_s(f0, f0, f1);
        mul_s(f1, f0, f5);
        mul_s(f3, f4, f4);
        adda_s(f10, f11);
        madd_s(f0, f12, f3);
        adda_s(f10, f9);
        madd_s(f0, f3, f0);
        adda_s(f10, f8);
        madd_s(f0, f3, f0);
        adda_s(f10, f7);
        madd_s(f0, f3, f0);
        adda_s(f10, f6);
        madd_s(f2, f3, f0);
        mul_s(f0, f3, f4);
        adda_s(f10, f4);
        madd_s(f0, f0, f2);
        mul_s(f2, f0, f5);
    }
    // 0x00464b74
    charge(ctx, 21);
    lwc1(f0, a2, 8);
    lwc1(f3, a1, 8);
    mula_s(f2, f0);
    madd_s(f0, f1, f3);
    swc1(f0, a0, 8);
    lwc1(f0, a2, 12);
    lwc1(f3, a1, 12);
    mula_s(f2, f0);
    madd_s(f0, f1, f3);
    swc1(f0, a0, 12);
    lwc1(f0, a2, 16);
    lwc1(f3, a1, 16);
    mula_s(f2, f0);
    madd_s(f0, f1, f3);
    swc1(f0, a0, 16);
    lwc1(f0, a2, 20);
    lwc1(f3, a1, 20);
    mula_s(f2, f0);
    madd_s(f0, f1, f3);
    swc1(f0, a0, 20);
    // 0x00464e70
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00464E80 sub_464E80 -- 1564 bytes; frame 0x10
// sub_464E80 [RpHAnimKeyFrameBlend]: Blend callback: slerp / lerp of two interpolated frames with weight $f12.
void sub_464E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18};
    // 0x00464e80
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f4, a1, 12);
    lwc1(f1, a2, 12);
    lwc1(f6, a1, anim::kIfQuat);
    lwc1(f5, a2, anim::kIfQuat);
    lwc1(f2, a1, anim::kIfTrans);
    lwc1(f0, a2, anim::kIfTrans);
    lwc1(f8, a1, 16);
    mula_s(f4, f1);
    lwc1(f7, a2, 16);
    madda_s(f6, f5);
    lwc1(f10, a1, 20);
    lwc1(f9, a2, 20);
    sub_s(f0, f0, f2);
    madda_s(f8, f7);
    mtc1(zero, f3);
    madd_s(f1, f10, f9);
    adda_s(f3, f2);
    madd_s(f0, f12, f0);
    swc1(f0, a0, anim::kIfTrans);
    lwc1(f2, a1, 28);
    lwc1(f0, a2, 28);
    c_lt_s(f1, f3);
    adda_s(f3, f2);
    sub_s(f0, f0, f2);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 28);
    lwc1(f2, a1, 32);
    lwc1(f0, a2, 32);
    adda_s(f3, f2);
    sub_s(f0, f0, f2);
    madd_s(f0, f12, f0);
    swc1(f0, a0, 32);
    if (cond(ctx)) {
        // 0x004651e0
        charge(ctx, 14);
        lwc1(f0, a2, anim::kIfQuat);
        neg_s(f1, f1);
        neg_s(f0, f0);
        swc1(f0, a2, anim::kIfQuat);
        lwc1(f0, a2, 12);
        neg_s(f0, f0);
        swc1(f0, a2, 12);
        lwc1(f0, a2, 16);
        neg_s(f0, f0);
        swc1(f0, a2, 16);
        lwc1(f0, a2, 20);
        neg_s(f0, f0);
        swc1(f0, a2, 20);
        backedge(ctx);
    }
    // 0x00464f08
    charge(ctx, 9);
    a3 = 0x3F800000;
    v1 = 0x3F7F0000;
    mtc1(a3, f0);
    v1 = v1 | 0xBE77;
    mtc1(v1, f3);
    c_lt_s(f1, f3);
    sub_s(f2, f0, f12);
    if (cond(ctx)) {
        // 0x00464f2c
        charge(ctx, 8);
        swc1(f1, sp, 0xC);
        at = 0x3F800000;
        lw(a3, sp, 0xC);
        v1 = dsll32(a3, 1);
        v1 = dsrl32(v1, 1);
        at = slt(v1, at);
        if (at == 0) {
            // 0x00465218
            charge(ctx, 2);
            if (i64(a3) <= 0) {
                // 0x0046522c
                charge(ctx, 5);
                v1 = 0x40490000;
                v1 = v1 | 0xFDB;
                mtc1(v1, f14);
                backedge(ctx);
            } else {
                // 0x00465220
                charge(ctx, 3);
                mtc1(zero, f14);
                backedge(ctx);
            }
        L_0046507c:
            charge(ctx, 1);
            v1 = 0x2F2E0000;
        } else {
            // 0x00464f4c
            charge(ctx, 4);
            at = 0x3F000000;
            at = slt(v1, at);
            if (at == 0) {
                // 0x00465240
                charge(ctx, 2);
                if (i64(a3) < 0) {
                    // 0x00465374
                    charge(ctx, 72);
                    add_s(f1, f0, f1);
                    t1 = 0x3F000000;
                    a3 = 0x38110000;
                    v1 = 0x3A4F0000;
                    t0 = a3 | 0xEF08;
                    t2 = v1 | 0x7F04;
                    a3 = lui(0xBD24);
                    v1 = 0x3E4E0000;
                    mtc1(t1, f3);
                    t5 = a3 | 0x1146;
                    mtc1(t2, f15);
                    mul_s(f17, f3, f1);
                    t1 = v1 | 0xAA8;
                    v1 = lui(0xBEA6);
                    t4 = v1 | 0xB090;
                    v1 = 0x3E2A0000;
                    mtc1(zero, f14);
                    mtc1(t0, f16);
                    adda_s(f14, f15);
                    t0 = v1 | 0xAAAB;
                    v1 = 0x3D9D0000;
                    a3 = v1 | 0xC62E;
                    v1 = lui(0xBF30);
                    t3 = v1 | 0x3361;
                    v1 = 0x40010000;
                    t2 = v1 | 0x572D;
                    mtc1(a3, f8);
                    v1 = lui(0xC019);
                    mtc1(t1, f11);
                    mtc1(t5, f13);
                    a3 = 0x40000000;
                    t1 = v1 | 0xD139;
                    madd_s(f15, f16, f17);
                    v1 = 0x33A20000;
                    adda_s(f14, f13);
                    madd_s(f13, f17, f15);
                    adda_s(f14, f11);
                    mtc1(t0, f9);
                    mtc1(t4, f10);
                    madd_s(f11, f17, f13);
                    t0 = v1 | 0x2168;
                    adda_s(f14, f10);
                    v1 = 0x40490000;
                    madd_s(f10, f17, f11);
                    v1 = v1 | 0xFDA;
                    adda_s(f14, f9);
                    madd_s(f9, f17, f10);
                    mtc1(t3, f7);
                    mtc1(t2, f6);
                    adda_s(f14, f7);
                    madd_s(f7, f8, f17);
                    adda_s(f14, f6);
                    mtc1(t1, f5);
                    madd_s(f6, f17, f7);
                    adda_s(f14, f5);
                    madd_s(f5, f17, f6);
                    adda_s(f14, f0);
                    mul_s(f9, f17, f9);
                    madd_s(f0, f17, f5);
                    sqrt_s(f18, f17);
                    div_s(f0, f9, f0);
                    mtc1(v1, f1);
                    mul_s(f0, f0, f18);
                    mtc1(t0, f4);
                    mtc1(a3, f3);
                    sub_s(f0, f0, f4);
                    add_s(f0, f18, f0);
                    adda_s(f14, f1);
                    msub_s(f14, f3, f0);
                    backedge(ctx);
                } else {
                    // 0x00465248
                    charge(ctx, 75);
                    sub_s(f1, f0, f1);
                    t1 = 0x3F000000;
                    a3 = 0x38110000;
                    v1 = si(-4096);
                    t0 = a3 | 0xEF08;
                    a3 = 0x3A4F0000;
                    mtc1(t1, f3);
                    t7 = a3 | 0x7F04;
                    a3 = lui(0xBD24);
                    mul_s(f15, f3, f1);
                    t1 = a3 | 0x1146;
                    a3 = 0x3E4E0000;
                    t6 = a3 | 0xAA8;
                    a3 = 0x3E2A0000;
                    t4 = a3 | 0xAAAB;
                    mtc1(t0, f14);
                    a3 = lui(0xBF30);
                    sqrt_s(f16, f15);
                    t2 = a3 | 0x3361;
                    t0 = lui(0xBEA6);
                    a3 = 0x40010000;
                    t5 = t0 | 0xB090;
                    t0 = 0x3D9D0000;
                    t3 = t0 | 0xC62E;
                    mtc1(t1, f10);
                    mtc1(t7, f13);
                    t1 = a3 | 0x572D;
                    mtc1(zero, f11);
                    a3 = lui(0xC019);
                    t0 = a3 | 0xD139;
                    adda_s(f11, f13);
                    a3 = 0x40000000;
                    madd_s(f13, f14, f15);
                    adda_s(f11, f10);
                    mtc1(t6, f9);
                    madd_s(f10, f15, f13);
                    adda_s(f11, f9);
                    mtc1(t5, f4);
                    madd_s(f9, f15, f10);
                    adda_s(f11, f4);
                    mtc1(t4, f8);
                    madd_s(f9, f15, f9);
                    adda_s(f11, f8);
                    madd_s(f8, f15, f9);
                    mtc1(t2, f6);
                    mtc1(t3, f7);
                    adda_s(f11, f6);
                    mtc1(t1, f5);
                    madd_s(f6, f7, f15);
                    adda_s(f11, f5);
                    mtc1(t0, f3);
                    madd_s(f5, f15, f6);
                    adda_s(f11, f3);
                    madd_s(f3, f15, f5);
                    adda_s(f11, f0);
                    madd_s(f0, f15, f3);
                    mul_s(f8, f15, f8);
                    div_s(f5, f8, f0);
                    mtc1(a3, f1);
                    swc1(f16, sp, 0x8);
                    lw(a3, sp, 0x8);
                    adda_s(f11, f15);
                    v1 = a3 & v1;
                    sw(v1, sp, 0x4);
                    lwc1(f4, sp, 0x4);
                    add_s(f0, f16, f4);
                    msub_s(f3, f4, f4);
                    div_s(f0, f3, f0);
                    adda_s(f11, f0);
                    madd_s(f0, f5, f16);
                    add_s(f0, f4, f0);
                    mul_s(f14, f1, f0);
                    backedge(ctx);
                }
                goto L_0046507c;
            }
            // 0x00464f5c
            charge(ctx, 5);
            at = 0x23000000;
            at = at | 0x1;
            at = slt(v1, at);
            if (at == 0) {
                // 0x00464f84
                charge(ctx, 62);
                v1 = 0x38110000;
                a3 = v1 | 0xEF08;
                v1 = 0x3A4F0000;
                t2 = v1 | 0x7F04;
                v1 = lui(0xBD24);
                t0 = v1 | 0x1146;
                v1 = 0x3E4E0000;
                t1 = v1 | 0xAA8;
                mul_s(f17, f1, f1);
                v1 = lui(0xBEA6);
                mtc1(a3, f16);
                mtc1(t2, f15);
                a3 = v1 | 0xB090;
                mtc1(zero, f14);
                v1 = 0x3E2A0000;
                mtc1(t0, f13);
                adda_s(f14, f15);
                t0 = v1 | 0xAAAB;
                madd_s(f15, f16, f17);
                v1 = 0x3D9D0000;
                mtc1(a3, f10);
                adda_s(f14, f13);
                a3 = v1 | 0xC62E;
                v1 = lui(0xBF30);
                v1 = v1 | 0x3361;
                mtc1(v1, f7);
                mtc1(t1, f11);
                madd_s(f13, f17, f15);
                v1 = 0x40010000;
                adda_s(f14, f11);
                madd_s(f11, f17, f13);
                adda_s(f14, f10);
                mtc1(a3, f8);
                mtc1(t0, f9);
                a3 = v1 | 0x572D;
                madd_s(f10, f17, f11);
                v1 = lui(0xC019);
                adda_s(f14, f9);
                v1 = v1 | 0xD139;
                madd_s(f9, f17, f10);
                adda_s(f14, f7);
                mtc1(v1, f5);
                mtc1(a3, f6);
                madd_s(f7, f8, f17);
                v1 = 0x33A20000;
                adda_s(f14, f6);
                a3 = v1 | 0x2168;
                madd_s(f6, f17, f7);
                v1 = 0x3FC90000;
                adda_s(f14, f5);
                v1 = v1 | 0xFDA;
                madd_s(f5, f17, f6);
                adda_s(f14, f0);
                mul_s(f9, f17, f9);
                madd_s(f0, f17, f5);
                div_s(f0, f9, f0);
                mtc1(a3, f4);
                mtc1(v1, f3);
                adda_s(f14, f4);
                msub_s(f0, f1, f0);
                sub_s(f0, f1, f0);
                sub_s(f14, f3, f0);
                goto L_0046507c;
            }
            // 0x00464f70
            charge(ctx, 5);
            v1 = 0x3FC90000;
            v1 = v1 | 0xFDB;
            mtc1(v1, f14);
            v1 = 0x2F2E0000;
        }
        // 0x00465080
        charge(ctx, 67);
        t0 = v1 | 0xC9D3;
        mul_s(f4, f14, f14);
        v1 = lui(0xB2D7);
        t2 = v1 | 0x2F34;
        v1 = 0x36380000;
        a3 = v1 | 0xEF1B;
        v1 = lui(0xB950);
        t1 = v1 | 0xD01;
        mtc1(t2, f11);
        v1 = 0x3C080000;
        mtc1(zero, f10);
        mtc1(t0, f13);
        adda_s(f10, f11);
        t0 = v1 | 0x8889;
        mtc1(a3, f9);
        v1 = lui(0xBE2A);
        madd_s(f3, f13, f4);
        a3 = v1 | 0xAAAB;
        adda_s(f10, f9);
        v1 = 0x3F800000;
        mtc1(t1, f8);
        madd_s(f3, f4, f3);
        adda_s(f10, f8);
        mtc1(t0, f7);
        madd_s(f3, f4, f3);
        adda_s(f10, f7);
        mtc1(a3, f6);
        madd_s(f3, f4, f3);
        adda_s(f10, f6);
        madd_s(f3, f4, f3);
        mul_s(f1, f4, f14);
        adda_s(f10, f14);
        madd_s(f1, f1, f3);
        mtc1(v1, f0);
        mul_s(f3, f2, f14);
        div_s(f5, f0, f1);
        mul_s(f2, f3, f3);
        adda_s(f10, f11);
        madd_s(f0, f13, f2);
        adda_s(f10, f9);
        madd_s(f0, f2, f0);
        adda_s(f10, f8);
        madd_s(f0, f2, f0);
        adda_s(f10, f7);
        madd_s(f0, f2, f0);
        adda_s(f10, f6);
        madd_s(f1, f2, f0);
        mul_s(f0, f2, f3);
        adda_s(f10, f3);
        madd_s(f0, f0, f1);
        mul_s(f4, f12, f14);
        mul_s(f2, f0, f5);
        mul_s(f3, f4, f4);
        adda_s(f10, f11);
        madd_s(f0, f13, f3);
        adda_s(f10, f9);
        madd_s(f0, f3, f0);
        adda_s(f10, f8);
        madd_s(f0, f3, f0);
        adda_s(f10, f7);
        madd_s(f0, f3, f0);
        adda_s(f10, f6);
        madd_s(f1, f3, f0);
        mul_s(f0, f3, f4);
        adda_s(f10, f4);
        madd_s(f0, f0, f1);
        mul_s(f12, f0, f5);
    }
    // 0x0046518c
    charge(ctx, 21);
    lwc1(f0, a2, 8);
    lwc1(f1, a1, 8);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 8);
    lwc1(f0, a2, 12);
    lwc1(f1, a1, 12);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 12);
    lwc1(f0, a2, 16);
    lwc1(f1, a1, 16);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 16);
    lwc1(f0, a2, 20);
    lwc1(f1, a1, 20);
    mula_s(f12, f0);
    madd_s(f0, f2, f1);
    swc1(f0, a0, 20);
    // 0x00465494
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x004654A0 sub_4654A0 -- 232 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4654A0 [RpHAnimKeyFrameStreamRead]: Stream-read callback: per 36-byte keyframe the time + quaternion +
// translation (8 reals) and the previous frame's byte offset (turned into a pointer).
void sub_4654A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004654a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, anim::kAnmNumFrames);
    lw(s0, a1, anim::kAnmFrames);
    v0 = slt(0, v0);
    s2 = 0;
    if (v0 != 0) {
        // 0x004654e0
        charge(ctx, 1);
        s1 = s0;
        for (;;) {
            // 0x004654e4
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(s1, 4);
            a2 = 32;
            jal(ctx, 0x4654ECu, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
            if (v0 == 0) {
                // 0x004654fc_4 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = 0;
                // 0x00465568 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x70);
                return;
            }
            // 0x00465504
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(sp, 0x6C);
            a2 = 4;
            jal(ctx, 0x46550Cu, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 == 0) {
                goto L_00465564;
            }
            // 0x0046551c
            charge(ctx, 16);
            lw(v1, sp, 0x6C);
            v0 = 0x38E30000;
            v0 = v0 | 0x8E39;
            multu(zero, v0, v1);
            mfhi(v0);
            s2 = addiu(s2, 1);
            v1 = srl(v0, 3);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            sw(v0, s1, 0);
            lw(v0, s3, anim::kAnmNumFrames);
            v0 = slt(s2, v0);
            s1 = addiu(s1, 36);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046555c
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004654d8
    charge(ctx, 2);
    v0 = s3;
    // 0x00465568 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00465564:
    charge(ctx, 1);
    v0 = 0;
    // 0x00465568 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00465590 sub_465590 -- 200 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_465590 [RpHAnimKeyFrameStreamWrite]: Stream-write callback: per keyframe the 8 reals and the previous frame's
// byte offset.
void sub_465590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465590
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    lw(v0, a0, anim::kAnmNumFrames);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = slt(0, v0);
    lw(s0, a0, anim::kAnmFrames);
    s2 = 0;
    if (v0 != 0) {
        // 0x004655d0
        charge(ctx, 1);
        s1 = s0;
        for (;;) {
            // 0x004655d4
            charge(ctx, 6);
            a0 = s3;
            a1 = addiu(s1, 4);
            a2 = 32;
            jal(ctx, 0x4655DCu, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
            if (v0 == 0) {
                // 0x004655ec_4 (its only goto: the block written out here)
                charge(ctx, 2);
                v0 = 0;
                // 0x00465638 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x70);
                return;
            }
            // 0x004655f4
            charge(ctx, 9);
            lw(v0, s1, 0);
            a0 = s3;
            a1 = addiu(sp, 0x6C);
            a2 = 4;
            v0 = subu(v0, s0);
            link(ctx, 0x465608u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x6C);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 == 0) {
                goto L_00465634;
            }
            // 0x00465618
            charge(ctx, 5);
            lw(v0, s4, anim::kAnmNumFrames);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v0);
            s1 = addiu(s1, 36);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046562c
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004655c8
    charge(ctx, 2);
    v0 = 1;
    // 0x00465638 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00465634:
    charge(ctx, 1);
    v0 = 0;
    // 0x00465638 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00465660 sub_465660 -- 16 bytes; leaf frame (no stack)
// sub_465660 [RpHAnimKeyFrameStreamGetSize]: Stream-size callback: 36 bytes per keyframe.
void sub_465660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00465660
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, anim::kAnmNumFrames);
    v1 = 36;
    mult(v0, v1, v0);
}

// 0x00465670 sub_465670 -- 352 bytes; frame 0x20
// sub_465670 [RpHAnimKeyFrameMulRecip]: Mul-recip callback: frame $a0 times the inverse of $a1 (conjugate quaternion
// product, translation difference).
void sub_465670(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10};
    // 0x00465670
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lwc1(f5, a1, 12);
    lwc1(f4, a1, anim::kKfQuat);
    lwc1(f3, a1, 16);
    lwc1(f2, a1, 20);
    lwc1(f8, sp, 0x14);
    mula_s(f5, f5);
    madda_s(f4, f4);
    madda_s(f3, f3);
    lwc1(f9, sp, 0x18);
    lwc1(f10, sp, 0x1C);
    mtc1(zero, f0);
    madd_s(f1, f2, f2);
    c_le_s(f1, f0);
    lwc1(f7, sp, 0x10);
    if (!cond(ctx)) {
        // 0x004656b0
        charge(ctx, 9);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f1);
        mul_s(f10, f2, f0);
        neg_s(f0, f0);
        mul_s(f7, f4, f0);
        mul_s(f8, f5, f0);
        mul_s(f9, f3, f0);
    }
    // 0x004656d4
    charge(ctx, 63);
    lwc1(f3, a0, 20);
    lwc1(f5, a0, 12);
    lwc1(f6, a0, anim::kKfQuat);
    lwc1(f4, a0, 16);
    mtc1(zero, f2);
    mul_s(f0, f10, f3);
    mula_s(f8, f5);
    madda_s(f7, f6);
    madd_s(f1, f9, f4);
    sub_s(f0, f0, f1);
    mula_s(f8, f4);
    swc1(f0, a0, 20);
    msub_s(f0, f9, f5);
    swc1(f0, a0, anim::kKfQuat);
    mula_s(f9, f6);
    msub_s(f0, f7, f4);
    swc1(f0, a0, 12);
    mula_s(f7, f5);
    msub_s(f0, f8, f6);
    swc1(f0, a0, 16);
    lwc1(f0, a0, anim::kKfQuat);
    swc1(f6, sp, 0x0);
    swc1(f5, sp, 0x4);
    swc1(f4, sp, 0x8);
    swc1(f3, sp, 0xC);
    adda_s(f2, f0);
    madd_s(f0, f6, f10);
    swc1(f0, a0, anim::kKfQuat);
    lwc1(f0, a0, 12);
    adda_s(f2, f0);
    madd_s(f0, f5, f10);
    swc1(f0, a0, 12);
    lwc1(f0, a0, 16);
    adda_s(f2, f0);
    madd_s(f0, f4, f10);
    swc1(f0, a0, 16);
    lwc1(f0, a0, anim::kKfQuat);
    adda_s(f2, f0);
    madd_s(f0, f7, f3);
    swc1(f0, a0, anim::kKfQuat);
    lwc1(f0, a0, 12);
    adda_s(f2, f0);
    madd_s(f0, f8, f3);
    swc1(f0, a0, 12);
    lwc1(f0, a0, 16);
    adda_s(f2, f0);
    madd_s(f0, f9, f3);
    swc1(f0, a0, 16);
    lwc1(f1, a1, anim::kKfTrans);
    lwc1(f0, a0, anim::kKfTrans);
    sub_s(f0, f0, f1);
    swc1(f0, a0, anim::kKfTrans);
    lwc1(f1, a1, 28);
    lwc1(f0, a0, 28);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 28);
    lwc1(f1, a1, 32);
    lwc1(f0, a0, 32);
    sub_s(f0, f0, f1);
    swc1(f0, a0, 32);
    sp = addiu(sp, 0x20);
}

// 0x004657D0 sub_4657D0 -- 344 bytes; leaf frame (no stack)
// sub_4657D0 [RpHAnimKeyFrameAdd]: Add callback: quaternion product and translation sum.
void sub_4657D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004657d0
    enter(ctx, 86);  // entry check point + this block's cycles
    lwc1(f2, a1, 20);
    lwc1(f1, a2, 20);
    lwc1(f4, a1, 12);
    lwc1(f3, a2, 12);
    lwc1(f6, a1, anim::kKfQuat);
    lwc1(f5, a2, anim::kKfQuat);
    lwc1(f8, a1, 16);
    lwc1(f7, a2, 16);
    mul_s(f1, f2, f1);
    mula_s(f4, f3);
    madda_s(f6, f5);
    madd_s(f3, f8, f7);
    sub_s(f1, f1, f3);
    swc1(f1, a0, 20);
    lwc1(f2, a1, 12);
    lwc1(f1, a2, 16);
    lwc1(f4, a1, 16);
    lwc1(f3, a2, 12);
    mtc1(zero, f0);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, anim::kKfQuat);
    lwc1(f2, a1, 16);
    lwc1(f1, a2, anim::kKfQuat);
    lwc1(f4, a1, anim::kKfQuat);
    lwc1(f3, a2, 16);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, 12);
    lwc1(f2, a1, anim::kKfQuat);
    lwc1(f1, a2, 12);
    lwc1(f4, a1, 12);
    lwc1(f3, a2, anim::kKfQuat);
    mula_s(f2, f1);
    msub_s(f1, f4, f3);
    swc1(f1, a0, 16);
    lwc1(f1, a0, anim::kKfQuat);
    lwc1(f3, a2, anim::kKfQuat);
    lwc1(f2, a1, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, anim::kKfQuat);
    lwc1(f1, a0, 12);
    lwc1(f3, a2, 12);
    lwc1(f2, a1, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 12);
    lwc1(f1, a0, 16);
    lwc1(f3, a2, 16);
    lwc1(f2, a1, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 16);
    lwc1(f1, a0, anim::kKfQuat);
    lwc1(f3, a1, anim::kKfQuat);
    lwc1(f2, a2, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, anim::kKfQuat);
    lwc1(f1, a0, 12);
    lwc1(f3, a1, 12);
    lwc1(f2, a2, 20);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    swc1(f1, a0, 12);
    lwc1(f1, a0, 16);
    lwc1(f3, a1, 16);
    lwc1(f2, a2, 20);
    adda_s(f0, f1);
    madd_s(f0, f3, f2);
    swc1(f0, a0, 16);
    lwc1(f1, a1, anim::kKfTrans);
    lwc1(f0, a2, anim::kKfTrans);
    add_s(f0, f1, f0);
    swc1(f0, a0, anim::kKfTrans);
    lwc1(f1, a1, 28);
    lwc1(f0, a2, 28);
    add_s(f0, f1, f0);
    swc1(f0, a0, 28);
    lwc1(f1, a1, 32);
    lwc1(f0, a2, 32);
    add_s(f0, f1, f0);
    swc1(f0, a0, 32);
}

// 0x00465930 sub_465930 -- 196 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_465930 [hAnimAttachFrameCB]: Child-frame callback of RpHAnimHierarchyAttach: stores frame $a0 in every node of
// hierarchy $a1 whose id is the frame's HAnim id, updates the frame and recurses into its children.
void sub_465930(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465930
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(v0, a1, anim::kHierNumNodes);
    at = slt(0, v0);
    s1 = 0;
    if (at != 0) {
        // 0x00465968
        charge(ctx, 1);
        s0 = 0;
        for (;;) {
            // 0x0046596c
            charge(ctx, 7);
            lw(v0, s2, anim::kHierNodeInfo);
            s5 = addu(v0, s0);
            lw(s4, s5, 0);
            a0 = s3;
            jal(ctx, 0x465978u, gen::fn_sub_466720_00466720);  // [RpHAnimFrameGetID]
            if (s4 == v0) {
                // 0x004659c4
                charge(ctx, 2);
                sw(s3, s5, 12);
                backedge(ctx);
            }
            // 0x00465988
            charge(ctx, 5);
            lw(v0, s2, anim::kHierNumNodes);
            s1 = addiu(s1, 1);
            v0 = slt(s1, v0);
            s0 = addiu(s0, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046599c
        charge(ctx, 1);
    }
    // 0x004659a0
    charge(ctx, 9);
    a0 = s3;
    jal(ctx, 0x4659A0u, gen::fn_sub_4CB270_004cb270);  // [RwFrameUpdateObjects]
    a1 = 0x460000;
    a2 = s2;
    a0 = s3;
    a1 = addiu(a1, 22832);  // &sub_465930
    jal(ctx, 0x4659B4u, gen::fn_sub_4CB6E0_004cb6e0);  // [RwFrameForAllChildren]
    v0 = s3;
    // 0x004659d0
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

// 0x00465A00 sub_465A00 -- 220 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// sub_465A00 [hAnimOpen]: RpHAnim's engine-open callback: creates the 36-byte hierarchy free list (0x7CE734) and
// registers the standard keyframe scheme (id 1, 36-byte keyframes and frames).
void sub_465A00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465a00
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a2 = 4;
    lw(a1, gp, -20952);  // 0x7CDB18
    s0 = a0;
    lw(a3, gp, -20948);  // 0x7CDB1C
    a0 = 36;
    t0 = addiu(t0, -15408);  // &0x95C3D0
    t1 = v0 | 0x11E;
    jal(ctx, 0x465A2Cu, gen::fn_sub_4C3B60_004c3b60);  // [RwFreeListCreate]
    sw(v0, gp, -17852);  // 0x7CE734 RpHAnim: hierarchy free list
    if (v0 == 0) {
        // 0x00465ac4
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    }
    // 0x00465a3c
    charge(ctx, 34);
    v0 = 1;
    v1 = 0x460000;
    sw(v0, sp, 0x20);
    v1 = addiu(v1, 18272);  // &sub_464760
    v0 = 36;
    sw(v1, sp, 0x2C);
    sw(v0, sp, 0x24);
    v1 = 0x460000;
    sw(v0, sp, 0x28);
    v1 = addiu(v1, 18512);  // &sub_464850
    v0 = 0x460000;
    sw(v1, sp, 0x34);
    v0 = addiu(v0, 20096);  // &sub_464E80
    v1 = 0x460000;
    sw(v0, sp, 0x30);
    v1 = addiu(v1, 22128);  // &sub_465670
    v0 = 0x460000;
    sw(v1, sp, 0x3C);
    v0 = addiu(v0, 22480);  // &sub_4657D0
    v1 = 0x460000;
    sw(v0, sp, 0x38);
    v1 = addiu(v1, 21904);  // &sub_465590
    v0 = 0x460000;
    sw(v1, sp, 0x44);
    v0 = addiu(v0, 21664);  // &sub_4654A0
    a0 = addiu(sp, 0x20);
    sw(v0, sp, 0x40);
    v0 = 0x460000;
    sw(zero, sp, 0x4C);
    v0 = addiu(v0, 22112);  // &sub_465660
    link(ctx, 0x465AB4u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x48);
    call(ctx, gen::fn_sub_4B6680_004b6680);  // [RtAnimRegisterInterpolationScheme]
    v0 = s0;
    // 0x00465acc
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00465AE0 sub_465AE0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_465AE0 [hAnimClose]: RpHAnim's engine-close callback: destroys the hierarchy free list.
void sub_465AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465ae0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -17852);  // 0x7CE734 RpHAnim: hierarchy free list
    if (a0 != 0) {
        // 0x00465afc
        charge(ctx, 3);
        jal(ctx, 0x465AFCu, gen::fn_sub_4C3C30_004c3c30);  // [RwFreeListDestroy]
        sw(zero, gp, -17852);  // 0x7CE734 RpHAnim: hierarchy free list
    }
    // 0x00465b08 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00465B20 sub_465B20 -- 28 bytes; leaf frame (no stack)
// sub_465B20 [hAnimFrameCtor]: Frame constructor: the 8-byte HAnim extension = {id -1, hierarchy 0}.
void sub_465B20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00465b20
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    v0 = a0;
    v1 = si(-1);
    a0 = addu(a0, a1);
    sw(zero, a0, 4);
    sw(v1, a0, 0);
}

// 0x00465B40 sub_465B40 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_465B40 [hAnimFrameDtor]: Frame destructor: when the frame carries a hierarchy, clears every node's frame
// pointer and destroys the hierarchy if this frame is its parent frame; id -1.
void sub_465B40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465b40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    s0 = addu(s1, v0);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x00465b68
        charge(ctx, 4);
        lw(v0, a0, 4);
        at = slt(0, v0);
        a1 = 0;
        if (at != 0) {
            // 0x00465b78
            charge(ctx, 1);
            v1 = 0;
            for (;;) {
                // 0x00465b7c
                charge(ctx, 8);
                lw(v0, a0, 16);
                a1 = addiu(a1, 1);
                v0 = addu(v0, v1);
                sw(zero, v0, 12);
                lw(v0, a0, 4);
                v0 = slt(a1, v0);
                v1 = addiu(v1, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00465b9c
            charge(ctx, 1);
        }
        // 0x00465ba0
        charge(ctx, 3);
        lw(v0, a0, 20);
        if (v0 == s1) {
            // 0x00465bc0
            charge(ctx, 4);
            jal(ctx, 0x465BC0u, gen::fn_sub_4663D0_004663d0);  // [RpHAnimHierarchyDestroy]
            sw(zero, s0, 4);
            backedge(ctx);
        } else {
            // 0x00465bac
            charge(ctx, 1);
            sw(zero, s0, 4);
        }
    }
    // 0x00465bb0
    charge(ctx, 4);
    v1 = si(-1);
    v0 = s1;
    sw(v1, s0, 0);
    // 0x00465bd0
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00465BF0 sub_465BF0 -- 252 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_465BF0 [hAnimFrameCopy]: Frame copy callback: copies the id and, for an owned hierarchy, creates a copy (same
// node ids, indices and flags, frames cleared) whose parent frame is the new frame.
void sub_465BF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465bf0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    v1 = addu(a1, v0);
    s1 = addu(s2, v0);
    lw(v0, v1, 0);
    lw(s0, v1, 4);
    sw(v0, s1, 0);
    if (s0 != 0) {
        // 0x00465c24
        charge(ctx, 4);
        lw(a3, s0, 0);
        v0 = a3 & 0x1;
        if (v0 == 0) {
            // 0x00465c34
            charge(ctx, 10);
            lw(v0, s0, 32);
            a1 = 0;
            lw(a0, s0, 4);
            lw(t0, v0, 32);
            a2 = 0;
            jal(ctx, 0x465C44u, gen::fn_sub_466260_00466260);  // [RpHAnimHierarchyCreate]
            lw(v1, v0, 4);
            at = slt(0, v1);
            a0 = 0;
            if (at != 0) {
                // 0x00465c5c
                charge(ctx, 1);
                v1 = 0;
                for (;;) {
                    // 0x00465c60
                    charge(ctx, 26);
                    lw(a1, v0, 16);
                    a0 = addiu(a0, 1);
                    a1 = addu(a1, v1);
                    sw(zero, a1, 12);
                    lw(a2, s0, 16);
                    lw(a1, v0, 16);
                    a2 = addu(a2, v1);
                    lw(a2, a2, 8);
                    a1 = addu(a1, v1);
                    sw(a2, a1, 8);
                    lw(a2, s0, 16);
                    lw(a1, v0, 16);
                    a2 = addu(a2, v1);
                    lw(a2, a2, 4);
                    a1 = addu(a1, v1);
                    sw(a2, a1, 4);
                    lw(a2, s0, 16);
                    lw(a1, v0, 16);
                    a2 = addu(a2, v1);
                    lw(a2, a2, 0);
                    a1 = addu(a1, v1);
                    sw(a2, a1, 0);
                    lw(a1, v0, 4);
                    a1 = slt(a0, a1);
                    v1 = addiu(v1, 16);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00465cc8
            charge(ctx, 2);
            sw(v0, s1, 4);
            sw(s2, v0, 20);
        }
    }
    // 0x00465cd0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00465CF0 sub_465CF0 -- 444 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_465CF0 [hAnimFrameStreamWrite]: Frame stream-write: version 0x100, the id, then for a hierarchy its node count,
// flags and keyframe size and per node {id, index, flags}; a frame without (or with a sub-) hierarchy writes 0.
void sub_465CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00465cf0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 256;
    sd(ra, sp, 0x40);
    a1 = addiu(sp, 0x5C);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    sw(v0, sp, 0x5C);
    a2 = 4;
    jal(ctx, 0x465D1Cu, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
    if (v0 != 0) {
        // 0x00465d34
        charge(ctx, 8);
        lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
        a0 = s3;
        a2 = 4;
        s0 = addu(s0, v0);
        a1 = s0;
        jal(ctx, 0x465D44u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 == 0) {
            // 0x00465d90
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x00465d54
            charge(ctx, 3);
            lw(s0, s0, 4);
            if (s0 != 0) {
                // 0x00465d60
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    goto L_00465e70;
                }
                // 0x00465d70
                charge(ctx, 6);
                a0 = s3;
                a1 = addiu(s0, 4);
                a2 = 4;
                jal(ctx, 0x465D78u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                if (v0 != 0) {
                    // 0x00465d98
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = s0;
                    a2 = 4;
                    jal(ctx, 0x465DA0u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                    if (v0 != 0) {
                        // 0x00465db8
                        charge(ctx, 7);
                        lw(v0, s0, 32);
                        a0 = s3;
                        a2 = 4;
                        a1 = addiu(v0, 32);
                        jal(ctx, 0x465DC4u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                        if (v0 == 0) {
                            // 0x00465e58
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x00465dd4
                            charge(ctx, 5);
                            lw(v0, s0, 4);
                            lw(s1, s0, 16);
                            at = slt(0, v0);
                            s2 = 0;
                            if (at != 0) {
                                for (;;) {
                                    // 0x00465de8
                                    charge(ctx, 6);
                                    a0 = s3;
                                    a1 = s1;
                                    a2 = 4;
                                    jal(ctx, 0x465DF0u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                                    if (v0 == 0) {
                                        // 0x00465e00_13 (its only goto: the block written out here)
                                        charge(ctx, 2);
                                        v0 = 0;
                                        // 0x00465e90 (the shared epilogue, written out on this path)
                                        charge(ctx, 7);
                                        ld(ra, sp, 0x40);
                                        lq(s3, sp, 0x30);
                                        lq(s2, sp, 0x20);
                                        lq(s1, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x60);
                                        return;
                                    }
                                    // 0x00465e08
                                    charge(ctx, 6);
                                    a0 = s3;
                                    a1 = addiu(s1, 4);
                                    a2 = 4;
                                    jal(ctx, 0x465E10u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                                    if (v0 == 0) {
                                        // 0x00465e60 (its only goto: the block written out here)
                                        charge(ctx, 2);
                                        v0 = 0;
                                        // 0x00465e90 (the shared epilogue, written out on this path)
                                        charge(ctx, 7);
                                        ld(ra, sp, 0x40);
                                        lq(s3, sp, 0x30);
                                        lq(s2, sp, 0x20);
                                        lq(s1, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x60);
                                        return;
                                    }
                                    // 0x00465e20
                                    charge(ctx, 6);
                                    a0 = s3;
                                    a1 = addiu(s1, 8);
                                    a2 = 4;
                                    jal(ctx, 0x465E28u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                                    if (v0 == 0) {
                                        goto L_00465e68;
                                    }
                                    // 0x00465e38
                                    charge(ctx, 5);
                                    lw(v0, s0, 4);
                                    s2 = addiu(s2, 1);
                                    v0 = slt(s2, v0);
                                    s1 = addiu(s1, 16);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x00465e4c
                                charge(ctx, 1);
                                goto L_00465e50;
                            }
                        L_00465e50:
                            charge(ctx, 2);
                            v0 = s3;
                        }
                    } else {
                        // 0x00465db0
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x00465d88
                    charge(ctx, 2);
                    v0 = 0;
                }
                // 0x00465e90 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        L_00465e70:
            charge(ctx, 7);
            a0 = s3;
            a1 = addiu(sp, 0x58);
            a2 = 4;
            link(ctx, 0x465E7Cu);  // $ra first: the delay slot below depends on it
            sw(zero, sp, 0x58);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 != 0) {
                backedge(ctx);
                goto L_00465e50;
            }
            // 0x00465e8c
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x00465d2c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00465e90 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_00465e68:
    charge(ctx, 2);
    v0 = 0;
    // 0x00465e90 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00465EB0 sub_465EB0 -- 628 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_465EB0 [hAnimFrameStreamRead]: Frame stream-read: version 0x100, the id, the node count; when nodes follow, the
// flags and keyframe size, a new hierarchy (free list) with its interpolator, matrix array (64-byte aligned unless
// flag 2) and node table read {id, index, flags}, frames cleared.
void sub_465EB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00465eb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    a1 = addiu(sp, 0x68);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    a2 = 4;
    sq(s0, sp, 0x0);
    lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    s0 = a0;
    s1 = addu(s3, v0);
    jal(ctx, 0x465EE0u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
    if (v0 == 0) {
        // 0x00465f08
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00465ef0
        charge(ctx, 4);
        lw(v1, sp, 0x68);
        v0 = 256;
        if (v1 == v0) {
            // 0x00465f10
            charge(ctx, 6);
            a0 = s0;
            a1 = s1;
            a2 = 4;
            jal(ctx, 0x465F18u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 != 0) {
                // 0x00465f30
                charge(ctx, 6);
                a0 = s0;
                a1 = addiu(sp, 0x6C);
                a2 = 4;
                jal(ctx, 0x465F38u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                if (v0 == 0) {
                    // 0x00465f5c
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00465f48
                    charge(ctx, 3);
                    lw(v0, sp, 0x6C);
                    if (i64(v0) > 0) {
                        // 0x00465f64
                        charge(ctx, 6);
                        a0 = s0;
                        a1 = addiu(sp, 0x64);
                        a2 = 4;
                        jal(ctx, 0x465F6Cu, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                        if (v0 != 0) {
                            // 0x00465f84
                            charge(ctx, 6);
                            a0 = s0;
                            a1 = addiu(sp, 0x60);
                            a2 = 4;
                            jal(ctx, 0x465F8Cu, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                            if (v0 != 0) {
                                // 0x00465fa4
                                charge(ctx, 13);
                                v0 = 0x30000;
                                a1 = v0 | 0x11E;
                                v0 = 0x960000;
                                lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
                                jt = v0.u();  // the target, read before the delay slot
                                link(ctx, 0x465FB4u);  // $ra = the return address
                                lw(a0, gp, -17852);  // 0x7CE734 RpHAnim: hierarchy free list
                                call_ptr(ctx, jt);
                                s2 = v0;
                                a1 = 0;
                                a0 = s2;
                                a2 = 36;
                                jal(ctx, 0x465FC8u, gen::fn_memset_00521408);  // [memset]
                                if (s2 != 0) {
                                    // 0x00465fd8
                                    charge(ctx, 14);
                                    lw(a1, sp, 0x60);
                                    link(ctx, 0x465FDCu);  // $ra first: the delay slot below depends on it
                                    lw(a0, sp, 0x6C);
                                    call(ctx, gen::fn_sub_4B6E10_004b6e10);  // [RtAnimInterpolatorCreate]
                                    sw(v0, s2, 32);
                                    lw(v0, sp, 0x64);
                                    sw(v0, s2, 0);
                                    sw(s3, s2, 20);
                                    lw(v0, sp, 0x6C);
                                    sw(v0, s2, 4);
                                    sw(s2, s2, 24);
                                    lw(v0, s2, 0);
                                    v0 = v0 & 0x2;
                                    if (v0 == 0) {
                                        // 0x004660c0
                                        charge(ctx, 14);
                                        v0 = 0x30000;
                                        lw(v1, sp, 0x6C);
                                        a1 = v0 | 0x11E;
                                        v0 = 0x960000;
                                        lw(v0, v0, 376);  // 0x960178 RwMalloc slot
                                        v1 = sll(v1, 6);
                                        a0 = addiu(v1, 15);
                                        jalr(ctx, 0x4660D8u, v0.u());
                                        a0 = addiu(v0, 15);
                                        v1 = si(-16);
                                        v1 = a0 & v1;
                                        sw(v1, s2, 8);
                                        sw(v0, s2, 12);
                                        backedge(ctx);
                                    } else {
                                        // 0x00466010
                                        charge(ctx, 2);
                                        sw(zero, s2, 8);
                                        sw(zero, s2, 12);
                                    }
                                    // 0x00466018
                                    charge(ctx, 13);
                                    v0 = 0x30000;
                                    lw(v1, sp, 0x6C);
                                    a1 = v0 | 0x11E;
                                    v0 = 0x960000;
                                    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
                                    a0 = sll(v1, 4);
                                    jalr(ctx, 0x46602Cu, v0.u());
                                    sw(v0, s2, 16);
                                    lw(v0, s2, 4);
                                    lw(s3, s2, 16);
                                    at = slt(0, v0);
                                    s4 = 0;
                                    if (at == 0) {
                                        goto L_004660b8;
                                    }
                                    for (;;) {
                                        // 0x0046604c
                                        charge(ctx, 6);
                                        a0 = s0;
                                        a1 = s3;
                                        a2 = 4;
                                        jal(ctx, 0x466054u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                                        if (v0 == 0) {
                                            // 0x00466064_19 (its only goto: the block written out here)
                                            charge(ctx, 2);
                                            v0 = 0;
                                            // 0x00466104 (the shared epilogue, written out on this path)
                                            charge(ctx, 8);
                                            ld(ra, sp, 0x50);
                                            lq(s4, sp, 0x40);
                                            lq(s3, sp, 0x30);
                                            lq(s2, sp, 0x20);
                                            lq(s1, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x70);
                                            return;
                                        }
                                        // 0x0046606c
                                        charge(ctx, 6);
                                        a0 = s0;
                                        a1 = addiu(s3, 4);
                                        a2 = 4;
                                        jal(ctx, 0x466074u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                                        if (v0 == 0) {
                                            // 0x004660f8 (its only goto: the block written out here)
                                            charge(ctx, 2);
                                            v0 = 0;
                                            // 0x00466104 (the shared epilogue, written out on this path)
                                            charge(ctx, 8);
                                            ld(ra, sp, 0x50);
                                            lq(s4, sp, 0x40);
                                            lq(s3, sp, 0x30);
                                            lq(s2, sp, 0x20);
                                            lq(s1, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x70);
                                            return;
                                        }
                                        // 0x00466084
                                        charge(ctx, 6);
                                        a0 = s0;
                                        a1 = addiu(s3, 8);
                                        a2 = 4;
                                        jal(ctx, 0x46608Cu, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                                        if (v0 == 0) {
                                            goto L_00466100;
                                        }
                                        // 0x0046609c
                                        charge(ctx, 6);
                                        sw(zero, s3, 12);
                                        s4 = addiu(s4, 1);
                                        lw(v0, s2, 4);
                                        v0 = slt(s4, v0);
                                        s3 = addiu(s3, 16);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004660b4
                                    charge(ctx, 1);
                                    goto L_004660b8;
                                }
                            L_004660b8:
                                charge(ctx, 2);
                                sw(s2, s1, 4);
                                backedge(ctx);
                                goto L_00465f54;
                            }
                            // 0x00465f9c
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x00465f7c
                            charge(ctx, 2);
                            v0 = 0;
                        }
                        // 0x00466104 (the shared epilogue, written out on this path)
                        charge(ctx, 8);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x70);
                        return;
                    }
                L_00465f54:
                    charge(ctx, 2);
                    v0 = s0;
                }
            } else {
                // 0x00465f28
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x00465f00
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x00466104 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00466100:
    charge(ctx, 1);
    v0 = 0;
    // 0x00466104 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00466130 sub_466130 -- 120 bytes; leaf frame (no stack)
// sub_466130 [hAnimFrameStreamGetSize]: Frame stream-size: 0 for a plain frame, 12 for an id or a sub-hierarchy, 20 +
// 12 per node for a hierarchy.
void sub_466130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00466130
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    v1 = addu(a0, v0);
    lw(v0, v1, 0);
    v0 = nor(v0, 0);
    v0 = sltu(0, v0);
    if (v0 == 0) {
        // 0x0046614c
        charge(ctx, 2);
        lw(v0, v1, 4);
        v0 = sltu(0, v0);
    }
    // 0x00466154
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0046619c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0046615c
        charge(ctx, 4);
        lw(a0, v1, 4);
        v0 = 4;
        v0 = addiu(v0, 8);
        if (a0 != 0) {
            // 0x0046616c
            charge(ctx, 4);
            lw(v1, a0, 0);
            v1 = v1 & 0x1;
            if (v1 == 0) {
                // 0x0046617c
                charge(ctx, 8);
                lw(v1, a0, 4);
                a0 = addiu(v0, 8);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(a0, v0);
            }
        }
    }
    // 0x004661a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004661B0 sub_4661B0 -- 164 bytes; frame 0x10: ra sp+0x0
// sub_4661B0 [RpHAnimPluginAttach]: Attaches RpHAnim (id 0x11E): the engine plugin, the 8-byte frame extension
// (offset 0x7CE730) and its stream callbacks. Returns 1 on success.
void sub_4661B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004661b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x460000;
    a3 = 0x460000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 286;
    a2 = addiu(a2, 23040);  // &sub_465A00
    a3 = addiu(a3, 23264);  // &sub_465AE0
    jal(ctx, 0x4661CCu, gen::fn_sub_4CA520_004ca520);  // [RwEngineRegisterPlugin]
    if (i64(v0) >= 0) {
        // 0x004661e4
        charge(ctx, 22);
        a2 = 0x460000;
        a3 = 0x460000;
        t0 = 0x460000;
        a0 = 8;
        a1 = 286;
        a2 = addiu(a2, 23328);  // &sub_465B20
        a3 = addiu(a3, 23360);  // &sub_465B40
        t0 = addiu(t0, 23536);  // &sub_465BF0
        jal(ctx, 0x466200u, gen::fn_sub_4CB9F0_004cb9f0);  // [RwFrameRegisterPlugin]
        a1 = 0x460000;
        a2 = 0x460000;
        a3 = 0x460000;
        sw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
        a0 = 286;
        a1 = addiu(a1, 24240);  // &sub_465EB0
        a2 = addiu(a2, 23792);  // &sub_465CF0
        a3 = addiu(a3, 24880);  // &sub_466130
        jal(ctx, 0x466224u, gen::fn_sub_4C7D00_004c7d00);  // [RwFrameRegisterPluginStream]
        v0 = slt(v0, 0);
        v0 = v0 ^ 0x1;
        if (v0 != 0) {
            // 0x0046623c
            charge(ctx, 3);
            lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
            v0 = slt(v0, 0);
            v0 = v0 ^ 0x1;
        }
    } else {
        // 0x004661dc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00466248 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00466260 sub_466260 -- 360 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_466260 [RpHAnimHierarchyCreate]: Creates a hierarchy of $a0 nodes, flags $a3, keyframe size $t0: an
// interpolator, the matrix array (unless flag 2), the node table from the optional id ($a2) and flag ($a1) arrays
// (index = node number). It is its own root (parent hierarchy = itself).
void sub_466260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00466260
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x30000;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = t0;
    sq(s2, sp, 0x20);
    s3 = a0;
    s2 = a1;
    sq(s1, sp, 0x10);
    a1 = v0 | 0x11E;
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(a0, gp, -17852);  // 0x7CE734 RpHAnim: hierarchy free list
    lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
    s1 = a2;
    s0 = a3;
    jalr(ctx, 0x4662A0u, v0.u());
    a1 = s4;
    a0 = s3;
    s4 = v0;
    jal(ctx, 0x4662B0u, gen::fn_sub_4B6E10_004b6e10);  // [RtAnimInterpolatorCreate]
    sw(v0, s4, 32);
    sw(s0, s4, 0);
    v0 = s0 & 0x2;
    sw(s3, s4, 4);
    sw(zero, s4, 20);
    if (v0 == 0) {
        // 0x00466374
        charge(ctx, 13);
        v0 = 0x30000;
        v1 = sll(s3, 6);
        a1 = v0 | 0x11E;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 RwMalloc slot
        a0 = addiu(v1, 15);
        jalr(ctx, 0x466388u, v0.u());
        a0 = addiu(v0, 15);
        v1 = si(-16);
        v1 = a0 & v1;
        sw(v1, s4, 8);
        sw(v0, s4, 12);
        backedge(ctx);
    } else {
        // 0x004662d0
        charge(ctx, 2);
        sw(zero, s4, 8);
        sw(zero, s4, 12);
    }
    // 0x004662d8
    charge(ctx, 10);
    v0 = 0x30000;
    a1 = v0 | 0x11E;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
    a0 = sll(s3, 4);
    jalr(ctx, 0x4662E8u, v0.u());
    at = slt(0, s3);
    sw(v0, s4, 16);
    a3 = 0;
    if (at != 0) {
        // 0x00466300
        charge(ctx, 3);
        a2 = 0;
        a1 = s1;
        a0 = s2;
        for (;;) {
            // 0x0046630c
            charge(ctx, 4);
            lw(v0, s4, 16);
            v0 = addu(v0, a2);
            sw(zero, v0, 12);
            if (s1 != 0) {
                // 0x0046631c
                charge(ctx, 5);
                lw(v0, s4, 16);
                lw(v1, a1, 0);
                v0 = addu(v0, a2);
                sw(v1, v0, 0);
            }
            // 0x00466330
            charge(ctx, 4);
            lw(v0, s4, 16);
            v0 = addu(v0, a2);
            sw(a3, v0, 4);
            if (s2 != 0) {
                // 0x00466340
                charge(ctx, 4);
                lw(v0, s4, 16);
                lw(v1, a0, 0);
                v0 = addu(v0, a2);
                sw(v1, v0, 8);
            }
            // 0x00466350
            charge(ctx, 6);
            a3 = addiu(a3, 1);
            v0 = slt(a3, s3);
            a2 = addiu(a2, 16);
            a1 = addiu(a1, 4);
            a0 = addiu(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00466368
    charge(ctx, 3);
    sw(s4, s4, 24);
    v0 = s4;
    // 0x004663a8
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00466480 sub_466480 -- 448 bytes; frame 0xF0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_466480 [RpHAnimHierarchyCreateSubHierarchy]: Creates the sub-hierarchy of parent $a0 rooted at node $a1: counts
// the nodes of the subtree (push / pop flags 2 / 1), a hierarchy flagged 1 | $a2 sharing the parent's matrix array
// and node table from that node, a sub-interpolator, and the root's parent offset found by replaying the push / pop
// stack.
void sub_466480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00466480
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a3;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = 1;
    lw(v0, a0, anim::kHierNodeInfo);
    s0 = sll(s3, 4);
    a0 = addu(v0, s0);
    lw(v0, a0, 8);
    v0 = v0 & 0x1;
    a1 = 0;
    if (v0 == 0) {
        // 0x004664d0
        charge(ctx, 2);
        a1 = s1;
        a0 = addiu(a0, 16);
    }
    // 0x004664d8
    charge(ctx, 2);
    if (a1 != 0) {
        for (;;) {
            // 0x004664e0
            charge(ctx, 4);
            lw(v1, a0, 8);
            v0 = v1 & 0x2;
            if (v0 != 0) {
                // 0x004664f0
                charge(ctx, 2);
                a1 = addiu(a1, 1);
            }
            // 0x004664f8
            charge(ctx, 3);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x00466504
                charge(ctx, 1);
                a1 = addiu(a1, -1);
            }
            // 0x00466508
            charge(ctx, 3);
            s1 = addiu(s1, 1);
            a0 = addiu(a0, 16);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00466514
        charge(ctx, 1);
    }
    // 0x00466518
    charge(ctx, 17);
    v0 = 0x960000;
    lw(a0, gp, -17852);  // 0x7CE734 RpHAnim: hierarchy free list
    v1 = 0x30000;
    lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
    a1 = v1 | 0x11E;
    jalr(ctx, 0x466528u, v0.u());
    v1 = s2 | 0x1;
    a3 = s5;
    sw(v1, v0, 0);
    s2 = v0;
    sw(s1, v0, 4);
    a2 = s1;
    lw(a0, s4, anim::kHierInterp);
    a1 = s3;
    jal(ctx, 0x46654Cu, gen::fn_sub_4B75D0_004b75d0);  // [RtAnimInterpolatorCreateSubInterpolator]
    sw(v0, s2, 32);
    if (s3 == 0) {
        // 0x00466604
        charge(ctx, 3);
        v0 = si(-1);
        sw(v0, s2, 28);
        backedge(ctx);
    } else {
        // 0x0046655c
        charge(ctx, 5);
        at = slt(0, s3);
        a2 = addiu(sp, 0x70);
        a1 = si(-1);
        a3 = 0;
        if (at != 0) {
            // 0x00466570
            charge(ctx, 2);
            lw(v1, s4, anim::kHierNodeInfo);
            a0 = 0;
            for (;;) {
                // 0x00466578
                charge(ctx, 5);
                v0 = addu(v1, a0);
                lw(v0, v0, 8);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x00466610
                    charge(ctx, 3);
                    sw(a1, a2, 0);
                    a2 = addiu(a2, 4);
                    backedge(ctx);
                }
                // 0x0046658c
                charge(ctx, 6);
                lw(v0, s4, anim::kHierNodeInfo);
                v0 = addu(v0, a0);
                lw(v0, v0, 8);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x004665b0
                    charge(ctx, 1);
                    a1 = a3;
                } else {
                    // 0x004665a4
                    charge(ctx, 3);
                    a2 = addiu(a2, -4);
                    lw(a1, a2, 0);
                }
                // 0x004665b4
                charge(ctx, 4);
                a3 = addiu(a3, 1);
                v0 = slt(a3, s3);
                a0 = addiu(a0, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004665c4
        charge(ctx, 1);
        sw(a1, s2, 28);
    }
    // 0x004665c8
    charge(ctx, 15);
    lw(v1, s4, anim::kHierNodeInfo);
    a0 = sll(s3, 6);
    v0 = s2;
    v1 = addu(s0, v1);
    lw(v1, v1, 12);
    sw(v1, s2, 20);
    lw(v1, s4, anim::kHierMatrices);
    v1 = addu(v1, a0);
    sw(v1, s2, 8);
    sw(zero, s2, 12);
    lw(v1, s4, anim::kHierNodeInfo);
    v1 = addu(v1, s0);
    sw(v1, s2, 16);
    sw(s4, s2, 24);
    // 0x0046661c
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x00466640 sub_466640 -- 196 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_466640 [RpHAnimHierarchyAttach]: Binds hierarchy $a0 to its frames: every node whose id matches the parent
// frame's gets it, the frame is updated, and the child frames are walked with hAnimAttachFrameCB. Returns $a0.
void sub_466640(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00466640
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, anim::kHierNumNodes);
    lw(s2, a0, anim::kHierParentFrame);
    at = slt(0, v0);
    s1 = 0;
    if (at != 0) {
        // 0x00466678
        charge(ctx, 1);
        s0 = 0;
        for (;;) {
            // 0x0046667c
            charge(ctx, 7);
            lw(v0, s3, anim::kHierNodeInfo);
            s5 = addu(v0, s0);
            lw(s4, s5, 0);
            a0 = s2;
            jal(ctx, 0x466688u, gen::fn_sub_466720_00466720);  // [RpHAnimFrameGetID]
            if (s4 == v0) {
                // 0x004666d4
                charge(ctx, 2);
                sw(s2, s5, 12);
                backedge(ctx);
            }
            // 0x00466698
            charge(ctx, 5);
            lw(v0, s3, anim::kHierNumNodes);
            s1 = addiu(s1, 1);
            v0 = slt(s1, v0);
            s0 = addiu(s0, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004666ac
        charge(ctx, 1);
    }
    // 0x004666b0
    charge(ctx, 9);
    a0 = s2;
    jal(ctx, 0x4666B0u, gen::fn_sub_4CB270_004cb270);  // [RwFrameUpdateObjects]
    a1 = 0x460000;
    a0 = s2;
    a1 = addiu(a1, 22832);  // &sub_465930
    a2 = s3;
    jal(ctx, 0x4666C4u, gen::fn_sub_4CB6E0_004cb6e0);  // [RwFrameForAllChildren]
    v0 = s3;
    // 0x004666e0
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

// 0x00466710 sub_466710 -- 16 bytes; leaf frame (no stack)
// sub_466710 [RpHAnimFrameGetHierarchy]: The hierarchy attached to frame $a0 (extension +4).
void sub_466710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00466710
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    v0 = addu(a0, v0);
    lw(v0, v0, 4);
}

// 0x00466720 sub_466720 -- 16 bytes; leaf frame (no stack)
// sub_466720 [RpHAnimFrameGetID]: The HAnim id of frame $a0 (extension +0).
void sub_466720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00466720
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, -17856);  // 0x7CE730 RpHAnim: frame extension offset
    v0 = addu(a0, v0);
    lw(v0, v0, 0);
}

// 0x00466730 sub_466730 -- 1972 bytes; frame 0x9B0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_466730 [hAnimHierarchyUpdateFrames]: The matrix update of a hierarchy without a matrix array (flag 2): the root
// is the parent frame's LTM (rebuilt through the dirty parent chain when the frame is dirty), then per node the
// interpolated frame becomes a local matrix (keyframe apply callback), is multiplied by the parent matrix kept on a
// push / pop stack (node flags 2 / 1) and written into the node frame's matrix; the frames are updated. Returns 1.
void sub_466730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x00466730
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x9B0);
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
    lw(v0, a0, anim::kHierParentFrame);
    lw(s3, a0, anim::kHierFlags);
    lw(s0, v0, 4);
    s5 = a0;
    if (s0 == 0) {
        // 0x00466cbc
        charge(ctx, 19);
        v1 = 0x3F800000;
        v0 = 0x20000;
        sw(v1, sp, 0x198);
        v0 = v0 | 0x3;
        sw(v1, sp, 0x184);
        sw(v1, sp, 0x170);
        lw(v1, sp, 0x17C);
        sw(zero, sp, 0x180);
        sw(zero, sp, 0x178);
        sw(zero, sp, 0x174);
        sw(zero, sp, 0x194);
        sw(zero, sp, 0x190);
        v0 = v1 | v0;
        sw(zero, sp, 0x188);
        sw(zero, sp, 0x1A8);
        sw(zero, sp, 0x1A4);
        sw(zero, sp, 0x1A0);
        sw(v0, sp, 0x17C);
        backedge(ctx);
    } else {
        // 0x00466770
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x466770u, gen::fn_sub_4CAE30_004cae30);  // [rwFrameIsDirty]
        if (v0 == 0) {
            // 0x00466c84
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x466C84u, gen::fn_sub_4CB2F0_004cb2f0);  // [RwFrameGetLTM]
            a2 = addiu(sp, 0x170);
            a1 = 8;
            for (;;) {
                // 0x00466c94
                charge(ctx, 8);
                lw(a0, v0, 0);
                a1 = addiu(a1, -1);
                lw(v1, v0, 4);
                sw(a0, a2, 0);
                v0 = addiu(v0, 8);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00466cb4
            charge(ctx, 2);
            backedge(ctx);
        } else {
            // 0x00466780
            charge(ctx, 3);
            a2 = addiu(s0, 16);
            a1 = addiu(sp, 0x170);
            a0 = 8;
            for (;;) {
                // 0x0046678c
                charge(ctx, 8);
                lw(v1, a2, 0);
                a0 = addiu(a0, -1);
                lw(v0, a2, 4);
                sw(v1, a1, 0);
                a2 = addiu(a2, 8);
                sw(v0, a1, 4);
                a1 = addiu(a1, 8);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004667ac
            charge(ctx, 3);
            lw(s4, s0, 4);
            if (s4 != 0) {
                // 0x004667b8
                charge(ctx, 6);
                s2 = addiu(sp, 0x174);
                s1 = addiu(sp, 0x134);
                s0 = addiu(sp, 0x178);
                s6 = addiu(sp, 0x138);
                s7 = addiu(sp, 0x17C);
                fp = addiu(sp, 0x13C);
                for (;;) {
                    // 0x004667d0
                    charge(ctx, 63);
                    v0 = addiu(sp, 0x180);
                    lw(a3, s7, 0);
                    lwc1(f3, v0, 0);
                    a0 = addiu(sp, 0x170);
                    lwc1(f4, s0, 0);
                    lwc1(f6, sp, 0x170);
                    lwc1(f5, s2, 0);
                    sw(a3, fp, 0x0);
                    v0 = addiu(sp, 0x18C);
                    lw(a2, v0, 0);
                    swc1(f4, s6, 0);
                    swc1(f6, sp, 0x130);
                    swc1(f5, s1, 0);
                    v0 = addiu(sp, 0x184);
                    lwc1(f2, v0, 0);
                    v0 = addiu(sp, 0x19C);
                    lw(a1, v0, 0);
                    v0 = addiu(sp, 0x188);
                    lwc1(f1, v0, 0);
                    v0 = addiu(sp, 0x1AC);
                    lw(v1, v0, 0);
                    v0 = addiu(sp, 0x190);
                    lwc1(f0, v0, 0);
                    v0 = addiu(sp, 0x14C);
                    sw(a2, v0, 0);
                    v0 = addiu(sp, 0x140);
                    a2 = addiu(s4, 16);
                    swc1(f3, v0, 0);
                    v0 = addiu(sp, 0x15C);
                    sw(a1, v0, 0);
                    v0 = addiu(sp, 0x144);
                    a1 = addiu(sp, 0x130);
                    swc1(f2, v0, 0);
                    v0 = addiu(sp, 0x16C);
                    sw(v1, v0, 0);
                    v0 = addiu(sp, 0x148);
                    swc1(f1, v0, 0);
                    v0 = addiu(sp, 0x150);
                    swc1(f0, v0, 0);
                    v0 = addiu(sp, 0x194);
                    lwc1(f4, v0, 0);
                    v0 = addiu(sp, 0x198);
                    lwc1(f3, v0, 0);
                    v0 = addiu(sp, 0x1A0);
                    lwc1(f2, v0, 0);
                    v0 = addiu(sp, 0x1A4);
                    lwc1(f1, v0, 0);
                    v0 = addiu(sp, 0x1A8);
                    lwc1(f0, v0, 0);
                    v0 = addiu(sp, 0x154);
                    swc1(f4, v0, 0);
                    v0 = addiu(sp, 0x158);
                    swc1(f3, v0, 0);
                    v0 = addiu(sp, 0x160);
                    swc1(f2, v0, 0);
                    v0 = addiu(sp, 0x164);
                    swc1(f1, v0, 0);
                    v0 = addiu(sp, 0x168);
                    link(ctx, 0x4668B8u);  // $ra first: the delay slot below depends on it
                    swc1(f0, v0, 0);
                    call(ctx, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                    lw(s4, s4, 4);
                    if (s4 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004668cc
                charge(ctx, 1);
            }
        }
    }
    // 0x004668d0
    charge(ctx, 3);
    s4 = s3 & 0x2000;
    if (s4 != 0) {
        // 0x004668dc
        charge(ctx, 6);
        lw(v0, s5, anim::kHierParentFrame);
        lw(v1, v0, 160);
        lbu(v0, v1, 3);
        v0 = v0 & 0x3;
        if (v0 == 0) {
            // 0x004668f4
            charge(ctx, 21);
            a0 = 0x960000;
            a0 = addiu(a0, 300);  // &0x96012C
            lw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
            sw(v0, v1, 8);
            lw(v0, s5, anim::kHierParentFrame);
            lw(v0, v0, 160);
            sw(a0, v0, 12);
            lw(v1, s5, anim::kHierParentFrame);
            lw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
            lw(v1, v1, 160);
            v1 = addiu(v1, 8);
            sw(v1, v0, 4);
            lw(v0, s5, anim::kHierParentFrame);
            lw(v0, v0, 160);
            v0 = addiu(v0, 8);
            sw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
            lw(v0, s5, anim::kHierParentFrame);
            lw(v1, v0, 160);
            lbu(v0, v1, 3);
            v0 = v0 | 0x2;
            sb(v0, v1, 3);
        }
    }
    // 0x00466948
    charge(ctx, 11);
    lw(v0, s5, anim::kHierInterp);
    s2 = addiu(sp, 0x1F0);
    lw(v1, s5, anim::kHierNumNodes);
    s6 = 0;
    lw(s1, s5, anim::kHierNodeInfo);
    lw(s7, v0, anim::kItpApplyCB);
    s0 = addiu(v0, 76);
    at = slt(0, v1);
    lw(v0, v0, anim::kItpFrameSize);
    sq(v0, sp, 0xA0);
    if (at != 0) {
        // 0x00466974
        charge(ctx, 1);
        fp = s3 & 0x1000;
        for (;;) {
            // 0x00466978
            charge(ctx, 4);
            v0 = 0x460000;
            v0 = addiu(v0, 18272);  // &sub_464760
            if (v0 == s7) {
                // 0x00466d08
                charge(ctx, 75);
                lwc1(f8, s0, 8);
                v0 = 0x40000000;
                lwc1(f7, s0, 12);
                v1 = 3;
                lwc1(f2, s0, 16);
                lwc1(f1, s0, 20);
                mtc1(v0, f6);
                mul_s(f4, f8, f8);
                v0 = 0x3F800000;
                mul_s(f0, f2, f2);
                mul_s(f12, f7, f2);
                mul_s(f11, f2, f8);
                mtc1(v0, f5);
                mul_s(f10, f8, f7);
                v0 = addiu(sp, 0xFC);
                sw(v1, v0, 0);
                v0 = addiu(sp, 0x120);
                sw(zero, v0, 0);
                mul_s(f9, f1, f8);
                v0 = addiu(sp, 0x124);
                sw(zero, v0, 0);
                v0 = addiu(sp, 0x128);
                sw(zero, v0, 0);
                v0 = addiu(sp, 0xF4);
                mul_s(f3, f7, f7);
                mul_s(f8, f1, f7);
                mul_s(f2, f1, f2);
                add_s(f7, f3, f0);
                add_s(f1, f4, f0);
                add_s(f0, f4, f3);
                add_s(f3, f10, f2);
                sub_s(f2, f10, f2);
                mul_s(f3, f6, f3);
                mtc1(zero, f4);
                swc1(f3, v0, 0);
                mul_s(f2, f6, f2);
                v0 = addiu(sp, 0x100);
                swc1(f2, v0, 0);
                adda_s(f4, f5);
                v0 = addiu(sp, 0x104);
                msub_s(f2, f6, f7);
                adda_s(f4, f5);
                msub_s(f1, f6, f1);
                swc1(f1, v0, 0);
                adda_s(f4, f5);
                v0 = addiu(sp, 0x118);
                msub_s(f0, f6, f0);
                swc1(f0, v0, 0);
                sub_s(f1, f11, f8);
                v0 = addiu(sp, 0xF8);
                add_s(f0, f11, f8);
                mul_s(f1, f6, f1);
                swc1(f1, v0, 0);
                add_s(f1, f12, f9);
                v0 = addiu(sp, 0x110);
                mul_s(f0, f6, f0);
                swc1(f0, v0, 0);
                sub_s(f0, f12, f9);
                v0 = addiu(sp, 0x108);
                mul_s(f1, f6, f1);
                swc1(f1, v0, 0);
                mul_s(f0, f6, f0);
                v0 = addiu(sp, 0x114);
                swc1(f0, v0, 0);
                swc1(f2, sp, 0xF0);
                v0 = addiu(sp, 0x120);
                lwc1(f0, s0, 24);
                swc1(f0, v0, 0);
                lwc1(f0, s0, 28);
                v0 = addiu(sp, 0x124);
                swc1(f0, v0, 0);
                lwc1(f0, s0, 32);
                v0 = addiu(sp, 0x128);
                swc1(f0, v0, 0);
                backedge(ctx);
            } else {
                // 0x00466988
                charge(ctx, 3);
                a0 = addiu(sp, 0xF0);
                a1 = s0;
                jalr(ctx, 0x46698Cu, s7.u());
            }
            // 0x00466994
            charge(ctx, 7);
            a0 = addiu(sp, 0xB0);
            a1 = addiu(sp, 0xF0);
            a2 = addiu(sp, 0x170);
            jal(ctx, 0x46699Cu, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
            lw(s3, s1, 12);
            if (s3 != 0) {
                // 0x004669b0
                charge(ctx, 2);
                if (fp != 0) {
                    // 0x00466e34
                    charge(ctx, 3);
                    a2 = addiu(sp, 0xF0);
                    a1 = addiu(s3, 16);
                    a0 = 8;
                    for (;;) {
                        // 0x00466e40
                        charge(ctx, 8);
                        lw(v1, a2, 0);
                        a0 = addiu(a0, -1);
                        lw(v0, a2, 4);
                        sw(v1, a1, 0);
                        a2 = addiu(a2, 8);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00466e60
                    charge(ctx, 2);
                    if (s4 != 0) {
                        backedge(ctx);
                    } else {
                        // 0x00466e68
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x466E68u, gen::fn_sub_4CB270_004cb270);  // [RwFrameUpdateObjects]
                        backedge(ctx);
                    }
                }
                // 0x004669b8
                charge(ctx, 2);
                if (s4 != 0) {
                    // 0x004669c0
                    charge(ctx, 3);
                    a2 = addiu(sp, 0xB0);
                    a1 = addiu(s3, 80);
                    a0 = 8;
                    for (;;) {
                        // 0x004669cc
                        charge(ctx, 8);
                        lw(v1, a2, 0);
                        a0 = addiu(a0, -1);
                        lw(v0, a2, 4);
                        sw(v1, a1, 0);
                        a2 = addiu(a2, 8);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004669ec
                    charge(ctx, 6);
                    lbu(v1, s3, 3);
                    v0 = si(-5);
                    v0 = v1 & v0;
                    v0 = v0 | 0x8;
                    sb(v0, s3, 3);
                }
            }
            // 0x00466e78
            charge(ctx, 5);
            lw(v1, s1, 8);
            v0 = 3;
            v1 = v1 & 0x3;
            if (v1 == v0) {
                backedge(ctx);
            } else {
                // 0x00466e8c
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    backedge(ctx);
                    // 0x00466b38
                    charge(ctx, 3);
                    a2 = addiu(sp, 0x170);
                    a0 = 8;
                    a1 = s2;
                    for (;;) {
                        // 0x00466b44
                        charge(ctx, 8);
                        lw(v1, a2, 0);
                        a0 = addiu(a0, -1);
                        lw(v0, a2, 4);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a2 = addiu(a2, 8);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00466b64
                    charge(ctx, 63);
                    v0 = addiu(sp, 0xB4);
                    s2 = addiu(s2, 64);
                    lwc1(f5, v0, 0);
                    lwc1(f6, sp, 0xB0);
                    v0 = addiu(sp, 0xB8);
                    lwc1(f4, v0, 0);
                    swc1(f6, sp, 0x170);
                    v0 = addiu(sp, 0xC0);
                    lwc1(f3, v0, 0);
                    v0 = addiu(sp, 0xBC);
                    lw(a2, v0, 0);
                    v0 = addiu(sp, 0xC4);
                    lwc1(f2, v0, 0);
                    v0 = addiu(sp, 0xCC);
                    lw(a1, v0, 0);
                    v0 = addiu(sp, 0xC8);
                    lwc1(f1, v0, 0);
                    v0 = addiu(sp, 0xDC);
                    lw(a0, v0, 0);
                    v0 = addiu(sp, 0xD0);
                    lwc1(f0, v0, 0);
                    v0 = addiu(sp, 0xEC);
                    lw(v1, v0, 0);
                    v0 = addiu(sp, 0x174);
                    swc1(f5, v0, 0);
                    v0 = addiu(sp, 0x178);
                    swc1(f4, v0, 0);
                    v0 = addiu(sp, 0x17C);
                    sw(a2, v0, 0);
                    v0 = addiu(sp, 0x180);
                    swc1(f3, v0, 0);
                    v0 = addiu(sp, 0x18C);
                    sw(a1, v0, 0);
                    v0 = addiu(sp, 0x184);
                    swc1(f2, v0, 0);
                    v0 = addiu(sp, 0x19C);
                    sw(a0, v0, 0);
                    v0 = addiu(sp, 0x188);
                    swc1(f1, v0, 0);
                    v0 = addiu(sp, 0x1AC);
                    sw(v1, v0, 0);
                    v0 = addiu(sp, 0x190);
                    swc1(f0, v0, 0);
                    v0 = addiu(sp, 0xD4);
                    lwc1(f4, v0, 0);
                    v0 = addiu(sp, 0xD8);
                    lwc1(f3, v0, 0);
                    v0 = addiu(sp, 0xE0);
                    lwc1(f2, v0, 0);
                    v0 = addiu(sp, 0xE4);
                    lwc1(f1, v0, 0);
                    v0 = addiu(sp, 0xE8);
                    lwc1(f0, v0, 0);
                    v0 = addiu(sp, 0x194);
                    swc1(f4, v0, 0);
                    v0 = addiu(sp, 0x198);
                    swc1(f3, v0, 0);
                    v0 = addiu(sp, 0x1A0);
                    swc1(f2, v0, 0);
                    v0 = addiu(sp, 0x1A4);
                    swc1(f1, v0, 0);
                    v0 = addiu(sp, 0x1A8);
                    swc1(f0, v0, 0);
                    goto L_00466c60;
                }
                // 0x00466e98
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x00466ea4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        backedge(ctx);
                        // 0x00466a04
                        charge(ctx, 63);
                        v0 = addiu(sp, 0xB4);
                        lwc1(f5, v0, 0);
                        lwc1(f6, sp, 0xB0);
                        v0 = addiu(sp, 0xB8);
                        lwc1(f4, v0, 0);
                        swc1(f6, sp, 0x170);
                        v0 = addiu(sp, 0xBC);
                        lw(a2, v0, 0);
                        v0 = addiu(sp, 0xC0);
                        lwc1(f3, v0, 0);
                        v0 = addiu(sp, 0xCC);
                        lw(a1, v0, 0);
                        v0 = addiu(sp, 0xC4);
                        lwc1(f2, v0, 0);
                        v0 = addiu(sp, 0xDC);
                        lw(a0, v0, 0);
                        v0 = addiu(sp, 0xC8);
                        lwc1(f1, v0, 0);
                        v0 = addiu(sp, 0xEC);
                        lw(v1, v0, 0);
                        v0 = addiu(sp, 0xD0);
                        lwc1(f0, v0, 0);
                        v0 = addiu(sp, 0x174);
                        swc1(f5, v0, 0);
                        v0 = addiu(sp, 0x17C);
                        sw(a2, v0, 0);
                        v0 = addiu(sp, 0x178);
                        swc1(f4, v0, 0);
                        v0 = addiu(sp, 0x18C);
                        sw(a1, v0, 0);
                        v0 = addiu(sp, 0x180);
                        swc1(f3, v0, 0);
                        v0 = addiu(sp, 0x19C);
                        sw(a0, v0, 0);
                        v0 = addiu(sp, 0x184);
                        swc1(f2, v0, 0);
                        v0 = addiu(sp, 0x1AC);
                        sw(v1, v0, 0);
                        v0 = addiu(sp, 0x188);
                        swc1(f1, v0, 0);
                        v0 = addiu(sp, 0x190);
                        swc1(f0, v0, 0);
                        v0 = addiu(sp, 0xD4);
                        lwc1(f4, v0, 0);
                        v0 = addiu(sp, 0xD8);
                        lwc1(f3, v0, 0);
                        v0 = addiu(sp, 0xE0);
                        lwc1(f2, v0, 0);
                        v0 = addiu(sp, 0xE4);
                        lwc1(f1, v0, 0);
                        v0 = addiu(sp, 0xE8);
                        lwc1(f0, v0, 0);
                        v0 = addiu(sp, 0x194);
                        swc1(f4, v0, 0);
                        v0 = addiu(sp, 0x198);
                        swc1(f3, v0, 0);
                        v0 = addiu(sp, 0x1A0);
                        swc1(f2, v0, 0);
                        v0 = addiu(sp, 0x1A4);
                        swc1(f1, v0, 0);
                        v0 = addiu(sp, 0x1A8);
                        swc1(f0, v0, 0);
                    } else {
                        // 0x00466eac
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                    goto L_00466c60;
                }
                backedge(ctx);
                // 0x00466b00
                charge(ctx, 4);
                s2 = addiu(s2, -64);
                a1 = addiu(sp, 0x170);
                a0 = 8;
                a2 = s2;
                for (;;) {
                    // 0x00466b10
                    charge(ctx, 8);
                    lw(v1, a2, 0);
                    a0 = addiu(a0, -1);
                    lw(v0, a2, 4);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a2 = addiu(a2, 8);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00466b30
                charge(ctx, 2);
                lq(v0, sp, 0xA0);
                goto L_00466c64;
            }
        L_00466c60:
            charge(ctx, 1);
            lq(v0, sp, 0xA0);
        L_00466c64:
            charge(ctx, 6);
            s6 = addiu(s6, 1);
            s0 = addu(s0, v0);
            lw(v0, s5, anim::kHierNumNodes);
            v0 = slt(s6, v0);
            s1 = addiu(s1, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00466c7c
    charge(ctx, 2);
    v0 = 1;
    // 0x00466eb4
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
    sp = addiu(sp, 0x9B0);
}

// 0x00466EF0 sub_466EF0 -- 1692 bytes; frame 0x260: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_466EF0 [RpHAnimHierarchyUpdateMatrices]: Computes a hierarchy's node matrices from its interpolator. Flag 2 (no
// matrix array) goes to hAnimHierarchyUpdateFrames. Otherwise the root matrix is the parent hierarchy's matrix at the
// root offset for a sub-hierarchy (flag 1), identity for local-space matrices (flag 0x4000), else the parent frame's
// LTM; then for every node the keyframe apply callback turns the interpolated frame into a local matrix, which is
// multiplied by the parent matrix kept on a stack (node flags: 2 push, 1 pop) and stored in the matrix array (64
// bytes per node: the bone matrices RpSkin's palette update reads); with 0x2000 the node frames follow. Returns 1.
void sub_466EF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x00466ef0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x260);
    a3 = 0;
    sd(ra, sp, 0x90);
    a2 = 0;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s4, a0, anim::kHierFlags);
    v0 = s4 & 0x2;
    s3 = a0;
    if (v0 != 0) {
        // 0x0046726c
        charge(ctx, 4);
        jal(ctx, 0x46726Cu, gen::fn_sub_466730_00466730);  // [hAnimHierarchyUpdateFrames]
        ld(ra, sp, 0x90);
    } else {
        // 0x00466f34
        charge(ctx, 3);
        v0 = s4 & 0x1;
        if (v0 != 0) {
            // 0x0046727c
            charge(ctx, 4);
            lw(v1, s3, anim::kHierRootParentOffset);
            v0 = si(-1);
            if (v1 == v0) {
                backedge(ctx);
                goto L_00466f40;
            }
            // 0x0046728c
            charge(ctx, 6);
            lw(a1, s3, anim::kHierParentHier);
            a0 = sll(v1, 6);
            v0 = s4 & 0x2000;
            lw(v1, a1, anim::kHierMatrices);
            s6 = addu(v1, a0);
            if (v0 == 0) {
                backedge(ctx);
            } else {
                // 0x004672a4
                charge(ctx, 3);
                v0 = s4 & 0x4000;
                if (v0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004672b0
                    charge(ctx, 3);
                    lw(a2, a1, 20);
                    a3 = 1;
                    backedge(ctx);
                }
            }
            goto L_00466f58;
        }
    L_00466f40:
        charge(ctx, 3);
        v0 = s4 & 0x4000;
        if (v0 != 0) {
            // 0x004672bc
            charge(ctx, 21);
            a0 = 0x3F800000;
            v0 = 0x20000;
            sw(a0, sp, 0x208);
            v1 = v0 | 0x3;
            sw(a0, sp, 0x1F4);
            v0 = s4 & 0x2000;
            sw(a0, sp, 0x1E0);
            s6 = addiu(sp, 0x1E0);
            lw(a0, sp, 0x1EC);
            sw(zero, sp, 0x1F0);
            sw(zero, sp, 0x1E8);
            sw(zero, sp, 0x1E4);
            sw(zero, sp, 0x204);
            sw(zero, sp, 0x200);
            v1 = a0 | v1;
            sw(zero, sp, 0x1F8);
            sw(zero, sp, 0x218);
            sw(zero, sp, 0x214);
            sw(zero, sp, 0x210);
            sw(v1, sp, 0x1EC);
            if (v0 == 0) {
                backedge(ctx);
            } else {
                // 0x00467310
                charge(ctx, 3);
                lw(a2, s3, anim::kHierParentFrame);
                a3 = 1;
                backedge(ctx);
            }
        } else {
            // 0x00466f4c
            charge(ctx, 3);
            lw(a2, s3, anim::kHierParentFrame);
            a3 = 1;
            s6 = addiu(sp, 0x220);
        }
    L_00466f58:
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x00466f60
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x00466f68
                charge(ctx, 3);
                lw(s0, a2, 4);
                if (s0 == 0) {
                    goto L_00467354;
                }
                // 0x00466f74
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x466F74u, gen::fn_sub_4CAE30_004cae30);  // [rwFrameIsDirty]
                if (v0 == 0) {
                    // 0x0046731c
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x46731Cu, gen::fn_sub_4CB2F0_004cb2f0);  // [RwFrameGetLTM]
                    a2 = addiu(sp, 0x220);
                    a1 = 8;
                    for (;;) {
                        // 0x0046732c
                        charge(ctx, 8);
                        lw(a0, v0, 0);
                        a1 = addiu(a1, -1);
                        lw(v1, v0, 4);
                        sw(a0, a2, 0);
                        v0 = addiu(v0, 8);
                        sw(v1, a2, 4);
                        a2 = addiu(a2, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0046734c
                    charge(ctx, 2);
                    backedge(ctx);
                } else {
                    // 0x00466f84
                    charge(ctx, 3);
                    a2 = addiu(s0, 16);
                    a1 = addiu(sp, 0x220);
                    a0 = 8;
                    for (;;) {
                        // 0x00466f90
                        charge(ctx, 8);
                        lw(v1, a2, 0);
                        a0 = addiu(a0, -1);
                        lw(v0, a2, 4);
                        sw(v1, a1, 0);
                        a2 = addiu(a2, 8);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00466fb0
                    charge(ctx, 3);
                    lw(s2, s0, 4);
                    if (s2 != 0) {
                        // 0x00466fbc
                        charge(ctx, 5);
                        s1 = addiu(sp, 0x224);
                        s0 = addiu(sp, 0x124);
                        s5 = addiu(sp, 0x228);
                        s7 = addiu(sp, 0x128);
                        fp = addiu(sp, 0x22C);
                        for (;;) {
                            // 0x00466fd0
                            charge(ctx, 64);
                            v0 = addiu(sp, 0x230);
                            lw(a3, fp, 0x0);
                            lwc1(f3, v0, 0);
                            a0 = addiu(sp, 0x220);
                            lwc1(f4, s5, 0);
                            lwc1(f6, sp, 0x220);
                            lwc1(f5, s1, 0);
                            v0 = addiu(sp, 0x23C);
                            lw(a2, v0, 0);
                            swc1(f4, s7, 0);
                            swc1(f6, sp, 0x120);
                            swc1(f5, s0, 0);
                            v0 = addiu(sp, 0x234);
                            lwc1(f2, v0, 0);
                            v0 = addiu(sp, 0x24C);
                            lw(a1, v0, 0);
                            v0 = addiu(sp, 0x238);
                            lwc1(f1, v0, 0);
                            v0 = addiu(sp, 0x25C);
                            lw(v1, v0, 0);
                            v0 = addiu(sp, 0x240);
                            lwc1(f0, v0, 0);
                            v0 = addiu(sp, 0x12C);
                            sw(a3, v0, 0);
                            v0 = addiu(sp, 0x13C);
                            sw(a2, v0, 0);
                            v0 = addiu(sp, 0x130);
                            a2 = addiu(s2, 16);
                            swc1(f3, v0, 0);
                            v0 = addiu(sp, 0x14C);
                            sw(a1, v0, 0);
                            v0 = addiu(sp, 0x134);
                            a1 = addiu(sp, 0x120);
                            swc1(f2, v0, 0);
                            v0 = addiu(sp, 0x15C);
                            sw(v1, v0, 0);
                            v0 = addiu(sp, 0x138);
                            swc1(f1, v0, 0);
                            v0 = addiu(sp, 0x140);
                            swc1(f0, v0, 0);
                            v0 = addiu(sp, 0x244);
                            lwc1(f4, v0, 0);
                            v0 = addiu(sp, 0x248);
                            lwc1(f3, v0, 0);
                            v0 = addiu(sp, 0x250);
                            lwc1(f2, v0, 0);
                            v0 = addiu(sp, 0x254);
                            lwc1(f1, v0, 0);
                            v0 = addiu(sp, 0x258);
                            lwc1(f0, v0, 0);
                            v0 = addiu(sp, 0x144);
                            swc1(f4, v0, 0);
                            v0 = addiu(sp, 0x148);
                            swc1(f3, v0, 0);
                            v0 = addiu(sp, 0x150);
                            swc1(f2, v0, 0);
                            v0 = addiu(sp, 0x154);
                            swc1(f1, v0, 0);
                            v0 = addiu(sp, 0x158);
                            link(ctx, 0x4670BCu);  // $ra first: the delay slot below depends on it
                            swc1(f0, v0, 0);
                            call(ctx, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                            lw(s2, s2, 4);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                goto L_004670d0;
            }
        L_00467354:
            charge(ctx, 19);
            v1 = 0x3F800000;
            v0 = 0x20000;
            sw(v1, sp, 0x248);
            v0 = v0 | 0x3;
            sw(v1, sp, 0x234);
            sw(v1, sp, 0x220);
            lw(v1, sp, 0x22C);
            sw(zero, sp, 0x230);
            sw(zero, sp, 0x228);
            sw(zero, sp, 0x224);
            sw(zero, sp, 0x244);
            sw(zero, sp, 0x240);
            v0 = v1 | v0;
            sw(zero, sp, 0x238);
            sw(zero, sp, 0x258);
            sw(zero, sp, 0x254);
            sw(zero, sp, 0x250);
            sw(v0, sp, 0x22C);
            backedge(ctx);
        }
    L_004670d0:
        charge(ctx, 3);
        s5 = s4 & 0x2000;
        if (s5 != 0) {
            // 0x004670dc
            charge(ctx, 6);
            lw(v0, s3, anim::kHierParentFrame);
            lw(v1, v0, 160);
            lbu(v0, v1, 3);
            v0 = v0 & 0x3;
            if (v0 == 0) {
                // 0x004670f4
                charge(ctx, 21);
                a0 = 0x960000;
                a0 = addiu(a0, 300);  // &0x96012C
                lw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
                sw(v0, v1, 8);
                lw(v0, s3, anim::kHierParentFrame);
                lw(v0, v0, 160);
                sw(a0, v0, 12);
                lw(v1, s3, anim::kHierParentFrame);
                lw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
                lw(v1, v1, 160);
                v1 = addiu(v1, 8);
                sw(v1, v0, 4);
                lw(v0, s3, anim::kHierParentFrame);
                lw(v0, v0, 160);
                v0 = addiu(v0, 8);
                sw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
                lw(v0, s3, anim::kHierParentFrame);
                lw(v1, v0, 160);
                lbu(v0, v1, 3);
                v0 = v0 | 0x2;
                sb(v0, v1, 3);
            }
        }
        // 0x00467148
        charge(ctx, 13);
        lw(a0, s3, anim::kHierInterp);
        s2 = addiu(sp, 0x164);
        lw(v1, s3, anim::kHierNumNodes);
        fp = 0;
        lw(s7, s3, anim::kHierNodeInfo);
        lw(s1, s3, anim::kHierMatrices);
        lw(v0, a0, anim::kItpApplyCB);
        s0 = addiu(a0, 76);
        at = slt(0, v1);
        sq(v0, sp, 0xD0);
        lw(v0, a0, anim::kItpFrameSize);
        sq(v0, sp, 0xC0);
        if (at != 0) {
            // 0x0046717c
            charge(ctx, 4);
            v0 = s4 & 0x1000;
            sq(v0, sp, 0xB0);
            v0 = s4 & 0x4000;
            sq(v0, sp, 0xA0);
            for (;;) {
                // 0x0046718c
                charge(ctx, 5);
                lq(v0, sp, 0xD0);
                v1 = 0x460000;
                v1 = addiu(v1, 18272);  // &sub_464760
                if (v1 == v0) {
                    // 0x004673a0
                    charge(ctx, 75);
                    lwc1(f8, s0, 8);
                    v0 = 0x40000000;
                    lwc1(f7, s0, 12);
                    v1 = 3;
                    lwc1(f2, s0, 16);
                    lwc1(f1, s0, 20);
                    mtc1(v0, f6);
                    mul_s(f4, f8, f8);
                    v0 = 0x3F800000;
                    mul_s(f0, f2, f2);
                    mul_s(f12, f7, f2);
                    mul_s(f11, f2, f8);
                    mtc1(v0, f5);
                    mul_s(f10, f8, f7);
                    v0 = addiu(sp, 0xEC);
                    sw(v1, v0, 0);
                    v0 = addiu(sp, 0x110);
                    sw(zero, v0, 0);
                    mul_s(f9, f1, f8);
                    v0 = addiu(sp, 0x114);
                    sw(zero, v0, 0);
                    v0 = addiu(sp, 0x118);
                    sw(zero, v0, 0);
                    v0 = addiu(sp, 0xE4);
                    mul_s(f3, f7, f7);
                    mul_s(f8, f1, f7);
                    mul_s(f2, f1, f2);
                    add_s(f7, f3, f0);
                    add_s(f1, f4, f0);
                    add_s(f0, f4, f3);
                    add_s(f3, f10, f2);
                    sub_s(f2, f10, f2);
                    mul_s(f3, f6, f3);
                    mtc1(zero, f4);
                    swc1(f3, v0, 0);
                    mul_s(f2, f6, f2);
                    v0 = addiu(sp, 0xF0);
                    swc1(f2, v0, 0);
                    adda_s(f4, f5);
                    v0 = addiu(sp, 0xF4);
                    msub_s(f2, f6, f7);
                    adda_s(f4, f5);
                    msub_s(f1, f6, f1);
                    swc1(f1, v0, 0);
                    adda_s(f4, f5);
                    v0 = addiu(sp, 0x108);
                    msub_s(f0, f6, f0);
                    swc1(f0, v0, 0);
                    sub_s(f1, f11, f8);
                    v0 = addiu(sp, 0xE8);
                    add_s(f0, f11, f8);
                    mul_s(f1, f6, f1);
                    swc1(f1, v0, 0);
                    add_s(f1, f12, f9);
                    v0 = addiu(sp, 0x100);
                    mul_s(f0, f6, f0);
                    swc1(f0, v0, 0);
                    sub_s(f0, f12, f9);
                    v0 = addiu(sp, 0xF8);
                    mul_s(f1, f6, f1);
                    swc1(f1, v0, 0);
                    mul_s(f0, f6, f0);
                    v0 = addiu(sp, 0x104);
                    swc1(f0, v0, 0);
                    swc1(f2, sp, 0xE0);
                    v0 = addiu(sp, 0x110);
                    lwc1(f0, s0, 24);
                    swc1(f0, v0, 0);
                    lwc1(f0, s0, 28);
                    v0 = addiu(sp, 0x114);
                    swc1(f0, v0, 0);
                    lwc1(f0, s0, 32);
                    v0 = addiu(sp, 0x118);
                    swc1(f0, v0, 0);
                    backedge(ctx);
                } else {
                    // 0x004671a0
                    charge(ctx, 3);
                    a0 = addiu(sp, 0xE0);
                    a1 = s0;
                    jalr(ctx, 0x4671A4u, v0.u());
                }
                // 0x004671ac
                charge(ctx, 7);
                a0 = s1;
                a1 = addiu(sp, 0xE0);
                a2 = s6;
                jal(ctx, 0x4671B4u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                lw(s4, s7, 12);
                if (s4 != 0) {
                    // 0x004671c8
                    charge(ctx, 3);
                    lq(v0, sp, 0xB0);
                    if (v0 != 0) {
                        // 0x004674cc
                        charge(ctx, 3);
                        a2 = addiu(sp, 0xE0);
                        a1 = addiu(s4, 16);
                        a0 = 8;
                        for (;;) {
                            // 0x004674d8
                            charge(ctx, 8);
                            lw(v1, a2, 0);
                            a0 = addiu(a0, -1);
                            lw(v0, a2, 4);
                            sw(v1, a1, 0);
                            a2 = addiu(a2, 8);
                            sw(v0, a1, 4);
                            a1 = addiu(a1, 8);
                            if (i64(a0) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004674f8
                        charge(ctx, 2);
                        if (s5 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x00467500
                            charge(ctx, 4);
                            a0 = s4;
                            jal(ctx, 0x467500u, gen::fn_sub_4CB270_004cb270);  // [RwFrameUpdateObjects]
                            backedge(ctx);
                        }
                    }
                    // 0x004671d4
                    charge(ctx, 2);
                    if (s5 != 0) {
                        // 0x004671dc
                        charge(ctx, 3);
                        lq(v0, sp, 0xA0);
                        if (v0 != 0) {
                            // 0x00467510
                            charge(ctx, 6);
                            a0 = addiu(s4, 80);
                            a1 = s1;
                            a2 = addiu(sp, 0x220);
                            jal(ctx, 0x467518u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                            lbu(v1, s4, 3);
                            backedge(ctx);
                        } else {
                            // 0x004671e8
                            charge(ctx, 3);
                            a1 = addiu(s4, 80);
                            a0 = 8;
                            a2 = s1;
                            for (;;) {
                                // 0x004671f4
                                charge(ctx, 8);
                                lw(v1, a2, 0);
                                a0 = addiu(a0, -1);
                                lw(v0, a2, 4);
                                sw(v1, a1, 0);
                                a2 = addiu(a2, 8);
                                sw(v0, a1, 4);
                                a1 = addiu(a1, 8);
                                if (i64(a0) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00467214
                            charge(ctx, 1);
                            lbu(v1, s4, 3);
                        }
                        // 0x00467218
                        charge(ctx, 5);
                        v0 = si(-5);
                        v0 = v1 & v0;
                        v0 = v0 | 0x8;
                        sb(v0, s4, 3);
                    }
                }
                // 0x00467528
                charge(ctx, 5);
                lw(v1, s7, 8);
                v0 = 3;
                v1 = v1 & 0x3;
                if (v1 == v0) {
                    backedge(ctx);
                } else {
                    // 0x0046753c
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        backedge(ctx);
                        // 0x00467238
                        charge(ctx, 3);
                        sw(s6, s2, 0);
                        s2 = addiu(s2, 4);
                        s6 = s1;
                    } else {
                        // 0x00467548
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            backedge(ctx);
                            // 0x0046722c
                            charge(ctx, 3);
                            s2 = addiu(s2, -4);
                            lw(s6, s2, 0);
                        } else {
                            // 0x00467554
                            charge(ctx, 2);
                            if (v1 == 0) s6 = s1;
                            backedge(ctx);
                        }
                    }
                }
                // 0x00467244
                charge(ctx, 8);
                lq(v0, sp, 0xC0);
                fp = addiu(fp, 0x1);
                s1 = addiu(s1, 64);
                s0 = addu(s0, v0);
                lw(v0, s3, anim::kHierNumNodes);
                v0 = slt(fp, v0);
                s7 = addiu(s7, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00467264
        charge(ctx, 2);
        v0 = 1;
        // 0x0046755c
        charge(ctx, 1);
        ld(ra, sp, 0x90);
    }
    // 0x00467560 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x260);
}

// 0x00489020 sub_489020 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_489020 [skinSplitDataDestroy]: Frees a skin's split data (+56 block) and zeroes the six split fields
// (+44..+64). Returns 1.
void sub_489020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489020
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addiu(a0, 44);
    lw(a0, a0, anim::kSkinSplitRemap);
    if (a0 != 0) {
        // 0x0048903c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C RwFree slot
        jalr(ctx, 0x489044u, v0.u());
    }
    // 0x0048904c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    sw(zero, s0, 0);
    v0 = 1;
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(zero, s0, 16);
    sw(zero, s0, 20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00489080 sub_489080 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489080 [skinSplitDataStreamWrite]: Writes the split data: bone limit, mesh count, RLE count, then (when meshes)
// the remap / RLE-count / RLE block.
void sub_489080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489080
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = 4;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = addiu(s2, 44);
    s0 = a0;
    a1 = s1;
    jal(ctx, 0x4890A4u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
    if (v0 != 0) {
        // 0x004890bc
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(s1, 4);
        a2 = 4;
        jal(ctx, 0x4890C4u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 != 0) {
            // 0x004890dc
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(s1, 8);
            a2 = 4;
            jal(ctx, 0x4890E4u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 == 0) {
                // 0x00489108
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004890f4
                charge(ctx, 3);
                lw(v0, s2, anim::kSkinSplitNumMeshes);
                if (v0 != 0) {
                    // 0x00489110
                    charge(ctx, 12);
                    lw(a2, s1, 4);
                    a0 = s0;
                    lw(v0, s1, 8);
                    lw(v1, s2, anim::kSkinNumBones);
                    lw(a1, s1, 12);
                    a2 = sll(a2, 1);
                    v0 = sll(v0, 1);
                    v1 = addu(v1, a2);
                    a2 = addu(v1, v0);
                    jal(ctx, 0x489130u, gen::fn_sub_4C53F0_004c53f0);  // [RwStreamWrite]
                    if (v0 != 0) {
                        backedge(ctx);
                        goto L_00489100;
                    }
                    // 0x00489140
                    charge(ctx, 1);
                    v0 = 0;
                    // 0x00489144 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x40);
                    return;
                }
            L_00489100:
                charge(ctx, 2);
                v0 = s0;
            }
        } else {
            // 0x004890d4
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004890b4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00489144 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00489160 sub_489160 -- 448 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489160 [skinSplitDataStreamRead]: Reads the split data: bone limit, mesh count, RLE count; then one RwMalloc
// for the remap indices (bones bytes), RLE counts (2 x meshes) and RLE (2 x RLE count) and the block itself. Returns
// the stream or 0.
void sub_489160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00489160
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    a2 = 4;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    a1 = addiu(sp, 0xB4);
    sq(s1, sp, 0x10);
    s3 = addiu(s4, 44);
    link(ctx, 0x48919Cu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
    if (v0 != 0) {
        // 0x004891b4
        charge(ctx, 6);
        a0 = s5;
        a1 = addiu(sp, 0xBC);
        a2 = 4;
        jal(ctx, 0x4891BCu, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
        if (v0 != 0) {
            // 0x004891d4
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(sp, 0xB8);
            a2 = 4;
            jal(ctx, 0x4891DCu, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 == 0) {
                // 0x00489200
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004891ec
                charge(ctx, 3);
                lw(s1, sp, 0xBC);
                if (i64(s1) > 0) {
                    // 0x00489208
                    charge(ctx, 21);
                    lw(v0, sp, 0xB4);
                    a0 = s4;
                    lw(s6, sp, 0xB8);
                    s0 = s3;
                    lw(s7, s4, anim::kSkinNumBones);
                    link(ctx, 0x48921Cu);  // $ra first: the delay slot below depends on it
                    sq(v0, sp, 0xA0);
                    call(ctx, gen::fn_sub_489020_00489020);  // [skinSplitDataDestroy]
                    v0 = 0x30000;
                    fp = sll(s1, 1);
                    a1 = v0 | 0x116;
                    v1 = sll(s6, 1);
                    v0 = 0x960000;
                    a0 = addu(s7, fp);
                    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
                    s2 = addu(a0, v1);
                    a0 = s2;
                    jalr(ctx, 0x489244u, v0.u());
                    sw(v0, s0, 12);
                    lw(a0, s0, 12);
                    if (a0 == 0) {
                        // 0x004892e4
                        charge(ctx, 2);
                        v1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048925c
                        charge(ctx, 14);
                        a2 = s2;
                        a1 = 0;
                        jal(ctx, 0x489260u, gen::fn_memset_00521408);  // [memset]
                        lq(v0, sp, 0xA0);
                        v1 = s4;
                        sw(v0, s0, 0);
                        sw(s1, s0, 4);
                        sw(s6, s0, 8);
                        lw(v0, s0, 12);
                        v0 = addu(v0, s7);
                        sw(v0, s0, 16);
                        lw(v0, s0, 16);
                        v0 = addu(v0, fp);
                        sw(v0, s0, 20);
                    }
                    // 0x00489294
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x004892ec
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0048929c
                        charge(ctx, 12);
                        lw(a2, s3, 4);
                        a0 = s5;
                        lw(v0, s3, 8);
                        lw(v1, s4, anim::kSkinNumBones);
                        lw(a1, s3, 12);
                        a2 = sll(a2, 1);
                        v0 = sll(v0, 1);
                        v1 = addu(v1, a2);
                        a2 = addu(v1, v0);
                        jal(ctx, 0x4892BCu, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
                        if (v0 != 0) {
                            backedge(ctx);
                            goto L_004891f8;
                        }
                        // 0x004892cc
                        charge(ctx, 6);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C RwFree slot
                        a0 = s3;
                        jalr(ctx, 0x4892D4u, v0.u());
                        v0 = 0;
                    }
                    // 0x004892f0 (the shared epilogue, written out on this path)
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
                    sp = addiu(sp, 0xC0);
                    return;
                }
            L_004891f8:
                charge(ctx, 2);
                v0 = s5;
            }
        } else {
            // 0x004891cc
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004891ac
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004892f0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xC0);
}

// 0x00489320 sub_489320 -- 48 bytes; leaf frame (no stack)
// sub_489320 [skinSplitDataStreamGetSize]: Size of the split data in the stream: 12, plus the block when meshes.
void sub_489320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00489320
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, anim::kSkinSplitNumMeshes);
    v0 = 12;
    if (v1 != 0) {
        // 0x0048932c
        charge(ctx, 7);
        a2 = sll(v1, 1);
        lw(a1, a0, anim::kSkinNumBones);
        lw(v1, a0, anim::kSkinSplitNumRLE);
        a0 = addu(a1, a2);
        v1 = sll(v1, 1);
        v1 = addu(a0, v1);
        v0 = addu(v0, v1);
    }
    // 0x00489348 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00489350 sub_489350 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489350 [skinAtomicSetType]: RpSkinAtomicSetType (atomic $a0, type $a1): type 2 (MatFX) falls back to 1 when
// MatFX (0x120) is not attached, type 3 when plugin 0x12E is not; then skinAtomicSetPipeline.
void sub_489350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489350
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 288;
    jal(ctx, 0x489368u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
    v1 = si(-1);
    if (v0 == v1) {
        // 0x0048937c
        charge(ctx, 3);
        v0 = 2;
        if (s0 != v0) {
            goto L_004893a0;
        }
        // 0x00489388
        charge(ctx, 1);
        s0 = 1;
        goto L_0048938c;
    }
L_004893a0:
    charge(ctx, 5);
    a0 = 302;
    jal(ctx, 0x4893A0u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
    v1 = si(-1);
    if (v0 != v1) {
        backedge(ctx);
    } else {
        // 0x004893b4
        charge(ctx, 3);
        v0 = 3;
        if (s0 != v0) {
            backedge(ctx);
        } else {
            // 0x004893c0
            charge(ctx, 2);
            s0 = 1;
            backedge(ctx);
        }
    }
L_0048938c:
    charge(ctx, 5);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x489390u, gen::fn_sub_48AC10_0048ac10);  // [skinAtomicSetPipeline]
    ld(ra, sp, 0x20);
    // 0x004893c8
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004893E0 sub_4893E0 -- 128 bytes; leaf frame (no stack)
// sub_4893E0 [skinFindMaxWeights]: Sets the skin's maximum weights per vertex (+16): 1 + the highest weight slot in
// use over $a2 vertex weight records ($a1, 16 bytes each), at most 4.
void sub_4893E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x004893e0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 1;
    at = sltu(0, a2);
    sw(v1, a0, anim::kSkinMaxWeights);
    t2 = 0;
    if (at != 0) {
        // 0x004893f4
        charge(ctx, 1);
        a3 = 4;
        for (;;) {
            // 0x004893f8
            charge(ctx, 4);
            lw(t1, a0, 16);
            at = sltiu(t1, 4);
            if (at != 0) {
                // 0x00489408
                charge(ctx, 2);
                v1 = sll(t1, 2);
                t0 = addu(a1, v1);
                for (;;) {
                    // 0x00489410
                    charge(ctx, 3);
                    lw(v1, t0, 0);
                    if (v1 == 0) {
                        goto L_00489448;
                    }
                    // 0x0048941c
                    charge(ctx, 6);
                    lw(v1, a0, 16);
                    v1 = addiu(v1, 1);
                    sw(v1, a0, 16);
                    lw(v1, a0, 16);
                    if (v1 != a3) {
                        // 0x00489434
                        charge(ctx, 4);
                        t1 = addiu(t1, 1);
                        v1 = sltiu(t1, 4);
                        t0 = addiu(t0, 4);
                        if (v1 == 0) {
                            goto L_00489444_7;
                        }
                        backedge(ctx);
                        continue;
                    }
                    break;
                }
                break;
            }
        L_00489448:
            charge(ctx, 4);
            t2 = addiu(t2, 1);
            v1 = sltu(t2, a2);
            a1 = addiu(a1, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00489458 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00489444_7:
    charge(ctx, 1);
    goto L_00489448;
}

// 0x00489460 sub_489460 -- 236 bytes; frame 0x10: s0 sp+0x0 (sq)
// sub_489460 [skinFindUsedBones]: Builds the used-bone list ($a3, count in *$a4) from $t1 vertices: each non-zero
// weight's bone index byte, added once.
void sub_489460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00489460
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    at = sltu(0, t1);
    sq(s0, sp, 0x0);
    t5 = 0;
    sw(zero, t0, 0);
    if (at != 0) {
        // 0x00489478
        charge(ctx, 1);
        v1 = 1;
        for (;;) {
            // 0x0048947c
            charge(ctx, 4);
            lw(t2, a0, 16);
            at = sltu(0, t2);
            t4 = 0;
            if (at != 0) {
                // 0x0048948c
                charge(ctx, 3);
                t3 = a2;
                t2 = 0;
                for (;;) {
                    // 0x00489498
                    charge(ctx, 3);
                    lw(t6, t3, 0);
                    if (t6 != 0) {
                        // 0x004894a4
                        charge(ctx, 8);
                        lw(t6, a1, 0);
                        t9 = v1;
                        lw(t7, t0, 0);
                        s0 = 0;
                        t6 = srlv(t6, t2);
                        at = sltu(0, t7);
                        t8 = t6 & 0xFF;
                        if (at != 0) {
                            // 0x004894c4
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004894c8
                                charge(ctx, 4);
                                t6 = addu(a3, s0);
                                lbu(t6, t6, 0);
                                if (t8 == t6) {
                                    goto L_004894d8_8;
                                }
                                // 0x004894e0
                                charge(ctx, 4);
                                s0 = addiu(s0, 1);
                                t6 = sltu(s0, t7);
                                if (t6 != 0) {
                                    backedge(ctx);
                                    continue;
                                }
                                break;
                            }
                        }
                    L_004894f0:
                        charge(ctx, 2);
                        if (t9 != 0) {
                            // 0x004894f8
                            charge(ctx, 6);
                            t6 = addu(a3, t7);
                            sb(t8, t6, 0);
                            lw(t6, t0, 0);
                            t6 = addiu(t6, 1);
                            sw(t6, t0, 0);
                        }
                    }
                    // 0x00489510
                    charge(ctx, 6);
                    lw(t6, a0, 16);
                    t4 = addiu(t4, 1);
                    t3 = addiu(t3, 4);
                    t6 = sltu(t4, t6);
                    t2 = addiu(t2, 8);
                    if (t6 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00489528
            charge(ctx, 5);
            t5 = addiu(t5, 1);
            t2 = sltu(t5, t1);
            a2 = addiu(a2, 16);
            a1 = addiu(a1, 4);
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048953c
        charge(ctx, 1);
    }
    // 0x00489540 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_004894d8_8:
    charge(ctx, 2);
    t9 = 0;
    goto L_004894f0;
}

// 0x00489550 sub_489550 -- 476 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489550 [skinCreateData]: Allocates a skin's data block for $a1 bones, $a2 used bones and $a3 vertices
// (used-bone list, 16-aligned bone matrices, indices, weights), and copies what is given (used bones, weights,
// indices, matrices in reverse order). Returns 1, 0 when the allocation failed.
void sub_489550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00489550
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = t3;
    sq(s6, sp, 0x60);
    s7 = t1;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    s2 = a3;
    sq(s1, sp, 0x10);
    v0 = sll(s2, 2);
    sq(s0, sp, 0x0);
    v1 = addu(v0, s2);
    s1 = t0;
    v0 = sll(s4, 6);
    a0 = sll(v1, 2);
    sq(v0, sp, 0xA0);
    v1 = 0x30000;
    v0 = addu(a0, v0);
    a1 = v1 | 0x116;
    v1 = addu(s3, v0);
    s0 = t2;
    v0 = 0x960000;
    s6 = addiu(v1, 15);
    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
    a0 = s6;
    jalr(ctx, 0x4895CCu, v0.u());
    sw(v0, s5, anim::kSkinDataBlock);
    lw(a0, s5, anim::kSkinDataBlock);
    if (a0 == 0) {
        // 0x004896f8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004895e4
        charge(ctx, 22);
        a2 = s6;
        a1 = 0;
        jal(ctx, 0x4895E8u, gen::fn_memset_00521408);  // [memset]
        sw(s4, s5, anim::kSkinNumBones);
        v0 = si(-16);
        sw(s3, s5, anim::kSkinNumUsedBones);
        s4 = sll(s2, 2);
        lw(v1, s5, anim::kSkinDataBlock);
        sw(v1, s5, anim::kSkinUsedBones);
        lw(v1, s5, anim::kSkinUsedBones);
        v1 = addu(v1, s3);
        v1 = addiu(v1, 15);
        v0 = v1 & v0;
        sw(v0, s5, anim::kSkinBoneMatrices);
        lw(v1, s5, anim::kSkinBoneMatrices);
        lq(v0, sp, 0xA0);
        v0 = addu(v1, v0);
        sw(v0, s5, anim::kSkinVertexIndices);
        lw(v0, s5, anim::kSkinVertexIndices);
        v0 = addu(v0, s4);
        sw(v0, s5, anim::kSkinVertexWeights);
        if (s1 != 0) {
            // 0x0048963c
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00489644
                charge(ctx, 4);
                lw(a0, s5, anim::kSkinUsedBones);
                a1 = s1;
                a2 = s3;
                jal(ctx, 0x48964Cu, gen::fn_memcpy_00521250);  // [memcpy]
            }
        }
        // 0x00489654
        charge(ctx, 2);
        if (fp != 0) {
            // 0x0048965c
            charge(ctx, 3);
            lw(v0, s5, anim::kSkinNumBones);
            t2 = addiu(v0, -1);
            if (v0 != 0) {
                // 0x00489668
                charge(ctx, 3);
                t0 = sll(t2, 6);
                v1 = 8;
                t1 = addu(fp, t0);
                for (;;) {
                    // 0x00489674
                    charge(ctx, 5);
                    lw(v0, s5, anim::kSkinBoneMatrices);
                    a1 = v1;
                    a2 = t1;
                    a3 = addu(v0, t0);
                    for (;;) {
                        // 0x00489688
                        charge(ctx, 8);
                        lw(a0, a2, 0);
                        a1 = addiu(a1, -1);
                        lw(v0, a2, 4);
                        sw(a0, a3, 0);
                        a2 = addiu(a2, 8);
                        sw(v0, a3, 4);
                        a3 = addiu(a3, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004896a8
                    charge(ctx, 5);
                    v0 = t2;
                    t1 = addiu(t1, -64);
                    t0 = addiu(t0, -64);
                    t2 = addiu(t2, -1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004896bc
                charge(ctx, 1);
            }
        }
        // 0x004896c0
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x004896c8
            charge(ctx, 4);
            lw(a0, s5, anim::kSkinVertexIndices);
            a1 = s0;
            a2 = s4;
            jal(ctx, 0x4896D0u, gen::fn_memcpy_00521250);  // [memcpy]
        }
        // 0x004896d8
        charge(ctx, 2);
        if (s7 != 0) {
            // 0x004896e0
            charge(ctx, 4);
            lw(a0, s5, anim::kSkinVertexWeights);
            a2 = sll(s2, 4);
            a1 = s7;
            jal(ctx, 0x4896E8u, gen::fn_memcpy_00521250);  // [memcpy]
        }
        // 0x004896f0
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004896fc (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}

// 0x00489730 sub_489730 -- 264 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489730 [skinOpen]: RpSkin's engine-open callback: on the first open picks the pipelines available (MatFX,
// 0x12E), creates the 72-byte skin free list (0x95DE28) and the 16 KiB bone-matrix palette (0x95DE20, aligned at
// 0x95DE1C); counts the opens (0x95DE30).
void sub_489730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489730
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -8656);  // 0x95DE30 RpSkin: open count
    s0 = a0;
    if (v0 == 0) {
        // 0x0048976c
        charge(ctx, 6);
        a0 = 288;
        s1 = 1;
        jal(ctx, 0x489770u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
        v1 = si(-1);
        if (v0 != v1) {
            // 0x00489784
            charge(ctx, 1);
            s1 = s1 | 0x2;
        }
        // 0x00489788
        charge(ctx, 5);
        a0 = 302;
        jal(ctx, 0x489788u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
        v1 = si(-1);
        if (v0 != v1) {
            // 0x0048979c
            charge(ctx, 1);
            s1 = s1 | 0x4;
        }
        // 0x004897a0
        charge(ctx, 33);
        a0 = s1;
        jal(ctx, 0x4897A0u, gen::fn_sub_48ABF0_0048abf0);  // [skinPlatformOpen]
        lw(a1, gp, -20776);  // 0x7CDBC8
        t0 = 0x960000;
        lw(a3, gp, -20772);  // 0x7CDBCC
        v0 = 0x40000;
        a0 = 72;
        a2 = 4;
        t0 = addiu(t0, -8736);  // &0x95DDE0
        t1 = v0 | 0x116;
        jal(ctx, 0x4897C4u, gen::fn_sub_4C3B60_004c3b60);  // [RwFreeListCreate]
        v1 = 0x960000;
        sw(v0, v1, -8664);  // 0x95DE28 RpSkin: skin free list
        v0 = 0x40000;
        a1 = v0 | 0x116;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 RwMalloc slot
        a0 = 16399;
        jalr(ctx, 0x4897E4u, v0.u());
        v1 = 0x960000;
        a0 = v0;
        sw(v0, v1, -8672);  // 0x95DE20 RpSkin: palette allocation
        a1 = 0;
        a2 = 16399;
        jal(ctx, 0x4897FCu, gen::fn_memset_00521408);  // [memset]
        v0 = 0x960000;
        v1 = si(-16);
        lw(a0, v0, -8672);  // 0x95DE20 RpSkin: palette allocation
        a0 = addiu(a0, 15);
        v0 = 0x960000;
        v1 = a0 & v1;
        sw(v1, v0, -8676);  // 0x95DE1C RpSkin: bone-matrix palette (aligned)
        backedge(ctx);
    }
    // 0x00489750
    charge(ctx, 7);
    v1 = 0x960000;
    v0 = s0;
    lw(a0, v1, -8656);  // 0x95DE30 RpSkin: open count
    v1 = 0x960000;
    a0 = addiu(a0, 1);
    sw(a0, v1, -8656);  // 0x95DE30 RpSkin: open count
    // 0x00489824
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00489840 sub_489840 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_489840 [skinClose]: RpSkin's engine-close callback: on the last close destroys the free list and the palette.
void sub_489840(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00489840
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    lw(v1, v1, -8656);  // 0x95DE30 RpSkin: open count
    s0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, v0, -8656);  // 0x95DE30 RpSkin: open count
    if (v1 == 0) {
        // 0x00489870
        charge(ctx, 15);
        jal(ctx, 0x489870u, gen::fn_sub_48AC00_0048ac00);  // [skinPlatformClose]
        v0 = 0x960000;
        link(ctx, 0x48987Cu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, -8664);
        call(ctx, gen::fn_sub_4C3C30_004c3c30);  // [RwFreeListDestroy]
        v0 = 0x960000;
        v1 = 0x960000;
        sw(zero, v0, -8664);  // 0x95DE28 RpSkin: skin free list
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C RwFree slot
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x489898u);  // $ra = the return address
        lw(a0, v1, -8672);
        call_ptr(ctx, jt);
        v0 = 0x960000;
        sw(zero, v0, -8672);  // 0x95DE20 RpSkin: palette allocation
        backedge(ctx);
    }
    // 0x00489868
    charge(ctx, 2);
    v0 = s0;
    // 0x004898ac
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004898C0 sub_4898C0 -- 24 bytes; leaf frame (no stack)
// sub_4898C0 [skinGeometryCtor]: Geometry constructor: skin = 0.
void sub_4898C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004898c0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v1, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    v1 = addu(a0, v1);
    v0 = a0;
    sw(zero, v1, 0);
}

// 0x004898E0 sub_4898E0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4898E0 [skinGeometryDtor]: Geometry destructor: destroys the geometry's skin.
void sub_4898E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004898e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    s0 = a0;
    v0 = addu(s0, v0);
    lw(s1, v0, 0);
    if (s1 != 0) {
        // 0x0048990c
        charge(ctx, 8);
        jal(ctx, 0x48990Cu, gen::fn_sub_48A790_0048a790);  // [skinDestroyNoop]
        a0 = s1;
        jal(ctx, 0x489914u, gen::fn_sub_48A370_0048a370);  // [skinDestroy]
        v1 = 0x960000;
        lw(v1, v1, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
        v1 = addu(s0, v1);
        sw(v0, v1, 0);
    }
    // 0x0048992c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00489950 sub_489950 -- 8 bytes; leaf frame (no stack)
// sub_489950 [skinGeometryCopy]: Geometry copy callback: nothing (returns the geometry).
void sub_489950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00489950
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x00489960 sub_489960 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_489960 [skinAtomicCtor]: Atomic constructor: the 4-byte extension (the hierarchy) = 0.
void sub_489960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489960
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    a1 = 0;
    sq(s0, sp, 0x0);
    a2 = 4;
    lw(v0, v0, -8684);  // 0x95DE14 RpSkin: atomic extension offset (hierarchy)
    s0 = a0;
    a0 = addu(s0, v0);
    jal(ctx, 0x489980u, gen::fn_memset_00521408);  // [memset]
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004899A0 sub_4899A0 -- 28 bytes; leaf frame (no stack)
// sub_4899A0 [skinAtomicDtor]: Atomic destructor: clears the hierarchy link.
void sub_4899A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004899a0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, -8684);  // 0x95DE14 RpSkin: atomic extension offset (hierarchy)
    v1 = addu(a0, v0);
    lw(v0, v1, 0);
    if (v0 == 0) {
        gen::fn_sub_4899BC_004899bc(ctx);  // tail call
        return;
    }
    // 0x004899b8
    charge(ctx, 1);
    sw(zero, v1, 0);
    gen::fn_sub_4899BC_004899bc(ctx);  // tail call
}

// 0x004899BC sub_4899BC -- 8 bytes; leaf frame (no stack)
// sub_4899BC [skinAtomicDtorTail]: Returns $a0 (the tail of skinAtomicDtor, reached by its jal).
void sub_4899BC(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004899bc
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x004899D0 sub_4899D0 -- 32 bytes; leaf frame (no stack)
// sub_4899D0 [skinAtomicCopy]: Atomic copy callback: copies the hierarchy link.
void sub_4899D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004899d0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v1, v0, -8684);  // 0x95DE14 RpSkin: atomic extension offset (hierarchy)
    a1 = addu(a1, v1);
    v0 = a0;
    v1 = addu(a0, v1);
    lw(a0, a1, 0);
    sw(a0, v1, 0);
}

// 0x004899F0 sub_4899F0 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4899F0 [skinAtomicAlwaysCB]: Atomic stream-always callback: a skinned geometry gets the skin pipeline (type 2
// when MatFX is attached and enabled on the atomic).
void sub_4899F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004899f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 1;
    s0 = a0;
    a0 = 288;
    jal(ctx, 0x489A08u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
    v1 = si(-1);
    if (v0 != v1) {
        // 0x00489a4c
        charge(ctx, 6);
        a0 = 288;
        jal(ctx, 0x489A4Cu, gen::fn_sub_492D00_00492d00);  // [RpAtomicGetPluginOffset]
        v0 = addu(s0, v0);
        lbu(v0, v0, 0);
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x00489a64
            charge(ctx, 2);
            s1 = 2;
            backedge(ctx);
        }
    }
    // 0x00489a1c
    charge(ctx, 3);
    lw(a0, s0, anim::kAtmGeometry);
    if (a0 != 0) {
        // 0x00489a28
        charge(ctx, 4);
        jal(ctx, 0x489A28u, gen::fn_sub_48A2C0_0048a2c0);  // [RpSkinGeometryGetSkin]
        if (v0 != 0) {
            // 0x00489a38
            charge(ctx, 3);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x489A3Cu, gen::fn_sub_489350_00489350);  // [skinAtomicSetType]
        }
    }
    // 0x00489a44
    charge(ctx, 2);
    v0 = 1;
    // 0x00489a6c
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00489A80 sub_489A80 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489A80 [skinAtomicRightsCB]: Atomic stream-rights callback: a skinned geometry gets the pipeline of the type in
// the rights data ($a3).
void sub_489A80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489a80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, anim::kAtmGeometry);
    s0 = a3;
    if (a0 != 0) {
        // 0x00489aa0
        charge(ctx, 4);
        jal(ctx, 0x489AA0u, gen::fn_sub_48A2C0_0048a2c0);  // [RpSkinGeometryGetSkin]
        if (v0 != 0) {
            // 0x00489ab0
            charge(ctx, 3);
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x489AB4u, gen::fn_sub_489350_00489350);  // [skinAtomicSetType]
        }
    }
    // 0x00489abc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = 1;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00489AE0 sub_489AE0 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_489AE0 [skinGeometryStreamGetSize]: Geometry stream-size: 0 without a skin; native geometries (flag 0x1000000)
// via skinNativeStreamGetSize, else 4 + used bones + 20 per vertex + 64 per bone + the split data.
void sub_489AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489ae0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, v1, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    v1 = addu(a0, v1);
    lw(a1, v1, 0);
    v0 = 0;
    if (a1 != 0) {
        // 0x00489b04
        charge(ctx, 5);
        lw(v1, a0, anim::kGeoFlags);
        v0 = 0x1000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x00489b54
            charge(ctx, 2);
            jal(ctx, 0x489B54u, gen::fn_sub_48A7A0_0048a7a0);  // [skinNativeStreamGetSize]
        } else {
            // 0x00489b18
            charge(ctx, 15);
            lw(a3, a0, 20);
            a2 = 4;
            lw(v1, a1, 4);
            lw(v0, a1, 0);
            a0 = a1;
            a2 = addu(a2, v1);
            a1 = sll(a3, 2);
            v1 = sll(a3, 4);
            a1 = addu(a2, a1);
            v0 = sll(v0, 6);
            v1 = addu(a1, v1);
            s0 = addu(v1, v0);
            jal(ctx, 0x489B44u, gen::fn_sub_489320_00489320);  // [skinSplitDataStreamGetSize]
            v0 = addu(s0, v0);
        }
    }
    // 0x00489b5c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00489B70 sub_489B70 -- 352 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489B70 [skinGeometryStreamWrite]: Geometry stream-write: the packed counts {bones, used bones, max weights},
// the used-bone list, the indices, the weights, the bone matrices and the split data (native geometries via
// skinNativeStreamWrite).
void sub_489B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00489b70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x960000;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    v0 = addu(a2, v0);
    lw(s1, v0, 0);
    s2 = a0;
    if (s1 != 0) {
        // 0x00489b9c
        charge(ctx, 5);
        lw(v1, a2, anim::kGeoFlags);
        v0 = 0x1000000;
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x00489bc8
            charge(ctx, 17);
            lw(t0, s1, 16);
            a3 = 0xFF0000;
            lw(v1, s1, 4);
            a1 = addiu(sp, 0x4C);
            lw(s0, a2, anim::kGeoNumVertices);
            lbu(v0, s1, 0);
            t0 = sll(t0, 16);
            v1 = sll(v1, 8);
            a3 = t0 & a3;
            v1 = v1 & 0xFF00;
            a2 = 4;
            v1 = a3 | v1;
            v0 = v0 | v1;
            link(ctx, 0x489BFCu);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x4C);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 == 0) {
                // 0x00489c8c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x00489c0c
                charge(ctx, 6);
                lw(a1, s1, 8);
                lw(a2, s1, 4);
                a0 = s2;
                jal(ctx, 0x489C14u, gen::fn_sub_4C53F0_004c53f0);  // [RwStreamWrite]
                if (v0 == 0) {
                    // 0x00489c94
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00489c24
                    charge(ctx, 6);
                    lw(a1, s1, 20);
                    a2 = sll(s0, 2);
                    a0 = s2;
                    jal(ctx, 0x489C2Cu, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                    if (v0 == 0) {
                        // 0x00489c9c
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x00489c3c
                        charge(ctx, 6);
                        lw(a1, s1, 24);
                        a2 = sll(s0, 4);
                        a0 = s2;
                        jal(ctx, 0x489C44u, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
                        if (v0 == 0) {
                            // 0x00489ca4
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x00489c54
                            charge(ctx, 7);
                            lw(v0, s1, 0);
                            a0 = s2;
                            lw(a1, s1, 12);
                            a2 = sll(v0, 6);
                            jal(ctx, 0x489C60u, gen::fn_sub_4C1750_004c1750);  // [RwStreamWriteReal]
                            if (v0 == 0) {
                                // 0x00489cac
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x00489c70
                                charge(ctx, 5);
                                a1 = s1;
                                a0 = s2;
                                jal(ctx, 0x489C74u, gen::fn_sub_489080_00489080);  // [skinSplitDataStreamWrite]
                                if (v0 != 0) {
                                    goto L_00489cb4;
                                }
                                // 0x00489c84
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        }
                    }
                }
            }
        } else {
            // 0x00489bb0
            charge(ctx, 4);
            a1 = a2;
            jal(ctx, 0x489BB0u, gen::fn_sub_48A800_0048a800);  // [skinNativeStreamWrite]
            if (v0 != 0) {
                goto L_00489cb4;
            }
            // 0x00489bc0
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x00489cb8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00489cb4:
    charge(ctx, 1);
    v0 = s2;
    // 0x00489cb8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00489CD0 sub_489CD0 -- 584 bytes; frame 0x190: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489CD0 [skinGeometryStreamRead]: Geometry stream-read: the packed counts, a new skin (free list) with its data
// block, the used-bone list (or built from the weights), indices, weights, the bone matrices and the split data; the
// skin is set on the geometry (skinGeometrySetSkin). Native geometries via skinNativeStreamRead.
void sub_489CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00489cd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    v0 = 0x1000000;
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a2, anim::kGeoFlags);
    v0 = v1 & v0;
    s4 = a2;
    if (v0 == 0) {
        // 0x00489d2c
        charge(ctx, 5);
        a1 = addiu(sp, 0x18C);
        a2 = 4;
        jal(ctx, 0x489D30u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
        if (v0 == 0) {
            // 0x00489e14
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x00489d40
            charge(ctx, 22);
            v0 = 0x960000;
            lw(a2, sp, 0x18C);
            lw(a0, v0, -8664);  // 0x95DE28 RpSkin: skin free list
            lw(s2, s4, anim::kGeoNumVertices);
            v1 = srl(a2, 8);
            s6 = a2 & 0xFF;
            v0 = 0x30000;
            s3 = v1 & 0xFF;
            a1 = v0 | 0x116;
            v1 = srl(a2, 16);
            v0 = 0x960000;
            s0 = v1 & 0xFF;
            lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x489D74u);  // $ra = the return address
            sw(s3, sp, 0x188);
            call_ptr(ctx, jt);
            s1 = v0;
            a1 = 0;
            a0 = s1;
            a2 = 72;
            jal(ctx, 0x489D88u, gen::fn_memset_00521408);  // [memset]
            if (s0 == 0) {
                // 0x00489e1c
                charge(ctx, 6);
                a0 = s1;
                a1 = 0;
                a2 = s2;
                jal(ctx, 0x489E24u, gen::fn_sub_4893E0_004893e0);  // [skinFindMaxWeights]
                lw(v0, sp, 0x188);
                backedge(ctx);
            } else {
                // 0x00489d98
                charge(ctx, 1);
                lw(v0, sp, 0x188);
            }
            // 0x00489d9c
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00489da4
                charge(ctx, 7);
                a0 = s1;
                a1 = 0;
                a2 = 0;
                a3 = addiu(sp, 0x80);
                t0 = addiu(sp, 0x188);
                t1 = s2;
                jal(ctx, 0x489DB8u, gen::fn_sub_489460_00489460);  // [skinFindUsedBones]
            }
            // 0x00489dc0
            charge(ctx, 11);
            lw(a2, sp, 0x188);
            a1 = s6;
            a0 = s1;
            a3 = s2;
            t0 = addiu(sp, 0x80);
            t1 = 0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x489DDCu, gen::fn_sub_489550_00489550);  // [skinCreateData]
            if (v0 == 0) {
                // 0x00489e34
                charge(ctx, 8);
                v0 = 0x960000;
                lw(a0, v0, -8664);  // 0x95DE28 RpSkin: skin free list
                v0 = 0x960000;
                lw(v0, v0, 396);  // 0x96018C RwFreeListFree slot
                a1 = s1;
                jalr(ctx, 0x489E44u, v0.u());
                s1 = 0;
                backedge(ctx);
            }
            // 0x00489dec
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x00489e54
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x00489df4
                charge(ctx, 6);
                lw(a1, s1, 8);
                a0 = s5;
                a2 = s3;
                jal(ctx, 0x489DFCu, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
                if (s3 == v0) {
                    // 0x00489e5c
                    charge(ctx, 6);
                    lw(a1, s1, 20);
                    a2 = sll(s2, 2);
                    a0 = s5;
                    jal(ctx, 0x489E64u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                    if (v0 == 0) {
                        // 0x00489ed4
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x00489e74
                        charge(ctx, 6);
                        lw(a1, s1, 24);
                        a2 = sll(s2, 4);
                        a0 = s5;
                        jal(ctx, 0x489E7Cu, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
                        if (v0 == 0) {
                            // 0x00489edc
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x00489e8c
                            charge(ctx, 8);
                            sw(s0, s1, 16);
                            a0 = s5;
                            lw(v0, s1, 0);
                            lw(a1, s1, 12);
                            a2 = sll(v0, 6);
                            jal(ctx, 0x489E9Cu, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
                            if (v0 == 0) {
                                // 0x00489ee4
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x00489eac
                                charge(ctx, 5);
                                a0 = s5;
                                a1 = s1;
                                jal(ctx, 0x489EB0u, gen::fn_sub_489160_00489160);  // [skinSplitDataStreamRead]
                                if (v0 == 0) {
                                    // 0x00489eec
                                    charge(ctx, 1);
                                    v0 = 0;
                                } else {
                                    // 0x00489ec0
                                    charge(ctx, 5);
                                    a0 = s4;
                                    a1 = s1;
                                    jal(ctx, 0x489EC4u, gen::fn_sub_48A2E0_0048a2e0);  // [skinGeometrySetSkin]
                                    backedge(ctx);
                                L_00489d24:
                                    charge(ctx, 2);
                                    v0 = s5;
                                }
                            }
                        }
                    }
                } else {
                    // 0x00489e0c
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
        }
    } else {
        // 0x00489d0c
        charge(ctx, 4);
        a1 = s4;
        jal(ctx, 0x489D0Cu, gen::fn_sub_48A9A0_0048a9a0);  // [skinNativeStreamRead]
        if (v0 != 0) {
            goto L_00489d24;
        }
        // 0x00489d1c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00489ef0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x00489F20 sub_489F20 -- 596 bytes; frame 0x180: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_489F20 [skinAtomicStreamRead]: Atomic-side skin read for old files: when the geometry already has a skin the
// chunk is skipped, else the bone count, the indices, the weights and the bone matrices (each preceded by a 12-byte
// skip) make the skin.
void sub_489F20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00489f20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(s1, a2, 24);
    s0 = t0;
    a0 = s1;
    jal(ctx, 0x489F4Cu, gen::fn_sub_48A2C0_0048a2c0);  // [RpSkinGeometryGetSkin]
    if (v0 == 0) {
        // 0x00489f80
        charge(ctx, 6);
        a0 = s2;
        a1 = addiu(sp, 0x17C);
        a2 = 4;
        jal(ctx, 0x489F88u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
        if (v0 == 0) {
            // 0x0048a10c
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x00489f98
            charge(ctx, 18);
            v0 = 0x960000;
            lw(s0, s1, 20);
            lw(a0, v0, -8664);  // 0x95DE28 RpSkin: skin free list
            lw(s3, sp, 0x17C);
            v0 = 0x30000;
            a1 = v0 | 0x116;
            v0 = 0x960000;
            lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x489FB8u);  // $ra = the return address
            sw(s3, sp, 0x178);
            call_ptr(ctx, jt);
            s4 = v0;
            a1 = 0;
            a0 = s4;
            a2 = 72;
            jal(ctx, 0x489FCCu, gen::fn_memset_00521408);  // [memset]
            lw(v0, sp, 0x178);
            if (v0 == 0) {
                // 0x00489fe0
                charge(ctx, 7);
                a0 = s4;
                a1 = 0;
                a2 = 0;
                a3 = addiu(sp, 0x70);
                t0 = addiu(sp, 0x178);
                t1 = s0;
                jal(ctx, 0x489FF4u, gen::fn_sub_489460_00489460);  // [skinFindUsedBones]
            }
            // 0x00489ffc
            charge(ctx, 11);
            lw(a2, sp, 0x178);
            a1 = s3;
            a0 = s4;
            a3 = s0;
            t0 = addiu(sp, 0x70);
            t1 = 0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x48A018u, gen::fn_sub_489550_00489550);  // [skinCreateData]
            if (v0 == 0) {
                // 0x0048a114
                charge(ctx, 8);
                v0 = 0x960000;
                lw(a0, v0, -8664);  // 0x95DE28 RpSkin: skin free list
                v0 = 0x960000;
                lw(v0, v0, 396);  // 0x96018C RwFreeListFree slot
                a1 = s4;
                jalr(ctx, 0x48A124u, v0.u());
                s4 = 0;
                backedge(ctx);
            }
            // 0x0048a028
            charge(ctx, 5);
            a0 = s2;
            a1 = 4;
            jal(ctx, 0x48A02Cu, gen::fn_sub_4C5620_004c5620);  // [RwStreamSkip]
            if (v0 == 0) {
                // 0x0048a134
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048a03c
                charge(ctx, 6);
                lw(a1, s4, 20);
                a2 = sll(s0, 2);
                a0 = s2;
                jal(ctx, 0x48A044u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                if (v0 == 0) {
                    // 0x0048a13c
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x0048a054
                    charge(ctx, 6);
                    lw(a1, s4, 24);
                    a2 = sll(s0, 4);
                    a0 = s2;
                    jal(ctx, 0x48A05Cu, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
                    if (v0 == 0) {
                        // 0x0048a144
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x0048a06c
                        charge(ctx, 4);
                        lw(v0, s4, 0);
                        at = sltu(0, v0);
                        s5 = 0;
                        if (at != 0) {
                            // 0x0048a07c
                            charge(ctx, 1);
                            s3 = 0;
                            for (;;) {
                                // 0x0048a080
                                charge(ctx, 5);
                                a0 = s2;
                                a1 = 12;
                                jal(ctx, 0x48A084u, gen::fn_sub_4C5620_004c5620);  // [RwStreamSkip]
                                if (v0 == 0) {
                                    // 0x0048a094_14 (its only goto: the block written out here)
                                    charge(ctx, 2);
                                    v0 = 0;
                                    // 0x0048a150 (the shared epilogue, written out on this path)
                                    charge(ctx, 9);
                                    ld(ra, sp, 0x60);
                                    lq(s5, sp, 0x50);
                                    lq(s4, sp, 0x40);
                                    lq(s3, sp, 0x30);
                                    lq(s2, sp, 0x20);
                                    lq(s1, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x180);
                                    return;
                                }
                                // 0x0048a09c
                                charge(ctx, 7);
                                lw(v0, s4, 12);
                                a0 = s2;
                                a2 = 64;
                                a1 = addu(v0, s3);
                                jal(ctx, 0x48A0A8u, gen::fn_sub_4C18B0_004c18b0);  // [RwStreamReadReal]
                                if (v0 == 0) {
                                    goto L_0048a14c;
                                }
                                // 0x0048a0b8
                                charge(ctx, 5);
                                lw(v0, s4, 0);
                                s5 = addiu(s5, 1);
                                v0 = sltu(s5, v0);
                                s3 = addiu(s3, 64);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048a0cc
                            charge(ctx, 1);
                        }
                        // 0x0048a0d0
                        charge(ctx, 15);
                        lw(a1, s4, 24);
                        a0 = s4;
                        a2 = s0;
                        jal(ctx, 0x48A0D8u, gen::fn_sub_4893E0_004893e0);  // [skinFindMaxWeights]
                        lw(a1, s4, 20);
                        t1 = s0;
                        lw(a2, s4, 24);
                        lw(a3, s4, 8);
                        t0 = addiu(s4, 4);
                        jal(ctx, 0x48A0F0u, gen::fn_sub_489460_00489460);  // [skinFindUsedBones]
                        a0 = s1;
                        a1 = s4;
                        jal(ctx, 0x48A0FCu, gen::fn_sub_48A2E0_0048a2e0);  // [skinGeometrySetSkin]
                        backedge(ctx);
                    L_00489f78:
                        charge(ctx, 2);
                        v0 = s2;
                    }
                }
            }
        }
    } else {
        // 0x00489f5c
        charge(ctx, 5);
        a1 = s0;
        a0 = s2;
        jal(ctx, 0x489F60u, gen::fn_sub_4C5620_004c5620);  // [RwStreamSkip]
        if (v0 != 0) {
            goto L_00489f78;
        }
        // 0x00489f70
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0048a150 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
    return;
L_0048a14c:
    charge(ctx, 1);
    v0 = 0;
    // 0x0048a150 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x0048A180 sub_48A180 -- 8 bytes; leaf frame (no stack)
// sub_48A180 [skinAtomicStreamWrite]: Atomic stream-write: nothing (returns the stream).
void sub_48A180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048a180
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0048A190 sub_48A190 -- 8 bytes; leaf frame (no stack)
// sub_48A190 [skinAtomicStreamGetSize]: Atomic stream-size: 0.
void sub_48A190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0048a190
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0048A1A0 sub_48A1A0 -- 244 bytes; frame 0x10: ra sp+0x0
// sub_48A1A0 [RpSkinPluginAttach]: Attaches RpSkin (id 0x116): the engine plugin, the 4-byte atomic extension
// (0x95DE14), its stream / always / rights callbacks, the 4-byte geometry extension (0x95DE18) and its stream
// callbacks. Returns 1.
void sub_48A1A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a1a0
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x490000;
    a3 = 0x490000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 278;
    a2 = addiu(a2, -26832);  // &sub_489730
    a3 = addiu(a3, -26560);  // &sub_489840
    jal(ctx, 0x48A1BCu, gen::fn_sub_4CA520_004ca520);  // [RwEngineRegisterPlugin]
    v1 = 0x960000;
    a2 = 0x490000;
    a3 = 0x490000;
    t0 = 0x490000;
    a0 = 4;
    sw(v0, v1, -8688);  // 0x95DE10 RpSkin: engine offset
    a1 = 278;
    a2 = addiu(a2, -26272);  // &sub_489960
    a3 = addiu(a3, -26208);  // &sub_4899A0
    t0 = addiu(t0, -26160);  // &sub_4899D0
    jal(ctx, 0x48A1E8u, gen::fn_sub_492C30_00492c30);  // [RpAtomicRegisterPlugin]
    v1 = 0x960000;
    a1 = 0x490000;
    a2 = 0x490000;
    a3 = 0x490000;
    a0 = 278;
    sw(v0, v1, -8684);  // 0x95DE14 RpSkin: atomic extension offset (hierarchy)
    a1 = addiu(a1, -24800);  // &sub_489F20
    a2 = addiu(a2, -24192);  // &sub_48A180
    a3 = addiu(a3, -24176);  // &sub_48A190
    jal(ctx, 0x48A210u, gen::fn_sub_492C90_00492c90);  // [RpAtomicRegisterPluginStream]
    a1 = 0x490000;
    a0 = 278;
    a1 = addiu(a1, -26128);  // &sub_4899F0
    jal(ctx, 0x48A220u, gen::fn_sub_492CC0_00492cc0);  // [RpAtomicSetStreamAlwaysCallBack]
    a1 = 0x490000;
    a0 = 278;
    a1 = addiu(a1, -25984);  // &sub_489A80
    jal(ctx, 0x48A230u, gen::fn_sub_492CE0_00492ce0);  // [RpAtomicSetStreamRightsCallBack]
    a2 = 0x490000;
    a3 = 0x490000;
    t0 = 0x490000;
    a0 = 4;
    a1 = 278;
    a2 = addiu(a2, -26432);  // &sub_4898C0
    a3 = addiu(a3, -26400);  // &sub_4898E0
    t0 = addiu(t0, -26288);  // &sub_489950
    jal(ctx, 0x48A254u, gen::fn_sub_493C50_00493c50);  // [RpGeometryRegisterPlugin]
    v1 = 0x960000;
    a1 = 0x490000;
    a2 = 0x490000;
    a3 = 0x490000;
    a0 = 278;
    sw(v0, v1, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    a1 = addiu(a1, -25392);  // &sub_489CD0
    a2 = addiu(a2, -25744);  // &sub_489B70
    a3 = addiu(a3, -25888);  // &sub_489AE0
    jal(ctx, 0x48A27Cu, gen::fn_sub_493C80_00493c80);  // [RpGeometryRegisterPluginStream]
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x0048A2A0 sub_48A2A0 -- 24 bytes; leaf frame (no stack)
// sub_48A2A0 [RpSkinAtomicSetHAnimHierarchy]: Sets atomic $a0's skin hierarchy to $a1. Returns $a0.
void sub_48A2A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0048a2a0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v1, v0, -8684);  // 0x95DE14 RpSkin: atomic extension offset (hierarchy)
    v1 = addu(a0, v1);
    v0 = a0;
    sw(a1, v1, 0);
}

// 0x0048A2C0 sub_48A2C0 -- 20 bytes; leaf frame (no stack)
// sub_48A2C0 [RpSkinGeometryGetSkin]: The skin of geometry $a0 (0 = not skinned).
void sub_48A2C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048a2c0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    v0 = addu(a0, v0);
    lw(v0, v0, 0);
}

// 0x0048A2E0 sub_48A2E0 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_48A2E0 [skinGeometrySetSkin]: RpSkinGeometrySetSkin: replaces the geometry's skin by $a1 and precomputes the
// per-vertex weights (skinPrepareWeights). Returns the geometry, 0 when that failed.
void sub_48A2E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a2e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    s0 = a1;
    v0 = addu(s1, v0);
    lw(v0, v0, 0);
    if (s0 != v0) {
        // 0x0048a310
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x0048a318
            charge(ctx, 2);
            jal(ctx, 0x48A318u, gen::fn_sub_48A790_0048a790);  // [skinDestroyNoop]
        }
        // 0x0048a320
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
        v0 = addu(s1, v0);
        sw(s0, v0, 0);
        if (s0 == 0) {
            goto L_0048a34c;
        }
        // 0x0048a334
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x48A334u, gen::fn_sub_48A4B0_0048a4b0);  // [skinPrepareWeights]
        if (v0 != 0) {
            goto L_0048a34c;
        }
        // 0x0048a344
        charge(ctx, 2);
        v0 = 0;
        // 0x0048a350 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0048a34c:
    charge(ctx, 1);
    v0 = s1;
    // 0x0048a350 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0048A370 sub_48A370 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_48A370 [skinDestroy]: RpSkinDestroy: frees the data block and the split data and returns the skin to the free
// list. Returns 0.
void sub_48A370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a370
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, anim::kSkinDataBlock);
    if (a0 != 0) {
        // 0x0048a38c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C RwFree slot
        jalr(ctx, 0x48A394u, v0.u());
    }
    // 0x0048a39c
    charge(ctx, 13);
    a0 = s0;
    jal(ctx, 0x48A39Cu, gen::fn_sub_489020_00489020);  // [skinSplitDataDestroy]
    v0 = 0x960000;
    lw(a0, v0, -8664);  // 0x95DE28 RpSkin: skin free list
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C RwFreeListFree slot
    a1 = s0;
    jalr(ctx, 0x48A3B4u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 0;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0048A3D0 name__C9type_info -- 8 bytes; leaf frame (no stack)
// name__C9type_info [RpSkinGetNumBones]: The bone count of skin $a0 (+0). (functions.json's name is a FLIRT
// mismatch.)
void name__C9type_info(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048a3d0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, anim::kSkinNumBones);
}

// 0x0048A3F0 sub_48A3F0 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_48A3F0 [RpSkinAtomicSetType]: Public RpSkinAtomicSetType: the same body as skinAtomicSetType (type 2 needs
// MatFX, type 3 plugin 0x12E; else 1), then skinAtomicSetPipeline.
void sub_48A3F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a3f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 288;
    jal(ctx, 0x48A408u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
    v1 = si(-1);
    if (v0 == v1) {
        // 0x0048a41c
        charge(ctx, 3);
        v0 = 2;
        if (s0 != v0) {
            goto L_0048a440;
        }
        // 0x0048a428
        charge(ctx, 1);
        s0 = 1;
        goto L_0048a42c;
    }
L_0048a440:
    charge(ctx, 5);
    a0 = 302;
    jal(ctx, 0x48A440u, gen::fn_sub_4CA550_004ca550);  // [RwEngineGetPluginOffset]
    v1 = si(-1);
    if (v0 != v1) {
        backedge(ctx);
    } else {
        // 0x0048a454
        charge(ctx, 3);
        v0 = 3;
        if (s0 != v0) {
            backedge(ctx);
        } else {
            // 0x0048a460
            charge(ctx, 2);
            s0 = 1;
            backedge(ctx);
        }
    }
L_0048a42c:
    charge(ctx, 5);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x48A430u, gen::fn_sub_48AC10_0048ac10);  // [skinAtomicSetPipeline]
    ld(ra, sp, 0x20);
    // 0x0048a468
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0048A480 sub_48A480 -- 40 bytes; leaf frame (no stack)
// sub_48A480 [RpSkinAtomicGetType]: The skin type of atomic $a0: its pipeline's plugin data when the pipeline belongs
// to the skin plugin (0x116), else 0.
void sub_48A480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0048a480
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, anim::kAtmPipeline);
    v0 = 278;
    lw(v1, a0, 44);
    if (v1 != v0) {
        // 0x0048a49c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0048a494
        charge(ctx, 2);
        lw(v0, a0, 48);
    }
    // 0x0048a4a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0048A4B0 sub_48A4B0 -- 728 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_48A4B0 [skinPrepareWeights]: Packs each vertex's bone indices into the low bits of its weights for the VU1 skin
// programs: weight slot k gets (bone + 1) x 4 (through the split remap table for partitioned skins), a zero weight
// becomes 0; counts the vertices per number of weights (+28..+40).
void sub_48A4B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0048a4b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x1000000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, anim::kGeoFlags);
    v0 = v1 & v0;
    s0 = a0;
    if (v0 == 0) {
        // 0x0048a4d8
        charge(ctx, 12);
        jal(ctx, 0x48A4D8u, gen::fn_sub_48A2C0_0048a2c0);  // [RpSkinGeometryGetSkin]
        lw(a3, v0, 24);
        lw(a2, v0, 20);
        lw(a0, s0, anim::kGeoNumVertices);
        sw(zero, v0, 28);
        sw(zero, v0, 32);
        sw(zero, v0, 36);
        sw(zero, v0, 40);
        lw(v1, v0, 48);
        if (v1 != 0) {
            // 0x0048a614
            charge(ctx, 3);
            at = sltu(0, a0);
            a1 = 0;
            if (at == 0) {
                backedge(ctx);
            } else {
                // 0x0048a620
                charge(ctx, 2);
                mtc1(zero, f1);
                v1 = si(-1024);
                for (;;) {
                    // 0x0048a628
                    charge(ctx, 19);
                    lbu(t2, a2, 0);
                    t0 = 0;
                    lw(t1, v0, 56);
                    lw(t3, a3, 0);
                    t1 = addu(t1, t2);
                    lbu(t1, t1, 0);
                    t3 = t3 & v1;
                    t1 = addiu(t1, 1);
                    t1 = sll(t1, 2);
                    t1 = t3 | t1;
                    sw(t1, a3, 0);
                    lwc1(f0, a3, 4);
                    lw(t2, a3, 4);
                    lw(t1, a2, 0);
                    c_eq_s(f1, f0);
                    t3 = t2 & v1;
                    t1 = srl(t1, 8);
                    t2 = t1 & 0xFF;
                    if (cond(ctx)) {
                        // 0x0048a760
                        charge(ctx, 2);
                        t1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048a674
                        charge(ctx, 7);
                        lw(t1, v0, 56);
                        t0 = addiu(t0, 1);
                        t1 = addu(t1, t2);
                        lbu(t1, t1, 0);
                        t1 = addiu(t1, 1);
                        t1 = sll(t1, 2);
                        t1 = t3 | t1;
                    }
                    // 0x0048a690
                    charge(ctx, 9);
                    sw(t1, a3, 4);
                    lwc1(f0, a3, 8);
                    lw(t2, a3, 8);
                    lw(t1, a2, 0);
                    c_eq_s(f1, f0);
                    t3 = t2 & v1;
                    t1 = srl(t1, 16);
                    t2 = t1 & 0xFF;
                    if (cond(ctx)) {
                        // 0x0048a768
                        charge(ctx, 2);
                        t1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048a6b4
                        charge(ctx, 7);
                        lw(t1, v0, 56);
                        t0 = addiu(t0, 1);
                        t1 = addu(t1, t2);
                        lbu(t1, t1, 0);
                        t1 = addiu(t1, 1);
                        t1 = sll(t1, 2);
                        t1 = t3 | t1;
                    }
                    // 0x0048a6d0
                    charge(ctx, 9);
                    sw(t1, a3, 8);
                    lwc1(f0, a3, 12);
                    lw(t2, a3, 12);
                    lw(t1, a2, 0);
                    c_eq_s(f1, f0);
                    t3 = t2 & v1;
                    t1 = srl(t1, 24);
                    t2 = t1 & 0xFF;
                    if (cond(ctx)) {
                        // 0x0048a770
                        charge(ctx, 2);
                        t1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048a6f4
                        charge(ctx, 7);
                        lw(t1, v0, 56);
                        t0 = addiu(t0, 1);
                        t1 = addu(t1, t2);
                        lbu(t1, t1, 0);
                        t1 = addiu(t1, 1);
                        t1 = sll(t1, 2);
                        t1 = t3 | t1;
                    }
                    // 0x0048a710
                    charge(ctx, 11);
                    t0 = sll(t0, 2);
                    sw(t1, a3, 12);
                    t2 = addu(v0, t0);
                    lw(t1, t2, 28);
                    a1 = addiu(a1, 1);
                    t0 = sltu(a1, a0);
                    a3 = addiu(a3, 16);
                    a2 = addiu(a2, 4);
                    t1 = addiu(t1, 1);
                    sw(t1, t2, 28);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048a73c
                charge(ctx, 2);
                backedge(ctx);
            }
        } else {
            // 0x0048a508
            charge(ctx, 3);
            at = sltu(0, a0);
            t0 = 0;
            if (at == 0) {
                backedge(ctx);
            } else {
                // 0x0048a514
                charge(ctx, 2);
                mtc1(zero, f1);
                v1 = si(-1024);
                for (;;) {
                    // 0x0048a51c
                    charge(ctx, 16);
                    lbu(t1, a2, 0);
                    a1 = 0;
                    lw(t2, a3, 0);
                    t1 = addiu(t1, 1);
                    t2 = t2 & v1;
                    t1 = sll(t1, 2);
                    t1 = t2 | t1;
                    sw(t1, a3, 0);
                    lwc1(f0, a3, 4);
                    lw(t1, a2, 0);
                    lw(t2, a3, 4);
                    c_eq_s(f1, f0);
                    t1 = srl(t1, 8);
                    t2 = t2 & v1;
                    t1 = t1 & 0xFF;
                    if (cond(ctx)) {
                        // 0x0048a744
                        charge(ctx, 2);
                        t1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048a55c
                        charge(ctx, 5);
                        t1 = addiu(t1, 1);
                        a1 = addiu(a1, 1);
                        t1 = sll(t1, 2);
                        t1 = t2 | t1;
                    }
                    // 0x0048a570
                    charge(ctx, 9);
                    sw(t1, a3, 4);
                    lwc1(f0, a3, 8);
                    lw(t1, a2, 0);
                    lw(t2, a3, 8);
                    c_eq_s(f1, f0);
                    t1 = srl(t1, 16);
                    t2 = t2 & v1;
                    t1 = t1 & 0xFF;
                    if (cond(ctx)) {
                        // 0x0048a750
                        charge(ctx, 2);
                        t1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048a594
                        charge(ctx, 5);
                        t1 = addiu(t1, 1);
                        a1 = addiu(a1, 1);
                        t1 = sll(t1, 2);
                        t1 = t2 | t1;
                    }
                    // 0x0048a5a8
                    charge(ctx, 9);
                    sw(t1, a3, 8);
                    lwc1(f0, a3, 12);
                    lw(t1, a2, 0);
                    lw(t2, a3, 12);
                    c_eq_s(f1, f0);
                    t1 = srl(t1, 24);
                    t2 = t2 & v1;
                    t1 = t1 & 0xFF;
                    if (cond(ctx)) {
                        // 0x0048a758
                        charge(ctx, 2);
                        t1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x0048a5cc
                        charge(ctx, 5);
                        t1 = addiu(t1, 1);
                        a1 = addiu(a1, 1);
                        t1 = sll(t1, 2);
                        t1 = t2 | t1;
                    }
                    // 0x0048a5e0
                    charge(ctx, 11);
                    a1 = sll(a1, 2);
                    sw(t1, a3, 12);
                    t2 = addu(v0, a1);
                    lw(t1, t2, 28);
                    t0 = addiu(t0, 1);
                    a1 = sltu(t0, a0);
                    a3 = addiu(a3, 16);
                    a2 = addiu(a2, 4);
                    t1 = addiu(t1, 1);
                    sw(t1, t2, 28);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048a60c
                charge(ctx, 2);
                backedge(ctx);
            }
        }
    }
    // 0x0048a4d0
    charge(ctx, 2);
    v0 = s0;
    // 0x0048a778
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0048A790 sub_48A790 -- 8 bytes; leaf frame (no stack)
// sub_48A790 [skinDestroyNoop]: Returns $a0 (an empty skin release hook).
void sub_48A790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048a790
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0048A7A0 sub_48A7A0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_48A7A0 [skinNativeStreamGetSize]: Native-geometry stream size: 64 per bone + 36 + used bones + split data.
void sub_48A7A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a7a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 16;
    sd(ra, sp, 0x10);
    a1 = addiu(v0, 4);
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    lw(v1, a0, 0);
    lw(v0, a0, 4);
    v1 = sll(v1, 6);
    v1 = addu(a1, v1);
    v0 = addu(v1, v0);
    s0 = addiu(v0, 16);
    jal(ctx, 0x48A7D8u, gen::fn_sub_489320_00489320);  // [skinSplitDataStreamGetSize]
    v0 = addu(s0, v0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0048A800 sub_48A800 -- 404 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_48A800 [skinNativeStreamWrite]: Native-geometry stream-write: a chunk with version 4, the packed counts, the
// used-bone list, the bone matrices, the 16 bytes at +28 and the split data.
void sub_48A800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a800
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 4;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sw(v0, sp, 0x4C);
    s0 = a1;
    v0 = 16;
    a1 = addiu(v0, 4);
    v0 = 0x960000;
    lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
    v0 = addu(s0, v0);
    lw(a0, v0, 0);
    lw(v1, a0, 0);
    lw(v0, a0, 4);
    v1 = sll(v1, 6);
    v1 = addu(a1, v1);
    v0 = addu(v1, v0);
    s2 = addiu(v0, 16);
    jal(ctx, 0x48A850u, gen::fn_sub_489320_00489320);  // [skinSplitDataStreamGetSize]
    v0 = addu(s2, v0);
    a0 = s1;
    a2 = addiu(v0, -12);
    a1 = 1;
    v0 = 0x30000;
    t0 = 55;
    a3 = v0 | 0x7002;
    jal(ctx, 0x48A870u, gen::fn_sub_4C15A0_004c15a0);  // [RwStreamWriteVersionedChunkHeader]
    if (v0 != 0) {
        // 0x0048a888
        charge(ctx, 6);
        a0 = s1;
        a1 = addiu(sp, 0x4C);
        a2 = 4;
        jal(ctx, 0x48A890u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
        if (v0 != 0) {
            // 0x0048a8a8
            charge(ctx, 21);
            v0 = 0x960000;
            a3 = 0xFF0000;
            lw(v0, v0, -8680);  // 0x95DE18 RpSkin: geometry extension offset (RpSkin*)
            a0 = s1;
            a1 = addiu(sp, 0x48);
            a2 = 4;
            v0 = addu(s0, v0);
            lw(s0, v0, 0);
            lw(t0, s0, 16);
            lw(v1, s0, 4);
            lbu(v0, s0, 0);
            t0 = sll(t0, 16);
            v1 = sll(v1, 8);
            a3 = t0 & a3;
            v1 = v1 & 0xFF00;
            v1 = a3 | v1;
            v0 = v0 | v1;
            link(ctx, 0x48A8ECu);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x48);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
            if (v0 != 0) {
                // 0x0048a904
                charge(ctx, 6);
                lw(a1, s0, 8);
                lw(a2, s0, 4);
                a0 = s1;
                jal(ctx, 0x48A90Cu, gen::fn_sub_4C53F0_004c53f0);  // [RwStreamWrite]
                if (v0 != 0) {
                    // 0x0048a924
                    charge(ctx, 7);
                    lw(v0, s0, 0);
                    a0 = s1;
                    lw(a1, s0, 12);
                    a2 = sll(v0, 6);
                    jal(ctx, 0x48A930u, gen::fn_sub_4C53F0_004c53f0);  // [RwStreamWrite]
                    if (v0 != 0) {
                        // 0x0048a948
                        charge(ctx, 6);
                        a0 = s1;
                        a1 = addiu(s0, 28);
                        a2 = 16;
                        jal(ctx, 0x48A950u, gen::fn_sub_4C17F0_004c17f0);  // [RwStreamWriteInt32]
                        if (v0 != 0) {
                            // 0x0048a968
                            charge(ctx, 5);
                            a1 = s0;
                            a0 = s1;
                            jal(ctx, 0x48A96Cu, gen::fn_sub_489080_00489080);  // [skinSplitDataStreamWrite]
                            if (v0 == 0) s1 = 0;
                            v0 = s1;
                        } else {
                            // 0x0048a960
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x0048a940
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x0048a91c
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x0048a8fc
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0048a8a0
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0048a880
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0048a97c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0048A9A0 sub_48A9A0 -- 588 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_48A9A0 [skinNativeStreamRead]: Native-geometry stream-read: a chunk of version 0x35000..0x37002 (else RpSkin
// error), platform 4, the packed counts, one block for the bone matrices and the used-bone list, +28..+40 and the
// split data; sets the skin on the geometry.
void sub_48A9A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048a9a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    a2 = addiu(sp, 0x78);
    sq(s4, sp, 0x40);
    a3 = addiu(sp, 0x7C);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a1 = 1;
    link(ctx, 0x48A9CCu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);  // [RwStreamFindChunk]
    if (v0 == 0) {
        // 0x0048aa30
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0048a9dc
        charge(ctx, 6);
        lw(v1, sp, 0x7C);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x0048a9f4
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_0048aa08;
            }
            // 0x0048aa38
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(sp, 0x70);
            a2 = 4;
            jal(ctx, 0x48AA40u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
            if (v0 == 0) {
                // 0x0048aa68
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048aa50
                charge(ctx, 4);
                lw(v1, sp, 0x70);
                v0 = 4;
                if (v1 == v0) {
                    // 0x0048aa70
                    charge(ctx, 18);
                    v0 = 0x960000;
                    v1 = 0x30000;
                    lw(a0, v0, -8664);  // 0x95DE28 RpSkin: skin free list
                    v0 = 0x960000;
                    lw(v0, v0, 392);  // 0x960188 RwFreeListAlloc slot
                    a1 = v1 | 0x116;
                    jalr(ctx, 0x48AA84u, v0.u());
                    s1 = v0;
                    a1 = 0;
                    a0 = s1;
                    a2 = 72;
                    jal(ctx, 0x48AA98u, gen::fn_memset_00521408);  // [memset]
                    a0 = s4;
                    a1 = addiu(sp, 0x74);
                    a2 = 4;
                    jal(ctx, 0x48AAA8u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                    if (v0 != 0) {
                        // 0x0048aac0
                        charge(ctx, 38);
                        lbu(v1, sp, 0x74);
                        v0 = 0x30000;
                        a1 = v0 | 0x116;
                        v0 = 0x960000;
                        sw(v1, s1, 0);
                        lw(v1, sp, 0x74);
                        v1 = srl(v1, 8);
                        v1 = v1 & 0xFF;
                        sw(v1, s1, 4);
                        lw(v1, sp, 0x74);
                        v1 = srl(v1, 16);
                        v1 = v1 & 0xFF;
                        sw(v1, s1, 16);
                        lw(v1, s1, 0);
                        lw(s0, s1, 4);
                        lw(v0, v0, 376);  // 0x960178 RwMalloc slot
                        s2 = sll(v1, 6);
                        v1 = addu(s2, s0);
                        sw(v1, sp, 0x78);
                        a0 = addiu(v1, 15);
                        jalr(ctx, 0x48AB0Cu, v0.u());
                        sw(v0, s1, 68);
                        a0 = s4;
                        lw(v1, s1, 68);
                        v0 = si(-16);
                        v1 = addiu(v1, 15);
                        v0 = v1 & v0;
                        sw(v0, s1, 12);
                        lw(v1, s1, 0);
                        lw(v0, s1, 12);
                        v1 = sll(v1, 6);
                        v0 = addu(v0, v1);
                        sw(v0, s1, 8);
                        lw(a1, s1, 8);
                        a2 = s0;
                        jal(ctx, 0x48AB48u, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
                        if (s0 == v0) {
                            // 0x0048ab60
                            charge(ctx, 6);
                            lw(a1, s1, 12);
                            a0 = s4;
                            a2 = s2;
                            jal(ctx, 0x48AB68u, gen::fn_sub_4C5250_004c5250);  // [RwStreamRead]
                            if (s2 == v0) {
                                // 0x0048ab80
                                charge(ctx, 6);
                                a0 = s4;
                                a1 = addiu(s1, 28);
                                a2 = 16;
                                jal(ctx, 0x48AB88u, gen::fn_sub_4C1910_004c1910);  // [RwStreamReadInt32]
                                if (v0 == s4) {
                                    // 0x0048aba0
                                    charge(ctx, 5);
                                    a0 = s4;
                                    a1 = s1;
                                    jal(ctx, 0x48ABA4u, gen::fn_sub_489160_00489160);  // [skinSplitDataStreamRead]
                                    if (v0 != 0) {
                                        // 0x0048abbc
                                        charge(ctx, 4);
                                        a0 = s3;
                                        a1 = s1;
                                        jal(ctx, 0x48ABC0u, gen::fn_sub_48A2E0_0048a2e0);  // [skinGeometrySetSkin]
                                        v0 = s4;
                                    } else {
                                        // 0x0048abb4
                                        charge(ctx, 2);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x0048ab98
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                            } else {
                                // 0x0048ab78
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        } else {
                            // 0x0048ab58
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x0048aab8
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x0048aa60
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
            // 0x0048abcc (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x80);
            return;
        }
    L_0048aa08:
        charge(ctx, 10);
        v1 = 278;
        v0 = lui(0x8000);
        sw(v1, sp, 0x68);
        a0 = v0 | 0x4;
        jal(ctx, 0x48AA14u, gen::fn_sub_4C1D10_004c1d10);  // [_rwerror]
        sw(v0, sp, 0x6C);
        a0 = addiu(sp, 0x68);
        jal(ctx, 0x48AA20u, gen::fn_sub_4C1C50_004c1c50);  // [RwErrorSet]
        v0 = 0;
    }
    // 0x0048abcc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0048ABF0 sub_48ABF0 -- 8 bytes; leaf frame (no stack)
// sub_48ABF0 [skinPlatformOpen]: Returns 1 (no platform set-up).
void sub_48ABF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0048abf0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0048AC00 sub_48AC00 -- 8 bytes; leaf frame (no stack)
// sub_48AC00 [skinPlatformClose]: Returns 1.
void sub_48AC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0048ac00
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0048AC10 sub_48AC10 -- 264 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_48AC10 [skinAtomicSetPipeline]: Gives atomic $a0 the PDS skin pipeline: 0x11002 (plain skin), or the MatFX skin
// pipelines 0x11013 / 0x11014 (geometry flag 0x80 picks the second) for type 2, or type 0 with MatFX enabled on the
// atomic. Returns $a0.
void sub_48AC10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048ac10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, a0, anim::kAtmGeometry);
    lw(v0, v0, anim::kGeoFlags);
    a0 = 288;
    v0 = v0 & 0x80;
    s0 = sltu(0, v0);
    jal(ctx, 0x48AC3Cu, gen::fn_sub_492D00_00492d00);  // [RpAtomicGetPluginOffset]
    v0 = addu(s2, v0);
    lbu(v0, v0, 0);
    if (s1 == 0) {
        // 0x0048acd4
        charge(ctx, 3);
        v1 = 0x10000;
        a0 = v1 | 0x1002;
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x0048ace0
            charge(ctx, 3);
            v0 = 1;
            if (s0 != v0) {
                // 0x0048acf4
                charge(ctx, 1);
                a0 = v1 | 0x1013;
            } else {
                // 0x0048acec
                charge(ctx, 2);
                a0 = v1 | 0x1014;
            }
            // 0x0048acf8
            charge(ctx, 2);
            backedge(ctx);
        }
    } else {
        // 0x0048ac50
        charge(ctx, 3);
        v0 = 3;
        if (s1 == v0) {
            // 0x0048acb0
            charge(ctx, 3);
            v0 = 0x10000;
            a0 = v0 | 0x1002;
        } else {
            // 0x0048ac5c
            charge(ctx, 3);
            v0 = 2;
            if (s1 == v0) {
                // 0x0048ac88
                charge(ctx, 3);
                v0 = 1;
                if (s0 != v0) {
                    // 0x0048aca0
                    charge(ctx, 2);
                    v0 = 0x10000;
                    a0 = v0 | 0x1013;
                } else {
                    // 0x0048ac94
                    charge(ctx, 3);
                    v0 = 0x10000;
                    a0 = v0 | 0x1014;
                }
                // 0x0048aca8
                charge(ctx, 2);
            } else {
                // 0x0048ac68
                charge(ctx, 3);
                v0 = 1;
                if (s1 == v0) {
                    // 0x0048ac7c
                    charge(ctx, 3);
                    v0 = 0x10000;
                    a0 = v0 | 0x1002;
                } else {
                    // 0x0048ac74
                    charge(ctx, 2);
                    v0 = 0x10000;
                    // 0x0048acbc
                    charge(ctx, 1);
                    a0 = v0 | 0x1002;
                }
            }
        }
    }
    // 0x0048acc0
    charge(ctx, 5);
    jal(ctx, 0x48ACC0u, gen::fn_RpPDSGetPipe_0046a890);  // [RpPDSGetPipe]
    sw(v0, s2, anim::kAtmPipeline);
    v0 = s2;
    // 0x0048ad00
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00311730 sub_311730 -- 5432 bytes; frame 0x4A0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_311730 [mdlSlotUpdateHierarchyLookAt]: The hierarchy matrix update of a slot with a look-at ($a0 hierarchy, $a1
// slot, $a2 the slot's look-at record +76, $a3 0): RpHAnimHierarchyUpdateMatrices' walk with, on the look bone(s), a
// rotation towards the target (point or angle mode, limited by the slot's yaw / pitch limits, eased by its speed into
// the slot's look quaternion) and the bone scale of 0x9571C0 / 0x9571C4.
void sub_311730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00311730
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4A0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    sw(a1, sp, 0x11C);
    s3 = a2;
    sw(a3, sp, 0x110);
    a2 = 0;
    a1 = 0;
    lw(s5, a0, anim::kHierFlags);
    v0 = s5 & 0x1;
    if (v0 != 0) {
        // 0x00311794
        charge(ctx, 4);
        lw(v1, s4, anim::kHierRootParentOffset);
        v0 = si(-1);
        if (v1 == v0) {
            goto L_003117dc;
        }
        // 0x003117a4
        charge(ctx, 7);
        lw(a0, s4, anim::kHierParentHier);
        v1 = sll(v1, 6);
        lw(v0, a0, anim::kHierMatrices);
        s2 = addu(v0, v1);
        v0 = s5 & 0x2000;
        if (v0 != 0) {
            // 0x003117c0
            charge(ctx, 3);
            v0 = s5 & 0x4000;
            if (v0 != 0) {
                // 0x003117cc
                charge(ctx, 4);
                a2 = 1;
                lw(a1, a0, 20);
            }
        }
        goto L_0031185c;
    }
L_003117dc:
    charge(ctx, 3);
    v0 = s5 & 0x4000;
    if (v0 == 0) {
        // 0x00311850
        charge(ctx, 3);
        a2 = 1;
        lw(a1, s4, anim::kHierParentFrame);
        s2 = addiu(sp, 0x410);
    } else {
        // 0x003117e8
        charge(ctx, 22);
        v0 = 0x3F800000;
        sw(v0, sp, 0x3F8);
        sw(v0, sp, 0x3E4);
        sw(v0, sp, 0x3D0);
        sw(zero, sp, 0x3E0);
        sw(zero, sp, 0x3D8);
        sw(zero, sp, 0x3D4);
        sw(zero, sp, 0x3F4);
        sw(zero, sp, 0x3F0);
        sw(zero, sp, 0x3E8);
        sw(zero, sp, 0x408);
        sw(zero, sp, 0x404);
        sw(zero, sp, 0x400);
        lw(v1, sp, 0x3DC);
        v0 = 0x20000;
        v0 = v0 | 0x3;
        v0 = v1 | v0;
        sw(v0, sp, 0x3DC);
        s2 = addiu(sp, 0x3D0);
        v0 = s5 & 0x2000;
        if (v0 != 0) {
            // 0x00311840
            charge(ctx, 4);
            a2 = 1;
            lw(a1, s4, anim::kHierParentFrame);
        }
    }
L_0031185c:
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00311864
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x0031186c
            charge(ctx, 3);
            lw(s0, a1, 4);
            if (s0 == 0) {
                goto L_00311958;
            }
            // 0x00311878
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x31187Cu, gen::fn_sub_4CAE30_004cae30);  // [rwFrameIsDirty]
            if (v0 != 0) {
                // 0x003118cc
                charge(ctx, 3);
                a2 = addiu(s0, 16);
                a1 = addiu(sp, 0x410);
                a0 = 8;
                for (;;) {
                    // 0x003118d8
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
                // 0x003118fc
                charge(ctx, 3);
                lw(s0, s0, 4);
                for (;;) {
                    // 0x00311948
                    charge(ctx, 2);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00311908
                    charge(ctx, 3);
                    a1 = addiu(sp, 0x410);
                    a0 = addiu(sp, 0x2D0);
                    v1 = 4;
                    for (;;) {
                        // 0x00311914
                        charge(ctx, 7);
                        lq(v0, a1, 0);
                        a1 = addiu(a1, 16);
                        v1 = addiu(v1, -1);
                        sq(v0, a0, 0);
                        a0 = addiu(a0, 16);
                        if (i64(v1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00311930
                    charge(ctx, 6);
                    a0 = addiu(sp, 0x410);
                    a1 = addiu(sp, 0x2D0);
                    a2 = addiu(s0, 16);
                    jal(ctx, 0x31193Cu, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                    lw(s0, s0, 4);
                }
                // 0x00311950
                charge(ctx, 2);
            } else {
                // 0x0031188c
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x311890u, gen::fn_sub_4CB2F0_004cb2f0);  // [RwFrameGetLTM]
                a2 = addiu(sp, 0x410);
                a1 = 8;
                for (;;) {
                    // 0x003118a0
                    charge(ctx, 9);
                    lw(a0, v0, 0);
                    lw(v1, v0, 4);
                    v0 = addiu(v0, 8);
                    a1 = addiu(a1, -1);
                    sw(a0, a2, 0);
                    sw(v1, a2, 4);
                    a2 = addiu(a2, 8);
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x003118c4
                charge(ctx, 2);
            }
            goto L_003119a0;
        }
    L_00311958:
        charge(ctx, 18);
        v0 = 0x3F800000;
        sw(v0, sp, 0x438);
        sw(v0, sp, 0x424);
        sw(v0, sp, 0x410);
        sw(zero, sp, 0x420);
        sw(zero, sp, 0x418);
        sw(zero, sp, 0x414);
        sw(zero, sp, 0x434);
        sw(zero, sp, 0x430);
        sw(zero, sp, 0x428);
        sw(zero, sp, 0x448);
        sw(zero, sp, 0x444);
        sw(zero, sp, 0x440);
        lw(v1, sp, 0x41C);
        v0 = 0x20000;
        v0 = v0 | 0x3;
        v0 = v1 | v0;
        sw(v0, sp, 0x41C);
    }
L_003119a0:
    charge(ctx, 4);
    v0 = s5 & 0x2000;
    sw(v0, sp, 0xF0);
    if (v0 != 0) {
        // 0x003119b0
        charge(ctx, 6);
        lw(v0, s4, anim::kHierParentFrame);
        lw(v1, v0, 160);
        lbu(v0, v1, 3);
        v0 = v0 & 0x3;
        if (v0 == 0) {
            // 0x003119c8
            charge(ctx, 19);
            a0 = 0x960000;
            a0 = addiu(a0, 300);  // &0x96012C
            lw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
            sw(v0, v1, 8);
            lw(v0, s4, anim::kHierParentFrame);
            lw(v0, v0, 160);
            sw(a0, v0, 12);
            lw(v0, s4, anim::kHierParentFrame);
            lw(v0, v0, 160);
            v1 = addiu(v0, 8);
            lw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
            sw(v1, v0, 4);
            lw(v0, s4, anim::kHierParentFrame);
            lw(v1, v0, 160);
            v0 = addiu(v1, 8);
            sw(v0, a0, 0);  // 0x96012C RW engine: the dirty-frame list head (RwLinkList)
            lbu(v0, v1, 3);
            v0 = v0 | 0x2;
            sb(v0, v1, 3);
        }
    }
    // 0x00311a14
    charge(ctx, 16);
    lw(v1, s4, anim::kHierInterp);
    lw(v0, v1, anim::kItpApplyCB);
    sq(v0, sp, 0xE0);
    lw(v0, v1, anim::kItpFrameSize);
    sq(v0, sp, 0xD0);
    s6 = addiu(sp, 0x354);
    lw(s7, s4, anim::kHierNodeInfo);
    lw(s1, s4, anim::kHierMatrices);
    s0 = addiu(v1, 76);
    fp = 0;
    v0 = s5 & 0x1000;
    sq(v0, sp, 0xC0);
    v0 = s5 & 0x4000;
    sq(v0, sp, 0xB0);
    for (;;) {
        // 0x00312c10
        charge(ctx, 4);
        lw(v0, s4, anim::kHierNumNodes);
        v0 = slt(fp, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00311a54
        charge(ctx, 5);
        v1 = 0x460000;
        v1 = addiu(v1, 18272);  // &sub_464760
        lq(v0, sp, 0xE0);
        if (v1 != v0) {
            // 0x00311b60
            charge(ctx, 4);
            a0 = addiu(sp, 0x290);
            a1 = s0;
            jalr(ctx, 0x311B68u, v0.u());
        } else {
            // 0x00311a68
            charge(ctx, 62);
            lwc1(f3, s0, 8);
            lwc1(f2, s0, 12);
            lwc1(f1, s0, 16);
            lwc1(f0, s0, 20);
            mul_s(f12, f3, f3);
            mul_s(f11, f2, f2);
            mul_s(f10, f1, f1);
            mul_s(f9, f2, f1);
            mul_s(f8, f1, f3);
            mul_s(f7, f3, f2);
            mul_s(f6, f0, f3);
            mul_s(f5, f0, f2);
            mul_s(f4, f0, f1);
            add_s(f0, f11, f10);
            v0 = 0x40000000;
            mtc1(v0, f3);
            v0 = 0x3F800000;
            mtc1(v0, f2);
            mtc1(zero, f1);
            adda_s(f1, f2);
            msub_s(f0, f3, f0);
            swc1(f0, sp, 0x290);
            add_s(f0, f7, f4);
            mul_s(f0, f3, f0);
            swc1(f0, sp, 0x294);
            sub_s(f0, f8, f5);
            mul_s(f0, f3, f0);
            swc1(f0, sp, 0x298);
            sub_s(f0, f7, f4);
            mul_s(f0, f3, f0);
            swc1(f0, sp, 0x2A0);
            add_s(f0, f12, f10);
            adda_s(f1, f2);
            msub_s(f0, f3, f0);
            swc1(f0, sp, 0x2A4);
            add_s(f0, f9, f6);
            mul_s(f0, f3, f0);
            swc1(f0, sp, 0x2A8);
            add_s(f0, f8, f5);
            mul_s(f0, f3, f0);
            swc1(f0, sp, 0x2B0);
            sub_s(f0, f9, f6);
            mul_s(f0, f3, f0);
            swc1(f0, sp, 0x2B4);
            add_s(f0, f12, f11);
            adda_s(f1, f2);
            msub_s(f0, f3, f0);
            swc1(f0, sp, 0x2B8);
            sw(zero, sp, 0x2C0);
            sw(zero, sp, 0x2C4);
            sw(zero, sp, 0x2C8);
            v0 = 3;
            sw(v0, sp, 0x29C);
            lwc1(f0, s0, 24);
            swc1(f0, sp, 0x2C0);
            lwc1(f0, s0, 28);
            swc1(f0, sp, 0x2C4);
            lwc1(f0, s0, 32);
            swc1(f0, sp, 0x2C8);
        }
        // 0x00311b70
        charge(ctx, 7);
        v1 = sll(fp, 4);
        lw(v0, s4, anim::kHierNodeInfo);
        v0 = addu(v0, v1);
        lw(v1, v0, 0);
        v0 = 5001;
        if (v1 == v0) {
            // 0x00311b94
            charge(ctx, 3);
            lw(v0, sp, 0x110);
            if (v0 == 0) {
                // 0x00311ba0
                charge(ctx, 4);
                lhu(v1, s3, 0);
                v0 = v1 & 0x400;
                if (v0 == 0) {
                    // 0x00311bb0
                    charge(ctx, 2);
                    v0 = v1 | 0x600;
                    sh(v0, s3, 0);
                }
            }
            // 0x00311bb8
            charge(ctx, 17);
            s5 = 0;
            v0 = 0x3F800000;
            mtc1(v0, f1);
            lwc1(f0, s3, 48);
            div_s(f4, f1, f0);
            swc1(f4, sp, 0x470);
            lwc1(f0, s3, 52);
            div_s(f3, f1, f0);
            swc1(f3, sp, 0x474);
            lwc1(f0, s3, 56);
            div_s(f2, f1, f0);
            swc1(f2, sp, 0x478);
            lw(v0, sp, 0x11C);
            lhu(v0, v0, 0);
            v0 = v0 & 0x10;
            if (v0 != 0) {
                // 0x00311bfc
                charge(ctx, 12);
                v0 = 0x950000;
                lwc1(f0, v0, 29120);  // 0x9571C0 bone parameter 0 (slot +68 copy)
                div_s(f1, f1, f0);
                mul_s(f0, f4, f1);
                swc1(f0, sp, 0x470);
                v0 = 0x950000;
                lwc1(f0, v0, 29124);  // 0x9571C4 bone parameter 1 (slot +72 copy)
                mul_s(f1, f1, f0);
                mul_s(f0, f3, f1);
                swc1(f0, sp, 0x474);
                mul_s(f0, f2, f1);
                swc1(f0, sp, 0x478);
            }
            // 0x00311c2c
            charge(ctx, 3);
            a1 = addiu(sp, 0x310);
            a0 = 8;
            a2 = s2;
            for (;;) {
                // 0x00311c38
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
            // 0x00311c5c
            charge(ctx, 19);
            a0 = addiu(sp, 0x310);
            a1 = addiu(sp, 0x470);
            a2 = 1;
            jal(ctx, 0x311C68u, gen::fn_sub_4C33D0_004c33d0);  // [RwMatrixScale]
            a0 = addiu(sp, 0x190);
            a1 = addiu(sp, 0x290);
            a2 = addiu(sp, 0x310);
            jal(ctx, 0x311C7Cu, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
            lwc1(f2, sp, 0x1C0);
            lwc1(f1, sp, 0x1C4);
            lwc1(f0, sp, 0x1C8);
            swc1(f2, sp, 0x480);
            swc1(f1, sp, 0x484);
            swc1(f0, sp, 0x488);
            lw(v0, sp, 0x110);
            if (v0 == 0) {
                // 0x00311ca8
                charge(ctx, 36);
                a0 = addiu(sp, 0x190);
                a1 = addiu(sp, 0x470);
                a2 = 1;
                jal(ctx, 0x311CB4u, gen::fn_sub_4C33D0_004c33d0);  // [RwMatrixScale]
                sw(zero, sp, 0x490);
                v0 = 0x3F800000;
                sw(v0, sp, 0x494);
                sw(zero, sp, 0x498);
                v0 = 0x43340000;
                mtc1(v0, f12);
                a0 = addiu(sp, 0x210);
                a1 = addiu(sp, 0x490);
                a2 = 0;
                jal(ctx, 0x311CE0u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                sw(zero, sp, 0x490);
                sw(zero, sp, 0x494);
                v0 = 0x3F800000;
                sw(v0, sp, 0x498);
                v0 = lui(0xC2B4);
                mtc1(v0, f12);
                a0 = addiu(sp, 0x210);
                a1 = addiu(sp, 0x490);
                a2 = 2;
                jal(ctx, 0x311D0Cu, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                a0 = addiu(sp, 0x250);
                a1 = addiu(sp, 0x210);
                a2 = addiu(sp, 0x410);
                jal(ctx, 0x311D20u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                lhu(v1, s3, 0);
                v0 = v1 & 0x100;
                if (v0 != 0) {
                    // 0x003121cc
                    charge(ctx, 4);
                    a0 = addiu(sp, 0x180);
                    a1 = addiu(sp, 0x190);
                    jal(ctx, 0x3121D4u, gen::fn_sub_4BDCB0_004bdcb0);
                } else {
                    // 0x00311d38
                    charge(ctx, 3);
                    v0 = v1 & 0x80;
                    if (v0 != 0) {
                        // 0x003120b8
                        charge(ctx, 21);
                        sw(zero, sp, 0x100);
                        v0 = 0x3F800000;
                        sw(v0, sp, 0x490);
                        sw(zero, sp, 0x494);
                        sw(zero, sp, 0x498);
                        a0 = addiu(sp, 0x210);
                        a1 = addiu(sp, 0x490);
                        lwc1(f12, s3, 60);
                        a2 = 0;
                        jal(ctx, 0x3120DCu, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                        sw(zero, sp, 0x490);
                        v0 = 0x3F800000;
                        sw(v0, sp, 0x494);
                        sw(zero, sp, 0x498);
                        a0 = addiu(sp, 0x210);
                        a1 = addiu(sp, 0x490);
                        lwc1(f12, s3, 64);
                        a2 = 2;
                        jal(ctx, 0x312104u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                    } else {
                        // 0x00311d44
                        charge(ctx, 5);
                        v0 = 1;
                        sw(v0, sp, 0x100);
                        v0 = v1 & 0x40;
                        if (v0 == 0) {
                            // 0x00311d90
                            charge(ctx, 15);
                            lwc1(f2, s3, 60);
                            lwc1(f1, s3, 64);
                            lwc1(f0, s3, 68);
                            swc1(f2, sp, 0x470);
                            swc1(f1, sp, 0x474);
                            swc1(f0, sp, 0x478);
                            lwc1(f0, sp, 0x470);
                            neg_s(f0, f0);
                            swc1(f0, sp, 0x470);
                            lwc1(f0, sp, 0x474);
                            neg_s(f0, f0);
                            swc1(f0, sp, 0x474);
                            lwc1(f0, sp, 0x478);
                            neg_s(f0, f0);
                            swc1(f0, sp, 0x478);
                        } else {
                            // 0x00311d58
                            charge(ctx, 14);
                            lwc1(f1, s3, 60);
                            lwc1(f0, sp, 0x480);
                            sub_s(f0, f0, f1);
                            swc1(f0, sp, 0x470);
                            lwc1(f1, s3, 64);
                            lwc1(f0, sp, 0x484);
                            sub_s(f0, f0, f1);
                            swc1(f0, sp, 0x474);
                            lwc1(f1, s3, 68);
                            lwc1(f0, sp, 0x488);
                            sub_s(f0, f0, f1);
                            swc1(f0, sp, 0x478);
                        }
                        // 0x00311dcc
                        charge(ctx, 92);
                        a0 = addiu(sp, 0x470);
                        a1 = a0;
                        jal(ctx, 0x311DD4u, gen::fn_sub_4C69F0_004c69f0);
                        a0 = addiu(sp, 0x1D0);
                        a1 = addiu(sp, 0x410);
                        jal(ctx, 0x311DE4u, gen::fn_sub_4C32A0_004c32a0);
                        a0 = addiu(sp, 0x470);
                        a1 = a0;
                        a2 = addiu(sp, 0x1D0);
                        jal(ctx, 0x311DF8u, gen::fn_sub_4C6C60_004c6c60);
                        a0 = addiu(sp, 0x470);
                        a1 = a0;
                        jal(ctx, 0x311E08u, gen::fn_sub_4C69F0_004c69f0);
                        sw(zero, sp, 0x450);
                        sw(zero, sp, 0x454);
                        v0 = lui(0xC2C8);
                        sw(v0, sp, 0x458);
                        a0 = addiu(sp, 0x450);
                        a1 = a0;
                        a2 = addiu(sp, 0x310);
                        jal(ctx, 0x311E2Cu, gen::fn_sub_4C6BE0_004c6be0);
                        lwc1(f1, sp, 0x480);
                        lwc1(f0, sp, 0x450);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x460);
                        lwc1(f1, sp, 0x484);
                        lwc1(f0, sp, 0x454);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x464);
                        lwc1(f1, sp, 0x488);
                        lwc1(f0, sp, 0x458);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x468);
                        a0 = addiu(sp, 0x460);
                        a1 = a0;
                        a2 = addiu(sp, 0x1D0);
                        jal(ctx, 0x311E70u, gen::fn_sub_4C6C60_004c6c60);
                        a0 = addiu(sp, 0x460);
                        a1 = a0;
                        jal(ctx, 0x311E80u, gen::fn_sub_4C69F0_004c69f0);
                        lwc1(f12, sp, 0x464);
                        jal(ctx, 0x311E8Cu, gen::fn_acosf_0052e9e8);  // [acosf]
                        lwc1(f1, gp, -32560);  // 0x7CADC0
                        mul_s(f1, f1, f0);
                        v0 = 0x42B40000;
                        mtc1(v0, f0);
                        sub_s(f20, f1, f0);
                        lwc1(f12, sp, 0x460);
                        lwc1(f13, sp, 0x468);
                        jal(ctx, 0x311EB4u, gen::fn_atan2f_0052ea18);  // [atan2f]
                        lwc1(f3, gp, -32560);  // 0x7CADC0
                        v0 = 0x43340000;
                        mtc1(v0, f2);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f21, f3, f0);
                        lwc1(f12, sp, 0x474);
                        jal(ctx, 0x311EDCu, gen::fn_acosf_0052e9e8);  // [acosf]
                        lwc1(f1, gp, -32560);  // 0x7CADC0
                        mul_s(f1, f1, f0);
                        v0 = 0x42B40000;
                        mtc1(v0, f0);
                        sub_s(f23, f1, f0);
                        lwc1(f12, sp, 0x470);
                        lwc1(f13, sp, 0x478);
                        jal(ctx, 0x311F04u, gen::fn_atan2f_0052ea18);  // [atan2f]
                        lwc1(f3, gp, -32560);  // 0x7CADC0
                        v0 = 0x43340000;
                        mtc1(v0, f2);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f22, f3, f0);
                        sub_s(f23, f23, f20);
                        v0 = 0x43B40000;
                        mtc1(v0, f0);
                        for (;;) {
                            // 0x00311f40
                            charge(ctx, 6);
                            c_lt_s(f23, f1);
                            if (!cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00311f3c
                            charge(ctx, 1);
                            add_s(f23, f23, f0);
                        }
                        // 0x00311f58
                        charge(ctx, 4);
                        v0 = 0x43B40000;
                        mtc1(v0, f0);
                        for (;;) {
                            // 0x00311f6c
                            charge(ctx, 6);
                            c_le_s(f23, f0);
                            if (cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00311f68
                            charge(ctx, 1);
                            sub_s(f23, f23, f0);
                        }
                        // 0x00311f84
                        charge(ctx, 4);
                        lwc1(f2, s3, 8);
                        c_le_s(f23, f2);
                        if (!cond(ctx)) {
                            // 0x00311f94
                            charge(ctx, 4);
                            sub_s(f1, f0, f2);
                            c_lt_s(f23, f1);
                            if (cond(ctx)) {
                                // 0x00311fa4
                                charge(ctx, 6);
                                v0 = 0x43340000;
                                mtc1(v0, f0);
                                c_lt_s(f23, f0);
                                if (!cond(ctx)) {
                                    // 0x00311fc8
                                    charge(ctx, 1);
                                    mov_s(f23, f1);
                                } else {
                                    // 0x00311fbc
                                    charge(ctx, 3);
                                    mov_s(f23, f2);
                                }
                                // 0x00311fcc
                                charge(ctx, 1);
                                s5 = 1;
                            }
                        }
                        // 0x00311fd0
                        charge(ctx, 13);
                        add_s(f0, f23, f20);
                        neg_s(f12, f0);
                        a0 = addiu(sp, 0x210);
                        a1 = addiu(sp, 0x260);
                        a2 = 0;
                        jal(ctx, 0x311FE4u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                        sub_s(f22, f22, f21);
                        v0 = 0x43B40000;
                        mtc1(v0, f1);
                        mtc1(zero, f0);
                        for (;;) {
                            // 0x00312008
                            charge(ctx, 6);
                            c_lt_s(f22, f0);
                            if (!cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00312004
                            charge(ctx, 1);
                            add_s(f22, f22, f1);
                        }
                        // 0x00312020
                        charge(ctx, 4);
                        v0 = 0x43B40000;
                        mtc1(v0, f0);
                        for (;;) {
                            // 0x00312034
                            charge(ctx, 6);
                            c_le_s(f22, f0);
                            if (cond(ctx)) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00312030
                            charge(ctx, 1);
                            sub_s(f22, f22, f0);
                        }
                        // 0x0031204c
                        charge(ctx, 4);
                        lwc1(f2, s3, 12);
                        c_le_s(f22, f2);
                        if (!cond(ctx)) {
                            // 0x0031205c
                            charge(ctx, 4);
                            sub_s(f1, f0, f2);
                            c_lt_s(f22, f1);
                            if (cond(ctx)) {
                                // 0x0031206c
                                charge(ctx, 6);
                                v0 = 0x43340000;
                                mtc1(v0, f0);
                                c_lt_s(f22, f0);
                                if (!cond(ctx)) {
                                    // 0x00312090
                                    charge(ctx, 1);
                                    mov_s(f22, f1);
                                } else {
                                    // 0x00312084
                                    charge(ctx, 3);
                                    mov_s(f22, f2);
                                }
                                // 0x00312094
                                charge(ctx, 1);
                                s5 = 1;
                            }
                        }
                        // 0x00312098
                        charge(ctx, 8);
                        add_s(f12, f22, f21);
                        a0 = addiu(sp, 0x210);
                        a1 = addiu(sp, 0x250);
                        a2 = 2;
                        jal(ctx, 0x3120A8u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate]
                    }
                    // 0x0031210c
                    charge(ctx, 13);
                    a0 = s1;
                    a1 = addiu(sp, 0x250);
                    a2 = addiu(sp, 0x210);
                    jal(ctx, 0x312118u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                    a0 = addiu(sp, 0x180);
                    a1 = s1;
                    jal(ctx, 0x312128u, gen::fn_sub_4BDCB0_004bdcb0);
                    lhu(v1, s3, 0);
                    v0 = v1 & 0x1000;
                    if (v0 != 0) {
                        // 0x00312140
                        charge(ctx, 2);
                        if (s5 == 0) {
                            goto L_00312188;
                        }
                        // 0x00312148
                        charge(ctx, 3);
                        v0 = v1 & 0x800;
                        if (v0 == 0) {
                            // 0x00312154
                            charge(ctx, 8);
                            lwc1(f3, sp, 0x180);
                            lwc1(f2, sp, 0x184);
                            lwc1(f1, sp, 0x188);
                            lwc1(f0, sp, 0x18C);
                            swc1(f3, s3, 32);
                            swc1(f2, s3, 36);
                            swc1(f1, s3, 40);
                            swc1(f0, s3, 44);
                        }
                        // 0x00312174
                        charge(ctx, 5);
                        lhu(v0, s3, 0);
                        v0 = v0 | 0x800;
                        sh(v0, s3, 0);
                        goto L_00312194;
                    }
                L_00312188:
                    charge(ctx, 3);
                    lhu(v0, s3, 0);
                    v0 = v0 & 0xF7FF;
                    sh(v0, s3, 0);
                L_00312194:
                    charge(ctx, 4);
                    lhu(v0, s3, 0);
                    v0 = v0 & 0x800;
                    if (v0 != 0) {
                        // 0x003121a4
                        charge(ctx, 10);
                        lwc1(f3, s3, 32);
                        lwc1(f2, s3, 36);
                        lwc1(f1, s3, 40);
                        lwc1(f0, s3, 44);
                        swc1(f3, sp, 0x180);
                        swc1(f2, sp, 0x184);
                        swc1(f1, sp, 0x188);
                        swc1(f0, sp, 0x18C);
                    }
                }
                // 0x003121dc
                charge(ctx, 4);
                lhu(v1, s3, 0);
                v0 = v1 & 0x200;
                if (v0 == 0) {
                    // 0x00312240
                    charge(ctx, 3);
                    v0 = v1 & 0x100;
                    if (v0 != 0) {
                        // 0x0031224c
                        charge(ctx, 16);
                        lwc1(f9, sp, 0x184);
                        lwc1(f8, s3, 20);
                        lwc1(f2, sp, 0x180);
                        lwc1(f7, s3, 16);
                        lwc1(f1, sp, 0x188);
                        lwc1(f6, s3, 24);
                        mula_s(f8, f9);
                        mtc1(zero, f5);
                        madda_s(f7, f2);
                        madda_s(f6, f1);
                        lwc1(f0, sp, 0x18C);
                        lwc1(f4, s3, 28);
                        madd_s(f12, f4, f0);
                        c_lt_s(f12, f5);
                        if (cond(ctx)) {
                            // 0x0031228c
                            charge(ctx, 11);
                            neg_s(f3, f0);
                            neg_s(f2, f2);
                            neg_s(f0, f9);
                            neg_s(f1, f1);
                            mul_s(f0, f8, f0);
                            adda_s(f5, f0);
                            madd_s(f0, f7, f2);
                            adda_s(f5, f0);
                            madd_s(f0, f6, f1);
                            adda_s(f5, f0);
                            madd_s(f12, f4, f3);
                        }
                        // 0x003122b8
                        charge(ctx, 10);
                        jal(ctx, 0x3122B8u, gen::fn_acosf_0052e9e8);  // [acosf]
                        v0 = 0x40000000;
                        mtc1(v0, f1);
                        mul_s(f1, f1, f0);
                        lwc1(f0, gp, -32524);  // 0x7CADE4
                        c_lt_s(f1, f0);
                        if (cond(ctx)) {
                            // 0x003122e0
                            charge(ctx, 6);
                            lhu(v0, s3, 0);
                            v0 = v0 & 0xFE1F;
                            sh(v0, s3, 0);
                            lhu(v0, s3, 0);
                            v0 = v0 & 0xFBFF;
                            sh(v0, s3, 0);
                        }
                        // 0x003122f8
                        charge(ctx, 3);
                        lhu(v0, s3, 0);
                        v0 = v0 & 0xF7FF;
                        sh(v0, s3, 0);
                    }
                    // 0x00312304
                    charge(ctx, 19);
                    a0 = addiu(sp, 0x130);
                    lwc1(f3, s3, 16);
                    lwc1(f2, s3, 20);
                    lwc1(f1, s3, 24);
                    lwc1(f0, s3, 28);
                    swc1(f3, sp, 0x130);
                    swc1(f2, sp, 0x134);
                    swc1(f1, sp, 0x138);
                    swc1(f0, sp, 0x13C);
                    a1 = addiu(sp, 0x180);
                    a2 = addiu(sp, 0x150);
                    jal(ctx, 0x312330u, gen::fn_sub_4BE310_004be310);
                    lwc1(f0, s3, 4);
                    mtc1(zero, f12);
                    c_le_s(f0, f12);
                    if (!cond(ctx)) {
                        // 0x00312360
                        charge(ctx, 6);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                        c_le_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x00312388
                            charge(ctx, 4);
                            sub_s(f1, f1, f0);
                            lw(v0, sp, 0x174);
                            if (v0 == 0) {
                                // 0x00312398
                                charge(ctx, 37);
                                lwc1(f11, sp, 0x170);
                                mul_s(f4, f1, f11);
                                mul_s(f3, f4, f4);
                                lwc1(f10, gp, -32436);  // 0x7CAE3C
                                lwc1(f9, gp, -32696);  // 0x7CAD38
                                adda_s(f12, f9);
                                madd_s(f1, f10, f3);
                                lwc1(f8, gp, -32488);  // 0x7CAE08
                                adda_s(f12, f8);
                                madd_s(f1, f3, f1);
                                lwc1(f7, gp, -32688);  // 0x7CAD40
                                adda_s(f12, f7);
                                madd_s(f1, f3, f1);
                                lwc1(f6, gp, -32684);  // 0x7CAD44
                                adda_s(f12, f6);
                                madd_s(f1, f3, f1);
                                lwc1(f5, gp, -32680);  // 0x7CAD48
                                adda_s(f12, f5);
                                madd_s(f2, f3, f1);
                                mul_s(f1, f3, f4);
                                adda_s(f12, f4);
                                madd_s(f1, f1, f2);
                                mul_s(f4, f0, f11);
                                mul_s(f3, f4, f4);
                                adda_s(f12, f9);
                                madd_s(f0, f10, f3);
                                adda_s(f12, f8);
                                madd_s(f0, f3, f0);
                                adda_s(f12, f7);
                                madd_s(f0, f3, f0);
                                adda_s(f12, f6);
                                madd_s(f0, f3, f0);
                                adda_s(f12, f5);
                                madd_s(f2, f3, f0);
                                mul_s(f0, f3, f4);
                                adda_s(f12, f4);
                                madd_s(f0, f0, f2);
                            }
                            // 0x0031242c
                            charge(ctx, 28);
                            lwc1(f2, sp, 0x150);
                            mul_s(f6, f2, f1);
                            swc1(f6, sp, 0x140);
                            lwc1(f2, sp, 0x154);
                            mul_s(f5, f2, f1);
                            swc1(f5, sp, 0x144);
                            lwc1(f2, sp, 0x158);
                            mul_s(f4, f2, f1);
                            swc1(f4, sp, 0x148);
                            lwc1(f2, sp, 0x160);
                            mtc1(zero, f3);
                            adda_s(f3, f6);
                            madd_s(f2, f2, f0);
                            swc1(f2, sp, 0x140);
                            lwc1(f2, sp, 0x164);
                            adda_s(f3, f5);
                            madd_s(f2, f2, f0);
                            swc1(f2, sp, 0x144);
                            lwc1(f2, sp, 0x168);
                            adda_s(f3, f4);
                            madd_s(f2, f2, f0);
                            swc1(f2, sp, 0x148);
                            lwc1(f3, sp, 0x15C);
                            lwc1(f2, sp, 0x16C);
                            mula_s(f2, f0);
                            madd_s(f0, f3, f1);
                            swc1(f0, sp, 0x14C);
                        } else {
                            // 0x00312378
                            charge(ctx, 4);
                            lq(v0, sp, 0x180);
                            sq(v0, sp, 0x140);
                        }
                    } else {
                        // 0x00312350
                        charge(ctx, 4);
                        lq(v0, sp, 0x130);
                        sq(v0, sp, 0x140);
                    }
                    // 0x0031249c
                    charge(ctx, 4);
                    lhu(v0, s3, 0);
                    v0 = v0 & 0x2000;
                    if (v0 != 0) {
                        // 0x003124ac
                        charge(ctx, 3);
                        lw(v0, sp, 0x100);
                        if (v0 == 0) {
                            goto L_00312760;
                        }
                        // 0x003124b8
                        charge(ctx, 20);
                        a0 = addiu(sp, 0x120);
                        a1 = addiu(sp, 0x190);
                        jal(ctx, 0x3124C0u, gen::fn_sub_4BDCB0_004bdcb0);
                        lwc1(f9, sp, 0x144);
                        lwc1(f8, sp, 0x124);
                        lwc1(f2, sp, 0x140);
                        lwc1(f7, sp, 0x120);
                        lwc1(f1, sp, 0x148);
                        lwc1(f6, sp, 0x128);
                        mula_s(f8, f9);
                        mtc1(zero, f5);
                        madda_s(f7, f2);
                        madda_s(f6, f1);
                        lwc1(f0, sp, 0x14C);
                        lwc1(f4, sp, 0x12C);
                        madd_s(f12, f4, f0);
                        c_lt_s(f12, f5);
                        if (cond(ctx)) {
                            // 0x00312508
                            charge(ctx, 11);
                            neg_s(f3, f0);
                            neg_s(f2, f2);
                            neg_s(f0, f9);
                            neg_s(f1, f1);
                            mul_s(f0, f8, f0);
                            adda_s(f5, f0);
                            madd_s(f0, f7, f2);
                            adda_s(f5, f0);
                            madd_s(f0, f6, f1);
                            adda_s(f5, f0);
                            madd_s(f12, f4, f3);
                        }
                        // 0x00312534
                        charge(ctx, 12);
                        jal(ctx, 0x312534u, gen::fn_acosf_0052e9e8);  // [acosf]
                        v0 = 0x40000000;
                        mtc1(v0, f1);
                        mul_s(f2, f1, f0);
                        lwc1(f1, gp, -32432);  // 0x7CAE40
                        lwc1(f0, s3, 12);
                        mul_s(f0, f1, f0);
                        c_le_s(f2, f0);
                        if (!cond(ctx)) {
                            // 0x0031258c
                            charge(ctx, 17);
                            lwc1(f0, gp, -32428);  // 0x7CAE44
                            div_s(f1, f0, f2);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            sub_s(f20, f0, f1);
                            a0 = addiu(sp, 0x140);
                            a1 = addiu(sp, 0x120);
                            a2 = addiu(sp, 0x150);
                            jal(ctx, 0x3125B4u, gen::fn_sub_4BE310_004be310);
                            mtc1(zero, f11);
                            c_le_s(f20, f11);
                            if (!cond(ctx)) {
                                // 0x003125f8
                                charge(ctx, 6);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                c_le_s(f0, f20);
                                if (!cond(ctx)) {
                                    // 0x00312638
                                    charge(ctx, 4);
                                    sub_s(f0, f0, f20);
                                    lw(v0, sp, 0x174);
                                    if (v0 == 0) {
                                        // 0x00312648
                                        charge(ctx, 37);
                                        lwc1(f10, sp, 0x170);
                                        mul_s(f4, f0, f10);
                                        mul_s(f3, f4, f4);
                                        lwc1(f9, gp, -32424);  // 0x7CAE48
                                        lwc1(f8, gp, -32696);  // 0x7CAD38
                                        adda_s(f11, f8);
                                        madd_s(f0, f9, f3);
                                        lwc1(f7, gp, -32488);  // 0x7CAE08
                                        adda_s(f11, f7);
                                        madd_s(f0, f3, f0);
                                        lwc1(f6, gp, -32688);  // 0x7CAD40
                                        adda_s(f11, f6);
                                        madd_s(f0, f3, f0);
                                        lwc1(f5, gp, -32684);  // 0x7CAD44
                                        adda_s(f11, f5);
                                        madd_s(f0, f3, f0);
                                        lwc1(f2, gp, -32680);  // 0x7CAD48
                                        adda_s(f11, f2);
                                        madd_s(f1, f3, f0);
                                        mul_s(f0, f3, f4);
                                        adda_s(f11, f4);
                                        madd_s(f0, f0, f1);
                                        mul_s(f4, f20, f10);
                                        mul_s(f3, f4, f4);
                                        adda_s(f11, f8);
                                        madd_s(f1, f9, f3);
                                        adda_s(f11, f7);
                                        madd_s(f1, f3, f1);
                                        adda_s(f11, f6);
                                        madd_s(f1, f3, f1);
                                        adda_s(f11, f5);
                                        madd_s(f1, f3, f1);
                                        adda_s(f11, f2);
                                        madd_s(f2, f3, f1);
                                        mul_s(f1, f3, f4);
                                        adda_s(f11, f4);
                                        madd_s(f20, f1, f2);
                                    }
                                    // 0x003126dc
                                    charge(ctx, 33);
                                    lwc1(f1, sp, 0x150);
                                    mul_s(f1, f1, f0);
                                    swc1(f1, s3, 16);
                                    lwc1(f1, sp, 0x154);
                                    mul_s(f1, f1, f0);
                                    swc1(f1, s3, 20);
                                    lwc1(f1, sp, 0x158);
                                    mul_s(f1, f1, f0);
                                    swc1(f1, s3, 24);
                                    lwc1(f2, sp, 0x160);
                                    lwc1(f1, s3, 16);
                                    mtc1(zero, f3);
                                    adda_s(f3, f1);
                                    madd_s(f1, f2, f20);
                                    swc1(f1, s3, 16);
                                    lwc1(f2, sp, 0x164);
                                    lwc1(f1, s3, 20);
                                    adda_s(f3, f1);
                                    madd_s(f1, f2, f20);
                                    swc1(f1, s3, 20);
                                    lwc1(f2, sp, 0x168);
                                    lwc1(f1, s3, 24);
                                    adda_s(f3, f1);
                                    madd_s(f1, f2, f20);
                                    swc1(f1, s3, 24);
                                    lwc1(f2, sp, 0x15C);
                                    lwc1(f1, sp, 0x16C);
                                    mula_s(f1, f20);
                                    madd_s(f0, f2, f0);
                                    swc1(f0, s3, 28);
                                } else {
                                    // 0x00312610
                                    charge(ctx, 10);
                                    lwc1(f3, sp, 0x120);
                                    lwc1(f2, sp, 0x124);
                                    lwc1(f1, sp, 0x128);
                                    lwc1(f0, sp, 0x12C);
                                    swc1(f3, s3, 16);
                                    swc1(f2, s3, 20);
                                    swc1(f1, s3, 24);
                                    swc1(f0, s3, 28);
                                }
                            } else {
                                // 0x003125d0
                                charge(ctx, 10);
                                lwc1(f3, sp, 0x140);
                                lwc1(f2, sp, 0x144);
                                lwc1(f1, sp, 0x148);
                                lwc1(f0, sp, 0x14C);
                                swc1(f3, s3, 16);
                                swc1(f2, s3, 20);
                                swc1(f1, s3, 24);
                                swc1(f0, s3, 28);
                            }
                        } else {
                            // 0x00312564
                            charge(ctx, 10);
                            lwc1(f3, sp, 0x140);
                            lwc1(f2, sp, 0x144);
                            lwc1(f1, sp, 0x148);
                            lwc1(f0, sp, 0x14C);
                            swc1(f3, s3, 16);
                            swc1(f2, s3, 20);
                            swc1(f1, s3, 24);
                            swc1(f0, s3, 28);
                        }
                        goto L_00312780;
                    }
                L_00312760:
                    charge(ctx, 8);
                    lwc1(f3, sp, 0x140);
                    lwc1(f2, sp, 0x144);
                    lwc1(f1, sp, 0x148);
                    lwc1(f0, sp, 0x14C);
                    swc1(f3, s3, 16);
                    swc1(f2, s3, 20);
                    swc1(f1, s3, 24);
                    swc1(f0, s3, 28);
                } else {
                    // 0x003121ec
                    charge(ctx, 11);
                    a0 = addiu(s3, 16);
                    a1 = addiu(sp, 0x190);
                    jal(ctx, 0x3121F4u, gen::fn_sub_4BDCB0_004bdcb0);
                    lhu(v0, s3, 0);
                    v0 = v0 & 0xFDFF;
                    sh(v0, s3, 0);
                    lhu(v1, s3, 0);
                    v0 = v1 & 0x100;
                    if (v0 != 0) {
                        // 0x00312218
                        charge(ctx, 10);
                        v0 = v1 & 0xFE1F;
                        sh(v0, s3, 0);
                        lhu(v0, s3, 0);
                        v0 = v0 & 0xFBFF;
                        sh(v0, s3, 0);
                        lhu(v0, s3, 0);
                        v0 = v0 & 0xF7FF;
                        sh(v0, s3, 0);
                    }
                }
            }
        L_00312780:
            charge(ctx, 3);
            lw(v0, sp, 0x110);
            if (v0 != 0) {
                // 0x003128f8
                charge(ctx, 64);
                lwc1(f4, s3, 20);
                lwc1(f12, s3, 16);
                lwc1(f11, s3, 24);
                lwc1(f3, s3, 28);
                mula_s(f4, f4);
                madda_s(f12, f12);
                madda_s(f11, f11);
                madd_s(f1, f3, f3);
                v0 = 0x40000000;
                mtc1(v0, f0);
                div_s(f0, f0, f1);
                mul_s(f2, f12, f0);
                mul_s(f1, f4, f0);
                mul_s(f0, f11, f0);
                mul_s(f10, f2, f3);
                mul_s(f9, f1, f3);
                mul_s(f8, f0, f3);
                mul_s(f7, f12, f2);
                mul_s(f6, f4, f1);
                mul_s(f5, f11, f0);
                mul_s(f4, f4, f0);
                mul_s(f3, f11, f2);
                mul_s(f2, f12, f1);
                add_s(f0, f6, f5);
                v0 = 0x3F800000;
                mtc1(v0, f1);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x190);
                add_s(f0, f2, f8);
                swc1(f0, sp, 0x194);
                sub_s(f0, f3, f9);
                swc1(f0, sp, 0x198);
                sub_s(f0, f2, f8);
                swc1(f0, sp, 0x1A0);
                add_s(f0, f5, f7);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x1A4);
                add_s(f0, f4, f10);
                swc1(f0, sp, 0x1A8);
                add_s(f0, f3, f9);
                swc1(f0, sp, 0x1B0);
                sub_s(f0, f4, f10);
                swc1(f0, sp, 0x1B4);
                add_s(f0, f7, f6);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x1B8);
                sw(zero, sp, 0x1C0);
                sw(zero, sp, 0x1C4);
                sw(zero, sp, 0x1C8);
                v0 = 3;
                sw(v0, sp, 0x19C);
                lwc1(f2, s3, 48);
                lwc1(f1, s3, 52);
                lwc1(f0, s3, 56);
                swc1(f2, sp, 0x470);
                swc1(f1, sp, 0x474);
                swc1(f0, sp, 0x478);
                lw(v0, sp, 0x11C);
                lhu(v0, v0, 0);
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    // 0x003129f8
                    charge(ctx, 14);
                    v0 = 0x950000;
                    lwc1(f1, v0, 29120);  // 0x9571C0 bone parameter 0 (slot +68 copy)
                    lwc1(f0, sp, 0x470);
                    mul_s(f0, f0, f1);
                    swc1(f0, sp, 0x470);
                    v0 = 0x950000;
                    lwc1(f0, v0, 29124);  // 0x9571C4 bone parameter 1 (slot +72 copy)
                    mul_s(f1, f1, f0);
                    lwc1(f0, sp, 0x474);
                    mul_s(f0, f0, f1);
                    swc1(f0, sp, 0x474);
                    lwc1(f0, sp, 0x478);
                    mul_s(f0, f0, f1);
                    swc1(f0, sp, 0x478);
                }
                // 0x00312a30
                charge(ctx, 16);
                a0 = addiu(sp, 0x190);
                a1 = addiu(sp, 0x470);
                a2 = 1;
                jal(ctx, 0x312A3Cu, gen::fn_sub_4C33D0_004c33d0);  // [RwMatrixScale]
                lwc1(f2, sp, 0x480);
                lwc1(f1, sp, 0x484);
                lwc1(f0, sp, 0x488);
                swc1(f2, sp, 0x1C0);
                swc1(f1, sp, 0x1C4);
                swc1(f0, sp, 0x1C8);
                a0 = s1;
                a1 = addiu(sp, 0x190);
                lw(a2, sp, 0x110);
                jal(ctx, 0x312A68u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
            } else {
                // 0x0031278c
                charge(ctx, 64);
                lwc1(f4, s3, 20);
                lwc1(f12, s3, 16);
                lwc1(f11, s3, 24);
                lwc1(f3, s3, 28);
                mula_s(f4, f4);
                madda_s(f12, f12);
                madda_s(f11, f11);
                madd_s(f1, f3, f3);
                v0 = 0x40000000;
                mtc1(v0, f0);
                div_s(f0, f0, f1);
                mul_s(f2, f12, f0);
                mul_s(f1, f4, f0);
                mul_s(f0, f11, f0);
                mul_s(f10, f2, f3);
                mul_s(f9, f1, f3);
                mul_s(f8, f0, f3);
                mul_s(f7, f12, f2);
                mul_s(f6, f4, f1);
                mul_s(f5, f11, f0);
                mul_s(f4, f4, f0);
                mul_s(f3, f11, f2);
                mul_s(f2, f12, f1);
                add_s(f0, f6, f5);
                v0 = 0x3F800000;
                mtc1(v0, f1);
                sub_s(f0, f1, f0);
                swc1(f0, s1, 0);
                add_s(f0, f2, f8);
                swc1(f0, s1, 4);
                sub_s(f0, f3, f9);
                swc1(f0, s1, 8);
                sub_s(f0, f2, f8);
                swc1(f0, s1, 16);
                add_s(f0, f5, f7);
                sub_s(f0, f1, f0);
                swc1(f0, s1, 20);
                add_s(f0, f4, f10);
                swc1(f0, s1, 24);
                add_s(f0, f3, f9);
                swc1(f0, s1, 32);
                sub_s(f0, f4, f10);
                swc1(f0, s1, 36);
                add_s(f0, f7, f6);
                sub_s(f0, f1, f0);
                swc1(f0, s1, 40);
                sw(zero, s1, 48);
                sw(zero, s1, 52);
                sw(zero, s1, 56);
                v0 = 3;
                sw(v0, s1, 12);
                lwc1(f2, s3, 48);
                lwc1(f1, s3, 52);
                lwc1(f0, s3, 56);
                swc1(f2, sp, 0x470);
                swc1(f1, sp, 0x474);
                swc1(f0, sp, 0x478);
                lw(v0, sp, 0x11C);
                lhu(v0, v0, 0);
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    // 0x0031288c
                    charge(ctx, 14);
                    v0 = 0x950000;
                    lwc1(f1, v0, 29120);  // 0x9571C0 bone parameter 0 (slot +68 copy)
                    lwc1(f0, sp, 0x470);
                    mul_s(f0, f0, f1);
                    swc1(f0, sp, 0x470);
                    v0 = 0x950000;
                    lwc1(f0, v0, 29124);  // 0x9571C4 bone parameter 1 (slot +72 copy)
                    mul_s(f1, f1, f0);
                    lwc1(f0, sp, 0x474);
                    mul_s(f0, f0, f1);
                    swc1(f0, sp, 0x474);
                    lwc1(f0, sp, 0x478);
                    mul_s(f0, f0, f1);
                    swc1(f0, sp, 0x478);
                }
                // 0x003128c4
                charge(ctx, 13);
                a0 = s1;
                a1 = addiu(sp, 0x470);
                a2 = 1;
                jal(ctx, 0x3128D0u, gen::fn_sub_4C33D0_004c33d0);  // [RwMatrixScale]
                lwc1(f2, sp, 0x480);
                lwc1(f1, sp, 0x484);
                lwc1(f0, sp, 0x488);
                swc1(f2, s1, 48);
                swc1(f1, s1, 52);
                swc1(f0, s1, 56);
            }
            // 0x00312a70
            charge(ctx, 3);
            lw(v0, s7, 12);
            if (v0 != 0) {
                // 0x00312a7c
                charge(ctx, 3);
                lw(v0, v0, 4);
                if (v0 != 0) {
                    // 0x00312a88
                    charge(ctx, 5);
                    lw(a0, v0, 160);
                    lbu(v0, a0, 3);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x00312a9c
                        charge(ctx, 4);
                        jal(ctx, 0x312A9Cu, gen::fn_sub_4CF4C0_004cf4c0);
                    }
                }
            }
        } else {
            // 0x00311b8c
            charge(ctx, 2);
            // 0x00312aac
            charge(ctx, 5);
            a0 = s1;
            a1 = addiu(sp, 0x290);
            a2 = s2;
            jal(ctx, 0x312AB8u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
        }
        // 0x00312ac0
        charge(ctx, 3);
        lw(s5, s7, 12);
        if (s5 != 0) {
            // 0x00312acc
            charge(ctx, 3);
            lq(v0, sp, 0xC0);
            if (v0 != 0) {
                // 0x00312ad8
                charge(ctx, 3);
                a2 = addiu(sp, 0x290);
                a1 = addiu(s5, 16);
                a0 = 8;
                for (;;) {
                    // 0x00312ae4
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
                // 0x00312b08
                charge(ctx, 3);
                lw(v0, sp, 0xF0);
                if (v0 == 0) {
                    // 0x00312b14
                    charge(ctx, 3);
                    a0 = s5;
                    jal(ctx, 0x312B18u, gen::fn_sub_4CB270_004cb270);  // [RwFrameUpdateObjects]
                }
            }
            // 0x00312b20
            charge(ctx, 3);
            lw(v0, sp, 0xF0);
            if (v0 != 0) {
                // 0x00312b2c
                charge(ctx, 3);
                lq(v0, sp, 0xB0);
                if (v0 == 0) {
                    // 0x00312b54
                    charge(ctx, 3);
                    a1 = addiu(s5, 80);
                    a0 = 8;
                    a2 = s1;
                    for (;;) {
                        // 0x00312b60
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
                } else {
                    // 0x00312b38
                    charge(ctx, 7);
                    a0 = addiu(s5, 80);
                    a1 = s1;
                    a2 = addiu(sp, 0x410);
                    jal(ctx, 0x312B44u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
                }
                // 0x00312b84
                charge(ctx, 5);
                lbu(v1, s5, 3);
                v0 = si(-5);
                v0 = v1 & v0;
                v0 = v0 | 0x8;
                sb(v0, s5, 3);
            }
        }
        // 0x00312b98
        charge(ctx, 5);
        lw(v0, s7, 8);
        v1 = v0 & 0x3;
        v0 = 3;
        if (v1 != v0) {
            // 0x00312bac
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00312bf0
                charge(ctx, 3);
                sw(s2, s6, 0);
                s6 = addiu(s6, 4);
                s2 = s1;
            } else {
                // 0x00312bb8
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00312be0
                    charge(ctx, 4);
                    s6 = addiu(s6, -4);
                    lw(s2, s6, 0);
                } else {
                    // 0x00312bc4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00312bd4
                        charge(ctx, 3);
                        s2 = s1;
                    } else {
                        // 0x00312bcc
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x00312bfc
        charge(ctx, 5);
        lq(v0, sp, 0xD0);
        s0 = addu(s0, v0);
        s1 = addiu(s1, 64);
        s7 = addiu(s7, 16);
        fp = addiu(fp, 0x1);
    }
    // 0x00312c20
    charge(ctx, 18);
    v0 = 1;
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
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x4A0);
}

// 0x00317730 sub_317730 -- 744 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_317730 [mdlModelUpdate]: Per frame, one ready model ($a0, flag 0x1000): places the clump (root offset x
// placement), sets the children's parent matrix, the look scale, updates the four animation slots in order (each gets
// the previous slot), the material animation, the effect list, each slot's effect binding and the sound record, then
// every attached child (copying the placement or a helper matrix) recursively.
void sub_317730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00317730
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lhu(v1, a0, mdl::kMdlFlags);
    v1 = v1 & 0x1000;
    if (v1 != 0) {
        // 0x0031775c
        charge(ctx, 22);
        lw(v0, s2, mdl::kMdlClump);
        lw(s0, v0, 4);
        a0 = addiu(sp, 0x50);
        a1 = addiu(s2, 64);
        a2 = s2;
        jal(ctx, 0x317770u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
        a0 = s0;
        a1 = addiu(sp, 0x50);
        a2 = 0;
        jal(ctx, 0x317784u, gen::fn_sub_4CB7F0_004cb7f0);  // [RwFrameTransform]
        a0 = s2;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x317794u, gen::fn_sub_3197C0_003197c0);  // [mdlModelSetChildrenParentMatrix]
        s1 = 0;
        a0 = s2;
        jal(ctx, 0x3177A4u, gen::fn_sub_3191D0_003191d0);  // [mdlModelIsLooking]
        if (v0 != 0) {
            // 0x003177b4
            charge(ctx, 4);
            a0 = s2;
            a1 = addiu(s2, 128);
            jal(ctx, 0x3177BCu, gen::fn_sub_319210_00319210);  // [mdlModelSetLookScale]
        }
        // 0x003177c4
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x00317818
            charge(ctx, 3);
            v0 = sltiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003177d0
            charge(ctx, 6);
            a1 = s0 & 0xFFFF;
            a0 = s2;
            jal(ctx, 0x3177D8u, gen::fn_sub_3185B0_003185b0);  // [mdlModelHasAnimSet]
            if (v0 != 0) {
                // 0x003177e8
                charge(ctx, 11);
                v0 = sll(s0, 2);
                v0 = addu(v0, s0);
                v0 = sll(v0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(s2, v0);
                a0 = addiu(v0, 236);
                a1 = s1;
                jal(ctx, 0x317808u, gen::fn_sub_313490_00313490);  // [mdlAnimSlotUpdate]
                s1 = v0;
            }
            // 0x00317814
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x00317824
        charge(ctx, 6);
        a0 = addiu(s2, 868);
        jal(ctx, 0x317828u, gen::fn_sub_314D30_00314d30);  // [mdlMatAnimUpdate]
        lw(a0, s2, mdl::kMdlFxList);
        if (a0 != 0) {
            // 0x0031783c
            charge(ctx, 7);
            a1 = addiu(s2, 128);
            jal(ctx, 0x317840u, gen::fn_sub_31DDA0_0031dda0);  // [mdlFxListSet]
            lw(a0, s2, mdl::kMdlFxList);
            a1 = s2;
            jal(ctx, 0x317850u, gen::fn_sub_31D9C0_0031d9c0);  // [mdlFxListPlace]
        }
        // 0x00317858
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x00317898
            charge(ctx, 3);
            v0 = sltiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00317864
            charge(ctx, 9);
            v0 = sll(s0, 2);
            v0 = addu(v0, s0);
            v0 = sll(v0, 3);
            v0 = subu(v0, s0);
            v0 = sll(v0, 2);
            v0 = addu(s2, v0);
            lw(a0, v0, 284);
            if (a0 != 0) {
                // 0x00317888
                charge(ctx, 3);
                a1 = s2;
                jal(ctx, 0x31788Cu, gen::fn_sub_311480_00311480);  // [mdlAnimFxUpdate]
            }
            // 0x00317894
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x003178a4
        charge(ctx, 6);
        a0 = addiu(s2, 1016);
        jal(ctx, 0x3178A8u, gen::fn_sub_31F5C0_0031f5c0);  // [mdlSoundUpdate]
        s1 = 0;
        for (;;) {
            // 0x003179ec
            charge(ctx, 3);
            v1 = sltiu(s1, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003178bc
            charge(ctx, 8);
            v1 = sll(s1, 1);
            v1 = addu(v1, s1);
            v1 = sll(v1, 2);
            a0 = addu(s2, v1);
            lbu(v1, a0, 948);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x003178dc
                charge(ctx, 4);
                s0 = addiu(a0, 952);
                lw(v1, a0, 952);
                if (v1 != 0) {
                    // 0x003178ec
                    charge(ctx, 6);
                    a1 = s1 & 0xFFFF;
                    a0 = s2;
                    jal(ctx, 0x3178F4u, gen::fn_sub_319770_00319770);  // [mdlModelAttachReady]
                    if (v0 != 0) {
                        // 0x00317904
                        charge(ctx, 8);
                        v0 = sll(s1, 1);
                        v0 = addu(v0, s1);
                        v0 = sll(v0, 2);
                        a3 = addu(s2, v0);
                        lw(v0, s0, 0);
                        a2 = addiu(s2, 64);
                        a1 = addiu(v0, 64);
                        a0 = 8;
                        for (;;) {
                            // 0x00317924
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
                        // 0x00317948
                        charge(ctx, 5);
                        s3 = addiu(a3, 956);
                        lw(v1, a3, 956);
                        v0 = si(-1);
                        if (v1 == v0) {
                            // 0x00317984
                            charge(ctx, 3);
                            lw(a1, s0, 0);
                            a0 = 8;
                            a2 = s2;
                            for (;;) {
                                // 0x00317990
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
                        } else {
                            // 0x0031795c
                            charge(ctx, 10);
                            lw(a0, s0, 0);
                            jal(ctx, 0x317960u, gen::fn_sub_318B60_00318b60);  // [mdlModelGetPlacement]
                            lw(a1, s3, 0);
                            a0 = s2;
                            a2 = v0;
                            jal(ctx, 0x317974u, gen::fn_sub_318D10_00318d10);  // [mdlModelGetHelperMatrix]
                        }
                        // 0x003179b4
                        charge(ctx, 13);
                        v0 = sll(s1, 1);
                        v0 = addu(v0, s1);
                        v0 = sll(v0, 2);
                        v0 = addu(s2, v0);
                        s0 = addiu(v0, 952);
                        lw(a0, v0, 952);
                        a1 = 0;
                        lwc1(f12, s2, 244);
                        jal(ctx, 0x3179D4u, gen::fn_sub_3189F0_003189f0);  // [mdlModelSetAnimSpeed]
                        lw(a0, s0, 0);
                        jal(ctx, 0x3179E0u, gen::fn_sub_317730_00317730);  // [mdlModelUpdate]
                    }
                }
            }
            // 0x003179e8
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
    }
    // 0x003179f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

}  // namespace p3fes::game
