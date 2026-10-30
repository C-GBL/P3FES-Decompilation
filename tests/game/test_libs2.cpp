// Pair tests for slice libs2 (game/src/cri/libs2_acss_*.cpp: CRI ACSS, the sound layer the BGM manager drives). Every
// body against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and cycle count at
// every check point and at the return / stop, all 32 MiB of RAM (the dead stack too), the scratchpad, the BIOS window,
// the bus log. The drivers below ACSS that this test binary does not emit (AIXP, ADXT's own drivers PS2RNA / ADXSTM /
// ADXB / the list streamer, the SVM callbacks, the ADX error reporters, libm's pow) are stand-ins (stand_ins.h):
// recorders, the host's pow, the reporters keeping their texts; a stand-in's entry check point holds the call's
// arguments, so the pair compares the calls too. On top of the generic sweep (random worlds):
//   * every function on the live server, sounds, faders and back ends of four replay snapshots (dorm, battle x2,
//     fusion);
//   * the fader: volume <-> level against the formulas, the step, a whole life (delay, fade, hold, both callbacks,
//     idle), reverse;
//   * the back ends: the ELF's two method tables, the ADX status map through the live player, the resets, the
//     track-0-only and AIX accessor rules;
//   * the sound: the four start requests stored, the guards of an uninitialised sound, setters / getters through the
//     public thunks, the ADXT / AIXP getters by mode, the AIX track volume getter, CalcWorkSize on the game's own
//     configurations against the formula;
//   * the server: the 16 slots, 'Can't create sound any more' / 'Not initialized', destroy frees the slot; the ducking
//     object's setters, frames-left rules, reset, and a restore run to idle on the battle snapshot.
// Random draws are separate statements (MSVC and clang evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs2.h"

