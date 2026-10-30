// Pair tests of the boot slice (game/src/boot/boot.cpp; boot.h has the boot sequence). Every body against its
// recompiled body: on random worlds (the p3fes_handgen skeleton, tests/game/handgen_pairs.h: the whole register file
// and cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the
// bus log), then the set-up tasks frame by frame on the stand-in world with the real files of extracted/ and the
// documented rules of boot.h checked on the host (the "Meaningful pairs" section below).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/boot.h"
#include "p3fes/game/hcdvd.h"
#include "p3fes/game/task.h"
#include "p3fes/game/ui2.h"

#include <cstring>
#include <fstream>
#include <functional>
#include <map>

#include <cstdio>
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
void fn_sub_191D10_00191d10(EEContext&);  // generated body
void fn_sub_191D10_00191d10__recomp(EEContext&);  // recompiled
void fn_sub_191D70_00191d70(EEContext&);  // generated body
void fn_sub_191D70_00191d70__recomp(EEContext&);  // recompiled
void fn_sub_191E60_00191e60(EEContext&);  // generated body
void fn_sub_191E60_00191e60__recomp(EEContext&);  // recompiled
void fn_sub_191EC0_00191ec0(EEContext&);  // generated body
void fn_sub_191EC0_00191ec0__recomp(EEContext&);  // recompiled
void fn_sub_192160_00192160(EEContext&);  // generated body
void fn_sub_192160_00192160__recomp(EEContext&);  // recompiled
void fn_sub_1921D0_001921d0(EEContext&);  // generated body
void fn_sub_1921D0_001921d0__recomp(EEContext&);  // recompiled
void fn_sub_192230_00192230(EEContext&);  // generated body
void fn_sub_192230_00192230__recomp(EEContext&);  // recompiled
void fn_sub_1922A0_001922a0(EEContext&);  // generated body
void fn_sub_1922A0_001922a0__recomp(EEContext&);  // recompiled
void fn_sub_192310_00192310(EEContext&);  // generated body
void fn_sub_192310_00192310__recomp(EEContext&);  // recompiled
void fn_sub_192370_00192370(EEContext&);  // generated body
void fn_sub_192370_00192370__recomp(EEContext&);  // recompiled
void fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0(EEContext&);  // generated body
void fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0__recomp(EEContext&);  // recompiled
void fn_sub_192480_00192480(EEContext&);  // generated body
void fn_sub_192480_00192480__recomp(EEContext&);  // recompiled
void fn_sub_1924D0_001924d0(EEContext&);  // generated body
void fn_sub_1924D0_001924d0__recomp(EEContext&);  // recompiled
void fn_sub_192570_00192570(EEContext&);  // generated body
void fn_sub_192570_00192570__recomp(EEContext&);  // recompiled
void fn_sub_1926A0_001926a0(EEContext&);  // generated body
void fn_sub_1926A0_001926a0__recomp(EEContext&);  // recompiled
void fn_sub_192710_00192710(EEContext&);  // generated body
void fn_sub_192710_00192710__recomp(EEContext&);  // recompiled
void fn_sub_1927B0_001927b0(EEContext&);  // generated body
void fn_sub_1927B0_001927b0__recomp(EEContext&);  // recompiled
void fn_sub_1928A0_001928a0(EEContext&);  // generated body
void fn_sub_1928A0_001928a0__recomp(EEContext&);  // recompiled
void fn_sub_1928D0_001928d0(EEContext&);  // generated body
void fn_sub_1928D0_001928d0__recomp(EEContext&);  // recompiled
void fn_sub_192980_00192980(EEContext&);  // generated body
void fn_sub_192980_00192980__recomp(EEContext&);  // recompiled
void fn_sub_192A70_00192a70(EEContext&);  // generated body
void fn_sub_192A70_00192a70__recomp(EEContext&);  // recompiled
void fn_sub_192AA0_00192aa0(EEContext&);  // generated body
void fn_sub_192AA0_00192aa0__recomp(EEContext&);  // recompiled
void fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50(EEContext&);  // generated body
void fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50__recomp(EEContext&);  // recompiled
void fn_sub_192DB0_00192db0(EEContext&);  // generated body
void fn_sub_192DB0_00192db0__recomp(EEContext&);  // recompiled
void fn_sub_192DE0_00192de0(EEContext&);  // generated body
void fn_sub_192DE0_00192de0__recomp(EEContext&);  // recompiled
void fn_sub_192E70_00192e70(EEContext&);  // generated body
void fn_sub_192E70_00192e70__recomp(EEContext&);  // recompiled
void fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020(EEContext&);  // generated body
void fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020__recomp(EEContext&);  // recompiled
void fn_sub_193320_00193320(EEContext&);  // generated body
void fn_sub_193320_00193320__recomp(EEContext&);  // recompiled
void fn_sub_1933D0_001933d0(EEContext&);  // generated body
void fn_sub_1933D0_001933d0__recomp(EEContext&);  // recompiled
void fn_sub_193460_00193460(EEContext&);  // generated body
void fn_sub_193460_00193460__recomp(EEContext&);  // recompiled
void fn_sub_1938B0_001938b0(EEContext&);  // generated body
void fn_sub_1938B0_001938b0__recomp(EEContext&);  // recompiled
void fn_sub_1938E0_001938e0(EEContext&);  // generated body
void fn_sub_1938E0_001938e0__recomp(EEContext&);  // recompiled
void fn_main_00193980(EEContext&);  // generated body
void fn_main_00193980__recomp(EEContext&);  // recompiled
void fn_initAndLoop_001939b0(EEContext&);  // generated body
void fn_initAndLoop_001939b0__recomp(EEContext&);  // recompiled
void fn_sub_194750_00194750(EEContext&);  // generated body
void fn_sub_194750_00194750__recomp(EEContext&);  // recompiled
void fn_sub_1948B0_001948b0(EEContext&);  // generated body
void fn_sub_1948B0_001948b0__recomp(EEContext&);  // recompiled
void fn_kwlnSetupMainCameraViewport_00195980(EEContext&);  // generated body
void fn_kwlnSetupMainCameraViewport_00195980__recomp(EEContext&);  // recompiled
void fn_kwlnCreateMainCamera_00195c80(EEContext&);  // generated body
void fn_kwlnCreateMainCamera_00195c80__recomp(EEContext&);  // recompiled
void fn_sub_196770_00196770(EEContext&);  // generated body
void fn_sub_196770_00196770__recomp(EEContext&);  // recompiled
void fn_sub_1967D0_001967d0(EEContext&);  // generated body
void fn_sub_1967D0_001967d0__recomp(EEContext&);  // recompiled
void fn_kwlnInitRenderer_00197350(EEContext&);  // generated body
void fn_kwlnInitRenderer_00197350__recomp(EEContext&);  // recompiled
void fn_sub_197F80_00197f80(EEContext&);  // generated body
void fn_sub_197F80_00197f80__recomp(EEContext&);  // recompiled
void fn_sub_198540_00198540(EEContext&);  // generated body
void fn_sub_198540_00198540__recomp(EEContext&);  // recompiled
void fn_sub_198560_00198560(EEContext&);  // generated body
void fn_sub_198560_00198560__recomp(EEContext&);  // recompiled
void fn_sub_198570_00198570(EEContext&);  // generated body
void fn_sub_198570_00198570__recomp(EEContext&);  // recompiled
void fn_sub_198580_00198580(EEContext&);  // generated body
void fn_sub_198580_00198580__recomp(EEContext&);  // recompiled
void fn_sub_198590_00198590(EEContext&);  // generated body
void fn_sub_198590_00198590__recomp(EEContext&);  // recompiled
void fn_sub_1985A0_001985a0(EEContext&);  // generated body
void fn_sub_1985A0_001985a0__recomp(EEContext&);  // recompiled
void fn_sub_1985B0_001985b0(EEContext&);  // generated body
void fn_sub_1985B0_001985b0__recomp(EEContext&);  // recompiled
void fn_sub_1985D0_001985d0(EEContext&);  // generated body
void fn_sub_1985D0_001985d0__recomp(EEContext&);  // recompiled
void fn_sub_1985E0_001985e0(EEContext&);  // generated body
void fn_sub_1985E0_001985e0__recomp(EEContext&);  // recompiled
void fn_kwlnRootUpdateTask_00198650(EEContext&);  // generated body
void fn_kwlnRootUpdateTask_00198650__recomp(EEContext&);  // recompiled
void fn_sub_1988F0_001988f0(EEContext&);  // generated body
void fn_sub_1988F0_001988f0__recomp(EEContext&);  // recompiled
void fn_kwlnRootCreateTask_00198940(EEContext&);  // generated body
void fn_kwlnRootCreateTask_00198940__recomp(EEContext&);  // recompiled
void fn_kwlnRootUpdate2DDrawPreEndTask_00198b10(EEContext&);  // generated body
void fn_kwlnRootUpdate2DDrawPreEndTask_00198b10__recomp(EEContext&);  // recompiled
void fn_sub_198B50_00198b50(EEContext&);  // generated body
void fn_sub_198B50_00198b50__recomp(EEContext&);  // recompiled
void fn_sub_198B90_00198b90(EEContext&);  // generated body
void fn_sub_198B90_00198b90__recomp(EEContext&);  // recompiled
void fn_sub_198BD0_00198bd0(EEContext&);  // generated body
void fn_sub_198BD0_00198bd0__recomp(EEContext&);  // recompiled
void fn_sub_198DD0_00198dd0(EEContext&);  // generated body
void fn_sub_198DD0_00198dd0__recomp(EEContext&);  // recompiled
void fn_sub_198E10_00198e10(EEContext&);  // generated body
void fn_sub_198E10_00198e10__recomp(EEContext&);  // recompiled
void fn_sub_198E50_00198e50(EEContext&);  // generated body
void fn_sub_198E50_00198e50__recomp(EEContext&);  // recompiled
void fn_kwlnRootUpdateEtcDrawTask_00198f90(EEContext&);  // generated body
void fn_kwlnRootUpdateEtcDrawTask_00198f90__recomp(EEContext&);  // recompiled
void fn_sub_199080_00199080(EEContext&);  // generated body
void fn_sub_199080_00199080__recomp(EEContext&);  // recompiled
void fn_sub_1990C0_001990c0(EEContext&);  // generated body
void fn_sub_1990C0_001990c0__recomp(EEContext&);  // recompiled
void fn_sub_199100_00199100(EEContext&);  // generated body
void fn_sub_199100_00199100__recomp(EEContext&);  // recompiled
void fn_kwlnRootCreateShowRasterTask_00199360(EEContext&);  // generated body
void fn_kwlnRootCreateShowRasterTask_00199360__recomp(EEContext&);  // recompiled
void fn_kwlnRootUpdateDrawBustupProcTask_001993a0(EEContext&);  // generated body
void fn_kwlnRootUpdateDrawBustupProcTask_001993a0__recomp(EEContext&);  // recompiled
void fn_sub_1993D0_001993d0(EEContext&);  // generated body
void fn_sub_1993D0_001993d0__recomp(EEContext&);  // recompiled
void fn_sub_199410_00199410(EEContext&);  // generated body
void fn_sub_199410_00199410__recomp(EEContext&);  // recompiled
void fn_sub_199440_00199440(EEContext&);  // generated body
void fn_sub_199440_00199440__recomp(EEContext&);  // recompiled
void fn_sub_1996C0_001996c0(EEContext&);  // generated body
void fn_sub_1996C0_001996c0__recomp(EEContext&);  // recompiled
void fn_sub_199700_00199700(EEContext&);  // generated body
void fn_sub_199700_00199700__recomp(EEContext&);  // recompiled
void fn_sub_1997A0_001997a0(EEContext&);  // generated body
void fn_sub_1997A0_001997a0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_191D10", 0x191D10, &recomp_gen::fn_sub_191D10_00191d10, &recomp_gen::fn_sub_191D10_00191d10__recomp},
    {"sub_191D70", 0x191D70, &recomp_gen::fn_sub_191D70_00191d70, &recomp_gen::fn_sub_191D70_00191d70__recomp},
    {"sub_191E60", 0x191E60, &recomp_gen::fn_sub_191E60_00191e60, &recomp_gen::fn_sub_191E60_00191e60__recomp},
    {"sub_191EC0", 0x191EC0, &recomp_gen::fn_sub_191EC0_00191ec0, &recomp_gen::fn_sub_191EC0_00191ec0__recomp},
    {"sub_192160", 0x192160, &recomp_gen::fn_sub_192160_00192160, &recomp_gen::fn_sub_192160_00192160__recomp},
    {"sub_1921D0", 0x1921D0, &recomp_gen::fn_sub_1921D0_001921d0, &recomp_gen::fn_sub_1921D0_001921d0__recomp},
    {"sub_192230", 0x192230, &recomp_gen::fn_sub_192230_00192230, &recomp_gen::fn_sub_192230_00192230__recomp},
    {"sub_1922A0", 0x1922A0, &recomp_gen::fn_sub_1922A0_001922a0, &recomp_gen::fn_sub_1922A0_001922a0__recomp},
    {"sub_192310", 0x192310, &recomp_gen::fn_sub_192310_00192310, &recomp_gen::fn_sub_192310_00192310__recomp},
    {"sub_192370", 0x192370, &recomp_gen::fn_sub_192370_00192370, &recomp_gen::fn_sub_192370_00192370__recomp},
    {"H_FileSetup_UpdateHonpenItemTblDataReadTask", 0x1923B0, &recomp_gen::fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0, &recomp_gen::fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0__recomp},
    {"sub_192480", 0x192480, &recomp_gen::fn_sub_192480_00192480, &recomp_gen::fn_sub_192480_00192480__recomp},
    {"sub_1924D0", 0x1924D0, &recomp_gen::fn_sub_1924D0_001924d0, &recomp_gen::fn_sub_1924D0_001924d0__recomp},
    {"sub_192570", 0x192570, &recomp_gen::fn_sub_192570_00192570, &recomp_gen::fn_sub_192570_00192570__recomp},
    {"sub_1926A0", 0x1926A0, &recomp_gen::fn_sub_1926A0_001926a0, &recomp_gen::fn_sub_1926A0_001926a0__recomp},
    {"sub_192710", 0x192710, &recomp_gen::fn_sub_192710_00192710, &recomp_gen::fn_sub_192710_00192710__recomp},
    {"sub_1927B0", 0x1927B0, &recomp_gen::fn_sub_1927B0_001927b0, &recomp_gen::fn_sub_1927B0_001927b0__recomp},
    {"sub_1928A0", 0x1928A0, &recomp_gen::fn_sub_1928A0_001928a0, &recomp_gen::fn_sub_1928A0_001928a0__recomp},
    {"sub_1928D0", 0x1928D0, &recomp_gen::fn_sub_1928D0_001928d0, &recomp_gen::fn_sub_1928D0_001928d0__recomp},
    {"sub_192980", 0x192980, &recomp_gen::fn_sub_192980_00192980, &recomp_gen::fn_sub_192980_00192980__recomp},
    {"sub_192A70", 0x192A70, &recomp_gen::fn_sub_192A70_00192a70, &recomp_gen::fn_sub_192A70_00192a70__recomp},
    {"sub_192AA0", 0x192AA0, &recomp_gen::fn_sub_192AA0_00192aa0, &recomp_gen::fn_sub_192AA0_00192aa0__recomp},
    {"H_FileSetup_UpdateChoiceDataFileSetupTask", 0x192B50, &recomp_gen::fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50, &recomp_gen::fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50__recomp},
    {"sub_192DB0", 0x192DB0, &recomp_gen::fn_sub_192DB0_00192db0, &recomp_gen::fn_sub_192DB0_00192db0__recomp},
    {"sub_192DE0", 0x192DE0, &recomp_gen::fn_sub_192DE0_00192de0, &recomp_gen::fn_sub_192DE0_00192de0__recomp},
    {"sub_192E70", 0x192E70, &recomp_gen::fn_sub_192E70_00192e70, &recomp_gen::fn_sub_192E70_00192e70__recomp},
    {"H_FileSetup_UpdateHikitugiDataProcTask", 0x193020, &recomp_gen::fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020, &recomp_gen::fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020__recomp},
    {"sub_193320", 0x193320, &recomp_gen::fn_sub_193320_00193320, &recomp_gen::fn_sub_193320_00193320__recomp},
    {"sub_1933D0", 0x1933D0, &recomp_gen::fn_sub_1933D0_001933d0, &recomp_gen::fn_sub_1933D0_001933d0__recomp},
    {"sub_193460", 0x193460, &recomp_gen::fn_sub_193460_00193460, &recomp_gen::fn_sub_193460_00193460__recomp},
    {"sub_1938B0", 0x1938B0, &recomp_gen::fn_sub_1938B0_001938b0, &recomp_gen::fn_sub_1938B0_001938b0__recomp},
    {"sub_1938E0", 0x1938E0, &recomp_gen::fn_sub_1938E0_001938e0, &recomp_gen::fn_sub_1938E0_001938e0__recomp},
    {"main", 0x193980, &recomp_gen::fn_main_00193980, &recomp_gen::fn_main_00193980__recomp},
    {"initAndLoop", 0x1939B0, &recomp_gen::fn_initAndLoop_001939b0, &recomp_gen::fn_initAndLoop_001939b0__recomp},
    {"sub_194750", 0x194750, &recomp_gen::fn_sub_194750_00194750, &recomp_gen::fn_sub_194750_00194750__recomp},
    {"sub_1948B0", 0x1948B0, &recomp_gen::fn_sub_1948B0_001948b0, &recomp_gen::fn_sub_1948B0_001948b0__recomp},
    {"kwlnSetupMainCameraViewport", 0x195980, &recomp_gen::fn_kwlnSetupMainCameraViewport_00195980, &recomp_gen::fn_kwlnSetupMainCameraViewport_00195980__recomp},
    {"kwlnCreateMainCamera", 0x195C80, &recomp_gen::fn_kwlnCreateMainCamera_00195c80, &recomp_gen::fn_kwlnCreateMainCamera_00195c80__recomp},
    {"sub_196770", 0x196770, &recomp_gen::fn_sub_196770_00196770, &recomp_gen::fn_sub_196770_00196770__recomp},
    {"sub_1967D0", 0x1967D0, &recomp_gen::fn_sub_1967D0_001967d0, &recomp_gen::fn_sub_1967D0_001967d0__recomp},
    {"kwlnInitRenderer", 0x197350, &recomp_gen::fn_kwlnInitRenderer_00197350, &recomp_gen::fn_kwlnInitRenderer_00197350__recomp},
    {"sub_197F80", 0x197F80, &recomp_gen::fn_sub_197F80_00197f80, &recomp_gen::fn_sub_197F80_00197f80__recomp},
    {"sub_198540", 0x198540, &recomp_gen::fn_sub_198540_00198540, &recomp_gen::fn_sub_198540_00198540__recomp},
    {"sub_198560", 0x198560, &recomp_gen::fn_sub_198560_00198560, &recomp_gen::fn_sub_198560_00198560__recomp},
    {"sub_198570", 0x198570, &recomp_gen::fn_sub_198570_00198570, &recomp_gen::fn_sub_198570_00198570__recomp},
    {"sub_198580", 0x198580, &recomp_gen::fn_sub_198580_00198580, &recomp_gen::fn_sub_198580_00198580__recomp},
    {"sub_198590", 0x198590, &recomp_gen::fn_sub_198590_00198590, &recomp_gen::fn_sub_198590_00198590__recomp},
    {"sub_1985A0", 0x1985A0, &recomp_gen::fn_sub_1985A0_001985a0, &recomp_gen::fn_sub_1985A0_001985a0__recomp},
    {"sub_1985B0", 0x1985B0, &recomp_gen::fn_sub_1985B0_001985b0, &recomp_gen::fn_sub_1985B0_001985b0__recomp},
    {"sub_1985D0", 0x1985D0, &recomp_gen::fn_sub_1985D0_001985d0, &recomp_gen::fn_sub_1985D0_001985d0__recomp},
    {"sub_1985E0", 0x1985E0, &recomp_gen::fn_sub_1985E0_001985e0, &recomp_gen::fn_sub_1985E0_001985e0__recomp},
    {"kwlnRootUpdateTask", 0x198650, &recomp_gen::fn_kwlnRootUpdateTask_00198650, &recomp_gen::fn_kwlnRootUpdateTask_00198650__recomp},
    {"sub_1988F0", 0x1988F0, &recomp_gen::fn_sub_1988F0_001988f0, &recomp_gen::fn_sub_1988F0_001988f0__recomp},
    {"kwlnRootCreateTask", 0x198940, &recomp_gen::fn_kwlnRootCreateTask_00198940, &recomp_gen::fn_kwlnRootCreateTask_00198940__recomp},
    {"kwlnRootUpdate2DDrawPreEndTask", 0x198B10, &recomp_gen::fn_kwlnRootUpdate2DDrawPreEndTask_00198b10, &recomp_gen::fn_kwlnRootUpdate2DDrawPreEndTask_00198b10__recomp},
    {"sub_198B50", 0x198B50, &recomp_gen::fn_sub_198B50_00198b50, &recomp_gen::fn_sub_198B50_00198b50__recomp},
    {"sub_198B90", 0x198B90, &recomp_gen::fn_sub_198B90_00198b90, &recomp_gen::fn_sub_198B90_00198b90__recomp},
    {"sub_198BD0", 0x198BD0, &recomp_gen::fn_sub_198BD0_00198bd0, &recomp_gen::fn_sub_198BD0_00198bd0__recomp},
    {"sub_198DD0", 0x198DD0, &recomp_gen::fn_sub_198DD0_00198dd0, &recomp_gen::fn_sub_198DD0_00198dd0__recomp},
    {"sub_198E10", 0x198E10, &recomp_gen::fn_sub_198E10_00198e10, &recomp_gen::fn_sub_198E10_00198e10__recomp},
    {"sub_198E50", 0x198E50, &recomp_gen::fn_sub_198E50_00198e50, &recomp_gen::fn_sub_198E50_00198e50__recomp},
    {"kwlnRootUpdateEtcDrawTask", 0x198F90, &recomp_gen::fn_kwlnRootUpdateEtcDrawTask_00198f90, &recomp_gen::fn_kwlnRootUpdateEtcDrawTask_00198f90__recomp},
    {"sub_199080", 0x199080, &recomp_gen::fn_sub_199080_00199080, &recomp_gen::fn_sub_199080_00199080__recomp},
    {"sub_1990C0", 0x1990C0, &recomp_gen::fn_sub_1990C0_001990c0, &recomp_gen::fn_sub_1990C0_001990c0__recomp},
    {"sub_199100", 0x199100, &recomp_gen::fn_sub_199100_00199100, &recomp_gen::fn_sub_199100_00199100__recomp},
    {"kwlnRootCreateShowRasterTask", 0x199360, &recomp_gen::fn_kwlnRootCreateShowRasterTask_00199360, &recomp_gen::fn_kwlnRootCreateShowRasterTask_00199360__recomp},
    {"kwlnRootUpdateDrawBustupProcTask", 0x1993A0, &recomp_gen::fn_kwlnRootUpdateDrawBustupProcTask_001993a0, &recomp_gen::fn_kwlnRootUpdateDrawBustupProcTask_001993a0__recomp},
    {"sub_1993D0", 0x1993D0, &recomp_gen::fn_sub_1993D0_001993d0, &recomp_gen::fn_sub_1993D0_001993d0__recomp},
    {"sub_199410", 0x199410, &recomp_gen::fn_sub_199410_00199410, &recomp_gen::fn_sub_199410_00199410__recomp},
    {"sub_199440", 0x199440, &recomp_gen::fn_sub_199440_00199440, &recomp_gen::fn_sub_199440_00199440__recomp},
    {"sub_1996C0", 0x1996C0, &recomp_gen::fn_sub_1996C0_001996c0, &recomp_gen::fn_sub_1996C0_001996c0__recomp},
    {"sub_199700", 0x199700, &recomp_gen::fn_sub_199700_00199700, &recomp_gen::fn_sub_199700_00199700__recomp},
    {"sub_1997A0", 0x1997A0, &recomp_gen::fn_sub_1997A0_001997a0, &recomp_gen::fn_sub_1997A0_001997a0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(boot): every body equals its recompiled body on random worlds") {
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
// Meaningful pairs: the boot's set-up tasks run frame by frame on the stand-in world (tests/game/stand_ins.h: the heap
// behind RwCalloc / H_Malloc, the H_Cdvd layer over extracted/), each frame a pair (hand vs recompiled, whole RAM, the
// register file at every check point, the dead stack, the stand-ins' logs); the machine carries the recompiled run's
// state into the next frame, the heap's live blocks are carried into the next frame's worlds, and between frames the
// host does what kwlnUpdate's H_Cdvd_Update would (loads a requested file into its node). On top: the documented rules
// of boot.h -- which files each scenario loads, in which order, where they land, the item table's sections, the
// set-up step tables, the scenario prompt, the carry-over flags, the root task's draw passes and priorities.
// =====================================================================================================================

namespace {

namespace rg = p3fes::recomp_gen;
namespace boot = p3fes::game::boot;
using p3fes::game::kwln::kOffChild;
using p3fes::game::kwln::kOffName;
using p3fes::game::kwln::kOffParent;
using p3fes::game::kwln::kOffPriority;
using p3fes::game::kwln::kOffSibling;
using p3fes::game::kwln::kOffState;
using p3fes::game::kwln::kOffWork;

Machine* si_machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        write_rw_slots(*mm);
        return mm;
    }();
    return m;
}

