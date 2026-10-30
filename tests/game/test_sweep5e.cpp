// Pair tests for slice sweep5e (game/src/fx/sweep5e.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window and the bus log), with the stand-in world of
// stand_ins.h around both runs (heap and RW memory slots, printf / sprintf, the H_Cdvd file layer, the libmc2
// semaphore wrappers) and its call logs, heaps and file nodes compared. Worlds: random worlds; the replay snapshots'
// live objects (gBtl and its units, the nm list objects, live heap blocks); battle units at the +162 / flag / id values
// the battle helpers branch on; and documented rules on the leaves. A callee this build neither emits nor stands in
// stops both runs at the same call: no test asserts such a stop.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/sweep5e.h"

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
void fn_sub_2E3AE0_002e3ae0(EEContext&);  // generated body
void fn_sub_2E3AE0_002e3ae0__recomp(EEContext&);  // recompiled
void fn_sub_2E97E0_002e97e0(EEContext&);  // generated body
void fn_sub_2E97E0_002e97e0__recomp(EEContext&);  // recompiled
void fn_sub_2EAA40_002eaa40(EEContext&);  // generated body
void fn_sub_2EAA40_002eaa40__recomp(EEContext&);  // recompiled
void fn_sub_2EC190_002ec190(EEContext&);  // generated body
void fn_sub_2EC190_002ec190__recomp(EEContext&);  // recompiled
void fn_sub_2EEE20_002eee20(EEContext&);  // generated body
void fn_sub_2EEE20_002eee20__recomp(EEContext&);  // recompiled
void fn_sub_2EF9D0_002ef9d0(EEContext&);  // generated body
void fn_sub_2EF9D0_002ef9d0__recomp(EEContext&);  // recompiled
void fn_sub_2EFB40_002efb40(EEContext&);  // generated body
void fn_sub_2EFB40_002efb40__recomp(EEContext&);  // recompiled
void fn_sub_2F1B60_002f1b60(EEContext&);  // generated body
void fn_sub_2F1B60_002f1b60__recomp(EEContext&);  // recompiled
void fn_sub_2F5BF0_002f5bf0(EEContext&);  // generated body
void fn_sub_2F5BF0_002f5bf0__recomp(EEContext&);  // recompiled
void fn_sub_2F8790_002f8790(EEContext&);  // generated body
void fn_sub_2F8790_002f8790__recomp(EEContext&);  // recompiled
void fn_sub_3138E0_003138e0(EEContext&);  // generated body
void fn_sub_3138E0_003138e0__recomp(EEContext&);  // recompiled
void fn_sub_314850_00314850(EEContext&);  // generated body
void fn_sub_314850_00314850__recomp(EEContext&);  // recompiled
void fn_sub_314D30_00314d30(EEContext&);  // generated body
void fn_sub_314D30_00314d30__recomp(EEContext&);  // recompiled
void fn_sub_319970_00319970(EEContext&);  // generated body
void fn_sub_319970_00319970__recomp(EEContext&);  // recompiled
void fn_sub_31AAD0_0031aad0(EEContext&);  // generated body
void fn_sub_31AAD0_0031aad0__recomp(EEContext&);  // recompiled
void fn_sub_31B820_0031b820(EEContext&);  // generated body
void fn_sub_31B820_0031b820__recomp(EEContext&);  // recompiled
void fn_sub_31C820_0031c820(EEContext&);  // generated body
void fn_sub_31C820_0031c820__recomp(EEContext&);  // recompiled
void fn_sub_31EF80_0031ef80(EEContext&);  // generated body
void fn_sub_31EF80_0031ef80__recomp(EEContext&);  // recompiled
void fn_sub_329890_00329890(EEContext&);  // generated body
void fn_sub_329890_00329890__recomp(EEContext&);  // recompiled
void fn_sub_329A60_00329a60(EEContext&);  // generated body
void fn_sub_329A60_00329a60__recomp(EEContext&);  // recompiled
void fn_sub_334310_00334310(EEContext&);  // generated body
void fn_sub_334310_00334310__recomp(EEContext&);  // recompiled
void fn_sub_334390_00334390(EEContext&);  // generated body
void fn_sub_334390_00334390__recomp(EEContext&);  // recompiled
void fn_sub_334820_00334820(EEContext&);  // generated body
void fn_sub_334820_00334820__recomp(EEContext&);  // recompiled
void fn_sub_3348B0_003348b0(EEContext&);  // generated body
void fn_sub_3348B0_003348b0__recomp(EEContext&);  // recompiled
void fn_sub_335180_00335180(EEContext&);  // generated body
void fn_sub_335180_00335180__recomp(EEContext&);  // recompiled
void fn_sub_3353F0_003353f0(EEContext&);  // generated body
void fn_sub_3353F0_003353f0__recomp(EEContext&);  // recompiled
void fn_sub_335540_00335540(EEContext&);  // generated body
void fn_sub_335540_00335540__recomp(EEContext&);  // recompiled
void fn_sub_3359E0_003359e0(EEContext&);  // generated body
void fn_sub_3359E0_003359e0__recomp(EEContext&);  // recompiled
void fn_sub_336630_00336630(EEContext&);  // generated body
void fn_sub_336630_00336630__recomp(EEContext&);  // recompiled
void fn_sub_3368A0_003368a0(EEContext&);  // generated body
void fn_sub_3368A0_003368a0__recomp(EEContext&);  // recompiled
void fn_sub_336920_00336920(EEContext&);  // generated body
void fn_sub_336920_00336920__recomp(EEContext&);  // recompiled
void fn_sub_336DF0_00336df0(EEContext&);  // generated body
void fn_sub_336DF0_00336df0__recomp(EEContext&);  // recompiled
void fn_sub_336E80_00336e80(EEContext&);  // generated body
void fn_sub_336E80_00336e80__recomp(EEContext&);  // recompiled
void fn_sub_3377F0_003377f0(EEContext&);  // generated body
void fn_sub_3377F0_003377f0__recomp(EEContext&);  // recompiled
void fn_sub_338530_00338530(EEContext&);  // generated body
void fn_sub_338530_00338530__recomp(EEContext&);  // recompiled
void fn_sub_3385D0_003385d0(EEContext&);  // generated body
void fn_sub_3385D0_003385d0__recomp(EEContext&);  // recompiled
void fn_sub_338770_00338770(EEContext&);  // generated body
void fn_sub_338770_00338770__recomp(EEContext&);  // recompiled
void fn_sub_3387C0_003387c0(EEContext&);  // generated body
void fn_sub_3387C0_003387c0__recomp(EEContext&);  // recompiled
void fn_sub_338AC0_00338ac0(EEContext&);  // generated body
void fn_sub_338AC0_00338ac0__recomp(EEContext&);  // recompiled
void fn_sub_349FD0_00349fd0(EEContext&);  // generated body
void fn_sub_349FD0_00349fd0__recomp(EEContext&);  // recompiled
void fn_sub_34A370_0034a370(EEContext&);  // generated body
void fn_sub_34A370_0034a370__recomp(EEContext&);  // recompiled
void fn_sub_3A4B90_003a4b90(EEContext&);  // generated body
void fn_sub_3A4B90_003a4b90__recomp(EEContext&);  // recompiled
void fn_sub_3B83D0_003b83d0(EEContext&);  // generated body
void fn_sub_3B83D0_003b83d0__recomp(EEContext&);  // recompiled
void fn_sub_3B8470_003b8470(EEContext&);  // generated body
void fn_sub_3B8470_003b8470__recomp(EEContext&);  // recompiled
void fn_sub_3B8730_003b8730(EEContext&);  // generated body
void fn_sub_3B8730_003b8730__recomp(EEContext&);  // recompiled
void fn_sub_3B8C30_003b8c30(EEContext&);  // generated body
void fn_sub_3B8C30_003b8c30__recomp(EEContext&);  // recompiled
void fn_sub_3B8E80_003b8e80(EEContext&);  // generated body
void fn_sub_3B8E80_003b8e80__recomp(EEContext&);  // recompiled
void fn_sub_3BB180_003bb180(EEContext&);  // generated body
void fn_sub_3BB180_003bb180__recomp(EEContext&);  // recompiled
void fn_sub_3BB390_003bb390(EEContext&);  // generated body
void fn_sub_3BB390_003bb390__recomp(EEContext&);  // recompiled
void fn_sub_3BCBF0_003bcbf0(EEContext&);  // generated body
void fn_sub_3BCBF0_003bcbf0__recomp(EEContext&);  // recompiled
void fn_sub_3BD9A0_003bd9a0(EEContext&);  // generated body
void fn_sub_3BD9A0_003bd9a0__recomp(EEContext&);  // recompiled
void fn_sub_3C8230_003c8230(EEContext&);  // generated body
void fn_sub_3C8230_003c8230__recomp(EEContext&);  // recompiled
void fn_sub_3C82E0_003c82e0(EEContext&);  // generated body
void fn_sub_3C82E0_003c82e0__recomp(EEContext&);  // recompiled
void fn_sub_3CB100_003cb100(EEContext&);  // generated body
void fn_sub_3CB100_003cb100__recomp(EEContext&);  // recompiled
void fn_sub_3CF240_003cf240(EEContext&);  // generated body
void fn_sub_3CF240_003cf240__recomp(EEContext&);  // recompiled
void fn_sub_3E6130_003e6130(EEContext&);  // generated body
void fn_sub_3E6130_003e6130__recomp(EEContext&);  // recompiled
void fn_sub_3E9200_003e9200(EEContext&);  // generated body
void fn_sub_3E9200_003e9200__recomp(EEContext&);  // recompiled
void fn_sub_3EAD10_003ead10(EEContext&);  // generated body
void fn_sub_3EAD10_003ead10__recomp(EEContext&);  // recompiled
void fn_sub_3EADD0_003eadd0(EEContext&);  // generated body
void fn_sub_3EADD0_003eadd0__recomp(EEContext&);  // recompiled
void fn_sub_3EBA10_003eba10(EEContext&);  // generated body
void fn_sub_3EBA10_003eba10__recomp(EEContext&);  // recompiled
void fn_sub_3EBAD0_003ebad0(EEContext&);  // generated body
void fn_sub_3EBAD0_003ebad0__recomp(EEContext&);  // recompiled
void fn_sub_3EC090_003ec090(EEContext&);  // generated body
void fn_sub_3EC090_003ec090__recomp(EEContext&);  // recompiled
void fn_sub_3EC150_003ec150(EEContext&);  // generated body
void fn_sub_3EC150_003ec150__recomp(EEContext&);  // recompiled
void fn_sub_3EC6F0_003ec6f0(EEContext&);  // generated body
void fn_sub_3EC6F0_003ec6f0__recomp(EEContext&);  // recompiled
void fn_sub_3EC7B0_003ec7b0(EEContext&);  // generated body
void fn_sub_3EC7B0_003ec7b0__recomp(EEContext&);  // recompiled
void fn_sub_3ECD30_003ecd30(EEContext&);  // generated body
void fn_sub_3ECD30_003ecd30__recomp(EEContext&);  // recompiled
void fn_sub_3ECDF0_003ecdf0(EEContext&);  // generated body
void fn_sub_3ECDF0_003ecdf0__recomp(EEContext&);  // recompiled
void fn_sub_3ED420_003ed420(EEContext&);  // generated body
void fn_sub_3ED420_003ed420__recomp(EEContext&);  // recompiled
void fn_sub_3EDDD0_003eddd0(EEContext&);  // generated body
void fn_sub_3EDDD0_003eddd0__recomp(EEContext&);  // recompiled
void fn_sub_3EDE80_003ede80(EEContext&);  // generated body
void fn_sub_3EDE80_003ede80__recomp(EEContext&);  // recompiled
void fn_sub_3FC060_003fc060(EEContext&);  // generated body
void fn_sub_3FC060_003fc060__recomp(EEContext&);  // recompiled
void fn_sub_3FC540_003fc540(EEContext&);  // generated body
void fn_sub_3FC540_003fc540__recomp(EEContext&);  // recompiled
void fn_sub_3FD820_003fd820(EEContext&);  // generated body
void fn_sub_3FD820_003fd820__recomp(EEContext&);  // recompiled
void fn_sub_4030B0_004030b0(EEContext&);  // generated body
void fn_sub_4030B0_004030b0__recomp(EEContext&);  // recompiled
void fn_sub_4030F0_004030f0(EEContext&);  // generated body
void fn_sub_4030F0_004030f0__recomp(EEContext&);  // recompiled
void fn_sub_403130_00403130(EEContext&);  // generated body
void fn_sub_403130_00403130__recomp(EEContext&);  // recompiled
void fn_sub_403220_00403220(EEContext&);  // generated body
void fn_sub_403220_00403220__recomp(EEContext&);  // recompiled
void fn_sub_403E40_00403e40(EEContext&);  // generated body
void fn_sub_403E40_00403e40__recomp(EEContext&);  // recompiled
void fn_sub_403F20_00403f20(EEContext&);  // generated body
void fn_sub_403F20_00403f20__recomp(EEContext&);  // recompiled
void fn_sub_4044C0_004044c0(EEContext&);  // generated body
void fn_sub_4044C0_004044c0__recomp(EEContext&);  // recompiled
void fn_sub_40B3A0_0040b3a0(EEContext&);  // generated body
void fn_sub_40B3A0_0040b3a0__recomp(EEContext&);  // recompiled
void fn_sub_414770_00414770(EEContext&);  // generated body
void fn_sub_414770_00414770__recomp(EEContext&);  // recompiled
void fn_sub_416240_00416240(EEContext&);  // generated body
void fn_sub_416240_00416240__recomp(EEContext&);  // recompiled
void fn_sub_4163F0_004163f0(EEContext&);  // generated body
void fn_sub_4163F0_004163f0__recomp(EEContext&);  // recompiled
void fn_sub_4166D0_004166d0(EEContext&);  // generated body
void fn_sub_4166D0_004166d0__recomp(EEContext&);  // recompiled
void fn_sub_416B90_00416b90(EEContext&);  // generated body
void fn_sub_416B90_00416b90__recomp(EEContext&);  // recompiled
void fn_sub_419730_00419730(EEContext&);  // generated body
void fn_sub_419730_00419730__recomp(EEContext&);  // recompiled
void fn_sub_419790_00419790(EEContext&);  // generated body
void fn_sub_419790_00419790__recomp(EEContext&);  // recompiled
void fn_sub_4198F0_004198f0(EEContext&);  // generated body
void fn_sub_4198F0_004198f0__recomp(EEContext&);  // recompiled
void fn_sub_419F20_00419f20(EEContext&);  // generated body
void fn_sub_419F20_00419f20__recomp(EEContext&);  // recompiled
void fn_sub_41A3F0_0041a3f0(EEContext&);  // generated body
void fn_sub_41A3F0_0041a3f0__recomp(EEContext&);  // recompiled
void fn_sub_41A730_0041a730(EEContext&);  // generated body
void fn_sub_41A730_0041a730__recomp(EEContext&);  // recompiled
void fn_sub_41ABC0_0041abc0(EEContext&);  // generated body
void fn_sub_41ABC0_0041abc0__recomp(EEContext&);  // recompiled
void fn_sub_41AFF0_0041aff0(EEContext&);  // generated body
void fn_sub_41AFF0_0041aff0__recomp(EEContext&);  // recompiled
void fn_sub_48D960_0048d960(EEContext&);  // generated body
void fn_sub_48D960_0048d960__recomp(EEContext&);  // recompiled
void fn_j_RpClumpDestroy_004906d0(EEContext&);  // generated body
void fn_j_RpClumpDestroy_004906d0__recomp(EEContext&);  // recompiled
void fn_j_RpAtomicDestroy_004906e0(EEContext&);  // generated body
void fn_j_RpAtomicDestroy_004906e0__recomp(EEContext&);  // recompiled
void fn_sub_490810_00490810(EEContext&);  // generated body
void fn_sub_490810_00490810__recomp(EEContext&);  // recompiled
void fn_sub_4AE070_004ae070(EEContext&);  // generated body
void fn_sub_4AE070_004ae070__recomp(EEContext&);  // recompiled
void fn_sub_4AE0C0_004ae0c0(EEContext&);  // generated body
void fn_sub_4AE0C0_004ae0c0__recomp(EEContext&);  // recompiled
void fn_sub_4AEF60_004aef60(EEContext&);  // generated body
void fn_sub_4AEF60_004aef60__recomp(EEContext&);  // recompiled
void fn_sub_4B4C70_004b4c70(EEContext&);  // generated body
void fn_sub_4B4C70_004b4c70__recomp(EEContext&);  // recompiled
void fn_sub_4B4D60_004b4d60(EEContext&);  // generated body
void fn_sub_4B4D60_004b4d60__recomp(EEContext&);  // recompiled
void fn_sub_4B5000_004b5000(EEContext&);  // generated body
void fn_sub_4B5000_004b5000__recomp(EEContext&);  // recompiled
void fn_sub_4B78B0_004b78b0(EEContext&);  // generated body
void fn_sub_4B78B0_004b78b0__recomp(EEContext&);  // recompiled
void fn_sub_4C0820_004c0820(EEContext&);  // generated body
void fn_sub_4C0820_004c0820__recomp(EEContext&);  // recompiled
void fn_sub_4C3EE0_004c3ee0(EEContext&);  // generated body
void fn_sub_4C3EE0_004c3ee0__recomp(EEContext&);  // recompiled
void fn_sub_4C5FC0_004c5fc0(EEContext&);  // generated body
void fn_sub_4C5FC0_004c5fc0__recomp(EEContext&);  // recompiled
void fn_sub_4C7100_004c7100(EEContext&);  // generated body
void fn_sub_4C7100_004c7100__recomp(EEContext&);  // recompiled
void fn_sub_4CA500_004ca500(EEContext&);  // generated body
void fn_sub_4CA500_004ca500__recomp(EEContext&);  // recompiled
void fn_sub_4CF5C0_004cf5c0(EEContext&);  // generated body
void fn_sub_4CF5C0_004cf5c0__recomp(EEContext&);  // recompiled
void fn_sub_4D09D0_004d09d0(EEContext&);  // generated body
void fn_sub_4D09D0_004d09d0__recomp(EEContext&);  // recompiled
void fn_sub_4D84A0_004d84a0(EEContext&);  // generated body
void fn_sub_4D84A0_004d84a0__recomp(EEContext&);  // recompiled
void fn_sub_4DB350_004db350(EEContext&);  // generated body
void fn_sub_4DB350_004db350__recomp(EEContext&);  // recompiled
void fn_sub_4DD2E0_004dd2e0(EEContext&);  // generated body
void fn_sub_4DD2E0_004dd2e0__recomp(EEContext&);  // recompiled
void fn_sub_4EBFB0_004ebfb0(EEContext&);  // generated body
void fn_sub_4EBFB0_004ebfb0__recomp(EEContext&);  // recompiled
void fn__dualPrimeVector_004fafe0(EEContext&);  // generated body
void fn__dualPrimeVector_004fafe0__recomp(EEContext&);  // recompiled
void fn__decodeOrSkipField_00500858(EEContext&);  // generated body
void fn__decodeOrSkipField_00500858__recomp(EEContext&);  // recompiled
void fn_sceMc2UnformatAsync_00513648(EEContext&);  // generated body
void fn_sceMc2UnformatAsync_00513648__recomp(EEContext&);  // recompiled
void fn_sceMc2ReadFastFileAsync_00513a88(EEContext&);  // generated body
void fn_sceMc2ReadFastFileAsync_00513a88__recomp(EEContext&);  // recompiled
void fn_sceMc2WriteFastFileAsync_00513ba8(EEContext&);  // generated body
void fn_sceMc2WriteFastFileAsync_00513ba8__recomp(EEContext&);  // recompiled
void fn_sceMc2DeleteAsync_00513ee0(EEContext&);  // generated body
void fn_sceMc2DeleteAsync_00513ee0__recomp(EEContext&);  // recompiled
void fn_sceMc2GetDirAsync_00513fc8(EEContext&);  // generated body
void fn_sceMc2GetDirAsync_00513fc8__recomp(EEContext&);  // recompiled
void fn_sceMc2ChdirAsync_005141f0(EEContext&);  // generated body
void fn_sceMc2ChdirAsync_005141f0__recomp(EEContext&);  // recompiled
void fn_sceMc2ChmodAsync_005142f0(EEContext&);  // generated body
void fn_sceMc2ChmodAsync_005142f0__recomp(EEContext&);  // recompiled
void fn_sceMc2RenameAsync_005143f0(EEContext&);  // generated body
void fn_sceMc2RenameAsync_005143f0__recomp(EEContext&);  // recompiled
void fn_sceMc2GetEntSpaceAsync_00514510(EEContext&);  // generated body
void fn_sceMc2GetEntSpaceAsync_00514510__recomp(EEContext&);  // recompiled
void fn__sceMcCoreBlockErase_0051bbd8(EEContext&);  // generated body
void fn__sceMcCoreBlockErase_0051bbd8__recomp(EEContext&);  // recompiled
void fn__sceMcCoreReadPageFast_0051bd10(EEContext&);  // generated body
void fn__sceMcCoreReadPageFast_0051bd10__recomp(EEContext&);  // recompiled
void fn__sceMcCoreWritePageFast_0051bf40(EEContext&);  // generated body
void fn__sceMcCoreWritePageFast_0051bf40__recomp(EEContext&);  // recompiled
void fn__sceMcCoreDeleteSocket_0051c280(EEContext&);  // generated body
void fn__sceMcCoreDeleteSocket_0051c280__recomp(EEContext&);  // recompiled
void fn_calloc_0051e150(EEContext&);  // generated body
void fn_calloc_0051e150__recomp(EEContext&);  // recompiled
void fn_realloc_00522f98(EEContext&);  // generated body
void fn_realloc_00522f98__recomp(EEContext&);  // recompiled
void fn_sub_535888_00535888(EEContext&);  // generated body
void fn_sub_535888_00535888__recomp(EEContext&);  // recompiled
void fn_sub_5358E0_005358e0(EEContext&);  // generated body
void fn_sub_5358E0_005358e0__recomp(EEContext&);  // recompiled
void fn_sub_535A80_00535a80(EEContext&);  // generated body
void fn_sub_535A80_00535a80__recomp(EEContext&);  // recompiled
void fn_sub_535DA8_00535da8(EEContext&);  // generated body
void fn_sub_535DA8_00535da8__recomp(EEContext&);  // recompiled
void fn_sub_537CF0_00537cf0(EEContext&);  // generated body
void fn_sub_537CF0_00537cf0__recomp(EEContext&);  // recompiled
void fn_sub_538040_00538040(EEContext&);  // generated body
void fn_sub_538040_00538040__recomp(EEContext&);  // recompiled
void fn_sub_538048_00538048(EEContext&);  // generated body
void fn_sub_538048_00538048__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_0_00541cc8(EEContext&);  // generated body
void fn_r_lock_def_free_0_00541cc8__recomp(EEContext&);  // recompiled
void fn_sub_542A88_00542a88(EEContext&);  // generated body
void fn_sub_542A88_00542a88__recomp(EEContext&);  // recompiled
void fn_sub_542C70_00542c70(EEContext&);  // generated body
void fn_sub_542C70_00542c70__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_2E3AE0", 0x2E3AE0, &recomp_gen::fn_sub_2E3AE0_002e3ae0, &recomp_gen::fn_sub_2E3AE0_002e3ae0__recomp},
    {"sub_2E97E0", 0x2E97E0, &recomp_gen::fn_sub_2E97E0_002e97e0, &recomp_gen::fn_sub_2E97E0_002e97e0__recomp},
    {"sub_2EAA40", 0x2EAA40, &recomp_gen::fn_sub_2EAA40_002eaa40, &recomp_gen::fn_sub_2EAA40_002eaa40__recomp},
    {"sub_2EC190", 0x2EC190, &recomp_gen::fn_sub_2EC190_002ec190, &recomp_gen::fn_sub_2EC190_002ec190__recomp},
    {"sub_2EEE20", 0x2EEE20, &recomp_gen::fn_sub_2EEE20_002eee20, &recomp_gen::fn_sub_2EEE20_002eee20__recomp},
    {"sub_2EF9D0", 0x2EF9D0, &recomp_gen::fn_sub_2EF9D0_002ef9d0, &recomp_gen::fn_sub_2EF9D0_002ef9d0__recomp},
    {"sub_2EFB40", 0x2EFB40, &recomp_gen::fn_sub_2EFB40_002efb40, &recomp_gen::fn_sub_2EFB40_002efb40__recomp},
    {"sub_2F1B60", 0x2F1B60, &recomp_gen::fn_sub_2F1B60_002f1b60, &recomp_gen::fn_sub_2F1B60_002f1b60__recomp},
    {"sub_2F5BF0", 0x2F5BF0, &recomp_gen::fn_sub_2F5BF0_002f5bf0, &recomp_gen::fn_sub_2F5BF0_002f5bf0__recomp},
    {"sub_2F8790", 0x2F8790, &recomp_gen::fn_sub_2F8790_002f8790, &recomp_gen::fn_sub_2F8790_002f8790__recomp},
    {"sub_3138E0", 0x3138E0, &recomp_gen::fn_sub_3138E0_003138e0, &recomp_gen::fn_sub_3138E0_003138e0__recomp},
    {"sub_314850", 0x314850, &recomp_gen::fn_sub_314850_00314850, &recomp_gen::fn_sub_314850_00314850__recomp},
    {"sub_314D30", 0x314D30, &recomp_gen::fn_sub_314D30_00314d30, &recomp_gen::fn_sub_314D30_00314d30__recomp},
    {"sub_319970", 0x319970, &recomp_gen::fn_sub_319970_00319970, &recomp_gen::fn_sub_319970_00319970__recomp},
    {"sub_31AAD0", 0x31AAD0, &recomp_gen::fn_sub_31AAD0_0031aad0, &recomp_gen::fn_sub_31AAD0_0031aad0__recomp},
    {"sub_31B820", 0x31B820, &recomp_gen::fn_sub_31B820_0031b820, &recomp_gen::fn_sub_31B820_0031b820__recomp},
    {"sub_31C820", 0x31C820, &recomp_gen::fn_sub_31C820_0031c820, &recomp_gen::fn_sub_31C820_0031c820__recomp},
    {"sub_31EF80", 0x31EF80, &recomp_gen::fn_sub_31EF80_0031ef80, &recomp_gen::fn_sub_31EF80_0031ef80__recomp},
    {"sub_329890", 0x329890, &recomp_gen::fn_sub_329890_00329890, &recomp_gen::fn_sub_329890_00329890__recomp},
    {"sub_329A60", 0x329A60, &recomp_gen::fn_sub_329A60_00329a60, &recomp_gen::fn_sub_329A60_00329a60__recomp},
    {"sub_334310", 0x334310, &recomp_gen::fn_sub_334310_00334310, &recomp_gen::fn_sub_334310_00334310__recomp},
    {"sub_334390", 0x334390, &recomp_gen::fn_sub_334390_00334390, &recomp_gen::fn_sub_334390_00334390__recomp},
    {"sub_334820", 0x334820, &recomp_gen::fn_sub_334820_00334820, &recomp_gen::fn_sub_334820_00334820__recomp},
    {"sub_3348B0", 0x3348B0, &recomp_gen::fn_sub_3348B0_003348b0, &recomp_gen::fn_sub_3348B0_003348b0__recomp},
    {"sub_335180", 0x335180, &recomp_gen::fn_sub_335180_00335180, &recomp_gen::fn_sub_335180_00335180__recomp},
    {"sub_3353F0", 0x3353F0, &recomp_gen::fn_sub_3353F0_003353f0, &recomp_gen::fn_sub_3353F0_003353f0__recomp},
    {"sub_335540", 0x335540, &recomp_gen::fn_sub_335540_00335540, &recomp_gen::fn_sub_335540_00335540__recomp},
    {"sub_3359E0", 0x3359E0, &recomp_gen::fn_sub_3359E0_003359e0, &recomp_gen::fn_sub_3359E0_003359e0__recomp},
    {"sub_336630", 0x336630, &recomp_gen::fn_sub_336630_00336630, &recomp_gen::fn_sub_336630_00336630__recomp},
    {"sub_3368A0", 0x3368A0, &recomp_gen::fn_sub_3368A0_003368a0, &recomp_gen::fn_sub_3368A0_003368a0__recomp},
    {"sub_336920", 0x336920, &recomp_gen::fn_sub_336920_00336920, &recomp_gen::fn_sub_336920_00336920__recomp},
    {"sub_336DF0", 0x336DF0, &recomp_gen::fn_sub_336DF0_00336df0, &recomp_gen::fn_sub_336DF0_00336df0__recomp},
    {"sub_336E80", 0x336E80, &recomp_gen::fn_sub_336E80_00336e80, &recomp_gen::fn_sub_336E80_00336e80__recomp},
    {"sub_3377F0", 0x3377F0, &recomp_gen::fn_sub_3377F0_003377f0, &recomp_gen::fn_sub_3377F0_003377f0__recomp},
    {"sub_338530", 0x338530, &recomp_gen::fn_sub_338530_00338530, &recomp_gen::fn_sub_338530_00338530__recomp},
    {"sub_3385D0", 0x3385D0, &recomp_gen::fn_sub_3385D0_003385d0, &recomp_gen::fn_sub_3385D0_003385d0__recomp},
    {"sub_338770", 0x338770, &recomp_gen::fn_sub_338770_00338770, &recomp_gen::fn_sub_338770_00338770__recomp},
    {"sub_3387C0", 0x3387C0, &recomp_gen::fn_sub_3387C0_003387c0, &recomp_gen::fn_sub_3387C0_003387c0__recomp},
    {"sub_338AC0", 0x338AC0, &recomp_gen::fn_sub_338AC0_00338ac0, &recomp_gen::fn_sub_338AC0_00338ac0__recomp},
    {"sub_349FD0", 0x349FD0, &recomp_gen::fn_sub_349FD0_00349fd0, &recomp_gen::fn_sub_349FD0_00349fd0__recomp},
    {"sub_34A370", 0x34A370, &recomp_gen::fn_sub_34A370_0034a370, &recomp_gen::fn_sub_34A370_0034a370__recomp},
    {"sub_3A4B90", 0x3A4B90, &recomp_gen::fn_sub_3A4B90_003a4b90, &recomp_gen::fn_sub_3A4B90_003a4b90__recomp},
    {"sub_3B83D0", 0x3B83D0, &recomp_gen::fn_sub_3B83D0_003b83d0, &recomp_gen::fn_sub_3B83D0_003b83d0__recomp},
    {"sub_3B8470", 0x3B8470, &recomp_gen::fn_sub_3B8470_003b8470, &recomp_gen::fn_sub_3B8470_003b8470__recomp},
    {"sub_3B8730", 0x3B8730, &recomp_gen::fn_sub_3B8730_003b8730, &recomp_gen::fn_sub_3B8730_003b8730__recomp},
    {"sub_3B8C30", 0x3B8C30, &recomp_gen::fn_sub_3B8C30_003b8c30, &recomp_gen::fn_sub_3B8C30_003b8c30__recomp},
    {"sub_3B8E80", 0x3B8E80, &recomp_gen::fn_sub_3B8E80_003b8e80, &recomp_gen::fn_sub_3B8E80_003b8e80__recomp},
    {"sub_3BB180", 0x3BB180, &recomp_gen::fn_sub_3BB180_003bb180, &recomp_gen::fn_sub_3BB180_003bb180__recomp},
    {"sub_3BB390", 0x3BB390, &recomp_gen::fn_sub_3BB390_003bb390, &recomp_gen::fn_sub_3BB390_003bb390__recomp},
    {"sub_3BCBF0", 0x3BCBF0, &recomp_gen::fn_sub_3BCBF0_003bcbf0, &recomp_gen::fn_sub_3BCBF0_003bcbf0__recomp},
    {"sub_3BD9A0", 0x3BD9A0, &recomp_gen::fn_sub_3BD9A0_003bd9a0, &recomp_gen::fn_sub_3BD9A0_003bd9a0__recomp},
    {"sub_3C8230", 0x3C8230, &recomp_gen::fn_sub_3C8230_003c8230, &recomp_gen::fn_sub_3C8230_003c8230__recomp},
    {"sub_3C82E0", 0x3C82E0, &recomp_gen::fn_sub_3C82E0_003c82e0, &recomp_gen::fn_sub_3C82E0_003c82e0__recomp},
    {"sub_3CB100", 0x3CB100, &recomp_gen::fn_sub_3CB100_003cb100, &recomp_gen::fn_sub_3CB100_003cb100__recomp},
    {"sub_3CF240", 0x3CF240, &recomp_gen::fn_sub_3CF240_003cf240, &recomp_gen::fn_sub_3CF240_003cf240__recomp},
    {"sub_3E6130", 0x3E6130, &recomp_gen::fn_sub_3E6130_003e6130, &recomp_gen::fn_sub_3E6130_003e6130__recomp},
    {"sub_3E9200", 0x3E9200, &recomp_gen::fn_sub_3E9200_003e9200, &recomp_gen::fn_sub_3E9200_003e9200__recomp},
    {"sub_3EAD10", 0x3EAD10, &recomp_gen::fn_sub_3EAD10_003ead10, &recomp_gen::fn_sub_3EAD10_003ead10__recomp},
    {"sub_3EADD0", 0x3EADD0, &recomp_gen::fn_sub_3EADD0_003eadd0, &recomp_gen::fn_sub_3EADD0_003eadd0__recomp},
    {"sub_3EBA10", 0x3EBA10, &recomp_gen::fn_sub_3EBA10_003eba10, &recomp_gen::fn_sub_3EBA10_003eba10__recomp},
    {"sub_3EBAD0", 0x3EBAD0, &recomp_gen::fn_sub_3EBAD0_003ebad0, &recomp_gen::fn_sub_3EBAD0_003ebad0__recomp},
    {"sub_3EC090", 0x3EC090, &recomp_gen::fn_sub_3EC090_003ec090, &recomp_gen::fn_sub_3EC090_003ec090__recomp},
    {"sub_3EC150", 0x3EC150, &recomp_gen::fn_sub_3EC150_003ec150, &recomp_gen::fn_sub_3EC150_003ec150__recomp},
    {"sub_3EC6F0", 0x3EC6F0, &recomp_gen::fn_sub_3EC6F0_003ec6f0, &recomp_gen::fn_sub_3EC6F0_003ec6f0__recomp},
    {"sub_3EC7B0", 0x3EC7B0, &recomp_gen::fn_sub_3EC7B0_003ec7b0, &recomp_gen::fn_sub_3EC7B0_003ec7b0__recomp},
    {"sub_3ECD30", 0x3ECD30, &recomp_gen::fn_sub_3ECD30_003ecd30, &recomp_gen::fn_sub_3ECD30_003ecd30__recomp},
    {"sub_3ECDF0", 0x3ECDF0, &recomp_gen::fn_sub_3ECDF0_003ecdf0, &recomp_gen::fn_sub_3ECDF0_003ecdf0__recomp},
    {"sub_3ED420", 0x3ED420, &recomp_gen::fn_sub_3ED420_003ed420, &recomp_gen::fn_sub_3ED420_003ed420__recomp},
    {"sub_3EDDD0", 0x3EDDD0, &recomp_gen::fn_sub_3EDDD0_003eddd0, &recomp_gen::fn_sub_3EDDD0_003eddd0__recomp},
    {"sub_3EDE80", 0x3EDE80, &recomp_gen::fn_sub_3EDE80_003ede80, &recomp_gen::fn_sub_3EDE80_003ede80__recomp},
    {"sub_3FC060", 0x3FC060, &recomp_gen::fn_sub_3FC060_003fc060, &recomp_gen::fn_sub_3FC060_003fc060__recomp},
    {"sub_3FC540", 0x3FC540, &recomp_gen::fn_sub_3FC540_003fc540, &recomp_gen::fn_sub_3FC540_003fc540__recomp},
    {"sub_3FD820", 0x3FD820, &recomp_gen::fn_sub_3FD820_003fd820, &recomp_gen::fn_sub_3FD820_003fd820__recomp},
    {"sub_4030B0", 0x4030B0, &recomp_gen::fn_sub_4030B0_004030b0, &recomp_gen::fn_sub_4030B0_004030b0__recomp},
    {"sub_4030F0", 0x4030F0, &recomp_gen::fn_sub_4030F0_004030f0, &recomp_gen::fn_sub_4030F0_004030f0__recomp},
    {"sub_403130", 0x403130, &recomp_gen::fn_sub_403130_00403130, &recomp_gen::fn_sub_403130_00403130__recomp},
    {"sub_403220", 0x403220, &recomp_gen::fn_sub_403220_00403220, &recomp_gen::fn_sub_403220_00403220__recomp},
    {"sub_403E40", 0x403E40, &recomp_gen::fn_sub_403E40_00403e40, &recomp_gen::fn_sub_403E40_00403e40__recomp},
    {"sub_403F20", 0x403F20, &recomp_gen::fn_sub_403F20_00403f20, &recomp_gen::fn_sub_403F20_00403f20__recomp},
    {"sub_4044C0", 0x4044C0, &recomp_gen::fn_sub_4044C0_004044c0, &recomp_gen::fn_sub_4044C0_004044c0__recomp},
    {"sub_40B3A0", 0x40B3A0, &recomp_gen::fn_sub_40B3A0_0040b3a0, &recomp_gen::fn_sub_40B3A0_0040b3a0__recomp},
    {"sub_414770", 0x414770, &recomp_gen::fn_sub_414770_00414770, &recomp_gen::fn_sub_414770_00414770__recomp},
    {"sub_416240", 0x416240, &recomp_gen::fn_sub_416240_00416240, &recomp_gen::fn_sub_416240_00416240__recomp},
    {"sub_4163F0", 0x4163F0, &recomp_gen::fn_sub_4163F0_004163f0, &recomp_gen::fn_sub_4163F0_004163f0__recomp},
    {"sub_4166D0", 0x4166D0, &recomp_gen::fn_sub_4166D0_004166d0, &recomp_gen::fn_sub_4166D0_004166d0__recomp},
    {"sub_416B90", 0x416B90, &recomp_gen::fn_sub_416B90_00416b90, &recomp_gen::fn_sub_416B90_00416b90__recomp},
    {"sub_419730", 0x419730, &recomp_gen::fn_sub_419730_00419730, &recomp_gen::fn_sub_419730_00419730__recomp},
    {"sub_419790", 0x419790, &recomp_gen::fn_sub_419790_00419790, &recomp_gen::fn_sub_419790_00419790__recomp},
    {"sub_4198F0", 0x4198F0, &recomp_gen::fn_sub_4198F0_004198f0, &recomp_gen::fn_sub_4198F0_004198f0__recomp},
    {"sub_419F20", 0x419F20, &recomp_gen::fn_sub_419F20_00419f20, &recomp_gen::fn_sub_419F20_00419f20__recomp},
    {"sub_41A3F0", 0x41A3F0, &recomp_gen::fn_sub_41A3F0_0041a3f0, &recomp_gen::fn_sub_41A3F0_0041a3f0__recomp},
    {"sub_41A730", 0x41A730, &recomp_gen::fn_sub_41A730_0041a730, &recomp_gen::fn_sub_41A730_0041a730__recomp},
    {"sub_41ABC0", 0x41ABC0, &recomp_gen::fn_sub_41ABC0_0041abc0, &recomp_gen::fn_sub_41ABC0_0041abc0__recomp},
    {"sub_41AFF0", 0x41AFF0, &recomp_gen::fn_sub_41AFF0_0041aff0, &recomp_gen::fn_sub_41AFF0_0041aff0__recomp},
    {"sub_48D960", 0x48D960, &recomp_gen::fn_sub_48D960_0048d960, &recomp_gen::fn_sub_48D960_0048d960__recomp},
    {"j_RpClumpDestroy", 0x4906D0, &recomp_gen::fn_j_RpClumpDestroy_004906d0, &recomp_gen::fn_j_RpClumpDestroy_004906d0__recomp},
    {"j_RpAtomicDestroy", 0x4906E0, &recomp_gen::fn_j_RpAtomicDestroy_004906e0, &recomp_gen::fn_j_RpAtomicDestroy_004906e0__recomp},
    {"sub_490810", 0x490810, &recomp_gen::fn_sub_490810_00490810, &recomp_gen::fn_sub_490810_00490810__recomp},
    {"sub_4AE070", 0x4AE070, &recomp_gen::fn_sub_4AE070_004ae070, &recomp_gen::fn_sub_4AE070_004ae070__recomp},
    {"sub_4AE0C0", 0x4AE0C0, &recomp_gen::fn_sub_4AE0C0_004ae0c0, &recomp_gen::fn_sub_4AE0C0_004ae0c0__recomp},
    {"sub_4AEF60", 0x4AEF60, &recomp_gen::fn_sub_4AEF60_004aef60, &recomp_gen::fn_sub_4AEF60_004aef60__recomp},
    {"sub_4B4C70", 0x4B4C70, &recomp_gen::fn_sub_4B4C70_004b4c70, &recomp_gen::fn_sub_4B4C70_004b4c70__recomp},
    {"sub_4B4D60", 0x4B4D60, &recomp_gen::fn_sub_4B4D60_004b4d60, &recomp_gen::fn_sub_4B4D60_004b4d60__recomp},
    {"sub_4B5000", 0x4B5000, &recomp_gen::fn_sub_4B5000_004b5000, &recomp_gen::fn_sub_4B5000_004b5000__recomp},
    {"sub_4B78B0", 0x4B78B0, &recomp_gen::fn_sub_4B78B0_004b78b0, &recomp_gen::fn_sub_4B78B0_004b78b0__recomp},
    {"sub_4C0820", 0x4C0820, &recomp_gen::fn_sub_4C0820_004c0820, &recomp_gen::fn_sub_4C0820_004c0820__recomp},
    {"sub_4C3EE0", 0x4C3EE0, &recomp_gen::fn_sub_4C3EE0_004c3ee0, &recomp_gen::fn_sub_4C3EE0_004c3ee0__recomp},
    {"sub_4C5FC0", 0x4C5FC0, &recomp_gen::fn_sub_4C5FC0_004c5fc0, &recomp_gen::fn_sub_4C5FC0_004c5fc0__recomp},
    {"sub_4C7100", 0x4C7100, &recomp_gen::fn_sub_4C7100_004c7100, &recomp_gen::fn_sub_4C7100_004c7100__recomp},
    {"sub_4CA500", 0x4CA500, &recomp_gen::fn_sub_4CA500_004ca500, &recomp_gen::fn_sub_4CA500_004ca500__recomp},
    {"sub_4CF5C0", 0x4CF5C0, &recomp_gen::fn_sub_4CF5C0_004cf5c0, &recomp_gen::fn_sub_4CF5C0_004cf5c0__recomp},
    {"sub_4D09D0", 0x4D09D0, &recomp_gen::fn_sub_4D09D0_004d09d0, &recomp_gen::fn_sub_4D09D0_004d09d0__recomp},
    {"sub_4D84A0", 0x4D84A0, &recomp_gen::fn_sub_4D84A0_004d84a0, &recomp_gen::fn_sub_4D84A0_004d84a0__recomp},
    {"sub_4DB350", 0x4DB350, &recomp_gen::fn_sub_4DB350_004db350, &recomp_gen::fn_sub_4DB350_004db350__recomp},
    {"sub_4DD2E0", 0x4DD2E0, &recomp_gen::fn_sub_4DD2E0_004dd2e0, &recomp_gen::fn_sub_4DD2E0_004dd2e0__recomp},
    {"sub_4EBFB0", 0x4EBFB0, &recomp_gen::fn_sub_4EBFB0_004ebfb0, &recomp_gen::fn_sub_4EBFB0_004ebfb0__recomp},
    {"_dualPrimeVector", 0x4FAFE0, &recomp_gen::fn__dualPrimeVector_004fafe0, &recomp_gen::fn__dualPrimeVector_004fafe0__recomp},
    {"_decodeOrSkipField", 0x500858, &recomp_gen::fn__decodeOrSkipField_00500858, &recomp_gen::fn__decodeOrSkipField_00500858__recomp},
    {"sceMc2UnformatAsync", 0x513648, &recomp_gen::fn_sceMc2UnformatAsync_00513648, &recomp_gen::fn_sceMc2UnformatAsync_00513648__recomp},
    {"sceMc2ReadFastFileAsync", 0x513A88, &recomp_gen::fn_sceMc2ReadFastFileAsync_00513a88, &recomp_gen::fn_sceMc2ReadFastFileAsync_00513a88__recomp},
    {"sceMc2WriteFastFileAsync", 0x513BA8, &recomp_gen::fn_sceMc2WriteFastFileAsync_00513ba8, &recomp_gen::fn_sceMc2WriteFastFileAsync_00513ba8__recomp},
    {"sceMc2DeleteAsync", 0x513EE0, &recomp_gen::fn_sceMc2DeleteAsync_00513ee0, &recomp_gen::fn_sceMc2DeleteAsync_00513ee0__recomp},
    {"sceMc2GetDirAsync", 0x513FC8, &recomp_gen::fn_sceMc2GetDirAsync_00513fc8, &recomp_gen::fn_sceMc2GetDirAsync_00513fc8__recomp},
    {"sceMc2ChdirAsync", 0x5141F0, &recomp_gen::fn_sceMc2ChdirAsync_005141f0, &recomp_gen::fn_sceMc2ChdirAsync_005141f0__recomp},
    {"sceMc2ChmodAsync", 0x5142F0, &recomp_gen::fn_sceMc2ChmodAsync_005142f0, &recomp_gen::fn_sceMc2ChmodAsync_005142f0__recomp},
    {"sceMc2RenameAsync", 0x5143F0, &recomp_gen::fn_sceMc2RenameAsync_005143f0, &recomp_gen::fn_sceMc2RenameAsync_005143f0__recomp},
    {"sceMc2GetEntSpaceAsync", 0x514510, &recomp_gen::fn_sceMc2GetEntSpaceAsync_00514510, &recomp_gen::fn_sceMc2GetEntSpaceAsync_00514510__recomp},
    {"_sceMcCoreBlockErase", 0x51BBD8, &recomp_gen::fn__sceMcCoreBlockErase_0051bbd8, &recomp_gen::fn__sceMcCoreBlockErase_0051bbd8__recomp},
    {"_sceMcCoreReadPageFast", 0x51BD10, &recomp_gen::fn__sceMcCoreReadPageFast_0051bd10, &recomp_gen::fn__sceMcCoreReadPageFast_0051bd10__recomp},
    {"_sceMcCoreWritePageFast", 0x51BF40, &recomp_gen::fn__sceMcCoreWritePageFast_0051bf40, &recomp_gen::fn__sceMcCoreWritePageFast_0051bf40__recomp},
    {"_sceMcCoreDeleteSocket", 0x51C280, &recomp_gen::fn__sceMcCoreDeleteSocket_0051c280, &recomp_gen::fn__sceMcCoreDeleteSocket_0051c280__recomp},
    {"calloc", 0x51E150, &recomp_gen::fn_calloc_0051e150, &recomp_gen::fn_calloc_0051e150__recomp},
    {"realloc", 0x522F98, &recomp_gen::fn_realloc_00522f98, &recomp_gen::fn_realloc_00522f98__recomp},
    {"sub_535888", 0x535888, &recomp_gen::fn_sub_535888_00535888, &recomp_gen::fn_sub_535888_00535888__recomp},
    {"sub_5358E0", 0x5358E0, &recomp_gen::fn_sub_5358E0_005358e0, &recomp_gen::fn_sub_5358E0_005358e0__recomp},
    {"sub_535A80", 0x535A80, &recomp_gen::fn_sub_535A80_00535a80, &recomp_gen::fn_sub_535A80_00535a80__recomp},
    {"sub_535DA8", 0x535DA8, &recomp_gen::fn_sub_535DA8_00535da8, &recomp_gen::fn_sub_535DA8_00535da8__recomp},
    {"sub_537CF0", 0x537CF0, &recomp_gen::fn_sub_537CF0_00537cf0, &recomp_gen::fn_sub_537CF0_00537cf0__recomp},
    {"sub_538040", 0x538040, &recomp_gen::fn_sub_538040_00538040, &recomp_gen::fn_sub_538040_00538040__recomp},
    {"sub_538048", 0x538048, &recomp_gen::fn_sub_538048_00538048, &recomp_gen::fn_sub_538048_00538048__recomp},
    {"r_lock_def_free_0", 0x541CC8, &recomp_gen::fn_r_lock_def_free_0_00541cc8, &recomp_gen::fn_r_lock_def_free_0_00541cc8__recomp},
    {"sub_542A88", 0x542A88, &recomp_gen::fn_sub_542A88_00542a88, &recomp_gen::fn_sub_542A88_00542a88__recomp},
    {"sub_542C70", 0x542C70, &recomp_gen::fn_sub_542C70_00542c70, &recomp_gen::fn_sub_542C70_00542c70__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

constexpr u32 kWaitSema = 0x5031A0u;    // _sceWaitSema (a kernel wrapper; stood in for the libmc2 requests)
constexpr u32 kSignalSema = 0x503180u;  // _sceSignalSema
constexpr u32 kGBtl = 0x7CE3ECu;        // gBtl (the battle work)
constexpr u32 kNmLists[] = {0x7CE680u, 0x7CE684u, 0x7CE688u};  // the nm list objects (NmListObject)

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 r16(Machine& m, u32 va) {
    u16 v = 0;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
bool ram_ptr(u32 p) { return p >= 0x00100000u && p < 0x01F00000u; }

// Pairs with the stand-ins: both bodies get a fresh world (heap, printf / sprintf, the H_Cdvd file layer, the libmc2
// semaphore wrappers) and the two call logs, heaps and file layers must be equal.
StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    const EntryBypass entry{g_fn[0]};  // past its own stand-in (calloc / realloc have one in install_standard)
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    const EntryBypass entry{g_fn[1]};
    g_fn[1](ctx);
}
int g_pairs = 0;
int g_stops = 0;
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        install_standard(*w);
        w->si.install_recorder(kWaitSema, "_sceWaitSema", 0);
        w->si.install_recorder(kSignalSema, "_sceSignalSema", 0);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    CHECK(wh->heap.live() == wr->heap.live());
    CHECK(wh->cd.nodes == wr->cd.nodes);
    ++g_pairs;
    g_stops += r.stopped ? 1 : 0;
    return r;
}

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

