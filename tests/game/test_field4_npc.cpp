// Pair tests of slice field4, the NPC-placement / field-effect band (game/src/field/field4_npc.cpp): every body against
// its recompiled body, on random worlds (the p3fes_handgen sweep), the party-member field rules and the field predicates
// on five snapshots (documented scene rules checked), the built-in editor's FBN image (the field4.h layout, byte for
// byte) and record lists, and the FBN / HBN / script / MAP requests and the field-script copy on the stand-in world.
#include "handgen_pairs.h"
#include "field4_util.h"

#include "p3fes/game/field4.h"

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
void fn_sub_1DC6F0_001dc6f0(EEContext&);  // generated body
void fn_sub_1DC6F0_001dc6f0__recomp(EEContext&);  // recompiled
void fn_sub_1DC8E0_001dc8e0(EEContext&);  // generated body
void fn_sub_1DC8E0_001dc8e0__recomp(EEContext&);  // recompiled
void fn_sub_1DC910_001dc910(EEContext&);  // generated body
void fn_sub_1DC910_001dc910__recomp(EEContext&);  // recompiled
void fn_sub_1DCA10_001dca10(EEContext&);  // generated body
void fn_sub_1DCA10_001dca10__recomp(EEContext&);  // recompiled
void fn_sub_1DCB60_001dcb60(EEContext&);  // generated body
void fn_sub_1DCB60_001dcb60__recomp(EEContext&);  // recompiled
void fn_sub_1DD430_001dd430(EEContext&);  // generated body
void fn_sub_1DD430_001dd430__recomp(EEContext&);  // recompiled
void fn_sub_1DD460_001dd460(EEContext&);  // generated body
void fn_sub_1DD460_001dd460__recomp(EEContext&);  // recompiled
void fn_sub_1DD530_001dd530(EEContext&);  // generated body
void fn_sub_1DD530_001dd530__recomp(EEContext&);  // recompiled
void fn_sub_1DD600_001dd600(EEContext&);  // generated body
void fn_sub_1DD600_001dd600__recomp(EEContext&);  // recompiled
void fn_sub_1DD8E0_001dd8e0(EEContext&);  // generated body
void fn_sub_1DD8E0_001dd8e0__recomp(EEContext&);  // recompiled
void fn_sub_1DDB30_001ddb30(EEContext&);  // generated body
void fn_sub_1DDB30_001ddb30__recomp(EEContext&);  // recompiled
void fn_sub_1DDCA0_001ddca0(EEContext&);  // generated body
void fn_sub_1DDCA0_001ddca0__recomp(EEContext&);  // recompiled
void fn_sub_1DDD30_001ddd30(EEContext&);  // generated body
void fn_sub_1DDD30_001ddd30__recomp(EEContext&);  // recompiled
void fn_sub_1DDE00_001dde00(EEContext&);  // generated body
void fn_sub_1DDE00_001dde00__recomp(EEContext&);  // recompiled
void fn_sub_1DE630_001de630(EEContext&);  // generated body
void fn_sub_1DE630_001de630__recomp(EEContext&);  // recompiled
void fn_sub_1DED40_001ded40(EEContext&);  // generated body
void fn_sub_1DED40_001ded40__recomp(EEContext&);  // recompiled
void fn_sub_1DF450_001df450(EEContext&);  // generated body
void fn_sub_1DF450_001df450__recomp(EEContext&);  // recompiled
void fn_sub_1DFA70_001dfa70(EEContext&);  // generated body
void fn_sub_1DFA70_001dfa70__recomp(EEContext&);  // recompiled
void fn_sub_1E1850_001e1850(EEContext&);  // generated body
void fn_sub_1E1850_001e1850__recomp(EEContext&);  // recompiled
void fn_sub_1E2300_001e2300(EEContext&);  // generated body
void fn_sub_1E2300_001e2300__recomp(EEContext&);  // recompiled
void fn_sub_1E2370_001e2370(EEContext&);  // generated body
void fn_sub_1E2370_001e2370__recomp(EEContext&);  // recompiled
void fn_sub_1E2430_001e2430(EEContext&);  // generated body
void fn_sub_1E2430_001e2430__recomp(EEContext&);  // recompiled
void fn_sub_1E2850_001e2850(EEContext&);  // generated body
void fn_sub_1E2850_001e2850__recomp(EEContext&);  // recompiled
void fn_sub_1E28A0_001e28a0(EEContext&);  // generated body
void fn_sub_1E28A0_001e28a0__recomp(EEContext&);  // recompiled
void fn_sub_1E2930_001e2930(EEContext&);  // generated body
void fn_sub_1E2930_001e2930__recomp(EEContext&);  // recompiled
void fn_sub_1E2A20_001e2a20(EEContext&);  // generated body
void fn_sub_1E2A20_001e2a20__recomp(EEContext&);  // recompiled
void fn_sub_1E2A70_001e2a70(EEContext&);  // generated body
void fn_sub_1E2A70_001e2a70__recomp(EEContext&);  // recompiled
void fn_sub_1E2B10_001e2b10(EEContext&);  // generated body
void fn_sub_1E2B10_001e2b10__recomp(EEContext&);  // recompiled
void fn_sub_1E2BD0_001e2bd0(EEContext&);  // generated body
void fn_sub_1E2BD0_001e2bd0__recomp(EEContext&);  // recompiled
void fn_sub_1E2DA0_001e2da0(EEContext&);  // generated body
void fn_sub_1E2DA0_001e2da0__recomp(EEContext&);  // recompiled
void fn_sub_1E2E50_001e2e50(EEContext&);  // generated body
void fn_sub_1E2E50_001e2e50__recomp(EEContext&);  // recompiled
void fn_sub_1E3940_001e3940(EEContext&);  // generated body
void fn_sub_1E3940_001e3940__recomp(EEContext&);  // recompiled
void fn_sub_1E3F10_001e3f10(EEContext&);  // generated body
void fn_sub_1E3F10_001e3f10__recomp(EEContext&);  // recompiled
void fn_sub_1E4B10_001e4b10(EEContext&);  // generated body
void fn_sub_1E4B10_001e4b10__recomp(EEContext&);  // recompiled
void fn_sub_1E4B40_001e4b40(EEContext&);  // generated body
void fn_sub_1E4B40_001e4b40__recomp(EEContext&);  // recompiled
void fn_sub_1E4BC0_001e4bc0(EEContext&);  // generated body
void fn_sub_1E4BC0_001e4bc0__recomp(EEContext&);  // recompiled
void fn_sub_1E5820_001e5820(EEContext&);  // generated body
void fn_sub_1E5820_001e5820__recomp(EEContext&);  // recompiled
void fn_sub_1E5850_001e5850(EEContext&);  // generated body
void fn_sub_1E5850_001e5850__recomp(EEContext&);  // recompiled
void fn_sub_1E58D0_001e58d0(EEContext&);  // generated body
void fn_sub_1E58D0_001e58d0__recomp(EEContext&);  // recompiled
void fn_sub_1E6000_001e6000(EEContext&);  // generated body
void fn_sub_1E6000_001e6000__recomp(EEContext&);  // recompiled
void fn_sub_1E6030_001e6030(EEContext&);  // generated body
void fn_sub_1E6030_001e6030__recomp(EEContext&);  // recompiled
void fn_sub_1E60B0_001e60b0(EEContext&);  // generated body
void fn_sub_1E60B0_001e60b0__recomp(EEContext&);  // recompiled
void fn_sub_1E6A40_001e6a40(EEContext&);  // generated body
void fn_sub_1E6A40_001e6a40__recomp(EEContext&);  // recompiled
void fn_sub_1E6A70_001e6a70(EEContext&);  // generated body
void fn_sub_1E6A70_001e6a70__recomp(EEContext&);  // recompiled
void fn_sub_1E6AF0_001e6af0(EEContext&);  // generated body
void fn_sub_1E6AF0_001e6af0__recomp(EEContext&);  // recompiled
void fn_sub_1E6CB0_001e6cb0(EEContext&);  // generated body
void fn_sub_1E6CB0_001e6cb0__recomp(EEContext&);  // recompiled
void fn_sub_1E6D50_001e6d50(EEContext&);  // generated body
void fn_sub_1E6D50_001e6d50__recomp(EEContext&);  // recompiled
void fn_sub_1E6EA0_001e6ea0(EEContext&);  // generated body
void fn_sub_1E6EA0_001e6ea0__recomp(EEContext&);  // recompiled
void fn_sub_1E7200_001e7200(EEContext&);  // generated body
void fn_sub_1E7200_001e7200__recomp(EEContext&);  // recompiled
void fn_sub_1E7290_001e7290(EEContext&);  // generated body
void fn_sub_1E7290_001e7290__recomp(EEContext&);  // recompiled
void fn_sub_1E7410_001e7410(EEContext&);  // generated body
void fn_sub_1E7410_001e7410__recomp(EEContext&);  // recompiled
void fn_sub_1E7470_001e7470(EEContext&);  // generated body
void fn_sub_1E7470_001e7470__recomp(EEContext&);  // recompiled
void fn_sub_1E74E0_001e74e0(EEContext&);  // generated body
void fn_sub_1E74E0_001e74e0__recomp(EEContext&);  // recompiled
void fn_sub_1E7520_001e7520(EEContext&);  // generated body
void fn_sub_1E7520_001e7520__recomp(EEContext&);  // recompiled
void fn_sub_1E7540_001e7540(EEContext&);  // generated body
void fn_sub_1E7540_001e7540__recomp(EEContext&);  // recompiled
void fn_sub_1E75B0_001e75b0(EEContext&);  // generated body
void fn_sub_1E75B0_001e75b0__recomp(EEContext&);  // recompiled
void fn_sub_1E7720_001e7720(EEContext&);  // generated body
void fn_sub_1E7720_001e7720__recomp(EEContext&);  // recompiled
void fn_sub_1E78C0_001e78c0(EEContext&);  // generated body
void fn_sub_1E78C0_001e78c0__recomp(EEContext&);  // recompiled
void fn_sub_1E7A60_001e7a60(EEContext&);  // generated body
void fn_sub_1E7A60_001e7a60__recomp(EEContext&);  // recompiled
void fn_sub_1E7AA0_001e7aa0(EEContext&);  // generated body
void fn_sub_1E7AA0_001e7aa0__recomp(EEContext&);  // recompiled
void fn_sub_1E7B10_001e7b10(EEContext&);  // generated body
void fn_sub_1E7B10_001e7b10__recomp(EEContext&);  // recompiled
void fn_sub_1E7C20_001e7c20(EEContext&);  // generated body
void fn_sub_1E7C20_001e7c20__recomp(EEContext&);  // recompiled
void fn_sub_1E7CE0_001e7ce0(EEContext&);  // generated body
void fn_sub_1E7CE0_001e7ce0__recomp(EEContext&);  // recompiled
void fn_sub_1E7DE0_001e7de0(EEContext&);  // generated body
void fn_sub_1E7DE0_001e7de0__recomp(EEContext&);  // recompiled
void fn_sub_1E7E30_001e7e30(EEContext&);  // generated body
void fn_sub_1E7E30_001e7e30__recomp(EEContext&);  // recompiled
void fn_sub_1E7F90_001e7f90(EEContext&);  // generated body
void fn_sub_1E7F90_001e7f90__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1DC6F0", 0x1DC6F0, &recomp_gen::fn_sub_1DC6F0_001dc6f0, &recomp_gen::fn_sub_1DC6F0_001dc6f0__recomp},
    {"sub_1DC8E0", 0x1DC8E0, &recomp_gen::fn_sub_1DC8E0_001dc8e0, &recomp_gen::fn_sub_1DC8E0_001dc8e0__recomp},
    {"sub_1DC910", 0x1DC910, &recomp_gen::fn_sub_1DC910_001dc910, &recomp_gen::fn_sub_1DC910_001dc910__recomp},
    {"sub_1DCA10", 0x1DCA10, &recomp_gen::fn_sub_1DCA10_001dca10, &recomp_gen::fn_sub_1DCA10_001dca10__recomp},
    {"sub_1DCB60", 0x1DCB60, &recomp_gen::fn_sub_1DCB60_001dcb60, &recomp_gen::fn_sub_1DCB60_001dcb60__recomp},
    {"sub_1DD430", 0x1DD430, &recomp_gen::fn_sub_1DD430_001dd430, &recomp_gen::fn_sub_1DD430_001dd430__recomp},
    {"sub_1DD460", 0x1DD460, &recomp_gen::fn_sub_1DD460_001dd460, &recomp_gen::fn_sub_1DD460_001dd460__recomp},
    {"sub_1DD530", 0x1DD530, &recomp_gen::fn_sub_1DD530_001dd530, &recomp_gen::fn_sub_1DD530_001dd530__recomp},
    {"sub_1DD600", 0x1DD600, &recomp_gen::fn_sub_1DD600_001dd600, &recomp_gen::fn_sub_1DD600_001dd600__recomp},
    {"sub_1DD8E0", 0x1DD8E0, &recomp_gen::fn_sub_1DD8E0_001dd8e0, &recomp_gen::fn_sub_1DD8E0_001dd8e0__recomp},
    {"sub_1DDB30", 0x1DDB30, &recomp_gen::fn_sub_1DDB30_001ddb30, &recomp_gen::fn_sub_1DDB30_001ddb30__recomp},
    {"sub_1DDCA0", 0x1DDCA0, &recomp_gen::fn_sub_1DDCA0_001ddca0, &recomp_gen::fn_sub_1DDCA0_001ddca0__recomp},
    {"sub_1DDD30", 0x1DDD30, &recomp_gen::fn_sub_1DDD30_001ddd30, &recomp_gen::fn_sub_1DDD30_001ddd30__recomp},
    {"sub_1DDE00", 0x1DDE00, &recomp_gen::fn_sub_1DDE00_001dde00, &recomp_gen::fn_sub_1DDE00_001dde00__recomp},
    {"sub_1DE630", 0x1DE630, &recomp_gen::fn_sub_1DE630_001de630, &recomp_gen::fn_sub_1DE630_001de630__recomp},
    {"sub_1DED40", 0x1DED40, &recomp_gen::fn_sub_1DED40_001ded40, &recomp_gen::fn_sub_1DED40_001ded40__recomp},
    {"sub_1DF450", 0x1DF450, &recomp_gen::fn_sub_1DF450_001df450, &recomp_gen::fn_sub_1DF450_001df450__recomp},
    {"sub_1DFA70", 0x1DFA70, &recomp_gen::fn_sub_1DFA70_001dfa70, &recomp_gen::fn_sub_1DFA70_001dfa70__recomp},
    {"sub_1E1850", 0x1E1850, &recomp_gen::fn_sub_1E1850_001e1850, &recomp_gen::fn_sub_1E1850_001e1850__recomp},
    {"sub_1E2300", 0x1E2300, &recomp_gen::fn_sub_1E2300_001e2300, &recomp_gen::fn_sub_1E2300_001e2300__recomp},
    {"sub_1E2370", 0x1E2370, &recomp_gen::fn_sub_1E2370_001e2370, &recomp_gen::fn_sub_1E2370_001e2370__recomp},
    {"sub_1E2430", 0x1E2430, &recomp_gen::fn_sub_1E2430_001e2430, &recomp_gen::fn_sub_1E2430_001e2430__recomp},
    {"sub_1E2850", 0x1E2850, &recomp_gen::fn_sub_1E2850_001e2850, &recomp_gen::fn_sub_1E2850_001e2850__recomp},
    {"sub_1E28A0", 0x1E28A0, &recomp_gen::fn_sub_1E28A0_001e28a0, &recomp_gen::fn_sub_1E28A0_001e28a0__recomp},
    {"sub_1E2930", 0x1E2930, &recomp_gen::fn_sub_1E2930_001e2930, &recomp_gen::fn_sub_1E2930_001e2930__recomp},
    {"sub_1E2A20", 0x1E2A20, &recomp_gen::fn_sub_1E2A20_001e2a20, &recomp_gen::fn_sub_1E2A20_001e2a20__recomp},
    {"sub_1E2A70", 0x1E2A70, &recomp_gen::fn_sub_1E2A70_001e2a70, &recomp_gen::fn_sub_1E2A70_001e2a70__recomp},
    {"sub_1E2B10", 0x1E2B10, &recomp_gen::fn_sub_1E2B10_001e2b10, &recomp_gen::fn_sub_1E2B10_001e2b10__recomp},
    {"sub_1E2BD0", 0x1E2BD0, &recomp_gen::fn_sub_1E2BD0_001e2bd0, &recomp_gen::fn_sub_1E2BD0_001e2bd0__recomp},
    {"sub_1E2DA0", 0x1E2DA0, &recomp_gen::fn_sub_1E2DA0_001e2da0, &recomp_gen::fn_sub_1E2DA0_001e2da0__recomp},
    {"sub_1E2E50", 0x1E2E50, &recomp_gen::fn_sub_1E2E50_001e2e50, &recomp_gen::fn_sub_1E2E50_001e2e50__recomp},
    {"sub_1E3940", 0x1E3940, &recomp_gen::fn_sub_1E3940_001e3940, &recomp_gen::fn_sub_1E3940_001e3940__recomp},
    {"sub_1E3F10", 0x1E3F10, &recomp_gen::fn_sub_1E3F10_001e3f10, &recomp_gen::fn_sub_1E3F10_001e3f10__recomp},
    {"sub_1E4B10", 0x1E4B10, &recomp_gen::fn_sub_1E4B10_001e4b10, &recomp_gen::fn_sub_1E4B10_001e4b10__recomp},
    {"sub_1E4B40", 0x1E4B40, &recomp_gen::fn_sub_1E4B40_001e4b40, &recomp_gen::fn_sub_1E4B40_001e4b40__recomp},
    {"sub_1E4BC0", 0x1E4BC0, &recomp_gen::fn_sub_1E4BC0_001e4bc0, &recomp_gen::fn_sub_1E4BC0_001e4bc0__recomp},
    {"sub_1E5820", 0x1E5820, &recomp_gen::fn_sub_1E5820_001e5820, &recomp_gen::fn_sub_1E5820_001e5820__recomp},
    {"sub_1E5850", 0x1E5850, &recomp_gen::fn_sub_1E5850_001e5850, &recomp_gen::fn_sub_1E5850_001e5850__recomp},
    {"sub_1E58D0", 0x1E58D0, &recomp_gen::fn_sub_1E58D0_001e58d0, &recomp_gen::fn_sub_1E58D0_001e58d0__recomp},
    {"sub_1E6000", 0x1E6000, &recomp_gen::fn_sub_1E6000_001e6000, &recomp_gen::fn_sub_1E6000_001e6000__recomp},
    {"sub_1E6030", 0x1E6030, &recomp_gen::fn_sub_1E6030_001e6030, &recomp_gen::fn_sub_1E6030_001e6030__recomp},
    {"sub_1E60B0", 0x1E60B0, &recomp_gen::fn_sub_1E60B0_001e60b0, &recomp_gen::fn_sub_1E60B0_001e60b0__recomp},
    {"sub_1E6A40", 0x1E6A40, &recomp_gen::fn_sub_1E6A40_001e6a40, &recomp_gen::fn_sub_1E6A40_001e6a40__recomp},
    {"sub_1E6A70", 0x1E6A70, &recomp_gen::fn_sub_1E6A70_001e6a70, &recomp_gen::fn_sub_1E6A70_001e6a70__recomp},
    {"sub_1E6AF0", 0x1E6AF0, &recomp_gen::fn_sub_1E6AF0_001e6af0, &recomp_gen::fn_sub_1E6AF0_001e6af0__recomp},
    {"sub_1E6CB0", 0x1E6CB0, &recomp_gen::fn_sub_1E6CB0_001e6cb0, &recomp_gen::fn_sub_1E6CB0_001e6cb0__recomp},
    {"sub_1E6D50", 0x1E6D50, &recomp_gen::fn_sub_1E6D50_001e6d50, &recomp_gen::fn_sub_1E6D50_001e6d50__recomp},
    {"sub_1E6EA0", 0x1E6EA0, &recomp_gen::fn_sub_1E6EA0_001e6ea0, &recomp_gen::fn_sub_1E6EA0_001e6ea0__recomp},
    {"sub_1E7200", 0x1E7200, &recomp_gen::fn_sub_1E7200_001e7200, &recomp_gen::fn_sub_1E7200_001e7200__recomp},
    {"sub_1E7290", 0x1E7290, &recomp_gen::fn_sub_1E7290_001e7290, &recomp_gen::fn_sub_1E7290_001e7290__recomp},
    {"sub_1E7410", 0x1E7410, &recomp_gen::fn_sub_1E7410_001e7410, &recomp_gen::fn_sub_1E7410_001e7410__recomp},
    {"sub_1E7470", 0x1E7470, &recomp_gen::fn_sub_1E7470_001e7470, &recomp_gen::fn_sub_1E7470_001e7470__recomp},
    {"sub_1E74E0", 0x1E74E0, &recomp_gen::fn_sub_1E74E0_001e74e0, &recomp_gen::fn_sub_1E74E0_001e74e0__recomp},
    {"sub_1E7520", 0x1E7520, &recomp_gen::fn_sub_1E7520_001e7520, &recomp_gen::fn_sub_1E7520_001e7520__recomp},
    {"sub_1E7540", 0x1E7540, &recomp_gen::fn_sub_1E7540_001e7540, &recomp_gen::fn_sub_1E7540_001e7540__recomp},
    {"sub_1E75B0", 0x1E75B0, &recomp_gen::fn_sub_1E75B0_001e75b0, &recomp_gen::fn_sub_1E75B0_001e75b0__recomp},
    {"sub_1E7720", 0x1E7720, &recomp_gen::fn_sub_1E7720_001e7720, &recomp_gen::fn_sub_1E7720_001e7720__recomp},
    {"sub_1E78C0", 0x1E78C0, &recomp_gen::fn_sub_1E78C0_001e78c0, &recomp_gen::fn_sub_1E78C0_001e78c0__recomp},
    {"sub_1E7A60", 0x1E7A60, &recomp_gen::fn_sub_1E7A60_001e7a60, &recomp_gen::fn_sub_1E7A60_001e7a60__recomp},
    {"sub_1E7AA0", 0x1E7AA0, &recomp_gen::fn_sub_1E7AA0_001e7aa0, &recomp_gen::fn_sub_1E7AA0_001e7aa0__recomp},
    {"sub_1E7B10", 0x1E7B10, &recomp_gen::fn_sub_1E7B10_001e7b10, &recomp_gen::fn_sub_1E7B10_001e7b10__recomp},
    {"sub_1E7C20", 0x1E7C20, &recomp_gen::fn_sub_1E7C20_001e7c20, &recomp_gen::fn_sub_1E7C20_001e7c20__recomp},
    {"sub_1E7CE0", 0x1E7CE0, &recomp_gen::fn_sub_1E7CE0_001e7ce0, &recomp_gen::fn_sub_1E7CE0_001e7ce0__recomp},
    {"sub_1E7DE0", 0x1E7DE0, &recomp_gen::fn_sub_1E7DE0_001e7de0, &recomp_gen::fn_sub_1E7DE0_001e7de0__recomp},
    {"sub_1E7E30", 0x1E7E30, &recomp_gen::fn_sub_1E7E30_001e7e30, &recomp_gen::fn_sub_1E7E30_001e7e30__recomp},
    {"sub_1E7F90", 0x1E7F90, &recomp_gen::fn_sub_1E7F90_001e7f90, &recomp_gen::fn_sub_1E7F90_001e7f90__recomp},
};