u32 g32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 g16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void p32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void p16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }

HwCheck whole_ram() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// A clean file layer and kwln kernel: no requests, an empty cache, empty task lists (as at boot).
void clean_world(Machine& m) {
    std::memset(m.at(game::kHCdvdListHead), 0, 16 + 256);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * game::kHCdvdCacheSlots);
    std::memset(m.at(0x7CE064u), 0, 0x7CE088u - 0x7CE064u);  // the starting / ending / running lists
}

// The parent task of the set-up tasks: a zeroed 0x68-byte record whose work block follows it.
constexpr u32 kParent = 0x01B80000u;
constexpr u32 kParentWork = kParent + 0x100u;
void make_parent(Machine& m, u32 work_bytes = 0x100) {
    std::memset(m.at(kParent), 0, 0x100 + work_bytes);
    p32(m, kParent + kOffWork, kParentWork);
    p32(m, kParent + kOffState, 2);  // running
}

// The heap's live blocks of the last frame, reserved in every world of the next one; `extra` runs after.
using Live = std::map<u32, u32>;
WorldSetup carry(const Live& live, std::function<void(StandInWorld&)> extra = {}) {
    return [live, extra](StandInWorld& w) {
        install_standard(w);
        for (const auto& [p, n] : live) w.heap.reserve(p, n);
        if (extra) extra(w);
    };
}
Live merge(Live a, const Live& b) {
    for (const auto& kv : b) a.insert(kv);
    return a;
}

