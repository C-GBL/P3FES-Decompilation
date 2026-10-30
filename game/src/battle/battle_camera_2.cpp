// Battle camera work states, part 2 (game/include/p3fes/game/battle_camera_2.h), hand-decompiled from SLUS_216.21.
// Phase 5 slice `battle_camera` (battle_camera.cpp has the band's overview, battle_camera_cpu.h the register-faithful
// Cpu view and the cycle model); tests/game/test_battle_camera_2.cpp runs each body against its __recomp body.
#include "battle_camera_cpu.h"
#include "p3fes/game/battle_camera_2.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);  // btlUnit position (unit, out vec3)
void fn_sub_280050_00280050(p3fes::EEContext&);  // btlUnit position (unit, out vec3)
void fn_sub_280870_00280870(p3fes::EEContext&);  // a side's centre (side, ..., out, ...)
void fn_sub_2880E0_002880e0(p3fes::EEContext&);  // btlUnit motion (unit, motion)
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);  // target candidates by skill (action, record, skill, 0)
void fn_sub_2C09F0_002c09f0(p3fes::EEContext&);  // (candidate record)
void fn_sub_2C0880_002c0880(p3fes::EEContext&);  // the current candidate (record)
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_sub_2D1DE0_002d1de0(p3fes::EEContext&);
void fn_sub_2D1F30_002d1f30(p3fes::EEContext&);
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_351BB0_00351bb0(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);  // a direction (out, axis, 1, angles)
void fn_sub_4BE310_004be310(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);  // a rotation matrix (out, axis, angle in $f12, 0)
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);  // vector normalise (out, in)
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);  // vector * matrix (out, in, matrix)
void fn_tanf_0052e930(p3fes::EEContext&);
// this slice (through the generated entry points)
void fn_sub_2A2170_002a2170(p3fes::EEContext&);
void fn_sub_2A2290_002a2290(p3fes::EEContext&);  // camera key (record, eye, target, kind)
void fn_sub_2A3110_002a3110(p3fes::EEContext&);  // field of view (record; $f12)
void fn_sub_2A3160_002a3160(p3fes::EEContext&);
void fn_sub_2A3380_002a3380(p3fes::EEContext&);
void fn_sub_2A3420_002a3420(p3fes::EEContext&);
void fn_sub_2A3520_002a3520(p3fes::EEContext&);
void fn_sub_2A3550_002a3550(p3fes::EEContext&);
void fn_sub_2A3590_002a3590(p3fes::EEContext&);
void fn_sub_2A3750_002a3750(p3fes::EEContext&);
void fn_sub_2A3820_002a3820(p3fes::EEContext&);
void fn_sub_2A3850_002a3850(p3fes::EEContext&);
void fn_sub_2A3E80_002a3e80(p3fes::EEContext&);  // the units' visibility around a camera (action, eye, target, flags)
void fn_sub_2A4470_002a4470(p3fes::EEContext&);
void fn_sub_2A44F0_002a44f0(p3fes::EEContext&);
void fn_sub_2A4690_002a4690(p3fes::EEContext&);  // look-at rotation (out, eye, target, up)
void fn_sub_2AB2A0_002ab2a0(p3fes::EEContext&);
// the recompiled bodies (the placeholders below)
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

using namespace btl_cam;

// The camera work record (gBtl+32; $a0 of every camera state) and the btlUnit fields these states read (obs from the
// instructions).
namespace btl_cam2 {
inline constexpr s32 kCwSubject = 224;      // u32: the subject btlAction (its +48 btlUnit, +26 bit 0 a combatant)
inline constexpr s32 kCwFov = 184;          // f32: the field of view (degrees) the framing distance is computed for
inline constexpr s32 kCwEye = 156;          // vec3: a saved eye position
inline constexpr s32 kCwPhase = 272;        // u16: the phase of the multi-phase states (sub_2AC6E0: 0..6)
inline constexpr s32 kCwPhaseFlag = 276;    // u32
inline constexpr s32 kCwMotionUnit = 288;   // u32: the btlUnit sub_2A3750 / sub_2880E0 act on
inline constexpr s32 kCwMotion = 292;       // u16: its motion
inline constexpr s32 kUnitScale = 44;       // f32: the btlUnit's model scale
inline constexpr s32 kUnitRotation = 28;    // vec3: its rotation (angles)
inline constexpr s32 kUnitHeight = 144;     // f32: its height (model units)
inline constexpr s32 kUnitRadius = 140;     // f32: its radius
inline constexpr s32 kGpFrameWide = -32656;    // f32 1.2: the framing angle factor for a tall unit
inline constexpr u32 kAxisZ = 0x697890;     // vec4 (0, 0, 1): sub_4BE1E0's axis
inline constexpr u32 kAxisUp = 0x697880;    // vec4: the up vector of sub_2A4690 / sub_4C31B0
}  // namespace btl_cam2
using namespace btl_cam2;

class Cpu2 final : public Cpu {
public:
    using Cpu::Cpu;
#define P3FES_BCAM_BODY_2(name, addr) void name();
    P3FES_BCAM_BODIES_2(P3FES_BCAM_BODY_2)
#undef P3FES_BCAM_BODY_2

private:
    void unit_front_shot(u32 base, u32 scale_hi, bool swap);  // sub_2AE260 / sub_2AE4D0
    void motion_if_ready(u32 link_check, u32 link_motion, u64 cyc);  // sub_2AC6E0's tail
    // `a0 = sp + off`
    void a0_sp(s32 off) { a0 = addiu(sp, off); }
    // the frame vec3 sp+dst = sp+x + sp+y, per component `lwc1 $f1, x; lwc1 $f0, y; add.s $f0, $f1, $f0; swc1 $f0, dst`
    void add3_sp(s32 dst, s32 x, s32 y) {
        for (s32 k = 0; k < 12; k += 4) {
            lwc1(F1, sp, x + k);
            lwc1(F0, sp, y + k);
            add_s(F0, F1, F0);
            swc1(F0, sp, dst + k);
        }
    }
    // a 28-byte key at sp+off copied word by word to `dst` when it is non-null (dst advances; `beqz dst` is the
    // caller's block): `a0 = sp + off; v1 = 7; do { v0 = *a0++; *dst++ = v0; } while (--v1 > 0)`
    void copy7_out(Gpr& dst, s32 off) {
        if (dst == 0) return;
        charge(2);
        a0 = addiu(sp, off);
        v1 = li(7);
        for (;;) {
            charge(7);
            lw(v0, a0, 0);
            a0 = addiu(a0, 4);
            v1 = addiu(v1, -1);
            sw(v0, dst, 0);
            dst = addiu(dst, 4);
            if (!gtz(v1)) break;
            backedge();
        }
    }
    // the direction sp+272 *= $f<f> (components left in $f3, $f2, $f1) and the eye sp+dst = sp+256 + it
    void scaled_eye(s32 dst, unsigned f) {
        lwc1(F0, sp, 272);
        mul_s(F3, F0, f);
        swc1(F3, sp, 272);
        lwc1(F0, sp, 276);
        mul_s(F2, F0, f);
        swc1(F2, sp, 276);
        lwc1(F0, sp, 280);
        mul_s(F1, F0, f);
        swc1(F1, sp, 280);
        lwc1(F0, sp, 256);
        add_s(F0, F0, F3);
        swc1(F0, sp, dst);
        lwc1(F0, sp, 260);
        add_s(F0, F0, F2);
        swc1(F0, sp, dst + 4);
        lwc1(F0, sp, 264);
        add_s(F0, F0, F1);
        swc1(F0, sp, dst + 8);
    }
    void side_eye(u32 link_tan, u32 link_norm, unsigned fr, s32 dst);  // sub_2AE740
    // the point sp+p moves sideways by $f<fr> along the normal of the ground part of the direction sp+d (its (x, z)
    // through sp+328, normalised by sub_4C6B20): p.x += n.z * fr ($f5), p.z -= n.x * fr ($f4); $f2 = 0
    void side_shift(s32 d, s32 p, unsigned fr, u32 link_norm) {
        lwc1(F0, sp, d);
        swc1(F0, sp, 328);
        lwc1(F0, sp, d + 8);
        swc1(F0, sp, 332);
        a0_sp(328);
        a1 = a0;
        jal(link_norm, rg::fn_sub_4C6B20_004c6b20);
        lwc1(F1, sp, 332);
        lwc1(F0, sp, p);
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F5, F1, fr);
        swc1(F5, sp, p);
        lwc1(F1, sp, 328);
        lwc1(F0, sp, p + 8);
        adda_s(F2, F0);
        msub_s(F4, F1, fr);
        swc1(F4, sp, p + 8);
    }
    // the frame vec3 sp+d *= $f<f> through $f0 (each component stored back)
    void scale3_in(s32 d, unsigned f) { scale3_sp(d, d, f); }
    // $f12 = tan(1.2 * fov / 2) of the camera work record in s4 (and the tanf call)
    void tan_fov_wide(const Gpr& cw, u32 link) {
        lif(v0, 0x3f00, F1);
        lwc1(F0, cw, kCwFov);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, kGpFrameWide);
        mul_s(F12, F0, F1);
        jal(link, rg::fn_tanf_0052e930);
    }
    void skill_heights_2AA2B0();  // sub_2AA2B0's fixed-height table
    // sub_2AB330's steps
    void aim_and_measure(s32 rot, u32 link_look, u32 link_dir, u32 link_dist);
    void push_side(u32 link_tan, u32 link_norm, u32 k_hi, s32 d, bool neg);
    void eye_from_dir(s32 dst);
    // the frame vec3 sp+off *= $f<f>, per component `lwc1 $f0; mul.s $f0, $f0, f; swc1 $f0` (into sp+dst)
    void scale3_sp(s32 dst, s32 off, unsigned f) {
        for (s32 k = 0; k < 12; k += 4) {
            lwc1(F0, sp, off + k);
            mul_s(F0, F0, f);
            swc1(F0, sp, dst + k);
        }
    }
    // `lui rX, 0x69; addiu rX, rX, lo` (the constant vectors at 0x697880 / 0x697890)
    void la69(Gpr& r, s32 lo) {
        r = lui(0x69);
        r = addiu(r, lo);
    }
};

// =====================================================================================================================
// Hand-written bodies
// =====================================================================================================================

