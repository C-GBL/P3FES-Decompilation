// Battle camera work states, part 3 (game/include/p3fes/game/battle_camera_3.h), hand-decompiled from SLUS_216.21.
// Phase 5 slice `battle_camera` (battle_camera.cpp has the band's overview, battle_camera_cpu.h the register-faithful
// Cpu view and the cycle model); tests/game/test_battle_camera_3.cpp runs each body against its __recomp body.
//
// The camera work states of the table 0x6939F0 take the camera work record gBtl+32 in $a0 (called through the row's
// init / update pointer with `jalr`). The record fields these bodies use: +156 the current key (a 28-byte camera key:
// position x, y, z, then the rotation quaternion), +184 the field of view in degrees, +224 the subject btlAction (its
// +48 btlUnit). A camera key is built from an eye and a target with sub_2A4690(key, eye, target, up = 0x697880 (0, 1,
// 0)); sub_4BE1E0(out, v, 1, key + 12) rotates a vector by a key's quaternion (v = 0x6978A0 (0, 0, -1): the view
// direction); the new keys go to the camera with sub_2A2290(record, from, to, mode) / sub_2A2170(record, key) /
// sub_2A2660(record, k0, k1, k2, k3, mode) (four keys: a spline) and the lens with sub_2A3110(record, $f12) /
// sub_2A44B0. The distance that frames a unit of height h is h / tan(fov / 2) (tanf on the record's +184 * 0.5, often
// times the $gp constant gp-32656 = 1.2). The btlUnit fields read here: +28 the unit's rotation quaternion, +44 its
// scale, +140 / +144 its height / width (both times the scale).
#include "battle_camera_cpu.h"
#include "p3fes/game/battle_camera_3.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);    // (n): 0..n-1 (battle_data)
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);     // btlUnit position (unit, out)
void fn_sub_280050_00280050(p3fes::EEContext&);     // btlUnit position, another point (unit, out)
void fn_sub_280130_00280130(p3fes::EEContext&);     // btlUnit position, another point (unit, out)
void fn_sub_2802D0_002802d0(p3fes::EEContext&);     // btlUnit position, another point (unit, out)
void fn_sub_280870_00280870(p3fes::EEContext&);     // a side's centre / extent (side, a1, out, out, out, a5)
void fn_sub_2C0880_002c0880(p3fes::EEContext&);     // the current candidate (record)
void fn_sub_2D1E70_002d1e70(p3fes::EEContext&);
void fn_sub_2D1F30_002d1f30(p3fes::EEContext&);
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_2D5BF0_002d5bf0(p3fes::EEContext&);
void fn_sub_3093A0_003093a0(p3fes::EEContext&);     // (DatUnit) (battle_calc)
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);     // quaternion: rotate about an axis (q, axis, mode; $f12 degrees)
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);     // rotate a vector by a quaternion (out, v, 1, q)
void fn_sub_4BE310_004be310(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);     // a rotation matrix about an axis (out, axis, mode; $f12 degrees)
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);     // vector normalise (out, in); the length in $f0
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6AF0_004c6af0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);     // transform a vector by a matrix (out, v, m)
void fn_tanf_0052e930(p3fes::EEContext&);           // tanf($f12) -> $f0
// this slice (the generated entry points: the shims of battle_camera.cpp)
#define P3FES_BCAM3_DECL(name, addr) void fn_##name##_##addr(p3fes::EEContext&);
P3FES_BCAM_BODIES(P3FES_BCAM3_DECL)
#undef P3FES_BCAM3_DECL
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

using namespace btl_cam;

namespace btl_cam3 {
inline constexpr s32 kCwKey = 156;      // camera work record: the current 28-byte key
inline constexpr s32 kCwFov = 184;      // f32: the field of view (degrees)
inline constexpr s32 kCwSubject = 224;  // u32: the subject btlAction
inline constexpr s32 kActUnit = 48;     // btlAction: its btlUnit
inline constexpr s32 kUnitRot = 28;     // btlUnit: rotation quaternion
inline constexpr s32 kUnitScale = 44;   // f32
inline constexpr s32 kUnitHeight = 140; // f32 (times +44)
inline constexpr s32 kUnitWidth = 144;  // f32 (times +44)
inline constexpr s32 kGpFovScale = -32656;  // f32 1.2
}  // namespace btl_cam3
using namespace btl_cam3;

class Cpu3 final : public Cpu {
public:
    using Cpu::Cpu;
#define P3FES_BCAM_BODY_3(name, addr) void name();
    P3FES_BCAM_BODIES_3(P3FES_BCAM_BODY_3)
#undef P3FES_BCAM_BODY_3

private:
    // `a0 = sp+out; a1 = 0x6978A0 (0, 0, -1); a2 = 1; a3 = sp+key + 12...`: the view direction of a key / quaternion
    // at sp+q into sp+out
    void view_dir(u32 link, s32 out, s32 q) {
        a0 = addiu(sp, out);
        a1 = lui(0x69);
        a1 = addiu(a1, 30880);
        a2 = li(1);
        a3 = addiu(sp, q);
        jal(link, rg::fn_sub_4BE1E0_004be1e0);
    }
    // `sub_2A4690(sp+key, sp+eye, sp+at, 0x697880 (0, 1, 0))`: the key looking from eye at the target
    void look_at(u32 link, s32 key, s32 eye, s32 target) {
        a0 = addiu(sp, key);
        a1 = addiu(sp, eye);
        a2 = addiu(sp, target);
        a3 = lui(0x69);
        a3 = addiu(a3, 30848);
        jal(link, rg::fn_sub_2A4690_002a4690);
    }
    // the vector sp+dir scaled in place by f (x, y, z left in $f3, $f2, $f1) and sp+dst = sp+base + it
    void scale_add(s32 dir, unsigned f, s32 base, s32 dst) {
        lwc1(F0, sp, dir);
        mul_s(F3, F0, f);
        swc1(F3, sp, dir);
        lwc1(F0, sp, dir + 4);
        mul_s(F2, F0, f);
        swc1(F2, sp, dir + 4);
        lwc1(F0, sp, dir + 8);
        mul_s(F1, F0, f);
        swc1(F1, sp, dir + 8);
        lwc1(F0, sp, base);
        add_s(F0, F0, F3);
        swc1(F0, sp, dst);
        lwc1(F0, sp, base + 4);
        add_s(F0, F0, F2);
        swc1(F0, sp, dst + 4);
        lwc1(F0, sp, base + 8);
        add_s(F0, F0, F1);
        swc1(F0, sp, dst + 8);
    }
    // the same with sp+dst = sp+base - it
    void scale_sub(s32 dir, unsigned f, s32 base, s32 dst) {
        lwc1(F0, sp, dir);
        mul_s(F3, F0, f);
        swc1(F3, sp, dir);
        lwc1(F0, sp, dir + 4);
        mul_s(F2, F0, f);
        swc1(F2, sp, dir + 4);
        lwc1(F0, sp, dir + 8);
        mul_s(F1, F0, f);
        swc1(F1, sp, dir + 8);
        lwc1(F0, sp, base);
        sub_s(F0, F0, F3);
        swc1(F0, sp, dst);
        lwc1(F0, sp, base + 4);
        sub_s(F0, F0, F2);
        swc1(F0, sp, dst + 4);
        lwc1(F0, sp, base + 8);
        sub_s(F0, F0, F1);
        swc1(F0, sp, dst + 8);
    }
    // sp+dst = sp+a - sp+b (three floats through $f1, $f0)
    void sub_vec(s32 dst, s32 a, s32 b) {
        for (s32 k = 0; k < 12; k += 4) {
            lwc1(F1, sp, a + k);
            lwc1(F0, sp, b + k);
            sub_s(F0, F1, F0);
            swc1(F0, sp, dst + k);
        }
    }
    // The limited slerp (entered with $f0 = the angle between the quaternions q0 / q1, $f1 = the largest angle):
    // t = $f1 / $f0, sub_4BE310(q0, q1, sp+data) sets the slerp up at sp+data (q0' +0, q1' +16 pre-divided by
    // sin(angle), the angle +32, a no-sine flag +36), and sp+out = q0 for t <= 0, q1 for t >= 1, else q0' * sin((1 - t)
    // * angle) + q1' * sin(t * angle) (the sines by their inline Taylor series to x^13: c13 = the gp slot of the 1/13!
    // coefficient, c9 the one of 1/9! (the copies differ per function), the others gp-32696 / -32688 / -32684 / -32680;
    // with the flag set the weights stay 1 - t and t).
    void slerp_limited(u32 link, const Gpr& q0b, s32 q0o, const Gpr& q1b, s32 q1o, s32 data, s32 out, s32 c13, s32 c9) {
        charge(13);
        div_s(F20, F1, F0);
        a0 = addiu(q0b, q0o);
        a1 = addiu(q1b, q1o);
        a2 = addiu(sp, data);
        jal(link, rg::fn_sub_4BE310_004be310);
        mtc1(zero, F11);
        c_le_s(F20, F11);
        if (cc()) {
            charge(10);
            copy_vec4(q0b, q0o, sp, out);
            return;
        }
        charge(6);
        lif(v0, 0x3f80, F0);
        c_le_s(F0, F20);
        if (cc()) {
            charge(10);
            copy_vec4(q1b, q1o, sp, out);
            return;
        }
        charge(4);
        sub_s(F0, F0, F20);  // 1 - t
        lw(v0, sp, data + 36);
        if (v0 == 0) {
            charge(37);
            lwc1(F10, sp, data + 32);
            mul_s(F4, F0, F10);
            mul_s(F3, F4, F4);
            lwc1(F9, gp, c13);
            lwc1(F8, gp, -32696);
            adda_s(F11, F8);
            madd_s(F0, F9, F3);
            lwc1(F7, gp, c9);
            adda_s(F11, F7);
            madd_s(F0, F3, F0);
            lwc1(F6, gp, -32688);
            adda_s(F11, F6);
            madd_s(F0, F3, F0);
            lwc1(F5, gp, -32684);
            adda_s(F11, F5);
            madd_s(F0, F3, F0);
            lwc1(F2, gp, -32680);
            adda_s(F11, F2);
            madd_s(F1, F3, F0);
            mul_s(F0, F3, F4);
            adda_s(F11, F4);
            madd_s(F0, F0, F1);
            mul_s(F4, F20, F10);
            mul_s(F3, F4, F4);
            adda_s(F11, F8);
            madd_s(F1, F9, F3);
            adda_s(F11, F7);
            madd_s(F1, F3, F1);
            adda_s(F11, F6);
            madd_s(F1, F3, F1);
            adda_s(F11, F5);
            madd_s(F1, F3, F1);
            adda_s(F11, F2);
            madd_s(F2, F3, F1);
            mul_s(F1, F3, F4);
            adda_s(F11, F4);
            madd_s(F20, F1, F2);
        }
        charge(28);
        lwc1(F1, sp, data);
        mul_s(F5, F1, F0);
        swc1(F5, sp, out);
        lwc1(F1, sp, data + 4);
        mul_s(F4, F1, F0);
        swc1(F4, sp, out + 4);
        lwc1(F1, sp, data + 8);
        mul_s(F3, F1, F0);
        swc1(F3, sp, out + 8);
        lwc1(F1, sp, data + 16);
        mtc1(zero, F2);
        adda_s(F2, F5);
        madd_s(F1, F1, F20);
        swc1(F1, sp, out);
        lwc1(F1, sp, data + 20);
        adda_s(F2, F4);
        madd_s(F1, F1, F20);
        swc1(F1, sp, out + 4);
        lwc1(F1, sp, data + 24);
        adda_s(F2, F3);
        madd_s(F1, F1, F20);
        swc1(F1, sp, out + 8);
        lwc1(F2, sp, data + 12);
        lwc1(F1, sp, data + 28);
        mula_s(F1, F20);
        madd_s(F0, F2, F0);
        swc1(F0, sp, out + 12);
    }
    // the y in $f1 (stored at sp+off) at least 25: `lui; mtc1 $f0; c.lt.s $f1, $f0; bc1f; swc1 $f0, off(sp)`
    void at_least_25(s32 off) {
        lif(v0, 0x41c8, F0);  // 25
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, off);
        }
    }
    // sub_2B0280's horizontal distance: (sp+304 x / z, sp+272 x / z) and the eye (sp+320 x, $f21) through the
    // frame words sp+224 / +232 / +248, sub_2D1FD0(sp+224, sp+232, sp+248, sp+240) -> $f0 (the point sp+240)
    void horizontal_distance(u32 link) {
        lwc1(F0, sp, 304);
        swc1(F0, sp, 224);
        lwc1(F0, sp, 312);
        swc1(F0, sp, 228);
        lwc1(F0, sp, 272);
        swc1(F0, sp, 232);
        lwc1(F0, sp, 280);
        swc1(F0, sp, 236);
        lwc1(F0, sp, 320);
        swc1(F0, sp, 248);
        swc1(F21, sp, 252);
        a0 = addiu(sp, 224);
        a1 = addiu(sp, 232);
        a2 = addiu(sp, 248);
        a3 = addiu(sp, 240);
        jal(link, rg::fn_sub_2D1FD0_002d1fd0);
    }
    // sp+v *= f (three floats through $f0)
    void scale_by(s32 v, unsigned f) {
        for (s32 k = 0; k < 12; k += 4) {
            lwc1(F0, sp, v + k);
            mul_s(F0, F0, f);
            swc1(F0, sp, v + k);
        }
    }
    // sub_2AEF80's eye behind the subject (after tanf; the base point sp+base with its y / z in $f21 / $f20, the
    // direction sp+360, the width $f22): sp+344 = base + direction * (width + sp+396 / tan), its y = gp-32484 (0.25) *
    // the side's high y sp+412
    void behind_eye(s32 base) {
        lwc1(F1, sp, 396);
        div_s(F0, F1, F0);
        add_s(F1, F22, F0);
        lwc1(F0, sp, 360);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 360);
        lwc1(F0, sp, 364);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 364);
        lwc1(F0, sp, 368);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 368);
        lwc1(F0, sp, base);
        add_s(F0, F0, F3);
        swc1(F0, sp, 344);
        add_s(F0, F21, F2);
        swc1(F0, sp, 348);
        add_s(F0, F20, F1);
        swc1(F0, sp, 352);
        lwc1(F1, gp, -32484);
        lwc1(F0, sp, 412);
        mul_s(F0, F1, F0);
        swc1(F0, sp, 348);
    }
    // f = max(f, g) as compiled: `c.le.s f, g; bc1t 1f; b 2f; 1: mov.s f, g; 2:` (2 cycles kept, 1 raised)
    void max_le(unsigned f, unsigned g) {
        c_le_s(f, g);
        if (cc()) {
            charge(1);
            mov_s(f, g);
        } else {
            charge(2);
        }
    }
    // f = max(f, g): `c.lt.s f, g; bc1f 1f; mov.s f, g; 1:` (1 cycle when raised)
    void max_lt(unsigned f, unsigned g) {
        c_lt_s(f, g);
        if (cc()) {
            charge(1);
            mov_s(f, g);
        }
    }
    // rec+off = ($f1 < $f0) ? 0 : 1, as compiled (`c.lt.s; li v0, 1; bc1f; move v0, zero; sw v0`)
    void side_flag(const Gpr& rec, s32 off) {
        charge(4);
        c_lt_s(F1, F0);
        v0 = li(1);
        if (cc()) {
            charge(1);
            v0 = 0;
        }
        charge(1);
        sw(v0, rec, off);
    }
    // sp+dst = sp+a + sp+b (three floats through $f1, $f0)
    void add_vec(s32 dst, s32 a, s32 b) {
        for (s32 k = 0; k < 12; k += 4) {
            lwc1(F1, sp, a + k);
            lwc1(F0, sp, b + k);
            add_s(F0, F1, F0);
            swc1(F0, sp, dst + k);
        }
    }
    // v1 = idx & 0xFFFF, v0 = sp + 28 * v1: a key of a frame array
    void key_slot(const Gpr& idx) {
        v1 = idx & 0xffff;
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
    }
    // `lwc1 $f0, 184(rec); mul.s $f12, half, $f0` (half = $f1 / $f3 = 0.5): the half field of view, tanf of it
    void tan_half_fov(u32 link, const Gpr& rec, unsigned half) {
        lwc1(F0, rec, kCwFov);
        mul_s(F12, half, F0);
        jal(link, rg::fn_tanf_0052e930);
    }
    // ... times gp-32656 (1.2): `lwc1 $f0, 184(rec); mul.s $f1, half, $f0; lwc1 $f0, -32656(gp); mul.s $f12, $f0, $f1`
    void tan_half_fov12(u32 link, const Gpr& rec, unsigned half) {
        lwc1(F0, rec, kCwFov);
        mul_s(F1, half, F0);
        lwc1(F0, gp, kGpFovScale);
        mul_s(F12, F0, F1);
        jal(link, rg::fn_tanf_0052e930);
    }
};

