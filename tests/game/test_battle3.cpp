// Phase 5 pair tests for slice battle3 (game/src/battle/battle3.cpp): every body against its recompiled body (__recomp)
// on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register file and the cycle count at
// every check point and at the return / stop, all 32 MiB of RAM (a PairRange: the dead stack and every stray store),
// the scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both bodies meet the same
// deterministic heap behind the RwMalloc / RwFree slots, printf and the H_Cdvd layer).
//
//   * random worlds (the p3fes_handgen skeleton's);
//   * battle worlds: the replay snapshots b_5800, b_6150, b_6300, b_6700, battle_ref_6150 and climb_ref_17000 (real
//     gBtl, btlActions, btlUnits, DatUnits, packets, the battle tables), each pair perturbed the way the branches ask:
//     bad-status bits (down 0x100000, dead 0x80000, the ailments), HP, the encounter id (the boss encounters 417..436,
//     468 / 469 / 506), a boss enemy id on one unit, the advantage word, the effect request bits; arguments of the kind
//     each function takes (an action, its AI target record, a unit, a unit packet's data block, a skill, an element, an
//     AI query parameter or command code, a unit id / uid valid in the snapshot);
//   * documented rules on the host: the AI weights table 0x696FA0, the MYHP / MYMP thresholds against datCalcGetMaxHp /
//     MaxSp, the unit finders (sub_2C0E30, sub_288FE0, sub_289030) and the all-out attack check (sub_28A200) against host
//     models over the snapshots' lists, the SENSEI condition, the grid cell rounding (sub_2D2280), the AI command
//     decoder (sub_2C6A00), the boss index map (sub_2F6C50) and the id maps.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle3.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace b3 = p3fes::game::b3;

