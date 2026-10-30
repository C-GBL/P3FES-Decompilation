// Pair tests for slice libs8 (game/src/cri/libs8.cpp: ADXM threads, PS2RNA guards, ADXT, an ADX encoder, ADXSTM, AHX
// pieces). Every body against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and
// cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the
// bus log and the stand-ins' call logs. Worlds: random ones; the live ADXM / ADXT / ADXSTM state of three replay
// snapshots (b_5800, dorm_replay_4900, climb_ref_17000); built records for the host-model checks (thread status rules,
// ADXSTM accessors, ADXT clamps and errors, the cipher-key walk, the stream size, the predictor step, the bit reader).
// Stand-ins: the kernel's thread wrappers (a status model) and callees other tests already stand in; callees another
// current packet claims are not stood in (a pair stops there, identically).
#include "handgen_pairs.h"

#include "stand_ins.h"

#include "p3fes/game/libs8.h"

#include <algorithm>
#include <cstring>
#include <map>
#include <stdexcept>
#include <vector>

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
void fn_sub_540048_00540048(EEContext&);  // generated body
void fn_sub_540048_00540048__recomp(EEContext&);  // recompiled
void fn_sub_540098_00540098(EEContext&);  // generated body
void fn_sub_540098_00540098__recomp(EEContext&);  // recompiled
void fn_sub_5400B0_005400b0(EEContext&);  // generated body
void fn_sub_5400B0_005400b0__recomp(EEContext&);  // recompiled
void fn_sub_540118_00540118(EEContext&);  // generated body
void fn_sub_540118_00540118__recomp(EEContext&);  // recompiled
void fn_adxm_SetupSafeThrd_00540178(EEContext&);  // generated body
void fn_adxm_SetupSafeThrd_00540178__recomp(EEContext&);  // recompiled
void fn_adxm_SetupUsrVsyncThrd_00540220(EEContext&);  // generated body
void fn_adxm_SetupUsrVsyncThrd_00540220__recomp(EEContext&);  // recompiled
void fn_adxm_SetupVsyncThrd_005402d8(EEContext&);  // generated body
void fn_adxm_SetupVsyncThrd_005402d8__recomp(EEContext&);  // recompiled
void fn_adxm_SetupFsThrd_00540360(EEContext&);  // generated body
void fn_adxm_SetupFsThrd_00540360__recomp(EEContext&);  // recompiled
void fn_adxm_SetupMwIdleThrd_005403e8(EEContext&);  // generated body
void fn_adxm_SetupMwIdleThrd_005403e8__recomp(EEContext&);  // recompiled
void fn_adxm_SetupUsrIdleThrd_00540480(EEContext&);  // generated body
void fn_adxm_SetupUsrIdleThrd_00540480__recomp(EEContext&);  // recompiled
void fn___errno_00540550(EEContext&);  // generated body
void fn___errno_00540550__recomp(EEContext&);  // recompiled
void fn_sub_540560_00540560(EEContext&);  // generated body
void fn_sub_540560_00540560__recomp(EEContext&);  // recompiled
void fn_sub_540570_00540570(EEContext&);  // generated body
void fn_sub_540570_00540570__recomp(EEContext&);  // recompiled
void fn_ADXM_SetupThrd_00540588(EEContext&);  // generated body
void fn_ADXM_SetupThrd_00540588__recomp(EEContext&);  // recompiled
void fn_sub_540718_00540718(EEContext&);  // generated body
void fn_sub_540718_00540718__recomp(EEContext&);  // recompiled
void fn_sub_540768_00540768(EEContext&);  // generated body
void fn_sub_540768_00540768__recomp(EEContext&);  // recompiled
void fn_sub_540800_00540800(EEContext&);  // generated body
void fn_sub_540800_00540800__recomp(EEContext&);  // recompiled
void fn_sub_5408D0_005408d0(EEContext&);  // generated body
void fn_sub_5408D0_005408d0__recomp(EEContext&);  // recompiled
void fn_sub_5409A0_005409a0(EEContext&);  // generated body
void fn_sub_5409A0_005409a0__recomp(EEContext&);  // recompiled
void fn_sub_540A70_00540a70(EEContext&);  // generated body
void fn_sub_540A70_00540a70__recomp(EEContext&);  // recompiled
void fn_sub_540BA0_00540ba0(EEContext&);  // generated body
void fn_sub_540BA0_00540ba0__recomp(EEContext&);  // recompiled
void fn_sub_540C70_00540c70(EEContext&);  // generated body
void fn_sub_540C70_00540c70__recomp(EEContext&);  // recompiled
void fn_sub_540D40_00540d40(EEContext&);  // generated body
void fn_sub_540D40_00540d40__recomp(EEContext&);  // recompiled
void fn_sub_540D58_00540d58(EEContext&);  // generated body
void fn_sub_540D58_00540d58__recomp(EEContext&);  // recompiled
void fn_ADXPS2_ExecVint_00540d80(EEContext&);  // generated body
void fn_ADXPS2_ExecVint_00540d80__recomp(EEContext&);  // recompiled
void fn_sub_540EA8_00540ea8(EEContext&);  // generated body
void fn_sub_540EA8_00540ea8__recomp(EEContext&);  // recompiled
void fn_sub_540ED8_00540ed8(EEContext&);  // generated body
void fn_sub_540ED8_00540ed8__recomp(EEContext&);  // recompiled
void fn_sub_540F60_00540f60(EEContext&);  // generated body
void fn_sub_540F60_00540f60__recomp(EEContext&);  // recompiled
void fn_sub_540FE0_00540fe0(EEContext&);  // generated body
void fn_sub_540FE0_00540fe0__recomp(EEContext&);  // recompiled
void fn_sub_5414E0_005414e0(EEContext&);  // generated body
void fn_sub_5414E0_005414e0__recomp(EEContext&);  // recompiled
void fn_sub_541510_00541510(EEContext&);  // generated body
void fn_sub_541510_00541510__recomp(EEContext&);  // recompiled
void fn_sub_541610_00541610(EEContext&);  // generated body
void fn_sub_541610_00541610__recomp(EEContext&);  // recompiled
void fn_sub_5416E8_005416e8(EEContext&);  // generated body
void fn_sub_5416E8_005416e8__recomp(EEContext&);  // recompiled
void fn_sub_541760_00541760(EEContext&);  // generated body
void fn_sub_541760_00541760__recomp(EEContext&);  // recompiled
void fn_sub_5417E0_005417e0(EEContext&);  // generated body
void fn_sub_5417E0_005417e0__recomp(EEContext&);  // recompiled
void fn_sub_5419C0_005419c0(EEContext&);  // generated body
void fn_sub_5419C0_005419c0__recomp(EEContext&);  // recompiled
void fn_sub_5419D8_005419d8(EEContext&);  // generated body
void fn_sub_5419D8_005419d8__recomp(EEContext&);  // recompiled
void fn_sub_5419F0_005419f0(EEContext&);  // generated body
void fn_sub_5419F0_005419f0__recomp(EEContext&);  // recompiled
void fn_expl_1_00541aa8(EEContext&);  // generated body
void fn_expl_1_00541aa8__recomp(EEContext&);  // recompiled
void fn_sub_541BB8_00541bb8(EEContext&);  // generated body
void fn_sub_541BB8_00541bb8__recomp(EEContext&);  // recompiled
void fn_sub_541C60_00541c60(EEContext&);  // generated body
void fn_sub_541C60_00541c60__recomp(EEContext&);  // recompiled
void fn_sub_541C88_00541c88(EEContext&);  // generated body
void fn_sub_541C88_00541c88__recomp(EEContext&);  // recompiled
void fn_sub_541CA0_00541ca0(EEContext&);  // generated body
void fn_sub_541CA0_00541ca0__recomp(EEContext&);  // recompiled
void fn_sub_541D00_00541d00(EEContext&);  // generated body
void fn_sub_541D00_00541d00__recomp(EEContext&);  // recompiled
void fn_sub_541D18_00541d18(EEContext&);  // generated body
void fn_sub_541D18_00541d18__recomp(EEContext&);  // recompiled
void fn_sub_541D30_00541d30(EEContext&);  // generated body
void fn_sub_541D30_00541d30__recomp(EEContext&);  // recompiled
void fn_sub_541DA0_00541da0(EEContext&);  // generated body
void fn_sub_541DA0_00541da0__recomp(EEContext&);  // recompiled
void fn_sub_542F70_00542f70(EEContext&);  // generated body
void fn_sub_542F70_00542f70__recomp(EEContext&);  // recompiled
void fn_sub_542FA8_00542fa8(EEContext&);  // generated body
void fn_sub_542FA8_00542fa8__recomp(EEContext&);  // recompiled
void fn_sub_542FC0_00542fc0(EEContext&);  // generated body
void fn_sub_542FC0_00542fc0__recomp(EEContext&);  // recompiled
void fn_sub_543020_00543020(EEContext&);  // generated body
void fn_sub_543020_00543020__recomp(EEContext&);  // recompiled
void fn_sub_543038_00543038(EEContext&);  // generated body
void fn_sub_543038_00543038__recomp(EEContext&);  // recompiled
void fn_sub_543328_00543328(EEContext&);  // generated body
void fn_sub_543328_00543328__recomp(EEContext&);  // recompiled
void fn_sub_543380_00543380(EEContext&);  // generated body
void fn_sub_543380_00543380__recomp(EEContext&);  // recompiled
void fn_sub_543388_00543388(EEContext&);  // generated body
void fn_sub_543388_00543388__recomp(EEContext&);  // recompiled
void fn_sub_5433C0_005433c0(EEContext&);  // generated body
void fn_sub_5433C0_005433c0__recomp(EEContext&);  // recompiled
void fn_sub_543430_00543430(EEContext&);  // generated body
void fn_sub_543430_00543430__recomp(EEContext&);  // recompiled
void fn_sub_543450_00543450(EEContext&);  // generated body
void fn_sub_543450_00543450__recomp(EEContext&);  // recompiled
void fn_sub_543470_00543470(EEContext&);  // generated body
void fn_sub_543470_00543470__recomp(EEContext&);  // recompiled
void fn_sub_5436D0_005436d0(EEContext&);  // generated body
void fn_sub_5436D0_005436d0__recomp(EEContext&);  // recompiled
void fn_sub_5438C0_005438c0(EEContext&);  // generated body
void fn_sub_5438C0_005438c0__recomp(EEContext&);  // recompiled
void fn_sub_543AA8_00543aa8(EEContext&);  // generated body
void fn_sub_543AA8_00543aa8__recomp(EEContext&);  // recompiled
void fn_sub_543B40_00543b40(EEContext&);  // generated body
void fn_sub_543B40_00543b40__recomp(EEContext&);  // recompiled
void fn_sub_543B50_00543b50(EEContext&);  // generated body
void fn_sub_543B50_00543b50__recomp(EEContext&);  // recompiled
void fn_sub_543B60_00543b60(EEContext&);  // generated body
void fn_sub_543B60_00543b60__recomp(EEContext&);  // recompiled
void fn_sub_543B78_00543b78(EEContext&);  // generated body
void fn_sub_543B78_00543b78__recomp(EEContext&);  // recompiled
void fn_sub_543BF0_00543bf0(EEContext&);  // generated body
void fn_sub_543BF0_00543bf0__recomp(EEContext&);  // recompiled
void fn_sub_543C90_00543c90(EEContext&);  // generated body
void fn_sub_543C90_00543c90__recomp(EEContext&);  // recompiled
void fn_sub_543CC8_00543cc8(EEContext&);  // generated body
void fn_sub_543CC8_00543cc8__recomp(EEContext&);  // recompiled
void fn_sub_543CD8_00543cd8(EEContext&);  // generated body
void fn_sub_543CD8_00543cd8__recomp(EEContext&);  // recompiled
void fn_sub_543D30_00543d30(EEContext&);  // generated body
void fn_sub_543D30_00543d30__recomp(EEContext&);  // recompiled
void fn_sub_543D40_00543d40(EEContext&);  // generated body
void fn_sub_543D40_00543d40__recomp(EEContext&);  // recompiled
void fn_sub_543E28_00543e28(EEContext&);  // generated body
void fn_sub_543E28_00543e28__recomp(EEContext&);  // recompiled
void fn_sub_543EC0_00543ec0(EEContext&);  // generated body
void fn_sub_543EC0_00543ec0__recomp(EEContext&);  // recompiled
void fn_sub_543EF8_00543ef8(EEContext&);  // generated body
void fn_sub_543EF8_00543ef8__recomp(EEContext&);  // recompiled
void fn_sub_543F08_00543f08(EEContext&);  // generated body
void fn_sub_543F08_00543f08__recomp(EEContext&);  // recompiled
void fn_sub_544078_00544078(EEContext&);  // generated body
void fn_sub_544078_00544078__recomp(EEContext&);  // recompiled
void fn_sub_5442D8_005442d8(EEContext&);  // generated body
void fn_sub_5442D8_005442d8__recomp(EEContext&);  // recompiled
void fn_sub_544560_00544560(EEContext&);  // generated body
void fn_sub_544560_00544560__recomp(EEContext&);  // recompiled
void fn_sub_544720_00544720(EEContext&);  // generated body
void fn_sub_544720_00544720__recomp(EEContext&);  // recompiled
void fn_sub_544850_00544850(EEContext&);  // generated body
void fn_sub_544850_00544850__recomp(EEContext&);  // recompiled
void fn_sub_545BF0_00545bf0(EEContext&);  // generated body
void fn_sub_545BF0_00545bf0__recomp(EEContext&);  // recompiled
void fn_atan2l_2_00545c08(EEContext&);  // generated body
void fn_atan2l_2_00545c08__recomp(EEContext&);  // recompiled
void fn_cosl_2_00545c20(EEContext&);  // generated body
void fn_cosl_2_00545c20__recomp(EEContext&);  // recompiled
void fn_coshl_2_00545c38(EEContext&);  // generated body
void fn_coshl_2_00545c38__recomp(EEContext&);  // recompiled
void fn_sub_545C40_00545c40(EEContext&);  // generated body
void fn_sub_545C40_00545c40__recomp(EEContext&);  // recompiled
void fn_sub_545C78_00545c78(EEContext&);  // generated body
void fn_sub_545C78_00545c78__recomp(EEContext&);  // recompiled
void fn_sub_545D18_00545d18(EEContext&);  // generated body
void fn_sub_545D18_00545d18__recomp(EEContext&);  // recompiled
void fn_sub_545E20_00545e20(EEContext&);  // generated body
void fn_sub_545E20_00545e20__recomp(EEContext&);  // recompiled
void fn_sub_545EF8_00545ef8(EEContext&);  // generated body
void fn_sub_545EF8_00545ef8__recomp(EEContext&);  // recompiled
void fn_adxstm_Create_00546010(EEContext&);  // generated body
void fn_adxstm_Create_00546010__recomp(EEContext&);  // recompiled
void fn_sub_546088_00546088(EEContext&);  // generated body
void fn_sub_546088_00546088__recomp(EEContext&);  // recompiled
void fn_sub_546150_00546150(EEContext&);  // generated body
void fn_sub_546150_00546150__recomp(EEContext&);  // recompiled
void fn_sub_5461C8_005461c8(EEContext&);  // generated body
void fn_sub_5461C8_005461c8__recomp(EEContext&);  // recompiled
void fn_sub_546238_00546238(EEContext&);  // generated body
void fn_sub_546238_00546238__recomp(EEContext&);  // recompiled
void fn_sub_5462A0_005462a0(EEContext&);  // generated body
void fn_sub_5462A0_005462a0__recomp(EEContext&);  // recompiled
void fn_sub_5462E0_005462e0(EEContext&);  // generated body
void fn_sub_5462E0_005462e0__recomp(EEContext&);  // recompiled
void fn_sub_546310_00546310(EEContext&);  // generated body
void fn_sub_546310_00546310__recomp(EEContext&);  // recompiled
void fn_sub_5463A0_005463a0(EEContext&);  // generated body
void fn_sub_5463A0_005463a0__recomp(EEContext&);  // recompiled
void fn_sub_5463F0_005463f0(EEContext&);  // generated body
void fn_sub_5463F0_005463f0__recomp(EEContext&);  // recompiled
void fn_sub_546410_00546410(EEContext&);  // generated body
void fn_sub_546410_00546410__recomp(EEContext&);  // recompiled
void fn_sub_546448_00546448(EEContext&);  // generated body
void fn_sub_546448_00546448__recomp(EEContext&);  // recompiled
void fn_sub_546460_00546460(EEContext&);  // generated body
void fn_sub_546460_00546460__recomp(EEContext&);  // recompiled
void fn_sub_5464D0_005464d0(EEContext&);  // generated body
void fn_sub_5464D0_005464d0__recomp(EEContext&);  // recompiled
void fn_sub_546510_00546510(EEContext&);  // generated body
void fn_sub_546510_00546510__recomp(EEContext&);  // recompiled
void fn_sub_546558_00546558(EEContext&);  // generated body
void fn_sub_546558_00546558__recomp(EEContext&);  // recompiled
void fn_sub_5465D0_005465d0(EEContext&);  // generated body
void fn_sub_5465D0_005465d0__recomp(EEContext&);  // recompiled
void fn_sub_546638_00546638(EEContext&);  // generated body
void fn_sub_546638_00546638__recomp(EEContext&);  // recompiled
void fn_sub_546668_00546668(EEContext&);  // generated body
void fn_sub_546668_00546668__recomp(EEContext&);  // recompiled
void fn_sub_546708_00546708(EEContext&);  // generated body
void fn_sub_546708_00546708__recomp(EEContext&);  // recompiled
void fn_sub_546758_00546758(EEContext&);  // generated body
void fn_sub_546758_00546758__recomp(EEContext&);  // recompiled
void fn_adxstmf_ExecRead_00546788(EEContext&);  // generated body
void fn_adxstmf_ExecRead_00546788__recomp(EEContext&);  // recompiled
void fn_ADXSTMF_ExecHndl_00546bb0(EEContext&);  // generated body
void fn_ADXSTMF_ExecHndl_00546bb0__recomp(EEContext&);  // recompiled
void fn_sub_546D90_00546d90(EEContext&);  // generated body
void fn_sub_546D90_00546d90__recomp(EEContext&);  // recompiled
void fn_sub_546DB8_00546db8(EEContext&);  // generated body
void fn_sub_546DB8_00546db8__recomp(EEContext&);  // recompiled
void fn_sub_546E38_00546e38(EEContext&);  // generated body
void fn_sub_546E38_00546e38__recomp(EEContext&);  // recompiled
void fn_adxstmf_ExecServer_00546e60(EEContext&);  // generated body
void fn_adxstmf_ExecServer_00546e60__recomp(EEContext&);  // recompiled
void fn_sub_546FF8_00546ff8(EEContext&);  // generated body
void fn_sub_546FF8_00546ff8__recomp(EEContext&);  // recompiled
void fn_sub_547008_00547008(EEContext&);  // generated body
void fn_sub_547008_00547008__recomp(EEContext&);  // recompiled
void fn_sub_547050_00547050(EEContext&);  // generated body
void fn_sub_547050_00547050__recomp(EEContext&);  // recompiled
void fn_sub_547068_00547068(EEContext&);  // generated body
void fn_sub_547068_00547068__recomp(EEContext&);  // recompiled
void fn_sub_5470A0_005470a0(EEContext&);  // generated body
void fn_sub_5470A0_005470a0__recomp(EEContext&);  // recompiled
void fn_sub_5470A8_005470a8(EEContext&);  // generated body
void fn_sub_5470A8_005470a8__recomp(EEContext&);  // recompiled
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2_005470e0(EEContext&);  // generated body
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2_005470e0__recomp(EEContext&);  // recompiled
void fn_sub_547138_00547138(EEContext&);  // generated body
void fn_sub_547138_00547138__recomp(EEContext&);  // recompiled
void fn_sub_547178_00547178(EEContext&);  // generated body
void fn_sub_547178_00547178__recomp(EEContext&);  // recompiled
void fn_sub_547318_00547318(EEContext&);  // generated body
void fn_sub_547318_00547318__recomp(EEContext&);  // recompiled
void fn_sub_547358_00547358(EEContext&);  // generated body
void fn_sub_547358_00547358__recomp(EEContext&);  // recompiled
void fn_sub_547558_00547558(EEContext&);  // generated body
void fn_sub_547558_00547558__recomp(EEContext&);  // recompiled
void fn_ADXPS2_SetupDvdFs_00547668(EEContext&);  // generated body
void fn_ADXPS2_SetupDvdFs_00547668__recomp(EEContext&);  // recompiled
void fn_sub_548278_00548278(EEContext&);  // generated body
void fn_sub_548278_00548278__recomp(EEContext&);  // recompiled
void fn_sub_549000_00549000(EEContext&);  // generated body
void fn_sub_549000_00549000__recomp(EEContext&);  // recompiled
void fn_sub_549310_00549310(EEContext&);  // generated body
void fn_sub_549310_00549310__recomp(EEContext&);  // recompiled
void fn_sub_549390_00549390(EEContext&);  // generated body
void fn_sub_549390_00549390__recomp(EEContext&);  // recompiled
void fn_sub_549450_00549450(EEContext&);  // generated body
void fn_sub_549450_00549450__recomp(EEContext&);  // recompiled
void fn_sub_54AC40_0054ac40(EEContext&);  // generated body
void fn_sub_54AC40_0054ac40__recomp(EEContext&);  // recompiled
void fn_sub_54B3F0_0054b3f0(EEContext&);  // generated body
void fn_sub_54B3F0_0054b3f0__recomp(EEContext&);  // recompiled
void fn_sub_54B8E0_0054b8e0(EEContext&);  // generated body
void fn_sub_54B8E0_0054b8e0__recomp(EEContext&);  // recompiled
void fn_sub_54CFE8_0054cfe8(EEContext&);  // generated body
void fn_sub_54CFE8_0054cfe8__recomp(EEContext&);  // recompiled
void fn_sub_54D528_0054d528(EEContext&);  // generated body
void fn_sub_54D528_0054d528__recomp(EEContext&);  // recompiled
void fn_sub_54D6B8_0054d6b8(EEContext&);  // generated body
void fn_sub_54D6B8_0054d6b8__recomp(EEContext&);  // recompiled
void fn_sub_54D7E8_0054d7e8(EEContext&);  // generated body
void fn_sub_54D7E8_0054d7e8__recomp(EEContext&);  // recompiled
void fn_sub_54D898_0054d898(EEContext&);  // generated body
void fn_sub_54D898_0054d898__recomp(EEContext&);  // recompiled
void fn_sub_54DB38_0054db38(EEContext&);  // generated body
void fn_sub_54DB38_0054db38__recomp(EEContext&);  // recompiled
void fn_sub_54DBE8_0054dbe8(EEContext&);  // generated body
void fn_sub_54DBE8_0054dbe8__recomp(EEContext&);  // recompiled
void fn_sub_54DBF0_0054dbf0(EEContext&);  // generated body
void fn_sub_54DBF0_0054dbf0__recomp(EEContext&);  // recompiled
void fn_sub_54DE50_0054de50(EEContext&);  // generated body
void fn_sub_54DE50_0054de50__recomp(EEContext&);  // recompiled
void fn_sub_54DE90_0054de90(EEContext&);  // generated body
void fn_sub_54DE90_0054de90__recomp(EEContext&);  // recompiled
void fn_sub_54E2C0_0054e2c0(EEContext&);  // generated body
void fn_sub_54E2C0_0054e2c0__recomp(EEContext&);  // recompiled
void fn_sub_54E568_0054e568(EEContext&);  // generated body
void fn_sub_54E568_0054e568__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_540048", 0x540048, &recomp_gen::fn_sub_540048_00540048, &recomp_gen::fn_sub_540048_00540048__recomp},
    {"sub_540098", 0x540098, &recomp_gen::fn_sub_540098_00540098, &recomp_gen::fn_sub_540098_00540098__recomp},
    {"sub_5400B0", 0x5400B0, &recomp_gen::fn_sub_5400B0_005400b0, &recomp_gen::fn_sub_5400B0_005400b0__recomp},
    {"sub_540118", 0x540118, &recomp_gen::fn_sub_540118_00540118, &recomp_gen::fn_sub_540118_00540118__recomp},
    {"adxm_SetupSafeThrd", 0x540178, &recomp_gen::fn_adxm_SetupSafeThrd_00540178, &recomp_gen::fn_adxm_SetupSafeThrd_00540178__recomp},
    {"adxm_SetupUsrVsyncThrd", 0x540220, &recomp_gen::fn_adxm_SetupUsrVsyncThrd_00540220, &recomp_gen::fn_adxm_SetupUsrVsyncThrd_00540220__recomp},
    {"adxm_SetupVsyncThrd", 0x5402D8, &recomp_gen::fn_adxm_SetupVsyncThrd_005402d8, &recomp_gen::fn_adxm_SetupVsyncThrd_005402d8__recomp},
    {"adxm_SetupFsThrd", 0x540360, &recomp_gen::fn_adxm_SetupFsThrd_00540360, &recomp_gen::fn_adxm_SetupFsThrd_00540360__recomp},
    {"adxm_SetupMwIdleThrd", 0x5403E8, &recomp_gen::fn_adxm_SetupMwIdleThrd_005403e8, &recomp_gen::fn_adxm_SetupMwIdleThrd_005403e8__recomp},
    {"adxm_SetupUsrIdleThrd", 0x540480, &recomp_gen::fn_adxm_SetupUsrIdleThrd_00540480, &recomp_gen::fn_adxm_SetupUsrIdleThrd_00540480__recomp},
    {"__errno", 0x540550, &recomp_gen::fn___errno_00540550, &recomp_gen::fn___errno_00540550__recomp},
    {"sub_540560", 0x540560, &recomp_gen::fn_sub_540560_00540560, &recomp_gen::fn_sub_540560_00540560__recomp},
    {"sub_540570", 0x540570, &recomp_gen::fn_sub_540570_00540570, &recomp_gen::fn_sub_540570_00540570__recomp},
    {"ADXM_SetupThrd", 0x540588, &recomp_gen::fn_ADXM_SetupThrd_00540588, &recomp_gen::fn_ADXM_SetupThrd_00540588__recomp},
    {"sub_540718", 0x540718, &recomp_gen::fn_sub_540718_00540718, &recomp_gen::fn_sub_540718_00540718__recomp},
    {"sub_540768", 0x540768, &recomp_gen::fn_sub_540768_00540768, &recomp_gen::fn_sub_540768_00540768__recomp},
    {"sub_540800", 0x540800, &recomp_gen::fn_sub_540800_00540800, &recomp_gen::fn_sub_540800_00540800__recomp},
    {"sub_5408D0", 0x5408D0, &recomp_gen::fn_sub_5408D0_005408d0, &recomp_gen::fn_sub_5408D0_005408d0__recomp},
    {"sub_5409A0", 0x5409A0, &recomp_gen::fn_sub_5409A0_005409a0, &recomp_gen::fn_sub_5409A0_005409a0__recomp},
    {"sub_540A70", 0x540A70, &recomp_gen::fn_sub_540A70_00540a70, &recomp_gen::fn_sub_540A70_00540a70__recomp},
    {"sub_540BA0", 0x540BA0, &recomp_gen::fn_sub_540BA0_00540ba0, &recomp_gen::fn_sub_540BA0_00540ba0__recomp},
    {"sub_540C70", 0x540C70, &recomp_gen::fn_sub_540C70_00540c70, &recomp_gen::fn_sub_540C70_00540c70__recomp},
    {"sub_540D40", 0x540D40, &recomp_gen::fn_sub_540D40_00540d40, &recomp_gen::fn_sub_540D40_00540d40__recomp},
    {"sub_540D58", 0x540D58, &recomp_gen::fn_sub_540D58_00540d58, &recomp_gen::fn_sub_540D58_00540d58__recomp},
    {"ADXPS2_ExecVint", 0x540D80, &recomp_gen::fn_ADXPS2_ExecVint_00540d80, &recomp_gen::fn_ADXPS2_ExecVint_00540d80__recomp},
    {"sub_540EA8", 0x540EA8, &recomp_gen::fn_sub_540EA8_00540ea8, &recomp_gen::fn_sub_540EA8_00540ea8__recomp},
    {"sub_540ED8", 0x540ED8, &recomp_gen::fn_sub_540ED8_00540ed8, &recomp_gen::fn_sub_540ED8_00540ed8__recomp},
    {"sub_540F60", 0x540F60, &recomp_gen::fn_sub_540F60_00540f60, &recomp_gen::fn_sub_540F60_00540f60__recomp},
    {"sub_540FE0", 0x540FE0, &recomp_gen::fn_sub_540FE0_00540fe0, &recomp_gen::fn_sub_540FE0_00540fe0__recomp},
    {"sub_5414E0", 0x5414E0, &recomp_gen::fn_sub_5414E0_005414e0, &recomp_gen::fn_sub_5414E0_005414e0__recomp},
    {"sub_541510", 0x541510, &recomp_gen::fn_sub_541510_00541510, &recomp_gen::fn_sub_541510_00541510__recomp},
    {"sub_541610", 0x541610, &recomp_gen::fn_sub_541610_00541610, &recomp_gen::fn_sub_541610_00541610__recomp},
    {"sub_5416E8", 0x5416E8, &recomp_gen::fn_sub_5416E8_005416e8, &recomp_gen::fn_sub_5416E8_005416e8__recomp},
    {"sub_541760", 0x541760, &recomp_gen::fn_sub_541760_00541760, &recomp_gen::fn_sub_541760_00541760__recomp},
    {"sub_5417E0", 0x5417E0, &recomp_gen::fn_sub_5417E0_005417e0, &recomp_gen::fn_sub_5417E0_005417e0__recomp},
    {"sub_5419C0", 0x5419C0, &recomp_gen::fn_sub_5419C0_005419c0, &recomp_gen::fn_sub_5419C0_005419c0__recomp},
    {"sub_5419D8", 0x5419D8, &recomp_gen::fn_sub_5419D8_005419d8, &recomp_gen::fn_sub_5419D8_005419d8__recomp},
    {"sub_5419F0", 0x5419F0, &recomp_gen::fn_sub_5419F0_005419f0, &recomp_gen::fn_sub_5419F0_005419f0__recomp},
    {"expl_1", 0x541AA8, &recomp_gen::fn_expl_1_00541aa8, &recomp_gen::fn_expl_1_00541aa8__recomp},
    {"sub_541BB8", 0x541BB8, &recomp_gen::fn_sub_541BB8_00541bb8, &recomp_gen::fn_sub_541BB8_00541bb8__recomp},
    {"sub_541C60", 0x541C60, &recomp_gen::fn_sub_541C60_00541c60, &recomp_gen::fn_sub_541C60_00541c60__recomp},
    {"sub_541C88", 0x541C88, &recomp_gen::fn_sub_541C88_00541c88, &recomp_gen::fn_sub_541C88_00541c88__recomp},
    {"sub_541CA0", 0x541CA0, &recomp_gen::fn_sub_541CA0_00541ca0, &recomp_gen::fn_sub_541CA0_00541ca0__recomp},
    {"sub_541D00", 0x541D00, &recomp_gen::fn_sub_541D00_00541d00, &recomp_gen::fn_sub_541D00_00541d00__recomp},
    {"sub_541D18", 0x541D18, &recomp_gen::fn_sub_541D18_00541d18, &recomp_gen::fn_sub_541D18_00541d18__recomp},
    {"sub_541D30", 0x541D30, &recomp_gen::fn_sub_541D30_00541d30, &recomp_gen::fn_sub_541D30_00541d30__recomp},
    {"sub_541DA0", 0x541DA0, &recomp_gen::fn_sub_541DA0_00541da0, &recomp_gen::fn_sub_541DA0_00541da0__recomp},
    {"sub_542F70", 0x542F70, &recomp_gen::fn_sub_542F70_00542f70, &recomp_gen::fn_sub_542F70_00542f70__recomp},
    {"sub_542FA8", 0x542FA8, &recomp_gen::fn_sub_542FA8_00542fa8, &recomp_gen::fn_sub_542FA8_00542fa8__recomp},
    {"sub_542FC0", 0x542FC0, &recomp_gen::fn_sub_542FC0_00542fc0, &recomp_gen::fn_sub_542FC0_00542fc0__recomp},
    {"sub_543020", 0x543020, &recomp_gen::fn_sub_543020_00543020, &recomp_gen::fn_sub_543020_00543020__recomp},
    {"sub_543038", 0x543038, &recomp_gen::fn_sub_543038_00543038, &recomp_gen::fn_sub_543038_00543038__recomp},
    {"sub_543328", 0x543328, &recomp_gen::fn_sub_543328_00543328, &recomp_gen::fn_sub_543328_00543328__recomp},
    {"sub_543380", 0x543380, &recomp_gen::fn_sub_543380_00543380, &recomp_gen::fn_sub_543380_00543380__recomp},
    {"sub_543388", 0x543388, &recomp_gen::fn_sub_543388_00543388, &recomp_gen::fn_sub_543388_00543388__recomp},
    {"sub_5433C0", 0x5433C0, &recomp_gen::fn_sub_5433C0_005433c0, &recomp_gen::fn_sub_5433C0_005433c0__recomp},
    {"sub_543430", 0x543430, &recomp_gen::fn_sub_543430_00543430, &recomp_gen::fn_sub_543430_00543430__recomp},
    {"sub_543450", 0x543450, &recomp_gen::fn_sub_543450_00543450, &recomp_gen::fn_sub_543450_00543450__recomp},
    {"sub_543470", 0x543470, &recomp_gen::fn_sub_543470_00543470, &recomp_gen::fn_sub_543470_00543470__recomp},
    {"sub_5436D0", 0x5436D0, &recomp_gen::fn_sub_5436D0_005436d0, &recomp_gen::fn_sub_5436D0_005436d0__recomp},
    {"sub_5438C0", 0x5438C0, &recomp_gen::fn_sub_5438C0_005438c0, &recomp_gen::fn_sub_5438C0_005438c0__recomp},
    {"sub_543AA8", 0x543AA8, &recomp_gen::fn_sub_543AA8_00543aa8, &recomp_gen::fn_sub_543AA8_00543aa8__recomp},
    {"sub_543B40", 0x543B40, &recomp_gen::fn_sub_543B40_00543b40, &recomp_gen::fn_sub_543B40_00543b40__recomp},
    {"sub_543B50", 0x543B50, &recomp_gen::fn_sub_543B50_00543b50, &recomp_gen::fn_sub_543B50_00543b50__recomp},
    {"sub_543B60", 0x543B60, &recomp_gen::fn_sub_543B60_00543b60, &recomp_gen::fn_sub_543B60_00543b60__recomp},
    {"sub_543B78", 0x543B78, &recomp_gen::fn_sub_543B78_00543b78, &recomp_gen::fn_sub_543B78_00543b78__recomp},
    {"sub_543BF0", 0x543BF0, &recomp_gen::fn_sub_543BF0_00543bf0, &recomp_gen::fn_sub_543BF0_00543bf0__recomp},
    {"sub_543C90", 0x543C90, &recomp_gen::fn_sub_543C90_00543c90, &recomp_gen::fn_sub_543C90_00543c90__recomp},
    {"sub_543CC8", 0x543CC8, &recomp_gen::fn_sub_543CC8_00543cc8, &recomp_gen::fn_sub_543CC8_00543cc8__recomp},
    {"sub_543CD8", 0x543CD8, &recomp_gen::fn_sub_543CD8_00543cd8, &recomp_gen::fn_sub_543CD8_00543cd8__recomp},
    {"sub_543D30", 0x543D30, &recomp_gen::fn_sub_543D30_00543d30, &recomp_gen::fn_sub_543D30_00543d30__recomp},
    {"sub_543D40", 0x543D40, &recomp_gen::fn_sub_543D40_00543d40, &recomp_gen::fn_sub_543D40_00543d40__recomp},
    {"sub_543E28", 0x543E28, &recomp_gen::fn_sub_543E28_00543e28, &recomp_gen::fn_sub_543E28_00543e28__recomp},
    {"sub_543EC0", 0x543EC0, &recomp_gen::fn_sub_543EC0_00543ec0, &recomp_gen::fn_sub_543EC0_00543ec0__recomp},
    {"sub_543EF8", 0x543EF8, &recomp_gen::fn_sub_543EF8_00543ef8, &recomp_gen::fn_sub_543EF8_00543ef8__recomp},
    {"sub_543F08", 0x543F08, &recomp_gen::fn_sub_543F08_00543f08, &recomp_gen::fn_sub_543F08_00543f08__recomp},
    {"sub_544078", 0x544078, &recomp_gen::fn_sub_544078_00544078, &recomp_gen::fn_sub_544078_00544078__recomp},
    {"sub_5442D8", 0x5442D8, &recomp_gen::fn_sub_5442D8_005442d8, &recomp_gen::fn_sub_5442D8_005442d8__recomp},
    {"sub_544560", 0x544560, &recomp_gen::fn_sub_544560_00544560, &recomp_gen::fn_sub_544560_00544560__recomp},
    {"sub_544720", 0x544720, &recomp_gen::fn_sub_544720_00544720, &recomp_gen::fn_sub_544720_00544720__recomp},
    {"sub_544850", 0x544850, &recomp_gen::fn_sub_544850_00544850, &recomp_gen::fn_sub_544850_00544850__recomp},
    {"sub_545BF0", 0x545BF0, &recomp_gen::fn_sub_545BF0_00545bf0, &recomp_gen::fn_sub_545BF0_00545bf0__recomp},
    {"atan2l_2", 0x545C08, &recomp_gen::fn_atan2l_2_00545c08, &recomp_gen::fn_atan2l_2_00545c08__recomp},
    {"cosl_2", 0x545C20, &recomp_gen::fn_cosl_2_00545c20, &recomp_gen::fn_cosl_2_00545c20__recomp},
    {"coshl_2", 0x545C38, &recomp_gen::fn_coshl_2_00545c38, &recomp_gen::fn_coshl_2_00545c38__recomp},
    {"sub_545C40", 0x545C40, &recomp_gen::fn_sub_545C40_00545c40, &recomp_gen::fn_sub_545C40_00545c40__recomp},
    {"sub_545C78", 0x545C78, &recomp_gen::fn_sub_545C78_00545c78, &recomp_gen::fn_sub_545C78_00545c78__recomp},
    {"sub_545D18", 0x545D18, &recomp_gen::fn_sub_545D18_00545d18, &recomp_gen::fn_sub_545D18_00545d18__recomp},
    {"sub_545E20", 0x545E20, &recomp_gen::fn_sub_545E20_00545e20, &recomp_gen::fn_sub_545E20_00545e20__recomp},
    {"sub_545EF8", 0x545EF8, &recomp_gen::fn_sub_545EF8_00545ef8, &recomp_gen::fn_sub_545EF8_00545ef8__recomp},
    {"adxstm_Create", 0x546010, &recomp_gen::fn_adxstm_Create_00546010, &recomp_gen::fn_adxstm_Create_00546010__recomp},
    {"sub_546088", 0x546088, &recomp_gen::fn_sub_546088_00546088, &recomp_gen::fn_sub_546088_00546088__recomp},
    {"sub_546150", 0x546150, &recomp_gen::fn_sub_546150_00546150, &recomp_gen::fn_sub_546150_00546150__recomp},
    {"sub_5461C8", 0x5461C8, &recomp_gen::fn_sub_5461C8_005461c8, &recomp_gen::fn_sub_5461C8_005461c8__recomp},
    {"sub_546238", 0x546238, &recomp_gen::fn_sub_546238_00546238, &recomp_gen::fn_sub_546238_00546238__recomp},
    {"sub_5462A0", 0x5462A0, &recomp_gen::fn_sub_5462A0_005462a0, &recomp_gen::fn_sub_5462A0_005462a0__recomp},
    {"sub_5462E0", 0x5462E0, &recomp_gen::fn_sub_5462E0_005462e0, &recomp_gen::fn_sub_5462E0_005462e0__recomp},
    {"sub_546310", 0x546310, &recomp_gen::fn_sub_546310_00546310, &recomp_gen::fn_sub_546310_00546310__recomp},
    {"sub_5463A0", 0x5463A0, &recomp_gen::fn_sub_5463A0_005463a0, &recomp_gen::fn_sub_5463A0_005463a0__recomp},
    {"sub_5463F0", 0x5463F0, &recomp_gen::fn_sub_5463F0_005463f0, &recomp_gen::fn_sub_5463F0_005463f0__recomp},
    {"sub_546410", 0x546410, &recomp_gen::fn_sub_546410_00546410, &recomp_gen::fn_sub_546410_00546410__recomp},
    {"sub_546448", 0x546448, &recomp_gen::fn_sub_546448_00546448, &recomp_gen::fn_sub_546448_00546448__recomp},
    {"sub_546460", 0x546460, &recomp_gen::fn_sub_546460_00546460, &recomp_gen::fn_sub_546460_00546460__recomp},
    {"sub_5464D0", 0x5464D0, &recomp_gen::fn_sub_5464D0_005464d0, &recomp_gen::fn_sub_5464D0_005464d0__recomp},
    {"sub_546510", 0x546510, &recomp_gen::fn_sub_546510_00546510, &recomp_gen::fn_sub_546510_00546510__recomp},
    {"sub_546558", 0x546558, &recomp_gen::fn_sub_546558_00546558, &recomp_gen::fn_sub_546558_00546558__recomp},
    {"sub_5465D0", 0x5465D0, &recomp_gen::fn_sub_5465D0_005465d0, &recomp_gen::fn_sub_5465D0_005465d0__recomp},
    {"sub_546638", 0x546638, &recomp_gen::fn_sub_546638_00546638, &recomp_gen::fn_sub_546638_00546638__recomp},
    {"sub_546668", 0x546668, &recomp_gen::fn_sub_546668_00546668, &recomp_gen::fn_sub_546668_00546668__recomp},
    {"sub_546708", 0x546708, &recomp_gen::fn_sub_546708_00546708, &recomp_gen::fn_sub_546708_00546708__recomp},
    {"sub_546758", 0x546758, &recomp_gen::fn_sub_546758_00546758, &recomp_gen::fn_sub_546758_00546758__recomp},
    {"adxstmf_ExecRead", 0x546788, &recomp_gen::fn_adxstmf_ExecRead_00546788, &recomp_gen::fn_adxstmf_ExecRead_00546788__recomp},
    {"ADXSTMF_ExecHndl", 0x546BB0, &recomp_gen::fn_ADXSTMF_ExecHndl_00546bb0, &recomp_gen::fn_ADXSTMF_ExecHndl_00546bb0__recomp},
    {"sub_546D90", 0x546D90, &recomp_gen::fn_sub_546D90_00546d90, &recomp_gen::fn_sub_546D90_00546d90__recomp},
    {"sub_546DB8", 0x546DB8, &recomp_gen::fn_sub_546DB8_00546db8, &recomp_gen::fn_sub_546DB8_00546db8__recomp},
    {"sub_546E38", 0x546E38, &recomp_gen::fn_sub_546E38_00546e38, &recomp_gen::fn_sub_546E38_00546e38__recomp},
    {"adxstmf_ExecServer", 0x546E60, &recomp_gen::fn_adxstmf_ExecServer_00546e60, &recomp_gen::fn_adxstmf_ExecServer_00546e60__recomp},
    {"sub_546FF8", 0x546FF8, &recomp_gen::fn_sub_546FF8_00546ff8, &recomp_gen::fn_sub_546FF8_00546ff8__recomp},
    {"sub_547008", 0x547008, &recomp_gen::fn_sub_547008_00547008, &recomp_gen::fn_sub_547008_00547008__recomp},
    {"sub_547050", 0x547050, &recomp_gen::fn_sub_547050_00547050, &recomp_gen::fn_sub_547050_00547050__recomp},
    {"sub_547068", 0x547068, &recomp_gen::fn_sub_547068_00547068, &recomp_gen::fn_sub_547068_00547068__recomp},
    {"sub_5470A0", 0x5470A0, &recomp_gen::fn_sub_5470A0_005470a0, &recomp_gen::fn_sub_5470A0_005470a0__recomp},
    {"sub_5470A8", 0x5470A8, &recomp_gen::fn_sub_5470A8_005470a8, &recomp_gen::fn_sub_5470A8_005470a8__recomp},
    {"_ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2", 0x5470E0, &recomp_gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2_005470e0, &recomp_gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2_005470e0__recomp},
    {"sub_547138", 0x547138, &recomp_gen::fn_sub_547138_00547138, &recomp_gen::fn_sub_547138_00547138__recomp},
    {"sub_547178", 0x547178, &recomp_gen::fn_sub_547178_00547178, &recomp_gen::fn_sub_547178_00547178__recomp},
    {"sub_547318", 0x547318, &recomp_gen::fn_sub_547318_00547318, &recomp_gen::fn_sub_547318_00547318__recomp},
    {"sub_547358", 0x547358, &recomp_gen::fn_sub_547358_00547358, &recomp_gen::fn_sub_547358_00547358__recomp},
    {"sub_547558", 0x547558, &recomp_gen::fn_sub_547558_00547558, &recomp_gen::fn_sub_547558_00547558__recomp},
    {"ADXPS2_SetupDvdFs", 0x547668, &recomp_gen::fn_ADXPS2_SetupDvdFs_00547668, &recomp_gen::fn_ADXPS2_SetupDvdFs_00547668__recomp},
    {"sub_548278", 0x548278, &recomp_gen::fn_sub_548278_00548278, &recomp_gen::fn_sub_548278_00548278__recomp},
    {"sub_549000", 0x549000, &recomp_gen::fn_sub_549000_00549000, &recomp_gen::fn_sub_549000_00549000__recomp},
    {"sub_549310", 0x549310, &recomp_gen::fn_sub_549310_00549310, &recomp_gen::fn_sub_549310_00549310__recomp},
    {"sub_549390", 0x549390, &recomp_gen::fn_sub_549390_00549390, &recomp_gen::fn_sub_549390_00549390__recomp},
    {"sub_549450", 0x549450, &recomp_gen::fn_sub_549450_00549450, &recomp_gen::fn_sub_549450_00549450__recomp},
    {"sub_54AC40", 0x54AC40, &recomp_gen::fn_sub_54AC40_0054ac40, &recomp_gen::fn_sub_54AC40_0054ac40__recomp},
    {"sub_54B3F0", 0x54B3F0, &recomp_gen::fn_sub_54B3F0_0054b3f0, &recomp_gen::fn_sub_54B3F0_0054b3f0__recomp},
    {"sub_54B8E0", 0x54B8E0, &recomp_gen::fn_sub_54B8E0_0054b8e0, &recomp_gen::fn_sub_54B8E0_0054b8e0__recomp},
    {"sub_54CFE8", 0x54CFE8, &recomp_gen::fn_sub_54CFE8_0054cfe8, &recomp_gen::fn_sub_54CFE8_0054cfe8__recomp},
    {"sub_54D528", 0x54D528, &recomp_gen::fn_sub_54D528_0054d528, &recomp_gen::fn_sub_54D528_0054d528__recomp},
    {"sub_54D6B8", 0x54D6B8, &recomp_gen::fn_sub_54D6B8_0054d6b8, &recomp_gen::fn_sub_54D6B8_0054d6b8__recomp},
    {"sub_54D7E8", 0x54D7E8, &recomp_gen::fn_sub_54D7E8_0054d7e8, &recomp_gen::fn_sub_54D7E8_0054d7e8__recomp},
    {"sub_54D898", 0x54D898, &recomp_gen::fn_sub_54D898_0054d898, &recomp_gen::fn_sub_54D898_0054d898__recomp},
    {"sub_54DB38", 0x54DB38, &recomp_gen::fn_sub_54DB38_0054db38, &recomp_gen::fn_sub_54DB38_0054db38__recomp},
    {"sub_54DBE8", 0x54DBE8, &recomp_gen::fn_sub_54DBE8_0054dbe8, &recomp_gen::fn_sub_54DBE8_0054dbe8__recomp},
    {"sub_54DBF0", 0x54DBF0, &recomp_gen::fn_sub_54DBF0_0054dbf0, &recomp_gen::fn_sub_54DBF0_0054dbf0__recomp},
    {"sub_54DE50", 0x54DE50, &recomp_gen::fn_sub_54DE50_0054de50, &recomp_gen::fn_sub_54DE50_0054de50__recomp},
    {"sub_54DE90", 0x54DE90, &recomp_gen::fn_sub_54DE90_0054de90, &recomp_gen::fn_sub_54DE90_0054de90__recomp},
    {"sub_54E2C0", 0x54E2C0, &recomp_gen::fn_sub_54E2C0_0054e2c0, &recomp_gen::fn_sub_54E2C0_0054e2c0__recomp},
    {"sub_54E568", 0x54E568, &recomp_gen::fn_sub_54E568_0054e568, &recomp_gen::fn_sub_54E568_0054e568__recomp},
};