// 0x2AEF80 sub_2AEF80(record, a1 = set at once): the camera between the subject and its target's side. The current
// target candidate (sub_2C0880(subject + 136)) and its side's extent (sub_280870(1 << its side, 1, sp+392, sp+412,
// sp+408, 1) -> $f23, the centre sp+392, the high / low y); the subject's position sp+328 and the target's sp+312
// (sub_280050). The centre's y is at least the subject's height (the subject's y + half its height; half of that when
// the centre is lower) and the high y at least it. The centre moves 0.3 (gp-32628) * $f23 toward the subject. Key 0
// (sp+156) looks at the centre from behind the subject: the eye = subject (at the centre height) + the direction away
// from the centre * (the subject's width + centre height / tan(fov / 2)), its y 0.25 (gp-32484) * the high y; the
// distance = max(sub_2D1E70(eye, centre), 1.15 * $f23 / tan(1.2 * fov / 2) (gp-32512)), at least 1100; the end point
// sp+144 = the centre (moved sideways by 0.21875 * distance * tan(1.2 * fov / 2)) + view direction * distance. Key 1
// (sp+184): the same toward the target unit (factor 1.1, gp-32576) -> sp+172. Unless record+262 is set, the result
// sp+236 = the slerp of the two rotations at 0.825 / 0.175 (gp-32480 / gp-32476; sub_4BE310 at sp+96, the sines' series
// inline) and the same blend of the two points; with +262 it is key 0 (sub_2A44F0). a1: set at once (sub_2A2170); else
// sub_2A2290(record, the current key, the result, 1) and the lens 0.75.
void Cpu3::sub_2AEF80() {
    enter(57);
    sp = addiu(sp, -416);
    sd(ra, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s3 = a0;
    s2 = a1;
    lw(s1, a0, kCwSubject);
    a0 = addiu(s1, 136);
    jal(0x2aefb8, rg::fn_sub_2C0880_002c0880);
    s0 = v0;
    lw(s1, s1, kActUnit);
    a0 = addiu(sp, 208);
    a1 = addiu(s3, kCwKey);
    jal(0x2aefd0, rg::fn_sub_2A4470_002a4470);
    lw(v0, s0, kActUnit);
    lbu(v0, v0, 162);
    a1 = li(1);
    v0 = sllv(a1, v0);
    a0 = v0 & 0xffff;
    a2 = addiu(sp, 392);
    a3 = addiu(sp, 412);
    t0 = addiu(sp, 408);
    t1 = a1;
    jal(0x2aeffc, rg::fn_sub_280870_00280870);
    mov_s(F23, F0);
    a0 = s1;
    a1 = addiu(sp, 328);
    jal(0x2af010, rg::fn_sub_280050_00280050);
    lwc1(F1, s1, kUnitScale);
    lwc1(F0, s1, kUnitHeight);
    mul_s(F20, F0, F1);
    lwc1(F0, s1, kUnitWidth);
    mul_s(F22, F0, F1);
    lw(a0, s0, kActUnit);
    a1 = addiu(sp, 312);
    jal(0x2af034, rg::fn_sub_280050_00280050);
    lif(v0, 0x3f00, F2);
    mul_s(F1, F2, F20);
    lwc1(F0, sp, 332);
    add_s(F1, F0, F1);
    lwc1(F0, sp, 396);
    c_lt_s(F0, F1);
    if (cc()) {
        charge(2);
        mul_s(F0, F2, F1);
        swc1(F0, sp, 396);
    }
    charge(4);
    lwc1(F0, sp, 412);
    c_lt_s(F0, F1);
    if (cc()) {
        charge(1);
        swc1(F1, sp, 412);
    }
    // key 0: from behind the subject at the side's centre
    charge(120);
    ld(v0, sp, 328);
    lwc1(F0, sp, 336);
    sd(v0, sp, 376);
    swc1(F0, sp, 384);
    lwc1(F2, sp, 396);
    swc1(F2, sp, 380);
    lwc1(F1, sp, 376);
    lwc1(F0, sp, 392);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 360);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 364);
    lwc1(F1, sp, 384);
    lwc1(F0, sp, 400);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 368);
    a0 = addiu(sp, 360);
    a1 = a0;
    jal(0x2af0c8, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F0, gp, -32628);  // 0.3
    mul_s(F1, F0, F23);
    lwc1(F0, sp, 360);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 360);
    lwc1(F0, sp, 364);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 364);
    lwc1(F0, sp, 368);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 368);
    lwc1(F0, sp, 392);
    add_s(F2, F0, F2);
    swc1(F2, sp, 392);
    lwc1(F0, sp, 396);
    add_s(F21, F0, F3);
    swc1(F21, sp, 396);
    lwc1(F0, sp, 400);
    add_s(F1, F0, F1);
    swc1(F1, sp, 400);
    ld(v0, sp, 328);
    lwc1(F0, sp, 336);
    sd(v0, sp, 272);
    swc1(F0, sp, 280);
    swc1(F21, sp, 276);
    lwc1(F0, sp, 272);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 360);
    sub_s(F0, F21, F21);
    swc1(F0, sp, 364);
    lwc1(F20, sp, 280);
    sub_s(F0, F20, F1);
    swc1(F0, sp, 368);
    a0 = addiu(sp, 360);
    a1 = a0;
    jal(0x2af15c, rg::fn_sub_4C69F0_004c69f0);
    lif(v0, 0x3f00, F1);
    tan_half_fov(0x2af174, s3, F1);
    behind_eye(272);
    look_at(0x2af1f0, 156, 344, 392);
    a0 = addiu(sp, 344);
    a1 = addiu(sp, 392);
    jal(0x2af200, rg::fn_sub_2D1E70_002d1e70);
    mov_s(F20, F0);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2af224, s3, F1);
    lwc1(F1, gp, -32512);  // 1.15
    mul_s(F1, F1, F23);
    div_s(F21, F1, F0);
    view_dir(0x2af24c, 360, 156);
    max_le(F20, F21);
    charge(7);
    v0 = li(1100);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    max_lt(F20, F0);
    charge(135);
    scale_by(360, F20);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2af2c8, s3, F1);
    mul_s(F1, F20, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 360);
    swc1(F0, sp, 304);
    lwc1(F0, sp, 368);
    swc1(F0, sp, 308);
    a0 = addiu(sp, 304);
    a1 = a0;
    jal(0x2af2fc, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 308);
    lwc1(F0, sp, 392);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, F20);
    swc1(F3, sp, 392);
    lwc1(F1, sp, 304);
    lwc1(F0, sp, 400);
    adda_s(F2, F0);
    msub_s(F1, F1, F20);
    swc1(F1, sp, 400);
    lwc1(F0, sp, 360);
    add_s(F0, F3, F0);
    swc1(F0, sp, 144);
    lwc1(F21, sp, 396);
    lwc1(F0, sp, 364);
    add_s(F0, F21, F0);
    swc1(F0, sp, 148);
    lwc1(F0, sp, 368);
    add_s(F0, F1, F0);
    swc1(F0, sp, 152);
    // key 1: from behind the subject at the target unit
    ld(v0, sp, 328);
    lwc1(F0, sp, 336);
    sd(v0, sp, 288);
    swc1(F0, sp, 296);
    swc1(F21, sp, 292);
    lwc1(F1, sp, 288);
    lwc1(F0, sp, 312);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 360);
    lwc1(F0, sp, 316);
    sub_s(F0, F21, F0);
    swc1(F0, sp, 364);
    lwc1(F20, sp, 296);
    lwc1(F0, sp, 320);
    sub_s(F0, F20, F0);
    swc1(F0, sp, 368);
    a0 = addiu(sp, 360);
    a1 = a0;
    jal(0x2af3a4, rg::fn_sub_4C69F0_004c69f0);
    lif(v0, 0x3f00, F1);
    tan_half_fov(0x2af3bc, s3, F1);
    behind_eye(288);
    look_at(0x2af438, 184, 344, 312);
    a0 = addiu(sp, 344);
    a1 = addiu(sp, 312);
    jal(0x2af448, rg::fn_sub_2D1E70_002d1e70);
    mov_s(F20, F0);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2af46c, s3, F1);
    lwc1(F1, gp, -32576);  // 1.1
    mul_s(F1, F1, F23);
    div_s(F21, F1, F0);
    view_dir(0x2af494, 360, 184);
    max_le(F20, F21);
    charge(7);
    v0 = li(1100);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    max_lt(F20, F0);
    charge(57);
    scale_by(360, F20);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2af510, s3, F1);
    mul_s(F1, F20, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 360);
    swc1(F0, sp, 304);
    lwc1(F0, sp, 368);
    swc1(F0, sp, 308);
    a0 = addiu(sp, 304);
    a1 = a0;
    jal(0x2af544, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 308);
    lwc1(F0, sp, 392);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F0, F1, F20);
    swc1(F0, sp, 392);
    lwc1(F1, sp, 304);
    lwc1(F0, sp, 400);
    adda_s(F2, F0);
    msub_s(F0, F1, F20);
    swc1(F0, sp, 400);
    add_vec(172, 312, 360);
    lhu(v0, s3, 262);
    if (v0 == 0) {
        // the blend: the rotations slerped at 0.825 / 0.175, the points mixed the same way
        charge(10);
        a0 = addiu(sp, 156);
        a1 = addiu(sp, 184);
        a2 = addiu(sp, 96);
        jal(0x2af5c4, rg::fn_sub_4BE310_004be310);
        lwc1(F1, gp, -32480);  // 0.825
        lwc1(F0, gp, -32476);  // 0.175
        lw(v0, sp, 132);
        if (v0 == 0) {
            charge(39);
            lwc1(F12, sp, 128);
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
        lwc1(F2, sp, 96);
        mul_s(F6, F2, F1);
        swc1(F6, sp, 248);
        lwc1(F2, sp, 100);
        mul_s(F5, F2, F1);
        swc1(F5, sp, 252);
        lwc1(F2, sp, 104);
        mul_s(F4, F2, F1);
        swc1(F4, sp, 256);
        lwc1(F2, sp, 112);
        mtc1(zero, F3);
        adda_s(F3, F6);
        madd_s(F2, F2, F0);
        swc1(F2, sp, 248);
        lwc1(F2, sp, 116);
        adda_s(F3, F5);
        madd_s(F2, F2, F0);
        swc1(F2, sp, 252);
        lwc1(F2, sp, 120);
        adda_s(F3, F4);
        madd_s(F2, F2, F0);
        swc1(F2, sp, 256);
        lwc1(F3, sp, 108);
        lwc1(F2, sp, 124);
        mula_s(F2, F0);
        madd_s(F0, F3, F1);
        swc1(F0, sp, 260);
        lwc1(F0, sp, 144);
        lwc1(F1, gp, -32480);
        mul_s(F6, F0, F1);
        swc1(F6, sp, 144);
        lwc1(F0, sp, 148);
        mul_s(F5, F0, F1);
        swc1(F5, sp, 148);
        lwc1(F0, sp, 152);
        mul_s(F4, F0, F1);
        swc1(F4, sp, 152);
        lwc1(F0, sp, 172);
        lwc1(F1, gp, -32476);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 172);
        lwc1(F0, sp, 176);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 176);
        lwc1(F0, sp, 180);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 180);
        add_s(F0, F6, F3);
        swc1(F0, sp, 236);
        add_s(F0, F5, F2);
        swc1(F0, sp, 240);
        add_s(F0, F4, F1);
        swc1(F0, sp, 244);
    } else {
        charge(4);
        a0 = addiu(sp, 236);
        a1 = addiu(sp, 144);
        jal(0x2af764, rg::fn_sub_2A44F0_002a44f0);
    }
    charge(2);
    if (s2 != 0) {
        charge(6);
        a0 = s3;
        a1 = addiu(sp, 236);
        jal(0x2af77c, rg::fn_sub_2A2170_002a2170);
    } else {
        charge(11);
        a0 = s3;
        a1 = addiu(sp, 208);
        a2 = addiu(sp, 236);
        a3 = li(1);
        jal(0x2af79c, rg::fn_sub_2A2290_002a2290);
        lif(v0, 0x3f40, F12);  // 0.75
        a0 = s3;
        jal(0x2af7b0, rg::fn_sub_2A3110_002a3110);
    }
    charge(12);
    ld(ra, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 416);
}

