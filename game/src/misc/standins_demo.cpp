// Phase 5 slice `standins_demo` (game/include/p3fes/game/standins_demo.h): heap users, printf users and file loaders
// the slices skipped until the test stand-ins existed (tests/game/stand_ins.h). tests/game/test_standins_demo.cpp runs
// each against its __recomp body with the stand-ins installed in both runs.
//
// Virtual time per ADR-0013: guest::enter / charge mirror the `ctx.cycles += N` blocks of the recompiled body on the
// executed path, charged where the block starts (before its calls); guest::backedge where the recompiled loop checks.
//
// Register discipline (docs/PHASE5_AGENT_BRIEF.md, wave-6 / wave-7 lessons): each function writes the original
// prologue spills (Frame), keeps in every register the original writes the value it has there at each call, check
// point and return (S(...) where the original assigns it; registers it leaves alone keep what the caller or the last
// callee left), calls through the callee's generated entry point with $ra = the original link (jal) and the
// RenderWare memory functions through the slot word with $v0 = the target and $ra = the `jalr` link (jalr_to).
#include "p3fes/game/standins_demo.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);         // K_Assert(file, line): `jr ra` in retail
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);     // (path, isArchive) -> node
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);    // (node)
void fn_sub_17D800_0017d800(p3fes::EEContext&);         // scenario: 1 = The Answer
void fn_datGetFlag_0016f190(p3fes::EEContext&);         // (id)
void fn_memset_00521408(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_3C4A90_003c4a90(p3fes::EEContext&);         // nm list: release the items
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);     // (parent, name, priority, update, destroy, work)
void fn_sub_244770_00244770(p3fes::EEContext&);
void fn_sub_1FA4F0_001fa4f0(p3fes::EEContext&);         // (member) best equipment after a level-up (battle_result)
void fn_bpIfontSetDigitQuad_00238fd0(p3fes::EEContext&); // (quad, digit, colour) (battle_result)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = p3fes::recomp_gen;

constexpr unsigned kAT = 1, kV0 = 2, kV1 = 3, kA0 = 4, kA1 = 5, kA2 = 6, kA3 = 7, kT0 = 8, kT1 = 9, kS0 = 16, kS1 = 17,
                   kS2 = 18, kS3 = 19, kGP = 28, kSP = 29;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u32 a32(u64 v) { return static_cast<u32>(v); }
s64 sgn(u64 v) { return static_cast<s64>(v); }

// Guest loads / stores through the runtime's own operations (base $zero, the address as the offset), so an unaligned
// or unmapped address stops the run exactly where the recompiled body stops (brief: wave-10 lesson).
u64 lw(EEContext& ctx, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 4))) rt::lw(ctx, 0, 0, static_cast<s32>(va));
    return sx(guest::load<u32>(ctx, va));
}
u64 lbu(EEContext& ctx, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 1))) rt::lbu(ctx, 0, 0, static_cast<s32>(va));
    return guest::load<u8>(ctx, va);
}
u64 lb(EEContext& ctx, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 1))) rt::lb(ctx, 0, 0, static_cast<s32>(va));
    return static_cast<u64>(static_cast<s64>(static_cast<s8>(guest::load<u8>(ctx, va))));
}
u64 lhu(EEContext& ctx, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 2))) rt::lhu(ctx, 0, 0, static_cast<s32>(va));
    return guest::load<u16>(ctx, va);
}
void sw(EEContext& ctx, u64 value, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 4))) rt::sw(ctx, 0, 0, static_cast<s32>(va));
    guest::store<u32>(ctx, va, a32(value));
}
void sh(EEContext& ctx, u64 value, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 2))) rt::sh(ctx, 0, 0, static_cast<s32>(va));
    guest::store<u16>(ctx, va, static_cast<u16>(value));
}
void sb(EEContext& ctx, u64 value, u64 base, s32 off) {
    const u32 va = a32(base) + static_cast<u32>(off);
    if (!(ctx.memory && ctx.memory->fast_ptr(va, 1))) rt::sb(ctx, 0, 0, static_cast<s32>(va));
    guest::store<u8>(ctx, va, static_cast<u8>(value));
}
u64 add32(u64 a, u64 b) { return sx(a32(a) + a32(b)); }
u64 sub32(u64 a, u64 b) { return sx(a32(a) - a32(b)); }
u64 addi(u64 a, s32 imm) { return sx(a32(a) + static_cast<u32>(imm)); }
u64 sll(u64 v, unsigned sa) { return sx(a32(v) << sa); }
u64 slt(u64 a, u64 b) { return sgn(a) < sgn(b) ? 1u : 0u; }
u64 lui(u32 hi16) { return sx(hi16 << 16); }
// `lui rX, hi; addiu rX, rX, lo` of a data address.
u64 la(u32 va) { return sx(va); }