constexpr u32 kWorld = 0x01810000u;      // free RAM for random worlds and built records
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kOut = 0x01820000u;        // out-parameter area and built records (16 KiB)
constexpr u32 kSeeds = 48;

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    throw std::runtime_error("libs8: no case for an address");
}
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u64 r64(Machine& m, u32 va) { u64 v; std::memcpy(&v, m.at(va), 8); return v; }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
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

// ---- the guest records (libs8.cpp's role comments; the live ones from the replay snapshots) ----------------------
constexpr u32 kStm = 0x792BD8u, kStmSize = 96u, kStmCount = 40u;   // ADXSTM records
constexpr u32 kAdxt = 0x787570u, kAdxtSize = 200u;                 // ADXT handles (+4 decoder, +8 ADXSTM, +12 output)
constexpr u32 kSetupCount = 0x788644u, kThrdMode = 0x788648u, kPrintLevel = 0x78FF80u;
constexpr u32 kTids = 0x7886D8u;    // safe, usr-vsync, vsync, fs, main, mwidle, usr-idle (words)
constexpr u32 kExitReq = 0x7886F8u; // six 64-bit request / ack pairs, stride 16
constexpr u32 kKeyTable = 0x7C11B8u, kKeySeeds[3] = {0x7C13B8u, 0x7C15B8u, 0x7C17B8u};
constexpr u32 kBitMask = 0x796F58u;
constexpr u32 kFmtUsrVsync = 0x7C2520u;  // "ADXM: UsrVsyncThread Stack pointer = 0x%08x, ..."

