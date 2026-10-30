// Pair tests of slice sweep5c (game/src/ui/sweep5c.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the packet's replay snapshots (dorm_replay_4900, b_5800, climb_ref_17000, fusion_ref_6300, shop_ref_4100) with
//     arguments of each function's kind (kKinds): kwln-style tasks with a work list, command tables, model handles,
//     clump-style atomic lists with a real callback, dvCi handles, LSN / plain file names, small ids, the scene
//     record of the snapshot (its resource manager and type lists);
//   * documented rules: the scene-record accessors and the per-type resource count (field6_util.h scene_resources),
//     MT_Scene_Load's cache hit, the dvCi handle size / seek / status queries, the LSN-name test, the PS2RNA volume /
//     pan clamps, the 32-entry ring queue of sub_58A108, the task work-list walk of sub_1A4510, the clump iterators.
// Compared by tests/game/handgen_pairs.h (hgp::pair) and stand_ins.h (run_pair_si): the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log.
#include "handgen_pairs.h"
#include "sweep2_util.h"

#include "p3fes/game/sweep5c.h"

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
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_17B860_0017b860(EEContext&);  // generated body
void fn_sub_17B860_0017b860__recomp(EEContext&);  // recompiled
void fn_sub_1A0D00_001a0d00(EEContext&);  // generated body
void fn_sub_1A0D00_001a0d00__recomp(EEContext&);  // recompiled
void fn_sub_1A0D80_001a0d80(EEContext&);  // generated body
void fn_sub_1A0D80_001a0d80__recomp(EEContext&);  // recompiled
void fn_sub_1A3AE0_001a3ae0(EEContext&);  // generated body
void fn_sub_1A3AE0_001a3ae0__recomp(EEContext&);  // recompiled
void fn_sub_1A3BF0_001a3bf0(EEContext&);  // generated body
void fn_sub_1A3BF0_001a3bf0__recomp(EEContext&);  // recompiled
void fn_sub_1A3DC0_001a3dc0(EEContext&);  // generated body
void fn_sub_1A3DC0_001a3dc0__recomp(EEContext&);  // recompiled
void fn_sub_1A41B0_001a41b0(EEContext&);  // generated body
void fn_sub_1A41B0_001a41b0__recomp(EEContext&);  // recompiled
void fn_sub_1A4510_001a4510(EEContext&);  // generated body
void fn_sub_1A4510_001a4510__recomp(EEContext&);  // recompiled
void fn_sub_1A4CD0_001a4cd0(EEContext&);  // generated body
void fn_sub_1A4CD0_001a4cd0__recomp(EEContext&);  // recompiled
void fn_sub_1A4DC0_001a4dc0(EEContext&);  // generated body
void fn_sub_1A4DC0_001a4dc0__recomp(EEContext&);  // recompiled
void fn_sub_1A4E60_001a4e60(EEContext&);  // generated body
void fn_sub_1A4E60_001a4e60__recomp(EEContext&);  // recompiled
void fn_sub_20B250_0020b250(EEContext&);  // generated body
void fn_sub_20B250_0020b250__recomp(EEContext&);  // recompiled
void fn_sub_20C400_0020c400(EEContext&);  // generated body
void fn_sub_20C400_0020c400__recomp(EEContext&);  // recompiled
void fn_sub_20C500_0020c500(EEContext&);  // generated body
void fn_sub_20C500_0020c500__recomp(EEContext&);  // recompiled
void fn_sub_21AB80_0021ab80(EEContext&);  // generated body
void fn_sub_21AB80_0021ab80__recomp(EEContext&);  // recompiled
void fn_sub_2B94F0_002b94f0(EEContext&);  // generated body
void fn_sub_2B94F0_002b94f0__recomp(EEContext&);  // recompiled
void fn_sub_316E00_00316e00(EEContext&);  // generated body
void fn_sub_316E00_00316e00__recomp(EEContext&);  // recompiled
void fn_sub_316F70_00316f70(EEContext&);  // generated body
void fn_sub_316F70_00316f70__recomp(EEContext&);  // recompiled
void fn_sub_324BD0_00324bd0(EEContext&);  // generated body
void fn_sub_324BD0_00324bd0__recomp(EEContext&);  // recompiled
void fn_sub_3252A0_003252a0(EEContext&);  // generated body
void fn_sub_3252A0_003252a0__recomp(EEContext&);  // recompiled
void fn_sub_325920_00325920(EEContext&);  // generated body
void fn_sub_325920_00325920__recomp(EEContext&);  // recompiled
void fn_sub_329BA0_00329ba0(EEContext&);  // generated body
void fn_sub_329BA0_00329ba0__recomp(EEContext&);  // recompiled
void fn_sub_32A770_0032a770(EEContext&);  // generated body
void fn_sub_32A770_0032a770__recomp(EEContext&);  // recompiled
void fn_sub_32A890_0032a890(EEContext&);  // generated body
void fn_sub_32A890_0032a890__recomp(EEContext&);  // recompiled
void fn_sub_358A30_00358a30(EEContext&);  // generated body
void fn_sub_358A30_00358a30__recomp(EEContext&);  // recompiled
void fn_sub_359380_00359380(EEContext&);  // generated body
void fn_sub_359380_00359380__recomp(EEContext&);  // recompiled
void fn_sub_3A2090_003a2090(EEContext&);  // generated body
void fn_sub_3A2090_003a2090__recomp(EEContext&);  // recompiled
void fn_sub_3B2F90_003b2f90(EEContext&);  // generated body
void fn_sub_3B2F90_003b2f90__recomp(EEContext&);  // recompiled
void fn_MT_Scene_Load_003b5760(EEContext&);  // generated body
void fn_MT_Scene_Load_003b5760__recomp(EEContext&);  // recompiled
void fn_sub_3B5A10_003b5a10(EEContext&);  // generated body
void fn_sub_3B5A10_003b5a10__recomp(EEContext&);  // recompiled
void fn_sub_3B5AB0_003b5ab0(EEContext&);  // generated body
void fn_sub_3B5AB0_003b5ab0__recomp(EEContext&);  // recompiled
void fn_sub_3B5CF0_003b5cf0(EEContext&);  // generated body
void fn_sub_3B5CF0_003b5cf0__recomp(EEContext&);  // recompiled
void fn_sub_3B5D00_003b5d00(EEContext&);  // generated body
void fn_sub_3B5D00_003b5d00__recomp(EEContext&);  // recompiled
void fn_sub_3B5D10_003b5d10(EEContext&);  // generated body
void fn_sub_3B5D10_003b5d10__recomp(EEContext&);  // recompiled
void fn_sub_3B5DF0_003b5df0(EEContext&);  // generated body
void fn_sub_3B5DF0_003b5df0__recomp(EEContext&);  // recompiled
void fn_sub_3B6000_003b6000(EEContext&);  // generated body
void fn_sub_3B6000_003b6000__recomp(EEContext&);  // recompiled
void fn_sub_3B6030_003b6030(EEContext&);  // generated body
void fn_sub_3B6030_003b6030__recomp(EEContext&);  // recompiled
void fn_sub_3B6270_003b6270(EEContext&);  // generated body
void fn_sub_3B6270_003b6270__recomp(EEContext&);  // recompiled
void fn_sub_3B65D0_003b65d0(EEContext&);  // generated body
void fn_sub_3B65D0_003b65d0__recomp(EEContext&);  // recompiled
void fn_sub_3B8B30_003b8b30(EEContext&);  // generated body
void fn_sub_3B8B30_003b8b30__recomp(EEContext&);  // recompiled
void fn_sub_3B91C0_003b91c0(EEContext&);  // generated body
void fn_sub_3B91C0_003b91c0__recomp(EEContext&);  // recompiled
void fn_sub_3B9320_003b9320(EEContext&);  // generated body
void fn_sub_3B9320_003b9320__recomp(EEContext&);  // recompiled
void fn_sub_3B9550_003b9550(EEContext&);  // generated body
void fn_sub_3B9550_003b9550__recomp(EEContext&);  // recompiled
void fn_sub_3BB010_003bb010(EEContext&);  // generated body
void fn_sub_3BB010_003bb010__recomp(EEContext&);  // recompiled
void fn_sub_3BB1D0_003bb1d0(EEContext&);  // generated body
void fn_sub_3BB1D0_003bb1d0__recomp(EEContext&);  // recompiled
void fn_sub_3BCC80_003bcc80(EEContext&);  // generated body
void fn_sub_3BCC80_003bcc80__recomp(EEContext&);  // recompiled
void fn_sub_3C77A0_003c77a0(EEContext&);  // generated body
void fn_sub_3C77A0_003c77a0__recomp(EEContext&);  // recompiled
void fn_sub_3C7B90_003c7b90(EEContext&);  // generated body
void fn_sub_3C7B90_003c7b90__recomp(EEContext&);  // recompiled
void fn_sub_3C7BC0_003c7bc0(EEContext&);  // generated body
void fn_sub_3C7BC0_003c7bc0__recomp(EEContext&);  // recompiled
void fn_sub_3C7C20_003c7c20(EEContext&);  // generated body
void fn_sub_3C7C20_003c7c20__recomp(EEContext&);  // recompiled
void fn_sub_3C7D80_003c7d80(EEContext&);  // generated body
void fn_sub_3C7D80_003c7d80__recomp(EEContext&);  // recompiled
void fn_sub_3C7E20_003c7e20(EEContext&);  // generated body
void fn_sub_3C7E20_003c7e20__recomp(EEContext&);  // recompiled
void fn_sub_3C8F70_003c8f70(EEContext&);  // generated body
void fn_sub_3C8F70_003c8f70__recomp(EEContext&);  // recompiled
void fn_sub_3C94E0_003c94e0(EEContext&);  // generated body
void fn_sub_3C94E0_003c94e0__recomp(EEContext&);  // recompiled
void fn_sub_3C9790_003c9790(EEContext&);  // generated body
void fn_sub_3C9790_003c9790__recomp(EEContext&);  // recompiled
void fn_fclMisc_CreatePsStatusTasks_003c9850(EEContext&);  // generated body
void fn_fclMisc_CreatePsStatusTasks_003c9850__recomp(EEContext&);  // recompiled
void fn_sub_3C9AB0_003c9ab0(EEContext&);  // generated body
void fn_sub_3C9AB0_003c9ab0__recomp(EEContext&);  // recompiled
void fn_sub_3C9D00_003c9d00(EEContext&);  // generated body
void fn_sub_3C9D00_003c9d00__recomp(EEContext&);  // recompiled
void fn_sub_464120_00464120(EEContext&);  // generated body
void fn_sub_464120_00464120__recomp(EEContext&);  // recompiled
void fn_sub_48EE80_0048ee80(EEContext&);  // generated body
void fn_sub_48EE80_0048ee80__recomp(EEContext&);  // recompiled
void fn_sub_48EED0_0048eed0(EEContext&);  // generated body
void fn_sub_48EED0_0048eed0__recomp(EEContext&);  // recompiled
void fn_sub_4916D0_004916d0(EEContext&);  // generated body
void fn_sub_4916D0_004916d0__recomp(EEContext&);  // recompiled
void fn_sub_491EA0_00491ea0(EEContext&);  // generated body
void fn_sub_491EA0_00491ea0__recomp(EEContext&);  // recompiled
void fn_sub_4932C0_004932c0(EEContext&);  // generated body
void fn_sub_4932C0_004932c0__recomp(EEContext&);  // recompiled
void fn_sub_4AA410_004aa410(EEContext&);  // generated body
void fn_sub_4AA410_004aa410__recomp(EEContext&);  // recompiled
void fn_sub_4AAA60_004aaa60(EEContext&);  // generated body
void fn_sub_4AAA60_004aaa60__recomp(EEContext&);  // recompiled
void fn_sub_4B3710_004b3710(EEContext&);  // generated body
void fn_sub_4B3710_004b3710__recomp(EEContext&);  // recompiled
void fn_sub_4B6EB0_004b6eb0(EEContext&);  // generated body
void fn_sub_4B6EB0_004b6eb0__recomp(EEContext&);  // recompiled
void fn_sub_4C1D50_004c1d50(EEContext&);  // generated body
void fn_sub_4C1D50_004c1d50__recomp(EEContext&);  // recompiled
void fn_sub_4C9D70_004c9d70(EEContext&);  // generated body
void fn_sub_4C9D70_004c9d70__recomp(EEContext&);  // recompiled
void fn__sceMpegError_00502668(EEContext&);  // generated body
void fn__sceMpegError_00502668__recomp(EEContext&);  // recompiled
void fn__sceMpegError1_005026c0(EEContext&);  // generated body
void fn__sceMpegError1_005026c0__recomp(EEContext&);  // recompiled
void fn__sceRemoveIntcHandler_00502e60(EEContext&);  // generated body
void fn__sceRemoveIntcHandler_00502e60__recomp(EEContext&);  // recompiled
void fn__sceExitDeleteThread_00502fa0(EEContext&);  // generated body
void fn__sceExitDeleteThread_00502fa0__recomp(EEContext&);  // recompiled
void fn_sceFsInit_00508170(EEContext&);  // generated body
void fn_sceFsInit_00508170__recomp(EEContext&);  // recompiled
void fn_sceOpen_00508670(EEContext&);  // generated body
void fn_sceOpen_00508670__recomp(EEContext&);  // recompiled
void fn_sceClose_00508900(EEContext&);  // generated body
void fn_sceClose_00508900__recomp(EEContext&);  // recompiled
void fn_sceLseek_00508a78(EEContext&);  // generated body
void fn_sceLseek_00508a78__recomp(EEContext&);  // recompiled
void fn__sceCallCode_00509758(EEContext&);  // generated body
void fn__sceCallCode_00509758__recomp(EEContext&);  // recompiled
void fn_sub_50E508_0050e508(EEContext&);  // generated body
void fn_sub_50E508_0050e508__recomp(EEContext&);  // recompiled
void fn__sceMcCoreReadClock_0051b5f0(EEContext&);  // generated body
void fn__sceMcCoreReadClock_0051b5f0__recomp(EEContext&);  // recompiled
void fn___swrite_00523cc0(EEContext&);  // generated body
void fn___swrite_00523cc0__recomp(EEContext&);  // recompiled
void fn_sub_535DD8_00535dd8(EEContext&);  // generated body
void fn_sub_535DD8_00535dd8__recomp(EEContext&);  // recompiled
void fn_sub_535E28_00535e28(EEContext&);  // generated body
void fn_sub_535E28_00535e28__recomp(EEContext&);  // recompiled
void fn_sub_535FC0_00535fc0(EEContext&);  // generated body
void fn_sub_535FC0_00535fc0__recomp(EEContext&);  // recompiled
void fn_sub_535FF0_00535ff0(EEContext&);  // generated body
void fn_sub_535FF0_00535ff0__recomp(EEContext&);  // recompiled
void fn_sub_536080_00536080(EEContext&);  // generated body
void fn_sub_536080_00536080__recomp(EEContext&);  // recompiled
void fn_my_malloc_00537790(EEContext&);  // generated body
void fn_my_malloc_00537790__recomp(EEContext&);  // recompiled
void fn_sub_537890_00537890(EEContext&);  // generated body
void fn_sub_537890_00537890__recomp(EEContext&);  // recompiled
void fn_sub_537D90_00537d90(EEContext&);  // generated body
void fn_sub_537D90_00537d90__recomp(EEContext&);  // recompiled
void fn_sub_537F08_00537f08(EEContext&);  // generated body
void fn_sub_537F08_00537f08__recomp(EEContext&);  // recompiled
void fn_sub_538060_00538060(EEContext&);  // generated body
void fn_sub_538060_00538060__recomp(EEContext&);  // recompiled
void fn_sub_5382C0_005382c0(EEContext&);  // generated body
void fn_sub_5382C0_005382c0__recomp(EEContext&);  // recompiled
void fn_sub_5382C8_005382c8(EEContext&);  // generated body
void fn_sub_5382C8_005382c8__recomp(EEContext&);  // recompiled
void fn_sub_538348_00538348(EEContext&);  // generated body
void fn_sub_538348_00538348__recomp(EEContext&);  // recompiled
void fn_sub_538360_00538360(EEContext&);  // generated body
void fn_sub_538360_00538360__recomp(EEContext&);  // recompiled
void fn_sub_5383A8_005383a8(EEContext&);  // generated body
void fn_sub_5383A8_005383a8__recomp(EEContext&);  // recompiled
void fn_sub_53AE08_0053ae08(EEContext&);  // generated body
void fn_sub_53AE08_0053ae08__recomp(EEContext&);  // recompiled
void fn_sub_53AE60_0053ae60(EEContext&);  // generated body
void fn_sub_53AE60_0053ae60__recomp(EEContext&);  // recompiled
void fn_sub_53EA30_0053ea30(EEContext&);  // generated body
void fn_sub_53EA30_0053ea30__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_0053ea50(EEContext&);  // generated body
void fn_r_lock_def_free_0053ea50__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_0053ea70(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_0053ea70__recomp(EEContext&);  // recompiled
void fn_sub_5419F8_005419f8(EEContext&);  // generated body
void fn_sub_5419F8_005419f8__recomp(EEContext&);  // recompiled
void fn_sub_541A10_00541a10(EEContext&);  // generated body
void fn_sub_541A10_00541a10__recomp(EEContext&);  // recompiled
void fn_sub_541AD8_00541ad8(EEContext&);  // generated body
void fn_sub_541AD8_00541ad8__recomp(EEContext&);  // recompiled
void fn_sub_541B28_00541b28(EEContext&);  // generated body
void fn_sub_541B28_00541b28__recomp(EEContext&);  // recompiled
void fn_sub_541B58_00541b58(EEContext&);  // generated body
void fn_sub_541B58_00541b58__recomp(EEContext&);  // recompiled
void fn_sub_541B70_00541b70(EEContext&);  // generated body
void fn_sub_541B70_00541b70__recomp(EEContext&);  // recompiled
void fn_sub_541B88_00541b88(EEContext&);  // generated body
void fn_sub_541B88_00541b88__recomp(EEContext&);  // recompiled
void fn_sub_541BA0_00541ba0(EEContext&);  // generated body
void fn_sub_541BA0_00541ba0__recomp(EEContext&);  // recompiled
void fn_sub_541BD0_00541bd0(EEContext&);  // generated body
void fn_sub_541BD0_00541bd0__recomp(EEContext&);  // recompiled
void fn___env_lock_7_00541cb8(EEContext&);  // generated body
void fn___env_lock_7_00541cb8__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_0_00541ce8(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_0_00541ce8__recomp(EEContext&);  // recompiled
void fn_sub_54B748_0054b748(EEContext&);  // generated body
void fn_sub_54B748_0054b748__recomp(EEContext&);  // recompiled
void fn_sub_5526B0_005526b0(EEContext&);  // generated body
void fn_sub_5526B0_005526b0__recomp(EEContext&);  // recompiled
void fn_sub_5530D0_005530d0(EEContext&);  // generated body
void fn_sub_5530D0_005530d0__recomp(EEContext&);  // recompiled
void fn_srd_exec_dvd_00558138(EEContext&);  // generated body
void fn_srd_exec_dvd_00558138__recomp(EEContext&);  // recompiled
void fn___errno_4_005584f0(EEContext&);  // generated body
void fn___errno_4_005584f0__recomp(EEContext&);  // recompiled
void fn_dtx_create_rmt_00559588(EEContext&);  // generated body
void fn_dtx_create_rmt_00559588__recomp(EEContext&);  // recompiled
void fn_sub_55A198_0055a198(EEContext&);  // generated body
void fn_sub_55A198_0055a198__recomp(EEContext&);  // recompiled
void fn_dvCiOpen_0055a1f0(EEContext&);  // generated body
void fn_dvCiOpen_0055a1f0__recomp(EEContext&);  // recompiled
void fn_dvCiSeek_0055a3c0(EEContext&);  // generated body
void fn_dvCiSeek_0055a3c0__recomp(EEContext&);  // recompiled
void fn_dvCiReqRd_0055a490(EEContext&);  // generated body
void fn_dvCiReqRd_0055a490__recomp(EEContext&);  // recompiled
void fn_sub_55A758_0055a758(EEContext&);  // generated body
void fn_sub_55A758_0055a758__recomp(EEContext&);  // recompiled
void fn_sub_55A760_0055a760(EEContext&);  // generated body
void fn_sub_55A760_0055a760__recomp(EEContext&);  // recompiled
void fn_sub_55A898_0055a898(EEContext&);  // generated body
void fn_sub_55A898_0055a898__recomp(EEContext&);  // recompiled
void fn_sub_55A8A8_0055a8a8(EEContext&);  // generated body
void fn_sub_55A8A8_0055a8a8__recomp(EEContext&);  // recompiled
void fn_sub_55A8E8_0055a8e8(EEContext&);  // generated body
void fn_sub_55A8E8_0055a8e8__recomp(EEContext&);  // recompiled
void fn_dvci_is_lsn_access_fname_0055b120(EEContext&);  // generated body
void fn_dvci_is_lsn_access_fname_0055b120__recomp(EEContext&);  // recompiled
void fn_sub_564EF8_00564ef8(EEContext&);  // generated body
void fn_sub_564EF8_00564ef8__recomp(EEContext&);  // recompiled
void fn_sub_57D518_0057d518(EEContext&);  // generated body
void fn_sub_57D518_0057d518__recomp(EEContext&);  // recompiled
void fn_sub_57FC60_0057fc60(EEContext&);  // generated body
void fn_sub_57FC60_0057fc60__recomp(EEContext&);  // recompiled
void fn_sub_580F10_00580f10(EEContext&);  // generated body
void fn_sub_580F10_00580f10__recomp(EEContext&);  // recompiled
void fn_sub_580FE8_00580fe8(EEContext&);  // generated body
void fn_sub_580FE8_00580fe8__recomp(EEContext&);  // recompiled
void fn_sub_585590_00585590(EEContext&);  // generated body
void fn_sub_585590_00585590__recomp(EEContext&);  // recompiled
void fn_sub_589BE0_00589be0(EEContext&);  // generated body
void fn_sub_589BE0_00589be0__recomp(EEContext&);  // recompiled
void fn_sub_58A108_0058a108(EEContext&);  // generated body
void fn_sub_58A108_0058a108__recomp(EEContext&);  // recompiled
void fn_sub_5941A8_005941a8(EEContext&);  // generated body
void fn_sub_5941A8_005941a8__recomp(EEContext&);  // recompiled
void fn_sub_594AC0_00594ac0(EEContext&);  // generated body
void fn_sub_594AC0_00594ac0__recomp(EEContext&);  // recompiled
void fn_sub_595988_00595988(EEContext&);  // generated body
void fn_sub_595988_00595988__recomp(EEContext&);  // recompiled
void fn_sub_595BA0_00595ba0(EEContext&);  // generated body
void fn_sub_595BA0_00595ba0__recomp(EEContext&);  // recompiled
void fn_sub_595BE8_00595be8(EEContext&);  // generated body
void fn_sub_595BE8_00595be8__recomp(EEContext&);  // recompiled
void fn_sub_595C60_00595c60(EEContext&);  // generated body
void fn_sub_595C60_00595c60__recomp(EEContext&);  // recompiled
void fn_sub_5972B0_005972b0(EEContext&);  // generated body
void fn_sub_5972B0_005972b0__recomp(EEContext&);  // recompiled
void fn_sub_59BCF0_0059bcf0(EEContext&);  // generated body
void fn_sub_59BCF0_0059bcf0__recomp(EEContext&);  // recompiled
void fn_sub_59BEF0_0059bef0(EEContext&);  // generated body
void fn_sub_59BEF0_0059bef0__recomp(EEContext&);  // recompiled
void fn_sub_59FD10_0059fd10(EEContext&);  // generated body
void fn_sub_59FD10_0059fd10__recomp(EEContext&);  // recompiled
void fn_sub_5A1868_005a1868(EEContext&);  // generated body
void fn_sub_5A1868_005a1868__recomp(EEContext&);  // recompiled
void fn_sub_5A19C0_005a19c0(EEContext&);  // generated body
void fn_sub_5A19C0_005a19c0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_17B860", 0x17B860, &recomp_gen::fn_sub_17B860_0017b860, &recomp_gen::fn_sub_17B860_0017b860__recomp},
    {"sub_1A0D00", 0x1A0D00, &recomp_gen::fn_sub_1A0D00_001a0d00, &recomp_gen::fn_sub_1A0D00_001a0d00__recomp},
    {"sub_1A0D80", 0x1A0D80, &recomp_gen::fn_sub_1A0D80_001a0d80, &recomp_gen::fn_sub_1A0D80_001a0d80__recomp},
    {"sub_1A3AE0", 0x1A3AE0, &recomp_gen::fn_sub_1A3AE0_001a3ae0, &recomp_gen::fn_sub_1A3AE0_001a3ae0__recomp},
    {"sub_1A3BF0", 0x1A3BF0, &recomp_gen::fn_sub_1A3BF0_001a3bf0, &recomp_gen::fn_sub_1A3BF0_001a3bf0__recomp},
    {"sub_1A3DC0", 0x1A3DC0, &recomp_gen::fn_sub_1A3DC0_001a3dc0, &recomp_gen::fn_sub_1A3DC0_001a3dc0__recomp},
    {"sub_1A41B0", 0x1A41B0, &recomp_gen::fn_sub_1A41B0_001a41b0, &recomp_gen::fn_sub_1A41B0_001a41b0__recomp},
    {"sub_1A4510", 0x1A4510, &recomp_gen::fn_sub_1A4510_001a4510, &recomp_gen::fn_sub_1A4510_001a4510__recomp},
    {"sub_1A4CD0", 0x1A4CD0, &recomp_gen::fn_sub_1A4CD0_001a4cd0, &recomp_gen::fn_sub_1A4CD0_001a4cd0__recomp},
    {"sub_1A4DC0", 0x1A4DC0, &recomp_gen::fn_sub_1A4DC0_001a4dc0, &recomp_gen::fn_sub_1A4DC0_001a4dc0__recomp},
    {"sub_1A4E60", 0x1A4E60, &recomp_gen::fn_sub_1A4E60_001a4e60, &recomp_gen::fn_sub_1A4E60_001a4e60__recomp},
    {"sub_20B250", 0x20B250, &recomp_gen::fn_sub_20B250_0020b250, &recomp_gen::fn_sub_20B250_0020b250__recomp},
    {"sub_20C400", 0x20C400, &recomp_gen::fn_sub_20C400_0020c400, &recomp_gen::fn_sub_20C400_0020c400__recomp},
    {"sub_20C500", 0x20C500, &recomp_gen::fn_sub_20C500_0020c500, &recomp_gen::fn_sub_20C500_0020c500__recomp},
    {"sub_21AB80", 0x21AB80, &recomp_gen::fn_sub_21AB80_0021ab80, &recomp_gen::fn_sub_21AB80_0021ab80__recomp},
    {"sub_2B94F0", 0x2B94F0, &recomp_gen::fn_sub_2B94F0_002b94f0, &recomp_gen::fn_sub_2B94F0_002b94f0__recomp},
    {"sub_316E00", 0x316E00, &recomp_gen::fn_sub_316E00_00316e00, &recomp_gen::fn_sub_316E00_00316e00__recomp},
    {"sub_316F70", 0x316F70, &recomp_gen::fn_sub_316F70_00316f70, &recomp_gen::fn_sub_316F70_00316f70__recomp},
    {"sub_324BD0", 0x324BD0, &recomp_gen::fn_sub_324BD0_00324bd0, &recomp_gen::fn_sub_324BD0_00324bd0__recomp},
    {"sub_3252A0", 0x3252A0, &recomp_gen::fn_sub_3252A0_003252a0, &recomp_gen::fn_sub_3252A0_003252a0__recomp},
    {"sub_325920", 0x325920, &recomp_gen::fn_sub_325920_00325920, &recomp_gen::fn_sub_325920_00325920__recomp},
    {"sub_329BA0", 0x329BA0, &recomp_gen::fn_sub_329BA0_00329ba0, &recomp_gen::fn_sub_329BA0_00329ba0__recomp},
    {"sub_32A770", 0x32A770, &recomp_gen::fn_sub_32A770_0032a770, &recomp_gen::fn_sub_32A770_0032a770__recomp},
    {"sub_32A890", 0x32A890, &recomp_gen::fn_sub_32A890_0032a890, &recomp_gen::fn_sub_32A890_0032a890__recomp},
    {"sub_358A30", 0x358A30, &recomp_gen::fn_sub_358A30_00358a30, &recomp_gen::fn_sub_358A30_00358a30__recomp},
    {"sub_359380", 0x359380, &recomp_gen::fn_sub_359380_00359380, &recomp_gen::fn_sub_359380_00359380__recomp},
    {"sub_3A2090", 0x3A2090, &recomp_gen::fn_sub_3A2090_003a2090, &recomp_gen::fn_sub_3A2090_003a2090__recomp},
    {"sub_3B2F90", 0x3B2F90, &recomp_gen::fn_sub_3B2F90_003b2f90, &recomp_gen::fn_sub_3B2F90_003b2f90__recomp},
    {"MT_Scene_Load", 0x3B5760, &recomp_gen::fn_MT_Scene_Load_003b5760, &recomp_gen::fn_MT_Scene_Load_003b5760__recomp},
    {"sub_3B5A10", 0x3B5A10, &recomp_gen::fn_sub_3B5A10_003b5a10, &recomp_gen::fn_sub_3B5A10_003b5a10__recomp},
    {"sub_3B5AB0", 0x3B5AB0, &recomp_gen::fn_sub_3B5AB0_003b5ab0, &recomp_gen::fn_sub_3B5AB0_003b5ab0__recomp},
    {"sub_3B5CF0", 0x3B5CF0, &recomp_gen::fn_sub_3B5CF0_003b5cf0, &recomp_gen::fn_sub_3B5CF0_003b5cf0__recomp},
    {"sub_3B5D00", 0x3B5D00, &recomp_gen::fn_sub_3B5D00_003b5d00, &recomp_gen::fn_sub_3B5D00_003b5d00__recomp},
    {"sub_3B5D10", 0x3B5D10, &recomp_gen::fn_sub_3B5D10_003b5d10, &recomp_gen::fn_sub_3B5D10_003b5d10__recomp},
    {"sub_3B5DF0", 0x3B5DF0, &recomp_gen::fn_sub_3B5DF0_003b5df0, &recomp_gen::fn_sub_3B5DF0_003b5df0__recomp},
    {"sub_3B6000", 0x3B6000, &recomp_gen::fn_sub_3B6000_003b6000, &recomp_gen::fn_sub_3B6000_003b6000__recomp},
    {"sub_3B6030", 0x3B6030, &recomp_gen::fn_sub_3B6030_003b6030, &recomp_gen::fn_sub_3B6030_003b6030__recomp},
    {"sub_3B6270", 0x3B6270, &recomp_gen::fn_sub_3B6270_003b6270, &recomp_gen::fn_sub_3B6270_003b6270__recomp},
    {"sub_3B65D0", 0x3B65D0, &recomp_gen::fn_sub_3B65D0_003b65d0, &recomp_gen::fn_sub_3B65D0_003b65d0__recomp},
    {"sub_3B8B30", 0x3B8B30, &recomp_gen::fn_sub_3B8B30_003b8b30, &recomp_gen::fn_sub_3B8B30_003b8b30__recomp},
    {"sub_3B91C0", 0x3B91C0, &recomp_gen::fn_sub_3B91C0_003b91c0, &recomp_gen::fn_sub_3B91C0_003b91c0__recomp},
    {"sub_3B9320", 0x3B9320, &recomp_gen::fn_sub_3B9320_003b9320, &recomp_gen::fn_sub_3B9320_003b9320__recomp},
    {"sub_3B9550", 0x3B9550, &recomp_gen::fn_sub_3B9550_003b9550, &recomp_gen::fn_sub_3B9550_003b9550__recomp},
    {"sub_3BB010", 0x3BB010, &recomp_gen::fn_sub_3BB010_003bb010, &recomp_gen::fn_sub_3BB010_003bb010__recomp},
    {"sub_3BB1D0", 0x3BB1D0, &recomp_gen::fn_sub_3BB1D0_003bb1d0, &recomp_gen::fn_sub_3BB1D0_003bb1d0__recomp},
    {"sub_3BCC80", 0x3BCC80, &recomp_gen::fn_sub_3BCC80_003bcc80, &recomp_gen::fn_sub_3BCC80_003bcc80__recomp},
    {"sub_3C77A0", 0x3C77A0, &recomp_gen::fn_sub_3C77A0_003c77a0, &recomp_gen::fn_sub_3C77A0_003c77a0__recomp},
    {"sub_3C7B90", 0x3C7B90, &recomp_gen::fn_sub_3C7B90_003c7b90, &recomp_gen::fn_sub_3C7B90_003c7b90__recomp},
    {"sub_3C7BC0", 0x3C7BC0, &recomp_gen::fn_sub_3C7BC0_003c7bc0, &recomp_gen::fn_sub_3C7BC0_003c7bc0__recomp},
    {"sub_3C7C20", 0x3C7C20, &recomp_gen::fn_sub_3C7C20_003c7c20, &recomp_gen::fn_sub_3C7C20_003c7c20__recomp},
    {"sub_3C7D80", 0x3C7D80, &recomp_gen::fn_sub_3C7D80_003c7d80, &recomp_gen::fn_sub_3C7D80_003c7d80__recomp},
    {"sub_3C7E20", 0x3C7E20, &recomp_gen::fn_sub_3C7E20_003c7e20, &recomp_gen::fn_sub_3C7E20_003c7e20__recomp},
    {"sub_3C8F70", 0x3C8F70, &recomp_gen::fn_sub_3C8F70_003c8f70, &recomp_gen::fn_sub_3C8F70_003c8f70__recomp},
    {"sub_3C94E0", 0x3C94E0, &recomp_gen::fn_sub_3C94E0_003c94e0, &recomp_gen::fn_sub_3C94E0_003c94e0__recomp},
    {"sub_3C9790", 0x3C9790, &recomp_gen::fn_sub_3C9790_003c9790, &recomp_gen::fn_sub_3C9790_003c9790__recomp},
    {"fclMisc_CreatePsStatusTasks", 0x3C9850, &recomp_gen::fn_fclMisc_CreatePsStatusTasks_003c9850, &recomp_gen::fn_fclMisc_CreatePsStatusTasks_003c9850__recomp},
    {"sub_3C9AB0", 0x3C9AB0, &recomp_gen::fn_sub_3C9AB0_003c9ab0, &recomp_gen::fn_sub_3C9AB0_003c9ab0__recomp},
    {"sub_3C9D00", 0x3C9D00, &recomp_gen::fn_sub_3C9D00_003c9d00, &recomp_gen::fn_sub_3C9D00_003c9d00__recomp},
    {"sub_464120", 0x464120, &recomp_gen::fn_sub_464120_00464120, &recomp_gen::fn_sub_464120_00464120__recomp},
    {"sub_48EE80", 0x48EE80, &recomp_gen::fn_sub_48EE80_0048ee80, &recomp_gen::fn_sub_48EE80_0048ee80__recomp},
    {"sub_48EED0", 0x48EED0, &recomp_gen::fn_sub_48EED0_0048eed0, &recomp_gen::fn_sub_48EED0_0048eed0__recomp},
    {"sub_4916D0", 0x4916D0, &recomp_gen::fn_sub_4916D0_004916d0, &recomp_gen::fn_sub_4916D0_004916d0__recomp},
    {"sub_491EA0", 0x491EA0, &recomp_gen::fn_sub_491EA0_00491ea0, &recomp_gen::fn_sub_491EA0_00491ea0__recomp},
    {"sub_4932C0", 0x4932C0, &recomp_gen::fn_sub_4932C0_004932c0, &recomp_gen::fn_sub_4932C0_004932c0__recomp},
    {"sub_4AA410", 0x4AA410, &recomp_gen::fn_sub_4AA410_004aa410, &recomp_gen::fn_sub_4AA410_004aa410__recomp},
    {"sub_4AAA60", 0x4AAA60, &recomp_gen::fn_sub_4AAA60_004aaa60, &recomp_gen::fn_sub_4AAA60_004aaa60__recomp},
    {"sub_4B3710", 0x4B3710, &recomp_gen::fn_sub_4B3710_004b3710, &recomp_gen::fn_sub_4B3710_004b3710__recomp},
    {"sub_4B6EB0", 0x4B6EB0, &recomp_gen::fn_sub_4B6EB0_004b6eb0, &recomp_gen::fn_sub_4B6EB0_004b6eb0__recomp},
    {"sub_4C1D50", 0x4C1D50, &recomp_gen::fn_sub_4C1D50_004c1d50, &recomp_gen::fn_sub_4C1D50_004c1d50__recomp},
    {"sub_4C9D70", 0x4C9D70, &recomp_gen::fn_sub_4C9D70_004c9d70, &recomp_gen::fn_sub_4C9D70_004c9d70__recomp},
    {"_sceMpegError", 0x502668, &recomp_gen::fn__sceMpegError_00502668, &recomp_gen::fn__sceMpegError_00502668__recomp},
    {"_sceMpegError1", 0x5026C0, &recomp_gen::fn__sceMpegError1_005026c0, &recomp_gen::fn__sceMpegError1_005026c0__recomp},
    {"_sceRemoveIntcHandler", 0x502E60, &recomp_gen::fn__sceRemoveIntcHandler_00502e60, &recomp_gen::fn__sceRemoveIntcHandler_00502e60__recomp},
    {"_sceExitDeleteThread", 0x502FA0, &recomp_gen::fn__sceExitDeleteThread_00502fa0, &recomp_gen::fn__sceExitDeleteThread_00502fa0__recomp},
    {"sceFsInit", 0x508170, &recomp_gen::fn_sceFsInit_00508170, &recomp_gen::fn_sceFsInit_00508170__recomp},
    {"sceOpen", 0x508670, &recomp_gen::fn_sceOpen_00508670, &recomp_gen::fn_sceOpen_00508670__recomp},
    {"sceClose", 0x508900, &recomp_gen::fn_sceClose_00508900, &recomp_gen::fn_sceClose_00508900__recomp},
    {"sceLseek", 0x508A78, &recomp_gen::fn_sceLseek_00508a78, &recomp_gen::fn_sceLseek_00508a78__recomp},
    {"_sceCallCode", 0x509758, &recomp_gen::fn__sceCallCode_00509758, &recomp_gen::fn__sceCallCode_00509758__recomp},
    {"sub_50E508", 0x50E508, &recomp_gen::fn_sub_50E508_0050e508, &recomp_gen::fn_sub_50E508_0050e508__recomp},
    {"_sceMcCoreReadClock", 0x51B5F0, &recomp_gen::fn__sceMcCoreReadClock_0051b5f0, &recomp_gen::fn__sceMcCoreReadClock_0051b5f0__recomp},
    {"__swrite", 0x523CC0, &recomp_gen::fn___swrite_00523cc0, &recomp_gen::fn___swrite_00523cc0__recomp},
    {"sub_535DD8", 0x535DD8, &recomp_gen::fn_sub_535DD8_00535dd8, &recomp_gen::fn_sub_535DD8_00535dd8__recomp},
    {"sub_535E28", 0x535E28, &recomp_gen::fn_sub_535E28_00535e28, &recomp_gen::fn_sub_535E28_00535e28__recomp},
    {"sub_535FC0", 0x535FC0, &recomp_gen::fn_sub_535FC0_00535fc0, &recomp_gen::fn_sub_535FC0_00535fc0__recomp},
    {"sub_535FF0", 0x535FF0, &recomp_gen::fn_sub_535FF0_00535ff0, &recomp_gen::fn_sub_535FF0_00535ff0__recomp},
    {"sub_536080", 0x536080, &recomp_gen::fn_sub_536080_00536080, &recomp_gen::fn_sub_536080_00536080__recomp},
    {"my_malloc", 0x537790, &recomp_gen::fn_my_malloc_00537790, &recomp_gen::fn_my_malloc_00537790__recomp},
    {"sub_537890", 0x537890, &recomp_gen::fn_sub_537890_00537890, &recomp_gen::fn_sub_537890_00537890__recomp},
    {"sub_537D90", 0x537D90, &recomp_gen::fn_sub_537D90_00537d90, &recomp_gen::fn_sub_537D90_00537d90__recomp},
    {"sub_537F08", 0x537F08, &recomp_gen::fn_sub_537F08_00537f08, &recomp_gen::fn_sub_537F08_00537f08__recomp},
    {"sub_538060", 0x538060, &recomp_gen::fn_sub_538060_00538060, &recomp_gen::fn_sub_538060_00538060__recomp},
    {"sub_5382C0", 0x5382C0, &recomp_gen::fn_sub_5382C0_005382c0, &recomp_gen::fn_sub_5382C0_005382c0__recomp},
    {"sub_5382C8", 0x5382C8, &recomp_gen::fn_sub_5382C8_005382c8, &recomp_gen::fn_sub_5382C8_005382c8__recomp},
    {"sub_538348", 0x538348, &recomp_gen::fn_sub_538348_00538348, &recomp_gen::fn_sub_538348_00538348__recomp},
    {"sub_538360", 0x538360, &recomp_gen::fn_sub_538360_00538360, &recomp_gen::fn_sub_538360_00538360__recomp},
    {"sub_5383A8", 0x5383A8, &recomp_gen::fn_sub_5383A8_005383a8, &recomp_gen::fn_sub_5383A8_005383a8__recomp},
    {"sub_53AE08", 0x53AE08, &recomp_gen::fn_sub_53AE08_0053ae08, &recomp_gen::fn_sub_53AE08_0053ae08__recomp},
    {"sub_53AE60", 0x53AE60, &recomp_gen::fn_sub_53AE60_0053ae60, &recomp_gen::fn_sub_53AE60_0053ae60__recomp},
    {"sub_53EA30", 0x53EA30, &recomp_gen::fn_sub_53EA30_0053ea30, &recomp_gen::fn_sub_53EA30_0053ea30__recomp},
    {"r_lock_def_free", 0x53EA50, &recomp_gen::fn_r_lock_def_free_0053ea50, &recomp_gen::fn_r_lock_def_free_0053ea50__recomp},
    {"r_lock_def_get_free_item", 0x53EA70, &recomp_gen::fn_r_lock_def_get_free_item_0053ea70, &recomp_gen::fn_r_lock_def_get_free_item_0053ea70__recomp},
    {"sub_5419F8", 0x5419F8, &recomp_gen::fn_sub_5419F8_005419f8, &recomp_gen::fn_sub_5419F8_005419f8__recomp},
    {"sub_541A10", 0x541A10, &recomp_gen::fn_sub_541A10_00541a10, &recomp_gen::fn_sub_541A10_00541a10__recomp},
    {"sub_541AD8", 0x541AD8, &recomp_gen::fn_sub_541AD8_00541ad8, &recomp_gen::fn_sub_541AD8_00541ad8__recomp},
    {"sub_541B28", 0x541B28, &recomp_gen::fn_sub_541B28_00541b28, &recomp_gen::fn_sub_541B28_00541b28__recomp},
    {"sub_541B58", 0x541B58, &recomp_gen::fn_sub_541B58_00541b58, &recomp_gen::fn_sub_541B58_00541b58__recomp},
    {"sub_541B70", 0x541B70, &recomp_gen::fn_sub_541B70_00541b70, &recomp_gen::fn_sub_541B70_00541b70__recomp},
    {"sub_541B88", 0x541B88, &recomp_gen::fn_sub_541B88_00541b88, &recomp_gen::fn_sub_541B88_00541b88__recomp},
    {"sub_541BA0", 0x541BA0, &recomp_gen::fn_sub_541BA0_00541ba0, &recomp_gen::fn_sub_541BA0_00541ba0__recomp},
    {"sub_541BD0", 0x541BD0, &recomp_gen::fn_sub_541BD0_00541bd0, &recomp_gen::fn_sub_541BD0_00541bd0__recomp},
    {"__env_lock_7", 0x541CB8, &recomp_gen::fn___env_lock_7_00541cb8, &recomp_gen::fn___env_lock_7_00541cb8__recomp},
    {"r_lock_def_get_free_item_0", 0x541CE8, &recomp_gen::fn_r_lock_def_get_free_item_0_00541ce8, &recomp_gen::fn_r_lock_def_get_free_item_0_00541ce8__recomp},
    {"sub_54B748", 0x54B748, &recomp_gen::fn_sub_54B748_0054b748, &recomp_gen::fn_sub_54B748_0054b748__recomp},
    {"sub_5526B0", 0x5526B0, &recomp_gen::fn_sub_5526B0_005526b0, &recomp_gen::fn_sub_5526B0_005526b0__recomp},
    {"sub_5530D0", 0x5530D0, &recomp_gen::fn_sub_5530D0_005530d0, &recomp_gen::fn_sub_5530D0_005530d0__recomp},
    {"srd_exec_dvd", 0x558138, &recomp_gen::fn_srd_exec_dvd_00558138, &recomp_gen::fn_srd_exec_dvd_00558138__recomp},
    {"__errno_4", 0x5584F0, &recomp_gen::fn___errno_4_005584f0, &recomp_gen::fn___errno_4_005584f0__recomp},
    {"dtx_create_rmt", 0x559588, &recomp_gen::fn_dtx_create_rmt_00559588, &recomp_gen::fn_dtx_create_rmt_00559588__recomp},
    {"sub_55A198", 0x55A198, &recomp_gen::fn_sub_55A198_0055a198, &recomp_gen::fn_sub_55A198_0055a198__recomp},
    {"dvCiOpen", 0x55A1F0, &recomp_gen::fn_dvCiOpen_0055a1f0, &recomp_gen::fn_dvCiOpen_0055a1f0__recomp},
    {"dvCiSeek", 0x55A3C0, &recomp_gen::fn_dvCiSeek_0055a3c0, &recomp_gen::fn_dvCiSeek_0055a3c0__recomp},
    {"dvCiReqRd", 0x55A490, &recomp_gen::fn_dvCiReqRd_0055a490, &recomp_gen::fn_dvCiReqRd_0055a490__recomp},
    {"sub_55A758", 0x55A758, &recomp_gen::fn_sub_55A758_0055a758, &recomp_gen::fn_sub_55A758_0055a758__recomp},
    {"sub_55A760", 0x55A760, &recomp_gen::fn_sub_55A760_0055a760, &recomp_gen::fn_sub_55A760_0055a760__recomp},
    {"sub_55A898", 0x55A898, &recomp_gen::fn_sub_55A898_0055a898, &recomp_gen::fn_sub_55A898_0055a898__recomp},
    {"sub_55A8A8", 0x55A8A8, &recomp_gen::fn_sub_55A8A8_0055a8a8, &recomp_gen::fn_sub_55A8A8_0055a8a8__recomp},
    {"sub_55A8E8", 0x55A8E8, &recomp_gen::fn_sub_55A8E8_0055a8e8, &recomp_gen::fn_sub_55A8E8_0055a8e8__recomp},
    {"dvci_is_lsn_access_fname", 0x55B120, &recomp_gen::fn_dvci_is_lsn_access_fname_0055b120, &recomp_gen::fn_dvci_is_lsn_access_fname_0055b120__recomp},
    {"sub_564EF8", 0x564EF8, &recomp_gen::fn_sub_564EF8_00564ef8, &recomp_gen::fn_sub_564EF8_00564ef8__recomp},
    {"sub_57D518", 0x57D518, &recomp_gen::fn_sub_57D518_0057d518, &recomp_gen::fn_sub_57D518_0057d518__recomp},
    {"sub_57FC60", 0x57FC60, &recomp_gen::fn_sub_57FC60_0057fc60, &recomp_gen::fn_sub_57FC60_0057fc60__recomp},
    {"sub_580F10", 0x580F10, &recomp_gen::fn_sub_580F10_00580f10, &recomp_gen::fn_sub_580F10_00580f10__recomp},
    {"sub_580FE8", 0x580FE8, &recomp_gen::fn_sub_580FE8_00580fe8, &recomp_gen::fn_sub_580FE8_00580fe8__recomp},
    {"sub_585590", 0x585590, &recomp_gen::fn_sub_585590_00585590, &recomp_gen::fn_sub_585590_00585590__recomp},
    {"sub_589BE0", 0x589BE0, &recomp_gen::fn_sub_589BE0_00589be0, &recomp_gen::fn_sub_589BE0_00589be0__recomp},
    {"sub_58A108", 0x58A108, &recomp_gen::fn_sub_58A108_0058a108, &recomp_gen::fn_sub_58A108_0058a108__recomp},
    {"sub_5941A8", 0x5941A8, &recomp_gen::fn_sub_5941A8_005941a8, &recomp_gen::fn_sub_5941A8_005941a8__recomp},
    {"sub_594AC0", 0x594AC0, &recomp_gen::fn_sub_594AC0_00594ac0, &recomp_gen::fn_sub_594AC0_00594ac0__recomp},
    {"sub_595988", 0x595988, &recomp_gen::fn_sub_595988_00595988, &recomp_gen::fn_sub_595988_00595988__recomp},
    {"sub_595BA0", 0x595BA0, &recomp_gen::fn_sub_595BA0_00595ba0, &recomp_gen::fn_sub_595BA0_00595ba0__recomp},
    {"sub_595BE8", 0x595BE8, &recomp_gen::fn_sub_595BE8_00595be8, &recomp_gen::fn_sub_595BE8_00595be8__recomp},
    {"sub_595C60", 0x595C60, &recomp_gen::fn_sub_595C60_00595c60, &recomp_gen::fn_sub_595C60_00595c60__recomp},
    {"sub_5972B0", 0x5972B0, &recomp_gen::fn_sub_5972B0_005972b0, &recomp_gen::fn_sub_5972B0_005972b0__recomp},
    {"sub_59BCF0", 0x59BCF0, &recomp_gen::fn_sub_59BCF0_0059bcf0, &recomp_gen::fn_sub_59BCF0_0059bcf0__recomp},
    {"sub_59BEF0", 0x59BEF0, &recomp_gen::fn_sub_59BEF0_0059bef0, &recomp_gen::fn_sub_59BEF0_0059bef0__recomp},
    {"sub_59FD10", 0x59FD10, &recomp_gen::fn_sub_59FD10_0059fd10, &recomp_gen::fn_sub_59FD10_0059fd10__recomp},
    {"sub_5A1868", 0x5A1868, &recomp_gen::fn_sub_5A1868_005a1868, &recomp_gen::fn_sub_5A1868_005a1868__recomp},
    {"sub_5A19C0", 0x5A19C0, &recomp_gen::fn_sub_5A19C0_005a19c0, &recomp_gen::fn_sub_5A19C0_005a19c0__recomp},
};

// The argument kinds of each case (a0..a3, then $t0 / $t1); a function not listed takes small ids. B a cleared 12 KiB
// block (pointers to a cleared sub-block at +4 / +8 / +60 / +64 / +80 / +96 / +144 / +180 / +192, a count 1..3 at +84),
// T a task whose work (+60) holds a 4-node list (+60 head, next at +552, index +44 / +48, count +56), C a 4-row command
// table (32-byte rows: id, op 1..4, arguments, a flag), V a float vector, M a model handle (+4 kind 0..2, RGBA at +64),
// P an array owner (+84 u16 count, +88 the null entries), U a field-unit record (+212 / +214 ids, +216 load flags), K a
// clump (+8 a two-atomic ring, +16 an empty ring, +32 / +36 three entries), F the callback 0x4B3710 (returns $a1), O
// zero, Q a file name, L an LSN-style or plain name, D a dvCi handle, q a dvCi status query, x a DMA size (16-byte
// units), w a seek whence, n 0..7, z 0 / 1, h an s32 -40..40, k a g_data.c kind (415, 425, other), p a party slot
// 1..10, - no argument (small).
const std::map<std::string, const char*> kKinds = {
    {"sub_17B860", "ppkn"}, {"sub_1A3AE0", "Tnn"},  {"sub_1A3BF0", "Tn"},   {"sub_1A3DC0", "TCn"},  {"sub_1A4510", "T"},
    {"sub_1A4CD0", "T"},    {"sub_1A4DC0", "TB"},   {"sub_1A4E60", "TV"},   {"sub_20B250", "M"},    {"sub_20C400", "VV"},
    {"sub_2B94F0", "P"},    {"sub_316E00", "nnz"},  {"sub_316F70", "U"},    {"sub_324BD0", "BBn"},  {"sub_3252A0", "Bn"},
    {"sub_325920", "BBn"},  {"sub_329BA0", "BB"},   {"sub_32A770", "BBnB"}, {"sub_32A890", "BBn"},  {"sub_358A30", "BBn"},
    {"sub_359380", "BBn"},  {"sub_3A2090", "Tnnn"}, {"sub_3B2F90", "BBnn"}, {"sub_3B8B30", "nVnn"}, {"sub_3BB1D0", "nnnnn"},
    {"fclMisc_CreatePsStatusTasks", "Tn"},          {"sub_3C9AB0", "T"},    {"sub_3C9D00", "Tn"},   {"sub_464120", "BBnn"},
    {"sub_48EE80", "B"},    {"sub_48EED0", "Bn"},   {"sub_4916D0", "KFz"},  {"sub_491EA0", "K"},    {"sub_4932C0", "KFz"},
    {"sub_4AA410", "B"},    {"sub_4B6EB0", "O"},    {"sub_4C9D70", "B"},    {"_sceMpegError", "BQ"},
    {"_sceMpegError1", "BQn"}, {"sceOpen", "Qn"},   {"_sceCallCode", "Qn"}, {"__swrite", "BQn"},    {"sub_535DD8", "B"},
    {"sub_535E28", "B"},    {"sub_535FC0", "B"},    {"sub_535FF0", "Bn"},   {"sub_536080", "B"},    {"sub_537890", "B"},
    {"sub_537D90", "B"},    {"sub_537F08", "Bnn"},  {"sub_538060", "B"},    {"sub_5382C0", "B"},    {"sub_5382C8", "B"},
    {"sub_538348", "B"},    {"sub_538360", "B"},    {"sub_5383A8", "B"},    {"sub_53AE08", "Q"},    {"sub_53AE60", "QQ"},
    {"sub_541A10", "B"},    {"sub_541B58", "Bn"},   {"sub_541B88", "Bh"},   {"sub_541BA0", "Bnh"},  {"sub_54B748", "BBnn"},
    {"sub_5530D0", "B"},    {"srd_exec_dvd", "B"},  {"dvCiOpen", "Qn"},     {"dvCiSeek", "Dhw"},    {"dvCiReqRd", "DnB"},
    {"sub_55A760", "D"},    {"sub_55A898", "D"},    {"sub_55A8A8", "D"},    {"sub_55A8E8", "Dq"},   {"dvci_is_lsn_access_fname", "L"},
    {"sub_57D518", "B"},    {"sub_580F10", "nxB"},  {"sub_580FE8", "Bxn"},  {"sub_585590", "Q"},    {"sub_589BE0", "Bn"},
    {"sub_58A108", "Bnn"},  {"sub_5941A8", "B"},    {"sub_594AC0", "B"},    {"sub_595988", "B"},    {"sub_595C60", "B"},
    {"sub_5972B0", "B"},    {"sub_59BCF0", "B"},    {"sub_59BEF0", "B"},
};

constexpr u32 kStrings = kScratch + 0x30000u;  // the file names (above the 12 blocks)

// Callees a body busy-waits on (it retries until they report success): stood in with that result on the snapshots,
// so the pair ends (a recorder returning 0 would keep both runs looping).
const std::map<std::string, std::vector<std::pair<u32, u64>>> kWaits = {
    {"_sceMcCoreReadClock", {{0x51D308u, 1}}},  // sceDbcSendData3: 1 = sent
};

// One argument of kind `k` (writes the world it needs); blocks come from kScratch upwards, 16 KiB apart.
u64 arg_of(Machine& m, char k, std::mt19937& rng, u32& blk) {
    auto block = [&](u32 clear) {
        const u32 b = kScratch + 0x4000u * blk++;
        std::memset(m.at(b), 0, clear);
        return b;
    };
    switch (k) {
    case 'B': {
        const u32 b = block(0x3000);
        for (u32 off : {4u, 8u, 60u, 64u, 80u, 96u, 144u, 180u, 192u}) w32(m, b + off, b + 0x1000);
        w32(m, b + 84, 1 + rng() % 3);
        return b;
    }
    case 'T': {
        const u32 b = block(0x1800);
        const u32 work = b + 0x400;
        w32(m, b + 60, work);
        w32(m, work + 44, rng() % 2);
        w32(m, work + 48, rng() % 2);
        w32(m, work + 56, 1 + rng() % 4);
        w32(m, work + 40, rng() % 2);
        for (u32 i = 0; i < 4; ++i) {
            const u32 node = b + 0x800 + 0x300 * i;
            w32(m, node, 100 + i);
            w32(m, node + 552, i < 3 ? node + 0x300 : 0);
        }
        w32(m, work + 60, b + 0x800);
        return b;
    }
    case 'C': {
        const u32 b = block(0x100);
        for (u32 r = 0; r < 4; ++r) {
            const u32 row = b + 32 * r;
            w32(m, row, rng() % 4);
            w32(m, row + 4, 1 + rng() % 4);
            for (u32 i = 2; i < 7; ++i) w32(m, row + 4 * i, rng() % 8);
            w32(m, row + 28, rng() % 2);
        }
        return b;
    }
    case 'V': {
        const u32 b = block(0x40);
        for (u32 i = 0; i < 4; ++i) wf32(m, b + 4 * i, static_cast<f32>(static_cast<int>(rng() % 401) - 200));
        return b;
    }
    case 'M': {
        const u32 b = block(0x2000);
        w32(m, b, rng() % 8);
        w32(m, b + 4, rng() % 3);
        for (u32 i = 0; i < 4; ++i) w8(m, b + 64 + i, static_cast<u8>(rng()));
        return b;
    }
    case 'P': {
        const u32 b = block(0x800);
        w16(m, b + 84, static_cast<u16>(rng() % 3));
        w32(m, b + 88, b + 0x400);
        return b;
    }
    case 'U': {
        const u32 b = block(0x800);
        static const u32 flags[] = {0, 0x1000, 0x2000, 0x3000};
        w16(m, b + 212, static_cast<u16>(rng() % 4));
        w16(m, b + 214, static_cast<u16>(rng() % 4));
        w16(m, b + 216, static_cast<u16>(flags[rng() % 4]));
        return b;
    }
    case 'K': {
        const u32 b = block(0x1000);
        const u32 l1 = b + 0x440, l2 = b + 0x840;
        w32(m, b + 8, l1);
        w32(m, l1, l2);
        w32(m, l2, b + 8);
        w32(m, b + 16, b + 16);
        w32(m, b + 32, b + 0x100);
        for (u32 i = 0; i < 3; ++i) w32(m, b + 0x100 + 4 * i, b + 0x200 + 0x40 * i);
        w32(m, b + 36, 3);
        return b;
    }
    case 'F': return 0x4B3710u;
    case 'O': return 0;
    case 'Q':
    case 'L': {
        const u32 s = kStrings + 0x100u * blk++;
        static const char* names[] = {"data/test.bin", "0000ABCD.00001234", "\\DATA.CVM;1", "init.bin"};
        wstr(m, s, k == 'L' ? names[1 + (rng() % 2) * 2] : names[rng() % 4]);
        return s;
    }
    case 'D': {
        const u32 b = block(0x80);
        w8(m, b, 1);
        w8(m, b + 2, static_cast<u8>(rng() % 2));
        w32(m, b + 8, 1 + rng() % 100);
        w32(m, b + 12, rng() % 50);
        w32(m, b + 20, 1 + rng() % 100);
        return b;
    }
    case 'q': {
        static const u32 q[] = {200, 201, 202, 203, 204, 205, 299, 7};
        return q[rng() % 8];
    }
    case 'x': return 16 * (1 + rng() % 16);
    case 'w': return rng() % 3;
    case 'z': return rng() % 2;
    case 'h': return static_cast<u64>(static_cast<s64>(static_cast<int>(rng() % 81) - 40));
    case 'k': {
        const u32 r = rng() % 3;
        return r == 0 ? 415u : r == 1 ? 425u : rng() % 500;
    }
    case 'p': return 1 + rng() % 10;
    default: return rng() % 8;
    }
}

constexpr u32 kSceneSlot = 0x7CD540u;  // -> MT_Scene's record (field4.h gpv::kSceneRecord)

}  // namespace