u64 gpw(EEContext& ctx, s32 off) { return lw(ctx, R(ctx, kGP), off); }
void set_gpw(EEContext& ctx, s32 off, u64 v) { sw(ctx, v, R(ctx, kGP), off); }

// `jal fn` with $ra = the original link; returns $v0.
u64 jal(EEContext& ctx, u32 link, guest::Fn fn) {
    rt::jal(ctx, link);
    fn(ctx);
    return R(ctx, kV0);
}
// `lui v0, 0x96; lw v0, slot(v0); jalr v0` at `link`: $v0 = the slot word, the target through rt::lookup_func.
u64 jalr_slot(EEContext& ctx, s32 slot, u32 link) {
    S(ctx, kV0, lui(0x96));
    S(ctx, kV0, lw(ctx, R(ctx, kV0), slot));
    const u32 target = a32(R(ctx, kV0));
    rt::jalr(ctx, GPR_RA, link);
    rt::lookup_func(target)(ctx);
    return R(ctx, kV0);
}
constexpr s32 kSlotMalloc = 376, kSlotFree = 380, kSlotCalloc = 388;  // 0x960178 / 0x96017C / 0x960184

// The prologue `addiu sp, sp, -size; sd ra, ra_off(sp); sq s<n-1>..s0` (s_i at ra_off - 16 * (n - i)); on destruction
// the epilogue (the reloads from the guest stack, `addiu sp, sp, size`).
class Frame {
public:
    Frame(EEContext& ctx, u32 size, u32 ra_off, unsigned nsaved) noexcept : ctx_(ctx), size_(size), ra_off_(ra_off), n_(nsaved) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size_));
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = n_; i-- > 0;) rt::sq(ctx_, kS0 + i, GPR_SP, slot(i));
    }
    ~Frame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = n_; i-- > 0;) rt::lq(ctx_, kS0 + i, GPR_SP, slot(i));
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    s32 slot(unsigned i) const noexcept { return static_cast<s32>(ra_off_ - 16u * (n_ - i)); }
    EEContext& ctx_;
    u32 size_, ra_off_;
    unsigned n_;
};

