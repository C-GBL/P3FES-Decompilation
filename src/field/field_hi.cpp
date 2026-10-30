// The field layer, second pass (game/include/p3fes/game/field_hi.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/26_field.md). Phase 5 slice `field_hi`: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_field_hi.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: every guest::enter / charge mirrors a `ctx.cycles += N` block of
// recomp/generated/fn_0008_001c0040_001d2a10.cpp (and the neighbouring files) on the executed path. A block that
// contains a `jal` is charged whole before the call, as the generated code does. Every loop here tests first, so
// guest::backedge stands after the test block's charge, before each iteration's body.
//
// Registers. The event task (K_FldEvent_UpdateFldEventTask), the field root (K_Field_UpdateFieldRootTask) and the enemy-think tasks call these, and a
// check point may preempt the thread: the kernel then writes the whole register file to the guest stack. So each
// function leaves every register it writes -- $at/$v0/$v1/$a0..$a3/$t0..$t3, $s0..$s2 inside its frame, $f0/$f1/$f12,
// FCR31.C, HI/LO -- holding the original's value at every check point (entry, back-edges, the callees' entries) and
// at the return; a local named after a register holds what the original keeps there. The non-leaf functions write
// their prologue spills to the guest stack (Frame), so the callees' own frames and spills land on the original
// bytes, and call every callee through its generated entry point with $ra = the original link (jal). $gp is read
// from the register.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 21 of the 50 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 20, callee frames 1); each keeps the
// notes of its earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/field_hi.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/guest.h"

#include <cstddef>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);  // (request) -> the file is resident
void fn_sub_1A9400_001a9400(p3fes::EEContext&);           // (epl, instance): stop an EPL effect instance (inf)
void fn_sub_1A91B0_001a91b0(p3fes::EEContext&);           // (epl, &pos) -> an EPL effect instance (26_field.md 2.1)
void fn_datGetFlag_0016f190(p3fes::EEContext&);           // (flag)
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);           // eight integer arguments + $f12 (a draw-list command, inf)
void fn_sub_3174E0_003174e0(p3fes::EEContext&);           // (model handle): release (inf)
void fn_sub_319230_00319230(p3fes::EEContext&);           // (anim set, id)
void fn_kwlnTaskSetFlags_001956d0(p3fes::EEContext&);           // (task, flags, clear): kwln task flag helper
void fn_sub_316E00_00316e00(p3fes::EEContext&);           // (8, kind, 0) -> a model handle
void fn_sub_316F70_00316f70(p3fes::EEContext&);           // (model) -> ready
void fn_sub_1D1640_001d1640(p3fes::EEContext&);           // (field unit, arg): reset a field unit (creates tasks)
void fn_sub_19C2F0_0019c2f0(p3fes::EEContext&);           // (resource +484 word, arg)
void fn_sub_1A60D0_001a60d0(p3fes::EEContext&);           // (0, model, alpha)
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);       // (task) -> 1 when live
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);           // MT_Scene_GetRes(id)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace fldhi;
namespace rg = p3fes::recomp_gen;

// --- registers -----------------------------------------------------------------------------------------------------
constexpr unsigned kV0 = 2, kV1 = 3, kA0 = 4, kA1 = 5, kA2 = 6, kA3 = 7, kT0 = 8, kS0 = 16, kS1 = 17, kS2 = 18;
constexpr u32 kTaskWork = 60;  // KwlnTask +0x3C: the work pointer

void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u32 a32(u64 v) { return static_cast<u32>(v); }
s64 sgn(u64 v) { return static_cast<s64>(v); }

// Loads and stores at `base + off` (base the 64-bit register value; the address is its low word).
u64 lw(const EEContext& ctx, u64 base, s32 off) { return sx(guest::load<u32>(ctx, a32(base) + static_cast<u32>(off))); }
u64 lhu(const EEContext& ctx, u64 base, s32 off) { return guest::load<u16>(ctx, a32(base) + static_cast<u32>(off)); }
void sw(EEContext& ctx, u64 base, s32 off, u64 v) { guest::store<u32>(ctx, a32(base) + static_cast<u32>(off), a32(v)); }
void sh(EEContext& ctx, u64 base, s32 off, u64 v) {
    guest::store<u16>(ctx, a32(base) + static_cast<u32>(off), static_cast<u16>(v));
}
void sb(EEContext& ctx, u64 base, s32 off, u64 v) {
    guest::store<u8>(ctx, a32(base) + static_cast<u32>(off), static_cast<u8>(v));
}
// `$gp + off` as `addiu` computes it, and `lw rt, off($gp)`.
u64 gp(const EEContext& ctx, s32 off) { return sx(ee::core::gpr32(ctx, GPR_GP) + static_cast<u32>(off)); }
u64 lw_gp(const EEContext& ctx, s32 off) { return lw(ctx, R(ctx, GPR_GP), off); }
// 32-bit ALU results, sign-extended as the register holds them.
u64 addu(u64 a, u64 b) { return sx(a32(a) + a32(b)); }
u64 subu(u64 a, u64 b) { return sx(a32(a) - a32(b)); }
u64 sll(u64 a, unsigned n) { return sx(a32(a) << n); }
u64 b2u(bool b) { return b ? 1u : 0u; }

// `jal fn` at `pc` ($ra = pc + 8) through the callee's generated entry point; returns $v0.
u64 jal(EEContext& ctx, u32 pc, guest::Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
    return R(ctx, kV0);
}

// The prologue `addiu sp, sp, -size; sd ra, ra_off; sq s<top>..s0 at ra_off - 16, ra_off - 32, ...` and, on
// destruction, its epilogue (the reloads from the guest stack, `addiu sp, sp, size`). top_s < 16: no s-registers.
class Frame {
public:
    Frame(EEContext& ctx, u32 size, u32 ra_off, unsigned top_s) noexcept
        : ctx_(ctx), size_(size), ra_off_(ra_off), top_s_(top_s) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size_));
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned r = top_s_; r >= kS0; --r) rt::sq(ctx_, r, GPR_SP, slot(r));
    }
    ~Frame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned r = top_s_; r >= kS0; --r) rt::lq(ctx_, r, GPR_SP, slot(r));
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    u64 sp() const noexcept { return R(ctx_, GPR_SP); }

private:
    s32 slot(unsigned r) const noexcept { return static_cast<s32>(ra_off_ - 16u * (top_s_ - r + 1u)); }
    EEContext& ctx_;
    u32 size_, ra_off_;
    unsigned top_s_;
};

// The field-unit address as the walks compute it (no multiply): `sll rt, i, 3; subu rt, rt, i; sll roff, rt, 6;
// lui/addiu rbase, base; addu runit, rbase, roff` -- the registers written in that order (they may alias).
u64 unit_addr(EEContext& ctx, u64 i, u32 base, unsigned rt_, unsigned roff, unsigned rbase, unsigned runit) {
    const u64 t = subu(sll(i, 3), i);
    S(ctx, rt_, t);
    const u64 off = sll(t, 6);
    S(ctx, roff, off);
    S(ctx, rbase, sx(base));
    const u64 unit = addu(sx(base), off);
    S(ctx, runit, unit);
    return unit;
}

