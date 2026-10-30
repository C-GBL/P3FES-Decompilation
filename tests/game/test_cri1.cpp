// Pair tests for slice cri1 (game/src/cri/cri1_*.cpp: the CRI middleware's pure parts). Every body against its
// recompiled body, compared by tests/game/handgen_pairs.h (the whole register file and cycle count at every check point
// and at the return / stop, all 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window, the bus log) or, where
// a callee is not emitted here, by stand_ins.h's run_pair_si (the same, plus the stand-ins' call logs). On top of the
// generic sweep (random worlds), each family runs on meaningful inputs with documented-rule checks on the host:
//   * every .adx file of the disc (read from extracted/ at run time; no audio is committed): the header parsers against
//     the public ADX header layout (data offset, codec fields, rate, samples, version, cutoff, histories, loop record);
//   * the ADPCM decoders on real blocks of one file of each kind (mono / stereo, version 3 / 4, 24 / 48 kHz), through
//     the decoder objects as the library drives them, PCM compared sample for sample with a host decoder written from
//     the public ADX format (the plain and the downmix stereo paths), plus random blocks, the running key, odd counts;
//   * the coefficients against the public formula;
//   * the stream joints SJRBF / SJMEM / SJUNI against host models of their rules (chunk sizes, positions modulo the
//     size, the extra area's mirroring, unget, merge / split, node pools, conservation of bytes);
//   * the SVM lock depth / type and error texts, cvFs init, upper-casing, path splitting, default device;
//   * the replay snapshots' live stream joints, decoder objects and device table.
// Random draws are separate statements (MSVC and clang evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/cri1.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <filesystem>
#include <fstream>
#include <map>
#include <cstdlib>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_538EF0_00538ef0(EEContext&);  // generated body
void fn_sub_538EF0_00538ef0__recomp(EEContext&);  // recompiled
void fn_sub_538F18_00538f18(EEContext&);  // generated body
void fn_sub_538F18_00538f18__recomp(EEContext&);  // recompiled
void fn_sub_539148_00539148(EEContext&);  // generated body
void fn_sub_539148_00539148__recomp(EEContext&);  // recompiled
void fn_sub_5396F8_005396f8(EEContext&);  // generated body
void fn_sub_5396F8_005396f8__recomp(EEContext&);  // recompiled
void fn_sub_5397B8_005397b8(EEContext&);  // generated body
void fn_sub_5397B8_005397b8__recomp(EEContext&);  // recompiled
void fn_sub_5397E8_005397e8(EEContext&);  // generated body
void fn_sub_5397E8_005397e8__recomp(EEContext&);  // recompiled
void fn_sub_539848_00539848(EEContext&);  // generated body
void fn_sub_539848_00539848__recomp(EEContext&);  // recompiled
void fn_sub_539850_00539850(EEContext&);  // generated body
void fn_sub_539850_00539850__recomp(EEContext&);  // recompiled
void fn_sub_539858_00539858(EEContext&);  // generated body
void fn_sub_539858_00539858__recomp(EEContext&);  // recompiled
void fn_sub_5399B8_005399b8(EEContext&);  // generated body
void fn_sub_5399B8_005399b8__recomp(EEContext&);  // recompiled
void fn_sub_539A38_00539a38(EEContext&);  // generated body
void fn_sub_539A38_00539a38__recomp(EEContext&);  // recompiled
void fn_sub_539AE0_00539ae0(EEContext&);  // generated body
void fn_sub_539AE0_00539ae0__recomp(EEContext&);  // recompiled
void fn_sub_539BE0_00539be0(EEContext&);  // generated body
void fn_sub_539BE0_00539be0__recomp(EEContext&);  // recompiled
void fn_sub_539C60_00539c60(EEContext&);  // generated body
void fn_sub_539C60_00539c60__recomp(EEContext&);  // recompiled
void fn_sub_539CD8_00539cd8(EEContext&);  // generated body
void fn_sub_539CD8_00539cd8__recomp(EEContext&);  // recompiled
void fn_sub_539E10_00539e10(EEContext&);  // generated body
void fn_sub_539E10_00539e10__recomp(EEContext&);  // recompiled
void fn_sub_539ED8_00539ed8(EEContext&);  // generated body
void fn_sub_539ED8_00539ed8__recomp(EEContext&);  // recompiled
void fn_sub_53A138_0053a138(EEContext&);  // generated body
void fn_sub_53A138_0053a138__recomp(EEContext&);  // recompiled
void fn__get_peer_or_sock_name_3_0053a358(EEContext&);  // generated body
void fn__get_peer_or_sock_name_3_0053a358__recomp(EEContext&);  // recompiled
void fn_sub_53A3B8_0053a3b8(EEContext&);  // generated body
void fn_sub_53A3B8_0053a3b8__recomp(EEContext&);  // recompiled
void fn_sub_53A410_0053a410(EEContext&);  // generated body
void fn_sub_53A410_0053a410__recomp(EEContext&);  // recompiled
void fn_sub_53AD00_0053ad00(EEContext&);  // generated body
void fn_sub_53AD00_0053ad00__recomp(EEContext&);  // recompiled
void fn_sub_54CB78_0054cb78(EEContext&);  // generated body
void fn_sub_54CB78_0054cb78__recomp(EEContext&);  // recompiled
void fn_sub_54CBA0_0054cba0(EEContext&);  // generated body
void fn_sub_54CBA0_0054cba0__recomp(EEContext&);  // recompiled
void fn_sub_54CBC8_0054cbc8(EEContext&);  // generated body
void fn_sub_54CBC8_0054cbc8__recomp(EEContext&);  // recompiled
void fn_sub_54CC98_0054cc98(EEContext&);  // generated body
void fn_sub_54CC98_0054cc98__recomp(EEContext&);  // recompiled
void fn_sub_54CCC0_0054ccc0(EEContext&);  // generated body
void fn_sub_54CCC0_0054ccc0__recomp(EEContext&);  // recompiled
void fn_sub_54CCE8_0054cce8(EEContext&);  // generated body
void fn_sub_54CCE8_0054cce8__recomp(EEContext&);  // recompiled
void fn_sub_54CD10_0054cd10(EEContext&);  // generated body
void fn_sub_54CD10_0054cd10__recomp(EEContext&);  // recompiled
void fn_sub_54CD40_0054cd40(EEContext&);  // generated body
void fn_sub_54CD40_0054cd40__recomp(EEContext&);  // recompiled
void fn_sub_54CD78_0054cd78(EEContext&);  // generated body
void fn_sub_54CD78_0054cd78__recomp(EEContext&);  // recompiled
void fn_sub_54CD80_0054cd80(EEContext&);  // generated body
void fn_sub_54CD80_0054cd80__recomp(EEContext&);  // recompiled
void fn_sub_54CD88_0054cd88(EEContext&);  // generated body
void fn_sub_54CD88_0054cd88__recomp(EEContext&);  // recompiled
void fn_sub_54CDB8_0054cdb8(EEContext&);  // generated body
void fn_sub_54CDB8_0054cdb8__recomp(EEContext&);  // recompiled
void fn_sub_54CDE8_0054cde8(EEContext&);  // generated body
void fn_sub_54CDE8_0054cde8__recomp(EEContext&);  // recompiled
void fn_sub_54CE38_0054ce38(EEContext&);  // generated body
void fn_sub_54CE38_0054ce38__recomp(EEContext&);  // recompiled
void fn_sub_54CE60_0054ce60(EEContext&);  // generated body
void fn_sub_54CE60_0054ce60__recomp(EEContext&);  // recompiled
void fn_sub_54CE78_0054ce78(EEContext&);  // generated body
void fn_sub_54CE78_0054ce78__recomp(EEContext&);  // recompiled
void fn_sub_54CE80_0054ce80(EEContext&);  // generated body
void fn_sub_54CE80_0054ce80__recomp(EEContext&);  // recompiled
void fn_sub_54CE90_0054ce90(EEContext&);  // generated body
void fn_sub_54CE90_0054ce90__recomp(EEContext&);  // recompiled
void fn_sub_54CF88_0054cf88(EEContext&);  // generated body
void fn_sub_54CF88_0054cf88__recomp(EEContext&);  // recompiled
void fn_sub_561758_00561758(EEContext&);  // generated body
void fn_sub_561758_00561758__recomp(EEContext&);  // recompiled
void fn_sub_5617C0_005617c0(EEContext&);  // generated body
void fn_sub_5617C0_005617c0__recomp(EEContext&);  // recompiled
void fn_sub_5617D8_005617d8(EEContext&);  // generated body
void fn_sub_5617D8_005617d8__recomp(EEContext&);  // recompiled
void fn_sub_5617F0_005617f0(EEContext&);  // generated body
void fn_sub_5617F0_005617f0__recomp(EEContext&);  // recompiled
void fn_sub_561808_00561808(EEContext&);  // generated body
void fn_sub_561808_00561808__recomp(EEContext&);  // recompiled
void fn_sub_561828_00561828(EEContext&);  // generated body
void fn_sub_561828_00561828__recomp(EEContext&);  // recompiled
void fn_sub_561870_00561870(EEContext&);  // generated body
void fn_sub_561870_00561870__recomp(EEContext&);  // recompiled
void fn_sub_5618A0_005618a0(EEContext&);  // generated body
void fn_sub_5618A0_005618a0__recomp(EEContext&);  // recompiled
void fn_sub_5618F0_005618f0(EEContext&);  // generated body
void fn_sub_5618F0_005618f0__recomp(EEContext&);  // recompiled
void fn_sub_561920_00561920(EEContext&);  // generated body
void fn_sub_561920_00561920__recomp(EEContext&);  // recompiled
void fn_sub_561970_00561970(EEContext&);  // generated body
void fn_sub_561970_00561970__recomp(EEContext&);  // recompiled
void fn_sub_5619B8_005619b8(EEContext&);  // generated body
void fn_sub_5619B8_005619b8__recomp(EEContext&);  // recompiled
void fn_sub_561A80_00561a80(EEContext&);  // generated body
void fn_sub_561A80_00561a80__recomp(EEContext&);  // recompiled
void fn_sub_561AB0_00561ab0(EEContext&);  // generated body
void fn_sub_561AB0_00561ab0__recomp(EEContext&);  // recompiled
void fn_sub_561B38_00561b38(EEContext&);  // generated body
void fn_sub_561B38_00561b38__recomp(EEContext&);  // recompiled
void fn_sub_561B70_00561b70(EEContext&);  // generated body
void fn_sub_561B70_00561b70__recomp(EEContext&);  // recompiled
void fn_sub_561BC8_00561bc8(EEContext&);  // generated body
void fn_sub_561BC8_00561bc8__recomp(EEContext&);  // recompiled
void fn_sub_561C18_00561c18(EEContext&);  // generated body
void fn_sub_561C18_00561c18__recomp(EEContext&);  // recompiled
void fn_sub_561C78_00561c78(EEContext&);  // generated body
void fn_sub_561C78_00561c78__recomp(EEContext&);  // recompiled
void fn_sub_561CA8_00561ca8(EEContext&);  // generated body
void fn_sub_561CA8_00561ca8__recomp(EEContext&);  // recompiled
void fn_sub_561D10_00561d10(EEContext&);  // generated body
void fn_sub_561D10_00561d10__recomp(EEContext&);  // recompiled
void fn_sub_561D58_00561d58(EEContext&);  // generated body
void fn_sub_561D58_00561d58__recomp(EEContext&);  // recompiled
void fn_sub_561DB8_00561db8(EEContext&);  // generated body
void fn_sub_561DB8_00561db8__recomp(EEContext&);  // recompiled
void fn_sub_561E98_00561e98(EEContext&);  // generated body
void fn_sub_561E98_00561e98__recomp(EEContext&);  // recompiled
void fn_sub_561EE8_00561ee8(EEContext&);  // generated body
void fn_sub_561EE8_00561ee8__recomp(EEContext&);  // recompiled
void fn_sub_561F88_00561f88(EEContext&);  // generated body
void fn_sub_561F88_00561f88__recomp(EEContext&);  // recompiled
void fn_sub_561FD8_00561fd8(EEContext&);  // generated body
void fn_sub_561FD8_00561fd8__recomp(EEContext&);  // recompiled
void fn_sub_5620D8_005620d8(EEContext&);  // generated body
void fn_sub_5620D8_005620d8__recomp(EEContext&);  // recompiled
void fn_sub_562140_00562140(EEContext&);  // generated body
void fn_sub_562140_00562140__recomp(EEContext&);  // recompiled
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3_00562210(EEContext&);  // generated body
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3_00562210__recomp(EEContext&);  // recompiled
void fn_width__CQ24_STL8ios_base_0_00562218(EEContext&);  // generated body
void fn_width__CQ24_STL8ios_base_0_00562218__recomp(EEContext&);  // recompiled
void fn_sub_562220_00562220(EEContext&);  // generated body
void fn_sub_562220_00562220__recomp(EEContext&);  // recompiled
void fn_sub_562240_00562240(EEContext&);  // generated body
void fn_sub_562240_00562240__recomp(EEContext&);  // recompiled
void fn_sub_562288_00562288(EEContext&);  // generated body
void fn_sub_562288_00562288__recomp(EEContext&);  // recompiled
void fn_sub_5622B8_005622b8(EEContext&);  // generated body
void fn_sub_5622B8_005622b8__recomp(EEContext&);  // recompiled
void fn_sub_562308_00562308(EEContext&);  // generated body
void fn_sub_562308_00562308__recomp(EEContext&);  // recompiled
void fn_sub_562338_00562338(EEContext&);  // generated body
void fn_sub_562338_00562338__recomp(EEContext&);  // recompiled
void fn_sub_562388_00562388(EEContext&);  // generated body
void fn_sub_562388_00562388__recomp(EEContext&);  // recompiled
void fn_sub_5623E0_005623e0(EEContext&);  // generated body
void fn_sub_5623E0_005623e0__recomp(EEContext&);  // recompiled
void fn_sub_5624B0_005624b0(EEContext&);  // generated body
void fn_sub_5624B0_005624b0__recomp(EEContext&);  // recompiled
void fn_sub_5624E0_005624e0(EEContext&);  // generated body
void fn_sub_5624E0_005624e0__recomp(EEContext&);  // recompiled
void fn_sub_562568_00562568(EEContext&);  // generated body
void fn_sub_562568_00562568__recomp(EEContext&);  // recompiled
void fn_sub_562570_00562570(EEContext&);  // generated body
void fn_sub_562570_00562570__recomp(EEContext&);  // recompiled
void fn_sub_562580_00562580(EEContext&);  // generated body
void fn_sub_562580_00562580__recomp(EEContext&);  // recompiled
void fn_sub_5625B0_005625b0(EEContext&);  // generated body
void fn_sub_5625B0_005625b0__recomp(EEContext&);  // recompiled
void fn_sub_562630_00562630(EEContext&);  // generated body
void fn_sub_562630_00562630__recomp(EEContext&);  // recompiled
void fn_sub_562680_00562680(EEContext&);  // generated body
void fn_sub_562680_00562680__recomp(EEContext&);  // recompiled
void fn_sub_5626E0_005626e0(EEContext&);  // generated body
void fn_sub_5626E0_005626e0__recomp(EEContext&);  // recompiled
void fn_sub_562880_00562880(EEContext&);  // generated body
void fn_sub_562880_00562880__recomp(EEContext&);  // recompiled
void fn_sub_5628D0_005628d0(EEContext&);  // generated body
void fn_sub_5628D0_005628d0__recomp(EEContext&);  // recompiled
void fn_sub_562A50_00562a50(EEContext&);  // generated body
void fn_sub_562A50_00562a50__recomp(EEContext&);  // recompiled
void fn_sub_562AA0_00562aa0(EEContext&);  // generated body
void fn_sub_562AA0_00562aa0__recomp(EEContext&);  // recompiled
void fn_sub_562C80_00562c80(EEContext&);  // generated body
void fn_sub_562C80_00562c80__recomp(EEContext&);  // recompiled
void fn_sub_562CE8_00562ce8(EEContext&);  // generated body
void fn_sub_562CE8_00562ce8__recomp(EEContext&);  // recompiled
void fn_sub_562DE0_00562de0(EEContext&);  // generated body
void fn_sub_562DE0_00562de0__recomp(EEContext&);  // recompiled
void fn_sub_562DE8_00562de8(EEContext&);  // generated body
void fn_sub_562DE8_00562de8__recomp(EEContext&);  // recompiled
void fn_sub_562DF0_00562df0(EEContext&);  // generated body
void fn_sub_562DF0_00562df0__recomp(EEContext&);  // recompiled
void fn_sub_562DF8_00562df8(EEContext&);  // generated body
void fn_sub_562DF8_00562df8__recomp(EEContext&);  // recompiled
void fn_sub_562E10_00562e10(EEContext&);  // generated body
void fn_sub_562E10_00562e10__recomp(EEContext&);  // recompiled
void fn_sub_562E28_00562e28(EEContext&);  // generated body
void fn_sub_562E28_00562e28__recomp(EEContext&);  // recompiled
void fn_sub_562E48_00562e48(EEContext&);  // generated body
void fn_sub_562E48_00562e48__recomp(EEContext&);  // recompiled
void fn_sub_562E90_00562e90(EEContext&);  // generated body
void fn_sub_562E90_00562e90__recomp(EEContext&);  // recompiled
void fn_sub_562EC0_00562ec0(EEContext&);  // generated body
void fn_sub_562EC0_00562ec0__recomp(EEContext&);  // recompiled
void fn_sub_562F10_00562f10(EEContext&);  // generated body
void fn_sub_562F10_00562f10__recomp(EEContext&);  // recompiled
void fn_sub_562F40_00562f40(EEContext&);  // generated body
void fn_sub_562F40_00562f40__recomp(EEContext&);  // recompiled
void fn_sub_562F90_00562f90(EEContext&);  // generated body
void fn_sub_562F90_00562f90__recomp(EEContext&);  // recompiled
void fn_sub_562FE8_00562fe8(EEContext&);  // generated body
void fn_sub_562FE8_00562fe8__recomp(EEContext&);  // recompiled
void fn_sub_5630D0_005630d0(EEContext&);  // generated body
void fn_sub_5630D0_005630d0__recomp(EEContext&);  // recompiled
void fn_sub_563100_00563100(EEContext&);  // generated body
void fn_sub_563100_00563100__recomp(EEContext&);  // recompiled
void fn_sub_563188_00563188(EEContext&);  // generated body
void fn_sub_563188_00563188__recomp(EEContext&);  // recompiled
void fn_sub_5631C0_005631c0(EEContext&);  // generated body
void fn_sub_5631C0_005631c0__recomp(EEContext&);  // recompiled
void fn_sub_563218_00563218(EEContext&);  // generated body
void fn_sub_563218_00563218__recomp(EEContext&);  // recompiled
void fn_sub_563268_00563268(EEContext&);  // generated body
void fn_sub_563268_00563268__recomp(EEContext&);  // recompiled
void fn_sub_5632C8_005632c8(EEContext&);  // generated body
void fn_sub_5632C8_005632c8__recomp(EEContext&);  // recompiled
void fn_sub_5632F8_005632f8(EEContext&);  // generated body
void fn_sub_5632F8_005632f8__recomp(EEContext&);  // recompiled
void fn_sub_5633D0_005633d0(EEContext&);  // generated body
void fn_sub_5633D0_005633d0__recomp(EEContext&);  // recompiled
void fn_sub_563418_00563418(EEContext&);  // generated body
void fn_sub_563418_00563418__recomp(EEContext&);  // recompiled
void fn_sub_5634D0_005634d0(EEContext&);  // generated body
void fn_sub_5634D0_005634d0__recomp(EEContext&);  // recompiled
void fn_sub_563530_00563530(EEContext&);  // generated body
void fn_sub_563530_00563530__recomp(EEContext&);  // recompiled
void fn_sub_563680_00563680(EEContext&);  // generated body
void fn_sub_563680_00563680__recomp(EEContext&);  // recompiled
void fn_sub_5636D0_005636d0(EEContext&);  // generated body
void fn_sub_5636D0_005636d0__recomp(EEContext&);  // recompiled
void fn_sub_5637F8_005637f8(EEContext&);  // generated body
void fn_sub_5637F8_005637f8__recomp(EEContext&);  // recompiled
void fn_sub_563848_00563848(EEContext&);  // generated body
void fn_sub_563848_00563848__recomp(EEContext&);  // recompiled
void fn_sub_563968_00563968(EEContext&);  // generated body
void fn_sub_563968_00563968__recomp(EEContext&);  // recompiled
void fn_sub_5639D0_005639d0(EEContext&);  // generated body
void fn_sub_5639D0_005639d0__recomp(EEContext&);  // recompiled
void fn_sub_563A98_00563a98(EEContext&);  // generated body
void fn_sub_563A98_00563a98__recomp(EEContext&);  // recompiled
void fn_sub_563AE0_00563ae0(EEContext&);  // generated body
void fn_sub_563AE0_00563ae0__recomp(EEContext&);  // recompiled
void fn_sub_563B70_00563b70(EEContext&);  // generated body
void fn_sub_563B70_00563b70__recomp(EEContext&);  // recompiled
void fn_sub_563BA8_00563ba8(EEContext&);  // generated body
void fn_sub_563BA8_00563ba8__recomp(EEContext&);  // recompiled
void fn_sub_563C28_00563c28(EEContext&);  // generated body
void fn_sub_563C28_00563c28__recomp(EEContext&);  // recompiled
void fn_sub_564888_00564888(EEContext&);  // generated body
void fn_sub_564888_00564888__recomp(EEContext&);  // recompiled
void fn_sub_5648E8_005648e8(EEContext&);  // generated body
void fn_sub_5648E8_005648e8__recomp(EEContext&);  // recompiled
void fn_sub_564978_00564978(EEContext&);  // generated body
void fn_sub_564978_00564978__recomp(EEContext&);  // recompiled
void fn_sub_564990_00564990(EEContext&);  // generated body
void fn_sub_564990_00564990__recomp(EEContext&);  // recompiled
void fn_sub_5649A8_005649a8(EEContext&);  // generated body
void fn_sub_5649A8_005649a8__recomp(EEContext&);  // recompiled
void fn_sub_5649C0_005649c0(EEContext&);  // generated body
void fn_sub_5649C0_005649c0__recomp(EEContext&);  // recompiled
void fn_sub_5649D8_005649d8(EEContext&);  // generated body
void fn_sub_5649D8_005649d8__recomp(EEContext&);  // recompiled
void fn_sub_5649F0_005649f0(EEContext&);  // generated body
void fn_sub_5649F0_005649f0__recomp(EEContext&);  // recompiled
void fn_sub_564A20_00564a20(EEContext&);  // generated body
void fn_sub_564A20_00564a20__recomp(EEContext&);  // recompiled
void fn_sub_564A38_00564a38(EEContext&);  // generated body
void fn_sub_564A38_00564a38__recomp(EEContext&);  // recompiled
void fn_sub_564A50_00564a50(EEContext&);  // generated body
void fn_sub_564A50_00564a50__recomp(EEContext&);  // recompiled
void fn_sub_564A68_00564a68(EEContext&);  // generated body
void fn_sub_564A68_00564a68__recomp(EEContext&);  // recompiled
void fn_sub_564AA8_00564aa8(EEContext&);  // generated body
void fn_sub_564AA8_00564aa8__recomp(EEContext&);  // recompiled
void fn_sub_564B50_00564b50(EEContext&);  // generated body
void fn_sub_564B50_00564b50__recomp(EEContext&);  // recompiled
void fn_sub_5558E8_005558e8(EEContext&);  // generated body
void fn_sub_5558E8_005558e8__recomp(EEContext&);  // recompiled
void fn_sub_555918_00555918(EEContext&);  // generated body
void fn_sub_555918_00555918__recomp(EEContext&);  // recompiled
void fn_cvFsInit_00555940(EEContext&);  // generated body
void fn_cvFsInit_00555940__recomp(EEContext&);  // recompiled
void fn_sub_555D10_00555d10(EEContext&);  // generated body
void fn_sub_555D10_00555d10__recomp(EEContext&);  // recompiled
void fn_cvfs_getDevName_005561e8(EEContext&);  // generated body
void fn_cvfs_getDevName_005561e8__recomp(EEContext&);  // recompiled
void fn_cvfs_getDefDev_00556330(EEContext&);  // generated body
void fn_cvfs_getDefDev_00556330__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_538EF0", 0x538EF0, &recomp_gen::fn_sub_538EF0_00538ef0, &recomp_gen::fn_sub_538EF0_00538ef0__recomp},
    {"sub_538F18", 0x538F18, &recomp_gen::fn_sub_538F18_00538f18, &recomp_gen::fn_sub_538F18_00538f18__recomp},
    {"sub_539148", 0x539148, &recomp_gen::fn_sub_539148_00539148, &recomp_gen::fn_sub_539148_00539148__recomp},
    {"sub_5396F8", 0x5396F8, &recomp_gen::fn_sub_5396F8_005396f8, &recomp_gen::fn_sub_5396F8_005396f8__recomp},
    {"sub_5397B8", 0x5397B8, &recomp_gen::fn_sub_5397B8_005397b8, &recomp_gen::fn_sub_5397B8_005397b8__recomp},
    {"sub_5397E8", 0x5397E8, &recomp_gen::fn_sub_5397E8_005397e8, &recomp_gen::fn_sub_5397E8_005397e8__recomp},
    {"sub_539848", 0x539848, &recomp_gen::fn_sub_539848_00539848, &recomp_gen::fn_sub_539848_00539848__recomp},
    {"sub_539850", 0x539850, &recomp_gen::fn_sub_539850_00539850, &recomp_gen::fn_sub_539850_00539850__recomp},
    {"sub_539858", 0x539858, &recomp_gen::fn_sub_539858_00539858, &recomp_gen::fn_sub_539858_00539858__recomp},
    {"sub_5399B8", 0x5399B8, &recomp_gen::fn_sub_5399B8_005399b8, &recomp_gen::fn_sub_5399B8_005399b8__recomp},
    {"sub_539A38", 0x539A38, &recomp_gen::fn_sub_539A38_00539a38, &recomp_gen::fn_sub_539A38_00539a38__recomp},
    {"sub_539AE0", 0x539AE0, &recomp_gen::fn_sub_539AE0_00539ae0, &recomp_gen::fn_sub_539AE0_00539ae0__recomp},
    {"sub_539BE0", 0x539BE0, &recomp_gen::fn_sub_539BE0_00539be0, &recomp_gen::fn_sub_539BE0_00539be0__recomp},
    {"sub_539C60", 0x539C60, &recomp_gen::fn_sub_539C60_00539c60, &recomp_gen::fn_sub_539C60_00539c60__recomp},
    {"sub_539CD8", 0x539CD8, &recomp_gen::fn_sub_539CD8_00539cd8, &recomp_gen::fn_sub_539CD8_00539cd8__recomp},
    {"sub_539E10", 0x539E10, &recomp_gen::fn_sub_539E10_00539e10, &recomp_gen::fn_sub_539E10_00539e10__recomp},
    {"sub_539ED8", 0x539ED8, &recomp_gen::fn_sub_539ED8_00539ed8, &recomp_gen::fn_sub_539ED8_00539ed8__recomp},
    {"sub_53A138", 0x53A138, &recomp_gen::fn_sub_53A138_0053a138, &recomp_gen::fn_sub_53A138_0053a138__recomp},
    {"_get_peer_or_sock_name_3", 0x53A358, &recomp_gen::fn__get_peer_or_sock_name_3_0053a358, &recomp_gen::fn__get_peer_or_sock_name_3_0053a358__recomp},
    {"sub_53A3B8", 0x53A3B8, &recomp_gen::fn_sub_53A3B8_0053a3b8, &recomp_gen::fn_sub_53A3B8_0053a3b8__recomp},
    {"sub_53A410", 0x53A410, &recomp_gen::fn_sub_53A410_0053a410, &recomp_gen::fn_sub_53A410_0053a410__recomp},
    {"sub_53AD00", 0x53AD00, &recomp_gen::fn_sub_53AD00_0053ad00, &recomp_gen::fn_sub_53AD00_0053ad00__recomp},
    {"sub_54CB78", 0x54CB78, &recomp_gen::fn_sub_54CB78_0054cb78, &recomp_gen::fn_sub_54CB78_0054cb78__recomp},
    {"sub_54CBA0", 0x54CBA0, &recomp_gen::fn_sub_54CBA0_0054cba0, &recomp_gen::fn_sub_54CBA0_0054cba0__recomp},
    {"sub_54CBC8", 0x54CBC8, &recomp_gen::fn_sub_54CBC8_0054cbc8, &recomp_gen::fn_sub_54CBC8_0054cbc8__recomp},
    {"sub_54CC98", 0x54CC98, &recomp_gen::fn_sub_54CC98_0054cc98, &recomp_gen::fn_sub_54CC98_0054cc98__recomp},
    {"sub_54CCC0", 0x54CCC0, &recomp_gen::fn_sub_54CCC0_0054ccc0, &recomp_gen::fn_sub_54CCC0_0054ccc0__recomp},
    {"sub_54CCE8", 0x54CCE8, &recomp_gen::fn_sub_54CCE8_0054cce8, &recomp_gen::fn_sub_54CCE8_0054cce8__recomp},
    {"sub_54CD10", 0x54CD10, &recomp_gen::fn_sub_54CD10_0054cd10, &recomp_gen::fn_sub_54CD10_0054cd10__recomp},
    {"sub_54CD40", 0x54CD40, &recomp_gen::fn_sub_54CD40_0054cd40, &recomp_gen::fn_sub_54CD40_0054cd40__recomp},
    {"sub_54CD78", 0x54CD78, &recomp_gen::fn_sub_54CD78_0054cd78, &recomp_gen::fn_sub_54CD78_0054cd78__recomp},
    {"sub_54CD80", 0x54CD80, &recomp_gen::fn_sub_54CD80_0054cd80, &recomp_gen::fn_sub_54CD80_0054cd80__recomp},
    {"sub_54CD88", 0x54CD88, &recomp_gen::fn_sub_54CD88_0054cd88, &recomp_gen::fn_sub_54CD88_0054cd88__recomp},
    {"sub_54CDB8", 0x54CDB8, &recomp_gen::fn_sub_54CDB8_0054cdb8, &recomp_gen::fn_sub_54CDB8_0054cdb8__recomp},
    {"sub_54CDE8", 0x54CDE8, &recomp_gen::fn_sub_54CDE8_0054cde8, &recomp_gen::fn_sub_54CDE8_0054cde8__recomp},
    {"sub_54CE38", 0x54CE38, &recomp_gen::fn_sub_54CE38_0054ce38, &recomp_gen::fn_sub_54CE38_0054ce38__recomp},
    {"sub_54CE60", 0x54CE60, &recomp_gen::fn_sub_54CE60_0054ce60, &recomp_gen::fn_sub_54CE60_0054ce60__recomp},
    {"sub_54CE78", 0x54CE78, &recomp_gen::fn_sub_54CE78_0054ce78, &recomp_gen::fn_sub_54CE78_0054ce78__recomp},
    {"sub_54CE80", 0x54CE80, &recomp_gen::fn_sub_54CE80_0054ce80, &recomp_gen::fn_sub_54CE80_0054ce80__recomp},
    {"sub_54CE90", 0x54CE90, &recomp_gen::fn_sub_54CE90_0054ce90, &recomp_gen::fn_sub_54CE90_0054ce90__recomp},
    {"sub_54CF88", 0x54CF88, &recomp_gen::fn_sub_54CF88_0054cf88, &recomp_gen::fn_sub_54CF88_0054cf88__recomp},
    {"sub_561758", 0x561758, &recomp_gen::fn_sub_561758_00561758, &recomp_gen::fn_sub_561758_00561758__recomp},
    {"sub_5617C0", 0x5617C0, &recomp_gen::fn_sub_5617C0_005617c0, &recomp_gen::fn_sub_5617C0_005617c0__recomp},
    {"sub_5617D8", 0x5617D8, &recomp_gen::fn_sub_5617D8_005617d8, &recomp_gen::fn_sub_5617D8_005617d8__recomp},
    {"sub_5617F0", 0x5617F0, &recomp_gen::fn_sub_5617F0_005617f0, &recomp_gen::fn_sub_5617F0_005617f0__recomp},
    {"sub_561808", 0x561808, &recomp_gen::fn_sub_561808_00561808, &recomp_gen::fn_sub_561808_00561808__recomp},
    {"sub_561828", 0x561828, &recomp_gen::fn_sub_561828_00561828, &recomp_gen::fn_sub_561828_00561828__recomp},
    {"sub_561870", 0x561870, &recomp_gen::fn_sub_561870_00561870, &recomp_gen::fn_sub_561870_00561870__recomp},
    {"sub_5618A0", 0x5618A0, &recomp_gen::fn_sub_5618A0_005618a0, &recomp_gen::fn_sub_5618A0_005618a0__recomp},
    {"sub_5618F0", 0x5618F0, &recomp_gen::fn_sub_5618F0_005618f0, &recomp_gen::fn_sub_5618F0_005618f0__recomp},
    {"sub_561920", 0x561920, &recomp_gen::fn_sub_561920_00561920, &recomp_gen::fn_sub_561920_00561920__recomp},
    {"sub_561970", 0x561970, &recomp_gen::fn_sub_561970_00561970, &recomp_gen::fn_sub_561970_00561970__recomp},
    {"sub_5619B8", 0x5619B8, &recomp_gen::fn_sub_5619B8_005619b8, &recomp_gen::fn_sub_5619B8_005619b8__recomp},
    {"sub_561A80", 0x561A80, &recomp_gen::fn_sub_561A80_00561a80, &recomp_gen::fn_sub_561A80_00561a80__recomp},
    {"sub_561AB0", 0x561AB0, &recomp_gen::fn_sub_561AB0_00561ab0, &recomp_gen::fn_sub_561AB0_00561ab0__recomp},
    {"sub_561B38", 0x561B38, &recomp_gen::fn_sub_561B38_00561b38, &recomp_gen::fn_sub_561B38_00561b38__recomp},
    {"sub_561B70", 0x561B70, &recomp_gen::fn_sub_561B70_00561b70, &recomp_gen::fn_sub_561B70_00561b70__recomp},
    {"sub_561BC8", 0x561BC8, &recomp_gen::fn_sub_561BC8_00561bc8, &recomp_gen::fn_sub_561BC8_00561bc8__recomp},
    {"sub_561C18", 0x561C18, &recomp_gen::fn_sub_561C18_00561c18, &recomp_gen::fn_sub_561C18_00561c18__recomp},
    {"sub_561C78", 0x561C78, &recomp_gen::fn_sub_561C78_00561c78, &recomp_gen::fn_sub_561C78_00561c78__recomp},
    {"sub_561CA8", 0x561CA8, &recomp_gen::fn_sub_561CA8_00561ca8, &recomp_gen::fn_sub_561CA8_00561ca8__recomp},
    {"sub_561D10", 0x561D10, &recomp_gen::fn_sub_561D10_00561d10, &recomp_gen::fn_sub_561D10_00561d10__recomp},
    {"sub_561D58", 0x561D58, &recomp_gen::fn_sub_561D58_00561d58, &recomp_gen::fn_sub_561D58_00561d58__recomp},
    {"sub_561DB8", 0x561DB8, &recomp_gen::fn_sub_561DB8_00561db8, &recomp_gen::fn_sub_561DB8_00561db8__recomp},
    {"sub_561E98", 0x561E98, &recomp_gen::fn_sub_561E98_00561e98, &recomp_gen::fn_sub_561E98_00561e98__recomp},
    {"sub_561EE8", 0x561EE8, &recomp_gen::fn_sub_561EE8_00561ee8, &recomp_gen::fn_sub_561EE8_00561ee8__recomp},
    {"sub_561F88", 0x561F88, &recomp_gen::fn_sub_561F88_00561f88, &recomp_gen::fn_sub_561F88_00561f88__recomp},
    {"sub_561FD8", 0x561FD8, &recomp_gen::fn_sub_561FD8_00561fd8, &recomp_gen::fn_sub_561FD8_00561fd8__recomp},
    {"sub_5620D8", 0x5620D8, &recomp_gen::fn_sub_5620D8_005620d8, &recomp_gen::fn_sub_5620D8_005620d8__recomp},
    {"sub_562140", 0x562140, &recomp_gen::fn_sub_562140_00562140, &recomp_gen::fn_sub_562140_00562140__recomp},
    {"_ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3", 0x562210, &recomp_gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3_00562210, &recomp_gen::fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3_00562210__recomp},
    {"width__CQ24_STL8ios_base_0", 0x562218, &recomp_gen::fn_width__CQ24_STL8ios_base_0_00562218, &recomp_gen::fn_width__CQ24_STL8ios_base_0_00562218__recomp},
    {"sub_562220", 0x562220, &recomp_gen::fn_sub_562220_00562220, &recomp_gen::fn_sub_562220_00562220__recomp},
    {"sub_562240", 0x562240, &recomp_gen::fn_sub_562240_00562240, &recomp_gen::fn_sub_562240_00562240__recomp},
    {"sub_562288", 0x562288, &recomp_gen::fn_sub_562288_00562288, &recomp_gen::fn_sub_562288_00562288__recomp},
    {"sub_5622B8", 0x5622B8, &recomp_gen::fn_sub_5622B8_005622b8, &recomp_gen::fn_sub_5622B8_005622b8__recomp},
    {"sub_562308", 0x562308, &recomp_gen::fn_sub_562308_00562308, &recomp_gen::fn_sub_562308_00562308__recomp},
    {"sub_562338", 0x562338, &recomp_gen::fn_sub_562338_00562338, &recomp_gen::fn_sub_562338_00562338__recomp},
    {"sub_562388", 0x562388, &recomp_gen::fn_sub_562388_00562388, &recomp_gen::fn_sub_562388_00562388__recomp},
    {"sub_5623E0", 0x5623E0, &recomp_gen::fn_sub_5623E0_005623e0, &recomp_gen::fn_sub_5623E0_005623e0__recomp},
    {"sub_5624B0", 0x5624B0, &recomp_gen::fn_sub_5624B0_005624b0, &recomp_gen::fn_sub_5624B0_005624b0__recomp},
    {"sub_5624E0", 0x5624E0, &recomp_gen::fn_sub_5624E0_005624e0, &recomp_gen::fn_sub_5624E0_005624e0__recomp},
    {"sub_562568", 0x562568, &recomp_gen::fn_sub_562568_00562568, &recomp_gen::fn_sub_562568_00562568__recomp},
    {"sub_562570", 0x562570, &recomp_gen::fn_sub_562570_00562570, &recomp_gen::fn_sub_562570_00562570__recomp},
    {"sub_562580", 0x562580, &recomp_gen::fn_sub_562580_00562580, &recomp_gen::fn_sub_562580_00562580__recomp},
    {"sub_5625B0", 0x5625B0, &recomp_gen::fn_sub_5625B0_005625b0, &recomp_gen::fn_sub_5625B0_005625b0__recomp},
    {"sub_562630", 0x562630, &recomp_gen::fn_sub_562630_00562630, &recomp_gen::fn_sub_562630_00562630__recomp},
    {"sub_562680", 0x562680, &recomp_gen::fn_sub_562680_00562680, &recomp_gen::fn_sub_562680_00562680__recomp},
    {"sub_5626E0", 0x5626E0, &recomp_gen::fn_sub_5626E0_005626e0, &recomp_gen::fn_sub_5626E0_005626e0__recomp},
    {"sub_562880", 0x562880, &recomp_gen::fn_sub_562880_00562880, &recomp_gen::fn_sub_562880_00562880__recomp},
    {"sub_5628D0", 0x5628D0, &recomp_gen::fn_sub_5628D0_005628d0, &recomp_gen::fn_sub_5628D0_005628d0__recomp},
    {"sub_562A50", 0x562A50, &recomp_gen::fn_sub_562A50_00562a50, &recomp_gen::fn_sub_562A50_00562a50__recomp},
    {"sub_562AA0", 0x562AA0, &recomp_gen::fn_sub_562AA0_00562aa0, &recomp_gen::fn_sub_562AA0_00562aa0__recomp},
    {"sub_562C80", 0x562C80, &recomp_gen::fn_sub_562C80_00562c80, &recomp_gen::fn_sub_562C80_00562c80__recomp},
    {"sub_562CE8", 0x562CE8, &recomp_gen::fn_sub_562CE8_00562ce8, &recomp_gen::fn_sub_562CE8_00562ce8__recomp},
    {"sub_562DE0", 0x562DE0, &recomp_gen::fn_sub_562DE0_00562de0, &recomp_gen::fn_sub_562DE0_00562de0__recomp},
    {"sub_562DE8", 0x562DE8, &recomp_gen::fn_sub_562DE8_00562de8, &recomp_gen::fn_sub_562DE8_00562de8__recomp},
    {"sub_562DF0", 0x562DF0, &recomp_gen::fn_sub_562DF0_00562df0, &recomp_gen::fn_sub_562DF0_00562df0__recomp},
    {"sub_562DF8", 0x562DF8, &recomp_gen::fn_sub_562DF8_00562df8, &recomp_gen::fn_sub_562DF8_00562df8__recomp},
    {"sub_562E10", 0x562E10, &recomp_gen::fn_sub_562E10_00562e10, &recomp_gen::fn_sub_562E10_00562e10__recomp},
    {"sub_562E28", 0x562E28, &recomp_gen::fn_sub_562E28_00562e28, &recomp_gen::fn_sub_562E28_00562e28__recomp},
    {"sub_562E48", 0x562E48, &recomp_gen::fn_sub_562E48_00562e48, &recomp_gen::fn_sub_562E48_00562e48__recomp},
    {"sub_562E90", 0x562E90, &recomp_gen::fn_sub_562E90_00562e90, &recomp_gen::fn_sub_562E90_00562e90__recomp},
    {"sub_562EC0", 0x562EC0, &recomp_gen::fn_sub_562EC0_00562ec0, &recomp_gen::fn_sub_562EC0_00562ec0__recomp},
    {"sub_562F10", 0x562F10, &recomp_gen::fn_sub_562F10_00562f10, &recomp_gen::fn_sub_562F10_00562f10__recomp},
    {"sub_562F40", 0x562F40, &recomp_gen::fn_sub_562F40_00562f40, &recomp_gen::fn_sub_562F40_00562f40__recomp},
    {"sub_562F90", 0x562F90, &recomp_gen::fn_sub_562F90_00562f90, &recomp_gen::fn_sub_562F90_00562f90__recomp},
    {"sub_562FE8", 0x562FE8, &recomp_gen::fn_sub_562FE8_00562fe8, &recomp_gen::fn_sub_562FE8_00562fe8__recomp},
    {"sub_5630D0", 0x5630D0, &recomp_gen::fn_sub_5630D0_005630d0, &recomp_gen::fn_sub_5630D0_005630d0__recomp},
    {"sub_563100", 0x563100, &recomp_gen::fn_sub_563100_00563100, &recomp_gen::fn_sub_563100_00563100__recomp},
    {"sub_563188", 0x563188, &recomp_gen::fn_sub_563188_00563188, &recomp_gen::fn_sub_563188_00563188__recomp},
    {"sub_5631C0", 0x5631C0, &recomp_gen::fn_sub_5631C0_005631c0, &recomp_gen::fn_sub_5631C0_005631c0__recomp},
    {"sub_563218", 0x563218, &recomp_gen::fn_sub_563218_00563218, &recomp_gen::fn_sub_563218_00563218__recomp},
    {"sub_563268", 0x563268, &recomp_gen::fn_sub_563268_00563268, &recomp_gen::fn_sub_563268_00563268__recomp},
    {"sub_5632C8", 0x5632C8, &recomp_gen::fn_sub_5632C8_005632c8, &recomp_gen::fn_sub_5632C8_005632c8__recomp},
    {"sub_5632F8", 0x5632F8, &recomp_gen::fn_sub_5632F8_005632f8, &recomp_gen::fn_sub_5632F8_005632f8__recomp},
    {"sub_5633D0", 0x5633D0, &recomp_gen::fn_sub_5633D0_005633d0, &recomp_gen::fn_sub_5633D0_005633d0__recomp},
    {"sub_563418", 0x563418, &recomp_gen::fn_sub_563418_00563418, &recomp_gen::fn_sub_563418_00563418__recomp},
    {"sub_5634D0", 0x5634D0, &recomp_gen::fn_sub_5634D0_005634d0, &recomp_gen::fn_sub_5634D0_005634d0__recomp},
    {"sub_563530", 0x563530, &recomp_gen::fn_sub_563530_00563530, &recomp_gen::fn_sub_563530_00563530__recomp},
    {"sub_563680", 0x563680, &recomp_gen::fn_sub_563680_00563680, &recomp_gen::fn_sub_563680_00563680__recomp},
    {"sub_5636D0", 0x5636D0, &recomp_gen::fn_sub_5636D0_005636d0, &recomp_gen::fn_sub_5636D0_005636d0__recomp},
    {"sub_5637F8", 0x5637F8, &recomp_gen::fn_sub_5637F8_005637f8, &recomp_gen::fn_sub_5637F8_005637f8__recomp},
    {"sub_563848", 0x563848, &recomp_gen::fn_sub_563848_00563848, &recomp_gen::fn_sub_563848_00563848__recomp},
    {"sub_563968", 0x563968, &recomp_gen::fn_sub_563968_00563968, &recomp_gen::fn_sub_563968_00563968__recomp},
    {"sub_5639D0", 0x5639D0, &recomp_gen::fn_sub_5639D0_005639d0, &recomp_gen::fn_sub_5639D0_005639d0__recomp},
    {"sub_563A98", 0x563A98, &recomp_gen::fn_sub_563A98_00563a98, &recomp_gen::fn_sub_563A98_00563a98__recomp},
    {"sub_563AE0", 0x563AE0, &recomp_gen::fn_sub_563AE0_00563ae0, &recomp_gen::fn_sub_563AE0_00563ae0__recomp},
    {"sub_563B70", 0x563B70, &recomp_gen::fn_sub_563B70_00563b70, &recomp_gen::fn_sub_563B70_00563b70__recomp},
    {"sub_563BA8", 0x563BA8, &recomp_gen::fn_sub_563BA8_00563ba8, &recomp_gen::fn_sub_563BA8_00563ba8__recomp},
    {"sub_563C28", 0x563C28, &recomp_gen::fn_sub_563C28_00563c28, &recomp_gen::fn_sub_563C28_00563c28__recomp},
    {"sub_564888", 0x564888, &recomp_gen::fn_sub_564888_00564888, &recomp_gen::fn_sub_564888_00564888__recomp},
    {"sub_5648E8", 0x5648E8, &recomp_gen::fn_sub_5648E8_005648e8, &recomp_gen::fn_sub_5648E8_005648e8__recomp},
    {"sub_564978", 0x564978, &recomp_gen::fn_sub_564978_00564978, &recomp_gen::fn_sub_564978_00564978__recomp},
    {"sub_564990", 0x564990, &recomp_gen::fn_sub_564990_00564990, &recomp_gen::fn_sub_564990_00564990__recomp},
    {"sub_5649A8", 0x5649A8, &recomp_gen::fn_sub_5649A8_005649a8, &recomp_gen::fn_sub_5649A8_005649a8__recomp},
    {"sub_5649C0", 0x5649C0, &recomp_gen::fn_sub_5649C0_005649c0, &recomp_gen::fn_sub_5649C0_005649c0__recomp},
    {"sub_5649D8", 0x5649D8, &recomp_gen::fn_sub_5649D8_005649d8, &recomp_gen::fn_sub_5649D8_005649d8__recomp},
    {"sub_5649F0", 0x5649F0, &recomp_gen::fn_sub_5649F0_005649f0, &recomp_gen::fn_sub_5649F0_005649f0__recomp},
    {"sub_564A20", 0x564A20, &recomp_gen::fn_sub_564A20_00564a20, &recomp_gen::fn_sub_564A20_00564a20__recomp},
    {"sub_564A38", 0x564A38, &recomp_gen::fn_sub_564A38_00564a38, &recomp_gen::fn_sub_564A38_00564a38__recomp},
    {"sub_564A50", 0x564A50, &recomp_gen::fn_sub_564A50_00564a50, &recomp_gen::fn_sub_564A50_00564a50__recomp},
    {"sub_564A68", 0x564A68, &recomp_gen::fn_sub_564A68_00564a68, &recomp_gen::fn_sub_564A68_00564a68__recomp},
    {"sub_564AA8", 0x564AA8, &recomp_gen::fn_sub_564AA8_00564aa8, &recomp_gen::fn_sub_564AA8_00564aa8__recomp},
    {"sub_564B50", 0x564B50, &recomp_gen::fn_sub_564B50_00564b50, &recomp_gen::fn_sub_564B50_00564b50__recomp},
    {"sub_5558E8", 0x5558E8, &recomp_gen::fn_sub_5558E8_005558e8, &recomp_gen::fn_sub_5558E8_005558e8__recomp},
    {"sub_555918", 0x555918, &recomp_gen::fn_sub_555918_00555918, &recomp_gen::fn_sub_555918_00555918__recomp},
    {"cvFsInit", 0x555940, &recomp_gen::fn_cvFsInit_00555940, &recomp_gen::fn_cvFsInit_00555940__recomp},
    {"sub_555D10", 0x555D10, &recomp_gen::fn_sub_555D10_00555d10, &recomp_gen::fn_sub_555D10_00555d10__recomp},
    {"cvfs_getDevName", 0x5561E8, &recomp_gen::fn_cvfs_getDevName_005561e8, &recomp_gen::fn_cvfs_getDevName_005561e8__recomp},
    {"cvfs_getDefDev", 0x556330, &recomp_gen::fn_cvfs_getDefDev_00556330, &recomp_gen::fn_cvfs_getDefDev_00556330__recomp},
};

