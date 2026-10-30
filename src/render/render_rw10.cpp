// Slice render_rw10: RenderWare, tenth (last) pass of the band 0x450000-0x4FFFFF -- the PS2 native-data streams, the
// Rt2d fonts, the image-stored texture dictionaries, RtTileRender, the raster / texture native writers, the string /
// camera / spline streams, PTank's remaining geometries, and the engine / sky device start-up (the group overview, the
// record layouts and the band's final stays-recompiled list are in game/include/p3fes/game/render_rw10.h). Every body
// started as p3fes_handgen's output and keeps the recompiled body's registers, frame, spills, $ra links, cycle charges
// and check points statement for statement (game/include/p3fes/game/hg_cpu.h); what was added is the role of each
// function and the names of the record offsets (rw10::, rw9::) where one base register holds one record throughout.
// sub_* keep their symbols/functions.json names; proposed names are in brackets (symbols/deltas/render_rw10.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw10.h"

namespace p3fes::recomp_gen {
void fn_DisableDmac_00503d10(p3fes::EEContext&);
void fn_DisableIntc_00503c40(p3fes::EEContext&);
void fn_RwEngineOpen_004ca700(p3fes::EEContext&);
void fn_RwEngineStart_004ca640(p3fes::EEContext&);
void fn_RxPipelineExecute_004f2e70(p3fes::EEContext&);
void fn_SkyCreateDBRaster_004e3320(p3fes::EEContext&);
void fn_SkyCreateFBRaster_004e3100(p3fes::EEContext&);
void fn_SkyUseMode_004dff20(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn__dispRefImageField_0_004c72e0(p3fes::EEContext&);
void fn__rwDeviceSystemRequest_004ca3e0(p3fes::EEContext&);
void fn__sceRemoveDmacHandler_00502e90(p3fes::EEContext&);
void fn__sceRemoveIntcHandler_00502e60(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_2_004e2f00(p3fes::EEContext&);
void fn_skyCustomModeIsOk_004e0c10(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_467860_00467860(p3fes::EEContext&);
void fn_sub_468EA0_00468ea0(p3fes::EEContext&);
void fn_sub_469280_00469280(p3fes::EEContext&);
void fn_sub_4692E0_004692e0(p3fes::EEContext&);
void fn_sub_469340_00469340(p3fes::EEContext&);
void fn_sub_4693A0_004693a0(p3fes::EEContext&);
void fn_sub_469400_00469400(p3fes::EEContext&);
void fn_sub_4694B0_004694b0(p3fes::EEContext&);
void fn_sub_469510_00469510(p3fes::EEContext&);
void fn_sub_469590_00469590(p3fes::EEContext&);
void fn_sub_4695F0_004695f0(p3fes::EEContext&);
void fn_sub_469650_00469650(p3fes::EEContext&);
void fn_sub_4696B0_004696b0(p3fes::EEContext&);
void fn_sub_469710_00469710(p3fes::EEContext&);
void fn_sub_469770_00469770(p3fes::EEContext&);
void fn_sub_469840_00469840(p3fes::EEContext&);
void fn_sub_4698E0_004698e0(p3fes::EEContext&);
void fn_sub_469940_00469940(p3fes::EEContext&);
void fn_sub_4699B0_004699b0(p3fes::EEContext&);
void fn_sub_469A10_00469a10(p3fes::EEContext&);
void fn_sub_46BFB0_0046bfb0(p3fes::EEContext&);
void fn_sub_47BD20_0047bd20(p3fes::EEContext&);
void fn_sub_486340_00486340(p3fes::EEContext&);
void fn_sub_4866C0_004866c0(p3fes::EEContext&);
void fn_sub_48D0E0_0048d0e0(p3fes::EEContext&);
void fn_sub_48DAB0_0048dab0(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_491760_00491760(p3fes::EEContext&);
void fn_sub_4917F0_004917f0(p3fes::EEContext&);
void fn_sub_4919B0_004919b0(p3fes::EEContext&);
void fn_sub_492E20_00492e20(p3fes::EEContext&);
void fn_sub_493210_00493210(p3fes::EEContext&);
void fn_sub_493230_00493230(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_493710_00493710(p3fes::EEContext&);
void fn_sub_493B60_00493b60(p3fes::EEContext&);
void fn_sub_494BE0_00494be0(p3fes::EEContext&);
void fn_sub_494CC0_00494cc0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_495340_00495340(p3fes::EEContext&);
void fn_sub_49BCD0_0049bcd0(p3fes::EEContext&);
void fn_sub_49BCE0_0049bce0(p3fes::EEContext&);
void fn_sub_49BD20_0049bd20(p3fes::EEContext&);
void fn_sub_49BD30_0049bd30(p3fes::EEContext&);
void fn_sub_49C240_0049c240(p3fes::EEContext&);
void fn_sub_49CC30_0049cc30(p3fes::EEContext&);
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);
void fn_sub_49E6C0_0049e6c0(p3fes::EEContext&);
void fn_sub_49E780_0049e780(p3fes::EEContext&);
void fn_sub_49E830_0049e830(p3fes::EEContext&);
void fn_sub_49E9F0_0049e9f0(p3fes::EEContext&);
void fn_sub_49ECD0_0049ecd0(p3fes::EEContext&);
void fn_sub_49EE70_0049ee70(p3fes::EEContext&);
void fn_sub_49F040_0049f040(p3fes::EEContext&);
void fn_sub_49F340_0049f340(p3fes::EEContext&);
void fn_sub_4A6CE0_004a6ce0(p3fes::EEContext&);
void fn_sub_4A6EB0_004a6eb0(p3fes::EEContext&);
void fn_sub_4A7620_004a7620(p3fes::EEContext&);
void fn_sub_4A7820_004a7820(p3fes::EEContext&);
void fn_sub_4A7E40_004a7e40(p3fes::EEContext&);
void fn_sub_4A8980_004a8980(p3fes::EEContext&);
void fn_sub_4A90F0_004a90f0(p3fes::EEContext&);
void fn_sub_4A9560_004a9560(p3fes::EEContext&);
void fn_sub_4A96B0_004a96b0(p3fes::EEContext&);
void fn_sub_4A97C0_004a97c0(p3fes::EEContext&);
void fn_sub_4A98A0_004a98a0(p3fes::EEContext&);
void fn_sub_4AAA60_004aaa60(p3fes::EEContext&);
void fn_sub_4AAD50_004aad50(p3fes::EEContext&);
void fn_sub_4AADA0_004aada0(p3fes::EEContext&);
void fn_sub_4AAE00_004aae00(p3fes::EEContext&);
void fn_sub_4AAE60_004aae60(p3fes::EEContext&);
void fn_sub_4AB0E0_004ab0e0(p3fes::EEContext&);
void fn_sub_4AB200_004ab200(p3fes::EEContext&);
void fn_sub_4AB2C0_004ab2c0(p3fes::EEContext&);
void fn_sub_4AB410_004ab410(p3fes::EEContext&);
void fn_sub_4AB6A0_004ab6a0(p3fes::EEContext&);
void fn_sub_4AC240_004ac240(p3fes::EEContext&);
void fn_sub_4AC390_004ac390(p3fes::EEContext&);
void fn_sub_4AC570_004ac570(p3fes::EEContext&);
void fn_sub_4AC5F0_004ac5f0(p3fes::EEContext&);
void fn_sub_4AC710_004ac710(p3fes::EEContext&);
void fn_sub_4AC920_004ac920(p3fes::EEContext&);
void fn_sub_4ACB10_004acb10(p3fes::EEContext&);
void fn_sub_4ACB90_004acb90(p3fes::EEContext&);
void fn_sub_4ACE70_004ace70(p3fes::EEContext&);
void fn_sub_4ACE80_004ace80(p3fes::EEContext&);
void fn_sub_4ADBD0_004adbd0(p3fes::EEContext&);
void fn_sub_4AE060_004ae060(p3fes::EEContext&);
void fn_sub_4AE270_004ae270(p3fes::EEContext&);
void fn_sub_4AE4E0_004ae4e0(p3fes::EEContext&);
void fn_sub_4B24C0_004b24c0(p3fes::EEContext&);
void fn_sub_4B4230_004b4230(p3fes::EEContext&);
void fn_sub_4B43C0_004b43c0(p3fes::EEContext&);
void fn_sub_4BCCD0_004bccd0(p3fes::EEContext&);
void fn_sub_4BD260_004bd260(p3fes::EEContext&);
void fn_sub_4BD4E0_004bd4e0(p3fes::EEContext&);
void fn_sub_4BDA10_004bda10(p3fes::EEContext&);
void fn_sub_4BE930_004be930(p3fes::EEContext&);
void fn_sub_4BEC20_004bec20(p3fes::EEContext&);
void fn_sub_4BF540_004bf540(p3fes::EEContext&);
void fn_sub_4BF560_004bf560(p3fes::EEContext&);
void fn_sub_4BF880_004bf880(p3fes::EEContext&);
void fn_sub_4BF980_004bf980(p3fes::EEContext&);
void fn_sub_4BFEA0_004bfea0(p3fes::EEContext&);
void fn_sub_4C0240_004c0240(p3fes::EEContext&);
void fn_sub_4C0370_004c0370(p3fes::EEContext&);
void fn_sub_4C0550_004c0550(p3fes::EEContext&);
void fn_sub_4C06C0_004c06c0(p3fes::EEContext&);
void fn_sub_4C0E70_004c0e70(p3fes::EEContext&);
void fn_sub_4C0F70_004c0f70(p3fes::EEContext&);
void fn_sub_4C0FC0_004c0fc0(p3fes::EEContext&);
void fn_sub_4C15A0_004c15a0(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C17F0_004c17f0(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C1D50_004c1d50(p3fes::EEContext&);
void fn_sub_4C1F70_004c1f70(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C3960_004c3960(p3fes::EEContext&);
void fn_sub_4C4450_004c4450(p3fes::EEContext&);
void fn_sub_4C4570_004c4570(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C53F0_004c53f0(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4C5A50_004c5a50(p3fes::EEContext&);
void fn_sub_4C5EA0_004c5ea0(p3fes::EEContext&);
void fn_sub_4C5F70_004c5f70(p3fes::EEContext&);
void fn_sub_4C6000_004c6000(p3fes::EEContext&);
void fn_sub_4C64B0_004c64b0(p3fes::EEContext&);
void fn_sub_4C7400_004c7400(p3fes::EEContext&);
void fn_sub_4C7410_004c7410(p3fes::EEContext&);
void fn_sub_4C7460_004c7460(p3fes::EEContext&);
void fn_sub_4C76C0_004c76c0(p3fes::EEContext&);
void fn_sub_4C78A0_004c78a0(p3fes::EEContext&);
void fn_sub_4C7B90_004c7b90(p3fes::EEContext&);
void fn_sub_4C9D20_004c9d20(p3fes::EEContext&);
void fn_sub_4C9D70_004c9d70(p3fes::EEContext&);
void fn_sub_4C9DB0_004c9db0(p3fes::EEContext&);
void fn_sub_4C9F00_004c9f00(p3fes::EEContext&);
void fn_sub_4C9F90_004c9f90(p3fes::EEContext&);
void fn_sub_4CA030_004ca030(p3fes::EEContext&);
void fn_sub_4CA090_004ca090(p3fes::EEContext&);
void fn_sub_4CA190_004ca190(p3fes::EEContext&);
void fn_sub_4CA850_004ca850(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CBE00_004cbe00(p3fes::EEContext&);
void fn_sub_4CBEB0_004cbeb0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CC5C0_004cc5c0(p3fes::EEContext&);
void fn_sub_4CD750_004cd750(p3fes::EEContext&);
void fn_sub_4CD940_004cd940(p3fes::EEContext&);
void fn_sub_4CDB50_004cdb50(p3fes::EEContext&);
void fn_sub_4CDC70_004cdc70(p3fes::EEContext&);
void fn_sub_4CDCE0_004cdce0(p3fes::EEContext&);
void fn_sub_4CDD50_004cdd50(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_4CDF80_004cdf80(p3fes::EEContext&);
void fn_sub_4CE050_004ce050(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_4CEE30_004cee30(p3fes::EEContext&);
void fn_sub_4CF790_004cf790(p3fes::EEContext&);
void fn_sub_4CF9B0_004cf9b0(p3fes::EEContext&);
void fn_sub_4CFFD0_004cffd0(p3fes::EEContext&);
void fn_sub_4D0B60_004d0b60(p3fes::EEContext&);
void fn_sub_4D0B80_004d0b80(p3fes::EEContext&);
void fn_sub_4D0BA0_004d0ba0(p3fes::EEContext&);
void fn_sub_4D0BC0_004d0bc0(p3fes::EEContext&);
void fn_sub_4D0BE0_004d0be0(p3fes::EEContext&);
void fn_sub_4D0C30_004d0c30(p3fes::EEContext&);
void fn_sub_4D0E40_004d0e40(p3fes::EEContext&);
void fn_sub_4D0FD0_004d0fd0(p3fes::EEContext&);
void fn_sub_4D1070_004d1070(p3fes::EEContext&);
void fn_sub_4D1110_004d1110(p3fes::EEContext&);
void fn_sub_4D11D0_004d11d0(p3fes::EEContext&);
void fn_sub_4D11F0_004d11f0(p3fes::EEContext&);
void fn_sub_4D1210_004d1210(p3fes::EEContext&);
void fn_sub_4D1260_004d1260(p3fes::EEContext&);
void fn_sub_4D1840_004d1840(p3fes::EEContext&);
void fn_sub_4D22F0_004d22f0(p3fes::EEContext&);
void fn_sub_4D3300_004d3300(p3fes::EEContext&);
void fn_sub_4D3800_004d3800(p3fes::EEContext&);
void fn_sub_4D3FC0_004d3fc0(p3fes::EEContext&);
void fn_sub_4D41E0_004d41e0(p3fes::EEContext&);
void fn_sub_4D6700_004d6700(p3fes::EEContext&);
void fn_sub_4D8440_004d8440(p3fes::EEContext&);
void fn_sub_4DF140_004df140(p3fes::EEContext&);
void fn_sub_4DF7C0_004df7c0(p3fes::EEContext&);
void fn_sub_4DF870_004df870(p3fes::EEContext&);
void fn_sub_4E00E0_004e00e0(p3fes::EEContext&);
void fn_sub_4E9680_004e9680(p3fes::EEContext&);
void fn_sub_4EAC00_004eac00(p3fes::EEContext&);
void fn_sub_4EB7E0_004eb7e0(p3fes::EEContext&);
void fn_sub_4EBB40_004ebb40(p3fes::EEContext&);
void fn_sub_4F1ED0_004f1ed0(p3fes::EEContext&);
void fn_sub_4F1F80_004f1f80(p3fes::EEContext&);
void fn_sub_4F1FD0_004f1fd0(p3fes::EEContext&);
void fn_sub_4F2710_004f2710(p3fes::EEContext&);
void fn_worldSectorGetWorld_0049a170(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// sub_467860 [matFXMaterialCopy] -- RpMatFX's material copy: the 144-byte effect extension (material + gp 0x7CE738,
//   allocated from the free list 0x95C400) of $a1 copied to $a0 -- the effect type (sub_468EA0), then per 64-byte slot by
//   its type (+32): UV transform 5, dual texture 4 (texture + blend modes), environment map 2, bump map 1 (two textures,
//   their reference counts +84 up); $a0, or 0
// 0x00467860 sub_467860 -- 724 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_467860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00467860
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = a0;
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a1;
    swc1(f20, sp, 0x0);
    lw(v1, gp, -17848);  // 0x7CE738
    v0 = addu(s1, v1);
    lw(s7, v0, 0);
    s0 = fp;
    if (s7 == 0) {
        // 0x00467aa4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004678ac
        charge(ctx, 4);
        v0 = addu(s0, v1);
        lw(s3, v0, 0);
        if (s3 == 0) {
            // 0x00467aac
            charge(ctx, 10);
            v0 = 0x960000;
            v1 = 0x30000;
            lw(a0, v0, -15360);  // 0x95C400
            v0 = 0x960000;
            lw(v0, v0, 392);  // 0x960188
            a1 = v1 | 0x120;
            jalr(ctx, 0x467AC0u, v0.u());
            s3 = v0;
            if (s3 == 0) {
                // 0x00467af4
                charge(ctx, 2);
                s3 = 0;
                backedge(ctx);
            } else {
                // 0x00467ad4
                charge(ctx, 8);
                a0 = s3;
                a1 = 0;
                a2 = 144;
                jal(ctx, 0x467ADCu, gen::fn_memset_00521408);
                lw(v0, gp, -17848);  // 0x7CE738
                v0 = addu(s0, v0);
                sw(s3, v0, 0);
                backedge(ctx);
            }
        }
        // 0x004678bc
        charge(ctx, 2);
        if (s3 == 0) {
            // 0x00467afc
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004678c4
            charge(ctx, 4);
            lw(a1, s7, 128);
            a0 = s0;
            jal(ctx, 0x4678C8u, gen::fn_sub_468EA0_00468ea0);
            s5 = 0;
            for (;;) {
                // 0x004678d4
                charge(ctx, 7);
                v1 = s5 & 0xFF;
                v0 = 5;
                a0 = sll(v1, 6);
                s4 = addu(s7, a0);
                lw(v1, s4, 32);
                if (v1 == v0) {
                    // 0x00467a60
                    charge(ctx, 10);
                    a0 = s1;
                    a1 = addiu(sp, 0xC0);
                    a2 = addiu(sp, 0xB0);
                    jal(ctx, 0x467A68u, gen::fn_sub_469A10_00469a10);
                    lw(a1, sp, 0xC0);
                    a0 = s0;
                    lw(a2, sp, 0xB0);
                    s1 = v0;
                    jal(ctx, 0x467A7Cu, gen::fn_sub_4699B0_004699b0);
                    s0 = v0;
                } else {
                    // 0x004678f0
                    charge(ctx, 3);
                    v0 = 4;
                    if (v1 == v0) {
                        // 0x00467a18
                        charge(ctx, 9);
                        a0 = s1;
                        jal(ctx, 0x467A18u, gen::fn_sub_4698E0_004698e0);
                        s2 = v0;
                        a0 = s1;
                        a1 = addiu(sp, 0xCC);
                        a2 = addiu(sp, 0xC8);
                        jal(ctx, 0x467A2Cu, gen::fn_sub_469940_00469940);
                        if (s2 != 0) {
                            // 0x00467a3c
                            charge(ctx, 3);
                            a1 = s2;
                            a0 = s0;
                            jal(ctx, 0x467A40u, gen::fn_sub_469770_00469770);
                        }
                        // 0x00467a48
                        charge(ctx, 6);
                        lw(a1, sp, 0xCC);
                        lw(a2, sp, 0xC8);
                        a0 = s0;
                        jal(ctx, 0x467A50u, gen::fn_sub_469840_00469840);
                    } else {
                        // 0x004678fc
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x004679a8
                            charge(ctx, 13);
                            a0 = s1;
                            jal(ctx, 0x4679A8u, gen::fn_sub_4695F0_004695f0);
                            s4 = v0;
                            a0 = s1;
                            jal(ctx, 0x4679B4u, gen::fn_sub_469650_00469650);
                            s2 = v0;
                            a0 = s1;
                            jal(ctx, 0x4679C0u, gen::fn_sub_469710_00469710);
                            mov_s(f20, f0);
                            a0 = s1;
                            jal(ctx, 0x4679CCu, gen::fn_sub_4696B0_004696b0);
                            s6 = v0;
                            if (s4 != 0) {
                                // 0x004679dc
                                charge(ctx, 3);
                                a1 = s4;
                                a0 = s0;
                                jal(ctx, 0x4679E0u, gen::fn_sub_469400_00469400);
                            }
                            // 0x004679e8
                            charge(ctx, 11);
                            a1 = s2;
                            a0 = s0;
                            jal(ctx, 0x4679ECu, gen::fn_sub_4694B0_004694b0);
                            a1 = s6;
                            a0 = s0;
                            jal(ctx, 0x4679F8u, gen::fn_sub_469510_00469510);
                            mov_s(f12, f20);
                            a0 = s0;
                            jal(ctx, 0x467A04u, gen::fn_sub_469590_00469590);
                        } else {
                            // 0x00467908
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x00467928
                                charge(ctx, 20);
                                s2 = addu(s3, a0);
                                a0 = s1;
                                jal(ctx, 0x46792Cu, gen::fn_sub_469340_00469340);
                                s6 = v0;
                                a0 = s1;
                                jal(ctx, 0x467938u, gen::fn_sub_4693A0_004693a0);
                                mov_s(f20, f0);
                                a1 = s6;
                                a0 = s0;
                                jal(ctx, 0x467948u, gen::fn_sub_469280_00469280);
                                mov_s(f12, f20);
                                a0 = s0;
                                jal(ctx, 0x467954u, gen::fn_sub_4692E0_004692e0);
                                lw(v0, s4, 4);
                                sw(v0, s2, 4);
                                lw(v0, s4, 8);
                                sw(v0, s2, 8);
                                lw(v1, s2, 4);
                                if (v1 != 0) {
                                    // 0x00467978
                                    charge(ctx, 4);
                                    lw(v0, v1, 84);
                                    v0 = addiu(v0, 1);
                                    sw(v0, v1, 84);
                                }
                                // 0x00467988
                                charge(ctx, 3);
                                lw(v1, s2, 8);
                                if (v1 != 0) {
                                    // 0x00467994
                                    charge(ctx, 4);
                                    lw(v0, v1, 84);
                                    v0 = addiu(v0, 1);
                                    sw(v0, v1, 84);
                                }
                            } else {
                                // 0x00467914
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    // 0x0046791c
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
                // 0x00467a88
                charge(ctx, 5);
                v0 = addiu(s5, 1);
                s5 = v0 & 0xFF;
                v0 = slti(s5, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00467a9c
            charge(ctx, 2);
            v0 = fp;
        }
    }
    // 0x00467b00 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0xA0);
    lwc1(f20, sp, 0x0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xD0);
}

// sub_46BFB0 [rt2dFontRenderString] -- draws a string with an Rt2d font: per character its glyph (the map at +36 below
//   128, the table +292 / +296 / +300 above), the vertices built in the font's packet, flushed through the font pipeline
//   (RxPipelineExecute 0x95F048) at every change of texture (render states 9 / 1); the pen x advanced (*$a2); the font,
//   or 0
// 0x0046BFB0 sub_46BFB0 -- 896 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_46BFB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0046bfb0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a0;
    sq(s3, sp, 0x40);
    s4 = a1;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a3;
    swc1(f21, sp, 0x4);
    sw(a2, sp, 0xC8);
    swc1(f20, sp, 0x0);
    mov_s(f21, f12);
    if (s5 != 0) {
        // 0x0046bffc
        charge(ctx, 2);
        if (s4 == 0) {
            goto L_0046c2f4;
        }
        // 0x0046c004
        charge(ctx, 7);
        link(ctx, 0x46C004u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 308);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        sq(v0, sp, 0xB0);
        lw(v0, s5, 16);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x0046c030
            charge(ctx, 3);
            fp = 0x1;
            s0 = 0;
            s6 = 0;
        } else {
            // 0x0046c020
            charge(ctx, 4);
            fp = 0x2;
            s0 = 255;
            s6 = 1;
        }
        // 0x0046c03c
        charge(ctx, 50);
        jal(ctx, 0x46C03Cu, gen::fn_sub_4AAA60_004aaa60);
        lw(v0, sp, 0xC8);
        lwc1(f13, v0, 4);
        link(ctx, 0x46C04Cu);  // $ra first: the delay slot below depends on it
        lwc1(f12, v0, 0);
        call(ctx, gen::fn_sub_4AAE00_004aae00);
        mov_s(f12, f21);
        mov_s(f13, f21);
        jal(ctx, 0x46C058u, gen::fn_sub_4AADA0_004aada0);
        lwc1(f0, s5, 8);
        mtc1(zero, f12);
        neg_s(f13, f0);
        jal(ctx, 0x46C068u, gen::fn_sub_4AAE00_004aae00);
        jal(ctx, 0x46C070u, gen::fn_sub_4AAE60_004aae60);
        v0 = 0x3F800000;
        a0 = s5;
        mtc1(v0, f12);
        a1 = s4;
        jal(ctx, 0x46C084u, gen::fn_sub_4A9560_004a9560);
        v0 = 0x960000;
        sw(zero, v0, -4192);  // 0x95EFA0
        mtc1(zero, f20);
        v0 = 0x960000;
        sw(s1, v0, -4216);  // 0x95EF88
        v0 = 0x960000;
        swc1(f0, v0, -4188);  // 0x95EFA4
        v0 = 0x960000;
        link(ctx, 0x46C0ACu);  // $ra first: the delay slot below depends on it
        sw(s5, v0, -4212);
        call(ctx, gen::fn_sub_4F2710_004f2710);
        v1 = 0x960000;
        lbu(a2, s4, 0);
        lw(t1, v1, -4764);  // 0x95ED64
        t0 = 20;
        s7 = s0 & 0xFF;
        s1 = v0;
        a1 = 0x960000;
        a0 = 0x960000;
        s3 = 0;
        v1 = addu(s4, s6);
        lbu(a3, v1, 0);
        sw(t1, v0, 4);
        v1 = 0;
        sw(t0, v0, 8);
        v0 = s7 & a3;
        sw(zero, a1, -4184);  // 0x95EFA8
        v0 = sll(v0, 8);
        a1 = a2 | v0;
        sw(s4, a0, -4204);  // 0x95EF94
        if (i64(a1) > 0) {
            // 0x0046c104
            charge(ctx, 2);
            s0 = 0x960000;
            s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
            for (;;) {
                // 0x0046c10c
                charge(ctx, 3);
                v0 = slti(a1, 128);
                if (v0 != 0) {
                    // 0x0046c150
                    charge(ctx, 4);
                    v0 = sll(a1, 1);
                    v0 = addu(s5, v0);
                    lh(v0, v0, 36);
                } else {
                    // 0x0046c118
                    charge(ctx, 4);
                    lw(v0, s5, 292);
                    a0 = subu(a1, v0);
                    if (i64(a0) >= 0) {
                        // 0x0046c128
                        charge(ctx, 4);
                        lw(v0, s5, 296);
                        at = slt(a0, v0);
                        if (at == 0) {
                            goto L_0046c2c8;
                        }
                        // 0x0046c138
                        charge(ctx, 5);
                        lw(v0, s5, 300);
                        a0 = sll(a0, 1);
                        v0 = addu(v0, a0);
                        lh(v0, v0, 0);
                        goto L_0046c160;
                    }
                L_0046c2c8:
                    charge(ctx, 2);
                    v0 = si(-1);
                    backedge(ctx);
                }
            L_0046c160:
                charge(ctx, 2);
                if (i64(v0) >= 0) {
                    // 0x0046c168
                    charge(ctx, 6);
                    a0 = sll(v0, 5);
                    lq(v0, sp, 0xB0);
                    s2 = addu(v0, a0);
                    lw(v0, s2, 4);
                    if (v0 != v1) {
                        // 0x0046c180
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x0046c188
                            charge(ctx, 20);
                            v0 = 0x2AAA0000;
                            v0 = v0 | 0xAAAB;
                            mult(zero, v0, s3);
                            a3 = srl(s3, 31);
                            mfhi(a2);
                            v1 = 0x960000;
                            sw(s3, v1, -4156);  // 0x95EFC4
                            a0 = 0x960000;
                            v0 = 0x960000;
                            a1 = addiu(s1, 12);
                            v1 = sra(a2, 1);
                            v1 = addu(v1, a3);
                            sw(v1, a0, -4152);  // 0x95EFC8
                            sh(s3, s1, 0);
                            lw(a0, v0, -4024);  // 0x95F048
                            a2 = 0;
                            jal(ctx, 0x46C1C8u, gen::fn_RxPipelineExecute_004f2e70);
                            if (v0 == 0) {
                                break;
                            }
                            // 0x0046c1d8
                            charge(ctx, 8);
                            v0 = 0x960000;
                            v1 = dsll32(s4, 0);
                            swc1(f20, v0, -4184);  // 0x95EFA8
                            v1 = dsra32(v1, 0);
                            v0 = 0x960000;
                            s3 = 0;
                            sw(v1, v0, -4204);  // 0x95EF94
                            goto L_0046c1f8;
                        }
                    L_0046c1f8:
                        charge(ctx, 12);
                        lw(v1, s2, 4);
                        lw(v0, s0, 0);
                        lbu(a1, v1, 80);
                        a0 = 9;
                        jalr(ctx, 0x46C204u, v0.u());
                        lw(v1, s2, 4);
                        lw(v0, s0, 0);
                        lw(a1, v1, 0);
                        a0 = 1;
                        jalr(ctx, 0x46C218u, v0.u());
                        lw(v1, s2, 4);
                    }
                    // 0x0046c228
                    charge(ctx, 4);
                    lwc1(f1, s2, 0);
                    lwc1(f0, s5, 12);
                    add_s(f0, f1, f0);
                    add_s(f20, f20, f0);
                }
                // 0x0046c238
                charge(ctx, 11);
                v0 = dsll32(s4, 0);
                v0 = dsra32(v0, 0);
                s4 = addu(v0, fp);
                a0 = addu(s6, s4);
                lbu(v0, s4, 0);
                lbu(a0, a0, 0);
                a0 = s7 & a0;
                a0 = sll(a0, 8);
                a1 = v0 | a0;
                s3 = addiu(s3, 1);
                if (i64(a1) <= 0) {
                    goto L_0046c264_20;
                }
                backedge(ctx);
            }
            // 0x0046c2d0
            charge(ctx, 2);
            v0 = 0;
            // 0x0046c2f8 (the shared epilogue, written out on this path)
            charge(ctx, 14);
            ld(ra, sp, 0xA0);
            lwc1(f21, sp, 0x4);
            lq(fp, sp, 0x90);
            lwc1(f20, sp, 0x0);
            lq(s7, sp, 0x80);
            lq(s6, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            sp = addiu(sp, 0xD0);
            return;
        }
    L_0046c268:
        charge(ctx, 2);
        if (i64(s3) > 0) {
            // 0x0046c270
            charge(ctx, 20);
            v0 = 0x2AAA0000;
            v0 = v0 | 0xAAAB;
            mult(zero, v0, s3);
            a3 = srl(s3, 31);
            mfhi(a2);
            v1 = 0x960000;
            sw(s3, v1, -4156);  // 0x95EFC4
            a0 = 0x960000;
            v0 = 0x960000;
            a1 = addiu(s1, 12);
            v1 = sra(a2, 1);
            v1 = addu(v1, a3);
            sw(v1, a0, -4152);  // 0x95EFC8
            sh(s3, s1, 0);
            lw(a0, v0, -4024);  // 0x95F048
            a2 = 0;
            jal(ctx, 0x46C2B0u, gen::fn_RxPipelineExecute_004f2e70);
            if (v0 != 0) {
                goto L_0046c2d8;
            }
            // 0x0046c2c0
            charge(ctx, 2);
            v0 = 0;
            // 0x0046c2f8 (the shared epilogue, written out on this path)
            charge(ctx, 14);
            ld(ra, sp, 0xA0);
            lwc1(f21, sp, 0x4);
            lq(fp, sp, 0x90);
            lwc1(f20, sp, 0x0);
            lq(s7, sp, 0x80);
            lq(s6, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            sp = addiu(sp, 0xD0);
            return;
        }
    L_0046c2d8:
        charge(ctx, 7);
        lw(v0, sp, 0xC8);
        mtc1(zero, f0);
        lwc1(f1, v0, 0);
        adda_s(f0, f1);
        madd_s(f0, f20, f21);
        link(ctx, 0x46C2ECu);  // $ra first: the delay slot below depends on it
        swc1(f0, v0, 0);
        call(ctx, gen::fn_sub_4AAD50_004aad50);
        goto L_0046c2f4;
    }
L_0046c2f4:
    charge(ctx, 1);
    v0 = s5;
    // 0x0046c2f8 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0xA0);
    lwc1(f21, sp, 0x4);
    lq(fp, sp, 0x90);
    lwc1(f20, sp, 0x0);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xD0);
    return;
L_0046c264_20:
    charge(ctx, 1);
    goto L_0046c268;
}

// sub_47BD20 [ptankInstGeometryCreate] -- builds a PTank atomic's empty geometry (the instancing path): a geometry, a
//   material set and released, the atomic's callbacks +36..+56 cleared; 1 / 0
// 0x0047BD20 sub_47BD20 -- 228 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47BD20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0047bd20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = 0;
    sd(ra, sp, 0x30);
    a2 = 0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x47BD40u, gen::fn_sub_493710_00493710);
    s2 = v0;
    if (s2 == 0) {
        // 0x0047bd84
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0047bd54
        charge(ctx, 10);
        lw(v1, s2, 92);
        v0 = 0x3F800000;
        a0 = s2;
        sw(zero, v1, 4);
        sw(zero, v1, 8);
        sw(zero, v1, 12);
        link(ctx, 0x47BD6Cu);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 16);
        call(ctx, gen::fn_sub_4933D0_004933d0);
        if (v0 != 0) {
            // 0x0047bd8c
            charge(ctx, 24);
            a0 = s0;
            a1 = s2;
            a2 = 0;
            jal(ctx, 0x47BD94u, gen::fn_sub_4919B0_004919b0);
            a0 = s2;
            jal(ctx, 0x47BD9Cu, gen::fn_sub_493B60_00493b60);
            jal(ctx, 0x47BDA4u, gen::fn_sub_494BE0_00494be0);
            s1 = v0;
            a0 = addiu(s2, 32);
            a1 = s1;
            jal(ctx, 0x47BDB4u, gen::fn_sub_495340_00495340);
            a0 = s1;
            jal(ctx, 0x47BDBCu, gen::fn_sub_494CC0_00494cc0);
            lw(v1, gp, -17792);  // 0x7CE770
            v0 = 1;
            v1 = addu(s0, v1);
            lw(v1, v1, 0);
            sw(zero, v1, 36);
            sw(zero, v1, 40);
            sw(zero, v1, 44);
            sw(zero, v1, 48);
            sw(zero, v1, 52);
            sw(zero, v1, 56);
        } else {
            // 0x0047bd7c
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0047bdec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_486340 [ptankQuadGeometryCreate] -- builds a PTank atomic's generic geometry: 4 vertices and 2 triangles per
//   particle ($a1), positions / UVs / pre-lit colours / normals initialised, the bounding sphere, the material, then
//   sub_4866C0; 1
// 0x00486340 sub_486340 -- 888 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_486340(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00486340
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    v1 = a2 & 0x10;
    sd(ra, sp, 0x90);
    v0 = 16;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sw(a0, sp, 0xDC);
    sq(s0, sp, 0x0);
    a0 = 6;
    sw(a1, sp, 0xD8);
    if (v1 != v0) {
        // 0x0048638c
        charge(ctx, 1);
        v1 = a0 | 0x8;
    } else {
        // 0x00486384
        charge(ctx, 2);
        v1 = a0 | 0x70;
    }
    // 0x00486390
    charge(ctx, 5);
    v0 = 0x40000;
    v0 = v0 | 0x42;
    v0 = a2 & v0;
    if (v0 != 0) {
        // 0x004863a4
        charge(ctx, 1);
        v1 = v1 | 0x8;
    }
    // 0x004863a8
    charge(ctx, 28);
    lw(v0, sp, 0xD8);
    a2 = v1;
    a0 = sll(v0, 2);
    a1 = sll(v0, 1);
    jal(ctx, 0x4863B4u, gen::fn_sub_493710_00493710);
    s5 = v0;
    jal(ctx, 0x4863BCu, gen::fn_sub_494BE0_00494be0);
    v1 = 0x3E990000;
    sw(v0, sp, 0xD4);
    a0 = v1 | 0x999A;
    fp = 0;
    v1 = 0x3F800000;
    sw(a0, v0, 12);
    sw(v1, v0, 16);
    sw(v1, v0, 20);
    lw(v0, s5, 92);
    lw(s1, s5, 52);
    lw(s0, s5, 48);
    lw(s2, s5, 44);
    sw(a0, sp, 0xF0);
    sw(v1, sp, 0xF8);
    lw(s4, v0, 20);
    lw(s3, v0, 24);
    sw(v0, sp, 0xC0);
    lw(v0, sp, 0xD8);
    at = slt(0, v0);
    sw(v1, sp, 0xF4);
    if (at != 0) {
        // 0x00486418
        charge(ctx, 6);
        v0 = 1;
        s6 = 0;
        sw(v0, sp, 0xB0);
        s7 = 2;
        v0 = 3;
        sw(v0, sp, 0xA0);
        for (;;) {
            // 0x00486430
            charge(ctx, 6);
            sw(zero, s4, 0);
            sw(zero, s4, 4);
            sw(zero, s4, 8);
            sw(zero, s1, 0);
            sw(zero, s1, 4);
            if (s0 != 0) {
                // 0x00486448
                charge(ctx, 6);
                sb(zero, s0, 0);
                v0 = 255;
                sb(zero, s0, 1);
                sb(zero, s0, 2);
                sb(v0, s0, 3);
                s0 = addiu(s0, 4);
            }
            // 0x00486460
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00486468
                charge(ctx, 6);
                v0 = 0x3F800000;
                sw(v0, s3, 0);
                sw(zero, s3, 4);
                sw(zero, s3, 8);
                s3 = addiu(s3, 12);
            }
            // 0x00486480
            charge(ctx, 7);
            sw(zero, s4, 12);
            sw(zero, s4, 16);
            v0 = 0x3F800000;
            sw(zero, s4, 20);
            sw(zero, s1, 8);
            sw(v0, s1, 12);
            if (s0 != 0) {
                // 0x0048649c
                charge(ctx, 7);
                sb(zero, s0, 0);
                v0 = 255;
                sb(zero, s0, 1);
                sb(zero, s0, 2);
                sb(v0, s0, 3);
                s0 = addiu(s0, 4);
            }
            // 0x004864b8
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x004864c0
                charge(ctx, 6);
                v0 = 0x3F800000;
                sw(v0, s3, 0);
                sw(zero, s3, 4);
                sw(zero, s3, 8);
                s3 = addiu(s3, 12);
            }
            // 0x004864d8
            charge(ctx, 7);
            sw(zero, s4, 24);
            sw(zero, s4, 28);
            v0 = 0x3F800000;
            sw(zero, s4, 32);
            sw(v0, s1, 16);
            sw(v0, s1, 20);
            if (s0 != 0) {
                // 0x004864f4
                charge(ctx, 7);
                sb(zero, s0, 0);
                v0 = 255;
                sb(zero, s0, 1);
                sb(zero, s0, 2);
                sb(v0, s0, 3);
                s0 = addiu(s0, 4);
            }
            // 0x00486510
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00486518
                charge(ctx, 6);
                v0 = 0x3F800000;
                sw(v0, s3, 0);
                sw(zero, s3, 4);
                sw(zero, s3, 8);
                s3 = addiu(s3, 12);
            }
            // 0x00486530
            charge(ctx, 9);
            sw(zero, s4, 36);
            sw(zero, s4, 40);
            v0 = 0x3F800000;
            sw(zero, s4, 44);
            sw(v0, s1, 24);
            s4 = addiu(s4, 48);
            sw(zero, s1, 28);
            s1 = addiu(s1, 32);
            if (s0 != 0) {
                // 0x00486554
                charge(ctx, 7);
                sb(zero, s0, 0);
                v0 = 255;
                sb(zero, s0, 1);
                sb(zero, s0, 2);
                sb(v0, s0, 3);
                s0 = addiu(s0, 4);
            }
            // 0x00486570
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00486578
                charge(ctx, 6);
                v0 = 0x3F800000;
                sw(v0, s3, 0);
                sw(zero, s3, 4);
                sw(zero, s3, 8);
                s3 = addiu(s3, 12);
            }
            // 0x00486590
            charge(ctx, 36);
            lhu(v0, sp, 0xB0);
            a2 = s7 & 0xFFFF;
            t0 = s6 & 0xFFFF;
            a0 = s5;
            a1 = s2;
            a3 = v0;
            jal(ctx, 0x4865A4u, gen::fn_sub_493210_00493210);
            lw(a2, sp, 0xD4);
            a1 = s2;
            a0 = s5;
            s2 = addiu(s2, 8);
            jal(ctx, 0x4865B8u, gen::fn_sub_493230_00493230);
            lhu(v0, sp, 0xA0);
            a3 = s7 & 0xFFFF;
            t0 = s6 & 0xFFFF;
            a0 = s5;
            a1 = s2;
            a2 = v0;
            jal(ctx, 0x4865D4u, gen::fn_sub_493210_00493210);
            lw(a2, sp, 0xD4);
            a1 = s2;
            a0 = s5;
            s2 = addiu(s2, 8);
            jal(ctx, 0x4865E8u, gen::fn_sub_493230_00493230);
            lw(v0, sp, 0xB0);
            fp = addiu(fp, 0x1);
            s6 = addiu(s6, 4);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0xB0);
            lw(v0, sp, 0xA0);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0xA0);
            lw(v0, sp, 0xD8);
            v0 = slt(fp, v0);
            s7 = addiu(s7, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00486620
    charge(ctx, 38);
    lw(a0, sp, 0xC0);
    a1 = addiu(sp, 0xE0);
    jal(ctx, 0x486624u, gen::fn_sub_492E20_00492e20);
    lwc1(f2, sp, 0xE0);
    lw(v0, sp, 0xC0);
    lwc1(f1, sp, 0xE4);
    v1 = 0x3F800000;
    lwc1(f0, sp, 0xE8);
    sw(v1, sp, 0xEC);
    a0 = s5;
    swc1(f2, v0, 4);
    swc1(f1, v0, 8);
    swc1(f0, v0, 12);
    link(ctx, 0x486654u);  // $ra first: the delay slot below depends on it
    sw(v1, v0, 16);
    call(ctx, gen::fn_sub_4933D0_004933d0);
    lw(a0, sp, 0xDC);
    a1 = s5;
    a2 = 0;
    jal(ctx, 0x486664u, gen::fn_sub_4919B0_004919b0);
    a0 = s5;
    jal(ctx, 0x48666Cu, gen::fn_sub_493B60_00493b60);
    link(ctx, 0x486674u);  // $ra first: the delay slot below depends on it
    lw(a0, sp, 0xD4);
    call(ctx, gen::fn_sub_494CC0_00494cc0);
    link(ctx, 0x48667Cu);  // $ra first: the delay slot below depends on it
    lw(a0, sp, 0xDC);
    call(ctx, gen::fn_sub_4866C0_004866c0);
    ld(ra, sp, 0x90);
    v0 = 1;
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// sub_48D0E0 [splineStreamRead] -- reads a spline chunk's body: a 40-byte header, the control points (12 bytes each,
//   RwMalloc'd buffer), the spline built (sub_48DAB0) with the header's 32 bytes copied to +24 and type byte 12; the
//   spline, or 0 (error 0x80000013 on a failed allocation)
// 0x0048D0E0 sub_48D0E0 -- 284 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48D0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048d0e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    a2 = 40;
    sd(ra, sp, 0x40);
    a1 = addiu(sp, 0x50);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    link(ctx, 0x48D100u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C5250_004c5250);
    v1 = 40;
    if (v0 == v1) {
        // 0x0048d11c
        charge(ctx, 12);
        lw(s0, sp, 0x70);
        v0 = 0x10000;
        a1 = v0 | 0x102;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        s3 = sll(v1, 2);
        a0 = s3;
        jalr(ctx, 0x48D13Cu, v0.u());
        s1 = v0;
        if (v0 == 0) {
            // 0x0048d16c
            charge(ctx, 11);
            v0 = 258;
            a1 = s3;
            sw(v0, sp, 0x78);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x48D17Cu, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x7C);
            a0 = addiu(sp, 0x78);
            jal(ctx, 0x48D188u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x0048d14c
            charge(ctx, 6);
            a0 = s2;
            a2 = s3;
            a1 = s1;
            jal(ctx, 0x48D154u, gen::fn_sub_4C18B0_004c18b0);
            if (v0 != 0) {
                // 0x0048d198
                charge(ctx, 18);
                lw(a1, sp, 0x74);
                a0 = s0;
                a2 = s1;
                jal(ctx, 0x48D1A0u, gen::fn_sub_48DAB0_0048dab0);
                s0 = v0;
                a1 = addiu(sp, 0x50);
                v0 = 0x960000;
                a0 = addiu(s0, 24);
                lw(v0, v0, 320);  // 0x960140
                a2 = 32;
                jalr(ctx, 0x48D1BCu, v0.u());
                v0 = 12;
                sb(v0, s0, 0);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                a0 = s1;
                jalr(ctx, 0x48D1D4u, v0.u());
                v0 = s0;
            } else {
                // 0x0048d164
                charge(ctx, 2);
                v0 = 0;
            }
        }
    } else {
        // 0x0048d114
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0048d1e0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_49BCD0 [geometryNativeWriteCB] -- the geometry native-data plugin's stream write callback (a tail call into
//   sub_49E830 with the object)
// 0x0049BCD0 sub_49BCD0 -- 8 bytes; leaf frame (no stack)
void sub_49BCD0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6};
    // 0x0049bcd0
    enter(ctx, 2);  // entry check point + this block's cycles
    a1 = a2;
    gen::fn_sub_49E830_0049e830(ctx);  // tail call
}

// sub_49BCE0 [geometryNativeReadCB] -- the geometry native-data plugin's stream read callback: sub_49E9F0; the stream,
//   or 0
// 0x0049BCE0 sub_49BCE0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BCE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bce0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = a2;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x49BCF0u, gen::fn_sub_49E9F0_0049e9f0);
    if (v0 == 0) s0 = 0;
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_49BD20 [sectorNativeWriteCB] -- the world-sector native-data plugin's stream write callback (a tail call into
//   sub_49EE70)
// 0x0049BD20 sub_49BD20 -- 8 bytes; leaf frame (no stack)
void sub_49BD20(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6};
    // 0x0049bd20
    enter(ctx, 2);  // entry check point + this block's cycles
    a1 = a2;
    gen::fn_sub_49EE70_0049ee70(ctx);  // tail call
}

// sub_49BD30 [sectorNativeReadCB] -- the world-sector native-data plugin's stream read callback: sub_49F040; the
//   stream, or 0
// 0x0049BD30 sub_49BD30 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bd30
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = a2;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x49BD40u, gen::fn_sub_49F040_0049f040);
    if (v0 == 0) s0 = 0;
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_49C240 [RpWorldAddClump] -- adds a clump to a world: linked into the world's clump list (+44), the count (+36)
//   up, the clump's world link set, each atomic / light / camera added (callbacks sub_49BBC0 / sub_49BBF0 / sub_49BC20),
//   the frame re-synced (sub_4C2D20 / sub_4CB270), the clump's frame counter stamp; the world
// 0x0049C240 sub_49C240 -- 236 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49C240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c240
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    v0 = addiu(s3, 44);
    lw(t0, gp, -17536);  // 0x7CE870
    v1 = addiu(s2, 32);
    lw(s1, a1, 4);
    a2 = s3;
    lw(a3, a0, 44);
    s0 = addu(s2, t0);
    sw(a3, a1, 32);
    sw(v0, a1, 36);
    lw(v0, a0, 44);
    a1 = 0x4A0000;
    a1 = addiu(a1, -17472);  // &sub_49BBC0
    sw(v1, v0, 4);
    sw(v1, a0, 44);
    lw(v0, a0, 36);
    v0 = addiu(v0, 1);
    sw(v0, a0, 36);
    a0 = s2;
    link(ctx, 0x49C2A8u);  // $ra first: the delay slot below depends on it
    sw(s3, s0, 0);
    call(ctx, gen::fn_sub_4916D0_004916d0);
    a1 = 0x4A0000;
    a0 = s2;
    a1 = addiu(a1, -17424);  // &sub_49BBF0
    a2 = s3;
    jal(ctx, 0x49C2BCu, gen::fn_sub_4917F0_004917f0);
    a1 = 0x4A0000;
    a0 = s2;
    a1 = addiu(a1, -17376);  // &sub_49BC20
    a2 = s3;
    jal(ctx, 0x49C2D0u, gen::fn_sub_491760_00491760);
    if (s1 != 0) {
        // 0x0049c2e0
        charge(ctx, 5);
        a0 = addiu(s1, 16);
        a1 = 0;
        jal(ctx, 0x49C2E4u, gen::fn_sub_4C2D20_004c2d20);
        a0 = s1;
        jal(ctx, 0x49C2ECu, gen::fn_sub_4CB270_004cb270);
    }
    // 0x0049c2f4 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a0, gp, -17528);  // 0x7CE878
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = s3;
    v1 = addu(v1, a0);
    lw(v1, v1, 8);
    sw(v1, s0, 4);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_49E830 [geometryNativeStreamWrite] -- writes a native geometry's PS2 instance data (geometry + gp 0x7CE890; only
//   for native geometries, flag 0x01000000): each block released from the DMA chain (sub_49CC30), the chunk header (type
//   1, the size from sub_49ECD0, version 0x37002), the platform id 4 (0x7CDC00), per block its size, the relocation word
//   (sub_49E6C0 makes its pointers offsets), the data, then the pointers restored (sub_49E780) and the data cache written
//   back (SyncDCache); the stream, or 0
// 0x0049E830 sub_49E830 -- 448 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49E830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049e830
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    lw(v1, a1, 8);
    sd(ra, sp, 0x60);
    v0 = 0x1000000;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    v0 = v1 & v0;
    sq(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x0049e868
        charge(ctx, 7);
        lw(v0, gp, -17504);  // 0x7CE890
        v0 = addu(s3, v0);
        lw(s2, v0, 0);
        lw(s5, s2, 0);
        at = sltu(0, s5);
        s1 = 0;
        if (at != 0) {
            // 0x0049e884
            charge(ctx, 1);
            s0 = s2;
            for (;;) {
                // 0x0049e888
                charge(ctx, 7);
                link(ctx, 0x49E888u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 4);
                call(ctx, gen::fn_sub_49CC30_0049cc30);
                s1 = addiu(s1, 1);
                s0 = addiu(s0, 4);
                v0 = sltu(s1, s5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049e8a4
            charge(ctx, 1);
        }
        // 0x0049e8a8
        charge(ctx, 11);
        a0 = s3;
        jal(ctx, 0x49E8A8u, gen::fn_sub_49ECD0_0049ecd0);
        a2 = addiu(v0, -12);
        a0 = s4;
        v0 = 0x30000;
        a1 = 1;
        a3 = v0 | 0x7002;
        t0 = 55;
        jal(ctx, 0x49E8C4u, gen::fn_sub_4C15A0_004c15a0);
        if (v0 != 0) {
            // 0x0049e8dc
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(gp, -20720);  // &0x7CDC00
            a2 = 4;
            jal(ctx, 0x49E8E4u, gen::fn_sub_4C53F0_004c53f0);
            if (v0 != 0) {
                // 0x0049e8f4
                charge(ctx, 4);
                lw(v0, s2, 0);
                at = sltu(0, v0);
                s1 = 0;
                if (at == 0) {
                    goto L_0049e9b0;
                }
                // 0x0049e904
                charge(ctx, 1);
                s3 = s2;
                for (;;) {
                    // 0x0049e908
                    charge(ctx, 13);
                    lw(s0, s3, 4);
                    a0 = s4;
                    a1 = addiu(sp, 0x7C);
                    a2 = 4;
                    lw(v1, s0, 32);
                    s5 = addiu(s0, 24);
                    lw(v0, s0, 8);
                    v1 = subu(v1, s0);
                    v0 = subu(v0, v1);
                    link(ctx, 0x49E92Cu);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x7C);
                    call(ctx, gen::fn_sub_4C53F0_004c53f0);
                    if (v0 == 0) {
                        goto L_0049e93c_11;
                    }
                    // 0x0049e944
                    charge(ctx, 9);
                    a0 = s5;
                    jal(ctx, 0x49E944u, gen::fn_sub_49E6C0_0049e6c0);
                    sw(v0, sp, 0x78);
                    a0 = s4;
                    a1 = addiu(sp, 0x78);
                    a2 = 4;
                    jal(ctx, 0x49E958u, gen::fn_sub_4C53F0_004c53f0);
                    if (v0 == 0) {
                        goto L_0049e9c0;
                    }
                    // 0x0049e968
                    charge(ctx, 6);
                    lw(a1, s5, 8);
                    lw(a2, sp, 0x7C);
                    a0 = s4;
                    jal(ctx, 0x49E970u, gen::fn_sub_4C53F0_004c53f0);
                    if (v0 == 0) {
                        goto L_0049e9c8;
                    }
                    // 0x0049e980
                    charge(ctx, 12);
                    a0 = s5;
                    jal(ctx, 0x49E980u, gen::fn_sub_49E780_0049e780);
                    lw(v0, s0, 8);
                    a0 = s0;
                    v0 = addu(s0, v0);
                    a1 = addiu(v0, 24);
                    jal(ctx, 0x49E994u, gen::fn_SyncDCache_00503a58);
                    lw(v0, s2, 0);
                    s1 = addiu(s1, 1);
                    v0 = sltu(s1, v0);
                    s3 = addiu(s3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_0049e9b0;
            }
            // 0x0049e9b8
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x0049e8d4
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x0049e9cc (the shared epilogue, written out on this path)
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
L_0049e9b0:
    charge(ctx, 2);
    v0 = s4;
    // 0x0049e9cc (the shared epilogue, written out on this path)
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
L_0049e93c_11:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049e9cc (the shared epilogue, written out on this path)
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
L_0049e9c0:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049e9cc (the shared epilogue, written out on this path)
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
L_0049e9c8:
    charge(ctx, 1);
    v0 = 0;
    // 0x0049e9cc (the shared epilogue, written out on this path)
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

// sub_49E9F0 [geometryNativeStreamRead] -- reads a native geometry's PS2 instance data: the struct chunk (version
//   0x35000..0x37002), platform 4, the instance list (sized for the geometry's mesh count, sub_49E5A0), per mesh a block
//   of size + 583 (RwMalloc; header: owner, release callback sub_49CC30), the data 64- (or 128-) byte aligned, its
//   pointers relocated (sub_49E780) and the cache written back (SyncDCache); the geometry, or 0
// 0x0049E9F0 sub_49E9F0 -- 732 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49E9F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0049e9f0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    a2 = 0;
    sd(ra, sp, 0x90);
    a3 = addiu(sp, 0xBC);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    a1 = 1;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x49EA2Cu, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x0049ea90
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049ea3c
        charge(ctx, 6);
        lw(v1, sp, 0xBC);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x0049ea54
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_0049ea68;
            }
            // 0x0049ea98
            charge(ctx, 7);
            a0 = s0;
            a1 = addiu(sp, 0xB8);
            a2 = 4;
            jal(ctx, 0x49EAA0u, gen::fn_sub_4C5250_004c5250);
            v1 = 4;
            if (v0 != v1) {
                // 0x0049eb20
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0049eab4
                charge(ctx, 3);
                lw(v0, sp, 0xB8);
                if (v0 != v1) {
                    // 0x0049eb28
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x0049eac0
                    charge(ctx, 5);
                    lw(v0, gp, -17504);  // 0x7CE890
                    a0 = addu(s6, v0);
                    lw(v0, a0, 0);
                    a1 = 0;
                    if (v0 != 0) {
                        // 0x0049ead4
                        charge(ctx, 4);
                        lw(v0, v0, 0);
                        lw(v1, s6, 36);
                        if (v1 == v0) {
                            // 0x0049eae4
                            charge(ctx, 1);
                            a1 = 1;
                        }
                    }
                    // 0x0049eae8
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x0049eaf8
                        charge(ctx, 4);
                        link(ctx, 0x49EAF8u);  // $ra first: the delay slot below depends on it
                        lw(a1, s6, 36);
                        call(ctx, gen::fn_sub_49E5A0_0049e5a0);
                        a0 = v0;
                        lw(s2, a0, 0);
                    } else {
                        // 0x0049eaf0
                        charge(ctx, 2);
                        lw(s2, a0, 0);
                    }
                    // 0x0049eb08
                    charge(ctx, 4);
                    lw(s7, s2, 0);
                    v0 = slt(0, s7);
                    s5 = 0;
                    if (v0 != 0) {
                        // 0x0049eb30
                        charge(ctx, 2);
                        fp = 0x960000;
                        fp = addiu(fp, 0x178);
                        for (;;) {
                            // 0x0049eb38
                            charge(ctx, 7);
                            a0 = s0;
                            a1 = addiu(sp, 0xB4);
                            a2 = 4;
                            jal(ctx, 0x49EB40u, gen::fn_sub_4C5250_004c5250);
                            v1 = 4;
                            if (v0 != v1) {
                                goto L_0049eb54_19;
                            }
                            // 0x0049eb5c
                            charge(ctx, 11);
                            lw(a0, sp, 0xB4);
                            v1 = 0x30000;
                            lw(v0, fp, 0x0);
                            a1 = v1 | 0x50D;
                            s4 = addiu(s2, 4);
                            a0 = addiu(a0, 583);
                            jalr(ctx, 0x49EB70u, v0.u());
                            sw(v0, s4, 0);
                            lw(v0, s4, 0);
                            if (v0 == 0) {
                                goto L_0049ec70;
                            }
                            // 0x0049eb88
                            charge(ctx, 24);
                            sw(zero, v0, 0);
                            v1 = 0x4A0000;
                            lw(v0, s4, 0);
                            v1 = addiu(v1, -13264);  // &sub_49CC30
                            a0 = s0;
                            a1 = addiu(sp, 0xB0);
                            a2 = 4;
                            sw(zero, v0, 4);
                            lw(v0, s4, 0);
                            sw(s6, v0, 12);
                            lw(a3, sp, 0xB4);
                            lw(v0, s4, 0);
                            a3 = addiu(a3, 559);
                            sw(a3, v0, 8);
                            lw(v0, s4, 0);
                            sw(s4, v0, 16);
                            lw(v0, s4, 0);
                            sw(v1, v0, 20);
                            lw(v0, s4, 0);
                            s3 = addiu(v0, 24);
                            jal(ctx, 0x49EBD4u, gen::fn_sub_4C5250_004c5250);
                            v1 = 4;
                            if (v0 != v1) {
                                goto L_0049ec78;
                            }
                            // 0x0049ebe8
                            charge(ctx, 14);
                            sw(zero, s3, 0);
                            a0 = s3;
                            a1 = 0;
                            a2 = 432;
                            link(ctx, 0x49EBF8u);  // $ra first: the delay slot below depends on it
                            sw(zero, s3, 4);
                            call(ctx, gen::fn_memset_00521408);
                            v1 = addiu(s3, 432);
                            v0 = si(-64);
                            v1 = addiu(v1, 63);
                            v0 = v1 & v0;
                            sw(v0, s3, 8);
                            lw(v0, sp, 0xB0);
                            if (v0 != 0) {
                                // 0x0049ec80
                                charge(ctx, 6);
                                lw(v1, s3, 8);
                                v0 = si(-128);
                                v1 = addiu(v1, 127);
                                v0 = v1 & v0;
                                sw(v0, s3, 8);
                                backedge(ctx);
                            }
                            // 0x0049ec20
                            charge(ctx, 7);
                            lw(s1, sp, 0xB4);
                            lw(a1, s3, 8);
                            a0 = s0;
                            a2 = s1;
                            jal(ctx, 0x49EC2Cu, gen::fn_sub_4C5250_004c5250);
                            if (s1 != v0) {
                                break;
                            }
                            // 0x0049ec3c
                            charge(ctx, 11);
                            a0 = s3;
                            jal(ctx, 0x49EC3Cu, gen::fn_sub_49E780_0049e780);
                            lw(a0, s4, 0);
                            lw(v0, a0, 8);
                            v0 = addu(a0, v0);
                            a1 = addiu(v0, 24);
                            jal(ctx, 0x49EC50u, gen::fn_SyncDCache_00503a58);
                            s5 = addiu(s5, 1);
                            v0 = slt(s5, s7);
                            s2 = addiu(s2, 4);
                            if (v0 == 0) {
                                goto L_0049ec68_25;
                            }
                            backedge(ctx);
                        }
                        // 0x0049ec98
                        charge(ctx, 1);
                        v0 = 0;
                        // 0x0049ec9c (the shared epilogue, written out on this path)
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
                L_0049eb18:
                    charge(ctx, 2);
                    v0 = s6;
                }
            }
            // 0x0049ec9c (the shared epilogue, written out on this path)
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
    L_0049ea68:
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0xA8);
        a0 = v0 | 0x4;
        jal(ctx, 0x49EA74u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xAC);
        a0 = addiu(sp, 0xA8);
        jal(ctx, 0x49EA80u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x0049ec9c (the shared epilogue, written out on this path)
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
L_0049eb54_19:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049ec9c (the shared epilogue, written out on this path)
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
L_0049ec68_25:
    charge(ctx, 2);
    backedge(ctx);
    goto L_0049eb18;
L_0049ec70:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049ec9c (the shared epilogue, written out on this path)
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
L_0049ec78:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049ec9c (the shared epilogue, written out on this path)
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

// sub_49EE70 [sectorNativeStreamWrite] -- writes a world sector's PS2 instance data (sector + gp 0x7CE888), as
//   sub_49E830 does for a geometry (the world's native flag; size from sub_49F340; platform id 0x7CDC04); the stream, or
//   0
// 0x0049EE70 sub_49EE70 -- 456 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49EE70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049ee70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a0 = s3;
    link(ctx, 0x49EE98u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_worldSectorGetWorld_0049a170);
    lw(v1, v0, 8);
    v0 = 0x1000000;
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x0049eeb4
        charge(ctx, 7);
        lw(v0, gp, -17512);  // 0x7CE888
        v0 = addu(s3, v0);
        lw(s2, v0, 0);
        lw(s5, s2, 0);
        at = sltu(0, s5);
        s1 = 0;
        if (at != 0) {
            // 0x0049eed0
            charge(ctx, 1);
            s0 = s2;
            for (;;) {
                // 0x0049eed4
                charge(ctx, 7);
                link(ctx, 0x49EED4u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 4);
                call(ctx, gen::fn_sub_49CC30_0049cc30);
                s1 = addiu(s1, 1);
                s0 = addiu(s0, 4);
                v0 = sltu(s1, s5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0049eef0
        charge(ctx, 11);
        a0 = s3;
        jal(ctx, 0x49EEF0u, gen::fn_sub_49F340_0049f340);
        a2 = addiu(v0, -12);
        a0 = s4;
        v0 = 0x30000;
        a1 = 1;
        a3 = v0 | 0x7002;
        t0 = 55;
        jal(ctx, 0x49EF0Cu, gen::fn_sub_4C15A0_004c15a0);
        if (v0 != 0) {
            // 0x0049ef24
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(gp, -20716);  // &0x7CDC04
            a2 = 4;
            jal(ctx, 0x49EF2Cu, gen::fn_sub_4C53F0_004c53f0);
            if (v0 != 0) {
                // 0x0049ef3c
                charge(ctx, 4);
                lw(v0, s2, 0);
                at = sltu(0, v0);
                s1 = 0;
                if (at == 0) {
                    goto L_0049eff8;
                }
                // 0x0049ef4c
                charge(ctx, 1);
                s3 = s2;
                for (;;) {
                    // 0x0049ef50
                    charge(ctx, 13);
                    lw(s0, s3, 4);
                    a0 = s4;
                    a1 = addiu(sp, 0x7C);
                    a2 = 4;
                    lw(v1, s0, 32);
                    s5 = addiu(s0, 24);
                    lw(v0, s0, 8);
                    v1 = subu(v1, s0);
                    v0 = subu(v0, v1);
                    link(ctx, 0x49EF74u);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x7C);
                    call(ctx, gen::fn_sub_4C53F0_004c53f0);
                    if (v0 == 0) {
                        goto L_0049ef84_10;
                    }
                    // 0x0049ef8c
                    charge(ctx, 9);
                    a0 = s5;
                    jal(ctx, 0x49EF8Cu, gen::fn_sub_49E6C0_0049e6c0);
                    sw(v0, sp, 0x78);
                    a0 = s4;
                    a1 = addiu(sp, 0x78);
                    a2 = 4;
                    jal(ctx, 0x49EFA0u, gen::fn_sub_4C53F0_004c53f0);
                    if (v0 == 0) {
                        goto L_0049f008;
                    }
                    // 0x0049efb0
                    charge(ctx, 6);
                    lw(a1, s5, 8);
                    lw(a2, sp, 0x7C);
                    a0 = s4;
                    jal(ctx, 0x49EFB8u, gen::fn_sub_4C53F0_004c53f0);
                    if (v0 == 0) {
                        goto L_0049f010;
                    }
                    // 0x0049efc8
                    charge(ctx, 12);
                    a0 = s5;
                    jal(ctx, 0x49EFC8u, gen::fn_sub_49E780_0049e780);
                    lw(v0, s0, 8);
                    a0 = s0;
                    v0 = addu(s0, v0);
                    a1 = addiu(v0, 24);
                    jal(ctx, 0x49EFDCu, gen::fn_SyncDCache_00503a58);
                    lw(v0, s2, 0);
                    s1 = addiu(s1, 1);
                    v0 = sltu(s1, v0);
                    s3 = addiu(s3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_0049eff8;
            }
            // 0x0049f000
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x0049ef1c
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x0049f014 (the shared epilogue, written out on this path)
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
L_0049eff8:
    charge(ctx, 2);
    v0 = s4;
    // 0x0049f014 (the shared epilogue, written out on this path)
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
L_0049ef84_10:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049f014 (the shared epilogue, written out on this path)
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
L_0049f008:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049f014 (the shared epilogue, written out on this path)
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
L_0049f010:
    charge(ctx, 1);
    v0 = 0;
    // 0x0049f014 (the shared epilogue, written out on this path)
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

// sub_49F040 [sectorNativeStreamRead] -- reads a world sector's PS2 instance data, as sub_49E9F0 does for a geometry
//   (the mesh count from the sector's mesh header +120); the sector, or 0
// 0x0049F040 sub_49F040 -- 756 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49F040(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0049f040
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = s6;
    jal(ctx, 0x49F074u, gen::fn_worldSectorGetWorld_0049a170);
    a0 = s0;
    a1 = 1;
    a2 = 0;
    a3 = addiu(sp, 0xBC);
    jal(ctx, 0x49F088u, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x0049f0ec
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049f098
        charge(ctx, 6);
        lw(v1, sp, 0xBC);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x0049f0b0
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_0049f0c4;
            }
            // 0x0049f0f4
            charge(ctx, 7);
            a0 = s0;
            a1 = addiu(sp, 0xB8);
            a2 = 4;
            jal(ctx, 0x49F0FCu, gen::fn_sub_4C5250_004c5250);
            v1 = 4;
            if (v0 != v1) {
                // 0x0049f184
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0049f110
                charge(ctx, 3);
                lw(v0, sp, 0xB8);
                if (v0 != v1) {
                    // 0x0049f18c
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x0049f11c
                    charge(ctx, 5);
                    lw(v0, gp, -17512);  // 0x7CE888
                    a0 = addu(s6, v0);
                    lw(v0, a0, 0);
                    a1 = 0;
                    if (v0 != 0) {
                        // 0x0049f130
                        charge(ctx, 5);
                        lw(v1, s6, 120);
                        lw(v0, v0, 0);
                        lhu(v1, v1, 4);
                        if (v1 == v0) {
                            // 0x0049f144
                            charge(ctx, 1);
                            a1 = 1;
                        }
                    }
                    // 0x0049f148
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x0049f158
                        charge(ctx, 5);
                        lw(v0, s6, 120);
                        link(ctx, 0x49F15Cu);  // $ra first: the delay slot below depends on it
                        lhu(a1, v0, 4);
                        call(ctx, gen::fn_sub_49E5A0_0049e5a0);
                        a0 = v0;
                        lw(s2, a0, 0);
                    } else {
                        // 0x0049f150
                        charge(ctx, 2);
                        lw(s2, a0, 0);
                    }
                    // 0x0049f16c
                    charge(ctx, 4);
                    lw(s7, s2, 0);
                    v0 = slt(0, s7);
                    s5 = 0;
                    if (v0 != 0) {
                        // 0x0049f194
                        charge(ctx, 2);
                        fp = 0x960000;
                        fp = addiu(fp, 0x178);
                        for (;;) {
                            // 0x0049f19c
                            charge(ctx, 7);
                            a0 = s0;
                            a1 = addiu(sp, 0xB4);
                            a2 = 4;
                            jal(ctx, 0x49F1A4u, gen::fn_sub_4C5250_004c5250);
                            v1 = 4;
                            if (v0 != v1) {
                                goto L_0049f1b8_19;
                            }
                            // 0x0049f1c0
                            charge(ctx, 11);
                            lw(a0, sp, 0xB4);
                            v1 = 0x30000;
                            lw(v0, fp, 0x0);
                            a1 = v1 | 0x50D;
                            s4 = addiu(s2, 4);
                            a0 = addiu(a0, 583);
                            jalr(ctx, 0x49F1D4u, v0.u());
                            sw(v0, s4, 0);
                            lw(v0, s4, 0);
                            if (v0 == 0) {
                                goto L_0049f2d8;
                            }
                            // 0x0049f1ec
                            charge(ctx, 24);
                            sw(zero, v0, 0);
                            v1 = 0x4A0000;
                            lw(v0, s4, 0);
                            v1 = addiu(v1, -13264);  // &sub_49CC30
                            a0 = s0;
                            a1 = addiu(sp, 0xB0);
                            a2 = 4;
                            sw(zero, v0, 4);
                            lw(v0, s4, 0);
                            sw(s6, v0, 12);
                            lw(a3, sp, 0xB4);
                            lw(v0, s4, 0);
                            a3 = addiu(a3, 559);
                            sw(a3, v0, 8);
                            lw(v0, s4, 0);
                            sw(s4, v0, 16);
                            lw(v0, s4, 0);
                            sw(v1, v0, 20);
                            lw(v0, s4, 0);
                            s3 = addiu(v0, 24);
                            jal(ctx, 0x49F238u, gen::fn_sub_4C5250_004c5250);
                            v1 = 4;
                            if (v0 != v1) {
                                goto L_0049f2e0;
                            }
                            // 0x0049f24c
                            charge(ctx, 14);
                            sw(zero, s3, 0);
                            a0 = s3;
                            a1 = 0;
                            a2 = 432;
                            link(ctx, 0x49F25Cu);  // $ra first: the delay slot below depends on it
                            sw(zero, s3, 4);
                            call(ctx, gen::fn_memset_00521408);
                            v1 = addiu(s3, 432);
                            v0 = si(-64);
                            v1 = addiu(v1, 63);
                            v0 = v1 & v0;
                            sw(v0, s3, 8);
                            lw(v0, sp, 0xB0);
                            if (v0 != 0) {
                                // 0x0049f2e8
                                charge(ctx, 6);
                                lw(v1, s3, 8);
                                v0 = si(-128);
                                v1 = addiu(v1, 127);
                                v0 = v1 & v0;
                                sw(v0, s3, 8);
                                backedge(ctx);
                            } else {
                                // 0x0049f284
                                charge(ctx, 1);
                            }
                            // 0x0049f288
                            charge(ctx, 7);
                            lw(s1, sp, 0xB4);
                            lw(a1, s3, 8);
                            a0 = s0;
                            a2 = s1;
                            jal(ctx, 0x49F294u, gen::fn_sub_4C5250_004c5250);
                            if (s1 != v0) {
                                break;
                            }
                            // 0x0049f2a4
                            charge(ctx, 11);
                            a0 = s3;
                            jal(ctx, 0x49F2A4u, gen::fn_sub_49E780_0049e780);
                            lw(a0, s4, 0);
                            lw(v0, a0, 8);
                            v0 = addu(a0, v0);
                            a1 = addiu(v0, 24);
                            jal(ctx, 0x49F2B8u, gen::fn_SyncDCache_00503a58);
                            s5 = addiu(s5, 1);
                            v0 = slt(s5, s7);
                            s2 = addiu(s2, 4);
                            if (v0 == 0) {
                                goto L_0049f2d0_26;
                            }
                            backedge(ctx);
                        }
                        // 0x0049f300
                        charge(ctx, 1);
                        v0 = 0;
                        // 0x0049f304 (the shared epilogue, written out on this path)
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
                L_0049f17c:
                    charge(ctx, 2);
                    v0 = s6;
                }
            }
            // 0x0049f304 (the shared epilogue, written out on this path)
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
    L_0049f0c4:
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0xA8);
        a0 = v0 | 0x4;
        jal(ctx, 0x49F0D0u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xAC);
        a0 = addiu(sp, 0xA8);
        jal(ctx, 0x49F0DCu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x0049f304 (the shared epilogue, written out on this path)
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
L_0049f1b8_19:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049f304 (the shared epilogue, written out on this path)
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
L_0049f2d0_26:
    charge(ctx, 2);
    backedge(ctx);
    goto L_0049f17c;
L_0049f2d8:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049f304 (the shared epilogue, written out on this path)
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
L_0049f2e0:
    charge(ctx, 2);
    v0 = 0;
    // 0x0049f304 (the shared epilogue, written out on this path)
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

// sub_4A6CE0 [rt2dFontStrokeString] -- draws a string with an outline (vector) font: the transform pushed, per
//   character its glyph and, for a glyph without a texture, its outline path stroked (sub_4ACE70) and the pen moved
//   (sub_4AAE00); the transform popped; the font
// 0x004A6CE0 sub_4A6CE0 -- 456 bytes; frame 0xA0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4A6CE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x004a6ce0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    s6 = a3;
    sq(s4, sp, 0x50);
    s5 = a0;
    sq(s3, sp, 0x40);
    s4 = a1;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a2;
    mov_s(f20, f12);
    if (s5 != 0) {
        // 0x004a6d24
        charge(ctx, 7);
        link(ctx, 0x4A6D24u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 308);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        s7 = v0;
        lw(v0, s5, 16);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x004a6d50
            charge(ctx, 3);
            s3 = 1;
            s1 = 0;
            s2 = 0;
        } else {
            // 0x004a6d40
            charge(ctx, 4);
            s3 = 2;
            s1 = 255;
            s2 = 1;
        }
        // 0x004a6d5c
        charge(ctx, 21);
        jal(ctx, 0x4A6D5Cu, gen::fn_sub_4AAA60_004aaa60);
        lwc1(f13, s0, 4);
        link(ctx, 0x4A6D68u);  // $ra first: the delay slot below depends on it
        lwc1(f12, s0, 0);
        call(ctx, gen::fn_sub_4AAE00_004aae00);
        mov_s(f12, f20);
        mov_s(f13, f20);
        jal(ctx, 0x4A6D74u, gen::fn_sub_4AADA0_004aada0);
        lwc1(f0, s5, 8);
        mtc1(zero, f12);
        neg_s(f13, f0);
        jal(ctx, 0x4A6D84u, gen::fn_sub_4AAE00_004aae00);
        v0 = addu(s4, s2);
        s1 = s1 & 0xFF;
        lbu(v1, v0, 0);
        lbu(v0, s4, 0);
        v1 = s1 & v1;
        v1 = sll(v1, 8);
        v1 = v0 | v1;
        if (i64(v1) > 0) {
            for (;;) {
                // 0x004a6db0
                charge(ctx, 3);
                v0 = slti(v1, 128);
                if (v0 != 0) {
                    // 0x004a6df0
                    charge(ctx, 4);
                    v0 = sll(v1, 1);
                    v0 = addu(s5, v0);
                    lh(v0, v0, 36);
                } else {
                    // 0x004a6dbc
                    charge(ctx, 4);
                    lw(v0, s5, 292);
                    v1 = subu(v1, v0);
                    if (i64(v1) >= 0) {
                        // 0x004a6dcc
                        charge(ctx, 4);
                        lw(v0, s5, 296);
                        at = slt(v1, v0);
                        if (at == 0) {
                            goto L_004a6e70;
                        }
                        // 0x004a6ddc
                        charge(ctx, 5);
                        lw(v0, s5, 300);
                        v1 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        lh(v0, v0, 0);
                        goto L_004a6e00;
                    }
                L_004a6e70:
                    charge(ctx, 2);
                    v0 = si(-1);
                    backedge(ctx);
                }
            L_004a6e00:
                charge(ctx, 2);
                s4 = addu(s4, s3);
                if (i64(v0) >= 0) {
                    // 0x004a6e08
                    charge(ctx, 5);
                    v0 = sll(v0, 5);
                    s0 = addu(s7, v0);
                    lw(v0, s0, 4);
                    if (v0 == 0) {
                        // 0x004a6e1c
                        charge(ctx, 9);
                        lw(a0, s0, 24);
                        a1 = s6;
                        jal(ctx, 0x4A6E20u, gen::fn_sub_4ACE70_004ace70);
                        lwc1(f1, s0, 0);
                        lwc1(f0, s5, 12);
                        mtc1(zero, f13);
                        add_s(f12, f1, f0);
                        jal(ctx, 0x4A6E34u, gen::fn_sub_4AAE00_004aae00);
                    }
                }
                // 0x004a6e40
                charge(ctx, 8);
                v0 = addu(s2, s4);
                lbu(v1, v0, 0);
                lbu(v0, s4, 0);
                v1 = s1 & v1;
                v1 = sll(v1, 8);
                v1 = v0 | v1;
                if (i64(v1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004a6e60
        charge(ctx, 2);
        jal(ctx, 0x4A6E60u, gen::fn_sub_4AAD50_004aad50);
    }
    // 0x004a6e68
    charge(ctx, 2);
    v0 = s5;
    // 0x004a6e78
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    lq(s7, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xA0);
}

// sub_4A6EB0 [rt2dFontBitmapShowString] -- draws a string with a bitmap font through Im3D: per character a textured
//   quad (six 36-byte vertices: position, the brush's gradient colours or flat colour, the glyph's UVs), flushed
//   (RwIm3DTransform sub_4F1ED0, render sub_4F1FD0, end sub_4F1F80) at a texture change or every 379 vertices; the pen x
//   advanced (*$a2); the font
// 0x004A6EB0 sub_4A6EB0 -- 1904 bytes; frame 0x140: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_4A6EB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x004a6eb0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    v0 = 0x960000;
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    s5 = a0;
    sq(s3, sp, 0x50);
    s4 = a1;
    sq(s2, sp, 0x40);
    s3 = a3;
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    sw(a2, sp, 0xFC);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lwc1(f21, v0, -4264);  // 0x95EF58
    mov_s(f24, f12);
    if (s5 != 0) {
        // 0x004a6f10
        charge(ctx, 7);
        link(ctx, 0x4A6F10u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 308);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        sq(v0, sp, 0xD0);
        lw(v0, s5, 16);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x004a6f40
            charge(ctx, 4);
            v0 = 1;
            s0 = 0;
            sw(v0, sp, 0xE0);
            s7 = 0;
        } else {
            // 0x004a6f2c
            charge(ctx, 5);
            v0 = 2;
            s0 = 255;
            sw(v0, sp, 0xE0);
            s7 = 1;
        }
        // 0x004a6f50
        charge(ctx, 40);
        jal(ctx, 0x4A6F50u, gen::fn_sub_4AAA60_004aaa60);
        lw(v0, sp, 0xFC);
        lwc1(f13, v0, 4);
        link(ctx, 0x4A6F60u);  // $ra first: the delay slot below depends on it
        lwc1(f12, v0, 0);
        call(ctx, gen::fn_sub_4AAE00_004aae00);
        mov_s(f12, f24);
        mov_s(f13, f24);
        jal(ctx, 0x4A6F6Cu, gen::fn_sub_4AADA0_004aada0);
        lwc1(f0, s5, 8);
        mtc1(zero, f12);
        neg_s(f13, f0);
        jal(ctx, 0x4A6F7Cu, gen::fn_sub_4AAE00_004aae00);
        jal(ctx, 0x4A6F84u, gen::fn_sub_4AAE60_004aae60);
        fp = v0;
        a0 = s5;
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a1 = s4;
        jal(ctx, 0x4A6F9Cu, gen::fn_sub_4A9560_004a9560);
        v0 = s0 & 0xFF;
        v1 = addu(s4, s7);
        sq(v0, sp, 0xC0);
        mtc1(zero, f20);
        v0 = 0x3F800000;
        lbu(a1, v1, 0);
        mtc1(v0, f1);
        lbu(a0, s4, 0);
        s2 = 0;
        s1 = 0;
        div_s(f22, f1, f0);
        v0 = 0x960000;
        lw(v0, v0, -4764);  // 0x95ED64
        lq(v1, sp, 0xC0);
        v1 = v1 & a1;
        v1 = sll(v1, 8);
        a0 = a0 | v1;
        mov_s(f23, f20);
        if (i64(a0) > 0) {
            // 0x004a6ff0
            charge(ctx, 2);
            s6 = 0x960000;
            s6 = addiu(s6, 144);  // &pfn_RwRenderStateSet
            for (;;) {
                // 0x004a6ff8
                charge(ctx, 3);
                v1 = slti(a0, 128);
                if (v1 != 0) {
                    // 0x004a7038
                    charge(ctx, 4);
                    v1 = sll(a0, 1);
                    v1 = addu(s5, v1);
                    lh(a0, v1, 36);
                } else {
                    // 0x004a7004
                    charge(ctx, 4);
                    lw(v1, s5, 292);
                    a0 = subu(a0, v1);
                    if (i64(a0) >= 0) {
                        // 0x004a7014
                        charge(ctx, 4);
                        lw(v1, s5, 296);
                        at = slt(a0, v1);
                        if (at == 0) {
                            goto L_004a7550;
                        }
                        // 0x004a7024
                        charge(ctx, 5);
                        lw(v1, s5, 300);
                        a0 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        lh(a0, v1, 0);
                        goto L_004a7048;
                    }
                L_004a7550:
                    charge(ctx, 2);
                    a0 = si(-1);
                    backedge(ctx);
                }
            L_004a7048:
                charge(ctx, 3);
                lw(v1, sp, 0xE0);
                s4 = addu(s4, v1);
                if (i64(a0) >= 0) {
                    // 0x004a7054
                    charge(ctx, 6);
                    lq(v1, sp, 0xD0);
                    a0 = sll(a0, 5);
                    s0 = addu(v1, a0);
                    lw(v1, s0, 4);
                    if (v1 != s2) {
                        // 0x004a706c
                        charge(ctx, 1);
                        goto L_004a7070;
                    }
                    // 0x004a7558
                    charge(ctx, 3);
                    at = slti(s1, 379);
                    if (at != 0) {
                        backedge(ctx);
                    } else {
                        // 0x004a7564
                        charge(ctx, 2);
                        backedge(ctx);
                    L_004a7070:
                        charge(ctx, 2);
                        if (s1 != 0) {
                            // 0x004a7570
                            charge(ctx, 16);
                            v1 = 0x960000;
                            lw(a0, v1, -4764);  // 0x95ED64
                            v1 = 0x38E30000;
                            v0 = subu(v0, a0);
                            v1 = v1 | 0x8E39;
                            mult(zero, v1, v0);
                            v1 = srl(v0, 31);
                            mfhi(v0);
                            a2 = fp;
                            a3 = 5;
                            v0 = sra(v0, 3);
                            a1 = addu(v0, v1);
                            jal(ctx, 0x4A75A0u, gen::fn_sub_4F1ED0_004f1ed0);
                            if (v0 == 0) {
                                backedge(ctx);
                            } else {
                                // 0x004a75b0
                                charge(ctx, 9);
                                a1 = 0x960000;
                                a2 = s1;
                                a0 = 3;
                                a1 = addiu(a1, -5536);  // &0x95EA60
                                jal(ctx, 0x4A75BCu, gen::fn_sub_4F1FD0_004f1fd0);
                                jal(ctx, 0x4A75C4u, gen::fn_sub_4F1F80_004f1f80);
                                backedge(ctx);
                            }
                        }
                        // 0x004a7078
                        charge(ctx, 3);
                        lw(v0, s0, 4);
                        if (v0 != s2) {
                            // 0x004a7084
                            charge(ctx, 11);
                            lbu(a1, v0, 80);
                            lw(v0, s6, 0);
                            a0 = 9;
                            jalr(ctx, 0x4A708Cu, v0.u());
                            lw(v1, s0, 4);
                            lw(v0, s6, 0);
                            lw(a1, v1, 0);
                            a0 = 1;
                            jalr(ctx, 0x4A70A0u, v0.u());
                            lw(s2, s0, 4);
                        }
                        // 0x004a70b0
                        charge(ctx, 5);
                        v0 = 0x960000;
                        lw(v1, s3, 104);
                        lw(v0, v0, -4764);  // 0x95ED64
                        s1 = 0;
                        if (v1 != 0) {
                            // 0x004a70c4
                            charge(ctx, 4);
                            lw(a0, s3, 100);
                            v1 = a0 & 0x2;
                            if (v1 != 0) {
                                // 0x004a70d4
                                charge(ctx, 3);
                                v1 = si(-3);
                                v1 = a0 & v1;
                                sw(v1, s3, 100);
                            }
                        }
                    }
                    // 0x004a70e0
                    charge(ctx, 17);
                    v1 = addiu(sp, 0x134);
                    sw(zero, v1, 0);
                    swc1(f23, v0, 0);
                    v1 = addiu(sp, 0x138);
                    swc1(f21, v1, 0);
                    lwc1(f1, sp, 0x134);
                    lwc1(f0, sp, 0x138);
                    swc1(f1, v0, 4);
                    swc1(f0, v0, 8);
                    lwc1(f0, s0, 8);
                    swc1(f0, v0, 28);
                    lwc1(f0, s0, 20);
                    swc1(f0, v0, 32);
                    lw(v1, s3, 100);
                    v1 = v1 & 0x1;
                    swc1(f23, sp, 0x130);
                    if (v1 == 0) {
                        // 0x004a71a0
                        charge(ctx, 8);
                        lbu(v1, s3, 96);
                        sb(v1, v0, 12);
                        lbu(v1, s3, 97);
                        sb(v1, v0, 13);
                        lbu(v1, s3, 98);
                        sb(v1, v0, 14);
                        lbu(v1, s3, 99);
                        sb(v1, v0, 15);
                    } else {
                        // 0x004a7124
                        charge(ctx, 30);
                        lwc1(f2, s3, 72);
                        mul_s(f6, f20, f22);
                        lwc1(f1, s3, 48);
                        mul_s(f2, f2, f6);
                        lwc1(f5, s3, 76);
                        add_s(f2, f2, f1);
                        lwc1(f0, s3, 52);
                        mul_s(f1, f5, f6);
                        add_s(f1, f1, f0);
                        cvt_w_s(f0, f2);
                        mfc1(a0, f0);
                        lwc1(f4, s3, 80);
                        cvt_w_s(f0, f1);
                        lwc1(f3, s3, 84);
                        mfc1(v1, f0);
                        lwc1(f1, s3, 56);
                        mul_s(f4, f4, f6);
                        lwc1(f0, s3, 60);
                        mul_s(f3, f3, f6);
                        add_s(f2, f4, f1);
                        sb(a0, v0, 12);
                        sb(v1, v0, 13);
                        add_s(f1, f3, f0);
                        cvt_w_s(f0, f2);
                        mfc1(v1, f0);
                        cvt_w_s(f0, f1);
                        sb(v1, v0, 14);
                        mfc1(v1, f0);
                        sb(v1, v0, 15);
                    }
                    // 0x004a71c0
                    charge(ctx, 18);
                    v1 = addiu(sp, 0x128);
                    swc1(f21, v1, 0);
                    a0 = 0x3F800000;
                    v1 = addiu(sp, 0x124);
                    sw(a0, v1, 0);
                    lwc1(f0, sp, 0x128);
                    lwc1(f1, sp, 0x124);
                    swc1(f23, v0, 36);
                    swc1(f1, v0, 40);
                    swc1(f0, v0, 44);
                    lwc1(f0, s0, 8);
                    swc1(f0, v0, 64);
                    lwc1(f0, s0, 12);
                    swc1(f0, v0, 68);
                    lw(v1, s3, 100);
                    v1 = v1 & 0x1;
                    swc1(f23, sp, 0x120);
                    if (v1 == 0) {
                        // 0x004a7280
                        charge(ctx, 8);
                        lbu(v1, s3, 96);
                        sb(v1, v0, 48);
                        lbu(v1, s3, 97);
                        sb(v1, v0, 49);
                        lbu(v1, s3, 98);
                        sb(v1, v0, 50);
                        lbu(v1, s3, 99);
                        sb(v1, v0, 51);
                    } else {
                        // 0x004a7208
                        charge(ctx, 30);
                        lwc1(f2, s3, 24);
                        mul_s(f6, f20, f22);
                        lwc1(f1, s3, 0);
                        mul_s(f2, f2, f6);
                        lwc1(f5, s3, 28);
                        add_s(f2, f2, f1);
                        lwc1(f0, s3, 4);
                        mul_s(f1, f5, f6);
                        add_s(f1, f1, f0);
                        cvt_w_s(f0, f2);
                        mfc1(a0, f0);
                        lwc1(f4, s3, 32);
                        cvt_w_s(f0, f1);
                        lwc1(f3, s3, 36);
                        mfc1(v1, f0);
                        lwc1(f1, s3, 8);
                        mul_s(f4, f4, f6);
                        lwc1(f0, s3, 12);
                        mul_s(f3, f3, f6);
                        add_s(f2, f4, f1);
                        sb(a0, v0, 48);
                        sb(v1, v0, 49);
                        add_s(f1, f3, f0);
                        cvt_w_s(f0, f2);
                        mfc1(v1, f0);
                        cvt_w_s(f0, f1);
                        sb(v1, v0, 50);
                        mfc1(v1, f0);
                        sb(v1, v0, 51);
                    }
                    // 0x004a72a0
                    charge(ctx, 19);
                    v1 = addiu(sp, 0x114);
                    lwc1(f2, s0, 0);
                    sw(zero, v1, 0);
                    v1 = addiu(sp, 0x118);
                    swc1(f21, v1, 0);
                    lwc1(f1, sp, 0x114);
                    lwc1(f0, sp, 0x118);
                    add_s(f2, f23, f2);
                    swc1(f2, v0, 72);
                    swc1(f1, v0, 76);
                    swc1(f0, v0, 80);
                    lwc1(f0, s0, 16);
                    swc1(f0, v0, 100);
                    lwc1(f0, s0, 20);
                    swc1(f0, v0, 104);
                    lw(v1, s3, 100);
                    v1 = v1 & 0x1;
                    swc1(f2, sp, 0x110);
                    if (v1 == 0) {
                        // 0x004a7370
                        charge(ctx, 8);
                        lbu(v1, s3, 96);
                        sb(v1, v0, 84);
                        lbu(v1, s3, 97);
                        sb(v1, v0, 85);
                        lbu(v1, s3, 98);
                        sb(v1, v0, 86);
                        lbu(v1, s3, 99);
                        sb(v1, v0, 87);
                    } else {
                        // 0x004a72ec
                        charge(ctx, 32);
                        lwc1(f5, s0, 0);
                        lwc1(f4, s3, 72);
                        lwc1(f2, s3, 80);
                        lwc1(f0, s3, 48);
                        lwc1(f1, s3, 84);
                        lwc1(f3, s3, 76);
                        add_s(f5, f20, f5);
                        mul_s(f6, f22, f5);
                        mul_s(f4, f4, f6);
                        add_s(f0, f4, f0);
                        mul_s(f5, f2, f6);
                        mul_s(f4, f1, f6);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        lwc1(f2, s3, 52);
                        mul_s(f3, f3, f6);
                        lwc1(f1, s3, 56);
                        add_s(f3, f3, f2);
                        lwc1(f0, s3, 60);
                        add_s(f2, f5, f1);
                        add_s(f1, f4, f0);
                        sb(v1, v0, 84);
                        cvt_w_s(f0, f3);
                        mfc1(v1, f0);
                        cvt_w_s(f0, f2);
                        sb(v1, v0, 85);
                        mfc1(v1, f0);
                        cvt_w_s(f0, f1);
                        sb(v1, v0, 86);
                        mfc1(v1, f0);
                        sb(v1, v0, 87);
                    }
                    // 0x004a7390
                    charge(ctx, 20);
                    a0 = 0x3F800000;
                    lwc1(f2, s0, 0);
                    v1 = addiu(sp, 0x104);
                    sw(a0, v1, 0);
                    v1 = addiu(sp, 0x108);
                    swc1(f21, v1, 0);
                    lwc1(f1, sp, 0x104);
                    lwc1(f0, sp, 0x108);
                    add_s(f2, f23, f2);
                    swc1(f2, v0, 108);
                    swc1(f1, v0, 112);
                    swc1(f0, v0, 116);
                    lwc1(f0, s0, 16);
                    swc1(f0, v0, 136);
                    lwc1(f0, s0, 12);
                    swc1(f0, v0, 140);
                    lw(v1, s3, 100);
                    v1 = v1 & 0x1;
                    swc1(f2, sp, 0x100);
                    if (v1 == 0) {
                        // 0x004a7460
                        charge(ctx, 8);
                        lbu(v1, s3, 96);
                        sb(v1, v0, 120);
                        lbu(v1, s3, 97);
                        sb(v1, v0, 121);
                        lbu(v1, s3, 98);
                        sb(v1, v0, 122);
                        lbu(v1, s3, 99);
                        sb(v1, v0, 123);
                    } else {
                        // 0x004a73e0
                        charge(ctx, 32);
                        lwc1(f5, s0, 0);
                        lwc1(f4, s3, 24);
                        lwc1(f2, s3, 32);
                        lwc1(f0, s3, 0);
                        lwc1(f1, s3, 36);
                        lwc1(f3, s3, 28);
                        add_s(f5, f20, f5);
                        mul_s(f6, f22, f5);
                        mul_s(f4, f4, f6);
                        add_s(f0, f4, f0);
                        mul_s(f5, f2, f6);
                        mul_s(f4, f1, f6);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        lwc1(f2, s3, 4);
                        mul_s(f3, f3, f6);
                        lwc1(f1, s3, 8);
                        add_s(f3, f3, f2);
                        lwc1(f0, s3, 12);
                        add_s(f2, f5, f1);
                        add_s(f1, f4, f0);
                        sb(v1, v0, 120);
                        cvt_w_s(f0, f3);
                        mfc1(v1, f0);
                        cvt_w_s(f0, f2);
                        sb(v1, v0, 121);
                        mfc1(v1, f0);
                        cvt_w_s(f0, f1);
                        sb(v1, v0, 122);
                        mfc1(v1, f0);
                        sb(v1, v0, 123);
                    }
                    // 0x004a7480
                    charge(ctx, 8);
                    v0 = addiu(v0, 144);
                    lwc1(f1, s0, 0);
                    s1 = addiu(s1, 6);
                    lwc1(f0, s5, 12);
                    add_s(f0, f1, f0);
                    add_s(f23, f23, f0);
                    add_s(f20, f20, f0);
                }
                // 0x004a74a0
                charge(ctx, 9);
                v1 = addu(s7, s4);
                lbu(a1, v1, 0);
                lbu(a0, s4, 0);
                lq(v1, sp, 0xC0);
                v1 = v1 & a1;
                v1 = sll(v1, 8);
                a0 = a0 | v1;
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004a74c4
            charge(ctx, 1);
        }
        // 0x004a74c8
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x004a74d0
            charge(ctx, 16);
            v1 = 0x960000;
            a1 = 0x38E30000;
            lw(a0, v1, -4764);  // 0x95ED64
            v1 = a1 | 0x8E39;
            v0 = subu(v0, a0);
            mult(zero, v1, v0);
            v1 = srl(v0, 31);
            mfhi(v0);
            a2 = fp;
            a3 = 5;
            v0 = sra(v0, 3);
            a1 = addu(v0, v1);
            jal(ctx, 0x4A7500u, gen::fn_sub_4F1ED0_004f1ed0);
            if (v0 != 0) {
                // 0x004a7510
                charge(ctx, 7);
                a1 = 0x960000;
                a2 = s1;
                a0 = 3;
                a1 = addiu(a1, -5536);  // &0x95EA60
                jal(ctx, 0x4A751Cu, gen::fn_sub_4F1FD0_004f1fd0);
                jal(ctx, 0x4A7524u, gen::fn_sub_4F1F80_004f1f80);
            }
        }
        // 0x004a752c
        charge(ctx, 7);
        lw(v0, sp, 0xFC);
        mtc1(zero, f0);
        lwc1(f1, v0, 0);
        adda_s(f0, f1);
        madd_s(f0, f23, f24);
        link(ctx, 0x4A7540u);  // $ra first: the delay slot below depends on it
        swc1(f0, v0, 0);
        call(ctx, gen::fn_sub_4AAD50_004aad50);
    }
    // 0x004a7548
    charge(ctx, 2);
    v0 = s5;
    // 0x004a75d8
    charge(ctx, 17);
    ld(ra, sp, 0xB0);
    lq(fp, sp, 0xA0);
    lwc1(f24, sp, 0x10);
    lq(s7, sp, 0x90);
    lwc1(f23, sp, 0xC);
    lq(s6, sp, 0x80);
    lwc1(f22, sp, 0x8);
    lq(s5, sp, 0x70);
    lwc1(f21, sp, 0x4);
    lq(s4, sp, 0x60);
    lwc1(f20, sp, 0x0);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0x140);
}

// sub_4A7820 [rt2dFontReadMetrics1] -- reads a METRICS1 font: the texture name line, the texture (sub_4D1260; with a
//   mask when the second name is present), the height line, then per line "%i %i %i %i %i" a glyph (code, left, top,
//   right, bottom): its UVs, width and character-map entry (codes >= 128 in the overflow table 0x95F984, grown 32 at a
//   time); the glyph table at +308 grown as needed; the font's height / baseline / show callback (sub_46BFB0); the font,
//   or 0
// 0x004A7820 sub_4A7820 -- 1564 bytes; frame 0x130: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_4A7820(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004a7820
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a1;
    sq(s2, sp, 0x30);
    s3 = a0;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    sw(a2, sp, 0x114);
    sw(a3, sp, 0x110);
    link(ctx, 0x4A7860u);  // $ra first: the delay slot below depends on it
    swc1(f20, sp, 0x0);
    call(ctx, gen::fn_sub_4D11F0_004d11f0);
    sw(v0, sp, 0x10C);
    v0 = 0x960000;
    link(ctx, 0x4A7870u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4736);
    call(ctx, gen::fn_sub_4D11D0_004d11d0);
    sw(zero, s3, 0);
    s6 = s3;
    lw(s2, s3, 304);
    s1 = 0;
    if (s2 == 0) {
        // 0x004a788c
        charge(ctx, 1);
        s2 = 256;
    }
    // 0x004a7890
    charge(ctx, 36);
    v0 = addiu(s3, 36);
    lw(a0, s3, 308);
    sq(v0, sp, 0xD0);
    a1 = s2;
    v0 = 0x960000;
    lw(s0, v0, -1660);  // 0x95F984
    v0 = 0x30000;
    a2 = v0 | 0x190;
    jal(ctx, 0x4A78ACu, gen::fn_sub_4C1F70_004c1f70);
    link(ctx, 0x4A78B4u);  // $ra first: the delay slot below depends on it
    lw(a0, s3, 308);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    s7 = v0;
    a2 = sll(s2, 5);
    a0 = s7;
    a1 = 0;
    jal(ctx, 0x4A78C8u, gen::fn_memset_00521408);
    lw(a0, sp, 0x110);
    lw(a2, sp, 0x114);
    a1 = 256;
    jal(ctx, 0x4A78D8u, gen::fn_sub_4C0550_004c0550);
    v0 = 0x960000;
    s5 = 0x960000;
    v0 = addiu(v0, 372);  // &0x960174
    s5 = addiu(s5, -2684);  // &0x95F584
    sw(v0, sp, 0xE0);
    a1 = addiu(gp, -20608);  // "%s %s\n"
    lw(a0, sp, 0x110);
    a2 = s4;
    lw(v0, v0, 0);  // 0x960174
    a3 = s5;
    jalr(ctx, 0x4A7904u, v0.u());
    fp = v0;
    v0 = addiu(fp, -0x1);
    at = sltiu(v0, 2);
    if (at != 0) {
        // 0x004a7920
        charge(ctx, 6);
        v0 = 0x960000;
        link(ctx, 0x4A7924u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, -4756);
        call(ctx, gen::fn_sub_4CC5C0_004cc5c0);
        v0 = 1;
        if (fp != v0) {
            // 0x004a7994
            charge(ctx, 4);
            a0 = s4;
            a1 = s5;
            jal(ctx, 0x4A7998u, gen::fn_sub_4D1260_004d1260);
            sw(v0, sp, 0x108);
        } else {
            // 0x004a7938
            charge(ctx, 13);
            v0 = 0x960000;
            fp = 0x960000;
            lw(a2, v0, -4756);  // 0x95ED6C
            fp = addiu(fp, 0x134);
            a0 = s5;
            a1 = addiu(gp, -20600);  // "%sm%s"
            lw(v0, fp, 0x0);
            a3 = s4;
            jalr(ctx, 0x4A7954u, v0.u());
            a0 = s5;
            jal(ctx, 0x4A795Cu, gen::fn_sub_4C06C0_004c06c0);
            if (v0 == 0) {
                // 0x004a7bd8
                charge(ctx, 5);
                a0 = s4;
                a1 = 0;
                jal(ctx, 0x4A7BDCu, gen::fn_sub_4D1260_004d1260);
                sw(v0, sp, 0x108);
                backedge(ctx);
            } else {
                // 0x004a796c
                charge(ctx, 10);
                lw(v0, fp, 0x0);
                a0 = s5;
                a1 = addiu(gp, -20592);  // "m%s"
                a2 = s4;
                jalr(ctx, 0x4A7978u, v0.u());
                a0 = s4;
                a1 = s5;
                jal(ctx, 0x4A7984u, gen::fn_sub_4D1260_004d1260);
                sw(v0, sp, 0x108);
            }
        }
        // 0x004a79a4
        charge(ctx, 3);
        lw(v0, sp, 0x108);
        if (v0 == 0) {
            // 0x004a7df4
            charge(ctx, 1);
            s6 = 0;
        } else {
            // 0x004a79b0
            charge(ctx, 31);
            sw(v0, s3, 20);
            lw(v0, v0, 0);
            lw(a0, sp, 0x110);
            lw(a2, sp, 0x114);
            lw(s4, v0, 12);
            lw(s5, v0, 16);
            a1 = 256;
            jal(ctx, 0x4A79C8u, gen::fn_sub_4C0550_004c0550);
            lw(v0, sp, 0xE0);
            a1 = addiu(gp, -20588);  // "%d"
            lw(a0, sp, 0x110);
            lw(v0, v0, 0);
            a2 = addiu(sp, 0x12C);
            jalr(ctx, 0x4A79E0u, v0.u());
            mtc1(s4, f0);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            fp = 0;
            cvt_s_w(f0, f0);
            sw(zero, sp, 0xF0);
            v0 = 0x960000;
            v0 = addiu(v0, 376);  // &0x960178
            sq(v0, sp, 0xC0);
            v0 = 0x960000;
            v0 = addiu(v0, 380);  // &0x96017C
            div_s(f21, f1, f0);
            sq(v0, sp, 0xB0);
            mtc1(s5, f0);
            cvt_s_w(f0, f0);
            div_s(f20, f1, f0);
            for (;;) {
                // 0x004a7a2c
                charge(ctx, 2);
                if (s6 == s3) {
                    // 0x004a7a34
                    charge(ctx, 6);
                    lw(a0, sp, 0x110);
                    lw(a2, sp, 0x114);
                    a1 = 256;
                    jal(ctx, 0x4A7A3Cu, gen::fn_sub_4C0550_004c0550);
                    if (v0 != 0) {
                        // 0x004a7a4c
                        charge(ctx, 14);
                        lw(v0, sp, 0xE0);
                        a1 = 0x780000;
                        lw(a0, sp, 0x110);
                        a1 = addiu(a1, -7328);  // "%i %i %i %i %i\n"
                        a2 = addiu(sp, 0x128);
                        a3 = addiu(sp, 0x124);
                        t0 = addiu(sp, 0x11C);
                        t1 = addiu(sp, 0x120);
                        lw(v0, v0, 0);
                        t2 = addiu(sp, 0x118);
                        jalr(ctx, 0x4A7A70u, v0.u());
                        v1 = 5;
                        if (v0 != v1) {
                            backedge(ctx);
                        } else {
                            // 0x004a7a84
                            charge(ctx, 5);
                            lw(v0, sp, 0x128);
                            at = 0x10000;
                            at = slt(v0, at);
                            if (at != 0) {
                                // 0x004a7aa0
                                charge(ctx, 5);
                                v0 = 0x960000;
                                lw(v0, v0, -1656);  // 0x95F988
                                at = slt(s1, v0);
                                if (at == 0) {
                                    // 0x004a7bec
                                    charge(ctx, 19);
                                    s4 = addiu(v0, 32);
                                    v0 = 0x30000;
                                    a1 = v0 | 0x190;
                                    lq(v0, sp, 0xC0);
                                    lw(v0, v0, 0);
                                    a0 = sll(s4, 2);
                                    jalr(ctx, 0x4A7C00u, v0.u());
                                    s5 = v0;
                                    a1 = s0;
                                    v0 = 0x960000;
                                    a0 = s5;
                                    lw(v0, v0, -1656);  // 0x95F988
                                    a2 = sll(v0, 2);
                                    jal(ctx, 0x4A7C1Cu, gen::fn_memcpy_00521250);
                                    v0 = 0x960000;
                                    lw(v0, v0, -1656);  // 0x95F988
                                    at = slt(v0, s4);
                                    if (at != 0) {
                                        // 0x004a7c38
                                        charge(ctx, 4);
                                        v1 = subu(s4, v0);
                                        at = slti(v1, 9);
                                        a1 = addiu(s4, -8);
                                        if (at == 0) {
                                            // 0x004a7c48
                                            charge(ctx, 4);
                                            at = slt(s4, v0);
                                            a0 = 0;
                                            v1 = 0;
                                            if (at == 0) {
                                                // 0x004a7c58
                                                charge(ctx, 5);
                                                at = 0x7FFF0000;
                                                at = at | 0xFFFF;
                                                at = slt(s4, at);
                                                if (at != 0) {
                                                    // 0x004a7c6c
                                                    charge(ctx, 2);
                                                    v1 = 1;
                                                }
                                            }
                                            // 0x004a7d48
                                            charge(ctx, 2);
                                            if (v1 == 0) {
                                                backedge(ctx);
                                            } else {
                                                // 0x004a7d50
                                                charge(ctx, 2);
                                                backedge(ctx);
                                                // 0x004a7c78
                                                charge(ctx, 7);
                                                v1 = 0x960000;
                                                lw(v1, v1, -1656);  // 0x95F988
                                                at = 0x7FFF0000;
                                                at = at | 0xFFFF;
                                                at = slt(v1, at);
                                                if (at != 0) {
                                                    // 0x004a7c94
                                                    charge(ctx, 1);
                                                    a0 = 1;
                                                }
                                            }
                                            // 0x004a7c98
                                            charge(ctx, 2);
                                            if (a0 != 0) {
                                                // 0x004a7ca0
                                                charge(ctx, 4);
                                                v1 = sll(v0, 2);
                                                a0 = si(-1);
                                                a2 = addu(s5, v1);
                                                for (;;) {
                                                    // 0x004a7cb0
                                                    charge(ctx, 12);
                                                    sw(a0, a2, 0);
                                                    sw(a0, a2, 4);
                                                    v0 = addiu(v0, 8);
                                                    sw(a0, a2, 8);
                                                    v1 = slt(v0, a1);
                                                    sw(a0, a2, 12);
                                                    sw(a0, a2, 16);
                                                    sw(a0, a2, 20);
                                                    sw(a0, a2, 24);
                                                    sw(a0, a2, 28);
                                                    a2 = addiu(a2, 32);
                                                    if (v1 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                            }
                                        }
                                        // 0x004a7ce0
                                        charge(ctx, 3);
                                        at = slt(v0, s4);
                                        if (at != 0) {
                                            // 0x004a7cec
                                            charge(ctx, 3);
                                            v1 = sll(v0, 2);
                                            a0 = si(-1);
                                            a1 = addu(s5, v1);
                                            for (;;) {
                                                // 0x004a7cf8
                                                charge(ctx, 7);
                                                v0 = addiu(v0, 1);
                                                sw(a0, a1, 0);
                                                v1 = slt(v0, s4);
                                                a1 = addiu(a1, 4);
                                                if (v1 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004a7d14
                                            charge(ctx, 1);
                                        }
                                    }
                                    // 0x004a7d18
                                    charge(ctx, 2);
                                    if (s0 != 0) {
                                        // 0x004a7d20
                                        charge(ctx, 4);
                                        lq(v0, sp, 0xB0);
                                        lw(v0, v0, 0);
                                        a0 = s0;
                                        jalr(ctx, 0x4A7D28u, v0.u());
                                    }
                                    // 0x004a7d30
                                    charge(ctx, 6);
                                    v1 = 0x960000;
                                    v0 = 0x960000;
                                    s0 = s5;
                                    sw(s5, v1, -1660);  // 0x95F984
                                    sw(s4, v0, -1656);  // 0x95F988
                                    backedge(ctx);
                                } else {
                                    // 0x004a7ab4
                                    charge(ctx, 1);
                                }
                                // 0x004a7ab8
                                charge(ctx, 4);
                                lw(v0, sp, 0x128);
                                at = slti(v0, 128);
                                if (at == 0) {
                                    // 0x004a7d58
                                    charge(ctx, 7);
                                    lw(v1, s3, 16);
                                    v0 = addu(s0, fp);
                                    v1 = v1 | 0x2;
                                    sw(v1, s3, 16);
                                    lw(v1, sp, 0x128);
                                    sw(v1, v0, 0);
                                    backedge(ctx);
                                } else {
                                    // 0x004a7ac8
                                    charge(ctx, 4);
                                    v1 = sll(v0, 1);
                                    lq(v0, sp, 0xD0);
                                    v0 = addu(v0, v1);
                                    sh(s1, v0, 0);
                                }
                                // 0x004a7ad8
                                charge(ctx, 48);
                                v0 = sll(s1, 5);
                                lwc1(f0, sp, 0x124);
                                a3 = addu(s7, v0);
                                v0 = 0x3F000000;
                                s1 = addiu(s1, 1);
                                mtc1(v0, f1);
                                fp = addiu(fp, 0x4);
                                v1 = slt(s1, s2);
                                lw(v0, sp, 0xF0);
                                cvt_s_w(f0, f0);
                                v0 = addiu(v0, 32);
                                sw(v0, sp, 0xF0);
                                add_s(f0, f1, f0);
                                lw(v0, sp, 0x108);
                                mul_s(f0, f0, f21);
                                swc1(f0, a3, 8);
                                lwc1(f0, sp, 0x11C);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                mul_s(f0, f0, f20);
                                swc1(f0, a3, 12);
                                lwc1(f0, sp, 0x120);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                mul_s(f0, f0, f21);
                                swc1(f0, a3, 16);
                                lwc1(f0, sp, 0x118);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                mul_s(f0, f0, f20);
                                swc1(f0, a3, 20);
                                sw(v0, a3, 4);
                                lw(a2, sp, 0x120);
                                lw(a1, sp, 0x124);
                                lw(a0, sp, 0x118);
                                lw(v0, sp, 0x11C);
                                a1 = subu(a2, a1);
                                mtc1(a1, f0);
                                v0 = subu(a0, v0);
                                cvt_s_w(f1, f0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                                swc1(f0, a3, 0);
                                sb(zero, a3, 28);
                                if (v1 != 0) {
                                    backedge(ctx);
                                } else {
                                    // 0x004a7b98
                                    charge(ctx, 16);
                                    lw(a0, s3, 308);
                                    v0 = 0x30000;
                                    a1 = 32;
                                    a2 = v0 | 0x190;
                                    jal(ctx, 0x4A7BA4u, gen::fn_sub_4C1F70_004c1f70);
                                    link(ctx, 0x4A7BACu);  // $ra first: the delay slot below depends on it
                                    lw(a0, s3, 308);
                                    call(ctx, gen::fn_sub_4C2090_004c2090);
                                    s7 = v0;
                                    a1 = 0;
                                    lw(v0, sp, 0xF0);
                                    a2 = 1024;
                                    s2 = addiu(s2, 32);
                                    a0 = addu(s7, v0);
                                    jal(ctx, 0x4A7BC8u, gen::fn_memset_00521408);
                                    backedge(ctx);
                                }
                            } else {
                                // 0x004a7a98
                                charge(ctx, 2);
                                s6 = 0;
                                backedge(ctx);
                            }
                        }
                        continue;
                    }
                }
                break;
            }
            // 0x004a7d78
            charge(ctx, 2);
            if (s6 == s3) {
                // 0x004a7d80
                charge(ctx, 7);
                a0 = s3;
                link(ctx, 0x4A7D84u);  // $ra first: the delay slot below depends on it
                sw(s1, s3, 304);
                call(ctx, gen::fn_sub_4A7620_004a7620);
                v0 = 0x960000;
                lw(a0, v0, -1660);  // 0x95F984
                if (a0 != 0) {
                    // 0x004a7d9c
                    charge(ctx, 5);
                    v0 = 0x960000;
                    a1 = si(-1);
                    lw(v0, v0, -1656);  // 0x95F988
                    a2 = sll(v0, 2);
                    jal(ctx, 0x4A7DA8u, gen::fn_memset_00521408);
                }
                // 0x004a7db0
                charge(ctx, 17);
                lw(a0, sp, 0x118);
                v0 = 0x470000;
                lw(v1, sp, 0x11C);
                v0 = addiu(v0, -16464);  // &sub_46BFB0
                v1 = subu(a0, v1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                swc1(f0, s3, 4);
                lwc1(f1, sp, 0x12C);
                lwc1(f0, s3, 4);
                cvt_s_w(f1, f1);
                div_s(f0, f1, f0);
                swc1(f0, s3, 8);
                sw(zero, s3, 12);
                sw(v0, s3, 312);
            }
        }
    }
    // 0x004a7df8
    charge(ctx, 17);
    link(ctx, 0x4A7DF8u);  // $ra first: the delay slot below depends on it
    lw(a0, sp, 0x10C);
    call(ctx, gen::fn_sub_4D11D0_004d11d0);
    v0 = s6;
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lwc1(f21, sp, 0x4);
    lq(s7, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x130);
}

// sub_4A7E40 [rt2dFontReadMetrics2] -- reads a METRICS2 font: up to four texture pages, each image scanned (memcmp of
//   pixel columns against the page's border colour) to find the glyph cells left to right, top to bottom, each cell a
//   glyph with its UVs and width, the character codes from the font file; the font, or 0
// 0x004A7E40 sub_4A7E40 -- 2872 bytes; frame 0x210: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0, s6 sp+0x1B4
void sub_4A7E40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004a7e40
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    s6 = a0;
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a3;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    sw(a1, sp, 0x208);
    swc1(f21, sp, 0x4);
    sw(a2, sp, 0x204);
    swc1(f20, sp, 0x0);
    link(ctx, 0x4A7E88u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x1D0);
    call(ctx, gen::fn_sub_4D11F0_004d11f0);
    sw(v0, sp, 0x1B8);
    v0 = 0x960000;
    link(ctx, 0x4A7E98u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4736);
    call(ctx, gen::fn_sub_4D11D0_004d11d0);
    sw(zero, s6, 0);
    s7 = 0;
    lw(v0, s6, 304);
    sw(s6, sp, 0x1B4);
    sw(v0, sp, 0x1C0);
    if (v0 == 0) {
        // 0x004a7eb8
        charge(ctx, 2);
        v0 = 256;
        sw(v0, sp, 0x1C0);
    }
    // 0x004a7ec0
    charge(ctx, 38);
    v0 = addiu(s6, 36);
    lw(a0, s6, 308);
    sq(v0, sp, 0x130);
    s1 = 0;
    v0 = 0x960000;
    lw(a1, sp, 0x1C0);
    lw(s2, v0, -1660);  // 0x95F984
    v0 = 0x30000;
    a2 = v0 | 0x190;
    jal(ctx, 0x4A7EE0u, gen::fn_sub_4C1F70_004c1f70);
    link(ctx, 0x4A7EE8u);  // $ra first: the delay slot below depends on it
    lw(a0, s6, 308);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    sw(v0, sp, 0x1BC);
    a1 = 0;
    lw(v0, sp, 0x1C0);
    lw(a0, sp, 0x1BC);
    a2 = sll(v0, 5);
    jal(ctx, 0x4A7F00u, gen::fn_memset_00521408);
    v0 = 0x960000;
    sw(zero, sp, 0x200);
    v0 = addiu(v0, -2684);  // &0x95F584
    sw(zero, sp, 0x1F8);
    sw(v0, sp, 0x1E0);
    v0 = 0x960000;
    sw(zero, sp, 0x1FC);
    v0 = addiu(v0, 372);  // &0x960174
    sw(zero, sp, 0x170);
    sq(v0, sp, 0x120);
    v0 = 0x960000;
    sw(zero, sp, 0x160);
    v0 = addiu(v0, 356);  // &0x960164
    sq(v0, sp, 0x110);
    v0 = 0x960000;
    v0 = addiu(v0, 376);  // &0x960178
    sq(v0, sp, 0x100);
    v0 = 0x960000;
    v0 = addiu(v0, 380);  // &0x96017C
    sq(v0, sp, 0xF0);
    for (;;) {
        // 0x004a7f58
        charge(ctx, 4);
        lw(v0, sp, 0x1D0);
        v0 = sltiu(v0, 4);
        if (v0 == 0) {
            break;
        }
        // 0x004a7f98
        charge(ctx, 6);
        lw(a2, sp, 0x204);
        a0 = s4;
        a1 = 256;
        jal(ctx, 0x4A7FA0u, gen::fn_sub_4C0550_004c0550);
        if (v0 == 0) {
            backedge(ctx);
            break;
        }
        // 0x004a7fb0
        charge(ctx, 2);
        lq(v0, sp, 0x120);
        // 0x004a8068
        charge(ctx, 9);
        a0 = s4;
        lw(a2, sp, 0x208);
        lw(a3, sp, 0x1E0);
        lw(v0, v0, 0);
        a1 = addiu(gp, -20608);  // "%s %s\n"
        jalr(ctx, 0x4A8078u, v0.u());
        s0 = v0;
        if (s0 == 0) {
            goto L_004a808c_22;
        }
        backedge(ctx);
        // 0x004a7fb8
        charge(ctx, 3);
        v0 = 1;
        if (s0 != v0) {
            // 0x004a7fc4
            charge(ctx, 3);
            v0 = 2;
            if (s0 == v0) {
                goto L_004a7fd0;
            }
            backedge(ctx);
            break;
        }
    L_004a7fd0:
        charge(ctx, 6);
        v0 = 0x960000;
        link(ctx, 0x4A7FD4u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, -4756);
        call(ctx, gen::fn_sub_4CC5C0_004cc5c0);
        v0 = 1;
        if (s0 != v0) {
            // 0x004a7ffc
            charge(ctx, 4);
            lw(a1, sp, 0x1E0);
            link(ctx, 0x4A8000u);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x208);
            call(ctx, gen::fn_sub_4D1260_004d1260);
            sq(v0, sp, 0xE0);
        } else {
            // 0x004a7fe8
            charge(ctx, 5);
            lw(a0, sp, 0x208);
            a1 = 0;
            jal(ctx, 0x4A7FECu, gen::fn_sub_4D1260_004d1260);
            sq(v0, sp, 0xE0);
        }
        // 0x004a800c
        charge(ctx, 3);
        lq(v0, sp, 0xE0);
        if (v0 == 0) {
            // 0x004a88ec
            charge(ctx, 4);
            v0 = 4;
            sw(zero, sp, 0x1B4);
            sw(v0, sp, 0x1D0);
            backedge(ctx);
        } else {
            // 0x004a8018
            charge(ctx, 10);
            lw(v0, sp, 0x1D0);
            v0 = sll(v0, 2);
            v1 = addu(s6, v0);
            lq(v0, sp, 0xE0);
            sw(v0, v1, 20);
            lw(fp, v0, 0);
            lw(v0, sp, 0x200);
            lw(s0, fp, 0x10);
            lw(s5, fp, 0xC);
            if (v0 != 0) {
                // 0x004a8040
                charge(ctx, 3);
                lw(v0, sp, 0x1FC);
                if (v0 != s5) {
                    // 0x004a8094
                    charge(ctx, 3);
                    link(ctx, 0x4A8094u);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x200);
                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                    sw(zero, sp, 0x200);
                } else {
                    // 0x004a804c
                    charge(ctx, 3);
                    lw(v0, sp, 0x1F8);
                    if (v0 != s0) {
                        // 0x004a8058
                        charge(ctx, 4);
                        link(ctx, 0x4A8058u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x200);
                        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                        sw(zero, sp, 0x200);
                    }
                }
            }
            // 0x004a80a0
            charge(ctx, 3);
            lw(v0, sp, 0x200);
            if (v0 == 0) {
                // 0x004a85e0
                charge(ctx, 9);
                a0 = s5;
                a1 = s0;
                a2 = 32;
                jal(ctx, 0x4A85E8u, gen::fn_sub_4CBE00_004cbe00);
                sw(v0, sp, 0x200);
                a0 = v0;
                jal(ctx, 0x4A85F4u, gen::fn_sub_4CBF20_004cbf20);
                lw(a0, sp, 0x200);
                backedge(ctx);
            } else {
                // 0x004a80ac
                charge(ctx, 1);
                lw(a0, sp, 0x200);
            }
            // 0x004a80b0
            charge(ctx, 37);
            a1 = fp;
            jal(ctx, 0x4A80B0u, gen::fn_sub_4CDC70_004cdc70);
            mtc1(s5, f0);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            lw(a2, sp, 0x204);
            cvt_s_w(f0, f0);
            a0 = s4;
            a1 = 256;
            sw(s5, sp, 0x1FC);
            sw(s0, sp, 0x1F8);
            div_s(f22, f1, f0);
            mtc1(s0, f0);
            cvt_s_w(f0, f0);
            div_s(f21, f1, f0);
            jal(ctx, 0x4A80F8u, gen::fn_sub_4C0550_004c0550);
            lq(v0, sp, 0x120);
            a0 = s4;
            a1 = addiu(gp, -20588);  // "%d"
            lw(v0, v0, 0);
            a2 = addiu(sp, 0x20C);
            jalr(ctx, 0x4A8110u, v0.u());
            lw(v0, sp, 0x200);
            at = slti(s0, 2);
            sw(zero, sp, 0x19C);
            s5 = 1;
            lw(v0, v0, 20);
            sw(v0, sp, 0x180);
            lw(v0, sp, 0x200);
            lw(v0, v0, 12);
            v0 = sra(v0, 3);
            sw(v0, sp, 0x1A0);
            if (at == 0) {
                for (;;) {
                    // 0x004a8604
                    charge(ctx, 10);
                    lw(v0, sp, 0x200);
                    lw(v0, v0, 16);
                    mult(v1, v0, s5);
                    lw(a0, sp, 0x180);
                    lw(a2, sp, 0x1A0);
                    v0 = a0;
                    a1 = addu(v0, v1);
                    jal(ctx, 0x4A861Cu, gen::fn_memcmp_005211b8);
                    if (v0 == 0) {
                        goto L_004a862c_68;
                    }
                    // 0x004a8634
                    charge(ctx, 4);
                    s5 = addiu(s5, 1);
                    v0 = slt(s5, s0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a8644
                charge(ctx, 2);
                lw(v0, sp, 0x19C);
                backedge(ctx);
                goto L_004a8148;
            }
        L_004a8144:
            charge(ctx, 1);
            lw(v0, sp, 0x19C);
        L_004a8148:
            charge(ctx, 2);
            if (i64(v0) <= 0) {
                // 0x004a88dc
                charge(ctx, 4);
                v0 = 4;
                sw(zero, sp, 0x1B4);
                sw(v0, sp, 0x1D0);
                backedge(ctx);
            } else {
                // 0x004a8150
                charge(ctx, 3);
                v0 = addiu(s4, -1);
                sw(zero, sp, 0x140);
                sq(v0, sp, 0xD0);
                for (;;) {
                    // 0x004a815c
                    charge(ctx, 5);
                    lw(v1, sp, 0x140);
                    lw(v0, sp, 0x1F8);
                    at = slt(v1, v0);
                    if (at != 0) {
                        // 0x004a8170
                        charge(ctx, 3);
                        lw(v0, sp, 0x1B4);
                        if (v0 == s6) {
                            // 0x004a817c
                            charge(ctx, 15);
                            v0 = v1;
                            sw(zero, sp, 0x198);
                            mtc1(v0, f0);
                            fp = 0x1;
                            lw(v0, sp, 0x1A0);
                            cvt_s_w(f0, f0);
                            sw(v0, sp, 0x150);
                            lw(v0, sp, 0x19C);
                            v0 = addu(v1, v0);
                            sq(v0, sp, 0xC0);
                            v0 = 0x40200000;
                            mtc1(v0, f1);
                            add_s(f0, f1, f0);
                            mul_s(f20, f0, f21);
                            for (;;) {
                                // 0x004a81b8
                                charge(ctx, 4);
                                lw(v0, sp, 0x1FC);
                                at = slt(fp, v0);
                                if (at != 0) {
                                    // 0x004a81c8
                                    charge(ctx, 3);
                                    lw(v0, sp, 0x1B4);
                                    if (v0 == s6) {
                                        // 0x004a81d4
                                        charge(ctx, 13);
                                        lw(v0, sp, 0x200);
                                        lw(v1, v0, 16);
                                        lw(v0, sp, 0x140);
                                        mult(v1, v1, v0);
                                        lw(a0, sp, 0x180);
                                        lw(a2, sp, 0x1A0);
                                        v0 = a0;
                                        v1 = addu(v0, v1);
                                        lw(v0, sp, 0x150);
                                        a1 = addu(v1, v0);
                                        jal(ctx, 0x4A81F8u, gen::fn_memcmp_005211b8);
                                        if (v0 == 0) {
                                            // 0x004a8208
                                            charge(ctx, 5);
                                            lw(v0, sp, 0x198);
                                            v1 = 1;
                                            v0 = subu(fp, v0);
                                            sq(v0, sp, 0xB0);
                                            if (v0 == v1) {
                                                break;
                                            }
                                            // 0x004a821c
                                            charge(ctx, 2);
                                            if (s1 != 0) {
                                                // 0x004a8224
                                                charge(ctx, 4);
                                                lb(v1, s1, 0);
                                                v0 = 10;
                                                if (v1 == v0) {
                                                    goto L_004a864c;
                                                }
                                                // 0x004a8234
                                                charge(ctx, 2);
                                                if (v1 == 0) {
                                                    goto L_004a864c;
                                                }
                                                // 0x004a823c
                                                charge(ctx, 4);
                                                v0 = subu(s1, s4);
                                                at = slti(v0, 128);
                                                if (at == 0) {
                                                    // 0x004a8668
                                                    charge(ctx, 10);
                                                    lq(v0, sp, 0x110);
                                                    lw(v0, v0, 0);
                                                    a0 = s1;
                                                    jalr(ctx, 0x4A8670u, v0.u());
                                                    s0 = v0;
                                                    v1 = addu(s1, s0);
                                                    v0 = 255;
                                                    v1 = subu(v1, s4);
                                                    if (v1 != v0) {
                                                        backedge(ctx);
                                                    } else {
                                                        // 0x004a8690
                                                        charge(ctx, 10);
                                                        a1 = s1;
                                                        a2 = addiu(s0, 1);
                                                        a0 = s4;
                                                        jal(ctx, 0x4A8698u, gen::fn_memcpy_00521250);
                                                        lq(v0, sp, 0xD0);
                                                        v0 = addu(v0, s0);
                                                        lb(v1, v0, 0);
                                                        v0 = 10;
                                                        s1 = s4;
                                                        if (v1 == v0) {
                                                            // 0x004a86b8
                                                            charge(ctx, 2);
                                                            s0 = addiu(s0, -1);
                                                        }
                                                        // 0x004a86c0
                                                        charge(ctx, 7);
                                                        lw(a2, sp, 0x204);
                                                        v0 = 256;
                                                        a0 = addu(s4, s0);
                                                        a1 = subu(v0, s0);
                                                        jal(ctx, 0x4A86CCu, gen::fn_sub_4C0550_004c0550);
                                                        backedge(ctx);
                                                    }
                                                } else {
                                                    // 0x004a824c
                                                    charge(ctx, 3);
                                                    v0 = slti(v0, 128);
                                                    if (v0 == 0) {
                                                        // 0x004a8258
                                                        charge(ctx, 15);
                                                        lq(v0, sp, 0x110);
                                                        lw(v0, v0, 0);
                                                        a0 = s1;
                                                        jalr(ctx, 0x4A8260u, v0.u());
                                                        s0 = v0;
                                                        a1 = s1;
                                                        a2 = addiu(s0, 1);
                                                        a0 = s4;
                                                        jal(ctx, 0x4A8274u, gen::fn_memcpy_00521250);
                                                        lq(v0, sp, 0xD0);
                                                        v0 = addu(v0, s0);
                                                        lb(v1, v0, 0);
                                                        v0 = 10;
                                                        s1 = s4;
                                                        if (v1 == v0) {
                                                            // 0x004a8294
                                                            charge(ctx, 1);
                                                            s0 = addiu(s0, -1);
                                                        }
                                                        // 0x004a8298
                                                        charge(ctx, 6);
                                                        lw(a2, sp, 0x204);
                                                        v0 = 256;
                                                        a0 = addu(s4, s0);
                                                        a1 = subu(v0, s0);
                                                        jal(ctx, 0x4A82A4u, gen::fn_sub_4C0550_004c0550);
                                                    }
                                                }
                                                goto L_004a82b0;
                                            }
                                        L_004a864c:
                                            charge(ctx, 6);
                                            lw(a2, sp, 0x204);
                                            a0 = s4;
                                            a1 = 256;
                                            jal(ctx, 0x4A8654u, gen::fn_sub_4C0550_004c0550);
                                            s1 = s4;
                                            backedge(ctx);
                                        L_004a82b0:
                                            charge(ctx, 4);
                                            lb(a0, s1, 0);
                                            v0 = a0 & 0x80;
                                            if (v0 == 0) {
                                                // 0x004a86e0
                                                charge(ctx, 3);
                                                s3 = a0;
                                                v0 = 1;
                                                backedge(ctx);
                                            } else {
                                                // 0x004a82c0
                                                charge(ctx, 4);
                                                v1 = a0 & 0xE0;
                                                v0 = 192;
                                                if (v1 != v0) {
                                                    // 0x004a82f0
                                                    charge(ctx, 4);
                                                    v1 = a0 & 0xF0;
                                                    v0 = 224;
                                                    if (v1 != v0) {
                                                        // 0x004a8330
                                                        charge(ctx, 4);
                                                        v1 = a0 & 0xF8;
                                                        v0 = 240;
                                                        if (v1 != v0) {
                                                            // 0x004a8380
                                                            charge(ctx, 4);
                                                            v1 = a0 & 0xFC;
                                                            v0 = 248;
                                                            if (v1 != v0) {
                                                                // 0x004a83e0
                                                                charge(ctx, 4);
                                                                v1 = a0 & 0xFE;
                                                                v0 = 252;
                                                                if (v1 != v0) {
                                                                    // 0x004a86f0
                                                                    charge(ctx, 2);
                                                                    v0 = si(-1);
                                                                    backedge(ctx);
                                                                } else {
                                                                    // 0x004a83f0
                                                                    charge(ctx, 22);
                                                                    lb(t0, s1, 1);
                                                                    v0 = a0 & 0x1;
                                                                    lb(a2, s1, 2);
                                                                    a3 = sll(v0, 30);
                                                                    lb(a1, s1, 3);
                                                                    v0 = 6;
                                                                    lb(a0, s1, 4);
                                                                    lb(v1, s1, 5);
                                                                    t0 = t0 & 0x3F;
                                                                    t0 = sll(t0, 24);
                                                                    a2 = a2 & 0x3F;
                                                                    a1 = a1 & 0x3F;
                                                                    a3 = a3 | t0;
                                                                    a2 = sll(a2, 18);
                                                                    a0 = a0 & 0x3F;
                                                                    a2 = a2 | a3;
                                                                    a1 = sll(a1, 12);
                                                                    a1 = a1 | a2;
                                                                    a0 = sll(a0, 6);
                                                                    a0 = a0 | a1;
                                                                    v1 = v1 & 0x3F;
                                                                    s3 = v1 | a0;
                                                                }
                                                            } else {
                                                                // 0x004a8390
                                                                charge(ctx, 19);
                                                                lb(a3, s1, 1);
                                                                v0 = a0 & 0x3;
                                                                lb(a1, s1, 2);
                                                                a2 = sll(v0, 24);
                                                                lb(a0, s1, 3);
                                                                v0 = 5;
                                                                lb(v1, s1, 4);
                                                                a3 = a3 & 0x3F;
                                                                a3 = sll(a3, 18);
                                                                a1 = a1 & 0x3F;
                                                                a0 = a0 & 0x3F;
                                                                a2 = a2 | a3;
                                                                a1 = sll(a1, 12);
                                                                a0 = sll(a0, 6);
                                                                a1 = a1 | a2;
                                                                v1 = v1 & 0x3F;
                                                                a0 = a0 | a1;
                                                                s3 = v1 | a0;
                                                            }
                                                        } else {
                                                            // 0x004a8340
                                                            charge(ctx, 15);
                                                            v0 = a0 & 0x7;
                                                            lb(a2, s1, 1);
                                                            lb(a0, s1, 2);
                                                            a1 = sll(v0, 18);
                                                            lb(v1, s1, 3);
                                                            v0 = 4;
                                                            a2 = a2 & 0x3F;
                                                            a2 = sll(a2, 12);
                                                            a0 = a0 & 0x3F;
                                                            a1 = a1 | a2;
                                                            a0 = sll(a0, 6);
                                                            a0 = a0 | a1;
                                                            v1 = v1 & 0x3F;
                                                            s3 = v1 | a0;
                                                        }
                                                    } else {
                                                        // 0x004a8300
                                                        charge(ctx, 11);
                                                        lb(a1, s1, 1);
                                                        v0 = a0 & 0xF;
                                                        lb(v1, s1, 2);
                                                        a0 = sll(v0, 12);
                                                        v0 = 3;
                                                        a1 = a1 & 0x3F;
                                                        a1 = sll(a1, 6);
                                                        v1 = v1 & 0x3F;
                                                        a0 = a0 | a1;
                                                        s3 = v1 | a0;
                                                    }
                                                } else {
                                                    // 0x004a82d0
                                                    charge(ctx, 7);
                                                    lb(v1, s1, 1);
                                                    v0 = a0 & 0x1F;
                                                    a0 = sll(v0, 6);
                                                    v0 = 2;
                                                    v1 = v1 & 0x3F;
                                                    s3 = a0 | v1;
                                                }
                                            }
                                            // 0x004a8448
                                            charge(ctx, 2);
                                            if (i64(v0) > 0) {
                                                // 0x004a8450
                                                charge(ctx, 4);
                                                at = 0x10000;
                                                at = slt(s3, at);
                                                if (at == 0) {
                                                    goto L_004a8860;
                                                }
                                                // 0x004a8460
                                                charge(ctx, 6);
                                                s1 = addu(s1, v0);
                                                v0 = 0x960000;
                                                lw(v0, v0, -1656);  // 0x95F988
                                                at = slt(s7, v0);
                                                if (at == 0) {
                                                    // 0x004a86f8
                                                    charge(ctx, 19);
                                                    s0 = addiu(v0, 32);
                                                    v0 = 0x30000;
                                                    a1 = v0 | 0x190;
                                                    lq(v0, sp, 0x100);
                                                    lw(v0, v0, 0);
                                                    a0 = sll(s0, 2);
                                                    jalr(ctx, 0x4A870Cu, v0.u());
                                                    s5 = v0;
                                                    a1 = s2;
                                                    v0 = 0x960000;
                                                    a0 = s5;
                                                    lw(v0, v0, -1656);  // 0x95F988
                                                    a2 = sll(v0, 2);
                                                    jal(ctx, 0x4A8728u, gen::fn_memcpy_00521250);
                                                    v0 = 0x960000;
                                                    lw(v0, v0, -1656);  // 0x95F988
                                                    at = slt(v0, s0);
                                                    if (at != 0) {
                                                        // 0x004a8744
                                                        charge(ctx, 4);
                                                        v1 = subu(s0, v0);
                                                        at = slti(v1, 9);
                                                        a1 = addiu(s0, -8);
                                                        if (at == 0) {
                                                            // 0x004a8754
                                                            charge(ctx, 4);
                                                            at = slt(s0, v0);
                                                            a0 = 0;
                                                            v1 = 0;
                                                            if (at == 0) {
                                                                // 0x004a8764
                                                                charge(ctx, 5);
                                                                at = 0x7FFF0000;
                                                                at = at | 0xFFFF;
                                                                at = slt(s0, at);
                                                                if (at != 0) {
                                                                    // 0x004a8778
                                                                    charge(ctx, 2);
                                                                    v1 = 1;
                                                                }
                                                            }
                                                            // 0x004a8850
                                                            charge(ctx, 2);
                                                            if (v1 == 0) {
                                                                backedge(ctx);
                                                            } else {
                                                                // 0x004a8858
                                                                charge(ctx, 2);
                                                                backedge(ctx);
                                                                // 0x004a8780
                                                                charge(ctx, 7);
                                                                v1 = 0x960000;
                                                                lw(v1, v1, -1656);  // 0x95F988
                                                                at = 0x7FFF0000;
                                                                at = at | 0xFFFF;
                                                                at = slt(v1, at);
                                                                if (at != 0) {
                                                                    // 0x004a879c
                                                                    charge(ctx, 1);
                                                                    a0 = 1;
                                                                }
                                                            }
                                                            // 0x004a87a0
                                                            charge(ctx, 2);
                                                            if (a0 != 0) {
                                                                // 0x004a87a8
                                                                charge(ctx, 4);
                                                                v1 = sll(v0, 2);
                                                                a0 = si(-1);
                                                                a2 = addu(s5, v1);
                                                                for (;;) {
                                                                    // 0x004a87b8
                                                                    charge(ctx, 12);
                                                                    sw(a0, a2, 0);
                                                                    sw(a0, a2, 4);
                                                                    v0 = addiu(v0, 8);
                                                                    sw(a0, a2, 8);
                                                                    v1 = slt(v0, a1);
                                                                    sw(a0, a2, 12);
                                                                    sw(a0, a2, 16);
                                                                    sw(a0, a2, 20);
                                                                    sw(a0, a2, 24);
                                                                    sw(a0, a2, 28);
                                                                    a2 = addiu(a2, 32);
                                                                    if (v1 == 0) {
                                                                        break;
                                                                    }
                                                                    backedge(ctx);
                                                                }
                                                            }
                                                        }
                                                        // 0x004a87e8
                                                        charge(ctx, 3);
                                                        at = slt(v0, s0);
                                                        if (at != 0) {
                                                            // 0x004a87f4
                                                            charge(ctx, 3);
                                                            v1 = sll(v0, 2);
                                                            a0 = si(-1);
                                                            a1 = addu(s5, v1);
                                                            for (;;) {
                                                                // 0x004a8800
                                                                charge(ctx, 7);
                                                                v0 = addiu(v0, 1);
                                                                sw(a0, a1, 0);
                                                                v1 = slt(v0, s0);
                                                                a1 = addiu(a1, 4);
                                                                if (v1 == 0) {
                                                                    break;
                                                                }
                                                                backedge(ctx);
                                                            }
                                                            // 0x004a881c
                                                            charge(ctx, 1);
                                                        }
                                                    }
                                                    // 0x004a8820
                                                    charge(ctx, 2);
                                                    if (s2 != 0) {
                                                        // 0x004a8828
                                                        charge(ctx, 4);
                                                        lq(v0, sp, 0xF0);
                                                        lw(v0, v0, 0);
                                                        a0 = s2;
                                                        jalr(ctx, 0x4A8830u, v0.u());
                                                    }
                                                    // 0x004a8838
                                                    charge(ctx, 6);
                                                    v1 = 0x960000;
                                                    v0 = 0x960000;
                                                    s2 = s5;
                                                    sw(s5, v1, -1660);  // 0x95F984
                                                    sw(s0, v0, -1656);  // 0x95F988
                                                    backedge(ctx);
                                                }
                                                // 0x004a8478
                                                charge(ctx, 3);
                                                v0 = slti(s3, 128);
                                                if (v0 != 0) {
                                                    // 0x004a84a0
                                                    charge(ctx, 4);
                                                    lq(v0, sp, 0x130);
                                                    v1 = sll(s3, 1);
                                                    v0 = addu(v0, v1);
                                                    sh(s7, v0, 0);
                                                } else {
                                                    // 0x004a8484
                                                    charge(ctx, 7);
                                                    lw(v1, s6, 16);
                                                    lw(v0, sp, 0x170);
                                                    v1 = v1 | 0x2;
                                                    v0 = addu(s2, v0);
                                                    sw(v1, s6, 16);
                                                    sw(s3, v0, 0);
                                                }
                                                // 0x004a84b0
                                                charge(ctx, 51);
                                                lq(v0, sp, 0xB0);
                                                a0 = sll(s7, 5);
                                                a2 = 0x40200000;
                                                a1 = 0x3F000000;
                                                s7 = addiu(s7, 1);
                                                mtc1(a2, f4);
                                                mtc1(a1, f3);
                                                v1 = addiu(v0, -3);
                                                lw(v0, sp, 0x198);
                                                mtc1(v1, f1);
                                                lq(v1, sp, 0xC0);
                                                cvt_s_w(f1, f1);
                                                mtc1(v0, f0);
                                                lw(v0, sp, 0x1BC);
                                                cvt_s_w(f2, f0);
                                                a3 = addu(v0, a0);
                                                lw(v0, sp, 0x140);
                                                add_s(f2, f4, f2);
                                                mul_s(f2, f2, f22);
                                                v0 = subu(v1, v0);
                                                a0 = addiu(v0, -3);
                                                lw(v0, sp, 0x170);
                                                mtc1(a0, f0);
                                                swc1(f2, a3, 8);
                                                cvt_s_w(f0, f0);
                                                v0 = addiu(v0, 4);
                                                sw(v0, sp, 0x170);
                                                lw(v0, sp, 0x160);
                                                div_s(f0, f1, f0);
                                                v0 = addiu(v0, 32);
                                                sw(v0, sp, 0x160);
                                                lw(v0, sp, 0x1C0);
                                                v1 = slt(s7, v0);
                                                lq(v0, sp, 0xC0);
                                                mtc1(v0, f1);
                                                mtc1(fp, f2);
                                                cvt_s_w(f1, f1);
                                                lq(v0, sp, 0xE0);
                                                cvt_s_w(f2, f2);
                                                sub_s(f2, f2, f3);
                                                sub_s(f1, f1, f3);
                                                mul_s(f2, f2, f22);
                                                swc1(f20, a3, 12);
                                                mul_s(f1, f1, f21);
                                                swc1(f2, a3, 16);
                                                swc1(f1, a3, 20);
                                                sw(v0, a3, 4);
                                                lw(v0, sp, 0x1D0);
                                                swc1(f0, a3, 0);
                                                sb(v0, a3, 28);
                                                if (v1 == 0) {
                                                    // 0x004a857c
                                                    charge(ctx, 17);
                                                    lw(a0, s6, 308);
                                                    v0 = 0x30000;
                                                    a1 = 32;
                                                    a2 = v0 | 0x190;
                                                    jal(ctx, 0x4A8588u, gen::fn_sub_4C1F70_004c1f70);
                                                    link(ctx, 0x4A8590u);  // $ra first: the delay slot below depends on it
                                                    lw(a0, s6, 308);
                                                    call(ctx, gen::fn_sub_4C2090_004c2090);
                                                    sw(v0, sp, 0x1BC);
                                                    a1 = 0;
                                                    lw(v0, sp, 0x1C0);
                                                    a2 = 1024;
                                                    lw(v1, sp, 0x1BC);
                                                    v0 = addiu(v0, 32);
                                                    sw(v0, sp, 0x1C0);
                                                    lw(v0, sp, 0x160);
                                                    a0 = addu(v1, v0);
                                                    jal(ctx, 0x4A85B8u, gen::fn_memset_00521408);
                                                }
                                                goto L_004a85c0;
                                            }
                                        L_004a8860:
                                            charge(ctx, 4);
                                            v0 = 4;
                                            sw(v0, sp, 0x1D0);
                                            sw(zero, sp, 0x1B4);
                                            backedge(ctx);
                                        L_004a85c0:
                                            charge(ctx, 2);
                                            sw(fp, sp, 0x198);
                                            goto L_004a85c8;
                                        }
                                    L_004a85c8:
                                        charge(ctx, 6);
                                        lw(v1, sp, 0x150);
                                        lw(v0, sp, 0x1A0);
                                        fp = addiu(fp, 0x1);
                                        v1 = addu(v1, v0);
                                        sw(v1, sp, 0x150);
                                        backedge(ctx);
                                        continue;
                                    }
                                }
                                break;
                            }
                            // 0x004a8870
                            charge(ctx, 5);
                            lw(v1, sp, 0x140);
                            lw(v0, sp, 0x19C);
                            v1 = addu(v1, v0);
                            sw(v1, sp, 0x140);
                            backedge(ctx);
                            continue;
                        }
                    }
                    break;
                }
                // 0x004a8888
                charge(ctx, 21);
                lw(v0, sp, 0x19C);
                s1 = 0;
                mtc1(v0, f1);
                cvt_s_w(f1, f1);
                v0 = 0x40400000;
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                lw(v0, sp, 0x1D0);
                swc1(f0, s6, 4);
                lwc1(f1, sp, 0x20C);
                v0 = addiu(v0, 1);
                lwc1(f0, s6, 4);
                sw(v0, sp, 0x1D0);
                cvt_s_w(f1, f1);
                div_s(f0, f1, f0);
                swc1(f0, s6, 8);
                sw(zero, s6, 12);
                backedge(ctx);
            }
        }
    }
    // 0x004a7f68
    charge(ctx, 1);
    lw(v0, sp, 0x200);
L_004a7f6c:
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004a7f74
        charge(ctx, 2);
        a0 = v0;
        jal(ctx, 0x4A7F74u, gen::fn_sub_4CBEB0_004cbeb0);
    }
    // 0x004a7f7c
    charge(ctx, 3);
    lw(v0, sp, 0x1B4);
    if (v0 == s6) {
        // 0x004a88fc
        charge(ctx, 7);
        a0 = s6;
        link(ctx, 0x4A8900u);  // $ra first: the delay slot below depends on it
        sw(s7, s6, 304);
        call(ctx, gen::fn_sub_4A7620_004a7620);
        v0 = 0x960000;
        lw(a0, v0, -1660);  // 0x95F984
        if (a0 != 0) {
            // 0x004a8918
            charge(ctx, 5);
            v0 = 0x960000;
            a1 = si(-1);
            lw(v0, v0, -1656);  // 0x95F988
            a2 = sll(v0, 2);
            jal(ctx, 0x4A8924u, gen::fn_memset_00521408);
        }
        // 0x004a892c
        charge(ctx, 4);
        v0 = 0x470000;
        v0 = addiu(v0, -16464);  // &sub_46BFB0
        sw(v0, s6, 312);
        backedge(ctx);
    }
    // 0x004a7f88
    charge(ctx, 4);
    link(ctx, 0x4A7F88u);  // $ra first: the delay slot below depends on it
    lw(a0, sp, 0x1B8);
    call(ctx, gen::fn_sub_4D11D0_004d11d0);
    lw(v0, sp, 0x1B4);
    // 0x004a893c
    charge(ctx, 15);
    ld(ra, sp, 0xA0);
    lwc1(f22, sp, 0x8);
    lq(fp, sp, 0x90);
    lwc1(f21, sp, 0x4);
    lq(s7, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x210);
    return;
L_004a808c_22:
    charge(ctx, 2);
    lw(v0, sp, 0x200);
    backedge(ctx);
    goto L_004a7f6c;
L_004a862c_68:
    charge(ctx, 2);
    sw(s5, sp, 0x19C);
    backedge(ctx);
    goto L_004a8144;
}

// sub_4A8980 [rt2dFontReadMetrics3] -- reads a METRICS3 (outline) font: the font name line, then per glyph its UTF-8
//   character code line followed by path commands -- "moveto", "lineto", "curveto", "closepath" -- built into a path
//   (sub_4AC570 / sub_4AB200 / sub_4AB2C0 / sub_4AB410 / sub_4AB6A0), flattened (sub_4AC240 / sub_4AC710) and stored with
//   its advance width; the show callback is the outline one (sub_4A6CE0); the font, or 0
// 0x004A8980 sub_4A8980 -- 1900 bytes; frame 0x1C0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s4 sp+0x118
void sub_4A8980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x004a8980
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
    v0 = 1;
    sd(ra, sp, 0x90);
    a1 = 256;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(v0, a0, 0);
    s0 = 0;
    v0 = 0x3F800000;
    sw(a2, sp, 0x11C);
    sw(v0, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    a0 = s3;
    link(ctx, 0x4A89DCu);  // $ra first: the delay slot below depends on it
    sw(s4, sp, 0x118);
    call(ctx, gen::fn_sub_4C0550_004c0550);
    lw(v0, s4, 304);
    s6 = 0;
    sw(v0, sp, 0x100);
    if (v0 == 0) {
        // 0x004a89f4
        charge(ctx, 2);
        v0 = 256;
        sw(v0, sp, 0x100);
    }
    // 0x004a89fc
    charge(ctx, 27);
    v0 = addiu(s4, 36);
    lw(a1, sp, 0x100);
    sq(v0, sp, 0xC0);
    v0 = 0x960000;
    lw(a0, s4, 308);
    lw(s1, v0, -1660);  // 0x95F984
    v0 = 0x30000;
    a2 = v0 | 0x190;
    jal(ctx, 0x4A8A18u, gen::fn_sub_4C1F70_004c1f70);
    link(ctx, 0x4A8A20u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 308);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    sw(v0, sp, 0xFC);
    a1 = 0;
    lw(v0, sp, 0x100);
    lw(a0, sp, 0xFC);
    a2 = sll(v0, 5);
    jal(ctx, 0x4A8A38u, gen::fn_memset_00521408);
    s7 = 0x960000;
    a0 = s3;
    s7 = addiu(s7, 372);  // &0x960174
    a1 = addiu(gp, -20584);  // "%[^\n]"
    lw(v0, s7, 0);  // 0x960174
    a2 = addiu(sp, 0x120);
    jalr(ctx, 0x4A8A54u, v0.u());
    v1 = 1;
    if (v0 == v1) {
        // 0x004a8a68
        charge(ctx, 11);
        v0 = 0x960000;
        fp = 0x960000;
        v0 = addiu(v0, 376);  // &0x960178
        s2 = 0;
        sq(v0, sp, 0xB0);
        fp = addiu(fp, 0x158);
        v0 = 0x960000;
        sw(zero, sp, 0xE0);
        v0 = addiu(v0, 380);  // &0x96017C
        sw(zero, sp, 0xD0);
        sq(v0, sp, 0xA0);
        for (;;) {
        L_004a8a94:
            charge(ctx, 1);
            lw(v0, sp, 0x118);
            for (;;) {
                // 0x004a8a98
                charge(ctx, 2);
                if (v0 == s4) {
                    // 0x004a8aa0
                    charge(ctx, 6);
                    lw(a2, sp, 0x11C);
                    a0 = s3;
                    a1 = 256;
                    jal(ctx, 0x4A8AA8u, gen::fn_sub_4C0550_004c0550);
                    if (v0 != 0) {
                        // 0x004a8ab8
                        charge(ctx, 2);
                        if (s2 == 0) {
                            goto L_004a8ac0_8;
                        }
                        // 0x004a8c90
                        charge(ctx, 6);
                        lw(v0, fp, 0x0);
                        a0 = s3;
                        a1 = addiu(gp, -20576);  // "begin\n"
                        jalr(ctx, 0x4A8C98u, v0.u());
                        if (v0 == 0) {
                            goto L_004a8db8;
                        }
                        // 0x004a8ca8
                        charge(ctx, 6);
                        lw(v0, fp, 0x0);
                        a0 = s3;
                        a1 = addiu(gp, -20568);  // "end\n"
                        jalr(ctx, 0x4A8CB0u, v0.u());
                        if (v0 == 0) {
                            goto L_004a8dd8;
                        }
                        // 0x004a8cc0
                        charge(ctx, 2);
                        if (s0 == 0) {
                            backedge(ctx);
                            goto L_004a8a94;
                        }
                        // 0x004a8cc8
                        charge(ctx, 10);
                        lw(v0, s7, 0);
                        a1 = 0x780000;
                        a0 = s3;
                        a1 = addiu(a1, -7312);  // "moveto %f %f\n"
                        a2 = addiu(sp, 0x1B0);
                        a3 = addiu(sp, 0x1A0);
                        jalr(ctx, 0x4A8CDCu, v0.u());
                        v1 = 2;
                        if (v0 == v1) {
                            goto L_004a9038;
                        }
                        // 0x004a8cf0
                        charge(ctx, 10);
                        lw(v0, s7, 0);
                        a1 = 0x780000;
                        a0 = s3;
                        a1 = addiu(a1, -7296);  // "lineto %f %f\n"
                        a2 = addiu(sp, 0x1B0);
                        a3 = addiu(sp, 0x1A0);
                        jalr(ctx, 0x4A8D04u, v0.u());
                        v1 = 2;
                        if (v0 == v1) {
                            goto L_004a9050;
                        }
                        // 0x004a8d18
                        charge(ctx, 14);
                        lw(v0, s7, 0);
                        a1 = 0x780000;
                        a0 = s3;
                        a1 = addiu(a1, -7280);  // "curveto %f %f %f %f %f %f\n"
                        a2 = addiu(sp, 0x1B0);
                        a3 = addiu(sp, 0x1A0);
                        t0 = addiu(sp, 0x1B4);
                        t1 = addiu(sp, 0x1A4);
                        t2 = addiu(sp, 0x1B8);
                        t3 = addiu(sp, 0x1A8);
                        jalr(ctx, 0x4A8D3Cu, v0.u());
                        v1 = 6;
                        if (v0 != v1) {
                            goto L_004a8d88;
                        }
                        // 0x004a8d50
                        charge(ctx, 14);
                        v0 = addiu(sp, 0x1B4);
                        lwc1(f14, v0, 0);
                        lwc1(f12, sp, 0x1B0);
                        lwc1(f13, sp, 0x1A0);
                        v0 = addiu(sp, 0x1A4);
                        lwc1(f15, v0, 0);
                        v0 = addiu(sp, 0x1B8);
                        lwc1(f16, v0, 0);
                        v0 = addiu(sp, 0x1A8);
                        lwc1(f17, v0, 0);
                        a0 = s0;
                        jal(ctx, 0x4A8D78u, gen::fn_sub_4AB410_004ab410);
                        lw(v0, sp, 0x118);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            break;
        }
    }
    // 0x004a9068
    charge(ctx, 3);
    lw(v0, sp, 0x118);
    if (v0 == s4) {
        // 0x004a907c
        charge(ctx, 7);
        a0 = s4;
        link(ctx, 0x4A9080u);  // $ra first: the delay slot below depends on it
        sw(s6, s4, 304);
        call(ctx, gen::fn_sub_4A7620_004a7620);
        v0 = 0x960000;
        lw(a0, v0, -1660);  // 0x95F984
        if (a0 != 0) {
            // 0x004a9098
            charge(ctx, 5);
            v0 = 0x960000;
            a1 = si(-1);
            lw(v0, v0, -1656);  // 0x95F988
            a2 = sll(v0, 2);
            jal(ctx, 0x4A90A4u, gen::fn_memset_00521408);
        }
        // 0x004a90ac
        charge(ctx, 4);
        v0 = 0x4A0000;
        v0 = addiu(v0, 27872);  // &sub_4A6CE0
        sw(v0, s4, 312);
        backedge(ctx);
    }
    // 0x004a9074
    charge(ctx, 2);
    lw(v0, sp, 0x118);
    // 0x004a90bc
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
    sp = addiu(sp, 0x1C0);
    return;
L_004a8ac0_8:
    charge(ctx, 4);
    lb(a0, s3, 1);
    v0 = a0 & 0x80;
    if (v0 == 0) {
        // 0x004a8c78
        charge(ctx, 3);
        s2 = a0;
        v0 = 1;
        backedge(ctx);
    } else {
        // 0x004a8ad0
        charge(ctx, 4);
        v1 = a0 & 0xE0;
        v0 = 192;
        if (v1 != v0) {
            // 0x004a8b00
            charge(ctx, 4);
            v1 = a0 & 0xF0;
            v0 = 224;
            if (v1 != v0) {
                // 0x004a8b40
                charge(ctx, 4);
                v1 = a0 & 0xF8;
                v0 = 240;
                if (v1 != v0) {
                    // 0x004a8b90
                    charge(ctx, 4);
                    v1 = a0 & 0xFC;
                    v0 = 248;
                    if (v1 != v0) {
                        // 0x004a8bf0
                        charge(ctx, 4);
                        v1 = a0 & 0xFE;
                        v0 = 252;
                        if (v1 != v0) {
                            // 0x004a8c88
                            charge(ctx, 2);
                            v0 = si(-1);
                            backedge(ctx);
                        } else {
                            // 0x004a8c00
                            charge(ctx, 22);
                            lb(t0, s3, 2);
                            v0 = a0 & 0x1;
                            lb(a2, s3, 3);
                            a3 = sll(v0, 30);
                            lb(a1, s3, 4);
                            v0 = 6;
                            lb(a0, s3, 5);
                            lb(v1, s3, 6);
                            t0 = t0 & 0x3F;
                            t0 = sll(t0, 24);
                            a2 = a2 & 0x3F;
                            a1 = a1 & 0x3F;
                            a3 = a3 | t0;
                            a2 = sll(a2, 18);
                            a0 = a0 & 0x3F;
                            a2 = a2 | a3;
                            a1 = sll(a1, 12);
                            a1 = a1 | a2;
                            a0 = sll(a0, 6);
                            a0 = a0 | a1;
                            v1 = v1 & 0x3F;
                            s2 = v1 | a0;
                        }
                    } else {
                        // 0x004a8ba0
                        charge(ctx, 19);
                        lb(a3, s3, 2);
                        v0 = a0 & 0x3;
                        lb(a1, s3, 3);
                        a2 = sll(v0, 24);
                        lb(a0, s3, 4);
                        v0 = 5;
                        lb(v1, s3, 5);
                        a3 = a3 & 0x3F;
                        a3 = sll(a3, 18);
                        a1 = a1 & 0x3F;
                        a0 = a0 & 0x3F;
                        a2 = a2 | a3;
                        a1 = sll(a1, 12);
                        a0 = sll(a0, 6);
                        a1 = a1 | a2;
                        v1 = v1 & 0x3F;
                        a0 = a0 | a1;
                        s2 = v1 | a0;
                    }
                } else {
                    // 0x004a8b50
                    charge(ctx, 15);
                    v0 = a0 & 0x7;
                    lb(a2, s3, 2);
                    lb(a0, s3, 3);
                    a1 = sll(v0, 18);
                    lb(v1, s3, 4);
                    v0 = 4;
                    a2 = a2 & 0x3F;
                    a2 = sll(a2, 12);
                    a0 = a0 & 0x3F;
                    a1 = a1 | a2;
                    a0 = sll(a0, 6);
                    a0 = a0 | a1;
                    v1 = v1 & 0x3F;
                    s2 = v1 | a0;
                }
            } else {
                // 0x004a8b10
                charge(ctx, 11);
                lb(a1, s3, 2);
                v0 = a0 & 0xF;
                lb(v1, s3, 3);
                a0 = sll(v0, 12);
                v0 = 3;
                a1 = a1 & 0x3F;
                a1 = sll(a1, 6);
                v1 = v1 & 0x3F;
                a0 = a0 | a1;
                s2 = v1 | a0;
            }
        } else {
            // 0x004a8ae0
            charge(ctx, 7);
            lb(v1, s3, 2);
            v0 = a0 & 0x1F;
            a0 = sll(v0, 6);
            v0 = 2;
            v1 = v1 & 0x3F;
            s2 = a0 | v1;
        }
    }
    // 0x004a8c58
    charge(ctx, 2);
    if (i64(v0) >= 0) {
        // 0x004a8c60
        charge(ctx, 4);
        at = 0x10000;
        at = slt(s2, at);
        if (at == 0) {
            goto L_004a8c70;
        }
        backedge(ctx);
        goto L_004a8a94;
    }
L_004a8c70:
    charge(ctx, 2);
    sw(zero, sp, 0x118);
    backedge(ctx);
    goto L_004a8a94;
L_004a8d88:
    charge(ctx, 7);
    lw(v0, fp, 0x0);
    a1 = 0x780000;
    a0 = s3;
    a1 = addiu(a1, -7248);  // "closepath\n"
    jalr(ctx, 0x4A8D94u, v0.u());
    if (v0 != 0) {
        backedge(ctx);
    } else {
        // 0x004a8da4
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4A8DA4u, gen::fn_sub_4AB6A0_004ab6a0);
        backedge(ctx);
    }
    goto L_004a8a94;
L_004a8db8:
    charge(ctx, 7);
    jal(ctx, 0x4A8DB8u, gen::fn_sub_4AC570_004ac570);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x4A8DC4u, gen::fn_sub_4AC5F0_004ac5f0);
    backedge(ctx);
    goto L_004a8a94;
L_004a8dd8:
    charge(ctx, 10);
    a0 = s0;
    jal(ctx, 0x4A8DD8u, gen::fn_sub_4AC240_004ac240);
    sw(v0, sp, 0x114);
    a0 = v0;
    jal(ctx, 0x4A8DE4u, gen::fn_sub_4AC710_004ac710);
    v0 = 0x960000;
    lw(v0, v0, -1656);  // 0x95F988
    at = slt(s6, v0);
    if (at == 0) {
        // 0x004a8ed0
        charge(ctx, 19);
        s0 = addiu(v0, 32);
        v0 = 0x30000;
        a1 = v0 | 0x190;
        lq(v0, sp, 0xB0);
        lw(v0, v0, 0);
        a0 = sll(s0, 2);
        jalr(ctx, 0x4A8EE4u, v0.u());
        s5 = v0;
        a1 = s1;
        v0 = 0x960000;
        a0 = s5;
        lw(v0, v0, -1656);  // 0x95F988
        a2 = sll(v0, 2);
        jal(ctx, 0x4A8F00u, gen::fn_memcpy_00521250);
        v0 = 0x960000;
        lw(v0, v0, -1656);  // 0x95F988
        at = slt(v0, s0);
        if (at != 0) {
            // 0x004a8f1c
            charge(ctx, 4);
            v1 = subu(s0, v0);
            at = slti(v1, 9);
            a1 = addiu(s0, -8);
            if (at == 0) {
                // 0x004a8f2c
                charge(ctx, 4);
                at = slt(s0, v0);
                a0 = 0;
                v1 = 0;
                if (at == 0) {
                    // 0x004a8f3c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(s0, at);
                    if (at != 0) {
                        // 0x004a8f50
                        charge(ctx, 2);
                        v1 = 1;
                    }
                }
                // 0x004a9028
                charge(ctx, 2);
                if (v1 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004a9030
                    charge(ctx, 2);
                    backedge(ctx);
                    // 0x004a8f58
                    charge(ctx, 7);
                    v1 = 0x960000;
                    lw(v1, v1, -1656);  // 0x95F988
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(v1, at);
                    if (at != 0) {
                        // 0x004a8f74
                        charge(ctx, 1);
                        a0 = 1;
                    }
                }
                // 0x004a8f78
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x004a8f80
                    charge(ctx, 4);
                    v1 = sll(v0, 2);
                    a0 = si(-1);
                    a2 = addu(s5, v1);
                    for (;;) {
                        // 0x004a8f90
                        charge(ctx, 12);
                        sw(a0, a2, 0);
                        sw(a0, a2, 4);
                        v0 = addiu(v0, 8);
                        sw(a0, a2, 8);
                        v1 = slt(v0, a1);
                        sw(a0, a2, 12);
                        sw(a0, a2, 16);
                        sw(a0, a2, 20);
                        sw(a0, a2, 24);
                        sw(a0, a2, 28);
                        a2 = addiu(a2, 32);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004a8fc0
            charge(ctx, 3);
            at = slt(v0, s0);
            if (at != 0) {
                // 0x004a8fcc
                charge(ctx, 3);
                v1 = sll(v0, 2);
                a0 = si(-1);
                a1 = addu(s5, v1);
                for (;;) {
                    // 0x004a8fd8
                    charge(ctx, 7);
                    v0 = addiu(v0, 1);
                    sw(a0, a1, 0);
                    v1 = slt(v0, s0);
                    a1 = addiu(a1, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a8ff4
                charge(ctx, 1);
            }
        }
        // 0x004a8ff8
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x004a9000
            charge(ctx, 4);
            lq(v0, sp, 0xA0);
            lw(v0, v0, 0);
            a0 = s1;
            jalr(ctx, 0x4A9008u, v0.u());
        }
        // 0x004a9010
        charge(ctx, 6);
        v1 = 0x960000;
        v0 = 0x960000;
        s1 = s5;
        sw(s5, v1, -1660);  // 0x95F984
        sw(s0, v0, -1656);  // 0x95F988
        backedge(ctx);
    }
    // 0x004a8e00
    charge(ctx, 3);
    v0 = slti(s2, 128);
    if (v0 != 0) {
        // 0x004a8e28
        charge(ctx, 4);
        lq(v0, sp, 0xC0);
        v1 = sll(s2, 1);
        v0 = addu(v0, v1);
        sh(s6, v0, 0);
    } else {
        // 0x004a8e0c
        charge(ctx, 7);
        lw(v1, s4, 16);
        lw(v0, sp, 0xE0);
        v1 = v1 | 0x2;
        v0 = addu(s1, v0);
        sw(v1, s4, 16);
        sw(s2, v0, 0);
    }
    // 0x004a8e38
    charge(ctx, 19);
    lw(v0, sp, 0xFC);
    v1 = sll(s6, 5);
    s2 = 0;
    s6 = addiu(s6, 1);
    s0 = 0;
    v1 = addu(v0, v1);
    lw(v0, sp, 0x114);
    sw(v0, v1, 24);
    lw(v0, sp, 0xE0);
    lwc1(f0, sp, 0x1B0);
    v0 = addiu(v0, 4);
    sw(v0, sp, 0xE0);
    lw(v0, sp, 0xD0);
    v0 = addiu(v0, 32);
    sw(v0, sp, 0xD0);
    lw(v0, sp, 0x100);
    v0 = slt(s6, v0);
    swc1(f0, v1, 0);
    if (v0 != 0) {
        backedge(ctx);
    } else {
        // 0x004a8e84
        charge(ctx, 19);
        lw(a0, s4, 308);
        v0 = 0x30000;
        a1 = 32;
        a2 = v0 | 0x190;
        jal(ctx, 0x4A8E90u, gen::fn_sub_4C1F70_004c1f70);
        link(ctx, 0x4A8E98u);  // $ra first: the delay slot below depends on it
        lw(a0, s4, 308);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        sw(v0, sp, 0xFC);
        a1 = 0;
        lw(v0, sp, 0x100);
        a2 = 1024;
        lw(v1, sp, 0xFC);
        v0 = addiu(v0, 32);
        sw(v0, sp, 0x100);
        lw(v0, sp, 0xD0);
        a0 = addu(v1, v0);
        jal(ctx, 0x4A8EC0u, gen::fn_memset_00521408);
        backedge(ctx);
    }
    goto L_004a8a94;
L_004a9038:
    charge(ctx, 6);
    lwc1(f12, sp, 0x1B0);
    lwc1(f13, sp, 0x1A0);
    a0 = s0;
    jal(ctx, 0x4A9040u, gen::fn_sub_4AB200_004ab200);
    backedge(ctx);
    goto L_004a8a94;
L_004a9050:
    charge(ctx, 6);
    lwc1(f12, sp, 0x1B0);
    lwc1(f13, sp, 0x1A0);
    a0 = s0;
    jal(ctx, 0x4A9058u, gen::fn_sub_4AB2C0_004ab2c0);
    backedge(ctx);
    goto L_004a8a94;
}

// sub_4A90F0 [rt2dFontCreate] -- creates an Rt2d font from the font free list (0x95ED68): one page, height 1.0, empty
//   glyph tables, the glyph sList (32-byte entries, sub_4C1D50), the bitmap show callback (sub_4A6EB0), the 128-entry
//   character map all -1; the font, or 0
// 0x004A90F0 sub_4A90F0 -- 244 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A90F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a90f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, v0, -4760);  // 0x95ED68
    v0 = 0x30000;
    a1 = v0 | 0x199;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188
    jalr(ctx, 0x4A9114u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004a91d0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004a9128
        charge(ctx, 28);
        v1 = 1;
        v0 = 0x3F800000;
        sw(v1, s0, 0);
        a0 = 32;
        sw(v0, s0, 4);
        sw(zero, s0, 8);
        v0 = 0x30000;
        sw(zero, s0, 12);
        a1 = v0 | 0x190;
        sw(zero, s0, 16);
        sw(zero, s0, 20);
        sw(zero, s0, 24);
        sw(zero, s0, 28);
        sw(zero, s0, 32);
        sw(zero, s0, 296);
        sw(zero, s0, 304);
        sw(zero, s0, 292);
        link(ctx, 0x4A916Cu);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 300);
        call(ctx, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s0, 308);
        a1 = 0;
        v0 = 0x4A0000;
        a0 = s0;
        v0 = addiu(v0, 28336);  // &sub_4A6EB0
        v1 = si(-1);
        sw(v0, s0, 312);
        sw(zero, s0, 316);
        sw(zero, s0, 320);
        for (;;) {
            // 0x004a9198
            charge(ctx, 12);
            sh(v1, a0, 36);
            a1 = addiu(a1, 8);
            sh(v1, a0, 38);
            v0 = slti(a1, 128);
            sh(v1, a0, 40);
            sh(v1, a0, 42);
            sh(v1, a0, 44);
            sh(v1, a0, 46);
            sh(v1, a0, 48);
            sh(v1, a0, 50);
            a0 = addiu(a0, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004a91c8
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004a91d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4A97C0 [rt2dFontOpenMetrics] -- opens a font's metrics file: for each ';'-separated directory of the font path
//   (0x95ED6C) the name and ".met" appended (strcat slot) and the file tried (sub_4C0240); the file, or 0
// 0x004A97C0 sub_4A97C0 -- 216 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A97C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a97c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x960000;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a0 = 0;
    sq(s0, sp, 0x0);
    s1 = 0x960000;
    lw(s2, v0, -4756);  // 0x95ED6C
    s1 = addiu(s1, 324);  // &0x960144
    v0 = 0;
    for (;;) {
        // 0x004a97fc
        charge(ctx, 4);
        lb(s0, s2, 0);
        v1 = 59;
        if (s0 != v1) {
            // 0x004a980c
            charge(ctx, 2);
            if (s0 == 0) {
                goto L_004a9838;
            }
            // 0x004a9814
            charge(ctx, 3);
            v1 = addu(s3, a0);
            sb(s0, v1, 0);
            a0 = addiu(a0, 1);
            goto L_004a9820;
        }
    L_004a9838:
        charge(ctx, 15);
        v0 = addu(s3, a0);
        a1 = s4;
        sb(zero, v0, 0);
        lw(v0, s1, 0);
        a0 = s3;
        jalr(ctx, 0x4A9848u, v0.u());
        lw(v0, s1, 0);
        a0 = s3;
        a1 = addiu(gp, -20536);  // ".met"
        jalr(ctx, 0x4A9858u, v0.u());
        a0 = s3;
        a1 = addiu(gp, -20528);  // &0x7CDCC0
        jal(ctx, 0x4A9864u, gen::fn_sub_4C0240_004c0240);
        a0 = 0;
        backedge(ctx);
    L_004a9820:
        charge(ctx, 2);
        s2 = addiu(s2, 1);
        if (s0 != 0) {
            // 0x004a9828
            charge(ctx, 2);
            if (v0 == 0) {
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x004a9830
    charge(ctx, 2);
    // 0x004a9878
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4A98A0 [Rt2dFontRead] -- reads an Rt2d font by name: a new font (sub_4A90F0), its metrics file found on the font
//   path (sub_4A97C0), the first line selecting the reader -- METRICS1 (sub_4A7820), METRICS2 (sub_4A7E40), METRICS3
//   (sub_4A8980) --, the file closed (sub_4C0370); a failed read destroys the font (sub_4A96B0); the font, or 0
// 0x004A98A0 sub_4A98A0 -- 452 bytes; frame 0x1E0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A98A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a98a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4A98BCu, gen::fn_sub_4A90F0_004a90f0);
    s4 = v0;
    if (s4 == 0) {
        // 0x004a99f4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a98d0
        charge(ctx, 21);
        v0 = 0x960000;
        s1 = 0x960000;
        lw(a0, v0, -4756);  // 0x95ED6C
        s1 = addiu(s1, 356);  // &0x960164
        lw(v0, s1, 0);  // 0x960164
        jalr(ctx, 0x4A98E4u, v0.u());
        lw(v1, s1, 0);  // 0x960164
        a0 = s0;
        s1 = v0;
        jalr(ctx, 0x4A98F4u, v1.u());
        v1 = addu(s1, v0);
        v0 = 0x10000;
        a1 = v0 | 0x190;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = addiu(v1, 5);
        jalr(ctx, 0x4A9910u, v0.u());
        s1 = v0;
        if (s1 == 0) {
            // 0x004a9a34
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x4A9A34u, gen::fn_sub_4A96B0_004a96b0);
            s4 = 0;
            backedge(ctx);
        } else {
            // 0x004a9924
            charge(ctx, 6);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x4A9928u, gen::fn_sub_4A97C0_004a97c0);
            s2 = v0;
            s3 = 0;
            if (s2 != 0) {
                // 0x004a993c
                charge(ctx, 13);
                a0 = addiu(sp, 0x60);
                a1 = 256;
                a2 = s2;
                jal(ctx, 0x4A9944u, gen::fn_sub_4C0550_004c0550);
                s0 = 0x960000;
                a1 = 0x780000;
                s0 = addiu(s0, 344);  // &0x960158
                a0 = addiu(sp, 0x60);
                lw(v0, s0, 0);  // 0x960158
                a1 = addiu(a1, -7232);  // "METRICS1\n"
                jalr(ctx, 0x4A9960u, v0.u());
                if (v0 == 0) {
                    // 0x004a99fc
                    charge(ctx, 7);
                    a0 = s4;
                    a1 = addiu(sp, 0x160);
                    a2 = s2;
                    a3 = addiu(sp, 0x60);
                    jal(ctx, 0x4A9A08u, gen::fn_sub_4A7820_004a7820);
                    s3 = v0;
                    backedge(ctx);
                } else {
                    // 0x004a9970
                    charge(ctx, 7);
                    lw(v0, s0, 0);
                    a1 = 0x780000;
                    a0 = addiu(sp, 0x60);
                    a1 = addiu(a1, -7216);  // "METRICS2\n"
                    jalr(ctx, 0x4A997Cu, v0.u());
                    if (v0 == 0) {
                        // 0x004a9a18
                        charge(ctx, 7);
                        a0 = s4;
                        a1 = addiu(sp, 0x160);
                        a2 = s2;
                        a3 = addiu(sp, 0x60);
                        jal(ctx, 0x4A9A24u, gen::fn_sub_4A7E40_004a7e40);
                        s3 = v0;
                        backedge(ctx);
                    } else {
                        // 0x004a998c
                        charge(ctx, 7);
                        lw(v0, s0, 0);
                        a1 = 0x780000;
                        a0 = addiu(sp, 0x60);
                        a1 = addiu(a1, -7200);  // "METRICS3\n"
                        jalr(ctx, 0x4A9998u, v0.u());
                        if (v0 == 0) {
                            // 0x004a99a8
                            charge(ctx, 6);
                            a0 = s4;
                            a1 = addiu(sp, 0x160);
                            a2 = s2;
                            a3 = addiu(sp, 0x60);
                            jal(ctx, 0x4A99B4u, gen::fn_sub_4A8980_004a8980);
                            s3 = v0;
                        }
                    }
                }
                // 0x004a99c0
                charge(ctx, 2);
                a0 = s2;
                jal(ctx, 0x4A99C0u, gen::fn_sub_4C0370_004c0370);
            }
            // 0x004a99c8
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            a0 = s1;
            jalr(ctx, 0x4A99D0u, v0.u());
            if (s3 != s4) {
                // 0x004a99e0
                charge(ctx, 3);
                a0 = s4;
                jal(ctx, 0x4A99E0u, gen::fn_sub_4A96B0_004a96b0);
                s4 = 0;
            }
        }
        // 0x004a99ec
        charge(ctx, 2);
        v0 = s4;
    }
    // 0x004a9a44 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// sub_4ACB90 [rt2dPathStreamReadNew] -- reads a chained sub-path: a new path (from the path free list, made an sList),
//   the 16-byte header and the body (sub_4AC920) when its version is 1; on a failure the new path is released (sub_4AB0E0
//   / sub_4AC390); the path, or 0
// 0x004ACB90 sub_4ACB90 -- 304 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4ACB90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004acb90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x30000;
    sd(ra, sp, 0x30);
    v0 = 0x960000;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, v0, -4732);  // 0x95ED84
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188
    a1 = v1 | 0x1A1;
    jalr(ctx, 0x4ACBBCu, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004acc28
        charge(ctx, 1);
        a0 = s1;
    } else {
        // 0x004acbd0
        charge(ctx, 12);
        sw(zero, s0, 0);
        v0 = 1;
        sw(zero, s0, 4);
        a0 = s0;
        sw(zero, s0, 8);
        sw(v0, s0, 12);
        sw(zero, s0, 20);
        sw(s0, s0, 24);
        link(ctx, 0x4ACBF0u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 16);
        call(ctx, gen::fn_sub_4AC5F0_004ac5f0);
        a0 = s1;
    }
    // 0x004acc2c
    charge(ctx, 7);
    a1 = addiu(sp, 0x40);
    a2 = 16;
    s2 = s0;
    jal(ctx, 0x4ACC34u, gen::fn_sub_4C5250_004c5250);
    v1 = 16;
    if (v0 == v1) {
        backedge(ctx);
        // 0x004acc08
        charge(ctx, 4);
        lw(v1, sp, 0x40);
        v0 = 1;
        if (v1 == v0) {
            // 0x004acc50
            charge(ctx, 6);
            a2 = s1;
            a0 = s0;
            a1 = addiu(sp, 0x40);
            jal(ctx, 0x4ACC58u, gen::fn_sub_4AC920_004ac920);
            s2 = v0;
            backedge(ctx);
        }
    } else {
        // 0x004acc48
        charge(ctx, 2);
        backedge(ctx);
        // 0x004acc00
        charge(ctx, 2);
        s2 = 0;
    }
    // 0x004acc18
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x004acc68
        charge(ctx, 2);
        if (s0 == 0) {
            backedge(ctx);
        } else {
            // 0x004acc70
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x4ACC70u, gen::fn_sub_4AB0E0_004ab0e0);
            if (v0 == 0) {
                backedge(ctx);
            } else {
                // 0x004acc80
                charge(ctx, 4);
                a0 = v0;
                jal(ctx, 0x4ACC80u, gen::fn_sub_4AB0E0_004ab0e0);
                if (v0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004acc90
                    charge(ctx, 6);
                    a0 = v0;
                    jal(ctx, 0x4ACC90u, gen::fn_sub_4AB0E0_004ab0e0);
                    a0 = v0;
                    jal(ctx, 0x4ACC98u, gen::fn_sub_4AC390_004ac390);
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004acc20
    charge(ctx, 2);
    v0 = s2;
    // 0x004acca8
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4ACE80 [rt2dShapeStrokeGeometry] -- builds the stroke of an Rt2d shape's path into its geometry: the brush's
//   material (made on first use), two vertices per path node (inset and outset by half the stroke width), colours from
//   the brush's gradient along the path length (flag 1) or white, UVs (flag 2), two triangles per segment with the
//   material; the vertex / triangle counters advanced; the shape
// 0x004ACE80 sub_4ACE80 -- 1532 bytes; frame 0x110: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_4ACE80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004ace80
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    s7 = a2;
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    sw(a0, sp, 0x108);
    swc1(f21, sp, 0x4);
    sw(a3, sp, 0x104);
    swc1(f20, sp, 0x0);
    sw(t0, sp, 0x100);
    lw(fp, a1, 108);
    s0 = a1;
    if (fp == 0) {
        // 0x004ad294
        charge(ctx, 5);
        jal(ctx, 0x4AD294u, gen::fn_sub_494BE0_00494be0);
        lw(a1, s0, 104);
        fp = v0;
        if (a1 != 0) {
            // 0x004ad2a8
            charge(ctx, 2);
            a0 = fp;
            jal(ctx, 0x4AD2A8u, gen::fn_sub_494D50_00494d50);
        }
        // 0x004ad2b0
        charge(ctx, 4);
        lw(v0, s0, 100);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x004ad2e8
            charge(ctx, 11);
            lwc1(f0, gp, -20516);  // 0x7CDCCC
            swc1(f0, sp, 0x10C);
            lbu(a1, sp, 0x10C);
            lbu(a0, sp, 0x10D);
            lbu(v1, sp, 0x10E);
            lbu(v0, sp, 0x10F);
            sb(a1, fp, 0x4);
            sb(a0, fp, 0x5);
            sb(v1, fp, 0x6);
            sb(v0, fp, 0x7);
            backedge(ctx);
        } else {
            // 0x004ad2c0
            charge(ctx, 8);
            lbu(a1, s0, 96);
            lbu(a0, s0, 97);
            lbu(v1, s0, 98);
            lbu(v0, s0, 99);
            sb(a1, fp, 0x4);
            sb(a0, fp, 0x5);
            sb(v1, fp, 0x6);
            sb(v0, fp, 0x7);
        }
        // 0x004ad2e0
        charge(ctx, 2);
        sw(fp, s0, 108);
        backedge(ctx);
    } else {
        // 0x004aced4
        charge(ctx, 3);
        lh(v0, fp, 0x18);
        v0 = addiu(v0, 1);
        sh(v0, fp, 0x18);
    }
    // 0x004acee0
    charge(ctx, 4);
    lw(v0, sp, 0x108);
    sw(zero, sp, 0xF0);
    sw(zero, sp, 0xE0);
    lw(s1, v0, 20);
    for (;;) {
        // 0x004acef0
        charge(ctx, 4);
        lw(v0, s1, 4);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x004acf00
            charge(ctx, 2);
            link(ctx, 0x4ACF00u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 0);
            call(ctx, gen::fn_sub_4C2120_004c2120);
        }
        // 0x004acf08
        charge(ctx, 13);
        v1 = sll(v0, 1);
        lw(s1, s1, 20);
        lw(v0, sp, 0xF0);
        v0 = addu(v0, v1);
        sw(v0, sp, 0xF0);
        v1 = addiu(v1, -2);
        lw(v0, sp, 0xE0);
        v0 = addu(v0, v1);
        sw(v0, sp, 0xE0);
        lw(v0, sp, 0x108);
        lw(v0, v0, 20);
        sw(v0, sp, 0xD0);
        if (s1 == v0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004acf3c
    charge(ctx, 5);
    v0 = 0x960000;
    lwc1(f21, v0, -4264);  // 0x95EF58
    lw(v0, sp, 0xE0);
    lwc1(f20, s0, 112);
    if (v0 != 0) {
        // 0x004acf50
        charge(ctx, 3);
        lw(v0, sp, 0xF0);
        if (v0 != 0) {
            // 0x004acf5c
            charge(ctx, 19);
            lw(v0, sp, 0x104);
            lw(t1, s7, 92);
            lw(v1, s7, 44);
            lw(a0, s7, 48);
            lw(s5, v0, 0);
            lw(v0, sp, 0x100);
            a3 = sll(s5, 1);
            t0 = addu(a3, s5);
            a1 = sll(s5, 2);
            lw(a3, t1, 20);
            t0 = sll(t0, 2);
            s3 = addu(a0, a1);
            lw(a2, v0, 0);
            s4 = addu(a3, t0);
            lw(v0, s7, 52);
            a2 = sll(a2, 3);
            s6 = addu(v1, a2);
            v1 = sll(s5, 3);
            s2 = addu(v0, v1);
            for (;;) {
                // 0x004acfa8
                charge(ctx, 6);
                lw(v0, sp, 0xD0);
                lwc1(f22, v0, 16);
                lw(v1, v0, 4);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x004acfd4
                    charge(ctx, 3);
                    lw(v0, sp, 0xD0);
                    lw(v0, v0, 0);
                    s1 = v0;
                } else {
                    // 0x004acfc0
                    charge(ctx, 5);
                    lw(v0, sp, 0xD0);
                    link(ctx, 0x4ACFC4u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4C2090_004c2090);
                    s1 = v0;
                }
                // 0x004acfe0
                charge(ctx, 5);
                v1 = si(-1);
                lw(v0, sp, 0xD0);
                lw(v0, v0, 4);
                sq(v0, sp, 0xC0);
                if (v0 == v1) {
                    // 0x004acff4
                    charge(ctx, 4);
                    lw(v0, sp, 0xD0);
                    link(ctx, 0x4ACFF8u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4C2120_004c2120);
                    sq(v0, sp, 0xC0);
                }
                // 0x004ad004
                charge(ctx, 19);
                lq(v0, sp, 0xC0);
                v1 = sll(v0, 1);
                v0 = 0x3F800000;
                mtc1(v0, f1);
                v0 = addu(s5, v1);
                v0 = addiu(v0, -1);
                sq(v0, sp, 0xB0);
                lq(v0, sp, 0xC0);
                v0 = addu(v1, v0);
                v1 = sll(v0, 3);
                v1 = addu(s1, v1);
                v0 = 0;
                lwc1(f0, v1, -4);
                div_s(f3, f1, f0);
                lq(v1, sp, 0xC0);
                at = sltu(0, v1);
                if (at != 0) {
                    // 0x004ad050
                    charge(ctx, 4);
                    add_s(f2, f20, f22);
                    a0 = 255;
                    sub_s(f1, f20, f22);
                    mtc1(zero, f0);
                    for (;;) {
                        // 0x004ad060
                        charge(ctx, 15);
                        lwc1(f4, s1, 4);
                        lwc1(f5, s1, 12);
                        lwc1(f6, s1, 16);
                        adda_s(f0, f4);
                        msub_s(f4, f5, f2);
                        swc1(f4, s4, 0);
                        lwc1(f4, s1, 8);
                        mul_s(f6, f6, f2);
                        sub_s(f4, f4, f6);
                        swc1(f4, s4, 4);
                        swc1(f21, s4, 8);
                        lw(v1, s0, 100);
                        v1 = v1 & 0x1;
                        if (v1 == 0) {
                            // 0x004ad314
                            charge(ctx, 6);
                            sb(a0, s3, 0);
                            sb(a0, s3, 1);
                            sb(a0, s3, 2);
                            sb(a0, s3, 3);
                            s3 = addiu(s3, 4);
                            backedge(ctx);
                        } else {
                            // 0x004ad09c
                            charge(ctx, 33);
                            lwc1(f9, s1, 20);
                            lwc1(f8, s0, 24);
                            lwc1(f6, s0, 32);
                            lwc1(f4, s0, 0);
                            lwc1(f5, s0, 36);
                            lwc1(f7, s0, 28);
                            mul_s(f10, f9, f3);
                            mul_s(f8, f8, f10);
                            add_s(f4, f8, f4);
                            mul_s(f9, f6, f10);
                            mul_s(f8, f5, f10);
                            cvt_w_s(f4, f4);
                            mfc1(v1, f4);
                            lwc1(f6, s0, 4);
                            mul_s(f7, f7, f10);
                            lwc1(f5, s0, 8);
                            add_s(f7, f7, f6);
                            lwc1(f4, s0, 12);
                            add_s(f6, f9, f5);
                            add_s(f5, f8, f4);
                            sb(v1, s3, 0);
                            cvt_w_s(f4, f7);
                            mfc1(v1, f4);
                            cvt_w_s(f4, f6);
                            sb(v1, s3, 1);
                            mfc1(v1, f4);
                            cvt_w_s(f4, f5);
                            sb(v1, s3, 2);
                            mfc1(v1, f4);
                            sb(v1, s3, 3);
                            s3 = addiu(s3, 4);
                        }
                        // 0x004ad120
                        charge(ctx, 4);
                        lw(v1, s0, 100);
                        v1 = v1 & 0x2;
                        if (v1 != 0) {
                            // 0x004ad330
                            charge(ctx, 14);
                            lwc1(f8, s1, 20);
                            lwc1(f7, s0, 40);
                            lwc1(f6, s0, 44);
                            lwc1(f5, s0, 16);
                            lwc1(f4, s0, 20);
                            mul_s(f8, f8, f3);
                            mul_s(f7, f7, f8);
                            mul_s(f6, f6, f8);
                            add_s(f5, f7, f5);
                            add_s(f4, f6, f4);
                            swc1(f5, s2, 0);
                            swc1(f4, s2, 4);
                            s2 = addiu(s2, 8);
                            backedge(ctx);
                        }
                        // 0x004ad130
                        charge(ctx, 15);
                        lwc1(f4, s1, 4);
                        lwc1(f6, s1, 16);
                        lwc1(f5, s1, 12);
                        adda_s(f0, f4);
                        mul_s(f6, f6, f1);
                        madd_s(f4, f5, f1);
                        swc1(f4, s4, 12);
                        lwc1(f4, s1, 8);
                        add_s(f4, f4, f6);
                        swc1(f4, s4, 16);
                        swc1(f21, s4, 20);
                        lw(v1, s0, 100);
                        v1 = v1 & 0x1;
                        if (v1 == 0) {
                            // 0x004ad368
                            charge(ctx, 6);
                            sb(a0, s3, 0);
                            sb(a0, s3, 1);
                            sb(a0, s3, 2);
                            sb(a0, s3, 3);
                            s3 = addiu(s3, 4);
                            backedge(ctx);
                        } else {
                            // 0x004ad16c
                            charge(ctx, 33);
                            lwc1(f9, s1, 20);
                            lwc1(f8, s0, 72);
                            lwc1(f6, s0, 80);
                            lwc1(f4, s0, 48);
                            lwc1(f5, s0, 84);
                            lwc1(f7, s0, 76);
                            mul_s(f10, f9, f3);
                            mul_s(f8, f8, f10);
                            add_s(f4, f8, f4);
                            mul_s(f9, f6, f10);
                            mul_s(f8, f5, f10);
                            cvt_w_s(f4, f4);
                            mfc1(v1, f4);
                            lwc1(f6, s0, 52);
                            mul_s(f7, f7, f10);
                            lwc1(f5, s0, 56);
                            add_s(f7, f7, f6);
                            lwc1(f4, s0, 60);
                            add_s(f6, f9, f5);
                            add_s(f5, f8, f4);
                            sb(v1, s3, 0);
                            cvt_w_s(f4, f7);
                            mfc1(v1, f4);
                            cvt_w_s(f4, f6);
                            sb(v1, s3, 1);
                            mfc1(v1, f4);
                            cvt_w_s(f4, f5);
                            sb(v1, s3, 2);
                            mfc1(v1, f4);
                            sb(v1, s3, 3);
                            s3 = addiu(s3, 4);
                        }
                        // 0x004ad1f0
                        charge(ctx, 4);
                        lw(v1, s0, 100);
                        v1 = v1 & 0x2;
                        if (v1 != 0) {
                            // 0x004ad380
                            charge(ctx, 14);
                            lwc1(f8, s1, 20);
                            lwc1(f7, s0, 88);
                            lwc1(f6, s0, 92);
                            lwc1(f5, s0, 64);
                            lwc1(f4, s0, 68);
                            mul_s(f8, f8, f3);
                            mul_s(f7, f7, f8);
                            mul_s(f6, f6, f8);
                            add_s(f5, f7, f5);
                            add_s(f4, f6, f4);
                            swc1(f5, s2, 0);
                            swc1(f4, s2, 4);
                            s2 = addiu(s2, 8);
                            backedge(ctx);
                        }
                        // 0x004ad200
                        charge(ctx, 6);
                        lq(v1, sp, 0xC0);
                        v0 = addiu(v0, 1);
                        s4 = addiu(s4, 24);
                        v1 = sltu(v0, v1);
                        s1 = addiu(s1, 24);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004ad218
                charge(ctx, 5);
                lq(v0, sp, 0xC0);
                v0 = addiu(v0, -1);
                v0 = sltu(0, v0);
                s1 = 0;
                if (v0 != 0) {
                    for (;;) {
                        // 0x004ad3b8
                        charge(ctx, 32);
                        v1 = addiu(s5, 1);
                        v0 = addiu(s5, 2);
                        a2 = s5 & 0xFFFF;
                        a3 = v1 & 0xFFFF;
                        t0 = v0 & 0xFFFF;
                        a0 = s7;
                        a1 = s6;
                        jal(ctx, 0x4AD3D0u, gen::fn_sub_493210_00493210);
                        a0 = s7;
                        a1 = s6;
                        a2 = fp;
                        jal(ctx, 0x4AD3E0u, gen::fn_sub_493230_00493230);
                        v0 = addiu(s5, 3);
                        v1 = addiu(s5, 1);
                        a3 = v0 & 0xFFFF;
                        a2 = v1 & 0xFFFF;
                        v0 = addiu(s5, 2);
                        a0 = s7;
                        t0 = v0 & 0xFFFF;
                        a1 = addiu(s6, 8);
                        jal(ctx, 0x4AD404u, gen::fn_sub_493210_00493210);
                        a0 = s7;
                        a1 = addiu(s6, 8);
                        a2 = fp;
                        jal(ctx, 0x4AD414u, gen::fn_sub_493230_00493230);
                        lq(v0, sp, 0xC0);
                        s1 = addiu(s1, 1);
                        s6 = addiu(s6, 16);
                        v0 = addiu(v0, -1);
                        v0 = sltu(s1, v0);
                        s5 = addiu(s5, 2);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ad438
                    charge(ctx, 2);
                    lq(v0, sp, 0xB0);
                    backedge(ctx);
                } else {
                    // 0x004ad22c
                    charge(ctx, 1);
                    lq(v0, sp, 0xB0);
                }
                // 0x004ad230
                charge(ctx, 9);
                s5 = addiu(v0, 1);
                lw(v0, sp, 0xD0);
                lw(v0, v0, 20);
                sw(v0, sp, 0xD0);
                lw(v0, sp, 0x108);
                lw(v1, v0, 20);
                lw(v0, sp, 0xD0);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004ad254
    charge(ctx, 16);
    a0 = fp;
    jal(ctx, 0x4AD254u, gen::fn_sub_494CC0_00494cc0);
    lw(v1, sp, 0x104);
    lw(v0, sp, 0x108);
    lw(a0, v1, 0);
    lw(v1, sp, 0xF0);
    a0 = addu(a0, v1);
    lw(v1, sp, 0x104);
    sw(a0, v1, 0);
    lw(v1, sp, 0x100);
    lw(a0, v1, 0);
    lw(v1, sp, 0xE0);
    a0 = addu(a0, v1);
    lw(v1, sp, 0x100);
    sw(a0, v1, 0);
    // 0x004ad440
    charge(ctx, 15);
    ld(ra, sp, 0xA0);
    lwc1(f22, sp, 0x8);
    lq(fp, sp, 0x90);
    lwc1(f21, sp, 0x4);
    lq(s7, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x110);
}

// sub_4AE270 [rt2dPickRegionStreamRead] -- reads a pick region: a new path (sub_4AC570) at +176, the transform-dirty
//   flag cleared, the path chunk (417) read into it (sub_4ACB10); the object, or 0
// 0x004AE270 sub_4AE270 -- 124 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AE270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae270
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x4AE284u, gen::fn_sub_4AC570_004ac570);
    sw(v0, s1, 176);
    a0 = s0;
    lw(v1, s1, 8);
    v0 = si(-2);
    a1 = 417;
    a2 = addiu(sp, 0x3C);
    a3 = addiu(sp, 0x38);
    v0 = v1 & v0;
    link(ctx, 0x4AE2ACu);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 8);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 != 0) {
        // 0x004ae2c4
        charge(ctx, 5);
        lw(a0, s1, 176);
        a1 = s0;
        jal(ctx, 0x4AE2C8u, gen::fn_sub_4ACB10_004acb10);
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x004ae2bc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ae2d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4AE4E0 [rt2dSceneDestroyBody] -- destroys a scene's contents: the reference sList (+184), every 272-byte child
//   object by its type (sub_4ADBD0), the child sList (+176); 1 when all went well
// 0x004AE4E0 sub_4AE4E0 -- 188 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AE4E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae4e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 184);
    s0 = 1;
    if (a0 != 0) {
        // 0x004ae508
        charge(ctx, 3);
        jal(ctx, 0x4AE508u, gen::fn_sub_4C20B0_004c20b0);
        s0 = v0;
    }
    // 0x004ae514
    charge(ctx, 12);
    link(ctx, 0x4AE514u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 176);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    lw(a1, s1, 180);
    lw(a0, s1, 176);
    v1 = sll(a1, 4);
    v1 = addu(v1, a1);
    v1 = sll(v1, 4);
    s2 = addu(v0, v1);
    jal(ctx, 0x4AE530u, gen::fn_sub_4C2090_004c2090);
    s3 = v0;
    if (s3 != s2) {
        for (;;) {
            // 0x004ae544
            charge(ctx, 3);
            s0 = sltu(0, s0);
            if (s0 != 0) {
                // 0x004ae550
                charge(ctx, 3);
                a0 = s3;
                jal(ctx, 0x4AE550u, gen::fn_sub_4ADBD0_004adbd0);
                s0 = sltu(0, v0);
            }
            // 0x004ae55c
            charge(ctx, 3);
            s3 = addiu(s3, 272);
            if (s3 == s2) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004ae568
    charge(ctx, 3);
    v0 = sltu(0, s0);
    if (v0 != 0) {
        // 0x004ae574
        charge(ctx, 3);
        link(ctx, 0x4AE574u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 176);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        v0 = sltu(0, v0);
    }
    // 0x004ae580 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4B24C0 [rt2dAnimPropBlendMatrix] -- blends an animated object's matrix towards a keyframe's by $f12: position,
//   right and up each lerped from the prop's stored values, the matrix orthonormalised (sub_4C2F10), the object marked
//   changed (sub_4AE060), the prop's matrix-dirty flag cleared; the prop
// 0x004B24C0 sub_4B24C0 -- 468 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B24C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x004b24c0
    enter(ctx, 117);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lwc1(f1, a1, 48);
    lw(v0, a0, 4);
    lwc1(f0, a0, 64);
    s0 = a0;
    sub_s(f0, f1, f0);
    swc1(f0, v0, 64);
    lwc1(f1, a1, 52);
    lwc1(f0, a0, 68);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 68);
    lwc1(f1, a1, 56);
    lwc1(f0, a0, 72);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 72);
    lwc1(f0, v0, 64);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 64);
    lwc1(f0, v0, 68);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 68);
    lwc1(f0, v0, 72);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 72);
    lwc1(f1, v0, 64);
    lwc1(f0, a0, 64);
    add_s(f0, f1, f0);
    swc1(f0, v0, 64);
    lwc1(f1, a0, 68);
    lwc1(f0, v0, 68);
    add_s(f0, f0, f1);
    swc1(f0, v0, 68);
    lwc1(f1, a0, 72);
    lwc1(f0, v0, 72);
    add_s(f0, f0, f1);
    swc1(f0, v0, 72);
    lwc1(f1, a1, 0);
    lw(v0, a0, 4);
    lwc1(f0, a0, 16);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 16);
    lwc1(f1, a1, 4);
    lwc1(f0, a0, 20);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 20);
    lwc1(f1, a1, 8);
    lwc1(f0, a0, 24);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 24);
    lwc1(f0, v0, 16);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 16);
    lwc1(f0, v0, 20);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 20);
    lwc1(f0, v0, 24);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 24);
    lwc1(f1, v0, 16);
    lwc1(f0, a0, 16);
    add_s(f0, f1, f0);
    swc1(f0, v0, 16);
    lwc1(f1, a0, 20);
    lwc1(f0, v0, 20);
    add_s(f0, f0, f1);
    swc1(f0, v0, 20);
    lwc1(f1, a0, 24);
    lwc1(f0, v0, 24);
    add_s(f0, f0, f1);
    swc1(f0, v0, 24);
    lwc1(f1, a1, 16);
    lw(v0, a0, 4);
    lwc1(f0, a0, 32);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 32);
    lwc1(f1, a1, 20);
    lwc1(f0, a0, 36);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 36);
    lwc1(f1, a1, 24);
    lwc1(f0, a0, 40);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 40);
    lwc1(f0, v0, 32);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 32);
    lwc1(f0, v0, 36);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 36);
    lwc1(f0, v0, 40);
    mul_s(f0, f0, f12);
    swc1(f0, v0, 40);
    lwc1(f1, v0, 32);
    lwc1(f0, a0, 32);
    add_s(f0, f1, f0);
    swc1(f0, v0, 32);
    lwc1(f1, a0, 36);
    lwc1(f0, v0, 36);
    add_s(f0, f0, f1);
    swc1(f0, v0, 36);
    lwc1(f1, a0, 40);
    lwc1(f0, v0, 40);
    add_s(f0, f0, f1);
    swc1(f0, v0, 40);
    lw(v0, a0, 4);
    a0 = addiu(v0, 16);
    jal(ctx, 0x4B266Cu, gen::fn_sub_4C2F10_004c2f10);
    link(ctx, 0x4B2674u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_4AE060_004ae060);
    sw(zero, s0, 8);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B43C0 [Rt2dMaestroCreate] -- creates a maestro from the maestro free list (0x95FA98), initialised by sub_4B4230;
//   the maestro, or 0
// 0x004B43C0 sub_4B43C0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B43C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b43c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = 0x960000;
    sd(ra, sp, 0x10);
    v1 = 0x30000;
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188
    a0 = addiu(a0, -1384);  // &0x95FA98
    a1 = v1 | 0x1B1;
    jalr(ctx, 0x4B43E0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004b43f4
        charge(ctx, 2);
        a0 = s0;
        jal(ctx, 0x4B43F4u, gen::fn_sub_4B4230_004b4230);
    }
    // 0x004b43fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4BCCD0 [textureStreamReadImages] -- reads a texture stored as images: the 72-byte header (names, image count,
//   format byte, filter / address nibbles), each image (chunk 24, sub_4CD750; non-palettised ones converted by
//   sub_4CD940), a raster of the best matching format (sub_4CDD50 / RwRasterCreate sub_4CE0F0; 8-bit falls back to 32- or
//   16-bit), the images resampled to each mip level (sub_4CEE30) and copied in (lock sub_4CE200 / sub_4CDCE0 / unlock
//   sub_4CDE00), the texture (sub_4D0E40) with its names, filter and address modes, added to the dictionary *$a1
//   (sub_4D1110); the dictionary, or 0
// 0x004BCCD0 sub_4BCCD0 -- 1424 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BCCD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004bccd0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    a2 = 72;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sw(a1, sp, 0xBC);
    sq(s1, sp, 0x10);
    a1 = addiu(sp, 0xC0);
    sq(s0, sp, 0x0);
    link(ctx, 0x4BCD0Cu);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xA0);
    call(ctx, gen::fn_sub_4C5250_004c5250);
    v1 = 72;
    if (v0 == v1) {
        // 0x004bcd28
        charge(ctx, 11);
        v0 = 0x10000;
        s0 = addiu(sp, 0x100);
        a1 = v0 | 0x1B3;
        lw(v1, s0, 0);
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = sll(v1, 2);
        jalr(ctx, 0x4BCD40u, v0.u());
        s5 = v0;
        if (s5 == 0) {
            // 0x004bcfcc
            charge(ctx, 12);
            lw(v1, s0, 0);
            v0 = 435;
            sw(v0, sp, 0x108);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            a1 = sll(v1, 2);
            jal(ctx, 0x4BCFE0u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x10C);
            a0 = addiu(sp, 0x108);
            jal(ctx, 0x4BCFECu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004bcd54
            charge(ctx, 4);
            lw(v0, s0, 0);
            v0 = slt(0, v0);
            s2 = 0;
            if (v0 != 0) {
                // 0x004bcffc
                charge(ctx, 1);
                s1 = s5;
                for (;;) {
                    // 0x004bd000
                    charge(ctx, 7);
                    a0 = s3;
                    a1 = 24;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x4BD00Cu, gen::fn_sub_4C1600_004c1600);
                    if (v0 == 0) {
                        break;
                    }
                    // 0x004bd024
                    charge(ctx, 6);
                    a0 = s3;
                    jal(ctx, 0x4BD024u, gen::fn_sub_4CD750_004cd750);
                    sw(v0, s1, 0);
                    lw(a0, s1, 0);
                    if (a0 == 0) {
                        goto L_004bd06c;
                    }
                    // 0x004bd03c
                    charge(ctx, 4);
                    lw(v0, a0, 0);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x004bd074
                        charge(ctx, 4);
                        jal(ctx, 0x4BD074u, gen::fn_sub_4CD940_004cd940);
                        backedge(ctx);
                    } else {
                        // 0x004bd04c
                        charge(ctx, 1);
                    }
                    // 0x004bd050
                    charge(ctx, 5);
                    lw(v0, s0, 0);
                    s2 = addiu(s2, 1);
                    v0 = slt(s2, v0);
                    s1 = addiu(s1, 4);
                    if (v0 == 0) {
                        goto L_004bd064_47;
                    }
                    backedge(ctx);
                }
                // 0x004bd01c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004bcd64
                charge(ctx, 1);
                lw(v1, s5, 0);
            L_004bcd68:
                charge(ctx, 12);
                s1 = 4;
                lw(v0, s0, 0);
                lw(v1, v1, 4);
                at = slti(v0, 2);
                sw(v1, sp, 0x11C);
                lw(v1, s5, 0);
                lw(v1, v1, 8);
                sw(v1, sp, 0x118);
                lw(v1, s5, 0);
                lw(v1, v1, 12);
                sw(v1, sp, 0x114);
                if (at != 0) {
                    // 0x004bcda0
                    charge(ctx, 4);
                    lbu(v1, sp, 0x104);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x004bcdb0
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 != v0) {
                            // 0x004bcdbc
                            charge(ctx, 1);
                            s1 = s1 | 0x9000;
                        }
                    }
                } else {
                    // 0x004bcd98
                    charge(ctx, 2);
                    s1 = s1 | 0x8000;
                }
                // 0x004bcdc0
                charge(ctx, 16);
                lw(a0, s5, 0);
                a1 = s1;
                a2 = addiu(sp, 0x11C);
                a3 = addiu(sp, 0x118);
                t0 = addiu(sp, 0x114);
                t1 = addiu(sp, 0x110);
                jal(ctx, 0x4BCDD4u, gen::fn_sub_4CDD50_004cdd50);
                lw(v0, sp, 0x110);
                lw(a0, sp, 0x11C);
                lw(a1, sp, 0x118);
                lw(a2, sp, 0x114);
                a3 = s1 | v0;
                jal(ctx, 0x4BCDECu, gen::fn_sub_4CE0F0_004ce0f0);
                s4 = v0;
                if (s4 != 0) {
                    // 0x004bce00
                    charge(ctx, 5);
                    lw(v1, s5, 0);
                    lw(s3, s4, 12);
                    lw(v0, v1, 4);
                    if (v0 == s3) {
                        // 0x004bce14
                        charge(ctx, 4);
                        lw(v1, v1, 8);
                        lw(v0, s4, 16);
                        if (v1 != v0) {
                            goto L_004bce24;
                        }
                    L_004bcef0:
                        charge(ctx, 4);
                        lw(v0, s0, 0);
                        at = slti(v0, 2);
                        if (at == 0) {
                            // 0x004bd0d0
                            charge(ctx, 8);
                            lbu(v1, s4, 35);
                            v0 = v1 & 0x10;
                            sw(v0, sp, 0xA0);
                            v0 = nor(v0, 0);
                            v0 = v0 & 0xFF;
                            v0 = v1 & v0;
                            sb(v0, s4, 35);
                            backedge(ctx);
                        }
                        // 0x004bcf00
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x4BCF00u, gen::fn_sub_4CDF80_004cdf80);
                        s1 = v0;
                        at = slt(0, s1);
                        s2 = 0;
                        if (at != 0) {
                            // 0x004bcf18
                            charge(ctx, 1);
                            s3 = s5;
                            for (;;) {
                                // 0x004bcf1c
                                charge(ctx, 3);
                                lw(v0, s0, 0);
                                if (s2 == v0) {
                                    goto L_004bcf80;
                                }
                                // 0x004bcf28
                                charge(ctx, 6);
                                a1 = s2 & 0xFF;
                                a0 = s4;
                                a2 = 1;
                                jal(ctx, 0x4BCF30u, gen::fn_sub_4CE200_004ce200);
                                if (v0 == 0) {
                                    goto L_004bd0f0;
                                }
                                // 0x004bcf40
                                charge(ctx, 5);
                                lw(a1, s3, 0);
                                a0 = s4;
                                jal(ctx, 0x4BCF44u, gen::fn_sub_4CDCE0_004cdce0);
                                if (v0 == 0) {
                                    goto L_004bd0f8;
                                }
                                // 0x004bcf54
                                charge(ctx, 4);
                                a0 = s4;
                                jal(ctx, 0x4BCF54u, gen::fn_sub_4CDE00_004cde00);
                                if (v0 == 0) {
                                    goto L_004bd100;
                                }
                                // 0x004bcf64
                                charge(ctx, 6);
                                link(ctx, 0x4BCF64u);  // $ra first: the delay slot below depends on it
                                lw(a0, s3, 0);
                                call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                                s2 = addiu(s2, 1);
                                v0 = slt(s2, s1);
                                s3 = addiu(s3, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004bcf7c
                            charge(ctx, 1);
                        }
                    L_004bcf80:
                        charge(ctx, 4);
                        lw(v0, s0, 0);
                        at = slti(v0, 2);
                        if (at == 0) {
                            // 0x004bd108
                            charge(ctx, 6);
                            lbu(v0, sp, 0xA0);
                            v1 = v0;
                            lbu(v0, s4, 35);
                            v0 = v0 | v1;
                            sb(v0, s4, 35);
                            backedge(ctx);
                        }
                        // 0x004bcf90
                        charge(ctx, 4);
                        lw(v0, s0, 0);
                        at = slt(s2, v0);
                        if (at != 0) {
                            // 0x004bcfa0
                            charge(ctx, 2);
                            v0 = sll(s2, 2);
                            s1 = addu(s5, v0);
                            for (;;) {
                                // 0x004bcfa8
                                charge(ctx, 7);
                                link(ctx, 0x4BCFA8u);  // $ra first: the delay slot below depends on it
                                lw(a0, s1, 0);
                                call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                                lw(v0, s0, 0);
                                s2 = addiu(s2, 1);
                                v0 = slt(s2, v0);
                                s1 = addiu(s1, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004bcfc4
                            charge(ctx, 2);
                        }
                        // 0x004bd120
                        charge(ctx, 9);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C
                        a0 = s5;
                        jalr(ctx, 0x4BD128u, v0.u());
                        a0 = s4;
                        jal(ctx, 0x4BD130u, gen::fn_sub_4D0E40_004d0e40);
                        s0 = v0;
                        if (s0 == 0) {
                            // 0x004bd204
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x004bd144
                            charge(ctx, 19);
                            a0 = s0;
                            a1 = addiu(sp, 0xC0);
                            jal(ctx, 0x4BD148u, gen::fn_sub_4D0FD0_004d0fd0);
                            a0 = s0;
                            a1 = addiu(sp, 0xE0);
                            jal(ctx, 0x4BD154u, gen::fn_sub_4D1070_004d1070);
                            a1 = addiu(sp, 0x104);
                            lw(a0, s0, 80);
                            lbu(v0, a1, 0);
                            v1 = si(-256);
                            v1 = a0 & v1;
                            v0 = v1 | v0;
                            sw(v0, s0, 80);
                            lw(v0, a1, 0);
                            v1 = v0 & 0xF00;
                            v0 = v0 & 0xF000;
                            v1 = srl(v1, 8);
                            v0 = srl(v0, 12);
                            if (v1 == 0) {
                                // 0x004bd20c
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    backedge(ctx);
                                    goto L_004bd190;
                                }
                                // 0x004bd214
                                charge(ctx, 3);
                                v0 = 1;
                                v1 = v0;
                                backedge(ctx);
                                goto L_004bd1ac;
                            }
                        L_004bd190:
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x004bd220
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    backedge(ctx);
                                    goto L_004bd198;
                                }
                                // 0x004bd228
                                charge(ctx, 2);
                                v1 = v0;
                                backedge(ctx);
                                goto L_004bd1ac;
                            }
                        L_004bd198:
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x004bd1a0
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x004bd1a8
                                    charge(ctx, 1);
                                    v0 = v1;
                                }
                            }
                        L_004bd1ac:
                            charge(ctx, 22);
                            lw(a3, s0, 80);
                            v1 = sll(v1, 8);
                            a2 = si(-3841);
                            a0 = v1 & 0xF00;
                            v1 = lui(0xFFFF);
                            v0 = sll(v0, 12);
                            v1 = v1 | 0xFFF;
                            v0 = v0 & 0xF000;
                            a2 = a3 & a2;
                            a0 = a2 | a0;
                            sw(a0, s0, 80);
                            lw(a0, s0, 80);
                            v1 = a0 & v1;
                            v0 = v1 | v0;
                            sw(v0, s0, 80);
                            lw(v0, sp, 0xBC);
                            lw(a0, v0, 0);
                            a1 = s0;
                            jal(ctx, 0x4BD1F0u, gen::fn_sub_4D1110_004d1110);
                            lw(v0, sp, 0xBC);
                            lw(v0, v0, 0);
                        }
                        // 0x004bd230 (the shared epilogue, written out on this path)
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
                        return;
                    }
                L_004bce24:
                    charge(ctx, 4);
                    lw(v1, sp, 0x114);
                    v0 = 8;
                    lw(s2, s4, 16);
                    if (v1 == v0) {
                        // 0x004bce34
                        charge(ctx, 10);
                        a0 = s4;
                        jal(ctx, 0x4BCE34u, gen::fn_sub_4CDE90_004cde90);
                        a3 = s1 | 0x500;
                        a0 = s3;
                        a1 = s2;
                        a2 = 32;
                        jal(ctx, 0x4BCE48u, gen::fn_sub_4CE0F0_004ce0f0);
                        s4 = v0;
                        if (s4 == 0) {
                            // 0x004bce5c
                            charge(ctx, 6);
                            a3 = s1 | 0x100;
                            a0 = s3;
                            a1 = s2;
                            a2 = 16;
                            jal(ctx, 0x4BCE68u, gen::fn_sub_4CE0F0_004ce0f0);
                            s4 = v0;
                        }
                    }
                    // 0x004bce74
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x4BCE74u, gen::fn_sub_4CDF80_004cdf80);
                    fp = v0;
                    at = slt(0, fp);
                    s6 = 0;
                    if (at == 0) {
                        goto L_004bcef0;
                    }
                    // 0x004bce8c
                    charge(ctx, 1);
                    s1 = s5;
                    for (;;) {
                        // 0x004bce90
                        charge(ctx, 7);
                        lw(a0, s1, 0);
                        a1 = s3;
                        a2 = s2;
                        jal(ctx, 0x4BCE98u, gen::fn_sub_4CEE30_004cee30);
                        s7 = v0;
                        if (s7 == 0) {
                            goto L_004bceac_19;
                        }
                        // 0x004bceb4
                        charge(ctx, 5);
                        link(ctx, 0x4BCEB4u);  // $ra first: the delay slot below depends on it
                        lw(a0, s1, 0);
                        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                        at = slti(s3, 2);
                        sw(s7, s1, 0);
                        if (at == 0) {
                            // 0x004bcec8
                            charge(ctx, 2);
                            s3 = sra(s3, 1);
                        }
                        // 0x004bced0
                        charge(ctx, 3);
                        at = slti(s2, 2);
                        if (at == 0) {
                            // 0x004bcedc
                            charge(ctx, 1);
                            s2 = sra(s2, 1);
                        }
                        // 0x004bcee0
                        charge(ctx, 4);
                        s6 = addiu(s6, 1);
                        v0 = slt(s6, fp);
                        s1 = addiu(s1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    goto L_004bcef0;
                }
                // 0x004bd088
                charge(ctx, 4);
                lw(v0, s0, 0);
                at = slt(0, v0);
                s1 = 0;
                if (at != 0) {
                    // 0x004bd098
                    charge(ctx, 1);
                    s2 = s5;
                    for (;;) {
                        // 0x004bd09c
                        charge(ctx, 7);
                        link(ctx, 0x4BD09Cu);  // $ra first: the delay slot below depends on it
                        lw(a0, s2, 0);
                        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                        lw(v0, s0, 0);
                        s1 = addiu(s1, 1);
                        v0 = slt(s1, v0);
                        s2 = addiu(s2, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004bd0b8
                charge(ctx, 6);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                a0 = s5;
                jalr(ctx, 0x4BD0C0u, v0.u());
                v0 = 0;
            }
        }
    } else {
        // 0x004bcd20
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004bd230 (the shared epilogue, written out on this path)
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
    return;
L_004bceac_19:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd230 (the shared epilogue, written out on this path)
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
    return;
L_004bd064_47:
    charge(ctx, 2);
    lw(v1, s5, 0);
    backedge(ctx);
    goto L_004bcd68;
L_004bd06c:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd230 (the shared epilogue, written out on this path)
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
    return;
L_004bd0f0:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd230 (the shared epilogue, written out on this path)
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
    return;
L_004bd0f8:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd230 (the shared epilogue, written out on this path)
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
    return;
L_004bd100:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd230 (the shared epilogue, written out on this path)
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

// sub_4BD260 [textureStreamReadHeader] -- reads a texture chunk's struct for an image-stored texture (chunk version
//   0x35000..0x37002, else error 0x80000004): the filter / address word (a missing V address copied from U), the
//   mipmapping and auto-mipmapping flags set for the filter mode (sub_4D0B60 / sub_4D0BA0; restored after), the name and
//   mask strings (sub_4C78A0), a texture without raster (sub_4D0E40) with those names and, for a raster-less one, the
//   filter word; on a failure the extensions are skipped (sub_4C5EA0 on 0x77E6D0); the texture, or 0
// 0x004BD260 sub_4BD260 -- 640 bytes; frame 0x180: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BD260(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bd260
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    a1 = 1;
    sd(ra, sp, 0x50);
    a2 = addiu(sp, 0x17C);
    sq(s4, sp, 0x40);
    a3 = addiu(sp, 0x178);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4BD288u, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004bd400
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004bd298
        charge(ctx, 6);
        lw(v1, sp, 0x178);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004bd2b0
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004bd49c;
            }
            // 0x004bd2c4
            charge(ctx, 11);
            a0 = addiu(sp, 0x174);
            a1 = 0;
            a2 = 4;
            jal(ctx, 0x4BD2CCu, gen::fn_memset_00521408);
            lw(s1, sp, 0x17C);
            a0 = s0;
            a1 = addiu(sp, 0x174);
            a2 = s1;
            jal(ctx, 0x4BD2E0u, gen::fn_sub_4C5250_004c5250);
            if (s1 != v0) {
                // 0x004bd408
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004bd2f0
                charge(ctx, 7);
                lw(a0, sp, 0x174);
                v0 = srl(a0, 8);
                v1 = v0 & 0xF;
                v0 = srl(a0, 12);
                v0 = v0 & 0xF;
                s2 = a0 & 0xFF;
                if (v0 == 0) {
                    // 0x004bd410
                    charge(ctx, 5);
                    v0 = v1 & 0xF;
                    v0 = sll(v0, 12);
                    v0 = a0 | v0;
                    sw(v0, sp, 0x174);
                    backedge(ctx);
                }
                // 0x004bd30c
                charge(ctx, 11);
                lw(v0, sp, 0x174);
                v0 = srl(v0, 16);
                s1 = v0 & 0xFF;
                jal(ctx, 0x4BD314u, gen::fn_sub_4D0B80_004d0b80);
                s4 = v0;
                jal(ctx, 0x4BD31Cu, gen::fn_sub_4D0BC0_004d0bc0);
                s3 = v0;
                v0 = addiu(s2, -3);
                at = sltiu(v0, 4);
                if (at == 0) {
                    // 0x004bd36c
                    charge(ctx, 4);
                    a0 = 0;
                    jal(ctx, 0x4BD36Cu, gen::fn_sub_4D0B60_004d0b60);
                    a0 = 0;
                    jal(ctx, 0x4BD374u, gen::fn_sub_4D0BA0_004d0ba0);
                L_004bd37c:
                    charge(ctx, 1);
                    a0 = addiu(sp, 0xE0);
                } else {
                    // 0x004bd338
                    charge(ctx, 5);
                    a0 = 1;
                    jal(ctx, 0x4BD338u, gen::fn_sub_4D0B60_004d0b60);
                    v0 = s1 & 0x1;
                    if (v0 == 0) {
                        // 0x004bd35c
                        charge(ctx, 4);
                        a0 = 1;
                        jal(ctx, 0x4BD35Cu, gen::fn_sub_4D0BA0_004d0ba0);
                        goto L_004bd37c;
                    }
                    // 0x004bd34c
                    charge(ctx, 4);
                    a0 = 0;
                    jal(ctx, 0x4BD34Cu, gen::fn_sub_4D0BA0_004d0ba0);
                    a0 = addiu(sp, 0xE0);
                }
                // 0x004bd380
                charge(ctx, 4);
                a1 = s0;
                jal(ctx, 0x4BD380u, gen::fn_sub_4C78A0_004c78a0);
                if (v0 == 0) {
                    // 0x004bd424
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x4BD424u, gen::fn_sub_4D0B60_004d0b60);
                    a0 = s3;
                    jal(ctx, 0x4BD42Cu, gen::fn_sub_4D0BA0_004d0ba0);
                    v0 = 0;
                } else {
                    // 0x004bd390
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x60);
                    a1 = s0;
                    jal(ctx, 0x4BD394u, gen::fn_sub_4C78A0_004c78a0);
                    if (v0 == 0) {
                        // 0x004bd43c
                        charge(ctx, 6);
                        a0 = s4;
                        jal(ctx, 0x4BD43Cu, gen::fn_sub_4D0B60_004d0b60);
                        a0 = s3;
                        jal(ctx, 0x4BD444u, gen::fn_sub_4D0BA0_004d0ba0);
                        v0 = 0;
                    } else {
                        // 0x004bd3a4
                        charge(ctx, 5);
                        a0 = 0;
                        jal(ctx, 0x4BD3A4u, gen::fn_sub_4D0E40_004d0e40);
                        s1 = v0;
                        if (s1 == 0) {
                            // 0x004bd454
                            charge(ctx, 10);
                            a0 = 0x780000;
                            a1 = s0;
                            a0 = addiu(a0, -6448);  // &0x77E6D0
                            jal(ctx, 0x4BD45Cu, gen::fn_sub_4C5EA0_004c5ea0);
                            a0 = s4;
                            jal(ctx, 0x4BD464u, gen::fn_sub_4D0B60_004d0b60);
                            a0 = s3;
                            jal(ctx, 0x4BD46Cu, gen::fn_sub_4D0BA0_004d0ba0);
                            v0 = 0;
                        } else {
                            // 0x004bd3b8
                            charge(ctx, 6);
                            a0 = s1;
                            a1 = addiu(sp, 0xE0);
                            jal(ctx, 0x4BD3BCu, gen::fn_sub_4D0FD0_004d0fd0);
                            a1 = addiu(sp, 0x60);
                            if (a1 == 0) {
                                // 0x004bd47c
                                charge(ctx, 5);
                                a0 = s1;
                                a1 = addiu(gp, -20448);  // &0x7CDD10
                                jal(ctx, 0x4BD480u, gen::fn_sub_4D1070_004d1070);
                                lw(v1, s1, 84);
                                backedge(ctx);
                            } else {
                                // 0x004bd3d0
                                charge(ctx, 3);
                                a0 = s1;
                                jal(ctx, 0x4BD3D0u, gen::fn_sub_4D1070_004d1070);
                                lw(v1, s1, 84);
                            }
                            // 0x004bd3dc
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x004bd490
                                charge(ctx, 3);
                                lhu(v0, sp, 0x174);
                                sw(v0, s1, 80);
                                backedge(ctx);
                            }
                            // 0x004bd3e8
                            charge(ctx, 6);
                            a0 = s4;
                            jal(ctx, 0x4BD3E8u, gen::fn_sub_4D0B60_004d0b60);
                            a0 = s3;
                            jal(ctx, 0x4BD3F0u, gen::fn_sub_4D0BA0_004d0ba0);
                            v0 = s1;
                        }
                    }
                }
            }
            // 0x004bd4c0 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x180);
            return;
        }
    L_004bd49c:
        charge(ctx, 9);
        v1 = 435;
        v0 = lui(0x8000);
        sw(v1, sp, 0x168);
        a0 = v0 | 0x4;
        jal(ctx, 0x4BD4A8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x16C);
        a0 = addiu(sp, 0x168);
        jal(ctx, 0x4BD4B4u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004bd4c0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// sub_4BD4E0 [textureReadImageEntry] -- reads one image-stored texture of a dictionary: the image count and images
//   (chunk 24, sub_4CD750; non-palettised ones converted), the texture header (chunk 6, sub_4BD260), a raster of the best
//   format (sub_4CDD50 / RwRasterCreate), the images resampled per mip level and copied in, the raster given to the
//   texture (sub_4D0BE0), its extensions (sub_4C5A50 on 0x77E6D0), added to the current dictionary (sub_4D11F0 /
//   sub_4D1110); 1, or 0
// 0x004BD4E0 sub_4BD4E0 -- 1328 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BD4E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004bd4e0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    a2 = 4;
    sd(ra, sp, 0x90);
    a1 = addiu(sp, 0xDC);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    link(ctx, 0x4BD518u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xB0);
    call(ctx, gen::fn_sub_4C5250_004c5250);
    v1 = 4;
    if (v0 == v1) {
        // 0x004bd534
        charge(ctx, 10);
        v0 = 0x10000;
        lw(v1, sp, 0xDC);
        a1 = v0 | 0x1B3;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = sll(v1, 2);
        jalr(ctx, 0x4BD548u, v0.u());
        s4 = v0;
        if (s4 == 0) {
            // 0x004bd5fc
            charge(ctx, 12);
            lw(v1, sp, 0xDC);
            v0 = 435;
            sw(v0, sp, 0xC0);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            a1 = sll(v1, 2);
            jal(ctx, 0x4BD610u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xC4);
            a0 = addiu(sp, 0xC0);
            jal(ctx, 0x4BD61Cu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004bd55c
            charge(ctx, 4);
            lw(v0, sp, 0xDC);
            at = slt(0, v0);
            s1 = 0;
            if (at != 0) {
                // 0x004bd56c
                charge(ctx, 1);
                s0 = s4;
                for (;;) {
                    // 0x004bd570
                    charge(ctx, 7);
                    a0 = s5;
                    a1 = 24;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x4BD57Cu, gen::fn_sub_4C1600_004c1600);
                    if (v0 == 0) {
                        break;
                    }
                    // 0x004bd594
                    charge(ctx, 6);
                    a0 = s5;
                    jal(ctx, 0x4BD594u, gen::fn_sub_4CD750_004cd750);
                    sw(v0, s0, 0);
                    lw(a0, s0, 0);
                    if (a0 == 0) {
                        goto L_004bd62c;
                    }
                    // 0x004bd5ac
                    charge(ctx, 4);
                    lw(v0, a0, 0);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x004bd634
                        charge(ctx, 4);
                        jal(ctx, 0x4BD634u, gen::fn_sub_4CD940_004cd940);
                        backedge(ctx);
                    } else {
                        // 0x004bd5bc
                        charge(ctx, 1);
                    }
                    // 0x004bd5c0
                    charge(ctx, 5);
                    lw(v0, sp, 0xDC);
                    s1 = addiu(s1, 1);
                    v0 = slt(s1, v0);
                    s0 = addiu(s0, 4);
                    if (v0 == 0) {
                        goto L_004bd5d4_11;
                    }
                    backedge(ctx);
                }
                // 0x004bd58c
                charge(ctx, 2);
                v0 = 0;
                // 0x004bd9e0 (the shared epilogue, written out on this path)
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
                sp = addiu(sp, 0xE0);
                return;
            }
        L_004bd5d8:
            charge(ctx, 7);
            a0 = s5;
            a1 = 6;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x4BD5E4u, gen::fn_sub_4C1600_004c1600);
            if (v0 != 0) {
                // 0x004bd648
                charge(ctx, 4);
                a0 = s5;
                jal(ctx, 0x4BD648u, gen::fn_sub_4BD260_004bd260);
                sw(v0, sp, 0xA0);
                if (v0 == 0) {
                    // 0x004bd8c4
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004bd658
                    charge(ctx, 13);
                    lw(v1, s4, 0);
                    s0 = 4;
                    lw(v0, sp, 0xDC);
                    lw(v1, v1, 4);
                    at = slti(v0, 2);
                    sw(v1, sp, 0xD8);
                    lw(v1, s4, 0);
                    lw(v1, v1, 8);
                    sw(v1, sp, 0xD4);
                    lw(v1, s4, 0);
                    lw(v1, v1, 12);
                    sw(v1, sp, 0xD0);
                    if (at != 0) {
                        // 0x004bd694
                        charge(ctx, 5);
                        lw(v0, sp, 0xA0);
                        lbu(v1, v0, 80);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x004bd6a8
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 != v0) {
                                // 0x004bd6b4
                                charge(ctx, 1);
                                s0 = s0 | 0x9000;
                            }
                        }
                    } else {
                        // 0x004bd68c
                        charge(ctx, 2);
                        s0 = s0 | 0x8000;
                    }
                    // 0x004bd6b8
                    charge(ctx, 16);
                    lw(a0, s4, 0);
                    a1 = s0;
                    a2 = addiu(sp, 0xD8);
                    a3 = addiu(sp, 0xD4);
                    t0 = addiu(sp, 0xD0);
                    t1 = addiu(sp, 0xCC);
                    jal(ctx, 0x4BD6CCu, gen::fn_sub_4CDD50_004cdd50);
                    lw(v0, sp, 0xCC);
                    lw(a0, sp, 0xD8);
                    lw(a1, sp, 0xD4);
                    lw(a2, sp, 0xD0);
                    a3 = s0 | v0;
                    jal(ctx, 0x4BD6E4u, gen::fn_sub_4CE0F0_004ce0f0);
                    s3 = v0;
                    if (s3 != 0) {
                        // 0x004bd6f8
                        charge(ctx, 5);
                        lw(v1, s4, 0);
                        lw(s2, s3, 12);
                        lw(v0, v1, 4);
                        if (v0 == s2) {
                            // 0x004bd70c
                            charge(ctx, 4);
                            lw(v1, v1, 8);
                            lw(v0, s3, 16);
                            if (v1 != v0) {
                                goto L_004bd71c;
                            }
                        L_004bd7e8:
                            charge(ctx, 4);
                            lw(v0, sp, 0xDC);
                            at = slti(v0, 2);
                            if (at == 0) {
                                // 0x004bd918
                                charge(ctx, 8);
                                lbu(v1, s3, 35);
                                v0 = v1 & 0x10;
                                sw(v0, sp, 0xB0);
                                v0 = nor(v0, 0);
                                v0 = v0 & 0xFF;
                                v0 = v1 & v0;
                                sb(v0, s3, 35);
                                backedge(ctx);
                            }
                            // 0x004bd7f8
                            charge(ctx, 6);
                            a0 = s3;
                            jal(ctx, 0x4BD7F8u, gen::fn_sub_4CDF80_004cdf80);
                            s0 = v0;
                            at = slt(0, s0);
                            s1 = 0;
                            if (at != 0) {
                                // 0x004bd810
                                charge(ctx, 1);
                                s2 = s4;
                                for (;;) {
                                    // 0x004bd814
                                    charge(ctx, 3);
                                    lw(v0, sp, 0xDC);
                                    if (s1 == v0) {
                                        goto L_004bd878;
                                    }
                                    // 0x004bd820
                                    charge(ctx, 6);
                                    a1 = s1 & 0xFF;
                                    a0 = s3;
                                    a2 = 1;
                                    jal(ctx, 0x4BD828u, gen::fn_sub_4CE200_004ce200);
                                    if (v0 == 0) {
                                        goto L_004bd938;
                                    }
                                    // 0x004bd838
                                    charge(ctx, 5);
                                    lw(a1, s2, 0);
                                    a0 = s3;
                                    jal(ctx, 0x4BD83Cu, gen::fn_sub_4CDCE0_004cdce0);
                                    if (v0 == 0) {
                                        goto L_004bd940;
                                    }
                                    // 0x004bd84c
                                    charge(ctx, 4);
                                    a0 = s3;
                                    jal(ctx, 0x4BD84Cu, gen::fn_sub_4CDE00_004cde00);
                                    if (v0 == 0) {
                                        goto L_004bd948;
                                    }
                                    // 0x004bd85c
                                    charge(ctx, 6);
                                    link(ctx, 0x4BD85Cu);  // $ra first: the delay slot below depends on it
                                    lw(a0, s2, 0);
                                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                                    s1 = addiu(s1, 1);
                                    v0 = slt(s1, s0);
                                    s2 = addiu(s2, 4);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004bd874
                                charge(ctx, 1);
                            }
                        L_004bd878:
                            charge(ctx, 4);
                            lw(v0, sp, 0xDC);
                            at = slti(v0, 2);
                            if (at == 0) {
                                // 0x004bd950
                                charge(ctx, 6);
                                lbu(v0, sp, 0xB0);
                                v1 = v0;
                                lbu(v0, s3, 35);
                                v0 = v0 | v1;
                                sb(v0, s3, 35);
                                backedge(ctx);
                            }
                            // 0x004bd888
                            charge(ctx, 4);
                            lw(v0, sp, 0xDC);
                            at = slt(s1, v0);
                            if (at != 0) {
                                // 0x004bd898
                                charge(ctx, 2);
                                v0 = sll(s1, 2);
                                s0 = addu(s4, v0);
                                for (;;) {
                                    // 0x004bd8a0
                                    charge(ctx, 7);
                                    link(ctx, 0x4BD8A0u);  // $ra first: the delay slot below depends on it
                                    lw(a0, s0, 0);
                                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                                    lw(v0, sp, 0xDC);
                                    s1 = addiu(s1, 1);
                                    v0 = slt(s1, v0);
                                    s0 = addiu(s0, 4);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004bd8bc
                                charge(ctx, 2);
                            }
                            // 0x004bd968
                            charge(ctx, 14);
                            v0 = 0x960000;
                            lw(v0, v0, 380);  // 0x96017C
                            a0 = s4;
                            jalr(ctx, 0x4BD970u, v0.u());
                            lw(a0, sp, 0xA0);
                            a1 = s3;
                            jal(ctx, 0x4BD97Cu, gen::fn_sub_4D0BE0_004d0be0);
                            lw(a2, sp, 0xA0);
                            a0 = 0x780000;
                            a1 = s5;
                            a0 = addiu(a0, -6448);  // &0x77E6D0
                            jal(ctx, 0x4BD990u, gen::fn_sub_4C5A50_004c5a50);
                            if (v0 == 0) {
                                // 0x004bd9a0
                                charge(ctx, 1);
                                sw(zero, sp, 0xA0);
                                goto L_004bd9a4;
                            }
                            // 0x004bd9b8
                            charge(ctx, 4);
                            jal(ctx, 0x4BD9B8u, gen::fn_sub_4D11F0_004d11f0);
                            if (v0 == 0) {
                                backedge(ctx);
                            L_004bd9a4:
                                charge(ctx, 1);
                                lw(v0, sp, 0xA0);
                            } else {
                                // 0x004bd9c8
                                charge(ctx, 5);
                                lw(a1, sp, 0xA0);
                                a0 = v0;
                                jal(ctx, 0x4BD9CCu, gen::fn_sub_4D1110_004d1110);
                                lw(v0, sp, 0xA0);
                                backedge(ctx);
                            }
                            // 0x004bd9a8
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x004bd9dc
                                charge(ctx, 1);
                                v0 = 0;
                            } else {
                                // 0x004bd9b0
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bd9e0 (the shared epilogue, written out on this path)
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
                            sp = addiu(sp, 0xE0);
                            return;
                        }
                    L_004bd71c:
                        charge(ctx, 4);
                        lw(v1, sp, 0xD0);
                        v0 = 8;
                        lw(s1, s3, 16);
                        if (v1 == v0) {
                            // 0x004bd72c
                            charge(ctx, 10);
                            a0 = s3;
                            jal(ctx, 0x4BD72Cu, gen::fn_sub_4CDE90_004cde90);
                            a3 = s0 | 0x500;
                            a0 = s2;
                            a1 = s1;
                            a2 = 32;
                            jal(ctx, 0x4BD740u, gen::fn_sub_4CE0F0_004ce0f0);
                            s3 = v0;
                            if (s3 == 0) {
                                // 0x004bd754
                                charge(ctx, 6);
                                a3 = s0 | 0x100;
                                a0 = s2;
                                a1 = s1;
                                a2 = 16;
                                jal(ctx, 0x4BD760u, gen::fn_sub_4CE0F0_004ce0f0);
                                s3 = v0;
                            }
                        }
                        // 0x004bd76c
                        charge(ctx, 6);
                        a0 = s3;
                        jal(ctx, 0x4BD76Cu, gen::fn_sub_4CDF80_004cdf80);
                        fp = v0;
                        at = slt(0, fp);
                        s6 = 0;
                        if (at == 0) {
                            goto L_004bd7e8;
                        }
                        // 0x004bd784
                        charge(ctx, 1);
                        s0 = s4;
                        for (;;) {
                            // 0x004bd788
                            charge(ctx, 7);
                            lw(a0, s0, 0);
                            a1 = s2;
                            a2 = s1;
                            jal(ctx, 0x4BD790u, gen::fn_sub_4CEE30_004cee30);
                            s7 = v0;
                            if (s7 == 0) {
                                goto L_004bd7a4_32;
                            }
                            // 0x004bd7ac
                            charge(ctx, 5);
                            link(ctx, 0x4BD7ACu);  // $ra first: the delay slot below depends on it
                            lw(a0, s0, 0);
                            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                            at = slti(s2, 2);
                            sw(s7, s0, 0);
                            if (at == 0) {
                                // 0x004bd7c0
                                charge(ctx, 2);
                                s2 = sra(s2, 1);
                            }
                            // 0x004bd7c8
                            charge(ctx, 3);
                            at = slti(s1, 2);
                            if (at == 0) {
                                // 0x004bd7d4
                                charge(ctx, 1);
                                s1 = sra(s1, 1);
                            }
                            // 0x004bd7d8
                            charge(ctx, 4);
                            s6 = addiu(s6, 1);
                            v0 = slt(s6, fp);
                            s0 = addiu(s0, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        goto L_004bd7e8;
                    }
                    // 0x004bd8cc
                    charge(ctx, 4);
                    lw(v0, sp, 0xDC);
                    at = slt(0, v0);
                    s0 = 0;
                    if (at != 0) {
                        // 0x004bd8dc
                        charge(ctx, 1);
                        s1 = s4;
                        for (;;) {
                            // 0x004bd8e0
                            charge(ctx, 7);
                            link(ctx, 0x4BD8E0u);  // $ra first: the delay slot below depends on it
                            lw(a0, s1, 0);
                            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                            lw(v0, sp, 0xDC);
                            s0 = addiu(s0, 1);
                            v0 = slt(s0, v0);
                            s1 = addiu(s1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004bd8fc
                        charge(ctx, 1);
                    }
                    // 0x004bd900
                    charge(ctx, 6);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    a0 = s4;
                    jalr(ctx, 0x4BD908u, v0.u());
                    v0 = 0;
                }
            } else {
                // 0x004bd5f4
                charge(ctx, 2);
                v0 = 0;
            }
        }
    } else {
        // 0x004bd52c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004bd9e0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
    return;
L_004bd5d4_11:
    charge(ctx, 1);
    goto L_004bd5d8;
L_004bd62c:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd9e0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
    return;
L_004bd7a4_32:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd9e0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
    return;
L_004bd938:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd9e0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
    return;
L_004bd940:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd9e0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
    return;
L_004bd948:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bd9e0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
}

// sub_4BDA10 [texDictStreamReadImages] -- reads a texture dictionary stored as images: the count and device id, a new
//   dictionary (sub_4D0C30), then per texture sub_4BCCD0 (device 0) or, with the dictionary made current (sub_4D11D0,
//   restored after), sub_4BD4E0; the dictionary, or 0
// 0x004BDA10 sub_4BDA10 -- 280 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BDA10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bda10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a2 = 4;
    sd(ra, sp, 0x30);
    a1 = addiu(sp, 0x48);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4BDA2Cu, gen::fn_sub_4C5250_004c5250);
    at = sltiu(v0, 4);
    if (at == 0) {
        // 0x004bda48
        charge(ctx, 4);
        jal(ctx, 0x4BDA48u, gen::fn_sub_4D0C30_004d0c30);
        sw(v0, sp, 0x4C);
        if (v0 == 0) {
            // 0x004bdaa0
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004bda58
            charge(ctx, 3);
            lhu(v0, sp, 0x4A);
            if (i64(v0) <= 0) {
                // 0x004bda64
                charge(ctx, 4);
                lhu(v0, sp, 0x48);
                at = sltu(0, v0);
                s1 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004bda74
                        charge(ctx, 8);
                        a0 = s0;
                        a1 = addiu(sp, 0x4C);
                        jal(ctx, 0x4BDA78u, gen::fn_sub_4BCCD0_004bccd0);
                        lhu(v0, sp, 0x48);
                        s1 = addiu(s1, 1);
                        v0 = sltu(s1, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004bda94
                    charge(ctx, 1);
                }
                goto L_004bda98;
            }
            // 0x004bdaa8
            charge(ctx, 9);
            jal(ctx, 0x4BDAA8u, gen::fn_sub_4D11F0_004d11f0);
            lw(a0, sp, 0x4C);
            s2 = v0;
            jal(ctx, 0x4BDAB4u, gen::fn_sub_4D11D0_004d11d0);
            lhu(v0, sp, 0x48);
            at = sltu(0, v0);
            s1 = 0;
            if (at != 0) {
                for (;;) {
                    // 0x004bdacc
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x4BDACCu, gen::fn_sub_4BD4E0_004bd4e0);
                    if (v0 == 0) {
                        goto L_004bdadc_11;
                    }
                    // 0x004bdaec
                    charge(ctx, 5);
                    lhu(v0, sp, 0x48);
                    s1 = addiu(s1, 1);
                    v0 = sltu(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004bdb00
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x4BDB00u, gen::fn_sub_4D11D0_004d11d0);
            backedge(ctx);
        L_004bda98:
            charge(ctx, 2);
            lw(v0, sp, 0x4C);
        }
    } else {
        // 0x004bda40
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004bdb10 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004bdadc_11:
    charge(ctx, 4);
    a0 = s2;
    jal(ctx, 0x4BDADCu, gen::fn_sub_4D11D0_004d11d0);
    v0 = 0;
    // 0x004bdb10 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4BEC20 [RtTileRender] -- renders an image in tiles: a tile camera cloned from $a0 (its frame, view window, clip
//   planes; frame and z rasters as sub-rasters of the camera's), a tile image (sub_4CBE00 / sub_4CBF20) and frame
//   (sub_4CAF10); for each tile row and column the camera shifted (its view offset), the render callback $t1 called, the
//   raster locked and read into the image, the archive callback $t2 called (the built-in sub_4BF560 gets the BMP writer's
//   state, sub_4BE930); everything released after; 1, or 0 (bad sizes: not multiples of the tile size)
// 0x004BEC20 sub_4BEC20 -- 2332 bytes; frame 0x1B0: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_4BEC20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30};
    // 0x004bec20
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    s6 = a2;
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    s4 = a0;
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f30, sp, 0x28);
    s0 = a1;
    swc1(f29, sp, 0x24);
    sw(a3, sp, 0x14C);
    swc1(f28, sp, 0x20);
    sw(t0, sp, 0x148);
    swc1(f27, sp, 0x1C);
    sw(t1, sp, 0x140);
    swc1(f26, sp, 0x18);
    sw(t2, sp, 0x13C);
    swc1(f25, sp, 0x14);
    sw(t3, sp, 0x138);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    if (i64(s0) > 0) {
        // 0x004bec9c
        charge(ctx, 2);
        if (i64(s6) <= 0) {
            goto L_004bed00;
        }
        // 0x004beca4
        charge(ctx, 3);
        v0 = a3;
        if (i64(v0) <= 0) {
            goto L_004bed00;
        }
        // 0x004becb0
        charge(ctx, 3);
        v0 = t0;
        if (i64(v0) <= 0) {
            goto L_004bed00;
        }
        // 0x004becbc
        charge(ctx, 4);
        v0 = a3;
        v0 = slt(s0, v0);
        if (v0 != 0) {
            goto L_004bed00;
        }
        // 0x004beccc
        charge(ctx, 4);
        v0 = t0;
        v0 = slt(s6, v0);
        if (v0 != 0) {
            goto L_004bed00;
        }
        // 0x004becdc
        charge(ctx, 2);
        if (s4 == 0) {
            goto L_004bed00;
        }
        // 0x004bece4
        charge(ctx, 5);
        v0 = a3;
        div(s0, v0);
        mfhi(v0);
        if (i64(v0) <= 0) {
            // 0x004bed08
            charge(ctx, 5);
            v0 = t0;
            div(s6, v0);
            mfhi(v0);
            if (i64(v0) > 0) {
                backedge(ctx);
                goto L_004becf8;
            }
            // 0x004bed1c
            charge(ctx, 26);
            lw(v0, sp, 0x1B0);
            fp = 0;
            s3 = 0;
            sw(zero, sp, 0x11C);
            sw(zero, sp, 0x110);
            s1 = 0;
            sw(v0, sp, 0x150);
            v0 = addiu(sp, 0x158);
            sw(zero, v0, 0);
            v0 = addiu(sp, 0x180);
            link(ctx, 0x4BED44u);  // $ra first: the delay slot below depends on it
            sw(zero, v0, 0);
            call(ctx, gen::fn_sub_4CA090_004ca090);
            s5 = v0;
            lw(a0, s4, 4);
            lw(v0, s4, 20);
            lw(s7, s4, 96);
            sq(v0, sp, 0xE0);
            lw(v0, s4, 100);
            link(ctx, 0x4BED64u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x120);
            call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
            lwc1(f27, s4, 120);
            lwc1(f28, s4, 124);
            lwc1(f26, s4, 104);
            lwc1(f29, s4, 108);
            s2 = v0;
            if (s4 != 0) {
                // 0x004bed84
                charge(ctx, 18);
                lw(v0, s4, 24);
                sw(v0, s5, 24);
                lw(v0, s4, 28);
                sw(v0, s5, 28);
                lwc1(f12, s4, 128);
                a0 = s5;
                jal(ctx, 0x4BED98u, gen::fn_sub_4C9D70_004c9d70);
                lwc1(f12, s4, 132);
                a0 = s5;
                jal(ctx, 0x4BEDA4u, gen::fn_sub_4C9DB0_004c9db0);
                lq(a1, sp, 0xE0);
                a0 = s5;
                jal(ctx, 0x4BEDB0u, gen::fn_sub_4C9F00_004c9f00);
                lw(v1, s7, 12);
                lw(v0, sp, 0x14C);
                v0 = slt(v1, v0);
                lw(a0, s7, 16);
                if (v0 == 0) {
                    // 0x004bedcc
                    charge(ctx, 4);
                    lw(v0, sp, 0x148);
                    v0 = slt(a0, v0);
                    if (v0 != 0) {
                        goto L_004bee60;
                    }
                    // 0x004beddc
                    charge(ctx, 14);
                    lw(v0, sp, 0x14C);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    sw(zero, sp, 0x190);
                    sw(zero, sp, 0x194);
                    sw(v0, sp, 0x198);
                    lw(v0, sp, 0x148);
                    link(ctx, 0x4BEE00u);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x19C);
                    call(ctx, gen::fn_sub_4CE0F0_004ce0f0);
                    s3 = v0;
                    if (s3 == 0) {
                        // 0x004bee68
                        charge(ctx, 2);
                        s4 = 0;
                        backedge(ctx);
                    } else {
                        // 0x004bee14
                        charge(ctx, 5);
                        a1 = s7;
                        a0 = s3;
                        a2 = addiu(sp, 0x190);
                        jal(ctx, 0x4BEE1Cu, gen::fn_sub_4CE050_004ce050);
                        sw(s3, s5, 96);
                    }
                    // 0x004bee28
                    charge(ctx, 7);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x4BEE34u, gen::fn_sub_4CE0F0_004ce0f0);
                    sw(v0, sp, 0x11C);
                    if (s3 == 0) {
                        // 0x004bee70
                        charge(ctx, 1);
                        s4 = 0;
                    } else {
                        // 0x004bee44
                        charge(ctx, 7);
                        lw(a1, sp, 0x120);
                        a0 = v0;
                        a2 = addiu(sp, 0x190);
                        jal(ctx, 0x4BEE4Cu, gen::fn_sub_4CE050_004ce050);
                        lw(v0, sp, 0x11C);
                        sw(v0, s5, 100);
                    }
                    goto L_004bee74;
                }
            L_004bee60:
                charge(ctx, 2);
                s4 = 0;
            }
        L_004bee74:
            charge(ctx, 2);
            if (s4 != 0) {
                // 0x004bee7c
                charge(ctx, 7);
                lw(a0, sp, 0x14C);
                lw(a1, sp, 0x148);
                a2 = 32;
                jal(ctx, 0x4BEE84u, gen::fn_sub_4CBE00_004cbe00);
                fp = v0;
                if (fp == 0) {
                    // 0x004beeb0
                    charge(ctx, 1);
                    s4 = 0;
                } else {
                    // 0x004bee98
                    charge(ctx, 4);
                    a0 = fp;
                    jal(ctx, 0x4BEE98u, gen::fn_sub_4CBF20_004cbf20);
                    if (v0 == 0) {
                        // 0x004beea8
                        charge(ctx, 2);
                        s4 = 0;
                    }
                }
            }
            // 0x004beeb4
            charge(ctx, 2);
            if (s4 != 0) {
                // 0x004beebc
                charge(ctx, 4);
                jal(ctx, 0x4BEEBCu, gen::fn_sub_4CAF10_004caf10);
                sw(v0, sp, 0x110);
                if (v0 == 0) {
                    // 0x004bef14
                    charge(ctx, 1);
                    s4 = 0;
                } else {
                    // 0x004beecc
                    charge(ctx, 3);
                    a1 = addiu(v0, 16);
                    a0 = 8;
                    a2 = s2;
                    for (;;) {
                        // 0x004beed8
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
                    // 0x004beef8
                    charge(ctx, 7);
                    lw(v0, sp, 0x110);
                    a0 = s5;
                    s1 = addiu(v0, 16);
                    a1 = v0;
                    jal(ctx, 0x4BEF04u, gen::fn_sub_4D1840_004d1840);
                }
            }
            // 0x004bef18
            charge(ctx, 2);
            if (s4 != 0) {
                // 0x004bef20
                charge(ctx, 26);
                lw(v0, sp, 0x14C);
                v1 = 2;
                div(s0, v0);
                lw(v0, sp, 0x148);
                mflo(s7);
                mtc1(s7, f1);
                cvt_s_w(f1, f1);
                div1(s6, v0);
                mflo1(v0);
                sq(v0, sp, 0xD0);
                v0 = 0x3F800000;
                mtc1(v0, f2);
                lq(v0, sp, 0xD0);
                div_s(f4, f2, f1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f3, f2, f0);
                lw(v0, sp, 0x1B0);
                if (v0 != v1) {
                    // 0x004bf004
                    charge(ctx, 3);
                    at = slt(s6, s0);
                    if (at == 0) {
                        // 0x004bf05c
                        charge(ctx, 17);
                        div_s(f2, f26, f1);
                        v0 = addiu(sp, 0x1AC);
                        sw(v0, sp, 0xF0);
                        lw(v0, sp, 0x148);
                        mtc1(v0, f1);
                        swc1(f2, sp, 0x1A8);
                        lw(v0, sp, 0x14C);
                        cvt_s_w(f1, f1);
                        mtc1(v0, f0);
                        mul_s(f1, f2, f1);
                        lw(v0, sp, 0xF0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, v0, 0);
                    } else {
                        // 0x004bf010
                        charge(ctx, 19);
                        div_s(f2, f29, f0);
                        v0 = addiu(sp, 0x1AC);
                        sw(v0, sp, 0xF0);
                        swc1(f2, v0, 0);
                        lw(v0, sp, 0x14C);
                        mtc1(v0, f1);
                        lw(v0, sp, 0x148);
                        cvt_s_w(f1, f1);
                        mtc1(v0, f0);
                        mul_s(f1, f2, f1);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, sp, 0x1A8);
                    }
                } else {
                    // 0x004bef88
                    charge(ctx, 3);
                    v0 = slt(s0, s6);
                    if (v0 != 0) {
                        // 0x004bef9c
                        charge(ctx, 7);
                        mtc1(s0, f1);
                        mtc1(s6, f0);
                        cvt_s_w(f1, f1);
                        cvt_s_w(f0, f0);
                        div_s(f2, f1, f0);
                        at = slt(s6, s0);
                    } else {
                        // 0x004bef94
                        charge(ctx, 2);
                        at = slt(s6, s0);
                    }
                    // 0x004befb8
                    charge(ctx, 2);
                    if (at != 0) {
                        // 0x004befd0
                        charge(ctx, 7);
                        mtc1(s6, f1);
                        mtc1(s0, f0);
                        cvt_s_w(f1, f1);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        mul_s(f1, f2, f4);
                    } else {
                        // 0x004befc0
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        mul_s(f1, f2, f4);
                    }
                    // 0x004befec
                    charge(ctx, 6);
                    v0 = addiu(sp, 0x1AC);
                    sw(v0, sp, 0xF0);
                    mul_s(f0, f0, f3);
                    swc1(f1, sp, 0x1A8);
                    swc1(f0, v0, 0);
                }
                // 0x004bf0a0
                charge(ctx, 14);
                mtc1(s6, f1);
                mtc1(s0, f0);
                cvt_s_w(f2, f1);
                cvt_s_w(f1, f0);
                div_s(f3, f29, f26);
                div_s(f0, f2, f1);
                c_le_s(f3, f0);
                if (cond(ctx)) {
                    // 0x004bf0fc
                    charge(ctx, 9);
                    div_s(f0, f3, f0);
                    sw(s0, sp, 0x178);
                    mul_s(f0, f2, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sw(v0, sp, 0x17C);
                } else {
                    // 0x004bf0d8
                    charge(ctx, 9);
                    div_s(f0, f0, f3);
                    sw(s6, sp, 0x17C);
                    mul_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sw(v0, sp, 0x178);
                }
                // 0x004bf120
                charge(ctx, 17);
                a0 = s5;
                a1 = addiu(sp, 0x1A8);
                jal(ctx, 0x4BF124u, gen::fn_sub_4C9F90_004c9f90);
                lw(v0, sp, 0xF0);
                v1 = 0x4C0000;
                lwc1(f1, sp, 0x1A8);
                v1 = addiu(v1, -2720);  // &sub_4BF560
                lwc1(f25, v0, 0);
                v0 = 0x40000000;
                mtc1(v0, f2);
                lw(v0, sp, 0xF0);
                mul_s(f0, f25, f2);
                mul_s(f1, f1, f2);
                swc1(f0, v0, 0);
                lw(v0, sp, 0x13C);
                swc1(f1, sp, 0x1A8);
                if (v0 == v1) {
                    // 0x004bf488
                    charge(ctx, 3);
                    lw(v0, sp, 0x138);
                    if (v0 == 0) {
                        backedge(ctx);
                        goto L_004bf164;
                    }
                    // 0x004bf494
                    charge(ctx, 10);
                    lw(a3, sp, 0x14C);
                    a1 = s0;
                    lw(t0, sp, 0x148);
                    a2 = s6;
                    a0 = addiu(sp, 0x150);
                    t1 = v0;
                    jal(ctx, 0x4BF4A8u, gen::fn_sub_4BE930_004be930);
                    v0 = addiu(sp, 0x150);
                    sw(v0, sp, 0x100);
                    backedge(ctx);
                    goto L_004bf16c;
                }
            L_004bf164:
                charge(ctx, 2);
                lw(v0, sp, 0x138);
                sw(v0, sp, 0x100);
            L_004bf16c:
                charge(ctx, 12);
                v0 = 0x3F000000;
                s6 = 0;
                mtc1(v0, f2);
                mtc1(zero, f0);
                lw(v0, sp, 0xF0);
                adda_s(f0, f29);
                lwc1(f1, v0, 0);
                lq(v0, sp, 0xD0);
                msub_s(f0, f2, f1);
                at = slt(0, v0);
                neg_s(f23, f0);
                if (at != 0) {
                    for (;;) {
                        // 0x004bf19c
                        charge(ctx, 9);
                        lwc1(f0, sp, 0x1A8);
                        v0 = 0x3F000000;
                        mtc1(v0, f1);
                        at = slt(0, s7);
                        mov_s(f30, f26);
                        s0 = 0;
                        mul_s(f24, f1, f0);
                        sub_s(f22, f26, f24);
                        if (at != 0) {
                            // 0x004bf1c0
                            charge(ctx, 2);
                            add_s(f20, f23, f28);
                            neg_s(f21, f23);
                            for (;;) {
                                // 0x004bf1c8
                                charge(ctx, 5);
                                mtc1(zero, f4);
                                c_le_s(f24, f4);
                                if (!cond(ctx)) {
                                    // 0x004bf1dc
                                    charge(ctx, 3);
                                    c_le_s(f25, f4);
                                    if (cond(ctx)) {
                                        goto L_004bf2b0;
                                    }
                                    // 0x004bf1e8
                                    charge(ctx, 37);
                                    lwc1(f0, s2, 48);
                                    a0 = s1;
                                    lwc1(f1, s2, 0);
                                    a1 = 0;
                                    lwc1(f3, s2, 4);
                                    lwc1(f2, s2, 8);
                                    adda_s(f4, f0);
                                    madd_s(f0, f1, f22);
                                    mul_s(f3, f3, f22);
                                    swc1(f0, s1, 48);
                                    lwc1(f0, s2, 52);
                                    mul_s(f2, f2, f22);
                                    add_s(f0, f3, f0);
                                    swc1(f0, s1, 52);
                                    lwc1(f0, s2, 56);
                                    add_s(f0, f2, f0);
                                    swc1(f0, s1, 56);
                                    lwc1(f0, s1, 48);
                                    lwc1(f3, s2, 20);
                                    lwc1(f2, s2, 24);
                                    lwc1(f1, s2, 16);
                                    adda_s(f4, f0);
                                    mul_s(f3, f3, f21);
                                    madd_s(f0, f1, f21);
                                    swc1(f0, s1, 48);
                                    lwc1(f0, s1, 52);
                                    mul_s(f2, f2, f21);
                                    add_s(f0, f0, f3);
                                    swc1(f0, s1, 52);
                                    lwc1(f0, s1, 56);
                                    add_s(f0, f0, f2);
                                    link(ctx, 0x4BF264u);  // $ra first: the delay slot below depends on it
                                    swc1(f0, s1, 56);
                                    call(ctx, gen::fn_sub_4C2D20_004c2d20);
                                    lq(v0, sp, 0xE0);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x004bf4bc
                                        charge(ctx, 9);
                                        add_s(f0, f22, f27);
                                        v0 = addiu(sp, 0x1A4);
                                        a0 = s5;
                                        a1 = addiu(sp, 0x1A0);
                                        swc1(f20, v0, 0);
                                        link(ctx, 0x4BF4D0u);  // $ra first: the delay slot below depends on it
                                        swc1(f0, sp, 0x1A0);
                                        call(ctx, gen::fn_sub_4C9D20_004c9d20);
                                        backedge(ctx);
                                    } else {
                                        // 0x004bf27c
                                        charge(ctx, 1);
                                    }
                                    // 0x004bf280
                                    charge(ctx, 10);
                                    link(ctx, 0x4BF280u);  // $ra first: the delay slot below depends on it
                                    lw(a0, sp, 0x110);
                                    call(ctx, gen::fn_sub_4CB270_004cb270);
                                    lw(a3, sp, 0x138);
                                    a0 = s5;
                                    lw(v0, sp, 0x140);
                                    a1 = s0;
                                    a2 = s6;
                                    jalr(ctx, 0x4BF298u, v0.u());
                                    if (v0 != s5) {
                                        // 0x004bf2a8
                                        charge(ctx, 2);
                                        s4 = 0;
                                    }
                                    goto L_004bf2b8;
                                }
                            L_004bf2b0:
                                charge(ctx, 2);
                                s0 = s7;
                            L_004bf2b8:
                                charge(ctx, 2);
                                if (s4 != 0) {
                                    // 0x004bf2c0
                                    charge(ctx, 2);
                                    lw(v1, fp, 0x14);
                                    if (s3 != 0) {
                                        // 0x004bf2c8
                                        charge(ctx, 9);
                                        lw(v0, s3, 4);
                                        a0 = s3;
                                        a1 = 0;
                                        a2 = 2;
                                        sw(v0, gp, -17464);  // 0x7CE8B8
                                        link(ctx, 0x4BF2DCu);  // $ra first: the delay slot below depends on it
                                        sw(v1, s3, 4);
                                        call(ctx, gen::fn_sub_4CE200_004ce200);
                                        if (v0 == 0) {
                                            // 0x004bf2ec
                                            charge(ctx, 3);
                                            lw(v0, gp, -17464);  // 0x7CE8B8
                                            sw(v0, s3, 4);
                                        }
                                    }
                                    // 0x004bf2f8
                                    charge(ctx, 12);
                                    a0 = s3;
                                    jal(ctx, 0x4BF2F8u, gen::fn_sub_4CDE00_004cde00);
                                    lw(v0, gp, -17464);  // 0x7CE8B8
                                    a0 = fp;
                                    lw(a3, sp, 0x100);
                                    a1 = s0;
                                    sw(v0, s3, 4);
                                    lw(v0, sp, 0x13C);
                                    a2 = s6;
                                    jalr(ctx, 0x4BF318u, v0.u());
                                    if (v0 == 0) {
                                        // 0x004bf328
                                        charge(ctx, 2);
                                        s4 = 0;
                                    }
                                }
                                // 0x004bf330
                                charge(ctx, 2);
                                if (s4 != 0) {
                                    // 0x004bf338
                                    charge(ctx, 8);
                                    lwc1(f1, sp, 0x1A8);
                                    v0 = 0x3F000000;
                                    mtc1(v0, f0);
                                    v1 = 1;
                                    lw(v0, sp, 0x1B0);
                                    mul_s(f0, f0, f1);
                                    sub_s(f30, f30, f0);
                                    if (v0 == v1) {
                                        // 0x004bf358
                                        charge(ctx, 3);
                                        c_le_s(f30, f0);
                                        if (cond(ctx)) {
                                            // 0x004bf370
                                            charge(ctx, 2);
                                            mov_s(f24, f30);
                                        } else {
                                            // 0x004bf364
                                            charge(ctx, 2);
                                            mov_s(f24, f0);
                                        }
                                    }
                                    // 0x004bf378
                                    charge(ctx, 4);
                                    s0 = addiu(s0, 1);
                                    v0 = slt(s0, s7);
                                    sub_s(f22, f22, f1);
                                    if (v0 != 0) {
                                        backedge(ctx);
                                        continue;
                                    }
                                }
                                break;
                            }
                        }
                        // 0x004bf388
                        charge(ctx, 2);
                        if (s4 == 0) {
                            goto L_004bf3f0;
                        }
                        // 0x004bf390
                        charge(ctx, 10);
                        lw(v0, sp, 0xF0);
                        v1 = 1;
                        lwc1(f1, v0, 0);
                        v0 = 0x3F000000;
                        mtc1(v0, f0);
                        mul_s(f0, f0, f1);
                        lw(v0, sp, 0x1B0);
                        sub_s(f29, f29, f0);
                        if (v0 == v1) {
                            // 0x004bf3b8
                            charge(ctx, 3);
                            c_le_s(f29, f0);
                            if (cond(ctx)) {
                                // 0x004bf3d0
                                charge(ctx, 2);
                                mov_s(f25, f29);
                            } else {
                                // 0x004bf3c4
                                charge(ctx, 2);
                                mov_s(f25, f0);
                            }
                        }
                        // 0x004bf3d8
                        charge(ctx, 5);
                        lq(v0, sp, 0xD0);
                        s6 = addiu(s6, 1);
                        v0 = slt(s6, v0);
                        add_s(f23, f23, f1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004bf3ec
                    charge(ctx, 1);
                }
            }
        L_004bf3f0:
            charge(ctx, 3);
            lw(v0, sp, 0x110);
            if (v0 != 0) {
                // 0x004bf3fc
                charge(ctx, 2);
                a0 = v0;
                jal(ctx, 0x4BF3FCu, gen::fn_sub_4CAF80_004caf80);
            }
            // 0x004bf404
            charge(ctx, 2);
            if (fp != 0) {
                // 0x004bf40c
                charge(ctx, 2);
                a0 = fp;
                jal(ctx, 0x4BF40Cu, gen::fn_sub_4CBEB0_004cbeb0);
            }
            // 0x004bf414
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x004bf41c
                charge(ctx, 2);
                a0 = s3;
                jal(ctx, 0x4BF41Cu, gen::fn_sub_4CDE90_004cde90);
            }
            // 0x004bf424
            charge(ctx, 3);
            lw(v0, sp, 0x11C);
            if (v0 != 0) {
                // 0x004bf430
                charge(ctx, 2);
                a0 = v0;
                jal(ctx, 0x4BF430u, gen::fn_sub_4CDE90_004cde90);
            }
            // 0x004bf438
            charge(ctx, 2);
            if (s5 != 0) {
                // 0x004bf440
                charge(ctx, 2);
                a0 = s5;
                jal(ctx, 0x4BF440u, gen::fn_sub_4CA030_004ca030);
            }
            // 0x004bf448
            charge(ctx, 4);
            v0 = addiu(sp, 0x158);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x004bf458
                charge(ctx, 2);
                a1 = 0;
                jal(ctx, 0x4BF458u, gen::fn_sub_4C5780_004c5780);
            }
            // 0x004bf460
            charge(ctx, 4);
            v0 = addiu(sp, 0x180);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x004bf470
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x4BF478u, v0.u());
            }
            // 0x004bf480
            charge(ctx, 2);
            v0 = s4;
            // 0x004bf4e0 (the shared epilogue, written out on this path)
            charge(ctx, 23);
            ld(ra, sp, 0xC0);
            lq(fp, sp, 0xB0);
            lwc1(f30, sp, 0x28);
            lq(s7, sp, 0xA0);
            lwc1(f29, sp, 0x24);
            lq(s6, sp, 0x90);
            lwc1(f28, sp, 0x20);
            lq(s5, sp, 0x80);
            lwc1(f27, sp, 0x1C);
            lq(s4, sp, 0x70);
            lwc1(f26, sp, 0x18);
            lq(s3, sp, 0x60);
            lwc1(f25, sp, 0x14);
            lq(s2, sp, 0x50);
            lwc1(f24, sp, 0x10);
            lq(s1, sp, 0x40);
            lwc1(f23, sp, 0xC);
            lq(s0, sp, 0x30);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x1B0);
            return;
        }
    L_004becf8:
        charge(ctx, 2);
        v0 = 0;
        // 0x004bf4e0 (the shared epilogue, written out on this path)
        charge(ctx, 23);
        ld(ra, sp, 0xC0);
        lq(fp, sp, 0xB0);
        lwc1(f30, sp, 0x28);
        lq(s7, sp, 0xA0);
        lwc1(f29, sp, 0x24);
        lq(s6, sp, 0x90);
        lwc1(f28, sp, 0x20);
        lq(s5, sp, 0x80);
        lwc1(f27, sp, 0x1C);
        lq(s4, sp, 0x70);
        lwc1(f26, sp, 0x18);
        lq(s3, sp, 0x60);
        lwc1(f25, sp, 0x14);
        lq(s2, sp, 0x50);
        lwc1(f24, sp, 0x10);
        lq(s1, sp, 0x40);
        lwc1(f23, sp, 0xC);
        lq(s0, sp, 0x30);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x1B0);
        return;
    }
L_004bed00:
    charge(ctx, 2);
    v0 = 0;
    // 0x004bf4e0 (the shared epilogue, written out on this path)
    charge(ctx, 23);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lwc1(f30, sp, 0x28);
    lq(s7, sp, 0xA0);
    lwc1(f29, sp, 0x24);
    lq(s6, sp, 0x90);
    lwc1(f28, sp, 0x20);
    lq(s5, sp, 0x80);
    lwc1(f27, sp, 0x1C);
    lq(s4, sp, 0x70);
    lwc1(f26, sp, 0x18);
    lq(s3, sp, 0x60);
    lwc1(f25, sp, 0x14);
    lq(s2, sp, 0x50);
    lwc1(f24, sp, 0x10);
    lq(s1, sp, 0x40);
    lwc1(f23, sp, 0xC);
    lq(s0, sp, 0x30);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1B0);
}

// sub_4BF540 [rtTileRenderThunk] -- a tail call into RtTileRender (sub_4BEC20) with the caller's arguments
// 0x004BF540 sub_4BF540 -- 32 bytes; frame 0x20: ra sp+0x10
void sub_4BF540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bf540
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(ra, sp, 0x10);
    link(ctx, 0x4BF54Cu);  // $ra first: the delay slot below depends on it
    sd(v0, sp, 0x0);
    call(ctx, gen::fn_sub_4BEC20_004bec20);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// sub_4BF560 [rtTileArchiveBmpCB] -- RtTileRender's built-in archive callback: the tile's 32-bit pixels copied as BGR
//   into the band buffer of the BMP writer's state ($a3) at the tile's column (clipped to the image size), and after the
//   last column of a row the band written (sub_4C53F0) and cleared; the image
// 0x004BF560 sub_4BF560 -- 372 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BF560(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bf560
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (a3 != 0) {
        // 0x004bf578
        charge(ctx, 4);
        lw(v0, a3, 28);
        at = slt(a1, v0);
        s1 = a3;
        if (at != 0) {
            // 0x004bf588
            charge(ctx, 16);
            lw(t3, s1, 24);
            mult(a2, a2, t3);
            lw(v1, s1, 20);
            lw(a0, s0, 20);
            lw(v0, s0, 16);
            lw(t2, s1, 48);
            mult1(t0, a1, v1);
            lw(t1, s1, 12);
            v1 = sll(t0, 1);
            at = slt(0, t3);
            v1 = addu(v1, t0);
            a3 = 0;
            v1 = addu(t2, v1);
            t0 = sll(t1, 1);
            t2 = addu(t0, t1);
            if (at != 0) {
                // 0x004bf5c8
                charge(ctx, 1);
                t1 = 1;
                for (;;) {
                    // 0x004bf5cc
                    charge(ctx, 7);
                    lw(t0, s1, 20);
                    mult(t5, a1, t0);
                    at = slt(0, t0);
                    t3 = a0;
                    t4 = v1;
                    t6 = 0;
                    if (at != 0) {
                        for (;;) {
                            // 0x004bf5e8
                            charge(ctx, 10);
                            lbu(t0, t3, 2);
                            sb(t0, t4, 0);
                            lbu(t0, t3, 1);
                            sb(t0, t4, 1);
                            lbu(t0, t3, 0);
                            sb(t0, t4, 2);
                            t3 = addiu(t3, 4);
                            lw(t0, s1, 0);
                            t4 = addiu(t4, 3);
                            if (t0 == t1) {
                                // 0x004bf610
                                charge(ctx, 4);
                                lw(t0, s1, 40);
                                at = slt(t0, t5);
                                if (at != 0) {
                                    goto L_004bf6a4;
                                }
                                goto L_004bf620;
                            }
                        L_004bf620:
                            charge(ctx, 5);
                            lw(t0, s1, 20);
                            t6 = addiu(t6, 1);
                            t0 = slt(t6, t0);
                            t5 = addiu(t5, 1);
                            if (t0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004bf634
                        charge(ctx, 2);
                        lw(t0, s1, 0);
                        goto L_004bf6a8;
                    }
                L_004bf6a4:
                    charge(ctx, 1);
                    lw(t0, s1, 0);
                L_004bf6a8:
                    charge(ctx, 3);
                    v1 = addu(v1, t2);
                    a0 = addu(a0, v0);
                    if (t0 != t1) {
                        backedge(ctx);
                    } else {
                        // 0x004bf6b4
                        charge(ctx, 2);
                        backedge(ctx);
                        // 0x004bf640
                        charge(ctx, 4);
                        lw(t0, s1, 44);
                        at = slt(t0, a2);
                        if (at != 0) {
                            goto L_004bf668;
                        }
                        goto L_004bf650;
                    }
                L_004bf650:
                    charge(ctx, 5);
                    lw(t0, s1, 24);
                    a3 = addiu(a3, 1);
                    t0 = slt(a3, t0);
                    a2 = addiu(a2, 1);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004bf664
                charge(ctx, 1);
            }
        }
    L_004bf668:
        charge(ctx, 5);
        lw(v0, s1, 28);
        v0 = addiu(v0, -1);
        v0 = slt(a1, v0);
        if (v0 == 0) {
            // 0x004bf67c
            charge(ctx, 8);
            lw(a0, s1, 8);
            lw(a1, s1, 48);
            link(ctx, 0x4BF684u);  // $ra first: the delay slot below depends on it
            lw(a2, s1, 36);
            call(ctx, gen::fn_sub_4C53F0_004c53f0);
            lw(a2, s1, 36);
            lw(a0, s1, 48);
            a1 = 0;
            jal(ctx, 0x4BF694u, gen::fn_memset_00521408);
        }
    }
    // 0x004bf69c
    charge(ctx, 2);
    v0 = s0;
    // 0x004bf6c0
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4BF880 [rtfsBuildPath] -- builds a device path: the prefix $a2 then the path $a3 with every '/' and '\' replaced
//   by the separator $t0 (strcpy slot), when it fits in $a1 bytes; the buffer, or 0
// 0x004BF880 sub_4BF880 -- 256 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BF880(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bf880
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    s2 = t0;
    a0 = s4;
    link(ctx, 0x4BF8B8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_strlen_00524388);
    s1 = v0;
    a0 = s3;
    jal(ctx, 0x4BF8C4u, gen::fn_strlen_00524388);
    s0 = v0;
    v0 = addiu(s6, -1);
    v1 = addu(s1, s0);
    at = slt(v0, v1);
    if (at == 0) {
        // 0x004bf8ec
        charge(ctx, 8);
        v0 = 0x960000;
        a1 = s4;
        lw(v0, v0, 316);  // 0x96013C
        a0 = s5;
        jalr(ctx, 0x4BF8F8u, v0.u());
        at = slt(s0, 0);
        a2 = 0;
        if (at == 0) {
            // 0x004bf90c
            charge(ctx, 3);
            a1 = addu(s5, s1);
            v0 = 92;
            v1 = 47;
            for (;;) {
                // 0x004bf918
                charge(ctx, 4);
                a0 = addu(s3, a2);
                lb(a0, a0, 0);
                if (a0 != v1) {
                    // 0x004bf928
                    charge(ctx, 2);
                    if (a0 == v0) {
                        goto L_004bf950;
                    }
                    // 0x004bf930
                    charge(ctx, 2);
                    sb(a0, a1, 0);
                    goto L_004bf938;
                }
            L_004bf950:
                charge(ctx, 2);
                sb(s2, a1, 0);
                backedge(ctx);
            L_004bf938:
                charge(ctx, 4);
                a2 = addiu(a2, 1);
                at = slt(s0, a2);
                a1 = addiu(a1, 1);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004bf948
        charge(ctx, 2);
        v0 = s5;
    } else {
        // 0x004bf8e4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004bf958 (the shared epilogue, written out on this path)
    charge(ctx, 10);
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

// sub_4BF980 [rtfsFileExists] -- tests whether a file exists on a file system: opened for reading (sub_4BFEA0) and,
//   when it opened, closed through the file's close callback (+44); 1, or 0
// 0x004BF980 sub_4BF980 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4BF980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bf980
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 1;
    sd(ra, sp, 0x10);
    a3 = 0;
    sq(s0, sp, 0x0);
    t0 = 0;
    s0 = a0;
    jal(ctx, 0x4BF998u, gen::fn_sub_4BFEA0_004bfea0);
    if (v0 == 0) {
        // 0x004bf9c0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004bf9a8
        charge(ctx, 6);
        a0 = v0;
        lw(v0, s0, 44);
        jalr(ctx, 0x4BF9B0u, v0.u());
        v0 = 1;
    }
    // 0x004bf9c4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C0550 [RwFgets] -- reads a line from an RtFS file into $a0 (at most $a1 - 1 bytes): the file's read callback,
//   the line cut after the first '\n' ('\r\n' collapsed), the bytes read past it given back through the seek callback;
//   $a0, or 0 at the end
// 0x004C0550 sub_4C0550 -- 340 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C0550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0550
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    a2 = addiu(a1, -1);
    lw(v0, s2, 80);
    a0 = s2;
    a1 = s3;
    lw(v0, v0, 48);
    s1 = 0;
    jalr(ctx, 0x4C0584u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004c0648
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c0598
        charge(ctx, 2);
        if (i64(s0) > 0) {
            for (;;) {
                // 0x004c05a0
                charge(ctx, 5);
                a0 = addu(s3, s1);
                v1 = 10;
                lb(a1, a0, 0);
                if (a1 == v1) {
                    break;
                }
                // 0x004c05f8
                charge(ctx, 3);
                v0 = 13;
                if (a1 != v0) {
                    // 0x004c0620
                    charge(ctx, 2);
                    s1 = addiu(s1, 1);
                } else {
                    // 0x004c0604
                    charge(ctx, 4);
                    v0 = addiu(s0, -1);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        // 0x004c0614
                        charge(ctx, 1);
                        goto L_004c0618;
                    }
                    // 0x004c0664
                    charge(ctx, 3);
                    lb(v0, a0, 1);
                    a1 = addiu(a0, 1);
                    if (v0 != v1) {
                        backedge(ctx);
                    L_004c0618:
                        charge(ctx, 2);
                        s1 = addiu(s1, 1);
                    } else {
                        // 0x004c0670
                        charge(ctx, 5);
                        v0 = subu(s0, s1);
                        a2 = addiu(v0, -1);
                        jal(ctx, 0x4C0674u, gen::fn_memcpy_00521250);
                        s0 = addiu(s0, -1);
                        backedge(ctx);
                    }
                }
                // 0x004c0628
                charge(ctx, 3);
                at = slt(s1, s0);
                if (at == 0) {
                    goto L_004c0634_11;
                }
                backedge(ctx);
            }
            // 0x004c05b4
            charge(ctx, 8);
            v0 = addiu(s1, 1);
            a1 = subu(v0, s0);
            v0 = addu(s3, v0);
            sb(zero, v0, 0);
            lw(v1, s2, 80);
            lw(v0, s2, 48);
            a0 = addiu(v1, 40);
            if (v0 != 0) {
                // 0x004c0650
                charge(ctx, 5);
                v1 = 4;
                v0 = 3;
                sw(v1, s2, 64);
                sw(v0, s2, 56);
                backedge(ctx);
            }
            // 0x004c05d4
            charge(ctx, 9);
            lw(v0, a0, 16);
            a2 = dsll32(a1, 0);
            a2 = dsra32(a2, 0);
            a1 = s2;
            a3 = 2;
            a0 = addiu(sp, 0x50);
            jalr(ctx, 0x4C05E8u, v0.u());
            v0 = s3;
            // 0x004c0688 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004c0638:
        charge(ctx, 4);
        v0 = addu(s3, s0);
        sb(zero, v0, 0);
        v0 = s3;
    }
    // 0x004c0688 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c0634_11:
    charge(ctx, 1);
    goto L_004c0638;
}

// sub_4C0F70 [sceFsFileStatus] -- the sce file system device's status callback: unless the file record is idle (state
//   +56 == 1) its pending request is polled once without waiting (sub_4C0E70, $a1 = 0); the record's state
// 0x004C0F70 sub_4C0F70 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C0F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0f70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 56);
    s0 = a0;
    if (v1 != v0) {
        // 0x004c0f94
        charge(ctx, 4);
        a1 = 0;
        jal(ctx, 0x4C0F94u, gen::fn_sub_4C0E70_004c0e70);
        backedge(ctx);
    }
    // 0x004c0f8c
    charge(ctx, 2);
    lw(v0, s0, 56);
    // 0x004c0fa4
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C0FC0 [rtfsFileExistsThunk] -- a tail call into sub_4BF980
// 0x004C0FC0 sub_4C0FC0 -- 8 bytes; leaf frame (no stack)
void sub_4C0FC0(EEContext& ctx) {
    using namespace hg;
    // 0x004c0fc0
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_4BF980_004bf980(ctx);  // tail call
}

// sub_4C7460 [rwStringStreamWrite] -- writes a string chunk: the header (type 2, the padded size, version 0x37002), the
//   string's bytes padded to 4 (sub_4C53F0); the string, or 0
// 0x004C7460 sub_4C7460 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C7460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c7460
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x004c74d0
        charge(ctx, 3);
        s1 = 0x7C0000;
        s1 = addiu(s1, -13336);  // &0x7BCBE8
        backedge(ctx);
    }
    // 0x004c7480
    charge(ctx, 2);
    a0 = s1;
    if (s1 == 0) {
        // 0x004c74dc
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, -13336);  // &0x7BCBE8
        backedge(ctx);
    }
    // 0x004c7488
    charge(ctx, 16);
    v0 = 0x960000;
    lw(v0, v0, 356);  // 0x960164
    jalr(ctx, 0x4C7490u, v0.u());
    v1 = addiu(v0, 4);
    a0 = s0;
    v0 = si(-4);
    a1 = 2;
    s2 = v1 & v0;
    t0 = 55;
    v0 = 0x30000;
    a2 = s2;
    a3 = v0 | 0x7002;
    jal(ctx, 0x4C74B8u, gen::fn_sub_4C15A0_004c15a0);
    if (v0 != 0) {
        // 0x004c74e8
        charge(ctx, 6);
        a0 = s0;
        a2 = s2;
        a1 = s1;
        jal(ctx, 0x4C74F0u, gen::fn_sub_4C53F0_004c53f0);
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x004c74c8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c7500 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C76C0 [rwStringStreamReadUnicode] -- reads a unicode string chunk's body of $a2 bytes in 128-byte pieces,
//   keeping the low byte of each 16-bit character, into $a0 (allocated when 0, freed again on a short read); the string,
//   or 0
// 0x004C76C0 sub_4C76C0 -- 476 bytes; frame 0x130: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C76C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c76c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s0 = 0;
    if (s4 == 0) {
        // 0x004c77f0
        charge(ctx, 9);
        v0 = 0x30000;
        a1 = v0 | 0x2;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = s2;
        jalr(ctx, 0x4C7800u, v0.u());
        s4 = v0;
        if (s4 != 0) {
            // 0x004c7814
            charge(ctx, 2);
            s0 = 1;
            backedge(ctx);
            goto L_004c76f4;
        }
        // 0x004c781c
        charge(ctx, 11);
        v0 = 1;
        a1 = s2;
        sw(v0, sp, 0x128);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4C782Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x12C);
        a0 = addiu(sp, 0x128);
        jal(ctx, 0x4C7838u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004c7878 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x130);
        return;
    }
L_004c76f4:
    charge(ctx, 2);
    s1 = s4;
    if (s2 != 0) {
        for (;;) {
            // 0x004c76fc
            charge(ctx, 3);
            at = sltiu(s2, 129);
            if (at == 0) {
                // 0x004c7848
                charge(ctx, 2);
                s5 = 128;
                backedge(ctx);
            } else {
                // 0x004c7708
                charge(ctx, 2);
                s5 = s2;
            }
            // 0x004c7710
            charge(ctx, 6);
            a0 = s3;
            a1 = addiu(sp, 0x70);
            a2 = s5;
            jal(ctx, 0x4C7718u, gen::fn_sub_4C5250_004c5250);
            if (s5 != v0) {
                break;
            }
            // 0x004c7728
            charge(ctx, 5);
            a3 = srl(s5, 1);
            s2 = subu(s2, s5);
            at = sltu(0, a3);
            v0 = 0;
            if (at != 0) {
                // 0x004c773c
                charge(ctx, 3);
                at = sltiu(a3, 9);
                a2 = addiu(a3, -8);
                if (at == 0) {
                    // 0x004c7748
                    charge(ctx, 2);
                    t0 = addiu(sp, 0x70);
                    for (;;) {
                        // 0x004c7750
                        charge(ctx, 21);
                        lhu(a0, t0, 0);
                        a1 = addu(s1, v0);
                        v0 = addiu(v0, 8);
                        v1 = sltu(v0, a2);
                        sb(a0, a1, 0);
                        lhu(a0, t0, 2);
                        sb(a0, a1, 1);
                        lhu(a0, t0, 4);
                        sb(a0, a1, 2);
                        lhu(a0, t0, 6);
                        sb(a0, a1, 3);
                        lhu(a0, t0, 8);
                        sb(a0, a1, 4);
                        lhu(a0, t0, 10);
                        sb(a0, a1, 5);
                        lhu(a0, t0, 12);
                        sb(a0, a1, 6);
                        lhu(a0, t0, 14);
                        sb(a0, a1, 7);
                        t0 = addiu(t0, 16);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004c77a4
                    charge(ctx, 1);
                }
                // 0x004c77a8
                charge(ctx, 3);
                at = sltu(v0, a3);
                if (at != 0) {
                    // 0x004c77b4
                    charge(ctx, 3);
                    v1 = sll(v0, 1);
                    v1 = addu(v1, sp);
                    a2 = addiu(v1, 112);
                    for (;;) {
                        // 0x004c77c0
                        charge(ctx, 7);
                        lhu(a1, a2, 0);
                        a0 = addu(s1, v0);
                        v0 = addiu(v0, 1);
                        v1 = sltu(v0, a3);
                        sb(a1, a0, 0);
                        a2 = addiu(a2, 2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004c77dc
                    charge(ctx, 1);
                }
            }
            // 0x004c77e0
            charge(ctx, 2);
            s1 = addu(s1, a3);
            if (s2 == 0) {
                goto L_004c77e8;
            }
            backedge(ctx);
        }
        // 0x004c7850
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x004c7860
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            a0 = s4;
            jalr(ctx, 0x4C7868u, v0.u());
            backedge(ctx);
        }
        // 0x004c7858
        charge(ctx, 2);
        v0 = 0;
        // 0x004c7878 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x130);
        return;
    }
L_004c77e8:
    charge(ctx, 2);
    v0 = s4;
    // 0x004c7878 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// sub_4C7B90 [cameraStreamRead] -- reads a camera chunk: the struct (version 0x35000..0x37002, 32 bytes: view window,
//   view offset, near / far planes, fog plane, projection), a new camera (sub_4CA090) with its extensions (sub_4C5A50 on
//   0x77E5E0), then the view window (sub_4C9F90), view offset (sub_4C9D20), near (sub_4C9D70) and far planes
//   (sub_4C9DB0), the fog distance (+136) and the projection (sub_4C9F00); the camera, or 0
// 0x004C7B90 sub_4C7B90 -- 344 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C7B90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004c7b90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a1 = 1;
    sd(ra, sp, 0x20);
    a2 = addiu(sp, 0x5C);
    sq(s1, sp, 0x10);
    a3 = addiu(sp, 0x58);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C7BACu, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004c7c1c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c7bbc
        charge(ctx, 6);
        lw(v1, sp, 0x58);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004c7bd4
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004c7cb0;
            }
            // 0x004c7be8
            charge(ctx, 11);
            a0 = addiu(sp, 0x30);
            a1 = 0;
            a2 = 32;
            jal(ctx, 0x4C7BF0u, gen::fn_memset_00521408);
            lw(s1, sp, 0x5C);
            a0 = s0;
            a1 = addiu(sp, 0x30);
            a2 = s1;
            jal(ctx, 0x4C7C04u, gen::fn_sub_4C5250_004c5250);
            if (s1 == v0) {
                // 0x004c7c24
                charge(ctx, 5);
                jal(ctx, 0x4C7C24u, gen::fn_sub_4CA090_004ca090);
                s1 = v0;
                if (s1 == 0) {
                    // 0x004c7c5c
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004c7c38
                    charge(ctx, 7);
                    a0 = 0x780000;
                    a1 = s0;
                    a0 = addiu(a0, -6688);  // &0x77E5E0
                    a2 = s1;
                    jal(ctx, 0x4C7C44u, gen::fn_sub_4C5A50_004c5a50);
                    if (v0 != 0) {
                        // 0x004c7c64
                        charge(ctx, 19);
                        a0 = s1;
                        a1 = addiu(sp, 0x30);
                        jal(ctx, 0x4C7C68u, gen::fn_sub_4C9F90_004c9f90);
                        a0 = s1;
                        a1 = addiu(sp, 0x38);
                        jal(ctx, 0x4C7C74u, gen::fn_sub_4C9D20_004c9d20);
                        lwc1(f12, sp, 0x40);
                        a0 = s1;
                        jal(ctx, 0x4C7C80u, gen::fn_sub_4C9D70_004c9d70);
                        lwc1(f12, sp, 0x44);
                        a0 = s1;
                        jal(ctx, 0x4C7C8Cu, gen::fn_sub_4C9DB0_004c9db0);
                        lwc1(f0, sp, 0x48);
                        swc1(f0, s1, 136);
                        lw(a1, sp, 0x4C);
                        a0 = s1;
                        jal(ctx, 0x4C7CA0u, gen::fn_sub_4C9F00_004c9f00);
                        v0 = s1;
                    } else {
                        // 0x004c7c54
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
            } else {
                // 0x004c7c14
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x004c7cd4 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004c7cb0:
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x50);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C7CBCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x54);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x4C7CC8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004c7cd4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// RwEngineStart -- starts the engine: the device's start request (2, through _rwDeviceSystemRequest on the device block
//   0x960080); on success the engine plugin constructors run on the engine instance (sub_4C64B0 on the registry
//   0x77E630), the standard functions set up (sub_4CDB50), the device's request 17 made and the engine state set to
//   started (3) -- else the device stopped again (request 3); 1, or 0
// 0x004CA640 RwEngineStart -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void RwEngineStart(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004ca640
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 2;
    sd(ra, sp, 0x10);
    a2 = 0;
    sq(s0, sp, 0x0);
    a3 = 0;
    s0 = 0x960000;
    t0 = 0;
    s0 = addiu(s0, 128);  // &0x960080
    a0 = s0;
    jal(ctx, 0x4CA664u, gen::fn__rwDeviceSystemRequest_004ca3e0);
    if (v0 != 0) {
        // 0x004ca67c
        charge(ctx, 7);
        a0 = 0x780000;
        a1 = 0x960000;
        a0 = addiu(a0, -6608);  // &0x77E630
        a1 = addiu(a1, 112);  // &0x960070
        jal(ctx, 0x4CA688u, gen::fn_sub_4C64B0_004c64b0);
        if (v0 == 0) {
            // 0x004ca698
            charge(ctx, 8);
            a0 = s0;
            a1 = 3;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x4CA6A8u, gen::fn__rwDeviceSystemRequest_004ca3e0);
            backedge(ctx);
            goto L_004ca674;
        }
        // 0x004ca6b8
        charge(ctx, 12);
        link(ctx, 0x4CA6B8u);  // $ra first: the delay slot below depends on it
        lwc1(f12, s0, 0);
        call(ctx, gen::fn_sub_4CDB50_004cdb50);
        a0 = s0;
        a1 = 17;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x4CA6D0u, gen::fn__rwDeviceSystemRequest_004ca3e0);
        v1 = 3;
        v0 = 0x960000;
        sw(v1, v0, 404);  // 0x960194
        v0 = 1;
        // 0x004ca6e8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_004ca674:
    charge(ctx, 2);
    v0 = 0;
    // 0x004ca6e8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// RwEngineOpen -- opens the engine on a device: only in the initialised state (1; else error 0x80000001) and with a
//   parameter block (else error 0x80000016): the device block from sceLibgcc32GetErxEntries_2, its request 4 (the device
//   block 0x960080 and the memory functions 0x960178 copied), request 0 (open, $a0), then request 11 (the standard
//   functions into 0x9600B8, 29 of them) and the open count (gp 0x7CE908 + 32) up; the engine state opened (2); 1, or 0
// 0x004CA700 RwEngineOpen -- 336 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void RwEngineOpen(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca700
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 404);  // &0x960194
    lw(v0, s0, 0);  // 0x960194
    v0 = v0 ^ 0x1;
    s1 = sltiu(v0, 1);
    s2 = a0;
    if (s1 == 0) {
        // 0x004ca80c
        charge(ctx, 10);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x50);
        a0 = v0 | 0x1;
        jal(ctx, 0x4CA818u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x54);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x4CA824u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    } else {
        // 0x004ca734
        charge(ctx, 3);
        s1 = sltu(0, s2);
        if (s1 == 0) {
            // 0x004ca7e4
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x58);
            a0 = v0 | 0x16;
            jal(ctx, 0x4CA7F0u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x5C);
            a0 = addiu(sp, 0x58);
            jal(ctx, 0x4CA7FCu, gen::fn_sub_4C1C50_004c1c50);
            backedge(ctx);
        } else {
            // 0x004ca740
            charge(ctx, 6);
            jal(ctx, 0x4CA740u, gen::fn_sceLibgcc32GetErxEntries_2_004e2f00);
            s3 = v0;
            s1 = sltu(0, s3);
            if (s1 != 0) {
                // 0x004ca758
                charge(ctx, 16);
                a2 = 0x960000;
                a3 = 0x960000;
                a0 = s3;
                a1 = 4;
                a2 = addiu(a2, 128);  // &0x960080
                a3 = addiu(a3, 376);  // &0x960178
                t0 = 0;
                jal(ctx, 0x4CA770u, gen::fn__rwDeviceSystemRequest_004ca3e0);
                a3 = s2;
                a0 = s3;
                a1 = 0;
                a2 = 0;
                t0 = 0;
                jal(ctx, 0x4CA788u, gen::fn__rwDeviceSystemRequest_004ca3e0);
                if (v0 != 0) {
                    // 0x004ca7b4
                    charge(ctx, 12);
                    a2 = 0x960000;
                    a0 = s3;
                    a1 = 11;
                    a2 = addiu(a2, 184);  // &0x9600B8
                    a3 = 0;
                    t0 = 29;
                    jal(ctx, 0x4CA7C8u, gen::fn__rwDeviceSystemRequest_004ca3e0);
                    lw(v0, gp, -17352);  // 0x7CE928
                    s1 = 1;
                    v0 = addiu(v0, 1);
                    sw(v0, gp, -17352);  // 0x7CE928
                    backedge(ctx);
                } else {
                    // 0x004ca798
                    charge(ctx, 1);
                    s1 = 0;
                }
                // 0x004ca79c
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x004ca7a4
                    charge(ctx, 2);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            }
        }
    }
    // 0x004ca7ac
    charge(ctx, 2);
    v0 = s1;
    // 0x004ca834
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CA850 [RwEngineInit] -- initialises the engine: the free-list entry points (0x960188 / 0x96018C) set to the
//   plain allocator pair (sub_4CA380 / sub_4CA3A0, flag 1 of $a1: no free lists) or the free-list pair (sub_4C3D10 /
//   sub_4C3EE0), the free-list mode (sub_4C3960), the resource arena size ($a2, 0x960198); only in the uninitialised
//   state (0): the string functions (_dispRefImageField_0), the memory module (sub_4C4450 with $a0), the engine plugin
//   registry (sub_4C5F70), the core modules (sub_4CA190), the sky driver's init (sub_4E00E0) -- each failure closes the
//   earlier ones in reverse (sub_4C6000, sub_4C4570, sub_4C7400) --, the engine state initialised (1); 1, or 0
// 0x004CA850 sub_4CA850 -- 340 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CA850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca850
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = a1 & 0x1;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = 0;
    if (v0 == 0) {
        // 0x004ca8ac
        charge(ctx, 10);
        v1 = 0x4C0000;
        v0 = 0x960000;
        v1 = addiu(v1, 15632);  // &sub_4C3D10
        a0 = 1;
        sw(v1, v0, 392);  // 0x960188
        v1 = 0x4C0000;
        v0 = 0x960000;
        v1 = addiu(v1, 16096);  // &sub_4C3EE0
        link(ctx, 0x4CA8CCu);  // $ra first: the delay slot below depends on it
        sw(v1, v0, 396);
        call(ctx, gen::fn_sub_4C3960_004c3960);
    } else {
        // 0x004ca87c
        charge(ctx, 12);
        v1 = 0x4D0000;
        v0 = 0x960000;
        v1 = addiu(v1, -23680);  // &sub_4CA380
        a0 = 0;
        sw(v1, v0, 392);  // 0x960188
        v1 = 0x4D0000;
        v0 = 0x960000;
        v1 = addiu(v1, -23648);  // &sub_4CA3A0
        link(ctx, 0x4CA89Cu);  // $ra first: the delay slot below depends on it
        sw(v1, v0, 396);
        call(ctx, gen::fn_sub_4C3960_004c3960);
    }
    // 0x004ca8d4
    charge(ctx, 7);
    v0 = 0x960000;
    s0 = 0x960000;
    s0 = addiu(s0, 404);  // &0x960194
    sw(s2, v0, 408);  // 0x960198
    lw(v0, s0, 0);  // 0x960194
    if (v0 == 0) {
        // 0x004ca8f8
        charge(ctx, 5);
        jal(ctx, 0x4CA8F8u, gen::fn__dispRefImageField_0_004c72e0);
        s1 = v0;
        if (s1 == 0) {
            backedge(ctx);
            goto L_004ca8f0;
        }
        // 0x004ca90c
        charge(ctx, 5);
        a0 = s3;
        jal(ctx, 0x4CA90Cu, gen::fn_sub_4C4450_004c4450);
        s1 = v0;
        if (s1 != 0) {
            // 0x004ca920
            charge(ctx, 5);
            jal(ctx, 0x4CA920u, gen::fn_sub_4C5F70_004c5f70);
            s1 = v0;
            if (s1 != 0) {
                // 0x004ca934
                charge(ctx, 5);
                jal(ctx, 0x4CA934u, gen::fn_sub_4CA190_004ca190);
                s1 = v0;
                if (s1 != 0) {
                    // 0x004ca948
                    charge(ctx, 5);
                    jal(ctx, 0x4CA948u, gen::fn_sub_4E00E0_004e00e0);
                    s1 = v0;
                    if (s1 == 0) {
                        goto L_004ca968;
                    }
                    // 0x004ca95c
                    charge(ctx, 3);
                    v1 = 1;
                    sw(v1, s0, 0);
                    // 0x004ca988 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    ld(ra, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x50);
                    return;
                }
            L_004ca968:
                charge(ctx, 2);
                jal(ctx, 0x4CA968u, gen::fn_sub_4C6000_004c6000);
            }
            // 0x004ca970
            charge(ctx, 2);
            jal(ctx, 0x4CA970u, gen::fn_sub_4C4570_004c4570);
        }
        // 0x004ca978
        charge(ctx, 4);
        jal(ctx, 0x4CA978u, gen::fn_sub_4C7400_004c7400);
        backedge(ctx);
        goto L_004ca8f0;
    }
L_004ca8f0:
    charge(ctx, 2);
    v0 = s1;
    // 0x004ca988 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CFFD0 [textureReadDefaultMipmapped] -- the default texture reader with mipmaps: the names copied, the raster
//   format (4 / 0x8004 / 0x9004 by the module's mipmap flags), the level-0 image (sub_4CF9B0), the raster created; with
//   automatic mipmaps the image is copied in and the levels generated, else each further level's image read under its
//   level name (sub_4D1210 / sub_4CF9B0, sized from the locked level), the levels palettised together (sub_4CF790) or
//   gamma-corrected, each copied into its locked level; the texture (sub_4D0E40) with its names; the texture, or 0
// 0x004CFFD0 sub_4CFFD0 -- 1568 bytes; frame 0x710: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CFFD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004cffd0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x710);
    a2 = 256;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = 0x960000;
    sq(s5, sp, 0x50);
    s7 = addiu(s7, 320);  // &0x960140
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a0 = addiu(sp, 0x1A0);
    sq(s0, sp, 0x0);
    lw(v0, s7, 0);  // 0x960140
    a1 = s4;
    jalr(ctx, 0x4D0018u, v0.u());
    fp = 0x960000;
    fp = addiu(fp, 0x164);
    lw(v0, fp, 0x0);
    a0 = s4;
    jalr(ctx, 0x4D002Cu, v0.u());
    at = sltiu(v0, 256);
    if (at == 0) {
        // 0x004d029c
        charge(ctx, 14);
        lb(t0, s4, 255);
        v0 = 1;
        sw(v0, sp, 0x6F8);
        a1 = s4;
        v0 = lui(0x8000);
        a2 = 256;
        a0 = v0 | 0x1E;
        a3 = 255;
        jal(ctx, 0x4D02B8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x6FC);
        a0 = addiu(sp, 0x6F8);
        jal(ctx, 0x4D02C4u, gen::fn_sub_4C1C50_004c1c50);
        sb(zero, sp, 0x29F);
        backedge(ctx);
    }
    // 0x004d0040
    charge(ctx, 2);
    sb(zero, sp, 0xA0);
    if (s3 != 0) {
        // 0x004d0048
        charge(ctx, 3);
        lb(v0, s3, 0);
        if (v0 != 0) {
            // 0x004d0054
            charge(ctx, 11);
            lw(v0, s7, 0);
            a0 = addiu(sp, 0xA0);
            a1 = s3;
            a2 = 256;
            jalr(ctx, 0x4D0060u, v0.u());
            lw(v0, fp, 0x0);
            a0 = s3;
            jalr(ctx, 0x4D006Cu, v0.u());
            v0 = sltiu(v0, 256);
            if (v0 == 0) {
                // 0x004d0080
                charge(ctx, 13);
                lb(t0, s3, 255);
                v0 = 1;
                sw(v0, sp, 0x6F0);
                a1 = s3;
                v0 = lui(0x8000);
                a2 = 256;
                a0 = v0 | 0x1E;
                a3 = 255;
                jal(ctx, 0x4D009Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x6F4);
                a0 = addiu(sp, 0x6F0);
                jal(ctx, 0x4D00A8u, gen::fn_sub_4C1C50_004c1c50);
                sb(zero, sp, 0x19F);
            }
        }
    }
    // 0x004d00b4
    charge(ctx, 7);
    lw(v1, gp, -17312);  // 0x7CE950
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v1 = addu(v0, v1);
    lw(v0, v1, 28);
    s6 = 4;
    if (v0 != 0) {
        // 0x004d00d0
        charge(ctx, 3);
        lw(v0, v1, 32);
        s6 = s6 | 0x8000;
        if (v0 != 0) {
            // 0x004d00dc
            charge(ctx, 1);
            s6 = s6 | 0x1000;
        }
    }
    // 0x004d00e0
    charge(ctx, 17);
    a0 = addiu(sp, 0x1A0);
    a1 = addiu(sp, 0xA0);
    a2 = 0;
    a3 = s6;
    jal(ctx, 0x4D00ECu, gen::fn_sub_4D1210_004d1210);
    a0 = addiu(sp, 0x1A0);
    a1 = addiu(sp, 0xA0);
    a2 = s6;
    a3 = addiu(sp, 0x70C);
    t0 = addiu(sp, 0x708);
    t1 = addiu(sp, 0x704);
    t2 = addiu(sp, 0x700);
    sw(zero, sp, 0x70C);
    link(ctx, 0x4D0114u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x708);
    call(ctx, gen::fn_sub_4CF9B0_004cf9b0);
    sw(v0, sp, 0x6A0);
    if (v0 == 0) {
        // 0x004d02d4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004d0124
        charge(ctx, 8);
        lw(a1, sp, 0x708);
        lw(a2, sp, 0x704);
        lw(a3, sp, 0x700);
        link(ctx, 0x4D0130u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x70C);
        call(ctx, gen::fn_sub_4CE0F0_004ce0f0);
        s2 = v0;
        if (s2 == 0) {
            // 0x004d02dc
            charge(ctx, 4);
            link(ctx, 0x4D02DCu);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x6A0);
            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
            v0 = 0;
        } else {
            // 0x004d0144
            charge(ctx, 4);
            lw(v1, sp, 0x700);
            v0 = v1 & 0x8000;
            if (v0 == 0) {
                // 0x004d0558
                charge(ctx, 7);
                link(ctx, 0x4D0558u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0x6A0);
                call(ctx, gen::fn_sub_4CD940_004cd940);
                lw(a1, sp, 0x6A0);
                a0 = s2;
                jal(ctx, 0x4D0564u, gen::fn_sub_4CDCE0_004cdce0);
                if (v0 == 0) {
                    // 0x004d0584
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x4D0584u, gen::fn_sub_4CDE90_004cde90);
                    link(ctx, 0x4D058Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x6A0);
                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                    v0 = 0;
                } else {
                    // 0x004d0574
                    charge(ctx, 4);
                    link(ctx, 0x4D0574u);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x6A0);
                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                    backedge(ctx);
                L_004d0260:
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x4D0260u, gen::fn_sub_4D0E40_004d0e40);
                    s0 = v0;
                    if (s0 == 0) {
                        // 0x004d059c
                        charge(ctx, 4);
                        a0 = s2;
                        jal(ctx, 0x4D059Cu, gen::fn_sub_4CDE90_004cde90);
                        v0 = 0;
                    } else {
                        // 0x004d0274
                        charge(ctx, 5);
                        a1 = s4;
                        a0 = s0;
                        jal(ctx, 0x4D0278u, gen::fn_sub_4D0FD0_004d0fd0);
                        if (s3 == 0) {
                            // 0x004d05ac
                            charge(ctx, 5);
                            a0 = s0;
                            a1 = addiu(gp, -20328);  // &0x7CDD88
                            jal(ctx, 0x4D05B0u, gen::fn_sub_4D1070_004d1070);
                            backedge(ctx);
                        } else {
                            // 0x004d0288
                            charge(ctx, 3);
                            a1 = s3;
                            a0 = s0;
                            jal(ctx, 0x4D028Cu, gen::fn_sub_4D1070_004d1070);
                        }
                        // 0x004d0294
                        charge(ctx, 2);
                        v0 = s0;
                    }
                }
            } else {
                // 0x004d0154
                charge(ctx, 3);
                v0 = v1 & 0x1000;
                if (v0 == 0) {
                    // 0x004d0184
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x4D0184u, gen::fn_sub_4CDF80_004cdf80);
                    s1 = v0;
                    at = slti(s1, 2);
                    s0 = 1;
                    if (at != 0) {
                        // 0x004d019c
                        charge(ctx, 1);
                        lbu(v0, s2, 35);
                    L_004d01a0:
                        charge(ctx, 4);
                        v1 = sll(v0, 8);
                        v0 = v1 & 0x6000;
                        if (v0 != 0) {
                            // 0x004d01b0
                            charge(ctx, 3);
                            v0 = v1 & 0x4000;
                            if (v0 == 0) {
                                // 0x004d01dc
                                charge(ctx, 7);
                                a0 = addiu(sp, 0x2A0);
                                a1 = 0;
                                a2 = addiu(sp, 0x6A0);
                                a3 = s1;
                                t0 = 8;
                                jal(ctx, 0x4D01ECu, gen::fn_sub_4CF790_004cf790);
                                lw(a0, sp, 0x6A0);
                            } else {
                                // 0x004d01bc
                                charge(ctx, 8);
                                a0 = addiu(sp, 0x2A0);
                                a1 = 0;
                                a2 = addiu(sp, 0x6A0);
                                a3 = s1;
                                t0 = 4;
                                jal(ctx, 0x4D01CCu, gen::fn_sub_4CF790_004cf790);
                                lw(a0, sp, 0x6A0);
                            }
                            // 0x004d01f8
                            charge(ctx, 2);
                            jal(ctx, 0x4D01F8u, gen::fn_sub_4CD940_004cd940);
                            goto L_004d0200;
                        }
                        // 0x004d04e0
                        charge(ctx, 3);
                        at = slt(0, s1);
                        s5 = 0;
                        if (at == 0) {
                            backedge(ctx);
                        L_004d0200:
                            charge(ctx, 1);
                            at = slt(0, s1);
                        } else {
                            // 0x004d04ec
                            charge(ctx, 1);
                            s0 = addiu(sp, 0x6A0);
                            for (;;) {
                                // 0x004d04f0
                                charge(ctx, 7);
                                link(ctx, 0x4D04F0u);  // $ra first: the delay slot below depends on it
                                lw(a0, s0, 0);
                                call(ctx, gen::fn_sub_4CD940_004cd940);
                                s5 = addiu(s5, 1);
                                s0 = addiu(s0, 4);
                                v0 = slt(s5, s1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d050c
                            charge(ctx, 2);
                            at = slt(0, s1);
                            backedge(ctx);
                        }
                        // 0x004d0204
                        charge(ctx, 2);
                        s0 = 0;
                        if (at == 0) {
                            goto L_004d0260;
                        }
                        // 0x004d020c
                        charge(ctx, 1);
                        s5 = addiu(sp, 0x6A0);
                        for (;;) {
                            // 0x004d0210
                            charge(ctx, 6);
                            a1 = s0 & 0xFF;
                            a0 = s2;
                            a2 = 5;
                            jal(ctx, 0x4D0218u, gen::fn_sub_4CE200_004ce200);
                            if (v0 != 0) {
                                // 0x004d0228
                                charge(ctx, 5);
                                lw(a1, s5, 0);
                                a0 = s2;
                                jal(ctx, 0x4D022Cu, gen::fn_sub_4CDCE0_004cdce0);
                                if (v0 == 0) {
                                    goto L_004d0514;
                                }
                                // 0x004d023c
                                charge(ctx, 3);
                                a0 = s2;
                                jal(ctx, 0x4D023Cu, gen::fn_sub_4CDE00_004cde00);
                                goto L_004d0248;
                            }
                        L_004d0248:
                            charge(ctx, 6);
                            link(ctx, 0x4D0248u);  // $ra first: the delay slot below depends on it
                            lw(a0, s5, 0);
                            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                            s0 = addiu(s0, 1);
                            v0 = slt(s0, s1);
                            s5 = addiu(s5, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        goto L_004d0260;
                    }
                    // 0x004d0304
                    charge(ctx, 1);
                    s5 = addiu(sp, 0x6A4);
                    for (;;) {
                        // 0x004d0308
                        charge(ctx, 11);
                        lw(v0, s7, 0);
                        a0 = addiu(sp, 0x1A0);
                        a1 = s4;
                        a2 = 256;
                        jalr(ctx, 0x4D0314u, v0.u());
                        lw(v0, fp, 0x0);
                        a0 = s4;
                        jalr(ctx, 0x4D0320u, v0.u());
                        at = sltiu(v0, 256);
                        if (at == 0) {
                            // 0x004d0458
                            charge(ctx, 16);
                            lb(t0, s4, 255);
                            v0 = 1;
                            sw(v0, sp, 0x6E8);
                            a1 = s4;
                            v0 = lui(0x8000);
                            a2 = 256;
                            a0 = v0 | 0x1E;
                            a3 = 255;
                            jal(ctx, 0x4D0474u, gen::fn_sub_4C1D10_004c1d10);
                            v1 = addiu(sp, 0x6EC);
                            a0 = addiu(sp, 0x6E8);
                            link(ctx, 0x4D0484u);  // $ra first: the delay slot below depends on it
                            sw(v0, v1, 0);
                            call(ctx, gen::fn_sub_4C1C50_004c1c50);
                            v0 = addiu(sp, 0x29F);
                            sb(zero, v0, 0);
                            backedge(ctx);
                        } else {
                            // 0x004d0334
                            charge(ctx, 1);
                        }
                        // 0x004d0338
                        charge(ctx, 2);
                        sb(zero, sp, 0xA0);
                        if (s3 != 0) {
                            // 0x004d0340
                            charge(ctx, 3);
                            lb(v0, s3, 0);
                            if (v0 != 0) {
                                // 0x004d034c
                                charge(ctx, 11);
                                lw(v0, s7, 0);
                                a0 = addiu(sp, 0xA0);
                                a1 = s3;
                                a2 = 256;
                                jalr(ctx, 0x4D0358u, v0.u());
                                lw(v0, fp, 0x0);
                                a0 = s3;
                                jalr(ctx, 0x4D0364u, v0.u());
                                v0 = sltiu(v0, 256);
                                if (v0 == 0) {
                                    // 0x004d0378
                                    charge(ctx, 16);
                                    lb(t0, s3, 255);
                                    v0 = 1;
                                    sw(v0, sp, 0x6E0);
                                    a1 = s3;
                                    v0 = lui(0x8000);
                                    a2 = 256;
                                    a0 = v0 | 0x1E;
                                    a3 = 255;
                                    jal(ctx, 0x4D0394u, gen::fn_sub_4C1D10_004c1d10);
                                    v1 = addiu(sp, 0x6E4);
                                    a0 = addiu(sp, 0x6E0);
                                    link(ctx, 0x4D03A4u);  // $ra first: the delay slot below depends on it
                                    sw(v0, v1, 0);
                                    call(ctx, gen::fn_sub_4C1C50_004c1c50);
                                    v0 = addiu(sp, 0x19F);
                                    sb(zero, v0, 0);
                                }
                            }
                        }
                        // 0x004d03b8
                        charge(ctx, 34);
                        a2 = s0 & 0xFF;
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0xA0);
                        a3 = s6;
                        jal(ctx, 0x4D03C4u, gen::fn_sub_4D1210_004d1210);
                        a1 = s0 & 0xFF;
                        a0 = s2;
                        a2 = 5;
                        jal(ctx, 0x4D03D4u, gen::fn_sub_4CE200_004ce200);
                        lw(v0, s2, 12);
                        a0 = s2;
                        sw(v0, sp, 0x70C);
                        lw(v0, s2, 16);
                        sw(v0, sp, 0x708);
                        lw(v0, s2, 20);
                        sw(v0, sp, 0x704);
                        lbu(v1, s2, 35);
                        lbu(v0, s2, 32);
                        v1 = sll(v1, 8);
                        v0 = v1 | v0;
                        link(ctx, 0x4D0408u);  // $ra first: the delay slot below depends on it
                        sw(v0, sp, 0x700);
                        call(ctx, gen::fn_sub_4CDE00_004cde00);
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0xA0);
                        a2 = s6;
                        a3 = addiu(sp, 0x70C);
                        t0 = addiu(sp, 0x708);
                        t1 = addiu(sp, 0x704);
                        t2 = addiu(sp, 0x700);
                        jal(ctx, 0x4D0428u, gen::fn_sub_4CF9B0_004cf9b0);
                        sw(v0, s5, 0);
                        lw(v0, s5, 0);
                        if (v0 == 0) {
                            break;
                        }
                        // 0x004d0440
                        charge(ctx, 4);
                        s0 = addiu(s0, 1);
                        v0 = slt(s0, s1);
                        s5 = addiu(s5, 4);
                        if (v0 == 0) {
                            goto L_004d0450_45;
                        }
                        backedge(ctx);
                    }
                    // 0x004d0498
                    charge(ctx, 3);
                    s0 = addiu(s0, -1);
                    if (i64(s0) >= 0) {
                        // 0x004d04a4
                        charge(ctx, 3);
                        v0 = sll(s0, 2);
                        v0 = addu(v0, sp);
                        s1 = addiu(v0, 1696);
                        for (;;) {
                            // 0x004d04b0
                            charge(ctx, 7);
                            link(ctx, 0x4D04B0u);  // $ra first: the delay slot below depends on it
                            lw(a0, s1, 0);
                            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                            s0 = addiu(s0, -1);
                            s1 = addiu(s1, -4);
                            if (i64(s0) < 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004d04cc
                        charge(ctx, 1);
                    }
                    // 0x004d04d0
                    charge(ctx, 4);
                    a0 = s2;
                    jal(ctx, 0x4D04D0u, gen::fn_sub_4CDE90_004cde90);
                    v0 = 0;
                } else {
                    // 0x004d0160
                    charge(ctx, 5);
                    lw(a1, sp, 0x6A0);
                    a0 = s2;
                    jal(ctx, 0x4D0164u, gen::fn_sub_4CDCE0_004cdce0);
                    if (v0 != 0) {
                        // 0x004d0174
                        charge(ctx, 4);
                        link(ctx, 0x4D0174u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x6A0);
                        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                        goto L_004d0260;
                    }
                    // 0x004d02ec
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x4D02ECu, gen::fn_sub_4CDE90_004cde90);
                    link(ctx, 0x4D02F4u);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x6A0);
                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                    v0 = 0;
                }
            }
        }
    }
    // 0x004d05c0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x710);
    return;
L_004d0450_45:
    charge(ctx, 2);
    lbu(v0, s2, 35);
    backedge(ctx);
    goto L_004d01a0;
L_004d0514:
    charge(ctx, 3);
    at = slt(s0, s1);
    if (at != 0) {
        // 0x004d0520
        charge(ctx, 3);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        s3 = addiu(v0, 1696);
        for (;;) {
            // 0x004d052c
            charge(ctx, 7);
            link(ctx, 0x4D052Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s3, 0);
            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
            s0 = addiu(s0, 1);
            s3 = addiu(s3, 4);
            v0 = slt(s0, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004d0548
    charge(ctx, 4);
    a0 = s2;
    jal(ctx, 0x4D0548u, gen::fn_sub_4CDE90_004cde90);
    v0 = 0;
    // 0x004d05c0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x710);
}

// sub_4D6700 [rwDMARemoveHandlers] -- removes the RW DMA layer's interrupt handlers: the DMAC channel 2 and 1 handlers
//   and the INTC 2 (VBLANK start) handler disabled when they were enabled (the flags at gp 0x7CE974 / 0x7CE970 / 0x7CE96C
//   cleared), then each handler removed (_sceRemoveDmacHandler / _sceRemoveIntcHandler with the ids at 0x7CDDB8 /
//   0x7CDDB4 / 0x7CDDB0) and its id set to -1; the last removal's result
// 0x004D6700 sub_4D6700 -- 168 bytes; frame 0x10: ra sp+0x0
void sub_4D6700(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d6700
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lbu(v0, gp, -17276);  // 0x7CE974
    if (v0 != 0) {
        // 0x004d676c
        charge(ctx, 4);
        a0 = 2;
        jal(ctx, 0x4D676Cu, gen::fn_DisableDmac_00503d10);
        sb(zero, gp, -17276);  // 0x7CE974
        backedge(ctx);
    }
    // 0x004d6714
    charge(ctx, 3);
    lbu(v0, gp, -17280);  // 0x7CE970
    if (v0 != 0) {
        // 0x004d677c
        charge(ctx, 4);
        a0 = 1;
        jal(ctx, 0x4D677Cu, gen::fn_DisableDmac_00503d10);
        sb(zero, gp, -17280);  // 0x7CE970
        backedge(ctx);
    }
    // 0x004d6720
    charge(ctx, 3);
    lbu(v0, gp, -17284);  // 0x7CE96C
    if (v0 != 0) {
        // 0x004d678c
        charge(ctx, 4);
        a0 = 2;
        jal(ctx, 0x4D678Cu, gen::fn_DisableIntc_00503c40);
        sb(zero, gp, -17284);  // 0x7CE96C
        backedge(ctx);
    }
    // 0x004d672c
    charge(ctx, 16);
    lw(a1, gp, -20280);  // 0x7CDDB8
    a0 = 2;
    jal(ctx, 0x4D6730u, gen::fn__sceRemoveDmacHandler_00502e90);
    lw(a1, gp, -20284);  // 0x7CDDB4
    v0 = si(-1);
    a0 = 1;
    link(ctx, 0x4D6744u);  // $ra first: the delay slot below depends on it
    sw(v0, gp, -20280);  // 0x7CDDB8
    call(ctx, gen::fn__sceRemoveDmacHandler_00502e90);
    lw(a1, gp, -20288);  // 0x7CDDB0
    v0 = si(-1);
    a0 = 2;
    link(ctx, 0x4D6758u);  // $ra first: the delay slot below depends on it
    sw(v0, gp, -20284);  // 0x7CDDB4
    call(ctx, gen::fn__sceRemoveIntcHandler_00502e60);
    v1 = si(-1);
    sw(v1, gp, -20288);  // 0x7CDDB0
    // 0x004d679c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4D8440 [skyTextureKLStreamWrite] -- the sky texture plugin's stream write: the raster's mipmap K / L halfword
//   written as 4 bytes (sub_4C17F0); the stream, or 0
// 0x004D8440 sub_4D8440 -- 92 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4D8440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d8440
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (a2 != 0) {
        // 0x004d8454
        charge(ctx, 3);
        lw(v1, a2, 0);
        if (v1 == 0) {
            goto L_004d8488;
        }
        // 0x004d8460
        charge(ctx, 10);
        lw(v0, gp, -16968);  // 0x7CEAA8
        a1 = addiu(sp, 0x2C);
        a2 = 4;
        v0 = addu(v1, v0);
        lhu(v0, v0, 20);
        link(ctx, 0x4D8474u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x2C);
        call(ctx, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) s0 = 0;
        v0 = s0;
        // 0x004d848c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004d8488:
    charge(ctx, 1);
    v0 = 0;
    // 0x004d848c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4DF140 [skyRasterNativeStreamWrite] -- writes a raster's PS2 native data: refused for a locked raster; the
//   64-byte struct (size, depth, format, the palette / swizzle kind, the raster extension's GS words and sizes), then the
//   pixel chunk -- the pixels as one block, or for a palettised texture the palette and the pixel data separately (the
//   palette moved into place first when needed); the raster, or 0
// 0x004DF140 sub_4DF140 -- 688 bytes; frame 0xA0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4DF140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004df140
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    lbu(v0, a1, 34);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    v0 = v0 & 0x1E;
    sq(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x004df278
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004df170
        charge(ctx, 21);
        lw(v1, gp, -16968);  // 0x7CEAA8
        s0 = addiu(sp, 0x6E);
        lbu(a0, s3, 35);
        v0 = 2;
        lw(a2, s3, 16);
        lw(a3, s3, 12);
        lw(a1, s3, 20);
        sh(zero, s0, 0);
        s2 = addu(s3, v1);
        lbu(v1, s3, 32);
        a0 = sll(a0, 8);
        sw(a2, sp, 0x64);
        lw(t0, s2, 40);
        lw(a2, s2, 44);
        sw(a3, sp, 0x60);
        sw(a1, sp, 0x68);
        a0 = a0 | v1;
        lbu(v1, s2, 54);
        sh(a0, sp, 0x6C);
        s1 = addu(t0, a2);
        if (v1 == v0) {
            // 0x004df1c4
            charge(ctx, 3);
            v0 = 8;
            if (a1 == v0) {
                // 0x004df1d0
                charge(ctx, 2);
                v0 = 1;
                sh(v0, s0, 0);
            }
        }
        // 0x004df1d8
        charge(ctx, 5);
        lbu(v1, s2, 54);
        v0 = 1;
        v1 = v1 & 0x1;
        if (v1 == v0) {
            // 0x004df280
            charge(ctx, 3);
            v0 = 2;
            sh(v0, s0, 0);
            backedge(ctx);
        }
        // 0x004df1ec
        charge(ctx, 33);
        v0 = 0x30000;
        lw(t4, s2, 8);
        a3 = v0 | 0x7002;
        lw(t3, s2, 12);
        lw(t2, s2, 16);
        a0 = s4;
        lbu(t1, s2, 22);
        a1 = 1;
        lw(v1, s2, 24);
        a2 = 64;
        lw(v0, s2, 28);
        t0 = 55;
        sw(t4, sp, 0x70);
        sw(t3, sp, 0x74);
        sw(t2, sp, 0x78);
        sw(t1, sp, 0x7C);
        sw(v1, sp, 0x80);
        sw(v0, sp, 0x84);
        lw(t4, s2, 32);
        lw(t3, s2, 36);
        lw(t2, s2, 40);
        lw(t1, s2, 44);
        lw(v1, s2, 48);
        lhu(v0, s2, 20);
        sw(t4, sp, 0x88);
        sw(t3, sp, 0x8C);
        sw(t2, sp, 0x90);
        sw(t1, sp, 0x94);
        sw(v1, sp, 0x98);
        link(ctx, 0x4DF260u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x9C);
        call(ctx, gen::fn_sub_4C15A0_004c15a0);
        if (v0 != 0) {
            // 0x004df28c
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(sp, 0x60);
            a2 = 64;
            jal(ctx, 0x4DF294u, gen::fn_sub_4C17F0_004c17f0);
            if (v0 != 0) {
                // 0x004df2ac
                charge(ctx, 9);
                v0 = 0x30000;
                a0 = s4;
                a1 = 1;
                a2 = s1;
                a3 = v0 | 0x7002;
                t0 = 55;
                jal(ctx, 0x4DF2C0u, gen::fn_sub_4C15A0_004c15a0);
                if (v0 == 0) {
                    // 0x004df2f4
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004df2d0
                    charge(ctx, 4);
                    lhu(v1, s0, 0);
                    at = sltiu(v1, 2);
                    if (at != 0) {
                        // 0x004df2fc
                        charge(ctx, 6);
                        lw(a1, s3, 4);
                        a0 = s4;
                        a2 = s1;
                        jal(ctx, 0x4DF304u, gen::fn_sub_4C53F0_004c53f0);
                        if (v0 != 0) {
                        L_004df31c:
                            charge(ctx, 2);
                            v0 = s3;
                        } else {
                            // 0x004df314
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x004df2e0
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x004df324
                            charge(ctx, 7);
                            lw(v0, s3, 36);
                            lw(a2, s2, 40);
                            lw(a1, v0, 4);
                            a0 = s4;
                            jal(ctx, 0x4DF330u, gen::fn_sub_4C53F0_004c53f0);
                            if (v0 == 0) {
                                // 0x004df3cc
                                charge(ctx, 1);
                                v0 = 0;
                            } else {
                                // 0x004df340
                                charge(ctx, 4);
                                lbu(v0, s3, 33);
                                v0 = v0 & 0x40;
                                if (v0 != 0) {
                                    // 0x004df350
                                    charge(ctx, 9);
                                    lw(v1, s3, 36);
                                    lw(a1, s3, 8);
                                    lw(v0, v1, 0);
                                    v0 = addiu(v0, -1);
                                    v0 = sll(v0, 6);
                                    v0 = addu(v1, v0);
                                    lw(a0, v0, 68);
                                    if (a0 != a1) {
                                        // 0x004df374
                                        charge(ctx, 4);
                                        lw(v0, s2, 44);
                                        v1 = addiu(v0, -80);
                                        if (v1 != 0) {
                                            for (;;) {
                                                // 0x004df384
                                                charge(ctx, 7);
                                                lq(v0, a1, 0);
                                                v1 = addiu(v1, -16);
                                                sq(v0, a0, 0);
                                                a1 = addiu(a1, 16);
                                                a0 = addiu(a0, 16);
                                                if (v1 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                        }
                                    }
                                }
                                // 0x004df3a0
                                charge(ctx, 3);
                                lw(a2, s2, 44);
                                if (a2 == 0) {
                                    backedge(ctx);
                                    goto L_004df31c;
                                }
                                // 0x004df3ac
                                charge(ctx, 6);
                                lw(v0, s3, 8);
                                a0 = s4;
                                a1 = addiu(v0, -80);
                                jal(ctx, 0x4DF3B4u, gen::fn_sub_4C53F0_004c53f0);
                                if (v0 != 0) {
                                    backedge(ctx);
                                    goto L_004df31c;
                                }
                                // 0x004df3c4
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        } else {
                            // 0x004df2ec
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    }
                }
            } else {
                // 0x004df2a4
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x004df270
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004df3d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// sub_4DF7C0 [skyTextureNativeGetSize] -- the sky texture's native stream size: 20 + the name and mask string chunks
//   (sub_4C7410 + 12 each) + the raster's pixel and palette sizes + 100; 1
// 0x004DF7C0 sub_4DF7C0 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4DF7C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004df7c0
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sw(zero, a0, 0);
    s0 = a1;
    lw(v0, a0, 0);
    v0 = addiu(v0, 20);
    sw(v0, a0, 0);
    a0 = addiu(s0, 16);
    jal(ctx, 0x4DF7E8u, gen::fn_sub_4C7410_004c7410);
    v1 = addiu(v0, 12);
    a0 = addiu(s0, 48);
    lw(v0, s1, 0);
    v0 = addu(v0, v1);
    link(ctx, 0x4DF800u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 0);
    call(ctx, gen::fn_sub_4C7410_004c7410);
    lw(v1, s1, 0);
    a0 = addiu(v0, 12);
    a2 = 76;
    v0 = 1;
    v1 = addu(v1, a0);
    sw(v1, s1, 0);
    lw(a1, s0, 0);
    lw(a0, gp, -16968);  // 0x7CEAA8
    lw(v1, s1, 0);
    a0 = addu(a1, a0);
    lw(a1, a0, 40);
    lw(a0, a0, 44);
    a0 = addu(a1, a0);
    a0 = addiu(a0, 12);
    a0 = addu(a2, a0);
    a0 = addiu(a0, 12);
    v1 = addu(v1, a0);
    sw(v1, s1, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4DF870 [skyTextureNativeStreamWrite] -- writes a texture's PS2 native data: the struct chunk (the platform tag
//   0x7CDDE0 'PS2', the filter / address word), the name and mask strings (sub_4C7460), the raster chunk header and the
//   raster (sub_4DF140); 1, or 0
// 0x004DF870 sub_4DF870 -- 348 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4DF870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004df870
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x30000;
    sd(ra, sp, 0x30);
    a2 = 8;
    sq(s2, sp, 0x20);
    a3 = v0 | 0x7002;
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a1, 0);
    t0 = 55;
    a1 = 1;
    jal(ctx, 0x4DF8A0u, gen::fn_sub_4C15A0_004c15a0);
    if (v0 != 0) {
        // 0x004df8b8
        charge(ctx, 23);
        a0 = addiu(sp, 0x48);
        a1 = addiu(gp, -20240);  // "PS2"
        a2 = 4;
        jal(ctx, 0x4DF8C0u, gen::fn_memcpy_00521250);
        lw(a3, s1, 80);
        a0 = s2;
        a1 = addiu(sp, 0x48);
        a2 = 8;
        v0 = a3 & 0xF00;
        t0 = a3 & 0xFF;
        v1 = srl(v0, 8);
        v0 = a3 & 0xF000;
        a3 = srl(v0, 12);
        v0 = v1 & 0xF;
        v1 = sll(v0, 8);
        v0 = a3 & 0xF;
        v1 = t0 | v1;
        v0 = sll(v0, 12);
        v0 = v0 | v1;
        link(ctx, 0x4DF904u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x4C);
        call(ctx, gen::fn_sub_4C53F0_004c53f0);
        if (v0 != 0) {
            // 0x004df91c
            charge(ctx, 5);
            a0 = addiu(s1, 16);
            a1 = s2;
            jal(ctx, 0x4DF920u, gen::fn_sub_4C7460_004c7460);
            if (v0 != 0) {
                // 0x004df938
                charge(ctx, 5);
                a0 = addiu(s1, 48);
                a1 = s2;
                jal(ctx, 0x4DF93Cu, gen::fn_sub_4C7460_004c7460);
                if (v0 != 0) {
                    // 0x004df954
                    charge(ctx, 17);
                    lw(v1, gp, -16968);  // 0x7CEAA8
                    v0 = 0x30000;
                    a3 = v0 | 0x7002;
                    a2 = 76;
                    a0 = s2;
                    a1 = 1;
                    t0 = 55;
                    v0 = addu(s0, v1);
                    lw(v1, v0, 40);
                    lw(v0, v0, 44);
                    v0 = addu(v1, v0);
                    v0 = addiu(v0, 12);
                    s1 = addu(a2, v0);
                    a2 = s1;
                    jal(ctx, 0x4DF988u, gen::fn_sub_4C15A0_004c15a0);
                    if (v0 != 0) {
                        // 0x004df9a0
                        charge(ctx, 5);
                        a0 = s2;
                        a1 = s0;
                        a2 = s1;
                        jal(ctx, 0x4DF9A8u, gen::fn_sub_4DF140_004df140);
                        v0 = sltu(0, v0);
                    } else {
                        // 0x004df998
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x004df94c
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x004df930
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x004df914
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004df8b0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004df9b4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// SkyUseMode -- selects the sky driver's video mode: refused once the device is started (gp 0x7CEAC8) and outside
//   -1..89; the mode index stored (gp 0x7CEAD0); for a mode other than -1 its 24-byte row of the mode table 0x77E710
//   (width, height, depth, flags, refresh, format) copied into the frame-buffer and display modes (0x965730 / 0x965748),
//   a field mode (flag 0x100) halving the display height and keeping the first width (gp 0x7CEA90) with one buffer each,
//   a frame mode two; the default raster format (gp 0x7CEACC) 0x500 (8888) for a 32-bit frame buffer, else 0x100 (1555);
//   1, or 0
// 0x004DFF20 SkyUseMode -- 436 bytes; frame 0x20
void SkyUseMode(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x004dff20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lw(v0, gp, -16936);  // 0x7CEAC8
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
    if (v0 != 0) {
        // 0x004dff38
        charge(ctx, 1);
        v0 = slti(a0, 90);
    }
    // 0x004dff3c
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004dff44
        charge(ctx, 2);
        v0 = slti(a0, -1);
        v0 = v0 ^ 0x1;
    }
    // 0x004dff4c
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x004e00c8
        charge(ctx, 1);
        sp = addiu(sp, 0x20);
    } else {
        // 0x004dff54
        charge(ctx, 3);
        v1 = si(-1);
        sw(a0, gp, -16928);  // 0x7CEAD0
        if (a0 != v1) {
            // 0x004dff90
            charge(ctx, 46);
            a1 = sll(a0, 1);
            v1 = 0x780000;
            a0 = addu(a1, a0);
            v1 = addiu(v1, -6384);  // &videoModes
            a0 = sll(a0, 3);
            a2 = 0x960000;
            v1 = addu(v1, a0);
            t1 = 0x960000;
            lwc1(f2, v1, 12);
            t0 = 0x960000;
            lwc1(f5, v1, 0);
            t3 = 0x960000;
            lwc1(f4, v1, 4);
            t2 = 0x960000;
            lwc1(f1, v1, 16);
            a3 = 0x960000;
            lwc1(f0, v1, 20);
            a1 = 0x960000;
            lwc1(f3, v1, 8);
            a0 = 0x960000;
            swc1(f2, sp, 0xC);
            lwc1(f2, sp, 0xC);
            swc1(f5, sp, 0x0);
            swc1(f1, sp, 0x10);
            swc1(f0, sp, 0x14);
            swc1(f4, sp, 0x4);
            ld(t4, sp, 0x10);
            lwc1(f1, sp, 0x0);
            v1 = 0x960000;
            lwc1(f0, sp, 0x4);
            swc1(f3, sp, 0x8);
            swc1(f2, a2, 22356);  // g_skyDisplayMode+0xC
            lq(t5, sp, 0x0);
            lw(v1, v1, 22356);  // g_skyDisplayMode+0xC
            lwc1(f3, sp, 0x8);
            sd(t4, t2, 22336);  // customMode+0x10
            swc1(f1, t1, 22344);  // g_skyDisplayMode
            swc1(f0, t0, 22348);  // g_skyDisplayMode+0x4
            lwc1(f1, sp, 0x10);
            lwc1(f0, sp, 0x14);
            sq(t5, t3, 22320);  // customMode
            v1 = v1 & 0x100;
            swc1(f3, a3, 22352);  // g_skyDisplayMode+0x8
            swc1(f1, a1, 22360);  // g_skyDisplayMode+0x10
            swc1(f0, a0, 22364);  // g_skyDisplayMode+0x14
            if (v1 == 0) {
                // 0x004e008c
                charge(ctx, 8);
                a0 = 2;
                v1 = 0x960000;
                sb(a0, v1, 22368);  // 0x965760
                v1 = 0x960000;
                sb(a0, v1, 22369);  // 0x965761
                a0 = 1;
                v1 = 0x960000;
                sb(a0, v1, 22371);  // 0x965763
            } else {
                // 0x004e0048
                charge(ctx, 12);
                a0 = 1;
                v1 = 0x960000;
                sb(a0, v1, 22368);  // 0x965760
                v1 = 0x960000;
                sb(a0, v1, 22369);  // 0x965761
                v1 = 0x960000;
                lw(a0, gp, -16992);  // 0x7CEA90
                lw(a1, v1, 22348);  // g_skyDisplayMode+0x4
                v1 = 0x960000;
                a1 = sra(a1, 1);
                sw(a1, v1, 22348);  // g_skyDisplayMode+0x4
                if (a0 == 0) {
                    // 0x004e00b8
                    charge(ctx, 4);
                    v1 = 0x960000;
                    lw(v1, v1, 22344);  // g_skyDisplayMode
                    sw(v1, gp, -16992);  // 0x7CEA90
                    backedge(ctx);
                } else {
                    // 0x004e0078
                    charge(ctx, 2);
                    v1 = 0x960000;
                    sw(a0, v1, 22344);  // g_skyDisplayMode
                }
                // 0x004e0080
                charge(ctx, 3);
                v1 = 0x960000;
                sb(zero, v1, 22371);  // 0x965763
            }
            // 0x004e00ac
            charge(ctx, 3);
            v1 = 0x960000;
            sb(zero, v1, 22370);  // 0x965762
            backedge(ctx);
        }
        // 0x004dff60
        charge(ctx, 5);
        v1 = 0x960000;
        a0 = 32;
        lw(v1, v1, 22328);  // customMode+0x8
        if (v1 != a0) {
            // 0x004dff80
            charge(ctx, 2);
            v1 = 256;
            sw(v1, gp, -16932);  // 0x7CEACC
        } else {
            // 0x004dff74
            charge(ctx, 3);
            v1 = 1280;
            sw(v1, gp, -16932);  // 0x7CEACC
        }
        // 0x004dff88
        charge(ctx, 2);
        sp = addiu(sp, 0x20);
    }
    // 0x004e00cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// skyCustomModeIsOk -- checks the selected video mode before the start: the display height decides the GS mode (224 /
//   448: NTSC 2, 256 / 512: PAL 3, 480: DTV 80) unless set; the buffer counts 1 or 2 (both 2 for a frame mode), depths 16
//   or 32, the raster formats filled in from the depth (16 -> 0x100 1555, 32 -> 0x500 8888) or checked against it; then
//   the frame, display and Z buffers (widths rounded to 64, heights to 64 for 16-bit or 32 for 32-bit) must fit the 4 MiB
//   of GS memory; 1, or 0
// 0x004E0C10 skyCustomModeIsOk -- 1096 bytes; leaf frame (no stack)
void skyCustomModeIsOk(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, gp{ctx, 28};
    // 0x004e0c10
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lbu(v0, v0, 22370);  // 0x965762
    if (v0 == 0) {
        // 0x004e0c20
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 224;
        lw(a0, v0, 22348);  // g_skyDisplayMode+0x4
        if (a0 != v1) {
            // 0x004e0c34
            charge(ctx, 3);
            v0 = 448;
            if (a0 == v0) {
                goto L_004e0c6c;
            }
            // 0x004e0c40
            charge(ctx, 3);
            v0 = 256;
            if (a0 == v0) {
                goto L_004e0c6c;
            }
            // 0x004e0c4c
            charge(ctx, 3);
            v0 = 480;
            if (a0 == v0) {
                goto L_004e0c6c;
            }
            // 0x004e0c58
            charge(ctx, 3);
            v0 = 512;
            if (a0 == v0) {
                goto L_004e0c6c;
            }
            // 0x004e0c64
            charge(ctx, 2);
            v0 = 0;
            // 0x004e1050 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_004e0c6c:
        charge(ctx, 3);
        v0 = 480;
        if (a0 == v0) {
            // 0x004e0cd0
            charge(ctx, 4);
            v1 = 80;
            v0 = 0x960000;
            sb(v1, v0, 22370);  // 0x965762
            backedge(ctx);
        } else {
            // 0x004e0c78
            charge(ctx, 3);
            v0 = 256;
            if (a0 != v0) {
                // 0x004e0c84
                charge(ctx, 3);
                v0 = 512;
                if (a0 == v0) {
                    goto L_004e0ce0;
                }
                // 0x004e0c90
                charge(ctx, 3);
                v1 = 2;
                v0 = 0x960000;
                sb(v1, v0, 22370);  // 0x965762
                goto L_004e0c9c;
            }
        L_004e0ce0:
            charge(ctx, 4);
            v1 = 3;
            v0 = 0x960000;
            sb(v1, v0, 22370);  // 0x965762
            backedge(ctx);
        }
    }
L_004e0c9c:
    charge(ctx, 5);
    v0 = 0x960000;
    v1 = 2;
    lbu(a0, v0, 22370);  // 0x965762
    if (a0 != v1) {
        // 0x004e0cb0
        charge(ctx, 3);
        v0 = 80;
        if (a0 == v0) {
            goto L_004e0cf0;
        }
        // 0x004e0cbc
        charge(ctx, 3);
        v0 = 3;
        if (a0 == v0) {
            goto L_004e0cf0;
        }
        // 0x004e0cc8
        charge(ctx, 2);
        v0 = 0;
        // 0x004e1050 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004e0cf0:
    charge(ctx, 4);
    v0 = 0x960000;
    lbu(a2, v0, 22371);  // 0x965763
    if (a2 != 0) {
        // 0x004e0d00
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 2;
        lbu(v0, v0, 22368);  // 0x965760
        if (v0 == v1) {
            // 0x004e0d14
            charge(ctx, 4);
            v0 = 0x960000;
            lbu(v0, v0, 22369);  // 0x965761
            if (v0 != v1) {
                goto L_004e0d4c;
            }
            goto L_004e0d24;
        }
    L_004e0d4c:
        charge(ctx, 2);
        v0 = 0;
        // 0x004e1050 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004e0d24:
    charge(ctx, 5);
    v0 = 0x960000;
    v1 = 1;
    lbu(a0, v0, 22368);  // 0x965760
    if (a0 != v1) {
        // 0x004e0d38
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            goto L_004e0d54;
        }
    L_004e0d44:
        charge(ctx, 2);
        v0 = 0;
        // 0x004e1050 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004e0d54:
    charge(ctx, 5);
    v0 = 0x960000;
    v1 = 1;
    lbu(a0, v0, 22369);  // 0x965761
    if (a0 != v1) {
        // 0x004e0d68
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            goto L_004e0d74;
        }
        backedge(ctx);
        goto L_004e0d44;
    }
L_004e0d74:
    charge(ctx, 5);
    v0 = 0x960000;
    v1 = 16;
    lw(a1, v0, 22328);  // customMode+0x8
    if (a1 != v1) {
        // 0x004e0d88
        charge(ctx, 3);
        v0 = 32;
        if (a1 == v0) {
            goto L_004e0d9c;
        }
    L_004e0d94:
        charge(ctx, 2);
        v0 = 0;
        // 0x004e1050 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004e0d9c:
    charge(ctx, 5);
    v0 = 0x960000;
    a0 = 16;
    lw(v1, v0, 22352);  // g_skyDisplayMode+0x8
    if (v1 != a0) {
        // 0x004e0db0
        charge(ctx, 3);
        v0 = 32;
        if (v1 == v0) {
            goto L_004e1014;
        }
        // 0x004e0dbc
        charge(ctx, 2);
        backedge(ctx);
        goto L_004e0d94;
    }
L_004e1014:
    charge(ctx, 3);
    v0 = 16;
    if (a1 != v0) {
        backedge(ctx);
        // 0x004e0dd8
        charge(ctx, 5);
        v0 = 0x960000;
        a0 = si(-32);
        lw(a3, v0, 22324);  // customMode+0x4
        v0 = addiu(a3, 31);
        t0 = v0 & a0;
    } else {
        // 0x004e1020
        charge(ctx, 2);
        v0 = 0x960000;
        backedge(ctx);
        // 0x004e0dc4
        charge(ctx, 5);
        a0 = si(-64);
        lw(a3, v0, 22324);
        v0 = addiu(a3, 63);
        t0 = v0 & a0;
    }
    // 0x004e0dec
    charge(ctx, 9);
    v0 = 0x960000;
    a0 = si(-64);
    lw(v0, v0, 22320);  // customMode
    v0 = addiu(v0, 63);
    v0 = v0 & a0;
    mult(t0, v0, t0);
    a0 = 16;
    if (a1 != a0) {
        // 0x004e0e18
        charge(ctx, 1);
        a0 = 4;
    } else {
        // 0x004e0e10
        charge(ctx, 2);
        a0 = 2;
    }
    // 0x004e0e1c
    charge(ctx, 4);
    mult(a0, t0, a0);
    t0 = 16;
    if (v1 != t0) {
        // 0x004e0e44
        charge(ctx, 5);
        t0 = 0x960000;
        t1 = si(-32);
        lw(t0, t0, 22348);  // g_skyDisplayMode+0x4
        t0 = addiu(t0, 31);
        t2 = t0 & t1;
    } else {
        // 0x004e0e2c
        charge(ctx, 6);
        t0 = 0x960000;
        t1 = si(-64);
        lw(t0, t0, 22348);  // g_skyDisplayMode+0x4
        t0 = addiu(t0, 63);
        t2 = t0 & t1;
    }
    // 0x004e0e58
    charge(ctx, 9);
    t0 = 0x960000;
    t1 = si(-64);
    lw(t0, t0, 22344);  // g_skyDisplayMode
    t0 = addiu(t0, 63);
    t0 = t0 & t1;
    mult(t1, t0, t2);
    t0 = 16;
    if (v1 != t0) {
        // 0x004e0e84
        charge(ctx, 1);
        v1 = 4;
    } else {
        // 0x004e0e7c
        charge(ctx, 2);
        v1 = 2;
    }
    // 0x004e0e88
    charge(ctx, 5);
    mult(v1, t1, v1);
    t0 = 16;
    lw(t1, gp, -20248);  // g_skyZBufferDepth
    if (t1 != t0) {
        // 0x004e0eac
        charge(ctx, 3);
        t0 = addiu(a3, 31);
        a3 = si(-32);
        a3 = t0 & a3;
    } else {
        // 0x004e0e9c
        charge(ctx, 4);
        t0 = addiu(a3, 63);
        a3 = si(-64);
        a3 = t0 & a3;
    }
    // 0x004e0eb8
    charge(ctx, 4);
    mult(a3, v0, a3);
    v0 = 16;
    if (t1 != v0) {
        // 0x004e0ed0
        charge(ctx, 1);
        v0 = 4;
    } else {
        // 0x004e0ec8
        charge(ctx, 2);
        v0 = 2;
    }
    // 0x004e0ed4
    charge(ctx, 2);
    mult(v0, a3, v0);
    if (a2 != 0) {
        // 0x004e0edc
        charge(ctx, 3);
        at = sltu(a0, v1);
        if (at == 0) {
            goto L_004e0ef0;
        }
        // 0x004e0ee8
        charge(ctx, 2);
        v0 = 0;
        // 0x004e1050 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004e0ef0:
    charge(ctx, 4);
    a2 = 0x960000;
    lw(a3, a2, 22340);  // customMode+0x14
    if (a3 == 0) {
        // 0x004e0f2c
        charge(ctx, 3);
        a2 = 16;
        if (a1 != a2) {
            // 0x004e0f40
            charge(ctx, 1);
            a2 = 1280;
        } else {
            // 0x004e0f38
            charge(ctx, 2);
            a2 = 256;
        }
        // 0x004e0f44
        charge(ctx, 2);
        a1 = 0x960000;
        sw(a2, a1, 22340);  // customMode+0x14
    L_004e0f4c:
        charge(ctx, 4);
        a1 = 0x960000;
        lw(t0, a1, 22364);  // g_skyDisplayMode+0x14
        if (t0 == 0) {
            // 0x004e0f90
            charge(ctx, 5);
            a1 = 0x960000;
            a2 = 16;
            lw(a1, a1, 22352);  // g_skyDisplayMode+0x8
            if (a1 != a2) {
                // 0x004e0fac
                charge(ctx, 1);
                a2 = 1280;
            } else {
                // 0x004e0fa4
                charge(ctx, 2);
                a2 = 256;
            }
            // 0x004e0fb0
            charge(ctx, 2);
            a1 = 0x960000;
            sw(a2, a1, 22364);  // g_skyDisplayMode+0x14
        L_004e0fb8:
            charge(ctx, 4);
            a1 = 0x960000;
            lbu(a1, a1, 22371);  // 0x965763
            if (a1 == 0) {
                // 0x004e0fd0
                charge(ctx, 3);
                a1 = 0x960000;
                lbu(a1, a1, 22369);  // 0x965761
                mult(a1, v1, a1);
            } else {
                // 0x004e0fc8
                charge(ctx, 2);
                a1 = 0;
            }
            // 0x004e0fdc
            charge(ctx, 10);
            v1 = 0x960000;
            lbu(v1, v1, 22368);  // 0x965760
            mult(v1, a0, v1);
            at = 0x400000;
            at = at | 0x1;  // &0x400001
            v1 = addu(v1, a1);
            v0 = addu(v0, v1);
            at = sltu(v0, at);
            if (at != 0) {
                // 0x004e100c
                charge(ctx, 2);
                v0 = 1;
            } else {
                // 0x004e1004
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x004e0f5c
            charge(ctx, 5);
            a1 = 0x960000;
            a2 = 16;
            lw(a3, a1, 22352);  // g_skyDisplayMode+0x8
            if (a3 != a2) {
                // 0x004e0f70
                charge(ctx, 1);
                a1 = 32;
                goto L_004e0f74;
            }
            // 0x004e103c
            charge(ctx, 3);
            a1 = 256;
            if (t0 == a1) {
                // 0x004e1048
                charge(ctx, 2);
                a1 = 32;
                backedge(ctx);
            L_004e0f74:
                charge(ctx, 2);
                if (a3 != a1) {
                    goto L_004e0fb8;
                }
                // 0x004e0f7c
                charge(ctx, 3);
                a1 = 1280;
                if (t0 == a1) {
                    goto L_004e0fb8;
                }
                goto L_004e0f88;
            }
            backedge(ctx);
        L_004e0f88:
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004e0f00
        charge(ctx, 3);
        a2 = 16;
        if (a1 != a2) {
            // 0x004e0f0c
            charge(ctx, 1);
            a2 = 32;
            goto L_004e0f10;
        }
        // 0x004e1028
        charge(ctx, 3);
        a2 = 256;
        if (a3 == a2) {
            // 0x004e1034
            charge(ctx, 2);
            a2 = 32;
            backedge(ctx);
        L_004e0f10:
            charge(ctx, 2);
            if (a1 != a2) {
                goto L_004e0f4c;
            }
            // 0x004e0f18
            charge(ctx, 3);
            a1 = 1280;
            if (a3 == a1) {
                goto L_004e0f4c;
            }
            goto L_004e0f24;
        }
        backedge(ctx);
    L_004e0f24:
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004e1050 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// SkyCreateFBRaster -- creates the frame-buffer raster: a camera raster (RwRasterCreate sub_4CE0F0) of the frame-buffer
//   mode's size, depth and format | 2, its type byte 0x85, width and height rounded up to a power of two when not one,
//   then the raster extension's GS words: FBP from the frame-buffer base (gp 0x7CEA38, bits 16..21) and FBW (bits
//   24..29), log2 width / height in TW / TH; the raster
// 0x004E3100 SkyCreateFBRaster -- 540 bytes; frame 0x10: ra sp+0x0
void SkyCreateFBRaster(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e3100
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    lw(v1, v0, 22340);  // customMode+0x14
    v0 = 0x960000;
    lw(a0, v0, 22320);  // customMode
    v0 = 0x960000;
    lw(a1, v0, 22324);  // customMode+0x4
    v0 = 0x960000;
    lw(a2, v0, 22328);  // customMode+0x8
    a3 = v1 | 0x2;
    jal(ctx, 0x4E3128u, gen::fn_sub_4CE0F0_004ce0f0);
    v1 = 133;
    a1 = si(-1);
    sb(v1, v0, 32);
    lw(a0, v0, 12);
    v1 = a0;
    if (a0 != 0) {
        for (;;) {
            // 0x004e3148
            charge(ctx, 7);
            v1 = srl(v1, 1);
            a1 = addiu(a1, 1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e3164
        charge(ctx, 1);
    }
    // 0x004e3168
    charge(ctx, 6);
    v1 = 1;
    v1 = sllv(v1, a1);
    v1 = addiu(v1, -1);
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x004e31b4
        charge(ctx, 4);
        v1 = subu(a0, v1);
        v1 = sll(v1, 1);
        sw(v1, v0, 12);
        backedge(ctx);
    }
    // 0x004e3180
    charge(ctx, 4);
    lw(a0, v0, 16);
    a1 = si(-1);
    v1 = a0;
    if (a0 == 0) {
        // 0x004e31c4
        charge(ctx, 1);
        v1 = 1;
    } else {
        for (;;) {
            // 0x004e3190
            charge(ctx, 7);
            v1 = srl(v1, 1);
            a1 = addiu(a1, 1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e31ac
        charge(ctx, 2);
        v1 = 1;
    }
    // 0x004e31c8
    charge(ctx, 5);
    v1 = sllv(v1, a1);
    v1 = addiu(v1, -1);
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x004e3260
        charge(ctx, 4);
        v1 = subu(a0, v1);
        v1 = sll(v1, 1);
        sw(v1, v0, 16);
        backedge(ctx);
    }
    // 0x004e31dc
    charge(ctx, 24);
    lw(v1, gp, -16968);  // 0x7CEAA8
    v1 = addu(v0, v1);
    sw(zero, v1, 8);
    ld(a1, gp, -17080);  // 0x7CEA38
    lw(a0, v1, 8);
    a1 = dsra(a1, 16);
    a1 = a1 & 0x3F;
    a1 = dsll(a1, 14);
    a1 = dsll32(a1, 0);
    a1 = dsra32(a1, 0);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    ld(a1, gp, -17080);  // 0x7CEA38
    lw(a0, v1, 8);
    a1 = dsra(a1, 24);
    a1 = a1 & 0x3F;
    a1 = dsll(a1, 20);
    a1 = dsll32(a1, 0);
    a1 = dsra32(a1, 0);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    lw(a0, v0, 12);
    a2 = si(-1);
    if (a0 == 0) {
        // 0x004e3270
        charge(ctx, 1);
        lw(a0, v1, 8);
    } else {
        for (;;) {
            // 0x004e323c
            charge(ctx, 7);
            a0 = srl(a0, 1);
            a2 = addiu(a2, 1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e3258
        charge(ctx, 2);
        lw(a0, v1, 8);
    }
    // 0x004e3274
    charge(ctx, 8);
    a1 = a2 & 0xF;
    a1 = sll(a1, 26);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    sw(zero, v1, 12);
    lw(a0, v0, 16);
    a2 = si(-1);
    if (a0 != 0) {
        for (;;) {
            // 0x004e3294
            charge(ctx, 7);
            a0 = srl(a0, 1);
            a2 = addiu(a2, 1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004e32b0
    charge(ctx, 8);
    a0 = a2 & 0xF;
    a1 = sll(a0, 30);
    lw(a0, v1, 8);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    lw(a0, v0, 16);
    a2 = si(-1);
    if (a0 != 0) {
        for (;;) {
            // 0x004e32d0
            charge(ctx, 7);
            a0 = srl(a0, 1);
            a2 = addiu(a2, 1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e32ec
        charge(ctx, 1);
    }
    // 0x004e32f0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(a1, v1, 12);
    a0 = a2 & 0xF;
    a2 = sra(a0, 2);
    a0 = 1;
    a1 = a1 | a2;
    sw(a1, v1, 12);
    sb(a0, v1, 23);
    sb(zero, v1, 22);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// SkyCreateDBRaster -- creates the display (double) buffer raster: as SkyCreateFBRaster for the display mode (the flag
//   gp 0x7CEA18 set around the create), the GS base and width taken from the first display buffer's DISPFB (0x9649A0);
//   the raster
// 0x004E3320 SkyCreateDBRaster -- 556 bytes; frame 0x10: ra sp+0x0
void SkyCreateDBRaster(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e3320
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    sb(v0, gp, -17112);  // 0x7CEA18
    v0 = 0x960000;
    lw(v1, v0, 22364);  // g_skyDisplayMode+0x14
    v0 = 0x960000;
    lw(a0, v0, 22344);  // g_skyDisplayMode
    v0 = 0x960000;
    lw(a1, v0, 22348);  // g_skyDisplayMode+0x4
    v0 = 0x960000;
    lw(a2, v0, 22352);  // g_skyDisplayMode+0x8
    a3 = v1 | 0x2;
    jal(ctx, 0x4E3350u, gen::fn_sub_4CE0F0_004ce0f0);
    sb(zero, gp, -17112);  // 0x7CEA18
    v1 = 133;
    sb(v1, v0, 32);
    a1 = si(-1);
    lw(a0, v0, 12);
    v1 = a0;
    if (a0 != 0) {
        for (;;) {
            // 0x004e3374
            charge(ctx, 7);
            v1 = srl(v1, 1);
            a1 = addiu(a1, 1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004e3390
    charge(ctx, 6);
    v1 = 1;
    v1 = sllv(v1, a1);
    v1 = addiu(v1, -1);
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x004e33dc
        charge(ctx, 4);
        v1 = subu(a0, v1);
        v1 = sll(v1, 1);
        sw(v1, v0, 12);
        backedge(ctx);
    }
    // 0x004e33a8
    charge(ctx, 4);
    lw(a0, v0, 16);
    a1 = si(-1);
    v1 = a0;
    if (a0 == 0) {
        // 0x004e33ec
        charge(ctx, 1);
        v1 = 1;
    } else {
        for (;;) {
            // 0x004e33b8
            charge(ctx, 7);
            v1 = srl(v1, 1);
            a1 = addiu(a1, 1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e33d4
        charge(ctx, 2);
        v1 = 1;
    }
    // 0x004e33f0
    charge(ctx, 5);
    v1 = sllv(v1, a1);
    v1 = addiu(v1, -1);
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x004e3490
        charge(ctx, 4);
        v1 = subu(a0, v1);
        v1 = sll(v1, 1);
        sw(v1, v0, 16);
        backedge(ctx);
    }
    // 0x004e3404
    charge(ctx, 26);
    lw(v1, gp, -16968);  // 0x7CEAA8
    a1 = 0x960000;
    a0 = 0x960000;
    v1 = addu(v0, v1);
    sw(zero, v1, 8);
    ld(a2, a1, 18848);  // rwDMAFlipData+0x10
    lw(a1, v1, 8);
    a2 = dsra(a2, 9);
    a2 = a2 & 0x3F;
    a2 = dsll(a2, 14);
    a2 = dsll32(a2, 0);
    a2 = dsra32(a2, 0);
    a1 = a1 | a2;
    sw(a1, v1, 8);
    ld(a1, a0, 18848);  // rwDMAFlipData+0x10
    lw(a0, v1, 8);
    a1 = dsra(a1, 15);
    a1 = a1 & 0x1F;
    a1 = dsll(a1, 20);
    a1 = dsll32(a1, 0);
    a1 = dsra32(a1, 0);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    lw(a0, v0, 12);
    a3 = si(-1);
    if (a0 == 0) {
        // 0x004e34a0
        charge(ctx, 1);
        lw(a0, v1, 8);
    } else {
        for (;;) {
            // 0x004e346c
            charge(ctx, 7);
            a0 = srl(a0, 1);
            a3 = addiu(a3, 1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e3488
        charge(ctx, 2);
        lw(a0, v1, 8);
    }
    // 0x004e34a4
    charge(ctx, 8);
    a1 = a3 & 0xF;
    a1 = sll(a1, 26);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    sw(zero, v1, 12);
    lw(a0, v0, 16);
    a2 = si(-1);
    if (a0 != 0) {
        for (;;) {
            // 0x004e34c4
            charge(ctx, 7);
            a0 = srl(a0, 1);
            a2 = addiu(a2, 1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004e34e0
    charge(ctx, 8);
    a0 = a2 & 0xF;
    a1 = sll(a0, 30);
    lw(a0, v1, 8);
    a0 = a0 | a1;
    sw(a0, v1, 8);
    lw(a0, v0, 16);
    a2 = si(-1);
    if (a0 != 0) {
        for (;;) {
            // 0x004e3500
            charge(ctx, 7);
            a0 = srl(a0, 1);
            a2 = addiu(a2, 1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004e351c
        charge(ctx, 1);
    }
    // 0x004e3520 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(a1, v1, 12);
    a0 = a2 & 0xF;
    a2 = sra(a0, 2);
    a0 = 1;
    a1 = a1 | a2;
    sw(a1, v1, 12);
    sb(a0, v1, 23);
    sb(zero, v1, 22);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4E9680 [skySetSubRasterGlobals] -- remembers a raster ($a1) and its sub-rectangle (x +28, y +30, width +12,
//   height +16) in the sky driver's globals (0x7CEAF0, 0x965840..0x96584C); 1
// 0x004E9680 sub_4E9680 -- 60 bytes; leaf frame (no stack)
void sub_4E9680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x004e9680
    enter(ctx, 15);  // entry check point + this block's cycles
    sw(a1, gp, -16896);  // 0x7CEAF0
    a3 = 0x960000;
    lh(t0, a1, 28);
    a2 = 0x960000;
    a0 = 0x960000;
    v1 = 0x960000;
    v0 = 1;
    sw(t0, a3, 22592);  // 0x965840
    lh(a3, a1, 30);
    sw(a3, a2, 22596);  // 0x965844
    lw(a2, a1, 12);
    sw(a2, a0, 22600);  // 0x965848
    lw(a0, a1, 16);
    sw(a0, v1, 22604);  // 0x96584C
}

// sub_4EB7E0 [skyRasterQuantiseImage] -- fills a palettised raster from a 32-bit image: the quantiser (sub_4D3FC0) fed
//   the image, a 2^depth palette made, the indices written into the raster's pixels (sub_4D3800), the cache written back,
//   the palette written (sub_4EAC00), the quantiser freed; 1, or 0
// 0x004EB7E0 sub_4EB7E0 -- 224 bytes; frame 0x4460: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4EB7E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004eb7e0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4460);
    v1 = 1;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = 0;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, 20);
    s0 = a1;
    s3 = sllv(v1, v0);
    a0 = addiu(sp, 0x450);
    jal(ctx, 0x4EB810u, gen::fn_sub_4D3FC0_004d3fc0);
    if (v0 != 0) {
        // 0x004eb828
        charge(ctx, 31);
        v0 = 0x3F800000;
        a0 = addiu(sp, 0x450);
        mtc1(v0, f12);
        a1 = s0;
        jal(ctx, 0x4EB834u, gen::fn_sub_4D22F0_004d22f0);
        a1 = s3;
        a0 = addiu(sp, 0x50);
        a2 = addiu(sp, 0x450);
        jal(ctx, 0x4EB844u, gen::fn_sub_4D3300_004d3300);
        t1 = s0;
        lw(a1, s1, 24);
        lw(s0, s1, 4);
        a3 = 1;
        lw(a2, s1, 20);
        t0 = addiu(sp, 0x450);
        a0 = s0;
        jal(ctx, 0x4EB864u, gen::fn_sub_4D3800_004d3800);
        lw(v1, s1, 24);
        lw(v0, s1, 16);
        mult(v0, v1, v0);
        a0 = s0;
        v0 = addu(s0, v0);
        a1 = addiu(v0, 127);
        jal(ctx, 0x4EB880u, gen::fn_SyncDCache_00503a58);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x4EB88Cu, gen::fn_sub_4EAC00_004eac00);
        a0 = addiu(sp, 0x450);
        jal(ctx, 0x4EB894u, gen::fn_sub_4D41E0_004d41e0);
        s2 = 1;
        backedge(ctx);
    }
    // 0x004eb820
    charge(ctx, 2);
    v0 = s2;
    // 0x004eb8a4
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x4460);
}

// sub_4EBB40 [skyRasterSetImageDirect] -- copies an image into a direct-colour raster row by row: from a 32-bit image
//   or through a 4 / 8-bit image's palette, into 32-bit (alpha halved), 24-bit or 16-bit 1555 pixels by the raster's
//   format (5 / 6 / 1); the data cache written back per row for palettised images; 1, or 0 for another format
// 0x004EBB40 sub_4EBB40 -- 1132 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4EBB40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ebb40
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 32;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, 12);
    lw(s1, a0, 4);
    lw(s0, a1, 20);
    s3 = a1;
    if (v1 != v0) {
        // 0x004ebb7c
        charge(ctx, 3);
        v0 = 8;
        if (v1 != v0) {
            // 0x004ebb88
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                goto L_004ebb9c;
            }
            // 0x004ebb94
            charge(ctx, 2);
            v0 = 0;
            goto L_004ebf88;
        }
    L_004ebb9c:
        charge(ctx, 5);
        lw(v0, s4, 16);
        lw(s5, s3, 24);
        at = slt(0, v0);
        s2 = 0;
        if (at == 0) {
            goto L_004ebf80;
        }
        for (;;) {
            // 0x004ebbb0
            charge(ctx, 5);
            lbu(v1, s4, 35);
            v0 = 5;
            v1 = v1 & 0x6F;
            if (v1 == v0) {
                // 0x004ebce8
                charge(ctx, 5);
                lw(a0, s4, 12);
                v1 = s1;
                at = slt(0, a0);
                v0 = 0;
                if (at != 0) {
                    // 0x004ebcfc
                    charge(ctx, 1);
                    a1 = lui(0xFF00);
                    for (;;) {
                        // 0x004ebd00
                        charge(ctx, 26);
                        a0 = addu(s0, v0);
                        lbu(a0, a0, 0);
                        v0 = addiu(v0, 1);
                        a0 = sll(a0, 2);
                        a2 = addu(s5, a0);
                        lbu(t0, a2, 2);
                        lbu(a3, a2, 1);
                        lbu(a0, a2, 0);
                        t0 = sll(t0, 16);
                        a3 = sll(a3, 8);
                        lbu(a2, a2, 3);
                        a3 = t0 | a3;
                        a3 = a0 | a3;
                        a0 = sll(a2, 8);
                        a0 = addu(a0, a2);
                        a0 = sll(a0, 8);
                        a0 = addu(a0, a2);
                        a0 = sll(a0, 7);
                        a0 = addu(a0, a2);
                        a0 = a0 & a1;
                        a0 = a3 | a0;
                        sw(a0, v1, 0);
                        lw(a0, s4, 12);
                        a0 = slt(v0, a0);
                        v1 = addiu(v1, 4);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            L_004ebd68:
                charge(ctx, 13);
                lw(v0, s4, 24);
                a0 = s1;
                v0 = addu(s1, v0);
                a1 = addiu(v0, 127);
                jal(ctx, 0x4EBD74u, gen::fn_SyncDCache_00503a58);
                lw(v0, s4, 16);
                s2 = addiu(s2, 1);
                lw(a0, s4, 24);
                lw(v1, s3, 16);
                v0 = slt(s2, v0);
                s1 = addu(s1, a0);
                s0 = addu(s0, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                continue;
            }
            // 0x004ebbc4
            charge(ctx, 3);
            v0 = 6;
            if (v1 == v0) {
                // 0x004ebc70
                charge(ctx, 5);
                lw(a0, s4, 12);
                v1 = s1;
                at = slt(0, a0);
                v0 = 0;
                if (at != 0) {
                    // 0x004ebc84
                    charge(ctx, 1);
                    a3 = lui(0x8000);
                    for (;;) {
                        // 0x004ebc88
                        charge(ctx, 22);
                        a0 = addu(s0, v0);
                        lbu(a0, a0, 0);
                        v0 = addiu(v0, 1);
                        a0 = sll(a0, 2);
                        a0 = addu(s5, a0);
                        lbu(a2, a0, 0);
                        lbu(a1, a0, 1);
                        a2 = a2 | a3;
                        lbu(a0, a0, 2);
                        a1 = sll(a1, 8);
                        a1 = a2 | a1;
                        a0 = sll(a0, 16);
                        a1 = a0 | a1;
                        sb(a1, v1, 0);
                        a0 = srl(a1, 8);
                        sb(a0, v1, 1);
                        a0 = srl(a1, 16);
                        sb(a0, v1, 2);
                        lw(a0, s4, 12);
                        a0 = slt(v0, a0);
                        v1 = addiu(v1, 3);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ebce0
                    charge(ctx, 2);
                }
                goto L_004ebd68;
            }
            // 0x004ebbd0
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x004ebbdc
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_004ebbf0;
                }
                goto L_004ebbe4_9;
            }
        L_004ebbf0:
            charge(ctx, 5);
            lw(a0, s4, 12);
            v0 = s1;
            at = slt(0, a0);
            v1 = 0;
            if (at != 0) {
                // 0x004ebc04
                charge(ctx, 1);
                for (;;) {
                    // 0x004ebc08
                    charge(ctx, 24);
                    a0 = addu(s0, v1);
                    lbu(a0, a0, 0);
                    v1 = addiu(v1, 1);
                    a0 = sll(a0, 2);
                    a0 = addu(s5, a0);
                    lbu(a3, a0, 2);
                    lbu(a2, a0, 1);
                    lbu(a1, a0, 0);
                    a3 = sll(a3, 7);
                    a2 = sll(a2, 2);
                    a3 = a3 & 0x7C00;
                    lbu(a0, a0, 3);
                    a2 = a2 & 0x3E0;
                    a1 = srl(a1, 3);
                    a2 = a3 | a2;
                    a1 = a1 | a2;
                    a0 = sll(a0, 8);
                    a0 = a0 & 0x8000;
                    a0 = a0 | a1;
                    sh(a0, v0, 0);
                    lw(a0, s4, 12);
                    a0 = slt(v1, a0);
                    v0 = addiu(v0, 2);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ebc68
                charge(ctx, 2);
            }
            goto L_004ebd68;
        }
        // 0x004ebd9c
        charge(ctx, 2);
        goto L_004ebf80;
    }
    // 0x004ebdac
    charge(ctx, 4);
    lw(v0, s4, 16);
    at = slt(0, v0);
    t0 = 0;
    if (at != 0) {
        // 0x004ebdbc
        charge(ctx, 5);
        v1 = lui(0x8000);
        v0 = lui(0xFF00);
        a0 = 1;
        a1 = 6;
        a2 = 5;
        for (;;) {
            // 0x004ebdd0
            charge(ctx, 4);
            lbu(a3, s4, 35);
            a3 = a3 & 0x6F;
            t2 = s0;
            if (a3 == a2) {
                // 0x004ebee8
                charge(ctx, 5);
                lw(t3, s4, 12);
                t1 = s1;
                at = slt(0, t3);
                a3 = 0;
                if (at != 0) {
                    // 0x004ebefc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004ebf00
                        charge(ctx, 23);
                        lbu(t6, t2, 2);
                        lbu(t5, t2, 1);
                        a3 = addiu(a3, 1);
                        lbu(t3, t2, 0);
                        lbu(t4, t2, 3);
                        t6 = sll(t6, 16);
                        t5 = sll(t5, 8);
                        t5 = t6 | t5;
                        t5 = t3 | t5;
                        t2 = addiu(t2, 4);
                        t3 = sll(t4, 8);
                        t3 = addu(t3, t4);
                        t3 = sll(t3, 8);
                        t3 = addu(t3, t4);
                        t3 = sll(t3, 7);
                        t3 = addu(t3, t4);
                        t3 = t3 & v0;
                        t3 = t5 | t3;
                        sw(t3, t1, 0);
                        lw(t3, s4, 12);
                        t3 = slt(a3, t3);
                        t1 = addiu(t1, 4);
                        if (t3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ebf5c
                    charge(ctx, 1);
                }
            L_004ebf60:
                charge(ctx, 8);
                lw(a3, s4, 16);
                lw(t2, s4, 24);
                t0 = addiu(t0, 1);
                lw(t1, s3, 16);
                a3 = slt(t0, a3);
                s1 = addu(s1, t2);
                s0 = addu(s0, t1);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
                continue;
            }
            // 0x004ebde0
            charge(ctx, 2);
            if (a3 == a1) {
                // 0x004ebe78
                charge(ctx, 5);
                lw(t3, s4, 12);
                t1 = s1;
                at = slt(0, t3);
                a3 = 0;
                if (at != 0) {
                    // 0x004ebe8c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004ebe90
                        charge(ctx, 19);
                        lbu(t5, t2, 0);
                        lbu(t4, t2, 1);
                        a3 = addiu(a3, 1);
                        lbu(t3, t2, 2);
                        t5 = t5 | v1;
                        t4 = sll(t4, 8);
                        t4 = t5 | t4;
                        t3 = sll(t3, 16);
                        t4 = t3 | t4;
                        t2 = addiu(t2, 4);
                        sb(t4, t1, 0);
                        t3 = srl(t4, 8);
                        sb(t3, t1, 1);
                        t3 = srl(t4, 16);
                        sb(t3, t1, 2);
                        lw(t3, s4, 12);
                        t3 = slt(a3, t3);
                        t1 = addiu(t1, 3);
                        if (t3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ebedc
                    charge(ctx, 2);
                }
                goto L_004ebf60;
            }
            // 0x004ebde8
            charge(ctx, 2);
            if (a3 != a0) {
                // 0x004ebdf0
                charge(ctx, 2);
                if (a3 == 0) {
                    goto L_004ebe00;
                }
                goto L_004ebdf8_30;
            }
        L_004ebe00:
            charge(ctx, 5);
            lw(t3, s4, 12);
            t1 = s1;
            at = slt(0, t3);
            a3 = 0;
            if (at != 0) {
                // 0x004ebe14
                charge(ctx, 1);
                for (;;) {
                    // 0x004ebe18
                    charge(ctx, 21);
                    lbu(t6, t2, 2);
                    lbu(t5, t2, 1);
                    a3 = addiu(a3, 1);
                    lbu(t4, t2, 0);
                    lbu(t3, t2, 3);
                    t6 = sll(t6, 7);
                    t5 = sll(t5, 2);
                    t6 = t6 & 0x7C00;
                    t5 = t5 & 0x3E0;
                    t4 = srl(t4, 3);
                    t5 = t6 | t5;
                    t3 = sll(t3, 8);
                    t4 = t4 | t5;
                    t3 = t3 & 0x8000;
                    t3 = t3 | t4;
                    t2 = addiu(t2, 4);
                    sh(t3, t1, 0);
                    lw(t3, s4, 12);
                    t3 = slt(a3, t3);
                    t1 = addiu(t1, 2);
                    if (t3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ebe6c
                charge(ctx, 2);
            }
            goto L_004ebf60;
        }
        goto L_004ebf80;
    }
L_004ebf80:
    charge(ctx, 2);
    v0 = 1;
L_004ebf88:
    charge(ctx, 1);
    ld(ra, sp, 0x60);
    // 0x004ebf8c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004ebbe4_9:
    charge(ctx, 2);
    v0 = 0;
    // 0x004ebda4
    charge(ctx, 2);
    ld(ra, sp, 0x60);
    // 0x004ebf8c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004ebdf8_30:
    charge(ctx, 2);
    v0 = 0;
    goto L_004ebf88;
}

}  // namespace p3fes::game
