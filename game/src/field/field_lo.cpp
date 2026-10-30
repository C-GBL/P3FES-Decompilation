// Field (exploration) layer, second pass: the open rows of docs/ANALYSIS/queue_field.txt below 0x1C0000 (slice
// `field_lo`; game/include/p3fes/game/field_lo.h names them), hand-decompiled from SLUS_216.21. Phase 5: these
// replace the recompiled bodies listed in game/replaced.txt; tests/game/test_field_lo.cpp runs each against its
// __recomp body.
//
// Most of these run on the battle gate's field path (Tartarus entrance, Thebel): the collision controllers'
// accessors every move (K_FldFrame_HandleCollis reads the grid cell, the update task sets the state), the scene
// predicates of the event task and the per-frame block visibility pass, the camera controller's cylinder setters,
// the sequence checks of the admini task, the floor generator's cell marker, the enemy-think queue of the shadows.
//
// Virtual time per ADR-0013: each guest::enter / charge mirrors a `ctx.cycles += N` block of the generated body on
// the executed path (charged at the block's start, before the block's calls); guest::backedge stands where the
// recompiled loop checks before jumping back (every loop here tests first, so the check precedes each iteration).
//
// Registers. Leaves compute in C++ and then leave every register they wrote holding the original's value (scratch
// registers included: a preemption at the caller's next check point saves the whole register file to the guest
// stack). The non-leaf functions keep their working values in the guest registers the original uses (S / R below),
// write the prologue spills through Frame and call through the callees' generated entry points with the original
// link (`jal`), so every check point inside a callee sees the original register file and stack.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 23 of the 43 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 23); each keeps the notes of its
// earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/field_lo.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);         // K_Assert(file, line): `jr $ra` in retail
void fn_K_Field_Get_001b9120(p3fes::EEContext&);         // [K_Field_Get] &sField (game/src/field/field.cpp)
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);         // [K_Scene_IsRandomFloor] (field.cpp)
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);         // this file
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);     // (task) -> 1 while it lives (game/src/kwln/task.cpp)
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);         // MT_Scene_GetRes(id)
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);         // MT_Scene_GetResListHead(type)
void fn_sub_3B54C0_003b54c0(p3fes::EEContext&);         // resrcMng lookup (manager, id)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace fldlo;
namespace rg = p3fes::recomp_gen;
using ee::core::sext32;

constexpr unsigned kAT = 1, kV0 = 2, kV1 = 3, kA0 = 4, kA1 = 5, kA2 = 6;
constexpr unsigned kS0 = 16, kS1 = 17, kS2 = 18, kS3 = 19, kS4 = 20;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u32 a32(u64 v) { return static_cast<u32>(v); }
s64 sgn(u64 v) { return static_cast<s64>(v); }
// lw / lhu / lbu / lb as the register holds them.
u64 lw(const EEContext& ctx, u64 va) { return sext32(guest::load<u32>(ctx, a32(va))); }
void sw(EEContext& ctx, u64 va, u64 v) { guest::store<u32>(ctx, a32(va), a32(v)); }
// addu / addiu / sll: 32-bit results, sign-extended; slti on the whole register.
u64 addu(u64 a, u64 b) { return ee::core::add32(a, b); }
u64 slti(u64 a, s64 imm) { return sgn(a) < imm ? 1 : 0; }
// The address `off($gp)`.
u64 gp(const EEContext& ctx, s32 off) { return addu(R(ctx, 28), sext32(static_cast<u32>(off))); }
// `lw rd, 60(task)`: a kwln task's work pointer.
u64 work_of(const EEContext& ctx, u64 task) { return lw(ctx, task + kTaskWork); }

// `jal fn` at `pc` ($ra = pc + 8) through the callee's generated entry point; returns $v0.
u64 jal(EEContext& ctx, u32 pc, guest::Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
    return R(ctx, kV0);
}

// The prologue `addiu sp, sp, -size; sd ra, ra_off(sp); sq r, ra_off - 16 (sp); sq .., ra_off - 32 (sp) ...` (the
// registers in the order given) and, on destruction, the epilogue's reloads and `addiu sp, sp, size`.
class Frame {
public:
    Frame(EEContext& ctx, u32 size, u32 ra_off, std::initializer_list<unsigned> regs) noexcept
        : ctx_(ctx), size_(size), ra_off_(ra_off), n_(0) {
        for (unsigned r : regs) regs_[n_++] = r;
        rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size_));
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = 0; i < n_; ++i) rt::sq(ctx_, regs_[i], GPR_SP, slot(i));
    }
    ~Frame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = 0; i < n_; ++i) rt::lq(ctx_, regs_[i], GPR_SP, slot(i));
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    u64 at(u32 off) const noexcept { return sext32(ee::core::gpr32(ctx_, GPR_SP) + off); }

private:
    s32 slot(unsigned i) const noexcept { return static_cast<s32>(ra_off_ - 16u * (i + 1u)); }
    EEContext& ctx_;
    u32 size_, ra_off_;
    unsigned regs_[10];
    unsigned n_;
};

}  // namespace

// ===================================================================================================================
// The collision controller (52-byte work, 26_field.md 4.2)
// ===================================================================================================================

// 0x001AD870 sub_1AD870 -- 24 bytes; leaf frame (no stack)
// 0x1AD870 sub_1AD870 [K_FldFrame_CtlSetFlag](task, flags): work +4 |= flags (the creators of the PC / NPC units set
// bit 30 "snap to ground" this way). The or is on the whole 64-bit $a1; $a0 ends as the work, $v1 as the new word.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1AD870(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001ad870
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    lw(v1, a0, 4);
    v1 = v1 | a1;
    sw(v1, a0, 4);
}