#include <algorithm>
#include <cmath>
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
void fn_atan2l_00531998(EEContext&);  // generated body
void fn_atan2l_00531998__recomp(EEContext&);  // recompiled
void fn_cosl_005319b0(EEContext&);  // generated body
void fn_cosl_005319b0__recomp(EEContext&);  // recompiled
void fn_coshl_005319c8(EEContext&);  // generated body
void fn_coshl_005319c8__recomp(EEContext&);  // recompiled
void fn_expl_005319e0(EEContext&);  // generated body
void fn_expl_005319e0__recomp(EEContext&);  // recompiled
void fn_hypotf_005319f8(EEContext&);  // generated body
void fn_hypotf_005319f8__recomp(EEContext&);  // recompiled
void fn_sub_531A10_00531a10(EEContext&);  // generated body
void fn_sub_531A10_00531a10__recomp(EEContext&);  // recompiled
void fn_sub_531A28_00531a28(EEContext&);  // generated body
void fn_sub_531A28_00531a28__recomp(EEContext&);  // recompiled
void fn_sub_531A90_00531a90(EEContext&);  // generated body
void fn_sub_531A90_00531a90__recomp(EEContext&);  // recompiled
void fn_sub_531AB8_00531ab8(EEContext&);  // generated body
void fn_sub_531AB8_00531ab8__recomp(EEContext&);  // recompiled
void fn_sub_531AC0_00531ac0(EEContext&);  // generated body
void fn_sub_531AC0_00531ac0__recomp(EEContext&);  // recompiled
void fn_sub_531AC8_00531ac8(EEContext&);  // generated body
void fn_sub_531AC8_00531ac8__recomp(EEContext&);  // recompiled
void fn_sub_531AD0_00531ad0(EEContext&);  // generated body
void fn_sub_531AD0_00531ad0__recomp(EEContext&);  // recompiled
void fn_sub_531B00_00531b00(EEContext&);  // generated body
void fn_sub_531B00_00531b00__recomp(EEContext&);  // recompiled
void fn_sub_531BC0_00531bc0(EEContext&);  // generated body
void fn_sub_531BC0_00531bc0__recomp(EEContext&);  // recompiled
void fn_sub_531C00_00531c00(EEContext&);  // generated body
void fn_sub_531C00_00531c00__recomp(EEContext&);  // recompiled
void fn_sub_531D40_00531d40(EEContext&);  // generated body
void fn_sub_531D40_00531d40__recomp(EEContext&);  // recompiled
void fn_sub_531D48_00531d48(EEContext&);  // generated body
void fn_sub_531D48_00531d48__recomp(EEContext&);  // recompiled
void fn_sub_531D58_00531d58(EEContext&);  // generated body
void fn_sub_531D58_00531d58__recomp(EEContext&);  // recompiled
void fn_sub_531D68_00531d68(EEContext&);  // generated body
void fn_sub_531D68_00531d68__recomp(EEContext&);  // recompiled
void fn_sub_531DD8_00531dd8(EEContext&);  // generated body
void fn_sub_531DD8_00531dd8__recomp(EEContext&);  // recompiled
void fn_sub_531E60_00531e60(EEContext&);  // generated body
void fn_sub_531E60_00531e60__recomp(EEContext&);  // recompiled
void fn_sub_531F90_00531f90(EEContext&);  // generated body
void fn_sub_531F90_00531f90__recomp(EEContext&);  // recompiled
void fn_sub_5320B8_005320b8(EEContext&);  // generated body
void fn_sub_5320B8_005320b8__recomp(EEContext&);  // recompiled
void fn_sub_5320E8_005320e8(EEContext&);  // generated body
void fn_sub_5320E8_005320e8__recomp(EEContext&);  // recompiled
void fn_sub_532118_00532118(EEContext&);  // generated body
void fn_sub_532118_00532118__recomp(EEContext&);  // recompiled
void fn_sub_532180_00532180(EEContext&);  // generated body
void fn_sub_532180_00532180__recomp(EEContext&);  // recompiled
void fn_sub_5321A8_005321a8(EEContext&);  // generated body
void fn_sub_5321A8_005321a8__recomp(EEContext&);  // recompiled
void fn_sub_532230_00532230(EEContext&);  // generated body
void fn_sub_532230_00532230__recomp(EEContext&);  // recompiled
void fn_sub_532268_00532268(EEContext&);  // generated body
void fn_sub_532268_00532268__recomp(EEContext&);  // recompiled
void fn_sub_532280_00532280(EEContext&);  // generated body
void fn_sub_532280_00532280__recomp(EEContext&);  // recompiled
void fn_sub_532298_00532298(EEContext&);  // generated body
void fn_sub_532298_00532298__recomp(EEContext&);  // recompiled
void fn_sub_5322B0_005322b0(EEContext&);  // generated body
void fn_sub_5322B0_005322b0__recomp(EEContext&);  // recompiled
void fn_sub_5322C8_005322c8(EEContext&);  // generated body
void fn_sub_5322C8_005322c8__recomp(EEContext&);  // recompiled
void fn_sub_5322E0_005322e0(EEContext&);  // generated body
void fn_sub_5322E0_005322e0__recomp(EEContext&);  // recompiled
void fn_sub_5322F8_005322f8(EEContext&);  // generated body
void fn_sub_5322F8_005322f8__recomp(EEContext&);  // recompiled
void fn_sub_532310_00532310(EEContext&);  // generated body
void fn_sub_532310_00532310__recomp(EEContext&);  // recompiled
void fn_sub_532380_00532380(EEContext&);  // generated body
void fn_sub_532380_00532380__recomp(EEContext&);  // recompiled
void fn_sub_5323A8_005323a8(EEContext&);  // generated body
void fn_sub_5323A8_005323a8__recomp(EEContext&);  // recompiled
void fn_sub_5323C0_005323c0(EEContext&);  // generated body
void fn_sub_5323C0_005323c0__recomp(EEContext&);  // recompiled
void fn_sub_5323F0_005323f0(EEContext&);  // generated body
void fn_sub_5323F0_005323f0__recomp(EEContext&);  // recompiled
void fn_sub_532420_00532420(EEContext&);  // generated body
void fn_sub_532420_00532420__recomp(EEContext&);  // recompiled
void fn_sub_532438_00532438(EEContext&);  // generated body
void fn_sub_532438_00532438__recomp(EEContext&);  // recompiled
void fn_sub_532440_00532440(EEContext&);  // generated body
void fn_sub_532440_00532440__recomp(EEContext&);  // recompiled
void fn_sub_532458_00532458(EEContext&);  // generated body
void fn_sub_532458_00532458__recomp(EEContext&);  // recompiled
void fn_sub_5324C0_005324c0(EEContext&);  // generated body
void fn_sub_5324C0_005324c0__recomp(EEContext&);  // recompiled
void fn_sub_5324E8_005324e8(EEContext&);  // generated body
void fn_sub_5324E8_005324e8__recomp(EEContext&);  // recompiled
void fn_sub_532580_00532580(EEContext&);  // generated body
void fn_sub_532580_00532580__recomp(EEContext&);  // recompiled
void fn_sub_5325B8_005325b8(EEContext&);  // generated body
void fn_sub_5325B8_005325b8__recomp(EEContext&);  // recompiled
void fn_sub_5325D8_005325d8(EEContext&);  // generated body
void fn_sub_5325D8_005325d8__recomp(EEContext&);  // recompiled
void fn_sub_5325F0_005325f0(EEContext&);  // generated body
void fn_sub_5325F0_005325f0__recomp(EEContext&);  // recompiled
void fn_sub_532608_00532608(EEContext&);  // generated body
void fn_sub_532608_00532608__recomp(EEContext&);  // recompiled
void fn_sub_532628_00532628(EEContext&);  // generated body
void fn_sub_532628_00532628__recomp(EEContext&);  // recompiled
void fn_sub_532640_00532640(EEContext&);  // generated body
void fn_sub_532640_00532640__recomp(EEContext&);  // recompiled
void fn_sub_532658_00532658(EEContext&);  // generated body
void fn_sub_532658_00532658__recomp(EEContext&);  // recompiled
void fn_sub_532670_00532670(EEContext&);  // generated body
void fn_sub_532670_00532670__recomp(EEContext&);  // recompiled
void fn_sub_532688_00532688(EEContext&);  // generated body
void fn_sub_532688_00532688__recomp(EEContext&);  // recompiled
void fn_sub_5326F0_005326f0(EEContext&);  // generated body
void fn_sub_5326F0_005326f0__recomp(EEContext&);  // recompiled
void fn_sub_532718_00532718(EEContext&);  // generated body
void fn_sub_532718_00532718__recomp(EEContext&);  // recompiled
void fn_sub_532740_00532740(EEContext&);  // generated body
void fn_sub_532740_00532740__recomp(EEContext&);  // recompiled
void fn_sub_532748_00532748(EEContext&);  // generated body
void fn_sub_532748_00532748__recomp(EEContext&);  // recompiled
void fn_sub_532760_00532760(EEContext&);  // generated body
void fn_sub_532760_00532760__recomp(EEContext&);  // recompiled
void fn_sub_532768_00532768(EEContext&);  // generated body
void fn_sub_532768_00532768__recomp(EEContext&);  // recompiled
void fn_sub_532788_00532788(EEContext&);  // generated body
void fn_sub_532788_00532788__recomp(EEContext&);  // recompiled
void fn_sub_5327F0_005327f0(EEContext&);  // generated body
void fn_sub_5327F0_005327f0__recomp(EEContext&);  // recompiled
void fn_sub_532818_00532818(EEContext&);  // generated body
void fn_sub_532818_00532818__recomp(EEContext&);  // recompiled
void fn_sub_532D30_00532d30(EEContext&);  // generated body
void fn_sub_532D30_00532d30__recomp(EEContext&);  // recompiled
void fn_sub_532E08_00532e08(EEContext&);  // generated body
void fn_sub_532E08_00532e08__recomp(EEContext&);  // recompiled
void fn_sub_532E10_00532e10(EEContext&);  // generated body
void fn_sub_532E10_00532e10__recomp(EEContext&);  // recompiled
void fn_sub_532E70_00532e70(EEContext&);  // generated body
void fn_sub_532E70_00532e70__recomp(EEContext&);  // recompiled
void fn_sub_532EC0_00532ec0(EEContext&);  // generated body
void fn_sub_532EC0_00532ec0__recomp(EEContext&);  // recompiled
void fn_sub_532F10_00532f10(EEContext&);  // generated body
void fn_sub_532F10_00532f10__recomp(EEContext&);  // recompiled
void fn_sub_532F60_00532f60(EEContext&);  // generated body
void fn_sub_532F60_00532f60__recomp(EEContext&);  // recompiled
void fn_sub_5330A8_005330a8(EEContext&);  // generated body
void fn_sub_5330A8_005330a8__recomp(EEContext&);  // recompiled
void fn_sub_533160_00533160(EEContext&);  // generated body
void fn_sub_533160_00533160__recomp(EEContext&);  // recompiled
void fn_sub_5331A8_005331a8(EEContext&);  // generated body
void fn_sub_5331A8_005331a8__recomp(EEContext&);  // recompiled
void fn_sub_5331F0_005331f0(EEContext&);  // generated body
void fn_sub_5331F0_005331f0__recomp(EEContext&);  // recompiled
void fn_sub_533230_00533230(EEContext&);  // generated body
void fn_sub_533230_00533230__recomp(EEContext&);  // recompiled
void fn_sub_533238_00533238(EEContext&);  // generated body
void fn_sub_533238_00533238__recomp(EEContext&);  // recompiled
void fn_sub_533340_00533340(EEContext&);  // generated body
void fn_sub_533340_00533340__recomp(EEContext&);  // recompiled
void fn__ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv_00533450(EEContext&);  // generated body
void fn__ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv_00533450__recomp(EEContext&);  // recompiled
void fn_sub_5334A8_005334a8(EEContext&);  // generated body
void fn_sub_5334A8_005334a8__recomp(EEContext&);  // recompiled
void fn_sub_533570_00533570(EEContext&);  // generated body
void fn_sub_533570_00533570__recomp(EEContext&);  // recompiled
void fn_sub_533578_00533578(EEContext&);  // generated body
void fn_sub_533578_00533578__recomp(EEContext&);  // recompiled
void fn_sub_533580_00533580(EEContext&);  // generated body
void fn_sub_533580_00533580__recomp(EEContext&);  // recompiled
void fn__ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0_00533590(EEContext&);  // generated body
void fn__ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0_00533590__recomp(EEContext&);  // recompiled
void fn_sub_5335A0_005335a0(EEContext&);  // generated body
void fn_sub_5335A0_005335a0__recomp(EEContext&);  // recompiled
void fn_sub_5335B0_005335b0(EEContext&);  // generated body
void fn_sub_5335B0_005335b0__recomp(EEContext&);  // recompiled
void fn_sub_5336C0_005336c0(EEContext&);  // generated body
void fn_sub_5336C0_005336c0__recomp(EEContext&);  // recompiled
void fn_sub_5337A8_005337a8(EEContext&);  // generated body
void fn_sub_5337A8_005337a8__recomp(EEContext&);  // recompiled
void fn_sub_533808_00533808(EEContext&);  // generated body
void fn_sub_533808_00533808__recomp(EEContext&);  // recompiled
void fn_sub_533880_00533880(EEContext&);  // generated body
void fn_sub_533880_00533880__recomp(EEContext&);  // recompiled
void fn_sub_533900_00533900(EEContext&);  // generated body
void fn_sub_533900_00533900__recomp(EEContext&);  // recompiled
void fn_sub_533950_00533950(EEContext&);  // generated body
void fn_sub_533950_00533950__recomp(EEContext&);  // recompiled
void fn_sub_5339A8_005339a8(EEContext&);  // generated body
void fn_sub_5339A8_005339a8__recomp(EEContext&);  // recompiled
void fn_sub_533A18_00533a18(EEContext&);  // generated body
void fn_sub_533A18_00533a18__recomp(EEContext&);  // recompiled
void fn_sub_533A88_00533a88(EEContext&);  // generated body
void fn_sub_533A88_00533a88__recomp(EEContext&);  // recompiled
void fn_sub_533AC8_00533ac8(EEContext&);  // generated body
void fn_sub_533AC8_00533ac8__recomp(EEContext&);  // recompiled
void fn_sub_533CA0_00533ca0(EEContext&);  // generated body
void fn_sub_533CA0_00533ca0__recomp(EEContext&);  // recompiled
void fn_sub_533CA8_00533ca8(EEContext&);  // generated body
void fn_sub_533CA8_00533ca8__recomp(EEContext&);  // recompiled
void fn_sub_533CC0_00533cc0(EEContext&);  // generated body
void fn_sub_533CC0_00533cc0__recomp(EEContext&);  // recompiled
void fn_sub_533CD0_00533cd0(EEContext&);  // generated body
void fn_sub_533CD0_00533cd0__recomp(EEContext&);  // recompiled
void fn_sub_533E98_00533e98(EEContext&);  // generated body
void fn_sub_533E98_00533e98__recomp(EEContext&);  // recompiled
void fn_sub_533F10_00533f10(EEContext&);  // generated body
void fn_sub_533F10_00533f10__recomp(EEContext&);  // recompiled
void fn_sub_534010_00534010(EEContext&);  // generated body
void fn_sub_534010_00534010__recomp(EEContext&);  // recompiled
void fn_sub_534308_00534308(EEContext&);  // generated body
void fn_sub_534308_00534308__recomp(EEContext&);  // recompiled
void fn_sub_5343D8_005343d8(EEContext&);  // generated body
void fn_sub_5343D8_005343d8__recomp(EEContext&);  // recompiled
void fn_sub_534488_00534488(EEContext&);  // generated body
void fn_sub_534488_00534488__recomp(EEContext&);  // recompiled
void fn_sub_534530_00534530(EEContext&);  // generated body
void fn_sub_534530_00534530__recomp(EEContext&);  // recompiled
void fn_sub_534538_00534538(EEContext&);  // generated body
void fn_sub_534538_00534538__recomp(EEContext&);  // recompiled
void fn_sub_534678_00534678(EEContext&);  // generated body
void fn_sub_534678_00534678__recomp(EEContext&);  // recompiled
void fn_sub_534728_00534728(EEContext&);  // generated body
void fn_sub_534728_00534728__recomp(EEContext&);  // recompiled
void fn_sub_5347C0_005347c0(EEContext&);  // generated body
void fn_sub_5347C0_005347c0__recomp(EEContext&);  // recompiled
void fn_sub_534888_00534888(EEContext&);  // generated body
void fn_sub_534888_00534888__recomp(EEContext&);  // recompiled
void fn_sub_534960_00534960(EEContext&);  // generated body
void fn_sub_534960_00534960__recomp(EEContext&);  // recompiled
void fn_sub_5349C8_005349c8(EEContext&);  // generated body
void fn_sub_5349C8_005349c8__recomp(EEContext&);  // recompiled
void fn_sub_5349F8_005349f8(EEContext&);  // generated body
void fn_sub_5349F8_005349f8__recomp(EEContext&);  // recompiled
void fn_sub_534A60_00534a60(EEContext&);  // generated body
void fn_sub_534A60_00534a60__recomp(EEContext&);  // recompiled
void fn_sub_534A88_00534a88(EEContext&);  // generated body
void fn_sub_534A88_00534a88__recomp(EEContext&);  // recompiled
void fn_sub_534B60_00534b60(EEContext&);  // generated body
void fn_sub_534B60_00534b60__recomp(EEContext&);  // recompiled
void fn_sub_534C58_00534c58(EEContext&);  // generated body
void fn_sub_534C58_00534c58__recomp(EEContext&);  // recompiled
void fn_sub_534C98_00534c98(EEContext&);  // generated body
void fn_sub_534C98_00534c98__recomp(EEContext&);  // recompiled
void fn_sub_534DB0_00534db0(EEContext&);  // generated body
void fn_sub_534DB0_00534db0__recomp(EEContext&);  // recompiled
void fn_sub_535050_00535050(EEContext&);  // generated body
void fn_sub_535050_00535050__recomp(EEContext&);  // recompiled
void fn_sub_5350D0_005350d0(EEContext&);  // generated body
void fn_sub_5350D0_005350d0__recomp(EEContext&);  // recompiled
void fn_sub_535170_00535170(EEContext&);  // generated body
void fn_sub_535170_00535170__recomp(EEContext&);  // recompiled
void fn_sub_535178_00535178(EEContext&);  // generated body
void fn_sub_535178_00535178__recomp(EEContext&);  // recompiled
void fn_sub_5351B0_005351b0(EEContext&);  // generated body
void fn_sub_5351B0_005351b0__recomp(EEContext&);  // recompiled
void fn_sub_5351C0_005351c0(EEContext&);  // generated body
void fn_sub_5351C0_005351c0__recomp(EEContext&);  // recompiled
void fn_sub_5351E8_005351e8(EEContext&);  // generated body
void fn_sub_5351E8_005351e8__recomp(EEContext&);  // recompiled
void fn_sub_535250_00535250(EEContext&);  // generated body
void fn_sub_535250_00535250__recomp(EEContext&);  // recompiled
void fn_sub_535278_00535278(EEContext&);  // generated body
void fn_sub_535278_00535278__recomp(EEContext&);  // recompiled
void fn_sub_5352F8_005352f8(EEContext&);  // generated body
void fn_sub_5352F8_005352f8__recomp(EEContext&);  // recompiled
void fn_sub_535348_00535348(EEContext&);  // generated body
void fn_sub_535348_00535348__recomp(EEContext&);  // recompiled
void fn_sub_535350_00535350(EEContext&);  // generated body
void fn_sub_535350_00535350__recomp(EEContext&);  // recompiled
void fn_sub_535358_00535358(EEContext&);  // generated body
void fn_sub_535358_00535358__recomp(EEContext&);  // recompiled
void fn_sub_535388_00535388(EEContext&);  // generated body
void fn_sub_535388_00535388__recomp(EEContext&);  // recompiled
void fn_sub_535390_00535390(EEContext&);  // generated body
void fn_sub_535390_00535390__recomp(EEContext&);  // recompiled
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398(EEContext&);  // generated body
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398__recomp(EEContext&);  // recompiled
void fn_sub_5353A0_005353a0(EEContext&);  // generated body
void fn_sub_5353A0_005353a0__recomp(EEContext&);  // recompiled
void fn_sub_5353A8_005353a8(EEContext&);  // generated body
void fn_sub_5353A8_005353a8__recomp(EEContext&);  // recompiled
void fn_sub_5355B8_005355b8(EEContext&);  // generated body
void fn_sub_5355B8_005355b8__recomp(EEContext&);  // recompiled
void fn_sub_535610_00535610(EEContext&);  // generated body
void fn_sub_535610_00535610__recomp(EEContext&);  // recompiled
void fn_sub_535618_00535618(EEContext&);  // generated body
void fn_sub_535618_00535618__recomp(EEContext&);  // recompiled
void fn_sub_535668_00535668(EEContext&);  // generated body
void fn_sub_535668_00535668__recomp(EEContext&);  // recompiled
void fn_setenv_0054d030(EEContext&);  // generated body
void fn_setenv_0054d030__recomp(EEContext&);  // recompiled
void fn_unsetenv_0054d060(EEContext&);  // generated body
void fn_unsetenv_0054d060__recomp(EEContext&);  // recompiled
void fn_valloc_0054d080(EEContext&);  // generated body
void fn_valloc_0054d080__recomp(EEContext&);  // recompiled
void fn_pvalloc_0054d0a0(EEContext&);  // generated body
void fn_pvalloc_0054d0a0__recomp(EEContext&);  // recompiled
void fn_sub_54D0B8_0054d0b8(EEContext&);  // generated body
void fn_sub_54D0B8_0054d0b8__recomp(EEContext&);  // recompiled
void fn_sub_54D0D0_0054d0d0(EEContext&);  // generated body
void fn_sub_54D0D0_0054d0d0__recomp(EEContext&);  // recompiled
void fn_sub_54D0E8_0054d0e8(EEContext&);  // generated body
void fn_sub_54D0E8_0054d0e8__recomp(EEContext&);  // recompiled
void fn_cosl_4_0054d118(EEContext&);  // generated body
void fn_cosl_4_0054d118__recomp(EEContext&);  // recompiled
void fn_coshl_4_0054d130(EEContext&);  // generated body
void fn_coshl_4_0054d130__recomp(EEContext&);  // recompiled
void fn_hypotf_4_0054d160(EEContext&);  // generated body
void fn_hypotf_4_0054d160__recomp(EEContext&);  // recompiled
void fn_sub_54D178_0054d178(EEContext&);  // generated body
void fn_sub_54D178_0054d178__recomp(EEContext&);  // recompiled
void fn_sub_54D190_0054d190(EEContext&);  // generated body
void fn_sub_54D190_0054d190__recomp(EEContext&);  // recompiled
void fn_sub_54D1A8_0054d1a8(EEContext&);  // generated body
void fn_sub_54D1A8_0054d1a8__recomp(EEContext&);  // recompiled
void fn_sub_54D1C0_0054d1c0(EEContext&);  // generated body
void fn_sub_54D1C0_0054d1c0__recomp(EEContext&);  // recompiled
void fn_sub_54D1D8_0054d1d8(EEContext&);  // generated body
void fn_sub_54D1D8_0054d1d8__recomp(EEContext&);  // recompiled
void fn_sub_54D1F0_0054d1f0(EEContext&);  // generated body
void fn_sub_54D1F0_0054d1f0__recomp(EEContext&);  // recompiled
void fn_sub_54D208_0054d208(EEContext&);  // generated body
void fn_sub_54D208_0054d208__recomp(EEContext&);  // recompiled
void fn_sub_54D238_0054d238(EEContext&);  // generated body
void fn_sub_54D238_0054d238__recomp(EEContext&);  // recompiled
void fn_sub_54D250_0054d250(EEContext&);  // generated body
void fn_sub_54D250_0054d250__recomp(EEContext&);  // recompiled
void fn_sub_54D268_0054d268(EEContext&);  // generated body
void fn_sub_54D268_0054d268__recomp(EEContext&);  // recompiled
void fn_sub_54D280_0054d280(EEContext&);  // generated body
void fn_sub_54D280_0054d280__recomp(EEContext&);  // recompiled
void fn_sub_54D298_0054d298(EEContext&);  // generated body
void fn_sub_54D298_0054d298__recomp(EEContext&);  // recompiled
void fn_sub_54D2B0_0054d2b0(EEContext&);  // generated body
void fn_sub_54D2B0_0054d2b0__recomp(EEContext&);  // recompiled
void fn_sub_54D2C8_0054d2c8(EEContext&);  // generated body
void fn_sub_54D2C8_0054d2c8__recomp(EEContext&);  // recompiled
void fn_sub_54D2E0_0054d2e0(EEContext&);  // generated body
void fn_sub_54D2E0_0054d2e0__recomp(EEContext&);  // recompiled
void fn_sub_54D2F8_0054d2f8(EEContext&);  // generated body
void fn_sub_54D2F8_0054d2f8__recomp(EEContext&);  // recompiled
void fn_sub_54D310_0054d310(EEContext&);  // generated body
void fn_sub_54D310_0054d310__recomp(EEContext&);  // recompiled
void fn_sub_54D328_0054d328(EEContext&);  // generated body
void fn_sub_54D328_0054d328__recomp(EEContext&);  // recompiled
void fn_sub_54D340_0054d340(EEContext&);  // generated body
void fn_sub_54D340_0054d340__recomp(EEContext&);  // recompiled
void fn_sub_54D358_0054d358(EEContext&);  // generated body
void fn_sub_54D358_0054d358__recomp(EEContext&);  // recompiled
void fn_sub_54D378_0054d378(EEContext&);  // generated body
void fn_sub_54D378_0054d378__recomp(EEContext&);  // recompiled
void fn_atan2l_5_0054d390(EEContext&);  // generated body
void fn_atan2l_5_0054d390__recomp(EEContext&);  // recompiled
void fn_cosl_5_0054d3a8(EEContext&);  // generated body
void fn_cosl_5_0054d3a8__recomp(EEContext&);  // recompiled
void fn_coshl_5_0054d3c0(EEContext&);  // generated body
void fn_coshl_5_0054d3c0__recomp(EEContext&);  // recompiled
void fn_expl_5_0054d3d8(EEContext&);  // generated body
void fn_expl_5_0054d3d8__recomp(EEContext&);  // recompiled
void fn_hypotf_5_0054d3f0(EEContext&);  // generated body
void fn_hypotf_5_0054d3f0__recomp(EEContext&);  // recompiled
void fn_sub_54D408_0054d408(EEContext&);  // generated body
void fn_sub_54D408_0054d408__recomp(EEContext&);  // recompiled
void fn_sub_54D420_0054d420(EEContext&);  // generated body
void fn_sub_54D420_0054d420__recomp(EEContext&);  // recompiled
void fn_sub_54D438_0054d438(EEContext&);  // generated body
void fn_sub_54D438_0054d438__recomp(EEContext&);  // recompiled
void fn_sub_54D450_0054d450(EEContext&);  // generated body
void fn_sub_54D450_0054d450__recomp(EEContext&);  // recompiled
void fn_sub_54D468_0054d468(EEContext&);  // generated body
void fn_sub_54D468_0054d468__recomp(EEContext&);  // recompiled
void fn_sub_54D490_0054d490(EEContext&);  // generated body
void fn_sub_54D490_0054d490__recomp(EEContext&);  // recompiled
void fn_sub_54D4B8_0054d4b8(EEContext&);  // generated body
void fn_sub_54D4B8_0054d4b8__recomp(EEContext&);  // recompiled
void fn_sub_54D4F0_0054d4f0(EEContext&);  // generated body
void fn_sub_54D4F0_0054d4f0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"atan2l", 0x531998, &recomp_gen::fn_atan2l_00531998, &recomp_gen::fn_atan2l_00531998__recomp},
    {"cosl", 0x5319B0, &recomp_gen::fn_cosl_005319b0, &recomp_gen::fn_cosl_005319b0__recomp},
    {"coshl", 0x5319C8, &recomp_gen::fn_coshl_005319c8, &recomp_gen::fn_coshl_005319c8__recomp},
    {"expl", 0x5319E0, &recomp_gen::fn_expl_005319e0, &recomp_gen::fn_expl_005319e0__recomp},
    {"hypotf", 0x5319F8, &recomp_gen::fn_hypotf_005319f8, &recomp_gen::fn_hypotf_005319f8__recomp},
    {"sub_531A10", 0x531A10, &recomp_gen::fn_sub_531A10_00531a10, &recomp_gen::fn_sub_531A10_00531a10__recomp},
    {"sub_531A28", 0x531A28, &recomp_gen::fn_sub_531A28_00531a28, &recomp_gen::fn_sub_531A28_00531a28__recomp},
    {"sub_531A90", 0x531A90, &recomp_gen::fn_sub_531A90_00531a90, &recomp_gen::fn_sub_531A90_00531a90__recomp},
    {"sub_531AB8", 0x531AB8, &recomp_gen::fn_sub_531AB8_00531ab8, &recomp_gen::fn_sub_531AB8_00531ab8__recomp},
    {"sub_531AC0", 0x531AC0, &recomp_gen::fn_sub_531AC0_00531ac0, &recomp_gen::fn_sub_531AC0_00531ac0__recomp},
    {"sub_531AC8", 0x531AC8, &recomp_gen::fn_sub_531AC8_00531ac8, &recomp_gen::fn_sub_531AC8_00531ac8__recomp},
    {"sub_531AD0", 0x531AD0, &recomp_gen::fn_sub_531AD0_00531ad0, &recomp_gen::fn_sub_531AD0_00531ad0__recomp},
    {"sub_531B00", 0x531B00, &recomp_gen::fn_sub_531B00_00531b00, &recomp_gen::fn_sub_531B00_00531b00__recomp},
    {"sub_531BC0", 0x531BC0, &recomp_gen::fn_sub_531BC0_00531bc0, &recomp_gen::fn_sub_531BC0_00531bc0__recomp},
    {"sub_531C00", 0x531C00, &recomp_gen::fn_sub_531C00_00531c00, &recomp_gen::fn_sub_531C00_00531c00__recomp},
    {"sub_531D40", 0x531D40, &recomp_gen::fn_sub_531D40_00531d40, &recomp_gen::fn_sub_531D40_00531d40__recomp},
    {"sub_531D48", 0x531D48, &recomp_gen::fn_sub_531D48_00531d48, &recomp_gen::fn_sub_531D48_00531d48__recomp},
    {"sub_531D58", 0x531D58, &recomp_gen::fn_sub_531D58_00531d58, &recomp_gen::fn_sub_531D58_00531d58__recomp},
    {"sub_531D68", 0x531D68, &recomp_gen::fn_sub_531D68_00531d68, &recomp_gen::fn_sub_531D68_00531d68__recomp},
    {"sub_531DD8", 0x531DD8, &recomp_gen::fn_sub_531DD8_00531dd8, &recomp_gen::fn_sub_531DD8_00531dd8__recomp},
    {"sub_531E60", 0x531E60, &recomp_gen::fn_sub_531E60_00531e60, &recomp_gen::fn_sub_531E60_00531e60__recomp},
    {"sub_531F90", 0x531F90, &recomp_gen::fn_sub_531F90_00531f90, &recomp_gen::fn_sub_531F90_00531f90__recomp},
    {"sub_5320B8", 0x5320B8, &recomp_gen::fn_sub_5320B8_005320b8, &recomp_gen::fn_sub_5320B8_005320b8__recomp},
    {"sub_5320E8", 0x5320E8, &recomp_gen::fn_sub_5320E8_005320e8, &recomp_gen::fn_sub_5320E8_005320e8__recomp},
    {"sub_532118", 0x532118, &recomp_gen::fn_sub_532118_00532118, &recomp_gen::fn_sub_532118_00532118__recomp},
    {"sub_532180", 0x532180, &recomp_gen::fn_sub_532180_00532180, &recomp_gen::fn_sub_532180_00532180__recomp},
    {"sub_5321A8", 0x5321A8, &recomp_gen::fn_sub_5321A8_005321a8, &recomp_gen::fn_sub_5321A8_005321a8__recomp},
    {"sub_532230", 0x532230, &recomp_gen::fn_sub_532230_00532230, &recomp_gen::fn_sub_532230_00532230__recomp},
    {"sub_532268", 0x532268, &recomp_gen::fn_sub_532268_00532268, &recomp_gen::fn_sub_532268_00532268__recomp},
    {"sub_532280", 0x532280, &recomp_gen::fn_sub_532280_00532280, &recomp_gen::fn_sub_532280_00532280__recomp},
    {"sub_532298", 0x532298, &recomp_gen::fn_sub_532298_00532298, &recomp_gen::fn_sub_532298_00532298__recomp},
    {"sub_5322B0", 0x5322B0, &recomp_gen::fn_sub_5322B0_005322b0, &recomp_gen::fn_sub_5322B0_005322b0__recomp},
    {"sub_5322C8", 0x5322C8, &recomp_gen::fn_sub_5322C8_005322c8, &recomp_gen::fn_sub_5322C8_005322c8__recomp},
    {"sub_5322E0", 0x5322E0, &recomp_gen::fn_sub_5322E0_005322e0, &recomp_gen::fn_sub_5322E0_005322e0__recomp},
    {"sub_5322F8", 0x5322F8, &recomp_gen::fn_sub_5322F8_005322f8, &recomp_gen::fn_sub_5322F8_005322f8__recomp},
    {"sub_532310", 0x532310, &recomp_gen::fn_sub_532310_00532310, &recomp_gen::fn_sub_532310_00532310__recomp},
    {"sub_532380", 0x532380, &recomp_gen::fn_sub_532380_00532380, &recomp_gen::fn_sub_532380_00532380__recomp},
    {"sub_5323A8", 0x5323A8, &recomp_gen::fn_sub_5323A8_005323a8, &recomp_gen::fn_sub_5323A8_005323a8__recomp},
    {"sub_5323C0", 0x5323C0, &recomp_gen::fn_sub_5323C0_005323c0, &recomp_gen::fn_sub_5323C0_005323c0__recomp},
    {"sub_5323F0", 0x5323F0, &recomp_gen::fn_sub_5323F0_005323f0, &recomp_gen::fn_sub_5323F0_005323f0__recomp},
    {"sub_532420", 0x532420, &recomp_gen::fn_sub_532420_00532420, &recomp_gen::fn_sub_532420_00532420__recomp},
    {"sub_532438", 0x532438, &recomp_gen::fn_sub_532438_00532438, &recomp_gen::fn_sub_532438_00532438__recomp},
    {"sub_532440", 0x532440, &recomp_gen::fn_sub_532440_00532440, &recomp_gen::fn_sub_532440_00532440__recomp},
    {"sub_532458", 0x532458, &recomp_gen::fn_sub_532458_00532458, &recomp_gen::fn_sub_532458_00532458__recomp},
    {"sub_5324C0", 0x5324C0, &recomp_gen::fn_sub_5324C0_005324c0, &recomp_gen::fn_sub_5324C0_005324c0__recomp},
    {"sub_5324E8", 0x5324E8, &recomp_gen::fn_sub_5324E8_005324e8, &recomp_gen::fn_sub_5324E8_005324e8__recomp},
    {"sub_532580", 0x532580, &recomp_gen::fn_sub_532580_00532580, &recomp_gen::fn_sub_532580_00532580__recomp},
    {"sub_5325B8", 0x5325B8, &recomp_gen::fn_sub_5325B8_005325b8, &recomp_gen::fn_sub_5325B8_005325b8__recomp},
    {"sub_5325D8", 0x5325D8, &recomp_gen::fn_sub_5325D8_005325d8, &recomp_gen::fn_sub_5325D8_005325d8__recomp},
    {"sub_5325F0", 0x5325F0, &recomp_gen::fn_sub_5325F0_005325f0, &recomp_gen::fn_sub_5325F0_005325f0__recomp},
    {"sub_532608", 0x532608, &recomp_gen::fn_sub_532608_00532608, &recomp_gen::fn_sub_532608_00532608__recomp},
    {"sub_532628", 0x532628, &recomp_gen::fn_sub_532628_00532628, &recomp_gen::fn_sub_532628_00532628__recomp},
    {"sub_532640", 0x532640, &recomp_gen::fn_sub_532640_00532640, &recomp_gen::fn_sub_532640_00532640__recomp},
    {"sub_532658", 0x532658, &recomp_gen::fn_sub_532658_00532658, &recomp_gen::fn_sub_532658_00532658__recomp},
    {"sub_532670", 0x532670, &recomp_gen::fn_sub_532670_00532670, &recomp_gen::fn_sub_532670_00532670__recomp},
    {"sub_532688", 0x532688, &recomp_gen::fn_sub_532688_00532688, &recomp_gen::fn_sub_532688_00532688__recomp},
    {"sub_5326F0", 0x5326F0, &recomp_gen::fn_sub_5326F0_005326f0, &recomp_gen::fn_sub_5326F0_005326f0__recomp},
    {"sub_532718", 0x532718, &recomp_gen::fn_sub_532718_00532718, &recomp_gen::fn_sub_532718_00532718__recomp},
    {"sub_532740", 0x532740, &recomp_gen::fn_sub_532740_00532740, &recomp_gen::fn_sub_532740_00532740__recomp},
    {"sub_532748", 0x532748, &recomp_gen::fn_sub_532748_00532748, &recomp_gen::fn_sub_532748_00532748__recomp},
    {"sub_532760", 0x532760, &recomp_gen::fn_sub_532760_00532760, &recomp_gen::fn_sub_532760_00532760__recomp},
    {"sub_532768", 0x532768, &recomp_gen::fn_sub_532768_00532768, &recomp_gen::fn_sub_532768_00532768__recomp},
    {"sub_532788", 0x532788, &recomp_gen::fn_sub_532788_00532788, &recomp_gen::fn_sub_532788_00532788__recomp},
    {"sub_5327F0", 0x5327F0, &recomp_gen::fn_sub_5327F0_005327f0, &recomp_gen::fn_sub_5327F0_005327f0__recomp},
    {"sub_532818", 0x532818, &recomp_gen::fn_sub_532818_00532818, &recomp_gen::fn_sub_532818_00532818__recomp},
    {"sub_532D30", 0x532D30, &recomp_gen::fn_sub_532D30_00532d30, &recomp_gen::fn_sub_532D30_00532d30__recomp},
    {"sub_532E08", 0x532E08, &recomp_gen::fn_sub_532E08_00532e08, &recomp_gen::fn_sub_532E08_00532e08__recomp},
    {"sub_532E10", 0x532E10, &recomp_gen::fn_sub_532E10_00532e10, &recomp_gen::fn_sub_532E10_00532e10__recomp},
    {"sub_532E70", 0x532E70, &recomp_gen::fn_sub_532E70_00532e70, &recomp_gen::fn_sub_532E70_00532e70__recomp},
    {"sub_532EC0", 0x532EC0, &recomp_gen::fn_sub_532EC0_00532ec0, &recomp_gen::fn_sub_532EC0_00532ec0__recomp},
    {"sub_532F10", 0x532F10, &recomp_gen::fn_sub_532F10_00532f10, &recomp_gen::fn_sub_532F10_00532f10__recomp},
    {"sub_532F60", 0x532F60, &recomp_gen::fn_sub_532F60_00532f60, &recomp_gen::fn_sub_532F60_00532f60__recomp},
    {"sub_5330A8", 0x5330A8, &recomp_gen::fn_sub_5330A8_005330a8, &recomp_gen::fn_sub_5330A8_005330a8__recomp},
    {"sub_533160", 0x533160, &recomp_gen::fn_sub_533160_00533160, &recomp_gen::fn_sub_533160_00533160__recomp},
    {"sub_5331A8", 0x5331A8, &recomp_gen::fn_sub_5331A8_005331a8, &recomp_gen::fn_sub_5331A8_005331a8__recomp},
    {"sub_5331F0", 0x5331F0, &recomp_gen::fn_sub_5331F0_005331f0, &recomp_gen::fn_sub_5331F0_005331f0__recomp},
    {"sub_533230", 0x533230, &recomp_gen::fn_sub_533230_00533230, &recomp_gen::fn_sub_533230_00533230__recomp},
    {"sub_533238", 0x533238, &recomp_gen::fn_sub_533238_00533238, &recomp_gen::fn_sub_533238_00533238__recomp},
    {"sub_533340", 0x533340, &recomp_gen::fn_sub_533340_00533340, &recomp_gen::fn_sub_533340_00533340__recomp},
    {"_ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv", 0x533450, &recomp_gen::fn__ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv_00533450, &recomp_gen::fn__ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv_00533450__recomp},
    {"sub_5334A8", 0x5334A8, &recomp_gen::fn_sub_5334A8_005334a8, &recomp_gen::fn_sub_5334A8_005334a8__recomp},
    {"sub_533570", 0x533570, &recomp_gen::fn_sub_533570_00533570, &recomp_gen::fn_sub_533570_00533570__recomp},
    {"sub_533578", 0x533578, &recomp_gen::fn_sub_533578_00533578, &recomp_gen::fn_sub_533578_00533578__recomp},
    {"sub_533580", 0x533580, &recomp_gen::fn_sub_533580_00533580, &recomp_gen::fn_sub_533580_00533580__recomp},
    {"_ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0", 0x533590, &recomp_gen::fn__ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0_00533590, &recomp_gen::fn__ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0_00533590__recomp},
    {"sub_5335A0", 0x5335A0, &recomp_gen::fn_sub_5335A0_005335a0, &recomp_gen::fn_sub_5335A0_005335a0__recomp},
    {"sub_5335B0", 0x5335B0, &recomp_gen::fn_sub_5335B0_005335b0, &recomp_gen::fn_sub_5335B0_005335b0__recomp},
    {"sub_5336C0", 0x5336C0, &recomp_gen::fn_sub_5336C0_005336c0, &recomp_gen::fn_sub_5336C0_005336c0__recomp},
    {"sub_5337A8", 0x5337A8, &recomp_gen::fn_sub_5337A8_005337a8, &recomp_gen::fn_sub_5337A8_005337a8__recomp},
    {"sub_533808", 0x533808, &recomp_gen::fn_sub_533808_00533808, &recomp_gen::fn_sub_533808_00533808__recomp},
    {"sub_533880", 0x533880, &recomp_gen::fn_sub_533880_00533880, &recomp_gen::fn_sub_533880_00533880__recomp},
    {"sub_533900", 0x533900, &recomp_gen::fn_sub_533900_00533900, &recomp_gen::fn_sub_533900_00533900__recomp},
    {"sub_533950", 0x533950, &recomp_gen::fn_sub_533950_00533950, &recomp_gen::fn_sub_533950_00533950__recomp},
    {"sub_5339A8", 0x5339A8, &recomp_gen::fn_sub_5339A8_005339a8, &recomp_gen::fn_sub_5339A8_005339a8__recomp},
    {"sub_533A18", 0x533A18, &recomp_gen::fn_sub_533A18_00533a18, &recomp_gen::fn_sub_533A18_00533a18__recomp},
    {"sub_533A88", 0x533A88, &recomp_gen::fn_sub_533A88_00533a88, &recomp_gen::fn_sub_533A88_00533a88__recomp},
    {"sub_533AC8", 0x533AC8, &recomp_gen::fn_sub_533AC8_00533ac8, &recomp_gen::fn_sub_533AC8_00533ac8__recomp},
    {"sub_533CA0", 0x533CA0, &recomp_gen::fn_sub_533CA0_00533ca0, &recomp_gen::fn_sub_533CA0_00533ca0__recomp},
    {"sub_533CA8", 0x533CA8, &recomp_gen::fn_sub_533CA8_00533ca8, &recomp_gen::fn_sub_533CA8_00533ca8__recomp},
    {"sub_533CC0", 0x533CC0, &recomp_gen::fn_sub_533CC0_00533cc0, &recomp_gen::fn_sub_533CC0_00533cc0__recomp},
    {"sub_533CD0", 0x533CD0, &recomp_gen::fn_sub_533CD0_00533cd0, &recomp_gen::fn_sub_533CD0_00533cd0__recomp},
    {"sub_533E98", 0x533E98, &recomp_gen::fn_sub_533E98_00533e98, &recomp_gen::fn_sub_533E98_00533e98__recomp},
    {"sub_533F10", 0x533F10, &recomp_gen::fn_sub_533F10_00533f10, &recomp_gen::fn_sub_533F10_00533f10__recomp},
    {"sub_534010", 0x534010, &recomp_gen::fn_sub_534010_00534010, &recomp_gen::fn_sub_534010_00534010__recomp},
    {"sub_534308", 0x534308, &recomp_gen::fn_sub_534308_00534308, &recomp_gen::fn_sub_534308_00534308__recomp},
    {"sub_5343D8", 0x5343D8, &recomp_gen::fn_sub_5343D8_005343d8, &recomp_gen::fn_sub_5343D8_005343d8__recomp},
    {"sub_534488", 0x534488, &recomp_gen::fn_sub_534488_00534488, &recomp_gen::fn_sub_534488_00534488__recomp},
    {"sub_534530", 0x534530, &recomp_gen::fn_sub_534530_00534530, &recomp_gen::fn_sub_534530_00534530__recomp},
    {"sub_534538", 0x534538, &recomp_gen::fn_sub_534538_00534538, &recomp_gen::fn_sub_534538_00534538__recomp},
    {"sub_534678", 0x534678, &recomp_gen::fn_sub_534678_00534678, &recomp_gen::fn_sub_534678_00534678__recomp},
    {"sub_534728", 0x534728, &recomp_gen::fn_sub_534728_00534728, &recomp_gen::fn_sub_534728_00534728__recomp},
    {"sub_5347C0", 0x5347C0, &recomp_gen::fn_sub_5347C0_005347c0, &recomp_gen::fn_sub_5347C0_005347c0__recomp},
    {"sub_534888", 0x534888, &recomp_gen::fn_sub_534888_00534888, &recomp_gen::fn_sub_534888_00534888__recomp},
    {"sub_534960", 0x534960, &recomp_gen::fn_sub_534960_00534960, &recomp_gen::fn_sub_534960_00534960__recomp},
    {"sub_5349C8", 0x5349C8, &recomp_gen::fn_sub_5349C8_005349c8, &recomp_gen::fn_sub_5349C8_005349c8__recomp},
    {"sub_5349F8", 0x5349F8, &recomp_gen::fn_sub_5349F8_005349f8, &recomp_gen::fn_sub_5349F8_005349f8__recomp},
    {"sub_534A60", 0x534A60, &recomp_gen::fn_sub_534A60_00534a60, &recomp_gen::fn_sub_534A60_00534a60__recomp},
    {"sub_534A88", 0x534A88, &recomp_gen::fn_sub_534A88_00534a88, &recomp_gen::fn_sub_534A88_00534a88__recomp},
    {"sub_534B60", 0x534B60, &recomp_gen::fn_sub_534B60_00534b60, &recomp_gen::fn_sub_534B60_00534b60__recomp},
    {"sub_534C58", 0x534C58, &recomp_gen::fn_sub_534C58_00534c58, &recomp_gen::fn_sub_534C58_00534c58__recomp},
    {"sub_534C98", 0x534C98, &recomp_gen::fn_sub_534C98_00534c98, &recomp_gen::fn_sub_534C98_00534c98__recomp},
    {"sub_534DB0", 0x534DB0, &recomp_gen::fn_sub_534DB0_00534db0, &recomp_gen::fn_sub_534DB0_00534db0__recomp},
    {"sub_535050", 0x535050, &recomp_gen::fn_sub_535050_00535050, &recomp_gen::fn_sub_535050_00535050__recomp},
    {"sub_5350D0", 0x5350D0, &recomp_gen::fn_sub_5350D0_005350d0, &recomp_gen::fn_sub_5350D0_005350d0__recomp},
    {"sub_535170", 0x535170, &recomp_gen::fn_sub_535170_00535170, &recomp_gen::fn_sub_535170_00535170__recomp},
    {"sub_535178", 0x535178, &recomp_gen::fn_sub_535178_00535178, &recomp_gen::fn_sub_535178_00535178__recomp},
    {"sub_5351B0", 0x5351B0, &recomp_gen::fn_sub_5351B0_005351b0, &recomp_gen::fn_sub_5351B0_005351b0__recomp},
    {"sub_5351C0", 0x5351C0, &recomp_gen::fn_sub_5351C0_005351c0, &recomp_gen::fn_sub_5351C0_005351c0__recomp},
    {"sub_5351E8", 0x5351E8, &recomp_gen::fn_sub_5351E8_005351e8, &recomp_gen::fn_sub_5351E8_005351e8__recomp},
    {"sub_535250", 0x535250, &recomp_gen::fn_sub_535250_00535250, &recomp_gen::fn_sub_535250_00535250__recomp},
    {"sub_535278", 0x535278, &recomp_gen::fn_sub_535278_00535278, &recomp_gen::fn_sub_535278_00535278__recomp},
    {"sub_5352F8", 0x5352F8, &recomp_gen::fn_sub_5352F8_005352f8, &recomp_gen::fn_sub_5352F8_005352f8__recomp},
    {"sub_535348", 0x535348, &recomp_gen::fn_sub_535348_00535348, &recomp_gen::fn_sub_535348_00535348__recomp},
    {"sub_535350", 0x535350, &recomp_gen::fn_sub_535350_00535350, &recomp_gen::fn_sub_535350_00535350__recomp},
    {"sub_535358", 0x535358, &recomp_gen::fn_sub_535358_00535358, &recomp_gen::fn_sub_535358_00535358__recomp},
    {"sub_535388", 0x535388, &recomp_gen::fn_sub_535388_00535388, &recomp_gen::fn_sub_535388_00535388__recomp},
    {"sub_535390", 0x535390, &recomp_gen::fn_sub_535390_00535390, &recomp_gen::fn_sub_535390_00535390__recomp},
    {"rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc", 0x535398, &recomp_gen::fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398, &recomp_gen::fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398__recomp},
    {"sub_5353A0", 0x5353A0, &recomp_gen::fn_sub_5353A0_005353a0, &recomp_gen::fn_sub_5353A0_005353a0__recomp},
    {"sub_5353A8", 0x5353A8, &recomp_gen::fn_sub_5353A8_005353a8, &recomp_gen::fn_sub_5353A8_005353a8__recomp},
    {"sub_5355B8", 0x5355B8, &recomp_gen::fn_sub_5355B8_005355b8, &recomp_gen::fn_sub_5355B8_005355b8__recomp},
    {"sub_535610", 0x535610, &recomp_gen::fn_sub_535610_00535610, &recomp_gen::fn_sub_535610_00535610__recomp},
    {"sub_535618", 0x535618, &recomp_gen::fn_sub_535618_00535618, &recomp_gen::fn_sub_535618_00535618__recomp},
    {"sub_535668", 0x535668, &recomp_gen::fn_sub_535668_00535668, &recomp_gen::fn_sub_535668_00535668__recomp},
    {"setenv", 0x54D030, &recomp_gen::fn_setenv_0054d030, &recomp_gen::fn_setenv_0054d030__recomp},
    {"unsetenv", 0x54D060, &recomp_gen::fn_unsetenv_0054d060, &recomp_gen::fn_unsetenv_0054d060__recomp},
    {"valloc", 0x54D080, &recomp_gen::fn_valloc_0054d080, &recomp_gen::fn_valloc_0054d080__recomp},
    {"pvalloc", 0x54D0A0, &recomp_gen::fn_pvalloc_0054d0a0, &recomp_gen::fn_pvalloc_0054d0a0__recomp},
    {"sub_54D0B8", 0x54D0B8, &recomp_gen::fn_sub_54D0B8_0054d0b8, &recomp_gen::fn_sub_54D0B8_0054d0b8__recomp},
    {"sub_54D0D0", 0x54D0D0, &recomp_gen::fn_sub_54D0D0_0054d0d0, &recomp_gen::fn_sub_54D0D0_0054d0d0__recomp},
    {"sub_54D0E8", 0x54D0E8, &recomp_gen::fn_sub_54D0E8_0054d0e8, &recomp_gen::fn_sub_54D0E8_0054d0e8__recomp},
    {"cosl_4", 0x54D118, &recomp_gen::fn_cosl_4_0054d118, &recomp_gen::fn_cosl_4_0054d118__recomp},
    {"coshl_4", 0x54D130, &recomp_gen::fn_coshl_4_0054d130, &recomp_gen::fn_coshl_4_0054d130__recomp},
    {"hypotf_4", 0x54D160, &recomp_gen::fn_hypotf_4_0054d160, &recomp_gen::fn_hypotf_4_0054d160__recomp},
    {"sub_54D178", 0x54D178, &recomp_gen::fn_sub_54D178_0054d178, &recomp_gen::fn_sub_54D178_0054d178__recomp},
    {"sub_54D190", 0x54D190, &recomp_gen::fn_sub_54D190_0054d190, &recomp_gen::fn_sub_54D190_0054d190__recomp},
    {"sub_54D1A8", 0x54D1A8, &recomp_gen::fn_sub_54D1A8_0054d1a8, &recomp_gen::fn_sub_54D1A8_0054d1a8__recomp},
    {"sub_54D1C0", 0x54D1C0, &recomp_gen::fn_sub_54D1C0_0054d1c0, &recomp_gen::fn_sub_54D1C0_0054d1c0__recomp},
    {"sub_54D1D8", 0x54D1D8, &recomp_gen::fn_sub_54D1D8_0054d1d8, &recomp_gen::fn_sub_54D1D8_0054d1d8__recomp},
    {"sub_54D1F0", 0x54D1F0, &recomp_gen::fn_sub_54D1F0_0054d1f0, &recomp_gen::fn_sub_54D1F0_0054d1f0__recomp},
    {"sub_54D208", 0x54D208, &recomp_gen::fn_sub_54D208_0054d208, &recomp_gen::fn_sub_54D208_0054d208__recomp},
    {"sub_54D238", 0x54D238, &recomp_gen::fn_sub_54D238_0054d238, &recomp_gen::fn_sub_54D238_0054d238__recomp},
    {"sub_54D250", 0x54D250, &recomp_gen::fn_sub_54D250_0054d250, &recomp_gen::fn_sub_54D250_0054d250__recomp},
    {"sub_54D268", 0x54D268, &recomp_gen::fn_sub_54D268_0054d268, &recomp_gen::fn_sub_54D268_0054d268__recomp},
    {"sub_54D280", 0x54D280, &recomp_gen::fn_sub_54D280_0054d280, &recomp_gen::fn_sub_54D280_0054d280__recomp},
    {"sub_54D298", 0x54D298, &recomp_gen::fn_sub_54D298_0054d298, &recomp_gen::fn_sub_54D298_0054d298__recomp},
    {"sub_54D2B0", 0x54D2B0, &recomp_gen::fn_sub_54D2B0_0054d2b0, &recomp_gen::fn_sub_54D2B0_0054d2b0__recomp},
    {"sub_54D2C8", 0x54D2C8, &recomp_gen::fn_sub_54D2C8_0054d2c8, &recomp_gen::fn_sub_54D2C8_0054d2c8__recomp},
    {"sub_54D2E0", 0x54D2E0, &recomp_gen::fn_sub_54D2E0_0054d2e0, &recomp_gen::fn_sub_54D2E0_0054d2e0__recomp},
    {"sub_54D2F8", 0x54D2F8, &recomp_gen::fn_sub_54D2F8_0054d2f8, &recomp_gen::fn_sub_54D2F8_0054d2f8__recomp},
    {"sub_54D310", 0x54D310, &recomp_gen::fn_sub_54D310_0054d310, &recomp_gen::fn_sub_54D310_0054d310__recomp},
    {"sub_54D328", 0x54D328, &recomp_gen::fn_sub_54D328_0054d328, &recomp_gen::fn_sub_54D328_0054d328__recomp},
    {"sub_54D340", 0x54D340, &recomp_gen::fn_sub_54D340_0054d340, &recomp_gen::fn_sub_54D340_0054d340__recomp},
    {"sub_54D358", 0x54D358, &recomp_gen::fn_sub_54D358_0054d358, &recomp_gen::fn_sub_54D358_0054d358__recomp},
    {"sub_54D378", 0x54D378, &recomp_gen::fn_sub_54D378_0054d378, &recomp_gen::fn_sub_54D378_0054d378__recomp},
    {"atan2l_5", 0x54D390, &recomp_gen::fn_atan2l_5_0054d390, &recomp_gen::fn_atan2l_5_0054d390__recomp},
    {"cosl_5", 0x54D3A8, &recomp_gen::fn_cosl_5_0054d3a8, &recomp_gen::fn_cosl_5_0054d3a8__recomp},
    {"coshl_5", 0x54D3C0, &recomp_gen::fn_coshl_5_0054d3c0, &recomp_gen::fn_coshl_5_0054d3c0__recomp},
    {"expl_5", 0x54D3D8, &recomp_gen::fn_expl_5_0054d3d8, &recomp_gen::fn_expl_5_0054d3d8__recomp},
    {"hypotf_5", 0x54D3F0, &recomp_gen::fn_hypotf_5_0054d3f0, &recomp_gen::fn_hypotf_5_0054d3f0__recomp},
    {"sub_54D408", 0x54D408, &recomp_gen::fn_sub_54D408_0054d408, &recomp_gen::fn_sub_54D408_0054d408__recomp},
    {"sub_54D420", 0x54D420, &recomp_gen::fn_sub_54D420_0054d420, &recomp_gen::fn_sub_54D420_0054d420__recomp},
    {"sub_54D438", 0x54D438, &recomp_gen::fn_sub_54D438_0054d438, &recomp_gen::fn_sub_54D438_0054d438__recomp},
    {"sub_54D450", 0x54D450, &recomp_gen::fn_sub_54D450_0054d450, &recomp_gen::fn_sub_54D450_0054d450__recomp},
    {"sub_54D468", 0x54D468, &recomp_gen::fn_sub_54D468_0054d468, &recomp_gen::fn_sub_54D468_0054d468__recomp},
    {"sub_54D490", 0x54D490, &recomp_gen::fn_sub_54D490_0054d490, &recomp_gen::fn_sub_54D490_0054d490__recomp},
    {"sub_54D4B8", 0x54D4B8, &recomp_gen::fn_sub_54D4B8_0054d4b8, &recomp_gen::fn_sub_54D4B8_0054d4b8__recomp},
    {"sub_54D4F0", 0x54D4F0, &recomp_gen::fn_sub_54D4F0_0054d4f0, &recomp_gen::fn_sub_54D4F0_0054d4f0__recomp},
};


