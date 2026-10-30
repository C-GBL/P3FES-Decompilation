// Pair tests for slice script3 (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log.
// On top of that generic sweep, the meaningful pairs: the script task layer on the real field.bf inside the dorm
// snapshot's running-script list (scrStartScript's rejections and records, scrCreateTaskFromScriptMemory / FromHeader,
// COMM dispatch through CodeFunc_Comm: PUT / PUTSTR / SYNC / SCR_RUN / SCR_KILL, release, the field's sweep), the
// mt_evtMessage slot state machine, koma_Manager on the snapshot, an evtPMFileReader process loading E010_001 through
// the file stand-in, the event player's cut-table getters / draw requests / lerp, the effect registry, the PM paths and
// the small rules -- each with host checks of the documented behaviour (game/include/p3fes/game/script3.h). The callees
// the test build does not emit are stood in (stand_ins.h): no _callees entries were added.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/script3.h"

#include <bit>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
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
namespace s3 = p3fes::game::script3;

namespace p3fes::recomp_gen {
void fn_sub_35AC50_0035ac50(EEContext&);  // generated body
void fn_sub_35AC50_0035ac50__recomp(EEContext&);  // recompiled
void fn_nullsub_21_0035ac80(EEContext&);  // generated body
void fn_nullsub_21_0035ac80__recomp(EEContext&);  // recompiled
void fn_sub_35AD80_0035ad80(EEContext&);  // generated body
void fn_sub_35AD80_0035ad80__recomp(EEContext&);  // recompiled
void fn_sub_35ADB0_0035adb0(EEContext&);  // generated body
void fn_sub_35ADB0_0035adb0__recomp(EEContext&);  // recompiled
void fn_nullsub_22_0035ae50(EEContext&);  // generated body
void fn_nullsub_22_0035ae50__recomp(EEContext&);  // recompiled
void fn_nullsub_23_0035ae60(EEContext&);  // generated body
void fn_nullsub_23_0035ae60__recomp(EEContext&);  // recompiled
void fn_nullsub_24_0035ae70(EEContext&);  // generated body
void fn_nullsub_24_0035ae70__recomp(EEContext&);  // recompiled
void fn_nullsub_25_0035ae80(EEContext&);  // generated body
void fn_nullsub_25_0035ae80__recomp(EEContext&);  // recompiled
void fn_sub_35AE90_0035ae90(EEContext&);  // generated body
void fn_sub_35AE90_0035ae90__recomp(EEContext&);  // recompiled
void fn_sub_35AEA0_0035aea0(EEContext&);  // generated body
void fn_sub_35AEA0_0035aea0__recomp(EEContext&);  // recompiled
void fn_scrCommand_PUT_0035b090(EEContext&);  // generated body
void fn_scrCommand_PUT_0035b090__recomp(EEContext&);  // recompiled
void fn_sub_35B0D0_0035b0d0(EEContext&);  // generated body
void fn_sub_35B0D0_0035b0d0__recomp(EEContext&);  // recompiled
void fn_scrCommand_SCR_RUN_0035b280(EEContext&);  // generated body
void fn_scrCommand_SCR_RUN_0035b280__recomp(EEContext&);  // recompiled
void fn_scrCommand_SCR_KILL_0035b390(EEContext&);  // generated body
void fn_scrCommand_SCR_KILL_0035b390__recomp(EEContext&);  // recompiled
void fn_scrStartScript_0035b570(EEContext&);  // generated body
void fn_scrStartScript_0035b570__recomp(EEContext&);  // recompiled
void fn_scrCreateTaskFromHeader_0035bb40(EEContext&);  // generated body
void fn_scrCreateTaskFromHeader_0035bb40__recomp(EEContext&);  // recompiled
void fn_scrCreateTaskFromScriptMemory_0035bc00(EEContext&);  // generated body
void fn_scrCreateTaskFromScriptMemory_0035bc00__recomp(EEContext&);  // recompiled
void fn_scrCreateTask_0035bd50(EEContext&);  // generated body
void fn_scrCreateTask_0035bd50__recomp(EEContext&);  // recompiled
void fn_scrReleaseScript_0035be30(EEContext&);  // generated body
void fn_scrReleaseScript_0035be30__recomp(EEContext&);  // recompiled
void fn_sub_35BFB0_0035bfb0(EEContext&);  // generated body
void fn_sub_35BFB0_0035bfb0__recomp(EEContext&);  // recompiled
void fn_scrDestroyTask_0035c200(EEContext&);  // generated body
void fn_scrDestroyTask_0035c200__recomp(EEContext&);  // recompiled
void fn_CodeFunc_Comm_0035cf20(EEContext&);  // generated body
void fn_CodeFunc_Comm_0035cf20__recomp(EEContext&);  // recompiled
void fn_CodeFunc_Run_0035d2c0(EEContext&);  // generated body
void fn_CodeFunc_Run_0035d2c0__recomp(EEContext&);  // recompiled
void fn_sub_35F170_0035f170(EEContext&);  // generated body
void fn_sub_35F170_0035f170__recomp(EEContext&);  // recompiled
void fn_sub_35F4A0_0035f4a0(EEContext&);  // generated body
void fn_sub_35F4A0_0035f4a0__recomp(EEContext&);  // recompiled
void fn_sub_35F5B0_0035f5b0(EEContext&);  // generated body
void fn_sub_35F5B0_0035f5b0__recomp(EEContext&);  // recompiled
void fn_sub_35F680_0035f680(EEContext&);  // generated body
void fn_sub_35F680_0035f680__recomp(EEContext&);  // recompiled
void fn_sub_35F730_0035f730(EEContext&);  // generated body
void fn_sub_35F730_0035f730__recomp(EEContext&);  // recompiled
void fn_sub_35F7A0_0035f7a0(EEContext&);  // generated body
void fn_sub_35F7A0_0035f7a0__recomp(EEContext&);  // recompiled
void fn_sub_35F880_0035f880(EEContext&);  // generated body
void fn_sub_35F880_0035f880__recomp(EEContext&);  // recompiled
void fn_sub_35FD00_0035fd00(EEContext&);  // generated body
void fn_sub_35FD00_0035fd00__recomp(EEContext&);  // recompiled
void fn_sub_35FDB0_0035fdb0(EEContext&);  // generated body
void fn_sub_35FDB0_0035fdb0__recomp(EEContext&);  // recompiled
void fn_sub_393E30_00393e30(EEContext&);  // generated body
void fn_sub_393E30_00393e30__recomp(EEContext&);  // recompiled
void fn_sub_393F30_00393f30(EEContext&);  // generated body
void fn_sub_393F30_00393f30__recomp(EEContext&);  // recompiled
void fn_sub_394040_00394040(EEContext&);  // generated body
void fn_sub_394040_00394040__recomp(EEContext&);  // recompiled
void fn_sub_394070_00394070(EEContext&);  // generated body
void fn_sub_394070_00394070__recomp(EEContext&);  // recompiled
void fn_sub_394270_00394270(EEContext&);  // generated body
void fn_sub_394270_00394270__recomp(EEContext&);  // recompiled
void fn_sub_394C30_00394c30(EEContext&);  // generated body
void fn_sub_394C30_00394c30__recomp(EEContext&);  // recompiled
void fn_sub_394CE0_00394ce0(EEContext&);  // generated body
void fn_sub_394CE0_00394ce0__recomp(EEContext&);  // recompiled
void fn_sub_394D60_00394d60(EEContext&);  // generated body
void fn_sub_394D60_00394d60__recomp(EEContext&);  // recompiled
void fn_sub_394DF0_00394df0(EEContext&);  // generated body
void fn_sub_394DF0_00394df0__recomp(EEContext&);  // recompiled
void fn_sub_394E70_00394e70(EEContext&);  // generated body
void fn_sub_394E70_00394e70__recomp(EEContext&);  // recompiled
void fn_sub_395000_00395000(EEContext&);  // generated body
void fn_sub_395000_00395000__recomp(EEContext&);  // recompiled
void fn_sub_395200_00395200(EEContext&);  // generated body
void fn_sub_395200_00395200__recomp(EEContext&);  // recompiled
void fn_sub_395230_00395230(EEContext&);  // generated body
void fn_sub_395230_00395230__recomp(EEContext&);  // recompiled
void fn_sub_395270_00395270(EEContext&);  // generated body
void fn_sub_395270_00395270__recomp(EEContext&);  // recompiled
void fn_nullsub_27_003952a0(EEContext&);  // generated body
void fn_nullsub_27_003952a0__recomp(EEContext&);  // recompiled
void fn_sub_3952B0_003952b0(EEContext&);  // generated body
void fn_sub_3952B0_003952b0__recomp(EEContext&);  // recompiled
void fn_sub_3952C0_003952c0(EEContext&);  // generated body
void fn_sub_3952C0_003952c0__recomp(EEContext&);  // recompiled
void fn_sub_3952D0_003952d0(EEContext&);  // generated body
void fn_sub_3952D0_003952d0__recomp(EEContext&);  // recompiled
void fn_sub_395350_00395350(EEContext&);  // generated body
void fn_sub_395350_00395350__recomp(EEContext&);  // recompiled
void fn_sub_3953B0_003953b0(EEContext&);  // generated body
void fn_sub_3953B0_003953b0__recomp(EEContext&);  // recompiled
void fn_sub_3953E0_003953e0(EEContext&);  // generated body
void fn_sub_3953E0_003953e0__recomp(EEContext&);  // recompiled
void fn_nullsub_28_00395420(EEContext&);  // generated body
void fn_nullsub_28_00395420__recomp(EEContext&);  // recompiled
void fn_sub_395430_00395430(EEContext&);  // generated body
void fn_sub_395430_00395430__recomp(EEContext&);  // recompiled
void fn_sub_3954E0_003954e0(EEContext&);  // generated body
void fn_sub_3954E0_003954e0__recomp(EEContext&);  // recompiled
void fn_sub_395550_00395550(EEContext&);  // generated body
void fn_sub_395550_00395550__recomp(EEContext&);  // recompiled
void fn_sub_3957D0_003957d0(EEContext&);  // generated body
void fn_sub_3957D0_003957d0__recomp(EEContext&);  // recompiled
void fn_sub_395810_00395810(EEContext&);  // generated body
void fn_sub_395810_00395810__recomp(EEContext&);  // recompiled
void fn_sub_395910_00395910(EEContext&);  // generated body
void fn_sub_395910_00395910__recomp(EEContext&);  // recompiled
void fn_sub_395930_00395930(EEContext&);  // generated body
void fn_sub_395930_00395930__recomp(EEContext&);  // recompiled
void fn_sub_396250_00396250(EEContext&);  // generated body
void fn_sub_396250_00396250__recomp(EEContext&);  // recompiled
void fn_sub_396270_00396270(EEContext&);  // generated body
void fn_sub_396270_00396270__recomp(EEContext&);  // recompiled
void fn_sub_3962C0_003962c0(EEContext&);  // generated body
void fn_sub_3962C0_003962c0__recomp(EEContext&);  // recompiled
void fn_sub_3963C0_003963c0(EEContext&);  // generated body
void fn_sub_3963C0_003963c0__recomp(EEContext&);  // recompiled
void fn_sub_396410_00396410(EEContext&);  // generated body
void fn_sub_396410_00396410__recomp(EEContext&);  // recompiled
void fn_sub_396480_00396480(EEContext&);  // generated body
void fn_sub_396480_00396480__recomp(EEContext&);  // recompiled
void fn_sub_3964C0_003964c0(EEContext&);  // generated body
void fn_sub_3964C0_003964c0__recomp(EEContext&);  // recompiled
void fn_sub_396530_00396530(EEContext&);  // generated body
void fn_sub_396530_00396530__recomp(EEContext&);  // recompiled
void fn_sub_3965D0_003965d0(EEContext&);  // generated body
void fn_sub_3965D0_003965d0__recomp(EEContext&);  // recompiled
void fn_sub_3965F0_003965f0(EEContext&);  // generated body
void fn_sub_3965F0_003965f0__recomp(EEContext&);  // recompiled
void fn_sub_396760_00396760(EEContext&);  // generated body
void fn_sub_396760_00396760__recomp(EEContext&);  // recompiled
void fn_sub_3968A0_003968a0(EEContext&);  // generated body
void fn_sub_3968A0_003968a0__recomp(EEContext&);  // recompiled
void fn_sub_396910_00396910(EEContext&);  // generated body
void fn_sub_396910_00396910__recomp(EEContext&);  // recompiled
void fn_sub_3969B0_003969b0(EEContext&);  // generated body
void fn_sub_3969B0_003969b0__recomp(EEContext&);  // recompiled
void fn_sub_396A70_00396a70(EEContext&);  // generated body
void fn_sub_396A70_00396a70__recomp(EEContext&);  // recompiled
void fn_sub_396BA0_00396ba0(EEContext&);  // generated body
void fn_sub_396BA0_00396ba0__recomp(EEContext&);  // recompiled
void fn_sub_396BF0_00396bf0(EEContext&);  // generated body
void fn_sub_396BF0_00396bf0__recomp(EEContext&);  // recompiled
void fn_sub_396C70_00396c70(EEContext&);  // generated body
void fn_sub_396C70_00396c70__recomp(EEContext&);  // recompiled
void fn_sub_396E30_00396e30(EEContext&);  // generated body
void fn_sub_396E30_00396e30__recomp(EEContext&);  // recompiled
void fn_sub_396ED0_00396ed0(EEContext&);  // generated body
void fn_sub_396ED0_00396ed0__recomp(EEContext&);  // recompiled
void fn_sub_396F50_00396f50(EEContext&);  // generated body
void fn_sub_396F50_00396f50__recomp(EEContext&);  // recompiled
void fn_sub_397030_00397030(EEContext&);  // generated body
void fn_sub_397030_00397030__recomp(EEContext&);  // recompiled
void fn_sub_3970D0_003970d0(EEContext&);  // generated body
void fn_sub_3970D0_003970d0__recomp(EEContext&);  // recompiled
void fn_sub_3971A0_003971a0(EEContext&);  // generated body
void fn_sub_3971A0_003971a0__recomp(EEContext&);  // recompiled
void fn_sub_3973E0_003973e0(EEContext&);  // generated body
void fn_sub_3973E0_003973e0__recomp(EEContext&);  // recompiled
void fn_sub_397450_00397450(EEContext&);  // generated body
void fn_sub_397450_00397450__recomp(EEContext&);  // recompiled
void fn_sub_397500_00397500(EEContext&);  // generated body
void fn_sub_397500_00397500__recomp(EEContext&);  // recompiled
void fn_sub_397510_00397510(EEContext&);  // generated body
void fn_sub_397510_00397510__recomp(EEContext&);  // recompiled
void fn_sub_397520_00397520(EEContext&);  // generated body
void fn_sub_397520_00397520__recomp(EEContext&);  // recompiled
void fn_sub_397580_00397580(EEContext&);  // generated body
void fn_sub_397580_00397580__recomp(EEContext&);  // recompiled
void fn_sub_397630_00397630(EEContext&);  // generated body
void fn_sub_397630_00397630__recomp(EEContext&);  // recompiled
void fn_sub_3976F0_003976f0(EEContext&);  // generated body
void fn_sub_3976F0_003976f0__recomp(EEContext&);  // recompiled
void fn_sub_3977C0_003977c0(EEContext&);  // generated body
void fn_sub_3977C0_003977c0__recomp(EEContext&);  // recompiled
void fn_sub_397870_00397870(EEContext&);  // generated body
void fn_sub_397870_00397870__recomp(EEContext&);  // recompiled
void fn_sub_397950_00397950(EEContext&);  // generated body
void fn_sub_397950_00397950__recomp(EEContext&);  // recompiled
void fn_sub_397D60_00397d60(EEContext&);  // generated body
void fn_sub_397D60_00397d60__recomp(EEContext&);  // recompiled
void fn_sub_397EC0_00397ec0(EEContext&);  // generated body
void fn_sub_397EC0_00397ec0__recomp(EEContext&);  // recompiled
void fn_sub_397F80_00397f80(EEContext&);  // generated body
void fn_sub_397F80_00397f80__recomp(EEContext&);  // recompiled
void fn_sub_398060_00398060(EEContext&);  // generated body
void fn_sub_398060_00398060__recomp(EEContext&);  // recompiled
void fn_sub_3980E0_003980e0(EEContext&);  // generated body
void fn_sub_3980E0_003980e0__recomp(EEContext&);  // recompiled
void fn_sub_398140_00398140(EEContext&);  // generated body
void fn_sub_398140_00398140__recomp(EEContext&);  // recompiled
void fn_sub_3982D0_003982d0(EEContext&);  // generated body
void fn_sub_3982D0_003982d0__recomp(EEContext&);  // recompiled
void fn_sub_398390_00398390(EEContext&);  // generated body
void fn_sub_398390_00398390__recomp(EEContext&);  // recompiled
void fn_sub_3983A0_003983a0(EEContext&);  // generated body
void fn_sub_3983A0_003983a0__recomp(EEContext&);  // recompiled
void fn_sub_3983E0_003983e0(EEContext&);  // generated body
void fn_sub_3983E0_003983e0__recomp(EEContext&);  // recompiled
void fn_sub_39E6F0_0039e6f0(EEContext&);  // generated body
void fn_sub_39E6F0_0039e6f0__recomp(EEContext&);  // recompiled
void fn_sub_39E700_0039e700(EEContext&);  // generated body
void fn_sub_39E700_0039e700__recomp(EEContext&);  // recompiled
void fn_sub_39E7C0_0039e7c0(EEContext&);  // generated body
void fn_sub_39E7C0_0039e7c0__recomp(EEContext&);  // recompiled
void fn_sub_39E820_0039e820(EEContext&);  // generated body
void fn_sub_39E820_0039e820__recomp(EEContext&);  // recompiled
void fn_sub_39E880_0039e880(EEContext&);  // generated body
void fn_sub_39E880_0039e880__recomp(EEContext&);  // recompiled
void fn_sub_39EA20_0039ea20(EEContext&);  // generated body
void fn_sub_39EA20_0039ea20__recomp(EEContext&);  // recompiled
void fn_sub_39EAA0_0039eaa0(EEContext&);  // generated body
void fn_sub_39EAA0_0039eaa0__recomp(EEContext&);  // recompiled
void fn_sub_39EB90_0039eb90(EEContext&);  // generated body
void fn_sub_39EB90_0039eb90__recomp(EEContext&);  // recompiled
void fn_sub_39EC10_0039ec10(EEContext&);  // generated body
void fn_sub_39EC10_0039ec10__recomp(EEContext&);  // recompiled
void fn_sub_39EC60_0039ec60(EEContext&);  // generated body
void fn_sub_39EC60_0039ec60__recomp(EEContext&);  // recompiled
void fn_sub_39EC70_0039ec70(EEContext&);  // generated body
void fn_sub_39EC70_0039ec70__recomp(EEContext&);  // recompiled
void fn_sub_39ED20_0039ed20(EEContext&);  // generated body
void fn_sub_39ED20_0039ed20__recomp(EEContext&);  // recompiled
void fn_sub_39EDD0_0039edd0(EEContext&);  // generated body
void fn_sub_39EDD0_0039edd0__recomp(EEContext&);  // recompiled
void fn_sub_39EE80_0039ee80(EEContext&);  // generated body
void fn_sub_39EE80_0039ee80__recomp(EEContext&);  // recompiled
void fn_sub_39EEE0_0039eee0(EEContext&);  // generated body
void fn_sub_39EEE0_0039eee0__recomp(EEContext&);  // recompiled
void fn_sub_39EEF0_0039eef0(EEContext&);  // generated body
void fn_sub_39EEF0_0039eef0__recomp(EEContext&);  // recompiled
void fn_sub_39EF30_0039ef30(EEContext&);  // generated body
void fn_sub_39EF30_0039ef30__recomp(EEContext&);  // recompiled
void fn_sub_39EF70_0039ef70(EEContext&);  // generated body
void fn_sub_39EF70_0039ef70__recomp(EEContext&);  // recompiled
void fn_sub_39EFD0_0039efd0(EEContext&);  // generated body
void fn_sub_39EFD0_0039efd0__recomp(EEContext&);  // recompiled
void fn_sub_39F050_0039f050(EEContext&);  // generated body
void fn_sub_39F050_0039f050__recomp(EEContext&);  // recompiled
void fn_sub_39F0C0_0039f0c0(EEContext&);  // generated body
void fn_sub_39F0C0_0039f0c0__recomp(EEContext&);  // recompiled
void fn_sub_39F120_0039f120(EEContext&);  // generated body
void fn_sub_39F120_0039f120__recomp(EEContext&);  // recompiled
void fn_sub_39F190_0039f190(EEContext&);  // generated body
void fn_sub_39F190_0039f190__recomp(EEContext&);  // recompiled
void fn_sub_39F210_0039f210(EEContext&);  // generated body
void fn_sub_39F210_0039f210__recomp(EEContext&);  // recompiled
void fn_sub_39F2A0_0039f2a0(EEContext&);  // generated body
void fn_sub_39F2A0_0039f2a0__recomp(EEContext&);  // recompiled
void fn_sub_39F350_0039f350(EEContext&);  // generated body
void fn_sub_39F350_0039f350__recomp(EEContext&);  // recompiled
void fn_sub_39F410_0039f410(EEContext&);  // generated body
void fn_sub_39F410_0039f410__recomp(EEContext&);  // recompiled
void fn_sub_39F6E0_0039f6e0(EEContext&);  // generated body
void fn_sub_39F6E0_0039f6e0__recomp(EEContext&);  // recompiled
void fn_sub_39F710_0039f710(EEContext&);  // generated body
void fn_sub_39F710_0039f710__recomp(EEContext&);  // recompiled
void fn_sub_39F750_0039f750(EEContext&);  // generated body
void fn_sub_39F750_0039f750__recomp(EEContext&);  // recompiled
void fn_sub_39F7C0_0039f7c0(EEContext&);  // generated body
void fn_sub_39F7C0_0039f7c0__recomp(EEContext&);  // recompiled
void fn_sub_39F800_0039f800(EEContext&);  // generated body
void fn_sub_39F800_0039f800__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_35AC50", 0x35AC50, &recomp_gen::fn_sub_35AC50_0035ac50, &recomp_gen::fn_sub_35AC50_0035ac50__recomp},
    {"nullsub_21", 0x35AC80, &recomp_gen::fn_nullsub_21_0035ac80, &recomp_gen::fn_nullsub_21_0035ac80__recomp},
    {"sub_35AD80", 0x35AD80, &recomp_gen::fn_sub_35AD80_0035ad80, &recomp_gen::fn_sub_35AD80_0035ad80__recomp},
    {"sub_35ADB0", 0x35ADB0, &recomp_gen::fn_sub_35ADB0_0035adb0, &recomp_gen::fn_sub_35ADB0_0035adb0__recomp},
    {"nullsub_22", 0x35AE50, &recomp_gen::fn_nullsub_22_0035ae50, &recomp_gen::fn_nullsub_22_0035ae50__recomp},
    {"nullsub_23", 0x35AE60, &recomp_gen::fn_nullsub_23_0035ae60, &recomp_gen::fn_nullsub_23_0035ae60__recomp},
    {"nullsub_24", 0x35AE70, &recomp_gen::fn_nullsub_24_0035ae70, &recomp_gen::fn_nullsub_24_0035ae70__recomp},
    {"nullsub_25", 0x35AE80, &recomp_gen::fn_nullsub_25_0035ae80, &recomp_gen::fn_nullsub_25_0035ae80__recomp},
    {"sub_35AE90", 0x35AE90, &recomp_gen::fn_sub_35AE90_0035ae90, &recomp_gen::fn_sub_35AE90_0035ae90__recomp},
    {"sub_35AEA0", 0x35AEA0, &recomp_gen::fn_sub_35AEA0_0035aea0, &recomp_gen::fn_sub_35AEA0_0035aea0__recomp},
    {"scrCommand_PUT", 0x35B090, &recomp_gen::fn_scrCommand_PUT_0035b090, &recomp_gen::fn_scrCommand_PUT_0035b090__recomp},
    {"sub_35B0D0", 0x35B0D0, &recomp_gen::fn_sub_35B0D0_0035b0d0, &recomp_gen::fn_sub_35B0D0_0035b0d0__recomp},
    {"scrCommand_SCR_RUN", 0x35B280, &recomp_gen::fn_scrCommand_SCR_RUN_0035b280, &recomp_gen::fn_scrCommand_SCR_RUN_0035b280__recomp},
    {"scrCommand_SCR_KILL", 0x35B390, &recomp_gen::fn_scrCommand_SCR_KILL_0035b390, &recomp_gen::fn_scrCommand_SCR_KILL_0035b390__recomp},
    {"scrStartScript", 0x35B570, &recomp_gen::fn_scrStartScript_0035b570, &recomp_gen::fn_scrStartScript_0035b570__recomp},
    {"scrCreateTaskFromHeader", 0x35BB40, &recomp_gen::fn_scrCreateTaskFromHeader_0035bb40, &recomp_gen::fn_scrCreateTaskFromHeader_0035bb40__recomp},
    {"scrCreateTaskFromScriptMemory", 0x35BC00, &recomp_gen::fn_scrCreateTaskFromScriptMemory_0035bc00, &recomp_gen::fn_scrCreateTaskFromScriptMemory_0035bc00__recomp},
    {"scrCreateTask", 0x35BD50, &recomp_gen::fn_scrCreateTask_0035bd50, &recomp_gen::fn_scrCreateTask_0035bd50__recomp},
    {"scrReleaseScript", 0x35BE30, &recomp_gen::fn_scrReleaseScript_0035be30, &recomp_gen::fn_scrReleaseScript_0035be30__recomp},
    {"sub_35BFB0", 0x35BFB0, &recomp_gen::fn_sub_35BFB0_0035bfb0, &recomp_gen::fn_sub_35BFB0_0035bfb0__recomp},
    {"scrDestroyTask", 0x35C200, &recomp_gen::fn_scrDestroyTask_0035c200, &recomp_gen::fn_scrDestroyTask_0035c200__recomp},
    {"CodeFunc_Comm", 0x35CF20, &recomp_gen::fn_CodeFunc_Comm_0035cf20, &recomp_gen::fn_CodeFunc_Comm_0035cf20__recomp},
    {"CodeFunc_Run", 0x35D2C0, &recomp_gen::fn_CodeFunc_Run_0035d2c0, &recomp_gen::fn_CodeFunc_Run_0035d2c0__recomp},
    {"sub_35F170", 0x35F170, &recomp_gen::fn_sub_35F170_0035f170, &recomp_gen::fn_sub_35F170_0035f170__recomp},
    {"sub_35F4A0", 0x35F4A0, &recomp_gen::fn_sub_35F4A0_0035f4a0, &recomp_gen::fn_sub_35F4A0_0035f4a0__recomp},
    {"sub_35F5B0", 0x35F5B0, &recomp_gen::fn_sub_35F5B0_0035f5b0, &recomp_gen::fn_sub_35F5B0_0035f5b0__recomp},
    {"sub_35F680", 0x35F680, &recomp_gen::fn_sub_35F680_0035f680, &recomp_gen::fn_sub_35F680_0035f680__recomp},
    {"sub_35F730", 0x35F730, &recomp_gen::fn_sub_35F730_0035f730, &recomp_gen::fn_sub_35F730_0035f730__recomp},
    {"sub_35F7A0", 0x35F7A0, &recomp_gen::fn_sub_35F7A0_0035f7a0, &recomp_gen::fn_sub_35F7A0_0035f7a0__recomp},
    {"sub_35F880", 0x35F880, &recomp_gen::fn_sub_35F880_0035f880, &recomp_gen::fn_sub_35F880_0035f880__recomp},
    {"sub_35FD00", 0x35FD00, &recomp_gen::fn_sub_35FD00_0035fd00, &recomp_gen::fn_sub_35FD00_0035fd00__recomp},
    {"sub_35FDB0", 0x35FDB0, &recomp_gen::fn_sub_35FDB0_0035fdb0, &recomp_gen::fn_sub_35FDB0_0035fdb0__recomp},
    {"sub_393E30", 0x393E30, &recomp_gen::fn_sub_393E30_00393e30, &recomp_gen::fn_sub_393E30_00393e30__recomp},
    {"sub_393F30", 0x393F30, &recomp_gen::fn_sub_393F30_00393f30, &recomp_gen::fn_sub_393F30_00393f30__recomp},
    {"sub_394040", 0x394040, &recomp_gen::fn_sub_394040_00394040, &recomp_gen::fn_sub_394040_00394040__recomp},
    {"sub_394070", 0x394070, &recomp_gen::fn_sub_394070_00394070, &recomp_gen::fn_sub_394070_00394070__recomp},
    {"sub_394270", 0x394270, &recomp_gen::fn_sub_394270_00394270, &recomp_gen::fn_sub_394270_00394270__recomp},
    {"sub_394C30", 0x394C30, &recomp_gen::fn_sub_394C30_00394c30, &recomp_gen::fn_sub_394C30_00394c30__recomp},
    {"sub_394CE0", 0x394CE0, &recomp_gen::fn_sub_394CE0_00394ce0, &recomp_gen::fn_sub_394CE0_00394ce0__recomp},
    {"sub_394D60", 0x394D60, &recomp_gen::fn_sub_394D60_00394d60, &recomp_gen::fn_sub_394D60_00394d60__recomp},
    {"sub_394DF0", 0x394DF0, &recomp_gen::fn_sub_394DF0_00394df0, &recomp_gen::fn_sub_394DF0_00394df0__recomp},
    {"sub_394E70", 0x394E70, &recomp_gen::fn_sub_394E70_00394e70, &recomp_gen::fn_sub_394E70_00394e70__recomp},
    {"sub_395000", 0x395000, &recomp_gen::fn_sub_395000_00395000, &recomp_gen::fn_sub_395000_00395000__recomp},
    {"sub_395200", 0x395200, &recomp_gen::fn_sub_395200_00395200, &recomp_gen::fn_sub_395200_00395200__recomp},
    {"sub_395230", 0x395230, &recomp_gen::fn_sub_395230_00395230, &recomp_gen::fn_sub_395230_00395230__recomp},
    {"sub_395270", 0x395270, &recomp_gen::fn_sub_395270_00395270, &recomp_gen::fn_sub_395270_00395270__recomp},
    {"nullsub_27", 0x3952A0, &recomp_gen::fn_nullsub_27_003952a0, &recomp_gen::fn_nullsub_27_003952a0__recomp},
    {"sub_3952B0", 0x3952B0, &recomp_gen::fn_sub_3952B0_003952b0, &recomp_gen::fn_sub_3952B0_003952b0__recomp},
    {"sub_3952C0", 0x3952C0, &recomp_gen::fn_sub_3952C0_003952c0, &recomp_gen::fn_sub_3952C0_003952c0__recomp},
    {"sub_3952D0", 0x3952D0, &recomp_gen::fn_sub_3952D0_003952d0, &recomp_gen::fn_sub_3952D0_003952d0__recomp},
    {"sub_395350", 0x395350, &recomp_gen::fn_sub_395350_00395350, &recomp_gen::fn_sub_395350_00395350__recomp},
    {"sub_3953B0", 0x3953B0, &recomp_gen::fn_sub_3953B0_003953b0, &recomp_gen::fn_sub_3953B0_003953b0__recomp},
    {"sub_3953E0", 0x3953E0, &recomp_gen::fn_sub_3953E0_003953e0, &recomp_gen::fn_sub_3953E0_003953e0__recomp},
    {"nullsub_28", 0x395420, &recomp_gen::fn_nullsub_28_00395420, &recomp_gen::fn_nullsub_28_00395420__recomp},
    {"sub_395430", 0x395430, &recomp_gen::fn_sub_395430_00395430, &recomp_gen::fn_sub_395430_00395430__recomp},
    {"sub_3954E0", 0x3954E0, &recomp_gen::fn_sub_3954E0_003954e0, &recomp_gen::fn_sub_3954E0_003954e0__recomp},
    {"sub_395550", 0x395550, &recomp_gen::fn_sub_395550_00395550, &recomp_gen::fn_sub_395550_00395550__recomp},
    {"sub_3957D0", 0x3957D0, &recomp_gen::fn_sub_3957D0_003957d0, &recomp_gen::fn_sub_3957D0_003957d0__recomp},
    {"sub_395810", 0x395810, &recomp_gen::fn_sub_395810_00395810, &recomp_gen::fn_sub_395810_00395810__recomp},
    {"sub_395910", 0x395910, &recomp_gen::fn_sub_395910_00395910, &recomp_gen::fn_sub_395910_00395910__recomp},
    {"sub_395930", 0x395930, &recomp_gen::fn_sub_395930_00395930, &recomp_gen::fn_sub_395930_00395930__recomp},
    {"sub_396250", 0x396250, &recomp_gen::fn_sub_396250_00396250, &recomp_gen::fn_sub_396250_00396250__recomp},
    {"sub_396270", 0x396270, &recomp_gen::fn_sub_396270_00396270, &recomp_gen::fn_sub_396270_00396270__recomp},
    {"sub_3962C0", 0x3962C0, &recomp_gen::fn_sub_3962C0_003962c0, &recomp_gen::fn_sub_3962C0_003962c0__recomp},
    {"sub_3963C0", 0x3963C0, &recomp_gen::fn_sub_3963C0_003963c0, &recomp_gen::fn_sub_3963C0_003963c0__recomp},
    {"sub_396410", 0x396410, &recomp_gen::fn_sub_396410_00396410, &recomp_gen::fn_sub_396410_00396410__recomp},
    {"sub_396480", 0x396480, &recomp_gen::fn_sub_396480_00396480, &recomp_gen::fn_sub_396480_00396480__recomp},
    {"sub_3964C0", 0x3964C0, &recomp_gen::fn_sub_3964C0_003964c0, &recomp_gen::fn_sub_3964C0_003964c0__recomp},
    {"sub_396530", 0x396530, &recomp_gen::fn_sub_396530_00396530, &recomp_gen::fn_sub_396530_00396530__recomp},
    {"sub_3965D0", 0x3965D0, &recomp_gen::fn_sub_3965D0_003965d0, &recomp_gen::fn_sub_3965D0_003965d0__recomp},
    {"sub_3965F0", 0x3965F0, &recomp_gen::fn_sub_3965F0_003965f0, &recomp_gen::fn_sub_3965F0_003965f0__recomp},
    {"sub_396760", 0x396760, &recomp_gen::fn_sub_396760_00396760, &recomp_gen::fn_sub_396760_00396760__recomp},
    {"sub_3968A0", 0x3968A0, &recomp_gen::fn_sub_3968A0_003968a0, &recomp_gen::fn_sub_3968A0_003968a0__recomp},
    {"sub_396910", 0x396910, &recomp_gen::fn_sub_396910_00396910, &recomp_gen::fn_sub_396910_00396910__recomp},
    {"sub_3969B0", 0x3969B0, &recomp_gen::fn_sub_3969B0_003969b0, &recomp_gen::fn_sub_3969B0_003969b0__recomp},
    {"sub_396A70", 0x396A70, &recomp_gen::fn_sub_396A70_00396a70, &recomp_gen::fn_sub_396A70_00396a70__recomp},
    {"sub_396BA0", 0x396BA0, &recomp_gen::fn_sub_396BA0_00396ba0, &recomp_gen::fn_sub_396BA0_00396ba0__recomp},
    {"sub_396BF0", 0x396BF0, &recomp_gen::fn_sub_396BF0_00396bf0, &recomp_gen::fn_sub_396BF0_00396bf0__recomp},
    {"sub_396C70", 0x396C70, &recomp_gen::fn_sub_396C70_00396c70, &recomp_gen::fn_sub_396C70_00396c70__recomp},
    {"sub_396E30", 0x396E30, &recomp_gen::fn_sub_396E30_00396e30, &recomp_gen::fn_sub_396E30_00396e30__recomp},
    {"sub_396ED0", 0x396ED0, &recomp_gen::fn_sub_396ED0_00396ed0, &recomp_gen::fn_sub_396ED0_00396ed0__recomp},
    {"sub_396F50", 0x396F50, &recomp_gen::fn_sub_396F50_00396f50, &recomp_gen::fn_sub_396F50_00396f50__recomp},
    {"sub_397030", 0x397030, &recomp_gen::fn_sub_397030_00397030, &recomp_gen::fn_sub_397030_00397030__recomp},
    {"sub_3970D0", 0x3970D0, &recomp_gen::fn_sub_3970D0_003970d0, &recomp_gen::fn_sub_3970D0_003970d0__recomp},
    {"sub_3971A0", 0x3971A0, &recomp_gen::fn_sub_3971A0_003971a0, &recomp_gen::fn_sub_3971A0_003971a0__recomp},
    {"sub_3973E0", 0x3973E0, &recomp_gen::fn_sub_3973E0_003973e0, &recomp_gen::fn_sub_3973E0_003973e0__recomp},
    {"sub_397450", 0x397450, &recomp_gen::fn_sub_397450_00397450, &recomp_gen::fn_sub_397450_00397450__recomp},
    {"sub_397500", 0x397500, &recomp_gen::fn_sub_397500_00397500, &recomp_gen::fn_sub_397500_00397500__recomp},
    {"sub_397510", 0x397510, &recomp_gen::fn_sub_397510_00397510, &recomp_gen::fn_sub_397510_00397510__recomp},
    {"sub_397520", 0x397520, &recomp_gen::fn_sub_397520_00397520, &recomp_gen::fn_sub_397520_00397520__recomp},
    {"sub_397580", 0x397580, &recomp_gen::fn_sub_397580_00397580, &recomp_gen::fn_sub_397580_00397580__recomp},
    {"sub_397630", 0x397630, &recomp_gen::fn_sub_397630_00397630, &recomp_gen::fn_sub_397630_00397630__recomp},
    {"sub_3976F0", 0x3976F0, &recomp_gen::fn_sub_3976F0_003976f0, &recomp_gen::fn_sub_3976F0_003976f0__recomp},
    {"sub_3977C0", 0x3977C0, &recomp_gen::fn_sub_3977C0_003977c0, &recomp_gen::fn_sub_3977C0_003977c0__recomp},
    {"sub_397870", 0x397870, &recomp_gen::fn_sub_397870_00397870, &recomp_gen::fn_sub_397870_00397870__recomp},
    {"sub_397950", 0x397950, &recomp_gen::fn_sub_397950_00397950, &recomp_gen::fn_sub_397950_00397950__recomp},
    {"sub_397D60", 0x397D60, &recomp_gen::fn_sub_397D60_00397d60, &recomp_gen::fn_sub_397D60_00397d60__recomp},
    {"sub_397EC0", 0x397EC0, &recomp_gen::fn_sub_397EC0_00397ec0, &recomp_gen::fn_sub_397EC0_00397ec0__recomp},
    {"sub_397F80", 0x397F80, &recomp_gen::fn_sub_397F80_00397f80, &recomp_gen::fn_sub_397F80_00397f80__recomp},
    {"sub_398060", 0x398060, &recomp_gen::fn_sub_398060_00398060, &recomp_gen::fn_sub_398060_00398060__recomp},
    {"sub_3980E0", 0x3980E0, &recomp_gen::fn_sub_3980E0_003980e0, &recomp_gen::fn_sub_3980E0_003980e0__recomp},
    {"sub_398140", 0x398140, &recomp_gen::fn_sub_398140_00398140, &recomp_gen::fn_sub_398140_00398140__recomp},
    {"sub_3982D0", 0x3982D0, &recomp_gen::fn_sub_3982D0_003982d0, &recomp_gen::fn_sub_3982D0_003982d0__recomp},
    {"sub_398390", 0x398390, &recomp_gen::fn_sub_398390_00398390, &recomp_gen::fn_sub_398390_00398390__recomp},
    {"sub_3983A0", 0x3983A0, &recomp_gen::fn_sub_3983A0_003983a0, &recomp_gen::fn_sub_3983A0_003983a0__recomp},
    {"sub_3983E0", 0x3983E0, &recomp_gen::fn_sub_3983E0_003983e0, &recomp_gen::fn_sub_3983E0_003983e0__recomp},
    {"sub_39E6F0", 0x39E6F0, &recomp_gen::fn_sub_39E6F0_0039e6f0, &recomp_gen::fn_sub_39E6F0_0039e6f0__recomp},
    {"sub_39E700", 0x39E700, &recomp_gen::fn_sub_39E700_0039e700, &recomp_gen::fn_sub_39E700_0039e700__recomp},
    {"sub_39E7C0", 0x39E7C0, &recomp_gen::fn_sub_39E7C0_0039e7c0, &recomp_gen::fn_sub_39E7C0_0039e7c0__recomp},
    {"sub_39E820", 0x39E820, &recomp_gen::fn_sub_39E820_0039e820, &recomp_gen::fn_sub_39E820_0039e820__recomp},
    {"sub_39E880", 0x39E880, &recomp_gen::fn_sub_39E880_0039e880, &recomp_gen::fn_sub_39E880_0039e880__recomp},
    {"sub_39EA20", 0x39EA20, &recomp_gen::fn_sub_39EA20_0039ea20, &recomp_gen::fn_sub_39EA20_0039ea20__recomp},
    {"sub_39EAA0", 0x39EAA0, &recomp_gen::fn_sub_39EAA0_0039eaa0, &recomp_gen::fn_sub_39EAA0_0039eaa0__recomp},
    {"sub_39EB90", 0x39EB90, &recomp_gen::fn_sub_39EB90_0039eb90, &recomp_gen::fn_sub_39EB90_0039eb90__recomp},
    {"sub_39EC10", 0x39EC10, &recomp_gen::fn_sub_39EC10_0039ec10, &recomp_gen::fn_sub_39EC10_0039ec10__recomp},
    {"sub_39EC60", 0x39EC60, &recomp_gen::fn_sub_39EC60_0039ec60, &recomp_gen::fn_sub_39EC60_0039ec60__recomp},
    {"sub_39EC70", 0x39EC70, &recomp_gen::fn_sub_39EC70_0039ec70, &recomp_gen::fn_sub_39EC70_0039ec70__recomp},
    {"sub_39ED20", 0x39ED20, &recomp_gen::fn_sub_39ED20_0039ed20, &recomp_gen::fn_sub_39ED20_0039ed20__recomp},
    {"sub_39EDD0", 0x39EDD0, &recomp_gen::fn_sub_39EDD0_0039edd0, &recomp_gen::fn_sub_39EDD0_0039edd0__recomp},
    {"sub_39EE80", 0x39EE80, &recomp_gen::fn_sub_39EE80_0039ee80, &recomp_gen::fn_sub_39EE80_0039ee80__recomp},
    {"sub_39EEE0", 0x39EEE0, &recomp_gen::fn_sub_39EEE0_0039eee0, &recomp_gen::fn_sub_39EEE0_0039eee0__recomp},
    {"sub_39EEF0", 0x39EEF0, &recomp_gen::fn_sub_39EEF0_0039eef0, &recomp_gen::fn_sub_39EEF0_0039eef0__recomp},
    {"sub_39EF30", 0x39EF30, &recomp_gen::fn_sub_39EF30_0039ef30, &recomp_gen::fn_sub_39EF30_0039ef30__recomp},
    {"sub_39EF70", 0x39EF70, &recomp_gen::fn_sub_39EF70_0039ef70, &recomp_gen::fn_sub_39EF70_0039ef70__recomp},
    {"sub_39EFD0", 0x39EFD0, &recomp_gen::fn_sub_39EFD0_0039efd0, &recomp_gen::fn_sub_39EFD0_0039efd0__recomp},
    {"sub_39F050", 0x39F050, &recomp_gen::fn_sub_39F050_0039f050, &recomp_gen::fn_sub_39F050_0039f050__recomp},
    {"sub_39F0C0", 0x39F0C0, &recomp_gen::fn_sub_39F0C0_0039f0c0, &recomp_gen::fn_sub_39F0C0_0039f0c0__recomp},
    {"sub_39F120", 0x39F120, &recomp_gen::fn_sub_39F120_0039f120, &recomp_gen::fn_sub_39F120_0039f120__recomp},
    {"sub_39F190", 0x39F190, &recomp_gen::fn_sub_39F190_0039f190, &recomp_gen::fn_sub_39F190_0039f190__recomp},
    {"sub_39F210", 0x39F210, &recomp_gen::fn_sub_39F210_0039f210, &recomp_gen::fn_sub_39F210_0039f210__recomp},
    {"sub_39F2A0", 0x39F2A0, &recomp_gen::fn_sub_39F2A0_0039f2a0, &recomp_gen::fn_sub_39F2A0_0039f2a0__recomp},
    {"sub_39F350", 0x39F350, &recomp_gen::fn_sub_39F350_0039f350, &recomp_gen::fn_sub_39F350_0039f350__recomp},
    {"sub_39F410", 0x39F410, &recomp_gen::fn_sub_39F410_0039f410, &recomp_gen::fn_sub_39F410_0039f410__recomp},
    {"sub_39F6E0", 0x39F6E0, &recomp_gen::fn_sub_39F6E0_0039f6e0, &recomp_gen::fn_sub_39F6E0_0039f6e0__recomp},
    {"sub_39F710", 0x39F710, &recomp_gen::fn_sub_39F710_0039f710, &recomp_gen::fn_sub_39F710_0039f710__recomp},
    {"sub_39F750", 0x39F750, &recomp_gen::fn_sub_39F750_0039f750, &recomp_gen::fn_sub_39F750_0039f750__recomp},
    {"sub_39F7C0", 0x39F7C0, &recomp_gen::fn_sub_39F7C0_0039f7c0, &recomp_gen::fn_sub_39F7C0_0039f7c0__recomp},
    {"sub_39F800", 0x39F800, &recomp_gen::fn_sub_39F800_0039f800, &recomp_gen::fn_sub_39F800_0039f800__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena (the generic sweep: bad inputs and
// early stops; the meaningful pairs are the cases below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 12;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus) through two trampolines that set chosen FPRs and run each body inside its own
// stand-in world (stand_ins.h). The worlds persist across the pairs of one sequence -- world[0] serves the hand runs,
// world[1] the recompiled ones; both see the same calls in the same order, so they stay identical (their call logs are
// compared after every pair) and a sequence (create -> step -> destroy) keeps its heap and file layer.
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool pump = false;  // serve one H_Cdvd_Update before the body (the frame's read pump; registers restored after)
};
Tramp g_t;
int g_pairs = 0;
int g_stops = 0;  // pairs that ended at the same early stop in both bodies (a callee not emitted and not stood in)
std::map<std::string, int> g_stop_names;

constexpr u32 kEvtHeapAlloc = 0x386AE0u;  // mt_evtMisc.c's event heap: alloc(size, tag) (not emitted: stood in)

void script3_world(StandInWorld& w) {
    install_standard(w);
    StandIns& s = w.si;
    // the event heap: blocks from the stand-in heap, so the PM reader / registry / koma work are real guest memory
    s.install(kEvtHeapAlloc, "sub_386AE0", [&w](EEContext&, StandIns&, StandInCall& c) {
        const u32 b = w.heap.alloc(static_cast<u32>(c.args[0]));
        c.v0 = sx(b);
        c.extra = b;
    });
    // everything else these bodies call that the test build does not emit: recorders with a plausible result
    const std::pair<u32, u64> rec[] = {
        {0x386B70, 0},          {0x386C40, 0},          {0x1052B0, 0},     {0x3A2D80, 5},  // itfMesMngInitialize -> 5
        {0x3A4990, 0},          {0x3A3060, 0},          {0x3A4010, 0},
        // (no recorder for the effect rng sub_3580B0: it is replaced and the MT_Misc_Rand pairs below need it to run;
        // a stand-in would serve it since the hooked forwarders, 2026-10-29)
        {0x3BD9A0, 7},          {0x3BD8B0, 3},          {0x3A2A30, 0},     {0x3A3420, 0},
        {0x3A4B90, 0x1400},     {0x3A30C0, 0},          {0x3A37C0, 0},     {0x38D6B0, 0},
        {0x110F80, 0},          {0x111580, 0},          {0x3CF5D0, 0},     {0x111500, 0},
        {0x1114B0, 1},          {0x111530, 0},          {0x3B5CF0, 1},     {0x3B5D10, 1},
        {0x3B7090, 0},          {0x3B64C0, 0x12345},    {0x3B9550, 0},     {0x109F60, 0},
        {0x10A370, 0},          {0x10A100, 0},          {0x1099D0, 0},     {0x3CF160, 0},
        {0x3CF3A0, 0x1F3F000},  {0x3CF240, 0},          {0x172160, 0},     {0x1717C0, 1},
        {0x3A4270, 0},          {0x386E20, 0},          {0x386E40, 0},     {0x3C77A0, 0},
        {0x16DFB0, 0},          {0x16E100, 0},          {0x3BE8E0, 1},     {0x1728D0, 0},
        {0x16E920, 0},          {0x175360, 3},          {0x173780, 9},     {0x395170, 0},
    };
    for (const auto& [va, v0] : rec)
        if (!s.has(va)) s.install_recorder(va, "callee", v0);
}

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.world[K]) {
        g_t.world[K] = std::make_unique<StandInWorld>();
        script3_world(*g_t.world[K]);
    }
    StandInsScope scope(g_t.world[K]->si);
    if (g_t.pump) {
        u128 gpr[32];
        std::memcpy(gpr, c.gpr, sizeof gpr);
        g_t.world[K]->si.serve(c, kHCdvdUpdateFn);
        std::memcpy(c.gpr, gpr, sizeof gpr);
    }
    g_t.fn[K](c);
}