// ---- the stand-ins: the kernel's thread wrappers and the callees other tests already stand in ----------------------
// None of them is claimed by a current packet. The thread wrappers model the kernel: ReferThreadStatus writes the
// status `g_status` (+0) and a current priority (+24) into the caller's buffer; Wakeup / Resume / Suspend succeed
// (return the id); a woken ADXM thread acknowledges its exit request (all six ack words become 1), so the shutdown
// loops end after one round; CreateThread returns 0x21.
constexpr u32 kCreateThread = 0x502F60u, kChangePrio = 0x502FF0u, kGetThreadId = 0x503050u, kReferStatus = 0x503060u,
              kSleep = 0x503080u, kWakeup = 0x503090u, kSuspend = 0x5030D0u, kResume = 0x5030F0u,
              kStartThread = 0x5042A0u, kScePrintf = 0x505E48u, kAdxtErr = 0x53AE08u;
const u32 kRecorders[] = {0x537780u, 0x5460E0u, 0x5465A0u, 0x546270u, 0x53AE08u, 0x54A928u,
                          0x53AE60u, 0x5463A8u, 0x546718u, 0x538038u};
u64 g_v0 = 0;
u32 g_status = 4;
void install_world(StandIns& s) {
    for (u32 va : kRecorders) s.install_recorder(va, "recorder", g_v0, 3);
    for (u32 va : {kChangePrio, kStartThread, kSleep, kScePrintf}) s.install_recorder(va, "thread", 0, 3);
    s.install(kGetThreadId, "GetThreadId", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = 1; }, 3);
    s.install(kCreateThread, "CreateThread", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = 0x21; }, 3);
    s.install(kReferStatus, "ReferThreadStatus", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 buf = static_cast<u32>(c.args[1]);
        if (buf >= 0x100000u && buf + 32 <= EEMemory::kMainRamSize) {
            ctx.memory->write<u32>(buf, g_status);
            ctx.memory->write<u32>(buf + 24, 0x20u);
        }
        c.v0 = c.args[0];
    }, 3);
    s.install(kWakeup, "WakeupThread", [](EEContext& ctx, StandIns&, StandInCall& c) {
        for (u32 i = 0; i < 6; ++i) ctx.memory->write<u64>(kExitReq + 8 + 16 * i, 1);
        c.v0 = c.args[0];
    }, 3);
    for (u32 va : {kResume, kSuspend})
        s.install(va, "Resume/Suspend", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; }, 3);
    install_sprintf(s);
}

