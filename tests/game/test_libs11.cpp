// Pair tests for slice libs11 (game/src/cri/libs11.cpp): every hand body against its recompiled body, compared by
// tests/game/handgen_pairs.h -- the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window, the bus log and the stand-ins' call
// logs. Worlds: random ones, the three replay snapshots' CRI state (every function), and built records for the
// documented rules (PL2 encoder create / rate / position, the AIX player and parser records, the sector file handle,
// the HTCI name helpers and file-list split, the LSC queue, the DTX test reply), checked on the host as well.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs11.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_550808_00550808(EEContext&);  // generated body
void fn_sub_550808_00550808__recomp(EEContext&);  // recompiled
void fn_sub_5509F8_005509f8(EEContext&);  // generated body
void fn_sub_5509F8_005509f8__recomp(EEContext&);  // recompiled
void fn_sub_550BE8_00550be8(EEContext&);  // generated body
void fn_sub_550BE8_00550be8__recomp(EEContext&);  // recompiled
void fn_sub_550DD8_00550dd8(EEContext&);  // generated body
void fn_sub_550DD8_00550dd8__recomp(EEContext&);  // recompiled
void fn_sub_550FC8_00550fc8(EEContext&);  // generated body
void fn_sub_550FC8_00550fc8__recomp(EEContext&);  // recompiled
void fn_sub_5511B8_005511b8(EEContext&);  // generated body
void fn_sub_5511B8_005511b8__recomp(EEContext&);  // recompiled
void fn_sub_551980_00551980(EEContext&);  // generated body
void fn_sub_551980_00551980__recomp(EEContext&);  // recompiled
void fn_sub_551988_00551988(EEContext&);  // generated body
void fn_sub_551988_00551988__recomp(EEContext&);  // recompiled
void fn_sub_552000_00552000(EEContext&);  // generated body
void fn_sub_552000_00552000__recomp(EEContext&);  // recompiled
void fn_sub_552010_00552010(EEContext&);  // generated body
void fn_sub_552010_00552010__recomp(EEContext&);  // recompiled
void fn_sub_552020_00552020(EEContext&);  // generated body
void fn_sub_552020_00552020__recomp(EEContext&);  // recompiled
void fn_sub_5523F8_005523f8(EEContext&);  // generated body
void fn_sub_5523F8_005523f8__recomp(EEContext&);  // recompiled
void fn_sub_552478_00552478(EEContext&);  // generated body
void fn_sub_552478_00552478__recomp(EEContext&);  // recompiled
void fn_sub_552494_00552494(EEContext&);  // generated body
void fn_sub_552494_00552494__recomp(EEContext&);  // recompiled
void fn_sub_5524A8_005524a8(EEContext&);  // generated body
void fn_sub_5524A8_005524a8__recomp(EEContext&);  // recompiled
void fn_sub_5524B8_005524b8(EEContext&);  // generated body
void fn_sub_5524B8_005524b8__recomp(EEContext&);  // recompiled
void fn_sub_5524C8_005524c8(EEContext&);  // generated body
void fn_sub_5524C8_005524c8__recomp(EEContext&);  // recompiled
void fn_sub_5524D0_005524d0(EEContext&);  // generated body
void fn_sub_5524D0_005524d0__recomp(EEContext&);  // recompiled
void fn_sub_5524D8_005524d8(EEContext&);  // generated body
void fn_sub_5524D8_005524d8__recomp(EEContext&);  // recompiled
void fn_sub_5524F0_005524f0(EEContext&);  // generated body
void fn_sub_5524F0_005524f0__recomp(EEContext&);  // recompiled
void fn_sub_552538_00552538(EEContext&);  // generated body
void fn_sub_552538_00552538__recomp(EEContext&);  // recompiled
void fn_sub_552550_00552550(EEContext&);  // generated body
void fn_sub_552550_00552550__recomp(EEContext&);  // recompiled
void fn_sub_552558_00552558(EEContext&);  // generated body
void fn_sub_552558_00552558__recomp(EEContext&);  // recompiled
void fn_sub_552560_00552560(EEContext&);  // generated body
void fn_sub_552560_00552560__recomp(EEContext&);  // recompiled
void fn_sub_552568_00552568(EEContext&);  // generated body
void fn_sub_552568_00552568__recomp(EEContext&);  // recompiled
void fn_sub_552570_00552570(EEContext&);  // generated body
void fn_sub_552570_00552570__recomp(EEContext&);  // recompiled
void fn_sub_552578_00552578(EEContext&);  // generated body
void fn_sub_552578_00552578__recomp(EEContext&);  // recompiled
void fn_sub_552580_00552580(EEContext&);  // generated body
void fn_sub_552580_00552580__recomp(EEContext&);  // recompiled
void fn_sub_552588_00552588(EEContext&);  // generated body
void fn_sub_552588_00552588__recomp(EEContext&);  // recompiled
void fn_sub_5525A0_005525a0(EEContext&);  // generated body
void fn_sub_5525A0_005525a0__recomp(EEContext&);  // recompiled
void fn_sub_5525B8_005525b8(EEContext&);  // generated body
void fn_sub_5525B8_005525b8__recomp(EEContext&);  // recompiled
void fn_sub_5525D0_005525d0(EEContext&);  // generated body
void fn_sub_5525D0_005525d0__recomp(EEContext&);  // recompiled
void fn_sub_5525E8_005525e8(EEContext&);  // generated body
void fn_sub_5525E8_005525e8__recomp(EEContext&);  // recompiled
void fn_sub_552688_00552688(EEContext&);  // generated body
void fn_sub_552688_00552688__recomp(EEContext&);  // recompiled
void fn_sub_552D08_00552d08(EEContext&);  // generated body
void fn_sub_552D08_00552d08__recomp(EEContext&);  // recompiled
void fn_sub_552FA0_00552fa0(EEContext&);  // generated body
void fn_sub_552FA0_00552fa0__recomp(EEContext&);  // recompiled
void fn_sub_5531B8_005531b8(EEContext&);  // generated body
void fn_sub_5531B8_005531b8__recomp(EEContext&);  // recompiled
void fn_sub_553310_00553310(EEContext&);  // generated body
void fn_sub_553310_00553310__recomp(EEContext&);  // recompiled
void fn_sub_553358_00553358(EEContext&);  // generated body
void fn_sub_553358_00553358__recomp(EEContext&);  // recompiled
void fn_sub_553408_00553408(EEContext&);  // generated body
void fn_sub_553408_00553408__recomp(EEContext&);  // recompiled
void fn_sub_553438_00553438(EEContext&);  // generated body
void fn_sub_553438_00553438__recomp(EEContext&);  // recompiled
void fn_sub_553468_00553468(EEContext&);  // generated body
void fn_sub_553468_00553468__recomp(EEContext&);  // recompiled
void fn_sub_553498_00553498(EEContext&);  // generated body
void fn_sub_553498_00553498__recomp(EEContext&);  // recompiled
void fn_sub_553510_00553510(EEContext&);  // generated body
void fn_sub_553510_00553510__recomp(EEContext&);  // recompiled
void fn_sub_553560_00553560(EEContext&);  // generated body
void fn_sub_553560_00553560__recomp(EEContext&);  // recompiled
void fn_nullsub_143_00553688(EEContext&);  // generated body
void fn_nullsub_143_00553688__recomp(EEContext&);  // recompiled
void fn_sub_553690_00553690(EEContext&);  // generated body
void fn_sub_553690_00553690__recomp(EEContext&);  // recompiled
void fn_sub_553730_00553730(EEContext&);  // generated body
void fn_sub_553730_00553730__recomp(EEContext&);  // recompiled
void fn_sub_553788_00553788(EEContext&);  // generated body
void fn_sub_553788_00553788__recomp(EEContext&);  // recompiled
void fn_sub_5537E0_005537e0(EEContext&);  // generated body
void fn_sub_5537E0_005537e0__recomp(EEContext&);  // recompiled
void fn_sub_554008_00554008(EEContext&);  // generated body
void fn_sub_554008_00554008__recomp(EEContext&);  // recompiled
void fn_sub_5545D8_005545d8(EEContext&);  // generated body
void fn_sub_5545D8_005545d8__recomp(EEContext&);  // recompiled
void fn_sub_554678_00554678(EEContext&);  // generated body
void fn_sub_554678_00554678__recomp(EEContext&);  // recompiled
void fn_sub_554778_00554778(EEContext&);  // generated body
void fn_sub_554778_00554778__recomp(EEContext&);  // recompiled
void fn_sub_5547C8_005547c8(EEContext&);  // generated body
void fn_sub_5547C8_005547c8__recomp(EEContext&);  // recompiled
void fn_sub_554820_00554820(EEContext&);  // generated body
void fn_sub_554820_00554820__recomp(EEContext&);  // recompiled
void fn_sub_5548D0_005548d0(EEContext&);  // generated body
void fn_sub_5548D0_005548d0__recomp(EEContext&);  // recompiled
void fn_sub_554940_00554940(EEContext&);  // generated body
void fn_sub_554940_00554940__recomp(EEContext&);  // recompiled
void fn_sub_554950_00554950(EEContext&);  // generated body
void fn_sub_554950_00554950__recomp(EEContext&);  // recompiled
void fn_sub_554960_00554960(EEContext&);  // generated body
void fn_sub_554960_00554960__recomp(EEContext&);  // recompiled
void fn_sub_554970_00554970(EEContext&);  // generated body
void fn_sub_554970_00554970__recomp(EEContext&);  // recompiled
void fn_sub_554980_00554980(EEContext&);  // generated body
void fn_sub_554980_00554980__recomp(EEContext&);  // recompiled
void fn_sub_554EA0_00554ea0(EEContext&);  // generated body
void fn_sub_554EA0_00554ea0__recomp(EEContext&);  // recompiled
void fn_sub_554EF0_00554ef0(EEContext&);  // generated body
void fn_sub_554EF0_00554ef0__recomp(EEContext&);  // recompiled
void fn_sub_554FD0_00554fd0(EEContext&);  // generated body
void fn_sub_554FD0_00554fd0__recomp(EEContext&);  // recompiled
void fn_sub_555120_00555120(EEContext&);  // generated body
void fn_sub_555120_00555120__recomp(EEContext&);  // recompiled
void fn_sub_555470_00555470(EEContext&);  // generated body
void fn_sub_555470_00555470__recomp(EEContext&);  // recompiled
void fn_sub_555738_00555738(EEContext&);  // generated body
void fn_sub_555738_00555738__recomp(EEContext&);  // recompiled
void fn_sub_555788_00555788(EEContext&);  // generated body
void fn_sub_555788_00555788__recomp(EEContext&);  // recompiled
void fn_sub_557C70_00557c70(EEContext&);  // generated body
void fn_sub_557C70_00557c70__recomp(EEContext&);  // recompiled
void fn_sub_558320_00558320(EEContext&);  // generated body
void fn_sub_558320_00558320__recomp(EEContext&);  // recompiled
void fn_sub_5587A8_005587a8(EEContext&);  // generated body
void fn_sub_5587A8_005587a8__recomp(EEContext&);  // recompiled
void fn_sub_558848_00558848(EEContext&);  // generated body
void fn_sub_558848_00558848__recomp(EEContext&);  // recompiled
void fn_sub_5589B8_005589b8(EEContext&);  // generated body
void fn_sub_5589B8_005589b8__recomp(EEContext&);  // recompiled
void fn___errno_6_005589f8(EEContext&);  // generated body
void fn___errno_6_005589f8__recomp(EEContext&);  // recompiled
void fn___errno_7_00558a60(EEContext&);  // generated body
void fn___errno_7_00558a60__recomp(EEContext&);  // recompiled
void fn_sub_559458_00559458(EEContext&);  // generated body
void fn_sub_559458_00559458__recomp(EEContext&);  // recompiled
void fn_sub_559648_00559648(EEContext&);  // generated body
void fn_sub_559648_00559648__recomp(EEContext&);  // recompiled
void fn_sub_559660_00559660(EEContext&);  // generated body
void fn_sub_559660_00559660__recomp(EEContext&);  // recompiled
void fn_sub_55B480_0055b480(EEContext&);  // generated body
void fn_sub_55B480_0055b480__recomp(EEContext&);  // recompiled
void fn_sub_55B5C8_0055b5c8(EEContext&);  // generated body
void fn_sub_55B5C8_0055b5c8__recomp(EEContext&);  // recompiled
void fn_atan2l_7_0055b6e8(EEContext&);  // generated body
void fn_atan2l_7_0055b6e8__recomp(EEContext&);  // recompiled
void fn_sub_55B798_0055b798(EEContext&);  // generated body
void fn_sub_55B798_0055b798__recomp(EEContext&);  // recompiled
void fn_sub_55B7F8_0055b7f8(EEContext&);  // generated body
void fn_sub_55B7F8_0055b7f8__recomp(EEContext&);  // recompiled
void fn_sub_55B8B0_0055b8b0(EEContext&);  // generated body
void fn_sub_55B8B0_0055b8b0__recomp(EEContext&);  // recompiled
void fn_sub_55B910_0055b910(EEContext&);  // generated body
void fn_sub_55B910_0055b910__recomp(EEContext&);  // recompiled
void fn_sub_55BA68_0055ba68(EEContext&);  // generated body
void fn_sub_55BA68_0055ba68__recomp(EEContext&);  // recompiled
void fn_sub_55BCE8_0055bce8(EEContext&);  // generated body
void fn_sub_55BCE8_0055bce8__recomp(EEContext&);  // recompiled
void fn_sub_55BD70_0055bd70(EEContext&);  // generated body
void fn_sub_55BD70_0055bd70__recomp(EEContext&);  // recompiled
void fn_sub_55BFE0_0055bfe0(EEContext&);  // generated body
void fn_sub_55BFE0_0055bfe0__recomp(EEContext&);  // recompiled
void fn_sub_55C078_0055c078(EEContext&);  // generated body
void fn_sub_55C078_0055c078__recomp(EEContext&);  // recompiled
void fn_sub_55C0B0_0055c0b0(EEContext&);  // generated body
void fn_sub_55C0B0_0055c0b0__recomp(EEContext&);  // recompiled
void fn_sub_55C370_0055c370(EEContext&);  // generated body
void fn_sub_55C370_0055c370__recomp(EEContext&);  // recompiled
void fn_sub_55C378_0055c378(EEContext&);  // generated body
void fn_sub_55C378_0055c378__recomp(EEContext&);  // recompiled
void fn_sub_55C3E0_0055c3e0(EEContext&);  // generated body
void fn_sub_55C3E0_0055c3e0__recomp(EEContext&);  // recompiled
void fn_sub_55C400_0055c400(EEContext&);  // generated body
void fn_sub_55C400_0055c400__recomp(EEContext&);  // recompiled
void fn_sub_55C430_0055c430(EEContext&);  // generated body
void fn_sub_55C430_0055c430__recomp(EEContext&);  // recompiled
void fn_sub_55C450_0055c450(EEContext&);  // generated body
void fn_sub_55C450_0055c450__recomp(EEContext&);  // recompiled
void fn_sub_55C480_0055c480(EEContext&);  // generated body
void fn_sub_55C480_0055c480__recomp(EEContext&);  // recompiled
void fn_sub_55C548_0055c548(EEContext&);  // generated body
void fn_sub_55C548_0055c548__recomp(EEContext&);  // recompiled
void fn_sub_55C5B8_0055c5b8(EEContext&);  // generated body
void fn_sub_55C5B8_0055c5b8__recomp(EEContext&);  // recompiled
void fn_sub_55C728_0055c728(EEContext&);  // generated body
void fn_sub_55C728_0055c728__recomp(EEContext&);  // recompiled
void fn_sub_55C740_0055c740(EEContext&);  // generated body
void fn_sub_55C740_0055c740__recomp(EEContext&);  // recompiled
void fn_sub_55C798_0055c798(EEContext&);  // generated body
void fn_sub_55C798_0055c798__recomp(EEContext&);  // recompiled
void fn_sub_55C830_0055c830(EEContext&);  // generated body
void fn_sub_55C830_0055c830__recomp(EEContext&);  // recompiled
void fn_sub_55CB30_0055cb30(EEContext&);  // generated body
void fn_sub_55CB30_0055cb30__recomp(EEContext&);  // recompiled
void fn_sub_55CCE8_0055cce8(EEContext&);  // generated body
void fn_sub_55CCE8_0055cce8__recomp(EEContext&);  // recompiled
void fn_sub_55CE18_0055ce18(EEContext&);  // generated body
void fn_sub_55CE18_0055ce18__recomp(EEContext&);  // recompiled
void fn_sub_55D108_0055d108(EEContext&);  // generated body
void fn_sub_55D108_0055d108__recomp(EEContext&);  // recompiled
void fn_sub_55D198_0055d198(EEContext&);  // generated body
void fn_sub_55D198_0055d198__recomp(EEContext&);  // recompiled
void fn_WTLS_set_table_0055d220(EEContext&);  // generated body
void fn_WTLS_set_table_0055d220__recomp(EEContext&);  // recompiled
void fn_sub_55D400_0055d400(EEContext&);  // generated body
void fn_sub_55D400_0055d400__recomp(EEContext&);  // recompiled
void fn_sub_55D7F0_0055d7f0(EEContext&);  // generated body
void fn_sub_55D7F0_0055d7f0__recomp(EEContext&);  // recompiled
void fn_sub_55D880_0055d880(EEContext&);  // generated body
void fn_sub_55D880_0055d880__recomp(EEContext&);  // recompiled
void fn_sub_55D918_0055d918(EEContext&);  // generated body
void fn_sub_55D918_0055d918__recomp(EEContext&);  // recompiled
void fn_sub_55D9B0_0055d9b0(EEContext&);  // generated body
void fn_sub_55D9B0_0055d9b0__recomp(EEContext&);  // recompiled
void fn_sub_55DAB0_0055dab0(EEContext&);  // generated body
void fn_sub_55DAB0_0055dab0__recomp(EEContext&);  // recompiled
void fn_sub_55DB20_0055db20(EEContext&);  // generated body
void fn_sub_55DB20_0055db20__recomp(EEContext&);  // recompiled
void fn___env_unlock_7_0055dc80(EEContext&);  // generated body
void fn___env_unlock_7_0055dc80__recomp(EEContext&);  // recompiled
void fn_sub_55DDC8_0055ddc8(EEContext&);  // generated body
void fn_sub_55DDC8_0055ddc8__recomp(EEContext&);  // recompiled
void fn_sub_55DEF0_0055def0(EEContext&);  // generated body
void fn_sub_55DEF0_0055def0__recomp(EEContext&);  // recompiled
void fn_sub_55DFB8_0055dfb8(EEContext&);  // generated body
void fn_sub_55DFB8_0055dfb8__recomp(EEContext&);  // recompiled
void fn_sub_55E208_0055e208(EEContext&);  // generated body
void fn_sub_55E208_0055e208__recomp(EEContext&);  // recompiled
void fn_sub_55E318_0055e318(EEContext&);  // generated body
void fn_sub_55E318_0055e318__recomp(EEContext&);  // recompiled
void fn_sub_55E408_0055e408(EEContext&);  // generated body
void fn_sub_55E408_0055e408__recomp(EEContext&);  // recompiled
void fn_sub_55E800_0055e800(EEContext&);  // generated body
void fn_sub_55E800_0055e800__recomp(EEContext&);  // recompiled
void fn_sub_55EAB0_0055eab0(EEContext&);  // generated body
void fn_sub_55EAB0_0055eab0__recomp(EEContext&);  // recompiled
void fn_sub_55EAF0_0055eaf0(EEContext&);  // generated body
void fn_sub_55EAF0_0055eaf0__recomp(EEContext&);  // recompiled
void fn_sub_55EB38_0055eb38(EEContext&);  // generated body
void fn_sub_55EB38_0055eb38__recomp(EEContext&);  // recompiled
void fn_sub_55EB68_0055eb68(EEContext&);  // generated body
void fn_sub_55EB68_0055eb68__recomp(EEContext&);  // recompiled
void fn_sub_55EBA8_0055eba8(EEContext&);  // generated body
void fn_sub_55EBA8_0055eba8__recomp(EEContext&);  // recompiled
void fn_sub_55EBD8_0055ebd8(EEContext&);  // generated body
void fn_sub_55EBD8_0055ebd8__recomp(EEContext&);  // recompiled
void fn_sub_55EBF0_0055ebf0(EEContext&);  // generated body
void fn_sub_55EBF0_0055ebf0__recomp(EEContext&);  // recompiled
void fn_sub_55EC38_0055ec38(EEContext&);  // generated body
void fn_sub_55EC38_0055ec38__recomp(EEContext&);  // recompiled
void fn_sub_55ED38_0055ed38(EEContext&);  // generated body
void fn_sub_55ED38_0055ed38__recomp(EEContext&);  // recompiled
void fn_sub_55ED68_0055ed68(EEContext&);  // generated body
void fn_sub_55ED68_0055ed68__recomp(EEContext&);  // recompiled
void fn_sub_55ED88_0055ed88(EEContext&);  // generated body
void fn_sub_55ED88_0055ed88__recomp(EEContext&);  // recompiled
void fn_sub_55EDF8_0055edf8(EEContext&);  // generated body
void fn_sub_55EDF8_0055edf8__recomp(EEContext&);  // recompiled
void fn_sub_55EE58_0055ee58(EEContext&);  // generated body
void fn_sub_55EE58_0055ee58__recomp(EEContext&);  // recompiled
void fn_sub_55F028_0055f028(EEContext&);  // generated body
void fn_sub_55F028_0055f028__recomp(EEContext&);  // recompiled
void fn_sub_55F218_0055f218(EEContext&);  // generated body
void fn_sub_55F218_0055f218__recomp(EEContext&);  // recompiled
void fn_sub_55F2C8_0055f2c8(EEContext&);  // generated body
void fn_sub_55F2C8_0055f2c8__recomp(EEContext&);  // recompiled
void fn_sub_55F308_0055f308(EEContext&);  // generated body
void fn_sub_55F308_0055f308__recomp(EEContext&);  // recompiled
void fn_sub_55F390_0055f390(EEContext&);  // generated body
void fn_sub_55F390_0055f390__recomp(EEContext&);  // recompiled
void fn_sub_55F4C8_0055f4c8(EEContext&);  // generated body
void fn_sub_55F4C8_0055f4c8__recomp(EEContext&);  // recompiled
void fn_sub_55F598_0055f598(EEContext&);  // generated body
void fn_sub_55F598_0055f598__recomp(EEContext&);  // recompiled
void fn_sub_55F608_0055f608(EEContext&);  // generated body
void fn_sub_55F608_0055f608__recomp(EEContext&);  // recompiled
void fn_sub_55F620_0055f620(EEContext&);  // generated body
void fn_sub_55F620_0055f620__recomp(EEContext&);  // recompiled
void fn_sub_55F658_0055f658(EEContext&);  // generated body
void fn_sub_55F658_0055f658__recomp(EEContext&);  // recompiled
void fn_sub_55F670_0055f670(EEContext&);  // generated body
void fn_sub_55F670_0055f670__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_550808", 0x550808, &recomp_gen::fn_sub_550808_00550808, &recomp_gen::fn_sub_550808_00550808__recomp},
    {"sub_5509F8", 0x5509F8, &recomp_gen::fn_sub_5509F8_005509f8, &recomp_gen::fn_sub_5509F8_005509f8__recomp},
    {"sub_550BE8", 0x550BE8, &recomp_gen::fn_sub_550BE8_00550be8, &recomp_gen::fn_sub_550BE8_00550be8__recomp},
    {"sub_550DD8", 0x550DD8, &recomp_gen::fn_sub_550DD8_00550dd8, &recomp_gen::fn_sub_550DD8_00550dd8__recomp},
    {"sub_550FC8", 0x550FC8, &recomp_gen::fn_sub_550FC8_00550fc8, &recomp_gen::fn_sub_550FC8_00550fc8__recomp},
    {"sub_5511B8", 0x5511B8, &recomp_gen::fn_sub_5511B8_005511b8, &recomp_gen::fn_sub_5511B8_005511b8__recomp},
    {"sub_551980", 0x551980, &recomp_gen::fn_sub_551980_00551980, &recomp_gen::fn_sub_551980_00551980__recomp},
    {"sub_551988", 0x551988, &recomp_gen::fn_sub_551988_00551988, &recomp_gen::fn_sub_551988_00551988__recomp},
    {"sub_552000", 0x552000, &recomp_gen::fn_sub_552000_00552000, &recomp_gen::fn_sub_552000_00552000__recomp},
    {"sub_552010", 0x552010, &recomp_gen::fn_sub_552010_00552010, &recomp_gen::fn_sub_552010_00552010__recomp},
    {"sub_552020", 0x552020, &recomp_gen::fn_sub_552020_00552020, &recomp_gen::fn_sub_552020_00552020__recomp},
    {"sub_5523F8", 0x5523F8, &recomp_gen::fn_sub_5523F8_005523f8, &recomp_gen::fn_sub_5523F8_005523f8__recomp},
    {"sub_552478", 0x552478, &recomp_gen::fn_sub_552478_00552478, &recomp_gen::fn_sub_552478_00552478__recomp},
    {"sub_552494", 0x552494, &recomp_gen::fn_sub_552494_00552494, &recomp_gen::fn_sub_552494_00552494__recomp},
    {"sub_5524A8", 0x5524A8, &recomp_gen::fn_sub_5524A8_005524a8, &recomp_gen::fn_sub_5524A8_005524a8__recomp},
    {"sub_5524B8", 0x5524B8, &recomp_gen::fn_sub_5524B8_005524b8, &recomp_gen::fn_sub_5524B8_005524b8__recomp},
    {"sub_5524C8", 0x5524C8, &recomp_gen::fn_sub_5524C8_005524c8, &recomp_gen::fn_sub_5524C8_005524c8__recomp},
    {"sub_5524D0", 0x5524D0, &recomp_gen::fn_sub_5524D0_005524d0, &recomp_gen::fn_sub_5524D0_005524d0__recomp},
    {"sub_5524D8", 0x5524D8, &recomp_gen::fn_sub_5524D8_005524d8, &recomp_gen::fn_sub_5524D8_005524d8__recomp},
    {"sub_5524F0", 0x5524F0, &recomp_gen::fn_sub_5524F0_005524f0, &recomp_gen::fn_sub_5524F0_005524f0__recomp},
    {"sub_552538", 0x552538, &recomp_gen::fn_sub_552538_00552538, &recomp_gen::fn_sub_552538_00552538__recomp},
    {"sub_552550", 0x552550, &recomp_gen::fn_sub_552550_00552550, &recomp_gen::fn_sub_552550_00552550__recomp},
    {"sub_552558", 0x552558, &recomp_gen::fn_sub_552558_00552558, &recomp_gen::fn_sub_552558_00552558__recomp},
    {"sub_552560", 0x552560, &recomp_gen::fn_sub_552560_00552560, &recomp_gen::fn_sub_552560_00552560__recomp},
    {"sub_552568", 0x552568, &recomp_gen::fn_sub_552568_00552568, &recomp_gen::fn_sub_552568_00552568__recomp},
    {"sub_552570", 0x552570, &recomp_gen::fn_sub_552570_00552570, &recomp_gen::fn_sub_552570_00552570__recomp},
    {"sub_552578", 0x552578, &recomp_gen::fn_sub_552578_00552578, &recomp_gen::fn_sub_552578_00552578__recomp},
    {"sub_552580", 0x552580, &recomp_gen::fn_sub_552580_00552580, &recomp_gen::fn_sub_552580_00552580__recomp},
    {"sub_552588", 0x552588, &recomp_gen::fn_sub_552588_00552588, &recomp_gen::fn_sub_552588_00552588__recomp},
    {"sub_5525A0", 0x5525A0, &recomp_gen::fn_sub_5525A0_005525a0, &recomp_gen::fn_sub_5525A0_005525a0__recomp},
    {"sub_5525B8", 0x5525B8, &recomp_gen::fn_sub_5525B8_005525b8, &recomp_gen::fn_sub_5525B8_005525b8__recomp},
    {"sub_5525D0", 0x5525D0, &recomp_gen::fn_sub_5525D0_005525d0, &recomp_gen::fn_sub_5525D0_005525d0__recomp},
    {"sub_5525E8", 0x5525E8, &recomp_gen::fn_sub_5525E8_005525e8, &recomp_gen::fn_sub_5525E8_005525e8__recomp},
    {"sub_552688", 0x552688, &recomp_gen::fn_sub_552688_00552688, &recomp_gen::fn_sub_552688_00552688__recomp},
    {"sub_552D08", 0x552D08, &recomp_gen::fn_sub_552D08_00552d08, &recomp_gen::fn_sub_552D08_00552d08__recomp},
    {"sub_552FA0", 0x552FA0, &recomp_gen::fn_sub_552FA0_00552fa0, &recomp_gen::fn_sub_552FA0_00552fa0__recomp},
    {"sub_5531B8", 0x5531B8, &recomp_gen::fn_sub_5531B8_005531b8, &recomp_gen::fn_sub_5531B8_005531b8__recomp},
    {"sub_553310", 0x553310, &recomp_gen::fn_sub_553310_00553310, &recomp_gen::fn_sub_553310_00553310__recomp},
    {"sub_553358", 0x553358, &recomp_gen::fn_sub_553358_00553358, &recomp_gen::fn_sub_553358_00553358__recomp},
    {"sub_553408", 0x553408, &recomp_gen::fn_sub_553408_00553408, &recomp_gen::fn_sub_553408_00553408__recomp},
    {"sub_553438", 0x553438, &recomp_gen::fn_sub_553438_00553438, &recomp_gen::fn_sub_553438_00553438__recomp},
    {"sub_553468", 0x553468, &recomp_gen::fn_sub_553468_00553468, &recomp_gen::fn_sub_553468_00553468__recomp},
    {"sub_553498", 0x553498, &recomp_gen::fn_sub_553498_00553498, &recomp_gen::fn_sub_553498_00553498__recomp},
    {"sub_553510", 0x553510, &recomp_gen::fn_sub_553510_00553510, &recomp_gen::fn_sub_553510_00553510__recomp},
    {"sub_553560", 0x553560, &recomp_gen::fn_sub_553560_00553560, &recomp_gen::fn_sub_553560_00553560__recomp},
    {"nullsub_143", 0x553688, &recomp_gen::fn_nullsub_143_00553688, &recomp_gen::fn_nullsub_143_00553688__recomp},
    {"sub_553690", 0x553690, &recomp_gen::fn_sub_553690_00553690, &recomp_gen::fn_sub_553690_00553690__recomp},
    {"sub_553730", 0x553730, &recomp_gen::fn_sub_553730_00553730, &recomp_gen::fn_sub_553730_00553730__recomp},
    {"sub_553788", 0x553788, &recomp_gen::fn_sub_553788_00553788, &recomp_gen::fn_sub_553788_00553788__recomp},
    {"sub_5537E0", 0x5537E0, &recomp_gen::fn_sub_5537E0_005537e0, &recomp_gen::fn_sub_5537E0_005537e0__recomp},
    {"sub_554008", 0x554008, &recomp_gen::fn_sub_554008_00554008, &recomp_gen::fn_sub_554008_00554008__recomp},
    {"sub_5545D8", 0x5545D8, &recomp_gen::fn_sub_5545D8_005545d8, &recomp_gen::fn_sub_5545D8_005545d8__recomp},
    {"sub_554678", 0x554678, &recomp_gen::fn_sub_554678_00554678, &recomp_gen::fn_sub_554678_00554678__recomp},
    {"sub_554778", 0x554778, &recomp_gen::fn_sub_554778_00554778, &recomp_gen::fn_sub_554778_00554778__recomp},
    {"sub_5547C8", 0x5547C8, &recomp_gen::fn_sub_5547C8_005547c8, &recomp_gen::fn_sub_5547C8_005547c8__recomp},
    {"sub_554820", 0x554820, &recomp_gen::fn_sub_554820_00554820, &recomp_gen::fn_sub_554820_00554820__recomp},
    {"sub_5548D0", 0x5548D0, &recomp_gen::fn_sub_5548D0_005548d0, &recomp_gen::fn_sub_5548D0_005548d0__recomp},
    {"sub_554940", 0x554940, &recomp_gen::fn_sub_554940_00554940, &recomp_gen::fn_sub_554940_00554940__recomp},
    {"sub_554950", 0x554950, &recomp_gen::fn_sub_554950_00554950, &recomp_gen::fn_sub_554950_00554950__recomp},
    {"sub_554960", 0x554960, &recomp_gen::fn_sub_554960_00554960, &recomp_gen::fn_sub_554960_00554960__recomp},
    {"sub_554970", 0x554970, &recomp_gen::fn_sub_554970_00554970, &recomp_gen::fn_sub_554970_00554970__recomp},
    {"sub_554980", 0x554980, &recomp_gen::fn_sub_554980_00554980, &recomp_gen::fn_sub_554980_00554980__recomp},
    {"sub_554EA0", 0x554EA0, &recomp_gen::fn_sub_554EA0_00554ea0, &recomp_gen::fn_sub_554EA0_00554ea0__recomp},
    {"sub_554EF0", 0x554EF0, &recomp_gen::fn_sub_554EF0_00554ef0, &recomp_gen::fn_sub_554EF0_00554ef0__recomp},
    {"sub_554FD0", 0x554FD0, &recomp_gen::fn_sub_554FD0_00554fd0, &recomp_gen::fn_sub_554FD0_00554fd0__recomp},
    {"sub_555120", 0x555120, &recomp_gen::fn_sub_555120_00555120, &recomp_gen::fn_sub_555120_00555120__recomp},
    {"sub_555470", 0x555470, &recomp_gen::fn_sub_555470_00555470, &recomp_gen::fn_sub_555470_00555470__recomp},
    {"sub_555738", 0x555738, &recomp_gen::fn_sub_555738_00555738, &recomp_gen::fn_sub_555738_00555738__recomp},
    {"sub_555788", 0x555788, &recomp_gen::fn_sub_555788_00555788, &recomp_gen::fn_sub_555788_00555788__recomp},
    {"sub_557C70", 0x557C70, &recomp_gen::fn_sub_557C70_00557c70, &recomp_gen::fn_sub_557C70_00557c70__recomp},
    {"sub_558320", 0x558320, &recomp_gen::fn_sub_558320_00558320, &recomp_gen::fn_sub_558320_00558320__recomp},
    {"sub_5587A8", 0x5587A8, &recomp_gen::fn_sub_5587A8_005587a8, &recomp_gen::fn_sub_5587A8_005587a8__recomp},
    {"sub_558848", 0x558848, &recomp_gen::fn_sub_558848_00558848, &recomp_gen::fn_sub_558848_00558848__recomp},
    {"sub_5589B8", 0x5589B8, &recomp_gen::fn_sub_5589B8_005589b8, &recomp_gen::fn_sub_5589B8_005589b8__recomp},
    {"__errno_6", 0x5589F8, &recomp_gen::fn___errno_6_005589f8, &recomp_gen::fn___errno_6_005589f8__recomp},
    {"__errno_7", 0x558A60, &recomp_gen::fn___errno_7_00558a60, &recomp_gen::fn___errno_7_00558a60__recomp},
    {"sub_559458", 0x559458, &recomp_gen::fn_sub_559458_00559458, &recomp_gen::fn_sub_559458_00559458__recomp},
    {"sub_559648", 0x559648, &recomp_gen::fn_sub_559648_00559648, &recomp_gen::fn_sub_559648_00559648__recomp},
    {"sub_559660", 0x559660, &recomp_gen::fn_sub_559660_00559660, &recomp_gen::fn_sub_559660_00559660__recomp},
    {"sub_55B480", 0x55B480, &recomp_gen::fn_sub_55B480_0055b480, &recomp_gen::fn_sub_55B480_0055b480__recomp},
    {"sub_55B5C8", 0x55B5C8, &recomp_gen::fn_sub_55B5C8_0055b5c8, &recomp_gen::fn_sub_55B5C8_0055b5c8__recomp},
    {"atan2l_7", 0x55B6E8, &recomp_gen::fn_atan2l_7_0055b6e8, &recomp_gen::fn_atan2l_7_0055b6e8__recomp},
    {"sub_55B798", 0x55B798, &recomp_gen::fn_sub_55B798_0055b798, &recomp_gen::fn_sub_55B798_0055b798__recomp},
    {"sub_55B7F8", 0x55B7F8, &recomp_gen::fn_sub_55B7F8_0055b7f8, &recomp_gen::fn_sub_55B7F8_0055b7f8__recomp},
    {"sub_55B8B0", 0x55B8B0, &recomp_gen::fn_sub_55B8B0_0055b8b0, &recomp_gen::fn_sub_55B8B0_0055b8b0__recomp},
    {"sub_55B910", 0x55B910, &recomp_gen::fn_sub_55B910_0055b910, &recomp_gen::fn_sub_55B910_0055b910__recomp},
    {"sub_55BA68", 0x55BA68, &recomp_gen::fn_sub_55BA68_0055ba68, &recomp_gen::fn_sub_55BA68_0055ba68__recomp},
    {"sub_55BCE8", 0x55BCE8, &recomp_gen::fn_sub_55BCE8_0055bce8, &recomp_gen::fn_sub_55BCE8_0055bce8__recomp},
    {"sub_55BD70", 0x55BD70, &recomp_gen::fn_sub_55BD70_0055bd70, &recomp_gen::fn_sub_55BD70_0055bd70__recomp},
    {"sub_55BFE0", 0x55BFE0, &recomp_gen::fn_sub_55BFE0_0055bfe0, &recomp_gen::fn_sub_55BFE0_0055bfe0__recomp},
    {"sub_55C078", 0x55C078, &recomp_gen::fn_sub_55C078_0055c078, &recomp_gen::fn_sub_55C078_0055c078__recomp},
    {"sub_55C0B0", 0x55C0B0, &recomp_gen::fn_sub_55C0B0_0055c0b0, &recomp_gen::fn_sub_55C0B0_0055c0b0__recomp},
    {"sub_55C370", 0x55C370, &recomp_gen::fn_sub_55C370_0055c370, &recomp_gen::fn_sub_55C370_0055c370__recomp},
    {"sub_55C378", 0x55C378, &recomp_gen::fn_sub_55C378_0055c378, &recomp_gen::fn_sub_55C378_0055c378__recomp},
    {"sub_55C3E0", 0x55C3E0, &recomp_gen::fn_sub_55C3E0_0055c3e0, &recomp_gen::fn_sub_55C3E0_0055c3e0__recomp},
    {"sub_55C400", 0x55C400, &recomp_gen::fn_sub_55C400_0055c400, &recomp_gen::fn_sub_55C400_0055c400__recomp},
    {"sub_55C430", 0x55C430, &recomp_gen::fn_sub_55C430_0055c430, &recomp_gen::fn_sub_55C430_0055c430__recomp},
    {"sub_55C450", 0x55C450, &recomp_gen::fn_sub_55C450_0055c450, &recomp_gen::fn_sub_55C450_0055c450__recomp},
    {"sub_55C480", 0x55C480, &recomp_gen::fn_sub_55C480_0055c480, &recomp_gen::fn_sub_55C480_0055c480__recomp},
    {"sub_55C548", 0x55C548, &recomp_gen::fn_sub_55C548_0055c548, &recomp_gen::fn_sub_55C548_0055c548__recomp},
    {"sub_55C5B8", 0x55C5B8, &recomp_gen::fn_sub_55C5B8_0055c5b8, &recomp_gen::fn_sub_55C5B8_0055c5b8__recomp},
    {"sub_55C728", 0x55C728, &recomp_gen::fn_sub_55C728_0055c728, &recomp_gen::fn_sub_55C728_0055c728__recomp},
    {"sub_55C740", 0x55C740, &recomp_gen::fn_sub_55C740_0055c740, &recomp_gen::fn_sub_55C740_0055c740__recomp},
    {"sub_55C798", 0x55C798, &recomp_gen::fn_sub_55C798_0055c798, &recomp_gen::fn_sub_55C798_0055c798__recomp},
    {"sub_55C830", 0x55C830, &recomp_gen::fn_sub_55C830_0055c830, &recomp_gen::fn_sub_55C830_0055c830__recomp},
    {"sub_55CB30", 0x55CB30, &recomp_gen::fn_sub_55CB30_0055cb30, &recomp_gen::fn_sub_55CB30_0055cb30__recomp},
    {"sub_55CCE8", 0x55CCE8, &recomp_gen::fn_sub_55CCE8_0055cce8, &recomp_gen::fn_sub_55CCE8_0055cce8__recomp},
    {"sub_55CE18", 0x55CE18, &recomp_gen::fn_sub_55CE18_0055ce18, &recomp_gen::fn_sub_55CE18_0055ce18__recomp},
    {"sub_55D108", 0x55D108, &recomp_gen::fn_sub_55D108_0055d108, &recomp_gen::fn_sub_55D108_0055d108__recomp},
    {"sub_55D198", 0x55D198, &recomp_gen::fn_sub_55D198_0055d198, &recomp_gen::fn_sub_55D198_0055d198__recomp},
    {"WTLS_set_table", 0x55D220, &recomp_gen::fn_WTLS_set_table_0055d220, &recomp_gen::fn_WTLS_set_table_0055d220__recomp},
    {"sub_55D400", 0x55D400, &recomp_gen::fn_sub_55D400_0055d400, &recomp_gen::fn_sub_55D400_0055d400__recomp},
    {"sub_55D7F0", 0x55D7F0, &recomp_gen::fn_sub_55D7F0_0055d7f0, &recomp_gen::fn_sub_55D7F0_0055d7f0__recomp},
    {"sub_55D880", 0x55D880, &recomp_gen::fn_sub_55D880_0055d880, &recomp_gen::fn_sub_55D880_0055d880__recomp},
    {"sub_55D918", 0x55D918, &recomp_gen::fn_sub_55D918_0055d918, &recomp_gen::fn_sub_55D918_0055d918__recomp},
    {"sub_55D9B0", 0x55D9B0, &recomp_gen::fn_sub_55D9B0_0055d9b0, &recomp_gen::fn_sub_55D9B0_0055d9b0__recomp},
    {"sub_55DAB0", 0x55DAB0, &recomp_gen::fn_sub_55DAB0_0055dab0, &recomp_gen::fn_sub_55DAB0_0055dab0__recomp},
    {"sub_55DB20", 0x55DB20, &recomp_gen::fn_sub_55DB20_0055db20, &recomp_gen::fn_sub_55DB20_0055db20__recomp},
    {"__env_unlock_7", 0x55DC80, &recomp_gen::fn___env_unlock_7_0055dc80, &recomp_gen::fn___env_unlock_7_0055dc80__recomp},
    {"sub_55DDC8", 0x55DDC8, &recomp_gen::fn_sub_55DDC8_0055ddc8, &recomp_gen::fn_sub_55DDC8_0055ddc8__recomp},
    {"sub_55DEF0", 0x55DEF0, &recomp_gen::fn_sub_55DEF0_0055def0, &recomp_gen::fn_sub_55DEF0_0055def0__recomp},
    {"sub_55DFB8", 0x55DFB8, &recomp_gen::fn_sub_55DFB8_0055dfb8, &recomp_gen::fn_sub_55DFB8_0055dfb8__recomp},
    {"sub_55E208", 0x55E208, &recomp_gen::fn_sub_55E208_0055e208, &recomp_gen::fn_sub_55E208_0055e208__recomp},
    {"sub_55E318", 0x55E318, &recomp_gen::fn_sub_55E318_0055e318, &recomp_gen::fn_sub_55E318_0055e318__recomp},
    {"sub_55E408", 0x55E408, &recomp_gen::fn_sub_55E408_0055e408, &recomp_gen::fn_sub_55E408_0055e408__recomp},
    {"sub_55E800", 0x55E800, &recomp_gen::fn_sub_55E800_0055e800, &recomp_gen::fn_sub_55E800_0055e800__recomp},
    {"sub_55EAB0", 0x55EAB0, &recomp_gen::fn_sub_55EAB0_0055eab0, &recomp_gen::fn_sub_55EAB0_0055eab0__recomp},
    {"sub_55EAF0", 0x55EAF0, &recomp_gen::fn_sub_55EAF0_0055eaf0, &recomp_gen::fn_sub_55EAF0_0055eaf0__recomp},
    {"sub_55EB38", 0x55EB38, &recomp_gen::fn_sub_55EB38_0055eb38, &recomp_gen::fn_sub_55EB38_0055eb38__recomp},
    {"sub_55EB68", 0x55EB68, &recomp_gen::fn_sub_55EB68_0055eb68, &recomp_gen::fn_sub_55EB68_0055eb68__recomp},
    {"sub_55EBA8", 0x55EBA8, &recomp_gen::fn_sub_55EBA8_0055eba8, &recomp_gen::fn_sub_55EBA8_0055eba8__recomp},
    {"sub_55EBD8", 0x55EBD8, &recomp_gen::fn_sub_55EBD8_0055ebd8, &recomp_gen::fn_sub_55EBD8_0055ebd8__recomp},
    {"sub_55EBF0", 0x55EBF0, &recomp_gen::fn_sub_55EBF0_0055ebf0, &recomp_gen::fn_sub_55EBF0_0055ebf0__recomp},
    {"sub_55EC38", 0x55EC38, &recomp_gen::fn_sub_55EC38_0055ec38, &recomp_gen::fn_sub_55EC38_0055ec38__recomp},
    {"sub_55ED38", 0x55ED38, &recomp_gen::fn_sub_55ED38_0055ed38, &recomp_gen::fn_sub_55ED38_0055ed38__recomp},
    {"sub_55ED68", 0x55ED68, &recomp_gen::fn_sub_55ED68_0055ed68, &recomp_gen::fn_sub_55ED68_0055ed68__recomp},
    {"sub_55ED88", 0x55ED88, &recomp_gen::fn_sub_55ED88_0055ed88, &recomp_gen::fn_sub_55ED88_0055ed88__recomp},
    {"sub_55EDF8", 0x55EDF8, &recomp_gen::fn_sub_55EDF8_0055edf8, &recomp_gen::fn_sub_55EDF8_0055edf8__recomp},
    {"sub_55EE58", 0x55EE58, &recomp_gen::fn_sub_55EE58_0055ee58, &recomp_gen::fn_sub_55EE58_0055ee58__recomp},
    {"sub_55F028", 0x55F028, &recomp_gen::fn_sub_55F028_0055f028, &recomp_gen::fn_sub_55F028_0055f028__recomp},
    {"sub_55F218", 0x55F218, &recomp_gen::fn_sub_55F218_0055f218, &recomp_gen::fn_sub_55F218_0055f218__recomp},
    {"sub_55F2C8", 0x55F2C8, &recomp_gen::fn_sub_55F2C8_0055f2c8, &recomp_gen::fn_sub_55F2C8_0055f2c8__recomp},
    {"sub_55F308", 0x55F308, &recomp_gen::fn_sub_55F308_0055f308, &recomp_gen::fn_sub_55F308_0055f308__recomp},
    {"sub_55F390", 0x55F390, &recomp_gen::fn_sub_55F390_0055f390, &recomp_gen::fn_sub_55F390_0055f390__recomp},
    {"sub_55F4C8", 0x55F4C8, &recomp_gen::fn_sub_55F4C8_0055f4c8, &recomp_gen::fn_sub_55F4C8_0055f4c8__recomp},
    {"sub_55F598", 0x55F598, &recomp_gen::fn_sub_55F598_0055f598, &recomp_gen::fn_sub_55F598_0055f598__recomp},
    {"sub_55F608", 0x55F608, &recomp_gen::fn_sub_55F608_0055f608, &recomp_gen::fn_sub_55F608_0055f608__recomp},
    {"sub_55F620", 0x55F620, &recomp_gen::fn_sub_55F620_0055f620, &recomp_gen::fn_sub_55F620_0055f620__recomp},
    {"sub_55F658", 0x55F658, &recomp_gen::fn_sub_55F658_0055f658, &recomp_gen::fn_sub_55F658_0055f658__recomp},
    {"sub_55F670", 0x55F670, &recomp_gen::fn_sub_55F670_0055f670, &recomp_gen::fn_sub_55F670_0055f670__recomp},
};