using namespace p3fes::game::libs2;

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    static const Case none{"?", 0, nullptr, nullptr};
    FAIL("no case for " << hex64(addr));
    return none;
}

// --- guest memory helpers ------------------------------------------------------------------------------------------
u8 r8(Machine& m, u32 va) { return *m.at(va); }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
s32 r32s(Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
u32 uv(u64 v) { return static_cast<u32>(v); }
u64 sx64(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }
std::string gstr(const EEContext& ctx, u32 va) {
    std::string s;
    for (u32 a = va; s.size() < 255; ++a) {
        const char ch = static_cast<char>(ctx.memory->read<u8>(a));
        if (ch == 0) break;
        s += ch;
    }
    return s;
}

// --- the stand-ins: every driver below ACSS that the test binary does not emit -------------------------------------
// Recorders (no scratch clobbering, so one set serves both bodies of a pair alike: the hgp runner compares the whole
// register file at every callee's entry check point, which holds the call's arguments). pow is served by the host's
// pow on the 64-bit soft-float argument registers; the ADX error reporters keep their texts.
constexpr u32 kPow = 0x52E9D0u;
constexpr u32 kAdxErr1 = 0x53AE08u, kAdxErr2 = 0x53AE60u;
constexpr u32 kSvmLockCb = 0x53F8B8u, kSvmUnlockCb = 0x53F940u;
const u32 kDrivers[] = {
    // AIXP and the AHX attach of ADXT (the AIX back end's callees), ADXT functions no slice has taken
    0x552830u, 0x5528B0u, 0x552BD0u, 0x552EA8u, 0x552EC8u, 0x553028u, 0x5530D0u, 0x553188u, 0x553230u, 0x5533D8u,
    0x553590u, 0x553658u, 0x5540E8u, 0x5526B0u, 0x552760u, 0x54F5C0u, 0x54F708u, 0x54B3A0u, 0x549530u, 0x547F30u,
    0x53EA90u, 0x53EC20u, 0x564EF8u, 0x564FE8u, 0x53AFD8u,
    // PS2RNA, ADXSTM, the list streamer, the amplifier hooks, ADXF's lookup, ADXB, ADXSJD's pending steps
    // (test_cri2's driver set)
    0x5419F8u, 0x545FC8u, 0x55D2A0u, 0x541AC0u, 0x541AD8u, 0x546368u, 0x55D790u, 0x548FC8u, 0x541A10u, 0x541A78u,
    0x541A90u, 0x541B58u, 0x541B70u, 0x541B88u, 0x541BA0u, 0x541BD0u, 0x541CB8u, 0x541CC8u, 0x560DB8u, 0x546058u,
    0x5460E0u, 0x546270u, 0x5463A8u, 0x546498u, 0x5465A0u, 0x5466B8u, 0x546718u, 0x546FA0u, 0x55D3A8u, 0x55D3F8u,
    0x55D668u, 0x535888u, 0x5358E0u, 0x535A80u, 0x535DA8u, 0x548B38u, 0x549160u, 0x54A928u, 0x54A630u, 0x5433A0u,
    0x53DD10u, 0x541B28u, 0x537890u, 0x537D90u, 0x537F30u, 0x537F40u, 0x537FE8u, 0x538038u, 0x538040u, 0x5382C0u,
    0x5383E8u, 0x5383F0u, 0x538048u, 0x537F08u, 0x5379B0u, 0x537CF0u, 0x538060u, 0x5382C8u, 0x538348u, 0x538360u,
    0x5383A8u, 0x5389B0u, 0x535DD8u, 0x535E28u, 0x535FC0u, 0x535FF0u, 0x536080u, 0x537790u, 0x542A88u, 0x542C70u,
    0x542DC0u, 0x537780u, kSvmLockCb, kSvmUnlockCb};
u64 dbits(double d) { u64 b; std::memcpy(&b, &d, 8); return b; }
double bitsd(u64 b) { double d; std::memcpy(&d, &b, 8); return d; }
std::vector<std::string> g_err;  // ADX error texts seen (both bodies of every pair)
void install_drivers(StandIns& s) {
    s.clobber_scratch = false;
    for (u32 va : kDrivers) s.install_recorder(va, "driver", 0, 3);
    s.install(kPow, "pow", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = dbits(std::pow(bitsd(c.args[0]), bitsd(c.args[1]))); }, 4);
    for (u32 va : {kAdxErr1, kAdxErr2})
        s.install(va, "adx_err", [](EEContext& ctx, StandIns&, StandInCall& c) { g_err.push_back(gstr(ctx, uv(c.args[0]))); }, 3);
}