// Each body runs with its own stand-in set (a thunk installs it around the body); the two call logs must be equal.
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
// One pair from the machine's current state (the recompiled run's memory stays); `log` receives the hand body's calls.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, StandIns* log = nullptr) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_world(sh);
    install_world(sr);
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
// The same comparison on a long-lived BaseRange (write_tracker.h): the snapshot stays the base and restore() copies
// back only the pages a pair wrote.
hgp::Run pr_base(Machine& m, BaseRange& ram, u32 addr, const Args& args, const HwCheck& hw) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_world(sh);
    install_world(sr);
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
    INFO(c.name << " a0=" << std::hex << args[0] << " a1=" << args[1] << " a2=" << args[2] << " a3=" << args[3] << std::dec
                << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + ")" : std::string()));
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
    CHECK(h.vu_control == r.vu_control);
    same_log(sh, sr, c.name);
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, StandIns* log = nullptr) {
    const hgp::Run r = pr(m, addr, a, std::move(t), log);
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

// What $a0 / $a1 are for each function in the snapshot sweep (the records of libs8.cpp's role comments).
bool takes_tid(u32 a) { return a == 0x540048u || a == 0x5400B0u || a == 0x540118u; }
bool takes_stm(u32 a) {
    return a >= 0x545D18u && a <= 0x547558u && a != 0x546010u && a != 0x546D90u && a != 0x546DB8u && a != 0x546E38u &&
           a != 0x546E60u;
}
bool takes_adxt(u32 a) { return (a >= 0x542F70u && a <= 0x5433C0u) || (a >= 0x549000u && a <= 0x54B8E0u && a != 0x54AC40u); }
bool takes_rna(u32 a) { return a >= 0x541AA8u && a <= 0x541CA0u; }
// The encoder and AHX pieces work on records the snapshots do not hold: their own sections and the random worlds.
bool sweep_skips(u32 a) {
    return (a >= 0x543470u && a <= 0x544850u) || (a >= 0x54D6B8u && a <= 0x54E568u && a != 0x54DE50u);
}
std::vector<u64> a0s_of(Machine& m, u32 a) {
    if (takes_tid(a)) return {0, 5, 8};
    if (takes_stm(a)) return {kStm, kStm + kStmSize, kStm + 2 * kStmSize, kStm + (kStmCount - 1) * kStmSize};
    if (takes_adxt(a)) return {kAdxt, kAdxt + kAdxtSize, 0};
    if (takes_rna(a)) return {r32(m, kAdxt + 12), kOut};
    if (a == 0x546010u) return {r32(m, kStm + 4)};
    if (a == 0x5416E8u || a == 0x541760u) return {kFmtUsrVsync};
    return {0, 1, kOut};
}

}  // namespace