namespace p3fes::recomp_gen {
void fn_sub_2821B0_002821b0(EEContext&);
void fn_sub_2821B0_002821b0__recomp(EEContext&);
void fn_sub_282BC0_00282bc0(EEContext&);
void fn_sub_282BC0_00282bc0__recomp(EEContext&);
void fn_sub_2835E0_002835e0(EEContext&);
void fn_sub_2835E0_002835e0__recomp(EEContext&);
void fn_sub_2838D0_002838d0(EEContext&);
void fn_sub_2838D0_002838d0__recomp(EEContext&);
void fn_sub_283A70_00283a70(EEContext&);
void fn_sub_283A70_00283a70__recomp(EEContext&);
void fn_sub_284040_00284040(EEContext&);
void fn_sub_284040_00284040__recomp(EEContext&);
void fn_sub_284C00_00284c00(EEContext&);
void fn_sub_284C00_00284c00__recomp(EEContext&);
void fn_sub_285670_00285670(EEContext&);
void fn_sub_285670_00285670__recomp(EEContext&);
void fn_sub_285690_00285690(EEContext&);
void fn_sub_285690_00285690__recomp(EEContext&);
void fn_sub_285730_00285730(EEContext&);
void fn_sub_285730_00285730__recomp(EEContext&);
void fn_sub_2857D0_002857d0(EEContext&);
void fn_sub_2857D0_002857d0__recomp(EEContext&);
void fn_sub_2857F0_002857f0(EEContext&);
void fn_sub_2857F0_002857f0__recomp(EEContext&);
void fn_sub_285860_00285860(EEContext&);
void fn_sub_285860_00285860__recomp(EEContext&);
void fn_sub_285880_00285880(EEContext&);
void fn_sub_285880_00285880__recomp(EEContext&);
void fn_sub_285D10_00285d10(EEContext&);
void fn_sub_285D10_00285d10__recomp(EEContext&);
void fn_sub_285D30_00285d30(EEContext&);
void fn_sub_285D30_00285d30__recomp(EEContext&);
void fn_sub_285F80_00285f80(EEContext&);
void fn_sub_285F80_00285f80__recomp(EEContext&);
void fn_sub_285FA0_00285fa0(EEContext&);
void fn_sub_285FA0_00285fa0__recomp(EEContext&);
void fn_sub_286090_00286090(EEContext&);
void fn_sub_286090_00286090__recomp(EEContext&);
void fn_sub_2860B0_002860b0(EEContext&);
void fn_sub_2860B0_002860b0__recomp(EEContext&);
void fn_sub_286110_00286110(EEContext&);
void fn_sub_286110_00286110__recomp(EEContext&);
void fn_sub_286130_00286130(EEContext&);
void fn_sub_286130_00286130__recomp(EEContext&);
void fn_sub_286220_00286220(EEContext&);
void fn_sub_286220_00286220__recomp(EEContext&);
void fn_sub_286240_00286240(EEContext&);
void fn_sub_286240_00286240__recomp(EEContext&);
void fn_sub_2862A0_002862a0(EEContext&);
void fn_sub_2862A0_002862a0__recomp(EEContext&);
void fn_sub_2862C0_002862c0(EEContext&);
void fn_sub_2862C0_002862c0__recomp(EEContext&);
void fn_sub_286300_00286300(EEContext&);
void fn_sub_286300_00286300__recomp(EEContext&);
void fn_sub_286320_00286320(EEContext&);
void fn_sub_286320_00286320__recomp(EEContext&);
void fn_sub_287B20_00287b20(EEContext&);
void fn_sub_287B20_00287b20__recomp(EEContext&);
void fn_sub_287CF0_00287cf0(EEContext&);
void fn_sub_287CF0_00287cf0__recomp(EEContext&);
void fn_sub_2880E0_002880e0(EEContext&);
void fn_sub_2880E0_002880e0__recomp(EEContext&);
void fn_sub_288170_00288170(EEContext&);
void fn_sub_288170_00288170__recomp(EEContext&);
void fn_sub_288190_00288190(EEContext&);
void fn_sub_288190_00288190__recomp(EEContext&);
void fn_sub_288340_00288340(EEContext&);
void fn_sub_288340_00288340__recomp(EEContext&);
void fn_sub_288360_00288360(EEContext&);
void fn_sub_288360_00288360__recomp(EEContext&);
void fn_sub_288400_00288400(EEContext&);
void fn_sub_288400_00288400__recomp(EEContext&);
void fn_sub_288430_00288430(EEContext&);
void fn_sub_288430_00288430__recomp(EEContext&);
void fn_sub_2886B0_002886b0(EEContext&);
void fn_sub_2886B0_002886b0__recomp(EEContext&);
void fn_sub_2886E0_002886e0(EEContext&);
void fn_sub_2886E0_002886e0__recomp(EEContext&);
void fn_sub_288760_00288760(EEContext&);
void fn_sub_288760_00288760__recomp(EEContext&);
void fn_sub_288780_00288780(EEContext&);
void fn_sub_288780_00288780__recomp(EEContext&);
void fn_sub_288930_00288930(EEContext&);
void fn_sub_288930_00288930__recomp(EEContext&);
void fn_sub_288950_00288950(EEContext&);
void fn_sub_288950_00288950__recomp(EEContext&);
void fn_sub_288DA0_00288da0(EEContext&);
void fn_sub_288DA0_00288da0__recomp(EEContext&);
void fn_sub_288FE0_00288fe0(EEContext&);
void fn_sub_288FE0_00288fe0__recomp(EEContext&);
void fn_sub_289030_00289030(EEContext&);
void fn_sub_289030_00289030__recomp(EEContext&);
void fn_sub_2899E0_002899e0(EEContext&);
void fn_sub_2899E0_002899e0__recomp(EEContext&);
void fn_sub_289F40_00289f40(EEContext&);
void fn_sub_289F40_00289f40__recomp(EEContext&);
void fn_sub_28A0F0_0028a0f0(EEContext&);
void fn_sub_28A0F0_0028a0f0__recomp(EEContext&);
void fn_sub_28A200_0028a200(EEContext&);
void fn_sub_28A200_0028a200__recomp(EEContext&);
void fn_sub_28A3E0_0028a3e0(EEContext&);
void fn_sub_28A3E0_0028a3e0__recomp(EEContext&);
void fn_sub_28A540_0028a540(EEContext&);
void fn_sub_28A540_0028a540__recomp(EEContext&);
void fn_sub_28A780_0028a780(EEContext&);
void fn_sub_28A780_0028a780__recomp(EEContext&);
void fn_sub_28BA50_0028ba50(EEContext&);
void fn_sub_28BA50_0028ba50__recomp(EEContext&);
void fn_sub_297480_00297480(EEContext&);
void fn_sub_297480_00297480__recomp(EEContext&);
void fn_sub_297A50_00297a50(EEContext&);
void fn_sub_297A50_00297a50__recomp(EEContext&);
void fn_sub_298060_00298060(EEContext&);
void fn_sub_298060_00298060__recomp(EEContext&);
void fn_sub_299990_00299990(EEContext&);
void fn_sub_299990_00299990__recomp(EEContext&);
void fn_sub_29EA20_0029ea20(EEContext&);
void fn_sub_29EA20_0029ea20__recomp(EEContext&);
void fn_sub_29EA30_0029ea30(EEContext&);
void fn_sub_29EA30_0029ea30__recomp(EEContext&);
void fn_sub_29EA40_0029ea40(EEContext&);
void fn_sub_29EA40_0029ea40__recomp(EEContext&);
void fn_sub_29EA60_0029ea60(EEContext&);
void fn_sub_29EA60_0029ea60__recomp(EEContext&);
void fn_sub_29EC00_0029ec00(EEContext&);
void fn_sub_29EC00_0029ec00__recomp(EEContext&);
void fn_sub_29EC50_0029ec50(EEContext&);
void fn_sub_29EC50_0029ec50__recomp(EEContext&);
void fn_sub_29EC80_0029ec80(EEContext&);
void fn_sub_29EC80_0029ec80__recomp(EEContext&);
void fn_sub_29F4B0_0029f4b0(EEContext&);
void fn_sub_29F4B0_0029f4b0__recomp(EEContext&);
void fn_sub_29FA50_0029fa50(EEContext&);
void fn_sub_29FA50_0029fa50__recomp(EEContext&);
void fn_sub_2A5EE0_002a5ee0(EEContext&);
void fn_sub_2A5EE0_002a5ee0__recomp(EEContext&);
void fn_sub_2AC540_002ac540(EEContext&);
void fn_sub_2AC540_002ac540__recomp(EEContext&);
void fn_sub_2AF850_002af850(EEContext&);
void fn_sub_2AF850_002af850__recomp(EEContext&);
void fn_sub_2B8F90_002b8f90(EEContext&);
void fn_sub_2B8F90_002b8f90__recomp(EEContext&);
void fn_sub_2B9030_002b9030(EEContext&);
void fn_sub_2B9030_002b9030__recomp(EEContext&);
void fn_sub_2BB8F0_002bb8f0(EEContext&);
void fn_sub_2BB8F0_002bb8f0__recomp(EEContext&);
void fn_sub_2BBD00_002bbd00(EEContext&);
void fn_sub_2BBD00_002bbd00__recomp(EEContext&);
void fn_sub_2BD4F0_002bd4f0(EEContext&);
void fn_sub_2BD4F0_002bd4f0__recomp(EEContext&);
void fn_sub_2BD8E0_002bd8e0(EEContext&);
void fn_sub_2BD8E0_002bd8e0__recomp(EEContext&);
void fn_sub_2BF370_002bf370(EEContext&);
void fn_sub_2BF370_002bf370__recomp(EEContext&);
void fn_sub_2C0880_002c0880(EEContext&);
void fn_sub_2C0880_002c0880__recomp(EEContext&);
void fn_sub_2C08A0_002c08a0(EEContext&);
void fn_sub_2C08A0_002c08a0__recomp(EEContext&);
void fn_sub_2C0970_002c0970(EEContext&);
void fn_sub_2C0970_002c0970__recomp(EEContext&);
void fn_sub_2C09F0_002c09f0(EEContext&);
void fn_sub_2C09F0_002c09f0__recomp(EEContext&);
void fn_sub_2C0AC0_002c0ac0(EEContext&);
void fn_sub_2C0AC0_002c0ac0__recomp(EEContext&);
void fn_sub_2C0E30_002c0e30(EEContext&);
void fn_sub_2C0E30_002c0e30__recomp(EEContext&);
void fn_sub_2C0F40_002c0f40(EEContext&);
void fn_sub_2C0F40_002c0f40__recomp(EEContext&);
void fn_sub_2C12F0_002c12f0(EEContext&);
void fn_sub_2C12F0_002c12f0__recomp(EEContext&);
void fn_sub_2C13D0_002c13d0(EEContext&);
void fn_sub_2C13D0_002c13d0__recomp(EEContext&);
void fn_sub_2C1590_002c1590(EEContext&);
void fn_sub_2C1590_002c1590__recomp(EEContext&);
void fn_sub_2C1650_002c1650(EEContext&);
void fn_sub_2C1650_002c1650__recomp(EEContext&);
void fn_sub_2C16A0_002c16a0(EEContext&);
void fn_sub_2C16A0_002c16a0__recomp(EEContext&);
void fn_sub_2C1D90_002c1d90(EEContext&);
void fn_sub_2C1D90_002c1d90__recomp(EEContext&);
void fn_sub_2C1E10_002c1e10(EEContext&);
void fn_sub_2C1E10_002c1e10__recomp(EEContext&);
void fn_sub_2C1ED0_002c1ed0(EEContext&);
void fn_sub_2C1ED0_002c1ed0__recomp(EEContext&);
void fn_sub_2C24D0_002c24d0(EEContext&);
void fn_sub_2C24D0_002c24d0__recomp(EEContext&);
void fn_sub_2C3300_002c3300(EEContext&);
void fn_sub_2C3300_002c3300__recomp(EEContext&);
void fn_sub_2C3400_002c3400(EEContext&);
void fn_sub_2C3400_002c3400__recomp(EEContext&);
void fn_sub_2C3770_002c3770(EEContext&);
void fn_sub_2C3770_002c3770__recomp(EEContext&);
void fn_sub_2C48A0_002c48a0(EEContext&);
void fn_sub_2C48A0_002c48a0__recomp(EEContext&);
void fn_sub_2C6A00_002c6a00(EEContext&);
void fn_sub_2C6A00_002c6a00__recomp(EEContext&);
void fn_sub_2C6BA0_002c6ba0(EEContext&);
void fn_sub_2C6BA0_002c6ba0__recomp(EEContext&);
void fn_sub_2C6E30_002c6e30(EEContext&);
void fn_sub_2C6E30_002c6e30__recomp(EEContext&);
void fn_sub_2C7250_002c7250(EEContext&);
void fn_sub_2C7250_002c7250__recomp(EEContext&);
void fn_sub_2C7280_002c7280(EEContext&);
void fn_sub_2C7280_002c7280__recomp(EEContext&);
void fn_sub_2D0D00_002d0d00(EEContext&);
void fn_sub_2D0D00_002d0d00__recomp(EEContext&);
void fn_sub_2D1A70_002d1a70(EEContext&);
void fn_sub_2D1A70_002d1a70__recomp(EEContext&);
void fn_sub_2D2280_002d2280(EEContext&);
void fn_sub_2D2280_002d2280__recomp(EEContext&);
void fn_sub_2D2340_002d2340(EEContext&);
void fn_sub_2D2340_002d2340__recomp(EEContext&);
void fn_sub_2D2990_002d2990(EEContext&);
void fn_sub_2D2990_002d2990__recomp(EEContext&);
void fn_sub_2D3E00_002d3e00(EEContext&);
void fn_sub_2D3E00_002d3e00__recomp(EEContext&);
void fn_sub_2D4040_002d4040(EEContext&);
void fn_sub_2D4040_002d4040__recomp(EEContext&);
void fn_sub_2D4ED0_002d4ed0(EEContext&);
void fn_sub_2D4ED0_002d4ed0__recomp(EEContext&);
void fn_sub_2D50C0_002d50c0(EEContext&);
void fn_sub_2D50C0_002d50c0__recomp(EEContext&);
void fn_sub_2D5570_002d5570(EEContext&);
void fn_sub_2D5570_002d5570__recomp(EEContext&);
void fn_sub_2D56A0_002d56a0(EEContext&);
void fn_sub_2D56A0_002d56a0__recomp(EEContext&);
void fn_sub_2D6290_002d6290(EEContext&);
void fn_sub_2D6290_002d6290__recomp(EEContext&);
void fn_sub_2D6460_002d6460(EEContext&);
void fn_sub_2D6460_002d6460__recomp(EEContext&);
void fn_sub_2D7FB0_002d7fb0(EEContext&);
void fn_sub_2D7FB0_002d7fb0__recomp(EEContext&);
void fn_sub_2D8040_002d8040(EEContext&);
void fn_sub_2D8040_002d8040__recomp(EEContext&);
void fn_sub_2D8090_002d8090(EEContext&);
void fn_sub_2D8090_002d8090__recomp(EEContext&);
void fn_sub_2D8110_002d8110(EEContext&);
void fn_sub_2D8110_002d8110__recomp(EEContext&);
void fn_sub_2D8330_002d8330(EEContext&);
void fn_sub_2D8330_002d8330__recomp(EEContext&);
void fn_sub_2D8B40_002d8b40(EEContext&);
void fn_sub_2D8B40_002d8b40__recomp(EEContext&);
void fn_sub_2D8F70_002d8f70(EEContext&);
void fn_sub_2D8F70_002d8f70__recomp(EEContext&);
void fn_sub_2D9CA0_002d9ca0(EEContext&);
void fn_sub_2D9CA0_002d9ca0__recomp(EEContext&);
void fn_sub_2DB480_002db480(EEContext&);
void fn_sub_2DB480_002db480__recomp(EEContext&);
void fn_sub_2DB740_002db740(EEContext&);
void fn_sub_2DB740_002db740__recomp(EEContext&);
void fn_sub_2DB890_002db890(EEContext&);
void fn_sub_2DB890_002db890__recomp(EEContext&);
void fn_sub_2DBFE0_002dbfe0(EEContext&);
void fn_sub_2DBFE0_002dbfe0__recomp(EEContext&);
void fn_sub_2DC070_002dc070(EEContext&);
void fn_sub_2DC070_002dc070__recomp(EEContext&);
void fn_sub_2DC180_002dc180(EEContext&);
void fn_sub_2DC180_002dc180__recomp(EEContext&);
void fn_sub_2DD100_002dd100(EEContext&);
void fn_sub_2DD100_002dd100__recomp(EEContext&);
void fn_sub_2DD4A0_002dd4a0(EEContext&);
void fn_sub_2DD4A0_002dd4a0__recomp(EEContext&);
void fn_sub_2DD5E0_002dd5e0(EEContext&);
void fn_sub_2DD5E0_002dd5e0__recomp(EEContext&);
void fn_sub_2DDC10_002ddc10(EEContext&);
void fn_sub_2DDC10_002ddc10__recomp(EEContext&);
void fn_sub_2DDC80_002ddc80(EEContext&);
void fn_sub_2DDC80_002ddc80__recomp(EEContext&);
void fn_sub_2DE150_002de150(EEContext&);
void fn_sub_2DE150_002de150__recomp(EEContext&);
void fn_sub_2DE3C0_002de3c0(EEContext&);
void fn_sub_2DE3C0_002de3c0__recomp(EEContext&);
void fn_sub_2DE4E0_002de4e0(EEContext&);
void fn_sub_2DE4E0_002de4e0__recomp(EEContext&);
void fn_sub_2E2A10_002e2a10(EEContext&);
void fn_sub_2E2A10_002e2a10__recomp(EEContext&);
void fn_sub_2E2BE0_002e2be0(EEContext&);
void fn_sub_2E2BE0_002e2be0__recomp(EEContext&);
void fn_sub_2E2EC0_002e2ec0(EEContext&);
void fn_sub_2E2EC0_002e2ec0__recomp(EEContext&);
void fn_sub_2E38A0_002e38a0(EEContext&);
void fn_sub_2E38A0_002e38a0__recomp(EEContext&);
void fn_sub_2E3990_002e3990(EEContext&);
void fn_sub_2E3990_002e3990__recomp(EEContext&);
void fn_sub_2E3A90_002e3a90(EEContext&);
void fn_sub_2E3A90_002e3a90__recomp(EEContext&);
void fn_sub_2E3B50_002e3b50(EEContext&);
void fn_sub_2E3B50_002e3b50__recomp(EEContext&);
void fn_sub_2E3CD0_002e3cd0(EEContext&);
void fn_sub_2E3CD0_002e3cd0__recomp(EEContext&);
void fn_sub_2E3D10_002e3d10(EEContext&);
void fn_sub_2E3D10_002e3d10__recomp(EEContext&);
void fn_sub_2E42C0_002e42c0(EEContext&);
void fn_sub_2E42C0_002e42c0__recomp(EEContext&);
void fn_sub_2E4520_002e4520(EEContext&);
void fn_sub_2E4520_002e4520__recomp(EEContext&);
void fn_sub_2E4720_002e4720(EEContext&);
void fn_sub_2E4720_002e4720__recomp(EEContext&);
void fn_sub_2E47A0_002e47a0(EEContext&);
void fn_sub_2E47A0_002e47a0__recomp(EEContext&);
void fn_sub_2E4910_002e4910(EEContext&);
void fn_sub_2E4910_002e4910__recomp(EEContext&);
void fn_sub_2F6C50_002f6c50(EEContext&);
void fn_sub_2F6C50_002f6c50__recomp(EEContext&);
void fn_sub_2F9BC0_002f9bc0(EEContext&);
void fn_sub_2F9BC0_002f9bc0__recomp(EEContext&);
void fn_sub_2FA510_002fa510(EEContext&);
void fn_sub_2FA510_002fa510__recomp(EEContext&);
void fn_sub_2FB860_002fb860(EEContext&);
void fn_sub_2FB860_002fb860__recomp(EEContext&);
void fn_sub_2FC520_002fc520(EEContext&);
void fn_sub_2FC520_002fc520__recomp(EEContext&);
void fn_sub_2FCAA0_002fcaa0(EEContext&);
void fn_sub_2FCAA0_002fcaa0__recomp(EEContext&);
void fn_sub_2FD220_002fd220(EEContext&);
void fn_sub_2FD220_002fd220__recomp(EEContext&);
void fn_sub_2FD4A0_002fd4a0(EEContext&);
void fn_sub_2FD4A0_002fd4a0__recomp(EEContext&);
void fn_sub_2FD820_002fd820(EEContext&);
void fn_sub_2FD820_002fd820__recomp(EEContext&);
void fn_sub_2FDBB0_002fdbb0(EEContext&);
void fn_sub_2FDBB0_002fdbb0__recomp(EEContext&);
void fn_sub_2FDFE0_002fdfe0(EEContext&);
void fn_sub_2FDFE0_002fdfe0__recomp(EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(EEContext&);
void fn_datCalcGetMaxSp_00300100(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3, then $t0..$t2) -----------------------------------------
// A btlAction   R its AI target record (+136)  U btlUnit   D unit packet data (a unit at +0, another or a float at +4)
// T tint fade data   K skill banner data   P action packet data (the action at +0)   Q camera object (+224 an action)
// H effect handle   Y effect-object array   G effect-object group   W AI wait work   L u16 skill list
// k skill   e element   p AI parameter   x status mask   M side mask   s side   i unit id   u unit uid   m motion
// c AI command code / condition function   g small id 0..12   n small 0..7   f flags   C RGBA   F frames   E enemy id
// w EFFECT row   o an output buffer   v a vector
struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
};
const Case kCases[] = {
    {"sub_2821B0", 0x2821B0u, &rg::fn_sub_2821B0_002821b0, &rg::fn_sub_2821B0_002821b0__recomp, "D"},
    {"sub_282BC0", 0x282BC0u, &rg::fn_sub_282BC0_00282bc0, &rg::fn_sub_282BC0_00282bc0__recomp, "U"},
    {"sub_2835E0", 0x2835E0u, &rg::fn_sub_2835E0_002835e0, &rg::fn_sub_2835E0_002835e0__recomp, "Um"},
    {"sub_2838D0", 0x2838D0u, &rg::fn_sub_2838D0_002838d0, &rg::fn_sub_2838D0_002838d0__recomp, "Um"},
    {"sub_283A70", 0x283A70u, &rg::fn_sub_283A70_00283a70, &rg::fn_sub_283A70_00283a70__recomp, "Um"},
    {"sub_284040", 0x284040u, &rg::fn_sub_284040_00284040, &rg::fn_sub_284040_00284040__recomp, "nUkn"},
    {"sub_284C00", 0x284C00u, &rg::fn_sub_284C00_00284c00, &rg::fn_sub_284C00_00284c00__recomp, "D"},
    {"sub_285670", 0x285670u, &rg::fn_sub_285670_00285670, &rg::fn_sub_285670_00285670__recomp, "D"},
    {"sub_285690", 0x285690u, &rg::fn_sub_285690_00285690, &rg::fn_sub_285690_00285690__recomp, "Unn"},
    {"sub_285730", 0x285730u, &rg::fn_sub_285730_00285730, &rg::fn_sub_285730_00285730__recomp, "D"},
    {"sub_2857D0", 0x2857D0u, &rg::fn_sub_2857D0_002857d0, &rg::fn_sub_2857D0_002857d0__recomp, "D"},
    {"sub_2857F0", 0x2857F0u, &rg::fn_sub_2857F0_002857f0, &rg::fn_sub_2857F0_002857f0__recomp, "U"},
    {"sub_285860", 0x285860u, &rg::fn_sub_285860_00285860, &rg::fn_sub_285860_00285860__recomp, "D"},
    {"sub_285880", 0x285880u, &rg::fn_sub_285880_00285880, &rg::fn_sub_285880_00285880__recomp, "T"},
    {"sub_285D10", 0x285D10u, &rg::fn_sub_285D10_00285d10, &rg::fn_sub_285D10_00285d10__recomp, "D"},
    {"sub_285D30", 0x285D30u, &rg::fn_sub_285D30_00285d30, &rg::fn_sub_285D30_00285d30__recomp, "UCFFnf"},
    {"sub_285F80", 0x285F80u, &rg::fn_sub_285F80_00285f80, &rg::fn_sub_285F80_00285f80__recomp, "D"},
    {"sub_285FA0", 0x285FA0u, &rg::fn_sub_285FA0_00285fa0, &rg::fn_sub_285FA0_00285fa0__recomp, "D"},
    {"sub_286090", 0x286090u, &rg::fn_sub_286090_00286090, &rg::fn_sub_286090_00286090__recomp, "D"},
    {"sub_2860B0", 0x2860B0u, &rg::fn_sub_2860B0_002860b0, &rg::fn_sub_2860B0_002860b0__recomp, "U"},
    {"sub_286110", 0x286110u, &rg::fn_sub_286110_00286110, &rg::fn_sub_286110_00286110__recomp, "D"},
    {"sub_286130", 0x286130u, &rg::fn_sub_286130_00286130, &rg::fn_sub_286130_00286130__recomp, "D"},
    {"sub_286220", 0x286220u, &rg::fn_sub_286220_00286220, &rg::fn_sub_286220_00286220__recomp, "D"},
    {"sub_286240", 0x286240u, &rg::fn_sub_286240_00286240, &rg::fn_sub_286240_00286240__recomp, "U"},
    {"sub_2862A0", 0x2862A0u, &rg::fn_sub_2862A0_002862a0, &rg::fn_sub_2862A0_002862a0__recomp, "D"},
    {"sub_2862C0", 0x2862C0u, &rg::fn_sub_2862C0_002862c0, &rg::fn_sub_2862C0_002862c0__recomp, "D"},
    {"sub_286300", 0x286300u, &rg::fn_sub_286300_00286300, &rg::fn_sub_286300_00286300__recomp, "D"},
    {"sub_286320", 0x286320u, &rg::fn_sub_286320_00286320, &rg::fn_sub_286320_00286320__recomp, "U"},
    {"sub_287B20", 0x287B20u, &rg::fn_sub_287B20_00287b20, &rg::fn_sub_287B20_00287b20__recomp, "Ug"},
    {"sub_287CF0", 0x287CF0u, &rg::fn_sub_287CF0_00287cf0, &rg::fn_sub_287CF0_00287cf0__recomp, "Ug"},
    {"sub_2880E0", 0x2880E0u, &rg::fn_sub_2880E0_002880e0, &rg::fn_sub_2880E0_002880e0__recomp, "Un"},
    {"sub_288170", 0x288170u, &rg::fn_sub_288170_00288170, &rg::fn_sub_288170_00288170__recomp, "D"},
    {"sub_288190", 0x288190u, &rg::fn_sub_288190_00288190, &rg::fn_sub_288190_00288190__recomp, "D"},
    {"sub_288340", 0x288340u, &rg::fn_sub_288340_00288340, &rg::fn_sub_288340_00288340__recomp, "D"},
    {"sub_288360", 0x288360u, &rg::fn_sub_288360_00288360, &rg::fn_sub_288360_00288360__recomp, "Uvf"},
    {"sub_288400", 0x288400u, &rg::fn_sub_288400_00288400, &rg::fn_sub_288400_00288400__recomp, "D"},
    {"sub_288430", 0x288430u, &rg::fn_sub_288430_00288430, &rg::fn_sub_288430_00288430__recomp, "D"},
    {"sub_2886B0", 0x2886B0u, &rg::fn_sub_2886B0_002886b0, &rg::fn_sub_2886B0_002886b0__recomp, "D"},
    {"sub_2886E0", 0x2886E0u, &rg::fn_sub_2886E0_002886e0, &rg::fn_sub_2886E0_002886e0__recomp, "UUf"},
    {"sub_288760", 0x288760u, &rg::fn_sub_288760_00288760, &rg::fn_sub_288760_00288760__recomp, "D"},
    {"sub_288780", 0x288780u, &rg::fn_sub_288780_00288780, &rg::fn_sub_288780_00288780__recomp, "D"},
    {"sub_288930", 0x288930u, &rg::fn_sub_288930_00288930, &rg::fn_sub_288930_00288930__recomp, "D"},
    {"sub_288950", 0x288950u, &rg::fn_sub_288950_00288950, &rg::fn_sub_288950_00288950__recomp, "Uf"},
    {"sub_288DA0", 0x288DA0u, &rg::fn_sub_288DA0_00288da0, &rg::fn_sub_288DA0_00288da0__recomp, "Ug"},
    {"sub_288FE0", 0x288FE0u, &rg::fn_sub_288FE0_00288fe0, &rg::fn_sub_288FE0_00288fe0__recomp, "si"},
    {"sub_289030", 0x289030u, &rg::fn_sub_289030_00289030, &rg::fn_sub_289030_00289030__recomp, "u"},
    {"sub_2899E0", 0x2899E0u, &rg::fn_sub_2899E0_002899e0, &rg::fn_sub_2899E0_002899e0__recomp, "A"},
    {"sub_289F40", 0x289F40u, &rg::fn_sub_289F40_00289f40, &rg::fn_sub_289F40_00289f40__recomp, "A"},
    {"sub_28A0F0", 0x28A0F0u, &rg::fn_sub_28A0F0_0028a0f0, &rg::fn_sub_28A0F0_0028a0f0__recomp, "A"},
    {"sub_28A200", 0x28A200u, &rg::fn_sub_28A200_0028a200, &rg::fn_sub_28A200_0028a200__recomp, "A"},
    {"sub_28A3E0", 0x28A3E0u, &rg::fn_sub_28A3E0_0028a3e0, &rg::fn_sub_28A3E0_0028a3e0__recomp, "A"},
    {"sub_28A540", 0x28A540u, &rg::fn_sub_28A540_0028a540, &rg::fn_sub_28A540_0028a540__recomp, "Akoooo"},
    {"sub_28A780", 0x28A780u, &rg::fn_sub_28A780_0028a780, &rg::fn_sub_28A780_0028a780__recomp, "A"},
    {"sub_28BA50", 0x28BA50u, &rg::fn_sub_28BA50_0028ba50, &rg::fn_sub_28BA50_0028ba50__recomp, "A"},
    {"sub_297480", 0x297480u, &rg::fn_sub_297480_00297480, &rg::fn_sub_297480_00297480__recomp, "A"},
    {"sub_297A50", 0x297A50u, &rg::fn_sub_297A50_00297a50, &rg::fn_sub_297A50_00297a50__recomp, "A"},
    {"sub_298060", 0x298060u, &rg::fn_sub_298060_00298060, &rg::fn_sub_298060_00298060__recomp, "A"},
    {"sub_299990", 0x299990u, &rg::fn_sub_299990_00299990, &rg::fn_sub_299990_00299990__recomp, "A"},
    {"sub_29EA20", 0x29EA20u, &rg::fn_sub_29EA20_0029ea20, &rg::fn_sub_29EA20_0029ea20__recomp, ""},
    {"sub_29EA30", 0x29EA30u, &rg::fn_sub_29EA30_0029ea30, &rg::fn_sub_29EA30_0029ea30__recomp, ""},
    {"sub_29EA40", 0x29EA40u, &rg::fn_sub_29EA40_0029ea40, &rg::fn_sub_29EA40_0029ea40__recomp, ""},
    {"sub_29EA60", 0x29EA60u, &rg::fn_sub_29EA60_0029ea60, &rg::fn_sub_29EA60_0029ea60__recomp, "woo"},
    {"sub_29EC00", 0x29EC00u, &rg::fn_sub_29EC00_0029ec00, &rg::fn_sub_29EC00_0029ec00__recomp, "w"},
    {"sub_29EC50", 0x29EC50u, &rg::fn_sub_29EC50_0029ec50, &rg::fn_sub_29EC50_0029ec50__recomp, "w"},
    {"sub_29EC80", 0x29EC80u, &rg::fn_sub_29EC80_0029ec80, &rg::fn_sub_29EC80_0029ec80__recomp, "woo"},
    {"sub_29F4B0", 0x29F4B0u, &rg::fn_sub_29F4B0_0029f4b0, &rg::fn_sub_29F4B0_0029f4b0__recomp, "CCF"},
    {"sub_29FA50", 0x29FA50u, &rg::fn_sub_29FA50_0029fa50, &rg::fn_sub_29FA50_0029fa50__recomp, "F"},
    {"sub_2A5EE0", 0x2A5EE0u, &rg::fn_sub_2A5EE0_002a5ee0, &rg::fn_sub_2A5EE0_002a5ee0__recomp, "Q"},
    {"sub_2AC540", 0x2AC540u, &rg::fn_sub_2AC540_002ac540, &rg::fn_sub_2AC540_002ac540__recomp, "Q"},
    {"sub_2AF850", 0x2AF850u, &rg::fn_sub_2AF850_002af850, &rg::fn_sub_2AF850_002af850__recomp, "Q"},
    {"sub_2B8F90", 0x2B8F90u, &rg::fn_sub_2B8F90_002b8f90, &rg::fn_sub_2B8F90_002b8f90__recomp, "n"},
    {"sub_2B9030", 0x2B9030u, &rg::fn_sub_2B9030_002b9030, &rg::fn_sub_2B9030_002b9030__recomp, "H"},
    {"sub_2BB8F0", 0x2BB8F0u, &rg::fn_sub_2BB8F0_002bb8f0, &rg::fn_sub_2BB8F0_002bb8f0__recomp, "Y"},
    {"sub_2BBD00", 0x2BBD00u, &rg::fn_sub_2BBD00_002bbd00, &rg::fn_sub_2BBD00_002bbd00__recomp, "G"},
    {"sub_2BD4F0", 0x2BD4F0u, &rg::fn_sub_2BD4F0_002bd4f0, &rg::fn_sub_2BD4F0_002bd4f0__recomp, "K"},
    {"sub_2BD8E0", 0x2BD8E0u, &rg::fn_sub_2BD8E0_002bd8e0, &rg::fn_sub_2BD8E0_002bd8e0__recomp, "D"},
    {"sub_2BF370", 0x2BF370u, &rg::fn_sub_2BF370_002bf370, &rg::fn_sub_2BF370_002bf370__recomp, "n"},
    {"sub_2C0880", 0x2C0880u, &rg::fn_sub_2C0880_002c0880, &rg::fn_sub_2C0880_002c0880__recomp, "R"},
    {"sub_2C08A0", 0x2C08A0u, &rg::fn_sub_2C08A0_002c08a0, &rg::fn_sub_2C08A0_002c08a0__recomp, "Ro"},
    {"sub_2C0970", 0x2C0970u, &rg::fn_sub_2C0970_002c0970, &rg::fn_sub_2C0970_002c0970__recomp, "R"},
    {"sub_2C09F0", 0x2C09F0u, &rg::fn_sub_2C09F0_002c09f0, &rg::fn_sub_2C09F0_002c09f0__recomp, "R"},
    {"sub_2C0AC0", 0x2C0AC0u, &rg::fn_sub_2C0AC0_002c0ac0, &rg::fn_sub_2C0AC0_002c0ac0__recomp, "AR"},
    {"sub_2C0E30", 0x2C0E30u, &rg::fn_sub_2C0E30_002c0e30, &rg::fn_sub_2C0E30_002c0e30__recomp, "iMx"},
    {"sub_2C0F40", 0x2C0F40u, &rg::fn_sub_2C0F40_002c0f40, &rg::fn_sub_2C0F40_002c0f40__recomp, "ApxMnco"},
    {"sub_2C12F0", 0x2C12F0u, &rg::fn_sub_2C12F0_002c12f0, &rg::fn_sub_2C12F0_002c12f0__recomp, "Ap"},
    {"sub_2C13D0", 0x2C13D0u, &rg::fn_sub_2C13D0_002c13d0, &rg::fn_sub_2C13D0_002c13d0__recomp, "Ap"},
    {"sub_2C1590", 0x2C1590u, &rg::fn_sub_2C1590_002c1590, &rg::fn_sub_2C1590_002c1590__recomp, "Ap"},
    {"sub_2C1650", 0x2C1650u, &rg::fn_sub_2C1650_002c1650, &rg::fn_sub_2C1650_002c1650__recomp, "Ap"},
    {"sub_2C16A0", 0x2C16A0u, &rg::fn_sub_2C16A0_002c16a0, &rg::fn_sub_2C16A0_002c16a0__recomp, "Ap"},
    {"sub_2C1D90", 0x2C1D90u, &rg::fn_sub_2C1D90_002c1d90, &rg::fn_sub_2C1D90_002c1d90__recomp, "A"},
    {"sub_2C1E10", 0x2C1E10u, &rg::fn_sub_2C1E10_002c1e10, &rg::fn_sub_2C1E10_002c1e10__recomp, "Ae"},
    {"sub_2C1ED0", 0x2C1ED0u, &rg::fn_sub_2C1ED0_002c1ed0, &rg::fn_sub_2C1ED0_002c1ed0__recomp, "Ae"},
    {"sub_2C24D0", 0x2C24D0u, &rg::fn_sub_2C24D0_002c24d0, &rg::fn_sub_2C24D0_002c24d0__recomp, "Ap"},
    {"sub_2C3300", 0x2C3300u, &rg::fn_sub_2C3300_002c3300, &rg::fn_sub_2C3300_002c3300__recomp, "Ap"},
    {"sub_2C3400", 0x2C3400u, &rg::fn_sub_2C3400_002c3400, &rg::fn_sub_2C3400_002c3400__recomp, "Ax"},
    {"sub_2C3770", 0x2C3770u, &rg::fn_sub_2C3770_002c3770, &rg::fn_sub_2C3770_002c3770__recomp, "A"},
    {"sub_2C48A0", 0x2C48A0u, &rg::fn_sub_2C48A0_002c48a0, &rg::fn_sub_2C48A0_002c48a0__recomp, "AALnn"},
    {"sub_2C6A00", 0x2C6A00u, &rg::fn_sub_2C6A00_002c6a00, &rg::fn_sub_2C6A00_002c6a00__recomp, "Aoc"},
    {"sub_2C6BA0", 0x2C6BA0u, &rg::fn_sub_2C6BA0_002c6ba0, &rg::fn_sub_2C6BA0_002c6ba0__recomp, "A"},
    {"sub_2C6E30", 0x2C6E30u, &rg::fn_sub_2C6E30_002c6e30, &rg::fn_sub_2C6E30_002c6e30__recomp, "An"},
    {"sub_2C7250", 0x2C7250u, &rg::fn_sub_2C7250_002c7250, &rg::fn_sub_2C7250_002c7250__recomp, "W"},
    {"sub_2C7280", 0x2C7280u, &rg::fn_sub_2C7280_002c7280, &rg::fn_sub_2C7280_002c7280__recomp, "W"},
    {"sub_2D0D00", 0x2D0D00u, &rg::fn_sub_2D0D00_002d0d00, &rg::fn_sub_2D0D00_002d0d00__recomp, ""},
    {"sub_2D1A70", 0x2D1A70u, &rg::fn_sub_2D1A70_002d1a70, &rg::fn_sub_2D1A70_002d1a70__recomp, ""},
    {"sub_2D2280", 0x2D2280u, &rg::fn_sub_2D2280_002d2280, &rg::fn_sub_2D2280_002d2280__recomp, "oov"},
    {"sub_2D2340", 0x2D2340u, &rg::fn_sub_2D2340_002d2340, &rg::fn_sub_2D2340_002d2340__recomp, "Unn"},
    {"sub_2D2990", 0x2D2990u, &rg::fn_sub_2D2990_002d2990, &rg::fn_sub_2D2990_002d2990__recomp, "vvv"},
    {"sub_2D3E00", 0x2D3E00u, &rg::fn_sub_2D3E00_002d3e00, &rg::fn_sub_2D3E00_002d3e00__recomp, "Uo"},
    {"sub_2D4040", 0x2D4040u, &rg::fn_sub_2D4040_002d4040, &rg::fn_sub_2D4040_002d4040__recomp, "U"},
    {"sub_2D4ED0", 0x2D4ED0u, &rg::fn_sub_2D4ED0_002d4ed0, &rg::fn_sub_2D4ED0_002d4ed0__recomp, "A"},
    {"sub_2D50C0", 0x2D50C0u, &rg::fn_sub_2D50C0_002d50c0, &rg::fn_sub_2D50C0_002d50c0__recomp, ""},
    {"sub_2D5570", 0x2D5570u, &rg::fn_sub_2D5570_002d5570, &rg::fn_sub_2D5570_002d5570__recomp, "E"},
    {"sub_2D56A0", 0x2D56A0u, &rg::fn_sub_2D56A0_002d56a0, &rg::fn_sub_2D56A0_002d56a0__recomp, "E"},
    {"sub_2D6290", 0x2D6290u, &rg::fn_sub_2D6290_002d6290, &rg::fn_sub_2D6290_002d6290__recomp, "AR"},
    {"sub_2D6460", 0x2D6460u, &rg::fn_sub_2D6460_002d6460, &rg::fn_sub_2D6460_002d6460__recomp, "Aonnn"},
    {"sub_2D7FB0", 0x2D7FB0u, &rg::fn_sub_2D7FB0_002d7fb0, &rg::fn_sub_2D7FB0_002d7fb0__recomp, "An"},
    {"sub_2D8040", 0x2D8040u, &rg::fn_sub_2D8040_002d8040, &rg::fn_sub_2D8040_002d8040__recomp, "P"},
    {"sub_2D8090", 0x2D8090u, &rg::fn_sub_2D8090_002d8090, &rg::fn_sub_2D8090_002d8090__recomp, "A"},
    {"sub_2D8110", 0x2D8110u, &rg::fn_sub_2D8110_002d8110, &rg::fn_sub_2D8110_002d8110__recomp, "P"},
    {"sub_2D8330", 0x2D8330u, &rg::fn_sub_2D8330_002d8330, &rg::fn_sub_2D8330_002d8330__recomp, "A"},
    {"sub_2D8B40", 0x2D8B40u, &rg::fn_sub_2D8B40_002d8b40, &rg::fn_sub_2D8B40_002d8b40__recomp, "A"},
    {"sub_2D8F70", 0x2D8F70u, &rg::fn_sub_2D8F70_002d8f70, &rg::fn_sub_2D8F70_002d8f70__recomp, "A"},
    {"sub_2D9CA0", 0x2D9CA0u, &rg::fn_sub_2D9CA0_002d9ca0, &rg::fn_sub_2D9CA0_002d9ca0__recomp, "A"},
    {"sub_2DB480", 0x2DB480u, &rg::fn_sub_2DB480_002db480, &rg::fn_sub_2DB480_002db480__recomp, ""},
    {"sub_2DB740", 0x2DB740u, &rg::fn_sub_2DB740_002db740, &rg::fn_sub_2DB740_002db740__recomp, "Annnn"},
    {"sub_2DB890", 0x2DB890u, &rg::fn_sub_2DB890_002db890, &rg::fn_sub_2DB890_002db890__recomp, ""},
    {"sub_2DBFE0", 0x2DBFE0u, &rg::fn_sub_2DBFE0_002dbfe0, &rg::fn_sub_2DBFE0_002dbfe0__recomp, "n"},
    {"sub_2DC070", 0x2DC070u, &rg::fn_sub_2DC070_002dc070, &rg::fn_sub_2DC070_002dc070__recomp, "A"},
    {"sub_2DC180", 0x2DC180u, &rg::fn_sub_2DC180_002dc180, &rg::fn_sub_2DC180_002dc180__recomp, "A"},
    {"sub_2DD100", 0x2DD100u, &rg::fn_sub_2DD100_002dd100, &rg::fn_sub_2DD100_002dd100__recomp, "nnn"},
    {"sub_2DD4A0", 0x2DD4A0u, &rg::fn_sub_2DD4A0_002dd4a0, &rg::fn_sub_2DD4A0_002dd4a0__recomp, "nn"},
    {"sub_2DD5E0", 0x2DD5E0u, &rg::fn_sub_2DD5E0_002dd5e0, &rg::fn_sub_2DD5E0_002dd5e0__recomp, "n"},
    {"sub_2DDC10", 0x2DDC10u, &rg::fn_sub_2DDC10_002ddc10, &rg::fn_sub_2DDC10_002ddc10__recomp, "g"},
    {"sub_2DDC80", 0x2DDC80u, &rg::fn_sub_2DDC80_002ddc80, &rg::fn_sub_2DDC80_002ddc80__recomp, "g"},
    {"sub_2DE150", 0x2DE150u, &rg::fn_sub_2DE150_002de150, &rg::fn_sub_2DE150_002de150__recomp, "A"},
    {"sub_2DE3C0", 0x2DE3C0u, &rg::fn_sub_2DE3C0_002de3c0, &rg::fn_sub_2DE3C0_002de3c0__recomp, "A"},
    {"sub_2DE4E0", 0x2DE4E0u, &rg::fn_sub_2DE4E0_002de4e0, &rg::fn_sub_2DE4E0_002de4e0__recomp, "A"},
    {"sub_2E2A10", 0x2E2A10u, &rg::fn_sub_2E2A10_002e2a10, &rg::fn_sub_2E2A10_002e2a10__recomp, ""},
    {"sub_2E2BE0", 0x2E2BE0u, &rg::fn_sub_2E2BE0_002e2be0, &rg::fn_sub_2E2BE0_002e2be0__recomp, "Annnn"},
    {"sub_2E2EC0", 0x2E2EC0u, &rg::fn_sub_2E2EC0_002e2ec0, &rg::fn_sub_2E2EC0_002e2ec0__recomp, "n"},
    {"sub_2E38A0", 0x2E38A0u, &rg::fn_sub_2E38A0_002e38a0, &rg::fn_sub_2E38A0_002e38a0__recomp, "n"},
    {"sub_2E3990", 0x2E3990u, &rg::fn_sub_2E3990_002e3990, &rg::fn_sub_2E3990_002e3990__recomp, ""},
    {"sub_2E3A90", 0x2E3A90u, &rg::fn_sub_2E3A90_002e3a90, &rg::fn_sub_2E3A90_002e3a90__recomp, ""},
    {"sub_2E3B50", 0x2E3B50u, &rg::fn_sub_2E3B50_002e3b50, &rg::fn_sub_2E3B50_002e3b50__recomp, "ggg"},
    {"sub_2E3CD0", 0x2E3CD0u, &rg::fn_sub_2E3CD0_002e3cd0, &rg::fn_sub_2E3CD0_002e3cd0__recomp, ""},
    {"sub_2E3D10", 0x2E3D10u, &rg::fn_sub_2E3D10_002e3d10, &rg::fn_sub_2E3D10_002e3d10__recomp, ""},
    {"sub_2E42C0", 0x2E42C0u, &rg::fn_sub_2E42C0_002e42c0, &rg::fn_sub_2E42C0_002e42c0__recomp, ""},
    {"sub_2E4520", 0x2E4520u, &rg::fn_sub_2E4520_002e4520, &rg::fn_sub_2E4520_002e4520__recomp, "Akn"},
    {"sub_2E4720", 0x2E4720u, &rg::fn_sub_2E4720_002e4720, &rg::fn_sub_2E4720_002e4720__recomp, "g"},
    {"sub_2E47A0", 0x2E47A0u, &rg::fn_sub_2E47A0_002e47a0, &rg::fn_sub_2E47A0_002e47a0__recomp, "Ak"},
    {"sub_2E4910", 0x2E4910u, &rg::fn_sub_2E4910_002e4910, &rg::fn_sub_2E4910_002e4910__recomp, "Ak"},
    {"sub_2F6C50", 0x2F6C50u, &rg::fn_sub_2F6C50_002f6c50, &rg::fn_sub_2F6C50_002f6c50__recomp, "E"},
    {"sub_2F9BC0", 0x2F9BC0u, &rg::fn_sub_2F9BC0_002f9bc0, &rg::fn_sub_2F9BC0_002f9bc0__recomp, ""},
    {"sub_2FA510", 0x2FA510u, &rg::fn_sub_2FA510_002fa510, &rg::fn_sub_2FA510_002fa510__recomp, "An"},
    {"sub_2FB860", 0x2FB860u, &rg::fn_sub_2FB860_002fb860, &rg::fn_sub_2FB860_002fb860__recomp, "Um"},
    {"sub_2FC520", 0x2FC520u, &rg::fn_sub_2FC520_002fc520, &rg::fn_sub_2FC520_002fc520__recomp, "U"},
    {"sub_2FCAA0", 0x2FCAA0u, &rg::fn_sub_2FCAA0_002fcaa0, &rg::fn_sub_2FCAA0_002fcaa0__recomp, "Ao"},
    {"sub_2FD220", 0x2FD220u, &rg::fn_sub_2FD220_002fd220, &rg::fn_sub_2FD220_002fd220__recomp, "AA"},
    {"sub_2FD4A0", 0x2FD4A0u, &rg::fn_sub_2FD4A0_002fd4a0, &rg::fn_sub_2FD4A0_002fd4a0__recomp, ""},
    {"sub_2FD820", 0x2FD820u, &rg::fn_sub_2FD820_002fd820, &rg::fn_sub_2FD820_002fd820__recomp, ""},
    {"sub_2FDBB0", 0x2FDBB0u, &rg::fn_sub_2FDBB0_002fdbb0, &rg::fn_sub_2FDBB0_002fdbb0__recomp, "AU"},
    {"sub_2FDFE0", 0x2FDFE0u, &rg::fn_sub_2FDFE0_002fdfe0, &rg::fn_sub_2FDFE0_002fdfe0__recomp, "Q"},
};

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u8* ram(Machine& m, u32 va) { return m.at(std::min<u32>(va & 0x1FFFFFFu, 0x2000000u - 8)); }
void st8(Machine& m, u32 va, u8 v) { *ram(m, va) = v; }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(ram(m, va), &v, 2); }
void st32(Machine& m, u32 va, u32 v) { std::memcpy(ram(m, va), &v, 4); }
void stf(Machine& m, u32 va, float v) { std::memcpy(ram(m, va), &v, 4); }
u8 ld8(Machine& m, u32 va) { return *ram(m, va); }
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, ram(m, va), 2);
    return v;
}
u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }
bool in_ram(u32 va) { return va >= 0x100000u && va < 0x2000000u; }