namespace cri = p3fes::game::cri1;

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    std::fprintf(stderr, "test_cri1: no case 0x%X\n", addr);
    std::abort();
}

constexpr u32 kSeeds = 24;            // generic sweep: pairs per function (P3FES_HG_SEEDS overrides)
constexpr u32 kWorld = 0x01810000u;   // 64 KiB of free RAM above the harness's arena (the generic sweep's world)
constexpr u32 kWorldSize = 0x10000u;
// The meaningful sections' buffers (free RAM in the ELF image; the snapshot sections use kScratch).
constexpr u32 kHdr = 0x01820000u;     // an ADX file's first 4 KiB
constexpr u32 kOut = 0x01821000u;     // out-parameters
constexpr u32 kStr = 0x01821400u;     // strings
constexpr u32 kSrc = 0x01822000u;     // ADX blocks (up to 32 KiB)
constexpr u32 kPcmL = 0x0182A000u;    // PCM out (up to 16 KiB per channel)
constexpr u32 kPcmR = 0x0182E000u;
constexpr u32 kRing = 0x01840000u;    // stream-joint buffers (64 KiB + extra)
constexpr u32 kNodes = 0x01852000u;   // SJUNI node work area
constexpr u32 kScratch = 0x01BC0000u; // free in every replay snapshot (stand_ins.h)