TEST_CASE("game(libs8): every body equals its recompiled body on random worlds") {
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
            g_status = (rng() % 4 == 0) ? 8u : 4u;
            g_v0 = rng() % 3;
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += pr(*m, c.addr, args).stopped ? 1 : 0;
            ++total;
        }
    }
    g_v0 = 0;
    g_status = 4;
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The replay snapshots hold a set-up ADXM (setup count 1, thread mode 0, the safe / vsync / fs / main / mwidle ids),
// ADXT handles at 0x787570 (in use, state 3, +8 their ADXSTM record) and live ADXSTM records (b_5800: four, two
// reading). Every function runs on them with the record its role takes, second arguments from the values its
// branches test, the thread status WAIT / SUSPEND / RUN and the recorders returning 0, 1 or -1; each pair starts
// from the snapshot.
TEST_CASE("game(libs8): every body on the live ADXM, ADXT and ADXSTM state of the replay snapshots") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int runs = 0, stops = 0, used = 0;
    for (const char* dir : {"b_5800", "dorm_replay_4900", "climb_ref_17000"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        ++used;
        REQUIRE(r32(*m, kSetupCount) == 1u);
        REQUIRE(m->at(kStm)[0] == 1u);
        REQUIRE(m->at(kAdxt)[0] == 1u);
        REQUIRE(r32(*m, kAdxt + 8) == kStm);
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            if (sweep_skips(c.addr)) continue;
            for (u64 a0 : a0s_of(*m, c.addr))
                for (u64 a1 : {0ull, 5ull, 256ull, 0x7FFFFFFFull})
                    for (u32 st : {4u, 8u, 1u})
                        for (u64 v : {0ull, ~0ull}) {
                            if (st != 4u && !takes_tid(c.addr) && c.addr > 0x541760u) continue;  // thread status: ADXM only
                            g_status = st;
                            g_v0 = v;
                            if (trace) std::fprintf(stderr, "%s %s a0 %llx a1 %llx st %u v0 %llx\n", dir, c.name,
                                                    (unsigned long long)a0, (unsigned long long)a1, st, (unsigned long long)v);
                            HwCheck hw;
                            hw.gpr_in = {{GPR_T0, r32(*m, kStm + 4)}};  // a fifth argument: a live stream joint
                            const hgp::Run r = pr_base(*m, base, c.addr, Args{a0, a1, kOut, kOut + 0x100}, hw);
                            base.restore();
                            ++runs;
                            stops += r.stopped ? 1 : 0;
                        }
        }
    }
    g_v0 = 0;
    g_status = 4;
    MESSAGE(used << " snapshots, " << runs << " pairs, " << stops << " stopped identically");
}

