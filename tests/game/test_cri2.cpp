// Pair tests for slice cri2 (game/src/cri/cri2_*.cpp: the CRI middleware, second pass). Every body against its
// recompiled body, compared by tests/game/handgen_pairs.h (the whole register file and cycle count at every check point
// and at the return / stop, all 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window, the bus log) or, where
// a callee is not emitted in this test binary (the drivers below these layers: ADXB, PS2RNA, ADXSTM, the list streamer,
// the IPU bit reader, newlib strncmp), by stand_ins.h's run_pair_si with that callee stood in (the same comparison plus
// both call logs). On top of the generic sweep (random worlds) each family runs on meaningful inputs with host checks:
//   * cvFs: a test device registered through cvFsAddDev, its interface table a row of recorders, every request
//     dispatched through it (the entry, the device file, the codes of the option requests, the 64-bit pairs, the error
//     paths); the snapshots' live device table looked up by name;
//   * ADXT: the replay snapshots' live players driven by the server frame after frame (the decoder, output and streamer
//     layers stood in, the output draining the PCM joints), the state rules one by one (opening, buffering, playing,
//     decode end, play end, error), and a whole lifecycle on a fresh machine -- create, start from a memory index holding
//     a real .adx file of the disc, the header and decode stages, the loop / end traps, stop, destroy;
//   * ADXSJD: the accessors on built decoder records, the header stage on real .adx headers (padding, alignment, the
//     header length) and the decode stage's joint bookkeeping;
//   * libmpeg: the GOP / picture headers and the extension walker on the video streams of the disc's .sfd movies (an MPEG
//     program-stream demultiplexer on the host feeds the bit reader stand-ins; no media is committed), the sequence
//     buffer layout, the residual add and the reference fetches against host models, the reference rotation rules.
// Random draws are separate statements (MSVC and clang evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/cri2.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
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
void fn_sub_541D48_00541d48(EEContext&);  // generated body
void fn_sub_541D48_00541d48__recomp(EEContext&);  // recompiled
void fn_sub_541DE8_00541de8(EEContext&);  // generated body
void fn_sub_541DE8_00541de8__recomp(EEContext&);  // recompiled
void fn_sub_541E28_00541e28(EEContext&);  // generated body
void fn_sub_541E28_00541e28__recomp(EEContext&);  // recompiled
void fn_sub_541FA8_00541fa8(EEContext&);  // generated body
void fn_sub_541FA8_00541fa8__recomp(EEContext&);  // recompiled
void fn_sub_542008_00542008(EEContext&);  // generated body
void fn_sub_542008_00542008__recomp(EEContext&);  // recompiled
void fn_sub_542010_00542010(EEContext&);  // generated body
void fn_sub_542010_00542010__recomp(EEContext&);  // recompiled
void fn_sub_542060_00542060(EEContext&);  // generated body
void fn_sub_542060_00542060__recomp(EEContext&);  // recompiled
void fn_sub_5420A0_005420a0(EEContext&);  // generated body
void fn_sub_5420A0_005420a0__recomp(EEContext&);  // recompiled
void fn_sub_5420D0_005420d0(EEContext&);  // generated body
void fn_sub_5420D0_005420d0__recomp(EEContext&);  // recompiled
void fn_sub_542100_00542100(EEContext&);  // generated body
void fn_sub_542100_00542100__recomp(EEContext&);  // recompiled
void fn_sub_542130_00542130(EEContext&);  // generated body
void fn_sub_542130_00542130__recomp(EEContext&);  // recompiled
void fn_sub_542438_00542438(EEContext&);  // generated body
void fn_sub_542438_00542438__recomp(EEContext&);  // recompiled
void fn_sub_542558_00542558(EEContext&);  // generated body
void fn_sub_542558_00542558__recomp(EEContext&);  // recompiled
void fn_sub_5428C0_005428c0(EEContext&);  // generated body
void fn_sub_5428C0_005428c0__recomp(EEContext&);  // recompiled
void fn_sub_542B18_00542b18(EEContext&);  // generated body
void fn_sub_542B18_00542b18__recomp(EEContext&);  // recompiled
void fn_sub_542BC8_00542bc8(EEContext&);  // generated body
void fn_sub_542BC8_00542bc8__recomp(EEContext&);  // recompiled
void fn_sub_542F00_00542f00(EEContext&);  // generated body
void fn_sub_542F00_00542f00__recomp(EEContext&);  // recompiled
void fn_sub_542F60_00542f60(EEContext&);  // generated body
void fn_sub_542F60_00542f60__recomp(EEContext&);  // recompiled
void fn_sub_542F68_00542f68(EEContext&);  // generated body
void fn_sub_542F68_00542f68__recomp(EEContext&);  // recompiled
void fn_sub_542F88_00542f88(EEContext&);  // generated body
void fn_sub_542F88_00542f88__recomp(EEContext&);  // recompiled
void fn_sub_5430A8_005430a8(EEContext&);  // generated body
void fn_sub_5430A8_005430a8__recomp(EEContext&);  // recompiled
void fn_sub_5430B8_005430b8(EEContext&);  // generated body
void fn_sub_5430B8_005430b8__recomp(EEContext&);  // recompiled
void fn_sub_5430C8_005430c8(EEContext&);  // generated body
void fn_sub_5430C8_005430c8__recomp(EEContext&);  // recompiled
void fn_sub_5430D8_005430d8(EEContext&);  // generated body
void fn_sub_5430D8_005430d8__recomp(EEContext&);  // recompiled
void fn_sub_5430E8_005430e8(EEContext&);  // generated body
void fn_sub_5430E8_005430e8__recomp(EEContext&);  // recompiled
void fn_sub_543100_00543100(EEContext&);  // generated body
void fn_sub_543100_00543100__recomp(EEContext&);  // recompiled
void fn_sub_543118_00543118(EEContext&);  // generated body
void fn_sub_543118_00543118__recomp(EEContext&);  // recompiled
void fn_sub_543130_00543130(EEContext&);  // generated body
void fn_sub_543130_00543130__recomp(EEContext&);  // recompiled
void fn_sub_543148_00543148(EEContext&);  // generated body
void fn_sub_543148_00543148__recomp(EEContext&);  // recompiled
void fn_sub_543178_00543178(EEContext&);  // generated body
void fn_sub_543178_00543178__recomp(EEContext&);  // recompiled
void fn_sub_5431A8_005431a8(EEContext&);  // generated body
void fn_sub_5431A8_005431a8__recomp(EEContext&);  // recompiled
void fn_sub_5431D8_005431d8(EEContext&);  // generated body
void fn_sub_5431D8_005431d8__recomp(EEContext&);  // recompiled
void fn_sub_5431F0_005431f0(EEContext&);  // generated body
void fn_sub_5431F0_005431f0__recomp(EEContext&);  // recompiled
void fn_sub_543220_00543220(EEContext&);  // generated body
void fn_sub_543220_00543220__recomp(EEContext&);  // recompiled
void fn_sub_543238_00543238(EEContext&);  // generated body
void fn_sub_543238_00543238__recomp(EEContext&);  // recompiled
void fn_sub_543268_00543268(EEContext&);  // generated body
void fn_sub_543268_00543268__recomp(EEContext&);  // recompiled
void fn_sub_5432C0_005432c0(EEContext&);  // generated body
void fn_sub_5432C0_005432c0__recomp(EEContext&);  // recompiled
void fn_sub_5433A8_005433a8(EEContext&);  // generated body
void fn_sub_5433A8_005433a8__recomp(EEContext&);  // recompiled
void fn_sub_547BC0_00547bc0(EEContext&);  // generated body
void fn_sub_547BC0_00547bc0__recomp(EEContext&);  // recompiled
void fn_sub_547C18_00547c18(EEContext&);  // generated body
void fn_sub_547C18_00547c18__recomp(EEContext&);  // recompiled
void fn_sub_547FD0_00547fd0(EEContext&);  // generated body
void fn_sub_547FD0_00547fd0__recomp(EEContext&);  // recompiled
void fn_sub_547FF8_00547ff8(EEContext&);  // generated body
void fn_sub_547FF8_00547ff8__recomp(EEContext&);  // recompiled
void fn_sub_548020_00548020(EEContext&);  // generated body
void fn_sub_548020_00548020__recomp(EEContext&);  // recompiled
void fn_sub_548048_00548048(EEContext&);  // generated body
void fn_sub_548048_00548048__recomp(EEContext&);  // recompiled
void fn_sub_548078_00548078(EEContext&);  // generated body
void fn_sub_548078_00548078__recomp(EEContext&);  // recompiled
void fn_sub_548318_00548318(EEContext&);  // generated body
void fn_sub_548318_00548318__recomp(EEContext&);  // recompiled
void fn_sub_548410_00548410(EEContext&);  // generated body
void fn_sub_548410_00548410__recomp(EEContext&);  // recompiled
void fn_sub_5484E0_005484e0(EEContext&);  // generated body
void fn_sub_5484E0_005484e0__recomp(EEContext&);  // recompiled
void fn_sub_548520_00548520(EEContext&);  // generated body
void fn_sub_548520_00548520__recomp(EEContext&);  // recompiled
void fn_sub_5485D8_005485d8(EEContext&);  // generated body
void fn_sub_5485D8_005485d8__recomp(EEContext&);  // recompiled
void fn_sub_548678_00548678(EEContext&);  // generated body
void fn_sub_548678_00548678__recomp(EEContext&);  // recompiled
void fn_sub_5486A8_005486a8(EEContext&);  // generated body
void fn_sub_5486A8_005486a8__recomp(EEContext&);  // recompiled
void fn_sub_548768_00548768(EEContext&);  // generated body
void fn_sub_548768_00548768__recomp(EEContext&);  // recompiled
void fn_sub_5487A0_005487a0(EEContext&);  // generated body
void fn_sub_5487A0_005487a0__recomp(EEContext&);  // recompiled
void fn_sub_5489A0_005489a0(EEContext&);  // generated body
void fn_sub_5489A0_005489a0__recomp(EEContext&);  // recompiled
void fn_sub_548AE8_00548ae8(EEContext&);  // generated body
void fn_sub_548AE8_00548ae8__recomp(EEContext&);  // recompiled
void fn_sub_548EB8_00548eb8(EEContext&);  // generated body
void fn_sub_548EB8_00548eb8__recomp(EEContext&);  // recompiled
void fn_sub_548EF0_00548ef0(EEContext&);  // generated body
void fn_sub_548EF0_00548ef0__recomp(EEContext&);  // recompiled
void fn_sub_548F40_00548f40(EEContext&);  // generated body
void fn_sub_548F40_00548f40__recomp(EEContext&);  // recompiled
void fn_sub_548F78_00548f78(EEContext&);  // generated body
void fn_sub_548F78_00548f78__recomp(EEContext&);  // recompiled
void fn_sub_5491B0_005491b0(EEContext&);  // generated body
void fn_sub_5491B0_005491b0__recomp(EEContext&);  // recompiled
void fn_sub_549480_00549480(EEContext&);  // generated body
void fn_sub_549480_00549480__recomp(EEContext&);  // recompiled
void fn_sub_5494C0_005494c0(EEContext&);  // generated body
void fn_sub_5494C0_005494c0__recomp(EEContext&);  // recompiled
void fn_sub_5497A0_005497a0(EEContext&);  // generated body
void fn_sub_5497A0_005497a0__recomp(EEContext&);  // recompiled
void fn_sub_5497B0_005497b0(EEContext&);  // generated body
void fn_sub_5497B0_005497b0__recomp(EEContext&);  // recompiled
void fn_sub_5497E0_005497e0(EEContext&);  // generated body
void fn_sub_5497E0_005497e0__recomp(EEContext&);  // recompiled
void fn_sub_5497F8_005497f8(EEContext&);  // generated body
void fn_sub_5497F8_005497f8__recomp(EEContext&);  // recompiled
void fn_sub_549838_00549838(EEContext&);  // generated body
void fn_sub_549838_00549838__recomp(EEContext&);  // recompiled
void fn_sub_549BB0_00549bb0(EEContext&);  // generated body
void fn_sub_549BB0_00549bb0__recomp(EEContext&);  // recompiled
void fn_sub_549DE8_00549de8(EEContext&);  // generated body
void fn_sub_549DE8_00549de8__recomp(EEContext&);  // recompiled
void fn_sub_549E28_00549e28(EEContext&);  // generated body
void fn_sub_549E28_00549e28__recomp(EEContext&);  // recompiled
void fn_sub_549EA0_00549ea0(EEContext&);  // generated body
void fn_sub_549EA0_00549ea0__recomp(EEContext&);  // recompiled
void fn_sub_549EC8_00549ec8(EEContext&);  // generated body
void fn_sub_549EC8_00549ec8__recomp(EEContext&);  // recompiled
void fn_sub_549FF8_00549ff8(EEContext&);  // generated body
void fn_sub_549FF8_00549ff8__recomp(EEContext&);  // recompiled
void fn_sub_54A030_0054a030(EEContext&);  // generated body
void fn_sub_54A030_0054a030__recomp(EEContext&);  // recompiled
void fn_sub_54A138_0054a138(EEContext&);  // generated body
void fn_sub_54A138_0054a138__recomp(EEContext&);  // recompiled
void fn_sub_54A178_0054a178(EEContext&);  // generated body
void fn_sub_54A178_0054a178__recomp(EEContext&);  // recompiled
void fn_sub_54A3C0_0054a3c0(EEContext&);  // generated body
void fn_sub_54A3C0_0054a3c0__recomp(EEContext&);  // recompiled
void fn_get_bufs_2_0054a400(EEContext&);  // generated body
void fn_get_bufs_2_0054a400__recomp(EEContext&);  // recompiled
void fn_sub_54A530_0054a530(EEContext&);  // generated body
void fn_sub_54A530_0054a530__recomp(EEContext&);  // recompiled
void fn_sub_54A568_0054a568(EEContext&);  // generated body
void fn_sub_54A568_0054a568__recomp(EEContext&);  // recompiled
void fn___env_unlock_0_0054a638(EEContext&);  // generated body
void fn___env_unlock_0_0054a638__recomp(EEContext&);  // recompiled
void fn_sub_54A968_0054a968(EEContext&);  // generated body
void fn_sub_54A968_0054a968__recomp(EEContext&);  // recompiled
void fn_sub_54B088_0054b088(EEContext&);  // generated body
void fn_sub_54B088_0054b088__recomp(EEContext&);  // recompiled
void fn_sub_54B0D8_0054b0d8(EEContext&);  // generated body
void fn_sub_54B0D8_0054b0d8__recomp(EEContext&);  // recompiled
void fn_sub_54B230_0054b230(EEContext&);  // generated body
void fn_sub_54B230_0054b230__recomp(EEContext&);  // recompiled
void fn_sub_54B2E8_0054b2e8(EEContext&);  // generated body
void fn_sub_54B2E8_0054b2e8__recomp(EEContext&);  // recompiled
void fn_sub_54B328_0054b328(EEContext&);  // generated body
void fn_sub_54B328_0054b328__recomp(EEContext&);  // recompiled
void fn_sub_54B4D0_0054b4d0(EEContext&);  // generated body
void fn_sub_54B4D0_0054b4d0__recomp(EEContext&);  // recompiled
void fn_sub_54B520_0054b520(EEContext&);  // generated body
void fn_sub_54B520_0054b520__recomp(EEContext&);  // recompiled
void fn_sub_54B690_0054b690(EEContext&);  // generated body
void fn_sub_54B690_0054b690__recomp(EEContext&);  // recompiled
void fn_sub_54B988_0054b988(EEContext&);  // generated body
void fn_sub_54B988_0054b988__recomp(EEContext&);  // recompiled
void fn_sub_54B9F0_0054b9f0(EEContext&);  // generated body
void fn_sub_54B9F0_0054b9f0__recomp(EEContext&);  // recompiled
void fn_sub_54BCD8_0054bcd8(EEContext&);  // generated body
void fn_sub_54BCD8_0054bcd8__recomp(EEContext&);  // recompiled
void fn_sub_54C100_0054c100(EEContext&);  // generated body
void fn_sub_54C100_0054c100__recomp(EEContext&);  // recompiled
void fn_sub_54C288_0054c288(EEContext&);  // generated body
void fn_sub_54C288_0054c288__recomp(EEContext&);  // recompiled
void fn_sub_54C370_0054c370(EEContext&);  // generated body
void fn_sub_54C370_0054c370__recomp(EEContext&);  // recompiled
void fn_sub_54C578_0054c578(EEContext&);  // generated body
void fn_sub_54C578_0054c578__recomp(EEContext&);  // recompiled
void fn_sub_54C8C0_0054c8c0(EEContext&);  // generated body
void fn_sub_54C8C0_0054c8c0__recomp(EEContext&);  // recompiled
void fn_sub_54C940_0054c940(EEContext&);  // generated body
void fn_sub_54C940_0054c940__recomp(EEContext&);  // recompiled
void fn_sub_54C9D8_0054c9d8(EEContext&);  // generated body
void fn_sub_54C9D8_0054c9d8__recomp(EEContext&);  // recompiled
void fn_sub_54CA08_0054ca08(EEContext&);  // generated body
void fn_sub_54CA08_0054ca08__recomp(EEContext&);  // recompiled
void fn_sub_539818_00539818(EEContext&);  // generated body
void fn_sub_539818_00539818__recomp(EEContext&);  // recompiled
void fn_sub_539830_00539830(EEContext&);  // generated body
void fn_sub_539830_00539830__recomp(EEContext&);  // recompiled
void fn_cvFsAddDev_00555b10(EEContext&);  // generated body
void fn_cvFsAddDev_00555b10__recomp(EEContext&);  // recompiled
void fn_cvfs_addDevice_00555ba0(EEContext&);  // generated body
void fn_cvfs_addDevice_00555ba0__recomp(EEContext&);  // recompiled
void fn_cvfs_getDevice_00555c78(EEContext&);  // generated body
void fn_cvfs_getDevice_00555c78__recomp(EEContext&);  // recompiled
void fn_sub_555D70_00555d70(EEContext&);  // generated body
void fn_sub_555D70_00555d70__recomp(EEContext&);  // recompiled
void fn_sub_555E48_00555e48(EEContext&);  // generated body
void fn_sub_555E48_00555e48__recomp(EEContext&);  // recompiled
void fn_sub_555F10_00555f10(EEContext&);  // generated body
void fn_sub_555F10_00555f10__recomp(EEContext&);  // recompiled
void fn_cvfs_variousProc_00555fa0(EEContext&);  // generated body
void fn_cvfs_variousProc_00555fa0__recomp(EEContext&);  // recompiled
void fn_cvFsOpen_00556048(EEContext&);  // generated body
void fn_cvFsOpen_00556048__recomp(EEContext&);  // recompiled
void fn_sub_556170_00556170(EEContext&);  // generated body
void fn_sub_556170_00556170__recomp(EEContext&);  // recompiled
void fn_sub_5561D8_005561d8(EEContext&);  // generated body
void fn_sub_5561D8_005561d8__recomp(EEContext&);  // recompiled
void fn_cvFsClose_00556398(EEContext&);  // generated body
void fn_cvFsClose_00556398__recomp(EEContext&);  // recompiled
void fn_cvFsTell_00556410(EEContext&);  // generated body
void fn_cvFsTell_00556410__recomp(EEContext&);  // recompiled
void fn_cvFsSeek_00556478(EEContext&);  // generated body
void fn_cvFsSeek_00556478__recomp(EEContext&);  // recompiled
void fn_cvFsReqRd_005564e0(EEContext&);  // generated body
void fn_cvFsReqRd_005564e0__recomp(EEContext&);  // recompiled
void fn_sub_556548_00556548(EEContext&);  // generated body
void fn_sub_556548_00556548__recomp(EEContext&);  // recompiled
void fn_sub_5565B0_005565b0(EEContext&);  // generated body
void fn_sub_5565B0_005565b0__recomp(EEContext&);  // recompiled
void fn_cvFsExecServer_00556608(EEContext&);  // generated body
void fn_cvFsExecServer_00556608__recomp(EEContext&);  // recompiled
void fn_cvFsGetStat_00556668(EEContext&);  // generated body
void fn_cvFsGetStat_00556668__recomp(EEContext&);  // recompiled
void fn_cvFsGetFileSize_005566d0(EEContext&);  // generated body
void fn_cvFsGetFileSize_005566d0__recomp(EEContext&);  // recompiled
void fn_sub_556790_00556790(EEContext&);  // generated body
void fn_sub_556790_00556790__recomp(EEContext&);  // recompiled
void fn_sub_556860_00556860(EEContext&);  // generated body
void fn_sub_556860_00556860__recomp(EEContext&);  // recompiled
void fn_sub_5568C0_005568c0(EEContext&);  // generated body
void fn_sub_5568C0_005568c0__recomp(EEContext&);  // recompiled
void fn_sub_556A00_00556a00(EEContext&);  // generated body
void fn_sub_556A00_00556a00__recomp(EEContext&);  // recompiled
void fn_sub_556A68_00556a68(EEContext&);  // generated body
void fn_sub_556A68_00556a68__recomp(EEContext&);  // recompiled
void fn_sub_556AC0_00556ac0(EEContext&);  // generated body
void fn_sub_556AC0_00556ac0__recomp(EEContext&);  // recompiled
void fn_sub_556B28_00556b28(EEContext&);  // generated body
void fn_sub_556B28_00556b28__recomp(EEContext&);  // recompiled
void fn_sub_556BE8_00556be8(EEContext&);  // generated body
void fn_sub_556BE8_00556be8__recomp(EEContext&);  // recompiled
void fn_sub_556C90_00556c90(EEContext&);  // generated body
void fn_sub_556C90_00556c90__recomp(EEContext&);  // recompiled
void fn_sub_556DA0_00556da0(EEContext&);  // generated body
void fn_sub_556DA0_00556da0__recomp(EEContext&);  // recompiled
void fn_sub_556E78_00556e78(EEContext&);  // generated body
void fn_sub_556E78_00556e78__recomp(EEContext&);  // recompiled
void fn_sub_556ED0_00556ed0(EEContext&);  // generated body
void fn_sub_556ED0_00556ed0__recomp(EEContext&);  // recompiled
void fn_sub_556F90_00556f90(EEContext&);  // generated body
void fn_sub_556F90_00556f90__recomp(EEContext&);  // recompiled
void fn_sub_557050_00557050(EEContext&);  // generated body
void fn_sub_557050_00557050__recomp(EEContext&);  // recompiled
void fn_sub_557110_00557110(EEContext&);  // generated body
void fn_sub_557110_00557110__recomp(EEContext&);  // recompiled
void fn_sub_557198_00557198(EEContext&);  // generated body
void fn_sub_557198_00557198__recomp(EEContext&);  // recompiled
void fn_sub_5571C0_005571c0(EEContext&);  // generated body
void fn_sub_5571C0_005571c0__recomp(EEContext&);  // recompiled
void fn_sub_557228_00557228(EEContext&);  // generated body
void fn_sub_557228_00557228__recomp(EEContext&);  // recompiled
void fn_cvFsSetCurVolume_00557290(EEContext&);  // generated body
void fn_cvFsSetCurVolume_00557290__recomp(EEContext&);  // recompiled
void fn_sub_557350_00557350(EEContext&);  // generated body
void fn_sub_557350_00557350__recomp(EEContext&);  // recompiled
void fn_cvFsAddVolumeEx_00557358(EEContext&);  // generated body
void fn_cvFsAddVolumeEx_00557358__recomp(EEContext&);  // recompiled
void fn_sub_557460_00557460(EEContext&);  // generated body
void fn_sub_557460_00557460__recomp(EEContext&);  // recompiled
void fn_sub_557520_00557520(EEContext&);  // generated body
void fn_sub_557520_00557520__recomp(EEContext&);  // recompiled
void fn_cvFsSetDefVol_005575f0(EEContext&);  // generated body
void fn_cvFsSetDefVol_005575f0__recomp(EEContext&);  // recompiled
void fn_cvfs_isNeedDevName_005576b0(EEContext&);  // generated body
void fn_cvfs_isNeedDevName_005576b0__recomp(EEContext&);  // recompiled
void fn_cvfs_addDevName_00557700(EEContext&);  // generated body
void fn_cvfs_addDevName_00557700__recomp(EEContext&);  // recompiled
void fn_sub_557798_00557798(EEContext&);  // generated body
void fn_sub_557798_00557798__recomp(EEContext&);  // recompiled
void fn_sub_5577B8_005577b8(EEContext&);  // generated body
void fn_sub_5577B8_005577b8__recomp(EEContext&);  // recompiled
void fn_sub_557850_00557850(EEContext&);  // generated body
void fn_sub_557850_00557850__recomp(EEContext&);  // recompiled
void fn_sub_557908_00557908(EEContext&);  // generated body
void fn_sub_557908_00557908__recomp(EEContext&);  // recompiled
void fn_sub_5579C8_005579c8(EEContext&);  // generated body
void fn_sub_5579C8_005579c8__recomp(EEContext&);  // recompiled
void fn_sub_557A28_00557a28(EEContext&);  // generated body
void fn_sub_557A28_00557a28__recomp(EEContext&);  // recompiled
void fn__getAllRefs_004fb168(EEContext&);  // generated body
void fn__getAllRefs_004fb168__recomp(EEContext&);  // recompiled
void fn__getRef0_004fbac0(EEContext&);  // generated body
void fn__getRef0_004fbac0__recomp(EEContext&);  // recompiled
void fn__skipMB0_004fd8a8(EEContext&);  // generated body
void fn__skipMB0_004fd8a8__recomp(EEContext&);  // recompiled
void fn__copyAddRefImage_004fd968(EEContext&);  // generated body
void fn__copyAddRefImage_004fd968__recomp(EEContext&);  // recompiled
void fn__rix_000_004fdc98(EEContext&);  // generated body
void fn__rix_000_004fdc98__recomp(EEContext&);  // recompiled
void fn__ri0_000_004fdd10(EEContext&);  // generated body
void fn__ri0_000_004fdd10__recomp(EEContext&);  // recompiled
void fn__rix_001_004fdda8(EEContext&);  // generated body
void fn__rix_001_004fdda8__recomp(EEContext&);  // recompiled
void fn__ri0_001_004fde60(EEContext&);  // generated body
void fn__ri0_001_004fde60__recomp(EEContext&);  // recompiled
void fn__rix_010_004fdf30(EEContext&);  // generated body
void fn__rix_010_004fdf30__recomp(EEContext&);  // recompiled
void fn__ri0_010_004fdfe0(EEContext&);  // generated body
void fn__ri0_010_004fdfe0__recomp(EEContext&);  // recompiled
void fn__rix_011_004fe098(EEContext&);  // generated body
void fn__rix_011_004fe098__recomp(EEContext&);  // recompiled
void fn__ri0_011_004fe190(EEContext&);  // generated body
void fn__ri0_011_004fe190__recomp(EEContext&);  // recompiled
void fn__rix_100_004fe290(EEContext&);  // generated body
void fn__rix_100_004fe290__recomp(EEContext&);  // recompiled
void fn__ri0_100_004fe330(EEContext&);  // generated body
void fn__ri0_100_004fe330__recomp(EEContext&);  // recompiled
void fn__rix_101_004fe3e0(EEContext&);  // generated body
void fn__rix_101_004fe3e0__recomp(EEContext&);  // recompiled
void fn__ri0_101_004fe4c0(EEContext&);  // generated body
void fn__ri0_101_004fe4c0__recomp(EEContext&);  // recompiled
void fn__rix_110_004fe5a8(EEContext&);  // generated body
void fn__rix_110_004fe5a8__recomp(EEContext&);  // recompiled
void fn__ri0_110_004fe680(EEContext&);  // generated body
void fn__ri0_110_004fe680__recomp(EEContext&);  // recompiled
void fn__rix_111_004fe750(EEContext&);  // generated body
void fn__rix_111_004fe750__recomp(EEContext&);  // recompiled
void fn__ri0_111_004fe870(EEContext&);  // generated body
void fn__ri0_111_004fe870__recomp(EEContext&);  // recompiled
void fn__initSeq_004febc8(EEContext&);  // generated body
void fn__initSeq_004febc8__recomp(EEContext&);  // recompiled
void fn__groupOfPicturesHeader_004ff190(EEContext&);  // generated body
void fn__groupOfPicturesHeader_004ff190__recomp(EEContext&);  // recompiled
void fn__pictureHeader_004ff230(EEContext&);  // generated body
void fn__pictureHeader_004ff230__recomp(EEContext&);  // recompiled
void fn__extensionAndUserData_004ff7c8(EEContext&);  // generated body
void fn__extensionAndUserData_004ff7c8__recomp(EEContext&);  // recompiled
void fn_flushBuf32_004ffb30(EEContext&);  // generated body
void fn_flushBuf32_004ffb30__recomp(EEContext&);  // recompiled
void fn__getpic_00500278(EEContext&);  // generated body
void fn__getpic_00500278__recomp(EEContext&);  // recompiled
void fn__updateRefImage_00500430(EEContext&);  // generated body
void fn__updateRefImage_00500430__recomp(EEContext&);  // recompiled
void fn__decodeOrSkipFrame_005006e8(EEContext&);  // generated body
void fn__decodeOrSkipFrame_005006e8__recomp(EEContext&);  // recompiled
void fn__decodeOrSkip_00500e00(EEContext&);  // generated body
void fn__decodeOrSkip_00500e00__recomp(EEContext&);  // recompiled
void fn__decPicture_00500f98(EEContext&);  // generated body
void fn__decPicture_00500f98__recomp(EEContext&);  // recompiled
void fn__dispRefImage_00501408(EEContext&);  // generated body
void fn__dispRefImage_00501408__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_541D48", 0x541D48, &recomp_gen::fn_sub_541D48_00541d48, &recomp_gen::fn_sub_541D48_00541d48__recomp},
    {"sub_541DE8", 0x541DE8, &recomp_gen::fn_sub_541DE8_00541de8, &recomp_gen::fn_sub_541DE8_00541de8__recomp},
    {"sub_541E28", 0x541E28, &recomp_gen::fn_sub_541E28_00541e28, &recomp_gen::fn_sub_541E28_00541e28__recomp},
    {"sub_541FA8", 0x541FA8, &recomp_gen::fn_sub_541FA8_00541fa8, &recomp_gen::fn_sub_541FA8_00541fa8__recomp},
    {"sub_542008", 0x542008, &recomp_gen::fn_sub_542008_00542008, &recomp_gen::fn_sub_542008_00542008__recomp},
    {"sub_542010", 0x542010, &recomp_gen::fn_sub_542010_00542010, &recomp_gen::fn_sub_542010_00542010__recomp},
    {"sub_542060", 0x542060, &recomp_gen::fn_sub_542060_00542060, &recomp_gen::fn_sub_542060_00542060__recomp},
    {"sub_5420A0", 0x5420A0, &recomp_gen::fn_sub_5420A0_005420a0, &recomp_gen::fn_sub_5420A0_005420a0__recomp},
    {"sub_5420D0", 0x5420D0, &recomp_gen::fn_sub_5420D0_005420d0, &recomp_gen::fn_sub_5420D0_005420d0__recomp},
    {"sub_542100", 0x542100, &recomp_gen::fn_sub_542100_00542100, &recomp_gen::fn_sub_542100_00542100__recomp},
    {"sub_542130", 0x542130, &recomp_gen::fn_sub_542130_00542130, &recomp_gen::fn_sub_542130_00542130__recomp},
    {"sub_542438", 0x542438, &recomp_gen::fn_sub_542438_00542438, &recomp_gen::fn_sub_542438_00542438__recomp},
    {"sub_542558", 0x542558, &recomp_gen::fn_sub_542558_00542558, &recomp_gen::fn_sub_542558_00542558__recomp},
    {"sub_5428C0", 0x5428C0, &recomp_gen::fn_sub_5428C0_005428c0, &recomp_gen::fn_sub_5428C0_005428c0__recomp},
    {"sub_542B18", 0x542B18, &recomp_gen::fn_sub_542B18_00542b18, &recomp_gen::fn_sub_542B18_00542b18__recomp},
    {"sub_542BC8", 0x542BC8, &recomp_gen::fn_sub_542BC8_00542bc8, &recomp_gen::fn_sub_542BC8_00542bc8__recomp},
    {"sub_542F00", 0x542F00, &recomp_gen::fn_sub_542F00_00542f00, &recomp_gen::fn_sub_542F00_00542f00__recomp},
    {"sub_542F60", 0x542F60, &recomp_gen::fn_sub_542F60_00542f60, &recomp_gen::fn_sub_542F60_00542f60__recomp},
    {"sub_542F68", 0x542F68, &recomp_gen::fn_sub_542F68_00542f68, &recomp_gen::fn_sub_542F68_00542f68__recomp},
    {"sub_542F88", 0x542F88, &recomp_gen::fn_sub_542F88_00542f88, &recomp_gen::fn_sub_542F88_00542f88__recomp},
    {"sub_5430A8", 0x5430A8, &recomp_gen::fn_sub_5430A8_005430a8, &recomp_gen::fn_sub_5430A8_005430a8__recomp},
    {"sub_5430B8", 0x5430B8, &recomp_gen::fn_sub_5430B8_005430b8, &recomp_gen::fn_sub_5430B8_005430b8__recomp},
    {"sub_5430C8", 0x5430C8, &recomp_gen::fn_sub_5430C8_005430c8, &recomp_gen::fn_sub_5430C8_005430c8__recomp},
    {"sub_5430D8", 0x5430D8, &recomp_gen::fn_sub_5430D8_005430d8, &recomp_gen::fn_sub_5430D8_005430d8__recomp},
    {"sub_5430E8", 0x5430E8, &recomp_gen::fn_sub_5430E8_005430e8, &recomp_gen::fn_sub_5430E8_005430e8__recomp},
    {"sub_543100", 0x543100, &recomp_gen::fn_sub_543100_00543100, &recomp_gen::fn_sub_543100_00543100__recomp},
    {"sub_543118", 0x543118, &recomp_gen::fn_sub_543118_00543118, &recomp_gen::fn_sub_543118_00543118__recomp},
    {"sub_543130", 0x543130, &recomp_gen::fn_sub_543130_00543130, &recomp_gen::fn_sub_543130_00543130__recomp},
    {"sub_543148", 0x543148, &recomp_gen::fn_sub_543148_00543148, &recomp_gen::fn_sub_543148_00543148__recomp},
    {"sub_543178", 0x543178, &recomp_gen::fn_sub_543178_00543178, &recomp_gen::fn_sub_543178_00543178__recomp},
    {"sub_5431A8", 0x5431A8, &recomp_gen::fn_sub_5431A8_005431a8, &recomp_gen::fn_sub_5431A8_005431a8__recomp},
    {"sub_5431D8", 0x5431D8, &recomp_gen::fn_sub_5431D8_005431d8, &recomp_gen::fn_sub_5431D8_005431d8__recomp},
    {"sub_5431F0", 0x5431F0, &recomp_gen::fn_sub_5431F0_005431f0, &recomp_gen::fn_sub_5431F0_005431f0__recomp},
    {"sub_543220", 0x543220, &recomp_gen::fn_sub_543220_00543220, &recomp_gen::fn_sub_543220_00543220__recomp},
    {"sub_543238", 0x543238, &recomp_gen::fn_sub_543238_00543238, &recomp_gen::fn_sub_543238_00543238__recomp},
    {"sub_543268", 0x543268, &recomp_gen::fn_sub_543268_00543268, &recomp_gen::fn_sub_543268_00543268__recomp},
    {"sub_5432C0", 0x5432C0, &recomp_gen::fn_sub_5432C0_005432c0, &recomp_gen::fn_sub_5432C0_005432c0__recomp},
    {"sub_5433A8", 0x5433A8, &recomp_gen::fn_sub_5433A8_005433a8, &recomp_gen::fn_sub_5433A8_005433a8__recomp},
    {"sub_547BC0", 0x547BC0, &recomp_gen::fn_sub_547BC0_00547bc0, &recomp_gen::fn_sub_547BC0_00547bc0__recomp},
    {"sub_547C18", 0x547C18, &recomp_gen::fn_sub_547C18_00547c18, &recomp_gen::fn_sub_547C18_00547c18__recomp},
    {"sub_547FD0", 0x547FD0, &recomp_gen::fn_sub_547FD0_00547fd0, &recomp_gen::fn_sub_547FD0_00547fd0__recomp},
    {"sub_547FF8", 0x547FF8, &recomp_gen::fn_sub_547FF8_00547ff8, &recomp_gen::fn_sub_547FF8_00547ff8__recomp},
    {"sub_548020", 0x548020, &recomp_gen::fn_sub_548020_00548020, &recomp_gen::fn_sub_548020_00548020__recomp},
    {"sub_548048", 0x548048, &recomp_gen::fn_sub_548048_00548048, &recomp_gen::fn_sub_548048_00548048__recomp},
    {"sub_548078", 0x548078, &recomp_gen::fn_sub_548078_00548078, &recomp_gen::fn_sub_548078_00548078__recomp},
    {"sub_548318", 0x548318, &recomp_gen::fn_sub_548318_00548318, &recomp_gen::fn_sub_548318_00548318__recomp},
    {"sub_548410", 0x548410, &recomp_gen::fn_sub_548410_00548410, &recomp_gen::fn_sub_548410_00548410__recomp},
    {"sub_5484E0", 0x5484E0, &recomp_gen::fn_sub_5484E0_005484e0, &recomp_gen::fn_sub_5484E0_005484e0__recomp},
    {"sub_548520", 0x548520, &recomp_gen::fn_sub_548520_00548520, &recomp_gen::fn_sub_548520_00548520__recomp},
    {"sub_5485D8", 0x5485D8, &recomp_gen::fn_sub_5485D8_005485d8, &recomp_gen::fn_sub_5485D8_005485d8__recomp},
    {"sub_548678", 0x548678, &recomp_gen::fn_sub_548678_00548678, &recomp_gen::fn_sub_548678_00548678__recomp},
    {"sub_5486A8", 0x5486A8, &recomp_gen::fn_sub_5486A8_005486a8, &recomp_gen::fn_sub_5486A8_005486a8__recomp},
    {"sub_548768", 0x548768, &recomp_gen::fn_sub_548768_00548768, &recomp_gen::fn_sub_548768_00548768__recomp},
    {"sub_5487A0", 0x5487A0, &recomp_gen::fn_sub_5487A0_005487a0, &recomp_gen::fn_sub_5487A0_005487a0__recomp},
    {"sub_5489A0", 0x5489A0, &recomp_gen::fn_sub_5489A0_005489a0, &recomp_gen::fn_sub_5489A0_005489a0__recomp},
    {"sub_548AE8", 0x548AE8, &recomp_gen::fn_sub_548AE8_00548ae8, &recomp_gen::fn_sub_548AE8_00548ae8__recomp},
    {"sub_548EB8", 0x548EB8, &recomp_gen::fn_sub_548EB8_00548eb8, &recomp_gen::fn_sub_548EB8_00548eb8__recomp},
    {"sub_548EF0", 0x548EF0, &recomp_gen::fn_sub_548EF0_00548ef0, &recomp_gen::fn_sub_548EF0_00548ef0__recomp},
    {"sub_548F40", 0x548F40, &recomp_gen::fn_sub_548F40_00548f40, &recomp_gen::fn_sub_548F40_00548f40__recomp},
    {"sub_548F78", 0x548F78, &recomp_gen::fn_sub_548F78_00548f78, &recomp_gen::fn_sub_548F78_00548f78__recomp},
    {"sub_5491B0", 0x5491B0, &recomp_gen::fn_sub_5491B0_005491b0, &recomp_gen::fn_sub_5491B0_005491b0__recomp},
    {"sub_549480", 0x549480, &recomp_gen::fn_sub_549480_00549480, &recomp_gen::fn_sub_549480_00549480__recomp},
    {"sub_5494C0", 0x5494C0, &recomp_gen::fn_sub_5494C0_005494c0, &recomp_gen::fn_sub_5494C0_005494c0__recomp},
    {"sub_5497A0", 0x5497A0, &recomp_gen::fn_sub_5497A0_005497a0, &recomp_gen::fn_sub_5497A0_005497a0__recomp},
    {"sub_5497B0", 0x5497B0, &recomp_gen::fn_sub_5497B0_005497b0, &recomp_gen::fn_sub_5497B0_005497b0__recomp},
    {"sub_5497E0", 0x5497E0, &recomp_gen::fn_sub_5497E0_005497e0, &recomp_gen::fn_sub_5497E0_005497e0__recomp},
    {"sub_5497F8", 0x5497F8, &recomp_gen::fn_sub_5497F8_005497f8, &recomp_gen::fn_sub_5497F8_005497f8__recomp},
    {"sub_549838", 0x549838, &recomp_gen::fn_sub_549838_00549838, &recomp_gen::fn_sub_549838_00549838__recomp},
    {"sub_549BB0", 0x549BB0, &recomp_gen::fn_sub_549BB0_00549bb0, &recomp_gen::fn_sub_549BB0_00549bb0__recomp},
    {"sub_549DE8", 0x549DE8, &recomp_gen::fn_sub_549DE8_00549de8, &recomp_gen::fn_sub_549DE8_00549de8__recomp},
    {"sub_549E28", 0x549E28, &recomp_gen::fn_sub_549E28_00549e28, &recomp_gen::fn_sub_549E28_00549e28__recomp},
    {"sub_549EA0", 0x549EA0, &recomp_gen::fn_sub_549EA0_00549ea0, &recomp_gen::fn_sub_549EA0_00549ea0__recomp},
    {"sub_549EC8", 0x549EC8, &recomp_gen::fn_sub_549EC8_00549ec8, &recomp_gen::fn_sub_549EC8_00549ec8__recomp},
    {"sub_549FF8", 0x549FF8, &recomp_gen::fn_sub_549FF8_00549ff8, &recomp_gen::fn_sub_549FF8_00549ff8__recomp},
    {"sub_54A030", 0x54A030, &recomp_gen::fn_sub_54A030_0054a030, &recomp_gen::fn_sub_54A030_0054a030__recomp},
    {"sub_54A138", 0x54A138, &recomp_gen::fn_sub_54A138_0054a138, &recomp_gen::fn_sub_54A138_0054a138__recomp},
    {"sub_54A178", 0x54A178, &recomp_gen::fn_sub_54A178_0054a178, &recomp_gen::fn_sub_54A178_0054a178__recomp},
    {"sub_54A3C0", 0x54A3C0, &recomp_gen::fn_sub_54A3C0_0054a3c0, &recomp_gen::fn_sub_54A3C0_0054a3c0__recomp},
    {"get_bufs_2", 0x54A400, &recomp_gen::fn_get_bufs_2_0054a400, &recomp_gen::fn_get_bufs_2_0054a400__recomp},
    {"sub_54A530", 0x54A530, &recomp_gen::fn_sub_54A530_0054a530, &recomp_gen::fn_sub_54A530_0054a530__recomp},
    {"sub_54A568", 0x54A568, &recomp_gen::fn_sub_54A568_0054a568, &recomp_gen::fn_sub_54A568_0054a568__recomp},
    {"__env_unlock_0", 0x54A638, &recomp_gen::fn___env_unlock_0_0054a638, &recomp_gen::fn___env_unlock_0_0054a638__recomp},
    {"sub_54A968", 0x54A968, &recomp_gen::fn_sub_54A968_0054a968, &recomp_gen::fn_sub_54A968_0054a968__recomp},
    {"sub_54B088", 0x54B088, &recomp_gen::fn_sub_54B088_0054b088, &recomp_gen::fn_sub_54B088_0054b088__recomp},
    {"sub_54B0D8", 0x54B0D8, &recomp_gen::fn_sub_54B0D8_0054b0d8, &recomp_gen::fn_sub_54B0D8_0054b0d8__recomp},
    {"sub_54B230", 0x54B230, &recomp_gen::fn_sub_54B230_0054b230, &recomp_gen::fn_sub_54B230_0054b230__recomp},
    {"sub_54B2E8", 0x54B2E8, &recomp_gen::fn_sub_54B2E8_0054b2e8, &recomp_gen::fn_sub_54B2E8_0054b2e8__recomp},
    {"sub_54B328", 0x54B328, &recomp_gen::fn_sub_54B328_0054b328, &recomp_gen::fn_sub_54B328_0054b328__recomp},
    {"sub_54B4D0", 0x54B4D0, &recomp_gen::fn_sub_54B4D0_0054b4d0, &recomp_gen::fn_sub_54B4D0_0054b4d0__recomp},
    {"sub_54B520", 0x54B520, &recomp_gen::fn_sub_54B520_0054b520, &recomp_gen::fn_sub_54B520_0054b520__recomp},
    {"sub_54B690", 0x54B690, &recomp_gen::fn_sub_54B690_0054b690, &recomp_gen::fn_sub_54B690_0054b690__recomp},
    {"sub_54B988", 0x54B988, &recomp_gen::fn_sub_54B988_0054b988, &recomp_gen::fn_sub_54B988_0054b988__recomp},
    {"sub_54B9F0", 0x54B9F0, &recomp_gen::fn_sub_54B9F0_0054b9f0, &recomp_gen::fn_sub_54B9F0_0054b9f0__recomp},
    {"sub_54BCD8", 0x54BCD8, &recomp_gen::fn_sub_54BCD8_0054bcd8, &recomp_gen::fn_sub_54BCD8_0054bcd8__recomp},
    {"sub_54C100", 0x54C100, &recomp_gen::fn_sub_54C100_0054c100, &recomp_gen::fn_sub_54C100_0054c100__recomp},
    {"sub_54C288", 0x54C288, &recomp_gen::fn_sub_54C288_0054c288, &recomp_gen::fn_sub_54C288_0054c288__recomp},
    {"sub_54C370", 0x54C370, &recomp_gen::fn_sub_54C370_0054c370, &recomp_gen::fn_sub_54C370_0054c370__recomp},
    {"sub_54C578", 0x54C578, &recomp_gen::fn_sub_54C578_0054c578, &recomp_gen::fn_sub_54C578_0054c578__recomp},
    {"sub_54C8C0", 0x54C8C0, &recomp_gen::fn_sub_54C8C0_0054c8c0, &recomp_gen::fn_sub_54C8C0_0054c8c0__recomp},
    {"sub_54C940", 0x54C940, &recomp_gen::fn_sub_54C940_0054c940, &recomp_gen::fn_sub_54C940_0054c940__recomp},
    {"sub_54C9D8", 0x54C9D8, &recomp_gen::fn_sub_54C9D8_0054c9d8, &recomp_gen::fn_sub_54C9D8_0054c9d8__recomp},
    {"sub_54CA08", 0x54CA08, &recomp_gen::fn_sub_54CA08_0054ca08, &recomp_gen::fn_sub_54CA08_0054ca08__recomp},
    {"sub_539818", 0x539818, &recomp_gen::fn_sub_539818_00539818, &recomp_gen::fn_sub_539818_00539818__recomp},
    {"sub_539830", 0x539830, &recomp_gen::fn_sub_539830_00539830, &recomp_gen::fn_sub_539830_00539830__recomp},
    {"cvFsAddDev", 0x555B10, &recomp_gen::fn_cvFsAddDev_00555b10, &recomp_gen::fn_cvFsAddDev_00555b10__recomp},
    {"cvfs_addDevice", 0x555BA0, &recomp_gen::fn_cvfs_addDevice_00555ba0, &recomp_gen::fn_cvfs_addDevice_00555ba0__recomp},
    {"cvfs_getDevice", 0x555C78, &recomp_gen::fn_cvfs_getDevice_00555c78, &recomp_gen::fn_cvfs_getDevice_00555c78__recomp},
    {"sub_555D70", 0x555D70, &recomp_gen::fn_sub_555D70_00555d70, &recomp_gen::fn_sub_555D70_00555d70__recomp},
    {"sub_555E48", 0x555E48, &recomp_gen::fn_sub_555E48_00555e48, &recomp_gen::fn_sub_555E48_00555e48__recomp},
    {"sub_555F10", 0x555F10, &recomp_gen::fn_sub_555F10_00555f10, &recomp_gen::fn_sub_555F10_00555f10__recomp},
    {"cvfs_variousProc", 0x555FA0, &recomp_gen::fn_cvfs_variousProc_00555fa0, &recomp_gen::fn_cvfs_variousProc_00555fa0__recomp},
    {"cvFsOpen", 0x556048, &recomp_gen::fn_cvFsOpen_00556048, &recomp_gen::fn_cvFsOpen_00556048__recomp},
    {"sub_556170", 0x556170, &recomp_gen::fn_sub_556170_00556170, &recomp_gen::fn_sub_556170_00556170__recomp},
    {"sub_5561D8", 0x5561D8, &recomp_gen::fn_sub_5561D8_005561d8, &recomp_gen::fn_sub_5561D8_005561d8__recomp},
    {"cvFsClose", 0x556398, &recomp_gen::fn_cvFsClose_00556398, &recomp_gen::fn_cvFsClose_00556398__recomp},
    {"cvFsTell", 0x556410, &recomp_gen::fn_cvFsTell_00556410, &recomp_gen::fn_cvFsTell_00556410__recomp},
    {"cvFsSeek", 0x556478, &recomp_gen::fn_cvFsSeek_00556478, &recomp_gen::fn_cvFsSeek_00556478__recomp},
    {"cvFsReqRd", 0x5564E0, &recomp_gen::fn_cvFsReqRd_005564e0, &recomp_gen::fn_cvFsReqRd_005564e0__recomp},
    {"sub_556548", 0x556548, &recomp_gen::fn_sub_556548_00556548, &recomp_gen::fn_sub_556548_00556548__recomp},
    {"sub_5565B0", 0x5565B0, &recomp_gen::fn_sub_5565B0_005565b0, &recomp_gen::fn_sub_5565B0_005565b0__recomp},
    {"cvFsExecServer", 0x556608, &recomp_gen::fn_cvFsExecServer_00556608, &recomp_gen::fn_cvFsExecServer_00556608__recomp},
    {"cvFsGetStat", 0x556668, &recomp_gen::fn_cvFsGetStat_00556668, &recomp_gen::fn_cvFsGetStat_00556668__recomp},
    {"cvFsGetFileSize", 0x5566D0, &recomp_gen::fn_cvFsGetFileSize_005566d0, &recomp_gen::fn_cvFsGetFileSize_005566d0__recomp},
    {"sub_556790", 0x556790, &recomp_gen::fn_sub_556790_00556790, &recomp_gen::fn_sub_556790_00556790__recomp},
    {"sub_556860", 0x556860, &recomp_gen::fn_sub_556860_00556860, &recomp_gen::fn_sub_556860_00556860__recomp},
    {"sub_5568C0", 0x5568C0, &recomp_gen::fn_sub_5568C0_005568c0, &recomp_gen::fn_sub_5568C0_005568c0__recomp},
    {"sub_556A00", 0x556A00, &recomp_gen::fn_sub_556A00_00556a00, &recomp_gen::fn_sub_556A00_00556a00__recomp},
    {"sub_556A68", 0x556A68, &recomp_gen::fn_sub_556A68_00556a68, &recomp_gen::fn_sub_556A68_00556a68__recomp},
    {"sub_556AC0", 0x556AC0, &recomp_gen::fn_sub_556AC0_00556ac0, &recomp_gen::fn_sub_556AC0_00556ac0__recomp},
    {"sub_556B28", 0x556B28, &recomp_gen::fn_sub_556B28_00556b28, &recomp_gen::fn_sub_556B28_00556b28__recomp},
    {"sub_556BE8", 0x556BE8, &recomp_gen::fn_sub_556BE8_00556be8, &recomp_gen::fn_sub_556BE8_00556be8__recomp},
    {"sub_556C90", 0x556C90, &recomp_gen::fn_sub_556C90_00556c90, &recomp_gen::fn_sub_556C90_00556c90__recomp},
    {"sub_556DA0", 0x556DA0, &recomp_gen::fn_sub_556DA0_00556da0, &recomp_gen::fn_sub_556DA0_00556da0__recomp},
    {"sub_556E78", 0x556E78, &recomp_gen::fn_sub_556E78_00556e78, &recomp_gen::fn_sub_556E78_00556e78__recomp},
    {"sub_556ED0", 0x556ED0, &recomp_gen::fn_sub_556ED0_00556ed0, &recomp_gen::fn_sub_556ED0_00556ed0__recomp},
    {"sub_556F90", 0x556F90, &recomp_gen::fn_sub_556F90_00556f90, &recomp_gen::fn_sub_556F90_00556f90__recomp},
    {"sub_557050", 0x557050, &recomp_gen::fn_sub_557050_00557050, &recomp_gen::fn_sub_557050_00557050__recomp},
    {"sub_557110", 0x557110, &recomp_gen::fn_sub_557110_00557110, &recomp_gen::fn_sub_557110_00557110__recomp},
    {"sub_557198", 0x557198, &recomp_gen::fn_sub_557198_00557198, &recomp_gen::fn_sub_557198_00557198__recomp},
    {"sub_5571C0", 0x5571C0, &recomp_gen::fn_sub_5571C0_005571c0, &recomp_gen::fn_sub_5571C0_005571c0__recomp},
    {"sub_557228", 0x557228, &recomp_gen::fn_sub_557228_00557228, &recomp_gen::fn_sub_557228_00557228__recomp},
    {"cvFsSetCurVolume", 0x557290, &recomp_gen::fn_cvFsSetCurVolume_00557290, &recomp_gen::fn_cvFsSetCurVolume_00557290__recomp},
    {"sub_557350", 0x557350, &recomp_gen::fn_sub_557350_00557350, &recomp_gen::fn_sub_557350_00557350__recomp},
    {"cvFsAddVolumeEx", 0x557358, &recomp_gen::fn_cvFsAddVolumeEx_00557358, &recomp_gen::fn_cvFsAddVolumeEx_00557358__recomp},
    {"sub_557460", 0x557460, &recomp_gen::fn_sub_557460_00557460, &recomp_gen::fn_sub_557460_00557460__recomp},
    {"sub_557520", 0x557520, &recomp_gen::fn_sub_557520_00557520, &recomp_gen::fn_sub_557520_00557520__recomp},
    {"cvFsSetDefVol", 0x5575F0, &recomp_gen::fn_cvFsSetDefVol_005575f0, &recomp_gen::fn_cvFsSetDefVol_005575f0__recomp},
    {"cvfs_isNeedDevName", 0x5576B0, &recomp_gen::fn_cvfs_isNeedDevName_005576b0, &recomp_gen::fn_cvfs_isNeedDevName_005576b0__recomp},
    {"cvfs_addDevName", 0x557700, &recomp_gen::fn_cvfs_addDevName_00557700, &recomp_gen::fn_cvfs_addDevName_00557700__recomp},
    {"sub_557798", 0x557798, &recomp_gen::fn_sub_557798_00557798, &recomp_gen::fn_sub_557798_00557798__recomp},
    {"sub_5577B8", 0x5577B8, &recomp_gen::fn_sub_5577B8_005577b8, &recomp_gen::fn_sub_5577B8_005577b8__recomp},
    {"sub_557850", 0x557850, &recomp_gen::fn_sub_557850_00557850, &recomp_gen::fn_sub_557850_00557850__recomp},
    {"sub_557908", 0x557908, &recomp_gen::fn_sub_557908_00557908, &recomp_gen::fn_sub_557908_00557908__recomp},
    {"sub_5579C8", 0x5579C8, &recomp_gen::fn_sub_5579C8_005579c8, &recomp_gen::fn_sub_5579C8_005579c8__recomp},
    {"sub_557A28", 0x557A28, &recomp_gen::fn_sub_557A28_00557a28, &recomp_gen::fn_sub_557A28_00557a28__recomp},
    {"_getAllRefs", 0x4FB168, &recomp_gen::fn__getAllRefs_004fb168, &recomp_gen::fn__getAllRefs_004fb168__recomp},
    {"_getRef0", 0x4FBAC0, &recomp_gen::fn__getRef0_004fbac0, &recomp_gen::fn__getRef0_004fbac0__recomp},
    {"_skipMB0", 0x4FD8A8, &recomp_gen::fn__skipMB0_004fd8a8, &recomp_gen::fn__skipMB0_004fd8a8__recomp},
    {"_copyAddRefImage", 0x4FD968, &recomp_gen::fn__copyAddRefImage_004fd968, &recomp_gen::fn__copyAddRefImage_004fd968__recomp},
    {"_rix_000", 0x4FDC98, &recomp_gen::fn__rix_000_004fdc98, &recomp_gen::fn__rix_000_004fdc98__recomp},
    {"_ri0_000", 0x4FDD10, &recomp_gen::fn__ri0_000_004fdd10, &recomp_gen::fn__ri0_000_004fdd10__recomp},
    {"_rix_001", 0x4FDDA8, &recomp_gen::fn__rix_001_004fdda8, &recomp_gen::fn__rix_001_004fdda8__recomp},
    {"_ri0_001", 0x4FDE60, &recomp_gen::fn__ri0_001_004fde60, &recomp_gen::fn__ri0_001_004fde60__recomp},
    {"_rix_010", 0x4FDF30, &recomp_gen::fn__rix_010_004fdf30, &recomp_gen::fn__rix_010_004fdf30__recomp},
    {"_ri0_010", 0x4FDFE0, &recomp_gen::fn__ri0_010_004fdfe0, &recomp_gen::fn__ri0_010_004fdfe0__recomp},
    {"_rix_011", 0x4FE098, &recomp_gen::fn__rix_011_004fe098, &recomp_gen::fn__rix_011_004fe098__recomp},
    {"_ri0_011", 0x4FE190, &recomp_gen::fn__ri0_011_004fe190, &recomp_gen::fn__ri0_011_004fe190__recomp},
    {"_rix_100", 0x4FE290, &recomp_gen::fn__rix_100_004fe290, &recomp_gen::fn__rix_100_004fe290__recomp},
    {"_ri0_100", 0x4FE330, &recomp_gen::fn__ri0_100_004fe330, &recomp_gen::fn__ri0_100_004fe330__recomp},
    {"_rix_101", 0x4FE3E0, &recomp_gen::fn__rix_101_004fe3e0, &recomp_gen::fn__rix_101_004fe3e0__recomp},
    {"_ri0_101", 0x4FE4C0, &recomp_gen::fn__ri0_101_004fe4c0, &recomp_gen::fn__ri0_101_004fe4c0__recomp},
    {"_rix_110", 0x4FE5A8, &recomp_gen::fn__rix_110_004fe5a8, &recomp_gen::fn__rix_110_004fe5a8__recomp},
    {"_ri0_110", 0x4FE680, &recomp_gen::fn__ri0_110_004fe680, &recomp_gen::fn__ri0_110_004fe680__recomp},
    {"_rix_111", 0x4FE750, &recomp_gen::fn__rix_111_004fe750, &recomp_gen::fn__rix_111_004fe750__recomp},
    {"_ri0_111", 0x4FE870, &recomp_gen::fn__ri0_111_004fe870, &recomp_gen::fn__ri0_111_004fe870__recomp},
    {"_initSeq", 0x4FEBC8, &recomp_gen::fn__initSeq_004febc8, &recomp_gen::fn__initSeq_004febc8__recomp},
    {"_groupOfPicturesHeader", 0x4FF190, &recomp_gen::fn__groupOfPicturesHeader_004ff190, &recomp_gen::fn__groupOfPicturesHeader_004ff190__recomp},
    {"_pictureHeader", 0x4FF230, &recomp_gen::fn__pictureHeader_004ff230, &recomp_gen::fn__pictureHeader_004ff230__recomp},
    {"_extensionAndUserData", 0x4FF7C8, &recomp_gen::fn__extensionAndUserData_004ff7c8, &recomp_gen::fn__extensionAndUserData_004ff7c8__recomp},
    {"flushBuf32", 0x4FFB30, &recomp_gen::fn_flushBuf32_004ffb30, &recomp_gen::fn_flushBuf32_004ffb30__recomp},
    {"_getpic", 0x500278, &recomp_gen::fn__getpic_00500278, &recomp_gen::fn__getpic_00500278__recomp},
    {"_updateRefImage", 0x500430, &recomp_gen::fn__updateRefImage_00500430, &recomp_gen::fn__updateRefImage_00500430__recomp},
    {"_decodeOrSkipFrame", 0x5006E8, &recomp_gen::fn__decodeOrSkipFrame_005006e8, &recomp_gen::fn__decodeOrSkipFrame_005006e8__recomp},
    {"_decodeOrSkip", 0x500E00, &recomp_gen::fn__decodeOrSkip_00500e00, &recomp_gen::fn__decodeOrSkip_00500e00__recomp},
    {"_decPicture", 0x500F98, &recomp_gen::fn__decPicture_00500f98, &recomp_gen::fn__decPicture_00500f98__recomp},
    {"_dispRefImage", 0x501408, &recomp_gen::fn__dispRefImage_00501408, &recomp_gen::fn__dispRefImage_00501408__recomp},
};