// 0x001AD890 sub_1AD890 -- 28 bytes; leaf frame (no stack)
// 0x1AD890 sub_1AD890 [K_FldFrame_CtlClearFlag](task, flags): work +4 &= ~flags ($a0 = ~flags as `nor`, $a2 the work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1AD890(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::nor, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x001ad890
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a2, a0, 60);
    a0 = nor(a1, 0);
    lw(v1, a2, 4);
    v1 = v1 & a0;
    sw(v1, a2, 4);
}

// 0x001AD8B0 K_FldFrame_CtlGetSphereCollisRadius -- 16 bytes; leaf frame (no stack)
// 0x1AD8B0 K_FldFrame_CtlGetSphereCollisRadius [K_FldFrame_CtlGetSphereCollisRadius](task): $f0 = work +32 (returned as its bit pattern).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_CtlGetSphereCollisRadius(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::lwc1;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x001ad8b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lwc1(f0, v0, 32);
}

// 0x001AD8C0 K_FldFrame_CtlSetSphereCollisRadius -- 80 bytes; leaf frame (no stack)
// 0x1AD8C0 K_FldFrame_CtlSetSphereCollisRadius [K_FldFrame_CtlSetSphereCollisRadius](task, $f12 radius): work +32 = radius; a radius equal to
// 0.0 (c.eq.s, so -0.0 too) sets flag bit 28 "no collision", any other clears it. FCR31.C keeps the compare, $f0 = 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_CtlSetSphereCollisRadius(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::c_eq_s, hg::charge, hg::cond, hg::enter, hg::lui, hg::lw, hg::mtc1, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x001ad8c0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, a0, 60);
    swc1(f12, a1, 32);
    mtc1(zero, f0);
    c_eq_s(f0, f12);
    if (!cond(ctx)) {
        // 0x001ad8f4
        charge(ctx, 5);
        lw(a0, a1, 4);
        v1 = lui(0xEFFF);
        v1 = v1 | 0xFFFF;
        v1 = a0 & v1;
        sw(v1, a1, 4);
    } else {
        // 0x001ad8dc
        charge(ctx, 6);
        lw(a0, a1, 4);
        v1 = 0x10000000;
        v1 = a0 | v1;
        sw(v1, a1, 4);
    }
    // 0x001ad908 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001AD910 K_FldFrame_CtlGetXGrid -- 16 bytes; leaf frame (no stack)
// 0x1AD910 K_FldFrame_CtlGetXGrid [K_FldFrame_CtlGetXGrid](task): work +44 = (int)((x + 400) / 800), the 800-unit grid column.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_CtlGetXGrid(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001ad910
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 44);
}

// 0x001AD920 K_FldFrame_CtlGetZGrid -- 16 bytes; leaf frame (no stack)
// 0x1AD920 K_FldFrame_CtlGetZGrid [K_FldFrame_CtlGetZGrid](task): work +48, the grid row.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_FldFrame_CtlGetZGrid(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001ad920
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 48);
}

// 0x001AD930 sub_1AD930 -- 16 bytes; leaf frame (no stack)
// 0x1AD930 sub_1AD930 [K_FldFrame_CtlGetMoveDistance](task): work +40, the accumulated (int) speed of the accepted
// moves (K_FldFrame_CtlMoveInDir adds to it; the enemy pop scheduler reads it).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1AD930(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001ad930
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 40);
}

// 0x001AE470 sub_1AE470 -- 16 bytes; leaf frame (no stack)
// 0x1AE470 sub_1AE470 [K_FldFrame_CtlSetState](task, state): work +0 (K_FldFrame_UpdateCtlTask: 1 idle, 0 pending).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1AE470(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001ae470
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 0);
}

// ===================================================================================================================
// Scene ids (`*(gp-0x57B0)` = the scene record {s32 major, s32 minor, ..}; 26_field.md 3.2)
// ===================================================================================================================

// 0x1A02C0 sub_1A02C0 [K_Scene_IsFixedTartarusFloor]: major 51..58 or 71..78 (the scripted Tartarus floors, any
// minor). Signed compares; the record stays in $v0 until the result, the major in $v1, the upper tests in $at.
u32 sub_1A02C0(EEContext& ctx) {
    guest::enter(ctx, 5);
    const u64 v1 = lw(ctx, lw(ctx, gp(ctx, kGpSceneIds)) + kSceneMajor);
    S(ctx, kV1, v1);
    bool yes = false;
    if (slti(v1, 51) == 0) {
        guest::charge(ctx, 3);
        const u64 at = slti(v1, 59);
        S(ctx, kAT, at);
        yes = at != 0;
    }
    if (!yes) {
        guest::charge(ctx, 3);
        if (slti(v1, 71) == 0) {
            guest::charge(ctx, 3);
            const u64 at = slti(v1, 79);
            S(ctx, kAT, at);
            yes = at != 0;
        }
    }
    guest::charge(ctx, yes ? 3 : 1);
    guest::charge(ctx, 2);
    S(ctx, kV0, yes ? 1 : 0);
    return yes ? 1 : 0;
}

// 0x1A01C0 sub_1A01C0 [K_Scene_IsTartarus]: a random floor (K_Scene_IsRandomFloor), a fixed floor (sub_1A02C0) or
// major 30..38. Calls both predicates through their entry points inside its 16-byte frame; $v1 / $a0 hold the 1 the
// original compares with, $at the last range test.
u32 sub_1A01C0(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame frame(ctx, 16, 0, {});
    u64 v0 = jal(ctx, 0x1A01C8u, &rg::fn_K_Scene_IsRandomFloor_001a0250);
    S(ctx, kV1, 1);
    if (v0 == 1) {
        guest::charge(ctx, 3);
    } else {
        guest::charge(ctx, 5);
        v0 = jal(ctx, 0x1A01E8u, &rg::fn_sub_1A02C0_001a02c0);
        S(ctx, kA0, 1);
        if (v0 == 1) {
            guest::charge(ctx, 3);
        } else {
            guest::charge(ctx, 5);
            const u64 rec = lw(ctx, gp(ctx, kGpSceneIds));
            const u64 v1 = lw(ctx, rec + kSceneMajor);
            S(ctx, kV1, v1);
            v0 = slti(v1, 30);
            bool yes = false;
            if (v0 == 0) {
                guest::charge(ctx, 3);
                const u64 at = slti(v1, 39);
                S(ctx, kAT, at);
                yes = at != 0;
            }
            if (yes) {
                guest::charge(ctx, 3);
                v0 = 1;
            } else {
                guest::charge(ctx, 1);
                v0 = 0;
            }
        }
    }
    guest::charge(ctx, 4);
    S(ctx, kV0, v0);
    return a32(v0);
}

