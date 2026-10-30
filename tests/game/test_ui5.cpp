// Pair tests of slice ui5 (game/src/ui/ui5.cpp): the camp menu's screens. Every pair runs the hand body and its
// recompiled body from the same guest machine through tests/game/handgen_pairs.h -- the whole register file and the cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (write-tracked), the scratchpad, the BIOS
// window, the bus log -- and, where a body allocates, prints or loads files, on two identical stand-in worlds
// (tests/game/stand_ins.h) whose call logs must match.
//
// Inputs: the p3fes_handgen random worlds for every function; the tween records (sub_18BC10's fields, the camp list's
// slide-in / fade-in / fade-out layouts, sub_18B6D0's RwCalloc); the flash-control task driven frame by frame through a
// whole screen transition (the .anm functions served by recorders) and its request table; the equipment stock of the
// b_5800 replay snapshot (real game data) through the list builders, with the item kinds of the real item tables; the
// status screen's digit / condition-icon draws on the hero record; and the task creators of the camp screens on the
// dorm snapshot's task system with the heap / file / printf stand-ins. Documented-rule checks after every pair (the
// tween fields and row layout, the 24-frame transition, the list count / order / row fields against the EquipEntry
// records, the digit sprites 11 + digit, the condition -> sprite table, every task's name / priority / callbacks / work
// size / work fields).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/ui5.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace ui5 = p3fes::game::ui5;  // the named offsets of game/include/p3fes/game/ui5.h
namespace p3fes::recomp_gen {
void fn_H_Cdvd_ReadSync_001023a0(EEContext&);  // the file layer (a stand-in in these tests)
}  // namespace p3fes::recomp_gen  // the named offsets of game/include/p3fes/game/ui5.h

