// Field (exploration) layer leaves, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/26_field.md; names from
// symbols/deltas/field.sym, IDA names since master update #4). Phase 5: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_field.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: the guest::enter/charge lines mirror the `ctx.cycles += N` blocks of
// recomp/generated/fn_0006..fn_0009 on the executed path; guest::backedge stands where the generated loop has its
// back-edge check (the test block comes first in every loop here, so the check runs before every iteration).
//
// Registers: every function leaves each GPR / FPR / ACC / FCR31 bit it writes holding what the original leaves there,
// scratch registers included (the wave-6 lesson: callers' frames can capture them). Where the original keeps a
// value in a register across blocks, the local is named after that register. $gp is read from the register.
// Floats are EE singles as bit patterns through p3fes/ee/fpu.h (round toward zero, no denormals, DIV.S to nearest).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 8 of the 15 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 5, $v0 2, frame/spills 1); each keeps
// the notes of its earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/field.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::game {

namespace {

namespace fpu = ee::fpu;
using ee::core::sext32;
using namespace fld;

void set(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
// lw: the word sign-extended to 64 bits, as the register holds it.
u64 lw(const EEContext& ctx, u32 va) { return sext32(guest::load<u32>(ctx, va)); }
// The address `off($gp)`.
u32 gp_addr(const EEContext& ctx, s32 off) { return ee::core::gpr32(ctx, GPR_GP) + static_cast<u32>(off); }
// addu / sll: 32-bit results, sign-extended.
u64 addu(u64 a, u64 b) { return ee::core::add32(a, b); }
u64 sll(u64 a, unsigned sa) { return sext32(static_cast<u32>(a) << sa); }
u64 sltiu(u64 a, s32 imm) { return a < static_cast<u64>(static_cast<s64>(imm)) ? 1 : 0; }

// The four accessors of the dungeon work: `lw $v0, gp-0x4A88` (the task), then work->field or 0.
// Blocks 3 + (2 | 3) + 2 cycles.
s32 dungeon_word(EEContext& ctx, u32 offset) {
    guest::enter(ctx, 3);
    const u64 task = lw(ctx, gp_addr(ctx, kGpDungeonTask));
    u64 v0 = task;
    if (task != 0) {
        guest::charge(ctx, 2);
        v0 = lw(ctx, static_cast<u32>(task) + kTaskWork);
        v0 = lw(ctx, static_cast<u32>(v0) + offset);
    } else {
        guest::charge(ctx, 3);
        v0 = 0;
    }
    guest::charge(ctx, 2);
    set(ctx, GPR_V0, v0);
    return static_cast<s32>(v0);
}

}  // namespace

// 0x1B9120 K_Field_Get: &sField (`lui` + `addiu`).
u32 K_Field_Get(EEContext& ctx) {
    guest::enter(ctx, 4);
    set(ctx, GPR_V0, sext32(kField));
    return kField;
}

// 0x1B9130 K_Fld_GetPhase: the word at gp-0x4AA4 (0 loading, 3 scene loaded, 1 setting up, 2 running;
// written by K_Field_UpdateFieldRootTask 0x1B9480).
s32 K_Fld_GetPhase(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u64 v0 = lw(ctx, gp_addr(ctx, kGpPhase));
    set(ctx, GPR_V0, v0);
    return static_cast<s32>(v0);
}

// 0x001BAB20 K_Field_GetMajorId -- 16 bytes; leaf frame (no stack)
// 0x1BAB20 K_Field_GetMajorId(root task): the u16 major field id of the root work.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_Field_GetMajorId(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001bab20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lhu(v0, v0, 16);
}

// 0x001BAB30 K_Field_GetMinorId -- 16 bytes; leaf frame (no stack)
// 0x1BAB30 K_Field_GetMinorId(root task): the u16 minor field id.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_Field_GetMinorId(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001bab30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lhu(v0, v0, 18);
}

// 0x1BFF20 K_FldDungeon_GetCurrentFloor: dungeon work +4, 0 without a dungeon task.
s32 K_FldDungeon_GetCurrentFloor(EEContext& ctx) { return dungeon_word(ctx, kDngFloor); }

// 0x1C0040 K_FldDungeon_GetFloorKind: dungeon work +40 (sub_1BF340's random floor kind 0..4), 0 without.
s32 K_FldDungeon_GetFloorKind(EEContext& ctx) { return dungeon_word(ctx, kDngFloorKind); }

