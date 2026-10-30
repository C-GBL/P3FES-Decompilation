// Pair tests of slice render_rw10 (game/src/render/render_rw10.cpp): RenderWare, tenth (last) pass -- the PS2
// native-data streams, the Rt2d fonts, the image-stored texture dictionaries, RtTileRender, the raster / texture native
// writers, the string / camera / spline streams, PTank's remaining geometries, the engine / sky device start-up. Every
// body runs against its recompiled body and tests/game/handgen_pairs.h compares the whole register file and cycles at
// every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS
// window and the bus log; the stand-ins' call logs and heaps must be equal too (stand_ins.h).
//   * sub_4E9680 stores a raster and its sub-rectangle in the sky globals (the one documented rule checked here);
//   * every body on the three snapshots with built records, and the random-world sweep (the p3fes_handgen skeleton).
// P3FES_HG_SEEDS sets the pairs per function of the random sweep, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces.
// Every random draw is its own statement (argument evaluation order differs between MSVC and clang-cl).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw10.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
void fn_sub_467860_00467860(EEContext&);  // generated body
void fn_sub_467860_00467860__recomp(EEContext&);  // recompiled
void fn_sub_46BFB0_0046bfb0(EEContext&);  // generated body
void fn_sub_46BFB0_0046bfb0__recomp(EEContext&);  // recompiled
void fn_sub_47BD20_0047bd20(EEContext&);  // generated body
void fn_sub_47BD20_0047bd20__recomp(EEContext&);  // recompiled
void fn_sub_486340_00486340(EEContext&);  // generated body
void fn_sub_486340_00486340__recomp(EEContext&);  // recompiled
void fn_sub_48D0E0_0048d0e0(EEContext&);  // generated body
void fn_sub_48D0E0_0048d0e0__recomp(EEContext&);  // recompiled
void fn_sub_49BCD0_0049bcd0(EEContext&);  // generated body
void fn_sub_49BCD0_0049bcd0__recomp(EEContext&);  // recompiled
void fn_sub_49BCE0_0049bce0(EEContext&);  // generated body
void fn_sub_49BCE0_0049bce0__recomp(EEContext&);  // recompiled
void fn_sub_49BD20_0049bd20(EEContext&);  // generated body
void fn_sub_49BD20_0049bd20__recomp(EEContext&);  // recompiled
void fn_sub_49BD30_0049bd30(EEContext&);  // generated body
void fn_sub_49BD30_0049bd30__recomp(EEContext&);  // recompiled
void fn_sub_49C240_0049c240(EEContext&);  // generated body
void fn_sub_49C240_0049c240__recomp(EEContext&);  // recompiled
void fn_sub_49E830_0049e830(EEContext&);  // generated body
void fn_sub_49E830_0049e830__recomp(EEContext&);  // recompiled
void fn_sub_49E9F0_0049e9f0(EEContext&);  // generated body
void fn_sub_49E9F0_0049e9f0__recomp(EEContext&);  // recompiled
void fn_sub_49EE70_0049ee70(EEContext&);  // generated body
void fn_sub_49EE70_0049ee70__recomp(EEContext&);  // recompiled
void fn_sub_49F040_0049f040(EEContext&);  // generated body
void fn_sub_49F040_0049f040__recomp(EEContext&);  // recompiled
void fn_sub_4A6CE0_004a6ce0(EEContext&);  // generated body
void fn_sub_4A6CE0_004a6ce0__recomp(EEContext&);  // recompiled
void fn_sub_4A6EB0_004a6eb0(EEContext&);  // generated body
void fn_sub_4A6EB0_004a6eb0__recomp(EEContext&);  // recompiled
void fn_sub_4A7820_004a7820(EEContext&);  // generated body
void fn_sub_4A7820_004a7820__recomp(EEContext&);  // recompiled
void fn_sub_4A7E40_004a7e40(EEContext&);  // generated body
void fn_sub_4A7E40_004a7e40__recomp(EEContext&);  // recompiled
void fn_sub_4A8980_004a8980(EEContext&);  // generated body
void fn_sub_4A8980_004a8980__recomp(EEContext&);  // recompiled
void fn_sub_4A90F0_004a90f0(EEContext&);  // generated body
void fn_sub_4A90F0_004a90f0__recomp(EEContext&);  // recompiled
void fn_sub_4A97C0_004a97c0(EEContext&);  // generated body
void fn_sub_4A97C0_004a97c0__recomp(EEContext&);  // recompiled
void fn_sub_4A98A0_004a98a0(EEContext&);  // generated body
void fn_sub_4A98A0_004a98a0__recomp(EEContext&);  // recompiled
void fn_sub_4ACB90_004acb90(EEContext&);  // generated body
void fn_sub_4ACB90_004acb90__recomp(EEContext&);  // recompiled
void fn_sub_4ACE80_004ace80(EEContext&);  // generated body
void fn_sub_4ACE80_004ace80__recomp(EEContext&);  // recompiled
void fn_sub_4AE270_004ae270(EEContext&);  // generated body
void fn_sub_4AE270_004ae270__recomp(EEContext&);  // recompiled
void fn_sub_4AE4E0_004ae4e0(EEContext&);  // generated body
void fn_sub_4AE4E0_004ae4e0__recomp(EEContext&);  // recompiled
void fn_sub_4B24C0_004b24c0(EEContext&);  // generated body
void fn_sub_4B24C0_004b24c0__recomp(EEContext&);  // recompiled
void fn_sub_4B43C0_004b43c0(EEContext&);  // generated body
void fn_sub_4B43C0_004b43c0__recomp(EEContext&);  // recompiled
void fn_sub_4BCCD0_004bccd0(EEContext&);  // generated body
void fn_sub_4BCCD0_004bccd0__recomp(EEContext&);  // recompiled
void fn_sub_4BD260_004bd260(EEContext&);  // generated body
void fn_sub_4BD260_004bd260__recomp(EEContext&);  // recompiled
void fn_sub_4BD4E0_004bd4e0(EEContext&);  // generated body
void fn_sub_4BD4E0_004bd4e0__recomp(EEContext&);  // recompiled
void fn_sub_4BDA10_004bda10(EEContext&);  // generated body
void fn_sub_4BDA10_004bda10__recomp(EEContext&);  // recompiled
void fn_sub_4BEC20_004bec20(EEContext&);  // generated body
void fn_sub_4BEC20_004bec20__recomp(EEContext&);  // recompiled
void fn_sub_4BF540_004bf540(EEContext&);  // generated body
void fn_sub_4BF540_004bf540__recomp(EEContext&);  // recompiled
void fn_sub_4BF560_004bf560(EEContext&);  // generated body
void fn_sub_4BF560_004bf560__recomp(EEContext&);  // recompiled
void fn_sub_4BF880_004bf880(EEContext&);  // generated body
void fn_sub_4BF880_004bf880__recomp(EEContext&);  // recompiled
void fn_sub_4BF980_004bf980(EEContext&);  // generated body
void fn_sub_4BF980_004bf980__recomp(EEContext&);  // recompiled
void fn_sub_4C0550_004c0550(EEContext&);  // generated body
void fn_sub_4C0550_004c0550__recomp(EEContext&);  // recompiled
void fn_sub_4C0F70_004c0f70(EEContext&);  // generated body
void fn_sub_4C0F70_004c0f70__recomp(EEContext&);  // recompiled
void fn_sub_4C0FC0_004c0fc0(EEContext&);  // generated body
void fn_sub_4C0FC0_004c0fc0__recomp(EEContext&);  // recompiled
void fn_sub_4C7460_004c7460(EEContext&);  // generated body
void fn_sub_4C7460_004c7460__recomp(EEContext&);  // recompiled
void fn_sub_4C76C0_004c76c0(EEContext&);  // generated body
void fn_sub_4C76C0_004c76c0__recomp(EEContext&);  // recompiled
void fn_sub_4C7B90_004c7b90(EEContext&);  // generated body
void fn_sub_4C7B90_004c7b90__recomp(EEContext&);  // recompiled
void fn_RwEngineStart_004ca640(EEContext&);  // generated body
void fn_RwEngineStart_004ca640__recomp(EEContext&);  // recompiled
void fn_RwEngineOpen_004ca700(EEContext&);  // generated body
void fn_RwEngineOpen_004ca700__recomp(EEContext&);  // recompiled
void fn_sub_4CA850_004ca850(EEContext&);  // generated body
void fn_sub_4CA850_004ca850__recomp(EEContext&);  // recompiled
void fn_sub_4CFFD0_004cffd0(EEContext&);  // generated body
void fn_sub_4CFFD0_004cffd0__recomp(EEContext&);  // recompiled
void fn_sub_4D6700_004d6700(EEContext&);  // generated body
void fn_sub_4D6700_004d6700__recomp(EEContext&);  // recompiled
void fn_sub_4D8440_004d8440(EEContext&);  // generated body
void fn_sub_4D8440_004d8440__recomp(EEContext&);  // recompiled
void fn_sub_4DF140_004df140(EEContext&);  // generated body
void fn_sub_4DF140_004df140__recomp(EEContext&);  // recompiled
void fn_sub_4DF7C0_004df7c0(EEContext&);  // generated body
void fn_sub_4DF7C0_004df7c0__recomp(EEContext&);  // recompiled
void fn_sub_4DF870_004df870(EEContext&);  // generated body
void fn_sub_4DF870_004df870__recomp(EEContext&);  // recompiled
void fn_SkyUseMode_004dff20(EEContext&);  // generated body
void fn_SkyUseMode_004dff20__recomp(EEContext&);  // recompiled
void fn_skyCustomModeIsOk_004e0c10(EEContext&);  // generated body
void fn_skyCustomModeIsOk_004e0c10__recomp(EEContext&);  // recompiled
void fn_SkyCreateFBRaster_004e3100(EEContext&);  // generated body
void fn_SkyCreateFBRaster_004e3100__recomp(EEContext&);  // recompiled
void fn_SkyCreateDBRaster_004e3320(EEContext&);  // generated body
void fn_SkyCreateDBRaster_004e3320__recomp(EEContext&);  // recompiled
void fn_sub_4E9680_004e9680(EEContext&);  // generated body
void fn_sub_4E9680_004e9680__recomp(EEContext&);  // recompiled
void fn_sub_4EB7E0_004eb7e0(EEContext&);  // generated body
void fn_sub_4EB7E0_004eb7e0__recomp(EEContext&);  // recompiled
void fn_sub_4EBB40_004ebb40(EEContext&);  // generated body
void fn_sub_4EBB40_004ebb40__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_467860", 0x467860, &recomp_gen::fn_sub_467860_00467860, &recomp_gen::fn_sub_467860_00467860__recomp},
    {"sub_46BFB0", 0x46BFB0, &recomp_gen::fn_sub_46BFB0_0046bfb0, &recomp_gen::fn_sub_46BFB0_0046bfb0__recomp},
    {"sub_47BD20", 0x47BD20, &recomp_gen::fn_sub_47BD20_0047bd20, &recomp_gen::fn_sub_47BD20_0047bd20__recomp},
    {"sub_486340", 0x486340, &recomp_gen::fn_sub_486340_00486340, &recomp_gen::fn_sub_486340_00486340__recomp},
    {"sub_48D0E0", 0x48D0E0, &recomp_gen::fn_sub_48D0E0_0048d0e0, &recomp_gen::fn_sub_48D0E0_0048d0e0__recomp},
    {"sub_49BCD0", 0x49BCD0, &recomp_gen::fn_sub_49BCD0_0049bcd0, &recomp_gen::fn_sub_49BCD0_0049bcd0__recomp},
    {"sub_49BCE0", 0x49BCE0, &recomp_gen::fn_sub_49BCE0_0049bce0, &recomp_gen::fn_sub_49BCE0_0049bce0__recomp},
    {"sub_49BD20", 0x49BD20, &recomp_gen::fn_sub_49BD20_0049bd20, &recomp_gen::fn_sub_49BD20_0049bd20__recomp},
    {"sub_49BD30", 0x49BD30, &recomp_gen::fn_sub_49BD30_0049bd30, &recomp_gen::fn_sub_49BD30_0049bd30__recomp},
    {"sub_49C240", 0x49C240, &recomp_gen::fn_sub_49C240_0049c240, &recomp_gen::fn_sub_49C240_0049c240__recomp},
    {"sub_49E830", 0x49E830, &recomp_gen::fn_sub_49E830_0049e830, &recomp_gen::fn_sub_49E830_0049e830__recomp},
    {"sub_49E9F0", 0x49E9F0, &recomp_gen::fn_sub_49E9F0_0049e9f0, &recomp_gen::fn_sub_49E9F0_0049e9f0__recomp},
    {"sub_49EE70", 0x49EE70, &recomp_gen::fn_sub_49EE70_0049ee70, &recomp_gen::fn_sub_49EE70_0049ee70__recomp},
    {"sub_49F040", 0x49F040, &recomp_gen::fn_sub_49F040_0049f040, &recomp_gen::fn_sub_49F040_0049f040__recomp},
    {"sub_4A6CE0", 0x4A6CE0, &recomp_gen::fn_sub_4A6CE0_004a6ce0, &recomp_gen::fn_sub_4A6CE0_004a6ce0__recomp},
    {"sub_4A6EB0", 0x4A6EB0, &recomp_gen::fn_sub_4A6EB0_004a6eb0, &recomp_gen::fn_sub_4A6EB0_004a6eb0__recomp},
    {"sub_4A7820", 0x4A7820, &recomp_gen::fn_sub_4A7820_004a7820, &recomp_gen::fn_sub_4A7820_004a7820__recomp},
    {"sub_4A7E40", 0x4A7E40, &recomp_gen::fn_sub_4A7E40_004a7e40, &recomp_gen::fn_sub_4A7E40_004a7e40__recomp},
    {"sub_4A8980", 0x4A8980, &recomp_gen::fn_sub_4A8980_004a8980, &recomp_gen::fn_sub_4A8980_004a8980__recomp},
    {"sub_4A90F0", 0x4A90F0, &recomp_gen::fn_sub_4A90F0_004a90f0, &recomp_gen::fn_sub_4A90F0_004a90f0__recomp},
    {"sub_4A97C0", 0x4A97C0, &recomp_gen::fn_sub_4A97C0_004a97c0, &recomp_gen::fn_sub_4A97C0_004a97c0__recomp},
    {"sub_4A98A0", 0x4A98A0, &recomp_gen::fn_sub_4A98A0_004a98a0, &recomp_gen::fn_sub_4A98A0_004a98a0__recomp},
    {"sub_4ACB90", 0x4ACB90, &recomp_gen::fn_sub_4ACB90_004acb90, &recomp_gen::fn_sub_4ACB90_004acb90__recomp},
    {"sub_4ACE80", 0x4ACE80, &recomp_gen::fn_sub_4ACE80_004ace80, &recomp_gen::fn_sub_4ACE80_004ace80__recomp},
    {"sub_4AE270", 0x4AE270, &recomp_gen::fn_sub_4AE270_004ae270, &recomp_gen::fn_sub_4AE270_004ae270__recomp},
    {"sub_4AE4E0", 0x4AE4E0, &recomp_gen::fn_sub_4AE4E0_004ae4e0, &recomp_gen::fn_sub_4AE4E0_004ae4e0__recomp},
    {"sub_4B24C0", 0x4B24C0, &recomp_gen::fn_sub_4B24C0_004b24c0, &recomp_gen::fn_sub_4B24C0_004b24c0__recomp},
    {"sub_4B43C0", 0x4B43C0, &recomp_gen::fn_sub_4B43C0_004b43c0, &recomp_gen::fn_sub_4B43C0_004b43c0__recomp},
    {"sub_4BCCD0", 0x4BCCD0, &recomp_gen::fn_sub_4BCCD0_004bccd0, &recomp_gen::fn_sub_4BCCD0_004bccd0__recomp},
    {"sub_4BD260", 0x4BD260, &recomp_gen::fn_sub_4BD260_004bd260, &recomp_gen::fn_sub_4BD260_004bd260__recomp},
    {"sub_4BD4E0", 0x4BD4E0, &recomp_gen::fn_sub_4BD4E0_004bd4e0, &recomp_gen::fn_sub_4BD4E0_004bd4e0__recomp},
    {"sub_4BDA10", 0x4BDA10, &recomp_gen::fn_sub_4BDA10_004bda10, &recomp_gen::fn_sub_4BDA10_004bda10__recomp},
    {"sub_4BEC20", 0x4BEC20, &recomp_gen::fn_sub_4BEC20_004bec20, &recomp_gen::fn_sub_4BEC20_004bec20__recomp},
    {"sub_4BF540", 0x4BF540, &recomp_gen::fn_sub_4BF540_004bf540, &recomp_gen::fn_sub_4BF540_004bf540__recomp},
    {"sub_4BF560", 0x4BF560, &recomp_gen::fn_sub_4BF560_004bf560, &recomp_gen::fn_sub_4BF560_004bf560__recomp},
    {"sub_4BF880", 0x4BF880, &recomp_gen::fn_sub_4BF880_004bf880, &recomp_gen::fn_sub_4BF880_004bf880__recomp},
    {"sub_4BF980", 0x4BF980, &recomp_gen::fn_sub_4BF980_004bf980, &recomp_gen::fn_sub_4BF980_004bf980__recomp},
    {"sub_4C0550", 0x4C0550, &recomp_gen::fn_sub_4C0550_004c0550, &recomp_gen::fn_sub_4C0550_004c0550__recomp},
    {"sub_4C0F70", 0x4C0F70, &recomp_gen::fn_sub_4C0F70_004c0f70, &recomp_gen::fn_sub_4C0F70_004c0f70__recomp},
    {"sub_4C0FC0", 0x4C0FC0, &recomp_gen::fn_sub_4C0FC0_004c0fc0, &recomp_gen::fn_sub_4C0FC0_004c0fc0__recomp},
    {"sub_4C7460", 0x4C7460, &recomp_gen::fn_sub_4C7460_004c7460, &recomp_gen::fn_sub_4C7460_004c7460__recomp},
    {"sub_4C76C0", 0x4C76C0, &recomp_gen::fn_sub_4C76C0_004c76c0, &recomp_gen::fn_sub_4C76C0_004c76c0__recomp},
    {"sub_4C7B90", 0x4C7B90, &recomp_gen::fn_sub_4C7B90_004c7b90, &recomp_gen::fn_sub_4C7B90_004c7b90__recomp},
    {"RwEngineStart", 0x4CA640, &recomp_gen::fn_RwEngineStart_004ca640, &recomp_gen::fn_RwEngineStart_004ca640__recomp},
    {"RwEngineOpen", 0x4CA700, &recomp_gen::fn_RwEngineOpen_004ca700, &recomp_gen::fn_RwEngineOpen_004ca700__recomp},
    {"sub_4CA850", 0x4CA850, &recomp_gen::fn_sub_4CA850_004ca850, &recomp_gen::fn_sub_4CA850_004ca850__recomp},
    {"sub_4CFFD0", 0x4CFFD0, &recomp_gen::fn_sub_4CFFD0_004cffd0, &recomp_gen::fn_sub_4CFFD0_004cffd0__recomp},
    {"sub_4D6700", 0x4D6700, &recomp_gen::fn_sub_4D6700_004d6700, &recomp_gen::fn_sub_4D6700_004d6700__recomp},
    {"sub_4D8440", 0x4D8440, &recomp_gen::fn_sub_4D8440_004d8440, &recomp_gen::fn_sub_4D8440_004d8440__recomp},
    {"sub_4DF140", 0x4DF140, &recomp_gen::fn_sub_4DF140_004df140, &recomp_gen::fn_sub_4DF140_004df140__recomp},
    {"sub_4DF7C0", 0x4DF7C0, &recomp_gen::fn_sub_4DF7C0_004df7c0, &recomp_gen::fn_sub_4DF7C0_004df7c0__recomp},
    {"sub_4DF870", 0x4DF870, &recomp_gen::fn_sub_4DF870_004df870, &recomp_gen::fn_sub_4DF870_004df870__recomp},
    {"SkyUseMode", 0x4DFF20, &recomp_gen::fn_SkyUseMode_004dff20, &recomp_gen::fn_SkyUseMode_004dff20__recomp},
    {"skyCustomModeIsOk", 0x4E0C10, &recomp_gen::fn_skyCustomModeIsOk_004e0c10, &recomp_gen::fn_skyCustomModeIsOk_004e0c10__recomp},
    {"SkyCreateFBRaster", 0x4E3100, &recomp_gen::fn_SkyCreateFBRaster_004e3100, &recomp_gen::fn_SkyCreateFBRaster_004e3100__recomp},
    {"SkyCreateDBRaster", 0x4E3320, &recomp_gen::fn_SkyCreateDBRaster_004e3320, &recomp_gen::fn_SkyCreateDBRaster_004e3320__recomp},
    {"sub_4E9680", 0x4E9680, &recomp_gen::fn_sub_4E9680_004e9680, &recomp_gen::fn_sub_4E9680_004e9680__recomp},
    {"sub_4EB7E0", 0x4EB7E0, &recomp_gen::fn_sub_4EB7E0_004eb7e0, &recomp_gen::fn_sub_4EB7E0_004eb7e0__recomp},
    {"sub_4EBB40", 0x4EBB40, &recomp_gen::fn_sub_4EBB40_004ebb40, &recomp_gen::fn_sub_4EBB40_004ebb40__recomp},
};