void fresh_worlds() {
    g_t.world[0].reset();
    g_t.world[1].reset();
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
    bool pump = false;
};

hgp::Run s3_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.pump = o.pump;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    ++g_pairs;
    if (r.stopped) {
        ++g_stops;
        ++g_stop_names[std::string(what) + " @ " + std::to_string(r.stop_pc) + " " + r.what.substr(0, 80)];
    }
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u32 f0_of(const hgp::Run& r) { return r.end.fpr[0]; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
u32 fbits(float f) { return std::bit_cast<u32>(f); }
float fval(u32 b) { return std::bit_cast<float>(b); }

// Free RAM in every snapshot and in the ELF image: above the stand-in heap (0x1C00000-0x1F00000), below the main-thread
// stack (0x1F60000-0x2000000).
constexpr u32 kBf = 0x01F00000u;    // a BF image (field.bf: 73,407 bytes)
constexpr u32 kRec = 0x01F30000u;   // records the tests build (event player, slots, tables)
constexpr u32 kText = 0x01F48000u;  // string buffers

constexpr u32 kTaskListHead = 0x7CE580u, kTaskListTail = 0x7CE584u, kTaskCount = 0x7CE57Cu, kCurrentTask = 0x7CE5A8u;

bool load_snapshot(Machine& m) {
    const std::vector<u8> snap = read_snapshot("dorm_replay_4900");  // the dorm route: a scripted event is running
    if (snap.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(m);
    return true;
}

std::vector<u8> read_host(const std::string& rel) {
    std::ifstream f(extracted_root() + "/" + rel, std::ios::binary);
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

// A BF image in guest memory, split the way scrStartScript2 splits it (descriptors {type, size, count, offset} at
// +0x20, count at +0x10).
struct Bf {
    u32 base = 0, size = 0, sections = 0, procs = 0, jumps = 0, insns = 0, messages = 0, strings = 0, nprocs = 0;
};
Bf put_bf(Machine& m, const std::vector<u8>& img, u32 at) {
    std::memcpy(m.at(at), img.data(), img.size());
    Bf b;
    b.base = at;
    b.size = static_cast<u32>(img.size());
    b.sections = at + 0x20;
    const u32 n = r32(m, at + 0x10);
    for (u32 i = 0; i < n; ++i) {
        const u32 d = at + 0x20 + 16 * i;
        const u32 type = r32(m, d), count = r32(m, d + 8), off = r32(m, d + 12);
        if (type == 0) b.procs = at + off, b.nprocs = count;
        if (type == 1) b.jumps = at + off;
        if (type == 2) b.insns = at + off;
        if (type == 3 && count != 0) b.messages = at + off;
        if (type == 4) b.strings = at + off;
    }
    return b;
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; fewer seeds: the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(script3): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int stops_total = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops_total += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
    }
    MESSAGE("script3 random worlds: " << seeds << " pairs per function, " << stops_total << " stopped early");
}

// =====================================================================================================================
// The script task layer on field.bf, inside the dorm snapshot's running-script list
// =====================================================================================================================
TEST_CASE("game(script3): script tasks from field.bf -- start, create, COMM dispatch, release (heap stand-ins)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> img = read_host("DATA/FIELD/SCRIPT/FIELD.BF");
    if (!load_snapshot(m) || img.size() < 0x70) {
        MESSAGE("SKIP: no dorm snapshot or no extracted field.bf");
        return;
    }
    fresh_worlds();
    const Bf bf = put_bf(m, img, kBf);
    REQUIRE(bf.nprocs > 4);
    const u32 count0 = r32(m, kTaskCount);
    const u32 tail0 = r32(m, kTaskListTail);

    // scrStartScript: the bad-input rejections (K_Abort, 0) and three real procedures
    const Opt full{{{GPR_T0, sx(bf.insns)}, {GPR_T1, sx(bf.messages)}, {GPR_T2, sx(bf.strings)}, {GPR_T3, 0}}};
    {
        const hgp::Run r = s3_pair(m, "scrStartScript", {0, sx(bf.sections), sx(bf.procs), sx(bf.jumps)}, 1, "scrStartScript: no image", full);
        CHECK(v0_of(r) == 0);
        Opt bad = full;
        bad.gpr_in[GPR_T3] = sx(bf.nprocs);  // one past the last procedure
        CHECK(v0_of(s3_pair(m, "scrStartScript", {sx(bf.base), sx(bf.sections), sx(bf.procs), sx(bf.jumps)}, 2, "scrStartScript: proc == count", bad)) == 0);
        bad.gpr_in[GPR_T3] = sx(0xFFFFFFFFu);
        CHECK(v0_of(s3_pair(m, "scrStartScript", {sx(bf.base), sx(bf.sections), sx(bf.procs), sx(bf.jumps)}, 3, "scrStartScript: proc -1", bad)) == 0);
        CHECK(r32(m, kTaskCount) == count0);
    }
    std::vector<u32> tasks;
    for (u32 proc : {0u, 1u, bf.nprocs - 1}) {
        Opt o = full;
        o.gpr_in[GPR_T3] = proc;
        const hgp::Run r = s3_pair(m, "scrStartScript", {sx(bf.base), sx(bf.sections), sx(bf.procs), sx(bf.jumps)}, 10 + proc, "scrStartScript: field.bf", o);
        const u32 t = static_cast<u32>(v0_of(r));
        REQUIRE(t != 0);
        tasks.push_back(t);
        // documented layout (18_script_vm.md section 3)
        CHECK(m.str(t, 24) == m.str(bf.procs + 32 * proc, 24));
        CHECK(r32(m, t + s3::kTaskPc) == r32(m, bf.procs + 32 * proc + s3::kLabelInsn));
        CHECK(r32(m, t + s3::kTaskSp) == 0);
        CHECK(r32(m, t + s3::kTaskImage) == bf.base);
        CHECK(r32(m, t + s3::kTaskInsn) == bf.insns);
        CHECK(r32(m, t + s3::kTaskStartProc) == proc);
        CHECK(r32(m, t + s3::kTaskMessageId) == 5);  // the itfMesMngInitialize stand-in's handle (section 3 present)
        CHECK(r32(m, t + s3::kTaskProcess) == 0);
        CHECK(r32(m, kTaskListTail) == t);
        CHECK(r32(m, t + s3::kTaskNext) == 0);
    }
    CHECK(r32(m, kTaskCount) == count0 + 3);
    CHECK(r32(m, tasks[0] + s3::kTaskPrev) == tail0);

    // COMM dispatch through CodeFunc_Comm on the first task: the instruction stream is redirected to words the test
    // writes ({u16 opcode 8, s16 id}), the arguments pushed as int slots.
    const u32 t = tasks[0];
    const u32 code = kRec + 0x2000;
    auto comm = [&](u16 id, std::initializer_list<u32> args, u32 seed, const char* what) {
        w16(m, code, 8);
        w16(m, code + 2, id);
        w32(m, t + s3::kTaskInsn, code);
        w32(m, t + s3::kTaskPc, 0);
        const u32 sp = static_cast<u32>(args.size());  // arg0 is the top slot (sp - 1)
        u32 i = 0;
        for (u32 v : args) {
            const u32 slot = sp - 1 - i;
            w8(m, t + s3::kTaskTags + slot, 0);
            w32(m, t + s3::kTaskValues + 4 * slot, v);
            ++i;
        }
        w32(m, t + s3::kTaskSp, sp);
        return s3_pair(m, "CodeFunc_Comm", {sx(t), 0, 0, 0}, seed, what);
    };
    {
        const hgp::Run r = comm(16, {1234}, 100, "CodeFunc_Comm: PUT");  // COMM 16 PUT (argc 1)
        CHECK(v0_of(r) == 1);
        CHECK(r32(m, t + s3::kTaskSp) == 0);  // sp -= argc
        CHECK(r32(m, t + s3::kTaskPc) == 1);  // pc += 1
        CHECK(r32(m, kCurrentTask) == t);
        const auto& log = g_t.world[1]->si.log;
        REQUIRE(!log.empty());
        CHECK(log.back().text == "PUT -> 1234\n");
    }
    {
        const u32 str = kText;
        std::memcpy(m.at(str), "hello", 6);
        w16(m, code, 8);
        w16(m, code + 2, 18);
        w32(m, t + s3::kTaskInsn, code);
        w32(m, t + s3::kTaskPc, 0);
        w8(m, t + s3::kTaskTags, 5);  // a string slot (PUSHSTR's tag)
        w32(m, t + s3::kTaskValues, str);
        w32(m, t + s3::kTaskSp, 1);
        const hgp::Run r = s3_pair(m, "CodeFunc_Comm", {sx(t), 0, 0, 0}, 101, "CodeFunc_Comm: PUTSTR");
        CHECK(v0_of(r) == 1);
        CHECK(g_t.world[1]->si.log.back().text == "PUTSTR -> hello\n");
    }
    {
        w32(m, t + s3::kTaskCmdTimer, 0);
        const hgp::Run r = comm(11, {}, 102, "CodeFunc_Comm: SYNC, first frame");  // COMM 11 SYNC: not done yet
        CHECK(v0_of(r) == 2);
        CHECK(r32(m, t + s3::kTaskPc) == 0);
    }
    // SCR_RUN without a process (the assert print), then with one: a new task from the current script
    {
        const hgp::Run r = comm(23, {1, 2}, 103, "CodeFunc_Comm: SCR_RUN, no process");
        CHECK(v0_of(r) == 1);
        CHECK(r32(m, kTaskCount) == count0 + 3);
    }
    // a real process for the second task: scrCreateTaskFromScriptMemory makes its own copy and process
    const hgp::Run cm = s3_pair(m, "scrCreateTaskFromScriptMemory", {0x1000, sx(bf.base), bf.size, 2}, 104, "scrCreateTaskFromScriptMemory");
    const u32 proc = static_cast<u32>(v0_of(cm));
    REQUIRE(proc != 0);
    const u32 work = r32(m, proc + 0x3C);  // the kwln task's work = the script record
    REQUIRE(work != 0);
    CHECK(r32(m, work + s3::kTaskProcess) == proc);
    CHECK(r32(m, work + s3::kTaskOwnedImage) != 0);
    CHECK(r32(m, work + s3::kTaskOwnedImage) != bf.base);
    CHECK(r32(m, proc + 0x20) == 0x1000);  // the kwln priority
    CHECK(m.str(proc, 24) == m.str(bf.procs + 64, 24));  // the process is named after the procedure
    CHECK(r32(m, kTaskCount) == count0 + 4);
    {
        w32(m, t + s3::kTaskProcess, proc);  // the first task now "has" that process
        const hgp::Run r = comm(23, {3, 5}, 105, "CodeFunc_Comm: SCR_RUN proc 3");
        CHECK(v0_of(r) == 1);
        CHECK(r32(m, kTaskCount) == count0 + 5);
        const u32 handle = r32(m, t + s3::kTaskValues + 4 * 27);  // the COMM return register (slot 27)
        CHECK(handle != 0);
        if (handle != 0) {
            CHECK(r32(m, handle + 0x20) == 0x1000 + 5);  // priority = the caller's + arg1
            const u32 rec = r32(m, handle + 0x3C);
            CHECK(r32(m, rec + s3::kTaskStartProc) == 3);
            CHECK(r32(m, rec + s3::kTaskInsn) == code);  // the CURRENT task's section pointers (here the test's words)
            CHECK(r32(m, rec + s3::kTaskImage) == bf.base);
            CHECK(r32(m, rec + s3::kTaskOwnedImage) == 0);
            // SCR_KILL of that handle: the kwln destroy runs scrDestroyTask -> scrReleaseScript
            const hgp::Run k = comm(24, {handle}, 106, "CodeFunc_Comm: SCR_KILL");
            CHECK(v0_of(k) == 1);
        }
    }
    s3_pair(m, "scrCreateTaskFromHeader", {0x900, sx(bf.base), 4, 0}, 107, "scrCreateTaskFromHeader");
    s3_pair(m, "CodeFunc_Run", {sx(t), 0, 0, 0}, 108, "CodeFunc_Run");
    // release what the case made (the destroy callback path and the direct one)
    s3_pair(m, "scrDestroyTask", {sx(proc), 0, 0, 0}, 109, "scrDestroyTask");
    w32(m, t + s3::kTaskProcess, 0);
    for (std::size_t i = 0; i < tasks.size(); ++i)
        s3_pair(m, "scrReleaseScript", {sx(tasks[i]), 0, 0, 0}, 110 + static_cast<u32>(i), "scrReleaseScript");
    CHECK(r32(m, kTaskListTail) != tasks.back());
    // the field's sweep over every running script of the snapshot
    s3_pair(m, "sub_35BFB0", {0, 0, 0, 0}, 120, "sub_35BFB0: kill all scripts");
    MESSAGE("script tasks: running scripts at the start " << count0 << ", after the sweep " << r32(m, kTaskCount));
    fresh_worlds();
}

// =====================================================================================================================
// mt_evtMessage.c: the 32-byte message slot and its request state machine
// =====================================================================================================================
TEST_CASE("game(script3): message slots -- open, request, the phases of MT_Msg_Update, close") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m)) {
        MESSAGE("SKIP: no dorm snapshot");
        return;
    }
    fresh_worlds();
    using namespace s3;
    const u32 slot = kRec;
    std::memset(m.at(slot), 0, 32);
    const char* opens[3] = {"sub_39EC70", "sub_39ED20", "sub_39EDD0"};
    for (u32 kind = 0; kind < 3; ++kind) {
        std::memset(m.at(slot), 0, 32);
        const hgp::Run r = s3_pair(m, opens[kind], {sx(slot), sx(kBf), 0, 0}, 200 + kind, opens[kind]);
        CHECK(v0_of(r) == 5);
        CHECK(r32(m, slot + kMsgActive) == 1);
        CHECK(r32(m, slot + kMsgKind) == kind);
        CHECK(r32(m, slot + kMsgHandle) == 5);
        CHECK(v0_of(s3_pair(m, "sub_39EEE0", {sx(slot), 0, 0, 0}, 210 + kind, "MT_Msg_IsOpen")) == 1);
        CHECK(v0_of(s3_pair(m, "sub_39F6E0", {sx(slot), 0, 0, 0}, 220 + kind, "MT_Msg_IsIdle")) == 1);
        // a request with no message and no selection: phase 1 -> 3 -> 5 -> 0
        s3_pair(m, "sub_39F210", {sx(slot), sx(0xFFFFFFFFu), sx(0xFFFFFFFFu), 3}, 230 + kind, "MT_Msg_Request (none)");
        CHECK(r32(m, slot + kMsgPhase) == 1);
        CHECK(r32(m, slot + kMsgResult) == 0xFFFFFFFFu);
        const u32 expect[3] = {3, 5, 0};
        for (u32 step = 0; step < 3; ++step) {
            s3_pair(m, "sub_39F410", {sx(slot), 0, 0, 0}, 240 + 10 * kind + step, "MT_Msg_Update");
            CHECK(r32(m, slot + kMsgPhase) == expect[step]);
        }
        // a request with a message and a selection: phase 1 positions / requests (kind rules), then each later phase
        s3_pair(m, "sub_39F210", {sx(slot), 4, 2, 7}, 270 + kind, "MT_Msg_Request");
        CHECK(r32(m, slot + kMsgMessage) == 4);
        CHECK(r32(m, slot + kMsgSelection) == 2);
        CHECK(r32(m, slot + kMsgSelArg) == 7);
        for (u32 phase = 1; phase <= 5; ++phase) {
            w32(m, slot + kMsgPhase, phase);
            s3_pair(m, "sub_39F410", {sx(slot), 0, 0, 0}, 280 + 10 * kind + phase, "MT_Msg_Update (each phase)");
        }
        for (const char* n : {"sub_39EEF0", "sub_39EF30", "sub_39EF70", "sub_39EFD0", "sub_39F050", "sub_39F0C0",
                              "sub_39F120", "sub_39F190", "sub_39F710", "sub_39F750", "sub_39F7C0", "sub_39F800",
                              "sub_39F2A0", "sub_39F350"})
            s3_pair(m, n, {sx(slot), 1, 2, 3}, 320 + kind, n);
        s3_pair(m, "sub_39EE80", {sx(slot), 0, 0, 0}, 340 + kind, "MT_Msg_Close");
        CHECK(r32(m, slot + kMsgActive) == 0);
        CHECK(r32(m, slot + kMsgHandle) == 0);
        CHECK(v0_of(s3_pair(m, "sub_39EEE0", {sx(slot), 0, 0, 0}, 350 + kind, "MT_Msg_IsOpen (closed)")) == 0);
        CHECK(v0_of(s3_pair(m, "sub_39F710", {sx(slot), 0, 0, 0}, 360 + kind, "MT_Msg_GetMessageCount (closed)")) == 0);
    }
    fresh_worlds();
}