// ---- the world --------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;  // free RAM for random worlds and built records
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;
constexpr u32 kRec = 0x01820000u;    // a built record (8 KiB)
constexpr u32 kOut = 0x01822000u;    // out-parameters / buffers (8 KiB)
const char* const kSnaps[] = {"b_5800", "dorm_replay_4900", "climb_ref_17000"};

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    throw std::runtime_error("libs11: no case for an address");
}
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
void put(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
std::string str(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va))); }

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}

// ---- the stand-ins ------------------------------------------------------------------------------------------------
// Callees this test binary does not emit and no current packet takes: recorders returning `g_v0` (the SVM lock /
// unlock callbacks 0x53F8B8 / 0x53F940 the CRI lock wrappers reach on the snapshots, as test_cri1 does, the ADX error
// handler, the SRD DVD layer, the AIX / LSC / DVCI helpers other tests also stand in), sprintf with its real effect.
// What other packets take (the libs10 SRD / HTCI / LSC core, the libs8 debug printers) is emitted through _callees when
// it is safe, else the pair stops there identically.
const u32 kRecorders[] = {0x53AE08u, 0x552658u, 0x552680u, 0x558768u, 0x558AE0u, 0x505E48u, 0x552BD0u, 0x5530D0u,
                          0x553188u, 0x55AB80u, 0x55AEA0u, 0x55B0F8u, 0x5460E0u, 0x546270u, 0x5463A8u, 0x546498u,
                          0x5465A0u, 0x546718u, 0x546FA0u, 0x546368u, 0x53F8B8u, 0x53F940u};