// 0x2AF960 sub_2AF960(record): table row 10's init, the subject and its first target side by side. record+280 = the
// target action. Key A = the current key. The subject's point +220 / +228 at its +132 * scale height (sp+264); the
// target's point toward the subject (sub_2802D0(target, subject, sp+248)); the height $f22 from 0.15 of both heights,
// $f20 = the subject's +232 + both widths. The centre sp+296 a quarter of $f20 from the target toward the subject, at
// half $f22; record+256 = it, +268 = half the subject's +232. Key sp+120 looks at the centre from (key A's x / z,
// $f22). When it turns more than 30 degrees from key A (sub_2D1F30 > gp-32528) it is slerped back to 30 degrees and
// re-aimed from the centre + its view direction; when it turns less than 5 degrees (gp-32524) it is turned 30 degrees
// about the up axis (sub_4BDDE0). The distance $f23 = half of max(both widths + $f20, 450) / tan(1.2 * fov / 2); then
// the same shoulder choice and side-point re-aim as sub_2B1060, the key's position = the centre (moved sideways by
// 0.21875 * $f23 * tan(1.2 * fov / 2)) + its view direction * $f23; sub_2A2290(record, A, B, 1), the lens 1.0.
void Cpu3::sub_2AF960() {
    enter(136);
    sp = addiu(sp, -384);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s2 = a0;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, kActUnit);
    lw(v0, v0, 56);  // the first target
    lw(s0, v0, kActUnit);
    sw(v0, a0, 280);
    a0 = addiu(sp, 80);
    a1 = addiu(s2, kCwKey);
    jal(0x2af9a4, rg::fn_sub_2A4470_002a4470);
    lwc1(F0, s1, 220);
    swc1(F0, sp, 264);
    lwc1(F1, s1, 132);
    lwc1(F0, s1, kUnitScale);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 268);
    lwc1(F0, s1, 228);
    swc1(F0, sp, 272);
    a0 = s0;
    a1 = s1;
    a2 = addiu(sp, 248);
    jal(0x2af9d8, rg::fn_sub_2802D0_002802d0);
    lwc1(F6, s1, kUnitScale);
    lwc1(F0, s1, kUnitHeight);
    mul_s(F1, F0, F6);
    lwc1(F5, gp, -32620);  // 0.15
    lwc1(F0, sp, 268);
    mtc1(zero, F3);
    adda_s(F3, F0);
    madd_s(F4, F5, F1);
    lwc1(F2, s0, kUnitScale);
    lwc1(F0, s0, kUnitHeight);
    mul_s(F1, F0, F2);
    lwc1(F0, sp, 252);
    adda_s(F3, F0);
    madd_s(F0, F5, F1);
    add_s(F22, F4, F0);
    lwc1(F1, s1, 232);
    lwc1(F0, s1, kUnitWidth);
    adda_s(F3, F1);
    madda_s(F0, F6);
    lwc1(F0, s0, kUnitWidth);
    madd_s(F20, F0, F2);
    sw(zero, sp, 252);
    sw(zero, sp, 268);
    lwc1(F1, s1, 220);
    lwc1(F0, sp, 248);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 328);
    lwc1(F0, s1, 224);
    sub_s(F0, F0, F3);
    swc1(F0, sp, 332);
    lwc1(F1, s1, 228);
    lwc1(F0, sp, 256);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 336);
    a0 = addiu(sp, 328);
    a1 = a0;
    jal(0x2afa74, rg::fn_sub_4C69F0_004c69f0);
    lif(v0, 0x3e80, F0);  // 0.25
    mul_s(F1, F0, F20);
    lwc1(F0, sp, 328);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 296);
    lwc1(F0, sp, 332);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 300);
    lwc1(F0, sp, 336);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 304);
    lwc1(F0, sp, 248);
    add_s(F0, F3, F0);
    swc1(F0, sp, 296);
    lwc1(F0, sp, 252);
    add_s(F0, F2, F0);
    swc1(F0, sp, 300);
    lwc1(F0, sp, 256);
    add_s(F0, F1, F0);
    swc1(F0, sp, 304);
    lif(v0, 0x3f00, F1);
    mul_s(F21, F1, F22);
    swc1(F21, sp, 300);
    a1 = addiu(sp, 344);
    ld(v0, sp, 80);
    lwc1(F0, sp, 88);
    sd(v0, sp, 344);
    swc1(F0, sp, 352);
    swc1(F22, sp, 348);
    lwc1(F0, s1, 232);
    mul_s(F0, F1, F0);
    swc1(F0, s2, 268);
    a2 = addiu(sp, 296);
    copy_vec3(sp, 296, s2, 256);
    a0 = addiu(sp, 120);
    a3 = lui(0x69);
    a3 = addiu(a3, 30848);
    jal(0x2afb34, rg::fn_sub_2A4690_002a4690);  // key sp+120 from sp+344 at sp+296
    lwc1(F2, s1, kUnitWidth);
    lwc1(F1, s1, kUnitScale);
    mtc1(zero, F0);
    adda_s(F0, F20);
    madda_s(F2, F1);
    lwc1(F1, s0, kUnitWidth);
    lwc1(F0, s0, kUnitScale);
    madd_s(F22, F1, F0);
    a0 = addiu(sp, 92);
    a1 = addiu(sp, 120);
    jal(0x2afb68, rg::fn_sub_2D1F30_002d1f30);
    lwc1(F1, gp, -32528);  // 30 degrees
    c_le_s(F0, F1);
    if (!cc()) {
        slerp_limited(0x2afb98, sp, 92, sp, 120, 144, 224, -32532, -32692);
        charge(28);
        view_dir(0x2afd44, 344, 224);
        add_vec(344, 344, 296);
        look_at(0x2afd90, 120, 344, 296);
    } else {
        charge(4);
        lwc1(F1, gp, -32524);  // 5 degrees
        c_lt_s(F0, F1);
        if (cc()) {
            charge(7);
            a0 = addiu(sp, 120);
            a1 = lui(0x69);
            a1 = addiu(a1, 30848);
            lwc1(F12, gp, -32520);  // 30
            a2 = li(2);
            jal(0x2afdc4, rg::fn_sub_4BDDE0_004bdde0);
        }
    }
    charge(6);
    lif(v0, 0x43e1, F0);  // 450
    max_lt(F22, F0);
    charge(39);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2afe00, s2, F1);
    lif(v0, 0x3f00, F1);
    mul_s(F1, F1, F22);
    div_s(F23, F1, F0);
    view_dir(0x2afe30, 344, 120);
    lwc1(F0, sp, 348);
    swc1(F0, sp, 332);
    a0 = addiu(sp, 328);
    a1 = a0;
    jal(0x2afe48, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F4, sp, 328);
    lwc1(F5, sp, 336);
    lwc1(F3, sp, 352);
    lwc1(F2, sp, 344);
    lwc1(F1, sp, 348);
    lwc1(F0, sp, 332);
    mula_s(F1, F0);
    mtc1(zero, F0);
    madda_s(F2, F4);
    madd_s(F20, F3, F5);
    c_lt_s(F20, F0);
    if (!cc()) {
        charge(9);
        lwc1(F1, s1, kUnitWidth);
        lwc1(F0, s1, kUnitScale);
        mul_s(F22, F1, F0);
        ld(v0, sp, 264);
        lwc1(F0, sp, 272);
        sd(v0, sp, 280);
        swc1(F0, sp, 288);
    } else {
        charge(7);
        lwc1(F1, s0, kUnitWidth);
        lwc1(F0, s0, kUnitScale);
        mul_s(F22, F1, F0);
        ld(v0, sp, 248);
        lwc1(F0, sp, 256);
        sd(v0, sp, 280);
        swc1(F0, sp, 288);
    }
    charge(40);
    lwc1(F0, sp, 248);
    mtc1(zero, F1);
    adda_s(F1, F0);
    madd_s(F3, F5, F22);
    swc1(F3, sp, 360);
    lwc1(F2, sp, 300);
    swc1(F2, sp, 364);
    lwc1(F0, sp, 256);
    adda_s(F1, F0);
    msub_s(F1, F4, F22);
    swc1(F1, sp, 368);
    lwc1(F0, sp, 296);
    sub_s(F0, F3, F0);
    swc1(F0, sp, 312);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 316);
    lwc1(F0, sp, 304);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 320);
    a0 = addiu(sp, 312);
    a1 = a0;
    jal(0x2aff1c, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F6, sp, 320);
    lwc1(F5, sp, 336);
    lwc1(F4, sp, 312);
    lwc1(F2, sp, 328);
    lwc1(F1, sp, 316);
    lwc1(F0, sp, 332);
    mula_s(F1, F0);
    mtc1(zero, F3);
    madda_s(F4, F2);
    madd_s(F2, F6, F5);
    abs_s(F1, F20);
    abs_s(F0, F2);
    c_le_s(F1, F0);
    bool keep = cc();
    if (!keep) {
        charge(3);
        c_eq_s(F3, F2);
        keep = cc();
    }
    if (!keep) {
        charge(3);
        c_eq_s(F3, F20);
        keep = cc();
    }
    if (!keep) {
        // re-aim from the better of the two side points
        charge(65);
        lwc1(F1, sp, 296);
        lwc1(F0, sp, 280);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 376);
        lwc1(F20, sp, 288);
        lwc1(F0, sp, 304);
        sub_s(F0, F0, F20);
        swc1(F0, sp, 380);
        a0 = addiu(sp, 376);
        jal(0x2affa0, rg::fn_sub_4C6AF0_004c6af0);
        mul_s(F0, F21, F0);
        div_s(F1, F0, F23);
        lwc1(F0, sp, 300);
        add_s(F0, F0, F1);
        swc1(F0, sp, 364);
        lwc1(F2, sp, 336);
        lwc1(F0, sp, 280);
        mtc1(zero, F1);
        adda_s(F1, F0);
        madd_s(F0, F2, F22);
        swc1(F0, sp, 360);
        lwc1(F0, sp, 328);
        adda_s(F1, F20);
        msub_s(F0, F0, F22);
        swc1(F0, sp, 368);
        look_at(0x2b0000, 192, 360, 296);
        a0 = addiu(sp, 92);
        a1 = addiu(sp, 192);
        jal(0x2b0010, rg::fn_sub_2D1F30_002d1f30);
        mov_s(F21, F0);
        lwc1(F2, sp, 336);
        lwc1(F0, sp, 280);
        mtc1(zero, F1);
        adda_s(F1, F0);
        msub_s(F0, F2, F22);
        swc1(F0, sp, 360);
        lwc1(F0, sp, 328);
        adda_s(F1, F20);
        madd_s(F0, F0, F22);
        swc1(F0, sp, 368);
        look_at(0x2b005c, 208, 360, 296);
        a0 = addiu(sp, 92);
        a1 = addiu(sp, 208);
        jal(0x2b006c, rg::fn_sub_2D1F30_002d1f30);
        c_lt_s(F21, F0);
        if (cc()) {
            charge(10);
            copy_vec4(sp, 192, sp, 120);
        } else {
            charge(8);
            copy_vec4(sp, 208, sp, 120);
        }
        charge(7);
        view_dir(0x2b00dc, 344, 120);
    }
    charge(74);
    for (s32 k = 0; k < 12; k += 4) {
        lwc1(F0, sp, 344 + k);
        mul_s(F0, F0, F23);
        swc1(F0, sp, 344 + k);
    }
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b0120, s2, F1);
    mul_s(F1, F23, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 344);
    swc1(F0, sp, 376);
    lwc1(F0, sp, 352);
    swc1(F0, sp, 380);
    a0 = addiu(sp, 376);
    a1 = a0;
    jal(0x2b0154, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 380);
    lwc1(F0, sp, 296);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, F20);
    swc1(F3, sp, 296);
    lwc1(F1, sp, 376);
    lwc1(F0, sp, 304);
    adda_s(F2, F0);
    msub_s(F2, F1, F20);
    swc1(F2, sp, 304);
    lwc1(F0, sp, 344);
    add_s(F0, F3, F0);
    swc1(F0, sp, 108);
    lwc1(F1, sp, 300);
    lwc1(F0, sp, 348);
    add_s(F0, F1, F0);
    swc1(F0, sp, 112);
    lwc1(F0, sp, 352);
    add_s(F0, F2, F0);
    swc1(F0, sp, 116);
    a0 = s2;
    a1 = addiu(sp, 80);
    a2 = addiu(sp, 108);
    a3 = li(1);
    jal(0x2b01c4, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x3f80, F12);  // 1.0
    a0 = s2;
    jal(0x2b01d8, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 384);
}

