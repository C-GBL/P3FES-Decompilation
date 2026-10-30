// p3fes::rt -- the adapter API that recompiled code targets (recomp/README.md "Adapter API").
//
// Every statement the emitter produces is a call into this namespace; nothing in the generated
// code open-codes R5900 arithmetic, memory access or extension rules (ADR-0010 section 2 keeps
// the semantics in one place). This header only *declares* the API: the runtime implements it
// over its semantics headers (runtime/include/p3fes/ee/*.h) in a single adapter translation
// unit, and recomp/rt_stubs/rt_stubs.cpp provides aborting stand-ins so generated code can be
// linked for compile tests before the runtime exists.
//
// Conventions
//   * One declaration per decoder Op that changes guest state (recomp/src/r5900_decode.h); the
//     generator maps Op -> name mechanically (recomp/src/emit_cgen.cpp). Names are the census
//     mnemonics with '.' -> '_' and a trailing '_' where the mnemonic is a C++ alternative token
//     (and_, or_, xor_). Pure control flow has no declaration of its own: j / jr / branches
//     become goto, host calls and returns, with conditions from cmp_* / cop*_cond; `break` and
//     undecodable words go through trap().
//   * Register operands are indices: GPR 0..31 (`Reg`), FPR 0..31, VU0 vf 0..31, COP0 0..31.
//     Writes to GPR 0 must be dropped by the implementation; the emitter already omits pure
//     ALU writes to $zero but still emits loads whose destination is $zero (the memory read
//     is a side effect the hardware performs).
//   * 32-bit integer results are sign-extended to 64 bits by the implementation (MIPS rule);
//     the emitter never does arithmetic on register values.
//   * `imm` is the 16-bit immediate sign-extended to int32; `uimm` is zero-extended (andi/ori/
//     xori/lui). Memory ops take (rt, base, imm) and compute base + imm themselves.
//   * `pc` is passed only where the runtime needs it: syscall, traps, link writes, dispatch
//     misses, unreachable words. Memory operations carry no pc (a fault reports the address).
//   * Besides rt:: calls, the generated code touches exactly one field directly:
//     `ctx.cycles += N;` per basic block (virtual time, ADR-0013 §2).
//   * Calls are host calls and `jr $ra` is a host return (N64Recomp model), but the link
//     register is still written (jal / jalr, before the delay slot as on hardware) so that
//     guest-visible state -- $ra saved to the stack, $ra read by the callee -- matches the EE
//     for tracediff. Control flow never depends on the value: a `jr $ra` returns to the host
//     caller even if the guest rewrote $ra (setjmp/longjmp-style code needs HLE).
//   * VU0 macro ops take `dest` as the xyzw mask (bit3 = x ... bit0 = w) exactly as decoded.
//     Broadcast forms carry the component in `bc` (0 x, 1 y, 2 z, 3 w).
//
// This header must compile stand-alone against the runtime/include headers (p3fes/ee_context.h,
// p3fes/ee_memory.h and the ee/*.h semantics headers its inline companion p3fes_recomp_rt_inline.h
// pulls in) under cl.exe and clang-cl at /W4 with C++20 (ADR-0003, ADR-0010 section 5). No GNU
// extensions.
#pragma once

#include "p3fes/ee_context.h"

#include <cstdint>