namespace p3fes::recomp_gen {
void fn_sub_119AA0_00119aa0(EEContext&);  // generated body
void fn_sub_119AA0_00119aa0__recomp(EEContext&);  // recompiled
void fn_sub_119E00_00119e00(EEContext&);  // generated body
void fn_sub_119E00_00119e00__recomp(EEContext&);  // recompiled
void fn_sub_119F10_00119f10(EEContext&);  // generated body
void fn_sub_119F10_00119f10__recomp(EEContext&);  // recompiled
void fn_sub_11A710_0011a710(EEContext&);  // generated body
void fn_sub_11A710_0011a710__recomp(EEContext&);  // recompiled
void fn_H_Camp_CreateDrawTask_0011a770(EEContext&);  // generated body
void fn_H_Camp_CreateDrawTask_0011a770__recomp(EEContext&);  // recompiled
void fn_sub_11A8A0_0011a8a0(EEContext&);  // generated body
void fn_sub_11A8A0_0011a8a0__recomp(EEContext&);  // recompiled
void fn_sub_11AAE0_0011aae0(EEContext&);  // generated body
void fn_sub_11AAE0_0011aae0__recomp(EEContext&);  // recompiled
void fn_sub_11B0B0_0011b0b0(EEContext&);  // generated body
void fn_sub_11B0B0_0011b0b0__recomp(EEContext&);  // recompiled
void fn_sub_11B210_0011b210(EEContext&);  // generated body
void fn_sub_11B210_0011b210__recomp(EEContext&);  // recompiled
void fn_sub_11B2B0_0011b2b0(EEContext&);  // generated body
void fn_sub_11B2B0_0011b2b0__recomp(EEContext&);  // recompiled
void fn_sub_11B370_0011b370(EEContext&);  // generated body
void fn_sub_11B370_0011b370__recomp(EEContext&);  // recompiled
void fn_sub_11BAA0_0011baa0(EEContext&);  // generated body
void fn_sub_11BAA0_0011baa0__recomp(EEContext&);  // recompiled
void fn_H_Camp_CreateRootDrawTask_0011bad0(EEContext&);  // generated body
void fn_H_Camp_CreateRootDrawTask_0011bad0__recomp(EEContext&);  // recompiled
void fn_nullsub_3_0011bba0(EEContext&);  // generated body
void fn_nullsub_3_0011bba0__recomp(EEContext&);  // recompiled
void fn_sub_11C550_0011c550(EEContext&);  // generated body
void fn_sub_11C550_0011c550__recomp(EEContext&);  // recompiled
void fn_sub_11CC80_0011cc80(EEContext&);  // generated body
void fn_sub_11CC80_0011cc80__recomp(EEContext&);  // recompiled
void fn_sub_11D3A0_0011d3a0(EEContext&);  // generated body
void fn_sub_11D3A0_0011d3a0__recomp(EEContext&);  // recompiled
void fn_sub_11DA80_0011da80(EEContext&);  // generated body
void fn_sub_11DA80_0011da80__recomp(EEContext&);  // recompiled
void fn_sub_11E380_0011e380(EEContext&);  // generated body
void fn_sub_11E380_0011e380__recomp(EEContext&);  // recompiled
void fn_sub_11EA20_0011ea20(EEContext&);  // generated body
void fn_sub_11EA20_0011ea20__recomp(EEContext&);  // recompiled
void fn_sub_11F120_0011f120(EEContext&);  // generated body
void fn_sub_11F120_0011f120__recomp(EEContext&);  // recompiled
void fn_sub_11F1B0_0011f1b0(EEContext&);  // generated body
void fn_sub_11F1B0_0011f1b0__recomp(EEContext&);  // recompiled
void fn_sub_11F260_0011f260(EEContext&);  // generated body
void fn_sub_11F260_0011f260__recomp(EEContext&);  // recompiled
void fn_sub_11F400_0011f400(EEContext&);  // generated body
void fn_sub_11F400_0011f400__recomp(EEContext&);  // recompiled
void fn_sub_11F5C0_0011f5c0(EEContext&);  // generated body
void fn_sub_11F5C0_0011f5c0__recomp(EEContext&);  // recompiled
void fn_sub_11F760_0011f760(EEContext&);  // generated body
void fn_sub_11F760_0011f760__recomp(EEContext&);  // recompiled
void fn_sub_11F900_0011f900(EEContext&);  // generated body
void fn_sub_11F900_0011f900__recomp(EEContext&);  // recompiled
void fn_sub_11FAF0_0011faf0(EEContext&);  // generated body
void fn_sub_11FAF0_0011faf0__recomp(EEContext&);  // recompiled
void fn_sub_11FCA0_0011fca0(EEContext&);  // generated body
void fn_sub_11FCA0_0011fca0__recomp(EEContext&);  // recompiled
void fn_sub_11FE50_0011fe50(EEContext&);  // generated body
void fn_sub_11FE50_0011fe50__recomp(EEContext&);  // recompiled
void fn_sub_11FFD0_0011ffd0(EEContext&);  // generated body
void fn_sub_11FFD0_0011ffd0__recomp(EEContext&);  // recompiled
void fn_sub_120150_00120150(EEContext&);  // generated body
void fn_sub_120150_00120150__recomp(EEContext&);  // recompiled
void fn_sub_1202B0_001202b0(EEContext&);  // generated body
void fn_sub_1202B0_001202b0__recomp(EEContext&);  // recompiled
void fn_sub_120410_00120410(EEContext&);  // generated body
void fn_sub_120410_00120410__recomp(EEContext&);  // recompiled
void fn_sub_120570_00120570(EEContext&);  // generated body
void fn_sub_120570_00120570__recomp(EEContext&);  // recompiled
void fn_sub_1206D0_001206d0(EEContext&);  // generated body
void fn_sub_1206D0_001206d0__recomp(EEContext&);  // recompiled
void fn_sub_120830_00120830(EEContext&);  // generated body
void fn_sub_120830_00120830__recomp(EEContext&);  // recompiled
void fn_sub_120990_00120990(EEContext&);  // generated body
void fn_sub_120990_00120990__recomp(EEContext&);  // recompiled
void fn_sub_120B10_00120b10(EEContext&);  // generated body
void fn_sub_120B10_00120b10__recomp(EEContext&);  // recompiled
void fn_sub_120CA0_00120ca0(EEContext&);  // generated body
void fn_sub_120CA0_00120ca0__recomp(EEContext&);  // recompiled
void fn_sub_120E20_00120e20(EEContext&);  // generated body
void fn_sub_120E20_00120e20__recomp(EEContext&);  // recompiled
void fn_sub_120FD0_00120fd0(EEContext&);  // generated body
void fn_sub_120FD0_00120fd0__recomp(EEContext&);  // recompiled
void fn_sub_121180_00121180(EEContext&);  // generated body
void fn_sub_121180_00121180__recomp(EEContext&);  // recompiled
void fn_sub_121300_00121300(EEContext&);  // generated body
void fn_sub_121300_00121300__recomp(EEContext&);  // recompiled
void fn_sub_121480_00121480(EEContext&);  // generated body
void fn_sub_121480_00121480__recomp(EEContext&);  // recompiled
void fn_sub_121600_00121600(EEContext&);  // generated body
void fn_sub_121600_00121600__recomp(EEContext&);  // recompiled
void fn_sub_121780_00121780(EEContext&);  // generated body
void fn_sub_121780_00121780__recomp(EEContext&);  // recompiled
void fn_sub_121930_00121930(EEContext&);  // generated body
void fn_sub_121930_00121930__recomp(EEContext&);  // recompiled
void fn_sub_121AB0_00121ab0(EEContext&);  // generated body
void fn_sub_121AB0_00121ab0__recomp(EEContext&);  // recompiled
void fn_sub_121C30_00121c30(EEContext&);  // generated body
void fn_sub_121C30_00121c30__recomp(EEContext&);  // recompiled
void fn_sub_121FF0_00121ff0(EEContext&);  // generated body
void fn_sub_121FF0_00121ff0__recomp(EEContext&);  // recompiled
void fn_sub_122630_00122630(EEContext&);  // generated body
void fn_sub_122630_00122630__recomp(EEContext&);  // recompiled
void fn_sub_122660_00122660(EEContext&);  // generated body
void fn_sub_122660_00122660__recomp(EEContext&);  // recompiled
void fn_sub_122940_00122940(EEContext&);  // generated body
void fn_sub_122940_00122940__recomp(EEContext&);  // recompiled
void fn_sub_122FD0_00122fd0(EEContext&);  // generated body
void fn_sub_122FD0_00122fd0__recomp(EEContext&);  // recompiled
void fn_sub_123000_00123000(EEContext&);  // generated body
void fn_sub_123000_00123000__recomp(EEContext&);  // recompiled
void fn_sub_1230C0_001230c0(EEContext&);  // generated body
void fn_sub_1230C0_001230c0__recomp(EEContext&);  // recompiled
void fn_sub_123540_00123540(EEContext&);  // generated body
void fn_sub_123540_00123540__recomp(EEContext&);  // recompiled
void fn_sub_123570_00123570(EEContext&);  // generated body
void fn_sub_123570_00123570__recomp(EEContext&);  // recompiled
void fn_sub_123B70_00123b70(EEContext&);  // generated body
void fn_sub_123B70_00123b70__recomp(EEContext&);  // recompiled
void fn_sub_123F80_00123f80(EEContext&);  // generated body
void fn_sub_123F80_00123f80__recomp(EEContext&);  // recompiled
void fn_sub_124090_00124090(EEContext&);  // generated body
void fn_sub_124090_00124090__recomp(EEContext&);  // recompiled
void fn_sub_124E60_00124e60(EEContext&);  // generated body
void fn_sub_124E60_00124e60__recomp(EEContext&);  // recompiled
void fn_sub_125740_00125740(EEContext&);  // generated body
void fn_sub_125740_00125740__recomp(EEContext&);  // recompiled
void fn_sub_125B40_00125b40(EEContext&);  // generated body
void fn_sub_125B40_00125b40__recomp(EEContext&);  // recompiled
void fn_sub_1266E0_001266e0(EEContext&);  // generated body
void fn_sub_1266E0_001266e0__recomp(EEContext&);  // recompiled
void fn_sub_127A40_00127a40(EEContext&);  // generated body
void fn_sub_127A40_00127a40__recomp(EEContext&);  // recompiled
void fn_sub_127B00_00127b00(EEContext&);  // generated body
void fn_sub_127B00_00127b00__recomp(EEContext&);  // recompiled
void fn_sub_127FC0_00127fc0(EEContext&);  // generated body
void fn_sub_127FC0_00127fc0__recomp(EEContext&);  // recompiled
void fn_sub_128040_00128040(EEContext&);  // generated body
void fn_sub_128040_00128040__recomp(EEContext&);  // recompiled
void fn_sub_1281E0_001281e0(EEContext&);  // generated body
void fn_sub_1281E0_001281e0__recomp(EEContext&);  // recompiled
void fn_sub_128480_00128480(EEContext&);  // generated body
void fn_sub_128480_00128480__recomp(EEContext&);  // recompiled
void fn_sub_129160_00129160(EEContext&);  // generated body
void fn_sub_129160_00129160__recomp(EEContext&);  // recompiled
void fn_sub_12BCE0_0012bce0(EEContext&);  // generated body
void fn_sub_12BCE0_0012bce0__recomp(EEContext&);  // recompiled
void fn_sub_12DDC0_0012ddc0(EEContext&);  // generated body
void fn_sub_12DDC0_0012ddc0__recomp(EEContext&);  // recompiled
void fn_sub_12DF50_0012df50(EEContext&);  // generated body
void fn_sub_12DF50_0012df50__recomp(EEContext&);  // recompiled
void fn_sub_12E170_0012e170(EEContext&);  // generated body
void fn_sub_12E170_0012e170__recomp(EEContext&);  // recompiled
void fn_sub_130E40_00130e40(EEContext&);  // generated body
void fn_sub_130E40_00130e40__recomp(EEContext&);  // recompiled
void fn_sub_130F20_00130f20(EEContext&);  // generated body
void fn_sub_130F20_00130f20__recomp(EEContext&);  // recompiled
void fn_sub_131000_00131000(EEContext&);  // generated body
void fn_sub_131000_00131000__recomp(EEContext&);  // recompiled
void fn_sub_131090_00131090(EEContext&);  // generated body
void fn_sub_131090_00131090__recomp(EEContext&);  // recompiled
void fn_sub_1332F0_001332f0(EEContext&);  // generated body
void fn_sub_1332F0_001332f0__recomp(EEContext&);  // recompiled
void fn_sub_1335D0_001335d0(EEContext&);  // generated body
void fn_sub_1335D0_001335d0__recomp(EEContext&);  // recompiled
void fn_sub_1336B0_001336b0(EEContext&);  // generated body
void fn_sub_1336B0_001336b0__recomp(EEContext&);  // recompiled
void fn_sub_133780_00133780(EEContext&);  // generated body
void fn_sub_133780_00133780__recomp(EEContext&);  // recompiled
void fn_sub_133900_00133900(EEContext&);  // generated body
void fn_sub_133900_00133900__recomp(EEContext&);  // recompiled
void fn_sub_1339A0_001339a0(EEContext&);  // generated body
void fn_sub_1339A0_001339a0__recomp(EEContext&);  // recompiled
void fn_sub_133A80_00133a80(EEContext&);  // generated body
void fn_sub_133A80_00133a80__recomp(EEContext&);  // recompiled
void fn_sub_133B80_00133b80(EEContext&);  // generated body
void fn_sub_133B80_00133b80__recomp(EEContext&);  // recompiled
void fn_sub_133C40_00133c40(EEContext&);  // generated body
void fn_sub_133C40_00133c40__recomp(EEContext&);  // recompiled
void fn_sub_133D00_00133d00(EEContext&);  // generated body
void fn_sub_133D00_00133d00__recomp(EEContext&);  // recompiled
void fn_sub_133D30_00133d30(EEContext&);  // generated body
void fn_sub_133D30_00133d30__recomp(EEContext&);  // recompiled
void fn_sub_134A10_00134a10(EEContext&);  // generated body
void fn_sub_134A10_00134a10__recomp(EEContext&);  // recompiled
void fn_sub_134D80_00134d80(EEContext&);  // generated body
void fn_sub_134D80_00134d80__recomp(EEContext&);  // recompiled
void fn_sub_135120_00135120(EEContext&);  // generated body
void fn_sub_135120_00135120__recomp(EEContext&);  // recompiled
void fn_sub_135460_00135460(EEContext&);  // generated body
void fn_sub_135460_00135460__recomp(EEContext&);  // recompiled
void fn_sub_1365B0_001365b0(EEContext&);  // generated body
void fn_sub_1365B0_001365b0__recomp(EEContext&);  // recompiled
void fn_sub_136750_00136750(EEContext&);  // generated body
void fn_sub_136750_00136750__recomp(EEContext&);  // recompiled
void fn_sub_1368A0_001368a0(EEContext&);  // generated body
void fn_sub_1368A0_001368a0__recomp(EEContext&);  // recompiled
void fn_sub_137300_00137300(EEContext&);  // generated body
void fn_sub_137300_00137300__recomp(EEContext&);  // recompiled
void fn_sub_138EE0_00138ee0(EEContext&);  // generated body
void fn_sub_138EE0_00138ee0__recomp(EEContext&);  // recompiled
void fn_sub_1392D0_001392d0(EEContext&);  // generated body
void fn_sub_1392D0_001392d0__recomp(EEContext&);  // recompiled
void fn_sub_13BCE0_0013bce0(EEContext&);  // generated body
void fn_sub_13BCE0_0013bce0__recomp(EEContext&);  // recompiled
void fn_sub_13BE50_0013be50(EEContext&);  // generated body
void fn_sub_13BE50_0013be50__recomp(EEContext&);  // recompiled
void fn_sub_13C240_0013c240(EEContext&);  // generated body
void fn_sub_13C240_0013c240__recomp(EEContext&);  // recompiled
void fn_sub_13C6A0_0013c6a0(EEContext&);  // generated body
void fn_sub_13C6A0_0013c6a0__recomp(EEContext&);  // recompiled
void fn_sub_13CC90_0013cc90(EEContext&);  // generated body
void fn_sub_13CC90_0013cc90__recomp(EEContext&);  // recompiled
void fn_sub_13CF80_0013cf80(EEContext&);  // generated body
void fn_sub_13CF80_0013cf80__recomp(EEContext&);  // recompiled
void fn_sub_141590_00141590(EEContext&);  // generated body
void fn_sub_141590_00141590__recomp(EEContext&);  // recompiled
void fn_sub_145350_00145350(EEContext&);  // generated body
void fn_sub_145350_00145350__recomp(EEContext&);  // recompiled
void fn_sub_14ED20_0014ed20(EEContext&);  // generated body
void fn_sub_14ED20_0014ed20__recomp(EEContext&);  // recompiled
void fn_sub_14EE80_0014ee80(EEContext&);  // generated body
void fn_sub_14EE80_0014ee80__recomp(EEContext&);  // recompiled
void fn_sub_14EF60_0014ef60(EEContext&);  // generated body
void fn_sub_14EF60_0014ef60__recomp(EEContext&);  // recompiled
void fn_sub_14F320_0014f320(EEContext&);  // generated body
void fn_sub_14F320_0014f320__recomp(EEContext&);  // recompiled
void fn_sub_14F680_0014f680(EEContext&);  // generated body
void fn_sub_14F680_0014f680__recomp(EEContext&);  // recompiled
void fn_sub_154770_00154770(EEContext&);  // generated body
void fn_sub_154770_00154770__recomp(EEContext&);  // recompiled
void fn_sub_1548A0_001548a0(EEContext&);  // generated body
void fn_sub_1548A0_001548a0__recomp(EEContext&);  // recompiled
void fn_sub_15C460_0015c460(EEContext&);  // generated body
void fn_sub_15C460_0015c460__recomp(EEContext&);  // recompiled
void fn_sub_15C520_0015c520(EEContext&);  // generated body
void fn_sub_15C520_0015c520__recomp(EEContext&);  // recompiled
void fn_sub_15D8E0_0015d8e0(EEContext&);  // generated body
void fn_sub_15D8E0_0015d8e0__recomp(EEContext&);  // recompiled
void fn_sub_1616D0_001616d0(EEContext&);  // generated body
void fn_sub_1616D0_001616d0__recomp(EEContext&);  // recompiled
void fn_sub_1617D0_001617d0(EEContext&);  // generated body
void fn_sub_1617D0_001617d0__recomp(EEContext&);  // recompiled
void fn_sub_161D60_00161d60(EEContext&);  // generated body
void fn_sub_161D60_00161d60__recomp(EEContext&);  // recompiled
void fn_sub_1669B0_001669b0(EEContext&);  // generated body
void fn_sub_1669B0_001669b0__recomp(EEContext&);  // recompiled
void fn_sub_166A50_00166a50(EEContext&);  // generated body
void fn_sub_166A50_00166a50__recomp(EEContext&);  // recompiled
void fn_sub_1675B0_001675b0(EEContext&);  // generated body
void fn_sub_1675B0_001675b0__recomp(EEContext&);  // recompiled
void fn_sub_1675E0_001675e0(EEContext&);  // generated body
void fn_sub_1675E0_001675e0__recomp(EEContext&);  // recompiled
void fn_sub_1678E0_001678e0(EEContext&);  // generated body
void fn_sub_1678E0_001678e0__recomp(EEContext&);  // recompiled
void fn_sub_167EC0_00167ec0(EEContext&);  // generated body
void fn_sub_167EC0_00167ec0__recomp(EEContext&);  // recompiled
void fn_sub_167F40_00167f40(EEContext&);  // generated body
void fn_sub_167F40_00167f40__recomp(EEContext&);  // recompiled
void fn_sub_168040_00168040(EEContext&);  // generated body
void fn_sub_168040_00168040__recomp(EEContext&);  // recompiled
void fn_sub_168100_00168100(EEContext&);  // generated body
void fn_sub_168100_00168100__recomp(EEContext&);  // recompiled
void fn_sub_168220_00168220(EEContext&);  // generated body
void fn_sub_168220_00168220__recomp(EEContext&);  // recompiled
void fn_sub_1685E0_001685e0(EEContext&);  // generated body
void fn_sub_1685E0_001685e0__recomp(EEContext&);  // recompiled
void fn_sub_168720_00168720(EEContext&);  // generated body
void fn_sub_168720_00168720__recomp(EEContext&);  // recompiled
void fn_sub_168770_00168770(EEContext&);  // generated body
void fn_sub_168770_00168770__recomp(EEContext&);  // recompiled
void fn_sub_169040_00169040(EEContext&);  // generated body
void fn_sub_169040_00169040__recomp(EEContext&);  // recompiled
void fn_sub_169330_00169330(EEContext&);  // generated body
void fn_sub_169330_00169330__recomp(EEContext&);  // recompiled
void fn_sub_169AE0_00169ae0(EEContext&);  // generated body
void fn_sub_169AE0_00169ae0__recomp(EEContext&);  // recompiled
void fn_sub_16A6A0_0016a6a0(EEContext&);  // generated body
void fn_sub_16A6A0_0016a6a0__recomp(EEContext&);  // recompiled
void fn_sub_18B6D0_0018b6d0(EEContext&);  // generated body
void fn_sub_18B6D0_0018b6d0__recomp(EEContext&);  // recompiled
void fn_sub_18BC10_0018bc10(EEContext&);  // generated body
void fn_sub_18BC10_0018bc10__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_119AA0", 0x119AA0, &recomp_gen::fn_sub_119AA0_00119aa0, &recomp_gen::fn_sub_119AA0_00119aa0__recomp},
    {"sub_119E00", 0x119E00, &recomp_gen::fn_sub_119E00_00119e00, &recomp_gen::fn_sub_119E00_00119e00__recomp},
    {"sub_119F10", 0x119F10, &recomp_gen::fn_sub_119F10_00119f10, &recomp_gen::fn_sub_119F10_00119f10__recomp},
    {"sub_11A710", 0x11A710, &recomp_gen::fn_sub_11A710_0011a710, &recomp_gen::fn_sub_11A710_0011a710__recomp},
    {"H_Camp_CreateDrawTask", 0x11A770, &recomp_gen::fn_H_Camp_CreateDrawTask_0011a770, &recomp_gen::fn_H_Camp_CreateDrawTask_0011a770__recomp},
    {"sub_11A8A0", 0x11A8A0, &recomp_gen::fn_sub_11A8A0_0011a8a0, &recomp_gen::fn_sub_11A8A0_0011a8a0__recomp},
    {"sub_11AAE0", 0x11AAE0, &recomp_gen::fn_sub_11AAE0_0011aae0, &recomp_gen::fn_sub_11AAE0_0011aae0__recomp},
    {"sub_11B0B0", 0x11B0B0, &recomp_gen::fn_sub_11B0B0_0011b0b0, &recomp_gen::fn_sub_11B0B0_0011b0b0__recomp},
    {"sub_11B210", 0x11B210, &recomp_gen::fn_sub_11B210_0011b210, &recomp_gen::fn_sub_11B210_0011b210__recomp},
    {"sub_11B2B0", 0x11B2B0, &recomp_gen::fn_sub_11B2B0_0011b2b0, &recomp_gen::fn_sub_11B2B0_0011b2b0__recomp},
    {"sub_11B370", 0x11B370, &recomp_gen::fn_sub_11B370_0011b370, &recomp_gen::fn_sub_11B370_0011b370__recomp},
    {"sub_11BAA0", 0x11BAA0, &recomp_gen::fn_sub_11BAA0_0011baa0, &recomp_gen::fn_sub_11BAA0_0011baa0__recomp},
    {"H_Camp_CreateRootDrawTask", 0x11BAD0, &recomp_gen::fn_H_Camp_CreateRootDrawTask_0011bad0, &recomp_gen::fn_H_Camp_CreateRootDrawTask_0011bad0__recomp},
    {"nullsub_3", 0x11BBA0, &recomp_gen::fn_nullsub_3_0011bba0, &recomp_gen::fn_nullsub_3_0011bba0__recomp},
    {"sub_11C550", 0x11C550, &recomp_gen::fn_sub_11C550_0011c550, &recomp_gen::fn_sub_11C550_0011c550__recomp},
    {"sub_11CC80", 0x11CC80, &recomp_gen::fn_sub_11CC80_0011cc80, &recomp_gen::fn_sub_11CC80_0011cc80__recomp},
    {"sub_11D3A0", 0x11D3A0, &recomp_gen::fn_sub_11D3A0_0011d3a0, &recomp_gen::fn_sub_11D3A0_0011d3a0__recomp},
    {"sub_11DA80", 0x11DA80, &recomp_gen::fn_sub_11DA80_0011da80, &recomp_gen::fn_sub_11DA80_0011da80__recomp},
    {"sub_11E380", 0x11E380, &recomp_gen::fn_sub_11E380_0011e380, &recomp_gen::fn_sub_11E380_0011e380__recomp},
    {"sub_11EA20", 0x11EA20, &recomp_gen::fn_sub_11EA20_0011ea20, &recomp_gen::fn_sub_11EA20_0011ea20__recomp},
    {"sub_11F120", 0x11F120, &recomp_gen::fn_sub_11F120_0011f120, &recomp_gen::fn_sub_11F120_0011f120__recomp},
    {"sub_11F1B0", 0x11F1B0, &recomp_gen::fn_sub_11F1B0_0011f1b0, &recomp_gen::fn_sub_11F1B0_0011f1b0__recomp},
    {"sub_11F260", 0x11F260, &recomp_gen::fn_sub_11F260_0011f260, &recomp_gen::fn_sub_11F260_0011f260__recomp},
    {"sub_11F400", 0x11F400, &recomp_gen::fn_sub_11F400_0011f400, &recomp_gen::fn_sub_11F400_0011f400__recomp},
    {"sub_11F5C0", 0x11F5C0, &recomp_gen::fn_sub_11F5C0_0011f5c0, &recomp_gen::fn_sub_11F5C0_0011f5c0__recomp},
    {"sub_11F760", 0x11F760, &recomp_gen::fn_sub_11F760_0011f760, &recomp_gen::fn_sub_11F760_0011f760__recomp},
    {"sub_11F900", 0x11F900, &recomp_gen::fn_sub_11F900_0011f900, &recomp_gen::fn_sub_11F900_0011f900__recomp},
    {"sub_11FAF0", 0x11FAF0, &recomp_gen::fn_sub_11FAF0_0011faf0, &recomp_gen::fn_sub_11FAF0_0011faf0__recomp},
    {"sub_11FCA0", 0x11FCA0, &recomp_gen::fn_sub_11FCA0_0011fca0, &recomp_gen::fn_sub_11FCA0_0011fca0__recomp},
    {"sub_11FE50", 0x11FE50, &recomp_gen::fn_sub_11FE50_0011fe50, &recomp_gen::fn_sub_11FE50_0011fe50__recomp},
    {"sub_11FFD0", 0x11FFD0, &recomp_gen::fn_sub_11FFD0_0011ffd0, &recomp_gen::fn_sub_11FFD0_0011ffd0__recomp},
    {"sub_120150", 0x120150, &recomp_gen::fn_sub_120150_00120150, &recomp_gen::fn_sub_120150_00120150__recomp},
    {"sub_1202B0", 0x1202B0, &recomp_gen::fn_sub_1202B0_001202b0, &recomp_gen::fn_sub_1202B0_001202b0__recomp},
    {"sub_120410", 0x120410, &recomp_gen::fn_sub_120410_00120410, &recomp_gen::fn_sub_120410_00120410__recomp},
    {"sub_120570", 0x120570, &recomp_gen::fn_sub_120570_00120570, &recomp_gen::fn_sub_120570_00120570__recomp},
    {"sub_1206D0", 0x1206D0, &recomp_gen::fn_sub_1206D0_001206d0, &recomp_gen::fn_sub_1206D0_001206d0__recomp},
    {"sub_120830", 0x120830, &recomp_gen::fn_sub_120830_00120830, &recomp_gen::fn_sub_120830_00120830__recomp},
    {"sub_120990", 0x120990, &recomp_gen::fn_sub_120990_00120990, &recomp_gen::fn_sub_120990_00120990__recomp},
    {"sub_120B10", 0x120B10, &recomp_gen::fn_sub_120B10_00120b10, &recomp_gen::fn_sub_120B10_00120b10__recomp},
    {"sub_120CA0", 0x120CA0, &recomp_gen::fn_sub_120CA0_00120ca0, &recomp_gen::fn_sub_120CA0_00120ca0__recomp},
    {"sub_120E20", 0x120E20, &recomp_gen::fn_sub_120E20_00120e20, &recomp_gen::fn_sub_120E20_00120e20__recomp},
    {"sub_120FD0", 0x120FD0, &recomp_gen::fn_sub_120FD0_00120fd0, &recomp_gen::fn_sub_120FD0_00120fd0__recomp},
    {"sub_121180", 0x121180, &recomp_gen::fn_sub_121180_00121180, &recomp_gen::fn_sub_121180_00121180__recomp},
    {"sub_121300", 0x121300, &recomp_gen::fn_sub_121300_00121300, &recomp_gen::fn_sub_121300_00121300__recomp},
    {"sub_121480", 0x121480, &recomp_gen::fn_sub_121480_00121480, &recomp_gen::fn_sub_121480_00121480__recomp},
    {"sub_121600", 0x121600, &recomp_gen::fn_sub_121600_00121600, &recomp_gen::fn_sub_121600_00121600__recomp},
    {"sub_121780", 0x121780, &recomp_gen::fn_sub_121780_00121780, &recomp_gen::fn_sub_121780_00121780__recomp},
    {"sub_121930", 0x121930, &recomp_gen::fn_sub_121930_00121930, &recomp_gen::fn_sub_121930_00121930__recomp},
    {"sub_121AB0", 0x121AB0, &recomp_gen::fn_sub_121AB0_00121ab0, &recomp_gen::fn_sub_121AB0_00121ab0__recomp},
    {"sub_121C30", 0x121C30, &recomp_gen::fn_sub_121C30_00121c30, &recomp_gen::fn_sub_121C30_00121c30__recomp},
    {"sub_121FF0", 0x121FF0, &recomp_gen::fn_sub_121FF0_00121ff0, &recomp_gen::fn_sub_121FF0_00121ff0__recomp},
    {"sub_122630", 0x122630, &recomp_gen::fn_sub_122630_00122630, &recomp_gen::fn_sub_122630_00122630__recomp},
    {"sub_122660", 0x122660, &recomp_gen::fn_sub_122660_00122660, &recomp_gen::fn_sub_122660_00122660__recomp},
    {"sub_122940", 0x122940, &recomp_gen::fn_sub_122940_00122940, &recomp_gen::fn_sub_122940_00122940__recomp},
    {"sub_122FD0", 0x122FD0, &recomp_gen::fn_sub_122FD0_00122fd0, &recomp_gen::fn_sub_122FD0_00122fd0__recomp},
    {"sub_123000", 0x123000, &recomp_gen::fn_sub_123000_00123000, &recomp_gen::fn_sub_123000_00123000__recomp},
    {"sub_1230C0", 0x1230C0, &recomp_gen::fn_sub_1230C0_001230c0, &recomp_gen::fn_sub_1230C0_001230c0__recomp},
    {"sub_123540", 0x123540, &recomp_gen::fn_sub_123540_00123540, &recomp_gen::fn_sub_123540_00123540__recomp},
    {"sub_123570", 0x123570, &recomp_gen::fn_sub_123570_00123570, &recomp_gen::fn_sub_123570_00123570__recomp},
    {"sub_123B70", 0x123B70, &recomp_gen::fn_sub_123B70_00123b70, &recomp_gen::fn_sub_123B70_00123b70__recomp},
    {"sub_123F80", 0x123F80, &recomp_gen::fn_sub_123F80_00123f80, &recomp_gen::fn_sub_123F80_00123f80__recomp},
    {"sub_124090", 0x124090, &recomp_gen::fn_sub_124090_00124090, &recomp_gen::fn_sub_124090_00124090__recomp},
    {"sub_124E60", 0x124E60, &recomp_gen::fn_sub_124E60_00124e60, &recomp_gen::fn_sub_124E60_00124e60__recomp},
    {"sub_125740", 0x125740, &recomp_gen::fn_sub_125740_00125740, &recomp_gen::fn_sub_125740_00125740__recomp},
    {"sub_125B40", 0x125B40, &recomp_gen::fn_sub_125B40_00125b40, &recomp_gen::fn_sub_125B40_00125b40__recomp},
    {"sub_1266E0", 0x1266E0, &recomp_gen::fn_sub_1266E0_001266e0, &recomp_gen::fn_sub_1266E0_001266e0__recomp},
    {"sub_127A40", 0x127A40, &recomp_gen::fn_sub_127A40_00127a40, &recomp_gen::fn_sub_127A40_00127a40__recomp},
    {"sub_127B00", 0x127B00, &recomp_gen::fn_sub_127B00_00127b00, &recomp_gen::fn_sub_127B00_00127b00__recomp},
    {"sub_127FC0", 0x127FC0, &recomp_gen::fn_sub_127FC0_00127fc0, &recomp_gen::fn_sub_127FC0_00127fc0__recomp},
    {"sub_128040", 0x128040, &recomp_gen::fn_sub_128040_00128040, &recomp_gen::fn_sub_128040_00128040__recomp},
    {"sub_1281E0", 0x1281E0, &recomp_gen::fn_sub_1281E0_001281e0, &recomp_gen::fn_sub_1281E0_001281e0__recomp},
    {"sub_128480", 0x128480, &recomp_gen::fn_sub_128480_00128480, &recomp_gen::fn_sub_128480_00128480__recomp},
    {"sub_129160", 0x129160, &recomp_gen::fn_sub_129160_00129160, &recomp_gen::fn_sub_129160_00129160__recomp},
    {"sub_12BCE0", 0x12BCE0, &recomp_gen::fn_sub_12BCE0_0012bce0, &recomp_gen::fn_sub_12BCE0_0012bce0__recomp},
    {"sub_12DDC0", 0x12DDC0, &recomp_gen::fn_sub_12DDC0_0012ddc0, &recomp_gen::fn_sub_12DDC0_0012ddc0__recomp},
    {"sub_12DF50", 0x12DF50, &recomp_gen::fn_sub_12DF50_0012df50, &recomp_gen::fn_sub_12DF50_0012df50__recomp},
    {"sub_12E170", 0x12E170, &recomp_gen::fn_sub_12E170_0012e170, &recomp_gen::fn_sub_12E170_0012e170__recomp},
    {"sub_130E40", 0x130E40, &recomp_gen::fn_sub_130E40_00130e40, &recomp_gen::fn_sub_130E40_00130e40__recomp},
    {"sub_130F20", 0x130F20, &recomp_gen::fn_sub_130F20_00130f20, &recomp_gen::fn_sub_130F20_00130f20__recomp},
    {"sub_131000", 0x131000, &recomp_gen::fn_sub_131000_00131000, &recomp_gen::fn_sub_131000_00131000__recomp},
    {"sub_131090", 0x131090, &recomp_gen::fn_sub_131090_00131090, &recomp_gen::fn_sub_131090_00131090__recomp},
    {"sub_1332F0", 0x1332F0, &recomp_gen::fn_sub_1332F0_001332f0, &recomp_gen::fn_sub_1332F0_001332f0__recomp},
    {"sub_1335D0", 0x1335D0, &recomp_gen::fn_sub_1335D0_001335d0, &recomp_gen::fn_sub_1335D0_001335d0__recomp},
    {"sub_1336B0", 0x1336B0, &recomp_gen::fn_sub_1336B0_001336b0, &recomp_gen::fn_sub_1336B0_001336b0__recomp},
    {"sub_133780", 0x133780, &recomp_gen::fn_sub_133780_00133780, &recomp_gen::fn_sub_133780_00133780__recomp},
    {"sub_133900", 0x133900, &recomp_gen::fn_sub_133900_00133900, &recomp_gen::fn_sub_133900_00133900__recomp},
    {"sub_1339A0", 0x1339A0, &recomp_gen::fn_sub_1339A0_001339a0, &recomp_gen::fn_sub_1339A0_001339a0__recomp},
    {"sub_133A80", 0x133A80, &recomp_gen::fn_sub_133A80_00133a80, &recomp_gen::fn_sub_133A80_00133a80__recomp},
    {"sub_133B80", 0x133B80, &recomp_gen::fn_sub_133B80_00133b80, &recomp_gen::fn_sub_133B80_00133b80__recomp},
    {"sub_133C40", 0x133C40, &recomp_gen::fn_sub_133C40_00133c40, &recomp_gen::fn_sub_133C40_00133c40__recomp},
    {"sub_133D00", 0x133D00, &recomp_gen::fn_sub_133D00_00133d00, &recomp_gen::fn_sub_133D00_00133d00__recomp},
    {"sub_133D30", 0x133D30, &recomp_gen::fn_sub_133D30_00133d30, &recomp_gen::fn_sub_133D30_00133d30__recomp},
    {"sub_134A10", 0x134A10, &recomp_gen::fn_sub_134A10_00134a10, &recomp_gen::fn_sub_134A10_00134a10__recomp},
    {"sub_134D80", 0x134D80, &recomp_gen::fn_sub_134D80_00134d80, &recomp_gen::fn_sub_134D80_00134d80__recomp},
    {"sub_135120", 0x135120, &recomp_gen::fn_sub_135120_00135120, &recomp_gen::fn_sub_135120_00135120__recomp},
    {"sub_135460", 0x135460, &recomp_gen::fn_sub_135460_00135460, &recomp_gen::fn_sub_135460_00135460__recomp},
    {"sub_1365B0", 0x1365B0, &recomp_gen::fn_sub_1365B0_001365b0, &recomp_gen::fn_sub_1365B0_001365b0__recomp},
    {"sub_136750", 0x136750, &recomp_gen::fn_sub_136750_00136750, &recomp_gen::fn_sub_136750_00136750__recomp},
    {"sub_1368A0", 0x1368A0, &recomp_gen::fn_sub_1368A0_001368a0, &recomp_gen::fn_sub_1368A0_001368a0__recomp},
    {"sub_137300", 0x137300, &recomp_gen::fn_sub_137300_00137300, &recomp_gen::fn_sub_137300_00137300__recomp},
    {"sub_138EE0", 0x138EE0, &recomp_gen::fn_sub_138EE0_00138ee0, &recomp_gen::fn_sub_138EE0_00138ee0__recomp},
    {"sub_1392D0", 0x1392D0, &recomp_gen::fn_sub_1392D0_001392d0, &recomp_gen::fn_sub_1392D0_001392d0__recomp},
    {"sub_13BCE0", 0x13BCE0, &recomp_gen::fn_sub_13BCE0_0013bce0, &recomp_gen::fn_sub_13BCE0_0013bce0__recomp},
    {"sub_13BE50", 0x13BE50, &recomp_gen::fn_sub_13BE50_0013be50, &recomp_gen::fn_sub_13BE50_0013be50__recomp},
    {"sub_13C240", 0x13C240, &recomp_gen::fn_sub_13C240_0013c240, &recomp_gen::fn_sub_13C240_0013c240__recomp},
    {"sub_13C6A0", 0x13C6A0, &recomp_gen::fn_sub_13C6A0_0013c6a0, &recomp_gen::fn_sub_13C6A0_0013c6a0__recomp},
    {"sub_13CC90", 0x13CC90, &recomp_gen::fn_sub_13CC90_0013cc90, &recomp_gen::fn_sub_13CC90_0013cc90__recomp},
    {"sub_13CF80", 0x13CF80, &recomp_gen::fn_sub_13CF80_0013cf80, &recomp_gen::fn_sub_13CF80_0013cf80__recomp},
    {"sub_141590", 0x141590, &recomp_gen::fn_sub_141590_00141590, &recomp_gen::fn_sub_141590_00141590__recomp},
    {"sub_145350", 0x145350, &recomp_gen::fn_sub_145350_00145350, &recomp_gen::fn_sub_145350_00145350__recomp},
    {"sub_14ED20", 0x14ED20, &recomp_gen::fn_sub_14ED20_0014ed20, &recomp_gen::fn_sub_14ED20_0014ed20__recomp},
    {"sub_14EE80", 0x14EE80, &recomp_gen::fn_sub_14EE80_0014ee80, &recomp_gen::fn_sub_14EE80_0014ee80__recomp},
    {"sub_14EF60", 0x14EF60, &recomp_gen::fn_sub_14EF60_0014ef60, &recomp_gen::fn_sub_14EF60_0014ef60__recomp},
    {"sub_14F320", 0x14F320, &recomp_gen::fn_sub_14F320_0014f320, &recomp_gen::fn_sub_14F320_0014f320__recomp},
    {"sub_14F680", 0x14F680, &recomp_gen::fn_sub_14F680_0014f680, &recomp_gen::fn_sub_14F680_0014f680__recomp},
    {"sub_154770", 0x154770, &recomp_gen::fn_sub_154770_00154770, &recomp_gen::fn_sub_154770_00154770__recomp},
    {"sub_1548A0", 0x1548A0, &recomp_gen::fn_sub_1548A0_001548a0, &recomp_gen::fn_sub_1548A0_001548a0__recomp},
    {"sub_15C460", 0x15C460, &recomp_gen::fn_sub_15C460_0015c460, &recomp_gen::fn_sub_15C460_0015c460__recomp},
    {"sub_15C520", 0x15C520, &recomp_gen::fn_sub_15C520_0015c520, &recomp_gen::fn_sub_15C520_0015c520__recomp},
    {"sub_15D8E0", 0x15D8E0, &recomp_gen::fn_sub_15D8E0_0015d8e0, &recomp_gen::fn_sub_15D8E0_0015d8e0__recomp},
    {"sub_1616D0", 0x1616D0, &recomp_gen::fn_sub_1616D0_001616d0, &recomp_gen::fn_sub_1616D0_001616d0__recomp},
    {"sub_1617D0", 0x1617D0, &recomp_gen::fn_sub_1617D0_001617d0, &recomp_gen::fn_sub_1617D0_001617d0__recomp},
    {"sub_161D60", 0x161D60, &recomp_gen::fn_sub_161D60_00161d60, &recomp_gen::fn_sub_161D60_00161d60__recomp},
    {"sub_1669B0", 0x1669B0, &recomp_gen::fn_sub_1669B0_001669b0, &recomp_gen::fn_sub_1669B0_001669b0__recomp},
    {"sub_166A50", 0x166A50, &recomp_gen::fn_sub_166A50_00166a50, &recomp_gen::fn_sub_166A50_00166a50__recomp},
    {"sub_1675B0", 0x1675B0, &recomp_gen::fn_sub_1675B0_001675b0, &recomp_gen::fn_sub_1675B0_001675b0__recomp},
    {"sub_1675E0", 0x1675E0, &recomp_gen::fn_sub_1675E0_001675e0, &recomp_gen::fn_sub_1675E0_001675e0__recomp},
    {"sub_1678E0", 0x1678E0, &recomp_gen::fn_sub_1678E0_001678e0, &recomp_gen::fn_sub_1678E0_001678e0__recomp},
    {"sub_167EC0", 0x167EC0, &recomp_gen::fn_sub_167EC0_00167ec0, &recomp_gen::fn_sub_167EC0_00167ec0__recomp},
    {"sub_167F40", 0x167F40, &recomp_gen::fn_sub_167F40_00167f40, &recomp_gen::fn_sub_167F40_00167f40__recomp},
    {"sub_168040", 0x168040, &recomp_gen::fn_sub_168040_00168040, &recomp_gen::fn_sub_168040_00168040__recomp},
    {"sub_168100", 0x168100, &recomp_gen::fn_sub_168100_00168100, &recomp_gen::fn_sub_168100_00168100__recomp},
    {"sub_168220", 0x168220, &recomp_gen::fn_sub_168220_00168220, &recomp_gen::fn_sub_168220_00168220__recomp},
    {"sub_1685E0", 0x1685E0, &recomp_gen::fn_sub_1685E0_001685e0, &recomp_gen::fn_sub_1685E0_001685e0__recomp},
    {"sub_168720", 0x168720, &recomp_gen::fn_sub_168720_00168720, &recomp_gen::fn_sub_168720_00168720__recomp},
    {"sub_168770", 0x168770, &recomp_gen::fn_sub_168770_00168770, &recomp_gen::fn_sub_168770_00168770__recomp},
    {"sub_169040", 0x169040, &recomp_gen::fn_sub_169040_00169040, &recomp_gen::fn_sub_169040_00169040__recomp},
    {"sub_169330", 0x169330, &recomp_gen::fn_sub_169330_00169330, &recomp_gen::fn_sub_169330_00169330__recomp},
    {"sub_169AE0", 0x169AE0, &recomp_gen::fn_sub_169AE0_00169ae0, &recomp_gen::fn_sub_169AE0_00169ae0__recomp},
    {"sub_16A6A0", 0x16A6A0, &recomp_gen::fn_sub_16A6A0_0016a6a0, &recomp_gen::fn_sub_16A6A0_0016a6a0__recomp},
    {"sub_18B6D0", 0x18B6D0, &recomp_gen::fn_sub_18B6D0_0018b6d0, &recomp_gen::fn_sub_18B6D0_0018b6d0__recomp},
    {"sub_18BC10", 0x18BC10, &recomp_gen::fn_sub_18BC10_0018bc10, &recomp_gen::fn_sub_18BC10_0018bc10__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair through two trampolines that (a) set chosen FPRs after the random register file and (b) optionally give each
// body a fresh, identical stand-in world (the heap behind H_Malloc and the RW slots, printf / sprintf, the H_Cdvd layer
// over extracted/, plus per-test recorders for callees that are not emitted) whose call logs must match. The blocks a
// chain of pairs allocated stay reserved in the next worlds (`g_live`), so a chain sees one heap.
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    std::vector<std::tuple<u32, std::string, u64>> recorders;
};
Tramp g_t;
std::map<u32, u32> g_live;
int g_pairs = 0;

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    g_t.world[K] = std::make_unique<StandInWorld>();
    for (const auto& [p, n] : g_live) g_t.world[K]->heap.reserve(p, n);
    install_standard(*g_t.world[K]);
    for (const auto& [va, name, v0] : g_t.recorders) g_t.world[K]->si.install_recorder(va, name, v0);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = false;
    std::vector<std::tuple<u32, std::string, u64>> recorders;
};