std::map<std::string, int> g_pairs;  // pairs per function in the meaningful sections
u32 g_seed = 1;

// One pair from the machine's current state (the recompiled run's memory stays), with the drivers stood in; $t0..$t3
// from `t`.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const Case& c = by_addr(addr);
    StandIns si;
    install_drivers(si);
    StandInsScope scope{si};
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    return hgp::pair(m, c.hand, c.recomp, a, g_seed++, c.name, hw);
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const hgp::Run r = pr(m, addr, a, std::move(t));
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
std::map<unsigned, u64> tregs(u64 t0, u64 t1 = 0) { return {{GPR_T0, t0}, {GPR_T0 + 1, t1}}; }

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
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

constexpr u32 kServerPtr = 0x793F44u;  // the server's address (the public entry points read it)
constexpr u32 kAdxVtbl = 0x7C0520u, kAixVtbl = 0x7C0630u, kAdxStatMap = 0x7C0610u;
constexpr s32 kSilent = -960;
constexpr s32 kFullLevel = 3238200;
constexpr u32 kWork = 0x01810000u;     // free RAM for built records (the generated world's region)

// What $a0 holds for each function (the records of libs2.h) -- the snapshot sweep's argument recipe.
enum class Arg { None, Snd, Fdr, Bad, Bai, Svr, Vhl, SndPly };
Arg arg_of(u32 a) {
    if (a >= 0x531A90u && a < 0x532118u && a != 0x531A10u && a != 0x531A28u) return Arg::Fdr;
    if ((a >= 0x532180u && a <= 0x532440u)) return Arg::Bad;
    if (a >= 0x5324C0u && a <= 0x532768u) return Arg::Bai;
    if (a == 0x5343D8u || a == 0x534488u || a == 0x534538u || a == 0x534888u) return Arg::SndPly;
    if ((a >= 0x5327F0u && a <= 0x5349C8u) || a == 0x54D178u || a == 0x54D1F0u || a == 0x54D238u || a == 0x54D250u ||
        a == 0x54D2B0u || a == 0x54D2E0u || a == 0x54D310u)
        return Arg::Snd;
    if (a >= 0x534A60u && a <= 0x5351C0u) return Arg::Svr;
    if (a >= 0x535250u && a <= 0x535668u) return Arg::Vhl;
    if (a >= 0x54D0A0u && a <= 0x54D450u) return Arg::Snd;  // the public thunks take the sound
    return Arg::None;
}
// Functions the sweep leaves to their own sections: the creators and init / finish (they rebuild the whole server
// or a sound from a configuration and a work area -- done on fresh machines below), and those taking a work pointer.
bool sweep_skips(u32 a) {
    switch (a) {
    case 0x531A28u: case 0x532118u: case 0x532458u: case 0x532788u: case 0x5349F8u: case 0x5351E8u:  // creates
    case 0x532818u: case 0x534A88u: case 0x534B60u: case 0x534C58u: case 0x534C98u: case 0x54D030u:  // init / finish
    case 0x54D080u:  // a configuration pointer
        return true;
    default:
        return false;
    }
}

}  // namespace