// `lui a0, hi; addiu a0, a0, lo; addiu a1, zero, line; jal K_Assert` (a 5-cycle block; `jr ra` in retail, so the
// caller continues).
void k_assert(EEContext& ctx, u32 file, u32 line, u32 link) {
    guest::charge(ctx, 5);
    S(ctx, kA0, la(file));
    S(ctx, kA1, line);
    jal(ctx, link, &rg::fn_sub_19D3F0_0019d3f0);
}
// `lw r, off(gp); bnez r, ok; <k_assert>`.
void need_work(EEContext& ctx, unsigned r, s32 gp_off, u32 file, u32 line, u32 link) {
    S(ctx, r, gpw(ctx, gp_off));
    if (R(ctx, r) == 0) k_assert(ctx, file, line, link);
}
// `lw v0, off(s0); nor v0, v0, zero; andi v0, v0, mask; bnez v0, ok; <k_assert>`: the bit must be clear.
void need_clear(EEContext& ctx, s32 off, u32 mask, u32 file, u32 line, u32 link) {
    S(ctx, kV0, lw(ctx, R(ctx, kS0), off));
    S(ctx, kV0, ~R(ctx, kV0) & mask);
    if (R(ctx, kV0) == 0) k_assert(ctx, file, line, link);
}
// The request tail: `lui a0..; addiu a0..; addiu a1, zero, archive; jal H_Cdvd_Request; sw v0, store(s0);
// lw v1, 0(s0); ori v1, v1, bit; sw v1, 0(s0)`.
void request_into(EEContext& ctx, u32 path, u64 archive, u32 link, s32 store, u32 bit) {
    S(ctx, kA0, la(path));
    S(ctx, kA1, archive);
    jal(ctx, link, &rg::fn_H_Cdvd_Request_00100d80);
    sw(ctx, R(ctx, kV0), R(ctx, kS0), store);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 0) | bit);
    sw(ctx, R(ctx, kV1), R(ctx, kS0), 0);
}

}  // namespace

// =====================================================================================================================
// File requests
// =====================================================================================================================

// 0x266A20: op_res.c (K_Assert file 0x68EC78), work gp-18780.
void sub_266A20(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, -18780, 0x68EC78u, 68, 0x266a44u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, -18780));
    need_clear(ctx, 0, 1, 0x68EC78u, 191, 0x266a70u);
    guest::charge(ctx, 5);
    need_clear(ctx, 4, 1, 0x68EC78u, 192, 0x266a98u);
    guest::charge(ctx, 14);
    request_into(ctx, 0x68EC90u, 1, 0x266aacu, 8, 1);
}

// 0x266CB0: the logo twin of sub_266A20 (bit 2, work+72).
void sub_266CB0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, -18780, 0x68EC78u, 68, 0x266cd4u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, -18780));
    need_clear(ctx, 0, 2, 0x68EC78u, 237, 0x266d00u);
    guest::charge(ctx, 5);
    need_clear(ctx, 4, 2, 0x68EC78u, 238, 0x266d28u);
    guest::charge(ctx, 14);
    request_into(ctx, 0x68ECB0u, 1, 0x266d3cu, 72, 2);
}

// 0x21C7F0: bp_res.c (0x68E2E0), work gp-18924; a plain file (`daddu a1, zero, zero`).
void sub_21C7F0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, -18924, 0x68E2E0u, 89, 0x21c814u);
    guest::charge(ctx, 15);
    S(ctx, kS0, gpw(ctx, -18924));
    request_into(ctx, 0x68E350u, 0, 0x21c82cu, 132, 4);
}

// 0x233B20: br_res.c (0x68E6A0), work gp-18916.
void sub_233B20(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, -18916, 0x68E6A0u, 82, 0x233b44u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, -18916));
    need_clear(ctx, 0, 2, 0x68E6A0u, 126, 0x233b70u);
    guest::charge(ctx, 14);
    request_into(ctx, 0x68E710u, 1, 0x233b84u, 16, 2);
}

// 0x2339D0: br_res.c, the result base PAK: The Answer (sub_17D800) picks by flag 752 between two variants, else the
// plain one; work+12, bit 1.
void sub_2339D0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, -18916, 0x68E6A0u, 82, 0x2339f4u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, -18916));
    need_clear(ctx, 0, 1, 0x68E6A0u, 101, 0x233a20u);
    guest::charge(ctx, 4);
    u32 path, link;
    if (jal(ctx, 0x233a28u, &rg::fn_sub_17D800_0017d800) == 0) {
        guest::charge(ctx, 6);
        path = 0x68E6F0u;
        link = 0x233a98u;
    } else {
        guest::charge(ctx, 5);
        S(ctx, kA0, 752);
        if (jal(ctx, 0x233a3cu, &rg::fn_datGetFlag_0016f190) == 0) {
            path = 0x68E6D0u;
            link = 0x233a78u;
        } else {
            path = 0x68E6B0u;
            link = 0x233a58u;
        }
        guest::charge(ctx, 8);
    }
    S(ctx, kA0, la(path));
    S(ctx, kA1, 1);
    jal(ctx, link, &rg::fn_H_Cdvd_Request_00100d80);
    sw(ctx, R(ctx, kV0), R(ctx, kS0), 12);
    guest::charge(ctx, 8);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 0) | 1u);
    sw(ctx, R(ctx, kV1), R(ctx, kS0), 0);
}