// The "live unit" test of the walks: `lw rx, 72(unit); beqz; lw rx, 84(unit); beqz; li rflag, 1` (rflag was zeroed
// at the top of the body). The +72 load belongs to the body block (charged by the caller); the +84 block costs 3 and
// the `li` block 1.
bool unit_live(EEContext& ctx, u64 unit, unsigned rx, unsigned rflag) {
    u64 x = lw(ctx, unit, static_cast<s32>(kUnitInstance));
    S(ctx, rx, x);
    if (x == 0) return false;
    guest::charge(ctx, 3);
    x = lw(ctx, unit, static_cast<s32>(kUnitResource));
    S(ctx, rx, x);
    if (x == 0) return false;
    guest::charge(ctx, 1);
    S(ctx, rflag, 1);
    return true;
}

// The two list lookups of the NPC-placement band: `lw v0, head($gp); andi a0, a0, 0xFFFF;` then while (v0) { if
// (u16 v0[id_off] == a0) break; v0 = v0[next_off]; }. Test block 4 (two nops, bnez, nop), body 3 + 1.
u32 find_in_list(EEContext& ctx, u64 id, s32 head, s32 id_off, s32 next_off) {
    guest::enter(ctx, 4);
    u64 v0 = lw_gp(ctx, head);
    const u64 a0 = id & 0xFFFFu;
    S(ctx, kV0, v0);
    S(ctx, kA0, a0);
    for (;;) {
        guest::charge(ctx, 4);
        if (v0 == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 3);
        const u64 v1 = lhu(ctx, v0, id_off);
        S(ctx, kV1, v1);
        if (v1 == a0) break;
        guest::charge(ctx, 1);
        v0 = lw(ctx, v0, next_off);
        S(ctx, kV0, v0);
    }
    guest::charge(ctx, 2);
    return a32(v0);
}

}  // namespace

// =====================================================================================================================
// The automatic dungeon (k_dungeon.c)
// =====================================================================================================================

// 0x1C0010 K_FldDungeon_GetScrSize [K_FldDungeon_GetScriptSize]: dungeon work +56 (the dungeon script's size, next to +52 =
// its memory), 0 without the dungeon task.
s32 K_FldDungeon_GetScrSize(EEContext& ctx) {
    guest::enter(ctx, 3);
    u64 v0 = lw_gp(ctx, kGpDungeonTask);
    if (v0 != 0) {
        guest::charge(ctx, 2);
        v0 = lw(ctx, lw(ctx, v0, static_cast<s32>(kTaskWork)), 56);
    } else {
        guest::charge(ctx, 3);
    }
    guest::charge(ctx, 2);
    S(ctx, kV0, v0);
    return static_cast<s32>(v0);
}

// 0x1C0070 sub_1C0070 [K_FldDungeon_GetFloorKindScale]: $f0 = 2.0 when the floor kind (dungeon work +40, 0 without
// the task) is 1 or 3, else 1.0 (26_field.md 6.3). Leaves the kind in $v1 and the last constant in $v0.
u32 sub_1C0070(EEContext& ctx) {
    guest::enter(ctx, 5);
    ctx.fpr[0] = 0x3F800000u;  // lui v0, 0x3F80; mtc1 v0, $f0
    const u64 task = lw_gp(ctx, kGpDungeonTask);
    u64 v1 = 0;
    S(ctx, kV0, task);
    if (task != 0) {
        guest::charge(ctx, 2);
        const u64 work = lw(ctx, task, static_cast<s32>(kTaskWork));
        S(ctx, kV0, work);
        v1 = lw(ctx, work, 40);
    } else {
        guest::charge(ctx, 3);
    }
    S(ctx, kV1, v1);
    guest::charge(ctx, 3);
    S(ctx, kV0, 3);
    bool doubled = v1 == 3;
    if (!doubled) {
        guest::charge(ctx, 3);
        S(ctx, kV0, 1);
        doubled = v1 == 1;
        if (!doubled) guest::charge(ctx, 2);
    }
    if (doubled) {
        guest::charge(ctx, 2);
        S(ctx, kV0, sx(0x40000000u));
        ctx.fpr[0] = 0x40000000u;
    }
    guest::charge(ctx, 2);
    return ctx.fpr[0];
}

// 0x1C03B0 sub_1C03B0 [K_FldDungeon_IsRequestDone](request): 1 for no request, else H_Cdvd_IsFileLoaded(request) != 0
// (the dungeon's file requests polled by the field root). 16-byte frame, $ra at 0.
u32 sub_1C03B0(EEContext& ctx, u64 req) {
    guest::enter(ctx, 4);
    Frame f(ctx, 16, 0, 15);
    u64 v0;
    if (req != 0) {
        guest::charge(ctx, 3);
        v0 = b2u(jal(ctx, 0x1C03CCu, &rg::fn_H_Cdvd_IsFileLoaded_001016b0) != 0);
    } else {
        guest::charge(ctx, 3);
        v0 = 1;
    }
    S(ctx, kV0, v0);
    guest::charge(ctx, 4);
    return a32(v0);
}

// 0x1C00D0 sub_1C00D0 [K_FldDungeon_StopFloorEffect]: with a dungeon task whose work +44 (the floor's EPL) is set,
// sub_1A9400(work +44, work +48 = the instance sub_1C0110 started). 16-byte frame.
void sub_1C00D0(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 15);
    u64 v1 = lw_gp(ctx, kGpDungeonTask);
    S(ctx, kV1, v1);
    if (v1 != 0) {
        guest::charge(ctx, 4);
        v1 = lw(ctx, v1, static_cast<s32>(kTaskWork));
        S(ctx, kV1, v1);
        const u64 a0 = lw(ctx, v1, 44);
        S(ctx, kA0, a0);
        if (a0 != 0) {
            guest::charge(ctx, 3);
            S(ctx, kA1, lw(ctx, v1, 48));
            jal(ctx, 0x1C00F8u, &rg::fn_sub_1A9400_001a9400);
        }
    }
    guest::charge(ctx, 4);
}

// 0x1C0110 sub_1C0110 [K_FldDungeon_StartFloorEffect]: with the floor's EPL at dungeon work +44, a zeroed 12-byte
// position at frame +32 (the inlined byte-clear loop) and work +48 = sub_1A91B0(epl, &pos). 48-byte frame: $ra at
// 16, $s0 (the work) at 0.
void sub_1C0110(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 48, 16, kS0);
    u64 v1 = lw_gp(ctx, kGpDungeonTask);
    S(ctx, kV1, v1);
    if (v1 != 0) {
        guest::charge(ctx, 4);
        const u64 s0 = lw(ctx, v1, static_cast<s32>(kTaskWork));
        S(ctx, kS0, s0);
        v1 = lw(ctx, s0, 44);
        S(ctx, kV1, v1);
        if (v1 != 0) {
            guest::charge(ctx, 4);
            u64 p = addu(f.sp(), 32);  // $v1
            u64 n = 12;                // $v0
            S(ctx, kV1, p);
            S(ctx, kV0, n);
            if (p != 0) {
                for (;;) {
                    guest::charge(ctx, 7);
                    sb(ctx, p, 0, 0);
                    p = addu(p, 1);
                    n = addu(n, static_cast<u64>(-1));
                    S(ctx, kV1, p);
                    S(ctx, kV0, n);
                    if (n == 0) break;
                    guest::backedge(ctx);
                }
            }
            guest::charge(ctx, 5);
            S(ctx, kA0, lw(ctx, s0, 44));
            S(ctx, kA1, addu(f.sp(), 32));
            const u64 v0 = jal(ctx, 0x1C016Cu, &rg::fn_sub_1A91B0_001a91b0);
            sw(ctx, s0, 48, v0);
        }
    }
    guest::charge(ctx, 5);
}

// =====================================================================================================================
// The field event task's helpers (k_event.c)
// =====================================================================================================================