// What H_Cdvd_Update does for a state-0 node (stand_ins.cpp FakeCd::load_node, without the cache registration): the
// whole file into a 64-byte-aligned buffer at `raw`, the node's data / size words, state 4. Returns the bytes ("" =
// not under extracted/).
std::vector<u8> host_load(Machine& m, u32 node, u32 raw) {
    GuestHeap scratch;
    FakeCd cd{scratch};
    const std::string hp = cd.host_path(m.str(node + 16, 256));
    if (hp.empty()) return {};
    std::ifstream f(hp, std::ios::binary);
    std::vector<u8> bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    const u32 data = (raw + 63u) & ~63u;
    std::memcpy(m.at(data), bytes.data(), bytes.size());
    p32(m, node + 276, raw);
    p32(m, node + 272, data);
    p32(m, node + 292, static_cast<u32>(bytes.size()));
    p32(m, node + 280, static_cast<u32>(bytes.size()));
    p32(m, node + 12, game::kHCdvdStateLoaded);
    return bytes;
}
u32 round16(u32 n) { return (n + 15u) & ~15u; }

// datItemTblSetSections restated on the host (ui2.h): each section's first record and the 35 tail records.
void check_item_sections(Machine& m) {
    using namespace game::ui2;
    u32 p = kItemTbl;
    for (u32 s = 0; s < kItemTblSections; ++s) {
        const u32 count = g32(m, p);
        CHECK(g32(m, kItemTblSectionSlot[s]) == p + 16u);
        p = p + 16u + count * kItemTblRecordSize[s];
    }
    for (u32 i = 0; i < kItemTblTailCount; ++i) CHECK(g32(m, kItemTblTail + 4u * i) == p + 16u + 32u * i);
}

