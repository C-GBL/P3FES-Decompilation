// Pair tests for slice libs10 (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log.
// TODO(libs10): give each function meaningful inputs -- its real structures (world layouts, real game data from
// the extracted tree, snapshots), the edge cases its branches test, the callees it needs emitted (the _callees list
// of tests/game/CMakeLists.txt; without them the runs stop, identically, at the first call) -- and a few documented-rule
// checks on the host.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs10.h"

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

namespace p3fes::recomp_gen {
void fn_sub_550048_00550048(EEContext&);  // generated body
void fn_sub_550048_00550048__recomp(EEContext&);  // recompiled
void fn_sub_550238_00550238(EEContext&);  // generated body
void fn_sub_550238_00550238__recomp(EEContext&);  // recompiled
void fn_sub_550428_00550428(EEContext&);  // generated body
void fn_sub_550428_00550428__recomp(EEContext&);  // recompiled
void fn_sub_550618_00550618(EEContext&);  // generated body
void fn_sub_550618_00550618__recomp(EEContext&);  // recompiled
void fn_sub_5513A8_005513a8(EEContext&);  // generated body
void fn_sub_5513A8_005513a8__recomp(EEContext&);  // recompiled
void fn_sub_551598_00551598(EEContext&);  // generated body
void fn_sub_551598_00551598__recomp(EEContext&);  // recompiled
void fn_sub_551788_00551788(EEContext&);  // generated body
void fn_sub_551788_00551788__recomp(EEContext&);  // recompiled
void fn_sub_551978_00551978(EEContext&);  // generated body
void fn_sub_551978_00551978__recomp(EEContext&);  // recompiled
void fn_sub_551990_00551990(EEContext&);  // generated body
void fn_sub_551990_00551990__recomp(EEContext&);  // recompiled
void fn_sub_5519E8_005519e8(EEContext&);  // generated body
void fn_sub_5519E8_005519e8__recomp(EEContext&);  // recompiled
void fn_sub_551A88_00551a88(EEContext&);  // generated body
void fn_sub_551A88_00551a88__recomp(EEContext&);  // recompiled
void fn_sub_551AD8_00551ad8(EEContext&);  // generated body
void fn_sub_551AD8_00551ad8__recomp(EEContext&);  // recompiled
void fn_sub_551BB0_00551bb0(EEContext&);  // generated body
void fn_sub_551BB0_00551bb0__recomp(EEContext&);  // recompiled
void fn_sub_551BF0_00551bf0(EEContext&);  // generated body
void fn_sub_551BF0_00551bf0__recomp(EEContext&);  // recompiled
void fn_sub_551D38_00551d38(EEContext&);  // generated body
void fn_sub_551D38_00551d38__recomp(EEContext&);  // recompiled
void fn_sub_551DA0_00551da0(EEContext&);  // generated body
void fn_sub_551DA0_00551da0__recomp(EEContext&);  // recompiled
void fn_sub_551DF8_00551df8(EEContext&);  // generated body
void fn_sub_551DF8_00551df8__recomp(EEContext&);  // recompiled
void fn_sub_551E30_00551e30(EEContext&);  // generated body
void fn_sub_551E30_00551e30__recomp(EEContext&);  // recompiled
void fn_sub_551F80_00551f80(EEContext&);  // generated body
void fn_sub_551F80_00551f80__recomp(EEContext&);  // recompiled
void fn_sub_551FF8_00551ff8(EEContext&);  // generated body
void fn_sub_551FF8_00551ff8__recomp(EEContext&);  // recompiled
void fn_sub_552008_00552008(EEContext&);  // generated body
void fn_sub_552008_00552008__recomp(EEContext&);  // recompiled
void fn_sub_552028_00552028(EEContext&);  // generated body
void fn_sub_552028_00552028__recomp(EEContext&);  // recompiled
void fn_sub_552080_00552080(EEContext&);  // generated body
void fn_sub_552080_00552080__recomp(EEContext&);  // recompiled
void fn_sub_5520B0_005520b0(EEContext&);  // generated body
void fn_sub_5520B0_005520b0__recomp(EEContext&);  // recompiled
void fn_sub_552110_00552110(EEContext&);  // generated body
void fn_sub_552110_00552110__recomp(EEContext&);  // recompiled
void fn_sub_5523B8_005523b8(EEContext&);  // generated body
void fn_sub_5523B8_005523b8__recomp(EEContext&);  // recompiled
void fn_sub_552460_00552460(EEContext&);  // generated body
void fn_sub_552460_00552460__recomp(EEContext&);  // recompiled
void fn_sub_552468_00552468(EEContext&);  // generated body
void fn_sub_552468_00552468__recomp(EEContext&);  // recompiled
void fn_sub_552480_00552480(EEContext&);  // generated body
void fn_sub_552480_00552480__recomp(EEContext&);  // recompiled
void fn_sub_552508_00552508(EEContext&);  // generated body
void fn_sub_552508_00552508__recomp(EEContext&);  // recompiled
void fn_sub_552520_00552520(EEContext&);  // generated body
void fn_sub_552520_00552520__recomp(EEContext&);  // recompiled
void fn_sub_552600_00552600(EEContext&);  // generated body
void fn_sub_552600_00552600__recomp(EEContext&);  // recompiled
void fn_sub_552630_00552630(EEContext&);  // generated body
void fn_sub_552630_00552630__recomp(EEContext&);  // recompiled
void fn_sub_552930_00552930(EEContext&);  // generated body
void fn_sub_552930_00552930__recomp(EEContext&);  // recompiled
void fn_sub_552D68_00552d68(EEContext&);  // generated body
void fn_sub_552D68_00552d68__recomp(EEContext&);  // recompiled
void fn_sub_553288_00553288(EEContext&);  // generated body
void fn_sub_553288_00553288__recomp(EEContext&);  // recompiled
void fn_sub_5535D0_005535d0(EEContext&);  // generated body
void fn_sub_5535D0_005535d0__recomp(EEContext&);  // recompiled
void fn_sub_553838_00553838(EEContext&);  // generated body
void fn_sub_553838_00553838__recomp(EEContext&);  // recompiled
void fn_sub_553920_00553920(EEContext&);  // generated body
void fn_sub_553920_00553920__recomp(EEContext&);  // recompiled
void fn_sub_553A78_00553a78(EEContext&);  // generated body
void fn_sub_553A78_00553a78__recomp(EEContext&);  // recompiled
void fn_sub_553B70_00553b70(EEContext&);  // generated body
void fn_sub_553B70_00553b70__recomp(EEContext&);  // recompiled
void fn_sub_553BC0_00553bc0(EEContext&);  // generated body
void fn_sub_553BC0_00553bc0__recomp(EEContext&);  // recompiled
void fn_sub_553FA8_00553fa8(EEContext&);  // generated body
void fn_sub_553FA8_00553fa8__recomp(EEContext&);  // recompiled
void fn_sub_554048_00554048(EEContext&);  // generated body
void fn_sub_554048_00554048__recomp(EEContext&);  // recompiled
void fn_sub_5541D0_005541d0(EEContext&);  // generated body
void fn_sub_5541D0_005541d0__recomp(EEContext&);  // recompiled
void fn_sub_5542E8_005542e8(EEContext&);  // generated body
void fn_sub_5542E8_005542e8__recomp(EEContext&);  // recompiled
void fn_sub_554360_00554360(EEContext&);  // generated body
void fn_sub_554360_00554360__recomp(EEContext&);  // recompiled
void fn_sub_5543C8_005543c8(EEContext&);  // generated body
void fn_sub_5543C8_005543c8__recomp(EEContext&);  // recompiled
void fn_sub_554448_00554448(EEContext&);  // generated body
void fn_sub_554448_00554448__recomp(EEContext&);  // recompiled
void fn_sub_5544C8_005544c8(EEContext&);  // generated body
void fn_sub_5544C8_005544c8__recomp(EEContext&);  // recompiled
void fn_sub_554530_00554530(EEContext&);  // generated body
void fn_sub_554530_00554530__recomp(EEContext&);  // recompiled
void fn_sub_5546F0_005546f0(EEContext&);  // generated body
void fn_sub_5546F0_005546f0__recomp(EEContext&);  // recompiled
void fn_sub_554708_00554708(EEContext&);  // generated body
void fn_sub_554708_00554708__recomp(EEContext&);  // recompiled
void fn_sub_554720_00554720(EEContext&);  // generated body
void fn_sub_554720_00554720__recomp(EEContext&);  // recompiled
void fn_sub_554900_00554900(EEContext&);  // generated body
void fn_sub_554900_00554900__recomp(EEContext&);  // recompiled
void fn_sub_554908_00554908(EEContext&);  // generated body
void fn_sub_554908_00554908__recomp(EEContext&);  // recompiled
void fn_sub_554948_00554948(EEContext&);  // generated body
void fn_sub_554948_00554948__recomp(EEContext&);  // recompiled
void fn_sub_554958_00554958(EEContext&);  // generated body
void fn_sub_554958_00554958__recomp(EEContext&);  // recompiled
void fn_sub_554968_00554968(EEContext&);  // generated body
void fn_sub_554968_00554968__recomp(EEContext&);  // recompiled
void fn_sub_554990_00554990(EEContext&);  // generated body
void fn_sub_554990_00554990__recomp(EEContext&);  // recompiled
void fn_sub_5549C8_005549c8(EEContext&);  // generated body
void fn_sub_5549C8_005549c8__recomp(EEContext&);  // recompiled
void fn_sub_554A98_00554a98(EEContext&);  // generated body
void fn_sub_554A98_00554a98__recomp(EEContext&);  // recompiled
void fn_sub_554AE8_00554ae8(EEContext&);  // generated body
void fn_sub_554AE8_00554ae8__recomp(EEContext&);  // recompiled
void fn_sub_555570_00555570(EEContext&);  // generated body
void fn_sub_555570_00555570__recomp(EEContext&);  // recompiled
void fn_sub_5555A0_005555a0(EEContext&);  // generated body
void fn_sub_5555A0_005555a0__recomp(EEContext&);  // recompiled
void fn_sub_555658_00555658(EEContext&);  // generated body
void fn_sub_555658_00555658__recomp(EEContext&);  // recompiled
void fn_sub_555898_00555898(EEContext&);  // generated body
void fn_sub_555898_00555898__recomp(EEContext&);  // recompiled
void fn_SRD_Create_00557a58(EEContext&);  // generated body
void fn_SRD_Create_00557a58__recomp(EEContext&);  // recompiled
void fn_sub_557AE0_00557ae0(EEContext&);  // generated body
void fn_sub_557AE0_00557ae0__recomp(EEContext&);  // recompiled
void fn_sub_557D20_00557d20(EEContext&);  // generated body
void fn_sub_557D20_00557d20__recomp(EEContext&);  // recompiled
void fn_sub_557D28_00557d28(EEContext&);  // generated body
void fn_sub_557D28_00557d28__recomp(EEContext&);  // recompiled
void fn_sub_557D80_00557d80(EEContext&);  // generated body
void fn_sub_557D80_00557d80__recomp(EEContext&);  // recompiled
void fn_SRD_WaitComplete_00557e50(EEContext&);  // generated body
void fn_SRD_WaitComplete_00557e50__recomp(EEContext&);  // recompiled
void fn_sub_557F80_00557f80(EEContext&);  // generated body
void fn_sub_557F80_00557f80__recomp(EEContext&);  // recompiled
void fn_SRD_ExecServer_00558500(EEContext&);  // generated body
void fn_SRD_ExecServer_00558500__recomp(EEContext&);  // recompiled
void fn_sub_558610_00558610(EEContext&);  // generated body
void fn_sub_558610_00558610__recomp(EEContext&);  // recompiled
void fn_sub_558988_00558988(EEContext&);  // generated body
void fn_sub_558988_00558988__recomp(EEContext&);  // recompiled
void fn_sub_558A70_00558a70(EEContext&);  // generated body
void fn_sub_558A70_00558a70__recomp(EEContext&);  // recompiled
void fn_sub_558AA8_00558aa8(EEContext&);  // generated body
void fn_sub_558AA8_00558aa8__recomp(EEContext&);  // recompiled
void fn_sub_558B68_00558b68(EEContext&);  // generated body
void fn_sub_558B68_00558b68__recomp(EEContext&);  // recompiled
void fn_sub_558C20_00558c20(EEContext&);  // generated body
void fn_sub_558C20_00558c20__recomp(EEContext&);  // recompiled
void fn_sub_558C98_00558c98(EEContext&);  // generated body
void fn_sub_558C98_00558c98__recomp(EEContext&);  // recompiled
void fn_sub_558D00_00558d00(EEContext&);  // generated body
void fn_sub_558D00_00558d00__recomp(EEContext&);  // recompiled
void fn_sub_558D58_00558d58(EEContext&);  // generated body
void fn_sub_558D58_00558d58__recomp(EEContext&);  // recompiled
void fn_sub_559138_00559138(EEContext&);  // generated body
void fn_sub_559138_00559138__recomp(EEContext&);  // recompiled
void fn_sub_559280_00559280(EEContext&);  // generated body
void fn_sub_559280_00559280__recomp(EEContext&);  // recompiled
void fn_sub_559370_00559370(EEContext&);  // generated body
void fn_sub_559370_00559370__recomp(EEContext&);  // recompiled
void fn_sub_559398_00559398(EEContext&);  // generated body
void fn_sub_559398_00559398__recomp(EEContext&);  // recompiled
void fn_sub_559718_00559718(EEContext&);  // generated body
void fn_sub_559718_00559718__recomp(EEContext&);  // recompiled
void fn_sub_5598B0_005598b0(EEContext&);  // generated body
void fn_sub_5598B0_005598b0__recomp(EEContext&);  // recompiled
void fn_sub_559918_00559918(EEContext&);  // generated body
void fn_sub_559918_00559918__recomp(EEContext&);  // recompiled
void fn_sub_559928_00559928(EEContext&);  // generated body
void fn_sub_559928_00559928__recomp(EEContext&);  // recompiled
void fn_sub_559B98_00559b98(EEContext&);  // generated body
void fn_sub_559B98_00559b98__recomp(EEContext&);  // recompiled
void fn_sub_559D18_00559d18(EEContext&);  // generated body
void fn_sub_559D18_00559d18__recomp(EEContext&);  // recompiled
void fn_dvCiGetInterface_00559d78(EEContext&);  // generated body
void fn_dvCiGetInterface_00559d78__recomp(EEContext&);  // recompiled
void fn_sub_559DA8_00559da8(EEContext&);  // generated body
void fn_sub_559DA8_00559da8__recomp(EEContext&);  // recompiled
void fn_dvCiExecHndl_00559e80(EEContext&);  // generated body
void fn_dvCiExecHndl_00559e80__recomp(EEContext&);  // recompiled
void fn_dvCiExecServer_00559f48(EEContext&);  // generated body
void fn_dvCiExecServer_00559f48__recomp(EEContext&);  // recompiled
void fn_sub_559FC0_00559fc0(EEContext&);  // generated body
void fn_sub_559FC0_00559fc0__recomp(EEContext&);  // recompiled
void fn_sub_559FD8_00559fd8(EEContext&);  // generated body
void fn_sub_559FD8_00559fd8__recomp(EEContext&);  // recompiled
void fn_dvci_get_fstate_0055b220(EEContext&);  // generated body
void fn_dvci_get_fstate_0055b220__recomp(EEContext&);  // recompiled
void fn_dvCiLoadFcache_0055b300(EEContext&);  // generated body
void fn_dvCiLoadFcache_0055b300__recomp(EEContext&);  // recompiled
void fn_sub_55B5F0_0055b5f0(EEContext&);  // generated body
void fn_sub_55B5F0_0055b5f0__recomp(EEContext&);  // recompiled
void fn_dvCiSetRootDir_0055b610(EEContext&);  // generated body
void fn_dvCiSetRootDir_0055b610__recomp(EEContext&);  // recompiled
void fn_sub_55B7C8_0055b7c8(EEContext&);  // generated body
void fn_sub_55B7C8_0055b7c8__recomp(EEContext&);  // recompiled
void fn_sub_55B9D8_0055b9d8(EEContext&);  // generated body
void fn_sub_55B9D8_0055b9d8__recomp(EEContext&);  // recompiled
void fn_sub_55BB30_0055bb30(EEContext&);  // generated body
void fn_sub_55BB30_0055bb30__recomp(EEContext&);  // recompiled
void fn_sub_55BDA8_0055bda8(EEContext&);  // generated body
void fn_sub_55BDA8_0055bda8__recomp(EEContext&);  // recompiled
void fn_sub_55C240_0055c240(EEContext&);  // generated body
void fn_sub_55C240_0055c240__recomp(EEContext&);  // recompiled
void fn_sub_55C338_0055c338(EEContext&);  // generated body
void fn_sub_55C338_0055c338__recomp(EEContext&);  // recompiled
void fn_sub_55C3C8_0055c3c8(EEContext&);  // generated body
void fn_sub_55C3C8_0055c3c8__recomp(EEContext&);  // recompiled
void fn_sub_55C610_0055c610(EEContext&);  // generated body
void fn_sub_55C610_0055c610__recomp(EEContext&);  // recompiled
void fn_sub_55C9D0_0055c9d0(EEContext&);  // generated body
void fn_sub_55C9D0_0055c9d0__recomp(EEContext&);  // recompiled
void fn_sub_55CEE0_0055cee0(EEContext&);  // generated body
void fn_sub_55CEE0_0055cee0__recomp(EEContext&);  // recompiled
void fn_sub_55CF08_0055cf08(EEContext&);  // generated body
void fn_sub_55CF08_0055cf08__recomp(EEContext&);  // recompiled
void fn_sub_55D240_0055d240(EEContext&);  // generated body
void fn_sub_55D240_0055d240__recomp(EEContext&);  // recompiled
void fn_sub_55D428_0055d428(EEContext&);  // generated body
void fn_sub_55D428_0055d428__recomp(EEContext&);  // recompiled
void fn_sub_55D5C0_0055d5c0(EEContext&);  // generated body
void fn_sub_55D5C0_0055d5c0__recomp(EEContext&);  // recompiled
void fn_sub_55D600_0055d600(EEContext&);  // generated body
void fn_sub_55D600_0055d600__recomp(EEContext&);  // recompiled
void fn_sub_55D730_0055d730(EEContext&);  // generated body
void fn_sub_55D730_0055d730__recomp(EEContext&);  // recompiled
void fn_sub_55DB58_0055db58(EEContext&);  // generated body
void fn_sub_55DB58_0055db58__recomp(EEContext&);  // recompiled
void fn_sub_55DB88_0055db88(EEContext&);  // generated body
void fn_sub_55DB88_0055db88__recomp(EEContext&);  // recompiled
void fn_sub_55DBA8_0055dba8(EEContext&);  // generated body
void fn_sub_55DBA8_0055dba8__recomp(EEContext&);  // recompiled
void fn_sub_55DBC0_0055dbc0(EEContext&);  // generated body
void fn_sub_55DBC0_0055dbc0__recomp(EEContext&);  // recompiled
void fn_sub_55DBE8_0055dbe8(EEContext&);  // generated body
void fn_sub_55DBE8_0055dbe8__recomp(EEContext&);  // recompiled
void fn___env_lock_8_0055dc78(EEContext&);  // generated body
void fn___env_lock_8_0055dc78__recomp(EEContext&);  // recompiled
void fn_sub_55DC88_0055dc88(EEContext&);  // generated body
void fn_sub_55DC88_0055dc88__recomp(EEContext&);  // recompiled
void fn_sub_55DD08_0055dd08(EEContext&);  // generated body
void fn_sub_55DD08_0055dd08__recomp(EEContext&);  // recompiled
void fn_sub_55E0C0_0055e0c0(EEContext&);  // generated body
void fn_sub_55E0C0_0055e0c0__recomp(EEContext&);  // recompiled
void fn_sub_55E190_0055e190(EEContext&);  // generated body
void fn_sub_55E190_0055e190__recomp(EEContext&);  // recompiled
void fn_sub_55E1A8_0055e1a8(EEContext&);  // generated body
void fn_sub_55E1A8_0055e1a8__recomp(EEContext&);  // recompiled
void fn_sub_55E1C0_0055e1c0(EEContext&);  // generated body
void fn_sub_55E1C0_0055e1c0__recomp(EEContext&);  // recompiled
void fn_sub_55E1D8_0055e1d8(EEContext&);  // generated body
void fn_sub_55E1D8_0055e1d8__recomp(EEContext&);  // recompiled
void fn_sub_55E220_0055e220(EEContext&);  // generated body
void fn_sub_55E220_0055e220__recomp(EEContext&);  // recompiled
void fn_sub_55E320_0055e320(EEContext&);  // generated body
void fn_sub_55E320_0055e320__recomp(EEContext&);  // recompiled
void fn_sub_55E378_0055e378(EEContext&);  // generated body
void fn_sub_55E378_0055e378__recomp(EEContext&);  // recompiled
void fn_sub_55E390_0055e390(EEContext&);  // generated body
void fn_sub_55E390_0055e390__recomp(EEContext&);  // recompiled
void fn_sub_55E3B0_0055e3b0(EEContext&);  // generated body
void fn_sub_55E3B0_0055e3b0__recomp(EEContext&);  // recompiled
void fn_sub_55E428_0055e428(EEContext&);  // generated body
void fn_sub_55E428_0055e428__recomp(EEContext&);  // recompiled
void fn_sub_55E940_0055e940(EEContext&);  // generated body
void fn_sub_55E940_0055e940__recomp(EEContext&);  // recompiled
void fn_sub_55EA80_0055ea80(EEContext&);  // generated body
void fn_sub_55EA80_0055ea80__recomp(EEContext&);  // recompiled
void fn_sub_55EA98_0055ea98(EEContext&);  // generated body
void fn_sub_55EA98_0055ea98__recomp(EEContext&);  // recompiled
void fn_sub_55EB08_0055eb08(EEContext&);  // generated body
void fn_sub_55EB08_0055eb08__recomp(EEContext&);  // recompiled
void fn_sub_55EDB8_0055edb8(EEContext&);  // generated body
void fn_sub_55EDB8_0055edb8__recomp(EEContext&);  // recompiled
void fn_sub_55F1C8_0055f1c8(EEContext&);  // generated body
void fn_sub_55F1C8_0055f1c8__recomp(EEContext&);  // recompiled
void fn_sub_55F688_0055f688(EEContext&);  // generated body
void fn_sub_55F688_0055f688__recomp(EEContext&);  // recompiled
void fn_sub_55FB20_0055fb20(EEContext&);  // generated body
void fn_sub_55FB20_0055fb20__recomp(EEContext&);  // recompiled
void fn_sub_55FB98_0055fb98(EEContext&);  // generated body
void fn_sub_55FB98_0055fb98__recomp(EEContext&);  // recompiled
void fn_sub_55FBA0_0055fba0(EEContext&);  // generated body
void fn_sub_55FBA0_0055fba0__recomp(EEContext&);  // recompiled
void fn_sub_55FC00_0055fc00(EEContext&);  // generated body
void fn_sub_55FC00_0055fc00__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_550048", 0x550048, &recomp_gen::fn_sub_550048_00550048, &recomp_gen::fn_sub_550048_00550048__recomp},
    {"sub_550238", 0x550238, &recomp_gen::fn_sub_550238_00550238, &recomp_gen::fn_sub_550238_00550238__recomp},
    {"sub_550428", 0x550428, &recomp_gen::fn_sub_550428_00550428, &recomp_gen::fn_sub_550428_00550428__recomp},
    {"sub_550618", 0x550618, &recomp_gen::fn_sub_550618_00550618, &recomp_gen::fn_sub_550618_00550618__recomp},
    {"sub_5513A8", 0x5513A8, &recomp_gen::fn_sub_5513A8_005513a8, &recomp_gen::fn_sub_5513A8_005513a8__recomp},
    {"sub_551598", 0x551598, &recomp_gen::fn_sub_551598_00551598, &recomp_gen::fn_sub_551598_00551598__recomp},
    {"sub_551788", 0x551788, &recomp_gen::fn_sub_551788_00551788, &recomp_gen::fn_sub_551788_00551788__recomp},
    {"sub_551978", 0x551978, &recomp_gen::fn_sub_551978_00551978, &recomp_gen::fn_sub_551978_00551978__recomp},
    {"sub_551990", 0x551990, &recomp_gen::fn_sub_551990_00551990, &recomp_gen::fn_sub_551990_00551990__recomp},
    {"sub_5519E8", 0x5519E8, &recomp_gen::fn_sub_5519E8_005519e8, &recomp_gen::fn_sub_5519E8_005519e8__recomp},
    {"sub_551A88", 0x551A88, &recomp_gen::fn_sub_551A88_00551a88, &recomp_gen::fn_sub_551A88_00551a88__recomp},
    {"sub_551AD8", 0x551AD8, &recomp_gen::fn_sub_551AD8_00551ad8, &recomp_gen::fn_sub_551AD8_00551ad8__recomp},
    {"sub_551BB0", 0x551BB0, &recomp_gen::fn_sub_551BB0_00551bb0, &recomp_gen::fn_sub_551BB0_00551bb0__recomp},
    {"sub_551BF0", 0x551BF0, &recomp_gen::fn_sub_551BF0_00551bf0, &recomp_gen::fn_sub_551BF0_00551bf0__recomp},
    {"sub_551D38", 0x551D38, &recomp_gen::fn_sub_551D38_00551d38, &recomp_gen::fn_sub_551D38_00551d38__recomp},
    {"sub_551DA0", 0x551DA0, &recomp_gen::fn_sub_551DA0_00551da0, &recomp_gen::fn_sub_551DA0_00551da0__recomp},
    {"sub_551DF8", 0x551DF8, &recomp_gen::fn_sub_551DF8_00551df8, &recomp_gen::fn_sub_551DF8_00551df8__recomp},
    {"sub_551E30", 0x551E30, &recomp_gen::fn_sub_551E30_00551e30, &recomp_gen::fn_sub_551E30_00551e30__recomp},
    {"sub_551F80", 0x551F80, &recomp_gen::fn_sub_551F80_00551f80, &recomp_gen::fn_sub_551F80_00551f80__recomp},
    {"sub_551FF8", 0x551FF8, &recomp_gen::fn_sub_551FF8_00551ff8, &recomp_gen::fn_sub_551FF8_00551ff8__recomp},
    {"sub_552008", 0x552008, &recomp_gen::fn_sub_552008_00552008, &recomp_gen::fn_sub_552008_00552008__recomp},
    {"sub_552028", 0x552028, &recomp_gen::fn_sub_552028_00552028, &recomp_gen::fn_sub_552028_00552028__recomp},
    {"sub_552080", 0x552080, &recomp_gen::fn_sub_552080_00552080, &recomp_gen::fn_sub_552080_00552080__recomp},
    {"sub_5520B0", 0x5520B0, &recomp_gen::fn_sub_5520B0_005520b0, &recomp_gen::fn_sub_5520B0_005520b0__recomp},
    {"sub_552110", 0x552110, &recomp_gen::fn_sub_552110_00552110, &recomp_gen::fn_sub_552110_00552110__recomp},
    {"sub_5523B8", 0x5523B8, &recomp_gen::fn_sub_5523B8_005523b8, &recomp_gen::fn_sub_5523B8_005523b8__recomp},
    {"sub_552460", 0x552460, &recomp_gen::fn_sub_552460_00552460, &recomp_gen::fn_sub_552460_00552460__recomp},
    {"sub_552468", 0x552468, &recomp_gen::fn_sub_552468_00552468, &recomp_gen::fn_sub_552468_00552468__recomp},
    {"sub_552480", 0x552480, &recomp_gen::fn_sub_552480_00552480, &recomp_gen::fn_sub_552480_00552480__recomp},
    {"sub_552508", 0x552508, &recomp_gen::fn_sub_552508_00552508, &recomp_gen::fn_sub_552508_00552508__recomp},
    {"sub_552520", 0x552520, &recomp_gen::fn_sub_552520_00552520, &recomp_gen::fn_sub_552520_00552520__recomp},
    {"sub_552600", 0x552600, &recomp_gen::fn_sub_552600_00552600, &recomp_gen::fn_sub_552600_00552600__recomp},
    {"sub_552630", 0x552630, &recomp_gen::fn_sub_552630_00552630, &recomp_gen::fn_sub_552630_00552630__recomp},
    {"sub_552930", 0x552930, &recomp_gen::fn_sub_552930_00552930, &recomp_gen::fn_sub_552930_00552930__recomp},
    {"sub_552D68", 0x552D68, &recomp_gen::fn_sub_552D68_00552d68, &recomp_gen::fn_sub_552D68_00552d68__recomp},
    {"sub_553288", 0x553288, &recomp_gen::fn_sub_553288_00553288, &recomp_gen::fn_sub_553288_00553288__recomp},
    {"sub_5535D0", 0x5535D0, &recomp_gen::fn_sub_5535D0_005535d0, &recomp_gen::fn_sub_5535D0_005535d0__recomp},
    {"sub_553838", 0x553838, &recomp_gen::fn_sub_553838_00553838, &recomp_gen::fn_sub_553838_00553838__recomp},
    {"sub_553920", 0x553920, &recomp_gen::fn_sub_553920_00553920, &recomp_gen::fn_sub_553920_00553920__recomp},
    {"sub_553A78", 0x553A78, &recomp_gen::fn_sub_553A78_00553a78, &recomp_gen::fn_sub_553A78_00553a78__recomp},
    {"sub_553B70", 0x553B70, &recomp_gen::fn_sub_553B70_00553b70, &recomp_gen::fn_sub_553B70_00553b70__recomp},
    {"sub_553BC0", 0x553BC0, &recomp_gen::fn_sub_553BC0_00553bc0, &recomp_gen::fn_sub_553BC0_00553bc0__recomp},
    {"sub_553FA8", 0x553FA8, &recomp_gen::fn_sub_553FA8_00553fa8, &recomp_gen::fn_sub_553FA8_00553fa8__recomp},
    {"sub_554048", 0x554048, &recomp_gen::fn_sub_554048_00554048, &recomp_gen::fn_sub_554048_00554048__recomp},
    {"sub_5541D0", 0x5541D0, &recomp_gen::fn_sub_5541D0_005541d0, &recomp_gen::fn_sub_5541D0_005541d0__recomp},
    {"sub_5542E8", 0x5542E8, &recomp_gen::fn_sub_5542E8_005542e8, &recomp_gen::fn_sub_5542E8_005542e8__recomp},
    {"sub_554360", 0x554360, &recomp_gen::fn_sub_554360_00554360, &recomp_gen::fn_sub_554360_00554360__recomp},
    {"sub_5543C8", 0x5543C8, &recomp_gen::fn_sub_5543C8_005543c8, &recomp_gen::fn_sub_5543C8_005543c8__recomp},
    {"sub_554448", 0x554448, &recomp_gen::fn_sub_554448_00554448, &recomp_gen::fn_sub_554448_00554448__recomp},
    {"sub_5544C8", 0x5544C8, &recomp_gen::fn_sub_5544C8_005544c8, &recomp_gen::fn_sub_5544C8_005544c8__recomp},
    {"sub_554530", 0x554530, &recomp_gen::fn_sub_554530_00554530, &recomp_gen::fn_sub_554530_00554530__recomp},
    {"sub_5546F0", 0x5546F0, &recomp_gen::fn_sub_5546F0_005546f0, &recomp_gen::fn_sub_5546F0_005546f0__recomp},
    {"sub_554708", 0x554708, &recomp_gen::fn_sub_554708_00554708, &recomp_gen::fn_sub_554708_00554708__recomp},
    {"sub_554720", 0x554720, &recomp_gen::fn_sub_554720_00554720, &recomp_gen::fn_sub_554720_00554720__recomp},
    {"sub_554900", 0x554900, &recomp_gen::fn_sub_554900_00554900, &recomp_gen::fn_sub_554900_00554900__recomp},
    {"sub_554908", 0x554908, &recomp_gen::fn_sub_554908_00554908, &recomp_gen::fn_sub_554908_00554908__recomp},
    {"sub_554948", 0x554948, &recomp_gen::fn_sub_554948_00554948, &recomp_gen::fn_sub_554948_00554948__recomp},
    {"sub_554958", 0x554958, &recomp_gen::fn_sub_554958_00554958, &recomp_gen::fn_sub_554958_00554958__recomp},
    {"sub_554968", 0x554968, &recomp_gen::fn_sub_554968_00554968, &recomp_gen::fn_sub_554968_00554968__recomp},
    {"sub_554990", 0x554990, &recomp_gen::fn_sub_554990_00554990, &recomp_gen::fn_sub_554990_00554990__recomp},
    {"sub_5549C8", 0x5549C8, &recomp_gen::fn_sub_5549C8_005549c8, &recomp_gen::fn_sub_5549C8_005549c8__recomp},
    {"sub_554A98", 0x554A98, &recomp_gen::fn_sub_554A98_00554a98, &recomp_gen::fn_sub_554A98_00554a98__recomp},
    {"sub_554AE8", 0x554AE8, &recomp_gen::fn_sub_554AE8_00554ae8, &recomp_gen::fn_sub_554AE8_00554ae8__recomp},
    {"sub_555570", 0x555570, &recomp_gen::fn_sub_555570_00555570, &recomp_gen::fn_sub_555570_00555570__recomp},
    {"sub_5555A0", 0x5555A0, &recomp_gen::fn_sub_5555A0_005555a0, &recomp_gen::fn_sub_5555A0_005555a0__recomp},
    {"sub_555658", 0x555658, &recomp_gen::fn_sub_555658_00555658, &recomp_gen::fn_sub_555658_00555658__recomp},
    {"sub_555898", 0x555898, &recomp_gen::fn_sub_555898_00555898, &recomp_gen::fn_sub_555898_00555898__recomp},
    {"SRD_Create", 0x557A58, &recomp_gen::fn_SRD_Create_00557a58, &recomp_gen::fn_SRD_Create_00557a58__recomp},
    {"sub_557AE0", 0x557AE0, &recomp_gen::fn_sub_557AE0_00557ae0, &recomp_gen::fn_sub_557AE0_00557ae0__recomp},
    {"sub_557D20", 0x557D20, &recomp_gen::fn_sub_557D20_00557d20, &recomp_gen::fn_sub_557D20_00557d20__recomp},
    {"sub_557D28", 0x557D28, &recomp_gen::fn_sub_557D28_00557d28, &recomp_gen::fn_sub_557D28_00557d28__recomp},
    {"sub_557D80", 0x557D80, &recomp_gen::fn_sub_557D80_00557d80, &recomp_gen::fn_sub_557D80_00557d80__recomp},
    {"SRD_WaitComplete", 0x557E50, &recomp_gen::fn_SRD_WaitComplete_00557e50, &recomp_gen::fn_SRD_WaitComplete_00557e50__recomp},
    {"sub_557F80", 0x557F80, &recomp_gen::fn_sub_557F80_00557f80, &recomp_gen::fn_sub_557F80_00557f80__recomp},
    {"SRD_ExecServer", 0x558500, &recomp_gen::fn_SRD_ExecServer_00558500, &recomp_gen::fn_SRD_ExecServer_00558500__recomp},
    {"sub_558610", 0x558610, &recomp_gen::fn_sub_558610_00558610, &recomp_gen::fn_sub_558610_00558610__recomp},
    {"sub_558988", 0x558988, &recomp_gen::fn_sub_558988_00558988, &recomp_gen::fn_sub_558988_00558988__recomp},
    {"sub_558A70", 0x558A70, &recomp_gen::fn_sub_558A70_00558a70, &recomp_gen::fn_sub_558A70_00558a70__recomp},
    {"sub_558AA8", 0x558AA8, &recomp_gen::fn_sub_558AA8_00558aa8, &recomp_gen::fn_sub_558AA8_00558aa8__recomp},
    {"sub_558B68", 0x558B68, &recomp_gen::fn_sub_558B68_00558b68, &recomp_gen::fn_sub_558B68_00558b68__recomp},
    {"sub_558C20", 0x558C20, &recomp_gen::fn_sub_558C20_00558c20, &recomp_gen::fn_sub_558C20_00558c20__recomp},
    {"sub_558C98", 0x558C98, &recomp_gen::fn_sub_558C98_00558c98, &recomp_gen::fn_sub_558C98_00558c98__recomp},
    {"sub_558D00", 0x558D00, &recomp_gen::fn_sub_558D00_00558d00, &recomp_gen::fn_sub_558D00_00558d00__recomp},
    {"sub_558D58", 0x558D58, &recomp_gen::fn_sub_558D58_00558d58, &recomp_gen::fn_sub_558D58_00558d58__recomp},
    {"sub_559138", 0x559138, &recomp_gen::fn_sub_559138_00559138, &recomp_gen::fn_sub_559138_00559138__recomp},
    {"sub_559280", 0x559280, &recomp_gen::fn_sub_559280_00559280, &recomp_gen::fn_sub_559280_00559280__recomp},
    {"sub_559370", 0x559370, &recomp_gen::fn_sub_559370_00559370, &recomp_gen::fn_sub_559370_00559370__recomp},
    {"sub_559398", 0x559398, &recomp_gen::fn_sub_559398_00559398, &recomp_gen::fn_sub_559398_00559398__recomp},
    {"sub_559718", 0x559718, &recomp_gen::fn_sub_559718_00559718, &recomp_gen::fn_sub_559718_00559718__recomp},
    {"sub_5598B0", 0x5598B0, &recomp_gen::fn_sub_5598B0_005598b0, &recomp_gen::fn_sub_5598B0_005598b0__recomp},
    {"sub_559918", 0x559918, &recomp_gen::fn_sub_559918_00559918, &recomp_gen::fn_sub_559918_00559918__recomp},
    {"sub_559928", 0x559928, &recomp_gen::fn_sub_559928_00559928, &recomp_gen::fn_sub_559928_00559928__recomp},
    {"sub_559B98", 0x559B98, &recomp_gen::fn_sub_559B98_00559b98, &recomp_gen::fn_sub_559B98_00559b98__recomp},
    {"sub_559D18", 0x559D18, &recomp_gen::fn_sub_559D18_00559d18, &recomp_gen::fn_sub_559D18_00559d18__recomp},
    {"dvCiGetInterface", 0x559D78, &recomp_gen::fn_dvCiGetInterface_00559d78, &recomp_gen::fn_dvCiGetInterface_00559d78__recomp},
    {"sub_559DA8", 0x559DA8, &recomp_gen::fn_sub_559DA8_00559da8, &recomp_gen::fn_sub_559DA8_00559da8__recomp},
    {"dvCiExecHndl", 0x559E80, &recomp_gen::fn_dvCiExecHndl_00559e80, &recomp_gen::fn_dvCiExecHndl_00559e80__recomp},
    {"dvCiExecServer", 0x559F48, &recomp_gen::fn_dvCiExecServer_00559f48, &recomp_gen::fn_dvCiExecServer_00559f48__recomp},
    {"sub_559FC0", 0x559FC0, &recomp_gen::fn_sub_559FC0_00559fc0, &recomp_gen::fn_sub_559FC0_00559fc0__recomp},
    {"sub_559FD8", 0x559FD8, &recomp_gen::fn_sub_559FD8_00559fd8, &recomp_gen::fn_sub_559FD8_00559fd8__recomp},
    {"dvci_get_fstate", 0x55B220, &recomp_gen::fn_dvci_get_fstate_0055b220, &recomp_gen::fn_dvci_get_fstate_0055b220__recomp},
    {"dvCiLoadFcache", 0x55B300, &recomp_gen::fn_dvCiLoadFcache_0055b300, &recomp_gen::fn_dvCiLoadFcache_0055b300__recomp},
    {"sub_55B5F0", 0x55B5F0, &recomp_gen::fn_sub_55B5F0_0055b5f0, &recomp_gen::fn_sub_55B5F0_0055b5f0__recomp},
    {"dvCiSetRootDir", 0x55B610, &recomp_gen::fn_dvCiSetRootDir_0055b610, &recomp_gen::fn_dvCiSetRootDir_0055b610__recomp},
    {"sub_55B7C8", 0x55B7C8, &recomp_gen::fn_sub_55B7C8_0055b7c8, &recomp_gen::fn_sub_55B7C8_0055b7c8__recomp},
    {"sub_55B9D8", 0x55B9D8, &recomp_gen::fn_sub_55B9D8_0055b9d8, &recomp_gen::fn_sub_55B9D8_0055b9d8__recomp},
    {"sub_55BB30", 0x55BB30, &recomp_gen::fn_sub_55BB30_0055bb30, &recomp_gen::fn_sub_55BB30_0055bb30__recomp},
    {"sub_55BDA8", 0x55BDA8, &recomp_gen::fn_sub_55BDA8_0055bda8, &recomp_gen::fn_sub_55BDA8_0055bda8__recomp},
    {"sub_55C240", 0x55C240, &recomp_gen::fn_sub_55C240_0055c240, &recomp_gen::fn_sub_55C240_0055c240__recomp},
    {"sub_55C338", 0x55C338, &recomp_gen::fn_sub_55C338_0055c338, &recomp_gen::fn_sub_55C338_0055c338__recomp},
    {"sub_55C3C8", 0x55C3C8, &recomp_gen::fn_sub_55C3C8_0055c3c8, &recomp_gen::fn_sub_55C3C8_0055c3c8__recomp},
    {"sub_55C610", 0x55C610, &recomp_gen::fn_sub_55C610_0055c610, &recomp_gen::fn_sub_55C610_0055c610__recomp},
    {"sub_55C9D0", 0x55C9D0, &recomp_gen::fn_sub_55C9D0_0055c9d0, &recomp_gen::fn_sub_55C9D0_0055c9d0__recomp},
    {"sub_55CEE0", 0x55CEE0, &recomp_gen::fn_sub_55CEE0_0055cee0, &recomp_gen::fn_sub_55CEE0_0055cee0__recomp},
    {"sub_55CF08", 0x55CF08, &recomp_gen::fn_sub_55CF08_0055cf08, &recomp_gen::fn_sub_55CF08_0055cf08__recomp},
    {"sub_55D240", 0x55D240, &recomp_gen::fn_sub_55D240_0055d240, &recomp_gen::fn_sub_55D240_0055d240__recomp},
    {"sub_55D428", 0x55D428, &recomp_gen::fn_sub_55D428_0055d428, &recomp_gen::fn_sub_55D428_0055d428__recomp},
    {"sub_55D5C0", 0x55D5C0, &recomp_gen::fn_sub_55D5C0_0055d5c0, &recomp_gen::fn_sub_55D5C0_0055d5c0__recomp},
    {"sub_55D600", 0x55D600, &recomp_gen::fn_sub_55D600_0055d600, &recomp_gen::fn_sub_55D600_0055d600__recomp},
    {"sub_55D730", 0x55D730, &recomp_gen::fn_sub_55D730_0055d730, &recomp_gen::fn_sub_55D730_0055d730__recomp},
    {"sub_55DB58", 0x55DB58, &recomp_gen::fn_sub_55DB58_0055db58, &recomp_gen::fn_sub_55DB58_0055db58__recomp},
    {"sub_55DB88", 0x55DB88, &recomp_gen::fn_sub_55DB88_0055db88, &recomp_gen::fn_sub_55DB88_0055db88__recomp},
    {"sub_55DBA8", 0x55DBA8, &recomp_gen::fn_sub_55DBA8_0055dba8, &recomp_gen::fn_sub_55DBA8_0055dba8__recomp},
    {"sub_55DBC0", 0x55DBC0, &recomp_gen::fn_sub_55DBC0_0055dbc0, &recomp_gen::fn_sub_55DBC0_0055dbc0__recomp},
    {"sub_55DBE8", 0x55DBE8, &recomp_gen::fn_sub_55DBE8_0055dbe8, &recomp_gen::fn_sub_55DBE8_0055dbe8__recomp},
    {"__env_lock_8", 0x55DC78, &recomp_gen::fn___env_lock_8_0055dc78, &recomp_gen::fn___env_lock_8_0055dc78__recomp},
    {"sub_55DC88", 0x55DC88, &recomp_gen::fn_sub_55DC88_0055dc88, &recomp_gen::fn_sub_55DC88_0055dc88__recomp},
    {"sub_55DD08", 0x55DD08, &recomp_gen::fn_sub_55DD08_0055dd08, &recomp_gen::fn_sub_55DD08_0055dd08__recomp},
    {"sub_55E0C0", 0x55E0C0, &recomp_gen::fn_sub_55E0C0_0055e0c0, &recomp_gen::fn_sub_55E0C0_0055e0c0__recomp},
    {"sub_55E190", 0x55E190, &recomp_gen::fn_sub_55E190_0055e190, &recomp_gen::fn_sub_55E190_0055e190__recomp},
    {"sub_55E1A8", 0x55E1A8, &recomp_gen::fn_sub_55E1A8_0055e1a8, &recomp_gen::fn_sub_55E1A8_0055e1a8__recomp},
    {"sub_55E1C0", 0x55E1C0, &recomp_gen::fn_sub_55E1C0_0055e1c0, &recomp_gen::fn_sub_55E1C0_0055e1c0__recomp},
    {"sub_55E1D8", 0x55E1D8, &recomp_gen::fn_sub_55E1D8_0055e1d8, &recomp_gen::fn_sub_55E1D8_0055e1d8__recomp},
    {"sub_55E220", 0x55E220, &recomp_gen::fn_sub_55E220_0055e220, &recomp_gen::fn_sub_55E220_0055e220__recomp},
    {"sub_55E320", 0x55E320, &recomp_gen::fn_sub_55E320_0055e320, &recomp_gen::fn_sub_55E320_0055e320__recomp},
    {"sub_55E378", 0x55E378, &recomp_gen::fn_sub_55E378_0055e378, &recomp_gen::fn_sub_55E378_0055e378__recomp},
    {"sub_55E390", 0x55E390, &recomp_gen::fn_sub_55E390_0055e390, &recomp_gen::fn_sub_55E390_0055e390__recomp},
    {"sub_55E3B0", 0x55E3B0, &recomp_gen::fn_sub_55E3B0_0055e3b0, &recomp_gen::fn_sub_55E3B0_0055e3b0__recomp},
    {"sub_55E428", 0x55E428, &recomp_gen::fn_sub_55E428_0055e428, &recomp_gen::fn_sub_55E428_0055e428__recomp},
    {"sub_55E940", 0x55E940, &recomp_gen::fn_sub_55E940_0055e940, &recomp_gen::fn_sub_55E940_0055e940__recomp},
    {"sub_55EA80", 0x55EA80, &recomp_gen::fn_sub_55EA80_0055ea80, &recomp_gen::fn_sub_55EA80_0055ea80__recomp},
    {"sub_55EA98", 0x55EA98, &recomp_gen::fn_sub_55EA98_0055ea98, &recomp_gen::fn_sub_55EA98_0055ea98__recomp},
    {"sub_55EB08", 0x55EB08, &recomp_gen::fn_sub_55EB08_0055eb08, &recomp_gen::fn_sub_55EB08_0055eb08__recomp},
    {"sub_55EDB8", 0x55EDB8, &recomp_gen::fn_sub_55EDB8_0055edb8, &recomp_gen::fn_sub_55EDB8_0055edb8__recomp},
    {"sub_55F1C8", 0x55F1C8, &recomp_gen::fn_sub_55F1C8_0055f1c8, &recomp_gen::fn_sub_55F1C8_0055f1c8__recomp},
    {"sub_55F688", 0x55F688, &recomp_gen::fn_sub_55F688_0055f688, &recomp_gen::fn_sub_55F688_0055f688__recomp},
    {"sub_55FB20", 0x55FB20, &recomp_gen::fn_sub_55FB20_0055fb20, &recomp_gen::fn_sub_55FB20_0055fb20__recomp},
    {"sub_55FB98", 0x55FB98, &recomp_gen::fn_sub_55FB98_0055fb98, &recomp_gen::fn_sub_55FB98_0055fb98__recomp},
    {"sub_55FBA0", 0x55FBA0, &recomp_gen::fn_sub_55FBA0_0055fba0, &recomp_gen::fn_sub_55FBA0_0055fba0__recomp},
    {"sub_55FC00", 0x55FC00, &recomp_gen::fn_sub_55FC00_0055fc00, &recomp_gen::fn_sub_55FC00_0055fc00__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
constexpr u32 kWork = kWorld;  // the built records, names and buffers of the real-world sections

// --- the real worlds ---------------------------------------------------------------------------------------------
// The CRI records these bodies work on (layouts read from the instructions; see game/src/cri/libs10.cpp's roles).
constexpr u32 kAhxSynRefs = 0x798640u, kAhxSynSlots = 0x798648u;   // 16 pointers
constexpr u32 kAhxDecRefs = 0x7986E8u, kAhxDecSlots = 0x7986F0u;   // 16 pointers
constexpr u32 kAixp = 0x799978u, kAixpSize = 620u;                 // 4 players
constexpr u32 kAixDemux = 0x79A330u, kAixDemuxSize = 6492u;        // 4 demuxers
constexpr u32 kSrdObj = 0x7A08B0u, kSrdBusy = 0x7A08ECu;           // the single SRD request, the server's busy word
constexpr u32 kDtr = 0x7A0938u, kDtrSize = 64u;                    // 32 DTR objects
constexpr u32 kDtx = 0x7A1160u, kDtxSize = 68u;                    // 16 DTX records
constexpr u32 kDvci = 0x7A1DF0u, kDvciSize = 72u;                  // 40 DVD CI handles
constexpr u32 kHtci = 0x7A2C80u, kHtciSize = 48u;                  // 13 host CI handles
constexpr u32 kLsc = 0x7A32A0u, kLscSize = 568u;                   // 32 LSC streamers
constexpr u32 kRootDir = 0x7A2A80u;                                // dvCi's root directory
constexpr u32 kAdxErr = 0x53AE08u, kScePrintf = 0x505E48u, kSceIoctl = 0x5091E8u, kDtxCreateRmt = 0x559588u;

// The callees these bodies reach that the test build does not emit and no current slice takes: recorders (no scratch
// clobbering, so one set serves both bodies of a pair alike; the two halves of its log are compared). The callees
// other slices take are left to stop the pair (identically) at the call.
const u32 kDrivers[] = {
    kAdxErr,  0x545FC8u, 0x5466B8u, 0x552BD0u, 0x5530D0u, 0x546FA0u, 0x553188u, 0x5463A8u, 0x546498u, 0x546718u,
    0x5460E0u, 0x546270u, 0x546368u, 0x54A928u, 0x547F30u, 0x547BC0u, 0x548048u, 0x548678u, 0x548768u, 0x5484E0u,
    0x54A3C0u, kScePrintf, 0x508A78u, 0x508670u, 0x508900u, 0x508CB8u, 0x50ACD8u, 0x55B030u, 0x55B120u, 0x55B160u,
    0x55AB80u, 0x55AD18u, 0x55AEA0u, 0x55B0F8u, 0x55D668u, 0x5288C8u, 0x55D3A8u, 0x523AC8u, 0x557D58u, 0x558138u,
    kDtxCreateRmt, 0x5595F8u, 0x54E7D8u, 0x562388u, 0x563C28u,
    0x53F8B8u, 0x53F940u,  // the SVM lock / unlock callbacks behind the CRI critical section
    0x504650u};            // kputs (scePrintf's output)

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    FAIL("no case at " << a);
    return kCases[0];
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
std::string rstr(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va))); }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
u32 uv32(u64 v) { return static_cast<u32>(v); }