// 0x2AF7F0 sub_2AF7F0(cw): the target-cursor camera's init (row 29). The subject's candidates for its skill
// (sub_2BFF60(action, 0, action+110, 0)) -> cw+262, the first candidate's index (sub_2C09F0(action+136)) -> cw+260,
// cw+256 = 0.
void Cpu2::sub_2AF7F0() {
    enter(24);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(s0, a0, kCwSubject);
    a0 = s0;
    a1 = 0;
    lhu(a2, s0, 110);
    a3 = 0;
    jal(0x2af818, rg::fn_sub_2BFF60_002bff60);
    sh(v0, s1, 262);
    a0 = addiu(s0, 136);
    jal(0x2af828, rg::fn_sub_2C09F0_002c09f0);
    sh(v0, s1, 260);
    sw(zero, s1, 256);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// The body of sub_2AE260 / sub_2AE4D0 (compiled twice; `base` = the function's start, the jal links are base + the same
// offsets): a frontal shot of the subject's unit. Its position (sub_27FFB0), height h = +144 * scale, half radius
// r = +140 * scale / 2; the position's y += r / 4. The distance d = scale_hi-float (1.25 / 1.5) * max(h, r) /
// tan(fov / 2 (* 1.2 when h > r)). The direction of the unit's rotation (sub_4BE1E0(dir, (0,0,1), 1, unit+28)) times
// (d + 125) gives the eye = position + it; the look-at rotation sub_2A4690(rot, eye, position, up) and the key
// {eye, rot} / {position + dir * d, rot} go to sub_2A2290(cw, a, b, 1) (`swap` exchanges a and b); the units around
// are shown (sub_2A3E80(subject, 0, 0, 1)) and the field of view is 2.5 (sub_2A3110).
void Cpu2::unit_front_shot(u32 base, u32 scale_hi, bool swap) {
    enter(35);
    sp = addiu(sp, -176);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    lw(v0, a0, kCwSubject);
    lw(s0, v0, 48);
    a0 = s0;
    a1 = addiu(sp, 160);
    jal(base + 0x34, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s0, kUnitScale);
    lwc1(F0, s0, kUnitHeight);
    mul_s(F20, F0, F1);
    lwc1(F0, s0, kUnitRadius);
    mul_s(F0, F0, F1);
    lif(v0, 0x3f00, F3);  // 0.5
    mul_s(F21, F3, F0);
    lif(v0, 0x3e80, F2);  // 0.25
    lwc1(F1, sp, 164);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F21);
    swc1(F0, sp, 164);
    c_le_s(F20, F21);
    if (!cc()) {
        charge(16);
        lwc1(F0, s1, kCwFov);
        mul_s(F1, F3, F0);
        lwc1(F0, gp, kGpFrameWide);
        mul_s(F12, F0, F1);
        jal(base + 0x9c, rg::fn_tanf_0052e930);
        lif(v0, scale_hi, F1);
        mul_s(F1, F1, F20);
        div_s(F20, F1, F0);
    } else {
        charge(9);
        lwc1(F0, s1, kCwFov);
        mul_s(F12, F3, F0);
        jal(base + 0xd4, rg::fn_tanf_0052e930);
        lif(v0, scale_hi, F1);
        mul_s(F1, F1, F21);
        div_s(F20, F1, F0);
    }
    charge(91);
    a0_sp(144);
    la69(a1, 30864);  // (0, 0, 1)
    a2 = li(1);
    a3 = addiu(s0, kUnitRotation);
    jal(base + 0x104, rg::fn_sub_4BE1E0_004be1e0);
    lif(v0, 0x42fa, F0);  // 125.0
    add_s(F1, F0, F20);
    lwc1(F0, sp, 144);
    mul_s(F23, F0, F1);
    lwc1(F0, sp, 148);
    mul_s(F22, F0, F1);
    lwc1(F0, sp, 152);
    mul_s(F21, F0, F1);
    lwc1(F0, sp, 160);
    add_s(F0, F0, F23);
    swc1(F0, sp, 128);
    lwc1(F0, sp, 164);
    add_s(F0, F0, F22);
    swc1(F0, sp, 132);
    lwc1(F0, sp, 168);
    add_s(F0, F0, F21);
    swc1(F0, sp, 136);
    a0_sp(76);
    a1 = addiu(sp, 128);
    a2 = addiu(sp, 160);
    la69(a3, 30848);  // up
    jal(base + 0x16c, rg::fn_sub_2A4690_002a4690);
    // key 1 (sp+64): the eye and the rotation; key 2 (sp+92): position + dir * d and the same rotation
    lwc1(F6, sp, 160);
    add_s(F0, F6, F23);
    swc1(F0, sp, 64);
    lwc1(F5, sp, 164);
    add_s(F0, F5, F22);
    swc1(F0, sp, 68);
    lwc1(F4, sp, 168);
    add_s(F0, F4, F21);
    swc1(F0, sp, 72);
    lwc1(F3, sp, 76);
    lwc1(F2, sp, 80);
    lwc1(F1, sp, 84);
    lwc1(F0, sp, 88);
    swc1(F3, sp, 104);
    swc1(F2, sp, 108);
    swc1(F1, sp, 112);
    swc1(F0, sp, 116);
    lwc1(F0, sp, 144);
    mtc1(zero, F12);
    adda_s(F12, F6);
    madd_s(F0, F0, F20);
    swc1(F0, sp, 92);
    lwc1(F0, sp, 148);
    adda_s(F12, F5);
    madd_s(F0, F0, F20);
    swc1(F0, sp, 96);
    lwc1(F0, sp, 152);
    adda_s(F12, F4);
    madd_s(F0, F0, F20);
    swc1(F0, sp, 100);
    lw(a0, s1, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(base + 0x200, rg::fn_sub_2A3E80_002a3e80);
    a0 = s1;
    a1 = addiu(sp, swap ? 92 : 64);
    a2 = addiu(sp, swap ? 64 : 92);
    a3 = li(1);
    jal(base + 0x218, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4020, F12);  // 2.5
    a0 = s1;
    jal(base + 0x22c, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 176);
}

// 0x2AE260 sub_2AE260(cw): the unit front shot of camera row 26 (init): distance factor 1.25, the eye key first.
void Cpu2::sub_2AE260() { unit_front_shot(0x2ae260, 0x3fa0, false); }
// 0x2AE4D0 sub_2AE4D0(cw): row 27's init: the same shot with distance factor 1.5 and the keys the other way round
// (from the near point to the eye).
void Cpu2::sub_2AE4D0() { unit_front_shot(0x2ae4d0, 0x3fc0, true); }

// 0x2AD880 sub_2AD880(cw; $f12 = yaw, $f13 = distance factor, $f14 = height factor, $f15 = minimum distance): a two-key
// sweep around the subject's unit. Its position p (sub_27FFB0) with p.y += r * $f14 (h = +144 * scale, r = +140 *
// scale / 2); the distance d = $f13 * max(h, r) / tan(fov / 2 (* 1.2 when h > r)), at least $f15. The offset o =
// normalise(dir(rotation) * h + (0, 0.2 r, 0)) * d (sub_4BE1E0 / sub_4C69F0), turned by +yaw and by -yaw about the up
// axis (sub_4C31B0 / sub_4C6C60): the two eyes p + o' with their look-at rotations at p (sub_2A4690) are the keys of
// sub_2A2290(cw, key1, key2, 1); the units around are shown (sub_2A3E80(subject, 0, 0, 1), $f12 = 0) and the field of
// view is 3.5 (sub_2A3110).
void Cpu2::sub_2AD880() {
    enter(43);
    sp = addiu(sp, -304);
    sd(ra, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    mov_s(F25, F12);
    mov_s(F24, F13);
    mov_s(F20, F14);
    mov_s(F23, F15);
    lw(v0, a0, kCwSubject);
    lw(s1, v0, 48);
    a0 = s1;
    a1 = addiu(sp, 288);
    jal(0x2ad8cc, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s1, kUnitScale);
    lwc1(F0, s1, kUnitHeight);
    mul_s(F22, F0, F1);  // h
    lwc1(F0, s1, kUnitRadius);
    mul_s(F0, F0, F1);
    lif(v0, 0x3f00, F2);
    mul_s(F21, F2, F0);  // r
    // p = sp+272 (a doubleword copy of x, y and a word copy of z), p.y += r * $f14
    ld(v0, sp, 288);
    lwc1(F0, sp, 296);
    sd(v0, sp, 272);
    swc1(F0, sp, 280);
    lwc1(F1, sp, 276);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F21, F20);
    swc1(F0, sp, 276);
    c_le_s(F22, F21);
    if (!cc()) {
        charge(14);
        lwc1(F0, s0, kCwFov);
        mul_s(F1, F2, F0);
        lwc1(F0, gp, kGpFrameWide);
        mul_s(F12, F0, F1);
        jal(0x2ad93c, rg::fn_tanf_0052e930);
        mul_s(F1, F22, F24);
        div_s(F20, F1, F0);
    } else {
        charge(7);
        lwc1(F0, s0, kCwFov);
        mul_s(F12, F2, F0);
        jal(0x2ad96c, rg::fn_tanf_0052e930);
        mul_s(F1, F21, F24);
        div_s(F20, F1, F0);
    }
    charge(3);
    c_lt_s(F20, F23);
    if (cc()) {
        charge(1);
        mov_s(F20, F23);
    }
    charge(166);
    a0_sp(256);
    la69(a1, 30864);
    a2 = li(1);
    a3 = addiu(s1, kUnitRotation);
    jal(0x2ad9a4, rg::fn_sub_4BE1E0_004be1e0);
    // sp+208 = dir * h; sp+224 = p + it with y = 0.2 r + that; sp+240 = sp+224 - p, normalised, * d -> sp+208
    lwc1(F0, sp, 256);
    mul_s(F2, F0, F22);
    swc1(F2, sp, 208);
    lwc1(F0, sp, 260);
    mul_s(F1, F0, F22);
    swc1(F1, sp, 212);
    lwc1(F0, sp, 264);
    mul_s(F0, F0, F22);
    swc1(F0, sp, 216);
    lwc1(F7, sp, 272);
    add_s(F6, F7, F2);
    swc1(F6, sp, 224);
    lwc1(F5, sp, 276);
    add_s(F4, F5, F1);
    swc1(F4, sp, 228);
    lwc1(F3, sp, 280);
    add_s(F2, F3, F0);
    swc1(F2, sp, 232);
    lwc1(F1, gp, -32588);  // 0.2
    mtc1(zero, F0);
    adda_s(F0, F4);
    madd_s(F1, F1, F21);
    swc1(F1, sp, 228);
    sub_s(F0, F6, F7);
    swc1(F0, sp, 240);
    sub_s(F0, F1, F5);
    swc1(F0, sp, 244);
    sub_s(F0, F2, F3);
    swc1(F0, sp, 248);
    a0_sp(240);
    a1 = a0;
    jal(0x2ada2c, rg::fn_sub_4C69F0_004c69f0);
    scale3_sp(208, 240, F20);
    // +yaw: the rotation sp+80, o' = sp+240, eye 1 = p + o' (sp+224), its rotation sp+156 (key 1 = sp+144)
    a0_sp(80);
    la69(a1, 30848);
    mov_s(F12, F25);
    a2 = 0;
    jal(0x2ada6c, rg::fn_sub_4C31B0_004c31b0);
    a0_sp(240);
    a1 = addiu(sp, 208);
    a2 = addiu(sp, 80);
    jal(0x2ada80, rg::fn_sub_4C6C60_004c6c60);
    add3_sp(224, 272, 240);
    a0_sp(156);
    a1 = addiu(sp, 224);
    a2 = addiu(sp, 272);
    la69(a3, 30848);
    jal(0x2adacc, rg::fn_sub_2A4690_002a4690);
    add3_sp(144, 272, 240);
    // -yaw: eye 2 (key 2 = sp+172, its rotation sp+184)
    neg_s(F12, F25);
    a0_sp(80);
    la69(a1, 30848);
    a2 = 0;
    jal(0x2adb18, rg::fn_sub_4C31B0_004c31b0);
    a0_sp(240);
    a1 = addiu(sp, 208);
    a2 = addiu(sp, 80);
    jal(0x2adb2c, rg::fn_sub_4C6C60_004c6c60);
    add3_sp(224, 272, 240);
    a0_sp(184);
    a1 = addiu(sp, 224);
    a2 = addiu(sp, 272);
    la69(a3, 30848);
    jal(0x2adb78, rg::fn_sub_2A4690_002a4690);
    add3_sp(172, 272, 240);
    mtc1(zero, F12);
    lw(a0, s0, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(0x2adbc4, rg::fn_sub_2A3E80_002a3e80);
    a0 = s0;
    a1 = addiu(sp, 144);
    a2 = addiu(sp, 172);
    a3 = li(1);
    jal(0x2adbdc, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4060, F12);  // 3.5
    a0 = s0;
    jal(0x2adbf0, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 304);
}

// 0x2ADD10 sub_2ADD10(cw, a1 = result, a2 = key A out, a3 = key B out) -> $v0: an over-the-shoulder shot of the subject
// towards the enemy side. The current key A (a copy of cw+156, 28 bytes, at sp+128); the enemies' centre c = sp+192
// and spread ($f0 -> $f21) from sub_280870(2, 0, c, &spread, 0, 1), c.y = spread * gp-32572; the subject's unit
// position p (sub_27FFB0), raised by its radius * gp-32668, moved along the direction from sub_2D1DE0(p, c)
// (sub_4BE1E0 with the axis 0x697870) by its height * gp-32500; the look-at target t = c + normalise(p - c) * |p - c|
// * gp-32636; key B's rotation looks from p to t (sub_2A4690) and its angle (sub_2D1F30) beyond gp-32496 sets the
// result (else a1 is returned). The eye distance is max(radius / tan(fov/2) + |p - c|, 0.875 * spread /
// tan(fov/2)); the eye = c +/- a sideways offset of distance * tan(1.2 fov/2) * 0.109375 * 1.25 along the key's
// direction (sub_4BE1E0 axis 0x6978A0) plus that direction * distance; both keys' y at least 25. Key A (sp+128) and
// key B (sp+156) are copied out (7 words each) when a2 / a3 are non-null.
void Cpu2::sub_2ADD10() {
    enter(135);
    sp = addiu(sp, -272);
    sd(ra, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    a0_sp(128);
    a1 = addiu(s4, kCwEye);
    jal(0x2add50, rg::fn_sub_2A4470_002a4470);
    a0 = li(2);
    a1 = 0;
    a2 = addiu(sp, 192);
    a3 = addiu(sp, 268);
    t0 = 0;
    t1 = li(1);
    jal(0x2add70, rg::fn_sub_280870_00280870);
    mov_s(F21, F0);
    lwc1(F1, gp, -32572);
    lwc1(F0, sp, 268);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 196);
    lw(v0, s4, kCwSubject);
    lw(s0, v0, 48);
    lwc1(F1, s0, kUnitHeight);
    lwc1(F0, s0, kUnitScale);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32500);
    mul_s(F20, F1, F0);
    a0 = s0;
    a1 = addiu(sp, 208);
    jal(0x2addb0, rg::fn_sub_27FFB0_0027ffb0);
    a0_sp(112);
    a1 = addiu(sp, 208);
    a2 = addiu(sp, 192);
    jal(0x2addc4, rg::fn_sub_2D1DE0_002d1de0);
    lwc1(F1, s0, kUnitRadius);
    lwc1(F0, s0, kUnitScale);
    mul_s(F3, F1, F0);
    lwc1(F2, gp, -32668);
    lwc1(F1, sp, 212);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F3);
    swc1(F0, sp, 212);
    a0_sp(256);
    la69(a1, 30832);
    a2 = li(1);
    a3 = addiu(sp, 112);
    jal(0x2ade08, rg::fn_sub_4BE1E0_004be1e0);
    // sp+256 *= $f20; p (sp+208) += it; sp+240 = p - c
    lwc1(F0, sp, 256);
    mul_s(F3, F0, F20);
    swc1(F3, sp, 256);
    lwc1(F0, sp, 260);
    mul_s(F2, F0, F20);
    swc1(F2, sp, 260);
    lwc1(F0, sp, 264);
    mul_s(F1, F0, F20);
    swc1(F1, sp, 264);
    lwc1(F0, sp, 208);
    add_s(F3, F0, F3);
    swc1(F3, sp, 208);
    lwc1(F0, sp, 212);
    add_s(F2, F0, F2);
    swc1(F2, sp, 212);
    lwc1(F0, sp, 216);
    add_s(F1, F0, F1);
    swc1(F1, sp, 216);
    lwc1(F0, sp, 192);
    sub_s(F0, F3, F0);
    swc1(F0, sp, 240);
    lwc1(F0, sp, 196);
    sub_s(F0, F2, F0);
    swc1(F0, sp, 244);
    lwc1(F0, sp, 200);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 248);
    a0_sp(240);
    a1 = a0;
    jal(0x2ade84, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F20, F0);  // |p - c|
    // t (sp+224) = c + normalised * |p - c| * gp-32636
    lwc1(F1, gp, -32636);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 240);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 224);
    lwc1(F0, sp, 244);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 228);
    lwc1(F0, sp, 248);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 232);
    lwc1(F0, sp, 192);
    add_s(F0, F3, F0);
    swc1(F0, sp, 224);
    lwc1(F0, sp, 196);
    add_s(F0, F2, F0);
    swc1(F0, sp, 228);
    lwc1(F0, sp, 200);
    add_s(F0, F1, F0);
    swc1(F0, sp, 232);
    a1 = addiu(sp, 256);
    ld(v0, sp, 208);
    lwc1(F0, sp, 216);
    sd(v0, sp, 256);
    swc1(F0, sp, 264);
    a0_sp(168);
    a2 = addiu(sp, 224);
    la69(a3, 30848);
    jal(0x2adf04, rg::fn_sub_2A4690_002a4690);
    a0_sp(140);
    a1 = addiu(sp, 168);
    jal(0x2adf14, rg::fn_sub_2D1F30_002d1f30);
    lwc1(F1, gp, -32496);
    c_le_s(F0, F1);
    if (!cc()) {
        charge(1);
        s3 = li(1);
    }
    charge(29);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s4, kCwFov);
    mul_s(F12, F1, F0);
    lwc1(F1, s0, kUnitRadius);
    lwc1(F0, s0, kUnitScale);
    mul_s(F22, F1, F0);
    jal(0x2adf4c, rg::fn_tanf_0052e930);
    div_s(F0, F22, F0);
    add_s(F20, F0, F20);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s4, kCwFov);
    mul_s(F12, F1, F0);
    jal(0x2adf74, rg::fn_tanf_0052e930);
    lif(v0, 0x3f60, F1);  // 0.875
    mul_s(F1, F1, F21);
    div_s(F0, F1, F0);
    c_le_s(F20, F0);
    if (cc()) {
        charge(1);
        mov_s(F20, F0);
    } else {
        charge(2);
    }
    charge(57);
    a0_sp(256);
    la69(a1, 30880);
    a2 = li(1);
    a3 = addiu(sp, 168);
    jal(0x2adfc4, rg::fn_sub_4BE1E0_004be1e0);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s4, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, kGpFrameWide);
    mul_s(F12, F0, F1);
    jal(0x2adfe4, rg::fn_tanf_0052e930);
    mul_s(F1, F20, F0);
    lif(v0, 0x3de0, F0);  // 0.109375
    mul_s(F1, F1, F0);
    lif(v0, 0x3fa0, F0);  // 1.25
    mul_s(F3, F1, F0);
    // c.x += dir.z * side, c.z -= dir.x * side; dir *= distance; key B's eye (sp+156) = c + dir
    lwc1(F6, sp, 264);
    lwc1(F0, sp, 192);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F5, F6, F3);
    swc1(F5, sp, 192);
    lwc1(F1, sp, 256);
    lwc1(F0, sp, 200);
    adda_s(F2, F0);
    msub_s(F4, F1, F3);
    swc1(F4, sp, 200);
    mul_s(F3, F1, F20);
    swc1(F3, sp, 256);
    lwc1(F0, sp, 260);
    mul_s(F2, F0, F20);
    swc1(F2, sp, 260);
    mul_s(F1, F6, F20);
    swc1(F1, sp, 264);
    add_s(F0, F5, F3);
    swc1(F0, sp, 156);
    lwc1(F0, sp, 196);
    add_s(F0, F0, F2);
    swc1(F0, sp, 160);
    add_s(F0, F4, F1);
    swc1(F0, sp, 164);
    // both eyes at least 25 high
    lwc1(F1, sp, 132);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 132);
    }
    charge(7);
    lwc1(F1, sp, 160);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 160);
    }
    charge(2);
    copy7_out(s2, 128);
    charge(2);
    copy7_out(s1, 156);
    charge(13);
    v0 = s3;
    ld(ra, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 272);
}