TEST_CASE("game(sweep5c): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 64);
}

// Every body on the packet's snapshots: arguments of its kind (above), the snapshot restored between pairs. The pairs run
// on the stand-ins (every callee this build does not emit recorded); a pair whose original faults is run again as a
// plain pair, which compares the two stops.
TEST_CASE("game(sweep5c): every body on the replay snapshots with real structures") {
    struct Snap {
        const char* dir;
        u32 reps;
    };
    const Snap snaps[] = {{"b_5800", 3}, {"dorm_replay_4900", 2}, {"climb_ref_17000", 2}, {"fusion_ref_6300", 1}, {"shop_ref_4100", 1}};
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    int pairs = 0, stood = 0, stops = 0, used = 0;
    std::map<std::string, int> stop_of;
    for (const Snap& sn : snaps) {
        std::vector<u8> base;
        auto mp = real_machine(sn.dir, base);
        if (!mp) {
            MESSAGE("SKIP: no ELF or snapshot " << std::string(sn.dir));
            continue;
        }
        Machine& m = *mp;
        write_rw_slots(m);
        base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        ++used;
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            const auto it = kKinds.find(c.name);
            const char* kinds = it == kKinds.end() ? "" : it->second;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                const std::mt19937 rng0{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                u64 a[6] = {};
                auto draw = [&](Machine& mm) {
                    std::mt19937 rng = rng0;
                    u32 blk = 0;
                    for (u64& x : a) x = rng() % 8;
                    for (std::size_t i = 0; i < 6 && kinds[i]; ++i) a[i] = arg_of(mm, kinds[i], rng, blk);
                    return rng();
                };
                const u32 seed = draw(m);
                ++pairs;
                const auto wt = kWaits.find(c.name);
                try {
                    if (wt != kWaits.end()) {
                        const auto waits = wt->second;
                        s2t::run_case_w(m, base, kCases, c.name, Args{a[0], a[1], a[2], a[3]}, seed, [&](Machine& mm) { draw(mm); },
                                        [waits](StandInWorld& w) {
                                            for (const auto& [va, v0] : waits) w.si.install_recorder(va, "wait", v0);
                                        });
                    } else {
                        run_case(m, base, kCases, c.name, Args{a[0], a[1], a[2], a[3]}, seed, [&](Machine& mm) { draw(mm); }, 0,
                                 {{GPR_T0, a[4]}, {GPR_T1, a[5]}});
                    }
                    ++stood;
                } catch (const rt_test::FatalEvent&) {
                    reset(m, base);
                    draw(m);
                    HwCheck h = hw;
                    h.gpr_in[GPR_T0] = a[4];
                    h.gpr_in[GPR_T1] = a[5];
                    const hgp::Run r = hgp::pair(m, c.hand, c.recomp, Args{a[0], a[1], a[2], a[3]}, seed, c.name, h);
                    if (r.stopped) {
                        ++stops;
                        ++stop_of[std::string(c.name) + " (" + r.what.substr(0, 40) + " at " + hex64(r.stop_pc) + ")"];
                    }
                }
                reset(m, base);
            }
        }
    }
    std::string why;
    for (const auto& [k, n] : stop_of) why += " " + k + " x" + std::to_string(n) + ";";
    MESSAGE("snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stood << " on the stand-ins, " << stops
                          << " ended at a compared fault stop:" << why.substr(0, 1500));
}