// The generic sweep: 64 KiB of free RAM above the harness's arena (the real structures: the snapshot cases below).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field4 npc): every body equals its recompiled body on random worlds") {
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

// --- field4 tests ---

namespace {
const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    std::fprintf(stderr, "no case %s\n", name);
    std::abort();
}
hgp::Run call(Machine& m, const char* fn, Args a, u32 seed = 1) {
    const Case& c = find_case(fn);
    return hgp::pair(m, c.hand, c.recomp, a, seed, fn);
}
using namespace f4t;
namespace fbn = game::f4::fbn;
constexpr u32 kNpcList = 0x7CE2B8u, kPosList = 0x7CE2BCu, kScheduleUsed = 0x7CE2C0u;
const char* const kSnaps[] = {"climb_ref_17000", "dorm_replay_4900", "shop_ref_4100", "fusion_vr_5000", "b_5800"};
}  // namespace

// The party-member field rules (sub_1DDE00 shown / sub_1DE630 walk / sub_1DED40 run / sub_1DF450 idle) for members
// 0..14 and the field predicates (party panel, mini-map, area name) on the snapshots' scenes: hand-written and
// recompiled agree, the results stay in their documented ranges, and the documented scene rules hold: member 2 never
// follows in majors 6 / 7 (the dorm 7/2) and walks / runs with set 1 / 2 there; Tartarus-type scenes (climb 51/4) have
// the party panel and the mini-map, the dorm neither (flag 3111 aside); in the dungeon the area name is the floor's
// record (0x67B160 + 26 floor, or The Answer's 0x67CFE0).
TEST_CASE("game(field4 npc): the party-member field rules and the field predicates on the replay snapshots") {
    int checked = 0;
    for (const char* snap : kSnaps) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        const s32 major = rs32(m, kSceneRecord), minor = rs32(m, kSceneRecord + 4);
        if (major < 0) continue;
        for (s64 member = 0; member <= 14; ++member) {
            const s64 shown = v0_of(call(m, "sub_1DDE00", {S(member), 0, 0, 0}, static_cast<u32>(member) + 1));
            const s64 walk = v0_of(call(m, "sub_1DE630", {S(member), 0, 0, 0}, static_cast<u32>(member) + 2));
            const s64 run = v0_of(call(m, "sub_1DED40", {S(member), 0, 0, 0}, static_cast<u32>(member) + 3));
            hgp::Run idle = call(m, "sub_1DF450", {S(member), 0, 0, 0}, static_cast<u32>(member) + 4);
            CHECK((shown == 0 || shown == 1));
            CHECK((walk >= 0 && walk <= 3));
            CHECK((run >= 0 && run <= 5));
            if (!idle.stopped && member == 1) {
                const s64 id = v0_of(idle);
                CHECK(((id >= 6 && id <= 8) || id == 15 || id == shown));
            }
            if (member == 2 && (major == 6 || major == 7)) {
                CHECK(shown == 0);
                CHECK(walk == 1);
                CHECK(run == 2);
            }
        }
        const s64 panel = v0_of(call(m, "sub_1DD600", {0, 0, 0, 0}, 50));
        const s64 minimap = v0_of(call(m, "sub_1DDD30", {0, 0, 0, 0}, 51));
        if (major >= 51 && major <= 58) {
            CHECK(panel == 1);
            CHECK(minimap == 1);
        }
        if (major == 7) CHECK(minimap == 0);
        const u32 dungeon = r32(m, gpv(game::f4::gpv::kDungeonTask));
        hgp::Run name = call(m, "sub_1DDB30", {0, 0, 0, 0}, 52);
        if (dungeon && !name.stopped) {
            const u32 floor = r32(m, r32(m, dungeon + game::f4::kTaskWork) + game::f4::dng::kFloor);
            const u32 got = static_cast<u32>(v0_of(name));
            if (floor < 400) CHECK((got == 0x67B160u + 26 * floor || got == 0x67CFE0u + 26 * floor));
            MESSAGE(std::string(snap) << ": floor " << floor << " area name at " << got);
        }
        ++checked;
        MESSAGE(std::string(snap) << " (" << major << "/" << minor << "): panel " << panel << ", mini-map " << minimap);
    }
    if (checked == 0) MESSAGE("SKIP: no replay snapshot");
}

