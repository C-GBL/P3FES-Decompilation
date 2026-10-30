// Pair tests for slice savedata (game/src/data/savedata.cpp: the save system). Every body against its recompiled body,
// compared by tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the
// return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log.
//   1. the generic sweep: random words and pointers in a scratch window (mostly the bad-input and early-stop paths);
//   2. THE SAVE FORMAT on real data: the save the game itself wrote on extracted/_ours/cards/tartarus.ps2 (read from the
//      card image's file system by a small reader below) checked against savedata.h byte for byte on the host --
//      version, header, every block's id / size / order, the header sum, the checksum, the terminator;
//   3. ROUND TRIPS through the bodies on the replay snapshots: verify (and corrupted copies), unpack, pack again --
//      pack(unpack(file)) equals the file except the fields the packer re-reads from the live game; and a SAVE
//      TRANSFER: each snapshot's state packed, then unpacked on another snapshot's machine, lands block for block;
//   4. documented rules on the snapshots' game state: the compendium (get / compare / register / completion), the
//      tables of blocks 27..31, the H_Memcard request words, the 500-word list, the message-window result, the
//      name-entry buffers, the animation tracks, the field-event helpers, the personas of the stock.
// The stand-in world (stand_ins.h) serves the heap behind the RW slots, printf / sprintf and the H_Cdvd layer, and a
// recorder answers every callee this build does not emit.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/savedata.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_173C60_00173c60(EEContext&);  // generated body
void fn_sub_173C60_00173c60__recomp(EEContext&);  // recompiled
void fn_sub_174C10_00174c10(EEContext&);  // generated body
void fn_sub_174C10_00174c10__recomp(EEContext&);  // recompiled
void fn_sub_175820_00175820(EEContext&);  // generated body
void fn_sub_175820_00175820__recomp(EEContext&);  // recompiled
void fn_sub_175CE0_00175ce0(EEContext&);  // generated body
void fn_sub_175CE0_00175ce0__recomp(EEContext&);  // recompiled
void fn_sub_177DB0_00177db0(EEContext&);  // generated body
void fn_sub_177DB0_00177db0__recomp(EEContext&);  // recompiled
void fn_sub_179030_00179030(EEContext&);  // generated body
void fn_sub_179030_00179030__recomp(EEContext&);  // recompiled
void fn_sub_1791D0_001791d0(EEContext&);  // generated body
void fn_sub_1791D0_001791d0__recomp(EEContext&);  // recompiled
void fn_sub_179360_00179360(EEContext&);  // generated body
void fn_sub_179360_00179360__recomp(EEContext&);  // recompiled
void fn_sub_17A430_0017a430(EEContext&);  // generated body
void fn_sub_17A430_0017a430__recomp(EEContext&);  // recompiled
void fn_sub_17C2F0_0017c2f0(EEContext&);  // generated body
void fn_sub_17C2F0_0017c2f0__recomp(EEContext&);  // recompiled
void fn_sub_17C350_0017c350(EEContext&);  // generated body
void fn_sub_17C350_0017c350__recomp(EEContext&);  // recompiled
void fn_sub_17C4E0_0017c4e0(EEContext&);  // generated body
void fn_sub_17C4E0_0017c4e0__recomp(EEContext&);  // recompiled
void fn_sub_17C590_0017c590(EEContext&);  // generated body
void fn_sub_17C590_0017c590__recomp(EEContext&);  // recompiled
void fn_sub_17C610_0017c610(EEContext&);  // generated body
void fn_sub_17C610_0017c610__recomp(EEContext&);  // recompiled
void fn_sub_17C670_0017c670(EEContext&);  // generated body
void fn_sub_17C670_0017c670__recomp(EEContext&);  // recompiled
void fn_sub_17C6C0_0017c6c0(EEContext&);  // generated body
void fn_sub_17C6C0_0017c6c0__recomp(EEContext&);  // recompiled
void fn_sub_17C6E0_0017c6e0(EEContext&);  // generated body
void fn_sub_17C6E0_0017c6e0__recomp(EEContext&);  // recompiled
void fn_sub_17C700_0017c700(EEContext&);  // generated body
void fn_sub_17C700_0017c700__recomp(EEContext&);  // recompiled
void fn_sub_17C750_0017c750(EEContext&);  // generated body
void fn_sub_17C750_0017c750__recomp(EEContext&);  // recompiled
void fn_sub_17C7F0_0017c7f0(EEContext&);  // generated body
void fn_sub_17C7F0_0017c7f0__recomp(EEContext&);  // recompiled
void fn_sub_17C860_0017c860(EEContext&);  // generated body
void fn_sub_17C860_0017c860__recomp(EEContext&);  // recompiled
void fn_sub_17C8C0_0017c8c0(EEContext&);  // generated body
void fn_sub_17C8C0_0017c8c0__recomp(EEContext&);  // recompiled
void fn_sub_17C960_0017c960(EEContext&);  // generated body
void fn_sub_17C960_0017c960__recomp(EEContext&);  // recompiled
void fn_sub_17CA10_0017ca10(EEContext&);  // generated body
void fn_sub_17CA10_0017ca10__recomp(EEContext&);  // recompiled
void fn_sub_17CD30_0017cd30(EEContext&);  // generated body
void fn_sub_17CD30_0017cd30__recomp(EEContext&);  // recompiled
void fn_sub_17CF00_0017cf00(EEContext&);  // generated body
void fn_sub_17CF00_0017cf00__recomp(EEContext&);  // recompiled
void fn_sub_17D030_0017d030(EEContext&);  // generated body
void fn_sub_17D030_0017d030__recomp(EEContext&);  // recompiled
void fn_sub_17D040_0017d040(EEContext&);  // generated body
void fn_sub_17D040_0017d040__recomp(EEContext&);  // recompiled
void fn_sub_17D060_0017d060(EEContext&);  // generated body
void fn_sub_17D060_0017d060__recomp(EEContext&);  // recompiled
void fn_sub_17D1A0_0017d1a0(EEContext&);  // generated body
void fn_sub_17D1A0_0017d1a0__recomp(EEContext&);  // recompiled
void fn_sub_17D250_0017d250(EEContext&);  // generated body
void fn_sub_17D250_0017d250__recomp(EEContext&);  // recompiled
void fn_sub_17D2E0_0017d2e0(EEContext&);  // generated body
void fn_sub_17D2E0_0017d2e0__recomp(EEContext&);  // recompiled
void fn_sub_17D3C0_0017d3c0(EEContext&);  // generated body
void fn_sub_17D3C0_0017d3c0__recomp(EEContext&);  // recompiled
void fn_sub_17D450_0017d450(EEContext&);  // generated body
void fn_sub_17D450_0017d450__recomp(EEContext&);  // recompiled
void fn_sub_17D610_0017d610(EEContext&);  // generated body
void fn_sub_17D610_0017d610__recomp(EEContext&);  // recompiled
void fn_sub_17D6D0_0017d6d0(EEContext&);  // generated body
void fn_sub_17D6D0_0017d6d0__recomp(EEContext&);  // recompiled
void fn_sub_17D700_0017d700(EEContext&);  // generated body
void fn_sub_17D700_0017d700__recomp(EEContext&);  // recompiled
void fn_sub_17D790_0017d790(EEContext&);  // generated body
void fn_sub_17D790_0017d790__recomp(EEContext&);  // recompiled
void fn_sub_17D7B0_0017d7b0(EEContext&);  // generated body
void fn_sub_17D7B0_0017d7b0__recomp(EEContext&);  // recompiled
void fn_sub_18F170_0018f170(EEContext&);  // generated body
void fn_sub_18F170_0018f170__recomp(EEContext&);  // recompiled
void fn_sub_18F2A0_0018f2a0(EEContext&);  // generated body
void fn_sub_18F2A0_0018f2a0__recomp(EEContext&);  // recompiled
void fn_sub_18F2B0_0018f2b0(EEContext&);  // generated body
void fn_sub_18F2B0_0018f2b0__recomp(EEContext&);  // recompiled
void fn_sub_190580_00190580(EEContext&);  // generated body
void fn_sub_190580_00190580__recomp(EEContext&);  // recompiled
void fn_sub_190700_00190700(EEContext&);  // generated body
void fn_sub_190700_00190700__recomp(EEContext&);  // recompiled
void fn_sub_190CB0_00190cb0(EEContext&);  // generated body
void fn_sub_190CB0_00190cb0__recomp(EEContext&);  // recompiled
void fn_sub_191640_00191640(EEContext&);  // generated body
void fn_sub_191640_00191640__recomp(EEContext&);  // recompiled
void fn_sub_1919C0_001919c0(EEContext&);  // generated body
void fn_sub_1919C0_001919c0__recomp(EEContext&);  // recompiled
void fn_sub_41BE50_0041be50(EEContext&);  // generated body
void fn_sub_41BE50_0041be50__recomp(EEContext&);  // recompiled
void fn_sub_41BEB0_0041beb0(EEContext&);  // generated body
void fn_sub_41BEB0_0041beb0__recomp(EEContext&);  // recompiled
void fn_sub_41BEE0_0041bee0(EEContext&);  // generated body
void fn_sub_41BEE0_0041bee0__recomp(EEContext&);  // recompiled
void fn_sub_41BF10_0041bf10(EEContext&);  // generated body
void fn_sub_41BF10_0041bf10__recomp(EEContext&);  // recompiled
void fn_sub_41C140_0041c140(EEContext&);  // generated body
void fn_sub_41C140_0041c140__recomp(EEContext&);  // recompiled
void fn_sub_41C180_0041c180(EEContext&);  // generated body
void fn_sub_41C180_0041c180__recomp(EEContext&);  // recompiled
void fn_sub_41CC70_0041cc70(EEContext&);  // generated body
void fn_sub_41CC70_0041cc70__recomp(EEContext&);  // recompiled
void fn_sub_41CEA0_0041cea0(EEContext&);  // generated body
void fn_sub_41CEA0_0041cea0__recomp(EEContext&);  // recompiled
void fn_sub_41D120_0041d120(EEContext&);  // generated body
void fn_sub_41D120_0041d120__recomp(EEContext&);  // recompiled
void fn_sub_41D330_0041d330(EEContext&);  // generated body
void fn_sub_41D330_0041d330__recomp(EEContext&);  // recompiled
void fn_sub_41DB20_0041db20(EEContext&);  // generated body
void fn_sub_41DB20_0041db20__recomp(EEContext&);  // recompiled
void fn_sub_41E010_0041e010(EEContext&);  // generated body
void fn_sub_41E010_0041e010__recomp(EEContext&);  // recompiled
void fn_sub_41E830_0041e830(EEContext&);  // generated body
void fn_sub_41E830_0041e830__recomp(EEContext&);  // recompiled
void fn_sub_41EAF0_0041eaf0(EEContext&);  // generated body
void fn_sub_41EAF0_0041eaf0__recomp(EEContext&);  // recompiled
void fn_Y_McProc_UpdateMcProcDrawTask_0041eb50(EEContext&);  // generated body
void fn_Y_McProc_UpdateMcProcDrawTask_0041eb50__recomp(EEContext&);  // recompiled
void fn_sub_41EC30_0041ec30(EEContext&);  // generated body
void fn_sub_41EC30_0041ec30__recomp(EEContext&);  // recompiled
void fn_nullsub_59_0041ec60(EEContext&);  // generated body
void fn_nullsub_59_0041ec60__recomp(EEContext&);  // recompiled
void fn_sub_41EC70_0041ec70(EEContext&);  // generated body
void fn_sub_41EC70_0041ec70__recomp(EEContext&);  // recompiled
void fn_sub_41ECA0_0041eca0(EEContext&);  // generated body
void fn_sub_41ECA0_0041eca0__recomp(EEContext&);  // recompiled
void fn_sub_41EF40_0041ef40(EEContext&);  // generated body
void fn_sub_41EF40_0041ef40__recomp(EEContext&);  // recompiled
void fn_sub_41F370_0041f370(EEContext&);  // generated body
void fn_sub_41F370_0041f370__recomp(EEContext&);  // recompiled
void fn_sub_41F940_0041f940(EEContext&);  // generated body
void fn_sub_41F940_0041f940__recomp(EEContext&);  // recompiled
void fn_sub_41FD90_0041fd90(EEContext&);  // generated body
void fn_sub_41FD90_0041fd90__recomp(EEContext&);  // recompiled
void fn_sub_41FF50_0041ff50(EEContext&);  // generated body
void fn_sub_41FF50_0041ff50__recomp(EEContext&);  // recompiled
void fn_sub_4202E0_004202e0(EEContext&);  // generated body
void fn_sub_4202E0_004202e0__recomp(EEContext&);  // recompiled
void fn_Y_McProc_CreateMcProcDrawTask_00420340(EEContext&);  // generated body
void fn_Y_McProc_CreateMcProcDrawTask_00420340__recomp(EEContext&);  // recompiled
void fn_sub_4204F0_004204f0(EEContext&);  // generated body
void fn_sub_4204F0_004204f0__recomp(EEContext&);  // recompiled
void fn_sub_420520_00420520(EEContext&);  // generated body
void fn_sub_420520_00420520__recomp(EEContext&);  // recompiled
void fn_sub_420A20_00420a20(EEContext&);  // generated body
void fn_sub_420A20_00420a20__recomp(EEContext&);  // recompiled
void fn_sub_420DA0_00420da0(EEContext&);  // generated body
void fn_sub_420DA0_00420da0__recomp(EEContext&);  // recompiled
void fn_sub_420F60_00420f60(EEContext&);  // generated body
void fn_sub_420F60_00420f60__recomp(EEContext&);  // recompiled
void fn_sub_420F90_00420f90(EEContext&);  // generated body
void fn_sub_420F90_00420f90__recomp(EEContext&);  // recompiled
void fn_sub_420FE0_00420fe0(EEContext&);  // generated body
void fn_sub_420FE0_00420fe0__recomp(EEContext&);  // recompiled
void fn_Y_Misc_UpdateMcWNDProcTask_00421330(EEContext&);  // generated body
void fn_Y_Misc_UpdateMcWNDProcTask_00421330__recomp(EEContext&);  // recompiled
void fn_sub_421460_00421460(EEContext&);  // generated body
void fn_sub_421460_00421460__recomp(EEContext&);  // recompiled
void fn_Y_Misc_CreateMCWNDProcTasks_004214e0(EEContext&);  // generated body
void fn_Y_Misc_CreateMCWNDProcTasks_004214e0__recomp(EEContext&);  // recompiled
void fn_sub_4215B0_004215b0(EEContext&);  // generated body
void fn_sub_4215B0_004215b0__recomp(EEContext&);  // recompiled
void fn_sub_421650_00421650(EEContext&);  // generated body
void fn_sub_421650_00421650__recomp(EEContext&);  // recompiled
void fn_sub_421700_00421700(EEContext&);  // generated body
void fn_sub_421700_00421700__recomp(EEContext&);  // recompiled
void fn_sub_421760_00421760(EEContext&);  // generated body
void fn_sub_421760_00421760__recomp(EEContext&);  // recompiled
void fn_sub_45A3B0_0045a3b0(EEContext&);  // generated body
void fn_sub_45A3B0_0045a3b0__recomp(EEContext&);  // recompiled
void fn_sub_45A3E0_0045a3e0(EEContext&);  // generated body
void fn_sub_45A3E0_0045a3e0__recomp(EEContext&);  // recompiled
void fn_sub_45A400_0045a400(EEContext&);  // generated body
void fn_sub_45A400_0045a400__recomp(EEContext&);  // recompiled
void fn_sub_45A430_0045a430(EEContext&);  // generated body
void fn_sub_45A430_0045a430__recomp(EEContext&);  // recompiled
void fn_sub_45A490_0045a490(EEContext&);  // generated body
void fn_sub_45A490_0045a490__recomp(EEContext&);  // recompiled
void fn_sub_45ACE0_0045ace0(EEContext&);  // generated body
void fn_sub_45ACE0_0045ace0__recomp(EEContext&);  // recompiled
void fn_sub_45AF40_0045af40(EEContext&);  // generated body
void fn_sub_45AF40_0045af40__recomp(EEContext&);  // recompiled
void fn_sub_45AF70_0045af70(EEContext&);  // generated body
void fn_sub_45AF70_0045af70__recomp(EEContext&);  // recompiled
void fn_sub_45AF90_0045af90(EEContext&);  // generated body
void fn_sub_45AF90_0045af90__recomp(EEContext&);  // recompiled
void fn_sub_45AFD0_0045afd0(EEContext&);  // generated body
void fn_sub_45AFD0_0045afd0__recomp(EEContext&);  // recompiled
void fn_sub_45B190_0045b190(EEContext&);  // generated body
void fn_sub_45B190_0045b190__recomp(EEContext&);  // recompiled
void fn_sub_45B420_0045b420(EEContext&);  // generated body
void fn_sub_45B420_0045b420__recomp(EEContext&);  // recompiled
void fn_sub_45B480_0045b480(EEContext&);  // generated body
void fn_sub_45B480_0045b480__recomp(EEContext&);  // recompiled
void fn_sub_45B4B0_0045b4b0(EEContext&);  // generated body
void fn_sub_45B4B0_0045b4b0__recomp(EEContext&);  // recompiled
void fn_sub_45B4E0_0045b4e0(EEContext&);  // generated body
void fn_sub_45B4E0_0045b4e0__recomp(EEContext&);  // recompiled
void fn_sub_45B620_0045b620(EEContext&);  // generated body
void fn_sub_45B620_0045b620__recomp(EEContext&);  // recompiled
void fn_sub_45B830_0045b830(EEContext&);  // generated body
void fn_sub_45B830_0045b830__recomp(EEContext&);  // recompiled
void fn_sub_45B8F0_0045b8f0(EEContext&);  // generated body
void fn_sub_45B8F0_0045b8f0__recomp(EEContext&);  // recompiled
void fn_sub_45BCB0_0045bcb0(EEContext&);  // generated body
void fn_sub_45BCB0_0045bcb0__recomp(EEContext&);  // recompiled
void fn_sub_45BD90_0045bd90(EEContext&);  // generated body
void fn_sub_45BD90_0045bd90__recomp(EEContext&);  // recompiled
void fn_sub_45C530_0045c530(EEContext&);  // generated body
void fn_sub_45C530_0045c530__recomp(EEContext&);  // recompiled
void fn_sub_45C8C0_0045c8c0(EEContext&);  // generated body
void fn_sub_45C8C0_0045c8c0__recomp(EEContext&);  // recompiled
void fn_sub_45CDD0_0045cdd0(EEContext&);  // generated body
void fn_sub_45CDD0_0045cdd0__recomp(EEContext&);  // recompiled
void fn_sub_45CE90_0045ce90(EEContext&);  // generated body
void fn_sub_45CE90_0045ce90__recomp(EEContext&);  // recompiled
void fn_sub_45D990_0045d990(EEContext&);  // generated body
void fn_sub_45D990_0045d990__recomp(EEContext&);  // recompiled
void fn_sub_45DF00_0045df00(EEContext&);  // generated body
void fn_sub_45DF00_0045df00__recomp(EEContext&);  // recompiled
void fn_sub_45E010_0045e010(EEContext&);  // generated body
void fn_sub_45E010_0045e010__recomp(EEContext&);  // recompiled
void fn_sub_45E0C0_0045e0c0(EEContext&);  // generated body
void fn_sub_45E0C0_0045e0c0__recomp(EEContext&);  // recompiled
void fn_sub_45E170_0045e170(EEContext&);  // generated body
void fn_sub_45E170_0045e170__recomp(EEContext&);  // recompiled
void fn_M_Name_UpdateNameKeyProcTask_0045e3e0(EEContext&);  // generated body
void fn_M_Name_UpdateNameKeyProcTask_0045e3e0__recomp(EEContext&);  // recompiled
void fn_sub_45E7B0_0045e7b0(EEContext&);  // generated body
void fn_sub_45E7B0_0045e7b0__recomp(EEContext&);  // recompiled
void fn_sub_45E7E0_0045e7e0(EEContext&);  // generated body
void fn_sub_45E7E0_0045e7e0__recomp(EEContext&);  // recompiled
void fn_M_Name_UpdateNameEntryTask_0045e8c0(EEContext&);  // generated body
void fn_M_Name_UpdateNameEntryTask_0045e8c0__recomp(EEContext&);  // recompiled
void fn_sub_45EA80_0045ea80(EEContext&);  // generated body
void fn_sub_45EA80_0045ea80__recomp(EEContext&);  // recompiled
void fn_M_Name_CreateNameEntryTask_0045eaf0(EEContext&);  // generated body
void fn_M_Name_CreateNameEntryTask_0045eaf0__recomp(EEContext&);  // recompiled
void fn_sub_45EBA0_0045eba0(EEContext&);  // generated body
void fn_sub_45EBA0_0045eba0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_173C60", 0x173C60, &recomp_gen::fn_sub_173C60_00173c60, &recomp_gen::fn_sub_173C60_00173c60__recomp},
    {"sub_174C10", 0x174C10, &recomp_gen::fn_sub_174C10_00174c10, &recomp_gen::fn_sub_174C10_00174c10__recomp},
    {"sub_175820", 0x175820, &recomp_gen::fn_sub_175820_00175820, &recomp_gen::fn_sub_175820_00175820__recomp},
    {"sub_175CE0", 0x175CE0, &recomp_gen::fn_sub_175CE0_00175ce0, &recomp_gen::fn_sub_175CE0_00175ce0__recomp},
    {"sub_177DB0", 0x177DB0, &recomp_gen::fn_sub_177DB0_00177db0, &recomp_gen::fn_sub_177DB0_00177db0__recomp},
    {"sub_179030", 0x179030, &recomp_gen::fn_sub_179030_00179030, &recomp_gen::fn_sub_179030_00179030__recomp},
    {"sub_1791D0", 0x1791D0, &recomp_gen::fn_sub_1791D0_001791d0, &recomp_gen::fn_sub_1791D0_001791d0__recomp},
    {"sub_179360", 0x179360, &recomp_gen::fn_sub_179360_00179360, &recomp_gen::fn_sub_179360_00179360__recomp},
    {"sub_17A430", 0x17A430, &recomp_gen::fn_sub_17A430_0017a430, &recomp_gen::fn_sub_17A430_0017a430__recomp},
    {"sub_17C2F0", 0x17C2F0, &recomp_gen::fn_sub_17C2F0_0017c2f0, &recomp_gen::fn_sub_17C2F0_0017c2f0__recomp},
    {"sub_17C350", 0x17C350, &recomp_gen::fn_sub_17C350_0017c350, &recomp_gen::fn_sub_17C350_0017c350__recomp},
    {"sub_17C4E0", 0x17C4E0, &recomp_gen::fn_sub_17C4E0_0017c4e0, &recomp_gen::fn_sub_17C4E0_0017c4e0__recomp},
    {"sub_17C590", 0x17C590, &recomp_gen::fn_sub_17C590_0017c590, &recomp_gen::fn_sub_17C590_0017c590__recomp},
    {"sub_17C610", 0x17C610, &recomp_gen::fn_sub_17C610_0017c610, &recomp_gen::fn_sub_17C610_0017c610__recomp},
    {"sub_17C670", 0x17C670, &recomp_gen::fn_sub_17C670_0017c670, &recomp_gen::fn_sub_17C670_0017c670__recomp},
    {"sub_17C6C0", 0x17C6C0, &recomp_gen::fn_sub_17C6C0_0017c6c0, &recomp_gen::fn_sub_17C6C0_0017c6c0__recomp},
    {"sub_17C6E0", 0x17C6E0, &recomp_gen::fn_sub_17C6E0_0017c6e0, &recomp_gen::fn_sub_17C6E0_0017c6e0__recomp},
    {"sub_17C700", 0x17C700, &recomp_gen::fn_sub_17C700_0017c700, &recomp_gen::fn_sub_17C700_0017c700__recomp},
    {"sub_17C750", 0x17C750, &recomp_gen::fn_sub_17C750_0017c750, &recomp_gen::fn_sub_17C750_0017c750__recomp},
    {"sub_17C7F0", 0x17C7F0, &recomp_gen::fn_sub_17C7F0_0017c7f0, &recomp_gen::fn_sub_17C7F0_0017c7f0__recomp},
    {"sub_17C860", 0x17C860, &recomp_gen::fn_sub_17C860_0017c860, &recomp_gen::fn_sub_17C860_0017c860__recomp},
    {"sub_17C8C0", 0x17C8C0, &recomp_gen::fn_sub_17C8C0_0017c8c0, &recomp_gen::fn_sub_17C8C0_0017c8c0__recomp},
    {"sub_17C960", 0x17C960, &recomp_gen::fn_sub_17C960_0017c960, &recomp_gen::fn_sub_17C960_0017c960__recomp},
    {"sub_17CA10", 0x17CA10, &recomp_gen::fn_sub_17CA10_0017ca10, &recomp_gen::fn_sub_17CA10_0017ca10__recomp},
    {"sub_17CD30", 0x17CD30, &recomp_gen::fn_sub_17CD30_0017cd30, &recomp_gen::fn_sub_17CD30_0017cd30__recomp},
    {"sub_17CF00", 0x17CF00, &recomp_gen::fn_sub_17CF00_0017cf00, &recomp_gen::fn_sub_17CF00_0017cf00__recomp},
    {"sub_17D030", 0x17D030, &recomp_gen::fn_sub_17D030_0017d030, &recomp_gen::fn_sub_17D030_0017d030__recomp},
    {"sub_17D040", 0x17D040, &recomp_gen::fn_sub_17D040_0017d040, &recomp_gen::fn_sub_17D040_0017d040__recomp},
    {"sub_17D060", 0x17D060, &recomp_gen::fn_sub_17D060_0017d060, &recomp_gen::fn_sub_17D060_0017d060__recomp},
    {"sub_17D1A0", 0x17D1A0, &recomp_gen::fn_sub_17D1A0_0017d1a0, &recomp_gen::fn_sub_17D1A0_0017d1a0__recomp},
    {"sub_17D250", 0x17D250, &recomp_gen::fn_sub_17D250_0017d250, &recomp_gen::fn_sub_17D250_0017d250__recomp},
    {"sub_17D2E0", 0x17D2E0, &recomp_gen::fn_sub_17D2E0_0017d2e0, &recomp_gen::fn_sub_17D2E0_0017d2e0__recomp},
    {"sub_17D3C0", 0x17D3C0, &recomp_gen::fn_sub_17D3C0_0017d3c0, &recomp_gen::fn_sub_17D3C0_0017d3c0__recomp},
    {"sub_17D450", 0x17D450, &recomp_gen::fn_sub_17D450_0017d450, &recomp_gen::fn_sub_17D450_0017d450__recomp},
    {"sub_17D610", 0x17D610, &recomp_gen::fn_sub_17D610_0017d610, &recomp_gen::fn_sub_17D610_0017d610__recomp},
    {"sub_17D6D0", 0x17D6D0, &recomp_gen::fn_sub_17D6D0_0017d6d0, &recomp_gen::fn_sub_17D6D0_0017d6d0__recomp},
    {"sub_17D700", 0x17D700, &recomp_gen::fn_sub_17D700_0017d700, &recomp_gen::fn_sub_17D700_0017d700__recomp},
    {"sub_17D790", 0x17D790, &recomp_gen::fn_sub_17D790_0017d790, &recomp_gen::fn_sub_17D790_0017d790__recomp},
    {"sub_17D7B0", 0x17D7B0, &recomp_gen::fn_sub_17D7B0_0017d7b0, &recomp_gen::fn_sub_17D7B0_0017d7b0__recomp},
    {"sub_18F170", 0x18F170, &recomp_gen::fn_sub_18F170_0018f170, &recomp_gen::fn_sub_18F170_0018f170__recomp},
    {"sub_18F2A0", 0x18F2A0, &recomp_gen::fn_sub_18F2A0_0018f2a0, &recomp_gen::fn_sub_18F2A0_0018f2a0__recomp},
    {"sub_18F2B0", 0x18F2B0, &recomp_gen::fn_sub_18F2B0_0018f2b0, &recomp_gen::fn_sub_18F2B0_0018f2b0__recomp},
    {"sub_190580", 0x190580, &recomp_gen::fn_sub_190580_00190580, &recomp_gen::fn_sub_190580_00190580__recomp},
    {"sub_190700", 0x190700, &recomp_gen::fn_sub_190700_00190700, &recomp_gen::fn_sub_190700_00190700__recomp},
    {"sub_190CB0", 0x190CB0, &recomp_gen::fn_sub_190CB0_00190cb0, &recomp_gen::fn_sub_190CB0_00190cb0__recomp},
    {"sub_191640", 0x191640, &recomp_gen::fn_sub_191640_00191640, &recomp_gen::fn_sub_191640_00191640__recomp},
    {"sub_1919C0", 0x1919C0, &recomp_gen::fn_sub_1919C0_001919c0, &recomp_gen::fn_sub_1919C0_001919c0__recomp},
    {"sub_41BE50", 0x41BE50, &recomp_gen::fn_sub_41BE50_0041be50, &recomp_gen::fn_sub_41BE50_0041be50__recomp},
    {"sub_41BEB0", 0x41BEB0, &recomp_gen::fn_sub_41BEB0_0041beb0, &recomp_gen::fn_sub_41BEB0_0041beb0__recomp},
    {"sub_41BEE0", 0x41BEE0, &recomp_gen::fn_sub_41BEE0_0041bee0, &recomp_gen::fn_sub_41BEE0_0041bee0__recomp},
    {"sub_41BF10", 0x41BF10, &recomp_gen::fn_sub_41BF10_0041bf10, &recomp_gen::fn_sub_41BF10_0041bf10__recomp},
    {"sub_41C140", 0x41C140, &recomp_gen::fn_sub_41C140_0041c140, &recomp_gen::fn_sub_41C140_0041c140__recomp},
    {"sub_41C180", 0x41C180, &recomp_gen::fn_sub_41C180_0041c180, &recomp_gen::fn_sub_41C180_0041c180__recomp},
    {"sub_41CC70", 0x41CC70, &recomp_gen::fn_sub_41CC70_0041cc70, &recomp_gen::fn_sub_41CC70_0041cc70__recomp},
    {"sub_41CEA0", 0x41CEA0, &recomp_gen::fn_sub_41CEA0_0041cea0, &recomp_gen::fn_sub_41CEA0_0041cea0__recomp},
    {"sub_41D120", 0x41D120, &recomp_gen::fn_sub_41D120_0041d120, &recomp_gen::fn_sub_41D120_0041d120__recomp},
    {"sub_41D330", 0x41D330, &recomp_gen::fn_sub_41D330_0041d330, &recomp_gen::fn_sub_41D330_0041d330__recomp},
    {"sub_41DB20", 0x41DB20, &recomp_gen::fn_sub_41DB20_0041db20, &recomp_gen::fn_sub_41DB20_0041db20__recomp},
    {"sub_41E010", 0x41E010, &recomp_gen::fn_sub_41E010_0041e010, &recomp_gen::fn_sub_41E010_0041e010__recomp},
    {"sub_41E830", 0x41E830, &recomp_gen::fn_sub_41E830_0041e830, &recomp_gen::fn_sub_41E830_0041e830__recomp},
    {"sub_41EAF0", 0x41EAF0, &recomp_gen::fn_sub_41EAF0_0041eaf0, &recomp_gen::fn_sub_41EAF0_0041eaf0__recomp},
    {"Y_McProc_UpdateMcProcDrawTask", 0x41EB50, &recomp_gen::fn_Y_McProc_UpdateMcProcDrawTask_0041eb50, &recomp_gen::fn_Y_McProc_UpdateMcProcDrawTask_0041eb50__recomp},
    {"sub_41EC30", 0x41EC30, &recomp_gen::fn_sub_41EC30_0041ec30, &recomp_gen::fn_sub_41EC30_0041ec30__recomp},
    {"nullsub_59", 0x41EC60, &recomp_gen::fn_nullsub_59_0041ec60, &recomp_gen::fn_nullsub_59_0041ec60__recomp},
    {"sub_41EC70", 0x41EC70, &recomp_gen::fn_sub_41EC70_0041ec70, &recomp_gen::fn_sub_41EC70_0041ec70__recomp},
    {"sub_41ECA0", 0x41ECA0, &recomp_gen::fn_sub_41ECA0_0041eca0, &recomp_gen::fn_sub_41ECA0_0041eca0__recomp},
    {"sub_41EF40", 0x41EF40, &recomp_gen::fn_sub_41EF40_0041ef40, &recomp_gen::fn_sub_41EF40_0041ef40__recomp},
    {"sub_41F370", 0x41F370, &recomp_gen::fn_sub_41F370_0041f370, &recomp_gen::fn_sub_41F370_0041f370__recomp},
    {"sub_41F940", 0x41F940, &recomp_gen::fn_sub_41F940_0041f940, &recomp_gen::fn_sub_41F940_0041f940__recomp},
    {"sub_41FD90", 0x41FD90, &recomp_gen::fn_sub_41FD90_0041fd90, &recomp_gen::fn_sub_41FD90_0041fd90__recomp},
    {"sub_41FF50", 0x41FF50, &recomp_gen::fn_sub_41FF50_0041ff50, &recomp_gen::fn_sub_41FF50_0041ff50__recomp},
    {"sub_4202E0", 0x4202E0, &recomp_gen::fn_sub_4202E0_004202e0, &recomp_gen::fn_sub_4202E0_004202e0__recomp},
    {"Y_McProc_CreateMcProcDrawTask", 0x420340, &recomp_gen::fn_Y_McProc_CreateMcProcDrawTask_00420340, &recomp_gen::fn_Y_McProc_CreateMcProcDrawTask_00420340__recomp},
    {"sub_4204F0", 0x4204F0, &recomp_gen::fn_sub_4204F0_004204f0, &recomp_gen::fn_sub_4204F0_004204f0__recomp},
    {"sub_420520", 0x420520, &recomp_gen::fn_sub_420520_00420520, &recomp_gen::fn_sub_420520_00420520__recomp},
    {"sub_420A20", 0x420A20, &recomp_gen::fn_sub_420A20_00420a20, &recomp_gen::fn_sub_420A20_00420a20__recomp},
    {"sub_420DA0", 0x420DA0, &recomp_gen::fn_sub_420DA0_00420da0, &recomp_gen::fn_sub_420DA0_00420da0__recomp},
    {"sub_420F60", 0x420F60, &recomp_gen::fn_sub_420F60_00420f60, &recomp_gen::fn_sub_420F60_00420f60__recomp},
    {"sub_420F90", 0x420F90, &recomp_gen::fn_sub_420F90_00420f90, &recomp_gen::fn_sub_420F90_00420f90__recomp},
    {"sub_420FE0", 0x420FE0, &recomp_gen::fn_sub_420FE0_00420fe0, &recomp_gen::fn_sub_420FE0_00420fe0__recomp},
    {"Y_Misc_UpdateMcWNDProcTask", 0x421330, &recomp_gen::fn_Y_Misc_UpdateMcWNDProcTask_00421330, &recomp_gen::fn_Y_Misc_UpdateMcWNDProcTask_00421330__recomp},
    {"sub_421460", 0x421460, &recomp_gen::fn_sub_421460_00421460, &recomp_gen::fn_sub_421460_00421460__recomp},
    {"Y_Misc_CreateMCWNDProcTasks", 0x4214E0, &recomp_gen::fn_Y_Misc_CreateMCWNDProcTasks_004214e0, &recomp_gen::fn_Y_Misc_CreateMCWNDProcTasks_004214e0__recomp},
    {"sub_4215B0", 0x4215B0, &recomp_gen::fn_sub_4215B0_004215b0, &recomp_gen::fn_sub_4215B0_004215b0__recomp},
    {"sub_421650", 0x421650, &recomp_gen::fn_sub_421650_00421650, &recomp_gen::fn_sub_421650_00421650__recomp},
    {"sub_421700", 0x421700, &recomp_gen::fn_sub_421700_00421700, &recomp_gen::fn_sub_421700_00421700__recomp},
    {"sub_421760", 0x421760, &recomp_gen::fn_sub_421760_00421760, &recomp_gen::fn_sub_421760_00421760__recomp},
    {"sub_45A3B0", 0x45A3B0, &recomp_gen::fn_sub_45A3B0_0045a3b0, &recomp_gen::fn_sub_45A3B0_0045a3b0__recomp},
    {"sub_45A3E0", 0x45A3E0, &recomp_gen::fn_sub_45A3E0_0045a3e0, &recomp_gen::fn_sub_45A3E0_0045a3e0__recomp},
    {"sub_45A400", 0x45A400, &recomp_gen::fn_sub_45A400_0045a400, &recomp_gen::fn_sub_45A400_0045a400__recomp},
    {"sub_45A430", 0x45A430, &recomp_gen::fn_sub_45A430_0045a430, &recomp_gen::fn_sub_45A430_0045a430__recomp},
    {"sub_45A490", 0x45A490, &recomp_gen::fn_sub_45A490_0045a490, &recomp_gen::fn_sub_45A490_0045a490__recomp},
    {"sub_45ACE0", 0x45ACE0, &recomp_gen::fn_sub_45ACE0_0045ace0, &recomp_gen::fn_sub_45ACE0_0045ace0__recomp},
    {"sub_45AF40", 0x45AF40, &recomp_gen::fn_sub_45AF40_0045af40, &recomp_gen::fn_sub_45AF40_0045af40__recomp},
    {"sub_45AF70", 0x45AF70, &recomp_gen::fn_sub_45AF70_0045af70, &recomp_gen::fn_sub_45AF70_0045af70__recomp},
    {"sub_45AF90", 0x45AF90, &recomp_gen::fn_sub_45AF90_0045af90, &recomp_gen::fn_sub_45AF90_0045af90__recomp},
    {"sub_45AFD0", 0x45AFD0, &recomp_gen::fn_sub_45AFD0_0045afd0, &recomp_gen::fn_sub_45AFD0_0045afd0__recomp},
    {"sub_45B190", 0x45B190, &recomp_gen::fn_sub_45B190_0045b190, &recomp_gen::fn_sub_45B190_0045b190__recomp},
    {"sub_45B420", 0x45B420, &recomp_gen::fn_sub_45B420_0045b420, &recomp_gen::fn_sub_45B420_0045b420__recomp},
    {"sub_45B480", 0x45B480, &recomp_gen::fn_sub_45B480_0045b480, &recomp_gen::fn_sub_45B480_0045b480__recomp},
    {"sub_45B4B0", 0x45B4B0, &recomp_gen::fn_sub_45B4B0_0045b4b0, &recomp_gen::fn_sub_45B4B0_0045b4b0__recomp},
    {"sub_45B4E0", 0x45B4E0, &recomp_gen::fn_sub_45B4E0_0045b4e0, &recomp_gen::fn_sub_45B4E0_0045b4e0__recomp},
    {"sub_45B620", 0x45B620, &recomp_gen::fn_sub_45B620_0045b620, &recomp_gen::fn_sub_45B620_0045b620__recomp},
    {"sub_45B830", 0x45B830, &recomp_gen::fn_sub_45B830_0045b830, &recomp_gen::fn_sub_45B830_0045b830__recomp},
    {"sub_45B8F0", 0x45B8F0, &recomp_gen::fn_sub_45B8F0_0045b8f0, &recomp_gen::fn_sub_45B8F0_0045b8f0__recomp},
    {"sub_45BCB0", 0x45BCB0, &recomp_gen::fn_sub_45BCB0_0045bcb0, &recomp_gen::fn_sub_45BCB0_0045bcb0__recomp},
    {"sub_45BD90", 0x45BD90, &recomp_gen::fn_sub_45BD90_0045bd90, &recomp_gen::fn_sub_45BD90_0045bd90__recomp},
    {"sub_45C530", 0x45C530, &recomp_gen::fn_sub_45C530_0045c530, &recomp_gen::fn_sub_45C530_0045c530__recomp},
    {"sub_45C8C0", 0x45C8C0, &recomp_gen::fn_sub_45C8C0_0045c8c0, &recomp_gen::fn_sub_45C8C0_0045c8c0__recomp},
    {"sub_45CDD0", 0x45CDD0, &recomp_gen::fn_sub_45CDD0_0045cdd0, &recomp_gen::fn_sub_45CDD0_0045cdd0__recomp},
    {"sub_45CE90", 0x45CE90, &recomp_gen::fn_sub_45CE90_0045ce90, &recomp_gen::fn_sub_45CE90_0045ce90__recomp},
    {"sub_45D990", 0x45D990, &recomp_gen::fn_sub_45D990_0045d990, &recomp_gen::fn_sub_45D990_0045d990__recomp},
    {"sub_45DF00", 0x45DF00, &recomp_gen::fn_sub_45DF00_0045df00, &recomp_gen::fn_sub_45DF00_0045df00__recomp},
    {"sub_45E010", 0x45E010, &recomp_gen::fn_sub_45E010_0045e010, &recomp_gen::fn_sub_45E010_0045e010__recomp},
    {"sub_45E0C0", 0x45E0C0, &recomp_gen::fn_sub_45E0C0_0045e0c0, &recomp_gen::fn_sub_45E0C0_0045e0c0__recomp},
    {"sub_45E170", 0x45E170, &recomp_gen::fn_sub_45E170_0045e170, &recomp_gen::fn_sub_45E170_0045e170__recomp},
    {"M_Name_UpdateNameKeyProcTask", 0x45E3E0, &recomp_gen::fn_M_Name_UpdateNameKeyProcTask_0045e3e0, &recomp_gen::fn_M_Name_UpdateNameKeyProcTask_0045e3e0__recomp},
    {"sub_45E7B0", 0x45E7B0, &recomp_gen::fn_sub_45E7B0_0045e7b0, &recomp_gen::fn_sub_45E7B0_0045e7b0__recomp},
    {"sub_45E7E0", 0x45E7E0, &recomp_gen::fn_sub_45E7E0_0045e7e0, &recomp_gen::fn_sub_45E7E0_0045e7e0__recomp},
    {"M_Name_UpdateNameEntryTask", 0x45E8C0, &recomp_gen::fn_M_Name_UpdateNameEntryTask_0045e8c0, &recomp_gen::fn_M_Name_UpdateNameEntryTask_0045e8c0__recomp},
    {"sub_45EA80", 0x45EA80, &recomp_gen::fn_sub_45EA80_0045ea80, &recomp_gen::fn_sub_45EA80_0045ea80__recomp},
    {"M_Name_CreateNameEntryTask", 0x45EAF0, &recomp_gen::fn_M_Name_CreateNameEntryTask_0045eaf0, &recomp_gen::fn_M_Name_CreateNameEntryTask_0045eaf0__recomp},
    {"sub_45EBA0", 0x45EBA0, &recomp_gen::fn_sub_45EBA0_0045eba0, &recomp_gen::fn_sub_45EBA0_0045eba0__recomp},
};