// 0x001C2000 sub_1C2000 -- 16 bytes; leaf frame (no stack)
// 0x1C2000 sub_1C2000 [K_FldTWall_SetTarget](task, value): work +516 (the event task hands the transparent-wall
// control `sField+28` the hero's resource +480).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C2000(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001c2000
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 516);
}

// 0x1C6080 sub_1C6080 [K_FldEvent_IsPadScriptAllowed]: 0 in the scenes where the event task's pad-0x80 header script
// is off -- majors 4..10, 12, 14, 33, 39 and the fields 26/51..53, 27/50, 32/1, 32/2, 35/1, 37/1 -- else 1. The
// compare chain of the original: the major in $v1, the record in $a0, the last constant in $a1, the minor in $a2
// (in $a0 with 1 in $v1 for the last test).
u32 sub_1C6080(EEContext& ctx) {
    static constexpr s64 kMajors[] = {4, 5, 6, 7, 8, 9, 10, 12, 14, 33, 39};
    static constexpr s64 kFields[][2] = {{26, 51}, {26, 52}, {26, 53}, {27, 50}, {32, 1}, {32, 2}, {35, 1}};
    guest::enter(ctx, 6);
    S(ctx, kV0, 1);
    const u64 rec = lw_gp(ctx, kGpSceneIds);
    const u64 major = lw(ctx, rec, 0);
    S(ctx, kA0, rec);
    S(ctx, kV1, major);
    bool off = false;
    for (std::size_t k = 0; k < sizeof kMajors / sizeof kMajors[0] && !off; ++k) {
        if (k != 0) guest::charge(ctx, 3);
        S(ctx, kA1, static_cast<u64>(kMajors[k]));
        off = sgn(major) == kMajors[k];
    }
    for (std::size_t k = 0; k < sizeof kFields / sizeof kFields[0] && !off; ++k) {
        guest::charge(ctx, 3);
        S(ctx, kA1, static_cast<u64>(kFields[k][0]));
        if (sgn(major) != kFields[k][0]) continue;
        guest::charge(ctx, 4);
        const u64 minor = lw(ctx, rec, 4);
        S(ctx, kA2, minor);
        S(ctx, kA1, static_cast<u64>(kFields[k][1]));
        off = sgn(minor) == kFields[k][1];
    }
    if (!off) {
        guest::charge(ctx, 3);
        S(ctx, kA1, 37);
        if (sgn(major) == 37) {
            guest::charge(ctx, 4);
            const u64 minor = lw(ctx, rec, 4);
            S(ctx, kA0, minor);
            S(ctx, kV1, 1);
            off = minor == 1;
        }
    }
    if (off) {
        guest::charge(ctx, 1);
        S(ctx, kV0, 0);
    }
    guest::charge(ctx, 2);
    return off ? 0u : 1u;
}

// 0x001C65E0 sub_1C65E0 -- 320 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1C65E0 sub_1C65E0 [K_FldUnit_IsLevelGapOk](unit): 1 when flag 3173 is set; otherwise avg = the summed +388 of the
// live party units / their count (`div`, HI/LO kept), and the table at 0x6836B0 ({s16 level, s16 gap} rows until
// level -1) is scanned for the first row with level >= avg: the result is 0 when avg - unit[+388] >= that row's gap,
// else 1 (also 1 when no row matches). 48-byte frame: $ra at 32, $s1 = unit, $s0 = the result.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C65E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::enter, hg::jal, hg::ld, hg::lh,
          hg::lq, hg::lw, hg::mflo, hg::sd, hg::si, hg::sll, hg::slt, hg::slti, hg::sltu, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c65e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 1;
    a0 = 3173;
    jal(ctx, 0x1C65FCu, gen::fn_datGetFlag_0016f190);
    a1 = s0;
    if (v0 != a1) {
        // 0x001c661c
        charge(ctx, 7);
        a3 = 0;
        t0 = 0;
        t1 = 0;
        a0 = 0x870000;
        a0 = addiu(a0, 6048);  // &gFldUnitsPc
        for (;;) {
            // 0x001c6684
            charge(ctx, 3);
            v0 = slti(t1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001c6638
            charge(ctx, 8);
            a2 = 0;
            v0 = sll(t1, 3);
            v0 = subu(v0, t1);
            v0 = sll(v0, 6);
            v1 = addu(a0, v0);
            lw(v0, v1, 72);
            if (v0 != 0) {
                // 0x001c6658
                charge(ctx, 3);
                lw(v0, v1, 84);
                if (v0 != 0) {
                    // 0x001c6664
                    charge(ctx, 1);
                    a2 = a1;
                }
            }
            // 0x001c6668
            charge(ctx, 3);
            v0 = sltu(0, a2);
            if (v0 == a1) {
                // 0x001c6674
                charge(ctx, 3);
                lw(v0, v1, 388);
                a3 = addu(a3, v0);
                t0 = addiu(t0, 1);
            }
            // 0x001c6680
            charge(ctx, 1);
            t1 = addiu(t1, 1);
        }
        // 0x001c6690
        charge(ctx, 8);
        div(a3, t0);
        mflo(a2);
        a3 = 0;
        a0 = 0x680000;
        a0 = addiu(a0, 14000);  // "\n"
        v0 = si(-1);
        for (;;) {
            // 0x001c66f0
            charge(ctx, 5);
            a1 = sll(a3, 2);
            v1 = addu(a0, a1);
            lh(v1, v1, 0);
            if (v1 == v0) {
                break;
            }
            backedge(ctx);
            // 0x001c66b0
            charge(ctx, 3);
            at = slt(v1, a2);
            if (at == 0) {
                goto L_001c66bc_12;
            }
            // 0x001c66ec
            charge(ctx, 1);
            a3 = addiu(a3, 1);
        }
    L_001c6704:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x001c6610
        charge(ctx, 3);
        v0 = a1;
    }
    // 0x001c6708 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_001c66bc_12:
    charge(ctx, 9);
    lw(v0, s1, 388);
    v1 = subu(a2, v0);
    v0 = 0x680000;
    v0 = addiu(v0, 14002);  // &0x6836B2
    v0 = addu(v0, a1);
    lh(v0, v0, 0);
    v0 = slt(v1, v0);
    if (v0 == 0) {
        // 0x001c66e0
        charge(ctx, 3);
        s0 = 0;
    }
    goto L_001c6704;
}

// 0x1C7B10 K_FldEvent_IsUnitHero [K_FldEvent_IsUnitHero](unit): unit == gFldUnitsPc (the hero is party unit 0), as a whole
// register compare (`xor`, `sltiu 1`).
u32 K_FldEvent_IsUnitHero(EEContext& ctx, u64 unit) {
    guest::enter(ctx, 6);
    const u64 v0 = b2u(unit == sx(kPcUnits));
    S(ctx, kV0, v0);
    return a32(v0);
}

// 0x001CD650 sub_1CD650 -- 24 bytes; leaf frame (no stack)
// 0x1CD650 sub_1CD650 [K_FldEvent_SetPause](task, value): event work +4 (the event task, the virtual pad and the
// rotate task pause it), nothing for a null task.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1CD650(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001cd650
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001cd658
        charge(ctx, 2);
        lw(v1, a0, 60);
        sw(a1, v1, 4);
    }
    // 0x001cd660 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001CD670 sub_1CD670 -- 24 bytes; leaf frame (no stack)