// The scene-record accessors on a field snapshot: sub_3B5CF0 returns the record pointer *(0x7CD540), sub_3B5D00 its
// resource manager (+8), sub_3B5D10 0 once the manager is cleared, and MT_Scene_Load's cache hit (the same major / minor,
// the major outside 20..28) clears +12, sets its bit 0 and prints once without reloading (+0 / +4 kept).
TEST_CASE("game(sweep5c): the scene-record accessors and MT_Scene_Load's cache hit") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot dorm_replay_4900");
        return;
    }
    Machine& m = *mp;
    const u32 rec = r32(m, kSceneSlot);
    REQUIRE(rec == kSceneRecord);
    SiPair sp = run_case(m, base, kCases, "sub_3B5CF0", {}, 901);
    CHECK(static_cast<u32>(v0_of(sp.hw)) == rec);
    sp = run_case(m, base, kCases, "sub_3B5D00", {}, 902);
    CHECK(static_cast<u32>(v0_of(sp.hw)) == r32(m, rec + 8));
    sp = run_case(m, base, kCases, "sub_3B5D10", {}, 903, [rec](Machine& mm) { w32(mm, rec + 8, 0); });
    CHECK(v0_of(sp.hw) == 0);
    for (const u32 type : {0u, 1u, 5u, 21u}) {
        sp = run_case(m, base, kCases, "sub_3B5DF0", {type, 0, 0, 0}, 910 + type, [rec](Machine& mm) { w32(mm, rec + 8, 0); });
        CHECK(v0_of(sp.hw) == 0);  // no resource manager: 0 for every type
    }
    auto hit = [rec](Machine& mm) {
        w32(mm, rec, 5);
        w32(mm, rec + 4, 7);
        w32(mm, rec + 12, 0x40);
    };
    sp = run_case(m, base, kCases, "MT_Scene_Load", {5, 7, 0, 0}, 920, hit);
    CHECK(r32(m, rec + 12) == 1u);  // cleared first, then bit 0
    CHECK(r32(m, rec) == 5u);
    CHECK(r32(m, rec + 4) == 7u);
    CHECK(calls(sp, 0x5225A8u).size() == 1u);
}

