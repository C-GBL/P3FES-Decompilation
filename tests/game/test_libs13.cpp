// Pair tests for slice libs13 (CRI Sofdec's SFD core around the video decoder): every body against its recompiled body,
// compared by tests/game/handgen_pairs.h -- the whole register file and cycle count at every check point and at the
// return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log -- on random worlds, on SFD handle
// worlds (the handle, its video-decoder work, frame records with real states; libs13.h's records), on the replay
// snapshots' RAM, and a few documented-rule checks. Callees this build does not emit stop both runs at the same call.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs13.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

namespace p3fes::recomp_gen {
void fn_sub_590008_00590008(EEContext&);  // generated body
void fn_sub_590008_00590008__recomp(EEContext&);  // recompiled
void fn_sub_590360_00590360(EEContext&);  // generated body
void fn_sub_590360_00590360__recomp(EEContext&);  // recompiled
void fn_sub_590408_00590408(EEContext&);  // generated body
void fn_sub_590408_00590408__recomp(EEContext&);  // recompiled
void fn_sub_5905F0_005905f0(EEContext&);  // generated body
void fn_sub_5905F0_005905f0__recomp(EEContext&);  // recompiled
void fn_sub_590948_00590948(EEContext&);  // generated body
void fn_sub_590948_00590948__recomp(EEContext&);  // recompiled
void fn_sub_590AE8_00590ae8(EEContext&);  // generated body
void fn_sub_590AE8_00590ae8__recomp(EEContext&);  // recompiled
void fn_sub_590DF8_00590df8(EEContext&);  // generated body
void fn_sub_590DF8_00590df8__recomp(EEContext&);  // recompiled
void fn_sub_590EF0_00590ef0(EEContext&);  // generated body
void fn_sub_590EF0_00590ef0__recomp(EEContext&);  // recompiled
void fn_sub_590FD0_00590fd0(EEContext&);  // generated body
void fn_sub_590FD0_00590fd0__recomp(EEContext&);  // recompiled
void fn_sub_591118_00591118(EEContext&);  // generated body
void fn_sub_591118_00591118__recomp(EEContext&);  // recompiled
void fn_sub_591168_00591168(EEContext&);  // generated body
void fn_sub_591168_00591168__recomp(EEContext&);  // recompiled
void fn_sub_591298_00591298(EEContext&);  // generated body
void fn_sub_591298_00591298__recomp(EEContext&);  // recompiled
void fn_sub_5913B8_005913b8(EEContext&);  // generated body
void fn_sub_5913B8_005913b8__recomp(EEContext&);  // recompiled
void fn_sub_5913F0_005913f0(EEContext&);  // generated body
void fn_sub_5913F0_005913f0__recomp(EEContext&);  // recompiled
void fn_sub_5915A8_005915a8(EEContext&);  // generated body
void fn_sub_5915A8_005915a8__recomp(EEContext&);  // recompiled
void fn_sub_5916A0_005916a0(EEContext&);  // generated body
void fn_sub_5916A0_005916a0__recomp(EEContext&);  // recompiled
void fn_sub_591858_00591858(EEContext&);  // generated body
void fn_sub_591858_00591858__recomp(EEContext&);  // recompiled
void fn_sub_591C80_00591c80(EEContext&);  // generated body
void fn_sub_591C80_00591c80__recomp(EEContext&);  // recompiled
void fn_sub_591F38_00591f38(EEContext&);  // generated body
void fn_sub_591F38_00591f38__recomp(EEContext&);  // recompiled
void fn_sub_592240_00592240(EEContext&);  // generated body
void fn_sub_592240_00592240__recomp(EEContext&);  // recompiled
void fn_sub_5922C8_005922c8(EEContext&);  // generated body
void fn_sub_5922C8_005922c8__recomp(EEContext&);  // recompiled
void fn_sub_592570_00592570(EEContext&);  // generated body
void fn_sub_592570_00592570__recomp(EEContext&);  // recompiled
void fn_sub_592618_00592618(EEContext&);  // generated body
void fn_sub_592618_00592618__recomp(EEContext&);  // recompiled
void fn_sub_592790_00592790(EEContext&);  // generated body
void fn_sub_592790_00592790__recomp(EEContext&);  // recompiled
void fn_sub_592958_00592958(EEContext&);  // generated body
void fn_sub_592958_00592958__recomp(EEContext&);  // recompiled
void fn_sub_5929B0_005929b0(EEContext&);  // generated body
void fn_sub_5929B0_005929b0__recomp(EEContext&);  // recompiled
void fn_sub_592B10_00592b10(EEContext&);  // generated body
void fn_sub_592B10_00592b10__recomp(EEContext&);  // recompiled
void fn_sub_592D08_00592d08(EEContext&);  // generated body
void fn_sub_592D08_00592d08__recomp(EEContext&);  // recompiled
void fn_sub_592DD0_00592dd0(EEContext&);  // generated body
void fn_sub_592DD0_00592dd0__recomp(EEContext&);  // recompiled
void fn_sub_592E80_00592e80(EEContext&);  // generated body
void fn_sub_592E80_00592e80__recomp(EEContext&);  // recompiled
void fn_sub_592EA0_00592ea0(EEContext&);  // generated body
void fn_sub_592EA0_00592ea0__recomp(EEContext&);  // recompiled
void fn_sub_592F38_00592f38(EEContext&);  // generated body
void fn_sub_592F38_00592f38__recomp(EEContext&);  // recompiled
void fn_sub_5930C8_005930c8(EEContext&);  // generated body
void fn_sub_5930C8_005930c8__recomp(EEContext&);  // recompiled
void fn_sub_593200_00593200(EEContext&);  // generated body
void fn_sub_593200_00593200__recomp(EEContext&);  // recompiled
void fn_sub_593468_00593468(EEContext&);  // generated body
void fn_sub_593468_00593468__recomp(EEContext&);  // recompiled
void fn_sub_593590_00593590(EEContext&);  // generated body
void fn_sub_593590_00593590__recomp(EEContext&);  // recompiled
void fn_sub_593700_00593700(EEContext&);  // generated body
void fn_sub_593700_00593700__recomp(EEContext&);  // recompiled
void fn_sub_593878_00593878(EEContext&);  // generated body
void fn_sub_593878_00593878__recomp(EEContext&);  // recompiled
void fn_sub_593900_00593900(EEContext&);  // generated body
void fn_sub_593900_00593900__recomp(EEContext&);  // recompiled
void fn_sub_593958_00593958(EEContext&);  // generated body
void fn_sub_593958_00593958__recomp(EEContext&);  // recompiled
void fn_sub_593968_00593968(EEContext&);  // generated body
void fn_sub_593968_00593968__recomp(EEContext&);  // recompiled
void fn_sub_593978_00593978(EEContext&);  // generated body
void fn_sub_593978_00593978__recomp(EEContext&);  // recompiled
void fn_sub_593A18_00593a18(EEContext&);  // generated body
void fn_sub_593A18_00593a18__recomp(EEContext&);  // recompiled
void fn_sub_593AB0_00593ab0(EEContext&);  // generated body
void fn_sub_593AB0_00593ab0__recomp(EEContext&);  // recompiled
void fn_sub_593AE0_00593ae0(EEContext&);  // generated body
void fn_sub_593AE0_00593ae0__recomp(EEContext&);  // recompiled
void fn_sub_593B38_00593b38(EEContext&);  // generated body
void fn_sub_593B38_00593b38__recomp(EEContext&);  // recompiled
void fn_sub_593DB0_00593db0(EEContext&);  // generated body
void fn_sub_593DB0_00593db0__recomp(EEContext&);  // recompiled
void fn_sub_593E08_00593e08(EEContext&);  // generated body
void fn_sub_593E08_00593e08__recomp(EEContext&);  // recompiled
void fn_sub_593EA0_00593ea0(EEContext&);  // generated body
void fn_sub_593EA0_00593ea0__recomp(EEContext&);  // recompiled
void fn_sub_593FB0_00593fb0(EEContext&);  // generated body
void fn_sub_593FB0_00593fb0__recomp(EEContext&);  // recompiled
void fn_sub_593FE8_00593fe8(EEContext&);  // generated body
void fn_sub_593FE8_00593fe8__recomp(EEContext&);  // recompiled
void fn_sub_594108_00594108(EEContext&);  // generated body
void fn_sub_594108_00594108__recomp(EEContext&);  // recompiled
void fn_viBufCreate_00594130(EEContext&);  // generated body
void fn_viBufCreate_00594130__recomp(EEContext&);  // recompiled
void fn_sub_5942E8_005942e8(EEContext&);  // generated body
void fn_sub_5942E8_005942e8__recomp(EEContext&);  // recompiled
void fn_sub_5943D8_005943d8(EEContext&);  // generated body
void fn_sub_5943D8_005943d8__recomp(EEContext&);  // recompiled
void fn_sub_594428_00594428(EEContext&);  // generated body
void fn_sub_594428_00594428__recomp(EEContext&);  // recompiled
void fn_sub_594B68_00594b68(EEContext&);  // generated body
void fn_sub_594B68_00594b68__recomp(EEContext&);  // recompiled
void fn_sub_594B78_00594b78(EEContext&);  // generated body
void fn_sub_594B78_00594b78__recomp(EEContext&);  // recompiled
void fn_sub_594B88_00594b88(EEContext&);  // generated body
void fn_sub_594B88_00594b88__recomp(EEContext&);  // recompiled
void fn_sub_594C38_00594c38(EEContext&);  // generated body
void fn_sub_594C38_00594c38__recomp(EEContext&);  // recompiled
void fn_sub_594EC8_00594ec8(EEContext&);  // generated body
void fn_sub_594EC8_00594ec8__recomp(EEContext&);  // recompiled
void fn_sub_595010_00595010(EEContext&);  // generated body
void fn_sub_595010_00595010__recomp(EEContext&);  // recompiled
void fn_sub_595038_00595038(EEContext&);  // generated body
void fn_sub_595038_00595038__recomp(EEContext&);  // recompiled
void fn_sub_595060_00595060(EEContext&);  // generated body
void fn_sub_595060_00595060__recomp(EEContext&);  // recompiled
void fn_sub_595110_00595110(EEContext&);  // generated body
void fn_sub_595110_00595110__recomp(EEContext&);  // recompiled
void fn_sub_595138_00595138(EEContext&);  // generated body
void fn_sub_595138_00595138__recomp(EEContext&);  // recompiled
void fn_sub_5951A8_005951a8(EEContext&);  // generated body
void fn_sub_5951A8_005951a8__recomp(EEContext&);  // recompiled
void fn_sub_595260_00595260(EEContext&);  // generated body
void fn_sub_595260_00595260__recomp(EEContext&);  // recompiled
void fn_sub_595390_00595390(EEContext&);  // generated body
void fn_sub_595390_00595390__recomp(EEContext&);  // recompiled
void fn_sub_5954D8_005954d8(EEContext&);  // generated body
void fn_sub_5954D8_005954d8__recomp(EEContext&);  // recompiled
void fn_sub_5954E8_005954e8(EEContext&);  // generated body
void fn_sub_5954E8_005954e8__recomp(EEContext&);  // recompiled
void fn_sub_595700_00595700(EEContext&);  // generated body
void fn_sub_595700_00595700__recomp(EEContext&);  // recompiled
void fn_sub_595718_00595718(EEContext&);  // generated body
void fn_sub_595718_00595718__recomp(EEContext&);  // recompiled
void fn_sub_5959D0_005959d0(EEContext&);  // generated body
void fn_sub_5959D0_005959d0__recomp(EEContext&);  // recompiled
void fn_sub_595B30_00595b30(EEContext&);  // generated body
void fn_sub_595B30_00595b30__recomp(EEContext&);  // recompiled
void fn_sub_595B58_00595b58(EEContext&);  // generated body
void fn_sub_595B58_00595b58__recomp(EEContext&);  // recompiled
void fn_sub_595D10_00595d10(EEContext&);  // generated body
void fn_sub_595D10_00595d10__recomp(EEContext&);  // recompiled
void fn_sub_595E28_00595e28(EEContext&);  // generated body
void fn_sub_595E28_00595e28__recomp(EEContext&);  // recompiled
void fn_sub_595E50_00595e50(EEContext&);  // generated body
void fn_sub_595E50_00595e50__recomp(EEContext&);  // recompiled
void fn_sub_595E68_00595e68(EEContext&);  // generated body
void fn_sub_595E68_00595e68__recomp(EEContext&);  // recompiled
void fn_sub_595E98_00595e98(EEContext&);  // generated body
void fn_sub_595E98_00595e98__recomp(EEContext&);  // recompiled
void fn_sub_595F58_00595f58(EEContext&);  // generated body
void fn_sub_595F58_00595f58__recomp(EEContext&);  // recompiled
void fn_sub_596008_00596008(EEContext&);  // generated body
void fn_sub_596008_00596008__recomp(EEContext&);  // recompiled
void fn_sub_596038_00596038(EEContext&);  // generated body
void fn_sub_596038_00596038__recomp(EEContext&);  // recompiled
void fn_sub_5960E0_005960e0(EEContext&);  // generated body
void fn_sub_5960E0_005960e0__recomp(EEContext&);  // recompiled
void fn_sub_596168_00596168(EEContext&);  // generated body
void fn_sub_596168_00596168__recomp(EEContext&);  // recompiled
void fn_sub_596230_00596230(EEContext&);  // generated body
void fn_sub_596230_00596230__recomp(EEContext&);  // recompiled
void fn_sub_5962D0_005962d0(EEContext&);  // generated body
void fn_sub_5962D0_005962d0__recomp(EEContext&);  // recompiled
void fn_sub_596348_00596348(EEContext&);  // generated body
void fn_sub_596348_00596348__recomp(EEContext&);  // recompiled
void fn_sub_5963B0_005963b0(EEContext&);  // generated body
void fn_sub_5963B0_005963b0__recomp(EEContext&);  // recompiled
void fn_sub_596460_00596460(EEContext&);  // generated body
void fn_sub_596460_00596460__recomp(EEContext&);  // recompiled
void fn_sub_5966C0_005966c0(EEContext&);  // generated body
void fn_sub_5966C0_005966c0__recomp(EEContext&);  // recompiled
void fn_sub_596898_00596898(EEContext&);  // generated body
void fn_sub_596898_00596898__recomp(EEContext&);  // recompiled
void fn_sub_596908_00596908(EEContext&);  // generated body
void fn_sub_596908_00596908__recomp(EEContext&);  // recompiled
void fn_sub_596978_00596978(EEContext&);  // generated body
void fn_sub_596978_00596978__recomp(EEContext&);  // recompiled
void fn_sub_596A40_00596a40(EEContext&);  // generated body
void fn_sub_596A40_00596a40__recomp(EEContext&);  // recompiled
void fn_sub_596A98_00596a98(EEContext&);  // generated body
void fn_sub_596A98_00596a98__recomp(EEContext&);  // recompiled
void fn_sub_596C28_00596c28(EEContext&);  // generated body
void fn_sub_596C28_00596c28__recomp(EEContext&);  // recompiled
void fn_sub_596CC0_00596cc0(EEContext&);  // generated body
void fn_sub_596CC0_00596cc0__recomp(EEContext&);  // recompiled
void fn_sub_596D28_00596d28(EEContext&);  // generated body
void fn_sub_596D28_00596d28__recomp(EEContext&);  // recompiled
void fn_sub_596D68_00596d68(EEContext&);  // generated body
void fn_sub_596D68_00596d68__recomp(EEContext&);  // recompiled
void fn_sub_596F98_00596f98(EEContext&);  // generated body
void fn_sub_596F98_00596f98__recomp(EEContext&);  // recompiled
void fn_sub_597000_00597000(EEContext&);  // generated body
void fn_sub_597000_00597000__recomp(EEContext&);  // recompiled
void fn_sub_597078_00597078(EEContext&);  // generated body
void fn_sub_597078_00597078__recomp(EEContext&);  // recompiled
void fn_sub_597088_00597088(EEContext&);  // generated body
void fn_sub_597088_00597088__recomp(EEContext&);  // recompiled
void fn_sub_597100_00597100(EEContext&);  // generated body
void fn_sub_597100_00597100__recomp(EEContext&);  // recompiled
void fn_sub_5971D0_005971d0(EEContext&);  // generated body
void fn_sub_5971D0_005971d0__recomp(EEContext&);  // recompiled
void fn_sub_5971E8_005971e8(EEContext&);  // generated body
void fn_sub_5971E8_005971e8__recomp(EEContext&);  // recompiled
void fn_sub_597288_00597288(EEContext&);  // generated body
void fn_sub_597288_00597288__recomp(EEContext&);  // recompiled
void fn_sub_597330_00597330(EEContext&);  // generated body
void fn_sub_597330_00597330__recomp(EEContext&);  // recompiled
void fn_sub_597340_00597340(EEContext&);  // generated body
void fn_sub_597340_00597340__recomp(EEContext&);  // recompiled
void fn_sub_5973C0_005973c0(EEContext&);  // generated body
void fn_sub_5973C0_005973c0__recomp(EEContext&);  // recompiled
void fn_sceInsockSetErrnoMode_1_00597428(EEContext&);  // generated body
void fn_sceInsockSetErrnoMode_1_00597428__recomp(EEContext&);  // recompiled
void fn_my_malloc_1_00597448(EEContext&);  // generated body
void fn_my_malloc_1_00597448__recomp(EEContext&);  // recompiled
void fn_sub_5974A8_005974a8(EEContext&);  // generated body
void fn_sub_5974A8_005974a8__recomp(EEContext&);  // recompiled
void fn_sub_597C28_00597c28(EEContext&);  // generated body
void fn_sub_597C28_00597c28__recomp(EEContext&);  // recompiled
void fn_sub_597D20_00597d20(EEContext&);  // generated body
void fn_sub_597D20_00597d20__recomp(EEContext&);  // recompiled
void fn_sub_597DC8_00597dc8(EEContext&);  // generated body
void fn_sub_597DC8_00597dc8__recomp(EEContext&);  // recompiled
void fn_sub_597E20_00597e20(EEContext&);  // generated body
void fn_sub_597E20_00597e20__recomp(EEContext&);  // recompiled
void fn_sub_597E80_00597e80(EEContext&);  // generated body
void fn_sub_597E80_00597e80__recomp(EEContext&);  // recompiled
void fn_sub_597FA0_00597fa0(EEContext&);  // generated body
void fn_sub_597FA0_00597fa0__recomp(EEContext&);  // recompiled
void fn_sub_5980C8_005980c8(EEContext&);  // generated body
void fn_sub_5980C8_005980c8__recomp(EEContext&);  // recompiled
void fn_sub_5982A0_005982a0(EEContext&);  // generated body
void fn_sub_5982A0_005982a0__recomp(EEContext&);  // recompiled
void fn_sub_5982E0_005982e0(EEContext&);  // generated body
void fn_sub_5982E0_005982e0__recomp(EEContext&);  // recompiled
void fn_sub_598640_00598640(EEContext&);  // generated body
void fn_sub_598640_00598640__recomp(EEContext&);  // recompiled
void fn_sub_599810_00599810(EEContext&);  // generated body
void fn_sub_599810_00599810__recomp(EEContext&);  // recompiled
void fn_sub_59A028_0059a028(EEContext&);  // generated body
void fn_sub_59A028_0059a028__recomp(EEContext&);  // recompiled
void fn_sub_59A910_0059a910(EEContext&);  // generated body
void fn_sub_59A910_0059a910__recomp(EEContext&);  // recompiled
void fn_sub_59A9D8_0059a9d8(EEContext&);  // generated body
void fn_sub_59A9D8_0059a9d8__recomp(EEContext&);  // recompiled
void fn_sub_59AD80_0059ad80(EEContext&);  // generated body
void fn_sub_59AD80_0059ad80__recomp(EEContext&);  // recompiled
void fn_sub_59AE88_0059ae88(EEContext&);  // generated body
void fn_sub_59AE88_0059ae88__recomp(EEContext&);  // recompiled
void fn_sub_59AEC0_0059aec0(EEContext&);  // generated body
void fn_sub_59AEC0_0059aec0__recomp(EEContext&);  // recompiled
void fn_sub_59B048_0059b048(EEContext&);  // generated body
void fn_sub_59B048_0059b048__recomp(EEContext&);  // recompiled
void fn_sub_59B210_0059b210(EEContext&);  // generated body
void fn_sub_59B210_0059b210__recomp(EEContext&);  // recompiled
void fn_sub_59B3A8_0059b3a8(EEContext&);  // generated body
void fn_sub_59B3A8_0059b3a8__recomp(EEContext&);  // recompiled
void fn_sub_59B620_0059b620(EEContext&);  // generated body
void fn_sub_59B620_0059b620__recomp(EEContext&);  // recompiled
void fn_sub_59B6D8_0059b6d8(EEContext&);  // generated body
void fn_sub_59B6D8_0059b6d8__recomp(EEContext&);  // recompiled
void fn_sub_59B720_0059b720(EEContext&);  // generated body
void fn_sub_59B720_0059b720__recomp(EEContext&);  // recompiled
void fn_sub_59B840_0059b840(EEContext&);  // generated body
void fn_sub_59B840_0059b840__recomp(EEContext&);  // recompiled
void fn_sub_59B930_0059b930(EEContext&);  // generated body
void fn_sub_59B930_0059b930__recomp(EEContext&);  // recompiled
void fn_sub_59B9D0_0059b9d0(EEContext&);  // generated body
void fn_sub_59B9D0_0059b9d0__recomp(EEContext&);  // recompiled
void fn_sub_59BA70_0059ba70(EEContext&);  // generated body
void fn_sub_59BA70_0059ba70__recomp(EEContext&);  // recompiled
void fn_sub_59BA90_0059ba90(EEContext&);  // generated body
void fn_sub_59BA90_0059ba90__recomp(EEContext&);  // recompiled
void fn_sub_59BAB0_0059bab0(EEContext&);  // generated body
void fn_sub_59BAB0_0059bab0__recomp(EEContext&);  // recompiled
void fn_sub_59BAD0_0059bad0(EEContext&);  // generated body
void fn_sub_59BAD0_0059bad0__recomp(EEContext&);  // recompiled
void fn_sub_59BB50_0059bb50(EEContext&);  // generated body
void fn_sub_59BB50_0059bb50__recomp(EEContext&);  // recompiled
void fn_sub_59C358_0059c358(EEContext&);  // generated body
void fn_sub_59C358_0059c358__recomp(EEContext&);  // recompiled
void fn_sub_59C418_0059c418(EEContext&);  // generated body
void fn_sub_59C418_0059c418__recomp(EEContext&);  // recompiled
void fn_sub_59C480_0059c480(EEContext&);  // generated body
void fn_sub_59C480_0059c480__recomp(EEContext&);  // recompiled
void fn_sub_59C5E0_0059c5e0(EEContext&);  // generated body
void fn_sub_59C5E0_0059c5e0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_590008", 0x590008, &recomp_gen::fn_sub_590008_00590008, &recomp_gen::fn_sub_590008_00590008__recomp},
    {"sub_590360", 0x590360, &recomp_gen::fn_sub_590360_00590360, &recomp_gen::fn_sub_590360_00590360__recomp},
    {"sub_590408", 0x590408, &recomp_gen::fn_sub_590408_00590408, &recomp_gen::fn_sub_590408_00590408__recomp},
    {"sub_5905F0", 0x5905F0, &recomp_gen::fn_sub_5905F0_005905f0, &recomp_gen::fn_sub_5905F0_005905f0__recomp},
    {"sub_590948", 0x590948, &recomp_gen::fn_sub_590948_00590948, &recomp_gen::fn_sub_590948_00590948__recomp},
    {"sub_590AE8", 0x590AE8, &recomp_gen::fn_sub_590AE8_00590ae8, &recomp_gen::fn_sub_590AE8_00590ae8__recomp},
    {"sub_590DF8", 0x590DF8, &recomp_gen::fn_sub_590DF8_00590df8, &recomp_gen::fn_sub_590DF8_00590df8__recomp},
    {"sub_590EF0", 0x590EF0, &recomp_gen::fn_sub_590EF0_00590ef0, &recomp_gen::fn_sub_590EF0_00590ef0__recomp},
    {"sub_590FD0", 0x590FD0, &recomp_gen::fn_sub_590FD0_00590fd0, &recomp_gen::fn_sub_590FD0_00590fd0__recomp},
    {"sub_591118", 0x591118, &recomp_gen::fn_sub_591118_00591118, &recomp_gen::fn_sub_591118_00591118__recomp},
    {"sub_591168", 0x591168, &recomp_gen::fn_sub_591168_00591168, &recomp_gen::fn_sub_591168_00591168__recomp},
    {"sub_591298", 0x591298, &recomp_gen::fn_sub_591298_00591298, &recomp_gen::fn_sub_591298_00591298__recomp},
    {"sub_5913B8", 0x5913B8, &recomp_gen::fn_sub_5913B8_005913b8, &recomp_gen::fn_sub_5913B8_005913b8__recomp},
    {"sub_5913F0", 0x5913F0, &recomp_gen::fn_sub_5913F0_005913f0, &recomp_gen::fn_sub_5913F0_005913f0__recomp},
    {"sub_5915A8", 0x5915A8, &recomp_gen::fn_sub_5915A8_005915a8, &recomp_gen::fn_sub_5915A8_005915a8__recomp},
    {"sub_5916A0", 0x5916A0, &recomp_gen::fn_sub_5916A0_005916a0, &recomp_gen::fn_sub_5916A0_005916a0__recomp},
    {"sub_591858", 0x591858, &recomp_gen::fn_sub_591858_00591858, &recomp_gen::fn_sub_591858_00591858__recomp},
    {"sub_591C80", 0x591C80, &recomp_gen::fn_sub_591C80_00591c80, &recomp_gen::fn_sub_591C80_00591c80__recomp},
    {"sub_591F38", 0x591F38, &recomp_gen::fn_sub_591F38_00591f38, &recomp_gen::fn_sub_591F38_00591f38__recomp},
    {"sub_592240", 0x592240, &recomp_gen::fn_sub_592240_00592240, &recomp_gen::fn_sub_592240_00592240__recomp},
    {"sub_5922C8", 0x5922C8, &recomp_gen::fn_sub_5922C8_005922c8, &recomp_gen::fn_sub_5922C8_005922c8__recomp},
    {"sub_592570", 0x592570, &recomp_gen::fn_sub_592570_00592570, &recomp_gen::fn_sub_592570_00592570__recomp},
    {"sub_592618", 0x592618, &recomp_gen::fn_sub_592618_00592618, &recomp_gen::fn_sub_592618_00592618__recomp},
    {"sub_592790", 0x592790, &recomp_gen::fn_sub_592790_00592790, &recomp_gen::fn_sub_592790_00592790__recomp},
    {"sub_592958", 0x592958, &recomp_gen::fn_sub_592958_00592958, &recomp_gen::fn_sub_592958_00592958__recomp},
    {"sub_5929B0", 0x5929B0, &recomp_gen::fn_sub_5929B0_005929b0, &recomp_gen::fn_sub_5929B0_005929b0__recomp},
    {"sub_592B10", 0x592B10, &recomp_gen::fn_sub_592B10_00592b10, &recomp_gen::fn_sub_592B10_00592b10__recomp},
    {"sub_592D08", 0x592D08, &recomp_gen::fn_sub_592D08_00592d08, &recomp_gen::fn_sub_592D08_00592d08__recomp},
    {"sub_592DD0", 0x592DD0, &recomp_gen::fn_sub_592DD0_00592dd0, &recomp_gen::fn_sub_592DD0_00592dd0__recomp},
    {"sub_592E80", 0x592E80, &recomp_gen::fn_sub_592E80_00592e80, &recomp_gen::fn_sub_592E80_00592e80__recomp},
    {"sub_592EA0", 0x592EA0, &recomp_gen::fn_sub_592EA0_00592ea0, &recomp_gen::fn_sub_592EA0_00592ea0__recomp},
    {"sub_592F38", 0x592F38, &recomp_gen::fn_sub_592F38_00592f38, &recomp_gen::fn_sub_592F38_00592f38__recomp},
    {"sub_5930C8", 0x5930C8, &recomp_gen::fn_sub_5930C8_005930c8, &recomp_gen::fn_sub_5930C8_005930c8__recomp},
    {"sub_593200", 0x593200, &recomp_gen::fn_sub_593200_00593200, &recomp_gen::fn_sub_593200_00593200__recomp},
    {"sub_593468", 0x593468, &recomp_gen::fn_sub_593468_00593468, &recomp_gen::fn_sub_593468_00593468__recomp},
    {"sub_593590", 0x593590, &recomp_gen::fn_sub_593590_00593590, &recomp_gen::fn_sub_593590_00593590__recomp},
    {"sub_593700", 0x593700, &recomp_gen::fn_sub_593700_00593700, &recomp_gen::fn_sub_593700_00593700__recomp},
    {"sub_593878", 0x593878, &recomp_gen::fn_sub_593878_00593878, &recomp_gen::fn_sub_593878_00593878__recomp},
    {"sub_593900", 0x593900, &recomp_gen::fn_sub_593900_00593900, &recomp_gen::fn_sub_593900_00593900__recomp},
    {"sub_593958", 0x593958, &recomp_gen::fn_sub_593958_00593958, &recomp_gen::fn_sub_593958_00593958__recomp},
    {"sub_593968", 0x593968, &recomp_gen::fn_sub_593968_00593968, &recomp_gen::fn_sub_593968_00593968__recomp},
    {"sub_593978", 0x593978, &recomp_gen::fn_sub_593978_00593978, &recomp_gen::fn_sub_593978_00593978__recomp},
    {"sub_593A18", 0x593A18, &recomp_gen::fn_sub_593A18_00593a18, &recomp_gen::fn_sub_593A18_00593a18__recomp},
    {"sub_593AB0", 0x593AB0, &recomp_gen::fn_sub_593AB0_00593ab0, &recomp_gen::fn_sub_593AB0_00593ab0__recomp},
    {"sub_593AE0", 0x593AE0, &recomp_gen::fn_sub_593AE0_00593ae0, &recomp_gen::fn_sub_593AE0_00593ae0__recomp},
    {"sub_593B38", 0x593B38, &recomp_gen::fn_sub_593B38_00593b38, &recomp_gen::fn_sub_593B38_00593b38__recomp},
    {"sub_593DB0", 0x593DB0, &recomp_gen::fn_sub_593DB0_00593db0, &recomp_gen::fn_sub_593DB0_00593db0__recomp},
    {"sub_593E08", 0x593E08, &recomp_gen::fn_sub_593E08_00593e08, &recomp_gen::fn_sub_593E08_00593e08__recomp},
    {"sub_593EA0", 0x593EA0, &recomp_gen::fn_sub_593EA0_00593ea0, &recomp_gen::fn_sub_593EA0_00593ea0__recomp},
    {"sub_593FB0", 0x593FB0, &recomp_gen::fn_sub_593FB0_00593fb0, &recomp_gen::fn_sub_593FB0_00593fb0__recomp},
    {"sub_593FE8", 0x593FE8, &recomp_gen::fn_sub_593FE8_00593fe8, &recomp_gen::fn_sub_593FE8_00593fe8__recomp},
    {"sub_594108", 0x594108, &recomp_gen::fn_sub_594108_00594108, &recomp_gen::fn_sub_594108_00594108__recomp},
    {"viBufCreate", 0x594130, &recomp_gen::fn_viBufCreate_00594130, &recomp_gen::fn_viBufCreate_00594130__recomp},
    {"sub_5942E8", 0x5942E8, &recomp_gen::fn_sub_5942E8_005942e8, &recomp_gen::fn_sub_5942E8_005942e8__recomp},
    {"sub_5943D8", 0x5943D8, &recomp_gen::fn_sub_5943D8_005943d8, &recomp_gen::fn_sub_5943D8_005943d8__recomp},
    {"sub_594428", 0x594428, &recomp_gen::fn_sub_594428_00594428, &recomp_gen::fn_sub_594428_00594428__recomp},
    {"sub_594B68", 0x594B68, &recomp_gen::fn_sub_594B68_00594b68, &recomp_gen::fn_sub_594B68_00594b68__recomp},
    {"sub_594B78", 0x594B78, &recomp_gen::fn_sub_594B78_00594b78, &recomp_gen::fn_sub_594B78_00594b78__recomp},
    {"sub_594B88", 0x594B88, &recomp_gen::fn_sub_594B88_00594b88, &recomp_gen::fn_sub_594B88_00594b88__recomp},
    {"sub_594C38", 0x594C38, &recomp_gen::fn_sub_594C38_00594c38, &recomp_gen::fn_sub_594C38_00594c38__recomp},
    {"sub_594EC8", 0x594EC8, &recomp_gen::fn_sub_594EC8_00594ec8, &recomp_gen::fn_sub_594EC8_00594ec8__recomp},
    {"sub_595010", 0x595010, &recomp_gen::fn_sub_595010_00595010, &recomp_gen::fn_sub_595010_00595010__recomp},
    {"sub_595038", 0x595038, &recomp_gen::fn_sub_595038_00595038, &recomp_gen::fn_sub_595038_00595038__recomp},
    {"sub_595060", 0x595060, &recomp_gen::fn_sub_595060_00595060, &recomp_gen::fn_sub_595060_00595060__recomp},
    {"sub_595110", 0x595110, &recomp_gen::fn_sub_595110_00595110, &recomp_gen::fn_sub_595110_00595110__recomp},
    {"sub_595138", 0x595138, &recomp_gen::fn_sub_595138_00595138, &recomp_gen::fn_sub_595138_00595138__recomp},
    {"sub_5951A8", 0x5951A8, &recomp_gen::fn_sub_5951A8_005951a8, &recomp_gen::fn_sub_5951A8_005951a8__recomp},
    {"sub_595260", 0x595260, &recomp_gen::fn_sub_595260_00595260, &recomp_gen::fn_sub_595260_00595260__recomp},
    {"sub_595390", 0x595390, &recomp_gen::fn_sub_595390_00595390, &recomp_gen::fn_sub_595390_00595390__recomp},
    {"sub_5954D8", 0x5954D8, &recomp_gen::fn_sub_5954D8_005954d8, &recomp_gen::fn_sub_5954D8_005954d8__recomp},
    {"sub_5954E8", 0x5954E8, &recomp_gen::fn_sub_5954E8_005954e8, &recomp_gen::fn_sub_5954E8_005954e8__recomp},
    {"sub_595700", 0x595700, &recomp_gen::fn_sub_595700_00595700, &recomp_gen::fn_sub_595700_00595700__recomp},
    {"sub_595718", 0x595718, &recomp_gen::fn_sub_595718_00595718, &recomp_gen::fn_sub_595718_00595718__recomp},
    {"sub_5959D0", 0x5959D0, &recomp_gen::fn_sub_5959D0_005959d0, &recomp_gen::fn_sub_5959D0_005959d0__recomp},
    {"sub_595B30", 0x595B30, &recomp_gen::fn_sub_595B30_00595b30, &recomp_gen::fn_sub_595B30_00595b30__recomp},
    {"sub_595B58", 0x595B58, &recomp_gen::fn_sub_595B58_00595b58, &recomp_gen::fn_sub_595B58_00595b58__recomp},
    {"sub_595D10", 0x595D10, &recomp_gen::fn_sub_595D10_00595d10, &recomp_gen::fn_sub_595D10_00595d10__recomp},
    {"sub_595E28", 0x595E28, &recomp_gen::fn_sub_595E28_00595e28, &recomp_gen::fn_sub_595E28_00595e28__recomp},
    {"sub_595E50", 0x595E50, &recomp_gen::fn_sub_595E50_00595e50, &recomp_gen::fn_sub_595E50_00595e50__recomp},
    {"sub_595E68", 0x595E68, &recomp_gen::fn_sub_595E68_00595e68, &recomp_gen::fn_sub_595E68_00595e68__recomp},
    {"sub_595E98", 0x595E98, &recomp_gen::fn_sub_595E98_00595e98, &recomp_gen::fn_sub_595E98_00595e98__recomp},
    {"sub_595F58", 0x595F58, &recomp_gen::fn_sub_595F58_00595f58, &recomp_gen::fn_sub_595F58_00595f58__recomp},
    {"sub_596008", 0x596008, &recomp_gen::fn_sub_596008_00596008, &recomp_gen::fn_sub_596008_00596008__recomp},
    {"sub_596038", 0x596038, &recomp_gen::fn_sub_596038_00596038, &recomp_gen::fn_sub_596038_00596038__recomp},
    {"sub_5960E0", 0x5960E0, &recomp_gen::fn_sub_5960E0_005960e0, &recomp_gen::fn_sub_5960E0_005960e0__recomp},
    {"sub_596168", 0x596168, &recomp_gen::fn_sub_596168_00596168, &recomp_gen::fn_sub_596168_00596168__recomp},
    {"sub_596230", 0x596230, &recomp_gen::fn_sub_596230_00596230, &recomp_gen::fn_sub_596230_00596230__recomp},
    {"sub_5962D0", 0x5962D0, &recomp_gen::fn_sub_5962D0_005962d0, &recomp_gen::fn_sub_5962D0_005962d0__recomp},
    {"sub_596348", 0x596348, &recomp_gen::fn_sub_596348_00596348, &recomp_gen::fn_sub_596348_00596348__recomp},
    {"sub_5963B0", 0x5963B0, &recomp_gen::fn_sub_5963B0_005963b0, &recomp_gen::fn_sub_5963B0_005963b0__recomp},
    {"sub_596460", 0x596460, &recomp_gen::fn_sub_596460_00596460, &recomp_gen::fn_sub_596460_00596460__recomp},
    {"sub_5966C0", 0x5966C0, &recomp_gen::fn_sub_5966C0_005966c0, &recomp_gen::fn_sub_5966C0_005966c0__recomp},
    {"sub_596898", 0x596898, &recomp_gen::fn_sub_596898_00596898, &recomp_gen::fn_sub_596898_00596898__recomp},
    {"sub_596908", 0x596908, &recomp_gen::fn_sub_596908_00596908, &recomp_gen::fn_sub_596908_00596908__recomp},
    {"sub_596978", 0x596978, &recomp_gen::fn_sub_596978_00596978, &recomp_gen::fn_sub_596978_00596978__recomp},
    {"sub_596A40", 0x596A40, &recomp_gen::fn_sub_596A40_00596a40, &recomp_gen::fn_sub_596A40_00596a40__recomp},
    {"sub_596A98", 0x596A98, &recomp_gen::fn_sub_596A98_00596a98, &recomp_gen::fn_sub_596A98_00596a98__recomp},
    {"sub_596C28", 0x596C28, &recomp_gen::fn_sub_596C28_00596c28, &recomp_gen::fn_sub_596C28_00596c28__recomp},
    {"sub_596CC0", 0x596CC0, &recomp_gen::fn_sub_596CC0_00596cc0, &recomp_gen::fn_sub_596CC0_00596cc0__recomp},
    {"sub_596D28", 0x596D28, &recomp_gen::fn_sub_596D28_00596d28, &recomp_gen::fn_sub_596D28_00596d28__recomp},
    {"sub_596D68", 0x596D68, &recomp_gen::fn_sub_596D68_00596d68, &recomp_gen::fn_sub_596D68_00596d68__recomp},
    {"sub_596F98", 0x596F98, &recomp_gen::fn_sub_596F98_00596f98, &recomp_gen::fn_sub_596F98_00596f98__recomp},
    {"sub_597000", 0x597000, &recomp_gen::fn_sub_597000_00597000, &recomp_gen::fn_sub_597000_00597000__recomp},
    {"sub_597078", 0x597078, &recomp_gen::fn_sub_597078_00597078, &recomp_gen::fn_sub_597078_00597078__recomp},
    {"sub_597088", 0x597088, &recomp_gen::fn_sub_597088_00597088, &recomp_gen::fn_sub_597088_00597088__recomp},
    {"sub_597100", 0x597100, &recomp_gen::fn_sub_597100_00597100, &recomp_gen::fn_sub_597100_00597100__recomp},
    {"sub_5971D0", 0x5971D0, &recomp_gen::fn_sub_5971D0_005971d0, &recomp_gen::fn_sub_5971D0_005971d0__recomp},
    {"sub_5971E8", 0x5971E8, &recomp_gen::fn_sub_5971E8_005971e8, &recomp_gen::fn_sub_5971E8_005971e8__recomp},
    {"sub_597288", 0x597288, &recomp_gen::fn_sub_597288_00597288, &recomp_gen::fn_sub_597288_00597288__recomp},
    {"sub_597330", 0x597330, &recomp_gen::fn_sub_597330_00597330, &recomp_gen::fn_sub_597330_00597330__recomp},
    {"sub_597340", 0x597340, &recomp_gen::fn_sub_597340_00597340, &recomp_gen::fn_sub_597340_00597340__recomp},
    {"sub_5973C0", 0x5973C0, &recomp_gen::fn_sub_5973C0_005973c0, &recomp_gen::fn_sub_5973C0_005973c0__recomp},
    {"sceInsockSetErrnoMode_1", 0x597428, &recomp_gen::fn_sceInsockSetErrnoMode_1_00597428, &recomp_gen::fn_sceInsockSetErrnoMode_1_00597428__recomp},
    {"my_malloc_1", 0x597448, &recomp_gen::fn_my_malloc_1_00597448, &recomp_gen::fn_my_malloc_1_00597448__recomp},
    {"sub_5974A8", 0x5974A8, &recomp_gen::fn_sub_5974A8_005974a8, &recomp_gen::fn_sub_5974A8_005974a8__recomp},
    {"sub_597C28", 0x597C28, &recomp_gen::fn_sub_597C28_00597c28, &recomp_gen::fn_sub_597C28_00597c28__recomp},
    {"sub_597D20", 0x597D20, &recomp_gen::fn_sub_597D20_00597d20, &recomp_gen::fn_sub_597D20_00597d20__recomp},
    {"sub_597DC8", 0x597DC8, &recomp_gen::fn_sub_597DC8_00597dc8, &recomp_gen::fn_sub_597DC8_00597dc8__recomp},
    {"sub_597E20", 0x597E20, &recomp_gen::fn_sub_597E20_00597e20, &recomp_gen::fn_sub_597E20_00597e20__recomp},
    {"sub_597E80", 0x597E80, &recomp_gen::fn_sub_597E80_00597e80, &recomp_gen::fn_sub_597E80_00597e80__recomp},
    {"sub_597FA0", 0x597FA0, &recomp_gen::fn_sub_597FA0_00597fa0, &recomp_gen::fn_sub_597FA0_00597fa0__recomp},
    {"sub_5980C8", 0x5980C8, &recomp_gen::fn_sub_5980C8_005980c8, &recomp_gen::fn_sub_5980C8_005980c8__recomp},
    {"sub_5982A0", 0x5982A0, &recomp_gen::fn_sub_5982A0_005982a0, &recomp_gen::fn_sub_5982A0_005982a0__recomp},
    {"sub_5982E0", 0x5982E0, &recomp_gen::fn_sub_5982E0_005982e0, &recomp_gen::fn_sub_5982E0_005982e0__recomp},
    {"sub_598640", 0x598640, &recomp_gen::fn_sub_598640_00598640, &recomp_gen::fn_sub_598640_00598640__recomp},
    {"sub_599810", 0x599810, &recomp_gen::fn_sub_599810_00599810, &recomp_gen::fn_sub_599810_00599810__recomp},
    {"sub_59A028", 0x59A028, &recomp_gen::fn_sub_59A028_0059a028, &recomp_gen::fn_sub_59A028_0059a028__recomp},
    {"sub_59A910", 0x59A910, &recomp_gen::fn_sub_59A910_0059a910, &recomp_gen::fn_sub_59A910_0059a910__recomp},
    {"sub_59A9D8", 0x59A9D8, &recomp_gen::fn_sub_59A9D8_0059a9d8, &recomp_gen::fn_sub_59A9D8_0059a9d8__recomp},
    {"sub_59AD80", 0x59AD80, &recomp_gen::fn_sub_59AD80_0059ad80, &recomp_gen::fn_sub_59AD80_0059ad80__recomp},
    {"sub_59AE88", 0x59AE88, &recomp_gen::fn_sub_59AE88_0059ae88, &recomp_gen::fn_sub_59AE88_0059ae88__recomp},
    {"sub_59AEC0", 0x59AEC0, &recomp_gen::fn_sub_59AEC0_0059aec0, &recomp_gen::fn_sub_59AEC0_0059aec0__recomp},
    {"sub_59B048", 0x59B048, &recomp_gen::fn_sub_59B048_0059b048, &recomp_gen::fn_sub_59B048_0059b048__recomp},
    {"sub_59B210", 0x59B210, &recomp_gen::fn_sub_59B210_0059b210, &recomp_gen::fn_sub_59B210_0059b210__recomp},
    {"sub_59B3A8", 0x59B3A8, &recomp_gen::fn_sub_59B3A8_0059b3a8, &recomp_gen::fn_sub_59B3A8_0059b3a8__recomp},
    {"sub_59B620", 0x59B620, &recomp_gen::fn_sub_59B620_0059b620, &recomp_gen::fn_sub_59B620_0059b620__recomp},
    {"sub_59B6D8", 0x59B6D8, &recomp_gen::fn_sub_59B6D8_0059b6d8, &recomp_gen::fn_sub_59B6D8_0059b6d8__recomp},
    {"sub_59B720", 0x59B720, &recomp_gen::fn_sub_59B720_0059b720, &recomp_gen::fn_sub_59B720_0059b720__recomp},
    {"sub_59B840", 0x59B840, &recomp_gen::fn_sub_59B840_0059b840, &recomp_gen::fn_sub_59B840_0059b840__recomp},
    {"sub_59B930", 0x59B930, &recomp_gen::fn_sub_59B930_0059b930, &recomp_gen::fn_sub_59B930_0059b930__recomp},
    {"sub_59B9D0", 0x59B9D0, &recomp_gen::fn_sub_59B9D0_0059b9d0, &recomp_gen::fn_sub_59B9D0_0059b9d0__recomp},
    {"sub_59BA70", 0x59BA70, &recomp_gen::fn_sub_59BA70_0059ba70, &recomp_gen::fn_sub_59BA70_0059ba70__recomp},
    {"sub_59BA90", 0x59BA90, &recomp_gen::fn_sub_59BA90_0059ba90, &recomp_gen::fn_sub_59BA90_0059ba90__recomp},
    {"sub_59BAB0", 0x59BAB0, &recomp_gen::fn_sub_59BAB0_0059bab0, &recomp_gen::fn_sub_59BAB0_0059bab0__recomp},
    {"sub_59BAD0", 0x59BAD0, &recomp_gen::fn_sub_59BAD0_0059bad0, &recomp_gen::fn_sub_59BAD0_0059bad0__recomp},
    {"sub_59BB50", 0x59BB50, &recomp_gen::fn_sub_59BB50_0059bb50, &recomp_gen::fn_sub_59BB50_0059bb50__recomp},
    {"sub_59C358", 0x59C358, &recomp_gen::fn_sub_59C358_0059c358, &recomp_gen::fn_sub_59C358_0059c358__recomp},
    {"sub_59C418", 0x59C418, &recomp_gen::fn_sub_59C418_0059c418, &recomp_gen::fn_sub_59C418_0059c418__recomp},
    {"sub_59C480", 0x59C480, &recomp_gen::fn_sub_59C480_0059c480, &recomp_gen::fn_sub_59C480_0059c480__recomp},
    {"sub_59C5E0", 0x59C5E0, &recomp_gen::fn_sub_59C5E0_0059c5e0, &recomp_gen::fn_sub_59C5E0_0059c5e0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs13): every body equals its recompiled body on random worlds") {
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

namespace {

namespace L = p3fes::game::libs13;

// An SFD handle world (game/include/p3fes/game/libs13.h): the handle at kHandle, its video-decoder work at
// handle + sfd::kVdecArea (what sub_5929B0 installs at +sfd::kVdecWork), up to 16 frame records with real states,
// times and shown marks, the reference / pending frame pointers, the header object, the IPU switch and the video-input
// ring; every other word is drawn from the values the bodies compare against (statuses, requests, param values, the
// variable-rate marker, the frame rates) or is a pointer into the world.
constexpr u32 kHandle = 0x01820000u;
constexpr u32 kHandleSpan = 0x10000u;
constexpr u32 kWork = kHandle + L::sfd::kVdecArea;
constexpr u32 kHdr = kHandle + 0xE000u;  // the header object (beyond the handle's 0x37D0 bytes)

u32 enum_word(std::mt19937& rng) {
    static const u32 kValues[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 15u, 16u, 0xFFFFFFFFu, 0xFFFFFFFEu, 0xFFFFFFFDu,
                                  0xFFFFFFFCu, 0xFFFFFFFBu, 0x3FFFFu, 63u, 64u, 512u, 1000u, 29970u, 59940u, 0x7FFFFFFFu};
    const u32 k = rng() % 8;
    if (k < 5) return kValues[rng() % (sizeof kValues / sizeof kValues[0])];
    if (k < 7) return kHandle + ((rng() % kHandleSpan) & ~3u);
    return rng() % 0x10000u;
}

void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

void sfd_world(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= kHandleSpan; i += 4) w32(m, kHandle + i, enum_word(rng));
    w32(m, kHandle + L::sfd::kStat, rng() % 7);
    w32(m, kHandle + L::sfd::kReq, rng() % 7);
    w32(m, kHandle + L::sfd::kVdecWork, kWork);
    w32(m, kHandle + L::sfd::kHdrObj, rng() % 3 == 0 ? 0u : kHdr);
    w32(m, kHandle + 56, 2 + rng() % 2);  // the picture format (2 or 3)
    const u32 frames = rng() % 17;
    w32(m, kWork + L::vdec::kFrameCount, frames);
    for (u32 i = 0; i < 16; ++i) {
        const u32 f = kWork + L::vdec::kFrames + L::frm::kSize * i;
        w32(m, f + L::frm::kState, rng() % 5);
        w32(m, f + L::frm::kTime, rng() % 8);
        w32(m, f + L::frm::kShown, rng() % 2 ? 0xFFFFFFFFu : rng() % 4);
    }
    const auto frame_ptr = [&] { return rng() % 3 == 0 ? 0u : kWork + L::vdec::kFrames + L::frm::kSize * (rng() % 16); };
    w32(m, kWork + L::vdec::kPrevRef, frame_ptr());
    w32(m, kWork + L::vdec::kNextRef, frame_ptr());
    w32(m, kWork + L::vdec::kPending, frame_ptr());
    w32(m, kWork + L::vdec::kIpu, rng() % 2);
    w32(m, kWork + L::vdec::kIpuPending, rng() % 5);
}

// Recorders for the callees this build does not emit and the bodies meet first (no other current packet takes them):
// the SFD lock / unlock, the kernel semaphores, libmpeg (sceMpeg*), the video-input ring's DMA functions (hardware
// registers). Each logs the call and returns $v0; both bodies of a pair get a fresh set and
// the two call logs must be equal.
struct Rec {
    u32 va;
    const char* name;
    u64 v0;
};
const Rec kRecorders[] = {
    {0x58C100u, "sub_58C100 (lock)", 0},    {0x58C118u, "sub_58C118 (unlock)", 0},
    {0x503160u, "_sceCreateSema", 5},       {0x503180u, "_sceSignalSema", 0},
    {0x5031A0u, "_sceWaitSema", 0},         {0x500A20u, "sceMpegInit", 0},
    {0x4FFE78u, "sceMpegCreate", 0},        {0x500C90u, "sceMpegAddCallback", 0},
    {0x500AD0u, "sceMpegDelete", 0},        {0x500BB8u, "sceMpegReset", 0},
    {0x500B18u, "sceMpegGetPicture", 0},    {0x500B60u, "sceMpegGetPictureRAW8", 0},
    {0x5941A8u, "sub_5941A8 (ring DMA)", 0}, {0x5944A8u, "sub_5944A8 (ring DMA)", 0},
    {0x5946A8u, "sub_5946A8 (ring DMA)", 0}, {0x5947A8u, "sub_5947A8 (ring DMA)", 0},
    {0x594AC0u, "sub_594AC0 (ring DMA)", 0},
};
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
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        w->si.clobber_scratch = true;
        for (const Rec& r : kRecorders) w->si.install_recorder(r.va, r.name, r.v0, 3);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

u64 sfd_arg(std::mt19937& rng) {
    const u32 k = rng() % 8;
    if (k < 4) return sx(kHandle);
    if (k < 5) return sx(kWork + L::vdec::kFrames + L::frm::kSize * (rng() % 16));
    if (k < 6) return sx(kHandle + ((rng() % kHandleSpan) & ~15u));
    return sx(enum_word(rng));
}

void run_sfd_worlds(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            sfd_world(m, rng);
            const Args args{sfd_arg(rng), sfd_arg(rng), sfd_arg(rng), sfd_arg(rng)};
            stops += spair(m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

TEST_CASE("game(libs13): every body equals its recompiled body on SFD handle worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    run_sfd_worlds(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 32u, "sfd world");
}

// The same worlds over the RAM of the replay snapshots (real globals: the handle table 0x7B4774, the IPU switch
// 0x7B47A8, the saved decoder configuration 0x9ACAF0.., the clock words); and, where a snapshot holds an open SFD
// handle, every body on that handle as it is.
TEST_CASE("game(libs13): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"};
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_sfd_worlds(*m, 4u, dir);
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        std::vector<u32> handles;  // the open-handle table 0x7B4774[8] and the last checked handle 0x7B4568
        for (u32 i = 0; i <= 8; ++i) {
            u32 h = 0;
            std::memcpy(&h, snap.data() + (i < 8 ? 0x7B4774u + 4 * i : 0x7B4568u), 4);
            if (h != 0 && h < 0x01FF0000u && std::find(handles.begin(), handles.end(), h) == handles.end()) handles.push_back(h);
        }
        for (const u32 h : handles) {
            for (const Case& c : kCases) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());  // the live handle as the snapshot holds it
                for (u32 seed = 1; seed <= 4; ++seed) {
                    std::mt19937 rng{seed + c.addr};
                    const Args args{sx(h), rng() % 8, rng() % 8, rng() % 8};
                    spair(*m, c.hand, c.recomp, args, seed, c.name);
                }
            }
            const std::string note = std::string(dir) + ": open SFD handle " + hex64(h) + ", " + std::to_string((sizeof kCases / sizeof kCases[0]) * 4) + " pairs";
            MESSAGE(note);
        }
    }
}