// 0x2B0280 sub_2B0280(record, a1 = the target to frame (0 = the first target's unit), a2 = keep the side; $f12 = the
// turn limit in degrees): table row 11's init (sub_2B1020) and the boss band's sub_2E7210 call it: the shot of a unit
// acting on its first target. Key A (sp+144) = the current key. The subject's position sp+352 and the target's sp+336
// (sub_27FFB0), the target at least 125 high and $f20 = its y + half its height; the direction target -> subject
// (sp+288, length $f21) and the point 0.35 (gp-32616) of it from the target (sp+304); the side $f22 = the cross product
// of the current key's horizontal direction from that point with the line (sub_4C6B20). Over the subject's shoulder
// when the camera is on its side (or a2 == 1) and a1 is 0: the eye at the subject (2.5 widths sideways, away from the
// camera side; raised by 85 for a party unit whose held weapon type (sub_3093A0 of its DatUnit, when +164 == 3 or
// sub_2D5BF0) is 2 and sub_2A32F0 says 0), its height lifted by 0.3 / 0.05 of the target's height (the target below /
// above 400) and half the subject's height; key B (sp+184) looks from it at sp+304; the distance (sub_2D1FD0 + 2 *
// width) / tan(1.2 * fov / 2) back along the view, moved 2 widths sideways. Else over the target's shoulder: the
// midpoint, the target's point 1.25 widths sideways, at the higher of its height and the subject's y, distance
// (sub_2D1FD0 + 1.5 width) / tan(1.2 * fov / 2), at least 550, moved half a width. Then with $f12 > 0 and the turn from
// A (sub_2D1F30) within $f12 degrees (gp-32508): A follows B (both at least 25 high), sub_2A3E80(subject, a1 + 4, B,
// 51; $f12 = max(widths)) and the lens 1.25 or 0.85 * $f12 / turn (gp-32604), at most 1.25. Otherwise: on the camera's
// side B is set at once (sub_2A2170) and the move starts 200 along its view direction; else the new key A' looks from
// the frame unit's side point at sp+304 (0.6 of its height, gp-32572; 4 widths over tan back); both keys at least 25
// high, sub_2A2290(record, A, B, 1), the lens 1.15 (gp-32512), and sub_2A3E80(subject, a1 + 4, B, 3; $f12 =
// max(widths)).
void Cpu3::sub_2B0280() {
    enter(52);
    sp = addiu(sp, -368);
    sd(ra, sp, 128);
    sq(s4, sp, 112);
    sq(s3, sp, 96);
    sq(s2, sp, 80);
    sq(s1, sp, 64);
    sq(s0, sp, 48);
    swc1(F28, sp, 32);
    swc1(F27, sp, 28);
    swc1(F26, sp, 24);
    swc1(F25, sp, 20);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    mov_s(F26, F12);
    s2 = a1;
    s1 = a2;
    a0 = addiu(sp, 144);
    a1 = addiu(s0, kCwKey);
    jal(0x2b02d8, rg::fn_sub_2A4470_002a4470);
    lw(v0, s0, kCwSubject);
    lw(s4, v0, kActUnit);
    lw(v0, v0, 56);  // the first target
    lw(s3, v0, kActUnit);
    a0 = s4;
    a1 = addiu(sp, 352);
    jal(0x2b02f8, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s3;
    a1 = addiu(sp, 336);
    jal(0x2b0308, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F3, sp, 340);
    lwc1(F1, s3, kUnitHeight);
    lwc1(F0, s3, kUnitScale);
    mul_s(F2, F1, F0);
    lif(v0, 0x3f00, F1);
    mtc1(zero, F0);
    adda_s(F0, F3);
    madd_s(F20, F1, F2);
    lif(v0, 0x42fa, F0);  // 125
    c_lt_s(F3, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 340);
    }
    charge(66);
    lwc1(F1, s4, kUnitWidth);
    lwc1(F0, s4, kUnitScale);
    mul_s(F24, F1, F0);
    lwc1(F1, s3, kUnitWidth);
    lwc1(F0, s3, kUnitScale);
    mul_s(F23, F1, F0);
    sub_vec(288, 352, 336);
    a0 = addiu(sp, 288);
    a1 = a0;
    jal(0x2b03a4, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F21, F0);
    lwc1(F1, gp, -32616);  // 0.35
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 288);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 304);
    lwc1(F0, sp, 292);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 308);
    lwc1(F0, sp, 296);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 312);
    lwc1(F0, sp, 336);
    add_s(F2, F2, F0);
    swc1(F2, sp, 304);
    lwc1(F0, sp, 340);
    add_s(F0, F3, F0);
    swc1(F0, sp, 308);
    lwc1(F0, sp, 344);
    add_s(F1, F1, F0);
    swc1(F1, sp, 312);
    lwc1(F0, s0, kCwKey);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 216);
    lwc1(F0, s0, kCwKey + 8);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 220);
    a0 = addiu(sp, 216);
    a1 = a0;
    jal(0x2b0420, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 288);
    swc1(F1, sp, 208);
    lwc1(F0, sp, 296);
    swc1(F0, sp, 212);
    lwc1(F3, sp, 216);
    lwc1(F2, sp, 220);
    mula_s(F0, F2);
    mtc1(zero, F2);
    madd_s(F22, F1, F3);
    c_lt_s(F22, F2);
    bool target_side = false;
    if (cc()) {
        charge(3);
        v0 = li(1);
        target_side = s1 != v0;
    }
    if (!target_side) {
        charge(2);
        target_side = s2 != 0;
    }
    if (!target_side) {
        // over the subject's shoulder
        charge(16);
        s1 = s4;
        s2 = s3;
        ld(v0, sp, 352);
        lwc1(F0, sp, 360);
        sd(v0, sp, 320);
        swc1(F0, sp, 328);
        lwc1(F1, s4, kUnitWidth);
        lwc1(F0, s4, kUnitScale);
        mul_s(F1, F1, F0);
        lif(v0, 0x4020, F0);  // 2.5
        mul_s(F27, F0, F1);
        lbu(v0, s4, 162);
        bool raised = false;
        if (v0 == 0) {
            charge(4);
            lhu(v1, s4, 164);
            v0 = li(3);
            bool armed = v1 == v0;
            if (!armed) {
                charge(5);
                a0 = s4;
                jal(0x2b04c4, rg::fn_sub_2D5BF0_002d5bf0);
                armed = v0 != 0;
            }
            if (armed) {
                charge(7);
                lw(a0, s4, 2604);  // its DatUnit
                jal(0x2b04d8, rg::fn_sub_3093A0_003093a0);
                v1 = v0 & 0xff;
                v0 = li(2);
                if (v1 == v0) {
                    charge(5);
                    a0 = s0;
                    jal(0x2b04f4, rg::fn_sub_2A32F0_002a32f0);
                    raised = v0 == 0;
                }
            }
        }
        if (raised) {
            charge(4);
            lif(v0, 0x42aa, F5);  // 85
        } else {
            charge(1);
            mtc1(zero, F5);
        }
        charge(6);
        lif(v0, 0x43c8, F0);  // 400
        c_le_s(F20, F0);
        if (cc()) {
            charge(12);
            lwc1(F1, s3, kUnitHeight);
            lwc1(F0, s3, kUnitScale);
            mul_s(F3, F1, F0);
            lwc1(F2, gp, -32628);  // 0.3
            lwc1(F1, sp, 308);
            mtc1(zero, F0);
            adda_s(F0, F1);
            madd_s(F0, F2, F3);
            swc1(F0, sp, 308);
        } else {
            charge(10);
            lwc1(F1, s3, kUnitHeight);
            lwc1(F0, s3, kUnitScale);
            mul_s(F3, F1, F0);
            lwc1(F2, gp, -32660);  // 0.05
            lwc1(F1, sp, 308);
            mtc1(zero, F0);
            adda_s(F0, F1);
            madd_s(F0, F2, F3);
            swc1(F0, sp, 308);
        }
        charge(23);
        lwc1(F4, sp, 296);
        swc1(F4, sp, 208);
        lwc1(F3, sp, 288);
        neg_s(F2, F3);
        swc1(F2, sp, 212);
        lwc1(F1, sp, 216);
        lwc1(F0, sp, 220);
        mula_s(F2, F0);
        mtc1(zero, F2);
        madd_s(F25, F4, F1);
        lwc1(F20, sp, 324);
        add_s(F28, F5, F20);
        lwc1(F1, s4, kUnitHeight);
        lwc1(F0, s4, kUnitScale);
        mul_s(F1, F1, F0);
        lif(v0, 0x3f00, F0);
        adda_s(F2, F28);
        madd_s(F0, F0, F1);
        swc1(F0, sp, 276);
        c_lt_s(F25, F2);
        if (!cc()) {
            charge(10);
            lwc1(F0, sp, 320);
            adda_s(F2, F0);
            madd_s(F0, F4, F27);
            swc1(F0, sp, 272);
            lwc1(F21, sp, 328);
            adda_s(F2, F21);
            msub_s(F0, F3, F27);
            swc1(F0, sp, 280);
        } else {
            charge(12);
            lwc1(F0, sp, 320);
            adda_s(F2, F0);
            msub_s(F0, F4, F27);
            swc1(F0, sp, 272);
            lwc1(F21, sp, 328);
            adda_s(F2, F21);
            madd_s(F0, F3, F27);
            swc1(F0, sp, 280);
            ld(v0, sp, 288);
            lwc1(F0, sp, 296);
            sd(v0, sp, 256);
            swc1(F0, sp, 264);
        }
        charge(76);
        look_at(0x2b0650, 184, 272, 304);
        view_dir(0x2b066c, 288, 184);
        horizontal_distance(0x2b06b0);
        lwc1(F1, s4, kUnitWidth);
        lwc1(F4, s4, kUnitScale);
        mul_s(F3, F1, F4);
        lif(v0, 0x4000, F1);  // 2.0
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F27, F1, F3);
        lwc1(F0, sp, 240);
        swc1(F0, sp, 272);
        lwc1(F0, s4, kUnitHeight);
        mul_s(F1, F0, F4);
        lif(v0, 0x3e80, F0);  // 0.25
        adda_s(F2, F28);
        madd_s(F0, F0, F1);
        swc1(F0, sp, 276);
        lwc1(F0, sp, 244);
        swc1(F0, sp, 280);
        lwc1(F28, gp, kGpFovScale);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s0, kCwFov);
        mul_s(F0, F1, F0);
        mul_s(F12, F28, F0);
        jal(0x2b0720, rg::fn_tanf_0052e930);
        div_s(F1, F27, F0);
        scale_by(288, F1);
        mtc1(zero, F3);
        c_lt_s(F25, F3);
        if (cc()) {
            charge(17);
            lwc1(F1, s4, kUnitWidth);
            lwc1(F0, s4, kUnitScale);
            mul_s(F1, F1, F0);
            lif(v0, 0x4000, F0);
            mul_s(F2, F0, F1);
            lwc1(F1, sp, 264);
            lwc1(F0, sp, 272);
            adda_s(F3, F0);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 272);
            lwc1(F1, sp, 256);
            lwc1(F0, sp, 280);
            adda_s(F3, F0);
            msub_s(F0, F1, F2);
            swc1(F0, sp, 280);
        }
        charge(14);
        add_vec(172, 272, 288);
    } else {
        // over the target's shoulder
        charge(48);
        s1 = s3;
        s2 = s4;
        lif(v0, 0x3f00, F2);
        mul_s(F3, F2, F21);
        lwc1(F7, sp, 288);
        mul_s(F6, F7, F3);
        swc1(F6, sp, 304);
        lwc1(F2, sp, 292);
        mul_s(F4, F2, F3);
        swc1(F4, sp, 308);
        lwc1(F5, sp, 296);
        mul_s(F3, F5, F3);
        swc1(F3, sp, 312);
        lwc1(F2, sp, 336);
        add_s(F2, F6, F2);
        swc1(F2, sp, 304);
        lwc1(F2, sp, 340);
        add_s(F2, F4, F2);
        swc1(F2, sp, 308);
        lwc1(F2, sp, 344);
        add_s(F2, F3, F2);
        swc1(F2, sp, 312);
        ld(v0, sp, 336);
        lwc1(F2, sp, 344);
        sd(v0, sp, 320);
        swc1(F2, sp, 328);
        lwc1(F3, s3, kUnitWidth);
        lwc1(F2, s3, kUnitScale);
        mul_s(F3, F3, F2);
        lif(v0, 0x3fa0, F2);  // 1.25
        mul_s(F6, F2, F3);
        swc1(F5, sp, 208);
        neg_s(F4, F7);
        swc1(F4, sp, 212);
        lwc1(F3, sp, 216);
        lwc1(F2, sp, 220);
        mula_s(F4, F2);
        madd_s(F25, F5, F3);
        lwc1(F20, sp, 324);
        swc1(F20, sp, 276);
        lwc1(F2, sp, 356);
        c_lt_s(F20, F2);
        if (cc()) {
            charge(1);
            swc1(F2, sp, 276);
        }
        charge(5);
        mtc1(zero, F3);
        c_lt_s(F25, F3);
        if (!cc()) {
            charge(14);
            lwc1(F2, sp, 320);
            adda_s(F3, F2);
            madd_s(F0, F0, F6);
            swc1(F0, sp, 272);
            lwc1(F21, sp, 328);
            adda_s(F3, F21);
            msub_s(F0, F1, F6);
            swc1(F0, sp, 280);
            ld(v0, sp, 288);
            lwc1(F0, sp, 296);
            sd(v0, sp, 256);
            swc1(F0, sp, 264);
        } else {
            charge(8);
            lwc1(F2, sp, 320);
            adda_s(F3, F2);
            msub_s(F0, F0, F6);
            swc1(F0, sp, 272);
            lwc1(F21, sp, 328);
            adda_s(F3, F21);
            madd_s(F0, F1, F6);
            swc1(F0, sp, 280);
        }
        charge(63);
        look_at(0x2b092c, 184, 272, 304);
        view_dir(0x2b0948, 288, 184);
        horizontal_distance(0x2b098c);
        lwc1(F2, s3, kUnitWidth);
        lwc1(F1, s3, kUnitScale);
        mul_s(F3, F2, F1);
        lif(v0, 0x3fc0, F2);  // 1.5
        mtc1(zero, F1);
        adda_s(F1, F0);
        madd_s(F27, F2, F3);
        lwc1(F0, sp, 240);
        swc1(F0, sp, 272);
        swc1(F20, sp, 276);
        lwc1(F0, sp, 244);
        swc1(F0, sp, 280);
        lwc1(F28, gp, kGpFovScale);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s0, kCwFov);
        mul_s(F0, F1, F0);
        mul_s(F12, F28, F0);
        jal(0x2b09e4, rg::fn_tanf_0052e930);
        div_s(F1, F27, F0);
        v0 = li(550);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        max_lt(F1, F0);
        charge(14);
        scale_by(288, F1);
        mtc1(zero, F3);
        c_lt_s(F25, F3);
        if (!cc()) {
            charge(17);
            lwc1(F1, s3, kUnitWidth);
            lwc1(F0, s3, kUnitScale);
            mul_s(F1, F1, F0);
            lif(v0, 0x3f00, F0);
            mul_s(F2, F0, F1);
            lwc1(F1, sp, 264);
            lwc1(F0, sp, 272);
            adda_s(F3, F0);
            msub_s(F0, F1, F2);
            swc1(F0, sp, 272);
            lwc1(F1, sp, 256);
            lwc1(F0, sp, 280);
            adda_s(F3, F0);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 280);
        }
        charge(12);
        add_vec(172, 272, 288);
    }
    charge(9);
    a0 = addiu(sp, 156);
    a1 = addiu(sp, 184);
    jal(0x2b0acc, rg::fn_sub_2D1F30_002d1f30);
    mtc1(zero, F1);
    c_le_s(F26, F1);
    bool small_turn = false;
    if (!cc()) {
        charge(5);
        lwc1(F1, gp, -32508);  // degrees -> radians
        mul_s(F26, F1, F26);
        c_le_s(F0, F26);
        small_turn = cc();
    }
    if (!small_turn) {
        charge(5);
        mtc1(zero, F0);
        c_lt_s(F22, F0);
        if (cc()) {
            // the camera's side: B at once, the move from 200 along its view direction
            charge(46);
            a0 = s0;
            a1 = addiu(sp, 172);
            jal(0x2b0b18, rg::fn_sub_2A2170_002a2170);
            view_dir(0x2b0b34, 288, 184);
            lif(v0, 0x4348, F1);  // 200
            scale_add(288, F1, 172, 144);
            copy_vec4(sp, 184, sp, 156);
            lwc1(F1, sp, 148);
            at_least_25(148);
            charge(7);
            lwc1(F1, sp, 176);
            at_least_25(176);
            charge(12);
            a0 = s0;
            a1 = addiu(sp, 144);
            a2 = addiu(sp, 172);
            a3 = li(1);
            jal(0x2b0bfc, rg::fn_sub_2A2290_002a2290);
            a0 = s0;
            lwc1(F12, gp, -32512);  // 1.15
            jal(0x2b0c0c, rg::fn_sub_2A3110_002a3110);
        } else {
            // key A' from the frame unit's side point
            charge(31);
            lwc1(F1, s1, kUnitWidth);
            lwc1(F0, s1, kUnitScale);
            mul_s(F22, F1, F0);
            sub_vec(288, 352, 336);
            a0 = addiu(sp, 288);
            a1 = a0;
            jal(0x2b0c60, rg::fn_sub_4C69F0_004c69f0);
            lwc1(F1, s1, kUnitHeight);
            lwc1(F0, s1, kUnitScale);
            mul_s(F1, F1, F0);
            lwc1(F0, gp, -32572);  // 0.6
            mtc1(zero, F2);
            adda_s(F2, F20);
            madd_s(F0, F0, F1);
            swc1(F0, sp, 276);
            c_lt_s(F25, F2);
            if (!cc()) {
                charge(11);
                lwc1(F1, sp, 296);
                lwc1(F0, sp, 320);
                adda_s(F2, F0);
                msub_s(F0, F1, F22);
                swc1(F0, sp, 272);
                lwc1(F0, sp, 288);
                adda_s(F2, F21);
                madd_s(F0, F0, F22);
                swc1(F0, sp, 280);
            } else {
                charge(9);
                lwc1(F1, sp, 296);
                lwc1(F0, sp, 320);
                adda_s(F2, F0);
                madd_s(F0, F1, F22);
                swc1(F0, sp, 272);
                lwc1(F0, sp, 288);
                adda_s(F2, F21);
                msub_s(F0, F0, F22);
                swc1(F0, sp, 280);
            }
            charge(83);
            look_at(0x2b0cfc, 156, 272, 304);
            view_dir(0x2b0d18, 288, 156);
            horizontal_distance(0x2b0d5c);
            lwc1(F0, sp, 240);
            swc1(F0, sp, 272);
            lwc1(F1, s1, kUnitHeight);
            lwc1(F0, s1, kUnitScale);
            mul_s(F2, F1, F0);
            lwc1(F1, gp, -32572);
            mtc1(zero, F0);
            adda_s(F0, F20);
            madd_s(F0, F1, F2);
            swc1(F0, sp, 276);
            lwc1(F0, sp, 244);
            swc1(F0, sp, 280);
            lif(v0, 0x3f00, F1);
            lwc1(F0, s0, kCwFov);
            mul_s(F0, F1, F0);
            mul_s(F12, F28, F0);
            jal(0x2b0dac, rg::fn_tanf_0052e930);
            lwc1(F2, s1, kUnitWidth);
            lwc1(F1, s1, kUnitScale);
            mul_s(F2, F2, F1);
            lif(v0, 0x4080, F1);  // 4.0
            mul_s(F1, F1, F2);
            div_s(F2, F1, F0);
            lwc1(F0, sp, 288);
            mul_s(F3, F0, F2);
            swc1(F3, sp, 288);
            lwc1(F0, sp, 292);
            mul_s(F1, F0, F2);
            swc1(F1, sp, 292);
            lwc1(F0, sp, 296);
            mul_s(F2, F0, F2);
            swc1(F2, sp, 296);
            lwc1(F0, sp, 272);
            add_s(F0, F0, F3);
            swc1(F0, sp, 144);
            lwc1(F0, sp, 276);
            add_s(F1, F0, F1);
            swc1(F1, sp, 148);
            lwc1(F0, sp, 280);
            add_s(F0, F0, F2);
            swc1(F0, sp, 152);
            at_least_25(148);
            charge(7);
            lwc1(F1, sp, 176);
            at_least_25(176);
            charge(10);
            a0 = s0;
            a1 = addiu(sp, 144);
            a2 = addiu(sp, 172);
            a3 = li(1);
            jal(0x2b0e68, rg::fn_sub_2A2290_002a2290);
            a0 = s0;
            lwc1(F12, gp, -32512);  // 1.15
            jal(0x2b0e78, rg::fn_sub_2A3110_002a3110);
        }
        charge(3);
        max_le(F24, F23);
        charge(9);
        lw(a0, s0, kCwSubject);
        a1 = addiu(s2, 4);
        a2 = addiu(sp, 172);
        mov_s(F12, F24);
        a3 = li(3);
        jal(0x2b0eac, rg::fn_sub_2A3E80_002a3e80);
    } else {
        // a small turn: A follows B
        charge(3);
        max_le(F24, F23);
        charge(14);
        lw(a0, s0, kCwSubject);
        a1 = addiu(s2, 4);
        a2 = addiu(sp, 172);
        mov_s(F12, F24);
        a3 = li(51);
        jal(0x2b0ee8, rg::fn_sub_2A3E80_002a3e80);
        lwc1(F1, sp, 148);
        at_least_25(148);
        charge(7);
        lwc1(F1, sp, 176);
        at_least_25(176);
        charge(11);
        a0 = addiu(sp, 156);
        a1 = addiu(sp, 184);
        jal(0x2b0f38, rg::fn_sub_2D1F30_002d1f30);
        lif(v0, 0x3fa0, F20);  // 1.25
        mtc1(zero, F1);
        c_le_s(F0, F1);
        if (!cc()) {
            charge(9);
            div_s(F1, F26, F0);
            lif(v0, 0x3f80, F0);
            c_le_s(F1, F0);
            if (!cc()) {
                charge(4);
                lwc1(F0, gp, -32604);  // 0.85
                mul_s(F20, F1, F0);
            } else {
                charge(1);
                lwc1(F20, gp, -32604);
            }
            charge(6);
            lif(v0, 0x3fa0, F0);
            c_le_s(F20, F0);
            if (!cc()) {
                charge(1);
                mov_s(F20, F0);
            }
        }
        charge(10);
        a0 = s0;
        a1 = addiu(sp, 144);
        a2 = addiu(sp, 172);
        a3 = li(1);
        jal(0x2b0fc0, rg::fn_sub_2A2290_002a2290);
        a0 = s0;
        mov_s(F12, F20);
        jal(0x2b0fd0, rg::fn_sub_2A3110_002a3110);
    }
    charge(18);
    ld(ra, sp, 128);
    lq(s4, sp, 112);
    lq(s3, sp, 96);
    lq(s2, sp, 80);
    lq(s1, sp, 64);
    lq(s0, sp, 48);
    lwc1(F28, sp, 32);
    lwc1(F27, sp, 28);
    lwc1(F26, sp, 24);
    lwc1(F25, sp, 20);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 368);
}