hgp::Run ui_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    g_t.recorders = o.recorders;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) {
        expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
        g_live = g_t.world[1]->heap.live();
    }
    ++g_pairs;
    if (r.stopped) MESSAGE(std::string(what) << ": both bodies stopped at " << hex64(r.stop_pc) << " (" << r.what << ")");
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
const StandIns& log_of() { return g_t.world[1]->si; }
std::vector<StandInCall> calls_of(u32 va) {
    std::vector<StandInCall> out;
    for (const StandInCall& c : log_of().log)
        if (c.va == va) out.push_back(c);
    return out;
}

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va & 0x1FFFFFFu]; }
float rf(const Machine& m, u32 va) { return std::bit_cast<float>(r32(m, va)); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
u32 fbits(float f) { return std::bit_cast<u32>(f); }
u64 xy(float x, float y) { return static_cast<u64>(fbits(y)) << 32 | fbits(x); }

constexpr u32 kGpReg = 0x7D2CF0u;
constexpr u32 gpv(s32 off) { return kGpReg + static_cast<u32>(off); }  // a $gp-relative word
constexpr u32 kOut = 0x01F40000u;  // free in every snapshot (stand_ins.h) and in the ELF image
constexpr u32 kRwCalloc = 0x104040u;
constexpr u32 kSprDrawSpriteBasic = 0x1159F0u;

// The same pair for two composite bodies (a chain of calls on one stand-in world).
hgp::Run fn_pair(Machine& m, Fn hand, Fn recomp, const Args& a, u32 seed, const char* what, const Opt& o) {
    g_t.fn[0] = hand;
    g_t.fn[1] = recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    g_t.recorders = o.recorders;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) {
        expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
        g_live = g_t.world[1]->heap.live();
    }
    ++g_pairs;
    if (r.stopped) MESSAGE(std::string(what) << ": both bodies stopped at " << hex64(r.stop_pc) << " (" << r.what << ")");
    return r;
}