// 0x2AC920 sub_2AC920(cw): a two-shot of the subject's unit A and its first target's unit B (action+56 -> +48). The
// direction d = normalise(A - B) (length L), the ground vector g = normalise2(cw+156 - A) (x, z; sub_4C6B20), the
// look-at point m = B + d * L * gp-32616. The side of g against d (dot((d.x, d.z), g) = $f24 >= 0: A is the near unit,
// else B) picks the near unit N, the far unit F, the pivot P = N's position and the factors: A near -> lateral
// 1.5 * A's height, height factor gp-32620, offset factor 1.5, P.y at least 125; B near -> lateral (1.5 for a party
// unit, 1.25 for an enemy) * B's height, height and offset factor 0.25, eye factor 3.5 / 1.75. The eye side is the sign
// of g against d's normal ($f25); the eye = P +/- d's normal * lateral, y = P.y + factor * N's radius; the rotation
// from it to m (sub_2A4690) gives the direction sp+272 (sub_4BE1E0); sub_2D1FD0 the distance along it, scaled by
// N's height * the eye factor and divided by tan(1.2 fov/2) (at least 500). Then a sideways nudge by N's height, the
// eye y = P.y + 0.25-ish * N's radius, key A = cw+156, key B = that eye + the scaled direction. When the angle between
// the keys' rotations (sub_2D1F30) exceeds gp-32460: key B = key A's rotation (sub_2A44F0), moved back 150 along it,
// flags 3, sound/effect sub_351BB0(12), field of view 1.5; else flags 51 and the field of view gp-32600. Both eyes at
// least 25 high; the units around are shown (sub_2A3E80(subject, F+4, key B, flags), $f12 = 50), the key pair is
// sub_2A2290(cw, A, B, 1) and the field of view sub_2A3110.
void Cpu2::sub_2AC920() {
    enter(85);
    sp = addiu(sp, -352);
    sd(ra, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    lw(v0, a0, kCwSubject);
    lw(s4, v0, 48);
    lw(v0, v0, kActTargets);
    lw(s3, v0, 48);
    a0 = s4;
    a1 = addiu(sp, 336);
    jal(0x2ac970, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s3;
    a1 = addiu(sp, 320);
    jal(0x2ac980, rg::fn_sub_27FFB0_0027ffb0);
    // d = sp+272 = A - B, normalised (length -> $f20)
    lwc1(F1, sp, 336);
    lwc1(F0, sp, 320);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 272);
    lwc1(F1, sp, 340);
    lwc1(F0, sp, 324);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 276);
    lwc1(F1, sp, 344);
    lwc1(F0, sp, 328);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 280);
    a0_sp(272);
    a1 = a0;
    jal(0x2ac9c0, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F20, F0);
    // g = sp+200 = (cw+156 - A).xz, normalised
    lwc1(F1, s0, kCwEye);
    lwc1(F0, sp, 336);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 200);
    lwc1(F1, s0, kCwEye + 8);
    lwc1(F0, sp, 344);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 204);
    a0_sp(200);
    a1 = a0;
    jal(0x2ac9f4, rg::fn_sub_4C6B20_004c6b20);
    // m = sp+288 = B + d * L * gp-32616
    lwc1(F0, gp, -32616);
    mul_s(F2, F0, F20);
    lwc1(F1, sp, 272);
    mul_s(F5, F1, F2);
    swc1(F5, sp, 288);
    lwc1(F0, sp, 276);
    mul_s(F4, F0, F2);
    swc1(F4, sp, 292);
    lwc1(F0, sp, 280);
    mul_s(F3, F0, F2);
    swc1(F3, sp, 296);
    lwc1(F2, sp, 320);
    add_s(F2, F5, F2);
    swc1(F2, sp, 288);
    lwc1(F2, sp, 324);
    add_s(F2, F4, F2);
    swc1(F2, sp, 292);
    lwc1(F2, sp, 328);
    add_s(F2, F3, F2);
    swc1(F2, sp, 296);
    // $f1 = d.x, $f0 = d.z; $f24 = dot((d.x, d.z), g)
    swc1(F1, sp, 192);
    swc1(F0, sp, 196);
    lwc1(F3, sp, 200);
    lwc1(F2, sp, 204);
    mula_s(F0, F2);
    mtc1(zero, F5);
    madd_s(F24, F1, F3);
    c_lt_s(F24, F5);
    if (!cc()) {
        // A near: N = s1 = A, F = s2 = B, P = A
        charge(21);
        s1 = s4;
        s2 = s3;
        ld(v0, sp, 336);
        lwc1(F2, sp, 344);
        sd(v0, sp, 304);
        swc1(F2, sp, 312);
        lwc1(F3, s4, kUnitHeight);
        lwc1(F2, s4, kUnitScale);
        mul_s(F2, F3, F2);
        lif(v0, 0x3fc0, F23);
        mul_s(F6, F23, F2);
        lwc1(F22, gp, -32620);
        lwc1(F3, sp, 308);
        lif(v0, 0x42fa, F2);  // 125
        c_lt_s(F3, F2);
        if (cc()) {
            charge(3);
            swc1(F2, sp, 308);
        }
    } else {
        // B near: N = s1 = B, F = s2 = A, P = B
        charge(9);
        s1 = s3;
        s2 = s4;
        ld(v0, sp, 320);
        lwc1(F2, sp, 328);
        sd(v0, sp, 304);
        swc1(F2, sp, 312);
        lbu(v0, s3, btl_task::kUnitSide);
        if (v0 == 0) {
            charge(11);
            lwc1(F3, s3, kUnitHeight);
            lwc1(F2, s3, kUnitScale);
            mul_s(F3, F3, F2);
            lif(v0, 0x3fc0, F2);
            mul_s(F6, F2, F3);
            lif(v0, 0x4060, F23);
        } else {
            charge(9);
            lwc1(F3, s3, kUnitHeight);
            lwc1(F2, s3, kUnitScale);
            mul_s(F3, F3, F2);
            lif(v0, 0x3fa0, F2);
            mul_s(F6, F2, F3);
            lif(v0, 0x3fe0, F23);
        }
        charge(4);
        lif(v0, 0x3e80, F22);
        mov_s(F5, F22);
    }
    charge(18);
    // the normal (d.z, -d.x) -> sp+192; $f25 = dot(normal, g); the eye sp+256: y = P.y + $f5 * N's radius
    swc1(F0, sp, 192);
    neg_s(F4, F1);
    swc1(F4, sp, 196);
    lwc1(F3, sp, 200);
    lwc1(F2, sp, 204);
    mula_s(F4, F2);
    mtc1(zero, F4);
    madd_s(F25, F0, F3);
    lwc1(F20, sp, 308);
    lwc1(F3, s1, kUnitRadius);
    lwc1(F2, s1, kUnitScale);
    mul_s(F2, F3, F2);
    adda_s(F4, F20);
    madd_s(F2, F5, F2);
    swc1(F2, sp, 260);
    c_lt_s(F25, F4);
    if (!cc()) {
        charge(10);
        lwc1(F2, sp, 304);
        adda_s(F4, F2);
        madd_s(F0, F0, F6);
        swc1(F0, sp, 256);
        lwc1(F21, sp, 312);
        adda_s(F4, F21);
        msub_s(F0, F1, F6);
        swc1(F0, sp, 264);
    } else {
        charge(8);
        lwc1(F2, sp, 304);
        adda_s(F4, F2);
        msub_s(F0, F0, F6);
        swc1(F0, sp, 256);
        lwc1(F21, sp, 312);
        adda_s(F4, F21);
        madd_s(F0, F1, F6);
        swc1(F0, sp, 264);
    }
    charge(64);
    ld(v0, sp, 272);
    lwc1(F0, sp, 280);
    sd(v0, sp, 240);
    swc1(F0, sp, 248);
    a0_sp(168);
    a1 = addiu(sp, 256);
    a2 = addiu(sp, 288);
    la69(a3, 30848);
    jal(0x2acc0c, rg::fn_sub_2A4690_002a4690);
    a0_sp(272);
    la69(a1, 30880);
    a2 = li(1);
    a3 = addiu(sp, 168);
    jal(0x2acc28, rg::fn_sub_4BE1E0_004be1e0);
    // sub_2D1FD0((m.x, m.z), (eye.x, eye.z), (P.x, P.z), out sp+224)
    lwc1(F0, sp, 288);
    swc1(F0, sp, 208);
    lwc1(F0, sp, 296);
    swc1(F0, sp, 212);
    lwc1(F0, sp, 256);
    swc1(F0, sp, 216);
    lwc1(F0, sp, 264);
    swc1(F0, sp, 220);
    lwc1(F0, sp, 304);
    swc1(F0, sp, 232);
    swc1(F21, sp, 236);
    a0_sp(208);
    a1 = addiu(sp, 216);
    a2 = addiu(sp, 232);
    a3 = addiu(sp, 224);
    jal(0x2acc6c, rg::fn_sub_2D1FD0_002d1fd0);
    lwc1(F2, s1, kUnitHeight);
    lwc1(F1, s1, kUnitScale);
    mul_s(F2, F2, F1);
    mtc1(zero, F1);
    adda_s(F1, F0);
    madd_s(F21, F23, F2);
    lwc1(F0, sp, 224);
    swc1(F0, sp, 256);
    swc1(F20, sp, 260);
    lwc1(F0, sp, 228);
    swc1(F0, sp, 264);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s0, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, kGpFrameWide);
    mul_s(F12, F0, F1);
    jal(0x2accbc, rg::fn_tanf_0052e930);
    div_s(F1, F21, F0);
    lif(v0, 0x43fa, F0);  // 500
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        mov_s(F1, F0);
    }
    charge(14);
    lwc1(F0, sp, 272);
    mul_s(F0, F0, F1);
    swc1(F0, sp, 272);
    lwc1(F0, sp, 276);
    mul_s(F0, F0, F1);
    swc1(F0, sp, 276);
    lwc1(F0, sp, 280);
    mul_s(F0, F0, F1);
    swc1(F0, sp, 280);
    mtc1(zero, F3);
    c_lt_s(F24, F3);
    // the sideways nudge by N's height along d's normal (sp+240 = d) when $f24 and $f25 have opposite signs:
    // +(d.z, -d.x) for $f24 >= 0 > $f25, -(...) for $f24 < 0 <= $f25
    if (!cc()) {
        charge(3);
        c_lt_s(F25, F3);
        if (cc()) {
            charge(15);
            lwc1(F1, s1, kUnitHeight);
            lwc1(F0, s1, kUnitScale);
            mul_s(F2, F1, F0);
            lwc1(F1, sp, 248);
            lwc1(F0, sp, 256);
            adda_s(F3, F0);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 256);
            lwc1(F1, sp, 240);
            lwc1(F0, sp, 264);
            adda_s(F3, F0);
            msub_s(F0, F1, F2);
            swc1(F0, sp, 264);
        }
    } else {
        charge(3);
        c_lt_s(F25, F3);
        if (!cc()) {
            charge(13);
            lwc1(F1, s1, kUnitHeight);
            lwc1(F0, s1, kUnitScale);
            mul_s(F2, F1, F0);
            lwc1(F1, sp, 248);
            lwc1(F0, sp, 256);
            adda_s(F3, F0);
            msub_s(F0, F1, F2);
            swc1(F0, sp, 256);
            lwc1(F1, sp, 240);
            lwc1(F0, sp, 264);
            adda_s(F3, F0);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 264);
        }
    }
    charge(31);
    lwc1(F1, s1, kUnitRadius);
    lwc1(F0, s1, kUnitScale);
    mul_s(F1, F1, F0);
    mtc1(zero, F0);
    adda_s(F0, F20);
    madd_s(F2, F22, F1);
    swc1(F2, sp, 260);
    // key B's eye sp+156 = sp+256 + the scaled direction
    lwc1(F1, sp, 256);
    lwc1(F0, sp, 272);
    add_s(F0, F1, F0);
    swc1(F0, sp, 156);
    lwc1(F0, sp, 276);
    add_s(F0, F2, F0);
    swc1(F0, sp, 160);
    lwc1(F1, sp, 264);
    lwc1(F0, sp, 280);
    add_s(F0, F1, F0);
    swc1(F0, sp, 164);
    a0_sp(128);
    a1 = addiu(s0, kCwEye);
    jal(0x2ace00, rg::fn_sub_2A4470_002a4470);
    a0_sp(140);
    a1 = addiu(sp, 168);
    jal(0x2ace10, rg::fn_sub_2D1F30_002d1f30);
    lwc1(F1, gp, -32460);
    c_le_s(F0, F1);
    if (!cc()) {
        charge(39);
        a0_sp(128);
        a1 = addiu(sp, 156);
        jal(0x2ace30, rg::fn_sub_2A44F0_002a44f0);
        a0_sp(272);
        la69(a1, 30880);
        a2 = li(1);
        a3 = addiu(sp, 140);
        jal(0x2ace4c, rg::fn_sub_4BE1E0_004be1e0);
        lif(v0, 0x4316, F1);  // 150
        lwc1(F0, sp, 272);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 272);
        lwc1(F0, sp, 276);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 276);
        lwc1(F0, sp, 280);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 280);
        lwc1(F0, sp, 156);
        add_s(F0, F0, F3);
        swc1(F0, sp, 156);
        lwc1(F0, sp, 160);
        add_s(F0, F0, F2);
        swc1(F0, sp, 160);
        lwc1(F0, sp, 164);
        add_s(F0, F0, F1);
        swc1(F0, sp, 164);
        s1 = dli(3);
        a0 = li(12);
        jal(0x2aceac, rg::fn_sub_351BB0_00351bb0);
        lif(v0, 0x3fc0, F20);
    } else {
        charge(2);
        s1 = dli(51);
        lwc1(F20, gp, -32600);
    }
    charge(7);
    lwc1(F1, sp, 132);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 132);
    }
    charge(7);
    lwc1(F1, sp, 160);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 160);
    }
    charge(33);
    lif(v0, 0x4248, F12);  // 50
    lw(a0, s0, kCwSubject);
    a1 = addiu(s2, 4);
    a2 = addiu(sp, 156);
    a3 = s1;
    jal(0x2acf24, rg::fn_sub_2A3E80_002a3e80);
    a0 = s0;
    a1 = addiu(sp, 128);
    a2 = addiu(sp, 156);
    a3 = li(1);
    jal(0x2acf3c, rg::fn_sub_2A2290_002a2290);
    a0 = s0;
    mov_s(F12, F20);
    jal(0x2acf4c, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 352);
}