// 0x2B1060 sub_2B1060(record; $f12 = the turn in degrees, $f13 = the lens): a turned two-shot of the subject and its
// first target. Key A = the current key. The subject's point +220 / +228 at its +132 * scale height (sp+296), the
// target's position (sub_27FFB0, sp+280); the height $f20 from 0.15 of both heights, $f22 = the subject's +232 + both
// widths. The centre sp+328: a quarter of $f22 from the target toward the subject, at half $f20; record+256 = it, +268
// = half the subject's +232. The current key's offset from the centre turned by $f12 about the up axis (negated on the
// other side of the line: the 2D cross product, sub_4C6B20) gives the eye; key sp+136 looks from it at the centre. The
// distance $f23 = half of max($f22, 400) / tan(1.2 * fov / 2). Then the nearer unit (by the sign of the dot product of
// the view direction with the horizontal subject-target direction) picks the shoulder point sp+312 and width; when the
// shot looks along the line (|dot| greater than the other point's, and neither dot zero) the key is re-aimed from the
// better (smaller turn, sub_2D1F30 against key A's rotation sp+108) of the two side points (+/- the width across the
// line, raised by the centre height * distance over the horizontal distance, sub_4C6AF0). The key's position = the
// centre (moved sideways by 0.21875 * $f23 * tan(1.2 * fov / 2)) + its view direction * $f23; sub_2A2290(record, A, B,
// 1), the lens sub_2A3110(record, $f13).
void Cpu3::sub_2B1060() {
    enter(151);
    sp = addiu(sp, -416);
    sd(ra, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s2 = a0;
    mov_s(F23, F12);
    mov_s(F24, F13);
    lw(v0, a0, kCwSubject);
    lw(s0, v0, kActUnit);
    lw(v0, v0, 56);  // the first target
    lw(s1, v0, kActUnit);
    a0 = addiu(sp, 96);
    a1 = addiu(s2, kCwKey);
    jal(0x2b10ac, rg::fn_sub_2A4470_002a4470);
    lwc1(F0, s0, 220);
    swc1(F0, sp, 296);
    lwc1(F1, s0, 132);
    lwc1(F0, s0, kUnitScale);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 300);
    lwc1(F0, s0, 228);
    swc1(F0, sp, 304);
    a0 = s1;
    a1 = addiu(sp, 280);
    jal(0x2b10dc, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F6, s0, kUnitScale);
    lwc1(F0, s0, kUnitHeight);
    mul_s(F1, F0, F6);
    lwc1(F5, gp, -32620);  // 0.15
    lwc1(F0, sp, 300);
    mtc1(zero, F3);
    adda_s(F3, F0);
    madd_s(F4, F5, F1);
    lwc1(F2, s1, kUnitScale);
    lwc1(F0, s1, kUnitHeight);
    mul_s(F1, F0, F2);
    lwc1(F0, sp, 284);
    adda_s(F3, F0);
    madd_s(F0, F5, F1);
    add_s(F20, F4, F0);
    lwc1(F1, s0, 232);
    lwc1(F0, s0, kUnitWidth);
    adda_s(F3, F1);
    madda_s(F0, F6);
    lwc1(F0, s1, kUnitWidth);
    madd_s(F22, F0, F2);
    sw(zero, sp, 284);
    sw(zero, sp, 300);
    lwc1(F1, s0, 220);
    lwc1(F0, sp, 280);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 360);
    lwc1(F0, s0, 224);
    sub_s(F0, F0, F3);
    swc1(F0, sp, 364);
    lwc1(F1, s0, 228);
    lwc1(F0, sp, 288);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 368);
    a0 = addiu(sp, 360);
    a1 = a0;
    jal(0x2b1178, rg::fn_sub_4C69F0_004c69f0);
    lif(v0, 0x3e80, F0);  // 0.25
    mul_s(F1, F0, F22);
    lwc1(F0, sp, 360);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 328);
    lwc1(F0, sp, 364);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 332);
    lwc1(F0, sp, 368);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 336);
    lwc1(F0, sp, 280);
    add_s(F0, F3, F0);
    swc1(F0, sp, 328);
    lwc1(F0, sp, 284);
    add_s(F0, F2, F0);
    swc1(F0, sp, 332);
    lwc1(F0, sp, 288);
    add_s(F0, F1, F0);
    swc1(F0, sp, 336);
    lif(v0, 0x3f00, F1);
    mul_s(F21, F1, F20);
    swc1(F21, sp, 332);
    lwc1(F0, s0, 232);
    mul_s(F0, F1, F0);
    swc1(F0, s2, 268);
    copy_vec3(sp, 328, s2, 256);
    lwc1(F0, sp, 368);
    swc1(F0, sp, 256);
    lwc1(F0, sp, 360);
    neg_s(F0, F0);
    swc1(F0, sp, 260);
    lwc1(F1, sp, 96);
    lwc1(F0, sp, 328);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 264);
    lwc1(F1, sp, 104);
    lwc1(F0, sp, 336);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 268);
    a0 = addiu(sp, 256);
    a1 = a0;
    jal(0x2b124c, rg::fn_sub_4C6B20_004c6b20);
    a0 = addiu(sp, 264);
    a1 = a0;
    jal(0x2b125c, rg::fn_sub_4C6B20_004c6b20);
    sub_vec(376, 96, 328);
    lwc1(F3, sp, 256);
    lwc1(F2, sp, 264);
    lwc1(F1, sp, 260);
    lwc1(F0, sp, 268);
    mula_s(F1, F0);
    mtc1(zero, F0);
    madd_s(F1, F3, F2);
    c_lt_s(F1, F0);
    if (!cc()) {
        charge(9);
        a0 = addiu(sp, 160);
        a1 = lui(0x69);
        a1 = addiu(a1, 30848);
        mov_s(F12, F23);
        a2 = 0;
        jal(0x2b12d0, rg::fn_sub_4C31B0_004c31b0);
    } else {
        charge(7);
        neg_s(F12, F23);
        a0 = addiu(sp, 160);
        a1 = lui(0x69);
        a1 = addiu(a1, 30848);
        a2 = 0;
        jal(0x2b12f4, rg::fn_sub_4C31B0_004c31b0);
    }
    charge(30);
    a0 = addiu(sp, 376);
    a1 = a0;
    a2 = addiu(sp, 160);
    jal(0x2b1308, rg::fn_sub_4C6C60_004c6c60);
    add_vec(376, 376, 328);
    look_at(0x2b1354, 136, 376, 328);
    lif(v0, 0x43c8, F0);  // 400
    max_lt(F22, F0);
    charge(39);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b1390, s2, F1);
    lif(v0, 0x3f00, F1);
    mul_s(F1, F1, F22);
    div_s(F23, F1, F0);
    view_dir(0x2b13c0, 376, 136);
    lwc1(F0, sp, 380);
    swc1(F0, sp, 364);
    a0 = addiu(sp, 360);
    a1 = a0;
    jal(0x2b13d8, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F4, sp, 360);
    lwc1(F5, sp, 368);
    lwc1(F3, sp, 384);
    lwc1(F2, sp, 376);
    lwc1(F1, sp, 380);
    lwc1(F0, sp, 364);
    mula_s(F1, F0);
    mtc1(zero, F0);
    madda_s(F2, F4);
    madd_s(F20, F3, F5);
    c_lt_s(F20, F0);
    if (!cc()) {
        // looking from the subject's side: the subject's shoulder
        charge(9);
        lwc1(F1, s0, kUnitWidth);
        lwc1(F0, s0, kUnitScale);
        mul_s(F22, F1, F0);
        ld(v0, sp, 296);
        lwc1(F0, sp, 304);
        sd(v0, sp, 312);
        swc1(F0, sp, 320);
    } else {
        charge(7);
        lwc1(F1, s1, kUnitWidth);
        lwc1(F0, s1, kUnitScale);
        mul_s(F22, F1, F0);
        ld(v0, sp, 280);
        lwc1(F0, sp, 288);
        sd(v0, sp, 312);
        swc1(F0, sp, 320);
    }
    charge(40);
    lwc1(F0, sp, 280);
    mtc1(zero, F1);
    adda_s(F1, F0);
    madd_s(F3, F5, F22);
    swc1(F3, sp, 392);
    lwc1(F2, sp, 332);
    swc1(F2, sp, 396);
    lwc1(F0, sp, 288);
    adda_s(F1, F0);
    msub_s(F1, F4, F22);
    swc1(F1, sp, 400);
    lwc1(F0, sp, 328);
    sub_s(F0, F3, F0);
    swc1(F0, sp, 344);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 348);
    lwc1(F0, sp, 336);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 352);
    a0 = addiu(sp, 344);
    a1 = a0;
    jal(0x2b14ac, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F6, sp, 352);
    lwc1(F5, sp, 368);
    lwc1(F4, sp, 344);
    lwc1(F2, sp, 360);
    lwc1(F1, sp, 348);
    lwc1(F0, sp, 364);
    mula_s(F1, F0);
    mtc1(zero, F3);
    madda_s(F4, F2);
    madd_s(F2, F6, F5);
    abs_s(F1, F20);
    abs_s(F0, F2);
    c_le_s(F1, F0);
    bool keep = cc();
    if (!keep) {
        charge(3);
        c_eq_s(F3, F2);
        keep = cc();
    }
    if (!keep) {
        charge(3);
        c_eq_s(F3, F20);
        keep = cc();
    }
    if (!keep) {
        // re-aim from the better of the two side points
        charge(65);
        lwc1(F1, sp, 328);
        lwc1(F0, sp, 312);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 408);
        lwc1(F20, sp, 320);
        lwc1(F0, sp, 336);
        sub_s(F0, F0, F20);
        swc1(F0, sp, 412);
        a0 = addiu(sp, 408);
        jal(0x2b1530, rg::fn_sub_4C6AF0_004c6af0);
        mul_s(F0, F21, F0);
        div_s(F1, F0, F23);
        lwc1(F0, sp, 332);
        add_s(F0, F0, F1);
        swc1(F0, sp, 396);
        lwc1(F2, sp, 368);
        lwc1(F0, sp, 312);
        mtc1(zero, F1);
        adda_s(F1, F0);
        madd_s(F0, F2, F22);
        swc1(F0, sp, 392);
        lwc1(F0, sp, 360);
        adda_s(F1, F20);
        msub_s(F0, F0, F22);
        swc1(F0, sp, 400);
        look_at(0x2b1590, 224, 392, 328);
        a0 = addiu(sp, 108);
        a1 = addiu(sp, 224);
        jal(0x2b15a0, rg::fn_sub_2D1F30_002d1f30);
        mov_s(F21, F0);
        lwc1(F2, sp, 368);
        lwc1(F0, sp, 312);
        mtc1(zero, F1);
        adda_s(F1, F0);
        msub_s(F0, F2, F22);
        swc1(F0, sp, 392);
        lwc1(F0, sp, 360);
        adda_s(F1, F20);
        madd_s(F0, F0, F22);
        swc1(F0, sp, 400);
        look_at(0x2b15ec, 240, 392, 328);
        a0 = addiu(sp, 108);
        a1 = addiu(sp, 240);
        jal(0x2b15fc, rg::fn_sub_2D1F30_002d1f30);
        c_lt_s(F21, F0);
        if (cc()) {
            charge(10);
            copy_vec4(sp, 224, sp, 136);
        } else {
            charge(8);
            copy_vec4(sp, 240, sp, 136);
        }
        charge(7);
        view_dir(0x2b166c, 376, 136);
    }
    charge(74);
    for (s32 k = 0; k < 12; k += 4) {
        lwc1(F0, sp, 376 + k);
        mul_s(F0, F0, F23);
        swc1(F0, sp, 376 + k);
    }
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b16b0, s2, F1);
    mul_s(F1, F23, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 376);
    swc1(F0, sp, 408);
    lwc1(F0, sp, 384);
    swc1(F0, sp, 412);
    a0 = addiu(sp, 408);
    a1 = a0;
    jal(0x2b16e4, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 412);
    lwc1(F0, sp, 328);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, F20);
    swc1(F3, sp, 328);
    lwc1(F1, sp, 408);
    lwc1(F0, sp, 336);
    adda_s(F2, F0);
    msub_s(F2, F1, F20);
    swc1(F2, sp, 336);
    lwc1(F0, sp, 376);
    add_s(F0, F3, F0);
    swc1(F0, sp, 124);
    lwc1(F1, sp, 332);
    lwc1(F0, sp, 380);
    add_s(F0, F1, F0);
    swc1(F0, sp, 128);
    lwc1(F0, sp, 384);
    add_s(F0, F2, F0);
    swc1(F0, sp, 132);
    a0 = s2;
    a1 = addiu(sp, 96);
    a2 = addiu(sp, 124);
    a3 = li(1);
    jal(0x2b1754, rg::fn_sub_2A2290_002a2290);
    a0 = s2;
    mov_s(F12, F24);
    jal(0x2b1764, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 416);
}

// 0x2B17A0 sub_2B17A0(record; $f12 = the sweep angle, $f13 = the lens): a four-key sweep around the subject and its
// first target. Key 0 = the record's current key (sub_2A4470). The subject's unit (record+224 -> +48) and the first
// target's (the action's +56 -> +48, its position by sub_27FFB0, y = 0). The centre: halfway (or 0.15, gp-32620, when
// the current key is on the other side: the sign of the 2D cross product of the two horizontal directions, normalised
// by sub_4C6B20) from the target to the subject's point +220..+228 (its y lowered by the subject's +132 * scale), at
// half of (+132 * scale + 0.15 * both heights); record+256..+264 = the centre, +268 = half the subject's +232. Keys
// 1..3: the current key's offset from the centre turned about the up axis by $f12 / 3, 2 * $f12 / 3, $f12 (negated on
// the other side; sub_4C31B0 / sub_4C6C60), looking at the centre. Then the spline sub_2A2660(record, keys 0..3, 1) and
// the lens sub_2A3110(record, $f13).
void Cpu3::sub_2B17A0() {
    enter(111);
    sp = addiu(sp, -368);
    sd(ra, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    mov_s(F24, F12);
    mov_s(F23, F13);
    lw(v0, a0, kCwSubject);
    lw(s0, v0, kActUnit);
    lw(v0, v0, 56);  // the first target
    lw(s2, v0, kActUnit);
    a0 = addiu(sp, 96);
    a1 = addiu(s1, kCwKey);
    jal(0x2b17ec, rg::fn_sub_2A4470_002a4470);
    lwc1(F1, s0, 132);
    lwc1(F0, s0, kUnitScale);
    mul_s(F20, F1, F0);
    a0 = s2;
    a1 = addiu(sp, 288);
    jal(0x2b1808, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s0, kUnitHeight);
    lwc1(F0, s0, kUnitScale);
    mul_s(F0, F1, F0);
    lwc1(F4, gp, -32620);  // 0.15
    mtc1(zero, F2);
    adda_s(F2, F20);
    madd_s(F3, F4, F0);
    lwc1(F1, s2, kUnitHeight);
    lwc1(F0, s2, kUnitScale);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 292);
    adda_s(F2, F0);
    madd_s(F0, F4, F1);
    add_s(F21, F3, F0);
    sw(zero, sp, 292);
    lwc1(F1, s0, 220);
    lwc1(F0, sp, 288);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 352);
    lwc1(F0, s0, 224);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 356);
    lwc1(F1, s0, 228);
    lwc1(F0, sp, 296);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 360);
    a0 = addiu(sp, 352);
    a1 = a0;
    jal(0x2b1884, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F20, F0);
    lif(v0, 0x3f00, F6);
    mul_s(F1, F6, F20);
    lwc1(F5, sp, 352);
    mul_s(F2, F5, F1);
    swc1(F2, sp, 336);
    lwc1(F0, sp, 356);
    mul_s(F4, F0, F1);
    swc1(F4, sp, 340);
    lwc1(F3, sp, 360);
    mul_s(F1, F3, F1);
    swc1(F1, sp, 344);
    lwc1(F0, sp, 288);
    add_s(F2, F2, F0);
    swc1(F2, sp, 336);
    lwc1(F0, sp, 292);
    add_s(F0, F4, F0);
    swc1(F0, sp, 340);
    lwc1(F0, sp, 296);
    add_s(F1, F1, F0);
    swc1(F1, sp, 344);
    mul_s(F21, F6, F21);
    swc1(F21, sp, 340);
    swc1(F3, sp, 272);
    neg_s(F0, F5);
    swc1(F0, sp, 276);
    lwc1(F0, sp, 96);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 280);
    lwc1(F0, sp, 104);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 284);
    a0 = addiu(sp, 272);
    a1 = a0;
    jal(0x2b191c, rg::fn_sub_4C6B20_004c6b20);
    a0 = addiu(sp, 280);
    a1 = a0;
    jal(0x2b192c, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F3, sp, 272);
    lwc1(F2, sp, 280);
    lwc1(F1, sp, 276);
    lwc1(F0, sp, 284);
    mula_s(F1, F0);
    mtc1(zero, F0);
    madd_s(F22, F3, F2);  // the side: the dot product of the normal with the key's direction
    c_lt_s(F22, F0);
    charge(13);
    if (!cc()) {
        lwc1(F0, gp, -32620);
        mul_s(F1, F0, F20);
    } else {
        lif(v0, 0x3f00, F0);
        mul_s(F1, F0, F20);
    }
    for (s32 k = 0; k < 12; k += 4) {
        lwc1(F0, sp, 352 + k);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 336 + k);
    }
    charge(45);
    add_vec(336, 336, 288);
    swc1(F21, sp, 340);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s0, 232);
    mul_s(F0, F1, F0);
    swc1(F0, s1, 268);
    copy_vec3(sp, 336, s1, 256);
    sub_vec(304, 96, 336);
    lif(v0, 0x4040, F0);  // 3.0
    div_s(F21, F24, F0);
    mov_s(F20, F21);
    s0 = dli(1);
    for (;;) {
        charge(4);
        v0 = s0 & 0xffff;
        v0 = slti(v0, 4);
        if (v0 == 0) break;
        backedge();
        charge(5);
        mtc1(zero, F0);
        c_lt_s(F22, F0);
        if (!cc()) {
            charge(9);
            a0 = addiu(sp, 208);
            a1 = lui(0x69);
            a1 = addiu(a1, 30848);
            mov_s(F12, F21);
            a2 = 0;
            jal(0x2b1aa0, rg::fn_sub_4C31B0_004c31b0);
        } else {
            charge(7);
            neg_s(F12, F21);
            a0 = addiu(sp, 208);
            a1 = lui(0x69);
            a1 = addiu(a1, 30848);
            a2 = 0;
            jal(0x2b1ac4, rg::fn_sub_4C31B0_004c31b0);
        }
        charge(32);
        a0 = addiu(sp, 320);
        a1 = addiu(sp, 304);
        a2 = addiu(sp, 208);
        jal(0x2b1ad8, rg::fn_sub_4C6C60_004c6c60);
        key_slot(s0);
        a1 = addiu(v0, 96);
        lwc1(F1, sp, 320);
        lwc1(F0, sp, 336);
        add_s(F0, F1, F0);
        swc1(F0, a1, 0);
        lwc1(F1, sp, 324);
        lwc1(F0, sp, 340);
        add_s(F0, F1, F0);
        swc1(F0, a1, 4);
        lwc1(F1, sp, 328);
        lwc1(F0, sp, 344);
        add_s(F0, F1, F0);
        swc1(F0, a1, 8);
        a0 = addiu(a1, 12);
        a2 = addiu(sp, 336);
        a3 = lui(0x69);
        a3 = addiu(a3, 30848);
        jal(0x2b1b38, rg::fn_sub_2A4690_002a4690);
        add_s(F21, F21, F20);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xffff;
    }
    charge(24);
    a0 = s1;
    a1 = addiu(sp, 96);
    a2 = addiu(sp, 124);
    a3 = addiu(sp, 152);
    t0 = addiu(sp, 180);
    t1 = li(1);
    jal(0x2b1b74, rg::fn_sub_2A2660_002a2660);
    a0 = s1;
    mov_s(F12, F23);
    jal(0x2b1b84, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 368);
}