// The camp sprite set-up chain (hand bodies in run 0, recompiled in run 1): create "H_CampSprSetupFile" (sub_119F10), load
// its PAK (the H_Cdvd_ReadSync stand-in), then one update in state 2 (sub_119AA0: "wait for the PAK alone" -> 3). (State 0
// takes the PAK's 14 entries through H_Cdvd_ArchiveGetFile, whose header copies alone exceed the harness's 20,000
// check-point cap: state 0 is covered by the random worlds and the faithfulness audit.)
struct SetupChain {
    Fn create, update;
};
SetupChain g_chain[2];
u32 g_chain_task = 0;
template <int K>
void setup_chain(EEContext& c) {
    c.gpr[GPR_A0].u64[0] = 0;
    c.gpr[GPR_A1].u64[0] = 0;
    g_chain[K].create(c);
    const u32 task = static_cast<u32>(c.gpr[GPR_V0].u64[0]);
    g_chain_task = task;
    if (task == 0) return;
    const u32 work = c.memory->read<u32>(task + 0x3C);
    c.gpr[GPR_A0].u64[0] = sx(c.memory->read<u32>(work + ui5::sf::kPak));
    recomp_gen::fn_H_Cdvd_ReadSync_001023a0(c);
    c.memory->write<u32>(work + ui5::sf::kState, 2);
    c.gpr[GPR_A0].u64[0] = sx(task);
    g_chain[K].update(c);
}