// 0x1BFF50 K_FldDungeon_IsCurrentFloorExplorable: 2 <= floor < 400, unsigned on the sign-extended floor
// (a negative floor is not explorable). The floor stays in $v1, the second test in $at.
u32 K_FldDungeon_IsCurrentFloorExplorable(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u64 task = lw(ctx, gp_addr(ctx, kGpDungeonTask));
    u64 v0 = task;
    u64 v1;
    if (task != 0) {
        guest::charge(ctx, 2);
        v0 = lw(ctx, static_cast<u32>(task) + kTaskWork);
        v1 = lw(ctx, static_cast<u32>(v0) + kDngFloor);
    } else {
        guest::charge(ctx, 3);
        v1 = 0;
    }
    set(ctx, GPR_V1, v1);
    guest::charge(ctx, 3);
    v0 = sltiu(v1, 2);
    if (v0 != 0) {
        guest::charge(ctx, 1);
        v0 = 0;
    } else {
        guest::charge(ctx, 3);
        const u64 at = sltiu(v1, static_cast<s32>(kExplorableFloorEnd));
        set(ctx, GPR_AT, at);
        if (at == 0) {
            guest::charge(ctx, 1);
            v0 = 0;
        } else {
            guest::charge(ctx, 3);
            v0 = 1;
        }
    }
    guest::charge(ctx, 2);
    set(ctx, GPR_V0, v0);
    return static_cast<u32>(v0);
}

// 0x1BFFA0 K_FldDungeon_GetCurrentFloorData: &floors[floor] (dungeon work +32 = gFldDngFloorsData
// 0x867F60, 16-byte entries {u16 major, u16 minor, u16, u8, u8, u32 flags, u8 block script, u8 EPL, ..}), 0 without.
// Leaves the work in $a0 and floor * 16 in $v1.
u32 K_FldDungeon_GetCurrentFloorData(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u64 task = lw(ctx, gp_addr(ctx, kGpDungeonTask));
    u64 v0 = task;
    if (task != 0) {
        guest::charge(ctx, 5);
        const u64 a0 = lw(ctx, static_cast<u32>(task) + kTaskWork);
        const u64 v1 = sll(lw(ctx, static_cast<u32>(a0) + kDngFloor), 4);
        v0 = addu(lw(ctx, static_cast<u32>(a0) + kDngFloorTable), v1);
        set(ctx, GPR_A0, a0);
        set(ctx, GPR_V1, v1);
    } else {
        guest::charge(ctx, 3);
        v0 = 0;
    }
    guest::charge(ctx, 2);
    set(ctx, GPR_V0, v0);
    return static_cast<u32>(v0);
}

// 0x1A0250 K_Scene_IsRandomFloor: the scene record (gp-0x57B0 -> {s32 major, s32 minor}) is a randomly
// generated Tartarus floor: major 21..28 or 41..48 with minor 0. Signed compares; the record pointer stays in $a0,
// the major in $v1, the range tests in $v0/$at.
u32 K_Scene_IsRandomFloor(EEContext& ctx) {
    guest::enter(ctx, 5);
    const u64 a0 = lw(ctx, gp_addr(ctx, kGpSceneIds));
    const u64 v1 = lw(ctx, static_cast<u32>(a0));
    set(ctx, GPR_A0, a0);
    set(ctx, GPR_V1, v1);
    const s64 major = static_cast<s64>(v1);
    bool yes = false;
    bool decided = false;
    u64 v0 = major < 21 ? 1 : 0;
    if (v0 == 0) {
        guest::charge(ctx, 3);
        const u64 at = major < 29 ? 1 : 0;
        set(ctx, GPR_AT, at);
        if (at != 0) {
            guest::charge(ctx, 3);
            v0 = lw(ctx, static_cast<u32>(a0) + 4);
            if (v0 == 0) {
                yes = true;
                decided = true;
            }
        }
    }
    if (!decided) {
        guest::charge(ctx, 3);
        v0 = major < 41 ? 1 : 0;
        if (v0 == 0) {
            guest::charge(ctx, 3);
            const u64 at = major < 49 ? 1 : 0;
            set(ctx, GPR_AT, at);
            if (at != 0) {
                guest::charge(ctx, 3);
                v0 = lw(ctx, static_cast<u32>(a0) + 4);
                yes = v0 == 0;
            }
        }
    }
    if (yes) {
        guest::charge(ctx, 3);
        v0 = 1;
    } else {
        guest::charge(ctx, 1);
        v0 = 0;
    }
    guest::charge(ctx, 2);
    set(ctx, GPR_V0, v0);
    return static_cast<u32>(v0);
}