std::map<std::string, int> g_pairs;  // pairs per function in the meaningful sections
u32 g_seed = 1;

u8 r8(Machine& m, u32 va) { return *m.at(va); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void fill(Machine& m, u32 va, const std::vector<u8>& b) { std::memcpy(m.at(va), b.data(), b.size()); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
std::string cstr(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va))); }
void put_str(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
u16 be16(const u8* p) { return static_cast<u16>((p[0] << 8) | p[1]); }
u32 be32(const u8* p) { return (static_cast<u32>(p[0]) << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
u32 uv(u64 v) { return static_cast<u32>(v); }

// One pair (hand vs recompiled) of the function at `addr`: $a0..$a3 from `a`, $t0..$t3 from `t`, the 9th.. arguments
// in the caller's 8-byte stack slots from $sp + 0. Everything hgp::pair compares; the recompiled run's memory stays.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, std::vector<u64> stk = {}) {
    const Case& c = by_addr(addr);
    for (std::size_t i = 0; i < stk.size(); ++i) w64(m, kSp + 8 * static_cast<u32>(i), stk[i]);
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    hgp::Run r = hgp::pair(m, c.hand, c.recomp, a, g_seed++, c.name, hw);
    INFO(c.name);
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

// A pair on stand-ins (stand_ins.h): the whole register file at every check point, the dead stack, all of RAM, the
// stand-ins' call logs. Returns the recompiled run's $v0 and log.
struct SiResult {
    u64 v0 = 0;
    std::vector<StandInCall> log;
};
SiResult pr_si(Machine& m, u32 addr, Args a, const WorldSetup& setup, std::map<unsigned, u64> t = {}) {
    const Case& c = by_addr(addr);
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

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}
// The ELF image with a replay snapshot's RAM (empty when the snapshot is absent).
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
    std::string s;
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    s = std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
    return s;
}

// --- ADX files from extracted/ (read at run time; nothing is committed) --------------------------------------------
std::vector<std::filesystem::path> adx_files() {
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
        if (ext == ".ADX" && it->path().string().find("_ours") == std::string::npos) out.push_back(it->path());
    }
    std::sort(out.begin(), out.end());
    return out;
}
std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream f(p, std::ios::binary);
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

// The public ADX header layout, parsed on the host (the reference of the header pairs).
struct AdxHeader {
    bool magic = false;
    u16 data_off = 0;  // header size + 4
    u8 enc = 0, block = 0, bits = 0, ch = 0;
    u32 rate = 0, samples = 0;
    u16 cutoff = 0;
    u8 ver = 0, flags = 0;
    bool copyright = false;
    // loop record (version 3 at +20, version 4 at +32)
    bool has_loop_record = false;
    s16 align = 0;
    u16 loop_count = 0, loop_flag = 0;
    u32 loop_start = 0, loop_start_byte = 0, loop_end = 0, loop_end_byte = 0;
};
AdxHeader parse_adx(const std::vector<u8>& b) {
    AdxHeader h;
    if (b.size() < 20) return h;
    h.magic = be16(&b[0]) == 0x8000;
    h.data_off = static_cast<u16>(be16(&b[2]) + 4);
    h.enc = b[4];
    h.block = b[5];
    h.bits = b[6];
    h.ch = b[7];
    h.rate = be32(&b[8]);
    h.samples = be32(&b[12]);
    h.cutoff = be16(&b[16]);
    h.ver = b[18];
    h.flags = b[19];
    h.copyright = h.data_off >= 6 && h.data_off <= b.size() && std::memcmp(&b[h.data_off - 6], "(c)CRI", 6) == 0;
    const u32 base = h.ver == 4 ? 32 : 20;
    if (b.size() >= base + 24 && be16(&b[2]) >= base + 24) {
        h.has_loop_record = true;
        h.align = static_cast<s16>(be16(&b[base]));
        h.loop_count = be16(&b[base + 2]);
        h.loop_flag = be16(&b[base + 6]);
        h.loop_start = be32(&b[base + 8]);
        h.loop_start_byte = be32(&b[base + 12]);
        h.loop_end = be32(&b[base + 16]);
        h.loop_end_byte = be32(&b[base + 20]);
    }
    return h;
}

// The public ADX decoder (host reference): coefficients from the cutoff and rate; per 18-byte frame a big-endian scale
// stored minus one (bit 15 marks the end block), 32 signed nibbles high first; sample = nibble * scale + ((coef1 * hist1 +
// coef2 * hist2) >> 12), clamped to 16 bits.
void host_coefficients(u32 cutoff, u32 rate, s32& c1, s32& c2) {
    const double a = std::sqrt(2.0) - std::cos(2.0 * 3.14159265358979323846 * cutoff / rate);
    const double b = std::sqrt(2.0) - 1.0;
    const double c = (a - std::sqrt((a + b) * (a - b))) / b;
    c1 = static_cast<s32>(c * 8192.0);
    c2 = static_cast<s32>(-c * c * 4096.0);
}
struct HostHist {
    s32 h1 = 0, h2 = 0;
};
// The stereo decoder's downmix (0x784948 non-zero): both outputs get (L + R) * 7 / 10, clamped; histories unmixed.
void host_downmix(const s16* l, const s16* r, s16* out) {
    for (int i = 0; i < 32; ++i) out[i] = static_cast<s16>(std::clamp((7 * (l[i] + r[i])) / 10, -32768, 32767));
}
void host_frame(const u8* f, s16* out, HostHist& h, s32 c1, s32 c2) {
    const s32 scale = (be16(f) & 0x1FFF) + 1;
    for (int i = 0; i < 32; ++i) {
        const u8 byte = f[2 + i / 2];
        s32 nib = (i & 1) ? (byte & 0xF) : (byte >> 4);
        if (nib >= 8) nib -= 16;
        s32 s = nib * scale + ((c1 * h.h1 + c2 * h.h2) >> 12);
        s = std::clamp(s, -32768, 32767);
        out[i] = static_cast<s16>(s);
        h.h2 = h.h1;
        h.h1 = s;
    }
}

}  // namespace