// 0x2ACF90 sub_2ACF90(cw): the whole-side target shot. s0 = sub_2A3820(cw) (a fixed-height variant when non-zero);
// key A starts as cw+156. The side of the targets (btlTargetGetSideMask(action+56) for two or more targets, else 3) gives the
// side centre c (sub_280870(side, 1, &c, &spread, 0, 0); c.y = 0.75 * spread) and the distance D = spread /
// tan(1.2 fov/2), at least 1000; the target centre c2 (sub_280870(side, 1, &c2, 0, 0, 1)). The farthest living target
// from c2 (|c2 - position| by sub_280050 / sub_4C6AC0) or, with none, the current actor's unit gives the point q;
// the look-at point t = c + normalise(q - c, y = 0) * gp-32620 (y = c.y), the eye height H = max(1.5 * spread, 250);
// the direction from t to (c + normalise(q - c) * spread, H) is turned by +/-7.5 degrees (sub_357FD0(0) bit 0 picks
// the sign) about the up axis and scaled by D: key B's eye (sp+108) and rotation at t. Without s0 key A is the same
// turned the other way, with sub_351BB0(12) and field of view 8; with s0 key A keeps key B's eye with a fixed height
// and target y by the action's skill (+110: 56 -> 1000 / 750, fov 2.5; 44 -> 800 / 700, fov 3.75; 39 -> 600 / 550, fov
// 3; 38 and others -> 500 / 450, fov 2.75) and sub_351BB0(12). Both keys go through sub_2A3590, then
// sub_2A2290(cw, A, B, 1) and the field of view sub_2A3110.
void Cpu2::sub_2ACF90() {
    enter(22);
    sp = addiu(sp, -336);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s2 = a0;
    jal(0x2acfb8, rg::fn_sub_2A3820_002a3820);
    s0 = v0;
    a0_sp(80);
    a1 = addiu(s2, kCwEye);
    jal(0x2acfcc, rg::fn_sub_2A4470_002a4470);
    lw(v1, s2, kCwSubject);
    lhu(v0, v1, kActTargetCount);
    at = slti(v0, 2);
    if (at == 0) {
        charge(5);
        a0 = addiu(v1, kActTargets);
        jal(0x2acfec, rg::fn_btlTargetGetSideMask_002d1600);
    } else {
        charge(1);
        v0 = li(3);
    }
    charge(32);
    s1 = v0 & 0xffff;
    a0 = s1;
    a1 = li(1);
    a2 = addiu(sp, 320);
    a3 = addiu(sp, 332);
    t0 = 0;
    t1 = 0;
    jal(0x2ad01c, rg::fn_sub_280870_00280870);
    mov_s(F21, F0);
    lif(v0, 0x3f40, F1);  // 0.75
    lwc1(F0, sp, 332);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 324);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s2, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, kGpFrameWide);
    mul_s(F12, F0, F1);
    jal(0x2ad054, rg::fn_tanf_0052e930);
    div_s(F23, F21, F0);
    lif(v0, 0x447a, F0);  // 1000
    c_lt_s(F23, F0);
    if (cc()) {
        charge(1);
        mov_s(F23, F0);
    }
    charge(12);
    a0 = s1;
    a1 = li(1);
    a2 = addiu(sp, 304);
    a3 = 0;
    t0 = 0;
    t1 = a1;
    jal(0x2ad09c, rg::fn_sub_280870_00280870);
    mtc1(zero, F20);
    s1 = 0;
    // the farthest living target from c2 -> sp+224 (distance $f20)
    for (;;) {
        charge(6);
        lw(a0, s2, kCwSubject);
        v1 = s1 & 0xffff;
        lhu(v0, a0, kActTargetCount);
        v0 = slt(v1, v0);
        if (v0 == 0) break;
        backedge();
        charge(8);
        v0 = s1 & 0xffff;
        v0 = sll(v0, 2);
        v0 = addu(a0, v0);
        lw(v1, v0, kActTargets);
        lhu(v0, v1, 26);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            charge(22);
            lw(a0, v1, 48);
            a1 = addiu(sp, 240);
            jal(0x2ad0dc, rg::fn_sub_280050_00280050);
            lwc1(F1, sp, 304);
            lwc1(F0, sp, 240);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 288);
            lwc1(F1, sp, 308);
            lwc1(F0, sp, 244);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 292);
            lwc1(F1, sp, 312);
            lwc1(F0, sp, 248);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 296);
            a0_sp(288);
            jal(0x2ad118, rg::fn_sub_4C6AC0_004c6ac0);
            c_le_s(F0, F20);
            if (!cc()) {
                charge(5);
                ld(v0, sp, 240);
                lwc1(F1, sp, 248);
                sd(v0, sp, 224);
                swc1(F1, sp, 232);
                mov_s(F20, F0);
            }
        }
        charge(2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xffff;
    }
    charge(5);
    mtc1(zero, F0);
    c_eq_s(F0, F20);
    if (cc()) {
        charge(6);
        gbtl(v0);
        lw(v0, v0, btl_task::kCurrentAction);
        lw(a0, v0, 48);
        a1 = addiu(sp, 224);
        jal(0x2ad184, rg::fn_sub_280050_00280050);
    }
    charge(69);
    lwc1(F2, sp, 324);
    swc1(F2, sp, 228);
    lwc1(F1, sp, 224);
    lwc1(F0, sp, 320);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 288);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 292);
    lwc1(F1, sp, 232);
    lwc1(F0, sp, 328);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 296);
    a0_sp(288);
    a1 = a0;
    jal(0x2ad1c4, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F0, sp, 288);
    mul_s(F1, F0, F21);
    swc1(F1, sp, 288);
    lwc1(F0, sp, 292);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 292);
    lwc1(F0, sp, 296);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 296);
    lwc1(F3, sp, 320);
    add_s(F22, F3, F1);
    lwc1(F2, sp, 328);
    add_s(F20, F2, F0);
    lif(v0, 0x3fc0, F1);
    lwc1(F0, sp, 332);
    mul_s(F21, F1, F0);
    sub_s(F0, F22, F3);
    swc1(F0, sp, 272);
    sub_s(F0, F20, F2);
    swc1(F0, sp, 280);
    sw(zero, sp, 276);
    a0_sp(272);
    a1 = a0;
    jal(0x2ad22c, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F1, gp, -32620);
    mul_s(F2, F1, F0);
    lwc1(F0, sp, 272);
    mul_s(F1, F0, F2);
    swc1(F1, sp, 272);
    lwc1(F0, sp, 276);
    mul_s(F3, F0, F2);
    swc1(F3, sp, 276);
    lwc1(F0, sp, 280);
    mul_s(F2, F0, F2);
    swc1(F2, sp, 280);
    lwc1(F0, sp, 320);
    add_s(F0, F0, F1);
    swc1(F0, sp, 256);
    lwc1(F1, sp, 324);
    add_s(F0, F1, F3);
    swc1(F0, sp, 260);
    lwc1(F0, sp, 328);
    add_s(F0, F0, F2);
    swc1(F0, sp, 264);
    swc1(F1, sp, 260);
    lif(v0, 0x437a, F0);  // 250
    c_lt_s(F21, F0);
    if (cc()) {
        charge(1);
        mov_s(F21, F0);
    }
    charge(52);
    lwc1(F0, sp, 256);
    sub_s(F0, F22, F0);
    swc1(F0, sp, 288);
    lwc1(F0, sp, 260);
    sub_s(F0, F21, F0);
    swc1(F0, sp, 292);
    lwc1(F0, sp, 264);
    sub_s(F0, F20, F0);
    swc1(F0, sp, 296);
    a0_sp(288);
    a1 = a0;
    jal(0x2ad2d0, rg::fn_sub_4C69F0_004c69f0);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s2, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, kGpFrameWide);
    mul_s(F12, F0, F1);
    jal(0x2ad2f0, rg::fn_tanf_0052e930);
    mul_s(F1, F23, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 288);
    swc1(F0, sp, 216);
    lwc1(F0, sp, 296);
    swc1(F0, sp, 220);
    a0_sp(216);
    a1 = a0;
    jal(0x2ad324, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 220);
    lwc1(F0, sp, 256);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F0, F1, F20);
    swc1(F0, sp, 256);
    lwc1(F1, sp, 216);
    lwc1(F0, sp, 264);
    adda_s(F2, F0);
    msub_s(F0, F1, F20);
    swc1(F0, sp, 264);
    a0 = 0;
    jal(0x2ad360, rg::fn_sub_357FD0_00357fd0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        charge(4);
        lif(v0, 0x40f0, F20);  // 7.5
    } else {
        charge(2);
        lif(v0, 0xc0f0, F20);  // -7.5
    }
    charge(39);
    a0_sp(144);
    la69(a1, 30848);
    mov_s(F12, F20);
    a2 = 0;
    jal(0x2ad3a0, rg::fn_sub_4C31B0_004c31b0);
    a0_sp(272);
    a1 = addiu(sp, 288);
    a2 = addiu(sp, 144);
    jal(0x2ad3b4, rg::fn_sub_4C6C60_004c6c60);
    scaled_eye(108, F23);
    a0_sp(120);
    a1 = addiu(sp, 108);
    a2 = addiu(sp, 256);
    la69(a3, 30848);
    jal(0x2ad418, rg::fn_sub_2A4690_002a4690);
    if (s0 == 0) {
        charge(44);
        neg_s(F12, F20);
        a0_sp(144);
        la69(a1, 30848);
        a2 = 0;
        jal(0x2ad43c, rg::fn_sub_4C31B0_004c31b0);
        a0_sp(272);
        a1 = addiu(sp, 288);
        a2 = addiu(sp, 144);
        jal(0x2ad450, rg::fn_sub_4C6C60_004c6c60);
        scaled_eye(80, F23);
        a0_sp(92);
        a1 = addiu(sp, 80);
        a2 = addiu(sp, 256);
        la69(a3, 30848);
        jal(0x2ad4b4, rg::fn_sub_2A4690_002a4690);
        a0 = li(12);
        jal(0x2ad4c0, rg::fn_sub_351BB0_00351bb0);
        lif(v0, 0x4100, F20);  // 8
    } else {
        charge(11);
        copy_vec3(sp, 108, sp, 80);
        lw(v0, s2, kCwSubject);
        lhu(v1, v0, 110);
        // (eye y, target y, field of view) by the skill
        u32 eye_y = 0x43fa, fov = 0x4030;
        s32 target_y = 0x43e1;  // lui of 450.0 (or a word converted for 550 / 750)
        bool converted = false;
        v0 = li(56);
        if (v1 == v0) {
            charge(11);
            eye_y = 0x447a, target_y = 750, fov = 0x4020, converted = true;
        } else {
            charge(3);
            v0 = li(44);
            if (v1 == v0) {
                charge(8);
                eye_y = 0x4448, target_y = 0x442f, fov = 0x4070;
            } else {
                charge(3);
                v0 = li(39);
                if (v1 == v0) {
                    charge(11);
                    eye_y = 0x4416, target_y = 550, fov = 0x4040, converted = true;
                } else {
                    charge(3);
                    v0 = li(38);
                    if (v1 == v0) {
                        charge(8);
                    } else {
                        charge(2);
                        charge(6);
                    }
                }
            }
        }
        v0 = lui(eye_y);
        sw(v0, sp, 84);
        if (converted) {
            v0 = li(target_y);
            mtc1(v0, F0);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 260);
        } else {
            v0 = lui(static_cast<u32>(target_y));
            sw(v0, sp, 260);
        }
        lif(v0, fov, F20);
        charge(10);
        a0_sp(92);
        a1 = addiu(sp, 80);
        a2 = addiu(sp, 256);
        la69(a3, 30848);
        jal(0x2ad5f4, rg::fn_sub_2A4690_002a4690);
        a0 = li(12);
        jal(0x2ad600, rg::fn_sub_351BB0_00351bb0);
    }
    charge(29);
    a0_sp(80);
    a1 = a0;
    jal(0x2ad610, rg::fn_sub_2A3590_002a3590);
    a0_sp(108);
    a1 = a0;
    jal(0x2ad620, rg::fn_sub_2A3590_002a3590);
    a0 = s2;
    a1 = addiu(sp, 80);
    a2 = addiu(sp, 108);
    a3 = li(1);
    jal(0x2ad638, rg::fn_sub_2A2290_002a2290);
    a0 = s2;
    mov_s(F12, F20);
    jal(0x2ad648, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 336);
}

// sub_2AE740's eye step (three times): the direction sp+304 *= $f20 (the distance); $f<fr> = $f20 * tan(1.2 fov/2) *
// 0.21875; the point sp+352 moves sideways along the normal of the direction's ground part (sub_4C6B20 of (x, z) at
// sp+368) by $f<fr>; the eye sp+dst = sp+352 + the direction.
void Cpu2::side_eye(u32 link_tan, u32 link_norm, unsigned fr, s32 dst) {
    scale3_sp(304, 304, F20);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s4, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, kGpFrameWide);
    mul_s(F12, F0, F1);
    jal(link_tan, rg::fn_tanf_0052e930);
    mul_s(F1, F20, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(fr, F1, F0);
    lwc1(F0, sp, 304);
    swc1(F0, sp, 368);
    lwc1(F0, sp, 312);
    swc1(F0, sp, 372);
    a0_sp(368);
    a1 = a0;
    jal(link_norm, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 372);
    lwc1(F0, sp, 352);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, fr);
    swc1(F3, sp, 352);
    lwc1(F1, sp, 368);
    lwc1(F0, sp, 360);
    adda_s(F2, F0);
    msub_s(F2, F1, fr);
    swc1(F2, sp, 360);
    lwc1(F0, sp, 304);
    add_s(F0, F3, F0);
    swc1(F0, sp, dst);
    lwc1(F1, sp, 356);
    lwc1(F0, sp, 308);
    add_s(F0, F1, F0);
    swc1(F0, sp, dst + 4);
    lwc1(F0, sp, 312);
    add_s(F0, F2, F0);
    swc1(F0, sp, dst + 8);
}

// 0x2AE740 sub_2AE740(cw, a1 = single key): the target-cursor camera's update. The cursor's current candidate
// (sub_2C0880(action+136)); key A starts as cw+156. The candidates' side (sub_2A3850(cw) == 0 -> side 1, else 0) gives
// the centre c, its spread ($f0) and height range lo..hi (sub_280870(3, side, &c, &hi, &lo, 1)); c.y = lo + (hi - lo) /
// 2; the distance d = spread * gp-32472 / tan(1.2 fov/2). From the subject's unit position u (sub_280050): the
// look-at point m = c + normalise(u - c, y = 0) * |u - c| / 2, the eye (u.x, 2 hi, u.z) -> rotation sp+172
// (sub_2A4690), direction by sub_4BE1E0; side_eye -> key 1 eye sp+160. When the candidate is the subject itself: with
// cw+262 == 0 the same from m' = c + normalise(u - c) * gp-32472 and eye height 1.5 hi into key B (sp+252); otherwise
// key B = key 1's rotation (sub_2A44F0). For another candidate: the look-at point is that candidate's unit position
// (sub_280050), its rotation sp+200 and eye (sp+188); with cw+262 == 0 key B blends the two rotations (sub_4BE310 ->
// the slerp terms at sp+112..sp+148, sin series with gp-32604 / gp-32620) and the eyes (key 1 * gp-32604 + eye 2 *
// gp-32620); otherwise key B = key 1's rotation. Key B goes through sub_2A3590; with a1 the single key sub_2A2170(cw,
// key B), else the pair sub_2A2290(cw, A, B, 1) and the field of view 0.75 (sub_2A3110).
void Cpu2::sub_2AE740() {
    enter(175);
    sp = addiu(sp, -384);
    sd(ra, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;
    s3 = a1;
    lw(s1, a0, kCwSubject);
    lw(s2, s1, 48);
    a0 = addiu(s1, 136);
    jal(0x2ae778, rg::fn_sub_2C0880_002c0880);
    s0 = v0;
    a0_sp(224);
    a1 = addiu(s4, kCwEye);
    jal(0x2ae78c, rg::fn_sub_2A4470_002a4470);
    a0 = s4;
    jal(0x2ae798, rg::fn_sub_2A3850_002a3850);
    v0 = sltu(zero, v0);
    a1 = v0 ^ 0x1;
    a0 = li(3);
    a2 = addiu(sp, 336);
    a3 = addiu(sp, 380);
    t0 = addiu(sp, 376);
    t1 = li(1);
    jal(0x2ae7bc, rg::fn_sub_280870_00280870);
    mov_s(F20, F0);
    lwc1(F3, sp, 376);
    lwc1(F0, sp, 380);
    sub_s(F2, F0, F3);
    lif(v0, 0x3f00, F1);
    mtc1(zero, F0);
    adda_s(F0, F3);
    madd_s(F0, F1, F2);
    swc1(F0, sp, 340);
    lwc1(F0, s4, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, kGpFrameWide);
    mul_s(F12, F0, F1);
    jal(0x2ae800, rg::fn_tanf_0052e930);
    lwc1(F1, gp, -32472);
    mul_s(F1, F1, F20);
    div_s(F20, F1, F0);
    a0 = s2;
    a1 = addiu(sp, 288);
    jal(0x2ae820, rg::fn_sub_280050_00280050);
    // sp+320 = (u.x, c.y, u.z); sp+304 = it - c, normalised (length -> $f0)
    lwc1(F3, sp, 288);
    swc1(F3, sp, 320);
    lwc1(F2, sp, 340);
    swc1(F2, sp, 324);
    lwc1(F1, sp, 296);
    swc1(F1, sp, 328);
    lwc1(F0, sp, 336);
    sub_s(F0, F3, F0);
    swc1(F0, sp, 304);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 308);
    lwc1(F0, sp, 344);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 312);
    a0_sp(304);
    a1 = a0;
    jal(0x2ae868, rg::fn_sub_4C69F0_004c69f0);
    lif(v0, 0x3f00, F1);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 304);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 304);
    lwc1(F0, sp, 308);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 308);
    lwc1(F0, sp, 312);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 312);
    lwc1(F0, sp, 336);
    add_s(F0, F0, F3);
    swc1(F0, sp, 352);
    lwc1(F0, sp, 340);
    add_s(F0, F0, F2);
    swc1(F0, sp, 356);
    lwc1(F0, sp, 344);
    add_s(F0, F0, F1);
    swc1(F0, sp, 360);
    lwc1(F0, sp, 288);
    swc1(F0, sp, 320);
    lif(v0, 0x4000, F1);  // 2
    lwc1(F0, sp, 380);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 324);
    lwc1(F0, sp, 296);
    swc1(F0, sp, 328);
    a0_sp(172);
    a1 = addiu(sp, 320);
    a2 = addiu(sp, 352);
    la69(a3, 30848);
    jal(0x2ae900, rg::fn_sub_2A4690_002a4690);
    a0_sp(304);
    la69(a1, 30880);
    a2 = li(1);
    a3 = addiu(sp, 172);
    jal(0x2ae91c, rg::fn_sub_4BE1E0_004be1e0);
    side_eye(0x2ae960, 0x2ae994, F21, 160);
    if (s1 == s0) {
        charge(3);
        lhu(v0, s4, 262);
        if (v0 == 0) {
            charge(127);
            lwc1(F3, sp, 288);
            swc1(F3, sp, 320);
            lwc1(F2, sp, 340);
            swc1(F2, sp, 324);
            lwc1(F1, sp, 296);
            swc1(F1, sp, 328);
            lwc1(F0, sp, 336);
            sub_s(F0, F3, F0);
            swc1(F0, sp, 304);
            sub_s(F0, F2, F2);
            swc1(F0, sp, 308);
            lwc1(F0, sp, 344);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 312);
            a0_sp(304);
            a1 = a0;
            jal(0x2aea48, rg::fn_sub_4C69F0_004c69f0);
            // m' = sp+352 = c + n * |u - c| * gp-32472; the eye sp+320 = u + n * |u - c| / 2 with y = 1.5 hi
            lwc1(F1, gp, -32472);
            mul_s(F1, F1, F0);
            lwc1(F7, sp, 304);
            mul_s(F6, F7, F1);
            swc1(F6, sp, 320);
            lwc1(F5, sp, 308);
            mul_s(F4, F5, F1);
            swc1(F4, sp, 324);
            lwc1(F3, sp, 312);
            mul_s(F2, F3, F1);
            swc1(F2, sp, 328);
            lwc1(F1, sp, 336);
            add_s(F1, F1, F6);
            swc1(F1, sp, 352);
            lwc1(F1, sp, 340);
            add_s(F1, F1, F4);
            swc1(F1, sp, 356);
            lwc1(F1, sp, 344);
            add_s(F1, F1, F2);
            swc1(F1, sp, 360);
            lif(v0, 0x3f00, F1);
            mul_s(F2, F1, F0);
            mul_s(F1, F7, F2);
            swc1(F1, sp, 320);
            mul_s(F0, F5, F2);
            swc1(F0, sp, 324);
            mul_s(F2, F3, F2);
            swc1(F2, sp, 328);
            lwc1(F0, sp, 288);
            add_s(F0, F1, F0);
            swc1(F0, sp, 320);
            lif(v0, 0x3fc0, F1);
            lwc1(F0, sp, 380);
            mul_s(F0, F1, F0);
            swc1(F0, sp, 324);
            lwc1(F0, sp, 296);
            add_s(F0, F2, F0);
            swc1(F0, sp, 328);
            a0_sp(264);
            a1 = addiu(sp, 320);
            a2 = addiu(sp, 352);
            la69(a3, 30848);
            jal(0x2aeb08, rg::fn_sub_2A4690_002a4690);
            a0_sp(304);
            la69(a1, 30880);
            a2 = li(1);
            a3 = addiu(sp, 264);
            jal(0x2aeb24, rg::fn_sub_4BE1E0_004be1e0);
            side_eye(0x2aeb68, 0x2aeb9c, F20, 252);
        } else {
            charge(6);
            a0_sp(252);
            a1 = addiu(sp, 160);
            jal(0x2aec0c, rg::fn_sub_2A44F0_002a44f0);
        }
    } else {
        charge(73);
        lw(a0, s0, 48);
        a1 = addiu(sp, 352);
        jal(0x2aec24, rg::fn_sub_280050_00280050);
        a0_sp(200);
        a1 = addiu(sp, 320);
        a2 = addiu(sp, 352);
        la69(a3, 30848);
        jal(0x2aec40, rg::fn_sub_2A4690_002a4690);
        a0_sp(304);
        la69(a1, 30880);
        a2 = li(1);
        a3 = addiu(sp, 200);
        jal(0x2aec5c, rg::fn_sub_4BE1E0_004be1e0);
        side_eye(0x2aeca0, 0x2aecd4, F20, 188);
        lhu(v0, s4, 262);
        if (v0 == 0) {
            charge(10);
            a0_sp(172);
            a1 = addiu(sp, 200);
            a2 = addiu(sp, 112);
            jal(0x2aed4c, rg::fn_sub_4BE310_004be310);
            lwc1(F1, gp, -32604);
            lwc1(F0, gp, -32620);
            lw(v0, sp, 148);
            if (v0 == 0) {
                // the slerp weights: sin(w * angle) by the series (gp-32492, -32696, -32488, -32688, -32684, -32680)
                charge(39);
                lwc1(F12, sp, 144);
                mul_s(F4, F1, F12);
                mul_s(F3, F4, F4);
                lwc1(F11, gp, -32492);
                lwc1(F10, gp, -32696);
                mtc1(zero, F9);
                adda_s(F9, F10);
                madd_s(F1, F11, F3);
                lwc1(F8, gp, -32488);
                adda_s(F9, F8);
                madd_s(F1, F3, F1);
                lwc1(F7, gp, -32688);
                adda_s(F9, F7);
                madd_s(F1, F3, F1);
                lwc1(F6, gp, -32684);
                adda_s(F9, F6);
                madd_s(F1, F3, F1);
                lwc1(F5, gp, -32680);
                adda_s(F9, F5);
                madd_s(F2, F3, F1);
                mul_s(F1, F3, F4);
                adda_s(F9, F4);
                madd_s(F1, F1, F2);
                mul_s(F4, F0, F12);
                mul_s(F3, F4, F4);
                adda_s(F9, F10);
                madd_s(F0, F11, F3);
                adda_s(F9, F8);
                madd_s(F0, F3, F0);
                adda_s(F9, F7);
                madd_s(F0, F3, F0);
                adda_s(F9, F6);
                madd_s(F0, F3, F0);
                adda_s(F9, F5);
                madd_s(F2, F3, F0);
                mul_s(F0, F3, F4);
                adda_s(F9, F4);
                madd_s(F0, F0, F2);
            }
            charge(56);
            // key B's rotation sp+264 = sp+112 * $f1 + sp+128 * $f0 (four components); its eye = key 1's eye *
            // gp-32604 + eye 2 * gp-32620
            lwc1(F2, sp, 112);
            mul_s(F6, F2, F1);
            swc1(F6, sp, 264);
            lwc1(F2, sp, 116);
            mul_s(F5, F2, F1);
            swc1(F5, sp, 268);
            lwc1(F2, sp, 120);
            mul_s(F4, F2, F1);
            swc1(F4, sp, 272);
            lwc1(F2, sp, 128);
            mtc1(zero, F3);
            adda_s(F3, F6);
            madd_s(F2, F2, F0);
            swc1(F2, sp, 264);
            lwc1(F2, sp, 132);
            adda_s(F3, F5);
            madd_s(F2, F2, F0);
            swc1(F2, sp, 268);
            lwc1(F2, sp, 136);
            adda_s(F3, F4);
            madd_s(F2, F2, F0);
            swc1(F2, sp, 272);
            lwc1(F3, sp, 124);
            lwc1(F2, sp, 140);
            mula_s(F2, F0);
            madd_s(F0, F3, F1);
            swc1(F0, sp, 276);
            lwc1(F0, sp, 160);
            lwc1(F1, gp, -32604);
            mul_s(F6, F0, F1);
            swc1(F6, sp, 160);
            lwc1(F0, sp, 164);
            mul_s(F5, F0, F1);
            swc1(F5, sp, 164);
            lwc1(F0, sp, 168);
            mul_s(F4, F0, F1);
            swc1(F4, sp, 168);
            lwc1(F0, sp, 188);
            lwc1(F1, gp, -32620);
            mul_s(F3, F0, F1);
            swc1(F3, sp, 188);
            lwc1(F0, sp, 192);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 192);
            lwc1(F0, sp, 196);
            mul_s(F1, F0, F1);
            swc1(F1, sp, 196);
            add_s(F0, F6, F3);
            swc1(F0, sp, 252);
            add_s(F0, F5, F2);
            swc1(F0, sp, 256);
            add_s(F0, F4, F1);
            swc1(F0, sp, 260);
        } else {
            charge(4);
            a0_sp(252);
            a1 = addiu(sp, 160);
            jal(0x2aeeec, rg::fn_sub_2A44F0_002a44f0);
        }
    }
    charge(6);
    a0_sp(252);
    a1 = a0;
    jal(0x2aeefc, rg::fn_sub_2A3590_002a3590);
    if (s3 != 0) {
        charge(6);
        a0 = s4;
        a1 = addiu(sp, 252);
        jal(0x2aef14, rg::fn_sub_2A2170_002a2170);
    } else {
        charge(11);
        a0 = s4;
        a1 = addiu(sp, 224);
        a2 = addiu(sp, 252);
        a3 = li(1);
        jal(0x2aef34, rg::fn_sub_2A2290_002a2290);
        lif(v0, 0x3f40, F12);  // 0.75
        a0 = s4;
        jal(0x2aef48, rg::fn_sub_2A3110_002a3110);
    }
    charge(11);
    ld(ra, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 384);
}