bool load_snapshot(Machine& m, const char* s) {
    std::vector<u8> snap = read_snapshot(s);
    if (snap.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    return true;
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; the tests below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(ui5): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int stops = 0, pairs = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// =====================================================================================================================
// Tween records: the setter's fields, the allocator, the camp list's slide-in / fade-in / fade-out layouts
// =====================================================================================================================
TEST_CASE("game(ui5): tween records and the camp list's layouts") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 1;
    // sub_18BC10 [H_Camp_TweenStart]: every argument lands in its field, the frame restarts at 0
    for (const auto& [from, to, first, last] : {std::tuple{xy(-154.f, 59.f), xy(46.f, 59.f), 4u, 10u},
                                               std::tuple{xy(1.5f, -2.f), xy(700.f, 385.f), 0u, 7u}}) {
        const u32 rec = kOut;
        std::memset(m.at(rec), 0xCD, 68);
        w32(m, kSp, first);  // the 9th / 10th arguments: the caller's stack slots 0 / 1
        w32(m, kSp + 8, last);
        Opt o;
        o.gpr_in = {{GPR_T0, from}, {GPR_T1, to}, {GPR_T2, 0x11}, {GPR_T3, 0x22}};
        o.fpr = {{12, fbits(5.f)}};
        ui_pair(m, "sub_18BC10", {sx(rec), 3, 2, 1}, seed++, "tween start", o);
        CHECK(r32(m, rec + ui5::tw::kActive) == 1);
        CHECK(r32(m, rec + ui5::tw::kKind) == 3);
        CHECK(r32(m, rec + ui5::tw::kMode) == 2);
        CHECK(r32(m, rec + ui5::tw::kCurve) == 1);
        CHECK(r32(m, rec + ui5::tw::kExtraA) == 0x11);
        CHECK(r32(m, rec + ui5::tw::kExtraB) == 0x22);
        CHECK(r32(m, rec + ui5::tw::kFromX) == static_cast<u32>(from));
        CHECK(r32(m, rec + ui5::tw::kFromY) == static_cast<u32>(from >> 32));
        CHECK(r32(m, rec + ui5::tw::kToX) == static_cast<u32>(to));
        CHECK(r32(m, rec + ui5::tw::kToY) == static_cast<u32>(to >> 32));
        CHECK(rf(m, rec + ui5::tw::kZ) == 5.f);
        CHECK(r32(m, rec + ui5::tw::kFirst) == first);
        CHECK(r32(m, rec + ui5::tw::kLast) == last);
        CHECK(r32(m, rec + ui5::tw::kFrame) == 0);
        CHECK(r32(m, rec + 56) == 0xCDCDCDCDu);  // +56..+67 untouched
    }
    // sub_18B6D0 [H_Camp_AllocTweens]: RwCalloc(count, 68, 0x40000) through the slot 0x960184
    write_rw_slots(m);
    g_live.clear();
    Opt si;
    si.standins = true;
    for (u32 n : {200u, 1u, 15u}) {
        const hgp::Run r = ui_pair(m, "sub_18B6D0", {n, 0, 0, 0}, seed++, "tween alloc", si);
        const auto c = calls_of(kRwCalloc);
        REQUIRE(c.size() == 1);
        CHECK(c[0].args[0] == n);
        CHECK(c[0].args[1] == 68u);
        CHECK(c[0].args[2] == 0x40000u);
        CHECK(v0_of(r) == c[0].v0);
    }
    // the camp list's layouts on 15 records at gp-19876, for every cursor row
    const u32 kTw = kOut + 0x1000, kRoot = kOut + 0x800;
    w32(m, gpv(ui5::g::kCampTweens), kTw);
    struct Layout {
        const char* fn;
        u32 mode, curve;
        bool slide;
    };
    for (const Layout& l : {Layout{"sub_11C550", 2, 1, true}, Layout{"sub_11CC80", 0, 1, false}, Layout{"sub_11D3A0", 0, 2, false},
                            Layout{"sub_11DA80", 0, 2, false}}) {
        for (u32 cursor = 0; cursor <= 6; ++cursor) {
            std::memset(m.at(kTw), 0, 15 * 68);
            std::memset(m.at(kRoot), 0, 44);
            w32(m, kRoot + 16, cursor);
            ui_pair(m, l.fn, {sx(kRoot), 0, 0, 0}, seed++, l.fn);
            for (u32 i = 0; i < 7; ++i) {  // the seven rows: x 46 - 200 -> 46, y 59 + 19 i
                const u32 rec = kTw + 68 * i;
                INFO(l.fn << " row " << i << " cursor " << cursor);
                CHECK(r32(m, rec + ui5::tw::kActive) == 1);
                CHECK(r32(m, rec + ui5::tw::kMode) == l.mode);
                CHECK(r32(m, rec + ui5::tw::kCurve) == l.curve);
                CHECK(rf(m, rec + ui5::tw::kFromX) == 46.f - 200.f);
                CHECK(rf(m, rec + ui5::tw::kToX) == 46.f);
                CHECK(rf(m, rec + ui5::tw::kToY) == 59.f + 19.f * static_cast<float>(i));
                CHECK(rf(m, rec + ui5::tw::kFromY) == rf(m, rec + ui5::tw::kToY));
                CHECK(r32(m, rec + ui5::tw::kFirst) == (l.slide ? i + 4 : 0u));
                CHECK(r32(m, rec + ui5::tw::kLast) == (l.slide ? i + 10 : 10u));
            }
            // the highlight (record 10): from x -19 to 181 at y 57 + 19 cursor
            const u32 hl = kTw + 680;
            CHECK(rf(m, hl + ui5::tw::kFromX) == -19.f);
            CHECK(rf(m, hl + ui5::tw::kToX) == 181.f);
            CHECK(rf(m, hl + ui5::tw::kToY) == 57.f + 19.f * static_cast<float>(cursor));
        }
    }
    // the two fade-out bodies are copies: the same records from the same input
    std::vector<u8> a(15 * 68), b(15 * 68);
    w32(m, kRoot + 16, 3);
    std::memset(m.at(kTw), 0, 15 * 68);
    Opt z;
    z.fpr = {{12, fbits(0.f)}};  // the records take their z from the caller's $f12
    ui_pair(m, "sub_11D3A0", {sx(kRoot), 0, 0, 0}, seed++, "fade out", z);
    std::memcpy(a.data(), m.at(kTw), a.size());
    std::memset(m.at(kTw), 0, 15 * 68);
    ui_pair(m, "sub_11DA80", {sx(kRoot), 0, 0, 0}, seed++, "fade out 2", z);
    std::memcpy(b.data(), m.at(kTw), b.size());
    CHECK(a == b);
}

// =====================================================================================================================
// The flash-control task: a whole screen transition frame by frame, the finish state, the request table
// =====================================================================================================================
TEST_CASE("game(ui5): flash-control transitions") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    g_live.clear();
    const u32 kTask = kOut, kWork = kOut + 0x100, kAnm = kOut + 0x400;
    std::memset(m.at(kTask), 0, 0x68);
    std::memset(m.at(kWork), 0, 108);
    w32(m, kTask + ui5::task::kWork, kWork);
    Opt o;
    o.standins = true;
    // the .anm task functions are not emitted: recorders (the sound request sub_10A4E0 and the voice layer run)
    o.recorders = {{0x111DD0u, "anm create", sx(kAnm)}, {0x111EC0u, "anm loaded", 1}, {0x111EE0u, "anm start", 0},
                   {0x111F20u, "anm play flag", 0},   {0x111D50u, "anm draw", 0}};
    u32 seed = 100;
    auto frame = [&](const char* what) { return ui_pair(m, "sub_11EA20", {sx(kTask), 0, 0, 0}, seed++, what, o); };
    // state 1: arm the main-list transition (state 2, done 0, step 0)
    w32(m, kWork + ui5::fl::kState, 1);
    w32(m, kWork + ui5::fl::kDone, 7);
    CHECK(v0_of(frame("arm")) == 0);
    CHECK(r32(m, kWork + ui5::fl::kState) == 2);
    CHECK(r32(m, kWork + ui5::fl::kDone) == 0);
    CHECK(r32(m, kWork + ui5::fl::kStep) == 0);
    // step 0: no .anm in slot 0 -> load camp/main_all/if_c_mai01.anm
    frame("load");
    {
        const auto c = calls_of(0x111DD0u);
        REQUIRE(c.size() == 1);
        CHECK(m.str(static_cast<u32>(c[0].args[2])) == "camp/main_all/if_c_mai01.anm");
        CHECK(c[0].args[1] == 6333u);
    }
    CHECK(r32(m, kWork + ui5::fl::kLoading) == kAnm);
    CHECK(r32(m, kWork + ui5::fl::kStep) == 1);
    // step 1: loaded -> started, done, 24 frames, the sound
    frame("start");
    CHECK(calls_of(0x111EE0u).size() == 1);
    CHECK(calls_of(0x111F20u).size() == 1);
    CHECK(r32(m, kWork + ui5::fl::kDone) == 1);
    CHECK(r32(m, kWork + ui5::fl::kTimer) == 24);
    CHECK(r32(m, kWork + ui5::fl::kStep) == 2);
    // step 2: 24 frames, then the new .anm takes slot 0 and the dispatcher is idle again
    int frames = 0;
    while (r32(m, kWork + ui5::fl::kState) == 2 && frames < 40) {
        frame("run");
        ++frames;
    }
    CHECK(frames == 24);
    CHECK(r32(m, kWork + ui5::fl::kState) == 0);
    CHECK(r32(m, kWork + ui5::fl::kStep) == 999);
    CHECK(r32(m, kWork + ui5::fl::kAnmSlots) == kAnm);
    CHECK(r32(m, kWork + ui5::fl::kLoading) == 0);
    // again with the .anm in slot 0: one frame draws it and the transition is over
    w32(m, kWork + ui5::fl::kState, 1);
    frame("arm again");
    frame("reuse");
    CHECK(calls_of(0x111D50u).size() == 1);
    CHECK(calls_of(0x111DD0u).empty());
    CHECK(r32(m, kWork + ui5::fl::kState) == 0);
    CHECK(r32(m, kWork + ui5::fl::kDone) == 1);
    // idle returns 0, state 6 finishes the task (-1), an out-of-table state returns 0
    w32(m, kWork + ui5::fl::kState, 0);
    CHECK(v0_of(frame("idle")) == 0);
    w32(m, kWork + ui5::fl::kState, 6);
    CHECK(static_cast<s64>(v0_of(frame("finish"))) == -1);
    w32(m, kWork + ui5::fl::kState, 59);
    CHECK(v0_of(frame("beyond the table")) == 0);
    // sub_11E380 [H_CampFlash_Request]: busy -> nothing; request 0 -> state 13; request 1 from the main list -> 1
    struct Req {
        u32 state, screen, req, want_state, want_done;
    };
    for (const Req& q : {Req{5, 0, 1, 5, 9}, Req{0, 0, 0, 13, 0}, Req{0, 0, 1, 1, 0}, Req{0, 1, 1, 0, 1}, Req{0, 3, 1, 11, 0}}) {
        w32(m, kWork + ui5::fl::kState, q.state);
        w32(m, kWork + ui5::fl::kScreen, q.screen);
        w32(m, kWork + ui5::fl::kDone, 9);
        ui_pair(m, "sub_11E380", {sx(kTask), q.req, 0, 0}, seed++, "flash request");
        INFO("state " << q.state << " screen " << q.screen << " request " << q.req);
        CHECK(r32(m, kWork + ui5::fl::kState) == q.want_state);
        CHECK(r32(m, kWork + ui5::fl::kDone) == q.want_done);
    }
}