// The built-in editor's FBN writer (sub_1E2BD0) on two NPC records and one position record linked as the editor
// keeps them (0x7CE2B8 / 0x7CE2BC): the image it builds in the heap is the FBN layout of field4.h -- {0x12345678,
// 0x00010001, 2, 112, 1, 96} and the records in list order, byte for byte -- the format a scene editor can write.
// Then the list helpers: a new record goes to the head of its list (sub_1E2850 / sub_1E2A20), freeing all clears it.
TEST_CASE("game(field4 npc): the field editor's FBN image and record lists (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    write_rw_slots(m);
    const HwCheck hw = whole_ram_check();
    const u32 a = kScratch, b = kScratch + 0x100, p = kScratch + 0x200;
    for (u32 i = 0; i < 0x300; ++i) w8(m, kScratch + i, static_cast<u8>(i * 7 + 3));
    w32(m, a + fbn::kNpcNext, b);
    w32(m, a + fbn::kNpcPrev, 0);
    w32(m, b + fbn::kNpcNext, 0);
    w32(m, b + fbn::kNpcPrev, a);
    w32(m, p + fbn::kPosNext, 0);
    w32(m, p + fbn::kPosPrev, 0);
    w32(m, kNpcList, a);
    w32(m, kPosList, p);
    w32(m, kScheduleUsed, 0);
    const std::vector<u8> ra(m.at(a), m.at(a) + 112), rb(m.at(b), m.at(b) + 112), rp(m.at(p), m.at(p) + 96);
    {
        const Case& c = find_case("sub_1E2BD0");
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {0, 0, 0, 0}, 1, c.name, hw);
        CHECK(v0_of(sp.hw) == 1);
        u32 image = 0;
        for (const StandInCall& k : sp.recomp->si.log)
            if (k.va == 0x104040u && !image) image = static_cast<u32>(k.v0);  // RwCalloc(1, size, hint)
        REQUIRE(image != 0);
        CHECK(r32(m, image + fbn::kHdrMagic) == fbn::kMagic);
        CHECK(r32(m, image + fbn::kHdrVersion) == fbn::kVersion);
        CHECK(r32(m, image + fbn::kHdrNpcCount) == 2);
        CHECK(r32(m, image + fbn::kHdrNpcSize) == 112);
        CHECK(r32(m, image + fbn::kHdrPosCount) == 1);
        CHECK(r32(m, image + fbn::kHdrPosSize) == 96);
        CHECK(guest_equals(m, image + 24, ra));
        CHECK(guest_equals(m, image + 24 + 112, rb));
        CHECK(guest_equals(m, image + 24 + 224, rp));
    }
    {
        // a schedule NPC was placed (0x7CE2C0): no image
        w32(m, kScheduleUsed, 1);
        const Case& c = find_case("sub_1E2BD0");
        SiPair sp = run_pair_si(m, c.hand, c.recomp, {0, 0, 0, 0}, 2, c.name, hw);
        CHECK(v0_of(sp.hw) == 0);
        w32(m, kScheduleUsed, 0);
    }
    {
        reset(m, base);
        write_rw_slots(m);
        w32(m, kNpcList, 0);
        w32(m, kPosList, 0);
        u32 first = 0;
        for (int i = 0; i < 3; ++i) {
            hgp::Run r = call(m, "sub_1E2850", {0, 0, 0, 0}, 10 + i);  // the snapshot's own RW allocator
            if (r.stopped) break;
            const u32 rec = static_cast<u32>(v0_of(r));
            CHECK(r32(m, kNpcList) == rec);
            CHECK(r32(m, rec + fbn::kNpcNext) == first);
            if (first) CHECK(r32(m, first + fbn::kNpcPrev) == rec);
            first = rec;
        }
        hgp::Run r = call(m, "sub_1E2930", {0, 0, 0, 0}, 20);
        if (!r.stopped) CHECK(r32(m, kNpcList) == 0);
    }
}

