// Slice render_rw7: RenderWare, seventh pass -- RpMatFX's plugin, RpMorph, the PDS registry, the PTank data layout and
// object set-ups, RpRandom, RpSpline, RpUserData, the pipeline-id streams, the bin-mesh / native-data streams, the
// tri-strip edge records and Rt2d's font layer (the group overview, RpRandom's state and the record layouts are in
// game/include/p3fes/game/render_rw7.h). Every body started as p3fes_handgen's output and keeps the recompiled body's
// registers, frame, spills, $ra links, cycle charges and check points statement for statement
// (game/include/p3fes/game/hg_cpu.h); what was added is the role of each function, the role of its main blocks, the
// names of the record offsets (rw4:: .. rw7::) and the labels of the RW globals. sub_* keep their
// symbols/functions.json names; proposed names are in brackets (symbols/deltas/render_rw7.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw7.h"

namespace p3fes::recomp_gen {
void fn_RpPDSGetPipe_0046a890(p3fes::EEContext&);
void fn_RpRandomSeedMT_00488c70(p3fes::EEContext&);
void fn_RpRandomSeed_00488dd0(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_matfxSetSectorPipeline_00469d00(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_name__C9type_info_0_0048ef10(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_0049ff00(p3fes::EEContext&);
void fn_sub_464280_00464280(p3fes::EEContext&);
void fn_sub_4643B0_004643b0(p3fes::EEContext&);
void fn_sub_464540_00464540(p3fes::EEContext&);
void fn_sub_467590_00467590(p3fes::EEContext&);
void fn_sub_467600_00467600(p3fes::EEContext&);
void fn_sub_4676A0_004676a0(p3fes::EEContext&);
void fn_sub_4676C0_004676c0(p3fes::EEContext&);
void fn_sub_4677F0_004677f0(p3fes::EEContext&);
void fn_sub_467B40_00467b40(p3fes::EEContext&);
void fn_sub_467C20_00467c20(p3fes::EEContext&);
void fn_sub_468350_00468350(p3fes::EEContext&);
void fn_sub_4684C0_004684c0(p3fes::EEContext&);
void fn_sub_4684E0_004684e0(p3fes::EEContext&);
void fn_sub_468500_00468500(p3fes::EEContext&);
void fn_sub_468530_00468530(p3fes::EEContext&);
void fn_sub_4685D0_004685d0(p3fes::EEContext&);
void fn_sub_4685F0_004685f0(p3fes::EEContext&);
void fn_sub_468610_00468610(p3fes::EEContext&);
void fn_sub_468630_00468630(p3fes::EEContext&);
void fn_sub_468660_00468660(p3fes::EEContext&);
void fn_sub_468690_00468690(p3fes::EEContext&);
void fn_sub_468700_00468700(p3fes::EEContext&);
void fn_sub_468720_00468720(p3fes::EEContext&);
void fn_sub_468C50_00468c50(p3fes::EEContext&);
void fn_sub_468E30_00468e30(p3fes::EEContext&);
void fn_sub_469030_00469030(p3fes::EEContext&);
void fn_sub_469060_00469060(p3fes::EEContext&);
void fn_sub_469280_00469280(p3fes::EEContext&);
void fn_sub_4692E0_004692e0(p3fes::EEContext&);
void fn_sub_469340_00469340(p3fes::EEContext&);
void fn_sub_4693A0_004693a0(p3fes::EEContext&);
void fn_sub_469400_00469400(p3fes::EEContext&);
void fn_sub_4694B0_004694b0(p3fes::EEContext&);
void fn_sub_469590_00469590(p3fes::EEContext&);
void fn_sub_4695F0_004695f0(p3fes::EEContext&);
void fn_sub_469650_00469650(p3fes::EEContext&);
void fn_sub_4696B0_004696b0(p3fes::EEContext&);
void fn_sub_469710_00469710(p3fes::EEContext&);
void fn_sub_4698E0_004698e0(p3fes::EEContext&);
void fn_sub_469940_00469940(p3fes::EEContext&);
void fn_sub_4699B0_004699b0(p3fes::EEContext&);
void fn_sub_469A10_00469a10(p3fes::EEContext&);
void fn_sub_469AA0_00469aa0(p3fes::EEContext&);
void fn_sub_469B50_00469b50(p3fes::EEContext&);
void fn_sub_469BC0_00469bc0(p3fes::EEContext&);
void fn_sub_469CE0_00469ce0(p3fes::EEContext&);
void fn_sub_469CF0_00469cf0(p3fes::EEContext&);
void fn_sub_469DC0_00469dc0(p3fes::EEContext&);
void fn_sub_469DD0_00469dd0(p3fes::EEContext&);
void fn_sub_469DF0_00469df0(p3fes::EEContext&);
void fn_sub_469E10_00469e10(p3fes::EEContext&);
void fn_sub_469E30_00469e30(p3fes::EEContext&);
void fn_sub_469FE0_00469fe0(p3fes::EEContext&);
void fn_sub_46A040_0046a040(p3fes::EEContext&);
void fn_sub_46A0F0_0046a0f0(p3fes::EEContext&);
void fn_sub_46A230_0046a230(p3fes::EEContext&);
void fn_sub_46A3C0_0046a3c0(p3fes::EEContext&);
void fn_sub_46A400_0046a400(p3fes::EEContext&);
void fn_sub_46A440_0046a440(p3fes::EEContext&);
void fn_sub_46A470_0046a470(p3fes::EEContext&);
void fn_sub_46A530_0046a530(p3fes::EEContext&);
void fn_sub_46A660_0046a660(p3fes::EEContext&);
void fn_sub_46A6C0_0046a6c0(p3fes::EEContext&);
void fn_sub_46A6F0_0046a6f0(p3fes::EEContext&);
void fn_sub_46A720_0046a720(p3fes::EEContext&);
void fn_sub_46A750_0046a750(p3fes::EEContext&);
void fn_sub_46A970_0046a970(p3fes::EEContext&);
void fn_sub_46A9E0_0046a9e0(p3fes::EEContext&);
void fn_sub_4734B0_004734b0(p3fes::EEContext&);
void fn_sub_473590_00473590(p3fes::EEContext&);
void fn_sub_473600_00473600(p3fes::EEContext&);
void fn_sub_473B10_00473b10(p3fes::EEContext&);
void fn_sub_4753D0_004753d0(p3fes::EEContext&);
void fn_sub_475540_00475540(p3fes::EEContext&);
void fn_sub_475C20_00475c20(p3fes::EEContext&);
void fn_sub_477050_00477050(p3fes::EEContext&);
void fn_sub_478CC0_00478cc0(p3fes::EEContext&);
void fn_sub_47A050_0047a050(p3fes::EEContext&);
void fn_sub_47ABF0_0047abf0(p3fes::EEContext&);
void fn_sub_488CD0_00488cd0(p3fes::EEContext&);
void fn_sub_488D40_00488d40(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_488FE0_00488fe0(p3fes::EEContext&);
void fn_sub_48AD20_0048ad20(p3fes::EEContext&);
void fn_sub_48AF80_0048af80(p3fes::EEContext&);
void fn_sub_48B910_0048b910(p3fes::EEContext&);
void fn_sub_48CF00_0048cf00(p3fes::EEContext&);
void fn_sub_48CFA0_0048cfa0(p3fes::EEContext&);
void fn_sub_48D200_0048d200(p3fes::EEContext&);
void fn_sub_48D370_0048d370(p3fes::EEContext&);
void fn_sub_48D480_0048d480(p3fes::EEContext&);
void fn_sub_48DCF0_0048dcf0(p3fes::EEContext&);
void fn_sub_48DD30_0048dd30(p3fes::EEContext&);
void fn_sub_48DD50_0048dd50(p3fes::EEContext&);
void fn_sub_48DD70_0048dd70(p3fes::EEContext&);
void fn_sub_48DE50_0048de50(p3fes::EEContext&);
void fn_sub_48E020_0048e020(p3fes::EEContext&);
void fn_sub_48E2D0_0048e2d0(p3fes::EEContext&);
void fn_sub_48E4F0_0048e4f0(p3fes::EEContext&);
void fn_sub_48E610_0048e610(p3fes::EEContext&);
void fn_sub_48E750_0048e750(p3fes::EEContext&);
void fn_sub_48E890_0048e890(p3fes::EEContext&);
void fn_sub_48EA90_0048ea90(p3fes::EEContext&);
void fn_sub_48EAB0_0048eab0(p3fes::EEContext&);
void fn_sub_48EB50_0048eb50(p3fes::EEContext&);
void fn_sub_48EC20_0048ec20(p3fes::EEContext&);
void fn_sub_48ECF0_0048ecf0(p3fes::EEContext&);
void fn_sub_48ED20_0048ed20(p3fes::EEContext&);
void fn_sub_48EDE0_0048ede0(p3fes::EEContext&);
void fn_sub_48EE30_0048ee30(p3fes::EEContext&);
void fn_sub_48EE70_0048ee70(p3fes::EEContext&);
void fn_sub_48EF20_0048ef20(p3fes::EEContext&);
void fn_sub_48EF30_0048ef30(p3fes::EEContext&);
void fn_sub_48EF40_0048ef40(p3fes::EEContext&);
void fn_sub_48EF60_0048ef60(p3fes::EEContext&);
void fn_sub_48EFA0_0048efa0(p3fes::EEContext&);
void fn_sub_48EFC0_0048efc0(p3fes::EEContext&);
void fn_sub_48EFE0_0048efe0(p3fes::EEContext&);
void fn_sub_48F340_0048f340(p3fes::EEContext&);
void fn_sub_48F3C0_0048f3c0(p3fes::EEContext&);
void fn_sub_48F430_0048f430(p3fes::EEContext&);
void fn_sub_48F460_0048f460(p3fes::EEContext&);
void fn_sub_48F4E0_0048f4e0(p3fes::EEContext&);
void fn_sub_48F550_0048f550(p3fes::EEContext&);
void fn_sub_4915C0_004915c0(p3fes::EEContext&);
void fn_sub_492C30_00492c30(p3fes::EEContext&);
void fn_sub_492C60_00492c60(p3fes::EEContext&);
void fn_sub_492C90_00492c90(p3fes::EEContext&);
void fn_sub_492CE0_00492ce0(p3fes::EEContext&);
void fn_sub_493C50_00493c50(p3fes::EEContext&);
void fn_sub_493C80_00493c80(p3fes::EEContext&);
void fn_sub_494520_00494520(p3fes::EEContext&);
void fn_sub_494580_00494580(p3fes::EEContext&);
void fn_sub_4947C0_004947c0(p3fes::EEContext&);
void fn_sub_494DB0_00494db0(p3fes::EEContext&);
void fn_sub_494DE0_00494de0(p3fes::EEContext&);
void fn_sub_494E10_00494e10(p3fes::EEContext&);
void fn_sub_494E30_00494e30(p3fes::EEContext&);
void fn_sub_495320_00495320(p3fes::EEContext&);
void fn_sub_495480_00495480(p3fes::EEContext&);
void fn_sub_495C80_00495c80(p3fes::EEContext&);
void fn_sub_495FB0_00495fb0(p3fes::EEContext&);
void fn_sub_496230_00496230(p3fes::EEContext&);
void fn_sub_4964F0_004964f0(p3fes::EEContext&);
void fn_sub_496580_00496580(p3fes::EEContext&);
void fn_sub_496AD0_00496ad0(p3fes::EEContext&);
void fn_sub_496BE0_00496be0(p3fes::EEContext&);
void fn_sub_496CD0_00496cd0(p3fes::EEContext&);
void fn_sub_498E40_00498e40(p3fes::EEContext&);
void fn_sub_499250_00499250(p3fes::EEContext&);
void fn_sub_499280_00499280(p3fes::EEContext&);
void fn_sub_4992D0_004992d0(p3fes::EEContext&);
void fn_sub_499720_00499720(p3fes::EEContext&);
void fn_sub_499850_00499850(p3fes::EEContext&);
void fn_sub_49A920_0049a920(p3fes::EEContext&);
void fn_sub_49A950_0049a950(p3fes::EEContext&);
void fn_sub_49A980_0049a980(p3fes::EEContext&);
void fn_sub_49AEB0_0049aeb0(p3fes::EEContext&);
void fn_sub_49AF20_0049af20(p3fes::EEContext&);
void fn_sub_49BC50_0049bc50(p3fes::EEContext&);
void fn_sub_49BC70_0049bc70(p3fes::EEContext&);
void fn_sub_49BCC0_0049bcc0(p3fes::EEContext&);
void fn_sub_49BD10_0049bd10(p3fes::EEContext&);
void fn_sub_49BD60_0049bd60(p3fes::EEContext&);
void fn_sub_49BD70_0049bd70(p3fes::EEContext&);
void fn_sub_49BDC0_0049bdc0(p3fes::EEContext&);
void fn_sub_49BE20_0049be20(p3fes::EEContext&);
void fn_sub_49BE50_0049be50(p3fes::EEContext&);
void fn_sub_49C790_0049c790(p3fes::EEContext&);
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);
void fn_sub_49E6C0_0049e6c0(p3fes::EEContext&);
void fn_sub_49E780_0049e780(p3fes::EEContext&);
void fn_sub_49ECD0_0049ecd0(p3fes::EEContext&);
void fn_sub_49F340_0049f340(p3fes::EEContext&);
void fn_sub_49F500_0049f500(p3fes::EEContext&);
void fn_sub_49FE40_0049fe40(p3fes::EEContext&);
void fn_sub_4A0430_004a0430(p3fes::EEContext&);
void fn_sub_4A5100_004a5100(p3fes::EEContext&);
void fn_sub_4A5470_004a5470(p3fes::EEContext&);
void fn_sub_4A5DD0_004a5dd0(p3fes::EEContext&);
void fn_sub_4A6200_004a6200(p3fes::EEContext&);
void fn_sub_4A62E0_004a62e0(p3fes::EEContext&);
void fn_sub_4A6360_004a6360(p3fes::EEContext&);
void fn_sub_4A6530_004a6530(p3fes::EEContext&);
void fn_sub_4A7620_004a7620(p3fes::EEContext&);
void fn_sub_4A91F0_004a91f0(p3fes::EEContext&);
void fn_sub_4A9330_004a9330(p3fes::EEContext&);
void fn_sub_4A9490_004a9490(p3fes::EEContext&);
void fn_sub_4A9550_004a9550(p3fes::EEContext&);
void fn_sub_4A9560_004a9560(p3fes::EEContext&);
void fn_sub_4A96B0_004a96b0(p3fes::EEContext&);
void fn_sub_4A9BD0_004a9bd0(p3fes::EEContext&);
void fn_sub_4A9BE0_004a9be0(p3fes::EEContext&);
void fn_sub_4AC390_004ac390(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C1750_004c1750(p3fes::EEContext&);
void fn_sub_4C17F0_004c17f0(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1CD0_004c1cd0(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);
void fn_sub_4C3B50_004c3b50(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C47E0_004c47e0(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C53F0_004c53f0(p3fes::EEContext&);
void fn_sub_4C5A50_004c5a50(p3fes::EEContext&);
void fn_sub_4C5C30_004c5c30(p3fes::EEContext&);
void fn_sub_4C64B0_004c64b0(p3fes::EEContext&);
void fn_sub_4C6560_004c6560(p3fes::EEContext&);
void fn_sub_4C6970_004c6970(p3fes::EEContext&);
void fn_sub_4C81D0_004c81d0(p3fes::EEContext&);
void fn_sub_4C8240_004c8240(p3fes::EEContext&);
void fn_sub_4C83C0_004c83c0(p3fes::EEContext&);
void fn_sub_4CA000_004ca000(p3fes::EEContext&);
void fn_sub_4CA520_004ca520(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4D0C30_004d0c30(p3fes::EEContext&);
void fn_sub_4D0D10_004d0d10(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D1110_004d1110(p3fes::EEContext&);
void fn_sub_4D1170_004d1170(p3fes::EEContext&);
void fn_sub_4D11F0_004d11f0(p3fes::EEContext&);
void fn_sub_4F2AD0_004f2ad0(p3fes::EEContext&);
void fn_sub_4F3010_004f3010(p3fes::EEContext&);
void fn_worldForAllLights_00499c20(p3fes::EEContext&);
void fn_worldSectorGetWorld_0049a170(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rw4;
using namespace rw5;
using namespace rw6;
using namespace rw7;

namespace gen = ::p3fes::recomp_gen;

// sub_4643B0 [prt122CreateEntry] -- allocates entry $a1's 20-byte records of a plugin-0x122 object: n records zeroed with their last word -1, the count
// ($a0 = the object, $a1 = the entry, $a2 = n) The entry is {count, records} at object +4 + 8 x entry; error
// 0x80000013 (domain 0x122) and 0 when the allocation fails, else the object.
// 0x004643B0 sub_4643B0 -- 392 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4643B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004643b0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    lw(a0, a0, 4);
    v0 = sll(s0, 2);
    a2 = sll(a1, 3);
    v1 = addu(v0, s0);
    v0 = 0x30000;
    s3 = sll(v1, 2);
    a1 = v0 | 0x122;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    s2 = addu(a0, a2);
    a0 = s3;
    jalr(ctx, 0x4643F8u, v0.u());
    sw(v0, s2, 4);
    lw(a0, s2, 4);
    if (a0 == 0) {
        // 0x004644f4
        charge(ctx, 10);
        v0 = 290;
        a1 = s3;
        sw(v0, sp, 0x58);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x464504u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x464510u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x00464410
        charge(ctx, 6);
        a2 = s3;
        a1 = 0;
        jal(ctx, 0x464414u, gen::fn_memset_00521408);
        at = sltu(0, s0);
        a1 = 0;
        if (at != 0) {
            // 0x00464428
            charge(ctx, 3);
            at = sltiu(s0, 9);
            v1 = addiu(s0, -8);
            if (at == 0) {
                // 0x00464434
                charge(ctx, 2);
                a0 = 0;
                v0 = si(-1);
                for (;;) {
                    // 0x0046443c
                    charge(ctx, 28);
                    lw(a3, s2, 4);
                    a1 = addiu(a1, 8);
                    a2 = sltu(a1, v1);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 16);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 36);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 56);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 76);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 96);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 116);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 136);
                    lw(a3, s2, 4);
                    a3 = addu(a3, a0);
                    sw(v0, a3, 156);
                    a0 = addiu(a0, 160);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004644ac
                charge(ctx, 1);
            }
            // 0x004644b0
            charge(ctx, 3);
            at = sltu(a1, s0);
            if (at != 0) {
                // 0x004644bc
                charge(ctx, 4);
                v0 = sll(a1, 2);
                a0 = si(-1);
                v0 = addu(v0, a1);
                a2 = sll(v0, 2);
                for (;;) {
                    // 0x004644cc
                    charge(ctx, 7);
                    lw(v1, s2, 4);
                    a1 = addiu(a1, 1);
                    v0 = sltu(a1, s0);
                    v1 = addu(v1, a2);
                    sw(a0, v1, 16);
                    a2 = addiu(a2, 20);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004644e8
        charge(ctx, 3);
        sw(s0, s2, 0);
        v0 = s1;
    }
    // 0x0046451c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_464540 [prt122StreamRead] -- reads a plugin-0x122 chunk (the resource manager's loader): a 4-word header, the object (sub_464280), each entry's 20-byte records
// A struct chunk (type 1), then four words: a count that must not exceed 256 (else error 0x80000004), two more, the
// entry count; per entry its record count and, when non-zero, the records (sub_4643B0) as four reals and a word.
// The object, or 0.
// 0x00464540 sub_464540 -- 536 bytes; frame 0xA0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_464540(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00464540
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    a1 = 1;
    sd(ra, sp, 0x60);
    a2 = addiu(sp, 0x9C);
    sq(s5, sp, 0x50);
    a3 = addiu(sp, 0x98);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x46456Cu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 != 0) {
        // 0x00464584
        charge(ctx, 6);
        a0 = s5;
        a1 = addiu(sp, 0x94);
        a2 = 4;
        jal(ctx, 0x46458Cu, gen::fn_sub_4C1910_004c1910);
        if (v0 != 0) {
            // 0x004645a4
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(sp, 0x90);
            a2 = 4;
            jal(ctx, 0x4645ACu, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                backedge(ctx);
                goto L_0046459c;
            }
            // 0x004645bc
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(sp, 0x8C);
            a2 = 4;
            jal(ctx, 0x4645C4u, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                backedge(ctx);
                goto L_0046459c;
            }
            // 0x004645d4
            charge(ctx, 6);
            a0 = s5;
            a1 = addiu(sp, 0x88);
            a2 = 4;
            jal(ctx, 0x4645DCu, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                backedge(ctx);
                goto L_0046459c;
            }
            // 0x004645ec
            charge(ctx, 4);
            lw(v0, sp, 0x94);
            at = sltiu(v0, 257);
            if (at == 0) {
                // 0x00464628
                charge(ctx, 10);
                v1 = 290;
                v0 = lui(0x8000);
                sw(v1, sp, 0x78);
                a0 = v0 | 0x4;
                jal(ctx, 0x464634u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x7C);
                a0 = addiu(sp, 0x78);
                jal(ctx, 0x464640u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x004645fc
                charge(ctx, 5);
                link(ctx, 0x4645FCu);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0x8C);
                call(ctx, gen::fn_sub_464280_00464280);
                s4 = v0;
                if (s4 == 0) {
                    // 0x00464650
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00464610
                    charge(ctx, 4);
                    lw(v0, sp, 0x8C);
                    v0 = sltu(0, v0);
                    s3 = 0;
                    if (v0 != 0) {
                        // 0x00464658
                        charge(ctx, 1);
                        s0 = 0;
                        for (;;) {
                            // 0x0046465c
                            charge(ctx, 6);
                            a0 = s5;
                            a1 = addiu(sp, 0x84);
                            a2 = 4;
                            jal(ctx, 0x464664u, gen::fn_sub_4C1910_004c1910);
                            if (v0 == 0) {
                                goto L_00464674_15;
                            }
                            // 0x0046467c
                            charge(ctx, 3);
                            lw(a2, sp, 0x84);
                            if (a2 != 0) {
                                // 0x004646a4
                                charge(ctx, 5);
                                a0 = s4;
                                a1 = s3;
                                jal(ctx, 0x4646A8u, gen::fn_sub_4643B0_004643b0);
                                if (v0 == 0) {
                                    break;
                                }
                                // 0x004646b8
                                charge(ctx, 7);
                                lw(v1, s4, 4);
                                lw(v0, sp, 0x84);
                                v1 = addu(v1, s0);
                                lw(s2, v1, 4);
                                at = sltu(0, v0);
                                s1 = 0;
                                if (at == 0) {
                                    backedge(ctx);
                                    goto L_00464688;
                                }
                                // 0x004646d4
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004646d8
                                    charge(ctx, 6);
                                    a0 = s5;
                                    a1 = s2;
                                    a2 = 16;
                                    jal(ctx, 0x4646E0u, gen::fn_sub_4C18B0_004c18b0);
                                    if (v0 == 0) {
                                        goto L_00464730;
                                    }
                                    // 0x004646f0
                                    charge(ctx, 6);
                                    a0 = s5;
                                    a1 = addiu(s2, 16);
                                    a2 = 4;
                                    jal(ctx, 0x4646F8u, gen::fn_sub_4C1910_004c1910);
                                    if (v0 == 0) {
                                        goto L_00464730;
                                    }
                                    // 0x00464708
                                    charge(ctx, 5);
                                    lw(v0, sp, 0x84);
                                    s1 = addiu(s1, 1);
                                    v0 = sltu(s1, v0);
                                    s2 = addiu(s2, 20);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x0046471c
                                charge(ctx, 2);
                                backedge(ctx);
                                goto L_00464688;
                            }
                        L_00464688:
                            charge(ctx, 5);
                            lw(v0, sp, 0x8C);
                            s3 = addiu(s3, 1);
                            v0 = sltu(s3, v0);
                            s0 = addiu(s0, 8);
                            if (v0 == 0) {
                                goto L_0046469c_18;
                            }
                            backedge(ctx);
                        }
                        // 0x00464728
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x00464734 (the shared epilogue, written out on this path)
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
                L_00464620:
                    charge(ctx, 2);
                    v0 = s4;
                }
            }
            // 0x00464734 (the shared epilogue, written out on this path)
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
    L_0046459c:
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0046457c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00464734 (the shared epilogue, written out on this path)
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
L_00464674_15:
    charge(ctx, 2);
    v0 = 0;
    // 0x00464734 (the shared epilogue, written out on this path)
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
L_0046469c_18:
    charge(ctx, 2);
    backedge(ctx);
    goto L_00464620;
L_00464730:
    charge(ctx, 1);
    v0 = 0;
    // 0x00464734 (the shared epilogue, written out on this path)
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


// sub_467590 [matfxClose] -- RpMatFX's engine close: the open count down (at 0 the platform close sub_469CF0), the 144-byte free list destroyed
// Returns $a0 (the engine instance).
// 0x00467590 sub_467590 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_467590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00467590
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    lw(v1, v1, -15364);  // 0x95C3FC (RpMatFX's open count)
    s0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, v0, -15364);  // 0x95C3FC (RpMatFX's open count)
    if (v1 == 0) {
        // 0x004675e0
        charge(ctx, 4);
        jal(ctx, 0x4675E0u, gen::fn_sub_469CF0_00469cf0);
        backedge(ctx);
    }
    // 0x004675b8
    charge(ctx, 4);
    v0 = 0x960000;
    lw(a0, v0, -15360);  // 0x95C400 (RpMatFX's 144-byte free list)
    if (a0 != 0) {
        // 0x004675c8
        charge(ctx, 4);
        jal(ctx, 0x4675C8u, gen::fn_sub_4C3C30_004c3c30);
        v0 = 0x960000;
        sw(zero, v0, -15360);  // 0x95C400 (RpMatFX's 144-byte free list)
    }
    // 0x004675d8
    charge(ctx, 2);
    v0 = s0;
    // 0x004675f0
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_467600 [matfxOpen] -- RpMatFX's engine open: on the first open the 144-byte effect free list (sub_4C3B60, static block 0x95C410) and the platform open
// Fails (0) when the free list cannot be created or the platform open (sub_469CE0) declines; else the open count up, $a0.
// 0x00467600 sub_467600 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_467600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00467600
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -15364);  // 0x95C3FC (RpMatFX's open count)
    s0 = a0;
    if (v0 == 0) {
        // 0x00467638
        charge(ctx, 12);
        lw(a1, gp, -20944);  // 0x7CDB20 (RpMatFX's free-list block parameters)
        t0 = 0x960000;
        lw(a3, gp, -20940);  // 0x7CDB24 (RpMatFX's free-list block parameters (2))
        v0 = 0x40000;
        a0 = 144;
        a2 = 16;
        t0 = addiu(t0, -15344);  // &0x95C410 (RpMatFX's free-list static block)
        t1 = v0 | 0x120;
        jal(ctx, 0x467654u, gen::fn_sub_4C3B60_004c3b60);
        v1 = 0x960000;
        sw(v0, v1, -15360);  // 0x95C400 (RpMatFX's 144-byte free list)
        if (v0 == 0) {
            // 0x00467680
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00467668
            charge(ctx, 4);
            jal(ctx, 0x467668u, gen::fn_sub_469CE0_00469ce0);
            if (v0 != 0) {
                backedge(ctx);
                goto L_0046761c;
            }
            // 0x00467678
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x00467684 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0046761c:
    charge(ctx, 7);
    v1 = 0x960000;
    v0 = s0;
    lw(a0, v1, -15364);  // 0x95C3FC (RpMatFX's open count)
    v1 = 0x960000;
    a0 = addiu(a0, 1);
    sw(a0, v1, -15364);  // 0x95C3FC (RpMatFX's open count)
    // 0x00467684 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4676A0 [matfxMaterialConstructor] -- the RpMatFX material extension constructor: no effects (the pointer at material + offset = 0); the material
// 0x004676A0 sub_4676A0 -- 20 bytes; leaf frame (no stack)
void sub_4676A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004676a0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_4676C0 [matfxEffectsReset] -- resets a material's RpMatFX effects record: each slot's textures destroyed by its type, then all 144 bytes cleared
// Bump (1): the bumped texture and the texture; environment (2): its texture; dual (4): its texture (RwTextureDestroy,
// sub_4D0F00); UV (5): the matrix pointers cleared. Returns the record.
// 0x004676C0 sub_4676C0 -- 304 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4676C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004676c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = 0;
    for (;;) {
        // 0x004676dc
        charge(ctx, 7);
        v1 = s1 & 0xFF;
        v0 = 5;
        v1 = sll(v1, 6);
        s0 = addu(s2, v1);
        lw(v1, s0, mfxslot::kType);
        if (v1 == v0) {
            // 0x004677a8
            charge(ctx, 2);
            sw(zero, s0, 0);
            sw(zero, s0, 4);
        } else {
            // 0x004676f8
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                // 0x00467788
                charge(ctx, 3);
                lw(a0, s0, 0);
                if (a0 != 0) {
                    // 0x00467794
                    charge(ctx, 4);
                    jal(ctx, 0x467794u, gen::fn_sub_4D0F00_004d0f00);
                }
            } else {
                // 0x00467704
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    // 0x00467768
                    charge(ctx, 3);
                    lw(a0, s0, 4);
                    if (a0 != 0) {
                        // 0x00467774
                        charge(ctx, 4);
                        jal(ctx, 0x467774u, gen::fn_sub_4D0F00_004d0f00);
                    }
                } else {
                    // 0x00467710
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00467730
                        charge(ctx, 3);
                        lw(a0, s0, 4);
                        if (a0 != 0) {
                            // 0x0046773c
                            charge(ctx, 3);
                            jal(ctx, 0x46773Cu, gen::fn_sub_4D0F00_004d0f00);
                        }
                        // 0x00467748
                        charge(ctx, 3);
                        lw(a0, s0, 8);
                        if (a0 != 0) {
                            // 0x00467754
                            charge(ctx, 4);
                            jal(ctx, 0x467754u, gen::fn_sub_4D0F00_004d0f00);
                        }
                    } else {
                        // 0x0046771c
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x00467724
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x004677b0
        charge(ctx, 5);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFF;
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004677c4
    charge(ctx, 11);
    a0 = s2;
    a1 = 0;
    a2 = 144;
    jal(ctx, 0x4677CCu, gen::fn_memset_00521408);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4677F0 [matfxMaterialDestructor] -- the RpMatFX material extension destructor: the effects record reset (sub_4676C0) and returned to the 144-byte free list; the material
// 0x004677F0 sub_4677F0 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4677F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004677f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    s0 = a0;
    v0 = addu(s0, v0);
    lw(s1, v0, 0);
    if (s1 != 0) {
        // 0x00467818
        charge(ctx, 11);
        a0 = s1;
        jal(ctx, 0x467818u, gen::fn_sub_4676C0_004676c0);
        v0 = 0x960000;
        lw(a0, v0, -15360);  // 0x95C400 (RpMatFX's 144-byte free list)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s1;
        jalr(ctx, 0x467830u, v0.u());
        lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
        v0 = addu(s0, v0);
        sw(zero, v0, 0);
    }
    // 0x00467844 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_467B40 [matfxReadTexture] -- reads an effect texture: a 'present' word, then (when 1) the texture chunk (RwTextureStreamRead, sub_4C83C0)
// ($a0 = the stream, $a1 = where the texture goes) Finds the texture chunk (type 6); a missing texture is accepted when
// the error left is 0x80000000 (none) or 22 (texture not found), else the error is re-raised. The stream, or 0.
// 0x00467B40 sub_467B40 -- 212 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_467B40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00467b40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a0;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x467B5Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x00467b84
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00467b6c
        charge(ctx, 3);
        lw(v0, sp, 0x3C);
        if (v0 == 0) {
            // 0x00467b78
            charge(ctx, 1);
            sw(zero, s1, 0);
            goto L_00467b7c;
        }
        // 0x00467b8c
        charge(ctx, 7);
        a0 = s0;
        a1 = 6;
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x467B98u, gen::fn_sub_4C1600_004c1600);
        if (v0 != 0) {
            // 0x00467bb0
            charge(ctx, 8);
            a0 = addiu(sp, 0x30);
            jal(ctx, 0x467BB0u, gen::fn_sub_4C1CD0_004c1cd0);
            a0 = s0;
            jal(ctx, 0x467BB8u, gen::fn_sub_4C83C0_004c83c0);
            sw(v0, s1, 0);
            lw(v0, s1, 0);
            if (v0 != 0) {
                backedge(ctx);
            L_00467b7c:
                charge(ctx, 2);
                v0 = s0;
            } else {
                // 0x00467bd0
                charge(ctx, 6);
                a0 = addiu(sp, 0x30);
                jal(ctx, 0x467BD0u, gen::fn_sub_4C1CD0_004c1cd0);
                lw(v1, sp, 0x34);
                v0 = lui(0x8000);
                if (v1 == v0) {
                    backedge(ctx);
                    goto L_00467b7c;
                }
                // 0x00467be8
                charge(ctx, 3);
                v0 = 22;
                if (v1 == v0) {
                    backedge(ctx);
                    goto L_00467b7c;
                }
                // 0x00467bf4
                charge(ctx, 3);
                a0 = addiu(sp, 0x30);
                jal(ctx, 0x467BF4u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            }
        } else {
            // 0x00467ba8
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x00467c00 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_467C20 [matfxMaterialStreamWrite] -- the RpMatFX material extension stream write: the effects flags, then each of the two slots by its type
// ($a0 = the stream, $a2 = the material) The flags (+128), then per slot its type and: bump (1) -- the negated
// coefficient as a real, the bumped texture, the texture; environment (2) -- the coefficient, the frame-buffer alpha,
// the texture; dual (4) -- the source / destination blend modes, the texture; UV (5) and none (0) -- nothing. A
// texture goes as a 'present' word and RwTextureStreamWrite (sub_4C8240). The stream, or 0 on a write error.
// 0x00467C20 sub_467C20 -- 936 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_467C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00467c20
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    a1 = addiu(sp, 0x7C);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    s0 = a0;
    v0 = addu(a2, v0);
    lw(s2, v0, 0);
    a2 = 4;
    lw(v0, s2, mfx::kFlags);
    link(ctx, 0x467C58u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x7C);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    if (v0 != 0) {
        // 0x00467c70: each of the two slots: its type word
        charge(ctx, 1);
        s4 = 0;
        for (;;) {
            // 0x00467c74
            charge(ctx, 11);
            v0 = s4 & 0xFF;
            a0 = s0;
            s1 = sll(v0, 6);
            a1 = addiu(sp, 0x78);
            v0 = addu(s2, s1);
            a2 = 4;
            lw(v0, v0, 32);
            link(ctx, 0x467C90u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x78);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);
            if (v0 == 0) {
                break;
            }
            // 0x00467ca8: a dual slot: the blend modes, the texture
            charge(ctx, 4);
            lw(v1, sp, 0x78);
            a2 = 4;
            if (v1 == a2) {
                // 0x00467e48
                charge(ctx, 8);
                s1 = addu(s2, s1);
                a0 = s0;
                lw(v0, s1, 4);
                a1 = addiu(sp, 0x7C);
                link(ctx, 0x467E58u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x7C);
                call(ctx, gen::fn_sub_4C17F0_004c17f0);
                if (v0 == 0) {
                    goto L_00467f78;
                }
                // 0x00467e68
                charge(ctx, 8);
                lw(v0, s1, 8);
                a0 = s0;
                a1 = addiu(sp, 0x7C);
                a2 = 4;
                link(ctx, 0x467E78u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x7C);
                call(ctx, gen::fn_sub_4C17F0_004c17f0);
                if (v0 == 0) {
                    goto L_00467f80;
                }
                // 0x00467e88
                charge(ctx, 9);
                lw(s1, s1, 0);
                a0 = s0;
                a1 = addiu(sp, 0x64);
                a2 = 4;
                v0 = sltu(0, s1);
                link(ctx, 0x467E9Cu);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x64);
                call(ctx, gen::fn_sub_4C17F0_004c17f0);
                if (v0 != 0) {
                    // 0x00467eb8
                    charge(ctx, 3);
                    lw(v0, sp, 0x64);
                    if (v0 == 0) {
                        // 0x00467ec4
                        charge(ctx, 1);
                        goto L_00467ec8;
                    }
                    // 0x00467f88
                    charge(ctx, 5);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x467F8Cu, gen::fn_sub_4C8240_004c8240);
                    if (v0 != 0) {
                        backedge(ctx);
                    L_00467ec8:
                        charge(ctx, 2);
                        v0 = s0;
                    } else {
                        // 0x00467f9c
                        charge(ctx, 2);
                        v0 = 0;
                        backedge(ctx);
                    }
                } else {
                    // 0x00467eac
                    charge(ctx, 2);
                    v0 = 0;
                }
                // 0x00467ed0
                charge(ctx, 2);
                if (v0 == 0) {
                    goto L_00467ed8_42;
                }
            L_00467ee0:
                charge(ctx, 1);
                v0 = addiu(s4, 1);
            L_00467ee4:
                charge(ctx, 4);
                s4 = v0 & 0xFF;
                v0 = slti(s4, 2);
                if (v0 == 0) {
                    goto L_00467ef4_45;
                }
                backedge(ctx);
                continue;
            }
            // 0x00467cb8: an environment slot: the coefficient, the frame-buffer alpha, the texture
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00467db8
                charge(ctx, 6);
                s1 = addu(s2, s1);
                a0 = s0;
                a1 = addiu(s1, 8);
                jal(ctx, 0x467DC0u, gen::fn_sub_4C1750_004c1750);
                if (v0 == 0) {
                    goto L_00467f48;
                }
                // 0x00467dd0
                charge(ctx, 8);
                lw(v0, s1, 12);
                a0 = s0;
                a1 = addiu(sp, 0x7C);
                a2 = 4;
                link(ctx, 0x467DE0u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x7C);
                call(ctx, gen::fn_sub_4C17F0_004c17f0);
                if (v0 == 0) {
                    goto L_00467f50;
                }
                // 0x00467df0
                charge(ctx, 9);
                lw(s1, s1, 4);
                a0 = s0;
                a1 = addiu(sp, 0x68);
                a2 = 4;
                v0 = sltu(0, s1);
                link(ctx, 0x467E04u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x68);
                call(ctx, gen::fn_sub_4C17F0_004c17f0);
                if (v0 != 0) {
                    // 0x00467e20
                    charge(ctx, 3);
                    lw(v0, sp, 0x68);
                    if (v0 == 0) {
                        // 0x00467e2c
                        charge(ctx, 1);
                        goto L_00467e30;
                    }
                    // 0x00467f58
                    charge(ctx, 5);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x467F5Cu, gen::fn_sub_4C8240_004c8240);
                    if (v0 != 0) {
                        backedge(ctx);
                    L_00467e30:
                        charge(ctx, 2);
                        v0 = s0;
                    } else {
                        // 0x00467f6c
                        charge(ctx, 2);
                        v0 = 0;
                        backedge(ctx);
                    }
                } else {
                    // 0x00467e14
                    charge(ctx, 2);
                    v0 = 0;
                }
                // 0x00467e38
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_00467ee0;
                }
                goto L_00467e40_33;
            }
            // 0x00467cc4
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x00467cd0
                charge(ctx, 3);
                v0 = 5;
                if (v1 == v0) {
                    goto L_00467ee0;
                }
                // 0x00467cdc
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_00467ee0;
                }
                // 0x00467ce4
                charge(ctx, 2);
                v0 = addiu(s4, 1);
                goto L_00467ee4;
            }
            // 0x00467cf0
            charge(ctx, 9);
            s3 = addu(s2, s1);
            lwc1(f0, s3, 12);
            a0 = s0;
            a1 = addiu(sp, 0x74);
            neg_s(f0, f0);
            link(ctx, 0x467D04u);  // $ra first: the delay slot below depends on it
            swc1(f0, sp, 0x74);
            call(ctx, gen::fn_sub_4C1750_004c1750);
            if (v0 == 0) {
                goto L_00467efc;
            }
            // 0x00467d14
            charge(ctx, 9);
            lw(s1, s3, 4);
            a0 = s0;
            a1 = addiu(sp, 0x70);
            a2 = 4;
            v0 = sltu(0, s1);
            link(ctx, 0x467D28u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x70);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);
            if (v0 != 0) {
                // 0x00467d40
                charge(ctx, 3);
                lw(v0, sp, 0x70);
                if (v0 == 0) {
                    // 0x00467d4c
                    charge(ctx, 1);
                    goto L_00467d50;
                }
                // 0x00467f04
                charge(ctx, 5);
                a0 = s1;
                a1 = s0;
                jal(ctx, 0x467F08u, gen::fn_sub_4C8240_004c8240);
                if (v0 != 0) {
                    backedge(ctx);
                L_00467d50:
                    charge(ctx, 2);
                    v0 = s0;
                } else {
                    // 0x00467f18
                    charge(ctx, 2);
                    v0 = 0;
                    backedge(ctx);
                }
            } else {
                // 0x00467d38
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x00467d58
            charge(ctx, 2);
            if (v0 == 0) {
                goto L_00467f20;
            }
            // 0x00467d60
            charge(ctx, 9);
            lw(s1, s3, 8);
            a0 = s0;
            a1 = addiu(sp, 0x6C);
            a2 = 4;
            v0 = sltu(0, s1);
            link(ctx, 0x467D74u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x6C);
            call(ctx, gen::fn_sub_4C17F0_004c17f0);
            if (v0 != 0) {
                // 0x00467d90
                charge(ctx, 3);
                lw(v0, sp, 0x6C);
                if (v0 == 0) {
                    // 0x00467d9c
                    charge(ctx, 1);
                    goto L_00467da0;
                }
                // 0x00467f28
                charge(ctx, 5);
                a0 = s1;
                a1 = s0;
                jal(ctx, 0x467F2Cu, gen::fn_sub_4C8240_004c8240);
                if (v0 != 0) {
                    backedge(ctx);
                L_00467da0:
                    charge(ctx, 2);
                    v0 = s0;
                } else {
                    // 0x00467f3c
                    charge(ctx, 2);
                    v0 = 0;
                    backedge(ctx);
                }
            } else {
                // 0x00467d84
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x00467da8
            charge(ctx, 2);
            if (v0 != 0) {
                goto L_00467ee0;
            }
            goto L_00467db0_24;
        }
        // 0x00467ca0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00467c68
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467db0_24:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467e40_33:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467ed8_42:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467ef4_45:
    charge(ctx, 2);
    v0 = s0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467efc:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467f20:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467f48:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467f50:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467f78:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00467f80:
    charge(ctx, 2);
    v0 = 0;
    // 0x00467fa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}


// sub_468350 [matfxMaterialStreamSize] -- the RpMatFX material extension stream size: 4 (the flags) + per slot 4 (its type) + its fields and textures
// 0 for a material without an extension or without effects. A texture counts its chunk (RwTextureStreamGetSize,
// sub_4C81D0) + 16, or 4 for a missing one.
// 0x00468350 sub_468350 -- 368 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_468350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468350
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v0 = addu(a0, v0);
    lw(s0, v0, 0);
    if (s0 != 0) {
        // 0x00468380
        charge(ctx, 3);
        lw(v0, s0, mfx::kFlags);
        if (v0 == 0) {
            goto L_0046849c;
        }
        // 0x0046838c
        charge(ctx, 2);
        v0 = 4;
        s3 = 0;
        for (;;) {
            // 0x00468394
            charge(ctx, 7);
            v1 = s3 & 0xFF;
            s2 = 4;
            v1 = sll(v1, 6);
            s1 = addu(s0, v1);
            lw(a0, s1, mfxslot::kType);
            v0 = addiu(v0, 4);
            if (a0 == s2) {
                // 0x00468458
                charge(ctx, 3);
                lw(a0, s1, 0);
                s4 = addiu(v0, 8);
                if (a0 != 0) {
                    // 0x00468464
                    charge(ctx, 5);
                    jal(ctx, 0x468464u, gen::fn_sub_4C81D0_004c81d0);
                    v0 = addiu(v0, 12);
                    s2 = addu(s2, v0);
                }
                // 0x00468478
                charge(ctx, 2);
                v0 = addu(s4, s2);
            } else {
                // 0x004683b0
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00468430
                    charge(ctx, 3);
                    lw(a0, s1, 4);
                    s4 = addiu(v0, 8);
                    if (a0 != 0) {
                        // 0x0046843c
                        charge(ctx, 5);
                        jal(ctx, 0x46843Cu, gen::fn_sub_4C81D0_004c81d0);
                        v0 = addiu(v0, 12);
                        s2 = addu(s2, v0);
                    }
                    // 0x00468450
                    charge(ctx, 2);
                    v0 = addu(s4, s2);
                } else {
                    // 0x004683bc
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x004683e8
                        charge(ctx, 3);
                        lw(a0, s1, 4);
                        s4 = addiu(v0, 4);
                        if (a0 != 0) {
                            // 0x004683f4
                            charge(ctx, 5);
                            jal(ctx, 0x4683F4u, gen::fn_sub_4C81D0_004c81d0);
                            v0 = addiu(v0, 12);
                            s2 = addu(s2, v0);
                        }
                        // 0x00468408
                        charge(ctx, 4);
                        lw(a0, s1, 8);
                        s2 = addu(s4, s2);
                        s1 = 4;
                        if (a0 != 0) {
                            // 0x00468418
                            charge(ctx, 4);
                            jal(ctx, 0x468418u, gen::fn_sub_4C81D0_004c81d0);
                            v0 = addiu(v0, 12);
                            s1 = addu(s1, v0);
                        }
                        // 0x00468428
                        charge(ctx, 2);
                        v0 = addu(s2, s1);
                    } else {
                        // 0x004683c8
                        charge(ctx, 3);
                        v1 = 5;
                        if (a0 != v1) {
                            // 0x004683d4
                            charge(ctx, 2);
                            if (a0 != 0) {
                                // 0x004683dc
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
            // 0x00468480
            charge(ctx, 5);
            v1 = addiu(s3, 1);
            s3 = v1 & 0xFF;
            v1 = slti(s3, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00468494
        charge(ctx, 2);
        ld(ra, sp, 0x50);
        // 0x004684a4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_0046849c:
    charge(ctx, 2);
    v0 = 0;
    ld(ra, sp, 0x50);
    // 0x004684a4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4684C0 [matfxAtomicConstructor] -- the RpMatFX atomic extension constructor: the 'effects enabled' word = 0; the atomic
// 0x004684C0 sub_4684C0 -- 20 bytes; leaf frame (no stack)
void sub_4684C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004684c0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17844);  // 0x7CE73C (the RpMatFX atomic extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_4684E0 [matfxAtomicDestructor] -- the RpMatFX atomic extension destructor: the 'effects enabled' word = 0; the atomic
// 0x004684E0 sub_4684E0 -- 20 bytes; leaf frame (no stack)
void sub_4684E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004684e0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17844);  // 0x7CE73C (the RpMatFX atomic extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_468500 [matfxAtomicCopy] -- the RpMatFX atomic extension copy: sets the destination's word to 1 when the source's is set; the destination
// 0x00468500 sub_468500 -- 48 bytes; leaf frame (no stack)
void sub_468500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00468500
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17844);  // 0x7CE73C (the RpMatFX atomic extension offset)
    v0 = addu(a1, v1);
    lw(v0, v0, 0);
    v1 = addu(a0, v1);
    if (v0 != 0) {
        // 0x0046851c
        charge(ctx, 3);
        v0 = 1;
        sw(v0, v1, 0);
        backedge(ctx);
    }
    // 0x00468514
    charge(ctx, 2);
    v0 = a0;
    // 0x00468528
    charge(ctx, 2);
}


// sub_468530 [matfxAtomicStreamWrite] -- the RpMatFX atomic extension stream write: the 'effects enabled' word (RwStreamWriteInt32)
// 0x00468530 sub_468530 -- 48 bytes; frame 0x20: ra sp+0x0
void sub_468530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468530
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a1 = addiu(sp, 0x1C);
    lw(v0, gp, -17844);  // 0x7CE73C (the RpMatFX atomic extension offset)
    v0 = addu(a2, v0);
    lw(v0, v0, 0);
    a2 = 4;
    link(ctx, 0x46854Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x1C);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4685D0 [matfxAtomicStreamSize] -- the RpMatFX atomic extension stream size: 4 when effects are enabled, else 0
// 0x004685D0 sub_4685D0 -- 28 bytes; leaf frame (no stack)
void sub_4685D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004685d0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17844);  // 0x7CE73C (the RpMatFX atomic extension offset)
    v0 = 0;
    v1 = 4;
    a0 = addu(a0, a1);
    lw(a0, a0, 0);
    if (a0 != 0) v0 = v1;
}


// sub_4685F0 [matfxSectorConstructor] -- the RpMatFX world-sector extension constructor: the 'effects enabled' word = 0; the sector
// 0x004685F0 sub_4685F0 -- 20 bytes; leaf frame (no stack)
void sub_4685F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004685f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_468610 [matfxSectorDestructor] -- the RpMatFX world-sector extension destructor: the 'effects enabled' word = 0; the sector
// 0x00468610 sub_468610 -- 20 bytes; leaf frame (no stack)
void sub_468610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00468610
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_468630 [matfxSectorCopy] -- the RpMatFX world-sector extension copy: sets the destination's word to 1 when the source's is set
// 0x00468630 sub_468630 -- 48 bytes; leaf frame (no stack)
void sub_468630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00468630
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
    v0 = addu(a1, v1);
    lw(v0, v0, 0);
    v1 = addu(a0, v1);
    if (v0 != 0) {
        // 0x0046864c
        charge(ctx, 3);
        v0 = 1;
        sw(v0, v1, 0);
        backedge(ctx);
    }
    // 0x00468644
    charge(ctx, 2);
    v0 = a0;
    // 0x00468658
    charge(ctx, 2);
}


// sub_468660 [matfxSectorStreamWrite] -- the RpMatFX world-sector extension stream write: the 'effects enabled' word
// 0x00468660 sub_468660 -- 48 bytes; frame 0x20: ra sp+0x0
void sub_468660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468660
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a1 = addiu(sp, 0x1C);
    lw(v0, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
    v0 = addu(a2, v0);
    lw(v0, v0, 0);
    a2 = 4;
    link(ctx, 0x46867Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x1C);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_468690 [matfxSectorStreamRead] -- the RpMatFX world-sector extension stream read: a word; when set, RpMatFXWorldSectorEnableEffects (sub_468E30)
// The stream, or 0 when the word cannot be read.
// 0x00468690 sub_468690 -- 108 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_468690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468690
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    a1 = addiu(sp, 0x3C);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a2 = 4;
    jal(ctx, 0x4686ACu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004686d0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004686bc
        charge(ctx, 3);
        lw(v0, sp, 0x3C);
        if (v0 != 0) {
            // 0x004686d8
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x4686D8u, gen::fn_sub_468E30_00468e30);
            backedge(ctx);
        }
        // 0x004686c8
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004686e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_468700 [matfxSectorStreamSize] -- the RpMatFX world-sector extension stream size: 4 when effects are enabled, else 0
// 0x00468700 sub_468700 -- 28 bytes; leaf frame (no stack)
void sub_468700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00468700
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
    v0 = 0;
    v1 = 4;
    a0 = addu(a0, a1);
    lw(a0, a0, 0);
    if (a0 != 0) v0 = v1;
}


// sub_468C50 [RpMatFXPluginAttach] -- registers RpMatFX (plugin 0x120): the engine open / close, the 4-byte material, atomic and world-sector extensions with their streams
// The three extension offsets go to gp 0x7CE738 / 0x7CE73C / 0x7CE740. 1, or 0 at the first registration that fails.
// 0x00468C50 sub_468C50 -- 356 bytes; frame 0x10: ra sp+0x0
void sub_468C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468c50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x460000;
    a3 = 0x460000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 288;
    a2 = addiu(a2, 30208);  // &sub_467600
    a3 = addiu(a3, 30096);  // &sub_467590
    jal(ctx, 0x468C6Cu, gen::fn_sub_4CA520_004ca520);
    if (i64(v0) >= 0) {
        // 0x00468c84
        charge(ctx, 11);
        a2 = 0x460000;
        a3 = 0x460000;
        t0 = 0x460000;
        a0 = 4;
        a1 = 288;
        a2 = addiu(a2, 30368);  // &sub_4676A0
        a3 = addiu(a3, 30704);  // &sub_4677F0
        t0 = addiu(t0, 30816);  // &sub_467860
        jal(ctx, 0x468CA0u, gen::fn_sub_494DB0_00494db0);
        sw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
        if (i64(v0) >= 0) {
            // 0x00468cb8
            charge(ctx, 10);
            a1 = 0x460000;
            a2 = 0x460000;
            a3 = 0x470000;
            a0 = 288;
            a1 = addiu(a1, 32720);  // &sub_467FD0
            a2 = addiu(a2, 31776);  // &sub_467C20
            a3 = addiu(a3, -31920);  // &sub_468350
            jal(ctx, 0x468CD0u, gen::fn_sub_494DE0_00494de0);
            if (i64(v0) >= 0) {
                // 0x00468ce8
                charge(ctx, 11);
                a2 = 0x470000;
                a3 = 0x470000;
                t0 = 0x470000;
                a0 = 4;
                a1 = 288;
                a2 = addiu(a2, -31552);  // &sub_4684C0
                a3 = addiu(a3, -31520);  // &sub_4684E0
                t0 = addiu(t0, -31488);  // &sub_468500
                jal(ctx, 0x468D04u, gen::fn_sub_492C30_00492c30);
                sw(v0, gp, -17844);  // 0x7CE73C (the RpMatFX atomic extension offset)
                if (i64(v0) >= 0) {
                    // 0x00468d1c
                    charge(ctx, 10);
                    a1 = 0x470000;
                    a2 = 0x470000;
                    a3 = 0x470000;
                    a0 = 288;
                    a1 = addiu(a1, -31392);  // &sub_468560
                    a2 = addiu(a2, -31440);  // &sub_468530
                    a3 = addiu(a3, -31280);  // &sub_4685D0
                    jal(ctx, 0x468D34u, gen::fn_sub_492C90_00492c90);
                    if (i64(v0) >= 0) {
                        // 0x00468d4c
                        charge(ctx, 11);
                        a2 = 0x470000;
                        a3 = 0x470000;
                        t0 = 0x470000;
                        a0 = 4;
                        a1 = 288;
                        a2 = addiu(a2, -31248);  // &sub_4685F0
                        a3 = addiu(a3, -31216);  // &sub_468610
                        t0 = addiu(t0, -31184);  // &sub_468630
                        jal(ctx, 0x468D68u, gen::fn_sub_499250_00499250);
                        sw(v0, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
                        if (i64(v0) >= 0) {
                            // 0x00468d80
                            charge(ctx, 10);
                            a1 = 0x470000;
                            a2 = 0x470000;
                            a3 = 0x470000;
                            a0 = 288;
                            a1 = addiu(a1, -31088);  // &sub_468690
                            a2 = addiu(a2, -31136);  // &sub_468660
                            a3 = addiu(a3, -30976);  // &sub_468700
                            jal(ctx, 0x468D98u, gen::fn_sub_499280_00499280);
                            v0 = slt(v0, 0);
                            v0 = v0 ^ 0x1;
                        } else {
                            // 0x00468d78
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x00468d44
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x00468d14
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x00468ce0
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x00468cb0
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x00468c7c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00468da8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_468E30 [RpMatFXWorldSectorEnableEffects] -- enables effects on a world sector: once, its pipeline set (matfxSetSectorPipeline) and the word set to 1
// The sector, or 0 when the pipeline cannot be set.
// 0x00468E30 sub_468E30 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_468E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468e30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17840);  // 0x7CE740 (the RpMatFX world-sector extension offset)
    s0 = addu(s1, v0);
    lw(v0, s0, 0);
    if (v0 == 0) {
        // 0x00468e60
        charge(ctx, 4);
        jal(ctx, 0x468E60u, gen::fn_matfxSetSectorPipeline_00469d00);
        if (v0 != 0) {
            // 0x00468e70
            charge(ctx, 3);
            v0 = 1;
            sw(v0, s0, 0);
            backedge(ctx);
            goto L_00468e58;
        }
        // 0x00468e7c
        charge(ctx, 1);
        v0 = 0;
        // 0x00468e80 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00468e58:
    charge(ctx, 2);
    v0 = s1;
    // 0x00468e80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_469030 [RpMatFXMaterialGetEffects] -- a material's effects flags (extension +128), or 0 without an extension
// 0x00469030 sub_469030 -- 40 bytes; leaf frame (no stack)
void sub_469030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00469030
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v0 = addu(a0, v0);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0046904c
        charge(ctx, 1);
        lw(v0, v0, 128);
    } else {
        // 0x00469044
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00469050 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_469060 [RpMatFXMaterialSetBumpMapTexture] -- sets the bump-map slot's texture and derives the bumped texture
// ($a0 = the material, $a1 = the texture or 0) The old bumped texture and texture are destroyed (RwTextureDestroy,
// sub_4D0F00). With a texture whose raster and the material's texture's raster both exist: the bumped texture's name
// (sub_468720 on a 32-byte stack buffer), looked up in the current dictionary (sub_4D11F0 / sub_4D1170) or created
// (sub_469DC0) and added to it (sub_4D1110); +16 = 1 / the bumped (else the material's) texture raster's width.
// The slot is the first of the two whose type (+32) is 1 (bump); without one the access goes to address 0 + offset (the original faults).
// The material, or 0 when the bumped texture cannot be created.
// 0x00469060 sub_469060 -- 540 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_469060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00469060
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    a1 = 0;
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v0 = addu(s3, v0);
    lw(a0, v0, 0);
    v1 = 1;
    for (;;) {
        // 0x00469098
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        s1 = addu(a0, v0);
        lw(v0, s1, mfxslot::kType);
        if (v0 == v1) {
            goto L_004690b0_2;
        }
        // 0x004690b8
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004690cc
    charge(ctx, 2);
    s1 = 0;
    lw(a0, s1, mfxbump::kTexture);  // 0x8
L_004690d4:
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x004690dc
        charge(ctx, 3);
        jal(ctx, 0x4690DCu, gen::fn_sub_4D0F00_004d0f00);
        sw(zero, s1, mfxbump::kTexture);
    }
    // 0x004690e8
    charge(ctx, 3);
    lw(a0, s1, mfxbump::kBumpTexture);
    if (a0 != 0) {
        // 0x004690f4
        charge(ctx, 4);
        jal(ctx, 0x4690F4u, gen::fn_sub_4D0F00_004d0f00);
        sw(zero, s1, mfxbump::kBumpTexture);
        sw(zero, s1, mfxbump::kInvWidth);
    }
    // 0x00469104
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x00469230
        charge(ctx, 11);
        lw(v1, s3, 0);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        lw(v0, v1, 0);
        lwc1(f1, v0, 12);
        cvt_s_w(f1, f1);
        div_s(f0, f0, f1);
        swc1(f0, s1, mfxbump::kInvWidth);
        backedge(ctx);
    L_004691ec:
        charge(ctx, 2);
        v0 = s3;
    } else {
        // 0x0046910c
        charge(ctx, 11);
        sw(s2, s1, mfxbump::kTexture);
        lw(v1, s1, mfxbump::kTexture);
        lw(v0, v1, rwtex::kRefCount);
        v0 = addiu(v0, 1);
        sw(v0, v1, rwtex::kRefCount);
        lw(v0, s2, 0);
        lw(v0, v0, 12);
        // xor v0: a 64-bit move to itself (no effect)
        v0 = sltiu(v0, 1);
        lw(s0, s3, 0);
        if (v0 == 0) {
            // 0x00469138
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x00469140
                charge(ctx, 4);
                lw(v0, s0, 0);
                lw(v0, v0, 12);
                // xor v0: a 64-bit move to itself (no effect)
                v0 = sltiu(v0, 1);
            }
        }
        // 0x00469150
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_004691ec;
        }
        // 0x00469158
        charge(ctx, 3);
        v1 = addiu(sp, 0x60);
        v0 = 32;
        if (v1 != 0) {
            for (;;) {
                // 0x00469164
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
        // 0x00469180
        charge(ctx, 9);
        a0 = addiu(sp, 0x60);
        a1 = s0;
        a2 = s2;
        jal(ctx, 0x469188u, gen::fn_sub_468720_00468720);
        jal(ctx, 0x469190u, gen::fn_sub_4D11F0_004d11f0);
        s4 = v0;
        sw(zero, s1, mfxbump::kBumpTexture);
        if (s4 != 0) {
            // 0x004691a4
            charge(ctx, 4);
            a0 = s4;
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x4691A8u, gen::fn_sub_4D1170_004d1170);
            sw(v0, s1, mfxbump::kBumpTexture);
        }
        // 0x004691b4
        charge(ctx, 3);
        lw(v1, s1, mfxbump::kBumpTexture);
        if (v1 != 0) {
            // 0x004691c0
            charge(ctx, 3);
            lw(v0, v1, rwtex::kRefCount);
            v0 = addiu(v0, 1);
            sw(v0, v1, rwtex::kRefCount);
            goto L_004691cc;
        }
        // 0x004691f4
        charge(ctx, 7);
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x4691F8u, gen::fn_sub_469DC0_00469dc0);
        sw(v0, s1, mfxbump::kBumpTexture);
        lw(a1, s1, mfxbump::kBumpTexture);
        if (a1 != 0) {
            // 0x00469210
            charge(ctx, 2);
            if (s4 == 0) {
                backedge(ctx);
            L_004691cc:
                charge(ctx, 1);
                lw(v1, s1, mfxbump::kBumpTexture);
            } else {
                // 0x00469218
                charge(ctx, 4);
                a0 = s4;
                jal(ctx, 0x469218u, gen::fn_sub_4D1110_004d1110);
                lw(v1, s1, mfxbump::kBumpTexture);
                backedge(ctx);
            }
            // 0x004691d0
            charge(ctx, 7);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            lw(v0, v1, 0);
            lwc1(f1, v0, 12);
            cvt_s_w(f1, f1);
            div_s(f0, f0, f1);
            swc1(f0, s1, mfxbump::kInvWidth);
            goto L_004691ec;
        }
        // 0x00469228
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0046925c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004690b0_2:
    charge(ctx, 2);
    lw(a0, s1, mfxbump::kTexture);
    goto L_004690d4;
}


// sub_469280 [RpMatFXMaterialSetBumpMapFrame] -- the bump-map slot's frame (+0) = $a1; the material
// The slot is the first of the two whose type (+32) is 1 (bump); without one the access goes to address 0 + offset (the original faults).
// 0x00469280 sub_469280 -- 88 bytes; leaf frame (no stack)
void sub_469280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x00469280
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a3 = 0;
    v0 = addu(a0, v0);
    lw(a2, v0, 0);
    v1 = 1;
    for (;;) {
        // 0x00469294
        charge(ctx, 6);
        v0 = a3 & 0xFF;
        v0 = sll(v0, 6);
        t0 = addu(a2, v0);
        lw(v0, t0, mfxslot::kType);
        if (v0 == v1) {
            goto L_004692ac_2;
        }
        // 0x004692b4
        charge(ctx, 5);
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFF;
        v0 = slti(a3, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004692c8
    charge(ctx, 2);
    t0 = 0;
    sw(a1, t0, mfxbump::kFrame);  // 0x0
    // 0x004692d0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
    return;
L_004692ac_2:
    charge(ctx, 2);
    sw(a1, t0, mfxbump::kFrame);
    // 0x004692d0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}


// sub_4692E0 [RpMatFXMaterialSetBumpMapCoefficient] -- the bump-map slot's coefficient = $f12, stored negated (+12); the material
// The slot is the first of the two whose type (+32) is 1 (bump); without one the access goes to address 0 + offset (the original faults).
// 0x004692E0 sub_4692E0 -- 92 bytes; leaf frame (no stack)
void sub_4692E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004692e0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a2 = 0;
    v0 = addu(a0, v0);
    lw(a1, v0, 0);
    v1 = 1;
    for (;;) {
        // 0x004692f4
        charge(ctx, 6);
        v0 = a2 & 0xFF;
        v0 = sll(v0, 6);
        a3 = addu(a1, v0);
        lw(v0, a3, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046930c_2;
        }
        // 0x00469314
        charge(ctx, 5);
        v0 = addiu(a2, 1);
        a2 = v0 & 0xFF;
        v0 = slti(a2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469328
    charge(ctx, 2);
    a3 = 0;
    neg_s(f0, f12);
    // 0x00469330 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
    swc1(f0, a3, mfxbump::kNegCoef);
    return;
L_0046930c_2:
    charge(ctx, 2);
    neg_s(f0, f12);
    // 0x00469330 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
    swc1(f0, a3, mfxbump::kNegCoef);
}


// sub_469340 [RpMatFXMaterialGetBumpMapFrame] -- the bump-map slot's frame (+0)
// The slot is the first of the two whose type (+32) is 1 (bump); without one the access goes to address 0 + offset (the original faults).
// 0x00469340 sub_469340 -- 88 bytes; leaf frame (no stack)
void sub_469340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00469340
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 1;
    for (;;) {
        // 0x00469354
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046936c_2;
        }
        // 0x00469374
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469388
    charge(ctx, 2);
    a2 = 0;
    lw(v0, a2, mfxbump::kFrame);  // 0x0
    // 0x00469390 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0046936c_2:
    charge(ctx, 2);
    lw(v0, a2, mfxbump::kFrame);
    // 0x00469390 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4693A0 [RpMatFXMaterialGetBumpMapCoefficient] -- the bump-map slot's coefficient in $f0 (the stored value negated back)
// The slot is the first of the two whose type (+32) is 1 (bump); without one the access goes to address 0 + offset (the original faults).
// 0x004693A0 sub_4693A0 -- 88 bytes; leaf frame (no stack)
void sub_4693A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    Fpr f0{ctx, 0};
    // 0x004693a0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 1;
    for (;;) {
        // 0x004693b4
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_004693cc_2;
        }
        // 0x004693d4
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004693e8
    charge(ctx, 2);
    a2 = 0;
    lwc1(f0, a2, mfxbump::kNegCoef);  // 0xC
    // 0x004693f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    neg_s(f0, f0);
    return;
L_004693cc_2:
    charge(ctx, 2);
    lwc1(f0, a2, mfxbump::kNegCoef);
    // 0x004693f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    neg_s(f0, f0);
}


// sub_469400 [RpMatFXMaterialSetEnvMapTexture] -- sets the environment slot's texture: its reference count up, the old one destroyed; the material
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x00469400 sub_469400 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_469400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469400
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(s2, v0);
    lw(a0, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x00469430
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        s0 = addu(a0, v0);
        lw(v0, s0, mfxslot::kType);
        if (v0 == v1) {
            goto L_00469448_2;
        }
        // 0x00469450
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469464
    charge(ctx, 2);
    s0 = 0;
    lw(v0, s1, rwtex::kRefCount);
L_0046946c:
    charge(ctx, 5);
    v0 = addiu(v0, 1);
    sw(v0, s1, rwtex::kRefCount);
    lw(a0, s0, mfxenv::kTexture);
    if (a0 != 0) {
        // 0x00469480
        charge(ctx, 3);
        jal(ctx, 0x469480u, gen::fn_sub_4D0F00_004d0f00);
        sw(zero, s0, mfxenv::kTexture);
    }
    // 0x0046948c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(s1, s0, mfxenv::kTexture);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_00469448_2:
    charge(ctx, 2);
    lw(v0, s1, rwtex::kRefCount);
    goto L_0046946c;
}


// sub_4694B0 [RpMatFXMaterialSetEnvMapFrame] -- the environment slot's frame (+0) = $a1; the material
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x004694B0 sub_4694B0 -- 88 bytes; leaf frame (no stack)
void sub_4694B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x004694b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a3 = 0;
    v0 = addu(a0, v0);
    lw(a2, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x004694c4
        charge(ctx, 6);
        v0 = a3 & 0xFF;
        v0 = sll(v0, 6);
        t0 = addu(a2, v0);
        lw(v0, t0, mfxslot::kType);
        if (v0 == v1) {
            goto L_004694dc_2;
        }
        // 0x004694e4
        charge(ctx, 5);
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFF;
        v0 = slti(a3, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004694f8
    charge(ctx, 2);
    t0 = 0;
    sw(a1, t0, mfxenv::kFrame);  // 0x0
    // 0x00469500 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
    return;
L_004694dc_2:
    charge(ctx, 2);
    sw(a1, t0, mfxenv::kFrame);
    // 0x00469500 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}


// sub_469590 [RpMatFXMaterialSetEnvMapCoefficient] -- the environment slot's coefficient (+8) = $f12; the material
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x00469590 sub_469590 -- 88 bytes; leaf frame (no stack)
void sub_469590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    Fpr f12{ctx, 12};
    // 0x00469590
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a2 = 0;
    v0 = addu(a0, v0);
    lw(a1, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x004695a4
        charge(ctx, 6);
        v0 = a2 & 0xFF;
        v0 = sll(v0, 6);
        a3 = addu(a1, v0);
        lw(v0, a3, mfxslot::kType);
        if (v0 == v1) {
            goto L_004695bc_2;
        }
        // 0x004695c4
        charge(ctx, 5);
        v0 = addiu(a2, 1);
        a2 = v0 & 0xFF;
        v0 = slti(a2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004695d8
    charge(ctx, 2);
    a3 = 0;
    swc1(f12, a3, mfxenv::kCoef);  // 0x8
    // 0x004695e0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
    return;
L_004695bc_2:
    charge(ctx, 2);
    swc1(f12, a3, mfxenv::kCoef);
    // 0x004695e0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}


// sub_4695F0 [RpMatFXMaterialGetEnvMapTexture] -- the environment slot's texture (+4)
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x004695F0 sub_4695F0 -- 88 bytes; leaf frame (no stack)
void sub_4695F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004695f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x00469604
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046961c_2;
        }
        // 0x00469624
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469638
    charge(ctx, 2);
    a2 = 0;
    lw(v0, a2, mfxenv::kTexture);  // 0x4
    // 0x00469640 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0046961c_2:
    charge(ctx, 2);
    lw(v0, a2, mfxenv::kTexture);
    // 0x00469640 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_469650 [RpMatFXMaterialGetEnvMapFrame] -- the environment slot's frame (+0)
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x00469650 sub_469650 -- 88 bytes; leaf frame (no stack)
void sub_469650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00469650
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x00469664
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046967c_2;
        }
        // 0x00469684
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469698
    charge(ctx, 2);
    a2 = 0;
    lw(v0, a2, mfxenv::kFrame);  // 0x0
    // 0x004696a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0046967c_2:
    charge(ctx, 2);
    lw(v0, a2, mfxenv::kFrame);
    // 0x004696a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4696B0 [RpMatFXMaterialGetEnvMapFrameBufferAlpha] -- the environment slot's frame-buffer alpha switch (+12)
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x004696B0 sub_4696B0 -- 88 bytes; leaf frame (no stack)
void sub_4696B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004696b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x004696c4
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_004696dc_2;
        }
        // 0x004696e4
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004696f8
    charge(ctx, 2);
    a2 = 0;
    lw(v0, a2, mfxenv::kFbAlpha);  // 0xC
    // 0x00469700 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004696dc_2:
    charge(ctx, 2);
    lw(v0, a2, mfxenv::kFbAlpha);
    // 0x00469700 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_469710 [RpMatFXMaterialGetEnvMapCoefficient] -- the environment slot's coefficient (+8) in $f0
// The slot is the first of the two whose type (+32) is 2 (environment); without one the access goes to address 0 + offset (the original faults).
// 0x00469710 sub_469710 -- 88 bytes; leaf frame (no stack)
void sub_469710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    Fpr f0{ctx, 0};
    // 0x00469710
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 2;
    for (;;) {
        // 0x00469724
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046973c_2;
        }
        // 0x00469744
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469758
    charge(ctx, 2);
    a2 = 0;
    lwc1(f0, a2, mfxenv::kCoef);  // 0x8
    // 0x00469760 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0046973c_2:
    charge(ctx, 2);
    lwc1(f0, a2, mfxenv::kCoef);
    // 0x00469760 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4698E0 [RpMatFXMaterialGetDualTexture] -- the dual slot's texture (+0)
// The slot is the first of the two whose type (+32) is 4 (dual); without one the access goes to address 0 + offset (the original faults).
// 0x004698E0 sub_4698E0 -- 88 bytes; leaf frame (no stack)
void sub_4698E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004698e0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    a1 = 0;
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    v1 = 4;
    for (;;) {
        // 0x004698f4
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        a2 = addu(a0, v0);
        lw(v0, a2, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046990c_2;
        }
        // 0x00469914
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469928
    charge(ctx, 2);
    a2 = 0;
    lw(v0, a2, mfxdual::kTexture);  // 0x0
    // 0x00469930 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0046990c_2:
    charge(ctx, 2);
    lw(v0, a2, mfxdual::kTexture);
    // 0x00469930 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_469940 [RpMatFXMaterialGetDualBlendModes] -- the dual slot's source / destination blend modes (+4 / +8) into *$a1 / *$a2; the material
// The slot is the first of the two whose type (+32) is 4 (dual); without one the access goes to address 0 + offset (the original faults).
// 0x00469940 sub_469940 -- 100 bytes; leaf frame (no stack)
void sub_469940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    // 0x00469940
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    t0 = 0;
    v0 = addu(a0, v0);
    lw(a3, v0, 0);
    v1 = 4;
    for (;;) {
        // 0x00469954
        charge(ctx, 6);
        v0 = t0 & 0xFF;
        v0 = sll(v0, 6);
        t1 = addu(a3, v0);
        lw(v0, t1, mfxslot::kType);
        if (v0 == v1) {
            goto L_0046996c_2;
        }
        // 0x00469974
        charge(ctx, 5);
        v0 = addiu(t0, 1);
        t0 = v0 & 0xFF;
        v0 = slti(t0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469988
    charge(ctx, 2);
    t1 = 0;
    lw(v1, t1, mfxdual::kSrcBlend);  // 0x4
    // 0x00469990 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = a0;
    sw(v1, a1, 0);
    lw(v1, t1, mfxdual::kDstBlend);
    sw(v1, a2, 0);
    return;
L_0046996c_2:
    charge(ctx, 2);
    lw(v1, t1, mfxdual::kSrcBlend);
    // 0x00469990 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = a0;
    sw(v1, a1, 0);
    lw(v1, t1, mfxdual::kDstBlend);
    sw(v1, a2, 0);
}


// sub_4699B0 [RpMatFXMaterialSetUVTransformMatrices] -- the UV slot's base / dual matrices (+0 / +4) = $a1 / $a2; the material
// The slot is the first of the two whose type (+32) is 5 (UV transform); without one the access goes to address 0 + offset (the original faults).
// 0x004699B0 sub_4699B0 -- 92 bytes; leaf frame (no stack)
void sub_4699B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    // 0x004699b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    t0 = 0;
    v0 = addu(a0, v0);
    lw(a3, v0, 0);
    v1 = 5;
    for (;;) {
        // 0x004699c4
        charge(ctx, 6);
        v0 = t0 & 0xFF;
        v0 = sll(v0, 6);
        t1 = addu(a3, v0);
        lw(v0, t1, mfxslot::kType);
        if (v0 == v1) {
            goto L_004699dc_2;
        }
        // 0x004699e4
        charge(ctx, 5);
        v0 = addiu(t0, 1);
        t0 = v0 & 0xFF;
        v0 = slti(t0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004699f8
    charge(ctx, 2);
    t1 = 0;
    sw(a1, t1, mfxuv::kBaseMatrix);  // 0x0
    // 0x00469a00 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
    sw(a2, t1, mfxuv::kDualMatrix);
    return;
L_004699dc_2:
    charge(ctx, 2);
    sw(a1, t1, mfxuv::kBaseMatrix);
    // 0x00469a00 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
    sw(a2, t1, mfxuv::kDualMatrix);
}


// sub_469A10 [RpMatFXMaterialGetUVTransformMatrices] -- the UV slot's base / dual matrices into *$a1 / *$a2 (each when non-null); the material
// The slot is the first of the two whose type (+32) is 5 (UV transform); without one the access goes to address 0 + offset (the original faults).
// 0x00469A10 sub_469A10 -- 116 bytes; leaf frame (no stack)
void sub_469A10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    // 0x00469a10
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    t0 = 0;
    v0 = addu(a0, v0);
    lw(a3, v0, 0);
    v1 = 5;
    for (;;) {
        // 0x00469a24
        charge(ctx, 6);
        v0 = t0 & 0xFF;
        v0 = sll(v0, 6);
        t1 = addu(a3, v0);
        lw(v0, t1, mfxslot::kType);
        if (v0 == v1) {
            goto L_00469a3c_2;
        }
        // 0x00469a44
        charge(ctx, 5);
        v0 = addiu(t0, 1);
        t0 = v0 & 0xFF;
        v0 = slti(t0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00469a58
    charge(ctx, 1);
    t1 = 0;
L_00469a5c:
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x00469a64
        charge(ctx, 2);
        lw(v0, t1, mfxuv::kBaseMatrix);
        sw(v0, a1, 0);
    }
    // 0x00469a6c
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00469a74
        charge(ctx, 2);
        lw(v0, t1, mfxuv::kDualMatrix);
        sw(v0, a2, 0);
    }
    // 0x00469a7c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
    return;
L_00469a3c_2:
    charge(ctx, 2);
    goto L_00469a5c;
}


// sub_469AA0 [matfxSetupGsWords] -- the default GS words of a material's effect passes by its effects flags (a jump table on +128)
// 1 bump, 3 bump + env: slot 0's ALPHA word 0x80_0000_0048 (and for 3 slot 1's 88); 2 env: 0x80_0000_0068; 4 dual:
// slot 0's second word 0x1000000; 6 dual + UV: slot 1's 0x1000000; the other words of the pass cleared. Other flags:
// nothing.
// 0x00469AA0 sub_469AA0 -- 172 bytes; leaf frame (no stack)
void sub_469AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00469aa0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v1 = addu(a0, v1);
    lw(a1, v1, 0);
    lw(v1, a1, mfx::kFlags);
    at = sltiu(v1, 7);
    if (at != 0) {
        // 0x00469abc
        charge(ctx, 7);
        a0 = 0x7C0000;
        v1 = sll(v1, 2);
        a0 = addiu(a0, -14240);  // &0x7BC860
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x469AD8u:  // table[3]
            // 0x00469ad8
            charge(ctx, 4);
            v1 = 88;
            sd(v1, a1, mfx::kGs1Alpha);
            sd(zero, a1, mfx::kGs1B);
            sd(zero, a1, mfx::kGs1C);
        L_00469ae8:
            charge(ctx, 8);
            a0 = 128;
            v1 = 72;
            a0 = dsll32(a0, 0);
            v1 = v1 | a0;
            sd(v1, a1, mfx::kGs0Alpha);
            sd(zero, a1, mfx::kGs0B);
            sd(zero, a1, mfx::kGs0C);
            break;
        case 0x469AE8u:  // table[1]
            goto L_00469ae8;
        case 0x469B08u:  // table[2]
            // 0x00469b08
            charge(ctx, 8);
            a0 = 128;
            v1 = 104;
            a0 = dsll32(a0, 0);
            v1 = v1 | a0;
            sd(v1, a1, mfx::kGs0Alpha);
            sd(zero, a1, mfx::kGs0B);
            sd(zero, a1, mfx::kGs0C);
            break;
        case 0x469B28u:  // table[4]
            // 0x00469b28
            charge(ctx, 4);
            v1 = 0x1000000;
            sd(v1, a1, mfx::kGs0B);
            sd(zero, a1, mfx::kGs0C);
            break;
        case 0x469B38u:  // table[6]
            // 0x00469b38
            charge(ctx, 3);
            v1 = 0x1000000;
            sd(v1, a1, mfx::kGs1B);
            sd(zero, a1, mfx::kGs1C);
            break;
        case 0x469B44u:  // table[0, 5]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00469b44 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_469B50 [matfxSetEnvAlphaWord] -- an environment pass's ALPHA word from its frame-buffer alpha switch: 88 when set, else 0x80_0000_0068
// Slot 1 (+104 from +76) for bump + env (flags 3), else slot 0 (+40 from +12).
// 0x00469B50 sub_469B50 -- 104 bytes; leaf frame (no stack)
void sub_469B50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x00469b50
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v1 = 3;
    a0 = addu(a0, a1);
    lw(a3, a0, 0);
    lw(a0, a3, mfx::kFlags);
    if (a0 != v1) {
        // 0x00469b90
        charge(ctx, 8);
        lw(a2, a3, mfx::kEnv0FbAlpha);
        a0 = 128;
        v1 = 104;
        a0 = dsll32(a0, 0);
        a1 = 88;
        v1 = v1 | a0;
        if (a2 == 0) a1 = v1;
        sd(a1, a3, mfx::kGs0Alpha);
    } else {
        // 0x00469b6c
        charge(ctx, 9);
        lw(a2, a3, mfx::kEnv1FbAlpha);
        a0 = 128;
        v1 = 104;
        a0 = dsll32(a0, 0);
        a1 = 88;
        v1 = v1 | a0;
        if (a2 == 0) a1 = v1;
        sd(a1, a3, mfx::kGs1Alpha);
    }
    // 0x00469bb0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_469BC0 [matfxSetDualAlphaWord] -- the dual pass's ALPHA word from its blend modes: the 6 x 6 table 0x6B4EB0 | 0x80_0000_0000
// The dual slot is slot 0 when the flags are 4, else slot 1. Blend modes 1, 2, 5, 6, 7 are rows / columns 0..4,
// anything else 5 (two jump tables).
// 0x00469BC0 sub_469BC0 -- 280 bytes; leaf frame (no stack)
void sub_469BC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x00469bc0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17848);  // 0x7CE738 (the RpMatFX material extension offset)
    v1 = 4;
    a0 = addu(a0, a1);
    lw(a3, a0, 0);
    lw(a0, a3, mfx::kFlags);
    if (a0 != v1) {
        // 0x00469be4
        charge(ctx, 1);
        v1 = 1;
    } else {
        // 0x00469bdc
        charge(ctx, 2);
        v1 = 0;
    }
    // 0x00469be8
    charge(ctx, 6);
    a2 = sll(v1, 6);
    a1 = addu(a3, a2);
    lw(v1, a1, mfxdual::kSrcBlend);
    at = sltiu(v1, 9);
    if (at != 0) {
        // 0x00469c00
        charge(ctx, 7);
        a0 = 0x7C0000;
        v1 = sll(v1, 2);
        a0 = addiu(a0, -14160);  // &0x7BC8B0
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x469C1Cu:  // table[1]
            // 0x00469c1c
            charge(ctx, 2);
            t0 = 0;
            break;
        case 0x469C24u:  // table[2]
            // 0x00469c24
            charge(ctx, 2);
            t0 = 1;
            break;
        case 0x469C2Cu:  // table[5]
            // 0x00469c2c
            charge(ctx, 2);
            t0 = 2;
            break;
        case 0x469C34u:  // table[6]
            // 0x00469c34
            charge(ctx, 2);
            t0 = 3;
            break;
        case 0x469C3Cu:  // table[7]
            // 0x00469c3c
            charge(ctx, 2);
            t0 = 4;
            break;
        case 0x469C44u:  // table[0, 3, 4, 8]
        L_00469c44:
            charge(ctx, 1);
            t0 = 5;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        goto L_00469c48;
    }
    goto L_00469c44;
L_00469c48:
    charge(ctx, 4);
    lw(v1, a1, mfxdual::kDstBlend);
    at = sltiu(v1, 9);
    if (at != 0) {
        // 0x00469c58
        charge(ctx, 7);
        a0 = 0x7C0000;
        v1 = sll(v1, 2);
        a0 = addiu(a0, -14208);  // &0x7BC880
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x469C74u:  // table[1]
            // 0x00469c74
            charge(ctx, 2);
            a1 = 0;
            break;
        case 0x469C7Cu:  // table[2]
            // 0x00469c7c
            charge(ctx, 2);
            a1 = 1;
            break;
        case 0x469C84u:  // table[5]
            // 0x00469c84
            charge(ctx, 2);
            a1 = 2;
            break;
        case 0x469C8Cu:  // table[6]
            // 0x00469c8c
            charge(ctx, 2);
            a1 = 3;
            break;
        case 0x469C94u:  // table[7]
            // 0x00469c94
            charge(ctx, 2);
            a1 = 4;
            break;
        case 0x469C9Cu:  // table[0, 3, 4, 8]
        L_00469c9c:
            charge(ctx, 1);
            a1 = 5;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x00469ca0 (the shared epilogue, written out on this path)
        charge(ctx, 14);
        a0 = sll(a1, 1);
        v1 = addu(a2, a3);
        a0 = addu(a0, a1);
        a1 = 0x6B0000;
        a2 = sll(a0, 1);
        a1 = addiu(a1, 20144);  // &0x6B4EB0 (the RpMatFX dual-pass ALPHA table (6 x 6 bytes))
        a0 = 128;
        a1 = addu(a1, a2);
        a0 = dsll32(a0, 0);
        a1 = addu(t0, a1);
        lbu(a1, a1, mfxdual::kTexture);
        a0 = a1 | a0;
        sd(a0, v1, 40);
        return;
    }
    goto L_00469c9c;
}


// sub_469CE0 [matfxPlatformOpen] -- the platform part of RpMatFX's open: 1
// 0x00469CE0 sub_469CE0 -- 8 bytes; leaf frame (no stack)
void sub_469CE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00469ce0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}


// sub_469CF0 [matfxPlatformClose] -- the platform part of RpMatFX's close: 1
// 0x00469CF0 sub_469CF0 -- 8 bytes; leaf frame (no stack)
void sub_469CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00469cf0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}


// sub_469DD0 [morphOpen] -- RpMorph's engine open: the open count up; $a0
// 0x00469DD0 sub_469DD0 -- 20 bytes; leaf frame (no stack)
void sub_469DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00469dd0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17820);  // 0x7CE754 (RpMorph's open count)
    v0 = a0;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17820);  // 0x7CE754 (RpMorph's open count)
}


// sub_469DF0 [morphClose] -- RpMorph's engine close: the open count down; $a0
// 0x00469DF0 sub_469DF0 -- 20 bytes; leaf frame (no stack)
void sub_469DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00469df0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17820);  // 0x7CE754 (RpMorph's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17820);  // 0x7CE754 (RpMorph's open count)
}


// sub_469E10 [morphAtomicConstructor] -- the RpMorph atomic extension constructor: key, position and geometry cleared; the atomic
// 0x00469E10 sub_469E10 -- 28 bytes; leaf frame (no stack)
void sub_469E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00469e10
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17836);  // 0x7CE744 (the RpMorph atomic extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, morphatom::kKey);
    sw(zero, v1, morphatom::kPosition);
    sw(zero, v1, morphatom::kGeometry);
}


// sub_469E30 [morphAtomicCopy] -- the RpMorph atomic extension copy: the state when it belongs to the source's geometry, applied to the interpolator
// ($a0 = the destination atomic, $a1 = the source) When the source state's geometry is the source atomic's geometry
// (+24) the key / position / geometry are copied and, with a key, the atomic's interpolator (+76) takes its start /
// end morph targets, duration, 1 / duration and position -- each store marking the interpolator dirty (flags | 3)
// and, unless bit 2 is set and with a frame (+4), the frame updated (sub_4CB270). Else the state is cleared.
// 0x00469E30 sub_469E30 -- 424 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_469E30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00469e30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    lw(v0, a1, atomic::kGeometry);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, gp, -17836);  // 0x7CE744 (the RpMorph atomic extension offset)
    a0 = addu(a1, v1);
    s1 = addu(s2, v1);
    lw(v1, a0, morphatom::kGeometry);
    s0 = addiu(s2, 76);
    if (v1 == v0) {
        // 0x00469e78
        charge(ctx, 8);
        lw(v0, a0, morphatom::kKey);
        lwc1(f0, a0, morphatom::kPosition);
        sw(v0, s1, morphatom::kKey);
        swc1(f0, s1, morphatom::kPosition);
        sw(v1, s1, morphatom::kGeometry);
        lw(v0, s1, morphatom::kKey);
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x00469e98
            charge(ctx, 11);
            lh(v0, v0, morphkey::kStartMorph);
            sh(v0, s0, interp::kStartMorph);
            lw(v0, s0, interp::kFlags);
            v0 = v0 | 0x3;
            sw(v0, s0, interp::kFlags);
            lw(v0, s0, interp::kFlags);
            v0 = v0 & 0x4;
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                // 0x00469ec4
                charge(ctx, 3);
                lw(a0, s2, atomic::kFrame);
                if (a0 != 0) {
                    // 0x00469ed0
                    charge(ctx, 2);
                    jal(ctx, 0x469ED0u, gen::fn_sub_4CB270_004cb270);
                }
            }
            // 0x00469ed8
            charge(ctx, 12);
            lw(v0, s1, morphatom::kKey);
            lh(v0, v0, morphkey::kEndMorph);
            sh(v0, s0, interp::kEndMorph);
            lw(v0, s0, interp::kFlags);
            v0 = v0 | 0x3;
            sw(v0, s0, interp::kFlags);
            lw(v0, s0, interp::kFlags);
            v0 = v0 & 0x4;
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                // 0x00469f08
                charge(ctx, 3);
                lw(a0, s2, atomic::kFrame);
                if (a0 != 0) {
                    // 0x00469f14
                    charge(ctx, 2);
                    jal(ctx, 0x469F14u, gen::fn_sub_4CB270_004cb270);
                }
            }
            // 0x00469f1c
            charge(ctx, 18);
            lw(v1, s1, morphatom::kKey);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            lwc1(f0, v1, 8);
            swc1(f0, s0, interp::kTime);
            lw(v0, s1, morphatom::kKey);
            lwc1(f0, v0, morphkey::kTime);
            div_s(f0, f1, f0);
            swc1(f0, s0, interp::kRecipTime);
            lw(v0, s0, interp::kFlags);
            v0 = v0 | 0x3;
            sw(v0, s0, interp::kFlags);
            lw(v0, s0, interp::kFlags);
            v0 = v0 & 0x4;
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                // 0x00469f64
                charge(ctx, 3);
                lw(a0, s2, atomic::kFrame);
                if (a0 != 0) {
                    // 0x00469f70
                    charge(ctx, 2);
                    jal(ctx, 0x469F70u, gen::fn_sub_4CB270_004cb270);
                }
            }
            // 0x00469f78
            charge(ctx, 11);
            lwc1(f0, s1, morphatom::kPosition);
            swc1(f0, s0, interp::kPosition);
            lw(v0, s0, interp::kFlags);
            v0 = v0 | 0x3;
            sw(v0, s0, interp::kFlags);
            lw(v0, s0, interp::kFlags);
            v0 = v0 & 0x4;
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                backedge(ctx);
            } else {
                // 0x00469fa4
                charge(ctx, 3);
                lw(a0, s2, atomic::kFrame);
                if (a0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x00469fb0
                    charge(ctx, 4);
                    jal(ctx, 0x469FB0u, gen::fn_sub_4CB270_004cb270);
                    backedge(ctx);
                }
            }
        }
    } else {
        // 0x00469e64
        charge(ctx, 3);
        sw(zero, s1, morphatom::kKey);
        sw(zero, s1, morphatom::kPosition);
        sw(zero, s1, morphatom::kGeometry);
    }
    // 0x00469e70
    charge(ctx, 2);
    v0 = s2;
    // 0x00469fc0
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_469FE0 [morphGeometryDestructor] -- the RpMorph geometry extension destructor: the key array freed (RwFree), count and keys cleared; the geometry
// 0x00469FE0 sub_469FE0 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_469FE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469fe0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    s0 = addu(s1, v0);
    lw(a0, s0, morphgeo::kKeys);
    if (a0 != 0) {
        // 0x0046a008
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x46A010u, v0.u());
    }
    // 0x0046a018 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, s0, morphgeo::kKeys);
    v0 = s1;
    sw(zero, s0, morphgeo::kNumKeys);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_46A040 [morphGeometryCopy] -- the RpMorph geometry extension copy: the keys copied into a new 20 x n block (RwMalloc, memcpy) with the count
// ($a0 = the destination, $a1 = the source) Nothing for a source without keys; the destination, or 0 when the
// allocation fails.
// 0x0046A040 sub_46A040 -- 176 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46A040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a040
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    s0 = addu(a1, v0);
    lw(a0, s0, morphgeo::kNumKeys);
    s1 = addu(s3, v0);
    if (i64(a0) > 0) {
        // 0x0046a078
        charge(ctx, 13);
        v0 = 0x30000;
        v1 = sll(a0, 2);
        a1 = v0 | 0x105;
        v1 = addu(v1, a0);
        v0 = 0x960000;
        s2 = sll(v1, 2);
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = s2;
        jalr(ctx, 0x46A094u, v0.u());
        sw(v0, s1, morphgeo::kKeys);
        lw(v0, s1, morphgeo::kKeys);
        if (v0 != 0) {
            // 0x0046a0b4
            charge(ctx, 8);
            lw(v0, s0, morphgeo::kNumKeys);
            lw(a1, s0, morphgeo::kKeys);
            sw(v0, s1, morphgeo::kNumKeys);
            lw(a0, s1, morphgeo::kKeys);
            a2 = s2;
            jal(ctx, 0x46A0C4u, gen::fn_memcpy_00521250);
            backedge(ctx);
            goto L_0046a070;
        }
        // 0x0046a0ac
        charge(ctx, 2);
        v0 = 0;
        // 0x0046a0d4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0046a070:
    charge(ctx, 2);
    v0 = s3;
    // 0x0046a0d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_46A0F0 [morphGeometryStreamWrite] -- the RpMorph geometry extension stream write: the key count, then each key as 5 words (type, start, end, duration, next index)
// The next key goes as its index ((next - keys) / 20). The stream, or 0 on a write error.
// 0x0046A0F0 sub_46A0F0 -- 320 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46A0F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0046a0f0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x80);
    a1 = addiu(sp, 0xAC);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    s0 = a0;
    s3 = addu(a2, v0);
    lw(v0, s3, morphgeo::kNumKeys);
    a2 = 4;
    link(ctx, 0x46A130u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xAC);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    if (v0 == 0) {
        // 0x0046a158
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0046a140
        charge(ctx, 4);
        lw(v0, sp, 0xAC);
        v0 = slt(0, v0);
        s5 = 0;
        if (v0 != 0) {
            // 0x0046a160
            charge(ctx, 5);
            s4 = 0;
            s2 = addiu(sp, 0x94);
            s1 = addiu(sp, 0x98);
            s6 = addiu(sp, 0x9C);
            s7 = addiu(sp, 0xA0);
            for (;;) {
                // 0x0046a174
                charge(ctx, 27);
                lw(a1, s3, morphgeo::kKeys);
                v0 = 0x66660000;
                v0 = v0 | 0x6667;
                a2 = 20;
                a0 = addu(a1, s4);
                lw(v1, a0, morphkey::kType);
                sw(v1, sp, 0x90);
                lh(v1, a0, morphkey::kStartMorph);
                sw(v1, s2, 0);
                lh(v1, a0, morphkey::kEndMorph);
                sw(v1, s1, 0);
                lwc1(f0, a0, morphkey::kTime);
                swc1(f0, s6, 0);
                lw(v1, a0, morphkey::kNext);
                v1 = subu(v1, a1);
                mult(zero, v0, v1);
                v1 = srl(v1, 31);
                mfhi(v0);
                a0 = s0;
                a1 = addiu(sp, 0x90);
                v0 = sra(v0, 3);
                v0 = addu(v0, v1);
                link(ctx, 0x46A1D0u);  // $ra first: the delay slot below depends on it
                sw(v0, s7, 0);
                call(ctx, gen::fn_sub_4C53F0_004c53f0);
                if (v0 == 0) {
                    goto L_0046a1e0_6;
                }
                // 0x0046a1e8
                charge(ctx, 5);
                lw(v0, sp, 0xAC);
                s5 = addiu(s5, 1);
                v0 = slt(s5, v0);
                s4 = addiu(s4, 20);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0046a1fc
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x0046a150
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x0046a204 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
    return;
L_0046a1e0_6:
    charge(ctx, 2);
    v0 = 0;
    // 0x0046a204 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
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


// sub_46A230 [morphGeometryStreamRead] -- the RpMorph geometry extension stream read: the key count, the keys (RpMorphGeometryCreateInterpolators), each read as 5 words
// Each key: type, start / end morph targets (s16), duration, 1 / duration computed (+12), the next key from its
// index. The stream, or 0 when a key is short (fewer than 20 bytes read).
// 0x0046A230 sub_46A230 -- 392 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46A230(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0046a230
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x80);
    a1 = addiu(sp, 0xAC);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    s0 = a0;
    a2 = 4;
    s3 = addu(s1, v0);
    jal(ctx, 0x46A26Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x0046a290
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0046a27c
        charge(ctx, 3);
        lw(a1, sp, 0xAC);
        if (i64(a1) > 0) {
            // 0x0046a298
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x46A298u, gen::fn_sub_46A470_0046a470);
            if (v0 != 0) {
                // 0x0046a2a8
                charge(ctx, 4);
                lw(v0, sp, 0xAC);
                at = slt(0, v0);
                s5 = 0;
                if (at == 0) {
                    backedge(ctx);
                    goto L_0046a288;
                }
                // 0x0046a2b8
                charge(ctx, 5);
                s4 = 0;
                s2 = addiu(sp, 0x94);
                s6 = addiu(sp, 0x98);
                s1 = addiu(sp, 0x9C);
                s7 = addiu(sp, 0xA0);
                for (;;) {
                    // 0x0046a2cc
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = addiu(sp, 0x90);
                    a2 = 20;
                    jal(ctx, 0x46A2D4u, gen::fn_sub_4C5250_004c5250);
                    v1 = 20;
                    if (v0 != v1) {
                        goto L_0046a2e8_8;
                    }
                    // 0x0046a2f0
                    charge(ctx, 36);
                    v0 = 0x3F800000;
                    lw(v1, sp, 0x90);
                    mtc1(v0, f1);
                    s5 = addiu(s5, 1);
                    lw(v0, s3, morphgeo::kKeys);
                    v0 = addu(v0, s4);
                    sw(v1, v0, morphkey::kType);
                    lw(v0, s3, morphgeo::kKeys);
                    lw(v1, s2, 0);
                    v0 = addu(v0, s4);
                    sh(v1, v0, morphkey::kStartMorph);
                    lw(v0, s3, morphgeo::kKeys);
                    lw(v1, s6, 0);
                    v0 = addu(v0, s4);
                    sh(v1, v0, morphkey::kEndMorph);
                    lw(v0, s3, morphgeo::kKeys);
                    lwc1(f0, s1, 0);
                    v0 = addu(v0, s4);
                    swc1(f0, v0, morphkey::kTime);
                    lwc1(f0, s1, 0);
                    lw(v0, s3, morphgeo::kKeys);
                    div_s(f0, f1, f0);
                    v0 = addu(v0, s4);
                    swc1(f0, v0, 12);
                    lw(a0, s7, 0);
                    lw(a1, s3, morphgeo::kKeys);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v0 = addu(a1, s4);
                    v1 = sll(v1, 2);
                    v1 = addu(a1, v1);
                    sw(v1, v0, morphkey::kNext);
                    lw(v0, sp, 0xAC);
                    v0 = slt(s5, v0);
                    s4 = addiu(s4, 20);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046a380
                charge(ctx, 2);
                backedge(ctx);
                goto L_0046a288;
            }
            // 0x0046a388
            charge(ctx, 1);
            v0 = 0;
            // 0x0046a38c (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(ra, sp, 0x80);
            lq(s7, sp, 0x70);
            lq(s6, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xB0);
            return;
        }
    L_0046a288:
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x0046a38c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
    return;
L_0046a2e8_8:
    charge(ctx, 2);
    v0 = 0;
    // 0x0046a38c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
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


// sub_46A3C0 [morphGeometryStreamSize] -- the RpMorph geometry extension stream size: 20 x keys + 4, or 0 without keys
// 0x0046A3C0 sub_46A3C0 -- 56 bytes; leaf frame (no stack)
void sub_46A3C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0046a3c0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    if (a0 == 0) {
        // 0x0046a3ec
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0046a3d4
        charge(ctx, 6);
        v0 = sll(a0, 2);
        v1 = 4;
        v0 = addu(v0, a0);
        v0 = sll(v0, 2);
        v0 = addu(v1, v0);
    }
    // 0x0046a3f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_46A400 [morphDefaultKeyEnd] -- RpMorph's default key-end callback: the atomic's current key becomes that key's next (+16); returns it
// 0x0046A400 sub_46A400 -- 52 bytes; leaf frame (no stack)
void sub_46A400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0046a400
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v0, gp, -17836);  // 0x7CE744 (the RpMorph atomic extension offset)
    mtc1(zero, f1);
    v1 = addu(a0, v0);
    lw(v0, v1, 0);
    lwc1(f0, v0, 8);
    sub_s(f0, f12, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x0046a424
        charge(ctx, 1);
        mov_s(f0, f1);
    }
    // 0x0046a428 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lw(v0, v0, 16);
    sw(v0, v1, 0);
}


// sub_46A440 [morphGeometryConstructor] -- the RpMorph geometry extension constructor: no keys, the key-end callback sub_46A400; the geometry
// 0x0046A440 sub_46A440 -- 36 bytes; leaf frame (no stack)
void sub_46A440(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0046a440
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(a1, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    v0 = a0;
    v1 = 0x470000;
    v1 = addiu(v1, -23552);  // &sub_46A400
    a0 = addu(a0, a1);
    sw(zero, a0, morphgeo::kNumKeys);
    sw(zero, a0, morphgeo::kKeys);
    sw(v1, a0, morphgeo::kKeyEnd);
}


// sub_46A470 [RpMorphGeometryCreateInterpolators] -- gives a geometry $a1 zeroed interpolation keys: the old array freed, RwMalloc(20 x n), the count; the geometry, or 0
// 0x0046A470 sub_46A470 -- 184 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46A470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a470
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
    s0 = addu(s3, v0);
    lw(a0, s0, morphgeo::kKeys);
    s2 = a1;
    if (a0 != 0) {
        // 0x0046a4a0
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x46A4A8u, v0.u());
        sw(zero, s0, morphgeo::kNumKeys);
        sw(zero, s0, morphgeo::kKeys);
    }
    // 0x0046a4b8
    charge(ctx, 13);
    v0 = 0x30000;
    v1 = sll(s2, 2);
    a1 = v0 | 0x105;
    v1 = addu(v1, s2);
    v0 = 0x960000;
    s1 = sll(v1, 2);
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = s1;
    jalr(ctx, 0x46A4D4u, v0.u());
    sw(v0, s0, morphgeo::kKeys);
    lw(v0, s0, morphgeo::kKeys);
    if (v0 != 0) {
        // 0x0046a4f4
        charge(ctx, 6);
        sw(s2, s0, morphgeo::kNumKeys);
        a2 = s1;
        lw(a0, s0, morphgeo::kKeys);
        a1 = 0;
        jal(ctx, 0x46A500u, gen::fn_memset_00521408);
        v0 = s3;
    } else {
        // 0x0046a4ec
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0046a50c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_46A530 [RpMorphPluginAttach] -- registers RpMorph (plugin 0x105): the engine open / close, the 12-byte atomic and geometry extensions and the geometry's streams
// The offsets go to gp 0x7CE744 / 0x7CE748. 1, or 0 at the first registration that fails.
// 0x0046A530 sub_46A530 -- 204 bytes; frame 0x10: ra sp+0x0
void sub_46A530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a530
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x470000;
    a3 = 0x470000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 261;
    a2 = addiu(a2, -25136);  // &sub_469DD0
    a3 = addiu(a3, -25104);  // &sub_469DF0
    jal(ctx, 0x46A54Cu, gen::fn_sub_4CA520_004ca520);
    if (i64(v0) >= 0) {
        // 0x0046a564
        charge(ctx, 10);
        a2 = 0x470000;
        t0 = 0x470000;
        a2 = addiu(a2, -25072);  // &sub_469E10
        a0 = 12;
        a1 = 261;
        t0 = addiu(t0, -25040);  // &sub_469E30
        a3 = a2;
        jal(ctx, 0x46A57Cu, gen::fn_sub_492C30_00492c30);
        sw(v0, gp, -17836);  // 0x7CE744 (the RpMorph atomic extension offset)
        if (i64(v0) >= 0) {
            // 0x0046a594
            charge(ctx, 11);
            a2 = 0x470000;
            a3 = 0x470000;
            t0 = 0x470000;
            a0 = 12;
            a1 = 261;
            a2 = addiu(a2, -23488);  // &sub_46A440
            a3 = addiu(a3, -24608);  // &sub_469FE0
            t0 = addiu(t0, -24512);  // &sub_46A040
            jal(ctx, 0x46A5B0u, gen::fn_sub_493C50_00493c50);
            sw(v0, gp, -17832);  // 0x7CE748 (the RpMorph geometry extension offset)
            if (i64(v0) >= 0) {
                // 0x0046a5c8
                charge(ctx, 10);
                a1 = 0x470000;
                a2 = 0x470000;
                a3 = 0x470000;
                a0 = 261;
                a1 = addiu(a1, -24016);  // &sub_46A230
                a2 = addiu(a2, -24336);  // &sub_46A0F0
                a3 = addiu(a3, -23616);  // &sub_46A3C0
                jal(ctx, 0x46A5E0u, gen::fn_sub_493C80_00493c80);
                v0 = slt(v0, 0);
                v0 = v0 ^ 0x1;
            } else {
                // 0x0046a5c0
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0046a58c
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0046a55c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0046a5f0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_46A660 [pdsClose] -- the PDS plugin's engine close: the open count down; at 0 the pipe registry destroyed (sub_46A9E0); $a0
// 0x0046A660 sub_46A660 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a660
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    lw(v1, v1, -15288);  // 0x95C448
    s0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, v0, -15288);  // 0x95C448
    if (v1 == 0) {
        // 0x0046a690
        charge(ctx, 5);
        a0 = 0x960000;
        a0 = addiu(a0, -15284);  // &0x95C44C (the PDS pipe registry {entries, count, capacity, 0})
        jal(ctx, 0x46A694u, gen::fn_sub_46A9E0_0046a9e0);
        backedge(ctx);
    }
    // 0x0046a688
    charge(ctx, 2);
    v0 = s0;
    // 0x0046a6a4
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_46A6C0 [pdsMaterialRights] -- the PDS rights callback of materials: the material's pipeline (+8) from its PDS id
// Registered as a stream-rights callback: ($a0 = the object, $a3 = the id streamed with it) the object's pipeline = RpPDSGetPipe(id); 1.
// 0x0046A6C0 sub_46A6C0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A6C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a6c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a3;
    jal(ctx, 0x46A6D0u, gen::fn_RpPDSGetPipe_0046a890);
    sw(v0, s0, 8);
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_46A6F0 [pdsAtomicRights] -- the PDS rights callback of atomics: the atomic's pipeline (+108) from its PDS id
// Registered as a stream-rights callback: ($a0 = the object, $a3 = the id streamed with it) the object's pipeline = RpPDSGetPipe(id); 1.
// 0x0046A6F0 sub_46A6F0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a6f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a3;
    jal(ctx, 0x46A700u, gen::fn_RpPDSGetPipe_0046a890);
    sw(v0, s0, 108);
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_46A720 [pdsSectorRights] -- the PDS rights callback of world sectors: the sector's pipeline (+124) from its PDS id
// Registered as a stream-rights callback: ($a0 = the object, $a3 = the id streamed with it) the object's pipeline = RpPDSGetPipe(id); 1.
// 0x0046A720 sub_46A720 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a720
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a3;
    jal(ctx, 0x46A730u, gen::fn_RpPDSGetPipe_0046a890);
    sw(v0, s0, 124);
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_46A750 [RpPDSPluginAttach] -- registers the PDS plugin (0x131): the pipe registry for $a0 pipes, the engine open / close, the material / atomic / sector rights callbacks
// The registry (0x95C44C) is set up first (sub_46A970) and $a0 kept at 0x95C45C; the material, atomic and world-sector
// plugins are registered with size 0 only to carry the rights callbacks. Always 1.
// 0x0046A750 sub_46A750 -- 216 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a750
    enter(ctx, 54);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x960000;
    a1 = s0;
    a0 = addiu(a0, -15284);  // &0x95C44C (the PDS pipe registry {entries, count, capacity, 0})
    jal(ctx, 0x46A768u, gen::fn_sub_46A970_0046a970);
    v0 = 0x960000;
    a2 = 0x470000;
    a3 = 0x470000;
    a0 = 0;
    sw(s0, v0, -15268);  // 0x95C45C (the PDS registry's requested size)
    a1 = 305;
    a2 = addiu(a2, -23040);  // &sub_46A600
    a3 = addiu(a3, -22944);  // &sub_46A660
    jal(ctx, 0x46A78Cu, gen::fn_sub_4CA520_004ca520);
    v1 = 0x960000;
    a0 = 0;
    sw(v0, v1, -15296);  // 0x95C440 (the PDS plugin's engine offset)
    a1 = 305;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x46A7ACu, gen::fn_sub_494DB0_00494db0);
    a0 = 0;
    a1 = 305;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x46A7C4u, gen::fn_sub_492C30_00492c30);
    a0 = 0;
    a1 = 305;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x46A7DCu, gen::fn_sub_499250_00499250);
    a1 = 0x470000;
    a0 = 305;
    a1 = addiu(a1, -22848);  // &sub_46A6C0
    jal(ctx, 0x46A7ECu, gen::fn_sub_494E10_00494e10);
    a1 = 0x470000;
    a0 = 305;
    a1 = addiu(a1, -22800);  // &sub_46A6F0
    jal(ctx, 0x46A7FCu, gen::fn_sub_492CE0_00492ce0);
    a1 = 0x470000;
    a0 = 305;
    a1 = addiu(a1, -22752);  // &sub_46A720
    jal(ctx, 0x46A80Cu, gen::fn_sub_4992D0_004992d0);
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_46A970 [pdsRegistryInit] -- sets up a PDS pipe registry: RwMalloc(20 x n) (n = $a1, 9 when 0), count 0, capacity n; the registry
// 0x0046A970 sub_46A970 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46A970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a970
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (a1 == 0) {
        // 0x0046a990
        charge(ctx, 1);
        s0 = 9;
    } else {
        // 0x0046a988
        charge(ctx, 2);
        s0 = a1;
    }
    // 0x0046a994
    charge(ctx, 18);
    v0 = 0x1040000;
    v1 = sll(s0, 2);
    a1 = v0 | 0x131;  // &0x1040131
    v1 = addu(v1, s0);
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = sll(v1, 2);
    jalr(ctx, 0x46A9ACu, v0.u());
    sw(v0, s1, pdsreg::kEntries);
    sw(s0, s1, pdsreg::kCapacity);
    v0 = s1;
    sw(zero, s1, pdsreg::kCount);
    sw(zero, s1, pdsreg::kWord12);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_46A9E0 [pdsRegistryDestroy] -- destroys a PDS pipe registry: each entry's pipeline (RxPipelineDestroy), the entry array (RwFree), the four words cleared
// 0x0046A9E0 sub_46A9E0 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46A9E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0046a9e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    at = sltu(0, v0);
    s1 = 0;
    if (at != 0) {
        // 0x0046aa08
        charge(ctx, 1);
        s0 = 0;
        for (;;) {
            // 0x0046aa0c
            charge(ctx, 5);
            lw(v0, s2, pdsreg::kEntries);
            v0 = addu(v0, s0);
            lw(a0, v0, 16);
            if (a0 != 0) {
                // 0x0046aa20
                charge(ctx, 2);
                jal(ctx, 0x46AA20u, gen::fn_sub_4F3010_004f3010);
            }
            // 0x0046aa28
            charge(ctx, 5);
            lw(v0, s2, pdsreg::kCount);
            s1 = addiu(s1, 1);
            v0 = sltu(s1, v0);
            s0 = addiu(s0, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046aa3c
        charge(ctx, 1);
    }
    // 0x0046aa40
    charge(ctx, 14);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x46AA48u);  // $ra = the return address
    lw(a0, s2, pdsreg::kEntries);
    call_ptr(ctx, jt);
    sw(zero, s2, pdsreg::kCapacity);
    sw(zero, s2, pdsreg::kCount);
    sw(zero, s2, pdsreg::kEntries);
    sw(zero, s2, pdsreg::kWord12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4734B0 [ptankAtomicConstructor] -- the PTank atomic extension constructor: no tank data; the atomic
// 0x004734B0 sub_4734B0 -- 20 bytes; leaf frame (no stack)
void sub_4734B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004734b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17792);  // 0x7CE770 (the PTank atomic extension offset)
    v0 = a0;
    v1 = addu(a0, v1);
    sw(zero, v1, 0);
}


// sub_473590 [ptankPluginAttach] -- registers the PTank plugin (0x12F): the engine open / close (sub_474BB0 / sub_474C60) and the 4-byte atomic extension (destructor sub_4734D0)
// The offsets go to gp 0x7CE774 / 0x7CE770. 1, or 0 when a registration fails.
// 0x00473590 sub_473590 -- 108 bytes; frame 0x10: ra sp+0x0
void sub_473590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00473590
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x470000;
    a3 = 0x470000;
    sd(ra, sp, 0x0);
    a0 = 4;
    a1 = 303;
    a2 = addiu(a2, 19376);  // &sub_474BB0
    a3 = addiu(a3, 19552);  // &sub_474C60
    jal(ctx, 0x4735ACu, gen::fn_sub_4CA520_004ca520);
    sw(v0, gp, -17788);  // 0x7CE774 (the PTank engine offset)
    if (i64(v0) >= 0) {
        // 0x004735c4
        charge(ctx, 11);
        a2 = 0x470000;
        a3 = 0x470000;
        a0 = 4;
        a1 = 303;
        a2 = addiu(a2, 13488);  // &sub_4734B0
        a3 = addiu(a3, 13520);  // &sub_4734D0
        t0 = 0;
        jal(ctx, 0x4735DCu, gen::fn_sub_492C30_00492c30);
        sw(v0, gp, -17792);  // 0x7CE770 (the PTank atomic extension offset)
        v0 = slt(v0, 0);
        v0 = v0 ^ 0x1;
    } else {
        // 0x004735bc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004735f0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_473600 [ptankAllocSeparate] -- allocates a tank's component arrays one after the other (a structure of arrays) for the format $a1
// ($a0 = the tank data, $a1 = the format) The format's low 9 bits rewritten, the component count (+160) and +60
// cleared; one RwMalloc of the summed sizes + 16 (hint 0x3012F), 16-aligned; each component's {pointer, stride}
// pair at +84.. filled in the order position, matrix, normal, size, colour, vertex colours, rotation, tex coords;
// +164 cleared, the block at +12. 1, or 0 when the allocation fails.
// The components by flag (RpPTank's data flags): position 0x1 (12 bytes), matrix 0x8 (64), normal 0x10 (12), size 0x4 (8), colour 0x2 (4), vertex colours 0x40 (16), 2-D rotation 0x20 (4), two tex coords 0x80 (16), four 0x100 (32); the strides come from the table 0x7BC900.
// 0x00473600 sub_473600 -- 1296 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_473600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00473600: the format's component flags
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    v0 = a1 & 0x1;
    sd(ra, sp, 0x90);
    v1 = v0 ^ 0x1;
    sq(fp, sp, 0x80);
    v0 = a1 & 0x2;
    sq(s7, sp, 0x70);
    v0 = v0 ^ 0x2;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = sltiu(v1, 1);
    s3 = sltiu(v0, 1);
    sq(s2, sp, 0x20);
    v0 = a1 & 0x4;
    sq(s1, sp, 0x10);
    v1 = v0 ^ 0x4;
    sq(s0, sp, 0x0);
    v0 = a1 & 0x8;
    s2 = sltiu(v1, 1);
    v0 = v0 ^ 0x8;
    lw(a2, a0, ptankdata::kFormat);
    s1 = sltiu(v0, 1);
    sw(zero, sp, 0xB0);
    v0 = a1 & 0x10;
    v1 = v0 ^ 0x10;
    v0 = a1 & 0x20;
    s0 = sltiu(v1, 1);
    v0 = v0 ^ 0x20;
    s6 = sltiu(v0, 1);
    v0 = a1 & 0x40;
    v1 = v0 ^ 0x40;
    v0 = a1 & 0x80;
    s7 = sltiu(v1, 1);
    v0 = v0 ^ 0x80;
    fp = sltiu(v0, 1);
    v0 = a1 & 0x100;
    v1 = v0 ^ 0x100;
    a1 = si(-512);
    v1 = sltiu(v1, 1);
    a1 = a2 & a1;
    sq(v1, sp, 0xA0);
    v0 = 0;
    sw(a1, a0, ptankdata::kFormat);
    v1 = 1;
    sw(zero, a0, ptankdata::kNumComponents);
    sw(zero, a0, ptankdata::kWord60);
    if (s4 == v1) {
        // 0x004737f4
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14080);  // 0x7BC900 (PTank: the component strides by flag (position .. 4 tex coords))
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x1;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x004736c8
    charge(ctx, 3);
    v1 = 1;
    if (s1 == v1) {
        // 0x00473824
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14076);  // 0x7BC904
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x8;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x004736d4
    charge(ctx, 3);
    v1 = 1;
    if (s0 == v1) {
        // 0x00473854
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14072);  // 0x7BC908
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x10;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x004736e0
    charge(ctx, 3);
    v1 = 1;
    if (s2 == v1) {
        // 0x00473884
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14068);  // 0x7BC90C
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x4;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x004736ec
    charge(ctx, 3);
    v1 = 1;
    if (s3 == v1) {
        // 0x004738b4
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14064);  // 0x7BC910
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x2;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x004736f8
    charge(ctx, 3);
    v1 = 1;
    if (s7 == v1) {
        // 0x004738e4
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14060);  // 0x7BC914
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x40;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x00473704
    charge(ctx, 3);
    v1 = 1;
    if (s6 == v1) {
        // 0x00473914
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14056);  // 0x7BC918
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x20;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x00473710
    charge(ctx, 3);
    v1 = 1;
    if (fp == v1) {
        // 0x00473944
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14052);  // 0x7BC91C
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x80;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x0047371c
    charge(ctx, 4);
    lq(v1, sp, 0xA0);
    a0 = 1;
    if (v1 == a0) {
        // 0x00473974
        charge(ctx, 12);
        v1 = 0x7C0000;
        lw(a1, s5, ptankdata::kNumComponents);
        lw(a0, v1, -14048);  // 0x7BC920
        v1 = addiu(a1, 1);
        sw(v1, s5, ptankdata::kNumComponents);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x100;
        sw(v1, s5, ptankdata::kFormat);
        lw(v1, s5, ptankdata::kNumParticles);
        mult(v1, a0, v1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x0047372c: one block for every component
    charge(ctx, 9);
    a0 = addiu(v0, 16);
    v0 = 0x30000;
    a1 = v0 | 0x12F;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    jalr(ctx, 0x473740u, v0.u());
    if (v0 != 0) {
        // 0x00473750: each component's {pointer, stride}
        charge(ctx, 6);
        a0 = addiu(v0, 15);
        v1 = si(-16);
        v1 = a0 & v1;
        a1 = 1;
        a0 = 0;
        if (s4 == a1) {
            // 0x004739a4
            charge(ctx, 9);
            sw(v1, s5, ptankdata::kPosition);
            a1 = 12;
            sw(a1, s5, ptankdata::kPositionStride);
            a1 = 0x7C0000;
            lw(a2, a1, -14080);  // 0x7BC900 (PTank: the component strides by flag (position .. 4 tex coords))
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x00473768
        charge(ctx, 3);
        a1 = 1;
        if (s1 == a1) {
            // 0x004739c8
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 64;
            sw(a1, s5, ptankdata::kMatrix);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kMatrixStride);
            lw(a2, a1, -14076);  // 0x7BC904
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x00473774
        charge(ctx, 3);
        a1 = 1;
        if (s0 == a1) {
            // 0x004739f0
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 12;
            sw(a1, s5, ptankdata::kNormal);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kNormalStride);
            lw(a2, a1, -14072);  // 0x7BC908
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x00473780
        charge(ctx, 3);
        a1 = 1;
        if (s2 == a1) {
            // 0x00473a18
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 8;
            sw(a1, s5, ptankdata::kPartSize);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kPartSizeStride);
            lw(a2, a1, -14068);  // 0x7BC90C
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x0047378c
        charge(ctx, 3);
        a1 = 1;
        if (s3 == a1) {
            // 0x00473a40
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 4;
            sw(a1, s5, ptankdata::kColor);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kColorStride);
            lw(a2, a1, -14064);  // 0x7BC910
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x00473798
        charge(ctx, 3);
        a1 = 1;
        if (s7 == a1) {
            // 0x00473a68
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 16;
            sw(a1, s5, ptankdata::kVtxColor);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kVtxColorStride);
            lw(a2, a1, -14060);  // 0x7BC914
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x004737a4
        charge(ctx, 3);
        a1 = 1;
        if (s6 == a1) {
            // 0x00473a90
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 4;
            sw(a1, s5, ptankdata::kRotate);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kRotateStride);
            lw(a2, a1, -14056);  // 0x7BC918
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x004737b0
        charge(ctx, 3);
        a1 = 1;
        if (fp == a1) {
            // 0x00473ab8
            charge(ctx, 10);
            a1 = addu(v1, a0);
            a2 = 16;
            sw(a1, s5, ptankdata::kVtx2Tex);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kVtx2TexStride);
            lw(a2, a1, -14052);  // 0x7BC91C
            lw(a1, s5, ptankdata::kNumParticles);
            mult(a1, a2, a1);
            a0 = addu(a0, a1);
            backedge(ctx);
        }
        // 0x004737bc
        charge(ctx, 4);
        lq(a1, sp, 0xA0);
        a2 = 1;
        if (a1 == a2) {
            // 0x004737cc
            charge(ctx, 4);
            a0 = addu(v1, a0);
            v1 = 32;
            sw(a0, s5, ptankdata::kVtx4Tex);
            sw(v1, s5, ptankdata::kVtx4TexStride);
        }
        // 0x004737dc
        charge(ctx, 4);
        sw(zero, s5, ptankdata::kWord164);
        v1 = 1;
        sw(v1, sp, 0xB0);
        sw(v0, s5, ptankdata::kBlock);
    }
    // 0x004737ec
    charge(ctx, 2);
    lw(v0, sp, 0xB0);
    // 0x00473ae0
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


// sub_473B10 [ptankAllocInterleaved] -- allocates a tank's components interleaved (an array of structures) for the format $a1
// As sub_473600, but every component's pointer is its offset into one record per particle and every stride the
// record size.
// The components by flag (RpPTank's data flags): position 0x1 (12 bytes), matrix 0x8 (64), normal 0x10 (12), size 0x4 (8), colour 0x2 (4), vertex colours 0x40 (16), 2-D rotation 0x20 (4), two tex coords 0x80 (16), four 0x100 (32); the strides come from the table 0x7BC900.
// 0x00473B10 sub_473B10 -- 1176 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_473B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00473b10
    enter(ctx, 49);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    v0 = a1 & 0x1;
    sd(ra, sp, 0x90);
    v1 = v0 ^ 0x1;
    sq(fp, sp, 0x80);
    v0 = a1 & 0x2;
    sq(s7, sp, 0x70);
    v0 = v0 ^ 0x2;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = sltiu(v1, 1);
    s3 = sltiu(v0, 1);
    sq(s2, sp, 0x20);
    v0 = a1 & 0x4;
    sq(s1, sp, 0x10);
    v1 = v0 ^ 0x4;
    sq(s0, sp, 0x0);
    v0 = a1 & 0x8;
    s2 = sltiu(v1, 1);
    v0 = v0 ^ 0x8;
    lw(a2, a0, ptankdata::kFormat);
    s1 = sltiu(v0, 1);
    sw(zero, sp, 0xB0);
    v0 = a1 & 0x10;
    v1 = v0 ^ 0x10;
    v0 = a1 & 0x20;
    s0 = sltiu(v1, 1);
    v0 = v0 ^ 0x20;
    s6 = sltiu(v0, 1);
    v0 = a1 & 0x40;
    v1 = v0 ^ 0x40;
    v0 = a1 & 0x80;
    s7 = sltiu(v1, 1);
    v0 = v0 ^ 0x80;
    fp = sltiu(v0, 1);
    v0 = a1 & 0x100;
    v1 = v0 ^ 0x100;
    a1 = si(-512);
    v1 = sltiu(v1, 1);
    a1 = a2 & a1;
    sq(v1, sp, 0xA0);
    v0 = 0;
    sw(a1, a0, ptankdata::kFormat);
    v1 = 1;
    sw(zero, a0, ptankdata::kNumComponents);
    if (s4 == v1) {
        // 0x00473d14
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14080);  // 0x7BC900 (PTank: the component strides by flag (position .. 4 tex coords))
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x1;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473bd4
    charge(ctx, 3);
    v1 = 1;
    if (s1 == v1) {
        // 0x00473d3c
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14076);  // 0x7BC904
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x8;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473be0
    charge(ctx, 3);
    v1 = 1;
    if (s0 == v1) {
        // 0x00473d64
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14072);  // 0x7BC908
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x10;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473bec
    charge(ctx, 3);
    v1 = 1;
    if (s2 == v1) {
        // 0x00473d8c
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14068);  // 0x7BC90C
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x4;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473bf8
    charge(ctx, 3);
    v1 = 1;
    if (s3 == v1) {
        // 0x00473db4
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14064);  // 0x7BC910
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x2;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473c04
    charge(ctx, 3);
    v1 = 1;
    if (s7 == v1) {
        // 0x00473ddc
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14060);  // 0x7BC914
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x40;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473c10
    charge(ctx, 3);
    v1 = 1;
    if (s6 == v1) {
        // 0x00473e04
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14056);  // 0x7BC918
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x20;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473c1c
    charge(ctx, 3);
    v1 = 1;
    if (fp == v1) {
        // 0x00473e2c
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14052);  // 0x7BC91C
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x80;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473c28
    charge(ctx, 4);
    lq(v1, sp, 0xA0);
    a0 = 1;
    if (v1 == a0) {
        // 0x00473e54
        charge(ctx, 10);
        lw(a0, s5, ptankdata::kNumComponents);
        v1 = 0x7C0000;
        lw(v1, v1, -14048);  // 0x7BC920
        a0 = addiu(a0, 1);
        sw(a0, s5, ptankdata::kNumComponents);
        v0 = addu(v0, v1);
        lw(v1, s5, ptankdata::kFormat);
        v1 = v1 | 0x100;
        sw(v1, s5, ptankdata::kFormat);
        backedge(ctx);
    }
    // 0x00473c38
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x00473c40
        charge(ctx, 3);
        v1 = addiu(v0, 15);
        v0 = si(-16);
        v0 = v1 & v0;
    }
    // 0x00473c4c
    charge(ctx, 10);
    sw(v0, s5, ptankdata::kWord164);
    lw(v1, s5, ptankdata::kNumParticles);
    mult(v1, v0, v1);
    a1 = 0x30000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = addiu(v1, 16);
    jalr(ctx, 0x473C64u, v0.u());
    if (v0 != 0) {
        // 0x00473c74
        charge(ctx, 6);
        a0 = addiu(v0, 15);
        v1 = si(-16);
        v1 = a0 & v1;
        a1 = 1;
        a0 = 0;
        if (s4 == a1) {
            // 0x00473e7c
            charge(ctx, 7);
            sw(v1, s5, ptankdata::kPosition);
            a1 = 0x7C0000;
            lw(a1, a1, -14080);  // 0x7BC900 (PTank: the component strides by flag (position .. 4 tex coords))
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kPositionStride);
            backedge(ctx);
        }
        // 0x00473c8c
        charge(ctx, 3);
        a1 = 1;
        if (s1 == a1) {
            // 0x00473e98
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kMatrix);
            lw(a1, a1, -14076);  // 0x7BC904
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kMatrixStride);
            backedge(ctx);
        }
        // 0x00473c98
        charge(ctx, 3);
        a1 = 1;
        if (s0 == a1) {
            // 0x00473eb8
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kNormal);
            lw(a1, a1, -14072);  // 0x7BC908
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kNormalStride);
            backedge(ctx);
        }
        // 0x00473ca4
        charge(ctx, 3);
        a1 = 1;
        if (s2 == a1) {
            // 0x00473ed8
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kPartSize);
            lw(a1, a1, -14068);  // 0x7BC90C
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kPartSizeStride);
            backedge(ctx);
        }
        // 0x00473cb0
        charge(ctx, 3);
        a1 = 1;
        if (s3 == a1) {
            // 0x00473ef8
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kColor);
            lw(a1, a1, -14064);  // 0x7BC910
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kColorStride);
            backedge(ctx);
        }
        // 0x00473cbc
        charge(ctx, 3);
        a1 = 1;
        if (s7 == a1) {
            // 0x00473f18
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kVtxColor);
            lw(a1, a1, -14060);  // 0x7BC914
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kVtxColorStride);
            backedge(ctx);
        }
        // 0x00473cc8
        charge(ctx, 3);
        a1 = 1;
        if (s6 == a1) {
            // 0x00473f38
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kRotate);
            lw(a1, a1, -14056);  // 0x7BC918
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kRotateStride);
            backedge(ctx);
        }
        // 0x00473cd4
        charge(ctx, 3);
        a1 = 1;
        if (fp == a1) {
            // 0x00473f58
            charge(ctx, 8);
            a2 = addu(v1, a0);
            a1 = 0x7C0000;
            sw(a2, s5, ptankdata::kVtx2Tex);
            lw(a1, a1, -14052);  // 0x7BC91C
            lw(a2, s5, ptankdata::kWord164);
            a0 = addu(a0, a1);
            sw(a2, s5, ptankdata::kVtx2TexStride);
            backedge(ctx);
        }
        // 0x00473ce0
        charge(ctx, 4);
        lq(a1, sp, 0xA0);
        a2 = 1;
        if (a1 == a2) {
            // 0x00473cf0
            charge(ctx, 4);
            v1 = addu(v1, a0);
            sw(v1, s5, ptankdata::kVtx4Tex);
            lw(v1, s5, ptankdata::kWord164);
            sw(v1, s5, ptankdata::kVtx4TexStride);
        }
        // 0x00473d00
        charge(ctx, 3);
        sw(v0, s5, ptankdata::kBlock);
        v0 = 1;
        sw(v0, sp, 0xB0);
    }
    // 0x00473d0c
    charge(ctx, 2);
    lw(v0, sp, 0xB0);
    // 0x00473f78
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


// sub_4753D0 [ptankDataSize] -- the bytes of a tank's components for $a0 particles in the format $a1, each array rounded to 16 (+79 for colour and size)
// The components by flag (RpPTank's data flags): position 0x1 (12 bytes), matrix 0x8 (64), normal 0x10 (12), size 0x4 (8), colour 0x2 (4), vertex colours 0x40 (16), 2-D rotation 0x20 (4), two tex coords 0x80 (16), four 0x100 (32); the strides come from the table 0x7BC900.
// 0x004753D0 sub_4753D0 -- 360 bytes; leaf frame (no stack)
void sub_4753D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004753d0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = a1 & 0x1;
    v0 = 0;
    if (v1 != 0) {
        // 0x004753dc
        charge(ctx, 5);
        a2 = sll(a0, 4);
        v1 = si(-16);
        a2 = addiu(a2, 15);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x004753f0
    charge(ctx, 3);
    v1 = a1 & 0x8;
    if (v1 != 0) {
        // 0x004753fc
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14076);  // 0x7BC904
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 15);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x00475418
    charge(ctx, 3);
    v1 = a1 & 0x10;
    if (v1 != 0) {
        // 0x00475424
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14072);  // 0x7BC908
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 15);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x00475440
    charge(ctx, 3);
    v1 = a1 & 0x4;
    if (v1 != 0) {
        // 0x0047544c
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14068);  // 0x7BC90C
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 79);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x00475468
    charge(ctx, 3);
    v1 = a1 & 0x2;
    if (v1 != 0) {
        // 0x00475474
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14064);  // 0x7BC910
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 79);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x00475490
    charge(ctx, 3);
    v1 = a1 & 0x40;
    if (v1 != 0) {
        // 0x0047549c
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14060);  // 0x7BC914
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 15);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x004754b8
    charge(ctx, 3);
    v1 = a1 & 0x20;
    if (v1 != 0) {
        // 0x004754c4
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14056);  // 0x7BC918
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 15);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x004754e0
    charge(ctx, 3);
    v1 = a1 & 0x80;
    if (v1 != 0) {
        // 0x004754ec
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14052);  // 0x7BC91C
        mult(a2, a0, v1);
        v1 = si(-16);
        a2 = addiu(a2, 15);
        v1 = a2 & v1;
        v0 = addu(v0, v1);
    }
    // 0x00475508
    charge(ctx, 3);
    v1 = a1 & 0x100;
    if (v1 != 0) {
        // 0x00475514
        charge(ctx, 7);
        v1 = 0x7C0000;
        lw(v1, v1, -14048);  // 0x7BC920
        mult(a0, a0, v1);
        v1 = si(-16);
        a0 = addiu(a0, 15);
        v1 = a0 & v1;
        v0 = addu(v0, v1);
    }
    // 0x00475530 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_475540 [ptankCreatePipeData] -- creates a tank's pipeline record (400 bytes + its buffers) for $a1 particles and the format at +88, by the flags $a3
// ($a0 = the tank data) The component count (+80); flag 0x10 hands over to the callback 0x77B250; a format without
// matrices, normals or other high bits (and flag 4 clear) takes a packed VU1 layout of the table 0x77AC40 (40 words
// a variant, picked by the constant colour / UV / size bits 0x40040 / 0x100100 / 0x20020: clusters, strides, the
// batch size) with the record's cluster words and sizes; an interleaved format (0x20000000) one record per particle
// (16-rounded with a position or a matrix); else the separate arrays (sub_4753D0). Flag 8: the 400-byte record
// only; flag 2: two buffers; flag 1: +220 = 1. The buffer ring at +216..+232, the record at tank data +76; 0 when
// the allocation fails (in the packed branch).
// 0x00475540 sub_475540 -- 1752 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_475540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00475540
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = 0;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a3;
    sq(s2, sp, 0x20);
    v0 = s4 & 0x4;
    sq(s1, sp, 0x10);
    v0 = sltu(0, v0);
    sq(s0, sp, 0x0);
    t6 = v0 ^ 0x1;
    lw(a2, a0, 88);
    t4 = a2 & 0x1;
    t5 = a2 & 0x8;
    t7 = t4 ^ 0x1;
    v1 = a2 & 0x10;
    s1 = sltiu(t7, 1);
    t3 = a2 & 0x4;
    t7 = t5 ^ 0x8;
    t2 = a2 & 0x2;
    s0 = sltiu(t7, 1);
    t1 = a2 & 0x40;
    t7 = v1 ^ 0x10;
    s0 = addu(s1, s0);
    t7 = sltiu(t7, 1);
    v0 = a2 & 0x20;
    s1 = addu(t7, s0);
    t0 = a2 & 0x80;
    t7 = t3 ^ 0x4;
    a3 = a2 & 0x100;
    s0 = sltiu(t7, 1);
    t7 = t2 ^ 0x2;
    s0 = addu(s0, s1);
    t7 = sltiu(t7, 1);
    s1 = addu(t7, s0);
    t7 = t1 ^ 0x40;
    s0 = sltiu(t7, 1);
    t7 = v0 ^ 0x20;
    s0 = addu(s0, s1);
    t7 = sltiu(t7, 1);
    s1 = addu(t7, s0);
    t7 = t0 ^ 0x80;
    s0 = sltiu(t7, 1);
    t7 = a3 ^ 0x100;
    s0 = addu(s0, s1);
    t7 = sltiu(t7, 1);
    t7 = addu(t7, s0);
    sw(t7, a0, 80);
    if (t6 != 0) {
        // 0x0047561c
        charge(ctx, 7);
        a0 = lui(0xEEE1);
        a0 = a0 | 0xFE18;
        a0 = a2 & a0;
        a0 = sltu(0, a0);
        a0 = a0 ^ 0x1;
        if (a0 != 0) {
            // 0x00475638
            charge(ctx, 1);
            s7 = 1;
        }
    }
    // 0x0047563c
    charge(ctx, 6);
    t7 = s4 & 0x2;
    s6 = 2;
    t6 = 1;
    a0 = s4 & 0x10;
    if (t7 == 0) s6 = t6;
    if (a0 != 0) {
        // 0x004757ec
        charge(ctx, 7);
        v0 = 0x780000;
        a0 = s5;
        lw(v0, v0, -19888);  // 0x77B250
        a3 = s4;
        jalr(ctx, 0x4757F8u, v0.u());
        ld(ra, sp, 0x90);
    } else {
        // 0x00475654
        charge(ctx, 2);
        if (s7 == 0) {
            // 0x0047565c
            charge(ctx, 4);
            a0 = 0x20000000;
            a0 = a2 & a0;
            if (a0 == 0) {
                // 0x00475b88
                charge(ctx, 5);
                t0 = 0x780000;
                sw(zero, s5, 84);
                a0 = 0;
                t0 = addiu(t0, -21536);  // &0x77ABE0
                a3 = s5;
                for (;;) {
                    // 0x00475b9c
                    charge(ctx, 11);
                    lw(v1, t0, 0);
                    a0 = addiu(a0, 3);
                    v0 = sltiu(a0, 9);
                    sw(v1, a3, 8);
                    lw(v1, t0, 4);
                    sw(v1, a3, 16);
                    lw(v1, t0, 8);
                    sw(v1, a3, 24);
                    t0 = addiu(t0, 12);
                    a3 = addiu(a3, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00475bc8
                charge(ctx, 5);
                a0 = a1;
                a1 = a2;
                jal(ctx, 0x475BCCu, gen::fn_sub_4753D0_004753d0);
                v1 = s4 & 0x8;
                backedge(ctx);
            } else {
                // 0x0047566c
                charge(ctx, 2);
                a0 = 0;
                if (t4 != 0) {
                    // 0x00475674
                    charge(ctx, 1);
                    a0 = addiu(a0, 16);
                }
                // 0x00475678
                charge(ctx, 2);
                if (t5 != 0) {
                    // 0x00475680
                    charge(ctx, 3);
                    t4 = 0x7C0000;
                    lw(t4, t4, -14076);  // 0x7BC904
                    a0 = addu(a0, t4);
                }
                // 0x0047568c
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x00475694
                    charge(ctx, 3);
                    v1 = 0x7C0000;
                    lw(v1, v1, -14072);  // 0x7BC908
                    a0 = addu(a0, v1);
                }
                // 0x004756a0
                charge(ctx, 2);
                if (t3 != 0) {
                    // 0x004756a8
                    charge(ctx, 3);
                    v1 = 0x7C0000;
                    lw(v1, v1, -14068);  // 0x7BC90C
                    a0 = addu(a0, v1);
                }
                // 0x004756b4
                charge(ctx, 2);
                if (t2 != 0) {
                    // 0x004756bc
                    charge(ctx, 3);
                    v1 = 0x7C0000;
                    lw(v1, v1, -14064);  // 0x7BC910
                    a0 = addu(a0, v1);
                }
                // 0x004756c8
                charge(ctx, 2);
                if (t1 != 0) {
                    // 0x004756d0
                    charge(ctx, 3);
                    v1 = 0x7C0000;
                    lw(v1, v1, -14060);  // 0x7BC914
                    a0 = addu(a0, v1);
                }
                // 0x004756dc
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004756e4
                    charge(ctx, 3);
                    v0 = 0x7C0000;
                    lw(v0, v0, -14056);  // 0x7BC918
                    a0 = addu(a0, v0);
                }
                // 0x004756f0
                charge(ctx, 2);
                if (t0 != 0) {
                    // 0x004756f8
                    charge(ctx, 3);
                    v0 = 0x7C0000;
                    lw(v0, v0, -14052);  // 0x7BC91C
                    a0 = addu(a0, v0);
                }
                // 0x00475704
                charge(ctx, 2);
                if (a3 != 0) {
                    // 0x0047570c
                    charge(ctx, 3);
                    v0 = 0x7C0000;
                    lw(v0, v0, -14048);  // 0x7BC920
                    a0 = addu(a0, v0);
                }
                // 0x00475718
                charge(ctx, 3);
                v0 = a2 & 0x9;
                if (v0 != 0) {
                    // 0x00475724
                    charge(ctx, 3);
                    v1 = addiu(a0, 15);
                    v0 = si(-16);
                    a0 = v1 & v0;
                }
                // 0x00475730
                charge(ctx, 3);
                sw(a0, s5, 84);
                v1 = 0;
                a2 = s5;
                for (;;) {
                    // 0x0047573c
                    charge(ctx, 7);
                    sw(a0, a2, 8);
                    v1 = addiu(v1, 3);
                    sw(a0, a2, 16);
                    v0 = sltiu(v1, 9);
                    sw(a0, a2, 24);
                    a2 = addiu(a2, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00475758
                charge(ctx, 2);
                mult(v0, a1, a0);
                v1 = s4 & 0x8;
            }
            // 0x00475760
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00475788
                charge(ctx, 8);
                a0 = addiu(v0, 400);
                v0 = 0x30000;
                a1 = v0 | 0x12F;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                jalr(ctx, 0x47579Cu, v0.u());
                s3 = v0;
            } else {
                // 0x00475768
                charge(ctx, 8);
                v0 = 0x30000;
                a1 = v0 | 0x12F;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                a0 = 400;
                jalr(ctx, 0x475778u, v0.u());
                s3 = v0;
            }
            // 0x004757a8
            charge(ctx, 4);
            a0 = s3;
            a1 = 0;
            a2 = 400;
            jal(ctx, 0x4757B0u, gen::fn_memset_00521408);
            goto L_004757b8;
        }
        // 0x00475808
        charge(ctx, 5);
        t5 = 0x780000;
        sw(zero, s5, 84);
        t6 = 0;
        t5 = addiu(t5, -21536);  // &0x77ABE0
        t4 = s5;
        for (;;) {
            // 0x0047581c
            charge(ctx, 11);
            lw(a0, t5, 0);
            t6 = addiu(t6, 3);
            v1 = sltiu(t6, 9);
            sw(a0, t4, 8);
            lw(a0, t5, 4);
            sw(a0, t4, 16);
            lw(a0, t5, 8);
            sw(a0, t4, 24);
            t5 = addiu(t5, 12);
            t4 = addiu(t4, 24);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00475848
        charge(ctx, 5);
        a0 = 0x40000;
        a0 = a0 | 0x40;
        a0 = a2 & a0;
        v1 = 0;
        if (a0 != 0) {
            // 0x0047585c
            charge(ctx, 1);
            v1 = addiu(v1, 1);
        }
        // 0x00475860
        charge(ctx, 5);
        a0 = 0x100000;
        a0 = a0 | 0x100;  // &0x100100
        a0 = a2 & a0;
        if (a0 != 0) {
            // 0x00475874
            charge(ctx, 1);
            v1 = addiu(v1, 2);
        }
        // 0x00475878
        charge(ctx, 5);
        a0 = 0x20000;
        a0 = a0 | 0x20;
        a0 = a2 & a0;
        if (a0 != 0) {
            // 0x0047588c
            charge(ctx, 1);
            v1 = addiu(v1, 4);
        }
        // 0x00475890
        charge(ctx, 40);
        a0 = addiu(a1, -1);
        v0 = sltu(0, v0);
        a1 = sll(v1, 2);
        sw(zero, sp, 0xC0);
        v1 = addu(a1, v1);
        s1 = 0;
        a2 = sll(v1, 5);
        a1 = 0x780000;
        v1 = s4 & 0x20;
        a1 = addiu(a1, -21440);  // &0x77AC40
        v1 = sltu(0, v1);
        s2 = addu(a1, a2);
        sq(v1, sp, 0xB0);
        s0 = 0;
        lw(v1, s2, 16);
        divu(a0, v1);
        a0 = sltu(0, t1);
        a0 = a0 ^ 0x1;
        sw(a0, sp, 0xD4);
        mflo(v1);
        a0 = v0 ^ 0x1;
        sw(a0, sp, 0xD8);
        a0 = sltu(0, t0);
        lw(v0, s2, 24);
        a0 = a0 ^ 0x1;
        fp = addiu(v1, 0x1);
        sw(a0, sp, 0xDC);
        a0 = sltu(0, a3);
        a0 = a0 ^ 0x1;
        sw(a0, sp, 0xE0);
        a0 = sltu(0, t3);
        a0 = a0 ^ 0x1;
        sw(a0, sp, 0xCC);
        a0 = sltu(0, t2);
        a0 = a0 ^ 0x1;
        sw(a0, sp, 0xD0);
        a0 = addiu(v0, 1);
        a0 = sll(a0, 4);
        sq(a0, sp, 0xA0);
        if (t3 != 0) {
            // 0x00475930
            charge(ctx, 1);
            s0 = addiu(s0, 64);
        }
        // 0x00475934
        charge(ctx, 2);
        if (t2 != 0) {
            // 0x0047593c
            charge(ctx, 1);
            s0 = addiu(s0, 64);
        }
        // 0x00475940
        charge(ctx, 3);
        at = sltu(0, v0);
        a0 = 0;
        if (at == 0) {
            // 0x00475b54
            charge(ctx, 1);
            lq(v0, sp, 0xA0);
        } else {
            // 0x0047594c
            charge(ctx, 1);
            a1 = s2;
            for (;;) {
                // 0x00475950
                charge(ctx, 6);
                lw(v1, a1, 36);
                v1 = sll(v1, 2);
                v1 = addu(v1, sp);
                lw(v1, v1, 192);
                if (v1 == 0) {
                    // 0x00475978
                    charge(ctx, 4);
                    lw(v1, a1, 40);
                    v1 = sll(v1, 4);
                    s1 = addu(s1, v1);
                } else {
                    // 0x00475968
                    charge(ctx, 4);
                    lw(v1, a1, 44);
                    v1 = sll(v1, 4);
                    s0 = addu(s0, v1);
                }
                // 0x00475988
                charge(ctx, 4);
                a0 = addiu(a0, 1);
                v1 = sltu(a0, v0);
                a1 = addiu(a1, 24);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00475998
            charge(ctx, 2);
            lq(v0, sp, 0xA0);
        }
        // 0x00475b58
        charge(ctx, 8);
        v1 = addiu(s0, 64);
        v0 = addu(v0, s1);
        mult(v0, fp, v0);
        v0 = addu(v1, v0);
        mult(v1, s6, v0);
        v0 = s4 & 0x8;
        if (v0 == 0) {
            backedge(ctx);
            // 0x004759bc
            charge(ctx, 7);
            v0 = 0x30000;
            a1 = v0 | 0x12F;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = addiu(v1, 400);
            jalr(ctx, 0x4759CCu, v0.u());
            s3 = v0;
        } else {
            // 0x00475b78
            charge(ctx, 2);
            v0 = 0x30000;
            backedge(ctx);
            // 0x004759a0
            charge(ctx, 7);
            a1 = v0 | 0x12F;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = 400;
            jalr(ctx, 0x4759ACu, v0.u());
            s3 = v0;
        }
        // 0x004759d8
        charge(ctx, 2);
        if (s3 == 0) {
            // 0x00475b80
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004759e0
            charge(ctx, 25);
            a0 = s3;
            a1 = 0;
            a2 = 400;
            jal(ctx, 0x4759E8u, gen::fn_memset_00521408);
            sw(s2, s3, 252);
            v0 = 64;
            sw(fp, s3, 292);
            a0 = addiu(s3, 256);
            sw(v0, s3, 304);
            a1 = addiu(sp, 0xC0);
            lq(v0, sp, 0xA0);
            a2 = 36;
            sw(s0, s3, 308);
            sw(v0, s3, 296);
            link(ctx, 0x475A18u);  // $ra first: the delay slot below depends on it
            sw(s1, s3, 300);
            call(ctx, gen::fn_memcpy_00521250);
            lq(v0, sp, 0xB0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            lw(v0, v0, 28);
            sw(v0, s3, 248);
            lw(a0, s2, 24);
            at = sltiu(a0, 2);
            a1 = 1;
            if (at == 0) {
                // 0x00475a44
                charge(ctx, 3);
                v1 = 0x780000;
                a2 = addiu(s2, 24);
                v1 = addiu(v1, -21488);  // &0x77AC10
                for (;;) {
                    // 0x00475a50
                    charge(ctx, 6);
                    lw(v0, a2, 36);
                    a0 = sll(v0, 2);
                    v0 = addu(a0, sp);
                    lw(v0, v0, 192);
                    if (v0 == 0) {
                        // 0x00475a70
                        charge(ctx, 2);
                        v0 = addu(v1, a0);
                        lw(a0, v0, 0);
                    } else {
                        // 0x00475a68
                        charge(ctx, 2);
                        a0 = 0;
                    }
                    // 0x00475a78
                    charge(ctx, 7);
                    v0 = addu(s3, a1);
                    sb(a0, v0, 243);
                    a1 = addiu(a1, 1);
                    lw(a0, s2, 24);
                    v0 = sltu(a1, a0);
                    a2 = addiu(a2, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00475a94
            charge(ctx, 3);
            at = sltu(0, a0);
            v1 = 0;
            if (at == 0) {
                backedge(ctx);
            L_004757b8:
                charge(ctx, 1);
                v1 = sltiu(s6, 2);
            } else {
                // 0x00475aa0
                charge(ctx, 4);
                a2 = s2;
                a1 = s3;
                a0 = s3;
                v0 = 0x30000000;
                for (;;) {
                    // 0x00475ab0
                    charge(ctx, 6);
                    lw(a3, a2, 36);
                    a3 = sll(a3, 2);
                    a3 = addu(a3, sp);
                    lw(a3, a3, 192);
                    if (a3 == 0) {
                        // 0x00475af0
                        charge(ctx, 14);
                        lwu(a3, a2, 40);
                        a3 = a3 | v0;
                        a3 = dsll32(a3, 0);
                        a3 = dsra32(a3, 0);
                        sw(a3, a1, 64);
                        lw(a3, a2, 48);
                        sw(a3, a1, 76);
                        lw(a3, a2, 40);
                        a3 = sll(a3, 4);
                        a3 = dsll32(a3, 0);
                        a3 = dsrl32(a3, 0);
                        a3 = dsll32(a3, 0);
                        sd(a3, a0, 144);
                    } else {
                        // 0x00475ac8
                        charge(ctx, 9);
                        lwu(a3, a2, 44);
                        a3 = a3 | v0;
                        a3 = dsll32(a3, 0);
                        a3 = dsra32(a3, 0);
                        sw(a3, a1, 64);
                        lw(a3, a2, 52);
                        sw(a3, a1, 76);
                        sd(zero, a0, 144);
                    }
                    // 0x00475b28
                    charge(ctx, 9);
                    lw(a3, a2, 56);
                    v1 = addiu(v1, 1);
                    a0 = addiu(a0, 8);
                    sw(a3, a1, 72);
                    a2 = addiu(a2, 24);
                    lw(a3, s2, 24);
                    a3 = sltu(v1, a3);
                    a1 = addiu(a1, 16);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00475b4c
                charge(ctx, 2);
                v1 = sltiu(s6, 2);
                backedge(ctx);
            }
            // 0x004757bc
            charge(ctx, 9);
            sw(s7, s3, 216);
            a0 = addiu(s6, -1);
            v1 = v1 ^ 0x1;
            sw(a0, s3, 232);
            v0 = s4 & 0x1;
            sw(v1, s3, 224);
            v1 = 14;
            sd(v1, s3, 200);
            if (v0 != 0) {
                // 0x00475bdc
                charge(ctx, 3);
                v0 = 1;
                sw(v0, s3, 220);
                backedge(ctx);
            }
            // 0x004757e0
            charge(ctx, 3);
            sw(s3, s5, 76);
            v0 = s3;
        }
        // 0x00475be8
        charge(ctx, 1);
        ld(ra, sp, 0x90);
    }
    // 0x00475bec (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xF0);
}


// sub_475C20 [ptankReleaseInstanceBuffers] -- releases a tank atomic's instance buffers: each buffer record's resource entry (sub_4C47E0) cleared
// Only when the pipeline flags (+68) lack bit 4 (the buffers are the tank's). The buffer ring (+156, 4-byte stride from
// +312) up to its count (+232).
// 0x00475C20 sub_475C20 -- 136 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_475C20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00475c20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17792);  // 0x7CE770 (the PTank atomic extension offset)
    v1 = addu(a0, v1);
    lw(a0, v1, 0);
    lw(v1, a0, 68);
    v1 = v1 & 0x10;
    if (v1 == 0) {
        // 0x00475c50
        charge(ctx, 3);
        lw(s0, a0, 156);
        s2 = 0;
        s1 = s0;
        for (;;) {
            // 0x00475c5c
            charge(ctx, 3);
            lw(a0, s1, 312);
            if (a0 != 0) {
                // 0x00475c68
                charge(ctx, 4);
                jal(ctx, 0x475C68u, gen::fn_sub_4C47E0_004c47e0);
                sw(zero, s1, 312);
            }
            // 0x00475c78
            charge(ctx, 5);
            lw(v1, s0, 232);
            s2 = addiu(s2, 1);
            at = sltu(v1, s2);
            s1 = addiu(s1, 4);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00475c8c
        charge(ctx, 1);
    }
    // 0x00475c90 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_477050 [ptankNextBuffer] -- steps a tank's buffer ring and loads the current buffer's three {pointer, stride} pairs into the tank data
// 1 without a ring (+216 = 0); else the index (+228) wraps at the count (+232); returns 1 when the buffer's +16 word
// is 0.
// 0x00477050 sub_477050 -- 248 bytes; leaf frame (no stack)
void sub_477050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x00477050
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, gp, -17792);  // 0x7CE770 (the PTank atomic extension offset)
    v0 = addu(a0, v0);
    lw(v0, v0, 0);
    lw(a0, v0, 156);
    a1 = addiu(v0, 80);
    lw(v0, a0, 216);
    if (v0 == 0) {
        // 0x0047713c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x00477070
        charge(ctx, 5);
        lw(v1, a0, 228);
        lw(v0, a0, 232);
        at = slt(v1, v0);
        if (at == 0) {
            // 0x00477094
            charge(ctx, 1);
            sw(zero, a0, 228);
        } else {
            // 0x00477084
            charge(ctx, 4);
            lw(v0, a0, 228);
            v0 = addiu(v0, 1);
            sw(v0, a0, 228);
        }
        // 0x00477098
        charge(ctx, 3);
        lw(v0, a0, 232);
        if (v0 != 0) {
            // 0x004770a4
            charge(ctx, 2);
            v1 = 0;
            v0 = 0;
            for (;;) {
                // 0x004770ac
                charge(ctx, 29);
                lw(t0, a0, 228);
                v1 = addiu(v1, 3);
                a2 = sltiu(v1, 9);
                a3 = sll(t0, 3);
                a3 = addu(a3, t0);
                a3 = sll(a3, 2);
                a3 = addu(a0, a3);
                a3 = addu(a3, v0);
                lw(a3, a3, 320);
                sw(a3, a1, 4);
                lw(t0, a0, 228);
                a3 = sll(t0, 3);
                a3 = addu(a3, t0);
                a3 = sll(a3, 2);
                a3 = addu(a0, a3);
                a3 = addu(a3, v0);
                lw(a3, a3, 324);
                sw(a3, a1, 12);
                lw(t0, a0, 228);
                a3 = sll(t0, 3);
                a3 = addu(a3, t0);
                a3 = sll(a3, 2);
                a3 = addu(a0, a3);
                a3 = addu(a3, v0);
                lw(a3, a3, 328);
                v0 = addiu(v0, 12);
                sw(a3, a1, 20);
                a1 = addiu(a1, 24);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00477120
        charge(ctx, 7);
        lw(v0, a0, 228);
        v0 = sll(v0, 5);
        v0 = addu(v0, a0);
        lw(v0, v0, 16);
        // xor v0: a 64-bit move to itself (no effect)
        v0 = sltiu(v0, 1);
    }
    // 0x00477140 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_478CC0 [ptank2dObjectSetup] -- the 2-D tank pipeline's PS2All object set-up callback: mesh header, resource entry, transform, frustum clip flag
// ($a0 = the object set-up record, $a1 = the transform destination) The geometry's mesh header (+12) and its native resource entry (+16; through the pipeline-id cache, else sub_49E5A0), flag bit 0 cleared, the camera's 64-byte transform copied, then the atomic's world bounding sphere against the camera's six frustum planes (module + 96, 20 bytes each): +40 = the camera's clip word, | 2 when the sphere crosses a plane; +41 = 4, +42 = 1. Returns 1.
// 0x00478CC0 sub_478CC0 -- 440 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_478CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x00478cc0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x960000;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s1, a0, 8);
    lw(v0, v0, 112);  // 0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(a1, s1, 24);
    s0 = addiu(v0, 32);
    lw(v0, a1, 84);
    sw(v0, a0, 12);
    lw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
    a0 = addu(a1, v0);
    lw(v0, a0, 0);
    a2 = 0;
    if (v0 != 0) {
        // 0x00478d10
        charge(ctx, 5);
        lw(v1, a1, 84);
        lw(v0, v0, 0);
        lhu(v1, v1, 4);
        if (v1 == v0) {
            // 0x00478d24
            charge(ctx, 1);
            a2 = 1;
        }
    }
    // 0x00478d28
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x00478d38
        charge(ctx, 5);
        lw(v0, a1, 84);
        link(ctx, 0x478D3Cu);  // $ra first: the delay slot below depends on it
        lhu(a1, v0, 4);
        call(ctx, gen::fn_sub_49E5A0_0049e5a0);
        a0 = v0;
        lw(v1, a0, 0);
    } else {
        // 0x00478d30
        charge(ctx, 2);
        lw(v1, a0, 0);
    }
    // 0x00478d4c
    charge(ctx, 7);
    v0 = si(-2);
    sw(v1, s3, objsetup::kResEntry);
    a0 = 8;
    lw(v1, s3, objsetup::kFlags);
    v0 = v1 & v0;
    sw(v0, s3, objsetup::kFlags);
    lw(a1, s2, 0);
    for (;;) {
        // 0x00478d68
        charge(ctx, 8);
        lw(v1, s0, 0);
        a0 = addiu(a0, -1);
        lw(v0, s0, 4);
        sw(v1, a1, 0);
        s0 = addiu(s0, 8);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00478d88
    charge(ctx, 11);
    a0 = s1;
    s0 = 2;
    jal(ctx, 0x478D8Cu, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    v1 = 0x960000;
    lw(a0, gp, -16972);  // 0x7CEAA4 (the camera module offset (its frustum planes at +96))
    lw(a1, v1, 112);  // 0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = 6;
    a0 = addu(a1, a0);
    a2 = addiu(v1, -1);
    a0 = addiu(a0, 96);
    if (v1 != 0) {
        // 0x00478db4
        charge(ctx, 6);
        lwc1(f0, v0, 12);
        v1 = 1;
        lwc1(f7, v0, 4);
        lwc1(f6, v0, 0);
        lwc1(f5, v0, 8);
        neg_s(f4, f0);
        for (;;) {
            // 0x00478dcc
            charge(ctx, 11);
            lwc1(f1, a0, 4);
            lwc1(f2, a0, 0);
            lwc1(f3, a0, 8);
            lwc1(f0, a0, 12);
            mula_s(f7, f1);
            madda_s(f6, f2);
            madd_s(f1, f5, f3);
            sub_s(f0, f1, f0);
            c_le_s(f0, f4);
            v0 = v1;
            if (cond(ctx)) {
                // 0x00478df8
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x00478dfc
            charge(ctx, 3);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                goto L_00478e08_13;
            }
            // 0x00478e10
            charge(ctx, 4);
            v0 = a2;
            a0 = addiu(a0, 20);
            a2 = addiu(a2, -1);
            if (v0 != 0) {
                backedge(ctx);
                continue;
            }
            break;
        }
    }
L_00478e20:
    charge(ctx, 8);
    a0 = 4;
    sb(a0, s3, objsetup::kLightMode);
    v1 = dsll32(s0, 0);
    lbu(a0, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
    v1 = dsra32(v1, 0);
    v0 = 2;
    sb(a0, s3, objsetup::kClip);
    if (v1 != v0) {
        // 0x00478e4c
        charge(ctx, 4);
        lbu(v0, s3, objsetup::kClip);
        v0 = v0 | 0x2;
        sb(v0, s3, objsetup::kClip);
        backedge(ctx);
    }
    // 0x00478e40
    charge(ctx, 3);
    v0 = 1;
    sb(v0, s3, objsetup::kDone);
    // 0x00478e5c
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_00478e08_13:
    charge(ctx, 2);
    s0 = 1;
    goto L_00478e20;
}


// sub_47A050 [ptank3dObjectSetup] -- the 3-D tank pipeline's PS2All object set-up callback (the same body as sub_478CC0)
// ($a0 = the object set-up record, $a1 = the transform destination) The geometry's mesh header (+12) and its native resource entry (+16; through the pipeline-id cache, else sub_49E5A0), flag bit 0 cleared, the camera's 64-byte transform copied, then the atomic's world bounding sphere against the camera's six frustum planes (module + 96, 20 bytes each): +40 = the camera's clip word, | 2 when the sphere crosses a plane; +41 = 4, +42 = 1. Returns 1.
// 0x0047A050 sub_47A050 -- 440 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47A050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x0047a050
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x960000;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s1, a0, 8);
    lw(v0, v0, 112);  // 0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(a1, s1, 24);
    s0 = addiu(v0, 32);
    lw(v0, a1, 84);
    sw(v0, a0, 12);
    lw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
    a0 = addu(a1, v0);
    lw(v0, a0, 0);
    a2 = 0;
    if (v0 != 0) {
        // 0x0047a0a0
        charge(ctx, 5);
        lw(v1, a1, 84);
        lw(v0, v0, 0);
        lhu(v1, v1, 4);
        if (v1 == v0) {
            // 0x0047a0b4
            charge(ctx, 1);
            a2 = 1;
        }
    }
    // 0x0047a0b8
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x0047a0c8
        charge(ctx, 5);
        lw(v0, a1, 84);
        link(ctx, 0x47A0CCu);  // $ra first: the delay slot below depends on it
        lhu(a1, v0, 4);
        call(ctx, gen::fn_sub_49E5A0_0049e5a0);
        a0 = v0;
        lw(v1, a0, 0);
    } else {
        // 0x0047a0c0
        charge(ctx, 2);
        lw(v1, a0, 0);
    }
    // 0x0047a0dc
    charge(ctx, 7);
    v0 = si(-2);
    sw(v1, s3, objsetup::kResEntry);
    a0 = 8;
    lw(v1, s3, objsetup::kFlags);
    v0 = v1 & v0;
    sw(v0, s3, objsetup::kFlags);
    lw(a1, s2, 0);
    for (;;) {
        // 0x0047a0f8
        charge(ctx, 8);
        lw(v1, s0, 0);
        a0 = addiu(a0, -1);
        lw(v0, s0, 4);
        sw(v1, a1, 0);
        s0 = addiu(s0, 8);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0047a118
    charge(ctx, 11);
    a0 = s1;
    s0 = 2;
    jal(ctx, 0x47A11Cu, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    v1 = 0x960000;
    lw(a0, gp, -16972);  // 0x7CEAA4 (the camera module offset (its frustum planes at +96))
    lw(a1, v1, 112);  // 0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = 6;
    a0 = addu(a1, a0);
    a2 = addiu(v1, -1);
    a0 = addiu(a0, 96);
    if (v1 != 0) {
        // 0x0047a144
        charge(ctx, 6);
        lwc1(f0, v0, 12);
        v1 = 1;
        lwc1(f7, v0, 4);
        lwc1(f6, v0, 0);
        lwc1(f5, v0, 8);
        neg_s(f4, f0);
        for (;;) {
            // 0x0047a15c
            charge(ctx, 11);
            lwc1(f1, a0, 4);
            lwc1(f2, a0, 0);
            lwc1(f3, a0, 8);
            lwc1(f0, a0, 12);
            mula_s(f7, f1);
            madda_s(f6, f2);
            madd_s(f1, f5, f3);
            sub_s(f0, f1, f0);
            c_le_s(f0, f4);
            v0 = v1;
            if (cond(ctx)) {
                // 0x0047a188
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x0047a18c
            charge(ctx, 3);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                goto L_0047a198_13;
            }
            // 0x0047a1a0
            charge(ctx, 4);
            v0 = a2;
            a0 = addiu(a0, 20);
            a2 = addiu(a2, -1);
            if (v0 != 0) {
                backedge(ctx);
                continue;
            }
            break;
        }
    }
L_0047a1b0:
    charge(ctx, 8);
    a0 = 4;
    sb(a0, s3, objsetup::kLightMode);
    v1 = dsll32(s0, 0);
    lbu(a0, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
    v1 = dsra32(v1, 0);
    v0 = 2;
    sb(a0, s3, objsetup::kClip);
    if (v1 != v0) {
        // 0x0047a1dc
        charge(ctx, 4);
        lbu(v0, s3, objsetup::kClip);
        v0 = v0 | 0x2;
        sb(v0, s3, objsetup::kClip);
        backedge(ctx);
    }
    // 0x0047a1d0
    charge(ctx, 3);
    v0 = 1;
    sb(v0, s3, objsetup::kDone);
    // 0x0047a1ec
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_0047a198_13:
    charge(ctx, 2);
    s0 = 1;
    goto L_0047a1b0;
}


// sub_47ABF0 [ptankLitObjectSetup] -- the lit tank pipeline's PS2All object set-up callback: as sub_478CC0 plus the reinstance flags and the lights
// For a non-native geometry the instance key (+24: the geometry's flags & 0x9F, its morph-target count, the mesh
// header's serial) against the resource entry's: a change of flags / count sets bit 3 (full reinstance), of the serial
// bit 2; the geometry's lock flags add 2 / 8 x the flags; a dirty interpolator (atomic +76 bit 0) whose morph targets
// differ bit 2. The lock flags and the interpolator's dirty bit are cleared. After the clip test: with lighting
// (geometry flag 0x40) the engine stamp (0x96007A) is bumped and the world's lights and the atomic's sectors' local
// lights are collected through sub_4A0430 into the lighting record on the stack; +41 = the light mode.
// 0x0047ABF0 sub_47ABF0 -- 1456 bytes; frame 0xF0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47ABF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x0047abf0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v0 = 0x960000;
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s1, a0, 8);
    lw(v0, v0, 112);  // 0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(a1, s1, 24);
    s0 = addiu(v0, 32);
    lw(v0, a1, 84);
    sw(v0, a0, 12);
    lw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
    a0 = addu(a1, v0);
    lw(v0, a0, 0);
    a2 = 0;
    if (v0 != 0) {
        // 0x0047ac4c
        charge(ctx, 5);
        lw(v1, a1, 84);
        lw(v0, v0, 0);
        lhu(v1, v1, 4);
        if (v1 == v0) {
            // 0x0047ac60
            charge(ctx, 1);
            a2 = 1;
        }
    }
    // 0x0047ac64
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x0047ac74
        charge(ctx, 5);
        lw(v0, a1, 84);
        link(ctx, 0x47AC78u);  // $ra first: the delay slot below depends on it
        lhu(a1, v0, 4);
        call(ctx, gen::fn_sub_49E5A0_0049e5a0);
        a0 = v0;
        lw(v1, a0, 0);
    } else {
        // 0x0047ac6c
        charge(ctx, 2);
        lw(v1, a0, 0);
    }
    // 0x0047ac88
    charge(ctx, 7);
    v0 = 0x1000000;
    sw(v1, s3, objsetup::kResEntry);
    lw(a0, s1, 24);
    lw(v1, a0, 8);
    v0 = v1 & v0;
    if (v0 == 0) {
        // 0x0047aff8
        charge(ctx, 18);
        lw(a2, s3, objsetup::kMeshHeader);
        v0 = v1 & 0x9F;
        lbu(v1, a0, 24);
        v0 = v0 & 0xFF;
        a1 = sll(v0, 16);
        v0 = si(-2);
        lhu(a2, a2, 6);
        v1 = sll(v1, 24);
        a1 = a2 | a1;
        v1 = v1 | a1;
        sw(v1, s3, objsetup::kInstanceKey);
        lw(v1, s3, objsetup::kFlags);
        v0 = v1 & v0;
        sw(v0, s3, objsetup::kFlags);
        lw(v0, s3, objsetup::kResEntry);
        lw(v0, v0, 4);
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x0047b040
            charge(ctx, 5);
            lw(t0, v0, 40);
            v1 = addiu(v0, 24);
            lw(a3, s3, objsetup::kInstanceKey);
            v0 = addiu(s1, 76);
            if (a3 != t0) {
                // 0x0047b054
                charge(ctx, 6);
                a2 = srl(a3, 16);
                a1 = srl(t0, 16);
                a2 = a2 & 0xFF;
                a1 = a1 & 0xFF;
                if (a2 == a1) {
                    // 0x0047b06c
                    charge(ctx, 6);
                    a2 = srl(a3, 24);
                    a1 = srl(t0, 24);
                    a2 = a2 & 0xFF;
                    a1 = a1 & 0xFF;
                    if (a2 != a1) {
                        goto L_0047b094;
                    }
                    // 0x0047b084
                    charge(ctx, 4);
                    lw(a1, s3, objsetup::kFlags);
                    a1 = a1 | 0x4;
                    sw(a1, s3, objsetup::kFlags);
                    goto L_0047b0a0;
                }
            L_0047b094:
                charge(ctx, 3);
                lw(a1, s3, objsetup::kFlags);
                a1 = a1 | 0x8;
                sw(a1, s3, objsetup::kFlags);
            }
        L_0047b0a0:
            charge(ctx, 3);
            lhu(a1, a0, 12);
            if (a1 != 0) {
                // 0x0047b0ac
                charge(ctx, 3);
                a1 = a1 & 0x1;
                if (a1 == 0) {
                    // 0x0047b0c8
                    charge(ctx, 8);
                    lw(a1, s3, objsetup::kFlags);
                    a1 = a1 | 0x2;
                    sw(a1, s3, objsetup::kFlags);
                    lhu(a1, a0, 12);
                    lw(a0, s3, objsetup::kFlags);
                    a1 = sll(a1, 3);
                    a0 = a0 | a1;
                    sw(a0, s3, objsetup::kFlags);
                } else {
                    // 0x0047b0b8
                    charge(ctx, 4);
                    lw(a0, s3, objsetup::kFlags);
                    a0 = a0 | 0x8;
                    sw(a0, s3, objsetup::kFlags);
                }
            }
            // 0x0047b0e8
            charge(ctx, 4);
            lw(a0, v0, 0);
            a0 = a0 & 0x1;
            if (a0 == 0) {
                backedge(ctx);
            } else {
                // 0x0047b0f8
                charge(ctx, 4);
                lw(a1, v1, 40);
                lh(a0, v0, 6);
                if (a1 == a0) {
                    // 0x0047b108
                    charge(ctx, 4);
                    lw(v1, v1, 36);
                    lh(v0, v0, 4);
                    if (v1 != v0) {
                        goto L_0047b118;
                    }
                    backedge(ctx);
                    goto L_0047aca4;
                }
            L_0047b118:
                charge(ctx, 4);
                lw(v0, s3, objsetup::kFlags);
                v0 = v0 | 0x4;
                sw(v0, s3, objsetup::kFlags);
                backedge(ctx);
            }
        }
    }
L_0047aca4:
    charge(ctx, 8);
    lw(v1, s1, 24);
    v0 = si(-2);
    a0 = 8;
    sh(zero, v1, 12);
    lw(v1, s1, 76);
    v0 = v1 & v0;
    sw(v0, s1, 76);
    lw(a1, s2, 0);
    for (;;) {
        // 0x0047acc4
        charge(ctx, 8);
        lw(v1, s0, 0);
        a0 = addiu(a0, -1);
        lw(v0, s0, 4);
        sw(v1, a1, 0);
        s0 = addiu(s0, 8);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0047ace4
    charge(ctx, 11);
    a0 = s1;
    s0 = 2;
    jal(ctx, 0x47ACE8u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    v1 = 0x960000;
    lw(a0, gp, -16972);  // 0x7CEAA4 (the camera module offset (its frustum planes at +96))
    lw(a1, v1, 112);  // 0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = 6;
    a0 = addu(a1, a0);
    a2 = addiu(v1, -1);
    a0 = addiu(a0, 96);
    if (v1 != 0) {
        // 0x0047ad10
        charge(ctx, 6);
        lwc1(f0, v0, 12);
        v1 = 1;
        lwc1(f7, v0, 4);
        lwc1(f6, v0, 0);
        lwc1(f5, v0, 8);
        neg_s(f4, f0);
        for (;;) {
            // 0x0047ad28
            charge(ctx, 11);
            lwc1(f1, a0, 4);
            lwc1(f2, a0, 0);
            lwc1(f3, a0, 8);
            lwc1(f0, a0, 12);
            mula_s(f7, f1);
            madda_s(f6, f2);
            madd_s(f1, f5, f3);
            sub_s(f0, f1, f0);
            c_le_s(f0, f4);
            v0 = v1;
            if (cond(ctx)) {
                // 0x0047ad54
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x0047ad58
            charge(ctx, 3);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                goto L_0047ad64_14;
            }
            // 0x0047ad6c
            charge(ctx, 4);
            v0 = a2;
            a0 = addiu(a0, 20);
            a2 = addiu(a2, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0047ad7c
        charge(ctx, 1);
    }
L_0047ad80:
    charge(ctx, 7);
    lw(v1, s3, objsetup::kMeshHeader);
    v0 = dsll32(s0, 0);
    a2 = 1;
    lw(a3, v1, 0);
    v1 = a3 & 0x1;
    v0 = dsra32(v0, 0);
    if (v1 == a2) {
        // 0x0047b128
        charge(ctx, 5);
        v1 = 4;
        sb(v1, s3, objsetup::kLightMode);
        lbu(v1, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
        sb(v1, s3, objsetup::kClip);
        backedge(ctx);
    } else {
        // 0x0047ad9c
        charge(ctx, 3);
        v1 = a3 & 0xFF;
        if (v1 != 0) {
            // 0x0047ada8
            charge(ctx, 4);
            v1 = a3 & 0x2;
            a1 = 2;
            if (v1 == a1) {
                goto L_0047b13c;
            }
            // 0x0047adb8
            charge(ctx, 4);
            a0 = a3 & 0x10;
            v1 = 16;
            if (a0 == v1) {
                // 0x0047b154
                charge(ctx, 5);
                v1 = 4;
                sb(v1, s3, objsetup::kLightMode);
                lbu(v1, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
                sb(v1, s3, objsetup::kClip);
                backedge(ctx);
            } else {
                // 0x0047adc8
                charge(ctx, 4);
                a0 = a3 & 0x8;
                v1 = 8;
                if (a0 != v1) {
                    // 0x0047adec
                    charge(ctx, 4);
                    sb(a2, s3, objsetup::kLightMode);
                    lbu(v1, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
                    v1 = v1 | 0x14;
                    sb(v1, s3, objsetup::kClip);
                } else {
                    // 0x0047add8
                    charge(ctx, 5);
                    sb(a1, s3, objsetup::kLightMode);
                    lbu(v1, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
                    v1 = v1 | 0x10;
                    sb(v1, s3, objsetup::kClip);
                }
            }
            goto L_0047adfc;
        }
    L_0047b13c:
        charge(ctx, 6);
        v1 = 3;
        sb(v1, s3, objsetup::kLightMode);
        lbu(v1, gp, -16892);  // 0x7CEAF4 (the camera's clip word)
        v1 = v1 | 0x4;
        sb(v1, s3, objsetup::kClip);
        backedge(ctx);
    }
L_0047adfc:
    charge(ctx, 3);
    v1 = 2;
    if (v0 != v1) {
        // 0x0047b168
        charge(ctx, 4);
        lbu(v0, s3, objsetup::kClip);
        v0 = v0 | 0x2;
        sb(v0, s3, objsetup::kClip);
        backedge(ctx);
    }
    // 0x0047ae08
    charge(ctx, 14);
    lbu(v0, s3, objsetup::kClip);
    v0 = v0 | 0x2;
    sb(v0, s3, objsetup::kClip);
    lw(v0, s1, 24);
    lw(v0, v0, 8);
    v0 = v0 & 0x40;
    v0 = sltu(0, v0);
    sb(v0, s3, objsetup::kDone);
    lw(s5, s3, objsetup::kAtomic);
    lw(s0, s5, 24);
    lw(v0, s0, 8);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x0047ae40
        charge(ctx, 16);
        s2 = 0x960000;
        s2 = addiu(s2, 122);  // &0x96007A (the engine's u16 light / frame stamp)
        lhu(v0, s2, 0);  // 0x96007A (the engine's u16 light / frame stamp)
        v0 = addiu(v0, 1);
        sh(v0, s2, 0);  // 0x96007A (the engine's u16 light / frame stamp)
        link(ctx, 0x47AE54u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 4);
        call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
        s1 = v0;
        a0 = addiu(sp, 0x90);
        a1 = s1;
        jal(ctx, 0x47AE64u, gen::fn_sub_4C32A0_004c32a0);
        lw(v1, s1, 12);
        v0 = 3;
        v1 = v1 & 0x3;
        if (v1 != v0) {
            // 0x0047ae90
            charge(ctx, 12);
            lwc1(f3, sp, 0xB4);
            lwc1(f2, sp, 0xB0);
            lwc1(f0, sp, 0xB8);
            mtc1(zero, f1);
            mula_s(f3, f3);
            madda_s(f2, f2);
            madd_s(f0, f0, f0);
            sqrt_s(f2, f0);
            c_le_s(f2, f1);
            swc1(f2, sp, 0xD0);
            if (!cond(ctx)) {
                // 0x0047aec0
                charge(ctx, 7);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                div_s(f2, f0, f2);
            }
            // 0x0047aedc
            charge(ctx, 1);
            swc1(f2, sp, 0xD4);
        } else {
            // 0x0047ae80
            charge(ctx, 4);
            v0 = 0x3F800000;
            sw(v0, sp, 0xD0);
            sw(v0, sp, 0xD4);
        }
        // 0x0047aee0
        charge(ctx, 14);
        lw(v1, s0, 84);
        a0 = 0x4A0000;
        a0 = addiu(a0, 1072);  // &sub_4A0430
        a1 = addiu(sp, 0x80);
        lw(v0, v1, 12);
        v0 = addu(v0, v1);
        lw(v0, v0, 24);
        v0 = addiu(v0, 12);
        link(ctx, 0x47AF00u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x80);
        call(ctx, gen::fn_worldForAllLights_00499c20);
        lw(s4, s5, 100);
        s6 = addiu(s5, 100);
        if (s4 != s6) {
            for (;;) {
                // 0x0047af18
                charge(ctx, 5);
                lw(v0, s4, 8);
                lw(s3, v0, 64);
                s1 = addiu(v0, 64);
                if (s3 != s1) {
                    // 0x0047af2c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0047af30
                        charge(ctx, 3);
                        lw(a1, s3, objsetup::kAtomic);
                        if (a1 != 0) {
                            // 0x0047af3c
                            charge(ctx, 4);
                            lhu(a0, s2, 0);
                            lhu(v0, a1, 60);
                            v1 = addiu(a1, 60);
                            if (v0 != a0) {
                                // 0x0047af4c
                                charge(ctx, 4);
                                lbu(v0, a1, 2);
                                v0 = v0 & 0x1;
                                if (v0 != 0) {
                                    // 0x0047af5c
                                    charge(ctx, 27);
                                    sh(a0, v1, 0);
                                    lw(v0, s3, objsetup::kAtomic);
                                    link(ctx, 0x47AF64u);  // $ra first: the delay slot below depends on it
                                    lw(a0, v0, 4);
                                    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                                    s0 = addiu(v0, 48);
                                    a0 = s5;
                                    jal(ctx, 0x47AF70u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
                                    lwc1(f4, v0, 4);
                                    lw(a0, s3, objsetup::kAtomic);
                                    lwc1(f3, s0, 4);
                                    lwc1(f6, v0, 0);
                                    lwc1(f5, s0, 0);
                                    lwc1(f0, s0, 8);
                                    lwc1(f1, v0, 8);
                                    lwc1(f2, v0, 12);
                                    sub_s(f3, f4, f3);
                                    sub_s(f5, f6, f5);
                                    mula_s(f3, f3);
                                    sub_s(f0, f1, f0);
                                    madda_s(f5, f5);
                                    madd_s(f1, f0, f0);
                                    lwc1(f0, a0, 20);
                                    add_s(f0, f2, f0);
                                    mul_s(f0, f0, f0);
                                    c_lt_s(f1, f0);
                                    if (cond(ctx)) {
                                        // 0x0047afc8
                                        charge(ctx, 2);
                                        a1 = addiu(sp, 0x80);
                                        jal(ctx, 0x47AFC8u, gen::fn_sub_4A0430_004a0430);
                                    }
                                }
                            }
                        }
                        // 0x0047afd0
                        charge(ctx, 3);
                        lw(s3, s3, 0);
                        if (s3 == s1) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047afdc
                    charge(ctx, 1);
                }
                // 0x0047afe0
                charge(ctx, 3);
                lw(s4, s4, 0);
                if (s4 == s6) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047afec
            charge(ctx, 1);
        }
    }
    // 0x0047aff0
    charge(ctx, 2);
    v0 = 1;
    // 0x0047b178
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xF0);
    return;
L_0047ad64_14:
    charge(ctx, 2);
    s0 = 1;
    goto L_0047ad80;
}


// RpRandomSeedMT -- seeds the separate MT-style generator: 0x95D410 = seed | 1, the 623 words at 0x95D414 the successive x 69069 products, the index cleared
// Not RpRandom's state (render_rw7.h): kwlnMain seeds both from the T0 counter.
// 0x00488C70 RpRandomSeedMT -- 88 bytes; leaf frame (no stack)
void RpRandomSeedMT(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00488c70
    enter(ctx, 10);  // entry check point + this block's cycles
    v1 = 0x960000;
    a2 = a0 | 0x1;
    v1 = addiu(v1, -11248);  // &0x95D410 (RpRandomSeedMT's seed | 1)
    sw(zero, gp, -20780);  // 0x7CDBC4 (RpRandomSeedMT's index)
    a1 = addiu(v1, 4);  // &0x95D414 (RpRandomSeedMT's 624-word table)
    v1 = 624;
    a0 = addiu(v1, -1);
    v1 = 0x960000;
    sw(a2, v1, -11248);  // 0x95D410 (RpRandomSeedMT's seed | 1)
    if (a0 != 0) {
        // 0x00488c98
        charge(ctx, 2);
        v1 = 0x10000;
        v1 = v1 | 0xDCD;
        for (;;) {
            // 0x00488ca0
            charge(ctx, 7);
            mult(a2, a2, v1);
            a0 = addiu(a0, -1);
            sw(a2, a1, 0);
            a1 = addiu(a1, 4);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00488cbc
        charge(ctx, 1);
    }
    // 0x00488cc0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_488CD0 [randomClose] -- RpRandom's engine close: the 124-byte state table freed (RwFree) and its pointer cleared; $a0
// 0x00488CD0 sub_488CD0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_488CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00488cd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, rrand::kTable);
    if (a0 != 0) {
        // 0x00488cfc
        charge(ctx, 9);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x488D04u, v0.u());
        lw(v1, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, rrand::kTable);
    }
    // 0x00488d20 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_488D40 [randomOpen] -- RpRandom's engine open: the 124-byte state table (RwMalloc, hint 0x4010C), the pointers, the default seed 0x9A319039
// front = table + 3, rear = table, end = table + 124, then RpRandomSeed(0x9A319039). $a0, or 0 when the allocation
// fails.
// 0x00488D40 sub_488D40 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_488D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00488d40
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x40000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x10C;
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    s0 = a0;
    a0 = 124;
    jalr(ctx, 0x488D60u, v0.u());
    lw(a0, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = addu(v1, a0);
    sw(v0, a1, rrand::kTable);
    lw(v0, a1, rrand::kTable);
    if (v0 == 0) {
        // 0x00488db8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00488d88
        charge(ctx, 12);
        v1 = addiu(v0, 12);
        v0 = lui(0x9A31);
        sw(v1, a1, rrand::kFront);
        a0 = v0 | 0x9039;
        lw(v0, a1, rrand::kTable);
        sw(v0, a1, rrand::kRear);
        lw(v0, a1, rrand::kTable);
        v0 = addiu(v0, 124);
        link(ctx, 0x488DA8u);  // $ra first: the delay slot below depends on it
        sw(v0, a1, rrand::kEnd);
        call(ctx, gen::fn_RpRandomSeed_00488dd0);
        v0 = s0;
    }
    // 0x00488dbc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// RpRandomSeed -- seeds RpRandom: table[0] = seed, table[i] = table[i-1] x 1103515245 + 12345, front = table + 3, rear = table, 310 draws discarded
// The fill runs six words per iteration (a2 = 1, 7, .. 25, the last pass ending at word 30), with mult / mult1
// alternating (the result only); the warm-up calls RpRandom (sub_488F30) 310 times (10 x the 31 words).
// 0x00488DD0 RpRandomSeed -- 340 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void RpRandomSeed(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00488dd0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    a2 = 1;
    lw(v0, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    a1 = 4;
    v0 = addu(v1, v0);
    lw(v0, v0, 0);
    sw(a0, v0, 0);
    v0 = 0x41C60000;
    v0 = v0 | 0x4E6D;
    for (;;) {
        // 0x00488e04: the LCG fill: six words per pass, x 1103515245 + 12345
        charge(ctx, 52);
        lw(a3, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        a2 = addiu(a2, 6);
        a0 = slti(a2, 31);
        a3 = addu(v1, a3);
        lw(a3, a3, rrand::kTable);
        t0 = addu(a3, a1);
        lw(a3, t0, -4);
        mult(a3, a3, v0);
        a3 = addiu(a3, 12345);
        sw(a3, t0, 0);
        lw(a3, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        a3 = addu(v1, a3);
        lw(a3, a3, rrand::kTable);
        t0 = addu(a3, a1);
        lw(a3, t0, 0);
        mult1(a3, a3, v0);
        a3 = addiu(a3, 12345);
        sw(a3, t0, 4);
        lw(a3, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        a3 = addu(v1, a3);
        lw(a3, a3, rrand::kTable);
        t0 = addu(a3, a1);
        lw(a3, t0, 4);
        mult(a3, a3, v0);
        a3 = addiu(a3, 12345);
        sw(a3, t0, 8);
        lw(a3, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        a3 = addu(v1, a3);
        lw(a3, a3, rrand::kTable);
        t0 = addu(a3, a1);
        lw(a3, t0, 8);
        mult1(a3, a3, v0);
        a3 = addiu(a3, 12345);
        sw(a3, t0, 12);
        lw(a3, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        a3 = addu(v1, a3);
        lw(a3, a3, rrand::kTable);
        t0 = addu(a3, a1);
        lw(a3, t0, 12);
        mult(a3, a3, v0);
        a3 = addiu(a3, 12345);
        sw(a3, t0, 16);
        lw(a3, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
        a3 = addu(v1, a3);
        lw(a3, a3, rrand::kTable);
        t0 = addu(a3, a1);
        lw(a3, t0, 16);
        a1 = addiu(a1, 24);
        mult1(a3, a3, v0);
        a3 = addiu(a3, 12345);
        sw(a3, t0, 20);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00488ed4: front = table + 3, rear = table
    charge(ctx, 8);
    lw(v0, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    s0 = 0;
    v1 = addu(v1, v0);
    lw(v0, v1, rrand::kTable);
    v0 = addiu(v0, 12);
    sw(v0, v1, rrand::kFront);
    lw(v0, v1, rrand::kTable);
    sw(v0, v1, rrand::kRear);
    for (;;) {
        // 0x00488ef4: 310 draws thrown away
        charge(ctx, 8);
        jal(ctx, 0x488EF4u, gen::fn_sub_488F30_00488f30);
        s0 = addiu(s0, 1);
        v1 = slti(s0, 310);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00488f14
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_488F30 [RpRandom] -- RpRandom: *front += *rear, the result the new value >> 1 (0 .. 2^31 - 1); front and rear step, wrapping at the table end
// The additive lagged generator of render_rw7.h (BSD TYPE_3, lag 31 / 3). When front reaches the end it wraps to
// the table start and rear steps without a check; else rear steps and wraps at the end. $v0 is zero-extended.
// 0x00488F30 sub_488F30 -- 164 bytes; leaf frame (no stack)
void sub_488F30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00488f30: *front += *rear; the result *front >> 1; front + 1
    enter(ctx, 22);  // entry check point + this block's cycles
    lw(v0, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    a1 = 0x960000;
    a1 = addiu(a1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(a1, v0);
    lw(v0, v1, rrand::kRear);
    lw(a0, v1, rrand::kFront);
    lw(v0, v0, 0);
    lw(v1, a0, 0);
    v0 = addu(v1, v0);
    sw(v0, a0, 0);
    lw(v0, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    a1 = addu(a1, v0);
    lw(v1, a1, rrand::kFront);
    lw(v0, v1, 0);
    a0 = addiu(v1, 4);
    sw(a0, a1, rrand::kFront);
    v0 = srl(v0, 1);
    lw(v1, a1, rrand::kEnd);
    v0 = dsll32(v0, 1);
    at = sltu(a0, v1);
    v0 = dsrl32(v0, 1);
    if (at == 0) {
        // 0x00488fb4: front wrapped: front = table, rear + 1
        charge(ctx, 6);
        lw(v1, a1, rrand::kTable);
        sw(v1, a1, rrand::kFront);
        lw(v1, a1, rrand::kRear);
        v1 = addiu(v1, 4);
        sw(v1, a1, rrand::kRear);
        backedge(ctx);
    L_00488fac:
        charge(ctx, 2);
    } else {
        // 0x00488f88: rear + 1, wrapping at the end
        charge(ctx, 7);
        lw(v1, a1, rrand::kRear);
        a0 = addiu(v1, 4);
        sw(a0, a1, rrand::kRear);
        lw(v1, a1, rrand::kEnd);
        v1 = sltu(a0, v1);
        if (v1 == 0) {
            // 0x00488fa4
            charge(ctx, 2);
            lw(v1, a1, rrand::kTable);
            sw(v1, a1, rrand::kRear);
            goto L_00488fac;
        }
    }
    // 0x00488fcc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_488FE0 [RpRandomPluginAttach] -- registers RpRandom (plugin 0x10C): 16 bytes of engine data, the open / close (sub_488D40 / sub_488CD0); 1 when registered
// The engine offset goes to gp 0x7CE778.
// 0x00488FE0 sub_488FE0 -- 60 bytes; frame 0x10: ra sp+0x0
void sub_488FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00488fe0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x490000;
    a3 = 0x490000;
    sd(ra, sp, 0x0);
    a0 = 16;
    a1 = 268;
    a2 = addiu(a2, -29376);  // &sub_488D40
    a3 = addiu(a3, -29488);  // &sub_488CD0
    jal(ctx, 0x488FFCu, gen::fn_sub_4CA520_004ca520);
    sw(v0, gp, -17784);  // 0x7CE778 (the RpRandom engine offset)
    ld(ra, sp, 0x0);
    v0 = slt(v0, 0);
    v0 = v0 ^ 0x1;
    sp = addiu(sp, 0x10);
}


// sub_48AD20 [splineOpenBasis] -- RpSpline's open: the twelve 257-entry basis tables (one RwMalloc of 12,336 bytes) -- the cubic B-spline weights and their derivatives at t = i / 256
// Tables 0..3 the cubic weights (t^3 / 6, (-3t^3 + 3t^2 + 3t + 1) / 6, (3t^3 - 6t^2 + 4) / 6, (1 - t)^3 / 6),
// 4..7 the first derivatives (/ 2), 8..11 the second derivatives; the pointers at gp 0x7CE77C..0x7CE7A8. 1, or
// error 0x80000013 (out of memory) and 0 when the allocation fails.
// 0x0048AD20 sub_48AD20 -- 604 bytes; frame 0x20: ra sp+0x0
void sub_48AD20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x0048ad20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x40000;
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = 12336;
    a1 = v1 | 0x102;
    jalr(ctx, 0x48AD38u, v0.u());
    sw(v0, gp, -17780);  // 0x7CE77C (RpSpline: the basis tables (12 x 257 floats from here))
    if (v0 == 0) {
        // 0x0048af44
        charge(ctx, 11);
        v1 = 258;
        v0 = lui(0x8000);
        sw(v1, sp, 0x18);
        a0 = v0 | 0x13;
        a1 = 12336;
        jal(ctx, 0x48AF54u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x1C);
        a0 = addiu(sp, 0x18);
        jal(ctx, 0x48AF60u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    } else {
        // 0x0048ad48
        charge(ctx, 43);
        v0 = addiu(v0, 1028);
        a0 = 0x43800000;
        sw(v0, gp, -17776);  // 0x7CE780
        mtc1(a0, f7);
        v0 = addiu(v0, 1028);
        a1 = 0x40C00000;
        sw(v0, gp, -17772);  // 0x7CE784
        a0 = lui(0xC040);
        v0 = addiu(v0, 1028);
        v1 = 0;
        sw(v0, gp, -17768);  // 0x7CE788
        mtc1(a1, f5);
        v0 = addiu(v0, 1028);
        sw(v0, gp, -17764);  // 0x7CE78C
        mtc1(a0, f4);
        v0 = addiu(v0, 1028);
        a1 = 0x40400000;
        sw(v0, gp, -17760);  // 0x7CE790
        a0 = 0x3F800000;
        v0 = addiu(v0, 1028);
        sw(v0, gp, -17756);  // 0x7CE794
        mtc1(a1, f3);
        v0 = addiu(v0, 1028);
        sw(v0, gp, -17752);  // 0x7CE798
        mtc1(a0, f1);
        v0 = addiu(v0, 1028);
        a1 = 0x40800000;
        sw(v0, gp, -17748);  // 0x7CE79C
        a0 = lui(0xBF80);
        v0 = addiu(v0, 1028);
        sw(v0, gp, -17744);  // 0x7CE7A0
        mtc1(a1, f0);
        v0 = addiu(v0, 1028);
        mtc1(a0, f14);
        sw(v0, gp, -17740);  // 0x7CE7A4
        v0 = addiu(v0, 1028);
        a1 = 0x40000000;
        a0 = lui(0xC080);
        sw(v0, gp, -17736);  // 0x7CE7A8
        mtc1(a1, f12);
        v0 = 0;
        mtc1(a0, f11);
        mtc1(zero, f2);
        for (;;) {
            // 0x0048adf4: the 257 entries of the twelve tables
            charge(ctx, 81);
            mtc1(v1, f6);
            lw(a0, gp, -17780);  // 0x7CE77C (RpSpline: the basis tables (12 x 257 floats from here))
            adda_s(f2, f3);
            cvt_s_w(f6, f6);
            v1 = addiu(v1, 1);
            at = slti(v1, 257);
            a0 = addu(a0, v0);
            div_s(f6, f6, f7);
            mul_s(f9, f6, f6);
            mul_s(f8, f6, f9);
            div_s(f8, f8, f5);
            swc1(f8, a0, 0);
            mul_s(f10, f4, f6);
            lw(a0, gp, -17776);  // 0x7CE780
            add_s(f8, f3, f10);
            a0 = addu(a0, v0);
            madd_s(f8, f8, f6);
            adda_s(f2, f1);
            madd_s(f8, f6, f8);
            div_s(f8, f8, f5);
            swc1(f8, a0, 0);
            mul_s(f15, f3, f6);
            lw(a0, gp, -17772);  // 0x7CE784
            sub_s(f8, f15, f5);
            a0 = addu(a0, v0);
            mul_s(f8, f8, f6);
            adda_s(f2, f0);
            madd_s(f8, f6, f8);
            div_s(f8, f8, f5);
            swc1(f8, a0, 0);
            mul_s(f13, f14, f6);
            lw(a0, gp, -17768);  // 0x7CE788
            add_s(f8, f3, f13);
            a0 = addu(a0, v0);
            mul_s(f8, f8, f6);
            sub_s(f8, f8, f3);
            adda_s(f2, f1);
            madd_s(f8, f6, f8);
            div_s(f8, f8, f5);
            swc1(f8, a0, 0);
            add_s(f8, f12, f10);
            lw(a0, gp, -17764);  // 0x7CE78C
            adda_s(f2, f1);
            madd_s(f8, f8, f6);
            div_s(f9, f9, f12);
            a0 = addu(a0, v0);
            swc1(f9, a0, 0);
            lw(a0, gp, -17760);  // 0x7CE790
            div_s(f8, f8, f12);
            a0 = addu(a0, v0);
            swc1(f8, a0, 0);
            add_s(f8, f11, f15);
            lw(a0, gp, -17756);  // 0x7CE794
            mul_s(f8, f8, f6);
            a0 = addu(a0, v0);
            div_s(f8, f8, f12);
            swc1(f8, a0, 0);
            add_s(f8, f12, f13);
            lw(a0, gp, -17752);  // 0x7CE798
            mul_s(f8, f8, f6);
            a0 = addu(a0, v0);
            sub_s(f8, f8, f1);
            div_s(f8, f8, f12);
            swc1(f8, a0, 0);
            lw(a0, gp, -17748);  // 0x7CE79C
            add_s(f10, f1, f10);
            sub_s(f9, f15, f12);
            a0 = addu(a0, v0);
            swc1(f6, a0, 0);
            lw(a0, gp, -17744);  // 0x7CE7A0
            add_s(f8, f1, f13);
            a0 = addu(a0, v0);
            swc1(f10, a0, 0);
            lw(a0, gp, -17740);  // 0x7CE7A4
            a0 = addu(a0, v0);
            swc1(f9, a0, 0);
            lw(a0, gp, -17736);  // 0x7CE7A8
            a0 = addu(a0, v0);
            swc1(f8, a0, 0);
            v0 = addiu(v0, 4);
            if (at == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0048af38
    charge(ctx, 3);
    lw(v0, gp, -17780);  // 0x7CE77C (RpSpline: the basis tables (12 x 257 floats from here))
    v0 = sltu(0, v0);
    // 0x0048af70
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_48AF80 [splineEndMatrix] -- builds the n x n float matrix of an open spline's end conditions (the inverse of the 1 4 1 system with its ends)
// From the integer sequences d[i] = 4 d[i-1] - d[i-2] (1, 4, ... and 1, 2, ...): entry (i, j) = +-d[..] x d[..] /
// the determinant term, the sign alternating, then mirrored about the anti-diagonal. RwMalloc'd (the scratch
// sequences freed); 0 and error 0x80000013 when an allocation fails.
// 0x0048AF80 sub_48AF80 -- 2448 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48AF80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048af80
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = sll(s5, 2);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    mult(s0, s5, s3);
    s2 = 0x960000;
    s2 = addiu(s2, 376);  // &0x960178 (RwMalloc slot)
    v1 = 0x30000;
    lw(v0, s2, 0);  // 0x960178 (RwMalloc slot)
    a1 = v1 | 0x102;
    a0 = s0;
    jalr(ctx, 0x48AFC4u, v0.u());
    s4 = v0;
    if (s4 == 0) {
        // 0x0048b828
        charge(ctx, 11);
        v0 = 258;
        a1 = s0;
        sw(v0, sp, 0x98);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x48B838u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x9C);
        a0 = addiu(sp, 0x98);
        jal(ctx, 0x48B844u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x0048afd8
        charge(ctx, 14);
        mult(s1, s5, s5);
        a0 = s4;
        a1 = 0;
        a2 = sll(s1, 2);
        jal(ctx, 0x48AFE4u, gen::fn_memset_00521408);
        v0 = 0x30000;
        v1 = addiu(s5, -1);
        a1 = v0 | 0x102;
        s0 = sll(v1, 2);
        lw(v0, s2, 0);
        a0 = s0;
        jalr(ctx, 0x48B000u, v0.u());
        if (v0 == 0) {
            // 0x0048b854
            charge(ctx, 11);
            v0 = 258;
            a1 = s0;
            sw(v0, sp, 0x90);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x48B864u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x94);
            a0 = addiu(sp, 0x90);
            jal(ctx, 0x48B870u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            backedge(ctx);
        } else {
            // 0x0048b010
            charge(ctx, 8);
            a3 = 1;
            a2 = addiu(s5, -1);
            v1 = 4;
            sw(a3, v0, 0);
            at = slti(a2, 3);
            a1 = 2;
            sw(v1, v0, 4);
            if (at == 0) {
                // 0x0048b030
                charge(ctx, 4);
                a0 = addiu(s5, -3);
                at = slti(a0, 9);
                v1 = addiu(s5, -9);
                if (at == 0) {
                    // 0x0048b040
                    charge(ctx, 3);
                    a0 = slti(a2, 2);
                    t0 = 0;
                    if (a0 == 0) {
                        // 0x0048b04c
                        charge(ctx, 5);
                        at = 0x7FFF0000;
                        at = at | 0xFFFF;
                        at = slt(a2, at);
                        if (at != 0) {
                            // 0x0048b060
                            charge(ctx, 1);
                            t0 = a3;
                        }
                    }
                    // 0x0048b064
                    charge(ctx, 2);
                    if (t0 != 0) {
                        // 0x0048b06c
                        charge(ctx, 1);
                        a0 = addiu(v0, 8);
                        for (;;) {
                            // 0x0048b070
                            charge(ctx, 44);
                            lw(t0, a0, -4);
                            a1 = addiu(a1, 8);
                            lw(a3, a0, -8);
                            a2 = slt(a1, v1);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 0);
                            lw(t0, a0, 0);
                            lw(a3, a0, -4);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 4);
                            lw(t0, a0, 4);
                            lw(a3, a0, 0);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 8);
                            lw(t0, a0, 8);
                            lw(a3, a0, 4);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 12);
                            lw(t0, a0, 12);
                            lw(a3, a0, 8);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 16);
                            lw(t0, a0, 16);
                            lw(a3, a0, 12);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 20);
                            lw(t0, a0, 20);
                            lw(a3, a0, 16);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 24);
                            lw(t0, a0, 24);
                            lw(a3, a0, 20);
                            t0 = sll(t0, 2);
                            a3 = subu(t0, a3);
                            sw(a3, a0, 28);
                            a0 = addiu(a0, 32);
                            if (a2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                // 0x0048b120
                charge(ctx, 4);
                a3 = addiu(s5, -1);
                at = slt(a1, a3);
                if (at != 0) {
                    // 0x0048b130
                    charge(ctx, 2);
                    v1 = sll(a1, 2);
                    t0 = addu(v0, v1);
                    for (;;) {
                        // 0x0048b138
                        charge(ctx, 9);
                        lw(a2, t0, -4);
                        a1 = addiu(a1, 1);
                        lw(a0, t0, -8);
                        v1 = slt(a1, a3);
                        a2 = sll(a2, 2);
                        a0 = subu(a2, a0);
                        sw(a0, t0, 0);
                        t0 = addiu(t0, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048b15c
                    charge(ctx, 1);
                }
            }
        }
        // 0x0048b160
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0048b880
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s4;
            jalr(ctx, 0x48B888u, v0.u());
            v0 = 0;
        } else {
            // 0x0048b168
            charge(ctx, 15);
            v1 = sll(s5, 2);
            s0 = 0x960000;
            v1 = addu(v1, v0);
            s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
            a0 = v0;
            lw(v0, s0, 0);  // 0x96017C (RwFree slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x48B180u);  // $ra = the return address
            lw(s6, v1, -8);
            call_ptr(ctx, jt);
            lw(v0, s2, 0);
            v1 = 0x30000;
            a0 = s3;
            a1 = v1 | 0x102;
            jalr(ctx, 0x48B194u, v0.u());
            if (v0 == 0) {
                // 0x0048b898
                charge(ctx, 11);
                v0 = 258;
                a1 = s3;
                sw(v0, sp, 0x88);
                v0 = lui(0x8000);
                a0 = v0 | 0x13;
                jal(ctx, 0x48B8A8u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x8C);
                a0 = addiu(sp, 0x88);
                jal(ctx, 0x48B8B4u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                backedge(ctx);
            } else {
                // 0x0048b1a4
                charge(ctx, 6);
                a2 = 1;
                a1 = 2;
                sw(a2, v0, 0);
                at = slti(s5, 3);
                sw(a1, v0, 4);
                if (at == 0) {
                    // 0x0048b1bc
                    charge(ctx, 4);
                    a0 = addiu(s5, -2);
                    at = slti(a0, 9);
                    v1 = addiu(s5, -8);
                    if (at == 0) {
                        // 0x0048b1cc
                        charge(ctx, 3);
                        a0 = slti(s5, 2);
                        a3 = 0;
                        if (a0 == 0) {
                            // 0x0048b1d8
                            charge(ctx, 5);
                            at = 0x7FFF0000;
                            at = at | 0xFFFF;
                            at = slt(s5, at);
                            if (at != 0) {
                                // 0x0048b1ec
                                charge(ctx, 1);
                                a3 = a2;
                            }
                        }
                        // 0x0048b1f0
                        charge(ctx, 2);
                        if (a3 != 0) {
                            // 0x0048b1f8
                            charge(ctx, 1);
                            a0 = addiu(v0, 8);
                            for (;;) {
                                // 0x0048b1fc
                                charge(ctx, 44);
                                lw(t0, a0, -4);
                                a1 = addiu(a1, 8);
                                lw(a3, a0, -8);
                                a2 = slt(a1, v1);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 0);
                                lw(t0, a0, 0);
                                lw(a3, a0, -4);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 4);
                                lw(t0, a0, 4);
                                lw(a3, a0, 0);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 8);
                                lw(t0, a0, 8);
                                lw(a3, a0, 4);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 12);
                                lw(t0, a0, 12);
                                lw(a3, a0, 8);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 16);
                                lw(t0, a0, 16);
                                lw(a3, a0, 12);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 20);
                                lw(t0, a0, 20);
                                lw(a3, a0, 16);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 24);
                                lw(t0, a0, 24);
                                lw(a3, a0, 20);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 28);
                                a0 = addiu(a0, 32);
                                if (a2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048b2ac
                            charge(ctx, 1);
                        }
                    }
                    // 0x0048b2b0
                    charge(ctx, 3);
                    at = slt(a1, s5);
                    if (at != 0) {
                        // 0x0048b2bc
                        charge(ctx, 2);
                        v1 = sll(a1, 2);
                        a3 = addu(v0, v1);
                        for (;;) {
                            // 0x0048b2c4
                            charge(ctx, 9);
                            lw(a2, a3, -4);
                            a1 = addiu(a1, 1);
                            lw(a0, a3, -8);
                            v1 = slt(a1, s5);
                            a2 = sll(a2, 2);
                            a0 = subu(a2, a0);
                            sw(a0, a3, 0);
                            a3 = addiu(a3, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
            }
            // 0x0048b2e8
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0048b8c4
                charge(ctx, 5);
                lw(v0, s0, 0);
                a0 = s4;
                jalr(ctx, 0x48B8C8u, v0.u());
                v0 = 0;
            } else {
                // 0x0048b2f0
                charge(ctx, 3);
                a0 = addiu(s5, -2);
                if (i64(a0) >= 0) {
                    // 0x0048b2fc
                    charge(ctx, 2);
                    v1 = sra(s5, 1);
                    if (i64(s5) < 0) {
                        // 0x0048b304
                        charge(ctx, 2);
                        v1 = addiu(s5, 1);
                        v1 = sra(v1, 1);
                    }
                    // 0x0048b30c
                    charge(ctx, 3);
                    at = slti(v1, 9);
                    if (at == 0) {
                        // 0x0048b318
                        charge(ctx, 3);
                        a1 = addiu(s5, -2);
                        a2 = 0;
                        if (i64(a1) >= 0) {
                            // 0x0048b324
                            charge(ctx, 5);
                            v1 = lui(0x8000);
                            v1 = v1 | 0x2;
                            v1 = slt(a1, v1);
                            if (v1 == 0) {
                                // 0x0048b338
                                charge(ctx, 1);
                                a2 = 1;
                            }
                        }
                        // 0x0048b33c
                        charge(ctx, 2);
                        if (a2 != 0) {
                            // 0x0048b344
                            charge(ctx, 2);
                            v1 = sll(a0, 2);
                            v1 = addu(v0, v1);
                            for (;;) {
                                // 0x0048b34c
                                charge(ctx, 28);
                                lw(a1, v1, 0);
                                a0 = addiu(a0, -16);
                                at = slti(a0, 16);
                                a1 = subu(0, a1);
                                sw(a1, v1, 0);
                                lw(a1, v1, -8);
                                a1 = subu(0, a1);
                                sw(a1, v1, -8);
                                lw(a1, v1, -16);
                                a1 = subu(0, a1);
                                sw(a1, v1, -16);
                                lw(a1, v1, -24);
                                a1 = subu(0, a1);
                                sw(a1, v1, -24);
                                lw(a1, v1, -32);
                                a1 = subu(0, a1);
                                sw(a1, v1, -32);
                                lw(a1, v1, -40);
                                a1 = subu(0, a1);
                                sw(a1, v1, -40);
                                lw(a1, v1, -48);
                                a1 = subu(0, a1);
                                sw(a1, v1, -48);
                                lw(a1, v1, -56);
                                a1 = subu(0, a1);
                                sw(a1, v1, -56);
                                v1 = addiu(v1, -64);
                                if (at != 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048b3bc
                            charge(ctx, 1);
                        }
                    }
                    // 0x0048b3c0
                    charge(ctx, 2);
                    if (i64(a0) >= 0) {
                        // 0x0048b3c8
                        charge(ctx, 2);
                        v1 = sll(a0, 2);
                        a1 = addu(v0, v1);
                        for (;;) {
                            // 0x0048b3d0
                            charge(ctx, 7);
                            lw(v1, a1, 0);
                            a0 = addiu(a0, -2);
                            v1 = subu(0, v1);
                            sw(v1, a1, 0);
                            a1 = addiu(a1, -8);
                            if (i64(a0) < 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0048b3ec
                        charge(ctx, 1);
                    }
                }
                // 0x0048b3f0
                charge(ctx, 7);
                a0 = s5 & 0x1;
                t0 = 2;
                v1 = si(-2);
                at = slt(0, s5);
                if (a0 == 0) t0 = v1;
                t1 = 0;
                if (at != 0) {
                    // 0x0048b40c
                    charge(ctx, 6);
                    mtc1(s6, f0);
                    t5 = 0;
                    v1 = addiu(v0, 4);
                    a3 = addiu(s5, -1);
                    cvt_s_w(f1, f0);
                    a1 = 1;
                    for (;;) {
                        // 0x0048b424
                        charge(ctx, 13);
                        a0 = sll(t5, 2);
                        t2 = subu(a3, t1);
                        a2 = addu(s4, a0);
                        t6 = a1;
                        a0 = sll(t2, 2);
                        t2 = addu(v0, a0);
                        lwc1(f0, t2, 0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f0, f1);
                        swc1(f0, a2, 0);
                        if (i64(t1) > 0) {
                            // 0x0048b458
                            charge(ctx, 3);
                            at = slti(t1, 9);
                            a0 = addiu(t1, -8);
                            if (at == 0) {
                                // 0x0048b464
                                charge(ctx, 2);
                                t3 = 0;
                                if (i64(t1) > 0) {
                                    // 0x0048b46c
                                    charge(ctx, 5);
                                    at = 0x7FFF0000;
                                    at = at | 0xFFFF;
                                    at = slt(t1, at);
                                    if (at != 0) {
                                        // 0x0048b480
                                        charge(ctx, 2);
                                        t3 = a1;
                                    }
                                }
                                // 0x0048b488
                                charge(ctx, 2);
                                if (t3 != 0) {
                                    // 0x0048b490
                                    charge(ctx, 2);
                                    t4 = v1;
                                    t3 = addiu(a2, 4);
                                    for (;;) {
                                        // 0x0048b498
                                        charge(ctx, 77);
                                        lw(s2, t4, 0);
                                        lw(t7, t2, 0);
                                        mult(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 0);
                                        lw(s2, t4, 4);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 4);
                                        lw(s2, t4, 8);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 8);
                                        lw(s2, t4, 12);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 12);
                                        lw(s2, t4, 16);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 16);
                                        lw(s2, t4, 20);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 20);
                                        lw(s2, t4, 24);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 24);
                                        lw(s2, t4, 28);
                                        lw(t7, t2, 0);
                                        mult1(t7, s2, t7);
                                        mult(t7, t0, t7);
                                        t6 = addiu(t6, 8);
                                        at = slt(a0, t6);
                                        t4 = addiu(t4, 32);
                                        mtc1(t7, f0);
                                        cvt_s_w(f0, f0);
                                        div_s(f0, f0, f1);
                                        swc1(f0, t3, 28);
                                        t3 = addiu(t3, 32);
                                        if (at != 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0048b5cc
                                    charge(ctx, 1);
                                }
                            }
                            // 0x0048b5d0
                            charge(ctx, 3);
                            at = slt(t1, t6);
                            if (at == 0) {
                                // 0x0048b5dc
                                charge(ctx, 3);
                                a0 = sll(t6, 2);
                                t3 = addu(a2, a0);
                                t4 = addu(v0, a0);
                                for (;;) {
                                    // 0x0048b5e8
                                    charge(ctx, 14);
                                    lw(a2, t4, 0);
                                    lw(a0, t2, 0);
                                    mult(a0, a2, a0);
                                    mult(a0, t0, a0);
                                    t6 = addiu(t6, 1);
                                    at = slt(t1, t6);
                                    t4 = addiu(t4, 4);
                                    mtc1(a0, f0);
                                    cvt_s_w(f0, f0);
                                    div_s(f0, f0, f1);
                                    swc1(f0, t3, 0);
                                    t3 = addiu(t3, 4);
                                    if (at != 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        }
                        // 0x0048b620
                        charge(ctx, 4);
                        t1 = addiu(t1, 1);
                        a0 = slt(t1, s5);
                        t5 = addu(t5, s5);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0048b630
                charge(ctx, 7);
                v1 = sll(s1, 2);
                lwc1(f0, s4, 0);
                v1 = addu(v1, s4);
                at = slt(0, s5);
                t6 = 0;
                swc1(f0, v1, -4);
                if (at != 0) {
                    // 0x0048b64c
                    charge(ctx, 6);
                    v1 = lui(0x8000);
                    t4 = addiu(s5, -1);
                    t2 = v1 | 0x1;
                    s1 = 0;
                    t1 = 1;
                    t0 = slt(t4, t2);
                    for (;;) {
                        // 0x0048b664
                        charge(ctx, 3);
                        at = slt(t6, t4);
                        t5 = t4;
                        if (at != 0) {
                            // 0x0048b670
                            charge(ctx, 4);
                            v1 = subu(t4, t6);
                            at = slti(v1, 9);
                            t3 = addiu(t6, 8);
                            if (at == 0) {
                                // 0x0048b680
                                charge(ctx, 4);
                                v1 = slt(t4, t6);
                                a1 = 0;
                                a0 = 0;
                                if (v1 == 0) {
                                    // 0x0048b690
                                    charge(ctx, 3);
                                    v1 = slt(t6, t2);
                                    if (v1 == 0) {
                                        // 0x0048b69c
                                        charge(ctx, 2);
                                        a0 = t1;
                                    }
                                }
                                // 0x0048b8d8
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    backedge(ctx);
                                } else {
                                    // 0x0048b8e0
                                    charge(ctx, 2);
                                    backedge(ctx);
                                    // 0x0048b6a8
                                    charge(ctx, 2);
                                    if (t0 == 0) {
                                        // 0x0048b6b0
                                        charge(ctx, 2);
                                        a1 = t1;
                                    }
                                }
                                // 0x0048b6b8
                                charge(ctx, 2);
                                if (a1 != 0) {
                                    // 0x0048b6c0
                                    charge(ctx, 8);
                                    v1 = sll(s1, 2);
                                    a0 = sll(t5, 2);
                                    a1 = addu(s4, v1);
                                    v1 = subu(s5, t6);
                                    t7 = addu(a1, a0);
                                    mult(v1, s5, v1);
                                    a3 = addiu(v1, -1);
                                    for (;;) {
                                        // 0x0048b6e0
                                        charge(ctx, 51);
                                        v1 = subu(a3, t5);
                                        a0 = sll(v1, 2);
                                        a0 = addu(s4, a0);
                                        v1 = addiu(t5, -1);
                                        lwc1(f0, a0, 0);
                                        v1 = subu(a3, v1);
                                        v1 = sll(v1, 2);
                                        v1 = addu(s4, v1);
                                        swc1(f0, t7, 0);
                                        a0 = addiu(t5, -2);
                                        lwc1(f0, v1, 0);
                                        a1 = subu(a3, a0);
                                        a1 = sll(a1, 2);
                                        a0 = addiu(t5, -3);
                                        a0 = subu(a3, a0);
                                        a2 = addu(s4, a1);
                                        a0 = sll(a0, 2);
                                        a1 = addu(s4, a0);
                                        a0 = addiu(t5, -4);
                                        swc1(f0, t7, -4);
                                        a0 = subu(a3, a0);
                                        lwc1(f0, a2, 0);
                                        v1 = sll(a0, 2);
                                        a0 = addu(s4, v1);
                                        v1 = addiu(t5, -5);
                                        s2 = subu(a3, v1);
                                        v1 = addiu(t5, -6);
                                        s3 = sll(s2, 2);
                                        s2 = subu(a3, v1);
                                        swc1(f0, t7, -8);
                                        v1 = addu(s4, s3);
                                        lwc1(f0, a1, 0);
                                        s2 = sll(s2, 2);
                                        s3 = addu(s4, s2);
                                        s2 = addiu(t5, -7);
                                        s2 = subu(a3, s2);
                                        t5 = addiu(t5, -8);
                                        a2 = sll(s2, 2);
                                        at = slt(t3, t5);
                                        a2 = addu(s4, a2);
                                        swc1(f0, t7, -12);
                                        lwc1(f0, a0, 0);
                                        swc1(f0, t7, -16);
                                        lwc1(f0, v1, 0);
                                        swc1(f0, t7, -20);
                                        lwc1(f0, s3, 0);
                                        swc1(f0, t7, -24);
                                        lwc1(f0, a2, 0);
                                        swc1(f0, t7, -28);
                                        t7 = addiu(t7, -32);
                                        if (at == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0048b7ac
                                    charge(ctx, 1);
                                }
                            }
                            // 0x0048b7b0
                            charge(ctx, 3);
                            at = slt(t6, t5);
                            if (at != 0) {
                                // 0x0048b7bc
                                charge(ctx, 7);
                                v1 = sll(s1, 2);
                                a0 = sll(t5, 2);
                                a1 = addu(s4, v1);
                                v1 = subu(s5, t6);
                                a1 = addu(a1, a0);
                                mult(v1, s5, v1);
                                a0 = addiu(v1, -1);
                                for (;;) {
                                    // 0x0048b7d8
                                    charge(ctx, 9);
                                    v1 = subu(a0, t5);
                                    v1 = sll(v1, 2);
                                    t5 = addiu(t5, -1);
                                    v1 = addu(s4, v1);
                                    at = slt(t6, t5);
                                    lwc1(f0, v1, 0);
                                    swc1(f0, a1, 0);
                                    a1 = addiu(a1, -4);
                                    if (at == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x0048b7fc
                                charge(ctx, 1);
                            }
                        }
                        // 0x0048b800
                        charge(ctx, 4);
                        t6 = addiu(t6, 1);
                        v1 = slt(t6, s5);
                        s1 = addu(s1, s5);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0048b810
                charge(ctx, 6);
                a0 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x48B818u, v0.u());
                v0 = s4;
            }
        }
    }
    // 0x0048b8e8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}


// sub_48B910 [splineSolve] -- RpSpline's control-point solve: the user's points (+20) to the B-spline points (+56) so that the curve passes through them
// ($a0 = the spline, $a1 = the user's points) The tridiagonal system of the interpolating cubic (1 4 1) by the
// recurrence d[i] = 4 d[i-1] - d[i-2] (two integer tables, RwMalloc'd and freed): a closed spline (type 2) solves the
// cyclic system (odd / even point counts separately), an open one (type 1) the system with the end conditions and
// copies the end points; 1, or error 0x80000013 (out of memory) and 0 when the allocation fails.
// 0x0048B910 sub_48B910 -- 5612 bytes; frame 0x100: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_48B910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f20{ctx, 20};
    // 0x0048b910
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = a0;
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a1;
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    link(ctx, 0x48B944u);  // $ra first: the delay slot below depends on it
    swc1(f20, sp, 0x0);
    call(ctx, gen::fn_sub_48D200_0048d200);
    lw(v1, fp, 0xC);
    s3 = v0;
    v0 = 2;
    s4 = addiu(fp, 0x38);
    if (v1 == v0) {
        // 0x0048bb9c
        charge(ctx, 3);
        at = slti(s3, 10);
        if (at == 0) {
            // 0x0048bbb0
            charge(ctx, 1);
            s7 = 10;
        } else {
            // 0x0048bba8
            charge(ctx, 2);
            s7 = s3;
        }
        // 0x0048bbb4
        charge(ctx, 2);
        v0 = s7 & 0x1;
        if (i64(s7) < 0) {
            // 0x0048bbbc
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x0048bbc4
                charge(ctx, 1);
                v0 = addiu(v0, -2);
            }
        }
        // 0x0048bbc8
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0048bf20
            charge(ctx, 2);
            s2 = sra(s7, 1);
            if (i64(s7) < 0) {
                // 0x0048bf28
                charge(ctx, 2);
                v0 = addiu(s7, 1);
                s2 = sra(v0, 1);
            }
            // 0x0048bf30
            charge(ctx, 10);
            s1 = 0x960000;
            v0 = 0x30000;
            s1 = addiu(s1, 376);  // &0x960178 (RwMalloc slot)
            a1 = v0 | 0x102;
            lw(v0, s1, 0);  // 0x960178 (RwMalloc slot)
            s0 = sll(s2, 2);
            a0 = s0;
            jalr(ctx, 0x48BF48u, v0.u());
            if (v0 == 0) {
                // 0x0048ce68
                charge(ctx, 11);
                v0 = 258;
                a1 = s0;
                sw(v0, sp, 0xC8);
                v0 = lui(0x8000);
                a0 = v0 | 0x13;
                jal(ctx, 0x48CE78u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0xCC);
                a0 = addiu(sp, 0xC8);
                jal(ctx, 0x48CE84u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                backedge(ctx);
            } else {
                // 0x0048bf58
                charge(ctx, 7);
                a2 = 1;
                v1 = 4;
                sw(a2, v0, 0);
                at = slti(s2, 3);
                a1 = 2;
                sw(v1, v0, 4);
                if (at == 0) {
                    // 0x0048bf74
                    charge(ctx, 4);
                    a0 = addiu(s2, -2);
                    at = slti(a0, 9);
                    v1 = addiu(s2, -8);
                    if (at == 0) {
                        // 0x0048bf84
                        charge(ctx, 3);
                        a0 = slti(s2, 2);
                        a3 = 0;
                        if (a0 == 0) {
                            // 0x0048bf90
                            charge(ctx, 5);
                            at = 0x7FFF0000;
                            at = at | 0xFFFF;
                            at = slt(s2, at);
                            if (at != 0) {
                                // 0x0048bfa4
                                charge(ctx, 1);
                                a3 = a2;
                            }
                        }
                        // 0x0048bfa8
                        charge(ctx, 2);
                        if (a3 != 0) {
                            // 0x0048bfb0
                            charge(ctx, 1);
                            a0 = addiu(v0, 8);
                            for (;;) {
                                // 0x0048bfb4
                                charge(ctx, 44);
                                lw(t0, a0, -4);
                                a1 = addiu(a1, 8);
                                lw(a3, a0, -8);
                                a2 = slt(a1, v1);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 0);
                                lw(t0, a0, 0);
                                lw(a3, a0, -4);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 4);
                                lw(t0, a0, 4);
                                lw(a3, a0, 0);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 8);
                                lw(t0, a0, 8);
                                lw(a3, a0, 4);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 12);
                                lw(t0, a0, 12);
                                lw(a3, a0, 8);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 16);
                                lw(t0, a0, 16);
                                lw(a3, a0, 12);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 20);
                                lw(t0, a0, 20);
                                lw(a3, a0, 16);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 24);
                                lw(t0, a0, 24);
                                lw(a3, a0, 20);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 28);
                                a0 = addiu(a0, 32);
                                if (a2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048c064
                            charge(ctx, 1);
                        }
                    }
                    // 0x0048c068
                    charge(ctx, 3);
                    at = slt(a1, s2);
                    if (at != 0) {
                        // 0x0048c074
                        charge(ctx, 2);
                        v1 = sll(a1, 2);
                        a3 = addu(v0, v1);
                        for (;;) {
                            // 0x0048c07c
                            charge(ctx, 9);
                            lw(a2, a3, -4);
                            a1 = addiu(a1, 1);
                            lw(a0, a3, -8);
                            v1 = slt(a1, s2);
                            a2 = sll(a2, 2);
                            a0 = subu(a2, a0);
                            sw(a0, a3, 0);
                            a3 = addiu(a3, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
            }
            // 0x0048c0a0
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0048ce94
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048c0a8
                charge(ctx, 24);
                a0 = sll(s2, 2);
                v1 = 0x3F800000;
                a1 = addu(a0, v0);
                s6 = 0x960000;
                lwc1(f0, a1, -4);
                a0 = v0;
                s6 = addiu(s6, 380);  // &0x96017C (RwFree slot)
                mtc1(v1, f1);
                lw(v0, s6, 0);  // 0x96017C (RwFree slot)
                cvt_s_w(f0, f0);
                div_s(f20, f1, f0);
                jalr(ctx, 0x48C0DCu, v0.u());
                lw(v0, s1, 0);
                v1 = 0x30000;
                a1 = v1 | 0x102;
                s1 = addiu(s2, 1);
                s0 = sll(s1, 2);
                a0 = s0;
                jalr(ctx, 0x48C0F8u, v0.u());
                if (v0 == 0) {
                    // 0x0048ce9c
                    charge(ctx, 11);
                    v0 = 258;
                    a1 = s0;
                    sw(v0, sp, 0xC0);
                    v0 = lui(0x8000);
                    a0 = v0 | 0x13;
                    jal(ctx, 0x48CEACu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xC4);
                    a0 = addiu(sp, 0xC0);
                    jal(ctx, 0x48CEB8u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    backedge(ctx);
                } else {
                    // 0x0048c108
                    charge(ctx, 6);
                    a2 = 1;
                    a1 = 2;
                    sw(a2, v0, 0);
                    at = slti(s1, 3);
                    sw(a1, v0, 4);
                    if (at == 0) {
                        // 0x0048c120
                        charge(ctx, 4);
                        a0 = addiu(s2, -1);
                        at = slti(a0, 9);
                        v1 = addiu(s2, -7);
                        if (at == 0) {
                            // 0x0048c130
                            charge(ctx, 3);
                            a0 = slti(s1, 2);
                            a3 = 0;
                            if (a0 == 0) {
                                // 0x0048c13c
                                charge(ctx, 5);
                                at = 0x7FFF0000;
                                at = at | 0xFFFF;
                                at = slt(s1, at);
                                if (at != 0) {
                                    // 0x0048c150
                                    charge(ctx, 1);
                                    a3 = a2;
                                }
                            }
                            // 0x0048c154
                            charge(ctx, 2);
                            if (a3 != 0) {
                                // 0x0048c15c
                                charge(ctx, 1);
                                a0 = addiu(v0, 8);
                                for (;;) {
                                    // 0x0048c160
                                    charge(ctx, 44);
                                    lw(t0, a0, -4);
                                    a1 = addiu(a1, 8);
                                    lw(a3, a0, -8);
                                    a2 = slt(a1, v1);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 0);
                                    lw(t0, a0, 0);
                                    lw(a3, a0, -4);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 4);
                                    lw(t0, a0, 4);
                                    lw(a3, a0, 0);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 8);
                                    lw(t0, a0, 8);
                                    lw(a3, a0, 4);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 12);
                                    lw(t0, a0, 12);
                                    lw(a3, a0, 8);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 16);
                                    lw(t0, a0, 16);
                                    lw(a3, a0, 12);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 20);
                                    lw(t0, a0, 20);
                                    lw(a3, a0, 16);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 24);
                                    lw(t0, a0, 24);
                                    lw(a3, a0, 20);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 28);
                                    a0 = addiu(a0, 32);
                                    if (a2 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        }
                        // 0x0048c210
                        charge(ctx, 3);
                        at = slt(a1, s1);
                        if (at != 0) {
                            // 0x0048c21c
                            charge(ctx, 3);
                            v1 = sll(a1, 2);
                            a3 = addiu(s2, 1);
                            t0 = addu(v0, v1);
                            for (;;) {
                                // 0x0048c228
                                charge(ctx, 9);
                                lw(a2, t0, -4);
                                a1 = addiu(a1, 1);
                                lw(a0, t0, -8);
                                v1 = slt(a1, a3);
                                a2 = sll(a2, 2);
                                a0 = subu(a2, a0);
                                sw(a0, t0, 0);
                                t0 = addiu(t0, 4);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048c24c
                            charge(ctx, 1);
                        }
                    }
                }
                // 0x0048c250
                charge(ctx, 2);
                if (v0 != 0) {
                L_0048c260:
                    charge(ctx, 3);
                    v1 = addiu(s2, -1);
                    if (i64(v1) >= 0) {
                        // 0x0048c26c
                        charge(ctx, 2);
                        a0 = sra(s1, 1);
                        if (i64(s1) < 0) {
                            // 0x0048c274
                            charge(ctx, 2);
                            a0 = addiu(s1, 1);
                            a0 = sra(a0, 1);
                        }
                        // 0x0048c27c
                        charge(ctx, 3);
                        at = slti(a0, 9);
                        if (at == 0) {
                            // 0x0048c288
                            charge(ctx, 2);
                            a1 = 0;
                            if (i64(v1) >= 0) {
                                // 0x0048c290
                                charge(ctx, 5);
                                a0 = lui(0x8000);
                                a0 = a0 | 0x2;
                                a0 = slt(v1, a0);
                                if (a0 == 0) {
                                    // 0x0048c2a4
                                    charge(ctx, 1);
                                    a1 = 1;
                                }
                            }
                            // 0x0048c2a8
                            charge(ctx, 2);
                            if (a1 != 0) {
                                // 0x0048c2b0
                                charge(ctx, 2);
                                a0 = sll(v1, 2);
                                a0 = addu(v0, a0);
                                for (;;) {
                                    // 0x0048c2b8
                                    charge(ctx, 28);
                                    lw(a1, a0, 0);
                                    v1 = addiu(v1, -16);
                                    at = slti(v1, 16);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, 0);
                                    lw(a1, a0, -8);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -8);
                                    lw(a1, a0, -16);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -16);
                                    lw(a1, a0, -24);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -24);
                                    lw(a1, a0, -32);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -32);
                                    lw(a1, a0, -40);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -40);
                                    lw(a1, a0, -48);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -48);
                                    lw(a1, a0, -56);
                                    a1 = subu(0, a1);
                                    sw(a1, a0, -56);
                                    a0 = addiu(a0, -64);
                                    if (at != 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        }
                        // 0x0048c328
                        charge(ctx, 2);
                        if (i64(v1) >= 0) {
                            // 0x0048c330
                            charge(ctx, 2);
                            a0 = sll(v1, 2);
                            a1 = addu(v0, a0);
                            for (;;) {
                                // 0x0048c338
                                charge(ctx, 7);
                                lw(a0, a1, 0);
                                v1 = addiu(v1, -2);
                                a0 = subu(0, a0);
                                sw(a0, a1, 0);
                                a1 = addiu(a1, -8);
                                if (i64(v1) < 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048c354
                            charge(ctx, 1);
                        }
                    }
                    // 0x0048c358
                    charge(ctx, 3);
                    at = slt(0, s3);
                    t2 = 0;
                    if (at != 0) {
                        // 0x0048c364
                        charge(ctx, 8);
                        v1 = addiu(s7, 1);
                        a0 = sll(s2, 2);
                        t5 = s4;
                        a3 = addiu(s2, 1);
                        t0 = addu(v0, a0);
                        t4 = addiu(s2, -7);
                        a2 = sra(v1, 1);
                        if (i64(v1) < 0) {
                            // 0x0048c384
                            charge(ctx, 2);
                            v1 = addiu(v1, 1);
                            a2 = sra(v1, 1);
                        }
                        // 0x0048c38c
                        charge(ctx, 4);
                        mtc1(zero, f0);
                        a1 = addiu(a2, -1);
                        t3 = addiu(a2, -8);
                        a0 = 1;
                        for (;;) {
                            // 0x0048c39c
                            charge(ctx, 17);
                            div(t2, s3);
                            mfhi(t6);
                            at = slti(a3, 2);
                            lwc1(f1, t0, 0);
                            t1 = a0;
                            v1 = sll(t6, 1);
                            v1 = addu(v1, t6);
                            v1 = sll(v1, 2);
                            v1 = addu(s5, v1);
                            cvt_s_w(f4, f1);
                            lwc1(f3, v1, 0);
                            lwc1(f2, v1, 4);
                            lwc1(f1, v1, 8);
                            mul_s(f6, f4, f3);
                            mul_s(f5, f4, f2);
                            mul_s(f7, f4, f1);
                            if (at == 0) {
                                // 0x0048c3e0
                                charge(ctx, 3);
                                at = slti(s2, 9);
                                if (at == 0) {
                                    // 0x0048c3ec
                                    charge(ctx, 2);
                                    v1 = 0;
                                    if (i64(a3) > 0) {
                                        // 0x0048c3f4
                                        charge(ctx, 5);
                                        at = 0x7FFF0000;
                                        at = at | 0xFFFF;
                                        at = slt(a3, at);
                                        if (at != 0) {
                                            // 0x0048c408
                                            charge(ctx, 2);
                                            v1 = a0;
                                        }
                                    }
                                    // 0x0048c410
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        for (;;) {
                                            // 0x0048c418
                                            charge(ctx, 178);
                                            v1 = addu(t1, t2);
                                            div(v1, s3);
                                            mfhi(v1);
                                            t6 = subu(s2, t1);
                                            t6 = sll(t6, 2);
                                            t7 = addiu(t1, 1);
                                            s0 = addu(v0, t6);
                                            lwc1(f1, s0, 0);
                                            t6 = addu(t7, t2);
                                            adda_s(f0, f6);
                                            s0 = sll(v1, 1);
                                            v1 = addu(s0, v1);
                                            v1 = sll(v1, 2);
                                            v1 = addu(s5, v1);
                                            cvt_s_w(f4, f1);
                                            lwc1(f2, v1, 0);
                                            lwc1(f1, v1, 8);
                                            madd_s(f3, f2, f4);
                                            lwc1(f2, v1, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f2, f4);
                                            adda_s(f0, f7);
                                            madd_s(f6, f1, f4);
                                            div(t6, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t7 = addiu(t1, 2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            adda_s(f0, f3);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = addu(t7, t2);
                                            t6 = addu(s5, t6);
                                            lwc1(f4, t6, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(v1, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t7 = addiu(t1, 3);
                                            adda_s(f0, f2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = addu(t7, t2);
                                            t6 = addu(s5, t6);
                                            lwc1(f4, t6, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(v1, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t7 = addiu(t1, 4);
                                            adda_s(f0, f2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = addu(t7, t2);
                                            t6 = addu(s5, t6);
                                            lwc1(f4, t6, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(v1, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t7 = addiu(t1, 5);
                                            adda_s(f0, f2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = addu(t7, t2);
                                            t6 = addu(s5, t6);
                                            lwc1(f4, t6, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(v1, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t7 = addiu(t1, 6);
                                            adda_s(f0, f2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = addu(t7, t2);
                                            t6 = addu(s5, t6);
                                            lwc1(f4, t6, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(v1, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t7 = addiu(t1, 7);
                                            adda_s(f0, f2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = addu(t7, t2);
                                            t6 = addu(s5, t6);
                                            lwc1(f4, t6, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f6);
                                            madd_s(f4, f1, f3);
                                            div(v1, s3);
                                            mfhi(t6);
                                            v1 = subu(s2, t7);
                                            v1 = sll(v1, 2);
                                            t1 = addiu(t1, 8);
                                            adda_s(f0, f2);
                                            v1 = addu(v0, v1);
                                            lwc1(f2, v1, 0);
                                            v1 = sll(t6, 1);
                                            t6 = addu(v1, t6);
                                            t6 = sll(t6, 2);
                                            v1 = slt(t1, t4);
                                            t6 = addu(s5, t6);
                                            lwc1(f3, t6, 0);
                                            cvt_s_w(f2, f2);
                                            madd_s(f6, f3, f2);
                                            lwc1(f1, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f2);
                                            lwc1(f1, t6, 8);
                                            adda_s(f0, f4);
                                            madd_s(f7, f1, f2);
                                            if (v1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                    }
                                }
                                // 0x0048c6e0
                                charge(ctx, 3);
                                at = slt(t1, a3);
                                if (at != 0) {
                                    // 0x0048c6ec
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x0048c6f0
                                        charge(ctx, 24);
                                        v1 = addu(t1, t2);
                                        div(v1, s3);
                                        mfhi(t7);
                                        v1 = subu(s2, t1);
                                        v1 = sll(v1, 2);
                                        t1 = addiu(t1, 1);
                                        t6 = addu(v0, v1);
                                        lwc1(f1, t6, 0);
                                        v1 = slt(t1, a3);
                                        adda_s(f0, f6);
                                        t6 = sll(t7, 1);
                                        t6 = addu(t6, t7);
                                        t6 = sll(t6, 2);
                                        t6 = addu(s5, t6);
                                        cvt_s_w(f3, f1);
                                        lwc1(f2, t6, 0);
                                        lwc1(f1, t6, 8);
                                        madd_s(f6, f2, f3);
                                        lwc1(f2, t6, 4);
                                        adda_s(f0, f5);
                                        madd_s(f5, f2, f3);
                                        adda_s(f0, f7);
                                        madd_s(f7, f1, f3);
                                        if (v1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                            }
                            // 0x0048c750
                            charge(ctx, 3);
                            at = slti(a2, 2);
                            t1 = a0;
                            if (at == 0) {
                                // 0x0048c75c
                                charge(ctx, 3);
                                at = slti(a1, 9);
                                if (at == 0) {
                                    // 0x0048c768
                                    charge(ctx, 2);
                                    v1 = 0;
                                    if (i64(a2) > 0) {
                                        // 0x0048c770
                                        charge(ctx, 5);
                                        at = 0x7FFF0000;
                                        at = at | 0xFFFF;
                                        at = slt(a2, at);
                                        if (at != 0) {
                                            // 0x0048c784
                                            charge(ctx, 1);
                                            v1 = a0;
                                        }
                                    }
                                    // 0x0048c788
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        // 0x0048c790
                                        charge(ctx, 2);
                                        v1 = addu(s3, t2);
                                        for (;;) {
                                            // 0x0048c798
                                            charge(ctx, 178);
                                            t6 = subu(v1, t1);
                                            div(t6, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, t1);
                                            t7 = sll(t7, 2);
                                            s0 = addiu(t1, 1);
                                            s1 = addu(v0, t7);
                                            lwc1(f1, s1, 0);
                                            t7 = subu(v1, s0);
                                            adda_s(f0, f6);
                                            s1 = sll(t6, 1);
                                            t6 = addu(s1, t6);
                                            t6 = sll(t6, 2);
                                            t6 = addu(s5, t6);
                                            cvt_s_w(f4, f1);
                                            lwc1(f2, t6, 0);
                                            lwc1(f1, t6, 8);
                                            madd_s(f3, f2, f4);
                                            lwc1(f2, t6, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f2, f4);
                                            adda_s(f0, f7);
                                            madd_s(f6, f1, f4);
                                            div(t7, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, s0);
                                            t7 = sll(t7, 2);
                                            s0 = addu(v0, t7);
                                            lwc1(f2, s0, 0);
                                            t7 = addiu(t1, 2);
                                            adda_s(f0, f3);
                                            s0 = sll(t6, 1);
                                            s0 = addu(s0, t6);
                                            s0 = sll(s0, 2);
                                            t6 = subu(v1, t7);
                                            s0 = addu(s5, s0);
                                            lwc1(f4, s0, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, s0, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, s0, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(t6, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, t7);
                                            t7 = sll(t7, 2);
                                            s0 = addu(v0, t7);
                                            adda_s(f0, f2);
                                            t7 = addiu(t1, 3);
                                            lwc1(f2, s0, 0);
                                            s0 = sll(t6, 1);
                                            s0 = addu(s0, t6);
                                            s0 = sll(s0, 2);
                                            t6 = subu(v1, t7);
                                            s0 = addu(s5, s0);
                                            lwc1(f4, s0, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, s0, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, s0, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(t6, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, t7);
                                            t7 = sll(t7, 2);
                                            s0 = addu(v0, t7);
                                            adda_s(f0, f2);
                                            t7 = addiu(t1, 4);
                                            lwc1(f2, s0, 0);
                                            s0 = sll(t6, 1);
                                            s0 = addu(s0, t6);
                                            s0 = sll(s0, 2);
                                            t6 = subu(v1, t7);
                                            s0 = addu(s5, s0);
                                            lwc1(f4, s0, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, s0, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, s0, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(t6, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, t7);
                                            t7 = sll(t7, 2);
                                            s0 = addu(v0, t7);
                                            adda_s(f0, f2);
                                            t7 = addiu(t1, 5);
                                            lwc1(f2, s0, 0);
                                            s0 = sll(t6, 1);
                                            s0 = addu(s0, t6);
                                            s0 = sll(s0, 2);
                                            t6 = subu(v1, t7);
                                            s0 = addu(s5, s0);
                                            lwc1(f4, s0, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, s0, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, s0, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(t6, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, t7);
                                            t7 = sll(t7, 2);
                                            s0 = addu(v0, t7);
                                            adda_s(f0, f2);
                                            t7 = addiu(t1, 6);
                                            lwc1(f2, s0, 0);
                                            s0 = sll(t6, 1);
                                            s0 = addu(s0, t6);
                                            s0 = sll(s0, 2);
                                            t6 = subu(v1, t7);
                                            s0 = addu(s5, s0);
                                            lwc1(f4, s0, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, s0, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, s0, 8);
                                            adda_s(f0, f6);
                                            madd_s(f6, f1, f3);
                                            div(t6, s3);
                                            mfhi(t6);
                                            t7 = subu(s2, t7);
                                            t7 = sll(t7, 2);
                                            s0 = addiu(t1, 7);
                                            adda_s(f0, f2);
                                            t7 = addu(v0, t7);
                                            lwc1(f2, t7, 0);
                                            t7 = sll(t6, 1);
                                            t7 = addu(t7, t6);
                                            t7 = sll(t7, 2);
                                            t6 = subu(v1, s0);
                                            t7 = addu(s5, t7);
                                            lwc1(f4, t7, 0);
                                            cvt_s_w(f3, f2);
                                            madd_s(f2, f4, f3);
                                            lwc1(f1, t7, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f3);
                                            lwc1(f1, t7, 8);
                                            adda_s(f0, f6);
                                            madd_s(f4, f1, f3);
                                            div(t6, s3);
                                            mfhi(t7);
                                            t6 = subu(s2, s0);
                                            t6 = sll(t6, 2);
                                            t1 = addiu(t1, 8);
                                            adda_s(f0, f2);
                                            t6 = addu(v0, t6);
                                            lwc1(f2, t6, 0);
                                            t6 = sll(t7, 1);
                                            t7 = addu(t6, t7);
                                            t7 = sll(t7, 2);
                                            t6 = slt(t1, t3);
                                            t7 = addu(s5, t7);
                                            lwc1(f3, t7, 0);
                                            cvt_s_w(f2, f2);
                                            madd_s(f6, f3, f2);
                                            lwc1(f1, t7, 4);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f2);
                                            lwc1(f1, t7, 8);
                                            adda_s(f0, f4);
                                            madd_s(f7, f1, f2);
                                            if (t6 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                    }
                                }
                                // 0x0048ca60
                                charge(ctx, 3);
                                at = slt(t1, a2);
                                if (at != 0) {
                                    // 0x0048ca6c
                                    charge(ctx, 1);
                                    t6 = addu(s3, t2);
                                    for (;;) {
                                        // 0x0048ca70
                                        charge(ctx, 24);
                                        v1 = subu(t6, t1);
                                        div(v1, s3);
                                        mfhi(v1);
                                        t7 = subu(s2, t1);
                                        t7 = sll(t7, 2);
                                        t1 = addiu(t1, 1);
                                        s0 = addu(v0, t7);
                                        lwc1(f1, s0, 0);
                                        t7 = slt(t1, a2);
                                        adda_s(f0, f6);
                                        s0 = sll(v1, 1);
                                        v1 = addu(s0, v1);
                                        v1 = sll(v1, 2);
                                        v1 = addu(s5, v1);
                                        cvt_s_w(f3, f1);
                                        lwc1(f2, v1, 0);
                                        lwc1(f1, v1, 8);
                                        madd_s(f6, f2, f3);
                                        lwc1(f2, v1, 4);
                                        adda_s(f0, f5);
                                        madd_s(f5, f2, f3);
                                        adda_s(f0, f7);
                                        madd_s(f7, f1, f3);
                                        if (t7 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                            }
                            // 0x0048cad0
                            charge(ctx, 10);
                            t2 = addiu(t2, 1);
                            mul_s(f1, f6, f20);
                            v1 = slt(t2, s3);
                            swc1(f1, t5, 12);
                            mul_s(f1, f5, f20);
                            swc1(f1, t5, 16);
                            mul_s(f1, f7, f20);
                            swc1(f1, t5, 20);
                            t5 = addiu(t5, 12);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x0048caf8
                    charge(ctx, 26);
                    a0 = v0;
                    v0 = sll(s3, 1);
                    v0 = addu(v0, s3);
                    v0 = sll(v0, 2);
                    v0 = addu(s4, v0);
                    lwc1(f2, v0, 0);
                    lwc1(f1, v0, 4);
                    lwc1(f0, v0, 8);
                    swc1(f2, s4, 0);
                    swc1(f1, s4, 4);
                    swc1(f0, s4, 8);
                    lwc1(f2, s4, 12);
                    lwc1(f1, s4, 16);
                    lwc1(f0, s4, 20);
                    swc1(f2, v0, 12);
                    swc1(f1, v0, 16);
                    swc1(f0, v0, 20);
                    lwc1(f2, s4, 24);
                    lwc1(f1, s4, 28);
                    lwc1(f0, s4, 32);
                    swc1(f2, v0, 24);
                    swc1(f1, v0, 28);
                    swc1(f0, v0, 32);
                    lw(v0, s6, 0);
                    jalr(ctx, 0x48CB58u, v0.u());
                L_0048cb60:
                    charge(ctx, 2);
                    v0 = fp;
                } else {
                    // 0x0048c258
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
        } else {
            // 0x0048bbd0
            charge(ctx, 2);
            s2 = sra(s7, 1);
            if (i64(s7) < 0) {
                // 0x0048bbd8
                charge(ctx, 2);
                v0 = addiu(s7, 1);
                s2 = sra(v0, 1);
            }
            // 0x0048bbe0
            charge(ctx, 13);
            v0 = 0x960000;
            s1 = addiu(s2, 1);
            v0 = addiu(v0, 376);  // &0x960178 (RwMalloc slot)
            s0 = sll(s1, 2);
            sq(v0, sp, 0xB0);
            v0 = 0x30000;
            a1 = v0 | 0x102;
            lq(v0, sp, 0xB0);
            lw(v0, v0, 0);
            a0 = s0;
            jalr(ctx, 0x48BC04u, v0.u());
            if (v0 == 0) {
                // 0x0048ce08
                charge(ctx, 11);
                v0 = 258;
                sw(v0, sp, 0xD8);
                a1 = s0;
                v0 = lui(0x8000);
                a0 = v0 | 0x13;
                jal(ctx, 0x48CE18u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0xDC);
                a0 = addiu(sp, 0xD8);
                jal(ctx, 0x48CE24u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                backedge(ctx);
            } else {
                // 0x0048bc14
                charge(ctx, 7);
                a2 = 1;
                v1 = 3;
                sw(a2, v0, 0);
                at = slti(s1, 3);
                a1 = 2;
                sw(v1, v0, 4);
                if (at == 0) {
                    // 0x0048bc30
                    charge(ctx, 4);
                    a0 = addiu(s2, -1);
                    at = slti(a0, 9);
                    v1 = addiu(s2, -7);
                    if (at == 0) {
                        // 0x0048bc40
                        charge(ctx, 3);
                        a0 = slti(s1, 2);
                        a3 = 0;
                        if (a0 == 0) {
                            // 0x0048bc4c
                            charge(ctx, 5);
                            at = 0x7FFF0000;
                            at = at | 0xFFFF;
                            at = slt(s1, at);
                            if (at != 0) {
                                // 0x0048bc60
                                charge(ctx, 1);
                                a3 = a2;
                            }
                        }
                        // 0x0048bc64
                        charge(ctx, 2);
                        if (a3 != 0) {
                            // 0x0048bc6c
                            charge(ctx, 1);
                            a0 = addiu(v0, 8);
                            for (;;) {
                                // 0x0048bc70
                                charge(ctx, 44);
                                lw(t0, a0, -4);
                                a1 = addiu(a1, 8);
                                lw(a3, a0, -8);
                                a2 = slt(a1, v1);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 0);
                                lw(t0, a0, 0);
                                lw(a3, a0, -4);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 4);
                                lw(t0, a0, 4);
                                lw(a3, a0, 0);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 8);
                                lw(t0, a0, 8);
                                lw(a3, a0, 4);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 12);
                                lw(t0, a0, 12);
                                lw(a3, a0, 8);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 16);
                                lw(t0, a0, 16);
                                lw(a3, a0, 12);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 20);
                                lw(t0, a0, 20);
                                lw(a3, a0, 16);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 24);
                                lw(t0, a0, 24);
                                lw(a3, a0, 20);
                                t0 = sll(t0, 2);
                                a3 = subu(t0, a3);
                                sw(a3, a0, 28);
                                a0 = addiu(a0, 32);
                                if (a2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                    }
                    // 0x0048bd20
                    charge(ctx, 3);
                    at = slt(a1, s1);
                    if (at != 0) {
                        // 0x0048bd2c
                        charge(ctx, 3);
                        v1 = sll(a1, 2);
                        a3 = addiu(s2, 1);
                        t0 = addu(v0, v1);
                        for (;;) {
                            // 0x0048bd38
                            charge(ctx, 9);
                            lw(a2, t0, -4);
                            a1 = addiu(a1, 1);
                            lw(a0, t0, -8);
                            v1 = slt(a1, a3);
                            a2 = sll(a2, 2);
                            a0 = subu(a2, a0);
                            sw(a0, t0, 0);
                            t0 = addiu(t0, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0048bd5c
                        charge(ctx, 1);
                    }
                }
            }
            // 0x0048bd60
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0048ce34
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048bd68
                charge(ctx, 23);
                a0 = sll(s2, 2);
                v1 = 0x3F800000;
                a1 = addu(v0, a0);
                s6 = 0x960000;
                lwc1(f0, a1, 0);
                a0 = v0;
                s6 = addiu(s6, 380);  // &0x96017C (RwFree slot)
                mtc1(v1, f1);
                lw(v0, s6, 0);  // 0x96017C (RwFree slot)
                cvt_s_w(f0, f0);
                div_s(f20, f1, f0);
                jalr(ctx, 0x48BD9Cu, v0.u());
                lq(v0, sp, 0xB0);
                v1 = 0x30000;
                a0 = s0;
                lw(v0, v0, 0);
                a1 = v1 | 0x102;
                jalr(ctx, 0x48BDB4u, v0.u());
                if (v0 == 0) {
                    // 0x0048ce3c
                    charge(ctx, 11);
                    v0 = 258;
                    a1 = s0;
                    sw(v0, sp, 0xD0);
                    v0 = lui(0x8000);
                    a0 = v0 | 0x13;
                    jal(ctx, 0x48CE4Cu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xD4);
                    a0 = addiu(sp, 0xD0);
                    jal(ctx, 0x48CE58u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    backedge(ctx);
                } else {
                    // 0x0048bdc4
                    charge(ctx, 7);
                    a2 = 1;
                    v1 = 5;
                    sw(a2, v0, 0);
                    at = slti(s1, 3);
                    a1 = 2;
                    sw(v1, v0, 4);
                    if (at == 0) {
                        // 0x0048bde0
                        charge(ctx, 4);
                        a0 = addiu(s2, -1);
                        at = slti(a0, 9);
                        v1 = addiu(s2, -7);
                        if (at == 0) {
                            // 0x0048bdf0
                            charge(ctx, 3);
                            a0 = slti(s1, 2);
                            a3 = 0;
                            if (a0 == 0) {
                                // 0x0048bdfc
                                charge(ctx, 5);
                                at = 0x7FFF0000;
                                at = at | 0xFFFF;
                                at = slt(s1, at);
                                if (at != 0) {
                                    // 0x0048be10
                                    charge(ctx, 1);
                                    a3 = a2;
                                }
                            }
                            // 0x0048be14
                            charge(ctx, 2);
                            if (a3 != 0) {
                                // 0x0048be1c
                                charge(ctx, 1);
                                a0 = addiu(v0, 8);
                                for (;;) {
                                    // 0x0048be20
                                    charge(ctx, 44);
                                    lw(t0, a0, -4);
                                    a1 = addiu(a1, 8);
                                    lw(a3, a0, -8);
                                    a2 = slt(a1, v1);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 0);
                                    lw(t0, a0, 0);
                                    lw(a3, a0, -4);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 4);
                                    lw(t0, a0, 4);
                                    lw(a3, a0, 0);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 8);
                                    lw(t0, a0, 8);
                                    lw(a3, a0, 4);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 12);
                                    lw(t0, a0, 12);
                                    lw(a3, a0, 8);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 16);
                                    lw(t0, a0, 16);
                                    lw(a3, a0, 12);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 20);
                                    lw(t0, a0, 20);
                                    lw(a3, a0, 16);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 24);
                                    lw(t0, a0, 24);
                                    lw(a3, a0, 20);
                                    t0 = sll(t0, 2);
                                    a3 = subu(t0, a3);
                                    sw(a3, a0, 28);
                                    a0 = addiu(a0, 32);
                                    if (a2 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        }
                        // 0x0048bed0
                        charge(ctx, 3);
                        at = slt(a1, s1);
                        if (at != 0) {
                            // 0x0048bedc
                            charge(ctx, 3);
                            v1 = sll(a1, 2);
                            a3 = addiu(s2, 1);
                            t0 = addu(v0, v1);
                            for (;;) {
                                // 0x0048bee8
                                charge(ctx, 9);
                                lw(a2, t0, -4);
                                a1 = addiu(a1, 1);
                                lw(a0, t0, -8);
                                v1 = slt(a1, a3);
                                a2 = sll(a2, 2);
                                a0 = subu(a2, a0);
                                sw(a0, t0, 0);
                                t0 = addiu(t0, 4);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0048bf0c
                            charge(ctx, 1);
                        }
                    }
                }
                // 0x0048bf10
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_0048c260;
                }
                // 0x0048bf18
                charge(ctx, 2);
                v0 = 0;
            }
        }
    } else {
        // 0x0048b960
        charge(ctx, 3);
        a0 = 1;
        if (v1 == a0) {
            // 0x0048b974
            charge(ctx, 3);
            at = slti(s3, 10);
            if (at == 0) {
                // 0x0048cb84
                charge(ctx, 2);
                s0 = 10;
                backedge(ctx);
            } else {
                // 0x0048b980
                charge(ctx, 1);
                s0 = s3;
            }
            // 0x0048b984
            charge(ctx, 7);
            v0 = 0x960000;
            v1 = sll(s0, 2);
            v0 = addiu(v0, -8640);  // &0x95DE40 (RpSpline: the solve's scratch)
            v0 = addu(v0, v1);
            lw(t0, v0, 0);
            if (t0 != 0) {
                // 0x0048b9a0
                charge(ctx, 3);
                at = slt(0, s3);
                s1 = 0;
                if (at != 0) {
                    // 0x0048b9ac
                    charge(ctx, 7);
                    t7 = 0;
                    t6 = subu(s0, s3);
                    t5 = s4;
                    a3 = addiu(sp, 0xF4);
                    a2 = addiu(sp, 0xF8);
                    a1 = sra(s0, 1);
                    if (i64(s0) < 0) {
                        // 0x0048b9c8
                        charge(ctx, 2);
                        v0 = addiu(s0, 1);
                        a1 = sra(v0, 1);
                    }
                    // 0x0048b9d0
                    charge(ctx, 12);
                    a0 = subu(s3, a1);
                    mult(t1, s0, a1);
                    v1 = subu(s3, s0);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = sll(t1, 2);
                    t3 = addu(s5, v0);
                    t4 = addu(t0, v1);
                    mtc1(zero, f0);
                    v0 = 1;
                    v1 = addiu(s0, -8);
                    for (;;) {
                        // 0x0048ba00
                        charge(ctx, 5);
                        t1 = slt(s1, a1);
                        sw(zero, sp, 0xF0);
                        sw(zero, a3, 0);
                        sw(zero, a2, 0);
                        if (t1 != 0) {
                            // 0x0048cbb4
                            charge(ctx, 3);
                            at = slt(0, s0);
                            t2 = 0;
                            if (at == 0) {
                                backedge(ctx);
                            } else {
                                // 0x0048cbc0
                                charge(ctx, 3);
                                at = slti(s0, 9);
                                if (at == 0) {
                                    // 0x0048cbcc
                                    charge(ctx, 3);
                                    at = slt(s0, 0);
                                    t1 = 0;
                                    if (at == 0) {
                                        // 0x0048cbd8
                                        charge(ctx, 5);
                                        at = 0x7FFF0000;
                                        at = at | 0xFFFF;
                                        at = slt(s0, at);
                                        if (at != 0) {
                                            // 0x0048cbec
                                            charge(ctx, 1);
                                            t1 = v0;
                                        }
                                    }
                                    // 0x0048cbf0
                                    charge(ctx, 2);
                                    if (t1 != 0) {
                                        // 0x0048cbf8
                                        charge(ctx, 4);
                                        t1 = sll(t7, 2);
                                        s2 = s5;
                                        s6 = addu(t0, t1);
                                        for (;;) {
                                            // 0x0048cc08
                                            charge(ctx, 91);
                                            t2 = addiu(t2, 8);
                                            lwc1(f1, sp, 0xF0);
                                            t1 = slt(t2, v1);
                                            lwc1(f7, s2, 0);
                                            lwc1(f6, s6, 0);
                                            lwc1(f4, a3, 0);
                                            lwc1(f5, s2, 4);
                                            lwc1(f2, a2, 0);
                                            adda_s(f0, f1);
                                            lwc1(f3, s2, 8);
                                            madd_s(f8, f7, f6);
                                            adda_s(f0, f4);
                                            madd_s(f7, f5, f6);
                                            adda_s(f0, f2);
                                            lwc1(f1, s2, 12);
                                            madd_s(f6, f3, f6);
                                            lwc1(f5, s6, 4);
                                            adda_s(f0, f8);
                                            lwc1(f3, s2, 16);
                                            lwc1(f2, s2, 20);
                                            madd_s(f4, f1, f5);
                                            adda_s(f0, f7);
                                            madd_s(f3, f3, f5);
                                            adda_s(f0, f6);
                                            madd_s(f8, f2, f5);
                                            lwc1(f1, s2, 24);
                                            lwc1(f7, s6, 8);
                                            adda_s(f0, f4);
                                            lwc1(f2, s2, 28);
                                            lwc1(f6, s6, 12);
                                            madd_s(f5, f1, f7);
                                            adda_s(f0, f3);
                                            madd_s(f4, f2, f7);
                                            adda_s(f0, f8);
                                            lwc1(f3, s2, 32);
                                            lwc1(f1, s2, 36);
                                            lwc1(f2, s2, 40);
                                            lwc1(f8, s6, 24);
                                            madd_s(f3, f3, f7);
                                            adda_s(f0, f5);
                                            madd_s(f5, f1, f6);
                                            adda_s(f0, f4);
                                            madd_s(f7, f2, f6);
                                            adda_s(f0, f3);
                                            lwc1(f1, s2, 44);
                                            lwc1(f3, s2, 48);
                                            lwc1(f4, s6, 16);
                                            lwc1(f2, s2, 52);
                                            madd_s(f6, f1, f6);
                                            adda_s(f0, f5);
                                            madd_s(f3, f3, f4);
                                            adda_s(f0, f7);
                                            madd_s(f9, f2, f4);
                                            adda_s(f0, f6);
                                            lwc1(f1, s2, 56);
                                            lwc1(f5, s2, 60);
                                            lwc1(f6, s6, 20);
                                            lwc1(f2, s2, 72);
                                            madd_s(f7, f1, f4);
                                            adda_s(f0, f3);
                                            madd_s(f5, f5, f6);
                                            lwc1(f4, s2, 64);
                                            adda_s(f0, f9);
                                            lwc1(f3, s2, 68);
                                            lwc1(f1, s2, 76);
                                            madd_s(f4, f4, f6);
                                            adda_s(f0, f7);
                                            madd_s(f3, f3, f6);
                                            adda_s(f0, f5);
                                            madd_s(f7, f2, f8);
                                            adda_s(f0, f4);
                                            madd_s(f6, f1, f8);
                                            adda_s(f0, f3);
                                            lwc1(f5, s2, 80);
                                            lwc1(f4, s6, 28);
                                            lwc1(f3, s2, 84);
                                            lwc1(f2, s2, 88);
                                            lwc1(f1, s2, 92);
                                            madd_s(f5, f5, f8);
                                            adda_s(f0, f7);
                                            s6 = addiu(s6, 32);
                                            madd_s(f3, f3, f4);
                                            adda_s(f0, f6);
                                            madd_s(f2, f2, f4);
                                            s2 = addiu(s2, 96);
                                            adda_s(f0, f5);
                                            madd_s(f1, f1, f4);
                                            swc1(f3, sp, 0xF0);
                                            swc1(f2, a3, 0);
                                            swc1(f1, a2, 0);
                                            if (t1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x0048cd74
                                        charge(ctx, 1);
                                    }
                                }
                                // 0x0048cd78
                                charge(ctx, 3);
                                at = slt(t2, s0);
                                if (at == 0) {
                                    backedge(ctx);
                                } else {
                                    // 0x0048cd84
                                    charge(ctx, 9);
                                    s2 = sll(t7, 2);
                                    t1 = sll(t2, 2);
                                    s6 = addu(t0, s2);
                                    s2 = sll(t2, 1);
                                    t1 = addu(s6, t1);
                                    s2 = addu(s2, t2);
                                    s2 = sll(s2, 2);
                                    s6 = addu(s5, s2);
                                    for (;;) {
                                        // 0x0048cda8
                                        charge(ctx, 21);
                                        t2 = addiu(t2, 1);
                                        lwc1(f1, sp, 0xF0);
                                        s2 = slt(t2, s0);
                                        lwc1(f6, t1, 0);
                                        lwc1(f5, s6, 0);
                                        lwc1(f3, a3, 0);
                                        lwc1(f4, s6, 4);
                                        lwc1(f2, s6, 8);
                                        adda_s(f0, f1);
                                        lwc1(f1, a2, 0);
                                        t1 = addiu(t1, 4);
                                        madd_s(f5, f5, f6);
                                        adda_s(f0, f3);
                                        madd_s(f3, f4, f6);
                                        swc1(f5, sp, 0xF0);
                                        s6 = addiu(s6, 12);
                                        swc1(f3, a3, 0);
                                        adda_s(f0, f1);
                                        madd_s(f1, f2, f6);
                                        swc1(f1, a2, 0);
                                        if (s2 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0048cdfc
                                    charge(ctx, 2);
                                    backedge(ctx);
                                }
                            }
                        } else {
                            // 0x0048ba14
                            charge(ctx, 3);
                            at = slt(s1, a0);
                            if (at == 0) {
                                // 0x0048baa8
                                charge(ctx, 3);
                                at = slt(0, s0);
                                t2 = 0;
                                if (at != 0) {
                                    // 0x0048bab4
                                    charge(ctx, 5);
                                    mult(t1, s0, t6);
                                    s2 = t3;
                                    t1 = sll(t1, 2);
                                    s6 = addu(t0, t1);
                                    for (;;) {
                                        // 0x0048bac8
                                        charge(ctx, 21);
                                        t2 = addiu(t2, 1);
                                        lwc1(f1, sp, 0xF0);
                                        t1 = slt(t2, s0);
                                        lwc1(f6, s6, 0);
                                        lwc1(f5, s2, 0);
                                        lwc1(f3, a3, 0);
                                        lwc1(f4, s2, 4);
                                        lwc1(f2, s2, 8);
                                        adda_s(f0, f1);
                                        lwc1(f1, a2, 0);
                                        s6 = addiu(s6, 4);
                                        madd_s(f5, f5, f6);
                                        adda_s(f0, f3);
                                        madd_s(f3, f4, f6);
                                        swc1(f5, sp, 0xF0);
                                        s2 = addiu(s2, 12);
                                        swc1(f3, a3, 0);
                                        adda_s(f0, f1);
                                        madd_s(f1, f2, f6);
                                        swc1(f1, a2, 0);
                                        if (t1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0048bb1c
                                    charge(ctx, 1);
                                }
                            } else {
                                // 0x0048ba20
                                charge(ctx, 3);
                                at = slt(0, s0);
                                t1 = 0;
                                if (at != 0) {
                                    // 0x0048ba2c
                                    charge(ctx, 7);
                                    s6 = subu(s1, a1);
                                    t2 = t4;
                                    s2 = sll(s6, 1);
                                    s2 = addu(s2, s6);
                                    s2 = sll(s2, 2);
                                    s6 = addu(s5, s2);
                                    for (;;) {
                                        // 0x0048ba48
                                        charge(ctx, 21);
                                        t1 = addiu(t1, 1);
                                        lwc1(f1, sp, 0xF0);
                                        s2 = slt(t1, s0);
                                        lwc1(f6, t2, 0);
                                        lwc1(f5, s6, 0);
                                        lwc1(f3, a3, 0);
                                        lwc1(f4, s6, 4);
                                        lwc1(f2, s6, 8);
                                        adda_s(f0, f1);
                                        lwc1(f1, a2, 0);
                                        t2 = addiu(t2, 4);
                                        madd_s(f5, f5, f6);
                                        adda_s(f0, f3);
                                        madd_s(f3, f4, f6);
                                        swc1(f5, sp, 0xF0);
                                        s6 = addiu(s6, 12);
                                        swc1(f3, a3, 0);
                                        adda_s(f0, f1);
                                        madd_s(f1, f2, f6);
                                        swc1(f1, a2, 0);
                                        if (s2 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0048ba9c
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x0048bb20
                        charge(ctx, 13);
                        s1 = addiu(s1, 1);
                        lwc1(f3, sp, 0xF0);
                        t2 = addiu(t5, 12);
                        lwc1(f2, sp, 0xF4);
                        t1 = slt(s1, s3);
                        lwc1(f1, sp, 0xF8);
                        t7 = addu(t7, s0);
                        t6 = addiu(t6, 1);
                        swc1(f3, t5, 12);
                        swc1(f2, t5, 16);
                        swc1(f1, t5, 20);
                        t5 = t2;
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048bb54
                    charge(ctx, 1);
                }
                // 0x0048bb58
                charge(ctx, 17);
                v0 = sll(s3, 1);
                lwc1(f2, s4, 24);
                v0 = addu(v0, s3);
                lwc1(f1, s4, 28);
                v0 = sll(v0, 2);
                lwc1(f0, s4, 32);
                v0 = addu(v0, s4);
                swc1(f2, s4, 0);
                swc1(f1, s4, 4);
                swc1(f0, s4, 8);
                lwc1(f2, v0, -12);
                lwc1(f1, v0, -8);
                lwc1(f0, v0, -4);
                swc1(f2, v0, 12);
                swc1(f1, v0, 16);
                swc1(f0, v0, 20);
                goto L_0048cb60;
            }
            // 0x0048cb8c
            charge(ctx, 10);
            v1 = 258;
            v0 = lui(0x8000);
            sw(v1, sp, 0xE8);
            a0 = v0 | 0x16;
            jal(ctx, 0x48CB98u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xEC);
            a0 = addiu(sp, 0xE8);
            jal(ctx, 0x48CBA4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x0048b96c
            charge(ctx, 2);
            v0 = 258;
            // 0x0048cb68
            charge(ctx, 7);
            link(ctx, 0x48CB68u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0xE0);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xE4);
            a0 = addiu(sp, 0xE0);
            jal(ctx, 0x48CB74u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        }
    }
    // 0x0048cec8 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x100);
}


// sub_48CF00 [splineClose] -- RpSpline's close: at the last close the basis tables freed (RwFree x 8 of the scratch, then the block); $a0
// 0x0048CF00 sub_48CF00 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48CF00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048cf00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17724);  // 0x7CE7B4 (RpSpline's open count)
    s0 = a0;
    v0 = addiu(v0, -1);
    sw(v0, gp, -17724);  // 0x7CE7B4 (RpSpline's open count)
    if (v0 == 0) {
        // 0x0048cf34
        charge(ctx, 5);
        s2 = 0x960000;
        s1 = 0x960000;
        s3 = 10;
        s2 = addiu(s2, -8600);  // &0x95DE68 (RpSpline: the last basis table)
        s1 = addiu(s1, 380);  // &0x96017C (RwFree slot)
        for (;;) {
            // 0x0048cf48
            charge(ctx, 8);
            lw(v0, s1, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x48CF4Cu);  // $ra = the return address
            lw(a0, s2, 0);
            call_ptr(ctx, jt);
            s3 = addiu(s3, -1);
            sw(zero, s2, 0);
            at = slti(s3, 4);
            s2 = addiu(s2, -4);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048cf68
        charge(ctx, 5);
        lw(v0, s1, 0);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x48CF6Cu);  // $ra = the return address
        lw(a0, gp, -17780);  // 0x7CE77C (RpSpline: the basis tables (12 x 257 floats from here))
        call_ptr(ctx, jt);
        sw(zero, gp, -17780);  // 0x7CE77C (RpSpline: the basis tables (12 x 257 floats from here))
        backedge(ctx);
    }
    // 0x0048cf2c
    charge(ctx, 2);
    v0 = s0;
    // 0x0048cf7c
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_48CFA0 [splineOpen] -- RpSpline's engine open: on the first open the basis tables (sub_48AD20) and the end matrices for 4..10 points (0x95DE50..)
// A failed matrix frees the ones made and raises error 3; the open count (gp 0x7CE7B4) up; $a0, or 0.
// 0x0048CFA0 sub_48CFA0 -- 316 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48CFA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048cfa0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17724);  // 0x7CE7B4 (RpSpline's open count)
    s1 = a0;
    if (v0 == 0) {
        // 0x0048cfd8
        charge(ctx, 4);
        jal(ctx, 0x48CFD8u, gen::fn_sub_48AD20_0048ad20);
        if (v0 == 0) {
            // 0x0048d05c
            charge(ctx, 9);
            v0 = 258;
            a0 = 3;
            link(ctx, 0x48D064u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x58);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x5C);
            a0 = addiu(sp, 0x58);
            jal(ctx, 0x48D070u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x0048cfe8
            charge(ctx, 3);
            s0 = 0x960000;
            s2 = 4;
            s0 = addiu(s0, -8624);  // &0x95DE50
            for (;;) {
                // 0x0048cff4
                charge(ctx, 4);
                a0 = s2;
                jal(ctx, 0x48CFF4u, gen::fn_sub_48AF80_0048af80);
                sw(v0, s0, 0);
                if (v0 == 0) {
                    goto L_0048d004_5;
                }
                // 0x0048d01c
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                at = slti(s2, 11);
                s0 = addiu(s0, 4);
                if (at == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048d02c
            charge(ctx, 1);
            v0 = 1;
        L_0048d030:
            charge(ctx, 2);
            if (v0 != 0) {
                backedge(ctx);
                goto L_0048cfc4;
            }
            // 0x0048d038
            charge(ctx, 9);
            v0 = 258;
            a0 = 3;
            link(ctx, 0x48D040u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x50);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x48D04Cu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        }
        // 0x0048d0c0 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_0048cfc4:
    charge(ctx, 5);
    lw(v1, gp, -17724);  // 0x7CE7B4 (RpSpline's open count)
    v0 = s1;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17724);  // 0x7CE7B4 (RpSpline's open count)
    // 0x0048d0c0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_0048d004_5:
    charge(ctx, 4);
    s0 = addiu(s2, -1);
    at = slti(s0, 4);
    if (at == 0) {
        // 0x0048d080
        charge(ctx, 6);
        v0 = 0x960000;
        s2 = 0x960000;
        v1 = sll(s0, 2);
        v0 = addiu(v0, -8640);  // &0x95DE40 (RpSpline: the solve's scratch)
        s3 = addu(v0, v1);
        s2 = addiu(s2, 380);  // &0x96017C (RwFree slot)
        for (;;) {
            // 0x0048d098
            charge(ctx, 8);
            lw(v0, s2, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x48D09Cu);  // $ra = the return address
            lw(a0, s3, 0);
            call_ptr(ctx, jt);
            s0 = addiu(s0, -1);
            sw(zero, s3, 0);
            at = slti(s0, 4);
            s3 = addiu(s3, -4);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048d0b8
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x0048d014
    charge(ctx, 2);
    v0 = 0;
    goto L_0048d030;
}


// sub_48D200 [splineGetNumSegments] -- the number of user control points of a spline: points - 3 (closed) / - 2 (open); error 1 and 0 for another type
// 0x0048D200 sub_48D200 -- 104 bytes; frame 0x20: ra sp+0x0
void sub_48D200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048d200
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lw(v1, a0, spline::kType);
    v0 = 2;
    sd(ra, sp, 0x0);
    if (v1 == v0) {
        // 0x0048d234
        charge(ctx, 3);
        lw(v0, a0, spline::kNumPoints);
        v0 = addiu(v0, -3);
    } else {
        // 0x0048d214
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0048d228
            charge(ctx, 3);
            lw(v0, a0, spline::kNumPoints);
            v0 = addiu(v0, -2);
        } else {
            // 0x0048d220
            charge(ctx, 2);
            a0 = v0;
            // 0x0048d240
            charge(ctx, 7);
            v0 = 258;
            link(ctx, 0x48D244u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x18);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x1C);
            a0 = addiu(sp, 0x18);
            jal(ctx, 0x48D250u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        }
    }
    // 0x0048d25c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_48D370 [RpSplineSetControlPoint] -- sets user control point $a1 of a spline to *$a2 and re-solves the spline (sub_48B910)
// An index below 0 or not below sub_48D200's count raises 'control point out of range' (0x80000003) and returns 0;
// else the spline, or 0 when the solve fails.
// 0x0048D370 sub_48D370 -- 272 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48D370(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0048d370
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    if (i64(s1) >= 0) {
        // 0x0048d394
        charge(ctx, 4);
        lw(v1, s2, spline::kType);
        v0 = 2;
        if (v1 == v0) {
            // 0x0048d3c4
            charge(ctx, 3);
            lw(v0, s2, spline::kNumPoints);
            v0 = addiu(v0, -3);
        } else {
            // 0x0048d3a4
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x0048d3b8
                charge(ctx, 3);
                lw(v0, s2, spline::kNumPoints);
                v0 = addiu(v0, -2);
            } else {
                // 0x0048d3b0
                charge(ctx, 2);
                v0 = 258;
                // 0x0048d3d4
                charge(ctx, 6);
                link(ctx, 0x48D3D4u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x40);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x44);
                a0 = addiu(sp, 0x40);
                jal(ctx, 0x48D3E0u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            }
        }
        // 0x0048d3ec
        charge(ctx, 3);
        at = slt(s1, v0);
        if (at == 0) {
            goto L_0048d43c;
        }
        // 0x0048d3f8
        charge(ctx, 17);
        lw(v0, s2, spline::kCtrlPoints);
        v1 = sll(s1, 1);
        lwc1(f2, s0, 0);
        v1 = addu(v1, s1);
        lwc1(f1, s0, 4);
        v1 = sll(v1, 2);
        lwc1(f0, s0, 8);
        v0 = addu(v0, v1);
        swc1(f2, v0, 0);
        swc1(f1, v0, 4);
        swc1(f0, v0, 8);
        lw(a1, s2, spline::kCtrlPoints);
        a0 = s2;
        jal(ctx, 0x48D428u, gen::fn_sub_48B910_0048b910);
        if (v0 == 0) s2 = 0;
        v0 = s2;
        // 0x0048d468 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0048d43c:
    charge(ctx, 11);
    v1 = 258;
    v0 = lui(0x8000);
    a1 = 0x780000;
    sw(v1, sp, 0x48);
    a0 = v0 | 0x3;
    a1 = addiu(a1, -9024);  // "control point out of range"
    jal(ctx, 0x48D450u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x4C);
    a0 = addiu(sp, 0x48);
    jal(ctx, 0x48D45Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x0048d468 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_48D480 [RpSplineFindPosition] -- RpSpline's position (and tangent) at a parameter: path 10 (smooth) or 11 (nice ends), the basis tables
// ($a0 = the spline, $a1 = the path, $f12 = the parameter, $a2 = the position or 0, $a3 = the tangent or 0) A
// negative parameter is mirrored, a closed spline's above 1 wrapped into [0, 1); path 11 eases the ends (2t^2 up to
// 0.5, else 1 - 2(1 - t)^2); the segment is (points - 3) x t (t = 1: the last one at its end), the table position
// 256 x the fraction, interpolated between neighbouring entries; the position the four B-spline points weighted by
// tables 0..3, the tangent by 4..7, normalised (RwV3dNormalize, sub_4C6970) -- (0, 1, 0) for a zero tangent.
// Another path raises error 1. Returns the position pointer.
// 0x0048D480 sub_48D480 -- 1236 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48D480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12};
    // 0x0048d480
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = addiu(a0, 56);
    sd(ra, sp, 0x20);
    mtc1(zero, f0);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    c_lt_s(f12, f0);
    s0 = a3;
    lw(a3, a0, 8);
    s1 = a2;
    if (cond(ctx)) {
        // 0x0048d4b4
        charge(ctx, 2);
        neg_s(f12, f12);
        lw(a0, a0, 12);
    } else {
        // 0x0048d4ac
        charge(ctx, 2);
        lw(a0, a0, 12);
    }
    // 0x0048d4bc
    charge(ctx, 3);
    v0 = 2;
    if (a0 == v0) {
        // 0x0048d4c8
        charge(ctx, 6);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        c_le_s(f12, f0);
        if (!cond(ctx)) {
            // 0x0048d4e0
            charge(ctx, 6);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f12);
            if (cond(ctx)) {
                // 0x0048d508
                charge(ctx, 6);
                sub_s(f0, f12, f0);
                v0 = lui(0x8000);
                cvt_w_s(f0, f0);
                mfc1(a2, f0);
                a2 = a2 | v0;
            } else {
                // 0x0048d4f8
                charge(ctx, 4);
                cvt_w_s(f0, f12);
                mfc1(a2, f0);
            }
            // 0x0048d520
            charge(ctx, 2);
            if (i64(a2) < 0) {
                // 0x0048d534
                charge(ctx, 7);
                a0 = srl(a2, 1);
                v0 = a2 & 0x1;
                a0 = a0 | v0;
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x0048d528
                charge(ctx, 3);
                mtc1(a2, f0);
                cvt_s_w(f0, f0);
            }
            // 0x0048d550
            charge(ctx, 1);
            sub_s(f12, f12, f0);
        }
    }
    // 0x0048d554
    charge(ctx, 3);
    v0 = 11;
    if (a1 == v0) {
        // 0x0048d574
        charge(ctx, 6);
        v0 = 0x3F000000;
        mtc1(v0, f0);
        c_le_s(f12, f0);
        if (!cond(ctx)) {
            // 0x0048d598
            charge(ctx, 12);
            a0 = lui(0xC000);
            v0 = 0x40800000;
            mtc1(a0, f0);
            mtc1(v0, f3);
            mul_s(f2, f0, f12);
            v0 = lui(0xBF80);
            mtc1(v0, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madda_s(f2, f12);
            madd_s(f12, f3, f12);
        } else {
            // 0x0048d58c
            charge(ctx, 3);
            add_s(f0, f12, f12);
            mul_s(f12, f12, f0);
        }
    L_0048d5c8:
        charge(ctx, 6);
        v0 = 0x3F800000;
        mtc1(v0, f2);
        c_eq_s(f2, f12);
        if (cond(ctx)) {
            // 0x0048d934
            charge(ctx, 3);
            a1 = addiu(a3, -4);
            v0 = 255;
            backedge(ctx);
        } else {
            // 0x0048d5e0
            charge(ctx, 17);
            a0 = addiu(a3, -3);
            v0 = 0x43800000;
            mtc1(a0, f1);
            mtc1(v0, f0);
            cvt_s_w(f1, f1);
            mul_s(f2, f1, f12);
            cvt_w_s(f1, f2);
            mfc1(a1, f1);
            cvt_s_w(f1, f1);
            sub_s(f1, f2, f1);
            mul_s(f1, f0, f1);
            cvt_w_s(f0, f1);
            mfc1(v0, f0);
            cvt_s_w(f0, f0);
            sub_s(f2, f1, f0);
        }
        // 0x0048d644
        charge(ctx, 92);
        lw(t2, gp, -17768);  // 0x7CE788
        a0 = sll(a1, 1);
        a0 = addu(a0, a1);
        v0 = sll(v0, 2);
        lw(t1, gp, -17772);  // 0x7CE784
        a0 = sll(a0, 2);
        t0 = addu(v1, a0);
        lw(a1, gp, -17776);  // 0x7CE780
        lw(a0, gp, -17780);  // 0x7CE77C (RpSpline: the basis tables (12 x 257 floats from here))
        mtc1(zero, f1);
        a3 = addiu(t0, 12);
        a2 = addiu(t0, 24);
        t2 = addu(t2, v0);
        v1 = addiu(t0, 36);
        lwc1(f7, t2, 0);
        t1 = addu(t1, v0);
        lwc1(f6, t2, 4);
        a1 = addu(a1, v0);
        lwc1(f5, t1, 0);
        a0 = addu(a0, v0);
        lwc1(f4, t1, 4);
        lwc1(f3, a1, 0);
        lwc1(f0, a1, 4);
        adda_s(f1, f7);
        sub_s(f6, f6, f7);
        madd_s(f7, f2, f6);
        sub_s(f4, f4, f5);
        adda_s(f1, f5);
        madd_s(f6, f2, f4);
        sub_s(f0, f0, f3);
        adda_s(f1, f3);
        lwc1(f3, t0, 0);
        madd_s(f5, f2, f0);
        lwc1(f4, a0, 0);
        lwc1(f0, a0, 4);
        mul_s(f3, f3, f7);
        swc1(f3, s1, 0);
        lwc1(f3, t0, 4);
        sub_s(f0, f0, f4);
        adda_s(f1, f4);
        mul_s(f3, f3, f7);
        swc1(f3, s1, 4);
        lwc1(f3, t0, 8);
        madd_s(f0, f2, f0);
        mul_s(f3, f3, f7);
        swc1(f3, s1, 8);
        lwc1(f3, s1, 0);
        lwc1(f4, t0, 12);
        adda_s(f1, f3);
        madd_s(f3, f4, f6);
        swc1(f3, s1, 0);
        lwc1(f3, s1, 4);
        lwc1(f4, t0, 16);
        adda_s(f1, f3);
        madd_s(f3, f4, f6);
        swc1(f3, s1, 4);
        lwc1(f3, s1, 8);
        lwc1(f4, t0, 20);
        adda_s(f1, f3);
        madd_s(f3, f4, f6);
        swc1(f3, s1, 8);
        lwc1(f3, s1, 0);
        lwc1(f4, t0, 24);
        adda_s(f1, f3);
        madd_s(f3, f4, f5);
        swc1(f3, s1, 0);
        lwc1(f3, s1, 4);
        lwc1(f4, t0, 28);
        adda_s(f1, f3);
        madd_s(f3, f4, f5);
        swc1(f3, s1, 4);
        lwc1(f3, s1, 8);
        lwc1(f4, t0, 32);
        adda_s(f1, f3);
        madd_s(f3, f4, f5);
        swc1(f3, s1, 8);
        lwc1(f3, s1, 0);
        lwc1(f4, t0, 36);
        adda_s(f1, f3);
        madd_s(f3, f4, f0);
        swc1(f3, s1, 0);
        lwc1(f3, s1, 4);
        lwc1(f4, t0, 40);
        adda_s(f1, f3);
        madd_s(f3, f4, f0);
        swc1(f3, s1, 4);
        lwc1(f3, s1, 8);
        lwc1(f4, t0, 44);
        adda_s(f1, f3);
        madd_s(f0, f4, f0);
        swc1(f0, s1, 8);
        if (s0 != 0) {
            // 0x0048d7b4
            charge(ctx, 90);
            lw(t4, gp, -17752);  // 0x7CE798
            lwc1(f0, t0, 0);
            lw(t3, gp, -17756);  // 0x7CE794
            a0 = s0;
            lw(t2, gp, -17760);  // 0x7CE790
            a1 = s0;
            lw(t1, gp, -17764);  // 0x7CE78C
            t4 = addu(t4, v0);
            lwc1(f8, t4, 0);
            t3 = addu(t3, v0);
            lwc1(f7, t4, 4);
            t2 = addu(t2, v0);
            lwc1(f6, t3, 0);
            v0 = addu(t1, v0);
            lwc1(f5, t3, 4);
            lwc1(f4, t2, 0);
            lwc1(f3, t2, 4);
            adda_s(f1, f8);
            sub_s(f7, f7, f8);
            madd_s(f7, f2, f7);
            sub_s(f5, f5, f6);
            adda_s(f1, f6);
            madd_s(f6, f2, f5);
            sub_s(f3, f3, f4);
            adda_s(f1, f4);
            madd_s(f5, f2, f3);
            mul_s(f3, f0, f7);
            lwc1(f4, v0, 0);
            lwc1(f0, v0, 4);
            adda_s(f1, f4);
            sub_s(f0, f0, f4);
            madd_s(f0, f2, f0);
            swc1(f3, s0, 0);
            lwc1(f2, t0, 4);
            mul_s(f2, f2, f7);
            swc1(f2, s0, 4);
            lwc1(f2, t0, 8);
            mul_s(f2, f2, f7);
            swc1(f2, s0, 8);
            lwc1(f2, s0, 0);
            lwc1(f3, a3, 0);
            adda_s(f1, f2);
            madd_s(f2, f3, f6);
            swc1(f2, s0, 0);
            lwc1(f2, s0, 4);
            lwc1(f3, a3, 4);
            adda_s(f1, f2);
            madd_s(f2, f3, f6);
            swc1(f2, s0, 4);
            lwc1(f2, s0, 8);
            lwc1(f3, a3, 8);
            adda_s(f1, f2);
            madd_s(f2, f3, f6);
            swc1(f2, s0, 8);
            lwc1(f2, s0, 0);
            lwc1(f3, a2, 0);
            adda_s(f1, f2);
            madd_s(f2, f3, f5);
            swc1(f2, s0, 0);
            lwc1(f2, s0, 4);
            lwc1(f3, a2, 4);
            adda_s(f1, f2);
            madd_s(f2, f3, f5);
            swc1(f2, s0, 4);
            lwc1(f2, s0, 8);
            lwc1(f3, a2, 8);
            adda_s(f1, f2);
            madd_s(f2, f3, f5);
            swc1(f2, s0, 8);
            lwc1(f2, s0, 0);
            lwc1(f3, v1, 0);
            adda_s(f1, f2);
            madd_s(f2, f3, f0);
            swc1(f2, s0, 0);
            lwc1(f2, s0, 4);
            lwc1(f3, v1, 4);
            adda_s(f1, f2);
            madd_s(f2, f3, f0);
            swc1(f2, s0, 4);
            lwc1(f2, s0, 8);
            lwc1(f3, v1, 8);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            link(ctx, 0x48D900u);  // $ra first: the delay slot below depends on it
            swc1(f0, s0, 8);
            call(ctx, gen::fn_sub_4C6970_004c6970);
            mtc1(zero, f1);
            c_eq_s(f1, f0);
            if (cond(ctx)) {
                // 0x0048d91c
                charge(ctx, 4);
                swc1(f1, s0, 0);
                v0 = 0x3F800000;
                sw(v0, s0, 4);
                swc1(f1, s0, 8);
            }
        }
        // 0x0048d92c
        charge(ctx, 2);
        v0 = s1;
    } else {
        // 0x0048d560
        charge(ctx, 3);
        v0 = 10;
        if (a1 == v0) {
            goto L_0048d5c8;
        }
        // 0x0048d56c
        charge(ctx, 2);
        v0 = 258;
        // 0x0048d624
        charge(ctx, 8);
        a0 = 1;
        link(ctx, 0x48D628u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x38);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x48D634u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x0048d940 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_48DCF0 [RpSplinePluginAttach] -- registers RpSpline (plugin 0x102): the engine open / close (sub_48CFA0 / sub_48CF00); 1 when registered
// 0x0048DCF0 sub_48DCF0 -- 56 bytes; frame 0x10: ra sp+0x0
void sub_48DCF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048dcf0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x490000;
    a3 = 0x490000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 258;
    a2 = addiu(a2, -12384);  // &sub_48CFA0
    a3 = addiu(a3, -12544);  // &sub_48CF00
    jal(ctx, 0x48DD0Cu, gen::fn_sub_4CA520_004ca520);
    ld(ra, sp, 0x0);
    v0 = slt(v0, 0);
    v0 = v0 ^ 0x1;
    sp = addiu(sp, 0x10);
}


// sub_48DD30 [userDataOpen] -- RpUserData's engine open: the open count up; $a0
// 0x0048DD30 sub_48DD30 -- 20 bytes; leaf frame (no stack)
void sub_48DD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0048dd30
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17660);  // 0x7CE7F4 (RpUserData's open count)
    v0 = a0;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17660);  // 0x7CE7F4 (RpUserData's open count)
}


// sub_48DD50 [userDataClose] -- RpUserData's engine close: the open count down; $a0
// 0x0048DD50 sub_48DD50 -- 20 bytes; leaf frame (no stack)
void sub_48DD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0048dd50
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17660);  // 0x7CE7F4 (RpUserData's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17660);  // 0x7CE7F4 (RpUserData's open count)
}


// sub_48DD70 [userDataArrayDestroy] -- frees a user data array: its name, for strings every string, and the element array (RwFree)
// 0x0048DD70 sub_48DD70 -- 212 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48DD70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048dd70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x0048dd98
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x48DDA0u, v0.u());
        sw(zero, s3, uda::kName);
    }
    // 0x0048ddac
    charge(ctx, 4);
    lw(a0, s3, uda::kFormat);
    v1 = 3;
    if (a0 == v1) {
        // 0x0048ddbc
        charge(ctx, 5);
        lw(v1, s3, uda::kCount);
        lw(s1, s3, uda::kData);
        at = slt(0, v1);
        s2 = 0;
        if (at != 0) {
            // 0x0048ddd0
            charge(ctx, 2);
            s0 = 0x960000;
            s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
            for (;;) {
                // 0x0048ddd8
                charge(ctx, 3);
                lw(a0, s1, 0);
                if (a0 != 0) {
                    // 0x0048dde4
                    charge(ctx, 3);
                    lw(v0, s0, 0);
                    jalr(ctx, 0x48DDE8u, v0.u());
                }
                // 0x0048ddf0
                charge(ctx, 5);
                lw(v1, s3, uda::kCount);
                s2 = addiu(s2, 1);
                v1 = slt(s2, v1);
                s1 = addiu(s1, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048de04
            charge(ctx, 1);
        }
    }
    // 0x0048de08
    charge(ctx, 3);
    lw(a0, s3, uda::kData);
    if (a0 != 0) {
        // 0x0048de14
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x48DE1Cu, v0.u());
        sw(zero, s3, uda::kData);
    }
    // 0x0048de28 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_48DE50 [userDataArrayCopy] -- copies a user data array into $a0: format, count, the name and (strings) each string duplicated, else the elements copied
// Duplicates go through RwMalloc + the engine's strlen / strcpy slots; a null source string stays null.
// 0x0048DE50 sub_48DE50 -- 464 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48DE50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048de50
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, uda::kFormat);
    sw(v1, a0, 4);
    lw(v1, a1, uda::kCount);
    sw(v1, a0, 8);
    lw(v1, a1, uda::kName);
    s2 = a1;
    if (v1 != 0) {
        // 0x0048de94
        charge(ctx, 4);
        sw(zero, s5, uda::kName);
        lw(a0, s2, 0);
        if (a0 != 0) {
            // 0x0048dea4
            charge(ctx, 15);
            v0 = 0x960000;
            lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
            jalr(ctx, 0x48DEACu, v0.u());
            a0 = addiu(v0, 1);
            v0 = 0x30000;
            a1 = v0 | 0x2;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            jalr(ctx, 0x48DEC8u, v0.u());
            sw(v0, s5, uda::kName);
            lw(a0, s5, uda::kName);
            if (a0 != 0) {
                // 0x0048dee0
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x48DEE8u);  // $ra = the return address
                lw(a1, s2, 0);
                call_ptr(ctx, jt);
            }
        }
    }
    // 0x0048def0
    charge(ctx, 3);
    lw(v1, s2, 12);
    if (v1 != 0) {
        // 0x0048defc
        charge(ctx, 16);
        link(ctx, 0x48DEFCu);  // $ra first: the delay slot below depends on it
        lw(a0, s5, uda::kFormat);
        call(ctx, gen::fn_sub_48EFE0_0048efe0);
        lw(v1, s5, uda::kCount);
        mult(s0, v1, v0);
        s1 = 0x960000;
        s1 = addiu(s1, 376);  // &0x960178 (RwMalloc slot)
        lw(v0, s1, 0);  // 0x960178 (RwMalloc slot)
        v1 = 0x30000;
        a1 = v1 | 0x11F;
        a0 = s0;
        jalr(ctx, 0x48DF20u, v0.u());
        sw(v0, s5, uda::kData);
        v1 = 3;
        lw(a0, s5, uda::kFormat);
        if (a0 != v1) {
            // 0x0048dfe8
            charge(ctx, 4);
            lw(a0, s5, uda::kData);
            lw(a1, s2, 12);
            a2 = s0;
            jal(ctx, 0x48DFF0u, gen::fn_memcpy_00521250);
            goto L_0048dff8;
        }
        // 0x0048df3c
        charge(ctx, 6);
        lw(s3, s2, 12);
        lw(v1, s5, uda::kCount);
        lw(s2, s5, uda::kData);
        at = slt(0, v1);
        s4 = 0;
        if (at == 0) {
            goto L_0048dff8;
        }
        // 0x0048df54
        charge(ctx, 4);
        s0 = 0x960000;
        s6 = 0x960000;
        s0 = addiu(s0, 356);  // &0x960164 (the engine's strlen slot)
        s6 = addiu(s6, 316);  // &0x96013C (the engine's strcpy slot)
        for (;;) {
            // 0x0048df64
            charge(ctx, 3);
            lw(v1, s3, 0);
            if (v1 == 0) {
                // 0x0048dfe0
                charge(ctx, 2);
                sw(zero, s2, 0);
                backedge(ctx);
            } else {
                // 0x0048df70
                charge(ctx, 4);
                sw(zero, s2, 0);
                lw(a0, s3, 0);
                if (a0 != 0) {
                    // 0x0048df80
                    charge(ctx, 13);
                    lw(v0, s0, 0);
                    jalr(ctx, 0x48DF84u, v0.u());
                    a0 = addiu(v0, 1);
                    v0 = 0x30000;
                    a1 = v0 | 0x2;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x48DF9Cu, v0.u());
                    sw(v0, s2, 0);
                    lw(a0, s2, 0);
                    if (a0 != 0) {
                        // 0x0048dfb4
                        charge(ctx, 3);
                        lw(v0, s6, 0);
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x48DFB8u);  // $ra = the return address
                        lw(a1, s3, 0);
                        call_ptr(ctx, jt);
                    }
                }
            }
            // 0x0048dfc0
            charge(ctx, 6);
            lw(v1, s5, uda::kCount);
            s4 = addiu(s4, 1);
            s3 = addiu(s3, 4);
            v1 = slt(s4, v1);
            s2 = addiu(s2, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048dfd8
        charge(ctx, 2);
        ld(ra, sp, 0x70);
        // 0x0048dffc (the shared epilogue, written out on this path)
        charge(ctx, 9);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
L_0048dff8:
    charge(ctx, 1);
    ld(ra, sp, 0x70);
    // 0x0048dffc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}


// sub_48E020 [userDataArrayStreamRead] -- reads a user data array: the name (length, chars), the format, the count, then the elements by format
// ($a0 = the array, $a1 = the stream) Strings (3): per element its length and characters (RwMalloc'd, 0 for a
// null one); reals (2): RwStreamReadReal; ints (1): RwStreamReadInt32; another format fails. The stream, or 0.
// A 0 name length leaves the name word as it was (not cleared); an int / real array with no elements fails (the
// 0-byte read returns 0) -- and the list reader sub_48EC20 goes on with that 0 as its stream.
// 0x0048E020 sub_48E020 -- 688 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48E020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048e020
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 4;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    s3 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    a0 = s3;
    a1 = addiu(sp, 0x6C);
    link(ctx, 0x48E04Cu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x0048e0a8
        charge(ctx, 2);
        v0 = 0;
    L_0048e2b0:
        charge(ctx, 1);
        ld(ra, sp, 0x50);
    } else {
        // 0x0048e05c
        charge(ctx, 3);
        lw(a0, sp, 0x6C);
        if (i64(a0) > 0) {
            // 0x0048e068
            charge(ctx, 9);
            v0 = 0x960000;
            v1 = 0x30000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a1 = v1 | 0x11F;
            jalr(ctx, 0x48E074u, v0.u());
            sw(v0, s4, uda::kName);
            lw(a1, s4, uda::kName);
            if (a1 == 0) {
                // 0x0048e0b0
                charge(ctx, 2);
                v0 = 0;
                goto L_0048e2b0;
            }
            // 0x0048e08c
            charge(ctx, 5);
            lw(a2, sp, 0x6C);
            a0 = s3;
            jal(ctx, 0x48E090u, gen::fn_sub_4C5250_004c5250);
            if (v0 != 0) {
                goto L_0048e0b8;
            }
            // 0x0048e0a0
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e2b0;
        }
    L_0048e0b8:
        charge(ctx, 6);
        a0 = s3;
        a1 = addiu(s4, 4);
        a2 = 4;
        jal(ctx, 0x48E0C0u, gen::fn_sub_4C1910_004c1910);
        if (v0 == 0) {
            // 0x0048e0d0
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e2b0;
        }
        // 0x0048e0d8
        charge(ctx, 6);
        a0 = s3;
        a1 = addiu(s4, 8);
        a2 = 4;
        jal(ctx, 0x48E0E0u, gen::fn_sub_4C1910_004c1910);
        if (v0 == 0) {
            // 0x0048e250
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e2b0;
        }
        // 0x0048e0f0
        charge(ctx, 4);
        lw(v1, s4, uda::kFormat);
        v0 = 3;
        if (v1 == v0) {
            // 0x0048e1b8
            charge(ctx, 12);
            s0 = 0x960000;
            lw(a0, s4, uda::kCount);
            s0 = addiu(s0, 376);  // &0x960178 (RwMalloc slot)
            v1 = 0x30000;
            lw(v0, s0, 0);  // 0x960178 (RwMalloc slot)
            a1 = v1 | 0x11F;
            a0 = sll(a0, 2);
            jalr(ctx, 0x48E1D0u, v0.u());
            sw(v0, s4, uda::kData);
            lw(s1, s4, uda::kData);
            if (s1 == 0) {
                // 0x0048e268
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048e1e8
                charge(ctx, 4);
                lw(v0, s4, uda::kCount);
                at = slt(0, v0);
                s2 = 0;
                if (at == 0) {
                L_0048e240:
                    charge(ctx, 2);
                    v0 = s3;
                } else {
                    for (;;) {
                        // 0x0048e1f8
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = addiu(sp, 0x6C);
                        a2 = 4;
                        jal(ctx, 0x48E200u, gen::fn_sub_4C1910_004c1910);
                        if (v0 == 0) {
                            goto L_0048e210_23;
                        }
                        // 0x0048e218
                        charge(ctx, 3);
                        lw(a0, sp, 0x6C);
                        if (i64(a0) <= 0) {
                            // 0x0048e224
                            charge(ctx, 1);
                            sw(zero, s1, 0);
                            goto L_0048e228;
                        }
                        // 0x0048e270
                        charge(ctx, 8);
                        lw(v0, s0, 0);
                        v1 = 0x30000;
                        a1 = v1 | 0x11F;
                        jalr(ctx, 0x48E278u, v0.u());
                        sw(v0, s1, 0);
                        lw(a1, s1, 0);
                        if (a1 == 0) {
                            goto L_0048e2ac;
                        }
                        // 0x0048e290
                        charge(ctx, 5);
                        lw(a2, sp, 0x6C);
                        a0 = s3;
                        jal(ctx, 0x48E294u, gen::fn_sub_4C5250_004c5250);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    L_0048e228:
                        charge(ctx, 5);
                        lw(v0, s4, uda::kCount);
                        s2 = addiu(s2, 1);
                        v0 = slt(s2, v0);
                        s1 = addiu(s1, 4);
                        if (v0 == 0) {
                            goto L_0048e23c_27;
                        }
                        backedge(ctx);
                    }
                    // 0x0048e2a4
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
            goto L_0048e2b0;
        }
        // 0x0048e100
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x0048e16c
            charge(ctx, 11);
            v0 = 0x30000;
            lw(v1, s4, uda::kCount);
            a1 = v0 | 0x11F;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = sll(v1, 2);
            jalr(ctx, 0x48E180u, v0.u());
            sw(v0, s4, uda::kData);
            lw(a1, s4, uda::kData);
            if (a1 == 0) {
                // 0x0048e260
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048e198
                charge(ctx, 6);
                lw(v0, s4, uda::kCount);
                a0 = s3;
                a2 = sll(v0, 2);
                jal(ctx, 0x48E1A0u, gen::fn_sub_4C18B0_004c18b0);
                if (v0 != 0) {
                    goto L_0048e240;
                }
                // 0x0048e1b0
                charge(ctx, 2);
                v0 = 0;
            }
            goto L_0048e2b0;
        }
        // 0x0048e10c
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0048e120
            charge(ctx, 11);
            v0 = 0x30000;
            lw(v1, s4, uda::kCount);
            a1 = v0 | 0x11F;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = sll(v1, 2);
            jalr(ctx, 0x48E134u, v0.u());
            sw(v0, s4, uda::kData);
            lw(a1, s4, uda::kData);
            if (a1 == 0) {
                // 0x0048e258
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048e14c
                charge(ctx, 6);
                lw(v0, s4, uda::kCount);
                a0 = s3;
                a2 = sll(v0, 2);
                jal(ctx, 0x48E154u, gen::fn_sub_4C1910_004c1910);
                if (v0 != 0) {
                    goto L_0048e240;
                }
                // 0x0048e164
                charge(ctx, 2);
                v0 = 0;
            }
            goto L_0048e2b0;
        }
        // 0x0048e118
        charge(ctx, 2);
        v0 = 0;
        // 0x0048e248
        charge(ctx, 2);
        ld(ra, sp, 0x50);
    }
    // 0x0048e2b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_0048e210_23:
    charge(ctx, 2);
    v0 = 0;
    goto L_0048e2b0;
L_0048e23c_27:
    charge(ctx, 1);
    goto L_0048e240;
L_0048e2ac:
    charge(ctx, 1);
    v0 = 0;
    goto L_0048e2b0;
}


// sub_48E2D0 [userDataArrayStreamWrite] -- writes a user data array: the name (strlen + 1, then the chars), the format, the count, the elements by format
// 0x0048E2D0 sub_48E2D0 -- 536 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48E2D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048e2d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s3 = a1;
    if (a0 == 0) {
        // 0x0048e314
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0048e2fc
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
        jalr(ctx, 0x48E304u, v0.u());
        v0 = addiu(v0, 1);
    }
    // 0x0048e318
    charge(ctx, 7);
    sw(v0, sp, 0x6C);
    a0 = s3;
    a1 = addiu(sp, 0x6C);
    a2 = 4;
    jal(ctx, 0x48E324u, gen::fn_sub_4C17F0_004c17f0);
    if (v0 == 0) {
        // 0x0048e35c
        charge(ctx, 2);
        v0 = 0;
    L_0048e4c8:
        charge(ctx, 1);
        ld(ra, sp, 0x50);
    } else {
        // 0x0048e334
        charge(ctx, 3);
        lw(a2, sp, 0x6C);
        if (i64(a2) > 0) {
            // 0x0048e340
            charge(ctx, 5);
            lw(a1, s4, uda::kName);
            a0 = s3;
            jal(ctx, 0x48E344u, gen::fn_sub_4C53F0_004c53f0);
            if (v0 != 0) {
                goto L_0048e364;
            }
            // 0x0048e354
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e4c8;
        }
    L_0048e364:
        charge(ctx, 6);
        a0 = s3;
        a1 = addiu(s4, 4);
        a2 = 4;
        jal(ctx, 0x48E36Cu, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) {
            // 0x0048e37c
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e4c8;
        }
        // 0x0048e384
        charge(ctx, 6);
        a0 = s3;
        a1 = addiu(s4, 8);
        a2 = 4;
        jal(ctx, 0x48E38Cu, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) {
            // 0x0048e4a0
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e4c8;
        }
        // 0x0048e39c
        charge(ctx, 4);
        lw(v1, s4, uda::kFormat);
        v0 = 3;
        if (v1 == v0) {
            // 0x0048e414
            charge(ctx, 5);
            lw(v0, s4, uda::kCount);
            lw(s1, s4, uda::kData);
            at = slt(0, v0);
            s2 = 0;
            if (at == 0) {
            L_0048e490:
                charge(ctx, 2);
                v0 = s3;
            } else {
                // 0x0048e428
                charge(ctx, 2);
                s0 = 0x960000;
                s0 = addiu(s0, 356);  // &0x960164 (the engine's strlen slot)
                for (;;) {
                    // 0x0048e430
                    charge(ctx, 3);
                    lw(a0, s1, 0);
                    if (a0 == 0) {
                        // 0x0048e450
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0048e43c
                        charge(ctx, 5);
                        lw(v0, s0, 0);
                        jalr(ctx, 0x48E440u, v0.u());
                        v0 = addiu(v0, 1);
                    }
                    // 0x0048e454
                    charge(ctx, 7);
                    sw(v0, sp, 0x6C);
                    a0 = s3;
                    a1 = addiu(sp, 0x6C);
                    a2 = 4;
                    jal(ctx, 0x48E460u, gen::fn_sub_4C17F0_004c17f0);
                    if (v0 == 0) {
                        goto L_0048e4a8;
                    }
                    // 0x0048e470
                    charge(ctx, 3);
                    lw(a2, sp, 0x6C);
                    if (i64(a2) > 0) {
                        // 0x0048e4b0
                        charge(ctx, 5);
                        lw(a1, s1, 0);
                        a0 = s3;
                        jal(ctx, 0x48E4B4u, gen::fn_sub_4C53F0_004c53f0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        goto L_0048e47c;
                    }
                L_0048e47c:
                    charge(ctx, 5);
                    lw(v0, s4, uda::kCount);
                    s2 = addiu(s2, 1);
                    v0 = slt(s2, v0);
                    s1 = addiu(s1, 4);
                    if (v0 == 0) {
                        goto L_0048e490;
                    }
                    backedge(ctx);
                }
                // 0x0048e4c4
                charge(ctx, 1);
                v0 = 0;
            }
            goto L_0048e4c8;
        }
        // 0x0048e3ac
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x0048e3f0
            charge(ctx, 7);
            lw(v0, s4, uda::kCount);
            a0 = s3;
            lw(a1, s4, uda::kData);
            a2 = sll(v0, 2);
            jal(ctx, 0x48E3FCu, gen::fn_sub_4C1750_004c1750);
            if (v0 != 0) {
                goto L_0048e490;
            }
            // 0x0048e40c
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e4c8;
        }
        // 0x0048e3b8
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0048e3cc
            charge(ctx, 7);
            lw(v0, s4, uda::kCount);
            a0 = s3;
            lw(a1, s4, uda::kData);
            a2 = sll(v0, 2);
            jal(ctx, 0x48E3D8u, gen::fn_sub_4C17F0_004c17f0);
            if (v0 != 0) {
                goto L_0048e490;
            }
            // 0x0048e3e8
            charge(ctx, 2);
            v0 = 0;
            goto L_0048e4c8;
        }
        // 0x0048e3c4
        charge(ctx, 2);
        v0 = 0;
        // 0x0048e498
        charge(ctx, 2);
        ld(ra, sp, 0x50);
    }
    // 0x0048e4cc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_0048e4a8:
    charge(ctx, 2);
    v0 = 0;
    goto L_0048e4c8;
}


// sub_48E4F0 [userDataArrayStreamSize] -- the stream size of a user data array: 4 + the name (strlen + 1) + 8 + the elements (strings: 4 + length + 1 each)
// 0 for no array.
// 0x0048E4F0 sub_48E4F0 -- 280 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48E4F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048e4f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = 0;
    sq(s0, sp, 0x0);
    if (s4 != 0) {
        // 0x0048e518
        charge(ctx, 3);
        lw(a0, s4, uda::kName);
        s2 = addiu(s2, 4);
        if (a0 != 0) {
            // 0x0048e524
            charge(ctx, 7);
            v0 = 0x960000;
            lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
            jalr(ctx, 0x48E52Cu, v0.u());
            v0 = addiu(v0, 1);
            s2 = addu(s2, v0);
        }
        // 0x0048e5bc
        charge(ctx, 4);
        lw(v1, s4, uda::kFormat);
        v0 = 3;
        s2 = addiu(s2, 8);
        if (v1 != v0) {
            // 0x0048e5cc
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                backedge(ctx);
                // 0x0048e550
                charge(ctx, 4);
                lw(v0, s4, uda::kCount);
                v0 = sll(v0, 2);
                s2 = addu(s2, v0);
            } else {
                // 0x0048e5d8
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    backedge(ctx);
                    // 0x0048e540
                    charge(ctx, 4);
                    lw(v0, s4, uda::kCount);
                    v0 = sll(v0, 2);
                    s2 = addu(s2, v0);
                }
            }
            goto L_0048e5e4;
        }
        backedge(ctx);
        // 0x0048e560
        charge(ctx, 5);
        lw(v0, s4, uda::kCount);
        lw(s1, s4, uda::kData);
        at = slt(0, v0);
        s3 = 0;
        if (at == 0) {
            goto L_0048e5e4;
        }
        // 0x0048e574
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 356);  // &0x960164 (the engine's strlen slot)
        for (;;) {
            // 0x0048e57c
            charge(ctx, 3);
            lw(a0, s1, 0);
            s2 = addiu(s2, 4);
            if (a0 != 0) {
                // 0x0048e588
                charge(ctx, 6);
                lw(v0, s0, 0);
                jalr(ctx, 0x48E58Cu, v0.u());
                v0 = addiu(v0, 1);
                s2 = addu(s2, v0);
            }
            // 0x0048e5a0
            charge(ctx, 5);
            lw(v0, s4, uda::kCount);
            s3 = addiu(s3, 1);
            v0 = slt(s3, v0);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048e5b4
        charge(ctx, 2);
        v0 = s2;
        // 0x0048e5e8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_0048e5e4:
    charge(ctx, 1);
    v0 = s2;
    // 0x0048e5e8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_48E610 [userDataListDestroy] -- frees every array of a user data list (as sub_48DD70) and the array of arrays; count and pointer cleared
// 0x0048E610 sub_48E610 -- 320 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48E610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048e610
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    s5 = a0;
    if (v1 != 0) {
        // 0x0048e640
        charge(ctx, 4);
        lw(v0, s5, udlist::kCount);
        at = slt(0, v0);
        s4 = 0;
        if (at != 0) {
            // 0x0048e650
            charge(ctx, 3);
            s0 = 0x960000;
            s6 = 0;
            s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
            for (;;) {
                // 0x0048e65c
                charge(ctx, 5);
                lw(v0, s5, udlist::kArrays);
                s3 = addu(v0, s6);
                lw(a0, s3, uda::kName);
                if (a0 != 0) {
                    // 0x0048e670
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    jalr(ctx, 0x48E674u, v0.u());
                    sw(zero, s3, uda::kName);
                }
                // 0x0048e680
                charge(ctx, 4);
                lw(v1, s3, uda::kFormat);
                v0 = 3;
                if (v1 == v0) {
                    // 0x0048e690
                    charge(ctx, 5);
                    lw(v0, s3, uda::kCount);
                    lw(s1, s3, uda::kData);
                    at = slt(0, v0);
                    s2 = 0;
                    if (at != 0) {
                        // 0x0048e6a4
                        charge(ctx, 1);
                        for (;;) {
                            // 0x0048e6a8
                            charge(ctx, 3);
                            lw(a0, s1, 0);
                            if (a0 != 0) {
                                // 0x0048e6b4
                                charge(ctx, 3);
                                lw(v0, s0, 0);
                                jalr(ctx, 0x48E6B8u, v0.u());
                            }
                            // 0x0048e6c0
                            charge(ctx, 5);
                            lw(v0, s3, uda::kCount);
                            s2 = addiu(s2, 1);
                            v0 = slt(s2, v0);
                            s1 = addiu(s1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0048e6d4
                        charge(ctx, 1);
                    }
                }
                // 0x0048e6d8
                charge(ctx, 3);
                lw(a0, s3, uda::kData);
                if (a0 != 0) {
                    // 0x0048e6e4
                    charge(ctx, 5);
                    lw(v0, s0, 0);
                    jalr(ctx, 0x48E6E8u, v0.u());
                    sw(zero, s3, uda::kData);
                }
                // 0x0048e6f8
                charge(ctx, 5);
                lw(v0, s5, udlist::kCount);
                s4 = addiu(s4, 1);
                v0 = slt(s4, v0);
                s6 = addiu(s6, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048e70c
            charge(ctx, 1);
        }
        // 0x0048e710
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x48E718u);  // $ra = the return address
        lw(a0, s5, udlist::kArrays);
        call_ptr(ctx, jt);
    }
    // 0x0048e720 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    sw(zero, s5, udlist::kArrays);
    sw(zero, s5, udlist::kCount);
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


// sub_48E750 [userDataListStreamWrite] -- writes a user data list: the count of arrays with a format, then each such array (sub_48E2D0)
// 0 for no list or an empty one; else the stream.
// 0x0048E750 sub_48E750 -- 312 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48E750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048e750
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    if (s3 != 0) {
        // 0x0048e774
        charge(ctx, 3);
        lw(a1, s3, udlist::kCount);
        if (i64(a1) <= 0) {
            goto L_0048e868;
        }
        // 0x0048e780
        charge(ctx, 5);
        at = slt(0, a1);
        sw(zero, sp, 0x5C);
        v0 = 0;
        a3 = 0;
        if (at != 0) {
            // 0x0048e794
            charge(ctx, 2);
            lw(a0, s3, udlist::kArrays);
            a2 = 0;
            for (;;) {
                // 0x0048e79c
                charge(ctx, 4);
                v1 = addu(a0, a2);
                lw(v1, v1, 4);
                if (v1 != 0) {
                    // 0x0048e7d8
                    charge(ctx, 5);
                    v0 = dsll32(v0, 0);
                    v0 = dsra32(v0, 0);
                    v0 = addiu(v0, 1);
                    sw(v0, sp, 0x5C);
                    backedge(ctx);
                } else {
                    // 0x0048e7ac
                    charge(ctx, 1);
                }
                // 0x0048e7b0
                charge(ctx, 4);
                a3 = addiu(a3, 1);
                v1 = slt(a3, a1);
                a2 = addiu(a2, 16);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0048e7c0
        charge(ctx, 4);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        if (v0 != 0) {
            // 0x0048e7f0
            charge(ctx, 6);
            a0 = s2;
            a1 = addiu(sp, 0x5C);
            a2 = 4;
            jal(ctx, 0x48E7F8u, gen::fn_sub_4C17F0_004c17f0);
            if (v0 != 0) {
                // 0x0048e808
                charge(ctx, 4);
                lw(v0, s3, udlist::kCount);
                at = slt(0, v0);
                s0 = 0;
                if (at == 0) {
                    backedge(ctx);
                } else {
                    // 0x0048e818
                    charge(ctx, 1);
                    s1 = 0;
                    for (;;) {
                        // 0x0048e81c
                        charge(ctx, 5);
                        lw(v0, s3, udlist::kArrays);
                        a0 = addu(v0, s1);
                        lw(v0, a0, 4);
                        if (v0 != 0) {
                            // 0x0048e854
                            charge(ctx, 4);
                            a1 = s2;
                            jal(ctx, 0x48E854u, gen::fn_sub_48E2D0_0048e2d0);
                            s2 = v0;
                            backedge(ctx);
                        }
                        // 0x0048e830
                        charge(ctx, 5);
                        lw(v0, s3, udlist::kCount);
                        s0 = addiu(s0, 1);
                        v0 = slt(s0, v0);
                        s1 = addiu(s1, 16);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0048e844
                    charge(ctx, 2);
                    backedge(ctx);
                }
                goto L_0048e7d0;
            }
            // 0x0048e84c
            charge(ctx, 2);
            v0 = 0;
            // 0x0048e86c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_0048e7d0:
        charge(ctx, 2);
        v0 = s2;
        // 0x0048e86c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_0048e868:
    charge(ctx, 1);
    v0 = 0;
    // 0x0048e86c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_48E890 [userDataListAddArray] -- adds an array to a user data list: the first array without data, else the list grown by one (RwMalloc, copy, RwFree)
// ($a0 = the list, $a1 = the name or 0, $a2 = the format, $a3 = the count) The elements RwMalloc'd and zeroed
// (format size x count), the name duplicated. Returns the array's index, or -1 when an allocation fails.
// 0x0048E890 sub_48E890 -- 512 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48E890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048e890
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = si(-1);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(v1, a0, 0);
    s0 = a3;
    at = slt(0, v1);
    a1 = 0;
    if (at != 0) {
        // 0x0048e8d4
        charge(ctx, 1);
        lw(a0, s4, uda::kFormat);
        for (;;) {
            // 0x0048e8d8
            charge(ctx, 3);
            lw(v0, a0, 12);
            if (v0 == 0) {
                goto L_0048e8e4_3;
            }
            // 0x0048e8ec
            charge(ctx, 4);
            a1 = addiu(a1, 1);
            v0 = slt(a1, v1);
            a0 = addiu(a0, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048e8fc
        charge(ctx, 1);
    }
L_0048e900:
    charge(ctx, 3);
    v0 = si(-1);
    if (s5 == v0) {
        // 0x0048e90c
        charge(ctx, 3);
        lw(v0, s4, uda::kFormat);
        if (v0 == 0) {
            // 0x0048ea34
            charge(ctx, 11);
            v0 = 0x30000;
            v1 = addiu(v1, 1);
            a1 = v0 | 0x11F;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = sll(v1, 4);
            jalr(ctx, 0x48EA48u, v0.u());
            sw(v0, s4, uda::kFormat);
            lw(v0, s4, uda::kFormat);
            if (v0 != 0) {
                backedge(ctx);
            L_0048e968:
                charge(ctx, 3);
                lw(s5, s4, uda::kName);
                v0 = addiu(s5, 1);
                sw(v0, s4, uda::kName);
                goto L_0048e974;
            }
            // 0x0048ea60
            charge(ctx, 2);
            v0 = si(-1);
        } else {
            // 0x0048e918
            charge(ctx, 10);
            v0 = 0x30000;
            v1 = addiu(v1, 1);
            a1 = v0 | 0x11F;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = sll(v1, 4);
            jalr(ctx, 0x48E92Cu, v0.u());
            s3 = v0;
            if (s3 != 0) {
                // 0x0048e940
                charge(ctx, 10);
                lw(v0, s4, uda::kName);
                a0 = s3;
                lw(a1, s4, uda::kFormat);
                a2 = sll(v0, 4);
                jal(ctx, 0x48E94Cu, gen::fn_memcpy_00521250);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x48E95Cu);  // $ra = the return address
                lw(a0, s4, uda::kFormat);
                call_ptr(ctx, jt);
                sw(s3, s4, uda::kFormat);
                goto L_0048e968;
            }
            // 0x0048ea2c
            charge(ctx, 2);
            v0 = si(-1);
        }
        // 0x0048ea6c (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_0048e974:
    charge(ctx, 17);
    lw(v0, s4, uda::kFormat);
    v1 = sll(s5, 4);
    s3 = 0x960000;
    a0 = s1;
    s3 = addiu(s3, 376);  // &0x960178 (RwMalloc slot)
    s4 = addu(v0, v1);
    jal(ctx, 0x48E988u, gen::fn_sub_48EFE0_0048efe0);
    mult(a0, s0, v0);
    v0 = 0x30000;
    a1 = v0 | 0x11F;
    lw(v0, s3, 0);  // 0x960178 (RwMalloc slot)
    jalr(ctx, 0x48E9A0u, v0.u());
    sw(v0, s4, uda::kData);
    lw(v0, s4, uda::kData);
    if (v0 == 0) {
        // 0x0048ea68
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x0048e9b8
        charge(ctx, 8);
        a0 = s1;
        jal(ctx, 0x48E9B8u, gen::fn_sub_48EFE0_0048efe0);
        mult(a2, s0, v0);
        lw(a0, s4, uda::kData);
        a1 = 0;
        jal(ctx, 0x48E9C8u, gen::fn_memset_00521408);
        sw(zero, s4, uda::kName);
        if (s2 != 0) {
            // 0x0048e9d8
            charge(ctx, 13);
            v0 = 0x960000;
            lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
            a0 = s2;
            jalr(ctx, 0x48E9E0u, v0.u());
            lw(v1, s3, 0);
            a0 = addiu(v0, 1);
            v0 = 0x30000;
            a1 = v0 | 0x2;
            jalr(ctx, 0x48E9F4u, v1.u());
            sw(v0, s4, uda::kName);
            lw(a0, s4, uda::kName);
            if (a0 != 0) {
                // 0x0048ea0c
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
                a1 = s2;
                jalr(ctx, 0x48EA14u, v0.u());
            }
        }
        // 0x0048ea1c
        charge(ctx, 4);
        sw(s1, s4, uda::kFormat);
        v0 = s5;
        sw(s0, s4, uda::kCount);
    }
    // 0x0048ea6c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_0048e8e4_3:
    charge(ctx, 2);
    s5 = a1;
    goto L_0048e900;
}


// sub_48EA90 [userDataConstructor] -- the user data extension constructor ($a1 = the extension offset): count and arrays cleared; the object
// 0x0048EA90 sub_48EA90 -- 20 bytes; leaf frame (no stack)
void sub_48EA90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0048ea90
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = addu(a0, a1);
    v0 = a0;
    sw(zero, v1, 0);
    sw(zero, v1, 4);
}


// sub_48EAB0 [userDataDestructor] -- the user data extension destructor: each array destroyed (sub_48DD70), the array of arrays freed; the object
// 0x0048EAB0 sub_48EAB0 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48EAB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0048eab0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addu(s3, a1);
    lw(v0, s0, udlist::kArrays);
    if (v0 != 0) {
        // 0x0048eadc
        charge(ctx, 4);
        lw(v0, s0, udlist::kCount);
        at = slt(0, v0);
        s2 = 0;
        if (at != 0) {
            // 0x0048eaec
            charge(ctx, 1);
            s1 = 0;
            for (;;) {
                // 0x0048eaf0
                charge(ctx, 8);
                lw(v0, s0, udlist::kArrays);
                a0 = addu(v0, s1);
                jal(ctx, 0x48EAF4u, gen::fn_sub_48DD70_0048dd70);
                lw(v0, s0, udlist::kCount);
                s2 = addiu(s2, 1);
                v0 = slt(s2, v0);
                s1 = addiu(s1, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0048eb10
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x48EB18u);  // $ra = the return address
        lw(a0, s0, udlist::kArrays);
        call_ptr(ctx, jt);
    }
    // 0x0048eb20 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    sw(zero, s0, udlist::kArrays);
    v0 = s3;
    sw(zero, s0, udlist::kCount);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_48EB50 [userDataCopy] -- the user data extension copy: the destination's list destroyed (sub_48E610), then every array copied (sub_48DE50); the destination
// 0x0048EB50 sub_48EB50 -- 208 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48EB50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048eb50
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addu(s4, a2);
    s0 = addu(a1, a2);
    a0 = s1;
    jal(ctx, 0x48EB78u, gen::fn_sub_48E610_0048e610);
    lw(v0, s0, udlist::kCount);
    sw(v0, s1, udlist::kCount);
    lw(v0, s1, udlist::kCount);
    if (i64(v0) > 0) {
        // 0x0048eb9c
        charge(ctx, 12);
        a0 = sll(v0, 4);
        v0 = 0x30000;
        a1 = v0 | 0x11F;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        jalr(ctx, 0x48EBB0u, v0.u());
        sw(v0, s1, udlist::kArrays);
        lw(v0, s1, udlist::kCount);
        at = slt(0, v0);
        s3 = 0;
        if (at == 0) {
            backedge(ctx);
        } else {
            // 0x0048ebcc
            charge(ctx, 1);
            s2 = 0;
            for (;;) {
                // 0x0048ebd0
                charge(ctx, 10);
                lw(v1, s1, udlist::kArrays);
                lw(v0, s0, udlist::kArrays);
                a0 = addu(v1, s2);
                a1 = addu(v0, s2);
                jal(ctx, 0x48EBDCu, gen::fn_sub_48DE50_0048de50);
                lw(v0, s1, udlist::kCount);
                s3 = addiu(s3, 1);
                v0 = slt(s3, v0);
                s2 = addiu(s2, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048ebf8
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x0048eb94
    charge(ctx, 2);
    v0 = s4;
    // 0x0048ec00
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_48EC20 [userDataStreamRead] -- the user data extension stream read: the array count, the arrays (RwMalloc of 16 x count), each read by sub_48E020
// Returns the stream it was given.
// 0x0048EC20 sub_48EC20 -- 204 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48EC20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048ec20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addu(a2, a3);
    s3 = s4;
    if (s0 != 0) {
        // 0x0048ec4c
        charge(ctx, 5);
        a1 = addiu(sp, 0x6C);
        a2 = 4;
        jal(ctx, 0x48EC50u, gen::fn_sub_4C1910_004c1910);
        if (v0 != 0) {
            // 0x0048ec60
            charge(ctx, 14);
            lw(v1, sp, 0x6C);
            v0 = 0x30000;
            a1 = v0 | 0x11F;
            v0 = 0x960000;
            sw(v1, s0, udlist::kCount);
            lw(v1, s0, udlist::kCount);
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = sll(v1, 4);
            jalr(ctx, 0x48EC7Cu, v0.u());
            sw(v0, s0, udlist::kArrays);
            lw(v0, s0, udlist::kCount);
            at = slt(0, v0);
            s2 = 0;
            if (at != 0) {
                // 0x0048ec98
                charge(ctx, 1);
                s1 = 0;
                for (;;) {
                    // 0x0048ec9c
                    charge(ctx, 10);
                    lw(v0, s0, udlist::kArrays);
                    a1 = s3;
                    a0 = addu(v0, s1);
                    jal(ctx, 0x48ECA4u, gen::fn_sub_48E020_0048e020);
                    s3 = v0;
                    s2 = addiu(s2, 1);
                    lw(v0, s0, udlist::kCount);
                    v0 = slt(s2, v0);
                    s1 = addiu(s1, 16);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048ecc4
                charge(ctx, 1);
            }
        }
    }
    // 0x0048ecc8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_48ECF0 [userDataStreamWrite] -- the user data extension stream write: the list written (sub_48E750); the stream
// 0x0048ECF0 sub_48ECF0 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_48ECF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048ecf0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addu(a2, a3);
    a1 = s0;
    jal(ctx, 0x48ED04u, gen::fn_sub_48E750_0048e750);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_48ED20 [userDataStreamSize] -- the user data extension stream size: the arrays with a format (sub_48E4F0) + 4, or 0
// 0x0048ED20 sub_48ED20 -- 192 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48ED20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048ed20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = 0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addu(a0, a1);
    s2 = 0;
    if (s0 != 0) {
        // 0x0048ed4c
        charge(ctx, 3);
        lw(v0, s0, udlist::kCount);
        if (i64(v0) > 0) {
            // 0x0048ed58
            charge(ctx, 3);
            at = slt(0, v0);
            s3 = 0;
            if (at != 0) {
                // 0x0048ed64
                charge(ctx, 1);
                s1 = 0;
                for (;;) {
                    // 0x0048ed68
                    charge(ctx, 5);
                    lw(v0, s0, udlist::kArrays);
                    a0 = addu(v0, s1);
                    lw(v0, a0, 4);
                    if (v0 != 0) {
                        // 0x0048edac
                        charge(ctx, 4);
                        jal(ctx, 0x48EDACu, gen::fn_sub_48E4F0_0048e4f0);
                        s2 = addu(s2, v0);
                        backedge(ctx);
                    } else {
                        // 0x0048ed7c
                        charge(ctx, 1);
                    }
                    // 0x0048ed80
                    charge(ctx, 5);
                    lw(v0, s0, udlist::kCount);
                    s3 = addiu(s3, 1);
                    v0 = slt(s3, v0);
                    s1 = addiu(s1, 16);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048ed94
                charge(ctx, 1);
            }
            // 0x0048ed98
            charge(ctx, 2);
            if (i64(s2) > 0) {
                // 0x0048eda0
                charge(ctx, 1);
                s2 = addiu(s2, 4);
            }
        }
    }
    // 0x0048eda4
    charge(ctx, 2);
    v0 = addu(s4, s2);
    // 0x0048edc0
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_48EDE0 [userDataCountFilled] -- the number of an object's user data arrays that have elements (data != 0)
// 0x0048EDE0 sub_48EDE0 -- 72 bytes; leaf frame (no stack)
void sub_48EDE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x0048ede0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, -17704);  // 0x7CE7C8 (a user-data extension offset (the object of the 0x1A6xxx accessors))
    v0 = 0;
    v1 = addu(a0, v1);
    lw(a0, v1, udlist::kCount);
    at = slt(0, a0);
    a2 = 0;
    if (at != 0) {
        // 0x0048edfc
        charge(ctx, 1);
        lw(a1, v1, udlist::kArrays);
        for (;;) {
            // 0x0048ee00
            charge(ctx, 3);
            lw(v1, a1, uda::kData);
            if (v1 != 0) {
                // 0x0048ee0c
                charge(ctx, 1);
                v0 = addiu(v0, 1);
            }
            // 0x0048ee10
            charge(ctx, 4);
            a2 = addiu(a2, 1);
            v1 = slt(a2, a0);
            a1 = addiu(a1, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0048ee20 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_48EE30 [userDataGetArray] -- an object's user data array $a1 (its 16-byte record), or 0 past the count
// 0x0048EE30 sub_48EE30 -- 52 bytes; leaf frame (no stack)
void sub_48EE30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0048ee30
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, -17704);  // 0x7CE7C8 (a user-data extension offset (the object of the 0x1A6xxx accessors))
    a0 = addu(a0, v0);
    lw(v0, a0, udlist::kCount);
    at = slt(a1, v0);
    if (at == 0) {
        // 0x0048ee58
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0048ee48
        charge(ctx, 4);
        lw(v0, a0, udlist::kArrays);
        v1 = sll(a1, 4);
        v0 = addu(v0, v1);
    }
    // 0x0048ee5c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_48EE70 [userDataAddArrayTo] -- adds a user data array to the object of extension gp 0x7CE7E0 (sub_48E890 on its list); the index
// 0x0048EE70 sub_48EE70 -- 12 bytes; leaf frame (no stack)
void sub_48EE70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0048ee70
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -17680);  // 0x7CE7E0
    a0 = addu(a0, v0);
    gen::fn_sub_48E890_0048e890(ctx);  // tail call
}


// name__C9type_info_0 -- returns the word at $a0 + 0: here an RpUserDataArray's name (RpUserDataArrayGetName)
// The 2-instruction body is shared with type_info::name (identical code); its 14 callers are the user data accessors
// of 0x1A6xxx.
// 0x0048EF10 name__C9type_info_0 -- 8 bytes; leaf frame (no stack)
void name__C9type_info_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048ef10
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, uda::kName);
}


// sub_48EF20 [RpUserDataArrayGetFormat] -- a user data array's format (+4)
// 0x0048EF20 sub_48EF20 -- 8 bytes; leaf frame (no stack)
void sub_48EF20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048ef20
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, uda::kFormat);
}


// sub_48EF30 [RpUserDataArrayGetNumElements] -- a user data array's element count (+8)
// 0x0048EF30 sub_48EF30 -- 8 bytes; leaf frame (no stack)
void sub_48EF30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048ef30
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, uda::kCount);
}


// sub_48EF40 [RpUserDataArrayGetInt] -- element $a1 of a user data array as an int
// 0x0048EF40 sub_48EF40 -- 20 bytes; leaf frame (no stack)
void sub_48EF40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0048ef40
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, uda::kData);
    v1 = sll(a1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}


// sub_48EF60 [RpUserDataArrayGetReal] -- element $a1 of a user data array as a real ($f0)
// 0x0048EF60 sub_48EF60 -- 20 bytes; leaf frame (no stack)
void sub_48EF60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0};
    // 0x0048ef60
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, uda::kData);
    v1 = sll(a1, 2);
    v0 = addu(v0, v1);
    lwc1(f0, v0, 0);
}


// sub_48EFA0 [RpUserDataArraySetInt] -- element $a1 of a user data array = $a2
// 0x0048EFA0 sub_48EFA0 -- 20 bytes; leaf frame (no stack)
void sub_48EFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0048efa0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, uda::kData);
    a1 = sll(a1, 2);
    v1 = addu(v1, a1);
    sw(a2, v1, 0);
}


// sub_48EFC0 [RpUserDataArraySetReal] -- element $a1 of a user data array = $f12
// 0x0048EFC0 sub_48EFC0 -- 20 bytes; leaf frame (no stack)
void sub_48EFC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f12{ctx, 12};
    // 0x0048efc0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, uda::kData);
    a1 = sll(a1, 2);
    v1 = addu(v1, a1);
    swc1(f12, v1, 0);
}


// sub_48EFE0 [RpUserDataGetFormatSize] -- the element size of a user data format: 4 for 1 (int), 2 (real), 3 (string pointer), else 0
// 0x0048EFE0 sub_48EFE0 -- 72 bytes; leaf frame (no stack)
void sub_48EFE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048efe0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 3;
    if (a0 == v0) {
        // 0x0048f01c
        charge(ctx, 1);
        v0 = 4;
    } else {
        // 0x0048efec
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x0048f014
            charge(ctx, 2);
            v0 = 4;
        } else {
            // 0x0048eff8
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                // 0x0048f00c
                charge(ctx, 2);
                v0 = 4;
            } else {
                // 0x0048f004
                charge(ctx, 2);
                v0 = 0;
            }
        }
    }
    // 0x0048f020 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_48F340 [atomicPipeStreamRead] -- the atomic's pipeline-id stream read: the plugin id (held at gp 0x7CE804) and, for an 8-byte chunk, the data (0x7CE800)
// Held until the rights callback picks the pipeline. The stream, or 0 when a word cannot be read.
// 0x0048F340 sub_48F340 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48F340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048f340
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = addiu(gp, -17644);  // &0x7CE804 (the atomic's streamed pipeline data)
    jal(ctx, 0x48F35Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x0048f380
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0048f36c
        charge(ctx, 3);
        v0 = 8;
        if (s0 == v0) {
            // 0x0048f388
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(gp, -17648);  // &0x7CE800 (the atomic's streamed pipeline id (held for the rights callback))
            a2 = 4;
            jal(ctx, 0x48F390u, gen::fn_sub_4C1910_004c1910);
            if (v0 != 0) {
                backedge(ctx);
                goto L_0048f378;
            }
            // 0x0048f3a0
            charge(ctx, 1);
            v0 = 0;
            // 0x0048f3a4 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0048f378:
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x0048f3a4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_48F3C0 [atomicPipeStreamWrite] -- the atomic's pipeline-id stream write: its pipeline's plugin id and data (+44 / +48)
// 0x0048F3C0 sub_48F3C0 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48F3C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048f3c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lw(v0, a2, atomic::kPipeline);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a1 = addiu(v0, 44);
    a2 = 4;
    jal(ctx, 0x48F3E0u, gen::fn_sub_4C17F0_004c17f0);
    if (v0 != 0) {
        // 0x0048f3f8
        charge(ctx, 7);
        lw(v0, s0, atomic::kPipeline);
        a0 = s1;
        a2 = 4;
        a1 = addiu(v0, 48);
        jal(ctx, 0x48F404u, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x0048f3f0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0048f414 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_48F430 [atomicPipeStreamSize] -- the atomic's pipeline-id stream size: 8 when its pipeline (+108) has a plugin id, else 0
// 0x0048F430 sub_48F430 -- 44 bytes; leaf frame (no stack)
void sub_48F430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048f430
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, atomic::kPipeline);
    if (v0 != 0) {
        // 0x0048f43c
        charge(ctx, 3);
        lw(v0, v0, pipeline::kPluginId);
        if (v0 == 0) {
            goto L_0048f450;
        }
        // 0x0048f448
        charge(ctx, 2);
        v0 = 8;
        // 0x0048f454 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0048f450:
    charge(ctx, 1);
    v0 = 0;
    // 0x0048f454 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_48F460 [sectorPipeStreamRead] -- the world sector's pipeline-id stream read: the plugin id (gp 0x7CE7FC) and, for an 8-byte chunk, the data (0x7CE7F8)
// 0x0048F460 sub_48F460 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48F460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048f460
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = addiu(gp, -17652);  // &0x7CE7FC (the world sector's streamed pipeline data)
    jal(ctx, 0x48F47Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x0048f4a0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0048f48c
        charge(ctx, 3);
        v0 = 8;
        if (s0 == v0) {
            // 0x0048f4a8
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(gp, -17656);  // &0x7CE7F8 (the world sector's streamed pipeline id (held for the rights callback))
            a2 = 4;
            jal(ctx, 0x48F4B0u, gen::fn_sub_4C1910_004c1910);
            if (v0 != 0) {
                backedge(ctx);
                goto L_0048f498;
            }
            // 0x0048f4c0
            charge(ctx, 1);
            v0 = 0;
            // 0x0048f4c4 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0048f498:
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x0048f4c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_48F4E0 [sectorPipeStreamWrite] -- the world sector's pipeline-id stream write: its pipeline's plugin id and data (+44 / +48)
// 0x0048F4E0 sub_48F4E0 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48F4E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048f4e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lw(v0, a2, 124);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a1 = addiu(v0, 44);
    a2 = 4;
    jal(ctx, 0x48F500u, gen::fn_sub_4C17F0_004c17f0);
    if (v0 != 0) {
        // 0x0048f518
        charge(ctx, 7);
        lw(v0, s0, 124);
        a0 = s1;
        a2 = 4;
        a1 = addiu(v0, 48);
        jal(ctx, 0x48F524u, gen::fn_sub_4C17F0_004c17f0);
        if (v0 == 0) s1 = 0;
        v0 = s1;
    } else {
        // 0x0048f510
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0048f534 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_48F550 [sectorPipeStreamSize] -- the world sector's pipeline-id stream size: 8 when its pipeline (+124) has a plugin id, else 0
// 0x0048F550 sub_48F550 -- 44 bytes; leaf frame (no stack)
void sub_48F550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048f550
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 124);
    if (v0 != 0) {
        // 0x0048f55c
        charge(ctx, 3);
        lw(v0, v0, pipeline::kPluginId);
        if (v0 == 0) {
            goto L_0048f570;
        }
        // 0x0048f568
        charge(ctx, 2);
        v0 = 8;
        // 0x0048f574 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0048f570:
    charge(ctx, 1);
    v0 = 0;
    // 0x0048f574 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_494580 [RpLightStreamRead] -- reads a light: the struct chunk (library 0x35000..0x37002), the light created by type (sub_4947C0), radius, colour, cone, flags, its plugins
// Versions before 0x30300 store the cone as tan: -sqrt(1 / (1 + t^2)) is taken. The grey flag (+3) when r = g = b.
// The light, or 0 (a wrong version raises error 0x80000004).
// 0x00494580 sub_494580 -- 472 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_494580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00494580
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a1 = 1;
    sd(ra, sp, 0x30);
    a2 = addiu(sp, 0x6C);
    sq(s2, sp, 0x20);
    a3 = addiu(sp, 0x68);
    sq(s1, sp, 0x10);
    s2 = a0;
    link(ctx, 0x4945A0u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x00494610
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004945b0
        charge(ctx, 6);
        lw(v1, sp, 0x68);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004945c8
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_0049471c;
            }
            // 0x004945dc
            charge(ctx, 11);
            a0 = addiu(sp, 0x40);
            a1 = 0;
            a2 = 24;
            jal(ctx, 0x4945E4u, gen::fn_memset_00521408);
            lw(s0, sp, 0x6C);
            a0 = s2;
            a1 = addiu(sp, 0x40);
            a2 = s0;
            jal(ctx, 0x4945F8u, gen::fn_sub_4C5250_004c5250);
            if (s0 == v0) {
                // 0x00494618
                charge(ctx, 8);
                s0 = addiu(sp, 0x54);
                lw(v0, s0, 0);
                v0 = srl(v0, 16);
                a0 = v0 & 0xFF;
                jal(ctx, 0x494624u, gen::fn_sub_4947C0_004947c0);
                s1 = v0;
                if (s1 == 0) {
                    // 0x004946f0
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00494638
                    charge(ctx, 14);
                    lwc1(f0, sp, 0x40);
                    at = 0x30000;
                    at = at | 0x300;
                    swc1(f0, s1, light::kRadius);
                    lwc1(f0, sp, 0x44);
                    swc1(f0, s1, light::kColor);
                    lwc1(f0, sp, 0x48);
                    swc1(f0, s1, light::kColorG);
                    lwc1(f0, sp, 0x4C);
                    swc1(f0, s1, light::kColorB);
                    lw(v0, sp, 0x68);
                    at = sltu(v0, at);
                    if (at == 0) {
                        // 0x004946a4
                        charge(ctx, 2);
                        lwc1(f0, sp, 0x50);
                        swc1(f0, s1, light::kMinusCosAngle);
                    } else {
                        // 0x00494670
                        charge(ctx, 13);
                        lwc1(f2, sp, 0x50);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        madd_s(f0, f2, f2);
                        div_s(f0, f1, f0);
                        sqrt_s(f0, f0);
                        neg_s(f0, f0);
                        swc1(f0, s1, light::kMinusCosAngle);
                    }
                    // 0x004946ac
                    charge(ctx, 5);
                    lwc1(f1, s1, light::kColor);
                    lwc1(f0, s1, light::kColorG);
                    c_eq_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x004946f8
                        charge(ctx, 4);
                        lwc1(f0, s1, light::kColorB);
                        c_eq_s(f1, f0);
                        if (!cond(ctx)) {
                            backedge(ctx);
                            goto L_004946c0;
                        }
                        // 0x00494708
                        charge(ctx, 3);
                        v0 = 1;
                        sb(v0, s1, light::kPrivateFlags);
                        backedge(ctx);
                        goto L_004946c4;
                    }
                L_004946c0:
                    charge(ctx, 1);
                    sb(zero, s1, light::kPrivateFlags);
                L_004946c4:
                    charge(ctx, 9);
                    lw(v0, s0, 0);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -8896);  // &0x77DD40
                    a2 = s1;
                    link(ctx, 0x4946D8u);  // $ra first: the delay slot below depends on it
                    sb(v0, s1, light::kFlags);
                    call(ctx, gen::fn_sub_4C5A50_004c5a50);
                    if (v0 == 0) {
                        // 0x00494714
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x004946e8
                        charge(ctx, 2);
                        v0 = s1;
                    }
                }
            } else {
                // 0x00494608
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x00494740 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_0049471c:
        charge(ctx, 9);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x60);
        a0 = v0 | 0x4;
        jal(ctx, 0x494728u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x64);
        a0 = addiu(sp, 0x60);
        jal(ctx, 0x494734u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00494740 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_494E30 [RpMaterialStreamRead] -- reads a material: the struct chunk (library 0x35000..0x37002), a material from the free list, colour, surface properties, the texture, its plugins
// The texture chunk when the 'textured' word is set (RwTextureStreamRead); a failure destroys the material (its
// plugin data, texture and record, or one reference). A rights plugin left by the plugin read (gp 0x7CE83C, its
// data 0x7CE838) gets its rights callback (sub_4C5C30). The material, or 0.
// 0x00494E30 sub_494E30 -- 1068 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_494E30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00494e30
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    a1 = 1;
    sd(ra, sp, 0x30);
    a2 = addiu(sp, 0x7C);
    sq(s2, sp, 0x20);
    a3 = addiu(sp, 0x78);
    sq(s1, sp, 0x10);
    s2 = a0;
    link(ctx, 0x494E50u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x00494ec0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00494e60
        charge(ctx, 6);
        lw(v1, sp, 0x78);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x00494e78
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_00495220;
            }
            // 0x00494e8c
            charge(ctx, 11);
            a0 = addiu(sp, 0x40);
            a1 = 0;
            a2 = 28;
            jal(ctx, 0x494E94u, gen::fn_memset_00521408);
            lw(s0, sp, 0x7C);
            a0 = s2;
            a1 = addiu(sp, 0x40);
            a2 = s0;
            jal(ctx, 0x494EA8u, gen::fn_sub_4C5250_004c5250);
            if (s0 == v0) {
                // 0x00494ec8
                charge(ctx, 20);
                lw(a0, gp, -17584);  // 0x7CE840
                v1 = 0x960000;
                v0 = 0x30000;
                t1 = addiu(sp, 0x46);
                a3 = addiu(sp, 0x47);
                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                a1 = v0 | 0x7;
                lbu(t0, t1, 0);
                lbu(a2, a3, 0);
                v0 = 0x960000;
                lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
                s0 = addiu(sp, 0x44);
                v1 = addu(v1, a0);
                lw(a0, v1, 0);
                sb(t0, t1, 0);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x494F04u);  // $ra = the return address
                sb(a2, a3, 0);
                call_ptr(ctx, jt);
                s1 = v0;
                if (s1 == 0) {
                    // 0x004950a0
                    charge(ctx, 2);
                    s1 = 0;
                    backedge(ctx);
                } else {
                    // 0x00494f18
                    charge(ctx, 30);
                    a1 = 255;
                    v0 = 1;
                    sb(a1, sp, 0x74);
                    a0 = 0x780000;
                    sb(a1, sp, 0x75);
                    a2 = 0x780000;
                    sb(a1, sp, 0x76);
                    v1 = 0x780000;
                    sb(a1, sp, 0x77);
                    a0 = addiu(a0, -8864);  // &0x77DD60
                    lbu(t2, sp, 0x74);
                    a1 = s1;
                    lbu(t1, sp, 0x75);
                    sh(v0, s1, material::kRefCount);
                    lbu(t0, sp, 0x76);
                    v0 = 0x780000;
                    lbu(a3, sp, 0x77);
                    sb(t2, s1, material::kColor);
                    sb(t1, s1, material::kColorG);
                    sb(t0, s1, material::kColorB);
                    sb(a3, s1, material::kColorA);
                    sw(zero, s1, material::kTexture);
                    sw(zero, s1, material::kPipeline);
                    lwc1(f2, a2, -8840);  // 0x77DD78
                    lwc1(f1, v1, -8836);  // 0x77DD7C
                    lwc1(f0, v0, -8832);  // 0x77DD80
                    swc1(f2, s1, material::kAmbient);
                    swc1(f1, s1, material::kSpecular);
                    link(ctx, 0x494F88u);  // $ra first: the delay slot below depends on it
                    swc1(f0, s1, material::kDiffuse);
                    call(ctx, gen::fn_sub_4C64B0_004c64b0);
                }
                // 0x00494f90
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x004950a8
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00494f98
                    charge(ctx, 18);
                    lbu(a1, s0, 0);
                    lbu(a0, s0, 1);
                    lbu(v1, s0, 2);
                    lbu(v0, s0, 3);
                    sb(a1, s1, material::kColor);
                    sb(a0, s1, material::kColorG);
                    sb(v1, s1, material::kColorB);
                    sb(v0, s1, material::kColorA);
                    lwc1(f2, sp, 0x50);
                    lwc1(f1, sp, 0x54);
                    lwc1(f0, sp, 0x58);
                    swc1(f2, s1, material::kAmbient);
                    swc1(f1, s1, material::kSpecular);
                    swc1(f0, s1, material::kDiffuse);
                    sw(zero, s1, material::kTexture);
                    lw(v0, sp, 0x4C);
                    if (v0 != 0) {
                        // 0x00494fe0
                        charge(ctx, 7);
                        a0 = s2;
                        a1 = 6;
                        a2 = 0;
                        a3 = addiu(sp, 0x78);
                        jal(ctx, 0x494FECu, gen::fn_sub_4C1600_004c1600);
                        if (v0 != 0) {
                            // 0x00495020
                            charge(ctx, 6);
                            lw(v1, sp, 0x78);
                            v0 = 0x30000;
                            v0 = v0 | 0x5000;
                            v0 = sltu(v1, v0);
                            if (v0 == 0) {
                                // 0x00495038
                                charge(ctx, 5);
                                at = 0x30000;
                                at = at | 0x7003;
                                at = sltu(v1, at);
                                if (at == 0) {
                                    goto L_00495104;
                                }
                                // 0x0049504c
                                charge(ctx, 3);
                                a0 = s2;
                                jal(ctx, 0x49504Cu, gen::fn_sub_4C83C0_004c83c0);
                                sw(v0, s1, material::kTexture);
                                goto L_00495058;
                            }
                        L_00495104:
                            charge(ctx, 4);
                            lh(v1, s1, material::kRefCount);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x00495148
                                charge(ctx, 7);
                                a0 = 0x780000;
                                a1 = s1;
                                a0 = addiu(a0, -8864);  // &0x77DD60
                                jal(ctx, 0x495150u, gen::fn_sub_4C6560_004c6560);
                                lw(a0, s1, material::kTexture);
                                if (a0 != 0) {
                                    // 0x00495164
                                    charge(ctx, 2);
                                    jal(ctx, 0x495164u, gen::fn_sub_4D0F00_004d0f00);
                                }
                                // 0x0049516c
                                charge(ctx, 12);
                                sw(zero, s1, material::kTexture);
                                v1 = 0x960000;
                                lw(a0, gp, -17584);  // 0x7CE840
                                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                                v0 = 0x960000;
                                lw(v0, v0, 396);  // 0x96018C (free-list free slot)
                                v1 = addu(v1, a0);
                                lw(a0, v1, 0);
                                a1 = s1;
                                jalr(ctx, 0x49518Cu, v0.u());
                                v1 = 2;
                                backedge(ctx);
                            } else {
                                // 0x00495114
                                charge(ctx, 4);
                                lh(v0, s1, material::kRefCount);
                                v0 = addiu(v0, -1);
                                sh(v0, s1, material::kRefCount);
                                v1 = 2;
                            }
                            // 0x00495124
                            charge(ctx, 9);
                            v0 = lui(0x8000);
                            sw(v1, sp, 0x68);
                            a0 = v0 | 0x4;
                            jal(ctx, 0x49512Cu, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x6C);
                            a0 = addiu(sp, 0x68);
                            jal(ctx, 0x495138u, gen::fn_sub_4C1C50_004c1c50);
                            v0 = 0;
                        } else {
                            // 0x00494ffc
                            charge(ctx, 4);
                            lh(v1, s1, material::kRefCount);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x004950b0
                                charge(ctx, 7);
                                a0 = 0x780000;
                                a1 = s1;
                                a0 = addiu(a0, -8864);  // &0x77DD60
                                jal(ctx, 0x4950B8u, gen::fn_sub_4C6560_004c6560);
                                lw(a0, s1, material::kTexture);
                                if (a0 != 0) {
                                    // 0x004950cc
                                    charge(ctx, 2);
                                    jal(ctx, 0x4950CCu, gen::fn_sub_4D0F00_004d0f00);
                                }
                                // 0x004950d4
                                charge(ctx, 12);
                                sw(zero, s1, material::kTexture);
                                v1 = 0x960000;
                                lw(a0, gp, -17584);  // 0x7CE840
                                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                                v0 = 0x960000;
                                lw(v0, v0, 396);  // 0x96018C (free-list free slot)
                                v1 = addu(v1, a0);
                                lw(a0, v1, 0);
                                a1 = s1;
                                jalr(ctx, 0x4950F4u, v0.u());
                                backedge(ctx);
                            } else {
                                // 0x0049500c
                                charge(ctx, 3);
                                lh(v0, s1, material::kRefCount);
                                v0 = addiu(v0, -1);
                                sh(v0, s1, material::kRefCount);
                            }
                            // 0x00495018
                            charge(ctx, 2);
                            v0 = 0;
                        }
                        // 0x00495244 (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        ld(ra, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x80);
                        return;
                    }
                L_00495058:
                    charge(ctx, 9);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -8864);  // &0x77DD60
                    a2 = s1;
                    sw(zero, gp, -17588);  // 0x7CE83C
                    link(ctx, 0x49506Cu);  // $ra first: the delay slot below depends on it
                    sw(zero, gp, -17592);  // 0x7CE838
                    call(ctx, gen::fn_sub_4C5A50_004c5a50);
                    if (v0 != 0) {
                        // 0x004951f0
                        charge(ctx, 3);
                        lw(a1, gp, -17588);  // 0x7CE83C
                        if (a1 != 0) {
                            // 0x00495204
                            charge(ctx, 7);
                            lw(a3, gp, -17592);  // 0x7CE838
                            a0 = 0x780000;
                            a0 = addiu(a0, -8864);  // &0x77DD60
                            a2 = s1;
                            jal(ctx, 0x495210u, gen::fn_sub_4C5C30_004c5c30);
                            backedge(ctx);
                        }
                        // 0x004951fc
                        charge(ctx, 2);
                        v0 = s1;
                    } else {
                        // 0x0049507c
                        charge(ctx, 4);
                        lh(v1, s1, material::kRefCount);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x0049519c
                            charge(ctx, 7);
                            a0 = 0x780000;
                            a1 = s1;
                            a0 = addiu(a0, -8864);  // &0x77DD60
                            jal(ctx, 0x4951A4u, gen::fn_sub_4C6560_004c6560);
                            lw(a0, s1, material::kTexture);
                            if (a0 != 0) {
                                // 0x004951b8
                                charge(ctx, 2);
                                jal(ctx, 0x4951B8u, gen::fn_sub_4D0F00_004d0f00);
                            }
                            // 0x004951c0
                            charge(ctx, 12);
                            sw(zero, s1, material::kTexture);
                            v1 = 0x960000;
                            lw(a0, gp, -17584);  // 0x7CE840
                            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                            v0 = 0x960000;
                            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
                            v1 = addu(v1, a0);
                            lw(a0, v1, 0);
                            a1 = s1;
                            jalr(ctx, 0x4951E0u, v0.u());
                            backedge(ctx);
                        } else {
                            // 0x0049508c
                            charge(ctx, 3);
                            lh(v0, s1, material::kRefCount);
                            v0 = addiu(v0, -1);
                            sh(v0, s1, material::kRefCount);
                        }
                        // 0x00495098
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
            } else {
                // 0x00494eb8
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x00495244 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x80);
            return;
        }
    L_00495220:
        charge(ctx, 9);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x60);
        a0 = v0 | 0x4;
        jal(ctx, 0x49522Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x64);
        a0 = addiu(sp, 0x60);
        jal(ctx, 0x495238u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00495244 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}


// sub_495FB0 [binMeshStreamWrite] -- writes a bin-mesh header: {flags, mesh count, total indices}, per mesh {index count, material index} and its indices
// ($a0 = the mesh header, $a1 = the geometry / world, $a2 = the stream, $a3 = the material list) The material index
// from sub_495480 (-1 -> 0); the indices widened to 32-bit words, 256 per write, unless flag 0x1000000 in the geometry's / world's flags (+8) and type 7 / 8 = native data: no indices are streamed. The stream,
// or 0 on a write error.
// 0x00495FB0 sub_495FB0 -- 636 bytes; frame 0x4C0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_495FB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00495fb0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4C0);
    lhu(v1, a0, 4);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = a3;
    sq(s6, sp, 0x60);
    s7 = a1;
    sq(s5, sp, 0x50);
    a1 = addiu(sp, 0x4B0);
    sq(s4, sp, 0x40);
    s5 = a2;
    sq(s3, sp, 0x30);
    a2 = 12;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a3, a0, 0);
    s0 = a0;
    lw(v0, a0, 8);
    sw(v1, sp, 0x4B4);
    sw(a3, sp, 0x4B0);
    sw(v0, sp, 0x4B8);
    a0 = s5;
    jal(ctx, 0x49600Cu, gen::fn_sub_4C17F0_004c17f0);
    if (v0 == 0) {
        // 0x00496034
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049601c
        charge(ctx, 4);
        lhu(v0, s0, 4);
        s3 = addiu(s0, 16);
        s4 = addiu(v0, -1);
        if (v0 != 0) {
            // 0x0049603c
            charge(ctx, 1);
            s6 = addiu(s7, 8);
            for (;;) {
                // 0x00496040
                charge(ctx, 8);
                lw(v0, s3, 4);
                a0 = fp;
                lw(a1, s3, 8);
                link(ctx, 0x49604Cu);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x4A8);
                call(ctx, gen::fn_sub_495480_00495480);
                v1 = addiu(sp, 0x4AC);
                sw(v0, v1, 0);
                if (i64(v0) < 0) {
                    // 0x004961b8
                    charge(ctx, 3);
                    v0 = v1;
                    sw(zero, v0, 0);
                    backedge(ctx);
                }
                // 0x00496060
                charge(ctx, 6);
                a0 = s5;
                a1 = addiu(sp, 0x4A8);
                a2 = 8;
                jal(ctx, 0x496068u, gen::fn_sub_4C17F0_004c17f0);
                if (v0 == 0) {
                    goto L_004961c8;
                }
                // 0x00496078
                charge(ctx, 4);
                lbu(a0, s7, 0);
                v0 = 8;
                if (a0 == v0) {
                    // 0x004961d0
                    charge(ctx, 5);
                    lw(v1, s6, 0);
                    v0 = 0x1000000;
                    v0 = v1 & v0;
                    if (v0 != 0) {
                        // 0x004961e4
                        charge(ctx, 2);
                        backedge(ctx);
                        goto L_00496088;
                    }
                    backedge(ctx);
                L_004960a8:
                    charge(ctx, 3);
                    lw(s2, s3, 4);
                    lw(s1, s3, 0);
                    if (s2 == 0) {
                    L_004961a0:
                        charge(ctx, 4);
                        v0 = s4;
                        s3 = addiu(s3, 12);
                        s4 = addiu(s4, -1);
                        if (v0 == 0) {
                            goto L_004961b0_27;
                        }
                        backedge(ctx);
                        continue;
                    }
                    // 0x004960b4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004960b8
                        charge(ctx, 3);
                        at = sltiu(s2, 256);
                        if (at == 0) {
                            // 0x004961f0
                            charge(ctx, 2);
                            s0 = 256;
                            backedge(ctx);
                        } else {
                            // 0x004960c4
                            charge(ctx, 1);
                            s0 = s2;
                        }
                        // 0x004960c8
                        charge(ctx, 3);
                        at = sltu(0, s0);
                        v0 = 0;
                        if (at != 0) {
                            // 0x004960d4
                            charge(ctx, 3);
                            at = sltiu(s0, 9);
                            a1 = addiu(s0, -8);
                            if (at == 0) {
                                // 0x004960e0
                                charge(ctx, 2);
                                a2 = addiu(sp, 0xA0);
                                for (;;) {
                                    // 0x004960e8
                                    charge(ctx, 21);
                                    lhu(a0, s1, 0);
                                    v0 = addiu(v0, 8);
                                    v1 = sltu(v0, a1);
                                    sw(a0, a2, 0);
                                    lhu(a0, s1, 2);
                                    sw(a0, a2, 4);
                                    lhu(a0, s1, 4);
                                    sw(a0, a2, 8);
                                    lhu(a0, s1, 6);
                                    sw(a0, a2, 12);
                                    lhu(a0, s1, 8);
                                    sw(a0, a2, 16);
                                    lhu(a0, s1, 10);
                                    sw(a0, a2, 20);
                                    lhu(a0, s1, 12);
                                    sw(a0, a2, 24);
                                    lhu(a0, s1, 14);
                                    sw(a0, a2, 28);
                                    s1 = addiu(s1, 16);
                                    a2 = addiu(a2, 32);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x0049613c
                                charge(ctx, 1);
                            }
                            // 0x00496140
                            charge(ctx, 3);
                            at = sltu(v0, s0);
                            if (at != 0) {
                                // 0x0049614c
                                charge(ctx, 3);
                                v1 = sll(v0, 2);
                                v1 = addu(v1, sp);
                                a1 = addiu(v1, 160);
                                for (;;) {
                                    // 0x00496158
                                    charge(ctx, 7);
                                    lhu(a0, s1, 0);
                                    v0 = addiu(v0, 1);
                                    v1 = sltu(v0, s0);
                                    sw(a0, a1, 0);
                                    s1 = addiu(s1, 2);
                                    a1 = addiu(a1, 4);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x00496174
                                charge(ctx, 1);
                            }
                        }
                        // 0x00496178
                        charge(ctx, 6);
                        a2 = sll(s0, 2);
                        a0 = s5;
                        a1 = addiu(sp, 0xA0);
                        jal(ctx, 0x496180u, gen::fn_sub_4C17F0_004c17f0);
                        if (v0 == 0) {
                            break;
                        }
                        // 0x00496190
                        charge(ctx, 3);
                        s2 = subu(s2, s0);
                        if (s2 == 0) {
                            goto L_0049619c_25;
                        }
                        backedge(ctx);
                    }
                    break;
                }
            L_00496088:
                charge(ctx, 3);
                v0 = 7;
                if (a0 != v0) {
                    goto L_004961a0;
                }
                // 0x00496094
                charge(ctx, 5);
                lw(v1, s6, 0);
                v0 = 0x1000000;
                v0 = v1 & v0;
                if (v0 != 0) {
                    goto L_004961a0;
                }
                goto L_004960a8;
            }
            // 0x004961f8
            charge(ctx, 1);
            v0 = 0;
            // 0x004961fc (the shared epilogue, written out on this path)
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
            sp = addiu(sp, 0x4C0);
            return;
        }
    L_0049602c:
        charge(ctx, 2);
        v0 = s5;
    }
    // 0x004961fc (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x4C0);
    return;
L_0049619c_25:
    charge(ctx, 1);
    goto L_004961a0;
L_004961b0_27:
    charge(ctx, 2);
    backedge(ctx);
    goto L_0049602c;
L_004961c8:
    charge(ctx, 2);
    v0 = 0;
    // 0x004961fc (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x4C0);
}


// sub_496230 [binMeshStreamRead] -- reads a bin-mesh header: one RwMalloc for the header, the meshes and the indices; the serial number from the engine counter
// ($a0 = the stream, $a1 = the geometry / world, $a2 = the material list) 16 + 16 x meshes bytes (+ 2 x indices
// unless flag 0x1000000 in the geometry's / world's flags (+8) and type 7 / 8 = native data: no indices are streamed); each mesh's material through sub_495320, its indices read 256 words at a time and narrowed
// to u16. The header, or 0.
// 0x00496230 sub_496230 -- 704 bytes; frame 0x4D0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_496230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00496230
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4D0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sw(a1, sp, 0xAC);
    sw(a2, sp, 0xA8);
    a1 = addiu(sp, 0x4C0);
    sq(s1, sp, 0x10);
    a2 = 12;
    link(ctx, 0x49626Cu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x00496458
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049627c
        charge(ctx, 8);
        lw(v0, sp, 0xAC);
        s0 = addiu(sp, 0x4C4);
        lw(v1, s0, 0);
        lbu(a1, v0, 0);
        v1 = sll(v1, 4);
        v0 = 8;
        a0 = addiu(v1, 16);
        if (a1 != v0) {
            // 0x0049629c
            charge(ctx, 1);
            v0 = 7;
            goto L_004962a0;
        }
        // 0x00496460
        charge(ctx, 6);
        lw(v0, sp, 0xAC);
        lw(v1, v0, 8);
        v0 = 0x1000000;
        v0 = v1 & v0;
        if (v0 == 0) {
            backedge(ctx);
        L_004962c0:
            charge(ctx, 3);
            lw(v0, sp, 0x4C8);
            v0 = sll(v0, 1);
            a0 = addu(a0, v0);
        } else {
            // 0x00496478
            charge(ctx, 2);
            v0 = 7;
            backedge(ctx);
        L_004962a0:
            charge(ctx, 2);
            if (a1 == v0) {
                // 0x004962a8
                charge(ctx, 6);
                lw(v0, sp, 0xAC);
                lw(v1, v0, 8);
                v0 = 0x1000000;
                v0 = v1 & v0;
                if (v0 == 0) {
                    goto L_004962c0;
                }
            }
        }
        // 0x004962cc: one block: header, meshes, indices
        charge(ctx, 8);
        v0 = 0x960000;
        v1 = 0x30000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a1 = v1 | 0x502;
        jalr(ctx, 0x4962D8u, v0.u());
        fp = v0;
        if (fp != 0) {
            // 0x004962ec
            charge(ctx, 27);
            lw(a1, s0, 0);
            v1 = 0x960000;
            lw(v0, sp, 0x4C0);
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            s1 = addiu(fp, 0x10);
            a0 = sll(a1, 1);
            sw(v0, fp, meshhdr::kFlags);
            a0 = addu(a0, a1);
            lw(v0, s0, 0);
            a0 = sll(a0, 2);
            sh(v0, fp, meshhdr::kNumMeshes);
            s0 = addu(s1, a0);
            lw(v0, gp, -17568);  // 0x7CE850 (the mesh-header serial counter offset)
            v0 = addu(v1, v0);
            lh(v0, v0, 0);
            sh(v0, fp, meshhdr::kSerial);
            lw(v0, sp, 0x4C8);
            sw(v0, fp, meshhdr::kTotalIndices);
            sw(zero, fp, meshhdr::kFirstMeshOffset);
            lw(v0, gp, -17568);  // 0x7CE850 (the mesh-header serial counter offset)
            v1 = addu(v1, v0);
            lh(v0, v1, 0);
            v0 = addiu(v0, 1);
            sh(v0, v1, 0);
            lhu(v0, fp, meshhdr::kNumMeshes);
            s5 = addiu(v0, -1);
            if (v0 == 0) {
                goto L_00496450;
            }
            // 0x00496358
            charge(ctx, 2);
            lw(v0, sp, 0xAC);
            s7 = addiu(v0, 8);
            for (;;) {
                // 0x00496360: each mesh: index count, material
                charge(ctx, 6);
                a0 = s6;
                a1 = addiu(sp, 0x4B8);
                a2 = 8;
                jal(ctx, 0x496368u, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    break;
                }
                // 0x00496380
                charge(ctx, 12);
                lw(v0, sp, 0x4B8);
                sw(v0, s1, mesh::kNumIndices);
                v0 = addiu(sp, 0x4BC);
                lw(a1, v0, 0);
                link(ctx, 0x496390u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0xA8);
                call(ctx, gen::fn_sub_495320_00495320);
                sw(v0, s1, mesh::kMaterial);
                v1 = 8;
                lw(v0, sp, 0xAC);
                lbu(a0, v0, 0);
                sw(s0, s1, mesh::kIndices);
                if (a0 == v1) {
                    // 0x00496480
                    charge(ctx, 5);
                    lw(v1, s7, 0);
                    v0 = 0x1000000;
                    v0 = v1 & v0;
                    if (v0 != 0) {
                        // 0x00496494
                        charge(ctx, 2);
                        backedge(ctx);
                        goto L_004963b0;
                    }
                    backedge(ctx);
                L_004963d0:
                    charge(ctx, 3);
                    lw(s4, s1, mesh::kNumIndices);
                    if (s4 == 0) {
                    L_00496440:
                        charge(ctx, 4);
                        v0 = s5;
                        s1 = addiu(s1, 12);
                        s5 = addiu(s5, -1);
                        if (v0 == 0) {
                            goto L_00496450;
                        }
                        backedge(ctx);
                        continue;
                    }
                    // 0x004963dc: its indices, 256 words at a time, narrowed to u16
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004963e0
                        charge(ctx, 3);
                        at = sltiu(s4, 256);
                        s3 = addiu(sp, 0xB0);
                        if (at == 0) {
                            // 0x004964a0
                            charge(ctx, 2);
                            s2 = 256;
                            backedge(ctx);
                        } else {
                            // 0x004963ec
                            charge(ctx, 1);
                            s2 = s4;
                        }
                        // 0x004963f0
                        charge(ctx, 6);
                        a2 = sll(s2, 2);
                        a0 = s6;
                        a1 = s3;
                        jal(ctx, 0x4963F8u, gen::fn_sub_4C1910_004c1910);
                        if (v0 == 0) {
                            goto L_004964a8;
                        }
                        // 0x00496408
                        charge(ctx, 3);
                        s4 = subu(s4, s2);
                        a0 = addiu(s2, -1);
                        if (s2 != 0) {
                            // 0x00496414
                            charge(ctx, 1);
                            for (;;) {
                                // 0x00496418
                                charge(ctx, 7);
                                lw(v1, s3, 0);
                                v0 = a0;
                                a0 = addiu(a0, -1);
                                sh(v1, s0, 0);
                                s3 = addiu(s3, 4);
                                s0 = addiu(s0, 2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00496434
                            charge(ctx, 2);
                        }
                        // 0x004964b0
                        charge(ctx, 2);
                        if (s4 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004964b8
                    charge(ctx, 2);
                    backedge(ctx);
                    goto L_00496440;
                }
            L_004963b0:
                charge(ctx, 3);
                v0 = 7;
                if (a0 != v0) {
                    goto L_00496440;
                }
                // 0x004963bc
                charge(ctx, 5);
                lw(v1, s7, 0);
                v0 = 0x1000000;
                v0 = v1 & v0;
                if (v0 != 0) {
                    goto L_00496440;
                }
                goto L_004963d0;
            }
            // 0x00496378
            charge(ctx, 2);
            v0 = 0;
            // 0x004964c0 (the shared epilogue, written out on this path)
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
            sp = addiu(sp, 0x4D0);
            return;
        }
    L_00496450:
        charge(ctx, 2);
        v0 = fp;
    }
    // 0x004964c0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x4D0);
    return;
L_004964a8:
    charge(ctx, 2);
    v0 = 0;
    // 0x004964c0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x4D0);
}


// sub_4964F0 [binMeshStreamSize] -- the stream size of a bin-mesh header: 12 + 8 x meshes (+ 4 x the header's total indices unless native data)
// The write (sub_495FB0) streams each mesh's own index count: the two agree only while the header's total (+8) is
// its meshes' sum (6 of the b_5800 geometries' headers carry a total of 0).
// 0x004964F0 sub_4964F0 -- 132 bytes; leaf frame (no stack)
void sub_4964F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004964f0
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(a2, a1, 0);
    v0 = 8;
    if (a2 != v0) {
        // 0x00496500
        charge(ctx, 1);
        v0 = 7;
        goto L_00496504;
    }
    // 0x00496534
    charge(ctx, 5);
    lw(v1, a1, 8);
    v0 = 0x1000000;
    v0 = v1 & v0;
    if (v0 != 0) {
        backedge(ctx);
    L_00496520:
        charge(ctx, 3);
        lhu(v0, a0, meshhdr::kNumMeshes);
        v0 = sll(v0, 3);
        v0 = addiu(v0, 12);
    } else {
        // 0x00496548
        charge(ctx, 2);
        v0 = 7;
        backedge(ctx);
    L_00496504:
        charge(ctx, 2);
        if (a2 == v0) {
            // 0x0049650c
            charge(ctx, 5);
            lw(v1, a1, 8);
            v0 = 0x1000000;
            v0 = v1 & v0;
            if (v0 == 0) {
                goto L_00496550;
            }
            goto L_00496520;
        }
    L_00496550:
        charge(ctx, 7);
        lhu(v1, a0, meshhdr::kNumMeshes);
        lw(v0, a0, meshhdr::kTotalIndices);
        v1 = sll(v1, 3);
        v1 = addiu(v1, 12);
        v0 = sll(v0, 2);
        v0 = addu(v1, v0);
        backedge(ctx);
    }
    // 0x0049652c
    charge(ctx, 2);
    // 0x0049656c
    charge(ctx, 2);
}


// sub_496580 [meshHeaderNextSerial] -- the next mesh-header serial number: the engine's u16 counter, post-incremented (sign-extended)
// 0x00496580 sub_496580 -- 32 bytes; leaf frame (no stack)
void sub_496580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00496580
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -17568);  // 0x7CE850 (the mesh-header serial counter offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a0 = addu(v0, v1);
    lh(v0, a0, 0);
    v1 = addiu(v0, 1);
    sh(v1, a0, 0);
}


// sub_496AD0 [triStripFindEdge] -- the tri-strip builder's edge lookup: the open edge (v0, v1) of a bucket gets triangle $t0 as its second, else a new edge
// ($a0 = the edge free list, $a1 = the bucket, $a2 / $a3 = the vertices, $t0 = the triangle index, $t1 = the
// triangle table) An edge matching (v1 = $a2, v0 = $a3) with no second triangle takes it and both triangles' shared
// count (+32) goes up; otherwise a 16-byte edge from the free list is pushed on the bucket. Returns the edge.
// 0x00496AD0 sub_496AD0 -- 264 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_496AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00496ad0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    s1 = t0;
    lw(v0, a1, 0);
    s0 = t1;
    if (v0 != 0) {
        // 0x00496b08
        charge(ctx, 2);
        a2 = s3 & 0xFFFF;
        a1 = s2 & 0xFFFF;
        for (;;) {
            // 0x00496b10
            charge(ctx, 3);
            lhu(v1, v0, tsedge::kV0);
            if (a2 == v1) {
                // 0x00496b1c
                charge(ctx, 3);
                lhu(v1, v0, tsedge::kV1);
                if (a1 != v1) {
                    goto L_00496b68;
                }
                // 0x00496b28
                charge(ctx, 3);
                lw(v1, v0, tsedge::kOther);
                if (v1 != 0) {
                    goto L_00496b68;
                }
                goto L_00496b34_5;
            }
        L_00496b68:
            charge(ctx, 3);
            lw(v0, v0, tsedge::kNext);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00496b74
        charge(ctx, 1);
    }
    // 0x00496b78
    charge(ctx, 16);
    v0 = 0x30000;
    a1 = v0 | 0x502;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    jalr(ctx, 0x496B88u, v0.u());
    sh(s3, v0, tsedge::kV1);
    v1 = sll(s1, 2);
    v1 = addu(s0, v1);
    sh(s2, v0, tsedge::kV0);
    lw(v1, v1, 0);
    sw(v1, v0, tsedge::kTri);
    sw(zero, v0, tsedge::kOther);
    lw(v1, s4, 0);
    sw(v1, v0, tsedge::kNext);
    sw(v0, s4, 0);
    // 0x00496bb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_00496b34_5:
    charge(ctx, 13);
    lw(a0, v0, tsedge::kTri);
    v1 = sll(s1, 2);
    a1 = addu(s0, v1);
    lbu(v1, a0, 32);
    v1 = addiu(v1, 1);
    sb(v1, a0, 32);
    lw(a0, a1, 0);
    lbu(v1, a0, 32);
    v1 = addiu(v1, 1);
    sb(v1, a0, 32);
    lw(v1, a1, 0);
    sw(v1, v0, tsedge::kOther);
    // 0x00496bb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_496BE0 [triStripFreeEdges] -- frees the tri-strip builder's records: the edge list to its free list, the free lists destroyed, the triangle table freed; 0
// ($a0 = the triangle count, $a1 = the two free lists, $a2 = the edges, $a3 = the triangle table)
// 0x00496BE0 sub_496BE0 -- 228 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_496BE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00496be0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a2 != 0) {
        // 0x00496c10
        charge(ctx, 2);
        s1 = 0x960000;
        s1 = addiu(s1, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x00496c18
            charge(ctx, 7);
            lw(s0, a2, 12);
            lw(a0, s4, 4);
            lw(v0, s1, 0);
            a1 = a2;
            jalr(ctx, 0x496C24u, v0.u());
            a2 = s0;
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00496c34
        charge(ctx, 1);
    }
    // 0x00496c38
    charge(ctx, 6);
    link(ctx, 0x496C38u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 4);
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    at = sltu(0, s5);
    sw(zero, s4, 4);
    s2 = 0;
    if (at != 0) {
        // 0x00496c50
        charge(ctx, 3);
        s0 = 0x960000;
        s1 = s3;
        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x00496c5c
            charge(ctx, 9);
            lw(a1, s1, 0);
            lw(v0, s0, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x496C64u);  // $ra = the return address
            lw(a0, s4, 0);
            call_ptr(ctx, jt);
            s2 = addiu(s2, 1);
            sw(zero, s1, 0);
            v0 = sltu(s2, s5);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00496c80
    charge(ctx, 17);
    link(ctx, 0x496C80u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 0);
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    sw(zero, s4, 0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s3;
    jalr(ctx, 0x496C94u, v0.u());
    ld(ra, sp, 0x60);
    v0 = 0;
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_496CD0 [triStripBuildTriangles] -- builds the tri-strip builder's triangles: a 36-byte record per triangle and its three edges (sub_496AD0)
// ($a0 = the count, $a1 = the two free lists (created here, 36- and 16-byte), $a2 = the edge bucket, $a3 = the
// triangles' vertex indices, 20 bytes apart) Returns the RwMalloc'd table of triangle records.
// 0x00496CD0 sub_496CD0 -- 420 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_496CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00496cd0
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 0x960000;
    sd(ra, sp, 0x80);
    v1 = 0x30000;
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    a0 = sll(s6, 2);
    sq(s0, sp, 0x0);
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a1 = v1 | 0x502;
    jalr(ctx, 0x496D18u, v0.u());
    s2 = v0;
    a0 = 36;
    v0 = 0x30000;
    a1 = s6;
    a2 = 4;
    a3 = v0 | 0x502;
    jal(ctx, 0x496D34u, gen::fn_sub_4C3B50_004c3b50);
    sw(v0, s5, 0);
    a0 = 16;
    v0 = srl(s6, 1);
    a2 = 4;
    a1 = addiu(v0, 1);
    v0 = 0x30000;
    a3 = v0 | 0x502;
    jal(ctx, 0x496D54u, gen::fn_sub_4C3B50_004c3b50);
    sw(v0, s5, 4);
    v0 = sltu(0, s6);
    s1 = 0;
    if (v0 != 0) {
        // 0x00496d74
        charge(ctx, 3);
        s7 = 0x960000;
        s0 = s2;
        s7 = addiu(s7, 392);  // &0x960188 (free-list alloc slot)
        for (;;) {
            // 0x00496d80
            charge(ctx, 48);
            v0 = 0x30000;
            a1 = v0 | 0x502;
            lw(v0, s7, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x496D8Cu);  // $ra = the return address
            lw(a0, s5, 0);
            call_ptr(ctx, jt);
            sw(v0, s0, 0);
            a1 = s4;
            lw(v0, s0, 0);
            t0 = s1;
            sb(zero, v0, tstri::kNeighbours);
            lw(v0, s0, 0);
            sw(s1, v0, tstri::kIndex);
            lw(v0, s0, 0);
            sw(zero, v0, tstri::kWord20);
            lw(v0, s0, 0);
            sw(zero, v0, tstri::kWord16);
            lw(v0, s0, 0);
            sw(zero, v0, tstri::kWord24);
            lw(a0, s5, 4);
            lhu(a2, s3, 0);
            lhu(a3, s3, 2);
            t1 = s2;
            jal(ctx, 0x496DD4u, gen::fn_sub_496AD0_00496ad0);
            lw(v1, s0, 0);
            a1 = s4;
            t0 = s1;
            sw(v0, v1, 4);
            lw(a0, s5, 4);
            lhu(a2, s3, 2);
            lhu(a3, s3, 4);
            t1 = s2;
            jal(ctx, 0x496DF8u, gen::fn_sub_496AD0_00496ad0);
            lw(v1, s0, 0);
            a1 = s4;
            t0 = s1;
            sw(v0, v1, 8);
            lw(a0, s5, 4);
            lhu(a2, s3, 4);
            lhu(a3, s3, 0);
            t1 = s2;
            jal(ctx, 0x496E1Cu, gen::fn_sub_496AD0_00496ad0);
            lw(a0, s0, 0);
            s1 = addiu(s1, 1);
            v1 = sltu(s1, s6);
            s3 = addiu(s3, 20);
            sw(v0, a0, 12);
            s0 = addiu(s0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00496e40
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x00496d6c
    charge(ctx, 2);
    v0 = s2;
    // 0x00496e48
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_498E40 [getWordPair] -- stores the pointer word 0x77DDA0 into *$a0 and the word 0x77DDA4 into *$a1 (each when non-null); 1
// 0x00498E40 sub_498E40 -- 48 bytes; leaf frame (no stack)
void sub_498E40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00498e40
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x00498e48
        charge(ctx, 3);
        v0 = 0x780000;
        lw(v0, v0, -8800);  // 0x77DDA0 (a pointer word (sub_498E40's first result))
        sw(v0, a0, 0);
    }
    // 0x00498e54
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x00498e5c
        charge(ctx, 3);
        v0 = 0x780000;
        lw(v0, v0, -8796);  // 0x77DDA4 (a word (sub_498E40's second result))
        sw(v0, a1, 0);
    }
    // 0x00498e68 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 1;
}


// sub_499720 [bspTeardown] -- walks a BSP tree and unhooks each world sector: its resource entry (sub_4C47E0), atomic and light ties, its plugin data
// A sector (type -1): the resource entry at +52 freed, the ties of its atomics (+56) and lights (+64) released
// (sub_49AF20 / sub_49AEB0), its plugin data de-initialised on the world-sector registry 0x77DDB0 (sub_4C6560), its
// +120 mesh header destroyed (sub_495C80); a plane recurses into both children; type -2 is skipped.
// 0x00499720 sub_499720 -- 292 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_499720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499720
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = si(-2);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 0);
    if (a0 != v1) {
        // 0x00499748
        charge(ctx, 3);
        v1 = si(-1);
        if (a0 != v1) {
            // 0x00499754
            charge(ctx, 2);
            lw(a0, s0, bsp::kLeft);
            // 0x004997a8
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x004997b0
                charge(ctx, 2);
                jal(ctx, 0x4997B0u, gen::fn_sub_499720_00499720);
            }
            // 0x004997b8
            charge(ctx, 3);
            lw(a0, s0, bsp::kRight);
            if (a0 == 0) {
                goto L_0049982c;
            }
            // 0x004997c4
            charge(ctx, 2);
            jal(ctx, 0x4997C4u, gen::fn_sub_499720_00499720);
            goto L_004997cc;
        }
        // 0x0049975c
        charge(ctx, 3);
        lw(a0, s0, 52);
        if (a0 != 0) {
            // 0x00499768
            charge(ctx, 2);
            jal(ctx, 0x499768u, gen::fn_sub_4C47E0_004c47e0);
        }
        // 0x00499770
        charge(ctx, 4);
        lw(s2, s0, sector::kAtomicTies);
        s1 = addiu(s0, 56);
        if (s2 == s1) {
            // 0x004997d4
            charge(ctx, 1);
            lw(s2, s0, sector::kLightTies);
        } else {
            for (;;) {
                // 0x00499780
                charge(ctx, 7);
                a0 = s2;
                link(ctx, 0x499784u);  // $ra first: the delay slot below depends on it
                lw(s2, s2, 0);
                call(ctx, gen::fn_sub_49AF20_0049af20);
                if (s2 == s1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049979c
            charge(ctx, 2);
            lw(s2, s0, sector::kLightTies);
        }
        // 0x004997d8
        charge(ctx, 3);
        s1 = addiu(s0, 64);
        if (s2 != s1) {
            for (;;) {
                // 0x004997e4
                charge(ctx, 7);
                a0 = s2;
                link(ctx, 0x4997E8u);  // $ra first: the delay slot below depends on it
                lw(s2, s2, 0);
                call(ctx, gen::fn_sub_49AEB0_0049aeb0);
                if (s2 == s1) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00499800
        charge(ctx, 7);
        a0 = 0x780000;
        a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry)
        a1 = s0;
        jal(ctx, 0x499808u, gen::fn_sub_4C6560_004c6560);
        lw(a0, s0, sector::kMesh);
        if (a0 == 0) {
            goto L_0049982c;
        }
        // 0x0049981c
        charge(ctx, 4);
        jal(ctx, 0x49981Cu, gen::fn_sub_495C80_00495c80);
        sw(zero, s0, sector::kMesh);
        backedge(ctx);
    L_004997cc:
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        // 0x00499830 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_0049982c:
    charge(ctx, 1);
    ld(ra, sp, 0x30);
    // 0x00499830 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_499850 [bspDestroy] -- destroys a BSP tree: as sub_499720 and every sector array / plane freed (RwFree)
// A sector also frees its +8 / +12 / +48 / +4 arrays and the eight words from +16, then itself; a plane frees its
// children first; type -2 is freed at once.
// 0x00499850 sub_499850 -- 556 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_499850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499850
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = si(-2);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 0);
    if (v1 == v0) {
        // 0x004998d8
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4998E0u, v0.u());
    } else {
        // 0x00499878
        charge(ctx, 3);
        v0 = si(-1);
        if (v1 == v0) {
            // 0x0049988c
            charge(ctx, 4);
            s0 = a0;
            lw(a0, a0, 52);
            if (a0 != 0) {
                // 0x0049989c
                charge(ctx, 2);
                jal(ctx, 0x49989Cu, gen::fn_sub_4C47E0_004c47e0);
            }
            // 0x004998a4
            charge(ctx, 4);
            lw(s2, s0, sector::kAtomicTies);
            s1 = addiu(s0, 56);
            if (s2 == s1) {
                // 0x00499938
                charge(ctx, 1);
                lw(s2, s0, sector::kLightTies);
            } else {
                for (;;) {
                    // 0x004998b4
                    charge(ctx, 7);
                    a0 = s2;
                    link(ctx, 0x4998B8u);  // $ra first: the delay slot below depends on it
                    lw(s2, s2, 0);
                    call(ctx, gen::fn_sub_49AF20_0049af20);
                    if (s2 == s1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004998d0
                charge(ctx, 2);
                lw(s2, s0, sector::kLightTies);
            }
            // 0x0049993c
            charge(ctx, 3);
            s1 = addiu(s0, 64);
            if (s2 != s1) {
                for (;;) {
                    // 0x00499948
                    charge(ctx, 7);
                    a0 = s2;
                    link(ctx, 0x49994Cu);  // $ra first: the delay slot below depends on it
                    lw(s2, s2, 0);
                    call(ctx, gen::fn_sub_49AEB0_0049aeb0);
                    if (s2 == s1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00499964
                charge(ctx, 1);
            }
            // 0x00499968
            charge(ctx, 7);
            a0 = 0x780000;
            a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry)
            a1 = s0;
            jal(ctx, 0x499970u, gen::fn_sub_4C6560_004c6560);
            lw(a0, s0, 8);
            if (a0 != 0) {
                // 0x00499984
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x49998Cu, v0.u());
                sw(zero, s0, 8);
            }
            // 0x00499998
            charge(ctx, 3);
            lw(a0, s0, 12);
            if (a0 != 0) {
                // 0x004999a4
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4999ACu, v0.u());
                sw(zero, s0, 12);
            }
            // 0x004999b8
            charge(ctx, 3);
            lw(a0, s0, 48);
            if (a0 != 0) {
                // 0x004999c4
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4999CCu, v0.u());
                sw(zero, s0, 48);
            }
            // 0x004999d8
            charge(ctx, 3);
            lw(a0, s0, 4);
            if (a0 != 0) {
                // 0x004999e4
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4999ECu, v0.u());
                sw(zero, s0, 4);
            }
            // 0x004999f8
            charge(ctx, 4);
            s1 = 0x960000;
            s3 = 0;
            s2 = s0;
            s1 = addiu(s1, 380);  // &0x96017C (RwFree slot)
            for (;;) {
                // 0x00499a08
                charge(ctx, 3);
                lw(a0, s2, 16);
                if (a0 != 0) {
                    // 0x00499a14
                    charge(ctx, 5);
                    lw(v0, s1, 0);
                    jalr(ctx, 0x499A18u, v0.u());
                    sw(zero, s2, 16);
                }
                // 0x00499a28
                charge(ctx, 4);
                s3 = addiu(s3, 1);
                v0 = slti(s3, 8);
                s2 = addiu(s2, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00499a38
            charge(ctx, 3);
            lw(a0, s0, sector::kMesh);
            if (a0 != 0) {
                // 0x00499a44
                charge(ctx, 3);
                jal(ctx, 0x499A44u, gen::fn_sub_495C80_00495c80);
                sw(zero, s0, sector::kMesh);
            }
            // 0x00499a50
            charge(ctx, 5);
            lw(v0, s1, 0);
            a0 = s0;
            jalr(ctx, 0x499A54u, v0.u());
            backedge(ctx);
        } else {
            // 0x00499884
            charge(ctx, 2);
            s0 = a0;
            // 0x004998f0
            charge(ctx, 3);
            lw(a0, a0, 8);
            if (a0 != 0) {
                // 0x004998fc
                charge(ctx, 2);
                jal(ctx, 0x4998FCu, gen::fn_sub_499850_00499850);
            }
            // 0x00499904
            charge(ctx, 4);
            sw(zero, s0, 8);
            lw(a0, s0, 12);
            if (a0 != 0) {
                // 0x00499914
                charge(ctx, 2);
                jal(ctx, 0x499914u, gen::fn_sub_499850_00499850);
            }
            // 0x0049991c
            charge(ctx, 5);
            sw(zero, s0, 12);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s0;
            jalr(ctx, 0x499928u, v0.u());
        }
    }
    // 0x00499930
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x00499a64
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_49A980 [worldPluginAttach] -- registers the world module's plugins (0x501..0x50B): the engine data, the sector / world / geometry plugins, then sub_49BE50, sub_4915C0, sub_4A5100
// 1 when every registration and the three follow-ups succeed, else 0.
// 0x0049A980 sub_49A980 -- 364 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49A980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049a980
    enter(ctx, 70);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0x490000;
    sd(ra, sp, 0x10);
    a3 = 0x490000;
    sq(s0, sp, 0x0);
    a0 = 4;
    a1 = 1281;
    a2 = addiu(a2, 19168);  // &sub_494AE0
    a3 = addiu(a3, 19312);  // &sub_494B70
    s0 = 0;
    jal(ctx, 0x49A9A4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 48;
    a1 = 1282;
    a2 = addiu(a2, 23088);  // &sub_495A30
    a3 = addiu(a3, 23008);  // &sub_4959E0
    jal(ctx, 0x49A9C4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 4;
    a1 = 1283;
    a2 = addiu(a2, 11744);  // &sub_492DE0
    a3 = addiu(a3, 11776);  // &sub_492E00
    jal(ctx, 0x49A9E4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 8;
    a1 = 1284;
    a2 = addiu(a2, 5328);  // &sub_4914D0
    a3 = addiu(a3, 5136);  // &sub_491410
    jal(ctx, 0x49AA04u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 4;
    a1 = 1285;
    a2 = addiu(a2, 18736);  // &sub_494930
    a3 = addiu(a3, 18608);  // &sub_4948B0
    jal(ctx, 0x49AA24u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    s0 = s0 | v0;
    a0 = 0;
    a1 = 1290;
    a2 = addiu(a2, -28176);  // &sub_4991F0
    a3 = addiu(a3, -28144);  // &sub_499210
    jal(ctx, 0x49AA44u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    s0 = s0 | v0;
    a0 = 12;
    a1 = 1287;
    a2 = addiu(a2, -25872);  // &sub_499AF0
    a3 = addiu(a3, -25984);  // &sub_499A80
    jal(ctx, 0x49AA64u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 0;
    a1 = 1291;
    a2 = addiu(a2, 1712);  // &sub_4906B0
    a3 = addiu(a3, 1680);  // &sub_490690
    jal(ctx, 0x49AA84u, gen::fn_sub_4CA520_004ca520);
    v0 = s0 | v0;
    if (i64(v0) >= 0) {
        // 0x0049aaa0
        charge(ctx, 4);
        jal(ctx, 0x49AAA0u, gen::fn_sub_49BE50_0049be50);
        if (v0 != 0) {
            // 0x0049aab8
            charge(ctx, 4);
            jal(ctx, 0x49AAB8u, gen::fn_sub_4915C0_004915c0);
            if (v0 != 0) {
                // 0x0049aad0
                charge(ctx, 3);
                jal(ctx, 0x49AAD0u, gen::fn_sub_4A5100_004a5100);
                v0 = sltu(0, v0);
            } else {
                // 0x0049aac8
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0049aab0
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0049aa98
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0049aadc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49BC50 [geometryBinMeshWrite] -- the geometry's bin-mesh stream write: its mesh header (+84) through sub_495FB0 (the material list at +32)
// 0x0049BC50 sub_49BC50 -- 24 bytes; leaf frame (no stack)
void sub_49BC50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0049bc50
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = a0;
    a1 = a2;
    lw(a0, a2, geoext::kMeshHeader);
    a3 = addiu(a1, 32);
    a2 = v0;
    gen::fn_sub_495FB0_00495fb0(ctx);  // tail call
}


// sub_49BC70 [geometryBinMeshRead] -- the geometry's bin-mesh stream read: the mesh header (sub_496230) into +84; the stream, or 0
// 0x0049BC70 sub_49BC70 -- 72 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49BC70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bc70
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a1 = s0;
    a2 = addiu(s0, 32);
    jal(ctx, 0x49BC8Cu, gen::fn_sub_496230_00496230);
    sw(v0, s0, geoext::kMeshHeader);
    lw(v0, s0, geoext::kMeshHeader);
    if (v0 == 0) s1 = 0;
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49BCC0 [geometryBinMeshSize] -- the geometry's bin-mesh stream size (sub_4964F0 on +84)
// 0x0049BCC0 sub_49BCC0 -- 12 bytes; leaf frame (no stack)
void sub_49BCC0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0049bcc0
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = a0;
    lw(a0, a0, geoext::kMeshHeader);
    gen::fn_sub_4964F0_004964f0(ctx);  // tail call
}


// sub_49BD10 [geometryNativeSizeThunk] -- the geometry's native-data stream size: a tail call to sub_49ECD0
// 0x0049BD10 sub_49BD10 -- 8 bytes; leaf frame (no stack)
void sub_49BD10(EEContext& ctx) {
    using namespace hg;
    // 0x0049bd10
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_49ECD0_0049ecd0(ctx);  // tail call
}


// sub_49BD60 [sectorNativeSizeThunk] -- the world sector's native-data stream size: a tail call to sub_49F340
// 0x0049BD60 sub_49BD60 -- 8 bytes; leaf frame (no stack)
void sub_49BD60(EEContext& ctx) {
    using namespace hg;
    // 0x0049bd60
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_49F340_0049f340(ctx);  // tail call
}


// sub_49BD70 [sectorBinMeshWrite] -- the world sector's bin-mesh stream write: its mesh header (+120) with its world (worldSectorGetWorld) and the world's materials
// 0x0049BD70 sub_49BD70 -- 72 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49BD70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bd70
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a0 = s0;
    jal(ctx, 0x49BD88u, gen::fn_worldSectorGetWorld_0049a170);
    lw(a0, s0, sector::kMesh);
    a2 = s1;
    a1 = v0;
    a3 = addiu(v0, 16);
    jal(ctx, 0x49BD9Cu, gen::fn_sub_495FB0_00495fb0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49BDC0 [sectorBinMeshRead] -- the world sector's bin-mesh stream read: the mesh header into +120; the stream, or 0
// 0x0049BDC0 sub_49BDC0 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49BDC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049bdc0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a0 = s0;
    jal(ctx, 0x49BDD8u, gen::fn_worldSectorGetWorld_0049a170);
    a0 = s1;
    a1 = v0;
    a2 = addiu(v0, 16);
    jal(ctx, 0x49BDE8u, gen::fn_sub_496230_00496230);
    sw(v0, s0, sector::kMesh);
    lw(v0, s0, sector::kMesh);
    if (v0 == 0) s1 = 0;
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49BE20 [sectorBinMeshSize] -- the world sector's bin-mesh stream size (sub_4964F0 on +120 with its world)
// 0x0049BE20 sub_49BE20 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BE20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049be20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x49BE2Cu, gen::fn_worldSectorGetWorld_0049a170);
    lw(a0, s0, sector::kMesh);
    a1 = v0;
    jal(ctx, 0x49BE38u, gen::fn_sub_4964F0_004964f0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49BE50 [worldRegisterPlugins] -- the world module's plugin set: the 0x509 extensions of worlds / sectors / atomics / clumps / lights, the bin-mesh (0x50E) and native-data (0x510) streams, the pipeline-id streams (0x1F)
// The extension offsets go to gp 0x7CE868..0x7CE874; then sub_49C790. 1 when everything registered.
// 0x0049BE50 sub_49BE50 -- 776 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49BE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049be50
    enter(ctx, 185);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    sd(ra, sp, 0x10);
    a0 = 12;
    a1 = 1289;
    a2 = addiu(a2, -21776);  // &sub_49AAF0
    a3 = addiu(a3, -21520);  // &sub_49ABF0
    link(ctx, 0x49BE70u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    t0 = 0x4A0000;
    s0 = v0;
    a0 = 28;
    a1 = 1289;
    a2 = addiu(a2, -21120);  // &sub_49AD80
    a3 = addiu(a3, -20944);  // &sub_49AE30
    t0 = addiu(t0, -21024);  // &sub_49ADE0
    jal(ctx, 0x49BE98u, gen::fn_sub_4CA000_004ca000);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    t0 = 0x4A0000;
    s0 = s0 | v0;
    sw(v0, gp, -17544);  // 0x7CE868 (the world plugin's 28-byte sector extension offset)
    a0 = 8;
    a1 = 1289;
    a2 = addiu(a2, -19824);  // &sub_49B290
    a3 = addiu(a3, -19744);  // &sub_49B2E0
    t0 = addiu(t0, -19760);  // &sub_49B2D0
    jal(ctx, 0x49BEC4u, gen::fn_sub_492C30_00492c30);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    t0 = 0x4A0000;
    s0 = s0 | v0;
    sw(v0, gp, -17540);  // 0x7CE86C
    a0 = 8;
    a1 = 1289;
    a2 = addiu(a2, -19520);  // &sub_49B3C0
    a3 = addiu(a3, -19408);  // &sub_49B430
    t0 = addiu(t0, -19472);  // &sub_49B3F0
    jal(ctx, 0x49BEF0u, gen::fn_sub_492C60_00492c60);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    t0 = 0x4A0000;
    s0 = s0 | v0;
    sw(v0, gp, -17536);  // 0x7CE870
    a0 = 8;
    a1 = 1289;
    a2 = addiu(a2, -18640);  // &sub_49B730
    a3 = addiu(a3, -18528);  // &sub_49B7A0
    t0 = addiu(t0, -18592);  // &sub_49B760
    jal(ctx, 0x49BF1Cu, gen::fn_sub_494520_00494520);
    s0 = s0 | v0;
    sw(v0, gp, -17532);  // 0x7CE874
    a0 = 0;
    a1 = 1294;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49BF3Cu, gen::fn_sub_493C50_00493c50);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 1294;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49BF58u, gen::fn_sub_499250_00499250);
    a1 = 0x4A0000;
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    s0 = s0 | v0;
    a0 = 1294;
    a1 = addiu(a1, -17296);  // &sub_49BC70
    a2 = addiu(a2, -17328);  // &sub_49BC50
    a3 = addiu(a3, -17216);  // &sub_49BCC0
    jal(ctx, 0x49BF7Cu, gen::fn_sub_493C80_00493c80);
    a1 = 0x4A0000;
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    s0 = s0 | v0;
    a0 = 1294;
    a1 = addiu(a1, -16960);  // &sub_49BDC0
    a2 = addiu(a2, -17040);  // &sub_49BD70
    a3 = addiu(a3, -16864);  // &sub_49BE20
    jal(ctx, 0x49BFA0u, gen::fn_sub_499280_00499280);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 1296;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49BFBCu, gen::fn_sub_493C50_00493c50);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 1296;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49BFD8u, gen::fn_sub_499250_00499250);
    a1 = 0x4A0000;
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    s0 = s0 | v0;
    a0 = 1296;
    a1 = addiu(a1, -17184);  // &sub_49BCE0
    a2 = addiu(a2, -17200);  // &sub_49BCD0
    a3 = addiu(a3, -17136);  // &sub_49BD10
    jal(ctx, 0x49BFFCu, gen::fn_sub_493C80_00493c80);
    a1 = 0x4A0000;
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    s0 = s0 | v0;
    a0 = 1296;
    a1 = addiu(a1, -17104);  // &sub_49BD30
    a2 = addiu(a2, -17120);  // &sub_49BD20
    a3 = addiu(a3, -17056);  // &sub_49BD60
    jal(ctx, 0x49C020u, gen::fn_sub_499280_00499280);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 31;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49C03Cu, gen::fn_sub_492C30_00492c30);
    a1 = 0x490000;
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 31;
    a1 = addiu(a1, 1776);  // &sub_4906F0
    a2 = addiu(a2, 1904);  // &sub_490770
    a3 = addiu(a3, 2016);  // &sub_4907E0
    jal(ctx, 0x49C060u, gen::fn_sub_492C90_00492c90);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 31;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49C07Cu, gen::fn_sub_49A920_0049a920);
    a1 = 0x490000;
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 31;
    a1 = addiu(a1, -3264);  // &sub_48F340
    a2 = addiu(a2, -3136);  // &sub_48F3C0
    a3 = addiu(a3, -3024);  // &sub_48F430
    jal(ctx, 0x49C0A0u, gen::fn_sub_49A950_0049a950);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 31;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49C0BCu, gen::fn_sub_499250_00499250);
    a1 = 0x490000;
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 31;
    a1 = addiu(a1, -2976);  // &sub_48F460
    a2 = addiu(a2, -2848);  // &sub_48F4E0
    a3 = addiu(a3, -2736);  // &sub_48F550
    jal(ctx, 0x49C0E0u, gen::fn_sub_499280_00499280);
    s0 = s0 | v0;
    a0 = 0;
    a1 = 31;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x49C0FCu, gen::fn_sub_494DB0_00494db0);
    a1 = 0x490000;
    a2 = 0x490000;
    a3 = 0x490000;
    s0 = s0 | v0;
    a0 = 31;
    a1 = addiu(a1, 18880);  // &sub_4949C0
    a2 = addiu(a2, 19008);  // &sub_494A40
    a3 = addiu(a3, 19120);  // &sub_494AB0
    jal(ctx, 0x49C120u, gen::fn_sub_494DE0_00494de0);
    v0 = s0 | v0;
    if (i64(v0) >= 0) {
        // 0x0049c13c
        charge(ctx, 3);
        jal(ctx, 0x49C13Cu, gen::fn_sub_49C790_0049c790);
        v0 = sltu(0, v0);
    } else {
        // 0x0049c134
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0049c148 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49E6C0 [nativeDataToOffsets] -- rewrites the DMA chain of native data for streaming: each ref tag's (3) address becomes a qword offset from the chain start
// Walks tags by (tag >> 28) & 7: 1 (cnt) skips its qwords, 3 (ref) converts, 0 / 6 / 7 end. 1 when no ref tag was
// met, else 0.
// 0x0049E6C0 sub_49E6C0 -- 192 bytes; leaf frame (no stack)
void sub_49E6C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0049e6c0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(a1, a0, 8);
    v1 = 0;
    v0 = 1;
    t2 = 0x7C0000;
    a3 = v0;
    t0 = v0;
    t1 = v0;
    t2 = addiu(t2, -13696);  // &0x7BCA80
    for (;;) {
        // 0x0049e6e0
        charge(ctx, 7);
        lw(a2, a1, 0);
        t3 = a2 & 0xFFFF;
        a2 = srl(a2, 28);
        a2 = a2 & 0x7;
        at = sltiu(a2, 8);
        if (at != 0) {
            // 0x0049e6fc
            charge(ctx, 5);
            a2 = sll(a2, 2);
            a2 = addu(a2, t2);
            lw(a2, a2, 0);
            switch (a2.u()) {
            case 0x49E710u:  // table[0]
                // 0x0049e710
                charge(ctx, 2);
                v1 = t1;
                break;
            case 0x49E718u:  // table[1]
                // 0x0049e718
                charge(ctx, 4);
                a2 = addiu(t3, 1);
                a2 = sll(a2, 4);
                a1 = addu(a1, a2);
                break;
            case 0x49E728u:  // table[3]
                // 0x0049e728
                charge(ctx, 5);
                lw(a2, a1, 4);
                lw(v0, a0, 8);
                a2 = subu(a2, v0);
                v0 = sra(a2, 4);
                if (i64(a2) < 0) {
                    // 0x0049e73c
                    charge(ctx, 2);
                    v0 = addiu(a2, 15);
                    v0 = sra(v0, 4);
                }
                // 0x0049e744
                charge(ctx, 4);
                sw(v0, a1, 4);
                v0 = 0;
                a1 = addiu(a1, 16);
                break;
            case 0x49E758u:  // table[6]
                // 0x0049e758
                charge(ctx, 2);
                v1 = t0;
                break;
            case 0x49E760u:  // table[7]
                // 0x0049e760
                charge(ctx, 2);
                v1 = a3;
                break;
            case 0x49E768u:  // table[2, 4, 5]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, a2.u());
                return;
            }
        }
        // 0x0049e768
        charge(ctx, 4);
        a2 = sltu(0, v1);
        a2 = a2 ^ 0x1;
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0049e778
    charge(ctx, 2);
}


// sub_49E780 [nativeDataToAddresses] -- the inverse of sub_49E6C0 after reading: each ref tag's qword offset becomes an address again; 1 when none was met, else 0
// 0x0049E780 sub_49E780 -- 176 bytes; leaf frame (no stack)
void sub_49E780(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0049e780
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(a1, a0, 8);
    v1 = 0;
    v0 = 1;
    t3 = 0x7C0000;
    a3 = v0;
    t0 = v0;
    t2 = v0;
    t3 = addiu(t3, -13664);  // &0x7BCAA0
    for (;;) {
        // 0x0049e7a0
        charge(ctx, 7);
        lw(a2, a1, 0);
        t1 = a2 & 0xFFFF;
        a2 = srl(a2, 28);
        a2 = a2 & 0x7;
        at = sltiu(a2, 8);
        if (at != 0) {
            // 0x0049e7bc
            charge(ctx, 5);
            a2 = sll(a2, 2);
            a2 = addu(a2, t3);
            lw(a2, a2, 0);
            switch (a2.u()) {
            case 0x49E7D0u:  // table[0]
                // 0x0049e7d0
                charge(ctx, 2);
                v1 = t2;
                break;
            case 0x49E7D8u:  // table[1]
                // 0x0049e7d8
                charge(ctx, 4);
                a2 = addiu(t1, 1);
                a2 = sll(a2, 4);
                a1 = addu(a1, a2);
                break;
            case 0x49E7E8u:  // table[3]
                // 0x0049e7e8
                charge(ctx, 8);
                lw(t1, a1, 4);
                lw(a2, a0, 8);
                v0 = 0;
                t1 = sll(t1, 4);
                a2 = addu(a2, t1);
                sw(a2, a1, 4);
                a1 = addiu(a1, 16);
                break;
            case 0x49E808u:  // table[6]
                // 0x0049e808
                charge(ctx, 2);
                v1 = t0;
                break;
            case 0x49E810u:  // table[7]
                // 0x0049e810
                charge(ctx, 2);
                v1 = a3;
                break;
            case 0x49E818u:  // table[2, 4, 5]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, a2.u());
                return;
            }
        }
        // 0x0049e818
        charge(ctx, 4);
        a2 = sltu(0, v1);
        a2 = a2 ^ 0x1;
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0049e828
    charge(ctx, 2);
}


// sub_49ECD0 [geometryNativeSize] -- the geometry's native-data stream size: 16 + per DMA packet its size - the header's offset + 8; 0 without native data
// The packets of the geometry's PS2 resource (geometry + gp 0x7CE890: count, then packet pointers).
// 0x0049ECD0 sub_49ECD0 -- 412 bytes; frame 0x30: s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49ECD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29};
    // 0x0049ecd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    lw(a1, a0, 8);
    sq(s2, sp, 0x20);
    v1 = 0x1000000;
    sq(s1, sp, 0x10);
    v0 = 0;
    v1 = a1 & v1;
    sq(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x0049ecf4
        charge(ctx, 8);
        lw(v1, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
        v0 = addiu(v0, 16);
        v1 = addu(a0, v1);
        lw(a1, v1, 0);
        lw(a0, a1, 0);
        at = sltu(0, a0);
        a3 = 0;
        if (at != 0) {
            // 0x0049ed14
            charge(ctx, 3);
            at = sltiu(a0, 9);
            v1 = addiu(a0, -8);
            if (at == 0) {
                // 0x0049ed20
                charge(ctx, 1);
                a2 = a1;
                for (;;) {
                    // 0x0049ed24
                    charge(ctx, 60);
                    lw(s2, a2, 4);
                    a3 = addiu(a3, 8);
                    lw(s1, a2, 8);
                    t0 = sltu(a3, v1);
                    lw(t8, a2, 12);
                    lw(t4, a2, 16);
                    lw(t7, a2, 20);
                    lw(t3, a2, 24);
                    lw(t2, s2, 32);
                    lw(t1, s2, 8);
                    lw(s0, s1, 32);
                    lw(t9, s1, 8);
                    lw(t6, t8, 32);
                    lw(t5, t8, 8);
                    s2 = subu(t2, s2);
                    s2 = subu(t1, s2);
                    s0 = subu(s0, s1);
                    lw(t2, t4, 32);
                    s1 = addiu(s2, 8);
                    t9 = subu(t9, s0);
                    lw(t1, t4, 8);
                    s0 = addu(v0, s1);
                    v0 = subu(t6, t8);
                    t5 = subu(t5, v0);
                    t6 = addiu(t9, 8);
                    t6 = addu(s0, t6);
                    v0 = subu(t2, t4);
                    t2 = addiu(t5, 8);
                    v0 = subu(t1, v0);
                    t2 = addu(t6, t2);
                    v0 = addiu(v0, 8);
                    t8 = addu(t2, v0);
                    lw(t6, t7, 32);
                    lw(t1, t3, 32);
                    lw(t4, t7, 8);
                    lw(v0, t3, 8);
                    lw(t5, a2, 28);
                    lw(t2, a2, 32);
                    t6 = subu(t6, t7);
                    t1 = subu(t1, t3);
                    t4 = subu(t4, t6);
                    t3 = addiu(t4, 8);
                    v0 = subu(v0, t1);
                    lw(t4, t5, 32);
                    t3 = addu(t8, t3);
                    v0 = addiu(v0, 8);
                    lw(t1, t2, 32);
                    t6 = addu(t3, v0);
                    a2 = addiu(a2, 32);
                    lw(t3, t5, 8);
                    lw(v0, t2, 8);
                    t4 = subu(t4, t5);
                    t1 = subu(t1, t2);
                    t3 = subu(t3, t4);
                    t2 = addiu(t3, 8);
                    v0 = subu(v0, t1);
                    t2 = addu(t6, t2);
                    v0 = addiu(v0, 8);
                    v0 = addu(t2, v0);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049ee14
                charge(ctx, 1);
            }
            // 0x0049ee18
            charge(ctx, 3);
            at = sltu(a3, a0);
            if (at != 0) {
                // 0x0049ee24
                charge(ctx, 2);
                v1 = sll(a3, 2);
                t1 = addu(a1, v1);
                for (;;) {
                    // 0x0049ee2c
                    charge(ctx, 11);
                    lw(t0, t1, 4);
                    a3 = addiu(a3, 1);
                    v1 = sltu(a3, a0);
                    lw(a2, t0, 32);
                    t1 = addiu(t1, 4);
                    lw(a1, t0, 8);
                    a2 = subu(a2, t0);
                    a1 = subu(a1, a2);
                    a1 = addiu(a1, 8);
                    v0 = addu(v0, a1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x0049ee58 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49F340 [sectorNativeSize] -- the world sector's native-data stream size, as sub_49ECD0 for the sector's resource (gp 0x7CE888) when its world is native
// 0x0049F340 sub_49F340 -- 436 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49F340(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049f340
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    jal(ctx, 0x49F358u, gen::fn_worldSectorGetWorld_0049a170);
    lw(v1, v0, 8);
    v0 = 0x1000000;
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x0049f374
        charge(ctx, 8);
        lw(v0, gp, -17512);  // 0x7CE888 (the PS2 pipeline-id extension offset of world sectors)
        s0 = addiu(s0, 16);
        v0 = addu(s1, v0);
        lw(a0, v0, 0);
        lw(v1, a0, 0);
        at = sltu(0, v1);
        a2 = 0;
        if (at != 0) {
            // 0x0049f394
            charge(ctx, 3);
            at = sltiu(v1, 9);
            v0 = addiu(v1, -8);
            if (at == 0) {
                // 0x0049f3a0
                charge(ctx, 1);
                a1 = a0;
                for (;;) {
                    // 0x0049f3a4
                    charge(ctx, 60);
                    lw(s2, a1, 4);
                    a2 = addiu(a2, 8);
                    lw(t9, a1, 8);
                    a3 = sltu(a2, v0);
                    lw(t6, a1, 12);
                    lw(t2, a1, 16);
                    lw(t7, a1, 20);
                    lw(t3, a1, 24);
                    lw(t1, s2, 32);
                    lw(t0, s2, 8);
                    lw(t8, t9, 32);
                    lw(t5, t6, 32);
                    lw(s1, t9, 8);
                    lw(t4, t6, 8);
                    s2 = subu(t1, s2);
                    lw(t1, t2, 32);
                    s2 = subu(t0, s2);
                    lw(t0, t2, 8);
                    t8 = subu(t8, t9);
                    t9 = addiu(s2, 8);
                    t5 = subu(t5, t6);
                    s1 = subu(s1, t8);
                    t4 = subu(t4, t5);
                    s0 = addu(s0, t9);
                    t6 = addiu(s1, 8);
                    t6 = addu(s0, t6);
                    lw(t5, a1, 28);
                    t1 = subu(t1, t2);
                    t2 = addiu(t4, 8);
                    t0 = subu(t0, t1);
                    t2 = addu(t6, t2);
                    t0 = addiu(t0, 8);
                    s0 = addu(t2, t0);
                    lw(t6, t7, 32);
                    lw(t1, t3, 32);
                    lw(t4, t7, 8);
                    lw(t0, t3, 8);
                    lw(t2, a1, 32);
                    t6 = subu(t6, t7);
                    t1 = subu(t1, t3);
                    t4 = subu(t4, t6);
                    t3 = addiu(t4, 8);
                    t0 = subu(t0, t1);
                    lw(t4, t5, 32);
                    t3 = addu(s0, t3);
                    t0 = addiu(t0, 8);
                    lw(t1, t2, 32);
                    t6 = addu(t3, t0);
                    a1 = addiu(a1, 32);
                    lw(t3, t5, 8);
                    lw(t0, t2, 8);
                    t4 = subu(t4, t5);
                    t1 = subu(t1, t2);
                    t3 = subu(t3, t4);
                    t2 = addiu(t3, 8);
                    t0 = subu(t0, t1);
                    t2 = addu(t6, t2);
                    t0 = addiu(t0, 8);
                    s0 = addu(t2, t0);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049f494
                charge(ctx, 1);
            }
            // 0x0049f498
            charge(ctx, 3);
            at = sltu(a2, v1);
            if (at != 0) {
                // 0x0049f4a4
                charge(ctx, 2);
                v0 = sll(a2, 2);
                t0 = addu(a0, v0);
                for (;;) {
                    // 0x0049f4ac
                    charge(ctx, 11);
                    lw(a3, t0, 4);
                    a2 = addiu(a2, 1);
                    v0 = sltu(a2, v1);
                    lw(a1, a3, 32);
                    t0 = addiu(t0, 4);
                    lw(a0, a3, 8);
                    a1 = subu(a1, a3);
                    a0 = subu(a0, a1);
                    a0 = addiu(a0, 8);
                    s0 = addu(s0, a0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x0049f4d8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_49F500 [ps2AllNodeInitData] -- a PS2All node's private-data init: the 976-byte packet area with its 16-aligned GIF tag, the stride / field bytes
// ($a0 = the node; its private data at +20) Writes the 128-bit tag with sq (pcpyld), the format bytes +1..+13; 1.
// 0x0049F500 sub_49F500 -- 204 bytes; leaf frame (no stack)
void sub_49F500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x0049f500
    enter(ctx, 51);  // entry check point + this block's cycles
    lw(v1, a0, 20);
    v0 = 0x1000000;
    t0 = v0 | 0x404;  // &0x1000404
    t4 = 976;
    t3 = 32;
    a3 = si(-16);
    t1 = 0x6C010000;
    v0 = 1;
    a2 = 2;
    a1 = 3;
    sw(zero, v1, 24);
    t2 = addiu(v1, 40);
    sw(t4, v1, 28);
    t2 = addiu(t2, 15);
    a3 = t2 & a3;
    sw(t3, v1, 32);
    sw(a3, v1, 36);
    a0 = 0;
    lw(a3, v1, 36);
    sw(zero, a3, 16);
    lw(a3, v1, 36);
    sw(zero, a3, 20);
    lw(a3, v1, 36);
    sw(zero, a3, 24);
    lw(a3, v1, 36);
    sw(zero, a3, 28);
    lw(t2, v1, 28);
    lw(a3, v1, 36);
    t2 = addiu(t2, 4);
    t2 = dsll32(t2, 0);
    t2 = dsrl32(t2, 0);
    t1 = t2 | t1;
    t1 = dsll32(t1, 0);
    t0 = t1 | t0;
    pcpyld(a0, t0, a0);
    sq(a0, a3, 0);
    sw(zero, v1, 16);
    sw(zero, v1, 20);
    sb(v0, v1, 1);
    sb(a2, v1, 2);
    sb(v0, v1, 3);
    sb(v0, v1, 4);
    sb(a1, v1, 5);
    sb(v0, v1, 6);
    sb(zero, v1, 8);
    sb(v0, v1, 9);
    sb(zero, v1, 10);
    sb(a2, v1, 11);
    sb(a2, v1, 12);
    sb(zero, v1, 13);
}


// sub_49FE40 [ps2AllNodeSetCallBack] -- sets a PS2All node's callback: type 1 (non-null) at private data +16, type 2 at +20; the node, or 0
// 0 without a node or private data, for type 1 with a null callback, or for another type.
// 0x0049FE40 sub_49FE40 -- 120 bytes; leaf frame (no stack)
void sub_49FE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0049fe40
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x0049fe9c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049fe48
        charge(ctx, 3);
        lw(v1, a0, 20);
        if (v1 == 0) {
            // 0x0049fea4
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x0049fe54
            charge(ctx, 3);
            v0 = 2;
            if (a1 == v0) {
                // 0x0049fe88
                charge(ctx, 3);
                sw(a2, v1, 20);
                v0 = a0;
            } else {
                // 0x0049fe60
                charge(ctx, 3);
                v0 = 1;
                if (a1 == v0) {
                    // 0x0049fe74
                    charge(ctx, 2);
                    if (a2 == 0) {
                        // 0x0049feac
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0049fe7c
                        charge(ctx, 3);
                        sw(a2, v1, 16);
                        v0 = a0;
                    }
                } else {
                    // 0x0049fe6c
                    charge(ctx, 2);
                    v0 = 0;
                    // 0x0049fe94
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0049feb0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sceLibgcc32GetErxEntries -- returns 0x77DE80: the PS2All node definition the PDS pipe builders add (the symbol name is not its role)
// 0x0049FF00 sceLibgcc32GetErxEntries -- 12 bytes; leaf frame (no stack)
void sceLibgcc32GetErxEntries(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0049ff00
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    v0 = addiu(v0, -8576);  // &0x77DE80 (the PS2All node definition)
}


// sub_4A5470 [Rt2dBrushCreate] -- creates a brush: a cleared 120-byte record from the brush free list, white (four 255 colours), zero UVs, no texture, 0.5 at +112, one reference
// 0x004A5470 sub_4A5470 -- 204 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A5470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5470
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, v0, -4768);  // 0x95ED60
    v0 = 0x30000;
    a1 = v0 | 0x1A2;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    jalr(ctx, 0x4A5494u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004a5528
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004a54a8
        charge(ctx, 32);
        a0 = s0;
        a1 = 0;
        a2 = 120;
        jal(ctx, 0x4A54B0u, gen::fn_memset_00521408);
        v0 = 255;
        a1 = addiu(sp, 0x2C);
        a0 = s0;
        sb(v0, sp, 0x2C);
        sb(v0, sp, 0x2D);
        a2 = a1;
        sb(v0, sp, 0x2E);
        a3 = a1;
        sb(v0, sp, 0x2F);
        t0 = a1;
        jal(ctx, 0x4A54DCu, gen::fn_sub_4A5DD0_004a5dd0);
        a1 = addiu(sp, 0x20);
        a0 = s0;
        a2 = a1;
        a3 = a1;
        t0 = a1;
        sw(zero, sp, 0x20);
        link(ctx, 0x4A54FCu);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x24);
        call(ctx, gen::fn_sub_4A6200_004a6200);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x4A5508u, gen::fn_sub_4A62E0_004a62e0);
        v0 = 0x3F000000;
        v1 = 1;
        sw(v0, s0, brush2d::kHalfWidth);
        v0 = s0;
        sw(v1, s0, brush2d::kRefCount);
    }
    // 0x004a552c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4A5DD0 [Rt2dBrushSetRGBA] -- sets a brush's four colours: the byte RGBA of $t0 / $a3 / $a1 / $a2 as floats, the second of each edge as a delta, the first packed at +96
// +0 = $t0, +24 = $a3 - $t0, +48 = $a1, +72 = $a2 - $a1 (each four floats); the brush.
// 0x004A5DD0 sub_4A5DD0 -- 1072 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A5DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004a5dd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, t0, 0);
    s0 = a0;
    if (i64(v0) < 0) {
        // 0x004a5df4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5de8
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5e10
    charge(ctx, 4);
    swc1(f0, s0, brush2d::kRgba0);
    lbu(v0, t0, 1);
    if (i64(v0) < 0) {
        // 0x004a5e2c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5e20
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5e48
    charge(ctx, 4);
    swc1(f0, s0, 4);
    lbu(v0, t0, 2);
    if (i64(v0) < 0) {
        // 0x004a5e64
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5e58
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5e80
    charge(ctx, 4);
    swc1(f0, s0, 8);
    lbu(v0, t0, 3);
    if (i64(v0) < 0) {
        // 0x004a5e9c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5e90
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5eb8
    charge(ctx, 4);
    swc1(f0, s0, 12);
    lbu(v0, a3, 0);
    if (i64(v0) < 0) {
        // 0x004a5ed4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5ec8
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5ef0
    charge(ctx, 4);
    swc1(f0, s0, brush2d::kRgbaDelta0);
    lbu(v0, a3, 1);
    if (i64(v0) < 0) {
        // 0x004a5f0c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5f00
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5f28
    charge(ctx, 4);
    swc1(f0, s0, 28);
    lbu(v0, a3, 2);
    if (i64(v0) < 0) {
        // 0x004a5f44
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5f38
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5f60
    charge(ctx, 4);
    swc1(f0, s0, 32);
    lbu(v0, a3, 3);
    if (i64(v0) < 0) {
        // 0x004a5f7c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5f70
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a5f98
    charge(ctx, 20);
    swc1(f0, s0, 36);
    lwc1(f1, s0, brush2d::kRgbaDelta0);
    lwc1(f0, s0, brush2d::kRgba0);
    sub_s(f0, f1, f0);
    swc1(f0, s0, brush2d::kRgbaDelta0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 28);
    sub_s(f0, f0, f1);
    swc1(f0, s0, 28);
    lwc1(f1, s0, 8);
    lwc1(f0, s0, 32);
    sub_s(f0, f0, f1);
    swc1(f0, s0, 32);
    lwc1(f1, s0, 12);
    lwc1(f0, s0, 36);
    sub_s(f0, f0, f1);
    swc1(f0, s0, 36);
    lbu(v0, a1, 0);
    if (i64(v0) < 0) {
        // 0x004a5ff4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a5fe8
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a6010
    charge(ctx, 4);
    swc1(f0, s0, brush2d::kRgba1);
    lbu(v0, a1, 1);
    if (i64(v0) < 0) {
        // 0x004a602c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a6020
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a6048
    charge(ctx, 4);
    swc1(f0, s0, 52);
    lbu(v0, a1, 2);
    if (i64(v0) < 0) {
        // 0x004a6064
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a6058
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a6080
    charge(ctx, 4);
    swc1(f0, s0, 56);
    lbu(v0, a1, 3);
    if (i64(v0) < 0) {
        // 0x004a609c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a6090
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a60b8
    charge(ctx, 4);
    swc1(f0, s0, 60);
    lbu(v0, a2, 0);
    if (i64(v0) < 0) {
        // 0x004a60d4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a60c8
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a60f0
    charge(ctx, 4);
    swc1(f0, s0, brush2d::kRgbaDelta1);
    lbu(v0, a2, 1);
    if (i64(v0) < 0) {
        // 0x004a610c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a6100
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a6128
    charge(ctx, 4);
    swc1(f0, s0, 76);
    lbu(v0, a2, 2);
    if (i64(v0) < 0) {
        // 0x004a6144
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a6138
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a6160
    charge(ctx, 4);
    swc1(f0, s0, 80);
    lbu(v0, a2, 3);
    if (i64(v0) < 0) {
        // 0x004a617c
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x004a6170
        charge(ctx, 3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004a6198
    charge(ctx, 26);
    swc1(f0, s0, 84);
    a1 = t0;
    lwc1(f1, s0, brush2d::kRgba1);
    a0 = addiu(s0, 96);
    lwc1(f0, s0, brush2d::kRgbaDelta1);
    a2 = 4;
    sub_s(f0, f0, f1);
    swc1(f0, s0, brush2d::kRgbaDelta1);
    lwc1(f1, s0, 52);
    lwc1(f0, s0, 76);
    sub_s(f0, f0, f1);
    swc1(f0, s0, 76);
    lwc1(f1, s0, 56);
    lwc1(f0, s0, 80);
    sub_s(f0, f0, f1);
    swc1(f0, s0, 80);
    lwc1(f1, s0, 60);
    lwc1(f0, s0, 84);
    sub_s(f0, f0, f1);
    link(ctx, 0x4A61E4u);  // $ra first: the delay slot below depends on it
    swc1(f0, s0, 84);
    call(ctx, gen::fn_memcpy_00521250);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A6200 [rt2dBrushSetUV] -- sets a brush's two UV origins and deltas from four points; flag bit 1 set when any delta is non-zero, else cleared
// +16 = *$t0, +40 = *$a3 - *$t0, +64 = *$a1, +88 = *$a2 - *$a1 (2-D points). The brush.
// 0x004A6200 sub_4A6200 -- 212 bytes; leaf frame (no stack)
void sub_4A6200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004a6200
    enter(ctx, 29);  // entry check point + this block's cycles
    lwc1(f2, t0, 0);
    lwc1(f0, t0, 4);
    mtc1(zero, f1);
    swc1(f2, a0, brush2d::kUv0);
    swc1(f0, a0, 20);
    lwc1(f2, a3, 0);
    lwc1(f0, t0, 0);
    sub_s(f0, f2, f0);
    swc1(f0, a0, brush2d::kUvDelta0);
    lwc1(f2, a3, 4);
    lwc1(f0, t0, 4);
    sub_s(f0, f2, f0);
    swc1(f0, a0, 44);
    lwc1(f2, a1, 0);
    lwc1(f0, a1, 4);
    swc1(f2, a0, brush2d::kUv1);
    swc1(f0, a0, 68);
    lwc1(f2, a2, 0);
    lwc1(f0, a1, 0);
    sub_s(f0, f2, f0);
    swc1(f0, a0, brush2d::kUvDelta1);
    lwc1(f2, a2, 4);
    lwc1(f0, a1, 4);
    sub_s(f0, f2, f0);
    swc1(f0, a0, 92);
    lwc1(f0, a0, brush2d::kUvDelta0);
    c_eq_s(f1, f0);
    if (cond(ctx)) {
        // 0x004a6288
        charge(ctx, 4);
        lwc1(f0, a0, 44);
        c_eq_s(f1, f0);
        if (!cond(ctx)) {
            backedge(ctx);
            goto L_004a6274;
        }
        // 0x004a6298
        charge(ctx, 4);
        lwc1(f0, a0, brush2d::kUvDelta1);
        c_eq_s(f1, f0);
        if (!cond(ctx)) {
            backedge(ctx);
            goto L_004a6274;
        }
        // 0x004a62a8
        charge(ctx, 4);
        lwc1(f0, a0, 92);
        c_eq_s(f1, f0);
        if (!cond(ctx)) {
            backedge(ctx);
            goto L_004a6274;
        }
        // 0x004a62b8
        charge(ctx, 5);
        lw(v1, a0, brush2d::kFlags);
        v0 = si(-3);
        v0 = v1 & v0;
        sw(v0, a0, brush2d::kFlags);
        backedge(ctx);
        goto L_004a6280;
    }
L_004a6274:
    charge(ctx, 3);
    lw(v0, a0, brush2d::kFlags);
    v0 = v0 | 0x2;
    sw(v0, a0, brush2d::kFlags);
L_004a6280:
    charge(ctx, 2);
    v0 = a0;
    // 0x004a62cc
    charge(ctx, 2);
}


// sub_4A62E0 [rt2dBrushSetTexture] -- sets a brush's texture: its reference count up, flag bit 1 by its presence, the old texture destroyed; the brush
// 0x004A62E0 sub_4A62E0 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A62E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a62e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s1 = a0;
    if (s0 == 0) {
        // 0x004a6334
        charge(ctx, 5);
        lw(v1, s1, brush2d::kFlags);
        v0 = si(-3);
        v0 = v1 & v0;
        sw(v0, s1, brush2d::kFlags);
        backedge(ctx);
    } else {
        // 0x004a62fc
        charge(ctx, 6);
        lw(v0, s1, brush2d::kFlags);
        v0 = v0 | 0x2;
        sw(v0, s1, brush2d::kFlags);
        lw(v0, s0, rwtex::kRefCount);
        v0 = addiu(v0, 1);
        sw(v0, s0, rwtex::kRefCount);
    }
    // 0x004a6314
    charge(ctx, 3);
    lw(a0, s1, brush2d::kTexture);
    if (a0 != 0) {
        // 0x004a6320
        charge(ctx, 2);
        jal(ctx, 0x4A6320u, gen::fn_sub_4D0F00_004d0f00);
    }
    // 0x004a6328
    charge(ctx, 3);
    sw(s0, s1, brush2d::kTexture);
    v0 = s1;
    // 0x004a6348
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4A6360 [rt2dBrushStreamReadBody] -- fills a brush from its streamed 112-byte record: the four colour / UV groups, the packed colour, flags, +112; the texture when streamed
// ($a0 = the brush, $a1 = the record, $a2 = the stream) A texture (chunk 6, RwTextureStreamRead) whose raster is not
// a power of two in both sizes gets clamped addressing (0x33 in +81); the brush, or 0 when the texture chunk is
// missing.
// 0x004A6360 sub_4A6360 -- 460 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A6360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004a6360
    enter(ctx, 66);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a1 = addiu(s1, 4);
    a2 = 16;
    jal(ctx, 0x4A6384u, gen::fn_memcpy_00521250);
    lwc1(f1, s1, 20);
    a0 = addiu(s2, 24);
    lwc1(f0, s1, 24);
    a1 = addiu(s1, 28);
    a2 = 16;
    swc1(f1, s2, brush2d::kUv0);
    link(ctx, 0x4A63A4u);  // $ra first: the delay slot below depends on it
    swc1(f0, s2, 20);
    call(ctx, gen::fn_memcpy_00521250);
    lwc1(f1, s1, 44);
    a0 = addiu(s2, 48);
    lwc1(f0, s1, 48);
    a1 = addiu(s1, 52);
    a2 = 16;
    swc1(f1, s2, brush2d::kUvDelta0);
    link(ctx, 0x4A63C4u);  // $ra first: the delay slot below depends on it
    swc1(f0, s2, 44);
    call(ctx, gen::fn_memcpy_00521250);
    lwc1(f1, s1, 68);
    a0 = addiu(s2, 72);
    lwc1(f0, s1, 72);
    a1 = addiu(s1, 76);
    a2 = 16;
    swc1(f1, s2, brush2d::kUv1);
    link(ctx, 0x4A63E4u);  // $ra first: the delay slot below depends on it
    swc1(f0, s2, 68);
    call(ctx, gen::fn_memcpy_00521250);
    lwc1(f1, s1, 92);
    lwc1(f0, s1, 96);
    swc1(f1, s2, brush2d::kUvDelta1);
    swc1(f0, s2, 92);
    lwc1(f0, s2, brush2d::kRgba0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sb(v0, s2, brush2d::kPackedRgba);
    lwc1(f0, s2, 4);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sb(v0, s2, 97);
    lwc1(f0, s2, 8);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sb(v0, s2, 98);
    lwc1(f0, s2, 12);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sb(v0, s2, 99);
    lw(v0, s1, 100);
    sw(v0, s2, brush2d::kFlags);
    lwc1(f0, s1, 104);
    swc1(f0, s2, brush2d::kHalfWidth);
    lw(v0, s1, 108);
    if (v0 != 0) {
        // 0x004a6470
        charge(ctx, 7);
        a0 = s0;
        a1 = 6;
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x4A647Cu, gen::fn_sub_4C1600_004c1600);
        if (v0 != 0) {
            // 0x004a6494
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x4A6494u, gen::fn_sub_4C83C0_004c83c0);
            if (v0 != 0) {
                // 0x004a64a4
                charge(ctx, 3);
                lw(v1, v0, 0);
                if (v1 != 0) {
                    // 0x004a64b0
                    charge(ctx, 8);
                    lw(a1, v1, 16);
                    lw(a0, v1, 12);
                    v1 = addiu(a1, -1);
                    v1 = a1 & v1;
                    // xor v1: a 64-bit move to itself (no effect)
                    v1 = sltiu(v1, 1);
                    if (v1 != 0) {
                        // 0x004a64d0
                        charge(ctx, 4);
                        v1 = addiu(a0, -1);
                        v1 = a0 & v1;
                        // xor v1: a 64-bit move to itself (no effect)
                        v1 = sltiu(v1, 1);
                    }
                    // 0x004a64e0
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x004a64e8
                        charge(ctx, 6);
                        lw(a0, v0, 80);
                        v1 = lui(0xFFFF);
                        v1 = v1 | 0xFF;
                        v1 = a0 & v1;
                        v1 = v1 | 0x3300;
                        sw(v1, v0, 80);
                    }
                }
            }
            // 0x004a6500
            charge(ctx, 5);
            sw(v0, s2, brush2d::kTexture);
            lw(v0, s2, brush2d::kFlags);
            v0 = v0 | 0x2;
            sw(v0, s2, brush2d::kFlags);
            backedge(ctx);
            goto L_004a6468;
        }
        // 0x004a648c
        charge(ctx, 2);
        v0 = 0;
        // 0x004a6514 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004a6468:
    charge(ctx, 2);
    v0 = s2;
    // 0x004a6514 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4A6530 [Rt2dBrushStreamRead] -- reads a brush: 112 bytes from the stream, the packed colour, then the body (sub_4A6360) when the record's version word is 1; else 0
// 0x004A6530 sub_4A6530 -- 200 bytes; frame 0xA0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A6530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004a6530
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    a2 = 112;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x4A6550u, gen::fn_sub_4C5250_004c5250);
    v1 = 112;
    if (v0 != v1) {
        // 0x004a65cc
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a6564
        charge(ctx, 24);
        lwc1(f0, s1, brush2d::kRgba0);
        v0 = 1;
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, s1, brush2d::kPackedRgba);
        lwc1(f0, s1, 4);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, s1, 97);
        lwc1(f0, s1, 8);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, s1, 98);
        lwc1(f0, s1, 12);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, s1, 99);
        lw(v1, sp, 0x30);
        if (v1 == v0) {
            // 0x004a65d4
            charge(ctx, 4);
            a0 = s1;
            a2 = s0;
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x4A65DCu, gen::fn_sub_4A6360_004a6360);
        } else {
            // 0x004a65c4
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004a65e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}


// sub_4A7620 [rt2dFontBuildHighMap] -- builds a font's map of codes >= 128: the code table's minimum / maximum positive codes, a u16 table of glyph indices (-1 for none)
// The codes come from 0x95F984 (one per glyph); 1 / the font, or error 0x80000013 (out of memory) and 0 when the allocation fails.
// 0x004A7620 sub_4A7620 -- 512 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A7620(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a7620
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a2 = 0;
    sd(ra, sp, 0x40);
    a3 = 0;
    sq(s3, sp, 0x30);
    t0 = 0;
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 304);
    at = slt(0, a0);
    s2 = 0xFFFF;
    if (at != 0) {
        // 0x004a7658
        charge(ctx, 3);
        v0 = 0x960000;
        v1 = 1;
        lw(a1, v0, -1660);  // 0x95F984 (Rt2d fonts: the code table of the font being read)
        for (;;) {
            // 0x004a7664
            charge(ctx, 3);
            lw(v0, a1, 0);
            if (i64(v0) > 0) {
                // 0x004a7670
                charge(ctx, 3);
                at = slt(v0, s2);
                if (at != 0) {
                    // 0x004a767c
                    charge(ctx, 1);
                    s2 = v0;
                }
                // 0x004a7680
                charge(ctx, 3);
                at = slt(a2, v0);
                if (at != 0) {
                    // 0x004a768c
                    charge(ctx, 1);
                    a2 = v0;
                }
                // 0x004a7690
                charge(ctx, 2);
                a3 = v1;
            }
            // 0x004a7698
            charge(ctx, 4);
            t0 = addiu(t0, 1);
            v0 = slt(t0, a0);
            a1 = addiu(a1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004a76a8
    charge(ctx, 2);
    if (i64(a3) > 0) {
        // 0x004a76b8
        charge(ctx, 10);
        v0 = 0x30000;
        s0 = subu(a2, s2);
        a1 = v0 | 0x190;
        s1 = addiu(s0, 1);
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = sll(s1, 1);
        jalr(ctx, 0x4A76D0u, v0.u());
        if (v0 != 0) {
            // 0x004a76e0
            charge(ctx, 3);
            at = slt(0, s1);
            a2 = 0;
            if (at != 0) {
                // 0x004a76ec
                charge(ctx, 3);
                at = slti(s1, 9);
                a1 = addiu(s0, -7);
                if (at == 0) {
                    // 0x004a76f8
                    charge(ctx, 3);
                    at = slt(s1, 0);
                    v1 = 0;
                    if (at == 0) {
                        // 0x004a7704
                        charge(ctx, 5);
                        at = 0x7FFF0000;
                        at = at | 0xFFFF;
                        at = slt(s1, at);
                        if (at != 0) {
                            // 0x004a7718
                            charge(ctx, 1);
                            v1 = 1;
                        }
                    }
                    // 0x004a771c
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x004a7724
                        charge(ctx, 2);
                        a3 = v0;
                        a0 = si(-1);
                        for (;;) {
                            // 0x004a772c
                            charge(ctx, 12);
                            sh(a0, a3, 0);
                            a2 = addiu(a2, 8);
                            sh(a0, a3, 2);
                            v1 = slt(a2, a1);
                            sh(a0, a3, 4);
                            sh(a0, a3, 6);
                            sh(a0, a3, 8);
                            sh(a0, a3, 10);
                            sh(a0, a3, 12);
                            sh(a0, a3, 14);
                            a3 = addiu(a3, 16);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a775c
                        charge(ctx, 1);
                    }
                }
                // 0x004a7760
                charge(ctx, 3);
                at = slt(a2, s1);
                if (at != 0) {
                    // 0x004a776c
                    charge(ctx, 4);
                    v1 = sll(a2, 1);
                    a1 = addiu(s0, 1);
                    a3 = addu(v0, v1);
                    a0 = si(-1);
                    for (;;) {
                        // 0x004a777c
                        charge(ctx, 7);
                        a2 = addiu(a2, 1);
                        sh(a0, a3, 0);
                        v1 = slt(a2, a1);
                        a3 = addiu(a3, 2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004a7798
            charge(ctx, 4);
            lw(v1, s3, font2d::kNumGlyphs);
            at = slt(0, v1);
            a1 = 0;
            if (at != 0) {
                // 0x004a77a8
                charge(ctx, 2);
                a2 = 0;
                v1 = 0x960000;
                for (;;) {
                    // 0x004a77b0
                    charge(ctx, 5);
                    lw(a0, v1, -1660);  // 0x95F984 (Rt2d fonts: the code table of the font being read)
                    a0 = addu(a0, a2);
                    lw(a0, a0, 0);
                    if (i64(a0) > 0) {
                        // 0x004a77c4
                        charge(ctx, 5);
                        a0 = subu(a0, s2);
                        a0 = sll(a0, 1);
                        a0 = addu(v0, a0);
                        sh(a1, a0, 0);
                    }
                    // 0x004a77d8
                    charge(ctx, 5);
                    lw(a0, s3, font2d::kNumGlyphs);
                    a1 = addiu(a1, 1);
                    a0 = slt(a1, a0);
                    a2 = addiu(a2, 4);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a77ec
                charge(ctx, 1);
            }
            // 0x004a77f0
            charge(ctx, 4);
            sw(s1, s3, font2d::kNumHigh);
            sw(s2, s3, font2d::kFirstHigh);
            sw(v0, s3, font2d::kHighMap);
            backedge(ctx);
            goto L_004a76b0;
        }
        // 0x004a7800
        charge(ctx, 1);
        v0 = 0;
        // 0x004a7804 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004a76b0:
    charge(ctx, 2);
    v0 = s3;
    // 0x004a7804 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4A91F0 [rt2dFontClose] -- the font module's close: every dictionary font destroyed (its name freed, sub_4A96B0), the texture dictionary, free lists and buffers released
// 0x004A91F0 sub_4A91F0 -- 320 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A91F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004a91f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x960000;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s3, v0, -4744);  // 0x95ED78 (Rt2d fonts: the font dictionary)
    if (s3 != 0) {
        // 0x004a9218
        charge(ctx, 4);
        s1 = 0x960000;
        s0 = 0x960000;
        s1 = addiu(s1, 380);  // &0x96017C (RwFree slot)
        s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
        for (;;) {
            // 0x004a9228
            charge(ctx, 13);
            lw(v0, s1, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4A922Cu);  // $ra = the return address
            lw(a0, s3, 0);
            call_ptr(ctx, jt);
            link(ctx, 0x4A9234u);  // $ra first: the delay slot below depends on it
            lw(a0, s3, 4);
            call(ctx, gen::fn_sub_4A96B0_004a96b0);
            v0 = 0x960000;
            lw(v1, s0, 0);
            lw(a0, v0, -4748);  // 0x95ED74 (Rt2d fonts: the 12-byte font-dictionary entry free list)
            lw(s2, s3, 8);
            a1 = s3;
            jalr(ctx, 0x4A924Cu, v1.u());
            s3 = s2;
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004a925c
        charge(ctx, 1);
    }
    // 0x004a9260
    charge(ctx, 6);
    v0 = 0x960000;
    sw(zero, v0, -4744);  // 0x95ED78 (Rt2d fonts: the font dictionary)
    v0 = 0x960000;
    lw(a0, v0, -4740);  // 0x95ED7C (Rt2d fonts: the font texture dictionary)
    if (a0 != 0) {
        // 0x004a9278
        charge(ctx, 2);
        jal(ctx, 0x4A9278u, gen::fn_sub_4D0D10_004d0d10);
    }
    // 0x004a9280
    charge(ctx, 18);
    v0 = 0x960000;
    v1 = 0x960000;
    sw(zero, v0, -4740);  // 0x95ED7C (Rt2d fonts: the font texture dictionary)
    v0 = 0x960000;
    lw(a0, v0, -4748);  // 0x95ED74 (Rt2d fonts: the 12-byte font-dictionary entry free list)
    link(ctx, 0x4A9294u);  // $ra first: the delay slot below depends on it
    sw(zero, v1, -4736);  // 0x95ED80 (Rt2d fonts: the current texture dictionary)
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    v0 = 0x960000;
    v1 = 0x960000;
    lw(a0, v0, -4760);  // 0x95ED68 (Rt2d fonts: the 324-byte font free list)
    link(ctx, 0x4A92A8u);  // $ra first: the delay slot below depends on it
    sw(zero, v1, -4748);  // 0x95ED74 (Rt2d fonts: the 12-byte font-dictionary entry free list)
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    v1 = 0x960000;
    sw(zero, a0, -4760);  // 0x95ED68 (Rt2d fonts: the 324-byte font free list)
    lw(a0, v1, -1660);  // 0x95F984 (Rt2d fonts: the code table of the font being read)
    if (a0 != 0) {
        // 0x004a92c8
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4A92D0u, v0.u());
    }
    // 0x004a92d8
    charge(ctx, 6);
    a0 = 0x960000;
    v1 = 0x960000;
    sw(zero, a0, -1660);  // 0x95F984 (Rt2d fonts: the code table of the font being read)
    lw(a0, v1, -4756);  // 0x95ED6C (Rt2d fonts: the font path buffer)
    if (a0 != 0) {
        // 0x004a92f0
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4A92F8u, v0.u());
    }
    // 0x004a9300 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v1 = 0x960000;
    sw(zero, gp, -17500);  // 0x7CE894
    sw(zero, v1, -4756);  // 0x95ED6C (Rt2d fonts: the font path buffer)
    v1 = 0x960000;
    sw(zero, v1, -4752);  // 0x95ED70 (Rt2d fonts: the path buffer size)
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4A9330 [rt2dFontOpen] -- the font module's open: the 324-byte font and 12-byte entry free lists, the 81-byte path buffer ('fonts\\'), the quad index table, the texture dictionary
// The index table: 64 quads of 6 indices (0 2 3 0 3 1 + 4k); the read callback sub_4A98A0 installed. 1, or 0 when
// a free list or the buffer cannot be made.
// 0x004A9330 sub_4A9330 -- 340 bytes; frame 0x10: ra sp+0x0
void sub_4A9330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a9330
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = 0x40000;
    lw(a1, gp, -20560);  // 0x7CDCA0
    a0 = 324;
    lw(a3, gp, -20556);  // 0x7CDCA4
    a2 = 4;
    t0 = addiu(t0, -6096);  // &0x95E830 (Rt2d fonts: the 324-byte free list's static block)
    t1 = v0 | 0x199;
    jal(ctx, 0x4A9354u, gen::fn_sub_4C3B60_004c3b60);
    v1 = 0x960000;
    sw(v0, v1, -4760);  // 0x95ED68 (Rt2d fonts: the 324-byte font free list)
    if (v0 == 0) {
        // 0x004a9464
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a9368
        charge(ctx, 12);
        lw(a1, gp, -20552);  // 0x7CDCA8
        t0 = 0x960000;
        lw(a3, gp, -20548);  // 0x7CDCAC
        v0 = 0x40000;
        a0 = 12;
        a2 = 4;
        t0 = addiu(t0, -6144);  // &0x95E800 (Rt2d fonts: the 12-byte free list's static block)
        t1 = v0 | 0x190;
        jal(ctx, 0x4A9384u, gen::fn_sub_4C3B60_004c3b60);
        v1 = 0x960000;
        sw(v0, v1, -4748);  // 0x95ED74 (Rt2d fonts: the 12-byte font-dictionary entry free list)
        if (v0 == 0) {
            // 0x004a946c
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004a9398
            charge(ctx, 9);
            v0 = 0x1040000;
            a1 = v0 | 0x190;  // &0x1040190
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = 81;
            jalr(ctx, 0x4A93A8u, v0.u());
            v1 = 0x960000;
            sw(v0, v1, -4756);  // 0x95ED6C (Rt2d fonts: the font path buffer)
            if (v0 == 0) {
                // 0x004a9474
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004a93bc
                charge(ctx, 9);
                v1 = 81;
                v0 = 0x960000;
                sw(v1, v0, -4752);  // 0x95ED70 (Rt2d fonts: the path buffer size)
                a0 = addiu(gp, -20544);  // "fonts\\"
                jal(ctx, 0x4A93C8u, gen::fn_sub_4A9490_004a9490);
                a1 = 0x960000;
                a3 = 0;
                a1 = addiu(a1, -5536);  // &0x95EA60 (Rt2d fonts: the quad index table (6 x 64 u16))
                a2 = 0;
                for (;;) {
                    // 0x004a93e0: the quad index table: 0 2 3 0 3 1 + 4k
                    charge(ctx, 16);
                    v1 = a2 & 0xFFFF;
                    sh(a2, a1, 0);
                    v0 = addiu(v1, 2);
                    a0 = addiu(v1, 3);
                    sh(v0, a1, 2);
                    v1 = addiu(v1, 1);
                    sh(a0, a1, 4);
                    v0 = addiu(a2, 4);
                    sh(a2, a1, 6);
                    a3 = addiu(a3, 6);
                    sh(a0, a1, 8);
                    a2 = v0 & 0xFFFF;
                    sh(v1, a1, 10);
                    v0 = slti(a3, 384);
                    a1 = addiu(a1, 12);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a9420
                charge(ctx, 17);
                v0 = 0x960000;
                link(ctx, 0x4A9424u);  // $ra first: the delay slot below depends on it
                sw(zero, v0, -4744);  // 0x95ED78 (Rt2d fonts: the font dictionary)
                call(ctx, gen::fn_sub_4D0C30_004d0c30);
                v1 = 0x960000;
                a0 = 0x960000;
                sw(v0, v1, -4740);  // 0x95ED7C (Rt2d fonts: the font texture dictionary)
                sw(v0, a0, -4736);  // 0x95ED80 (Rt2d fonts: the current texture dictionary)
                v1 = 0x960000;
                v0 = 0x960000;
                a0 = 0x4B0000;
                sw(zero, v1, -1660);  // 0x95F984 (Rt2d fonts: the code table of the font being read)
                a0 = addiu(a0, -26464);  // &sub_4A98A0
                link(ctx, 0x4A9450u);  // $ra first: the delay slot below depends on it
                sw(zero, v0, -1656);  // 0x95F988 (Rt2d fonts: its size)
                call(ctx, gen::fn_sub_4A9550_004a9550);
                v0 = 1;
                sw(v0, gp, -17500);  // 0x7CE894
            }
        }
    }
    // 0x004a9478 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4A9490 [Rt2dFontSetPath] -- sets the font path: the buffer grown to strlen + 1 (RwRealloc) when needed, the string copied; the path, or 0
// 0x004A9490 sub_4A9490 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A9490(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a9490
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    if (s1 == 0) {
        // 0x004a9530
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004a94a8
        charge(ctx, 10);
        v0 = 0x960000;
        lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
        jalr(ctx, 0x4A94B0u, v0.u());
        s0 = addiu(v0, 1);
        v0 = 0x960000;
        lw(v0, v0, -4752);  // 0x95ED70 (Rt2d fonts: the path buffer size)
        at = sltu(v0, s0);
        if (at != 0) {
            // 0x004a94d0
            charge(ctx, 10);
            v0 = 0x960000;
            lw(a0, v0, -4756);  // 0x95ED6C (Rt2d fonts: the font path buffer)
            v0 = 0x1040000;
            a2 = v0 | 0x190;  // &0x1040190
            v0 = 0x960000;
            lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
            a1 = s0;
            jalr(ctx, 0x4A94E8u, v0.u());
            if (v0 != 0) {
                // 0x004a94f8
                charge(ctx, 4);
                a0 = 0x960000;
                v1 = 0x960000;
                sw(v0, a0, -4756);  // 0x95ED6C (Rt2d fonts: the font path buffer)
                sw(s0, v1, -4752);  // 0x95ED70 (Rt2d fonts: the path buffer size)
                goto L_004a9508;
            }
            // 0x004a9528
            charge(ctx, 2);
            v0 = 0;
            // 0x004a9534 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004a9508:
        charge(ctx, 8);
        v0 = 0x960000;
        lw(a0, v0, -4756);  // 0x95ED6C (Rt2d fonts: the font path buffer)
        v0 = 0x960000;
        lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
        a1 = s1;
        jalr(ctx, 0x4A9518u, v0.u());
        v0 = s1;
    }
    // 0x004a9534 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4A9550 [rt2dFontSetReadCallBack] -- stores the font read callback (0x95F478); 1
// 0x004A9550 sub_4A9550 -- 16 bytes; leaf frame (no stack)
void sub_4A9550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004a9550
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    sw(a0, v0, -2952);  // 0x95F478 (Rt2d fonts: the font read callback)
    v0 = 1;
}


// sub_4A9560 [Rt2dFontGetStringWidth] -- a string's width in $f0: the sum of each character's glyph advance + the font's gap, times the height $f12
// ($a0 = the font, $a1 = the string; unicode fonts read two-byte codes) Codes below 128 through the 128-entry map
// (+36), the rest through the high map (+292..+300); unmapped ones add nothing; the string ends at code 0.
// 0x004A9560 sub_4A9560 -- 324 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_4A9560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004a9560
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    swc1(f21, sp, 0x4);
    s0 = a1;
    swc1(f20, sp, 0x0);
    lw(a0, a0, 308);
    mtc1(zero, f20);
    mov_s(f21, f12);
    jal(ctx, 0x4A9588u, gen::fn_sub_4C2090_004c2090);
    lw(v1, s1, font2d::kFlags);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x004a95b0
        charge(ctx, 3);
        a1 = 1;
        v1 = 0;
        a0 = 0;
    } else {
        // 0x004a95a0
        charge(ctx, 4);
        a1 = 2;
        v1 = 255;
        a0 = 1;
    }
    // 0x004a95bc
    charge(ctx, 9);
    a2 = addu(s0, a0);
    v1 = v1 & 0xFF;
    lbu(a3, a2, 0);
    lbu(a2, s0, 0);
    a3 = v1 & a3;
    a3 = sll(a3, 8);
    t0 = a2 | a3;
    if (i64(t0) > 0) {
        // 0x004a95e0
        charge(ctx, 1);
        a2 = si(-1);
        for (;;) {
            // 0x004a95e4
            charge(ctx, 3);
            a3 = slti(t0, 128);
            if (a3 != 0) {
                // 0x004a9628
                charge(ctx, 4);
                a3 = sll(t0, 1);
                a3 = addu(s1, a3);
                lh(a3, a3, 36);
            } else {
                // 0x004a95f0
                charge(ctx, 4);
                lw(a3, s1, font2d::kFirstHigh);
                t0 = subu(t0, a3);
                if (i64(t0) >= 0) {
                    // 0x004a9600
                    charge(ctx, 4);
                    lw(a3, s1, font2d::kNumHigh);
                    at = slt(t0, a3);
                    if (at == 0) {
                        goto L_004a9680;
                    }
                    // 0x004a9610
                    charge(ctx, 5);
                    lw(a3, s1, font2d::kHighMap);
                    t0 = sll(t0, 1);
                    a3 = addu(a3, t0);
                    lh(a3, a3, 0);
                    goto L_004a9638;
                }
            L_004a9680:
                charge(ctx, 2);
                a3 = a2;
                backedge(ctx);
            }
        L_004a9638:
            charge(ctx, 2);
            s0 = addu(s0, a1);
            if (i64(a3) >= 0) {
                // 0x004a9640
                charge(ctx, 6);
                a3 = sll(a3, 5);
                a3 = addu(v0, a3);
                lwc1(f1, a3, 0);
                lwc1(f0, s1, font2d::kHeight);
                add_s(f0, f1, f0);
                add_s(f20, f20, f0);
            }
            // 0x004a9658
            charge(ctx, 8);
            a3 = addu(a0, s0);
            lbu(t0, a3, 0);
            lbu(a3, s0, 0);
            t0 = v1 & t0;
            t0 = sll(t0, 8);
            t0 = a3 | t0;
            if (i64(t0) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004a9678
    charge(ctx, 2);
    mul_s(f0, f20, f21);
    // 0x004a9688
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lwc1(f21, sp, 0x4);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4A96B0 [rt2dFontDestroy] -- destroys a font: each glyph's path (sub_4AC390), the glyph sList, the high map, the four textures, the record; 1, or 0 for none
// 0x004A96B0 sub_4A96B0 -- 272 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A96B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a96b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x004a97a4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004a96d0
        charge(ctx, 3);
        lw(a0, s0, font2d::kGlyphs);
        if (a0 != 0) {
            // 0x004a96dc
            charge(ctx, 6);
            jal(ctx, 0x4A96DCu, gen::fn_sub_4C2090_004c2090);
            lw(v1, s0, font2d::kNumGlyphs);
            at = sltu(0, v1);
            s2 = 0;
            if (at != 0) {
                // 0x004a96f4
                charge(ctx, 1);
                s1 = v0;
                for (;;) {
                    // 0x004a96f8
                    charge(ctx, 3);
                    lw(a0, s1, 24);
                    if (a0 != 0) {
                        // 0x004a9704
                        charge(ctx, 3);
                        jal(ctx, 0x4A9704u, gen::fn_sub_4AC390_004ac390);
                        sw(zero, s1, 24);
                    }
                    // 0x004a9710
                    charge(ctx, 5);
                    lw(v0, s0, font2d::kNumGlyphs);
                    s2 = addiu(s2, 1);
                    v0 = sltu(s2, v0);
                    s1 = addiu(s1, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a9724
                charge(ctx, 1);
            }
            // 0x004a9728
            charge(ctx, 2);
            link(ctx, 0x4A9728u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, font2d::kGlyphs);
            call(ctx, gen::fn_sub_4C20B0_004c20b0);
        }
        // 0x004a9730
        charge(ctx, 4);
        sw(zero, s0, font2d::kGlyphs);
        lw(a0, s0, font2d::kHighMap);
        if (a0 != 0) {
            // 0x004a9740
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4A9748u, v0.u());
        }
        // 0x004a9750
        charge(ctx, 3);
        sw(zero, s0, font2d::kHighMap);
        s1 = 0;
        s2 = s0;
        for (;;) {
            // 0x004a975c
            charge(ctx, 3);
            lw(a0, s2, 20);
            if (a0 != 0) {
                // 0x004a9768
                charge(ctx, 2);
                jal(ctx, 0x4A9768u, gen::fn_sub_4D0F00_004d0f00);
            }
            // 0x004a9770
            charge(ctx, 5);
            s1 = addiu(s1, 1);
            sw(zero, s2, 20);
            v0 = sltiu(s1, 4);
            s2 = addiu(s2, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004a9784
        charge(ctx, 8);
        v0 = 0x960000;
        lw(a0, v0, -4760);  // 0x95ED68 (Rt2d fonts: the 324-byte font free list)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s0;
        jalr(ctx, 0x4A9794u, v0.u());
        v0 = 1;
    }
    // 0x004a97a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4A9BD0 [Rt2dFontIsUnicode] -- 1 when a font is unicode (flag bit 1)
// 0x004A9BD0 sub_4A9BD0 -- 16 bytes; leaf frame (no stack)
void sub_4A9BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004a9bd0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, font2d::kFlags);
    v0 = v0 & 0x2;
    v0 = sltu(0, v0);
}


// sub_4A9BE0 [rt2dCallToolkitHook] -- calls the toolkit hook at 0x95EFD0 (a tail call)
// 0x004A9BE0 sub_4A9BE0 -- 16 bytes; leaf frame (no stack)
void sub_4A9BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004a9be0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, -4144);  // 0x95EFD0 (Rt2d fonts: a toolkit callback)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4F2AD0 [rxPipelineNodeDestroy] -- destroys one node of a pipeline: unlocked, the definition's terms and reference count; locked, the node removed from the arrays in place
// ($a0 = the node, $a1 = the pipeline) Unlocked: the pipeline-node term (+20), the reference count (+60) down -- at
// 0 the node term (+12) and, for a heap definition (+56), the definition freed --, the node's init data freed, its
// 40 bytes cleared. Locked: the init data freed, a heap definition with no references freed, the later nodes,
// their 128-byte cluster blocks and 12-byte records moved down one place, every input index fixed up (the removed
// node's -1). The node count goes down in both. Returns the node.
// 0x004F2AD0 sub_4F2AD0 -- 904 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F2AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2ad0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, 0);
    s3 = a1;
    if (v0 != 0) {
        // 0x004f2ba8
        charge(ctx, 3);
        lw(a0, s4, pnode::kInitData);
        if (a0 != 0) {
            // 0x004f2bb4
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4F2BBCu, v0.u());
            sw(zero, s4, pnode::kInitData);
            sw(zero, s4, pnode::kInitDataSize);
        }
        // 0x004f2bcc
        charge(ctx, 4);
        lw(a0, s4, pnode::kNodeDef);
        lw(v0, a0, 60);
        if (v0 == 0) {
            // 0x004f2bdc
            charge(ctx, 3);
            lw(v0, a0, 56);
            if (v0 != 0) {
                // 0x004f2be8
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4F2BF0u, v0.u());
                sw(zero, s4, pnode::kNodeDef);
            }
        }
        // 0x004f2bfc
        charge(ctx, 15);
        lw(a3, s3, rxpipe::kNodes);
        v0 = 0x66660000;
        v0 = v0 | 0x6667;
        v1 = subu(s4, a3);
        mult(zero, v0, v1);
        a0 = srl(v1, 31);
        mfhi(v1);
        lw(v0, s3, rxpipe::kNumNodes);
        v1 = sra(v1, 4);
        s0 = addu(v1, a0);
        v0 = addiu(v0, -1);
        at = sltu(s0, v0);
        if (at != 0) {
            // 0x004f2c38
            charge(ctx, 15);
            lw(a2, gp, -16840);  // 0x7CEB28
            a1 = 0x960000;
            a1 = addiu(a1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            a0 = sll(s0, 7);
            v1 = sltu(s0, v0);
            s1 = s0;
            a1 = addu(a1, a2);
            lw(a2, a1, 56);
            a1 = sll(a2, 2);
            a1 = addu(a1, a2);
            a1 = sll(a1, 3);
            a1 = addu(a3, a1);
            a0 = addu(a1, a0);
            s2 = addiu(a0, 128);
            if (v1 != 0) {
                for (;;) {
                    // 0x004f2d6c
                    charge(ctx, 10);
                    a1 = s2;
                    a2 = 128;
                    jal(ctx, 0x4F2D70u, gen::fn_memcpy_00521250);
                    lw(v0, s3, rxpipe::kNumNodes);
                    a0 = s2;
                    s1 = addiu(s1, 1);
                    v0 = addiu(v0, -1);
                    v1 = sltu(s1, v0);
                    s2 = addiu(s2, 128);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004f2d94
                charge(ctx, 2);
                lw(a2, gp, -16840);  // 0x7CEB28
                backedge(ctx);
            } else {
                // 0x004f2c74
                charge(ctx, 1);
                lw(a2, gp, -16840);  // 0x7CEB28
            }
            // 0x004f2c78
            charge(ctx, 15);
            a0 = 0x960000;
            a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            lw(a1, s3, rxpipe::kNodes);
            v1 = sltu(s0, v0);
            s1 = s0;
            a0 = addu(a0, a2);
            lw(a3, a0, 56);
            a2 = sll(a3, 2);
            a0 = sll(a3, 7);
            a2 = addu(a2, a3);
            a2 = sll(a2, 3);
            a1 = addu(a1, a2);
            a0 = addu(a1, a0);
            s2 = addiu(a0, 12);
            if (v1 != 0) {
                for (;;) {
                    // 0x004f2d9c
                    charge(ctx, 10);
                    a1 = s2;
                    a2 = 12;
                    jal(ctx, 0x4F2DA0u, gen::fn_memcpy_00521250);
                    lw(v0, s3, rxpipe::kNumNodes);
                    a0 = s2;
                    s1 = addiu(s1, 1);
                    v0 = addiu(v0, -1);
                    v1 = sltu(s1, v0);
                    s2 = addiu(s2, 12);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004f2dc4
                charge(ctx, 2);
                v1 = sltu(s0, v0);
                backedge(ctx);
            } else {
                // 0x004f2cb4
                charge(ctx, 1);
                v1 = sltu(s0, v0);
            }
            // 0x004f2cb8
            charge(ctx, 2);
            s1 = s0;
            if (v1 != 0) {
                // 0x004f2dcc
                charge(ctx, 3);
                v0 = sll(s0, 2);
                v0 = addu(v0, s0);
                s2 = sll(v0, 3);
                for (;;) {
                    // 0x004f2dd8
                    charge(ctx, 22);
                    lw(v1, s3, rxpipe::kNodes);
                    v0 = addiu(s2, 40);
                    a2 = 40;
                    a1 = addu(v1, v0);
                    a0 = addu(v1, s2);
                    jal(ctx, 0x4F2DE8u, gen::fn_memcpy_00521250);
                    lw(v0, s3, rxpipe::kNodes);
                    s1 = addiu(s1, 1);
                    v1 = addu(v0, s2);
                    lw(v0, v1, 8);
                    v0 = addiu(v0, -128);
                    sw(v0, v1, 8);
                    lw(v0, s3, rxpipe::kNodes);
                    v1 = addu(v0, s2);
                    lw(v0, v1, 28);
                    v0 = addiu(v0, -12);
                    sw(v0, v1, 28);
                    lw(v0, s3, rxpipe::kNumNodes);
                    v0 = addiu(v0, -1);
                    v1 = sltu(s1, v0);
                    s2 = addiu(s2, 40);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004f2e30
                charge(ctx, 2);
                at = sltu(0, v0);
                backedge(ctx);
            } else {
                // 0x004f2cc0
                charge(ctx, 1);
                at = sltu(0, v0);
            }
            // 0x004f2cc4
            charge(ctx, 2);
            a2 = 0;
            if (at != 0) {
                // 0x004f2ccc
                charge(ctx, 2);
                t0 = 0;
                v1 = si(-1);
                for (;;) {
                    // 0x004f2cd4
                    charge(ctx, 6);
                    lw(v0, s3, rxpipe::kNodes);
                    a0 = addu(v0, t0);
                    lw(v0, a0, 4);
                    at = sltu(0, v0);
                    t1 = 0;
                    if (at != 0) {
                        // 0x004f2cec
                        charge(ctx, 1);
                        a3 = 0;
                        for (;;) {
                            // 0x004f2cf0
                            charge(ctx, 6);
                            lw(v0, a0, 8);
                            a1 = addu(v0, a3);
                            lw(a0, a1, 0);
                            v0 = sltu(a0, s0);
                            if (v0 == 0) {
                                // 0x004f2d08
                                charge(ctx, 2);
                                if (s0 != a0) {
                                    // 0x004f2d18
                                    charge(ctx, 2);
                                    v0 = addiu(a0, -1);
                                    sw(v0, a1, 0);
                                } else {
                                    // 0x004f2d10
                                    charge(ctx, 2);
                                    sw(v1, a1, 0);
                                }
                            }
                            // 0x004f2d20
                            charge(ctx, 7);
                            lw(v0, s3, rxpipe::kNodes);
                            t1 = addiu(t1, 1);
                            a0 = addu(t0, v0);
                            lw(v0, a0, 4);
                            v0 = sltu(t1, v0);
                            a3 = addiu(a3, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f2d3c
                        charge(ctx, 1);
                    }
                    // 0x004f2d40
                    charge(ctx, 6);
                    lw(v0, s3, rxpipe::kNumNodes);
                    a2 = addiu(a2, 1);
                    v0 = addiu(v0, -1);
                    v0 = sltu(a2, v0);
                    t0 = addiu(t0, 40);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    } else {
        // 0x004f2afc
        charge(ctx, 4);
        lw(v0, s4, pnode::kNodeDef);
        lw(v0, v0, 20);
        if (v0 != 0) {
            // 0x004f2b0c
            charge(ctx, 2);
            jalr(ctx, 0x4F2B0Cu, v0.u());
        }
        // 0x004f2b14
        charge(ctx, 8);
        lw(v1, s4, pnode::kNodeDef);
        lw(v0, v1, 60);
        v0 = addiu(v0, -1);
        sw(v0, v1, 60);
        lw(a0, s4, pnode::kNodeDef);
        lw(v0, a0, 60);
        if (v0 == 0) {
            // 0x004f2b34
            charge(ctx, 3);
            lw(v0, a0, 12);
            if (v0 != 0) {
                // 0x004f2b40
                charge(ctx, 2);
                jalr(ctx, 0x4F2B40u, v0.u());
            }
            // 0x004f2b48
            charge(ctx, 4);
            lw(a0, s4, pnode::kNodeDef);
            lw(v0, a0, 56);
            if (v0 != 0) {
                // 0x004f2b58
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4F2B60u, v0.u());
                sw(zero, s4, pnode::kNodeDef);
            }
        }
        // 0x004f2b6c
        charge(ctx, 3);
        lw(a0, s4, pnode::kInitData);
        if (a0 != 0) {
            // 0x004f2b78
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4F2B80u, v0.u());
            sw(zero, s4, pnode::kInitData);
            sw(zero, s4, pnode::kInitDataSize);
        }
        // 0x004f2b90
        charge(ctx, 6);
        a0 = s4;
        a1 = 0;
        a2 = 40;
        jal(ctx, 0x4F2B98u, gen::fn_memset_00521408);
    }
    // 0x004f2d58
    charge(ctx, 5);
    lw(v1, s3, rxpipe::kNumNodes);
    v0 = s4;
    v1 = addiu(v1, -1);
    sw(v1, s3, rxpipe::kNumNodes);
    // 0x004f2e38
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4F3010 [RxPipelineDestroy] -- destroys a pipeline: each of its nodes (sub_4F2AD0), its scratch block (RwFree), the record back to the pipeline free list
// The free list is the pipeline module's (RwEngineInstance + gp 0x7CEB28 +0). Nothing for a null pipeline.
// 0x004F3010 sub_4F3010 -- 200 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3010(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f3010
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s3 == 0) {
        // 0x004f30bc
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    } else {
        // 0x004f3030
        charge(ctx, 5);
        lw(s0, s3, rxpipe::kNumNodes);
        lw(s1, s3, rxpipe::kNodes);
        v0 = sltu(0, s0);
        s2 = 0;
        if (v0 != 0) {
            for (;;) {
                // 0x004f3098
                charge(ctx, 7);
                a0 = s1;
                a1 = s3;
                jal(ctx, 0x4F309Cu, gen::fn_sub_4F2AD0_004f2ad0);
                s2 = addiu(s2, 1);
                v0 = sltu(s2, s0);
                s1 = addiu(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f30b4
            charge(ctx, 2);
            sw(zero, s3, rxpipe::kNodes);
            backedge(ctx);
        } else {
            // 0x004f3044
            charge(ctx, 1);
            sw(zero, s3, rxpipe::kNodes);
        }
        // 0x004f3048
        charge(ctx, 3);
        lw(a0, s3, rxpipe::kScratch);
        if (a0 != 0) {
            // 0x004f3054
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4F305Cu, v0.u());
            sw(zero, s3, rxpipe::kScratch);
            sw(zero, s3, rxpipe::kScratchSize);
        }
        // 0x004f306c
        charge(ctx, 11);
        lw(a0, gp, -16840);  // 0x7CEB28
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        a1 = s3;
        jalr(ctx, 0x4F3088u, v0.u());
        ld(ra, sp, 0x40);
    }
    // 0x004f30c0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


}  // namespace p3fes::game