// =====================================================================================================================
// mt_evtCutin.c: "koma_Manager" on the snapshot (kwlnInitMain created it) and the CUTIN COMM handlers
// =====================================================================================================================
TEST_CASE("game(script3): koma_Manager panels and the CUTIN commands") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m)) {
        MESSAGE("SKIP: no dorm snapshot");
        return;
    }
    fresh_worlds();
    for (u32 panel = 0; panel <= 3; ++panel) {
        const Opt o{{{GPR_T0, 4}, {GPR_T1, 5}, {GPR_T2, 6}}};
        const hgp::Run op = s3_pair(m, "sub_396C70", {panel, 100, 200, 3}, 400 + panel, "koma_Open", o);
        const u64 opened = v0_of(op);
        if (panel == 3) CHECK(opened == 0);  // only 3 panels
        if (panel == 0) MESSAGE("koma_Manager in the snapshot: " << std::string(opened ? "yes (panel 0 opened)" : "no"));
        CHECK(v0_of(s3_pair(m, "sub_396ED0", {panel, 0, 0, 0}, 410 + panel, "koma_GetState")) == (opened ? 1u : 0u));
        s3_pair(m, "sub_396E30", {panel, 0, 0, 0}, 420 + panel, "koma_RequestClose");
        s3_pair(m, "sub_396F50", {panel, 0, 0, 0}, 430 + panel, "koma_Close");
        s3_pair(m, "sub_397030", {panel, 0, 0, 0}, 440 + panel, "koma_Destroy");
    }
    s3_pair(m, "sub_3970D0", {0, 0, 0, 0}, 450, "koma_DestroyAll");
    fresh_worlds();
}

