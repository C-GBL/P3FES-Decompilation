// Pair tests of slice scene (game/src/scene/scene_*.cpp; the formats in game/include/p3fes/game/scene.h): every hand
// body against its recompiled body on identical guest machines, compared by tests/game/handgen_pairs.h (the whole
// register file and cycles at every check point and at the return / stop, all 32 MiB of RAM -- the dead stack and the
// stand-in heap included --, the scratchpad, the BIOS window, the bus log) and, through stand-in worlds
// (tests/game/stand_ins.h: the heap behind the RW slots, printf / sprintf, the H_Cdvd layer), the two call logs.
//   1. Random worlds: all 109 functions.
//   2. The resource manager on the ELF image: a manager, one record of every type (sizes from the jump table, the zeroed
//      body, scale 1.0, the list links), duplicates and unknown types refused with their prints, the lookups and counts,
//      the scene's list heads, every typed creator (ids, fields, the shown flag), MT_Scene_DeleteRes (prints, unlink,
//      free), the foreign-record delete, the no-manager prints, resrcMngDestroy (everything freed).
//   3. The live scenes of dorm_replay_4900 / b_5800 / climb_ref_17000: every type list's count and head, 48 resources
//      found by id with the flag setters and the move / rotation requests checked field by field, the transform /
//      motion / fade / controller requests on the model types, the hit value against the default table, type 7's
//      reset, the NPC-set / ENV setters.
//   4. Host models: the angle normalisation and turn (exact), the cubic Bezier and the path point with its local-t rule
//      (tolerance: ACC rounding), the signed segment count, comuDateInRange on six ranges (its two quirks), the links
//      6..11, the reference point.
//   5. comuTable.bin from extracted/DATA/EVENT/COMUPACK.PAK: the loader through the fake file layer, the block the game
//      loaded in two snapshots (byte for byte, every section pointer / size, the per-link copies, the derived pairs),
//      and the accessors on it (getters, link records and their lookup, section 112, the partner flags of every link and
//      rank against the flag array, the event requests of every link and kind, today's links, the dated call).
//   6. The comu timer-sequence steps on a made-up task (state transitions, next steps), the scene-manager tasks, the 25
//      icon files loaded and found in the cache, the icon slots of a character, nmListAllocNode, the fclBank panel
//      slide, the facility panel slide, the matrix helpers.
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function (random worlds), one function, a trace line per pair.
// Every random draw is a statement of its own (MSVC and clang-cl evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/scene.h"

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
using namespace p3fes::game;