s64 sv(const hgp::Run& r) { return static_cast<s64>(r.end.gpr[GPR_V0].u64[0]); }

// --- the live objects of a snapshot ---------------------------------------------------------------------------------
// gBtl and its unit list (head +344, next +2612) on the battle routes, the nm list objects of the menus, a sample of
// the live H_Malloc blocks (model / effect / message records) and field-UI style handles ((kind << 10) | index).
struct Pool {
    std::vector<u32> ptrs;
    std::vector<u32> units;
};
Pool live_pool(Machine& m) {
    Pool p;
    const u32 btl = r32(m, kGBtl);
    if (ram_ptr(btl)) {
        p.ptrs.push_back(btl);
        u32 u = r32(m, btl + 344);
        for (int i = 0; i < 16 && ram_ptr(u); ++i) {
            p.units.push_back(u);
            u = r32(m, u + 2612);
        }
    }
    for (u32 g : kNmLists)
        if (const u32 o = r32(m, g); ram_ptr(o)) p.ptrs.push_back(o);
    const auto blocks = h_malloc_blocks(m);
    for (std::size_t i = 0; i < blocks.size(); i += 1 + blocks.size() / 48)
        if (ram_ptr(blocks[i].first)) p.ptrs.push_back(blocks[i].first);
    for (u32 u : p.units) p.ptrs.push_back(u);
    return p;
}
u64 live_arg(std::mt19937& rng, const Pool& p) {
    const u32 k = rng() % 12;
    if (k < 3 && !p.units.empty()) return sx(p.units[rng() % p.units.size()]);
    if (k < 7 && !p.ptrs.empty()) return sx(p.ptrs[rng() % p.ptrs.size()]);
    if (k < 9) return rng() % 8;
    if (k < 10) return (static_cast<u64>(rng() % 16) << 10) | (rng() % 8);  // a handle (kind, index)
    if (k < 11) return 0;
    return sx(kWorld + ((rng() % kWorldSize) & ~15u));
}