std::map<std::string, int> g_pairs;  // pairs per function in the real-world sections
u32 g_seed = 1;

// One pair from the machine's current state with the drivers stood in. `v0s`: a recorder's result per callee;
// sceIoctl also writes *$a2 = 0 (the host read is finished). $t0..$t3 from `t`.
hgp::Run pr(Machine& m, u32 addr, const Args& a, const std::map<u32, u64>& v0s = {}, std::map<unsigned, u64> t = {}) {
    const Case& c = by_addr(addr);
    StandIns si;
    si.clobber_scratch = false;
    for (u32 va : kDrivers) {
        const auto it = v0s.find(va);
        si.install_recorder(va, "driver", it == v0s.end() ? 0 : it->second, 3);
    }
    const auto io = v0s.find(kSceIoctl);
    const u64 io_v0 = io == v0s.end() ? 0 : io->second;
    si.install(kSceIoctl, "sceIoctl", [io_v0](EEContext& ctx, StandIns&, StandInCall& call) {
        if (static_cast<u32>(call.args[2]) != 0) ctx.memory->write<u32>(static_cast<u32>(call.args[2]), 0);
        call.v0 = io_v0;
    }, 3);
    StandInsScope scope{si};
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s seed %u\n", c.name, g_seed);
    const hgp::Run r = hgp::pair(m, c.hand, c.recomp, a, g_seed++, c.name, hw);
    if (r.stopped && std::getenv("P3FES_LIBS10_WHY")) std::fprintf(stderr, "%s: stopped at %08x (%s)\n", c.name, r.stop_pc, r.what.c_str());
    // Both bodies met the same stand-ins: the log's first half (the hand run) equals its second half.
    INFO(c.name << " stand-in calls " << si.log.size());
    if (!r.stopped) {
        REQUIRE(si.log.size() % 2 == 0);
        const std::size_t half = si.log.size() / 2;
        for (std::size_t i = 0; i < half; ++i) CHECK(si.log[i] == si.log[half + i]);
    }
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

std::vector<u8> snapshot(const char* dir) {
    std::vector<u8> snap = read_snapshot(dir);
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot " << dir << " not found");
        snap.clear();
    }
    return snap;
}
void restore(Machine& m, const std::vector<u8>& snap) { std::memcpy(m.mem.main_ram(), snap.data(), snap.size()); }