constexpr u32 kGBtlSlot = 0x7CE3ECu;
constexpr u32 kSkillTblSlot = 0x7CE3F8u;
constexpr u32 kAiWeights = 0x696FA0u;  // sub_2C3770's weights by candidate count: 4 rows of 4 bytes
// Free guest memory for the blocks a test builds (zero in every replay snapshot; the stand-in heap allocates from
// kStandInHeap upwards and never gets this far in these pairs).
constexpr u32 kScratch = kStandInHeap + 0x2C0000u;

// The stand-ins: heap, printf, sprintf, H_Cdvd, and recorders for the callees the test build does not emit that the
// bodies reach on the battle worlds (both bodies meet the same recorder; its log is compared).
const u32 kRecorded[] = {0x324BD0u, 0x2E3AE0u, 0x2DCFB0u, 0x242600u, 0x2B94F0u, 0x316F70u, 0x4F7560u, 0x242720u, 0x25BE60u};
void b3_setup(StandInWorld& w) {
    install_standard(w);
    for (u32 va : kRecorded) w.si.install_recorder(va, "rec_" + hex64(va), 0, 4);
}

// --- stand-ins and the pair -----------------------------------------------------------------------------------------
StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}
// hgp::pair (everything at every check point, the end / stop, all RAM, scratchpad, BIOS, bus) with a fresh stand-in
// world around each body (heap, printf, sprintf, H_Cdvd) and the two call logs compared. Returns the recompiled run.
hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b3_setup(*wh);
    b3_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    return r;
}
// hgp::pair's comparison on a long-lived BaseRange (write_tracker.h) instead of a PairRange per pair: the snapshot
// world's 32 MiB stay the base and restore() copies back only the pages a pair wrote. Same checks as hgp::pair.
hgp::Run pair_base(Machine& m, BaseRange& ram, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b3_setup(*wh);
    b3_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, &thunk0, args, seed, hw);
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, &thunk1, args, seed, hw);
    const bool bios_r = !hgp::bios_clean(m);
    INFO(what << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " a3=" << hex64(args[3])
              << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string())
              << (h.stopped ? " (hand stopped: " + h.what + " at " + hex64(h.stop_pc) + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                                  << unsigned(m.mem.main_ram()[first]));
        CHECK(false);
    }
    CHECK(h.spr == r.spr);
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto &x = h.bus[i], &y = r.bus[i];
        if (x.write != y.write || x.bits != y.bits || x.pa != y.pa || x.lo != y.lo || x.hi != y.hi) {
            INFO("bus access " << i << " differs");
            CHECK(false);
            break;
        }
    }
    CHECK(h.vu_control == r.vu_control);
    expect_same_log(wh->si, wr->si, what);
    return r;
}
// One body alone (the rule checks) with its own stand-in world.
hgp::Run solo(Machine& m, Fn fn, const Args& args, const HwCheck& hw = {}) {
    auto w = std::make_unique<StandInWorld>();
    b3_setup(*w);
    g_si[0] = w.get();
    g_fn[0] = fn;
    return hgp::run_one(m, &thunk0, args, 1, hw);
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

std::unique_ptr<Machine> new_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

// --- the battle objects of a snapshot -------------------------------------------------------------------------------
struct Objects {
    u32 btl = 0;
    std::vector<u32> acts, units, dats, data;  // data: the packets' data blocks
    std::vector<u16> ids;
    std::vector<u32> uids;
};
Objects objects_of(Machine& m) {
    Objects o;
    o.btl = ld32(m, kGBtlSlot);
    if (!in_ram(o.btl)) {
        o.btl = 0;
        return o;
    }
    for (u32 a = ld32(m, o.btl + b3::gbtl::kActionList), n = 0; in_ram(a) && n < 32; a = ld32(m, a + b3::act::kNext), ++n)
        o.acts.push_back(a);
    for (u32 s = 0; s < 4; ++s)
        for (u32 u = ld32(m, o.btl + b3::gbtl::kUnitHead0 + 8 * s), n = 0; in_ram(u) && n < 32; u = ld32(m, u + b3::unit::kNext), ++n) {
            o.units.push_back(u);
            o.ids.push_back(ld16(m, u + b3::unit::kId));
            o.uids.push_back(ld32(m, u + b3::unit::kUid));
            if (const u32 d = ld32(m, u + b3::unit::kDat); in_ram(d)) o.dats.push_back(d);
        }
    for (u32 q = 0; q < 4; ++q)
        for (u32 p = ld32(m, o.btl + b3::gbtl::kPktHead0 + 8 * q), n = 0; in_ram(p) && n < 64; p = ld32(m, p + b3::pkt::kNext), ++n)
            if (const u32 d = ld32(m, p + b3::pkt::kData); in_ram(d)) o.data.push_back(d);
    return o;
}
template <class T>
T pick(const std::vector<T>& v, std::mt19937& rng, T fallback) {
    return v.empty() ? fallback : v[rng() % v.size()];
}

// The perturbations of one battle-world pair: the bad-status words and HP of a few DatUnits, the encounter id, a boss
// id on one enemy unit, the advantage word, the effect requests, the AI wait work.
void perturb(Machine& m, const Objects& o, std::mt19937& rng) {
    static const u32 kStatus[] = {0x100000u, 0x80000u, 0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x100u, 0x200u, 0x261u};
    for (u32 d : o.dats) {
        if (chance(rng, 35)) st32(m, d + b3::dat::kStatus, chance(rng, 50) ? 0 : kStatus[rng() % 12] | (chance(rng, 20) ? kStatus[rng() % 12] : 0));
        if (chance(rng, 20)) st16(m, d + b3::dat::kHp, static_cast<u16>(chance(rng, 30) ? 0 : 1 + rng() % 400));
    }
    if (!o.btl) return;
    if (chance(rng, 40)) {
        static const u16 kEnc[] = {417, 420, 421, 422, 423, 424, 428, 429, 433, 434, 435, 436, 468, 469, 506};
        if (const u32 g = ld32(m, o.btl + b3::gbtl::kSetupEnemies); in_ram(g)) st16(m, g + 8, kEnc[rng() % 15]);
    }
    if (chance(rng, 30) && !o.units.empty()) {
        static const u16 kBoss[] = {233, 234, 235, 241, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269,
                                    271, 272, 274, 277, 278, 279, 280, 281, 294, 295};
        const u32 u = o.units[rng() % o.units.size()];
        if (ld8(m, u + b3::unit::kSide) == 1) st16(m, u + b3::unit::kId, kBoss[rng() % 28]);
    }
    if (chance(rng, 30)) st16(m, o.btl + b3::gbtl::kAdvantage, static_cast<u16>(rng() % 3));
    if (chance(rng, 30)) {
        st16(m, o.btl + b3::gbtl::kFxRequest, static_cast<u16>(rng() & 0x3F));
        st32(m, o.btl + b3::gbtl::kFlags, ld32(m, o.btl + b3::gbtl::kFlags) | 0x400000u);
    }
    if (chance(rng, 30)) st16(m, o.btl + b3::gbtl::kEscRowA, static_cast<u16>(rng() % 12));
    if (chance(rng, 30)) st16(m, o.btl + b3::gbtl::kEscRowB, static_cast<u16>(rng() % 8));
}

// Builds the argument blocks in the scratch area and returns the value for one kind.
u64 arg_of(Machine& m, char kind, const Objects& o, std::mt19937& rng, u32& blk) {
    auto block = [&](u32 size) {
        const u32 b = kScratch + blk;
        blk += (size + 15) & ~15u;
        for (u32 i = 0; i < size; i += 4) st32(m, b + i, chance(rng, 60) ? 0 : rng() % 64);
        return b;
    };
    const u32 act = pick(o.acts, rng, 0u), unit = pick(o.units, rng, 0u);
    switch (kind) {
    case 'A': return sx(act);
    case 'R': return sx(act ? act + b3::act::kTargetRec : 0);
    case 'U': return sx(unit);
    case 'D': {
        const u32 b = block(64);
        st32(m, b, unit);
        if (chance(rng, 50)) st32(m, b + 4, pick(o.units, rng, 0u));
        else stf(m, b + 4, static_cast<float>(static_cast<int>(rng() % 400) - 200));
        return sx(b);
    }
    case 'T': {  // the tint fade packet's data: unit, start, target, durations, mode, flags, frame
        const u32 b = block(20);
        st32(m, b, unit);
        st32(m, b + 4, rng());
        st32(m, b + 8, rng());
        st16(m, b + 12, static_cast<u16>(rng() % 20));
        st16(m, b + 14, static_cast<u16>(rng() % 20));
        st8(m, b + 16, static_cast<u8>(rng() % 6));
        st8(m, b + 17, static_cast<u8>(rng() & 0xF));
        st16(m, b + 18, static_cast<u16>(rng() % 45));
        return sx(b);
    }
    case 'K': {
        const u32 b = block(16);
        st16(m, b + 4, static_cast<u16>(rng() % 464));
        st32(m, b + 8, rng() % 50);
        return sx(b);
    }
    case 'P': {
        const u32 b = block(16);
        st32(m, b, act);
        return sx(b);
    }
    case 'Q': {
        const u32 b = block(288);
        st32(m, b + 224, act);
        return sx(b);
    }
    case 'H': {
        const u32 b = block(1600);
        st16(m, b + 1584, static_cast<u16>(rng() % 16));
        st16(m, b + 1586, static_cast<u16>(1 + rng() % 3));
        return sx(b);
    }
    case 'Y': {  // 48 effect objects (zeroed 64-byte records: no links)
        const u32 arr = block(48 * 4);
        for (u32 i = 0; i < 48; ++i) {
            const u32 obj = block(64);
            std::memset(m.at(obj), 0, 64);
            st32(m, arr + 4 * i, obj);
        }
        return sx(arr);
    }
    case 'G': {  // an effect-object group: +8 the object, +12 a handle or 0
        const u32 g = block(32), obj = block(64);
        std::memset(m.at(obj), 0, 64);
        st32(m, g + 8, obj);
        st32(m, g + 12, 0);
        if (chance(rng, 50)) {
            const u32 h = block(1600);
            st16(m, h + 1584, static_cast<u16>(rng() % 16));
            st16(m, h + 1586, static_cast<u16>(2 + rng() % 3));
            st32(m, g + 12, h);
        }
        return sx(g);
    }
    case 'W': {
        const u32 b = block(96);
        st8(m, b + 48, static_cast<u8>(rng() % 2));
        st32(m, b + 76, chance(rng, 50) ? 0 : b);
        return sx(b);
    }
    case 'L': {
        const u32 b = block(16);
        for (u32 i = 0; i < 8; ++i) st16(m, b + 2 * i, static_cast<u16>(chance(rng, 15) ? 0 : rng() % 464));
        return sx(b);
    }
    case 'k': return chance(rng, 5) ? sx(0xFFFFFFFFu) : rng() % (chance(rng, 90) ? 464 : 624);
    case 'e': return sx(static_cast<u32>(static_cast<int>(rng() % 20) - 1));
    case 'p': return rng() % 120;
    case 'x': {
        static const u32 kMasks[] = {0u, 0x80000u, 0x100000u, 0x100261u, 0x180000u, 0xFFFFFu, 0x4u};
        return kMasks[rng() % 7];
    }
    case 'M': return 1 + rng() % 15;
    case 's': return rng() % 4;
    case 'i': return chance(rng, 80) ? pick(o.ids, rng, u16{1}) : rng() % 340;
    case 'u': return chance(rng, 80) ? pick(o.uids, rng, 0u) : rng() % 0x400;
    case 'm': return rng() % 26;
    case 'c': {
        static const u32 kCodes[] = {0x8000u, 0x8001u, 0x8002u, 0x8004u, 0x8005u, 0x8006u, 0x8007u, 0x8008u, 0x1155u, 0x2003u};
        if (chance(rng, 70)) return kCodes[rng() % 10];
        return rng() % 464;
    }
    case 'g': return rng() % 13;
    case 'n': return rng() % 8;
    case 'f': return rng() & 0x3F;
    case 'C': return rng();
    case 'F': return rng() % 60;
    case 'E': return 200 + rng() % 140;
    case 'w': return rng() % 464;
    case 'o': return sx(block(64));
    case 'v': {
        const u32 b = block(16);
        for (u32 i = 0; i < 3; ++i) stf(m, b + 4 * i, static_cast<float>(static_cast<int>(rng() % 3600) - 1800) / 1.5f);
        return sx(b);
    }
    default: return rng() % 8;
    }
}

// a0..a3 in Args; $t0..$t2 through HwCheck::gpr_in (for 'c' in $t1: a condition function of the table 0x6971B0).
void args_for(Machine& m, const Case& c, const Objects& o, std::mt19937& rng, Args& a, HwCheck& hw) {
    u32 blk = 0;
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 7; ++i) {
        u64 v = i < n ? arg_of(m, c.kinds[i], o, rng, blk) : rng() % 8;
        if (i == 5 && i < n && c.kinds[i] == 'c') {
            static const u32 kConds[] = {0x2C12F0u, 0x2C13D0u, 0x2C24D0u, 0x2C3400u, 0x2C1D90u};
            v = kConds[rng() % 5];
        }
        if (i < 4) a[i] = v;
        else hw.gpr_in[GPR_T0 + (i - 4)] = v;
    }
}

