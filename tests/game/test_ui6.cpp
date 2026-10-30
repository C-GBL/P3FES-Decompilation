// Pair tests for slice ui6 (game/src/ui/ui6_*.cpp: the camp menu's screens, second pass). Every body against its
// recompiled body, compared on the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log:
//   1. random worlds for all 104 bodies (the skeleton p3fes_handgen wrote: mostly the bad-input and early-stop paths);
//   2. the screens driven frame by frame on the replay snapshots' game state (climb_ref_17000, b_5800,
//      dorm_replay_4900) with pad input: the item screen (its lists against the stock / flags / party, the list cursor's
//      paging and wrap, the page change, the close), the equipment screen (the slot menu without wrap, the candidate
//      list, equipping and the HP / SP rescale to the new maxima), the system menu (the entry wrap, the config page's
//      values from flags 387.., the calendar on today's date);
//   3. documented rules on the host: the Status screen's HP / max HP / level digits equal the party records, the skill
//      list holds every distinct skill of the persona stock once (192..255 first, the rest by id).
// The stand-in world (stand_ins.h) serves the heap, printf / sprintf and the H_Cdvd layer, logs the sprite draws and
// finishes every tween at once; a recorder answers every other callee this build does not emit.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/ui6.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_11BBB0_0011bbb0(EEContext&);  // generated body
void fn_sub_11BBB0_0011bbb0__recomp(EEContext&);  // recompiled
void fn_sub_11C880_0011c880(EEContext&);  // generated body
void fn_sub_11C880_0011c880__recomp(EEContext&);  // recompiled
void fn_sub_11CFB0_0011cfb0(EEContext&);  // generated body
void fn_sub_11CFB0_0011cfb0__recomp(EEContext&);  // recompiled
void fn_sub_11D6D0_0011d6d0(EEContext&);  // generated body
void fn_sub_11D6D0_0011d6d0__recomp(EEContext&);  // recompiled
void fn_sub_11DDB0_0011ddb0(EEContext&);  // generated body
void fn_sub_11DDB0_0011ddb0__recomp(EEContext&);  // recompiled
void fn_sub_11DFE0_0011dfe0(EEContext&);  // generated body
void fn_sub_11DFE0_0011dfe0__recomp(EEContext&);  // recompiled
void fn_sub_1236A0_001236a0(EEContext&);  // generated body
void fn_sub_1236A0_001236a0__recomp(EEContext&);  // recompiled
void fn_sub_124370_00124370(EEContext&);  // generated body
void fn_sub_124370_00124370__recomp(EEContext&);  // recompiled
void fn_sub_124B30_00124b30(EEContext&);  // generated body
void fn_sub_124B30_00124b30__recomp(EEContext&);  // recompiled
void fn_sub_125D70_00125d70(EEContext&);  // generated body
void fn_sub_125D70_00125d70__recomp(EEContext&);  // recompiled
void fn_sub_1269A0_001269a0(EEContext&);  // generated body
void fn_sub_1269A0_001269a0__recomp(EEContext&);  // recompiled
void fn_sub_1273B0_001273b0(EEContext&);  // generated body
void fn_sub_1273B0_001273b0__recomp(EEContext&);  // recompiled
void fn_sub_127C00_00127c00(EEContext&);  // generated body
void fn_sub_127C00_00127c00__recomp(EEContext&);  // recompiled
void fn_sub_128720_00128720(EEContext&);  // generated body
void fn_sub_128720_00128720__recomp(EEContext&);  // recompiled
void fn_sub_128C40_00128c40(EEContext&);  // generated body
void fn_sub_128C40_00128c40__recomp(EEContext&);  // recompiled
void fn_sub_1293B0_001293b0(EEContext&);  // generated body
void fn_sub_1293B0_001293b0__recomp(EEContext&);  // recompiled
void fn_sub_129B30_00129b30(EEContext&);  // generated body
void fn_sub_129B30_00129b30__recomp(EEContext&);  // recompiled
void fn_sub_12A560_0012a560(EEContext&);  // generated body
void fn_sub_12A560_0012a560__recomp(EEContext&);  // recompiled
void fn_sub_12AC60_0012ac60(EEContext&);  // generated body
void fn_sub_12AC60_0012ac60__recomp(EEContext&);  // recompiled
void fn_sub_12B300_0012b300(EEContext&);  // generated body
void fn_sub_12B300_0012b300__recomp(EEContext&);  // recompiled
void fn_sub_12B860_0012b860(EEContext&);  // generated body
void fn_sub_12B860_0012b860__recomp(EEContext&);  // recompiled
void fn_sub_12BFB0_0012bfb0(EEContext&);  // generated body
void fn_sub_12BFB0_0012bfb0__recomp(EEContext&);  // recompiled
void fn_sub_133180_00133180(EEContext&);  // generated body
void fn_sub_133180_00133180__recomp(EEContext&);  // recompiled
void fn_sub_133460_00133460(EEContext&);  // generated body
void fn_sub_133460_00133460__recomp(EEContext&);  // recompiled
void fn_sub_1345B0_001345b0(EEContext&);  // generated body
void fn_sub_1345B0_001345b0__recomp(EEContext&);  // recompiled
void fn_sub_134900_00134900(EEContext&);  // generated body
void fn_sub_134900_00134900__recomp(EEContext&);  // recompiled
void fn_sub_167930_00167930(EEContext&);  // generated body
void fn_sub_167930_00167930__recomp(EEContext&);  // recompiled
void fn_sub_12C430_0012c430(EEContext&);  // generated body
void fn_sub_12C430_0012c430__recomp(EEContext&);  // recompiled
void fn_sub_12DC20_0012dc20(EEContext&);  // generated body
void fn_sub_12DC20_0012dc20__recomp(EEContext&);  // recompiled
void fn_sub_12DCF0_0012dcf0(EEContext&);  // generated body
void fn_sub_12DCF0_0012dcf0__recomp(EEContext&);  // recompiled
void fn_sub_12E3B0_0012e3b0(EEContext&);  // generated body
void fn_sub_12E3B0_0012e3b0__recomp(EEContext&);  // recompiled
void fn_sub_12F6D0_0012f6d0(EEContext&);  // generated body
void fn_sub_12F6D0_0012f6d0__recomp(EEContext&);  // recompiled
void fn_sub_1311D0_001311d0(EEContext&);  // generated body
void fn_sub_1311D0_001311d0__recomp(EEContext&);  // recompiled
void fn_sub_133E10_00133e10(EEContext&);  // generated body
void fn_sub_133E10_00133e10__recomp(EEContext&);  // recompiled
void fn_sub_1344B0_001344b0(EEContext&);  // generated body
void fn_sub_1344B0_001344b0__recomp(EEContext&);  // recompiled
void fn_sub_1355C0_001355c0(EEContext&);  // generated body
void fn_sub_1355C0_001355c0__recomp(EEContext&);  // recompiled
void fn_sub_136A10_00136a10(EEContext&);  // generated body
void fn_sub_136A10_00136a10__recomp(EEContext&);  // recompiled
void fn_sub_137580_00137580(EEContext&);  // generated body
void fn_sub_137580_00137580__recomp(EEContext&);  // recompiled
void fn_sub_1380E0_001380e0(EEContext&);  // generated body
void fn_sub_1380E0_001380e0__recomp(EEContext&);  // recompiled
void fn_sub_1387B0_001387b0(EEContext&);  // generated body
void fn_sub_1387B0_001387b0__recomp(EEContext&);  // recompiled
void fn_sub_139660_00139660(EEContext&);  // generated body
void fn_sub_139660_00139660__recomp(EEContext&);  // recompiled
void fn_sub_139FC0_00139fc0(EEContext&);  // generated body
void fn_sub_139FC0_00139fc0__recomp(EEContext&);  // recompiled
void fn_sub_13AFD0_0013afd0(EEContext&);  // generated body
void fn_sub_13AFD0_0013afd0__recomp(EEContext&);  // recompiled
void fn_sub_13C780_0013c780(EEContext&);  // generated body
void fn_sub_13C780_0013c780__recomp(EEContext&);  // recompiled
void fn_sub_13D1A0_0013d1a0(EEContext&);  // generated body
void fn_sub_13D1A0_0013d1a0__recomp(EEContext&);  // recompiled
void fn_sub_13E710_0013e710(EEContext&);  // generated body
void fn_sub_13E710_0013e710__recomp(EEContext&);  // recompiled
void fn_sub_13FCA0_0013fca0(EEContext&);  // generated body
void fn_sub_13FCA0_0013fca0__recomp(EEContext&);  // recompiled
void fn_sub_1406D0_001406d0(EEContext&);  // generated body
void fn_sub_1406D0_001406d0__recomp(EEContext&);  // recompiled
void fn_sub_140E30_00140e30(EEContext&);  // generated body
void fn_sub_140E30_00140e30__recomp(EEContext&);  // recompiled
void fn_sub_141660_00141660(EEContext&);  // generated body
void fn_sub_141660_00141660__recomp(EEContext&);  // recompiled
void fn_sub_141FB0_00141fb0(EEContext&);  // generated body
void fn_sub_141FB0_00141fb0__recomp(EEContext&);  // recompiled
void fn_sub_142930_00142930(EEContext&);  // generated body
void fn_sub_142930_00142930__recomp(EEContext&);  // recompiled
void fn_sub_1432F0_001432f0(EEContext&);  // generated body
void fn_sub_1432F0_001432f0__recomp(EEContext&);  // recompiled
void fn_sub_143A00_00143a00(EEContext&);  // generated body
void fn_sub_143A00_00143a00__recomp(EEContext&);  // recompiled
void fn_sub_143EE0_00143ee0(EEContext&);  // generated body
void fn_sub_143EE0_00143ee0__recomp(EEContext&);  // recompiled
void fn_sub_144910_00144910(EEContext&);  // generated body
void fn_sub_144910_00144910__recomp(EEContext&);  // recompiled
void fn_sub_145520_00145520(EEContext&);  // generated body
void fn_sub_145520_00145520__recomp(EEContext&);  // recompiled
void fn_sub_146710_00146710(EEContext&);  // generated body
void fn_sub_146710_00146710__recomp(EEContext&);  // recompiled
void fn_sub_1474F0_001474f0(EEContext&);  // generated body
void fn_sub_1474F0_001474f0__recomp(EEContext&);  // recompiled
void fn_sub_1482F0_001482f0(EEContext&);  // generated body
void fn_sub_1482F0_001482f0__recomp(EEContext&);  // recompiled
void fn_sub_148880_00148880(EEContext&);  // generated body
void fn_sub_148880_00148880__recomp(EEContext&);  // recompiled
void fn_sub_148C10_00148c10(EEContext&);  // generated body
void fn_sub_148C10_00148c10__recomp(EEContext&);  // recompiled
void fn_sub_1496F0_001496f0(EEContext&);  // generated body
void fn_sub_1496F0_001496f0__recomp(EEContext&);  // recompiled
void fn_sub_14A490_0014a490(EEContext&);  // generated body
void fn_sub_14A490_0014a490__recomp(EEContext&);  // recompiled
void fn_sub_14B210_0014b210(EEContext&);  // generated body
void fn_sub_14B210_0014b210__recomp(EEContext&);  // recompiled
void fn_sub_14BCE0_0014bce0(EEContext&);  // generated body
void fn_sub_14BCE0_0014bce0__recomp(EEContext&);  // recompiled
void fn_sub_14C290_0014c290(EEContext&);  // generated body
void fn_sub_14C290_0014c290__recomp(EEContext&);  // recompiled
void fn_sub_14C5C0_0014c5c0(EEContext&);  // generated body
void fn_sub_14C5C0_0014c5c0__recomp(EEContext&);  // recompiled
void fn_sub_14F7D0_0014f7d0(EEContext&);  // generated body
void fn_sub_14F7D0_0014f7d0__recomp(EEContext&);  // recompiled
void fn_sub_154970_00154970(EEContext&);  // generated body
void fn_sub_154970_00154970__recomp(EEContext&);  // recompiled
void fn_sub_154F70_00154f70(EEContext&);  // generated body
void fn_sub_154F70_00154f70__recomp(EEContext&);  // recompiled
void fn_sub_155070_00155070(EEContext&);  // generated body
void fn_sub_155070_00155070__recomp(EEContext&);  // recompiled
void fn_sub_155710_00155710(EEContext&);  // generated body
void fn_sub_155710_00155710__recomp(EEContext&);  // recompiled
void fn_sub_155830_00155830(EEContext&);  // generated body
void fn_sub_155830_00155830__recomp(EEContext&);  // recompiled
void fn_sub_156140_00156140(EEContext&);  // generated body
void fn_sub_156140_00156140__recomp(EEContext&);  // recompiled
void fn_sub_156240_00156240(EEContext&);  // generated body
void fn_sub_156240_00156240__recomp(EEContext&);  // recompiled
void fn_sub_156E80_00156e80(EEContext&);  // generated body
void fn_sub_156E80_00156e80__recomp(EEContext&);  // recompiled
void fn_sub_156F80_00156f80(EEContext&);  // generated body
void fn_sub_156F80_00156f80__recomp(EEContext&);  // recompiled
void fn_sub_159900_00159900(EEContext&);  // generated body
void fn_sub_159900_00159900__recomp(EEContext&);  // recompiled
void fn_sub_1599F0_001599f0(EEContext&);  // generated body
void fn_sub_1599F0_001599f0__recomp(EEContext&);  // recompiled
void fn_sub_15B330_0015b330(EEContext&);  // generated body
void fn_sub_15B330_0015b330__recomp(EEContext&);  // recompiled
void fn_sub_15B430_0015b430(EEContext&);  // generated body
void fn_sub_15B430_0015b430__recomp(EEContext&);  // recompiled
void fn_sub_15C840_0015c840(EEContext&);  // generated body
void fn_sub_15C840_0015c840__recomp(EEContext&);  // recompiled
void fn_sub_15CE50_0015ce50(EEContext&);  // generated body
void fn_sub_15CE50_0015ce50__recomp(EEContext&);  // recompiled
void fn_sub_15DA70_0015da70(EEContext&);  // generated body
void fn_sub_15DA70_0015da70__recomp(EEContext&);  // recompiled
void fn_sub_15E150_0015e150(EEContext&);  // generated body
void fn_sub_15E150_0015e150__recomp(EEContext&);  // recompiled
void fn_sub_15E6E0_0015e6e0(EEContext&);  // generated body
void fn_sub_15E6E0_0015e6e0__recomp(EEContext&);  // recompiled
void fn_sub_15EE40_0015ee40(EEContext&);  // generated body
void fn_sub_15EE40_0015ee40__recomp(EEContext&);  // recompiled
void fn_sub_15F320_0015f320(EEContext&);  // generated body
void fn_sub_15F320_0015f320__recomp(EEContext&);  // recompiled
void fn_sub_15FA90_0015fa90(EEContext&);  // generated body
void fn_sub_15FA90_0015fa90__recomp(EEContext&);  // recompiled
void fn_sub_160800_00160800(EEContext&);  // generated body
void fn_sub_160800_00160800__recomp(EEContext&);  // recompiled
void fn_sub_1618A0_001618a0(EEContext&);  // generated body
void fn_sub_1618A0_001618a0__recomp(EEContext&);  // recompiled
void fn_sub_161D90_00161d90(EEContext&);  // generated body
void fn_sub_161D90_00161d90__recomp(EEContext&);  // recompiled
void fn_sub_163330_00163330(EEContext&);  // generated body
void fn_sub_163330_00163330__recomp(EEContext&);  // recompiled
void fn_sub_164920_00164920(EEContext&);  // generated body
void fn_sub_164920_00164920__recomp(EEContext&);  // recompiled
void fn_sub_166C70_00166c70(EEContext&);  // generated body
void fn_sub_166C70_00166c70__recomp(EEContext&);  // recompiled
void fn_sub_168810_00168810(EEContext&);  // generated body
void fn_sub_168810_00168810__recomp(EEContext&);  // recompiled
void fn_sub_169110_00169110(EEContext&);  // generated body
void fn_sub_169110_00169110__recomp(EEContext&);  // recompiled
void fn_sub_1691F0_001691f0(EEContext&);  // generated body
void fn_sub_1691F0_001691f0__recomp(EEContext&);  // recompiled
void fn_sub_169470_00169470(EEContext&);  // generated body
void fn_sub_169470_00169470__recomp(EEContext&);  // recompiled
void fn_sub_169B90_00169b90(EEContext&);  // generated body
void fn_sub_169B90_00169b90__recomp(EEContext&);  // recompiled
void fn_sub_16A030_0016a030(EEContext&);  // generated body
void fn_sub_16A030_0016a030__recomp(EEContext&);  // recompiled
void fn_sub_16A700_0016a700(EEContext&);  // generated body
void fn_sub_16A700_0016a700__recomp(EEContext&);  // recompiled
void fn_sub_16AF90_0016af90(EEContext&);  // generated body
void fn_sub_16AF90_0016af90__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_11BBB0", 0x11BBB0, &recomp_gen::fn_sub_11BBB0_0011bbb0, &recomp_gen::fn_sub_11BBB0_0011bbb0__recomp},
    {"sub_11C880", 0x11C880, &recomp_gen::fn_sub_11C880_0011c880, &recomp_gen::fn_sub_11C880_0011c880__recomp},
    {"sub_11CFB0", 0x11CFB0, &recomp_gen::fn_sub_11CFB0_0011cfb0, &recomp_gen::fn_sub_11CFB0_0011cfb0__recomp},
    {"sub_11D6D0", 0x11D6D0, &recomp_gen::fn_sub_11D6D0_0011d6d0, &recomp_gen::fn_sub_11D6D0_0011d6d0__recomp},
    {"sub_11DDB0", 0x11DDB0, &recomp_gen::fn_sub_11DDB0_0011ddb0, &recomp_gen::fn_sub_11DDB0_0011ddb0__recomp},
    {"sub_11DFE0", 0x11DFE0, &recomp_gen::fn_sub_11DFE0_0011dfe0, &recomp_gen::fn_sub_11DFE0_0011dfe0__recomp},
    {"sub_1236A0", 0x1236A0, &recomp_gen::fn_sub_1236A0_001236a0, &recomp_gen::fn_sub_1236A0_001236a0__recomp},
    {"sub_124370", 0x124370, &recomp_gen::fn_sub_124370_00124370, &recomp_gen::fn_sub_124370_00124370__recomp},
    {"sub_124B30", 0x124B30, &recomp_gen::fn_sub_124B30_00124b30, &recomp_gen::fn_sub_124B30_00124b30__recomp},
    {"sub_125D70", 0x125D70, &recomp_gen::fn_sub_125D70_00125d70, &recomp_gen::fn_sub_125D70_00125d70__recomp},
    {"sub_1269A0", 0x1269A0, &recomp_gen::fn_sub_1269A0_001269a0, &recomp_gen::fn_sub_1269A0_001269a0__recomp},
    {"sub_1273B0", 0x1273B0, &recomp_gen::fn_sub_1273B0_001273b0, &recomp_gen::fn_sub_1273B0_001273b0__recomp},
    {"sub_127C00", 0x127C00, &recomp_gen::fn_sub_127C00_00127c00, &recomp_gen::fn_sub_127C00_00127c00__recomp},
    {"sub_128720", 0x128720, &recomp_gen::fn_sub_128720_00128720, &recomp_gen::fn_sub_128720_00128720__recomp},
    {"sub_128C40", 0x128C40, &recomp_gen::fn_sub_128C40_00128c40, &recomp_gen::fn_sub_128C40_00128c40__recomp},
    {"sub_1293B0", 0x1293B0, &recomp_gen::fn_sub_1293B0_001293b0, &recomp_gen::fn_sub_1293B0_001293b0__recomp},
    {"sub_129B30", 0x129B30, &recomp_gen::fn_sub_129B30_00129b30, &recomp_gen::fn_sub_129B30_00129b30__recomp},
    {"sub_12A560", 0x12A560, &recomp_gen::fn_sub_12A560_0012a560, &recomp_gen::fn_sub_12A560_0012a560__recomp},
    {"sub_12AC60", 0x12AC60, &recomp_gen::fn_sub_12AC60_0012ac60, &recomp_gen::fn_sub_12AC60_0012ac60__recomp},
    {"sub_12B300", 0x12B300, &recomp_gen::fn_sub_12B300_0012b300, &recomp_gen::fn_sub_12B300_0012b300__recomp},
    {"sub_12B860", 0x12B860, &recomp_gen::fn_sub_12B860_0012b860, &recomp_gen::fn_sub_12B860_0012b860__recomp},
    {"sub_12BFB0", 0x12BFB0, &recomp_gen::fn_sub_12BFB0_0012bfb0, &recomp_gen::fn_sub_12BFB0_0012bfb0__recomp},
    {"sub_133180", 0x133180, &recomp_gen::fn_sub_133180_00133180, &recomp_gen::fn_sub_133180_00133180__recomp},
    {"sub_133460", 0x133460, &recomp_gen::fn_sub_133460_00133460, &recomp_gen::fn_sub_133460_00133460__recomp},
    {"sub_1345B0", 0x1345B0, &recomp_gen::fn_sub_1345B0_001345b0, &recomp_gen::fn_sub_1345B0_001345b0__recomp},
    {"sub_134900", 0x134900, &recomp_gen::fn_sub_134900_00134900, &recomp_gen::fn_sub_134900_00134900__recomp},
    {"sub_167930", 0x167930, &recomp_gen::fn_sub_167930_00167930, &recomp_gen::fn_sub_167930_00167930__recomp},
    {"sub_12C430", 0x12C430, &recomp_gen::fn_sub_12C430_0012c430, &recomp_gen::fn_sub_12C430_0012c430__recomp},
    {"sub_12DC20", 0x12DC20, &recomp_gen::fn_sub_12DC20_0012dc20, &recomp_gen::fn_sub_12DC20_0012dc20__recomp},
    {"sub_12DCF0", 0x12DCF0, &recomp_gen::fn_sub_12DCF0_0012dcf0, &recomp_gen::fn_sub_12DCF0_0012dcf0__recomp},
    {"sub_12E3B0", 0x12E3B0, &recomp_gen::fn_sub_12E3B0_0012e3b0, &recomp_gen::fn_sub_12E3B0_0012e3b0__recomp},
    {"sub_12F6D0", 0x12F6D0, &recomp_gen::fn_sub_12F6D0_0012f6d0, &recomp_gen::fn_sub_12F6D0_0012f6d0__recomp},
    {"sub_1311D0", 0x1311D0, &recomp_gen::fn_sub_1311D0_001311d0, &recomp_gen::fn_sub_1311D0_001311d0__recomp},
    {"sub_133E10", 0x133E10, &recomp_gen::fn_sub_133E10_00133e10, &recomp_gen::fn_sub_133E10_00133e10__recomp},
    {"sub_1344B0", 0x1344B0, &recomp_gen::fn_sub_1344B0_001344b0, &recomp_gen::fn_sub_1344B0_001344b0__recomp},
    {"sub_1355C0", 0x1355C0, &recomp_gen::fn_sub_1355C0_001355c0, &recomp_gen::fn_sub_1355C0_001355c0__recomp},
    {"sub_136A10", 0x136A10, &recomp_gen::fn_sub_136A10_00136a10, &recomp_gen::fn_sub_136A10_00136a10__recomp},
    {"sub_137580", 0x137580, &recomp_gen::fn_sub_137580_00137580, &recomp_gen::fn_sub_137580_00137580__recomp},
    {"sub_1380E0", 0x1380E0, &recomp_gen::fn_sub_1380E0_001380e0, &recomp_gen::fn_sub_1380E0_001380e0__recomp},
    {"sub_1387B0", 0x1387B0, &recomp_gen::fn_sub_1387B0_001387b0, &recomp_gen::fn_sub_1387B0_001387b0__recomp},
    {"sub_139660", 0x139660, &recomp_gen::fn_sub_139660_00139660, &recomp_gen::fn_sub_139660_00139660__recomp},
    {"sub_139FC0", 0x139FC0, &recomp_gen::fn_sub_139FC0_00139fc0, &recomp_gen::fn_sub_139FC0_00139fc0__recomp},
    {"sub_13AFD0", 0x13AFD0, &recomp_gen::fn_sub_13AFD0_0013afd0, &recomp_gen::fn_sub_13AFD0_0013afd0__recomp},
    {"sub_13C780", 0x13C780, &recomp_gen::fn_sub_13C780_0013c780, &recomp_gen::fn_sub_13C780_0013c780__recomp},
    {"sub_13D1A0", 0x13D1A0, &recomp_gen::fn_sub_13D1A0_0013d1a0, &recomp_gen::fn_sub_13D1A0_0013d1a0__recomp},
    {"sub_13E710", 0x13E710, &recomp_gen::fn_sub_13E710_0013e710, &recomp_gen::fn_sub_13E710_0013e710__recomp},
    {"sub_13FCA0", 0x13FCA0, &recomp_gen::fn_sub_13FCA0_0013fca0, &recomp_gen::fn_sub_13FCA0_0013fca0__recomp},
    {"sub_1406D0", 0x1406D0, &recomp_gen::fn_sub_1406D0_001406d0, &recomp_gen::fn_sub_1406D0_001406d0__recomp},
    {"sub_140E30", 0x140E30, &recomp_gen::fn_sub_140E30_00140e30, &recomp_gen::fn_sub_140E30_00140e30__recomp},
    {"sub_141660", 0x141660, &recomp_gen::fn_sub_141660_00141660, &recomp_gen::fn_sub_141660_00141660__recomp},
    {"sub_141FB0", 0x141FB0, &recomp_gen::fn_sub_141FB0_00141fb0, &recomp_gen::fn_sub_141FB0_00141fb0__recomp},
    {"sub_142930", 0x142930, &recomp_gen::fn_sub_142930_00142930, &recomp_gen::fn_sub_142930_00142930__recomp},
    {"sub_1432F0", 0x1432F0, &recomp_gen::fn_sub_1432F0_001432f0, &recomp_gen::fn_sub_1432F0_001432f0__recomp},
    {"sub_143A00", 0x143A00, &recomp_gen::fn_sub_143A00_00143a00, &recomp_gen::fn_sub_143A00_00143a00__recomp},
    {"sub_143EE0", 0x143EE0, &recomp_gen::fn_sub_143EE0_00143ee0, &recomp_gen::fn_sub_143EE0_00143ee0__recomp},
    {"sub_144910", 0x144910, &recomp_gen::fn_sub_144910_00144910, &recomp_gen::fn_sub_144910_00144910__recomp},
    {"sub_145520", 0x145520, &recomp_gen::fn_sub_145520_00145520, &recomp_gen::fn_sub_145520_00145520__recomp},
    {"sub_146710", 0x146710, &recomp_gen::fn_sub_146710_00146710, &recomp_gen::fn_sub_146710_00146710__recomp},
    {"sub_1474F0", 0x1474F0, &recomp_gen::fn_sub_1474F0_001474f0, &recomp_gen::fn_sub_1474F0_001474f0__recomp},
    {"sub_1482F0", 0x1482F0, &recomp_gen::fn_sub_1482F0_001482f0, &recomp_gen::fn_sub_1482F0_001482f0__recomp},
    {"sub_148880", 0x148880, &recomp_gen::fn_sub_148880_00148880, &recomp_gen::fn_sub_148880_00148880__recomp},
    {"sub_148C10", 0x148C10, &recomp_gen::fn_sub_148C10_00148c10, &recomp_gen::fn_sub_148C10_00148c10__recomp},
    {"sub_1496F0", 0x1496F0, &recomp_gen::fn_sub_1496F0_001496f0, &recomp_gen::fn_sub_1496F0_001496f0__recomp},
    {"sub_14A490", 0x14A490, &recomp_gen::fn_sub_14A490_0014a490, &recomp_gen::fn_sub_14A490_0014a490__recomp},
    {"sub_14B210", 0x14B210, &recomp_gen::fn_sub_14B210_0014b210, &recomp_gen::fn_sub_14B210_0014b210__recomp},
    {"sub_14BCE0", 0x14BCE0, &recomp_gen::fn_sub_14BCE0_0014bce0, &recomp_gen::fn_sub_14BCE0_0014bce0__recomp},
    {"sub_14C290", 0x14C290, &recomp_gen::fn_sub_14C290_0014c290, &recomp_gen::fn_sub_14C290_0014c290__recomp},
    {"sub_14C5C0", 0x14C5C0, &recomp_gen::fn_sub_14C5C0_0014c5c0, &recomp_gen::fn_sub_14C5C0_0014c5c0__recomp},
    {"sub_14F7D0", 0x14F7D0, &recomp_gen::fn_sub_14F7D0_0014f7d0, &recomp_gen::fn_sub_14F7D0_0014f7d0__recomp},
    {"sub_154970", 0x154970, &recomp_gen::fn_sub_154970_00154970, &recomp_gen::fn_sub_154970_00154970__recomp},
    {"sub_154F70", 0x154F70, &recomp_gen::fn_sub_154F70_00154f70, &recomp_gen::fn_sub_154F70_00154f70__recomp},
    {"sub_155070", 0x155070, &recomp_gen::fn_sub_155070_00155070, &recomp_gen::fn_sub_155070_00155070__recomp},
    {"sub_155710", 0x155710, &recomp_gen::fn_sub_155710_00155710, &recomp_gen::fn_sub_155710_00155710__recomp},
    {"sub_155830", 0x155830, &recomp_gen::fn_sub_155830_00155830, &recomp_gen::fn_sub_155830_00155830__recomp},
    {"sub_156140", 0x156140, &recomp_gen::fn_sub_156140_00156140, &recomp_gen::fn_sub_156140_00156140__recomp},
    {"sub_156240", 0x156240, &recomp_gen::fn_sub_156240_00156240, &recomp_gen::fn_sub_156240_00156240__recomp},
    {"sub_156E80", 0x156E80, &recomp_gen::fn_sub_156E80_00156e80, &recomp_gen::fn_sub_156E80_00156e80__recomp},
    {"sub_156F80", 0x156F80, &recomp_gen::fn_sub_156F80_00156f80, &recomp_gen::fn_sub_156F80_00156f80__recomp},
    {"sub_159900", 0x159900, &recomp_gen::fn_sub_159900_00159900, &recomp_gen::fn_sub_159900_00159900__recomp},
    {"sub_1599F0", 0x1599F0, &recomp_gen::fn_sub_1599F0_001599f0, &recomp_gen::fn_sub_1599F0_001599f0__recomp},
    {"sub_15B330", 0x15B330, &recomp_gen::fn_sub_15B330_0015b330, &recomp_gen::fn_sub_15B330_0015b330__recomp},
    {"sub_15B430", 0x15B430, &recomp_gen::fn_sub_15B430_0015b430, &recomp_gen::fn_sub_15B430_0015b430__recomp},
    {"sub_15C840", 0x15C840, &recomp_gen::fn_sub_15C840_0015c840, &recomp_gen::fn_sub_15C840_0015c840__recomp},
    {"sub_15CE50", 0x15CE50, &recomp_gen::fn_sub_15CE50_0015ce50, &recomp_gen::fn_sub_15CE50_0015ce50__recomp},
    {"sub_15DA70", 0x15DA70, &recomp_gen::fn_sub_15DA70_0015da70, &recomp_gen::fn_sub_15DA70_0015da70__recomp},
    {"sub_15E150", 0x15E150, &recomp_gen::fn_sub_15E150_0015e150, &recomp_gen::fn_sub_15E150_0015e150__recomp},
    {"sub_15E6E0", 0x15E6E0, &recomp_gen::fn_sub_15E6E0_0015e6e0, &recomp_gen::fn_sub_15E6E0_0015e6e0__recomp},
    {"sub_15EE40", 0x15EE40, &recomp_gen::fn_sub_15EE40_0015ee40, &recomp_gen::fn_sub_15EE40_0015ee40__recomp},
    {"sub_15F320", 0x15F320, &recomp_gen::fn_sub_15F320_0015f320, &recomp_gen::fn_sub_15F320_0015f320__recomp},
    {"sub_15FA90", 0x15FA90, &recomp_gen::fn_sub_15FA90_0015fa90, &recomp_gen::fn_sub_15FA90_0015fa90__recomp},
    {"sub_160800", 0x160800, &recomp_gen::fn_sub_160800_00160800, &recomp_gen::fn_sub_160800_00160800__recomp},
    {"sub_1618A0", 0x1618A0, &recomp_gen::fn_sub_1618A0_001618a0, &recomp_gen::fn_sub_1618A0_001618a0__recomp},
    {"sub_161D90", 0x161D90, &recomp_gen::fn_sub_161D90_00161d90, &recomp_gen::fn_sub_161D90_00161d90__recomp},
    {"sub_163330", 0x163330, &recomp_gen::fn_sub_163330_00163330, &recomp_gen::fn_sub_163330_00163330__recomp},
    {"sub_164920", 0x164920, &recomp_gen::fn_sub_164920_00164920, &recomp_gen::fn_sub_164920_00164920__recomp},
    {"sub_166C70", 0x166C70, &recomp_gen::fn_sub_166C70_00166c70, &recomp_gen::fn_sub_166C70_00166c70__recomp},
    {"sub_168810", 0x168810, &recomp_gen::fn_sub_168810_00168810, &recomp_gen::fn_sub_168810_00168810__recomp},
    {"sub_169110", 0x169110, &recomp_gen::fn_sub_169110_00169110, &recomp_gen::fn_sub_169110_00169110__recomp},
    {"sub_1691F0", 0x1691F0, &recomp_gen::fn_sub_1691F0_001691f0, &recomp_gen::fn_sub_1691F0_001691f0__recomp},
    {"sub_169470", 0x169470, &recomp_gen::fn_sub_169470_00169470, &recomp_gen::fn_sub_169470_00169470__recomp},
    {"sub_169B90", 0x169B90, &recomp_gen::fn_sub_169B90_00169b90, &recomp_gen::fn_sub_169B90_00169b90__recomp},
    {"sub_16A030", 0x16A030, &recomp_gen::fn_sub_16A030_0016a030, &recomp_gen::fn_sub_16A030_0016a030__recomp},
    {"sub_16A700", 0x16A700, &recomp_gen::fn_sub_16A700_0016a700, &recomp_gen::fn_sub_16A700_0016a700__recomp},
    {"sub_16AF90", 0x16AF90, &recomp_gen::fn_sub_16AF90_0016af90, &recomp_gen::fn_sub_16AF90_0016af90__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena (the real structures: below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(ui6): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// =====================================================================================================================
// Real game state: the screens driven frame by frame on the replay snapshots, and documented rules
// =====================================================================================================================
// Every pair below is run_pair_si (stand_ins.h): both bodies on identical machines and identical stand-in worlds,
// compared on the whole register file at every check point, the dead stack, all 32 MiB of RAM, the scratchpad, the bus
// log and the stand-ins' call logs. A screen is driven as the game drives it: one update call per frame on its work
// block, the pad words written before each frame, the flash-control task answering every transition at once (its
// state word reset to 0 between frames), and the tween records finishing in one step (a stand-in for sub_18B700 that
// sets the frame to the last frame and returns 0, so the element draws are skipped and every page counts as arrived:
// the input states run on every frame). The draws are logged by stand-ins (sprite, file, x, y) and checked against
// the party records where they show numbers.
namespace {

namespace u6 = p3fes::game::ui6;

constexpr u32 kGpReg = 0x7D2CF0u;
constexpr u32 gpv(s32 off) { return kGpReg + static_cast<u32>(off); }
// Free in every snapshot used here (stand_ins.h: zero from 0x1BC0000 up to the stand-in heap at 0x1C00000).
constexpr u32 kScratch = 0x01BC0000u;
constexpr u32 kTask = kScratch + 0x000;       // the screen's task (0x68 bytes): +0x3C -> kWork
constexpr u32 kWork = kScratch + 0x100;       // its work block (up to 0x400 bytes)
constexpr u32 kFlashTask = kScratch + 0x600;  // a stand-in flash-control task: +0x3C -> kFlashWork
constexpr u32 kFlashWork = kScratch + 0x680;
constexpr u32 kKaniTask = kScratch + 0x700;   // the two side-portrait tasks: +0x3C -> kKaniWork
constexpr u32 kKaniWork = kScratch + 0x780;
constexpr u32 kHandle = kScratch + 0x800;     // what the sprCreateHandle stand-in returns (0x100 bytes)
constexpr u32 kTweens = kScratch + 0x1000;    // 0x3000: 180 tween records
constexpr u32 kList0 = kScratch + 0x4000;     // 0x1000
constexpr u32 kList1 = kScratch + 0x5000;     // 0x3000 (11,632 bytes)
constexpr u32 kList2 = kScratch + 0x8000;     // 0x1000
constexpr u32 kTweens2 = kScratch + 0x9000;   // 0x1000
constexpr u32 kTweens3 = kScratch + 0xA000;   // 0x1000
constexpr u32 kPadTrig = 0x7E094Eu, kPadRepeat = 0x7E0952u, kPadTrig2 = 0x7E0958u, kPadRepeat2 = 0x7E095Au;

u32 rd32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
s32 rds32(Machine& m, u32 va) { return static_cast<s32>(rd32(m, va)); }
u16 rd16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
void wr32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wr16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
u32 fbits(float f) { u32 b; std::memcpy(&b, &f, 4); return b; }

std::unique_ptr<Machine> real_machine(const char* snapshot) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    const std::vector<u8> base = read_snapshot(snapshot);
    if (base.size() != EEMemory::kMainRamSize) return nullptr;
    std::memcpy(m->mem.main_ram(), base.data(), base.size());
    write_rw_slots(*m);
    return m;
}

// --- the stand-in world of these tests --------------------------------------------------------------------------------
// install_standard (heap, printf / sprintf, the H_Cdvd layer) plus: a logging stand-in for the sprite draws that this
// build does not emit (the call's arguments and $f12 / $f13 in `extra`), the tween step that finishes a record at once,
// sprCreateHandle returning a scratch handle, and a recorder for every other callee of the ui6 bodies the build does
// not emit (they log the call and return 0).
void log_draw(EEContext& ctx, StandIns&, StandInCall& call) {
    call.extra = (static_cast<u64>(ctx.fpr[13]) << 32) | ctx.fpr[12];
    call.v0 = 0;
}
void tween_finish(EEContext& ctx, StandIns&, StandInCall& call) {
    const u32 rec = static_cast<u32>(call.args[0]);
    if (rec >= 0x00100000u && rec + 68 <= 0x02000000u) {
        u32 last;
        std::memcpy(&last, ctx.memory->main_ram() + rec + u6::tw::kLast, 4);
        std::memcpy(ctx.memory->main_ram() + rec + u6::tw::kFrame, &last, 4);
    }
    call.v0 = 0;
}
constexpr u32 kDrawSprite = 0x1159F0u, kDrawSpriteRgb2 = 0x115AD0u, kDrawSpriteTint = 0x115BC0u;
void screen_world(StandInWorld& w) {
    install_standard(w);
    w.si.install(kDrawSprite, "sprDrawSpriteBasic", log_draw);
    w.si.install(kDrawSpriteRgb2, "sub_115AD0 (sprite, two colour bytes)", log_draw);
    w.si.install(kDrawSpriteTint, "sub_115BC0 (sprite, tinted)", log_draw);
    w.si.install(0x18B700u, "sub_18B700 (tween step: finished at once)", tween_finish);
    w.si.install_recorder(0x1158B0u, "sprCreateHandle", kHandle);
    // the item flag word (not emitted): every flag set, so every held entry of a slot's kind is a candidate
    w.si.install_recorder(0x1712D0u, "sub_1712D0 (item flags)", 0xFFFF);
    const std::pair<u32, const char*> rec[] = {
        {0x115980u, "sub_115980 (draw the handle)"}, {0x3B32D0u, "sub_3B32D0 (text)"}, {0x3B2CB0u, "sub_3B2CB0 (text)"},
        {0x3B2F90u, "sub_3B2F90 (text)"}, {0x3C7E20u, "sub_3C7E20 (message text)"}, {0x3C7E50u, "sub_3C7E50 (message text)"},
        {0x112420u, "sprCreateHandleFromData"}, {0x10C1A0u, "sub_10C1A0 (texture build)"}, {0x10C3A0u, "sub_10C3A0 (build poll)"},
        {0x3C7D80u, "sub_3C7D80 (message file)"}, {0x115DE0u, "sub_115DE0"}, {0x103C30u, "sub_103C30"}, {0x103CB0u, "sub_103CB0"},
        {0x403380u, "sub_403380"}, {0x403800u, "sub_403800"}, {0x403830u, "sub_403830"}, {0x403740u, "sub_403740"},
        {0x403880u, "sub_403880"}, {0x403900u, "sub_403900"}, {0x25F370u, "brItem_CreateStockOverBgTask"},
        {0x25F570u, "sub_25F570"}, {0x16D2F0u, "sub_16D2F0"}, {0x10A4E0u, "sub_10A4E0 (sound)"},
        // the sound request sub_10A4E0 and H_Sndcom_PlayVoice run (they are emitted); the sound driver below them
        // is served by recorders
        {0x51E028u, "sceSkSsSESQ_Status (sound driver)"}, {0x51DF58u, "sceSkSsSESQ_Control (sound driver)"},
    };
    for (const auto& [va, name] : rec) w.si.install_recorder(va, name, 0);
}

int g_pairs = 0;
u64 g_checks = 0;

struct Run {
    u64 v0 = 0;
    std::vector<StandInCall> log;  // the recompiled run's stand-in calls
};

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, name) == 0) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// One pair of `name` on the machine (afterwards the recompiled run's memory is in place).
Run pair_si(Machine& m, const char* name, const Args& a, const char* what, std::map<unsigned, u64> gpr_in = {}) {
    const Case& c = by_name(name);
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.ranges.push_back({0, EEMemory::kMainRamSize});
    hw.gpr_in = std::move(gpr_in);
    const std::string w = std::string(what) + " " + name;
    SiPair p = run_pair_si(m, c.hand, c.recomp, a, static_cast<u32>(++g_pairs), w.c_str(), hw, screen_world);
    g_checks += static_cast<u64>(p.hw.recomp.base.checks);
    Run r;
    r.v0 = p.hw.recomp.base.v0;
    if (p.recomp) r.log = p.recomp->si.log;
    return r;
}