// What $a0..$a3 hold for each function on a snapshot world: its records (live or not), NULL, and the work area for
// names and buffers. Several argument sets per function; the second argument takes the values its branches test.
std::vector<Args> recipes(u32 a) {
    const u64 w = kWork;
    std::vector<Args> out;
    auto pool = [&](u32 base, u32 size, u32 n, u64 a1 = 0, u64 a2 = 0, u64 a3 = 0) {
        for (u32 i = 0; i < n; ++i) out.push_back({base + size * i, a1, a2, a3});
    };
    switch (a) {
    // AIXP players: every slot, NULL, both pause / flag values
    case 0x552D68: pool(kAixp, kAixpSize, 4, w, 0, 16); out.push_back({0, w, 0, 16}); out.push_back({kAixp, w, 0, 0}); break;
    case 0x5535D0: case 0x5543C8: case 0x5544C8: case 0x554048:
        pool(kAixp, kAixpSize, 4, 0); pool(kAixp, kAixpSize, 4, 1); out.push_back({0, 1, 0, 0}); break;
    case 0x553288: case 0x553838: case 0x553920: case 0x553A78: case 0x553B70: case 0x553BC0: case 0x5541D0:
    case 0x5542E8: case 0x554360: case 0x554448: case 0x554530:
        pool(kAixp, kAixpSize, 4, w, 0x8000); out.push_back({0, 0, 0, 0}); break;
    // AIX demuxers
    case 0x554900: case 0x554908: case 0x554968: case 0x554990: case 0x554A98: case 0x555570: case 0x5555A0:
        pool(kAixDemux, kAixDemuxSize, 4); break;
    case 0x554948: case 0x554958: pool(kAixDemux, kAixDemuxSize, 4, 1); break;
    case 0x5549C8: pool(kAixDemux, kAixDemuxSize, 2, 0, w, w + 4); out.push_back({kAixDemux, 1, 0, 0}); break;
    // SRD
    case 0x557AE0: case 0x557D20: case 0x557D80: case 0x557E50: case 0x557F80:
        out.push_back({kSrdObj, 0, 0, 0}); out.push_back({w, 0, 0, 0}); out.push_back({0, 0, 0, 0}); break;
    // DTR / DTX
    case 0x559138: case 0x559370: case 0x559398: pool(kDtr, kDtrSize, 8); break;
    case 0x5598B0: pool(kDtx, kDtxSize, 3); break;
    case 0x559918: case 0x559928: pool(kDtx, kDtxSize, 2, 0x559660, 7); break;
    case 0x559718:  // id, EE work (64-aligned), IOP work (32-aligned), length (64 x N); each check's failure too
        out.push_back({5, w, 0x100000, 0x400}); out.push_back({0, w, 0x100000, 0x400});
        out.push_back({5, w + 4, 0x100000, 0x400}); out.push_back({5, w, 0x100004, 0x400});
        out.push_back({5, w, 0x100000, 0x404}); out.push_back({16, w, 0x100000, 0x400}); break;
    case 0x559280: out.push_back({0x1234, 0x5678, 0, 0}); break;
    // DVD CI / host CI handles
    case 0x559E80: pool(kDvci, kDvciSize, 40); break;
    case 0x55BDA8: case 0x55C338: case 0x55C240: pool(kHtci, kHtciSize, 2); out.push_back({0, 0, 0, 0}); break;
    // LSC
    case 0x55D5C0: case 0x55D600: case 0x55DB58: case 0x55E0C0: pool(kLsc, kLscSize, 5, 1); out.push_back({0, 0, 0, 0}); break;
    case 0x55D428: pool(kLsc, kLscSize, 5, w, 0x800, 0x40); out.push_back({kLsc, 0, 0, 0}); out.push_back({0, w, 0, 0}); break;
    // names, paths, buffers in the work area (prepared by the test)
    case 0x559FD8: case 0x55B610: case 0x55BB30: case 0x55C3C8: case 0x55E390:
        out.push_back({w, 0, 0, 0}); out.push_back({w + 0x100, 0, 0, 0}); break;
    case 0x55C610: case 0x55C9D0: case 0x55E220: out.push_back({w, w + 0x400, 0, 0}); out.push_back({w + 0x100, w + 0x400, 0, 0}); break;
    case 0x55B220: out.push_back({w, w + 0x400, 0, 0}); out.push_back({w + 0x200, w + 0x400, 0, 0}); break;
    case 0x55B300: out.push_back({w, w + 0x1000, 0x800, 23}); out.push_back({w, 0, 0x800, 23}); out.push_back({0, 0, 0, 0}); break;
    case 0x55E428: case 0x55E940: out.push_back({w + 0x800, 0, 0, 0}); break;
    case 0x554AE8: out.push_back({w + 0x2000, 0x2000, w + 0x8000, 0}); out.push_back({w + 0x2000, 0x100, w + 0x8000, 0}); break;
    case 0x55F688: out.push_back({3, 4, 0, 0}); out.push_back({16, 0, 0, 0}); out.push_back({0, 0, 0, 0}); break;
    case 0x55DBE8: case 0x552630: out.push_back({w + 0x300, 7, 0, 0}); break;
    case 0x558B68: out.push_back({3, 0, 0, 0}); out.push_back({3, 0x800, 2, 0}); break;
    case 0x558C20: out.push_back({3, 1, w + 0x600, 0}); break;
    case 0x558C98: out.push_back({w, 1, 0, 0}); break;
    case 0x558D00: out.push_back({3, 0, 0, 0}); break;
    case 0x558D58: out.push_back({3, w + 0x1000, 0x800, 0}); break;
    case 0x555898: out.push_back({0, w + 0x600, 0, 0}); break;
    case 0x558988: out.push_back({0x4400, 0, 0, 0}); break;
    case 0x55DBC0: case 0x559FC0: case 0x55E378: out.push_back({0x57F750, 0x1234, 0, 0}); out.push_back({0, 0x1234, 0, 0}); break;
    case 0x55B5F0: out.push_back({1, 2, 3, 4}); break;
    case 0x55FB98: out.push_back({w + 0x600, 0, 0, 0}); break;
    case 0x55FBA0: out.push_back({0, w + 0x600, 0, 0}); break;
    case 0x55FC00: out.push_back({0, w + 0x1000, 0, 0}); break;
    case 0x559DA8: case 0x55B7C8: case 0x55E1D8: case 0x55EB08: out.push_back({0, w + 0x300, 0, 0}); break;
    case 0x551AD8: out.push_back({w + 0x4000, 0x1000, 0, 0}); break;
    case 0x551BB0: out.push_back({w + 0x4000, 0, 0, 0}); break;
    case 0x551BF0: out.push_back({w + 0x4000, w + 0x6000, 1, w + 0x7000}); break;
    case 0x552930: out.push_back({w + 0x600, w + 0x10000, 0x40000, 0}); out.push_back({w + 0x600, 0, 0, 0}); break;
    // the AHX decoder record built in the work area (state byte +5 0..3)
    case 0x551DF8: case 0x551F80: case 0x551FF8: case 0x552008: case 0x552028: case 0x552080: case 0x5520B0:
    case 0x552110: case 0x5523B8: case 0x552460: case 0x552468: case 0x552480: case 0x552520: case 0x552600:
        out.push_back({w + 0x5000, w + 0x5800, 0x1234, 0}); break;
    case 0x551E30: out.push_back({w + 0x5800, 2, w + 0x600, w + 0x5000}); break;
    case 0x55F1C8: out.push_back({w, 0, 0, 0}); break;
    case 0x55CF08: out.push_back({w, w + 0x400, 0, 0}); break;
    case 0x55EDB8: out.push_back({w + 0x600, 0, 0, 0}); break;
    default: out.push_back({0, 0, 0, 0}); break;  // the servers, inits and finishes (no argument)
    }
    return out;
}