namespace c2 = p3fes::game::cri2;

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    std::fprintf(stderr, "test_cri2: no case 0x%X\n", addr);
    std::abort();
}

constexpr u32 kSeeds = 24;            // generic sweep: pairs per function (P3FES_HG_SEEDS overrides)
constexpr u32 kWorld = 0x01810000u;   // 64 KiB of free RAM above the harness's arena (the generic sweep's world)
constexpr u32 kWorldSize = 0x10000u;
// The meaningful sections' buffers (free RAM in the ELF image and in every replay snapshot: stand_ins.h's kScratch
// region and the area below it).
constexpr u32 kScratch = 0x01BC0000u; // 256 KiB
constexpr u32 kIface = kScratch + 0x0000u;   // a test device's interface table (26 words)
constexpr u32 kStr = kScratch + 0x0200u;     // strings
constexpr u32 kOut = kScratch + 0x0800u;     // out-parameters
constexpr u32 kRec = kScratch + 0x1000u;     // built records (decoder handles, ADXB records, MPEG state)
constexpr u32 kBuf = kScratch + 0x8000u;     // data buffers (up to 224 KiB)

std::map<std::string, int> g_pairs;  // pairs per function in the meaningful sections
u32 g_seed = 1;

u8 r8(Machine& m, u32 va) { return *m.at(va); }
s16 r16s(Machine& m, u32 va) { s16 v; std::memcpy(&v, m.at(va), 2); return v; }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
s32 r32s(Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
u64 r64(Machine& m, u32 va) { u64 v; std::memcpy(&v, m.at(va), 8); return v; }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
void fill(Machine& m, u32 va, const std::vector<u8>& b) { std::memcpy(m.at(va), b.data(), b.size()); }
std::string cstr(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va))); }
void put_str(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
u32 uv(u64 v) { return static_cast<u32>(v); }
u64 sx64(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }
u16 be16(const u8* p) { return static_cast<u16>((p[0] << 8) | p[1]); }
u32 be32(const u8* p) { return (static_cast<u32>(p[0]) << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; }

// guest memory from a stand-in
u32 glw(const EEContext& ctx, u32 va) { return ctx.memory->read<u32>(va); }
void gsw(EEContext& ctx, u32 va, u32 v) { ctx.memory->write<u32>(va, v); }
u8 glb(const EEContext& ctx, u32 va) { return ctx.memory->read<u8>(va); }
std::string gstr(const EEContext& ctx, u32 va) {
    std::string s;
    for (u32 a = va; s.size() < 255; ++a) {
        const char ch = static_cast<char>(ctx.memory->read<u8>(a));
        if (ch == 0) break;
        s += ch;
    }
    return s;
}

// One plain pair (no stand-ins): $a0..$a3 from `a`, $t0..$t3 from `t`, further arguments in the caller's stack slots.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, std::vector<u64> stk = {}) {
    const Case& c = by_addr(addr);
    for (std::size_t i = 0; i < stk.size(); ++i) w64(m, kSp + 8 * static_cast<u32>(i), stk[i]);
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    hgp::Run r = hgp::pair(m, c.hand, c.recomp, a, g_seed++, c.name, hw);
    INFO(std::string(c.name));
    CHECK_FALSE(r.stopped);
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, std::vector<u64> stk = {}) {
    return v0of(pr(m, addr, a, std::move(t), std::move(stk)));
}
std::map<unsigned, u64> tregs(u64 t0, u64 t1 = 0, u64 t2 = 0, u64 t3 = 0) {
    return {{GPR_T0, t0}, {GPR_T0 + 1, t1}, {GPR_T0 + 2, t2}, {GPR_T0 + 3, t3}};
}

// A pair on stand-ins: the whole register file at every check point, the dead stack, all of RAM, both call logs.
struct SiResult {
    u64 v0 = 0;
    std::vector<StandInCall> log;
    bool stopped = false;
};
SiResult pr_si(Machine& m, u32 addr, Args a, const WorldSetup& setup, std::map<unsigned, u64> t = {},
               std::vector<u64> stk = {}) {
    const Case& c = by_addr(addr);
    for (std::size_t i = 0; i < stk.size(); ++i) w64(m, kSp + 8 * static_cast<u32>(i), stk[i]);
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.ranges.push_back({0, EEMemory::kMainRamSize});
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    SiPair p = run_pair_si(m, c.hand, c.recomp, a, g_seed++, c.name, hw, setup);
    SiResult r;
    r.v0 = p.hw.recomp.base.v0;
    if (p.recomp) r.log = p.recomp->si.log;
    return r;
}
std::vector<StandInCall> calls_to(const std::vector<StandInCall>& log, u32 va) {
    std::vector<StandInCall> out;
    for (const StandInCall& c : log)
        if (c.va == va) out.push_back(c);
    return out;
}

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}
std::unique_ptr<Machine> snapshot_machine(const char* dir) {
    auto m = machine();
    if (!m) return nullptr;
    const std::vector<u8> snap = read_snapshot(dir);
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot " << dir << " not found");
        return nullptr;
    }
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    return m;
}