// 0x1CD670 sub_1CD670 [K_FldEvent_SetWork8](task, value): event work +8 (the enemy-think band), null ignored.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1CD670(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001cd670
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001cd678
        charge(ctx, 2);
        lw(v1, a0, 60);
        sw(a1, v1, 8);
    }
    // 0x001cd680 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001CD690 sub_1CD690 -- 76 bytes; frame 0x10: ra sp+0x0
// 0x1CD690 sub_1CD690 [K_FldEvent_UpdateDrawCmdTask](task): the draw-command task's update: sub_3B2CB0(320, 224, -1,
// 0, 0, work[0], 0, 0) with $f12 = 0.0; returns 0 (keep running). 16-byte frame.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1CD690(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::mtc1, hg::sd, hg::si;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x001cd690
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    mtc1(zero, f12);
    lw(v0, a0, 60);
    a0 = 320;
    a1 = 224;
    a2 = si(-1);
    a3 = 0;
    t0 = 0;
    lw(t1, v0, 0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1CD6C0u, gen::fn_sub_3B2CB0_003b2cb0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001CD790 sub_1CD790 -- 16 bytes; leaf frame (no stack)
// 0x1CD790 sub_1CD790 [K_FldEvent_SetDrawCmdState](task, value): draw-command work +0 (event work +92's task).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1CD790(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001cd790
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 0);
}

// =====================================================================================================================
// The field units (k_unit.c)
// =====================================================================================================================

// 0x001CD870 sub_1CD870 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1CD870 sub_1CD870 [K_FldUnit_FreePcModel](slot): when the party model slot's handle (0x871EA4 + 8 slot) is set,
// sub_3174E0(handle), then the handle and both u16 of the slot are cleared. 48-byte frame: $ra at 32, $s1 = slot * 8,
// $s0 = &handle.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1CD870(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sh,
          hg::sll, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001cd870
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = sll(a0, 3);
    v1 = 0x870000;
    v1 = addiu(v1, 7844);  // &0x871EA4
    s0 = addu(v1, s1);
    lw(a0, s0, 0);
    if (a0 != 0) {
        // 0x001cd89c
        charge(ctx, 11);
        jal(ctx, 0x1CD89Cu, gen::fn_sub_3174E0_003174e0);
        sw(zero, s0, 0);
        v1 = 0x870000;
        v1 = addiu(v1, 7840);  // &0x871EA0
        v1 = addu(v1, s1);
        sh(zero, v1, 0);
        v1 = 0x870000;
        v1 = addiu(v1, 7842);  // &0x871EA2
        v1 = addu(v1, s1);
        sh(zero, v1, 0);
    }
    // 0x001cd8c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x1CD8E0 sub_1CD8E0 [K_FldUnit_InitPcSlots]: for the four party units, +68 = 1 and the model slot (0x871EA0 + 8 i)
// cleared. Registers: i in $t0, 1 in $a3, the two bases in $a1 / $a0, i * 8 in $a2.
void sub_1CD8E0(EEContext& ctx) {
    guest::enter(ctx, 8);
    u64 t0 = 0;
    S(ctx, kT0, t0);
    S(ctx, kA3, 1);
    S(ctx, kA1, sx(kPcUnits));
    S(ctx, kA0, sx(kPcModelSlots));
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(t0) < 4);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        const u64 a2 = sll(t0, 3);
        S(ctx, kA2, a2);
        sw(ctx, addu(sx(kPcUnits), sll(subu(a2, t0), 6)), static_cast<s32>(kUnitActiveFlag), 1);
        const u64 v1 = addu(sx(kPcModelSlots), a2);
        S(ctx, kV1, v1);
        sw(ctx, v1, 4, 0);
        sh(ctx, v1, 0, 0);
        sh(ctx, v1, 2, 0);
        t0 = addu(t0, 1);
        S(ctx, kT0, t0);
    }
    guest::charge(ctx, 2);
}

// 0x1CD940 sub_1CD940 [K_FldUnit_FindFreePc]: the first party unit whose +72 is 0, or 0. Registers: i in $a2, the
// base in $a1, the unit in $a0.
u32 sub_1CD940(EEContext& ctx) {
    guest::enter(ctx, 6);
    u64 v0 = 0;
    u64 a2 = 0;
    S(ctx, kV0, v0);
    S(ctx, kA2, a2);
    S(ctx, kA1, sx(kPcUnits));
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(a2) < 4);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 7);
        const u64 v1 = sll(subu(sll(a2, 3), a2), 6);
        const u64 a0 = addu(sx(kPcUnits), v1);
        S(ctx, kA0, a0);
        const u64 inst = lw(ctx, a0, static_cast<s32>(kUnitInstance));
        S(ctx, kV1, inst);
        if (inst == 0) {
            guest::charge(ctx, 3);
            v0 = a0;
            S(ctx, kV0, v0);
            break;
        }
        guest::charge(ctx, 1);
        a2 = addu(a2, 1);
        S(ctx, kA2, a2);
    }
    guest::charge(ctx, 2);
    return a32(v0);
}

// 0x1CE880 sub_1CE880 [K_FldUnit_RefreshPcAnims]: for every live party unit (+72 and +84 set), each of its five
// animation slots whose entry (model +80 -> +952 + 12 k) is set gets sub_319230(entry, u16 unit[+414 + 2k]).
// 64-byte frame: $ra at 48, $s2 = i, $s1 = k, $s0 = the unit.
void sub_1CE880(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 64, 48, kS2);
    u64 s2 = 0;
    S(ctx, kS2, s2);
    for (;;) {
        guest::charge(ctx, 3);
        u64 more = b2u(sgn(s2) < 4);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        S(ctx, kA1, 0);
        const u64 s0 = unit_addr(ctx, s2, kPcUnits, kV1, kA0, kV1, kS0);
        unit_live(ctx, s0, kV1, kA1);
        guest::charge(ctx, 3);
        const u64 live = b2u(R(ctx, kA1) != 0);
        S(ctx, kV1, live);
        if (live != 0) {
            guest::charge(ctx, 3);
            u64 s1 = 0;
            S(ctx, kS1, s1);
            for (;;) {
                guest::charge(ctx, 3);
                more = b2u(sgn(s1) < 5);
                S(ctx, kV1, more);
                if (more == 0) break;
                guest::backedge(ctx);
                guest::charge(ctx, 8);
                const u64 model = lw(ctx, s0, static_cast<s32>(kUnitModel));
                const u64 a1 = sll(s1, 1);
                S(ctx, kA1, a1);
                const u64 v1 = addu(model, sll(addu(a1, s1), 2));
                S(ctx, kV1, v1);
                const u64 a0 = lw(ctx, v1, 952);
                S(ctx, kA0, a0);
                if (a0 != 0) {
                    guest::charge(ctx, 4);
                    const u64 v0 = addu(s0, a1);
                    S(ctx, kV0, v0);
                    S(ctx, kA1, lhu(ctx, v0, static_cast<s32>(kUnitAnimIds)));
                    jal(ctx, 0x1CE918u, &rg::fn_sub_319230_00319230);
                }
                guest::charge(ctx, 1);
                s1 = addu(s1, 1);
                S(ctx, kS1, s1);
            }
        }
        guest::charge(ctx, 1);
        s2 = addu(s2, 1);
        S(ctx, kS2, s2);
    }
    guest::charge(ctx, 7);
}