// =====================================================================================================================
// The equipment stock of a replay snapshot through the list builders (real game data)
// =====================================================================================================================
TEST_CASE("game(ui5): equipment lists on replay snapshots") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    int snapshots = 0;
    u32 seed = 200;
    for (const char* snap : {"b_5800", "climb_ref_17000", "climb_ref_39820"}) {
    if (!load_snapshot(m, snap)) {
        MESSAGE("SKIP: no " << std::string(snap) << " snapshot under extracted/_ours");
        continue;
    }
    ++snapshots;
    const u32 stock = r32(m, 0x836794u);  // EquipEntry[300] of owner 1 (gamedata.h kHeroEquipmentStock)
    REQUIRE(stock != 0);
    struct Entry {
        u16 id;
        u32 mask;
        u8 unk08, effect;
        u16 power, accuracy, evasion, defense;
    };
    std::vector<Entry> e(300);
    u32 held = 0;
    for (u32 i = 0; i < 300; ++i) {
        const u32 p = stock + 20 * i;
        e[i] = {r16(m, p), r32(m, p + 4), r8(m, p + 8), r8(m, p + 9), r16(m, p + 10), r16(m, p + 12), r16(m, p + 14), r16(m, p + 16)};
        held += e[i].id != 0;
    }
    auto kind_of = [](u16 id) { const s16 s = static_cast<s16>(id); return s < 1000 ? 0u : s < 2000 ? 1u : s < 3000 ? 2u : s < 4000 ? 3u : 4u; };
    // sub_13CC90: every held entry, ordered by item id, 36-byte rows from +100
    const u32 kList = kOut;
    std::memset(m.at(kList), 0xEE, 11640);
    ui_pair(m, "sub_13CC90", {sx(kList), 0, 0, 0}, seed++, "equipment stock list");
    const u32 n = r32(m, kList + 11620);
    CHECK(n == held);
    for (u32 k = 0; k < 21; ++k) CHECK(r32(m, kList + 12 + 4 * k) == 0);
    u32 prev = 0;
    for (u32 k = 0; k < n && k < 300; ++k) {
        const u32 row = kList + 100 + 36 * k;
        const u32 id = r32(m, row), idx = r32(m, row + 4);
        INFO("row " << k << " id " << id << " index " << idx);
        REQUIRE(idx < 300);
        CHECK(id == e[idx].id);
        CHECK(id >= prev);
        prev = id;
        CHECK(r8(m, row + 26) == kind_of(e[idx].id));
        CHECK(r8(m, row + 24) == e[idx].effect);
        CHECK(r8(m, row + 25) == e[idx].unk08);
        if (e[idx].mask & 0x1FFFFFu) CHECK(r32(m, row + 20) == static_cast<u32>(std::countr_zero(e[idx].mask)));
        switch (kind_of(e[idx].id)) {
        case 0:
            CHECK(r16(m, row + 28) == e[idx].power);
            CHECK(r16(m, row + 30) == e[idx].accuracy);
            break;
        case 1: CHECK(r16(m, row + 32) == e[idx].evasion); break;
        case 2: CHECK(r16(m, row + 34) == e[idx].defense); break;
        default: break;
        }
    }
    // sub_131090: the held entries of one kind (every item flag word served as 0x20 by a recorder), as indices ordered by id
    Opt o;
    o.standins = true;
    o.recorders = {{0x1712D0u, "item flags", 0x20}};
    g_live.clear();
    for (u32 kind = 0; kind <= 4; ++kind) {
        std::memset(m.at(kList), 0xEE, 0x400);
        const hgp::Run r = ui_pair(m, "sub_131090", {sx(kList), 0, 1, kind}, seed++, "equipment of a kind", o);
        u32 want = 0;
        for (const Entry& x : e) want += x.id != 0 && kind_of(x.id) == kind;
        CHECK(static_cast<u32>(v0_of(r)) == want);
        u32 last = 0;
        for (u32 k = 0; k < want; ++k) {
            const u16 idx = r16(m, kList + 2 * k);
            REQUIRE(idx < 300);
            CHECK(kind_of(e[idx].id) == kind);
            CHECK(e[idx].id >= last);
            last = e[idx].id;
        }
    }
    // sub_131000, the comparator: by item id
    for (const auto& [i, j] : {std::pair{0u, 1u}, std::pair{5u, 2u}, std::pair{7u, 7u}}) {
        w16(m, kList, static_cast<u16>(i));
        w16(m, kList + 2, static_cast<u16>(j));
        const hgp::Run r = ui_pair(m, "sub_131000", {sx(kList), sx(kList + 2), 0, 0}, seed++, "stock comparator");
        const s32 want = e[i].id == e[j].id ? 0 : e[i].id > e[j].id ? 1 : -1;
        CHECK(static_cast<s32>(v0_of(r)) == want);
    }
    MESSAGE(std::string(snap) << ": " << held << " equipment entries held");
    }
    if (snapshots == 0) MESSAGE("SKIP: no replay snapshot");
}