// 0x1A0310 sub_1A0310 [K_Scene_IsSpecialScene]: the scenes 8/3, 32/2 (the Tartarus entrance), 26/51, 26/52, 26/53,
// 37/1, 35/1 and every scene of majors 4 and 5 (called by the unit / event code of the 0x1CD..0x1DF band). A chain of
// compares: $v1 = each major constant (then the minor constant), $a0 = the minor when loaded, $a1 the record.
u32 sub_1A0310(EEContext& ctx) {
    struct Pair {
        s32 major, minor;
    };
    static constexpr Pair kPairs[] = {{8, 3}, {32, 2}, {26, 51}, {26, 52}, {26, 53}, {37, 1}, {35, 1}};
    guest::enter(ctx, 5);
    const u64 a1 = lw(ctx, gp(ctx, kGpSceneIds));
    const u64 v0 = lw(ctx, a1 + kSceneMajor);
    S(ctx, kA1, a1);
    bool yes = false;
    bool first = true;
    for (const Pair& p : kPairs) {
        if (!first) guest::charge(ctx, 3);
        first = false;
        S(ctx, kV1, sext32(static_cast<u32>(p.major)));
        if (v0 == sext32(static_cast<u32>(p.major))) {
            guest::charge(ctx, 4);
            const u64 a0 = lw(ctx, a1 + kSceneMinor);
            S(ctx, kA0, a0);
            S(ctx, kV1, sext32(static_cast<u32>(p.minor)));
            if (a0 == sext32(static_cast<u32>(p.minor))) {
                yes = true;
                break;
            }
        }
    }
    if (!yes) {
        guest::charge(ctx, 3);
        S(ctx, kV1, 4);
        if (v0 == 4) {
            yes = true;
        } else {
            guest::charge(ctx, 3);
            S(ctx, kV1, 5);
            yes = v0 == 5;
        }
    }
    guest::charge(ctx, yes ? 3 : 1);
    guest::charge(ctx, 2);
    S(ctx, kV0, yes ? 1 : 0);
    return yes ? 1 : 0;
}

// 0x1A0410 sub_1A0410 [K_Scene_SetWord24](value): scene record +24 (btlMainUpdateStateSceneSet). $v1 = the record.
void sub_1A0410(EEContext& ctx, u32 value) {
    guest::enter(ctx, 4);
    const u64 v1 = lw(ctx, gp(ctx, kGpSceneIds));
    sw(ctx, v1 + kSceneWord24, value);
    S(ctx, kV1, v1);
}
// 0x1A0420 sub_1A0420 [K_Scene_SetWord28](value): scene record +28 (the event viewer, 0x36ED30 / 0x36F260).
void sub_1A0420(EEContext& ctx, u32 value) {
    guest::enter(ctx, 4);
    const u64 v1 = lw(ctx, gp(ctx, kGpSceneIds));
    sw(ctx, v1 + kSceneWord28, value);
    S(ctx, kV1, v1);
}

// ===================================================================================================================
// Scene resources: flag bit 1 of +40 (the per-frame Tartarus block pass sub_1BD950 sets it per visible cell)
// ===================================================================================================================

namespace {
// The `on == 1 ? flags | 2 : flags & -3` tail shared by sub_1A0150 / sub_1A0DC0 (the resource in $v0, `on` in $s0):
// set 5 cycles ($v1 = the new flags), clear 4 ($a0 = the old flags, $v1 = the new); 3 cycles for the compare first.
void res_flag_tail(EEContext& ctx, u64 res) {
    guest::charge(ctx, 3);
    S(ctx, kV1, 1);
    if (R(ctx, kS0) == 1) {
        guest::charge(ctx, 5);
        const u64 v1 = lw(ctx, res + kResFlags) | kResFlagBit1;
        sw(ctx, res + kResFlags, v1);
        S(ctx, kV1, v1);
    } else {
        guest::charge(ctx, 4);
        const u64 a0 = lw(ctx, res + kResFlags);
        const u64 v1 = a0 & ~static_cast<u64>(kResFlagBit1);  // addiu v1, zero, -3; and
        sw(ctx, res + kResFlags, v1);
        S(ctx, kA0, a0);
        S(ctx, kV1, v1);
    }
}
}  // namespace

// 0x1A0150 sub_1A0150 [K_Scene_SetResFlag](id, on): the scene resource `id` (MT_Scene_GetRes) gets flag bit 1 when
// `on` == 1 (compared as the whole register), loses it otherwise; nothing without the resource. 32-byte frame
// ($ra at 16, $s0 = on at 0).
void sub_1A0150(EEContext& ctx, u32 id, u64 on) {
    (void)id;  // stays in $a0 for MT_Scene_GetRes
    guest::enter(ctx, 8);
    Frame frame(ctx, 32, 16, {kS0});
    S(ctx, kS0, on);
    const u64 res = jal(ctx, 0x1A0160u, &rg::fn_sub_3B5D10_003b5d10);
    if (res != 0) res_flag_tail(ctx, res);
    guest::charge(ctx, 5);
}