// =====================================================================================================================
// mt_evtPMFileReader.c: an "evtPMFileReader" process loading event E010_001 through the file stand-in
// =====================================================================================================================
TEST_CASE("game(script3): evtPMFileReader loads E010_001 (file and heap stand-ins)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m) || read_host("DATA/EVENT/E010/E010_001.PM1").empty()) {
        MESSAGE("SKIP: no dorm snapshot or no extracted EVENT/E010");
        return;
    }
    using namespace s3;
    for (u32 defaults = 0; defaults < 2; ++defaults) {
        REQUIRE(load_snapshot(m));  // a clean file list and kwln lists for each run
        fresh_worlds();
        const hgp::Run c = s3_pair(m, "sub_397EC0", {10, 1, 0, defaults}, 500 + defaults, "mtEvtPMR_Create");
        const u32 task = static_cast<u32>(v0_of(c));
        REQUIRE(task != 0);
        const u32 work = r32(m, task + 0x3C);
        REQUIRE(work != 0);
        CHECK(r32(m, work + kPmrMajor) == 10);
        CHECK(r32(m, work + kPmrMinor) == 1);
        CHECK(r32(m, work + kPmrDefaults) == defaults);
        CHECK(r32(m, work + kPmrState) == 0);
        CHECK(v0_of(s3_pair(m, "sub_398060", {sx(task), 0, 0, 0}, 510, "mtEvtPMR_IsDone (not yet)")) == 0);
        for (u32 frame = 0; frame < 12 && r32(m, work + kPmrState) != 7; ++frame)
            s3_pair(m, "sub_397950", {sx(task), 0, 0, 0}, 520 + frame, "evtPMFileReader update", Opt{{}, {}, true});
        CHECK(r32(m, work + kPmrState) == 7);
        CHECK(r32(m, work + kPmrPm1) != 0);
        CHECK(r32(m, work + kPmrPm2) != 0);
        CHECK(r32(m, work + kPmrPm3) != 0);
        if (defaults == 1) CHECK(r32(m, work + kPmrDefault2) != 0);  // PM2 / PM3 are the built-in blocks
        CHECK(r16(m, work + kPmrEventId) == 7);  // the sub_3BD9A0 stand-in's answer
        // the names it asked the file layer for
        bool pm1 = false;
        for (const StandInCall& call : g_t.world[1]->si.log)
            if (call.va == kHCdvdRequestFn && call.text.find("E010_001.PM1") != std::string::npos) pm1 = true;
        CHECK(pm1);
        CHECK(v0_of(s3_pair(m, "sub_398060", {sx(task), 0, 0, 0}, 540, "mtEvtPMR_IsDone")) == 1);
        CHECK(static_cast<u32>(v0_of(s3_pair(m, "sub_3980E0", {sx(task), 0, 0, 0}, 541, "mtEvtPMR_GetWork"))) == work);
        s3_pair(m, "sub_398140", {sx(task), sx(kRec), sx(kRec + 4), sx(kRec + 8)}, 542, "mtEvtPMR_FindEntry0",
                Opt{{{GPR_T0, sx(kRec + 12)}}});
        CHECK(v0_of(s3_pair(m, "sub_3982D0", {sx(task), 0, 0, 0}, 543, "mtEvtPMR_HasEvent")) == 1);
        s3_pair(m, "sub_397D60", {sx(task), 0, 0, 0}, 544, "evtPMFileReader destroy");
        CHECK(r32(m, work + kPmrCdvd1) == 0);
    }
    fresh_worlds();
}