// Documented rules on the host, from the instructions (both bodies run, compared, then the result checked).
TEST_CASE("game(libs13): time code, frame order, ring average and DMA tag rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto find = [](const char* name) -> const Case& {
        for (const Case& c : kCases)
            if (std::string(c.name) == name) return c;
        return kCases[0];
    };
    const u32 base = kHandle;
    // sub_59A910: (h * 3600 + m * 60 + s) * rate + 1000 * (f + extra) + 500 * field, the unit word = rate.
    {
        const u32 tc = base + 0x100, out = base + 0x200, unit = base + 0x204;
        w32(*m, tc + 8, 1);
        w32(*m, tc + 12, 2);
        w32(*m, tc + 16, 3);
        w32(*m, tc + 20, 4);
        w32(*m, tc + 24, 5);
        const s16 field = 1;
        std::memcpy(m->at(tc + 30), &field, 2);
        const Case& c = find("sub_59A910");
        hgp::pair(*m, c.hand, c.recomp, Args{30000, sx(tc), sx(out), sx(unit)}, 1, c.name);
        u32 got = 0, u = 0;
        std::memcpy(&got, m->at(out), 4);
        std::memcpy(&u, m->at(unit), 4);
        CHECK(got == (1u * 3600 + 2u * 60 + 3u) * 30000u + 1000u * (4u + 5u) + 500u);
        CHECK(u == 30000u);
    }
    // sub_593FB0: a null frame a -> 1; otherwise b is older than a (time at frm::kTime).
    {
        const u32 a = base + 0x300, b = base + 0x400;
        const Case& c = find("sub_593FB0");
        w32(*m, a + L::frm::kTime, 10);
        w32(*m, b + L::frm::kTime, 7);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{0, sx(b), 0, 0}, 1, c.name).end.gpr[2].u64[0] == 1u);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{sx(a), sx(b), 0, 0}, 2, c.name).end.gpr[2].u64[0] == 1u);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{sx(b), sx(a), 0, 0}, 3, c.name).end.gpr[2].u64[0] == 0u);
    }
    // sub_59C418: the average of the record's n samples (count at +16, samples from +24).
    {
        const u32 r = base + 0x500;
        w32(*m, r + 16, 4);
        const u32 samples[] = {10, 20, 30, 41};
        for (u32 i = 0; i < 4; ++i) w32(*m, r + 24 + 4 * i, samples[i]);
        const Case& c = find("sub_59C418");
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{sx(r), 0, 0, 0}, 1, c.name).end.gpr[2].u64[0] == 25u);
    }
    // sub_594108: a DMA tag (addr << 32) | (id << 28) | qwc stored as one 64-bit word.
    {
        const u32 t = base + 0x600;
        const Case& c = find("sub_594108");
        hgp::pair(*m, c.hand, c.recomp, Args{sx(t), 0x00123450u, 3, 0x40}, 1, c.name);
        u64 tag = 0;
        std::memcpy(&tag, m->at(t), 8);
        CHECK(tag == ((u64{0x00123450u} << 32) | (u64{3} << 28) | 0x40u));
    }
}

#else

TEST_CASE("game(libs13): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