std::string task_name(Machine& m, u32 task) { return m.str(task + kOffName, 24); }
void set_task_state(Machine& m, u32 task, u32 state) {
    p32(m, task + kOffState, (g32(m, task + kOffState) & ~0xFu) | state);
}

struct FrameResult {
    SiPair p;
    u32 v0;
};
FrameResult frame(Machine& m, Fn hand, Fn recomp, u32 a0, u32 seed, const char* what, const WorldSetup& setup) {
    FrameResult r{run_pair_si(m, hand, recomp, {sx(a0), 0, 0, 0}, seed, what, whole_ram(), setup), 0};
    r.v0 = static_cast<u32>(r.p.hw.recomp.base.v0);
    return r;
}

}  // namespace

TEST_CASE("game(boot): the item-table reads load their files, frame by frame, through the fake file layer") {
    Machine* mp = si_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    struct Scenario {
        const char* name;
        Fn hand, recomp;
        std::vector<std::pair<const char*, u32>> files;  // path, destination
    };
    const Scenario scenarios[] = {
        {"HonpenItemTblDataRead", rg::fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0,
         rg::fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0__recomp, {{"event/itemtbl.bin", boot::kItemTbl}}},
        {"GojitudanItemTblDataRead", rg::fn_sub_192570_00192570, rg::fn_sub_192570_00192570__recomp,
         {{"event/AEGIS_itemtbl.bin", boot::kItemTbl}, {"event/AEGIS_seq.bin", boot::kAegisSeq}}},
    };
    int pairs = 0, loaded = 0;
    for (const Scenario& sc : scenarios) {
        clean_world(m);
        make_parent(m);
        std::memset(m.at(boot::kAegisSeq), 0, 0x1000);
        std::memset(m.at(boot::kItemTbl), 0, 0x8000);
        std::memset(m.at(kParentWork), 0, 12);
        // frame 1: step 0 requests the file(s) (plain files, not archives) and moves to step 1
        FrameResult f1 = frame(m, sc.hand, sc.recomp, kParent, 11, sc.name, carry({}));
        ++pairs;
        CHECK(f1.v0 == 0);
        CHECK(g32(m, kParentWork) == 1);
        const StandIns& si = f1.p.recomp->si;
        REQUIRE(si.calls_to(kHCdvdRequestFn) == sc.files.size());
        std::vector<u32> nodes;
        for (std::size_t k = 0; k < sc.files.size(); ++k) {
            CHECK(si.log[k].va == kHCdvdRequestFn);
            CHECK(si.log[k].text == FakeCd::build_path(sc.files[k].first));
            CHECK(si.log[k].args[1] == 0);
            nodes.push_back(static_cast<u32>(si.log[k].v0));
            CHECK(g32(m, kParentWork + 4u + 4u * static_cast<u32>(k)) == nodes.back());
        }
        Live live = f1.p.recomp->heap.live();
        // frame 2: nothing read yet -- still step 1, returns 0
        FrameResult f2 = frame(m, sc.hand, sc.recomp, kParent, 12, sc.name, carry(live));
        ++pairs;
        CHECK(f2.v0 == 0);
        CHECK(g32(m, kParentWork) == 1);
        // the reads complete (one H_Cdvd_Update each)
        std::vector<std::vector<u8>> bytes;
        u32 raw = kStandInHeap + 0x100000u;
        bool all = true;
        for (u32 node : nodes) {
            bytes.push_back(host_load(m, node, raw));
            if (bytes.back().empty()) {
                all = false;
                break;
            }
            live[raw] = round16(static_cast<u32>(bytes.back().size()) + 64u);
            raw += round16(static_cast<u32>(bytes.back().size()) + 128u);
        }
        if (!all) {
            MESSAGE(std::string(sc.name) << ": the file is not under extracted/: the read part skipped");
            continue;
        }
        // frame 3: copied whole to their tables, the nodes destroyed, the section pointers set; the task ends
        FrameResult f3 = frame(m, sc.hand, sc.recomp, kParent, 13, sc.name, carry(live));
        ++pairs;
        ++loaded;
        CHECK(f3.v0 == 0xFFFFFFFFu);
        for (std::size_t k = 0; k < sc.files.size(); ++k) {
            CHECK(g32(m, kParentWork + 4u + 4u * static_cast<u32>(k)) == 0);
            CHECK(std::memcmp(m.at(sc.files[k].second), bytes[k].data(), bytes[k].size()) == 0);
        }
        const StandIns& s3 = f3.p.recomp->si;
        REQUIRE(s3.calls_to(kHCdvdDestroyFn) == nodes.size());
        std::size_t d = 0;
        for (const StandInCall& c : s3.log)
            if (c.va == kHCdvdDestroyFn) CHECK(static_cast<u32>(c.args[0]) == nodes[d++]);
        check_item_sections(m);
        // the documented layout: AEGIS_seq.bin ends where the item table begins (4,096 bytes before it)
        if (sc.files.size() == 2) CHECK(bytes[1].size() <= boot::kItemTbl - boot::kAegisSeq);
        std::string what = std::string(sc.name) + ": " + std::to_string(bytes[0].size()) + " bytes to 0x83BB30";
        if (sc.files.size() == 2) what += ", AEGIS_seq.bin " + std::to_string(bytes[1].size()) + " bytes to 0x83AB30";
        MESSAGE(what);
        // the destroy callback with nothing held: only RwFree(work)
        std::memset(m.at(kParentWork + 4), 0, 8);
    }
    MESSAGE("item-table reads: " << pairs << " frame pairs, " << loaded << " scenarios read from extracted/");
}