// sub_2AA2B0's fixed shot by the subject's skill (+110): the eye height sp+388, the eye-key height sp+276, the field of
// view $f20, s1 (1 = sub_2A3160 instead of sub_2A3110), s3 = 0 and cw+220 (the frames the units stay shown):
// 56 -> 1000 / 500 / 1.5 / 0 / 4; 44 -> 800 / 500 / 2 / 1 / 12; 39 -> 600 / 200 / gp-32596 / 0 / 8;
// 38 -> 500 / 200 / 1.25 / 1 / 12; others 500 / 200 / gp-32612 / 1 / 0.
void Cpu2::skill_heights_2AA2B0() {
    charge(5);
    lw(v0, s4, kCwSubject);
    lhu(v1, v0, 110);
    struct Row {
        u32 eye, key, fov_hi;  // fov_hi 0: the $gp float `fov_gp`
        s32 fov_gp;
        s32 s1v, frames;       // frames < 0: `sw zero`
        u64 cyc;
    };
    Row r{0x43fa, 0x4348, 0, -32612, 1, -1, 2 + 8};
    v0 = li(56);
    if (v1 == v0) {
        r = {0x447a, 0x43fa, 0x3fc0, 0, 0, 4, 12};
    } else {
        charge(3);
        v0 = li(44);
        if (v1 == v0) {
            r = {0x4448, 0x43fa, 0x4000, 0, 1, 12, 12};
        } else {
            charge(3);
            v0 = li(39);
            if (v1 == v0) {
                r = {0x4416, 0x4348, 0, -32596, 0, 8, 11};
            } else {
                charge(3);
                v0 = li(38);
                if (v1 == v0) r = {0x43fa, 0x4348, 0x3fa0, 0, 1, 12, 12};
            }
        }
    }
    charge(r.cyc);
    v0 = lui(r.eye);
    sw(v0, sp, 388);
    v0 = lui(r.key);
    sw(v0, sp, 276);
    if (r.fov_hi != 0) lif(v0, r.fov_hi, F20);
    else lwc1(F20, gp, r.fov_gp);
    s1 = li(r.s1v);
    s3 = 0;
    if (r.frames >= 0) {
        v0 = li(r.frames);
        sw(v0, s4, 220);
    } else {
        sw(zero, s4, 220);
    }
}