namespace {
// One pass of sub_1D0270: kwlnTaskSetFlags(unit[+364], 32, 0) for every unit of the array whose +364 task is set.
void flag_unit_tasks(EEContext& ctx, u32 base, s64 count, u32 jal_pc) {
    u64 s0 = 0;
    S(ctx, kS0, s0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s0) < count);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 9);
        const u64 u = unit_addr(ctx, s0, base, kV1, kA0, kV1, kV1);
        const u64 task = lw(ctx, u, static_cast<s32>(kUnitTask364));
        S(ctx, kA0, task);
        if (task != 0) {
            guest::charge(ctx, 4);
            S(ctx, kA1, 32);
            S(ctx, kA2, 0);
            jal(ctx, jal_pc, &rg::fn_kwlnTaskSetFlags_001956d0);
        }
        guest::charge(ctx, 1);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
}
}  // namespace

// 0x1D0270 sub_1D0270 [K_FldUnit_FlagAllTasks]: kwlnTaskSetFlags(task, 32, 0) on the +364 task of every party unit, then of
// every shadow (callers: the exits and the k_command.c sequence changes). 32-byte frame: $ra at 16, $s0 = i.
void sub_1D0270(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, kS0);
    flag_unit_tasks(ctx, kPcUnits, kPcUnitCount, 0x1D02B4u);
    guest::charge(ctx, 3);
    flag_unit_tasks(ctx, kEcUnits, kEcUnitCount, 0x1D0304u);
    guest::charge(ctx, 5);
}

// 0x1D0E40 sub_1D0E40 [K_FldUnit_GetLiveEcCount]: the live shadow count ($gp-19044).
u32 sub_1D0E40(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u64 v0 = lw_gp(ctx, kGpLiveEcCount);
    S(ctx, kV0, v0);
    return a32(v0);
}

// 0x1D11B0 sub_1D11B0 [K_FldUnit_RecreateEcModels]: for every shadow with an encounter instance, +80 =
// sub_316E00(8, k, 0) with k by its +396 kind: 1 / 5 -> 1, 2 -> 2, 3 -> 4, 4 -> 3 (the compare chain leaves the
// previous constant in $a1); other kinds keep their model. The event task's state 15 runs it after a battle.
// 48-byte frame: $ra at 32, $s1 = i, $s0 = the unit.
void sub_1D11B0(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 48, 32, kS1);
    u64 s1 = 0;
    S(ctx, kS1, s1);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s1) < static_cast<s64>(kEcUnitCount));
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 9);
        const u64 s0 = unit_addr(ctx, s1, kEcUnits, kV1, kA0, kV1, kS0);
        const u64 inst = lw(ctx, s0, static_cast<s32>(kUnitInstance));
        S(ctx, kV1, inst);
        if (inst != 0) {
            guest::charge(ctx, 4);
            const u64 kind = lw(ctx, s0, static_cast<s32>(kUnitModelKind));
            S(ctx, kA0, kind);
            S(ctx, kA1, 3);
            u32 pc = 0;  // the jal of the matching case
            if (kind == 3) {
                guest::charge(ctx, 6);
                S(ctx, kA1, 4);
                pc = 0x1D129Cu;
            } else {
                guest::charge(ctx, 3);
                S(ctx, kV1, 4);
                if (kind == 4) {
                    guest::charge(ctx, 7);  // $a1 stays 3
                    pc = 0x1D127Cu;
                } else {
                    guest::charge(ctx, 3);
                    S(ctx, kA1, 2);
                    if (kind == 2) {
                        guest::charge(ctx, 7);  // $a1 stays 2
                        pc = 0x1D1260u;
                    } else {
                        guest::charge(ctx, 3);
                        S(ctx, kV1, 1);
                        bool one = kind == 1;
                        if (!one) {
                            guest::charge(ctx, 3);
                            S(ctx, kV1, 5);
                            one = kind == 5;
                            if (!one) guest::charge(ctx, 2);
                        }
                        if (one) {
                            guest::charge(ctx, 8);
                            S(ctx, kA1, 1);
                            pc = 0x1D1244u;
                        }
                    }
                }
            }
            if (pc != 0) {
                S(ctx, kA0, 8);
                S(ctx, kA2, 0);
                sw(ctx, s0, static_cast<s32>(kUnitModel), jal(ctx, pc, &rg::fn_sub_316E00_00316e00));
            }
        }
        guest::charge(ctx, 1);
        s1 = addu(s1, 1);
        S(ctx, kS1, s1);
    }
    guest::charge(ctx, 6);
}

// 0x1D12D0 sub_1D12D0 [K_FldUnit_AreEcModelsReady]: 0 as soon as a shadow with an encounter instance has a model that
// sub_316F70 reports not ready, else 1. 32-byte frame: $ra at 16, $s0 = i.
u32 sub_1D12D0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, kS0);
    u64 s0 = 0;
    S(ctx, kS0, s0);
    u64 v0;
    for (;;) {
        guest::charge(ctx, 3);
        v0 = b2u(sgn(s0) < static_cast<s64>(kEcUnitCount));
        S(ctx, kV0, v0);
        if (v0 == 0) {
            guest::charge(ctx, 1);
            v0 = 1;
            break;
        }
        guest::backedge(ctx);
        guest::charge(ctx, 9);
        const u64 u = unit_addr(ctx, s0, kEcUnits, kV0, kV1, kV0, kV1);
        v0 = lw(ctx, u, static_cast<s32>(kUnitInstance));
        S(ctx, kV0, v0);
        if (v0 != 0) {
            guest::charge(ctx, 5);
            S(ctx, kA0, lw(ctx, u, static_cast<s32>(kUnitModel)));
            if (jal(ctx, 0x1D1310u, &rg::fn_sub_316F70_00316f70) == 0) {
                guest::charge(ctx, 3);
                v0 = 0;
                break;
            }
        }
        guest::charge(ctx, 1);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
    S(ctx, kV0, v0);
    guest::charge(ctx, 5);
    return a32(v0);
}

// 0x1D1780 sub_1D1780 [K_FldUnit_ResetPcs](arg): sub_1D1640(unit, 0) for party units 1..3, and unit 0 (the hero)
// too when arg == 0 (`sltu v1, zero, a0; xori s0, v1, 1` gives the first index). 32-byte frame: $ra at 16, $s0 = i.
void sub_1D1780(EEContext& ctx, u64 arg) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 16, kS0);
    const u64 v1 = b2u(arg != 0);
    S(ctx, kV1, v1);
    u64 s0 = v1 ^ 1u;
    S(ctx, kS0, s0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s0) < 4);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        unit_addr(ctx, s0, kPcUnits, kV0, kV1, kV0, kA0);
        S(ctx, kA1, 0);
        jal(ctx, 0x1D17B8u, &rg::fn_sub_1D1640_001d1640);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
    guest::charge(ctx, 5);
}

// 0x1D17F0 sub_1D17F0 [K_FldUnit_ResetEcs](arg): sub_1D1640(unit, arg) for the 24 shadows. 48-byte frame: $ra at 32,
// $s1 = arg, $s0 = i.
void sub_1D17F0(EEContext& ctx, u64 arg) {
    guest::enter(ctx, 8);
    Frame f(ctx, 48, 32, kS1);
    S(ctx, kS1, arg);
    u64 s0 = 0;
    S(ctx, kS0, s0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s0) < static_cast<s64>(kEcUnitCount));
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        unit_addr(ctx, s0, kEcUnits, kV0, kV1, kV0, kA0);
        S(ctx, kA1, arg);
        jal(ctx, 0x1D182Cu, &rg::fn_sub_1D1640_001d1640);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
    guest::charge(ctx, 6);
}