// =====================================================================================================================
// The generic sweep: every body against its recompiled body on random worlds
// =====================================================================================================================
TEST_CASE("game(cri1): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
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
            Args args{};
            for (u64& a : args) a = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("generic sweep: " << pairs << " pairs, " << stops << " stopped early (identically)");
}

// =====================================================================================================================
// ADXB: every ADX header of the disc through the header parsers, against the public layout
// =====================================================================================================================
TEST_CASE("game(cri1): ADX headers of every .adx file in extracted/ (parsers vs the public layout)") {
    auto m = machine();
    if (!m) return;
    const auto files = adx_files();
    if (files.empty()) {
        MESSAGE("SKIP: no .adx files under " << extracted_root());
        return;
    }
    int n = 0, with_loop = 0, v4 = 0;
    for (std::size_t fi = 0; fi < files.size(); ++fi) {
        const std::vector<u8> file = read_file(files[fi]);
        INFO(files[fi].string());
        REQUIRE(file.size() >= 64);
        std::vector<u8> head(file.begin(), file.begin() + std::min<std::size_t>(file.size(), 0x1000));
        const AdxHeader h = parse_adx(head);
        CHECK(h.magic);
        zero(*m, kHdr, 0x1000);
        fill(*m, kHdr, head);
        zero(*m, kOut, 0x100);
        const u32 size = static_cast<u32>(std::min<std::size_t>(file.size(), 0x10000));
        ++n;
        if (h.ver == 4) ++v4;

        // sub_539A38 [adx_IsHeader]: 0x8000 magic, >= 0x8000 bytes, "(c)CRI" before the data
        const s32 is = sv(prv(*m, 0x539A38, {kHdr, size, kOut, 0}));
        CHECK(is == ((size > 0x7FFF && h.copyright) ? 1 : 0));
        if (is == 1) CHECK(r16(*m, kOut) == h.data_off);

        // sub_539AE0 [adx_DecodeHeader]
        zero(*m, kOut, 0x40);
        const s32 dec = sv(prv(*m, 0x539AE0, {kHdr, size, kOut + 0, kOut + 4}, tregs(kOut + 5, kOut + 6, kOut + 7, kOut + 8),
                               {kOut + 12, kOut + 16}));
        CHECK(dec == 0);
        CHECK(r16(*m, kOut + 0) == h.data_off);
        CHECK(r8(*m, kOut + 4) == h.enc);
        CHECK(r8(*m, kOut + 5) == h.bits);
        CHECK(r8(*m, kOut + 6) == h.block);
        CHECK(r8(*m, kOut + 7) == h.ch);
        CHECK(r32(*m, kOut + 8) == h.rate);
        CHECK(r32(*m, kOut + 12) == h.samples);
        CHECK(static_cast<s32>(r32(*m, kOut + 16)) == (8 * h.block - 16) / h.bits);  // 32 samples per 18-byte frame

        // sub_539ED8 [adx_DecodeLoop]
        zero(*m, kOut, 0x40);
        const s32 lp = sv(prv(*m, 0x539ED8, {kHdr, size, kOut + 0, kOut + 4}, tregs(kOut + 6, kOut + 8, kOut + 12, kOut + 16),
                              {kOut + 20}));
        if (!h.has_loop_record) {
            CHECK(lp == -1);
        } else {
            ++with_loop;
            CHECK(static_cast<s32>(r32(*m, kOut + 0)) == h.align);
            CHECK(r16(*m, kOut + 4) == h.loop_count);
            if (h.loop_count == 1) {
                CHECK(lp == 0);
                CHECK(r16(*m, kOut + 6) == h.loop_flag);
                CHECK(r32(*m, kOut + 8) == h.loop_start);
                CHECK(r32(*m, kOut + 12) == h.loop_start_byte);
                CHECK(r32(*m, kOut + 16) == h.loop_end);
                CHECK(r32(*m, kOut + 20) == h.loop_end_byte);
                CHECK(h.loop_start <= h.loop_end);
                CHECK(h.loop_end <= h.samples);
                CHECK(h.loop_end_byte <= file.size());
            } else {
                CHECK(lp == -2);
            }
        }
        if (fi % 6 != 0) continue;  // the rest on every sixth file
        // sub_539A38 below the 0x8000-byte minimum: 0
        CHECK(prv(*m, 0x539A38, {kHdr, 0x7FFF, kOut, 0}) == 0);
        // sub_539BE0 [adx_GetCutoff]
        CHECK(prv(*m, 0x539BE0, {kHdr, size, kOut + 0x20, 0}) == 0);
        CHECK(r16(*m, kOut + 0x20) == h.cutoff);
        // sub_539C60 [adx_GetVersion]
        CHECK(prv(*m, 0x539C60, {kHdr, size, kOut + 0x24, kOut + 0x25}) == 0);
        CHECK(r8(*m, kOut + 0x24) == h.ver);
        CHECK(r8(*m, kOut + 0x25) == h.flags);
        // sub_539CD8 [adx_GetHistory]: version 4 keeps the channels' first histories at +24 .. +30
        std::memset(m->at(kOut + 0x28), 0xA5, 8);
        const s32 hr = sv(prv(*m, 0x539CD8, {kHdr, size, kOut + 0x28, kOut + 0x2C}));
        CHECK(hr == 0);
        if (h.ver >= 4) {
            CHECK(r16(*m, kOut + 0x28) == be16(&head[24]));
            CHECK(r16(*m, kOut + 0x2C) == be16(&head[26]));
            CHECK(r16(*m, kOut + 0x2A) == be16(&head[28]));
            CHECK(r16(*m, kOut + 0x2E) == be16(&head[30]));
        } else {
            CHECK(r32(*m, kOut + 0x28) == 0);
            CHECK(r32(*m, kOut + 0x2C) == 0);
        }
        // sub_539E10 [adx_GetLoopInfo]
        zero(*m, kOut + 0x30, 12);
        CHECK(prv(*m, 0x539E10, {kHdr, size, kOut + 0x30, kOut + 0x34}, tregs(kOut + 0x38)) == 0);
        if (h.has_loop_record && h.loop_count == 1) {
            const s32 cut = h.align % 2048;
            CHECK(r16(*m, kOut + 0x30) == 1);
            CHECK(static_cast<s32>(r32(*m, kOut + 0x34)) == static_cast<s32>(h.loop_start) - cut);
            CHECK(static_cast<s32>(r32(*m, kOut + 0x38)) == static_cast<s32>(h.loop_end) - cut);
        } else {
            CHECK(r16(*m, kOut + 0x30) == 0);
            CHECK(r32(*m, kOut + 0x34) == 0);
        }
        // sub_53A138 [adx_DecodeAinf]: no "AINF" on the disc
        const s32 ai = sv(prv(*m, 0x53A138, {kHdr, size, kOut + 0x40, kOut + 0x48}, tregs(kOut + 0x58, kOut + 0x5C)));
        CHECK(ai < 0);
        // _get_peer_or_sock_name_3 [ahx_DecodeHeader]: not an AHX header
        CHECK(sv(prv(*m, 0x53A358, {kHdr, size, kOut + 0x60, 0})) == -2);
    }
    MESSAGE("ADX headers: " << n << " files (" << v4 << " version 4, " << with_loop << " with a loop record); " << summary());
}

TEST_CASE("game(cri1): ADXB header rules on built headers (AHX, AINF, short buffers, the AHX sync search, SPSD / WAV tags)") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0xC21};
    // AHX: 0x8001 magic, data offset = header size + 4
    for (u32 hs : {0u, 28u, 0x1Cu, 0x7FFBu, 0xFFFFu}) {
        const u8 hdr[16] = {0x80, 0x01, static_cast<u8>(hs >> 8), static_cast<u8>(hs), 0x10, 0, 0, 1};
        std::memcpy(m->at(kHdr), hdr, 16);
        CHECK(sv(prv(*m, 0x53A358, {kHdr, 16, kOut, 0})) == 0);
        CHECK(r16(*m, kOut) == static_cast<u16>(hs + 4));
        CHECK(sv(prv(*m, 0x53A358, {kHdr, 15, kOut, 0})) == -1);  // shorter than 16 bytes
    }
    // An "AINF" record after a version-4 loop record (offset 32 + 24 = 56, the tag, size, id, volume, pan)
    {
        std::vector<u8> b(0x100, 0);
        b[0] = 0x80; b[1] = 0x00; b[2] = 0x00; b[3] = 0xF0;  // header size 0xF0
        b[4] = 3; b[5] = 18; b[6] = 4; b[7] = 2; b[18] = 4;
        b[32 + 2] = 0;        // loop count 0: the AINF parser skips no loop record (count 0 -> +24 only)
        const u32 tag = 32 + 4;
        std::memcpy(&b[tag], "AINF", 4);
        b[tag + 4] = 0; b[tag + 5] = 0; b[tag + 6] = 0; b[tag + 7] = 0x30;  // size
        for (int i = 0; i < 16; ++i) b[tag + 8 + i] = static_cast<u8>(0x41 + i);
        b[tag + 24] = 0xFF; b[tag + 25] = 0xF6;  // volume -10 (u16), two bytes unused
        b[tag + 28] = 0x00; b[tag + 29] = 0x10;  // pan 16
        b[tag + 30] = 0xFF; b[tag + 31] = 0xF0;  // pan -16
        fill(*m, kHdr, b);
        zero(*m, kOut, 0x80);
        const s32 r = sv(prv(*m, 0x53A138, {kHdr, 0x100, kOut, kOut + 8}, tregs(kOut + 0x20, kOut + 0x24)));
        CHECK(r == 0);
        CHECK(r32(*m, kOut) == 0x30);
        CHECK(std::memcmp(m->at(kOut + 8), &b[tag + 8], 16) == 0);
        CHECK(r16(*m, kOut + 0x20) == 0xFFF6);
        CHECK(r16(*m, kOut + 0x24) == 0x0010);
        CHECK(r16(*m, kOut + 0x26) == 0xFFF0);
        // a header too short for the record: -1; a wrong magic: -2
        CHECK(sv(prv(*m, 0x53A138, {kHdr, 59, kOut, kOut + 8}, tregs(kOut + 0x20, kOut + 0x24))) == -1);
        b[0] = 0x7F;
        fill(*m, kHdr, b);
        CHECK(sv(prv(*m, 0x539AE0, {kHdr, 0x100, kOut, kOut + 4}, tregs(kOut + 5, kOut + 6, kOut + 7, kOut + 8), {kOut + 12, kOut + 16})) == -2);
        CHECK(sv(prv(*m, 0x539AE0, {kHdr, 15, kOut, kOut + 4}, tregs(kOut + 5, kOut + 6, kOut + 7, kOut + 8), {kOut + 12, kOut + 16})) == -1);
    }
    // sub_5399B8 [ahx_FindSync]: the first even offset holding the little-endian halfword 0x0080
    for (int it = 0; it < 40; ++it) {
        const u32 len = 2 + rng() % 200;
        std::vector<u8> b(len);
        for (u8& x : b) {
            const u32 k = rng() % 3;
            const u32 v = rng() % 4;
            x = static_cast<u8>(k == 0 ? 0x80 : v);
        }
        fill(*m, kSrc, b);
        w16(*m, kOut, 0xBEEF);
        const s32 r = sv(prv(*m, 0x5399B8, {kSrc, len, kOut, 0}));
        // offset 0 is tested whenever there are two bytes, then 2, 4, ... below size - 1
        s32 want = -1;
        const s32 last = static_cast<s32>(len) - 1;
        if (last > 0) {
            if (b[0] == 0x80 && b[1] == 0) {
                want = 0;
            } else {
                for (s32 i = 2; i < last; i += 2)
                    if (b[static_cast<u32>(i)] == 0x80 && b[static_cast<u32>(i) + 1] == 0) {
                        want = i;
                        break;
                    }
            }
        }
        CHECK(r == (want < 0 ? -1 : 0));
        CHECK(r16(*m, kOut) == (want < 0 ? 0 : static_cast<u16>(want)));
    }
    // sub_53A3B8: (pos + header + block + 57 / 33) rounded down to blocks, less the header
    for (int it = 0; it < 24; ++it) {
        const u32 pos = rng() % 100000;
        const u32 hdr = rng() % 4096;
        const u32 blk = 1 + rng() % 4096;
        const u32 kind = rng() % 2;
        const u32 want = (pos + hdr + blk + (kind ? 57u : 33u)) / blk * blk - hdr;
        CHECK(uv(prv(*m, 0x53A3B8, {kind, pos, hdr, blk})) == want);
    }
    // the tag tests
    put_str(*m, kStr, "SPSD....");
    CHECK(prv(*m, 0x538EF0, {kStr, 0, 0, 0}) == 1);
    put_str(*m, kStr, "SPSE....");
    CHECK(prv(*m, 0x538EF0, {kStr, 0, 0, 0}) == 0);
    std::memcpy(m->at(kStr), "RIFF\x10\0\0\0WAVEfmt ", 16);
    CHECK(prv(*m, 0x5396F8, {kStr, 0, 0, 0}) == 1);
    std::memcpy(m->at(kStr), "RIFF\x10\0\0\0WAVXfmt ", 16);
    CHECK(prv(*m, 0x5396F8, {kStr, 0, 0, 0}) == 0);
    MESSAGE("built headers: " << summary());
}