// =====================================================================================================================
// The camp sprite set-up task on the real camp/camp_all.pak (file / heap stand-ins): create, load, update, destroy
// =====================================================================================================================
TEST_CASE("game(ui5): the camp sprite set-up task on camp_all.pak") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    // (on the ELF image: the dorm snapshot's long task and request lists make the chain exceed the harness's check-point cap)
    // the PAK on the host: 252-byte name, u32 size, the data at +256, entries 64-byte aligned
    const std::string host = FakeCd(*std::make_unique<GuestHeap>()).host_path("camp/camp_all.pak");
    std::vector<u8> pak;
    if (FILE* f = host.empty() ? nullptr : std::fopen(host.c_str(), "rb")) {
        std::fseek(f, 0, SEEK_END);
        pak.resize(static_cast<std::size_t>(std::ftell(f)));
        std::fseek(f, 0, SEEK_SET);
        if (std::fread(pak.data(), 1, pak.size(), f) != pak.size()) pak.clear();
        std::fclose(f);
    }
    if (pak.empty()) {
        MESSAGE("SKIP: camp/camp_all.pak not under extracted/");
        return;
    }
    std::vector<u32> data_off;
    for (u32 off = 0; data_off.size() < 14 && off + 256 <= pak.size();) {
        u32 size;
        std::memcpy(&size, pak.data() + off + 252, 4);
        data_off.push_back(off + 256);
        off += 256 + ((size + 63) & ~63u);
    }
    REQUIRE(data_off.size() == 14);
    write_rw_slots(m);
    g_live.clear();
    w32(m, gpv(ui5::g::kCampSetupTask), 0);
    const u32 kFile = kOut + 0x600;  // the sprite file every sprCreateHandleFromData returns: s16 state 5 (loaded)
    std::memset(m.at(kFile), 0, 0x40);
    w16(m, kFile, 5);
    for (u32 i = 0; i < 14; ++i) w32(m, 0x833B70u + 4 * i, 0xEEEEEEEEu);
    g_chain[0] = {&recomp_gen::fn_sub_119F10_00119f10, &recomp_gen::fn_sub_119AA0_00119aa0};
    g_chain[1] = {&recomp_gen::fn_sub_119F10_00119f10__recomp, &recomp_gen::fn_sub_119AA0_00119aa0__recomp};
    Opt o;
    o.standins = true;
    o.recorders = {{0x112420u, "sprCreateHandleFromData", sx(kFile)}, {0x1124B0u, "sprFileRelease", 0}, {0x3C7B90u, "sub_3C7B90", 0}};
    const hgp::Run r0 = fn_pair(m, &setup_chain<0>, &setup_chain<1>, {0, 0, 0, 0}, 600, "camp sprite set-up: create, load", o);
    REQUIRE(!r0.stopped);
    const u32 task = g_chain_task;
    REQUIRE(task != 0);
    const u32 work = r32(m, task + 0x3C);
    {
        const auto req = calls_of(0x100D80u);
        REQUIRE(req.size() == 1);
        CHECK(req[0].text == FakeCd::build_path("camp/camp_all.pak"));  // The Journey (scenario 0 in the ELF image)
        const auto rd = calls_of(0x1023A0u);
        REQUIRE(rd.size() == 1);
        CHECK(rd[0].extra == pak.size());  // the whole file loaded
        CHECK(r32(m, work + ui5::sf::kState) == 3);  // state 2 saw the PAK loaded
        CHECK(r32(m, gpv(ui5::g::kCampSetupTask)) == task);
        CHECK(calls_of(0x3C7B90u).size() == 1);
    }
    // state 1: the 14 files of the PAK's entries 0..13 (their data offsets in the file: data_off) are polled; when every
    // one is loaded they become the camp sprite-file table 0x833B70 and the task is done (3)
    for (bool all_ready : {false, true}) {
        w32(m, work + ui5::sf::kState, 1);
        for (u32 i = 0; i < 14; ++i) w32(m, work + ui5::sf::kFiles + 4 * i, kFile);
        w16(m, kFile, static_cast<u16>(all_ready ? 5 : 4));
        ui_pair(m, "sub_119AA0", {sx(task), 0, 0, 0}, all_ready ? 601 : 602, "set-up update, state 1", o);
        INFO("all files ready: " << all_ready);
        CHECK(r32(m, work + ui5::sf::kState) == (all_ready ? 3u : 1u));
        for (u32 i = 0; i < 14; ++i) CHECK(r32(m, 0x833B70u + 4 * i) == (all_ready ? kFile : 0xEEEEEEEEu));
    }
    // the destroy: every file released, the table and the globals cleared (the PAK request was destroyed by its own world)
    w32(m, work + ui5::sf::kPak, 0);
    w32(m, work + ui5::sf::kTweens, 0);
    ui_pair(m, "sub_119E00", {sx(task), 0, 0, 0}, 603, "set-up destroy", o);
    CHECK(calls_of(0x1124B0u).size() == 14);
    for (u32 i = 0; i < 14; ++i) {
        CHECK(r32(m, 0x833B70u + 4 * i) == 0);
        CHECK(r32(m, work + ui5::sf::kFiles + 4 * i) == 0);
    }
    CHECK(r32(m, gpv(ui5::g::kCampSetupTask)) == 0);
    // the PAK's sprite entries the update takes, for the record: 14 .spr files before the first .tmx
    for (u32 i = 0; i < 14; ++i) CHECK(std::string(reinterpret_cast<const char*>(pak.data() + data_off[i] - 256)).ends_with(".spr"));
}

// =====================================================================================================================
// Status screen draws: the level digits, the condition icon, the bit -> index table
// =====================================================================================================================
TEST_CASE("game(ui5): status digits, condition icons and the equipment bit table") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    g_live.clear();
    Opt o;
    o.standins = true;
    o.recorders = {{kSprDrawSpriteBasic, "sprDrawSpriteBasic", 0}};
    u32 seed = 300;
    // sub_124E60: a persona level (+4) as one or two digits of sprite font 2: sprite 11 + digit
    const u32 kRec = kOut;
    for (u32 level : {0u, 1u, 9u, 10u, 42u, 99u}) {
        std::memset(m.at(kRec), 0, 16);
        w8(m, kRec + 4, static_cast<u8>(level));
        ui_pair(m, "sub_124E60", {xy(100.f, 200.f), sx(kRec), 0x80, 0}, seed++, "persona level", o);
        const auto c = calls_of(kSprDrawSpriteBasic);
        INFO("level " << level);
        if (level < 10) {
            REQUIRE(c.size() == 1);
            CHECK(c[0].args[2] == 11 + level);
        } else {
            REQUIRE(c.size() == 2);
            CHECK(c[0].args[2] == 11 + level / 10);
            CHECK(c[1].args[2] == 11 + level % 10);
        }
        for (const StandInCall& k : c) CHECK((k.args[3] & 0xFF) == 0x80);
    }
    // sub_123F80: the hero's condition word (gGlobalWork +0x6C) -> sprite 11, 13, 12, 16, 14, 15, else 43
    const u32 kSprite[6] = {11, 13, 12, 16, 14, 15};
    for (u32 cond : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 0x40u}) {
        w16(m, 0x83626Cu, static_cast<u16>(cond));
        ui_pair(m, "sub_123F80", {xy(0.f, 0.f), 1, 0xFF, 0}, seed++, "condition icon", o);
        const auto c = calls_of(kSprDrawSpriteBasic);
        REQUIRE(c.size() == 1);
        INFO("condition " << cond);
        CHECK(c[0].args[1] == r32(m, 0x833B90u));
        CHECK(c[0].args[2] == (cond < 6 ? kSprite[cond] : 43u));
    }
    // sub_12DF50: the lowest flag of an equipment mask -> its index
    auto want_index = [](u32 bits) -> u32 {
        for (u32 b = 0; b < 16; ++b)
            if (bits & (1u << b)) return b & 7;
        if (bits & 0x10000u) return 9;
        if (bits & 0x20000u) return 10;
        if (bits & 0x40000u) return 11;
        if (bits & 0x180000u) return 13;
        return 0;
    };
    std::vector<u32> masks = {0, 0x1FFFFF, 0xFFE00000u};
    for (u32 b = 0; b < 32; ++b) masks.push_back(1u << b);
    for (u32 b = 1; b < 21; ++b) masks.push_back((1u << b) | (1u << (b - 1)));
    for (u32 mask : masks) {
        const hgp::Run r = ui_pair(m, "sub_12DF50", {mask, 0, 0, 0}, seed++, "mask index");
        INFO("mask " << hex64(mask));
        CHECK(static_cast<u32>(v0_of(r)) == want_index(mask));
    }
}