// 0x1A0DC0 sub_1A0DC0 [K_Scene_SetResFlagById](id, on): the same through the scene's resource manager (record +8,
// the lookup 0x3B54C0(manager, id)); without a manager nothing happens and $v0 is left as the caller had it. The
// resource is not tested for NULL (a missing id reads and writes address 40, as the original). 32-byte frame.
void sub_1A0DC0(EEContext& ctx, u32 id, u64 on) {
    guest::enter(ctx, 9);
    Frame frame(ctx, 32, 16, {kS0});
    const u64 a2 = R(ctx, kA0);
    S(ctx, kA2, a2);
    S(ctx, kS0, on);
    const u64 v1 = lw(ctx, gp(ctx, kGpSceneIds));
    const u64 mgr = lw(ctx, v1 + kSceneMgr);
    S(ctx, kV1, v1);
    S(ctx, kA0, mgr);
    (void)id;
    if (mgr == 0) {
        guest::charge(ctx, 2);
    } else {
        guest::charge(ctx, 5);
        S(ctx, kA1, a2);
        const u64 res = jal(ctx, 0x1A0DE8u, &rg::fn_sub_3B54C0_003b54c0);
        res_flag_tail(ctx, res);
    }
    guest::charge(ctx, 5);
}

// 0x1A0040 sub_1A0040 [K_Scene_SetBlockFlags](on, also_type10): every Tartarus block resource (type 12) gets flag
// bit 1 when `on` == 1 and loses it otherwise, writing sField +52 (0 when set, 1 when cleared) after each; when
// `also_type10` == 1 the type-10 resources follow `on` the same way. Both lists are walked through +248. 96-byte
// frame ($ra at 80, $s4..$s0): $s4 = on, $s3 = also_type10, $s2 / $s1 the two list cursors, $s0 = 1.
void sub_1A0040(EEContext& ctx, u64 on, u64 also_type10) {
    guest::enter(ctx, 19);
    Frame frame(ctx, 96, 80, {kS4, kS3, kS2, kS1, kS0});
    S(ctx, kS4, on);
    S(ctx, kS3, also_type10);
    S(ctx, kA0, kResTypeBlock);
    S(ctx, kS2, jal(ctx, 0x1A0068u, &rg::fn_sub_3B5D50_003b5d50));
    S(ctx, kA0, kResType10);
    S(ctx, kS1, jal(ctx, 0x1A0078u, &rg::fn_sub_3B5D50_003b5d50));
    for (;;) {
        guest::charge(ctx, 2);
        const u64 res = R(ctx, kS2);
        if (res == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 3);
        S(ctx, kS0, 1);
        if (on == 1) {
            guest::charge(ctx, 8);
            const u64 v0 = lw(ctx, res + kResFlags) | kResFlagBit1;
            sw(ctx, res + kResFlags, v0);
            S(ctx, kV0, v0);
            const u64 field = jal(ctx, 0x1A00A4u, &rg::fn_K_Field_Get_001b9120);
            sw(ctx, field + kFieldBlocksHidden, 0);
        } else {
            guest::charge(ctx, 7);
            const u64 v1 = lw(ctx, res + kResFlags);
            const u64 v0 = v1 & ~static_cast<u64>(kResFlagBit1);
            sw(ctx, res + kResFlags, v0);
            S(ctx, kV1, v1);
            S(ctx, kV0, v0);
            const u64 field = jal(ctx, 0x1A00C8u, &rg::fn_K_Field_Get_001b9120);
            sw(ctx, field + kFieldBlocksHidden, 1);
        }
        guest::charge(ctx, 1);
        S(ctx, kS2, lw(ctx, res + kResNext));
    }
    guest::charge(ctx, 3);
    S(ctx, kA1, 1);
    if (also_type10 == 1) {
        guest::charge(ctx, 3);
        S(ctx, kA0, sext32(~kResFlagBit1));  // -3
        for (;;) {
            guest::charge(ctx, 2);
            const u64 res = R(ctx, kS1);
            if (res == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 2);
            u64 v1;
            if (on == 1) {
                guest::charge(ctx, 5);
                v1 = lw(ctx, res + kResFlags) | kResFlagBit1;
            } else {
                guest::charge(ctx, 3);
                v1 = lw(ctx, res + kResFlags) & R(ctx, kA0);
            }
            sw(ctx, res + kResFlags, v1);
            S(ctx, kV1, v1);
            guest::charge(ctx, 1);
            S(ctx, kS1, lw(ctx, res + kResNext));
        }
    }
    guest::charge(ctx, 9);
}

namespace {
// sub_19FD40 / 70 / A0: `MT_Scene_GetResListHead(12) + off` in one 10-cycle block inside a 16-byte frame (no NULL
// test: an empty list gives `off`).
u32 block_list_plus(EEContext& ctx, u32 pc, u32 off) {
    guest::enter(ctx, 10);
    Frame frame(ctx, 16, 0, {});
    S(ctx, kA0, kResTypeBlock);
    const u64 v0 = addu(jal(ctx, pc, &rg::fn_sub_3B5D50_003b5d50), off);
    S(ctx, kV0, v0);
    return a32(v0);
}
// sub_1A09D0 / 0A10 / 0A50: `head = MT_Scene_GetResListHead(4); head ? head + off : 0` (16-byte frame).
u32 type4_list_plus(EEContext& ctx, u32 pc, u32 off) {
    guest::enter(ctx, 7);
    Frame frame(ctx, 16, 0, {});
    S(ctx, kA0, kResTypeChar);
    u64 v0 = jal(ctx, pc, &rg::fn_sub_3B5D50_003b5d50);
    if (v0 != 0) {
        guest::charge(ctx, 3);
        v0 = addu(v0, off);
    } else {
        guest::charge(ctx, 1);
        v0 = 0;
    }
    guest::charge(ctx, 4);
    S(ctx, kV0, v0);
    return a32(v0);
}
}  // namespace

