// Phase 5 slice libs8: CRI middleware 0x540048-0x54E568 (ADXM threads, PS2RNA guards, ADXT, an ADX encoder,
// ADXSTM, AHX pieces); game/src/cri/libs8.cpp. Register-ABI bodies: arguments in $a0.., the result in $v0.
// [brackets] hold proposed names (symbols/deltas/libs8.sym); the module tag follows.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

void sub_540048(EEContext& ctx);  // 0x540048 [adxm_WakeupThrd] ADXM
void sub_540098(EEContext& ctx);  // 0x540098 [adxm_SleepThrd] ADXM
void sub_5400B0(EEContext& ctx);  // 0x5400B0 [adxm_ResumeThrd] ADXM
void sub_540118(EEContext& ctx);  // 0x540118 [adxm_SuspendThrd] ADXM
void adxm_SetupSafeThrd(EEContext& ctx);  // 0x540178 ADXM
void adxm_SetupUsrVsyncThrd(EEContext& ctx);  // 0x540220 ADXM
void adxm_SetupVsyncThrd(EEContext& ctx);  // 0x5402D8 ADXM
void adxm_SetupFsThrd(EEContext& ctx);  // 0x540360 ADXM
void adxm_SetupMwIdleThrd(EEContext& ctx);  // 0x5403E8 ADXM
void adxm_SetupUsrIdleThrd(EEContext& ctx);  // 0x540480 ADXM
void __errno(EEContext& ctx);  // 0x540550 [adxm_GetThrdMode] ADXM
void sub_540560(EEContext& ctx);  // 0x540560 [adxm_IsSetup] ADXM
void sub_540570(EEContext& ctx);  // 0x540570 Thunk
void ADXM_SetupThrd(EEContext& ctx);  // 0x540588 ADXM
void sub_540718(EEContext& ctx);  // 0x540718 ADXM
void sub_540768(EEContext& ctx);  // 0x540768 ADXM
void sub_540800(EEContext& ctx);  // 0x540800 ADXM
void sub_5408D0(EEContext& ctx);  // 0x5408D0 ADXM
void sub_5409A0(EEContext& ctx);  // 0x5409A0 ADXM
void sub_540A70(EEContext& ctx);  // 0x540A70 ADXM
void sub_540BA0(EEContext& ctx);  // 0x540BA0 ADXM
void sub_540C70(EEContext& ctx);  // 0x540C70 ADXM
void sub_540D40(EEContext& ctx);  // 0x540D40 Thunk
void sub_540D58(EEContext& ctx);  // 0x540D58 Thunk
void ADXPS2_ExecVint(EEContext& ctx);  // 0x540D80
void sub_540EA8(EEContext& ctx);  // 0x540EA8
void sub_540ED8(EEContext& ctx);  // 0x540ED8 ADXM
void sub_540F60(EEContext& ctx);  // 0x540F60 ADXM
void sub_540FE0(EEContext& ctx);  // 0x540FE0 ADXM
void sub_5414E0(EEContext& ctx);  // 0x5414E0 ADXM
void sub_541510(EEContext& ctx);  // 0x541510 ADXM
void sub_541610(EEContext& ctx);  // 0x541610
void sub_5416E8(EEContext& ctx);  // 0x5416E8 Debug print
void sub_541760(EEContext& ctx);  // 0x541760 Debug print
void sub_5417E0(EEContext& ctx);  // 0x5417E0 Thunk
void sub_5419C0(EEContext& ctx);  // 0x5419C0
void sub_5419D8(EEContext& ctx);  // 0x5419D8 Thunk
void sub_5419F0(EEContext& ctx);  // 0x5419F0
void expl_1(EEContext& ctx);  // 0x541AA8 PS2RNA
void sub_541BB8(EEContext& ctx);  // 0x541BB8 PS2RNA
void sub_541C60(EEContext& ctx);  // 0x541C60 Thunk
void sub_541C88(EEContext& ctx);  // 0x541C88 PS2RNA
void sub_541CA0(EEContext& ctx);  // 0x541CA0 PS2RNA
void sub_541D00(EEContext& ctx);  // 0x541D00
void sub_541D18(EEContext& ctx);  // 0x541D18
void sub_541D30(EEContext& ctx);  // 0x541D30
void sub_541DA0(EEContext& ctx);  // 0x541DA0 Finish
void sub_542F70(EEContext& ctx);  // 0x542F70
void sub_542FA8(EEContext& ctx);  // 0x542FA8
void sub_542FC0(EEContext& ctx);  // 0x542FC0 Thunk
void sub_543020(EEContext& ctx);  // 0x543020
void sub_543038(EEContext& ctx);  // 0x543038
void sub_543328(EEContext& ctx);  // 0x543328
void sub_543380(EEContext& ctx);  // 0x543380
void sub_543388(EEContext& ctx);  // 0x543388
void sub_5433C0(EEContext& ctx);  // 0x5433C0
void sub_543430(EEContext& ctx);  // 0x543430 ADX encoder
void sub_543450(EEContext& ctx);  // 0x543450 ADX encoder
void sub_543470(EEContext& ctx);  // 0x543470 [adxenc_CalcKey] ADX encoder
void sub_5436D0(EEContext& ctx);  // 0x5436D0 ADX encoder
void sub_5438C0(EEContext& ctx);  // 0x5438C0 ADX encoder
void sub_543AA8(EEContext& ctx);  // 0x543AA8 ADX encoder
void sub_543B40(EEContext& ctx);  // 0x543B40
void sub_543B50(EEContext& ctx);  // 0x543B50
void sub_543B60(EEContext& ctx);  // 0x543B60
void sub_543B78(EEContext& ctx);  // 0x543B78
void sub_543BF0(EEContext& ctx);  // 0x543BF0 ADX encoder
void sub_543C90(EEContext& ctx);  // 0x543C90 ADX encoder
void sub_543CC8(EEContext& ctx);  // 0x543CC8
void sub_543CD8(EEContext& ctx);  // 0x543CD8
void sub_543D30(EEContext& ctx);  // 0x543D30
void sub_543D40(EEContext& ctx);  // 0x543D40
void sub_543E28(EEContext& ctx);  // 0x543E28
void sub_543EC0(EEContext& ctx);  // 0x543EC0
void sub_543EF8(EEContext& ctx);  // 0x543EF8
void sub_543F08(EEContext& ctx);  // 0x543F08 ADX encoder
void sub_544078(EEContext& ctx);  // 0x544078 ADX encoder
void sub_5442D8(EEContext& ctx);  // 0x5442D8 ADX encoder
void sub_544560(EEContext& ctx);  // 0x544560 ADX encoder
void sub_544720(EEContext& ctx);  // 0x544720 ADX encoder
void sub_544850(EEContext& ctx);  // 0x544850 ADX encoder
void sub_545BF0(EEContext& ctx);  // 0x545BF0 Thunk
void atan2l_2(EEContext& ctx);  // 0x545C08 Thunk
void cosl_2(EEContext& ctx);  // 0x545C20 Thunk
void coshl_2(EEContext& ctx);  // 0x545C38
void sub_545C40(EEContext& ctx);  // 0x545C40
void sub_545C78(EEContext& ctx);  // 0x545C78 ADXSTM init
void sub_545D18(EEContext& ctx);  // 0x545D18 ADXSTM
void sub_545E20(EEContext& ctx);  // 0x545E20 ADXSTM
void sub_545EF8(EEContext& ctx);  // 0x545EF8 ADXSTM
void adxstm_Create(EEContext& ctx);  // 0x546010 ADXSTM
void sub_546088(EEContext& ctx);  // 0x546088 ADXSTM
void sub_546150(EEContext& ctx);  // 0x546150 ADXSTM
void sub_5461C8(EEContext& ctx);  // 0x5461C8 ADXSTM
void sub_546238(EEContext& ctx);  // 0x546238 ADXSTM
void sub_5462A0(EEContext& ctx);  // 0x5462A0 ADXSTM
void sub_5462E0(EEContext& ctx);  // 0x5462E0 ADXSTM
void sub_546310(EEContext& ctx);  // 0x546310 ADXSTM
void sub_5463A0(EEContext& ctx);  // 0x5463A0 ADXSTM
void sub_5463F0(EEContext& ctx);  // 0x5463F0 ADXSTM
void sub_546410(EEContext& ctx);  // 0x546410 ADXSTM
void sub_546448(EEContext& ctx);  // 0x546448 ADXSTM
void sub_546460(EEContext& ctx);  // 0x546460 ADXSTM
void sub_5464D0(EEContext& ctx);  // 0x5464D0 ADXSTM
void sub_546510(EEContext& ctx);  // 0x546510 ADXSTM
void sub_546558(EEContext& ctx);  // 0x546558 ADXSTM
void sub_5465D0(EEContext& ctx);  // 0x5465D0 ADXSTM
void sub_546638(EEContext& ctx);  // 0x546638 ADXSTM
void sub_546668(EEContext& ctx);  // 0x546668 ADXSTM
void sub_546708(EEContext& ctx);  // 0x546708 ADXSTM
void sub_546758(EEContext& ctx);  // 0x546758 ADXSTM
void adxstmf_ExecRead(EEContext& ctx);  // 0x546788
void ADXSTMF_ExecHndl(EEContext& ctx);  // 0x546BB0
void sub_546D90(EEContext& ctx);  // 0x546D90 ADXSTM
void sub_546DB8(EEContext& ctx);  // 0x546DB8 ADXSTM
void sub_546E38(EEContext& ctx);  // 0x546E38 ADXSTM
void adxstmf_ExecServer(EEContext& ctx);  // 0x546E60 ADXSTM
void sub_546FF8(EEContext& ctx);  // 0x546FF8 ADXSTM
void sub_547008(EEContext& ctx);  // 0x547008 ADXSTM
void sub_547050(EEContext& ctx);  // 0x547050 ADXSTM
void sub_547068(EEContext& ctx);  // 0x547068 ADXSTM
void sub_5470A0(EEContext& ctx);  // 0x5470A0 ADXSTM
void sub_5470A8(EEContext& ctx);  // 0x5470A8 ADXSTM
void _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_2(EEContext& ctx);  // 0x5470E0 ADXSTM
void sub_547138(EEContext& ctx);  // 0x547138 ADXSTM
void sub_547178(EEContext& ctx);  // 0x547178 ADXSTM
void sub_547318(EEContext& ctx);  // 0x547318 ADXSTM
void sub_547358(EEContext& ctx);  // 0x547358 ADXSTM
void sub_547558(EEContext& ctx);  // 0x547558 ADXSTM
void ADXPS2_SetupDvdFs(EEContext& ctx);  // 0x547668 ADXPS2
void sub_548278(EEContext& ctx);  // 0x548278
void sub_549000(EEContext& ctx);  // 0x549000 ADXT
void sub_549310(EEContext& ctx);  // 0x549310 ADXT
void sub_549390(EEContext& ctx);  // 0x549390 ADXT
void sub_549450(EEContext& ctx);  // 0x549450 ADXT
void sub_54AC40(EEContext& ctx);  // 0x54AC40
void sub_54B3F0(EEContext& ctx);  // 0x54B3F0 ADXT
void sub_54B8E0(EEContext& ctx);  // 0x54B8E0 ADXT
void sub_54CFE8(EEContext& ctx);  // 0x54CFE8
void sub_54D528(EEContext& ctx);  // 0x54D528
void sub_54D6B8(EEContext& ctx);  // 0x54D6B8 AHX
void sub_54D7E8(EEContext& ctx);  // 0x54D7E8 AHX
void sub_54D898(EEContext& ctx);  // 0x54D898
void sub_54DB38(EEContext& ctx);  // 0x54DB38
void sub_54DBE8(EEContext& ctx);  // 0x54DBE8
void sub_54DBF0(EEContext& ctx);  // 0x54DBF0
void sub_54DE50(EEContext& ctx);  // 0x54DE50 AHX
void sub_54DE90(EEContext& ctx);  // 0x54DE90 [ahx_CalcKey] AHX
void sub_54E2C0(EEContext& ctx);  // 0x54E2C0 AHX
void sub_54E568(EEContext& ctx);  // 0x54E568 AHX

}  // namespace p3fes::game