std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream f(p, std::ios::binary);
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}
// files of extracted/ with an extension (upper-cased compare), sorted; never under _ours
std::vector<std::filesystem::path> disc_files(const char* ext_upper) {
    std::vector<std::filesystem::path> out;
    const std::filesystem::path root = extracted_root();
    std::error_code ec;
    if (!std::filesystem::is_directory(root, ec)) return out;
    for (auto it = std::filesystem::recursive_directory_iterator(root, ec); it != std::filesystem::recursive_directory_iterator();
         it.increment(ec)) {
        if (ec) break;
        if (!it->is_regular_file(ec)) continue;
        std::string ext = it->path().extension().string();
        for (char& ch : ext) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        if (ext == ext_upper && it->path().string().find("_ours") == std::string::npos) out.push_back(it->path());
    }
    std::sort(out.begin(), out.end());
    return out;
}

// The SVM lock / unlock callbacks the ADX setup installs (0x99A0A0 / 0x99A0A8) and the error callbacks: recorders.
constexpr u32 kSvmLockCb = 0x53F8B8u, kSvmUnlockCb = 0x53F940u;
// the SVM error callback of a snapshot (the game's printing handler, hand-written: it cannot be stood in) is replaced by a
// recorder at a function this binary does not emit (cri1's choice); the ADXT loop trap 0x54B748 (not taken) a recorder
constexpr u32 kSvmErrCb = 0x55E978u, kLoopTrap = 0x54B748u;
void install_svm(StandInWorld& w) {
    w.si.install_recorder(kSvmLockCb, "svm_lock_cb", 0, 4);
    w.si.install_recorder(kSvmUnlockCb, "svm_unlock_cb", 0, 4);
    w.si.install(kSvmErrCb, "svm_err_cb", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, uv(c.args[1])); }, 4);
    w.si.install_recorder(kLoopTrap, "adxt_LoopTrap", 0, 4);
}
void prep_snapshot_adx(Machine& m) {
    w32(m, p3fes::game::cri1::svm::kErrFn, kSvmErrCb);
    w32(m, p3fes::game::cri1::svm::kErrFn + 4, 0);
}

// newlib strncmp (0x524670: not emitted in this binary; test_models stands it in too): the real semantics on guest bytes.
constexpr u32 kStrncmp = 0x524670u;
void install_strncmp(StandInWorld& w) {
    w.si.install(kStrncmp, "strncmp", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 a = uv(c.args[0]), b = uv(c.args[1]);
        const u32 n = uv(c.args[2]);
        s32 r = 0;
        for (u32 i = 0; i < n; ++i) {
            const u8 x = glb(ctx, a + i), y = glb(ctx, b + i);
            if (x != y) {
                r = static_cast<s32>(x) - static_cast<s32>(y);
                break;
            }
            if (x == 0) break;
        }
        c.v0 = sx64(r);
    }, 6);
}

}  // namespace

// =====================================================================================================================
// The generic sweep: every body against its recompiled body on random worlds
// =====================================================================================================================
TEST_CASE("game(cri2): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (u64& a : args) a = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("generic sweep: " << pairs << " pairs, " << stops << " stopped early (identically)");
}

// =====================================================================================================================
// cvFs: a test device registered through cvFsAddDev; every request dispatched through its interface table
// =====================================================================================================================
namespace {
namespace cv = c2::cvfs;
// The test device's interface: one recorder per entry, at functions this binary does not emit (the CDV / HTCI devices).
constexpr std::array<u32, 26> kIfFns = {0x55A050u, 0x55A0D8u, 0x55A198u, 0x55A1D0u, 0x55A1F0u, 0x55A368u, 0x55A3C0u,
                                        0x55A458u, 0x55A490u, 0x55A638u, 0x55A720u, 0x55A758u, 0x55A760u, 0x55A7C0u,
                                        0x55A800u, 0x55A898u, 0x55A8A8u, 0x55A8C8u, 0x55A8D0u, 0x55A8E8u, 0x55A9B0u,
                                        0x55AA58u, 0x55AA90u, 0x55AAE8u, 0x55AB80u, 0x55AD18u};
constexpr u32 kGetter = 0x55AEA0u;    // the device's interface getter (cvFsAddDev's second argument)
constexpr u32 kErrCb = 0x55B030u;     // the cvFs error callback (sub_557198 installs it)
constexpr u32 kSprintfVa = 0x523AC8u;
constexpr u32 kErxEntries5 = 0x555F90u;  // sceLibgcc32GetErxEntries_5: the default-device getter (an sce* name: not taken)
constexpr u32 kFileId = 0x5A5A0001u;  // what the test device's Open returns
u32 if_fn(s32 entry) { return kIfFns[static_cast<std::size_t>(entry / 4)]; }
// the entry's recorder result: distinct per entry; OptFn1 answers per code (the 64-bit pairs, "need device name")
u64 if_result(s32 entry) { return 0x1000u + static_cast<u32>(entry); }

struct CvWorld {
    bool need_dev_name = false;  // OptFn1 code 100
    bool open_fails = false;
};
WorldSetup cv_world(CvWorld o = {}) {
    return [o](StandInWorld& w) {
        install_sprintf(w.si);
        install_strncmp(w);
        w.si.install_recorder(kGetter, "if_getter", kIface, 2);
        w.si.install_recorder(kErrCb, "cvfs_err_cb", 0, 2);
        w.si.install(kErxEntries5, "cvfs_getDefDevName", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c2::cvfs::kDefDev; }, 2);
        for (s32 e = 0; e < 26 * 4; e += 4) {
            if (e == cv::kIfOpen) {
                w.si.install(if_fn(e), "if_open", [o](EEContext& ctx, StandIns&, StandInCall& c) {
                    c.text = gstr(ctx, uv(c.args[0]));
                    c.v0 = o.open_fails ? 0 : kFileId;
                }, 3);
            } else if (e == cv::kIfOptFn1) {
                w.si.install(if_fn(e), "if_optfn1", [o](EEContext& ctx, StandIns&, StandInCall& c) {
                    const s32 code = sv(c.args[1]);
                    // the request block of the volume codes (5 words on the caller's stack)
                    if (code >= 1 && code <= 6) {
                        char t[96];
                        const u32 b = uv(c.args[0]);
                        std::snprintf(t, sizeof t, "%08X %08X %08X %08X %08X", glw(ctx, b), glw(ctx, b + 4), glw(ctx, b + 8),
                                      glw(ctx, b + 12), glw(ctx, b + 16));
                        c.text = t;
                    }
                    if (code == 100) c.v0 = o.need_dev_name ? 1 : 0;
                    else if (code >= 200 && code <= 205) c.v0 = (code & 1) ? 0x89ABCDEFu : 0x12u + static_cast<u32>(code - 200);
                    else c.v0 = 0x700u + static_cast<u32>(code);
                }, 3);
            } else {
                // a recorder that also keeps the text its first argument points at (the name requests pass the
                // split file name in a stack buffer of the caller: gone once the pair returns)
                w.si.install(if_fn(e), "if_" + std::to_string(e), [e](EEContext& ctx, StandIns&, StandInCall& c) {
                    const u32 p = uv(c.args[0]);
                    if (p >= 0x100000u && p < 0x2000000u) c.text = gstr(ctx, p);
                    c.v0 = if_result(e);
                }, 3);
            }
        }
    };
}
void build_iface(Machine& m, std::initializer_list<s32> missing = {}) {
    for (s32 e = 0; e < 26 * 4; e += 4) w32(m, kIface + static_cast<u32>(e), if_fn(e));
    for (s32 e : missing) w32(m, kIface + static_cast<u32>(e), 0);
}
// the error texts the cvFs layer reported (through sub_555918 -> the callback: (object, message))
std::vector<std::string> cv_errors(Machine& m, const std::vector<StandInCall>& log) {
    std::vector<std::string> out;
    for (const StandInCall& c : calls_to(log, kErrCb)) out.push_back(cstr(m, uv(c.args[1])));
    return out;
}
}  // namespace