// The dvCi handle queries on a built handle (+2 = 1 open, +8 the size in sectors, +12 the position, +20 the sectors):
// the size in bytes (sectors << 11), the status dispatch (200 >> 21, 201 << 11, 299 = 1, others 0, a null handle 0),
// the seek (set / current / from the end, clamped to 0..size, +20 cleared) and the 2048-byte sector size.
TEST_CASE("game(sweep5c): the dvCi size, status and seek rules") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 h = kScratch;
    auto handle = [h](Machine& mm) {
        std::memset(mm.at(h), 0, 0x80);
        w8(mm, h, 1);
        w8(mm, h + 2, 1);
        w32(mm, h + 8, 40);
        w32(mm, h + 12, 10);
        w32(mm, h + 20, 40);
    };
    SiPair sp = run_case(m, base, kCases, "sub_55A760", {h, 0, 0, 0}, 930, handle);
    CHECK(v0_of(sp.hw) == 40 * 2048);
    sp = run_case(m, base, kCases, "sub_55A758", {}, 931);
    CHECK(v0_of(sp.hw) == 2048);
    const std::pair<u32, s64> queries[] = {{200, 0}, {201, 40 * 2048}, {299, 1}, {7, 0}, {300, 0}};
    for (const auto& [q, want] : queries) {
        sp = run_case(m, base, kCases, "sub_55A8E8", {h, q, 0, 0}, 932 + q, handle);
        INFO("query " << q);
        CHECK(v0_of(sp.hw) == want);
    }
    sp = run_case(m, base, kCases, "sub_55A8E8", {0, 201, 0, 0}, 940, handle);
    CHECK(v0_of(sp.hw) == 0);
    struct Seek {
        s32 off;
        u32 whence;
        s32 want;
    };
    const Seek seeks[] = {{5, 0, 5}, {5, 1, 15}, {100, 1, 40}, {-3, 2, 37}, {-100, 0, 0}};
    u32 seed = 950;
    for (const Seek& s : seeks) {
        sp = run_case(m, base, kCases, "dvCiSeek", {h, static_cast<u64>(static_cast<s64>(s.off)), s.whence, 0}, ++seed, handle);
        INFO("seek " << s.off << " whence " << s.whence);
        CHECK(v0_of(sp.hw) == s.want);
        CHECK(static_cast<s32>(r32(m, h + 12)) == s.want);
        CHECK(r32(m, h + 20) == 0u);
    }
}

