// The effect system's effect-type handlers (fx_types.h has the dispatch tables, the data each function works on and
// the register contract; docs/ANALYSIS/27_unmapped_bands.md, section 6, band 0x324160-0x34C160).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated (N = the block's instruction count, its delay-slot nop included); backedge() sits wherever that body
// has a check point on a backward jump. Loops whose test block comes first ("goto test" in the recompiled body) charge
// the test block, then take the check point before every pass through the body. A block that ends in a `jal` is charged
// in full before the call (the recompiler keeps the call inside its block), so a call's return continues in the same
// block.
//
// Registers: register-faithful (fx_types.h). Each body runs on the Cpu view of the guest context: one variable per GPR
// (64-bit writes keep bits 64..127, as the EE does; the prologue / epilogue spills are 128-bit), the FPU operations
// through the runtime's own instruction semantics. The band was compiled without delay-slot scheduling (every slot is a
// nop), so the statements follow the instructions in order.
#include "p3fes/game/fx_types.h"

#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_321140_00321140(p3fes::EEContext&);
void fn_sub_321180_00321180(p3fes::EEContext&);
void fn_sub_3211D0_003211d0(p3fes::EEContext&);
void fn_sub_3237C0_003237c0(p3fes::EEContext&);
void fn_sub_323A30_00323a30(p3fes::EEContext&);
void fn_sub_324310_00324310(p3fes::EEContext&);
void fn_sub_3243D0_003243d0(p3fes::EEContext&);  // this slice
void fn_sub_3245B0_003245b0(p3fes::EEContext&);  // this slice
void fn_sub_3245F0_003245f0(p3fes::EEContext&);  // this slice
void fn_sub_327250_00327250(p3fes::EEContext&);
void fn_sub_3275D0_003275d0(p3fes::EEContext&);
void fn_sub_329490_00329490(p3fes::EEContext&);  // this slice
void fn_sub_332200_00332200(p3fes::EEContext&);  // this slice
void fn_sub_332210_00332210(p3fes::EEContext&);  // this slice
void fn_sub_3322D0_003322d0(p3fes::EEContext&);  // this slice
void fn_sub_332310_00332310(p3fes::EEContext&);  // this slice
void fn_sub_332330_00332330(p3fes::EEContext&);  // this slice
void fn_sub_3393D0_003393d0(p3fes::EEContext&);
void fn_sub_341F10_00341f10(p3fes::EEContext&);
void fn_sub_345CF0_00345cf0(p3fes::EEContext&);
void fn_sub_348110_00348110(p3fes::EEContext&);  // this slice
void fn_sub_358030_00358030(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB420_004cb420(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4E3630_004e3630(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {
namespace fx::detail {

namespace gen = ::p3fes::recomp_gen;

void Cpu::open_frame(unsigned n) {
    sp = addiu(sp, -static_cast<s32>(16 * n + 16));
    sd(sp + 16 * n, ra);
    for (unsigned i = n; i-- > 0;) sq(sp + 16 * i, Gpr{c, GPR_S0 + i});
}

void Cpu::close_frame(unsigned n) {
    ra = ld(sp + 16 * n);
    for (unsigned i = n; i-- > 0;) {
        Gpr s{c, GPR_S0 + i};
        lq(s, sp + 16 * i);
    }
    sp = addiu(sp, static_cast<s32>(16 * n + 16));
}

// The class table 0x69BE20: 13 words per effect class (`0x69BE20 + 52 * class`), the class number the u16 at
// effect +4. (52 * class is formed as ((class * 3) * 4 + class) * 4, the shifts and adds below.)
constexpr u32 kClassTable = 0x69BE20u;
inline u64 class_row_offset(u64 cls) {
    // sll t, cls, 1; addu t, t, cls; sll t, t, 2; addu t, t, cls; sll t, t, 2
    u64 t = sll(cls, 1);
    t = addu(t, cls);
    t = sll(t, 2);
    t = addu(t, cls);
    return sll(t, 2);
}

class Fx : public Cpu {
public:
    using Cpu::Cpu;
    void nop2();
    void sub_324650();
    void sub_3245B0();
    void sub_3245F0();
    void block_getter(s32 alloc, s32 ptr);
    void slot_call_if(Gpr& row_reg, s32 slot, u32 pc);
    void slot_call(s32 slot, u32 pc);
    void sub_324930();
    void sub_324990();
    void sub_3249E0();
    void sub_324A30();
    void sub_324A90();
    void sub_324AF0();
    void sub_3243D0();
    void model_matrix(rt::Fn build, u32 pc_build, u32 pc_apply);
    void sub_3244C0();
    void sub_324B50();
    void sub_326190();
    void sub_347D00();
    void sub_347D60();
    void shake_axis();
    void sub_347F80();
    void sub_34BD10();
    void kind_row(u64 table_lo, u32 pc);
    void filter_update(s32 table_lo, u32 pc);
    void sub_34B520();
    void filter_draw(s32 table_lo, u32 pc);
    void sub_34B580();
    void filter_notify(rt::Fn notify, u32 pc);
    void sub_34B5C0();
    void set_quad0();
    void set_word16();
    void set_float20();
    void sub_326160();
    void sub_326170();
    void sub_326180();
    void sub_3261C0();
    void sub_326200();
    void sub_326240();
    void sub_332200();
    void sub_332210();
    void track_get(s32 off);
    void sub_3322B0();
    void sub_3322F0();
    void track_set(s32 off);
    void sub_3322D0();
    void sub_332310();
    void sub_332330();
    void track_forward(s32 field, bool checked, rt::Fn fn, u32 pc);
    void sub_327220();
    void sub_332B30();
    void sub_329430();
    void sub_333020();
    void sub_329460();
    void sub_333050();
    void obj_set_time(s32 field, u32 pc);
    void sub_3294A0();
    void sub_3330B0();
    void sub_329490();
    void sub_333080();
    void sub_329350();
    void sub_3293A0();
    void sub_3293D0();
    void sub_333900();
    void sub_333920();
    void sub_333940();
    void kind_call(const Gpr& base, s32 kind_off, s32 slot_lo, bool stride28, u32 pc);
    void kobj_init(s32 kind_off, s32 count_off, s32 slot_lo, bool stride28, u32 pc);
    void kobj_update(s32 kind_off, s32 count_off, s32 slot_lo, bool stride28, u32 pc);
    void kobj_draw(s32 kind_off, s32 count_off, s32 slot_lo, bool stride28, u32 pc);
    void kobj_update_draw(s32 kind_off, s32 count_off, s32 update_lo, s32 draw_lo, bool stride28, u32 pc_update,
                          u32 pc_draw);
    void kobj_create(rt::Fn create, u32 pc_block, u32 pc_create);
    void kobj_recreate(s32 kind_off, s32 params_off, rt::Fn create, u32 pc);
    void kobj_create_from_effect(rt::Fn create, s32 param_lo, s32 init_lo, const u32* pc);
    void sub_341FD0();
    void sub_345DB0();
    void sub_342130();
    void sub_345F00();
    void rw_free(u32 pc);
    void kobj_destroy(s32 kind_off, s32 slot_lo, bool stride28, u32 pc_slot, u32 pc_free);
    void kobj_destroy_params(s32 slot_lo, bool stride28, u32 pc_slot, u32 pc_free);
    void sub_3321D0();
    void sub_3338B0();
    void release_free(s32 field, rt::Fn release, u32 pc_release, u32 pc_free);
    void sub_339950();
    void sub_342A40();
    void set_quad(s32 off);
    void set_word(s32 off);
    void set_float(s32 off);
    void set_float3(s32 off);
    void copy_float3(s32 off);
    void zero_word(s32 off);
    void inc_word(s32 off);
    void sub_3342C0();
    void apply_tint();
    void obj21_step(u32 pc);
    void sub_34BCF0();
    void u32_to_f0(const Gpr& src, Gpr& hi, Gpr& lo);
    void sub_32A540();
    void sub_348110();
    void camera_row(s32 row, u32 pc_scene, u32 pc_matrix);
    void sub_329740();
    void sub_3297A0();
};

// =====================================================================================================================
// [base] the shared defaults, the instance-block getters and the class-slot dispatchers
// =====================================================================================================================

// sub_324630 / sub_324640 / sub_324660 / sub_324670 [fxDefaultNop]: the empty defaults of the class rows (`jr ra`).
void Fx::nop2() { enter(2); }

// sub_324650 [fxDefaultZero]: the class-row default that returns 0.
void Fx::sub_324650() {
    enter(3);
    v0 = zero;
}

// sub_3245B0 [fxBlockA]: the effect's first data block -- the absolute pointer at +16 when +24 (its allocation) is set,
// else the offset at +16 relative to the record (0 stays 0).
void Fx::sub_3245B0() { block_getter(24, 16); }
// sub_3245F0 [fxBlockB]: the same for the second block (+40 allocation, +32 pointer / offset).
void Fx::sub_3245F0() { block_getter(40, 32); }

void Fx::block_getter(s32 alloc, s32 ptr) {
    enter(3);
    v0 = lw(a0 + alloc);
    if (v0 != 0) {
        charge(3);
        v0 = lw(a0 + ptr);
    } else {
        charge(3);
        v0 = lw(a0 + ptr);
        if (v0 != 0) {
            charge(3);
            v0 = addu(a0, v0);
        } else {
            charge(1);
            v0 = zero;
        }
    }
    charge(2);
}

// The class-slot dispatchers: `fn = 0x69BE20[52 * effect->class + slot]; fn(effect->instance)` (effect +4 the u16
// class, +8 the instance). `row_reg` is the scratch register the original forms the row offset in; the two
// unconditional ones (slots 2 and 3) form it in $v1 and the pointer in $v0, the conditional ones keep the slot word in
// $v1 and skip the call when it is null.
void Fx::slot_call_if(Gpr& row_reg, s32 slot, u32 pc) {
    enter(14);
    sp = addiu(sp, -16);
    sd(sp, ra);
    row_reg = lhu(a0 + 4);
    const u64 cls = row_reg;
    // the shifts and adds of 52 * class: $v1 holds the partial sums, row_reg the final offset
    v1 = sll(cls, 1);
    v1 = addu(v1, cls);
    v1 = sll(v1, 2);
    v1 = addu(v1, cls);
    row_reg = sll(v1, 2);
    v1 = lui(0x6A);
    v1 = addiu(v1, static_cast<s32>(kClassTable - 0x6A0000u) + slot);
    v1 = addu(v1, row_reg);
    v1 = lw(v1);
    if (v1 != 0) {
        charge(3);
        a0 = lw(a0 + 8);
        jalr(pc, w(v1));
    }
    charge(4);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

void Fx::slot_call(s32 slot, u32 pc) {
    enter(20);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v0 = a0;  // move v0, a0
    a0 = lw(a0 + 8);
    v1 = lhu(v0 + 4);
    const u64 cls = v1;
    v0 = sll(cls, 1);
    v0 = addu(v0, cls);
    v0 = sll(v0, 2);
    v0 = addu(v0, cls);
    v1 = sll(v0, 2);
    v0 = lui(0x6A);
    v0 = addiu(v0, static_cast<s32>(kClassTable - 0x6A0000u) + slot);
    v0 = addu(v0, v1);
    v0 = lw(v0);
    jalr(pc, w(v0));
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_324930 [fxClassSlot7]: slot 7 when present ($a1 holds the row offset).
void Fx::sub_324930() { slot_call_if(a1, 28, 0x32496Cu); }
// sub_324990 [fxClassSlot2]: slot 2, always.
void Fx::sub_324990() { slot_call(8, 0x3249C8u); }
// sub_3249E0 [fxClassSlot3]: slot 3, always.
void Fx::sub_3249E0() { slot_call(12, 0x324A18u); }
// sub_324A30 [fxClassSlot8]: slot 8 when present ($a2 holds the row offset).
void Fx::sub_324A30() { slot_call_if(a2, 32, 0x324A6Cu); }
// sub_324A90 [fxClassSlot10]: slot 10 when present ($a1).
void Fx::sub_324A90() { slot_call_if(a1, 40, 0x324ACCu); }
// sub_324AF0 [fxClassSlot12]: slot 12 when present ($a2).
void Fx::sub_324AF0() { slot_call_if(a2, 48, 0x324B2Cu); }

// sub_3243D0 [fxLayerAttach]: a tail into the layer manager (sub_321140) inside a 16-byte frame.
void Fx::sub_3243D0() {
    enter(8);
    sp = addiu(sp, -16);
    sd(sp, ra);
    jal(0x3243D8u, gen::fn_sub_321140_00321140);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_3244C0 [fxSetModelMatrix] (sub_324470 is the same with sub_323920): builds a matrix in the frame (+32,
// sub_323A30) and applies it to the effect's model (+12) with sub_4CB7F0(model, matrix, 0).
void Fx::model_matrix(rt::Fn build, u32 pc_build, u32 pc_apply) {
    enter(17);
    sp = addiu(sp, -96);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = addiu(sp, 32);
    jal(pc_build, build);
    a0 = lw(s0 + 12);
    a1 = addiu(sp, 32);
    a2 = zero;
    jal(pc_apply, gen::fn_sub_4CB7F0_004cb7f0);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}
void Fx::sub_3244C0() { model_matrix(gen::fn_sub_323A30_00323a30, 0x3244D4u, 0x3244E8u); }

// =====================================================================================================================
// [node] the effect node (sub_324BD0 allocates them; the EffectNode of fx_epl.h): its reset and copy
// =====================================================================================================================

// sub_324B50 [fxNodeReset]: clears the 128-byte node header and sets its defaults -- position / rotation / +64 / +80 to
// vf0 (0, 0, 0, 1), +68 = 5.0f, the colour quadword +32 from 0x69C4A0, +96 / +116 = 1.0f, +100 = -1, +104 = 128.
void Fx::sub_324B50() {
    enter(30);
    open_frame(1);
    s0 = a0;
    a1 = zero;
    a2 = 128;
    jal(0x324B68u, gen::fn_memset_00521408);
    sqc2(0, s0 + 0);
    sqc2(0, s0 + 16);
    sqc2(0, s0 + 64);
    v0 = lui(0x40A0);  // 5.0f
    sw(s0 + 68, v0);
    sqc2(0, s0 + 80);
    v0 = lui(0x6A);
    v0 = addiu(v0, -15200);  // 0x69C4A0
    lq(v0, v0);
    sq(s0 + 32, v0);
    v1 = lui(0x3F80);  // 1.0f
    sw(s0 + 96, v1);
    sw(s0 + 116, v1);
    v1 = sx(0xFFFFFFFFu);
    sw(s0 + 100, v1);
    v1 = 128;
    sw(s0 + 104, v1);
    close_frame(1);
}

// sub_326190 [fxNodeCopyHeader]: memcpy(dst, src, 144).
void Fx::sub_326190() {
    enter(9);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a2 = 144;
    jal(0x32619Cu, gen::fn_memcpy_00521250);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// =====================================================================================================================
// [screen shake] the gp-relative shake state (gp-18340 u8 active, gp-18336 u16, gp-18332 / gp-18328 the two
// amplitudes, gp-18320 the camera, gp-18312 / gp-18308 the two current offsets)
// =====================================================================================================================

// sub_347D00 [fxShakeInit]: clears the state, takes the current camera (sub_4CAF10) and moves it to the position of
// the scene's camera record (sub_198590 -> +4).
void Fx::sub_347D00() {
    enter(21);
    sp = addiu(sp, -16);
    sd(sp, ra);
    sb(gp - 18340, zero);
    sh(gp - 18336, zero);
    sw(gp - 18332, zero);
    sw(gp - 18328, zero);
    sw(gp - 18312, zero);
    sw(gp - 18308, zero);
    jal(0x347D20u, gen::fn_sub_4CAF10_004caf10);
    sw(gp - 18320, v0);
    jal(0x347D2Cu, gen::fn_sub_198590_00198590);
    a0 = lw(gp - 18320);
    a1 = lw(v0 + 4);
    jal(0x347D3Cu, gen::fn_sub_4CB420_004cb420);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_347D60 [fxShakeUpdate]: when the active byte is set, clears it and moves each of the two offsets toward a new
// random target within +-amplitude (amplitude * the frame factor gp-32108), then places the camera (sub_4CB750) at the
// scene camera's position plus the offsets. $f20 / $f21 are spilled in the frame (+0 / +4); the gp-25248 pair is
// copied to the frame (+96 / +100) as the per-axis limits.
void Fx::sub_347D60() {
    enter(14);
    sp = addiu(sp, -112);
    sd(sp + 64, ra);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    lwc1(F1, gp - 25248);
    lwc1(F0, gp - 25244);
    swc1(F1, sp + 96);
    swc1(F0, sp + 100);
    v1 = lbu(gp - 18340);
    if (v1 != 0) {
        charge(11);
        sb(gp - 18340, zero);
        lwc1(F1, gp - 32108);
        lwc1(F0, gp - 18332);
        mul_s(F0, F1, F0);
        swc1(F0, sp + 104);  // amplitude x
        lwc1(F0, gp - 18328);
        mul_s(F0, F1, F0);
        swc1(F0, sp + 108);  // amplitude y
        s2 = zero;
        for (;;) {
            charge(3);
            v0 = slti(s2, 2);
            if (v0 == 0) break;
            backedge();
            charge(9);
            s1 = sll(s2, 2);
            v0 = addu(s1, sp);
            v0 = addiu(v0, 104);
            lwc1(F20, v0);  // amplitude
            mtc1(zero, F0);
            c_eq_s(F0, F20);
            if (!cop1_cond()) shake_axis();
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(26);
        jal(0x347EE8u, gen::fn_sub_198590_00198590);
        v0 = lw(v0 + 4);
        lwc1(F4, gp - 18312);
        lwc1(F3, gp - 25256);
        lwc1(F0, v0 + 16);
        mul_s(F0, F0, F4);
        mul_s(F0, F3, F0);
        swc1(F0, sp + 80);
        lwc1(F2, v0 + 20);
        lwc1(F1, gp - 18308);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F0, F2, F4);
        mul_s(F0, F3, F0);
        swc1(F0, sp + 84);
        lwc1(F0, v0 + 24);
        mul_s(F0, F0, F4);
        mul_s(F0, F3, F0);
        swc1(F0, sp + 88);
        a0 = lw(gp - 18320);
        a1 = addiu(sp, 80);
        a2 = zero;
        jal(0x347F48u, gen::fn_sub_4CB750_004cb750);
    }
    charge(9);
    ra = ld(sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 112);
}

// One axis of sub_347D60 ($f20 the amplitude, $s1 the axis * 4): a random step of up to amplitude / 2 toward 0 when
// inside the limit, else a pull back of 2 * (rand - 0.5) * step; the offset is then clamped to +-amplitude.
void Fx::shake_axis() {
    charge(22);
    v0 = lui(0x3F00);
    mtc1(v0, F21);
    a0 = zero;
    jal(0x347DF4u, gen::fn_sub_358030_00358030);  // $f0 = rand in [0, 1)
    mul_s(F1, F20, F0);
    v0 = lui(0x3F00);
    mtc1(v0, F0);
    mula_s(F0, F1);
    mtc1(zero, F2);
    madd_s(F21, F21, F20);  // step = 0.5 * amplitude * rand + 0.5 * amplitude (ACC + f21 * f20)
    v0 = addiu(gp, -18312);
    s0 = addu(v0, s1);
    lwc1(F1, s0);  // offset
    abs_s(F3, F1);
    v0 = addu(s1, sp);
    lwc1(F0, v0 + 96);
    mul_s(F0, F20, F0);
    c_lt_s(F3, F0);
    if (!cop1_cond()) {
        charge(3);
        c_le_s(F1, F2);
        if (cop1_cond()) {
            charge(4);
            add_s(F0, F1, F21);
            swc1(F0, s0);
        } else {
            charge(4);
            sub_s(F0, F1, F21);
            swc1(F0, s0);
        }
    } else {
        charge(16);
        a0 = zero;
        jal(0x347E70u, gen::fn_sub_358030_00358030);
        v0 = lui(0x3F00);
        mtc1(v0, F1);
        sub_s(F0, F0, F1);
        mul_s(F3, F21, F0);
        v0 = lui(0x4000);
        mtc1(v0, F2);
        lwc1(F1, s0);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F0, F2, F3);
        swc1(F0, s0);
    }
    charge(5);
    neg_s(F1, F20);
    lwc1(F0, s0);
    c_lt_s(F0, F1);
    if (cop1_cond()) {
        charge(1);
        swc1(F1, s0);
    }
    charge(4);
    lwc1(F0, s0);
    c_le_s(F0, F20);
    if (!cop1_cond()) {
        charge(1);
        swc1(F20, s0);
    }
}

// sub_347F80 [fxShakeStop]: puts the camera back at 0x957A90 (sub_4CB750(camera, 0x957A90, 0)) and clears the active
// byte.
void Fx::sub_347F80() {
    enter(13);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a0 = lw(gp - 18320);
    a1 = lui(0x95);
    a1 = addiu(a1, 31376);
    a2 = zero;
    jal(0x347F98u, gen::fn_sub_4CB750_004cb750);
    sb(gp - 18340, zero);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_34BD10 [fxScreenSizeInit]: stores the current raster (sub_4E3630) at 0x957BA8 and its width / height (+12 / +16)
// as floats at 0x957BAC / 0x957BB0.
void Fx::sub_34BD10() {
    enter(18);
    sp = addiu(sp, -16);
    sd(sp, ra);
    jal(0x34BD18u, gen::fn_sub_4E3630_004e3630);
    v1 = lui(0x95);
    sw(v1 + 31656, v0);
    lwc1(F0, v0 + 12);
    cvt_s_w(F0, F0);
    v1 = lui(0x95);
    swc1(F0, v1 + 31660);
    lwc1(F0, v0 + 16);
    cvt_s_w(F0, F0);
    v1 = lui(0x95);
    swc1(F0, v1 + 31664);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// =====================================================================================================================
// [class 4 / 5] the screen-filter classes (rows 0x69BEF0 / 0x69BF24): instance +24 the filter kind (rows of six words
// at 0x69CB98 / 0x69CC50 + 24 * kind), +28 the frame counter, +36 the owner, +16 / +20 the set word / float, +0 a
// quadword
// =====================================================================================================================

// The kind-row call of sub_34B520 / sub_34BA30 / sub_34B580 / sub_34BA90: `fn = row[24 * inst->kind + slot](inst)`,
// $v1 / $v0 forming the offset and the pointer as the original does.
void Fx::kind_row(u64 table_lo, u32 pc) {
    v1 = lw(a0 + 24);
    const u64 kind = v1;
    v0 = sll(kind, 1);
    v0 = addu(v0, kind);
    v1 = sll(v0, 3);
    v0 = lui(0x6A);
    v0 = addiu(v0, static_cast<s32>(w(table_lo)));
    v0 = addu(v0, v1);
    v0 = lw(v0);
    jalr(pc, w(v0));
}

// sub_34B520 / sub_34BA30 [fxFilterUpdate]: the kind's update (slot 0), then ++frame (+28).
void Fx::filter_update(s32 table_lo, u32 pc) {
    enter(22);
    open_frame(1);
    s0 = a0;
    kind_row(static_cast<u64>(static_cast<s64>(table_lo)), pc);
    v1 = lw(s0 + 28);
    v1 = addiu(v1, 1);
    sw(s0 + 28, v1);
    close_frame(1);
}
void Fx::sub_34B520() { filter_update(-13416, 0x34B550u); }

// sub_34B580 / sub_34BA90 [fxFilterDraw]: the kind's slot 1.
void Fx::filter_draw(s32 table_lo, u32 pc) {
    enter(16);
    sp = addiu(sp, -16);
    sd(sp, ra);
    kind_row(static_cast<u64>(static_cast<s64>(table_lo)), pc);
    ra = ld(sp);
    sp = addiu(sp, 16);
}
void Fx::sub_34B580() { filter_draw(-13412, 0x34B5A8u); }

// sub_34B5C0 / sub_34BAD0 [fxFilterNotify]: after the first frame, tells the owner's layer (sub_321180 / sub_3211D0
// with the owner's u16 +40 in $a1).
void Fx::filter_notify(rt::Fn notify, u32 pc) {
    enter(5);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v1 = lw(a0 + 28);
    if (sgn(v1) > 0) {
        charge(4);
        v0 = lw(a0 + 36);
        a1 = lhu(v0 + 40);
        jal(pc, notify);
    }
    charge(4);
    ra = ld(sp);
    sp = addiu(sp, 16);
}
void Fx::sub_34B5C0() { filter_notify(gen::fn_sub_321180_00321180, 0x34B5DCu); }

// sub_34B680 / sub_34BB90 [fxFilterSetQuad]: inst +0 = the quadword at $a1.
void Fx::set_quad0() {
    enter(4);
    lq(v0, a1);
    sq(a0, v0);
}
// sub_34B690 / sub_34BBA0 [fxFilterSetWord16]: inst +16 = $a1.
void Fx::set_word16() {
    enter(3);
    sw(a0 + 16, a1);
}
// sub_34B6A0 / sub_34BBB0 [fxFilterSetFloat20]: inst +20 = $f12.
void Fx::set_float20() {
    enter(3);
    swc1(F12, a0 + 20);
}

// =====================================================================================================================
// [node tree] the effect node's children (sub_324BD0 / sub_325920 build them): the first child at +140 (0x8C), the next
// sibling at +172 (0xAC), each child's key word at +144 (0x90); the node's position / rotation quadwords +64 / +80 and
// its word +100
// =====================================================================================================================

// sub_326160 [fxNodeGetPosition]: *$a1 = node +64 (128 bits).
void Fx::sub_326160() {
    enter(4);
    lq(v0, a0 + 64);
    sq(a1, v0);
}
// sub_326170 [fxNodeGetRotation]: *$a1 = node +80.
void Fx::sub_326170() {
    enter(4);
    lq(v0, a0 + 80);
    sq(a1, v0);
}
// sub_326180 [fxNodeGetWord100]: returns node +100.
void Fx::sub_326180() {
    enter(3);
    v0 = lw(a0 + 100);
}

// sub_3261C0 [fxNodeFindChild]: the first child (+140, next +172) whose key (+144) equals $a1, else 0.
void Fx::sub_3261C0() {
    enter(3);
    v0 = lw(a0 + 140);
    for (;;) {
        charge(2);
        if (v0 == 0) break;
        backedge();
        charge(3);
        v1 = lw(v0 + 144);
        if (v1 == a1) {
            charge(2);
            charge(2);
            return;
        }
        charge(1);
        v0 = lw(v0 + 172);
    }
    charge(1);
    v0 = zero;
    charge(2);
}

// sub_326200 [fxNodeChildAt]: the child at position $a1 (counting down $a1; $v1 keeps the count before each
// step), else 0.
void Fx::sub_326200() {
    enter(3);
    v0 = lw(a0 + 140);
    for (;;) {
        charge(2);
        if (v0 == 0) break;
        backedge();
        charge(4);
        v1 = a1;
        a1 = addiu(a1, -1);
        if (v1 == 0) {
            charge(2);
            charge(2);
            return;
        }
        charge(1);
        v0 = lw(v0 + 172);
    }
    charge(1);
    v0 = zero;
    charge(2);
}

// sub_326240 [fxNodeChildIndex]: the position of the child $a1, else 0 (also 0 for the first child).
void Fx::sub_326240() {
    enter(4);
    v0 = zero;
    v1 = lw(a0 + 140);
    for (;;) {
        charge(2);
        if (v1 == 0) break;
        backedge();
        charge(2);
        if (v1 == a1) {
            charge(2);
            charge(2);
            return;
        }
        charge(2);
        v0 = addiu(v0, 1);
        v1 = lw(v1 + 172);
    }
    charge(1);
    v0 = zero;
    charge(2);
}

// =====================================================================================================================
// [track] the animation track of an effect object (object +76 / +48 / +44 -> track): +0 u16 the track type (rows of
// four words at 0x69C510 + 16 * type: the update, the time setter, ..), +4 a word, +8 the key count (unsigned), +16 the
// frame (0 = restart), +24 the key slots (32 bytes each, +16 = -1 when unset), +32 the value block (two quadwords)
// =====================================================================================================================

// sub_332200 [fxTrackRestart]: frame (+16) = 0.
void Fx::sub_332200() {
    enter(3);
    sw(a0 + 16, zero);
}

// sub_332210 [fxTrackUpdate]: on frame 0 clears the key slots (+24, count +8, +16 of each = -1), then calls the type's
// update (0x69C510 + 16 * type) and counts the frame.
void Fx::sub_332210() {
    enter(7);
    open_frame(1);
    s0 = a0;
    v0 = lw(a0 + 16);
    if (v0 == 0) {
        charge(6);
        a0 = lw(s0 + 8);
        a1 = lw(s0 + 24);
        a2 = zero;
        v1 = sx(0xFFFFFFFFu);
        for (;;) {
            charge(4);
            v0 = sltu(a2, a0);  // the key count (+8), unsigned
            if (v0 == 0) break;
            backedge();
            charge(3);
            sw(a1 + 16, v1);
            a1 = addiu(a1, 32);
            a2 = addiu(a2, 1);
        }
    }
    charge(17);
    a0 = s0;
    v0 = lhu(s0 + 0);
    v1 = sll(v0, 4);
    v0 = lui(0x6A);
    v0 = addiu(v0, -15088);  // 0x69C510
    v0 = addu(v0, v1);
    v0 = lw(v0);
    jalr(0x33227Cu, w(v0));
    v1 = lw(s0 + 16);
    v1 = addiu(v1, 1);
    sw(s0 + 16, v1);
    close_frame(1);
}

// sub_3322B0 / sub_3322F0 [fxTrackGetValue / fxTrackGetValue2]: *$a1 = the value block's quadword 0 / 1 (+32 -> +0 /
// +16).
void Fx::track_get(s32 off) {
    enter(5);
    v0 = lw(a0 + 32);
    lq(v0, v0 + off);
    sq(a1, v0);
}
void Fx::sub_3322B0() { track_get(0); }
void Fx::sub_3322F0() { track_get(16); }
// sub_3322D0 / sub_332310 [fxTrackSetValue / fxTrackSetValue2]: the value block's quadword 0 / 1 = *$a1.
void Fx::track_set(s32 off) {
    enter(5);
    v1 = lw(a0 + 32);
    lq(v0, a1);
    sq(v1 + off, v0);
}
void Fx::sub_3322D0() { track_set(0); }
void Fx::sub_332310() { track_set(16); }

// sub_332330 [fxTrackSetTime]: the type's second word (0x69C514 + 16 * type) on the track.
void Fx::sub_332330() {
    enter(14);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v0 = lhu(a0 + 0);
    v1 = sll(v0, 4);
    v0 = lui(0x6A);
    v0 = addiu(v0, -15084);  // 0x69C514
    v0 = addu(v0, v1);
    v0 = lw(v0);
    jalr(0x332350u, w(v0));
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// The object -> track forwarders: `track = obj->field; if (track or !checked) fn(track, ..)` in a 16-byte frame.
void Fx::track_forward(s32 field, bool checked, rt::Fn fn, u32 pc) {
    enter(checked ? 5 : 9);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a0 = lw(a0 + field);
    if (checked) {
        if (a0 != 0) {
            charge(2);
            jal(pc, fn);
        }
        charge(4);
    } else {
        jal(pc, fn);
    }
    ra = ld(sp);
    sp = addiu(sp, 16);
}
// sub_327220 / sub_332B30 [fxObjTrackRestart]: restarts the track at +76 / +48 when there is one.
void Fx::sub_327220() { track_forward(76, true, gen::fn_sub_332200_00332200, 0x327234u); }
void Fx::sub_332B30() { track_forward(48, true, gen::fn_sub_332200_00332200, 0x332B44u); }
// sub_329430 / sub_333020 [fxObjTrackSetValue]: the track's value quadword 0 = *$a1 (track +76 / +48).
void Fx::sub_329430() { track_forward(76, false, gen::fn_sub_3322D0_003322d0, 0x32943Cu); }
void Fx::sub_333020() { track_forward(48, false, gen::fn_sub_3322D0_003322d0, 0x33302Cu); }
// sub_329460 / sub_333050 [fxObjTrackSetValue2]: the track's value quadword 1 = *$a1.
void Fx::sub_329460() { track_forward(76, false, gen::fn_sub_332310_00332310, 0x32946Cu); }
void Fx::sub_333050() { track_forward(48, false, gen::fn_sub_332310_00332310, 0x33305Cu); }

// sub_3294A0 / sub_3330B0 [fxObjTrackSetTime]: object +8 = $f12, then the track's time setter (track +76 / +48).
void Fx::obj_set_time(s32 field, u32 pc) {
    enter(10);
    sp = addiu(sp, -16);
    sd(sp, ra);
    swc1(F12, a0 + 8);
    a0 = lw(a0 + field);
    jal(pc, gen::fn_sub_332330_00332330);
    ra = ld(sp);
    sp = addiu(sp, 16);
}
void Fx::sub_3294A0() { obj_set_time(76, 0x3294B0u); }
void Fx::sub_3330B0() { obj_set_time(48, 0x3330C0u); }

// sub_329490 [fxObjSetWord4]: object +4 = $a1.
void Fx::sub_329490() {
    enter(3);
    sw(a0 + 4, a1);
}

// sub_333080 [fxObjSetWord4Child]: object +4 = $a1, and the same on the child at +44 when there is one.
void Fx::sub_333080() {
    enter(6);
    sp = addiu(sp, -16);
    sd(sp, ra);
    sw(a0 + 4, a1);
    a0 = lw(a0 + 44);
    if (a0 != 0) {
        charge(2);
        jal(0x333098u, gen::fn_sub_329490_00329490);
    }
    charge(4);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_329350 [fxObj1Update]: when the object has a track (+76): the track's update, then the object's update
// (sub_327250(obj), $f12 = 1.0f).
void Fx::sub_329350() {
    enter(7);
    open_frame(1);
    s0 = a0;
    a0 = lw(a0 + 76);
    if (a0 != 0) {
        charge(7);
        jal(0x32936Cu, gen::fn_sub_332210_00332210);
        v0 = lui(0x3F80);
        mtc1(v0, F12);
        a0 = s0;
        jal(0x329380u, gen::fn_sub_327250_00327250);
    }
    charge(5);
    close_frame(1);
}

// sub_3293A0 [fxObj1Draw]: sub_3275D0(obj) with $f12 = 1.0f.
void Fx::sub_3293A0() {
    enter(10);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    jal(0x3293B0u, gen::fn_sub_3275D0_003275d0);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_3293D0 [fxObj1UpdateDraw]: sub_329350's update, then sub_3275D0(obj, 1.0f).
void Fx::sub_3293D0() {
    enter(7);
    open_frame(1);
    s0 = a0;
    a0 = lw(a0 + 76);
    if (a0 != 0) {
        charge(7);
        jal(0x3293ECu, gen::fn_sub_332210_00332210);
        v0 = lui(0x3F80);
        mtc1(v0, F12);
        a0 = s0;
        jal(0x329400u, gen::fn_sub_327250_00327250);
    }
    charge(10);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    a0 = s0;
    jal(0x329414u, gen::fn_sub_3275D0_003275d0);
    close_frame(1);
}

// =====================================================================================================================
// [mask] the u16 mask array of an object (+24): sub_333900 clears entry $a1, sub_333920 sets it to 0xFFFF,
// sub_333940 tests it for 0xFFFF
// =====================================================================================================================

void Fx::sub_333900() {
    enter(7);
    v1 = andi(a1, 0xFFFF);
    a1 = sll(v1, 1);
    v1 = lw(a0 + 24);
    v1 = addu(v1, a1);
    sh(v1, zero);
}
void Fx::sub_333920() {
    enter(8);
    a2 = sx(0xFFFFFFFFu);
    v1 = andi(a1, 0xFFFF);
    a1 = sll(v1, 1);
    v1 = lw(a0 + 24);
    v1 = addu(v1, a1);
    sh(v1, a2);
}
void Fx::sub_333940() {
    enter(9);
    v0 = andi(a1, 0xFFFF);
    v1 = sll(v0, 1);
    v0 = lw(a0 + 24);
    v0 = addu(v0, v1);
    v0 = lh(v0);
    v0 = ~static_cast<u64>(v0);  // nor v0, v0, zero
    v0 = sltiu(v0, 1);
}

// =====================================================================================================================
// [kind objects] the classes whose instance delegates to a kind row (classes 9, 10, 12, 13, 16: rows 0x69BFF4,
// 0x69C028, 0x69C090, 0x69C0C4, 0x69C160): the instance holds the kind number and a frame counter, the kind rows hold
// six (stride 24) or seven (stride 28) words -- init, .., update, draw, .. -- and the class slots forward to them.
//   class 12 (0x3394F0..): kind +56, counter +52, rows 0x69C650 (stride 24): init +0, update +12, draw +16
//   class 10 (0x341FD0..): kind +56, counter +52, rows 0x69C850 (stride 28): init +0, update +16, draw +20
//   class 16 (0x345DB0..): kind +56, counter +52, rows 0x69C970 (stride 28): init +0, update +16, draw +20
// =====================================================================================================================

// `fn = rows[stride * obj->kind + slot]; fn(obj)` with the original's registers: the kind in $v1, the row offset formed
// in $v0 / $v1 (stride 24: ((k << 1) + k) << 3; stride 28: ((k << 3) - k) << 2), the slot address and word in $v0.
void Fx::kind_call(const Gpr& base, s32 kind_off, s32 slot_lo, bool stride28, u32 pc) {
    v1 = lw(base + kind_off);
    const u64 k = v1;
    if (stride28) {
        v0 = sll(k, 3);
        v0 = subu(v0, k);
        v1 = sll(v0, 2);
    } else {
        v0 = sll(k, 1);
        v0 = addu(v0, k);
        v1 = sll(v0, 3);
    }
    v0 = lui(0x6A);
    v0 = addiu(v0, slot_lo);
    v0 = addu(v0, v1);
    v0 = lw(v0);
    jalr(pc, w(v0));
}

// [kobjInit]: the kind's init, then counter = 0.
void Fx::kobj_init(s32 kind_off, s32 count_off, s32 slot_lo, bool stride28, u32 pc) {
    enter(20);
    open_frame(1);
    s0 = a0;
    kind_call(a0, kind_off, slot_lo, stride28, pc);
    sw(s0 + count_off, zero);
    close_frame(1);
}
// [kobjUpdate]: the kind's update, then ++counter.
void Fx::kobj_update(s32 kind_off, s32 count_off, s32 slot_lo, bool stride28, u32 pc) {
    enter(22);
    open_frame(1);
    s0 = a0;
    kind_call(a0, kind_off, slot_lo, stride28, pc);
    v1 = lw(s0 + count_off);
    v1 = addiu(v1, 1);
    sw(s0 + count_off, v1);
    close_frame(1);
}
// [kobjDraw]: the kind's draw once the counter is positive.
void Fx::kobj_draw(s32 kind_off, s32 count_off, s32 slot_lo, bool stride28, u32 pc) {
    enter(5);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v1 = lw(a0 + count_off);
    if (sgn(v1) > 0) {
        charge(10);
        kind_call(a0, kind_off, slot_lo, stride28, pc);
    }
    charge(4);
    ra = ld(sp);
    sp = addiu(sp, 16);
}
// [kobjUpdateDraw]: the update, ++counter, then the draw once the counter is positive.
void Fx::kobj_update_draw(s32 kind_off, s32 count_off, s32 update_lo, s32 draw_lo, bool stride28, u32 pc_update,
                          u32 pc_draw) {
    enter(19);
    open_frame(1);
    s0 = a0;
    kind_call(a0, kind_off, update_lo, stride28, pc_update);
    v1 = lw(s0 + count_off);
    v1 = addiu(v1, 1);
    sw(s0 + count_off, v1);
    if (sgn(v1) > 0) {
        charge(11);
        a0 = s0;
        kind_call(a0, kind_off, draw_lo, stride28, pc_draw);
    }
    charge(5);
    close_frame(1);
}

// [kobjCreate]: `create(obj->u16 +12, fxBlockA(obj))` -- the class's create from the effect's first data block.
void Fx::kobj_create(rt::Fn create, u32 pc_block, u32 pc_create) {
    enter(15);
    open_frame(1);
    s0 = a0;
    jal(pc_block, gen::fn_sub_3245B0_003245b0);
    a0 = lhu(s0 + 12);
    a1 = v0;
    jal(pc_create, create);
    close_frame(1);
}
// [kobjRecreate]: `create(obj->u16 kind, obj->params)` -- the same create from the instance's own kind and parameters.
void Fx::kobj_recreate(s32 kind_off, s32 params_off, rt::Fn create, u32 pc) {
    enter(11);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v0 = a0;
    a0 = lhu(a0 + kind_off);
    a1 = lw(v0 + params_off);
    jal(pc, create);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_341FD0 / sub_345DB0 [kobjCreateFromEffect] (classes 10 / 16, class slot 0): the instance from the effect's first
// data block (create(u16 +12, fxBlockA)), its parameter word +60 from the kind's slot 1 (fxBlockA, fxBlockB -- no
// second block for the effect type 4 at u16 +28), then the kind's init on it; returns the instance.
void Fx::kobj_create_from_effect(rt::Fn create, s32 param_lo, s32 init_lo, const u32* pc) {
    enter(14);
    open_frame(4);
    s0 = a0;
    jal(pc[0], gen::fn_sub_3245F0_003245f0);
    s2 = v0;  // block B
    v1 = lhu(s0 + 28);
    v0 = 4;
    if (v1 == v0) {
        charge(1);
        s2 = zero;
    } else {
        charge(3);
        v0 = 1;
        if (v1 != v0) charge(2);
    }
    charge(39);
    a0 = s0;
    jal(pc[1], gen::fn_sub_3245B0_003245b0);
    s3 = v0;  // block A
    s0 = lhu(s0 + 12);
    a0 = s0;
    a1 = s3;
    jal(pc[2], create);
    s1 = v0;  // the instance
    v1 = andi(s0, 0xFFFF);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s0 = sll(v0, 2);  // 28 * kind
    a0 = s3;
    a1 = s2;
    v0 = lui(0x6A);
    v0 = addiu(v0, param_lo);
    v0 = addu(v0, s0);
    v0 = lw(v0);
    jalr(pc[3], w(v0));
    sw(s1 + 60, v0);
    a0 = s1;
    v0 = lui(0x6A);
    v0 = addiu(v0, init_lo);
    v0 = addu(v0, s0);
    v0 = lw(v0);
    jalr(pc[4], w(v0));
    v0 = s1;
    close_frame(4);
}
void Fx::sub_341FD0() {
    static constexpr u32 pc[5] = {0x341FECu, 0x342024u, 0x34203Cu, 0x342070u, 0x342090u};
    kobj_create_from_effect(gen::fn_sub_341F10_00341f10, -14252, -14256, pc);
}
void Fx::sub_345DB0() {
    static constexpr u32 pc[5] = {0x345DCCu, 0x345E04u, 0x345E1Cu, 0x345E50u, 0x345E70u};
    kobj_create_from_effect(gen::fn_sub_345CF0_00345cf0, -13964, -13968, pc);
}

// sub_342130 [kobj10Clone] (class 10, class slot 5): a new instance of the same kind and parameters (+56 / +64); when
// the kind has a clone slot (+12) its parameter word comes from that slot on the old instance, else from slot 1 on
// the parameters; then the kind's init on it. Returns the new instance.
void Fx::sub_342130() {
    enter(16);
    open_frame(3);
    s0 = a0;
    a0 = lw(a0 + 56);
    v0 = sll(a0, 3);
    v0 = subu(v0, a0);
    v1 = sll(v0, 2);
    v0 = lui(0x6A);
    v0 = addiu(v0, -14244);  // slot 3 (+12)
    v0 = addu(v0, v1);
    v0 = lw(v0);
    if (v0 == 0) {
        charge(29);
        s1 = lw(s0 + 64);
        s0 = andi(a0, 0xFFFF);
        a0 = s0;
        a1 = s1;
        jal(0x342180u, gen::fn_sub_341F10_00341f10);
        s2 = v0;
        v1 = andi(s0, 0xFFFF);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        s0 = sll(v0, 2);
        a0 = s1;
        a1 = zero;
        v0 = lui(0x6A);
        v0 = addiu(v0, -14252);
        v0 = addu(v0, s0);
        v0 = lw(v0);
        jalr(0x3421B4u, w(v0));
        sw(s2 + 60, v0);
        a0 = s2;
        v0 = lui(0x6A);
        v0 = addiu(v0, -14256);
        v0 = addu(v0, s0);
        v0 = lw(v0);
        jalr(0x3421D4u, w(v0));
    } else {
        charge(28);
        a0 = andi(a0, 0xFFFF);
        a1 = lw(s0 + 64);
        jal(0x3421ECu, gen::fn_sub_341F10_00341f10);
        s2 = v0;
        a0 = s0;
        kind_call(s0, 56, -14244, true, 0x34221Cu);
        sw(s2 + 60, v0);
        a0 = s2;
        kind_call(s0, 56, -14256, true, 0x34224Cu);
    }
    charge(8);
    v0 = s2;
    close_frame(3);
}

// sub_345F00 [kobj16Clone] (class 16, class slot 5): a new instance of the same kind and parameters, its parameter
// word from the kind's slot 3 on the old instance, then the kind's init; returns the new instance.
void Fx::sub_345F00() {
    enter(40);
    open_frame(2);
    s1 = a0;
    a0 = lhu(a0 + 56);
    a1 = lw(s1 + 64);
    jal(0x345F1Cu, gen::fn_sub_345CF0_00345cf0);
    s0 = v0;
    a0 = s1;
    kind_call(s1, 56, -13956, true, 0x345F4Cu);
    sw(s0 + 60, v0);
    a0 = s0;
    kind_call(s1, 56, -13968, true, 0x345F7Cu);
    v0 = s0;
    close_frame(2);
}

// The RW free function the engine keeps at 0x96017C (RwFree): `lui v0, 0x96; lw v0, 380(v0); jalr v0` on $a0.
void Fx::rw_free(u32 pc) {
    v0 = lui(0x96);
    v0 = lw(v0 + 380);
    jalr(pc, w(v0));
}

// sub_345EA0 [kobjDestroy] (class 16, class slot 1; class 13 has the same at sub_337BB0): the kind's destroy slot on
// the instance, then RwFree(instance).
void Fx::kobj_destroy(s32 kind_off, s32 slot_lo, bool stride28, u32 pc_slot, u32 pc_free) {
    enter(24);
    open_frame(1);
    s0 = a0;
    kind_call(a0, kind_off, slot_lo, stride28, pc_slot);
    a0 = s0;
    rw_free(pc_free);
    close_frame(1);
}
// sub_339530 / sub_3420C0 [kobjDestroyParams] (classes 12 / 10): the kind's destroy slot on the parameter block (+60),
// then RwFree(instance).
void Fx::kobj_destroy_params(s32 slot_lo, bool stride28, u32 pc_slot, u32 pc_free) {
    enter(25);
    open_frame(1);
    s0 = a0;
    a0 = lw(a0 + 60);
    kind_call(s0, 56, slot_lo, stride28, pc_slot);
    a0 = s0;
    rw_free(pc_free);
    close_frame(1);
}

// sub_3321D0 [fxTrackFreeKeys]: RwFree(track +40).
void Fx::sub_3321D0() {
    enter(11);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a0 = lw(a0 + 40);
    rw_free(0x3321E4u);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// The destroys of the classes 2 / 7 / 9 / 12 / 13 kinds: release one or two sub-objects (sub_3237C0 the layer
// manager's, sub_324310 the RW atomic release), then RwFree the object (or a block it holds).
// sub_3338B0 [fxObj2Destroy]: sub_324310(+16), sub_324310(+20), RwFree(obj).
void Fx::sub_3338B0() {
    enter(20);
    open_frame(1);
    s0 = a0;
    a0 = lw(a0 + 16);
    jal(0x3338C4u, gen::fn_sub_324310_00324310);
    a0 = lw(s0 + 20);
    jal(0x3338D0u, gen::fn_sub_324310_00324310);
    a0 = s0;
    rw_free(0x3338E4u);
    close_frame(1);
}
// sub_337F80 / sub_338E50 / sub_347300 [fxObjReleaseFree]: release(obj->field), RwFree(obj).
void Fx::release_free(s32 field, rt::Fn release, u32 pc_release, u32 pc_free) {
    enter(17);
    open_frame(1);
    s0 = a0;
    a0 = lw(a0 + field);
    jal(pc_release, release);
    a0 = s0;
    rw_free(pc_free);
    close_frame(1);
}
// sub_339950 [fxKindRelease]: sub_3237C0(block +4), RwFree(block +8) -- the parameter block of a class-12 kind.
void Fx::sub_339950() {
    enter(17);
    open_frame(1);
    s0 = a0;
    a0 = lw(a0 + 4);
    jal(0x339964u, gen::fn_sub_3237C0_003237c0);
    a0 = lw(s0 + 8);
    rw_free(0x339978u);
    close_frame(1);
}
// sub_342A40 [fxKindReleaseAtomic]: block = inst +60; sub_324310(block +4), RwFree(block +8).
void Fx::sub_342A40() {
    enter(17);
    open_frame(1);
    s0 = lw(a0 + 60);
    a0 = lw(s0 + 4);
    jal(0x342A54u, gen::fn_sub_324310_00324310);
    a0 = lw(s0 + 8);
    rw_free(0x342A68u);
    close_frame(1);
}

// The setters of the kind objects (and of the classes 7 / 9 / 21): a quadword, a word or a float of the instance.
void Fx::set_quad(s32 off) {
    enter(4);
    lq(v0, a1);
    sq(a0 + off, v0);
}
void Fx::set_word(s32 off) {
    enter(3);
    sw(a0 + off, a1);
}
void Fx::set_float(s32 off) {
    enter(3);
    swc1(F12, a0 + off);
}
// three floats +off.. = $f12
void Fx::set_float3(s32 off) {
    enter(5);
    swc1(F12, a0 + off);
    swc1(F12, a0 + off + 4);
    swc1(F12, a0 + off + 8);
}
// three floats +off.. = $a1[0..2] (through $f0)
void Fx::copy_float3(s32 off) {
    enter(8);
    lwc1(F0, a1);
    swc1(F0, a0 + off);
    lwc1(F0, a1 + 4);
    swc1(F0, a0 + off + 4);
    lwc1(F0, a1 + 8);
    swc1(F0, a0 + off + 8);
}
// the frame counters of the classes 7 / 9: reset and count
void Fx::zero_word(s32 off) {
    enter(3);
    sw(a0 + off, zero);
}
void Fx::inc_word(s32 off) {
    enter(5);
    v1 = lw(a0 + off);
    v1 = addiu(v1, 1);
    sw(a0 + off, v1);
}

// =====================================================================================================================
// [misc] small class handlers
// =====================================================================================================================

// sub_3342C0 [fxObj2AttachBoth]: sub_3243D0(obj +16, $a1) and sub_3243D0(obj +20, $a1).
void Fx::sub_3342C0() {
    enter(19);
    open_frame(2);
    s1 = a0;
    s0 = a1;
    a0 = lw(a0 + 16);
    jal(0x3342DCu, gen::fn_sub_3243D0_003243d0);
    a0 = lw(s1 + 20);
    a1 = s0;
    jal(0x3342ECu, gen::fn_sub_3243D0_003243d0);
    close_frame(2);
}

// sub_337E10 / sub_338CE0 [fxApplyTint]: copies the four tint bytes gp-18348..gp-18345 into the colour bytes +4..+7 of
// the material (obj +60 -> +0 -> +20). A tint alpha of 255 is written as 254 for the copy and restored after it.
void Fx::apply_tint() {
    enter(6);
    v1 = lw(a0 + 60);
    a0 = lw(v1);
    v1 = lbu(gp - 18345);
    t0 = 255;
    const bool opaque = v1 == t0;
    if (opaque) {
        charge(12);
        v1 = 254;
        sb(gp - 18345, v1);
    } else {
        charge(11);
    }
    a3 = lw(a0 + 20);
    a2 = lbu(gp - 18348);
    a1 = lbu(gp - 18347);
    a0 = lbu(gp - 18346);
    v1 = lbu(gp - 18345);
    sb(a3 + 4, a2);
    sb(a3 + 5, a1);
    sb(a3 + 6, a0);
    sb(a3 + 7, v1);
    if (opaque) sb(gp - 18345, t0);
    charge(2);
}

// sub_3482B0 / sub_348300 [fxObj21Step] (class 21): sub_348110(obj + 4, obj->frame), then ++frame (+0).
void Fx::obj21_step(u32 pc) {
    enter(16);
    open_frame(1);
    s0 = a0;
    a0 = addiu(s0, 4);
    a1 = lw(s0 + 0);
    jal(pc, gen::fn_sub_348110_00348110);
    v1 = lw(s0 + 0);
    v1 = addiu(v1, 1);
    sw(s0 + 0, v1);
    close_frame(1);
}

// sub_34BCF0 [fxRefInc]: ++(+4); returns the object.
void Fx::sub_34BCF0() {
    enter(6);
    v0 = lw(a0 + 4);
    v0 = addiu(v0, 1);
    sw(a0 + 4, v0);
    v0 = a0;
}

// =====================================================================================================================
// [math] the keyframe curve, the shake trigger, the camera position getters
// =====================================================================================================================

// An unsigned word as a float in $f0 (the compiler's idiom: halve, keep the low bit, convert, double when the sign bit
// is set). `hi` / `lo` are the scratch registers the original uses.
void Fx::u32_to_f0(const Gpr& src, Gpr& hi, Gpr& lo) {
    if (sgn(src) < 0) {
        charge(7);
        hi = srl(src, 1);
        lo = andi(src, 1);
        hi = static_cast<u64>(hi) | static_cast<u64>(lo);
        mtc1(hi, F0);
        cvt_s_w(F0, F0);
        add_s(F0, F0, F0);
    } else {
        charge(5);
        mtc1(src, F0);
        cvt_s_w(F0, F0);
    }
}

// sub_32A540 [fxCurveEval]: the value of a keyframe curve $a0 at frame $a1 of $a2, in $f0. Curve: +0 u8 the mode,
// +4 / +8 the start / end values, +20 / +28 the middle values, +24 / +32 the key positions as fractions of the
// duration. Mode 0 interpolates start..end linearly, mode 1 start..mid..end with one key, mode 2 two keys (start ..
// +20 .. +28 .. end); any other mode stays at the start value. A zero duration returns the start value.
void Fx::sub_32A540() {
    enter(2);
    if (a2 == 0) {
        charge(3);
        lwc1(F0, a0 + 4);
        charge(2);
        return;
    }
    charge(7);
    mtc1(a2, F0);
    cvt_s_w(F1, F0);  // duration
    v1 = lbu(a0 + 0);
    v0 = 2;
    // interpolation from $f4 to $f3 by the fraction t = num / den in $f2: lerp_seg(a, b, num_reg, den) forms them
    // as the original does in each case
    auto key_frame = [&](s32 off, Gpr& dst) {
        lwc1(F0, a0 + off);
        mul_s(F0, F0, F1);
        cvt_w_s(F0, F0);
        mfc1(dst, F0);
        at = slt(a1, dst);
    };
    auto frac_from_start = [&](s32 from, s32 to, const Gpr& key) {  // t = frame / key
        charge(14);
        lwc1(F4, a0 + from);
        lwc1(F3, a0 + to);
        mtc1(a1, F0);
        cvt_s_w(F1, F0);
        mtc1(key, F0);
        cvt_s_w(F0, F0);
        div_s(F2, F1, F0);
    };
    auto frac_between = [&](s32 from, s32 to, const Gpr& lo_key, const Gpr& hi_key) {  // t = (frame - lo) / (hi - lo)
        charge(16);
        lwc1(F4, a0 + from);
        lwc1(F3, a0 + to);
        v0 = subu(hi_key, lo_key);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = subu(a1, lo_key);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        div_s(F2, F0, F1);
    };
    if (v1 == v0) {  // mode 2
        charge(8);
        key_frame(24, a3);
        if (at != 0) {
            frac_from_start(4, 20, a3);
        } else {
            charge(8);
            key_frame(32, v1);
            if (at != 0) frac_between(20, 28, a3, v1);
            else frac_between(28, 8, v1, a2);
        }
    } else {
        charge(3);
        v0 = 1;
        if (v1 == v0) {  // mode 1
            charge(8);
            key_frame(24, v1);
            if (at != 0) frac_from_start(4, 20, v1);
            else frac_between(20, 8, v1, a2);
        } else {
            charge(2);
            if (v1 == 0) {  // mode 0: t = frame / duration
                charge(11);
                lwc1(F4, a0 + 4);
                lwc1(F3, a0 + 8);
                mtc1(a1, F0);
                cvt_s_w(F0, F0);
                div_s(F2, F0, F1);
            } else {
                charge(2);
                charge(3);
                lwc1(F4, a0 + 4);
                lwc1(F3, a0 + 8);
                mtc1(zero, F2);
            }
        }
    }
    // $f0 = from + t * (to - from) (ACC = 0 + from, then ACC + t * diff)
    charge(5);
    sub_s(F1, F3, F4);
    mtc1(zero, F0);
    adda_s(F0, F4);
    madd_s(F0, F2, F1);
    charge(2);
}

// sub_348110 [fxShakeStart]: (re)starts the screen shake of the shake record $a0 (+0 its length in frames, +4 u16 the
// strength, +8 / +12 the fade-in / fade-out lengths) at frame $a1. Past the length nothing happens (a length of 0
// never ends). The weight in $f3 is frame / fade-in while fading in, (length - frame) / fade-out in the last fade-out
// frames (0 without a fade-out), else 1; then gp-18328 = 10 * strength * weight, gp-18332 = 4 * that / 10,
// gp-25256 = weight, and the shake's active byte gp-18340 = 1 (sub_347D60 runs it).
void Fx::sub_348110() {
    enter(6);
    a3 = lw(a0 + 0);
    v1 = lui(0x3F80);
    mtc1(v1, F3);  // weight 1.0
    at = slt(a3, a1);
    if (at != 0) {
        charge(2);
        if (a3 != 0) {
            charge(2);
            return;
        }
    }
    charge(2);
    if (sgn(a3) > 0) {
        charge(4);
        v1 = lw(a0 + 8);
        at = sltu(a1, v1);
        if (at != 0) {  // fading in: weight = frame / fade-in
            charge(5);
            mtc1(a1, F0);
            cvt_s_w(F1, F0);
            u32_to_f0(v1, a1, v1);
            charge(8);
            div_s(F3, F1, F0);
        } else {
            charge(5);
            a2 = lw(a0 + 12);
            v1 = subu(a3, a2);
            at = sltu(v1, a1);
            if (at != 0) {  // fading out
                charge(2);
                if (a2 == 0) {
                    charge(1);
                    mtc1(zero, F3);
                } else {
                    charge(6);
                    v1 = subu(a3, a1);
                    mtc1(v1, F0);
                    cvt_s_w(F1, F0);
                    u32_to_f0(a2, a1, v1);
                    charge(8);
                    div_s(F3, F1, F0);
                }
            }
        }
    }
    charge(3);
    v1 = lhu(a0 + 4);
    u32_to_f0(v1, a0, v1);
    charge(14);
    v1 = lui(0x4120);  // 10.0
    mtc1(v1, F2);
    mul_s(F1, F2, F0);
    swc1(F1, gp - 18328);
    v1 = lui(0x4080);  // 4.0
    mtc1(v1, F0);
    mul_s(F0, F0, F1);
    div_s(F0, F0, F2);
    swc1(F0, gp - 18332);
    swc1(F3, gp - 25256);
    v1 = 1;
    sb(gp - 18340, v1);
    charge(2);
}

// sub_329740 / sub_3297A0 [fxCameraPos / fxCameraAt]: the scene camera's (sub_198590 -> +4) frame matrix
// (sub_4CB2F0) row +32 / +48 as a point (x, y, z, 0) at $a0.
void Fx::camera_row(s32 row, u32 pc_scene, u32 pc_matrix) {
    enter(21);
    open_frame(1);
    s0 = a0;
    jal(pc_scene, gen::fn_sub_198590_00198590);
    a0 = lw(v0 + 4);
    jal(pc_matrix, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(F0, v0 + row);
    swc1(F0, s0 + 0);
    lwc1(F0, v0 + row + 4);
    swc1(F0, s0 + 4);
    lwc1(F0, v0 + row + 8);
    swc1(F0, s0 + 8);
    sw(s0 + 12, zero);
    close_frame(1);
}
void Fx::sub_329740() { camera_row(32, 0x329750u, 0x32975Cu); }
void Fx::sub_3297A0() { camera_row(48, 0x3297B0u, 0x3297BCu); }


}  // namespace fx::detail

// --- the public entry points (fx_types.h) ---------------------------------------------------------------------------
namespace gen = ::p3fes::recomp_gen;
u64 sub_3243D0(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, a0);
    ee::core::set_gpr64(ctx, GPR_A1, a1);
    ee::core::set_gpr64(ctx, GPR_A2, a2);
    ee::core::set_gpr64(ctx, GPR_A3, a3);
    fx::detail::Fx(ctx).sub_3243D0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3244C0(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_3244C0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3245B0(EEContext& ctx, u64 rec) {
    ee::core::set_gpr64(ctx, GPR_A0, rec);
    fx::detail::Fx(ctx).sub_3245B0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3245F0(EEContext& ctx, u64 rec) {
    ee::core::set_gpr64(ctx, GPR_A0, rec);
    fx::detail::Fx(ctx).sub_3245F0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324630(EEContext& ctx) {
    fx::detail::Fx(ctx).nop2();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324640(EEContext& ctx) {
    fx::detail::Fx(ctx).nop2();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324650(EEContext& ctx) {
    fx::detail::Fx(ctx).sub_324650();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324660(EEContext& ctx) {
    fx::detail::Fx(ctx).nop2();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324670(EEContext& ctx) {
    fx::detail::Fx(ctx).nop2();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324930(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_324930();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324990(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_324990();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3249E0(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_3249E0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324A30(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_324A30();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324A90(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_324A90();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324AF0(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_324AF0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_324B50(EEContext& ctx, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    fx::detail::Fx(ctx).sub_324B50();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_326160(EEContext& ctx, u64 node, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    ee::core::set_gpr64(ctx, GPR_A1, out);
    fx::detail::Fx(ctx).sub_326160();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_326170(EEContext& ctx, u64 node, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    ee::core::set_gpr64(ctx, GPR_A1, out);
    fx::detail::Fx(ctx).sub_326170();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_326180(EEContext& ctx, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    fx::detail::Fx(ctx).sub_326180();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_326190(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, dst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_326190();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3261C0(EEContext& ctx, u64 node, u64 key) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    ee::core::set_gpr64(ctx, GPR_A1, key);
    fx::detail::Fx(ctx).sub_3261C0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_326200(EEContext& ctx, u64 node, u64 index) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    ee::core::set_gpr64(ctx, GPR_A1, index);
    fx::detail::Fx(ctx).sub_326200();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_326240(EEContext& ctx, u64 node, u64 child) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    ee::core::set_gpr64(ctx, GPR_A1, child);
    fx::detail::Fx(ctx).sub_326240();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_327220(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_327220();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_329350(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_329350();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3293A0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_3293A0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3293D0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_3293D0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_329430(EEContext& ctx, u64 obj, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_329430();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_329460(EEContext& ctx, u64 obj, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_329460();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_329490(EEContext& ctx, u64 obj, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).sub_329490();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3294A0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_3294A0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_329740(EEContext& ctx, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, out);
    fx::detail::Fx(ctx).sub_329740();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3297A0(EEContext& ctx, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, out);
    fx::detail::Fx(ctx).sub_3297A0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_32A540(EEContext& ctx, u64 curve, u64 frame, u64 duration) {
    ee::core::set_gpr64(ctx, GPR_A0, curve);
    ee::core::set_gpr64(ctx, GPR_A1, frame);
    ee::core::set_gpr64(ctx, GPR_A2, duration);
    fx::detail::Fx(ctx).sub_32A540();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3321D0(EEContext& ctx, u64 track) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    fx::detail::Fx(ctx).sub_3321D0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_332200(EEContext& ctx, u64 track) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    fx::detail::Fx(ctx).sub_332200();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_332210(EEContext& ctx, u64 track) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    fx::detail::Fx(ctx).sub_332210();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3322B0(EEContext& ctx, u64 track, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    ee::core::set_gpr64(ctx, GPR_A1, out);
    fx::detail::Fx(ctx).sub_3322B0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3322D0(EEContext& ctx, u64 track, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_3322D0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3322F0(EEContext& ctx, u64 track, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    ee::core::set_gpr64(ctx, GPR_A1, out);
    fx::detail::Fx(ctx).sub_3322F0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_332310(EEContext& ctx, u64 track, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_332310();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_332330(EEContext& ctx, u64 track) {
    ee::core::set_gpr64(ctx, GPR_A0, track);
    fx::detail::Fx(ctx).sub_332330();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_332B30(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_332B30();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_333020(EEContext& ctx, u64 obj, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_333020();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_333050(EEContext& ctx, u64 obj, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).sub_333050();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_333080(EEContext& ctx, u64 obj, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).sub_333080();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3330B0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_3330B0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3338B0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_3338B0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_333900(EEContext& ctx, u64 obj, u64 index) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, index);
    fx::detail::Fx(ctx).sub_333900();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_333920(EEContext& ctx, u64 obj, u64 index) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, index);
    fx::detail::Fx(ctx).sub_333920();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_333940(EEContext& ctx, u64 obj, u64 index) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, index);
    fx::detail::Fx(ctx).sub_333940();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3342C0(EEContext& ctx, u64 obj, u64 arg) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, arg);
    fx::detail::Fx(ctx).sub_3342C0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_337E10(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).apply_tint();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_337F80(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).release_free(0, gen::fn_sub_3237C0_003237c0, 0x337F94u, 0x337FA8u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_338CE0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).apply_tint();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_338E50(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).release_free(0, gen::fn_sub_3237C0_003237c0, 0x338E64u, 0x338E78u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3394F0(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).kobj_create(gen::fn_sub_3393D0_003393d0, 0x339500u, 0x339510u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339530(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_destroy_params(-14760, false, 0x339564u, 0x339578u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3395A0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_recreate(56, 64, gen::fn_sub_3393D0_003393d0, 0x3395B4u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3395D0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_init(56, 52, -14768, false, 0x339600u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339620(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_update(56, 52, -14756, false, 0x339650u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339680(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_draw(56, 52, -14752, false, 0x3396B4u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3396D0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_update_draw(56, 52, -14756, -14752, false, 0x339700u, 0x339740u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339760(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(0);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339770(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(16);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339780(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word(48);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339790(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).set_float3(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3397B0(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).copy_float3(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_339950(EEContext& ctx, u64 block) {
    ee::core::set_gpr64(ctx, GPR_A0, block);
    fx::detail::Fx(ctx).sub_339950();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_341FD0(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_341FD0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3420C0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_destroy_params(-14248, true, 0x3420F4u, 0x342108u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342130(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).sub_342130();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342280(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_init(56, 52, -14256, true, 0x3422B0u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3422D0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_update(56, 52, -14240, true, 0x342300u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342330(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_draw(56, 52, -14236, true, 0x342364u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342380(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_update_draw(56, 52, -14240, -14236, true, 0x3423B0u, 0x3423F0u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342410(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(0);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342420(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(16);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342430(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word(48);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342440(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).set_float3(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342460(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).copy_float3(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_342A40(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).sub_342A40();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_345DB0(EEContext& ctx, u64 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, effect);
    fx::detail::Fx(ctx).sub_345DB0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_345EA0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_destroy(56, -13960, true, 0x345ED0u, 0x345EE4u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_345F00(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).sub_345F00();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_345FA0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_init(56, 52, -13968, true, 0x345FD0u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_345FF0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_update(56, 52, -13952, true, 0x346020u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346050(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_draw(56, 52, -13948, true, 0x346084u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3460A0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).kobj_update_draw(56, 52, -13952, -13948, true, 0x3460D0u, 0x346110u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346130(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(0);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346140(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(16);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346150(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word(48);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346160(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).set_float3(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346180(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).copy_float3(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346500(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).zero_word(44);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_346510(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).inc_word(44);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347130(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(0);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347140(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(16);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347150(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word(36);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347160(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).set_float(32);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347300(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).release_free(88, gen::fn_sub_324310_00324310, 0x347314u, 0x347328u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347380(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).zero_word(16);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347390(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).inc_word(16);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347CE0(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad(0);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347CF0(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word(20);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347D00(EEContext& ctx) {
    fx::detail::Fx(ctx).sub_347D00();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347D60(EEContext& ctx) {
    fx::detail::Fx(ctx).sub_347D60();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_347F80(EEContext& ctx) {
    fx::detail::Fx(ctx).sub_347F80();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_348100(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).zero_word(0);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_348110(EEContext& ctx, u64 rec, u64 frame) {
    ee::core::set_gpr64(ctx, GPR_A0, rec);
    ee::core::set_gpr64(ctx, GPR_A1, frame);
    fx::detail::Fx(ctx).sub_348110();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3482B0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).obj21_step(0x3482C8u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3482F0(EEContext& ctx) {
    fx::detail::Fx(ctx).nop2();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_348300(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).obj21_step(0x348318u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B510(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).zero_word(28);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B520(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).filter_update(-13416, 0x34B550u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B580(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).filter_draw(-13412, 0x34B5A8u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B5C0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).filter_notify(gen::fn_sub_321180_00321180, 0x34B5DCu);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B680(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B690(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word16();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34B6A0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).set_float20();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BA20(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).zero_word(28);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BA30(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).filter_update(-13224, 0x34BA60u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BA90(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).filter_draw(-13220, 0x34BAB8u);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BAD0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).filter_notify(gen::fn_sub_3211D0_003211d0, 0x34BAECu);
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BB90(EEContext& ctx, u64 inst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, src);
    fx::detail::Fx(ctx).set_quad0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BBA0(EEContext& ctx, u64 inst, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    ee::core::set_gpr64(ctx, GPR_A1, value);
    fx::detail::Fx(ctx).set_word16();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BBB0(EEContext& ctx, u64 inst) {
    ee::core::set_gpr64(ctx, GPR_A0, inst);
    fx::detail::Fx(ctx).set_float20();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BCF0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    fx::detail::Fx(ctx).sub_34BCF0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_34BD10(EEContext& ctx) {
    fx::detail::Fx(ctx).sub_34BD10();
    return ee::core::gpr64(ctx, GPR_V0);
}

}  // namespace p3fes::game

namespace p3fes::recomp_gen {
namespace pg = ::p3fes::game;
namespace gen = ::p3fes::recomp_gen;

void fn_sub_3243D0_003243d0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3243D0(); }
void fn_sub_3244C0_003244c0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3244C0(); }
void fn_sub_3245B0_003245b0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3245B0(); }
void fn_sub_3245F0_003245f0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3245F0(); }
void fn_sub_324630_00324630(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).nop2(); }
void fn_sub_324640_00324640(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).nop2(); }
void fn_sub_324650_00324650(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324650(); }
void fn_sub_324660_00324660(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).nop2(); }
void fn_sub_324670_00324670(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).nop2(); }
void fn_sub_324930_00324930(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324930(); }
void fn_sub_324990_00324990(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324990(); }
void fn_sub_3249E0_003249e0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3249E0(); }
void fn_sub_324A30_00324a30(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324A30(); }
void fn_sub_324A90_00324a90(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324A90(); }
void fn_sub_324AF0_00324af0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324AF0(); }
void fn_sub_324B50_00324b50(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_324B50(); }
void fn_sub_326160_00326160(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_326160(); }
void fn_sub_326170_00326170(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_326170(); }
void fn_sub_326180_00326180(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_326180(); }
void fn_sub_326190_00326190(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_326190(); }
void fn_sub_3261C0_003261c0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3261C0(); }
void fn_sub_326200_00326200(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_326200(); }
void fn_sub_326240_00326240(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_326240(); }
void fn_sub_327220_00327220(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_327220(); }
void fn_sub_329350_00329350(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_329350(); }
void fn_sub_3293A0_003293a0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3293A0(); }
void fn_sub_3293D0_003293d0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3293D0(); }
void fn_sub_329430_00329430(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_329430(); }
void fn_sub_329460_00329460(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_329460(); }
void fn_sub_329490_00329490(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_329490(); }
void fn_sub_3294A0_003294a0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3294A0(); }
void fn_sub_329740_00329740(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_329740(); }
void fn_sub_3297A0_003297a0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3297A0(); }
void fn_sub_32A540_0032a540(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_32A540(); }
void fn_sub_3321D0_003321d0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3321D0(); }
void fn_sub_332200_00332200(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_332200(); }
void fn_sub_332210_00332210(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_332210(); }
void fn_sub_3322B0_003322b0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3322B0(); }
void fn_sub_3322D0_003322d0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3322D0(); }
void fn_sub_3322F0_003322f0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3322F0(); }
void fn_sub_332310_00332310(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_332310(); }
void fn_sub_332330_00332330(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_332330(); }
void fn_sub_332B30_00332b30(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_332B30(); }
void fn_sub_333020_00333020(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_333020(); }
void fn_sub_333050_00333050(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_333050(); }
void fn_sub_333080_00333080(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_333080(); }
void fn_sub_3330B0_003330b0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3330B0(); }
void fn_sub_3338B0_003338b0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3338B0(); }
void fn_sub_333900_00333900(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_333900(); }
void fn_sub_333920_00333920(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_333920(); }
void fn_sub_333940_00333940(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_333940(); }
void fn_sub_3342C0_003342c0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_3342C0(); }
void fn_sub_337E10_00337e10(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).apply_tint(); }
void fn_sub_337F80_00337f80(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).release_free(0, gen::fn_sub_3237C0_003237c0, 0x337F94u, 0x337FA8u);
}
void fn_sub_338CE0_00338ce0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).apply_tint(); }
void fn_sub_338E50_00338e50(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).release_free(0, gen::fn_sub_3237C0_003237c0, 0x338E64u, 0x338E78u);
}
void fn_sub_3394F0_003394f0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_create(gen::fn_sub_3393D0_003393d0, 0x339500u, 0x339510u);
}
void fn_sub_339530_00339530(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_destroy_params(-14760, false, 0x339564u, 0x339578u);
}
void fn_sub_3395A0_003395a0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_recreate(56, 64, gen::fn_sub_3393D0_003393d0, 0x3395B4u);
}
void fn_sub_3395D0_003395d0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_init(56, 52, -14768, false, 0x339600u);
}
void fn_sub_339620_00339620(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_update(56, 52, -14756, false, 0x339650u);
}
void fn_sub_339680_00339680(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_draw(56, 52, -14752, false, 0x3396B4u);
}
void fn_sub_3396D0_003396d0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_update_draw(56, 52, -14756, -14752, false, 0x339700u, 0x339740u);
}
void fn_sub_339760_00339760(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(0); }
void fn_sub_339770_00339770(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(16); }
void fn_sub_339780_00339780(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word(48); }
void fn_sub_339790_00339790(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_float3(32); }
void fn_sub_3397B0_003397b0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).copy_float3(32); }
void fn_sub_339950_00339950(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_339950(); }
void fn_sub_341FD0_00341fd0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_341FD0(); }
void fn_sub_3420C0_003420c0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_destroy_params(-14248, true, 0x3420F4u, 0x342108u);
}
void fn_sub_342130_00342130(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_342130(); }
void fn_sub_342280_00342280(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_init(56, 52, -14256, true, 0x3422B0u);
}
void fn_sub_3422D0_003422d0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_update(56, 52, -14240, true, 0x342300u);
}
void fn_sub_342330_00342330(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_draw(56, 52, -14236, true, 0x342364u);
}
void fn_sub_342380_00342380(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_update_draw(56, 52, -14240, -14236, true, 0x3423B0u, 0x3423F0u);
}
void fn_sub_342410_00342410(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(0); }
void fn_sub_342420_00342420(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(16); }
void fn_sub_342430_00342430(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word(48); }
void fn_sub_342440_00342440(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_float3(32); }
void fn_sub_342460_00342460(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).copy_float3(32); }
void fn_sub_342A40_00342a40(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_342A40(); }
void fn_sub_345DB0_00345db0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_345DB0(); }
void fn_sub_345EA0_00345ea0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_destroy(56, -13960, true, 0x345ED0u, 0x345EE4u);
}
void fn_sub_345F00_00345f00(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_345F00(); }
void fn_sub_345FA0_00345fa0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_init(56, 52, -13968, true, 0x345FD0u);
}
void fn_sub_345FF0_00345ff0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_update(56, 52, -13952, true, 0x346020u);
}
void fn_sub_346050_00346050(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_draw(56, 52, -13948, true, 0x346084u);
}
void fn_sub_3460A0_003460a0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).kobj_update_draw(56, 52, -13952, -13948, true, 0x3460D0u, 0x346110u);
}
void fn_sub_346130_00346130(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(0); }
void fn_sub_346140_00346140(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(16); }
void fn_sub_346150_00346150(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word(48); }
void fn_sub_346160_00346160(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_float3(32); }
void fn_sub_346180_00346180(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).copy_float3(32); }
void fn_sub_346500_00346500(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).zero_word(44); }
void fn_sub_346510_00346510(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).inc_word(44); }
void fn_sub_347130_00347130(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(0); }
void fn_sub_347140_00347140(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(16); }
void fn_sub_347150_00347150(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word(36); }
void fn_sub_347160_00347160(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_float(32); }
void fn_sub_347300_00347300(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).release_free(88, gen::fn_sub_324310_00324310, 0x347314u, 0x347328u);
}
void fn_sub_347380_00347380(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).zero_word(16); }
void fn_sub_347390_00347390(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).inc_word(16); }
void fn_sub_347CE0_00347ce0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad(0); }
void fn_sub_347CF0_00347cf0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word(20); }
void fn_sub_347D00_00347d00(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_347D00(); }
void fn_sub_347D60_00347d60(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_347D60(); }
void fn_sub_347F80_00347f80(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_347F80(); }
void fn_sub_348100_00348100(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).zero_word(0); }
void fn_sub_348110_00348110(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_348110(); }
void fn_sub_3482B0_003482b0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).obj21_step(0x3482C8u); }
void fn_sub_3482F0_003482f0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).nop2(); }
void fn_sub_348300_00348300(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).obj21_step(0x348318u); }
void fn_sub_34B510_0034b510(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).zero_word(28); }
void fn_sub_34B520_0034b520(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).filter_update(-13416, 0x34B550u); }
void fn_sub_34B580_0034b580(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).filter_draw(-13412, 0x34B5A8u); }
void fn_sub_34B5C0_0034b5c0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).filter_notify(gen::fn_sub_321180_00321180, 0x34B5DCu);
}
void fn_sub_34B680_0034b680(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad0(); }
void fn_sub_34B690_0034b690(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word16(); }
void fn_sub_34B6A0_0034b6a0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_float20(); }
void fn_sub_34BA20_0034ba20(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).zero_word(28); }
void fn_sub_34BA30_0034ba30(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).filter_update(-13224, 0x34BA60u); }
void fn_sub_34BA90_0034ba90(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).filter_draw(-13220, 0x34BAB8u); }
void fn_sub_34BAD0_0034bad0(p3fes::EEContext& ctx) {
    pg::fx::detail::Fx(ctx).filter_notify(gen::fn_sub_3211D0_003211d0, 0x34BAECu);
}
void fn_sub_34BB90_0034bb90(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_quad0(); }
void fn_sub_34BBA0_0034bba0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_word16(); }
void fn_sub_34BBB0_0034bbb0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).set_float20(); }
void fn_sub_34BCF0_0034bcf0(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_34BCF0(); }
void fn_sub_34BD10_0034bd10(p3fes::EEContext& ctx) { pg::fx::detail::Fx(ctx).sub_34BD10(); }

}  // namespace p3fes::recomp_gen