// =====================================================================================================================
// ADXB: the coefficients and the decoders on real ADX blocks, against the public decoder
// =====================================================================================================================
TEST_CASE("game(cri1): ADX prediction coefficients (sub_539858) against the public formula") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0xC0EF};
    std::vector<std::pair<u32, u32>> cases = {{500, 24000}, {500, 48000}, {500, 44100}, {500, 32000}, {500, 22050}, {500, 11025}};
    for (int i = 0; i < 18; ++i) {
        const u32 rate = 8000 + rng() % 40000;
        const u32 cut = 50 + rng() % (rate / 4);
        cases.emplace_back(cut, rate);
    }
    for (const auto& [cut, rate] : cases) {
        INFO("cutoff " << cut << " rate " << rate);
        zero(*m, kOut, 8);
        pr(*m, 0x539858, {cut, rate, kOut, kOut + 2});
        s32 c1 = 0, c2 = 0;
        host_coefficients(cut, rate, c1, c2);
        const s32 g1 = static_cast<s16>(r16(*m, kOut));
        const s32 g2 = static_cast<s16>(r16(*m, kOut + 2));
        CHECK(std::abs(g1 - c1) <= 1);  // single precision, truncating conversions (R5900 FPU)
        CHECK(std::abs(g2 - c2) <= 1);
        if (cut == 500 && rate == 24000) MESSAGE("coefficients 500 Hz / 24000 Hz: " << g1 << ", " << g2);
    }
}

namespace {

// A decode job on one decoder object, both bodies paired at every step (create, coefficients, entry, run, reset), and
// the PCM compared with the host decoder frame by frame.
struct DecodeStats {
    int files = 0, frames = 0, chunks = 0, ends = 0;
};
void decode_file(Machine& m, const std::filesystem::path& path, u32 max_chunks, DecodeStats& st) {
    const std::vector<u8> file = read_file(path);
    INFO(path.string());
    const AdxHeader h = parse_adx(file);
    REQUIRE(h.magic);
    REQUIRE(h.block == 18);
    REQUIRE(h.bits == 4);
    const u32 ch = h.ch;
    ++st.files;
    // the decoder objects: init, create (500 Hz / 44100 Hz by default), the file's coefficients
    pr(m, 0x54CB78, {0, 0, 0, 0});
    const u32 obj = uv(prv(m, 0x54CBC8, {0, 0, 0, 0}));
    CHECK(obj == cri::adxpd::kPool);
    CHECK(r32(m, obj + cri::adxpd::kUsed) == 1);
    pr(m, 0x54CC98, {obj, h.rate, h.cutoff, 0});
    s32 c1 = 0, c2 = 0;
    host_coefficients(h.cutoff, h.rate, c1, c2);
    c1 = static_cast<s16>(r16(m, obj + cri::adxpd::kCoef1));  // the game's own values (within 1 of the formula, above)
    c2 = static_cast<s16>(r16(m, obj + cri::adxpd::kCoef2));
    // version 4 starts from the header's histories (zero on the disc)
    HostHist hist[2];
    if (h.ver >= 4) {
        hist[0].h1 = static_cast<s16>(be16(&file[24]));
        hist[0].h2 = static_cast<s16>(be16(&file[26]));
        hist[1].h1 = static_cast<s16>(be16(&file[28]));
        hist[1].h2 = static_cast<s16>(be16(&file[30]));
    }
    w16(m, kOut + 0, static_cast<u16>(hist[0].h1));
    w16(m, kOut + 2, static_cast<u16>(hist[1].h1));
    w16(m, kOut + 4, static_cast<u16>(hist[0].h2));
    w16(m, kOut + 6, static_cast<u16>(hist[1].h2));
    pr(m, 0x54CCC0, {obj, kOut + 0, kOut + 4, 0});  // dly0 = hist1 (left, right), dly1 = hist2
    const u32 frame_bytes = 18 * ch;
    u32 total_frames = static_cast<u32>((file.size() - h.data_off) / frame_bytes);
    // the end block (bit 15 of a scale): the stream's last frame; what follows is padding
    for (u32 f = 0; f < total_frames; ++f) {
        bool end = false;
        for (u32 c = 0; c < ch; ++c) end = end || (be16(&file[h.data_off + f * frame_bytes + 18 * c]) & 0x8000) != 0;
        if (end) {
            total_frames = f + 1;
            break;
        }
    }
    const u32 per_chunk = ch == 1 ? 64 : 48;  // frames per channel and chunk
    // chunks from the start, then the file's last frames (the end block)
    std::vector<u32> starts;
    for (u32 c = 0; c < max_chunks && (c + 1) * per_chunk <= total_frames; ++c) starts.push_back(c * per_chunk);
    const u32 tail = total_frames > per_chunk ? total_frames - per_chunk : 0;
    for (u32 s0 : starts) REQUIRE(s0 + per_chunk <= total_frames);
    for (std::size_t ci = 0; ci <= starts.size(); ++ci) {
        const bool last = ci == starts.size();
        const u32 first = last ? tail : starts[ci];
        if (last && !starts.empty() && first < starts.back() + per_chunk) break;
        if (last) {
            // jumping to the tail: the histories there are the host decoder's after decoding everything before it
            for (u32 f = (starts.empty() ? 0 : starts.back() + per_chunk); f < first; ++f)
                for (u32 c = 0; c < ch; ++c) {
                    s16 tmp[32];
                    host_frame(&file[h.data_off + f * frame_bytes + 18 * c], tmp, hist[c], c1, c2);
                }
            w16(m, kOut + 0, static_cast<u16>(hist[0].h1));
            w16(m, kOut + 2, static_cast<u16>(hist[1].h1));
            w16(m, kOut + 4, static_cast<u16>(hist[0].h2));
            w16(m, kOut + 6, static_cast<u16>(hist[1].h2));
            pr(m, 0x54CCC0, {obj, kOut + 0, kOut + 4, 0});
        }
        // the blocks (beyond the file's end: zero frames would decode; give the decoder only what the file has)
        const u32 avail = std::min(per_chunk, total_frames - first);
        std::vector<u8> blocks(file.begin() + h.data_off + first * frame_bytes,
                               file.begin() + h.data_off + (first + avail) * frame_bytes);
        fill(m, kSrc, blocks);
        std::memset(m.at(kPcmL), 0x5A, avail * 64);
        std::memset(m.at(kPcmR), 0x5A, avail * 64);
        const u32 nblk = avail * ch;
        if (ch == 1)
            CHECK(prv(m, 0x54CD88, {obj, kSrc, nblk, kPcmL}, tregs(0)) == 1);
        else
            CHECK(prv(m, 0x54CDB8, {obj, kSrc, nblk, kPcmL}, tregs(kPcmR)) == 1);
        CHECK(r32(m, obj + cri::adxpd::kState) == 0);  // the entry does not start the object; set it as the starter does
        w32(m, obj + cri::adxpd::kState, 1);
        const u32 hist_before[2] = {r32(m, obj + cri::adxpd::kHistL), r32(m, obj + cri::adxpd::kHistR)};
        CHECK(sv(prv(m, 0x54CE90, {obj, 0, 0, 0})) == 3);
        // host decode of the same frames, stopping at the end block like the decoder
        const bool downmix = ch == 2 && r32(m, cri::adxpd::kImplFlag) != 0;
        u32 done = 0;
        bool ended = false;
        for (u32 f = 0; f < avail && !ended; ++f) {
            for (u32 c = 0; c < ch; ++c)
                if (be16(&blocks[f * frame_bytes + 18 * c]) & 0x8000) ended = true;
            if (ended) break;
            s16 want[2][32];
            for (u32 c = 0; c < ch; ++c) host_frame(&blocks[f * frame_bytes + 18 * c], want[c], hist[c], c1, c2);
            if (downmix) {
                s16 mix[32];
                host_downmix(want[0], want[1], mix);
                std::memcpy(want[0], mix, 64);
                std::memcpy(want[1], mix, 64);
            }
            for (u32 c = 0; c < ch; ++c) {
                const u32 dst = (c == 0 ? kPcmL : kPcmR) + f * 64;
                if (std::memcmp(m.at(dst), want[c], 64) != 0) {
                    INFO("frame " << first + f << " channel " << c << (downmix ? " (downmix)" : ""));
                    CHECK(false);
                    return;
                }
            }
            ++done;
            ++st.frames;
        }
        if (ended) ++st.ends;
        CHECK(r32(m, obj + cri::adxpd::kDecoded) == (ended ? done * ch : nblk));
        CHECK(uv(prv(m, 0x54CE78, {obj, 0, 0, 0})) == (ended ? done * ch : nblk));
        if (ended) {
            // a job that meets the end block returns early: the object's histories are not written back
            CHECK(r32(m, obj + cri::adxpd::kHistL) == hist_before[0]);
            CHECK(r32(m, obj + cri::adxpd::kHistR) == hist_before[1]);
        } else {
            // the object's histories equal the host's after the chunk
            CHECK(static_cast<s16>(r16(m, obj + cri::adxpd::kHistL)) == hist[0].h1);
            CHECK(static_cast<s16>(r16(m, obj + cri::adxpd::kHistL + 2)) == hist[0].h2);
            if (ch == 2) {
                CHECK(static_cast<s16>(r16(m, obj + cri::adxpd::kHistR)) == hist[1].h1);
                CHECK(static_cast<s16>(r16(m, obj + cri::adxpd::kHistR + 2)) == hist[1].h2);
            }
        }
        CHECK(sv(prv(m, 0x54CE60, {obj, 0, 0, 0})) == 3);  // done -> idle
        CHECK(r32(m, obj + cri::adxpd::kState) == 0);
        ++st.chunks;
        if (ended) break;
    }
    pr(m, 0x54CD40, {obj, 0, 0, 0});
    CHECK(r32(m, obj + cri::adxpd::kUsed) == 0);
}

}  // namespace

TEST_CASE("game(cri1): ADPCM decoding of real .adx files (decoder objects + both decoders) against the public decoder") {
    auto m = machine();
    if (!m) return;
    const auto files = adx_files();
    if (files.empty()) {
        MESSAGE("SKIP: no .adx files under " << extracted_root());
        return;
    }
    // one file of each kind: mono version 3 (voices), mono version 4 (battle), stereo 24 kHz / 48 kHz, long headers
    std::vector<std::filesystem::path> pick;
    std::set<std::string> kinds;
    for (const auto& p : files) {
        const std::vector<u8> head = [&] {
            std::ifstream f(p, std::ios::binary);
            std::vector<u8> b(64);
            f.read(reinterpret_cast<char*>(b.data()), 64);
            return b;
        }();
        const AdxHeader h = parse_adx(head);
        const std::string kind = std::to_string(h.ch) + "/" + std::to_string(h.ver) + "/" + std::to_string(h.rate) + "/" +
                                 std::to_string(h.data_off > 64);
        if (kinds.insert(kind).second) pick.push_back(p);
    }
    DecodeStats st;
    for (const auto& p : pick) decode_file(*m, p, 3, st);
    // the stereo decoder's downmix path (0x784948 non-zero: both outputs (L + R) * 7 / 10)
    const u32 saved = r32(*m, cri::adxpd::kImplFlag);
    w32(*m, cri::adxpd::kImplFlag, 1);
    for (const auto& p : pick) {
        const std::vector<u8> head = read_file(p);
        if (parse_adx(head).ch == 2) decode_file(*m, p, 2, st);
    }
    w32(*m, cri::adxpd::kImplFlag, saved);
    MESSAGE("decoded " << st.files << " file runs (" << pick.size() << " kinds), " << st.chunks << " chunks, " << st.frames
                       << " frames sample-exact, " << st.ends << " end blocks; " << summary());
}

TEST_CASE("game(cri1): the decoders called directly, the exec server, odd stereo counts and the key") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0xADC};
    // random blocks with random scales (end bit clear), both decoders direct, against the host
    for (int it = 0; it < 12; ++it) {
        const u32 stereo = it % 2;
        const u32 frames = 1 + rng() % 40;
        const u32 ch = stereo ? 2 : 1;
        std::vector<u8> b(frames * 18 * ch);
        for (u8& x : b) x = static_cast<u8>(rng());
        for (u32 f = 0; f < frames * ch; ++f) b[f * 18] &= 0x1F;  // scale < 0x2000, no end bit
        fill(*m, kSrc, b);
        const s32 c1 = static_cast<s32>(rng() % 8192);
        const s32 c2 = -static_cast<s32>(rng() % 4096);
        HostHist hh[2];
        hh[0].h1 = static_cast<s16>(rng());
        hh[0].h2 = static_cast<s16>(rng());
        hh[1].h1 = static_cast<s16>(rng());
        hh[1].h2 = static_cast<s16>(rng());
        w16(*m, kOut + 0, static_cast<u16>(hh[0].h1));
        w16(*m, kOut + 2, static_cast<u16>(hh[0].h2));
        w16(*m, kOut + 4, static_cast<u16>(hh[1].h1));
        w16(*m, kOut + 6, static_cast<u16>(hh[1].h2));
        w16(*m, kOut + 8, 0);  // key 0: the XOR is the identity
        const u32 impl = rng() % 2;
        w32(*m, cri::adxpd::kImplFlag, impl);
        s32 ret = 0;
        if (!stereo)
            ret = sv(prv(*m, 0x53A410, {kSrc, frames, kPcmL, kOut}, tregs(static_cast<u64>(c1), sx(static_cast<u32>(c2)), kOut + 8, 0), {0}));
        else
            ret = sv(prv(*m, 0x53AD00, {kSrc, frames * 2, kPcmL, kOut},
                         tregs(kPcmR, kOut + 4, static_cast<u64>(c1), sx(static_cast<u32>(c2))), {kOut + 8, 0, 0}));
        CHECK(ret == static_cast<s32>(frames * ch));
        for (u32 f = 0; f < frames; ++f) {
            s16 want[2][32];
            for (u32 c = 0; c < ch; ++c) host_frame(&b[(f * ch + c) * 18], want[c], hh[c], c1, c2);
            if (stereo && impl) {  // the downmix: both outputs (L + R) * 7 / 10
                s16 mix[32];
                host_downmix(want[0], want[1], mix);
                std::memcpy(want[0], mix, 64);
                std::memcpy(want[1], mix, 64);
            }
            for (u32 c = 0; c < ch; ++c) CHECK(std::memcmp(m->at((c ? kPcmR : kPcmL) + f * 64), want[c], 64) == 0);
        }
        CHECK(static_cast<s16>(r16(*m, kOut + 0)) == hh[0].h1);
        CHECK(static_cast<s16>(r16(*m, kOut + 2)) == hh[0].h2);
        if (stereo) {
            CHECK(static_cast<s16>(r16(*m, kOut + 4)) == hh[1].h1);
            CHECK(static_cast<s16>(r16(*m, kOut + 6)) == hh[1].h2);
        }
    }
    w32(*m, cri::adxpd::kImplFlag, 0);
    // a running key: (key * mult + add) & 0x7FFF per block, XORed into the scale (both decoders)
    for (int it = 0; it < 6; ++it) {
        const u32 stereo = it % 2;
        const u32 frames = 4 + rng() % 8;
        const u32 ch = stereo ? 2 : 1;
        std::vector<u8> b(frames * 18 * ch);
        for (u8& x : b) x = static_cast<u8>(rng());
        for (u32 f = 0; f < frames * ch; ++f) b[f * 18] &= 0x7F;  // no end bit
        fill(*m, kSrc, b);
        const u16 key0 = static_cast<u16>(rng() & 0x7FFF);
        const s16 mul = static_cast<s16>(rng() & 0x7FFF);
        const s16 add = static_cast<s16>(rng() & 0x7FFF);
        zero(*m, kOut, 16);
        w16(*m, kOut + 8, key0);
        if (!stereo)
            pr(*m, 0x53A410, {kSrc, frames, kPcmL, kOut}, tregs(0x700, sx(static_cast<u32>(-0x300)), kOut + 8, static_cast<u64>(mul)),
               {static_cast<u64>(add)});
        else
            pr(*m, 0x53AD00, {kSrc, frames * 2, kPcmL, kOut}, tregs(kPcmR, kOut + 4, 0x700, sx(static_cast<u32>(-0x300))),
               {kOut + 8, static_cast<u64>(mul), static_cast<u64>(add)});
        // host: descramble the scales with the key sequence, then the plain decoder
        u32 key = key0;
        std::vector<u8> plain = b;
        for (u32 f = 0; f < frames * ch; ++f) {
            const u16 sc = be16(&plain[f * 18]);
            const u16 ds = static_cast<u16>(sc ^ key);
            plain[f * 18] = static_cast<u8>(ds >> 8);
            plain[f * 18 + 1] = static_cast<u8>(ds);
            key = (key * static_cast<u32>(static_cast<s32>(mul)) + static_cast<u32>(static_cast<s32>(add))) & 0x7FFF;
        }
        HostHist hh[2];
        bool same = true;
        for (u32 f = 0; f < frames; ++f)
            for (u32 c = 0; c < ch; ++c) {
                s16 want[32];
                std::vector<u8> fr(plain.begin() + (f * ch + c) * 18, plain.begin() + (f * ch + c) * 18 + 18);
                fr[0] &= 0x1F;  // the decoders mask the descrambled scale to 13 bits
                host_frame(fr.data(), want, hh[c], 0x700, -0x300);
                same = same && std::memcmp(m->at((c ? kPcmR : kPcmL) + f * 64), want, 64) == 0;
            }
        CHECK(same);
        CHECK(r16(*m, kOut + 8) == key);
    }
    // odd stereo block count: the stereo decoder returns it, the object flags the error (0x793B78)
    {
        pr(*m, 0x54CB78, {0, 0, 0, 0});
        const u32 obj = uv(prv(*m, 0x54CBC8, {0, 0, 0, 0}));
        std::vector<u8> b(18 * 6, 0);
        fill(*m, kSrc, b);
        w32(*m, cri::adxpd::kErrorFlag, 0);
        CHECK(prv(*m, 0x54CDB8, {obj, kSrc, 5, kPcmL}, tregs(kPcmR)) == 1);
        w32(*m, obj + cri::adxpd::kState, 1);
        pr(*m, 0x54CE90, {obj, 0, 0, 0});
        CHECK(r32(*m, obj + cri::adxpd::kDecoded) == 5);
        CHECK(r32(*m, cri::adxpd::kErrorFlag) == 1);
        // a busy object refuses a new job
        w32(*m, obj + cri::adxpd::kState, 2);
        CHECK(prv(*m, 0x54CD88, {obj, kSrc, 2, kPcmL}, tregs(0)) == 0);
        CHECK(prv(*m, 0x54CDE8, {obj, kSrc, 2, kPcmL}, tregs(0)) == 0);
        pr(*m, 0x54CE38, {obj, 0, 0, 0});  // stop: idle, histories cleared
        CHECK(r32(*m, obj + cri::adxpd::kState) == 0);
        CHECK(r32(*m, obj + cri::adxpd::kHistL) == 0);
        CHECK(prv(*m, 0x54CDE8, {obj, kSrc, 2, kPcmL}, tregs(kPcmR)) == 1);
        CHECK(r32(*m, obj + cri::adxpd::kKind) == 1);
        CHECK(r32(*m, obj + cri::adxpd::kDstR) == kPcmR);
        // the key, the mode word, the histories through the accessors
        pr(*m, 0x54CD10, {obj, 0x1234, 0x0567, 0x0089});
        CHECK(r16(*m, obj + cri::adxpd::kKey) == 0x1234);
        CHECK(r16(*m, obj + cri::adxpd::kKeyMul) == 0x0567);
        CHECK(r16(*m, obj + cri::adxpd::kKeyAdd) == 0x0089);
        pr(*m, 0x54CD78, {obj, 7, 0, 0});
        CHECK(r32(*m, obj + cri::adxpd::kMode) == 7);
        w32(*m, kOut, 0x00220011);
        w32(*m, kOut + 4, 0x00440033);
        pr(*m, 0x54CCC0, {obj, kOut, kOut + 4, 0});
        zero(*m, kOut + 8, 8);
        pr(*m, 0x54CCE8, {obj, kOut + 8, kOut + 12, 0});
        CHECK(r32(*m, kOut + 8) == 0x00220011);
        CHECK(r32(*m, kOut + 12) == 0x00440033);
        CHECK(uv(prv(*m, 0x54CD80, {obj, 0, 0, 0})) == 0);
        // the exec server runs every used object: two started jobs
        const u32 obj2 = uv(prv(*m, 0x54CBC8, {0, 0, 0, 0}));
        CHECK(obj2 == obj + cri::adxpd::kSize);
        CHECK(prv(*m, 0x54CD88, {obj2, kSrc, 3, kPcmL + 0x1000}, tregs(0)) == 1);
        w32(*m, obj + cri::adxpd::kState, 1);
        w32(*m, obj2 + cri::adxpd::kState, 1);
        pr(*m, 0x54CF88, {0, 0, 0, 0});
        CHECK(r32(*m, obj + cri::adxpd::kState) == 3);
        CHECK(r32(*m, obj2 + cri::adxpd::kState) == 3);
        CHECK(r32(*m, obj2 + cri::adxpd::kDecoded) == 3);
        pr(*m, 0x54CBA0, {0, 0, 0, 0});  // finish: the pool cleared
        CHECK(r32(*m, obj + cri::adxpd::kUsed) == 0);
        CHECK(r32(*m, obj2 + cri::adxpd::kUsed) == 0);
    }
    MESSAGE("direct decoders: " << summary());
}