// 0x2B21F0 sub_2B21F0(record, a1 = choose the sides anew; $f12 = the lens): a two-shot over the subject's or its first
// target's shoulder. Both units' points (sub_280130) -> sp+336 (subject) / sp+320 (target); their direction normalised
// (sp+272, the distance $f20). With a1 set, record+260 = which unit is nearer the camera (gBtl+12 bit 21 forces 0),
// from the sign of the 2D cross product with the current key's horizontal direction (normalised by sub_4C6B20); +260 ==
// 1: over the subject's shoulder (the subject's point, at least 100 high, is the near unit; the far unit framed at 0.35
// of the distance, gp-32616; width factors 1.25 / 1.35, gp-32612), else over the target's (lowered by a quarter of its
// height, at least 100; a quarter of the way; 0.35 / 2.5). The near unit's point is pushed sideways by the width factor
// on the side record+264 chooses (the same cross-product test with the reversed direction, again only with a1 set). Key
// sp+184 looks from there at the far point; the distance: sub_2D1FD0 of the horizontal points + width * factor, over
// tan(1.2 * fov / 2), at least 500; the key's position = the near point (its y the record's +260 height) + view
// direction * distance (y at least 12.5). Key A = the current key; with a1, sub_2A3E80(subject, far unit + 4, B, mode;
// $f12 = 50) with mode 3 when the turn exceeds 45 degrees (sub_2D1F30 > gp-32556; A is then moved to B at once by
// sub_2A44F0), else 35. sub_2A2290(record, A, B, 1), the lens sub_2A3110(record, $f12).
void Cpu3::sub_2B21F0() {
    enter(69);
    sp = addiu(sp, -352);
    sd(ra, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;
    mov_s(F24, F12);
    s3 = a1;
    lw(v0, a0, kCwSubject);
    lw(s2, v0, kActUnit);
    lw(v0, v0, 56);  // the first target
    lw(s1, v0, kActUnit);
    a0 = s2;
    a1 = addiu(sp, 336);
    jal(0x2b2248, rg::fn_sub_280130_00280130);
    a0 = s1;
    a1 = addiu(sp, 320);
    jal(0x2b2258, rg::fn_sub_280130_00280130);
    sub_vec(272, 336, 320);
    a0 = addiu(sp, 272);
    a1 = a0;
    jal(0x2b2298, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F20, F0);
    lwc1(F1, s4, kCwKey);
    lwc1(F0, sp, 336);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 216);
    lwc1(F1, s4, kCwKey + 8);
    lwc1(F0, sp, 344);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 220);
    a0 = addiu(sp, 216);
    a1 = a0;
    jal(0x2b22cc, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F3, sp, 272);
    swc1(F3, sp, 208);
    lwc1(F2, sp, 280);
    swc1(F2, sp, 212);
    lwc1(F1, sp, 216);
    lwc1(F0, sp, 220);
    mula_s(F2, F0);
    mtc1(zero, F0);
    madd_s(F1, F3, F1);
    if (s3 != 0) {
        charge(6);
        gbtl(v0);
        lw(v1, v0, btl_task::kFlags);
        v0 = lui(0x20);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(3);
            sw(zero, s4, 260);
        } else {
            side_flag(s4, 260);
        }
    }
    charge(4);
    lw(v1, s4, 260);
    v0 = li(1);
    if (v1 == v0) {
        // over the subject's shoulder
        charge(32);
        s0 = s2;
        s5 = s1;
        ld(v0, sp, 336);
        lwc1(F0, sp, 344);
        sd(v0, sp, 304);
        swc1(F0, sp, 312);
        lwc1(F1, s2, kUnitWidth);
        lwc1(F0, s2, kUnitScale);
        mul_s(F1, F1, F0);
        lif(v0, 0x3fa0, F0);  // 1.25
        mul_s(F23, F0, F1);
        lwc1(F22, gp, -32612);  // 1.35
        lwc1(F0, gp, -32616);   // 0.35
        mul_s(F1, F0, F20);
        lwc1(F2, sp, 272);
        mul_s(F0, F2, F1);
        swc1(F0, sp, 288);
        lwc1(F0, sp, 276);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 292);
        lwc1(F3, sp, 280);
        mul_s(F0, F3, F1);
        swc1(F0, sp, 296);
        lwc1(F1, sp, 308);
        lif(v0, 0x42c8, F0);  // 100
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, 308);
        }
        charge(4);
        lwc1(F20, sp, 308);
        swc1(F20, sp, 260);
    } else {
        // over the target's shoulder
        charge(29);
        s0 = s1;
        s5 = s2;
        ld(v0, sp, 320);
        lwc1(F0, sp, 328);
        sd(v0, sp, 304);
        swc1(F0, sp, 312);
        lwc1(F2, s1, kUnitScale);
        lwc1(F0, s1, kUnitWidth);
        mul_s(F1, F0, F2);
        lwc1(F0, gp, -32616);  // 0.35
        mul_s(F23, F0, F1);
        lif(v0, 0x4020, F22);  // 2.5
        lwc1(F0, s1, kUnitHeight);
        mul_s(F3, F0, F2);
        lif(v0, 0x3e80, F2);  // 0.25
        lwc1(F1, sp, 340);
        mtc1(zero, F0);
        adda_s(F0, F1);
        msub_s(F1, F2, F3);
        swc1(F1, sp, 340);
        lif(v0, 0x42c8, F0);  // 100
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, sp, 340);
        }
        charge(31);
        sub_vec(272, 336, 320);
        a0 = addiu(sp, 272);
        a1 = a0;
        jal(0x2b2494, rg::fn_sub_4C69F0_004c69f0);
        lif(v0, 0x3e80, F1);
        mul_s(F1, F1, F0);
        lwc1(F2, sp, 272);
        mul_s(F0, F2, F1);
        swc1(F0, sp, 288);
        lwc1(F0, sp, 276);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 292);
        lwc1(F3, sp, 280);
        mul_s(F0, F3, F1);
        swc1(F0, sp, 296);
        lwc1(F20, sp, 308);
        swc1(F20, sp, 260);
    }
    charge(23);
    add_vec(288, 288, 320);
    swc1(F3, sp, 208);
    neg_s(F2, F2);
    swc1(F2, sp, 212);
    lwc1(F1, sp, 216);
    lwc1(F0, sp, 220);
    mula_s(F2, F0);
    mtc1(zero, F0);
    madd_s(F1, F3, F1);
    if (s3 != 0) {
        charge(4);
        c_lt_s(F1, F0);
        v0 = li(1);
        if (cc()) {
            charge(1);
            v0 = 0;
        }
        charge(1);
        sw(v0, s4, 264);
    }
    charge(4);
    lw(v1, s4, 264);
    v0 = li(1);
    if (v1 == v0) {
        charge(14);
        lwc1(F2, sp, 280);
        lwc1(F0, sp, 304);
        mtc1(zero, F1);
        adda_s(F1, F0);
        madd_s(F0, F2, F23);
        swc1(F0, sp, 256);
        lwc1(F21, sp, 312);
        lwc1(F0, sp, 272);
        adda_s(F1, F21);
        msub_s(F0, F0, F23);
        swc1(F0, sp, 264);
    } else {
        charge(12);
        lwc1(F2, sp, 280);
        lwc1(F0, sp, 304);
        mtc1(zero, F1);
        adda_s(F1, F0);
        msub_s(F0, F2, F23);
        swc1(F0, sp, 256);
        lwc1(F21, sp, 312);
        lwc1(F0, sp, 272);
        adda_s(F1, F21);
        madd_s(F0, F0, F23);
        swc1(F0, sp, 264);
    }
    charge(60);
    look_at(0x2b25d8, 184, 256, 288);
    view_dir(0x2b25f4, 272, 184);
    lwc1(F0, sp, 288);
    swc1(F0, sp, 224);
    lwc1(F0, sp, 296);
    swc1(F0, sp, 228);
    lwc1(F0, sp, 256);
    swc1(F0, sp, 232);
    lwc1(F0, sp, 264);
    swc1(F0, sp, 236);
    lwc1(F0, sp, 304);
    swc1(F0, sp, 248);
    swc1(F21, sp, 252);
    a0 = addiu(sp, 224);
    a1 = addiu(sp, 232);
    a2 = addiu(sp, 248);
    a3 = addiu(sp, 240);
    jal(0x2b2638, rg::fn_sub_2D1FD0_002d1fd0);
    lwc1(F2, s0, kUnitWidth);
    lwc1(F1, s0, kUnitScale);
    mul_s(F2, F2, F1);
    mtc1(zero, F1);
    adda_s(F1, F0);
    madd_s(F21, F22, F2);
    lwc1(F0, sp, 240);
    swc1(F0, sp, 256);
    swc1(F20, sp, 260);
    lwc1(F0, sp, 244);
    swc1(F0, sp, 264);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b2688, s4, F1);
    div_s(F2, F21, F0);
    lif(v0, 0x43fa, F0);  // 500
    max_lt(F2, F0);
    charge(24);
    lwc1(F0, sp, 272);
    mul_s(F3, F0, F2);
    swc1(F3, sp, 272);
    lwc1(F0, sp, 276);
    mul_s(F1, F0, F2);
    swc1(F1, sp, 276);
    lwc1(F0, sp, 280);
    mul_s(F2, F0, F2);
    swc1(F2, sp, 280);
    lwc1(F0, sp, 256);
    add_s(F0, F0, F3);
    swc1(F0, sp, 172);
    lwc1(F0, sp, 260);
    add_s(F1, F0, F1);
    swc1(F1, sp, 176);
    lwc1(F0, sp, 264);
    add_s(F0, F0, F2);
    swc1(F0, sp, 180);
    lif(v0, 0x4148, F0);  // 12.5
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 176);
    }
    charge(6);
    a0 = addiu(sp, 144);
    a1 = addiu(s4, kCwKey);
    jal(0x2b2724, rg::fn_sub_2A4470_002a4470);
    if (s3 != 0) {
        charge(8);
        a0 = addiu(sp, 156);
        a1 = addiu(sp, 184);
        jal(0x2b273c, rg::fn_sub_2D1F30_002d1f30);
        lwc1(F1, gp, -32556);  // pi/4
        c_le_s(F0, F1);
        if (!cc()) {
            charge(7);
            a0 = addiu(sp, 144);
            a1 = addiu(sp, 172);
            jal(0x2b275c, rg::fn_sub_2A44F0_002a44f0);
            a3 = dli(3);
        } else {
            charge(1);
            a3 = dli(35);
        }
        charge(7);
        lif(v0, 0x4248, F12);  // 50
        lw(a0, s4, kCwSubject);
        a1 = addiu(s5, 4);
        a2 = addiu(sp, 172);
        jal(0x2b2788, rg::fn_sub_2A3E80_002a3e80);
    }
    charge(25);
    a0 = s4;
    a1 = addiu(sp, 144);
    a2 = addiu(sp, 172);
    a3 = li(1);
    jal(0x2b27a0, rg::fn_sub_2A2290_002a2290);
    a0 = s4;
    mov_s(F12, F24);
    jal(0x2b27b0, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 352);
}

// 0x2B2940 sub_2B2940(record): table row 14's init, a two-shot of the subject and its first target. The target's
// position sp+240 and the subject's sp+224 (sub_27FFB0), their heights adjusted (the higher one lowered by 0.15 of its
// height, the other raised by 0.05 / 0.15; gp-32620 / gp-32660), the target's at least 65. The midpoint 0.4 (gp-32632)
// of the way from the target to the subject -> sp+192. The sideways offset: the target's side direction (0x697870
// rotated by its quaternion) times half its width (the subject a party unit: +162 == 0) or 1.5 width, placed on the
// side away from the current key (the sign of the 2D cross product with the key's direction from the target, normalised
// by sub_4C6B20). Key sp+108 looks from target - / + it (sp+208) at the midpoint; the distance: sub_2D1FD0 of the two
// horizontal points plus max(width, 100) (party) / max(width, 125), at least 160, over tan(1.2 * fov / 2), plus
// |midpoint - eye| (sub_4C6AC0), at least 0. The key's position = midpoint + its view direction * distance (y at least
// 25); sub_2A3E80(subject, key, midpoint, 3; $f12 = 400) and the key set at once (sub_2A2170).
void Cpu3::sub_2B2940() {
    enter(30);
    sp = addiu(sp, -256);
    sd(ra, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s2 = a0;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, kActUnit);
    lbu(s0, s1, 162);
    lw(v0, v0, 56);  // the first target
    lw(s3, v0, kActUnit);
    lwc1(F1, s3, kUnitWidth);
    lwc1(F0, s3, kUnitScale);
    mul_s(F21, F1, F0);
    a0 = s3;
    a1 = addiu(sp, 240);
    jal(0x2b298c, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s1;
    a1 = addiu(sp, 224);
    jal(0x2b299c, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F5, sp, 244);
    lwc1(F4, sp, 228);
    c_le_s(F5, F4);
    if (!cc()) {
        // the target is higher: it is lowered by 0.15 of its height, the subject raised by 0.05 of its own
        charge(18);
        lwc1(F1, s3, kUnitHeight);
        lwc1(F0, s3, kUnitScale);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32620);
        mtc1(zero, F2);
        adda_s(F2, F5);
        msub_s(F0, F0, F1);
        swc1(F0, sp, 244);
        lwc1(F1, s1, kUnitHeight);
        lwc1(F0, s1, kUnitScale);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32660);
        adda_s(F2, F4);
        madd_s(F0, F0, F1);
        swc1(F0, sp, 228);
    } else {
        charge(15);
        lwc1(F1, s3, kUnitHeight);
        lwc1(F0, s3, kUnitScale);
        mul_s(F0, F1, F0);
        lwc1(F3, gp, -32620);
        mtc1(zero, F2);
        adda_s(F2, F5);
        madd_s(F0, F3, F0);
        swc1(F0, sp, 244);
        lwc1(F1, s1, kUnitHeight);
        lwc1(F0, s1, kUnitScale);
        mul_s(F0, F1, F0);
        adda_s(F2, F4);
        msub_s(F0, F3, F0);
        swc1(F0, sp, 228);
    }
    charge(7);
    lwc1(F1, sp, 244);
    lif(v0, 0x4282, F0);  // 65
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 244);
    }
    charge(65);
    lwc1(F7, sp, 240);
    lwc1(F0, sp, 224);
    sub_s(F6, F0, F7);
    swc1(F6, sp, 176);
    lwc1(F5, sp, 244);
    lwc1(F0, sp, 228);
    sub_s(F2, F0, F5);
    swc1(F2, sp, 180);
    lwc1(F4, sp, 248);
    lwc1(F0, sp, 232);
    sub_s(F3, F0, F4);
    swc1(F3, sp, 184);
    lwc1(F1, gp, -32632);  // 0.4
    mul_s(F0, F6, F1);
    swc1(F0, sp, 176);
    mul_s(F2, F2, F1);
    swc1(F2, sp, 180);
    mul_s(F1, F3, F1);
    swc1(F1, sp, 184);
    add_s(F0, F7, F0);
    swc1(F0, sp, 192);
    add_s(F0, F5, F2);
    swc1(F0, sp, 196);
    add_s(F0, F4, F1);
    swc1(F0, sp, 200);
    lwc1(F0, s2, kCwKey);
    sub_s(F1, F7, F0);
    swc1(F1, sp, 176);
    lwc1(F0, s2, kCwKey + 4);
    sub_s(F0, F5, F0);
    swc1(F0, sp, 180);
    lwc1(F0, s2, kCwKey + 8);
    sub_s(F0, F4, F0);
    swc1(F0, sp, 184);
    swc1(F1, sp, 152);
    swc1(F0, sp, 156);
    a0 = addiu(sp, 152);
    a1 = a0;
    jal(0x2b2af4, rg::fn_sub_4C6B20_004c6b20);
    a0 = addiu(sp, 176);
    a1 = lui(0x69);
    a1 = addiu(a1, 30832);
    a2 = li(1);
    a3 = addiu(s3, kUnitRot);
    jal(0x2b2b10, rg::fn_sub_4BE1E0_004be1e0);
    lwc1(F0, sp, 176);
    swc1(F0, sp, 144);
    lwc1(F0, sp, 184);
    swc1(F0, sp, 148);
    a0 = addiu(sp, 144);
    a1 = a0;
    jal(0x2b2b30, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F3, sp, 144);
    lwc1(F2, sp, 152);
    lwc1(F1, sp, 148);
    lwc1(F0, sp, 156);
    mula_s(F1, F0);
    mtc1(zero, F4);
    madd_s(F5, F3, F2);
    s0 = s0 & 0xffff;
    if (s0 == 0) {
        charge(24);
        lif(v0, 0x3f00, F0);
        mul_s(F1, F0, F21);
        scale_sub(176, F1, 240, 208);
    } else {
        charge(16);
        lif(v0, 0x3fc0, F0);  // 1.5
        mul_s(F1, F0, F21);
        lwc1(F0, sp, 176);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 176);
        lwc1(F0, sp, 180);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 180);
        lwc1(F0, sp, 184);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 184);
        c_lt_s(F5, F4);
        if (cc()) {
            charge(11);
            lwc1(F0, sp, 240);
            add_s(F0, F0, F3);
            swc1(F0, sp, 208);
            lwc1(F0, sp, 244);
            add_s(F0, F0, F2);
            swc1(F0, sp, 212);
            lwc1(F0, sp, 248);
            add_s(F0, F0, F1);
            swc1(F0, sp, 216);
        } else {
            charge(9);
            lwc1(F0, sp, 240);
            sub_s(F0, F0, F3);
            swc1(F0, sp, 208);
            lwc1(F0, sp, 244);
            sub_s(F0, F0, F2);
            swc1(F0, sp, 212);
            lwc1(F0, sp, 248);
            sub_s(F0, F0, F1);
            swc1(F0, sp, 216);
        }
    }
    charge(28);
    look_at(0x2b2c64, 108, 208, 192);
    lwc1(F0, sp, 192);
    swc1(F0, sp, 128);
    lwc1(F0, sp, 200);
    swc1(F0, sp, 132);
    lwc1(F0, sp, 208);
    swc1(F0, sp, 136);
    lwc1(F0, sp, 216);
    swc1(F0, sp, 140);
    lwc1(F0, sp, 240);
    swc1(F0, sp, 168);
    lwc1(F0, sp, 248);
    swc1(F0, sp, 172);
    a0 = addiu(sp, 128);
    a1 = addiu(sp, 136);
    a2 = addiu(sp, 168);
    a3 = 0;
    jal(0x2b2cac, rg::fn_sub_2D1FD0_002d1fd0);
    mov_s(F20, F0);
    if (s0 == 0) {
        charge(6);
        lif(v0, 0x42c8, F0);  // 100
        max_le(F21, F0);
        charge(3);
        add_s(F20, F20, F21);
    } else {
        charge(6);
        lif(v0, 0x42fa, F0);  // 125
        max_le(F21, F0);
        charge(1);
        add_s(F20, F20, F21);
    }
    charge(6);
    lif(v0, 0x4320, F0);  // 160
    max_lt(F20, F0);
    charge(33);
    sub_vec(176, 192, 208);
    a0 = addiu(sp, 176);
    jal(0x2b2d68, rg::fn_sub_4C6AC0_004c6ac0);
    mov_s(F21, F0);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b2d8c, s2, F1);
    div_s(F0, F20, F0);
    add_s(F20, F21, F0);
    mtc1(zero, F0);
    max_le(F20, F0);
    charge(31);
    view_dir(0x2b2dd8, 176, 108);
    lwc1(F0, sp, 176);
    mul_s(F3, F0, F20);
    swc1(F3, sp, 176);
    lwc1(F0, sp, 180);
    mul_s(F1, F0, F20);
    swc1(F1, sp, 180);
    lwc1(F0, sp, 184);
    mul_s(F2, F0, F20);
    swc1(F2, sp, 184);
    lwc1(F0, sp, 192);
    add_s(F0, F0, F3);
    swc1(F0, sp, 96);
    lwc1(F0, sp, 196);
    add_s(F1, F0, F1);
    swc1(F1, sp, 100);
    lwc1(F0, sp, 200);
    add_s(F0, F0, F2);
    swc1(F0, sp, 104);
    lif(v0, 0x41c8, F0);  // 25
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 100);
    }
    charge(22);
    lif(v0, 0x43c8, F12);  // 400
    lw(a0, s2, kCwSubject);
    a1 = addiu(sp, 96);
    a2 = addiu(sp, 192);
    a3 = li(3);
    jal(0x2b2e5c, rg::fn_sub_2A3E80_002a3e80);
    a0 = s2;
    a1 = addiu(sp, 96);
    jal(0x2b2e6c, rg::fn_sub_2A2170_002a2170);
    ld(ra, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 256);
}