// The thread helpers follow sceReferThreadStatus (ps2sdk: 1 RUN, 2 READY, 4 WAIT, 8 SUSPEND, 12 WAITSUSPEND,
// 16 DORMANT): wake only a waiting thread, resume only a suspended one, suspend only one that is not.
TEST_CASE("game(libs8): ADXM wakes, resumes and suspends by the thread status") {
    auto m = machine();
    if (!m) return;
    for (u32 st : {1u, 2u, 4u, 8u, 12u, 16u}) {
        g_status = st;
        const bool waiting = st == 4u || st == 12u, suspended = st == 8u || st == 12u;
        StandIns log;
        prv(*m, 0x540048u, {7, 0, 0, 0}, {}, &log);
        CHECK(log.calls_to(kWakeup) == (waiting ? 1u : 0u));
        CHECK(log.calls_to(kReferStatus) == 1u);
        const s32 resumed = sv(prv(*m, 0x5400B0u, {7, 0, 0, 0}, {}, &log));
        CHECK(log.calls_to(kResume) == (suspended ? 1u : 0u));
        CHECK(resumed == (suspended ? 7 : 0));
        const s32 susp = sv(prv(*m, 0x540118u, {7, 0, 0, 0}, {}, &log));
        CHECK(log.calls_to(kSuspend) == (suspended ? 0u : 1u));
        CHECK(susp == (suspended ? 0 : 7));
    }
    // a null id calls nothing (sub_540048 leaves $v0 as it was; the other two return 0)
    StandIns log;
    for (u32 a : {0x540048u, 0x5400B0u, 0x540118u}) {
        const u64 v = prv(*m, a, {0, 0, 0, 0}, {}, &log);
        if (a != 0x540048u) CHECK(v == 0u);
        CHECK(log.log.empty());
    }
    g_status = 4;
}