// 0x19FD40 sub_19FD40: the first Tartarus block resource (type 12) + 256 (the field draw tasks read three
// consecutive 16-byte records of it at +256 / +272 / +288; inf: the block's light / colour records).
u32 sub_19FD40(EEContext& ctx) { return block_list_plus(ctx, 0x19FD4Cu, 256); }
// 0x19FD70 sub_19FD70: the first block resource + 272.
u32 sub_19FD70(EEContext& ctx) { return block_list_plus(ctx, 0x19FD7Cu, 272); }
// 0x19FDA0 sub_19FDA0: the first block resource + 288.
u32 sub_19FDA0(EEContext& ctx) { return block_list_plus(ctx, 0x19FDACu, 288); }
// 0x1A09D0 sub_1A09D0: the first type-4 resource + 256, 0 without one (battle scene set-up 0x29DFC0 / 0x29E420).
u32 sub_1A09D0(EEContext& ctx) { return type4_list_plus(ctx, 0x1A09DCu, 256); }
// 0x1A0A10 sub_1A0A10: the first type-4 resource + 272, 0 without one.
u32 sub_1A0A10(EEContext& ctx) { return type4_list_plus(ctx, 0x1A0A1Cu, 272); }
// 0x1A0A50 sub_1A0A50: the first type-4 resource + 288, 0 without one.
u32 sub_1A0A50(EEContext& ctx) { return type4_list_plus(ctx, 0x1A0A5Cu, 288); }

// ===================================================================================================================
// The camera controller's debug cylinder (K_Draw_CreateCylinderTask work; 26_field.md 4.4)
// ===================================================================================================================

// 0x001A48E0 sub_1A48E0 -- 16 bytes; leaf frame (no stack)
// 0x1A48E0 sub_1A48E0 [K_Draw_CylinderSetWord](task, value): work +0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A48E0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a48e0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 0);
}

// 0x001A48F0 sub_1A48F0 -- 36 bytes; leaf frame (no stack)
// 0x1A48F0 sub_1A48F0 [K_Draw_CylinderSetPos](task, pos): work +4..+12 = pos[0..2] (through $f2, $f1, $f0).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A48F0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::lwc1, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a48f0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, v1, 4);
    swc1(f1, v1, 8);
    swc1(f0, v1, 12);
}

// 0x001A4920 sub_1A4920 -- 16 bytes; leaf frame (no stack)
// 0x1A4920 sub_1A4920 [K_Draw_CylinderSetRadius](task, $f12): work +16 (the camera's dead-zone radius).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A4920(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x001a4920
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    swc1(f12, v1, 16);
}

// 0x001A4930 sub_1A4930 -- 16 bytes; leaf frame (no stack)
// 0x1A4930 sub_1A4930 [K_Draw_CylinderSetHeight](task, $f12): work +20 (the dead-zone height).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A4930(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x001a4930
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    swc1(f12, v1, 20);
}

// ===================================================================================================================
// The field root, the automatic dungeon, the sequence checks
// ===================================================================================================================

// 0x001BAB40 sub_1BAB40 -- 16 bytes; leaf frame (no stack)
// 0x1BAB40 sub_1BAB40 [K_Field_GetSubId1](root task): root work +24 (u16), the scene sub-id picked by sub_1B6EB0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1BAB40(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001bab40
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lhu(v0, v0, 24);
}

// 0x001BAB50 sub_1BAB50 -- 16 bytes; leaf frame (no stack)
// 0x1BAB50 sub_1BAB50 [K_Field_GetSubId2](root task): root work +26 (u16).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1BAB50(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001bab50
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lhu(v0, v0, 26);
}

// 0x1BFF00 K_FldDungeon_RequestShutdown [K_FldDungeon_RequestShutdown]: dungeon work +12 = 1 (K_FldDungeon_UpdateTask state 3 -> 9);
// nothing without the task. $v1 ends as the task (or its work), $a0 = 1.
void K_FldDungeon_RequestShutdown(EEContext& ctx) {
    guest::enter(ctx, 3);
    u64 v1 = lw(ctx, gp(ctx, kGpDungeonTask));
    if (v1 != 0) {
        guest::charge(ctx, 3);
        S(ctx, kA0, 1);
        v1 = work_of(ctx, v1);
        sw(ctx, v1 + kDngShutdown, 1);
    }
    guest::charge(ctx, 2);
    S(ctx, kV1, v1);
}

// 0x1BFFE0 K_FldDungeon_GetScrMemory [K_FldDungeon_GetScrMemory]: dungeon work +52 (the dungeon script memory: procedure 0 = stairs /
// transporter, 1 = game over), 0 without the task.
u32 K_FldDungeon_GetScrMemory(EEContext& ctx) {
    guest::enter(ctx, 3);
    u64 v0 = lw(ctx, gp(ctx, kGpDungeonTask));
    if (v0 == 0) {
        guest::charge(ctx, 3);
        v0 = 0;
    } else {
        guest::charge(ctx, 2);
        v0 = lw(ctx, work_of(ctx, v0) + kDngScrMemory);
    }
    guest::charge(ctx, 2);
    S(ctx, kV0, v0);
    return a32(v0);
}

// 0x1B0910 sub_1B0910 [K_Fldrc_GetFieldPack]: the word at gp-0x4B94 (inf: the resident field pack; read by the file
// requesters of k_fldrc.c and the event task before they load from the pack).
u32 sub_1B0910(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u64 v0 = lw(ctx, gp(ctx, kGpFieldPack));
    S(ctx, kV0, v0);
    return a32(v0);
}

namespace {
// K_Seq_CheckField / sub_1B79F0: `kwlnTaskExists(sField.root) == 1 ? 0 : (sField.root = 0, 1)` in a 16-byte frame; the
// three call sites at pc0, pc0 + 12, pc0 + 44.
u32 check_root_gone(EEContext& ctx, u32 pc0) {
    guest::enter(ctx, 10);
    Frame frame(ctx, 16, 0, {});
    const u64 field = jal(ctx, pc0, &rg::fn_K_Field_Get_001b9120);
    S(ctx, kA0, lw(ctx, field));
    u64 v0 = jal(ctx, pc0 + 12, &rg::fn_kwlnTaskExists_00195460);
    S(ctx, kV1, 1);
    if (v0 == 1) {
        guest::charge(ctx, 3);
        v0 = 0;
    } else {
        guest::charge(ctx, 4);
        sw(ctx, jal(ctx, pc0 + 44, &rg::fn_K_Field_Get_001b9120), 0);
        v0 = 1;
    }
    guest::charge(ctx, 4);
    S(ctx, kV0, v0);
    return a32(v0);
}
}  // namespace

