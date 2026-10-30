// Addressing helpers for the register-level bodies (p3fes_handgen, game/include/p3fes/game/hg_cpu.h) of the kwln task
// kernel (kwln/task.cpp), the RW leaf functions (render/rw_leaves.cpp), the EPL effect player (fx/fx_epl.cpp), the
// CRI ROFS / H_Cdvd file layer (cri/rofs_*.cpp, hcdvd/hcdvd_*.cpp) and the camp menu / date HUD (ui/ui3.cpp), so a
// body says `la(a0, kSomeTable)` or `lw(v0, gp, gp_off(kSomeGlobal))` instead of `a0 = 0x5E0000; a0 = addiu(a0,
// 20120)`. Written by the read_misc readability pass (2026-10-22); header only. Nothing here changes what a body runs:
// the helpers return the values the instructions hold, and la / k_assert run exactly the statements, in order, that
// they stand for. The record offsets of each file live in that file (an anonymous namespace), next to the code that
// reads them. battle_view.h and the read_text pass have the same addressing helpers in their own namespaces; they
// are repeated here so these bodies do not pull in the battle or text headers.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"
#include "p3fes/game/hg_cpu.h"

#include <bit>

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
}  // namespace p3fes::recomp_gen

namespace p3fes::game::mview {

// --- addressing: spell the address a `lui`/`addiu` pair or a `$gp` offset forms ------------------------------------
inline constexpr u32 kGp = 0x7D2CF0u;  // $gp of the whole program (crt0)
// `lw rt, gp_off(va)(gp)`: the signed 16-bit offset of `va` from $gp.
constexpr s32 gp_off(u32 va) noexcept { return static_cast<s32>(va - kGp); }
// `lui rt, hi(va)` + `addiu/lw rt, lo(va)(rt)`: the carry-adjusted upper half (as lui writes it: sign-extended) and the
// signed lower half. hi(0x5E4E98) = 0x5E0000, lo(0x5E4E98) = 20120.
constexpr u64 hi(u32 va) noexcept { return ee::core::lui((va + 0x8000u) >> 16); }
constexpr s32 lo(u32 va) noexcept { return static_cast<s16>(static_cast<u16>(va & 0xFFFFu)); }
static_assert(hi(0x5E4E98u) == 0x5E0000u && lo(0x5E4E98u) == 20120);
static_assert(hi(0x959EECu) == 0x960000u && lo(0x959EECu) == -24852);
// `lui rt, hi16` of an EE single literal (lui + mtc1 builds every such float): the register value lui writes for `f`
// (whose low 16 bits are zero). flt(50.0f) = 0x42480000.
constexpr u64 flt(float f) noexcept { return ee::core::sext32(std::bit_cast<u32>(f)); }
static_assert(flt(1.0f) == 0x3F800000u && flt(50.0f) == 0x42480000u);

// `la r, va`: the adjacent `lui r, hi(va); addiu r, r, lo(va)` pair that loads an address (same block, same order).
inline void la(hg::Gpr r, u32 va) {
    r = hi(va);
    r = hg::addiu(r, lo(va));
}

// K_Assert(file, line) called at `pc`: the original's `lui a0, hi(file); addiu a0, a0, lo(file); addiu a1, $zero, line;
// jal K_Assert` -- the same statements in the same order, one block (its `charge` stays at the call site). K_Assert is
// `jr $ra` in retail, so a failed check continues on the path after it with the same registers.
inline void k_assert(hg::Gpr a0, hg::Gpr a1, u32 pc, u32 file, s32 line) {
    a0 = hi(file);
    a0 = hg::addiu(a0, lo(file));
    a1 = hg::si(line);
    hg::jal(a0.c, pc, ::p3fes::recomp_gen::fn_sub_19D3F0_0019d3f0);
}

}  // namespace p3fes::game::mview