// 0x1D1860 sub_1D1860 [K_FldUnit_SetPcVisible](arg): sub_19C2F0(resource[+484], arg) for every live party unit.
// 48-byte frame: $ra at 32, $s1 = arg, $s0 = i.
void sub_1D1860(EEContext& ctx, u64 arg) {
    guest::enter(ctx, 8);
    Frame f(ctx, 48, 32, kS1);
    S(ctx, kS1, arg);
    u64 s0 = 0;
    S(ctx, kS0, s0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s0) < 4);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        S(ctx, kA2, 0);
        const u64 a1 = unit_addr(ctx, s0, kPcUnits, kV1, kA0, kV1, kA1);
        unit_live(ctx, a1, kV1, kA2);
        guest::charge(ctx, 4);
        const u64 live = b2u(R(ctx, kA2) != 0);
        S(ctx, kA0, live);
        S(ctx, kV1, 1);
        if (live == 1) {
            guest::charge(ctx, 5);
            const u64 v0 = lw(ctx, a1, static_cast<s32>(kUnitResource));
            S(ctx, kV0, v0);
            S(ctx, kA0, lw(ctx, v0, 484));
            S(ctx, kA1, arg);
            jal(ctx, 0x1D18D4u, &rg::fn_sub_19C2F0_0019c2f0);
        }
        guest::charge(ctx, 1);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
    guest::charge(ctx, 6);
}

namespace {
// The body head shared by sub_1D1910 / sub_1D19D0 / sub_1D1B60 / sub_1D1C20 (block 10 + the live test + block 4):
// `move a1, zero; <unit in a0>; live -> a1; sltu v1, zero, a1; li a3, 1`; returns the unit when live.
bool anim_unit_live(EEContext& ctx, u64 i, u32 base) {
    guest::charge(ctx, 10);
    S(ctx, kA1, 0);
    const u64 a0 = unit_addr(ctx, i, base, kV1, kA0, kV1, kA0);
    unit_live(ctx, a0, kV1, kA1);
    guest::charge(ctx, 4);
    const u64 live = b2u(R(ctx, kA1) != 0);
    S(ctx, kV1, live);
    S(ctx, kA3, 1);
    return live == 1;
}

// sub_1D19D0 / sub_1D1B60 / sub_1D1C20: per live unit, +380 = 0 and sub_1A60D0(0, unit[+80], alpha) (block 12).
// 32-byte frame: $ra at 16, $s0 = i.
void stop_anims_clear_first(EEContext& ctx, u32 base, s64 count, u64 alpha, u32 jal_pc) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, kS0);
    u64 s0 = 0;
    S(ctx, kS0, s0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s0) < count);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        if (anim_unit_live(ctx, s0, base)) {
            guest::charge(ctx, 12);
            const u64 v0 = unit_addr(ctx, s0, base, kV0, kV1, kV0, kV0);
            sw(ctx, v0, static_cast<s32>(kUnitTask380), 0);
            S(ctx, kA0, 0);
            S(ctx, kA1, lw(ctx, v0, static_cast<s32>(kUnitModel)));
            S(ctx, kA2, alpha);
            jal(ctx, jal_pc, &rg::fn_sub_1A60D0_001a60d0);
        }
        guest::charge(ctx, 1);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
    guest::charge(ctx, 5);
}

// sub_1D1A90 / sub_1D1CE0: 1 when no live unit's +380 task still exists; a stale handle (kwlnTaskExists != 1) is
// cleared. 64-byte frame: $ra at 48, $s2 = &unit[+380], $s1 = i, $s0 = the result.
u32 unit_tasks_done(EEContext& ctx, u32 base, s64 count, u32 jal_pc) {
    guest::enter(ctx, 9);
    Frame f(ctx, 64, 48, kS2);
    u64 s0 = 1;
    u64 s1 = 0;
    S(ctx, kS0, s0);
    S(ctx, kS1, s1);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s1) < count);
        S(ctx, kV0, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        S(ctx, kA1, 0);
        const u64 a0 = unit_addr(ctx, s1, base, kV0, kV1, kV0, kA0);
        unit_live(ctx, a0, kV0, kA1);
        guest::charge(ctx, 4);
        const u64 live = b2u(R(ctx, kA1) != 0);
        S(ctx, kV1, live);
        S(ctx, kV0, 1);
        if (live == 1) {
            guest::charge(ctx, 4);
            const u64 s2 = addu(a0, kUnitTask380);
            S(ctx, kS2, s2);
            const u64 task = lw(ctx, a0, static_cast<s32>(kUnitTask380));
            S(ctx, kA0, task);
            if (task != 0) {
                guest::charge(ctx, 5);
                const u64 exists = jal(ctx, jal_pc, &rg::fn_kwlnTaskExists_00195460);
                S(ctx, kV1, 1);
                if (exists == 1) {
                    guest::charge(ctx, 3);
                    s0 = 0;
                    S(ctx, kS0, s0);
                } else {
                    guest::charge(ctx, 1);
                    sw(ctx, s2, 0, 0);
                }
            }
        }
        guest::charge(ctx, 1);
        s1 = addu(s1, 1);
        S(ctx, kS1, s1);
    }
    guest::charge(ctx, 8);
    S(ctx, kV0, s0);
    return a32(s0);
}
}  // namespace

// 0x1D1910 sub_1D1910 [K_FldUnit_StopPcAnims]: per live party unit, sub_1A60D0(0, unit[+80], 0), then +380 = 0.
// 48-byte frame: $ra at 32, $s1 = the unit, $s0 = i.
void sub_1D1910(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 48, 32, kS1);
    u64 s0 = 0;
    S(ctx, kS0, s0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(s0) < 4);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        if (anim_unit_live(ctx, s0, kPcUnits)) {
            guest::charge(ctx, 12);
            const u64 s1 = unit_addr(ctx, s0, kPcUnits, kV0, kV1, kV0, kS1);
            S(ctx, kA0, 0);
            S(ctx, kA1, lw(ctx, s1, static_cast<s32>(kUnitModel)));
            S(ctx, kA2, 0);
            jal(ctx, 0x1D1998u, &rg::fn_sub_1A60D0_001a60d0);
            sw(ctx, s1, static_cast<s32>(kUnitTask380), 0);
        }
        guest::charge(ctx, 1);
        s0 = addu(s0, 1);
        S(ctx, kS0, s0);
    }
    guest::charge(ctx, 6);
}

// 0x1D19D0 sub_1D19D0 [K_FldUnit_StopPcAnims255]: per live party unit, +380 = 0, then sub_1A60D0(0, unit[+80], 255).
void sub_1D19D0(EEContext& ctx) { stop_anims_clear_first(ctx, kPcUnits, kPcUnitCount, 255, 0x1D1A58u); }

// 0x1D1A90 sub_1D1A90 [K_FldUnit_ArePcTasksDone]: 0 while a live party unit's +380 task exists (stale handles
// cleared), else 1.
u32 sub_1D1A90(EEContext& ctx) { return unit_tasks_done(ctx, kPcUnits, kPcUnitCount, 0x1D1B0Cu); }

// 0x1D1B60 sub_1D1B60 [K_FldUnit_StopEcAnims]: sub_1D19D0's loop over the 24 shadows with alpha 0.
void sub_1D1B60(EEContext& ctx) { stop_anims_clear_first(ctx, kEcUnits, kEcUnitCount, 0, 0x1D1BE8u); }

// 0x1D1C20 sub_1D1C20 [K_FldUnit_StopEcAnims255]: the same with alpha 255.
void sub_1D1C20(EEContext& ctx) { stop_anims_clear_first(ctx, kEcUnits, kEcUnitCount, 255, 0x1D1CA8u); }