// b_5800: the first battle in state ACTION (4 actions, 7 units, 15 packets) -- most pairs; battle_ref_6150 / b_6150:
// the battle over (RESULT, empty lists); b_6300 / b_6700 / climb_ref_17000: no battle (gBtl 0): the null paths.
struct Snap {
    const char* dir;
    u32 reps;
};
const Snap kSnapshots[] = {{"b_5800", 24}, {"battle_ref_6150", 3}, {"b_6150", 2}, {"b_6300", 1}, {"b_6700", 1}, {"climb_ref_17000", 1}};

}  // namespace

TEST_CASE("game(battle3): every body equals its recompiled body on random worlds") {
    auto m = new_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    constexpr u32 kWorld = 0x01810000u, kWorldSize = 0x10000u;
    int pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += pair(*m, c.hand, c.recomp, args, seed, c.name, {}).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " ended at a compared stop");
}

TEST_CASE("game(battle3): every body on the battle snapshots, perturbed") {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    int pairs = 0, stops = 0, used = 0;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    std::string always;
    std::vector<int> stopped_of(std::size(kCases), 0), ran_of(std::size(kCases), 0);
    std::vector<std::string> why_of(std::size(kCases));
    std::map<u32, std::string> missing;  // not-emitted callees the pairs stopped at, and who reached them
    for (const Snap& sn : kSnapshots) {
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        const std::vector<u8> snap = read_snapshot(sn.dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << std::string(sn.dir) << "/eeMemory.bin not found");
            continue;
        }
        auto m = new_machine();
        if (!m) return;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        ++used;
        MESSAGE(std::string(sn.dir) << ": gBtl " << hex64(o.btl) << ", " << o.acts.size() << " actions, " << o.units.size()
                                    << " units, " << o.data.size() << " packet data blocks");
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (std::size_t ci = 0; ci < std::size(kCases); ++ci) {
            const Case& c = kCases[ci];
            if (only && std::string(only) != c.name) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                std::mt19937 rng{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                perturb(*m, o, rng);
                Args a{};
                HwCheck hw;
                args_for(*m, c, o, rng, a, hw);
                const hgp::Run r = pair_base(*m, base, c.hand, c.recomp, a, rng(), c.name, hw);
                ++pairs;
                ++ran_of[ci];
                if (r.stopped) {
                    ++stops;
                    if (stopped_of[ci]++ == 0) why_of[ci] = r.what + " at " + hex64(r.stop_pc);
                    if (r.what.rfind("missing_function", 0) == 0 && missing[r.stop_pc].find(c.name) == std::string::npos)
                        missing[r.stop_pc] += std::string(" ") + c.name;
                }
                base.restore();
            }
        }
    }
    for (std::size_t ci = 0; ci < std::size(kCases); ++ci)
        if (ran_of[ci] && stopped_of[ci] == ran_of[ci]) always += std::string(" ") + kCases[ci].name + " (" + why_of[ci] + ")";
    for (const auto& [pc, who] : missing) MESSAGE("stopped at the not-emitted " << hex64(pc) << ":" << who.substr(0, 200));
    MESSAGE("battle snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stops
                                 << " ended at a compared stop; always stopped:" << (always.empty() ? " none" : always));
}