// 0x1B78A0 K_Seq_CheckField [K_Seq_CheckField]: sequence 2's check (sSequenceList 0x68F020): 0 while the field root lives,
// else sField.root = 0 and 1 (the admini task may run the next sequence).
u32 K_Seq_CheckField(EEContext& ctx) { return check_root_gone(ctx, 0x1B78A8u); }
// 0x1B79F0 sub_1B79F0 [K_Seq_CheckFieldEvent]: sequence 3's check, the same body.
u32 sub_1B79F0(EEContext& ctx) { return check_root_gone(ctx, 0x1B79F8u); }

// 0x1B7AC0 sub_1B7AC0 [K_Seq_CheckDungeon]: sequence 5's check: 0 while the dungeon task (gp-0x4A88) lives, else the
// slot = 0 and 1. 16-byte frame.
u32 sub_1B7AC0(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame frame(ctx, 16, 0, {});
    S(ctx, kA0, lw(ctx, gp(ctx, kGpDungeonTask)));
    u64 v0 = jal(ctx, 0x1B7ACCu, &rg::fn_kwlnTaskExists_00195460);
    S(ctx, kV1, 1);
    if (v0 == 1) {
        guest::charge(ctx, 3);
        v0 = 0;
    } else {
        guest::charge(ctx, 2);
        sw(ctx, gp(ctx, kGpDungeonTask), 0);
        v0 = 1;
    }
    guest::charge(ctx, 4);
    S(ctx, kV0, v0);
    return a32(v0);
}

// ===================================================================================================================
// EPL effect handles (the encounter flash and the other field effects of sField +4596..; sub_1A91B0 creates them)
// ===================================================================================================================

// 0x001A9180 sub_1A9180 -- 44 bytes; leaf frame (no stack)
// 0x1A9180 sub_1A9180 [K_Epl_IsStarted](task): 1 for a NULL task (compared as the whole register), else
// work +0 >= 1 (slti / xori). The event task polls it in the battle states 4..8.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A9180(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::slti;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001a9180
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001a9194
        charge(ctx, 4);
        lw(v0, a0, 60);
        lw(v0, v0, 0);
        v0 = slti(v0, 1);
        v0 = v0 ^ 0x1;
    } else {
        // 0x001a9188
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001a91a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001A9390 sub_1A9390 -- 64 bytes; leaf frame (no stack)
// 0x1A9390 sub_1A9390 [K_Epl_SetHalf](task, i, value): i < 0 (whole register) -> u16 work +28 = value; else when the
// handle +36[i] is set, u16 work +100[i] = value. $a0 = the work, $v1 the last address term.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A9390(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::i64, hg::lw, hg::sh, hg::sll;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x001a9390
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    if (i64(a1) < 0) {
        // 0x001a93c4
        charge(ctx, 1);
        sh(a2, a0, 28);
    } else {
        // 0x001a939c
        charge(ctx, 5);
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 36);
        if (v1 != 0) {
            // 0x001a93b0
            charge(ctx, 5);
            v1 = sll(a1, 1);
            v1 = addu(v1, a0);
            sh(a2, v1, 100);
        }
    }
    // 0x001a93c8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001A93D0 sub_1A93D0 -- 44 bytes; leaf frame (no stack)
// 0x1A93D0 sub_1A93D0 [K_Epl_GetWord](task, i): i < 0 -> work +24, else work +68[i]. $v1 = the work.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A93D0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::i64, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a93d0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    if (i64(a1) < 0) {
        // 0x001a93f0
        charge(ctx, 1);
        lw(v0, v1, 24);
    } else {
        // 0x001a93dc
        charge(ctx, 5);
        v0 = sll(a1, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 68);
    }
    // 0x001a93f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// ===================================================================================================================
// The Tartarus floor grid (k_dungeon.c)
// ===================================================================================================================