// The per-field requests of this band build their paths from their arguments (the FileExists / Request stand-ins log
// them): the NPC placement FBN (major, minor, set), the HBN hit file, the field script and the fixed floor's MAP; and
// the field-script loader copies a finished request into the field (sField +4168 / +4172), destroying the request.
TEST_CASE("game(field4 npc): the FBN / HBN / script / MAP requests and the field-script copy (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no climb_ref_17000 snapshot");
        return;
    }
    Machine& m = *mp;
    const HwCheck hw = whole_ram_check();
    struct Req {
        const char* fn;
        Args args;
        const char* path;
    };
    const Req reqs[] = {
        {"sub_1E2DA0", {51, 4, 3, 0}, "field/data/f051_004_003.FBN"},
        {"sub_1E6CB0", {51, 4, 0, 0}, "field/data/f051_004.HBN"},
        {"sub_1E7200", {51, 0, 0, 0}, "field/script/f051.bf"},
        {"sub_1E7470", {51, 4, 0, 0}, "field/map/f051_004.MAP"},
    };
    u32 seed = 1;
    for (const Req& q : reqs) {
        reset(m, base);
        write_rw_slots(m);
        w32(m, gpv(game::f4::gpv::kPacRequest), 0);
        const Case& c = find_case(q.fn);
        SiPair sp = run_pair_si(m, c.hand, c.recomp, q.args, seed++, q.fn, hw, install_field_world);
        bool asked = false;
        for (const StandInCall& k : sp.recomp->si.log) asked |= k.text == q.path || k.text == FakeCd::build_path(q.path);
        CHECK_MESSAGE(asked, q.fn << " did not ask for " << q.path);
    }
    const auto bytes = read_extracted("DATA/FIELD/SCRIPT/DUNGEONAT.BF");
    if (bytes.empty()) return;
    reset(m, base);
    write_rw_slots(m);
    w32(m, gpv(game::f4::gpv::kPacRequest), 0);
    make_loaded_node(m, kScratch, kScratch + 0x400, bytes);
    const Case& c = find_case("sub_1E7290");
    SiPair sp = run_pair_si(m, c.hand, c.recomp, {kScratch, 51, 0, 0}, seed++, c.name, hw, [](StandInWorld& w) {
        w.heap.install_all(w.si);
        w.si.install_recorder(kHCdvdDestroyFn, "H_Cdvd_Destroy", 1);
    });
    CHECK(v0_of(sp.hw) == 1);
    CHECK(guest_equals(m, r32(m, kSField + game::f4::fld::kFieldScript), bytes));
    CHECK(r32(m, kSField + game::f4::fld::kFieldScriptSize) == bytes.size());
    CHECK(sp.recomp->si.calls_to(kHCdvdDestroyFn) == 1);
}
// --- end of the field4 tests ---

#else

TEST_CASE("game(field4 npc): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