// dvci_is_lsn_access_fname: true only for a 17-character name with '.' at index 8 ("XXXXXXXX.YYYYYYYY").
TEST_CASE("game(sweep5c): the LSN-access name test") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const std::pair<const char*, s64> names[] = {
        {"0000ABCD.00001234", 1}, {"0000ABCD_00001234", 0}, {"0000ABCD.0000123", 0}, {"data/test.bin", 0}};
    u32 seed = 960;
    for (const auto& [name, want] : names) {
        const std::string s = name;
        const SiPair sp = run_case(m, base, kCases, "dvci_is_lsn_access_fname", {kStrings, 0, 0, 0}, ++seed,
                                   [s](Machine& mm) { wstr(mm, kStrings, s); });
        INFO(s);
        CHECK(v0_of(sp.hw) == want);
    }
}

// The PS2RNA volume / pan setters: the volume is clamped to -999..0 (+56), the pan of channel a1 to -15..15
// (+64 + 4 * a1); while the lock is held (0x7A93F8 == 1 with 0x7A93F0 <= 0) nothing is stored.
TEST_CASE("game(sweep5c): the PS2RNA volume and pan clamps") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 h = kScratch;
    auto unlocked = [h](Machine& mm) {
        std::memset(mm.at(h), 0xAB, 0x100);
        w32(mm, 0x7A93F8u, 0);
    };
    auto locked = [h](Machine& mm) {
        std::memset(mm.at(h), 0xAB, 0x100);
        w32(mm, 0x7A93F8u, 1);
        w32(mm, 0x7A93F0u, 0);
    };
    const std::pair<s32, s32> vols[] = {{5, 0}, {-500, -500}, {-5000, -999}};
    u32 seed = 970;
    for (const auto& [in, want] : vols) {
        run_case(m, base, kCases, "sub_541B88", {h, static_cast<u64>(static_cast<s64>(in)), 0, 0}, ++seed, unlocked);
        INFO("volume " << in);
        CHECK(static_cast<s32>(r32(m, h + 56)) == want);
    }
    run_case(m, base, kCases, "sub_541B88", {h, static_cast<u64>(static_cast<s64>(-20)), 0, 0}, ++seed, locked);
    CHECK(r32(m, h + 56) == 0xABABABABu);
    struct Pan {
        u32 ch;
        s32 in, want;
    };
    const Pan pans[] = {{0, 3, 3}, {1, 20, 15}, {2, -20, -15}};
    for (const Pan& p : pans) {
        run_case(m, base, kCases, "sub_541BA0", {h, p.ch, static_cast<u64>(static_cast<s64>(p.in)), 0}, ++seed, unlocked);
        INFO("pan " << p.in << " channel " << p.ch);
        CHECK(static_cast<s32>(r32(m, h + 64 + 4 * p.ch)) == p.want);
    }
    run_case(m, base, kCases, "sub_541BA0", {h, 0, 3, 0}, ++seed, locked);
    CHECK(r32(m, h + 64) == 0xABABABABu);
}

