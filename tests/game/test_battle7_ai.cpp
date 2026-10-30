// Phase 5 pair tests for slice battle7, ai (game/src/battle/battle7_ai.cpp): the AI condition / target-selector rows (tables 0x6971B0 / 0x6975E0), their predicates and helpers, the command decode and the AI script packets. Every body
// against its recompiled body (__recomp) on random worlds and on the battle snapshots, perturbed (battle7_pairs.h: the
// whole register file and cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad,
// the BIOS window, the bus log, the stand-in call log), plus documented-rule checks against host models (below).
#include "battle7_pairs.h"

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::b7t;

namespace p3fes::recomp_gen {
void fn_sub_2C08B0_002c08b0(EEContext&);
void fn_sub_2C08B0_002c08b0__recomp(EEContext&);
void fn_sub_2C08C0_002c08c0(EEContext&);
void fn_sub_2C08C0_002c08c0__recomp(EEContext&);
void fn_sub_2C0A50_002c0a50(EEContext&);
void fn_sub_2C0A50_002c0a50__recomp(EEContext&);
void fn_sub_2C1360_002c1360(EEContext&);
void fn_sub_2C1360_002c1360__recomp(EEContext&);
void fn_sub_2C1440_002c1440(EEContext&);
void fn_sub_2C1440_002c1440__recomp(EEContext&);
void fn_sub_2C1490_002c1490(EEContext&);
void fn_sub_2C1490_002c1490__recomp(EEContext&);
void fn_sub_2C14F0_002c14f0(EEContext&);
void fn_sub_2C14F0_002c14f0__recomp(EEContext&);
void fn_sub_2C1550_002c1550(EEContext&);
void fn_sub_2C1550_002c1550__recomp(EEContext&);
void fn_sub_2C15E0_002c15e0(EEContext&);
void fn_sub_2C15E0_002c15e0__recomp(EEContext&);
void fn_sub_2C1740_002c1740(EEContext&);
void fn_sub_2C1740_002c1740__recomp(EEContext&);
void fn_sub_2C1850_002c1850(EEContext&);
void fn_sub_2C1850_002c1850__recomp(EEContext&);
void fn_sub_2C1960_002c1960(EEContext&);
void fn_sub_2C1960_002c1960__recomp(EEContext&);
void fn_sub_2C1A30_002c1a30(EEContext&);
void fn_sub_2C1A30_002c1a30__recomp(EEContext&);
void fn_sub_2C1B10_002c1b10(EEContext&);
void fn_sub_2C1B10_002c1b10__recomp(EEContext&);
void fn_sub_2C1BF0_002c1bf0(EEContext&);
void fn_sub_2C1BF0_002c1bf0__recomp(EEContext&);
void fn_sub_2C1D80_002c1d80(EEContext&);
void fn_sub_2C1D80_002c1d80__recomp(EEContext&);
void fn_sub_2C1E50_002c1e50(EEContext&);
void fn_sub_2C1E50_002c1e50__recomp(EEContext&);
void fn_sub_2C1E90_002c1e90(EEContext&);
void fn_sub_2C1E90_002c1e90__recomp(EEContext&);
void fn_sub_2C1F10_002c1f10(EEContext&);
void fn_sub_2C1F10_002c1f10__recomp(EEContext&);
void fn_sub_2C1FC0_002c1fc0(EEContext&);
void fn_sub_2C1FC0_002c1fc0__recomp(EEContext&);
void fn_sub_2C2010_002c2010(EEContext&);
void fn_sub_2C2010_002c2010__recomp(EEContext&);
void fn_sub_2C2070_002c2070(EEContext&);
void fn_sub_2C2070_002c2070__recomp(EEContext&);
void fn_sub_2C20C0_002c20c0(EEContext&);
void fn_sub_2C20C0_002c20c0__recomp(EEContext&);
void fn_sub_2C2120_002c2120(EEContext&);
void fn_sub_2C2120_002c2120__recomp(EEContext&);
void fn_sub_2C2170_002c2170(EEContext&);
void fn_sub_2C2170_002c2170__recomp(EEContext&);
void fn_sub_2C21D0_002c21d0(EEContext&);
void fn_sub_2C21D0_002c21d0__recomp(EEContext&);
void fn_sub_2C2220_002c2220(EEContext&);
void fn_sub_2C2220_002c2220__recomp(EEContext&);
void fn_sub_2C2270_002c2270(EEContext&);
void fn_sub_2C2270_002c2270__recomp(EEContext&);
void fn_sub_2C2310_002c2310(EEContext&);
void fn_sub_2C2310_002c2310__recomp(EEContext&);
void fn_sub_2C2360_002c2360(EEContext&);
void fn_sub_2C2360_002c2360__recomp(EEContext&);
void fn_sub_2C23C0_002c23c0(EEContext&);
void fn_sub_2C23C0_002c23c0__recomp(EEContext&);
void fn_sub_2C2420_002c2420(EEContext&);
void fn_sub_2C2420_002c2420__recomp(EEContext&);
void fn_sub_2C2470_002c2470(EEContext&);
void fn_sub_2C2470_002c2470__recomp(EEContext&);
void fn_sub_2C24F0_002c24f0(EEContext&);
void fn_sub_2C24F0_002c24f0__recomp(EEContext&);
void fn_sub_2C2510_002c2510(EEContext&);
void fn_sub_2C2510_002c2510__recomp(EEContext&);
void fn_sub_2C25D0_002c25d0(EEContext&);
void fn_sub_2C25D0_002c25d0__recomp(EEContext&);
void fn_sub_2C25E0_002c25e0(EEContext&);
void fn_sub_2C25E0_002c25e0__recomp(EEContext&);
void fn_sub_2C2630_002c2630(EEContext&);
void fn_sub_2C2630_002c2630__recomp(EEContext&);
void fn_sub_2C2690_002c2690(EEContext&);
void fn_sub_2C2690_002c2690__recomp(EEContext&);
void fn_sub_2C26E0_002c26e0(EEContext&);
void fn_sub_2C26E0_002c26e0__recomp(EEContext&);
void fn_sub_2C2740_002c2740(EEContext&);
void fn_sub_2C2740_002c2740__recomp(EEContext&);
void fn_sub_2C2790_002c2790(EEContext&);
void fn_sub_2C2790_002c2790__recomp(EEContext&);
void fn_sub_2C27F0_002c27f0(EEContext&);
void fn_sub_2C27F0_002c27f0__recomp(EEContext&);
void fn_sub_2C2840_002c2840(EEContext&);
void fn_sub_2C2840_002c2840__recomp(EEContext&);
void fn_sub_2C28A0_002c28a0(EEContext&);
void fn_sub_2C28A0_002c28a0__recomp(EEContext&);
void fn_sub_2C28C0_002c28c0(EEContext&);
void fn_sub_2C28C0_002c28c0__recomp(EEContext&);
void fn_sub_2C29E0_002c29e0(EEContext&);
void fn_sub_2C29E0_002c29e0__recomp(EEContext&);
void fn_sub_2C2C40_002c2c40(EEContext&);
void fn_sub_2C2C40_002c2c40__recomp(EEContext&);
void fn_sub_2C2CA0_002c2ca0(EEContext&);
void fn_sub_2C2CA0_002c2ca0__recomp(EEContext&);
void fn_sub_2C3150_002c3150(EEContext&);
void fn_sub_2C3150_002c3150__recomp(EEContext&);
void fn_sub_2C31B0_002c31b0(EEContext&);
void fn_sub_2C31B0_002c31b0__recomp(EEContext&);
void fn_sub_2C3210_002c3210(EEContext&);
void fn_sub_2C3210_002c3210__recomp(EEContext&);
void fn_sub_2C3270_002c3270(EEContext&);
void fn_sub_2C3270_002c3270__recomp(EEContext&);
void fn_sub_2C32C0_002c32c0(EEContext&);
void fn_sub_2C32C0_002c32c0__recomp(EEContext&);
void fn_sub_2C32E0_002c32e0(EEContext&);
void fn_sub_2C32E0_002c32e0__recomp(EEContext&);
void fn_sub_2C3BE0_002c3be0(EEContext&);
void fn_sub_2C3BE0_002c3be0__recomp(EEContext&);
void fn_sub_2C3CE0_002c3ce0(EEContext&);
void fn_sub_2C3CE0_002c3ce0__recomp(EEContext&);
void fn_sub_2C3E10_002c3e10(EEContext&);
void fn_sub_2C3E10_002c3e10__recomp(EEContext&);
void fn_sub_2C3E20_002c3e20(EEContext&);
void fn_sub_2C3E20_002c3e20__recomp(EEContext&);
void fn_sub_2C3E60_002c3e60(EEContext&);
void fn_sub_2C3E60_002c3e60__recomp(EEContext&);
void fn_sub_2C3EA0_002c3ea0(EEContext&);
void fn_sub_2C3EA0_002c3ea0__recomp(EEContext&);
void fn_sub_2C3EE0_002c3ee0(EEContext&);
void fn_sub_2C3EE0_002c3ee0__recomp(EEContext&);
void fn_sub_2C3F00_002c3f00(EEContext&);
void fn_sub_2C3F00_002c3f00__recomp(EEContext&);
void fn_sub_2C4000_002c4000(EEContext&);
void fn_sub_2C4000_002c4000__recomp(EEContext&);
void fn_sub_2C4040_002c4040(EEContext&);
void fn_sub_2C4040_002c4040__recomp(EEContext&);
void fn_sub_2C4080_002c4080(EEContext&);
void fn_sub_2C4080_002c4080__recomp(EEContext&);
void fn_sub_2C40C0_002c40c0(EEContext&);
void fn_sub_2C40C0_002c40c0__recomp(EEContext&);
void fn_sub_2C4100_002c4100(EEContext&);
void fn_sub_2C4100_002c4100__recomp(EEContext&);
void fn_sub_2C4140_002c4140(EEContext&);
void fn_sub_2C4140_002c4140__recomp(EEContext&);
void fn_sub_2C4180_002c4180(EEContext&);
void fn_sub_2C4180_002c4180__recomp(EEContext&);
void fn_sub_2C41C0_002c41c0(EEContext&);
void fn_sub_2C41C0_002c41c0__recomp(EEContext&);
void fn_sub_2C4200_002c4200(EEContext&);
void fn_sub_2C4200_002c4200__recomp(EEContext&);
void fn_sub_2C42C0_002c42c0(EEContext&);
void fn_sub_2C42C0_002c42c0__recomp(EEContext&);
void fn_sub_2C43A0_002c43a0(EEContext&);
void fn_sub_2C43A0_002c43a0__recomp(EEContext&);
void fn_sub_2C43E0_002c43e0(EEContext&);
void fn_sub_2C43E0_002c43e0__recomp(EEContext&);
void fn_sub_2C4420_002c4420(EEContext&);
void fn_sub_2C4420_002c4420__recomp(EEContext&);
void fn_sub_2C4460_002c4460(EEContext&);
void fn_sub_2C4460_002c4460__recomp(EEContext&);
void fn_sub_2C44A0_002c44a0(EEContext&);
void fn_sub_2C44A0_002c44a0__recomp(EEContext&);
void fn_sub_2C44E0_002c44e0(EEContext&);
void fn_sub_2C44E0_002c44e0__recomp(EEContext&);
void fn_sub_2C4520_002c4520(EEContext&);
void fn_sub_2C4520_002c4520__recomp(EEContext&);
void fn_sub_2C4560_002c4560(EEContext&);
void fn_sub_2C4560_002c4560__recomp(EEContext&);
void fn_sub_2C45A0_002c45a0(EEContext&);
void fn_sub_2C45A0_002c45a0__recomp(EEContext&);
void fn_sub_2C45E0_002c45e0(EEContext&);
void fn_sub_2C45E0_002c45e0__recomp(EEContext&);
void fn_sub_2C4620_002c4620(EEContext&);
void fn_sub_2C4620_002c4620__recomp(EEContext&);
void fn_sub_2C4660_002c4660(EEContext&);
void fn_sub_2C4660_002c4660__recomp(EEContext&);
void fn_sub_2C46A0_002c46a0(EEContext&);
void fn_sub_2C46A0_002c46a0__recomp(EEContext&);
void fn_sub_2C46E0_002c46e0(EEContext&);
void fn_sub_2C46E0_002c46e0__recomp(EEContext&);
void fn_sub_2C4720_002c4720(EEContext&);
void fn_sub_2C4720_002c4720__recomp(EEContext&);
void fn_sub_2C4760_002c4760(EEContext&);
void fn_sub_2C4760_002c4760__recomp(EEContext&);
void fn_sub_2C4820_002c4820(EEContext&);
void fn_sub_2C4820_002c4820__recomp(EEContext&);
void fn_sub_2C4860_002c4860(EEContext&);
void fn_sub_2C4860_002c4860__recomp(EEContext&);
void fn_sub_2C4A90_002c4a90(EEContext&);
void fn_sub_2C4A90_002c4a90__recomp(EEContext&);
void fn_sub_2C65D0_002c65d0(EEContext&);
void fn_sub_2C65D0_002c65d0__recomp(EEContext&);
void fn_sub_2C74E0_002c74e0(EEContext&);
void fn_sub_2C74E0_002c74e0__recomp(EEContext&);
void fn_sub_2D08E0_002d08e0(EEContext&);
void fn_sub_2D08E0_002d08e0__recomp(EEContext&);
void fn_sub_2D1660_002d1660(EEContext&);
void fn_sub_2D1660_002d1660__recomp(EEContext&);
void fn_sub_2D1C20_002d1c20(EEContext&);
void fn_sub_2D1C20_002d1c20__recomp(EEContext&);
void fn_sub_2D1D00_002d1d00(EEContext&);
void fn_sub_2D1D00_002d1d00__recomp(EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(EEContext&);
void fn_datCalcGetHp_002ffd70(EEContext&);
void fn_datCalcChkBadStatus_00300580(EEContext&);
void fn_datCalcIsDead_0030b5a0(EEContext&);
void fn_datCalcGetLevel_002ffcc0(EEContext&);
void fn_datCalcGetAffinity_00306e80(EEContext&);
void fn_btlGetMeanLevel_002d4cf0(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

const Case kCases[] = {
    {"sub_2C08B0", 0x2C08B0u, &rg::fn_sub_2C08B0_002c08b0, &rg::fn_sub_2C08B0_002c08b0__recomp, "rr"},
    {"sub_2C08C0", 0x2C08C0u, &rg::fn_sub_2C08C0_002c08c0, &rg::fn_sub_2C08C0_002c08c0__recomp, "r"},
    {"sub_2C0A50", 0x2C0A50u, &rg::fn_sub_2C0A50_002c0a50, &rg::fn_sub_2C0A50_002c0a50__recomp, "zu"},
    {"sub_2C1360", 0x2C1360u, &rg::fn_sub_2C1360_002c1360, &rg::fn_sub_2C1360_002c1360__recomp, "Ap"},
    {"sub_2C1440", 0x2C1440u, &rg::fn_sub_2C1440_002c1440, &rg::fn_sub_2C1440_002c1440__recomp, "Ap"},
    {"sub_2C1490", 0x2C1490u, &rg::fn_sub_2C1490_002c1490, &rg::fn_sub_2C1490_002c1490__recomp, "Ap"},
    {"sub_2C14F0", 0x2C14F0u, &rg::fn_sub_2C14F0_002c14f0, &rg::fn_sub_2C14F0_002c14f0__recomp, "Ap"},
    {"sub_2C1550", 0x2C1550u, &rg::fn_sub_2C1550_002c1550, &rg::fn_sub_2C1550_002c1550__recomp, "Ap"},
    {"sub_2C15E0", 0x2C15E0u, &rg::fn_sub_2C15E0_002c15e0, &rg::fn_sub_2C15E0_002c15e0__recomp, "Ap"},
    {"sub_2C1740", 0x2C1740u, &rg::fn_sub_2C1740_002c1740, &rg::fn_sub_2C1740_002c1740__recomp, "Ap"},
    {"sub_2C1850", 0x2C1850u, &rg::fn_sub_2C1850_002c1850, &rg::fn_sub_2C1850_002c1850__recomp, "Ap"},
    {"sub_2C1960", 0x2C1960u, &rg::fn_sub_2C1960_002c1960, &rg::fn_sub_2C1960_002c1960__recomp, "Ap"},
    {"sub_2C1A30", 0x2C1A30u, &rg::fn_sub_2C1A30_002c1a30, &rg::fn_sub_2C1A30_002c1a30__recomp, "Ap"},
    {"sub_2C1B10", 0x2C1B10u, &rg::fn_sub_2C1B10_002c1b10, &rg::fn_sub_2C1B10_002c1b10__recomp, "Ap"},
    {"sub_2C1BF0", 0x2C1BF0u, &rg::fn_sub_2C1BF0_002c1bf0, &rg::fn_sub_2C1BF0_002c1bf0__recomp, "Ap"},
    {"sub_2C1D80", 0x2C1D80u, &rg::fn_sub_2C1D80_002c1d80, &rg::fn_sub_2C1D80_002c1d80__recomp, "A"},
    {"sub_2C1E50", 0x2C1E50u, &rg::fn_sub_2C1E50_002c1e50, &rg::fn_sub_2C1E50_002c1e50__recomp, "Ap"},
    {"sub_2C1E90", 0x2C1E90u, &rg::fn_sub_2C1E90_002c1e90, &rg::fn_sub_2C1E90_002c1e90__recomp, "Ap"},
    {"sub_2C1F10", 0x2C1F10u, &rg::fn_sub_2C1F10_002c1f10, &rg::fn_sub_2C1F10_002c1f10__recomp, "Ap"},
    {"sub_2C1FC0", 0x2C1FC0u, &rg::fn_sub_2C1FC0_002c1fc0, &rg::fn_sub_2C1FC0_002c1fc0__recomp, "Ap"},
    {"sub_2C2010", 0x2C2010u, &rg::fn_sub_2C2010_002c2010, &rg::fn_sub_2C2010_002c2010__recomp, "Ap"},
    {"sub_2C2070", 0x2C2070u, &rg::fn_sub_2C2070_002c2070, &rg::fn_sub_2C2070_002c2070__recomp, "Ap"},
    {"sub_2C20C0", 0x2C20C0u, &rg::fn_sub_2C20C0_002c20c0, &rg::fn_sub_2C20C0_002c20c0__recomp, "Ap"},
    {"sub_2C2120", 0x2C2120u, &rg::fn_sub_2C2120_002c2120, &rg::fn_sub_2C2120_002c2120__recomp, "Ap"},
    {"sub_2C2170", 0x2C2170u, &rg::fn_sub_2C2170_002c2170, &rg::fn_sub_2C2170_002c2170__recomp, "Ap"},
    {"sub_2C21D0", 0x2C21D0u, &rg::fn_sub_2C21D0_002c21d0, &rg::fn_sub_2C21D0_002c21d0__recomp, "Ap"},
    {"sub_2C2220", 0x2C2220u, &rg::fn_sub_2C2220_002c2220, &rg::fn_sub_2C2220_002c2220__recomp, "Ap"},
    {"sub_2C2270", 0x2C2270u, &rg::fn_sub_2C2270_002c2270, &rg::fn_sub_2C2270_002c2270__recomp, "Ap"},
    {"sub_2C2310", 0x2C2310u, &rg::fn_sub_2C2310_002c2310, &rg::fn_sub_2C2310_002c2310__recomp, "Ap"},
    {"sub_2C2360", 0x2C2360u, &rg::fn_sub_2C2360_002c2360, &rg::fn_sub_2C2360_002c2360__recomp, "Ap"},
    {"sub_2C23C0", 0x2C23C0u, &rg::fn_sub_2C23C0_002c23c0, &rg::fn_sub_2C23C0_002c23c0__recomp, "A"},
    {"sub_2C2420", 0x2C2420u, &rg::fn_sub_2C2420_002c2420, &rg::fn_sub_2C2420_002c2420__recomp, "Ap"},
    {"sub_2C2470", 0x2C2470u, &rg::fn_sub_2C2470_002c2470, &rg::fn_sub_2C2470_002c2470__recomp, "Ap"},
    {"sub_2C24F0", 0x2C24F0u, &rg::fn_sub_2C24F0_002c24f0, &rg::fn_sub_2C24F0_002c24f0__recomp, "Ap"},
    {"sub_2C2510", 0x2C2510u, &rg::fn_sub_2C2510_002c2510, &rg::fn_sub_2C2510_002c2510__recomp, "A"},
    {"sub_2C25D0", 0x2C25D0u, &rg::fn_sub_2C25D0_002c25d0, &rg::fn_sub_2C25D0_002c25d0__recomp, "A"},
    {"sub_2C25E0", 0x2C25E0u, &rg::fn_sub_2C25E0_002c25e0, &rg::fn_sub_2C25E0_002c25e0__recomp, "Ap"},
    {"sub_2C2630", 0x2C2630u, &rg::fn_sub_2C2630_002c2630, &rg::fn_sub_2C2630_002c2630__recomp, "Ap"},
    {"sub_2C2690", 0x2C2690u, &rg::fn_sub_2C2690_002c2690, &rg::fn_sub_2C2690_002c2690__recomp, "Ap"},
    {"sub_2C26E0", 0x2C26E0u, &rg::fn_sub_2C26E0_002c26e0, &rg::fn_sub_2C26E0_002c26e0__recomp, "Ap"},
    {"sub_2C2740", 0x2C2740u, &rg::fn_sub_2C2740_002c2740, &rg::fn_sub_2C2740_002c2740__recomp, "Ap"},
    {"sub_2C2790", 0x2C2790u, &rg::fn_sub_2C2790_002c2790, &rg::fn_sub_2C2790_002c2790__recomp, "Ap"},
    {"sub_2C27F0", 0x2C27F0u, &rg::fn_sub_2C27F0_002c27f0, &rg::fn_sub_2C27F0_002c27f0__recomp, "Ap"},
    {"sub_2C2840", 0x2C2840u, &rg::fn_sub_2C2840_002c2840, &rg::fn_sub_2C2840_002c2840__recomp, "Ap"},
    {"sub_2C28A0", 0x2C28A0u, &rg::fn_sub_2C28A0_002c28a0, &rg::fn_sub_2C28A0_002c28a0__recomp, "Ap"},
    {"sub_2C28C0", 0x2C28C0u, &rg::fn_sub_2C28C0_002c28c0, &rg::fn_sub_2C28C0_002c28c0__recomp, "Ap"},
    {"sub_2C29E0", 0x2C29E0u, &rg::fn_sub_2C29E0_002c29e0, &rg::fn_sub_2C29E0_002c29e0__recomp, "Ap"},
    {"sub_2C2C40", 0x2C2C40u, &rg::fn_sub_2C2C40_002c2c40, &rg::fn_sub_2C2C40_002c2c40__recomp, "Ap"},
    {"sub_2C2CA0", 0x2C2CA0u, &rg::fn_sub_2C2CA0_002c2ca0, &rg::fn_sub_2C2CA0_002c2ca0__recomp, "Ap"},
    {"sub_2C3150", 0x2C3150u, &rg::fn_sub_2C3150_002c3150, &rg::fn_sub_2C3150_002c3150__recomp, "Ap"},
    {"sub_2C31B0", 0x2C31B0u, &rg::fn_sub_2C31B0_002c31b0, &rg::fn_sub_2C31B0_002c31b0__recomp, "Ap"},
    {"sub_2C3210", 0x2C3210u, &rg::fn_sub_2C3210_002c3210, &rg::fn_sub_2C3210_002c3210__recomp, "Ap"},
    {"sub_2C3270", 0x2C3270u, &rg::fn_sub_2C3270_002c3270, &rg::fn_sub_2C3270_002c3270__recomp, "A"},
    {"sub_2C32C0", 0x2C32C0u, &rg::fn_sub_2C32C0_002c32c0, &rg::fn_sub_2C32C0_002c32c0__recomp, "A"},
    {"sub_2C32E0", 0x2C32E0u, &rg::fn_sub_2C32E0_002c32e0, &rg::fn_sub_2C32E0_002c32e0__recomp, "A"},
    {"sub_2C3BE0", 0x2C3BE0u, &rg::fn_sub_2C3BE0_002c3be0, &rg::fn_sub_2C3BE0_002c3be0__recomp, "A"},
    {"sub_2C3CE0", 0x2C3CE0u, &rg::fn_sub_2C3CE0_002c3ce0, &rg::fn_sub_2C3CE0_002c3ce0__recomp, "A"},
    {"sub_2C3E10", 0x2C3E10u, &rg::fn_sub_2C3E10_002c3e10, &rg::fn_sub_2C3E10_002c3e10__recomp, "A"},
    {"sub_2C3E20", 0x2C3E20u, &rg::fn_sub_2C3E20_002c3e20, &rg::fn_sub_2C3E20_002c3e20__recomp, "Ap"},
    {"sub_2C3E60", 0x2C3E60u, &rg::fn_sub_2C3E60_002c3e60, &rg::fn_sub_2C3E60_002c3e60__recomp, "Ap"},
    {"sub_2C3EA0", 0x2C3EA0u, &rg::fn_sub_2C3EA0_002c3ea0, &rg::fn_sub_2C3EA0_002c3ea0__recomp, "Ap"},
    {"sub_2C3EE0", 0x2C3EE0u, &rg::fn_sub_2C3EE0_002c3ee0, &rg::fn_sub_2C3EE0_002c3ee0__recomp, "A"},
    {"sub_2C3F00", 0x2C3F00u, &rg::fn_sub_2C3F00_002c3f00, &rg::fn_sub_2C3F00_002c3f00__recomp, "A"},
    {"sub_2C4000", 0x2C4000u, &rg::fn_sub_2C4000_002c4000, &rg::fn_sub_2C4000_002c4000__recomp, "Ap"},
    {"sub_2C4040", 0x2C4040u, &rg::fn_sub_2C4040_002c4040, &rg::fn_sub_2C4040_002c4040__recomp, "Ap"},
    {"sub_2C4080", 0x2C4080u, &rg::fn_sub_2C4080_002c4080, &rg::fn_sub_2C4080_002c4080__recomp, "Ap"},
    {"sub_2C40C0", 0x2C40C0u, &rg::fn_sub_2C40C0_002c40c0, &rg::fn_sub_2C40C0_002c40c0__recomp, "Ap"},
    {"sub_2C4100", 0x2C4100u, &rg::fn_sub_2C4100_002c4100, &rg::fn_sub_2C4100_002c4100__recomp, "Ap"},
    {"sub_2C4140", 0x2C4140u, &rg::fn_sub_2C4140_002c4140, &rg::fn_sub_2C4140_002c4140__recomp, "Ap"},
    {"sub_2C4180", 0x2C4180u, &rg::fn_sub_2C4180_002c4180, &rg::fn_sub_2C4180_002c4180__recomp, "Ap"},
    {"sub_2C41C0", 0x2C41C0u, &rg::fn_sub_2C41C0_002c41c0, &rg::fn_sub_2C41C0_002c41c0__recomp, "Ap"},
    {"sub_2C4200", 0x2C4200u, &rg::fn_sub_2C4200_002c4200, &rg::fn_sub_2C4200_002c4200__recomp, "A"},
    {"sub_2C42C0", 0x2C42C0u, &rg::fn_sub_2C42C0_002c42c0, &rg::fn_sub_2C42C0_002c42c0__recomp, "Ap"},
    {"sub_2C43A0", 0x2C43A0u, &rg::fn_sub_2C43A0_002c43a0, &rg::fn_sub_2C43A0_002c43a0__recomp, "Ap"},
    {"sub_2C43E0", 0x2C43E0u, &rg::fn_sub_2C43E0_002c43e0, &rg::fn_sub_2C43E0_002c43e0__recomp, "Ap"},
    {"sub_2C4420", 0x2C4420u, &rg::fn_sub_2C4420_002c4420, &rg::fn_sub_2C4420_002c4420__recomp, "Ap"},
    {"sub_2C4460", 0x2C4460u, &rg::fn_sub_2C4460_002c4460, &rg::fn_sub_2C4460_002c4460__recomp, "Ap"},
    {"sub_2C44A0", 0x2C44A0u, &rg::fn_sub_2C44A0_002c44a0, &rg::fn_sub_2C44A0_002c44a0__recomp, "Ap"},
    {"sub_2C44E0", 0x2C44E0u, &rg::fn_sub_2C44E0_002c44e0, &rg::fn_sub_2C44E0_002c44e0__recomp, "Ap"},
    {"sub_2C4520", 0x2C4520u, &rg::fn_sub_2C4520_002c4520, &rg::fn_sub_2C4520_002c4520__recomp, "Ap"},
    {"sub_2C4560", 0x2C4560u, &rg::fn_sub_2C4560_002c4560, &rg::fn_sub_2C4560_002c4560__recomp, "Ap"},
    {"sub_2C45A0", 0x2C45A0u, &rg::fn_sub_2C45A0_002c45a0, &rg::fn_sub_2C45A0_002c45a0__recomp, "Ap"},
    {"sub_2C45E0", 0x2C45E0u, &rg::fn_sub_2C45E0_002c45e0, &rg::fn_sub_2C45E0_002c45e0__recomp, "Ap"},
    {"sub_2C4620", 0x2C4620u, &rg::fn_sub_2C4620_002c4620, &rg::fn_sub_2C4620_002c4620__recomp, "Ap"},
    {"sub_2C4660", 0x2C4660u, &rg::fn_sub_2C4660_002c4660, &rg::fn_sub_2C4660_002c4660__recomp, "Ap"},
    {"sub_2C46A0", 0x2C46A0u, &rg::fn_sub_2C46A0_002c46a0, &rg::fn_sub_2C46A0_002c46a0__recomp, "Ap"},
    {"sub_2C46E0", 0x2C46E0u, &rg::fn_sub_2C46E0_002c46e0, &rg::fn_sub_2C46E0_002c46e0__recomp, "Ap"},
    {"sub_2C4720", 0x2C4720u, &rg::fn_sub_2C4720_002c4720, &rg::fn_sub_2C4720_002c4720__recomp, "Ap"},
    {"sub_2C4760", 0x2C4760u, &rg::fn_sub_2C4760_002c4760, &rg::fn_sub_2C4760_002c4760__recomp, "A"},
    {"sub_2C4820", 0x2C4820u, &rg::fn_sub_2C4820_002c4820, &rg::fn_sub_2C4820_002c4820__recomp, "Ap"},
    {"sub_2C4860", 0x2C4860u, &rg::fn_sub_2C4860_002c4860, &rg::fn_sub_2C4860_002c4860__recomp, "Ap"},
    {"sub_2C4A90", 0x2C4A90u, &rg::fn_sub_2C4A90_002c4a90, &rg::fn_sub_2C4A90_002c4a90__recomp, "AAIcq"},
    {"sub_2C65D0", 0x2C65D0u, &rg::fn_sub_2C65D0_002c65d0, &rg::fn_sub_2C65D0_002c65d0__recomp, "A"},
    {"sub_2C74E0", 0x2C74E0u, &rg::fn_sub_2C74E0_002c74e0, &rg::fn_sub_2C74E0_002c74e0__recomp, ""},
    {"sub_2D08E0", 0x2D08E0u, &rg::fn_sub_2D08E0_002d08e0, &rg::fn_sub_2D08E0_002d08e0__recomp, ""},
    {"sub_2D1660", 0x2D1660u, &rg::fn_sub_2D1660_002d1660, &rg::fn_sub_2D1660_002d1660__recomp, "ARw"},
    {"sub_2D1C20", 0x2D1C20u, &rg::fn_sub_2D1C20_002d1c20, &rg::fn_sub_2D1C20_002d1c20__recomp, "S"},
    {"sub_2D1D00", 0x2D1D00u, &rg::fn_sub_2D1D00_002d1d00, &rg::fn_sub_2D1D00_002d1d00__recomp, "Abt"},
};

const Snap kSnaps[] = {{"b_5800", 16}, {"battle_ref_6150", 2}, {"b_6150", 2}, {"b_6300", 1}, {"climb_ref_17000", 1}};

}  // namespace

TEST_CASE("game(battle7 ai): every body equals its recompiled body on random worlds") {
    run_random(kCases, std::size(kCases), 24, "battle7 ai");
}

TEST_CASE("game(battle7 ai): every body on the battle snapshots, perturbed") {
    run_snapshots(kCases, std::size(kCases), kSnaps, std::size(kSnaps), "battle7 ai");
}

namespace {
// Host models of the AI rows over a real battle (b_5800, perturbed): the DatUnit getters run as oracles (datCalcGetMaxHp,
// datCalcChkBadStatus, datCalcIsDead, datCalcGetLevel, datCalcGetAffinity, btlGetMeanLevel: other slices' hand-written
// functions, each paired with its own original); the rules themselves -- which units count, which side, the
// comparisons -- are written here from the instructions' documented meaning.
struct AiWorld {
    Machine& m;
    u64 call(Fn f, u64 a0, u64 a1 = 0) { return v0_of(solo(m, f, {a0, a1, 0, 0})); }
    u32 dat_of(u32 act) { return ld32(m, ld32(m, act + b3::act::kUnit) + b3::unit::kDat); }
    u8 side_of(u32 act) { return ld8(m, ld32(m, act + b3::act::kUnit) + b3::unit::kSide); }
    u16 id_of(u32 act) { return ld16(m, ld32(m, act + b3::act::kUnit) + b3::unit::kId); }
    u32 maxhp(u32 d) { return static_cast<u16>(call(&rg::fn_datCalcGetMaxHp_002ffdf0, sx(d))); }
    u32 hp(u32 d) { return ld16(m, d + b3::dat::kHp); }
    bool chk(u32 d, u32 mask) { return call(&rg::fn_datCalcChkBadStatus_00300580, sx(d), mask) != 0; }
    bool dead(u32 d) { return call(&rg::fn_datCalcIsDead_0030b5a0, sx(d), 0) != 0; }
    u32 level(u32 d) { return static_cast<u8>(call(&rg::fn_datCalcGetLevel_002ffcc0, sx(d))); }
    u32 affinity(u32 d, u32 e) { return static_cast<u32>(call(&rg::fn_datCalcGetAffinity_00306e80, sx(d), e)); }
    // The combatants: gBtl's action list, active (+26 bit 0) and placed (bit 3).
    std::vector<u32> combatants() {
        std::vector<u32> v;
        const u32 btl = ld32(m, kGBtlSlot);
        for (u32 a = ld32(m, btl + b3::gbtl::kActionList), n = 0; in_ram(a) && n < 32; a = ld32(m, a + b3::act::kNext), ++n)
            if ((ld16(m, a + b3::act::kFlags2) & 9) == 9) v.push_back(a);
        return v;
    }
    // btlAIAnyUnit with no filters: a combatant of the side mask, alive when the status mask has the dead bit, without
    // the masked statuses, that satisfies the predicate.
    template <class P>
    bool any(u32 side_mask, u32 status_mask, P pred) {
        for (u32 a : combatants()) {
            if (!(side_mask & (1u << side_of(a)))) continue;
            const u32 d = dat_of(a);
            if ((status_mask & 0x80000u) && dead(d)) continue;
            if (chk(d, status_mask)) continue;
            if (pred(a)) return true;
        }
        return false;
    }
};
}  // namespace

TEST_CASE("game(battle7 ai): the AI rows follow the documented rules") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    // (1) the tables: each row of the condition table 0x6971B0 (12-byte rows) and the target table 0x6975E0 (8-byte
    //     rows) points at the function this slice names after the row's string.
    {
        const std::pair<u32, u32> kCond[] = {{3, 0x2C1440u}, {4, 0x2C1490u}, {5, 0x2C14F0u}, {6, 0x2C1550u}, {8, 0x2C15E0u},
                                             {12, 0x2C1740u}, {14, 0x2C1850u}, {15, 0x2C1960u}, {16, 0x2C1A30u}, {17, 0x2C1B10u},
                                             {18, 0x2C1BF0u}, {20, 0x2C1D80u}, {23, 0x2C1E50u}, {24, 0x2C1E90u}, {26, 0x2C1F10u},
                                             {28, 0x2C1FC0u}, {29, 0x2C2010u}, {30, 0x2C2070u}, {31, 0x2C20C0u}, {32, 0x2C2120u},
                                             {33, 0x2C2170u}, {34, 0x2C21D0u}, {35, 0x2C2220u}, {36, 0x2C2270u}, {38, 0x2C2310u},
                                             {39, 0x2C2360u}, {40, 0x2C23C0u}, {41, 0x2C2420u}, {42, 0x2C2470u}, {44, 0x2C24F0u},
                                             {45, 0x2C2510u}, {46, 0x2C25D0u}, {47, 0x2C25E0u}, {54, 0x2C2840u}, {55, 0x2C28A0u},
                                             {56, 0x2C28C0u}, {57, 0x2C29E0u}, {60, 0x2C2C40u}, {61, 0x2C2CA0u}, {64, 0x2C3150u},
                                             {65, 0x2C31B0u}, {66, 0x2C3210u}, {67, 0x2C3270u}, {68, 0x2C32C0u}, {69, 0x2C32E0u}};
        for (const auto& [row, fn] : kCond) {
            INFO("condition row " << row);
            CHECK(ld32(*m, b7::kAiCondTable + 12u * row) == fn);
            ++checks;
        }
        const std::pair<u32, u32> kTgt[] = {{1, 0x2C3BE0u}, {2, 0x2C3CE0u}, {3, 0x2C3E10u}, {4, 0x2C3E20u}, {5, 0x2C3E60u},
                                            {6, 0x2C3EA0u}, {7, 0x2C3EE0u}, {8, 0x2C3F00u}, {9, 0x2C4000u}, {16, 0x2C41C0u},
                                            {17, 0x2C4200u}, {18, 0x2C42C0u}, {19, 0x2C43A0u}, {20, 0x2C43E0u}, {21, 0x2C4420u},
                                            {28, 0x2C45E0u}, {29, 0x2C4620u}, {32, 0x2C46E0u}, {33, 0x2C4720u}, {34, 0x2C4760u},
                                            {35, 0x2C4820u}, {36, 0x2C4860u}};
        for (const auto& [row, fn] : kTgt) {
            INFO("target row " << row);
            CHECK(ld32(*m, b7::kAiTargetTable + 8u * row) == fn);
            ++checks;
        }
    }
    // (2) the conditions over b_5800, perturbed (statuses, HP, unit ids, turns, one-more), for every action and a
    //     spread of parameters, against the host models.
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: extracted/_ours/b_5800/eeMemory.bin not found");
        return;
    }
    std::mt19937 rng{0xB7A1u};
    AiWorld w{*m};
    int true_seen = 0;
    for (int round = 0; round < 24; ++round) {
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        const Objects o = objects_of(*m);
        if (o.acts.empty()) break;
        perturb(*m, o, rng);
        for (u32 a : o.acts) {
            const u8 side = w.side_of(a);
            const u32 own = 1u << side, other = 1u << (side == 0 ? 1 : 0);
            const u32 d = w.dat_of(a);
            static const u32 kParams[] = {0, 10, 25, 50, 75, 100, 1, 2, 3, 5, 9};
            for (u32 p : kParams) {
                auto hp_le = [&](u32 x) { const u32 dd = w.dat_of(x); return u64{w.maxhp(dd)} * p >= 100u * u64{w.hp(dd)}; };
                auto hp_ge = [&](u32 x) { const u32 dd = w.dat_of(x); return 100u * u64{w.hp(dd)} >= u64{w.maxhp(dd)} * p; };
                INFO("round " << round << " action " << hex64(a) << " side " << int(side) << " param " << p);
                const bool frhp = w.any(own, 0x80000u, hp_le);
                CHECK((w.call(&rg::fn_sub_2C1440_002c1440, sx(a), p) != 0) == frhp);
                CHECK((w.call(&rg::fn_sub_2C1490_002c1490, sx(a), p) != 0) == w.any(other, 0x80000u, hp_le));
                CHECK((w.call(&rg::fn_sub_2C14F0_002c14f0, sx(a), p) != 0) == w.any(other, 0x80000u, hp_ge));
                CHECK((w.call(&rg::fn_sub_2C1550_002c1550, sx(a), p) != 0) == (w.level(d) >= p));
                CHECK((w.call(&rg::fn_sub_2C24F0_002c24f0, sx(a), p) != 0) == (u64{ld32(*m, a + b3::act::kTurnsTaken)} >= p));
                CHECK((w.call(&rg::fn_sub_2C28A0_002c28a0, sx(a), p) != 0) == (w.id_of(a) == p));
                // FRID / ENID: a living ally (not the action itself) / a living unit of the other side with the id
                bool frid = false, enid = false;
                for (u32 x : w.combatants()) {
                    const u32 dx = w.dat_of(x);
                    if (w.chk(dx, 0x80000u) || w.id_of(x) != p) continue;
                    if (x != a && w.side_of(x) == side) frid = true;
                    if (w.side_of(x) == (side == 0 ? 1 : 0)) enid = true;
                }
                CHECK((w.call(&rg::fn_sub_2C1960_002c1960, sx(a), p) != 0) == frid);
                CHECK((w.call(&rg::fn_sub_2C1A30_002c1a30, sx(a), p) != 0) == enid);
                // FRALLHP / ENALLHP: the living units' summed HP against their summed max HP
                for (u32 which = 0; which < 2; ++which) {
                    u64 sum = 0, sum_max = 0;
                    for (u32 x : w.combatants()) {
                        if (!((which ? other : own) & (1u << w.side_of(x)))) continue;
                        const u32 dx = w.dat_of(x);
                        if (w.dead(dx)) continue;
                        sum += static_cast<u16>(w.call(&rg::fn_datCalcGetHp_002ffd70, sx(dx)));
                        sum_max += w.maxhp(dx);
                    }
                    const Fn f = which ? &rg::fn_sub_2C29E0_002c29e0 : &rg::fn_sub_2C28C0_002c28c0;
                    CHECK((w.call(f, sx(a), p) != 0) == (sum_max * p >= 100u * sum));
                }
                checks += 10;
                true_seen += frhp ? 1 : 0;
            }
            // the status / affinity rows over the statuses and the elements
            static const u32 kStatus[] = {0x1u, 0x2u, 0x4u, 0x8u, 0x10u, 0x20u, 0x40u, 0x100u, 0x200u, 0x80000u, 0x100000u};
            for (u32 st : kStatus) {
                INFO("action " << hex64(a) << " status " << hex64(st));
                bool all = true;  // ENBAD_ALL: every living unit of the other side has it
                for (u32 x : w.combatants()) {
                    if (!(other & (1u << w.side_of(x)))) continue;
                    const u32 dx = w.dat_of(x);
                    if (!w.dead(dx) && !w.chk(dx, st)) all = false;
                }
                CHECK((w.call(&rg::fn_sub_2C1850_002c1850, sx(a), st) != 0) == all);
                const u32 mask = (st & 0x80000u) ? 0u : 0x80000u;  // FRBAD: dead units count only when asked for
                CHECK((w.call(&rg::fn_sub_2C1740_002c1740, sx(a), st) != 0) ==
                      w.any(own, mask, [&](u32 x) { return w.chk(w.dat_of(x), st); }));
                checks += 2;
            }
            for (u32 e = 0; e < 11; ++e) {
                INFO("action " << hex64(a) << " element " << e);
                const u32 aff = w.affinity(d, e);
                CHECK((w.call(&rg::fn_sub_2C1E50_002c1e50, sx(a), e) != 0) == ((aff & b7::kAffinityDrain) != 0));
                CHECK((w.call(&rg::fn_sub_2C1E90_002c1e90, sx(a), e) != 0) == ((aff & b7::kAffinityNull) != 0));
                auto has = [&](u32 bit) { return [&, bit](u32 x) { return (w.affinity(w.dat_of(x), e) & bit) != 0; }; };
                CHECK((w.call(&rg::fn_sub_2C1FC0_002c1fc0, sx(a), e) != 0) == w.any(own, 0x80000u, has(b7::kAffinityDrain)));
                CHECK((w.call(&rg::fn_sub_2C20C0_002c20c0, sx(a), e) != 0) == w.any(other, 0x80000u, has(b7::kAffinityNull)));
                CHECK((w.call(&rg::fn_sub_2C2170_002c2170, sx(a), e) != 0) == w.any(other, 0x80000u, has(b7::kAffinityWeak)));
                CHECK((w.call(&rg::fn_sub_2C27F0_002c27f0, sx(a), e) != 0) == w.any(own, 0x180000u, has(b7::kAffinityWeak)));
                checks += 6;
            }
            // the flag rows, the constant rows, MINE
            const u16 dflags = ld16(*m, d + b3::dat::kFlags);
            CHECK((w.call(&rg::fn_sub_2C32C0_002c32c0, sx(a)) != 0) == ((dflags & 0x10) == 0));
            CHECK((w.call(&rg::fn_sub_2C32E0_002c32e0, sx(a)) != 0) == ((dflags & 0x20) == 0));
            CHECK((w.call(&rg::fn_sub_2C25D0_002c25d0, sx(a)) != 0) == (ld8(*m, a + b3::act::kOneMore) != 0));
            CHECK(w.call(&rg::fn_sub_2C1D80_002c1d80, sx(a)) == 0);
            CHECK(w.call(&rg::fn_sub_2C3E10_002c3e10, sx(a)) == 0);
            CHECK(w.call(&rg::fn_sub_2C3EE0_002c3ee0, sx(a)) == 1);
            CHECK(ld32(*m, a + b3::act::kTargets) == a);
            CHECK(ld16(*m, a + b3::act::kTargetCount) == 1);
            checks += 8;
        }
    }
    MESSAGE("battle7 ai rules: " << checks << " checks (FRHP true in " << true_seen << ")");
}

#else

TEST_CASE("game(battle7 ai): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