namespace p3fes::recomp_gen {
void fn_sub_172A50_00172a50(EEContext&);  // generated body
void fn_sub_172A50_00172a50__recomp(EEContext&);  // recompiled
void fn_sub_3B4FC0_003b4fc0(EEContext&);  // generated body
void fn_sub_3B4FC0_003b4fc0__recomp(EEContext&);  // recompiled
void fn_sub_3B5020_003b5020(EEContext&);  // generated body
void fn_sub_3B5020_003b5020__recomp(EEContext&);  // recompiled
void fn_sub_3B50D0_003b50d0(EEContext&);  // generated body
void fn_sub_3B50D0_003b50d0__recomp(EEContext&);  // recompiled
void fn_sub_3B5360_003b5360(EEContext&);  // generated body
void fn_sub_3B5360_003b5360__recomp(EEContext&);  // recompiled
void fn_sub_3B5430_003b5430(EEContext&);  // generated body
void fn_sub_3B5430_003b5430__recomp(EEContext&);  // recompiled
void fn_sub_3B54C0_003b54c0(EEContext&);  // generated body
void fn_sub_3B54C0_003b54c0__recomp(EEContext&);  // recompiled
void fn_sub_3B5550_003b5550(EEContext&);  // generated body
void fn_sub_3B5550_003b5550__recomp(EEContext&);  // recompiled
void fn_sub_3B5620_003b5620(EEContext&);  // generated body
void fn_sub_3B5620_003b5620__recomp(EEContext&);  // recompiled
void fn_sub_3B58C0_003b58c0(EEContext&);  // generated body
void fn_sub_3B58C0_003b58c0__recomp(EEContext&);  // recompiled
void fn_sub_3B5980_003b5980(EEContext&);  // generated body
void fn_sub_3B5980_003b5980__recomp(EEContext&);  // recompiled
void fn_sub_3B5D50_003b5d50(EEContext&);  // generated body
void fn_sub_3B5D50_003b5d50__recomp(EEContext&);  // recompiled
void fn_sub_3B5E90_003b5e90(EEContext&);  // generated body
void fn_sub_3B5E90_003b5e90__recomp(EEContext&);  // recompiled
void fn_sub_3B5F70_003b5f70(EEContext&);  // generated body
void fn_sub_3B5F70_003b5f70__recomp(EEContext&);  // recompiled
void fn_sub_3B6180_003b6180(EEContext&);  // generated body
void fn_sub_3B6180_003b6180__recomp(EEContext&);  // recompiled
void fn_sub_3B63C0_003b63c0(EEContext&);  // generated body
void fn_sub_3B63C0_003b63c0__recomp(EEContext&);  // recompiled
void fn_sub_3B6440_003b6440(EEContext&);  // generated body
void fn_sub_3B6440_003b6440__recomp(EEContext&);  // recompiled
void fn_sub_3B66B0_003b66b0(EEContext&);  // generated body
void fn_sub_3B66B0_003b66b0__recomp(EEContext&);  // recompiled
void fn_sub_3B6790_003b6790(EEContext&);  // generated body
void fn_sub_3B6790_003b6790__recomp(EEContext&);  // recompiled
void fn_sub_3B6870_003b6870(EEContext&);  // generated body
void fn_sub_3B6870_003b6870__recomp(EEContext&);  // recompiled
void fn_sub_3B69A0_003b69a0(EEContext&);  // generated body
void fn_sub_3B69A0_003b69a0__recomp(EEContext&);  // recompiled
void fn_sub_3B6AD0_003b6ad0(EEContext&);  // generated body
void fn_sub_3B6AD0_003b6ad0__recomp(EEContext&);  // recompiled
void fn_sub_3B6B90_003b6b90(EEContext&);  // generated body
void fn_sub_3B6B90_003b6b90__recomp(EEContext&);  // recompiled
void fn_sub_3B6C50_003b6c50(EEContext&);  // generated body
void fn_sub_3B6C50_003b6c50__recomp(EEContext&);  // recompiled
void fn_sub_3B6D10_003b6d10(EEContext&);  // generated body
void fn_sub_3B6D10_003b6d10__recomp(EEContext&);  // recompiled
void fn_sub_3B6DD0_003b6dd0(EEContext&);  // generated body
void fn_sub_3B6DD0_003b6dd0__recomp(EEContext&);  // recompiled
void fn_sub_3B6E90_003b6e90(EEContext&);  // generated body
void fn_sub_3B6E90_003b6e90__recomp(EEContext&);  // recompiled
void fn_sub_3B6F50_003b6f50(EEContext&);  // generated body
void fn_sub_3B6F50_003b6f50__recomp(EEContext&);  // recompiled
void fn_sub_3B7090_003b7090(EEContext&);  // generated body
void fn_sub_3B7090_003b7090__recomp(EEContext&);  // recompiled
void fn_sub_3B7460_003b7460(EEContext&);  // generated body
void fn_sub_3B7460_003b7460__recomp(EEContext&);  // recompiled
void fn_sub_3B78B0_003b78b0(EEContext&);  // generated body
void fn_sub_3B78B0_003b78b0__recomp(EEContext&);  // recompiled
void fn_sub_3B7930_003b7930(EEContext&);  // generated body
void fn_sub_3B7930_003b7930__recomp(EEContext&);  // recompiled
void fn_sub_3B79A0_003b79a0(EEContext&);  // generated body
void fn_sub_3B79A0_003b79a0__recomp(EEContext&);  // recompiled
void fn_sub_3B7AC0_003b7ac0(EEContext&);  // generated body
void fn_sub_3B7AC0_003b7ac0__recomp(EEContext&);  // recompiled
void fn_sub_3B8210_003b8210(EEContext&);  // generated body
void fn_sub_3B8210_003b8210__recomp(EEContext&);  // recompiled
void fn_sub_3B8270_003b8270(EEContext&);  // generated body
void fn_sub_3B8270_003b8270__recomp(EEContext&);  // recompiled
void fn_sub_3B82C0_003b82c0(EEContext&);  // generated body
void fn_sub_3B82C0_003b82c0__recomp(EEContext&);  // recompiled
void fn_sub_3B83A0_003b83a0(EEContext&);  // generated body
void fn_sub_3B83A0_003b83a0__recomp(EEContext&);  // recompiled
void fn_sub_3B86C0_003b86c0(EEContext&);  // generated body
void fn_sub_3B86C0_003b86c0__recomp(EEContext&);  // recompiled
void fn_sub_3B8A60_003b8a60(EEContext&);  // generated body
void fn_sub_3B8A60_003b8a60__recomp(EEContext&);  // recompiled
void fn_sub_3B8CE0_003b8ce0(EEContext&);  // generated body
void fn_sub_3B8CE0_003b8ce0__recomp(EEContext&);  // recompiled
void fn_sub_3B8FF0_003b8ff0(EEContext&);  // generated body
void fn_sub_3B8FF0_003b8ff0__recomp(EEContext&);  // recompiled
void fn_sub_3B9260_003b9260(EEContext&);  // generated body
void fn_sub_3B9260_003b9260__recomp(EEContext&);  // recompiled
void fn_sub_3B9500_003b9500(EEContext&);  // generated body
void fn_sub_3B9500_003b9500__recomp(EEContext&);  // recompiled
void fn_sub_3BAA70_003baa70(EEContext&);  // generated body
void fn_sub_3BAA70_003baa70__recomp(EEContext&);  // recompiled
void fn_sub_3BAC40_003bac40(EEContext&);  // generated body
void fn_sub_3BAC40_003bac40__recomp(EEContext&);  // recompiled
void fn_sub_3BB0C0_003bb0c0(EEContext&);  // generated body
void fn_sub_3BB0C0_003bb0c0__recomp(EEContext&);  // recompiled
void fn_sub_3BB340_003bb340(EEContext&);  // generated body
void fn_sub_3BB340_003bb340__recomp(EEContext&);  // recompiled
void fn_sub_3BB450_003bb450(EEContext&);  // generated body
void fn_sub_3BB450_003bb450__recomp(EEContext&);  // recompiled
void fn_sub_3BB9B0_003bb9b0(EEContext&);  // generated body
void fn_sub_3BB9B0_003bb9b0__recomp(EEContext&);  // recompiled
void fn_sub_3BBA70_003bba70(EEContext&);  // generated body
void fn_sub_3BBA70_003bba70__recomp(EEContext&);  // recompiled
void fn_sub_3BBAA0_003bbaa0(EEContext&);  // generated body
void fn_sub_3BBAA0_003bbaa0__recomp(EEContext&);  // recompiled
void fn_sub_3BBC90_003bbc90(EEContext&);  // generated body
void fn_sub_3BBC90_003bbc90__recomp(EEContext&);  // recompiled
void fn_sub_3BBD40_003bbd40(EEContext&);  // generated body
void fn_sub_3BBD40_003bbd40__recomp(EEContext&);  // recompiled
void fn_sub_3BBFD0_003bbfd0(EEContext&);  // generated body
void fn_sub_3BBFD0_003bbfd0__recomp(EEContext&);  // recompiled
void fn_sub_3BC0E0_003bc0e0(EEContext&);  // generated body
void fn_sub_3BC0E0_003bc0e0__recomp(EEContext&);  // recompiled
void fn_sub_3BC730_003bc730(EEContext&);  // generated body
void fn_sub_3BC730_003bc730__recomp(EEContext&);  // recompiled
void fn_sub_3BC8F0_003bc8f0(EEContext&);  // generated body
void fn_sub_3BC8F0_003bc8f0__recomp(EEContext&);  // recompiled
void fn_sub_3BC900_003bc900(EEContext&);  // generated body
void fn_sub_3BC900_003bc900__recomp(EEContext&);  // recompiled
void fn_sub_3BD0B0_003bd0b0(EEContext&);  // generated body
void fn_sub_3BD0B0_003bd0b0__recomp(EEContext&);  // recompiled
void fn_sub_3BD130_003bd130(EEContext&);  // generated body
void fn_sub_3BD130_003bd130__recomp(EEContext&);  // recompiled
void fn_sub_3BD1C0_003bd1c0(EEContext&);  // generated body
void fn_sub_3BD1C0_003bd1c0__recomp(EEContext&);  // recompiled
void fn_sub_3BD280_003bd280(EEContext&);  // generated body
void fn_sub_3BD280_003bd280__recomp(EEContext&);  // recompiled
void fn_sub_3BD870_003bd870(EEContext&);  // generated body
void fn_sub_3BD870_003bd870__recomp(EEContext&);  // recompiled
void fn_sub_3BD890_003bd890(EEContext&);  // generated body
void fn_sub_3BD890_003bd890__recomp(EEContext&);  // recompiled
void fn_sub_3BD8A0_003bd8a0(EEContext&);  // generated body
void fn_sub_3BD8A0_003bd8a0__recomp(EEContext&);  // recompiled
void fn_sub_3BDA60_003bda60(EEContext&);  // generated body
void fn_sub_3BDA60_003bda60__recomp(EEContext&);  // recompiled
void fn_sub_3BDB80_003bdb80(EEContext&);  // generated body
void fn_sub_3BDB80_003bdb80__recomp(EEContext&);  // recompiled
void fn_sub_3BDBA0_003bdba0(EEContext&);  // generated body
void fn_sub_3BDBA0_003bdba0__recomp(EEContext&);  // recompiled
void fn_sub_3BDBB0_003bdbb0(EEContext&);  // generated body
void fn_sub_3BDBB0_003bdbb0__recomp(EEContext&);  // recompiled
void fn_sub_3BDBD0_003bdbd0(EEContext&);  // generated body
void fn_sub_3BDBD0_003bdbd0__recomp(EEContext&);  // recompiled
void fn_sub_3BDD40_003bdd40(EEContext&);  // generated body
void fn_sub_3BDD40_003bdd40__recomp(EEContext&);  // recompiled
void fn_sub_3BDD50_003bdd50(EEContext&);  // generated body
void fn_sub_3BDD50_003bdd50__recomp(EEContext&);  // recompiled
void fn_sub_3BDD60_003bdd60(EEContext&);  // generated body
void fn_sub_3BDD60_003bdd60__recomp(EEContext&);  // recompiled
void fn_sub_3BDD90_003bdd90(EEContext&);  // generated body
void fn_sub_3BDD90_003bdd90__recomp(EEContext&);  // recompiled
void fn_sub_3BDDD0_003bddd0(EEContext&);  // generated body
void fn_sub_3BDDD0_003bddd0__recomp(EEContext&);  // recompiled
void fn_sub_3BDDE0_003bdde0(EEContext&);  // generated body
void fn_sub_3BDDE0_003bdde0__recomp(EEContext&);  // recompiled
void fn_sub_3BDED0_003bded0(EEContext&);  // generated body
void fn_sub_3BDED0_003bded0__recomp(EEContext&);  // recompiled
void fn_sub_3BDFC0_003bdfc0(EEContext&);  // generated body
void fn_sub_3BDFC0_003bdfc0__recomp(EEContext&);  // recompiled
void fn_sub_3BE020_003be020(EEContext&);  // generated body
void fn_sub_3BE020_003be020__recomp(EEContext&);  // recompiled
void fn_sub_3BE1A0_003be1a0(EEContext&);  // generated body
void fn_sub_3BE1A0_003be1a0__recomp(EEContext&);  // recompiled
void fn_sub_3BE1C0_003be1c0(EEContext&);  // generated body
void fn_sub_3BE1C0_003be1c0__recomp(EEContext&);  // recompiled
void fn_sub_3BE2A0_003be2a0(EEContext&);  // generated body
void fn_sub_3BE2A0_003be2a0__recomp(EEContext&);  // recompiled
void fn_sub_3BEA20_003bea20(EEContext&);  // generated body
void fn_sub_3BEA20_003bea20__recomp(EEContext&);  // recompiled
void fn_sub_3BEAB0_003beab0(EEContext&);  // generated body
void fn_sub_3BEAB0_003beab0__recomp(EEContext&);  // recompiled
void fn_sub_3BEB10_003beb10(EEContext&);  // generated body
void fn_sub_3BEB10_003beb10__recomp(EEContext&);  // recompiled
void fn_sub_3BEB70_003beb70(EEContext&);  // generated body
void fn_sub_3BEB70_003beb70__recomp(EEContext&);  // recompiled
void fn_sub_3BEBD0_003bebd0(EEContext&);  // generated body
void fn_sub_3BEBD0_003bebd0__recomp(EEContext&);  // recompiled
void fn_sub_3BEC50_003bec50(EEContext&);  // generated body
void fn_sub_3BEC50_003bec50__recomp(EEContext&);  // recompiled
void fn_sub_3BECA0_003beca0(EEContext&);  // generated body
void fn_sub_3BECA0_003beca0__recomp(EEContext&);  // recompiled
void fn_sub_3BEE80_003bee80(EEContext&);  // generated body
void fn_sub_3BEE80_003bee80__recomp(EEContext&);  // recompiled
void fn_sub_3BF130_003bf130(EEContext&);  // generated body
void fn_sub_3BF130_003bf130__recomp(EEContext&);  // recompiled
void fn_sub_3BF180_003bf180(EEContext&);  // generated body
void fn_sub_3BF180_003bf180__recomp(EEContext&);  // recompiled
void fn_sub_3BF200_003bf200(EEContext&);  // generated body
void fn_sub_3BF200_003bf200__recomp(EEContext&);  // recompiled
void fn_sub_3BF270_003bf270(EEContext&);  // generated body
void fn_sub_3BF270_003bf270__recomp(EEContext&);  // recompiled
void fn_sub_3BF370_003bf370(EEContext&);  // generated body
void fn_sub_3BF370_003bf370__recomp(EEContext&);  // recompiled
void fn_sub_3BF510_003bf510(EEContext&);  // generated body
void fn_sub_3BF510_003bf510__recomp(EEContext&);  // recompiled
void fn_sub_3BF610_003bf610(EEContext&);  // generated body
void fn_sub_3BF610_003bf610__recomp(EEContext&);  // recompiled
void fn_sub_3BF720_003bf720(EEContext&);  // generated body
void fn_sub_3BF720_003bf720__recomp(EEContext&);  // recompiled
void fn_sub_3BF8E0_003bf8e0(EEContext&);  // generated body
void fn_sub_3BF8E0_003bf8e0__recomp(EEContext&);  // recompiled
void fn_sub_3BF950_003bf950(EEContext&);  // generated body
void fn_sub_3BF950_003bf950__recomp(EEContext&);  // recompiled
void fn_sub_3BFAE0_003bfae0(EEContext&);  // generated body
void fn_sub_3BFAE0_003bfae0__recomp(EEContext&);  // recompiled
void fn_sub_3BFC50_003bfc50(EEContext&);  // generated body
void fn_sub_3BFC50_003bfc50__recomp(EEContext&);  // recompiled
void fn_sub_3BFDB0_003bfdb0(EEContext&);  // generated body
void fn_sub_3BFDB0_003bfdb0__recomp(EEContext&);  // recompiled
void fn_sub_3BFF40_003bff40(EEContext&);  // generated body
void fn_sub_3BFF40_003bff40__recomp(EEContext&);  // recompiled
void fn_sub_3BFFA0_003bffa0(EEContext&);  // generated body
void fn_sub_3BFFA0_003bffa0__recomp(EEContext&);  // recompiled
void fn_sub_3C4650_003c4650(EEContext&);  // generated body
void fn_sub_3C4650_003c4650__recomp(EEContext&);  // recompiled
void fn_sub_3CA960_003ca960(EEContext&);  // generated body
void fn_sub_3CA960_003ca960__recomp(EEContext&);  // recompiled
void fn_sub_3CFB50_003cfb50(EEContext&);  // generated body
void fn_sub_3CFB50_003cfb50__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_172A50", 0x172A50, &recomp_gen::fn_sub_172A50_00172a50, &recomp_gen::fn_sub_172A50_00172a50__recomp},
    {"sub_3B4FC0", 0x3B4FC0, &recomp_gen::fn_sub_3B4FC0_003b4fc0, &recomp_gen::fn_sub_3B4FC0_003b4fc0__recomp},
    {"sub_3B5020", 0x3B5020, &recomp_gen::fn_sub_3B5020_003b5020, &recomp_gen::fn_sub_3B5020_003b5020__recomp},
    {"sub_3B50D0", 0x3B50D0, &recomp_gen::fn_sub_3B50D0_003b50d0, &recomp_gen::fn_sub_3B50D0_003b50d0__recomp},
    {"sub_3B5360", 0x3B5360, &recomp_gen::fn_sub_3B5360_003b5360, &recomp_gen::fn_sub_3B5360_003b5360__recomp},
    {"sub_3B5430", 0x3B5430, &recomp_gen::fn_sub_3B5430_003b5430, &recomp_gen::fn_sub_3B5430_003b5430__recomp},
    {"sub_3B54C0", 0x3B54C0, &recomp_gen::fn_sub_3B54C0_003b54c0, &recomp_gen::fn_sub_3B54C0_003b54c0__recomp},
    {"sub_3B5550", 0x3B5550, &recomp_gen::fn_sub_3B5550_003b5550, &recomp_gen::fn_sub_3B5550_003b5550__recomp},
    {"sub_3B5620", 0x3B5620, &recomp_gen::fn_sub_3B5620_003b5620, &recomp_gen::fn_sub_3B5620_003b5620__recomp},
    {"sub_3B58C0", 0x3B58C0, &recomp_gen::fn_sub_3B58C0_003b58c0, &recomp_gen::fn_sub_3B58C0_003b58c0__recomp},
    {"sub_3B5980", 0x3B5980, &recomp_gen::fn_sub_3B5980_003b5980, &recomp_gen::fn_sub_3B5980_003b5980__recomp},
    {"sub_3B5D50", 0x3B5D50, &recomp_gen::fn_sub_3B5D50_003b5d50, &recomp_gen::fn_sub_3B5D50_003b5d50__recomp},
    {"sub_3B5E90", 0x3B5E90, &recomp_gen::fn_sub_3B5E90_003b5e90, &recomp_gen::fn_sub_3B5E90_003b5e90__recomp},
    {"sub_3B5F70", 0x3B5F70, &recomp_gen::fn_sub_3B5F70_003b5f70, &recomp_gen::fn_sub_3B5F70_003b5f70__recomp},
    {"sub_3B6180", 0x3B6180, &recomp_gen::fn_sub_3B6180_003b6180, &recomp_gen::fn_sub_3B6180_003b6180__recomp},
    {"sub_3B63C0", 0x3B63C0, &recomp_gen::fn_sub_3B63C0_003b63c0, &recomp_gen::fn_sub_3B63C0_003b63c0__recomp},
    {"sub_3B6440", 0x3B6440, &recomp_gen::fn_sub_3B6440_003b6440, &recomp_gen::fn_sub_3B6440_003b6440__recomp},
    {"sub_3B66B0", 0x3B66B0, &recomp_gen::fn_sub_3B66B0_003b66b0, &recomp_gen::fn_sub_3B66B0_003b66b0__recomp},
    {"sub_3B6790", 0x3B6790, &recomp_gen::fn_sub_3B6790_003b6790, &recomp_gen::fn_sub_3B6790_003b6790__recomp},
    {"sub_3B6870", 0x3B6870, &recomp_gen::fn_sub_3B6870_003b6870, &recomp_gen::fn_sub_3B6870_003b6870__recomp},
    {"sub_3B69A0", 0x3B69A0, &recomp_gen::fn_sub_3B69A0_003b69a0, &recomp_gen::fn_sub_3B69A0_003b69a0__recomp},
    {"sub_3B6AD0", 0x3B6AD0, &recomp_gen::fn_sub_3B6AD0_003b6ad0, &recomp_gen::fn_sub_3B6AD0_003b6ad0__recomp},
    {"sub_3B6B90", 0x3B6B90, &recomp_gen::fn_sub_3B6B90_003b6b90, &recomp_gen::fn_sub_3B6B90_003b6b90__recomp},
    {"sub_3B6C50", 0x3B6C50, &recomp_gen::fn_sub_3B6C50_003b6c50, &recomp_gen::fn_sub_3B6C50_003b6c50__recomp},
    {"sub_3B6D10", 0x3B6D10, &recomp_gen::fn_sub_3B6D10_003b6d10, &recomp_gen::fn_sub_3B6D10_003b6d10__recomp},
    {"sub_3B6DD0", 0x3B6DD0, &recomp_gen::fn_sub_3B6DD0_003b6dd0, &recomp_gen::fn_sub_3B6DD0_003b6dd0__recomp},
    {"sub_3B6E90", 0x3B6E90, &recomp_gen::fn_sub_3B6E90_003b6e90, &recomp_gen::fn_sub_3B6E90_003b6e90__recomp},
    {"sub_3B6F50", 0x3B6F50, &recomp_gen::fn_sub_3B6F50_003b6f50, &recomp_gen::fn_sub_3B6F50_003b6f50__recomp},
    {"sub_3B7090", 0x3B7090, &recomp_gen::fn_sub_3B7090_003b7090, &recomp_gen::fn_sub_3B7090_003b7090__recomp},
    {"sub_3B7460", 0x3B7460, &recomp_gen::fn_sub_3B7460_003b7460, &recomp_gen::fn_sub_3B7460_003b7460__recomp},
    {"sub_3B78B0", 0x3B78B0, &recomp_gen::fn_sub_3B78B0_003b78b0, &recomp_gen::fn_sub_3B78B0_003b78b0__recomp},
    {"sub_3B7930", 0x3B7930, &recomp_gen::fn_sub_3B7930_003b7930, &recomp_gen::fn_sub_3B7930_003b7930__recomp},
    {"sub_3B79A0", 0x3B79A0, &recomp_gen::fn_sub_3B79A0_003b79a0, &recomp_gen::fn_sub_3B79A0_003b79a0__recomp},
    {"sub_3B7AC0", 0x3B7AC0, &recomp_gen::fn_sub_3B7AC0_003b7ac0, &recomp_gen::fn_sub_3B7AC0_003b7ac0__recomp},
    {"sub_3B8210", 0x3B8210, &recomp_gen::fn_sub_3B8210_003b8210, &recomp_gen::fn_sub_3B8210_003b8210__recomp},
    {"sub_3B8270", 0x3B8270, &recomp_gen::fn_sub_3B8270_003b8270, &recomp_gen::fn_sub_3B8270_003b8270__recomp},
    {"sub_3B82C0", 0x3B82C0, &recomp_gen::fn_sub_3B82C0_003b82c0, &recomp_gen::fn_sub_3B82C0_003b82c0__recomp},
    {"sub_3B83A0", 0x3B83A0, &recomp_gen::fn_sub_3B83A0_003b83a0, &recomp_gen::fn_sub_3B83A0_003b83a0__recomp},
    {"sub_3B86C0", 0x3B86C0, &recomp_gen::fn_sub_3B86C0_003b86c0, &recomp_gen::fn_sub_3B86C0_003b86c0__recomp},
    {"sub_3B8A60", 0x3B8A60, &recomp_gen::fn_sub_3B8A60_003b8a60, &recomp_gen::fn_sub_3B8A60_003b8a60__recomp},
    {"sub_3B8CE0", 0x3B8CE0, &recomp_gen::fn_sub_3B8CE0_003b8ce0, &recomp_gen::fn_sub_3B8CE0_003b8ce0__recomp},
    {"sub_3B8FF0", 0x3B8FF0, &recomp_gen::fn_sub_3B8FF0_003b8ff0, &recomp_gen::fn_sub_3B8FF0_003b8ff0__recomp},
    {"sub_3B9260", 0x3B9260, &recomp_gen::fn_sub_3B9260_003b9260, &recomp_gen::fn_sub_3B9260_003b9260__recomp},
    {"sub_3B9500", 0x3B9500, &recomp_gen::fn_sub_3B9500_003b9500, &recomp_gen::fn_sub_3B9500_003b9500__recomp},
    {"sub_3BAA70", 0x3BAA70, &recomp_gen::fn_sub_3BAA70_003baa70, &recomp_gen::fn_sub_3BAA70_003baa70__recomp},
    {"sub_3BAC40", 0x3BAC40, &recomp_gen::fn_sub_3BAC40_003bac40, &recomp_gen::fn_sub_3BAC40_003bac40__recomp},
    {"sub_3BB0C0", 0x3BB0C0, &recomp_gen::fn_sub_3BB0C0_003bb0c0, &recomp_gen::fn_sub_3BB0C0_003bb0c0__recomp},
    {"sub_3BB340", 0x3BB340, &recomp_gen::fn_sub_3BB340_003bb340, &recomp_gen::fn_sub_3BB340_003bb340__recomp},
    {"sub_3BB450", 0x3BB450, &recomp_gen::fn_sub_3BB450_003bb450, &recomp_gen::fn_sub_3BB450_003bb450__recomp},
    {"sub_3BB9B0", 0x3BB9B0, &recomp_gen::fn_sub_3BB9B0_003bb9b0, &recomp_gen::fn_sub_3BB9B0_003bb9b0__recomp},
    {"sub_3BBA70", 0x3BBA70, &recomp_gen::fn_sub_3BBA70_003bba70, &recomp_gen::fn_sub_3BBA70_003bba70__recomp},
    {"sub_3BBAA0", 0x3BBAA0, &recomp_gen::fn_sub_3BBAA0_003bbaa0, &recomp_gen::fn_sub_3BBAA0_003bbaa0__recomp},
    {"sub_3BBC90", 0x3BBC90, &recomp_gen::fn_sub_3BBC90_003bbc90, &recomp_gen::fn_sub_3BBC90_003bbc90__recomp},
    {"sub_3BBD40", 0x3BBD40, &recomp_gen::fn_sub_3BBD40_003bbd40, &recomp_gen::fn_sub_3BBD40_003bbd40__recomp},
    {"sub_3BBFD0", 0x3BBFD0, &recomp_gen::fn_sub_3BBFD0_003bbfd0, &recomp_gen::fn_sub_3BBFD0_003bbfd0__recomp},
    {"sub_3BC0E0", 0x3BC0E0, &recomp_gen::fn_sub_3BC0E0_003bc0e0, &recomp_gen::fn_sub_3BC0E0_003bc0e0__recomp},
    {"sub_3BC730", 0x3BC730, &recomp_gen::fn_sub_3BC730_003bc730, &recomp_gen::fn_sub_3BC730_003bc730__recomp},
    {"sub_3BC8F0", 0x3BC8F0, &recomp_gen::fn_sub_3BC8F0_003bc8f0, &recomp_gen::fn_sub_3BC8F0_003bc8f0__recomp},
    {"sub_3BC900", 0x3BC900, &recomp_gen::fn_sub_3BC900_003bc900, &recomp_gen::fn_sub_3BC900_003bc900__recomp},
    {"sub_3BD0B0", 0x3BD0B0, &recomp_gen::fn_sub_3BD0B0_003bd0b0, &recomp_gen::fn_sub_3BD0B0_003bd0b0__recomp},
    {"sub_3BD130", 0x3BD130, &recomp_gen::fn_sub_3BD130_003bd130, &recomp_gen::fn_sub_3BD130_003bd130__recomp},
    {"sub_3BD1C0", 0x3BD1C0, &recomp_gen::fn_sub_3BD1C0_003bd1c0, &recomp_gen::fn_sub_3BD1C0_003bd1c0__recomp},
    {"sub_3BD280", 0x3BD280, &recomp_gen::fn_sub_3BD280_003bd280, &recomp_gen::fn_sub_3BD280_003bd280__recomp},
    {"sub_3BD870", 0x3BD870, &recomp_gen::fn_sub_3BD870_003bd870, &recomp_gen::fn_sub_3BD870_003bd870__recomp},
    {"sub_3BD890", 0x3BD890, &recomp_gen::fn_sub_3BD890_003bd890, &recomp_gen::fn_sub_3BD890_003bd890__recomp},
    {"sub_3BD8A0", 0x3BD8A0, &recomp_gen::fn_sub_3BD8A0_003bd8a0, &recomp_gen::fn_sub_3BD8A0_003bd8a0__recomp},
    {"sub_3BDA60", 0x3BDA60, &recomp_gen::fn_sub_3BDA60_003bda60, &recomp_gen::fn_sub_3BDA60_003bda60__recomp},
    {"sub_3BDB80", 0x3BDB80, &recomp_gen::fn_sub_3BDB80_003bdb80, &recomp_gen::fn_sub_3BDB80_003bdb80__recomp},
    {"sub_3BDBA0", 0x3BDBA0, &recomp_gen::fn_sub_3BDBA0_003bdba0, &recomp_gen::fn_sub_3BDBA0_003bdba0__recomp},
    {"sub_3BDBB0", 0x3BDBB0, &recomp_gen::fn_sub_3BDBB0_003bdbb0, &recomp_gen::fn_sub_3BDBB0_003bdbb0__recomp},
    {"sub_3BDBD0", 0x3BDBD0, &recomp_gen::fn_sub_3BDBD0_003bdbd0, &recomp_gen::fn_sub_3BDBD0_003bdbd0__recomp},
    {"sub_3BDD40", 0x3BDD40, &recomp_gen::fn_sub_3BDD40_003bdd40, &recomp_gen::fn_sub_3BDD40_003bdd40__recomp},
    {"sub_3BDD50", 0x3BDD50, &recomp_gen::fn_sub_3BDD50_003bdd50, &recomp_gen::fn_sub_3BDD50_003bdd50__recomp},
    {"sub_3BDD60", 0x3BDD60, &recomp_gen::fn_sub_3BDD60_003bdd60, &recomp_gen::fn_sub_3BDD60_003bdd60__recomp},
    {"sub_3BDD90", 0x3BDD90, &recomp_gen::fn_sub_3BDD90_003bdd90, &recomp_gen::fn_sub_3BDD90_003bdd90__recomp},
    {"sub_3BDDD0", 0x3BDDD0, &recomp_gen::fn_sub_3BDDD0_003bddd0, &recomp_gen::fn_sub_3BDDD0_003bddd0__recomp},
    {"sub_3BDDE0", 0x3BDDE0, &recomp_gen::fn_sub_3BDDE0_003bdde0, &recomp_gen::fn_sub_3BDDE0_003bdde0__recomp},
    {"sub_3BDED0", 0x3BDED0, &recomp_gen::fn_sub_3BDED0_003bded0, &recomp_gen::fn_sub_3BDED0_003bded0__recomp},
    {"sub_3BDFC0", 0x3BDFC0, &recomp_gen::fn_sub_3BDFC0_003bdfc0, &recomp_gen::fn_sub_3BDFC0_003bdfc0__recomp},
    {"sub_3BE020", 0x3BE020, &recomp_gen::fn_sub_3BE020_003be020, &recomp_gen::fn_sub_3BE020_003be020__recomp},
    {"sub_3BE1A0", 0x3BE1A0, &recomp_gen::fn_sub_3BE1A0_003be1a0, &recomp_gen::fn_sub_3BE1A0_003be1a0__recomp},
    {"sub_3BE1C0", 0x3BE1C0, &recomp_gen::fn_sub_3BE1C0_003be1c0, &recomp_gen::fn_sub_3BE1C0_003be1c0__recomp},
    {"sub_3BE2A0", 0x3BE2A0, &recomp_gen::fn_sub_3BE2A0_003be2a0, &recomp_gen::fn_sub_3BE2A0_003be2a0__recomp},
    {"sub_3BEA20", 0x3BEA20, &recomp_gen::fn_sub_3BEA20_003bea20, &recomp_gen::fn_sub_3BEA20_003bea20__recomp},
    {"sub_3BEAB0", 0x3BEAB0, &recomp_gen::fn_sub_3BEAB0_003beab0, &recomp_gen::fn_sub_3BEAB0_003beab0__recomp},
    {"sub_3BEB10", 0x3BEB10, &recomp_gen::fn_sub_3BEB10_003beb10, &recomp_gen::fn_sub_3BEB10_003beb10__recomp},
    {"sub_3BEB70", 0x3BEB70, &recomp_gen::fn_sub_3BEB70_003beb70, &recomp_gen::fn_sub_3BEB70_003beb70__recomp},
    {"sub_3BEBD0", 0x3BEBD0, &recomp_gen::fn_sub_3BEBD0_003bebd0, &recomp_gen::fn_sub_3BEBD0_003bebd0__recomp},
    {"sub_3BEC50", 0x3BEC50, &recomp_gen::fn_sub_3BEC50_003bec50, &recomp_gen::fn_sub_3BEC50_003bec50__recomp},
    {"sub_3BECA0", 0x3BECA0, &recomp_gen::fn_sub_3BECA0_003beca0, &recomp_gen::fn_sub_3BECA0_003beca0__recomp},
    {"sub_3BEE80", 0x3BEE80, &recomp_gen::fn_sub_3BEE80_003bee80, &recomp_gen::fn_sub_3BEE80_003bee80__recomp},
    {"sub_3BF130", 0x3BF130, &recomp_gen::fn_sub_3BF130_003bf130, &recomp_gen::fn_sub_3BF130_003bf130__recomp},
    {"sub_3BF180", 0x3BF180, &recomp_gen::fn_sub_3BF180_003bf180, &recomp_gen::fn_sub_3BF180_003bf180__recomp},
    {"sub_3BF200", 0x3BF200, &recomp_gen::fn_sub_3BF200_003bf200, &recomp_gen::fn_sub_3BF200_003bf200__recomp},
    {"sub_3BF270", 0x3BF270, &recomp_gen::fn_sub_3BF270_003bf270, &recomp_gen::fn_sub_3BF270_003bf270__recomp},
    {"sub_3BF370", 0x3BF370, &recomp_gen::fn_sub_3BF370_003bf370, &recomp_gen::fn_sub_3BF370_003bf370__recomp},
    {"sub_3BF510", 0x3BF510, &recomp_gen::fn_sub_3BF510_003bf510, &recomp_gen::fn_sub_3BF510_003bf510__recomp},
    {"sub_3BF610", 0x3BF610, &recomp_gen::fn_sub_3BF610_003bf610, &recomp_gen::fn_sub_3BF610_003bf610__recomp},
    {"sub_3BF720", 0x3BF720, &recomp_gen::fn_sub_3BF720_003bf720, &recomp_gen::fn_sub_3BF720_003bf720__recomp},
    {"sub_3BF8E0", 0x3BF8E0, &recomp_gen::fn_sub_3BF8E0_003bf8e0, &recomp_gen::fn_sub_3BF8E0_003bf8e0__recomp},
    {"sub_3BF950", 0x3BF950, &recomp_gen::fn_sub_3BF950_003bf950, &recomp_gen::fn_sub_3BF950_003bf950__recomp},
    {"sub_3BFAE0", 0x3BFAE0, &recomp_gen::fn_sub_3BFAE0_003bfae0, &recomp_gen::fn_sub_3BFAE0_003bfae0__recomp},
    {"sub_3BFC50", 0x3BFC50, &recomp_gen::fn_sub_3BFC50_003bfc50, &recomp_gen::fn_sub_3BFC50_003bfc50__recomp},
    {"sub_3BFDB0", 0x3BFDB0, &recomp_gen::fn_sub_3BFDB0_003bfdb0, &recomp_gen::fn_sub_3BFDB0_003bfdb0__recomp},
    {"sub_3BFF40", 0x3BFF40, &recomp_gen::fn_sub_3BFF40_003bff40, &recomp_gen::fn_sub_3BFF40_003bff40__recomp},
    {"sub_3BFFA0", 0x3BFFA0, &recomp_gen::fn_sub_3BFFA0_003bffa0, &recomp_gen::fn_sub_3BFFA0_003bffa0__recomp},
    {"sub_3C4650", 0x3C4650, &recomp_gen::fn_sub_3C4650_003c4650, &recomp_gen::fn_sub_3C4650_003c4650__recomp},
    {"sub_3CA960", 0x3CA960, &recomp_gen::fn_sub_3CA960_003ca960, &recomp_gen::fn_sub_3CA960_003ca960__recomp},
    {"sub_3CFB50", 0x3CFB50, &recomp_gen::fn_sub_3CFB50_003cfb50, &recomp_gen::fn_sub_3CFB50_003cfb50__recomp},
};