// sub_58A108's 32-entry ring (a0 + 3884; write index +3876, read index +3880): a value is queued at write & 31 with
// +3868 = a2 and the write index advanced (v0 = 1) while fewer than 32 are pending; a full ring is left alone (v0 = 0).
TEST_CASE("game(sweep5c): the 32-entry ring queue of sub_58A108") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 q = kScratch;
    auto ring = [q](u32 wr, u32 rd) {
        return [q, wr, rd](Machine& mm) {
            std::memset(mm.at(q), 0, 0x1000);
            w32(mm, q + 3876, wr);
            w32(mm, q + 3880, rd);
        };
    };
    SiPair sp = run_case(m, base, kCases, "sub_58A108", {q, 0x111, 0x222, 0}, 980, ring(0, 0));
    CHECK(v0_of(sp.hw) == 1);
    CHECK(r32(m, q + 3884) == 0x111u);
    CHECK(r32(m, q + 3876) == 1u);
    CHECK(r32(m, q + 3868) == 0x222u);
    sp = run_case(m, base, kCases, "sub_58A108", {q, 0x333, 0x444, 0}, 981, ring(33, 2));
    CHECK(v0_of(sp.hw) == 1);
    CHECK(r32(m, q + 3884 + 4) == 0x333u);
    CHECK(r32(m, q + 3876) == 34u);
    sp = run_case(m, base, kCases, "sub_58A108", {q, 0x555, 0x666, 0}, 982, ring(40, 8));
    CHECK(v0_of(sp.hw) == 0);
    CHECK(r32(m, q + 3876) == 40u);
    CHECK(r32(m, q + 3868) == 0u);
}