constexpr u32 kAdxErr = 0x53AE08u;
u64 g_v0 = 0;
void install_si(StandIns& s) {
    s.clobber_scratch = false;
    for (u32 va : kRecorders) s.install_recorder(va, "libs11 callee", g_v0, 3);
    install_sprintf(s);
}

StandIns* g_si[2] = {nullptr, nullptr};
Fn g_fn[2] = {nullptr, nullptr};
void thunk0(EEContext& ctx) {
    StandInsScope s(*g_si[0]);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(*g_si[1]);
    g_fn[1](ctx);
}
void same_log(const StandIns& a, const StandIns& b, const char* what) {
    INFO(what);
    CHECK(a.log.size() == b.log.size());
    for (std::size_t i = 0; i < std::min(a.log.size(), b.log.size()); ++i) {
        if (!(a.log[i] == b.log[i])) {
            INFO("stand-in call " << i << " differs (callee " << std::hex << a.log[i].va << " / " << b.log[i].va << ")");
            CHECK(false);
            break;
        }
    }
}

std::map<std::string, int> g_pairs;
u32 g_seed = 1;
// One pair from the machine's state (the recompiled run's memory stays); `log` receives the hand body's call log.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, StandIns* log = nullptr) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_si(sh);
    install_si(sr);
    g_si[0] = &sh;
    g_si[1] = &sr;
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    hgp::Run r = hgp::pair(m, &thunk0, &thunk1, a, g_seed++, c.name, hw);
    same_log(sh, sr, c.name);
    if (log) log->log = sh.log;
    return r;
}
// The same comparison on a long-lived BaseRange (write_tracker.h): the snapshot's 32 MiB stay the base and restore()
// copies back only the pages a pair wrote.
hgp::Run pr_base(Machine& m, BaseRange& ram, u32 addr, const Args& args, const HwCheck& hw) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_si(sh);
    install_si(sr);
    g_si[0] = &sh;
    g_si[1] = &sr;
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    ++g_pairs[c.name];
    const u32 seed = g_seed++;
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
    INFO(c.name << " a0=" << std::hex << args[0] << " a1=" << args[1] << std::dec << " seed=" << seed
                << (r.stopped ? " (recomp stopped: " + r.what + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    for (std::size_t i = 0; i < std::min(h.snaps.size(), r.snaps.size()); ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << ": " << d);
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
        INFO("main RAM: first differing byte at " << std::hex << first);
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
    same_log(sh, sr, c.name);
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const hgp::Run r = pr(m, addr, a, std::move(t));
    INFO(by_addr(addr).name << (r.stopped ? " stopped: " + r.what : std::string()) << " at " << std::hex << r.stop_pc);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

}  // namespace

TEST_CASE("game(libs11): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            g_v0 = rng() % 4;
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += pr(*m, c.addr, args).stopped ? 1 : 0;
            ++total;
        }
    }
    g_v0 = 0;
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The replay snapshots hold the CRI modules as the game leaves them (the AIX parser module initialised once, the
// file system's sync flag 0x7A3030 = 0x8001, every handle table empty). Every body runs on each snapshot with null, a
// zeroed record and a record of small values / pointers back into it, second arguments from the values its branches
// test (0, 1, 3, 204, -1) and the stood-in callees returning 0 or 1; each pair starts from the snapshot (a BaseRange:
// only the pages a pair wrote are copied back).
TEST_CASE("game(libs11): every body on the replay snapshots' CRI state") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    int runs = 0, stops = 0, snaps = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        ++snaps;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        CHECK(r32(*m, 0x79A328u) == 1u);  // the AIX parser module's init count
        for (int rec = 0; rec < 3; ++rec) {
            std::memset(m->at(kRec), 0, 0x4000);
            if (rec == 2)
                for (u32 i = 0; i < 0x2000; i += 4) w32(*m, kRec + i, (i / 4) % 5 == 0 ? kRec + ((i * 7) & 0x1FF0u) : (i / 4) % 7);
            BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
            for (const Case& c : kCases) {
                if (only && std::string(only) != c.name) continue;
                for (u64 a1 : {0ull, 1ull, 3ull, 204ull, ~0ull})
                    for (u64 v : {0ull, 1ull}) {
                        g_v0 = v;
                        HwCheck hw;
                        hw.gpr_in = {{GPR_T0, kOut + 0x200}};
                        const hgp::Run r = pr_base(*m, base, c.addr, Args{rec == 0 ? 0 : kRec, a1, kOut, kOut + 0x100}, hw);
                        base.restore();
                        ++runs;
                        stops += r.stopped ? 1 : 0;
                    }
            }
        }
    }
    g_v0 = 0;
    std::memset(m->mem.main_ram(), 0, EEMemory::kMainRamSize);
    MESSAGE(runs << " pairs from " << snaps << " snapshots, " << stops << " stopped identically");
}