// 0x24BE40: brp_res.c (0x68E928), work gp-18876.
void sub_24BE40(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, -18876, 0x68E928u, 57, 0x24be64u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, -18876));
    need_clear(ctx, 4, 1, 0x68E928u, 171, 0x24be90u);
    guest::charge(ctx, 14);
    request_into(ctx, 0x68E940u, 1, 0x24bea4u, 8, 1);
}

// 0x107020: node = H_Cdvd_Request(0x5D3E90, 1) into 0x7E39D0, then H_Cdvd_ReadSync(node).
void sub_107020(EEContext& ctx) {
    guest::enter(ctx, 16);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, la(0x5D3E90u));
    S(ctx, kA1, 1);
    jal(ctx, 0x107034u, &rg::fn_H_Cdvd_Request_00100d80);
    S(ctx, kV1, lui(0x7E));
    sw(ctx, R(ctx, kV0), R(ctx, kV1), 14800);
    S(ctx, kA0, R(ctx, kV0));
    jal(ctx, 0x107048u, &rg::fn_H_Cdvd_ReadSync_001023a0);
}

// =====================================================================================================================
// Heap
// =====================================================================================================================

// 0x2699A0: free(a0) through the RW free slot.
void sub_2699A0(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 16, 0, 0);
    jalr_slot(ctx, kSlotFree, 0x2699b0u);
}

// 0x266600(task): gm_root.c (0x68EC58): gp-18788 must be set; cleared; free(task->+60).
void sub_266600(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 16, 1);
    S(ctx, kS0, R(ctx, kA0));
    need_work(ctx, kV0, -18788, 0x68EC58u, 90, 0x266628u);
    guest::charge(ctx, 11);
    set_gpw(ctx, -18788, 0);
    S(ctx, kA0, lw(ctx, R(ctx, kS0), 60));
    jalr_slot(ctx, kSlotFree, 0x266640u);
}

// 0x3C4430(payload): nmlist.c: block = RwMalloc(payload + 24, 0x40000) (K_Assert 0x6A3DE8 line 96 on 0), zeroed; with a payload
// block->+20 = block + 24; block->+8 = payload + 24. Returns the block.
void sub_3C4430(EEContext& ctx) {
    guest::enter(ctx, 16);
    Frame f(ctx, 64, 48, 3);
    S(ctx, kS2, R(ctx, kA0));
    S(ctx, kS1, addi(R(ctx, kS2), 24));
    S(ctx, kA0, R(ctx, kS1));
    S(ctx, kA1, lui(0x4));
    jalr_slot(ctx, kSlotMalloc, 0x3c445cu);
    S(ctx, kS0, R(ctx, kV0));
    if (R(ctx, kS0) == 0) k_assert(ctx, 0x6A3DE8u, 96, 0x3c447cu);
    guest::charge(ctx, 7);
    S(ctx, kA0, R(ctx, kS0));
    S(ctx, kA1, 0);
    S(ctx, kA2, R(ctx, kS1));
    jal(ctx, 0x3c4490u, &rg::fn_memset_00521408);
    if (R(ctx, kS2) != 0) {
        guest::charge(ctx, 2);
        S(ctx, kV0, addi(R(ctx, kS0), 24));
        sw(ctx, R(ctx, kV0), R(ctx, kS0), 20);
    }
    guest::charge(ctx, 9);
    sw(ctx, R(ctx, kS1), R(ctx, kS0), 8);
    S(ctx, kV0, R(ctx, kS0));
}