// =====================================================================================================================
// The camp screens' task creators on the dorm snapshot's task system (heap / file / printf stand-ins)
// =====================================================================================================================
TEST_CASE("game(ui5): camp screen task creators on the dorm snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m, "dorm_replay_4900")) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot under extracted/_ours");
        return;
    }
    g_live.clear();
    // a flash task for the status pages' creators (they clear its done flag)
    const u32 kFlashTask = kOut + 0x800, kFlashWork = kOut + 0x900;
    std::memset(m.at(kFlashTask), 0, 0x68);
    std::memset(m.at(kFlashWork), 0, 108);
    w32(m, kFlashTask + ui5::task::kWork, kFlashWork);
    w32(m, gpv(ui5::g::kCampFlashTask), kFlashTask);
    w32(m, gpv(ui5::g::kCampSetupTask), 0);
    Opt o;
    o.standins = true;
    u32 seed = 400;
    struct Want {
        const char* fn;
        Args args;
        std::map<unsigned, u64> gpr_in;
        const char* name;
        u32 size, priority, update, destroy;
        const char* path;  // the H_Cdvd request (nullptr: none)
    };
    const u64 pos = xy(50.f, 60.f);
    const std::vector<Want> wants = {
        {"H_Camp_CreateDrawTask", {0, 0, 0, 0}, {}, "H_CampDraw", 72, 6335, 0x11A050, 0x11A710, nullptr},
        {"H_Camp_CreateRootDrawTask", {0, sx(kFlashTask), 1, 0}, {}, "H_CampRootDraw", 44, 6335, 0x11B420, 0x11BAA0, nullptr},
        {"sub_11F1B0", {0, 0, 0, 0}, {}, "h_camp_flash_control", 108, 6335, 0x11EA20, 0x11F120, nullptr},
        {"sub_122660", {0, 0, 0, 0}, {}, "h_camp_pc_kani_control", 24, 6337, 0x121FF0, 0x122630, nullptr},
        {"sub_123000", {0, 7, 0, 0}, {}, "h_camp_persona_kani_control", 28, 6337, 0x122940, 0x122FD0, nullptr},
        {"sub_123570", {0, 6334, 3, 0}, {}, "H_CampPcStatusRoot", 36, 6334, 0x1230C0, 0x123540, nullptr},
        {"sub_11B2B0", {0, 0x2A, 0, 0}, {}, "CampPersonaTexControl", 276, 6335, 0x11B0B0, 0x11B210, nullptr},
        {"sub_130F20", {0, 6334, pos, 2}, {}, "H_CampSoubi1Draw", 708, 6334, 0x12C430, 0x130E40, nullptr},
        {"sub_1336B0", {0, 6334, pos, 4}, {}, "H_CampStatusPersonaDraw", 108, 6334, 0x1311D0, 0x1335D0, nullptr},
        {"sub_127B00", {0, 6334, pos, 5}, {{GPR_T0, 6}}, "H_CampStatusDraw", 72, 6334, 0x1269A0, 0x127A40, nullptr},
        {"sub_128040", {0, 6334, pos, 5}, {{GPR_T0, 6}}, "H_CampStatusPersonaDraw", 32, 6334, 0x127C00, 0x127FC0, nullptr},
        {"sub_167F40", {0, 6334, pos, 5}, {{GPR_T0, 6}, {GPR_T1, 7}}, "H_CampFrStatusPersonaDraw", 44, 6334, 0x167930, 0x167EC0, nullptr},
        {"sub_168770", {0, 6334, 0, 0}, {}, "H_FrStatusFlashDraw", 28, 6334, 0x168220, 0x168720, nullptr},
        {"sub_1548A0", {0, 6334, 0, 0}, {}, "H_CampSystemMenuDraw", 380, 6334, 0x14F7D0, 0x154770, nullptr},
        {"sub_14EE80", {0, 6334, 0, 0}, {}, "H_CampNewItem", 200, 6334, 0x14C5C0, 0x14ED20, "camp/camp_item.pak"},
        {"sub_1617D0", {0, 6334, 0, 0}, {}, "H_NewCampSkillDraw", 80, 6334, 0x160800, 0x1616D0, "camp/camp_skil.pak"},
        {"sub_136750", {0, 6334, 0, 0}, {}, "H_CampComuDraw", 416, 6334, 0x1355C0, 0x1365B0, "camp/comu/datComuHelp.bmd"},
        {"sub_166A50", {0, 6334, 3, 9}, {{GPR_T0, 1}}, "H_CampPartyStatusDraw", 56, 6334, 0x164920, 0x1669B0, "camp/camp_fr03.pak"},
        {"sub_119F10", {0, 0, 0, 0}, {}, "H_CampSprSetupFile", 72, 6335, 0x119AA0, 0x119E00, "camp/camp_all.pak"},
        {"sub_133D30", {0x1234, 0, 0, 0}, {}, "CampPersonaDispCtlFree", 8, 6335, 0x133C40, 0x133D00, nullptr},
    };
    for (const Want& w : wants) {
        Opt oo = o;
        oo.gpr_in = w.gpr_in;
        const hgp::Run r = ui_pair(m, w.fn, w.args, seed++, w.fn, oo);
        INFO(w.fn);
        REQUIRE(!r.stopped);
        const u32 task = static_cast<u32>(v0_of(r));
        REQUIRE(task != 0);
        const auto c = calls_of(kRwCalloc);
        REQUIRE(!c.empty());
        CHECK(c[0].args[0] == 1u);  // the work block: RwCalloc(1, size, 0x40000)
        CHECK(c[0].args[1] == w.size);
        CHECK(c[0].args[2] == 0x40000u);
        const u32 work = static_cast<u32>(c[0].v0);
        CHECK(m.str(task, 24) == std::string(w.name).substr(0, 23));  // name[23] is forced to 0
        CHECK(r32(m, task + 0x20) == w.priority);
        CHECK(r32(m, task + 0x34) == w.update);
        CHECK(r32(m, task + 0x38) == w.destroy);
        CHECK(r32(m, task + 0x3C) == work);
        if (w.path) {
            const auto q = calls_of(0x100D80u);
            REQUIRE(q.size() == 1);
            CHECK(q[0].text == FakeCd::build_path(w.path));
        }
        // the work fields each creator sets
        const std::string f = w.fn;
        if (f == "H_Camp_CreateRootDrawTask") {
            CHECK(r32(m, work + 36) == kFlashTask);
            CHECK(r32(m, work + 12) == 0xFFFFFFFFu);
            CHECK(r32(m, work + 8) == 1);
        } else if (f == "sub_122660") {
            CHECK(r16(m, work + 20) == 1);
        } else if (f == "sub_123000") {
            CHECK(r32(m, work + 16) == 7);  // the persona
            CHECK(r16(m, work + 24) == 1);
        } else if (f == "sub_123570") {
            CHECK(r32(m, work + 12) == 3);
        } else if (f == "sub_11B2B0") {
            CHECK(r32(m, work + ui5::ptc::kPersona) == 0x2A);
            CHECK(r32(m, gpv(ui5::g::kPersonaTexTask)) == task);
        } else if (f == "sub_130F20") {
            CHECK(rf(m, work + 8) == 50.f);
            CHECK(rf(m, work + 12) == 60.f);
            CHECK(r32(m, work + 20) == 1);
            CHECK(r16(m, work + 18) == 2);
        } else if (f == "sub_1336B0") {
            CHECK(rf(m, work + 16) == 50.f);
            CHECK(rf(m, work + 20) == 60.f);
            CHECK(r16(m, work + 24) == 4);
        } else if (f == "sub_127B00") {
            CHECK(rf(m, work + 4) == 50.f);
            CHECK(rf(m, work + 8) == 60.f);
            CHECK(r32(m, work + 32) == 1);
            CHECK(r16(m, work + 14) == 5);
            CHECK(r16(m, work + 16) == 6);
            CHECK(r32(m, kFlashWork + ui5::fl::kDone) == 0);
        } else if (f == "sub_128040") {
            CHECK(r32(m, work + 24) == 1);
            CHECK(r16(m, work + 14) == 5);
            CHECK(r16(m, work + 18) == 6);
        } else if (f == "sub_167F40") {
            CHECK(r32(m, work + 24) == 1);
            CHECK(r16(m, work + 14) == 5);
            CHECK(r16(m, work + 18) == 6);
            CHECK(r16(m, work + 28) == 7);
        } else if (f == "sub_1548A0") {
            CHECK(r32(m, work + 4) == 0);  // The Journey: no forced entry
        } else if (f == "sub_14EE80") {
            CHECK(r32(m, work) == 2);
            CHECK(r32(m, work + 8) == static_cast<u32>(calls_of(0x100D80u)[0].v0));
        } else if (f == "sub_166A50") {
            CHECK(r32(m, work + 8) == 3);
            CHECK(r32(m, work + 20) == 9);
            CHECK(r32(m, work + 4) == 1);
        } else if (f == "sub_119F10") {
            CHECK(r32(m, gpv(ui5::g::kCampSetupTask)) == task);
            CHECK(r32(m, work + ui5::sf::kPak) == static_cast<u32>(calls_of(0x100D80u)[0].v0));
            CHECK(r32(m, work + ui5::sf::kMessage) == 0);
        } else if (f == "sub_133D30") {
            CHECK(r32(m, work) == 0x1234);
            CHECK(r32(m, work + 4) == 0);
        }
    }
    // only one sprite set-up task at a time: a second request returns 0 and allocates nothing
    const hgp::Run again = ui_pair(m, "sub_119F10", {0, 0, 0, 0}, seed++, "setup exists", o);
    CHECK(v0_of(again) == 0);
    CHECK(calls_of(kRwCalloc).empty());
    MESSAGE("task creators: " << wants.size() << " screens");
}

#else

TEST_CASE("game(ui5): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