TEST_CASE("game(cri2): cvFs device registration and lookup (a test device, the strncmp prefix rule)") {
    auto m = machine();
    if (!m) return;
    zero(*m, cv::kDevices, cv::kDeviceCount * cv::kDeviceSize);
    zero(*m, cv::kHandles, cv::kHandleCount * 8);
    zero(*m, cv::kDefDev, 9);
    build_iface(*m);
    const WorldSetup world = cv_world();
    // the error callback (cvFsEntryErrFunc): object 0x77
    pr_si(*m, 0x557198, {kErrCb, 0x77, 0, 0}, world);
    CHECK(r32(*m, cv::kErrFn) == kErrCb);
    CHECK(r32(*m, cv::kErrFn + 4) == 0x77);
    // register "tst": the name is upper-cased in place, slot 0 takes {interface, "TST"}, the device gets the layer's
    // error callback (0x5558E8, 0) through its EntryErrFn
    put_str(*m, kStr, "tst");
    SiResult r = pr_si(*m, 0x555B10, {kStr, kGetter, 0, 0}, world);
    CHECK(r32(*m, cv::kDevices) == kIface);
    CHECK(cstr(*m, cv::kDevices + 4) == "TST");
    CHECK(cstr(*m, kStr) == "TST");
    REQUIRE(calls_to(r.log, kGetter).size() == 1);
    const auto ef = calls_to(r.log, if_fn(cv::kIfEntryErrFn));
    REQUIRE(ef.size() == 1);
    CHECK(uv(ef[0].args[0]) == 0x5558E8u);
    CHECK(ef[0].args[1] == 0);
    // the same name again: found, not added twice (the getter still runs)
    r = pr_si(*m, 0x555B10, {kStr, kGetter, 0, 0}, world);
    CHECK(cstr(*m, cv::kDevices + 16 + 4).empty());
    // a second device
    put_str(*m, kStr + 16, "DVD");
    pr_si(*m, 0x555B10, {kStr + 16, kGetter, 0, 0}, world);
    CHECK(cstr(*m, cv::kDevices + 16 + 4) == "DVD");
    // the errors: no name, no getter
    r = pr_si(*m, 0x555B10, {0, kGetter, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsAddDev #1:illegal device name"});
    CHECK(calls_to(r.log, kErrCb)[0].args[0] == 0x77);
    r = pr_si(*m, 0x555B10, {kStr, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsAddDev #2:illegal I/F func name"});
    // lookups: strncmp over the 32 slots with the length of the name asked for -- a prefix matches
    const std::vector<std::pair<std::string, u32>> lookups = {{"TST", kIface}, {"TS", kIface}, {"T", kIface}, {"DVD", kIface},
                                                              {"TSTX", 0}, {"XYZ", 0}, {"tst", 0}};
    for (const auto& [name, want] : lookups) {
        put_str(*m, kStr + 64, name);
        INFO(name);
        CHECK(uv(pr_si(*m, 0x555C78, {kStr + 64, 0, 0, 0}, world).v0) == want);
        CHECK(uv(pr_si(*m, 0x557798, {kStr + 64, 0, 0, 0}, world).v0) == (want ? 1u : 0u));
        CHECK(uv(pr_si(*m, 0x555F10, {kStr + 64, name.size(), 0, 0}, world).v0) == (want ? 1u : 0u));
    }
    // the default device: upper-cased, must be registered; "" clears it
    put_str(*m, kStr + 64, "dvd");
    pr_si(*m, 0x555E48, {kStr + 64, 0, 0, 0}, world);
    CHECK(cstr(*m, cv::kDefDev) == "DVD");
    put_str(*m, kStr + 64, "NOPE");
    r = pr_si(*m, 0x555E48, {kStr + 64, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsSetDefDev #2:unknown device name"});
    CHECK(cstr(*m, cv::kDefDev) == "DVD");
    r = pr_si(*m, 0x555E48, {0, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsSetDefDev #1:illegal device name"});
    put_str(*m, kStr + 64, "");
    pr_si(*m, 0x555E48, {kStr + 64, 0, 0, 0}, world);
    CHECK(cstr(*m, cv::kDefDev).empty());
    // removing a device clears the first byte of its name; it is no longer found
    put_str(*m, kStr + 64, "DVD");
    pr_si(*m, 0x555D70, {kStr + 64, 0, 0, 0}, world);
    CHECK(r8(*m, cv::kDevices + 16 + 4) == 0);
    CHECK(uv(pr_si(*m, 0x555C78, {kStr + 64, 0, 0, 0}, world).v0) == 0);
    r = pr_si(*m, 0x555D70, {0, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsDelDev #1:illegal device name"});
    // the stubs
    CHECK(prv(*m, 0x557350, {1, 2, 3, 4}) == 0);
    std::memset(m->at(cv::kSrdObj), 0xAA, 64);
    pr(*m, 0x557A28, {0, 0, 0, 0});
    for (u32 i = 0; i < 56; ++i) CHECK(r8(*m, cv::kSrdObj + i) == 0);
    CHECK(r8(*m, cv::kSrdObj + 56) == 0xAA);
    MESSAGE("cvFs devices: " << summary());
}

TEST_CASE("game(cri2): cvFs requests through the device interface (open / handle / name / option requests)") {
    auto m = machine();
    if (!m) return;
    zero(*m, cv::kDevices, cv::kDeviceCount * cv::kDeviceSize);
    zero(*m, cv::kHandles, cv::kHandleCount * 8);
    zero(*m, cv::kDefDev, 9);
    build_iface(*m);
    WorldSetup world = cv_world();
    pr_si(*m, 0x557198, {kErrCb, 0x77, 0, 0}, world);
    put_str(*m, kStr, "TST");
    pr_si(*m, 0x555B10, {kStr, kGetter, 0, 0}, world);

    // open "TST:FILE.BIN": the device's Open gets the file part and the two arguments; the handle {interface, file}
    put_str(*m, kStr + 64, "TST:FILE.BIN");
    SiResult r = pr_si(*m, 0x556048, {kStr + 64, 1, 2, 0}, world);
    const u32 h = uv(r.v0);
    CHECK(h == cv::kHandles);
    auto op = calls_to(r.log, if_fn(cv::kIfOpen));
    REQUIRE(op.size() == 1);
    CHECK(op[0].text == "FILE.BIN");
    CHECK(op[0].args[1] == 1);
    CHECK(op[0].args[2] == 2);
    CHECK(r32(*m, h + cv::kHIf) == kIface);
    CHECK(r32(*m, h + cv::kHFile) == kFileId);
    // a second open takes the next handle
    const u32 h2 = uv(pr_si(*m, 0x556048, {kStr + 64, 1, 2, 0}, world).v0);
    CHECK(h2 == cv::kHandles + 8);

    // the handle requests: the entry, called with the handle's device file and the caller's other arguments
    struct HReq {
        u32 fn;
        s32 entry;
        const char* name;
    };
    const HReq hreqs[] = {{0x556410, cv::kIfTell, "cvFsTell"},         {0x556478, cv::kIfSeek, "cvFsSeek"},
                          {0x5564E0, cv::kIfReqRd, "cvFsReqRd"},       {0x556548, cv::kIfReqWr, "cvFsReqWr"},
                          {0x5565B0, cv::kIfStopTr, "cvFsStopTr"},     {0x556668, cv::kIfGetStat, "cvFsGetStat"},
                          {0x556A00, cv::kIfGetSctLen, "cvFsGetSctLen"}, {0x556A68, cv::kIfSetSctLen, "cvFsSetSctLen"},
                          {0x556AC0, cv::kIfGetNumTr, "cvFsGetNumTr"}, {0x556E78, cv::kIfGetMaxByteRate, "cvFsGetMaxByteRate"},
                          {0x5571C0, cv::kIfOptFn1, "cvFsOptFn1"},     {0x557228, cv::kIfOptFn2, "cvFsOptFn2"}};
    for (const HReq& q : hreqs) {
        INFO(q.name);
        r = pr_si(*m, q.fn, {h, 0x111, 0x222, 0x333}, world);
        const auto c = calls_to(r.log, if_fn(q.entry));
        REQUIRE(c.size() == 1);
        CHECK(uv(c[0].args[0]) == kFileId);
        CHECK(c[0].args[1] == 0x111);
        CHECK(c[0].args[2] == 0x222);
        if (q.entry != cv::kIfOptFn1) CHECK(uv(r.v0) == uv(if_result(q.entry)));
        // a null handle: reported, nothing called
        r = pr_si(*m, q.fn, {0, 0, 0, 0}, world);
        CHECK(calls_to(r.log, if_fn(q.entry)).empty());
        REQUIRE(cv_errors(*m, r.log).size() == 1);
        CHECK(cv_errors(*m, r.log)[0].find("#") != std::string::npos);
        if (q.fn == 0x556668) CHECK(uv(r.v0) == 3);  // cvFsGetStat: 3 (error) for a bad handle
    }
    // the option requests by handle: file size (300), file-system flag (299), the 64-bit transfer count (200 / 201)
    r = pr_si(*m, 0x556860, {h, 0, 0, 0}, world);
    REQUIRE(calls_to(r.log, if_fn(cv::kIfOptFn1)).size() == 1);
    CHECK(calls_to(r.log, if_fn(cv::kIfOptFn1))[0].args[1] == 300);
    CHECK(uv(r.v0) == 0x700u + 300u);
    r = pr_si(*m, 0x5579C8, {h, 0, 0, 0}, world);
    CHECK(calls_to(r.log, if_fn(cv::kIfOptFn1))[0].args[1] == 299);
    r = pr_si(*m, 0x5577B8, {h, 0, 0, 0}, world);
    const auto tr64 = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(tr64.size() == 2);
    CHECK(tr64[0].args[1] == 200);
    CHECK(tr64[1].args[1] == 201);
    CHECK(r.v0 == (u64{0x12} << 32) + 0x89ABCDEFull);  // hi << 32 plus the zero-extended low word
    // the device name of a handle
    CHECK(cstr(*m, uv(pr_si(*m, 0x557110, {h, 0, 0, 0}, world).v0)) == "TST");

    // the name requests: the entry gets the file part
    struct NReq {
        u32 fn;
        s32 entry;
        s32 fail;
        const char* name;
    };
    const NReq nreqs[] = {{0x5566D0, cv::kIfGetFileSize, 0, "cvFsGetFileSize"}, {0x556790, cv::kIfGetFileSizeEx, 0, "cvFsGetFileSizeEx"},
                          {0x556B28, cv::kIfChangeDir, -1, "cvFsChangeDir"},     {0x556BE8, cv::kIfIsExistFile, 0, "cvFsIsExistFile"},
                          {0x556ED0, cv::kIfMakeDir, -1, "cvFsMakeDir"},         {0x556F90, cv::kIfRemoveDir, -1, "cvFsRemoveDir"},
                          {0x557050, cv::kIfDeleteFile, -1, "cvFsDeleteFile"}};
    for (const NReq& q : nreqs) {
        INFO(q.name);
        put_str(*m, kStr + 64, "TST:DIR/A.BIN");
        r = pr_si(*m, q.fn, {kStr + 64, 0x444, 0, 0}, world);
        auto c = calls_to(r.log, if_fn(q.entry));
        REQUIRE(c.size() == 1);
        CHECK(c[0].text == "DIR/A.BIN");
        CHECK(uv(r.v0) == uv(if_result(q.entry)));
        // a missing entry: "#4:vtbl error" and the failure value
        build_iface(*m, {q.entry});
        r = pr_si(*m, q.fn, {kStr + 64, 0, 0, 0}, world);
        CHECK(calls_to(r.log, if_fn(q.entry)).empty());
        REQUIRE(cv_errors(*m, r.log).size() == 1);
        CHECK(cv_errors(*m, r.log)[0].find("#4:vtbl error") != std::string::npos);
        CHECK(sv(r.v0) == q.fail);
        build_iface(*m);
    }
    // a name without a device part and no default device: "#1" (illegal) for an empty name
    put_str(*m, kStr + 64, "");
    r = pr_si(*m, 0x5566D0, {kStr + 64, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsGetFileSize #1:illegal file name"});
    // an unknown device with the default device set: the default device gets the whole original name
    put_str(*m, kStr + 96, "TST");
    pr_si(*m, 0x555E48, {kStr + 96, 0, 0, 0}, world);
    put_str(*m, kStr + 64, "XXX:B.BIN");
    r = pr_si(*m, 0x5566D0, {kStr + 64, 0, 0, 0}, world);
    REQUIRE(calls_to(r.log, if_fn(cv::kIfGetFileSize)).size() == 1);
    CHECK(calls_to(r.log, if_fn(cv::kIfGetFileSize))[0].text == "XXX:B.BIN");
    // a name without a device part goes to the default device
    put_str(*m, kStr + 64, "C.BIN");
    r = pr_si(*m, 0x556048, {kStr + 64, 0, 0, 0}, world);
    op = calls_to(r.log, if_fn(cv::kIfOpen));
    REQUIRE(op.size() == 1);
    CHECK(op[0].text == "C.BIN");
    // a device that wants its name in paths (OptFn1 code 100 = 1): the path becomes "TST:C.BIN" (sprintf "%s:%s")
    world = cv_world({true, false});
    put_str(*m, kStr + 64, "TST:C.BIN");
    r = pr_si(*m, 0x556048, {kStr + 64, 0, 0, 0}, world);
    op = calls_to(r.log, if_fn(cv::kIfOpen));
    REQUIRE(op.size() == 1);
    CHECK(op[0].text == "TST:C.BIN");
    CHECK(calls_to(r.log, kSprintfVa).size() == 1);
    CHECK(sv(pr_si(*m, 0x5576B0, {kStr + 96, 0, 0, 0}, world).v0) == 1);
    // the open failure and the missing Open entry release the handle
    world = cv_world({false, true});
    put_str(*m, kStr + 64, "TST:D.BIN");
    r = pr_si(*m, 0x556048, {kStr + 64, 0, 0, 0}, world);
    CHECK(r.v0 == 0);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsOpen #6:open failed"});
    world = cv_world();
    build_iface(*m, {cv::kIfOpen});
    r = pr_si(*m, 0x556048, {kStr + 64, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsOpen #5:vtbl error"});
    build_iface(*m);
    r = pr_si(*m, 0x556048, {0, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsOpen #1:illegal file name"});
    // LoadDirInfo passes the caller's three arguments through
    put_str(*m, kStr + 64, "TST:E");
    r = pr_si(*m, 0x556DA0, {kStr + 64, 0x55, 0x66, 0}, world);
    REQUIRE(calls_to(r.log, if_fn(cv::kIfLoadDirInfo)).size() == 1);
    CHECK(uv(calls_to(r.log, if_fn(cv::kIfLoadDirInfo))[0].args[0]) == kStr + 64);
    CHECK(calls_to(r.log, if_fn(cv::kIfLoadDirInfo))[0].args[2] == 0x66);
    // the free size of a device, the number of files
    put_str(*m, kStr + 64, "TST");
    r = pr_si(*m, 0x5568C0, {kStr + 64, 0, 0, 0}, world);
    CHECK(calls_to(r.log, if_fn(cv::kIfGetFreeSize)).size() == 1);
    CHECK(uv(r.v0) == uv(if_result(cv::kIfGetFreeSize)));
    r = pr_si(*m, 0x556C90, {kStr + 64, 0, 0, 0}, world);
    CHECK(calls_to(r.log, if_fn(cv::kIfGetNumFiles)).size() == 1);
    // the volume requests: OptFn1 with the code and the 5-word request block
    put_str(*m, kStr + 128, "VOLNAME");
    char want[96];
    r = pr_si(*m, 0x557290, {kStr + 64, 0xABC, 0, 0}, world);
    auto o = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(o.size() == 1);
    CHECK(o[0].args[1] == cv::kOptSetCurVolume);
    CHECK(o[0].text == "00000ABC 00000000 00000000 00000000 00000000");
    r = pr_si(*m, 0x557358, {kStr + 64, kStr + 128, 0xABC, 7}, world);
    o = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(o.size() == 1);
    CHECK(o[0].args[1] == cv::kOptAddVolume);
    std::snprintf(want, sizeof want, "00000ABC %08X 00000007 00000000 00000000", kStr + 128);
    CHECK(o[0].text == want);
    r = pr_si(*m, 0x557460, {kStr + 64, kStr + 128, 0, 0}, world);
    o = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(o.size() == 1);
    CHECK(o[0].args[1] == cv::kOptDelVolume);
    r = pr_si(*m, 0x557520, {kStr + 64, kStr + 128, 9, 0}, world);
    o = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(o.size() == 1);
    CHECK(o[0].args[1] == cv::kOptGetVolumeInfo);
    std::snprintf(want, sizeof want, "00000000 %08X 00000009 00000000 00000000", kStr + 128);
    CHECK(o[0].text == want);
    r = pr_si(*m, 0x5575F0, {kStr + 64, kStr + 128, 0, 0}, world);
    o = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(o.size() == 1);
    CHECK(o[0].args[1] == cv::kOptSetDefVol);
    // their argument checks
    r = pr_si(*m, 0x557358, {kStr + 64, 0, 0xABC, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsAddVolumeEx #2:illegal volume name"});
    r = pr_si(*m, 0x557290, {kStr + 64, 0, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsSetCurVolume #2:illegal image handle"});
    put_str(*m, kStr + 160, "QQQ");
    r = pr_si(*m, 0x5575F0, {kStr + 160, kStr + 128, 0, 0}, world);
    CHECK(cv_errors(*m, r.log) == std::vector<std::string>{"cvFsSetDefVol #3:device not found"});
    // the 64-bit size requests by name
    put_str(*m, kStr + 64, "TST:F");
    r = pr_si(*m, 0x557850, {kStr + 64, 0, 0, 0}, world);
    o = calls_to(r.log, if_fn(cv::kIfOptFn1));
    REQUIRE(o.size() == 3);   // "need the device name?" (100) while resolving, then the two halves
    CHECK(o[0].args[1] == cv::kOptNeedDevName);
    CHECK(o[1].args[1] == 202);
    CHECK(o[2].args[1] == 203);
    CHECK(r.v0 == (u64{0x14} << 32) + 0x89ABCDEFull);
    // the 64-bit free size: the device is looked up in the caller's frame BEFORE the path is split into it (the
    // original reads a stale stack buffer there; identical in both bodies, so a pair only)
    pr_si(*m, 0x557908, {kStr + 64, 0x10, 0, 0}, world);
    // the helpers on their own: the next free handle, its release, the resolve step, the "DEV:" prefix, a slot taken
    CHECK(uv(pr_si(*m, 0x556170, {0, 0, 0, 0}, world).v0) == cv::kHandles + 32);  // four files open
    w32(*m, kOut, 0x1111);
    w32(*m, kOut + 4, 0x2222);
    pr(*m, 0x5561D8, {kOut, 0, 0, 0});
    CHECK(r32(*m, kOut) == 0);
    CHECK(r32(*m, kOut + 4) == 0);
    put_str(*m, kStr + 192, "TST");
    put_str(*m, kStr + 224, "G.BIN");
    put_str(*m, kStr + 256, "TST:G.BIN");
    CHECK(uv(pr_si(*m, 0x555FA0, {kStr + 192, kStr + 224, kStr + 256, 0}, world).v0) == kIface);
    pr_si(*m, 0x557700, {kStr + 192, kStr + 224, 0, 0}, cv_world({true, false}));
    CHECK(cstr(*m, kStr + 224) == "TST:G.BIN");
    CHECK(cstr(*m, cv::kAddDevNameBuf) == "G.BIN");
    put_str(*m, kStr + 192, "new");
    CHECK(uv(pr_si(*m, 0x555BA0, {kStr + 192, kGetter, 0, 0}, world).v0) == kIface);
    CHECK(cstr(*m, cv::kDevices + 16 + 4) == "NEW");
    // every device's server (two registered now)
    r = pr_si(*m, 0x556608, {0, 0, 0, 0}, world);
    CHECK(calls_to(r.log, if_fn(cv::kIfExecServer)).size() == 2);
    // close: the device's Close with the file, the handle released
    r = pr_si(*m, 0x556398, {h, 0, 0, 0}, world);
    REQUIRE(calls_to(r.log, if_fn(cv::kIfClose)).size() == 1);
    CHECK(uv(calls_to(r.log, if_fn(cv::kIfClose))[0].args[0]) == kFileId);
    CHECK(r32(*m, h) == 0);
    CHECK(r32(*m, h + 4) == 0);
    MESSAGE("cvFs requests: " << summary());
}

TEST_CASE("game(cri2): cvFs lookups in the snapshots' live device table") {
    for (const char* dir : {"dorm_replay_4900", "b_5800"}) {
        auto m = snapshot_machine(dir);
        if (!m) continue;
        INFO(std::string(dir));
        const WorldSetup world = [](StandInWorld& w) {
            install_strncmp(w);
            install_sprintf(w.si);
        };
        // every registered name resolves to its own interface; a handle's interface names the first slot that has it
        int n = 0;
        for (u32 i = 0; i < cv::kDeviceCount; ++i) {
            const u32 slot = cv::kDevices + i * cv::kDeviceSize;
            const std::string name = cstr(*m, slot + 4);
            if (name.empty()) continue;
            ++n;
            put_str(*m, kStr, name);
            u32 first = slot;
            for (u32 j = 0; j < i; ++j) {
                const u32 s = cv::kDevices + j * cv::kDeviceSize;
                const std::string nj = cstr(*m, s + 4);
                if (!nj.empty() && nj.compare(0, name.size(), name) == 0) {
                    first = s;
                    break;
                }
            }
            CHECK(uv(pr_si(*m, 0x555C78, {kStr, 0, 0, 0}, world).v0) == r32(*m, first));
            w32(*m, kOut, r32(*m, slot));
            w32(*m, kOut + 4, 1);
            const u32 by_if = uv(pr_si(*m, 0x557110, {kOut, 0, 0, 0}, world).v0);
            u32 want = 0;
            for (u32 j = 0; j < cv::kDeviceCount; ++j)
                if (r32(*m, cv::kDevices + j * cv::kDeviceSize) == r32(*m, slot)) {
                    want = cv::kDevices + j * cv::kDeviceSize + 4;
                    break;
                }
            CHECK(by_if == want);
        }
        put_str(*m, kStr, "XYZ");
        CHECK(pr_si(*m, 0x555C78, {kStr, 0, 0, 0}, world).v0 == 0);
        CHECK(n == 6);
        MESSAGE(std::string(dir) << ": " << n << " devices; " << summary());
    }
}

// =====================================================================================================================
// ADXSJD / ADXT: the layers below them stood in (ADXB, PS2RNA, ADXSTM, the list streamer, ADXF's partition lookup)
// =====================================================================================================================
namespace {
namespace at = c2::adxt;
namespace sd = c2::adxsjd;
namespace xb = c2::adxb;
// A fake ADXB record (the decoder object of the ADXB layer, stood in): the fields the hand-written accessors read keep
// their offsets (cri2::adxb); the ones only the stand-ins read sit at +0x60...
constexpr s32 kXbNch = 0x60, kXbTotal = 0x64, kXbStat = 0x68, kXbFormat = 0x6C, kXbVol = 0x70, kXbPan = 0x74,
              kXbHasAinf = 0x78, kXbConsumed = 0x7C, kXbProduced = 0x80;
constexpr u32 kXbArea = kScratch + 0x30000u;   // fake ADXB records, 0x100 apart
constexpr u32 kRnaFake = kScratch + 0x34000u;  // fake PS2RNA / ADXSTM / list-streamer handles (never dereferenced)
constexpr u32 kStmFake = kScratch + 0x34100u;
constexpr u32 kLscFake = kScratch + 0x34200u;

struct AdxOpts {
    u32 queued = 0;            // PS2RNA: samples queued in the output (hypotf_1)
    u32 rna_size = 0x1000;     // PS2RNA: the output's buffer in samples (sub_541AD8)
    u32 stm_stat = 2;          // ADXSTM status (sub_546368)
    u32 lsc_stat = 0;          // the list streamer's status (sub_55D790)
    s32 afs_result = 0;        // ADXF's partition lookup (sub_53DD10)
    bool drain = false;        // the PS2RNA server consumes every player's PCM joints
    u32 header_nch = 2;        // sub_548FC8
    u32 snap_total = 0x7FFFFFFF;  // the total samples a snapshot's (real) ADXB record reports
    std::function<void(StandInWorld&)> more;  // further stand-ins
};

// The ADXB layer: the header decoder parses the public ADX header on the host and fills the fake record.
void install_adxb(StandInWorld& w, u32 snap_total) {
    auto next = std::make_shared<u32>(0);
    w.si.install(0x537890u, "ADXB_Create", [next](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 rec = kXbArea + 0x100u * ((*next)++ & 15u);
        for (u32 i = 0; i < 0x100; i += 4) gsw(ctx, rec + i, 0);
        gsw(ctx, rec + kXbNch, uv(c.args[0]));
        c.v0 = rec;
    }, 4);
    w.si.install(0x537D90u, "ADXB_DecodeHeader", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 rec = uv(c.args[0]), d = uv(c.args[1]);
        auto b8 = [&](u32 o) { return glb(ctx, d + o); };
        auto b16 = [&](u32 o) { return static_cast<u32>((b8(o) << 8) | b8(o + 1)); };
        auto b32 = [&](u32 o) { return (b16(o) << 16) | b16(o + 2); };
        if (b16(0) != 0x8000u) {
            c.v0 = 0;
            return;
        }
        const u32 off = b16(2) + 4;
        ctx.memory->write<u32>(rec + xb::kRate, b32(8));
        ctx.memory->write<u32>(rec + xb::kBlkSmpl, 32);
        gsw(ctx, rec + kXbNch, b8(7));
        gsw(ctx, rec + kXbTotal, b32(12));
        const u32 lp = b8(18) == 4 ? 32u : 20u;  // the loop record: version 4 at +32, version 3 at +20
        const bool loop = b16(2) >= lp + 24 && b16(lp + 6) == 1;
        ctx.memory->write<u16>(rec + xb::kLoopType, loop ? 1 : 0);
        if (loop) {
            gsw(ctx, rec + xb::kLoopStartSmp, b32(lp + 8));
            gsw(ctx, rec + xb::kLoopStartOfs, b32(lp + 12));
            gsw(ctx, rec + xb::kLoopEndSmp, b32(lp + 16));
            gsw(ctx, rec + xb::kLoopEndOfs, b32(lp + 20));
        }
        c.v0 = off;
    }, 8);
    // a fake record answers from its fields; a real ADXB record (a snapshot's) is not read: its channel count comes
    // from the decoder handle that owns it, its total from the world (snap_total), everything else is 0
    auto field = [&w, snap_total](u32 va, const char* name, s32 off) {
        w.si.install(va, name, [off, snap_total](EEContext& ctx, StandIns&, StandInCall& c) {
            const u32 rec = uv(c.args[0]);
            if (rec >= kXbArea && rec < kXbArea + 0x1000u) {
                c.v0 = sx64(static_cast<s32>(glw(ctx, rec + static_cast<u32>(off))));
                return;
            }
            c.v0 = 0;
            if (off == kXbTotal) c.v0 = snap_total;
            if (off == kXbNch)
                for (u32 i = 0; i < sd::kCount; ++i) {
                    const u32 h = sd::kPool + i * sd::kSize;
                    if (glb(ctx, h + sd::kUsed) == 1 && glw(ctx, h + sd::kAdxb) == rec) c.v0 = glb(ctx, h + sd::kNch);
                }
        }, 2);
    };
    field(0x537F30u, "ADXB_GetFormat", kXbFormat);
    field(0x537F40u, "ADXB_GetNumChan", kXbNch);
    field(0x537FE8u, "ADXB_GetTotalNumSmpl", kXbTotal);
    field(0x538038u, "ADXB_HasAinf", kXbHasAinf);
    field(0x538040u, "ADXB_GetDefOutVol", kXbVol);
    field(0x5382C0u, "ADXB_GetStat", kXbStat);
    field(0x5383E8u, "ADXB_GetDecDtLen", kXbConsumed);
    field(0x5383F0u, "ADXB_GetDecNumSmpl", kXbProduced);
    w.si.install(0x538048u, "ADXB_GetDefPan", [](EEContext& ctx, StandIns&, StandInCall& c) {
        c.v0 = sx64(static_cast<s32>(glw(ctx, uv(c.args[0]) + kXbPan)) + static_cast<s32>(c.args[1]));
    }, 2);
    for (const auto& [va, name] : std::initializer_list<std::pair<u32, const char*>>{
             {0x537F08u, "ADXB_EntryGetWrFunc"}, {0x5379B0u, "ADXB_Destroy"}, {0x537CF0u, "ADXB_ResetHdr"},
             {0x538060u, "ADXB_SetLpStart"}, {0x5382C8u, "ADXB_EntryData"}, {0x538348u, "ADXB_Start"},
             {0x538360u, "ADXB_Stop"}, {0x5383A8u, "ADXB_EvokeDecode"}, {0x5389B0u, "ADXB_ExecHndl"},
             {0x535DD8u, "sub_535DD8"}, {0x535E28u, "sub_535E28"}, {0x535FC0u, "sub_535FC0"}, {0x535FF0u, "sub_535FF0"},
             {0x536080u, "sub_536080"}, {0x537790u, "my_malloc"}, {0x542A88u, "adxsjd_DecodeEndAhx"},
             {0x542C70u, "adxsjd_Pend0"}, {0x542DC0u, "adxsjd_Pend1"}})
        w.si.install_recorder(va, name, 0, 3);
    w.si.install_recorder(0x537780u, "adx_GetErrSuppress", 0, 2);
    // the ADX error reporters: the message text logged
    for (u32 va : {0x53AE08u, 0x53AE60u})
        w.si.install(va, va == 0x53AE08u ? "ADXERR_CallErrFunc1" : "ADXERR_CallErrFunc2",
                     [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, uv(c.args[0])); }, 3);
    w.si.install_recorder(0x53AFD8u, "ADXERR_ItoA", 0, 3);
}

// PS2RNA, ADXSTM, the list streamer, the amplifier hooks, ADXF's partition lookup, the three ADXT functions with sce*
// FLIRT names (not taken; stood in here).
void install_drivers(StandInWorld& w, const AdxOpts& o) {
    install_svm(w);
    install_adxb(w, o.snap_total);
    w.si.install_recorder(0x5419F8u, "PS2RNA_Create", kRnaFake, 3);
    w.si.install_recorder(0x545FC8u, "ADXSTM_Create", kStmFake, 3);
    w.si.install_recorder(0x55D2A0u, "LSC_Create", kLscFake, 3);
    w.si.install_recorder(0x541AC0u, "PS2RNA_GetNumData", o.queued, 2);
    w.si.install_recorder(0x541AD8u, "PS2RNA_GetBufSize", o.rna_size, 2);
    w.si.install_recorder(0x546368u, "ADXSTM_GetStat", o.stm_stat, 2);
    w.si.install_recorder(0x55D790u, "LSC_GetStat", o.lsc_stat, 2);
    w.si.install_recorder(0x548FC8u, "adxt_GetNumChan", o.header_nch, 2);
    for (const auto& [va, name] : std::initializer_list<std::pair<u32, const char*>>{
             {0x541A10u, "PS2RNA_Destroy"}, {0x541A78u, "PS2RNA_SetTransSw"}, {0x541A90u, "PS2RNA_SetPlaySw"},
             {0x541B58u, "PS2RNA_SetNumChan"}, {0x541B70u, "PS2RNA_SetSfreq"}, {0x541B88u, "PS2RNA_SetOutVol"},
             {0x541BA0u, "PS2RNA_SetOutPan"}, {0x541BD0u, "PS2RNA_SetBitPerSmpl"}, {0x541CB8u, "PS2RNA_SetTotalNumSmpl"},
             {0x541CC8u, "PS2RNA_SetLpStart"}, {0x560DB8u, "PS2RNA_Discard"}, {0x546058u, "ADXSTM_Destroy"},
             {0x5460E0u, "ADXSTM_BindFile"}, {0x546270u, "ADXSTM_Stop"}, {0x5463A8u, "ADXSTM_SetBufSize"},
             {0x546498u, "ADXSTM_Start"}, {0x5465A0u, "ADXSTM_ReleaseFile"}, {0x5466B8u, "ADXSTM_EntryEosFunc"},
             {0x546718u, "ADXSTM_SetEos"}, {0x546FA0u, "ADXSTM_SetReqRdSize"}, {0x55D3A8u, "LSC_Destroy"},
             {0x55D3F8u, "LSC_SetStm"}, {0x55D668u, "LSC_Stop"}, {0x535888u, "amp_Destroy"}, {0x5358E0u, "amp_Start"},
             {0x535A80u, "amp_Stop"}, {0x535DA8u, "amp_SetSfreq"}, {0x548B38u, "adxt_GetTime (sceInsockBind_2)"},
             {0x549160u, "adxt_SetOutPan (sceInsockListen_2)"}, {0x54A928u, "adxt_SetTrapFlag (sceInsockSetsockopt_2)"},
             {0x54A630u, "adxt_SetHdrPan (__env_lock_0)"}, {0x5433A0u, "adxsjd_GetLpStartOfs"}})
        w.si.install_recorder(va, name, 0, 3);
    w.si.install(0x53DD10u, "ADXF_GetPtinfoFile", [o](EEContext& ctx, StandIns&, StandInCall& c) {
        if (o.afs_result == 0) {
            gsw(ctx, uv(c.args[3]), 0x10);   // the partition id, the first sector, the sector count
            gsw(ctx, uv(c.args[4]), 0x20);
            gsw(ctx, uv(c.args[5]), 0x30);
        }
        c.v0 = sx64(o.afs_result);
    }, 4);
    // the PS2RNA server: optionally plays out every player's PCM joints (data -> free, the read position advances)
    w.si.install(0x541B28u, "PS2RNA_ExecServer", [o](EEContext& ctx, StandIns&, StandInCall& c) {
        if (!o.drain) return;
        for (u32 i = 0; i < at::kCount; ++i) {
            const u32 h = at::kPool + i * at::kSize;
            if (glb(ctx, h + at::kUsed) != 1) continue;
            for (u32 ch = 0; ch < 2; ++ch) {
                const u32 sj = glw(ctx, h + at::kSjo + 4 * ch);
                if (!sj || glw(ctx, sj) != p3fes::game::cri1::sjrbf::kVtable) continue;  // SJRBF joints only
                namespace rb = p3fes::game::cri1::sjrbf;
                const u32 data = glw(ctx, sj + rb::kData), size = glw(ctx, sj + rb::kBufSize);
                if (!data || !size) continue;
                gsw(ctx, sj + rb::kFree, glw(ctx, sj + rb::kFree) + data);
                gsw(ctx, sj + rb::kPos1, (glw(ctx, sj + rb::kPos1) + data) % size);
                gsw(ctx, sj + rb::kData, 0);
                c.extra += data;
            }
        }
    }, 4);
    if (o.more) o.more(w);
}
WorldSetup adx_world(AdxOpts o = {}) {
    return [o](StandInWorld& w) { install_drivers(w, o); };
}

// a fake ADXB record and an ADXSJD handle around it
u32 build_adxb(Machine& m, u32 rec, u32 nch, u32 rate, u32 total) {
    zero(m, rec, 0x100);
    w32(m, rec + xb::kBlkSmpl, 32);
    w32(m, rec + xb::kRate, rate);
    w32(m, rec + kXbNch, nch);
    w32(m, rec + kXbTotal, total);
    return rec;
}

// the public ADX header, parsed on the host
struct AdxInfo {
    bool ok = false;
    u32 data_off = 0, rate = 0, samples = 0, nch = 0;
};
AdxInfo parse_adx(const std::vector<u8>& b) {
    AdxInfo a;
    if (b.size() < 32 || be16(&b[0]) != 0x8000) return a;
    a.ok = true;
    a.data_off = be16(&b[2]) + 4u;
    a.nch = b[7];
    a.rate = be32(&b[8]);
    a.samples = be32(&b[12]);
    return a;
}

// An SJMEM joint built in place over a buffer (cri1's layout; its vtable's functions are hand-written and emitted).
void build_sjmem(Machine& m, u32 h, u32 buf, u32 size) {
    namespace sm = p3fes::game::cri1::sjmem;
    zero(m, h, sm::kSize);
    w32(m, h + 0, sm::kVtable);
    w32(m, h + 4, 1);
    w32(m, h + 8, 0x7C67F0u);
    w32(m, h + sm::kLeft, size);
    w32(m, h + sm::kOffset, 0);
    w32(m, h + sm::kBuf, buf);
    w32(m, h + sm::kBufSize, size);
}
}  // namespace

TEST_CASE("game(cri2): ADXSJD accessors, setters and the handle pool on built records") {
    auto m = machine();
    if (!m) return;
    const WorldSetup world = adx_world();
    const u32 xbr = build_adxb(*m, kXbArea + 0xF00, 2, 48000, 123456);
    w16(*m, xbr + xb::kLoopType, 1);
    w32(*m, xbr + xb::kLoopStartSmp, 1000);
    w32(*m, xbr + xb::kLoopStartOfs, 0x800);
    w32(*m, xbr + xb::kLoopEndSmp, 50000);
    w32(*m, xbr + xb::kLoopEndOfs, 0x9000);
    w32(*m, xbr + kXbFormat, 0);
    // the pool: the first init clears the 16 handles (a junk-filled pool), later ones only count
    std::memset(m->at(sd::kPool), 0x5A, sd::kCount * sd::kSize);
    w32(*m, sd::kInitCount, 0);
    pr_si(*m, 0x541D48, {0, 0, 0, 0}, world);
    CHECK(r32(*m, sd::kInitCount) == 1);
    CHECK(r8(*m, sd::kPool) == 0);
    CHECK(r8(*m, sd::kPool + sd::kCount * sd::kSize - 1) == 0);
    pr_si(*m, 0x541D48, {0, 0, 0, 0}, world);
    CHECK(r32(*m, sd::kInitCount) == 2);
    // create on an input joint and two output SJRBF records (only their buffer fields are read)
    namespace rb = p3fes::game::cri1::sjrbf;
    const u32 sji = kRec + 0x600, sjo0 = kRec + 0x680, sjo1 = kRec + 0x6C0, arr = kRec + 0x700;
    for (u32 o : {sjo0, sjo1}) {
        zero(*m, o, 64);
        w32(*m, o + rb::kBuf, kBuf);
        w32(*m, o + rb::kBufSize, 0x4000);
        w32(*m, o + rb::kXtrSize, 0xC0);
    }
    w32(*m, arr, sjo0);
    w32(*m, arr + 4, sjo1);
    SiResult r = pr_si(*m, 0x541E28, {sji, 2, arr, 0}, world);
    const u32 h = uv(r.v0);
    CHECK(h == sd::kPool);
    const auto cr = calls_to(r.log, 0x537890u);
    REQUIRE(cr.size() == 1);
    CHECK(cr[0].args[0] == 2);              // channels
    CHECK(uv(cr[0].args[1]) == kBuf);       // the first output joint's buffer, half its size, half its size + extra
    CHECK(cr[0].args[2] == 0x2000);
    CHECK(cr[0].args[3] == 0x2000 + 0x60);
    CHECK(r8(*m, h + sd::kUsed) == 1);
    CHECK(r8(*m, h + sd::kNch) == 2);
    CHECK(r32(*m, h + sd::kSji) == sji);
    CHECK(r32(*m, h + sd::kSjo) == sjo0);
    CHECK(r32(*m, h + sd::kSjo + 4) == sjo1);
    CHECK(r32s(*m, h + sd::kTrapSmp) == -1);
    CHECK(r32s(*m, h + sd::kMaxDec) == 0x7FFFFFFF);
    const auto wr = calls_to(r.log, 0x537F08u);
    REQUIRE(wr.size() == 1);
    CHECK(uv(wr[0].args[1]) == 0x542438u);  // the output-info callback, with the handle as its object
    CHECK(uv(wr[0].args[2]) == h);
    // point it at the built ADXB record
    w32(*m, h + sd::kAdxb, xbr);
    // the plain accessors
    w32(*m, h + sd::kDecSmpl, 777);
    w32(*m, h + sd::kDecByte, 888);
    CHECK(prv(*m, 0x542F68, {h, 0, 0, 0}) == 777);
    CHECK(prv(*m, 0x542F60, {h, 0, 0, 0}) == 888);
    CHECK(prv(*m, 0x543100, {h, 0, 0, 0}) == 48000);
    CHECK(prv(*m, 0x543148, {h, 0, 0, 0}) == 32);
    CHECK(sv(prv(*m, 0x5431A8, {h, 0, 0, 0})) == 1);
    CHECK(prv(*m, 0x5431D8, {h, 0, 0, 0}) == 1000);
    CHECK(prv(*m, 0x5431F0, {h, 0, 0, 0}) == 0x800);
    CHECK(prv(*m, 0x5431F0, {0, 0, 0, 0}) == 0);
    CHECK(prv(*m, 0x543220, {h, 0, 0, 0}) == 50000);
    CHECK(prv(*m, 0x543238, {h, 0, 0, 0}) == 0x9000);
    CHECK(uv(pr_si(*m, 0x543118, {h, 0, 0, 0}, world).v0) == 2);
    CHECK(uv(pr_si(*m, 0x543178, {h, 0, 0, 0}, world).v0) == 123456);
    CHECK(uv(pr_si(*m, 0x5430E8, {h, 0, 0, 0}, world).v0) == 0);
    // bits per sample for the time functions: 16 for ADX (format 0), the AHX kinds by their sub-kind
    const std::array<std::array<s32, 3>, 7> bps = {{{0, 0, 16}, {1, 2, 4}, {1, 1, 16}, {2, 2, 4}, {2, 1, 8}, {2, 0, 16}, {3, 2, 16}}};
    for (const auto& [fmt, sub, want] : bps) {
        w16(*m, xbr + xb::kFormat, static_cast<u16>(fmt));
        w16(*m, xbr + xb::kBits, static_cast<u16>(sub));
        INFO(fmt << "/" << sub);
        CHECK(sv(prv(*m, 0x543130, {h, 0, 0, 0})) == want);
    }
    w16(*m, xbr + xb::kFormat, 0);
    // the setters
    pr(*m, 0x542F88, {h, 4242, 0, 0});
    CHECK(r32(*m, h + sd::kDecSmplTotal) == 4242);
    pr(*m, 0x5430A8, {h, 0x55A050, 0x99, 0});
    CHECK(r32(*m, h + sd::kTrapFn) == 0x55A050u);
    CHECK(r32(*m, h + sd::kTrapObj) == 0x99);
    pr(*m, 0x5430B8, {h, 5000, 0, 0});
    CHECK(r32(*m, h + sd::kTrapSmp) == 5000);
    pr(*m, 0x5430C8, {h, 6000, 0, 0});
    CHECK(r32(*m, h + sd::kTrapCnt) == 6000);
    pr(*m, 0x5430D8, {h, 7000, 0, 0});
    CHECK(r32(*m, h + sd::kTrapByte) == 7000);
    r = pr_si(*m, 0x542060, {h, 3072 * 5, 0, 0}, world);
    CHECK(r32(*m, h + sd::kMaxDec) == 3072 * 5);
    CHECK(r32(*m, xbr + 196) == 3072 * 5);
    CHECK(r32(*m, xbr + 200) == 10);  // the samples per call / 1536
    r = pr_si(*m, 0x542010, {h, 0x1234560, 0, 0}, world);
    CHECK(r32(*m, h + sd::kSji) == 0x1234560u);
    REQUIRE(calls_to(r.log, 0x535DD8u).size() == 1);
    CHECK(uv(calls_to(r.log, 0x535DD8u)[0].args[1]) == 0x1234560u);
    w32(*m, h + sd::kSji, sji);
    pr_si(*m, 0x5420A0, {h, 0, 0, 0}, world);
    // start / stop / reset
    w32(*m, h + sd::kDecSmpl, 1);
    w32(*m, h + sd::kTrapSmp, 3);
    pr_si(*m, 0x5420D0, {h, 0, 0, 0}, world);
    CHECK(r8(*m, h + sd::kStat) == 1);
    CHECK(r32(*m, h + sd::kDecSmpl) == 0);
    CHECK(r32s(*m, h + sd::kTrapSmp) == -1);
    CHECK(uv(pr_si(*m, 0x542008, {h, 0, 0, 0}, world).v0) == 1);
    r = pr_si(*m, 0x542100, {h, 0, 0, 0}, world);
    CHECK(r8(*m, h + sd::kStat) == 0);
    CHECK(calls_to(r.log, 0x538360u).size() == 1);
    // the header's volume / pan: only while the header is known (states 2, 3) and the record has them
    w32(*m, xbr + kXbHasAinf, 1);
    w32(*m, xbr + kXbVol, static_cast<u32>(-60));
    w32(*m, xbr + kXbPan, 3);
    for (const int st : {0, 1, 2, 3, 4}) {
        w8(*m, h + sd::kStat, static_cast<u8>(st));
        const bool known = st == 2 || st == 3;
        CHECK(sv(pr_si(*m, 0x543268, {h, 0, 0, 0}, world).v0) == (known ? -60 : 0));
        CHECK(sv(pr_si(*m, 0x5432C0, {h, 1, 0, 0}, world).v0) == (known ? 4 : -128));
    }
    w32(*m, xbr + kXbHasAinf, 0);
    w8(*m, h + sd::kStat, 2);
    CHECK(sv(pr_si(*m, 0x5432C0, {h, 1, 0, 0}, world).v0) == -128);
    pr_si(*m, 0x5433A8, {h, 0, 0, 0}, world);
    // reset of the counters
    pr(*m, 0x541DE8, {h, 0, 0, 0});
    CHECK(r32s(*m, h + sd::kTrapSmp) == -1);
    CHECK(r32s(*m, h + sd::kMaxDec) == 0x7FFFFFFF);
    CHECK(r8(*m, h + sd::kAhx) == 0);
    // destroy: the ADXB record released, the 168 bytes cleared
    r = pr_si(*m, 0x541FA8, {h, 0, 0, 0}, world);
    CHECK(calls_to(r.log, 0x5379B0u).size() == 1);
    for (u32 i = 0; i < sd::kSize; i += 4) CHECK(r32(*m, h + i) == 0);
    pr_si(*m, 0x541FA8, {0, 0, 0, 0}, world);  // a null handle: nothing
    MESSAGE("ADXSJD accessors: " << summary());
}

TEST_CASE("game(cri2): the ADXSJD header stage on real .adx headers (padding, alignment, the header length)") {
    auto m = machine();
    if (!m) return;
    const auto files = disc_files(".ADX");
    if (files.empty()) {
        MESSAGE("SKIP: no .adx files under extracted/");
        return;
    }
    const WorldSetup world = adx_world();
    namespace sm = p3fes::game::cri1::sjmem;
    const u32 h = sd::kPool, xbr = kRec + 0x400, sji = kRec + 0x600;
    int n = 0;
    // one file in 40 of the disc, plus padding variants of the first
    for (std::size_t fi = 0; fi < files.size(); fi += 40) {
        std::vector<u8> data = read_file(files[fi]);
        if (data.size() > 0x10000) data.resize(0x10000);
        const AdxInfo info = parse_adx(data);
        if (!info.ok) continue;
        for (u32 pad : {0u, 2u, 1u, 64u}) {
            INFO(files[fi].filename().string() << " pad " << pad);
            zero(*m, kBuf, pad);
            fill(*m, kBuf + pad, data);
            build_sjmem(*m, sji, kBuf, pad + static_cast<u32>(data.size()));
            zero(*m, h, sd::kSize);
            w8(*m, h + sd::kUsed, 1);
            w8(*m, h + sd::kStat, 1);
            w8(*m, h + sd::kNch, static_cast<u8>(info.nch));
            build_adxb(*m, xbr, info.nch, 0, 0);
            w32(*m, h + sd::kAdxb, xbr);
            w32(*m, h + sd::kSji, sji);
            const SiResult r = pr_si(*m, (pad & 2) ? 0x542130 : 0x542BC8, {h, 0, 0, 0}, world);  // the stage itself or through the handle step
            if (pad & 1) {
                // an odd number of zero bytes before the header: "The data alignment is illegal.", state 4
                CHECK(r8(*m, h + sd::kStat) == 4);
                REQUIRE(calls_to(r.log, 0x53AE60u).size() == 1);
                CHECK(calls_to(r.log, 0x53AE60u)[0].text.find("E04102501") == 0);
                CHECK(calls_to(r.log, 0x537D90u).empty());
            } else {
                // the header found after the padding: state 2, its length kept, the read position just after it
                CHECK(r8(*m, h + sd::kStat) == 2);
                CHECK(r32(*m, h + sd::kHdrLen) == info.data_off);
                CHECK(r32(*m, sji + sm::kOffset) == pad + info.data_off);
                CHECK(r32(*m, sji + sm::kLeft) == data.size() - info.data_off);
                CHECK(r32(*m, xbr + xb::kRate) == info.rate);
            }
            ++n;
        }
    }
    // a chunk shorter than 16 bytes after the padding: nothing decoded, the chunk put back, still state 1
    zero(*m, kBuf, 64);
    w16(*m, kBuf + 8, 0x0080);
    build_sjmem(*m, sji, kBuf, 20);
    w8(*m, h + sd::kStat, 1);
    SiResult r = pr_si(*m, 0x542BC8, {h, 0, 0, 0}, world);
    CHECK(r8(*m, h + sd::kStat) == 1);
    CHECK(r32(*m, sji + sm::kOffset) == 8);  // the 8 zero bytes consumed, the rest put back
    // not an ADX header: the ADXB layer reports 0, the data stays
    for (u32 i = 0; i < 64; ++i) w8(*m, kBuf + i, static_cast<u8>(0x40 + i));
    build_sjmem(*m, sji, kBuf, 64);
    r = pr_si(*m, 0x542BC8, {h, 0, 0, 0}, world);
    CHECK(r8(*m, h + sd::kStat) == 1);
    CHECK(r32(*m, sji + sm::kOffset) == 0);
    // the server runs every used handle
    r = pr_si(*m, 0x542F00, {0, 0, 0, 0}, world);
    CHECK(calls_to(r.log, 0x537D90u).size() == 1);
    MESSAGE("header stage: " << n << " headers; " << summary());
}

namespace {
// a snapshot with the game's SVM lock callbacks and the live players
struct LivePlayer {
    u32 h, stat, sjd;
};
std::vector<LivePlayer> live_players(Machine& m) {
    std::vector<LivePlayer> out;
    for (u32 i = 0; i < at::kCount; ++i) {
        const u32 h = at::kPool + i * at::kSize;
        if (r8(m, h + at::kUsed) == 1) out.push_back({h, r8(m, h + at::kStat), r32(m, h + at::kSjd)});
    }
    return out;
}
}  // namespace

TEST_CASE("game(cri2): the ADXT state rules on the snapshots' live players") {
    auto m = snapshot_machine("dorm_replay_4900");
    if (!m) return;
    prep_snapshot_adx(*m);
    namespace rb = p3fes::game::cri1::sjrbf;
    const auto players = live_players(*m);
    REQUIRE(players.size() == 2);
    const u32 h = players[0].h, sjd = players[0].sjd;
    const u32 sjo0 = r32(*m, h + at::kSjo), sjo1 = r32(*m, h + at::kSjo + 4);
    const u32 rna = r32(*m, h + at::kRna);
    const std::vector<u8> base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    auto restore = [&] { std::memcpy(m->mem.main_ram(), base.data(), base.size()); };
    auto set_data = [&](u32 sj, u32 data) {
        const u32 size = r32(*m, sj + rb::kBufSize);
        const u32 total = r32(*m, sj + rb::kData) + r32(*m, sj + rb::kFree);
        w32(*m, sj + rb::kData, data);
        w32(*m, sj + rb::kFree, total - data);
        (void)size;
    };
    // playing (3): the decoder still decoding -> stays 3
    SiResult r = pr_si(*m, 0x54CA08, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kStat) == 3);
    // playing (3), the decoder ended, both PCM joints below 64 bytes -> decode end (4)
    restore();
    w8(*m, sjd + sd::kStat, 3);
    set_data(sjo0, 0);
    set_data(sjo1, 63);
    pr_si(*m, 0x54C288, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kStat) == 4);
    // ... one joint still holding 64 bytes -> stays 3
    restore();
    w8(*m, sjd + sd::kStat, 3);
    set_data(sjo0, 0);
    set_data(sjo1, 64);
    pr_si(*m, 0x54C288, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kStat) == 3);
    // playing with looping off: once the decoder consumed the stop sample's bytes its trap goes to -1
    restore();
    w8(*m, h + at::kLoopFlag, 0);
    w32(*m, h + at::kStopSmp, r32(*m, sjd + sd::kDecByte));
    pr_si(*m, 0x54C288, {h, 0, 0, 0}, adx_world());
    CHECK(r32s(*m, sjd + sd::kTrapSmp) == -1);
    // decode end (4): silence padded, the output played out -> play end (5), the output stopped and discarded
    restore();
    w8(*m, h + at::kStat, 4);
    set_data(sjo0, 0);
    set_data(sjo1, 0);
    w32(*m, h + at::kFlushedSmp, 0);
    r = pr_si(*m, 0x54C370, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kStat) == 5);
    const auto trans = calls_to(r.log, 0x541A78u), play = calls_to(r.log, 0x541A90u), disc = calls_to(r.log, 0x560DB8u);
    REQUIRE(trans.size() == 1);
    REQUIRE(play.size() == 1);
    REQUIRE(disc.size() == 1);
    CHECK(uv(trans[0].args[0]) == rna);
    CHECK(trans[0].args[1] == 0);
    CHECK(play[0].args[1] == 0);
    CHECK(disc[0].args[1] == 1);
    // the padding went into the joints: maxdec samples each
    CHECK(r32(*m, sjo0 + rb::kData) == 2 * r32(*m, h + at::kMaxDec));
    // ... with samples still queued in the output -> stays 4
    restore();
    w8(*m, h + at::kStat, 4);
    set_data(sjo0, 0);
    set_data(sjo1, 0);
    w32(*m, h + at::kFlushedSmp, 0);
    AdxOpts q;
    q.queued = 100000;
    pr_si(*m, 0x54C370, {h, 0, 0, 0}, adx_world(q));
    CHECK(r8(*m, h + at::kStat) == 4);
    // buffering (2): enough PCM queued -> playing (3), the output started (unless paused)
    restore();
    w8(*m, h + at::kStat, 2);
    w8(*m, h + at::kHold, 0);
    w8(*m, h + at::kPause, 0);
    q.queued = 0x4000;
    r = pr_si(*m, 0x54C100, {h, 0, 0, 0}, adx_world(q));
    CHECK(r8(*m, h + at::kStat) == 3);
    CHECK(r8(*m, h + at::kStarted) == 1);
    REQUIRE(calls_to(r.log, 0x541A90u).size() == 1);
    CHECK(calls_to(r.log, 0x541A90u)[0].args[1] == 1);
    CHECK(r32(*m, h + at::kVsyncAtPause) == r32(*m, at::kVsync));
    // ... held: started, still buffering
    restore();
    w8(*m, h + at::kStat, 2);
    w8(*m, h + at::kHold, 1);
    pr_si(*m, 0x54C100, {h, 0, 0, 0}, adx_world(q));
    CHECK(r8(*m, h + at::kStat) == 2);
    CHECK(r8(*m, h + at::kStarted) == 1);
    // ... too little queued, the decoder still running: stays 2, nothing started
    restore();
    w8(*m, h + at::kStat, 2);
    w8(*m, h + at::kStarted, 0);
    q.queued = 0;
    q.rna_size = 0x100000;   // a block is smaller than the output's buffer: wait for the decoder
    r = pr_si(*m, 0x54C100, {h, 0, 0, 0}, adx_world(q));
    CHECK(r8(*m, h + at::kStat) == 2);
    CHECK(r8(*m, h + at::kStarted) == 0);
    // opening (1), a memory source, the header known: the samples per call from the rate and the server frequency
    restore();
    w8(*m, h + at::kStat, 1);
    w8(*m, h + at::kSource, 2);
    w8(*m, h + at::kOpenReq, 0);
    w8(*m, sjd + sd::kStat, 2);
    const u32 xbr = r32(*m, sjd + sd::kAdxb);
    const u32 rate = r32(*m, xbr + xb::kRate), blk = r32(*m, xbr + xb::kBlkSmpl), freq = r32(*m, h + at::kSvrFreq);
    const bool looped = r16s(*m, xbr + xb::kLoopType) > 0;
    AdxOpts two;
    two.more = [](StandInWorld& w) { w.si.install_recorder(0x537F40u, "ADXB_GetNumChan", 2, 2); };
    r = pr_si(*m, 0x54BCD8, {h, 0, 0, 0}, adx_world(two));
    CHECK(r8(*m, h + at::kStat) == 2);
    REQUIRE(blk != 0);
    const s32 per = looped ? 3 * static_cast<s32>(rate / freq) : 3 * static_cast<s32>(rate / freq) / 2;
    const s32 unit = 2 * static_cast<s32>(blk);
    CHECK(r32s(*m, h + at::kMaxDec) == (per + unit) / unit * unit);
    REQUIRE(calls_to(r.log, 0x541B70u).size() == 1);
    CHECK(calls_to(r.log, 0x541B70u)[0].args[1] == rate);
    // ... the header asks for more channels than the player has: reported, the player stopped
    restore();
    w8(*m, h + at::kStat, 1);
    w8(*m, h + at::kSource, 2);
    w8(*m, h + at::kOpenReq, 0);
    w8(*m, sjd + sd::kStat, 2);
    w8(*m, h + at::kMaxCh, 1);
    r = pr_si(*m, 0x54BCD8, {h, 0, 0, 0}, adx_world(two));
    REQUIRE(calls_to(r.log, 0x53AE60u).size() == 1);
    CHECK(calls_to(r.log, 0x53AE60u)[0].text.find("E9081001") == 0);
    CHECK(r8(*m, h + at::kStat) == 0);
    // ... the decoder failed on the header (4): error state 6
    restore();
    w8(*m, h + at::kStat, 1);
    w8(*m, h + at::kSource, 2);
    w8(*m, h + at::kOpenReq, 0);
    w8(*m, sjd + sd::kStat, 4);
    pr_si(*m, 0x54BCD8, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kStat) == 6);
    // ... a file source with the open request: the streamer bound to the requested range, the request cleared
    restore();
    w8(*m, h + at::kStat, 1);
    w8(*m, h + at::kSource, 0);
    w8(*m, h + at::kOpenReq, 1);
    w32(*m, h + at::kReqFname, kStr);
    w32(*m, h + at::kReqPtid, 0);
    w32(*m, h + at::kReqOfst, 5);
    w32(*m, h + at::kReqNsct, 99);
    AdxOpts idle;
    idle.stm_stat = 0;
    r = pr_si(*m, 0x54BCD8, {h, 0, 0, 0}, adx_world(idle));
    CHECK(r8(*m, h + at::kOpenReq) == 0);
    REQUIRE(calls_to(r.log, 0x5460E0u).size() == 1);
    CHECK(uv(calls_to(r.log, 0x5460E0u)[0].args[1]) == kStr);
    CHECK(calls_to(r.log, 0x5460E0u)[0].args[3] == 5);
    // ... the streamer still busy (2): nothing happens this call
    restore();
    w8(*m, h + at::kStat, 1);
    w8(*m, h + at::kSource, 0);
    w8(*m, h + at::kOpenReq, 1);
    r = pr_si(*m, 0x54BCD8, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kOpenReq) == 1);
    CHECK(calls_to(r.log, 0x5460E0u).empty());
    // the error check: a failed streamer (4) or list streamer (3) -> state 6, error code -1
    restore();
    AdxOpts bad;
    bad.stm_stat = 4;
    pr_si(*m, 0x54C8C0, {h, 0, 0, 0}, adx_world(bad));
    CHECK(r8(*m, h + at::kStat) == 6);
    CHECK(r16s(*m, h + at::kErrCode) == -1);
    restore();
    bad.stm_stat = 2;
    bad.lsc_stat = 3;
    pr_si(*m, 0x54C8C0, {h, 0, 0, 0}, adx_world(bad));
    CHECK(r8(*m, h + at::kStat) == 6);
    // the end-of-input check: a file source whose streamer finished (3) tells the decoder
    restore();
    AdxOpts eos;
    eos.stm_stat = 3;
    r = pr_si(*m, 0x54C940, {h, 0, 0, 0}, adx_world(eos));
    CHECK(calls_to(r.log, 0x536080u).size() == 1);
    // the play end state does nothing; the null handle reports
    restore();
    w8(*m, h + at::kStat, 5);
    pr_si(*m, 0x54C578, {h, 0, 0, 0}, adx_world());
    CHECK(r8(*m, h + at::kStat) == 5);
    r = pr_si(*m, 0x54CA08, {0, 0, 0, 0}, adx_world());
    REQUIRE(calls_to(r.log, 0x53AE08u).size() == 1);
    CHECK(calls_to(r.log, 0x53AE08u)[0].text.find("E02080842") == 0);
    // the dispatcher and its lock wrapper on every state (each state's step, then the end-of-input and error checks)
    for (u8 st = 0; st <= 6; ++st) {
        restore();
        w8(*m, h + at::kStat, st);
        w8(*m, h + at::kOpenReq, 0);
        w8(*m, h + at::kSource, 2);
        pr_si(*m, (st & 1) ? 0x54C9D8 : 0x54CA08, {h, 0, 0, 0}, adx_world());
    }
    MESSAGE("ADXT state rules: " << summary());
}

TEST_CASE("game(cri2): the ADXSJD decode stage on the snapshots' live decoders") {
    for (const char* dir : {"dorm_replay_4900", "b_5800"}) {
        auto m = snapshot_machine(dir);
        if (!m) continue;
        INFO(std::string(dir));
        prep_snapshot_adx(*m);
        const std::vector<u8> base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        auto restore = [&] { std::memcpy(m->mem.main_ram(), base.data(), base.size()); };
        int n = 0;
        for (u32 i = 0; i < sd::kCount; ++i) {
            const u32 h = sd::kPool + i * sd::kSize;
            if (r8(*m, h + sd::kUsed) != 1) continue;
            ++n;
            const u32 stat = r8(*m, h + sd::kStat);
            // one decode step, its input and output halves, the output-info callback, the whole handle step
            for (u32 fn : {0x542B18u, 0x542558u, 0x5428C0u, 0x542BC8u}) {
                restore();
                w8(*m, h + sd::kStat, 2);
                pr_si(*m, fn, {h, 0, 0, 0}, adx_world());
            }
            restore();
            const SiResult r = pr_si(*m, 0x542438, {h, kOut, kOut + 4, kOut + 8}, adx_world());
            CHECK(uv(r.v0) == r32(*m, r32(*m, h + sd::kAdxb) + 60));
            // the room per channel: the first output joint's chunk from its free line, in samples
            CHECK(r32s(*m, kOut + 4) == std::min(r32s(*m, h + sd::kMaxDec), r32s(*m, h + sd::kOutChunk + 4) / 2));
            // ... and the samples allowed before the trap (0x1FFFFFFF without one)
            const s32 trap = r32s(*m, h + sd::kTrapSmp);
            CHECK(r32s(*m, kOut + 8) == (trap >= 0 ? trap - r32s(*m, h + sd::kTrapCnt) : 0x1FFFFFFF));
            // the decode end of a stream at its total: state 3
            restore();
            w8(*m, h + sd::kStat, 2);
            AdxOpts end;
            end.snap_total = 0;
            pr_si(*m, 0x542558, {h, 0, 0, 0}, adx_world(end));
            CHECK(r8(*m, h + sd::kStat) == 3);
            (void)stat;
        }
        CHECK(n > 0);
        MESSAGE(std::string(dir) << ": " << n << " decoders; " << summary());
    }
}

TEST_CASE("game(cri2): the ADXT server frame after frame on the replay snapshots (the output playing the joints out)") {
    for (const char* dir : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        auto m = snapshot_machine(dir);
        if (!m) continue;
        INFO(std::string(dir));
        prep_snapshot_adx(*m);
        const auto players = live_players(*m);
        std::map<u32, std::vector<u32>> trace;  // player -> its state after each frame
        AdxOpts o;
        o.drain = true;
        int frames = 0, rna_calls = 0;
        for (int f = 0; f < 40; ++f) {
            // the decoders end after frame 8 (the ADXB layer reports its total reached), the output drains
            o.queued = f < 20 ? 0x2000u : 0u;
            o.snap_total = f < 8 ? 0x7FFFFFFFu : 0u;
            const SiResult r = pr_si(*m, 0x549EA0, {0, 0, 0, 0}, adx_world(o));
            rna_calls += static_cast<int>(calls_to(r.log, 0x541B28u).size());
            CHECK(r32(*m, at::kSvrState) == 0);
            for (const LivePlayer& p : players) trace[p.h].push_back(r8(*m, p.h + at::kStat));
            ++frames;
        }
        // the output server runs twice per call at a server frequency below 51 (the snapshots: 29)
        CHECK(rna_calls == frames * (r32(*m, at::kCurSvrFreq) < 51 ? 2 : 1));
        for (const LivePlayer& p : players) {
            const auto& t = trace[p.h];
            std::string s;
            for (u32 v : t) s += static_cast<char>('0' + v);
            INFO("player " << std::hex << p.h << " states " << s);
            // states never go back (3 -> 4 -> 5), and a playing player reaches the play end
            for (std::size_t i = 1; i < t.size(); ++i)
                if (!(t[i - 1] == 5 && t[i] == 5)) CHECK(t[i] >= t[i - 1]);
            if (p.stat == 3) CHECK(t.back() == 5);
            if (p.stat == 5 || p.stat == 0) CHECK(t.back() == p.stat);
        }
        MESSAGE(std::string(dir) << ": " << players.size() << " players, " << frames << " frames; " << summary());
    }
}

namespace {
// The public entry point (a lock wrapper: the retail lock / unlock stubs are empty) and its body from the same machine:
// both pairs run, the body first from a copy of the memory, then the wrapper; both must leave the same memory (apart
// from the stack) and make the same stand-in calls. Returns the wrapper's run.
SiResult both(Machine& m, u32 wrapper, u32 body, Args a, const WorldSetup& world, std::map<unsigned, u64> t = {}) {
    std::vector<u8> before(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    const SiResult rb = pr_si(m, body, a, world, t);
    std::vector<u8> after_body(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    std::memcpy(m.mem.main_ram(), before.data(), before.size());
    const SiResult rw = pr_si(m, wrapper, a, world, t);
    const u8* now = m.mem.main_ram();
    constexpr u32 kStackLo = kSp - 0x20000u, kStackHi = kSp + 0x100u;
    bool same = std::memcmp(now, after_body.data(), kStackLo) == 0 &&
                std::memcmp(now + kStackHi, after_body.data() + kStackHi, EEMemory::kMainRamSize - kStackHi) == 0;
    const std::string what = std::string(by_addr(wrapper).name) + " vs " + by_addr(body).name;
    INFO(what);
    CHECK(same);
    CHECK(rw.log.size() == rb.log.size());
    return rw;
}
}  // namespace

TEST_CASE("game(cri2): an ADXT player's life on a fresh machine (create, the starts, the header, stop, destroy)") {
    auto m = machine();
    if (!m) return;
    const auto files = disc_files(".ADX");
    if (files.empty()) {
        MESSAGE("SKIP: no .adx files under extracted/");
        return;
    }
    std::vector<u8> adx = read_file(files[files.size() / 2]);
    if (adx.size() > 0x20000) adx.resize(0x20000);
    const AdxInfo info = parse_adx(adx);
    REQUIRE(info.ok);
    const WorldSetup world = adx_world();
    // the server frequency (default and current)
    both(*m, 0x5497B0, 0x5497E0, {30, 0, 0, 0}, world);
    CHECK(r32(*m, at::kDefSvrFreq) == 30);
    CHECK(r32(*m, at::kCurSvrFreq) == 30);
    // create a 2-channel player: the PCM buffers at the 64-byte aligned start, the ring after them in whole sectors
    constexpr u32 kWork = 0x01830000u, kWorkSize = 0x30000u;
    SiResult r = both(*m, 0x547BC0, 0x547C18, {2, kWork + 8, kWorkSize, 0}, world);
    const u32 h = uv(r.v0);
    REQUIRE(h == at::kPool);
    CHECK(r8(*m, h + at::kUsed) == 1);
    CHECK(r8(*m, h + at::kStat) == 0);
    CHECK(r8(*m, h + at::kMaxCh) == 2);
    const u32 obuf = (kWork + 8 + 63) & ~63u;
    CHECK(r32(*m, h + at::kObuf) == obuf);
    CHECK(r32(*m, h + at::kIbuf) == obuf + 2 * 16576);
    const s32 rest = static_cast<s32>(kWorkSize - (obuf - (kWork + 8))) - 2 * 16576;
    CHECK(r32s(*m, h + at::kIbufSize) == (rest - 292) / 2048 * 2048);
    CHECK(r32(*m, h + at::kFnameBuf) == r32(*m, h + at::kIbuf) + r32(*m, h + at::kIbufSize) + 36);
    CHECK(r16s(*m, h + at::kMaxSct) == r32s(*m, h + at::kIbufSize) / 2048);
    CHECK(r16s(*m, h + at::kMinSct) == static_cast<s16>(static_cast<float>(r16s(*m, h + at::kMaxSct)) * 0.85f));
    CHECK(r16s(*m, h + at::kOutPan) == -128);
    CHECK(r8(*m, h + at::kLoopFlag) == 1);
    CHECK(r32(*m, h + at::kSvrFreq) == 30);
    CHECK(r32(*m, h + at::kStm) == kStmFake);
    CHECK(r32(*m, h + at::kRna) == kRnaFake);
    const u32 sjd = r32(*m, h + at::kSjd);
    CHECK(sjd == sd::kPool);
    // the status
    CHECK(sv(both(*m, 0x548768, 0x5487A0, {h, 0, 0, 0}, world).v0) == 0);
    CHECK(sv(both(*m, 0x548768, 0x5487A0, {0, 0, 0, 0}, world).v0) == -1);
    // start a named file: the name copied into the player's buffer, an open request for the whole file
    put_str(*m, kStr, "BGM:\\BGM_00.ADX");
    r = both(*m, 0x54B2E8, 0x54B328, {h, kStr, 0, 0}, world);
    CHECK(cstr(*m, r32(*m, h + at::kFnameBuf)) == "BGM:\\BGM_00.ADX");
    CHECK(r32(*m, h + at::kReqFname) == r32(*m, h + at::kFnameBuf));
    CHECK(r32(*m, h + at::kReqNsct) == 0xFFFFF);
    CHECK(r8(*m, h + at::kStat) == 1);
    CHECK(r8(*m, h + at::kSource) == 0);
    CHECK(r8(*m, h + at::kOpenReq) == 1);
    CHECK(calls_to(r.log, 0x546270u).size() == 1);  // the stop of whatever played before
    pr_si(*m, 0x54B230, {h, kStr, 4, 8}, world);   // a range: first sector 4, 8 sectors
    CHECK(r32(*m, h + at::kReqOfst) == 4);
    CHECK(r32(*m, h + at::kReqNsct) == 8);
    // the opening state binds the streamer to the request (the streamer idle)
    AdxOpts idle;
    idle.stm_stat = 0;
    r = pr_si(*m, 0x54BCD8, {h, 0, 0, 0}, adx_world(idle));
    REQUIRE(calls_to(r.log, 0x5460E0u).size() == 1);
    CHECK(calls_to(r.log, 0x5460E0u)[0].args[3] == 4);
    CHECK(r8(*m, h + at::kOpenReq) == 0);
    pr_si(*m, 0x548410, {h, kStr, 0, 0}, adx_world(idle), tregs(16));
    // start file 7 of a partition: the range from ADXF
    r = both(*m, 0x54B088, 0x54B0D8, {h, 3, 7, 0}, world);
    CHECK(r32(*m, h + at::kReqPtid) == 0x10);
    CHECK(r32(*m, h + at::kReqOfst) == 0x20);
    CHECK(r32(*m, h + at::kReqNsct) == 0x30);
    CHECK(r8(*m, h + at::kSource) == 1);
    // ... ADXF fails: the result returned, nothing started
    AdxOpts nf;
    nf.afs_result = -1;
    w8(*m, h + at::kStat, 0);
    r = both(*m, 0x54B088, 0x54B0D8, {h, 3, 8, 0}, adx_world(nf));
    CHECK(sv(r.v0) == -1);
    CHECK(r8(*m, h + at::kStat) == 0);
    // a memory index holding the .adx file as entry 1 (big-endian count and offsets)
    constexpr u32 kIdx = 0x01870000u;
    zero(*m, kIdx, 64);
    w32(*m, kIdx + 4, 0x02000000u);
    w32(*m, kIdx + 8 + 8, 0x40000000u);
    fill(*m, kIdx + 64, adx);
    // ... entry 2 is past the count: the player is stopped, nothing started
    r = both(*m, 0x54B4D0, 0x54B520, {h, kIdx, 2, 0}, world);
    CHECK(r8(*m, h + at::kStat) == 0);
    // ... entry 1: an SJMEM joint over it (source 2), the decoder started
    r = both(*m, 0x54B4D0, 0x54B520, {h, kIdx, 1, 0}, world);
    CHECK(r8(*m, h + at::kSource) == 2);
    CHECK(r8(*m, h + at::kStat) == 1);
    const u32 sji = r32(*m, h + at::kSji);
    namespace sm = p3fes::game::cri1::sjmem;
    CHECK(r32(*m, sji + sm::kBuf) == kIdx + 64);
    CHECK(r8(*m, sjd + sd::kStat) == 1);
    // one server call: the decoder reads the header from the joint (state 2), the player opens the output
    r = both(*m, 0x549EA0, 0x549EC8, {0, 0, 0, 0}, world);
    CHECK(r8(*m, sjd + sd::kStat) == 2);
    CHECK(r32(*m, sjd + sd::kHdrLen) == info.data_off);
    CHECK(r32(*m, sji + sm::kOffset) == info.data_off);
    CHECK(r8(*m, h + at::kStat) == (info.nch <= 2 ? 2 : 0));
    if (info.nch <= 2) {
        REQUIRE(calls_to(r.log, 0x541B70u).size() == 1);
        CHECK(calls_to(r.log, 0x541B70u)[0].args[1] == info.rate);  // the output's rate
        CHECK(calls_to(r.log, 0x541B58u)[0].args[1] == info.nch);    // its channels
    }
    // the samples / rate / time accessors once the header is known
    CHECK(uv(both(*m, 0x548F40, 0x548F78, {h, 0, 0, 0}, world).v0) == info.rate);
    CHECK(uv(both(*m, 0x548EB8, 0x548EF0, {h, 0, 0, 0}, world).v0) == info.samples);
    both(*m, 0x548AE8, 0x548AE8, {h, kOut, kOut + 4, 0}, world);
    pr_si(*m, 0x5489A0, {h, kOut, kOut + 4, 0}, world);  // still buffering: (0, 1)
    CHECK(r32(*m, kOut) == 0);
    CHECK(r32(*m, kOut + 4) == 1);
    w8(*m, h + at::kStat, 3);                              // playing: (samples played, the rate)
    pr_si(*m, 0x5489A0, {h, kOut, kOut + 4, 0}, world);
    CHECK(r32(*m, kOut + 4) == info.rate);
    w8(*m, h + at::kStat, 2);
    // volume: stored, the header's volume added only in pan mode 1
    pr(*m, 0x5497A0, {h, 0, 0, 0});
    CHECK(r8(*m, h + at::kPanMode) == 0);
    r = both(*m, 0x549480, 0x5494C0, {h, static_cast<u64>(-30), 0, 0}, world);
    CHECK(r16s(*m, h + at::kOutVol) == -30);
    REQUIRE(calls_to(r.log, 0x541B88u).size() == 1);
    CHECK(sv(calls_to(r.log, 0x541B88u)[0].args[1]) == -30);
    // pan per channel: -128 is automatic (+-15 in stereo), a value is used as given, a channel past the player's
    // is stored but reported
    AdxOpts two;
    two.more = [](StandInWorld& w) { w.si.install_recorder(0x537F40u, "ADXB_GetNumChan", 2, 2); };
    for (u32 ch = 0; ch < 2; ++ch) {
        r = pr_si(*m, 0x5491B0, {h, ch, static_cast<u64>(-128), 0}, adx_world(two));
        REQUIRE(calls_to(r.log, 0x541BA0u).size() == 1);
        CHECK(sv(calls_to(r.log, 0x541BA0u)[0].args[2]) == (ch ? 15 : -15));
    }
    r = pr_si(*m, 0x5491B0, {h, 0, 20, 0}, adx_world(two));
    CHECK(sv(calls_to(r.log, 0x541BA0u)[0].args[2]) == 20);
    r = pr_si(*m, 0x5491B0, {h, 2, 20, 0}, adx_world(two));
    REQUIRE(calls_to(r.log, 0x53AE08u).size() == 1);
    CHECK(calls_to(r.log, 0x53AE08u)[0].text.find("E8101208") == 0);
    pr_si(*m, 0x54B988, {h, 0, 0, 0}, adx_world(two));
    pr(*m, 0x54A638, {h, kOut, kOut + 4, 0});  // the header-pan stub
    // the player's server frequency, the flags, the error code, the pause, the PCM waiting
    both(*m, 0x5497F8, 0x549838, {h, 60, 0, 0}, world);
    CHECK(r32(*m, h + at::kSvrFreq) == 60);
    CHECK(r32(*m, at::kCurSvrFreq) == 60);
    pr(*m, 0x549E28, {h, 1, 0, 0});
    both(*m, 0x549DE8, 0x549E28, {h, 1, 0, 0}, world);
    CHECK(r8(*m, h + at::kFlag6D) == 1);
    CHECK(sv(both(*m, 0x549FF8, 0x54A030, {h, 0, 0, 0}, world).v0) == 0);
    CHECK(sv(both(*m, 0x549FF8, 0x54A030, {0, 0, 0, 0}, world).v0) == -1);
    CHECK(sv(both(*m, 0x54A530, 0x54A568, {h, 0, 0, 0}, world).v0) == 0);
    w8(*m, h + at::kStat, 3);
    both(*m, 0x54A3C0, 0x54A400, {h, 1, 0, 0}, world);  // pause: the output paused, the time kept
    CHECK(r8(*m, h + at::kPause) == 1);
    CHECK(sv(both(*m, 0x54A530, 0x54A568, {h, 0, 0, 0}, world).v0) == 1);
    both(*m, 0x54A3C0, 0x54A400, {h, 0, 0, 0}, world);  // resume: the time base from the vsync count
    CHECK(r8(*m, h + at::kPause) == 0);
    CHECK(r32(*m, h + at::kVsyncAtPause) == r32(*m, at::kVsync));
    namespace rb = p3fes::game::cri1::sjrbf;
    const u32 sjo0 = r32(*m, h + at::kSjo);
    CHECK(sv(prv(*m, 0x549BB0, {h, 0, 0, 0})) == static_cast<s32>(r32(*m, sjo0 + rb::kData) / 2));
    // the loop flag; off sets the stop sample at the end of the current loop pass
    both(*m, 0x54A138, 0x54A178, {h, 0, 0, 0}, world);
    CHECK(r8(*m, h + at::kLoopFlag) == 0);
    both(*m, 0x54A138, 0x54A178, {h, 1, 0, 0}, world);
    // the traps the opening state installs: the loop trap, the end-of-stream trap
    pr_si(*m, 0x54B690, {h, 0, 0, 0}, world);
    CHECK(r32(*m, sjd + sd::kTrapFn) == 0x54B748u);
    CHECK(r32(*m, sjd + sd::kTrapObj) == h);
    pr_si(*m, 0x54B9F0, {h, 0, 0, 0}, world);
    // the trap flag mirrors into the decoder
    pr(*m, 0x54A968, {h, 1, 0, 0});
    CHECK(r8(*m, h + at::kTrapFlag) == 1);
    CHECK(r32(*m, sjd + sd::kTrapFlag) == 1);
    // a caller's joint (source 3); a null joint is reported
    r = both(*m, 0x5484E0, 0x548520, {h, sji, 0, 0}, world);
    CHECK(r8(*m, h + at::kSource) == 3);
    CHECK(r32(*m, h + at::kSji) == sji);
    r = both(*m, 0x5484E0, 0x548520, {h, 0, 0, 0}, world);
    REQUIRE(calls_to(r.log, 0x53AE08u).size() == 1);
    pr_si(*m, 0x548318, {h, sji, 0, 0}, world);
    // the buffering / playing / decode-end / play-end / checks on this player
    for (u32 fn : {0x54C100u, 0x54C288u, 0x54C370u, 0x54C578u, 0x54C8C0u, 0x54C940u}) pr_si(*m, fn, {h, 0, 0, 0}, world);
    // stop: the streamer stopped, the decoder stopped, state 0
    r = both(*m, 0x548678, 0x5486A8, {h, 0, 0, 0}, world);
    CHECK(r8(*m, h + at::kStat) == 0);
    CHECK(r8(*m, sjd + sd::kStat) == 0);
    CHECK(calls_to(r.log, 0x546270u).size() == 1);
    pr_si(*m, 0x5485D8, {h, 0, 0, 0}, world);
    // the destroy hooks; destroy releases everything and clears the handle
    w32(*m, at::kHookDestroy0, 0x55B120u);
    w32(*m, at::kHookDestroy1, 0x55B0F8u);
    w32(*m, at::kHookDestroy2, 0x55B160u);
    AdxOpts hooks;
    hooks.more = [](StandInWorld& w) {
        w.si.install_recorder(0x55B0F8u, "destroy_hook1", 0, 2);
        w.si.install_recorder(0x55B120u, "destroy_hook0", 0, 2);
        w.si.install_recorder(0x55B160u, "destroy_hook2", 0, 2);
    };
    for (u32 fn : {0x547FD0u, 0x547FF8u, 0x548020u}) {
        r = pr_si(*m, fn, {h, 0, 0, 0}, adx_world(hooks));
        CHECK(r.log.size() == 1);
    }
    r = both(*m, 0x548048, 0x548078, {h, 0, 0, 0}, adx_world(hooks));
    REQUIRE(calls_to(r.log, 0x55B0F8u).size() == 1);
    CHECK(uv(calls_to(r.log, 0x55B0F8u)[0].args[0]) == h);
    CHECK(calls_to(r.log, 0x541A10u).size() == 1);  // the output
    CHECK(calls_to(r.log, 0x546058u).size() == 1);  // the streamer
    CHECK(calls_to(r.log, 0x55D3A8u).size() == 1);  // the list streamer
    for (u32 i = 0; i < at::kSize; i += 4) CHECK(r32(*m, h + i) == 0);
    CHECK(r8(*m, sjd + sd::kUsed) == 0);
    w32(*m, at::kHookDestroy0, 0);
    w32(*m, at::kHookDestroy1, 0);
    w32(*m, at::kHookDestroy2, 0);
    r = both(*m, 0x548048, 0x548078, {0, 0, 0, 0}, world);
    REQUIRE(calls_to(r.log, 0x53AE08u).size() == 1);
    // too many handles: the 17th create fails
    for (u32 i = 0; i < at::kCount; ++i) w8(*m, at::kPool + i * at::kSize, 1);
    r = both(*m, 0x547BC0, 0x547C18, {1, kWork, kWorkSize, 0}, world);
    CHECK(r.v0 == 0);
    REQUIRE(calls_to(r.log, 0x53AE08u).size() == 1);
    CHECK(calls_to(r.log, 0x53AE08u)[0].text.find("E03100801") == 0);
    // the SVM lock wrappers of the ADX libraries: through the lock / unlock callbacks
    w32(*m, p3fes::game::cri1::svm::kLockFn, kSvmLockCb);
    w32(*m, p3fes::game::cri1::svm::kUnlockFn, kSvmUnlockCb);
    w32(*m, p3fes::game::cri1::svm::kLockDepth, 0);
    r = pr_si(*m, 0x539818, {0, 0, 0, 0}, world);
    CHECK(calls_to(r.log, kSvmLockCb).size() == 1);
    CHECK(r32(*m, p3fes::game::cri1::svm::kLockDepth) == 1);
    r = pr_si(*m, 0x539830, {0, 0, 0, 0}, world);
    CHECK(calls_to(r.log, kSvmUnlockCb).size() == 1);
    CHECK(r32(*m, p3fes::game::cri1::svm::kLockDepth) == 0);
    MESSAGE("ADXT lifecycle: " << summary());
}

// =====================================================================================================================
// libmpeg: headers on the disc's movies (an MPEG program-stream demultiplexer on the host feeds the bit reader)
// =====================================================================================================================
namespace {
namespace mp = c2::mpeg;
constexpr u32 kNextBit = 0x4FD658u, kPeepBit = 0x4FD740u, kFlushBuf = 0x4FF9D0u, kFlushByte = 0x4FFB38u;
constexpr u32 kMpegError = 0x502668u, kMpegError1 = 0x5026C0u;
constexpr u32 kExtTable = 0x7BD7E8u;  // the extension handlers by extension id (11 words)
constexpr u32 kState = kRec;          // the decoder state (2,200 bytes)

// The video elementary stream (stream 0xE0) of an MPEG-1 / MPEG-2 program stream, from its first `limit` bytes.
std::vector<u8> demux_video(const std::vector<u8>& ps) {
    std::vector<u8> es;
    std::size_t i = 0;
    while (i + 4 <= ps.size()) {
        if (!(ps[i] == 0 && ps[i + 1] == 0 && ps[i + 2] == 1)) {
            ++i;
            continue;
        }
        const u8 id = ps[i + 3];
        if (id == 0xBA) {  // pack header: MPEG-1 12 bytes, MPEG-2 14 + stuffing
            if (i + 5 > ps.size()) break;
            if ((ps[i + 4] & 0xC0) == 0x40) {
                if (i + 14 > ps.size()) break;
                i += 14 + (ps[i + 13] & 7);
            } else {
                i += 12;
            }
            continue;
        }
        if (id == 0xB9) break;  // program end
        if (id < 0xBB) {
            ++i;
            continue;
        }
        if (i + 6 > ps.size()) break;
        const std::size_t len = (static_cast<std::size_t>(ps[i + 4]) << 8) | ps[i + 5];
        const std::size_t end = i + 6 + len;
        if (end > ps.size()) break;
        if (id == 0xE0) {
            std::size_t p = i + 6;
            if ((ps[p] & 0xC0) == 0x80) {  // MPEG-2 PES header
                p += 3 + ps[p + 2];
            } else {  // MPEG-1: stuffing, STD buffer, PTS / DTS
                while (p < end && ps[p] == 0xFF) ++p;
                if (p < end && (ps[p] & 0xC0) == 0x40) p += 2;
                if (p < end && (ps[p] & 0xF0) == 0x20) p += 5;
                else if (p < end && (ps[p] & 0xF0) == 0x30) p += 10;
                else if (p < end && ps[p] == 0x0F) p += 1;
            }
            if (p < end) es.insert(es.end(), ps.begin() + static_cast<std::ptrdiff_t>(p), ps.begin() + static_cast<std::ptrdiff_t>(end));
        }
        i = end;
    }
    return es;
}
std::vector<u8> read_head(const std::filesystem::path& p, std::size_t n) {
    std::ifstream f(p, std::ios::binary);
    std::vector<u8> b(n);
    f.read(reinterpret_cast<char*>(b.data()), static_cast<std::streamsize>(n));
    b.resize(static_cast<std::size_t>(f.gcount()));
    return b;
}
// start codes of an elementary stream: (offset of the 00 00 01, code)
std::vector<std::pair<std::size_t, u8>> start_codes(const std::vector<u8>& es) {
    std::vector<std::pair<std::size_t, u8>> out;
    for (std::size_t i = 0; i + 3 < es.size(); ++i)
        if (es[i] == 0 && es[i + 1] == 0 && es[i + 2] == 1) out.push_back({i, es[i + 3]});
    return out;
}
struct HostBits {
    const std::vector<u8>* es;
    std::size_t pos;  // bits
    u32 peek(u32 n) const {
        u32 v = 0;
        for (u32 k = 0; k < n; ++k) {
            const std::size_t b = pos + k;
            const u32 bit = (b / 8 < es->size()) ? ((*es)[b / 8] >> (7 - b % 8)) & 1u : 0u;
            v = (v << 1) | bit;
        }
        return v;
    }
    u32 next(u32 n) {
        const u32 v = peek(n);
        pos += n;
        return v;
    }
};
// The IPU bit reader stood in by a host reader over the stream (one per world, from the same position), and the
// extension handlers as recorders.
WorldSetup bit_world(std::shared_ptr<const std::vector<u8>> es, std::size_t bitpos, Machine& m, std::size_t* end_pos = nullptr) {
    std::vector<u32> handlers;
    for (u32 i = 0; i < 11; ++i) handlers.push_back(r32(m, kExtTable + 4 * i));
    return [es, bitpos, handlers, end_pos](StandInWorld& w) {
        auto st = std::make_shared<HostBits>(HostBits{es.get(), bitpos});
        auto keep = es;
        w.si.install(kNextBit, "_sceMpegNextBit", [st, keep, end_pos](EEContext&, StandIns&, StandInCall& c) {
            c.v0 = st->next(uv(c.args[1]));
            if (end_pos) *end_pos = st->pos;
        }, 4);
        w.si.install(kPeepBit, "_sceMpegPeepBit", [st](EEContext&, StandIns&, StandInCall& c) { c.v0 = st->peek(uv(c.args[1])); }, 4);
        w.si.install(kFlushBuf, "j__sceMpegFlushBuf_0", [st, end_pos](EEContext&, StandIns&, StandInCall& c) {
            st->pos += uv(c.args[1]);
            if (end_pos) *end_pos = st->pos;
        }, 4);
        w.si.install(kFlushByte, "flushByteBoundary", [st, end_pos](EEContext&, StandIns&, StandInCall&) {
            st->pos = (st->pos + 7) & ~std::size_t{7};
            if (end_pos) *end_pos = st->pos;
        }, 4);
        w.si.install(kMpegError, "_sceMpegError", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, uv(c.args[1])); }, 3);
        w.si.install(kMpegError1, "_sceMpegError1", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, uv(c.args[1])); }, 3);
        for (u32 i = 0; i < handlers.size(); ++i)
            if (handlers[i] && !w.si.has(handlers[i])) w.si.install_recorder(handlers[i], "ext_handler_" + std::to_string(i), 0, 3);
    };
}
}  // namespace

TEST_CASE("game(cri2): MPEG GOP / picture headers and the extension walker on the disc's .sfd video streams") {
    auto m = machine();
    if (!m) return;
    const auto files = disc_files(".SFD");
    if (files.empty()) {
        MESSAGE("SKIP: no .sfd files under extracted/");
        return;
    }
    int gops = 0, pics = 0, movies = 0;
    std::map<u32, int> types;
    for (std::size_t fi = 0; fi < files.size(); fi += 6) {
        auto es = std::make_shared<const std::vector<u8>>(demux_video(read_head(files[fi], 3u << 20)));
        const auto codes = start_codes(*es);
        if (codes.empty()) continue;
        ++movies;
        INFO(files[fi].filename().string());
        zero(*m, kState, 0x900);
        // the temporal-reference bookkeeping, carried picture to picture (the recompiled run's memory stays)
        u32 gop_base = 0, gop_max = 0;
        int done = 0;
        for (std::size_t k = 0; k < codes.size() && done < 40; ++k) {
            const auto [off, code] = codes[k];
            const std::size_t bitpos = (off + 4) * 8;
            if (code == 0xB8) {
                HostBits hb{es.get(), bitpos};
                hb.next(25);
                const u32 closed = hb.next(1), broken = hb.next(1);
                std::size_t end = 0;
                pr_si(*m, 0x4FF190, {kState, 0, 0, 0}, bit_world(es, bitpos, *m, &end));
                CHECK(r32(*m, kState + mp::kClosedGop) == closed);
                CHECK(r32(*m, kState + mp::kBrokenLink) == broken);
                gop_base = gop_max + 1;
                CHECK(r32(*m, kState + mp::kGopBase) == gop_base);
                CHECK(r32(*m, kState + mp::kGopFirst) == 1);
                CHECK(r32(*m, kState + mp::kBrokenLinkPend) == 0);
                ++gops;
                ++done;
            } else if (code == 0x00) {
                HostBits hb{es.get(), bitpos};
                const u32 tr = hb.next(10), type = hb.next(3);
                hb.next(16);
                u32 ffc = 0, bfc = 0;
                if (type == 2 || type == 3) {
                    hb.next(1);
                    ffc = hb.next(3);
                }
                if (type == 3) {
                    hb.next(1);
                    bfc = hb.next(3);
                }
                // where the walker must stop: the first start code after the header that is not an extension / user data
                std::size_t stop = 0;
                for (std::size_t j = k + 1; j < codes.size(); ++j)
                    if (codes[j].second != 0xB5 && codes[j].second != 0xB2) {
                        stop = codes[j].first * 8;
                        break;
                    }
                if (stop == 0) break;
                std::size_t end = 0;
                const SiResult r = pr_si(*m, 0x4FF230, {kState, 0, 0, 0}, bit_world(es, bitpos, *m, &end));
                CHECK(r32(*m, kState + mp::kPicType) == type);
                if (type == 2 || type == 3) CHECK(r32(*m, kState + mp::kFwdFcode) == ffc);
                if (type == 3) CHECK(r32(*m, kState + mp::kBwdFcode) == bfc);
                // the absolute temporal reference: this GOP's base + temporal_reference; the highest one kept
                CHECK(r32(*m, kState + mp::kTempRef) == gop_base + tr);
                gop_max = std::max(gop_max, gop_base + tr);
                CHECK(r32(*m, kState + mp::kGopMax) == gop_max);
                // the reader left at the next slice / header start code (peeked, not consumed)
                CHECK(end == stop);
                const auto peeks = calls_to(r.log, kPeepBit);
                REQUIRE_FALSE(peeks.empty());
                // the extensions met were dispatched by their id
                ++types[type];
                ++pics;
                ++done;
            }
        }
    }
    CHECK(movies > 0);
    CHECK(pics > 0);
    MESSAGE("MPEG headers: " << movies << " movies, " << gops << " GOP headers, " << pics << " picture headers (I "
                             << types[1] << ", P " << types[2] << ", B " << types[3] << "); " << summary());
}

TEST_CASE("game(cri2): MPEG extension / user-data walker on built streams (dispatch by id, the abort flag)") {
    auto m = machine();
    if (!m) return;
    // after a header: 3 junk bytes, an extension (id 8: picture coding), user data, an extension with an id past 10
    // (dispatched to entry 0), then a slice start code
    std::vector<u8> s = {0x12, 0x34, 0x56, 0, 0, 1, 0xB5, 0x8F, 0xFF, 0xAA, 0, 0, 1, 0xB2, 'U', 'D', 0, 0, 1, 0xB5, 0xF1,
                         0x00, 0, 0, 1, 0x01, 0xEE};
    auto es = std::make_shared<const std::vector<u8>>(s);
    zero(*m, kState, 0x900);
    std::size_t end = 0;
    SiResult r = pr_si(*m, 0x4FF7C8, {kState, 0, 0, 0}, bit_world(es, 3, *m, &end));
    const u32 h8 = r32(*m, kExtTable + 4 * 8), h0 = r32(*m, kExtTable);
    CHECK(calls_to(r.log, h8).size() == 1);
    CHECK(calls_to(r.log, h0).size() == 1);
    CHECK(end == 22 * 8);  // stopped at the slice start code
    // the abort flag ends the byte search at once
    w32(*m, kState + mp::kAbort, 1);
    r = pr_si(*m, 0x4FF7C8, {kState, 0, 0, 0}, bit_world(es, 3, *m, &end));
    CHECK(calls_to(r.log, h8).empty());
    w32(*m, kState + mp::kAbort, 0);
    // flushBuf32 drops a start code
    r = pr_si(*m, 0x4FFB30, {kState, 0, 0, 0}, bit_world(es, 24, *m, &end));
    CHECK(end == 24 + 32);
    MESSAGE("extension walker: " << summary());
}

TEST_CASE("game(cri2): MPEG sequence buffers (_initSeq) for the movies' sizes and both buffer types") {
    auto m = machine();
    if (!m) return;
    constexpr u32 kOuter = kRec + 0x1000;
    static constexpr u32 kMpegArena = 0x01900000u;
    const WorldSetup world = [](StandInWorld& w) {
        auto next = std::make_shared<u32>(kMpegArena);
        w.si.install(0x5010A0u, "_sceMpegAlalcAlloc", [next](EEContext&, StandIns&, StandInCall& c) {
            const u32 size = uv(c.args[2]);
            c.v0 = *next;
            *next += (size + 63) & ~63u;
            c.extra = size;
        }, 3);
        w.si.install_recorder(0x501090u, "_sceMpegAlalcFree", 0, 2);
    };
    struct Seq {
        u32 w, h, mpeg2, prog, buftype;
    };
    const Seq seqs[] = {{640, 448, 0, 0, 0}, {512, 448, 0, 0, 1}, {320, 240, 1, 1, 0}, {720, 480, 1, 0, 2}, {16, 16, 0, 0, 0}};
    for (const Seq& q : seqs) {
        INFO(q.w << "x" << q.h << " mpeg2 " << q.mpeg2 << " prog " << q.prog << " buf " << q.buftype);
        zero(*m, kState, 0x900);
        zero(*m, kOuter, 0x100);
        w32(*m, kOuter + mp::kInner, kState);
        w32(*m, kState + mp::kHsize, q.w);
        w32(*m, kState + mp::kVsize, q.h);
        w32(*m, kState + mp::kMpeg2, q.mpeg2);
        w32(*m, kState + mp::kProgSeq, q.prog);
        w32(*m, kState + mp::kBufType, q.buftype);
        SiResult r = pr_si(*m, 0x4FEBC8, {kOuter, 0, 0, 0}, world);
        const u32 mbw = (q.w + 15) >> 4;
        const u32 prog = q.mpeg2 ? q.prog : 1;
        const u32 mbh = prog ? (q.h + 15) >> 4 : 2 * ((q.h + 31) >> 5);
        CHECK(r32(*m, kState + mp::kMbWidth) == mbw);
        CHECK(r32(*m, kState + mp::kMbHeight) == mbh);
        if (!q.mpeg2) {  // the MPEG-1 defaults: a frame picture, progressive
            CHECK(r32(*m, kState + mp::kPicStruct) == 3);
            CHECK(r32(*m, kState + mp::kProgSeq) == 1);
        }
        CHECK(r32(*m, kOuter) == 16 * mbw);
        CHECK(r32(*m, kOuter + 4) == 16 * mbh);
        const auto allocs = calls_to(r.log, 0x5010A0u);
        REQUIRE(allocs.size() == 3);
        for (const auto& a : allocs) CHECK(a.extra == (16 * mbw * 384 * 16 * mbh) >> 8);
        // the three frames; uncached addresses for buffer type 0
        const u32 f0 = kMpegArena, step = ((((16 * mbw * 384 * 16 * mbh) >> 8) + 63) & ~63u);
        CHECK(r32(*m, kState + mp::kRefBuf0) == f0);
        CHECK(r32(*m, kState + mp::kRefBuf1) == f0 + step);
        CHECK(r32(*m, kState + mp::kRefBuf2) == f0 + 2 * step);
        const u32 desc0 = r32(*m, kState + 504);
        if (q.buftype == 0) CHECK(desc0 == ((f0 & 0x0FFFFFFFu) | 0x20000000u));
        if (q.buftype == 1) CHECK(desc0 == f0);
        CHECK(r32(*m, kState + 508) == 16 * mbw);
        CHECK(r32(*m, kState + 512) == 16 * mbh);
        CHECK(r32(*m, kState + 516) == mbw);
        CHECK(r32(*m, kState + 520) == mbh);
        // the same size again: nothing reallocated
        r = pr_si(*m, 0x4FEBC8, {kOuter, 0, 0, 0}, world);
        CHECK(calls_to(r.log, 0x5010A0u).empty());
    }
    MESSAGE("sequence buffers: " << summary());
}

TEST_CASE("game(cri2): MPEG residual add and the reference-fetch kernels") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0xC0FFEE};
    // _copyAddRefImage: dst[i] = clamp(a[i] + b[i] (16-bit), 0, the table's limit), 384 samples of a macroblock
    u16 lim = 0;
    std::memcpy(&lim, m->at(0x4FDB00u), 2);
    constexpr u32 kDst = kBuf, kA = kBuf + 0x400, kB = kBuf + 0x800;
    for (int it = 0; it < 24; ++it) {
        std::vector<s16> a(384), b(384);
        for (int i = 0; i < 384; ++i) {
            const u32 x = rng();
            const u32 y = rng();
            a[static_cast<std::size_t>(i)] = static_cast<s16>(it < 12 ? static_cast<s32>(x % 256) : static_cast<s32>(x & 0xFFFF));
            b[static_cast<std::size_t>(i)] = static_cast<s16>(it < 12 ? static_cast<s32>(y % 600) - 300 : static_cast<s32>(y & 0xFFFF));
        }
        std::memcpy(m->at(kA), a.data(), 768);
        std::memcpy(m->at(kB), b.data(), 768);
        pr(*m, 0x4FD968, {kDst, kA, kB, 0});
        for (int i = 0; i < 384; ++i) {
            const s16 sum = static_cast<s16>(a[static_cast<std::size_t>(i)] + b[static_cast<std::size_t>(i)]);
            const s32 v = std::max<s32>(0, std::min<s32>(sum, static_cast<s16>(lim)));
            INFO(i);
            CHECK(r8(*m, kDst + static_cast<u32>(i)) == static_cast<u8>(v & 0xFF));
        }
    }
    // the 16 fetch kernels on parameter blocks {dst, byte shift, rows, rows after the macroblock edge, stride, src0, src1}
    // over a random reference area; the luma kernel without half-pel or averaging against a host copy
    constexpr u32 kRef = kBuf + 0x1000, kPar = kBuf + 0xF00, kOutK = kBuf + 0x8000;
    for (u32 i = 0; i < 0x6000; i += 4) {
        const u32 v = rng();
        w32(*m, kRef + i, v);
    }
    const u32 kernels[16] = {0x4FDC98, 0x4FDD10, 0x4FDDA8, 0x4FDE60, 0x4FDF30, 0x4FDFE0, 0x4FE098, 0x4FE190,
                             0x4FE290, 0x4FE330, 0x4FE3E0, 0x4FE4C0, 0x4FE5A8, 0x4FE680, 0x4FE750, 0x4FE870};
    for (u32 k = 0; k < 16; ++k) {
        for (int it = 0; it < 12; ++it) {
            const bool chroma = (k & 1) != 0;
            const u32 shift = rng() % 16;
            const u32 rdraw = rng();
            const u32 rows = chroma ? 1 + rdraw % 8 : 1 + rdraw % 16;
            const u32 r2a = rng();
            const u32 r2b = rng();
            const u32 rows2 = r2a % 3 == 0 ? r2b % 4 : 0;
            const u32 src = kRef + 16 * (rng() % 64);
            zero(*m, kOutK, 0x800);
            w32(*m, kPar + 0, kOutK);
            w32(*m, kPar + 4, shift);
            w32(*m, kPar + 8, rows);
            w32(*m, kPar + 12, rows2);
            w32(*m, kPar + 16, 16);
            w32(*m, kPar + 20, src);
            w32(*m, kPar + 24, src + 16);
            pr(*m, kernels[k], {kPar, 0, 0, 0});
            if (k == 0 && rows2 == 0) {
                for (u32 r = 0; r < rows; ++r)
                    for (u32 j = 0; j < 16; ++j) {
                        const u32 sidx = shift + j;
                        const u8 want = sidx < 16 ? r8(*m, src + 16 * r + sidx) : r8(*m, src + 16 + 16 * r + sidx - 16);
                        u16 got;
                        std::memcpy(&got, m->at(kOutK + 32 * r + 2 * j), 2);
                        INFO("row " << r << " col " << j << " shift " << shift);
                        CHECK(got == want);
                    }
            }
        }
    }
    MESSAGE("kernels: " << summary());
}

namespace {
// a decoder state with three frame descriptors (12 words each 104 bytes apart, the layout _initSeq writes)
void build_mpeg_state(Machine& m, u32 picstruct, u32 pictype) {
    zero(m, kState, 0x900);
    for (u32 d = 0; d < 12; ++d) {
        const u32 desc = kState + 504 + 104 * d;
        w32(m, desc, 0x01900000u + 0x10000u * d);
        w32(m, desc + 4, 640);
        w32(m, desc + 8, 448);
        w32(m, desc + 12, 40);
        w32(m, desc + 16, 28);
    }
    // the reference slots point at the descriptors: forward / backward / current for frame, top and bottom
    for (u32 s = 0; s < 3; ++s) {
        w32(m, kState + mp::kRefFwd + 16 * s, kState + 504 + 104 * (4 * s + 0));
        w32(m, kState + mp::kRefBwd + 16 * s, kState + 504 + 104 * (4 * s + 1));
        w32(m, kState + mp::kRefCur + 16 * s, kState + 504 + 104 * (4 * s + 2));
        w32(m, kState + mp::kRefCur + 4 + 16 * s, kState + 504 + 104 * (4 * s + 3));  // the B-picture slot
    }
    w32(m, kState + mp::kPicStruct, picstruct);
    w32(m, kState + mp::kPicType, pictype);
    w32(m, kState + mp::kMpeg2, 1);
    w64(m, kState + mp::kPts, 0x1122334455667788ull);
    w64(m, kState + mp::kDts, 0x0102030405060708ull);
}
WorldSetup mpeg_world(std::vector<s32> headers = {}, u64 picdata = 1) {
    return [headers, picdata](StandInWorld& w) {
        auto idx = std::make_shared<std::size_t>(0);
        w.si.install(0x4FF9D8u, "_sceMpegNextHeader", [headers, idx](EEContext&, StandIns&, StandInCall& c) {
            c.v0 = sx64(*idx < headers.size() ? headers[(*idx)++] : -1);
        }, 4);
        w.si.install_recorder(0x4FC168u, "_sceMpegPictureData0", picdata, 4);
        w.si.install_recorder(0x501BA8u, "_sceMpegOutputFrame", 0, 4);
        w.si.install_recorder(0x500858u, "_decodeOrSkipField", 1, 4);
        w.si.install_recorder(0x501AE8u, "_sceMpegFlush", 0, 4);
        w.si.install_recorder(0x501178u, "_cpr8", 0, 4);
        w.si.install_recorder(0x501DF8u, "_sceMpegCscStoreRefImage", 0, 4);
        w.si.install_recorder(0x4FAFE0u, "_dualPrimeVector", 0, 4);
        w.si.install(kMpegError, "_sceMpegError", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, uv(c.args[1])); }, 3);
        w.si.install(kMpegError1, "_sceMpegError1", [](EEContext& ctx, StandIns&, StandInCall& c) { c.text = gstr(ctx, uv(c.args[1])); }, 3);
    };
}
}  // namespace

TEST_CASE("game(cri2): MPEG reference rotation, picture decode, skipped macroblocks, the picture loop") {
    auto m = machine();
    if (!m) return;
    // _updateRefImage: an I / P picture (not a second field) swaps forward and backward of all three slots; the
    // current descriptor gets the picture's parameters (PTS, DTS, type, structure ...) and is marked incomplete
    for (u32 type : {1u, 2u, 3u}) {
        build_mpeg_state(*m, 3, type);
        const u32 f[3] = {r32(*m, kState + mp::kRefFwd), r32(*m, kState + mp::kRefFwd + 16), r32(*m, kState + mp::kRefFwd + 32)};
        const u32 b[3] = {r32(*m, kState + mp::kRefBwd), r32(*m, kState + mp::kRefBwd + 16), r32(*m, kState + mp::kRefBwd + 32)};
        w32(*m, f[0] + mp::kRefDone, 1);
        w32(*m, b[0] + mp::kRefDone, 1);
        w32(*m, kState + mp::kCntI, 1);
        pr(*m, 0x500430, {kState, 0, 0, 0});
        INFO("type " << type);
        if (type != 3) {
            for (u32 s = 0; s < 3; ++s) {
                CHECK(r32(*m, kState + mp::kRefFwd + 16 * s) == b[s]);
                CHECK(r32(*m, kState + mp::kRefBwd + 16 * s) == f[s]);
                CHECK(r32(*m, kState + mp::kRefCur + 16 * s) == f[s]);
            }
        }
        const u32 cur = r32(*m, kState + mp::kRefCur);
        CHECK(r64(*m, cur + 24) == 0x1122334455667788ull);
        CHECK(r64(*m, cur + 32) == 0x0102030405060708ull);
        CHECK(r32(*m, cur + 44) == type);
        CHECK(r32(*m, cur + 48) == 3);
        CHECK(r32(*m, cur + mp::kRefDone) == 0);
    }
    // _decPicture: the current descriptor by picture structure, marked complete when the data decoded
    for (u32 ps : {1u, 2u, 3u}) {
        build_mpeg_state(*m, ps, 1);
        SiResult r = pr_si(*m, 0x500F98, {kState, 0, 0, 0}, mpeg_world());
        const u32 cur = r32(*m, kState + (ps == 3 ? mp::kRefCur : ps == 1 ? mp::kRefCur + 16 : mp::kRefCur + 32));
        INFO("structure " << ps);
        CHECK(r32(*m, cur + mp::kRefDone) == 1);
        CHECK(calls_to(r.log, 0x4FC168u).size() == 1);
    }
    build_mpeg_state(*m, 3, 1);
    w32(*m, kState + mp::kFieldParity, 1);  // a frame picture after a lone field: reported, parity reset
    SiResult r = pr_si(*m, 0x500F98, {kState, 0, 0, 0}, mpeg_world({}, 0));
    REQUIRE(calls_to(r.log, kMpegError).size() == 1);
    CHECK(calls_to(r.log, kMpegError)[0].text == "odd number of field pictures");
    CHECK(r32(*m, kState + mp::kFieldParity) == 0);
    CHECK(r32(*m, r32(*m, kState + mp::kRefCur) + mp::kRefDone) == 0);
    build_mpeg_state(*m, 7, 1);
    r = pr_si(*m, 0x500F98, {kState, 0, 0, 0}, mpeg_world());
    CHECK(calls_to(r.log, kMpegError)[0].text == "unknown picture sutructure");
    // _decodeOrSkip: frame pictures here, field pictures to _decodeOrSkipField
    constexpr u32 kHandle = kRec + 0x1000;
    zero(*m, kHandle, 0x100);
    w32(*m, kHandle + mp::kInner, kState);
    build_mpeg_state(*m, 1, 1);
    r = pr_si(*m, 0x500E00, {kHandle, 0, static_cast<u64>(-1), 0}, mpeg_world());
    CHECK(calls_to(r.log, 0x500858u).size() == 1);
    build_mpeg_state(*m, 3, 1);
    r = pr_si(*m, 0x500E00, {kHandle, 0, static_cast<u64>(-1), 0}, mpeg_world());
    CHECK(calls_to(r.log, 0x500858u).empty());
    CHECK(calls_to(r.log, 0x501BA8u).size() == 1);  // decoded, then the output
    build_mpeg_state(*m, 3, 1);
    r = pr_si(*m, 0x5006E8, {kHandle, 0, static_cast<u64>(-1), 0}, mpeg_world());  // the frame path on its own
    CHECK(calls_to(r.log, 0x4FC168u).size() == 1);
    build_mpeg_state(*m, 3, 3);
    r = pr_si(*m, 0x5006E8, {kHandle, 5, 2, 0}, mpeg_world());  // past the type's limit: skipped, no decode
    CHECK(calls_to(r.log, 0x4FC168u).empty());
    CHECK(r32(*m, kState + mp::kDecFrame) == 1);
    // _skipMB0: P pictures reset the vectors; the motion type by structure; I pictures may not skip
    for (u32 type : {1u, 2u, 3u})
        for (u32 ps : {2u, 3u}) {
            build_mpeg_state(*m, ps, type);
            constexpr u32 kVec = kOut, kMt = kOut + 0x40, kDmv = kOut + 0x50, kFlags = kOut + 0x60;
            for (u32 i = 0; i < 8; ++i) w32(*m, kVec + 4 * i, 0x100 + i);
            w32(*m, kFlags, 0xF);
            r = pr_si(*m, 0x4FD8A8, {kState, kVec, kMt, kDmv}, mpeg_world(), tregs(kFlags));
            INFO("type " << type << " structure " << ps);
            CHECK(r32(*m, kState + mp::kSkipped) == 1);
            CHECK(r32(*m, kFlags) == 0xE);
            CHECK(r32(*m, kMt) == (ps == 3 ? 2u : 1u));
            if (type == 2) {
                CHECK(r32(*m, kVec) == 0);
                CHECK(r32(*m, kVec + 4) == 0);
                CHECK(r32(*m, kVec + 16) == 0);
                CHECK(r32(*m, kVec + 20) == 0);
            }
            CHECK(sv(r.v0) == (type == 1 ? 0 : 1));
            CHECK(calls_to(r.log, kMpegError).size() == (type == 1 ? 1u : 0u));
        }
    // _getpic: an unaligned image buffer is refused; the loop decodes by picture type until the stream ends
    build_mpeg_state(*m, 3, 1);
    w32(*m, kState + mp::kImageBuf, 0x01A00004u);
    r = pr_si(*m, 0x500278, {kHandle, 0, 0, 0}, mpeg_world({1, 2, 3}));
    CHECK(sv(r.v0) == -1);
    REQUIRE(calls_to(r.log, kMpegError1).size() == 1);
    w32(*m, kState + mp::kImageBuf, 0x01A00000u);
    w32(*m, kState + mp::kPicStructWanted, 3);
    w32(*m, kState + mp::kSkipI, static_cast<u32>(-1));
    w32(*m, kState + mp::kSkipP, static_cast<u32>(-1));
    w32(*m, kState + mp::kSkipB, static_cast<u32>(-1));
    r = pr_si(*m, 0x500278, {kHandle, 0, 0, 0}, mpeg_world({1, 2, 3, 3, 2}));
    CHECK(sv(r.v0) == -1);  // the headers ran out
    CHECK(calls_to(r.log, 0x4FF9D8u).size() == 6);
    MESSAGE("MPEG picture loop: " << summary());
}

TEST_CASE("game(cri2): MPEG motion-compensation set-up (_getAllRefs / _getRef0) and the display hand-off") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0xBEEF};
    constexpr u32 kVec = kOut, kSel = kOut + 0x40;
    int n = 0;
    for (u32 ps : {1u, 2u, 3u})
        for (u32 type : {2u, 3u})
            for (u32 mtype : {1u, 2u, 3u})
                for (u32 flags : {4u, 8u, 12u}) {
                    build_mpeg_state(*m, ps, type);
                    w32(*m, kState + 2080, 0);
                    w32(*m, kState + 2096, 0x01980000u);  // the prediction output area
                    for (u32 i = 0; i < 8; ++i) {
                        const u32 v = rng();
                        w32(*m, kVec + 4 * i, (v % 64) - 32);
                    }
                    for (u32 i = 0; i < 4; ++i) {
                        const u32 v = rng();
                        w32(*m, kSel + 4 * i, v & 1);
                    }
                    const u32 mbx = rng() % 30;
                    const u32 mby = rng() % 20;
                    const SiResult r = pr_si(*m, 0x4FB168, {kState, 16 * mbx, 16 * mby, flags}, mpeg_world(),
                                             tregs(mtype, kVec, kSel, 0));
                    if (!(flags & 4)) CHECK(sv(r.v0) == 3);  // no backward prediction: 3
                    ++n;
                }
    // _getRef0 directly: the luma / chroma kernels chosen by (averaging, x half-pel, y half-pel)
    for (int it = 0; it < 48; ++it) {
        build_mpeg_state(*m, 3, 2);
        w32(*m, kState + 2080, 0);
        w32(*m, kState + 2096, 0x01980000u);
        const u32 vx = rng() % 64;
        const u32 vy = rng() % 64;
        const u32 avg = rng() & 1;
        const u32 desc = r32(*m, kState + mp::kRefFwd);
        pr(*m, 0x4FBAC0, {kState, desc, 0, 0}, tregs(0, 16, 32, 48), {vx, vy, 0, avg});
        const u32 slot = r32(*m, kState + 1740) - 1;  // the fetch count, incremented
        const u32 luma = r32(*m, kState + 1480 + 4 * slot);
        const u32 chroma = r32(*m, kState + 1496 + 4 * slot);
        INFO("vx " << vx << " vy " << vy << " avg " << avg);
        CHECK(luma == r32(*m, 0x77F2F8u + 4 * ((avg << 2) | ((vx & 1) << 1) | (vy & 1))));
        CHECK(chroma == r32(*m, 0x77F318u + 4 * ((avg << 2) | (((vx / 2) & 1) << 1) | ((vy / 2) & 1))));
    }
    // _dispRefImage: a complete picture that fits the buffer is converted / copied and marks the picture shown
    for (u32 csc : {0u, 1u}) {
        build_mpeg_state(*m, 3, 1);
        const u32 cur = r32(*m, kState + mp::kRefCur);
        w32(*m, cur + mp::kRefDone, 1);
        w64(*m, cur + 24, 0x1122334455667788ull);  // the picture's PTS (what _updateRefImage copies in)
        w32(*m, kState + mp::kOutInfo, kOut);
        zero(*m, kOut, 0x40);
        w32(*m, kState + 248, 0x7FFFFFFF);   // the image buffer's size
        w32(*m, kState + 196, csc);
        const SiResult r = pr_si(*m, 0x501408, {kState, cur, 0, 0}, mpeg_world());
        CHECK(r32(*m, kState + mp::kPicDone) == 1);
        CHECK(calls_to(r.log, csc ? 0x501DF8u : 0x501178u).size() == 1);
        CHECK(r64(*m, kOut + 16) == 0x1122334455667788ull);  // the PTS handed on
    }
    build_mpeg_state(*m, 3, 1);
    w32(*m, kState + mp::kOutInfo, kOut);
    w32(*m, kState + 248, 16);  // too small: reported through the error callback (the text from sceSnprintf)
    const u32 cur = r32(*m, kState + mp::kRefCur);
    w32(*m, cur + 12, 40);
    w32(*m, cur + 16, 28);
    const SiResult r = pr_si(*m, 0x501408, {kState, cur, 0, 0}, mpeg_world());
    REQUIRE(calls_to(r.log, kMpegError).size() == 1);
    CHECK(calls_to(r.log, kMpegError)[0].text.find("640x448") != std::string::npos);
    MESSAGE("motion compensation: " << n << " macroblocks; " << summary());
}

TEST_CASE("game(cri2): coverage of the meaningful sections") {
    // every function of the slice was paired at least once outside the generic sweep (the test cases above ran first)
    std::vector<std::string> missing;
    for (const Case& c : kCases)
        if (!g_pairs.count(c.name)) missing.push_back(c.name);
    std::string s;
    for (const auto& n : missing) s += n + " ";
    INFO("not paired on meaningful inputs: " << s);
    CHECK(missing.size() <= 12);
    MESSAGE("meaningful pairs: " << summary() << "; without one: " << missing.size());
}

#else

TEST_CASE("game(cri2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