// A plain call of an emitted function (no pair): the game's own value of an accessor.
u64 call1(Machine& m, Fn fn, const Args& a) {
    const hgp::Run r = hgp::run_one(m, fn, a, 1, HwCheck{});
    return r.end.gpr[GPR_V0].u64[0];
}

// The fake tasks every screen talks to: the flash-control task (state 0 = idle: the request answers 1) and the two
// side-portrait tasks.
void install_fake_tasks(Machine& m) {
    zero(m, kFlashTask, 0x200);
    wr32(m, kFlashTask + 0x3C, kFlashWork);
    zero(m, kKaniTask, 0x100);
    wr32(m, kKaniTask + 0x3C, kKaniWork);
    wr32(m, gpv(u6::g::kCampFlashTask), kFlashTask);
    wr32(m, gpv(u6::g::kCampPcKani), kKaniTask);
    wr32(m, gpv(u6::g::kCampPersonaKani), kKaniTask);
    wr32(m, gpv(u6::g::kPersonaTexTask), 0);
}
void set_pad(Machine& m, u16 trig, u16 repeat) {
    wr16(m, kPadTrig, trig);
    wr16(m, kPadRepeat, repeat);
    wr16(m, kPadTrig2, 0);
    wr16(m, kPadRepeat2, 0);
}
// One frame of a screen update: the flash task idle again, the pad words, the update.
u64 frame(Machine& m, const char* update, u16 trig, u16 repeat, const char* what) {
    wr32(m, kFlashWork, 0);
    set_pad(m, trig, repeat);
    return pair_si(m, update, {sx(kTask), 0, 0, 0}, what).v0;
}

}  // namespace