// 0x3C45F0(list): sub_3C4A90(list, list + 4); with a list: memset(list, 0, list->+32), free(list).
void sub_3C45F0(EEContext& ctx) {
    guest::enter(ctx, 9);
    Frame f(ctx, 32, 16, 1);
    S(ctx, kS0, R(ctx, kA0));
    S(ctx, kA1, addi(R(ctx, kS0), 4));
    jal(ctx, 0x3c4604u, &rg::fn_sub_3C4A90_003c4a90);
    if (R(ctx, kS0) != 0) {
        guest::charge(ctx, 10);
        S(ctx, kA0, R(ctx, kS0));
        S(ctx, kA1, 0);
        S(ctx, kA2, lw(ctx, R(ctx, kS0), 32));
        jal(ctx, 0x3c4620u, &rg::fn_memset_00521408);
        S(ctx, kA0, R(ctx, kS0));
        jalr_slot(ctx, kSlotFree, 0x3c4634u);
    }
    guest::charge(ctx, 5);
}

// 0x3C4F30(buf): with a buffer: memset(buf, 0, buf->+8), free(buf).
void sub_3C4F30(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    S(ctx, kS0, R(ctx, kA0));
    if (R(ctx, kS0) != 0) {
        guest::charge(ctx, 9);
        S(ctx, kA1, 0);
        S(ctx, kA2, lw(ctx, R(ctx, kS0), 8));
        jal(ctx, 0x3c4f50u, &rg::fn_memset_00521408);
        S(ctx, kA0, R(ctx, kS0));
        jalr_slot(ctx, kSlotFree, 0x3c4f64u);
    }
    guest::charge(ctx, 5);
}

namespace {
// 0x430150 / 0x4310E0: `lw a0, 60(a0)` and free it (a kwln task's destroy callback: the work word).
void free_task_work(EEContext& ctx, u32 link) {
    guest::enter(ctx, 11);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, lw(ctx, R(ctx, kA0), 60));
    jalr_slot(ctx, kSlotFree, link);
}
}  // namespace

void sub_430150(EEContext& ctx) { free_task_work(ctx, 0x430164u); }
void sub_4310E0(EEContext& ctx) { free_task_work(ctx, 0x4310f4u); }

// 0x430180(parent): work = RwCalloc(1, 28, 0x40000); 0 -> return 0; else kwlnTaskCreate(parent, 0x6B44F0, 6311,
// update 0x430060, destroy sub_430150, work), work: +2 = +0 = 0, +4 = 1.0f, +24 = 0; returns the task.
void Y_SMap_CreateStaireDispTask(EEContext& ctx) {
    guest::enter(ctx, 15);
    Frame f(ctx, 48, 32, 2);
    S(ctx, kS1, R(ctx, kA0));
    S(ctx, kA0, 1);
    S(ctx, kA1, 28);
    S(ctx, kA2, lui(0x4));
    jalr_slot(ctx, kSlotCalloc, 0x4301a8u);
    S(ctx, kS0, R(ctx, kV0));
    if (R(ctx, kS0) == 0) {
        guest::charge(ctx, 3);
        S(ctx, kV0, 0);
    } else {
        guest::charge(ctx, 16);
        S(ctx, kA0, R(ctx, kS1));
        S(ctx, kA1, la(0x6B44F0u));
        S(ctx, kA2, 6311);
        S(ctx, kA3, la(0x430060u));
        S(ctx, kT0, la(0x430150u));
        S(ctx, kT1, R(ctx, kS0));
        jal(ctx, 0x4301ecu, &rg::fn_kwlnTaskCreate_00194b20);
        sh(ctx, 0, R(ctx, kS0), 2);
        sh(ctx, 0, R(ctx, kS0), 0);
        S(ctx, kV1, lui(0x3F80));
        sw(ctx, R(ctx, kV1), R(ctx, kS0), 4);
        sb(ctx, 0, R(ctx, kS0), 24);
    }
    guest::charge(ctx, 6);
}