// 0x2AA2B0 sub_2AA2B0(cw, a1 = sound flag, a2 = keep-eye flag): the subject-and-enemies shot. The subject's unit S
// (subject+48) and its partner unit P (S+2560); s5 = sub_2A3520(cw) || sub_2A3550(cw). Their positions; S's height y
// raised by half its radius, P's likewise (S takes P's when P's is higher, unless s5, with the mean / 4 written back);
// the framing height h = max(1.25 * S's height, P's height unless s5); a y below 275 becomes 275 with gp-32608. The
// enemies' centre c (sub_280870(2, 0, &c, &spread, 0, 1), c.y = spread / 2), S's facing f (sub_4BE1E0 axis 0x697870),
// the look-at point m = c + normalise(S - c) * |S - c| * gp-32616; the side of cw+156 against the S-c normal = $f22.
// s8 = sub_2A3420(cw), s6 = sub_2A3820(cw); the roll (sub_357FD0(0) bit 0, skipped for a P whose ENEMY record
// (gp-18628, 88-byte rows by P+164) has flag 0x20 unless s5 == 1).
// A close shot (s8, or the roll with sub_2A3380(cw) and no s6): P plays motion 1 (sub_2880E0; cw+288 = P, +292 = 0),
// the eye beside S along f (+/- by $f22) * h, y = gp-32604 * height, the eye distance from the look-at point by the
// fov, the side shift, key B {eye, look-at rotation}; key A from S's facing scaled by +/- 2.5 * S's height and turned
// to m, pushed back by 4 * S's height / tan; field of view gp-32652.
// Otherwise: P plays motion 0 (cw+288 = P, +292 = 1), the eye over c (y = spread * gp-32600, shifted by the single
// target's height along f when there is one target), at least 125 high, its distance (spread at least 300), key B; then
// without s6 a +/-27.5 degree turn (sub_4C31B0 / sub_4C6C60), key A from it (fov 3.75); with s6 the fixed shot of
// skill_heights_2AA2B0.
// Without a2 and s6, key A becomes key B's rotation turned 100 along (0, 0, 1). cw+220 > 0 shows the units
// (sub_2A3E80(subject, 0, 0, 1)); both keys through sub_2A3590, sub_2A2290(cw, A, B, 1), the field of view
// (sub_2A3160 with s1, else sub_2A3110) and sub_351BB0(12) when s3.
void Cpu2::sub_2AA2B0() {
    enter(27);
    sp = addiu(sp, -480);
    sd(ra, sp, 176);
    sq(s8, sp, 160);
    sq(s7, sp, 144);
    sq(s6, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;
    s3 = a1;
    s7 = a2;
    lw(v0, a0, kCwSubject);
    lw(s0, v0, 48);
    lw(s2, s0, 2560);
    jal(0x2aa30c, rg::fn_sub_2A3520_002a3520);
    bool either = v0 != 0;
    if (!either) {
        charge(5);
        a0 = s4;
        jal(0x2aa320, rg::fn_sub_2A3550_002a3550);
        either = v0 != 0;
    }
    if (either) {
        charge(3);
        s5 = li(1);
    } else {
        charge(1);
        s5 = 0;
    }
    charge(28);
    s1 = 0;
    a0 = s0;
    a1 = addiu(sp, 432);
    jal(0x2aa34c, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s2;
    a1 = addiu(sp, 400);
    jal(0x2aa35c, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s0, kUnitRadius);
    lwc1(F0, s0, kUnitScale);
    mul_s(F1, F1, F0);
    lif(v0, 0x3f00, F3);
    lwc1(F0, sp, 436);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F20, F3, F1);
    lwc1(F1, s2, kUnitRadius);
    lwc1(F0, s2, kUnitScale);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 404);
    adda_s(F2, F0);
    madd_s(F2, F3, F1);
    c_lt_s(F20, F2);
    if (cc()) {
        charge(2);
        if (s5 == 0) {
            charge(7);
            add_s(F1, F20, F2);
            lif(v0, 0x3e80, F0);
            mul_s(F0, F0, F1);
            swc1(F0, sp, 436);
            mov_s(F20, F2);
        }
    }
    charge(13);
    lwc1(F1, s2, kUnitHeight);
    lwc1(F0, s2, kUnitScale);
    mul_s(F2, F1, F0);
    lwc1(F1, s0, kUnitHeight);
    lwc1(F0, s0, kUnitScale);
    mul_s(F1, F1, F0);
    lif(v0, 0x3fa0, F0);
    mul_s(F24, F0, F1);
    c_lt_s(F24, F2);
    if (cc()) {
        charge(2);
        if (s5 == 0) {
            charge(1);
            mov_s(F24, F2);
        }
    }
    charge(7);
    v0 = li(275);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    c_lt_s(F20, F0);
    if (cc()) {
        charge(3);
        mov_s(F20, F0);
        lwc1(F0, gp, -32608);
        swc1(F0, sp, 436);
    }
    charge(90);
    a0 = li(2);
    a1 = 0;
    a2 = addiu(sp, 416);
    a3 = addiu(sp, 476);
    t0 = 0;
    t1 = li(1);
    jal(0x2aa454, rg::fn_sub_280870_00280870);
    mov_s(F25, F0);
    a0_sp(464);
    la69(a1, 30832);
    a2 = li(1);
    a3 = addiu(s0, kUnitRotation);
    jal(0x2aa474, rg::fn_sub_4BE1E0_004be1e0);
    lif(v0, 0x3f00, F1);
    lwc1(F0, sp, 476);
    mul_s(F2, F1, F0);
    swc1(F2, sp, 420);
    // sp+448 = S - c, normalised; m = sp+384 (and a copy at sp+368) = c + it * |S - c| * gp-32616
    lwc1(F1, sp, 432);
    lwc1(F0, sp, 416);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 448);
    lwc1(F0, sp, 436);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 452);
    lwc1(F1, sp, 440);
    lwc1(F0, sp, 424);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 456);
    a0_sp(448);
    a1 = a0;
    jal(0x2aa4c4, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F1, gp, -32616);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 448);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 384);
    lwc1(F0, sp, 452);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 388);
    lwc1(F0, sp, 456);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 392);
    lwc1(F0, sp, 416);
    add_s(F2, F2, F0);
    swc1(F2, sp, 384);
    lwc1(F0, sp, 420);
    add_s(F0, F3, F0);
    swc1(F0, sp, 388);
    lwc1(F0, sp, 424);
    add_s(F1, F1, F0);
    swc1(F1, sp, 392);
    ld(v0, sp, 384);
    lwc1(F0, sp, 392);
    sd(v0, sp, 368);
    swc1(F0, sp, 376);
    // $f22 = dot((n.z, -n.x), normalise2(cw+156 - m))
    lwc1(F0, s4, kCwEye);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 200);
    lwc1(F0, s4, kCwEye + 8);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 204);
    a0_sp(200);
    a1 = a0;
    jal(0x2aa54c, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F3, sp, 456);
    swc1(F3, sp, 192);
    lwc1(F0, sp, 448);
    neg_s(F2, F0);
    swc1(F2, sp, 196);
    lwc1(F1, sp, 200);
    lwc1(F0, sp, 204);
    mula_s(F2, F0);
    madd_s(F22, F3, F1);
    a0 = s4;
    jal(0x2aa57c, rg::fn_sub_2A3420_002a3420);
    s8 = v0;
    a0 = s4;
    jal(0x2aa58c, rg::fn_sub_2A3820_002a3820);
    s6 = v0;
    v0 = li(1);
    bool roll = s5 == v0;
    if (!roll) {
        charge(12);
        lhu(v1, s2, 164);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, gp, -18628);
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
        v0 = v0 & 0x20;
        roll = v0 == 0;
    }
    if (roll) {
        charge(7);
        a0 = 0;
        jal(0x2aa5d8, rg::fn_sub_357FD0_00357fd0);
        v0 = v0 & 0x1;
        v1 = sltu(zero, v0);
    } else {
        charge(1);
        v1 = 0;
    }
    charge(2);
    bool close = s8 != 0;
    if (!close) {
        charge(3);
        v0 = li(1);
        if (v1 == v0) {
            charge(5);
            a0 = s4;
            jal(0x2aa60c, rg::fn_sub_2A3380_002a3380);
            if (v0 != 0) {
                charge(2);
                close = s6 == 0;
            }
        }
    }
    if (close) {
        charge(11);
        a0 = s2;
        a1 = li(1);
        jal(0x2aa62c, rg::fn_sub_2880E0_002880e0);
        sw(s2, s4, kCwMotionUnit);
        sh(zero, s4, kCwMotion);
        mtc1(zero, F0);
        c_lt_s(F22, F0);
        if (!cc()) {
            charge(11);
            scale3_in(464, F24);
        } else {
            charge(10);
            neg_s(F1, F24);
            scale3_in(464, F1);
        }
        charge(54);
        // the eye sp+352 = S + f * h, y = gp-32604 * S.y; sp+464 = it - m, normalised (length $f21)
        lwc1(F1, sp, 432);
        lwc1(F0, sp, 464);
        add_s(F2, F1, F0);
        swc1(F2, sp, 352);
        lwc1(F1, sp, 436);
        lwc1(F0, sp, 468);
        add_s(F0, F1, F0);
        swc1(F0, sp, 356);
        lwc1(F1, sp, 440);
        lwc1(F0, sp, 472);
        add_s(F1, F1, F0);
        swc1(F1, sp, 360);
        lwc1(F0, gp, -32604);
        mul_s(F20, F0, F20);
        swc1(F20, sp, 356);
        lwc1(F0, sp, 384);
        sub_s(F0, F2, F0);
        swc1(F0, sp, 464);
        lwc1(F0, sp, 388);
        sub_s(F0, F20, F0);
        swc1(F0, sp, 468);
        lwc1(F0, sp, 392);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 472);
        a0_sp(464);
        a1 = a0;
        jal(0x2aa70c, rg::fn_sub_4C69F0_004c69f0);
        mov_s(F21, F0);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s4, kCwFov);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, kGpFrameWide);
        mul_s(F23, F0, F1);  // the wide half angle
        mov_s(F12, F23);
        jal(0x2aa734, rg::fn_tanf_0052e930);
        div_s(F24, F24, F0);
        mov_s(F12, F23);
        jal(0x2aa754, rg::fn_tanf_0052e930);
        div_s(F0, F20, F0);
        c_le_s(F24, F0);
        if (cc()) {
            charge(1);
            mov_s(F24, F0);
        } else {
            charge(2);
        }
        charge(12);
        add_s(F21, F21, F24);
        mov_s(F12, F23);
        jal(0x2aa790, rg::fn_tanf_0052e930);
        div_s(F0, F25, F0);
        c_le_s(F21, F0);
        if (cc()) {
            charge(1);
            mov_s(F21, F0);
        } else {
            charge(2);
        }
        charge(85);
        tan_fov_wide(s4, 0x2aa7dc);
        mul_s(F1, F21, F0);
        lif(v0, 0x3e60, F0);
        mul_s(F20, F1, F0);
        side_shift(464, 384, F20, 0x2aa810);
        // key B (sp+300): the eye m + dir * distance, its rotation (sp+312) towards m
        lwc1(F0, sp, 464);
        mul_s(F3, F0, F21);
        lwc1(F0, sp, 468);
        mul_s(F2, F0, F21);
        lwc1(F0, sp, 472);
        mul_s(F1, F0, F21);
        add_s(F0, F5, F3);
        swc1(F0, sp, 300);
        lwc1(F0, sp, 388);
        add_s(F0, F0, F2);
        swc1(F0, sp, 304);
        add_s(F0, F4, F1);
        swc1(F0, sp, 308);
        a0_sp(312);
        a1 = addiu(sp, 300);
        a2 = addiu(sp, 384);
        la69(a3, 30848);
        jal(0x2aa890, rg::fn_sub_2A4690_002a4690);
        a0 = s0;
        a1 = addiu(sp, 432);
        jal(0x2aa8a0, rg::fn_sub_27FFB0_0027ffb0);
        lwc1(F0, s0, kUnitRadius);
        lwc1(F4, s0, kUnitScale);
        mul_s(F3, F0, F4);
        lwc1(F2, gp, -32620);
        lwc1(F1, sp, 436);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F0, F2, F3);
        swc1(F0, sp, 436);
        lwc1(F0, s0, kUnitHeight);
        mul_s(F1, F0, F4);
        lif(v0, 0x4020, F0);
        mul_s(F20, F0, F1);  // 2.5 * S's height
        a0_sp(464);
        la69(a1, 30832);
        a2 = li(1);
        a3 = addiu(s0, kUnitRotation);
        jal(0x2aa8fc, rg::fn_sub_4BE1E0_004be1e0);
        mtc1(zero, F0);
        c_lt_s(F22, F0);
        if (!cc()) {
            charge(12);
            neg_s(F1, F20);
            scale3_in(464, F1);
        } else {
            charge(9);
            scale3_in(464, F20);
        }
        charge(109);
        // key A (sp+272): the eye S + f, rotation sp+284 towards the m copy (sp+368), pushed back along it
        add3_sp(336, 432, 464);
        a0_sp(284);
        a1 = addiu(sp, 336);
        a2 = addiu(sp, 368);
        la69(a3, 30848);
        jal(0x2aa9b0, rg::fn_sub_2A4690_002a4690);
        lwc1(F1, s0, kUnitHeight);
        lwc1(F0, s0, kUnitScale);
        mul_s(F1, F1, F0);
        lif(v0, 0x4080, F0);
        mul_s(F21, F0, F1);
        lwc1(F1, sp, 336);
        lwc1(F0, sp, 368);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 464);
        lwc1(F1, sp, 340);
        lwc1(F0, sp, 372);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 468);
        lwc1(F1, sp, 344);
        lwc1(F0, sp, 376);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 472);
        a0_sp(464);
        a1 = a0;
        jal(0x2aaa0c, rg::fn_sub_4C69F0_004c69f0);
        mov_s(F20, F0);
        mov_s(F12, F23);
        jal(0x2aaa1c, rg::fn_tanf_0052e930);
        div_s(F0, F21, F0);
        add_s(F20, F20, F0);
        a0_sp(464);
        la69(a1, 30880);
        a2 = li(1);
        a3 = addiu(sp, 284);
        jal(0x2aaa48, rg::fn_sub_4BE1E0_004be1e0);
        tan_fov_wide(s4, 0x2aaa68);
        mul_s(F1, F20, F0);
        lif(v0, 0x3e60, F0);
        mul_s(F21, F1, F0);
        side_shift(464, 368, F21, 0x2aaa9c);
        lwc1(F0, sp, 464);
        mul_s(F3, F0, F20);
        swc1(F3, sp, 464);
        lwc1(F0, sp, 468);
        mul_s(F2, F0, F20);
        swc1(F2, sp, 468);
        lwc1(F0, sp, 472);
        mul_s(F1, F0, F20);
        swc1(F1, sp, 472);
        add_s(F0, F5, F3);
        swc1(F0, sp, 272);
        lwc1(F0, sp, 372);
        add_s(F0, F0, F2);
        swc1(F0, sp, 276);
        add_s(F0, F4, F1);
        swc1(F0, sp, 280);
        lwc1(F20, gp, -32652);
    } else {
        charge(19);
        a0 = s2;
        a1 = 0;
        jal(0x2aab28, rg::fn_sub_2880E0_002880e0);
        sw(s2, s4, kCwMotionUnit);
        a0 = li(1);
        sh(a0, s4, kCwMotion);
        // the eye sp+352 = c with y = spread * gp-32600
        ld(v0, sp, 416);
        lwc1(F0, sp, 424);
        sd(v0, sp, 352);
        swc1(F0, sp, 360);
        lwc1(F1, gp, -32600);
        lwc1(F0, sp, 476);
        mul_s(F0, F1, F0);
        swc1(F0, sp, 356);
        lw(v1, s4, kCwSubject);
        lhu(v0, v1, kActTargetCount);
        if (v0 == a0) {
            // one target: shift by its unit's height along +/- f
            charge(7);
            lw(v0, v1, kActTargets);
            lw(v0, v0, 48);
            mtc1(zero, F0);
            c_lt_s(F22, F0);
            if (!cc()) {
                charge(14);
                lwc1(F1, v0, kUnitHeight);
                lwc1(F0, v0, kUnitScale);
                mul_s(F1, F1, F0);
                scale3_in(464, F1);
            } else {
                charge(13);
                lwc1(F1, v0, kUnitHeight);
                lwc1(F0, v0, kUnitScale);
                mul_s(F0, F1, F0);
                neg_s(F1, F0);
                scale3_in(464, F1);
            }
            charge(12);
            add3_sp(352, 352, 464);
        }
        charge(7);
        lwc1(F1, sp, 356);
        lif(v0, 0x42fa, F0);  // 125
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, 356);
        }
        charge(23);
        lwc1(F1, sp, 352);
        lwc1(F0, sp, 384);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 464);
        lwc1(F1, sp, 356);
        lwc1(F0, sp, 388);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 468);
        lwc1(F1, sp, 360);
        lwc1(F0, sp, 392);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 472);
        a0_sp(464);
        a1 = a0;
        jal(0x2aac7c, rg::fn_sub_4C69F0_004c69f0);
        mov_s(F20, F0);
        lif(v0, 0x4396, F0);  // 300
        c_lt_s(F25, F0);
        if (cc()) {
            charge(1);
            mov_s(F25, F0);
        }
        charge(69);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s4, kCwFov);
        mul_s(F12, F1, F0);
        jal(0x2aacb4, rg::fn_tanf_0052e930);
        div_s(F0, F25, F0);
        add_s(F20, F20, F0);
        tan_fov_wide(s4, 0x2aace4);
        mul_s(F1, F20, F0);
        lif(v0, 0x3e60, F0);
        mul_s(F1, F1, F0);
        lif(v0, 0x3f00, F0);
        mul_s(F21, F1, F0);
        side_shift(464, 384, F21, 0x2aad28);
        lwc1(F0, sp, 464);
        mul_s(F3, F0, F20);
        lwc1(F0, sp, 468);
        mul_s(F2, F0, F20);
        lwc1(F0, sp, 472);
        mul_s(F1, F0, F20);
        add_s(F0, F5, F3);
        swc1(F0, sp, 300);
        lwc1(F0, sp, 388);
        add_s(F0, F0, F2);
        swc1(F0, sp, 304);
        add_s(F0, F4, F1);
        swc1(F0, sp, 308);
        a0_sp(312);
        a1 = addiu(sp, 300);
        a2 = addiu(sp, 384);
        la69(a3, 30848);
        jal(0x2aada8, rg::fn_sub_2A4690_002a4690);
        if (s6 == 0) {
            charge(5);
            mtc1(zero, F0);
            c_lt_s(F22, F0);
            if (!cc()) {
                charge(10);
                lif(v0, 0xc1dc, F12);  // -27.5
                a0_sp(208);
                la69(a1, 30848);
                a2 = 0;
                jal(0x2aade4, rg::fn_sub_4C31B0_004c31b0);
            } else {
                charge(8);
                lif(v0, 0x41dc, F12);  // 27.5
                a0_sp(208);
                la69(a1, 30848);
                a2 = 0;
                jal(0x2aae0c, rg::fn_sub_4C31B0_004c31b0);
            }
            charge(110);
            a0_sp(448);
            a1 = addiu(sp, 464);
            a2 = addiu(sp, 208);
            jal(0x2aae20, rg::fn_sub_4C6C60_004c6c60);
            lwc1(F0, gp, -32644);
            mul_s(F20, F20, F0);
            tan_fov_wide(s4, 0x2aae48);
            mul_s(F1, F20, F0);
            lif(v0, 0x3e60, F0);
            mul_s(F1, F1, F0);
            lif(v0, 0x3f00, F0);
            mul_s(F21, F1, F0);
            side_shift(448, 384, F21, 0x2aae8c);
            lwc1(F0, sp, 448);
            mul_s(F3, F0, F20);
            lwc1(F0, sp, 452);
            mul_s(F2, F0, F20);
            lwc1(F0, sp, 456);
            mul_s(F1, F0, F20);
            add_s(F0, F5, F3);
            swc1(F0, sp, 272);
            lwc1(F0, sp, 388);
            add_s(F0, F0, F2);
            swc1(F0, sp, 276);
            add_s(F0, F4, F1);
            swc1(F0, sp, 280);
            lwc1(F1, gp, -32604);
            lwc1(F0, sp, 476);
            mul_s(F0, F1, F0);
            swc1(F0, sp, 276);
            // key A looks at c + normalise(S - c) * |S - c| / 4
            lwc1(F1, sp, 432);
            lwc1(F0, sp, 416);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 448);
            lwc1(F1, sp, 436);
            lwc1(F0, sp, 420);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 452);
            lwc1(F1, sp, 440);
            lwc1(F0, sp, 424);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 456);
            a0_sp(448);
            a1 = a0;
            jal(0x2aaf40, rg::fn_sub_4C69F0_004c69f0);
            lif(v0, 0x3e80, F1);
            mul_s(F1, F1, F0);
            lwc1(F0, sp, 448);
            mul_s(F3, F0, F1);
            swc1(F3, sp, 384);
            lwc1(F0, sp, 452);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 388);
            lwc1(F0, sp, 456);
            mul_s(F1, F0, F1);
            swc1(F1, sp, 392);
            lwc1(F0, sp, 416);
            add_s(F0, F3, F0);
            swc1(F0, sp, 384);
            lwc1(F0, sp, 420);
            add_s(F0, F2, F0);
            swc1(F0, sp, 388);
            lwc1(F0, sp, 424);
            add_s(F0, F1, F0);
            swc1(F0, sp, 392);
            a0_sp(284);
            a1 = addiu(sp, 272);
            a2 = addiu(sp, 384);
            la69(a3, 30848);
            jal(0x2aafb4, rg::fn_sub_2A4690_002a4690);
            lif(v0, 0x4070, F20);  // 3.75
        } else {
            skill_heights_2AA2B0();
            charge(11);
            lwc1(F0, sp, 300);
            swc1(F0, sp, 272);
            lwc1(F0, sp, 308);
            swc1(F0, sp, 280);
            a0_sp(284);
            a1 = addiu(sp, 272);
            a2 = addiu(sp, 384);
            la69(a3, 30848);
            jal(0x2ab10c, rg::fn_sub_2A4690_002a4690);
        }
    }
    charge(2);
    if (s7 == 0) {
        charge(2);
        if (s6 == 0) {
            charge(35);
            a3 = addiu(sp, 284);
            copy_vec4(sp, 312, sp, 284);
            a0_sp(464);
            la69(a1, 30864);
            a2 = li(1);
            jal(0x2ab158, rg::fn_sub_4BE1E0_004be1e0);
            lif(v0, 0x42c8, F1);  // 100
            lwc1(F0, sp, 464);
            mul_s(F3, F0, F1);
            swc1(F3, sp, 464);
            lwc1(F0, sp, 468);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 468);
            lwc1(F0, sp, 472);
            mul_s(F1, F0, F1);
            swc1(F1, sp, 472);
            lwc1(F0, sp, 300);
            add_s(F0, F0, F3);
            swc1(F0, sp, 272);
            lwc1(F0, sp, 304);
            add_s(F0, F0, F2);
            swc1(F0, sp, 276);
            lwc1(F0, sp, 308);
            add_s(F0, F0, F1);
            swc1(F0, sp, 280);
        }
    }
    charge(3);
    lw(v0, s4, 220);
    if (!lez(v0)) {
        charge(7);
        mtc1(zero, F12);
        lw(a0, s4, kCwSubject);
        a1 = 0;
        a2 = 0;
        a3 = li(1);
        jal(0x2ab1d0, rg::fn_sub_2A3E80_002a3e80);
    }
    charge(16);
    a0_sp(272);
    a1 = a0;
    jal(0x2ab1e0, rg::fn_sub_2A3590_002a3590);
    a0_sp(300);
    a1 = a0;
    jal(0x2ab1f0, rg::fn_sub_2A3590_002a3590);
    a0 = s4;
    a1 = addiu(sp, 272);
    a2 = addiu(sp, 300);
    a3 = li(1);
    jal(0x2ab208, rg::fn_sub_2A2290_002a2290);
    if (s1 == 0) {
        charge(6);
        a0 = s4;
        mov_s(F12, F20);
        jal(0x2ab220, rg::fn_sub_2A3110_002a3110);
    } else {
        charge(4);
        a0 = s4;
        mov_s(F12, F20);
        jal(0x2ab238, rg::fn_sub_2A3160_002a3160);
    }
    charge(2);
    if (s3 != 0) {
        charge(3);
        a0 = li(12);
        jal(0x2ab24c, rg::fn_sub_351BB0_00351bb0);
    }
    charge(19);
    ld(ra, sp, 176);
    lq(s8, sp, 160);
    lq(s7, sp, 144);
    lq(s6, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 480);
}

// sub_2AB330's aim: the rotation sp+rot from the eye sp+304 to the look-at point sp+336 (sub_2A4690), the direction
// sp+320 of it (sub_4BE1E0, axis 0x6978A0), and sub_2D1FD0((look.x, look.z), (eye.x, eye.z), (pivot.x, pivot.z) of
// sp+352, out sp+272) -> $f0
void Cpu2::aim_and_measure(s32 rot, u32 link_look, u32 link_dir, u32 link_dist) {
    a0_sp(rot);
    a1 = addiu(sp, 304);
    a2 = addiu(sp, 336);
    la69(a3, 30848);
    jal(link_look, rg::fn_sub_2A4690_002a4690);
    a0_sp(320);
    la69(a1, 30880);
    a2 = li(1);
    a3 = addiu(sp, rot);
    jal(link_dir, rg::fn_sub_4BE1E0_004be1e0);
    lwc1(F0, sp, 336);
    swc1(F0, sp, 240);
    lwc1(F0, sp, 344);
    swc1(F0, sp, 244);
    lwc1(F0, sp, 304);
    swc1(F0, sp, 248);
    lwc1(F0, sp, 312);
    swc1(F0, sp, 252);
    lwc1(F0, sp, 352);
    swc1(F0, sp, 280);
    lwc1(F0, sp, 360);
    swc1(F0, sp, 284);
    a0_sp(240);
    a1 = addiu(sp, 248);
    a2 = addiu(sp, 280);
    a3 = addiu(sp, 272);
    jal(link_dist, rg::fn_sub_2D1FD0_002d1fd0);
}