// 0x1D1CE0 sub_1D1CE0 [K_FldUnit_AreEcTasksDone]: sub_1D1A90 for the shadows.
u32 sub_1D1CE0(EEContext& ctx) { return unit_tasks_done(ctx, kEcUnits, kEcUnitCount, 0x1D1D5Cu); }

// =====================================================================================================================
// The enemy pop scheduler (k_unit.c, K_Unit_UpdateEnemyPopSchedulerTask [K_Unit_UpdateEnemyPopSchedulerTask])
// =====================================================================================================================

// 0x001D3790 sub_1D3790 -- 92 bytes; leaf frame (no stack)
// 0x1D3790 sub_1D3790 [K_Unit_IsPopSchedulerIdle](task): 1 in field 14/5 (the scheduler never runs there) or when the
// work state is 2 (respawning), else 0. The work stays in $a1, the record in $a0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D3790(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x001d3790
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a1, a0, 60);
    lw(a0, gp, -22448);  // 0x7CD540
    lw(v1, a0, 0);
    v0 = 14;
    if (v1 == v0) {
        // 0x001d37a8
        charge(ctx, 4);
        lw(v1, a0, 4);
        v0 = 5;
        if (v1 != v0) {
            goto L_001d37c4;
        }
        // 0x001d37b8
        charge(ctx, 3);
        v0 = 1;
        // 0x001d37e4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_001d37c4:
    charge(ctx, 4);
    lw(v1, a1, 0);
    v0 = 2;
    if (v1 != v0) {
        // 0x001d37e0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001d37d4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001d37e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001D37F0 sub_1D37F0 -- 24 bytes; leaf frame (no stack)
// 0x1D37F0 sub_1D37F0 [K_Unit_SetPopSchedulerPause](task, value): work +4 (null task ignored).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D37F0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001d37f0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001d37f8
        charge(ctx, 2);
        lw(v1, a0, 60);
        sw(a1, v1, 4);
    }
    // 0x001d3800 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001D3810 sub_1D3810 -- 24 bytes; leaf frame (no stack)
// 0x1D3810 sub_1D3810 [K_Unit_SetPopSchedulerPause2](task, value): work +8 (null task ignored).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D3810(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001d3810
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001d3818
        charge(ctx, 2);
        lw(v1, a0, 60);
        sw(a1, v1, 8);
    }
    // 0x001d3820 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001D38A0 sub_1D38A0 -- 48 bytes; leaf frame (no stack)
// 0x1D38A0 sub_1D38A0 [K_Unit_GetReaperTimeLeft](task): the Reaper limit +12 minus the elapsed seconds (+16 frames
// / 30, `divu`: HI/LO kept), not below 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D38A0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::divu, hg::enter, hg::i64, hg::lw, hg::mflo, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x001d38a0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(a0, v0, 12);
    lw(v1, v0, 16);
    v0 = 30;
    divu(v1, v0);
    mflo(v0);
    v0 = subu(a0, v0);
    if (i64(v0) < 0) {
        // 0x001d38c4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001d38c8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// =====================================================================================================================
// The camera (k_fldCamera.c)
// =====================================================================================================================

// 0x1D5130 sub_1D5130 [K_FldCamera_SetGlobalWord](value): $gp-27176.
void sub_1D5130(EEContext& ctx, u64 value) {
    guest::enter(ctx, 3);
    sw(ctx, R(ctx, GPR_GP), kGpCameraWord, value);
}

// 0x001D5C00 sub_1D5C00 -- 16 bytes; leaf frame (no stack)
// 0x1D5C00 sub_1D5C00 [K_FldCamera_GetMode](task): camera work +8 (0 / 2 / 5 follow modes, 26_field.md 4.4).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D5C00(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001d5c00
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 8);
}

// 0x001D5E10 sub_1D5E10 -- 20 bytes; leaf frame (no stack)
// 0x1D5E10 sub_1D5E10 [K_FldCamera_GetFrameMatrix](task): the camera's RW frame (work +12) + 64.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D5E10(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001d5e10
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 12);
    v0 = addiu(v0, 64);
}

// 0x001D5F30 sub_1D5F30 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1D5F30 sub_1D5F30 [K_FldCamera_SetTarget](task, id): for a character resource id (type (id & 0xFFFF) >> 10 == 1),
// work +204 = MT_Scene_GetRes(id). 32-byte frame: $ra at 16, $s0 = the work.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D5F30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sra, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001d5f30
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    a0 = a1 & 0xFFFF;
    v1 = 0xF0000;
    v1 = v1 | 0xFC00;
    v1 = a0 & v1;
    a0 = sra(v1, 10);
    v1 = 1;
    if (a0 == v1) {
        // 0x001d5f60
        charge(ctx, 4);
        a0 = a1;
        jal(ctx, 0x1D5F64u, gen::fn_sub_3B5D10_003b5d10);
        sw(v0, s0, 204);
    }
    // 0x001d5f70 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// =====================================================================================================================
// The encounter task (k_battle.c)
// =====================================================================================================================

// 0x1D8C60 sub_1D8C60 [K_Battle_SetAllPause](value): work +8 of every live "battle kosaka" task (0x875A40[3]).
// Registers: i in $a2, the table in $a1.
void sub_1D8C60(EEContext& ctx, u64 value) {
    guest::enter(ctx, 5);
    u64 a2 = 0;
    S(ctx, kA2, a2);
    S(ctx, kA1, sx(kBattleKosakaTasks));
    for (;;) {
        guest::charge(ctx, 3);
        const u64 more = b2u(sgn(a2) < 3);
        S(ctx, kV1, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 5);
        u64 v1 = lw(ctx, addu(sx(kBattleKosakaTasks), sll(a2, 2)), 0);
        S(ctx, kV1, v1);
        if (v1 != 0) {
            guest::charge(ctx, 2);
            v1 = lw(ctx, v1, static_cast<s32>(kTaskWork));
            S(ctx, kV1, v1);
            sw(ctx, v1, 8, value);
        }
        guest::charge(ctx, 1);
        a2 = addu(a2, 1);
        S(ctx, kA2, a2);
    }
    guest::charge(ctx, 2);
}

// 0x001D8D50 sub_1D8D50 -- 16 bytes; leaf frame (no stack)
// 0x1D8D50 sub_1D8D50 [K_Battle_GetPartyCount](task): encounter work +16.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D8D50(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001d8d50
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 16);
}

// 0x001D8D60 sub_1D8D60 -- 24 bytes; leaf frame (no stack)
// 0x1D8D60 sub_1D8D60 [K_Battle_GetPartyUnit](task, n): encounter work +24 + 4n (the party field units).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D8D60(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001d8d60
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    v0 = sll(a1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 24);
}

// =====================================================================================================================
// Footstep, field effects, the virtual pad, the NPC-placement lists
// =====================================================================================================================

// 0x001D9FD0 sub_1D9FD0 -- 40 bytes; leaf frame (no stack)
// 0x1D9FD0 sub_1D9FD0 [K_Footstep_IsActive](task): 1 for no task, else work state > 0 (signed).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D9FD0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::slt;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001d9fd0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001d9fe4
        charge(ctx, 3);
        lw(v0, a0, 60);
        lw(v0, v0, 0);
        v0 = slt(0, v0);
    } else {
        // 0x001d9fd8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001d9ff0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001DA000 sub_1DA000 -- 32 bytes; leaf frame (no stack)
// 0x1DA000 sub_1DA000 [K_Footstep_SetUnit](task, value): work +4 = value, +12 = $gp-19432; null task ignored.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1DA000(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x001da000
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x001da008
        charge(ctx, 4);
        lw(a0, a0, 60);
        sw(a1, a0, 4);
        lw(v1, gp, -19432);  // g_kwlnFrameCounterB
        sw(v1, a0, 12);
    }
    // 0x001da018 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001DD5E0 sub_1DD5E0 -- 16 bytes; leaf frame (no stack)