// The world of the random sweep: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

// --- guest helpers ---------------------------------------------------------------------------------------------------
u32 ld(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
u8 ld8(Machine& m, u32 va) { return *m.at(va); }
float ldf(Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.at(va), 4);
    return f;
}
void st(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void stf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void sts(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
std::string lds(Machine& m, u32 va) { return reinterpret_cast<const char*>(m.at(va)); }
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
float frand(std::mt19937& rng, float lo, float hi) {
    const u32 r = rng() % 100001;
    return lo + (hi - lo) * static_cast<float>(r) / 100000.0f;
}
bool in_ram(u32 va, u32 len = 4) { return va != 0 && va < EEMemory::kMainRamSize - len; }

bool has_case(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return true;
    return false;
}
const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw10 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read.
constexpr u32 kEngine = 0x960070u;
constexpr u32 kGpClump = 0x7CE820u;      // the atomic free list (+0) and the clump free list (+4) at engine + this
constexpr u32 kGpImage = 0x7CE938u;      // the image module's block at engine + this (+12 gamma table, +268 inverse)
constexpr u32 kRegGeometry = 0x77DD20u;  // the geometry plugin registry (+0 the extended record size)
// Test data: free in the ELF's image and in every replay snapshot (below the stand-in heap 0x1C00000).
constexpr u32 kData = 0x01BC0000u;
constexpr u32 kDataSize = 0x00040000u;
// A function this build does not emit, served by a recorder (callbacks the bodies call through pointers).
constexpr u32 kCallback = 0x10A860u;

std::unique_ptr<Machine> snapshot_machine(const char* dir, std::vector<u8>& image) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    image = read_snapshot(dir);
    if (image.empty()) return nullptr;
    std::memcpy(m->mem.main_ram(), image.data(), image.size());
    write_rw_slots(*m);
    return m;
}
void restore(Machine& m, const std::vector<u8>& image) {
    std::memcpy(m.mem.main_ram(), image.data(), image.size());
    write_rw_slots(m);
    std::memset(m.at(kData), 0, kDataSize);
}

// The live entries of an RW free list (the used bits of each block, MSB first).
std::vector<u32> live_entries(Machine& m, u32 fl) {
    std::vector<u32> out;
    if (!in_ram(fl, 64)) return out;
    const u32 es = ld(m, fl), hs = ld(m, fl + 8), al = ld(m, fl + 12);
    if (al == 0 || hs > 64 || es == 0) return out;
    const u32 head = fl + 16;
    u32 b = ld(m, head);
    for (int nb = 0; b != head && in_ram(b) && nb < 256; ++nb, b = ld(m, b)) {
        const u32 base = (b + hs + al + 7) & ~(al - 1);
        for (u32 i = 0; i < hs; ++i) {
            const u8 bits = m.at(b + 8)[i];
            for (u32 k = 0; k < 8; ++k)
                if (bits & (0x80u >> k)) out.push_back(base + es * (8 * i + k));
        }
    }
    return out;
}
// A clump's atomics: its list head at +8, each atomic linked at +64.
std::vector<u32> clump_atomics(Machine& m, u32 clump) {
    std::vector<u32> out;
    const u32 head = clump + 8;
    for (u32 e = ld(m, head), n = 0; e != head && in_ram(e, 4) && n < 256; e = ld(m, e), ++n) out.push_back(e - 64);
    return out;
}
u32 frame_root(Machine& m, u32 frame) {
    for (int n = 0; n < 64 && in_ram(frame, 164); ++n) {
        const u32 parent = ld(m, frame + 4);
        if (!in_ram(parent, 164)) return frame;
        frame = parent;
    }
    return frame;
}

// --- the pair on stand-in worlds -------------------------------------------------------------------------------------
// hgp::pair with a fresh stand-in world around each body (the heap behind the RW memory slots and the free-list entry
// points, printf / sprintf, the H_Cdvd layer); afterwards both worlds' call logs, live heap blocks and bad frees must be
// equal. Float arguments go in through g_fpr (set after the harness's randomised registers). A sequence of calls can run
// as one body (both runs make the same calls in one stand-in world): each step sets $a0..$a3, $a0 = the previous call's
// $v0 when chained.
Fn g_body[2];
StandInWorld* g_world[2];
std::map<unsigned, float> g_fpr;
struct Step {
    const Case* c;
    Args a;
    bool chain = false;
};
std::vector<Step> g_seq;
std::vector<u32> g_seq_v0;  // each step's $v0 (the recompiled run's, written by the second run)
void thunk(int k, EEContext& ctx) {
    StandInsScope s(g_world[k]->si);
    for (const auto& [r, f] : g_fpr) ctx.fpr[r] = fbits(f);
    if (g_seq.empty()) {
        g_body[k](ctx);
        return;
    }
    g_seq_v0.clear();
    for (std::size_t i = 0; i < g_seq.size(); ++i) {
        const Step& st = g_seq[i];
        if (i > 0) {
            const u64 prev = ctx.gpr[GPR_V0].u64[0];
            for (int r = 0; r < 4; ++r) ctx.gpr[GPR_A0 + r].u64[0] = st.a[static_cast<std::size_t>(r)];
            if (st.chain) ctx.gpr[GPR_A0].u64[0] = prev;
        }
        (k == 0 ? st.c->hand : st.c->recomp)(ctx);
        g_seq_v0.push_back(static_cast<u32>(ctx.gpr[GPR_V0].u64[0]));
    }
}
void thunk_hand(EEContext& ctx) { thunk(0, ctx); }
void thunk_recomp(EEContext& ctx) { thunk(1, ctx); }

struct WPair {
    hgp::Run run;
    std::unique_ptr<StandInWorld> hand, recomp;
    u32 v0() const { return static_cast<u32>(run.end.gpr[GPR_V0].u64[0]); }
};

WPair wpair(Machine& m, const Case& c, const Args& args, u32 seed, const WorldSetup& setup, const HwCheck& hw = {}) {
    WPair p;
    p.hand = std::make_unique<StandInWorld>();
    p.recomp = std::make_unique<StandInWorld>();
    setup(*p.hand);
    setup(*p.recomp);
    g_body[0] = c.hand;
    g_body[1] = c.recomp;
    g_world[0] = p.hand.get();
    g_world[1] = p.recomp.get();
    p.run = hgp::pair(m, thunk_hand, thunk_recomp, args, seed, c.name, hw);
    expect_same_log(p.hand->si, p.recomp->si, c.name);
    CHECK(p.hand->heap.live() == p.recomp->heap.live());
    CHECK(p.hand->heap.bad_frees == p.recomp->heap.bad_frees);
    g_fpr.clear();
    return p;
}
WPair wp(Machine& m, const char* name, const Args& args, u32 seed, const WorldSetup& setup = install_standard, const HwCheck& hw = {}) {
    return wpair(m, by_name(name), args, seed, setup, hw);
}
WPair wseq(Machine& m, const std::vector<Step>& steps, u32 seed, const WorldSetup& setup = install_standard) {
    g_seq = steps;
    WPair p = wpair(m, *steps.front().c, steps.front().a, seed, setup);
    g_seq.clear();
    return p;
}
Step step(const char* name, const Args& a = {0, 0, 0, 0}, bool chain = false) { return Step{&by_name(name), a, chain}; }

// =====================================================================================================================
// sub_4E9680 [skySetSubRasterGlobals]
// =====================================================================================================================
// The raster ($a1) goes to gp-16896 (0x7CEAF0), its x / y halfwords (+28 / +30, sign-extended) and width / height words
// (+12 / +16) to 0x965840..0x96584C; $v0 = 1.
TEST_CASE("game(render_rw10): sub_4E9680 keeps a raster's sub-rectangle in the sky globals") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 r = kData + 0x100;
    st(*m, r + 12, 640);
    st(*m, r + 16, 448);
    st(*m, r + 28, 0x0020FFF0u);  // x = -16, y = 32
    const WPair p = wp(*m, "sub_4E9680", Args{0, r, 0, 0}, 4u);
    const u32 gp = static_cast<u32>(p.run.end.gpr[28].u64[0]);
    CHECK(p.v0() == 1);
    CHECK(ld(*m, gp - 16896) == r);
    CHECK(ld(*m, 0x965840) == 0xFFFFFFF0u);
    CHECK(ld(*m, 0x965844) == 32);
    CHECK(ld(*m, 0x965848) == 640);
    CHECK(ld(*m, 0x96584C) == 448);
}