// sub_2AB330's side push: $f20 = $f20 * tan(1.2 fov/2) * 0.21875 * k (k = the float of k_hi); the eye sp+304 moves
// along the normal of the ground part of sp+d (through sp+264, sub_4C6B20) by +/- $f20 (`neg`: the other way)
void Cpu2::push_side(u32 link_tan, u32 link_norm, u32 k_hi, s32 d, bool neg) {
    tan_fov_wide(s4, link_tan);
    mul_s(F1, F20, F0);
    lif(v0, 0x3e60, F0);
    mul_s(F1, F1, F0);
    lif(v0, k_hi, F0);
    mul_s(F20, F1, F0);
    lwc1(F0, sp, d);
    swc1(F0, sp, 264);
    lwc1(F0, sp, d + 8);
    swc1(F0, sp, 268);
    a0_sp(264);
    a1 = a0;
    jal(link_norm, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 268);
    lwc1(F0, sp, 304);
    mtc1(zero, F2);
    adda_s(F2, F0);
    if (neg) msub_s(F0, F1, F20);
    else madd_s(F0, F1, F20);
    swc1(F0, sp, 304);
    lwc1(F1, sp, 264);
    lwc1(F0, sp, 312);
    adda_s(F2, F0);
    if (neg) madd_s(F0, F1, F20);
    else msub_s(F0, F1, F20);
    swc1(F0, sp, 312);
}

// sub_2AB330's eye: sp+dst = sp+304 + sp+320, at least 25 high (the y through $f2)
void Cpu2::eye_from_dir(s32 dst) {
    lwc1(F1, sp, 304);
    lwc1(F0, sp, 320);
    add_s(F0, F1, F0);
    swc1(F0, sp, dst);
    lwc1(F1, sp, 308);
    lwc1(F0, sp, 324);
    add_s(F2, F1, F0);
    swc1(F2, sp, dst + 4);
    lwc1(F1, sp, 312);
    lwc1(F0, sp, 328);
    add_s(F0, F1, F0);
    swc1(F0, sp, dst + 8);
    lif(v0, 0x41c8, F0);
    c_lt_s(F2, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, dst + 4);
    }
}

// 0x2AB330 sub_2AB330(cw, a1 = sound flag, a2 = keep flag): the subject / target / partner shot. Units: S = the
// subject's (+48), T = its first target's, P = S's partner (S+2560); their positions (sub_27FFB0) raised by half their
// radius ($f24 S.y, $f23 T.y, $f22 P.y, P.y at least 135 with the stored y 67.5); $f25 = S's height, $f20 = P's.
// cw+260 = T's position, cw+256 = the first target. The close variant s0: with gBtl+12 bit 21, else unless P stands
// 125 or more above T: sub_2A3420(cw), else the roll (sub_357FD0(0) bit 0) and sub_2A3380(cw).
// Close: P plays motion 1 (cw+288 = P, +292 = 0); the look-at point from P towards T (gp-32616 along it); the eye
// beside P by 1.5 * P's height on the side of cw+156 ($f26), its height by the ordering of P and T (gp-32620 /
// gp-32720 / gp-32592 / 0.25 factors, gBtl+12 bit 21 and T.y >= 500 special); the aim and measured distance (at
// least 275, plus P's height * gp-32612) / tan -> key B (sp+188, with a side push for $f26 < 0); then key A from S
// towards T at 2 * S's height (+150 / +350 when sub_17D800() and T.y > 450), measured again (+ 3 * S's height) ->
// sp+160; field of view 2.5.
// Far: P plays motion 0 (cw+288 = P, +292 = 1); the pivot T, the side offset max(T's height * gp-32584, 0.75 * P's
// height) at least 125 high; the look-at height by P vs T (gp-32720 / gp-32580); the measured distance + 1.5 * T's
// height over tan, at least 550; the side push (factor 2, the other way) for $f21 >= 0 -> key A (sp+160, rotation
// sp+172), copied to key B (sp+188 / sp+200); key A is re-aimed from S (raised by its radius * gp-32720) and moved
// towards key B's eye by gp-32616 of their distance; both at least 25 high; field of view 2.25.
// Without a2 key A = key B. The units around are shown (sub_2A3E80(subject, S+4, key A, 3), $f12 = 50), the pair
// sub_2A2290(cw, A, B, 1), the field of view sub_2A3110 and sub_351BB0(12) when a1.
void Cpu2::sub_2AB330() {
    enter(77);
    sp = addiu(sp, -416);
    sd(ra, sp, 144);
    sq(s6, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F26, sp, 24);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;
    s5 = a1;
    s6 = a2;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, 48);
    lw(v0, v0, kActTargets);
    lw(s3, v0, 48);
    lw(s2, s1, 2560);
    a0 = s1;
    a1 = addiu(sp, 400);
    jal(0x2ab398, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s3;
    a1 = addiu(sp, 384);
    jal(0x2ab3a8, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s2;
    a1 = addiu(sp, 368);
    jal(0x2ab3b8, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F5, s1, kUnitScale);
    lwc1(F0, s1, kUnitRadius);
    mul_s(F1, F0, F5);
    lif(v0, 0x3f00, F4);
    lwc1(F0, sp, 404);
    mtc1(zero, F3);
    adda_s(F3, F0);
    madd_s(F24, F4, F1);
    lwc1(F1, s3, kUnitRadius);
    lwc1(F0, s3, kUnitScale);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 388);
    adda_s(F3, F0);
    madd_s(F23, F4, F1);
    lwc1(F2, s2, kUnitScale);
    lwc1(F0, s2, kUnitRadius);
    mul_s(F1, F0, F2);
    lwc1(F0, sp, 372);
    adda_s(F3, F0);
    madd_s(F22, F4, F1);
    lwc1(F0, s1, kUnitHeight);
    mul_s(F25, F0, F5);
    lwc1(F0, s2, kUnitHeight);
    mul_s(F20, F0, F2);
    lwc1(F2, sp, 384);
    lwc1(F1, sp, 388);
    lwc1(F0, sp, 392);
    swc1(F2, s4, 260);
    swc1(F1, s4, 264);
    swc1(F0, s4, 268);
    lw(v0, s4, kCwSubject);
    lw(v0, v0, kActTargets);
    sw(v0, s4, 256);
    lif(v0, 0x4307, F0);  // 135
    c_lt_s(F22, F0);
    if (cc()) {
        charge(3);
        mov_s(F22, F0);
        v0 = lui(0x4287);
        sw(v0, sp, 372);
    }
    charge(6);
    gbtl(v0);
    lw(v1, v0, btl_task::kFlags);
    v0 = lui(0x20);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(3);
        s0 = li(1);
    } else {
        charge(10);
        a0 = s4;
        jal(0x2ab498, rg::fn_sub_2A3420_002a3420);
        sub_s(F1, F22, F23);
        v1 = lui(0x42fa);
        mtc1(v1, F0);
        c_lt_s(F1, F0);
        if (!cc()) {
            charge(3);
            s0 = 0;
        } else {
            charge(3);
            s0 = sltu(zero, v0);
            if (s0 == 0) {
                charge(7);
                a0 = 0;
                jal(0x2ab4d8, rg::fn_sub_357FD0_00357fd0);
                v0 = v0 & 0x1;
                s0 = sltu(zero, v0);
                if (s0 != 0) {
                    charge(4);
                    a0 = s4;
                    jal(0x2ab4f4, rg::fn_sub_2A3380_002a3380);
                    s0 = sltu(zero, v0);
                }
            }
        }
    }
    charge(2);
    // sp+320 = normalise(X - T) (length $f21), sp+336 = it * $f21 * gp-32616: X = P (close) or (P + S) / 2 (far)
    if (s0 != 0) {
        charge(30);
        lwc1(F1, sp, 368);
        lwc1(F0, sp, 384);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 320);
        lwc1(F1, sp, 372);
        lwc1(F0, sp, 388);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 324);
        lwc1(F1, sp, 376);
        lwc1(F0, sp, 392);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 328);
        a0_sp(320);
        a1 = a0;
        jal(0x2ab540, rg::fn_sub_4C69F0_004c69f0);
    } else {
        charge(46);
        lwc1(F1, sp, 368);
        lwc1(F0, sp, 400);
        add_s(F3, F1, F0);
        swc1(F3, sp, 352);
        lwc1(F1, sp, 372);
        lwc1(F0, sp, 404);
        add_s(F2, F1, F0);
        swc1(F2, sp, 356);
        lwc1(F1, sp, 376);
        lwc1(F0, sp, 408);
        add_s(F1, F1, F0);
        swc1(F1, sp, 360);
        lif(v0, 0x3f00, F0);
        mul_s(F3, F3, F0);
        swc1(F3, sp, 352);
        mul_s(F2, F2, F0);
        swc1(F2, sp, 356);
        mul_s(F1, F1, F0);
        swc1(F1, sp, 360);
        lwc1(F0, sp, 384);
        sub_s(F0, F3, F0);
        swc1(F0, sp, 320);
        lwc1(F0, sp, 388);
        sub_s(F0, F2, F0);
        swc1(F0, sp, 324);
        lwc1(F0, sp, 392);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 328);
        a0_sp(320);
        a1 = a0;
        jal(0x2ab600, rg::fn_sub_4C69F0_004c69f0);
    }
    mov_s(F21, F0);
    lwc1(F1, gp, -32616);
    mul_s(F1, F1, F0);
    scale3_sp(336, 320, F1);
    charge(24);
    // the look-at point sp+336 += T; sp+232 = normalise2(cw+156 - it)
    lwc1(F1, sp, 336);
    lwc1(F0, sp, 384);
    add_s(F2, F1, F0);
    swc1(F2, sp, 336);
    lwc1(F1, sp, 340);
    lwc1(F0, sp, 388);
    add_s(F0, F1, F0);
    swc1(F0, sp, 340);
    lwc1(F1, sp, 344);
    lwc1(F0, sp, 392);
    add_s(F1, F1, F0);
    swc1(F1, sp, 344);
    lwc1(F0, s4, kCwEye);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 232);
    lwc1(F0, s4, kCwEye + 8);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 236);
    a0_sp(232);
    a1 = a0;
    jal(0x2ab688, rg::fn_sub_4C6B20_004c6b20);
    if (s0 != 0) {
        charge(28);
        a0 = s2;
        a1 = li(1);
        jal(0x2ab6a0, rg::fn_sub_2880E0_002880e0);
        sw(s2, s4, kCwMotionUnit);
        sh(zero, s4, kCwMotion);
        s1 = s3;
        // the pivot sp+352 = P; the side $f26 = dot((d.z, -d.x), sp+232); the eye sp+304 beside P by 1.5 * P's height
        ld(v0, sp, 368);
        lwc1(F0, sp, 376);
        sd(v0, sp, 352);
        swc1(F0, sp, 360);
        lif(v0, 0x3fc0, F0);
        mul_s(F5, F0, F20);
        lwc1(F4, sp, 328);
        swc1(F4, sp, 224);
        lwc1(F3, sp, 320);
        neg_s(F1, F3);
        swc1(F1, sp, 228);
        lwc1(F2, sp, 232);
        lwc1(F0, sp, 236);
        mula_s(F1, F0);
        mtc1(zero, F1);
        madd_s(F26, F4, F2);
        c_lt_s(F26, F1);
        if (!cc()) {
            charge(10);
            lwc1(F0, sp, 352);
            adda_s(F1, F0);
            madd_s(F0, F4, F5);
            swc1(F0, sp, 304);
            lwc1(F0, sp, 360);
            adda_s(F1, F0);
            msub_s(F0, F3, F5);
            swc1(F0, sp, 312);
        } else {
            // the other side, and the look-at point halfway (T + d * $f21 / 2)
            charge(28);
            lwc1(F0, sp, 352);
            adda_s(F1, F0);
            msub_s(F0, F4, F5);
            swc1(F0, sp, 304);
            lwc1(F0, sp, 360);
            adda_s(F1, F0);
            madd_s(F0, F3, F5);
            swc1(F0, sp, 312);
            lif(v0, 0x3f00, F0);
            mul_s(F1, F0, F21);
            mul_s(F3, F3, F1);
            swc1(F3, sp, 336);
            lwc1(F0, sp, 324);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 340);
            mul_s(F1, F4, F1);
            swc1(F1, sp, 344);
            lwc1(F0, sp, 384);
            add_s(F0, F3, F0);
            swc1(F0, sp, 336);
            lwc1(F0, sp, 388);
            add_s(F0, F2, F0);
            swc1(F0, sp, 340);
            lwc1(F0, sp, 392);
            add_s(F0, F1, F0);
            swc1(F0, sp, 344);
        }
        charge(3);
        c_lt_s(F22, F23);
        if (!cc()) {
            // P at least as high as T: the look-at y += gp-32620 * T's radius; the eye y
            charge(13);
            lwc1(F1, s3, kUnitRadius);
            lwc1(F0, s3, kUnitScale);
            mul_s(F3, F1, F0);
            lwc1(F1, gp, -32620);
            lwc1(F0, sp, 340);
            mtc1(zero, F2);
            adda_s(F2, F0);
            madd_s(F3, F1, F3);
            swc1(F3, sp, 340);
            c_le_s(F22, F3);
            if (!cc()) {
                charge(9);
                lwc1(F1, s2, kUnitRadius);
                lwc1(F0, s2, kUnitScale);
                mul_s(F1, F1, F0);
                lwc1(F0, gp, -32720);
                adda_s(F2, F3);
                madd_s(F0, F0, F1);
                swc1(F0, sp, 308);
            } else {
                charge(4);
                lwc1(F0, sp, 356);
                swc1(F0, sp, 308);
            }
        } else {
            charge(6);
            gbtl(v0);
            lw(v1, v0, btl_task::kFlags);
            v0 = lui(0x20);
            v0 = v1 & v0;
            bool high = false;
            if (v0 != 0) {
                charge(6);
                lif(v0, 0x43fa, F0);  // 500
                c_lt_s(F23, F0);
                high = !cc();
            }
            if (high) {
                charge(18);
                lwc1(F1, s3, kUnitRadius);
                lwc1(F0, s3, kUnitScale);
                mul_s(F3, F1, F0);
                lwc1(F1, gp, -32720);
                lwc1(F0, sp, 340);
                mtc1(zero, F2);
                adda_s(F2, F0);
                madd_s(F0, F1, F3);
                swc1(F0, sp, 340);
            } else {
                charge(16);
                lwc1(F1, s3, kUnitRadius);
                lwc1(F0, s3, kUnitScale);
                mul_s(F3, F1, F0);
                lwc1(F1, gp, -32592);
                lwc1(F0, sp, 340);
                mtc1(zero, F2);
                adda_s(F2, F0);
                msub_s(F0, F1, F3);
                swc1(F0, sp, 340);
            }
            lif(v0, 0x3e80, F1);
            lwc1(F0, sp, 356);
            adda_s(F2, F0);
            madd_s(F0, F1, F22);
            swc1(F0, sp, 308);
        }
        charge(44);
        aim_and_measure(200, 0x2ab8e0, 0x2ab8fc, 0x2ab944);
        lwc1(F2, gp, -32612);
        mtc1(zero, F1);
        adda_s(F1, F0);
        madd_s(F20, F20, F2);
        v0 = li(275);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        c_lt_s(F20, F0);
        if (cc()) {
            charge(1);
            mov_s(F20, F0);
        }
        charge(5);
        lwc1(F0, sp, 272);
        swc1(F0, sp, 304);
        c_lt_s(F22, F23);
        if (!cc()) {
            charge(4);
            lwc1(F3, sp, 340);
            c_le_s(F22, F3);
            if (!cc()) {
                charge(11);
                lwc1(F1, s2, kUnitRadius);
                lwc1(F0, s2, kUnitScale);
                mul_s(F2, F1, F0);
                lwc1(F1, gp, -32588);
                mtc1(zero, F0);
                adda_s(F0, F3);
                madd_s(F0, F1, F2);
                swc1(F0, sp, 308);
            } else {
                charge(13);
                lwc1(F1, s2, kUnitRadius);
                lwc1(F0, s2, kUnitScale);
                mul_s(F3, F1, F0);
                lif(v0, 0x3e80, F2);
                lwc1(F1, sp, 356);
                mtc1(zero, F0);
                adda_s(F0, F1);
                madd_s(F0, F2, F3);
                swc1(F0, sp, 308);
            }
        } else {
            charge(8);
            lif(v0, 0x3e80, F2);
            lwc1(F1, sp, 356);
            mtc1(zero, F0);
            adda_s(F0, F1);
            madd_s(F0, F2, F22);
            swc1(F0, sp, 308);
        }
        charge(27);
        lwc1(F0, sp, 276);
        swc1(F0, sp, 312);
        tan_fov_wide(s4, 0x2aba44);
        div_s(F20, F20, F0);
        scale3_in(320, F20);
        mtc1(zero, F0);
        c_lt_s(F26, F0);
        if (cc()) {
            charge(37);
            push_side(0x2abaa8, 0x2abaec, 0x3fa0, 320, false);
        }
        charge(18);
        eye_from_dir(188);
        // key A: from S towards T
        charge(49);
        lwc1(F1, sp, 400);
        lwc1(F0, sp, 384);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 320);
        lwc1(F1, sp, 404);
        lwc1(F0, sp, 388);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 324);
        lwc1(F1, sp, 408);
        lwc1(F0, sp, 392);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 328);
        a0_sp(320);
        a1 = a0;
        jal(0x2abba8, rg::fn_sub_4C69F0_004c69f0);
        mov_s(F21, F0);
        lwc1(F1, gp, -32616);
        mul_s(F1, F1, F0);
        lwc1(F0, sp, 320);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 336);
        lwc1(F0, sp, 324);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 340);
        lwc1(F0, sp, 328);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 344);
        lwc1(F0, sp, 384);
        add_s(F0, F3, F0);
        swc1(F0, sp, 336);
        lwc1(F0, sp, 388);
        add_s(F0, F2, F0);
        swc1(F0, sp, 340);
        lwc1(F0, sp, 392);
        add_s(F0, F1, F0);
        swc1(F0, sp, 344);
        ld(v0, sp, 400);
        lwc1(F0, sp, 408);
        sd(v0, sp, 352);
        swc1(F0, sp, 360);
        lif(v0, 0x4000, F0);
        mul_s(F20, F0, F25);
        jal(0x2abc24, rg::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            charge(7);
            lwc1(F1, sp, 388);
            lif(v0, 0x43e1, F0);  // 450
            c_le_s(F1, F0);
            if (!cc()) {
                charge(8);
                lif(v0, 0x4316, F0);  // 150
                add_s(F20, F20, F0);
                lif(v0, 0x43af, F0);  // 350
                add_s(F24, F24, F0);
            }
        }
        charge(11);
        lif(v0, 0x3f00, F1);
        lwc1(F0, sp, 356);
        mtc1(zero, F3);
        adda_s(F3, F0);
        madd_s(F0, F1, F24);
        swc1(F0, sp, 308);
        c_lt_s(F26, F3);
        if (!cc()) {
            charge(12);
            lwc1(F1, sp, 328);
            lwc1(F0, sp, 352);
            adda_s(F3, F0);
            madd_s(F0, F1, F20);
            swc1(F0, sp, 304);
            lwc1(F1, sp, 320);
            lwc1(F0, sp, 360);
            adda_s(F3, F0);
            msub_s(F0, F1, F20);
            swc1(F0, sp, 312);
        } else {
            charge(27);
            lwc1(F4, sp, 328);
            lwc1(F0, sp, 352);
            adda_s(F3, F0);
            msub_s(F0, F4, F20);
            swc1(F0, sp, 304);
            lwc1(F2, sp, 320);
            lwc1(F0, sp, 360);
            adda_s(F3, F0);
            madd_s(F0, F2, F20);
            swc1(F0, sp, 312);
            mul_s(F1, F1, F21);
            mul_s(F3, F2, F1);
            swc1(F3, sp, 336);
            lwc1(F0, sp, 324);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 340);
            mul_s(F1, F4, F1);
            swc1(F1, sp, 344);
            lwc1(F0, sp, 384);
            add_s(F0, F3, F0);
            swc1(F0, sp, 336);
            lwc1(F0, sp, 388);
            add_s(F0, F2, F0);
            swc1(F0, sp, 340);
            lwc1(F0, sp, 392);
            add_s(F0, F1, F0);
            swc1(F0, sp, 344);
        }
        charge(83);
        lwc1(F1, s3, kUnitRadius);
        lwc1(F0, s3, kUnitScale);
        mul_s(F3, F1, F0);
        lwc1(F2, gp, -32720);
        lwc1(F1, sp, 340);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F0, F2, F3);
        swc1(F0, sp, 340);
        aim_and_measure(172, 0x2abd74, 0x2abd90, 0x2abdd8);
        lif(v0, 0x4040, F1);  // 3
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F20, F25, F1);
        lwc1(F0, sp, 272);
        swc1(F0, sp, 304);
        lif(v0, 0x3e80, F1);
        lwc1(F0, sp, 356);
        adda_s(F2, F0);
        madd_s(F0, F1, F24);
        swc1(F0, sp, 308);
        lwc1(F0, sp, 276);
        swc1(F0, sp, 312);
        tan_fov_wide(s4, 0x2abe38);
        div_s(F20, F20, F0);
        scale3_in(320, F20);
        mtc1(zero, F0);
        c_lt_s(F26, F0);
        if (cc()) {
            charge(37);
            push_side(0x2abe9c, 0x2abee0, 0x3fa0, 320, false);
        }
        charge(18);
        eye_from_dir(160);
        charge(4);
        lif(v0, 0x4020, F20);  // 2.5
    } else {
        charge(23);
        a0 = s2;
        a1 = 0;
        jal(0x2abf7c, rg::fn_sub_2880E0_002880e0);
        sw(s2, s4, kCwMotionUnit);
        v0 = li(1);
        sh(v0, s4, kCwMotion);
        // the pivot sp+352 = T; the side offset $f5 = max(T's height * gp-32584, 0.75 * P's height)
        ld(v0, sp, 384);
        lwc1(F0, sp, 392);
        sd(v0, sp, 352);
        swc1(F0, sp, 360);
        lwc1(F1, s3, kUnitHeight);
        lwc1(F0, s3, kUnitScale);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32584);
        mul_s(F5, F0, F1);
        lif(v0, 0x3f40, F0);
        mul_s(F0, F0, F20);
        c_le_s(F0, F5);
        if (!cc()) {
            charge(1);
            mov_s(F5, F0);
        }
        charge(7);
        lwc1(F1, sp, 356);
        lif(v0, 0x42fa, F0);  // 125
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, 356);
        }
        charge(15);
        lwc1(F4, sp, 328);
        swc1(F4, sp, 224);
        lwc1(F3, sp, 320);
        neg_s(F1, F3);
        swc1(F1, sp, 228);
        lwc1(F2, sp, 232);
        lwc1(F0, sp, 236);
        mula_s(F1, F0);
        mtc1(zero, F1);
        madd_s(F21, F4, F2);
        lwc1(F0, sp, 356);
        swc1(F0, sp, 308);
        c_lt_s(F21, F1);
        if (!cc()) {
            charge(14);
            lwc1(F0, sp, 352);
            adda_s(F1, F0);
            madd_s(F0, F4, F5);
            swc1(F0, sp, 304);
            lwc1(F0, sp, 360);
            adda_s(F1, F0);
            msub_s(F0, F3, F5);
            swc1(F0, sp, 312);
            ld(v0, sp, 320);
            lwc1(F0, sp, 328);
            sd(v0, sp, 288);
            swc1(F0, sp, 296);
        } else {
            charge(8);
            lwc1(F0, sp, 352);
            adda_s(F1, F0);
            msub_s(F0, F4, F5);
            swc1(F0, sp, 304);
            lwc1(F0, sp, 360);
            adda_s(F1, F0);
            madd_s(F0, F3, F5);
            swc1(F0, sp, 312);
        }
        charge(3);
        c_lt_s(F22, F23);
        if (!cc()) {
            charge(12);
            lwc1(F1, s2, kUnitRadius);
            lwc1(F0, s2, kUnitScale);
            mul_s(F3, F1, F0);
            lwc1(F2, gp, -32720);
        } else {
            charge(10);
            lwc1(F1, s2, kUnitRadius);
            lwc1(F0, s2, kUnitScale);
            mul_s(F3, F1, F0);
            lwc1(F2, gp, -32580);
        }
        lwc1(F1, sp, 340);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F0, F2, F3);
        swc1(F0, sp, 340);
        charge(65);
        aim_and_measure(172, 0x2ac100, 0x2ac11c, 0x2ac164);
        lwc1(F2, s3, kUnitHeight);
        lwc1(F1, s3, kUnitScale);
        mul_s(F3, F2, F1);
        lif(v0, 0x3fc0, F2);
        mtc1(zero, F1);
        adda_s(F1, F0);
        madd_s(F20, F2, F3);
        lwc1(F0, sp, 272);
        swc1(F0, sp, 304);
        lwc1(F0, sp, 356);
        swc1(F0, sp, 308);
        lwc1(F0, sp, 276);
        swc1(F0, sp, 312);
        tan_fov_wide(s4, 0x2ac1c0);
        div_s(F20, F20, F0);
        v0 = li(550);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        c_lt_s(F20, F0);
        if (cc()) {
            charge(1);
            mov_s(F20, F0);
        }
        charge(14);
        scale3_in(320, F20);
        mtc1(zero, F0);
        c_lt_s(F21, F0);
        if (!cc()) {
            charge(37);
            push_side(0x2ac244, 0x2ac288, 0x4000, 288, true);
        }
        charge(90);
        // key A (sp+160, rotation sp+172) = the eye + direction; key B (sp+188 / sp+200) = a copy of it
        lwc1(F1, sp, 304);
        lwc1(F0, sp, 320);
        add_s(F0, F1, F0);
        swc1(F0, sp, 160);
        lwc1(F1, sp, 308);
        lwc1(F0, sp, 324);
        add_s(F0, F1, F0);
        swc1(F0, sp, 164);
        lwc1(F1, sp, 312);
        lwc1(F0, sp, 328);
        add_s(F0, F1, F0);
        swc1(F0, sp, 168);
        copy_vec4(sp, 172, sp, 200);
        copy_vec3(sp, 160, sp, 188);
        // key A re-aimed from S (raised by its radius * gp-32720) and moved towards key B's eye
        lwc1(F1, sp, 400);
        lwc1(F0, sp, 188);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 320);
        lwc1(F1, sp, 404);
        lwc1(F0, sp, 192);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 324);
        lwc1(F1, sp, 408);
        lwc1(F0, sp, 196);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 328);
        a0_sp(320);
        a1 = a0;
        jal(0x2ac360, rg::fn_sub_4C69F0_004c69f0);
        mov_s(F20, F0);
        a0 = s1;
        a1 = addiu(sp, 352);
        jal(0x2ac374, rg::fn_sub_27FFB0_0027ffb0);
        lwc1(F1, s1, kUnitRadius);
        lwc1(F0, s1, kUnitScale);
        mul_s(F3, F1, F0);
        lwc1(F2, gp, -32720);
        lwc1(F1, sp, 356);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F0, F2, F3);
        swc1(F0, sp, 356);
        a0_sp(172);
        a1 = addiu(sp, 188);
        a2 = addiu(sp, 352);
        la69(a3, 30848);
        jal(0x2ac3b8, rg::fn_sub_2A4690_002a4690);
        lwc1(F0, gp, -32616);
        mul_s(F2, F0, F20);
        lwc1(F0, sp, 320);
        mul_s(F3, F0, F2);
        swc1(F3, sp, 320);
        lwc1(F0, sp, 324);
        mul_s(F1, F0, F2);
        swc1(F1, sp, 324);
        lwc1(F0, sp, 328);
        mul_s(F2, F0, F2);
        swc1(F2, sp, 328);
        lwc1(F0, sp, 188);
        add_s(F0, F0, F3);
        swc1(F0, sp, 160);
        lwc1(F0, sp, 192);
        add_s(F1, F0, F1);
        swc1(F1, sp, 164);
        lwc1(F0, sp, 196);
        add_s(F0, F0, F2);
        swc1(F0, sp, 168);
        lif(v0, 0x41c8, F0);
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, 164);
        }
        charge(7);
        lwc1(F1, sp, 192);
        lif(v0, 0x41c8, F0);
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, 192);
        }
        charge(2);
        lif(v0, 0x4010, F20);  // 2.25
    }
    charge(2);
    if (s6 == 0) {
        charge(14);
        copy_vec3(sp, 188, sp, 160);
        copy_vec4(sp, 200, sp, 172);
    }
    charge(20);
    lif(v0, 0x4248, F12);  // 50
    lw(a0, s4, kCwSubject);
    a1 = addiu(s1, 4);
    a2 = addiu(sp, 160);
    a3 = li(3);
    jal(0x2ac4ac, rg::fn_sub_2A3E80_002a3e80);
    a0 = s4;
    a1 = addiu(sp, 160);
    a2 = addiu(sp, 188);
    a3 = li(1);
    jal(0x2ac4c4, rg::fn_sub_2A2290_002a2290);
    a0 = s4;
    mov_s(F12, F20);
    jal(0x2ac4d4, rg::fn_sub_2A3110_002a3110);
    if (s5 != 0) {
        charge(3);
        a0 = li(12);
        jal(0x2ac4e8, rg::fn_sub_351BB0_00351bb0);
    }
    charge(18);
    ld(ra, sp, 144);
    lq(s6, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F26, sp, 24);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 416);
}