// The generic sweep's world: 64 KiB of free RAM above the harness's arena (the real structures: the cases below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;

}  // namespace

TEST_CASE("game(savedata): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            ++pairs;
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// =====================================================================================================================
// The real game state and the real save
// =====================================================================================================================
namespace {

namespace sd = p3fes::game::savedata;

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, name) == 0) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u8 r8(Machine& m, u32 va) { return *m.at(va); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 le32(const std::vector<u8>& b, std::size_t off) { u32 v; std::memcpy(&v, b.data() + off, 4); return v; }
u16 le16(const std::vector<u8>& b, std::size_t off) { u16 v; std::memcpy(&v, b.data() + off, 2); return v; }

constexpr u64 S(s64 v) { return static_cast<u64>(v); }
s64 v0_of(const hgp::Run& r) { return static_cast<s32>(static_cast<u32>(r.end.gpr[GPR_V0].u64[0])); }

// Free in every replay snapshot used here (stand_ins.h: zero from 0x1BC0000 up to the main-thread stack; the stand-in
// heap arena starts at 0x1C00000).
constexpr u32 kScratch = 0x01BC0000u;
constexpr u32 kOut = kScratch + 0x000;       // out words
constexpr u32 kPersona = kScratch + 0x100;   // a scratch persona (52 bytes)
constexpr u32 kTrack = kScratch + 0x200;     // an animation track (152 bytes)
constexpr u32 kTask = kScratch + 0x400;      // a fake KwlnTask (0x68 bytes), +0x3C -> kWork
constexpr u32 kWork = kScratch + 0x480;      // its work
constexpr u32 kWin = kScratch + 0x600;       // a message window
constexpr u32 kList = kScratch + 0x700;      // a 500-word list (4,000 bytes)
constexpr u32 kFile = kScratch + 0x8000;     // the save file (36,182 bytes)
constexpr u32 kTaskWork = 0x3C;              // KwlnTask +0x3C (kwlnTaskGetWorkData)
constexpr const char* kSnapshots[] = {"b_3500", "dorm_replay_4900", "climb_ref_17000", "b_5800", "fusion_vr_5000",
                                      "shop_ref_4100"};

// --- a pair runner for long runs ---------------------------------------------------------------------------------------
// hgp::pair keeps the register file of every check point and cuts a run at 20,000 of them ("runaway"); the save
// functions walk 36 KB byte by byte (the checksums) and copy 13 KB blocks through memcpy -- far more check points. This
// runner compares the same things without storing them: the count of check points and a running FNV-1a hash of the
// whole register file and cycles at each (the fields hgp::diff compares), then the end state, all of RAM, the
// scratchpad and the bus log exactly. Its random register file is hgp::run_one's.
class LongHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    u64 checks = 0, hash = 1469598103934665603ull;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    hgp::Snap at_stop;
    int syscalls = 0;
    std::vector<std::pair<u32, u32>> vu_control;
    static constexpr u64 kMaxChecks = 4000000;

    void mix(const void* p, std::size_t n) {
        const u8* b = static_cast<const u8*>(p);
        for (std::size_t i = 0; i < n; ++i) hash = (hash ^ b[i]) * 1099511628211ull;
    }
    void mix_snap(const hgp::Snap& s) {
        mix(&s.cycles, 8);
        for (const u128& g : s.gpr) mix(&g, 16);
        mix(&s.hi, 16);
        mix(&s.lo, 16);
        mix(&s.sa, 4);
        mix(&s.fcr31, 4);
        mix(&s.acc, 4);
        mix(s.fpr.data(), 4 * 32);
        mix(s.vu0.vf, sizeof s.vu0.vf);
        mix(s.vu0.vi, sizeof s.vu0.vi);
        mix(s.vu0.acc, sizeof s.vu0.acc);
        mix(&s.vu0.q, sizeof s.vu0.q);
        mix(&s.vu0.p, sizeof s.vu0.p);
        mix(&s.vu0.i, sizeof s.vu0.i);
        mix(&s.vu0.r, sizeof s.vu0.r);
        mix(&s.vu0.status, sizeof s.vu0.status);
        mix(&s.vu0.mac, sizeof s.vu0.mac);
        mix(&s.vu0.clip, sizeof s.vu0.clip);
    }
    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        mix_snap(hgp::snap(ctx));
        if (checks >= kMaxChecks) {
            stopped = true;
            stop_pc = 0xFFFFFFFFu;
            what = "runaway";
            at_stop = hgp::snap(ctx);
            throw rt_test::FatalEvent{stop_pc, "runaway", &ctx};
        }
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* w) override {
        stopped = true;
        stop_pc = pc;
        what = w;
        if (const std::size_t k = what.find("; host return address"); k != std::string::npos) what.erase(k);
        at_stop = hgp::snap(ctx);
        throw rt_test::FatalEvent{pc, w, &ctx};
    }
    void vu_control_write(EEContext&, u32 reg, u32 value) override { vu_control.emplace_back(reg, value); }
};