// =====================================================================================================================
// Every body on the snapshots with built records, then the random-world sweep
// =====================================================================================================================
// Functions whose soup / random runs would only recurse through cycles a soup offers or start the whole device: they run
// in the tests above (or not at all on random input).
const std::set<u32> kNoSoup = {};
// ... and of those, the ones the random worlds (all RW slots 0, a 64 KiB world of random words) cannot bound either.
const std::set<u32> kNoRandom = {};

TEST_CASE("game(render_rw10): every body equals its recompiled body on the snapshots with built records") {
    int pairs = 0, whole = 0, snapshots = 0;
    std::map<std::string, int> runs;
    for (const char* sn : {"b_5800", "dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snapshots;
        Machine& m = *mp;
        std::mt19937 rng{0x52573A00u + static_cast<u32>(snapshots)};
        restore(m, image);
        std::vector<u32> live = live_entries(m, ld(m, kEngine + ld(m, kGpClump)));
        const std::vector<u32> cl = live_entries(m, ld(m, kEngine + ld(m, kGpClump) + 4));
        live.insert(live.end(), cl.begin(), cl.end());
        for (const Case& c : kCases) {
            if (kNoSoup.count(c.addr)) continue;
            for (int k = 0; k < 8; ++k) {
                restore(m, image);
                const u32 soup = kData + 0x1000;
                const u32 seed = rng();
                auto setup = [&m, seed, &live](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(kCallback, "callback (returns 0)", 0);
                    std::mt19937 r{seed};
                    for (u32 i = 0; i < 0x2000; i += 4) {
                        const u32 kind = r() % 8;
                        u32 v;
                        if (kind < 3) {
                            const u32 off = r() % 0x2000;
                            v = soup + (off & ~15u);
                        } else if (kind < 5) {
                            v = r() % 8;
                        } else if (kind < 6 && !live.empty()) {
                            const u32 j = r() % static_cast<u32>(live.size());
                            v = live[j];
                        } else {
                            v = r() % 3 == 0 ? 0xFFFFFFFFu : 0;
                        }
                        st(m, soup + i, v);
                    }
                };
                Args a{};
                for (int i = 0; i < 4; ++i) {
                    const u32 pick = rng() % 4;
                    const u32 off = rng() % 0x2000;
                    a[static_cast<std::size_t>(i)] = pick < 2 ? soup + (off & ~15u) : pick == 2 ? off % 6 : kEngine;
                }
                const u32 t0off = rng() % 0x2000;
                const WPair p = wpair(m, c, a, 690000u + static_cast<u32>(pairs), setup,
                                      HwCheck{{}, {}, {}, {{GPR_T0, soup + (t0off & ~15u)}, {GPR_T1, soup + 0x600}}});
                ++pairs;
                whole += p.run.stopped ? 0 : 1;
                runs[c.name] += p.run.stopped ? 0 : 1;
            }
        }
    }
    if (snapshots == 0) return;
    MESSAGE("built-record pairs: " << pairs << " on " << snapshots << " snapshots, run whole " << whole);
    std::string never;
    for (const auto& [name, r] : runs)
        if (r == 0) never += name + " ";
    if (!never.empty()) MESSAGE("never run whole there: " << never);
}

// Every body against its recompiled body on random worlds (the p3fes_handgen sweep), each function from a fresh ELF
// image (the module opens / closes of earlier functions write the words later ones read).
TEST_CASE("game(render_rw10): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> elf_image(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        if (kNoRandom.count(c.addr)) continue;
        std::memcpy(m->mem.main_ram(), elf_image.data(), elf_image.size());
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (std::size_t i = 0; i < 4; ++i) args[i] = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

#else

TEST_CASE("game(render_rw10): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