// sub_1A4510 walks the task work's list (+60 head, next at +552) to index +44 + +48 and returns that node's first word,
// or -1 when the index is not below the count at +56.
TEST_CASE("game(sweep5c): the work-list walk of sub_1A4510") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 t = kScratch, work = t + 0x400;
    auto task = [t, work](u32 i0, u32 i1, u32 count) {
        return [t, work, i0, i1, count](Machine& mm) {
            std::memset(mm.at(t), 0, 0x1800);
            w32(mm, t + 60, work);
            w32(mm, work + 44, i0);
            w32(mm, work + 48, i1);
            w32(mm, work + 56, count);
            for (u32 i = 0; i < 4; ++i) {
                const u32 node = t + 0x800 + 0x300 * i;
                w32(mm, node, 100 + i);
                w32(mm, node + 552, i < 3 ? node + 0x300 : 0);
            }
            w32(mm, work + 60, t + 0x800);
        };
    };
    SiPair sp = run_case(m, base, kCases, "sub_1A4510", {t, 0, 0, 0}, 990, task(1, 1, 4));
    CHECK(v0_of(sp.hw) == 102);
    sp = run_case(m, base, kCases, "sub_1A4510", {t, 0, 0, 0}, 991, task(0, 3, 4));
    CHECK(v0_of(sp.hw) == 103);
    sp = run_case(m, base, kCases, "sub_1A4510", {t, 0, 0, 0}, 992, task(1, 1, 2));
    CHECK(v0_of(sp.hw) == -1);
}