// =====================================================================================================================
// The stream joints against host models of their rules
// =====================================================================================================================
namespace {

// The host model of an SJRBF ring: line 0 = free bytes, line 1 = data; a chunk is never longer than the bytes up to
// the buffer's end plus the extra area; a put on line 1 mirrors what ran into the extra area back to the start and
// what lies in the first `extra` bytes into the extra area.
struct RingModel {
    u32 size = 0, xtr = 0;
    s32 freeb = 0, data = 0, pos0 = 0, pos1 = 0;
    s32 got0 = 0, put0 = 0, got1 = 0, put1 = 0;
    std::vector<u8> mem;  // size + xtr bytes, the buffer's contents
};
void check_ring(Machine& m, u32 h, const RingModel& r) {
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kFree)) == r.freeb);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kData)) == r.data);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kPos0)) == r.pos0);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kPos1)) == r.pos1);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kGot0)) == r.got0);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kPut0)) == r.put0);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kGot1)) == r.got1);
    CHECK(static_cast<s32>(r32(m, h + cri::sjrbf::kPut1)) == r.put1);
    CHECK(std::memcmp(m.at(kRing), r.mem.data(), r.mem.size()) == 0);
    // conservation: free + data + the chunks still out on either side = the size
    CHECK(r.freeb + r.data + (r.got0 - r.put1) + (r.got1 - r.put0) == static_cast<s32>(r.size));
}

}  // namespace

TEST_CASE("game(cri1): SJRBF ring buffers against the host model (get / put / unget / is-get / counts, the extra area)") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0x5B};
    int ops = 0;
    pr(*m, 0x562288, {0, 0, 0, 0});  // SJRBF init (the SVM lock callbacks are null in the ELF image: no call)
    for (int round = 0; round < 6; ++round) {
        RingModel r;
        r.size = 64 + rng() % 4000;
        const u32 kx = rng() % 3;
        const u32 xv = rng() % std::min(200u, r.size);  // the extra area never larger than the buffer
        r.xtr = kx == 0 ? 0 : xv;
        r.mem.assign(r.size + r.xtr, 0);
        for (u8& x : r.mem) x = static_cast<u8>(rng());
        fill(*m, kRing, r.mem);
        const u32 h = uv(prv(*m, 0x562388, {kRing, r.size, r.xtr, 0}));
        CHECK(h == cri::sjrbf::kPool + cri::sjrbf::kSize * static_cast<u32>(round));
        CHECK(r32(*m, h + cri::sj::kVtbl) == cri::sjrbf::kVtable);
        CHECK(r32(*m, h + cri::sjrbf::kBuf) == kRing);
        r.freeb = static_cast<s32>(r.size);
        check_ring(*m, h, r);
        CHECK(uv(prv(*m, 0x562568, {h, 0, 0, 0})) == 0x7C6950u);  // the uuid
        // outstanding chunks: got from a line, not yet put to the other (FIFO per line)
        std::deque<std::pair<u32, s32>> out0, out1;
        for (int it = 0; it < 120; ++it) {
            ++ops;
            const u32 op = rng() % 7;
            const u32 line = rng() % 2;
            const bool locked = rng() % 2 == 0;  // the locked wrapper or the body directly
            s32& pos = line ? r.pos1 : r.pos0;
            s32& avail = line ? r.data : r.freeb;
            if (op <= 1) {  // get a chunk
                const s32 n = static_cast<s32>(rng() % (r.size / 2 + 8));
                zero(*m, kOut, 8);
                pr(*m, locked ? 0x562680 : 0x5626E0, {h, line, static_cast<u64>(n), kOut});
                const s32 len = std::min({avail, static_cast<s32>(r.size) - pos + static_cast<s32>(r.xtr), n});
                CHECK(r32(*m, kOut) == kRing + static_cast<u32>(pos));
                CHECK(static_cast<s32>(r32(*m, kOut + 4)) == len);
                (line ? out1 : out0).emplace_back(kRing + static_cast<u32>(pos), len);
                pos = (pos + len) % static_cast<s32>(r.size);
                avail -= len;
                (line ? r.got1 : r.got0) += len;
            } else if (op <= 3) {  // put the oldest outstanding chunk of a line to the other line
                auto& q = line ? out1 : out0;
                if (q.empty()) continue;
                const auto [ptr, len] = q.front();
                q.pop_front();
                const u32 to = line ? 0 : 1;
                if (to == 1) {  // fresh data written into the chunk first
                    for (s32 i = 0; i < len; ++i) r.mem[ptr - kRing + static_cast<u32>(i)] = static_cast<u8>(rng());
                    std::memcpy(m->at(ptr), &r.mem[ptr - kRing], static_cast<std::size_t>(len));
                }
                w32(*m, kOut, ptr);
                w32(*m, kOut + 4, static_cast<u32>(len));
                pr(*m, locked ? 0x562880 : 0x5628D0, {h, to, kOut, 0});
                if (len > 0) {
                    if (to == 1) {
                        const s32 off = static_cast<s32>(ptr - kRing);
                        if (off < static_cast<s32>(r.xtr)) {
                            const s32 n1 = std::min(len, static_cast<s32>(r.xtr) - off);
                            std::memmove(&r.mem[r.size + static_cast<u32>(off)], &r.mem[static_cast<u32>(off)], static_cast<std::size_t>(n1));
                        }
                        const s32 end = off + len;
                        if (end > static_cast<s32>(r.size)) {
                            const s32 n2 = std::min(len, end - static_cast<s32>(r.size));
                            std::memmove(&r.mem[0], &r.mem[static_cast<u32>(end - n2)], static_cast<std::size_t>(n2));
                        }
                        r.data += len;
                        r.put1 += len;
                    } else {
                        r.freeb += len;
                        r.put0 += len;
                    }
                }
            } else if (op == 4) {  // unget the newest outstanding chunk of a line
                auto& q = line ? out1 : out0;
                if (q.empty()) continue;
                const auto [ptr, len] = q.back();
                q.pop_back();
                w32(*m, kOut, ptr);
                w32(*m, kOut + 4, static_cast<u32>(len));
                pr(*m, locked ? 0x562A50 : 0x562AA0, {h, line, kOut, 0});
                if (len > 0) {
                    const s32 back = (pos + static_cast<s32>(r.size) - len) % static_cast<s32>(r.size);
                    CHECK(back == static_cast<s32>(ptr - kRing) % static_cast<s32>(r.size));  // it was the last chunk got
                    pos = back;
                    avail += len;
                    (line ? r.got1 : r.got0) -= len;
                }
            } else if (op == 5) {  // is a chunk of n available
                const s32 n = static_cast<s32>(rng() % (r.size + 16));
                const s32 got = sv(prv(*m, locked ? 0x562C80 : 0x562CE8, {h, line, static_cast<u64>(n), kOut}));
                const s32 len = std::min({avail, static_cast<s32>(r.size) - pos + static_cast<s32>(r.xtr), n});
                CHECK(static_cast<s32>(r32(*m, kOut)) == len);
                CHECK(got == (len == n ? 1 : 0));
            } else {  // bytes on a line
                CHECK(sv(prv(*m, 0x562630, {h, line, 0, 0})) == avail);
            }
            check_ring(*m, h, r);
        }
        CHECK(uv(prv(*m, 0x562210, {h, 0, 0, 0})) == static_cast<u32>(r.pos0));
        CHECK(uv(prv(*m, 0x562218, {h, 0, 0, 0})) == static_cast<u32>(r.pos1));
        // reset: everything free again; then destroy the odd rounds' handles
        pr(*m, round % 2 ? 0x562580 : 0x5625B0, {h, 0, 0, 0});
        r = RingModel{r.size, r.xtr, static_cast<s32>(r.size), 0, 0, 0, 0, 0, 0, 0, r.mem};
        check_ring(*m, h, r);
        pr(*m, 0x562570, {h, 0x562220, h, 0});  // the error callback entry
        CHECK(r32(*m, h + cri::sjrbf::kErrFn) == 0x562220u);
    }
    // destroy, then the slot is taken again first
    pr(*m, 0x5624B0, {cri::sjrbf::kPool + cri::sjrbf::kSize, 0, 0, 0});
    CHECK(r32(*m, cri::sjrbf::kPool + cri::sjrbf::kSize + cri::sj::kUsed) == 0);
    CHECK(uv(prv(*m, 0x5623E0, {kRing, 256, 0, 0})) == cri::sjrbf::kPool + cri::sjrbf::kSize);
    pr(*m, 0x562308, {0, 0, 0, 0});  // finish: the last finish clears the pool
    CHECK(r32(*m, cri::sjrbf::kPool + cri::sj::kUsed) == 0);
    MESSAGE("SJRBF: " << ops << " operations against the model; " << summary());
}

TEST_CASE("game(cri1): SJMEM (a memory block read once) and SJUNI (chunk lists over a node pool) against host models") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0x51};
    int ops = 0;
    // ---- SJMEM: line 1 hands out the block front to back; unget steps back
    pr(*m, 0x561870, {0, 0, 0, 0});
    for (int round = 0; round < 4; ++round) {
        const u32 size = 16 + rng() % 5000;
        const u32 h = uv(prv(*m, 0x561970, {kRing, size, 0, 0}));
        CHECK(h == cri::sjmem::kPool + cri::sjmem::kSize * static_cast<u32>(round));
        CHECK(r32(*m, h + cri::sj::kVtbl) == cri::sjmem::kVtable);
        s32 left = static_cast<s32>(size), off = 0;
        std::deque<std::pair<u32, s32>> out;
        for (int it = 0; it < 60; ++it) {
            ++ops;
            const u32 op = rng() % 5;
            const bool locked = rng() % 2 == 0;
            if (op <= 1) {
                const s32 n = static_cast<s32>(rng() % (size / 3 + 4));
                const u32 line = rng() % 4 == 0 ? 0u : 1u;
                zero(*m, kOut, 8);
                pr(*m, locked ? 0x561D58 : 0x561DB8, {h, line, static_cast<u64>(n), kOut});
                if (line == 1) {
                    const s32 len = std::min(left, n);
                    CHECK(r32(*m, kOut) == kRing + static_cast<u32>(off));
                    CHECK(static_cast<s32>(r32(*m, kOut + 4)) == len);
                    out.emplace_back(kRing + static_cast<u32>(off), len);
                    off += len;
                    left -= len;
                } else {
                    CHECK(r32(*m, kOut + 4) == 0);  // line 0 gives an empty chunk
                }
            } else if (op == 2) {
                if (out.empty()) continue;
                const auto [ptr, len] = out.back();
                out.pop_back();
                w32(*m, kOut, ptr);
                w32(*m, kOut + 4, static_cast<u32>(len));
                pr(*m, locked ? 0x561F88 : 0x561FD8, {h, 1, kOut, 0});
                if (len > 0) {
                    off = std::max(off - len, 0);
                    left = std::min(left + len, static_cast<s32>(size));
                }
            } else if (op == 3) {
                const s32 n = static_cast<s32>(rng() % (size + 8));
                const s32 got = sv(prv(*m, locked ? 0x5620D8 : 0x562140, {h, 1, static_cast<u64>(n), kOut}));
                CHECK(static_cast<s32>(r32(*m, kOut)) == std::min(left, n));
                CHECK(got == (std::min(left, n) == n ? 1 : 0));
            } else {
                CHECK(sv(prv(*m, 0x561D10, {h, 1, 0, 0})) == left);
                CHECK(sv(prv(*m, 0x561D10, {h, 0, 0, 0})) == 0);
                // a put on either line is accepted and dropped
                w32(*m, kOut, kRing);
                w32(*m, kOut + 4, 4);
                const u32 put_line = rng() % 2;
                const u64 rv = prv(*m, locked ? 0x561E98 : 0x561EE8, {h, put_line, kOut, 0});
                if (!locked) CHECK(rv == 1);  // (the locked wrapper returns the unlock's $v0)
            }
            CHECK(static_cast<s32>(r32(*m, h + cri::sjmem::kLeft)) == left);
            CHECK(static_cast<s32>(r32(*m, h + cri::sjmem::kOffset)) == off);
        }
        pr(*m, round % 2 ? 0x561C78 : 0x561CA8, {h, 0, 0, 0});
        CHECK(r32(*m, h + cri::sjmem::kLeft) == size);
        CHECK(r32(*m, h + cri::sjmem::kOffset) == 0);
        CHECK(uv(prv(*m, round % 2 ? 0x561B38 : 0x561B70, {h, 0, 0, 0})) == 0x7C67F0u);
        pr(*m, round % 2 ? 0x561BC8 : 0x561C18, {h, 0x561808, h, 0});
    }
    pr(*m, 0x561A80, {cri::sjmem::kPool, 0, 0, 0});
    CHECK(r32(*m, cri::sjmem::kPool + cri::sj::kUsed) == 0);
    pr(*m, 0x5618F0, {0, 0, 0, 0});

    // ---- SJUNI: four lines of {data, size} chunks; merge mode joins contiguous chunks and splits on get
    pr(*m, 0x562E90, {0, 0, 0, 0});
    for (int round = 0; round < 4; ++round) {
        const u32 merge = round % 2;
        const u32 nodes = 4 + rng() % 24;
        const u32 h = uv(prv(*m, 0x562F90, {merge, kNodes, nodes * 16, 0}));
        CHECK(h == cri::sjuni::kPool + cri::sjuni::kSize * static_cast<u32>(round));
        CHECK(r8(*m, h + cri::sjuni::kMerge) == merge);
        CHECK(r32(*m, h + cri::sjuni::kNodes) == nodes);
        std::vector<std::deque<std::pair<u32, s32>>> lines(4);
        u32 free_nodes = nodes;
        u32 next = kRing;  // chunks handed in: contiguous runs most of the time
        for (int it = 0; it < 80; ++it) {
            ++ops;
            const u32 op = rng() % 6;
            const u32 line = rng() % 4;
            const bool locked = rng() % 2 == 0;
            auto& q = lines[line];
            if (op <= 1) {  // put at the tail
                const s32 len = 1 + static_cast<s32>(rng() % 300);
                if (rng() % 4 == 0) next += 16;  // a gap: not contiguous
                w32(*m, kOut, next);
                w32(*m, kOut + 4, static_cast<u32>(len));
                pr(*m, locked ? 0x563680 : 0x5636D0, {h, line, kOut, 0});
                if (merge && !q.empty() && q.back().first + static_cast<u32>(q.back().second) == next) {
                    q.back().second += len;
                } else if (free_nodes > 0) {
                    q.emplace_back(next, len);
                    --free_nodes;
                }  // (no node left: the error callback, none set here)
                next += static_cast<u32>(len);
            } else if (op == 2) {  // get from the head
                const s32 n = 1 + static_cast<s32>(rng() % 400);
                zero(*m, kOut, 8);
                pr(*m, locked ? 0x5634D0 : 0x563530, {h, line, static_cast<u64>(n), kOut});
                if (q.empty()) {
                    CHECK(r32(*m, kOut + 4) == 0);
                } else if (n >= q.front().second) {
                    CHECK(r32(*m, kOut) == q.front().first);
                    CHECK(static_cast<s32>(r32(*m, kOut + 4)) == q.front().second);
                    q.pop_front();
                    ++free_nodes;
                } else if (merge) {
                    CHECK(r32(*m, kOut) == q.front().first);
                    CHECK(static_cast<s32>(r32(*m, kOut + 4)) == n);
                    q.front().first += static_cast<u32>(n);
                    q.front().second -= n;
                } else {
                    CHECK(r32(*m, kOut) == 0);
                    CHECK(r32(*m, kOut + 4) == 0);
                }
            } else if (op == 3) {  // unget at the head: the chunk just before the head (merge) or anything
                const s32 len = 1 + static_cast<s32>(rng() % 64);
                const u32 adjacent = rng() % 2;
                const u32 far = kRing + 0x8000 + rng() % 0x1000;
                const u32 ptr = (!q.empty() && adjacent) ? q.front().first - static_cast<u32>(len) : far;
                w32(*m, kOut, ptr);
                w32(*m, kOut + 4, static_cast<u32>(len));
                pr(*m, locked ? 0x5637F8 : 0x563848, {h, line, kOut, 0});
                if (merge && !q.empty() && ptr + static_cast<u32>(len) == q.front().first) {
                    q.front().first = ptr;
                    q.front().second += len;
                } else if (free_nodes > 0) {
                    q.emplace_front(ptr, len);
                    --free_nodes;
                }
            } else if (op == 4) {  // is a chunk of n available
                const s32 n = 1 + static_cast<s32>(rng() % 400);
                const s32 got = sv(prv(*m, locked ? 0x563968 : 0x5639D0, {h, line, static_cast<u64>(n), kOut}));
                const s32 head = q.empty() ? 0 : q.front().second;
                CHECK(static_cast<s32>(r32(*m, kOut)) == head);
                CHECK(got == (q.empty() ? 0 : merge ? (head >= n ? 1 : 0) : (head == n ? 1 : 0)));
            } else {  // counts
                s32 bytes = 0;
                for (const auto& c : q) bytes += c.second;
                CHECK(sv(prv(*m, locked ? 0x5633D0 : 0x563418, {h, line, 0, 0})) == bytes);
                CHECK(uv(prv(*m, locked ? 0x563A98 : 0x563AE0, {h, line, 0, 0})) == q.size());
                CHECK(uv(prv(*m, locked ? 0x563B70 : 0x563BA8, {h, 0, 0, 0})) == free_nodes);
            }
        }
        pr(*m, round % 2 ? 0x5632C8 : 0x5632F8, {h, 0, 0, 0});  // reset: every node free, lines empty
        CHECK(uv(prv(*m, 0x563BA8, {h, 0, 0, 0})) == nodes);
        CHECK(uv(prv(*m, round % 2 ? 0x563188 : 0x5631C0, {h, 0, 0, 0})) == 0x7C6AA8u);
        pr(*m, round % 2 ? 0x563218 : 0x563268, {h, 0x562E28, h, 0});
    }
    pr(*m, 0x5630D0, {cri::sjuni::kPool, 0, 0, 0});
    CHECK(r8(*m, cri::sjuni::kPool + cri::sj::kUsed) == 0);
    pr(*m, 0x562F10, {0, 0, 0, 0});
    // SJ_SplitChunk: {data, size} at n
    for (int it = 0; it < 12; ++it) {
        const u32 data = kRing + rng() % 0x1000;
        const s32 size = static_cast<s32>(rng() % 500);
        const s32 n = static_cast<s32>(rng() % 600);
        w32(*m, kOut, data);
        w32(*m, kOut + 4, static_cast<u32>(size));
        zero(*m, kOut + 8, 16);
        pr(*m, 0x563C28, {kOut, static_cast<u64>(n), kOut + 8, kOut + 16});
        const s32 first = std::min(size, n);
        CHECK(r32(*m, kOut + 8) == data);
        CHECK(static_cast<s32>(r32(*m, kOut + 12)) == first);
        CHECK(static_cast<s32>(r32(*m, kOut + 20)) == size - first);
        CHECK(r32(*m, kOut + 16) == (size - first ? data + static_cast<u32>(first) : 0u));
    }
    MESSAGE("SJMEM / SJUNI: " << ops << " operations against the models; " << summary());
}