const char* const kSnaps[] = {"b_5800", "dorm_replay_4900", "climb_ref_17000"};

}  // namespace

TEST_CASE("game(sweep5e): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);  // the RW memory slots hold the retail functions (their stand-ins serve them)
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    g_pairs = g_stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            spair(*m, c.hand, c.recomp, args, seed, c.name);
        }
    }
    MESSAGE(g_pairs << " pairs on random worlds, " << g_stops << " stopped early (identically)");
}

// Every body over the RAM of the replay snapshots: the battle work and its units (b_5800), the menus' nm list
// objects, the live heap blocks -- the arguments drawn from those objects.
TEST_CASE("game(sweep5e): every body equals its recompiled body on the replay snapshots' live objects") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? std::max<u32>(1, static_cast<u32>(std::strtoul(env, nullptr, 10)) / 16) : 4u;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    g_pairs = g_stops = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        const Pool pool = live_pool(*m);
        CHECK(!pool.ptrs.empty());
        if (std::string(dir) == "b_5800") CHECK(!pool.units.empty());  // the battle route has units
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 seed = 1; seed <= seeds; ++seed) {
                if (trace) std::fprintf(stderr, "%s %s seed %u\n", dir, c.name, seed);
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                std::mt19937 rng{seed * 131u + c.addr};
                const Args args{live_arg(rng, pool), live_arg(rng, pool), live_arg(rng, pool), live_arg(rng, pool)};
                spair(*m, c.hand, c.recomp, args, seed, c.name);
            }
        }
        MESSAGE(std::string(dir) << ": " << pool.ptrs.size() << " live objects, " << pool.units.size() << " battle units");
    }
    MESSAGE(g_pairs << " pairs on snapshot objects, " << g_stops << " stopped early (identically)");
}