struct LongRun {
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    int syscalls = 0;
    u64 checks = 0, hash = 0;
    hgp::Snap end;
    std::vector<u8> spr;
    std::vector<ScriptedBus::Access> bus;
};

LongRun run_long(Machine& m, Fn fn, const Args& args, u32 seed) {
    LongHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 4; ++i) m.ctx.gpr[GPR_T0 + i].u64[0] = rng() % 4 == 0 ? (static_cast<u64>(rng()) << 32) | rng() : rng() % 64;
    for (unsigned i = 0; i < 32; ++i) {
        const float f = hgp::small_float(rng);
        u32 bits;
        std::memcpy(&bits, &f, 4);
        m.ctx.fpr[i] = rng() % 10 == 0 ? static_cast<u32>(rng()) : bits;
    }
    m.ctx.fcr31 = rng() & 0x00800000u;
    for (unsigned r = 1; r < 32; ++r)
        for (u32& x : m.ctx.vu0.vf[r]) {
            const float f = hgp::small_float(rng);
            std::memcpy(&x, &f, 4);
        }
    for (u32& x : m.ctx.vu0.acc) x = rng() & 0x7F7FFFFFu;
    bool host_fault = false;
    try {
        host_fault = !hgp::call_guarded(fn, m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    if (host_fault && !h.stopped) {
        h.stopped = true;
        h.stop_pc = 0xFFFFFFFEu;
        h.what = "host access violation";
        h.at_stop = hgp::snap(m.ctx);
    }
    LongRun r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.what = h.what;
    r.syscalls = h.syscalls;
    r.checks = h.checks;
    r.hash = h.hash;
    r.end = h.stopped ? h.at_stop : hgp::snap(m.ctx);
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    r.bus = std::move(h.bus_.log);
    CHECK(h.vu_control.empty());
    return r;
}

// Both bodies from the same machine; afterwards the recompiled run's memory is in place. Returns the recompiled run.
LongRun pair_long(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    LongRun h = run_long(m, hand, args, seed);
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    LongRun r = run_long(m, recomp, args, seed);
    INFO(what << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " seed=" << seed
              << (r.stopped ? " (recomp stopped: " + r.what + ")" : std::string()));
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.checks == r.checks);
    CHECK(h.hash == r.hash);
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first));
        CHECK(false);
    }
    CHECK(first_difference(h.spr.data(), r.spr.data(), h.spr.size()) == h.spr.size());
    CHECK(h.bus.size() == r.bus.size());
    return r;
}