// 0x2B2EB0 sub_2B2EB0(record, key): table row 30's init (sub_2B32C0) calls it: a key over the enemy side turned at most
// 45 degrees away from the record's current rotation. The enemy side's extent (sub_280870(3, 1, sp+136, sp+188, sp+184,
// 1) -> $f20): the distance $f21 = $f20 / tan(1.2 * fov / 2); the key's rotation (key + 12) looks from (0, high y,
// -$f20) at the side's centre sp+136. When sub_2D1F30(record + 168, key + 12) (the angle between the two rotations)
// exceeds pi/4 (gp-32556), the rotation is slerped from the record's toward it by t = (pi/4) / angle (sub_4BE310 sets
// up the slerp at sp+64: two quaternions, the angle +96, a no-sine flag +100; sin() is the inline Taylor series of
// gp-32492 / gp-32696..-32680) and the key re-aimed from centre + its view direction. The distance is at least 700; the
// key's position = the centre + its view direction * the distance, moved sideways by 0.21875 * distance * tan(1.2 * fov
// / 2) (the horizontal view direction normalised by sub_4C6B20, rotated a quarter turn).
void Cpu3::sub_2B2EB0() {
    enter(48);
    sp = addiu(sp, -192);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = li(3);
    a1 = li(1);
    a2 = addiu(sp, 136);
    a3 = addiu(sp, 188);
    t0 = addiu(sp, 184);
    t1 = a1;
    jal(0x2b2ee8, rg::fn_sub_280870_00280870);
    mov_s(F20, F0);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b2f0c, s1, F1);
    div_s(F21, F20, F0);
    sw(zero, sp, 168);
    lwc1(F0, sp, 188);
    swc1(F0, sp, 172);
    neg_s(F0, F20);
    swc1(F0, sp, 176);
    a0 = addiu(s0, 12);
    a1 = addiu(sp, 168);
    a2 = addiu(sp, 136);
    a3 = lui(0x69);
    a3 = addiu(a3, 30848);
    jal(0x2b2f48, rg::fn_sub_2A4690_002a4690);
    a0 = addiu(s1, 168);
    a1 = addiu(s0, 12);
    jal(0x2b2f58, rg::fn_sub_2D1F30_002d1f30);
    lwc1(F1, gp, -32556);  // pi/4
    c_le_s(F0, F1);
    if (!cc()) {
        slerp_limited(0x2b2f88, s1, 168, s0, 12, 64, 112, -32492, -32488);
        charge(26);
        view_dir(0x2b3134, 152, 112);
        add_vec(168, 136, 152);
        a0 = addiu(s0, 12);
        a1 = addiu(sp, 168);
        a2 = addiu(sp, 136);
        a3 = lui(0x69);
        a3 = addiu(a3, 30848);
        jal(0x2b3180, rg::fn_sub_2A4690_002a4690);
    }
    charge(6);
    lif(v0, 0x442f, F0);  // 700
    c_lt_s(F21, F0);
    if (cc()) {
        charge(1);
        mov_s(F21, F0);
    }
    charge(68);
    a0 = addiu(sp, 152);
    a1 = lui(0x69);
    a1 = addiu(a1, 30880);
    a2 = li(1);
    a3 = addiu(s0, 12);
    jal(0x2b31b8, rg::fn_sub_4BE1E0_004be1e0);
    lwc1(F0, sp, 152);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 152);
    lwc1(F0, sp, 156);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 156);
    lwc1(F0, sp, 160);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 160);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b31fc, s1, F1);
    mul_s(F1, F21, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 152);
    swc1(F0, sp, 128);
    lwc1(F0, sp, 160);
    swc1(F0, sp, 132);
    a0 = addiu(sp, 128);
    a1 = a0;
    jal(0x2b3230, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 132);
    lwc1(F0, sp, 136);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, F20);
    swc1(F3, sp, 136);
    lwc1(F1, sp, 128);
    lwc1(F0, sp, 144);
    adda_s(F2, F0);
    msub_s(F0, F1, F20);
    swc1(F0, sp, 144);
    lwc1(F0, sp, 152);
    add_s(F0, F3, F0);
    swc1(F0, s0, 0);
    lwc1(F1, sp, 140);
    lwc1(F0, sp, 156);
    add_s(F0, F1, F0);
    swc1(F0, s0, 4);
    lwc1(F1, sp, 144);
    lwc1(F0, sp, 160);
    add_s(F0, F1, F0);
    swc1(F0, s0, 8);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 192);
}

// 0x2B3340 sub_2B3340(record): table row 31's init, the camera behind the subject looking at the enemy side. The
// subject's unit (record+224, or gBtl+328's when none); the enemy side's centre sp+128 and high y sp+140 (sub_280870(3,
// 1, sp+128, sp+140, 0, 1) -> $f20 the extent); the unit's position on the ground (sub_280050, y = 0; the current
// actor's when it stands exactly over the centre). The eye: the centre + (position - centre) normalised * $f20, at the
// height max(0.75 * the unit's height, 0.6 * the side's high y (gp-32572)); the key sp+76 looks from the eye at the
// centre. The distance: max(0.75 * $f20 / tan(1.2 * fov / 2), |eye - centre| + 2 * the unit's width / tan(1.2 * fov /
// 2)); the key's position = the centre + (eye - centre) normalised * the distance, through sub_2A3590. Then
// sub_2A3E80(0, 0, 0, 64; $f12 = 0), the key set at once (sub_2A2170) and the record's key copied (sub_2A44B0(record +
// 156, key)).
void Cpu3::sub_2B3340() {
    enter(10);
    sp = addiu(sp, -144);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    lw(v0, a0, kCwSubject);
    if (v0 != 0) {
        charge(3);
        lw(s0, v0, kActUnit);
    } else {
        charge(3);
        gbtl(v0);
        lw(v0, v0, 328);
        lw(s0, v0, kActUnit);
    }
    charge(20);
    a0 = li(3);
    a1 = li(1);
    a2 = addiu(sp, 128);
    a3 = addiu(sp, 140);
    t0 = 0;
    t1 = a1;
    jal(0x2b3398, rg::fn_sub_280870_00280870);
    mov_s(F20, F0);
    a0 = s0;
    a1 = addiu(sp, 112);
    jal(0x2b33ac, rg::fn_sub_280050_00280050);
    sw(zero, sp, 132);
    sw(zero, sp, 116);
    lwc1(F1, sp, 112);
    lwc1(F0, sp, 128);
    c_eq_s(F1, F0);
    if (cc()) {
        charge(5);
        lwc1(F1, sp, 120);
        lwc1(F0, sp, 136);
        c_eq_s(F1, F0);
        if (cc()) {
            charge(7);
            gbtl(v0);
            lw(v0, v0, 328);
            lw(a0, v0, kActUnit);
            a1 = addiu(sp, 112);
            jal(0x2b33f4, rg::fn_sub_280050_00280050);
            sw(zero, sp, 116);
        }
    }
    charge(47);
    sub_vec(96, 112, 128);
    a0 = addiu(sp, 96);
    a1 = a0;
    jal(0x2b3438, rg::fn_sub_4C69F0_004c69f0);
    scale_add(96, F20, 128, 112);
    lwc1(F1, s0, kUnitHeight);
    lwc1(F0, s0, kUnitScale);
    mul_s(F1, F1, F0);
    lif(v0, 0x3f40, F0);  // 0.75
    mul_s(F2, F0, F1);
    lwc1(F1, gp, -32572);  // 0.6
    lwc1(F0, sp, 140);
    mul_s(F0, F1, F0);
    c_le_s(F0, F2);
    if (!cc()) {
        charge(2);
    } else {
        charge(1);
        mov_s(F0, F2);
    }
    charge(59);
    swc1(F0, sp, 116);
    look_at(0x2b34e0, 76, 112, 128);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b3500, s1, F1);
    lif(v0, 0x3f40, F1);
    mul_s(F1, F1, F20);
    div_s(F20, F1, F0);
    sub_vec(96, 112, 128);
    a0 = addiu(sp, 96);
    a1 = a0;
    jal(0x2b3554, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F21, F0);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b3578, s1, F1);
    lwc1(F2, s0, kUnitWidth);
    lwc1(F1, s0, kUnitScale);
    mul_s(F2, F2, F1);
    lif(v0, 0x4000, F1);  // 2.0
    mul_s(F1, F1, F2);
    div_s(F0, F1, F0);
    add_s(F0, F21, F0);
    c_le_s(F20, F0);
    if (!cc()) {
        charge(2);
    } else {
        charge(1);
        mov_s(F20, F0);
    }
    charge(45);
    lwc1(F0, sp, 96);
    mul_s(F3, F0, F20);
    swc1(F3, sp, 96);
    lwc1(F0, sp, 100);
    mul_s(F2, F0, F20);
    swc1(F2, sp, 100);
    lwc1(F0, sp, 104);
    mul_s(F1, F0, F20);
    swc1(F1, sp, 104);
    lwc1(F0, sp, 128);
    add_s(F0, F3, F0);
    swc1(F0, sp, 64);
    lwc1(F0, sp, 132);
    add_s(F0, F2, F0);
    swc1(F0, sp, 68);
    lwc1(F0, sp, 136);
    add_s(F0, F1, F0);
    swc1(F0, sp, 72);
    a0 = addiu(sp, 64);
    a1 = a0;
    jal(0x2b3610, rg::fn_sub_2A3590_002a3590);
    mtc1(zero, F12);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = li(64);
    jal(0x2b362c, rg::fn_sub_2A3E80_002a3e80);
    a0 = s1;
    a1 = addiu(sp, 64);
    jal(0x2b363c, rg::fn_sub_2A2170_002a2170);
    a0 = addiu(s1, kCwKey);
    a1 = addiu(sp, 64);
    jal(0x2b364c, rg::fn_sub_2A44B0_002a44b0);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 144);
}

// 0x2B3690 sub_2B3690(record): table row 2's init, a view of the whole battlefield from behind the party. The eye and
// target come from the side extents (sub_280870(3, 0, 0, sp+172, 0, 1) -> $f20, sub_280870(2, 0, sp+144, 0, 0, 1)) and
// the current actor's unit position (sub_280050; gBtl+328's unit): the target sp+144 (its y = half the extent sp+172),
// the eye the actor raised by 0.75 * its height; the key sp+76 looks from the eye at the target (rotated 30 degrees
// about the up axis with more than one party member, gBtl+2980 >= 2). The first key sits 250 / tan(fov / 2) along the
// view direction from the target, the second 0.875 * $f20 / tan(1.2 * fov / 2) (plus half the actor's height over
// tan(fov / 2) with exactly one party member); sub_2A2290(record, sp+64, sp+92, 1), the lens 1.725 (gp-32448).
void Cpu3::sub_2B3690() {
    enter(77);
    sp = addiu(sp, -176);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    gbtl(v0);
    lw(v0, v0, 328);
    lw(s0, v0, kActUnit);
    a0 = li(3);
    a1 = 0;
    a2 = 0;
    a3 = addiu(sp, 172);
    t0 = 0;
    t1 = li(1);
    jal(0x2b36d0, rg::fn_sub_280870_00280870);
    mov_s(F20, F0);
    a0 = li(2);
    a1 = 0;
    a2 = addiu(sp, 144);
    a3 = 0;
    t0 = 0;
    t1 = li(1);
    jal(0x2b36f4, rg::fn_sub_280870_00280870);
    lif(v0, 0x3f00, F1);  // 0.5
    lwc1(F0, sp, 172);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 148);
    a0 = s0;
    a1 = addiu(sp, 160);
    jal(0x2b3718, rg::fn_sub_280050_00280050);
    lwc1(F1, s0, kUnitHeight);
    lwc1(F0, s0, kUnitScale);
    mul_s(F3, F1, F0);
    lif(v0, 0x3f40, F2);  // 0.75
    lwc1(F1, sp, 164);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F3);
    swc1(F0, sp, 164);
    look_at(0x2b3760, 76, 160, 144);
    copy_vec4(sp, 76, sp, 104);
    lif(v0, 0x3f00, F1);
    tan_half_fov(0x2b3798, s1, F1);
    lif(v0, 0x437a, F1);  // 250.0
    div_s(F21, F1, F0);
    gbtl(v0);
    lbu(v0, v0, 2980);
    at = slti(v0, 2);
    if (at == 0) {
        charge(8);
        lif(v0, 0x41f0, F12);  // 30 degrees
        a0 = addiu(sp, 76);
        a1 = lui(0x69);
        a1 = addiu(a1, 30848);
        a2 = li(2);
        jal(0x2b37dc, rg::fn_sub_4BDDE0_004bdde0);
    }
    charge(43);
    view_dir(0x2b37f8, 128, 76);
    scale_add(128, F21, 144, 64);
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b3860, s1, F1);
    lif(v0, 0x3f60, F1);  // 0.875
    mul_s(F1, F1, F20);
    div_s(F20, F1, F0);
    gbtl(v0);
    lbu(v1, v0, 2980);
    v0 = li(1);
    if (v1 == v0) {
        charge(15);
        lif(v0, 0x3f00, F1);
        tan_half_fov(0x2b38a0, s1, F1);
        lwc1(F2, s0, kUnitHeight);
        lwc1(F1, s0, kUnitScale);
        mul_s(F2, F2, F1);
        lif(v0, 0x3f00, F1);
        mul_s(F1, F1, F2);
        div_s(F0, F1, F0);
        add_s(F20, F20, F0);
    }
    charge(43);
    view_dir(0x2b38e0, 128, 104);
    scale_add(128, F20, 144, 92);
    a0 = s1;
    a1 = addiu(sp, 64);
    a2 = addiu(sp, 92);
    a3 = li(1);
    jal(0x2b3940, rg::fn_sub_2A2290_002a2290);
    a0 = s1;
    lwc1(F12, gp, -32448);  // 1.725
    jal(0x2b3950, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 176);
}