TEST_CASE("game(cri1): stream-joint bad lines, null and dead handles (error callbacks through stand-ins)") {
    auto m = machine();
    if (!m) return;
    constexpr u32 kErrCb = 0x55E978u;  // an error callback: a recorder at a function no test emits
    const WorldSetup world = [](StandInWorld& w) {
        install_sprintf(w.si);
        w.si.install_recorder(kErrCb, "svm_err_cb", 0, 4);
        w.si.install_recorder(0x53F8B8u, "svm_lock_cb", 0, 4);
        w.si.install_recorder(0x53F940u, "svm_unlock_cb", 0, 4);
        w.si.install_recorder(0x55EA00u, "sj_err_cb", 0, 4);
    };
    w32(*m, cri::svm::kErrFn, kErrCb);
    w32(*m, cri::svm::kErrFn + 4, 0x1234);
    // a null handle: "E2004090211 : NULL pointer is specified." through sjrbf_Error -> SVM_CallErr1 -> the callback
    SiResult r = pr_si(*m, 0x5626E0, {0, 1, 8, kOut}, world);
    REQUIRE(r.log.size() == 1);
    CHECK(r.log[0].va == kErrCb);
    CHECK(r.log[0].args[0] == 0x1234);
    CHECK(cstr(*m, cri::svm::kErrText) == "E2004090211 : NULL pointer is specified.");
    // a dead handle
    zero(*m, kScratch, 64);
    pr_si(*m, 0x561DB8, {kScratch, 1, 8, kOut}, world);
    CHECK(cstr(*m, cri::svm::kErrText) == "E2004090242 : Specified handle is invalid.");
    pr_si(*m, 0x563530, {kScratch, 1, 8, kOut}, world);
    CHECK(cstr(*m, cri::svm::kErrText) == "E2004090272 : Specified handle is invalid.");
    // a bad line calls the handle's own error callback with -3
    pr(*m, 0x562288, {0, 0, 0, 0});
    const u32 h = uv(prv(*m, 0x5623E0, {kRing, 256, 0, 0}));
    w32(*m, h + cri::sjrbf::kErrFn, 0x55EA00u);
    w32(*m, h + cri::sjrbf::kErrObj, 0x77);
    r = pr_si(*m, 0x5626E0, {h, 2, 8, kOut}, world);
    REQUIRE(r.log.size() == 1);
    CHECK(r.log[0].va == 0x55EA00u);
    CHECK(r.log[0].args[0] == 0x77);
    CHECK(sv(r.log[0].args[1]) == -3);
    r = pr_si(*m, 0x562630, {h, 5, 0, 0}, world);
    CHECK(r.log.size() == 1);
    CHECK(r.v0 == 0);
    // the locked wrappers through the game's SVM lock callbacks (the ADX setup's 0x53F8B8 / 0x53F940)
    w32(*m, cri::svm::kLockFn, 0x53F8B8u);
    w32(*m, cri::svm::kUnlockFn, 0x53F940u);
    w32(*m, cri::svm::kLockDepth, 0);
    r = pr_si(*m, 0x562680, {h, 0, 16, kOut}, world);
    REQUIRE(r.log.size() == 2);
    CHECK(r.log[0].va == 0x53F8B8u);
    CHECK(r.log[1].va == 0x53F940u);
    CHECK(r32(*m, kOut + 4) == 16);
    CHECK(r32(*m, cri::svm::kLockDepth) == 0);
    w32(*m, cri::svm::kLockFn, 0);
    w32(*m, cri::svm::kUnlockFn, 0);
    MESSAGE("error paths: " << summary());
}

// =====================================================================================================================
// SVM lock / unlock / errors
// =====================================================================================================================
TEST_CASE("game(cri1): SVM lock depth and type, the type-mismatch report, the error texts") {
    auto m = machine();
    if (!m) return;
    // the ADX setup's lock / unlock callbacks; the error callback a recorder at a function no test emits (the game's
    // 0x197F80 is hand-written now: it cannot be stood in)
    constexpr u32 kLockCb = 0x53F8B8u, kUnlockCb = 0x53F940u, kErrCb = 0x55E978u;
    const WorldSetup world = [](StandInWorld& w) {
        install_sprintf(w.si);
        w.si.install_recorder(kLockCb, "lock", 0, 4);
        w.si.install_recorder(kUnlockCb, "unlock", 0, 4);
        w.si.install_recorder(kErrCb, "err", 0, 4);
    };
    w32(*m, cri::svm::kLockFn, kLockCb);
    w32(*m, cri::svm::kLockFn + 4, 0x11);
    w32(*m, cri::svm::kUnlockFn, kUnlockCb);
    w32(*m, cri::svm::kUnlockFn + 4, 0x22);
    w32(*m, cri::svm::kErrFn, kErrCb);
    w32(*m, cri::svm::kErrFn + 4, 0x33);
    w32(*m, cri::svm::kLockDepth, 0);
    w32(*m, cri::svm::kLockType, 0);
    const u32 locks[5] = {0x564978, 0x5649A8, 0x5649C0, 0x5649D8, 0x5649F0};
    const u32 unlocks[5] = {0x564990, 0x564A20, 0x564A38, 0x564A50, 0x564A68};
    for (u32 t = 0; t < 5; ++t) {
        SiResult r = pr_si(*m, locks[t], {0, 0, 0, 0}, world);
        REQUIRE(r.log.size() == 1);
        CHECK(r.log[0].va == kLockCb);
        CHECK(r.log[0].args[0] == 0x11);
        CHECK(r32(*m, cri::svm::kLockDepth) == 1);
        CHECK(r32(*m, cri::svm::kLockType) == t + 1);
        pr_si(*m, locks[(t + 1) % 5], {0, 0, 0, 0}, world);  // nested: the type stays the outermost one
        CHECK(r32(*m, cri::svm::kLockDepth) == 2);
        CHECK(r32(*m, cri::svm::kLockType) == t + 1);
        pr_si(*m, unlocks[(t + 1) % 5], {0, 0, 0, 0}, world);
        CHECK(r32(*m, cri::svm::kLockDepth) == 1);
        r = pr_si(*m, unlocks[t], {0, 0, 0, 0}, world);  // the outermost unlock: type checked, cleared
        REQUIRE(r.log.size() == 1);
        CHECK(r.log[0].va == kUnlockCb);
        CHECK(r32(*m, cri::svm::kLockDepth) == 0);
        CHECK(r32(*m, cri::svm::kLockType) == 0);
    }
    // a mismatched outermost unlock: reported through SVM_CallErr with both types
    pr_si(*m, locks[0], {0, 0, 0, 0}, world);
    SiResult r = pr_si(*m, unlocks[3], {0, 0, 0, 0}, world);
    REQUIRE(r.log.size() >= 2);
    const std::string text = cstr(*m, cri::svm::kErrText);
    CHECK(text.rfind("2103102:SVM:", 0) == 0);
    const std::string tail = "lock type miss match.(type org=1, type now=4)";
    CHECK(text.size() > tail.size());
    CHECK(text.substr(text.size() - tail.size()) == tail);
    CHECK(r.log.back().va == kUnlockCb);
    // SVM_CallErr1: the text (at most 127 characters) and the callback
    const std::string longtext(200, 'x');
    put_str(*m, kStr, longtext);
    r = pr_si(*m, 0x564B50, {kStr, 0, 0, 0}, world);
    REQUIRE(r.log.size() == 1);
    CHECK(r.log[0].args[0] == 0x33);
    CHECK(r.log[0].args[1] == cri::svm::kErrText);
    CHECK(cstr(*m, cri::svm::kErrText).substr(0, 127) == longtext.substr(0, 127));
    // no callbacks installed: nothing is called
    w32(*m, cri::svm::kLockFn, 0);
    w32(*m, cri::svm::kUnlockFn, 0);
    w32(*m, cri::svm::kErrFn, 0);
    r = pr_si(*m, 0x564978, {0, 0, 0, 0}, world);
    CHECK(r.log.empty());
    r = pr_si(*m, 0x564B50, {kStr, 0, 0, 0}, world);
    CHECK(r.log.empty());
    MESSAGE("SVM: " << summary());
}

// =====================================================================================================================
// cvFs: the name helpers (the device registration and lookup call newlib strncmp, which test_models stands in: left)
// =====================================================================================================================
TEST_CASE("game(cri1): cvFs init, upper-casing, the DEV:file split, the default device, the error helpers") {
    auto m = machine();
    if (!m) return;
    constexpr u32 kErrCb = 0x55E978u;  // an error callback: a recorder at a function no test emits
    const WorldSetup world = [](StandInWorld& w) {
        install_sprintf(w.si);
        w.si.install_recorder(kErrCb, "cvfs_err", 0, 4);
    };
    // init: tables cleared (junk first), the counter; a second init only counts
    std::memset(m->at(cri::cvfs::kHandles), 0xEE, 40 * 8);
    std::memset(m->at(cri::cvfs::kDevices), 0xEE, cri::cvfs::kDeviceCount * cri::cvfs::kDeviceSize);
    std::memset(m->at(cri::cvfs::kDefDev), 0xEE, 9);
    w32(*m, cri::cvfs::kInitCount, 0);
    pr(*m, 0x555940, {0, 0, 0, 0});
    CHECK(r32(*m, cri::cvfs::kInitCount) == 1);
    for (u32 i = 0; i < 40 * 8; i += 4) CHECK(r32(*m, cri::cvfs::kHandles + i) == 0);
    for (u32 i = 0; i < cri::cvfs::kDeviceCount; ++i) {
        CHECK(r8(*m, cri::cvfs::kDevices + 4 + i * cri::cvfs::kDeviceSize) == 0);  // the name's first byte only
        CHECK(r32(*m, cri::cvfs::kDevices + i * cri::cvfs::kDeviceSize) == 0xEEEEEEEEu);  // the interface words stay
    }
    for (u32 i = 0; i < 9; ++i) CHECK(r8(*m, cri::cvfs::kDefDev + i) == 0);
    std::memset(m->at(cri::cvfs::kHandles), 0xEE, 8);
    pr(*m, 0x555940, {0, 0, 0, 0});
    CHECK(r32(*m, cri::cvfs::kInitCount) == 2);
    CHECK(r32(*m, cri::cvfs::kHandles) == 0xEEEEEEEEu);
    // the default device copied out (empty when none)
    put_str(*m, cri::cvfs::kDefDev, "BGM");
    std::memset(m->at(kOut), 0x77, 16);
    pr(*m, 0x556330, {kOut, 0, 0, 0});
    CHECK(cstr(*m, kOut) == "BGM");
    put_str(*m, cri::cvfs::kDefDev, "");
    pr(*m, 0x556330, {kOut, 0, 0, 0});
    CHECK(cstr(*m, kOut) == "");
    // upper-casing in place (a-z only)
    put_str(*m, kStr, "abc:Def.cvm;1 xyz{}`~");
    pr(*m, 0x555D10, {kStr, 0, 0, 0});
    CHECK(cstr(*m, kStr) == "ABC:DEF.CVM;1 XYZ{}`~");
    std::mt19937 rng{0x5D};
    for (int it = 0; it < 20; ++it) {
        std::string s(rng() % 60, 'a');
        for (char& ch : s) ch = static_cast<char>(1 + rng() % 255);
        put_str(*m, kStr, s);
        pr(*m, 0x555D10, {kStr, 0, 0, 0});
        std::string want = s;
        for (char& ch : want)
            if (ch >= 'a' && ch <= 'z') ch = static_cast<char>(ch - 32);
        CHECK(cstr(*m, kStr) == want);
    }
    // "DEV:file" splitting: device upper-cased, one-letter devices stay in the file name, no colon -> no device
    const std::vector<std::tuple<std::string, std::string, std::string>> paths = {
        {"cdv:data.cvm", "CDV", "data.cvm"}, {"VOL:\\FIELD\\F001.PAK", "VOL", "\\FIELD\\F001.PAK"},
        {"data.cvm", "", "data.cvm"}, {"c:\\x.bin", "", "c:\\x.bin"}, {":x", "", "x"}, {"rofs:VOL:a", "ROFS", "VOL:a"},
        {"", "", ""}, {"host0:a/b/c", "HOST0", "a/b/c"}, {"BGM:", "BGM", ""}};
    for (const auto& [in, dev, file] : paths) {
        INFO(in);
        put_str(*m, kStr, in);
        std::memset(m->at(kOut), 0x77, 0x200);
        std::memset(m->at(kScratch), 0x77, 0x200);
        pr(*m, 0x5561E8, {kScratch, kOut, kStr, 0});
        CHECK(cstr(*m, kScratch) == dev);
        CHECK(cstr(*m, kOut) == file);
    }
    // the error helpers: the message through the cvFs error callback (0x7A08A4 / its object 0x7A08A8)
    w32(*m, cri::cvfs::kErrFn, kErrCb);
    w32(*m, cri::cvfs::kErrFn + 4, 0x4242);
    put_str(*m, kStr, "cvFsOpen #1:illegal file name");
    SiResult r = pr_si(*m, 0x555918, {kStr, 0, 0, 0}, world);
    REQUIRE(r.log.size() == 1);
    CHECK(r.log[0].va == kErrCb);
    CHECK(r.log[0].args[0] == 0x4242);
    r = pr_si(*m, 0x5558E8, {cri::cvfs::kErrFn + 4, kStr, 0, 0}, world);
    CHECK(r.log.size() == 1);
    w32(*m, cri::cvfs::kErrFn, 0);
    r = pr_si(*m, 0x555918, {kStr, 0, 0, 0}, world);
    CHECK(r.log.empty());
    MESSAGE("cvFs: " << summary());
}