namespace p3fes::recomp_gen {
void fn_sub_170760_00170760(EEContext&);  // datGetItemNum (owner, id)
void fn_datGetFlag_0016f190(EEContext&);
void fn_sub_16DD60_0016dd60(EEContext&);  // datGetPartyMember (i)
void fn_sub_174960_00174960(EEContext&);  // datPersonaIsSlotUsed (slot)
void fn_sub_174A90_00174a90(EEContext&);  // datPersonaGetHeroPersona (slot)
void fn_sub_16C4F0_0016c4f0(EEContext&);  // datGetPcHp
void fn_sub_16C5F0_0016c5f0(EEContext&);  // datGetPcMaxHp
void fn_sub_16C570_0016c570(EEContext&);  // datGetPcSp
void fn_sub_16C670_0016c670(EEContext&);  // datGetPcMaxSp
void fn_sub_16C470_0016c470(EEContext&);  // datGetPcLevel
void fn_datGetEquipmentIdx_0016cb80(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {
constexpr const char* kSnapshots[] = {"climb_ref_17000", "b_5800", "dorm_replay_4900"};

// The digits a draw sequence shows: the sprites 11..20 of the given calls, in order.
std::vector<int> digits_of(const std::vector<StandInCall>& log, std::size_t from, std::size_t to) {
    std::vector<int> d;
    for (std::size_t i = from; i < to && i < log.size(); ++i) {
        const s64 sprite = static_cast<s64>(log[i].args[2]);
        if ((log[i].va == kDrawSprite || log[i].va == kDrawSpriteRgb2) && sprite >= 11 && sprite <= 20) d.push_back(static_cast<int>(sprite - 11));
    }
    return d;
}
std::vector<int> decimal(unsigned v) {
    std::vector<int> d;
    if (v == 0) d.push_back(0);
    while (v) { d.insert(d.begin(), static_cast<int>(v % 10)); v /= 10; }
    return d;
}
std::vector<int> party(Machine& m) {  // the protagonist (1) and the members present
    std::vector<int> p{1};
    for (int i = 0; i < 3; ++i) {
        const int id = static_cast<s16>(call1(m, &recomp_gen::fn_sub_16DD60_0016dd60, {static_cast<u64>(i), 0, 0, 0}) & 0xFFFF);
        if (id == 0) break;
        p.push_back(id);
    }
    return p;
}

}  // namespace

TEST_CASE("game(ui6): the Status screen's numbers equal the party records") {
    int checked = 0;
    for (const char* snap : kSnapshots) {
        auto m = real_machine(snap);
        if (!m) { MESSAGE("SKIP: no snapshot " << snap); continue; }
        install_fake_tasks(*m);
        for (int pc : party(*m)) {
            const unsigned hp = call1(*m, &recomp_gen::fn_sub_16C4F0_0016c4f0, {static_cast<u64>(pc), 0, 0, 0}) & 0xFFFF;
            const unsigned maxhp = call1(*m, &recomp_gen::fn_sub_16C5F0_0016c5f0, {static_cast<u64>(pc), 0, 0, 0}) & 0xFFFF;
            const unsigned sp = call1(*m, &recomp_gen::fn_sub_16C570_0016c570, {static_cast<u64>(pc), 0, 0, 0}) & 0xFFFF;
            const unsigned maxsp = call1(*m, &recomp_gen::fn_sub_16C670_0016c670, {static_cast<u64>(pc), 0, 0, 0}) & 0xFFFF;
            const unsigned level = call1(*m, &recomp_gen::fn_sub_16C470_0016c470, {static_cast<u64>(pc), 0, 0, 0}) & 0xFF;
            INFO(std::string(snap) << " pc " << pc << " hp " << hp << "/" << maxhp << " sp " << sp << "/" << maxsp << " level " << level);
            const u64 xy = (static_cast<u64>(fbits(219.0f)) << 32) | fbits(40.0f);
            // the HP block: the frame, then the current HP, then the maximum (colour 102) -- up to three digits each
            const Run r = pair_si(*m, "sub_1236A0", {xy, static_cast<u64>(pc), 0, 200}, snap);
            std::size_t frame_at = r.log.size();
            for (std::size_t i = 0; i < r.log.size(); ++i)
                if (r.log[i].va == kDrawSprite && r.log[i].args[2] == 4) { frame_at = i; break; }
            REQUIRE(frame_at < r.log.size());
            std::vector<int> cur, max;
            for (std::size_t i = frame_at + 1; i < r.log.size(); ++i) {
                const s64 sprite = static_cast<s64>(r.log[i].args[2]);
                if (sprite < 11 || sprite > 20) continue;
                (r.log[i].va == kDrawSprite ? cur : max).push_back(static_cast<int>(sprite - 11));
                if (r.log[i].va == kDrawSpriteRgb2) CHECK(r.log[i].args[4] == 102);  // the maximum's colour byte
            }
            CHECK(cur == decimal(hp));
            CHECK(max == decimal(maxhp));
            // the whole panel: the level's two digits come first (font 2), then the HP and SP blocks with gauges
            const Run p = pair_si(*m, "sub_124B30", {xy, 0, static_cast<u64>(pc), 255}, snap);
            const std::vector<int> d = digits_of(p.log, 0, p.log.size());
            std::vector<int> want = decimal(level);
            for (int x : decimal(hp)) want.push_back(x);
            for (int x : decimal(maxhp)) want.push_back(x);
            REQUIRE(d.size() >= want.size());
            CHECK(std::vector<int>(d.begin(), d.begin() + static_cast<std::ptrdiff_t>(want.size())) == want);
            ++checked;
        }
    }
    MESSAGE("status panels checked: " << checked);
}

TEST_CASE("game(ui6): the item screen driven frame by frame") {
    for (const char* snap : kSnapshots) {
        auto m = real_machine(snap);
        if (!m) { MESSAGE("SKIP: no snapshot " << snap); continue; }
        install_fake_tasks(*m);
        Machine& mm = *m;
        // the item screen after its files and allocations (states 0 / 1): the lists as state 1 initialises them
        zero(mm, kTask, 0x100);
        wr32(mm, kTask + 0x3C, kWork);
        zero(mm, kWork, 0x400);
        zero(mm, kTweens, 0x3000);
        zero(mm, kTweens2, 0x1000);
        zero(mm, kTweens3, 0x1000);
        zero(mm, kList0, 0x1000);
        zero(mm, kList1, 0x3000);
        zero(mm, kList2, 0x1000);
        for (u32 i = 0; i < 300; ++i) {
            wr32(mm, kList0 + u6::ilist::kEntries + 8 * i, 0xFFFFFFFFu);
            wr32(mm, kList2 + u6::ilist::kEntries + 8 * i, 0xFFFFFFFFu);
        }
        for (u32 i = 0; i < 320; ++i) {
            wr32(mm, kList1 + u6::elist::kRows + 36 * i, 0xFFFFFFFFu);
            wr32(mm, kList1 + u6::elist::kRows + 36 * i + 4, 0xFFFFFFFFu);
        }
        wr32(mm, kWork + u6::item::kState, 3);
        wr32(mm, kWork + u6::item::kItemList, kList0);
        wr32(mm, kWork + u6::item::kEquipList, kList1);
        wr32(mm, kWork + u6::item::kMaterialList, kList2);
        wr32(mm, kWork + u6::item::kTweens, kTweens);
        wr32(mm, kWork + u6::item::kEquipTweens, kTweens2);
        wr32(mm, kWork + u6::item::kMaterialTweens, kTweens3);

        // state 3: the lists filled from the game state
        CHECK(frame(mm, "sub_14C5C0", 0, 0, snap) == 0);
        CHECK(rd32(mm, kWork + u6::item::kState) == 4);
        std::vector<std::pair<u32, u32>> items;
        for (u32 id = 4000; id < 4224; ++id) {
            const u32 n = call1(mm, &recomp_gen::fn_sub_170760_00170760, {1, id, 0, 0}) & 0xFFFF;
            if (n) items.emplace_back(id, n);
        }
        const s32 count = rds32(mm, kList0 + u6::ilist::kCount);
        INFO(std::string(snap) << ": " << items.size() << " items");
        REQUIRE(count == static_cast<s32>(items.size()));
        for (s32 i = 0; i < count; ++i) {
            CHECK(rd32(mm, kList0 + u6::ilist::kEntries + 8 * i) == items[i].first);
            CHECK(rd32(mm, kList0 + u6::ilist::kEntries + 8 * i + 4) == items[i].second);
        }
        std::vector<u32> materials;
        for (u32 id = 5001; id < 5128; ++id)
            if (call1(mm, &recomp_gen::fn_datGetFlag_0016f190, {id - 4488, 0, 0, 0}) & 0xFFFFFFFFu) materials.push_back(id);
        REQUIRE(rds32(mm, kList2 + u6::ilist::kCount) == static_cast<s32>(materials.size()));
        for (std::size_t i = 0; i < materials.size(); ++i) {
            CHECK(rd32(mm, kList2 + u6::ilist::kEntries + 8 * static_cast<u32>(i)) == materials[i]);
            CHECK(rd32(mm, kList2 + u6::ilist::kEntries + 8 * static_cast<u32>(i) + 4) == 1);
        }
        const std::vector<int> members = party(mm);
        REQUIRE(rds32(mm, kWork + u6::item::kTargetCount) == static_cast<s32>(members.size()));
        for (std::size_t i = 0; i < members.size(); ++i) CHECK(rds32(mm, kWork + u6::item::kTargets + 4 * static_cast<u32>(i)) == members[i]);
        s32 personas = 0;
        for (int s = 0; s < 12; ++s) {
            if (!(call1(mm, &recomp_gen::fn_sub_174960_00174960, {static_cast<u64>(s), 0, 0, 0}) & 0xFFFFFFFFu)) break;
            CHECK(rds32(mm, kWork + u6::item::kPersonas + 4 * s) == s);
            ++personas;
        }
        CHECK(rds32(mm, kWork + u6::item::kPersonaCount) == personas);

        // state 4: the list cursor. cursor + 1 on the repeat word walks the list (5 rows a page) and stops at the
        // last row; on the press word too it wraps around to the first.
        auto index = [&] { return rds32(mm, kList0 + u6::ilist::kScroll) + rds32(mm, kList0 + u6::ilist::kCursor); };
        CHECK(index() == 0);
        if (count > 1) {
            for (s32 k = 1; k < count; ++k) {
                frame(mm, "sub_14C5C0", 0, 0x4000, snap);
                CHECK(index() == k);
                CHECK(rds32(mm, kList0 + u6::ilist::kCursor) <= 4);
                CHECK(rds32(mm, kList0 + u6::ilist::kCursor) == std::min(k, 4));
            }
            frame(mm, "sub_14C5C0", 0, 0x4000, snap);  // held at the end: no wrap
            CHECK(index() == count - 1);
            frame(mm, "sub_14C5C0", 0x4000, 0x4000, snap);  // a fresh press: around to the first row
            CHECK(index() == 0);
            frame(mm, "sub_14C5C0", 0x1000, 0x1000, snap);  // and back to the last
            CHECK(index() == count - 1);
            frame(mm, "sub_14C5C0", 0, 0x1000, snap);
            CHECK(index() == count - 2);
        }
        CHECK(rd32(mm, kWork + u6::item::kState) == 4);
        // R1 opens the equipment page (state 16), cancel there ... the page states run on
        frame(mm, "sub_14C5C0", 0, 0x2000, snap);
        CHECK(rd32(mm, kWork + u6::item::kState) == 16);
        for (int f = 0; f < 3; ++f) frame(mm, "sub_14C5C0", 0, 0, snap);
        CHECK(rd32(mm, kWork + u6::item::kState) == 18);
        // cancel on the equipment page closes the screen: state 19, then -1
        frame(mm, "sub_14C5C0", 0x20, 0, snap);
        CHECK(rd32(mm, kWork + u6::item::kState) == 19);
        CHECK(frame(mm, "sub_14C5C0", 0, 0, snap) == static_cast<u64>(-1));
    }
}

TEST_CASE("game(ui6): the equipment screen: slot menu, candidates, equip and the HP / SP rescale") {
    for (const char* snap : kSnapshots) {
        auto m = real_machine(snap);
        if (!m) { MESSAGE("SKIP: no snapshot " << snap); continue; }
        install_fake_tasks(*m);
        Machine& mm = *m;
        for (int pc : party(mm)) {
            zero(mm, kTask, 0x100);
            wr32(mm, kTask + 0x3C, kWork);
            zero(mm, kWork, 0x400);
            zero(mm, kTweens, 0x3000);
            wr32(mm, kWork + u6::equip::kState, 4);  // the slot menu (states 0..3: the pak and the slide-in)
            wr16(mm, kWork + u6::equip::kPc, static_cast<u16>(pc));
            wr32(mm, kWork + u6::equip::kSlotTweens, kTweens);
            wr32(mm, kWork + u6::equip::kListTweens, kTweens + 0x400);
            wr32(mm, kWork + u6::equip::kBackdrop, kTweens + 0x800);
            INFO(std::string(snap) << " pc " << pc);
            // the first frame of state 4 sees the tweens arrive; then the slot cursor moves
            frame(mm, "sub_12C430", 0, 0, snap);
            CHECK(rd32(mm, kWork + u6::equip::kSlotsArrived) == 1);
            CHECK(rd16(mm, kWork + u6::equip::kSlot) == 0);
            // the slot menu does not wrap: cursor - 1 stops at the weapon slot, cursor + 1 at the accessory slot,
            // fresh press or not
            frame(mm, "sub_12C430", 0x1000, 0x1000, snap);
            CHECK(rd16(mm, kWork + u6::equip::kSlot) == 0);
            for (u16 k = 1; k <= 3; ++k) {
                frame(mm, "sub_12C430", 0, 0x4000, snap);
                CHECK(rd16(mm, kWork + u6::equip::kSlot) == k);
            }
            frame(mm, "sub_12C430", 0x4000, 0x4000, snap);
            CHECK(rd16(mm, kWork + u6::equip::kSlot) == 3);
            for (int k = 0; k < 3; ++k) frame(mm, "sub_12C430", 0, 0x1000, snap);
            CHECK(rd16(mm, kWork + u6::equip::kSlot) == 0);
            // confirm (the repeat word: this screen reads 0x7E0952 for confirm / cancel) -> the candidate list
            frame(mm, "sub_12C430", 0, 0x40, snap);
            CHECK(rd32(mm, kWork + u6::equip::kState) == 7);
            frame(mm, "sub_12C430", 0, 0, snap);  // state 7: the candidates of the weapon slot
            CHECK(rd32(mm, kWork + u6::equip::kState) == 8);
            const s32 n = rds32(mm, kWork + u6::equip::kCandidateCount);
            CHECK(n >= 0);
            CHECK(n <= 300);
            for (int f = 0; f < 3 && rd32(mm, kWork + u6::equip::kState) != 10; ++f) frame(mm, "sub_12C430", 0, 0, snap);
            REQUIRE(rd32(mm, kWork + u6::equip::kState) == 10);
            if (n == 0) continue;
            // equip the first candidate: datSetEquipmentIdx(pc, slot 0, its index), HP / SP rescaled to the new maxima
            const u16 cand = rd16(mm, kWork + u6::equip::kCandidates);
            const Args a{static_cast<u64>(pc), 0, 0, 0};
            const unsigned hp0 = call1(mm, &recomp_gen::fn_sub_16C4F0_0016c4f0, a) & 0xFFFF;
            const unsigned max0 = call1(mm, &recomp_gen::fn_sub_16C5F0_0016c5f0, a) & 0xFFFF;
            const unsigned sp0 = call1(mm, &recomp_gen::fn_sub_16C570_0016c570, a) & 0xFFFF;
            const unsigned maxsp0 = call1(mm, &recomp_gen::fn_sub_16C670_0016c670, a) & 0xFFFF;
            frame(mm, "sub_12C430", 0x40, 0, snap);
            CHECK((call1(mm, &recomp_gen::fn_datGetEquipmentIdx_0016cb80, a) & 0xFFFF) == cand);
            const unsigned hp1 = call1(mm, &recomp_gen::fn_sub_16C4F0_0016c4f0, a) & 0xFFFF;
            const unsigned max1 = call1(mm, &recomp_gen::fn_sub_16C5F0_0016c5f0, a) & 0xFFFF;
            const unsigned sp1 = call1(mm, &recomp_gen::fn_sub_16C570_0016c570, a) & 0xFFFF;
            const unsigned maxsp1 = call1(mm, &recomp_gen::fn_sub_16C670_0016c670, a) & 0xFFFF;
            if (max1 != max0 && max0 != 0) CHECK(hp1 == static_cast<u16>(hp0 * max1 / max0));
            else CHECK(hp1 == hp0);
            if (maxsp1 != maxsp0 && maxsp0 != 0) CHECK(sp1 == static_cast<u16>(sp0 * maxsp1 / maxsp0));
            else CHECK(sp1 == sp0);
        }
    }
}

TEST_CASE("game(ui6): the system menu: entries, the config page and the calendar") {
    for (const char* snap : kSnapshots) {
        auto m = real_machine(snap);
        if (!m) { MESSAGE("SKIP: no snapshot " << snap); continue; }
        install_fake_tasks(*m);
        Machine& mm = *m;
        zero(mm, kTask, 0x100);
        wr32(mm, kTask + 0x3C, kWork);
        zero(mm, kWork, 0x400);
        zero(mm, kTweens, 0x3000);
        zero(mm, kTweens2, 0x1000);
        wr32(mm, kWork + u6::sys::kState, 3);
        wr32(mm, kWork + u6::sys::kMenuTweens, kTweens2);
        wr32(mm, kWork + u6::sys::kPageTweens, kTweens);
        INFO(std::string(snap));
        frame(mm, "sub_14F7D0", 0, 0, snap);  // the menu's tweens arrive: input enabled
        CHECK(rd32(mm, kWork + u6::sys::kArrived) == 1);
        // cursor - 1 at entry 0: held stays, a fresh press wraps to the last entry
        frame(mm, "sub_14F7D0", 0, 0x1000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kCursor) == 0);
        frame(mm, "sub_14F7D0", 0x1000, 0x1000, snap);
        const s32 last = rds32(mm, kWork + u6::sys::kCursor);
        CHECK(last == 5);
        frame(mm, "sub_14F7D0", 0, 0x4000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kCursor) == 5);
        frame(mm, "sub_14F7D0", 0x4000, 0x4000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kCursor) == 0);
        // entry 4 = config: confirm -> state 6, which reads the option values from flags 387..
        for (int k = 0; k < 4; ++k) frame(mm, "sub_14F7D0", 0, 0x4000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kCursor) == 4);
        frame(mm, "sub_14F7D0", 0x40, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 6);
        frame(mm, "sub_14F7D0", 0, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 7);
        auto flag = [&](u32 f) { return static_cast<u32>(call1(mm, &recomp_gen::fn_datGetFlag_0016f190, {f, 0, 0, 0})); };
        for (u32 i = 0; i < 7; ++i) CHECK(rd32(mm, kWork + u6::sys::kConfigValues + 4 * i) == flag(387 + i));
        for (int f = 0; f < 3 && rd32(mm, kWork + u6::sys::kState) != 8; ++f) frame(mm, "sub_14F7D0", 0, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 8);
        frame(mm, "sub_14F7D0", 0, 0, snap);  // the page's tweens arrive: input enabled
        CHECK(rds32(mm, kWork + u6::sys::kConfigCursor) == 0);
        // row 3: 0x8000 turns the option on, 0x2000 off (fresh presses); set it to the opposite of its flag
        for (int k = 0; k < 3; ++k) frame(mm, "sub_14F7D0", 0, 0x4000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kConfigCursor) == 3);
        const u32 before = flag(390);
        frame(mm, "sub_14F7D0", 0x8000, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kConfigValues + 12) == 1);
        frame(mm, "sub_14F7D0", 0x2000, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kConfigValues + 12) == 0);
        frame(mm, "sub_14F7D0", before ? 0x2000 : 0x8000, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kConfigValues + 12) == (before ? 0u : 1u));
        frame(mm, "sub_14F7D0", 0x40, 0, snap);  // confirm on an option row does nothing
        CHECK(rd32(mm, kWork + u6::sys::kState) == 8);
        CHECK(flag(390) == before);
        // the rows do not wrap on the repeat word; row 7 is OK: confirm there writes the seven flags
        for (int k = 0; k < 5; ++k) frame(mm, "sub_14F7D0", 0, 0x4000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kConfigCursor) == 7);
        frame(mm, "sub_14F7D0", 0x40, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 9);
        CHECK(flag(390) == (before ? 0u : 1u));
        for (int f = 0; f < 4 && rd32(mm, kWork + u6::sys::kState) != 3; ++f) frame(mm, "sub_14F7D0", 0, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 3);
        frame(mm, "sub_14F7D0", 0, 0, snap);
        // entry 0 = the calendar: today's month and day
        for (int k = 0; k < 4; ++k) frame(mm, "sub_14F7D0", 0, 0x1000, snap);
        CHECK(rds32(mm, kWork + u6::sys::kCursor) == 0);
        frame(mm, "sub_14F7D0", 0x40, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 26);
        frame(mm, "sub_14F7D0", 0, 0, snap);
        const s32 month = rds32(mm, kWork + u6::sys::kMonth), day = rds32(mm, kWork + u6::sys::kDay);
        CHECK(month >= 1);
        CHECK(month <= 12);
        CHECK(day >= 1);
        CHECK(day <= 31);
        for (int f = 0; f < 3; ++f) frame(mm, "sub_14F7D0", 0, 0, snap);
        CHECK(rd32(mm, kWork + u6::sys::kState) == 28);
        MESSAGE(std::string(snap) << ": calendar opened on " << month << "/" << day);
        // 0x8 = the next month: April .. March of the school year (12 -> 1), never past March; 0x4 = the previous one,
        // never before April; the day is clamped to the month's length (tbl_clndMonthLengths) and April starts on the 7th
        static const int kLen[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        auto check_day = [&] {
            const s32 mo = rds32(mm, kWork + u6::sys::kMonth), d = rds32(mm, kWork + u6::sys::kDay);
            CHECK(d >= 1);
            CHECK(d <= kLen[mo]);
            if (mo == 4) CHECK(d >= 7);
        };
        s32 mo = month;
        for (int k = 0; k < 14; ++k) {
            frame(mm, "sub_14F7D0", 0, 0x8, snap);
            if (mo != 3) mo = mo == 12 ? 1 : mo + 1;
            CHECK(rds32(mm, kWork + u6::sys::kMonth) == mo);
            check_day();
        }
        CHECK(mo == 3);
        for (int k = 0; k < 14; ++k) {
            frame(mm, "sub_14F7D0", 0, 0x4, snap);
            if (mo != 4) mo = mo == 1 ? 12 : mo - 1;
            CHECK(rds32(mm, kWork + u6::sys::kMonth) == mo);
            check_day();
        }
        CHECK(mo == 4);
        frame(mm, "sub_14F7D0", 0x20, 0, snap);  // cancel: back to the menu
        CHECK(rd32(mm, kWork + u6::sys::kState) == 29);
    }
}