// sub_2AC6E0's common tail: `charge(5); a1 = cw+288; if (sub_2A3750(a0, a1)) { charge(cyc); sub_2880E0(cw+288,
// cw+292); }` -- the motion unit plays its motion once sub_2A3750 says it may ($a0 is whatever the case left there).
void Cpu2::motion_if_ready(u32 link_check, u32 link_motion, u64 cyc) {
    charge(5);
    lw(a1, s0, kCwMotionUnit);
    jal(link_check, rg::fn_sub_2A3750_002a3750);
    if (v0 != 0) {
        charge(cyc);
        lw(a0, s0, kCwMotionUnit);
        lhu(a1, s0, kCwMotion);
        jal(link_motion, rg::fn_sub_2880E0_002880e0);
    }
}

// 0x2AC6E0 sub_2AC6E0(cw): camera row 21's update, by the phase cw+272 through the jump table 0x7B7C70 (7 rows: 0, 1
// nothing; 2 / 6 the motion step; 3 the units shown once (sub_2A3E80(subject, 0, 0, 3), $f12 = 0, unless cw+220) and the
// motion step; 4 with cw+276 clear and a single target that is cw+256: the motion step and the units around (cw+156,
// cw+260, flags 51; $f12 = 10), with cw+276 set the plain motion step; 5 sub_2AB2A0(cw)). The motion step needs the
// subject to be a combatant (+26 bit 0); a phase >= 7 does nothing. A table entry outside the listed labels is a tail
// jump (the recompiled body's rt::lookup_func).
void Cpu2::sub_2AC6E0() {
    enter(8);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lhu(v1, a0, kCwPhase);
    at = sltiu(v1, 7);
    if (at != 0) {
        charge(7);
        a1 = lui(0x7b);
        a1 = addiu(a1, 31856);
        v1 = sll(v1, 2);
        v1 = addu(v1, a1);
        lw(v1, v1, 0);
        // the subject check of the motion steps: `lw r, 224(s0); beqz; lhu v1, 26(r); andi 1; beqz`
        const auto combatant = [&](Gpr& r) {
            charge(3);
            lw(r, s0, kCwSubject);
            if (r == 0) return false;
            charge(4);
            lhu(v1, r, 26);
            v1 = v1 & 0x1;
            return v1 != 0;
        };
        switch (static_cast<u32>(v1)) {
        case 0x2ac71c:
            if (combatant(v1)) motion_if_ready(0x2ac73c, 0x2ac754, 6);
            break;
        case 0x2ac764:
            if (combatant(a0)) {
                charge(3);
                lw(v0, s0, 220);
                if (v0 == 0) {
                    charge(6);
                    mtc1(zero, F12);
                    a1 = 0;
                    a2 = 0;
                    a3 = li(3);
                    jal(0x2ac79c, rg::fn_sub_2A3E80_002a3e80);
                }
                charge(1);
                a0 = s0;
                motion_if_ready(0x2ac7ac, 0x2ac7c4, 6);
            }
            break;
        case 0x2ac7d4:
            charge(3);
            lw(v1, s0, kCwPhaseFlag);
            if (v1 != 0) {
                if (combatant(v1)) motion_if_ready(0x2ac888, 0x2ac8a0, 6);
                break;
            }
            charge(3);
            lw(a2, s0, kCwSubject);
            if (a2 == 0) break;
            charge(4);
            lhu(a1, a2, kActTargetCount);
            v1 = li(1);
            if (a1 != v1) break;
            charge(4);
            lw(a1, s0, 256);
            lw(v1, a2, kActTargets);
            if (a1 != v1) break;
            charge(4);
            lhu(v1, a2, 26);
            v1 = v1 & 0x1;
            if (v1 == 0) break;
            motion_if_ready(0x2ac820, 0x2ac838, 4);
            charge(10);
            lif(v0, 0x4120, F12);  // 10.0
            lw(a0, s0, kCwSubject);
            a1 = addiu(s0, kCwEye);
            a2 = addiu(s0, 260);
            a3 = li(51);
            jal(0x2ac858, rg::fn_sub_2A3E80_002a3e80);
            break;
        case 0x2ac8b0:
            charge(4);
            jal(0x2ac8b0, rg::fn_sub_2AB2A0_002ab2a0);
            break;
        case 0x2ac8c0:
            if (combatant(v1)) motion_if_ready(0x2ac8e0, 0x2ac8f8, 4);
            break;
        case 0x2ac900:
            break;
        default:
            jr_unknown(v1);
            return;
        }
    }
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// =====================================================================================================================
// Not hand-written yet: the recompiled body (removed from the X-list before the slice is committed)
// =====================================================================================================================


}  // namespace p3fes::game::bcam

namespace p3fes::game {
#define P3FES_BCAM_API_2(name, addr) \
    void name(EEContext& ctx) { bcam::Cpu2(ctx).name(); }
P3FES_BCAM_BODIES_2(P3FES_BCAM_API_2)
#undef P3FES_BCAM_API_2
}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
#define P3FES_BCAM_SHIM_2(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { ::p3fes::game::bcam::Cpu2(ctx).name(); }
P3FES_BCAM_BODIES_2(P3FES_BCAM_SHIM_2)
#undef P3FES_BCAM_SHIM_2
}  // namespace p3fes::recomp_gen