// The module counters and ADXM's setup count, on the ELF's own data.
TEST_CASE("game(libs8): ADXM setup count, thread mode and the module counters") {
    auto m = machine();
    if (!m) return;
    w32(*m, kSetupCount, 0);
    CHECK(prv(*m, 0x540560u, {0, 0, 0, 0}) == 0u);
    w32(*m, kSetupCount, 3);
    CHECK(prv(*m, 0x540560u, {0, 0, 0, 0}) == 1u);
    CHECK(sv(prv(*m, 0x540588u, {0, 0, 0, 0})) == 4);  // already set up: only counts
    CHECK(r32(*m, kSetupCount) == 4u);
    w32(*m, kThrdMode, 1);
    CHECK(prv(*m, 0x540550u, {0, 0, 0, 0}) == 1u);
    for (u32 a : {0u, 1u, 2u, 7u}) CHECK(prv(*m, 0x541610u, {a, 0, 0, 0}) == (a == 1u ? 1u : 2u));
    w32(*m, 0x790A18u, 5);
    CHECK(prv(*m, 0x543430u, {0, 0, 0, 0}) == 0u);
    CHECK(r32(*m, 0x790A18u) == 6u);
    CHECK(prv(*m, 0x543450u, {0, 0, 0, 0}) == 0u);
    CHECK(r32(*m, 0x790A18u) == 5u);
    // the exit requests: six 64-bit words at stride 16 become 1
    for (u32 i = 0; i < 6; ++i) std::memset(m->at(kExitReq + 16 * i), 0, 8);
    CHECK(prv(*m, 0x540718u, {0, 0, 0, 0}) == 1u);
    for (u32 i = 0; i < 6; ++i) CHECK(r64(*m, kExitReq + 16 * i) == 1u);
    // the print level: sub_541760 prints unless it is 2, sub_5416E8 only at 0. A skipped print returns at once; a
    // taken one enters vsprintf (which this build may not run to its end: then the pair stops there, identically)
    // and then scePrintf.
    for (u32 level : {0u, 1u, 2u}) {
        w32(*m, kPrintLevel, level);
        for (u32 fn : {0x541760u, 0x5416E8u}) {
            const bool prints = fn == 0x541760u ? level != 2u : level == 0u;
            StandIns log;
            const hgp::Run r = pr(*m, fn, {kFmtUsrVsync, 0x1000, 5, 0}, {}, &log);
            INFO(by_addr(fn).name << " level " << level << " " << r.what);
            if (prints) {
                // (in this build vsprintf's formatter reaches 0x504650, which is not emitted)
                CHECK(((r.stopped && r.stop_pc == 0x504650u) || log.calls_to(kScePrintf) == 1u));
            } else {
                CHECK_FALSE(r.stopped);
                CHECK(log.log.empty());
            }
        }
    }
}

