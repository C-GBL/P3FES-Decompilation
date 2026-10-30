// Phase 5 slice libs5: CRI Sofdec SUD's tag reader, and the do-nothing functions of the kernel payload blobs at
// 0x77F568 / 0x7803A0 (0x5A1158-0x7D0000).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_5A1340_005a1340(p3fes::EEContext&);
void fn_sub_77F598_0077f598(p3fes::EEContext&);
void fn_sub_77F5F8_0077f5f8(p3fes::EEContext&);
void fn_sub_77F65C_0077f65c(p3fes::EEContext&);
void fn_sub_77F67C_0077f67c(p3fes::EEContext&);
void fn_sub_77F6B4_0077f6b4(p3fes::EEContext&);
void fn_sub_77F704_0077f704(p3fes::EEContext&);
void fn_sub_77FF10_0077ff10(p3fes::EEContext&);
void fn_sub_7803D0_007803d0(p3fes::EEContext&);
void fn_sub_7803EC_007803ec(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x005A1340 sub_5A1340 -- 64 bytes; frame 0x10: ra sp+0x0
// [sudIsTagD] SUD: true for a non-null tag record and a non-negative a1 whose byte +18 is 'D' (strncmp of one
// character with 0x7CABD8).
void sub_5A1340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005a1340
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005a134c
        charge(ctx, 2);
        cc = i64(a1) >= 0;  // the condition, before the delay slot changes it
        a1 = 0x7D0000;
        if (!cc) {
            goto L_005a1354;
        }
        // 0x005a1360
        charge(ctx, 5);
        a0 = addiu(a0, 18);
        a1 = addiu(a1, -21544);
        a2 = 1;
        jal(ctx, 0x5A1368u, gen::fn_strncmp_00524670);
        v0 = sltiu(v0, 1);
        // 0x005a1374 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_005a1354:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a1374 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0077F598 sub_77F598 -- 8 bytes; leaf frame (no stack)
// [kpTlbReturn0] Kernel payload 0x77F568 (runs at 0x80075000, never at this address): returns 0.
void sub_77F598(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0077f598
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0077F5F8 sub_77F5F8 -- 8 bytes; leaf frame (no stack)
// [kpTlbReturnM1] Kernel payload 0x77F568: returns -1.
void sub_77F5F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0077f5f8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
}

// 0x0077F65C sub_77F65C -- 8 bytes; leaf frame (no stack)
// [kpTlbReturnArg] Kernel payload 0x77F568: returns its argument.
void sub_77F65C(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0077f65c
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0077F67C sub_77F67C -- 8 bytes; leaf frame (no stack)
// [kpTlbReturnM1b] Kernel payload 0x77F568: returns -1.
void sub_77F67C(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0077f67c
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
}

// 0x0077F6B4 sub_77F6B4 -- 8 bytes; leaf frame (no stack)
// [kpTlbReturnArgB] Kernel payload 0x77F568: returns its argument.
void sub_77F6B4(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0077f6b4
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0077F704 sub_77F704 -- 8 bytes; leaf frame (no stack)
// [kpTlbReturnArgC] Kernel payload 0x77F568: returns its argument.
void sub_77F704(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0077f704
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0077FF10 sub_77FF10 -- 8 bytes; leaf frame (no stack)
// [kpExecPs2Return0] Kernel payload 0x77FBD8 (runs at 0x80074000): returns 0.
void sub_77FF10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0077ff10
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x007803D0 sub_7803D0 -- 8 bytes; leaf frame (no stack)
// [kpAlarmReturn0] Kernel payload 0x7803A0 (runs at 0x80076000): returns 0.
void sub_7803D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x007803d0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x007803EC sub_7803EC -- 8 bytes; leaf frame (no stack)
// [kpAlarmReturnArg1] Kernel payload 0x7803A0: returns its second argument.
void sub_7803EC(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x007803ec
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a1;
}

}  // namespace p3fes::game