// 0x234710(src, size): br_res.c (0x68E6A0), work gp-18916, flags2 (+4) bit 0x20 must be clear (line 386);
// work->+44 = copy = RwMalloc(size, 0x40000), memcpy(copy, src, size), flags2 |= 0x20.
void sub_234710(EEContext& ctx) {
    guest::enter(ctx, 11);
    Frame f(ctx, 80, 64, 4);
    S(ctx, kS2, R(ctx, kA0));
    S(ctx, kS1, R(ctx, kA1));
    need_work(ctx, kV0, -18916, 0x68E6A0u, 82, 0x234748u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, -18916));
    need_clear(ctx, 4, 0x20, 0x68E6A0u, 386, 0x234774u);
    guest::charge(ctx, 24);
    S(ctx, kA0, R(ctx, kS1));
    S(ctx, kA1, lui(0x4));
    jalr_slot(ctx, kSlotMalloc, 0x23478cu);
    S(ctx, kS3, R(ctx, kV0));
    S(ctx, kA0, R(ctx, kS3));
    S(ctx, kA1, R(ctx, kS2));
    S(ctx, kA2, R(ctx, kS1));
    jal(ctx, 0x2347a4u, &rg::fn_memcpy_00521250);
    sw(ctx, R(ctx, kS3), R(ctx, kS0), 44);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 4) | 0x20u);
    sw(ctx, R(ctx, kV1), R(ctx, kS0), 4);
}

// =====================================================================================================================
// printf / sprintf
// =====================================================================================================================

// 0x2449D0: printf(gp-26756), then sub_244770 with the registers printf left.
void sub_2449D0(EEContext& ctx) {
    guest::enter(ctx, 11);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, addi(R(ctx, kGP), -26756));
    jal(ctx, 0x2449dcu, &rg::fn_printf_005225a8);
    jal(ctx, 0x2449e4u, &rg::fn_sub_244770_00244770);
}

// 0x1FA450: unless The Answer, printf(0x684C10) and sub_1FA4F0(m) for m = 2, 3, 4, 5, 7, 8, 9, 10.
void sub_1FA450(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16, 0, 0);
    if (jal(ctx, 0x1fa458u, &rg::fn_sub_17D800_0017d800) == 0) {
        guest::charge(ctx, 28);
        S(ctx, kA0, la(0x684C10u));
        jal(ctx, 0x1fa470u, &rg::fn_printf_005225a8);
        static constexpr u32 kMembers[] = {2, 3, 4, 5, 7, 8, 9, 10};
        u32 link = 0x1fa47cu;
        for (u32 m : kMembers) {
            S(ctx, kA0, m);
            jal(ctx, link, &rg::fn_sub_1FA4F0_001fa4f0);
            link += 12;
        }
    }
    guest::charge(ctx, 4);
}