namespace p3fes::rt {

using Reg = unsigned;               // GPR / FPR / vf / COP0 register index
using Fn = void (*)(EEContext&);    // entry signature of every recompiled function

// ---------------------------------------------------------------------------------------------
// Dispatch, traps and non-code words.

// Function table lookup: returns the recompiled function starting (or entering) at `va`.
// Defined in the generated dispatch.cpp (binary search over the sorted {va, fn} table); on a
// miss it calls lookup_miss() and never returns.
Fn lookup_func(std::uint32_t va);
[[noreturn]] void lookup_miss(std::uint32_t va);                              // hard error naming the VA
[[noreturn]] void bad_entry(std::uint32_t fn_start, std::uint32_t entry_pc);  // entry-dispatch default
// IDA data word reached by fall-through, a chunk end that falls into no function, or a label
// with no instruction. The emitter only places labelled (goto-reached) statements after it.
[[noreturn]] void unreachable(std::uint32_t pc);
[[noreturn]] void missing_function(std::uint32_t va);                         // declared but not emitted (subset builds)

// break (code = the 20-bit code field) and, with --keep-going only, an undecodable word
// (code = the raw word). May return (a debugger-style handler resumes at pc + 4).
enum class Trap : std::uint8_t { Break, Unsupported };
void trap(EEContext& ctx, std::uint32_t pc, Trap kind, std::uint32_t code);
void syscall(EEContext& ctx, std::uint32_t pc);                               // the runtime reads $v1

// Check point (ADR-0013 §2): emitted once per function invocation (at the top of the body, before
// the entry dispatch of entry-form functions) and before every loop back-edge (a local branch,
// jump or switch case whose target address is <= the branch's own address). The runtime compares
// ctx.cycles with its next event deadline and may deliver interrupts or switch guest threads
// (fibers) before returning; guest state must be re-read afterwards. `p3fes_recomp
// --no-check-events` omits the calls. Virtual time itself is advanced by the generated code:
// `ctx.cycles += N;` at the start of every basic block (recomp/README.md "Cycle accounting";
// `--no-cycles` omits it).
void check_events(EEContext& ctx);

// Link writes: gpr[31] = pc + 8 (jal), gpr[rd] = pc + 8 (jalr; not emitted for rd == 0).
void jal(EEContext& ctx, std::uint32_t pc);
void jalr(EEContext& ctx, Reg rd, std::uint32_t pc);

// ---------------------------------------------------------------------------------------------
// Register reads the control-flow emission needs.

std::uint32_t reg32(const EEContext& ctx, Reg r);                             // gpr[r] low 32 bits (jr/jalr target)

// Branch conditions (the emitter evaluates them before the delay slot executes).
bool cmp_eq(const EEContext& ctx, Reg rs, Reg rt);                            // beq / beql
bool cmp_ne(const EEContext& ctx, Reg rs, Reg rt);                            // bne / bnel
bool cmp_lez(const EEContext& ctx, Reg rs);                                   // blez / blezl
bool cmp_gtz(const EEContext& ctx, Reg rs);                                   // bgtz / bgtzl
bool cmp_ltz(const EEContext& ctx, Reg rs);                                   // bltz / bltzl
bool cmp_gez(const EEContext& ctx, Reg rs);                                   // bgez / bgezl
bool cop1_cond(const EEContext& ctx);                                         // FCR31 C bit (bc1t/bc1tl; negated for bc1f/bc1fl)
bool cop0_cond(const EEContext& ctx);                                         // COP0 condition (bc0f branches when false)

// ---------------------------------------------------------------------------------------------
// Integer core (64).

void add(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void addu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void sub(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void subu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void and_(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void or_(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void xor_(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void nor(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void slt(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void sltu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void daddu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void dsubu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void movn(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void movz(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void sllv(EEContext& ctx, Reg rd, Reg rt, Reg rs);                            // shift gpr[rt] by gpr[rs]
void srlv(EEContext& ctx, Reg rd, Reg rt, Reg rs);
void srav(EEContext& ctx, Reg rd, Reg rt, Reg rs);
void dsllv(EEContext& ctx, Reg rd, Reg rt, Reg rs);
void dsrlv(EEContext& ctx, Reg rd, Reg rt, Reg rs);
void mult(EEContext& ctx, Reg rd, Reg rs, Reg rt);                            // EE 3-operand forms; rd may be 0
void multu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void div(EEContext& ctx, Reg rs, Reg rt);
void divu(EEContext& ctx, Reg rs, Reg rt);

void addi(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm);
void addiu(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm);
void daddiu(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm);
void slti(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm);
void sltiu(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm);
void andi(EEContext& ctx, Reg rt, Reg rs, std::uint32_t uimm);
void ori(EEContext& ctx, Reg rt, Reg rs, std::uint32_t uimm);
void xori(EEContext& ctx, Reg rt, Reg rs, std::uint32_t uimm);
void lui(EEContext& ctx, Reg rt, std::uint32_t uimm);

void sll(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void srl(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void sra(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void dsll(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void dsrl(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void dsra(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void dsll32(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void dsrl32(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void dsra32(EEContext& ctx, Reg rd, Reg rt, unsigned sa);

void mfhi(EEContext& ctx, Reg rd);
void mflo(EEContext& ctx, Reg rd);
void mthi(EEContext& ctx, Reg rs);
void mtlo(EEContext& ctx, Reg rs);

void lb(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lbu(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lh(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lhu(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lw(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lwu(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lwl(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void lwr(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void ld(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void ldl(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void ldr(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void sb(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void sh(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void sw(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void swl(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void swr(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void sd(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void sdl(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void sdr(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);

// ---------------------------------------------------------------------------------------------
// COP0 (7).

void mfc0(EEContext& ctx, Reg rt, Reg rd);
void mtc0(EEContext& ctx, Reg rt, Reg rd);
void sync(EEContext& ctx, unsigned stype);                                    // 0x10 = sync.p, else sync.l
void ei(EEContext& ctx);
void di(EEContext& ctx);
void cache(EEContext& ctx, unsigned op, Reg base, std::int32_t imm);
void eret(EEContext& ctx, std::uint32_t pc);                                  // kernel only; the emitter returns after it

// ---------------------------------------------------------------------------------------------
// COP1 FPU (29; the four bc1* branches use cop1_cond above).

void abs_s(EEContext& ctx, Reg fd, Reg fs);
void add_s(EEContext& ctx, Reg fd, Reg fs, Reg ft);
void adda_s(EEContext& ctx, Reg fs, Reg ft);
void c_eq_s(EEContext& ctx, Reg fs, Reg ft);
void c_le_s(EEContext& ctx, Reg fs, Reg ft);
void c_lt_s(EEContext& ctx, Reg fs, Reg ft);
void ctc1(EEContext& ctx, Reg rt, Reg fs);
void cvt_s_w(EEContext& ctx, Reg fd, Reg fs);
void cvt_w_s(EEContext& ctx, Reg fd, Reg fs);
void div_s(EEContext& ctx, Reg fd, Reg fs, Reg ft);
void lwc1(EEContext& ctx, Reg ft, Reg base, std::int32_t imm);
void madd_s(EEContext& ctx, Reg fd, Reg fs, Reg ft);
void madda_s(EEContext& ctx, Reg fs, Reg ft);
void mfc1(EEContext& ctx, Reg rt, Reg fs);
void mov_s(EEContext& ctx, Reg fd, Reg fs);
void msub_s(EEContext& ctx, Reg fd, Reg fs, Reg ft);
void msuba_s(EEContext& ctx, Reg fs, Reg ft);
void mtc1(EEContext& ctx, Reg rt, Reg fs);
void mul_s(EEContext& ctx, Reg fd, Reg fs, Reg ft);
void mula_s(EEContext& ctx, Reg fs, Reg ft);
void neg_s(EEContext& ctx, Reg fd, Reg fs);
void sqrt_s(EEContext& ctx, Reg fd, Reg ft);                                 // the EE reads the ft field
void sub_s(EEContext& ctx, Reg fd, Reg fs, Reg ft);
void suba_s(EEContext& ctx, Reg fs, Reg ft);
void swc1(EEContext& ctx, Reg ft, Reg base, std::int32_t imm);

// ---------------------------------------------------------------------------------------------
// MMI (49).

void div1(EEContext& ctx, Reg rs, Reg rt);
void lq(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);
void madd(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void maddu(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void maddu1(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void mfhi1(EEContext& ctx, Reg rd);
void mflo1(EEContext& ctx, Reg rd);
void mfsa(EEContext& ctx, Reg rd);
void mthi1(EEContext& ctx, Reg rs);
void mtlo1(EEContext& ctx, Reg rs);
void mtsa(EEContext& ctx, Reg rs);
void mtsab(EEContext& ctx, Reg rs, std::int32_t imm);
void mtsah(EEContext& ctx, Reg rs, std::int32_t imm);
void mult1(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void multu1(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void paddh(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void paddub(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void padduw(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void paddw(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pand(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pcgth(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pcpyh(EEContext& ctx, Reg rd, Reg rt);
void pcpyld(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pcpyud(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pexew(EEContext& ctx, Reg rd, Reg rt);
void pextlb(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pextlh(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pextlw(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pextub(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pextuw(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void phmadh(EEContext& ctx, Reg rd, Reg rs, Reg rt);                          // also writes HI/LO; rd may be 0
void pmaxh(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pmfhl(EEContext& ctx, Reg rd, unsigned fmt);                             // fmt: 0 lw, 1 uw, 2 slw, 3 lh, 4 sh
void pminh(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pnor(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void por(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void ppacb(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void ppach(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void ppacw(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void prot3w(EEContext& ctx, Reg rd, Reg rt);
void psllh(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void psrah(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void psraw(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void psrlh(EEContext& ctx, Reg rd, Reg rt, unsigned sa);
void psubb(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void psubw(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void pxor(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void qfsrv(EEContext& ctx, Reg rd, Reg rs, Reg rt);
void sq(EEContext& ctx, Reg rt, Reg base, std::int32_t imm);

// ---------------------------------------------------------------------------------------------
// COP2 transfers (6).

// The VU register is the instruction's fs field (bits 15..11) for all four transfers.
void cfc2(EEContext& ctx, Reg rt, Reg vi, bool interlock);                   // vi: 0..15 integer, 16.. control
void ctc2(EEContext& ctx, Reg rt, Reg vi, bool interlock);
void lqc2(EEContext& ctx, Reg vf, Reg base, std::int32_t imm);
void qmfc2(EEContext& ctx, Reg rt, Reg vf, bool interlock);
void qmtc2(EEContext& ctx, Reg rt, Reg vf, bool interlock);
void sqc2(EEContext& ctx, Reg vf, Reg base, std::int32_t imm);

// ---------------------------------------------------------------------------------------------
// COP2 VU0 macro mode (24 base ops; `_bc` is the broadcast form of the same op).

void vabs(EEContext& ctx, unsigned dest, Reg ft, Reg fs);
void vadd(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vadd_bc(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft, unsigned bc);
void vadda(EEContext& ctx, unsigned dest, Reg fs, Reg ft);
void vadda_bc(EEContext& ctx, unsigned dest, Reg fs, Reg ft, unsigned bc);
void vaddi(EEContext& ctx, unsigned dest, Reg fd, Reg fs);
void vftoi0(EEContext& ctx, unsigned dest, Reg ft, Reg fs);
void vitof0(EEContext& ctx, unsigned dest, Reg ft, Reg fs);
void vmadd(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vmadd_bc(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft, unsigned bc);
void vmadda(EEContext& ctx, unsigned dest, Reg fs, Reg ft);
void vmadda_bc(EEContext& ctx, unsigned dest, Reg fs, Reg ft, unsigned bc);
void vmax(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vmini(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vmove(EEContext& ctx, unsigned dest, Reg ft, Reg fs);
void vmsub(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vmsub_bc(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft, unsigned bc);
void vmsuba(EEContext& ctx, unsigned dest, Reg fs, Reg ft);
void vmsuba_bc(EEContext& ctx, unsigned dest, Reg fs, Reg ft, unsigned bc);
void vmul(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vmul_bc(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft, unsigned bc);
void vmula(EEContext& ctx, unsigned dest, Reg fs, Reg ft);
void vmula_bc(EEContext& ctx, unsigned dest, Reg fs, Reg ft, unsigned bc);
void vmuli(EEContext& ctx, unsigned dest, Reg fd, Reg fs);
void vmulq(EEContext& ctx, unsigned dest, Reg fd, Reg fs);
void vnop(EEContext& ctx);
void vopmsub(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vopmula(EEContext& ctx, unsigned dest, Reg fs, Reg ft);
void vrsqrt(EEContext& ctx, Reg fs, unsigned fsf, Reg ft, unsigned ftf);
void vsqrt(EEContext& ctx, Reg ft, unsigned ftf);
void vsub(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft);
void vsub_bc(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft, unsigned bc);
void vwaitq(EEContext& ctx);

}  // namespace p3fes::rt

// The hot subset above (integer ALU, shifts, immediates, branch conditions, link writes, HI/LO moves,
// aligned RAM loads/stores, check_events) is defined inline for every translation unit here; the rest
// is implemented by runtime/rt/ (or recomp/rt_stubs/ for link checks).
#include "p3fes_recomp_rt_inline.h"