// The ADXSTM accessors on the live records of b_5800 (record 0: reading, 1119 sectors from position 366).
TEST_CASE("game(libs8): the ADXSTM record accessors on a live stream") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot("b_5800");
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 rec = kStm, sectors = r32(*m, kStm + 20), bytes = r32(*m, kStm + 16);
    REQUIRE(sectors == 1119u);
    CHECK(prv(*m, 0x5470A0u, {rec, 0, 0, 0}) == bytes);
    CHECK(prv(*m, 0x5470E0u, {rec, 0, 0, 0}) == sectors);
    CHECK(prv(*m, 0x547068u, {rec, 0, 0, 0}) == bytes);
    CHECK(prv(*m, 0x5463A0u, {rec, 0, 0, 0}) == static_cast<u64>(static_cast<s8>(m->at(rec)[1])));
    CHECK(prv(*m, 0x546448u, {rec, 0, 0, 0}) == r32(*m, rec + 88));
    // the read position clamps to the sector count
    CHECK(prv(*m, 0x5463F0u, {rec, 5, 0, 0}) == 5u);
    CHECK(prv(*m, 0x5463F0u, {rec, 5000, 0, 0}) == sectors);
    CHECK(r32(*m, rec + 88) == sectors);
    CHECK(prv(*m, 0x546410u, {rec, 0, 0, 0}) == sectors);
    // the read end: a negative value means the whole file
    prv(*m, 0x546758u, {rec, ~0ull, 0, 0});
    CHECK(r32(*m, rec + 48) == sectors);
    prv(*m, 0x546758u, {rec, 9, 0, 0});
    CHECK(r32(*m, rec + 48) == 9u);
    // reset of the transfer state: status 2 with sectors, 3 for an empty file
    CHECK(prv(*m, 0x546460u, {rec, 0, 0, 0}) == 1u);
    CHECK(m->at(rec)[1] == 2u);
    CHECK(m->at(rec)[71] == 1u);
    w32(*m, rec + 20, 0);
    prv(*m, 0x546460u, {rec, 0, 0, 0});
    CHECK(m->at(rec)[1] == 3u);
    // the request cap, the callback and the pause byte
    CHECK(prv(*m, 0x547008u, {rec, 64, 0, 0}) == 1u);
    CHECK(r32(*m, rec + 44) == 64u);
    prv(*m, 0x546708u, {rec, 0x123450, 0x77, 0});
    CHECK(r32(*m, rec + 56) == 0x123450u);
    CHECK(r32(*m, rec + 60) == 0x77u);
    prv(*m, 0x547138u, {rec, 1, 0, 0});
    CHECK(m->at(rec)[68] == 1u);
    CHECK(prv(*m, 0x546FF8u, {rec, 3, 4, 0}) == 1u);
    CHECK(r32(*m, rec + 24) == 4u);
    CHECK(r32(*m, rec + 28) == 3u);
}

// ADXT's parameter checks: a null handle logs its E0208xxxx message and returns the documented value.
TEST_CASE("game(libs8): ADXT parameter errors and the clamped value at +70") {
    auto m = machine();
    if (!m) return;
    struct E {
        u32 addr;
        s32 ret;
    };
    for (const E& e : {E{0x549000u, -1}, E{0x549310u, 0}, E{0x549450u, 0}}) {
        StandIns log;
        CHECK(sv(prv(*m, e.addr, {0, 0, 0, 0}, {}, &log)) == e.ret);
        CHECK(log.calls_to(kAdxtErr) == 1u);
    }
    // sub_549390 clamps to -15..15 and passes it (or -128 while 0x787560 is set) to sub_541BB8, which stores it at the
    // output record +92 (PS2RNA mode 0 here: no guard)
    const u32 h = kOut, out = kOut + 0x400;
    std::memset(m->at(kOut), 0, 0x800);
    w32(*m, h + 12, out);
    w32(*m, 0x7A93F8u, 0);
    for (s32 v : {-40, -15, -3, 0, 9, 15, 16, 99}) {
        w32(*m, 0x787560u, 0);
        prv(*m, 0x549390u, {h, static_cast<u64>(static_cast<s64>(v)), 0, 0});
        const s32 want = v < -15 ? -15 : v > 15 ? 15 : v;
        s16 got;
        std::memcpy(&got, m->at(h + 70), 2);
        CHECK(got == want);
        CHECK(sv(r32(*m, out + 92)) == want);
        CHECK(sv(prv(*m, 0x549450u, {h, 0, 0, 0})) == want);
        w32(*m, 0x787560u, 1);
        prv(*m, 0x549390u, {h, static_cast<u64>(static_cast<s64>(v)), 0, 0});
        CHECK(sv(r32(*m, out + 92)) == -128);
    }
    // the 0x8001 header mark
    std::memset(m->at(kOut), 0, 0x10);
    m->at(kOut)[0] = 0x80;
    m->at(kOut)[1] = 0x01;
    CHECK(prv(*m, 0x54AC40u, {kOut, 16, kOut + 0x100, 0}) == 1u);
    CHECK(r32(*m, kOut + 0x100) == 16u);
    CHECK(prv(*m, 0x54AC40u, {kOut, 1, kOut + 0x100, 0}) == 0u);
    m->at(kOut)[1] = 0x02;
    CHECK(prv(*m, 0x54AC40u, {kOut, 16, kOut + 0x100, 0}) == 0u);
}

// The ADX / AHX cipher keys against a host model of the table walk (the ELF's tables at 0x7C11B8: 512 halfwords of
// results, then the multipliers by character), the stream size formula, the predictor step and the bit reader.
TEST_CASE("game(libs8): cipher keys, stream size, predictor step and bit reader against host models") {
    auto m = machine();
    if (!m) return;
    auto h16 = [&](u32 va) { s16 v; std::memcpy(&v, m->at(va), 2); return static_cast<s32>(v); };
    for (const char* key : {"a", "persona3", "ATLUS-P3FES", "0123456789abcdef"}) {
        const u32 len = static_cast<u32>(std::strlen(key));
        std::memset(m->at(kOut), 0, 0x200);
        std::memcpy(m->at(kOut), key, len);
        s32 want[3];
        for (int k = 0; k < 3; ++k) {
            s32 v = h16(kKeySeeds[k]);
            for (u32 i = 0; i < len; ++i) {
                const s32 p = v * h16(kKeyTable + 256 + 2 * static_cast<s8>(key[i]));
                v = h16(kKeyTable + 2 * (p % 1024));
            }
            want[k] = v;
        }
        for (u32 fn : {0x543470u, 0x54DE90u}) {
            CHECK(prv(*m, fn, {kOut, len, kOut + 0x100, kOut + 0x102}, {{GPR_T0, kOut + 0x104}}) == 0u);
            CHECK(h16(kOut + 0x100) == want[0]);
            CHECK(h16(kOut + 0x102) == want[1]);
            CHECK(h16(kOut + 0x104) == want[2]);
        }
    }
    // 18 bytes per 32 samples per channel, plus the header offset and 4
    for (s32 ch : {1, 2})
        for (s32 n : {0, 1, 31, 32, 33, 1000})
            CHECK(sv(prv(*m, 0x5436D0u, {static_cast<u64>(ch), 0x24, static_cast<u64>(n), 0})) ==
                  18 * ((n + 31) / 32) * ch + 0x24 + 4);
    // predictor: (c0 * h0 + c1 * h1) >> 12 plus the residual, saturated; the history shifts
    std::mt19937 rng{8};
    for (int i = 0; i < 64; ++i) {
        const u32 p = kOut + 0x300;
        // coefficients and history within +-0x4000 keep the 32-bit sum of products from wrapping
        auto q = [&] { return static_cast<s16>(static_cast<s32>(rng() % 0x8000) - 0x4000); };
        const s16 c0 = q(), c1 = q(), h0 = q(), h1 = q(), res = static_cast<s16>(rng());
        w16(*m, p + 4, static_cast<u16>(c0));
        w16(*m, p + 6, static_cast<u16>(c1));
        w16(*m, p + 8, static_cast<u16>(h0));
        w16(*m, p + 10, static_cast<u16>(h1));
        s32 v = ((c0 * h0 + c1 * h1) >> 12) + res;
        v = v > 0x7FFF ? 0x7FFF : v < -0x8000 ? -0x8000 : v;
        CHECK(sv(prv(*m, 0x543B78u, {p, static_cast<u64>(static_cast<u16>(res)), 0, 0})) == v);
        CHECK(h16(p + 8) == v);
        CHECK(h16(p + 10) == h0);
    }
    // bit reader with enough bits in the window: (window >> (count - n)) & mask[n], consumed += n
    for (u32 n : {1u, 4u, 7u, 12u, 20u}) {
        const u32 br = kOut + 0x380;
        std::memset(m->at(br), 0, 44);
        w32(*m, br + 8, 0xA5C3F00Fu);
        w32(*m, br + 12, 24);
        w32(*m, br + 16, 100);
        const u32 want = (0xA5C3F00Fu >> (24 - n)) & r32(*m, kBitMask + 4 * n);
        CHECK(prv(*m, 0x54DB38u, {br, n, 0, 0}) == want);
        CHECK(r32(*m, br + 12) == 24 - n);
        CHECK(r32(*m, br + 16) == 100 + n);
        CHECK(prv(*m, 0x54DBE8u, {br, 0, 0, 0}) == 100 + n);
    }
    MESSAGE(summary());
}

#else

TEST_CASE("game(libs8): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