// --- the pair runner ---------------------------------------------------------------------------------------------------
// hgp::pair through two trampolines that give each body a fresh, identical stand-in world, whose call logs must match:
// install_standard (the heap behind H_Malloc and the RW slots, printf / sprintf, the H_Cdvd layer) plus a recorder for
// the callees of the cases below that this build does not emit (they log the call and return 0).
void save_world(StandInWorld& w) {
    install_standard(w);
    const std::pair<u32, const char*> rec[] = {
        {0x403740u, "sub_403740 (block 27 sort key)"}, {0x403920u, "sub_403920"}, {0x403130u, "sub_403130"},
        {0x403220u, "sub_403220"}, {0x3D74B0u, "sub_3D74B0"}, {0x3F33D0u, "sub_3F33D0"}, {0x1052B0u, "sub_1052B0 (debug log)"},
        {0x10A4E0u, "sub_10A4E0 (sound)"}, {0x177410u, "sub_177410 (datSetHeroName)"},
    };
    for (const auto& [va, name] : rec) w.si.install_recorder(va, name, 0);
}

struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
};
Tramp g_t;

template <int K>
void tramp(EEContext& c) {
    g_t.world[K] = std::make_unique<StandInWorld>();
    save_world(*g_t.world[K]);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

std::map<std::string, int> g_stops;  // early stops by function and reason (reported once)
int g_pairs = 0;
u64 g_long_checks = 0;  // check points compared by pair_long

struct Real {
    Machine& m;
    std::string name;
    u32 seed = 1;
    hgp::Run call(const char* fn, Args a, const HwCheck& hw = {}) {
        const Case& c = find_case(fn);
        g_t.fn[0] = c.hand;
        g_t.fn[1] = c.recomp;
        const std::string what = name + " " + fn;
        hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, ++seed, what.c_str(), hw);
        if (g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what.c_str());
        ++g_pairs;
        if (r.stopped) ++g_stops[std::string(fn) + ": " + r.what.substr(0, 90)];
        return r;
    }
    s64 v0(const char* fn, Args a, const HwCheck& hw = {}) { return v0_of(call(fn, a, hw)); }
    // the long-run runner (pair_long) for the save functions
    LongRun call_long(const char* fn, Args a) {
        const Case& c = find_case(fn);
        g_t.fn[0] = c.hand;
        g_t.fn[1] = c.recomp;
        const std::string what = name + " " + fn;
        LongRun r = pair_long(m, &tramp<0>, &tramp<1>, a, ++seed, what.c_str());
        if (g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what.c_str());
        ++g_pairs;
        g_long_checks += r.checks;
        if (r.stopped) ++g_stops[std::string(fn) + ": " + r.what.substr(0, 90)];
        return r;
    }
    s64 v0_long(const char* fn, Args a) { return static_cast<s32>(static_cast<u32>(call_long(fn, a).end.gpr[GPR_V0].u64[0])); }
};