constexpr u32 kWorld = 0x01810000u;  // the random worlds: 64 KiB of free RAM above the harness's arena
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;
constexpr u32 kOut = 0x01F40000u;     // free in every snapshot (above the stand-in heap) and in the ELF image
constexpr u32 kSceneSlot = 0x7CD540u; // gp-0x57B0: -> the scene record
constexpr u32 kSceneRec = 0x95AFC0u;  // the scene record (MT_Scene)
constexpr u32 kFlagWords = 0x83A21Cu; // datGetFlag / datSetFlag bit array
constexpr u32 kComu = 0x95B070u;      // the comuTable.bin block (sub_3BD280)
constexpr u32 kHitDefaults = 0x67EF00u;

// --- the pair runner (as test_facility2.cpp) ------------------------------------------------------------------------
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    bool persist = false;
    WorldSetup setup;
};
Tramp g_t;
int g_pairs = 0;
std::map<std::string, int> g_stops;

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    if (!g_t.persist || !g_t.world[K]) {
        g_t.world[K] = std::make_unique<StandInWorld>();
        install_standard(*g_t.world[K]);
        if (g_t.setup) g_t.setup(*g_t.world[K]);
    }
    g_t.world[K]->si.log.clear();
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// The world of this file: install_standard plus H_Cdvd_FileExists answered from the fake file layer (as
// test_field3_camera.cpp does).
void scene_world(StandInWorld& w) {
    StandInWorld* wp = &w;
    w.si.install(kHCdvdFileExistsFn, "H_Cdvd_FileExists", [wp](EEContext& ctx, StandIns&, StandInCall& c) {
        std::string path;
        for (u32 a = static_cast<u32>(c.args[0]); path.size() < 255; ++a) {
            const char ch = static_cast<char>(ctx.memory->read<u8>(a));
            if (ch == 0) break;
            path += ch;
        }
        c.text = path;
        c.v0 = wp->cd.host_path(path).empty() ? 0u : 1u;
    });
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12.. (float arguments, bits)
    bool standins = true;
    bool persist = false;
    WorldSetup setup = scene_world;
};