TEST_CASE("game(ui6): the skill list of the persona stock") {
    for (const char* snap : kSnapshots) {
        auto m = real_machine(snap);
        if (!m) { MESSAGE("SKIP: no snapshot " << snap); continue; }
        install_fake_tasks(*m);
        Machine& mm = *m;
        zero(mm, kList1, 0x1000);
        pair_si(mm, "sub_15C840", {sx(kList1), 0, 0, 0}, snap);
        // every distinct non-zero skill of the used stock slots, once
        std::set<u32> want;
        for (int s = 0; s < 12; ++s) {
            if (!(call1(mm, &recomp_gen::fn_sub_174960_00174960, {static_cast<u64>(s), 0, 0, 0}) & 0xFFFFFFFFu)) continue;
            const u32 p = static_cast<u32>(call1(mm, &recomp_gen::fn_sub_174A90_00174a90, {static_cast<u64>(s), 0, 0, 0}));
            for (u32 j = 0; j < 8; ++j)
                if (const u16 sk = rd16(mm, p + 12 + 2 * j)) want.insert(sk);
        }
        const s32 n = rds32(mm, kList1 + 2012);
        INFO(std::string(snap) << ": " << want.size() << " skills");
        REQUIRE(n == static_cast<s32>(want.size()));
        std::set<u32> got;
        bool special_done = false;
        u32 prev = 0;
        for (s32 i = 0; i < n; ++i) {
            const u32 sk = rd32(mm, kList1 + 12 + 20 * i);
            got.insert(sk);
            const bool special = sk >= 192 && sk < 256;
            if (!special) {
                if (special_done) CHECK(sk > prev);  // the rest by id
                special_done = true;
                prev = sk;
            } else {
                CHECK(!special_done);  // skills 192..255 first
            }
        }
        CHECK(got == want);
    }
}

TEST_CASE("game(ui6): real-state pair count") { MESSAGE("real-state pairs: " << g_pairs << ", check points compared: " << g_checks); }

#else

TEST_CASE("game(ui6): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