TEST_CASE("game(boot): the scenario file set-ups run their three loaders in the documented order") {
    Machine* mp = si_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    // the step tables in the ELF: boot.h kFileSetupStepsJourney / kFileSetupStepsAnswer
    const u32 journey[4] = {0x1924D0u, 0x27E270u, 0x1B8030u, 0};
    const u32 answer[4] = {0x192710u, 0x27E2C0u, 0x1B80C0u, 0};
    for (u32 k = 0; k < 4; ++k) {
        CHECK(g32(m, boot::kFileSetupStepsJourney + 4u * k) == journey[k]);
        CHECK(g32(m, boot::kFileSetupStepsAnswer + 4u * k) == answer[k]);
    }
    struct Runner {
        const char* name;
        Fn hand, recomp;
        const char* first;  // the item-table read's task name
    };
    const Runner runners[] = {
        {"HonpenFileSetup", rg::fn_sub_1927B0_001927b0, rg::fn_sub_1927B0_001927b0__recomp, "HonpenItemTblDataRead"},
        {"GojitudanFileSetup", rg::fn_sub_192980_00192980, rg::fn_sub_192980_00192980__recomp, "GojitudanItemTblDataRead"},
    };
    int pairs = 0;
    for (const Runner& r : runners) {
        clean_world(m);
        make_parent(m);
        std::memset(m.at(kParentWork), 0, 12);
        Live live;
        const char* expected[3] = {r.first, "btlTableReload", "read startup data"};
        for (u32 step = 0; step < 3; ++step) {
            // phase 0: the step's creator runs with the set-up task as the parent
            FrameResult c = frame(m, r.hand, r.recomp, kParent, 21 + step, r.name, carry(live));
            ++pairs;
            CHECK(c.v0 == 0);
            CHECK(g32(m, kParentWork) == 1);
            CHECK(g32(m, kParentWork + 4) == step);
            const u32 sub = g32(m, kParentWork + 8);
            REQUIRE(sub != 0);
            CHECK(task_name(m, sub) == std::string(expected[step]).substr(0, 23));  // names are cut at 23 characters
            CHECK(g32(m, sub + kOffParent) == kParent);
            live = merge(live, c.p.recomp->heap.live());
            // phase 1 while the step's task runs: nothing moves
            FrameResult w = frame(m, r.hand, r.recomp, kParent, 31 + step, r.name, carry(live));
            ++pairs;
            CHECK(w.v0 == 0);
            CHECK(g32(m, kParentWork) == 1);
            // it ends (state 3): the next step
            set_task_state(m, sub, 3);
            FrameResult e = frame(m, r.hand, r.recomp, kParent, 41 + step, r.name, carry(live));
            ++pairs;
            CHECK(e.v0 == 0);
            CHECK(g32(m, kParentWork) == 0);
            CHECK(g32(m, kParentWork + 4) == step + 1);
        }
        // phase 0 at the table's 0: the set-up is done
        FrameResult done = frame(m, r.hand, r.recomp, kParent, 51, r.name, carry(live));
        ++pairs;
        CHECK(done.v0 == 0xFFFFFFFFu);
    }
    MESSAGE("file set-up runners: " << pairs << " frame pairs");
}