// 0x2B3980 sub_2B3980(record): table row 32's init, four keys circling the subject. The subject's unit position
// (sub_27FFB0) raised by 0.2 * half its height (gp-32588); the distance 1.25 * (the larger of its width and half its
// height) / tan(fov / 2) (the width case with the 1.2 factor). A coin (datCalcRand(100) > 50) picks the turn: from -60
// degrees in steps of +30, or from +60 in steps of -30; each key: the unit's forward 0x697890 turned by the angle about
// the up axis (sub_4C31B0 / sub_4C6C60), rotated by the unit's quaternion, times the distance, added to the position ->
// the eye; the key looks from it at the position; the distance grows by 37.5 a step. Then sub_2A3E80(subject, 0, 0, 1;
// $f12 = 0), the spline sub_2A2660(record, the four keys, 1) and the lens 6.0.
void Cpu3::sub_2B3980() {
    enter(38);
    sp = addiu(sp, -352);
    sd(ra, sp, 96);
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
    s2 = a0;
    lw(v0, a0, kCwSubject);
    lw(s0, v0, kActUnit);
    a0 = s0;
    a1 = addiu(sp, 320);
    jal(0x2b39c4, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s0, kUnitScale);
    lwc1(F0, s0, kUnitWidth);
    mul_s(F20, F0, F1);
    lwc1(F0, s0, kUnitHeight);
    mul_s(F0, F0, F1);
    lif(v0, 0x3f00, F3);
    mul_s(F21, F3, F0);
    lwc1(F2, gp, -32588);  // 0.2
    lwc1(F1, sp, 324);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F21);
    swc1(F0, sp, 324);
    c_le_s(F20, F21);
    if (!cc()) {
        charge(16);
        lwc1(F0, s2, kCwFov);
        mul_s(F1, F3, F0);
        lwc1(F0, gp, kGpFovScale);
        mul_s(F12, F0, F1);
        jal(0x2b3a28, rg::fn_tanf_0052e930);
        lif(v0, 0x3fa0, F1);  // 1.25
        mul_s(F1, F1, F20);
        div_s(F25, F1, F0);
    } else {
        charge(9);
        tan_half_fov(0x2b3a60, s2, F3);
        lif(v0, 0x3fa0, F1);
        mul_s(F1, F1, F21);
        div_s(F25, F1, F0);
    }
    charge(6);
    a0 = li(100);
    jal(0x2b3a80, rg::fn_datCalcRand_002ffbc0);
    at = sltiu(v0, 51);
    if (at == 0) {
        charge(6);
        lif(v0, 0x4270, F24);  // 60
        lif(v0, 0xc1f0, F23);  // -30
    } else {
        charge(4);
        lif(v0, 0xc270, F24);  // -60
        lif(v0, 0x41f0, F23);  // 30
    }
    charge(3);
    s1 = 0;
    for (;;) {
        charge(4);
        v0 = s1 & 0xffff;
        v0 = slti(v0, 4);
        if (v0 == 0) break;
        backedge();
        charge(63);
        a0 = addiu(sp, 224);
        a1 = lui(0x69);
        a1 = addiu(a1, 30848);
        mov_s(F12, F24);
        a2 = 0;
        jal(0x2b3adc, rg::fn_sub_4C31B0_004c31b0);
        a0 = addiu(sp, 288);
        a1 = lui(0x69);
        a1 = addiu(a1, 30864);
        a2 = addiu(sp, 224);
        jal(0x2b3af4, rg::fn_sub_4C6C60_004c6c60);
        a0 = addiu(sp, 304);
        a1 = addiu(sp, 288);
        a2 = li(1);
        a3 = addiu(s0, kUnitRot);
        jal(0x2b3b0c, rg::fn_sub_4BE1E0_004be1e0);
        lwc1(F0, sp, 304);
        mul_s(F22, F0, F25);
        lwc1(F0, sp, 308);
        mul_s(F21, F0, F25);
        lwc1(F0, sp, 312);
        mul_s(F20, F0, F25);
        lwc1(F0, sp, 320);
        add_s(F0, F0, F22);
        swc1(F0, sp, 336);
        lwc1(F0, sp, 324);
        add_s(F0, F0, F21);
        swc1(F0, sp, 340);
        lwc1(F0, sp, 328);
        add_s(F0, F0, F20);
        swc1(F0, sp, 344);
        key_slot(s1);
        s3 = addiu(v0, 112);
        a0 = addiu(s3, 12);
        a1 = addiu(sp, 336);
        a2 = addiu(sp, 320);
        a3 = lui(0x69);
        a3 = addiu(a3, 30848);
        jal(0x2b3b7c, rg::fn_sub_2A4690_002a4690);
        lwc1(F0, sp, 320);
        add_s(F0, F0, F22);
        swc1(F0, s3, 0);
        lwc1(F0, sp, 324);
        add_s(F0, F0, F21);
        swc1(F0, s3, 4);
        lwc1(F0, sp, 328);
        add_s(F0, F0, F20);
        swc1(F0, s3, 8);
        add_s(F24, F24, F23);
        lif(v0, 0x4216, F0);  // 37.5
        add_s(F25, F25, F0);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xffff;
    }
    charge(34);
    mtc1(zero, F12);
    lw(a0, s2, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(0x2b3be8, rg::fn_sub_2A3E80_002a3e80);
    a0 = s2;
    a1 = addiu(sp, 112);
    a2 = addiu(sp, 140);
    a3 = addiu(sp, 168);
    t0 = addiu(sp, 196);
    t1 = li(1);
    jal(0x2b3c08, rg::fn_sub_2A2660_002a2660);
    lif(v0, 0x40c0, F12);  // 6.0
    a0 = s2;
    jal(0x2b3c1c, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 96);
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

// 0x2B3C60 sub_2B3C60(record): table row 33's init, four keys swinging down past the subject. The subject's position
// raised by 0.2 * half its height; the unit's forward (0x697890 rotated by its quaternion) times 350 -> sp+240, the
// direction from the position to that point lowered by 35 normalised -> sp+256; the distance: 1.75 * width / tan(1.2 *
// fov / 2), or 1.2 * half the height / tan(fov / 2) when the width is below half the height. Each key turns the
// direction about the up axis (from 65 degrees in steps of -25; sub_4C31B0 / sub_4C6C60 -> sp+240), the eye = position
// + it * distance (y at least 5), looks at the position; the distance grows by 25. Then sub_2A3E80(subject, 0, 0, 1;
// $f12 = 0), sub_2A2660(record, the four keys, 1) and the lens 10.0.
void Cpu3::sub_2B3C60() {
    enter(70);
    sp = addiu(sp, -288);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    lw(v0, a0, kCwSubject);
    lw(s0, v0, kActUnit);
    a0 = s0;
    a1 = addiu(sp, 272);
    jal(0x2b3c8c, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s0, kUnitScale);
    lwc1(F0, s0, kUnitWidth);
    mul_s(F21, F0, F1);
    lwc1(F0, s0, kUnitHeight);
    mul_s(F1, F0, F1);
    lif(v0, 0x3f00, F0);
    mul_s(F20, F0, F1);
    lwc1(F2, gp, -32588);  // 0.2
    lwc1(F1, sp, 276);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F20);
    swc1(F0, sp, 276);
    a0 = addiu(sp, 256);
    a1 = lui(0x69);
    a1 = addiu(a1, 30864);
    a2 = li(1);
    a3 = addiu(s0, kUnitRot);
    jal(0x2b3ce8, rg::fn_sub_4BE1E0_004be1e0);
    lif(v0, 0x43af, F2);  // 350
    lwc1(F0, sp, 256);
    mul_s(F5, F2, F0);
    swc1(F5, sp, 240);
    lwc1(F0, sp, 260);
    mul_s(F1, F2, F0);
    swc1(F1, sp, 244);
    lwc1(F0, sp, 264);
    mul_s(F4, F2, F0);
    swc1(F4, sp, 248);
    lwc1(F3, sp, 276);
    add_s(F1, F3, F1);
    lif(v0, 0x420c, F0);  // 35
    sub_s(F2, F1, F0);
    lwc1(F1, sp, 272);
    add_s(F0, F1, F5);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 256);
    sub_s(F0, F2, F3);
    swc1(F0, sp, 260);
    lwc1(F1, sp, 280);
    add_s(F0, F1, F4);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 264);
    a0 = addiu(sp, 256);
    a1 = a0;
    jal(0x2b3d64, rg::fn_sub_4C69F0_004c69f0);
    c_lt_s(F21, F20);
    if (!cc()) {
        charge(18);
        lif(v0, 0x3f00, F1);
        tan_half_fov12(0x2b3d90, s1, F1);
        lif(v0, 0x3fe0, F1);  // 1.75
        mul_s(F1, F1, F21);
        div_s(F21, F1, F0);
    } else {
        charge(9);
        lif(v0, 0x3f00, F1);
        tan_half_fov(0x2b3dd0, s1, F1);
        lwc1(F1, gp, kGpFovScale);
        mul_s(F1, F1, F20);
        div_s(F21, F1, F0);
    }
    charge(5);
    lif(v0, 0x4282, F20);  // 65
    s0 = 0;
    for (;;) {
        charge(4);
        v0 = s0 & 0xffff;
        v0 = slti(v0, 4);
        if (v0 == 0) break;
        backedge();
        charge(43);
        a0 = addiu(sp, 176);
        a1 = lui(0x69);
        a1 = addiu(a1, 30848);
        mov_s(F12, F20);
        a2 = 0;
        jal(0x2b3e0c, rg::fn_sub_4C31B0_004c31b0);
        a0 = addiu(sp, 240);
        a1 = addiu(sp, 256);
        a2 = addiu(sp, 176);
        jal(0x2b3e20, rg::fn_sub_4C6C60_004c6c60);
        key_slot(s0);
        v0 = addiu(v0, 64);
        lwc1(F1, sp, 240);
        lwc1(F0, sp, 272);
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F0, F1, F21);
        swc1(F0, v0, 0);
        v1 = addiu(v0, 4);
        lwc1(F1, sp, 244);
        lwc1(F0, sp, 276);
        adda_s(F2, F0);
        madd_s(F0, F1, F21);
        swc1(F0, v0, 4);
        lwc1(F1, sp, 248);
        lwc1(F0, sp, 280);
        adda_s(F2, F0);
        madd_s(F0, F1, F21);
        swc1(F0, v0, 8);
        lwc1(F1, v0, 4);
        lif(v0, 0x40a0, F0);  // 5.0
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            swc1(F0, v1, 0);
        }
        charge(22);
        key_slot(s0);
        a1 = addiu(v0, 64);
        a0 = addiu(a1, 12);
        a2 = addiu(sp, 272);
        a3 = lui(0x69);
        a3 = addiu(a3, 30848);
        jal(0x2b3ed0, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0xc1c8, F0);  // -25
        add_s(F20, F20, F0);
        lif(v0, 0x41c8, F0);  // 25
        add_s(F21, F21, F0);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xffff;
    }
    charge(28);
    mtc1(zero, F12);
    lw(a0, s1, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(0x2b3f24, rg::fn_sub_2A3E80_002a3e80);
    a0 = s1;
    a1 = addiu(sp, 64);
    a2 = addiu(sp, 92);
    a3 = addiu(sp, 120);
    t0 = addiu(sp, 148);
    t1 = li(1);
    jal(0x2b3f44, rg::fn_sub_2A2660_002a2660);
    lif(v0, 0x4120, F12);  // 10.0
    a0 = s1;
    jal(0x2b3f58, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 288);
}

// 0x2B3F80 sub_2B3F80(record): table row 34's init, a view of the enemy side from behind the subject. Key A = the
// record's current key (sub_2A4470). The enemy side's extent (sub_280870(3, 1, sp+168, sp+204, sp+200, 1) -> $f20 and
// the low / high y) gives the target sp+168 at mid height; the subject's position (sub_280050) at that height to the
// target, normalised and scaled by 0.35 (gp-32616) times its length, added to the target -> the point sp+184; key B
// looks from (subject x, 2.5 * high y, subject z) at it and sits $f20 / tan(1.2 * fov / 2) back along its view
// direction. Both keys go through sub_2A3590, then sub_2A2290(record, A, B, 1) and the lens 0.75.
void Cpu3::sub_2B3F80() {
    enter(150);
    sp = addiu(sp, -208);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s0 = a0;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, kActUnit);
    a0 = addiu(sp, 64);
    a1 = addiu(s0, kCwKey);
    jal(0x2b3fa8, rg::fn_sub_2A4470_002a4470);
    a0 = li(3);
    a1 = li(1);
    a2 = addiu(sp, 168);
    a3 = addiu(sp, 204);
    t0 = addiu(sp, 200);
    t1 = a1;
    jal(0x2b3fc8, rg::fn_sub_280870_00280870);
    mov_s(F20, F0);
    lwc1(F3, sp, 200);
    lwc1(F0, sp, 204);
    sub_s(F2, F0, F3);
    lif(v0, 0x3f00, F1);
    mtc1(zero, F0);
    adda_s(F0, F3);
    madd_s(F0, F1, F2);
    swc1(F0, sp, 172);
    tan_half_fov12(0x2b400c, s0, F1);
    div_s(F20, F20, F0);
    a0 = s1;
    a1 = addiu(sp, 120);
    jal(0x2b402c, rg::fn_sub_280050_00280050);
    lwc1(F3, sp, 120);
    swc1(F3, sp, 152);
    lwc1(F2, sp, 172);
    swc1(F2, sp, 156);
    lwc1(F1, sp, 128);
    swc1(F1, sp, 160);
    lwc1(F0, sp, 168);
    sub_s(F0, F3, F0);
    swc1(F0, sp, 136);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 140);
    lwc1(F0, sp, 176);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 144);
    a0 = addiu(sp, 136);
    a1 = a0;
    jal(0x2b4074, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F1, gp, -32616);  // 0.35
    mul_s(F1, F1, F0);
    scale_add(136, F1, 168, 184);
    lwc1(F0, sp, 120);
    swc1(F0, sp, 152);
    lif(v0, 0x4020, F1);  // 2.5
    lwc1(F0, sp, 204);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 156);
    lwc1(F0, sp, 128);
    swc1(F0, sp, 160);
    look_at(0x2b4104, 104, 152, 184);
    view_dir(0x2b4120, 136, 104);
    scale_add(136, F20, 184, 92);
    a0 = addiu(sp, 64);
    a1 = a0;
    jal(0x2b4178, rg::fn_sub_2A3590_002a3590);
    a0 = addiu(sp, 92);
    a1 = a0;
    jal(0x2b4188, rg::fn_sub_2A3590_002a3590);
    a0 = s0;
    a1 = addiu(sp, 64);
    a2 = addiu(sp, 92);
    a3 = li(1);
    jal(0x2b41a0, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x3f40, F12);  // 0.75
    a0 = s0;
    jal(0x2b41b4, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 208);
}

// 0x2B41E0 sub_2B41E0(record): table row 5's init, a shot past the subject's shoulder. Key A = the record's current
// key. The subject's unit position (sub_280050) and the distance from it to key A's position (sub_4C6AC0 of the
// difference, halved -> $f22, at least 600); the unit's forward (0x697890 rotated by its quaternion) gives the point
// half a width in front of it (sp+224) and the eye 1.5 * width / tan(fov / 2) further, raised to 0.8 * its height
// (gp-32636): key B looks from the eye at the point, limited to 45 degrees from key A's rotation (the limited slerp,
// then re-aimed from the point + the view direction). Key B's position = the point + its view direction * $f22, moved
// sideways by 0.21875 * $f22 * tan(1.2 * fov / 2); sub_2A2290(record, A, B, 1), the lens 1.25.
void Cpu3::sub_2B41E0() {
    enter(114);
    sp = addiu(sp, -272);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, kActUnit);
    lwc1(F1, s1, kUnitWidth);
    lwc1(F0, s1, kUnitScale);
    mul_s(F20, F1, F0);
    a0 = addiu(sp, 64);
    a1 = addiu(s0, kCwKey);
    jal(0x2b421c, rg::fn_sub_2A4470_002a4470);
    a0 = s1;
    a1 = addiu(sp, 208);
    jal(0x2b422c, rg::fn_sub_280050_00280050);
    sub_vec(240, 64, 208);
    a0 = addiu(sp, 240);
    jal(0x2b4268, rg::fn_sub_4C6AC0_004c6ac0);
    lif(v0, 0x3f00, F1);
    mul_s(F22, F0, F1);
    tan_half_fov(0x2b4288, s0, F1);
    lif(v0, 0x3fc0, F1);  // 1.5
    mul_s(F1, F1, F20);
    div_s(F21, F1, F0);
    a0 = addiu(sp, 240);
    a1 = lui(0x69);
    a1 = addiu(a1, 30864);
    a2 = li(1);
    a3 = addiu(s1, kUnitRot);
    jal(0x2b42b8, rg::fn_sub_4BE1E0_004be1e0);
    lif(v0, 0x3f00, F0);
    mul_s(F0, F0, F20);
    lwc1(F8, sp, 240);
    mul_s(F3, F8, F0);
    swc1(F3, sp, 256);
    lwc1(F7, sp, 244);
    mul_s(F2, F7, F0);
    swc1(F2, sp, 260);
    lwc1(F6, sp, 248);
    mul_s(F1, F6, F0);
    swc1(F1, sp, 264);
    lwc1(F0, sp, 208);
    add_s(F5, F0, F3);
    swc1(F5, sp, 224);
    lwc1(F0, sp, 212);
    add_s(F3, F0, F2);
    swc1(F3, sp, 228);
    lwc1(F0, sp, 216);
    add_s(F4, F0, F1);
    swc1(F4, sp, 232);
    mul_s(F0, F8, F21);
    swc1(F0, sp, 256);
    mul_s(F2, F7, F21);
    swc1(F2, sp, 260);
    mul_s(F1, F6, F21);
    swc1(F1, sp, 264);
    add_s(F0, F0, F5);
    swc1(F0, sp, 256);
    add_s(F3, F2, F3);
    swc1(F3, sp, 260);
    add_s(F0, F1, F4);
    swc1(F0, sp, 264);
    lwc1(F1, s1, kUnitHeight);
    lwc1(F0, s1, kUnitScale);
    mul_s(F2, F1, F0);
    lwc1(F1, gp, -32636);  // 0.8
    mtc1(zero, F0);
    adda_s(F0, F3);
    madd_s(F0, F1, F2);
    swc1(F0, sp, 260);
    look_at(0x2b4380, 104, 256, 224);
    a0 = addiu(sp, 76);
    a1 = addiu(sp, 104);
    jal(0x2b4390, rg::fn_sub_2D1F30_002d1f30);
    lwc1(F1, gp, -32556);  // pi/4
    c_le_s(F0, F1);
    if (!cc()) {
        slerp_limited(0x2b43c0, sp, 76, sp, 104, 128, 176, -32464, -32488);
        charge(26);
        view_dir(0x2b456c, 240, 176);
        add_vec(256, 224, 240);
        look_at(0x2b45b8, 104, 256, 224);
    }
    charge(6);
    lif(v0, 0x4416, F0);  // 600
    c_lt_s(F22, F0);
    if (cc()) {
        charge(1);
        mov_s(F22, F0);
    }
    charge(79);
    view_dir(0x2b45f0, 240, 104);
    for (s32 k = 0; k < 12; k += 4) {
        lwc1(F0, sp, 240 + k);
        mul_s(F0, F0, F22);
        swc1(F0, sp, 240 + k);
    }
    lif(v0, 0x3f00, F1);
    tan_half_fov12(0x2b4634, s0, F1);
    mul_s(F1, F22, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 240);
    swc1(F0, sp, 200);
    lwc1(F0, sp, 248);
    swc1(F0, sp, 204);
    a0 = addiu(sp, 200);
    a1 = a0;
    jal(0x2b4668, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 204);
    lwc1(F0, sp, 224);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, F20);
    swc1(F3, sp, 224);
    lwc1(F1, sp, 200);
    lwc1(F0, sp, 232);
    adda_s(F2, F0);
    msub_s(F2, F1, F20);
    swc1(F2, sp, 232);
    lwc1(F0, sp, 240);
    add_s(F0, F3, F0);
    swc1(F0, sp, 92);
    lwc1(F1, sp, 228);
    lwc1(F0, sp, 244);
    add_s(F0, F1, F0);
    swc1(F0, sp, 96);
    lwc1(F0, sp, 248);
    add_s(F0, F2, F0);
    swc1(F0, sp, 100);
    a0 = s0;
    a1 = addiu(sp, 64);
    a2 = addiu(sp, 92);
    a3 = li(1);
    jal(0x2b46d8, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x3fa0, F12);  // 1.25
    a0 = s0;
    jal(0x2b46ec, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 272);
}

}  // namespace p3fes::game::bcam

namespace p3fes::game {
#define P3FES_BCAM_API_3(name, addr) \
    void name(EEContext& ctx) { bcam::Cpu3(ctx).name(); }
P3FES_BCAM_BODIES_3(P3FES_BCAM_API_3)
#undef P3FES_BCAM_API_3
}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
#define P3FES_BCAM_SHIM_3(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { ::p3fes::game::bcam::Cpu3(ctx).name(); }
P3FES_BCAM_BODIES_3(P3FES_BCAM_SHIM_3)
#undef P3FES_BCAM_SHIM_3
}  // namespace p3fes::recomp_gen