std::unique_ptr<Machine> real_machine(const char* snapshot) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    const std::vector<u8> base = read_snapshot(snapshot);
    if (base.size() != EEMemory::kMainRamSize) return nullptr;
    std::memcpy(m->mem.main_ram(), base.data(), base.size());
    write_rw_slots(*m);
    return m;
}

// --- the card reader: one file out of a PS2 memory-card image (Ross Ridge's description of the format: 528-byte raw
// pages, 512 data bytes each, 2-page clusters, the indirect FAT, 512-byte directory entries). An independent reference:
// it shares nothing with the runtime's p3fes_memcard library.
struct Card {
    std::vector<u8> raw;
    u32 alloc_offset = 0, rootdir = 0;
    u32 ifc[32] = {};
    std::vector<u8> cluster(u32 c) const {
        std::vector<u8> out(1024);
        for (u32 p = 0; p < 2; ++p) std::memcpy(out.data() + 512 * p, raw.data() + 528 * static_cast<std::size_t>(2 * c + p), 512);
        return out;
    }
    u32 fat(u32 c) const {
        const u32 fi = c / 256;
        const std::vector<u8> ind = cluster(ifc[fi / 256]);
        u32 fc;
        std::memcpy(&fc, ind.data() + 4 * (fi % 256), 4);
        const std::vector<u8> f = cluster(fc);
        u32 v;
        std::memcpy(&v, f.data() + 4 * (c % 256), 4);
        return v;
    }
    std::vector<u8> read(u32 first, u32 length) const {
        std::vector<u8> out;
        u32 c = first;
        for (int guard = 0; guard < 8192 && out.size() < length; ++guard) {
            const std::vector<u8> d = cluster(alloc_offset + c);
            out.insert(out.end(), d.begin(), d.end());
            const u32 next = fat(c);
            if (next == 0xFFFFFFFFu) break;
            c = next & 0x7FFFFFFFu;
        }
        out.resize(std::min<std::size_t>(out.size(), length));
        return out;
    }
    struct Entry {
        u16 mode;
        u32 length, cluster;
        std::string name;
    };
    std::vector<Entry> dir(u32 first, u32 count) const {
        const std::vector<u8> d = read(first, count * 512);
        std::vector<Entry> out;
        for (u32 i = 0; i < count && 512 * (i + 1) <= d.size(); ++i) {
            const u8* e = d.data() + 512 * i;
            Entry x;
            std::memcpy(&x.mode, e, 2);
            std::memcpy(&x.length, e + 4, 4);
            std::memcpy(&x.cluster, e + 0x10, 4);
            x.name.assign(reinterpret_cast<const char*>(e + 0x40), strnlen(reinterpret_cast<const char*>(e + 0x40), 32));
            out.push_back(x);
        }
        return out;
    }
};

// The first "BASLUS-21621Save*" file of the card (empty when the card or the file is missing).
std::vector<u8> read_card_save(const std::string& path, std::string* name = nullptr) {
    Card card;
    std::ifstream f(path, std::ios::binary);
    if (!f) return {};
    card.raw.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    if (card.raw.size() != 16384u * 528u) return {};
    const u8* sb = card.raw.data();
    if (std::memcmp(sb, "Sony PS2 Memory Card Format", 27) != 0) return {};
    std::memcpy(&card.alloc_offset, sb + 0x34, 4);
    std::memcpy(&card.rootdir, sb + 0x3C, 4);
    std::memcpy(card.ifc, sb + 0x50, sizeof card.ifc);
    const std::vector<Card::Entry> head = card.dir(card.rootdir, 1);
    if (head.empty()) return {};
    for (const Card::Entry& d : card.dir(card.rootdir, head[0].length)) {
        if (!(d.mode & 0x20) || !(d.mode & 0x8000) || d.name.rfind("BASLUS-21621Save", 0) != 0) continue;
        for (const Card::Entry& e : card.dir(d.cluster, d.length))
            if ((e.mode & 0x10) && (e.mode & 0x8000) && e.name == d.name) {
                if (name) *name = e.name;
                return card.read(e.cluster, e.length);
            }
    }
    return {};
}

std::string card_path() { return extracted_root() + "/_ours/cards/tartarus.ps2"; }

// --- the save format on the host (savedata.h) ----------------------------------------------------------------------
struct Block {
    s32 id;
    u32 size;
    u32 offset;  // of the data, in the file
};

// The block list of a save buffer, up to and including the terminator's position (the id -1 is not a Block).
std::vector<Block> parse_blocks(const std::vector<u8>& f, std::size_t* end = nullptr) {
    std::vector<Block> out;
    std::size_t p = sd::kSaveBlocksOffset;
    while (p + 4 <= f.size()) {
        const s32 id = static_cast<s32>(le32(f, p));
        if (id == sd::kBlockEnd || p + 8 > f.size()) break;
        const u32 n = le32(f, p + 4);
        out.push_back({id, n, static_cast<u32>(p + 8)});
        p += 8 + n;
    }
    if (end) *end = p;
    return out;
}