TEST_CASE("game(battle3): the battle core and AI follow the documented rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    // (1) sub_2C3770's weights: candidate count k uses row k - 1 of 0x696FA0, whose first k bytes sum to 100
    //     ({100}, {60, 40}, {60, 30, 10}, {40, 30, 20, 10}): the lowest-HP candidate is the likeliest pick.
    for (u32 k = 1; k <= 4; ++k) {
        u32 sum = 0;
        for (u32 j = 0; j < k; ++j) sum += ld8(*m, kAiWeights + 4 * (k - 1) + j);
        CHECK(sum == 100);
        for (u32 j = 1; j < k; ++j) CHECK(ld8(*m, kAiWeights + 4 * (k - 1) + j) <= ld8(*m, kAiWeights + 4 * (k - 1) + j - 1));
        ++checks;
    }
    // (2) the id maps
    struct Map {
        Fn fn;
        u32 in;
        s32 out;
    };
    const Map maps[] = {
        {&rg::fn_sub_2F6C50_002f6c50, 233, 22}, {&rg::fn_sub_2F6C50_002f6c50, 241, 30}, {&rg::fn_sub_2F6C50_002f6c50, 256, 0},
        {&rg::fn_sub_2F6C50_002f6c50, 263, 8},  {&rg::fn_sub_2F6C50_002f6c50, 264, 14}, {&rg::fn_sub_2F6C50_002f6c50, 277, 7},
        {&rg::fn_sub_2F6C50_002f6c50, 294, 19}, {&rg::fn_sub_2F6C50_002f6c50, 296, 17}, {&rg::fn_sub_2F6C50_002f6c50, 270, -1},
        {&rg::fn_sub_2F6C50_002f6c50, 1, -1},   {&rg::fn_sub_2E4720_002e4720, 2, 200},  {&rg::fn_sub_2E4720_002e4720, 6, 204},
        {&rg::fn_sub_2E4720_002e4720, 7, 217},  {&rg::fn_sub_2E4720_002e4720, 8, 0},    {&rg::fn_sub_2D56A0_002d56a0, 331, 152},
        {&rg::fn_sub_2D56A0_002d56a0, 256, 100}, {&rg::fn_sub_2D56A0_002d56a0, 257, 102}, {&rg::fn_sub_2D56A0_002d56a0, 1, 0},
    };
    for (const Map& mp : maps) {
        INFO("map input " << mp.in);
        CHECK(static_cast<s32>(v0_of(solo(*m, mp.fn, {mp.in, 0, 0, 0}))) == mp.out);
        ++checks;
    }
    // (3) the grid cell: round((int)(x + 1750) / 25) for both coordinates, written through the optional pointers
    {
        std::mt19937 rng{0x6121u};
        for (int k = 0; k < 400; ++k) {
            const float x = static_cast<float>(static_cast<int>(rng() % 350000) - 175000) / 100.0f;
            const float z = static_cast<float>(static_cast<int>(rng() % 350000) - 175000) / 100.0f;
            stf(*m, kScratch + 0x100, x);
            stf(*m, kScratch + 0x104, 0.0f);
            stf(*m, kScratch + 0x108, z);
            st32(*m, kScratch, 0xDEADBEEFu);
            solo(*m, &rg::fn_sub_2D2280_002d2280, {sx(kScratch), sx(kScratch + 2), sx(kScratch + 0x100), 0});
            auto cell = [](float f) {
                const s32 v = static_cast<s32>(1750.0f + f);
                return static_cast<s16>(v / 25 + (v % 25 >= 13 ? 1 : 0));
            };
            INFO("x " << x << " z " << z);
            CHECK(static_cast<s16>(ld16(*m, kScratch)) == cell(x));
            CHECK(static_cast<s16>(ld16(*m, kScratch + 2)) == cell(z));
            ++checks;
        }
    }
    // (4) the AI command decoder sub_2C6A00 (record +52 kind, +54 skill, +62 item argument; action +220)
    {
        st32(*m, kScratch + 0x400, 0);
        struct Cmd {
            u32 code;
            u16 kind;
            s32 skill;  // -1: not written
        };
        // 0x8005 writes nothing (its case falls out of the decoder): the kind stays 0
        const Cmd cmds[] = {{0x8001u, 6, -1}, {0x8006u, 11, -1}, {0x8007u, 8, -1}, {0x8008u, 12, -1}, {0x8002u, 7, -1},
                            {0x8005u, 0, -1}, {0x2003u, 7, -1},  {0x1155u, 9, 341}, {0x0042u, 2, 0x42}, {0x01A0u, 2, 0x1A0}};
        for (const Cmd& c : cmds) {
            std::memset(m->at(kScratch + 0x200), 0, 0x400);
            const u32 act = kScratch + 0x200, rec = kScratch + 0x500;
            st16(*m, rec + 54, 0xFFFF);
            solo(*m, &rg::fn_sub_2C6A00_002c6a00, {sx(act), sx(rec), c.code, 0});
            INFO("code " << hex64(c.code));
            CHECK(ld16(*m, rec + 52) == c.kind);
            if (c.skill >= 0) CHECK(ld16(*m, rec + 54) == static_cast<u16>(c.skill));
            if (c.code == 0x1155u) CHECK(ld16(*m, rec + 62) == 0x155);
            if (c.code == 0x2003u) CHECK(ld16(*m, act + 220) == 3);
            ++checks;
        }
    }
    // (5) the snapshot rules: the unit finders, MYHP / MYMP, SENSEI and the all-out attack check against host models
    for (const Snap& sn : kSnapshots) {
        const std::vector<u8> snap = read_snapshot(sn.dir);
        if (snap.empty()) continue;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        if (!o.btl) continue;
        auto dat_of = [&](u32 act) { return ld32(*m, ld32(*m, act + b3::act::kUnit) + b3::unit::kDat); };
        auto dead = [&](u32 d) { return (ld32(*m, d + b3::dat::kStatus) & 0x80000u) || static_cast<s32>(ld16(*m, d + b3::dat::kHp)) <= 0; };
        // sub_288FE0 (side, id) and sub_289030 (uid)
        for (u32 s = 0; s < 4; ++s)
            for (u32 id : {0u, 1u, 2u, 3u, 7u, 100u, 233u, 256u}) {
                u32 want = 0;
                for (u32 u = ld32(*m, o.btl + b3::gbtl::kUnitHead0 + 8 * s); in_ram(u); u = ld32(*m, u + b3::unit::kNext))
                    if (ld16(*m, u + b3::unit::kId) == id) {
                        want = u;
                        break;
                    }
                CHECK(static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_288FE0_00288fe0, {s, id, 0, 0}))) == want);
                ++checks;
            }
        for (u32 uid : o.uids) {
            u32 want = 0;
            for (u32 s = 0; s < 4 && !want; ++s)
                for (u32 u = ld32(*m, o.btl + b3::gbtl::kUnitHead0 + 8 * s); in_ram(u); u = ld32(*m, u + b3::unit::kNext))
                    if (ld32(*m, u + b3::unit::kUid) == uid) {
                        want = u;
                        break;
                    }
            CHECK(static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_289030_00289030, {uid, 0, 0, 0}))) == want);
            ++checks;
        }
        // sub_2C0E30 (id, side mask, status mask 0 / 0x80000): the first listed combatant that matches
        for (u16 id : o.ids)
            for (u32 mask = 1; mask < 16; ++mask)
                for (u32 st : {0u, 0x80000u}) {
                    u32 want = 0;
                    for (u32 a : o.acts) {
                        const u16 f2 = ld16(*m, a + b3::act::kFlags2);
                        if (!(f2 & 1) || !(f2 & 8)) continue;
                        const u32 u = ld32(*m, a + b3::act::kUnit);
                        if (!(mask & (1u << ld8(*m, u + b3::unit::kSide)))) continue;
                        const u32 d = ld32(*m, u + b3::unit::kDat);
                        if (st && dead(d)) continue;
                        if (ld32(*m, d + b3::dat::kStatus) & st) continue;
                        if (ld16(*m, u + b3::unit::kId) != id) continue;
                        want = a;
                        break;
                    }
                    CHECK(static_cast<u32>(v0_of(solo(*m, &rg::fn_sub_2C0E30_002c0e30, {id, mask, st, 0}))) == want);
                    ++checks;
                }
        // MYHP / MYMP: true exactly when 100 * cur <= max * param
        for (u32 a : o.acts) {
            const u32 d = dat_of(a);
            const u32 maxhp = static_cast<u16>(v0_of(solo(*m, &rg::fn_datCalcGetMaxHp_002ffdf0, {sx(d), 0, 0, 0})));
            const u32 maxsp = static_cast<u16>(v0_of(solo(*m, &rg::fn_datCalcGetMaxSp_00300100, {sx(d), 0, 0, 0})));
            for (u32 p : {0u, 1u, 25u, 50u, 99u, 100u, 101u}) {
                const bool hp = 100u * ld16(*m, d + b3::dat::kHp) <= maxhp * p;
                const bool sp = 100u * ld16(*m, d + b3::dat::kSp) <= maxsp * p;
                CHECK(v0_of(solo(*m, &rg::fn_sub_2C12F0_002c12f0, {sx(a), p, 0, 0})) == (hp ? 1u : 0u));
                CHECK(v0_of(solo(*m, &rg::fn_sub_2C13D0_002c13d0, {sx(a), p, 0, 0})) == (sp ? 1u : 0u));
                ++checks;
            }
            // SENSEI: no turn taken yet and the side won the advantage roll
            for (u16 adv = 0; adv < 3; ++adv) {
                st16(*m, o.btl + b3::gbtl::kAdvantage, adv);
                const u8 side = ld8(*m, ld32(*m, a + b3::act::kUnit) + b3::unit::kSide);
                const bool want = static_cast<s32>(ld32(*m, a + b3::act::kTurnsTaken)) <= 0 &&
                                  ((side == 1 && adv == 2) || (side == 0 && adv == 1));
                CHECK(v0_of(solo(*m, &rg::fn_sub_2C1D90_002c1d90, {sx(a), 0, 0, 0})) == (want ? 1u : 0u));
                ++checks;
            }
        }
        // the all-out attack check over random status assignments (down / dead / blocking ailments)
        std::mt19937 rng{0xA110u};
        const u32 hero = ld32(*m, o.btl + b3::gbtl::kPlayerAction);
        for (int k = 0; k < 40 && in_ram(hero) && !o.acts.empty(); ++k) {
            std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
            write_rw_slots(*m);
            for (u32 a : o.acts) {
                const u32 d = dat_of(a);
                const u32 r = rng() % 6;
                st32(*m, d + b3::dat::kStatus, r == 0 ? 0x100000u : r == 1 ? 0x80000u : r == 2 ? 0x1u : r == 3 ? 0x100000u : 0);
            }
            const u32 actor = o.acts[rng() % o.acts.size()];
            // host model
            u32 want = 0, list = 0, downs = 0;
            std::vector<u32> joined;
            const u32 hd = dat_of(hero);
            const auto status = [&](u32 d) { return ld32(*m, d + b3::dat::kStatus); };
            bool decided = false;
            if (dead(hd) || (status(hd) & 0x100261u)) decided = true;
            else if (ld8(*m, ld32(*m, actor + b3::act::kUnit) + b3::unit::kSide) == 1 && dead(dat_of(actor))) decided = true;
            else {
                for (u32 a : o.acts) {
                    if (!(ld16(*m, a + b3::act::kFlags2) & 1)) continue;
                    const u32 u = ld32(*m, a + b3::act::kUnit);
                    if (!(ld32(*m, u + b3::unit::kFlags) & 8)) continue;
                    const u32 d = ld32(*m, u + b3::unit::kDat);
                    if (dead(d)) continue;
                    if (ld8(*m, u + b3::unit::kSide) == 1) {
                        if (!(status(d) & 0x100000u)) {
                            decided = true;
                            break;
                        }
                        ++downs;
                    } else if (!(status(d) & 0x100261u) && a != hero) {
                        joined.push_back(a);
                    }
                }
                if (!decided) want = (downs && !joined.empty()) ? 1 : 0;
                list = static_cast<u32>(joined.size());
            }
            const u64 got = v0_of(solo(*m, &rg::fn_sub_28A200_0028a200, {sx(actor), 0, 0, 0}));
            CHECK(got == want);
            if (!decided) {
                CHECK(ld16(*m, o.btl + b3::gbtl::kAllOutCount) == list);
                for (u32 j = 0; j < list && j < 4; ++j) CHECK(ld32(*m, o.btl + b3::gbtl::kAllOutList + 4 * j) == joined[j]);
            }
            ++checks;
        }
    }
    MESSAGE("documented rules: " << checks << " checks");
}

#else

TEST_CASE("game(battle3): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