// The work area of the snapshot sweep: names, an AHX decoder record, a hex-named handle, a delay count.
void prepare_work(Machine& m) {
    std::memset(m.at(kWork), 0, 0x10000);
    wstr(m, kWork, "data/sound/bgm.aix");
    wstr(m, kWork + 0x100, "\\DVD-ROM/");
    wstr(m, kWork + 0x200, "DVD-ROM");
    wstr(m, kWork + 0x300, "E0000000: error %d");
    w32(m, kWork + 0x600, 2);  // a delay count / a config word
    // AHX decoder: +0 the MPEG decoder, +12 the bit reader, +16 the input stream, +20 the output stream, +5 state 2
    w32(m, kWork + 0x5000, kWork + 0x9000);
    w32(m, kWork + 0x500C, kWork + 0x9800);
    w32(m, kWork + 0x5010, kWork + 0xA000);
    w32(m, kWork + 0x5014, kWork + 0xA000);
    m.at(kWork + 0x5005)[0] = 2;
    w32(m, kWork + 0x5030, 0xFFFFFFFFu);
    wstr(m, kWork + 0x800 + 28, "0000ABCD.00001234");
}

}  // namespace

TEST_CASE("game(libs10): every body equals its recompiled body on random worlds") {
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

// The replay snapshots hold the live CRI state of a running game: 7 DTR objects and 2 DTX records (the IOP transfer
// channels), 3 live DVD CI handles, 4 LSC streamers, the PS2RNA channel records; the AHX / AIX pools are idle (the
// game plays ADX). Every function runs on them with the records its role takes (live and free slots, NULL), names and
// buffers in the work area, and a built AHX decoder.
TEST_CASE("game(libs10): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* only = std::getenv("P3FES_HG_ONLY");
    int runs = 0, stops = 0;
    for (const char* dir : {"b_5800", "dorm_replay_4900"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            restore(*m, snap);
            prepare_work(*m);
            w32(*m, kSrdBusy, 0);  // the SRD server idle (SRD_WaitForExecServer would spin 0x19640000 times)
            for (const Args& a : recipes(c.addr)) {
                stops += pr(*m, c.addr, a, {{kDtxCreateRmt, 0x4000}}).stopped ? 1 : 0;
                ++runs;
            }
        }
    }
    MESSAGE(runs << " snapshot pairs, " << stops << " stopped early, identically (a callee another slice takes, an indirect call into an unbuilt record, the check-point cap)");
}

// The branches the snapshots do not reach, on built states, with the documented rules checked on the host.
TEST_CASE("game(libs10): built states and documented rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = snapshot("b_5800");
    if (snap.empty()) return;
    auto fresh = [&] {
        restore(*m, snap);
        prepare_work(*m);
        w32(*m, kSrdBusy, 0);
    };

    // SRD: create on the idle object, every status of the handle through destroy / wait / the DVD CI handle step.
    fresh();
    CHECK(uv32(v0of(pr(*m, 0x557A58, {}))) == kSrdObj);
    CHECK(m->at(kSrdObj)[0] == 1);
    CHECK(m->at(kSrdObj)[3] == 0xFF);
    CHECK(uv32(v0of(pr(*m, 0x557A58, {}))) == 0);  // busy: one request at a time
    for (u8 st : {0, 2, 3, 5, 9}) {
        for (u8 mode : {0, 1, 2}) {
            fresh();
            m->at(kSrdObj)[0] = 1;
            m->at(kSrdObj)[1] = mode;
            m->at(kSrdObj)[2] = st;
            pr(*m, 0x557E50, {kSrdObj, 0, 0, 0});
            if (st == 2 && mode != 1) CHECK(m->at(kSrdObj)[2] == 3);  // complete (the host wait ends on sceIoctl's 0)
            fresh();
            m->at(kSrdObj)[0] = 1;
            m->at(kSrdObj)[2] = st;
            pr(*m, 0x557AE0, {kSrdObj, 0, 0, 0});
            CHECK(m->at(kSrdObj)[0] == 0);
        }
        fresh();
        m->at(kSrdObj)[0] = 1;
        m->at(kSrdObj)[2] = st;
        const u32 h = kDvci + 37 * kDvciSize;  // a live handle
        w32(*m, h + 28, kSrdObj);
        w32(*m, h + 12, 0x1000);
        w32(*m, h + 16, 0x800);
        pr(*m, 0x559E80, {h, 0, 0, 0});
        if (st == 3) {
            CHECK(m->at(h + 2)[0] == 1);
            CHECK(r32(*m, h + 12) == 0x1800);  // pos += n
            CHECK(r32(*m, h + 28) == 0);
        }
        if (st == 9) CHECK(m->at(h + 2)[0] == 3);
    }
    for (u64 io : {0ull, 0xFFFFFFFFFFFFFFFBull}) {  // the host wait: done, then an sceIoctl error (status 9)
        fresh();
        pr(*m, 0x557D80, {kSrdObj, 0, 0, 0}, {{kSceIoctl, io}});
        if (io != 0) CHECK(m->at(kSrdObj)[2] == 9);
    }
    fresh();
    pr(*m, 0x557F80, {kSrdObj, 0, 0, 0});
    CHECK(r32(*m, kSrdObj + 4) == 1);
    pr(*m, 0x557F80, {kSrdObj, 0, 0, 0});  // "Already Break!"

    // SRD trace codes: previous <- current, current <- $a0.
    fresh();
    pr(*m, 0x558988, {0x4400, 0, 0, 0});
    pr(*m, 0x558988, {0x4401, 0, 0, 0});
    CHECK(r32(*m, 0x7A0918u) == 0x4400);
    CHECK(r32(*m, 0x7A091Cu) == 0x4401);

    // AHX synthesis: init builds the tables once, create takes slot 0, destroy frees it, finish clears at zero.
    fresh();
    w32(*m, kAhxSynRefs, 0);
    w32(*m, 0x798644u, 0);
    pr(*m, 0x551990, {});
    CHECK(r32(*m, kAhxSynRefs) == 1);
    CHECK(r32(*m, 0x798644u) == 1);
    CHECK((r32(*m, 0x79868Cu) & 31u) == 0);
    const u64 syn = v0of(pr(*m, 0x551AD8, {kWork + 0x4000, 0x1000, 0, 0}));
    CHECK(uv32(syn) == kWork + 0x4000);
    CHECK(r32(*m, kAhxSynSlots) == kWork + 0x4000);
    CHECK(r32(*m, kWork + 0x4004) == 64);
    pr(*m, 0x551BB0, {kWork + 0x4000, 0x1000, 0, 0});
    CHECK(r32(*m, kAhxSynSlots) == 0);
    pr(*m, 0x551990, {});
    pr(*m, 0x551A88, {});
    pr(*m, 0x551A88, {});
    CHECK(r32(*m, kAhxSynRefs) == 0);
    for (u32 i = 0; i < 16; ++i) w32(*m, kAhxSynSlots + 4 * i, kWork + 0x4000);  // full
    CHECK(v0of(pr(*m, 0x551AD8, {kWork + 0x4000, 0x1000, 0, 0})) == 0);
    w32(*m, kAhxDecRefs, 1);  // the decoder finish's last reference (stops at the synthesis finish, another slice's)
    pr(*m, 0x551DA0, {});
    w32(*m, kAhxDecRefs, 2);
    pr(*m, 0x551DA0, {});
    CHECK(r32(*m, kAhxDecRefs) == 1);

    // The AHX decoder's server in each state, its accessors, the counter reset.
    for (u8 st : {0, 1, 2, 3}) {
        fresh();
        m->at(kWork + 0x5005)[0] = st;
        pr(*m, 0x5523B8, {kWork + 0x5000, 0, 0, 0});
    }
    fresh();
    pr(*m, 0x551DF8, {kWork + 0x5000, 0, 0, 0});
    CHECK(r32(*m, kWork + 0x5030) == 0xFFFFFFFFu);
    CHECK(r32(*m, kWork + 0x502C) == 0x7FFFFFFFu);
    w32(*m, kAhxDecSlots + 4 * 3, kWork + 0x5000);
    w32(*m, kWork + 0x503C, 3);  // its slot
    w32(*m, kWork + 0x500C, 0);  // no bit reader, no MPEG decoder: only the clear
    w32(*m, kWork + 0x5000, 0);
    pr(*m, 0x551F80, {kWork + 0x5000, 0, 0, 0});
    CHECK(r32(*m, kAhxDecSlots + 4 * 3) == 0);
    CHECK(r32(*m, kWork + 0x5010) == 0);

    // AIX header: "AIXF", the header length, the (c)CRI tail; one segment, one layer, one track.
    fresh();
    {
        const u32 h = kWork + 0x2000;
        u8* p = m->at(h);
        std::memset(p, 0, 0x100);
        std::memcpy(p, "AIXF", 4);
        p[7] = 0x78;  // header length 0x78: data at 0x80
        p[8] = 1; p[9] = 2;
        p[10] = 0xAC; p[11] = 0x44;  // 44100
        p[15] = 0x10;
        p[25] = 1;   // one segment at +32
        p[35] = 0x80; p[39] = 0x40; p[43] = 0x20; p[47] = 0x05;
        p[48] = 1;   // one layer at +56
        p[56] = 0x12; p[57] = 0x34;
        p[64] = 1;   // one track at +72
        p[75] = 0x99; p[76] = 7;
        std::memcpy(p + 0x7A, "(c)CRI", 6);
        const u64 v0 = v0of(pr(*m, 0x554AE8, {h, 0x2000, kWork + 0x8000, 0}));
        CHECK(v0 == 0x80);
        const u32 o = kWork + 0x8000;
        CHECK(m->at(o)[0] == 1);
        CHECK(m->at(o + 1)[0] == 2);
        float rate;
        std::memcpy(&rate, m->at(o + 8), 4);
        CHECK(rate == 44100.0f);
        CHECK(r32(*m, o + 4) == 0x10);
        CHECK(r32(*m, o + 528) == 1);
        CHECK(r32(*m, o + 532) == 0x80);   // the segment: offset, size, ...
        CHECK(r32(*m, o + 536) == 0x40);
        CHECK(r32(*m, o + 6292) == 1);
        CHECK(m->at(o + 12)[0] == 1);
        std::memcpy(p + 0x7A, "(c)CRX", 6);  // a wrong tail: -1
        CHECK(sv(v0of(pr(*m, 0x554AE8, {h, 0x2000, kWork + 0x8000, 0}))) == -1);
        CHECK(sv(v0of(pr(*m, 0x554AE8, {h, 6143, kWork + 0x8000, 0}))) == -1);  // shorter than 6144
    }

    // AIXP_GetByteRate on NULL: the error text, -1.
    fresh();
    CHECK(sv(v0of(pr(*m, 0x553838, {0, 0, 0, 0}))) == -1);

    // File names: '/' -> '\', upper case; the root directory without its trailing separator.
    fresh();
    pr(*m, 0x559FD8, {kWork, 0, 0, 0});
    CHECK(rstr(*m, kWork) == "DATA\\SOUND\\BGM.AIX");
    wstr(*m, kWork, "data/");
    pr(*m, 0x55B610, {kWork, 0, 0, 0});
    CHECK(rstr(*m, kRootDir) == rstr(*m, 0x7C4E30u) + "data");
    wstr(*m, kWork, "/abs/");
    pr(*m, 0x55B610, {kWork, 0, 0, 0});
    CHECK(rstr(*m, kRootDir) == "/abs");
    pr(*m, 0x55B610, {0, 0, 0, 0});
    CHECK(m->at(kRootDir)[0] == 0);

    // PS2RNA configuration: 2 x nste + nmono channels, 16640 bytes of work each.
    fresh();
    CHECK(v0of(pr(*m, 0x55F688, {3, 4, 0, 0})) == 1);
    CHECK(r32(*m, 0x7A9418u) == 3);
    CHECK(r32(*m, 0x7A941Cu) == 4);
    CHECK(r32(*m, 0x7A93F0u) == 10);
    CHECK(r32(*m, 0x7A93F4u) == 16640u * 10u);
    w32(*m, 0x7A93F0u, 2);  // two channels, both taken: none free
    m->at(0x7A9450u)[0] = 1;
    m->at(0x7A9450u + 24)[0] = 1;
    CHECK(v0of(pr(*m, 0x55FB20, {})) == 0);
    m->at(0x7A9450u + 24)[0] = 0;
    CHECK(uv32(v0of(pr(*m, 0x55FB20, {}))) == 0x7A9450u + 24);
    pr(*m, 0x55FB98, {0x7A9450u + 24, 0, 0, 0});
    CHECK(m->at(0x7A9450u + 24)[0] == 0);

    // DTR create: the first free object of 32 (7 live in the snapshot).
    fresh();
    const u64 dtr = v0of(pr(*m, 0x559280, {0x1234, 0x5678, 0, 0}));
    CHECK(uv32(dtr) == kDtr + 7 * kDtrSize);
    CHECK(r32(*m, kDtr + 7 * kDtrSize + 4) == 0x1234);
    CHECK(r32(*m, kDtr + 7 * kDtrSize + 56) == 64);

    // DTX create on a free id: the record, its uncached work pointer.
    fresh();
    const u64 dtx = v0of(pr(*m, 0x559718, {5, kWork, 0x100000, 0x400}, {{kDtxCreateRmt, 0x4000}}));
    CHECK(uv32(dtx) == kDtx + 5 * kDtxSize);
    CHECK(r32(*m, kDtx + 5 * kDtxSize + 20) == ((kWork + 0x400 - 64) | 0x20000000u));
    CHECK(r32(*m, kDtx + 5 * kDtxSize + 16) == 0x400 - 64);

    // LSC entry: the id follows the last one, +8 the sum of the name's bytes.
    fresh();
    wstr(*m, kWork, "ab");
    const u32 lsc = kLsc;
    w32(*m, lsc + 36, 0);
    w32(*m, lsc + 28, 0);
    const s32 id = sv(v0of(pr(*m, 0x55D428, {lsc, kWork, 0x800, 0x40})));
    CHECK(r32(*m, lsc + 56 + 8) == u32('a') + u32('b'));
    CHECK(r32(*m, lsc + 36) == 1);
    CHECK(r32(*m, lsc + 28) == 1);
    CHECK(id == sv(r32(*m, lsc + 56)));
    w32(*m, lsc + 36, 16);  // the ring is full
    CHECK(sv(v0of(pr(*m, 0x55D428, {lsc, kWork, 0x800, 0x40}))) == -1);

    MESSAGE(summary());
}

#else

TEST_CASE("game(libs10): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