// The order and sizes the packer writes.
std::vector<std::pair<s32, u32>> expected_blocks() {
    std::vector<std::pair<s32, u32>> v;
    for (const sd::GlobalBlock& g : sd::kGlobalBlocks) v.push_back({g.id, g.size});
    for (s32 k = 0; k < sd::kPartyRecordsSaved; ++k)
        for (s32 p = 0; p < 12; ++p) v.push_back({sd::record_block_id(k, p), sd::kRecordPieces[p].size});
    v.push_back({sd::kBlockEquipTable, 400});
    v.push_back({sd::kBlockItemTable, 600});
    v.push_back({sd::kBlockChecksum, 1});
    return v;
}

// Where block `id`'s data lives in a machine (0 for the checksum / unknown ids).
u32 block_address(Machine& m, s32 id) {
    for (const sd::GlobalBlock& g : sd::kGlobalBlocks)
        if (g.id == id) return g.via_pointer ? r32(m, g.addr) : g.addr;
    if (id == sd::kBlockEquipTable) return sd::kEquipTable;
    if (id == sd::kBlockItemTable) return sd::kItemTable;
    const s32 k = id / 0x100 - 1, p = id & 0xFF;
    if (id >= 0x100 && id < 0x1000 && k < sd::kPartyRecordsSaved && p < 12)
        return sd::kPartyRecords + sd::kPartyRecordSize * static_cast<u32>(k) + sd::kRecordPieces[p].offset;
    return 0;
}

// Everything savedata.h says about a save buffer, checked on the host. `m` (optional) is the machine whose state was
// packed: then every block's data must equal that machine's memory (the blocks 21..23 are compared too: the packer
// stores their refreshed values in the machine before packing them).
void check_format(const std::vector<u8>& f, const char* what, Machine* m = nullptr) {
    INFO(what);
    REQUIRE(f.size() == sd::kSaveFileSize);
    CHECK(le32(f, 0) == sd::kSaveVersion);
    // the header sum: the byte sum of header bytes 0..49, mod 256, in the u16 at +50
    u32 hs = 0;
    for (u32 i = 0; i < 50; ++i) hs += f[sd::kSaveHeaderOffset + i];
    CHECK(le16(f, sd::kSaveHeaderOffset + sd::kHdrSum) == (hs & 0xFFu));
    std::size_t end = 0;
    const std::vector<Block> blocks = parse_blocks(f, &end);
    const std::vector<std::pair<s32, u32>> want = expected_blocks();
    REQUIRE(blocks.size() == sd::kSaveBlockCount);
    REQUIRE(want.size() == sd::kSaveBlockCount);
    for (std::size_t i = 0; i < blocks.size(); ++i) {
        INFO("block " << i);
        CHECK(blocks[i].id == want[i].first);
        CHECK(blocks[i].size == want[i].second);
    }
    // the terminator right after the checksum block, at the very end
    CHECK(end + 4 == f.size());
    CHECK(le32(f, end) == 0xFFFFFFFFu);
    // the checksum: the byte sum of [56, the checksum block's id), mod 256
    const Block& ck = blocks.back();
    u32 sum = 0;
    for (std::size_t i = sd::kSaveBlocksOffset; i < ck.offset - 8; ++i) sum += f[i];
    CHECK(f[ck.offset] == (sum & 0xFFu));
    // the header repeats blocks: day = block 8, slot = block 9, names = block 1, block 35's low byte, the play time =
    // counter 47 of block 25, the clear mark from flag word 152 of block 17
    auto data = [&](s32 id) -> const u8* {
        for (const Block& b : blocks)
            if (b.id == id) return f.data() + b.offset;
        return nullptr;
    };
    const u8* h = f.data() + sd::kSaveHeaderOffset;
    CHECK(std::memcmp(h + sd::kHdrDay, data(8), 2) == 0);
    CHECK(h[sd::kHdrSlot] == *data(9));
    CHECK(h[sd::kHdrSlot + 1] == 0);
    CHECK(std::memcmp(h + sd::kHdrFirstName, data(1), 18) == 0);
    CHECK(std::memcmp(h + sd::kHdrSurname, data(1) + 18, 18) == 0);
    CHECK(h[sd::kHdrAnswer] == *data(35));
    CHECK(std::memcmp(h + sd::kHdrPlayTime, data(25) + 4 * 47, 4) == 0);
    u32 clear_word;
    std::memcpy(&clear_word, data(17) + 4 * 152, 4);
    CHECK(h[sd::kHdrClearMark] == ((clear_word & sd::kClearMarkB) ? 2 : (clear_word & sd::kClearMarkA) ? 1 : 0));
    if (m) {
        // the level: how many entries of the exp table the hero's exp reaches (block 2 +0x44 = gGlobalWork +0x68)
        s32 exp;
        std::memcpy(&exp, data(2) + 0x44, 4);
        u32 level = 0;
        while (level < 99 && exp >= static_cast<s32>(r32(*m, sd::kHeroExpTable + 4 * level))) ++level;
        CHECK(h[sd::kHdrLevel] == level);
        // the field: the field work's first two words, as bytes
        const u32 fw = r32(*m, 0x7CD540u);
        CHECK(h[sd::kHdrFieldMajor] == static_cast<u8>(r32(*m, fw)));
        CHECK(h[sd::kHdrFieldMinor] == static_cast<u8>(r32(*m, fw + 4)));
        for (const Block& b : blocks) {
            const u32 at = block_address(*m, b.id);
            if (at == 0) continue;
            INFO("block 0x" << std::hex << b.id);
            CHECK(std::memcmp(f.data() + b.offset, m->at(at), b.size) == 0);
        }
    }
}

std::vector<u8> guest_bytes(Machine& m, u32 va, u32 n) { return std::vector<u8>(m.at(va), m.at(va) + n); }

}  // namespace

TEST_CASE("game(savedata): the save the game wrote (tartarus.ps2) has the format of savedata.h, byte for byte") {
    std::string name;
    const std::vector<u8> f = read_card_save(card_path(), &name);
    if (f.empty()) {
        MESSAGE("SKIP: no save on " << card_path());
        return;
    }
    CHECK(name == "BASLUS-21621Save0");
    auto m = real_machine("b_3500");  // the exp table and the field work, read for the level / field checks
    check_format(f, "tartarus.ps2", nullptr);
    if (m) {
        // header +8: the level from block 2's exp and the ELF's exp table
        const std::vector<Block> blocks = parse_blocks(f);
        s32 exp;
        std::memcpy(&exp, f.data() + blocks[1].offset + 0x44, 4);
        u32 level = 0;
        while (level < 99 && exp >= static_cast<s32>(r32(*m, sd::kHeroExpTable + 4 * level))) ++level;
        CHECK(f[sd::kSaveHeaderOffset + sd::kHdrLevel] == level);
    }
    // the slot list's summary of this save: day 15 (April 20), the Dark Hour, 0 h 50 min of play
    const u8* h = f.data() + sd::kSaveHeaderOffset;
    CHECK(le16(f, sd::kSaveHeaderOffset) == 15);
    CHECK(h[sd::kHdrSlot] == 8);
    const u32 play = le32(f, sd::kSaveHeaderOffset + sd::kHdrPlayTime);
    CHECK(play / sd::kPlayTimePerHour == 0);
    CHECK(play / sd::kPlayTimePerMinute % 60 == 50);
    MESSAGE("tartarus.ps2: " << name << ", " << f.size() << " bytes, play time " << play << " (1/30 s)");
}

TEST_CASE("game(savedata): verify, unpack and pack again -- the real save through the bodies") {
    const std::vector<u8> f = read_card_save(card_path());
    auto mp = real_machine("b_3500");
    if (f.empty() || !mp) {
        MESSAGE("SKIP: no save card or no b_3500 snapshot");
        return;
    }
    Machine& m = *mp;
    Real R{m, "b_3500"};
    const u32 n = static_cast<u32>(f.size());
    auto load_file = [&](const std::vector<u8>& bytes) { std::memcpy(m.at(kFile), bytes.data(), bytes.size()); };
    const std::vector<Block> blocks = parse_blocks(f);

    // 1. the verifier (data + 4, size - 4, as sub_41DB20 calls it): the real save, then broken copies
    load_file(f);
    CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, n - 4, 0}) == 1);
    CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, 4095, 0}) == 0);  // under 4,096 bytes
    CHECK(R.v0_long("sub_1791D0", {2, kFile + 4, n - 4, 0}) == 1);                // version 2: no checksum to check
    CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, 8000, 0}) == 0);  // runs out before the checksum
    {
        std::vector<u8> bad = f;
        bad[blocks[15].offset + 100] ^= 0x40;  // one bit of the compendium
        load_file(bad);
        CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, n - 4, 0}) == 0);
        bad = f;
        bad[blocks.back().offset] ^= 1;  // the checksum byte itself
        load_file(bad);
        CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, n - 4, 0}) == 0);
        bad = f;
        std::memset(bad.data() + blocks[3].offset - 4, 0, 4);  // block 4's size 0
        load_file(bad);
        CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, n - 4, 0}) == 0);
        bad = f;
        std::memset(bad.data() + blocks[40].offset - 8, 0xFF, 4);  // a terminator before the checksum
        load_file(bad);
        CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, n - 4, 0}) == 0);
    }

    // 2. the unpacker: every block lands where savedata.h says, and the display names are rebuilt
    load_file(f);
    w32(m, sd::kCarryOverMode, 0);
    R.call_long("sub_179030", {sd::kSaveVersion, kFile + 4, n - 4, 0});
    for (const Block& b : blocks) {
        const u32 at = block_address(m, b.id);
        if (at == 0) continue;
        INFO("unpacked block 0x" << std::hex << b.id);
        CHECK(std::memcmp(m.at(at), f.data() + b.offset, b.size) == 0);
    }
    CHECK(std::memcmp(m.at(sd::kNameCopyFirst), f.data() + blocks[0].offset, 18) == 0);
    CHECK(std::memcmp(m.at(sd::kNameCopySurname), f.data() + blocks[0].offset + 18, 18) == 0);
    {
        const std::string first(reinterpret_cast<const char*>(f.data() + blocks[0].offset));
        const std::string surname(reinterpret_cast<const char*>(f.data() + blocks[0].offset + 18));
        CHECK(m.str(sd::kNameFull) == surname + " " + first);
    }

    // 3. pack the unpacked state: the same file, except what the packer re-reads from the live game (the field and
    //    floor words, blocks 21..23, the header's field bytes and sum, header byte 11 -- stale stack -- and so the
    //    checksum)
    w32(m, kOut, 0);
    const LongRun pack = R.call_long("sub_177DB0", {sd::kSaveVersion, kOut, 0, 0});
    REQUIRE_FALSE(pack.stopped);
    const u32 buf = static_cast<u32>(pack.end.gpr[GPR_V0].u64[0]);
    CHECK(buf >= kStandInHeap);
    CHECK(r32(m, kOut) == sd::kSaveFileSize);
    const std::vector<u8> g = guest_bytes(m, buf, sd::kSaveFileSize);
    check_format(g, "pack(unpack(tartarus.ps2))", &m);
    std::set<std::size_t> live;
    for (s32 i : {sd::kHdrFieldMajor, sd::kHdrFieldMinor, sd::kHdrSum, sd::kHdrSum + 1, 11}) live.insert(sd::kSaveHeaderOffset + static_cast<u32>(i));
    for (const Block& b : blocks)
        if (b.id == 21 || b.id == 22 || b.id == 23 || b.id == sd::kBlockChecksum)
            for (u32 i = 0; i < b.size; ++i) live.insert(b.offset + i);
    std::size_t same = 0, diffs = 0;
    for (std::size_t i = 0; i < f.size(); ++i) {
        if (live.count(i)) continue;
        if (f[i] == g[i]) {
            ++same;
        } else if (++diffs <= 8) {
            INFO("pack(unpack(file)) differs at file offset " << i);
            CHECK(false);
        }
    }
    CHECK(diffs == 0);
    MESSAGE("pack(unpack(tartarus.ps2)): " << same << " of " << f.size() << " bytes equal, " << live.size()
                                           << " live (field / floor / sums), " << diffs << " different");

    // 4. the packed buffer verifies
    std::memcpy(m.at(kFile), g.data(), g.size());
    CHECK(R.v0_long("sub_1791D0", {sd::kSaveVersion, kFile + 4, n - 4, 0}) == 1);

    // 5. a carry-over load: only blocks 2, 16, 17, 24 reach the four buffers (here: scratch areas)
    load_file(f);
    const u32 dst[4] = {kScratch + 0x20000, kScratch + 0x20100, kScratch + 0x20500, kScratch + 0x23A00};  // unit, flags, block 24, compendium
    std::memset(m.at(kScratch + 0x20000), 0, 0x8000);
    w32(m, sd::kCarryOverMode, 1);
    w32(m, sd::kCarryUnit, dst[0]);
    w32(m, sd::kCarryFlags, dst[1]);
    w32(m, sd::kCarryBlock24, dst[2]);
    w32(m, sd::kCarryCompendium, dst[3]);
    const std::vector<u8> before = guest_bytes(m, sd::kGlobalWork, 0x48A0);
    R.call_long("sub_179030", {sd::kSaveVersion, kFile + 4, n - 4, 0});
    CHECK(std::memcmp(m.at(dst[0]), f.data() + blocks[1].offset, 80) == 0);
    CHECK(std::memcmp(m.at(dst[1]), f.data() + blocks[16].offset, 704) == 0);
    CHECK(std::memcmp(m.at(dst[2]), f.data() + blocks[23].offset, 44) == 0);
    CHECK(std::memcmp(m.at(dst[3]), f.data() + blocks[15].offset, 13312) == 0);
    CHECK(guest_bytes(m, sd::kGlobalWork, 0x48A0) == before);  // gGlobalWork untouched
    w32(m, sd::kCarryOverMode, 0);
}