// 0x001BB090 sub_1BB090 -- 624 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1BB090 sub_1BB090 [K_FldDungeon_PlaceBlock](block, x, z, tag): marks the cells a block descriptor covers in the
// 16 x 16 grid at sField +72 (26_field.md 6.2), from the recursive layout step sub_1BCAC0. The descriptor: +0 s8,
// +1 width, +2 depth, +3 a byte, then one 24-byte row per z with a byte per x at +14 + 8 col. K_Assert (`jr $ra` in
// retail: the code continues) at k_dungeon.c 262 / 263 when x + width - 1 / z + depth - 1 leave the grid; the
// origin cell's +1 = 1; then per covered cell, unless already taken (K_Assert 292, the cell is skipped): +0 = 1,
// +11 = the descriptor's byte for the cell, +7 / +8 = width / depth, +2 = desc +0, +6 = tag (the low byte of the
// half the original stores at frame +174), +10 = desc +3, +9 = the placed-block counter gp-0x4A94 (low byte), which is
// incremented at the end. Every cell write re-fetches &sField (K_Field_Get) as the original does.
// 176-byte frame ($ra at 144, $fp, $s7..$s0): $s4 = block, $s5 / $s6 = x / z (u16), $s3 = row, $s2 = column,
// $s1 = (z + row) << 8, $s0 = (x + col) << 4, $fp = the row's descriptor bytes, $s7 the byte being stored.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1BB090(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::lbu, hg::ld,
          hg::lq, hg::lw, hg::sb, hg::sd, hg::sh, hg::sll, hg::slt, hg::slti, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x001bb090
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s1 = a1;
    s0 = a2;
    sh(a3, sp, 0xAE);
    s5 = s1 & 0xFFFF;
    lbu(v0, a0, 1);
    v0 = addu(s5, v0);
    v0 = addiu(v0, -1);
    v0 = slti(v0, 16);
    if (v0 == 0) {
        // 0x001bb0e8
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 13216);  // "k_dungeon.c"
        a1 = 262;
        jal(ctx, 0x1BB0F4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001bb0fc
    charge(ctx, 7);
    s6 = s0 & 0xFFFF;
    lbu(v0, s4, 2);
    v0 = addu(s6, v0);
    v0 = addiu(v0, -1);
    v0 = slti(v0, 16);
    if (v0 == 0) {
        // 0x001bb118
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 13216);  // "k_dungeon.c"
        a1 = 263;
        jal(ctx, 0x1BB124u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001bb12c
    charge(ctx, 13);
    s2 = 1;
    jal(ctx, 0x1BB130u, gen::fn_K_Field_Get_001b9120);
    v1 = s0 & 0xFFFF;
    v1 = sll(v1, 8);
    a0 = addu(v0, v1);
    v1 = s1 & 0xFFFF;
    v1 = sll(v1, 4);
    v1 = addu(a0, v1);
    sb(s2, v1, 73);
    s3 = 0;
    for (;;) {
        // 0x001bb2b0
        charge(ctx, 4);
        lbu(v1, s4, 2);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bb160
        charge(ctx, 9);
        s2 = 0;
        v1 = addu(s6, s3);
        s1 = sll(v1, 8);
        v1 = sll(s3, 1);
        v1 = addu(v1, s3);
        v1 = sll(v1, 3);
        fp = addu(s4, v1);
        for (;;) {
            // 0x001bb29c
            charge(ctx, 4);
            lbu(v1, s4, 1);
            v1 = slt(s2, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bb184
            charge(ctx, 9);
            v0 = addu(s5, s2);
            s0 = sll(v0, 4);
            jal(ctx, 0x1BB18Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(s1, v0);
            v0 = addu(v0, s0);
            lbu(v0, v0, 72);
            if (v0 != 0) {
                // 0x001bb284
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 13216);  // "k_dungeon.c"
                a1 = 292;
                jal(ctx, 0x1BB290u, gen::fn_sub_19D3F0_0019d3f0);
            } else {
                // 0x001bb1a8
                charge(ctx, 55);
                v0 = addu(s5, s2);
                s0 = sll(v0, 4);
                s7 = 1;
                jal(ctx, 0x1BB1B4u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 72);
                v0 = sll(s2, 3);
                v0 = addu(fp, v0);
                lbu(s7, v0, 14);
                jal(ctx, 0x1BB1D4u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 83);
                lbu(s7, s4, 1);
                jal(ctx, 0x1BB1ECu, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 79);
                lbu(s7, s4, 2);
                jal(ctx, 0x1BB204u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 80);
                lb(s7, s4, 0);
                jal(ctx, 0x1BB21Cu, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 74);
                lbu(v0, sp, 0xAE);
                s7 = v0;
                jal(ctx, 0x1BB238u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 78);
                lbu(s7, s4, 3);
                jal(ctx, 0x1BB250u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                sb(s7, v0, 82);
                lbu(s7, gp, -19092);  // 0x7CE25C
                jal(ctx, 0x1BB268u, gen::fn_K_Field_Get_001b9120);
                v1 = addu(s1, v0);
                v1 = addu(v1, s0);
                sb(s7, v1, 81);
            }
            // 0x001bb298
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x001bb2ac
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x001bb2c0
    charge(ctx, 16);
    lw(v1, gp, -19092);  // 0x7CE25C
    v1 = addiu(v1, 1);
    sw(v1, gp, -19092);  // 0x7CE25C
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// ===================================================================================================================
// The enemy-think action queue (work +32: 47 entries of 24 bytes, count +28)
// ===================================================================================================================

// 0x001B0220 sub_1B0220 -- 16 bytes; leaf frame (no stack)
// 0x1B0220 sub_1B0220 [K_Think_GetQueueCount](task): work +28.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B0220(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001b0220
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 28);
}

// 0x001B0240 sub_1B0240 -- 16 bytes; leaf frame (no stack)
// 0x1B0240 sub_1B0240 [K_Think_SetWord24](task, value): work +24.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B0240(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001b0240
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 24);
}

// 0x001B0260 sub_1B0260 -- 96 bytes; leaf frame (no stack)
// 0x1B0260 sub_1B0260 [K_Think_SetMode](task, mode): work +8 = mode; mode 1 (whole register) sets flag bit 27
// ("frozen") of the unit's collision controller (unit +480 -> task -> work +4), any other mode clears it.
// $a0 ends as the controller's old flags, $a1 as the controller work, $v1 the new flags.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B0260(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lui, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001b0260
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    sw(a1, a0, 8);
    v1 = 1;
    if (a1 != v1) {
        // 0x001b0298
        charge(ctx, 8);
        lw(v1, a0, 12);
        lw(v1, v1, 480);
        lw(a1, v1, 60);
        lw(a0, a1, 4);
        v1 = lui(0xF7FF);
        v1 = v1 | 0xFFFF;
        v1 = a0 & v1;
        sw(v1, a1, 4);
    } else {
        // 0x001b0274
        charge(ctx, 9);
        lw(v1, a0, 12);
        lw(v1, v1, 480);
        lw(a1, v1, 60);
        lw(a0, a1, 4);
        v1 = 0x8000000;
        v1 = a0 | v1;
        sw(v1, a1, 4);
    }
    // 0x001b02b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001AFF70 sub_1AFF70 -- 164 bytes; leaf frame (no stack)
// 0x1AFF70 sub_1AFF70 [K_Think_PushWait](task, value): appends a type-1 entry {+0 = 1, +16 = (float)value} unless the
// queue is full (47) or its last entry is already type 1; returns 1 when appended. $a2 = the work, $a0 the count
// (re-read), $v1 the new count, $f0 the converted value.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1AFF70(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::lw, hg::mtc1,
          hg::sll, hg::slti, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0};
    // 0x001aff70
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a2, a0, 60);
    lw(a0, a2, 28);
    at = slti(a0, 47);
    if (at == 0) {
        // 0x001b0008
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001aff84
        charge(ctx, 2);
        if (i64(a0) > 0) {
            // 0x001aff8c
            charge(ctx, 8);
            v0 = sll(a0, 1);
            v0 = addu(v0, a0);
            v0 = sll(v0, 3);
            v0 = addu(v0, a2);
            lw(v1, v0, 8);
            v0 = 1;
            if (v1 != v0) {
                goto L_001affb8;
            }
            // 0x001affac
            charge(ctx, 3);
            v0 = 0;
            // 0x001b000c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_001affb8:
        charge(ctx, 20);
        v0 = 1;
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 3);
        v1 = addu(v1, a2);
        sw(v0, v1, 32);
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        lw(a0, a2, 28);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 3);
        v1 = addu(v1, a2);
        swc1(f0, v1, 48);
        lw(v1, a2, 28);
        v1 = addiu(v1, 1);
        sw(v1, a2, 28);
    }
    // 0x001b000c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001B0020 sub_1B0020 -- 160 bytes; leaf frame (no stack)