// 0x001AAAD0 K_FldFrame_IsPointInTriangle -- 832 bytes; leaf frame (no stack)
// 0x1AAAD0 K_FldFrame_IsPointInTriangle(point, verts[3] (pointers to f32[3]), normal): the crossing-number
// test in the plane the normal's largest component drops (ties drop x, then y): for each edge (v[j], v[i]) with
// j = the previous vertex, i = 0..2, an edge that straddles the point's s coordinate (v[i].s <= p.s < v[j].s or
// v[j].s <= p.s < v[i].s) toggles the result when p.u < the edge's u at p.s. (s, u) = (y, z) for an x-dominant
// normal, (z, x) for y-dominant (the floor case: K_FldEvent_FindFldHitAt passes (0, 1, 0)), (y, x) for z-dominant.
// Registers as the original leaves them: $v0 result, $v1 the last j (2), $a2 0 (the loop test), $a3 3, $f0-$f5.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_IsPointInTriangle(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::abs_s, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::c_lt_s,
          hg::charge, hg::cond, hg::div_s, hg::enter, hg::lw, hg::lwc1, hg::mul_s, hg::sll, hg::slti, hg::sltu,
          hg::sub_s;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x001aaad0
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0;
    lwc1(f0, a2, 0);
    abs_s(f2, f0);
    lwc1(f0, a2, 4);
    abs_s(f1, f0);
    lwc1(f0, a2, 8);
    abs_s(f0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x001aab1c
        charge(ctx, 3);
        c_le_s(f1, f2);
        if (cond(ctx)) {
            // 0x001aab34
            charge(ctx, 1);
            a3 = 0;
        } else {
            // 0x001aab28
            charge(ctx, 3);
            a3 = 1;
        }
    } else {
        // 0x001aaaf8
        charge(ctx, 3);
        c_le_s(f0, f2);
        if (cond(ctx)) {
            // 0x001aab10
            charge(ctx, 1);
            a3 = 0;
        } else {
            // 0x001aab04
            charge(ctx, 3);
            a3 = 2;
        }
        // 0x001aab14
        charge(ctx, 2);
    }
    // 0x001aab38
    charge(ctx, 4);
    v1 = 0x7FFF0000;
    v1 = v1 | 0xFFFF;
    if (a3 != v1) {
        // 0x001aab48
        charge(ctx, 3);
        v1 = 2;
        if (a3 == v1) {
            // 0x001aad30
            charge(ctx, 4);
            a3 = 0;
            lwc1(f5, a0, 4);
            for (;;) {
                // 0x001aadfc
                charge(ctx, 3);
                a2 = slti(a3, 3);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001aad40
                charge(ctx, 7);
                a2 = sll(a3, 2);
                a2 = addu(a1, a2);
                lw(a2, a2, 0);
                lwc1(f0, a2, 4);
                c_le_s(f0, f5);
                if (cond(ctx)) {
                    // 0x001aad5c
                    charge(ctx, 7);
                    a2 = sll(v1, 2);
                    a2 = addu(a1, a2);
                    lw(a2, a2, 0);
                    lwc1(f4, a2, 4);
                    c_lt_s(f5, f4);
                    if (!cond(ctx)) {
                        goto L_001aad78;
                    }
                L_001aada0:
                    charge(ctx, 19);
                    a2 = sll(a3, 2);
                    a2 = addu(a1, a2);
                    lw(a2, a2, 0);
                    lwc1(f3, a2, 4);
                    v1 = sll(v1, 2);
                    v1 = addu(a1, v1);
                    lw(v1, v1, 0);
                    lwc1(f2, a2, 0);
                    sub_s(f1, f5, f3);
                    lwc1(f0, v1, 0);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    sub_s(f0, f4, f3);
                    div_s(f0, f1, f0);
                    add_s(f1, f2, f0);
                    lwc1(f0, a0, 0);
                    c_lt_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x001aadec
                        charge(ctx, 2);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                    }
                    goto L_001aadf4;
                }
            L_001aad78:
                charge(ctx, 7);
                a2 = sll(v1, 2);
                a2 = addu(a1, a2);
                lw(a2, a2, 0);
                lwc1(f4, a2, 4);
                c_le_s(f4, f5);
                if (cond(ctx)) {
                    // 0x001aad94
                    charge(ctx, 3);
                    c_lt_s(f5, f0);
                    if (cond(ctx)) {
                        goto L_001aada0;
                    }
                }
            L_001aadf4:
                charge(ctx, 2);
                v1 = a3;
                a3 = addiu(a3, 1);
            }
        } else {
            // 0x001aab54
            charge(ctx, 3);
            a2 = 1;
            if (a3 == a2) {
                // 0x001aac50
                charge(ctx, 4);
                a3 = 0;
                lwc1(f5, a0, 8);
                for (;;) {
                    // 0x001aad1c
                    charge(ctx, 3);
                    a2 = slti(a3, 3);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001aac60
                    charge(ctx, 7);
                    a2 = sll(a3, 2);
                    a2 = addu(a1, a2);
                    lw(a2, a2, 0);
                    lwc1(f0, a2, 8);
                    c_le_s(f0, f5);
                    if (cond(ctx)) {
                        // 0x001aac7c
                        charge(ctx, 7);
                        a2 = sll(v1, 2);
                        a2 = addu(a1, a2);
                        lw(a2, a2, 0);
                        lwc1(f4, a2, 8);
                        c_lt_s(f5, f4);
                        if (!cond(ctx)) {
                            goto L_001aac98;
                        }
                    L_001aacc0:
                        charge(ctx, 19);
                        a2 = sll(a3, 2);
                        a2 = addu(a1, a2);
                        lw(a2, a2, 0);
                        lwc1(f3, a2, 8);
                        v1 = sll(v1, 2);
                        v1 = addu(a1, v1);
                        lw(v1, v1, 0);
                        lwc1(f2, a2, 0);
                        sub_s(f1, f5, f3);
                        lwc1(f0, v1, 0);
                        sub_s(f0, f0, f2);
                        mul_s(f1, f1, f0);
                        sub_s(f0, f4, f3);
                        div_s(f0, f1, f0);
                        add_s(f1, f2, f0);
                        lwc1(f0, a0, 0);
                        c_lt_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x001aad0c
                            charge(ctx, 2);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                        }
                        goto L_001aad14;
                    }
                L_001aac98:
                    charge(ctx, 7);
                    a2 = sll(v1, 2);
                    a2 = addu(a1, a2);
                    lw(a2, a2, 0);
                    lwc1(f4, a2, 8);
                    c_le_s(f4, f5);
                    if (cond(ctx)) {
                        // 0x001aacb4
                        charge(ctx, 3);
                        c_lt_s(f5, f0);
                        if (cond(ctx)) {
                            goto L_001aacc0;
                        }
                    }
                L_001aad14:
                    charge(ctx, 2);
                    v1 = a3;
                    a3 = addiu(a3, 1);
                }
                // 0x001aad28
                charge(ctx, 2);
            } else {
                // 0x001aab60
                charge(ctx, 2);
                if (a3 == 0) {
                    // 0x001aab70
                    charge(ctx, 4);
                    a3 = 0;
                    lwc1(f5, a0, 4);
                    for (;;) {
                        // 0x001aac3c
                        charge(ctx, 3);
                        a2 = slti(a3, 3);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001aab80
                        charge(ctx, 7);
                        a2 = sll(a3, 2);
                        a2 = addu(a1, a2);
                        lw(a2, a2, 0);
                        lwc1(f0, a2, 4);
                        c_le_s(f0, f5);
                        if (cond(ctx)) {
                            // 0x001aab9c
                            charge(ctx, 7);
                            a2 = sll(v1, 2);
                            a2 = addu(a1, a2);
                            lw(a2, a2, 0);
                            lwc1(f4, a2, 4);
                            c_lt_s(f5, f4);
                            if (!cond(ctx)) {
                                goto L_001aabb8;
                            }
                        L_001aabe0:
                            charge(ctx, 19);
                            a2 = sll(a3, 2);
                            a2 = addu(a1, a2);
                            lw(a2, a2, 0);
                            lwc1(f3, a2, 4);
                            v1 = sll(v1, 2);
                            v1 = addu(a1, v1);
                            lw(v1, v1, 0);
                            lwc1(f2, a2, 8);
                            lwc1(f0, v1, 8);
                            sub_s(f1, f0, f2);
                            sub_s(f0, f5, f3);
                            mul_s(f1, f0, f1);
                            sub_s(f0, f4, f3);
                            div_s(f0, f1, f0);
                            add_s(f1, f2, f0);
                            lwc1(f0, a0, 8);
                            c_lt_s(f0, f1);
                            if (cond(ctx)) {
                                // 0x001aac2c
                                charge(ctx, 2);
                                v0 = sltu(0, v0);
                                v0 = v0 ^ 0x1;
                            }
                            goto L_001aac34;
                        }
                    L_001aabb8:
                        charge(ctx, 7);
                        a2 = sll(v1, 2);
                        a2 = addu(a1, a2);
                        lw(a2, a2, 0);
                        lwc1(f4, a2, 4);
                        c_le_s(f4, f5);
                        if (cond(ctx)) {
                            // 0x001aabd4
                            charge(ctx, 3);
                            c_lt_s(f5, f0);
                            if (cond(ctx)) {
                                goto L_001aabe0;
                            }
                        }
                    L_001aac34:
                        charge(ctx, 2);
                        v1 = a3;
                        a3 = addiu(a3, 1);
                    }
                    // 0x001aac48
                    charge(ctx, 2);
                } else {
                    // 0x001aab68
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x001aae08 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001AAE10 K_FldFrame_ClosestPointOnSegment -- 284 bytes; leaf frame (no stack)
// 0x1AAE10 K_FldFrame_ClosestPointOnSegment(out, p, a, b): with d = b - a and t' = p.d - a.d (two MADD
// chains through ACC, in the compiled order y, x, z), out = a when t' <= 0, out = a + d * (t' / |d|^2) when t' < |d|^2
// (|d|^2 = 0 + dy^2 + dx^2 ... as ((0 + dy*dy) + dx*dx), then + dz*dz, through ACC), else b. The product is stored to
// `out` and read back before the add, as the original does (so an `out` that aliases an input behaves the same).
// Returns `out` (a copy of the whole $a0). Leaves $f0-$f9 and ACC as the original.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_ClosestPointOnSegment(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::c_le_s, hg::c_lt_s, hg::charge, hg::cond, hg::div_s,
          hg::enter, hg::lwc1, hg::madd_s, hg::madda_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::sub_s, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x001aae10
    enter(ctx, 23);  // entry check point + this block's cycles
    lwc1(f9, a2, 0);
    lwc1(f0, a3, 0);
    sub_s(f8, f0, f9);
    lwc1(f7, a2, 4);
    lwc1(f0, a3, 4);
    sub_s(f6, f0, f7);
    lwc1(f5, a2, 8);
    lwc1(f0, a3, 8);
    sub_s(f4, f0, f5);
    lwc1(f3, a1, 8);
    lwc1(f1, a1, 0);
    lwc1(f0, a1, 4);
    mula_s(f0, f6);
    mtc1(zero, f2);
    madda_s(f1, f8);
    madd_s(f1, f3, f4);
    mula_s(f7, f6);
    madda_s(f9, f8);
    madd_s(f0, f5, f4);
    sub_s(f1, f1, f0);
    c_le_s(f1, f2);
    if (!cond(ctx)) {
        // 0x001aae8c
        charge(ctx, 8);
        mul_s(f0, f6, f6);
        adda_s(f2, f0);
        madd_s(f0, f8, f8);
        adda_s(f2, f0);
        madd_s(f0, f4, f4);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x001aaf08
            charge(ctx, 6);
            lwc1(f2, a3, 0);
            lwc1(f1, a3, 4);
            lwc1(f0, a3, 8);
            swc1(f2, a0, 0);
            swc1(f1, a0, 4);
            swc1(f0, a0, 8);
        } else {
            // 0x001aaeac
            charge(ctx, 23);
            div_s(f1, f1, f0);
            mul_s(f0, f8, f1);
            swc1(f0, a0, 0);
            mul_s(f0, f6, f1);
            swc1(f0, a0, 4);
            mul_s(f0, f4, f1);
            swc1(f0, a0, 8);
            lwc1(f1, a0, 0);
            lwc1(f0, a2, 0);
            add_s(f0, f1, f0);
            swc1(f0, a0, 0);
            lwc1(f1, a2, 4);
            lwc1(f0, a0, 4);
            add_s(f0, f0, f1);
            swc1(f0, a0, 4);
            lwc1(f1, a2, 8);
            lwc1(f0, a0, 8);
            add_s(f0, f0, f1);
            swc1(f0, a0, 8);
        }
    } else {
        // 0x001aae6c
        charge(ctx, 8);
        lwc1(f2, a2, 0);
        lwc1(f1, a2, 4);
        lwc1(f0, a2, 8);
        swc1(f2, a0, 0);
        swc1(f1, a0, 4);
        swc1(f0, a0, 8);
    }
    // 0x001aaf20 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
}