TEST_CASE("game(libs2): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24u;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    constexpr u32 kWorldSize = 0x10000u;
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWork, kWorldSize, rng);
            const u64 a0 = hgp::random_arg(rng, kWork, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWork, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWork, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWork, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, Args{a0, a1, a2, a3}, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The replay snapshots hold the live server (0x793F44), its ducking object, and two (dorm, fusion) or four (battle,
// Tartarus) sounds with their back ends and faders, mid-fade in some. Every function runs on them with the argument
// its role takes -- the live sound / fader / back end / server / ducking object -- and second arguments from the
// values its branches test; each pair starts from the snapshot.
TEST_CASE("game(libs2): every body on the snapshots' live server, sounds, faders and back ends") {
    auto m = machine();
    if (!m) return;
    const s64 kArgs[] = {0, 1, 2, 3, -1, kSilent, -300, 30};
    int ran = 0, stopped = 0;
    for (const char* dir : {"dorm_replay_4900", "b_5800", "battle_ref_6150", "fusion_ref_6300"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        const u32 svr = r32(*m, kServerPtr);
        REQUIRE(svr != 0u);
        const u32 vhl = r32(*m, svr + svr::kVhl);
        std::vector<u32> snds;
        for (u32 i = 0; i < 16; ++i)
            if (const u32 s = r32(*m, svr + 4 * i)) snds.push_back(s);
        REQUIRE(snds.size() >= 2u);
        for (const Case& c : kCases) {
            if (sweep_skips(c.addr)) continue;
            const Arg kind = arg_of(c.addr);
            for (std::size_t si = 0; si < snds.size(); ++si) {
                const u32 snd = snds[si];
                const u32 ply = snd + snd::kPlayers;
                const u32 fader = r32(*m, ply + ply::kFader);
                const u32 be = r32(*m, ply + ply::kBackend);
                u64 a0 = 0, a1x = 0;
                switch (kind) {
                case Arg::Snd: a0 = snd; break;
                case Arg::SndPly: a0 = snd; a1x = ply; break;
                case Arg::Fdr: a0 = fader; break;
                case Arg::Bad: a0 = be; break;
                case Arg::Bai: a0 = be; break;  // an ADX back end read as AIX: the AIX methods only forward its handle
                case Arg::Svr: a0 = svr; break;
                case Arg::Vhl: a0 = vhl; break;
                case Arg::None: a0 = snd; break;
                }
                if ((kind == Arg::Svr || kind == Arg::Vhl || kind == Arg::None) && si > 0) break;  // one owner
                for (std::size_t k = 0; k < 3; ++k) {
                    restore(*m, snap);
                    const s64 x = kArgs[(si * 3 + k + c.addr / 8) % 8];
                    const u64 a1 = kind == Arg::SndPly ? a1x : static_cast<u64>(x);
                    const hgp::Run r = pr(*m, c.addr, Args{a0, a1, static_cast<u64>(kArgs[(k + 5) % 8]), 2}, tregs(10, 3));
                    ++ran;
                    stopped += r.stopped ? 1 : 0;
                }
            }
        }
    }
    MESSAGE(ran << " pairs on snapshot state, " << stopped << " stopped (identically) at a callee no test emits");
    MESSAGE(summary());
}

// The fader: conversions against the formulas read from the instructions (the curve-0 level is 3238200 x
// 10^(vol / 200), the curve-1 one 3238200 log10(-vol) / log10(960); both clamped, 0 and -960 exact) and its life on
// a fresh machine: create, start with a delay, fade, hold, the two callbacks, idle.
TEST_CASE("game(libs2): the fader -- volume <-> level, start / update / hold, callbacks") {
    auto m = machine();
    if (!m) return;
    const u32 fdr = kWork;
    // create: the work check (68 bytes) and the reset values
    g_err.clear();
    CHECK(prv(*m, 0x531A28u, Args{fdr, 67, 0, 0}) == 0u);
    CHECK(prv(*m, 0x531A28u, Args{0, 68, 0, 0}) == 0u);
    CHECK(g_err.size() == 4u);  // two texts per pair
    std::memset(m->at(fdr), 0xAB, fdr::kSize);
    CHECK(uv(prv(*m, 0x531A28u, Args{fdr, 68, 0, 0})) == fdr);
    CHECK(r8(*m, fdr + fdr::kStat) == 0);
    CHECK(r32s(*m, fdr + fdr::kVolume) == kSilent);
    CHECK(r32s(*m, fdr + fdr::kTarget) == kSilent);
    CHECK(r32s(*m, fdr + fdr::kPrevTarget) == kSilent);
    CHECK(r32(*m, fdr + fdr::kStartCb) == 0u);
    CHECK(r32(*m, fdr + fdr::kEndCb) == 0u);
    // volume -> level (sub_531F90) and back (sub_531E60), both curves
    for (u8 curve : {u8{0}, u8{1}}) {
        w8(*m, fdr + fdr::kCurve, curve);
        for (s32 vol = kSilent; vol <= 0; vol += 17) {
            const s32 level = sv(prv(*m, 0x531F90u, Args{fdr, sx64(vol), 0, 0}));
            double expect;
            if (vol == 0) expect = kFullLevel;
            else if (vol == kSilent) expect = 0;
            else if (curve == 0) expect = std::pow(10.0, static_cast<double>(static_cast<float>(vol) / 200.0f)) * kFullLevel;
            else expect = kFullLevel * std::log10(static_cast<double>(-vol)) / std::log10(960.0);
            expect = std::min(std::max(expect, 0.0), static_cast<double>(kFullLevel));
            INFO("curve " << int(curve) << " vol " << vol << " level " << level << " expected " << expect);
            CHECK(std::abs(level - expect) <= std::max(2.0, expect * 2e-6));
            if (curve == 0 && vol != kSilent && vol != 0) {
                const s32 back = sv(prv(*m, 0x531E60u, Args{fdr, sx64(level), 0, 0}));
                INFO("back " << back);
                CHECK(std::abs(back - vol) <= 1);  // round trip within one step (truncation)
            }
        }
        CHECK(sv(prv(*m, 0x531E60u, Args{fdr, 0, 0, 0})) == kSilent);
        CHECK(sv(prv(*m, 0x531E60u, Args{fdr, sx64(kFullLevel), 0, 0})) == 0);
    }
    w8(*m, fdr + fdr::kCurve, 0);
    // the step: (level(to) - level(from)) / n, n <= 0 -> the whole range
    CHECK(sv(prv(*m, 0x531DD8u, Args{fdr, sx64(kSilent), 0, 0})) == kFullLevel);
    CHECK(sv(prv(*m, 0x531DD8u, Args{fdr, sx64(kSilent), 0, 10})) == kFullLevel / 10);
    CHECK(sv(prv(*m, 0x531DD8u, Args{fdr, 0, sx64(kSilent), 4})) == -kFullLevel / 4);
    // a life: start from silence to 0 dB in 5 frames after a 2-frame delay, hold 3; callbacks are recorders
    constexpr u32 kStartCbFn = 0x55E978u, kEndCbFn = 0x55EA00u;  // functions no test emits: recorders
    auto rec_pair = [&](u32 addr, Args a, std::vector<StandInCall>* log) {
        const Case& c = by_addr(addr);
        StandIns si;
        install_drivers(si);
        si.install_recorder(kStartCbFn, "start_cb", 0, 2);
        si.install_recorder(kEndCbFn, "end_cb", 0, 2);
        StandInsScope scope{si};
        ++g_pairs[c.name];
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, a, g_seed++, c.name, {});
        CHECK_FALSE(r.stopped);
        if (log) *log = si.log;
        return v0of(r);
    };
    prv(*m, 0x531D48u, Args{fdr, kStartCbFn, 0x11, 0x22});
    prv(*m, 0x531D58u, Args{fdr, kEndCbFn, 0x33, 0x44});
    CHECK(r32(*m, fdr + fdr::kStartArg2) == 0x22u);
    CHECK(r32(*m, fdr + fdr::kEndArg1) == 0x33u);
    CHECK(prv(*m, 0x531B00u, Args{fdr, 0, 5, 2}, tregs(3)) == 1u);  // delay > 0: waits
    CHECK(r8(*m, fdr + fdr::kStat) == 1);
    CHECK(r32s(*m, fdr + fdr::kTarget) == 0);
    CHECK(r32s(*m, fdr + fdr::kPrevTarget) == kSilent);
    CHECK(r32s(*m, fdr + fdr::kStep) == kFullLevel / 5);
    std::vector<int> states;
    int start_calls = 0, end_calls = 0;
    s32 last_vol = kSilent;
    for (int frame = 0; frame < 14; ++frame) {
        std::vector<StandInCall> log;
        rec_pair(0x531C00u, Args{fdr, 0, 0, 0}, &log);
        for (const StandInCall& call : log) {
            if (call.va == kStartCbFn) {
                ++start_calls;
                CHECK(call.args[0] == 0x11u);
                CHECK(call.args[1] == 0x22u);
            }
            if (call.va == kEndCbFn) ++end_calls;
        }
        states.push_back(r8(*m, fdr + fdr::kStat));
        const s32 vol = r32s(*m, fdr + fdr::kVolume);
        CHECK(vol >= last_vol);  // a fade-in never goes down
        last_vol = vol;
    }
    INFO("states: " << [&] { std::string s; for (int x : states) s += std::to_string(x); return s; }());
    CHECK(start_calls == 2);  // once per body
    CHECK(end_calls == 2);
    CHECK(states.front() == 1);
    CHECK(states.back() == 0);
    CHECK(std::count(states.begin(), states.end(), 2) >= 4);
    CHECK(std::count(states.begin(), states.end(), 3) >= 2);
    CHECK(r32s(*m, fdr + fdr::kVolume) == 0);
    CHECK(r32s(*m, fdr + fdr::kLevel) == kFullLevel);
    // reverse while holding: fades again, target and previous target swapped, the step negated
    prv(*m, 0x531B00u, Args{fdr, sx64(-200), 4, 0}, tregs(1));  // frames > 0: state 1 (no delay: fades next frame)
    CHECK(r8(*m, fdr + fdr::kStat) == 1);
    rec_pair(0x531C00u, Args{fdr, 0, 0, 0}, nullptr);
    CHECK(r8(*m, fdr + fdr::kStat) == 2);
    const s32 step = r32s(*m, fdr + fdr::kStep);
    prv(*m, 0x531BC0u, Args{fdr, 0, 0, 0});
    CHECK(r32s(*m, fdr + fdr::kStep) == -step);
    CHECK(r32s(*m, fdr + fdr::kTarget) == 0);
    CHECK(r32s(*m, fdr + fdr::kPrevTarget) == -200);
    MESSAGE(summary());
}

// The back ends: the two 16-entry method tables in the ELF point at exactly these functions, the ADX status map, and
// every method run on the snapshot's live ADX back end; the reset values.
TEST_CASE("game(libs2): the ADX / AIX back ends -- method tables, status map, resets") {
    auto m = machine();
    if (!m) return;
    const u32 adx[16] = {0x5321A8u, 0x532230u, 0x532268u, 0x532280u, 0x532298u, 0x5322B0u, 0x5322C8u, 0x5322E0u,
                         0x5322F8u, 0x532310u, 0x532380u, 0x5323A8u, 0x5323C0u, 0x5323F0u, 0x532420u, 0x532438u};
    const u32 aix[16] = {0x5324E8u, 0x532580u, 0x5325B8u, 0x5325D8u, 0x5325F0u, 0x532608u, 0x532628u, 0x532640u,
                         0x532658u, 0x532670u, 0x532688u, 0x5326F0u, 0x532718u, 0x532740u, 0x532748u, 0x532760u};
    for (u32 i = 0; i < 16; ++i) {
        CHECK(r32(*m, kAdxVtbl + 4 * i) == adx[i]);
        CHECK(r32(*m, kAixVtbl + 4 * i) == aix[i]);
    }
    // resets
    std::memset(m->at(kWork), 0xCD, 16);
    CHECK(uv(prv(*m, 0x532118u, Args{kWork, 12, 0, 0})) == kWork);
    CHECK(r32(*m, kWork + bad::kVtbl) == kAdxVtbl);
    CHECK(r32(*m, kWork + bad::kHndl) == 0u);
    CHECK(r32(*m, kWork + bad::kNch) == 0u);
    CHECK(prv(*m, 0x532118u, Args{kWork, 11, 0, 0}) == 0u);
    std::memset(m->at(kWork), 0xCD, 16);
    CHECK(uv(prv(*m, 0x532458u, Args{kWork, 16, 0, 0})) == kWork);
    CHECK(r32(*m, kWork + bai::kVtbl) == kAixVtbl);
    CHECK(r32(*m, kWork + bai::kNumTrack) == 0u);
    CHECK(prv(*m, 0x532458u, Args{kWork, 15, 0, 0}) == 0u);
    // the ADX status map on the dorm snapshot's live player: ADXT's state byte (+1) 0..7
    const std::vector<u8> snap = snapshot("dorm_replay_4900");
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 svr = r32(*m, kServerPtr);
    const u32 snd = r32(*m, svr);
    const u32 be = r32(*m, snd + snd::kPlayers + ply::kBackend);
    const u32 adxt = r32(*m, be + bad::kHndl);
    REQUIRE(r32(*m, be + bad::kVtbl) == kAdxVtbl);
    const u32 expect_map[8] = {0, 1, 1, 2, 2, 3, 4, 4};
    for (u32 st = 0; st < 8; ++st) {
        restore(*m, snap);
        w8(*m, adxt + 1, static_cast<u8>(st));
        CHECK(uv(prv(*m, 0x532310u, Args{be, 0, 0, 0})) == expect_map[st]);
        if (st < 7) CHECK(r32(*m, kAdxStatMap + 4 * st) != 0u);  // the jump table's case blocks
    }
    // the handle accessor and the track-0-only rule
    restore(*m, snap);
    CHECK(uv(prv(*m, 0x532438u, Args{be, 0, 0, 0})) == adxt);
    CHECK(prv(*m, 0x5323F0u, Args{be, 1, 0, 0}) == 0u);
    CHECK(uv(prv(*m, 0x532760u, Args{be, 0, 0, 0})) == adxt);  // the AIX accessor reads the same slot
    CHECK(prv(*m, 0x532740u, Args{be, 0, 0, 0}) == 0u);
    MESSAGE(summary());
}

// The sound object on the snapshots: the start requests are stored before the start runs, the accessors and setters
// of the public thunks, the ADXT / AIXP handle getters by mode, the busy / kind / volume fields; every rule checked on
// both bodies' result (the recompiled run's memory).
TEST_CASE("game(libs2): sound requests, accessors and the public thunks on the dorm snapshot") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot("dorm_replay_4900");
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 svr = r32(*m, kServerPtr);
    const u32 bgm = r32(*m, svr);
    REQUIRE(r32(*m, bgm + snd::kInit) == 1u);
    REQUIRE(r32(*m, bgm + snd::kNumPlayer) == 1u);
    // the game's settings (0x108740 sets them: fade-in 1, fade-out 30, cross 35, volume-change 15, hold 10)
    CHECK(r32s(*m, bgm + snd::kFadeOutTime) == 30);
    CHECK(r32s(*m, bgm + snd::kFadeInTime) == 1);
    CHECK(r32s(*m, bgm + snd::kVolChgTime) == 15);
    CHECK(r32s(*m, bgm + snd::kCrossOffset) == 55);
    CHECK(r32s(*m, bgm + snd::kHoldTime) == 10);
    // setters / getters through the public thunks
    const std::pair<u32, u32> setget[] = {{0x54D238u, 0x54D280u}, {0x54D250u, 0x54D298u}, {0x54D2B0u, 0x54D2C8u},
                                          {0x54D2E0u, 0x54D2F8u}};
    for (const auto& [set, get] : setget) {
        restore(*m, snap);
        prv(*m, set, Args{bgm, 77, 0, 0});
        CHECK(prv(*m, get, Args{bgm, 0, 0, 0}) == 77u);
    }
    restore(*m, snap);
    prv(*m, 0x54D178u, Args{bgm, 2, 0, 0});
    CHECK(prv(*m, 0x54D190u, Args{bgm, 0, 0, 0}) == 2u);
    prv(*m, 0x54D310u, Args{bgm, 0x1234560, 0, 0});
    CHECK(r32(*m, bgm + snd::kCbFunc) == 0x1234560u);
    CHECK(uv(prv(*m, 0x54D160u, Args{bgm, 0, 0, 0})) == bgm + snd::kCprm);
    CHECK(prv(*m, 0x54D268u, Args{bgm, 0, 0, 0}) == 30u);
    // the start requests: stored, then the start runs (into ADXT; its drivers stood in)
    restore(*m, snap);
    pr(*m, 0x54D0B8u, Args{bgm, 3, 7, 0});
    CHECK(r32(*m, bgm + snd::kReqType) == 1u);
    CHECK(r32(*m, bgm + snd::kReqPtid) == 3u);
    CHECK(r32(*m, bgm + snd::kReqFlid) == 7u);
    CHECK(static_cast<s8>(r8(*m, bgm + snd::kBusy)) == 1);
    restore(*m, snap);
    pr(*m, 0x54D0D0u, Args{bgm, 0x1500000, 0x8000, 0});
    CHECK(r32(*m, bgm + snd::kReqType) == 2u);
    CHECK(r32(*m, bgm + snd::kReqMem) == 0x1500000u);
    CHECK(r32(*m, bgm + snd::kReqMemSize) == 0x8000u);
    restore(*m, snap);
    pr(*m, 0x54D0E8u, Args{bgm, 0x1500000, 5, 0});
    CHECK(r32(*m, bgm + snd::kReqType) == 3u);
    CHECK(r32(*m, bgm + snd::kReqEntry) == 5u);
    restore(*m, snap);
    m->put(kWork, "BGM\\TEST.ADX");
    pr(*m, 0x54D0A0u, Args{bgm, kWork, 0, 0});
    CHECK(r32(*m, bgm + snd::kReqType) == 0u);
    CHECK(m->str(r32(*m, bgm + snd::kReqName)) == "BGM\\TEST.ADX");
    // a sound that is not initialised: every guarded method reports and does nothing
    restore(*m, snap);
    w32(*m, bgm + snd::kInit, 0);
    g_err.clear();
    CHECK(prv(*m, 0x533160u, Args{bgm, 0, 0, 0}) == 4u);
    CHECK(prv(*m, 0x5331A8u, Args{bgm, 0, 0, 0}) == 4u);
    CHECK(prv(*m, 0x5331F0u, Args{bgm, 0, 0, 0}) == 0u);
    pr(*m, 0x532E70u, Args{bgm, 3, 7, 0});
    { u32 was; std::memcpy(&was, snap.data() + bgm + snd::kReqType, 4); CHECK(r32(*m, bgm + snd::kReqType) == was); }
    CHECK(g_err.size() == 8u);
    // the handle getters: ADX mode
    restore(*m, snap);
    const u32 be = r32(*m, bgm + snd::kPlayers + ply::kBackend);
    const u32 adxt = r32(*m, be + bad::kHndl);
    CHECK(uv(prv(*m, 0x54D378u, Args{bgm, 0, 0, 0})) == adxt);
    CHECK(uv(prv(*m, 0x54D3A8u, Args{bgm, 0, 0, 0})) == adxt);
    CHECK(prv(*m, 0x54D3A8u, Args{bgm, 1, 0, 0}) == 0u);  // n out of range
    CHECK(prv(*m, 0x54D3C0u, Args{bgm, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x54D3D8u, Args{bgm, 0, 0, 0}) == 0u);  // no AIXP in ADX mode
    CHECK(prv(*m, 0x54D420u, Args{bgm, 0, 0, 0}) == 0u);
    // ... and AIX mode (the configuration's AIX flag set): the AIX getters answer, the ADX ones 0
    w32(*m, bgm + snd::kCprmAix, 1);
    CHECK(prv(*m, 0x54D378u, Args{bgm, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x54D420u, Args{bgm, 0, 0, 0}) == 1u);
    // the track volume getter: AIX only, index checked against the configuration's tracks
    w32(*m, bgm + snd::kCprmNumTrack, 2);
    w32(*m, bgm + snd::kTrackVol, kWork + 0x100);
    w32(*m, kWork + 0x100, static_cast<u32>(-40));
    w32(*m, kWork + 0x104, static_cast<u32>(-80));
    CHECK(sv(prv(*m, 0x54D1F0u, Args{bgm, 1, 0, 0})) == -80);
    CHECK(prv(*m, 0x54D1F0u, Args{bgm, 2, 0, 0}) == 0u);
    // the work-size rule: the public CalcWorkSize on the game's own configuration (0x7E42E0) against the formula
    restore(*m, snap);
    for (u32 cfgva : {0x7E42E0u, 0x7E4330u}) {
        const u32 sz = uv(prv(*m, 0x54D080u, Args{cfgva, 0, 0, 0}));
        const s32 c0 = r32s(*m, cfgva), c1 = r32s(*m, cfgva + 4), c2 = r32s(*m, cfgva + 8), c3 = r32s(*m, cfgva + 12),
                  c4 = r32s(*m, cfgva + 16), c6 = r32s(*m, cfgva + 24), c7 = r32s(*m, cfgva + 28), c8 = r32s(*m, cfgva + 32),
                  c9 = r32s(*m, cfgva + 36);
        // the ADX branch (no AIX, no +36 layout -- the game's configurations): per player the input buffer of
        // channels x (rate / 1000) x 25000 / 44 x (+0 + 1) bytes rounded to the nearest 2 KiB, plus 36, times +16,
        // plus the PCM buffers 16576 x channels and 76 (the back end and the player's extra), plus 12,288 with AHX and
        // 68 for the fader; doubled for two players; plus 464 (the sound and the server's share)
        REQUIRE(c7 == 0);
        REQUIRE(c9 == 0);
        (void)c3;
        const s32 raw = c1 * (c2 / 1000) * 25000 / 44 * (c0 + 1);
        const s32 rounded = ((raw + 2048) >> 11) << 11;
        s32 per = (rounded + 36) * c4 + 16576 * c1 + 76;
        if (c8) per += 12288;
        per += 68;
        if (c6) per *= 2;
        const s32 expect = per + 464;
        INFO("config " << hex64(cfgva) << " size " << sz);
        CHECK(sv(sz) == expect);
    }
    MESSAGE(summary());
}

// The server: slot rules (16 slots, 'Can't create sound any more', 'Not initialized'), destroy frees the slot, the
// init count; and the ducking object on the battle snapshot (a voice playing lowers kind-1 sounds by the depth).
TEST_CASE("game(libs2): the server's slots and the ducking object") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot("dorm_replay_4900");
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 svr = r32(*m, kServerPtr);
    CHECK(r32s(*m, svr + svr::kInitCnt) == 2);
    CHECK(prv(*m, 0x5351B0u, Args{svr, 0, 0, 0}) == 1u);
    CHECK(uv(prv(*m, 0x535170u, Args{svr, 0, 0, 0})) == svr + svr::kVhlWork);
    // all 16 slots taken: no sound is made, the error is reported
    for (u32 i = 0; i < 16; ++i)
        if (!r32(*m, svr + 4 * i)) w32(*m, svr + 4 * i, 0x100 + i);
    g_err.clear();
    CHECK(prv(*m, 0x534C98u, Args{svr, 0x7E42E0u, kWork, 0x10000}) == 0u);
    CHECK(g_err.size() == 2u);
    if (!g_err.empty()) CHECK(g_err[0].find("Can't create sound any more") != std::string::npos);
    // not initialised
    restore(*m, snap);
    w32(*m, svr + svr::kInitCnt, 0);
    g_err.clear();
    CHECK(prv(*m, 0x534C98u, Args{svr, 0x7E42E0u, kWork, 0x10000}) == 0u);
    if (!g_err.empty()) CHECK(g_err[0].find("Not initialized") != std::string::npos);
    CHECK(prv(*m, 0x5351B0u, Args{svr, 0, 0, 0}) == 0u);
    // destroy a sound through the public thunk: its slot is freed, the other stays
    restore(*m, snap);
    const u32 s0 = r32(*m, svr), s1 = r32(*m, svr + 4);
    pr(*m, 0x54D060u, Args{s1, 0, 0, 0});
    CHECK(r32(*m, svr + 4) == 0u);
    CHECK(r32(*m, svr) == s0);
    CHECK(r32(*m, s1 + snd::kInit) == 0u);  // finished and reset
    // the ducking object: reset values, the public setters, the frames-left rules
    restore(*m, snap);
    const u32 vhl = r32(*m, svr + svr::kVhl);
    CHECK(r32(*m, vhl + vhl::kServer) == svr);
    CHECK(r32s(*m, vhl + vhl::kDownTime) == 15);
    CHECK(r32s(*m, vhl + vhl::kUpTime) == 180);
    CHECK(r32s(*m, vhl + vhl::kDepth) == 60);
    prv(*m, 0x54D490u, Args{0, 0, 0, 0});
    CHECK(r32(*m, vhl + vhl::kEnable) == 0u);
    prv(*m, 0x54D468u, Args{0, 0, 0, 0});
    CHECK(r32(*m, vhl + vhl::kEnable) == 1u);
    prv(*m, 0x54D4B8u, Args{25, 0, 0, 0});
    prv(*m, 0x54D4F0u, Args{90, 0, 0, 0});
    CHECK(r32s(*m, vhl + vhl::kDownTime) == 25);
    CHECK(r32s(*m, vhl + vhl::kUpTime) == 90);
    const u32 vf = r32(*m, vhl + vhl::kFader);
    for (s32 vol : {0, -20, -30, -60}) {
        w32(*m, vf + fdr::kVolume, static_cast<u32>(vol));
        const s32 depth = 60;
        CHECK(sv(prv(*m, 0x535618u, Args{vhl, 0, 0, 0})) == 25 - (vol * 25) / -depth);
        CHECK(sv(prv(*m, 0x535668u, Args{vhl, 0, 0, 0})) == 25 - (vol * 90) / -depth);
    }
    std::memset(m->at(kWork), 0xEE, vhl::kSize);
    prv(*m, 0x5355B8u, Args{kWork, 0, 0, 0});
    CHECK(r32s(*m, kWork + vhl::kDownTime) == 30);
    CHECK(r32s(*m, kWork + vhl::kUpTime) == 60);
    CHECK(r32s(*m, kWork + vhl::kDepth) == 120);
    CHECK(r8(*m, kWork + vhl::kStat) == 0);
    // ducking on the battle snapshot: state 3 (restoring) with a fade under way; frames of the ducking frame step it
    // back to 0 dB and idle once no kind-2 sound plays
    const std::vector<u8> bsnap = snapshot("battle_ref_6150");
    if (bsnap.empty()) return;
    restore(*m, bsnap);
    const u32 bvhl = r32(*m, r32(*m, kServerPtr) + svr::kVhl);
    const u32 bvf = r32(*m, bvhl + vhl::kFader);
    CHECK(static_cast<s8>(r8(*m, bvhl + vhl::kStat)) == 3);
    // silence every kind-2 sound's status (their players' ADXT state 0 = stopped)
    const u32 bsvr = r32(*m, kServerPtr);
    for (u32 i = 0; i < 16; ++i) {
        const u32 s = r32(*m, bsvr + 4 * i);
        if (!s || static_cast<s8>(r8(*m, s + snd::kKind)) != 2) continue;
        const u32 be = r32(*m, s + snd::kPlayers + ply::kBackend);
        w8(*m, r32(*m, be + bad::kHndl) + 1, 0);
    }
    s32 last = r32s(*m, bvf + fdr::kVolume);
    int frames = 0;
    while (static_cast<s8>(r8(*m, bvhl + vhl::kStat)) != 0 && frames < 400) {
        pr(*m, 0x5353A8u, Args{bvhl, 0, 0, 0});
        const s32 v = r32s(*m, bvf + fdr::kVolume);
        CHECK(v >= last);
        last = v;
        ++frames;
    }
    INFO("frames " << frames);
    CHECK(static_cast<s8>(r8(*m, bvhl + vhl::kStat)) == 0);
    CHECK(r32s(*m, bvf + fdr::kVolume) == 0);
    MESSAGE(summary());
}

// Lifecycles: a server built and torn down on a fresh machine (create, init twice, finish twice, finish-all; the
// ducking object and its fader made by the first init), and a sound created on the dorm snapshot's live server with
// the game's own configuration (the ADXT player made through ADXT_Create, PS2RNA / ADXSTM / the list streamer
// answering with fake handles) in a work of exactly CalcWorkSize bytes, then destroyed; a work too small unwinds.
TEST_CASE("game(libs2): server and sound lifecycles") {
    auto m = machine();
    if (!m) return;
    constexpr u32 kFakeRna = 0x01A00000u, kFakeStm = 0x01A00100u, kFakeLsc = 0x01A00200u, kFakeAdxb = 0x01A00300u;
    auto life_pair = [&](u32 addr, Args a) {
        const Case& c = by_addr(addr);
        StandIns si;
        install_drivers(si);
        si.install_recorder(0x5419F8u, "PS2RNA_Create", kFakeRna, 3);
        si.install_recorder(0x545FC8u, "ADXSTM_Create", kFakeStm, 3);
        si.install_recorder(0x55D2A0u, "LSC_Create", kFakeLsc, 3);
        si.install_recorder(0x537890u, "ADXB_Create", kFakeAdxb, 3);
        StandInsScope scope{si};
        ++g_pairs[c.name];
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, a, g_seed++, c.name, {});
        INFO(c.name);
        CHECK_FALSE(r.stopped);
        return v0of(r);
    };
    // the server on a fresh machine
    const u32 svr = kWork;
    std::memset(m->at(svr), 0x5A, 0x200);
    CHECK(prv(*m, 0x5349F8u, Args{svr, 175, 0, 0}) == 0u);
    CHECK(uv(prv(*m, 0x5349F8u, Args{svr, 176, 0, 0})) == svr);
    for (u32 i = 0; i < 16; ++i) CHECK(r32(*m, svr + 4 * i) == 0u);
    CHECK(r32(*m, svr + svr::kInitCnt) == 0u);
    CHECK(prv(*m, 0x534A88u, Args{svr, 0, 0, 0}) == 1u);
    CHECK(r32s(*m, svr + svr::kInitCnt) == 1);
    const u32 vhl = r32(*m, svr + svr::kVhl);
    CHECK(vhl == svr + svr::kVhlWork);
    CHECK(r32(*m, vhl + vhl::kServer) == svr);
    CHECK(r32(*m, vhl + vhl::kFader) == vhl + vhl::kFaderWork);
    CHECK(r32s(*m, vhl + vhl::kDepth) == 120);
    CHECK(prv(*m, 0x534A88u, Args{svr, 0, 0, 0}) == 1u);  // counted
    CHECK(r32s(*m, svr + svr::kInitCnt) == 2);
    prv(*m, 0x534B60u, Args{svr, 0, 0, 0});
    CHECK(r32s(*m, svr + svr::kInitCnt) == 1);
    CHECK(r32(*m, svr + svr::kVhl) == vhl);  // still there
    prv(*m, 0x534B60u, Args{svr, 0, 0, 0});
    CHECK(r32s(*m, svr + svr::kInitCnt) == 0);
    CHECK(r32(*m, svr + svr::kVhl) == 0u);  // released by the last finish
    g_err.clear();
    prv(*m, 0x534B60u, Args{svr, 0, 0, 0});  // one too many
    CHECK(g_err.size() == 2u);
    if (!g_err.empty()) CHECK(g_err[0].find("Too many Finish") != std::string::npos);
    w32(*m, svr + svr::kInitCnt, 0);
    prv(*m, 0x534A88u, Args{svr, 0, 0, 0});
    prv(*m, 0x534A88u, Args{svr, 0, 0, 0});
    prv(*m, 0x534A88u, Args{svr, 0, 0, 0});
    prv(*m, 0x534C58u, Args{svr, 0, 0, 0});  // finish while initialised
    CHECK(r32s(*m, svr + svr::kInitCnt) == 0);
    // a sound on the dorm snapshot's server, from the game's configuration, in a work of CalcWorkSize bytes
    const std::vector<u8> snap = snapshot("dorm_replay_4900");
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 live = r32(*m, kServerPtr);
    constexpr u32 kCfg = 0x7E42E0u;
    const u32 size = uv(prv(*m, 0x54D080u, Args{kCfg, 0, 0, 0}));
    const u32 work = 0x01A10000u;
    std::memset(m->at(work), 0, size + 64);
    g_err.clear();
    const u32 snd = uv(life_pair(0x54D030u, Args{kCfg, work, size, 0}));
    for (const std::string& e : g_err) MESSAGE("error text: " << e);
    CHECK(snd == work);
    CHECK(r32(*m, live + 8) == snd);  // the first free slot (two sounds live)
    CHECK(r32(*m, snd + snd::kInit) == 1u);
    CHECK(r32(*m, snd + snd::kNumPlayer) == 1u);
    CHECK(r32(*m, snd + snd::kCprmSfreq) == 48000u);
    const u32 be = r32(*m, snd + snd::kPlayers + ply::kBackend);
    CHECK(r32(*m, be + bad::kVtbl) == kAdxVtbl);
    CHECK(r32(*m, be + bad::kNch) == 2u);
    CHECK(r32(*m, be + bad::kHndl) >= 0x787570u);  // an ADXT handle of the pool (16 x 200)
    CHECK(r32(*m, be + bad::kHndl) < 0x787570u + 16 * 200);
    const u32 fader = r32(*m, snd + snd::kPlayers + ply::kFader);
    CHECK(fader > be);
    CHECK(fader + fdr::kSize <= work + size);
    CHECK(r32s(*m, fader + fdr::kVolume) == kSilent);
    CHECK(r32(*m, snd + snd::kReqName) == r32(*m, snd + snd::kNameBuf));
    CHECK(r32(*m, snd + snd::kNameBuf) + 256 <= work + size);
    life_pair(0x54D060u, Args{snd, 0, 0, 0});
    CHECK(r32(*m, live + 8) == 0u);
    CHECK(r32(*m, snd + snd::kInit) == 0u);
    // the steps one by one: create (the 208-byte check, the reset values), init straight from the configuration
    restore(*m, snap);
    CHECK(prv(*m, 0x532788u, Args{work, 207, 0, 0}) == 0u);
    std::memset(m->at(work), 0x77, snd::kSize);
    CHECK(uv(prv(*m, 0x532788u, Args{work, 208, 0, 0})) == work);
    CHECK(r32s(*m, work + snd::kFadeOutTime) == 30);
    CHECK(r32s(*m, work + snd::kHoldTime) == 60);
    CHECK(r32(*m, work + snd::kInit) == 0u);
    CHECK(r32(*m, work + snd::kCbFunc) == 0u);
    CHECK(life_pair(0x532818u, Args{work, kCfg, work + snd::kSize, size - snd::kSize}) == 1u);
    CHECK(r32(*m, work + snd::kInit) == 1u);
    CHECK(r32(*m, work + snd::kIniting) == 0u);
    g_err.clear();
    CHECK(life_pair(0x532818u, Args{work, kCfg, work + snd::kSize, size - snd::kSize}) == 0u);  // twice
    if (!g_err.empty()) CHECK(g_err[0].find("Already initialized") != std::string::npos);
    // the ducking object's create: the 96-byte check
    CHECK(prv(*m, 0x5351E8u, Args{kWork, 95, 0, 0}) == 0u);
    CHECK(uv(prv(*m, 0x5351E8u, Args{kWork, 96, 0, 0})) == kWork);
    CHECK(r32s(*m, kWork + vhl::kUpTime) == 60);
    // too small: 'Specified work area size is too small', the sound unwound and its slot freed
    restore(*m, snap);
    g_err.clear();
    CHECK(life_pair(0x54D030u, Args{kCfg, work, 4096, 0}) == 0u);
    CHECK(r32(*m, live + 8) == 0u);
    bool too_small = false;
    for (const std::string& e : g_err) too_small = too_small || e.find("too small") != std::string::npos;
    CHECK(too_small);
    MESSAGE(summary());
}

#else

TEST_CASE("game(libs2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