// =====================================================================================================================
// The event player's helpers on a record the test builds, the effect registry, the paths (documented rules)
// =====================================================================================================================
TEST_CASE("game(script3): event player helpers, effect registry, PM paths, timers (documented rules)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m)) {
        MESSAGE("SKIP: no dorm snapshot");
        return;
    }
    using namespace s3;
    fresh_worlds();
    // the PM file names (sprintf stand-in texts)
    {
        const u32 b = kText;
        const Opt o{{{GPR_T0, sx(b + 0x100)}, {GPR_T1, sx(b + 0x180)}}};
        s3_pair(m, "sub_395000", {123, 4, sx(b), sx(b + 0x80)}, 600, "mtEvtPM_DiscPaths", o);
        CHECK(m.str(b) == "event/e120/E123_004.PM1");
        CHECK(m.str(b + 0x80) == "event/e120/E123_004.PM2");
        CHECK(m.str(b + 0x100) == "event/e120/E123_004.PM3");
        CHECK(m.str(b + 0x180) == "event/e120/E123_004.PAK");
        s3_pair(m, "sub_394E70", {10, 1, sx(b), sx(b + 0x80)}, 601, "mtEvtPM_HostPaths", Opt{{{GPR_T0, sx(b + 0x100)}}});
        CHECK(m.str(b) == "hdd:/persona3_data/event/e010/E010_001.PM1");
        CHECK(m.str(b + 0x100) == "hdd:/persona3_data/event/e010/E010_001.PM3");
    }
    // the event player: cut table (event data +96 -> {u16 count at +2, 140-byte rows at +4}) and the getters
    const u32 ply = kRec, data = kRec + 0x1000, cuts = kRec + 0x1200, rows = kRec + 0x1300;
    std::memset(m.at(ply), 0, 0x1000);
    w32(m, ply + kEvtData, data);
    w32(m, data + kEvtDataCuts, cuts);
    w16(m, cuts + kCutCount, 3);
    w32(m, cuts + kCutRows, rows);
    for (u32 i = 0; i < 3 * kCutRowBytes; ++i) w8(m, rows + i, static_cast<u8>(i * 7 + 1));
    for (u32 cut = 0; cut <= 3; ++cut) {
        s3_pair(m, "sub_397510", {sx(ply), cut, 0, 0}, 610 + cut, "mtEvt_SetCut");
        CHECK(v0_of(s3_pair(m, "sub_397500", {sx(ply), 0, 0, 0}, 615 + cut, "mtEvt_GetCut")) == cut);
        const u32 row = rows + kCutRowBytes * cut;
        const bool valid = cut < 3;
        CHECK(v0_of(s3_pair(m, "sub_397520", {sx(ply), sx(kText), 0, 0}, 620 + cut, "mtEvt_GetCutCount")) == 1);
        CHECK(r32(m, kText) == 3);
        for (u32 i : {0u, 9u, 10u}) {
            const hgp::Run a = s3_pair(m, "sub_397580", {sx(ply), i, sx(kText), 0}, 630 + cut * 16 + i, "mtEvt_GetCutWord");
            CHECK(v0_of(a) == (valid ? 1u : 0u));
            if (valid) CHECK(r16(m, kText) == r16(m, row + 2 * i));
            const hgp::Run b = s3_pair(m, "sub_397630", {sx(ply), i, sx(kText), 0}, 700 + cut * 16 + i, "mtEvt_GetCutByte22");
            CHECK(v0_of(b) == (valid && i < 10 ? 1u : 0u));
            if (valid && i < 10) CHECK(r32(m, kText) == *m.at(row + 22 + i));
            s3_pair(m, "sub_3976F0", {sx(ply), i, sx(kText), sx(kText + 4)}, 770 + cut * 16 + i, "mtEvt_GetCutPair");
            const hgp::Run q = s3_pair(m, "sub_397870", {sx(ply), i, sx(kText), sx(kText + 4)}, 840 + cut * 16 + i, "mtEvt_GetCutQuad",
                                       Opt{{{GPR_T0, sx(kText + 8)}, {GPR_T1, sx(kText + 12)}}});
            if (valid && i < 10) {
                CHECK(v0_of(q) == 1);
                CHECK(r32(m, kText + 12) == r16(m, row + 58 + 8 * i));
            }
        }
        const hgp::Run cam = s3_pair(m, "sub_3977C0", {sx(ply), sx(kText), sx(kText + 4), sx(kText + 8)}, 910 + cut, "mtEvt_GetCutCamera");
        if (valid) {
            CHECK(v0_of(cam) == 1);
            CHECK(r32(m, kText + 4) == r16(m, row + 14));
        }
    }
    s3_pair(m, "sub_393F30", {sx(ply), 77, 0, 0}, 920, "mtEvt_ResetCamera");
    CHECK((r32(m, ply + kEvtFlags) & 0x10000u) != 0);
    CHECK(r32(m, ply + kEvtCamKey) == 0xFFFFFFFFu);
    s3_pair(m, "sub_393E30", {sx(ply), 1, 2, 2}, 921, "mtEvt_StartCut", Opt{{{GPR_T0, 9}, {GPR_T1, 11}}});
    CHECK(r32(m, ply + kEvtCut) == 2);
    CHECK(r32(m, ply + kEvtCutMode) == 9);
    CHECK(r32(m, ply + kEvtCutWord) == 11);
    // the draw requests the 3D draw task consumes
    s3_pair(m, "sub_395550", {sx(ply), 3, 4, 0}, 930, "mtEvt_SetFlash");
    CHECK(r32(m, ply + kEvtFlashOn) == 1);
    s3_pair(m, "sub_395910", {sx(ply), 0, 0, 0}, 931, "mtEvt_RequestRedraw");
    s3_pair(m, "sub_395930", {sx(ply), 5, 6, 0}, 932, "mtEvt_SetLetterbox");
    s3_pair(m, "sub_396250", {sx(ply), 8, 0, 0}, 933, "mtEvt_SetWord1768");
    for (u32 i = 0; i < 3; ++i) w32(m, kText + 4 * i, fbits(1.5f * static_cast<float>(i + 1)));
    s3_pair(m, "sub_396270", {sx(ply), sx(kText), 0, 0}, 934, "mtEvt_SetScreenRect", Opt{{}, {{12, fbits(0.5f)}}});
    CHECK(fval(r32(m, ply + kEvtRectX)) == 1.5f);
    for (u32 i = 0; i < 16; ++i) w32(m, kText + 4 * i, fbits(static_cast<float>(i)));
    s3_pair(m, "sub_3957D0", {sx(ply), sx(kText), 0, 0}, 935, "mtEvt_SetFilterQuad", Opt{{}, {{12, fbits(2.0f)}}});
    CHECK(r32(m, ply + kEvtQuadOn) == 1);
    CHECK(fval(r32(m, ply + kEvtQuad + 60)) == 15.0f);
    s3_pair(m, "sub_395430", {sx(ply), 1, 300, 5}, 936, "mtEvt_SetFade", Opt{{{GPR_T0, 20}}});
    CHECK((r32(m, ply + kEvtFlags) & 0x1000u) != 0);
    for (u32 w = 0; w < 2; ++w) s3_pair(m, "sub_3954E0", {w, 0, 0, 0}, 937 + w, "mtEvt_FadeOut");
    // lerp: $f13 + ($f14 - ...) = to * t + from * (1 - t)
    {
        const hgp::Run r = s3_pair(m, "sub_394040", {1, 0, 0, 0}, 940, "mtEvt_Lerp",
                                   Opt{{}, {{12, fbits(0.25f)}, {13, fbits(8.0f)}, {14, fbits(16.0f)}}});
        CHECK(fval(f0_of(r)) == 10.0f);
        const hgp::Run z = s3_pair(m, "sub_394040", {0, 0, 0, 0}, 941, "mtEvt_Lerp (off)",
                                   Opt{{}, {{12, fbits(0.25f)}, {13, fbits(8.0f)}, {14, fbits(16.0f)}}});
        CHECK(fval(f0_of(z)) == 8.0f);
    }
    // the effect registry: create, two memory entries, load, resources, delete, destroy
    {
        const hgp::Run c = s3_pair(m, "sub_3964C0", {0, 0, 0, 0}, 950, "MT_RegEff_Create");
        const u32 reg = static_cast<u32>(v0_of(c));
        REQUIRE(reg != 0);
        s3_pair(m, "sub_396480", {sx(reg), sx(kBf), 0, 0}, 951, "MT_RegEff_AddMemory");
        s3_pair(m, "sub_396480", {sx(reg), sx(kBf + 0x100), 0, 0}, 952, "MT_RegEff_AddMemory");
        CHECK(r32(m, reg + kRegCount) == 2);
        CHECK(r32(m, reg + kRegEntryBytes + kRegEntData) == kBf + 0x100);
        s3_pair(m, "sub_3965D0", {sx(reg), 0, 0, 0}, 953, "MT_RegEff_StartLoad");
        for (u32 f = 0; f < 4; ++f) s3_pair(m, "sub_3965F0", {sx(reg), 0, 0, 0}, 954 + f, "MT_RegEff_Load");
        CHECK(r32(m, reg + kRegState) == 2);
        CHECK(r32(m, reg + kRegCursor) == 2);
        for (u32 slot : {0u, 15u, 16u}) {
            s3_pair(m, "sub_396760", {sx(reg), slot, 1, 9}, 960 + slot, "MT_RegEff_CreateResource");
            const hgp::Run g = s3_pair(m, "sub_3968A0", {sx(reg), slot, 0, 0}, 980 + slot, "MT_RegEff_GetResource");
            CHECK(v0_of(g) == (slot < 16 ? 0x2345u : 0u));  // the u16 of the sub_3B64C0 stand-in's 0x12345
        }
        s3_pair(m, "sub_396910", {sx(reg), 0, 0, 0}, 1000, "MT_RegEff_Delete");
        CHECK(r16(m, reg + kRegResIds) == 0);
        s3_pair(m, "sub_3969B0", {sx(reg), 0, 0, 0}, 1001, "MT_RegEff_DeleteAll");
        CHECK(r16(m, reg + kRegResIds + 30) == 0);
        s3_pair(m, "sub_396530", {sx(reg), 0, 0, 0}, 1002, "MT_RegEff_Destroy");
    }
    // timers and small rules
    s3_pair(m, "sub_398390", {sx(kText), 2, 0, 0}, 1010, "mtEvt_TimerSet");
    u32 ticks = 0;
    for (u32 i = 0; i < 4; ++i) ticks += v0_of(s3_pair(m, "sub_3983A0", {sx(kText), 0, 0, 0}, 1011 + i, "mtEvt_TimerTick")) ? 1u : 0u;
    CHECK(ticks == 2);  // 0, 0, then done twice
    CHECK(v0_of(s3_pair(m, "sub_39EC60", {5, 0, 0, 0}, 1020, "mtEvtModel_PackResId")) == 915);
    for (u32 link = 0; link < 3; ++link) {
        // sub_172160 / sub_1717C0 are emitted (they run on the snapshot's social-link data): the variant is the same for
        // every kind of one link, 0..2, and the kinds step by 3 inside the link's 12 rows
        u64 variant = 99;
        for (u32 kind = 0; kind < 4; ++kind) {
            const hgp::Run r = s3_pair(m, "sub_3983E0", {kind, link, 0, 0}, 1030 + 4 * link + kind, "mtEvtCustom_MessageIndex");
            const u64 v = v0_of(r) - (5 + 12 * link + 3 * kind);
            CHECK(v <= 2);
            if (kind == 0) variant = v;
            CHECK(v == variant);
        }
    }
    for (u32 n : {0u, 4u, 5u}) s3_pair(m, "sub_39EC10", {sx(ply), n, sx(kText), sx(kText + 4)}, 1040 + n, "mtEvtModel_GetPack");
    // the effect layer's generator (sub_3580B0, emitted): below n; chance 0 never, chance 101 always
    for (u32 i = 0; i < 8; ++i) CHECK(v0_of(s3_pair(m, "sub_395200", {10, 0, 0, 0}, 1050 + i, "MT_Misc_Rand")) < 10);
    CHECK(v0_of(s3_pair(m, "sub_395230", {0, 0, 0, 0}, 1060, "MT_Misc_Chance")) == 0);
    CHECK(v0_of(s3_pair(m, "sub_395230", {101, 0, 0, 0}, 1061, "MT_Misc_Chance")) == 1);
    s3_pair(m, "sub_3952D0", {0, 12, 2, 0}, 1053, "MT_Misc_PlayEventVoice");
    {
        bool voice = false;
        for (const StandInCall& call : g_t.world[1]->si.log)
            if (call.text == "SOUND2/EVENT/EVE_012.ADX") voice = true;
        CHECK(voice);
    }
    s3_pair(m, "sub_3952D0", {0, 0, 2, 0}, 1054, "MT_Misc_PlayEventVoice (stop)");
    s3_pair(m, "sub_395350", {2, 1, 0, 0}, 1055, "MT_Misc_StreamCtl");
    s3_pair(m, "sub_395270", {3, 0, 0, 0}, 1056, "MT_Misc_StopSe");
    fresh_worlds();
}

TEST_CASE("game(script3): pair count") {
    MESSAGE("script3 pairs run (outside the random-world case): " << g_pairs << ", " << g_stops << " ended at an early stop");
    for (const auto& [k, n] : g_stop_names) MESSAGE("  early stop x" << n << ": " << k);
}

#else

TEST_CASE("game(script3): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