// PL2ENC: the create rules (alignment, the 44-byte handle, the two 384-byte delay lines, at least 1024 bytes of work
// and work + size >= the lines' end), the sample-rate rule (delay = rate / 750 within 1..96) and the position rule
// (gain indices 127 + p, |p - 127|, |q + 127|, |q - 127| for p, q in -127..127).
TEST_CASE("game(libs11): the PL2 encoder's create, sample-rate and position rules") {
    auto m = machine();
    if (!m) return;
    using namespace p3fes::game::libs11;
    std::memset(m->at(kRec), 0x55, 0x2000);
    const u32 work = kRec + 2;  // unaligned on purpose
    const u32 h = sv(prv(*m, 0x55EC38u, {work, 4096, 0, 0}));
    CHECK(h == kRec + 4);
    CHECK(r32(*m, h + pl2::kWork) == work);
    CHECK(r32(*m, h + pl2::kWorkSize) == 4096u);
    CHECK(r32(*m, h + pl2::kDelay0) == h + 44);
    CHECK(r32(*m, h + pl2::kDelay1) == h + 44 + 384);
    CHECK(prv(*m, 0x55EC38u, {work, 1000, 0, 0}) == 0u);  // 'E03090102 : Work ... is too short.'
    CHECK(prv(*m, 0x55EC38u, {0, 4096, 0, 0}) == 0u);     // 'E03090101 : NULL pointer'
    CHECK(prv(*m, 0x55EC38u, {work, 1024, 0, 0}) == h);  // 1024 bytes always hold the handle and both lines
    for (const auto& [rate, len] : {std::pair<u32, u32>{48000, 64}, {44100, 58}, {100, 1}, {100000, 96}, {72000, 96}}) {
        prv(*m, 0x55F308u, {h, rate, 0, 0});
        CHECK(r32(*m, h + pl2::kRate) == rate);
        CHECK(r32(*m, h + pl2::kDelayLen) == len);
    }
    w32(*m, h + pl2::kRate, 7);
    prv(*m, 0x55F308u, {h, 0, 0, 0});  // 'E03091602 : Illegal parameter': nothing stored
    CHECK(r32(*m, h + pl2::kRate) == 7u);
    for (const auto& [p, q] : {std::pair<s32, s32>{0, 0}, {127, -127}, {-127, 127}, {40, -3}}) {
        prv(*m, 0x55F218u, {h, static_cast<u64>(static_cast<s64>(p)), static_cast<u64>(static_cast<s64>(q)), 0});
        CHECK(r32(*m, h + pl2::kGain0) == static_cast<u32>(p + 127));
        CHECK(r32(*m, h + pl2::kGain1) == static_cast<u32>(std::abs(p - 127)));
        CHECK(r32(*m, h + pl2::kGain2) == static_cast<u32>(std::abs(q + 127)));
        CHECK(r32(*m, h + pl2::kGain3) == static_cast<u32>(std::abs(q - 127)));
    }
    w32(*m, h + pl2::kGain0, 5);
    prv(*m, 0x55F218u, {h, 128, 0, 0});  // out of range: 'E03090307', nothing stored
    CHECK(r32(*m, h + pl2::kGain0) == 5u);
    // the init count and the error callback
    const u32 cnt = r32(*m, 0x7A8438u);
    prv(*m, 0x55EB38u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7A8438u) == cnt + 1);
    prv(*m, 0x55EBA8u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7A8438u) == cnt);
    prv(*m, 0x55EAB0u, {0x55F670u, 9, 0, 0});
    CHECK(r32(*m, 0x7A843Cu) == 0x55F670u);
    CHECK(r32(*m, 0x7A8440u) == 9u);
    // an error now reaches the ADX error handler through the callback (sub_55F670 forwards its second argument)
    StandIns log;
    pr(*m, 0x55F308u, {0, 48000, 0, 0}, {}, &log);
    CHECK(log.calls_to(kAdxErr) == 1u);
    if (!log.log.empty()) CHECK(str(*m, static_cast<u32>(log.log.back().args[0])).rfind("E03091601", 0) == 0);
    // one sample and a block of 32 run on the created handle (gains from the table, delay lines updated)
    prv(*m, 0x55F308u, {h, 48000, 0, 0});
    prv(*m, 0x55F218u, {h, 0, 0, 0});
    for (u32 i = 0; i < 32; ++i) {
        const s16 s = static_cast<s16>(i * 997 - 16000);
        std::memcpy(m->at(kOut + 2 * i), &s, 2);
    }
    pr(*m, 0x55EE58u, {h, 1234, kOut + 0x100, kOut + 0x102});
    CHECK(r32(*m, h + pl2::kPos) == 1u);
    pr(*m, 0x55F028u, {h, kOut, kOut + 0x200, kOut + 0x300});
    w32(*m, h + pl2::kPos, 63);
    pr(*m, 0x55EE58u, {h, static_cast<u64>(static_cast<s64>(-32768)), kOut + 0x100, kOut + 0x102});
    CHECK(r32(*m, h + pl2::kPos) == 0u);  // wraps at the delay length 64
    MESSAGE(summary());
}