TEST_CASE("game(savedata): a save transfer -- each snapshot's state packed, unpacked on another snapshot's machine") {
    std::vector<std::string> have;
    for (const char* s : kSnapshots)
        if (read_snapshot(s).size() == EEMemory::kMainRamSize) have.push_back(s);
    if (have.size() < 2) {
        MESSAGE("SKIP: fewer than two replay snapshots");
        return;
    }
    int transfers = 0;
    for (std::size_t i = 0; i < have.size(); ++i) {
        auto a = real_machine(have[i].c_str());
        Real RA{*a, have[i]};
        w32(*a, kOut, 0);
        const LongRun pack = RA.call_long("sub_177DB0", {sd::kSaveVersion, kOut, 0, 0});
        if (pack.stopped) {  // both bodies stopped alike (the pair compared them): no field work in this snapshot
            MESSAGE(have[i] << ": the pack stopped (" << pack.what << ")");
            continue;
        }
        const u32 buf = static_cast<u32>(pack.end.gpr[GPR_V0].u64[0]);
        const std::vector<u8> f = guest_bytes(*a, buf, sd::kSaveFileSize);
        check_format(f, have[i].c_str(), a.get());  // every block = A's memory
        CHECK(RA.v0_long("sub_1791D0", {sd::kSaveVersion, buf + 4, sd::kSaveFileSize - 4, 0}) == 1);
        // unpack it on the next snapshot's machine B
        const std::string& bn = have[(i + 1) % have.size()];
        auto b = real_machine(bn.c_str());
        Real RB{*b, bn + " <- " + have[i]};
        std::memcpy(b->at(kFile), f.data(), f.size());
        w32(*b, sd::kCarryOverMode, 0);
        RB.call_long("sub_179030", {sd::kSaveVersion, kFile + 4, sd::kSaveFileSize - 4, 0});
        for (const Block& blk : parse_blocks(f)) {
            const u32 at_a = block_address(*a, blk.id), at_b = block_address(*b, blk.id);
            if (at_a == 0) continue;
            INFO(bn << " <- " << have[i] << ": block 0x" << std::hex << blk.id);
            CHECK(std::memcmp(b->at(at_b), a->at(at_a), blk.size) == 0);
        }
        ++transfers;
    }
    MESSAGE("save transfers: " << transfers << " (" << have.size() << " snapshots)");
}