// 0x001ADDF0 K_FldFrame_CtlMoveInDir -- 196 bytes; frame 0x10
// 0x1ADDF0 K_FldFrame_CtlMoveInDir(collision task, dir, $f12 speed): only when the controller is idle
// (work +0 == 1): velocity (+20..+28) = dir * speed, +40 += (s32)speed (the compiler's unsigned conversion: speeds
// >= 2^31 subtract 2^31 and set bit 31), state = 0 (move pending; K_FldFrame_UpdateCtlTask 0x1AD2F0 applies it in
// three collision-checked thirds). The direction is copied to a 16-byte frame and scaled there, as the original
// does; $a0 ends as the state word (or the converted speed), $f12 as the converted speed on the move path.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_CtlMoveInDir(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::enter, hg::lui,
          hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x001addf0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(a2, a0, 60);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, sp, 0x0);
    swc1(f1, sp, 0x4);
    swc1(f0, sp, 0x8);
    lw(a0, a2, 0);
    v1 = 1;
    if (a0 == v1) {
        // 0x001ade20
        charge(ctx, 15);
        lwc1(f0, sp, 0x0);
        mul_s(f0, f0, f12);
        swc1(f0, sp, 0x0);
        lwc1(f0, sp, 0x4);
        mul_s(f0, f0, f12);
        swc1(f0, sp, 0x4);
        lwc1(f0, sp, 0x8);
        mul_s(f0, f0, f12);
        swc1(f0, sp, 0x8);
        v1 = 0x4F000000;
        mtc1(v1, f0);
        c_le_s(f0, f12);
        if (cond(ctx)) {
            // 0x001ade6c
            charge(ctx, 5);
            sub_s(f12, f12, f0);
            cvt_w_s(f12, f12);
            mfc1(a0, f12);
            v1 = lui(0x8000);
            a0 = a0 | v1;
        } else {
            // 0x001ade5c
            charge(ctx, 4);
            cvt_w_s(f12, f12);
            mfc1(a0, f12);
        }
        // 0x001ade80
        charge(ctx, 10);
        lw(v1, a2, 40);
        v1 = addu(v1, a0);
        sw(v1, a2, 40);
        lwc1(f2, sp, 0x0);
        lwc1(f1, sp, 0x4);
        lwc1(f0, sp, 0x8);
        swc1(f2, a2, 20);
        swc1(f1, a2, 24);
        swc1(f0, a2, 28);
        sw(zero, a2, 0);
    }
    // 0x001adea8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x001D8D80 K_Battle_FindTaskOfUnit -- 212 bytes; leaf frame (no stack)