// =====================================================================================================================
// The replay snapshots' live CRI state
// =====================================================================================================================
TEST_CASE("game(cri1): the snapshots' live stream joints, decoder objects and cvFs device table") {
    for (const char* dir : {"b_5800", "dorm_replay_4900"}) {
        auto m = snapshot_machine(dir);
        if (!m) continue;
        INFO(dir);
        // the SVM lock callbacks of the running game are not emitted here: clear them (the lock path is tested above)
        w32(*m, cri::svm::kLockFn, 0);
        w32(*m, cri::svm::kUnlockFn, 0);
        int rings = 0, unis = 0, objs = 0;
        // SJRBF handles: the counts and the is-get rule on both lines, the conservation rule
        for (u32 i = 0; i < cri::sjrbf::kCount; ++i) {
            const u32 h = cri::sjrbf::kPool + i * cri::sjrbf::kSize;
            if (!r32(*m, h + cri::sj::kUsed)) continue;
            ++rings;
            const s32 size = static_cast<s32>(r32(*m, h + cri::sjrbf::kBufSize));
            const s32 freeb = static_cast<s32>(r32(*m, h + cri::sjrbf::kFree));
            const s32 data = static_cast<s32>(r32(*m, h + cri::sjrbf::kData));
            const s32 out = static_cast<s32>(r32(*m, h + cri::sjrbf::kGot0) - r32(*m, h + cri::sjrbf::kPut1)) +
                            static_cast<s32>(r32(*m, h + cri::sjrbf::kGot1) - r32(*m, h + cri::sjrbf::kPut0));
            CHECK(freeb + data + out == size);
            CHECK(sv(prv(*m, 0x562630, {h, 0, 0, 0})) == freeb);
            CHECK(sv(prv(*m, 0x562630, {h, 1, 0, 0})) == data);
            for (u32 line = 0; line < 2; ++line) {
                const s32 pos = static_cast<s32>(r32(*m, h + (line ? cri::sjrbf::kPos1 : cri::sjrbf::kPos0)));
                const s32 n = (line ? data : freeb) + 1;
                pr(*m, 0x562CE8, {h, line, static_cast<u64>(n), kScratch});
                const s32 room = size - pos + static_cast<s32>(r32(*m, h + cri::sjrbf::kXtrSize));
                CHECK(static_cast<s32>(r32(*m, kScratch)) == std::min({line ? data : freeb, room, n}));
            }
        }
        // SJUNI handles: per-line bytes and chunk counts walk the same lists
        for (u32 i = 0; i < cri::sjuni::kCount; ++i) {
            const u32 h = cri::sjuni::kPool + i * cri::sjuni::kSize;
            if (!r8(*m, h + cri::sj::kUsed)) continue;
            ++unis;
            u32 chunks = 0;
            for (u32 line = 0; line < 4; ++line) {
                u32 bytes = 0, count = 0;
                for (u32 node = r32(*m, h + cri::sjuni::kLines + 4 * line); node && count < 1000; node = r32(*m, node)) {
                    bytes += r32(*m, node + 12);
                    ++count;
                }
                CHECK(uv(prv(*m, 0x563418, {h, line, 0, 0})) == bytes);
                CHECK(uv(prv(*m, 0x563AE0, {h, line, 0, 0})) == count);
                chunks += count;
            }
            const u32 free_nodes = uv(prv(*m, 0x563BA8, {h, 0, 0, 0}));
            CHECK(free_nodes + chunks == r32(*m, h + cri::sjuni::kNodes));
        }
        // decoder objects: the last job run again (state 1) from the same source, into the same output
        for (u32 i = 0; i < cri::adxpd::kCount; ++i) {
            const u32 obj = cri::adxpd::kPool + i * cri::adxpd::kSize;
            if (!r32(*m, obj + cri::adxpd::kUsed)) continue;
            ++objs;
            const u32 before = r32(*m, obj + cri::adxpd::kDecoded);
            CHECK(uv(prv(*m, 0x54CD80, {obj, 0, 0, 0})) == r32(*m, obj + cri::adxpd::kState));
            if (r32(*m, obj + cri::adxpd::kState) != 0) continue;
            w32(*m, obj + cri::adxpd::kState, 1);
            pr(*m, 0x54CE90, {obj, 0, 0, 0});
            CHECK(r32(*m, obj + cri::adxpd::kState) == 3);
            CHECK(r32(*m, obj + cri::adxpd::kDecoded) <= r32(*m, obj + cri::adxpd::kBlocks));
            (void)before;
        }
        // cvFs: the registered devices (not looked up here: the lookup is left recompiled), the default device copy
        int devs = 0;
        for (u32 i = 0; i < cri::cvfs::kDeviceCount; ++i)
            if (!cstr(*m, cri::cvfs::kDevices + 4 + i * cri::cvfs::kDeviceSize).empty()) ++devs;
        pr(*m, 0x556330, {kScratch, 0, 0, 0});
        CHECK(cstr(*m, kScratch) == "VOL");
        MESSAGE(std::string(dir) << ": " << rings << " SJRBF, " << unis << " SJUNI handles, " << objs << " decoder objects, " << devs
                    << " devices; " << summary());
    }
}

// =====================================================================================================================
// WAV headers, the ADXB lock counter, the stubs, the SJ library counters, the stream-record accessors
// =====================================================================================================================
TEST_CASE("game(cri1): WAV headers (sub_538F18 / sub_539148), the small ADXB / SJ helpers") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0x3A7};
    // canonical 44-byte RIFF / WAVE headers: PCM 16 / 8 bits, mono / stereo; and the 4-bit kind
    for (int it = 0; it < 12; ++it) {
        const u32 ch = 1 + static_cast<u32>(it % 2);
        const u32 bits = it % 3 == 0 ? 8u : it % 3 == 1 ? 16u : 4u;
        const u32 rate = 8000 + rng() % 40000;
        const u32 align = bits == 4 ? 36u * ch : ch * bits / 8;
        const u32 frames = 1 + rng() % 5000;
        const u32 size = frames * align;
        std::vector<u8> b(44, 0);
        auto le32 = [&](u32 off, u32 v) { for (int i = 0; i < 4; ++i) b[off + i] = static_cast<u8>(v >> (8 * i)); };
        auto le16 = [&](u32 off, u32 v) { b[off] = static_cast<u8>(v); b[off + 1] = static_cast<u8>(v >> 8); };
        std::memcpy(&b[0], "RIFF", 4);
        le32(4, 36 + size);
        std::memcpy(&b[8], "WAVEfmt ", 8);
        le32(16, 16);
        le16(20, 1);
        le16(22, ch);
        le32(24, rate);
        le32(28, rate * align);
        le16(32, align);
        le16(34, bits);
        std::memcpy(&b[36], "data", 4);
        le32(40, size);
        fill(*m, kHdr, b);
        zero(*m, kOut, 0x40);
        const s32 r = sv(prv(*m, 0x538F18, {kHdr, 44, kOut, kOut + 2}, tregs(kOut + 3, kOut + 4, kOut + 5, kOut + 8),
                             {kOut + 12, kOut + 16, kOut + 20}));
        INFO("bits " << bits << " channels " << ch);
        CHECK(r == 0);
        CHECK(r16(*m, kOut) == 44);         // data offset
        CHECK(r8(*m, kOut + 2) == 0xFF);
        CHECK(r8(*m, kOut + 5) == ch);
        CHECK(r32(*m, kOut + 8) == rate);
        if (bits == 4) {  // 4-bit: reported as 16-bit output, two bytes per channel and frame, kind 4, codec 2
            CHECK(r8(*m, kOut + 3) == 16);
            CHECK(r8(*m, kOut + 4) == 2 * ch);
            CHECK(r32(*m, kOut + 12) == size / 2 / ch);
            CHECK(r32(*m, kOut + 16) == 4);
            CHECK(r16(*m, kOut + 20) == 2);
        } else {
            CHECK(r8(*m, kOut + 3) == bits);
            CHECK(r8(*m, kOut + 4) == align);
            CHECK(r32(*m, kOut + 12) == frames);
            CHECK(r32(*m, kOut + 16) == 1);
            CHECK(r16(*m, kOut + 20) == (bits == 16 ? 0 : 1));
        }
        // the decoder-record set-up returns the data offset and keeps the parsed fields
        zero(*m, kScratch, 0x100);
        const u32 off = uv(prv(*m, 0x539148, {kScratch, kHdr, 44, 0}));
        CHECK(off == 44);
        CHECK(r16(*m, kScratch + 2) == 1);
        CHECK(r8(*m, kScratch + 14) == ch);
        CHECK(r32(*m, kScratch + 20) == rate);
        CHECK(r32(*m, kScratch + 80) == ch);
        CHECK(r16(*m, kScratch + 152) == 1);
    }
    // a compressed format tag (>= 2) or no "fmt " chunk: -1
    {
        std::vector<u8> b(44, 0);
        std::memcpy(&b[0], "RIFF\0\0\0\0WAVEfmt ", 16);
        b[20] = 2;
        std::memcpy(&b[36], "data", 4);
        fill(*m, kHdr, b);
        CHECK(sv(prv(*m, 0x538F18, {kHdr, 44, kOut, kOut + 2}, tregs(kOut + 3, kOut + 4, kOut + 5, kOut + 8),
                     {kOut + 12, kOut + 16, kOut + 20})) == -1);
        zero(*m, kHdr, 44);
        CHECK(sv(prv(*m, 0x538F18, {kHdr, 44, kOut, kOut + 2}, tregs(kOut + 3, kOut + 4, kOut + 5, kOut + 8),
                     {kOut + 12, kOut + 16, kOut + 20})) == -1);
    }
    // the ADXB lock counter: the first lock and the last unlock clear 0x784938
    w32(*m, 0x784940, 0);
    w32(*m, 0x784938, 0x55);
    pr(*m, 0x5397B8, {0, 0, 0, 0});
    CHECK(r32(*m, 0x784940) == 1);
    CHECK(r32(*m, 0x784938) == 0);
    w32(*m, 0x784938, 0x66);
    pr(*m, 0x5397B8, {0, 0, 0, 0});
    CHECK(r32(*m, 0x784940) == 2);
    CHECK(r32(*m, 0x784938) == 0x66);
    pr(*m, 0x5397E8, {0, 0, 0, 0});
    CHECK(r32(*m, 0x784938) == 0x66);
    pr(*m, 0x5397E8, {0, 0, 0, 0});
    CHECK(r32(*m, 0x784940) == 0);
    CHECK(r32(*m, 0x784938) == 0);
    // the empty lock stubs: nothing changes
    pr(*m, 0x539848, {1, 2, 3, 4});
    pr(*m, 0x539850, {1, 2, 3, 4});
    // the SJ library counter and the pools' init / finish counting (SJMEM / SJRBF / SJUNI)
    w32(*m, 0x7AC778, 0);
    w32(*m, 0x7AC770, 0x99);
    pr(*m, 0x561758, {0, 0, 0, 0});
    CHECK(r32(*m, 0x7AC778) == 1);
    CHECK(r32(*m, 0x7AC770) == 0);
    pr(*m, 0x5618A0, {0, 0, 0, 0});  // the first pool init clears the 32 SJMEM handles
    w32(*m, cri::sjmem::kPool + cri::sj::kUsed, 1);
    pr(*m, 0x5618A0, {0, 0, 0, 0});  // a second only counts
    CHECK(r32(*m, cri::sjmem::kPool + cri::sj::kUsed) == 1);
    pr(*m, 0x561920, {0, 0, 0, 0});
    CHECK(r32(*m, cri::sjmem::kPool + cri::sj::kUsed) == 1);
    pr(*m, 0x561920, {0, 0, 0, 0});  // the last finish clears them
    CHECK(r32(*m, cri::sjmem::kPool + cri::sj::kUsed) == 0);
    pr(*m, 0x5622B8, {0, 0, 0, 0});
    pr(*m, 0x562338, {0, 0, 0, 0});
    pr(*m, 0x562EC0, {0, 0, 0, 0});
    pr(*m, 0x562F40, {0, 0, 0, 0});
    // the default error callbacks: the type's text through SVM_CallErr1 into 0x7B2678
    w32(*m, cri::svm::kErrFn, 0);
    pr(*m, 0x561808, {0, 0, 0, 0});
    CHECK(cstr(*m, cri::svm::kErrText) == "SJMEM Error");
    pr(*m, 0x562220, {0, 0, 0, 0});
    CHECK(cstr(*m, cri::svm::kErrText) == "SJRBF Error");
    pr(*m, 0x562E28, {0, 0, 0, 0});
    CHECK(cstr(*m, cri::svm::kErrText) == "SJUNI Error");
    put_str(*m, kStr, "E1");
    put_str(*m, kStr + 16, " : x");
    pr(*m, 0x561828, {kStr, kStr + 16, 0, 0});
    CHECK(cstr(*m, cri::svm::kErrText) == "E1 : x");
    pr(*m, 0x562240, {kStr, kStr + 16, 0, 0});
    pr(*m, 0x562E48, {kStr, kStr + 16, 0, 0});
    pr(*m, 0x5617F0, {kStr, 0, 0, 0});
    CHECK(cstr(*m, cri::svm::kErrText) == "E1");
    // the stream-record accessors 0x562DE0 .. 0x562E10 (words +28 / +32 / +36, the 2-column table at +40)
    for (u32 i = 0; i < 16; ++i) w32(*m, kScratch + 4 * i, 0x1000 + i);
    CHECK(uv(prv(*m, 0x562DE0, {kScratch, 0, 0, 0})) == 0x1007);
    CHECK(uv(prv(*m, 0x562DE8, {kScratch, 0, 0, 0})) == 0x1008);
    CHECK(uv(prv(*m, 0x562DF0, {kScratch, 0, 0, 0})) == 0x1009);
    pr(*m, 0x562DF8, {kScratch, 1, 1, 0xABCD});
    CHECK(r32(*m, kScratch + 40 + 4 * 3) == 0xABCD);
    CHECK(uv(prv(*m, 0x562E10, {kScratch, 1, 1, 0})) == 0xABCD);
    CHECK(uv(prv(*m, 0x562E10, {kScratch, 0, 1, 0})) == 0x100B);
    // the bodies the wrappers above reach, paired directly: create / destroy of the three pools, the SVM lock pair,
    // the formatted SVM error (the real vsprintf), the decoder objects' error flag
    pr(*m, 0x5618A0, {0, 0, 0, 0});
    const u32 hm = uv(prv(*m, 0x5619B8, {kRing, 100, 0, 0}));
    CHECK(hm == cri::sjmem::kPool);
    CHECK(r32(*m, hm + cri::sjmem::kLeft) == 100);
    pr(*m, 0x561AB0, {hm, 0, 0, 0});
    CHECK(r32(*m, hm + cri::sj::kUsed) == 0);
    const u32 hr = uv(prv(*m, 0x5623E0, {kRing, 128, 8, 0}));
    pr(*m, 0x5624E0, {hr, 0, 0, 0});
    CHECK(r32(*m, hr + cri::sj::kUsed) == 0);
    const u32 hu = uv(prv(*m, 0x562FE8, {1, kNodes, 64, 0}));
    CHECK(r32(*m, hu + cri::sjuni::kNodes) == 4);
    pr(*m, 0x563100, {hu, 0, 0, 0});
    CHECK(r8(*m, hu + cri::sj::kUsed) == 0);
    w32(*m, cri::svm::kLockFn, 0);
    w32(*m, cri::svm::kUnlockFn, 0);
    pr(*m, 0x564888, {3, 0, 0, 0});  // no callbacks: no call, no count
    pr(*m, 0x5648E8, {3, 0, 0, 0});
    pr(*m, 0x5617C0, {0, 0, 0, 0});
    pr(*m, 0x5617D8, {0, 0, 0, 0});
    put_str(*m, kStr, "n=%d s=%s");
    put_str(*m, kStr + 32, "abc");
    pr(*m, 0x564AA8, {kStr, 42, kStr + 32, 0});
    CHECK(cstr(*m, cri::svm::kErrText) == "n=42 s=abc");
    w32(*m, cri::adxpd::kErrorFlag, 0);
    CHECK(prv(*m, 0x54CE80, {0, 0, 0, 0}) == 1);
    CHECK(r32(*m, cri::adxpd::kErrorFlag) == 1);
    // the cvFs error helpers: the message through the callback (none set: nothing happens)
    w32(*m, cri::cvfs::kErrFn, 0);
    pr(*m, 0x555918, {kStr, 0, 0, 0});
    pr(*m, 0x5558E8, {cri::cvfs::kErrFn + 4, kStr, 0, 0});
    MESSAGE("WAV / helpers: " << summary());
}

TEST_CASE("game(cri1): coverage of the meaningful sections") {
    std::string none;
    int covered = 0;
    for (const Case& c : kCases) {
        if (g_pairs.count(c.name)) {
            ++covered;
        } else {
            none += std::string(" ") + c.name;
        }
    }
    MESSAGE(covered << " of " << std::size(kCases) << " functions paired on meaningful inputs; generic sweep only:" << none);
}

#else

TEST_CASE("game(cri1): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