// The clump iterators call the callback (stood in here) with each atomic (link - 64) of the +8 ring / each of the +36
// entries at +32, with a2 as the second argument, until it returns 0; both return the clump.
TEST_CASE("game(sweep5c): the clump iterators") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 k = kScratch, l1 = k + 0x440, l2 = k + 0x840;
    auto clump = [=](Machine& mm) {
        std::memset(mm.at(k), 0, 0x1000);
        w32(mm, k + 8, l1);
        w32(mm, l1, l2);
        w32(mm, l2, k + 8);
        w32(mm, k + 32, k + 0x100);
        for (u32 i = 0; i < 3; ++i) w32(mm, k + 0x100 + 4 * i, k + 0x200 + 0x40 * i);
        w32(mm, k + 36, 3);
    };
    constexpr u32 kCb = 0x4B3710u;
    for (const u64 ret : {1u, 0u}) {
        auto world = [ret](StandInWorld& w) { w.si.install_recorder(kCb, "callback", ret); };
        INFO("callback returns " << ret);
        SiPair sp = s2t::run_case_w(m, base, kCases, "sub_4916D0", {k, kCb, 77, 0}, 1000 + static_cast<u32>(ret), clump, world);
        CHECK(static_cast<u32>(v0_of(sp.hw)) == k);
        auto c = calls(sp, kCb);
        REQUIRE(c.size() == (ret ? 2u : 1u));
        CHECK(c[0].args[0] == l1 - 64);
        CHECK(c[0].args[1] == 77u);
        if (ret) CHECK(c[1].args[0] == l2 - 64);
        sp = s2t::run_case_w(m, base, kCases, "sub_4932C0", {k, kCb, 88, 0}, 1010 + static_cast<u32>(ret), clump, world);
        CHECK(static_cast<u32>(v0_of(sp.hw)) == k);
        c = calls(sp, kCb);
        REQUIRE(c.size() == (ret ? 3u : 1u));
        for (u32 i = 0; i < c.size(); ++i) {
            CHECK(c[i].args[0] == k + 0x200 + 0x40 * i);
            CHECK(c[i].args[1] == 88u);
        }
    }
}

#else

TEST_CASE("game(sweep5c): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