// 0x1FBCA0(level): walks the 4-byte rows at gp-18600 {u8 lo, u8 hi, u16 x} until a row of all zeros; for each row
// with lo <= level < hi (signed compares of the whole registers): printf(0x684D50, lo, level, hi) and count. Returns
// the count. level = a0 & 0xFFFF.
void sub_1FBCA0(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 64, 48, 3);
    S(ctx, kS1, 0);
    S(ctx, kS2, gpw(ctx, -18600));
    S(ctx, kS0, R(ctx, kA0) & 0xFFFFu);
    for (;;) {
        guest::charge(ctx, 3);
        S(ctx, kA1, lbu(ctx, R(ctx, kS2), 0));
        if (R(ctx, kA1) == 0) {
            guest::charge(ctx, 3);
            S(ctx, kV0, lbu(ctx, R(ctx, kS2), 1));
            if (R(ctx, kV0) == 0) {
                guest::charge(ctx, 3);
                S(ctx, kV0, lhu(ctx, R(ctx, kS2), 2));
                if (R(ctx, kV0) == 0) break;
            }
        }
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS0), R(ctx, kA1)));
        if (R(ctx, kV0) == 0) {
            guest::charge(ctx, 4);
            S(ctx, kA3, lbu(ctx, R(ctx, kS2), 1));
            S(ctx, kAT, slt(R(ctx, kS0), R(ctx, kA3)));
            if (R(ctx, kAT) != 0) {
                guest::charge(ctx, 6);
                S(ctx, kA0, la(0x684D50u));
                S(ctx, kA2, R(ctx, kS0));
                jal(ctx, 0x1fbd0cu, &rg::fn_printf_005225a8);
                S(ctx, kS1, addi(R(ctx, kS1), 1));
            }
        }
        guest::charge(ctx, 3);
        S(ctx, kS2, addi(R(ctx, kS2), 4));
        guest::backedge(ctx);
    }
    guest::charge(ctx, 8);
    S(ctx, kV0, R(ctx, kS1));
}

// 0x21B8B0(value): bse_main.c (0x68E2D0), work gp-18928: printf(gp-26796), work->+8 = value, work->+0 &= ~1.
void sub_21B8B0(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 48, 32, 2);
    S(ctx, kS1, R(ctx, kA0));
    need_work(ctx, kV0, -18928, 0x68E2D0u, 30, 0x21b8dcu);
    guest::charge(ctx, 15);
    S(ctx, kS0, gpw(ctx, -18928));
    S(ctx, kA0, addi(R(ctx, kGP), -26796));
    jal(ctx, 0x21b8ecu, &rg::fn_printf_005225a8);
    sw(ctx, R(ctx, kS1), R(ctx, kS0), 8);
    S(ctx, kA0, lw(ctx, R(ctx, kS0), 0));
    S(ctx, kV1, sx(0xFFFFFFFEu));
    S(ctx, kV1, R(ctx, kA0) & R(ctx, kV1));
    sw(ctx, R(ctx, kV1), R(ctx, kS0), 0);
}

// 0x197FB0(obj, message): printf(message).
void kwlnAdxErrorCallback(EEContext& ctx) {
    guest::enter(ctx, 9);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, R(ctx, kA1));
    jal(ctx, 0x197fbcu, &rg::fn_printf_005225a8);
}