// The battle helpers' branch values: a unit record with the +162 byte / flag / id words each branch compares.
TEST_CASE("game(sweep5e): battle helpers on units at their branch values") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    static const u16 kIds[] = {256, 263, 281, 295, 7};
    g_pairs = g_stops = 0;
    for (const char* name : {"sub_2EFB40", "sub_2EC190", "sub_2E97E0", "sub_2EF9D0", "sub_2F8790", "sub_2E3AE0"}) {
        const Case& c = find_case(name);
        for (u32 seed = 1; seed <= 20; ++seed) {
            std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
            const Pool pool = live_pool(*m);
            if (pool.units.empty()) break;
            std::mt19937 rng{seed * 977u + c.addr};
            const u32 unit = pool.units[rng() % pool.units.size()];
            *m->at(unit + 162) = static_cast<u8>(rng() % 3 == 0 ? 0 : 1);
            w32(*m, unit + 152, r32(*m, unit + 152) ^ (rng() % 2 ? 2u : 0u));
            w16(*m, unit + 164, kIds[rng() % 5]);
            if (std::string(name) == "sub_2F8790" && rng() % 2) w32(*m, r32(*m, kGBtl) + 2836, 0);
            // sub_2EC190's action record: +48 the unit, +26 the flag word
            const u32 act = kWorld;
            std::memset(m->at(act), 0, 64);
            w32(*m, act + 48, unit);
            w16(*m, act + 26, static_cast<u16>(rng() % 2 ? 0x80 : 0));
            const Args args{sx(name == std::string("sub_2EC190") ? act : unit), sx(unit), sx(act), rng() % 4};
            spair(*m, c.hand, c.recomp, args, seed, name);
        }
    }
    MESSAGE(g_pairs << " battle-helper pairs, " << g_stops << " stopped early (identically)");
}