hgp::Run run_fns(Machine& m, Fn hand, Fn recomp, const char* name, const Args& a, u32 seed, const char* what, const Opt& o) {
    g_t.fn[0] = hand;
    g_t.fn[1] = recomp;
    g_t.standins = o.standins;
    g_t.fpr = o.fpr;
    if (!o.persist) {
        g_t.world[0].reset();
        g_t.world[1].reset();
    }
    g_t.persist = o.persist;
    g_t.setup = o.setup;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s (%s) seed %u\n", name, what, seed);
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    if (r.stopped) ++g_stops[std::string(name) + " @ " + hex64(r.stop_pc) + " (" + r.what.substr(0, 60) + ")"];
    ++g_pairs;
    return r;
}
// A pair of the slice function `name` (hand body vs its recompiled body).
hgp::Run spair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    return run_fns(m, c.hand, c.recomp, name, a, seed, what, o);
}
void fresh_worlds() {
    g_t.world[0].reset();
    g_t.world[1].reset();
}
Opt keep(std::map<unsigned, u32> fpr = {}, std::map<unsigned, u64> gpr = {}) {
    Opt o;
    o.persist = true;
    o.fpr = std::move(fpr);
    o.gpr_in = std::move(gpr);
    return o;
}
u32 v0u(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
s32 v0s(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }
float f0(const hgp::Run& r) {
    float f;
    std::memcpy(&f, &r.end.fpr[0], 4);
    return f;
}
u32 fb(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
// The stand-in log of the last pair's recompiled run: the printf texts.
std::vector<std::string> printed() {
    std::vector<std::string> out;
    if (!g_t.world[1]) return out;
    for (const StandInCall& c : g_t.world[1]->si.log)
        if (c.va == kPrintf) out.push_back(c.text);
    return out;
}
bool printed_has(const std::string& s) {
    for (const std::string& t : printed())
        if (t.find(s) != std::string::npos) return true;
    return false;
}

// --- guest memory helpers -------------------------------------------------------------------------------------------
u32 ram_off(u32 va, u32 n) {
    const u32 a = va & 0x01FFFFFFu;
    return a + n <= EEMemory::kMainRamSize ? a : 0;
}
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 2), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[ram_off(va, 1)]; }
float rf(const Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
bool flag(const Machine& m, u32 id) { return (r32(m, kFlagWords + 4 * (id / 32)) >> (id % 32)) & 1u; }

const std::vector<u8>& snapshot(const char* dir) {
    static std::map<std::string, std::vector<u8>> cache;
    auto it = cache.find(dir);
    if (it == cache.end()) it = cache.emplace(dir, read_snapshot(dir)).first;
    return it->second;
}
bool restore(Machine& m, const char* dir) {
    const std::vector<u8>& s = snapshot(dir);
    if (s.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), s.data(), s.size());
    return true;
}
std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

// The record size of a resource type (resrcMngAddRes's jump table 0x7BB250; 0 = no record).
constexpr u32 kResSize[22] = {0, 496, 464, 544, 432, 432, 264, 272, 256, 0, 304, 264, 368, 336, 272, 272, 272, 272, 272, 272, 288, 336};
u32 round16(u32 n) { return (n + 15u) & ~15u; }

// Host walk of one type list of a manager.
std::vector<u32> res_list(const Machine& m, u32 mgr, u32 type) {
    std::vector<u32> out;
    if (!mgr || type >= 22) return out;
    for (u32 r = r32(m, mgr + 4 * type); r != 0 && out.size() < 1024; r = r32(m, r + scn::res::kNext)) out.push_back(r);
    return out;
}

// The host model of comuDateInRange (sub_3BF270), written from the documented rule with its two quirks.
bool date_in_range(int month, int day, int m0, int d0, int m1, int d1) {
    const bool wraps = m1 < m0 || (m0 == m1 && d1 < d0);
    if (wraps) {
        if (month < m0) return m1 > month || (m1 == month && d1 >= day);
        return m0 != month || day >= d0;
    }
    if (month >= m0 && m1 >= month) {
        if (m0 == month) return day >= d0;  // quirk: no end-day test when the range starts in this month
        return m1 != month || d1 >= day;
    }
    return false;
}

// comuTable.bin from the pak (the first member of DATA/EVENT/COMUPACK.PAK: 252-byte name, u32 size, data).
std::vector<u8> comu_table_file() {
    std::FILE* f = std::fopen((extracted_root() + "/DATA/EVENT/COMUPACK.PAK").c_str(), "rb");
    if (!f) return {};
    std::vector<u8> pak;
    u8 buf[65536];
    for (std::size_t n; (n = std::fread(buf, 1, sizeof buf, f)) > 0;) pak.insert(pak.end(), buf, buf + n);
    std::fclose(f);
    if (pak.size() < 256 || std::string(reinterpret_cast<const char*>(pak.data())) != "comuTable.bin") return {};
    u32 size;
    std::memcpy(&size, pak.data() + 252, 4);
    if (256u + size > pak.size()) return {};
    return std::vector<u8>(pak.begin() + 256, pak.begin() + 256 + size);
}
u32 le32(const std::vector<u8>& b, u32 off) {
    u32 v = 0;
    if (off + 4 <= b.size()) std::memcpy(&v, b.data() + off, 4);
    return v;
}
// The derived {pointer, count} pairs of sub_3BD280: {global, section, record size (0: pointer only), count shift}.
struct Derived {
    u32 va;
    u32 sec;
    u32 rec;
};
const Derived kDerived[] = {
    {0x95B658, 96, 24}, {0x95B660, 106, 4}, {0x95B668, 107, 6}, {0x95B670, 112, 10}, {0x95B678, 99, 3},
    {0x95B680, 100, 3}, {0x95B688, 101, 5}, {0x95B690, 102, 5}, {0x95B698, 104, 5}, {0x95B6A0, 105, 3},
    {0x95B6A8, 114, 24}, {0x95B6B0, 115, 2}, {0x95B6B8, 116, 16}, {0x95B6C0, 139, 3}, {0x95B6C8, 117, 2},
    {0x95B6F8, 119, 0}, {0x95B6FC, 127, 0}, {0x95B700, 126, 0}, {0x95B704, 120, 0}, {0x95B708, 121, 0},
    {0x95B70C, 122, 0}, {0x95B710, 123, 26}, {0x95B6D8, 128, 5}, {0x95B6D0, 125, 12}, {0x95B718, 124, 0},
    {0x95B6E0, 129, 0}, {0x95B6E4, 131, 12}, {0x95B6EC, 132, 0}, {0x95B6F4, 133, 0}, {0x95B6F0, 134, 0},
    {0x95B71C, 135, 6}, {0x95B724, 136, 8},
};
// Checks the loaded table block against the file: the 144 section pointers / sizes, the three per-link copies, the
// derived pairs (the documented format of the header comment). Returns the number of checks.
int check_comu_block(const Machine& m, const std::vector<u8>& file) {
    const u32 base = r32(m, kComu);
    REQUIRE(base != 0);
    CHECK(le32(file, 0) == (r32(m, base) & 0xFFFFFFu));  // u16 version 1, u8 last section
    int n = 0;
    auto ptr = [&](u32 sec) { const u32 off = le32(file, 4 + 8 * sec); return off ? base + off : 0u; };
    auto size = [&](u32 sec) { return le32(file, 8 + 8 * sec); };
    for (u32 i = 0; i < 144; ++i) {
        CHECK(r32(m, 0x95B078u + 4 * i) == ptr(i));
        CHECK(r32(m, 0x95B2B4u + 4 * i) == size(i));
        n += 2;
    }
    for (u32 j = 0; j < 30; ++j) {
        CHECK(r32(m, 0x95B4F0u + 4 * j) == ptr(j));
        CHECK(r32(m, 0x95B568u + 4 * j) == ptr(32 + j));
        CHECK(r32(m, 0x95B5E0u + 4 * j) == ptr(64 + j));
        n += 3;
    }
    for (const Derived& d : kDerived) {
        INFO("derived " << hex64(d.va) << " section " << d.sec);
        CHECK(r32(m, d.va) == ptr(d.sec));
        ++n;
        if (d.rec) {
            CHECK(r32(m, d.va + 4) == size(d.sec) / d.rec);
            ++n;
        }
    }
    return n;
}
}  // namespace

// =====================================================================================================================
// 1. Every body on random worlds (with the stand-ins: the heap behind the RW slots, printf, the H_Cdvd layer)
// =====================================================================================================================
TEST_CASE("game(scene): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const int before = g_pairs;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const u64 a0 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWorld, kWorldSize);
            run_fns(*m, c.hand, c.recomp, c.name, {a0, a1, a2, a3}, seed, c.name, {});
        }
    }
    MESSAGE("random worlds: " << (g_pairs - before) << " pairs");
}