TEST_CASE("game(boot): the scenario prompt toggles, draws the choice's name and starts its set-up") {
    Machine* mp = si_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    const Fn hand = rg::fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50;
    const Fn recomp = rg::fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50__recomp;
    // the names the prompt shows (boot.h kChoiceNames)
    CHECK(m.str(g32(m, boot::kChoiceNames)) == "HONPEN");
    CHECK(m.str(g32(m, boot::kChoiceNames + 4)) == "GOJITUDAN");
    constexpr u32 kPadHeld = 0x7E094Eu, kPadNew = 0x7E0952u;
    // sub_104D10 (the debug printer) is not stood in: it runs and its output is read from its character grid
    constexpr u32 kDebugGrid = 0x7E1E30u, kDebugCols = 53, kDebugRows = 40;
    const auto printer = [](StandInWorld&) {};
    int pairs = 0;
    for (u32 pick = 0; pick < 2; ++pick) {
        clean_world(m);
        make_parent(m);
        std::memset(m.at(kParentWork), 0, 12);
        p16(m, kPadHeld, 0);
        p16(m, kPadNew, 0);
        FrameResult s0 = frame(m, hand, recomp, kParent, 61, "ChoiceDataFileSetup", carry({}, printer));
        ++pairs;
        CHECK(s0.v0 == 0);
        CHECK(g32(m, kParentWork) == 1);
        // up, down, up, nothing: the choice toggles on each newly pressed up / down; the name drawn follows it
        const u16 presses[] = {0x1000, 0x4000, 0x1000, 0x0000, 0x1000};
        u32 choice = 0;
        u32 seed = 70;
        for (u16 bits : presses) {
            if (choice == pick && bits != 0) continue;  // stop toggling once on the wanted one
            p16(m, kPadNew, bits);
            std::memset(m.at(kDebugGrid), 0, kDebugCols * kDebugRows);
            FrameResult f = frame(m, hand, recomp, kParent, seed++, "ChoiceDataFileSetup", carry({}, printer));
            ++pairs;
            if (bits) choice ^= 1u;
            CHECK(g32(m, kParentWork + 4) == choice);
            // sub_104D10 (the debug printer, hand-written since slice unblock: it runs) printed the choice's name once,
            // printf("%s", name) at column 4, row 4 of the 53 x 40 character grid 0x7E1E30; nothing else on the grid
            const std::string name = m.str(g32(m, boot::kChoiceNames + 4u * choice));
            REQUIRE(!name.empty());
            CHECK(std::memcmp(m.at(kDebugGrid + kDebugCols * 4 + 4), name.data(), name.size()) == 0);
            u32 other = 0;
            for (u32 k = 0; k < kDebugCols * kDebugRows; ++k)
                if (k < kDebugCols * 4 + 4 || k >= kDebugCols * 4 + 4 + name.size()) other += m.at(kDebugGrid + k)[0] != 0;
            CHECK(other == 0u);
            CHECK(f.p.recomp->si.calls_to(kVsprintf) == 1);  // the printer formats through vsprintf once
        }
        REQUIRE(choice == pick);
        // confirm: the scenario's set-up task (parent 0) and the scenario word
        p16(m, kPadNew, 0);
        p16(m, kPadHeld, 0x40);
        FrameResult c = frame(m, hand, recomp, kParent, 90 + pick, "ChoiceDataFileSetup", carry({}, printer));
        ++pairs;
        p16(m, kPadHeld, 0);
        CHECK(g32(m, kParentWork) == 2);
        const u32 sub = g32(m, kParentWork + 8);
        REQUIRE(sub != 0);
        CHECK(task_name(m, sub) == (pick ? "GojitudanFileSetup" : "HonpenFileSetup"));
        CHECK(g32(m, kGp - 19788u) == pick);  // the scenario word sub_17D800 reads
        const Live live = c.p.recomp->heap.live();
        // step 2: running -> 0; ended -> -1
        FrameResult w = frame(m, hand, recomp, kParent, 95, "ChoiceDataFileSetup", carry(live, printer));
        ++pairs;
        CHECK(w.v0 == 0);
        set_task_state(m, sub, 3);
        FrameResult e = frame(m, hand, recomp, kParent, 96, "ChoiceDataFileSetup", carry(live, printer));
        ++pairs;
        CHECK(e.v0 == 0xFFFFFFFFu);
    }
    MESSAGE("scenario prompt: " << pairs << " frame pairs");
}