// 0x1D8D80 K_Battle_FindTaskOfUnit(field unit): the live battle kosaka task (0x875A40[3]) whose party
// list (+24, count +16) or enemy list (+40, count +20) holds the unit, else 0; 0 for a NULL unit. The unit is compared
// as the whole 64-bit register. Registers: task $v0, work $a2, counts $a1, list index $t0, task index $t1, base $a3,
// the loaded entry / test $v1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_Battle_FindTaskOfUnit(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slt, hg::slti;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x001d8d80
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001d8d94
        charge(ctx, 5);
        t1 = 0;
        a3 = 0x870000;
        a3 = addiu(a3, 23104);  // &0x875A40
        for (;;) {
            // 0x001d8e3c
            charge(ctx, 3);
            v0 = slti(t1, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001d8da8
            charge(ctx, 5);
            v0 = sll(t1, 2);
            v0 = addu(a3, v0);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x001d8dbc
                charge(ctx, 5);
                lw(a2, v0, 60);
                t0 = 0;
                lw(a1, a2, 16);
                for (;;) {
                    // 0x001d8df0
                    charge(ctx, 3);
                    v1 = slt(t0, a1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001d8dd0
                    charge(ctx, 5);
                    v1 = sll(t0, 2);
                    v1 = addu(a2, v1);
                    lw(v1, v1, 24);
                    if (v1 == a0) {
                        goto L_001d8de4_6;
                    }
                    // 0x001d8dec
                    charge(ctx, 1);
                    t0 = addiu(t0, 1);
                }
                // 0x001d8dfc
                charge(ctx, 4);
                t0 = 0;
                lw(a1, a2, 20);
                for (;;) {
                    // 0x001d8e2c
                    charge(ctx, 3);
                    v1 = slt(t0, a1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001d8e0c
                    charge(ctx, 5);
                    v1 = sll(t0, 2);
                    v1 = addu(a2, v1);
                    lw(v1, v1, 40);
                    if (v1 == a0) {
                        goto L_001d8e20_11;
                    }
                    // 0x001d8e28
                    charge(ctx, 1);
                    t0 = addiu(t0, 1);
                }
            }
            // 0x001d8e38
            charge(ctx, 1);
            t1 = addiu(t1, 1);
        }
        // 0x001d8e48
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001d8d88
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001d8e4c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_001d8de4_6:
    charge(ctx, 2);
    // 0x001d8e4c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_001d8e20_11:
    charge(ctx, 2);
    // 0x001d8e4c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001D7B70 K_Battle_GetNthDatUnit -- 240 bytes; leaf frame (no stack)
// 0x1D7B70 K_Battle_GetNthDatUnit(battle kosaka task, n): the n-th battle unit of the encounter: party
// field unit i -> its encounter instance's DatUnit pointer (+72 -> +4), then each enemy's non-empty DatUnit slots.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_Battle_GetNthDatUnit(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lhu, hg::lw, hg::sll, hg::slt,
          hg::slti, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x001d7b70
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(t0, a0, 60);
    t2 = 0;
    a0 = 0;
    lw(v1, t0, 16);
    for (;;) {
        // 0x001d7bb4
        charge(ctx, 3);
        v0 = slt(a0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001d7b88
        charge(ctx, 2);
        if (a1 == t2) {
            goto L_001d7b90_2;
        }
        // 0x001d7bac
        charge(ctx, 2);
        t2 = addiu(t2, 1);
        a0 = addiu(a0, 1);
    }
    // 0x001d7bc0
    charge(ctx, 4);
    t1 = 0;
    lw(a3, t0, 20);
    for (;;) {
        // 0x001d7c48
        charge(ctx, 3);
        v0 = slt(t1, a3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001d7bd0
        charge(ctx, 5);
        t3 = 0;
        a2 = sll(t1, 2);
        a0 = addu(t0, a2);
        for (;;) {
            // 0x001d7c38
            charge(ctx, 3);
            v0 = slti(t3, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001d7be4
            charge(ctx, 10);
            v0 = sll(t3, 4);
            v0 = subu(v0, t3);
            v1 = sll(v0, 2);
            lw(v0, a0, 40);
            lw(v0, v0, 72);
            lw(v0, v0, 4);
            v0 = addu(v0, v1);
            lhu(v0, v0, 2);
            if (v0 != 0) {
                // 0x001d7c0c
                charge(ctx, 2);
                if (a1 == t2) {
                    goto L_001d7c14_9;
                }
                // 0x001d7c30
                charge(ctx, 1);
                t2 = addiu(t2, 1);
                goto L_001d7c34;
            }
        L_001d7c34:
            charge(ctx, 1);
            t3 = addiu(t3, 1);
        }
        // 0x001d7c44
        charge(ctx, 1);
        t1 = addiu(t1, 1);
    }
    // 0x001d7c54
    charge(ctx, 1);
    v0 = 0;
    // 0x001d7c58 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_001d7b90_2:
    charge(ctx, 7);
    v0 = sll(a0, 2);
    v0 = addu(v0, t0);
    lw(v0, v0, 24);
    lw(v0, v0, 72);
    lw(v0, v0, 4);
    // 0x001d7c58 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_001d7c14_9:
    charge(ctx, 7);
    v0 = addu(a2, t0);
    lw(v0, v0, 40);
    lw(v0, v0, 72);
    lw(v0, v0, 4);
    v0 = addu(v0, v1);
    // 0x001d7c58 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001D7C60 K_Battle_GetNthFieldUnit -- 220 bytes; leaf frame (no stack)
// 0x1D7C60 K_Battle_GetNthFieldUnit(battle kosaka task, n): the field unit behind the n-th battle unit
// (the same walk; an enemy field unit is returned once per non-empty slot of its encounter).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_Battle_GetNthFieldUnit(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lhu, hg::lw, hg::sll, hg::slt,
          hg::slti, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x001d7c60
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(t1, a0, 60);
    t3 = 0;
    a0 = 0;
    lw(v1, t1, 16);
    for (;;) {
        // 0x001d7c9c
        charge(ctx, 3);
        v0 = slt(a0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001d7c78
        charge(ctx, 2);
        if (a1 == t3) {
            goto L_001d7c80_2;
        }
        // 0x001d7c94
        charge(ctx, 2);
        t3 = addiu(t3, 1);
        a0 = addiu(a0, 1);
    }
    // 0x001d7ca8
    charge(ctx, 4);
    t2 = 0;
    lw(t0, t1, 20);
    for (;;) {
        // 0x001d7d24
        charge(ctx, 3);
        v0 = slt(t2, t0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001d7cb8
        charge(ctx, 5);
        t4 = 0;
        a3 = sll(t2, 2);
        a2 = addu(t1, a3);
        for (;;) {
            // 0x001d7d14
            charge(ctx, 3);
            v0 = slti(t4, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001d7ccc
            charge(ctx, 10);
            lw(v0, a2, 40);
            lw(a0, v0, 72);
            v0 = sll(t4, 4);
            v0 = subu(v0, t4);
            v1 = sll(v0, 2);
            lw(v0, a0, 4);
            v0 = addu(v0, v1);
            lhu(v0, v0, 2);
            if (v0 != 0) {
                // 0x001d7cf4
                charge(ctx, 2);
                if (a1 == t3) {
                    goto L_001d7cfc_9;
                }
                // 0x001d7d0c
                charge(ctx, 1);
                t3 = addiu(t3, 1);
                goto L_001d7d10;
            }
        L_001d7d10:
            charge(ctx, 1);
            t4 = addiu(t4, 1);
        }
        // 0x001d7d20
        charge(ctx, 1);
        t2 = addiu(t2, 1);
    }
    // 0x001d7d30
    charge(ctx, 1);
    v0 = 0;
    // 0x001d7d34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_001d7c80_2:
    charge(ctx, 5);
    v0 = sll(a0, 2);
    v0 = addu(v0, t1);
    lw(v0, v0, 24);
    // 0x001d7d34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_001d7cfc_9:
    charge(ctx, 4);
    v0 = addu(a3, t1);
    lw(v0, v0, 40);
    // 0x001d7d34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ------------------------------------------------------------------------
// Each shim passes $a0..$a3 (the 64-bit registers where the original compares them whole); the hand versions write
// $v0 and the other registers the originals leave.
namespace p3fes::recomp_gen {
using namespace p3fes::game;
void fn_K_Field_Get_001b9120(p3fes::EEContext& ctx) { K_Field_Get(ctx); }
void fn_K_Fld_GetPhase_001b9130(p3fes::EEContext& ctx) { K_Fld_GetPhase(ctx); }
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext& ctx) { K_FldDungeon_GetCurrentFloor(ctx); }
void fn_K_FldDungeon_IsCurrentFloorExplorable_001bff50(p3fes::EEContext& ctx) { K_FldDungeon_IsCurrentFloorExplorable(ctx); }
void fn_K_FldDungeon_GetCurrentFloorData_001bffa0(p3fes::EEContext& ctx) { K_FldDungeon_GetCurrentFloorData(ctx); }
void fn_K_FldDungeon_GetFloorKind_001c0040(p3fes::EEContext& ctx) { K_FldDungeon_GetFloorKind(ctx); }
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext& ctx) { K_Scene_IsRandomFloor(ctx); }
}  // namespace p3fes::recomp_gen