// Documented rules, from the instructions (both bodies run and are compared, then the result is checked). Only results
// that hold whatever the callees are (replaced or recompiled) are checked.
TEST_CASE("game(sweep5e): getters, setters, string compares, table lookup") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    g_pairs = g_stops = 0;
    std::mt19937 rng{5};
    hgp::random_world(*m, kWorld, kWorldSize, rng);
    const u32 rec = kWorld + 0x100u;
    for (u32 i = 0; i < 256; i += 4) w32(*m, rec + i, 0x80000000u + i * 0x01010101u);
    // getters: the sign-extended word / halfword at the offset
    CHECK(sv(spair(*m, find_case("sub_4B4D60").hand, find_case("sub_4B4D60").recomp, {sx(rec), 0, 0, 0}, 1, "4B4D60")) ==
          static_cast<s32>(r32(*m, rec + 36)));
    CHECK(sv(spair(*m, find_case("sub_4C0820").hand, find_case("sub_4C0820").recomp, {sx(rec), 0, 0, 0}, 1, "4C0820")) ==
          static_cast<s32>(r32(*m, rec + 16)));
    w32(*m, 0x7CE928u, 0xFFFFFFF0u);
    CHECK(sv(spair(*m, find_case("sub_4CA500").hand, find_case("sub_4CA500").recomp, {0, 0, 0, 0}, 1, "4CA500")) == -16);
    CHECK(sv(spair(*m, find_case("sub_538040").hand, find_case("sub_538040").recomp, {sx(rec), 0, 0, 0}, 1, "538040")) ==
          static_cast<s16>(r16(*m, rec + 224)));
    for (u32 k = 0; k < 4; ++k)
        CHECK(sv(spair(*m, find_case("sub_538048").hand, find_case("sub_538048").recomp, {sx(rec), k, 0, 0}, 1, "538048")) ==
              static_cast<s16>(r16(*m, rec + 226 + 2 * k)));
    // setters
    spair(*m, find_case("sub_535A80").hand, find_case("sub_535A80").recomp, {sx(rec), 0, 0, 0}, 1, "535A80");
    CHECK(*m->at(rec + 1) == 0);
    spair(*m, find_case("sub_535DA8").hand, find_case("sub_535DA8").recomp, {sx(rec), 0x12345678u, 0, 0}, 1, "535DA8");
    CHECK(r32(*m, rec + 32) == 0x12345678u);
    // 4 when a0 points at a non-zero word, else 0
    const Case& c4 = find_case("sub_4D84A0");
    CHECK(sv(spair(*m, c4.hand, c4.recomp, {0, 0, 0, 0}, 1, "4D84A0 null")) == 0);
    w32(*m, rec, 0);
    CHECK(sv(spair(*m, c4.hand, c4.recomp, {sx(rec), 0, 0, 0}, 1, "4D84A0 zero")) == 0);
    w32(*m, rec, 9);
    CHECK(sv(spair(*m, c4.hand, c4.recomp, {sx(rec), 0, 0, 0}, 1, "4D84A0 set")) == 4);
    // case-insensitive compares
    const u32 s1 = kWorld + 0x800u, s2 = kWorld + 0x900u, s3 = kWorld + 0xA00u;
    wstr(*m, s1, "Hello_World");
    wstr(*m, s2, "hELLO_wORLD");
    wstr(*m, s3, "Hello_Wprld");
    const Case& ci = find_case("sub_4C7100");
    CHECK(sv(spair(*m, ci.hand, ci.recomp, {sx(s1), sx(s2), 0, 0}, 1, "4C7100 equal")) == 0);
    CHECK(sv(spair(*m, ci.hand, ci.recomp, {sx(s1), sx(s3), 0, 0}, 1, "4C7100 differ")) != 0);
    CHECK(sv(spair(*m, ci.hand, ci.recomp, {0, sx(s2), 0, 0}, 1, "4C7100 null")) == 0);
    const Case& cp = find_case("sub_4D09D0");
    CHECK(sv(spair(*m, cp.hand, cp.recomp, {sx(s1), sx(s3), 0, 0}, 1, "4D09D0 differ")) == 0);
    spair(*m, cp.hand, cp.recomp, {sx(s1), sx(s2), 0, 0}, 1, "4D09D0 equal");
    // sub_3BD9A0: an empty table finds nothing (0) without reaching MT_Misc_BitChk
    w32(*m, 0x95B728u, 0);
    const Case& ct = find_case("sub_3BD9A0");
    CHECK(sv(spair(*m, ct.hand, ct.recomp, {5, 1, 0, 0}, 1, "3BD9A0 empty")) == 0);
    // sub_419730: returns 1 after its call (when the callee runs)
    const u32 obj = kWorld + 0xC00u;
    w32(*m, obj, obj + 0x40);
    w32(*m, obj + 0x40 + 12, 0xFFFFu);
    const Case& cm = find_case("sub_419730");
    const hgp::Run r = spair(*m, cm.hand, cm.recomp, {0, sx(obj), 0, 0}, 1, "419730");
    if (!r.stopped) CHECK(sv(r) == 1);
    MESSAGE(g_pairs << " rule pairs");
}

#else

TEST_CASE("game(sweep5e): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