TEST_CASE("game(boot): the carry-over step applies a loaded Persona 3 save and frees its buffers") {
    Machine* mp = si_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    const Fn hand = rg::fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020;
    const Fn recomp = rg::fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020__recomp;
    // the flag list (boot.h kHikitugiFlagList): 39 ids, 0-terminated
    std::vector<u32> flags;
    for (u32 k = 0; k < 64; ++k) {
        const u32 f = g32(m, boot::kHikitugiFlagList + 4u * k);
        if (!f) break;
        flags.push_back(f);
    }
    CHECK(flags.size() == 39);
    constexpr u32 kFlagWords = 0x83A21Cu;  // datGetFlag's bit array (flag f: word f >> 5, bit f & 31)
    const u32 sizes[4] = {80, 13312, 704, 44};
    std::mt19937 rng{0xB007};
    int pairs = 0;
    for (int loaded = 0; loaded < 2; ++loaded) {
        clean_world(m);
        make_parent(m);
        std::memset(m.at(kParentWork), 0, 12);
        // the buffers the card browser filled: placed in the arena as live heap blocks
        Live live;
        u32 at = kStandInHeap + 0x40000u;
        for (u32 k = 0; k < 4; ++k) {
            for (u32 i = 0; i < sizes[k]; i += 4) p32(m, at + i, rng());
            p32(m, boot::kHikitugiBufs + 4u * k, at);
            live[at] = round16(sizes[k]);
            at += round16(sizes[k]) + 0x100u;
        }
        // the compendium: a few registered personas only (bit 0 of each 52-byte entry's first halfword)
        const u32 comp = g32(m, boot::kHikitugiBufs + 4);
        for (u32 e = 0; e < 256; ++e) p16(m, comp + 52u * e, static_cast<u16>(g16(m, comp + 52u * e) & ~1u));
        for (u32 e : {3u, 40u, 200u}) p16(m, comp + 52u * e, static_cast<u16>(g16(m, comp + 52u * e) | 1u));
        const u32 old_flags = g32(m, boot::kHikitugiBufs + 8);
        std::memset(m.at(kFlagWords), 0, 704);
        // the card browser task, ending: alone in the kernel's ending list (kwlnTaskGetState looks a task up there)
        const u32 card = kParent + 0x400u;
        std::memset(m.at(card), 0, 0x68);
        p32(m, card + kOffState, 3);
        p32(m, kGp - 0x4C80u, card);  // ending list head
        p32(m, kGp - 0x4C7Cu, card);  // tail
        p32(m, kGp - 0x4C78u, 1);     // count
        p32(m, kParentWork, 1);
        p32(m, kParentWork + 8, card);
        p32(m, boot::kHikitugiMode, 1);
        p32(m, boot::kHikitugiLoaded, static_cast<u32>(loaded));
        FrameResult f = frame(m, hand, recomp, kParent, 101 + loaded, "HikitugiDataProc", carry(live));
        ++pairs;
        CHECK(f.v0 == 0);
        CHECK(g32(m, kParentWork) == 3);
        CHECK(g32(m, kParentWork + 4) == (loaded ? 1u : 0xFFFFFFFFu));
        CHECK(g32(m, boot::kHikitugiMode) == 0);
        for (u32 k = 0; k < 4; ++k) CHECK(g32(m, boot::kHikitugiBufs + 4u * k) == 0);
        CHECK(f.p.recomp->heap.live().size() == 0);  // all four freed (RwFree)
        if (loaded) {
            CHECK(g32(m, boot::kHikitugiLoaded) == 0);
            // every listed flag takes its bit from the old save's flag array
            for (u32 id : flags) {
                const bool want = (g32(m, old_flags + 4u * (id >> 5)) >> (id & 31u)) & 1u;
                const bool got = (g32(m, kFlagWords + 4u * (id >> 5)) >> (id & 31u)) & 1u;
                CHECK(got == want);
            }
        }
        // step 3: the task ends
        FrameResult d = frame(m, hand, recomp, kParent, 111, "HikitugiDataProc", carry({}));
        ++pairs;
        CHECK(d.v0 == 0xFFFFFFFFu);
    }
    MESSAGE("carry-over: " << pairs << " frame pairs, " << flags.size() << " carried flags checked");
}