// 0x238980(quads, max_digits, number, colour): sprintf(frame + 80, gp-26768 "%d"-style, number) (the number stays in
// $a2, $a3 as the caller set them); n = strlen; K_Assert(0x68E7A0, 37) when max_digits < n; then for each digit i from
// the right: bpIfontSetDigitQuad(quads + 256 * i, digit - '0', colour).
void bpIfontDrawNumber(EEContext& ctx) {
    guest::enter(ctx, 20);
    Frame f(ctx, 336, 64, 4);
    S(ctx, kS3, R(ctx, kA0));
    S(ctx, kS1, R(ctx, kA1));
    S(ctx, kS2, R(ctx, kA3));
    S(ctx, kA0, addi(R(ctx, kSP), 80));
    S(ctx, kA1, addi(R(ctx, kGP), -26768));
    jal(ctx, 0x2389acu, &rg::fn_sprintf_00523ac8);
    S(ctx, kA0, addi(R(ctx, kSP), 80));
    jal(ctx, 0x2389b8u, &rg::fn_strlen_00524388);
    S(ctx, kS0, R(ctx, kV0));
    S(ctx, kAT, slt(R(ctx, kS1), R(ctx, kS0)));
    if (R(ctx, kAT) != 0) k_assert(ctx, 0x68E7A0u, 37, 0x2389dcu);
    guest::charge(ctx, 3);
    S(ctx, kS1, 0);
    for (;;) {
        guest::charge(ctx, 3);
        S(ctx, kV1, slt(R(ctx, kS1), R(ctx, kS0)));
        if (R(ctx, kV1) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 11);
        S(ctx, kV0, sll(R(ctx, kS1), 8));
        S(ctx, kA0, add32(R(ctx, kS3), R(ctx, kV0)));
        S(ctx, kV0, addi(R(ctx, kS0), -1));
        S(ctx, kV0, sub32(R(ctx, kV0), R(ctx, kS1)));
        S(ctx, kV0, add32(R(ctx, kV0), R(ctx, kSP)));
        S(ctx, kV0, lb(ctx, R(ctx, kV0), 80));
        S(ctx, kA1, addi(R(ctx, kV0), -48));
        S(ctx, kA2, R(ctx, kS2));
        jal(ctx, 0x238a10u, &rg::fn_bpIfontSetDigitQuad_00238fd0);
        S(ctx, kS1, addi(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 8);
}

}  // namespace p3fes::game

// --- the generated entry points (each function reads its arguments from the guest registers itself) ---------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
void fn_sub_266A20_00266a20(p3fes::EEContext& ctx) { sub_266A20(ctx); }
void fn_sub_266CB0_00266cb0(p3fes::EEContext& ctx) { sub_266CB0(ctx); }
void fn_sub_21C7F0_0021c7f0(p3fes::EEContext& ctx) { sub_21C7F0(ctx); }
void fn_sub_233B20_00233b20(p3fes::EEContext& ctx) { sub_233B20(ctx); }
void fn_sub_2339D0_002339d0(p3fes::EEContext& ctx) { sub_2339D0(ctx); }
void fn_sub_24BE40_0024be40(p3fes::EEContext& ctx) { sub_24BE40(ctx); }
void fn_sub_107020_00107020(p3fes::EEContext& ctx) { sub_107020(ctx); }
void fn_sub_2699A0_002699a0(p3fes::EEContext& ctx) { sub_2699A0(ctx); }
void fn_sub_266600_00266600(p3fes::EEContext& ctx) { sub_266600(ctx); }
void fn_sub_3C4430_003c4430(p3fes::EEContext& ctx) { sub_3C4430(ctx); }
void fn_sub_3C45F0_003c45f0(p3fes::EEContext& ctx) { sub_3C45F0(ctx); }
void fn_sub_3C4F30_003c4f30(p3fes::EEContext& ctx) { sub_3C4F30(ctx); }
void fn_sub_430150_00430150(p3fes::EEContext& ctx) { sub_430150(ctx); }
void fn_sub_4310E0_004310e0(p3fes::EEContext& ctx) { sub_4310E0(ctx); }
void fn_Y_SMap_CreateStaireDispTask_00430180(p3fes::EEContext& ctx) { Y_SMap_CreateStaireDispTask(ctx); }
void fn_sub_234710_00234710(p3fes::EEContext& ctx) { sub_234710(ctx); }
void fn_sub_2449D0_002449d0(p3fes::EEContext& ctx) { sub_2449D0(ctx); }
void fn_sub_1FA450_001fa450(p3fes::EEContext& ctx) { sub_1FA450(ctx); }
void fn_sub_1FBCA0_001fbca0(p3fes::EEContext& ctx) { sub_1FBCA0(ctx); }
void fn_sub_21B8B0_0021b8b0(p3fes::EEContext& ctx) { sub_21B8B0(ctx); }
void fn_kwlnAdxErrorCallback_00197fb0(p3fes::EEContext& ctx) { kwlnAdxErrorCallback(ctx); }
void fn_bpIfontDrawNumber_00238980(p3fes::EEContext& ctx) { bpIfontDrawNumber(ctx); }
}  // namespace p3fes::recomp_gen