// The AIX player accessors on a built handle: the null reports (-1 / 0), the status gate 1..3 of the getters, the
// range set / get and the song count through the parser record.
TEST_CASE("game(libs11): the AIX player accessors") {
    auto m = machine();
    if (!m) return;
    using namespace p3fes::game::libs11;
    std::memset(m->at(kRec), 0, 0x2000);
    const u32 h = kRec, parser = kRec + 0x100;
    w32(*m, h + aixp::kParser, parser);
    w32(*m, parser + aixparse::kNumSong, 7);
    for (int st : {0, 1, 2, 3, 4}) {
        *m->at(h + aixp::kStat) = static_cast<u8>(st);
        CHECK(sv(prv(*m, 0x5537E0u, {h, 0, 0, 0})) == (st >= 1 && st <= 3 ? 7 : 0));
    }
    CHECK(sv(prv(*m, 0x5537E0u, {0, 0, 0, 0})) == -1);
    CHECK(sv(prv(*m, 0x553730u, {0, 0, 0, 0})) == -1);
    CHECK(sv(prv(*m, 0x553788u, {0, 0, 0, 0})) == -1);
    CHECK(sv(prv(*m, 0x553690u, {0, 0, 0, 0})) == -1);
    *m->at(h + aixp::kStat) = 0;
    CHECK(prv(*m, 0x553690u, {h, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x553730u, {h, 0, 0, 0}) == 0u);
    // the range
    prv(*m, 0x553498u, {h, 100, 50, 0});
    CHECK(r32(*m, h + aixp::kRangeStart) == 100u);
    CHECK(r32(*m, h + aixp::kRangeEnd) == 150u);
    w32(*m, kOut, 0xDEAD);
    w32(*m, kOut + 4, 0xBEEF);
    prv(*m, 0x553510u, {h, kOut, kOut + 4, 0});
    CHECK(r32(*m, kOut) == 100u);
    CHECK(r32(*m, kOut + 4) == 50u);
    prv(*m, 0x553510u, {h, 0, 0, 0});  // both out-parameters optional
    // the word +448, the byte +433, the source
    prv(*m, 0x553438u, {h, 0x1234, 0, 0});
    CHECK(prv(*m, 0x553468u, {h, 0, 0, 0}) == 0x1234u);
    CHECK(sv(prv(*m, 0x553468u, {0, 0, 0, 0})) == -1);
    prv(*m, 0x553408u, {h, 0x5A, 0, 0});
    CHECK(*m->at(h + aixp::kByte433) == 0x5A);
    w32(*m, h + aixp::kSource, 0x1234560);
    CHECK(prv(*m, 0x553560u, {h, 0, 0, 0}) == 0x1234560u);
    CHECK(prv(*m, 0x553560u, {0, 0, 0, 0}) == 0u);
    // a null handle reports through sub_552630 -> the ADX error handler with its message
    StandIns log;
    pr(*m, 0x553438u, {0, 1, 0, 0}, {}, &log);
    REQUIRE(log.calls_to(kAdxErr) == 1u);
    CHECK(str(*m, static_cast<u32>(log.log[0].args[0])).rfind("E2003050213", 0) == 0);
    MESSAGE(summary());
}

// The AIX parser records on the replay snapshot: create takes the first free one of the four, copies the track
// players and marks it used; the chunk header is unpacked from big-endian.
TEST_CASE("game(libs11): the AIX parser records and the chunk header") {
    auto m = machine();
    if (!m) return;
    using namespace p3fes::game::libs11;
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.size() == EEMemory::kMainRamSize) std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    for (u32 i = 0; i < 4; ++i) *m->at(aixparse::kRecords + aixparse::kRecordSize * i) = 0;
    *m->at(aixparse::kRecords) = 1;  // the first record in use
    const u32 tracks[3] = {0x111110u, 0x222220u, 0x333330u};
    std::memcpy(m->at(kOut), tracks, sizeof tracks);
    const u32 rec = sv(prv(*m, 0x5547C8u, {3, 0x4444, kOut, 0}));  // create under the SVM lock
    CHECK(rec == aixparse::kRecords + aixparse::kRecordSize);
    CHECK(*m->at(rec + aixparse::kUsed) == 1);
    CHECK(*m->at(rec + aixparse::kNumTrk) == 3);
    CHECK(r32(*m, rec + aixparse::kSource) == 0x4444u);
    CHECK(r32(*m, rec + aixparse::kTrkStream + 8) == 0x333330u);
    for (u32 i = 0; i < 4; ++i) *m->at(aixparse::kRecords + aixparse::kRecordSize * i) = 1;
    CHECK(prv(*m, 0x554820u, {1, 0, kOut, 0}) == 0u);  // all four in use
    // the chunk header: 'AIXE', size 0x01020304, 5, 6, 0x0708, 0x090A0B0C
    const u8 hdr[16] = {'A', 'I', 'X', 'E', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::memcpy(m->at(kRec), hdr, 16);
    CHECK(prv(*m, 0x554EF0u, {kRec, 16, kOut, 0}) == 16u);
    CHECK(r32(*m, kOut) == 0x41495845u);
    CHECK(r32(*m, kOut + 4) == 0x01020304u);
    CHECK(*m->at(kOut + 8) == 5);
    CHECK(*m->at(kOut + 9) == 6);
    CHECK(r16(*m, kOut + 10) == 0x0708u);
    CHECK(r32(*m, kOut + 12) == 0x090A0B0Cu);
    CHECK(prv(*m, 0x554EF0u, {kRec, 15, kOut + 0x40, 0}) == 0u);
    // the header reset
    std::memset(m->at(kRec), 0xCC, 6400);
    CHECK(prv(*m, 0x554EA0u, {kRec, 0, 0, 0}) == 1u);
    CHECK(*m->at(kRec + 12) == 1);
    CHECK(r32(*m, kRec + 528) == 1u);
    CHECK(r32(*m, kRec + 6292) == 1u);
    CHECK(r16(*m, kRec + 6298) == 1u);
    CHECK(*m->at(kRec + 6327) == 0);
    CHECK(*m->at(kRec + 6328) == 0xCC);
    MESSAGE(summary());
}

// The sector file handle: seek (set / current / end) clamps the position to [0, size] and clears the read count; tell
// gives the position; the read result is the sectors read << 11 only in state 1; null reports 'E0092712'.
TEST_CASE("game(libs11): the sector file handle's seek, tell and read result") {
    auto m = machine();
    if (!m) return;
    using namespace p3fes::game::libs11;
    std::memset(m->at(kRec), 0, 0x100);
    const u32 h = kRec;
    w32(*m, h + fsh::kNsct, 100);
    struct Step { s32 off; u32 whence; u32 want; };
    for (const Step& s : {Step{10, 0, 10}, Step{5, 1, 15}, Step{-3, 2, 97}, Step{200, 0, 100}, Step{-50, 1, 50},
                          Step{-500, 0, 0}, Step{7, 9, 0}}) {
        w32(*m, h + fsh::kNread, 33);
        CHECK(prv(*m, 0x55BFE0u, {h, static_cast<u64>(static_cast<s64>(s.off)), s.whence, 0}) == s.want);
        CHECK(r32(*m, h + fsh::kPos) == s.want);
        CHECK(r32(*m, h + fsh::kNread) == 0u);
        CHECK(prv(*m, 0x55C078u, {h, 0, 0, 0}) == s.want);
    }
    CHECK(prv(*m, 0x55BFE0u, {0, 1, 0, 0}) == 0u);
    CHECK(prv(*m, 0x55C078u, {0, 0, 0, 0}) == 0u);
    w32(*m, h + fsh::kNread, 3);
    for (int st : {0, 1, 2, 3}) {
        *m->at(h + fsh::kStat) = static_cast<u8>(st);
        CHECK(prv(*m, 0x55C378u, {h, 0, 0, 0}) == (st == 1 ? 3u << 11 : 0u));
    }
    CHECK(prv(*m, 0x55C370u, {0, 0, 0, 0}) == 2048u);
    // the bytes read, capped by the file size (u64 +8)
    const u64 size = 5000;
    std::memcpy(m->at(h + fsh::kSize), &size, 8);
    CHECK(prv(*m, 0x55C400u, {h, 0, 0, 0}) == 5000u);
    w32(*m, h + fsh::kNread, 1);
    CHECK(prv(*m, 0x55C400u, {h, 0, 0, 0}) == 2048u);
    CHECK(prv(*m, 0x55C3E0u, {h, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x55C480u, {h, 201, 0, 0}) == 2048u);
    CHECK(prv(*m, 0x55C480u, {h, 299, 0, 0}) == 1u);
    CHECK(prv(*m, 0x55C480u, {h, 206, 0, 0}) == 0u);
    CHECK(prv(*m, 0x55C480u, {0, 201, 0, 0}) == 0u);
    // the tail past the end of the file is zeroed: 2 sectors read at sector 1 of a 5000-byte file -> buffer bytes 2952..4095
    w32(*m, h + fsh::kPos, 1);
    w32(*m, h + fsh::kNreq, 2);
    w32(*m, h + fsh::kBuf, kOut);
    std::memset(m->at(kOut), 0x77, 4096);
    pr(*m, 0x55B8B0u, {h, 0, 0, 0});
    CHECK(*m->at(kOut + 2951) == 0x77);
    CHECK(*m->at(kOut + 2952) == 0);
    CHECK(*m->at(kOut + 4095) == 0);
    MESSAGE(summary());
}

// The HTCI name helpers: ':' within the first 16 characters, the 'host' prefix, '\' == '/' in the path compare, and the
// split of a file-list text into the name table (the first call keeps the table in 0x7A3020..0x7A302C), the lookup by
// name, the root directory copy and the device prefix.
TEST_CASE("game(libs11): the HTCI name helpers and the file-list split") {
    auto m = machine();
    if (!m) return;
    std::memset(m->at(kRec), 0, 0x2000);
    const u32 a = kRec, b = kRec + 0x100;
    put(*m, a, "host0:data/x.bin");
    CHECK(prv(*m, 0x55C548u, {a, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x55C5B8u, {a, 0, 0, 0}) == 1u);
    put(*m, a, "cdrom0:\\X.BIN");
    CHECK(prv(*m, 0x55C5B8u, {a, 0, 0, 0}) == 0u);
    put(*m, a, "0123456789ABCDEF:x");
    CHECK(prv(*m, 0x55C548u, {a, 0, 0, 0}) == 0u);
    put(*m, a, "hos");
    CHECK(prv(*m, 0x55C5B8u, {a, 0, 0, 0}) == 0u);
    put(*m, a, "dir\\sub\\f.bin");
    put(*m, b, "dir/sub/f.bin");
    CHECK(prv(*m, 0x55C798u, {a, b, 0, 0}) == 0u);
    put(*m, b, "dir/sub/g.bin");
    CHECK(sv(prv(*m, 0x55C798u, {a, b, 0, 0})) == -1);
    put(*m, b, "dir/sub/f.bin2");
    CHECK(sv(prv(*m, 0x55C798u, {a, b, 0, 0})) == -1);
    CHECK(prv(*m, 0x55C728u, {'\\', 0, 0, 0}) == static_cast<u64>('/'));
    CHECK(prv(*m, 0x55C728u, {'a', 0, 0, 0}) == static_cast<u64>('a'));
    CHECK(prv(*m, 0x55C740u, {'\\', '/', 0, 0}) == 0u);
    CHECK(sv(prv(*m, 0x55C740u, {'a', 'b', 0, 0})) == -1);
    // the split: 4 slots of 31-character names after the 4 descriptor / size pairs
    const u32 table = kRec + 0x400, text = kRec + 0x800;
    put(*m, text, "A.BIN\nSUB\\B.BIN\nC.BIN\n");
    w32(*m, 0x7A3020u, 0);
    CHECK(prv(*m, 0x55C830u, {table, text, 4, 31}) == 3u);
    CHECK(str(*m, table + 32) == "A.BIN");
    CHECK(str(*m, table + 32 + 32) == "SUB/B.BIN");
    CHECK(str(*m, table + 32 + 64) == "C.BIN");
    CHECK(r32(*m, 0x7A3020u) == table);
    CHECK(r32(*m, 0x7A3024u) == 3u);
    CHECK(r32(*m, 0x7A3028u) == 4u);
    CHECK(r32(*m, 0x7A302Cu) == 31u);
    // a last name without its line end is not taken (the list files end each name with CR / LF)
    put(*m, kRec + 0x1000, "A.BIN\nB.BIN");
    CHECK(prv(*m, 0x55C830u, {kRec + 0xC00, kRec + 0x1000, 4, 31}) == 1u);
    CHECK(r32(*m, 0x7A3020u) == table);  // kept from the first call
    // the lookup by name finds the descriptor / size pair of the second entry
    w32(*m, table + 8, 0x51);
    w32(*m, table + 12, 0x5200);
    put(*m, b, "SUB/B.BIN");
    pr(*m, 0x55CE18u, {kOut, b, table, 3});
    CHECK(r32(*m, kOut) == 0x51u);
    CHECK(r32(*m, kOut + 4) == 0x5200u);
    put(*m, b, "NONE");
    pr(*m, 0x55CE18u, {kOut, b, table, 3});
    CHECK(r32(*m, kOut) == 0u);
    // the root directory and the device prefix
    put(*m, a, "data");
    pr(*m, 0x55D108u, {a, 0, 0, 0});
    CHECK(str(*m, 0x7A3038u) == "data");  // the "/" written first is overwritten by the strcpy
    put(*m, a, "\\data");
    pr(*m, 0x55D108u, {a, 0, 0, 0});
    CHECK(str(*m, 0x7A3038u) == "\\data");
    pr(*m, 0x55D198u, {0, 0, 0, 0});
    CHECK(str(*m, 0x7A3140u) == "host:");
    MESSAGE(summary());
}

// The LSC queue getters: the ring slot of a queue index (from the head), the lookups by stream id (+60 / +80 / +84 of
// the entry), the null and not-found reports through sub_55DBE8.
TEST_CASE("game(libs11): the LSC queue getters") {
    auto m = machine();
    if (!m) return;
    using namespace p3fes::game::libs11;
    std::memset(m->at(kRec), 0, 0x1000);
    const u32 h = kRec;
    for (u32 i = 0; i < 16; ++i) {
        const u32 e = h + lsc::kQueue + lsc::kEntSize * i;
        w32(*m, e + lsc::ent::kId, 100 + i);
        w32(*m, e + 4, 0x1000 + i);
        w32(*m, e + 24, 0x2000 + i);
        w32(*m, e + 28, 0x3000 + i);
    }
    w32(*m, h + lsc::kHead, 14);
    w32(*m, h + lsc::kCount, 5);
    CHECK(prv(*m, 0x55D7F0u, {h, 0, 0, 0}) == 114u);
    CHECK(prv(*m, 0x55D7F0u, {h, 3, 0, 0}) == 101u);  // (14 + 3) mod 16
    CHECK(prv(*m, 0x55D880u, {h, 109, 0, 0}) == 0x1009u);
    CHECK(prv(*m, 0x55D918u, {h, 115, 0, 0}) == 0x200Fu);
    CHECK(prv(*m, 0x55D9B0u, {h, 100, 0, 0}) == 0x3000u);
    w32(*m, h + 20, 77);
    CHECK(prv(*m, 0x55DAB0u, {h, 0, 0, 0}) == 77u);
    // the reports go through sub_55DBE8 (vsprintf, libs10): the pair stopped there while it was absent and runs on
    // once it is replaced -- either way identically, which pr() checks
    for (const Args& a : {Args{h, 5, 0, 0}, Args{h, 116, 0, 0}, Args{0, 0, 0, 0}}) pr(*m, 0x55D7F0u, a);
    pr(*m, 0x55D880u, {h, 999, 0, 0});
    pr(*m, 0x55DAB0u, {0, 0, 0, 0});
    MESSAGE(summary());
}

// The small rules: the byte-wise helpers, the DTX test RPC's reply, the counters and the stored words.
TEST_CASE("game(libs11): the DTX test reply, the counters and the stored words") {
    auto m = machine();
    if (!m) return;
    std::memset(m->at(kOut), 0, 0x100);
    w32(*m, 0x7A1154u, 41);
    pr(*m, 0x559660u, {0, kOut, 40, 0});
    CHECK(str(*m, kOut) == "Hello from EE (41)");
    CHECK(*m->at(kOut + 19) == 0xAA);
    CHECK(*m->at(kOut + 39) == 0xAA);
    CHECK(*m->at(kOut + 40) == 0);
    CHECK(r32(*m, 0x7A1154u) == 42u);
    const u32 c = r32(*m, 0x7A1150u);
    pr(*m, 0x559648u, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7A1150u) == c + 1);
    CHECK(sv(prv(*m, 0x551988u, {10, 3, 0, 0})) == -7);
    pr(*m, 0x55D220u, {0x123450, 0, 0, 0});
    CHECK(r32(*m, 0x7A3034u) == 0x123450u);
    pr(*m, 0x5589B8u, {1, 0, 0, 0});
    CHECK(prv(*m, 0x5589F8u, {0, 0, 0, 0}) == 1u);
    pr(*m, 0x5589B8u, {0, 0, 0, 0});
    CHECK(prv(*m, 0x5589F8u, {0, 0, 0, 0}) == 0u);
    for (u32 a : {0x551980u, 0x5524D0u, 0x552550u, 0x552558u, 0x552560u, 0x552568u, 0x552570u, 0x552578u, 0x552580u})
        CHECK(prv(*m, a, {7, 7, 7, 7}) == 0u);
    std::memset(m->at(kRec), 0, 0x100);
    pr(*m, 0x552010u, {kRec, 3, 0x99, 0});
    CHECK(r32(*m, kRec + 20 + 12) == 0x99u);
    MESSAGE(summary());
}

#else

TEST_CASE("game(libs11): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