// 0x1B0020 sub_1B0020 [K_Think_PushMove](task, target, value): appends a type-2 entry {+0 = 2, +4..+12 = target[0..2],
// +16 = (float)value} unless the queue is full; returns 1 when appended. $a3 = the work, $v1 the count reloads,
// $f2 / $f1 / $f0 the copy then the converted value.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B0020(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::lw, hg::lwc1, hg::mtc1,
          hg::sll, hg::slti, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001b0020
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a3, a0, 60);
    lw(a0, a3, 28);
    at = slti(a0, 47);
    if (at == 0) {
        // 0x001b00b4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001b0034
        charge(ctx, 32);
        v1 = 2;
        v0 = sll(a0, 1);
        v0 = addu(v0, a0);
        v0 = sll(v0, 3);
        v0 = addu(v0, a3);
        sw(v1, v0, 32);
        lw(v1, a3, 28);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, a3);
        lwc1(f2, a1, 0);
        lwc1(f1, a1, 4);
        lwc1(f0, a1, 8);
        swc1(f2, v0, 36);
        swc1(f1, v0, 40);
        swc1(f0, v0, 44);
        mtc1(a2, f0);
        cvt_s_w(f0, f0);
        lw(v1, a3, 28);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, a3);
        swc1(f0, v0, 48);
        lw(v0, a3, 28);
        v0 = addiu(v0, 1);
        sw(v0, a3, 28);
        v0 = 1;
    }
    // 0x001b00b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ------------------------------------------------------------------------
// Each shim passes $a0..$a3 (the 64-bit registers where the original compares or combines them whole).
namespace p3fes::recomp_gen {
using namespace p3fes::game;
namespace {
u32 a(const p3fes::EEContext& ctx, unsigned i) { return guest::arg32(ctx, i); }
u64 a64(const p3fes::EEContext& ctx, unsigned i) { return ee::core::gpr64(ctx, GPR_A0 + i); }
}  // namespace
void fn_sub_1A02C0_001a02c0(p3fes::EEContext& ctx) { sub_1A02C0(ctx); }
void fn_sub_1A01C0_001a01c0(p3fes::EEContext& ctx) { sub_1A01C0(ctx); }
void fn_sub_1A0310_001a0310(p3fes::EEContext& ctx) { sub_1A0310(ctx); }
void fn_sub_1A0410_001a0410(p3fes::EEContext& ctx) { sub_1A0410(ctx, a(ctx, 0)); }
void fn_sub_1A0420_001a0420(p3fes::EEContext& ctx) { sub_1A0420(ctx, a(ctx, 0)); }
void fn_sub_1A0150_001a0150(p3fes::EEContext& ctx) { sub_1A0150(ctx, a(ctx, 0), a64(ctx, 1)); }
void fn_sub_1A0040_001a0040(p3fes::EEContext& ctx) { sub_1A0040(ctx, a64(ctx, 0), a64(ctx, 1)); }
void fn_sub_1A0DC0_001a0dc0(p3fes::EEContext& ctx) { sub_1A0DC0(ctx, a(ctx, 0), a64(ctx, 1)); }
void fn_sub_19FD40_0019fd40(p3fes::EEContext& ctx) { sub_19FD40(ctx); }
void fn_sub_19FD70_0019fd70(p3fes::EEContext& ctx) { sub_19FD70(ctx); }
void fn_sub_19FDA0_0019fda0(p3fes::EEContext& ctx) { sub_19FDA0(ctx); }
void fn_sub_1A09D0_001a09d0(p3fes::EEContext& ctx) { sub_1A09D0(ctx); }
void fn_sub_1A0A10_001a0a10(p3fes::EEContext& ctx) { sub_1A0A10(ctx); }
void fn_sub_1A0A50_001a0a50(p3fes::EEContext& ctx) { sub_1A0A50(ctx); }
void fn_K_FldDungeon_RequestShutdown_001bff00(p3fes::EEContext& ctx) { K_FldDungeon_RequestShutdown(ctx); }
void fn_K_FldDungeon_GetScrMemory_001bffe0(p3fes::EEContext& ctx) { K_FldDungeon_GetScrMemory(ctx); }
void fn_sub_1B0910_001b0910(p3fes::EEContext& ctx) { sub_1B0910(ctx); }
void fn_K_Seq_CheckField_001b78a0(p3fes::EEContext& ctx) { K_Seq_CheckField(ctx); }
void fn_sub_1B79F0_001b79f0(p3fes::EEContext& ctx) { sub_1B79F0(ctx); }
void fn_sub_1B7AC0_001b7ac0(p3fes::EEContext& ctx) { sub_1B7AC0(ctx); }
}  // namespace p3fes::recomp_gen