// =====================================================================================================================
// 2. The resource manager and the typed creators on the ELF image (documented rules)
// =====================================================================================================================
TEST_CASE("game(scene): the resource manager and the typed creators (documented rules)") {
    auto m = elf_machine();
    if (!m) return;
    fresh_worlds();
    w32(*m, kSceneSlot, kSceneRec);
    zero(*m, kSceneRec, 64);
    u32 seed = 100;
    const Opt k = keep();
    auto live = [&] { return g_t.world[1] ? g_t.world[1]->heap.live().size() : 0u; };

    // resrcMngCreate: an 88-byte zeroed block
    const hgp::Run cr = spair(*m, "sub_3B4FC0", {}, ++seed, "resrcMngCreate", k);
    const u32 mgr = v0u(cr);
    REQUIRE(mgr != 0);
    CHECK(g_t.world[1]->heap.size_of(mgr) == round16(88));
    for (u32 i = 0; i < 88; i += 4) CHECK(r32(*m, mgr + i) == 0);
    const std::size_t base_live = live();

    // resrcMngAddRes for every type (and two past the end)
    std::map<u32, u32> recs;  // id -> record
    for (u32 type = 0; type < 24; ++type) {
        const u32 id = (type << 10) | 5u;
        INFO("type " << type);
        const hgp::Run r = spair(*m, "sub_3B50D0", {sx(mgr), id, 0, 0}, ++seed, "resrcMngAddRes", k);
        REQUIRE(!r.stopped);
        const u32 rec = v0u(r);
        if (type >= 22) {
            CHECK(rec == 0);
            CHECK(printed_has("warning!! not known resrc!! resrcManager.c"));
            continue;
        }
        if (kResSize[type] == 0) {
            CHECK(rec == 0);
            CHECK(printed().empty());
            continue;
        }
        REQUIRE(rec != 0);
        recs[id] = rec;
        CHECK(g_t.world[1]->heap.size_of(rec) == round16(kResSize[type]));
        CHECK(r16(*m, rec + scn::res::kId) == id);
        CHECK(rf(*m, rec + scn::res::kScale) == 1.0f);
        CHECK(rf(*m, rec + scn::res::kScaleY) == 1.0f);
        CHECK(rf(*m, rec + scn::res::kScaleZ) == 1.0f);
        for (u32 off = 4; off < kResSize[type]; off += 4)
            if (off < 28 || off >= 40) CHECK(r32(*m, rec + off) == 0);  // zeroed; the head has no links
        CHECK(r32(*m, mgr + 4 * type) == rec);
    }
    CHECK(recs.size() == 20);  // types 1..21 but 9
    // a second record of type 13 is appended at the tail
    const u32 id13 = (13u << 10) | 5u, id13b = (13u << 10) | 6u;
    const hgp::Run r2 = spair(*m, "sub_3B50D0", {sx(mgr), id13b, 0, 0}, ++seed, "append", k);
    const u32 rec13b = v0u(r2);
    REQUIRE(rec13b != 0);
    CHECK(r32(*m, recs[id13] + scn::res::kNext) == rec13b);
    CHECK(r32(*m, rec13b + scn::res::kPrev) == recs[id13]);
    CHECK(r32(*m, rec13b + scn::res::kNext) == 0);
    // a duplicate id: refused, the block given back
    const std::size_t before_dup = live();
    const hgp::Run dup = spair(*m, "sub_3B50D0", {sx(mgr), id13b, 0, 0}, ++seed, "duplicate", k);
    CHECK(v0u(dup) == 0);
    CHECK(printed_has("warning!! duplicate resID!! not regist!resrcManager.c"));
    CHECK(live() == before_dup);

    // lookups and counts
    for (const auto& [id, rec] : recs) {
        CHECK(v0u(spair(*m, "sub_3B54C0", {sx(mgr), id, 0, 0}, ++seed, "find", k)) == rec);
        CHECK(v0u(spair(*m, "sub_3B54C0", {sx(mgr), id + 100u, 0, 0}, ++seed, "find absent", k)) == 0);
    }
    CHECK(v0u(spair(*m, "sub_3B54C0", {sx(mgr), 5, 0, 0}, ++seed, "find type 0", k)) == 0);
    for (u32 type = 0; type < 24; ++type) {
        const u32 head = type < 22 ? r32(*m, mgr + 4 * type) : 0u;
        CHECK(v0u(spair(*m, "sub_3B5430", {sx(mgr), type, 0, 0}, ++seed, "head", k)) == head);
        CHECK(v0u(spair(*m, "sub_3B5550", {sx(mgr), type, 0, 0}, ++seed, "count", k)) == res_list(*m, mgr, type).size());
    }
    // the scene's manager: MT_Scene_GetResListHead and the creators
    for (u32 type = 0; type < 22; ++type)
        CHECK(v0u(spair(*m, "sub_3B5D50", {type, 0, 0, 0}, ++seed, "scene head (none)", k)) == 0);
    w32(*m, kSceneRec + scn::scene::kResMgr, mgr);
    for (u32 type = 0; type < 22; ++type)
        CHECK(v0u(spair(*m, "sub_3B5D50", {type, 0, 0, 0}, ++seed, "scene head", k)) == r32(*m, mgr + 4 * type));

    const u32 n = 7;
    auto find = [&](u32 id) { return v0u(spair(*m, "sub_3B54C0", {sx(mgr), id, 0, 0}, ++seed, "find", k)); };
    CHECK(v0u(spair(*m, "sub_3B5E90", {n, 0, 0, 0}, ++seed, "pos", k)) == 0x2007u);
    CHECK(v0u(spair(*m, "sub_3B5F70", {n, 0, 0, 0}, ++seed, "type 7", k)) == 0x1C07u);
    CHECK(rf(*m, find(0x1C07u) + scn::snd::kRadius) == 35.0f);
    CHECK(v0u(spair(*m, "sub_3B6180", {n, 0, 0, 0}, ++seed, "model NULL", k)) == 0);
    CHECK(v0u(spair(*m, "sub_3B63C0", {n, 0, 0, 0}, ++seed, "light char", k)) == 0x1007u);
    CHECK(v0u(spair(*m, "sub_3B6440", {n, 0, 0, 0}, ++seed, "light npc", k)) == 0x1407u);
    CHECK(v0u(spair(*m, "sub_3B66B0", {n, 0, 0, 0}, ++seed, "field EPL NULL", k)) == 0);
    CHECK(v0u(spair(*m, "sub_3B66B0", {n, 0x01234560u, 0, 0}, ++seed, "field EPL", k)) == 0x2C07u);
    CHECK(r32(*m, find(0x2C07u) + scn::eff::kEpl) == 0x01234560u);
    CHECK((r32(*m, find(0x2C07u) + scn::res::kFlags) & 8u) != 0);
    CHECK(v0u(spair(*m, "sub_3B6790", {0x45, 0x01234570u, 0, 0}, ++seed, "block", k)) == 0x3045u);
    CHECK(r32(*m, find(0x3045u) + scn::blk::kBlockData) == 0x01234570u);
    // a field hit: the colour word, the centre, width / depth / turn (the quad needs the RW matrix allocator, which the
    // ELF image has not set up: the run stops there, identically; the snapshot case below checks the quad)
    const float quad[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for (int i = 0; i < 12; ++i) wf(*m, kOut + 4 * i, quad[i]);
    for (const char* fn : {"sub_3B6870", "sub_3B69A0"}) {
        const bool t21 = std::string(fn) == "sub_3B69A0";
        spair(*m, fn, {n, kOut, 0x44332211u, 0}, ++seed, "hit", keep({{12, fb(1.5f)}, {13, fb(2.5f)}, {14, fb(3.5f)}}));
        const u32 id = (t21 ? 0x5400u : 0x3400u) | n;
        const u32 rec = find(id);
        REQUIRE(rec != 0);
        CHECK(r32(*m, rec + scn::hit::kRgba) == 0x44332211u);
        CHECK(rf(*m, rec + scn::hit::kPos) == 1.0f);
        CHECK(rf(*m, rec + scn::hit::kPosZ) == 3.0f);
        CHECK(rf(*m, rec + scn::hit::kWidth) == 1.5f);
        CHECK(rf(*m, rec + scn::hit::kDepth) == 2.5f);
        CHECK(rf(*m, rec + scn::hit::kTurn) == 3.5f);
    }
    // the six marker types 14..19
    const char* markers[6] = {"sub_3B6AD0", "sub_3B6B90", "sub_3B6C50", "sub_3B6D10", "sub_3B6DD0", "sub_3B6E90"};
    for (u32 t = 0; t < 6; ++t) {
        const u32 id = ((14u + t) << 10) | n;
        CHECK(v0u(spair(*m, markers[t], {n, kOut + 12, 0, 0}, ++seed, "marker", keep({{12, fb(90.0f)}}))) == id);
        const u32 rec = find(id);
        REQUIRE(rec != 0);
        CHECK(rf(*m, rec + scn::pos::kPoint) == 4.0f);
        CHECK(rf(*m, rec + scn::pos::kPointZ) == 6.0f);
        CHECK(rf(*m, rec + scn::pos::kAngle) == 90.0f);
        CHECK((r32(*m, rec + scn::res::kFlags) & 8u) != 0);
    }
    // a camera (its matrix through RwMatrixCreate)
    for (int i = 0; i < 16; ++i) wf(*m, kOut + 0x100 + 4 * i, static_cast<float>(i));
    spair(*m, "sub_3B6F50", {n, 3, kOut + 0x100, kOut}, ++seed, "camera", keep({{12, fb(0.5f)}, {14, fb(9.0f)}}));

    // MT_Scene_DeleteRes: the prints and the unlink / free
    const std::size_t before_del = live();
    spair(*m, "sub_3B7090", {0x2007u, 0, 0, 0}, ++seed, "delete pos", k);
    CHECK(find(0x2007u) == 0);
    spair(*m, "sub_3B7090", {0x3407u, 0, 0, 0}, ++seed, "delete hit", k);
    CHECK(printed_has("delete field hit res"));
    CHECK(find(0x3407u) == 0);
    spair(*m, "sub_3B7090", {0x3807u, 0, 0, 0}, ++seed, "delete marker", k);
    CHECK(printed_has("delete field pos res"));
    w32(*m, find(0x2C07u) + scn::eff::kEpl, 0);  // no EPL to destroy
    spair(*m, "sub_3B7090", {0x2C07u, 0, 0, 0}, ++seed, "delete field EPL", k);
    CHECK(find(0x2C07u) == 0);
    CHECK(live() == before_del - 4);
    spair(*m, "sub_3B7090", {0x2007u, 0, 0, 0}, ++seed, "delete absent", k);
    CHECK(printed().empty());
    // resrcMngDeleteRes of a record that is not on its list: nothing
    zero(*m, kOut + 0x300, 256);
    w16(*m, kOut + 0x300, 0x2009u);
    const std::size_t before_foreign = live();
    spair(*m, "sub_3B5360", {sx(mgr), kOut + 0x300, 0, 0}, ++seed, "delete foreign", k);
    CHECK(live() == before_foreign);
    // no manager: the creators print and return 0
    w32(*m, kSceneRec + scn::scene::kResMgr, 0);
    CHECK(v0u(spair(*m, "sub_3B63C0", {n, 0, 0, 0}, ++seed, "no manager", k)) == 0);
    CHECK(printed_has("not found active resmanager"));
    spair(*m, "sub_3B7090", {0x1007u, 0, 0, 0}, ++seed, "delete without manager", k);
    CHECK(printed_has("not found active resmanager"));
    // resrcMngDestroy: every record and the manager freed
    std::vector<u32> left;
    for (u32 t = 0; t < 22; ++t)
        for (u32 r : res_list(*m, mgr, t)) left.push_back(r);
    REQUIRE(!left.empty());
    spair(*m, "sub_3B5020", {sx(mgr), 0, 0, 0}, ++seed, "resrcMngDestroy", k);
    for (u32 r : left) CHECK(g_t.world[1]->heap.size_of(r) == 0);
    CHECK(g_t.world[1]->heap.size_of(mgr) == 0);
    CHECK(live() < base_live + left.size());
    spair(*m, "sub_3B5020", {0, 0, 0, 0}, ++seed, "resrcMngDestroy NULL", k);
}

// =====================================================================================================================
// 3. The live scenes of the replay snapshots
// =====================================================================================================================
TEST_CASE("game(scene): the live scene resources of the snapshots") {
    auto m = elf_machine();
    if (!m) return;
    int scenes = 0, checks = 0;
    for (const char* dir : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        if (!restore(*m, dir)) {
            MESSAGE("note: extracted/_ours/" << dir << " not found");
            continue;
        }
        const u32 scene = r32(*m, kSceneSlot);
        const u32 mgr = scene ? r32(*m, scene + scn::scene::kResMgr) : 0u;
        if (!mgr) {
            MESSAGE(dir << ": no scene manager");
            continue;
        }
        ++scenes;
        u32 seed = 1000;
        fresh_worlds();
        std::vector<u32> all;
        std::string summary;
        for (u32 t = 0; t < 22; ++t) {
            const std::vector<u32> l = res_list(*m, mgr, t);
            if (!l.empty()) summary += " " + std::to_string(t) + ":" + std::to_string(l.size());
            CHECK(v0u(spair(*m, "sub_3B5550", {sx(mgr), t, 0, 0}, ++seed, "count")) == l.size());
            CHECK(v0u(spair(*m, "sub_3B5D50", {t, 0, 0, 0}, ++seed, "scene head")) == (l.empty() ? 0u : l[0]));
            checks += 2;
            all.insert(all.end(), l.begin(), l.end());
        }
        MESSAGE(std::string(dir) << ": scene " << r32(*m, scene) << "/" << r32(*m, scene + 4) << ", resources by type" << summary);
        // a new field hit of each kind on the live scene (RwMatrixCreate works here): the quad is the width x depth
        // rectangle turned about y and moved to the centre -- its corners average to the centre, opposite corners are
        // sqrt(w^2 + d^2) apart
        for (const char* fn : {"sub_3B6870", "sub_3B69A0"}) {
            const bool t21 = std::string(fn) == "sub_3B69A0";
            const u32 id = (t21 ? 0x5400u : 0x3400u) | 0x3FEu;
            const float c[3] = {100.0f, 5.0f, -40.0f};
            for (int i = 0; i < 3; ++i) wf(*m, kOut + 4 * i, c[i]);
            const hgp::Run h = spair(*m, fn, {0x3FE, kOut, 0x80FF00FFu, 0}, ++seed, "hit (live)", keep({{12, fb(60.0f)}, {13, fb(80.0f)}, {14, fb(30.0f)}}));
            if (h.stopped) continue;
            CHECK(v0u(h) == id);
            const u32 rec = v0u(spair(*m, "sub_3B54C0", {sx(mgr), id, 0, 0}, ++seed, "find hit"));
            REQUIRE(rec != 0);
            float avg[3] = {0, 0, 0};
            for (int v = 0; v < 4; ++v)
                for (int j = 0; j < 3; ++j) avg[j] += rf(*m, rec + scn::hit::kQuad + 12 * v + 4 * j) / 4.0f;
            for (int j = 0; j < 3; ++j) CHECK(std::fabs(avg[j] - c[j]) < 0.01f);
            const float dx = rf(*m, rec + scn::hit::kQuad3) - rf(*m, rec + scn::hit::kQuad);
            const float dz = rf(*m, rec + scn::hit::kQuad3 + 8) - rf(*m, rec + scn::hit::kQuad + 8);
            CHECK(std::fabs(std::sqrt(dx * dx + dz * dz) - 100.0f) < 0.01f);
            CHECK((r32(*m, rec + scn::res::kFlags) & 8u) != 0);
            checks += 6;
        }
        // every resource: found by id, the flag setters, the move / rotation requests
        std::mt19937 rng{7};
        u32 done = 0;
        for (u32 rec : all) {
            if (done++ >= 48) break;
            const u32 id = r16(*m, rec);
            INFO(dir << " resource " << hex64(id));
            CHECK(v0u(spair(*m, "sub_3B54C0", {sx(mgr), id, 0, 0}, ++seed, "find")) == rec);
            const u32 fl = r32(*m, rec + scn::res::kFlags);
            CHECK(v0u(spair(*m, "sub_3B83A0", {sx(rec), 0, 0, 0}, ++seed, "is shown")) == ((fl >> 3) & 1u));
            spair(*m, "sub_3B82C0", {sx(rec), 1, 0, 0}, ++seed, "show");
            CHECK((r32(*m, rec + scn::res::kFlags) & 8u) != 0);
            spair(*m, "sub_3B82C0", {sx(rec), 0, 0, 0}, ++seed, "hide");
            CHECK((r32(*m, rec + scn::res::kFlags) & 8u) == 0);
            spair(*m, "sub_3B9500", {sx(rec), 1, 0, 0}, ++seed, "visible");
            CHECK((r32(*m, rec + scn::res::kFlags) & 2u) != 0);
            spair(*m, "sub_3B9500", {sx(rec), 2, 0, 0}, ++seed, "invisible");
            CHECK((r32(*m, rec + scn::res::kFlags) & 2u) == 0);
            w32(*m, rec + scn::res::kFlags, fl);
            // a move request
            const float to[3] = {static_cast<float>(rng() % 2000) - 1000.0f, 0.0f, static_cast<float>(rng() % 2000) - 1000.0f};
            for (int i = 0; i < 3; ++i) wf(*m, kOut + 4 * i, to[i]);
            const float px = rf(*m, rec + scn::res::kPos);
            CHECK(v0u(spair(*m, "sub_3B86C0", {sx(rec), kOut, 0, 0}, ++seed, "move", keep({{12, fb(8.0f)}}))) == 1);
            CHECK((r32(*m, rec + scn::res::kFlags) & 0x41u) == 1u);
            CHECK(rf(*m, rec + scn::res::kMoveFrom) == px);
            CHECK(rf(*m, rec + scn::res::kMoveTo) == to[0]);
            CHECK(rf(*m, rec + scn::res::kMoveToZ) == to[2]);
            CHECK(rf(*m, rec + scn::res::kMoveSpeed) == 8.0f);
            // a rotation request: both ends normalised to [0, 360)
            const float rot[3] = {-90.0f, 450.0f, 720.0f};
            for (int i = 0; i < 3; ++i) wf(*m, kOut + 16 + 4 * i, rot[i]);
            CHECK(v0u(spair(*m, "sub_3B8A60", {sx(rec), kOut + 16, 30, 2}, ++seed, "rotate")) == 1);
            CHECK(rf(*m, rec + scn::res::kRotTo) == 270.0f);
            CHECK(rf(*m, rec + scn::res::kRotToY) == 90.0f);
            CHECK(rf(*m, rec + scn::res::kRotToZ) == 0.0f);
            CHECK(r8(*m, rec + scn::res::kRotMode) == 2);
            CHECK(r32(*m, rec + scn::res::kRotFrames) == 30);
            for (int i = 0; i < 3; ++i) {
                const float a = rf(*m, rec + scn::res::kRotFrom + 4 * i);
                CHECK((a >= 0.0f && a < 360.0f));
            }
            w32(*m, rec + scn::res::kFlags, fl);
            checks += 18;
        }
        // the transform setters and the motion / fade / icon requests on the first resources of the model types
        for (u32 t : {1u, 2u, 3u, 6u, 10u}) {
            const std::vector<u32> l = res_list(*m, mgr, t);
            for (std::size_t i = 0; i < l.size() && i < 3; ++i) {
                const u32 rec = l[i], id = r16(*m, rec);
                for (int j = 0; j < 3; ++j) wf(*m, kOut + 4 * j, rf(*m, rec + scn::res::kPos + 4 * j));
                for (int j = 0; j < 3; ++j) wf(*m, kOut + 16 + 4 * j, rf(*m, rec + scn::res::kRot + 4 * j));
                spair(*m, "sub_3B78B0", {id, kOut, kOut + 16, 0}, ++seed, "set pos/rot");
                spair(*m, "sub_3B7930", {id, kOut + 0x40, 0, 0}, ++seed, "set scale");
                spair(*m, "sub_3B9260", {sx(rec), 1, 2, 3}, ++seed, "queue motion", keep({{12, fb(0.5f)}}, {{8, 4}, {9, 5}}));
                spair(*m, "sub_3B8CE0", {sx(rec), 128, 10, 1}, ++seed, "fade");
                spair(*m, "sub_3BB0C0", {sx(rec), 1, 0, 0}, ++seed, "ctl mode");
                spair(*m, "sub_3B79A0", {kOut + 0x80, kOut, kOut + 16, 0}, ++seed, "rot matrix");
            }
        }
        // the hit value far above every hit: the default of the table
        {
            const u32 major = r32(*m, scene), minor0 = r32(*m, scene + 4);
            const u32 minor = (major >= 20 && major < 29 && minor0 >= 50) ? minor0 - 49 : minor0;
            const u32 row = r32(*m, kHitDefaults + 4 * major);
            const u32 expect = row ? r8(*m, row + minor) : 0u;
            for (const float y : {1.0e6f, -1.0e6f}) {
                wf(*m, kOut, 10.0f);
                wf(*m, kOut + 4, y);
                wf(*m, kOut + 8, 20.0f);
                CHECK(v0u(spair(*m, "sub_3BAA70", {kOut, 0, 0, 0}, ++seed, "hit value")) == expect);
                ++checks;
            }
            // and at the first vertex of each type-21 hit
            for (u32 h : res_list(*m, mgr, 21)) {
                for (int j = 0; j < 3; ++j) wf(*m, kOut + 4 * j, rf(*m, h + scn::hit::kQuad + 4 * j));
                spair(*m, "sub_3BAA70", {kOut, 0, 0, 0}, ++seed, "hit value at a hit");
            }
        }
        spair(*m, "sub_3BB340", {}, ++seed, "reset type 7");
        for (u32 r : res_list(*m, mgr, 7)) CHECK(r32(*m, r + scn::snd::kState) == 0);
        // the NPC set / ENV sub-id setters on the live scene
        spair(*m, "sub_3B58C0", {sx(static_cast<u32>(static_cast<s16>(r16(*m, scene + scn::scene::kNpcSet)))), 0, 0, 0}, ++seed, "same NPC set");
        spair(*m, "sub_3B58C0", {77, 0, 0, 0}, ++seed, "new NPC set");
        CHECK(r16(*m, scene + scn::scene::kNpcSet) == 77);
        spair(*m, "sub_3B5980", {55, 0, 0, 0}, ++seed, "new ENV sub-id");
        CHECK(r16(*m, scene + scn::scene::kEnvSub) == 55);
        checks += 2;
    }
    MESSAGE("snapshot scenes: " << scenes << ", " << checks << " rule checks");
}

// =====================================================================================================================
// 4. Angles, bezier paths, dates (documented rules against host models)
// =====================================================================================================================
TEST_CASE("game(scene): angles, bezier paths and date ranges (documented rules)") {
    auto m = elf_machine();
    if (!m) return;
    u32 seed = 5000;
    std::mt19937 rng{11};
    // MT_SceneFunc_NormAngles: repeated -360 / +360 in single precision
    auto norm = [](float a) {
        while (a >= 360.0f) a -= 360.0f;
        while (a < 0.0f) a += 360.0f;
        return a;
    };
    const float samples[] = {-725.5f, -360.0f, -0.25f, 0.0f, 359.75f, 360.0f, 361.5f, 1080.25f, 7200.0f, 45.0f};
    for (int i = 0; i < 40; ++i) {
        float a[3];
        for (float& v : a) {
            const u32 pick = rng() % 12;
            v = pick < 10 ? samples[pick] : static_cast<float>(static_cast<int>(rng() % 4000) - 2000) / 3.0f;
        }
        for (int j = 0; j < 3; ++j) wf(*m, kOut + 4 * j, a[j]);
        spair(*m, "sub_3BB9B0", {kOut, 0, 0, 0}, ++seed, "norm angles", {{}, {}, false});
        for (int j = 0; j < 3; ++j) CHECK(std::fabs(rf(*m, kOut + 4 * j) - norm(a[j])) <= 1e-3f);  // the EE FPU rounds toward zero
        // the turn from a to b
        float b[3];
        for (float& v : b) v = static_cast<float>(static_cast<int>(rng() % 1440) - 720);
        for (int j = 0; j < 3; ++j) {
            wf(*m, kOut + 4 * j, a[j]);
            wf(*m, kOut + 16 + 4 * j, b[j]);
        }
        spair(*m, "sub_3BBAA0", {kOut, kOut + 16, kOut + 32, 0}, ++seed, "angle delta", {{}, {}, false});
        for (int j = 0; j < 3; ++j) {
            float d = norm(b[j] - a[j]);
            if (d > 180.0f) d = -(360.0f - d);
            CHECK(std::fabs(rf(*m, kOut + 32 + 4 * j) - d) <= 1e-3f);
        }
    }
    // MT_SceneFunc_Bezier against the cubic Bernstein form (the ACC fused sums may round differently: tolerance)
    auto bez = [](const float* c, float t) {
        const float u = 1.0f - t;
        return u * u * u * c[0] + 3.0f * t * u * u * c[1] + 3.0f * t * t * u * c[2] + t * t * t * c[3];
    };
    for (int i = 0; i < 40; ++i) {
        float c[12];
        for (float& v : c) v = static_cast<float>(static_cast<int>(rng() % 2001) - 1000) * 0.5f;
        for (int j = 0; j < 12; ++j) wf(*m, kOut + 4 * j, c[j]);
        const float t = static_cast<float>(rng() % 1001) / 1000.0f;
        spair(*m, "sub_3BBC90", {kOut, kOut + 16, kOut + 32, kOut + 48}, ++seed, "bezier",
              {{{8, kOut + 52}, {9, kOut + 56}}, {{12, fb(t)}}, false});
        for (int j = 0; j < 3; ++j) CHECK(std::fabs(rf(*m, kOut + 48 + 4 * j) - bez(c + 4 * j, t)) <= 0.05f);
    }
    // MT_SceneFunc_PathPoint on paths of one and three segments (the documented local-t rule)
    for (u32 count : {1u, 3u}) {
        const u32 path = kOut + 0x200;
        zero(*m, path, 4 + 12 * (3 * count + 1));
        w8(*m, path, static_cast<u8>(count));
        std::vector<float> pts(3 * (3 * count + 1));
        for (float& v : pts) v = static_cast<float>(static_cast<int>(rng() % 801) - 400);
        for (std::size_t j = 0; j < pts.size(); ++j) wf(*m, path + 4 + 4 * static_cast<u32>(j), pts[j]);
        for (const float t : {0.0f, 0.1f, 0.25f, 0.5f, 0.75f, 0.99f, 1.0f, 1.25f}) {
            spair(*m, "sub_3BBD40", {path, kOut + 0x100, 0, 0}, ++seed, "path point", {{}, {{12, fb(t)}}, false});
            u32 seg;
            float lt = t;
            if (t < 1.0f) {
                const float step = 1.0f / static_cast<float>(count);
                seg = static_cast<u32>(static_cast<int>(t / step));
                while (lt > step) lt -= step;
                lt /= step;
            } else {
                seg = count - 1;
                lt = 1.0f;
            }
            for (int axis = 0; axis < 3; ++axis) {
                float c[4];
                for (int p = 0; p < 4; ++p) c[p] = pts[3 * (3 * seg + p) + axis];
                INFO("count " << count << " t " << t << " axis " << axis);
                CHECK(std::fabs(rf(*m, kOut + 0x100 + 4 * axis) - bez(c, lt)) <= 0.05f);
            }
        }
        CHECK(v0s(spair(*m, "sub_3BC8F0", {path, 0, 0, 0}, ++seed, "last segment", {{}, {}, false})) == static_cast<s32>(count) - 1);
        spair(*m, "sub_3BC0E0", {path, 0, 0, 0}, ++seed, "path length", {{}, {}, false});
        spair(*m, "sub_3BC730", {path, 2, 0, 0}, ++seed, "path length to", {{}, {}, false});
    }
    w8(*m, kOut + 0x200, 0x80);  // lb: a signed count
    CHECK(v0s(spair(*m, "sub_3BC8F0", {kOut + 0x200, 0, 0, 0}, ++seed, "last segment (signed)", {{}, {}, false})) == -129);
    // comuDateInRange: every day of the year against six ranges (normal, one month, wrapping, wrapping in one month)
    const int ranges[][4] = {{4, 1, 6, 30}, {5, 10, 5, 20}, {11, 15, 2, 10}, {5, 20, 5, 10}, {1, 1, 12, 31}, {7, 7, 7, 7}};
    int days = 0;
    for (const auto& r : ranges) {
        for (int month = 1; month <= 12; ++month) {
            for (int day = 1; day <= 31; day += (month * day) % 3 + 1) {
                const hgp::Run x = spair(*m, "sub_3BF270", {static_cast<u64>(month), static_cast<u64>(day), static_cast<u64>(r[0]), static_cast<u64>(r[1])},
                                         ++seed, "date range", {{{8, static_cast<u64>(r[2])}, {9, static_cast<u64>(r[3])}}, {}, false});
                INFO(month << "/" << day << " in " << r[0] << "/" << r[1] << ".." << r[2] << "/" << r[3]);
                CHECK(v0u(x) == (date_in_range(month, day, r[0], r[1], r[2], r[3]) ? 1u : 0u));
                ++days;
            }
        }
    }
    // the quirks, explicitly
    CHECK(date_in_range(5, 25, 5, 10, 5, 20));   // accepted past the end day
    CHECK(!date_in_range(5, 5, 5, 20, 5, 10));   // rejected though before the end day of a wrapping range
    // sub_172A50: the links 6..11
    for (int id = -3; id < 40; ++id)
        CHECK(v0u(spair(*m, "sub_172A50", {sx(static_cast<u32>(id)), 0, 0, 0}, ++seed, "link 6..11", {{}, {}, false})) == ((id >= 6 && id <= 11) ? 1u : 0u));
    // sub_3BC900: the reference point
    w16(*m, 0x7CE658u, 0);
    CHECK(v0u(spair(*m, "sub_3BC900", {kOut, 0, 0, 0}, ++seed, "ref point unset", {{}, {}, false})) == 0);
    w16(*m, 0x7CE658u, 1);
    wf(*m, 0x95AFF0u, 12.5f);
    wf(*m, 0x95AFF4u, -3.0f);
    CHECK(v0u(spair(*m, "sub_3BC900", {kOut, 0, 0, 0}, ++seed, "ref point", {{}, {}, false})) == 1);
    CHECK(rf(*m, kOut) == 12.5f);
    CHECK(rf(*m, kOut + 4) == -3.0f);
    MESSAGE("date checks: " << days);
}

// =====================================================================================================================
// 5. comuTable.bin: the loader on the file, the loaded block of the snapshots, the accessors
// =====================================================================================================================
TEST_CASE("game(scene): comuTable.bin and its accessors") {
    const std::vector<u8> file = comu_table_file();
    if (file.empty()) {
        MESSAGE("SKIP: extracted/DATA/EVENT/COMUPACK.PAK not found");
        return;
    }
    CHECK(le32(file, 0) == 0x008F0001u);  // version 1, last section 143
    auto m = elf_machine();
    if (!m) return;
    u32 seed = 9000;
    int checks = 0;
    // the loader itself, with the fake file layer serving comuPack.pak
    fresh_worlds();
    const hgp::Run ld = spair(*m, "sub_3BD280", {}, ++seed, "comuLoadTableBin");
    if (!ld.stopped && r32(*m, kComu) != 0) {
        checks += check_comu_block(*m, file);
        CHECK(printed_has("comuTableBinFile Load version=1 tableno=143"));
    } else {
        MESSAGE("note: the loader found no comuTable.bin in the fake file layer (stopped " << ld.stopped << ")");
    }
    // the block the game loaded, in the snapshots, and the accessors on it
    for (const char* dir : {"dorm_replay_4900", "b_5800"}) {
        if (!restore(*m, dir)) continue;
        fresh_worlds();
        const u32 base = r32(*m, kComu);
        REQUIRE(base != 0);
        for (u32 i = 0; i < file.size(); i += 4) {
            if (r32(*m, base + i) != le32(file, i)) {
                FAIL_CHECK("the loaded comuTable.bin differs at +" << i);
                break;
            }
        }
        checks += check_comu_block(*m, file);
        // the loader again on the live machine: the pak's members are still in the H_Cdvd cache, so the block is
        // rebuilt from them -- cleared first, it must come out as the game left it
        {
            std::vector<u8> saved(0x95B730u - kComu);
            std::memcpy(saved.data(), m->at(kComu), saved.size());
            zero(*m, kComu, static_cast<u32>(saved.size()));
            const hgp::Run again = spair(*m, "sub_3BD280", {}, ++seed, "comuLoadTableBin (live)");
            if (!again.stopped && r32(*m, kComu) != 0) {
                CHECK(r32(*m, kComu) == base);
                checks += check_comu_block(*m, file);
                CHECK(printed_has("comuTableBinFile Load version=1 tableno=143"));
                CHECK(std::memcmp(saved.data(), m->at(kComu), saved.size()) == 0);
            } else {
                MESSAGE("note: the live loader stopped (" << again.what.substr(0, 80) << ")");
                std::memcpy(m->at(kComu), saved.data(), saved.size());
            }
        }
        CHECK(v0u(spair(*m, "sub_3BD870", {}, ++seed, "tables")) == kComu);
        CHECK(v0u(spair(*m, "sub_3BD890", {}, ++seed, "dated conds")) == 0x95B660u);
        CHECK(v0u(spair(*m, "sub_3BD8A0", {}, ++seed, "dated flags")) == 0x95B668u);
        CHECK(v0u(spair(*m, "sub_3BDD40", {}, ++seed, "call tables")) == 0x95B678u);
        CHECK(v0u(spair(*m, "sub_3BDD50", {}, ++seed, "rank events")) == 0x95B6A8u);
        CHECK(v0u(spair(*m, "sub_3BDDD0", {}, ++seed, "section 130")) == r32(*m, 0x95B280u));
        CHECK(v0u(spair(*m, "sub_3BDBA0", {}, ++seed, "section 134")) == r32(*m, 0x95B6F0u));
        CHECK(v0u(spair(*m, "sub_3BDBB0", {}, ++seed, "section 137")) == r16(*m, r32(*m, 0x95B29Cu)));
        CHECK(f0(spair(*m, "sub_3BDB80", {}, ++seed, "section 133")) == rf(*m, r32(*m, 0x95B6F4u)));
        checks += 9;
        for (u32 link = 0; link < 33; ++link) {
            CHECK(v0u(spair(*m, "sub_3BDD90", {link, 0, 0, 0}, ++seed, "per-link table")) == (link < 31 ? r32(*m, kComu + 4 * (link + 348)) : 0u));
            ++checks;
        }
        // the 64 link records and their lookup
        const u32 links = r32(*m, 0x95B718u);
        for (u32 i = 0; i < 64; ++i) {
            CHECK(v0u(spair(*m, "sub_3BEB10", {i, 0, 0, 0}, ++seed, "link record")) == links + 32 * i);
            const u32 a = r8(*m, links + 32 * i), b = r8(*m, links + 32 * i + 1);
            u32 first = 64;
            for (u32 j = 0; j < 64 && first == 64; ++j)
                if (r8(*m, links + 32 * j) == a && r8(*m, links + 32 * j + 1) == b) first = j;
            w32(*m, kOut, 0xFFFFFFFFu);
            CHECK(v0u(spair(*m, "sub_3BEAB0", {a, b, kOut, 0}, ++seed, "find link")) == 1);
            CHECK(r32(*m, kOut) == first);
            checks += 3;
        }
        w32(*m, kOut, 0xFFFFFFFFu);
        CHECK(v0u(spair(*m, "sub_3BEAB0", {0xFF, 0xFE, kOut, 0}, ++seed, "find link (none)")) == 0);
        // section 112: every row whose key's first match has no flag answers its value
        const u32 rows = r32(*m, 0x95B670u), nrows = r32(*m, 0x95B674u);
        for (u32 i = 0; i < nrows && i < 200; ++i) {
            const u32 row = rows + 10 * i;
            const u32 a = r8(*m, row), b = r8(*m, row + 1), c = r16(*m, row + 2), d = r8(*m, row + 4);
            u32 first = i;
            for (u32 j = 0; j < i; ++j) {
                const u32 o = rows + 10 * j;
                if (r8(*m, o) == a && r8(*m, o + 1) == b && r16(*m, o + 2) == c && r8(*m, o + 4) == d) {
                    first = j;
                    break;
                }
            }
            const hgp::Run r = spair(*m, "sub_3BDA60", {a, b, c, d}, ++seed, "section 112");
            if (r16(*m, rows + 10 * first + 8) == 0) {
                CHECK(v0u(r) == r16(*m, rows + 10 * first + 6));
                ++checks;
            }
        }
        CHECK(v0s(spair(*m, "sub_3BDA60", {0xFE, 0xFE, 0xFFFE, 0xFE}, ++seed, "section 112 (none)")) == -1);
        // the link state rules for the 30 links
        for (u32 link = 0; link < 30; ++link) {
            const u32 st = v0u(spair(*m, "sub_3BDED0", {link, 0, 0, 0}, ++seed, "link state"));
            CHECK(st <= 5);
            for (u32 rank = 0; rank < 11; ++rank) {
                const hgp::Run r = spair(*m, "sub_3BE1C0", {link, rank, 0, 0}, ++seed, "partner flag");
                bool expect = false;
                const u32 t123 = r32(*m, 0x95B710u), n123 = r32(*m, 0x95B714u);
                if (rank >= 2)
                    for (u32 j = 0; j < n123 && !expect; ++j) {
                        const u32 fid = r16(*m, t123 + 26 * j + 4 + 2 * rank);
                        if (r8(*m, t123 + 26 * j) == link && fid != 0 && !flag(*m, fid)) expect = true;
                    }
                CHECK(v0u(r) == (expect ? 1u : 0u));
                checks += 1;
            }
            spair(*m, "sub_3BDFC0", {link, 0, 0, 0}, ++seed, "section 126");
            spair(*m, "sub_3BEBD0", {link, 0, 0, 0}, ++seed, "met today?");
            spair(*m, "sub_3BEE80", {link, kOut, 0, 0}, ++seed, "persona candidates");
            spair(*m, "sub_3BDBD0", {link, 0, 0, 0}, ++seed, "partner ranks");
            for (u32 kind = 0; kind < 8; ++kind) {
                zero(*m, kOut + 0x100, 64);
                w32(*m, kOut + 0x80, 0);
                const hgp::Run r = spair(*m, "sub_3BE2A0", {0, kOut + 0x80, link, kind}, ++seed, "event request", keep({}, {{8, kOut + 0x100}}));
                if (v0u(r) == 1) {
                    CHECK(r8(*m, kOut + 0x100 + scn::creq::kLink) == link);
                    CHECK(r8(*m, kOut + 0x100 + scn::creq::kKind) == kind);
                    CHECK(r32(*m, kOut + 0x100 + scn::creq::kResult) <= 3);
                    checks += 3;
                }
                spair(*m, "sub_3BE1A0", {kOut + 0x100, 0, 0, 0}, ++seed, "request result 3");
            }
            spair(*m, "sub_3BE020", {0, kOut + 0x100, link, 0}, ++seed, "partner event");
        }
        // today's links and the dated call
        const hgp::Run dl = spair(*m, "sub_3BECA0", {kOut + 0x200, 0, 0, 0}, ++seed, "today's links");
        const u32 nl = v0u(dl);
        CHECK(nl <= r32(*m, 0x95B6DCu));
        for (u32 i = 0; i < nl; ++i) CHECK(r32(*m, kOut + 0x200 + 4 * i) < 30);
        const hgp::Run call = spair(*m, "sub_3BFFA0", {kOut, kOut + 4, kOut + 8, 0}, ++seed, "dated call");
        if (v0u(call) == 1) CHECK((r32(*m, kOut) == 802 || r32(*m, kOut) == 803));
        spair(*m, "sub_3BDDE0", {}, ++seed, "refresh links");
        spair(*m, "sub_3BEA20", {1, 2, 0, 0}, ++seed, "byte table");
        spair(*m, "sub_3BF200", {4, 29, 255, 3}, ++seed, "date match (weekday)");
        CHECK(v0u(spair(*m, "sub_3BF200", {4, 29, 4, 29}, ++seed, "date match")) == 1);
        CHECK(v0u(spair(*m, "sub_3BF200", {4, 29, 4, 28}, ++seed, "date mismatch")) == 0);
        spair(*m, "sub_3BEC50", {}, ++seed, "clear met flags");
        for (u32 link = 0; link < 30; ++link) CHECK(!flag(*m, 2512 + link));
        spair(*m, "sub_3BEB70", {4, 0, 0, 0}, ++seed, "set met flag");
        CHECK(flag(*m, 2516));
        CHECK(v0u(spair(*m, "sub_3BEBD0", {4, 0, 0, 0}, ++seed, "met today")) == 1);
        spair(*m, "sub_3BF130", {}, ++seed, "no change pending");
        checks += 34;
    }
    MESSAGE("comu checks: " << checks);
}

// =====================================================================================================================
// 6. The comu timer sequence steps on a made-up task, the scene-manager tasks, the icon files, the leftovers
// =====================================================================================================================
TEST_CASE("game(scene): timer-sequence steps, the manager tasks, the icon files and the leftovers") {
    auto m = elf_machine();
    if (!m) return;
    u32 seed = 20000;
    const bool snap = restore(*m, "dorm_replay_4900");
    if (!snap) MESSAGE("note: dorm_replay_4900 not found; the ELF image instead");
    const u32 task = kOut + 0x400, work = kOut + 0x500;
    auto set_work = [&](u32 state, u32 timer, u32 wait) {
        zero(*m, task, 0x68);
        w32(*m, task + scn::task::kWork, work);
        zero(*m, work, 24);
        w32(*m, work + scn::seq::kState, state);
        w32(*m, work + scn::seq::kTimer, timer);
        w32(*m, work + scn::seq::kWait, wait);
    };
    // the first step: refresh, clear, next sub_3BFDB0
    set_work(5, 6, 7);
    CHECK(v0u(spair(*m, "sub_3BFF40", {task, 0, 0, 0}, ++seed, "first step")) == 0x3BFDB0u);
    for (u32 i = 0; i < 24; i += 4) CHECK(r32(*m, work + i) == 0);
    // "comuTimerProcess": 0 -> {1, 0, 2}; 1 -> requests sequence 2, state 2
    set_work(0, 9, 9);
    CHECK(v0u(spair(*m, "sub_3BF610", {task, 0, 0, 0}, ++seed, "timer 0")) == 0);
    CHECK(r32(*m, work) == 1);
    CHECK(r32(*m, work + 4) == 0);
    CHECK(r32(*m, work + 8) == 2);
    spair(*m, "sub_3BF610", {task, 0, 0, 0}, ++seed, "timer 1");
    CHECK(r32(*m, work) == 2);
    spair(*m, "sub_3BF610", {task, 0, 0, 0}, ++seed, "timer 2");
    // the wait-then-request steps: two frames of waiting, then state 2
    for (const char* fn : {"sub_3BFAE0", "sub_3BF950", "sub_3BF720"}) {
        set_work(0, 0, 0);
        spair(*m, fn, {task, 0, 0, 0}, ++seed, "arm");
        CHECK(r32(*m, work) == 1);
        CHECK(r32(*m, work + 8) == 2);
        for (u32 f = 0; f < 3; ++f) spair(*m, fn, {task, 0, 0, 0}, ++seed, "wait");
        CHECK(r32(*m, work) == 2);
        spair(*m, fn, {task, 0, 0, 0}, ++seed, "change");
        set_work(3, 0, 0);
        const hgp::Run end = spair(*m, fn, {task, 0, 0, 0}, ++seed, "state 3");
        if (std::string(fn) == "sub_3BF950") CHECK(v0u(end) == 0x3BF8E0u);
        if (std::string(fn) == "sub_3BFAE0") CHECK(v0s(end) == -1);
    }
    for (u32 st = 0; st < 5; ++st) {
        set_work(st, 0, 0);
        spair(*m, "sub_3BF370", {task, 0, 0, 0}, ++seed, "step 861");
        set_work(st, 0, 0);
        spair(*m, "sub_3BF510", {task, 0, 0, 0}, ++seed, "step 584");
        set_work(st, 0, 0);
        spair(*m, "sub_3BFC50", {task, 0, 0, 0}, ++seed, "step 810");
    }
    set_work(0, 0, 0);
    spair(*m, "sub_3BF8E0", {task, 0, 0, 0}, ++seed, "prepare request");
    set_work(0, 0, 0);
    spair(*m, "sub_3BFDB0", {task, 0, 0, 0}, ++seed, "pick link");
    spair(*m, "sub_3BF180", {800, 1, 2, 0}, ++seed, "sequence 3");
    spair(*m, "sub_3BDD60", {0, 1, 0, 0}, ++seed, "script start");

    // the icon-destroy task callbacks on a made-up work
    w32(*m, task + scn::task::kWork, work);
    w32(*m, work + scn::icondel::kFrames, 2);
    w32(*m, work + scn::icondel::kEpl, 0);
    CHECK(v0s(spair(*m, "sub_3B8210", {task, 0, 0, 0}, ++seed, "icon task")) == 0);
    CHECK(r32(*m, work) == 1);
    w32(*m, work, 0);
    CHECK(v0s(spair(*m, "sub_3B8210", {task, 0, 0, 0}, ++seed, "icon task done")) == -1);

    // the scene-manager tasks (the live task kernel, the heap stand-in)
    if (snap) {
        const hgp::Run t = spair(*m, "sub_3BD0B0", {}, ++seed, "SceneManager tasks", keep());
        CHECK(v0u(t) != 0);
    }
    // the icon files through the fake file layer: 25 requests, each found in the cache afterwards
    fresh_worlds();
    const hgp::Run li = spair(*m, "sub_3BD130", {}, ++seed, "load icons", keep());
    if (!li.stopped) {
        u32 loaded = 0;
        for (u32 i = 0; i < 25; ++i) loaded += r32(*m, 0x95B000u + 4 * i) != 0 ? 1u : 0u;
        CHECK(loaded == 25);
        CHECK(g_t.world[1]->cd.missing.empty());
        for (u32 icon = 0; icon < 28; ++icon) {
            const u32 data = v0u(spair(*m, "sub_3BD1C0", {icon, 0, 0, 0}, ++seed, "icon file", keep()));
            CHECK((data != 0) == (icon < 25));
        }
        // a character's icon: the "10ban" icon created once, then reset; another icon swaps the slots
        zero(*m, kOut + 0x800, 496);
        w16(*m, kOut + 0x800, 0x0405u);  // type 1
        spair(*m, "sub_3BAC40", {kOut + 0x800, 10, 0, 0}, ++seed, "10ban icon", keep());
        if (printed_has("10ban icon create")) CHECK(r32(*m, kOut + 0x800 + scn::chr::kIconTen) != 0);
        spair(*m, "sub_3BAC40", {kOut + 0x800, 10, 0, 0}, ++seed, "10ban icon again", keep());
        // (the side byte toggles after the EPL is made: only when the run got that far)
        if (!spair(*m, "sub_3BAC40", {kOut + 0x800, 3, 0, 0}, ++seed, "icon 3", keep()).stopped)
            CHECK(r8(*m, kOut + 0x800 + scn::chr::kIconSide) == 1);
        // an object (type 3) toggles first
        zero(*m, kOut + 0xA00, 544);
        w16(*m, kOut + 0xA00, 0x0C05u);
        spair(*m, "sub_3BAC40", {kOut + 0xA00, 4, 0, 0}, ++seed, "object icon 4", keep());
        CHECK(r8(*m, kOut + 0xA00 + scn::npc::kIconSide) == 1);
    }
    // MT_Scene_FieldModelExists on a few field ids (the fake layer answers from extracted/)
    for (const auto& [ma, mi] : std::vector<std::pair<u32, u32>>{{1, 1}, {6, 1}, {21, 0}, {999, 999}})
        spair(*m, "sub_3B5620", {ma, mi, 0, 0}, ++seed, "field model exists");
    // nmListAllocNode: size + 24 bytes, the owner, the payload pointer
    fresh_worlds();
    for (const auto& [owner, size] : std::vector<std::pair<u32, u32>>{{0, 0}, {0, 40}, {0x01234500u, 100}}) {
        const hgp::Run r = spair(*m, "sub_3C4650", {0, owner, size, 0}, ++seed, "nm node", keep());
        const u32 node = v0u(r);
        REQUIRE(node != 0);
        CHECK(g_t.world[1]->heap.size_of(node) == round16(size + 24));
        CHECK(r32(*m, node) == (owner ? owner : node));
        CHECK(r32(*m, node + 8) == size + 24);
        CHECK(r32(*m, node + 20) == (size ? node + 24 : 0u));
    }
    // the fclBank panels: a panel put in state 1 slides in (state 2, frame 1)
    if (snap && r32(*m, 0x7CE680u) != 0) {
        const u32 panels = r32(*m, r32(*m, 0x7CE680u) + 36) + 4;
        w16(*m, panels, static_cast<u16>(r16(*m, panels) | 1u));
        w16(*m, panels + 2, 1);
        spair(*m, "sub_3CFB50", {}, ++seed, "bank panels");
        CHECK(r16(*m, panels + 2) == 2);
        CHECK(r16(*m, panels + 16) == 1);
        for (int f = 0; f < 6; ++f) spair(*m, "sub_3CFB50", {}, ++seed, "bank panels slide");
        CHECK(r16(*m, panels + 2) == 3);
    }
    // the facility panel slide on a made-up sprite record
    for (u32 flags : {0u, 2u, 0x40u, 0x42u}) {
        zero(*m, kOut + 0x900, 240);
        w32(*m, kOut + 0x900 + 8, flags);
        w16(*m, kOut + 0x900 + 18, 200);
        w16(*m, kOut + 0x900 + 20, 30);
        w16(*m, kOut + 0x900 + 22, 7);
        spair(*m, "sub_3CA960", {kOut + 0x900, 0, 0, 0}, ++seed, "panel slide");
    }
    // the leftovers of the matrix helpers
    for (int i = 0; i < 16; ++i) wf(*m, kOut + 4 * i, (i % 5 == 0) ? 1.0f : 0.0f);
    spair(*m, "sub_3B7AC0", {kOut, kOut + 0x80, kOut + 0x90, 0}, ++seed, "matrix to angles");
    for (int i = 0; i < 3; ++i) wf(*m, kOut + 0x40 + 4 * i, 10.0f * static_cast<float>(i + 1));
    spair(*m, "sub_3BB450", {kOut + 0x40, kOut + 0x50, 0, 0}, ++seed, "offset along dir", keep({{12, fb(5.0f)}}));
    spair(*m, "sub_3BBA70", {kOut + 0x100, 0, 0, 0}, ++seed, "norm record angles");
    spair(*m, "sub_3BBFD0", {kOut, kOut + 16, kOut + 32, kOut + 48}, ++seed, "two points", {{{8, kOut + 64}}, {{12, fb(0.25f)}, {13, fb(0.5f)}}});
}

TEST_CASE("game(scene): pair summary") {
    std::string s;
    for (const auto& [k, n] : g_stops) s += "\n  " + k + " x" + std::to_string(n);
    MESSAGE(g_pairs << " pairs, " << g_stops.size() << " distinct early stops (identical in both bodies):" << s);
}

#else

TEST_CASE("game(scene): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