// 0x1DD5E0 sub_1DD5E0 [K_FldEffect_SetState](task, value): work +0 (the effect tasks sub_1DD460 creates).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1DD5E0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001dd5e0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 0);
}

// 0x001DD5F0 sub_1DD5F0 -- 16 bytes; leaf frame (no stack)
// 0x1DD5F0 sub_1DD5F0 [K_FldEffect_SetModel](task, value): work +548 (a field unit's model, sub_1D0110 / sub_1D1360).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1DD5F0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001dd5f0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 548);
}

// 0x1E13C0 sub_1E13C0 [K_VPad_GetTurnSpeed]: $f0 = the f32 at $gp-19004, or the one at $gp-19136 when it is <= 0.0
// (`c.le.s` into FCR31.C; $f1 = 0.0).
u32 sub_1E13C0(EEContext& ctx) {
    guest::enter(ctx, 6);
    ctx.fpr[0] = guest::load<u32>(ctx, a32(gp(ctx, kGpPadTurnSpeed)));
    ctx.fpr[1] = 0;
    rt::c_le_s(ctx, 0, 1);
    if (rt::cop1_cond(ctx)) {
        guest::charge(ctx, 1);
        ctx.fpr[0] = guest::load<u32>(ctx, a32(gp(ctx, kGpPadTurnDefault)));
    }
    guest::charge(ctx, 2);
    return ctx.fpr[0];
}

// 0x001E1820 sub_1E1820 -- 24 bytes; leaf frame (no stack)
// 0x1E1820 sub_1E1820 [K_VPad_IsMode1](task): work +64 == 1 (`xori 1`, `sltiu 1` on the whole register).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1E1820(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001e1820
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 64);
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
}

// 0x1E1840 sub_1E1840 [K_Npc_GetListHead]: &$gp-19000 (the NPC-placement list head).
u32 sub_1E1840(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u64 v0 = gp(ctx, kGpNpcList);
    S(ctx, kV0, v0);
    return a32(v0);
}

// 0x1E2810 sub_1E2810 [K_Npc_FindById](id): the node of the $gp-19000 list whose u16 +8 is id & 0xFFFF, or 0.
u32 sub_1E2810(EEContext& ctx, u64 id) { return find_in_list(ctx, id, kGpNpcList, 8, 108); }
// 0x1E29E0 sub_1E29E0 [K_Obj_FindById](id): the node of the $gp-18996 list whose u16 +80 is id & 0xFFFF, or 0.
u32 sub_1E29E0(EEContext& ctx, u64 id) { return find_in_list(ctx, id, kGpObjList, 80, 88); }

}  // namespace p3fes::game

// =====================================================================================================================
// The recompiled program's entry points (recomp/generated/functions.h signatures): the arguments come from $a0..$a2;
// every hand version writes $v0 (and the other registers) itself.
// =====================================================================================================================
namespace p3fes::recomp_gen {
namespace {
u64 A(const p3fes::EEContext& ctx, unsigned i) { return p3fes::ee::core::gpr64(ctx, GPR_A0 + i); }
}  // namespace
namespace g = p3fes::game;
void fn_K_FldDungeon_GetScrSize_001c0010(p3fes::EEContext& ctx) { g::K_FldDungeon_GetScrSize(ctx); }
void fn_sub_1C0070_001c0070(p3fes::EEContext& ctx) { g::sub_1C0070(ctx); }
void fn_sub_1C03B0_001c03b0(p3fes::EEContext& ctx) { g::sub_1C03B0(ctx, A(ctx, 0)); }
void fn_sub_1C00D0_001c00d0(p3fes::EEContext& ctx) { g::sub_1C00D0(ctx); }
void fn_sub_1C0110_001c0110(p3fes::EEContext& ctx) { g::sub_1C0110(ctx); }
void fn_sub_1C6080_001c6080(p3fes::EEContext& ctx) { g::sub_1C6080(ctx); }
void fn_K_FldEvent_IsUnitHero_001c7b10(p3fes::EEContext& ctx) { g::K_FldEvent_IsUnitHero(ctx, A(ctx, 0)); }
void fn_sub_1CD8E0_001cd8e0(p3fes::EEContext& ctx) { g::sub_1CD8E0(ctx); }
void fn_sub_1CD940_001cd940(p3fes::EEContext& ctx) { g::sub_1CD940(ctx); }
void fn_sub_1CE880_001ce880(p3fes::EEContext& ctx) { g::sub_1CE880(ctx); }
void fn_sub_1D0270_001d0270(p3fes::EEContext& ctx) { g::sub_1D0270(ctx); }
void fn_sub_1D0E40_001d0e40(p3fes::EEContext& ctx) { g::sub_1D0E40(ctx); }
void fn_sub_1D11B0_001d11b0(p3fes::EEContext& ctx) { g::sub_1D11B0(ctx); }
void fn_sub_1D12D0_001d12d0(p3fes::EEContext& ctx) { g::sub_1D12D0(ctx); }
void fn_sub_1D1780_001d1780(p3fes::EEContext& ctx) { g::sub_1D1780(ctx, A(ctx, 0)); }
void fn_sub_1D17F0_001d17f0(p3fes::EEContext& ctx) { g::sub_1D17F0(ctx, A(ctx, 0)); }
void fn_sub_1D1860_001d1860(p3fes::EEContext& ctx) { g::sub_1D1860(ctx, A(ctx, 0)); }
void fn_sub_1D1910_001d1910(p3fes::EEContext& ctx) { g::sub_1D1910(ctx); }
void fn_sub_1D19D0_001d19d0(p3fes::EEContext& ctx) { g::sub_1D19D0(ctx); }
void fn_sub_1D1A90_001d1a90(p3fes::EEContext& ctx) { g::sub_1D1A90(ctx); }
void fn_sub_1D1B60_001d1b60(p3fes::EEContext& ctx) { g::sub_1D1B60(ctx); }
void fn_sub_1D1C20_001d1c20(p3fes::EEContext& ctx) { g::sub_1D1C20(ctx); }
void fn_sub_1D1CE0_001d1ce0(p3fes::EEContext& ctx) { g::sub_1D1CE0(ctx); }
void fn_sub_1D5130_001d5130(p3fes::EEContext& ctx) { g::sub_1D5130(ctx, A(ctx, 0)); }
void fn_sub_1D8C60_001d8c60(p3fes::EEContext& ctx) { g::sub_1D8C60(ctx, A(ctx, 0)); }
void fn_sub_1E13C0_001e13c0(p3fes::EEContext& ctx) { g::sub_1E13C0(ctx); }
void fn_sub_1E1840_001e1840(p3fes::EEContext& ctx) { g::sub_1E1840(ctx); }
void fn_sub_1E2810_001e2810(p3fes::EEContext& ctx) { g::sub_1E2810(ctx, A(ctx, 0)); }
void fn_sub_1E29E0_001e29e0(p3fes::EEContext& ctx) { g::sub_1E29E0(ctx, A(ctx, 0)); }
}  // namespace p3fes::recomp_gen