TEST_CASE("game(boot): the root task creates the frame's draw passes with the documented priorities") {
    Machine* mp = si_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    const Fn hand = rg::fn_kwlnRootUpdateTask_00198650;
    const Fn recomp = rg::fn_kwlnRootUpdateTask_00198650__recomp;
    clean_world(m);
    make_parent(m, 8);
    std::memset(m.at(kParentWork), 0, 8);
    p32(m, 0x7CE134u, 0);  // no 3-D pipeline task yet (K_Assert otherwise)
    const auto stubs = [](StandInWorld& w) {
        w.si.install_recorder(0x103580u, "sub_103580 (pad update)");
        w.si.install_recorder(0x103110u, "H_Pad_UpdateWorkPad");
        w.si.install_recorder(0x109DF0u, "sub_109DF0 (ready)", 1);
        w.si.install_recorder(0x2664C0u, "gmRoot_CreateGameRootTask", 0);
    };
    int pairs = 0;
    // state 0: the draw tasks
    FrameResult s0 = frame(m, hand, recomp, kParent, 201, "rootProc", carry({}, stubs));
    ++pairs;
    CHECK(s0.v0 == 0);
    CHECK(g32(m, kParentWork) == 1);
    std::map<std::string, u32> prio;  // every task created below the root, by name
    std::vector<u32> todo{g32(m, kParent + kOffChild)};
    while (!todo.empty()) {
        const u32 t = todo.back();
        todo.pop_back();
        if (!t) continue;
        prio[task_name(m, t)] = g32(m, t + kOffPriority);
        todo.push_back(g32(m, t + kOffSibling));
        todo.push_back(g32(m, t + kOffChild));
    }
    const std::pair<const char*, u32> documented[] = {
        {"2D Draw Begin", 4196},        {"2D Draw Pre End", 5231},      {"2D Draw End", 5241},
        {"3D on 2D Zclear", 5243},      {"3D on 2D Draw Begin", 5245},  {"3D on 2D Draw End", 6320},
        {"drawBustupProc", 5276},       {"etc Draw Begin", 6323},       {"etc Draw", 6335},
        {"etc Draw End", 7379},         {"<<< show raster >>>", 7396},  {"shadow map camera", 2068},
        {"draw opac field", 2070},      {"draw opac field object", 2071}, {"draw character model", 2084},
        {"draw trans field obj preChar", 2095}, {"draw persona model", 4168}, {"draw trans field object", 4172},
        {"draw trans field", 4173},     {"3D Draw Begin", 2098},        {"3D Draw End", 4167},
        {"shadow node(camera all clear)", 2069},
    };
    for (const auto& [name, p] : documented) {
        const std::string key = std::string(name).substr(0, 23);  // the kernel keeps 23 characters of a name
        INFO(key);
        REQUIRE(prio.count(key) == 1);
        CHECK(prio[key] == p);
    }
    CHECK(prio.count("scene draw CTL") == 1);
    MESSAGE("root state 0: " << prio.size() << " tasks below the root");
    Live live = s0.p.recomp->heap.live();
    // state 1 -> 2; state 2 starts the game root (recorded) -> 3
    FrameResult s1 = frame(m, hand, recomp, kParent, 202, "rootProc", carry(live, stubs));
    ++pairs;
    CHECK(g32(m, kParentWork) == 2);
    FrameResult s2 = frame(m, hand, recomp, kParent, 203, "rootProc", carry(live, stubs));
    ++pairs;
    CHECK(g32(m, kParentWork) == 3);
    CHECK(g32(m, 0x7CE114u) == 1);
    REQUIRE(s2.p.recomp->si.calls_to(0x2664C0u) == 1);
    for (const StandInCall& c : s2.p.recomp->si.log)
        if (c.va == 0x2664C0u) CHECK(static_cast<u32>(c.args[0]) == kParent);
    // state 4: the root ends (-1)
    p32(m, kParentWork, 4);
    FrameResult s4 = frame(m, hand, recomp, kParent, 204, "rootProc", carry(live, stubs));
    ++pairs;
    CHECK(s4.v0 == 0xFFFFFFFFu);
    // state 5: the scenario prompt task, state 6; while it exists nothing moves
    p32(m, kParentWork, 5);
    FrameResult s5 = frame(m, hand, recomp, kParent, 205, "rootProc", carry(live, stubs));
    ++pairs;
    CHECK(g32(m, kParentWork) == 6);
    const u32 prompt = g32(m, kParentWork + 4);
    REQUIRE(prompt != 0);
    CHECK(task_name(m, prompt) == "ChoiceDataFileSetup");
    live = merge(live, s5.p.recomp->heap.live());
    FrameResult s6 = frame(m, hand, recomp, kParent, 206, "rootProc", carry(live, stubs));
    ++pairs;
    CHECK(s6.v0 == 0);
    CHECK(g32(m, kParentWork) == 6);
    // an out-of-table state keeps running
    p32(m, kParentWork, 9);
    FrameResult s9 = frame(m, hand, recomp, kParent, 209, "rootProc", carry(live, stubs));
    ++pairs;
    CHECK(s9.v0 == 0);
    MESSAGE("root task: " << pairs << " frame pairs");
}

#else

TEST_CASE("game(boot): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