TEST_CASE("game(savedata): documented rules -- the compendium and the tables of blocks 27..31 on the snapshots") {
    auto mp = real_machine("climb_ref_17000");
    if (!mp) {
        MESSAGE("SKIP: no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    Real R{m, "climb_ref_17000"};
    // datCompendiumGet: the entry when its flags bit 0 is set, else 0 -- every id
    int registered = 0;
    for (u32 id = 0; id < 256; ++id) {
        const u32 e = sd::kCompendium + sd::kPersonaSize * id;
        const bool reg = (r16(m, e) & 1) != 0;
        registered += reg ? 1 : 0;
        CHECK(R.v0("sub_17C8C0", {id, 0, 0, 0}) == (reg ? static_cast<s64>(e) : 0));
    }
    // datCompendiumPercent: 100 * registered / registrable (table flags without 0x08 / 0x20)
    {
        const u32 table = r32(m, sd::kPersonaTableSlot);
        int registrable = 0;
        for (u32 id = 0; id < 256; ++id) {
            const u16 fl = r16(m, table + 14 * id);
            registrable += ((fl & 8) == 0 && (fl & 0x20) == 0) ? 1 : 0;
        }
        REQUIRE(registrable > 0);
        CHECK(R.v0("sub_17CF00", {0, 0, 0, 0}) == 100 * registered / registrable);
        MESSAGE("compendium: " << registered << " registered of " << registrable << " registrable");
    }
    // datCompendiumCompare / datCompendiumRegister on the hero's stock personas
    int compared = 0;
    for (u32 s = 0; s < 12; ++s) {
        const u32 p = 0x836BACu + sd::kPersonaSize * s;
        if ((r16(m, p) & 1) == 0) continue;
        const u16 id = r16(m, p + 2);
        if (id == 0 || id >= 256) continue;
        std::memcpy(m.at(kPersona), m.at(p), sd::kPersonaSize);
        const u32 e = sd::kCompendium + sd::kPersonaSize * id;
        const bool reg = (r16(m, e) & 1) != 0;
        s64 want = -1;
        if (reg) {
            const u8* x = m.at(e);
            const u8* y = m.at(kPersona);
            want = (std::memcmp(x, y, 2) == 0 && x[4] == y[4] && std::memcmp(x + 8, y + 8, 4) == 0 &&
                    std::memcmp(x + 0x1C, y + 0x1C, 15) == 0 && std::memcmp(x + 0xC, y + 0xC, 16) == 0) ? 0 : 1;
        }
        CHECK(R.v0("sub_17CA10", {kPersona, 0, 0, 0}) == want);
        // one level more: different (when registered)
        w8(m, kPersona + 4, static_cast<u8>(r8(m, kPersona + 4) + 1));
        CHECK(R.v0("sub_17CA10", {kPersona, 0, 0, 0}) == (reg ? 1 : -1));
        ++compared;
    }
    CHECK(compared > 0);
    // register an unregistered, registrable id: 0 and the entry is the persona
    {
        const u32 table = r32(m, sd::kPersonaTableSlot);
        for (u32 id = 1; id < 192; ++id) {
            const u16 fl = r16(m, table + 14 * id);
            const u32 e = sd::kCompendium + sd::kPersonaSize * id;
            if ((r16(m, e) & 1) != 0 || (fl & 0x28) != 0) continue;
            std::memset(m.at(kPersona), 0, sd::kPersonaSize);
            w16(m, kPersona, 1);
            w16(m, kPersona + 2, static_cast<u16>(id));
            w8(m, kPersona + 4, 7);
            CHECK(R.v0("sub_17CD30", {kPersona, 0, 0, 0}) == 0);
            CHECK(std::memcmp(m.at(e), m.at(kPersona), sd::kPersonaSize) == 0);
            CHECK(R.v0("sub_17CD30", {kPersona, 0, 0, 0}) == static_cast<s64>(e));  // now registered: its entry
            CHECK(R.v0("sub_17CA10", {kPersona, 0, 0, 0}) == 0);
            break;
        }
    }

    // block 27: 4 x {s16 id, s16 counter}, three slots used
    for (u32 i = 0; i < 4; ++i) w32(m, sd::kBlock27 + 4 * i, 0x0000FFFFu);
    w32(m, sd::kBlock27, (3u << 16) | 5u);
    CHECK(R.v0("sub_17C700", {0, 0, 0, 0}) == 1);
    CHECK(R.v0("sub_17C610", {5, 0, 0, 0}) == static_cast<s64>(sd::kBlock27));
    CHECK(R.v0("sub_17C610", {6, 0, 0, 0}) == 0);
    CHECK(R.v0("sub_17C670", {0, 0, 0, 0}) == static_cast<s64>(sd::kBlock27));
    CHECK(R.v0("sub_17C670", {1, 0, 0, 0}) == 0);
    CHECK(R.v0("sub_17C4E0", {9, 0, 0, 0}) == 1);
    CHECK(R.v0("sub_17C4E0", {11, 0, 0, 0}) == 1);
    CHECK(R.v0("sub_17C4E0", {12, 0, 0, 0}) == 0);  // the three slots are full
    {
        std::multiset<s16> ids;
        for (u32 i = 0; i < 3; ++i) ids.insert(static_cast<s16>(r16(m, sd::kBlock27 + 4 * i)));
        CHECK(ids == std::multiset<s16>{5, 9, 11});
        CHECK(static_cast<s16>(r16(m, sd::kBlock27 + 12)) == -1);
    }
    CHECK(R.v0("sub_17C700", {0, 0, 0, 0}) == 3);
    R.call("sub_17C590", {9, 0, 0, 0});
    CHECK(R.v0("sub_17C610", {9, 0, 0, 0}) == 0);
    CHECK(R.v0("sub_17C700", {0, 0, 0, 0}) == 2);
    // block 28: u8[8] set / get
    for (u32 i = 0; i < 8; ++i) R.call("sub_17C7F0", {i, 0x30 + i, 0, 0});
    for (u32 i = 0; i < 8; ++i) {
        CHECK(r8(m, sd::kBlock28 + i) == 0x30 + i);
        CHECK(R.v0("sub_17C860", {i, 0, 0, 0}) == 0x30 + i);
    }
    // block 29: + 1
    const u32 c29 = r32(m, sd::kBlock29);
    R.call("sub_17D040", {0, 0, 0, 0});
    CHECK(R.v0("sub_17D030", {0, 0, 0, 0}) == static_cast<s32>(c29 + 1));
    // block 30: 32 x {a, b, key, value}
    std::memset(m.at(sd::kBlock30), 0, 256);
    const u32 row = static_cast<u32>(R.v0("sub_17D060", {(7u << 16) | 3u, 4, 50, 0}));
    CHECK(row == sd::kBlock30);
    CHECK(r16(m, row) == 3);
    CHECK(r16(m, row + 2) == 7);
    CHECK(r16(m, row + 4) == 4);
    CHECK(r16(m, row + 6) == 50);
    CHECK(R.v0("sub_17D250", {3, 4, 0, 0}) == 50);
    CHECK(R.v0("sub_17D250", {3, 5, 0, 0}) == -1);
    CHECK(R.v0("sub_17D1A0", {3, 4, 20, 0}) == 30);
    CHECK(R.v0("sub_17D1A0", {3, 4, 40, 0}) == 0);  // floored at 0
    CHECK(R.v0("sub_17D1A0", {9, 4, 1, 0}) == -1);
    CHECK(R.v0("sub_17D060", {(7u << 16) | 3u, 4, 99, 0}) == static_cast<s64>(row));  // same b: unchanged
    CHECK(r16(m, row + 6) == 0);
    R.call("sub_17D060", {(8u << 16) | 3u, 4, 99, 0});  // a different b: replaced
    CHECK(r16(m, row + 2) == 8);
    CHECK(r16(m, row + 6) == 99);
    CHECK(R.v0("sub_17D060", {(1u << 16) | 6u, 2, 5, 0}) == static_cast<s64>(sd::kBlock30 + 8));  // the next free row
    // block 31: nine rows of the four floats at 0x5E38C0; get current / previous
    R.call("sub_17D3C0", {0, 0, 0, 0});
    for (u32 i = 0; i < 9; ++i) CHECK(std::memcmp(m.at(sd::kBlock31 + 16 * i), m.at(sd::kBlock31Init), 16) == 0);
    for (u32 i = 0; i < 9; ++i) w32(m, sd::kBlock31 + 16 * i + 8, 0xA0 + i);
    R.call("sub_17D700", {2, 0, kOut, 0});
    CHECK(std::memcmp(m.at(kOut), m.at(sd::kBlock31 + 32), 8) == 0);
    R.call("sub_17D6D0", {4, kOut + 8, 0, 0});
    CHECK(r32(m, kOut + 8) == 0xA4);
}

TEST_CASE("game(savedata): documented rules -- the H_Memcard requests, the message window, the name entry, the tracks") {
    auto mp = real_machine("dorm_replay_4900");
    if (!mp) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    Real R{m, "dorm_replay_4900"};
    // the request words
    w32(m, sd::kCarryOverMode, 5);
    R.call("sub_18F170", {3, 0x1C10000, 36182, 0});
    CHECK(r32(m, sd::kMcSlot) == 3);
    CHECK(r32(m, sd::kMcData) == 0x1C10000u);
    CHECK(r32(m, sd::kMcSize) == 36182);
    CHECK(r32(m, sd::kMcSeqMode) == 0);
    CHECK(r32(m, sd::kMcSubStep) == 0);
    CHECK(r32(m, sd::kCarryOverMode) == 0);
    R.call("sub_18F2A0", {0, 0, 0, 0});
    CHECK(r32(m, sd::kMcSeqMode) == 9);
    R.call("sub_18F2B0", {0, 0, 0, 0});
    CHECK(r32(m, sd::kMcSeqMode) == 4);
    R.call("sub_190580", {0, 0, 0, 0});
    CHECK(r32(m, sd::kMcCancel) == 1);
    R.call("sub_190700", {1, 0x1C20000, kOut, 0});
    CHECK(r32(m, sd::kMcSlot) == 1);
    CHECK(r32(m, sd::kMcData) == 0x1C20000u);
    CHECK(r32(m, sd::kMcReadBlock) == kOut);
    R.call("sub_190CB0", {kWork + 20, 0, 0, 0});
    CHECK(r32(m, sd::kMcList) == kWork + 20);
    CHECK(r32(m, sd::kMcSlot) == 0);
    R.call("sub_191640", {2, 0, 0, 0});
    CHECK(r32(m, sd::kMcSlot) == 2);
    // the 500-word list
    std::memset(m.at(kList), 0xAB, 4000);
    R.call("sub_1919C0", {kList, 4000, 0, 0});
    CHECK(r32(m, 0x7CE04Cu) == kList);
    CHECK(r32(m, 0x7CE048u) == kList + 4000);
    CHECK(r32(m, 0x7CE044u) == 500);
    CHECK(r32(m, 0x7CE040u) == 0);
    CHECK(std::all_of(m.at(kList), m.at(kList + 4000), [](u8 b) { return b == 0; }));

    // the message window's result: 1 with no window, 0 while open, 1 + the answer once closing
    std::memset(m.at(kTask), 0, 0x68);
    std::memset(m.at(kWork), 0, 0x400);
    std::memset(m.at(kWin), 0, 0x40);
    w32(m, kTask + kTaskWork, kWork);
    CHECK(R.v0("sub_421700", {kTask, 0, 0, 0}) == 1);
    w32(m, kWork + 24, kWin);
    CHECK(R.v0("sub_421700", {kTask, 0, 0, 0}) == 0);
    w32(m, kWin + 4, 4);
    CHECK(R.v0("sub_421700", {kTask, 0, 0, 0}) == 1);  // yes / acknowledged
    w32(m, kWin + 16, 1);
    CHECK(R.v0("sub_421700", {kTask, 0, 0, 0}) == 2);  // no
    // the card process: done flag, the cursor row's used word
    w32(m, kWork + sd::kMcWorkFlags, 8);
    CHECK(R.v0("sub_4204F0", {kTask, 0, 0, 0}) == 1);
    w32(m, kWork + sd::kMcWorkFlags, 7);
    CHECK(R.v0("sub_4204F0", {kTask, 0, 0, 0}) == 0);
    w32(m, kWork + sd::kMcWorkList, kWin);
    w32(m, kWin + 12, kWin + 0x20);
    w32(m, kWin + 0x20, 3);  // the cursor's row number (1-based)
    w32(m, kWork + sd::kMcWorkSlotUsed + 8, 0x77);
    CHECK(R.v0("sub_41EC70", {kWork, 0, 0, 0}) == 0x77);

    // the name entry's buffers: eight blank characters each, the cursor words cleared
    R.call("sub_45E7E0", {0, 0, 0, 0});
    std::string blank8;
    for (int i = 0; i < sd::kNameChars; ++i) blank8 += m.str(sd::kNameBlank, 2);
    CHECK(m.str(sd::kNameBlank, 4).size() == 2);  // the blank is one two-byte character
    CHECK(m.str(sd::kNameFirstBuf, 32) == blank8);
    CHECK(m.str(sd::kNameSurnameBuf, 32) == blank8);
    for (u32 i = 27; i <= 30; ++i) CHECK(r32(m, sd::kNameWork + 4 * i) == 0);
    // the name-entry task's wait: no task -> 1
    w32(m, sd::kNameWork + 4 * 26, 0);
    CHECK(R.v0("sub_45EBA0", {0, 0, 0, 0}) == 1);

    // an animation track: reset, one key, run it to the end
    std::memset(m.at(kTrack), 0x5A, 152);
    CHECK(R.v0("sub_45AF90", {kTrack, 0, 0, 0}) == 0);
    for (u32 o = 128; o < 152; o += 4) CHECK(r32(m, kTrack + o) == 0);
    CHECK(R.v0("sub_45AF90", {0, 0, 0, 0}) == 1);
    HwCheck key;
    key.gpr_in = {{GPR_T0, 100}, {GPR_T1, 2}, {GPR_T2, 3}, {GPR_T3, 10}};  // y1, delay, hold, frames
    CHECK(R.v0("sub_45AFD0", {kTrack, 10, 20, 60}, key) == 0);
    CHECK(r32(m, kTrack + 132) == 1);                        // one key
    CHECK((r32(m, kTrack + 140) & 3) == 1);                  // running, not done
    CHECK(r32(m, kTrack + 148) == 2 + 3 + 10);               // delay + hold + frames
    CHECK(r16(m, kTrack + 30) == 10);
    CHECK(R.v0("sub_45B480", {kTrack, 0, 0, 0}) == 1);
    CHECK(R.v0("sub_45B4B0", {kTrack, 0, 0, 0}) == 0);
    CHECK(R.v0("sub_45B420", {kTrack, kOut, 0, 0}) == 0);
    float xy[2];
    std::memcpy(xy, m.at(kOut), 8);
    CHECK(xy[0] == 10.0f);
    CHECK(xy[1] == 20.0f);
    CHECK(R.v0("sub_45B420", {0, kOut, 0, 0}) == 1);
    int steps = 0;
    while (R.v0("sub_45B480", {kTrack, 0, 0, 0}) == 1 && steps < 40) {
        R.call("sub_45B190", {kTrack, 0, 0, 0});
        ++steps;
    }
    CHECK(steps >= 10);
    CHECK(steps < 40);
    CHECK((r32(m, kTrack + 140) & 2) != 0);  // done
    for (int k = 0; k < 4; ++k) R.call("sub_45AFD0", {kTrack, 0, 0, 0}, key);
    CHECK(R.v0("sub_45AFD0", {kTrack, 0, 0, 0}, key) == 2);  // four keys at most
    CHECK(r32(m, kTrack + 132) == 4);

    // the field-event helpers on the task in 0x7CE6F8, on every snapshot: -1 / 0 without it
    for (const char* s : kSnapshots) {
        auto sm = real_machine(s);
        if (!sm) continue;
        Real RS{*sm, s};
        const u32 t = r32(*sm, 0x7CE6F8u);
        const u32 w = t ? r32(*sm, t + kTaskWork) : 0;
        CHECK(RS.v0("sub_45AF40", {0, 0, 0, 0}) == (t ? static_cast<s32>(r32(*sm, w + 80)) : -1));
        CHECK(RS.v0("sub_45A3B0", {0, 0, 0, 0}) == (t ? (static_cast<s8>(r8(*sm, w + 4)) >= 2 ? 1 : 0) : 0));
        RS.call("sub_45A430", {1, 0, 0, 0});
        RS.call("sub_45A430", {0, 0, 0, 0});
        RS.call("sub_45AF70", {3, 0, 0, 0});
        if (t) CHECK(r8(*sm, w + 93) == 3);
    }
}

TEST_CASE("game(savedata): the persona functions on the hero's real stock, the skill element classes") {
    int personas = 0;
    for (const char* s : {"climb_ref_17000", "fusion_vr_5000", "shop_ref_4100"}) {
        auto mp = real_machine(s);
        if (!mp) continue;
        Machine& m = *mp;
        Real R{m, s};
        for (u32 slot = 0; slot < 12; ++slot) {
            const u32 p = 0x836BACu + sd::kPersonaSize * slot;
            if ((r16(m, p) & 1) == 0) continue;
            ++personas;
            for (u32 stat = 0; stat < 5; ++stat) R.call("sub_173C60", {p, stat, 0, 0});
            // the level-up record: its levels gained never take the persona past 99
            std::memset(m.at(kOut), 0xCC, 40);
            R.call("sub_175CE0", {p, kOut, 0, 0});
            CHECK(r8(m, kOut) + r8(m, p + 4) <= 100);
            for (u32 i = 0; i < 5; ++i) CHECK(r8(m, kOut + 34 + i) <= 99);
        }
        // give the hero a persona he has (selects it), give a member a persona, remove the last used slot
        R.call("sub_175820", {1, r16(m, 0x836BACu + 2), 0, 0});
        R.call("sub_175820", {2, 0xC1, 0, 0});
        CHECK(r16(m, sd::kPartyRecords + 0xDC) == 1);
        CHECK(r16(m, sd::kPartyRecords + 0xDC + 2) == 0xC1);
        for (s32 slot = 11; slot >= 0; --slot)
            if (r16(m, 0x836BACu + sd::kPersonaSize * static_cast<u32>(slot)) & 1) {
                CHECK(R.v0("sub_174C10", {static_cast<u64>(slot), 0, 0, 0}) == 1);
                break;
            }
        // the skill element classes of every skill id
        for (u32 skill = 0; skill < 0x270; skill += 7) R.call("sub_17D2E0", {skill, 0, 0, 0});
    }
    if (personas == 0) MESSAGE("SKIP: no snapshot with a persona stock");
    for (const auto& [k, n] : g_stops) MESSAGE("early stops: " << k << " x" << n);
    MESSAGE("real-state pairs so far: " << g_pairs << " (" << g_long_checks << " check points compared by pair_long)");
}

#else

TEST_CASE("game(savedata): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
